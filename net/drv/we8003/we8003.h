multiline_comment|/*&n; * we8003.h&t;Define the interface of the WE8003 Ethernet driver.&n; *&n; * Version:&t;@(#)we8003.h&t;1.0.0&t;(02/11/93)&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_WE8003_H
DECL|macro|_LINUX_WE8003_H
mdefine_line|#define _LINUX_WE8003_H
DECL|macro|CONF_WE8003
mdefine_line|#define CONF_WE8003&t;0&t;&t;/* add this driver to kernel&t;*/
DECL|macro|FORCE_8BIT
mdefine_line|#define FORCE_8BIT&t;0&t;&t;/* for forcing the WD8003 mode&t;*/
DECL|macro|WE_DEBUG
mdefine_line|#define&t;WE_DEBUG
macro_line|#ifdef&t;WE_DEBUG
DECL|macro|PRINTK
macro_line|#   define PRINTK(x)&t;printk x
macro_line|#else
DECL|macro|PRINTK
macro_line|#   define PRINTK(x)&t;/**/
macro_line|#endif
DECL|macro|NR_WE8003
mdefine_line|#define&t;NR_WE8003&t;4&t;&t;/* max number of units&t;&t;*/
DECL|macro|WE_NAME
mdefine_line|#define WE_NAME&t;&t;&quot;WE8003.%d&quot;&t;/* our DDI ID string&t;&t;*/
r_extern
r_struct
id|ddi_device
op_star
id|we_ptrs
(braket
id|NR_WE8003
)braket
suffix:semicolon
multiline_comment|/* pointers to DDI blocks&t;*/
r_extern
r_int
id|we8003_init
c_func
(paren
r_struct
id|ddi_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_WE8003_H */
eof
