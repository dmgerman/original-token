multiline_comment|/*&n; * linux/drivers/block/hpt343.c&t;&t;Version 0.23&t;May 12, 1999&n; *&n; * Copyright (C) 1998-99&t;Andre Hedrick&n; *&t;&t;&t;&t;&t;(hedrick@astro.dyer.vanderbilt.edu)&n; *&n; * 00:12.0 Unknown mass storage controller:&n; * Triones Technologies, Inc.&n; * Unknown device 0003 (rev 01)&n; *&n; * hde: UDMA 2 (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: UDMA 2 (0x0002 0x0012) (0x0010 0x0030)&n; * hde: DMA 2  (0x0000 0x0002) (0x0000 0x0010)&n; * hdf: DMA 2  (0x0002 0x0012) (0x0010 0x0030)&n; * hdg: DMA 1  (0x0012 0x0052) (0x0030 0x0070)&n; * hdh: DMA 1  (0x0052 0x0252) (0x0070 0x00f0)&n; *&n; * drive_number&n; *&t;= ((HWIF(drive)-&gt;channel ? 2 : 0) + (drive-&gt;select.b.unit &amp; 0x01));&n; *&t;= ((hwif-&gt;channel ? 2 : 0) + (drive-&gt;select.b.unit &amp; 0x01));&n; */
macro_line|#include &lt;linux/config.h&gt;&t;/* for CONFIG_BLK_DEV_IDEPCI */
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
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
DECL|macro|HPT343_DEBUG_DRIVE_INFO
mdefine_line|#define HPT343_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|HPT343_DISABLE_ALL_DMAING
mdefine_line|#define HPT343_DISABLE_ALL_DMAING&t;0
DECL|macro|HPT343_DMA_DISK_ONLY
mdefine_line|#define HPT343_DMA_DISK_ONLY&t;&t;0
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
DECL|function|hpt343_clear_chipset
r_static
r_void
id|hpt343_clear_chipset
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
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
r_int
r_int
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
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
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
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
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
l_int|0x00
op_lshift
(paren
l_int|3
op_star
id|drive_number
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive_number
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
l_int|0x00
op_lshift
id|drive_number
)paren
op_or
id|reg2
)paren
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
l_int|0x44
comma
id|tmp1
)paren
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
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
)brace
DECL|function|hpt343_tune_chipset
r_static
r_int
id|hpt343_tune_chipset
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
id|byte
id|hi_speed
comma
id|lo_speed
suffix:semicolon
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
r_int
r_int
id|reg1
op_assign
l_int|0
comma
id|tmp1
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|reg2
op_assign
l_int|0
comma
id|tmp2
op_assign
l_int|0
suffix:semicolon
id|SPLIT_BYTE
c_func
(paren
id|speed
comma
id|hi_speed
comma
id|lo_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi_speed
op_amp
l_int|7
)paren
(brace
id|hi_speed
op_assign
(paren
id|hi_speed
op_amp
l_int|4
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x10
suffix:semicolon
)brace
r_else
(brace
id|lo_speed
op_lshift_assign
l_int|5
suffix:semicolon
id|lo_speed
op_rshift_assign
l_int|5
suffix:semicolon
)brace
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
l_int|0x44
comma
op_amp
id|reg1
)paren
suffix:semicolon
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
l_int|0x48
comma
op_amp
id|reg2
)paren
suffix:semicolon
id|tmp1
op_assign
(paren
(paren
id|lo_speed
op_lshift
(paren
l_int|3
op_star
id|drive_number
)paren
)paren
op_or
(paren
id|reg1
op_amp
op_complement
(paren
l_int|7
op_lshift
(paren
l_int|3
op_star
id|drive_number
)paren
)paren
)paren
)paren
suffix:semicolon
id|tmp2
op_assign
(paren
(paren
id|hi_speed
op_lshift
id|drive_number
)paren
op_or
id|reg2
)paren
suffix:semicolon
id|err
op_assign
id|ide_wait_cmd
c_func
(paren
id|drive
comma
id|WIN_SETFEATURES
comma
id|speed
comma
id|SETFEATURES_XFER
comma
l_int|0
comma
l_int|NULL
)paren
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
l_int|0x44
comma
id|tmp1
)paren
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
l_int|0x48
comma
id|tmp2
)paren
suffix:semicolon
macro_line|#if HPT343_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: %s drive%d (0x%04x 0x%04x) (0x%04x 0x%04x)&quot;
"&bslash;"
l_string|&quot; (0x%02x 0x%02x) 0x%04x&bslash;n&quot;
comma
id|drive-&gt;name
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
id|tmp1
comma
id|reg2
comma
id|tmp2
comma
id|hi_speed
comma
id|lo_speed
comma
id|err
)paren
suffix:semicolon
macro_line|#endif /* HPT343_DEBUG_DRIVE_INFO */
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * This allows the configuration of ide_pci chipset registers&n; * for cards that learn about the drive&squot;s UDMA, DMA, PIO capabilities&n; * after the drive is reported by the OS.  Initally for designed for&n; * HPT343 UDMA chipset by HighPoint|Triones Technologies, Inc.&n; */
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
macro_line|#if HPT343_DISABLE_ALL_DMAING
r_return
(paren
(paren
r_int
)paren
id|ide_dma_off
)paren
suffix:semicolon
macro_line|#elif HPT343_DMA_DISK_ONLY
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
)paren
r_return
(paren
(paren
r_int
)paren
id|ide_dma_off_quietly
)paren
suffix:semicolon
macro_line|#endif /* HPT343_DISABLE_ALL_DMAING */
r_if
c_cond
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0004
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
l_int|4
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_ultra
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0404
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
l_int|2
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_ultra
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0202
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_ultra
op_rshift
l_int|8
)paren
op_amp
l_int|1
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_ultra
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_ultra
op_or_assign
l_int|0x0101
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
id|speed
op_assign
id|XFER_UDMA_0
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
op_amp
l_int|4
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0404
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
op_amp
l_int|2
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0202
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
op_amp
l_int|1
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_or_assign
l_int|0x0101
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
op_amp
l_int|4
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0404
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
op_amp
l_int|2
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0202
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
op_amp
l_int|1
)paren
)paren
(brace
id|drive-&gt;id-&gt;dma_1word
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
id|drive-&gt;id-&gt;dma_1word
op_or_assign
l_int|0x0101
suffix:semicolon
id|drive-&gt;id-&gt;dma_mword
op_and_assign
op_complement
l_int|0x0F00
suffix:semicolon
)brace
id|speed
op_assign
id|XFER_SW_DMA_0
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
(paren
r_int
)paren
id|ide_dma_off_quietly
)paren
suffix:semicolon
)brace
(paren
r_void
)paren
id|hpt343_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
)paren
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
(paren
r_void
)paren
id|hpt343_tune_chipset
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|hpt343_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
)brace
macro_line|#endif
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
l_int|0x0007
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
multiline_comment|/*&n; * hpt343_dmaproc() initiates/aborts (U)DMA read/write operations on a drive.&n; *&n; * This is specific to the HPT343 UDMA bios-less chipset&n; * and HPT345 UDMA bios chipset (stamped HPT363)&n; * by HighPoint|Triones Technologies, Inc.&n; */
DECL|function|hpt343_dmaproc
r_int
id|hpt343_dmaproc
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|ide_dma_check
suffix:colon
id|hpt343_clear_chipset
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|config_drive_xfer_rate
c_func
(paren
id|drive
)paren
suffix:semicolon
macro_line|#if 0
r_case
id|ide_dma_off
suffix:colon
r_case
id|ide_dma_off_quietly
suffix:colon
r_case
id|ide_dma_on
suffix:colon
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
id|ide_dma_read
suffix:colon
r_case
id|ide_dma_write
suffix:colon
r_case
id|ide_dma_begin
suffix:colon
r_case
id|ide_dma_end
suffix:colon
r_case
id|ide_dma_test_irq
suffix:colon
macro_line|#endif
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
multiline_comment|/*&n; * If the BIOS does not set the IO base addaress to XX00, 343 will fail.&n; */
DECL|macro|HPT343_PCI_INIT_REG
mdefine_line|#define&t;HPT343_PCI_INIT_REG&t;&t;0x80
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|pci_init_hpt343
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
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_int
r_int
id|hpt343IoBase
op_assign
id|dev-&gt;base_address
(braket
l_int|4
)braket
op_amp
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
macro_line|#if 0
r_int
r_char
id|misc10
op_assign
id|inb
c_func
(paren
id|hpt343IoBase
op_plus
l_int|0x0010
)paren
suffix:semicolon
r_int
r_char
id|misc11
op_assign
id|inb
c_func
(paren
id|hpt343IoBase
op_plus
l_int|0x0011
)paren
suffix:semicolon
macro_line|#endif
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|HPT343_PCI_INIT_REG
comma
l_int|0x00
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
op_amp
op_complement
id|PCI_COMMAND_IO
)paren
suffix:semicolon
id|dev-&gt;base_address
(braket
l_int|0
)braket
op_assign
(paren
id|hpt343IoBase
op_plus
l_int|0x20
)paren
suffix:semicolon
id|dev-&gt;base_address
(braket
l_int|1
)braket
op_assign
(paren
id|hpt343IoBase
op_plus
l_int|0x34
)paren
suffix:semicolon
id|dev-&gt;base_address
(braket
l_int|2
)braket
op_assign
(paren
id|hpt343IoBase
op_plus
l_int|0x28
)paren
suffix:semicolon
id|dev-&gt;base_address
(braket
l_int|3
)braket
op_assign
(paren
id|hpt343IoBase
op_plus
l_int|0x3c
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;base_address
(braket
id|i
)braket
op_or_assign
id|PCI_BASE_ADDRESS_SPACE_IO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Since 20-23 can be assigned and are R/W, we correct them.&n;&t; */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
comma
id|dev-&gt;base_address
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_1
comma
id|dev-&gt;base_address
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_2
comma
id|dev-&gt;base_address
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_3
comma
id|dev-&gt;base_address
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
macro_line|#if 0
id|outb
c_func
(paren
id|misc10
op_or
l_int|0x78
comma
(paren
id|hpt343IoBase
op_plus
l_int|0x0010
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|misc11
comma
(paren
id|hpt343IoBase
op_plus
l_int|0x0011
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: 0x%02x 0x%02x&bslash;n&quot;
comma
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
l_string|&quot;HPT345&quot;
suffix:colon
id|name
comma
id|inb
c_func
(paren
id|hpt343IoBase
op_plus
l_int|0x0010
)paren
comma
id|inb
c_func
(paren
id|hpt343IoBase
op_plus
l_int|0x0011
)paren
)paren
suffix:semicolon
macro_line|#endif
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|HPT343_PCI_INIT_REG
comma
l_int|0x80
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;rom_address
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_ROM_ADDRESS
comma
id|dev-&gt;rom_address
op_or
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HPT345: ROM enabled at 0x%08lx&bslash;n&quot;
comma
id|dev-&gt;rom_address
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x20
)paren
suffix:semicolon
)brace
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|ide_init_hpt343
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
)paren
(brace
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
r_int
r_int
id|pcicmd
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|hwif-&gt;pci_dev
comma
id|PCI_COMMAND
comma
op_amp
id|pcicmd
)paren
suffix:semicolon
id|hwif-&gt;autodma
op_assign
(paren
id|pcicmd
op_amp
id|PCI_COMMAND_MEMORY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|hwif-&gt;dmaproc
op_assign
op_amp
id|hpt343_dmaproc
suffix:semicolon
)brace
)brace
eof
