multiline_comment|/*&n; * include/asm-mips/segment.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 by Ralf Baechle&n; *&n; * Note that the quad functions are only being used for the 64 bit kernel and&n; * therefore it isn&squot;t really important that they will be miscompiled for&n; * 32-bit kernels.&n; */
macro_line|#ifndef __ASM_MIPS_SEGMENT_H
DECL|macro|__ASM_MIPS_SEGMENT_H
mdefine_line|#define __ASM_MIPS_SEGMENT_H
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
multiline_comment|/*&n; * For memcpy()&n; */
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * This is a gcc optimization barrier, which essentially&n; * inserts a sequence point in the gcc RTL tree that gcc&n; * can&squot;t move code around. This is needed when we enter&n; * or exit a critical region (in this case around user-level&n; * accesses that may sleep, and we can&squot;t let gcc optimize&n; * global state around them).&n; */
DECL|macro|__gcc_barrier
mdefine_line|#define __gcc_barrier() __asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) __put_user((unsigned long)(x),(ptr),sizeof(*(ptr)))
DECL|macro|get_user
mdefine_line|#define get_user(ptr) ((__typeof__(*(ptr)))__get_user((ptr),sizeof(*(ptr))))
multiline_comment|/*&n; * This is a silly but good way to make sure that&n; * the __put_user function is indeed always optimized,&n; * and that we use the correct sizes..&n; */
r_extern
r_int
id|bad_user_access_length
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* I should make this use unaligned transfers etc.. */
DECL|function|__put_user
r_static
r_inline
r_void
id|__put_user
c_func
(paren
r_int
r_int
id|x
comma
r_void
op_star
id|y
comma
r_int
id|size
)paren
(brace
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
(paren
r_char
op_star
)paren
id|y
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|y
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|y
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
op_star
(paren
r_int
op_star
)paren
id|y
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_user_access_length
c_func
(paren
)paren
suffix:semicolon
)brace
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* I should make this use unaligned transfers etc.. */
DECL|function|__get_user
r_static
r_inline
r_int
r_int
id|__get_user
c_func
(paren
r_const
r_void
op_star
id|y
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|result
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|y
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|result
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|y
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|result
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|y
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|result
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|y
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|result
op_assign
id|bad_user_access_length
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user((unsigned char *)(addr))
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user((unsigned short *)(addr))
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user((unsigned int *)(addr))
DECL|macro|get_fs_quad
mdefine_line|#define get_fs_quad(addr) get_user((unsigned long *)(addr))
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user((x),(char *)(addr))
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user((x),(short *)(addr))
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user((x),(int *)(addr))
DECL|macro|put_fs_quad
mdefine_line|#define put_fs_quad(x,addr) put_user((x),(long *)(addr))
DECL|function|memcpy_fromfs
r_static
r_inline
r_void
id|memcpy_fromfs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|memcpy_tofs
r_static
r_inline
r_void
id|memcpy_tofs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
id|__gcc_barrier
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|USER_DS
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
id|KERNEL_DS
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
macro_line|#endif /* !__LANGUAGE_ASSEMBLY__ */
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
multiline_comment|/*&n; * Returns the kernel segment base of a given address&n; */
DECL|macro|KSEGX
mdefine_line|#define KSEGX(a)                (((unsigned long)(a)) &amp; 0xe0000000)
multiline_comment|/*&n; * Returns the physical address of a KSEG0/KSEG1 address&n; */
DECL|macro|PHYSADDR
mdefine_line|#define PHYSADDR(a)&t;&t;(((unsigned long)(a)) &amp; 0x1fffffff)
multiline_comment|/*&n; * Map an address to a certain kernel segment&n; */
DECL|macro|KSEG0ADDR
mdefine_line|#define KSEG0ADDR(a)&t;&t;((((unsigned long)(a)) &amp; 0x1fffffff) | KSEG0)
DECL|macro|KSEG1ADDR
mdefine_line|#define KSEG1ADDR(a)&t;&t;((((unsigned long)(a)) &amp; 0x1fffffff) | KSEG1)
DECL|macro|KSEG2ADDR
mdefine_line|#define KSEG2ADDR(a)&t;&t;((((unsigned long)(a)) &amp; 0x1fffffff) | KSEG2)
DECL|macro|KSEG3ADDR
mdefine_line|#define KSEG3ADDR(a)&t;&t;((((unsigned long)(a)) &amp; 0x1fffffff) | KSEG3)
multiline_comment|/*&n; * Memory segments (64bit kernel mode addresses)&n; */
DECL|macro|XKUSEG
mdefine_line|#define XKUSEG                  0x0000 0000 0000 0000
DECL|macro|XKSSEG
mdefine_line|#define XKSSEG                  0x4000 0000 0000 0000
DECL|macro|XKPHYS
mdefine_line|#define XKPHYS                  0x8000 0000 0000 0000
DECL|macro|XKSEG
mdefine_line|#define XKSEG                   0xc000 0000 0000 0000
DECL|macro|CKSEG0
mdefine_line|#define CKSEG0                  0xffff ffff 8000 0000
DECL|macro|CKSEG1
mdefine_line|#define CKSEG1                  0xffff ffff a000 0000
DECL|macro|CKSSEG
mdefine_line|#define CKSSEG                  0xffff ffff c000 0000
DECL|macro|CKSEG3
mdefine_line|#define CKSEG3                  0xffff ffff e000 0000
macro_line|#endif /* __ASM_MIPS_SEGMENT_H */
eof
