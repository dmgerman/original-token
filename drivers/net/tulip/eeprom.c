multiline_comment|/*&n;&t;drivers/net/tulip/eeprom.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n;&t;Copyright 2000  The Linux Kernel Team&n;&t;Written/copyright 1994-1999 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/networking/tulip.txt for more&n;&t;information on this driver.&n;&n;*/
macro_line|#include &quot;tulip.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
multiline_comment|/* Serial EEPROM section. */
multiline_comment|/* The main routine to parse the very complicated SROM structure.&n;   Search www.digital.com for &quot;21X4 SROM&quot; to get details.&n;   This code is very complex, and will require changes to support&n;   additional cards, so I&squot;ll be verbose about what is going on.&n;   */
multiline_comment|/* Known cards that have old-style EEPROMs. */
DECL|variable|__devinitdata
r_static
r_struct
id|eeprom_fixup
id|eeprom_fixups
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
l_string|&quot;Asante&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0x94
comma
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x0800
comma
l_int|0x0100
comma
l_int|0x018c
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0xe078
comma
l_int|0x0001
comma
l_int|0x0050
comma
l_int|0x0018
)brace
)brace
comma
(brace
l_string|&quot;SMC9332DST&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0xC0
comma
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x0800
comma
l_int|0x041f
comma
l_int|0x0000
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT */
l_int|0x0004
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT-FD */
l_int|0x0903
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx */
l_int|0x0905
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx-FD */
)brace
)brace
comma
(brace
l_string|&quot;Cogent EM100&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0x92
comma
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x0800
comma
l_int|0x063f
comma
l_int|0x0107
comma
l_int|0x8021
comma
multiline_comment|/* 100baseFx */
l_int|0x0108
comma
l_int|0x8021
comma
multiline_comment|/* 100baseFx-FD */
l_int|0x0100
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT */
l_int|0x0104
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT-FD */
l_int|0x0103
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx */
l_int|0x0105
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx-FD */
)brace
)brace
comma
(brace
l_string|&quot;Maxtech NX-110&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0xE8
comma
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x0800
comma
l_int|0x0513
comma
l_int|0x1001
comma
l_int|0x009E
comma
multiline_comment|/* 10base2, CSR12 0x10*/
l_int|0x0000
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT */
l_int|0x0004
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT-FD */
l_int|0x0303
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx, CSR12 0x03 */
l_int|0x0305
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx-FD CSR12 0x03 */
)brace
)brace
comma
(brace
l_string|&quot;Accton EN1207&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0xE8
comma
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x0800
comma
l_int|0x051F
comma
l_int|0x1B01
comma
l_int|0x0000
comma
multiline_comment|/* 10base2,   CSR12 0x1B */
l_int|0x0B00
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT,   CSR12 0x0B */
l_int|0x0B04
comma
l_int|0x009E
comma
multiline_comment|/* 10baseT-FD,CSR12 0x0B */
l_int|0x1B03
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx, CSR12 0x1B */
l_int|0x1B05
comma
l_int|0x006D
comma
multiline_comment|/* 100baseTx-FD CSR12 0x1B */
)brace
)brace
comma
(brace
l_string|&quot;NetWinder&quot;
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x57
comma
multiline_comment|/* Default media = MII&n;&t; * MII block, reset sequence (3) = 0x0821 0x0000 0x0001, capabilities 0x01e1&n;&t; */
(brace
l_int|0x1e00
comma
l_int|0x0000
comma
l_int|0x000b
comma
l_int|0x8f01
comma
l_int|0x0103
comma
l_int|0x0300
comma
l_int|0x0821
comma
l_int|0x000
comma
l_int|0x0001
comma
l_int|0x0000
comma
l_int|0x01e1
)brace
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
)brace
)brace
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_const
r_char
op_star
id|block_name
(braket
)braket
id|__devinitdata
op_assign
(brace
l_string|&quot;21140 non-MII&quot;
comma
l_string|&quot;21140 MII PHY&quot;
comma
l_string|&quot;21142 Serial PHY&quot;
comma
l_string|&quot;21142 MII PHY&quot;
comma
l_string|&quot;21143 SYM PHY&quot;
comma
l_string|&quot;21143 reset method&quot;
)brace
suffix:semicolon
DECL|function|tulip_parse_eeprom
r_void
id|__devinit
id|tulip_parse_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* The last media info list parsed, for multiport boards.  */
r_static
r_struct
id|mediatable
op_star
id|last_mediatable
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
r_char
op_star
id|last_ee_data
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|controller_index
op_assign
l_int|0
suffix:semicolon
r_struct
id|tulip_private
op_star
id|tp
op_assign
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_char
op_star
id|ee_data
op_assign
id|tp-&gt;eeprom
suffix:semicolon
r_int
id|i
suffix:semicolon
id|tp-&gt;mtable
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Detect an old-style (SA only) EEPROM layout:&n;&t;   memcmp(eedata, eedata+16, 8). */
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
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ee_data
(braket
id|i
)braket
op_ne
id|ee_data
(braket
l_int|16
op_plus
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|ee_data
(braket
l_int|0
)braket
op_eq
l_int|0xff
)paren
(brace
r_if
c_cond
(paren
id|last_mediatable
)paren
(brace
id|controller_index
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  Controller %d of multiport board.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|controller_index
)paren
suffix:semicolon
id|tp-&gt;mtable
op_assign
id|last_mediatable
suffix:semicolon
id|ee_data
op_assign
id|last_ee_data
suffix:semicolon
r_goto
id|subsequent_board
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  Missing EEPROM, this interface may &quot;
l_string|&quot;not work correctly!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Do a fix-up based on the vendor half of the station address prefix. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|eeprom_fixups
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_eq
id|eeprom_fixups
(braket
id|i
)braket
dot
id|addr0
op_logical_and
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_eq
id|eeprom_fixups
(braket
id|i
)braket
dot
id|addr1
op_logical_and
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_eq
id|eeprom_fixups
(braket
id|i
)braket
dot
id|addr2
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_eq
l_int|0xE8
op_logical_and
id|ee_data
(braket
l_int|0x1a
)braket
op_eq
l_int|0x55
)paren
id|i
op_increment
suffix:semicolon
multiline_comment|/* An Accton EN1207, not an outlaw Maxtech. */
id|memcpy
c_func
(paren
id|ee_data
op_plus
l_int|26
comma
id|eeprom_fixups
(braket
id|i
)braket
dot
id|newtable
comma
r_sizeof
(paren
id|eeprom_fixups
(braket
id|i
)braket
dot
id|newtable
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Old format EEPROM on &squot;%s&squot; board.  Using&quot;
l_string|&quot; substitute media control info.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|eeprom_fixups
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|eeprom_fixups
(braket
id|i
)braket
dot
id|name
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* No fixup found. */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Old style EEPROM with no media selection &quot;
l_string|&quot;information.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|controller_index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ee_data
(braket
l_int|19
)braket
OG
l_int|1
)paren
(brace
multiline_comment|/* Multiport board. */
id|last_ee_data
op_assign
id|ee_data
suffix:semicolon
)brace
id|subsequent_board
suffix:colon
r_if
c_cond
(paren
id|ee_data
(braket
l_int|27
)braket
op_eq
l_int|0
)paren
(brace
multiline_comment|/* No valid media table. */
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|DC21041
)paren
(brace
r_int
r_char
op_star
id|p
op_assign
(paren
r_void
op_star
)paren
id|ee_data
op_plus
id|ee_data
(braket
l_int|27
op_plus
id|controller_index
op_star
l_int|3
)braket
suffix:semicolon
r_int
id|media
op_assign
id|get_u16
c_func
(paren
id|p
)paren
suffix:semicolon
r_int
id|count
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|p
op_add_assign
l_int|3
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21041 Media table, default media %4.4x (%s).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|media
comma
id|media
op_amp
l_int|0x0800
ques
c_cond
l_string|&quot;Autosense&quot;
suffix:colon
id|medianame
(braket
id|media
op_amp
l_int|15
)braket
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|media_code
op_assign
op_star
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|media_code
op_amp
l_int|0x40
)paren
id|p
op_add_assign
l_int|6
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  21041 media #%d, %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|media_code
op_amp
l_int|15
comma
id|medianame
(braket
id|media_code
op_amp
l_int|15
)braket
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_char
op_star
id|p
op_assign
(paren
r_void
op_star
)paren
id|ee_data
op_plus
id|ee_data
(braket
l_int|27
)braket
suffix:semicolon
r_int
r_char
id|csr12dir
op_assign
l_int|0
suffix:semicolon
r_int
id|count
comma
id|new_advertise
op_assign
l_int|0
suffix:semicolon
r_struct
id|mediatable
op_star
id|mtable
suffix:semicolon
id|u16
id|media
op_assign
id|get_u16
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;flags
op_amp
id|CSR12_IN_SROM
)paren
id|csr12dir
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|count
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|mtable
op_assign
(paren
r_struct
id|mediatable
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mediatable
)paren
op_plus
id|count
op_star
r_sizeof
(paren
r_struct
id|medialeaf
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtable
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Horrible, impossible failure. */
id|last_mediatable
op_assign
id|tp-&gt;mtable
op_assign
id|mtable
suffix:semicolon
id|mtable-&gt;defaultmedia
op_assign
id|media
suffix:semicolon
id|mtable-&gt;leafcount
op_assign
id|count
suffix:semicolon
id|mtable-&gt;csr12dir
op_assign
id|csr12dir
suffix:semicolon
id|mtable-&gt;has_nonmii
op_assign
id|mtable-&gt;has_mii
op_assign
id|mtable-&gt;has_reset
op_assign
l_int|0
suffix:semicolon
id|mtable-&gt;csr15dir
op_assign
id|mtable-&gt;csr15val
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  EEPROM default media type %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|media
op_amp
l_int|0x0800
ques
c_cond
l_string|&quot;Autosense&quot;
suffix:colon
id|medianame
(braket
id|media
op_amp
l_int|15
)braket
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|medialeaf
op_star
id|leaf
op_assign
op_amp
id|mtable-&gt;mleaf
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* 21140 Compact block. */
id|leaf-&gt;type
op_assign
l_int|0
suffix:semicolon
id|leaf-&gt;media
op_assign
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x3f
suffix:semicolon
id|leaf-&gt;leafdata
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x61
)paren
op_eq
l_int|0x01
)paren
multiline_comment|/* Bogus, but Znyx boards do it. */
id|mtable-&gt;has_mii
op_assign
l_int|1
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|leaf-&gt;type
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_int|0x05
)paren
(brace
id|mtable-&gt;has_reset
op_assign
id|i
suffix:semicolon
id|leaf-&gt;media
op_assign
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x0f
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_amp
l_int|1
)paren
(brace
id|mtable-&gt;has_mii
op_assign
l_int|1
suffix:semicolon
id|leaf-&gt;media
op_assign
l_int|11
suffix:semicolon
)brace
r_else
(brace
id|mtable-&gt;has_nonmii
op_assign
l_int|1
suffix:semicolon
id|leaf-&gt;media
op_assign
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|leaf-&gt;media
)paren
(brace
r_case
l_int|0
suffix:colon
id|new_advertise
op_or_assign
l_int|0x0020
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|new_advertise
op_or_assign
l_int|0x0040
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|new_advertise
op_or_assign
l_int|0x0080
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|new_advertise
op_or_assign
l_int|0x0100
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|new_advertise
op_or_assign
l_int|0x0200
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_int|2
op_logical_and
id|leaf-&gt;media
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x40
)paren
(brace
id|u32
id|base15
op_assign
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|mtable-&gt;csr15dir
op_assign
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|9
)braket
)paren
op_lshift
l_int|16
)paren
op_plus
id|base15
suffix:semicolon
id|mtable-&gt;csr15val
op_assign
(paren
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|11
)braket
)paren
op_lshift
l_int|16
)paren
op_plus
id|base15
suffix:semicolon
)brace
r_else
(brace
id|mtable-&gt;csr15dir
op_assign
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|3
)braket
)paren
op_lshift
l_int|16
suffix:semicolon
id|mtable-&gt;csr15val
op_assign
id|get_unaligned
c_func
(paren
(paren
id|u16
op_star
)paren
op_amp
id|p
(braket
l_int|5
)braket
)paren
op_lshift
l_int|16
suffix:semicolon
)brace
)brace
)brace
id|leaf-&gt;leafdata
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|p
op_add_assign
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x3f
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
op_logical_and
id|leaf-&gt;media
op_eq
l_int|11
)paren
(brace
r_int
r_char
op_star
id|bp
op_assign
id|leaf-&gt;leafdata
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  MII interface PHY %d, setup/reset &quot;
l_string|&quot;sequences %d/%d long, capabilities %2.2x %2.2x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|bp
(braket
l_int|0
)braket
comma
id|bp
(braket
l_int|1
)braket
comma
id|bp
(braket
l_int|2
op_plus
id|bp
(braket
l_int|1
)braket
op_star
l_int|2
)braket
comma
id|bp
(braket
l_int|5
op_plus
id|bp
(braket
l_int|2
op_plus
id|bp
(braket
l_int|1
)braket
op_star
l_int|2
)braket
op_star
l_int|2
)braket
comma
id|bp
(braket
l_int|4
op_plus
id|bp
(braket
l_int|2
op_plus
id|bp
(braket
l_int|1
)braket
op_star
l_int|2
)braket
op_star
l_int|2
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:  Index #%d - Media %s (#%d) described &quot;
l_string|&quot;by a %s (%d) block.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|i
comma
id|medianame
(braket
id|leaf-&gt;media
)braket
comma
id|leaf-&gt;media
comma
id|block_name
(braket
id|leaf-&gt;type
)braket
comma
id|leaf-&gt;type
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_advertise
)paren
id|tp-&gt;to_advertise
op_assign
id|new_advertise
suffix:semicolon
)brace
)brace
multiline_comment|/* Reading a serial EEPROM is a &quot;bit&quot; grungy, but we work our way through:-&gt;.*/
multiline_comment|/* Note: this routine returns extra data bits for size detection. */
DECL|function|tulip_read_eeprom
r_int
id|__devinit
id|tulip_read_eeprom
c_func
(paren
r_int
id|ioaddr
comma
r_int
id|location
comma
r_int
id|addr_len
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|ee_addr
op_assign
id|ioaddr
op_plus
id|CSR9
suffix:semicolon
r_int
id|read_cmd
op_assign
id|location
op_or
(paren
id|EE_READ_CMD
op_lshift
id|addr_len
)paren
suffix:semicolon
id|outl
c_func
(paren
id|EE_ENB
op_amp
op_complement
id|EE_CS
comma
id|ee_addr
)paren
suffix:semicolon
id|outl
c_func
(paren
id|EE_ENB
comma
id|ee_addr
)paren
suffix:semicolon
multiline_comment|/* Shift the read command bits out. */
r_for
c_loop
(paren
id|i
op_assign
l_int|4
op_plus
id|addr_len
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_int
id|dataval
op_assign
(paren
id|read_cmd
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|EE_DATA_WRITE
suffix:colon
l_int|0
suffix:semicolon
id|outl
c_func
(paren
id|EE_ENB
op_or
id|dataval
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|outl
c_func
(paren
id|EE_ENB
op_or
id|dataval
op_or
id|EE_SHIFT_CLK
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|retval
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|inl
c_func
(paren
id|ee_addr
)paren
op_amp
id|EE_DATA_READ
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
id|EE_ENB
comma
id|ee_addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|outl
c_func
(paren
id|EE_ENB
op_or
id|EE_SHIFT_CLK
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|retval
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|inl
c_func
(paren
id|ee_addr
)paren
op_amp
id|EE_DATA_READ
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|outl
c_func
(paren
id|EE_ENB
comma
id|ee_addr
)paren
suffix:semicolon
id|eeprom_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Terminate the EEPROM access. */
id|outl
c_func
(paren
id|EE_ENB
op_amp
op_complement
id|EE_CS
comma
id|ee_addr
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
