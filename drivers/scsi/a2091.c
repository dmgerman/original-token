macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;wd33c93.h&quot;
macro_line|#include &quot;a2091.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|variable|proc_scsi_a2091
r_struct
id|proc_dir_entry
id|proc_scsi_a2091
op_assign
(brace
id|PROC_SCSI_A2091
comma
l_int|5
comma
l_string|&quot;A2091&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
)brace
suffix:semicolon
DECL|macro|DMA
mdefine_line|#define DMA(ptr) ((a2091_scsiregs *)((ptr)-&gt;base))
DECL|macro|HDATA
mdefine_line|#define HDATA(ptr) ((struct WD33C93_hostdata *)((ptr)-&gt;hostdata))
DECL|variable|first_instance
r_static
r_struct
id|Scsi_Host
op_star
id|first_instance
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|a2091_template
r_static
id|Scsi_Host_Template
op_star
id|a2091_template
suffix:semicolon
DECL|function|a2091_intr
r_static
r_void
id|a2091_intr
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
r_int
r_int
id|status
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
r_for
c_loop
(paren
id|instance
op_assign
id|first_instance
suffix:semicolon
id|instance
op_logical_and
id|instance-&gt;hostt
op_eq
id|a2091_template
suffix:semicolon
id|instance
op_assign
id|instance-&gt;next
)paren
(brace
id|status
op_assign
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|ISTR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|ISTR_INT_F
op_or
id|ISTR_INT_P
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|ISTR_INTS
)paren
(brace
multiline_comment|/* disable PORTS interrupt */
id|custom.intena
op_assign
id|IF_PORTS
suffix:semicolon
id|wd33c93_intr
(paren
id|instance
)paren
suffix:semicolon
multiline_comment|/* enable PORTS interrupt */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_PORTS
suffix:semicolon
)brace
)brace
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
r_int
id|cntr
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|VTOP
c_func
(paren
id|cmd-&gt;SCp.ptr
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
op_assign
id|cmd-&gt;host
suffix:semicolon
multiline_comment|/* don&squot;t allow DMA if the physical address is bad */
r_if
c_cond
(paren
id|addr
op_amp
id|A2091_XFER_MASK
op_logical_or
(paren
op_logical_neg
id|dir_in
op_logical_and
id|mm_end_of_chunk
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
)paren
)paren
(brace
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
(paren
id|cmd-&gt;SCp.this_residual
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|0x1ff
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
id|scsi_malloc
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
)paren
suffix:semicolon
multiline_comment|/* can&squot;t allocate memory; use PIO */
r_if
c_cond
(paren
op_logical_neg
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
(brace
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* get the physical address of the bounce buffer */
id|addr
op_assign
id|VTOP
c_func
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
suffix:semicolon
multiline_comment|/* the bounce buffer may not be in the first 16M of physmem */
r_if
c_cond
(paren
id|addr
op_amp
id|A2091_XFER_MASK
)paren
(brace
multiline_comment|/* we could use chipmem... maybe later */
id|scsi_free
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
)paren
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
l_int|NULL
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dir_in
)paren
(brace
multiline_comment|/* copy to bounce buffer for a write */
r_if
c_cond
(paren
id|cmd-&gt;use_sg
)paren
macro_line|#if 0
id|panic
(paren
l_string|&quot;scsi%ddma: incomplete s/g support&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
macro_line|#else
id|memcpy
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|cmd-&gt;SCp.ptr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
macro_line|#endif
r_else
id|memcpy
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|cmd-&gt;request_buffer
comma
id|cmd-&gt;request_bufflen
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* setup dma direction */
r_if
c_cond
(paren
op_logical_neg
id|dir_in
)paren
id|cntr
op_or_assign
id|CNTR_DDIR
suffix:semicolon
multiline_comment|/* remember direction */
id|HDATA
c_func
(paren
id|cmd-&gt;host
)paren
op_member_access_from_pointer
id|dma_dir
op_assign
id|dir_in
suffix:semicolon
id|DMA
c_func
(paren
id|cmd-&gt;host
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|cntr
suffix:semicolon
multiline_comment|/* setup DMA *physical* address */
id|DMA
c_func
(paren
id|cmd-&gt;host
)paren
op_member_access_from_pointer
id|ACR
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|dir_in
)paren
(brace
multiline_comment|/* invalidate any cache */
id|cache_clear
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* push any dirty cache */
id|cache_push
(paren
id|addr
comma
id|cmd-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
multiline_comment|/* start DMA */
id|DMA
c_func
(paren
id|cmd-&gt;host
)paren
op_member_access_from_pointer
id|ST_DMA
op_assign
l_int|1
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
multiline_comment|/* disable SCSI interrupts */
r_int
r_int
id|cntr
op_assign
id|CNTR_PDMD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
)paren
id|cntr
op_or_assign
id|CNTR_DDIR
suffix:semicolon
multiline_comment|/* disable SCSI interrupts */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|cntr
suffix:semicolon
multiline_comment|/* flush if we were reading */
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
)paren
(brace
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|FLUSH
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|ISTR
op_amp
id|ISTR_FE_FLG
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* clear a possible interrupt */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CINT
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* stop DMA */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|SP_DMA
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* restore the CONTROL bits (minus the direction flag) */
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
multiline_comment|/* copy from a bounce buffer, if necessary */
r_if
c_cond
(paren
id|status
op_logical_and
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
)paren
(brace
r_if
c_cond
(paren
id|SCpnt
op_logical_and
id|SCpnt-&gt;use_sg
)paren
(brace
macro_line|#if 0
id|panic
(paren
l_string|&quot;scsi%d: incomplete s/g support&quot;
comma
id|instance-&gt;host_no
)paren
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
)paren
(brace
id|memcpy
(paren
id|SCpnt-&gt;SCp.ptr
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|SCpnt-&gt;SCp.this_residual
)paren
suffix:semicolon
)brace
id|scsi_free
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
)paren
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
l_int|NULL
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_dir
op_logical_and
id|SCpnt
)paren
id|memcpy
(paren
id|SCpnt-&gt;request_buffer
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|SCpnt-&gt;request_bufflen
)paren
suffix:semicolon
id|scsi_free
(paren
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
comma
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
)paren
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_buffer
op_assign
l_int|NULL
suffix:semicolon
id|HDATA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|dma_bounce_len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|variable|num_a2091
r_static
r_int
id|num_a2091
op_assign
l_int|0
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|a2091_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
)paren
(brace
r_static
r_int
r_char
id|called
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|instance
suffix:semicolon
id|caddr_t
id|address
suffix:semicolon
r_int
id|key
suffix:semicolon
r_struct
id|ConfigDev
op_star
id|cd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
id|called
)paren
r_return
l_int|0
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
id|tpnt-&gt;proc_dir
op_assign
op_amp
id|proc_scsi_a2091
suffix:semicolon
id|tpnt-&gt;proc_info
op_assign
op_amp
id|wd33c93_proc_info
suffix:semicolon
r_while
c_loop
(paren
(paren
id|key
op_assign
id|zorro_find
c_func
(paren
id|MANUF_COMMODORE
comma
id|PROD_A2091
comma
l_int|0
comma
l_int|0
)paren
)paren
op_logical_or
(paren
id|key
op_assign
id|zorro_find
c_func
(paren
id|MANUF_COMMODORE
comma
id|PROD_A590
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
id|cd
op_assign
id|zorro_get_board
c_func
(paren
id|key
)paren
suffix:semicolon
id|address
op_assign
id|cd-&gt;cd_BoardAddr
suffix:semicolon
id|instance
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
id|instance-&gt;base
op_assign
(paren
r_int
r_char
op_star
)paren
id|ZTWO_VADDR
c_func
(paren
id|address
)paren
suffix:semicolon
id|instance-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
id|instance-&gt;unique_id
op_assign
id|key
suffix:semicolon
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|DAWR
op_assign
id|DAWR_A2091
suffix:semicolon
id|wd33c93_init
c_func
(paren
id|instance
comma
(paren
id|wd33c93_regs
op_star
)paren
op_amp
(paren
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|SASR
)paren
comma
id|dma_setup
comma
id|dma_stop
comma
id|WD33C93_FS_8_10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_a2091
op_increment
op_eq
l_int|0
)paren
(brace
id|first_instance
op_assign
id|instance
suffix:semicolon
id|a2091_template
op_assign
id|instance-&gt;hostt
suffix:semicolon
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a2091_intr
comma
l_int|0
comma
l_string|&quot;A2091 SCSI&quot;
comma
id|a2091_intr
)paren
suffix:semicolon
)brace
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
id|CNTR_PDMD
op_or
id|CNTR_INTEN
suffix:semicolon
id|zorro_config_board
c_func
(paren
id|key
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|num_a2091
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
macro_line|#include &quot;a2091.h&quot;
DECL|variable|driver_template
id|Scsi_Host_Template
id|driver_template
op_assign
id|A2091_SCSI
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
macro_line|#endif
DECL|function|a2091_release
r_int
id|a2091_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
(brace
macro_line|#ifdef MODULE
id|DMA
c_func
(paren
id|instance
)paren
op_member_access_from_pointer
id|CNTR
op_assign
l_int|0
suffix:semicolon
id|zorro_unconfig_board
c_func
(paren
id|instance-&gt;unique_id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|num_a2091
op_eq
l_int|0
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|a2091_intr
)paren
suffix:semicolon
id|wd33c93_release
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
eof
