multiline_comment|/*&n;   md.h : Multiple Devices driver for Linux&n;          Copyright (C) 1994-96 Marc ZYNGIER&n;&t;  &lt;zyngier@ufr-info-p7.ibp.fr&gt; or&n;&t;  &lt;maz@gloups.fdn.fr&gt;&n;&t;  &n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2, or (at your option)&n;   any later version.&n;   &n;   You should have received a copy of the GNU General Public License&n;   (for example /usr/src/linux/COPYING); if not, write to the Free&n;   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  &n;*/
macro_line|#ifndef _MD_H
DECL|macro|_MD_H
mdefine_line|#define _MD_H
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|MD_VERSION
mdefine_line|#define MD_VERSION &quot;0.35&quot;
multiline_comment|/* ioctls */
DECL|macro|REGISTER_DEV
mdefine_line|#define REGISTER_DEV _IO (MD_MAJOR, 1)
DECL|macro|START_MD
mdefine_line|#define START_MD     _IO (MD_MAJOR, 2)
DECL|macro|STOP_MD
mdefine_line|#define STOP_MD      _IO (MD_MAJOR, 3)
DECL|macro|MD_INVALID
mdefine_line|#define MD_INVALID   _IO (MD_MAJOR, 4)
DECL|macro|MD_VALID
mdefine_line|#define MD_VALID     _IO (MD_MAJOR, 5)
multiline_comment|/*&n;   personalities :&n;   Byte 0 : Chunk size factor&n;   Byte 1 : Fault tolerance count for each physical device&n;            (   0 means no fault tolerance,&n;             0xFF means always tolerate faults)&n;   Byte 2 : Personality&n;   Byte 3 : Reserved.&n; */
DECL|macro|FAULT_SHIFT
mdefine_line|#define FAULT_SHIFT       8
DECL|macro|PERSONALITY_SHIFT
mdefine_line|#define PERSONALITY_SHIFT 16
DECL|macro|FACTOR_MASK
mdefine_line|#define FACTOR_MASK       0xFFUL
DECL|macro|FAULT_MASK
mdefine_line|#define FAULT_MASK        0xFF00UL
DECL|macro|PERSONALITY_MASK
mdefine_line|#define PERSONALITY_MASK  0xFF0000UL
DECL|macro|MD_RESERVED
mdefine_line|#define MD_RESERVED       0&t;/* Not used by now */
DECL|macro|LINEAR
mdefine_line|#define LINEAR            (1UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|STRIPED
mdefine_line|#define STRIPED           (2UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|STRIPPED
mdefine_line|#define STRIPPED          STRIPED /* Long lasting spelling mistake... */
DECL|macro|RAID0
mdefine_line|#define RAID0             STRIPED
DECL|macro|RAID1
mdefine_line|#define RAID1             (3UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|RAID5
mdefine_line|#define RAID5             (4UL &lt;&lt; PERSONALITY_SHIFT)
DECL|macro|MAX_PERSONALITY
mdefine_line|#define MAX_PERSONALITY   5
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
DECL|macro|MAX_REAL
mdefine_line|#define MAX_REAL     8&t;&t;/* Max number of physical dev per md dev */
DECL|macro|MAX_MD_DEV
mdefine_line|#define MAX_MD_DEV   4&t;&t;/* Max number of md dev */
DECL|macro|FACTOR
mdefine_line|#define FACTOR(a)         ((a)-&gt;repartition &amp; FACTOR_MASK)
DECL|macro|MAX_FAULT
mdefine_line|#define MAX_FAULT(a)      (((a)-&gt;repartition &amp; FAULT_MASK)&gt;&gt;8)
DECL|macro|PERSONALITY
mdefine_line|#define PERSONALITY(a)    ((a)-&gt;repartition &amp; PERSONALITY_MASK)
DECL|macro|FACTOR_SHIFT
mdefine_line|#define FACTOR_SHIFT(a) (PAGE_SHIFT + (a) - 10)
multiline_comment|/* Invalidation modes */
DECL|macro|VALID
mdefine_line|#define VALID          0
DECL|macro|INVALID_NEXT
mdefine_line|#define INVALID_NEXT   1
DECL|macro|INVALID_ALWAYS
mdefine_line|#define INVALID_ALWAYS 2
DECL|macro|INVALID
mdefine_line|#define INVALID        3&t;/* Only useful to md_valid_device */
multiline_comment|/* Return values from personalities to md driver */
DECL|macro|REDIRECTED_BHREQ
mdefine_line|#define REDIRECTED_BHREQ 0 /* Redirected individual buffers&n;&t;&t;&t;      (shouldn&squot;t be used anymore since 0.31) */
DECL|macro|REDIRECTED_REQ
mdefine_line|#define REDIRECTED_REQ   1 /* Redirected whole request */
DECL|macro|REDIRECT_FAILED
mdefine_line|#define REDIRECT_FAILED -1 /* For RAID-1 */
DECL|struct|real_dev
r_struct
id|real_dev
(brace
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
multiline_comment|/* Device number */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Device size (in blocks) */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* Real device offset (in blocks) in md dev&n;&t;&t;&t;&t;   (only used in linear mode) */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* Lock inode */
DECL|member|fault_count
r_int
id|fault_count
suffix:semicolon
multiline_comment|/* Fault counter for invalidation */
DECL|member|invalid
r_int
id|invalid
suffix:semicolon
multiline_comment|/* Indicate if the device is disabled :&n;&t;&t;&t;&t;   VALID          - valid&n;&t;&t;&t;&t;   INVALID_NEXT   - disabled for next access&n;&t;&t;&t;&t;   INVALID_ALWAYS - permanently disabled&n;&t;&t;&t;&t;   (for redundancy modes only) */
)brace
suffix:semicolon
r_struct
id|md_dev
suffix:semicolon
DECL|struct|md_personality
r_struct
id|md_personality
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|map
r_int
(paren
op_star
id|map
)paren
(paren
r_struct
id|md_dev
op_star
id|md_dev
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
suffix:semicolon
DECL|member|run
r_int
(paren
op_star
id|run
)paren
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|md_dev
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
r_int
id|minor
comma
r_struct
id|md_dev
op_star
id|md_dev
)paren
suffix:semicolon
DECL|member|status
r_int
(paren
op_star
id|status
)paren
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
id|md_dev
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|max_invalid_dev
r_int
id|max_invalid_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|md_dev
r_struct
id|md_dev
(brace
DECL|member|pers
r_struct
id|md_personality
op_star
id|pers
suffix:semicolon
DECL|member|repartition
r_int
id|repartition
suffix:semicolon
DECL|member|invalid_dev_count
r_int
id|invalid_dev_count
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|nb_dev
r_int
id|nb_dev
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|real_dev
id|devices
(braket
id|MAX_MD_DEV
)braket
(braket
id|MAX_REAL
)braket
suffix:semicolon
r_extern
r_struct
id|md_dev
id|md_dev
(braket
id|MAX_MD_DEV
)braket
suffix:semicolon
r_extern
r_int
id|md_size
(braket
id|MAX_MD_DEV
)braket
suffix:semicolon
r_extern
r_char
op_star
id|partition_name
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|register_md_personality
(paren
r_int
id|p_num
comma
r_struct
id|md_personality
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|unregister_md_personality
(paren
r_int
id|p_num
)paren
suffix:semicolon
macro_line|#endif __KERNEL__
macro_line|#endif _MD_H
eof
