multiline_comment|/*&n; * include/asm/setup.h&n; *&n; * Structure passed to kernel to tell it about the hardware it&squot;s running on&n; *&n; * Copyright (C) 1997,1998 Russell King&n; */
macro_line|#ifndef __ASMARM_SETUP_H
DECL|macro|__ASMARM_SETUP_H
mdefine_line|#define __ASMARM_SETUP_H
DECL|struct|param_struct
r_struct
id|param_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|page_size
r_int
r_int
id|page_size
suffix:semicolon
multiline_comment|/*  0 */
DECL|member|nr_pages
r_int
r_int
id|nr_pages
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|ramdisk_size
r_int
r_int
id|ramdisk_size
suffix:semicolon
multiline_comment|/*  8 */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* 12 */
DECL|macro|FLAG_READONLY
mdefine_line|#define FLAG_READONLY&t;1
DECL|macro|FLAG_RDLOAD
mdefine_line|#define FLAG_RDLOAD&t;4
DECL|macro|FLAG_RDPROMPT
mdefine_line|#define FLAG_RDPROMPT&t;8
DECL|member|rootdev
r_int
r_int
id|rootdev
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|video_num_cols
r_int
r_int
id|video_num_cols
suffix:semicolon
multiline_comment|/* 20 */
DECL|member|video_num_rows
r_int
r_int
id|video_num_rows
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|video_x
r_int
r_int
id|video_x
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|video_y
r_int
r_int
id|video_y
suffix:semicolon
multiline_comment|/* 32 */
DECL|member|memc_control_reg
r_int
r_int
id|memc_control_reg
suffix:semicolon
multiline_comment|/* 36 */
DECL|member|sounddefault
r_int
r_char
id|sounddefault
suffix:semicolon
multiline_comment|/* 40 */
DECL|member|adfsdrives
r_int
r_char
id|adfsdrives
suffix:semicolon
multiline_comment|/* 41 */
DECL|member|bytes_per_char_h
r_int
r_char
id|bytes_per_char_h
suffix:semicolon
multiline_comment|/* 42 */
DECL|member|bytes_per_char_v
r_int
r_char
id|bytes_per_char_v
suffix:semicolon
multiline_comment|/* 43 */
DECL|member|pages_in_bank
r_int
r_int
id|pages_in_bank
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 44 */
DECL|member|pages_in_vram
r_int
r_int
id|pages_in_vram
suffix:semicolon
multiline_comment|/* 60 */
DECL|member|initrd_start
r_int
r_int
id|initrd_start
suffix:semicolon
multiline_comment|/* 64 */
DECL|member|initrd_size
r_int
r_int
id|initrd_size
suffix:semicolon
multiline_comment|/* 68 */
DECL|member|rd_start
r_int
r_int
id|rd_start
suffix:semicolon
multiline_comment|/* 72 */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|unused
r_char
id|unused
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|u1
)brace
id|u1
suffix:semicolon
r_union
(brace
DECL|member|paths
r_char
id|paths
(braket
l_int|8
)braket
(braket
l_int|128
)braket
suffix:semicolon
r_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|n
r_char
id|n
(braket
l_int|1024
op_minus
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|u2
)brace
id|u2
suffix:semicolon
DECL|member|commandline
r_char
id|commandline
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
