multiline_comment|/*&n; * linux/drivers/block/hpt366.c&t;&t;Version 0.15&t;Dec. 22, 1999&n; *&n; * Copyright (C) 1999&t;&t;&t;Andre Hedrick &lt;andre@suse.com&gt;&n; * May be copied or modified under the terms of the GNU General Public License&n; *&n; * Thanks to HighPoint Technologies for their assistance, and hardware.&n; * Special Thanks to Jon Burchmore in SanDiego for the deep pockets, his&n; * donation of an ABit BP6 mainboard, processor, and memory acellerated&n; * development and support.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
DECL|variable|bad_ata66_4
r_const
r_char
op_star
id|bad_ata66_4
(braket
)braket
op_assign
(brace
l_string|&quot;WDC AC310200R&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata66_3
r_const
r_char
op_star
id|bad_ata66_3
(braket
)braket
op_assign
(brace
l_string|&quot;WDC AC310200R&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|bad_ata33
r_const
r_char
op_star
id|bad_ata33
(braket
)braket
op_assign
(brace
l_string|&quot;Maxtor 92720U8&quot;
comma
l_string|&quot;Maxtor 92040U6&quot;
comma
l_string|&quot;Maxtor 91360U4&quot;
comma
l_string|&quot;Maxtor 91020U3&quot;
comma
l_string|&quot;Maxtor 90845U3&quot;
comma
l_string|&quot;Maxtor 90650U2&quot;
comma
l_string|&quot;Maxtor 91360D8&quot;
comma
l_string|&quot;Maxtor 91190D7&quot;
comma
l_string|&quot;Maxtor 91020D6&quot;
comma
l_string|&quot;Maxtor 90845D5&quot;
comma
l_string|&quot;Maxtor 90680D4&quot;
comma
l_string|&quot;Maxtor 90510D3&quot;
comma
l_string|&quot;Maxtor 90340D2&quot;
comma
l_string|&quot;Maxtor 91152D8&quot;
comma
l_string|&quot;Maxtor 91008D7&quot;
comma
l_string|&quot;Maxtor 90845D6&quot;
comma
l_string|&quot;Maxtor 90840D6&quot;
comma
l_string|&quot;Maxtor 90720D5&quot;
comma
l_string|&quot;Maxtor 90648D5&quot;
comma
l_string|&quot;Maxtor 90576D4&quot;
comma
l_string|&quot;Maxtor 90510D4&quot;
comma
l_string|&quot;Maxtor 90432D3&quot;
comma
l_string|&quot;Maxtor 90288D2&quot;
comma
l_string|&quot;Maxtor 90256D2&quot;
comma
l_string|&quot;Maxtor 91000D8&quot;
comma
l_string|&quot;Maxtor 90910D8&quot;
comma
l_string|&quot;Maxtor 90875D7&quot;
comma
l_string|&quot;Maxtor 90840D7&quot;
comma
l_string|&quot;Maxtor 90750D6&quot;
comma
l_string|&quot;Maxtor 90625D5&quot;
comma
l_string|&quot;Maxtor 90500D4&quot;
comma
l_string|&quot;Maxtor 91728D8&quot;
comma
l_string|&quot;Maxtor 91512D7&quot;
comma
l_string|&quot;Maxtor 91303D6&quot;
comma
l_string|&quot;Maxtor 91080D5&quot;
comma
l_string|&quot;Maxtor 90845D4&quot;
comma
l_string|&quot;Maxtor 90680D4&quot;
comma
l_string|&quot;Maxtor 90648D3&quot;
comma
l_string|&quot;Maxtor 90432D2&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|struct|chipset_bus_clock_list_entry
r_struct
id|chipset_bus_clock_list_entry
(brace
DECL|member|xfer_speed
id|byte
id|xfer_speed
suffix:semicolon
DECL|member|chipset_settings
r_int
r_int
id|chipset_settings
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|forty_base
r_struct
id|chipset_bus_clock_list_entry
id|forty_base
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x900fd943
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x900ad943
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x900bd943
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x9008d943
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x9008d943
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa008d943
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa010d955
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa010d9fc
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc008d963
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc010d974
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc010d997
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc010d9c7
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0xc018d9d9
)brace
comma
(brace
l_int|0
comma
l_int|0x0120d9d9
)brace
)brace
suffix:semicolon
DECL|variable|thirty_three_base
r_struct
id|chipset_bus_clock_list_entry
id|thirty_three_base
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x90c9a731
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x90cfa731
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x90caa731
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x90cba731
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x90c8a731
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa0c8a731
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa0c8a732
)brace
comma
multiline_comment|/* 0xa0c8a733 */
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa0c8a797
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc0c8a731
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc0c8a742
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc0d0a753
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc0d0a7a3
)brace
comma
multiline_comment|/* 0xc0d0a793 */
(brace
id|XFER_PIO_0
comma
l_int|0xc0d0a7aa
)brace
comma
multiline_comment|/* 0xc0d0a7a7 */
(brace
l_int|0
comma
l_int|0x0120a7a7
)brace
)brace
suffix:semicolon
DECL|variable|twenty_five_base
r_struct
id|chipset_bus_clock_list_entry
id|twenty_five_base
(braket
)braket
op_assign
(brace
(brace
id|XFER_UDMA_4
comma
l_int|0x90c98521
)brace
comma
(brace
id|XFER_UDMA_3
comma
l_int|0x90cf8521
)brace
comma
(brace
id|XFER_UDMA_2
comma
l_int|0x90cf8521
)brace
comma
(brace
id|XFER_UDMA_1
comma
l_int|0x90cb8521
)brace
comma
(brace
id|XFER_UDMA_0
comma
l_int|0x90cb8521
)brace
comma
(brace
id|XFER_MW_DMA_2
comma
l_int|0xa0ca8521
)brace
comma
(brace
id|XFER_MW_DMA_1
comma
l_int|0xa0ca8532
)brace
comma
(brace
id|XFER_MW_DMA_0
comma
l_int|0xa0ca8575
)brace
comma
(brace
id|XFER_PIO_4
comma
l_int|0xc0ca8521
)brace
comma
(brace
id|XFER_PIO_3
comma
l_int|0xc0ca8532
)brace
comma
(brace
id|XFER_PIO_2
comma
l_int|0xc0ca8542
)brace
comma
(brace
id|XFER_PIO_1
comma
l_int|0xc0d08572
)brace
comma
(brace
id|XFER_PIO_0
comma
l_int|0xc0d08585
)brace
comma
(brace
l_int|0
comma
l_int|0x01208585
)brace
)brace
suffix:semicolon
DECL|macro|HPT366_DEBUG_DRIVE_INFO
mdefine_line|#define HPT366_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|HPT366_ALLOW_ATA66_4
mdefine_line|#define HPT366_ALLOW_ATA66_4&t;&t;1
DECL|macro|HPT366_ALLOW_ATA66_3
mdefine_line|#define HPT366_ALLOW_ATA66_3&t;&t;1
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
DECL|variable|hpt363_shared_irq
id|byte
id|hpt363_shared_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|hpt363_shared_pin
id|byte
id|hpt363_shared_pin
op_assign
l_int|0
suffix:semicolon
DECL|function|check_in_drive_lists
r_static
r_int
id|check_in_drive_lists
(paren
id|ide_drive_t
op_star
id|drive
comma
r_const
r_char
op_star
op_star
id|list
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;check_in_drive_lists(%s, %p)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|list
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
op_star
id|list
op_increment
comma
id|id-&gt;model
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: Broken ASIC, BackSpeeding (U)DMA for %s&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|id-&gt;model
)paren
suffix:semicolon
macro_line|#endif /* DEBUG */
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_bus_clock_list
r_static
r_int
r_int
id|pci_bus_clock_list
(paren
id|byte
id|speed
comma
r_struct
id|chipset_bus_clock_list_entry
op_star
id|chipset_table
)paren
(brace
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;pci_bus_clock_list(speed=0x%02x, table=%p)&bslash;n&quot;
comma
id|speed
comma
id|chipset_table
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_for
c_loop
(paren
suffix:semicolon
id|chipset_table-&gt;xfer_speed
suffix:semicolon
id|chipset_table
op_increment
)paren
r_if
c_cond
(paren
id|chipset_table-&gt;xfer_speed
op_eq
id|speed
)paren
(brace
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;pci_bus_clock_list: found match: 0x%08x&bslash;n&quot;
comma
id|chipset_table-&gt;chipset_settings
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_return
id|chipset_table-&gt;chipset_settings
suffix:semicolon
)brace
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;pci_bus_clock_list: using default: 0x%08x&bslash;n&quot;
comma
l_int|0x01208585
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_return
l_int|0x01208585
suffix:semicolon
)brace
DECL|function|hpt366_tune_chipset
r_static
r_int
id|hpt366_tune_chipset
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|speed
)paren
(brace
r_int
id|err
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
r_int
id|drive_number
op_assign
(paren
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_plus
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
id|byte
id|regtime
op_assign
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|0x44
suffix:colon
l_int|0x40
suffix:semicolon
r_int
r_int
id|reg1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg2
op_assign
l_int|0
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;hpt366_tune_chipset(%s, speed=0x%02x)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|speed
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
id|pci_read_config_dword
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
id|regtime
comma
op_amp
id|reg1
)paren
suffix:semicolon
multiline_comment|/* detect bus speed by looking at control reg timing: */
r_switch
c_cond
(paren
(paren
id|reg1
op_rshift
l_int|8
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|5
suffix:colon
id|reg2
op_assign
id|pci_bus_clock_list
c_func
(paren
id|speed
comma
id|forty_base
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|reg2
op_assign
id|pci_bus_clock_list
c_func
(paren
id|speed
comma
id|twenty_five_base
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;hpt366: assuming 33Mhz PCI bus&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|7
suffix:colon
id|reg2
op_assign
id|pci_bus_clock_list
c_func
(paren
id|speed
comma
id|thirty_three_base
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable on-chip PIO FIFO/buffer (to avoid problems handling I/O errors later)&n;&t; */
id|reg2
op_and_assign
op_complement
l_int|0x80000000
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
id|regtime
comma
id|reg2
)paren
suffix:semicolon
id|err
op_assign
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: speed=0x%02x(%s), drive%d, old=0x%08x, new=0x%08x, err=0x%04x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|speed
comma
id|ide_xfer_verbose
c_func
(paren
id|speed
)paren
comma
id|drive_number
comma
id|reg1
comma
id|reg2
comma
id|err
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * This allows the configuration of ide_pci chipset registers&n; * for cards that learn about the drive&squot;s UDMA, DMA, PIO capabilities&n; * after the drive is reported by the OS.  Initally for designed for&n; * HPT366 UDMA chipset by HighPoint|Triones Technologies, Inc.&n; *&n; * check_in_drive_lists(drive, bad_ata66_4)&n; * check_in_drive_lists(drive, bad_ata66_3)&n; * check_in_drive_lists(drive, bad_ata33)&n; *&n; */
DECL|function|config_chipset_for_dma
r_static
r_int
id|config_chipset_for_dma
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
id|byte
id|speed
op_assign
l_int|0x00
suffix:semicolon
id|byte
id|reg51h
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg40
op_assign
l_int|0
suffix:semicolon
r_int
id|rval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0010
)paren
op_logical_and
(paren
op_logical_neg
id|check_in_drive_lists
c_func
(paren
id|drive
comma
id|bad_ata66_4
)paren
)paren
op_logical_and
(paren
id|HPT366_ALLOW_ATA66_4
)paren
op_logical_and
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|udma_four
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_4
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0008
)paren
op_logical_and
(paren
op_logical_neg
id|check_in_drive_lists
c_func
(paren
id|drive
comma
id|bad_ata66_3
)paren
)paren
op_logical_and
(paren
id|HPT366_ALLOW_ATA66_3
)paren
op_logical_and
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|udma_four
)paren
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_3
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_logical_and
(paren
op_logical_neg
id|check_in_drive_lists
c_func
(paren
id|drive
comma
id|bad_ata33
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0004
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0002
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0001
)paren
(brace
id|speed
op_assign
id|XFER_UDMA_0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0004
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0002
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0001
)paren
(brace
id|speed
op_assign
id|XFER_MW_DMA_0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0004
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0002
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0001
)paren
(brace
id|speed
op_assign
id|XFER_SW_DMA_0
suffix:semicolon
)brace
r_else
(brace
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: config_chipset_for_dma: returning &squot;ide_dma_off_quietly&squot;&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_return
(paren
(paren
r_int
)paren
id|ide_dma_off_quietly
)paren
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x51
comma
op_amp
id|reg51h
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HPT366_FAST_IRQ_PREDICTION
multiline_comment|/*&n;&t; * Some drives prefer/allow for the method of handling interrupts.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg51h
op_amp
l_int|0x80
)paren
)paren
id|pci_write_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x51
comma
id|reg51h
op_or
l_int|0x80
)paren
suffix:semicolon
macro_line|#else /* ! CONFIG_HPT366_FAST_IRQ_PREDICTION */
multiline_comment|/*&n;&t; * Disable the &quot;fast interrupt&quot; prediction.&n;&t; * Instead, always wait for the real interrupt from the drive!&n;&t; */
r_if
c_cond
(paren
id|reg51h
op_amp
l_int|0x80
)paren
id|pci_write_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x51
comma
id|reg51h
op_amp
op_complement
l_int|0x80
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HPT366_FAST_IRQ_PREDICTION */
multiline_comment|/*&n;&t; * Preserve existing PIO settings:&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x40
comma
op_amp
id|reg40
)paren
suffix:semicolon
id|speed
op_assign
(paren
id|speed
op_amp
op_complement
l_int|0xc0000000
)paren
op_or
(paren
id|reg40
op_amp
l_int|0xc0000000
)paren
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: config_chipset_for_dma:  speed=0x%04x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|speed
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
(paren
r_void
)paren
id|hpt366_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
id|rval
op_assign
(paren
r_int
)paren
(paren
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|11
)paren
op_amp
l_int|3
)paren
ques
c_cond
id|ide_dma_on
suffix:colon
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
l_int|7
)paren
ques
c_cond
id|ide_dma_on
suffix:colon
(paren
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
op_amp
l_int|7
)paren
ques
c_cond
id|ide_dma_on
suffix:colon
(paren
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
op_amp
l_int|7
)paren
ques
c_cond
id|ide_dma_on
suffix:colon
id|ide_dma_off_quietly
)paren
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: config_chipset_for_dma: returning %d (%s)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rval
comma
id|rval
op_eq
id|ide_dma_on
ques
c_cond
l_string|&quot;dma_on&quot;
suffix:colon
l_string|&quot;dma_off&quot;
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
r_return
id|rval
suffix:semicolon
)brace
DECL|function|config_chipset_for_pio
r_static
r_void
id|config_chipset_for_pio
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_int
r_int
id|eide_pio_timing
(braket
l_int|6
)braket
op_assign
(brace
l_int|960
comma
l_int|480
comma
l_int|240
comma
l_int|180
comma
l_int|120
comma
l_int|90
)brace
suffix:semicolon
r_int
r_int
id|xfer_pio
op_assign
id|drive-&gt;id-&gt;eide_pio_modes
suffix:semicolon
id|byte
id|timing
comma
id|speed
comma
id|pio
suffix:semicolon
r_int
r_int
id|reg40
op_assign
l_int|0
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: config_chipset_for_pio&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
l_int|255
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfer_pio
OG
l_int|4
)paren
id|xfer_pio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;id-&gt;eide_pio_iordy
OG
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|xfer_pio
op_assign
l_int|5
suffix:semicolon
id|xfer_pio
OG
l_int|0
op_logical_and
id|drive-&gt;id-&gt;eide_pio_iordy
OG
id|eide_pio_timing
(braket
id|xfer_pio
)braket
suffix:semicolon
id|xfer_pio
op_decrement
)paren
suffix:semicolon
)brace
r_else
(brace
id|xfer_pio
op_assign
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
ques
c_cond
l_int|0x05
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
ques
c_cond
l_int|0x04
suffix:colon
(paren
id|drive-&gt;id-&gt;eide_pio_modes
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x03
suffix:colon
(paren
id|drive-&gt;id-&gt;tPIO
op_amp
l_int|2
)paren
ques
c_cond
l_int|0x02
suffix:colon
(paren
id|drive-&gt;id-&gt;tPIO
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x01
suffix:colon
id|xfer_pio
suffix:semicolon
)brace
id|timing
op_assign
(paren
id|xfer_pio
op_ge
id|pio
)paren
ques
c_cond
id|xfer_pio
suffix:colon
id|pio
suffix:semicolon
r_switch
c_cond
(paren
id|timing
)paren
(brace
r_case
l_int|4
suffix:colon
id|speed
op_assign
id|XFER_PIO_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|speed
op_assign
id|XFER_PIO_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|speed
op_assign
id|XFER_PIO_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|speed
op_assign
id|XFER_PIO_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
(paren
op_logical_neg
id|drive-&gt;id-&gt;tPIO
)paren
ques
c_cond
id|XFER_PIO_0
suffix:colon
id|XFER_PIO_SLOW
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Preserve existing DMA settings:&n;&t; */
id|pci_read_config_dword
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x40
comma
op_amp
id|reg40
)paren
suffix:semicolon
id|speed
op_assign
(paren
id|speed
op_amp
op_complement
l_int|0x30070000
)paren
op_or
(paren
id|reg40
op_amp
l_int|0x30070000
)paren
suffix:semicolon
macro_line|#if HPT366_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: config_chipset_for_pio:  speed=0x%04x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|speed
)paren
suffix:semicolon
macro_line|#endif /* HPT366_DEBUG_DRIVE_INFO */
(paren
r_void
)paren
id|hpt366_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|hpt366_tune_drive
r_static
r_void
id|hpt366_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
id|byte
id|speed
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
id|speed
op_assign
id|XFER_PIO_4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|speed
op_assign
id|XFER_PIO_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|speed
op_assign
id|XFER_PIO_2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|speed
op_assign
id|XFER_PIO_1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|speed
op_assign
id|XFER_PIO_0
suffix:semicolon
r_break
suffix:semicolon
)brace
(paren
r_void
)paren
id|hpt366_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
DECL|function|config_drive_xfer_rate
r_static
r_int
id|config_drive_xfer_rate
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
id|ide_dma_action_t
id|dma_func
op_assign
id|ide_dma_on
suffix:semicolon
r_if
c_cond
(paren
id|id
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|autodma
)paren
(brace
multiline_comment|/* Consult the list of known &quot;bad&quot; drives */
r_if
c_cond
(paren
id|ide_dmaproc
c_func
(paren
id|ide_dma_bad_drive
comma
id|drive
)paren
)paren
(brace
id|dma_func
op_assign
id|ide_dma_off
suffix:semicolon
r_goto
id|fast_ata_pio
suffix:semicolon
)brace
id|dma_func
op_assign
id|ide_dma_off_quietly
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x001F
)paren
(brace
multiline_comment|/* Force if Capable UltraDMA */
id|dma_func
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
op_logical_and
(paren
id|dma_func
op_ne
id|ide_dma_on
)paren
)paren
r_goto
id|try_dma_modes
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
id|try_dma_modes
suffix:colon
r_if
c_cond
(paren
(paren
id|id-&gt;dma_mword
op_amp
l_int|0x0007
)paren
op_logical_or
(paren
id|id-&gt;dma_1word
op_amp
l_int|0x0007
)paren
)paren
(brace
multiline_comment|/* Force if Capable regular DMA modes */
id|dma_func
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_func
op_ne
id|ide_dma_on
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ide_dmaproc
c_func
(paren
id|ide_dma_good_drive
comma
id|drive
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;eide_dma_time
OG
l_int|150
)paren
(brace
r_goto
id|no_dma_set
suffix:semicolon
)brace
multiline_comment|/* Consult the list of known &quot;good&quot; drives */
id|dma_func
op_assign
id|config_chipset_for_dma
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_func
op_ne
id|ide_dma_on
)paren
r_goto
id|no_dma_set
suffix:semicolon
)brace
r_else
(brace
r_goto
id|fast_ata_pio
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
op_logical_or
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
(brace
id|fast_ata_pio
suffix:colon
id|dma_func
op_assign
id|ide_dma_off_quietly
suffix:semicolon
id|no_dma_set
suffix:colon
id|config_chipset_for_pio
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_return
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|dma_func
comma
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hpt366_dmaproc() initiates/aborts (U)DMA read/write operations on a drive.&n; *&n; * This is specific to the HPT366 UDMA bios chipset&n; * by HighPoint|Triones Technologies, Inc.&n; */
DECL|function|hpt366_dmaproc
r_int
id|hpt366_dmaproc
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|reg50h
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_check
suffix:colon
r_return
id|config_drive_xfer_rate
c_func
(paren
id|drive
)paren
suffix:semicolon
r_case
id|ide_dma_lostirq
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x50
comma
op_amp
id|reg50h
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x50
comma
id|reg50h
op_or
l_int|0x03
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|pci_dev
comma
l_int|0x50
comma
op_amp
id|reg50h
)paren
suffix:semicolon
multiline_comment|/* ide_set_handler(drive, &amp;ide_dma_intr, WAIT_CMD, NULL); */
r_case
id|ide_dma_timeout
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
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
DECL|function|pci_init_hpt366
r_int
r_int
id|__init
id|pci_init_hpt366
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|byte
id|test
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_or
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
op_amp
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
op_ne
l_int|0x08
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
l_int|0x08
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
op_ne
l_int|0x78
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x78
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_MIN_GNT
comma
op_amp
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
op_ne
l_int|0x08
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_MIN_GNT
comma
l_int|0x08
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_MAX_LAT
comma
op_amp
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test
op_ne
l_int|0x08
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_MAX_LAT
comma
l_int|0x08
)paren
suffix:semicolon
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|ata66_hpt366
r_int
r_int
id|__init
id|ata66_hpt366
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|byte
id|ata66
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x5a
comma
op_amp
id|ata66
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;HPT366: reg5ah=0x%02x ATA-%s Cable Port%d&bslash;n&quot;
comma
id|ata66
comma
(paren
id|ata66
op_amp
l_int|0x02
)paren
ques
c_cond
l_string|&quot;33&quot;
suffix:colon
l_string|&quot;66&quot;
comma
id|PCI_FUNC
c_func
(paren
id|hwif-&gt;pci_dev-&gt;devfn
)paren
)paren
suffix:semicolon
macro_line|#endif /* DEBUG */
r_return
(paren
(paren
id|ata66
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ide_init_hpt366
r_void
id|__init
id|ide_init_hpt366
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|PCI_FUNC
c_func
(paren
id|hwif-&gt;pci_dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
op_logical_and
(paren
id|hpt363_shared_irq
)paren
)paren
(brace
id|hwif-&gt;mate
op_assign
op_amp
id|ide_hwifs
(braket
id|hwif-&gt;index
op_minus
l_int|1
)braket
suffix:semicolon
id|hwif-&gt;mate-&gt;mate
op_assign
id|hwif
suffix:semicolon
id|hwif-&gt;serialized
op_assign
id|hwif-&gt;mate-&gt;serialized
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|PCI_FUNC
c_func
(paren
id|hwif-&gt;pci_dev-&gt;devfn
)paren
op_amp
l_int|1
)paren
op_logical_and
(paren
id|hpt363_shared_pin
)paren
)paren
(brace
)brace
macro_line|#endif
id|hwif-&gt;tuneproc
op_assign
op_amp
id|hpt366_tune_drive
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
id|hwif-&gt;dmaproc
op_assign
op_amp
id|hpt366_dmaproc
suffix:semicolon
)brace
r_else
(brace
id|hwif-&gt;autodma
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|ide_dmacapable_hpt366
r_void
id|ide_dmacapable_hpt366
(paren
id|ide_hwif_t
op_star
id|hwif
comma
r_int
r_int
id|dmabase
)paren
(brace
id|byte
id|masterdma
op_assign
l_int|0
comma
id|slavedma
op_assign
l_int|0
suffix:semicolon
id|byte
id|dma_new
op_assign
l_int|0
comma
id|dma_old
op_assign
id|inb
c_func
(paren
id|dmabase
op_plus
l_int|2
)paren
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
id|dma_new
op_assign
id|dma_old
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x43
comma
op_amp
id|masterdma
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x47
comma
op_amp
id|slavedma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|masterdma
op_amp
l_int|0x30
)paren
id|dma_new
op_or_assign
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|slavedma
op_amp
l_int|0x30
)paren
id|dma_new
op_or_assign
l_int|0x40
suffix:semicolon
r_if
c_cond
(paren
id|dma_new
op_ne
id|dma_old
)paren
id|outb
c_func
(paren
id|dma_new
comma
id|dmabase
op_plus
l_int|2
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|ide_setup_dma
c_func
(paren
id|hwif
comma
id|dmabase
comma
l_int|8
)paren
suffix:semicolon
)brace
eof
