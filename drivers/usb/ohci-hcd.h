multiline_comment|/*&n; * OHCI HCD (Host Controller Driver) for USB.&n; *&n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; *&n; * The OHCI HCD layer is a simple but nearly complete implementation of what the&n; * USB people would call a HCD  for the OHCI. &n; * (ISO comming soon, Bulk disabled, INT u. CTRL transfers enabled)&n; * The layer on top of it, is for interfacing to the alternate-usb device-drivers.&n; * &n; * [ This is based on Linus&squot; UHCI code and gregs OHCI fragments (0.03c source tree). ]&n; * [ Open Host Controller Interface driver for USB. ]&n; * [ (C) Copyright 1999 Linus Torvalds (uhci.c) ]&n; * [ (C) Copyright 1999 Gregory P. Smith &lt;greg@electricrain.com&gt; ]&n; * [ $Log: ohci.c,v $ ]&n; * [ Revision 1.1  1999/04/05 08:32:30  greg ]&n; * &n; * &n; * v2.1 1999/05/09 ep_addr correction, code clean up&n; * v2.0 1999/05/04 &n; * v1.0 1999/04/27&n; * ohci-hcd.h&n; */
macro_line|#ifdef CONFIG_USB_OHCI_VROOTHUB
DECL|macro|VROOTHUB
mdefine_line|#define VROOTHUB  
macro_line|#endif
multiline_comment|/* enables virtual root hub &n; * (root hub will be managed by the hub controller &n; *  hub.c of the alternate usb driver)&n; *  last time I did more testing without virtual root hub &n; *  -&gt; the virtual root hub could be more unstable now */
macro_line|#ifdef OHCI_DBG
DECL|macro|OHCI_DEBUG
mdefine_line|#define OHCI_DEBUG(X) X
macro_line|#else 
DECL|macro|OHCI_DEBUG
mdefine_line|#define OHCI_DEBUG(X)
macro_line|#endif 
multiline_comment|/* for readl writel functions */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* for ED and TD structures */
DECL|typedef|__OHCI_BAG
r_typedef
r_void
op_star
id|__OHCI_BAG
suffix:semicolon
DECL|typedef|f_handler
r_typedef
r_int
(paren
op_star
id|f_handler
)paren
(paren
r_void
op_star
id|ohci
comma
r_int
r_int
id|ep_addr
comma
r_int
id|cmd_len
comma
r_void
op_star
id|cmd
comma
r_void
op_star
id|data
comma
r_int
id|data_len
comma
r_int
id|status
comma
id|__OHCI_BAG
id|lw0
comma
id|__OHCI_BAG
id|lw1
)paren
suffix:semicolon
DECL|struct|ep_address
r_struct
id|ep_address
(brace
DECL|member|ep
id|__u8
id|ep
suffix:semicolon
multiline_comment|/* bit 7: IN/-OUT, 6,5: type 10..CTRL 00..ISO  11..BULK 10..INT, 3..0: ep nr */
DECL|member|fa
id|__u8
id|fa
suffix:semicolon
multiline_comment|/* function address */
DECL|member|hc
id|__u8
id|hc
suffix:semicolon
DECL|member|host
id|__u8
id|host
suffix:semicolon
)brace
suffix:semicolon
DECL|union|ep_addr_
r_union
id|ep_addr_
(brace
DECL|member|iep
r_int
r_int
id|iep
suffix:semicolon
DECL|member|bep
r_struct
id|ep_address
id|bep
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ED and TD descriptors has to be 16-byte aligned&n; */
DECL|struct|ohci_hw_ed
r_struct
id|ohci_hw_ed
(brace
DECL|member|info
id|__u32
id|info
suffix:semicolon
DECL|member|tail_td
id|__u32
id|tail_td
suffix:semicolon
multiline_comment|/* TD Queue tail pointer */
DECL|member|head_td
id|__u32
id|head_td
suffix:semicolon
multiline_comment|/* TD Queue head pointer */
DECL|member|next_ed
id|__u32
id|next_ed
suffix:semicolon
multiline_comment|/* Next ED */
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|struct|usb_ohci_ed
r_struct
id|usb_ohci_ed
(brace
DECL|member|hw
r_struct
id|ohci_hw_ed
id|hw
suffix:semicolon
multiline_comment|/*  struct ohci * ohci; */
DECL|member|handler
id|f_handler
id|handler
suffix:semicolon
DECL|member|ep_addr
r_union
id|ep_addr_
id|ep_addr
suffix:semicolon
DECL|member|ed_list
r_struct
id|usb_ohci_ed
op_star
id|ed_list
suffix:semicolon
DECL|member|ed_prev
r_struct
id|usb_ohci_ed
op_star
id|ed_prev
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* OHCI Hardware fields */
DECL|struct|ohci_hw_td
r_struct
id|ohci_hw_td
(brace
DECL|member|info
id|__u32
id|info
suffix:semicolon
DECL|member|cur_buf
id|__u32
id|cur_buf
suffix:semicolon
multiline_comment|/* Current Buffer Pointer */
DECL|member|next_td
id|__u32
id|next_td
suffix:semicolon
multiline_comment|/* Next TD Pointer */
DECL|member|buf_end
id|__u32
id|buf_end
suffix:semicolon
multiline_comment|/* Memory Buffer End Pointer */
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* TD info field */
DECL|macro|TD_CC
mdefine_line|#define TD_CC       0xf0000000
DECL|macro|TD_CC_GET
mdefine_line|#define TD_CC_GET(td_p) ((td_p &gt;&gt;28) &amp; 0x04)
DECL|macro|TD_EC
mdefine_line|#define TD_EC       0x0C000000
DECL|macro|TD_T
mdefine_line|#define TD_T        0x03000000
DECL|macro|TD_T_DATA0
mdefine_line|#define TD_T_DATA0  0x02000000
DECL|macro|TD_T_DATA1
mdefine_line|#define TD_T_DATA1  0x03000000
DECL|macro|TD_T_TOGGLE
mdefine_line|#define TD_T_TOGGLE 0x00000000
DECL|macro|TD_R
mdefine_line|#define TD_R        0x00040000
DECL|macro|TD_DI
mdefine_line|#define TD_DI       0x00E00000
DECL|macro|TD_DI_SET
mdefine_line|#define TD_DI_SET(X) (((X) &amp; 0x07)&lt;&lt; 21)
DECL|macro|TD_DP
mdefine_line|#define TD_DP       0x00180000
DECL|macro|TD_DP_SETUP
mdefine_line|#define TD_DP_SETUP 0x00000000
DECL|macro|TD_DP_IN
mdefine_line|#define TD_DP_IN    0x00100000
DECL|macro|TD_DP_OUT
mdefine_line|#define TD_DP_OUT   0x00080000
multiline_comment|/* CC Codes */
DECL|macro|TD_CC_NOERROR
mdefine_line|#define TD_CC_NOERROR      0x00
DECL|macro|TD_CC_CRC
mdefine_line|#define TD_CC_CRC          0x01
DECL|macro|TD_CC_BITSTUFFING
mdefine_line|#define TD_CC_BITSTUFFING  0x02
DECL|macro|TD_CC_DATATOGGLEM
mdefine_line|#define TD_CC_DATATOGGLEM  0x03
DECL|macro|TD_CC_STALL
mdefine_line|#define TD_CC_STALL        0x04
DECL|macro|TD_DEVNOTRESP
mdefine_line|#define TD_DEVNOTRESP      0x05
DECL|macro|TD_PIDCHECKFAIL
mdefine_line|#define TD_PIDCHECKFAIL    0x06
DECL|macro|TD_UNEXPECTEDPID
mdefine_line|#define TD_UNEXPECTEDPID   0x07
DECL|macro|TD_DATAOVERRUN
mdefine_line|#define TD_DATAOVERRUN     0x08
DECL|macro|TD_DATAUNDERRUN
mdefine_line|#define TD_DATAUNDERRUN    0x09
DECL|macro|TD_BUFFEROVERRUN
mdefine_line|#define TD_BUFFEROVERRUN   0x0C
DECL|macro|TD_BUFFERUNDERRUN
mdefine_line|#define TD_BUFFERUNDERRUN  0x0D
DECL|macro|TD_NOTACCESSED
mdefine_line|#define TD_NOTACCESSED     0x0F
DECL|struct|usb_ohci_td
r_struct
id|usb_ohci_td
(brace
DECL|member|hw
r_struct
id|ohci_hw_td
id|hw
suffix:semicolon
DECL|member|buffer_start
r_void
op_star
id|buffer_start
suffix:semicolon
DECL|member|handler
id|f_handler
id|handler
suffix:semicolon
DECL|member|prev_td
r_struct
id|usb_ohci_td
op_star
id|prev_td
suffix:semicolon
DECL|member|ep
r_struct
id|usb_ohci_ed
op_star
id|ep
suffix:semicolon
DECL|member|next_dl_td
r_struct
id|usb_ohci_td
op_star
id|next_dl_td
suffix:semicolon
DECL|member|lw0
id|__OHCI_BAG
id|lw0
suffix:semicolon
DECL|member|lw1
id|__OHCI_BAG
id|lw1
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* TD types */
DECL|macro|BULK
mdefine_line|#define BULK&t;&t;0x03
DECL|macro|INT
mdefine_line|#define INT&t;&t;&t;0x01
DECL|macro|CTRL
mdefine_line|#define CTRL&t;&t;0x02
DECL|macro|ISO
mdefine_line|#define ISO&t;&t;&t;0x00
multiline_comment|/* TD types with direction */
DECL|macro|BULK_IN
mdefine_line|#define BULK_IN&t;&t;0x07
DECL|macro|BULK_OUT
mdefine_line|#define BULK_OUT&t;0x03
DECL|macro|INT_IN
mdefine_line|#define INT_IN&t;&t;0x05
DECL|macro|INT_OUT
mdefine_line|#define INT_OUT&t;&t;0x01
DECL|macro|CTRL_IN
mdefine_line|#define CTRL_IN&t;&t;0x06
DECL|macro|CTRL_OUT
mdefine_line|#define CTRL_OUT&t;0x02
DECL|macro|ISO_IN
mdefine_line|#define ISO_IN&t;&t;0x04
DECL|macro|ISO_OUT
mdefine_line|#define ISO_OUT&t;&t;0x00
DECL|struct|ohci_rep_td
r_struct
id|ohci_rep_td
(brace
DECL|member|cmd_len
r_int
id|cmd_len
suffix:semicolon
DECL|member|cmd
r_void
op_star
id|cmd
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
DECL|member|handler
id|f_handler
id|handler
suffix:semicolon
DECL|member|next_td
r_struct
id|ohci_rep_td
op_star
id|next_td
suffix:semicolon
DECL|member|ep_addr
r_int
id|ep_addr
suffix:semicolon
DECL|member|lw0
id|__OHCI_BAG
id|lw0
suffix:semicolon
DECL|member|lw1
id|__OHCI_BAG
id|lw1
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
DECL|macro|OHCI_ED_SKIP
mdefine_line|#define OHCI_ED_SKIP&t;(1 &lt;&lt; 14)
DECL|macro|OHCI_ED_MPS
mdefine_line|#define OHCI_ED_MPS&t;(0x7ff &lt;&lt; 16)
DECL|macro|OHCI_ED_F_NORM
mdefine_line|#define OHCI_ED_F_NORM&t;(0)
DECL|macro|OHCI_ED_F_ISOC
mdefine_line|#define OHCI_ED_F_ISOC&t;(1 &lt;&lt; 15)
DECL|macro|OHCI_ED_S_LOW
mdefine_line|#define OHCI_ED_S_LOW&t;(1 &lt;&lt; 13)
DECL|macro|OHCI_ED_S_HIGH
mdefine_line|#define OHCI_ED_S_HIGH&t;(0)
DECL|macro|OHCI_ED_D
mdefine_line|#define OHCI_ED_D&t;(3 &lt;&lt; 11)
DECL|macro|OHCI_ED_D_IN
mdefine_line|#define OHCI_ED_D_IN&t;(2 &lt;&lt; 11)
DECL|macro|OHCI_ED_D_OUT
mdefine_line|#define OHCI_ED_D_OUT&t;(1 &lt;&lt; 11)
DECL|macro|OHCI_ED_EN
mdefine_line|#define OHCI_ED_EN&t;(0xf &lt;&lt; 7)
DECL|macro|OHCI_ED_FA
mdefine_line|#define OHCI_ED_FA&t;(0x7f)
multiline_comment|/*&n; * The HCCA (Host Controller Communications Area) is a 256 byte&n; * structure defined in the OHCI spec. that the host controller is&n; * told the base address of.  It must be 256-byte aligned.&n; */
DECL|macro|NUM_INTS
mdefine_line|#define NUM_INTS 32&t;/* part of the OHCI standard */
DECL|struct|ohci_hcca
r_struct
id|ohci_hcca
(brace
DECL|member|int_table
id|__u32
id|int_table
(braket
id|NUM_INTS
)braket
suffix:semicolon
multiline_comment|/* Interrupt ED table */
DECL|member|frame_no
id|__u16
id|frame_no
suffix:semicolon
multiline_comment|/* current frame number */
DECL|member|pad1
id|__u16
id|pad1
suffix:semicolon
multiline_comment|/* set to 0 on each frame_no change */
DECL|member|done_head
id|__u32
id|done_head
suffix:semicolon
multiline_comment|/* info returned for an interrupt */
DECL|member|reserved_for_hc
id|u8
id|reserved_for_hc
(braket
l_int|116
)braket
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ED_INT_1
mdefine_line|#define ED_INT_1&t;1
DECL|macro|ED_INT_2
mdefine_line|#define ED_INT_2&t;2
DECL|macro|ED_INT_4
mdefine_line|#define ED_INT_4&t;4
DECL|macro|ED_INT_8
mdefine_line|#define ED_INT_8&t;8
DECL|macro|ED_INT_16
mdefine_line|#define ED_INT_16&t;16
DECL|macro|ED_INT_32
mdefine_line|#define ED_INT_32&t;32
DECL|macro|ED_CONTROL
mdefine_line|#define ED_CONTROL&t;64
DECL|macro|ED_BULK
mdefine_line|#define ED_BULK&t;&t;65
DECL|macro|ED_ISO
mdefine_line|#define ED_ISO&t;&t;0&t;/* same as 1ms interrupt queue */
multiline_comment|/*&n; * This is the maximum number of root hub ports.  I don&squot;t think we&squot;ll&n; * ever see more than two as that&squot;s the space available on an ATX&n; * motherboard&squot;s case, but it could happen.  The OHCI spec allows for&n; * up to 15... (which is insane!)&n; * &n; * Although I suppose several &quot;ports&quot; could be connected directly to&n; * internal laptop devices such as a keyboard, mouse, camera and&n; * serial/parallel ports.  hmm...  That&squot;d be neat.&n; */
DECL|macro|MAX_ROOT_PORTS
mdefine_line|#define MAX_ROOT_PORTS&t;15&t;/* maximum OHCI root hub ports */
multiline_comment|/*&n; * This is the structure of the OHCI controller&squot;s memory mapped I/O&n; * region.  This is Memory Mapped I/O.  You must use the readl() and&n; * writel() macros defined in asm/io.h to access these!!&n; */
DECL|struct|ohci_regs
r_struct
id|ohci_regs
(brace
multiline_comment|/* control and status registers */
DECL|member|revision
id|__u32
id|revision
suffix:semicolon
DECL|member|control
id|__u32
id|control
suffix:semicolon
DECL|member|cmdstatus
id|__u32
id|cmdstatus
suffix:semicolon
DECL|member|intrstatus
id|__u32
id|intrstatus
suffix:semicolon
DECL|member|intrenable
id|__u32
id|intrenable
suffix:semicolon
DECL|member|intrdisable
id|__u32
id|intrdisable
suffix:semicolon
multiline_comment|/* memory pointers */
DECL|member|hcca
id|__u32
id|hcca
suffix:semicolon
DECL|member|ed_periodcurrent
id|__u32
id|ed_periodcurrent
suffix:semicolon
DECL|member|ed_controlhead
id|__u32
id|ed_controlhead
suffix:semicolon
DECL|member|ed_controlcurrent
id|__u32
id|ed_controlcurrent
suffix:semicolon
DECL|member|ed_bulkhead
id|__u32
id|ed_bulkhead
suffix:semicolon
DECL|member|ed_bulkcurrent
id|__u32
id|ed_bulkcurrent
suffix:semicolon
DECL|member|donehead
id|__u32
id|donehead
suffix:semicolon
multiline_comment|/* frame counters */
DECL|member|fminterval
id|__u32
id|fminterval
suffix:semicolon
DECL|member|fmremaining
id|__u32
id|fmremaining
suffix:semicolon
DECL|member|fmnumber
id|__u32
id|fmnumber
suffix:semicolon
DECL|member|periodicstart
id|__u32
id|periodicstart
suffix:semicolon
DECL|member|lsthresh
id|__u32
id|lsthresh
suffix:semicolon
multiline_comment|/* Root hub ports */
DECL|struct|ohci_roothub_regs
r_struct
id|ohci_roothub_regs
(brace
DECL|member|a
id|__u32
id|a
suffix:semicolon
DECL|member|b
id|__u32
id|b
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|portstatus
id|__u32
id|portstatus
(braket
id|MAX_ROOT_PORTS
)braket
suffix:semicolon
DECL|member|roothub
)brace
id|roothub
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* &n; * Read a MMIO register and re-write it after ANDing with (m)&n; */
DECL|macro|writel_mask
mdefine_line|#define writel_mask(m, a) writel( (readl((__u32)(a))) &amp; (__u32)(m), (__u32)(a) )
multiline_comment|/*&n; * Read a MMIO register and re-write it after ORing with (b)&n; */
DECL|macro|writel_set
mdefine_line|#define writel_set(b, a) writel( (readl((__u32)(a))) | (__u32)(b), (__u32)(a) )
multiline_comment|/*&n; * cmdstatus register */
DECL|macro|OHCI_CLF
mdefine_line|#define OHCI_CLF  0x02
DECL|macro|OHCI_BLF
mdefine_line|#define OHCI_BLF  0x04
multiline_comment|/*&n; * Interrupt register masks&n; */
DECL|macro|OHCI_INTR_SO
mdefine_line|#define OHCI_INTR_SO&t;(1)
DECL|macro|OHCI_INTR_WDH
mdefine_line|#define OHCI_INTR_WDH&t;(1 &lt;&lt; 1)
DECL|macro|OHCI_INTR_SF
mdefine_line|#define OHCI_INTR_SF&t;(1 &lt;&lt; 2)
DECL|macro|OHCI_INTR_RD
mdefine_line|#define OHCI_INTR_RD&t;(1 &lt;&lt; 3)
DECL|macro|OHCI_INTR_UE
mdefine_line|#define OHCI_INTR_UE&t;(1 &lt;&lt; 4)
DECL|macro|OHCI_INTR_FNO
mdefine_line|#define OHCI_INTR_FNO&t;(1 &lt;&lt; 5)
DECL|macro|OHCI_INTR_RHSC
mdefine_line|#define OHCI_INTR_RHSC&t;(1 &lt;&lt; 6)
DECL|macro|OHCI_INTR_OC
mdefine_line|#define OHCI_INTR_OC&t;(1 &lt;&lt; 30)
DECL|macro|OHCI_INTR_MIE
mdefine_line|#define OHCI_INTR_MIE&t;(1 &lt;&lt; 31)
multiline_comment|/*&n; * Control register masks&n; */
DECL|macro|OHCI_USB_OPER
mdefine_line|#define OHCI_USB_OPER&t;&t;(2 &lt;&lt; 6)
DECL|macro|OHCI_USB_SUSPEND
mdefine_line|#define OHCI_USB_SUSPEND&t;(3 &lt;&lt; 6)
multiline_comment|/*&n; * This is the full ohci controller description&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs. (Linus)&n; */
DECL|struct|ohci
r_struct
id|ohci
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|regs
r_struct
id|ohci_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* OHCI controller&squot;s memory */
DECL|member|hc_area
r_struct
id|ohci_hc_area
op_star
id|hc_area
suffix:semicolon
multiline_comment|/* hcca, int ed-tree, ohci itself .. */
DECL|member|root_hub_funct_addr
r_int
id|root_hub_funct_addr
suffix:semicolon
multiline_comment|/* Address of Root Hub endpoint */
DECL|member|ohci_int_load
r_int
id|ohci_int_load
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* load of the 32 Interrupt Chains (for load ballancing)*/
DECL|member|ed_rm_list
r_struct
id|usb_ohci_ed
op_star
id|ed_rm_list
suffix:semicolon
multiline_comment|/* list of all endpoints to be removed */
DECL|member|ed_bulktail
r_struct
id|usb_ohci_ed
op_star
id|ed_bulktail
suffix:semicolon
multiline_comment|/* last endpoint of bulk list */
DECL|member|ed_controltail
r_struct
id|usb_ohci_ed
op_star
id|ed_controltail
suffix:semicolon
multiline_comment|/* last endpoint of control list */
DECL|member|ed_isotail
r_struct
id|usb_ohci_ed
op_star
id|ed_isotail
suffix:semicolon
multiline_comment|/* last endpoint of iso list */
DECL|member|root_hub
r_struct
id|ohci_device
op_star
id|root_hub
suffix:semicolon
DECL|member|ed_rh_ep0
r_struct
id|usb_ohci_ed
id|ed_rh_ep0
suffix:semicolon
DECL|member|ed_rh_epi
r_struct
id|usb_ohci_ed
id|ed_rh_epi
suffix:semicolon
DECL|member|td_rh_epi
r_struct
id|ohci_rep_td
op_star
id|td_rh_epi
suffix:semicolon
DECL|member|intrstatus
r_int
id|intrstatus
suffix:semicolon
DECL|member|ed_func_ep0
r_struct
id|usb_ohci_ed
op_star
id|ed_func_ep0
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* &quot;hash&quot;-table for ep to ed mapping */
DECL|member|repl_queue
r_struct
id|ohci_rep_td
op_star
id|repl_queue
suffix:semicolon
multiline_comment|/* for internal requests */
DECL|member|rh_int_interval
r_int
id|rh_int_interval
suffix:semicolon
DECL|member|rh_int_timer
r_int
id|rh_int_timer
suffix:semicolon
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Warning: This constant must not be so large as to cause the&n; *  ohci_device structure to exceed one 4096 byte page.  Or &quot;weird&n; *  things will happen&quot; as the alloc_ohci() function assumes that&n; *  its less than one page at the moment.  (FIXME)&n; */
DECL|macro|NUM_TDS
mdefine_line|#define NUM_TDS&t;4&t;&t;/* num of preallocated transfer descriptors */
DECL|macro|NUM_EDS
mdefine_line|#define NUM_EDS 80&t;&t;/* num of preallocated endpoint descriptors */
DECL|struct|ohci_hc_area
r_struct
id|ohci_hc_area
(brace
DECL|member|hcca
r_struct
id|ohci_hcca
id|hcca
suffix:semicolon
multiline_comment|/* OHCI mem. mapped IO area 256 Bytes*/
DECL|member|ed
r_struct
id|ohci_hw_ed
id|ed
(braket
id|NUM_EDS
)braket
suffix:semicolon
multiline_comment|/* Endpoint Descriptors 80 * 16  : 1280 Bytes */
DECL|member|td
r_struct
id|ohci_hw_td
id|td
(braket
id|NUM_TDS
)braket
suffix:semicolon
multiline_comment|/* Transfer Descriptors 2 * 32   : 64 Bytes */
DECL|member|ohci
r_struct
id|ohci
id|ohci
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ohci_device
r_struct
id|ohci_device
(brace
DECL|member|usb
r_struct
id|usb_device
op_star
id|usb
suffix:semicolon
DECL|member|ohci
r_struct
id|ohci
op_star
id|ohci
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ohci_to_usb
mdefine_line|#define ohci_to_usb(uhci)&t;((ohci)-&gt;usb)
DECL|macro|usb_to_ohci
mdefine_line|#define usb_to_ohci(usb)&t;((struct ohci_device *)(usb)-&gt;hcpriv)
multiline_comment|/* Debugging code */
multiline_comment|/*void show_ed(struct ohci_ed *ed);&n;void show_td(struct ohci_td *td);&n;void show_status(struct ohci *ohci); */
multiline_comment|/* hcd */
r_int
id|ohci_trans_req
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
r_int
id|ep_addr
comma
r_int
id|cmd_len
comma
r_void
op_star
id|cmd
comma
r_void
op_star
id|data
comma
r_int
id|data_len
comma
id|__OHCI_BAG
id|lw0
comma
id|__OHCI_BAG
id|lw1
)paren
suffix:semicolon
r_struct
id|usb_ohci_ed
op_star
id|usb_ohci_add_ep
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
r_int
id|ep_addr
comma
r_int
id|interval
comma
r_int
id|load
comma
id|f_handler
id|handler
comma
r_int
id|ep_size
comma
r_int
id|speed
)paren
suffix:semicolon
r_int
id|usb_ohci_rm_function
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
r_int
id|ep_addr
)paren
suffix:semicolon
r_int
id|usb_ohci_rm_ep
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_struct
id|usb_ohci_ed
op_star
id|ed
)paren
suffix:semicolon
r_struct
id|usb_ohci_ed
op_star
id|ohci_find_ep
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
r_int
id|ep_addr_in
)paren
suffix:semicolon
multiline_comment|/* roothub */
r_int
id|ohci_del_rh_int_timer
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
)paren
suffix:semicolon
r_int
id|ohci_init_rh_int_timer
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
id|interval
)paren
suffix:semicolon
r_int
id|root_hub_int_req
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
id|cmd_len
comma
r_void
op_star
id|ctrl
comma
r_void
op_star
id|data
comma
r_int
id|data_len
comma
id|__OHCI_BAG
id|lw0
comma
id|__OHCI_BAG
id|lw1
comma
id|f_handler
id|handler
)paren
suffix:semicolon
r_int
id|root_hub_send_irq
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_void
op_star
id|data
comma
r_int
id|data_len
)paren
suffix:semicolon
r_int
id|root_hub_control_msg
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
id|cmd_len
comma
r_void
op_star
id|rh_cmd
comma
r_void
op_star
id|rh_data
comma
r_int
id|len
comma
id|__OHCI_BAG
id|lw0
comma
id|__OHCI_BAG
id|lw1
comma
id|f_handler
id|handler
)paren
suffix:semicolon
r_int
id|queue_reply
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
comma
r_int
r_int
id|ep_addr
comma
r_int
id|cmd_len
comma
r_void
op_star
id|cmd
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
id|__OHCI_BAG
id|lw0
comma
id|__OHCI_BAG
id|lw1
comma
id|f_handler
id|handler
)paren
suffix:semicolon
r_int
id|send_replies
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
)paren
suffix:semicolon
multiline_comment|/* Root-Hub Register info */
DECL|macro|RH_PS_CCS
mdefine_line|#define RH_PS_CCS            0x00000001   
DECL|macro|RH_PS_PES
mdefine_line|#define RH_PS_PES            0x00000002   
DECL|macro|RH_PS_PSS
mdefine_line|#define RH_PS_PSS            0x00000004   
DECL|macro|RH_PS_POCI
mdefine_line|#define RH_PS_POCI           0x00000008   
DECL|macro|RH_PS_PRS
mdefine_line|#define RH_PS_PRS            0x00000010  
DECL|macro|RH_PS_PPS
mdefine_line|#define RH_PS_PPS            0x00000100   
DECL|macro|RH_PS_LSDA
mdefine_line|#define RH_PS_LSDA           0x00000200    
DECL|macro|RH_PS_CSC
mdefine_line|#define RH_PS_CSC            0x00010000 
DECL|macro|RH_PS_PESC
mdefine_line|#define RH_PS_PESC           0x00020000   
DECL|macro|RH_PS_PSSC
mdefine_line|#define RH_PS_PSSC           0x00040000    
DECL|macro|RH_PS_OCIC
mdefine_line|#define RH_PS_OCIC           0x00080000    
DECL|macro|RH_PS_PRSC
mdefine_line|#define RH_PS_PRSC           0x00100000   
macro_line|#ifdef OHCI_DBG
DECL|macro|OHCI_FREE
mdefine_line|#define OHCI_FREE(x) kfree(x); printk(&quot;OHCI FREE: %d&bslash;n&quot;, -- __ohci_free_cnt)
DECL|macro|OHCI_ALLOC
mdefine_line|#define OHCI_ALLOC(x,size) (x) = kmalloc(size, GFP_KERNEL); printk(&quot;OHCI ALLO: %d&bslash;n&quot;, ++ __ohci_free_cnt)
DECL|macro|USB_FREE
mdefine_line|#define USB_FREE(x) kfree(x); printk(&quot;USB FREE: %d&bslash;n&quot;, -- __ohci_free1_cnt)
DECL|macro|USB_ALLOC
mdefine_line|#define USB_ALLOC(x,size) (x) = kmalloc(size, GFP_KERNEL); printk(&quot;USB ALLO: %d&bslash;n&quot;, ++ __ohci_free1_cnt)
DECL|variable|__ohci_free_cnt
r_static
r_int
id|__ohci_free_cnt
op_assign
l_int|0
suffix:semicolon
DECL|variable|__ohci_free1_cnt
r_static
r_int
id|__ohci_free1_cnt
op_assign
l_int|0
suffix:semicolon
macro_line|#else
DECL|macro|OHCI_FREE
mdefine_line|#define OHCI_FREE(x) kfree(x) 
DECL|macro|OHCI_ALLOC
mdefine_line|#define OHCI_ALLOC(x,size) (x) = kmalloc(size, GFP_KERNEL) 
DECL|macro|USB_FREE
mdefine_line|#define USB_FREE(x) kfree(x) 
DECL|macro|USB_ALLOC
mdefine_line|#define USB_ALLOC(x,size) (x) = kmalloc(size, GFP_KERNEL) 
macro_line|#endif
eof
