multiline_comment|/*&n; * I/O Processor (IOP) management&n; * Written and (C) 1999 by Joshua M. Thompson (funaho@jurai.org)&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice and this list of conditions.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice and this list of conditions in the documentation and/or other&n; *    materials provided with the distribution.&n; */
multiline_comment|/*&n; * The IOP chips are used in the IIfx and some Quadras (900, 950) to manage&n; * serial and ADB. They are actually a 6502 processor and some glue logic.&n; *&n; * 990429 (jmt) - Initial implementation, just enough to knock the SCC IOP&n; *&t;&t;  into compatible mode so nobody has to fiddle with the&n; *&t;&t;  Serial Switch control panel anymore.&n; * 990603 (jmt) - Added code to grab the correct ISM IOP interrupt for OSS&n; *&t;&t;  and non-OSS machines (at least I hope it&squot;s correct on a&n; *&t;&t;  non-OSS machine -- someone with a Q900 or Q950 needs to&n; *&t;&t;  check this.)&n; * 990605 (jmt) - Rearranged things a bit wrt IOP detection; iop_present is&n; *&t;&t;  gone, IOP base addresses are now in an array and the&n; *&t;&t;  globally-visible functions take an IOP number instead of an&n; *&t;&t;  an actual base address.&n; * 990610 (jmt) - Finished the message passing framework and it seems to work.&n; *&t;&t;  Sending _definately_ works; my adb-bus.c mods can send&n; *&t;&t;  messages and receive the MSG_COMPLETED status back from the&n; *&t;&t;  IOP. The trick now is figuring out the message formats.&n; * 990611 (jmt) - More cleanups. Fixed problem where unclaimed messages on a&n; *&t;&t;  receive channel were never properly acknowledged. Bracketed&n; *&t;&t;  the remaining debug printk&squot;s with #ifdef&squot;s and disabled&n; *&t;&t;  debugging. I can now type on the console.&n; * 990612 (jmt) - Copyright notice added. Reworked the way replies are handled.&n; *&t;&t;  It turns out that replies are placed back in the send buffer&n; *&t;&t;  for that channel; messages on the receive channels are always&n; *&t;&t;  unsolicited messages from the IOP (and our replies to them&n; *&t;&t;  should go back in the receive channel.) Also added tracking&n; *&t;&t;  of device names to the listener functions ala the interrupt&n; *&t;&t;  handlers.&n; * 990729 (jmt) - Added passing of pt_regs structure to IOP handlers. This is&n; *&t;&t;  used by the new unified ADB driver.&n; *&n; * TODO:&n; *&n; * o Something should be periodically checking iop_alive() to make sure the&n; *   IOP hasn&squot;t died.&n; * o Some of the IOP manager routines need better error checking and&n; *   return codes. Nothing major, just prettying up.&n; */
multiline_comment|/*&n; * -----------------------&n; * IOP Message Passing 101&n; * -----------------------&n; *&n; * The host talks to the IOPs using a rather simple message-passing scheme via&n; * a shared memory area in the IOP RAM. Each IOP has seven &quot;channels&quot;; each&n; * channel is conneced to a specific software driver on the IOP. For example&n; * on the SCC IOP there is one channel for each serial port. Each channel has&n; * an incoming and and outgoing message queue with a depth of one.&n; *&n; * A message is 32 bytes plus a state byte for the channel (MSG_IDLE, MSG_NEW,&n; * MSG_RCVD, MSG_COMPLETE). To send a message you copy the message into the&n; * buffer, set the state to MSG_NEW and signal the IOP by setting the IRQ flag&n; * in the IOP control to 1. The IOP will move the state to MSG_RCVD when it&n; * receives the message and then to MSG_COMPLETE when the message processing&n; * has completed. It is the host&squot;s responsibility at that point to read the&n; * reply back out of the send channel buffer and reset the channel state back&n; * to MSG_IDLE.&n; *&n; * To receive message from the IOP the same procedure is used except the roles&n; * are reversed. That is, the IOP puts message in the channel with a state of&n; * MSG_NEW, and the host receives the message and move its state to MSG_RCVD&n; * and then to MSG_COMPLETE when processing is completed and the reply (if any)&n; * has been placed back in the receive channel. The IOP will then reset the&n; * channel state to MSG_IDLE.&n; *&n; * Two sets of host interrupts are provided, INT0 and INT1. Both appear on one&n; * interrupt level; they are distinguished by a pair of bits in the IOP status&n; * register. The IOP will raise INT0 when one or more messages in the send&n; * channels have gone to the MSG_COMPLETE state and it will raise INT1 when one&n; * or more messages on the receive channels have gone to the MSG_NEW state.&n; *&n; * Since each channel handles only one message we have to implement a small&n; * interrupt-driven queue on our end. Messages to e sent are placed on the&n; * queue for sending and contain a pointer to an optional callback function.&n; * The handler for a message is called when the message state goes to&n; * MSG_COMPLETE.&n; *&n; * For receiving message we maintain a list of handler functions to call when&n; * a message is received on that IOP/channel combination. The handlers are&n; * called much like an interrupt handler and are passed a copy of the message&n; * from the IOP. The message state will be in MSG_RCVD while the handler runs;&n; * it is the handler&squot;s responsibility to call iop_complete_message() when&n; * finished; this function moves the message state to MSG_COMPLETE and signals&n; * the IOP. This two-step process is provided to allow the handler to defer&n; * message processing to a bottom-half handler if the processing will take&n; * a signifigant amount of time (handlers are called at interrupt time so they&n; * should execute quickly.)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt; 
macro_line|#include &lt;asm/macintosh.h&gt; 
macro_line|#include &lt;asm/macints.h&gt; 
macro_line|#include &lt;asm/mac_iop.h&gt;
macro_line|#include &lt;asm/mac_oss.h&gt;
multiline_comment|/*#define DEBUG_IOP*/
multiline_comment|/* Set to nonezero if the IOPs are present. Set by iop_init() */
DECL|variable|iop_scc_present
DECL|variable|iop_ism_present
r_int
id|iop_scc_present
comma
id|iop_ism_present
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|iop_get_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|function|iop_get_proc_info
r_static
r_int
id|iop_get_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
(brace
)brace
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/* structure for tracking channel listeners */
DECL|struct|listener
r_struct
id|listener
(brace
DECL|member|devname
r_const
r_char
op_star
id|devname
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IOP structures for the two IOPs&n; *&n; * The SCC IOP controls both serial ports (A and B) as its two functions.&n; * The ISM IOP controls the SWIM (floppy drive) and ADB.&n; */
DECL|variable|iop_base
r_static
r_volatile
r_struct
id|mac_iop
op_star
id|iop_base
(braket
id|NUM_IOPS
)braket
suffix:semicolon
multiline_comment|/*&n; * IOP message queues&n; */
DECL|variable|iop_msg_pool
r_static
r_struct
id|iop_msg
id|iop_msg_pool
(braket
id|NUM_IOP_MSGS
)braket
suffix:semicolon
DECL|variable|iop_send_queue
r_static
r_struct
id|iop_msg
op_star
id|iop_send_queue
(braket
id|NUM_IOPS
)braket
(braket
id|NUM_IOP_CHAN
)braket
suffix:semicolon
DECL|variable|iop_listeners
r_static
r_struct
id|listener
id|iop_listeners
(braket
id|NUM_IOPS
)braket
(braket
id|NUM_IOP_CHAN
)braket
suffix:semicolon
r_void
id|iop_ism_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|oss_irq_enable
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Private access functions&n; */
DECL|function|iop_loadaddr
r_static
id|__inline__
r_void
id|iop_loadaddr
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
comma
id|__u16
id|addr
)paren
(brace
id|iop-&gt;ram_addr_lo
op_assign
id|addr
suffix:semicolon
id|iop-&gt;ram_addr_hi
op_assign
id|addr
op_rshift
l_int|8
suffix:semicolon
)brace
DECL|function|iop_readb
r_static
id|__inline__
id|__u8
id|iop_readb
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
comma
id|__u16
id|addr
)paren
(brace
id|iop-&gt;ram_addr_lo
op_assign
id|addr
suffix:semicolon
id|iop-&gt;ram_addr_hi
op_assign
id|addr
op_rshift
l_int|8
suffix:semicolon
r_return
id|iop-&gt;ram_data
suffix:semicolon
)brace
DECL|function|iop_writeb
r_static
id|__inline__
r_void
id|iop_writeb
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
comma
id|__u16
id|addr
comma
id|__u8
id|data
)paren
(brace
id|iop-&gt;ram_addr_lo
op_assign
id|addr
suffix:semicolon
id|iop-&gt;ram_addr_hi
op_assign
id|addr
op_rshift
l_int|8
suffix:semicolon
id|iop-&gt;ram_data
op_assign
id|data
suffix:semicolon
)brace
DECL|function|iop_stop
r_static
id|__inline__
r_void
id|iop_stop
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
)paren
(brace
id|iop-&gt;status_ctrl
op_and_assign
op_complement
id|IOP_RUN
suffix:semicolon
)brace
DECL|function|iop_start
r_static
id|__inline__
r_void
id|iop_start
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
)paren
(brace
id|iop-&gt;status_ctrl
op_assign
id|IOP_RUN
op_or
id|IOP_AUTOINC
suffix:semicolon
)brace
DECL|function|iop_bypass
r_static
id|__inline__
r_void
id|iop_bypass
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
)paren
(brace
id|iop-&gt;status_ctrl
op_or_assign
id|IOP_BYPASS
suffix:semicolon
)brace
DECL|function|iop_interrupt
r_static
id|__inline__
r_void
id|iop_interrupt
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
)paren
(brace
id|iop-&gt;status_ctrl
op_or_assign
id|IOP_IRQ
suffix:semicolon
)brace
DECL|function|iop_alive
r_static
r_int
id|iop_alive
c_func
(paren
r_volatile
r_struct
id|mac_iop
op_star
id|iop
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
(paren
id|iop_readb
c_func
(paren
id|iop
comma
id|IOP_ADDR_ALIVE
)paren
op_eq
l_int|0xFF
)paren
suffix:semicolon
id|iop_writeb
c_func
(paren
id|iop
comma
id|IOP_ADDR_ALIVE
comma
l_int|0
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|iop_alloc_msg
r_static
r_struct
id|iop_msg
op_star
id|iop_alloc_msg
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|ulong
id|cpu_flags
suffix:semicolon
id|save_flags
c_func
(paren
id|cpu_flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_MSGS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|iop_msg_pool
(braket
id|i
)braket
dot
id|status
op_eq
id|IOP_MSGSTATUS_UNUSED
)paren
(brace
id|iop_msg_pool
(braket
id|i
)braket
dot
id|status
op_assign
id|IOP_MSGSTATUS_WAITING
suffix:semicolon
id|restore_flags
c_func
(paren
id|cpu_flags
)paren
suffix:semicolon
r_return
op_amp
id|iop_msg_pool
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|cpu_flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|iop_free_msg
r_static
r_void
id|iop_free_msg
c_func
(paren
r_struct
id|iop_msg
op_star
id|msg
)paren
(brace
id|msg-&gt;status
op_assign
id|IOP_MSGSTATUS_UNUSED
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called by the startup code before anything else. Its purpose&n; * is to find and initalize the IOPs early in the boot sequence, so that&n; * the serial IOP can be placed into bypass mode _before_ we try to&n; * initialize the serial console.&n; */
DECL|function|iop_preinit
r_void
id|__init
id|iop_preinit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|macintosh_config-&gt;scc_type
op_eq
id|MAC_SCC_IOP
)paren
(brace
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IIFX
)paren
(brace
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_assign
(paren
r_struct
id|mac_iop
op_star
)paren
id|SCC_IOP_BASE_IIFX
suffix:semicolon
)brace
r_else
(brace
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_assign
(paren
r_struct
id|mac_iop
op_star
)paren
id|SCC_IOP_BASE_QUADRA
suffix:semicolon
)brace
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_member_access_from_pointer
id|status_ctrl
op_assign
l_int|0x87
suffix:semicolon
id|iop_scc_present
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_assign
l_int|NULL
suffix:semicolon
id|iop_scc_present
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|macintosh_config-&gt;adb_type
op_eq
id|MAC_ADB_IOP
)paren
(brace
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IIFX
)paren
(brace
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
op_assign
(paren
r_struct
id|mac_iop
op_star
)paren
id|ISM_IOP_BASE_IIFX
suffix:semicolon
)brace
r_else
(brace
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
op_assign
(paren
r_struct
id|mac_iop
op_star
)paren
id|ISM_IOP_BASE_QUADRA
suffix:semicolon
)brace
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_member_access_from_pointer
id|status_ctrl
op_assign
l_int|0
suffix:semicolon
id|iop_ism_present
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
op_assign
l_int|NULL
suffix:semicolon
id|iop_ism_present
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Initialize the IOPs, if present.&n; */
DECL|function|iop_init
r_void
id|__init
id|iop_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|iop_scc_present
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IOP: detected SCC IOP at %p&bslash;n&quot;
comma
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iop_ism_present
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IOP: detected ISM IOP at %p&bslash;n&quot;
comma
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
)paren
suffix:semicolon
id|iop_start
c_func
(paren
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
)paren
suffix:semicolon
id|iop_alive
c_func
(paren
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
)paren
suffix:semicolon
multiline_comment|/* clears the alive flag */
)brace
multiline_comment|/* Make the whole pool available and empty the queues */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_MSGS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iop_msg_pool
(braket
id|i
)braket
dot
id|status
op_assign
id|IOP_MSGSTATUS_UNUSED
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_CHAN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|iop_send_queue
(braket
id|IOP_NUM_SCC
)braket
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|iop_send_queue
(braket
id|IOP_NUM_ISM
)braket
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|iop_listeners
(braket
id|IOP_NUM_SCC
)braket
(braket
id|i
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|iop_listeners
(braket
id|IOP_NUM_SCC
)braket
(braket
id|i
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|iop_listeners
(braket
id|IOP_NUM_ISM
)braket
(braket
id|i
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|iop_listeners
(braket
id|IOP_NUM_ISM
)braket
(braket
id|i
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
)brace
id|create_proc_info_entry
c_func
(paren
l_string|&quot;mac_iop&quot;
comma
l_int|0
comma
l_int|0
comma
id|iop_get_proc_info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register the interrupt handler for the IOPs.&n; * TODO: might be wrong for non-OSS machines. Anyone?&n; */
DECL|function|iop_register_interrupts
r_void
id|__init
id|iop_register_interrupts
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|iop_ism_present
)paren
(brace
r_if
c_cond
(paren
id|oss_present
)paren
(brace
id|request_irq
c_func
(paren
id|OSS_IRQLEV_IOPISM
comma
id|iop_ism_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;ISM IOP&quot;
comma
(paren
r_void
op_star
)paren
id|IOP_NUM_ISM
)paren
suffix:semicolon
id|oss_irq_enable
c_func
(paren
id|IRQ_MAC_ADB
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_irq
c_func
(paren
id|IRQ_VIA2_0
comma
id|iop_ism_irq
comma
id|IRQ_FLG_LOCK
op_or
id|IRQ_FLG_FAST
comma
l_string|&quot;ISM IOP&quot;
comma
(paren
r_void
op_star
)paren
id|IOP_NUM_ISM
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|iop_alive
c_func
(paren
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IOP: oh my god, they killed the ISM IOP!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;IOP: the ISM IOP seems to be alive.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Register or unregister a listener for a specific IOP and channel&n; *&n; * If the handler pointer is NULL the current listener (if any) is&n; * unregistered. Otherwise the new listener is registered provided&n; * there is no existing listener registered.&n; */
DECL|function|iop_listen
r_int
id|iop_listen
c_func
(paren
id|uint
id|iop_num
comma
id|uint
id|chan
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_const
r_char
op_star
id|devname
)paren
(brace
r_if
c_cond
(paren
(paren
id|iop_num
op_ge
id|NUM_IOPS
)paren
op_logical_or
op_logical_neg
id|iop_base
(braket
id|iop_num
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|chan
op_ge
id|NUM_IOP_CHAN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|chan
)braket
dot
id|handler
op_logical_and
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|chan
)braket
dot
id|devname
op_assign
id|devname
suffix:semicolon
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|chan
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Complete reception of a message, which just means copying the reply&n; * into the buffer, setting the channel state to MSG_COMPLETE and&n; * notifying the IOP.&n; */
DECL|function|iop_complete_message
r_void
id|iop_complete_message
c_func
(paren
r_struct
id|iop_msg
op_star
id|msg
)paren
(brace
r_int
id|iop_num
op_assign
id|msg-&gt;iop_num
suffix:semicolon
r_int
id|chan
op_assign
id|msg-&gt;channel
suffix:semicolon
r_int
id|i
comma
id|offset
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_complete(%p): iop %d chan %d&bslash;n&quot;
comma
id|msg
comma
id|msg-&gt;iop_num
comma
id|msg-&gt;channel
)paren
suffix:semicolon
macro_line|#endif
id|offset
op_assign
id|IOP_ADDR_RECV_MSG
op_plus
(paren
id|msg-&gt;channel
op_star
id|IOP_MSG_LEN
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IOP_MSG_LEN
suffix:semicolon
id|i
op_increment
comma
id|offset
op_increment
)paren
(brace
id|iop_writeb
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|offset
comma
id|msg-&gt;reply
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|iop_writeb
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|IOP_ADDR_RECV_STATE
op_plus
id|chan
comma
id|IOP_MSG_COMPLETE
)paren
suffix:semicolon
id|iop_interrupt
c_func
(paren
id|iop_base
(braket
id|msg-&gt;iop_num
)braket
)paren
suffix:semicolon
id|iop_free_msg
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Actually put a message into a send channel buffer&n; */
DECL|function|iop_do_send
r_static
r_void
id|iop_do_send
c_func
(paren
r_struct
id|iop_msg
op_star
id|msg
)paren
(brace
r_volatile
r_struct
id|mac_iop
op_star
id|iop
op_assign
id|iop_base
(braket
id|msg-&gt;iop_num
)braket
suffix:semicolon
r_int
id|i
comma
id|offset
suffix:semicolon
id|offset
op_assign
id|IOP_ADDR_SEND_MSG
op_plus
(paren
id|msg-&gt;channel
op_star
id|IOP_MSG_LEN
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IOP_MSG_LEN
suffix:semicolon
id|i
op_increment
comma
id|offset
op_increment
)paren
(brace
id|iop_writeb
c_func
(paren
id|iop
comma
id|offset
comma
id|msg-&gt;message
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|iop_writeb
c_func
(paren
id|iop
comma
id|IOP_ADDR_SEND_STATE
op_plus
id|msg-&gt;channel
comma
id|IOP_MSG_NEW
)paren
suffix:semicolon
id|iop_interrupt
c_func
(paren
id|iop
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle sending a message on a channel that&n; * has gone into the IOP_MSG_COMPLETE state.&n; */
DECL|function|iop_handle_send
r_static
r_void
id|iop_handle_send
c_func
(paren
id|uint
id|iop_num
comma
id|uint
id|chan
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_volatile
r_struct
id|mac_iop
op_star
id|iop
op_assign
id|iop_base
(braket
id|iop_num
)braket
suffix:semicolon
r_struct
id|iop_msg
op_star
id|msg
comma
op_star
id|msg2
suffix:semicolon
r_int
id|i
comma
id|offset
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_handle_send: iop %d channel %d&bslash;n&quot;
comma
id|iop_num
comma
id|chan
)paren
suffix:semicolon
macro_line|#endif
id|iop_writeb
c_func
(paren
id|iop
comma
id|IOP_ADDR_SEND_STATE
op_plus
id|chan
comma
id|IOP_MSG_IDLE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|msg
op_assign
id|iop_send_queue
(braket
id|iop_num
)braket
(braket
id|chan
)braket
)paren
)paren
r_return
suffix:semicolon
id|msg-&gt;status
op_assign
id|IOP_MSGSTATUS_COMPLETE
suffix:semicolon
id|offset
op_assign
id|IOP_ADDR_SEND_MSG
op_plus
(paren
id|chan
op_star
id|IOP_MSG_LEN
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IOP_MSG_LEN
suffix:semicolon
id|i
op_increment
comma
id|offset
op_increment
)paren
(brace
id|msg-&gt;reply
(braket
id|i
)braket
op_assign
id|iop_readb
c_func
(paren
id|iop
comma
id|offset
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msg-&gt;handler
)paren
(paren
op_star
id|msg-&gt;handler
)paren
(paren
id|msg
comma
id|regs
)paren
suffix:semicolon
id|msg2
op_assign
id|msg
suffix:semicolon
id|msg
op_assign
id|msg-&gt;next
suffix:semicolon
id|iop_free_msg
c_func
(paren
id|msg2
)paren
suffix:semicolon
id|iop_send_queue
(braket
id|iop_num
)braket
(braket
id|chan
)braket
op_assign
id|msg
suffix:semicolon
r_if
c_cond
(paren
id|msg
)paren
id|iop_do_send
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle reception of a message on a channel that has&n; * gone into the IOP_MSG_NEW state.&n; */
DECL|function|iop_handle_recv
r_static
r_void
id|iop_handle_recv
c_func
(paren
id|uint
id|iop_num
comma
id|uint
id|chan
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_volatile
r_struct
id|mac_iop
op_star
id|iop
op_assign
id|iop_base
(braket
id|iop_num
)braket
suffix:semicolon
r_int
id|i
comma
id|offset
suffix:semicolon
r_struct
id|iop_msg
op_star
id|msg
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_handle_recv: iop %d channel %d&bslash;n&quot;
comma
id|iop_num
comma
id|chan
)paren
suffix:semicolon
macro_line|#endif
id|msg
op_assign
id|iop_alloc_msg
c_func
(paren
)paren
suffix:semicolon
id|msg-&gt;iop_num
op_assign
id|iop_num
suffix:semicolon
id|msg-&gt;channel
op_assign
id|chan
suffix:semicolon
id|msg-&gt;status
op_assign
id|IOP_MSGSTATUS_UNSOL
suffix:semicolon
id|msg-&gt;handler
op_assign
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|chan
)braket
dot
id|handler
suffix:semicolon
id|offset
op_assign
id|IOP_ADDR_RECV_MSG
op_plus
(paren
id|chan
op_star
id|IOP_MSG_LEN
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IOP_MSG_LEN
suffix:semicolon
id|i
op_increment
comma
id|offset
op_increment
)paren
(brace
id|msg-&gt;message
(braket
id|i
)braket
op_assign
id|iop_readb
c_func
(paren
id|iop
comma
id|offset
)paren
suffix:semicolon
)brace
id|iop_writeb
c_func
(paren
id|iop
comma
id|IOP_ADDR_RECV_STATE
op_plus
id|chan
comma
id|IOP_MSG_RCVD
)paren
suffix:semicolon
multiline_comment|/* If there is a listener, call it now. Otherwise complete */
multiline_comment|/* the message ourselves to avoid possible stalls.         */
r_if
c_cond
(paren
id|msg-&gt;handler
)paren
(brace
(paren
op_star
id|msg-&gt;handler
)paren
(paren
id|msg
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_handle_recv: unclaimed message on iop %d channel %d&bslash;n&quot;
comma
id|iop_num
comma
id|chan
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;iop_handle_recv:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IOP_MSG_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
(paren
id|uint
)paren
id|msg-&gt;message
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|iop_complete_message
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Send a message&n; * &n; * The message is placed at the end of the send queue. Afterwards if the&n; * channel is idle we force an immediate send of the next message in the&n; * queue.&n; */
DECL|function|iop_send_message
r_int
id|iop_send_message
c_func
(paren
id|uint
id|iop_num
comma
id|uint
id|chan
comma
r_void
op_star
id|privdata
comma
id|uint
id|msg_len
comma
id|__u8
op_star
id|msg_data
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|iop_msg
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
r_struct
id|iop_msg
op_star
id|msg
comma
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
(paren
id|iop_num
op_ge
id|NUM_IOPS
)paren
op_logical_or
op_logical_neg
id|iop_base
(braket
id|iop_num
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|chan
op_ge
id|NUM_IOP_CHAN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|msg_len
OG
id|IOP_MSG_LEN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|msg
op_assign
id|iop_alloc_msg
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msg
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|msg-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|msg-&gt;status
op_assign
id|IOP_MSGSTATUS_WAITING
suffix:semicolon
id|msg-&gt;iop_num
op_assign
id|iop_num
suffix:semicolon
id|msg-&gt;channel
op_assign
id|chan
suffix:semicolon
id|msg-&gt;caller_priv
op_assign
id|privdata
suffix:semicolon
id|memcpy
c_func
(paren
id|msg-&gt;message
comma
id|msg_data
comma
id|msg_len
)paren
suffix:semicolon
id|msg-&gt;handler
op_assign
id|handler
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|q
op_assign
id|iop_send_queue
(braket
id|iop_num
)braket
(braket
id|chan
)braket
)paren
)paren
(brace
id|iop_send_queue
(braket
id|iop_num
)braket
(braket
id|chan
)braket
op_assign
id|msg
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|q-&gt;next
)paren
id|q
op_assign
id|q-&gt;next
suffix:semicolon
id|q-&gt;next
op_assign
id|msg
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iop_readb
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|IOP_ADDR_SEND_STATE
op_plus
id|chan
)paren
op_eq
id|IOP_MSG_IDLE
)paren
(brace
id|iop_do_send
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Upload code to the shared RAM of an IOP.&n; */
DECL|function|iop_upload_code
r_void
id|iop_upload_code
c_func
(paren
id|uint
id|iop_num
comma
id|__u8
op_star
id|code_start
comma
id|uint
id|code_len
comma
id|__u16
id|shared_ram_start
)paren
(brace
r_if
c_cond
(paren
(paren
id|iop_num
op_ge
id|NUM_IOPS
)paren
op_logical_or
op_logical_neg
id|iop_base
(braket
id|iop_num
)braket
)paren
r_return
suffix:semicolon
id|iop_loadaddr
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|shared_ram_start
)paren
suffix:semicolon
r_while
c_loop
(paren
id|code_len
op_decrement
)paren
(brace
id|iop_base
(braket
id|iop_num
)braket
op_member_access_from_pointer
id|ram_data
op_assign
op_star
id|code_start
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Download code from the shared RAM of an IOP.&n; */
DECL|function|iop_download_code
r_void
id|iop_download_code
c_func
(paren
id|uint
id|iop_num
comma
id|__u8
op_star
id|code_start
comma
id|uint
id|code_len
comma
id|__u16
id|shared_ram_start
)paren
(brace
r_if
c_cond
(paren
(paren
id|iop_num
op_ge
id|NUM_IOPS
)paren
op_logical_or
op_logical_neg
id|iop_base
(braket
id|iop_num
)braket
)paren
r_return
suffix:semicolon
id|iop_loadaddr
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|shared_ram_start
)paren
suffix:semicolon
r_while
c_loop
(paren
id|code_len
op_decrement
)paren
(brace
op_star
id|code_start
op_increment
op_assign
id|iop_base
(braket
id|iop_num
)braket
op_member_access_from_pointer
id|ram_data
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Compare the code in the shared RAM of an IOP with a copy in system memory&n; * and return 0 on match or the first nonmatching system memory address on&n; * failure.&n; */
DECL|function|iop_compare_code
id|__u8
op_star
id|iop_compare_code
c_func
(paren
id|uint
id|iop_num
comma
id|__u8
op_star
id|code_start
comma
id|uint
id|code_len
comma
id|__u16
id|shared_ram_start
)paren
(brace
r_if
c_cond
(paren
(paren
id|iop_num
op_ge
id|NUM_IOPS
)paren
op_logical_or
op_logical_neg
id|iop_base
(braket
id|iop_num
)braket
)paren
r_return
id|code_start
suffix:semicolon
id|iop_loadaddr
c_func
(paren
id|iop_base
(braket
id|iop_num
)braket
comma
id|shared_ram_start
)paren
suffix:semicolon
r_while
c_loop
(paren
id|code_len
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|code_start
op_ne
id|iop_base
(braket
id|iop_num
)braket
op_member_access_from_pointer
id|ram_data
)paren
(brace
r_return
id|code_start
suffix:semicolon
)brace
id|code_start
op_increment
suffix:semicolon
)brace
r_return
(paren
id|__u8
op_star
)paren
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle an ISM IOP interrupt&n; */
DECL|function|iop_ism_irq
r_void
id|iop_ism_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|uint
id|iop_num
op_assign
(paren
id|uint
)paren
id|dev_id
suffix:semicolon
r_volatile
r_struct
id|mac_iop
op_star
id|iop
op_assign
id|iop_base
(braket
id|iop_num
)braket
suffix:semicolon
r_int
id|i
comma
id|state
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_ism_irq: status = %02X&bslash;n&quot;
comma
(paren
id|uint
)paren
id|iop-&gt;status_ctrl
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* INT0 indicates a state change on an outgoing message channel */
r_if
c_cond
(paren
id|iop-&gt;status_ctrl
op_amp
id|IOP_INT0
)paren
(brace
id|iop-&gt;status_ctrl
op_assign
id|IOP_INT0
op_or
id|IOP_RUN
op_or
id|IOP_AUTOINC
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_ism_irq: new status = %02X, send states&quot;
comma
(paren
id|uint
)paren
id|iop-&gt;status_ctrl
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_CHAN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|state
op_assign
id|iop_readb
c_func
(paren
id|iop
comma
id|IOP_ADDR_SEND_STATE
op_plus
id|i
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
id|state
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|state
op_eq
id|IOP_MSG_COMPLETE
)paren
(brace
id|iop_handle_send
c_func
(paren
id|iop_num
comma
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|iop-&gt;status_ctrl
op_amp
id|IOP_INT1
)paren
(brace
multiline_comment|/* INT1 for incoming msgs */
id|iop-&gt;status_ctrl
op_assign
id|IOP_INT1
op_or
id|IOP_RUN
op_or
id|IOP_AUTOINC
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;iop_ism_irq: new status = %02X, recv states&quot;
comma
(paren
id|uint
)paren
id|iop-&gt;status_ctrl
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_CHAN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|state
op_assign
id|iop_readb
c_func
(paren
id|iop
comma
id|IOP_ADDR_RECV_STATE
op_plus
id|i
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
id|state
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|state
op_eq
id|IOP_MSG_NEW
)paren
(brace
id|iop_handle_recv
c_func
(paren
id|iop_num
comma
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG_IOP
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|iop_chan_state
r_char
op_star
id|iop_chan_state
c_func
(paren
r_int
id|state
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|IOP_MSG_IDLE
suffix:colon
r_return
l_string|&quot;idle      &quot;
suffix:semicolon
r_case
id|IOP_MSG_NEW
suffix:colon
r_return
l_string|&quot;new       &quot;
suffix:semicolon
r_case
id|IOP_MSG_RCVD
suffix:colon
r_return
l_string|&quot;received  &quot;
suffix:semicolon
r_case
id|IOP_MSG_COMPLETE
suffix:colon
r_return
l_string|&quot;completed &quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown   &quot;
suffix:semicolon
)brace
)brace
DECL|function|iop_dump_one_iop
r_int
id|iop_dump_one_iop
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|iop_num
comma
r_char
op_star
id|iop_name
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_volatile
r_struct
id|mac_iop
op_star
id|iop
op_assign
id|iop_base
(braket
id|iop_num
)braket
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s IOP channel states:&bslash;n&bslash;n&quot;
comma
id|iop_name
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;##  send_state  recv_state  device&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;------------------------------------------------&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IOP_CHAN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d  %10s  %10s  %s&bslash;n&quot;
comma
id|i
comma
id|iop_chan_state
c_func
(paren
id|iop_readb
c_func
(paren
id|iop
comma
id|IOP_ADDR_SEND_STATE
op_plus
id|i
)paren
)paren
comma
id|iop_chan_state
c_func
(paren
id|iop_readb
c_func
(paren
id|iop
comma
id|IOP_ADDR_RECV_STATE
op_plus
id|i
)paren
)paren
comma
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|i
)braket
dot
id|handler
ques
c_cond
id|iop_listeners
(braket
id|iop_num
)braket
(braket
id|i
)braket
dot
id|devname
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|iop_get_proc_info
r_int
id|iop_get_proc_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|pos
comma
r_int
id|count
comma
r_int
id|wr
)paren
(brace
r_int
id|len
comma
id|cnt
suffix:semicolon
id|cnt
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;IOPs detected:&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iop_scc_present
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;SCC IOP (%p): status %02X&bslash;n&quot;
comma
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
comma
(paren
id|uint
)paren
id|iop_base
(braket
id|IOP_NUM_SCC
)braket
op_member_access_from_pointer
id|status_ctrl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iop_ism_present
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;ISM IOP (%p): status %02X&bslash;n&bslash;n&quot;
comma
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
comma
(paren
id|uint
)paren
id|iop_base
(braket
id|IOP_NUM_ISM
)braket
op_member_access_from_pointer
id|status_ctrl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iop_scc_present
)paren
(brace
id|len
op_add_assign
id|iop_dump_one_iop
c_func
(paren
id|buf
op_plus
id|len
comma
id|IOP_NUM_SCC
comma
l_string|&quot;SCC&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iop_ism_present
)paren
(brace
id|len
op_add_assign
id|iop_dump_one_iop
c_func
(paren
id|buf
op_plus
id|len
comma
id|IOP_NUM_ISM
comma
l_string|&quot;ISM&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_ge
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|start
)paren
(brace
op_star
id|start
op_assign
id|buf
op_plus
id|pos
suffix:semicolon
id|cnt
op_assign
id|len
op_minus
id|pos
suffix:semicolon
)brace
r_else
(brace
id|cnt
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_return
(paren
id|count
OG
id|cnt
)paren
ques
c_cond
id|cnt
suffix:colon
id|count
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
