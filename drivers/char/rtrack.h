multiline_comment|/* RadioTrack (RadioReveal) include file.&n; * (c) 1997 M. Kirkwood&n; *&n; * Not in include/linux/ because there&squot;s no need for anyone&n; * to know about these details, I reckon.&n; */
macro_line|#ifndef __RTRACK_H
DECL|macro|__RTRACK_H
mdefine_line|#define __RTRACK_H
macro_line|#include &lt;linux/radio.h&gt;
r_void
id|radiotrack_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|rt_setvol
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|vol
)paren
suffix:semicolon
r_int
id|rt_setband
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|vol
)paren
suffix:semicolon
r_int
id|rt_setfreq
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|vol
)paren
suffix:semicolon
r_int
id|rt_getsigstr
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* frequency encoding stuff... */
multiline_comment|/* we have to careful not to introduce fp stuff here */
DECL|macro|RTRACK_ENCODE
mdefine_line|#define&t;RTRACK_ENCODE(x)&t;(((((x)*2)/5)-(40*88))+0xf6c)
DECL|macro|RTRACK_DECODE
mdefine_line|#define&t;RTRACK_DECODE(x)&t;(((((x)-0xf6c)+(40*88))*5)/2)
multiline_comment|/* we shouldn&squot;t actually need the decode macro (or the excessive bracketing :-) */
macro_line|#endif /* __RTRACK_H */
eof
