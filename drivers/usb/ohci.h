macro_line|#ifndef __LINUX_OHCI_H
DECL|macro|__LINUX_OHCI_H
mdefine_line|#define __LINUX_OHCI_H
multiline_comment|/*&n; * Open Host Controller Interface data structures and defines.&n; *&n; * (C) Copyright 1999 Gregory P. Smith &lt;greg@electricrain.com&gt;&n; *&n; * $Id: ohci.h,v 1.24 1999/05/16 10:18:26 greg Exp $&n; */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;usb.h&quot;
r_struct
id|ohci_ed
suffix:semicolon
multiline_comment|/*&n; * Each TD must be aligned on a 16-byte boundary.  From the OHCI v1.0 spec&n; * it does not state that TDs must be contiguious in memory (due to the&n; * use of the next_td field).  This gives us extra room at the end of a&n; * TD for our own driver specific data.&n; *&n; * This structure&squot;s size must be a multiple of 16 bytes. ?? no way, I&n; * don&squot;t see why.  Alignment should be all that matters.&n; */
DECL|struct|ohci_td
r_struct
id|ohci_td
(brace
multiline_comment|/* OHCI Hardware fields */
DECL|member|info
id|__u32
id|info
suffix:semicolon
multiline_comment|/* TD status &amp; type flags */
DECL|member|cur_buf
id|__u32
id|cur_buf
suffix:semicolon
multiline_comment|/* Current Buffer Pointer (bus address) */
DECL|member|next_td
id|__u32
id|next_td
suffix:semicolon
multiline_comment|/* Next TD Pointer (bus address) */
DECL|member|buf_end
id|__u32
id|buf_end
suffix:semicolon
multiline_comment|/* Memory Buffer End Pointer (bus address) */
multiline_comment|/* Driver specific fields */
DECL|member|ed
r_struct
id|ohci_ed
op_star
id|ed
suffix:semicolon
multiline_comment|/* address of the ED this TD is on */
DECL|member|next_dl_td
r_struct
id|ohci_td
op_star
id|next_dl_td
suffix:semicolon
multiline_comment|/* used during donelist processing */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* virt. address of the the buffer */
DECL|member|completed
id|usb_device_irq
id|completed
suffix:semicolon
multiline_comment|/* Completion handler routine */
DECL|member|hcd_flags
r_int
id|hcd_flags
suffix:semicolon
multiline_comment|/* Flags for the HCD: */
multiline_comment|/* bit0: Is this TD allocated? */
multiline_comment|/* bit1: Is this a dummy (end of list) TD? */
multiline_comment|/* bit2: do NOT automatically free this TD on completion */
multiline_comment|/* bit3: this is the last TD in a contiguious TD chain */
DECL|member|usb_dev
r_struct
id|usb_device
op_star
id|usb_dev
suffix:semicolon
multiline_comment|/* the owning device */
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
multiline_comment|/* user defined pointer passed to irq handler */
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
DECL|macro|OHCI_TD_ROUND
mdefine_line|#define OHCI_TD_ROUND&t;(1 &lt;&lt; 18)&t;/* buffer rounding bit */
DECL|macro|OHCI_TD_D
mdefine_line|#define OHCI_TD_D&t;(3 &lt;&lt; 19)&t;/* direction of xfer: */
DECL|macro|OHCI_TD_D_IN
mdefine_line|#define OHCI_TD_D_IN&t;(2 &lt;&lt; 19)
DECL|macro|OHCI_TD_D_OUT
mdefine_line|#define OHCI_TD_D_OUT&t;(1 &lt;&lt; 19)
DECL|macro|OHCI_TD_D_SETUP
mdefine_line|#define OHCI_TD_D_SETUP (0 &lt;&lt; 19)
DECL|macro|td_set_dir_in
mdefine_line|#define td_set_dir_in(d)&t;((d) ? OHCI_TD_D_IN : OHCI_TD_D_OUT )
DECL|macro|td_set_dir_out
mdefine_line|#define td_set_dir_out(d)&t;((d) ? OHCI_TD_D_OUT : OHCI_TD_D_IN )
DECL|macro|OHCI_TD_IOC_DELAY
mdefine_line|#define OHCI_TD_IOC_DELAY (7 &lt;&lt; 21)&t;/* frame delay allowed before int. */
DECL|macro|OHCI_TD_IOC_OFF
mdefine_line|#define OHCI_TD_IOC_OFF&t;(OHCI_TD_IOC_DELAY)&t;/* no interrupt on complete */
DECL|macro|td_set_ioc_delay
mdefine_line|#define td_set_ioc_delay(frames)&t;(((frames) &amp; 7) &lt;&lt; 21)
DECL|macro|OHCI_TD_DT
mdefine_line|#define OHCI_TD_DT&t;(3 &lt;&lt; 24)&t;/* data toggle bits */
DECL|macro|TOGGLE_AUTO
mdefine_line|#define TOGGLE_AUTO&t;(0 &lt;&lt; 24)&t;/* automatic (from the ED) */
DECL|macro|TOGGLE_DATA0
mdefine_line|#define TOGGLE_DATA0&t;(2 &lt;&lt; 24)&t;/* force Data0 */
DECL|macro|TOGGLE_DATA1
mdefine_line|#define TOGGLE_DATA1&t;(3 &lt;&lt; 24)&t;/* force Data1 */
DECL|macro|td_force_toggle
mdefine_line|#define td_force_toggle(b)&t;(((b) | 2) &lt;&lt; 24)
DECL|macro|OHCI_TD_ERRCNT
mdefine_line|#define OHCI_TD_ERRCNT&t;(3 &lt;&lt; 26)&t;/* error count */
DECL|macro|td_errorcount
mdefine_line|#define td_errorcount(td)&t;((le32_to_cpup(&amp;(td).info) &gt;&gt; 26) &amp; 3)
DECL|macro|clear_td_errorcount
mdefine_line|#define clear_td_errorcount(td)&t;((td)-&gt;info &amp;= cpu_to_le32(~(__u32)OHCI_TD_ERRCNT))
DECL|macro|OHCI_TD_CC
mdefine_line|#define OHCI_TD_CC&t;(0xf &lt;&lt; 28)&t;/* condition code */
DECL|macro|OHCI_TD_CC_GET
mdefine_line|#define OHCI_TD_CC_GET(td_i) (((td_i) &gt;&gt; 28) &amp; 0xf)
DECL|macro|OHCI_TD_CC_NEW
mdefine_line|#define OHCI_TD_CC_NEW&t;(OHCI_TD_CC)&t;/* set this on all unaccessed TDs! */
DECL|macro|td_cc_notaccessed
mdefine_line|#define td_cc_notaccessed(td)&t;((le32_to_cpup(&amp;(td).info) &gt;&gt; 29) == 7)
DECL|macro|td_cc_accessed
mdefine_line|#define td_cc_accessed(td)&t;((le32_to_cpup(&amp;(td).info) &gt;&gt; 29) != 7)
DECL|macro|td_cc_noerror
mdefine_line|#define td_cc_noerror(td)&t;(((le32_to_cpup(&amp;(td).info)) &amp; OHCI_TD_CC) == 0)
DECL|macro|td_done
mdefine_line|#define td_done(td)&t;(td_cc_noerror((td)) || (td_errorcount((td)) == 3))
multiline_comment|/*&n; * Macros to use the td-&gt;hcd_flags field.&n; */
DECL|macro|td_allocated
mdefine_line|#define td_allocated(td)&t;((td).hcd_flags &amp; 1)
DECL|macro|allocate_td
mdefine_line|#define allocate_td(td)&t;&t;((td)-&gt;hcd_flags |= 1)
DECL|macro|ohci_free_td
mdefine_line|#define ohci_free_td(td)&t;((td)-&gt;hcd_flags &amp;= ~(__u32)1)
DECL|macro|td_dummy
mdefine_line|#define td_dummy(td)&t;&t;((td).hcd_flags &amp; 2)
DECL|macro|make_dumb_td
mdefine_line|#define make_dumb_td(td)&t;((td)-&gt;hcd_flags |= 2)
DECL|macro|clear_dumb_td
mdefine_line|#define clear_dumb_td(td)&t;((td)-&gt;hcd_flags &amp;= ~(__u32)2)
DECL|macro|td_endofchain
mdefine_line|#define td_endofchain(td)&t;((td).hcd_flags &amp; (1 &lt;&lt; 3))
DECL|macro|clear_td_endofchain
mdefine_line|#define clear_td_endofchain(td)&t;((td)-&gt;hcd_flags &amp;= ~(1 &lt;&lt; 3))
DECL|macro|set_td_endofchain
mdefine_line|#define set_td_endofchain(td)&t;((td)-&gt;hcd_flags |= (1 &lt;&lt; 3))
multiline_comment|/*&n; * These control if the IRQ will call ohci_free_td after taking the TDs&n; * off of the donelist (assuming the completion function does not ask&n; * for the TD to be requeued).&n; */
DECL|macro|can_auto_free
mdefine_line|#define can_auto_free(td)&t;(!((td).hcd_flags &amp; 4))
DECL|macro|noauto_free_td
mdefine_line|#define noauto_free_td(td)&t;((td)-&gt;hcd_flags |= 4)
DECL|macro|auto_free_td
mdefine_line|#define auto_free_td(td)&t;((td)-&gt;hcd_flags &amp;= ~(__u32)4)
multiline_comment|/*&n; * The endpoint descriptors also requires 16-byte alignment&n; */
DECL|struct|ohci_ed
r_struct
id|ohci_ed
(brace
multiline_comment|/* OHCI hardware fields */
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|tail_td
id|__u32
id|tail_td
suffix:semicolon
multiline_comment|/* TD Queue tail pointer */
DECL|member|_head_td
id|__u32
id|_head_td
suffix:semicolon
multiline_comment|/* TD Queue head pointer, toggle carry &amp; halted bits */
DECL|member|next_ed
id|__u32
id|next_ed
suffix:semicolon
multiline_comment|/* Next ED */
multiline_comment|/* driver fields */
DECL|member|ohci_dev
r_struct
id|ohci_device
op_star
id|ohci_dev
suffix:semicolon
DECL|member|ed_chain
r_struct
id|ohci_ed
op_star
id|ed_chain
suffix:semicolon
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
multiline_comment|/* get the head_td */
DECL|macro|ed_head_td
mdefine_line|#define ed_head_td(ed)&t;(le32_to_cpup(&amp;(ed)-&gt;_head_td) &amp; 0xfffffff0)
DECL|macro|ed_tail_td
mdefine_line|#define ed_tail_td(ed)&t;(le32_to_cpup(&amp;(ed)-&gt;tail_td))
multiline_comment|/* save the carry &amp; halted flag while setting the head_td */
DECL|macro|set_ed_head_td
mdefine_line|#define set_ed_head_td(ed, td)&t;((ed)-&gt;_head_td = cpu_to_le32((td)) &bslash;&n;&t;&t;&t;&t; | ((ed)-&gt;_head_td &amp; cpu_to_le32(3)))
multiline_comment|/* Control the ED&squot;s halted and carry flags */
DECL|macro|ohci_halt_ed
mdefine_line|#define ohci_halt_ed(ed)&t;((ed)-&gt;_head_td |= cpu_to_le32(1))
DECL|macro|ohci_unhalt_ed
mdefine_line|#define ohci_unhalt_ed(ed)&t;((ed)-&gt;_head_td &amp;= cpu_to_le32(~(__u32)1))
DECL|macro|ohci_ed_halted
mdefine_line|#define ohci_ed_halted(ed)&t;((ed)-&gt;_head_td &amp; cpu_to_le32(1))
DECL|macro|ohci_ed_set_carry
mdefine_line|#define ohci_ed_set_carry(ed)&t;((ed)-&gt;_head_td |= cpu_to_le32(2))
DECL|macro|ohci_ed_clr_carry
mdefine_line|#define ohci_ed_clr_carry(ed)&t;((ed)-&gt;_head_td &amp;= ~cpu_to_le32(2))
DECL|macro|ohci_ed_carry
mdefine_line|#define ohci_ed_carry(ed)&t;((le32_to_cpup(&amp;(ed)-&gt;_head_td) &gt;&gt; 1) &amp; 1)
DECL|macro|OHCI_ED_SKIP
mdefine_line|#define OHCI_ED_SKIP&t;(1 &lt;&lt; 14)
DECL|macro|OHCI_ED_MPS
mdefine_line|#define OHCI_ED_MPS&t;(0x7ff &lt;&lt; 16)
multiline_comment|/* FIXME: should cap at the USB max packet size [0x4ff] */
DECL|macro|ed_set_maxpacket
mdefine_line|#define ed_set_maxpacket(s)&t;(((s) &lt;&lt; 16) &amp; OHCI_ED_MPS)
DECL|macro|OHCI_ED_F_NORM
mdefine_line|#define OHCI_ED_F_NORM&t;(0)
DECL|macro|OHCI_ED_F_ISOC
mdefine_line|#define OHCI_ED_F_ISOC&t;(1 &lt;&lt; 15)
DECL|macro|ed_set_type_isoc
mdefine_line|#define ed_set_type_isoc(i)&t;((i) ? OHCI_ED_F_ISOC : OHCI_ED_F_NORM)
DECL|macro|OHCI_ED_S_LOW
mdefine_line|#define OHCI_ED_S_LOW&t;(1 &lt;&lt; 13)
DECL|macro|OHCI_ED_S_HIGH
mdefine_line|#define OHCI_ED_S_HIGH&t;(0)
DECL|macro|ed_set_speed
mdefine_line|#define ed_set_speed(s)&t;&t;((s) ? OHCI_ED_S_LOW : OHCI_ED_S_HIGH)
DECL|macro|OHCI_ED_D
mdefine_line|#define OHCI_ED_D&t;(3 &lt;&lt; 11)
DECL|macro|OHCI_ED_D_IN
mdefine_line|#define OHCI_ED_D_IN&t;(2 &lt;&lt; 11)
DECL|macro|OHCI_ED_D_OUT
mdefine_line|#define OHCI_ED_D_OUT&t;(1 &lt;&lt; 11)
DECL|macro|ed_set_dir_in
mdefine_line|#define ed_set_dir_in(d)&t;((d) ? OHCI_ED_D_IN : OHCI_ED_D_OUT)
DECL|macro|ed_set_dir_out
mdefine_line|#define ed_set_dir_out(d)&t;((d) ? OHCI_ED_D_OUT : OHCI_ED_D_IN)
DECL|macro|OHCI_ED_EN
mdefine_line|#define OHCI_ED_EN&t;(0xf &lt;&lt; 7)
DECL|macro|OHCI_ED_FA
mdefine_line|#define OHCI_ED_FA&t;(0x7f)
DECL|macro|ed_get_en
mdefine_line|#define ed_get_en(ed)&t;((le32_to_cpup(&amp;(ed)-&gt;status) &amp; OHCI_ED_EN) &gt;&gt; 7)
DECL|macro|ed_get_fa
mdefine_line|#define ed_get_fa(ed)&t;(le32_to_cpup(&amp;(ed)-&gt;status) &amp; OHCI_ED_FA)
multiline_comment|/* NOTE: bits 27-31 of the status dword are reserved for the HCD */
multiline_comment|/*&n; * We&squot;ll use this status flag for to mark if an ED is in use by the&n; * driver or not.  If the bit is set, it is being used.&n; */
DECL|macro|ED_ALLOCATED
mdefine_line|#define ED_ALLOCATED&t;(1 &lt;&lt; 31)
DECL|macro|ed_allocated
mdefine_line|#define ed_allocated(ed)&t;(le32_to_cpup(&amp;(ed).status) &amp; ED_ALLOCATED)
DECL|macro|allocate_ed
mdefine_line|#define allocate_ed(ed)&t;&t;((ed)-&gt;status |= cpu_to_le32(ED_ALLOCATED))
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
DECL|member|donehead
id|__u32
id|donehead
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
multiline_comment|/*&n; * The TD entries here are pre-allocated as Linus did with his simple&n; * UHCI implementation.  With the current state of this driver that&n; * shouldn&squot;t be a problem.  However if someone ever connects 127&n; * supported devices to this driver and tries to use them all at once:&n; * &t;a)  They&squot;re insane!&n; * &t;b)  They should code in dynamic allocation&n; */
r_struct
id|ohci
suffix:semicolon
multiline_comment|/*&n; *  Warning: These constants must not be so large as to cause the&n; *  ohci_device structure to exceed one 4096 byte page.  Or &quot;weird&n; *  things will happen&quot; as the alloc_ohci() function assumes that&n; *  its less than one page.  (FIXME)&n; */
DECL|macro|NUM_TDS
mdefine_line|#define NUM_TDS&t;32&t;&t;/* num of preallocated transfer descriptors */
DECL|macro|DATA_BUF_LEN
mdefine_line|#define DATA_BUF_LEN 16&t;&t;/* num of unsigned long&squot;s for the data buf */
multiline_comment|/*&n; * For this &quot;simple&quot; driver we only support a single ED for each&n; * polling rate.&n; *&n; * Later on this driver should be extended to use a full tree of EDs&n; * so that there can be 32 different 32ms polling frames, etc.&n; * Individual devices shouldn&squot;t need as many as the root hub in that&n; * case; complicating how things are done at the moment.&n; *&n; * Bulk and Control transfers hang off of their own ED lists.&n; */
DECL|macro|NUM_EDS
mdefine_line|#define NUM_EDS 16&t;&t;/* num of preallocated endpoint descriptors */
DECL|macro|ohci_to_usb
mdefine_line|#define ohci_to_usb(ohci)&t;((ohci)-&gt;usb)
DECL|macro|usb_to_ohci
mdefine_line|#define usb_to_ohci(usb)&t;((struct ohci_device *)(usb)-&gt;hcpriv)
multiline_comment|/* The usb_device must be first! */
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
DECL|member|hcca
r_struct
id|ohci_hcca
op_star
id|hcca
suffix:semicolon
multiline_comment|/* OHCI mem. mapped IO area */
DECL|member|ed
r_struct
id|ohci_ed
id|ed
(braket
id|NUM_EDS
)braket
suffix:semicolon
multiline_comment|/* Endpoint Descriptors */
DECL|member|td
r_struct
id|ohci_td
id|td
(braket
id|NUM_TDS
)braket
suffix:semicolon
multiline_comment|/* Transfer Descriptors */
DECL|member|data
r_int
r_int
id|data
(braket
id|DATA_BUF_LEN
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
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* .... */
multiline_comment|/*&n; * These are the index of the placeholder EDs for the root hub to&n; * build the interrupt transfer ED tree out of.&n; */
DECL|macro|ED_INT_1
mdefine_line|#define ED_INT_1&t;0
DECL|macro|ED_INT_2
mdefine_line|#define ED_INT_2&t;1
DECL|macro|ED_INT_4
mdefine_line|#define ED_INT_4&t;2
DECL|macro|ED_INT_8
mdefine_line|#define ED_INT_8&t;3
DECL|macro|ED_INT_16
mdefine_line|#define ED_INT_16&t;4
DECL|macro|ED_INT_32
mdefine_line|#define ED_INT_32&t;5
DECL|macro|ED_ISO
mdefine_line|#define ED_ISO&t;&t;ED_INT_1&t;/* same as 1ms interrupt queue */
multiline_comment|/*&n; * Given a period p in ms, convert it to the closest endpoint&n; * interrupt frequency; rounding down.  This is a gross macro.&n; * Feel free to toss it for actual code. (gasp!)&n; */
DECL|macro|ms_to_ed_int
mdefine_line|#define ms_to_ed_int(p) &bslash;&n;&t;((p &gt;= 32) ? ED_INT_32 : &bslash;&n;&t; ((p &amp; 16) ? ED_INT_16 : &bslash;&n;&t;  ((p &amp; 8) ? ED_INT_8 : &bslash;&n;&t;   ((p &amp; 4) ? ED_INT_4 : &bslash;&n;&t;    ((p &amp; 2) ? ED_INT_2 : &bslash;&n;&t;     ED_INT_1)))))  /* hmm.. scheme or lisp anyone? */
multiline_comment|/*&n; * This is the maximum number of root hub ports.  I don&squot;t think we&squot;ll&n; * ever see more than two as that&squot;s the space available on an ATX&n; * motherboard&squot;s case, but it could happen.  The OHCI spec allows for&n; * up to 15... (which is insane given that they each need to supply up&n; * to 500ma; that would be 7.5 amps!).  I have seen a PCI card with 4&n; * downstream ports on it.&n; * &n; * Although I suppose several &quot;ports&quot; could be connected directly to&n; * internal laptop devices such as a keyboard, mouse, camera and&n; * serial/parallel ports.  hmm...  That&squot;d be neat.&n; */
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
DECL|member|current_donehead
id|__u32
id|current_donehead
suffix:semicolon
multiline_comment|/* The driver should get this from the HCCA */
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
multiline_comment|/*&n; * These are used by internal ED managing functions as a&n; * parameter to state the type of ED to deal with (when it matters).&n; */
DECL|macro|HCD_ED_ISOC
mdefine_line|#define HCD_ED_ISOC     (0)
DECL|macro|HCD_ED_INT
mdefine_line|#define HCD_ED_INT      (1)
DECL|macro|HCD_ED_CONTROL
mdefine_line|#define HCD_ED_CONTROL  (2)
DECL|macro|HCD_ED_BULK
mdefine_line|#define HCD_ED_BULK     (3)
multiline_comment|/* &n; * Read a MMIO register and re-write it after ANDing with (m)&n; */
DECL|macro|writel_mask
mdefine_line|#define writel_mask(m, a) writel( (readl((unsigned long)(a))) &amp; (__u32)(m), (unsigned long)(a) )
multiline_comment|/*&n; * Read a MMIO register and re-write it after ORing with (b)&n; */
DECL|macro|writel_set
mdefine_line|#define writel_set(b, a) writel( (readl((unsigned long)(a))) | (__u32)(b), (unsigned long)(a) )
DECL|macro|PORT_CCS
mdefine_line|#define PORT_CCS&t;(1)&t;&t;/* port current connect status */
DECL|macro|PORT_PES
mdefine_line|#define PORT_PES&t;(1 &lt;&lt; 1)&t;/* port enable status */
DECL|macro|PORT_PSS
mdefine_line|#define PORT_PSS&t;(1 &lt;&lt; 2)&t;/* port suspend status */
DECL|macro|PORT_POCI
mdefine_line|#define PORT_POCI&t;(1 &lt;&lt; 3)&t;/* port overcurrent indicator */
DECL|macro|PORT_PRS
mdefine_line|#define PORT_PRS&t;(1 &lt;&lt; 4)&t;/* port reset status */
DECL|macro|PORT_PPS
mdefine_line|#define PORT_PPS&t;(1 &lt;&lt; 8)&t;/* port power status */
DECL|macro|PORT_LSDA
mdefine_line|#define PORT_LSDA&t;(1 &lt;&lt; 9)&t;/* port low speed dev. attached */
DECL|macro|PORT_CSC
mdefine_line|#define PORT_CSC&t;(1 &lt;&lt; 16)&t;/* port connect status change */
DECL|macro|PORT_PESC
mdefine_line|#define PORT_PESC&t;(1 &lt;&lt; 17)&t;/* port enable status change */
DECL|macro|PORT_PSSC
mdefine_line|#define PORT_PSSC&t;(1 &lt;&lt; 18)&t;/* port suspend status change */
DECL|macro|PORT_OCIC
mdefine_line|#define PORT_OCIC&t;(1 &lt;&lt; 19)&t;/* port over current indicator chg */
DECL|macro|PORT_PRSC
mdefine_line|#define PORT_PRSC&t;(1 &lt;&lt; 20)&t;/* port reset status change */
multiline_comment|/*&n; * Root Hub status register masks&n; */
DECL|macro|OHCI_ROOT_LPS
mdefine_line|#define OHCI_ROOT_LPS&t;(1)&t;&t;/* turn off root hub ports power */
DECL|macro|OHCI_ROOT_OCI
mdefine_line|#define OHCI_ROOT_OCI&t;(1 &lt;&lt; 1)&t;/* Overcurrent Indicator */
DECL|macro|OHCI_ROOT_DRWE
mdefine_line|#define OHCI_ROOT_DRWE&t;(1 &lt;&lt; 15)&t;/* Device remote wakeup enable */
DECL|macro|OHCI_ROOT_LPSC
mdefine_line|#define OHCI_ROOT_LPSC&t;(1 &lt;&lt; 16)&t;/* turn on root hub ports power */
DECL|macro|OHCI_ROOT_OCIC
mdefine_line|#define OHCI_ROOT_OCIC&t;(1 &lt;&lt; 17)&t;/* Overcurrent indicator change */
DECL|macro|OHCI_ROOT_CRWE
mdefine_line|#define OHCI_ROOT_CRWE&t;(1 &lt;&lt; 31)&t;/* Clear RemoteWakeupEnable */
multiline_comment|/*&n; * Root hub A register masks&n; */
DECL|macro|OHCI_ROOT_A_NPS
mdefine_line|#define OHCI_ROOT_A_NPS&t;(1 &lt;&lt; 9)
DECL|macro|OHCI_ROOT_A_PSM
mdefine_line|#define OHCI_ROOT_A_PSM&t;(1 &lt;&lt; 8)
multiline_comment|/*&n; * Root hub B register masks&n; */
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
DECL|macro|OHCI_USB_PLE
mdefine_line|#define OHCI_USB_PLE&t;&t;(1 &lt;&lt; 2)  /* Periodic (interrupt) list enable */
DECL|macro|OHCI_USB_IE
mdefine_line|#define OHCI_USB_IE&t;&t;(1 &lt;&lt; 3)  /* Isochronous list enable */
DECL|macro|OHCI_USB_CLE
mdefine_line|#define OHCI_USB_CLE&t;&t;(1 &lt;&lt; 4)  /* Control list enable */
DECL|macro|OHCI_USB_BLE
mdefine_line|#define OHCI_USB_BLE&t;&t;(1 &lt;&lt; 5)  /* Bulk list enable */
multiline_comment|/*&n; * Command status register masks&n; */
DECL|macro|OHCI_CMDSTAT_HCR
mdefine_line|#define OHCI_CMDSTAT_HCR&t;(1)
DECL|macro|OHCI_CMDSTAT_CLF
mdefine_line|#define OHCI_CMDSTAT_CLF&t;(1 &lt;&lt; 1)
DECL|macro|OHCI_CMDSTAT_BLF
mdefine_line|#define OHCI_CMDSTAT_BLF&t;(1 &lt;&lt; 2)
DECL|macro|OHCI_CMDSTAT_OCR
mdefine_line|#define OHCI_CMDSTAT_OCR&t;(1 &lt;&lt; 3)
DECL|macro|OHCI_CMDSTAT_SOC
mdefine_line|#define OHCI_CMDSTAT_SOC&t;(3 &lt;&lt; 16)
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
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
DECL|member|root_hub
r_struct
id|ohci_device
op_star
id|root_hub
suffix:semicolon
multiline_comment|/* Root hub &amp; controller */
DECL|member|interrupt_list
r_struct
id|list_head
id|interrupt_list
suffix:semicolon
multiline_comment|/* List of interrupt active TDs for this OHCI */
)brace
suffix:semicolon
DECL|macro|OHCI_TIMER
mdefine_line|#define OHCI_TIMER&t;&t;/* enable the OHCI timer */
DECL|macro|OHCI_TIMER_FREQ
mdefine_line|#define OHCI_TIMER_FREQ&t;(234)&t;/* ms between each root hub status check */
DECL|macro|OHCI_RHSC_INT
macro_line|#undef OHCI_RHSC_INT&t;&t;/* Don&squot;t use root hub status interrupts! */
multiline_comment|/* Debugging code [ohci-debug.c] */
r_void
id|show_ohci_ed
c_func
(paren
r_struct
id|ohci_ed
op_star
id|ed
)paren
suffix:semicolon
r_void
id|show_ohci_td
c_func
(paren
r_struct
id|ohci_td
op_star
id|td
)paren
suffix:semicolon
r_void
id|show_ohci_td_chain
c_func
(paren
r_struct
id|ohci_td
op_star
id|td
)paren
suffix:semicolon
r_void
id|show_ohci_status
c_func
(paren
r_struct
id|ohci
op_star
id|ohci
)paren
suffix:semicolon
r_void
id|show_ohci_device
c_func
(paren
r_struct
id|ohci_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|show_ohci_hcca
c_func
(paren
r_struct
id|ohci_hcca
op_star
id|hcca
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* vim:sw=8&n; */
eof
