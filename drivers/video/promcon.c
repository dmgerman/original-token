multiline_comment|/* $Id: promcon.c,v 1.6 1998/07/19 12:49:26 mj Exp $&n; * Console driver utilizing PROM sun terminal emulation&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; * Copyright (C) 1998  Jakub Jelinek  (jj@ultra.linux.cz)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
DECL|variable|pw
DECL|variable|ph
r_static
r_int
id|pw
op_assign
l_int|80
op_minus
l_int|1
comma
id|ph
op_assign
l_int|34
op_minus
l_int|1
suffix:semicolon
DECL|variable|px
DECL|variable|py
r_static
r_int
id|px
comma
id|py
suffix:semicolon
DECL|macro|PROMCON_COLOR
mdefine_line|#define PROMCON_COLOR 1
macro_line|#if PROMCON_COLOR
DECL|macro|inverted
mdefine_line|#define inverted(s)&t;((((s) &amp; 0x7700) == 0x0700) ? 0 : 1)
macro_line|#else
DECL|macro|inverted
mdefine_line|#define inverted(s)&t;(((s) &amp; 0x0800) ? 1 : 0)
macro_line|#endif
r_static
id|__inline__
r_void
DECL|function|promcon_puts
id|promcon_puts
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|cnt
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;%*.*s&quot;
comma
id|cnt
comma
id|cnt
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|promcon_start
id|promcon_start
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_char
op_star
id|b
)paren
(brace
r_int
r_int
op_star
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|conp-&gt;vc_origin
op_plus
id|py
op_star
id|conp-&gt;vc_size_row
op_plus
(paren
id|px
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|px
op_eq
id|pw
)paren
(brace
r_int
r_int
op_star
id|t
op_assign
id|s
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
op_logical_and
id|inverted
c_func
(paren
op_star
id|t
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b&bslash;033[7m%c&bslash;b&bslash;033[@%c&bslash;033[m&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b&bslash;033[7m%c&bslash;033[m&bslash;b&bslash;033[@%c&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|t
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b%c&bslash;b&bslash;033[@&bslash;033[7m%c&bslash;033[m&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b%c&bslash;b&bslash;033[@%c&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
)paren
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[7m%c&bslash;033[m&bslash;b&quot;
comma
op_star
id|s
)paren
suffix:semicolon
r_else
r_return
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;%c&bslash;b&quot;
comma
op_star
id|s
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|promcon_end
id|promcon_end
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_char
op_star
id|b
)paren
(brace
r_int
r_int
op_star
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|conp-&gt;vc_origin
op_plus
id|py
op_star
id|conp-&gt;vc_size_row
op_plus
(paren
id|px
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|b
suffix:semicolon
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|py
op_plus
l_int|1
comma
id|px
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|px
op_eq
id|pw
)paren
(brace
r_int
r_int
op_star
id|t
op_assign
id|s
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
op_logical_and
id|inverted
c_func
(paren
op_star
id|t
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b%c&bslash;b&bslash;033[@&bslash;033[7m%c&bslash;033[m&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b%c&bslash;b&bslash;033[@%c&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|t
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b&bslash;033[7m%c&bslash;b&bslash;033[@%c&bslash;033[m&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_else
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b&bslash;033[7m%c&bslash;033[m&bslash;b&bslash;033[@%c&quot;
comma
op_star
id|s
comma
op_star
id|t
)paren
suffix:semicolon
r_return
id|b
op_minus
id|p
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inverted
c_func
(paren
op_star
id|s
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;%c&bslash;b&quot;
comma
op_star
id|s
)paren
suffix:semicolon
r_else
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[7m%c&bslash;033[m&bslash;b&quot;
comma
op_star
id|s
)paren
suffix:semicolon
r_return
id|b
op_minus
id|p
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_const
r_char
op_star
id|promcon_startup
c_func
(paren
r_void
)paren
)paren
(brace
r_const
r_char
op_star
id|display_desc
op_assign
l_string|&quot;PROM&quot;
suffix:semicolon
r_int
id|node
suffix:semicolon
r_char
id|buf
(braket
l_int|40
)braket
suffix:semicolon
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;options&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;screen-#columns&quot;
comma
id|buf
comma
l_int|40
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|pw
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pw
template_param
l_int|256
)paren
id|pw
op_assign
l_int|80
suffix:semicolon
id|pw
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;screen-#rows&quot;
comma
id|buf
comma
l_int|40
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|ph
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ph
template_param
l_int|256
)paren
id|ph
op_assign
l_int|34
suffix:semicolon
id|ph
op_decrement
suffix:semicolon
)brace
id|promcon_puts
c_func
(paren
l_string|&quot;&bslash;033[H&bslash;033[J&quot;
comma
l_int|6
)paren
suffix:semicolon
r_return
id|display_desc
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_init
id|promcon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|init
)paren
(brace
id|conp-&gt;vc_can_do_color
op_assign
id|PROMCON_COLOR
suffix:semicolon
id|conp-&gt;vc_cols
op_assign
id|pw
op_plus
l_int|1
suffix:semicolon
id|conp-&gt;vc_rows
op_assign
id|ph
op_plus
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|promcon_switch
id|promcon_switch
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
r_int
op_star
DECL|function|promcon_repaint_line
id|promcon_repaint_line
c_func
(paren
r_int
r_int
op_star
id|s
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_char
op_star
op_star
id|bp
)paren
(brace
r_int
id|cnt
op_assign
id|pw
op_plus
l_int|1
suffix:semicolon
r_int
id|attr
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_char
op_star
id|b
op_assign
op_star
id|bp
suffix:semicolon
r_while
c_loop
(paren
id|cnt
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|attr
op_ne
id|inverted
c_func
(paren
op_star
id|s
)paren
)paren
(brace
id|attr
op_assign
id|inverted
c_func
(paren
op_star
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr
)paren
(brace
id|strcpy
(paren
id|b
comma
l_string|&quot;&bslash;033[7m&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|strcpy
(paren
id|b
comma
l_string|&quot;&bslash;033[m&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|3
suffix:semicolon
)brace
)brace
op_star
id|b
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|b
op_minus
id|buf
op_ge
l_int|224
)paren
(brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
id|b
op_assign
id|buf
suffix:semicolon
)brace
)brace
op_star
id|bp
op_assign
id|b
suffix:semicolon
r_return
id|s
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_putcs
id|promcon_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|256
)braket
comma
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_int
r_int
id|attr
op_assign
op_star
id|s
suffix:semicolon
r_int
r_char
id|save
suffix:semicolon
r_int
id|i
comma
id|last
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|console_blanked
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|b
op_add_assign
id|promcon_start
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
op_plus
id|count
op_ge
id|pw
op_plus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|1
)paren
(brace
id|x
op_sub_assign
l_int|1
suffix:semicolon
id|save
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|conp-&gt;vc_origin
op_plus
id|y
op_star
id|conp-&gt;vc_size_row
op_plus
(paren
id|x
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|px
op_ne
id|x
op_logical_or
id|py
op_ne
id|y
)paren
(brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|y
op_plus
l_int|1
comma
id|x
op_plus
l_int|1
)paren
suffix:semicolon
id|px
op_assign
id|x
suffix:semicolon
id|py
op_assign
id|y
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inverted
c_func
(paren
id|attr
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[7m%c&bslash;033[m&quot;
comma
op_star
id|s
op_increment
)paren
suffix:semicolon
r_else
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;%c&quot;
comma
op_star
id|s
op_increment
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;b&bslash;033[@&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|inverted
c_func
(paren
id|save
)paren
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[7m%c&bslash;033[m&quot;
comma
id|save
)paren
suffix:semicolon
r_else
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;%c&quot;
comma
id|save
)paren
suffix:semicolon
id|px
op_increment
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|last
op_assign
l_int|1
suffix:semicolon
id|count
op_assign
id|pw
op_minus
id|x
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|inverted
c_func
(paren
id|attr
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[7m&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|px
op_ne
id|x
op_logical_or
id|py
op_ne
id|y
)paren
(brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|y
op_plus
l_int|1
comma
id|x
op_plus
l_int|1
)paren
suffix:semicolon
id|px
op_assign
id|x
suffix:semicolon
id|py
op_assign
id|y
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|b
op_minus
id|buf
op_ge
l_int|224
)paren
(brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
id|b
op_assign
id|buf
suffix:semicolon
)brace
op_star
id|b
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
id|px
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|last
)paren
(brace
id|save
op_assign
op_star
id|s
op_increment
suffix:semicolon
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;%c&bslash;b&bslash;033[@%c&quot;
comma
op_star
id|s
op_increment
comma
id|save
)paren
suffix:semicolon
id|px
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inverted
c_func
(paren
id|attr
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[m&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|3
suffix:semicolon
)brace
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_putc
id|promcon_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|c
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
r_int
r_int
id|s
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|console_blanked
)paren
r_return
suffix:semicolon
id|promcon_putcs
c_func
(paren
id|conp
comma
op_amp
id|s
comma
l_int|1
comma
id|y
comma
id|x
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_clear
id|promcon_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|256
)braket
comma
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|console_blanked
)paren
r_return
suffix:semicolon
id|b
op_add_assign
id|promcon_start
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sx
op_logical_and
id|width
op_eq
id|pw
op_plus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sy
op_logical_and
id|height
op_eq
id|ph
op_plus
l_int|1
)paren
(brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[H&bslash;033[J&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|6
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sy
op_plus
id|height
op_eq
id|ph
op_plus
l_int|1
)paren
(brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%dH&bslash;033[J&quot;
comma
id|sy
op_plus
l_int|1
)paren
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%dH&quot;
comma
id|sy
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|height
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[K&bslash;n&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|4
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[K&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|3
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sx
op_plus
id|width
op_eq
id|pw
op_plus
l_int|1
)paren
(brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|sy
op_plus
l_int|1
comma
id|sx
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|height
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[K&bslash;n&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|4
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[K&quot;
)paren
suffix:semicolon
id|b
op_add_assign
l_int|3
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|sy
op_plus
l_int|1
suffix:semicolon
id|i
op_le
id|sy
op_plus
id|height
suffix:semicolon
id|i
op_increment
)paren
(brace
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|i
comma
id|sx
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|width
suffix:semicolon
id|j
op_increment
)paren
op_star
id|b
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
id|b
op_minus
id|buf
op_plus
id|width
op_ge
l_int|224
)paren
(brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
id|b
op_assign
id|buf
suffix:semicolon
)brace
)brace
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_bmove
id|promcon_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
r_char
id|buf
(braket
l_int|256
)braket
comma
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|console_blanked
)paren
r_return
suffix:semicolon
id|b
op_add_assign
id|promcon_start
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sy
op_eq
id|dy
op_logical_and
id|height
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|dx
OG
id|sx
op_logical_and
id|dx
op_plus
id|width
op_eq
id|conp-&gt;vc_cols
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&bslash;033[%d@&bslash;033[%d;%dH&quot;
comma
id|sy
op_plus
l_int|1
comma
id|sx
op_plus
l_int|1
comma
id|dx
op_minus
id|sx
comma
id|py
op_plus
l_int|1
comma
id|px
op_plus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dx
OL
id|sx
op_logical_and
id|sx
op_plus
id|width
op_eq
id|conp-&gt;vc_cols
)paren
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&bslash;033[%dP&bslash;033[%d;%dH&quot;
comma
id|dy
op_plus
l_int|1
comma
id|dx
op_plus
l_int|1
comma
id|sx
op_minus
id|dx
comma
id|py
op_plus
l_int|1
comma
id|px
op_plus
l_int|1
)paren
suffix:semicolon
id|b
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FIXME: What to do here???&n;&t; * Current console.c should not call it like that ever.&n;&t; */
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;033[7mFIXME: bmove not handled&bslash;033[m&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|promcon_cursor
id|promcon_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|mode
)paren
(brace
r_char
id|buf
(braket
l_int|32
)braket
comma
op_star
id|b
op_assign
id|buf
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
r_break
suffix:semicolon
r_case
id|CM_MOVE
suffix:colon
r_case
id|CM_DRAW
suffix:colon
id|b
op_add_assign
id|promcon_start
c_func
(paren
id|conp
comma
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|px
op_ne
id|conp-&gt;vc_x
op_logical_or
id|py
op_ne
id|conp-&gt;vc_y
)paren
(brace
id|px
op_assign
id|conp-&gt;vc_x
suffix:semicolon
id|py
op_assign
id|conp-&gt;vc_y
suffix:semicolon
id|b
op_add_assign
id|sprintf
c_func
(paren
id|b
comma
l_string|&quot;&bslash;033[%d;%dH&quot;
comma
id|py
op_plus
l_int|1
comma
id|px
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|b
op_minus
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|promcon_font_op
id|promcon_font_op
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|console_font_op
op_star
id|op
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_static
r_int
DECL|function|promcon_blank
id|promcon_blank
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|blank
)paren
(brace
r_if
c_cond
(paren
id|blank
)paren
(brace
id|promcon_puts
c_func
(paren
l_string|&quot;&bslash;033[H&bslash;033[J&bslash;033[7m &bslash;033[m&bslash;b&quot;
comma
l_int|15
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Let console.c redraw */
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|promcon_scroll
id|promcon_scroll
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_int
id|t
comma
r_int
id|b
comma
r_int
id|dir
comma
r_int
id|count
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|256
)braket
comma
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_int
r_int
op_star
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|console_blanked
)paren
r_return
l_int|0
suffix:semicolon
id|p
op_add_assign
id|promcon_start
c_func
(paren
id|conp
comma
id|p
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dir
)paren
(brace
r_case
id|SM_UP
suffix:colon
r_if
c_cond
(paren
id|b
op_eq
id|ph
op_plus
l_int|1
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[%dH&bslash;033[%dM&quot;
comma
id|t
op_plus
l_int|1
comma
id|count
)paren
suffix:semicolon
id|px
op_assign
l_int|0
suffix:semicolon
id|py
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|p
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|conp-&gt;vc_origin
op_plus
(paren
id|t
op_plus
id|count
)paren
op_star
id|conp-&gt;vc_size_row
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[%dH&quot;
comma
id|t
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|t
suffix:semicolon
id|i
OL
id|b
op_minus
id|count
suffix:semicolon
id|i
op_increment
)paren
id|s
op_assign
id|promcon_repaint_line
c_func
(paren
id|s
comma
id|buf
comma
op_amp
id|p
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|b
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[K&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p
op_minus
id|buf
op_ge
l_int|224
)paren
(brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
)brace
)brace
id|strcpy
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[K&quot;
)paren
suffix:semicolon
id|p
op_add_assign
l_int|3
suffix:semicolon
id|p
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|p
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SM_DOWN
suffix:colon
r_if
c_cond
(paren
id|b
op_eq
id|ph
op_plus
l_int|1
)paren
(brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[%dH&bslash;033[%dL&quot;
comma
id|t
op_plus
l_int|1
comma
id|count
)paren
suffix:semicolon
id|px
op_assign
l_int|0
suffix:semicolon
id|py
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|p
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|conp-&gt;vc_origin
op_plus
id|t
op_star
id|conp-&gt;vc_size_row
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[%dH&quot;
comma
id|t
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|t
suffix:semicolon
id|i
OL
id|t
op_plus
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|p
comma
l_string|&quot;&bslash;033[K&bslash;n&quot;
)paren
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p
op_minus
id|buf
op_ge
l_int|224
)paren
(brace
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|b
suffix:semicolon
id|i
op_increment
)paren
id|s
op_assign
id|promcon_repaint_line
c_func
(paren
id|s
comma
id|buf
comma
op_amp
id|p
)paren
suffix:semicolon
id|p
op_add_assign
id|promcon_end
c_func
(paren
id|conp
comma
id|p
)paren
suffix:semicolon
id|promcon_puts
c_func
(paren
id|buf
comma
id|p
op_minus
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  The console &squot;switch&squot; structure for the VGA based console&n; */
DECL|function|promcon_dummy
r_static
r_int
id|promcon_dummy
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|DUMMY
mdefine_line|#define DUMMY (void *) promcon_dummy
DECL|variable|prom_con
r_struct
id|consw
id|prom_con
op_assign
(brace
id|con_startup
suffix:colon
id|promcon_startup
comma
id|con_init
suffix:colon
id|promcon_init
comma
id|con_deinit
suffix:colon
id|DUMMY
comma
id|con_clear
suffix:colon
id|promcon_clear
comma
id|con_putc
suffix:colon
id|promcon_putc
comma
id|con_putcs
suffix:colon
id|promcon_putcs
comma
id|con_cursor
suffix:colon
id|promcon_cursor
comma
id|con_scroll
suffix:colon
id|promcon_scroll
comma
id|con_bmove
suffix:colon
id|promcon_bmove
comma
id|con_switch
suffix:colon
id|promcon_switch
comma
id|con_blank
suffix:colon
id|promcon_blank
comma
id|con_font_op
suffix:colon
id|promcon_font_op
comma
id|con_set_palette
suffix:colon
id|DUMMY
comma
id|con_scrolldelta
suffix:colon
id|DUMMY
comma
id|con_set_origin
suffix:colon
l_int|NULL
comma
id|con_save_screen
suffix:colon
l_int|NULL
comma
id|con_build_attr
suffix:colon
l_int|NULL
comma
id|con_invert_region
suffix:colon
l_int|NULL
comma
)brace
suffix:semicolon
eof
