multiline_comment|/*&n;   raid0.c : Multiple Devices driver for Linux&n;             Copyright (C) 1994-96 Marc ZYNGIER&n;&t;     &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;     &lt;maz@gloups.fdn.fr&gt;&n;&n;   RAID-0 management functions.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/md.h&gt;
macro_line|#include &lt;linux/raid0.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR MD_MAJOR
DECL|macro|MD_DRIVER
mdefine_line|#define MD_DRIVER
DECL|macro|MD_PERSONALITY
mdefine_line|#define MD_PERSONALITY
DECL|function|create_strip_zones
r_static
r_void
id|create_strip_zones
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
(brace
r_int
id|i
comma
id|j
comma
id|c
op_assign
l_int|0
suffix:semicolon
r_int
id|current_offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|real_dev
op_star
id|smallest_by_zone
suffix:semicolon
r_struct
id|raid0_data
op_star
id|data
op_assign
(paren
r_struct
id|raid0_data
op_star
)paren
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
id|data-&gt;nr_strip_zones
op_assign
l_int|1
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
id|mddev-&gt;nb_dev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|mddev-&gt;devices
(braket
id|i
)braket
dot
id|size
op_eq
id|mddev-&gt;devices
(braket
id|j
)braket
dot
id|size
)paren
(brace
id|c
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
id|data-&gt;nr_strip_zones
op_increment
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
)brace
id|data-&gt;strip_zone
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|strip_zone
)paren
op_star
id|data-&gt;nr_strip_zones
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|data-&gt;smallest
op_assign
l_int|NULL
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
id|data-&gt;nr_strip_zones
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|dev_offset
op_assign
id|current_offset
suffix:semicolon
id|smallest_by_zone
op_assign
l_int|NULL
suffix:semicolon
id|c
op_assign
l_int|0
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
id|mddev-&gt;nb_dev
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|mddev-&gt;devices
(braket
id|j
)braket
dot
id|size
OG
id|current_offset
)paren
(brace
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|dev
(braket
id|c
op_increment
)braket
op_assign
id|mddev-&gt;devices
op_plus
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smallest_by_zone
op_logical_or
id|smallest_by_zone-&gt;size
OG
id|mddev-&gt;devices
(braket
id|j
)braket
dot
id|size
)paren
id|smallest_by_zone
op_assign
id|mddev-&gt;devices
op_plus
id|j
suffix:semicolon
)brace
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|nb_dev
op_assign
id|c
suffix:semicolon
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|size
op_assign
(paren
id|smallest_by_zone-&gt;size
op_minus
id|current_offset
)paren
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;smallest
op_logical_or
id|data-&gt;smallest-&gt;size
OG
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|size
)paren
id|data-&gt;smallest
op_assign
id|data-&gt;strip_zone
op_plus
id|i
suffix:semicolon
id|data-&gt;strip_zone
(braket
id|i
)braket
dot
id|zone_offset
op_assign
id|i
ques
c_cond
(paren
id|data-&gt;strip_zone
(braket
id|i
op_minus
l_int|1
)braket
dot
id|zone_offset
op_plus
id|data-&gt;strip_zone
(braket
id|i
op_minus
l_int|1
)braket
dot
id|size
)paren
suffix:colon
l_int|0
suffix:semicolon
id|current_offset
op_assign
id|smallest_by_zone-&gt;size
suffix:semicolon
)brace
)brace
DECL|function|raid0_run
r_static
r_int
id|raid0_run
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
(brace
r_int
id|cur
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
comma
id|size
comma
id|zone0_size
comma
id|nb_zone
suffix:semicolon
r_struct
id|raid0_data
op_star
id|data
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|mddev
op_member_access_from_pointer
r_private
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|raid0_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|data
op_assign
(paren
r_struct
id|raid0_data
op_star
)paren
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
id|create_strip_zones
(paren
id|minor
comma
id|mddev
)paren
suffix:semicolon
id|nb_zone
op_assign
id|data-&gt;nr_zones
op_assign
id|md_size
(braket
id|minor
)braket
op_div
id|data-&gt;smallest-&gt;size
op_plus
(paren
id|md_size
(braket
id|minor
)braket
op_mod
id|data-&gt;smallest-&gt;size
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|data-&gt;hash_table
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|raid0_hash
)paren
op_star
id|nb_zone
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|size
op_assign
id|data-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|cur
OL
id|data-&gt;nr_strip_zones
)paren
(brace
id|data-&gt;hash_table
(braket
id|i
)braket
dot
id|zone0
op_assign
id|data-&gt;strip_zone
op_plus
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
id|data-&gt;smallest-&gt;size
)paren
multiline_comment|/* If we completely fill the slot */
(brace
id|data-&gt;hash_table
(braket
id|i
op_increment
)braket
dot
id|zone1
op_assign
l_int|NULL
suffix:semicolon
id|size
op_sub_assign
id|data-&gt;smallest-&gt;size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
r_if
c_cond
(paren
op_increment
id|cur
op_eq
id|data-&gt;nr_strip_zones
)paren
r_continue
suffix:semicolon
id|size
op_assign
id|data-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|cur
op_eq
id|data-&gt;nr_strip_zones
)paren
multiline_comment|/* Last dev, set unit1 as NULL */
(brace
id|data-&gt;hash_table
(braket
id|i
)braket
dot
id|zone1
op_assign
l_int|NULL
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|zone0_size
op_assign
id|size
suffix:semicolon
multiline_comment|/* Here, we use a 2nd dev to fill the slot */
id|size
op_assign
id|data-&gt;strip_zone
(braket
id|cur
)braket
dot
id|size
suffix:semicolon
id|data-&gt;hash_table
(braket
id|i
op_increment
)braket
dot
id|zone1
op_assign
id|data-&gt;strip_zone
op_plus
id|cur
suffix:semicolon
id|size
op_sub_assign
(paren
id|data-&gt;smallest-&gt;size
op_minus
id|zone0_size
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|raid0_stop
r_static
r_int
id|raid0_stop
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
(brace
r_struct
id|raid0_data
op_star
id|data
op_assign
(paren
r_struct
id|raid0_data
op_star
)paren
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
id|kfree
(paren
id|data-&gt;hash_table
)paren
suffix:semicolon
id|kfree
(paren
id|data-&gt;strip_zone
)paren
suffix:semicolon
id|kfree
(paren
id|data
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME - We assume some things here :&n; * - requested buffers NEVER bigger than chunk size,&n; * - requested buffers NEVER cross stripes limits.&n; * Of course, those facts may not be valid anymore (and surely won&squot;t...)&n; * Hey guys, there&squot;s some work out there ;-)&n; */
DECL|function|raid0_map
r_static
r_int
id|raid0_map
(paren
r_struct
id|md_dev
op_star
id|mddev
comma
id|kdev_t
op_star
id|rdev
comma
r_int
r_int
op_star
id|rsector
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|raid0_data
op_star
id|data
op_assign
(paren
r_struct
id|raid0_data
op_star
)paren
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
r_static
r_struct
id|raid0_hash
op_star
id|hash
suffix:semicolon
r_struct
id|strip_zone
op_star
id|zone
suffix:semicolon
r_struct
id|real_dev
op_star
id|tmp_dev
suffix:semicolon
r_int
id|blk_in_chunk
comma
id|factor
comma
id|chunk
comma
id|chunk_size
suffix:semicolon
r_int
id|block
comma
id|rblock
suffix:semicolon
id|factor
op_assign
id|FACTOR
c_func
(paren
id|mddev
)paren
suffix:semicolon
id|chunk_size
op_assign
(paren
l_int|1UL
op_lshift
id|FACTOR_SHIFT
c_func
(paren
id|factor
)paren
)paren
suffix:semicolon
id|block
op_assign
op_star
id|rsector
op_rshift
l_int|1
suffix:semicolon
id|hash
op_assign
id|data-&gt;hash_table
op_plus
(paren
id|block
op_div
id|data-&gt;smallest-&gt;size
)paren
suffix:semicolon
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
(paren
id|chunk_size
op_star
l_int|2
)paren
OL
(paren
op_star
id|rsector
op_mod
(paren
id|chunk_size
op_star
l_int|2
)paren
)paren
op_plus
id|size
)paren
(brace
id|printk
(paren
l_string|&quot;raid0_convert : can&squot;t convert block across chunks or bigger than %dk %ld %ld&bslash;n&quot;
comma
id|chunk_size
comma
op_star
id|rsector
comma
id|size
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_ge
(paren
id|hash-&gt;zone0-&gt;size
op_plus
id|hash-&gt;zone0-&gt;zone_offset
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hash-&gt;zone1
)paren
(brace
id|printk
(paren
l_string|&quot;raid0_convert : hash-&gt;zone1==NULL for block %ld&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|zone
op_assign
id|hash-&gt;zone1
suffix:semicolon
)brace
r_else
id|zone
op_assign
id|hash-&gt;zone0
suffix:semicolon
id|blk_in_chunk
op_assign
id|block
op_amp
(paren
id|chunk_size
op_minus
l_int|1
)paren
suffix:semicolon
id|chunk
op_assign
(paren
id|block
op_minus
id|zone-&gt;zone_offset
)paren
op_div
(paren
id|zone-&gt;nb_dev
op_lshift
id|FACTOR_SHIFT
c_func
(paren
id|factor
)paren
)paren
suffix:semicolon
id|tmp_dev
op_assign
id|zone-&gt;dev
(braket
(paren
id|block
op_rshift
id|FACTOR_SHIFT
c_func
(paren
id|factor
)paren
)paren
op_mod
id|zone-&gt;nb_dev
)braket
suffix:semicolon
id|rblock
op_assign
(paren
id|chunk
op_lshift
id|FACTOR_SHIFT
c_func
(paren
id|factor
)paren
)paren
op_plus
id|blk_in_chunk
op_plus
id|zone-&gt;dev_offset
suffix:semicolon
op_star
id|rdev
op_assign
id|tmp_dev-&gt;dev
suffix:semicolon
op_star
id|rsector
op_assign
id|rblock
op_lshift
l_int|1
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|raid0_status
r_static
r_int
id|raid0_status
(paren
r_char
op_star
id|page
comma
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|mddev
)paren
(brace
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
DECL|macro|MD_DEBUG
macro_line|#undef MD_DEBUG
macro_line|#ifdef MD_DEBUG
r_int
id|j
comma
id|k
suffix:semicolon
r_struct
id|raid0_data
op_star
id|data
op_assign
(paren
r_struct
id|raid0_data
op_star
)paren
id|mddev
op_member_access_from_pointer
r_private
suffix:semicolon
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;      &quot;
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
id|data-&gt;nr_zones
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;[z%d&quot;
comma
id|data-&gt;hash_table
(braket
id|j
)braket
dot
id|zone0
op_minus
id|data-&gt;strip_zone
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;hash_table
(braket
id|j
)braket
dot
id|zone1
)paren
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;/z%d] &quot;
comma
id|data-&gt;hash_table
(braket
id|j
)braket
dot
id|zone1
op_minus
id|data-&gt;strip_zone
)paren
suffix:semicolon
r_else
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;] &quot;
)paren
suffix:semicolon
)brace
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;&bslash;n&quot;
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
id|data-&gt;nr_strip_zones
suffix:semicolon
id|j
op_increment
)paren
(brace
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;      z%d=[&quot;
comma
id|j
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|data-&gt;strip_zone
(braket
id|j
)braket
dot
id|nb_dev
suffix:semicolon
id|k
op_increment
)paren
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;%s/&quot;
comma
id|partition_name
c_func
(paren
id|data-&gt;strip_zone
(braket
id|j
)braket
dot
id|dev
(braket
id|k
)braket
op_member_access_from_pointer
id|dev
)paren
)paren
suffix:semicolon
id|sz
op_decrement
suffix:semicolon
id|sz
op_add_assign
id|sprintf
(paren
id|page
op_plus
id|sz
comma
l_string|&quot;] zo=%d do=%d s=%d&bslash;n&quot;
comma
id|data-&gt;strip_zone
(braket
id|j
)braket
dot
id|zone_offset
comma
id|data-&gt;strip_zone
(braket
id|j
)braket
dot
id|dev_offset
comma
id|data-&gt;strip_zone
(braket
id|j
)braket
dot
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|sz
suffix:semicolon
)brace
DECL|variable|raid0_personality
r_static
r_struct
id|md_personality
id|raid0_personality
op_assign
(brace
l_string|&quot;raid0&quot;
comma
id|raid0_map
comma
id|raid0_run
comma
id|raid0_stop
comma
id|raid0_status
comma
l_int|NULL
comma
multiline_comment|/* no ioctls */
l_int|0
)brace
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|raid0_init
r_void
id|raid0_init
(paren
r_void
)paren
(brace
id|register_md_personality
(paren
id|RAID0
comma
op_amp
id|raid0_personality
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|init_module
r_int
id|init_module
(paren
r_void
)paren
(brace
r_return
(paren
id|register_md_personality
(paren
id|RAID0
comma
op_amp
id|raid0_personality
)paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
id|unregister_md_personality
(paren
id|RAID0
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
