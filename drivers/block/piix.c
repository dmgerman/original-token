multiline_comment|/*&n; * linux/drivers/block/piix.c&t;Version 0.28&t;Dec. 13, 1999&n; *&n; *  Copyright (C) 1998-1999 Andrzej Krzysztofowicz, Author and Maintainer&n; *  Copyright (C) 1998-1999 Andre Hedrick (andre@suse.com)&n; *  May be copied or modified under the terms of the GNU General Public License&n; *&n; *  PIO mode setting function for Intel chipsets.  &n; *  For use instead of BIOS settings.&n; *&n; * 40-41&n; * 42-43&n; * &n; *                 41&n; *                 43&n; *&n; * | PIO 0       | c0 | 80 | 0 | &t;piix_tune_drive(drive, 0);&n; * | PIO 2 | SW2 | d0 | 90 | 4 | &t;piix_tune_drive(drive, 2);&n; * | PIO 3 | MW1 | e1 | a1 | 9 | &t;piix_tune_drive(drive, 3);&n; * | PIO 4 | MW2 | e3 | a3 | b | &t;piix_tune_drive(drive, 4);&n; * &n; * sitre = word40 &amp; 0x4000; primary&n; * sitre = word42 &amp; 0x4000; secondary&n; *&n; * 44 8421|8421    hdd|hdb&n; * &n; * 48 8421         hdd|hdc|hdb|hda udma enabled&n; *&n; *    0001         hda&n; *    0010         hdb&n; *    0100         hdc&n; *    1000         hdd&n; *&n; * 4a 84|21        hdb|hda&n; * 4b 84|21        hdd|hdc&n; *&n; *    ata-33/82371AB&n; *    ata-33/82371EB&n; *    ata-33/82801AB            ata-66/82801AA&n; *    00|00 udma 0              00|00 reserved&n; *    01|01 udma 1              01|01 udma 3&n; *    10|10 udma 2              10|10 udma 4&n; *    11|11 reserved            11|11 reserved&n; *&n; * 54 8421|8421    ata66 drive|ata66 enable&n; *&n; * pci_read_config_word(HWIF(drive)-&gt;pci_dev, 0x40, &amp;reg40);&n; * pci_read_config_word(HWIF(drive)-&gt;pci_dev, 0x42, &amp;reg42);&n; * pci_read_config_word(HWIF(drive)-&gt;pci_dev, 0x44, &amp;reg44);&n; * pci_read_config_word(HWIF(drive)-&gt;pci_dev, 0x48, &amp;reg48);&n; * pci_read_config_word(HWIF(drive)-&gt;pci_dev, 0x4a, &amp;reg4a);&n; *&n; * #if 0&n; * int err;&n; * err = ide_config_drive_speed(drive, speed);&n; * (void) ide_config_drive_speed(drive, speed);&n; * #else&n; * #endif&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
DECL|macro|PIIX_DEBUG_DRIVE_INFO
mdefine_line|#define PIIX_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|DISPLAY_PIIX_TIMINGS
mdefine_line|#define DISPLAY_PIIX_TIMINGS
macro_line|#if defined(DISPLAY_PIIX_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
r_static
r_int
id|piix_get_info
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
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|piix_display_info
)paren
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
)paren
suffix:semicolon
multiline_comment|/* ide-proc.c */
r_extern
r_char
op_star
id|ide_media_verbose
c_func
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
DECL|variable|bmide_dev
r_static
r_struct
id|pci_dev
op_star
id|bmide_dev
suffix:semicolon
DECL|function|piix_get_info
r_static
r_int
id|piix_get_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|addr
comma
id|off_t
id|offset
comma
r_int
id|count
)paren
(brace
multiline_comment|/* int rc; */
r_int
id|piix_who
op_assign
(paren
(paren
id|bmide_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801AA_1
)paren
op_logical_or
(paren
id|bmide_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801AB_1
)paren
op_logical_or
(paren
id|bmide_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82371AB
)paren
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|3
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                                Intel PIIX%d Chipset.&bslash;n&quot;
comma
id|piix_who
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- Primary Channel ---------------- Secondary Channel -------------&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;--------------- drive0 --------- drive1 -------- drive0 ---------- drive1 ------&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;FIXME.... Add configuration junk data....blah blah......&n; */
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* =&gt; must be less than 4k! */
)brace
macro_line|#endif  /* defined(DISPLAY_PIIX_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
multiline_comment|/*&n; *  Used to set Fifo configuration via kernel command line:&n; */
DECL|variable|piix_proc
id|byte
id|piix_proc
op_assign
l_int|0
suffix:semicolon
r_extern
r_char
op_star
id|ide_xfer_verbose
(paren
id|byte
id|xfer_rate
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_PIIX_TUNING
multiline_comment|/*&n; *&n; */
DECL|function|piix_dma_2_pio
r_static
id|byte
id|piix_dma_2_pio
(paren
id|byte
id|xfer_rate
)paren
(brace
r_switch
c_cond
(paren
id|xfer_rate
)paren
(brace
r_case
id|XFER_UDMA_4
suffix:colon
r_case
id|XFER_UDMA_3
suffix:colon
r_case
id|XFER_UDMA_2
suffix:colon
r_case
id|XFER_UDMA_1
suffix:colon
r_case
id|XFER_UDMA_0
suffix:colon
r_case
id|XFER_MW_DMA_2
suffix:colon
r_case
id|XFER_PIO_4
suffix:colon
r_return
l_int|4
suffix:semicolon
r_case
id|XFER_MW_DMA_1
suffix:colon
r_case
id|XFER_PIO_3
suffix:colon
r_return
l_int|3
suffix:semicolon
r_case
id|XFER_SW_DMA_2
suffix:colon
r_case
id|XFER_PIO_2
suffix:colon
r_return
l_int|2
suffix:semicolon
r_case
id|XFER_MW_DMA_0
suffix:colon
r_case
id|XFER_SW_DMA_1
suffix:colon
r_case
id|XFER_SW_DMA_0
suffix:colon
r_case
id|XFER_PIO_1
suffix:colon
r_case
id|XFER_PIO_0
suffix:colon
r_case
id|XFER_PIO_SLOW
suffix:colon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_BLK_DEV_PIIX_TUNING */
multiline_comment|/*&n; *  Based on settings done by AMI BIOS&n; *  (might be usefull if drive is not registered in CMOS for any reason).&n; */
DECL|function|piix_tune_drive
r_static
r_void
id|piix_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u16
id|master_data
suffix:semicolon
id|byte
id|slave_data
suffix:semicolon
r_int
id|is_slave
op_assign
(paren
op_amp
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drives
(braket
l_int|1
)braket
op_eq
id|drive
)paren
suffix:semicolon
r_int
id|master_port
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
r_int
id|slave_port
op_assign
l_int|0x44
suffix:semicolon
multiline_comment|/* ISP  RTC */
id|byte
id|timings
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|2
comma
l_int|1
)brace
comma
(brace
l_int|2
comma
l_int|3
)brace
comma
)brace
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
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_read_config_word
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
id|master_port
comma
op_amp
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
(brace
id|master_data
op_assign
id|master_data
op_or
l_int|0x4000
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_assign
id|master_data
op_or
l_int|0x0070
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
id|slave_port
comma
op_amp
id|slave_data
)paren
suffix:semicolon
id|slave_data
op_assign
id|slave_data
op_amp
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
ques
c_cond
l_int|0x0f
suffix:colon
l_int|0xf0
)paren
suffix:semicolon
id|slave_data
op_assign
id|slave_data
op_or
(paren
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|2
)paren
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
op_lshift
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|master_data
op_assign
id|master_data
op_amp
l_int|0xccf8
suffix:semicolon
r_if
c_cond
(paren
id|pio
OG
l_int|1
)paren
multiline_comment|/* enable PPE, IE and TIME */
id|master_data
op_assign
id|master_data
op_or
l_int|0x0007
suffix:semicolon
id|master_data
op_assign
id|master_data
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|0
)braket
op_lshift
l_int|12
)paren
op_or
(paren
id|timings
(braket
id|pio
)braket
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
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
id|pci_write_config_word
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
id|master_port
comma
id|master_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
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
id|slave_port
comma
id|slave_data
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_PIIX_TUNING
DECL|function|piix_config_drive_for_dma
r_static
r_int
id|piix_config_drive_for_dma
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
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
r_int
id|sitre
suffix:semicolon
r_int
id|reg4042
comma
id|reg44
comma
id|reg48
comma
id|reg4a
comma
id|reg54
suffix:semicolon
id|byte
id|speed
suffix:semicolon
id|byte
id|maslave
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x42
suffix:colon
l_int|0x40
suffix:semicolon
id|byte
id|udma_66
op_assign
(paren
(paren
id|id-&gt;hw_config
op_amp
l_int|0x2000
)paren
op_logical_and
(paren
id|hwif-&gt;udma_four
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|ultra
op_assign
(paren
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82371AB
)paren
op_logical_or
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801AB_1
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|ultra66
op_assign
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801AA_1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_int
id|drive_number
op_assign
(paren
(paren
id|hwif-&gt;channel
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
id|a_speed
op_assign
l_int|2
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
r_int
id|u_flag
op_assign
l_int|1
op_lshift
id|drive_number
suffix:semicolon
r_int
id|u_speed
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|maslave
comma
op_amp
id|reg4042
)paren
suffix:semicolon
id|sitre
op_assign
(paren
id|reg4042
op_amp
l_int|0x4000
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|reg44
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
op_amp
id|reg48
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
op_amp
id|reg4a
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
l_int|0x54
comma
op_amp
id|reg54
)paren
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
id|ultra
)paren
)paren
(brace
id|u_speed
op_assign
l_int|2
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
id|speed
op_assign
(paren
(paren
id|udma_66
)paren
op_logical_and
(paren
id|ultra66
)paren
)paren
ques
c_cond
id|XFER_UDMA_4
suffix:colon
id|XFER_UDMA_2
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
id|ultra
)paren
)paren
(brace
id|u_speed
op_assign
l_int|1
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
id|speed
op_assign
(paren
(paren
id|udma_66
)paren
op_logical_and
(paren
id|ultra66
)paren
)paren
ques
c_cond
id|XFER_UDMA_3
suffix:colon
id|XFER_UDMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0004
)paren
op_logical_and
(paren
id|ultra
)paren
)paren
(brace
id|u_speed
op_assign
l_int|2
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
id|speed
op_assign
id|XFER_UDMA_2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0002
)paren
op_logical_and
(paren
id|ultra
)paren
)paren
(brace
id|u_speed
op_assign
l_int|1
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
id|speed
op_assign
id|XFER_UDMA_1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|id-&gt;dma_ultra
op_amp
l_int|0x0001
)paren
op_logical_and
(paren
id|ultra
)paren
)paren
(brace
id|u_speed
op_assign
l_int|0
op_lshift
(paren
id|drive_number
op_star
l_int|4
)paren
suffix:semicolon
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
(brace
id|speed
op_assign
id|XFER_PIO_0
op_plus
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
)brace
multiline_comment|/*&n;&t; * This is !@#$% ugly and stupid.............&n;&t; * But ugly harware generates ugly code.........&n;&t; */
r_if
c_cond
(paren
id|speed
op_ge
id|XFER_UDMA_0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg48
op_amp
id|u_flag
)paren
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_or
id|u_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg4a
op_amp
id|u_speed
)paren
)paren
(brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_or
id|u_speed
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|speed
OG
id|XFER_UDMA_2
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|reg54
op_amp
id|u_flag
)paren
)paren
)paren
(brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_or
id|u_flag
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|speed
OL
id|XFER_UDMA_0
)paren
(brace
r_if
c_cond
(paren
id|reg48
op_amp
id|u_flag
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x48
comma
id|reg48
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg4a
op_amp
id|a_speed
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x4a
comma
id|reg4a
op_amp
op_complement
id|a_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg54
op_amp
id|u_flag
)paren
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x54
comma
id|reg54
op_amp
op_complement
id|u_flag
)paren
suffix:semicolon
)brace
id|piix_tune_drive
c_func
(paren
id|drive
comma
id|piix_dma_2_pio
c_func
(paren
id|speed
)paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|ide_config_drive_speed
c_func
(paren
id|drive
comma
id|speed
)paren
suffix:semicolon
macro_line|#if PIIX_DEBUG_DRIVE_INFO
id|printk
c_func
(paren
l_string|&quot;%s: %s drive%d &quot;
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
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* PIIX_DEBUG_DRIVE_INFO */
r_return
(paren
(paren
r_int
)paren
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
)brace
DECL|function|piix_dmaproc
r_static
r_int
id|piix_dmaproc
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
id|ide_dmaproc
c_func
(paren
(paren
id|ide_dma_action_t
)paren
id|piix_config_drive_for_dma
c_func
(paren
id|drive
)paren
comma
id|drive
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Other cases are done by generic IDE-DMA code. */
r_return
id|ide_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_PIIX_TUNING */
DECL|function|pci_init_piix
r_int
r_int
id|__init
id|pci_init_piix
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
macro_line|#if defined(DISPLAY_PIIX_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
r_if
c_cond
(paren
op_logical_neg
id|piix_proc
)paren
(brace
id|piix_proc
op_assign
l_int|1
suffix:semicolon
id|bmide_dev
op_assign
id|dev
suffix:semicolon
id|piix_display_info
op_assign
op_amp
id|piix_get_info
suffix:semicolon
)brace
macro_line|#endif /* DISPLAY_PIIX_TIMINGS &amp;&amp; CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Sheesh, someone at Intel needs to go read the ATA-4/5 T13 standards.&n; * It does not specify device detection, but channel!!!&n; * You determine later if bit 13 of word93 is set...&n; */
DECL|function|ata66_piix
r_int
r_int
id|__init
id|ata66_piix
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|byte
id|reg54h
op_assign
l_int|0
comma
id|reg55h
op_assign
l_int|0
comma
id|ata66
op_assign
l_int|0
suffix:semicolon
id|byte
id|mask
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|0x0c
suffix:colon
l_int|0x03
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x54
comma
op_amp
id|reg54h
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hwif-&gt;pci_dev
comma
l_int|0x55
comma
op_amp
id|reg55h
)paren
suffix:semicolon
id|ata66
op_assign
(paren
id|reg54h
op_amp
id|mask
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_return
id|ata66
suffix:semicolon
)brace
DECL|function|ide_init_piix
r_void
id|__init
id|ide_init_piix
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;tuneproc
op_assign
op_amp
id|piix_tune_drive
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_PIIX_TUNING
id|hwif-&gt;dmaproc
op_assign
op_amp
id|piix_dmaproc
suffix:semicolon
macro_line|#endif /* CONFIG_BLK_DEV_PIIX_TUNING */
id|hwif-&gt;drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|0
suffix:semicolon
id|hwif-&gt;drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
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
r_if
c_cond
(paren
op_logical_neg
id|hwif-&gt;irq
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
)brace
eof
