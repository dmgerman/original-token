multiline_comment|/* &n;   Common Flash Interface probe code.&n;   (C) 2000 Red Hat. GPL&squot;d.&n;   $Id: cfi_probe.c,v 1.12 2000/07/03 13:29:16 dwmw2 Exp $&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/cfi.h&gt;
r_struct
id|mtd_info
op_star
id|cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
)paren
suffix:semicolon
r_static
r_void
id|print_cfi_ident
c_func
(paren
r_struct
id|cfi_ident
op_star
)paren
suffix:semicolon
r_static
r_void
id|check_cmd_set
c_func
(paren
r_struct
id|map_info
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_struct
id|cfi_private
op_star
id|cfi_cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
)paren
suffix:semicolon
DECL|variable|im_name
r_static
r_const
r_char
id|im_name
(braket
)braket
op_assign
l_string|&quot;cfi_probe&quot;
suffix:semicolon
multiline_comment|/* This routine is made available to other mtd code via&n; * inter_module_register.  It must only be accessed through&n; * inter_module_get which will bump the use count of this module.  The&n; * addresses passed back in mtd are valid as long as the use count of&n; * this module is non-zero, i.e. between inter_module_get and&n; * inter_module_put.  Keith Owens &lt;kaos@ocs.com.au&gt; 29 Oct 2000.&n; */
DECL|function|cfi_probe
r_struct
id|mtd_info
op_star
id|cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
id|map
)paren
(brace
r_struct
id|mtd_info
op_star
id|mtd
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|cfi_private
op_star
id|cfi
suffix:semicolon
multiline_comment|/* First probe the map to see if we have CFI stuff there. */
id|cfi
op_assign
id|cfi_cfi_probe
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi
)paren
r_return
l_int|NULL
suffix:semicolon
id|map-&gt;fldrv_priv
op_assign
id|cfi
suffix:semicolon
id|map-&gt;im_name
op_assign
id|im_name
suffix:semicolon
multiline_comment|/* OK we liked it. Now find a driver for the command set it talks */
id|check_cmd_set
c_func
(paren
id|map
comma
l_int|1
comma
id|cfi-&gt;chips
(braket
l_int|0
)braket
dot
id|start
)paren
suffix:semicolon
multiline_comment|/* First the primary cmdset */
id|check_cmd_set
c_func
(paren
id|map
comma
l_int|0
comma
id|cfi-&gt;chips
(braket
l_int|0
)braket
dot
id|start
)paren
suffix:semicolon
multiline_comment|/* Then the secondary */
multiline_comment|/* check_cmd_set() will have used inter_module_get to increase&n;&t;   the use count of the module which provides the command set &n;&t;   driver. If we&squot;re quitting, we have to decrease it again.&n;&t;*/
r_if
c_cond
(paren
id|cfi-&gt;cmdset_setup
)paren
(brace
id|mtd
op_assign
id|cfi
op_member_access_from_pointer
id|cmdset_setup
c_func
(paren
id|map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtd
)paren
r_return
id|mtd
suffix:semicolon
id|inter_module_put
c_func
(paren
id|cfi-&gt;im_name
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;No supported Vendor Command Set found&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cfi
)paren
suffix:semicolon
id|map-&gt;fldrv_priv
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|cfi_probe_new_chip
r_static
r_int
id|cfi_probe_new_chip
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
r_int
id|base
comma
r_struct
id|flchip
op_star
id|chips
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
(brace
r_switch
c_cond
(paren
id|map-&gt;buswidth
)paren
(brace
r_case
l_int|1
suffix:colon
(brace
r_int
r_char
id|tmp
op_assign
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x55
)paren
suffix:semicolon
multiline_comment|/* If there&squot;s a device there, put it in Query Mode */
id|map
op_member_access_from_pointer
id|write8
c_func
(paren
id|map
comma
l_int|0x98
comma
id|base
op_plus
l_int|0x55
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x10
)paren
op_eq
l_char|&squot;Q&squot;
op_logical_and
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x11
)paren
op_eq
l_char|&squot;R&squot;
op_logical_and
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x12
)paren
op_eq
l_char|&squot;Y&squot;
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found a CFI device at 0x%lx in 8 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
id|printk
c_func
(paren
l_string|&quot;FIXME: Do alias check at line %d of cfi_probe.c&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
multiline_comment|/* Put it back into Read Mode */
id|map
op_member_access_from_pointer
id|write8
c_func
(paren
id|map
comma
l_int|0x98
comma
id|base
op_plus
l_int|0x55
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x55
)paren
op_eq
l_int|0x98
)paren
(brace
multiline_comment|/* It looks like RAM. Put back the stuff we overwrote */
id|map
op_member_access_from_pointer
id|write8
c_func
(paren
id|map
comma
id|tmp
comma
id|base
op_plus
l_int|0x55
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_case
l_int|2
suffix:colon
(brace
id|__u16
id|tmp
op_assign
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0xaa
)paren
suffix:semicolon
multiline_comment|/* If there&squot;s a device there, put it into Query Mode */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0x9898
comma
id|base
op_plus
l_int|0xAA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x20
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x22
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x24
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0059
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found a CFI device at 0x%lx in 16 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
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
id|i
OL
id|cfi-&gt;numchips
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* This chip should be in read mode if it&squot;s one &n;&t;&t;&t;&t;&t;   we&squot;ve already touched. */
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x20
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x22
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x24
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0059
)paren
)paren
(brace
multiline_comment|/* Either the old chip has got &squot;Q&squot;&squot;R&squot;&squot;Y&squot; in a most&n;&t;&t;&t;&t;&t;&t;   unfortunate place, or it&squot;s an alias of the new&n;&t;&t;&t;&t;&t;&t;   chip. Double-check that it&squot;s in read mode, and check. */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x20
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x22
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0x24
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0059
)paren
)paren
(brace
multiline_comment|/* Yes it&squot;s got QRY for data. Most unfortunate. &n;&t;&t;&t;&t;&t;&t;&t;   Stick the old one in read mode too. */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x20
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x22
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x24
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0x0059
)paren
)paren
(brace
multiline_comment|/* OK, so has the new one. Assume it&squot;s an alias */
id|printk
c_func
(paren
l_string|&quot;T&squot;was probably an alias for the chip at 0x%lx&bslash;n&quot;
comma
id|chips
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* else no, they&squot;re different, fall through. */
)brace
r_else
(brace
multiline_comment|/* No the old one hasn&squot;t got QRY for data. Therefore,&n;&t;&t;&t;&t;&t;&t;&t;   it&squot;s an alias of the new one. */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|base
op_plus
l_int|0xaa
)paren
suffix:semicolon
multiline_comment|/* Just to be paranoid. */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|chips
(braket
id|i
)braket
dot
id|start
op_plus
l_int|0xaa
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;T&squot;was an alias for the chip at 0x%lx&bslash;n&quot;
comma
id|chips
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* No, the old one didn&squot;t look like it&squot;s in query mode. Next. */
)brace
multiline_comment|/* OK, if we got to here, then none of the previous chips appear to&n;&t;&t;&t;&t;   be aliases for the current one. */
r_if
c_cond
(paren
id|cfi-&gt;numchips
op_eq
id|MAX_CFI_CHIPS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Too many flash chips detected. Increase MAX_CFI_CHIPS from %d.&bslash;n&quot;
comma
id|map-&gt;name
comma
id|MAX_CFI_CHIPS
)paren
suffix:semicolon
multiline_comment|/* Doesn&squot;t matter about resetting it to Read Mode - we&squot;re not going to talk to it anyway */
r_return
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Not an alias. Adding&bslash;n&quot;
)paren
suffix:semicolon
id|chips
(braket
id|cfi-&gt;numchips
)braket
dot
id|start
op_assign
id|base
suffix:semicolon
id|chips
(braket
id|cfi-&gt;numchips
)braket
dot
id|state
op_assign
id|FL_READY
suffix:semicolon
id|chips
(braket
id|cfi-&gt;numchips
)braket
dot
id|mutex
op_assign
op_amp
id|chips
(braket
id|cfi-&gt;numchips
)braket
dot
id|_spinlock
suffix:semicolon
id|cfi-&gt;numchips
op_increment
suffix:semicolon
multiline_comment|/* Put it back into Read Mode */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|base
op_plus
l_int|0xaa
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x20
)paren
op_eq
l_int|0x5151
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x22
)paren
op_eq
l_int|0x5252
op_logical_and
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x24
)paren
op_eq
l_int|0x5959
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found a coupled pair of CFI devices at %lx in 8 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
id|printk
c_func
(paren
l_string|&quot;FIXME: Do alias check at line %d of cfi_probe.c&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
multiline_comment|/* Put it back into Read Mode */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
id|base
op_plus
l_int|0xaa
)paren
suffix:semicolon
)brace
r_return
l_int|2
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read16
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0xaa
)paren
op_eq
l_int|0x9898
)paren
(brace
multiline_comment|/* It looks like RAM. Put back the stuff we overwrote */
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
id|tmp
comma
id|base
op_plus
l_int|0xaa
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_case
l_int|4
suffix:colon
(brace
id|__u32
id|tmp
op_assign
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
multiline_comment|/* If there&squot;s a device there, put it into Query Mode */
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
l_int|0x98989898
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x40
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00000051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x44
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00000052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x48
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00000059
)paren
)paren
(brace
multiline_comment|/* This isn&squot;t actually in the CFI spec - only x8 and x16 are. */
id|printk
c_func
(paren
l_string|&quot;%s: Found a CFI device at %lx in 32 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
id|printk
c_func
(paren
l_string|&quot;FIXME: Do alias check at line %d of cfi_probe.c&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
multiline_comment|/* Put it back into read mode */
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
l_int|0xffffffff
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x40
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00510051
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x44
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00520052
)paren
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x48
)paren
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x00590059
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found a coupled pair of CFI devices at location %lx in 16 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
id|printk
c_func
(paren
l_string|&quot;FIXME: Do alias check at line %d of cfi_probe.c&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
multiline_comment|/* Put it back into read mode */
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
l_int|0xffffffff
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
)brace
r_return
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x40
)paren
op_eq
l_int|0x51515151
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x44
)paren
op_eq
l_int|0x52525252
op_logical_and
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x48
)paren
op_eq
l_int|0x59595959
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found four side-by-side CFI devices at location %lx in 8 bit mode&bslash;n&quot;
comma
id|map-&gt;name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chips
)paren
(brace
multiline_comment|/* Check previous chips for aliases */
id|printk
c_func
(paren
l_string|&quot;FIXME: Do alias check at line %d of cfi_probe.c&bslash;n&quot;
comma
id|__LINE__
)paren
suffix:semicolon
multiline_comment|/* Put it back into read mode */
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
l_int|0xffffffff
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
)brace
r_return
l_int|4
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read32
c_func
(paren
id|map
comma
id|base
op_plus
l_int|0x154
)paren
op_eq
l_int|0x98989898
)paren
(brace
multiline_comment|/* It looks like RAM. Put back the stuff we overwrote */
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
id|tmp
comma
id|base
op_plus
l_int|0x154
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cfi_probe called with strange buswidth %d&bslash;n&quot;
comma
id|map-&gt;buswidth
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|cfi_cfi_probe
r_static
r_struct
id|cfi_private
op_star
id|cfi_cfi_probe
c_func
(paren
r_struct
id|map_info
op_star
id|map
)paren
(brace
r_int
r_int
id|base
op_assign
l_int|0
suffix:semicolon
r_struct
id|cfi_private
id|cfi
suffix:semicolon
r_struct
id|cfi_private
op_star
id|retcfi
suffix:semicolon
r_struct
id|flchip
id|chip
(braket
id|MAX_CFI_CHIPS
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|cfi
comma
l_int|0
comma
r_sizeof
(paren
id|cfi
)paren
)paren
suffix:semicolon
multiline_comment|/* The first invocation (with chips == NULL) leaves the device in Query Mode */
id|cfi.interleave
op_assign
id|cfi_probe_new_chip
c_func
(paren
id|map
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi.interleave
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Found no CFI device at location zero&bslash;n&quot;
comma
id|map-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Doesn&squot;t appear to be CFI-compliant at all */
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Read the Basic Query Structure from the device */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
r_struct
id|cfi_ident
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|cfi.cfiq
)paren
(braket
id|i
)braket
op_assign
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
l_int|0x10
op_plus
id|i
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Do any necessary byteswapping */
id|cfi.cfiq.P_ID
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.P_ID
)paren
suffix:semicolon
id|cfi.cfiq.P_ADR
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.P_ADR
)paren
suffix:semicolon
id|cfi.cfiq.A_ID
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.A_ID
)paren
suffix:semicolon
id|cfi.cfiq.A_ADR
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.A_ADR
)paren
suffix:semicolon
id|cfi.cfiq.InterfaceDesc
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.InterfaceDesc
)paren
suffix:semicolon
id|cfi.cfiq.MaxBufWriteSize
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.cfiq.MaxBufWriteSize
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* Dump the information therein */
id|print_cfi_ident
c_func
(paren
op_amp
id|cfi.cfiq
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
id|cfi.cfiq.NumEraseRegions
suffix:semicolon
id|i
op_increment
)paren
(brace
id|__u16
id|EraseRegionInfoNum
op_assign
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
l_int|0x2d
op_plus
(paren
l_int|4
op_star
id|i
)paren
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
)paren
op_plus
(paren
(paren
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
(paren
l_int|0x2e
op_plus
(paren
l_int|4
op_star
id|i
)paren
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|__u16
id|EraseRegionInfoSize
op_assign
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
l_int|0x2f
op_plus
(paren
l_int|4
op_star
id|i
)paren
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
)paren
op_plus
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
l_int|0x30
op_plus
(paren
l_int|4
op_star
id|i
)paren
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Erase Region #%d: BlockSize 0x%4.4X bytes, %d blocks&bslash;n&quot;
comma
id|i
comma
id|EraseRegionInfoSize
op_star
l_int|256
comma
id|EraseRegionInfoNum
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
multiline_comment|/* Switch the chip back into Read Mode, to make the alias detection work */
r_switch
c_cond
(paren
id|map-&gt;buswidth
)paren
(brace
r_case
l_int|1
suffix:colon
id|map
op_member_access_from_pointer
id|write8
c_func
(paren
id|map
comma
l_int|0xff
comma
l_int|0x55
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|map
op_member_access_from_pointer
id|write16
c_func
(paren
id|map
comma
l_int|0xffff
comma
l_int|0xaa
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|map
op_member_access_from_pointer
id|write32
c_func
(paren
id|map
comma
l_int|0xffffffff
comma
l_int|0x154
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* OK. We&squot;ve worked out what it is and we&squot;re happy with it. Now see if there are others */
id|chip
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|chip
(braket
l_int|0
)braket
dot
id|state
op_assign
id|FL_READY
suffix:semicolon
id|chip
(braket
l_int|0
)braket
dot
id|mutex
op_assign
op_amp
id|chip
(braket
l_int|0
)braket
dot
id|_spinlock
suffix:semicolon
id|cfi.chipshift
op_assign
id|cfi.cfiq.DevSize
suffix:semicolon
id|cfi.numchips
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfi.chipshift
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cfi.chipsize is zero. This is bad. cfi.cfiq.DevSize is %d&bslash;n&quot;
comma
id|cfi.cfiq.DevSize
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|base
op_assign
(paren
l_int|1
op_lshift
id|cfi.chipshift
)paren
suffix:semicolon
id|base
OL
id|map-&gt;size
suffix:semicolon
id|base
op_add_assign
(paren
l_int|1
op_lshift
id|cfi.chipshift
)paren
)paren
id|cfi_probe_new_chip
c_func
(paren
id|map
comma
id|base
comma
op_amp
id|chip
(braket
l_int|0
)braket
comma
op_amp
id|cfi
)paren
suffix:semicolon
id|retcfi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cfi_private
)paren
op_plus
id|cfi.numchips
op_star
r_sizeof
(paren
r_struct
id|flchip
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retcfi
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|retcfi
comma
op_amp
id|cfi
comma
r_sizeof
(paren
id|cfi
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|retcfi-&gt;chips
(braket
l_int|0
)braket
comma
id|chip
comma
r_sizeof
(paren
r_struct
id|flchip
)paren
op_star
id|cfi.numchips
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
id|retcfi-&gt;numchips
suffix:semicolon
id|i
op_increment
)paren
(brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|retcfi-&gt;chips
(braket
id|i
)braket
dot
id|wq
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|retcfi-&gt;chips
(braket
id|i
)braket
dot
id|_spinlock
)paren
suffix:semicolon
)brace
r_return
id|retcfi
suffix:semicolon
)brace
DECL|function|vendorname
r_static
r_char
op_star
id|vendorname
c_func
(paren
id|__u16
id|vendor
)paren
(brace
r_switch
c_cond
(paren
id|vendor
)paren
(brace
r_case
id|P_ID_NONE
suffix:colon
r_return
l_string|&quot;None&quot;
suffix:semicolon
r_case
id|P_ID_INTEL_EXT
suffix:colon
r_return
l_string|&quot;Intel/Sharp Extended&quot;
suffix:semicolon
r_case
id|P_ID_AMD_STD
suffix:colon
r_return
l_string|&quot;AMD/Fujitsu Standard&quot;
suffix:semicolon
r_case
id|P_ID_INTEL_STD
suffix:colon
r_return
l_string|&quot;Intel/Sharp Standard&quot;
suffix:semicolon
r_case
id|P_ID_AMD_EXT
suffix:colon
r_return
l_string|&quot;AMD/Fujitsu Extended&quot;
suffix:semicolon
r_case
id|P_ID_MITSUBISHI_STD
suffix:colon
r_return
l_string|&quot;Mitsubishi Standard&quot;
suffix:semicolon
r_case
id|P_ID_MITSUBISHI_EXT
suffix:colon
r_return
l_string|&quot;Mitsubishi Extended&quot;
suffix:semicolon
r_case
id|P_ID_RESERVED
suffix:colon
r_return
l_string|&quot;Not Allowed / Reserved for Future Use&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;Unknown&quot;
suffix:semicolon
)brace
)brace
DECL|function|print_cfi_ident
r_static
r_void
id|print_cfi_ident
c_func
(paren
r_struct
id|cfi_ident
op_star
id|cfip
)paren
(brace
r_if
c_cond
(paren
id|cfip-&gt;qry
(braket
l_int|0
)braket
op_ne
l_char|&squot;Q&squot;
op_logical_or
id|cfip-&gt;qry
(braket
l_int|1
)braket
op_ne
l_char|&squot;R&squot;
op_logical_or
id|cfip-&gt;qry
(braket
l_int|2
)braket
op_ne
l_char|&squot;Y&squot;
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid CFI ident structure.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Primary Vendor Command Set: %4.4X (%s)&bslash;n&quot;
comma
id|cfip-&gt;P_ID
comma
id|vendorname
c_func
(paren
id|cfip-&gt;P_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;P_ADR
)paren
id|printk
c_func
(paren
l_string|&quot;Primary Algorithm Table at %4.4X&bslash;n&quot;
comma
id|cfip-&gt;P_ADR
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;No Primary Algorithm Table&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Alternative Vendor Command Set: %4.4X (%s)&bslash;n&quot;
comma
id|cfip-&gt;A_ID
comma
id|vendorname
c_func
(paren
id|cfip-&gt;A_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;A_ADR
)paren
id|printk
c_func
(paren
l_string|&quot;Alternate Algorithm Table at %4.4X&bslash;n&quot;
comma
id|cfip-&gt;A_ADR
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;No Alternate Algorithm Table&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vcc Minimum: %x.%x V&bslash;n&quot;
comma
id|cfip-&gt;VccMin
op_rshift
l_int|4
comma
id|cfip-&gt;VccMin
op_amp
l_int|0xf
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vcc Maximum: %x.%x V&bslash;n&quot;
comma
id|cfip-&gt;VccMax
op_rshift
l_int|4
comma
id|cfip-&gt;VccMax
op_amp
l_int|0xf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;VppMin
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Vpp Minimum: %x.%x V&bslash;n&quot;
comma
id|cfip-&gt;VppMin
op_rshift
l_int|4
comma
id|cfip-&gt;VppMin
op_amp
l_int|0xf
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Vpp Maximum: %x.%x V&bslash;n&quot;
comma
id|cfip-&gt;VppMax
op_rshift
l_int|4
comma
id|cfip-&gt;VppMax
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;No Vpp line&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Typical byte/word write timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum byte/word write timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;WordWriteTimeoutTyp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;BufWriteTimeoutTyp
op_logical_or
id|cfip-&gt;BufWriteTimeoutMax
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Typical full buffer write timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum full buffer write timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;BufWriteTimeoutTyp
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Full buffer write not supported&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Typical block erase timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum block erase timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;BlockEraseTimeoutTyp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfip-&gt;ChipEraseTimeoutTyp
op_logical_or
id|cfip-&gt;ChipEraseTimeoutMax
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Typical chip erase timeout: %d &#xfffd;s&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutTyp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Maximum chip erase timeout: %d &#xfffd;s&bslash;n&quot;
comma
(paren
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutMax
)paren
op_star
(paren
l_int|1
op_lshift
id|cfip-&gt;ChipEraseTimeoutTyp
)paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Chip erase not supported&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Device size: 0x%X bytes (%d Mb)&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;DevSize
comma
l_int|1
op_lshift
(paren
id|cfip-&gt;DevSize
op_minus
l_int|20
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Flash Device Interface description: 0x%4.4X&bslash;n&quot;
comma
id|cfip-&gt;InterfaceDesc
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cfip-&gt;InterfaceDesc
)paren
(brace
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x8-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x16-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - supports x8 and x16 via BYTE# with asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - x32-only asynchronous interface&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|65535
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Not Allowed / Reserved&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;  - Unknown&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Max. bytes in buffer write: 0x%x&bslash;n&quot;
comma
l_int|1
op_lshift
id|cfip-&gt;MaxBufWriteSize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Number of Erase Block Regions: %d&bslash;n&quot;
comma
id|cfip-&gt;NumEraseRegions
)paren
suffix:semicolon
)brace
DECL|function|check_cmd_set
r_static
r_void
id|check_cmd_set
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_int
id|primary
comma
r_int
r_int
id|base
)paren
(brace
id|__u16
id|adr
suffix:semicolon
r_struct
id|cfi_private
op_star
id|cfi
op_assign
id|map-&gt;fldrv_priv
suffix:semicolon
id|__u16
id|type
op_assign
id|primary
ques
c_cond
id|cfi-&gt;cfiq.P_ID
suffix:colon
id|cfi-&gt;cfiq.A_ID
suffix:semicolon
r_char
id|probename
(braket
l_int|32
)braket
suffix:semicolon
r_void
(paren
op_star
id|probe_function
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|P_ID_NONE
op_logical_or
id|type
op_eq
id|P_ID_RESERVED
)paren
r_return
suffix:semicolon
id|sprintf
c_func
(paren
id|probename
comma
l_string|&quot;cfi_cmdset_%4.4X&quot;
comma
id|type
)paren
suffix:semicolon
id|probe_function
op_assign
id|inter_module_get_request
c_func
(paren
id|probename
comma
id|probename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|probe_function
)paren
(brace
(paren
op_star
id|probe_function
)paren
(paren
id|map
comma
id|primary
comma
id|base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This was a command set we don&squot;t know about. Print only the basic info */
id|adr
op_assign
id|primary
ques
c_cond
id|cfi-&gt;cfiq.P_ADR
suffix:colon
id|cfi-&gt;cfiq.A_ADR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; No Extended Query Table&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
id|adr
op_star
id|map-&gt;buswidth
)paren
)paren
op_ne
(paren
id|primary
ques
c_cond
l_char|&squot;P&squot;
suffix:colon
l_char|&squot;A&squot;
)paren
op_logical_or
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|1
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
op_ne
(paren
id|primary
ques
c_cond
l_char|&squot;R&squot;
suffix:colon
l_char|&squot;L&squot;
)paren
op_logical_or
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|2
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
op_ne
(paren
id|primary
ques
c_cond
l_char|&squot;I&squot;
suffix:colon
l_char|&squot;T&squot;
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Invalid Extended Query Table at %4.4X: %2.2X %2.2X %2.2X&bslash;n&quot;
comma
id|adr
comma
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
id|adr
op_star
id|map-&gt;buswidth
)paren
)paren
comma
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|1
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
comma
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|2
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; Extended Query Table version %c.%c&bslash;n&quot;
comma
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|3
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
comma
id|map
op_member_access_from_pointer
id|read8
c_func
(paren
id|map
comma
id|base
op_plus
(paren
(paren
id|adr
op_plus
l_int|4
)paren
op_star
id|map-&gt;buswidth
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|cfi_probe_init
r_static
r_int
id|__init
id|cfi_probe_init
c_func
(paren
r_void
)paren
(brace
id|inter_module_register
c_func
(paren
id|im_name
comma
id|THIS_MODULE
comma
op_amp
id|cfi_probe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cfi_probe_exit
r_static
r_void
id|__exit
id|cfi_probe_exit
c_func
(paren
r_void
)paren
(brace
id|inter_module_unregister
c_func
(paren
id|im_name
)paren
suffix:semicolon
)brace
DECL|variable|cfi_probe_init
id|module_init
c_func
(paren
id|cfi_probe_init
)paren
suffix:semicolon
DECL|variable|cfi_probe_exit
id|module_exit
c_func
(paren
id|cfi_probe_exit
)paren
suffix:semicolon
eof
