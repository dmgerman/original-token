multiline_comment|/*&n; * xor.c : Multiple Devices driver for Linux&n; *&n; * Copyright (C) 1996, 1997, 1998, 1999, 2000,&n; * Ingo Molnar, Matti Aarnio, Jakub Jelinek, Richard Henderson.&n; *&n; * Dispatch optimized RAID-5 checksumming functions.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * You should have received a copy of the GNU General Public License&n; * (for example /usr/src/linux/COPYING); if not, write to the Free&n; * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|BH_TRACE
mdefine_line|#define BH_TRACE 0
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &lt;linux/raid/xor.h&gt;
macro_line|#include &lt;asm/xor.h&gt;
multiline_comment|/* The xor routines to use.  */
DECL|variable|active_template
r_static
r_struct
id|xor_block_template
op_star
id|active_template
suffix:semicolon
r_void
DECL|function|xor_block
id|xor_block
c_func
(paren
r_int
r_int
id|count
comma
r_struct
id|buffer_head
op_star
op_star
id|bh_ptr
)paren
(brace
r_int
r_int
op_star
id|p0
comma
op_star
id|p1
comma
op_star
id|p2
comma
op_star
id|p3
comma
op_star
id|p4
suffix:semicolon
r_int
r_int
id|bytes
op_assign
id|bh_ptr
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_size
suffix:semicolon
id|p0
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh_ptr
(braket
l_int|0
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
id|p1
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh_ptr
(braket
l_int|1
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|2
)paren
(brace
id|active_template
op_member_access_from_pointer
id|do_2
c_func
(paren
id|bytes
comma
id|p0
comma
id|p1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p2
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh_ptr
(braket
l_int|2
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|3
)paren
(brace
id|active_template
op_member_access_from_pointer
id|do_3
c_func
(paren
id|bytes
comma
id|p0
comma
id|p1
comma
id|p2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p3
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh_ptr
(braket
l_int|3
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|4
)paren
(brace
id|active_template
op_member_access_from_pointer
id|do_4
c_func
(paren
id|bytes
comma
id|p0
comma
id|p1
comma
id|p2
comma
id|p3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p4
op_assign
(paren
r_int
r_int
op_star
)paren
id|bh_ptr
(braket
l_int|4
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
id|active_template
op_member_access_from_pointer
id|do_5
c_func
(paren
id|bytes
comma
id|p0
comma
id|p1
comma
id|p2
comma
id|p3
comma
id|p4
)paren
suffix:semicolon
)brace
multiline_comment|/* Set of all registered templates.  */
DECL|variable|template_list
r_static
r_struct
id|xor_block_template
op_star
id|template_list
suffix:semicolon
multiline_comment|/* The -6*32 shift factor colors the cache.  */
DECL|macro|BENCH_SIZE
mdefine_line|#define BENCH_SIZE (PAGE_SIZE-6*32)
r_static
r_void
DECL|function|do_xor_speed
id|do_xor_speed
c_func
(paren
r_struct
id|xor_block_template
op_star
id|tmpl
comma
r_void
op_star
id|b1
comma
r_void
op_star
id|b2
)paren
(brace
r_int
id|speed
suffix:semicolon
r_int
r_int
id|now
suffix:semicolon
r_int
id|i
comma
id|count
comma
id|max
suffix:semicolon
id|tmpl-&gt;next
op_assign
id|template_list
suffix:semicolon
id|template_list
op_assign
id|tmpl
suffix:semicolon
multiline_comment|/*&n;&t; * Count the number of XORs done during a whole jiffy, and use&n;&t; * this to calculate the speed of checksumming.  We use a 2-page&n;&t; * allocation to have guaranteed color L1-cache layout.&n;&t; */
id|max
op_assign
l_int|0
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|now
op_assign
id|jiffies
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|jiffies
op_eq
id|now
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|tmpl
op_member_access_from_pointer
id|do_2
c_func
(paren
id|BENCH_SIZE
comma
id|b1
comma
id|b2
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|max
)paren
id|max
op_assign
id|count
suffix:semicolon
)brace
id|speed
op_assign
id|max
op_star
(paren
id|HZ
op_star
id|BENCH_SIZE
op_div
l_int|1024
)paren
suffix:semicolon
id|tmpl-&gt;speed
op_assign
id|speed
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;   %-10s: %5d.%03d MB/sec&bslash;n&quot;
comma
id|tmpl-&gt;name
comma
id|speed
op_div
l_int|1000
comma
id|speed
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|calibrate_xor_block
id|calibrate_xor_block
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|b1
comma
op_star
id|b2
suffix:semicolon
r_struct
id|xor_block_template
op_star
id|f
comma
op_star
id|fastest
suffix:semicolon
id|b1
op_assign
(paren
r_void
op_star
)paren
id|md__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;raid5: Yikes!  No memory available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|b2
op_assign
id|b1
op_plus
l_int|2
op_star
id|PAGE_SIZE
op_plus
id|BENCH_SIZE
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;raid5: measuring checksumming speed&bslash;n&quot;
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
DECL|macro|xor_speed
mdefine_line|#define xor_speed(templ)&t;do_xor_speed((templ), b1, b2)
id|XOR_TRY_TEMPLATES
suffix:semicolon
DECL|macro|xor_speed
macro_line|#undef xor_speed
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|b1
comma
l_int|2
)paren
suffix:semicolon
id|fastest
op_assign
id|template_list
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|fastest
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
r_if
c_cond
(paren
id|f-&gt;speed
OG
id|fastest-&gt;speed
)paren
id|fastest
op_assign
id|f
suffix:semicolon
macro_line|#ifdef XOR_SELECT_TEMPLATE
id|fastest
op_assign
id|XOR_SELECT_TEMPLATE
c_func
(paren
id|fastest
)paren
suffix:semicolon
macro_line|#endif
id|active_template
op_assign
id|fastest
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;raid5: using function: %s (%d.%03d MB/sec)&bslash;n&quot;
comma
id|fastest-&gt;name
comma
id|fastest-&gt;speed
op_div
l_int|1000
comma
id|fastest-&gt;speed
op_mod
l_int|1000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xor_block
id|MD_EXPORT_SYMBOL
c_func
(paren
id|xor_block
)paren
suffix:semicolon
DECL|variable|calibrate_xor_block
id|module_init
c_func
(paren
id|calibrate_xor_block
)paren
suffix:semicolon
eof
