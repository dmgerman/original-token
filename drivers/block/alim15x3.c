multiline_comment|/*&n; * linux/drivers/block/alim15x3.c&t;Version 0.04&t;Feb. 8, 1999&n; *&n; *  Copyright (C) 1998-99 Michel Aubry, Maintainer&n; *  Copyright (C) 1998-99 Andrzej Krzysztofowicz, Maintainer&n; *  Copyright (C) 1998-99 Andre Hedrick, Integrater and Maintainer&n; *&n; *  (U)DMA capable version of ali 1533/1543(C)&n; *&n; *  Default disable (U)DMA on all devices execpt hard disks.&n; *  This measure of overkill is needed to stablize the chipset code.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|DISPLAY_ALI_TIMINGS
mdefine_line|#define DISPLAY_ALI_TIMINGS
macro_line|#if defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
r_static
r_int
id|ali_get_info
c_func
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
comma
r_int
id|dummy
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|ali_display_info
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ide-proc.c */
DECL|variable|bmide_dev
r_struct
id|pci_dev
op_star
id|bmide_dev
suffix:semicolon
DECL|variable|fifo
r_char
op_star
id|fifo
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;FIFO Off&quot;
comma
l_string|&quot;FIFO On &quot;
comma
l_string|&quot;DMA mode&quot;
comma
l_string|&quot;PIO mode&quot;
)brace
suffix:semicolon
DECL|variable|udmaT
r_char
op_star
id|udmaT
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;1.5T&quot;
comma
l_string|&quot;  2T&quot;
comma
l_string|&quot;2.5T&quot;
comma
l_string|&quot;  3T&quot;
comma
l_string|&quot;3.5T&quot;
comma
l_string|&quot;  4T&quot;
comma
l_string|&quot;  6T&quot;
comma
l_string|&quot;  8T&quot;
)brace
suffix:semicolon
DECL|variable|channel_status
r_char
op_star
id|channel_status
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;OK            &quot;
comma
l_string|&quot;busy          &quot;
comma
l_string|&quot;DRQ           &quot;
comma
l_string|&quot;DRQ busy      &quot;
comma
l_string|&quot;error         &quot;
comma
l_string|&quot;error busy    &quot;
comma
l_string|&quot;error DRQ     &quot;
comma
l_string|&quot;error DRQ busy&quot;
)brace
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|pci_init_ali15x3
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
id|byte
id|confreg0
op_assign
l_int|0
comma
id|confreg1
op_assign
l_int|0
comma
id|progif
op_assign
l_int|0
suffix:semicolon
r_int
id|errors
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x50
comma
op_amp
id|confreg1
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|confreg1
op_amp
l_int|0x02
)paren
)paren
r_if
c_cond
(paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x50
comma
id|confreg1
op_or
l_int|0x02
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_PROG
comma
op_amp
id|progif
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|progif
op_amp
l_int|0x40
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The way to enable them is to set progif&n;&t;&t; * writable at 0x4Dh register, and set bit 6&n;&t;&t; * of progif to 1:&n;&t;&t; */
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x4d
comma
op_amp
id|confreg0
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
id|confreg0
op_amp
l_int|0x80
)paren
r_if
c_cond
(paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4d
comma
id|confreg0
op_amp
op_complement
l_int|0x80
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_PROG
comma
id|progif
op_or
l_int|0x40
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
r_if
c_cond
(paren
id|confreg0
op_amp
l_int|0x80
)paren
r_if
c_cond
(paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4d
comma
id|confreg0
)paren
)paren
id|errors
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_PROG
comma
op_amp
id|progif
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|progif
op_amp
l_int|0x40
)paren
)paren
)paren
r_goto
id|veryspecialsettingserror
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: enabled read of IDE channels state (en/dis-abled) %s.&bslash;n&quot;
comma
id|name
comma
id|errors
ques
c_cond
l_string|&quot;with Error(s)&quot;
suffix:colon
l_string|&quot;Succeeded&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|veryspecialsettingserror
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: impossible to enable read of IDE channels state (en/dis-abled)!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ali15x3_dmaproc
r_int
id|ali15x3_dmaproc
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
r_if
c_cond
(paren
id|drive-&gt;media
op_eq
id|ide_cdrom
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
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
id|byte
id|cd_dma_fifo
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
op_amp
id|cd_dma_fifo
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|id-&gt;field_valid
op_amp
l_int|4
)paren
op_logical_or
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
)paren
op_logical_and
(paren
id|id-&gt;capability
op_amp
l_int|1
)paren
op_logical_and
id|hwif-&gt;autodma
)paren
(brace
r_int
r_int
id|dma_set_bit
op_assign
id|hwif-&gt;dma_base
op_plus
l_int|2
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|cd_dma_fifo
op_amp
l_int|0x02
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|cd_dma_fifo
op_amp
op_complement
l_int|0x02
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|cd_dma_fifo
op_or
l_int|0x01
)paren
suffix:semicolon
macro_line|#else
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|cd_dma_fifo
op_or
l_int|0x01
op_or
l_int|0x02
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|drive-&gt;select.b.unit
op_amp
l_int|0x01
)paren
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_set_bit
)paren
op_or
l_int|0x40
comma
id|dma_set_bit
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|dma_set_bit
)paren
op_or
l_int|0x20
comma
id|dma_set_bit
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|cd_dma_fifo
op_amp
l_int|0x01
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|cd_dma_fifo
op_amp
op_complement
l_int|0x01
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x53
comma
id|cd_dma_fifo
op_or
l_int|0x02
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
)paren
(brace
r_return
id|ide_dmaproc
c_func
(paren
id|ide_dma_off_quietly
comma
id|drive
)paren
suffix:semicolon
)brace
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
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|ide_init_ali15x3
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
suffix:semicolon
id|byte
id|ideic
comma
id|inmir
suffix:semicolon
id|byte
id|irq_routing_table
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
l_int|9
comma
l_int|3
comma
l_int|10
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|6
comma
l_int|1
comma
l_int|11
comma
l_int|0
comma
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|15
)brace
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|hwif-&gt;channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
multiline_comment|/* look for ISA bridge */
r_if
c_cond
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_AL
op_logical_and
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_AL_M1533
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x58
comma
op_amp
id|ideic
)paren
suffix:semicolon
id|ideic
op_assign
id|ideic
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hwif-&gt;channel
op_logical_and
id|ideic
op_eq
l_int|0x03
)paren
op_logical_or
(paren
op_logical_neg
id|hwif-&gt;channel
op_logical_and
op_logical_neg
id|ideic
)paren
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x44
comma
op_amp
id|inmir
)paren
suffix:semicolon
id|inmir
op_assign
id|inmir
op_amp
l_int|0x0f
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|irq_routing_table
(braket
id|inmir
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|hwif-&gt;channel
op_logical_and
op_logical_neg
(paren
id|ideic
op_amp
l_int|0x01
)paren
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x75
comma
op_amp
id|inmir
)paren
suffix:semicolon
id|inmir
op_assign
id|inmir
op_amp
l_int|0x0f
suffix:semicolon
id|hwif-&gt;irq
op_assign
id|irq_routing_table
(braket
id|inmir
)braket
suffix:semicolon
)brace
)brace
macro_line|#if defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
id|bmide_dev
op_assign
id|hwif-&gt;pci_dev
suffix:semicolon
id|ali_display_info
op_assign
op_amp
id|ali_get_info
suffix:semicolon
macro_line|#endif  /* defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
r_if
c_cond
(paren
id|hwif-&gt;dma_base
)paren
id|hwif-&gt;dmaproc
op_assign
op_amp
id|ali15x3_dmaproc
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS)
DECL|function|ali_get_info
r_static
r_int
id|ali_get_info
c_func
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
comma
r_int
id|dummy
)paren
(brace
id|byte
id|reg53h
comma
id|reg5xh
comma
id|reg5yh
comma
id|reg5xh1
comma
id|reg5yh1
suffix:semicolon
r_int
r_int
id|bibma
suffix:semicolon
id|byte
id|c0
comma
id|c1
suffix:semicolon
id|byte
id|rev
comma
id|tmp
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_char
op_star
id|q
suffix:semicolon
multiline_comment|/* fetch rev. */
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x08
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev
op_ge
l_int|0xc1
)paren
multiline_comment|/* M1543C or newer */
id|udmaT
(braket
l_int|7
)braket
op_assign
l_string|&quot; ???&quot;
suffix:semicolon
r_else
id|fifo
(braket
l_int|3
)braket
op_assign
l_string|&quot;   ???  &quot;
suffix:semicolon
multiline_comment|/* first fetch bibma: */
id|pci_read_config_dword
c_func
(paren
id|bmide_dev
comma
l_int|0x20
comma
op_amp
id|bibma
)paren
suffix:semicolon
id|bibma
op_assign
(paren
id|bibma
op_amp
l_int|0xfff0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * at that point bibma+0x2 et bibma+0xa are byte&n;&t; * registers to investigate:&n;&t; */
id|c0
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x02
)paren
suffix:semicolon
id|c1
op_assign
id|inb
c_func
(paren
(paren
r_int
r_int
)paren
id|bibma
op_plus
l_int|0x0a
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n                                Ali M15x3 Chipset.&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;                                ------------------&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x78
comma
op_amp
id|reg53h
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PCI Clock: %d.&bslash;n&quot;
comma
id|reg53h
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x53
comma
op_amp
id|reg53h
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;CD_ROM FIFO:%s, CD_ROM DMA:%s&bslash;n&quot;
comma
(paren
id|reg53h
op_amp
l_int|0x02
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
comma
(paren
id|reg53h
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x74
comma
op_amp
id|reg53h
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;FIFO Status: contains %d Words, runs%s%s&bslash;n&bslash;n&quot;
comma
(paren
id|reg53h
op_amp
l_int|0x3f
)paren
comma
(paren
id|reg53h
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot; OVERWR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|reg53h
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot; OVERRD.&quot;
suffix:colon
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;-------------------primary channel-------------------secondary channel---------&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x09
comma
op_amp
id|reg53h
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;channel status:       %s                               %s&bslash;n&quot;
comma
(paren
id|reg53h
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;On &quot;
suffix:colon
l_string|&quot;Off&quot;
comma
(paren
id|reg53h
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;On &quot;
suffix:colon
l_string|&quot;Off&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;both channels togth:  %s                               %s&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;No &quot;
suffix:colon
l_string|&quot;Yes&quot;
comma
(paren
id|c1
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;No &quot;
suffix:colon
l_string|&quot;Yes&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x76
comma
op_amp
id|reg53h
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Channel state:        %s                    %s&bslash;n&quot;
comma
id|channel_status
(braket
id|reg53h
op_amp
l_int|0x07
)braket
comma
id|channel_status
(braket
(paren
id|reg53h
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)braket
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x58
comma
op_amp
id|reg5xh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5c
comma
op_amp
id|reg5yh
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Add. Setup Timing:    %dT                                %dT&bslash;n&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x07
)paren
ques
c_cond
(paren
id|reg5xh
op_amp
l_int|0x07
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5yh
op_amp
l_int|0x07
)paren
ques
c_cond
(paren
id|reg5yh
op_amp
l_int|0x07
)paren
suffix:colon
l_int|8
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x59
comma
op_amp
id|reg5xh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5d
comma
op_amp
id|reg5yh
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Command Act. Count:   %dT                                %dT&bslash;n&quot;
l_string|&quot;Command Rec. Count:   %dT                               %dT&bslash;n&bslash;n&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5xh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5yh
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5yh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5xh
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5xh
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
comma
(paren
id|reg5yh
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5yh
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;----------------drive0-----------drive1------------drive0-----------drive1------&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;DMA enabled:      %s              %s               %s              %s&bslash;n&quot;
comma
(paren
id|c0
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
comma
(paren
id|c0
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
comma
(paren
id|c1
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
comma
(paren
id|c1
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No &quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x54
comma
op_amp
id|reg5xh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x55
comma
op_amp
id|reg5yh
)paren
suffix:semicolon
id|q
op_assign
l_string|&quot;FIFO threshold:   %2d Words         %2d Words          %2d Words         %2d Words&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|rev
OL
l_int|0xc1
)paren
(brace
r_if
c_cond
(paren
(paren
id|rev
op_eq
l_int|0x20
)paren
op_logical_and
(paren
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x4f
comma
op_amp
id|tmp
)paren
comma
(paren
id|tmp
op_and_assign
l_int|0x20
)paren
)paren
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
id|q
comma
l_int|8
comma
l_int|8
comma
l_int|8
comma
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
id|q
comma
(paren
id|reg5xh
op_amp
l_int|0x03
)paren
op_plus
l_int|12
comma
(paren
(paren
id|reg5xh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|12
comma
(paren
id|reg5yh
op_amp
l_int|0x03
)paren
op_plus
l_int|12
comma
(paren
(paren
id|reg5yh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|12
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
id|q
comma
(paren
id|tmp
op_assign
(paren
id|reg5xh
op_amp
l_int|0x03
)paren
)paren
ques
c_cond
(paren
id|tmp
op_lshift
l_int|3
)paren
suffix:colon
l_int|4
comma
(paren
id|tmp
op_assign
(paren
(paren
id|reg5xh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
)paren
ques
c_cond
(paren
id|tmp
op_lshift
l_int|3
)paren
suffix:colon
l_int|4
comma
(paren
id|tmp
op_assign
(paren
id|reg5yh
op_amp
l_int|0x03
)paren
)paren
ques
c_cond
(paren
id|tmp
op_lshift
l_int|3
)paren
suffix:colon
l_int|4
comma
(paren
id|tmp
op_assign
(paren
(paren
id|reg5yh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
)paren
ques
c_cond
(paren
id|tmp
op_lshift
l_int|3
)paren
suffix:colon
l_int|4
)paren
suffix:semicolon
)brace
macro_line|#if 0
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;FIFO threshold:   %2d Words         %2d Words          %2d Words         %2d Words&bslash;n&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x03
)paren
op_plus
l_int|12
comma
(paren
(paren
id|reg5xh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|12
comma
(paren
id|reg5yh
op_amp
l_int|0x03
)paren
op_plus
l_int|12
comma
(paren
(paren
id|reg5yh
op_amp
l_int|0x30
)paren
op_rshift
l_int|4
)paren
op_plus
l_int|12
)paren
suffix:semicolon
macro_line|#endif
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;FIFO mode:        %s         %s          %s         %s&bslash;n&quot;
comma
id|fifo
(braket
(paren
(paren
id|reg5xh
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
)braket
comma
id|fifo
(braket
(paren
(paren
id|reg5xh
op_amp
l_int|0xc0
)paren
op_rshift
l_int|6
)paren
)braket
comma
id|fifo
(braket
(paren
(paren
id|reg5yh
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
)braket
comma
id|fifo
(braket
(paren
(paren
id|reg5yh
op_amp
l_int|0xc0
)paren
op_rshift
l_int|6
)paren
)braket
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5a
comma
op_amp
id|reg5xh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5b
comma
op_amp
id|reg5xh1
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5e
comma
op_amp
id|reg5yh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x5f
comma
op_amp
id|reg5yh1
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
multiline_comment|/*&n;&t;&t;&quot;------------------drive0-----------drive1------------drive0-----------drive1------&bslash;n&quot;)*/
l_string|&quot;Dt RW act. Cnt    %2dT              %2dT               %2dT              %2dT&bslash;n&quot;
l_string|&quot;Dt RW rec. Cnt    %2dT              %2dT               %2dT              %2dT&bslash;n&bslash;n&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5xh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5xh1
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5xh1
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5yh
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5yh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5yh1
op_amp
l_int|0x70
)paren
ques
c_cond
(paren
(paren
id|reg5yh1
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)paren
suffix:colon
l_int|8
comma
(paren
id|reg5xh
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5xh
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
comma
(paren
id|reg5xh1
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5xh1
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
comma
(paren
id|reg5yh
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5yh
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
comma
(paren
id|reg5yh1
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|reg5yh1
op_amp
l_int|0x0f
)paren
suffix:colon
l_int|16
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;-----------------------------------UDMA Timings--------------------------------&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x56
comma
op_amp
id|reg5xh
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|bmide_dev
comma
l_int|0x57
comma
op_amp
id|reg5yh
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;UDMA:             %s               %s                %s               %s&bslash;n&quot;
l_string|&quot;UDMA timings:     %s             %s              %s             %s&bslash;n&bslash;n&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x08
)paren
ques
c_cond
l_string|&quot;OK&quot;
suffix:colon
l_string|&quot;No&quot;
comma
(paren
id|reg5xh
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;OK&quot;
suffix:colon
l_string|&quot;No&quot;
comma
(paren
id|reg5yh
op_amp
l_int|0x08
)paren
ques
c_cond
l_string|&quot;OK&quot;
suffix:colon
l_string|&quot;No&quot;
comma
(paren
id|reg5yh
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;OK&quot;
suffix:colon
l_string|&quot;No&quot;
comma
id|udmaT
(braket
(paren
id|reg5xh
op_amp
l_int|0x07
)paren
)braket
comma
id|udmaT
(braket
(paren
id|reg5xh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)braket
comma
id|udmaT
(braket
id|reg5yh
op_amp
l_int|0x07
)braket
comma
id|udmaT
(braket
(paren
id|reg5yh
op_amp
l_int|0x70
)paren
op_rshift
l_int|4
)braket
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buffer
suffix:semicolon
multiline_comment|/* =&gt; must be less than 4k! */
)brace
macro_line|#endif  /* defined(DISPLAY_ALI_TIMINGS) &amp;&amp; defined(CONFIG_PROC_FS) */
eof
