multiline_comment|/*&n; * linux/drivers/block/ns87415.c&t;Version 1.00  December 7, 1997&n; *&n; * Copyright (C) 1997-1998  Mark Lord&n; * Copyright (C) 1998       Eddie C. Dost  (ecd@skynet.be)&n; *&n; * Inspired by an earlier effort from David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|ns87415_count
DECL|variable|ns87415_control
r_static
r_int
r_int
id|ns87415_count
op_assign
l_int|0
comma
id|ns87415_control
(braket
id|MAX_HWIFS
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * This routine either enables/disables (according to drive-&gt;present)&n; * the IRQ associated with the port (HWIF(drive)),&n; * and selects either PIO or DMA handshaking for the next I/O operation.&n; */
DECL|function|ns87415_prepare_drive
r_static
r_void
id|ns87415_prepare_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
r_int
id|use_dma
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|bit
comma
id|other
comma
r_new
comma
op_star
id|old
op_assign
(paren
r_int
r_int
op_star
)paren
id|hwif-&gt;select_data
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
r_new
op_assign
op_star
id|old
suffix:semicolon
multiline_comment|/* Adjust IRQ enable bit */
id|bit
op_assign
l_int|1
op_lshift
(paren
l_int|8
op_plus
id|hwif-&gt;channel
)paren
suffix:semicolon
r_new
op_assign
id|drive-&gt;present
ques
c_cond
(paren
r_new
op_amp
op_complement
id|bit
)paren
suffix:colon
(paren
r_new
op_or
id|bit
)paren
suffix:semicolon
multiline_comment|/* Select PIO or DMA, DMA may only be selected for one drive/channel. */
id|bit
op_assign
l_int|1
op_lshift
(paren
l_int|20
op_plus
id|drive-&gt;select.b.unit
op_plus
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
id|other
op_assign
l_int|1
op_lshift
(paren
l_int|20
op_plus
(paren
l_int|1
op_minus
id|drive-&gt;select.b.unit
)paren
op_plus
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_new
op_assign
id|use_dma
ques
c_cond
(paren
(paren
r_new
op_amp
op_complement
id|other
)paren
op_or
id|bit
)paren
suffix:colon
(paren
r_new
op_amp
op_complement
id|bit
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_ne
op_star
id|old
)paren
(brace
op_star
id|old
op_assign
r_new
suffix:semicolon
(paren
r_void
)paren
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
r_new
)paren
suffix:semicolon
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
)brace
DECL|function|ns87415_selectproc
r_static
r_void
id|ns87415_selectproc
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ns87415_prepare_drive
(paren
id|drive
comma
id|drive-&gt;using_dma
)paren
suffix:semicolon
)brace
DECL|function|ns87415_dmaproc
r_static
r_int
id|ns87415_dmaproc
c_func
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|byte
id|dma_stat
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_end
suffix:colon
multiline_comment|/* returns 1 on error, 0 otherwise */
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
id|dma_stat
op_assign
id|inb
c_func
(paren
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
)paren
op_amp
op_complement
l_int|1
comma
id|hwif-&gt;dma_base
)paren
suffix:semicolon
multiline_comment|/* stop DMA */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|hwif-&gt;dma_base
)paren
op_or
l_int|6
comma
id|hwif-&gt;dma_base
)paren
suffix:semicolon
multiline_comment|/* from ERRATA: clear the INTR &amp; ERROR bits */
r_return
(paren
id|dma_stat
op_amp
l_int|7
)paren
op_ne
l_int|4
suffix:semicolon
multiline_comment|/* verify good DMA status */
r_case
id|ide_dma_write
suffix:colon
r_case
id|ide_dma_read
suffix:colon
id|ns87415_prepare_drive
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* select DMA xfer */
r_if
c_cond
(paren
op_logical_neg
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
)paren
multiline_comment|/* use standard DMA stuff */
r_return
l_int|0
suffix:semicolon
id|ns87415_prepare_drive
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* DMA failed: select PIO xfer */
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
multiline_comment|/* use standard DMA stuff */
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|ide_init_ns87415
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
r_int
id|ctrl
comma
id|using_inta
suffix:semicolon
id|byte
id|progif
suffix:semicolon
macro_line|#ifdef __sparc_v9__
r_int
id|timeout
suffix:semicolon
id|byte
id|stat
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set a good latency timer and cache line size value. */
(paren
r_void
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|64
)paren
suffix:semicolon
macro_line|#ifdef __sparc_v9__
(paren
r_void
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0x10
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * We cannot probe for IRQ: both ports share common IRQ on INTA.&n;&t; * Also, leave IRQ masked during drive probing, to prevent infinite&n;&t; * interrupts from a potentially floating INTA..&n;&t; *&n;&t; * IRQs get unmasked in selectproc when drive is first used.&n;&t; */
(paren
r_void
)paren
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|ctrl
)paren
suffix:semicolon
(paren
r_void
)paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x09
comma
op_amp
id|progif
)paren
suffix:semicolon
multiline_comment|/* is irq in &quot;native&quot; mode? */
id|using_inta
op_assign
id|progif
op_amp
(paren
l_int|1
op_lshift
(paren
id|hwif-&gt;channel
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|using_inta
)paren
id|using_inta
op_assign
id|ctrl
op_amp
(paren
l_int|1
op_lshift
(paren
l_int|4
op_plus
id|hwif-&gt;channel
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;mate
)paren
(brace
id|hwif-&gt;select_data
op_assign
id|hwif-&gt;mate-&gt;select_data
suffix:semicolon
)brace
r_else
(brace
id|hwif-&gt;select_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ns87415_control
(braket
id|ns87415_count
op_increment
)braket
suffix:semicolon
id|ctrl
op_or_assign
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* mask both IRQs */
r_if
c_cond
(paren
id|using_inta
)paren
id|ctrl
op_and_assign
op_complement
(paren
l_int|1
op_lshift
l_int|6
)paren
suffix:semicolon
multiline_comment|/* unmask INTA */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|hwif-&gt;select_data
)paren
op_assign
id|ctrl
suffix:semicolon
(paren
r_void
)paren
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|ctrl
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set prefetch size to 512 bytes for both ports,&n;&t;&t; * but don&squot;t turn on/off prefetching here.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x55
comma
l_int|0xee
)paren
suffix:semicolon
macro_line|#ifdef __sparc_v9__
multiline_comment|/*&n;&t;&t; * XXX: Reset the device, if we don&squot;t it will not respond&n;&t;&t; *      to SELECT_DRIVE() properly during first probe_hwif().&n;&t;&t; */
id|timeout
op_assign
l_int|10000
suffix:semicolon
id|outb
c_func
(paren
l_int|12
comma
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|8
comma
id|hwif-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|stat
op_assign
id|inb
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_STATUS_OFFSET
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_eq
l_int|0xff
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|stat
op_amp
id|BUSY_STAT
)paren
op_logical_and
op_decrement
id|timeout
)paren
suffix:semicolon
macro_line|#endif
)brace
id|outb
c_func
(paren
l_int|0x60
comma
id|hwif-&gt;dma_base
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|using_inta
)paren
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
multiline_comment|/* legacy mode */
r_else
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;irq
op_logical_and
id|hwif-&gt;mate
op_logical_and
id|hwif-&gt;mate-&gt;irq
)paren
id|hwif-&gt;irq
op_assign
id|hwif-&gt;mate-&gt;irq
suffix:semicolon
multiline_comment|/* share IRQ with mate */
id|hwif-&gt;dmaproc
op_assign
op_amp
id|ns87415_dmaproc
suffix:semicolon
id|hwif-&gt;selectproc
op_assign
op_amp
id|ns87415_selectproc
suffix:semicolon
)brace
eof
