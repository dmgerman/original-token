multiline_comment|/*&n; *  linux/drivers/block/cmd640.c&t;Version 0.02  Nov 30, 1995&n; *&n; *  Copyright (C) 1995  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *  Principal Author/Maintainer:  abramov@cecmow.enet.dec.com (Igor)&n; *&n; *  This file provides support for the advanced features and bugs&n; *  of IDE interfaces using the CMD Technologies 0640 IDE interface chip.&n; *&n; *  Version 0.01&t;Initial version, hacked out of ide.c,&n; *&t;&t;&t;and #include&squot;d rather than compiled separately.&n; *&t;&t;&t;This will get cleaned up in a subsequent release.&n; *&n; *  Version 0.02&t;Fixes for vlb initialization code, enable&n; *&t;&t;&t;read-ahead for versions &squot;B&squot; and &squot;C&squot; of chip by&n; *&t;&t;&t;default, some code cleanup.&n; *&n; */
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
id|key
comma
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
id|key
comma
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
DECL|variable|is_cmd640
r_static
id|byte
id|is_cmd640
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|bus_speed
r_static
r_int
id|bus_speed
suffix:semicolon
multiline_comment|/* MHz */
multiline_comment|/*&n; * For some unknown reasons pcibios functions which read and write registers&n; * do not work with cmd640. We use direct io instead.&n; */
multiline_comment|/* PCI method 1 access */
DECL|function|put_cmd640_reg_pci1
r_static
r_void
id|put_cmd640_reg_pci1
c_func
(paren
r_int
id|key
comma
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
id|key
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
id|key
comma
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
id|key
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
id|key
comma
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
id|key
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
id|key
comma
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
id|key
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
id|key
comma
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
id|key
op_plus
l_int|8
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|key
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
id|key
comma
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
id|key
op_plus
l_int|8
)paren
suffix:semicolon
id|b
op_assign
id|inb_p
c_func
(paren
id|key
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
id|i
suffix:semicolon
r_int
id|second_port
suffix:semicolon
r_int
id|cmd_read_ahead
suffix:semicolon
id|byte
id|b
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
id|MAX_HWIFS
suffix:semicolon
id|i
op_increment
)paren
id|is_cmd640
(braket
id|i
)braket
op_assign
l_int|0
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
multiline_comment|/*&n;&t; * Undocumented magic. (There is no 0x5b port in specs)&n;&t; */
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
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
id|cmd640_key
comma
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
id|cmd640_key
comma
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
id|cmd640_key
comma
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
multiline_comment|/*&n;&t; * Do not initialize secondary controller for vlbus&n;&t; */
id|second_port
op_assign
(paren
id|bus_type
op_ne
id|vlb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the maximum allowed bus speed (it is safest until we&n;&t; * &t;&t;&t;&t;      find how detect bus speed)&n;&t; * Normally PCI bus runs at 33MHz, but often works overclocked to 40&n;&t; */
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
macro_line|#if 1&t;/* don&squot;t know if this is reliable yet */
multiline_comment|/*&n;&t; * Enable readahead for versions above &squot;A&squot;&n;&t; */
id|cmd_read_ahead
op_assign
(paren
id|cmd640_chip_version
OG
l_int|1
)paren
suffix:semicolon
macro_line|#else
id|cmd_read_ahead
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Setup Control Register&n;&t; */
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|cmd640_key
comma
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
r_if
c_cond
(paren
id|cmd_read_ahead
)paren
id|b
op_and_assign
op_complement
(paren
id|CNTRL_DIS_RA0
op_or
id|CNTRL_DIS_RA1
)paren
suffix:semicolon
r_else
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
id|cmd640_key
comma
id|CNTRL
comma
id|b
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize 2nd IDE port, if required&n;&t; */
r_if
c_cond
(paren
id|second_port
)paren
(brace
multiline_comment|/* We reset timings, and setup read-ahead */
id|b
op_assign
id|cmd_read_ahead
ques
c_cond
l_int|0
suffix:colon
(paren
id|DIS_RA2
op_or
id|DIS_RA3
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|ARTTIM23
comma
id|b
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|DRWTIM23
comma
l_int|0
)paren
suffix:semicolon
)brace
id|serialized
op_assign
l_int|1
suffix:semicolon
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
id|is_cmd640
(braket
l_int|0
)braket
op_assign
id|is_cmd640
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Reset interface timings&n;&t; */
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|CMDTIM
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n ... serialized, %s read-ahead, secondary interface %s&bslash;n&quot;
comma
id|cmd_read_ahead
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
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
DECL|function|as_clocks
r_static
r_int
id|as_clocks
c_func
(paren
r_int
id|a
)paren
(brace
r_switch
c_cond
(paren
id|a
op_amp
l_int|0xc0
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|4
suffix:semicolon
r_case
l_int|0x40
suffix:colon
r_return
l_int|2
suffix:semicolon
r_case
l_int|0x80
suffix:colon
r_return
l_int|3
suffix:semicolon
r_case
l_int|0xc0
suffix:colon
r_return
l_int|5
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Tuning of drive parameters&n; */
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
comma
r_int
id|r1
comma
r_int
id|r2
)paren
(brace
r_int
id|b_reg
suffix:semicolon
id|byte
id|b
suffix:semicolon
r_int
id|r52
suffix:semicolon
r_static
r_int
id|a
op_assign
l_int|0
suffix:semicolon
id|b_reg
op_assign
id|if_num
ques
c_cond
id|ARTTIM23
suffix:colon
id|dr_num
ques
c_cond
id|ARTTIM1
suffix:colon
id|ARTTIM0
suffix:semicolon
r_if
c_cond
(paren
id|if_num
op_eq
l_int|0
)paren
(brace
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
comma
id|r1
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
op_plus
l_int|1
comma
id|r2
)paren
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
l_int|0
op_logical_or
id|as_clocks
c_func
(paren
id|b
)paren
OL
id|as_clocks
c_func
(paren
id|r1
)paren
)paren
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
comma
(paren
id|b
op_amp
l_int|0xc0
)paren
op_or
id|r1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
l_int|0
)paren
(brace
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
op_plus
l_int|1
comma
id|r2
)paren
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
op_plus
l_int|1
)paren
suffix:semicolon
id|r52
op_assign
(paren
id|b
op_amp
l_int|0x0f
)paren
OL
(paren
id|r2
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|r2
op_amp
l_int|0x0f
)paren
suffix:colon
(paren
id|b
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|r52
op_or_assign
(paren
id|b
op_amp
l_int|0xf0
)paren
OL
(paren
id|r2
op_amp
l_int|0xf0
)paren
ques
c_cond
(paren
id|r2
op_amp
l_int|0xf0
)paren
suffix:colon
(paren
id|b
op_amp
l_int|0xf0
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|b_reg
op_plus
l_int|1
comma
id|r52
)paren
suffix:semicolon
)brace
id|a
op_assign
l_int|1
suffix:semicolon
)brace
id|b
op_assign
id|get_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|CMDTIM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
op_eq
l_int|0
)paren
(brace
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|CMDTIM
comma
id|r2
)paren
suffix:semicolon
)brace
r_else
(brace
id|r52
op_assign
(paren
id|b
op_amp
l_int|0x0f
)paren
OL
(paren
id|r2
op_amp
l_int|0x0f
)paren
ques
c_cond
(paren
id|r2
op_amp
l_int|0x0f
)paren
suffix:colon
(paren
id|b
op_amp
l_int|0x0f
)paren
suffix:semicolon
id|r52
op_or_assign
(paren
id|b
op_amp
l_int|0xf0
)paren
OL
(paren
id|r2
op_amp
l_int|0xf0
)paren
ques
c_cond
(paren
id|r2
op_amp
l_int|0xf0
)paren
suffix:colon
(paren
id|b
op_amp
l_int|0xf0
)paren
suffix:semicolon
id|put_cmd640_reg
c_func
(paren
id|cmd640_key
comma
id|CMDTIM
comma
id|r52
)paren
suffix:semicolon
)brace
)brace
DECL|struct|pio_timing
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
multiline_comment|/* PIO Mode 4 */
(brace
l_int|20
comma
l_int|50
comma
l_int|100
)brace
multiline_comment|/* PIO Mode ? */
)brace
suffix:semicolon
DECL|struct|drive_pio_info
r_struct
id|drive_pio_info
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|pio
r_int
id|pio
suffix:semicolon
DECL|variable|drive_pios
)brace
id|drive_pios
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Maxtor 7131 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7171 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7213 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7245 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3122A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;QUANTUM ELS127A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS240A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS270A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS540A&quot;
comma
l_int|3
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|known_drive_pio
r_static
r_int
id|known_drive_pio
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|drive_pio_info
op_star
id|pi
suffix:semicolon
r_for
c_loop
(paren
id|pi
op_assign
id|drive_pios
suffix:semicolon
id|pi-&gt;name
op_ne
l_int|NULL
suffix:semicolon
id|pi
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pi-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
r_return
id|pi-&gt;pio
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cmd640_timings_to_regvals
r_static
r_void
id|cmd640_timings_to_regvals
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
op_star
id|r1
comma
r_int
op_star
id|r2
)paren
(brace
r_int
id|a
comma
id|b
suffix:semicolon
id|a
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
r_if
c_cond
(paren
id|a
op_le
l_int|2
)paren
op_star
id|r1
op_assign
l_int|0x40
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a
op_eq
l_int|3
)paren
op_star
id|r1
op_assign
l_int|0x80
suffix:semicolon
r_else
r_if
c_cond
(paren
id|a
op_eq
l_int|4
)paren
op_star
id|r1
op_assign
l_int|0
suffix:semicolon
r_else
op_star
id|r1
op_assign
l_int|0xc0
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
l_int|0xf
)paren
id|a
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
id|b
op_sub_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|b
OG
l_int|0xf
)paren
id|b
op_assign
l_int|0
suffix:semicolon
op_star
id|r2
op_assign
(paren
id|a
op_lshift
l_int|4
)paren
op_or
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
id|delay_10ms
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cmd640_tune_drive
r_void
id|cmd640_tune_drive
c_func
(paren
id|ide_drive_t
op_star
id|drive
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
id|r1
comma
id|r2
suffix:semicolon
multiline_comment|/*&n;&t; * Determine if drive is under cmd640 control&n;&t; */
id|interface_number
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_minus
id|ide_hwifs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_cmd640
(braket
id|interface_number
)braket
)paren
r_return
suffix:semicolon
id|drive_number
op_assign
id|drive
op_minus
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drives
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
id|known_drive_pio
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
)brace
id|cmd640_timings_to_regvals
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
op_amp
id|r1
comma
op_amp
id|r2
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
comma
id|r1
comma
id|r2
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Mode and Timing set to PIO%d (0x%x 0x%x)&bslash;n&quot;
comma
id|max_pio
comma
id|r1
comma
id|r2
)paren
suffix:semicolon
)brace
eof
