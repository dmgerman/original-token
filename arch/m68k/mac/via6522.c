multiline_comment|/*&n; *&t;6522 Versatile Interface Adapter (VIA)&n; *&n; *&t;There are two of these on the Mac II. Some IRQ&squot;s are vectored&n; *&t;via them as are assorted bits and bobs - eg rtc, adb.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt; 
macro_line|#include &lt;asm/macints.h&gt; 
macro_line|#include &quot;via6522.h&quot;
macro_line|#include &quot;psc.h&quot;
DECL|variable|via1
r_volatile
r_int
r_char
op_star
id|via1
op_assign
(paren
r_int
r_char
op_star
)paren
id|VIABASE
suffix:semicolon
DECL|variable|via2
r_volatile
r_int
r_char
op_star
id|via2
op_assign
(paren
r_int
r_char
op_star
)paren
id|VIABASE2
suffix:semicolon
DECL|variable|psc
r_volatile
r_int
r_char
op_star
id|psc
op_assign
(paren
r_int
r_char
op_star
)paren
id|PSCBASE
suffix:semicolon
DECL|variable|via1_clock
DECL|variable|via1_datab
r_int
r_char
id|via1_clock
comma
id|via1_datab
suffix:semicolon
DECL|variable|rbv
r_static
r_int
id|rbv
op_assign
l_int|0
suffix:semicolon
DECL|variable|oss
r_static
r_int
id|oss
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
id|adb_interrupt
c_func
(paren
r_int
id|slot
comma
r_void
op_star
id|via
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * hardware reset vector&n; */
DECL|variable|rom_reset
r_static
r_void
(paren
op_star
id|rom_reset
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Timer defs.&n; */
DECL|macro|MAC_CLOCK_TICK
mdefine_line|#define MAC_CLOCK_TICK&t;&t;(783300/HZ)&t;/* ticks per HZ */
DECL|macro|MAC_CLOCK_LOW
mdefine_line|#define MAC_CLOCK_LOW&t;&t;(MAC_CLOCK_TICK&amp;0xFF)
DECL|macro|MAC_CLOCK_HIGH
mdefine_line|#define MAC_CLOCK_HIGH&t;&t;(MAC_CLOCK_TICK&gt;&gt;8)
DECL|function|via_init_clock
r_void
id|via_init_clock
c_func
(paren
r_void
(paren
op_star
id|func
)paren
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
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_switch
c_cond
(paren
id|macintosh_config-&gt;via_type
)paren
(brace
multiline_comment|/*&n;&t;&t; *      CI, SI, VX, LC &n;&t;&t; */
r_case
id|MAC_VIA_IIci
suffix:colon
id|via1
op_assign
(paren
r_void
op_star
)paren
l_int|0x50F00000
suffix:semicolon
id|via2
op_assign
(paren
r_void
op_star
)paren
l_int|0x50F26000
suffix:semicolon
id|rbv
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_IIFX
)paren
(brace
id|via2
op_assign
(paren
r_void
op_star
)paren
l_int|0x50F1A000
suffix:semicolon
id|oss
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; *      Quadra and early MacIIs agree on the VIA locations&n;&t;&t; */
r_case
id|MAC_VIA_QUADRA
suffix:colon
r_case
id|MAC_VIA_II
suffix:colon
id|via1
op_assign
(paren
r_void
op_star
)paren
l_int|0x50F00000
suffix:semicolon
id|via2
op_assign
(paren
r_void
op_star
)paren
l_int|0x50F02000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
)brace
id|via1_clock
op_assign
id|via_read
c_func
(paren
id|via1
comma
id|vACR
)paren
suffix:semicolon
id|via1_datab
op_assign
id|via_read
c_func
(paren
id|via1
comma
id|vBufB
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell what MacOS left us with&n;&t; */
id|printk
c_func
(paren
l_string|&quot;via_init: boot via1 acr=%X pcr=%X buf_a=%X dir_a=%X buf_b=%X dir_b=%X &bslash;n&quot;
comma
(paren
r_int
)paren
id|via1_clock
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vPCR
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vBufA
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vDirA
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vBufB
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vDirB
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbv
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;via_init: boot via2 acr=%X pcr=%X buf_a=%X dir_a=%X buf_b=%X dir_b=%X &bslash;n&quot;
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vACR
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vPCR
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vBufA
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vDirA
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vBufB
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vDirB
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Shut it down&n;&t; */
id|via_write
c_func
(paren
id|via1
comma
id|vIER
comma
l_int|0x7F
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Kill the timers&n;&t; */
id|via_write
c_func
(paren
id|via1
comma
id|vT1LL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1LH
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1CL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1CH
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT2CL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT2CH
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Now do via2&n;&t; */
r_if
c_cond
(paren
id|rbv
op_eq
l_int|0
)paren
(brace
id|via_write
c_func
(paren
id|via2
comma
id|vT1LL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vT1LH
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vT1CL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vT1CH
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vT2CL
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vT2CH
comma
l_int|0
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vIER
comma
l_int|0x7F
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|oss
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Init the RBV chip a bit&n;&t;&t; */
id|via_write
c_func
(paren
id|via2
comma
id|rIER
comma
l_int|0x7F
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Disable the timer latches&n;&t; */
id|c
op_assign
id|via_read
c_func
(paren
id|via1
comma
id|vACR
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vACR
comma
id|c
op_amp
l_int|0x3F
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbv
op_eq
l_int|0
)paren
(brace
id|c
op_assign
id|via_read
c_func
(paren
id|via2
comma
id|vACR
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vACR
comma
id|c
op_amp
l_int|0x3F
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Now start the clock - we want 100Hz&n;&t; */
id|via_write
c_func
(paren
id|via1
comma
id|vACR
comma
id|via_read
c_func
(paren
id|via1
comma
id|vACR
)paren
op_or
l_int|0x40
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1LL
comma
id|MAC_CLOCK_LOW
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1LH
comma
id|MAC_CLOCK_HIGH
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1CL
comma
id|MAC_CLOCK_LOW
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vT1CH
comma
id|MAC_CLOCK_HIGH
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;And enable its interrupt&n;&t; */
id|request_irq
c_func
(paren
id|IRQ_MAC_TIMER_1
comma
id|func
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;timer&quot;
comma
id|func
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * SE/30: disable video int. &n;&t; * XXX: testing for SE/30 VBL&n;&t; */
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_eq
id|MAC_MODEL_SE30
)paren
(brace
id|c
op_assign
id|via_read
c_func
(paren
id|via1
comma
id|vBufB
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vBufB
comma
id|c
op_or
(paren
l_int|0x40
)paren
)paren
suffix:semicolon
id|c
op_assign
id|via_read
c_func
(paren
id|via1
comma
id|vDirB
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via1
comma
id|vDirB
comma
id|c
op_or
(paren
l_int|0x40
)paren
)paren
suffix:semicolon
)brace
macro_line|#if 0 /* gone to mac_init_IRQ */
multiline_comment|/*&n;&t; * Set vPCR for SCSI interrupts.&n;&t; *&n;&t; * That is: CA1 negative edge int., CA2 indep., positive edge int.;&n;&t; *&t;    CB1 negative edge int., CB2 indep., positive edge int..&n;&t; */
id|via_write
c_func
(paren
id|via2
comma
id|vPCR
comma
l_int|0x66
)paren
suffix:semicolon
macro_line|#endif                                                                  
)brace
multiline_comment|/*&n; *&t;PSC (AV Macs; level 3-6): initialize interrupt enable registers&n; */
DECL|function|psc_init
r_void
id|psc_init
c_func
(paren
r_void
)paren
(brace
id|via_write
c_func
(paren
id|psc
comma
id|pIER3
comma
l_int|0x01
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|psc
comma
id|pIER4
comma
l_int|0x09
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|psc
comma
id|pIER4
comma
l_int|0x86
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|psc
comma
id|pIER5
comma
l_int|0x03
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|psc
comma
id|pIER6
comma
l_int|0x07
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The power switch - yes its software!&n; */
DECL|function|mac_poweroff
r_void
id|mac_poweroff
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
multiline_comment|/*&n;&t; * Powerdown, for the Macs that support it&n;&t; */
r_if
c_cond
(paren
id|rbv
)paren
(brace
id|via_write
c_func
(paren
id|via2
comma
id|rBufB
comma
id|via_read
c_func
(paren
id|via2
comma
id|rBufB
)paren
op_amp
op_complement
l_int|0x04
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Direction of vDirB is output */
id|via_write
c_func
(paren
id|via2
comma
id|vDirB
comma
id|via_read
c_func
(paren
id|via2
comma
id|vDirB
)paren
op_or
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* Send a value of 0 on that line */
id|via_write
c_func
(paren
id|via2
comma
id|vBufB
comma
id|via_read
c_func
(paren
id|via2
comma
id|vBufB
)paren
op_amp
op_complement
l_int|0x04
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* We should never make it this far... */
multiline_comment|/* XXX - delay do we need to spin here ? */
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Just in case .. */
)brace
multiline_comment|/* &n; * Not all Macs support software power down; for the rest, just &n; * try the ROM reset vector ...&n; */
DECL|function|mac_reset
r_void
id|mac_reset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
op_star
id|reset_hook
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0&t;/* need ROMBASE in booter */
macro_line|#if 0&t;/* works on some */
id|rom_reset
op_assign
(paren
id|boot_info.bi_mac.rombase
op_plus
l_int|0xa
)paren
suffix:semicolon
macro_line|#else&t;/* testing, doesn&squot;t work on SE/30 either */
id|reset_hook
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|boot_info.bi_mac.rombase
op_plus
l_int|0x4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ROM reset hook: %p&bslash;n&quot;
comma
op_star
id|reset_hook
)paren
suffix:semicolon
id|rom_reset
op_assign
op_star
id|reset_hook
suffix:semicolon
macro_line|#endif
id|rom_reset
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* We never make it this far... */
id|printk
c_func
(paren
l_string|&quot; reboot failed, reboot manually!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX - delay do we need to spin here ? */
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Just in case .. */
)brace
multiline_comment|/*&n; *&t;Set up the keyboard&n; */
DECL|function|via_setup_keyboard
r_void
id|via_setup_keyboard
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0 /* moved to adb */
id|via1_func_tab.vector
(braket
l_int|2
)braket
op_assign
id|adb_interrupt
suffix:semicolon
macro_line|#else
id|request_irq
c_func
(paren
id|IRQ_MAC_ADB
comma
id|adb_interrupt
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;adb interrupt&quot;
comma
id|adb_interrupt
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *&t;Floppy hook&n; */
DECL|function|via1_set_head
r_void
id|via1_set_head
c_func
(paren
r_int
id|head
)paren
(brace
r_if
c_cond
(paren
id|head
op_eq
l_int|0
)paren
(brace
id|via_write
c_func
(paren
id|via1
comma
id|vBufA
comma
id|via_read
c_func
(paren
id|via1
comma
id|vBufA
)paren
op_amp
op_complement
l_int|0x20
)paren
suffix:semicolon
)brace
r_else
id|via_write
c_func
(paren
id|via1
comma
id|vBufA
comma
id|via_read
c_func
(paren
id|via1
comma
id|vBufA
)paren
op_or
l_int|0x20
)paren
suffix:semicolon
)brace
DECL|function|nubus_init_via
r_void
id|nubus_init_via
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|rbv
)paren
(brace
r_if
c_cond
(paren
id|oss
op_eq
l_int|0
)paren
(brace
id|via_write
c_func
(paren
id|via2
comma
id|rBufB
comma
id|via_read
c_func
(paren
id|via2
comma
id|rBufB
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|rIER
comma
l_int|0x82
)paren
suffix:semicolon
multiline_comment|/* Interrupts on */
)brace
)brace
r_else
(brace
multiline_comment|/* Assert the nubus active */
id|via_write
c_func
(paren
id|via2
comma
id|vDirB
comma
id|via_read
c_func
(paren
id|via2
comma
id|vDirB
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
id|via_write
c_func
(paren
id|via2
comma
id|vBufB
comma
id|via_read
c_func
(paren
id|via2
comma
id|vBufB
)paren
op_or
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* Make the nubus interrupt source register all output (disable) */
multiline_comment|/* via_write(via2, vDirA, 0xFF); */
id|via_write
c_func
(paren
id|via2
comma
id|vIER
comma
l_int|0x82
)paren
suffix:semicolon
multiline_comment|/* Interrupts on */
)brace
id|printk
c_func
(paren
l_string|&quot;nubus_init_via: via1 acr=%X datab=%X pcr=%X&bslash;n&quot;
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vACR
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vBufB
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via1
comma
id|vPCR
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rbv
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;nubus_init_via: via2 acr=%X datab=%X pcr=%X&bslash;n&quot;
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vACR
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vBufB
)paren
comma
(paren
r_int
)paren
id|via_read
c_func
(paren
id|via2
comma
id|vPCR
)paren
)paren
suffix:semicolon
)brace
eof