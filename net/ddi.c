multiline_comment|/*&n; * ddi.c&t;Implement the Device Driver Interface (DDI) routines.&n; *&t;&t;Currently, this is only used by the NET layer of LINUX,&n; *&t;&t;but it eventually might move to an upper directory of&n; *&t;&t;the system.&n; *&n; * Version:&t;@(#)ddi.c&t;1.0.5&t;04/22/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; *&n; *&n; *&t;For the moment I&squot;m classifying DDI as &squot;dead&squot;. However if/when Fred&n; *&t;produces a masterpiece of design DDI may get resurrected. With the&n; *&t;current kernel as modules work by Peter MacDonald they might be&n; *&t;redundant anyway. Thus I&squot;ve removed all but the protocol initialise.&n; *&n; *&t;We will end up with protocol initialisers and socket family initialisers.&n; */
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
id|ddi_proto
id|protocols
(braket
)braket
suffix:semicolon
multiline_comment|/* network protocols&t;*/
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
id|PRINTK
(paren
(paren
l_string|&quot;DDI: Starting up!&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Kick all configured protocols. */
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
multiline_comment|/* We&squot;re all done... */
)brace
eof
