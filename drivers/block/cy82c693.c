multiline_comment|/*&n; * linux/drivers/block/cy82c693.c&t;Version 0.34&t;Dec. 13, 1999&n; *&n; *  Copyright (C) 1998-99 Andreas S. Krebs (akrebs@altavista.net), Maintainer&n; *  Copyright (C) 1998-99 Andre Hedrick, Integrater&n; *&n; * CYPRESS CY82C693 chipset IDE controller&n; *&n; * The CY82C693 chipset is used on Digital&squot;s PC-Alpha 164SX boards.&n; * Writting the driver was quite simple, since most of the job is&n; * done by the generic pci-ide support. &n; * The hard part was finding the CY82C693&squot;s datasheet on Cypress&squot;s&n; * web page :-(. But Altavista solved this problem :-).&n; *&n; *&n; * Notes:&n; * - I recently got a 16.8G IBM DTTA, so I was able to test it with&n; *   a large and fast disk - the results look great, so I&squot;d say the&n; *   driver is working fine :-)&n; *   hdparm -t reports 8.17 MB/sec at about 6% CPU usage for the DTTA &n; * - this is my first linux driver, so there&squot;s probably a lot  of room &n; *   for optimizations and bug fixing, so feel free to do it.&n; * - use idebus=xx parameter to set PCI bus speed - needed to calc&n; *   timings for PIO modes (default will be 40)&n; * - if using PIO mode it&squot;s a good idea to set the PIO mode and &n; *   32-bit I/O support (if possible), e.g. hdparm -p2 -c1 /dev/hda&n; * - I had some problems with my IBM DHEA with PIO modes &lt; 2&n; *   (lost interrupts) ?????&n; * - first tests with DMA look okay, they seem to work, but there is a&n; *   problem with sound - the BusMaster IDE TimeOut should fixed this&n; *&n; *&n; * History:&n; * AMH@1999-08-24: v0.34 init_cy82c693_chip moved to pci_init_cy82c693&n; * ASK@1999-01-23: v0.33 made a few minor code clean ups&n; *                       removed DMA clock speed setting by default&n; *                       added boot message&n; * ASK@1998-11-01: v0.32 added support to set BusMaster IDE TimeOut&n; *                       added support to set DMA Controller Clock Speed&n; * ASK@1998-10-31: v0.31 fixed problem with setting to high DMA modes on some drive&n; * ASK@1998-10-29: v0.3 added support to set DMA modes&n; * ASK@1998-10-28: v0.2 added support to set PIO modes&n; * ASK@1998-10-27: v0.1 first version - chipset detection&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
multiline_comment|/* the current version */
DECL|macro|CY82_VERSION
mdefine_line|#define CY82_VERSION&t;&quot;CY82C693U driver v0.34 99-09-03 Andreas S. Krebs (akrebs@altavista.net)&quot;
multiline_comment|/*&n; *&t;The following are used to debug the driver.&n; */
DECL|macro|CY82C693_DEBUG_LOGS
mdefine_line|#define&t;CY82C693_DEBUG_LOGS&t;0
DECL|macro|CY82C693_DEBUG_INFO
mdefine_line|#define&t;CY82C693_DEBUG_INFO&t;0
multiline_comment|/* define CY82C693_SETDMA_CLOCK to set DMA Controller Clock Speed to ATCLK */
DECL|macro|CY82C693_SETDMA_CLOCK
macro_line|#undef CY82C693_SETDMA_CLOCK
multiline_comment|/*&n; * note: the value for busmaster timeout is tricky and i got it by trial and error !&n; *       using a to low value will cause DMA timeouts and drop IDE performance&n; *       using a to high value will cause audio playback to scatter&n; *       if you know a better value or how to calc it, please let me know &n; */
DECL|macro|BUSMASTER_TIMEOUT
mdefine_line|#define BUSMASTER_TIMEOUT&t;0x50&t;/* twice the value written in cy82c693ub datasheet */
multiline_comment|/*&n; * the value above was tested on my machine and it seems to work okay&n; */
multiline_comment|/* here are the offset definitions for the registers */
DECL|macro|CY82_IDE_CMDREG
mdefine_line|#define CY82_IDE_CMDREG&t;&t;0x04
DECL|macro|CY82_IDE_ADDRSETUP
mdefine_line|#define CY82_IDE_ADDRSETUP&t;0x48
DECL|macro|CY82_IDE_MASTER_IOR
mdefine_line|#define CY82_IDE_MASTER_IOR&t;0x4C&t;
DECL|macro|CY82_IDE_MASTER_IOW
mdefine_line|#define CY82_IDE_MASTER_IOW&t;0x4D&t;
DECL|macro|CY82_IDE_SLAVE_IOR
mdefine_line|#define CY82_IDE_SLAVE_IOR&t;0x4E&t;
DECL|macro|CY82_IDE_SLAVE_IOW
mdefine_line|#define CY82_IDE_SLAVE_IOW&t;0x4F
DECL|macro|CY82_IDE_MASTER_8BIT
mdefine_line|#define CY82_IDE_MASTER_8BIT&t;0x50&t;
DECL|macro|CY82_IDE_SLAVE_8BIT
mdefine_line|#define CY82_IDE_SLAVE_8BIT&t;0x51&t;
DECL|macro|CY82_INDEX_PORT
mdefine_line|#define CY82_INDEX_PORT&t;&t;0x22
DECL|macro|CY82_DATA_PORT
mdefine_line|#define CY82_DATA_PORT&t;&t;0x23
DECL|macro|CY82_INDEX_CTRLREG1
mdefine_line|#define CY82_INDEX_CTRLREG1&t;0x01
DECL|macro|CY82_INDEX_CHANNEL0
mdefine_line|#define CY82_INDEX_CHANNEL0&t;0x30
DECL|macro|CY82_INDEX_CHANNEL1
mdefine_line|#define CY82_INDEX_CHANNEL1&t;0x31
DECL|macro|CY82_INDEX_TIMEOUT
mdefine_line|#define CY82_INDEX_TIMEOUT&t;0x32
multiline_comment|/* the max PIO mode - from datasheet */
DECL|macro|CY82C693_MAX_PIO
mdefine_line|#define CY82C693_MAX_PIO&t;4
multiline_comment|/* the min and max PCI bus speed in MHz - from datasheet */
DECL|macro|CY82C963_MIN_BUS_SPEED
mdefine_line|#define CY82C963_MIN_BUS_SPEED&t;25
DECL|macro|CY82C963_MAX_BUS_SPEED
mdefine_line|#define CY82C963_MAX_BUS_SPEED&t;33
multiline_comment|/* the struct for the PIO mode timings */
DECL|struct|pio_clocks_s
r_typedef
r_struct
id|pio_clocks_s
(brace
DECL|member|address_time
id|byte
id|address_time
suffix:semicolon
multiline_comment|/* Address setup (clocks) */
DECL|member|time_16r
id|byte
id|time_16r
suffix:semicolon
multiline_comment|/* clocks for 16bit IOR (0xF0=Active/data, 0x0F=Recovery) */
DECL|member|time_16w
id|byte
id|time_16w
suffix:semicolon
multiline_comment|/* clocks for 16bit IOW (0xF0=Active/data, 0x0F=Recovery) */
DECL|member|time_8
id|byte
id|time_8
suffix:semicolon
multiline_comment|/* clocks for 8bit (0xF0=Active/data, 0x0F=Recovery) */
DECL|typedef|pio_clocks_t
)brace
id|pio_clocks_t
suffix:semicolon
multiline_comment|/*&n; * calc clocks using bus_speed&n; * returns (rounded up) time in bus clocks for time in ns&n; */
DECL|function|calc_clk
r_static
r_int
id|calc_clk
(paren
r_int
id|time
comma
r_int
id|bus_speed
)paren
(brace
r_int
id|clocks
suffix:semicolon
id|clocks
op_assign
(paren
id|time
op_star
id|bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|clocks
OL
l_int|0
)paren
id|clocks
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|clocks
OG
l_int|0x0F
)paren
id|clocks
op_assign
l_int|0x0F
suffix:semicolon
r_return
id|clocks
suffix:semicolon
)brace
multiline_comment|/*&n; * compute the values for the clock registers for PIO&n; * mode and pci_clk [MHz] speed&n; *&n; * NOTE: for mode 0,1 and 2 drives 8-bit IDE command control registers are used&n; *       for mode 3 and 4 drives 8 and 16-bit timings are the same&n; *&n; */
DECL|function|compute_clocks
r_static
r_void
id|compute_clocks
(paren
id|byte
id|pio
comma
id|pio_clocks_t
op_star
id|p_pclk
)paren
(brace
r_int
id|clk1
comma
id|clk2
suffix:semicolon
r_int
id|bus_speed
suffix:semicolon
id|bus_speed
op_assign
id|ide_system_bus_speed
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* get speed of PCI bus */
multiline_comment|/* we don&squot;t check against CY82C693&squot;s min and max speed,&n;&t; * so you can play with the idebus=xx parameter&n;&t; */
r_if
c_cond
(paren
id|pio
OG
id|CY82C693_MAX_PIO
)paren
id|pio
op_assign
id|CY82C693_MAX_PIO
suffix:semicolon
multiline_comment|/* let&squot;s calc the address setup time clocks */
id|p_pclk-&gt;address_time
op_assign
(paren
id|byte
)paren
id|calc_clk
c_func
(paren
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|setup_time
comma
id|bus_speed
)paren
suffix:semicolon
multiline_comment|/* let&squot;s calc the active and recovery time clocks */
id|clk1
op_assign
id|calc_clk
c_func
(paren
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
comma
id|bus_speed
)paren
suffix:semicolon
multiline_comment|/* calc recovery timing */
id|clk2
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|cycle_time
op_minus
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
op_minus
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|setup_time
suffix:semicolon
id|clk2
op_assign
id|calc_clk
c_func
(paren
id|clk2
comma
id|bus_speed
)paren
suffix:semicolon
id|clk1
op_assign
(paren
id|clk1
op_lshift
l_int|4
)paren
op_or
id|clk2
suffix:semicolon
multiline_comment|/* combine active and recovery clocks */
multiline_comment|/* note: we use the same values for 16bit IOR and IOW&n;         *&t;those are all the same, since I don&squot;t have other&n;&t; *&t;timings than those from ide_modes.h&n;&t; */
id|p_pclk-&gt;time_16r
op_assign
(paren
id|byte
)paren
id|clk1
suffix:semicolon
id|p_pclk-&gt;time_16w
op_assign
(paren
id|byte
)paren
id|clk1
suffix:semicolon
multiline_comment|/* what are good values for 8bit ?? */
id|p_pclk-&gt;time_8
op_assign
(paren
id|byte
)paren
id|clk1
suffix:semicolon
)brace
multiline_comment|/*&n; * set DMA mode a specific channel for CY82C693&n; */
DECL|function|cy82c693_dma_enable
r_static
r_void
id|cy82c693_dma_enable
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|mode
comma
r_int
id|single
)paren
(brace
id|byte
id|index
suffix:semicolon
id|byte
id|data
suffix:semicolon
r_if
c_cond
(paren
id|mode
OG
l_int|2
)paren
multiline_comment|/* make sure we set a valid mode */
id|mode
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|mode
OG
id|drive-&gt;id-&gt;tDMA
)paren
multiline_comment|/* to be absolutly sure we have a valid mode */
id|mode
op_assign
id|drive-&gt;id-&gt;tDMA
suffix:semicolon
id|index
op_assign
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
op_eq
l_int|0
)paren
ques
c_cond
id|CY82_INDEX_CHANNEL0
suffix:colon
id|CY82_INDEX_CHANNEL1
suffix:semicolon
macro_line|#if CY82C693_DEBUG_LOGS
multiline_comment|/* for debug let&squot;s show the previous values */
id|OUT_BYTE
c_func
(paren
id|index
comma
id|CY82_INDEX_PORT
)paren
suffix:semicolon
id|data
op_assign
id|IN_BYTE
c_func
(paren
id|CY82_DATA_PORT
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s (ch=%d, dev=%d): DMA mode is %d (single=%d)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
comma
id|drive-&gt;select.b.unit
comma
(paren
id|data
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|data
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_LOGS */
id|data
op_assign
(paren
id|byte
)paren
id|mode
op_or
(paren
id|byte
)paren
(paren
id|single
op_lshift
l_int|2
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|index
comma
id|CY82_INDEX_PORT
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|data
comma
id|CY82_DATA_PORT
)paren
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s (ch=%d, dev=%d): set DMA mode to %d (single=%d)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|channel
comma
id|drive-&gt;select.b.unit
comma
id|mode
comma
id|single
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
multiline_comment|/* &n;&t; * note: below we set the value for Bus Master IDE TimeOut Register&n;&t; * I&squot;m not absolutly sure what this does, but it solved my problem&n;&t; * with IDE DMA and sound, so I now can play sound and work with&n;&t; * my IDE driver at the same time :-)&n;&t; *&n;&t; * If you know the correct (best) value for this register please&n;&t; * let me know - ASK&n;&t; */
id|data
op_assign
id|BUSMASTER_TIMEOUT
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|CY82_INDEX_TIMEOUT
comma
id|CY82_INDEX_PORT
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|data
comma
id|CY82_DATA_PORT
)paren
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO&t;
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: Set IDE Bus Master TimeOut Register to 0x%X&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|data
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
)brace
multiline_comment|/* &n; * used to set DMA mode for CY82C693 (single and multi modes)&n; */
DECL|function|cy82c693_dmaproc
r_static
r_int
id|cy82c693_dmaproc
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
multiline_comment|/*&n;&t; * if the function is dma on, set dma mode for drive everything&n;&t; * else is done by the defaul func&n;&t; */
r_if
c_cond
(paren
id|func
op_eq
id|ide_dma_on
)paren
(brace
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;dma_on: %s&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
r_if
c_cond
(paren
id|id
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Enable DMA on any drive that has DMA (multi or single) enabled */
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
multiline_comment|/* regular DMA */
r_int
id|mmode
comma
id|smode
suffix:semicolon
id|mmode
op_assign
id|id-&gt;dma_mword
op_amp
(paren
id|id-&gt;dma_mword
op_rshift
l_int|8
)paren
suffix:semicolon
id|smode
op_assign
id|id-&gt;dma_1word
op_amp
(paren
id|id-&gt;dma_1word
op_rshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmode
op_ne
l_int|0
)paren
id|cy82c693_dma_enable
c_func
(paren
id|drive
comma
(paren
id|mmode
op_rshift
l_int|1
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* enable multi */
r_else
r_if
c_cond
(paren
id|smode
op_ne
l_int|0
)paren
id|cy82c693_dma_enable
c_func
(paren
id|drive
comma
(paren
id|smode
op_rshift
l_int|1
)paren
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* enable single */
)brace
)brace
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
)brace
multiline_comment|/*&n; * tune ide drive - set PIO mode&n; */
DECL|function|cy82c693_tune_drive
r_static
r_void
id|cy82c693_tune_drive
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
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
id|pci_dev
op_star
id|dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|pio_clocks_t
id|pclk
suffix:semicolon
r_int
r_int
id|addrCtrl
suffix:semicolon
multiline_comment|/* select primary or secondary channel */
r_if
c_cond
(paren
id|hwif-&gt;index
OG
l_int|0
)paren
multiline_comment|/* drive is on the secondary channel */
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
macro_line|#if CY82C693_DEBUG_LOGS
multiline_comment|/* for debug let&squot;s show the register values */
r_if
c_cond
(paren
id|drive-&gt;select.b.unit
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * get master drive registers               &t;&n;&t;&t; * address setup control register&n;&t;&t; * is 32 bit !!!&n;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
op_amp
id|addrCtrl
)paren
suffix:semicolon
id|addrCtrl
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* now let&squot;s get the remaining registers */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_IOR
comma
op_amp
id|pclk.time_16r
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_IOW
comma
op_amp
id|pclk.time_16w
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_8BIT
comma
op_amp
id|pclk.time_8
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * set slave drive registers&n;&t;&t; * address setup control register&n;&t;&t; * is 32 bit !!!&n;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
op_amp
id|addrCtrl
)paren
suffix:semicolon
id|addrCtrl
op_and_assign
l_int|0xF0
suffix:semicolon
id|addrCtrl
op_rshift_assign
l_int|4
suffix:semicolon
multiline_comment|/* now let&squot;s get the remaining registers */
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_IOR
comma
op_amp
id|pclk.time_16r
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_IOW
comma
op_amp
id|pclk.time_16w
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_8BIT
comma
op_amp
id|pclk.time_8
)paren
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s (ch=%d, dev=%d): PIO timing is (addr=0x%X, ior=0x%X, iow=0x%X, 8bit=0x%X)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|hwif-&gt;channel
comma
id|drive-&gt;select.b.unit
comma
id|addrCtrl
comma
id|pclk.time_16r
comma
id|pclk.time_16w
comma
id|pclk.time_8
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_LOGS */
multiline_comment|/* first let&squot;s calc the pio modes */
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
id|CY82C693_MAX_PIO
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: Selected PIO mode %d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
id|compute_clocks
c_func
(paren
id|pio
comma
op_amp
id|pclk
)paren
suffix:semicolon
multiline_comment|/* let&squot;s calc the values for this PIO mode */
multiline_comment|/* now let&squot;s write  the clocks registers */
r_if
c_cond
(paren
id|drive-&gt;select.b.unit
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * set master drive&n;&t;&t; * address setup control register&n;&t;&t; * is 32 bit !!!&n;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
op_amp
id|addrCtrl
)paren
suffix:semicolon
id|addrCtrl
op_and_assign
(paren
op_complement
l_int|0xF
)paren
suffix:semicolon
id|addrCtrl
op_or_assign
(paren
r_int
r_int
)paren
id|pclk.address_time
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
id|addrCtrl
)paren
suffix:semicolon
multiline_comment|/* now let&squot;s set the remaining registers */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_IOR
comma
id|pclk.time_16r
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_IOW
comma
id|pclk.time_16w
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_MASTER_8BIT
comma
id|pclk.time_8
)paren
suffix:semicolon
id|addrCtrl
op_and_assign
l_int|0xF
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * set slave drive&n;&t;&t; * address setup control register&n;&t;&t; * is 32 bit !!!&n;&t;&t; */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
op_amp
id|addrCtrl
)paren
suffix:semicolon
id|addrCtrl
op_and_assign
(paren
op_complement
l_int|0xF0
)paren
suffix:semicolon
id|addrCtrl
op_or_assign
(paren
(paren
r_int
r_int
)paren
id|pclk.address_time
op_lshift
l_int|4
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|CY82_IDE_ADDRSETUP
comma
id|addrCtrl
)paren
suffix:semicolon
multiline_comment|/* now let&squot;s set the remaining registers */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_IOR
comma
id|pclk.time_16r
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_IOW
comma
id|pclk.time_16w
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|CY82_IDE_SLAVE_8BIT
comma
id|pclk.time_8
)paren
suffix:semicolon
id|addrCtrl
op_rshift_assign
l_int|4
suffix:semicolon
id|addrCtrl
op_and_assign
l_int|0xF
suffix:semicolon
)brace
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s (ch=%d, dev=%d): set PIO timing to (addr=0x%X, ior=0x%X, iow=0x%X, 8bit=0x%X)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|hwif-&gt;channel
comma
id|drive-&gt;select.b.unit
comma
id|addrCtrl
comma
id|pclk.time_16r
comma
id|pclk.time_16w
comma
id|pclk.time_8
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
)brace
multiline_comment|/*&n; * this function is called during init and is used to setup the cy82c693 chip&n; */
multiline_comment|/*&n; * FIXME! &quot;pci_init_cy82c693&quot; really should replace&n; * the &quot;init_cy82c693_chip&quot;, it is the correct location to tinker/setup&n; * the device prior to INIT.&n; */
DECL|function|pci_init_cy82c693
r_int
r_int
id|__init
id|pci_init_cy82c693
c_func
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
macro_line|#ifdef CY82C693_SETDMA_CLOCK
id|byte
id|data
suffix:semicolon
macro_line|#endif /* CY82C693_SETDMA_CLOCK */ 
multiline_comment|/* write info about this verion of the driver */
id|printk
(paren
id|KERN_INFO
id|CY82_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CY82C693_SETDMA_CLOCK
multiline_comment|/* okay let&squot;s set the DMA clock speed */
id|OUT_BYTE
c_func
(paren
id|CY82_INDEX_CTRLREG1
comma
id|CY82_INDEX_PORT
)paren
suffix:semicolon
id|data
op_assign
id|IN_BYTE
c_func
(paren
id|CY82_DATA_PORT
)paren
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: Peripheral Configuration Register: 0x%X&bslash;n&quot;
comma
id|name
comma
id|data
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
multiline_comment|/*&n;&t; * for some reason sometimes the DMA controller&n;&t; * speed is set to ATCLK/2 ???? - we fix this here&n;&t; * &n;&t; * note: i don&squot;t know what causes this strange behaviour,&n;&t; *       but even changing the dma speed doesn&squot;t solve it :-(&n;&t; *       the ide performance is still only half the normal speed &n;&t; * &n;&t; *       if anybody knows what goes wrong with my machine, please&n;&t; *       let me know - ASK&n;         */
id|data
op_or_assign
l_int|0x03
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|CY82_INDEX_CTRLREG1
comma
id|CY82_INDEX_PORT
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|data
comma
id|CY82_DATA_PORT
)paren
suffix:semicolon
macro_line|#if CY82C693_DEBUG_INFO
id|printk
(paren
id|KERN_INFO
l_string|&quot;%s: New Peripheral Configuration Register: 0x%X&bslash;n&quot;
comma
id|name
comma
id|data
)paren
suffix:semicolon
macro_line|#endif /* CY82C693_DEBUG_INFO */
macro_line|#endif /* CY82C693_SETDMA_CLOCK */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * the init function - called for each ide channel once&n; */
DECL|function|ide_init_cy82c693
r_void
id|__init
id|ide_init_cy82c693
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
id|hwif-&gt;chipset
op_assign
id|ide_cy82c693
suffix:semicolon
id|hwif-&gt;tuneproc
op_assign
op_amp
id|cy82c693_tune_drive
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
id|cy82c693_dmaproc
suffix:semicolon
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
)brace
eof
