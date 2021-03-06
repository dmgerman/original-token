macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mvme147hw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;wd33c93.h&quot;
macro_line|#include &quot;mvme147.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|macro|HDATA
mdefine_line|#define HDATA(ptr) ((struct WD33C93_hostdata *)((ptr)-&gt;hostdata))
DECL|variable|mvme147_host
r_static
r_struct
id|Scsi_Host
op_star
id|mvme147_host
op_assign
l_int|NULL
suffix:semicolon
DECL|function|mvme147_intr
r_static
r_void
id|mvme147_intr
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
id|MVME147_IRQ_SCSI_PORT
)paren
id|wd33c93_intr
(paren
id|mvme147_host
)paren
suffix:semicolon
r_else
id|m147_pcc-&gt;dma_intr
op_assign
l_int|0x89
suffix:semicolon
multiline_comment|/* Ack and enable ints */
)brace
DECL|function|dma_setup
r_static
r_int
id|dma_setup
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|dir_in
)paren
(brace
r_int
r_char
id|flags
op_assign
l_int|0x01
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|cmd-&gt;SCp.ptr
)paren
suffix:semicolon
multiline_comment|/* setup dma direction */
r_if
c_cond
(paren
op_logical_neg
id|dir_in
)paren
id|flags
op_or_assign
l_int|0x04
suffix:semicolon
multiline_comment|/* remember direction */
id|HDATA
c_func
(paren
id|mvme147_host
)paren
op_member_access_from_pointer
id|dma_dir
op_assign
id|dir_in
suffix:semicolon
r_if
c_cond
(paren
id|dir_in
)paren
multiline_comment|/* invalidate any cache */
id|cache_clear
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
r_else
multiline_comment|/* push any dirty cache */
id|cache_push
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
multiline_comment|/* start DMA */
id|m147_pcc-&gt;dma_bcr
op_assign
id|cmd-&gt;SCp.this_residual
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
suffix:semicolon
id|m147_pcc-&gt;dma_dadr
op_assign
id|addr
suffix:semicolon
id|m147_pcc-&gt;dma_cntrl
op_assign
id|flags
suffix:semicolon
multiline_comment|/* return success */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_stop
r_static
r_void
id|dma_stop
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|status
)paren
(brace
id|m147_pcc-&gt;dma_cntrl
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|mvme147_detect
r_int
id|mvme147_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
r_char
id|called
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MVME147
op_logical_or
id|called
)paren
r_return
l_int|0
suffix:semicolon
id|called
op_increment
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;MVME147&quot;
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|wd33c93_proc_info
suffix:semicolon
id|mvme147_host
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
r_struct
id|WD33C93_hostdata
)paren
)paren
suffix:semicolon
id|mvme147_host-&gt;base
op_assign
l_int|0xfffe4000
suffix:semicolon
id|mvme147_host-&gt;irq
op_assign
id|MVME147_IRQ_SCSI_PORT
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|mvme147_host
comma
(paren
id|wd33c93_regs
op_star
)paren
l_int|0xfffe4000
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_8_10
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|MVME147_IRQ_SCSI_PORT
comma
id|mvme147_intr
comma
l_int|0
comma
l_string|&quot;MVME147 SCSI PORT&quot;
comma
id|mvme147_intr
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|MVME147_IRQ_SCSI_DMA
comma
id|mvme147_intr
comma
l_int|0
comma
l_string|&quot;MVME147 SCSI DMA&quot;
comma
id|mvme147_intr
)paren
suffix:semicolon
macro_line|#if 0&t;/* Disabled; causes problems booting */
id|m147_pcc-&gt;scsi_interrupt
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* Assert SCSI bus reset */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|m147_pcc-&gt;scsi_interrupt
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Negate SCSI bus reset */
id|udelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|m147_pcc-&gt;scsi_interrupt
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* Clear bus reset interrupt */
macro_line|#endif
id|m147_pcc-&gt;scsi_interrupt
op_assign
l_int|0x09
suffix:semicolon
multiline_comment|/* Enable interrupt */
id|m147_pcc-&gt;dma_cntrl
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* ensure DMA is stopped */
id|m147_pcc-&gt;dma_intr
op_assign
l_int|0x89
suffix:semicolon
multiline_comment|/* Ack and enable ints */
r_return
l_int|1
suffix:semicolon
)brace
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
macro_line|#include &quot;mvme147.h&quot;
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
id|MVME147_SCSI
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
DECL|function|mvme147_release
r_int
id|mvme147_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
macro_line|#ifdef MODULE
multiline_comment|/* XXX Make sure DMA is stopped! */
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|MVME147_IRQ_SCSI_PORT
comma
id|mvme147_intr
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|MVME147_IRQ_SCSI_DMA
comma
id|mvme147_intr
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
eof
