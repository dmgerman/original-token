multiline_comment|/*&n; * Support for IDE interfaces on PowerMacs.&n; * These IDE interfaces are memory-mapped and have a DBDMA channel&n; * for doing DMA.&n; *&n; *  Copyright (C) 1998 Paul Mackerras.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; * Some code taken from drivers/block/ide-dma.c:&n; *&n; *  Copyright (c) 1995-1998  Mark Lord&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dbdma.h&gt;
macro_line|#include &lt;asm/ide.h&gt;
macro_line|#include &lt;asm/mediabay.h&gt;
macro_line|#include &lt;asm/feature.h&gt;
macro_line|#ifdef CONFIG_PMAC_PBOOK
macro_line|#include &lt;asm/adb.h&gt;
macro_line|#include &lt;asm/pmu.h&gt;
macro_line|#endif
macro_line|#include &quot;ide_modes.h&quot;
DECL|variable|pmac_ide_ports_known
r_int
id|pmac_ide_ports_known
suffix:semicolon
DECL|variable|pmac_ide_regbase
id|ide_ioreg_t
id|pmac_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|pmac_ide_irq
r_int
id|pmac_ide_irq
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|pmac_ide_count
r_int
id|pmac_ide_count
suffix:semicolon
DECL|variable|pmac_ide_node
r_struct
id|device_node
op_star
id|pmac_ide_node
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA_PMAC
DECL|macro|MAX_DCMDS
mdefine_line|#define MAX_DCMDS&t;256&t;/* allow up to 256 DBDMA commands per xfer */
r_static
r_void
id|pmac_ide_setup_dma
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
id|ide_hwif_t
op_star
id|hwif
)paren
suffix:semicolon
r_static
r_int
id|pmac_ide_dmaproc
c_func
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
r_static
r_int
id|pmac_ide_build_dmatable
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|wr
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA_PMAC */
macro_line|#ifdef CONFIG_PMAC_PBOOK
r_static
r_int
id|idepmac_notify
c_func
(paren
r_struct
id|notifier_block
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|variable|idepmac_sleep_notifier
r_struct
id|notifier_block
id|idepmac_sleep_notifier
op_assign
(brace
id|idepmac_notify
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_PBOOK */
multiline_comment|/*&n; * N.B. this can&squot;t be an initfunc, because the media-bay task can&n; * call ide_[un]register at any time.&n; */
DECL|function|pmac_ide_init_hwif_ports
r_void
id|pmac_ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
r_int
id|i
comma
id|ix
suffix:semicolon
r_if
c_cond
(paren
id|data_port
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|ix
op_assign
l_int|0
suffix:semicolon
id|ix
OL
id|MAX_HWIFS
suffix:semicolon
op_increment
id|ix
)paren
r_if
c_cond
(paren
id|data_port
op_eq
id|pmac_ide_regbase
(braket
id|ix
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ix
op_ge
id|MAX_HWIFS
)paren
(brace
multiline_comment|/* Probably a PCI interface... */
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
op_increment
id|i
)paren
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|data_port
op_plus
id|i
op_minus
id|IDE_DATA_OFFSET
suffix:semicolon
multiline_comment|/* XXX is this right? */
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
l_int|0
)paren
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* we check only for -EINVAL meaning that we have found a matching&n;&t;   bay but with the wrong device type */
id|i
op_assign
id|check_media_bay_by_base
c_func
(paren
id|data_port
comma
id|MB_CD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
op_minus
id|EINVAL
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
r_return
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
l_int|8
suffix:semicolon
op_increment
id|i
)paren
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|data_port
op_plus
id|i
op_star
l_int|0x10
suffix:semicolon
id|hw-&gt;io_ports
(braket
l_int|8
)braket
op_assign
id|data_port
op_plus
l_int|0x160
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
op_star
id|irq
op_assign
id|pmac_ide_irq
(braket
id|ix
)braket
suffix:semicolon
)brace
DECL|function|pmac_ide_tuneproc
r_void
id|pmac_ide_tuneproc
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
id|ide_pio_data_t
id|d
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
r_return
suffix:semicolon
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|4
comma
op_amp
id|d
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|4
suffix:colon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|IDE_DATA_REG
op_plus
l_int|0x200
op_plus
id|_IO_BASE
)paren
comma
l_int|0x211025
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|out_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|IDE_DATA_REG
op_plus
l_int|0x200
op_plus
id|_IO_BASE
)paren
comma
l_int|0x2f8526
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|pmac_ide_probe
c_func
(paren
r_void
)paren
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|device_node
op_star
id|atas
suffix:semicolon
r_struct
id|device_node
op_star
id|p
comma
op_star
op_star
id|pp
comma
op_star
id|removables
comma
op_star
op_star
id|rp
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
r_return
suffix:semicolon
id|pp
op_assign
op_amp
id|atas
suffix:semicolon
id|rp
op_assign
op_amp
id|removables
suffix:semicolon
id|p
op_assign
id|find_devices
c_func
(paren
l_string|&quot;ATA&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
id|p
op_assign
id|find_devices
c_func
(paren
l_string|&quot;IDE&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
id|p
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;ide&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
id|p
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;ata&quot;
)paren
suffix:semicolon
multiline_comment|/* Move removable devices such as the media-bay CDROM&n;&t;   on the PB3400 to the end of the list. */
r_for
c_loop
(paren
suffix:semicolon
id|p
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;parent
op_logical_and
id|p-&gt;parent-&gt;type
op_logical_and
id|strcasecmp
c_func
(paren
id|p-&gt;parent-&gt;type
comma
l_string|&quot;media-bay&quot;
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|rp
op_assign
id|p
suffix:semicolon
id|rp
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
r_else
(brace
op_star
id|pp
op_assign
id|p
suffix:semicolon
id|pp
op_assign
op_amp
id|p-&gt;next
suffix:semicolon
)brace
)brace
op_star
id|rp
op_assign
l_int|NULL
suffix:semicolon
op_star
id|pp
op_assign
id|removables
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|np
op_assign
id|atas
suffix:semicolon
id|i
OL
id|MAX_HWIFS
op_logical_and
id|np
op_ne
l_int|NULL
suffix:semicolon
id|np
op_assign
id|np-&gt;next
)paren
(brace
r_struct
id|device_node
op_star
id|tp
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this node is not under a mac-io or dbdma node,&n;&t;&t; * leave it to the generic PCI driver.&n;&t;&t; */
r_for
c_loop
(paren
id|tp
op_assign
id|np-&gt;parent
suffix:semicolon
id|tp
op_ne
l_int|0
suffix:semicolon
id|tp
op_assign
id|tp-&gt;parent
)paren
r_if
c_cond
(paren
id|tp-&gt;type
op_logical_and
(paren
id|strcmp
c_func
(paren
id|tp-&gt;type
comma
l_string|&quot;mac-io&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|tp-&gt;type
comma
l_string|&quot;dbdma&quot;
)paren
op_eq
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tp
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;n_addrs
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ide: no address for device %s&bslash;n&quot;
comma
id|np-&gt;full_name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If this slot is taken (e.g. by ide-pci.c) try the next one.&n;&t;&t; */
r_while
c_loop
(paren
id|i
OL
id|MAX_HWIFS
op_logical_and
id|ide_hwifs
(braket
id|i
)braket
dot
id|io_ports
(braket
id|IDE_DATA_OFFSET
)braket
op_ne
l_int|0
)paren
op_increment
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|MAX_HWIFS
)paren
r_break
suffix:semicolon
id|base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x200
)paren
op_minus
id|_IO_BASE
suffix:semicolon
multiline_comment|/* XXX This is bogus. Should be fixed in the registry by checking&n;&t;&t;   the kind of host interrupt controller, a bit like gatwick&n;&t;&t;   fixes in irq.c&n;&t;&t; */
r_if
c_cond
(paren
id|np-&gt;n_intrs
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide: no intrs for device %s, using 13&bslash;n&quot;
comma
id|np-&gt;full_name
)paren
suffix:semicolon
id|irq
op_assign
l_int|13
suffix:semicolon
)brace
r_else
(brace
id|irq
op_assign
id|np-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
)brace
id|pmac_ide_regbase
(braket
id|i
)braket
op_assign
id|base
suffix:semicolon
id|pmac_ide_irq
(braket
id|i
)braket
op_assign
id|irq
suffix:semicolon
id|pmac_ide_node
(braket
id|i
)braket
op_assign
id|np
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;parent
op_logical_and
id|np-&gt;parent-&gt;name
op_logical_and
id|strcasecmp
c_func
(paren
id|np-&gt;parent-&gt;name
comma
l_string|&quot;media-bay&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|media_bay_set_ide_infos
c_func
(paren
id|np-&gt;parent
comma
id|base
comma
id|irq
comma
id|i
)paren
suffix:semicolon
)brace
r_else
id|feature_set
c_func
(paren
id|np
comma
id|FEATURE_IDE_enable
)paren
suffix:semicolon
id|hwif
op_assign
op_amp
id|ide_hwifs
(braket
id|i
)braket
suffix:semicolon
id|pmac_ide_init_hwif_ports
c_func
(paren
op_amp
id|hwif-&gt;hw
comma
id|base
comma
l_int|0
comma
op_amp
id|hwif-&gt;irq
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|hwif-&gt;io_ports
comma
id|hwif-&gt;hw.io_ports
comma
r_sizeof
(paren
id|hwif-&gt;io_ports
)paren
)paren
suffix:semicolon
id|hwif-&gt;chipset
op_assign
id|ide_generic
suffix:semicolon
id|hwif-&gt;noprobe
op_assign
op_logical_neg
id|hwif-&gt;io_ports
(braket
id|IDE_DATA_OFFSET
)braket
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
id|pmac_ide_tuneproc
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA_PMAC
r_if
c_cond
(paren
id|np-&gt;n_addrs
op_ge
l_int|2
)paren
(brace
multiline_comment|/* has a DBDMA controller channel */
id|pmac_ide_setup_dma
c_func
(paren
id|np
comma
id|hwif
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA_PMAC */
op_increment
id|i
suffix:semicolon
)brace
id|pmac_ide_count
op_assign
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
id|notifier_chain_register
c_func
(paren
op_amp
id|sleep_notifier_list
comma
op_amp
id|idepmac_sleep_notifier
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PMAC_PBOOK */
)brace
macro_line|#ifdef CONFIG_BLK_DEV_IDEDMA_PMAC
r_static
r_void
id|__init
DECL|function|pmac_ide_setup_dma
id|pmac_ide_setup_dma
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;dma_base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
l_int|1
)braket
dot
id|address
comma
l_int|0x200
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate space for the DBDMA commands.&n;&t; * The +2 is +1 for the stop command and +1 to allow for&n;&t; * aligning the start address to a multiple of 16 bytes.&n;&t; */
id|hwif-&gt;dmatable
op_assign
(paren
r_int
r_int
op_star
)paren
id|kmalloc
c_func
(paren
(paren
id|MAX_DCMDS
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_struct
id|dbdma_cmd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;dmatable
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to allocate DMA command list&bslash;n&quot;
comma
id|hwif-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|hwif-&gt;dmaproc
op_assign
op_amp
id|pmac_ide_dmaproc
suffix:semicolon
macro_line|#ifdef CONFIG_IDEDMA_PMAC_AUTO
id|hwif-&gt;autodma
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_IDEDMA_PMAC_AUTO */
)brace
multiline_comment|/*&n; * pmac_ide_build_dmatable builds the DBDMA command list&n; * for a transfer and sets the DBDMA channel to point to it.&n; */
r_static
r_int
DECL|function|pmac_ide_build_dmatable
id|pmac_ide_build_dmatable
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|wr
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
r_struct
id|dbdma_cmd
op_star
id|table
comma
op_star
id|tstart
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
id|rq-&gt;bh
suffix:semicolon
r_int
r_int
id|size
comma
id|addr
suffix:semicolon
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
op_assign
(paren
r_volatile
r_struct
id|dbdma_regs
op_star
)paren
id|hwif-&gt;dma_base
suffix:semicolon
id|table
op_assign
id|tstart
op_assign
(paren
r_struct
id|dbdma_cmd
op_star
)paren
id|DBDMA_ALIGN
c_func
(paren
id|hwif-&gt;dmatable
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
id|RUN
op_or
id|PAUSE
op_or
id|FLUSH
op_or
id|WAKE
op_or
id|DEAD
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/*&n;&t;&t; * Determine addr and size of next buffer area.  We assume that&n;&t;&t; * individual virtual buffers are always composed linearly in&n;&t;&t; * physical memory.  For example, we assume that any 8kB buffer&n;&t;&t; * is always composed of two adjacent physical 4kB pages rather&n;&t;&t; * than two possibly non-adjacent physical 4kB pages.&n;&t;&t; */
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* paging requests have (rq-&gt;bh == NULL) */
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|rq-&gt;buffer
)paren
suffix:semicolon
id|size
op_assign
id|rq-&gt;nr_sectors
op_lshift
l_int|9
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* group sequential buffers into one large buffer */
id|addr
op_assign
id|virt_to_bus
c_func
(paren
id|bh-&gt;b_data
)paren
suffix:semicolon
id|size
op_assign
id|bh-&gt;b_size
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bh
op_assign
id|bh-&gt;b_reqnext
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
op_plus
id|size
)paren
op_ne
id|virt_to_bus
c_func
(paren
id|bh-&gt;b_data
)paren
)paren
r_break
suffix:semicolon
id|size
op_add_assign
id|bh-&gt;b_size
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Fill in the next DBDMA command block.&n;&t;&t; * Note that one DBDMA command can transfer&n;&t;&t; * at most 65535 bytes.&n;&t;&t; */
r_while
c_loop
(paren
id|size
)paren
(brace
r_int
r_int
id|tc
op_assign
(paren
id|size
OL
l_int|0xfe00
)paren
ques
c_cond
id|size
suffix:colon
l_int|0xfe00
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
op_ge
id|MAX_DCMDS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMA table too small&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* revert to PIO for this request */
)brace
id|st_le16
c_func
(paren
op_amp
id|table-&gt;command
comma
id|wr
ques
c_cond
id|OUTPUT_MORE
suffix:colon
id|INPUT_MORE
)paren
suffix:semicolon
id|st_le16
c_func
(paren
op_amp
id|table-&gt;req_count
comma
id|tc
)paren
suffix:semicolon
id|st_le32
c_func
(paren
op_amp
id|table-&gt;phy_addr
comma
id|addr
)paren
suffix:semicolon
id|table-&gt;cmd_dep
op_assign
l_int|0
suffix:semicolon
id|table-&gt;xfer_status
op_assign
l_int|0
suffix:semicolon
id|table-&gt;res_count
op_assign
l_int|0
suffix:semicolon
id|addr
op_add_assign
id|tc
suffix:semicolon
id|size
op_sub_assign
id|tc
suffix:semicolon
op_increment
id|table
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|bh
op_ne
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* convert the last command to an input/output last command */
r_if
c_cond
(paren
id|count
)paren
id|st_le16
c_func
(paren
op_amp
id|table
(braket
op_minus
l_int|1
)braket
dot
id|command
comma
id|wr
ques
c_cond
id|OUTPUT_LAST
suffix:colon
id|INPUT_LAST
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: empty DMA table?&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
multiline_comment|/* add the stop command to the end of the list */
id|memset
c_func
(paren
id|table
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dbdma_cmd
)paren
)paren
suffix:semicolon
id|out_le16
c_func
(paren
op_amp
id|table-&gt;command
comma
id|DBDMA_STOP
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|dma-&gt;cmdptr
comma
id|virt_to_bus
c_func
(paren
id|tstart
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pmac_ide_dmaproc
r_int
id|pmac_ide_dmaproc
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
r_volatile
r_struct
id|dbdma_regs
op_star
id|dma
op_assign
(paren
r_volatile
r_struct
id|dbdma_regs
op_star
)paren
id|hwif-&gt;dma_base
suffix:semicolon
r_int
id|dstat
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_on
suffix:colon
multiline_comment|/* ide-floppy DMA doesn&squot;t work yet... */
id|drive-&gt;using_dma
op_assign
id|drive-&gt;media
op_ne
id|ide_floppy
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_dma_off
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: DMA disabled&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_case
id|ide_dma_off_quietly
suffix:colon
id|drive-&gt;using_dma
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_dma_check
suffix:colon
multiline_comment|/* ide-floppy DMA doesn&squot;t work yet... */
id|drive-&gt;using_dma
op_assign
id|hwif-&gt;autodma
op_logical_and
id|drive-&gt;media
op_ne
id|ide_floppy
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_dma_read
suffix:colon
r_case
id|ide_dma_write
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|pmac_ide_build_dmatable
c_func
(paren
id|drive
comma
id|func
op_eq
id|ide_dma_write
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|drive-&gt;waiting_for_dma
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
)paren
r_return
l_int|0
suffix:semicolon
id|ide_set_handler
c_func
(paren
id|drive
comma
op_amp
id|ide_dma_intr
comma
id|WAIT_CMD
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|func
op_eq
id|ide_dma_write
ques
c_cond
id|WIN_WRITEDMA
suffix:colon
id|WIN_READDMA
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_case
id|ide_dma_begin
suffix:colon
id|out_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
id|RUN
op_lshift
l_int|16
)paren
op_or
id|RUN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ide_dma_end
suffix:colon
id|drive-&gt;waiting_for_dma
op_assign
l_int|0
suffix:semicolon
id|dstat
op_assign
id|in_le32
c_func
(paren
op_amp
id|dma-&gt;status
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|dma-&gt;control
comma
(paren
(paren
id|RUN
op_or
id|WAKE
op_or
id|DEAD
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
multiline_comment|/* verify good dma status */
r_return
(paren
id|dstat
op_amp
(paren
id|RUN
op_or
id|DEAD
op_or
id|ACTIVE
)paren
)paren
op_ne
id|RUN
suffix:semicolon
r_case
id|ide_dma_test_irq
suffix:colon
r_return
(paren
id|in_le32
c_func
(paren
op_amp
id|dma-&gt;status
)paren
op_amp
(paren
id|RUN
op_or
id|ACTIVE
)paren
)paren
op_eq
id|RUN
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmac_ide_dmaproc: bad func %d&bslash;n&quot;
comma
id|func
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_IDEDMA_PMAC */
macro_line|#ifdef CONFIG_PMAC_PBOOK
DECL|function|idepmac_notify
r_static
r_int
id|idepmac_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|p
)paren
(brace
r_int
id|i
comma
id|timeout
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|PBOOK_SLEEP
suffix:colon
multiline_comment|/* do anything here?? */
r_break
suffix:semicolon
r_case
id|PBOOK_WAKE
suffix:colon
multiline_comment|/* wait for the controller(s) to become ready */
id|timeout
op_assign
l_int|5000
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
id|pmac_ide_count
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
r_int
id|base
op_assign
id|pmac_ide_regbase
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|check_media_bay_by_base
c_func
(paren
id|base
comma
id|MB_CD
)paren
op_eq
op_minus
id|EINVAL
)paren
r_continue
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|base
op_plus
l_int|0x70
)paren
op_amp
id|BUSY_STAT
)paren
op_logical_and
id|timeout
)paren
(brace
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
op_decrement
id|timeout
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PMAC_PBOOK */
eof
