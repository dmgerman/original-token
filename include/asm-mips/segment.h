multiline_comment|/*&n; * include/asm-mips/segment.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 by Ralf Baechle&n; *&n; */
macro_line|#ifndef __ASM_MIPS_SEGMENT_H
DECL|macro|__ASM_MIPS_SEGMENT_H
mdefine_line|#define __ASM_MIPS_SEGMENT_H
multiline_comment|/*&n; * Memory segments (32bit kernel mode addresses)&n; */
DECL|macro|KUSEG
mdefine_line|#define KUSEG                   0x00000000
DECL|macro|KSEG0
mdefine_line|#define KSEG0                   0x80000000
DECL|macro|KSEG1
mdefine_line|#define KSEG1                   0xa0000000
DECL|macro|KSEG2
mdefine_line|#define KSEG2                   0xc0000000
DECL|macro|KSEG3
mdefine_line|#define KSEG3                   0xe0000000
multiline_comment|/*&n; * returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                (a &amp; 0xe0000000)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Beware: the xxx_fs_word functions work on 16bit words!&n; */
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user_byte((char *)(addr))
DECL|function|get_user_byte
r_static
r_inline
r_int
r_char
id|get_user_byte
c_func
(paren
r_const
r_char
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user_word((short *)(addr))
DECL|function|get_user_word
r_static
r_inline
r_int
r_int
id|get_user_word
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user_long((int *)(addr))
DECL|function|get_user_long
r_static
r_inline
r_int
r_int
id|get_user_long
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_dlong
mdefine_line|#define get_fs_dlong(addr) get_user_dlong((long long *)(addr))
DECL|function|get_user_dlong
r_static
r_inline
r_int
r_int
id|get_user_dlong
c_func
(paren
r_const
r_int
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user_byte((x),(char *)(addr))
DECL|function|put_user_byte
r_static
r_inline
r_void
id|put_user_byte
c_func
(paren
r_char
id|val
comma
r_char
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user_word((x),(short *)(addr))
DECL|function|put_user_word
r_static
r_inline
r_void
id|put_user_word
c_func
(paren
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user_long((x),(int *)(addr))
DECL|function|put_user_long
r_static
r_inline
r_void
id|put_user_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_dlong
mdefine_line|#define put_fs_dlong(x,addr) put_user_dlong((x),(int *)(addr))
DECL|function|put_user_dlong
r_static
r_inline
r_void
id|put_user_dlong
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|memcpy_fromfs
mdefine_line|#define memcpy_fromfs(to, from, n) memcpy((to),(from),(n))
DECL|macro|memcpy_tofs
mdefine_line|#define memcpy_tofs(to, from, n) memcpy((to),(from),(n))
multiline_comment|/*&n; * For segmented architectures, these are used to specify which segment&n; * to use for the above functions.&n; *&n; * MIPS is not segmented, so these are just dummies.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS 0
DECL|macro|USER_DS
mdefine_line|#define USER_DS 1
DECL|function|get_fs
r_static
r_inline
r_int
r_int
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ds
r_static
r_inline
r_int
r_int
id|get_ds
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
r_int
r_int
id|val
)paren
(brace
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_MIPS_SEGMENT_H */
eof
