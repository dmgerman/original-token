macro_line|#ifndef _S390_BITOPS_H
DECL|macro|_S390_BITOPS_H
mdefine_line|#define _S390_BITOPS_H
multiline_comment|/*&n; *  include/asm-s390/bitops.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/bitops.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * bit 0 is the LSB of *addr; bit 31 is the MSB of *addr;&n; * bit 32 is the LSB of *(addr+4). That combined with the&n; * big endian byte order on S390 give the following bit&n; * order in memory:&n; *    1f 1e 1d 1c 1b 1a 19 18 17 16 15 14 13 12 11 10 &bslash;&n; *    0f 0e 0d 0c 0b 0a 09 08 07 06 05 04 03 02 01 00&n; * after that follows the next long with bit numbers&n; *    3f 3e 3d 3c 3b 3a 39 38 37 36 35 34 33 32 31 30&n; *    2f 2e 2d 2c 2b 2a 29 28 27 26 25 24 23 22 21 20&n; * The reason for this bit ordering is the fact that&n; * in the architecture independent code bits operations&n; * of the form &quot;flags |= (1 &lt;&lt; bitnr)&quot; are used INTERMIXED&n; * with operation of the form &quot;set_bit(bitnr, flags)&quot;.&n; */
multiline_comment|/* set ALIGN_CS to 1 if the SMP safe bit operations should&n; * align the address to 4 byte boundary. It seems to work&n; * without the alignment. &n; */
DECL|macro|ALIGN_CS
mdefine_line|#define ALIGN_CS 0
multiline_comment|/* bitmap tables from arch/S390/kernel/bitmap.S */
r_extern
r_const
r_char
id|_oi_bitmap
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|_ni_bitmap
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|_zb_findmap
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Function prototypes to keep gcc -Wall happy&n; */
r_extern
r_void
id|__set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__constant_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|__test_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|__constant_test_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__constant_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__constant_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_set_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_clear_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|test_and_change_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|find_first_zero_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|find_next_zero_bit
(paren
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ffz
c_func
(paren
r_int
r_int
id|word
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * SMP save set_bit routine based on compare and swap (CS)&n; */
DECL|function|set_bit_cs
r_extern
id|__inline__
r_void
id|set_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
multiline_comment|/* make OR mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   or    1,2&bslash;n&quot;
multiline_comment|/* set bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP save clear_bit routine based on compare and swap (CS)&n; */
DECL|function|clear_bit_cs
r_extern
id|__inline__
r_void
id|clear_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
op_minus
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
l_string|&quot;   x     2,%2&bslash;n&quot;
multiline_comment|/* make AND mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   nr    1,2&bslash;n&quot;
multiline_comment|/* clear bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP save change_bit routine based on compare and swap (CS)&n; */
DECL|function|change_bit_cs
r_extern
id|__inline__
r_void
id|change_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
multiline_comment|/* make XR mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   xr    1,2&bslash;n&quot;
multiline_comment|/* change bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP save test_and_set_bit routine based on compare and swap (CS)&n; */
DECL|function|test_and_set_bit_cs
r_extern
id|__inline__
r_int
id|test_and_set_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
multiline_comment|/* make OR mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   or    1,2&bslash;n&quot;
multiline_comment|/* set bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&bslash;n&quot;
l_string|&quot;   nr    %0,2&bslash;n&quot;
multiline_comment|/* isolate old bit */
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP save test_and_clear_bit routine based on compare and swap (CS)&n; */
DECL|function|test_and_clear_bit_cs
r_extern
id|__inline__
r_int
id|test_and_clear_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
op_minus
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
l_string|&quot;   x     2,%2&bslash;n&quot;
multiline_comment|/* make AND mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   nr    1,2&bslash;n&quot;
multiline_comment|/* clear bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&bslash;n&quot;
l_string|&quot;   x     2,%2&bslash;n&quot;
l_string|&quot;   nr    %0,2&bslash;n&quot;
multiline_comment|/* isolate old bit */
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP save test_and_change_bit routine based on compare and swap (CS) &n; */
DECL|function|test_and_change_bit_cs
r_extern
id|__inline__
r_int
id|test_and_change_bit_cs
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
macro_line|#if ALIGN_CS == 1
l_string|&quot;   lhi   1,3&bslash;n&quot;
multiline_comment|/* CS must be aligned on 4 byte b. */
l_string|&quot;   nr    1,%1&bslash;n&quot;
multiline_comment|/* isolate last 2 bits of address */
l_string|&quot;   xr    %1,1&bslash;n&quot;
multiline_comment|/* make addr % 4 == 0 */
l_string|&quot;   sll   1,3&bslash;n&quot;
l_string|&quot;   ar    %0,1&bslash;n&quot;
multiline_comment|/* add alignement to bitnr */
macro_line|#endif
l_string|&quot;   lhi   1,31&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* make shift value */
l_string|&quot;   xr    %0,1&bslash;n&quot;
l_string|&quot;   srl   %0,3&bslash;n&quot;
l_string|&quot;   la    %1,0(%0,%1)&bslash;n&quot;
multiline_comment|/* calc. address for CS */
l_string|&quot;   lhi   2,1&bslash;n&quot;
l_string|&quot;   sll   2,0(1)&bslash;n&quot;
multiline_comment|/* make OR mask */
l_string|&quot;   l     %0,0(%1)&bslash;n&quot;
l_string|&quot;0: lr    1,%0&bslash;n&quot;
multiline_comment|/* CS loop starts here */
l_string|&quot;   xr    1,2&bslash;n&quot;
multiline_comment|/* change bit */
l_string|&quot;   cs    %0,1,0(%1)&bslash;n&quot;
l_string|&quot;   jl    0b&bslash;n&quot;
l_string|&quot;   nr    %0,2&bslash;n&quot;
multiline_comment|/* isolate old bit */
suffix:colon
l_string|&quot;+a&quot;
(paren
id|nr
)paren
comma
l_string|&quot;+a&quot;
(paren
id|addr
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * fast, non-SMP set_bit routine&n; */
DECL|function|__set_bit
r_extern
id|__inline__
r_void
id|__set_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   2,24&bslash;n&quot;
l_string|&quot;   lhi   1,7&bslash;n&quot;
l_string|&quot;   xr    2,%0&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
l_string|&quot;   srl   2,3&bslash;n&quot;
l_string|&quot;   la    2,0(2,%1)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   oc    0(1,2),0(1)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_oi_bitmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|__constant_set_bit
id|__constant_set_bit
c_func
(paren
r_const
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x01&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x02&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x04&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x08&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x10&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x20&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x40&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;oi 0(1),0x80&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|set_bit_simple
mdefine_line|#define set_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_set_bit((nr),(addr)) : &bslash;&n; __set_bit((nr),(addr)) )
multiline_comment|/*&n; * fast, non-SMP clear_bit routine&n; */
r_extern
id|__inline__
r_void
DECL|function|__clear_bit
id|__clear_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   2,24&bslash;n&quot;
l_string|&quot;   lhi   1,7&bslash;n&quot;
l_string|&quot;   xr    2,%0&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
l_string|&quot;   srl   2,3&bslash;n&quot;
l_string|&quot;   la    2,0(2,%1)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   nc    0(1,2),0(1)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_ni_bitmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|__constant_clear_bit
id|__constant_clear_bit
c_func
(paren
r_const
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xFE&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xFD&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xFB&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xF7&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xEF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xDF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0xBF&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;ni 0(1),0x7F&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|clear_bit_simple
mdefine_line|#define clear_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_clear_bit((nr),(addr)) : &bslash;&n; __clear_bit((nr),(addr)) )
multiline_comment|/* &n; * fast, non-SMP change_bit routine &n; */
DECL|function|__change_bit
r_extern
id|__inline__
r_void
id|__change_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   2,24&bslash;n&quot;
l_string|&quot;   lhi   1,7&bslash;n&quot;
l_string|&quot;   xr    2,%0&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
l_string|&quot;   srl   2,3&bslash;n&quot;
l_string|&quot;   la    2,0(2,%1)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   xc    0(1,2),0(1)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_oi_bitmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|__constant_change_bit
id|__constant_change_bit
c_func
(paren
r_const
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_switch
c_cond
(paren
id|nr
op_amp
l_int|7
)paren
(brace
r_case
l_int|0
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x01&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x02&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x04&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x08&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x10&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x20&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x40&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;la 1,%0&bslash;n&bslash;t&quot;
l_string|&quot;xi 0(1),0x80&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
op_plus
(paren
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)paren
)paren
)paren
suffix:colon
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|change_bit_simple
mdefine_line|#define change_bit_simple(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_change_bit((nr),(addr)) : &bslash;&n; __change_bit((nr),(addr)) )
multiline_comment|/*&n; * fast, non-SMP test_and_set_bit routine&n; */
DECL|function|test_and_set_bit_simple
r_extern
id|__inline__
r_int
id|test_and_set_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|1
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   1,24&bslash;n&quot;
l_string|&quot;   lhi   2,7&bslash;n&quot;
l_string|&quot;   xr    1,%1&bslash;n&quot;
l_string|&quot;   nr    2,1&bslash;n&quot;
l_string|&quot;   srl   1,3(0)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   ic    %0,0(0,1)&bslash;n&quot;
l_string|&quot;   srl   %0,0(2)&bslash;n&quot;
l_string|&quot;   n     %0,%4&bslash;n&quot;
l_string|&quot;   la    2,0(2,%3)&bslash;n&quot;
l_string|&quot;   oc    0(1,1),0(2)&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_oi_bitmap
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/*&n; * fast, non-SMP test_and_clear_bit routine&n; */
DECL|function|test_and_clear_bit_simple
r_extern
id|__inline__
r_int
id|test_and_clear_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|1
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   1,24&bslash;n&quot;
l_string|&quot;   lhi   2,7&bslash;n&quot;
l_string|&quot;   xr    1,%1&bslash;n&quot;
l_string|&quot;   nr    2,1&bslash;n&quot;
l_string|&quot;   srl   1,3(0)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   ic    %0,0(0,1)&bslash;n&quot;
l_string|&quot;   srl   %0,0(2)&bslash;n&quot;
l_string|&quot;   n     %0,%4&bslash;n&quot;
l_string|&quot;   la    2,0(2,%3)&bslash;n&quot;
l_string|&quot;   nc    0(1,1),0(2)&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_ni_bitmap
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
multiline_comment|/*&n; * fast, non-SMP test_and_change_bit routine&n; */
DECL|function|test_and_change_bit_simple
r_extern
id|__inline__
r_int
id|test_and_change_bit_simple
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|1
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   1,24&bslash;n&quot;
l_string|&quot;   lhi   2,7&bslash;n&quot;
l_string|&quot;   xr    1,%1&bslash;n&quot;
l_string|&quot;   nr    2,1&bslash;n&quot;
l_string|&quot;   srl   1,3(0)&bslash;n&quot;
l_string|&quot;   la    1,0(1,%2)&bslash;n&quot;
l_string|&quot;   ic    %0,0(0,1)&bslash;n&quot;
l_string|&quot;   srl   %0,0(2)&bslash;n&quot;
l_string|&quot;   n     %0,%4&bslash;n&quot;
l_string|&quot;   la    2,0(2,%3)&bslash;n&quot;
l_string|&quot;   xc    0(1,1),0(2)&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_oi_bitmap
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|set_bit
mdefine_line|#define set_bit             set_bit_cs
DECL|macro|clear_bit
mdefine_line|#define clear_bit           clear_bit_cs
DECL|macro|change_bit
mdefine_line|#define change_bit          change_bit_cs
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit    test_and_set_bit_cs
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit  test_and_clear_bit_cs
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit test_and_change_bit_cs
macro_line|#else
DECL|macro|set_bit
mdefine_line|#define set_bit             set_bit_simple
DECL|macro|clear_bit
mdefine_line|#define clear_bit           clear_bit_simple
DECL|macro|change_bit
mdefine_line|#define change_bit          change_bit_simple
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit    test_and_set_bit_simple
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit  test_and_clear_bit_simple
DECL|macro|test_and_change_bit
mdefine_line|#define test_and_change_bit test_and_change_bit_simple
macro_line|#endif
multiline_comment|/*&n; * This routine doesn&squot;t need to be atomic.&n; */
DECL|function|__test_bit
r_extern
id|__inline__
r_int
id|__test_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|1
suffix:semicolon
r_int
id|oldbit
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   lhi   2,24&bslash;n&quot;
l_string|&quot;   lhi   1,7&bslash;n&quot;
l_string|&quot;   xr    2,%1&bslash;n&quot;
l_string|&quot;   nr    1,%1&bslash;n&quot;
l_string|&quot;   srl   2,3&bslash;n&quot;
l_string|&quot;   ic    %0,0(2,%2)&bslash;n&quot;
l_string|&quot;   srl   %0,0(1)&bslash;n&quot;
l_string|&quot;   n     %0,%3&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|oldbit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
id|oldbit
suffix:semicolon
)brace
DECL|function|__constant_test_bit
r_extern
id|__inline__
r_int
id|__constant_test_bit
c_func
(paren
r_int
id|nr
comma
r_volatile
r_void
op_star
id|addr
)paren
(brace
r_return
(paren
(paren
(paren
r_volatile
r_char
op_star
)paren
id|addr
)paren
(braket
(paren
id|nr
op_rshift
l_int|3
)paren
op_xor
l_int|3
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|7
)paren
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|macro|test_bit
mdefine_line|#define test_bit(nr,addr) &bslash;&n;(__builtin_constant_p((nr)) ? &bslash;&n; __constant_test_bit((nr),(addr)) : &bslash;&n; __test_bit((nr),(addr)) )
multiline_comment|/*&n; * Find-bit routines..&n; */
DECL|function|find_first_zero_bit
r_extern
id|__inline__
r_int
id|find_first_zero_bit
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|0xffL
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lhi  0,-1&bslash;n&quot;
l_string|&quot;   lr   1,%1&bslash;n&quot;
l_string|&quot;   ahi  1,31&bslash;n&quot;
l_string|&quot;   srl  1,5&bslash;n&quot;
l_string|&quot;   sr   2,2&bslash;n&quot;
l_string|&quot;0: c    0,0(2,%2)&bslash;n&quot;
l_string|&quot;   jne  1f&bslash;n&quot;
l_string|&quot;   ahi  2,4&bslash;n&quot;
l_string|&quot;   brct 1,0b&bslash;n&quot;
l_string|&quot;   lr   2,%1&bslash;n&quot;
l_string|&quot;   j    4f&bslash;n&quot;
l_string|&quot;1: l    1,0(2,%2)&bslash;n&quot;
l_string|&quot;   sll  2,3(0)&bslash;n&quot;
l_string|&quot;   tml  1,0xFFFF&bslash;n&quot;
l_string|&quot;   jno  2f&bslash;n&quot;
l_string|&quot;   ahi  2,16&bslash;n&quot;
l_string|&quot;   srl  1,16&bslash;n&quot;
l_string|&quot;2: tml  1,0x00FF&bslash;n&quot;
l_string|&quot;   jno  3f&bslash;n&quot;
l_string|&quot;   ahi  2,8&bslash;n&quot;
l_string|&quot;   srl  1,8&bslash;n&quot;
l_string|&quot;3: n    1,%3&bslash;n&quot;
l_string|&quot;   ic   1,0(1,%4)&bslash;n&quot;
l_string|&quot;   n    1,%3&bslash;n&quot;
l_string|&quot;   ar   2,1&bslash;n&quot;
l_string|&quot;4: lr   %0,2&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
DECL|function|find_next_zero_bit
r_extern
id|__inline__
r_int
id|find_next_zero_bit
(paren
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|0xffL
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|bitvec
suffix:semicolon
r_int
id|set
comma
id|bit
op_assign
id|offset
op_amp
l_int|31
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
multiline_comment|/*&n;                 * Look for zero in first word&n;                 */
id|bitvec
op_assign
(paren
op_star
id|p
)paren
op_rshift
id|bit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lr   1,%1&bslash;n&quot;
l_string|&quot;   sr   %0,%0&bslash;n&quot;
l_string|&quot;   tml  1,0xFFFF&bslash;n&quot;
l_string|&quot;   jno  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  1,16&bslash;n&quot;
l_string|&quot;0: tml  1,0x00FF&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  1,8&bslash;n&quot;
l_string|&quot;1: n    1,%2&bslash;n&quot;
l_string|&quot;   ic   1,0(1,%3)&bslash;n&quot;
l_string|&quot;   n    1,%2&bslash;n&quot;
l_string|&quot;   ar   %0,1&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|set
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|bitvec
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
OL
(paren
l_int|32
op_minus
id|bit
)paren
)paren
r_return
id|set
op_plus
id|offset
suffix:semicolon
id|offset
op_add_assign
l_int|32
op_minus
id|bit
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;         * No zero yet, search remaining full words for a zero&n;         */
id|res
op_assign
id|find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|offset
op_plus
id|res
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffz = Find First Zero in word. Undefined if no zero exists,&n; * so code should check against ~0UL first..&n; */
DECL|function|ffz
r_extern
id|__inline__
r_int
r_int
id|ffz
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|0xffL
suffix:semicolon
r_int
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lr   1,%1&bslash;n&quot;
l_string|&quot;   sr   %0,%0&bslash;n&quot;
l_string|&quot;   tml  1,0xFFFF&bslash;n&quot;
l_string|&quot;   jno  0f&bslash;n&quot;
l_string|&quot;   ahi  %0,16&bslash;n&quot;
l_string|&quot;   srl  1,16&bslash;n&quot;
l_string|&quot;0: tml  1,0x00FF&bslash;n&quot;
l_string|&quot;   jno  1f&bslash;n&quot;
l_string|&quot;   ahi  %0,8&bslash;n&quot;
l_string|&quot;   srl  1,8&bslash;n&quot;
l_string|&quot;1: n    1,%2&bslash;n&quot;
l_string|&quot;   ic   1,0(1,%3)&bslash;n&quot;
l_string|&quot;   n    1,%2&bslash;n&quot;
l_string|&quot;   ar   %0,1&quot;
suffix:colon
l_string|&quot;=d&amp;&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|word
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|ffs
r_extern
r_int
id|__inline__
id|ffs
(paren
r_int
id|x
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;    lr   %%r1,%1&bslash;n&quot;
l_string|&quot;    sr   %0,%0&bslash;n&quot;
l_string|&quot;    tmh  %%r1,0xFFFF&bslash;n&quot;
l_string|&quot;    jz   0f&bslash;n&quot;
l_string|&quot;    ahi  %0,16&bslash;n&quot;
l_string|&quot;    srl  %%r1,16&bslash;n&quot;
l_string|&quot;0:  tml  %%r1,0xFF00&bslash;n&quot;
l_string|&quot;    jz   1f&bslash;n&quot;
l_string|&quot;    ahi  %0,8&bslash;n&quot;
l_string|&quot;    srl  %%r1,8&bslash;n&quot;
l_string|&quot;1:  tml  %%r1,0x00F0&bslash;n&quot;
l_string|&quot;    jz   2f&bslash;n&quot;
l_string|&quot;    ahi  %0,4&bslash;n&quot;
l_string|&quot;    srl  %%r1,4&bslash;n&quot;
l_string|&quot;2:  tml  %%r1,0x000C&bslash;n&quot;
l_string|&quot;    jz   3f&bslash;n&quot;
l_string|&quot;    ahi  %0,2&bslash;n&quot;
l_string|&quot;    srl  %%r1,2&bslash;n&quot;
l_string|&quot;3:  tml  %%r1,0x0002&bslash;n&quot;
l_string|&quot;    jz   4f&bslash;n&quot;
l_string|&quot;    ahi  %0,1&bslash;n&quot;
l_string|&quot;4:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|r
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * hweightN: returns the hamming weight (i.e. the number&n; * of bits set) of a N-bit word&n; */
DECL|macro|hweight32
mdefine_line|#define hweight32(x) generic_hweight32(x)
DECL|macro|hweight16
mdefine_line|#define hweight16(x) generic_hweight16(x)
DECL|macro|hweight8
mdefine_line|#define hweight8(x) generic_hweight8(x)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * ATTENTION: intel byte ordering convention for ext2 and minix !!&n; * bit 0 is the LSB of addr; bit 31 is the MSB of addr;&n; * bit 32 is the LSB of (addr+4).&n; * That combined with the little endian byte order of Intel gives the&n; * following bit order in memory:&n; *    07 06 05 04 03 02 01 00 15 14 13 12 11 10 09 08 &bslash;&n; *    23 22 21 20 19 18 17 16 31 30 29 28 27 26 25 24&n; */
DECL|macro|ext2_set_bit
mdefine_line|#define ext2_set_bit(nr, addr)       test_and_set_bit((nr)^24, addr)
DECL|macro|ext2_clear_bit
mdefine_line|#define ext2_clear_bit(nr, addr)     test_and_clear_bit((nr)^24, addr)
DECL|macro|ext2_test_bit
mdefine_line|#define ext2_test_bit(nr, addr)      test_bit((nr)^24, addr)
DECL|function|ext2_find_first_zero_bit
r_extern
id|__inline__
r_int
id|ext2_find_first_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|0xffL
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;   lhi  0,-1&bslash;n&quot;
l_string|&quot;   lr   1,%1&bslash;n&quot;
l_string|&quot;   ahi  1,31&bslash;n&quot;
l_string|&quot;   srl  1,5&bslash;n&quot;
l_string|&quot;   sr   2,2&bslash;n&quot;
l_string|&quot;0: c    0,0(2,%2)&bslash;n&quot;
l_string|&quot;   jne  1f&bslash;n&quot;
l_string|&quot;   ahi  2,4&bslash;n&quot;
l_string|&quot;   brct 1,0b&bslash;n&quot;
l_string|&quot;   lr   2,%1&bslash;n&quot;
l_string|&quot;   j    4f&bslash;n&quot;
l_string|&quot;1: l    1,0(2,%2)&bslash;n&quot;
l_string|&quot;   sll  2,3(0)&bslash;n&quot;
l_string|&quot;   ahi  2,24&bslash;n&quot;
l_string|&quot;   tmh  1,0xFFFF&bslash;n&quot;
l_string|&quot;   jo   2f&bslash;n&quot;
l_string|&quot;   ahi  2,-16&bslash;n&quot;
l_string|&quot;   srl  1,16&bslash;n&quot;
l_string|&quot;2: tml  1,0xFF00&bslash;n&quot;
l_string|&quot;   jo   3f&bslash;n&quot;
l_string|&quot;   ahi  2,-8&bslash;n&quot;
l_string|&quot;   srl  1,8&bslash;n&quot;
l_string|&quot;3: n    1,%3&bslash;n&quot;
l_string|&quot;   ic   1,0(1,%4)&bslash;n&quot;
l_string|&quot;   n    1,%3&bslash;n&quot;
l_string|&quot;   ar   2,1&bslash;n&quot;
l_string|&quot;4: lr   %0,2&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|size
)paren
comma
l_string|&quot;a&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;m&quot;
(paren
id|mask
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_return
(paren
id|res
OL
id|size
)paren
ques
c_cond
id|res
suffix:colon
id|size
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
DECL|function|ext2_find_next_zero_bit
id|ext2_find_next_zero_bit
c_func
(paren
r_void
op_star
id|vaddr
comma
r_int
id|size
comma
r_int
id|offset
)paren
(brace
r_static
r_const
r_int
id|mask
op_assign
l_int|0xffL
suffix:semicolon
r_static
r_int
r_int
id|orword
(braket
l_int|32
)braket
op_assign
(brace
l_int|0x00000000
comma
l_int|0x01000000
comma
l_int|0x03000000
comma
l_int|0x07000000
comma
l_int|0x0f000000
comma
l_int|0x1f000000
comma
l_int|0x3f000000
comma
l_int|0x7f000000
comma
l_int|0xff000000
comma
l_int|0xff010000
comma
l_int|0xff030000
comma
l_int|0xff070000
comma
l_int|0xff0f0000
comma
l_int|0xff1f0000
comma
l_int|0xff3f0000
comma
l_int|0xff7f0000
comma
l_int|0xffff0000
comma
l_int|0xffff0100
comma
l_int|0xffff0300
comma
l_int|0xffff0700
comma
l_int|0xffff0f00
comma
l_int|0xffff1f00
comma
l_int|0xffff3f00
comma
l_int|0xffff7f00
comma
l_int|0xffffff00
comma
l_int|0xffffff01
comma
l_int|0xffffff03
comma
l_int|0xffffff07
comma
l_int|0xffffff0f
comma
l_int|0xffffff1f
comma
l_int|0xffffff3f
comma
l_int|0xffffff7f
)brace
suffix:semicolon
r_int
r_int
op_star
id|addr
op_assign
id|vaddr
suffix:semicolon
r_int
r_int
op_star
id|p
op_assign
id|addr
op_plus
(paren
id|offset
op_rshift
l_int|5
)paren
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
r_int
id|bit
op_assign
id|offset
op_amp
l_int|31UL
comma
id|res
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|size
)paren
r_return
id|size
suffix:semicolon
r_if
c_cond
(paren
id|bit
)paren
(brace
id|word
op_assign
op_star
id|p
op_or
id|orword
(braket
id|bit
)braket
suffix:semicolon
multiline_comment|/* Look for zero in first longword */
id|__asm__
c_func
(paren
l_string|&quot;   lhi  %0,24&bslash;n&quot;
l_string|&quot;   tmh  %1,0xFFFF&bslash;n&quot;
l_string|&quot;   jo   0f&bslash;n&quot;
l_string|&quot;   ahi  %0,-16&bslash;n&quot;
l_string|&quot;   srl  %1,16&bslash;n&quot;
l_string|&quot;0: tml  %1,0xFF00&bslash;n&quot;
l_string|&quot;   jo   1f&bslash;n&quot;
l_string|&quot;   ahi  %0,-8&bslash;n&quot;
l_string|&quot;   srl  %1,8&bslash;n&quot;
l_string|&quot;1: n    %1,%2&bslash;n&quot;
l_string|&quot;   ic   %1,0(%1,%3)&bslash;n&quot;
l_string|&quot;   alr  %0,%1&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|res
)paren
comma
l_string|&quot;+&amp;d&quot;
(paren
id|word
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|mask
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|_zb_findmap
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|32
)paren
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
multiline_comment|/* No zero yet, search remaining full bytes for a zero */
id|res
op_assign
id|ext2_find_first_zero_bit
(paren
id|p
comma
id|size
op_minus
l_int|32
op_star
(paren
id|p
op_minus
id|addr
)paren
)paren
suffix:semicolon
r_return
(paren
id|p
op_minus
id|addr
)paren
op_star
l_int|32
op_plus
id|res
suffix:semicolon
)brace
multiline_comment|/* Bitmap functions for the minix filesystem.  */
multiline_comment|/* FIXME !!! */
DECL|macro|minix_test_and_set_bit
mdefine_line|#define minix_test_and_set_bit(nr,addr) test_and_set_bit(nr,addr)
DECL|macro|minix_set_bit
mdefine_line|#define minix_set_bit(nr,addr) set_bit(nr,addr)
DECL|macro|minix_test_and_clear_bit
mdefine_line|#define minix_test_and_clear_bit(nr,addr) test_and_clear_bit(nr,addr)
DECL|macro|minix_test_bit
mdefine_line|#define minix_test_bit(nr,addr) test_bit(nr,addr)
DECL|macro|minix_find_first_zero_bit
mdefine_line|#define minix_find_first_zero_bit(addr,size) find_first_zero_bit(addr,size)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _S390_BITOPS_H */
eof
