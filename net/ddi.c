multiline_comment|/*&n; * ddi.c&t;Implement the Device Driver Interface (DDI) routines.&n; *&t;&t;Currently, this is only used by the NET layer of LINUX,&n; *&t;&t;but it eventually might move to an upper directory of&n; *&t;&t;the system.&n; *&n; * Version:&t;@(#)ddi.c&t;1.0.5&t;04/22/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/ddi.h&gt;
DECL|macro|DDI_DEBUG
macro_line|#undef&t;DDI_DEBUG
macro_line|#ifdef&t;DDI_DEBUG
DECL|macro|PRINTK
macro_line|#   define PRINTK(x)&t;printk x
macro_line|#else
DECL|macro|PRINTK
macro_line|#   define PRINTK(x)&t;/**/
macro_line|#endif
r_extern
r_struct
id|ddi_device
id|devices
(braket
)braket
suffix:semicolon
multiline_comment|/* device driver map&t;*/
r_extern
r_struct
id|ddi_proto
id|protocols
(braket
)braket
suffix:semicolon
multiline_comment|/* network protocols&t;*/
multiline_comment|/*&n; * This function gets called with an ASCII string representing the&n; * ID of some DDI driver.  We loop through the DDI Devices table&n; * and return the address of the control block that has a matching&n; * &quot;name&quot; field.  It is used by upper-level layers that want to&n; * dynamically bind some UNIX-domain &quot;/dev/XXXX&quot; file name to a&n; * DDI device driver.  The &quot;iflink(8)&quot; program is an example of&n; * this behaviour.&n; */
r_struct
id|ddi_device
op_star
DECL|function|ddi_map
id|ddi_map
c_func
(paren
r_const
r_char
op_star
id|id
)paren
(brace
r_register
r_struct
id|ddi_device
op_star
id|dev
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;DDI: MAP: looking for &bslash;&quot;%s&bslash;&quot;: &quot;
comma
id|id
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|devices
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;title
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
id|id
comma
id|DDI_MAXNAME
)paren
op_eq
l_int|0
)paren
(brace
id|PRINTK
(paren
(paren
l_string|&quot;OK at 0x%X&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
id|dev
op_increment
suffix:semicolon
)brace
id|PRINTK
(paren
(paren
l_string|&quot;NOT FOUND&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the function that is called by a kernel routine during&n; * system startup.  Its purpose is to walk trough the &quot;devices&quot;&n; * table (defined above), and to call all moduled defined in it.&n; */
r_void
DECL|function|ddi_init
id|ddi_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|ddi_proto
op_star
id|pro
suffix:semicolon
r_struct
id|ddi_device
op_star
id|dev
suffix:semicolon
id|PRINTK
(paren
(paren
l_string|&quot;DDI: Starting up!&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* First off, kick all configured protocols. */
id|pro
op_assign
id|protocols
suffix:semicolon
r_while
c_loop
(paren
id|pro-&gt;name
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|pro-&gt;init
)paren
(paren
id|pro
)paren
suffix:semicolon
id|pro
op_increment
suffix:semicolon
)brace
multiline_comment|/* Done.  Now kick all configured device drivers. */
id|dev
op_assign
id|devices
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;title
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|dev-&gt;init
)paren
(paren
id|dev
)paren
suffix:semicolon
id|dev
op_increment
suffix:semicolon
)brace
multiline_comment|/* We&squot;re all done... */
)brace
eof
