multiline_comment|/*&n; *  linux/drivers/block/cmd640.c&t;Version 0.07  Jan 27, 1996&n; *&n; *  Copyright (C) 1995-1996  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author/Maintainer:  abramov@cecmow.enet.dec.com (Igor Abramov)&n; *&n; *  This file provides support for the advanced features and bugs&n; *  of IDE interfaces using the CMD Technologies 0640 IDE interface chip.&n; *&n; *  Version 0.01&t;Initial version, hacked out of ide.c,&n; *&t;&t;&t;and #include&squot;d rather than compiled separately.&n; *&t;&t;&t;This will get cleaned up in a subsequent release.&n; *&n; *  Version 0.02&t;Fixes for vlb initialization code, enable&n; *&t;&t;&t;read-ahead for versions &squot;B&squot; and &squot;C&squot; of chip by&n; *&t;&t;&t;default, some code cleanup.&n; *&n; *  Version 0.03&t;Added reset of secondary interface,&n; *&t;&t;&t;and black list for devices which are not compatible&n; *&t;&t;&t;with read ahead mode. Separate function for setting&n; *&t;&t;&t;readahead is added, possibly it will be called some&n; *&t;&t;&t;day from ioctl processing code.&n; *  &n; *  Version 0.04&t;Now configs/compiles separate from ide.c  -ml &n; *&n; *  Version 0.05&t;Major rewrite of interface timing code.&n; *&t;&t;&t;Added new function cmd640_set_mode to set PIO mode&n; *&t;&t;&t;from ioctl call. New drives added to black list.&n; *&n; *  Version 0.06&t;More code cleanup. Readahead is enabled only for&n; *&t;&t;&t;detected hard drives, not included in readahed&n; *&t;&t;&t;black list.&n; * &n; *  Version 0.07&t;Changed to more conservative drive tuning policy.&n; *&t;&t;&t;Unknown drives, which report PIO &lt; 4 are set to &n; *&t;&t;&t;(reported_PIO - 1) if it is supported, or to PIO0.&n; *&t;&t;&t;List of known drives extended by info provided by&n; *&t;&t;&t;CMD at their ftp site.&n; *&n; *  Version 0.08&t;Added autotune/noautotune support.  -ml&n; *&t;&t;&t;&n; */
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide.h&quot;
macro_line|#include &quot;ide_modes.h&quot;
DECL|variable|cmd640_vlb
r_int
id|cmd640_vlb
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * CMD640 specific registers definition.&n; */
DECL|macro|VID
mdefine_line|#define VID&t;&t;0x00
DECL|macro|DID
mdefine_line|#define DID&t;&t;0x02
DECL|macro|PCMD
mdefine_line|#define PCMD&t;&t;0x04
DECL|macro|PSTTS
mdefine_line|#define PSTTS&t;&t;0x06
DECL|macro|REVID
mdefine_line|#define REVID&t;&t;0x08
DECL|macro|PROGIF
mdefine_line|#define PROGIF&t;&t;0x09
DECL|macro|SUBCL
mdefine_line|#define SUBCL&t;&t;0x0a
DECL|macro|BASCL
mdefine_line|#define BASCL&t;&t;0x0b
DECL|macro|BaseA0
mdefine_line|#define BaseA0&t;&t;0x10
DECL|macro|BaseA1
mdefine_line|#define BaseA1&t;&t;0x14
DECL|macro|BaseA2
mdefine_line|#define BaseA2&t;&t;0x18
DECL|macro|BaseA3
mdefine_line|#define BaseA3&t;&t;0x1c
DECL|macro|INTLINE
mdefine_line|#define INTLINE&t;&t;0x3c
DECL|macro|INPINE
mdefine_line|#define INPINE&t;&t;0x3d
DECL|macro|CFR
mdefine_line|#define&t;CFR&t;&t;0x50
DECL|macro|CFR_DEVREV
mdefine_line|#define   CFR_DEVREV&t;&t;0x03
DECL|macro|CFR_IDE01INTR
mdefine_line|#define   CFR_IDE01INTR&t;&t;0x04
DECL|macro|CFR_DEVID
mdefine_line|#define&t;  CFR_DEVID&t;&t;0x18
DECL|macro|CFR_AT_VESA_078h
mdefine_line|#define&t;  CFR_AT_VESA_078h&t;0x20
DECL|macro|CFR_DSA1
mdefine_line|#define&t;  CFR_DSA1&t;&t;0x40
DECL|macro|CFR_DSA0
mdefine_line|#define&t;  CFR_DSA0&t;&t;0x80
DECL|macro|CNTRL
mdefine_line|#define CNTRL&t;&t;0x51
DECL|macro|CNTRL_DIS_RA0
mdefine_line|#define&t;  CNTRL_DIS_RA0&t;&t;0x40
DECL|macro|CNTRL_DIS_RA1
mdefine_line|#define   CNTRL_DIS_RA1&t;&t;0x80
DECL|macro|CNTRL_ENA_2ND
mdefine_line|#define&t;  CNTRL_ENA_2ND&t;&t;0x08
DECL|macro|CMDTIM
mdefine_line|#define&t;CMDTIM&t;&t;0x52
DECL|macro|ARTTIM0
mdefine_line|#define&t;ARTTIM0&t;&t;0x53
DECL|macro|DRWTIM0
mdefine_line|#define&t;DRWTIM0&t;&t;0x54
DECL|macro|ARTTIM1
mdefine_line|#define ARTTIM1 &t;0x55
DECL|macro|DRWTIM1
mdefine_line|#define DRWTIM1&t;&t;0x56
DECL|macro|ARTTIM23
mdefine_line|#define ARTTIM23&t;0x57
DECL|macro|DIS_RA2
mdefine_line|#define   DIS_RA2&t;&t;0x04
DECL|macro|DIS_RA3
mdefine_line|#define   DIS_RA3&t;&t;0x08
DECL|macro|DRWTIM23
mdefine_line|#define DRWTIM23&t;0x58
DECL|macro|BRST
mdefine_line|#define BRST&t;&t;0x59
DECL|variable|cmd640_tune_drive
r_static
id|ide_tuneproc_t
id|cmd640_tune_drive
suffix:semicolon
multiline_comment|/* Interface to access cmd640x registers */
DECL|variable|put_cmd640_reg
r_static
r_void
(paren
op_star
id|put_cmd640_reg
)paren
(paren
r_int
id|reg_no
comma
r_int
id|val
)paren
suffix:semicolon
DECL|variable|get_cmd640_reg
r_static
id|byte
(paren
op_star
id|get_cmd640_reg
)paren
(paren
r_int
id|reg_no
)paren
suffix:semicolon
DECL|enumerator|none
DECL|enumerator|vlb
DECL|enumerator|pci1
DECL|enumerator|pci2
r_enum
(brace
id|none
comma
id|vlb
comma
id|pci1
comma
id|pci2
)brace
suffix:semicolon
DECL|variable|bus_type
r_static
r_int
id|bus_type
op_assign
id|none
suffix:semicolon
DECL|variable|cmd640_chip_version
r_static
r_int
id|cmd640_chip_version
suffix:semicolon
DECL|variable|cmd640_key
r_static
r_int
id|cmd640_key
suffix:semicolon
DECL|variable|bus_speed
r_static
r_int
id|bus_speed
suffix:semicolon
multiline_comment|/* MHz */
multiline_comment|/*&n; * For some unknown reasons pcibios functions which read and write registers&n; * do not always work with cmd640. We use direct IO instead.&n; */
multiline_comment|/* PCI method 1 access */
DECL|function|put_cmd640_reg_pci1
r_static
r_void
id|put_cmd640_reg_pci1
c_func
(paren
r_int
id|reg_no
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
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
id|outl_p
c_func
(paren
(paren
id|reg_no
op_amp
l_int|0xfc
)paren
op_or
id|cmd640_key
comma
l_int|0xcf8
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
(paren
id|reg_no
op_amp
l_int|3
)paren
op_plus
l_int|0xcfc
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|get_cmd640_reg_pci1
r_static
id|byte
id|get_cmd640_reg_pci1
c_func
(paren
r_int
id|reg_no
)paren
(brace
id|byte
id|b
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|outl_p
c_func
(paren
(paren
id|reg_no
op_amp
l_int|0xfc
)paren
op_or
id|cmd640_key
comma
l_int|0xcf8
)paren
suffix:semicolon
id|b
op_assign
id|inb_p
c_func
(paren
l_int|0xcfc
op_plus
(paren
id|reg_no
op_amp
l_int|3
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/* PCI method 2 access (from CMD datasheet) */
DECL|function|put_cmd640_reg_pci2
r_static
r_void
id|put_cmd640_reg_pci2
c_func
(paren
r_int
id|reg_no
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
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
id|outb_p
c_func
(paren
l_int|0x10
comma
l_int|0xcf8
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|cmd640_key
op_plus
id|reg_no
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xcf8
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|get_cmd640_reg_pci2
r_static
id|byte
id|get_cmd640_reg_pci2
c_func
(paren
r_int
id|reg_no
)paren
(brace
id|byte
id|b
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|outb_p
c_func
(paren
l_int|0x10
comma
l_int|0xcf8
)paren
suffix:semicolon
id|b
op_assign
id|inb_p
c_func
(paren
id|cmd640_key
op_plus
id|reg_no
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xcf8
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/* VLB access */
DECL|function|put_cmd640_reg_vlb
r_static
r_void
id|put_cmd640_reg_vlb
c_func
(paren
r_int
id|reg_no
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
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
id|outb_p
c_func
(paren
id|reg_no
comma
id|cmd640_key
op_plus
l_int|8
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|cmd640_key
op_plus
l_int|0xc
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|get_cmd640_reg_vlb
r_static
id|byte
id|get_cmd640_reg_vlb
c_func
(paren
r_int
id|reg_no
)paren
(brace
id|byte
id|b
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|outb_p
c_func
(paren
id|reg_no
comma
id|cmd640_key
op_plus
l_int|8
)paren
suffix:semicolon
id|b
op_assign
id|inb_p
c_func
(paren
id|cmd640_key
op_plus
l_int|0xc
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for CMD640x -- pci method 1&n; */
DECL|function|probe_for_cmd640_pci1
r_static
r_int
id|probe_for_cmd640_pci1
c_func
(paren
r_void
)paren
(brace
r_int
id|id
suffix:semicolon
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0x80000000
suffix:semicolon
id|k
op_le
l_int|0x8000f800
suffix:semicolon
id|k
op_add_assign
l_int|0x800
)paren
(brace
id|outl
c_func
(paren
id|k
comma
l_int|0xcf8
)paren
suffix:semicolon
id|id
op_assign
id|inl
c_func
(paren
l_int|0xcfc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_ne
l_int|0x06401095
)paren
r_continue
suffix:semicolon
id|put_cmd640_reg
op_assign
id|put_cmd640_reg_pci1
suffix:semicolon
id|get_cmd640_reg
op_assign
id|get_cmd640_reg_pci1
suffix:semicolon
id|cmd640_key
op_assign
id|k
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for CMD640x -- pci method 2&n; */
DECL|function|probe_for_cmd640_pci2
r_static
r_int
id|probe_for_cmd640_pci2
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|v_id
suffix:semicolon
r_int
id|d_id
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0xc000
suffix:semicolon
id|i
op_le
l_int|0xcf00
suffix:semicolon
id|i
op_add_assign
l_int|0x100
)paren
(brace
id|outb
c_func
(paren
l_int|0x10
comma
l_int|0xcf8
)paren
suffix:semicolon
id|v_id
op_assign
id|inw
c_func
(paren
id|i
)paren
suffix:semicolon
id|d_id
op_assign
id|inw
c_func
(paren
id|i
op_plus
l_int|2
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0xcf8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v_id
op_ne
l_int|0x1095
op_logical_or
id|d_id
op_ne
l_int|0x640
)paren
r_continue
suffix:semicolon
id|put_cmd640_reg
op_assign
id|put_cmd640_reg_pci2
suffix:semicolon
id|get_cmd640_reg
op_assign
id|get_cmd640_reg_pci2
suffix:semicolon
id|cmd640_key
op_assign
id|i
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for CMD640x -- vlb&n; */
DECL|function|probe_for_cmd640_vlb
r_static
r_int
id|probe_for_cmd640_vlb
c_func
(paren
r_void
)paren
(brace
id|byte
id|b
suffix:semicolon
id|outb
c_func
(paren
id|CFR
comma
l_int|0x178
)paren
suffix:semicolon
id|b
op_assign
id|inb
c_func
(paren
l_int|0x17c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
l_int|0xff
op_logical_or
id|b
op_eq
l_int|0
op_logical_or
(paren
id|b
op_amp
id|CFR_AT_VESA_078h
)paren
)paren
(brace
id|outb
c_func
(paren
id|CFR
comma
l_int|0x78
)paren
suffix:semicolon
id|b
op_assign
id|inb
c_func
(paren
l_int|0x7c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
l_int|0xff
op_logical_or
id|b
op_eq
l_int|0
op_logical_or
op_logical_neg
(paren
id|b
op_amp
id|CFR_AT_VESA_078h
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cmd640_key
op_assign
l_int|0x70
suffix:semicolon
)brace
r_else
(brace
id|cmd640_key
op_assign
l_int|0x170
suffix:semicolon
)brace
id|put_cmd640_reg
op_assign
id|put_cmd640_reg_vlb
suffix:semicolon
id|get_cmd640_reg
op_assign
id|get_cmd640_reg_vlb
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Low level reset for controller, actually it has nothing specific for&n; * CMD640, but I don&squot;t know how to use standard reset routine before&n; * we recognized any drives.&n; */
DECL|function|cmd640_reset_controller
r_static
r_void
id|cmd640_reset_controller
c_func
(paren
r_int
id|iface_no
)paren
(brace
r_int
id|retry_count
op_assign
l_int|600
suffix:semicolon
r_int
id|base_port
op_assign
id|iface_no
ques
c_cond
l_int|0x170
suffix:colon
l_int|0x1f0
suffix:semicolon
id|outb_p
c_func
(paren
l_int|4
comma
id|base_port
op_plus
l_int|7
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|base_port
op_plus
l_int|7
)paren
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|retry_count
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|base_port
op_plus
l_int|7
)paren
op_amp
l_int|0x80
)paren
op_logical_and
id|retry_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retry_count
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;cmd640: failed to reset controller %d&bslash;n&quot;
comma
id|iface_no
)paren
suffix:semicolon
macro_line|#if 0&t;
r_else
id|printk
c_func
(paren
l_string|&quot;cmd640: controller %d reset [%d]&bslash;n&quot;
comma
id|iface_no
comma
id|retry_count
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Probe for Cmd640x and initialize it if found&n; */
DECL|function|ide_probe_for_cmd640x
r_int
id|ide_probe_for_cmd640x
c_func
(paren
r_void
)paren
(brace
r_int
id|second_port
suffix:semicolon
id|byte
id|b
suffix:semicolon
r_if
c_cond
(paren
id|probe_for_cmd640_pci1
c_func
(paren
)paren
)paren
(brace
id|bus_type
op_assign
id|pci1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|probe_for_cmd640_pci2
c_func
(paren
)paren
)paren
(brace
id|bus_type
op_assign
id|pci2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd640_vlb
op_logical_and
id|probe_for_cmd640_vlb
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* May be remove cmd640_vlb at all, and probe in any case */
id|bus_type
op_assign
id|vlb
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* ensure this *always* gets set */
macro_line|#if 0&t;
multiline_comment|/* Dump initial state of chip registers */
r_for
c_loop
(paren
id|b
op_assign
l_int|0
suffix:semicolon
id|b
op_ne
l_int|0xff
suffix:semicolon
id|b
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %2x%c&quot;
comma
id|get_cmd640_reg
c_func
(paren
id|b
)paren
comma
(paren
(paren
id|b
op_amp
l_int|0xf
)paren
op_eq
l_int|0xf
)paren
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot;,&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * Undocumented magic. (There is no 0x5b port in specs)&n;&t; */
id|put_cmd640_reg
c_func
(paren
l_int|0x5b
comma
l_int|0xbd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_cmd640_reg
c_func
(paren
l_int|0x5b
)paren
op_ne
l_int|0xbd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide: can&squot;t initialize cmd640 -- wrong value in 0x5b&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|put_cmd640_reg
c_func
(paren
l_int|0x5b
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Documented magic.&n;&t; */
id|cmd640_chip_version
op_assign
id|get_cmd640_reg
c_func
(paren
id|CFR
)paren
op_amp
id|CFR_DEVREV
suffix:semicolon
r_if
c_cond
(paren
id|cmd640_chip_version
op_eq
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;ide: wrong CMD640 version -- 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Setup the most conservative timings for all drives,&n;&t; */
id|put_cmd640_reg
c_func
(paren
id|ARTTIM0
comma
l_int|0xc0
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|ARTTIM1
comma
l_int|0xc0
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|ARTTIM23
comma
l_int|0xcc
)paren
suffix:semicolon
multiline_comment|/* 0xc0? */
multiline_comment|/*&n;&t; * Do not initialize secondary controller for vlbus&n;&t; */
id|second_port
op_assign
(paren
id|bus_type
op_ne
id|vlb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the maximum allowed bus speed (it is safest until we&n;&t; * &t;&t;&t;&t;      find how to detect bus speed)&n;&t; * Normally PCI bus runs at 33MHz, but often works overclocked to 40&n;&t; */
id|bus_speed
op_assign
(paren
id|bus_type
op_eq
id|vlb
)paren
ques
c_cond
l_int|50
suffix:colon
l_int|40
suffix:semicolon
multiline_comment|/*&n;&t; * Setup Control Register&n;&t; */
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|CNTRL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|second_port
)paren
id|b
op_or_assign
id|CNTRL_ENA_2ND
suffix:semicolon
r_else
id|b
op_and_assign
op_complement
id|CNTRL_ENA_2ND
suffix:semicolon
multiline_comment|/*&n;&t; * Disable readahead for drives at primary interface&n;&t; */
id|b
op_or_assign
(paren
id|CNTRL_DIS_RA0
op_or
id|CNTRL_DIS_RA1
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|CNTRL
comma
id|b
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note that we assume that the first interface is at 0x1f0,&n;&t; * and that the second interface, if enabled, is at 0x170.&n;&t; */
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_cmd640
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|cmd640_tune_drive
suffix:semicolon
r_if
c_cond
(paren
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|autotune
op_eq
l_int|0
)paren
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|autotune
op_eq
l_int|0
)paren
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize 2nd IDE port, if required&n;&t; */
r_if
c_cond
(paren
id|second_port
)paren
(brace
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_assign
id|ide_cmd640
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|tuneproc
op_assign
op_amp
id|cmd640_tune_drive
suffix:semicolon
r_if
c_cond
(paren
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|autotune
op_eq
l_int|0
)paren
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|autotune
op_eq
l_int|0
)paren
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|autotune
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We reset timings, and disable read-ahead */
id|put_cmd640_reg
c_func
(paren
id|ARTTIM23
comma
(paren
id|DIS_RA2
op_or
id|DIS_RA3
)paren
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|DRWTIM23
comma
l_int|0
)paren
suffix:semicolon
id|cmd640_reset_controller
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ide: buggy CMD640%c interface at &quot;
comma
l_char|&squot;A&squot;
op_minus
l_int|1
op_plus
id|cmd640_chip_version
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bus_type
)paren
(brace
r_case
id|vlb
suffix:colon
id|printk
c_func
(paren
l_string|&quot;local bus, port 0x%x&quot;
comma
id|cmd640_key
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pci1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;pci, (0x%x)&quot;
comma
id|cmd640_key
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pci2
suffix:colon
id|printk
c_func
(paren
l_string|&quot;pci,(access method 2) (0x%x)&quot;
comma
id|cmd640_key
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Reset interface timings&n;&t; */
id|put_cmd640_reg
c_func
(paren
id|CMDTIM
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n ... serialized, secondary interface %s&bslash;n&quot;
comma
id|second_port
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|cmd640_off
r_int
id|cmd640_off
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|a
op_assign
l_int|0
suffix:semicolon
id|byte
id|b
suffix:semicolon
r_if
c_cond
(paren
id|bus_type
op_eq
id|none
op_logical_or
id|a
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|a
op_assign
l_int|1
suffix:semicolon
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|CNTRL
)paren
suffix:semicolon
id|b
op_and_assign
op_complement
id|CNTRL_ENA_2ND
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|CNTRL
comma
id|b
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Sets readahead mode for specific drive&n; *  in the future it could be called from ioctl&n; */
DECL|function|set_readahead_mode
r_static
r_void
id|set_readahead_mode
c_func
(paren
r_int
id|mode
comma
r_int
id|if_num
comma
r_int
id|dr_num
)paren
(brace
r_static
r_int
id|masks
(braket
l_int|2
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|CNTRL_DIS_RA0
comma
id|CNTRL_DIS_RA1
)brace
comma
(brace
id|DIS_RA2
comma
id|DIS_RA3
)brace
)brace
suffix:semicolon
r_int
id|port
op_assign
(paren
id|if_num
op_eq
l_int|0
)paren
ques
c_cond
id|CNTRL
suffix:colon
id|ARTTIM23
suffix:semicolon
r_int
id|mask
op_assign
id|masks
(braket
id|if_num
)braket
(braket
id|dr_num
)braket
suffix:semicolon
id|byte
id|b
suffix:semicolon
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
)paren
id|b
op_and_assign
op_complement
id|mask
suffix:semicolon
multiline_comment|/* Enable readahead for specific drive */
r_else
id|b
op_or_assign
id|mask
suffix:semicolon
multiline_comment|/* Disable readahed for specific drive */
id|put_cmd640_reg
c_func
(paren
id|port
comma
id|b
)paren
suffix:semicolon
)brace
DECL|struct|readahead_black_list
r_static
r_struct
id|readahead_black_list
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|variable|drives_ra
)brace
id|drives_ra
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;ST3655A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;SAMSUNG&quot;
comma
l_int|0
)brace
comma
multiline_comment|/* Be conservative */
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|strmatch
r_static
r_int
id|strmatch
c_func
(paren
r_const
r_char
op_star
id|pattern
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_char
id|c1
comma
id|c2
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|c1
op_assign
op_star
id|pattern
op_increment
suffix:semicolon
id|c2
op_assign
op_star
id|name
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|c1
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c1
op_ne
id|c2
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|known_drive_readahead
r_static
r_int
id|known_drive_readahead
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|drives_ra
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strmatch
c_func
(paren
id|drives_ra
(braket
id|i
)braket
dot
id|name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|drives_ra
(braket
id|i
)braket
dot
id|mode
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|arttim
r_static
r_int
id|arttim
(braket
l_int|4
)braket
op_assign
(brace
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
)brace
suffix:semicolon
multiline_comment|/* Address setup count (in clocks) */
DECL|variable|a_count
r_static
r_int
id|a_count
(braket
l_int|4
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
multiline_comment|/* Active count   (encoded) */
DECL|variable|r_count
r_static
r_int
id|r_count
(braket
l_int|4
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
multiline_comment|/* Recovery count (encoded) */
multiline_comment|/*&n; * Convert address setup count from number of clocks &n; * to representation used by controller&n; */
DECL|function|pack_arttim
r_inline
r_static
r_int
id|pack_arttim
c_func
(paren
r_int
id|clocks
)paren
(brace
r_if
c_cond
(paren
id|clocks
op_le
l_int|2
)paren
r_return
l_int|0x40
suffix:semicolon
r_else
r_if
c_cond
(paren
id|clocks
op_eq
l_int|3
)paren
r_return
l_int|0x80
suffix:semicolon
r_else
r_if
c_cond
(paren
id|clocks
op_eq
l_int|4
)paren
r_return
l_int|0x00
suffix:semicolon
r_else
r_return
l_int|0xc0
suffix:semicolon
)brace
multiline_comment|/*&n; * Pack active and recovery counts into single byte representation&n; * used by controller&n; */
DECL|function|pack_counts
r_inline
r_static
r_int
id|pack_counts
c_func
(paren
r_int
id|act_count
comma
r_int
id|rec_count
)paren
(brace
r_return
(paren
(paren
id|act_count
op_amp
l_int|0x0f
)paren
op_lshift
l_int|4
)paren
op_or
(paren
id|rec_count
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
DECL|function|max
r_inline
r_int
id|max
c_func
(paren
r_int
id|a
comma
r_int
id|b
)paren
(brace
r_return
id|a
OG
id|b
ques
c_cond
id|a
suffix:colon
id|b
suffix:semicolon
)brace
DECL|function|max4
r_inline
r_int
id|max4
c_func
(paren
r_int
op_star
id|p
)paren
(brace
r_return
id|max
c_func
(paren
id|p
(braket
l_int|0
)braket
comma
id|max
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
id|max
c_func
(paren
id|p
(braket
l_int|2
)braket
comma
id|p
(braket
l_int|3
)braket
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set timing parameters&n; */
DECL|function|cmd640_set_timing
r_static
r_void
id|cmd640_set_timing
c_func
(paren
r_int
id|if_num
comma
r_int
id|dr_num
)paren
(brace
r_int
id|b_reg
suffix:semicolon
r_int
id|ac
comma
id|rc
comma
id|at
suffix:semicolon
multiline_comment|/*&n;&t; * Set address setup count and drive read/write timing registers.&n;&t; * Primary interface has individual count/timing registers for&n;&t; * each drive. Secondary interface has common set of registers, and&n;&t; * we should set timings for the slowest drive.&n;&t; */
r_if
c_cond
(paren
id|if_num
op_eq
l_int|0
)paren
(brace
id|b_reg
op_assign
id|dr_num
ques
c_cond
id|ARTTIM1
suffix:colon
id|ARTTIM0
suffix:semicolon
id|at
op_assign
id|arttim
(braket
id|dr_num
)braket
suffix:semicolon
id|ac
op_assign
id|a_count
(braket
id|dr_num
)braket
suffix:semicolon
id|rc
op_assign
id|r_count
(braket
id|dr_num
)braket
suffix:semicolon
)brace
r_else
(brace
id|b_reg
op_assign
id|ARTTIM23
suffix:semicolon
id|at
op_assign
id|max
c_func
(paren
id|arttim
(braket
l_int|2
)braket
comma
id|arttim
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|ac
op_assign
id|max
c_func
(paren
id|a_count
(braket
l_int|2
)braket
comma
id|a_count
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|rc
op_assign
id|max
c_func
(paren
id|r_count
(braket
l_int|2
)braket
comma
id|r_count
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
id|put_cmd640_reg
c_func
(paren
id|b_reg
comma
id|pack_arttim
c_func
(paren
id|at
)paren
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|b_reg
op_plus
l_int|1
comma
id|pack_counts
c_func
(paren
id|ac
comma
id|rc
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Update CMDTIM (IDE Command Block Timing Register) &n;&t; */
id|ac
op_assign
id|max4
c_func
(paren
id|r_count
)paren
suffix:semicolon
id|rc
op_assign
id|max4
c_func
(paren
id|a_count
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|CMDTIM
comma
id|pack_counts
c_func
(paren
id|ac
comma
id|rc
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Standard timings for PIO modes&n; */
DECL|struct|pio_timing
r_static
r_struct
id|pio_timing
(brace
DECL|member|mc_time
r_int
id|mc_time
suffix:semicolon
multiline_comment|/* Minimal cycle time (ns) */
DECL|member|av_time
r_int
id|av_time
suffix:semicolon
multiline_comment|/* Address valid to DIOR-/DIOW- setup (ns) */
DECL|member|ds_time
r_int
id|ds_time
suffix:semicolon
multiline_comment|/* DIOR data setup&t;(ns) */
DECL|variable|pio_timings
)brace
id|pio_timings
(braket
l_int|6
)braket
op_assign
(brace
(brace
l_int|70
comma
l_int|165
comma
l_int|600
)brace
comma
multiline_comment|/* PIO Mode 0 */
(brace
l_int|50
comma
l_int|125
comma
l_int|383
)brace
comma
multiline_comment|/* PIO Mode 1 */
(brace
l_int|30
comma
l_int|100
comma
l_int|240
)brace
comma
multiline_comment|/* PIO Mode 2 */
(brace
l_int|30
comma
l_int|80
comma
l_int|180
)brace
comma
multiline_comment|/* PIO Mode 3 */
(brace
l_int|25
comma
l_int|70
comma
l_int|125
)brace
comma
multiline_comment|/* PIO Mode 4  -- should be 120, not 125 */
(brace
l_int|20
comma
l_int|50
comma
l_int|100
)brace
multiline_comment|/* PIO Mode ? (nonstandard) */
)brace
suffix:semicolon
DECL|function|cmd640_timings_to_clocks
r_static
r_void
id|cmd640_timings_to_clocks
c_func
(paren
r_int
id|mc_time
comma
r_int
id|av_time
comma
r_int
id|ds_time
comma
r_int
id|clock_time
comma
r_int
id|drv_idx
)paren
(brace
r_int
id|a
comma
id|b
suffix:semicolon
id|arttim
(braket
id|drv_idx
)braket
op_assign
(paren
id|mc_time
op_plus
id|clock_time
op_minus
l_int|1
)paren
op_div
id|clock_time
suffix:semicolon
id|a
op_assign
(paren
id|av_time
op_plus
id|clock_time
op_minus
l_int|1
)paren
op_div
id|clock_time
suffix:semicolon
r_if
c_cond
(paren
id|a
OL
l_int|2
)paren
id|a
op_assign
l_int|2
suffix:semicolon
id|b
op_assign
(paren
id|ds_time
op_plus
id|clock_time
op_minus
l_int|1
)paren
op_div
id|clock_time
op_minus
id|a
suffix:semicolon
r_if
c_cond
(paren
id|b
OL
l_int|2
)paren
id|b
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|b
OG
l_int|0x11
)paren
(brace
id|a
op_add_assign
id|b
op_minus
l_int|0x11
suffix:semicolon
id|b
op_assign
l_int|0x11
suffix:semicolon
)brace
r_if
c_cond
(paren
id|a
OG
l_int|0x10
)paren
id|a
op_assign
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|cmd640_chip_version
OG
l_int|1
)paren
id|b
op_sub_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|b
OG
l_int|0x10
)paren
id|b
op_assign
l_int|0x10
suffix:semicolon
id|a_count
(braket
id|drv_idx
)braket
op_assign
id|a
suffix:semicolon
id|r_count
(braket
id|drv_idx
)braket
op_assign
id|b
suffix:semicolon
)brace
DECL|function|set_pio_mode
r_static
r_void
id|set_pio_mode
c_func
(paren
r_int
id|if_num
comma
r_int
id|drv_num
comma
r_int
id|mode_num
)paren
(brace
r_int
id|p_base
suffix:semicolon
r_int
id|i
suffix:semicolon
id|p_base
op_assign
id|if_num
ques
c_cond
l_int|0x170
suffix:colon
l_int|0x1f0
suffix:semicolon
id|outb_p
c_func
(paren
l_int|3
comma
id|p_base
op_plus
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|mode_num
op_or
l_int|8
comma
id|p_base
op_plus
l_int|2
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|drv_num
op_or
l_int|0xa
)paren
op_lshift
l_int|4
comma
id|p_base
op_plus
l_int|6
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xef
comma
id|p_base
op_plus
l_int|7
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|100
)paren
op_logical_and
(paren
id|inb
(paren
id|p_base
op_plus
l_int|7
)paren
op_amp
l_int|0x80
)paren
suffix:semicolon
id|i
op_increment
)paren
id|udelay
c_func
(paren
l_int|10000
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a specific pio_mode for a drive&n; */
DECL|function|cmd640_set_mode
r_static
r_void
id|cmd640_set_mode
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|pio_mode
)paren
(brace
r_int
id|interface_number
suffix:semicolon
r_int
id|drive_number
suffix:semicolon
r_int
id|clock_time
suffix:semicolon
multiline_comment|/* ns */
r_int
id|mc_time
comma
id|av_time
comma
id|ds_time
suffix:semicolon
id|interface_number
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
suffix:semicolon
id|drive_number
op_assign
id|drive-&gt;select.b.unit
suffix:semicolon
id|clock_time
op_assign
l_int|1000
op_div
id|bus_speed
suffix:semicolon
id|mc_time
op_assign
id|pio_timings
(braket
id|pio_mode
)braket
dot
id|mc_time
suffix:semicolon
id|av_time
op_assign
id|pio_timings
(braket
id|pio_mode
)braket
dot
id|av_time
suffix:semicolon
id|ds_time
op_assign
id|pio_timings
(braket
id|pio_mode
)braket
dot
id|ds_time
suffix:semicolon
id|cmd640_timings_to_clocks
c_func
(paren
id|mc_time
comma
id|av_time
comma
id|ds_time
comma
id|clock_time
comma
id|interface_number
op_star
l_int|2
op_plus
id|drive_number
)paren
suffix:semicolon
id|set_pio_mode
c_func
(paren
id|interface_number
comma
id|drive_number
comma
id|pio_mode
)paren
suffix:semicolon
id|cmd640_set_timing
c_func
(paren
id|interface_number
comma
id|drive_number
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Drive PIO mode &quot;autoconfiguration&quot;.&n; * Ideally, this code should *always* call cmd640_set_mode(), but it doesn&squot;t.&n; */
DECL|function|cmd640_tune_drive
r_static
r_void
id|cmd640_tune_drive
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio_mode
)paren
(brace
r_int
id|interface_number
suffix:semicolon
r_int
id|drive_number
suffix:semicolon
r_int
id|clock_time
suffix:semicolon
multiline_comment|/* ns */
r_int
id|max_pio
suffix:semicolon
r_int
id|mc_time
comma
id|av_time
comma
id|ds_time
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
suffix:semicolon
r_int
id|readahead
suffix:semicolon
multiline_comment|/* there is a global named read_ahead */
r_if
c_cond
(paren
id|pio_mode
op_ne
l_int|255
)paren
(brace
id|cmd640_set_mode
c_func
(paren
id|drive
comma
id|pio_mode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|interface_number
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|index
suffix:semicolon
id|drive_number
op_assign
id|drive-&gt;select.b.unit
suffix:semicolon
id|clock_time
op_assign
l_int|1000
op_div
id|bus_speed
suffix:semicolon
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_if
c_cond
(paren
(paren
id|max_pio
op_assign
id|ide_scan_pio_blacklist
c_func
(paren
id|id-&gt;model
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|ds_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|ds_time
suffix:semicolon
)brace
r_else
(brace
id|max_pio
op_assign
id|id-&gt;tPIO
suffix:semicolon
id|ds_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|ds_time
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
op_logical_and
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
id|max_pio
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
id|max_pio
op_assign
l_int|4
suffix:semicolon
r_else
id|max_pio
op_assign
l_int|3
suffix:semicolon
id|ds_time
op_assign
id|id-&gt;eide_pio_iordy
suffix:semicolon
)brace
r_else
(brace
id|ds_time
op_assign
id|id-&gt;eide_pio
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ds_time
op_eq
l_int|0
)paren
id|ds_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|ds_time
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Conservative &quot;downgrade&quot;&n;&t;&t; */
r_if
c_cond
(paren
id|max_pio
OL
l_int|4
op_logical_and
id|max_pio
op_ne
l_int|0
)paren
(brace
id|max_pio
op_sub_assign
l_int|1
suffix:semicolon
id|ds_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|ds_time
suffix:semicolon
)brace
)brace
id|mc_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|mc_time
suffix:semicolon
id|av_time
op_assign
id|pio_timings
(braket
id|max_pio
)braket
dot
id|av_time
suffix:semicolon
id|cmd640_timings_to_clocks
c_func
(paren
id|mc_time
comma
id|av_time
comma
id|ds_time
comma
id|clock_time
comma
id|interface_number
op_star
l_int|2
op_plus
id|drive_number
)paren
suffix:semicolon
id|set_pio_mode
c_func
(paren
id|interface_number
comma
id|drive_number
comma
id|max_pio
)paren
suffix:semicolon
id|cmd640_set_timing
c_func
(paren
id|interface_number
comma
id|drive_number
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable (or set) readahead mode&n;&t; */
id|readahead
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd640_chip_version
OG
l_int|1
)paren
(brace
multiline_comment|/* Mmmm.. probably should be &gt; 2 ?? */
id|readahead
op_assign
id|known_drive_readahead
c_func
(paren
id|id-&gt;model
)paren
suffix:semicolon
r_if
c_cond
(paren
id|readahead
op_eq
op_minus
l_int|1
)paren
id|readahead
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Mmmm.. probably be 0 ?? */
id|set_readahead_mode
c_func
(paren
id|readahead
comma
id|interface_number
comma
id|drive_number
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Mode and Timing set to PIO%d, Readahead is %s&bslash;n&quot;
comma
id|max_pio
comma
id|readahead
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
)brace
eof
