multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;IP/TCP/UDP checksumming routines&n; *&n; * Authors:&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Tom May, &lt;ftom@netcom.com&gt;&n; *&t;&t;Lots of code moved from tcp.c and ip.c; see those files&n; *&t;&t;for more names.&n; *&n; * Changes:     Ingo Molnar, converted csum_partial_copy() to 2.1 exception&n; *&t;&t;&t;     handling.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;net/checksum.h&gt;
multiline_comment|/*&n; * computes a partial checksum, e.g. for TCP/UDP fragments&n; */
DECL|function|csum_partial
r_int
r_int
id|csum_partial
c_func
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
multiline_comment|/*&n;&t;   * Experiments with ethernet and slip connections show that buff&n;&t;   * is aligned on either a 2-byte or 4-byte boundary.  We get at&n;&t;   * least a 2x speedup on 486 and Pentium if it is 4-byte aligned.&n;&t;   * Fortunately, it is easy to convert 2-byte alignment to 4-byte&n;&t;   * alignment for the unrolled loop.&n;&t;   */
id|__asm__
c_func
(paren
"&quot;"
id|testl
"$"
l_int|2
comma
op_mod
op_mod
id|esi
macro_line|# Check alignment.
id|jz
l_float|2f
macro_line|# Jump if alignment is ok.
id|subl
"$"
l_int|2
comma
op_mod
op_mod
id|ecx
macro_line|# Alignment uses up two bytes.
id|jae
l_float|1f
macro_line|# Jump if we had at least two bytes.
id|addl
"$"
l_int|2
comma
op_mod
op_mod
id|ecx
macro_line|# ecx was &lt; 2.  Deal with it.
id|jmp
l_float|4f
l_int|1
suffix:colon
id|movw
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|bx
id|addl
"$"
l_int|2
comma
op_mod
op_mod
id|esi
id|addw
op_mod
op_mod
id|bx
comma
op_mod
op_mod
id|ax
id|adcl
"$"
l_int|0
comma
op_mod
op_mod
id|eax
l_int|2
suffix:colon
id|movl
op_mod
op_mod
id|ecx
comma
op_mod
op_mod
id|edx
id|shrl
"$"
l_int|5
comma
op_mod
op_mod
id|ecx
id|jz
l_float|2f
id|testl
op_mod
op_mod
id|esi
comma
op_mod
op_mod
id|esi
l_int|1
suffix:colon
id|movl
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|4
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|8
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|12
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|16
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|20
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|24
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|movl
l_int|28
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|ebx
id|adcl
op_mod
op_mod
id|ebx
comma
op_mod
op_mod
id|eax
id|lea
l_int|32
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|esi
id|dec
op_mod
op_mod
id|ecx
id|jne
l_int|1
id|b
id|adcl
"$"
l_int|0
comma
op_mod
op_mod
id|eax
l_int|2
suffix:colon
id|movl
op_mod
op_mod
id|edx
comma
op_mod
op_mod
id|ecx
id|andl
"$"
l_int|0x1c
comma
op_mod
op_mod
id|edx
id|je
l_float|4f
id|shrl
"$"
l_int|2
comma
op_mod
op_mod
id|edx
macro_line|# This clears CF
l_int|3
suffix:colon
id|adcl
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|eax
id|lea
l_int|4
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|esi
id|dec
op_mod
op_mod
id|edx
id|jne
l_int|3
id|b
id|adcl
"$"
l_int|0
comma
op_mod
op_mod
id|eax
l_int|4
suffix:colon
id|andl
"$"
l_int|3
comma
op_mod
op_mod
id|ecx
id|jz
l_float|7f
id|cmpl
"$"
l_int|2
comma
op_mod
op_mod
id|ecx
id|jb
l_float|5f
id|movw
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|cx
id|leal
l_int|2
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|esi
id|je
l_float|6f
id|shll
"$"
l_int|16
comma
op_mod
op_mod
id|ecx
l_int|5
suffix:colon
id|movb
(paren
op_mod
op_mod
id|esi
)paren
comma
op_mod
op_mod
id|cl
l_int|6
suffix:colon
id|addl
op_mod
op_mod
id|ecx
comma
op_mod
op_mod
id|eax
id|adcl
"$"
l_int|0
comma
op_mod
op_mod
id|eax
l_int|7
suffix:colon
"&quot;"
suffix:colon
l_string|&quot;=a&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;c&quot;
(paren
id|len
)paren
comma
l_string|&quot;S&quot;
(paren
id|buff
)paren
suffix:colon
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy from ds while checksumming, otherwise like csum_partial&n; *&n; * The macros SRC and DST specify wether there should be exception handling&n; * for the source and/or the destination addresses.&n; *&n; * FIXME: could someone double check wether i havent mixed up some SRC and&n; *&t;  DST definitions? It&squot;s damn hard to trigger all cases, i hope i got&n; *&t;  them all but theres no guarantee ...&n; */
DECL|macro|csum_partial_copy_type
mdefine_line|#define csum_partial_copy_type(type) &bslash;&n;unsigned int csum_partial_copy ##type (int * __csum_err, const char *src, char *dst,   &bslash;&n;&t;&t;&t;&t;  int len, int sum) {  &bslash;&n;    __asm__( &t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&quot;&t;&t;testl $2, %%edi&t;&t;# Check alignment. &t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jz 2f&t;&t;&t;# Jump if alignment is ok. &t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;subl $2, %%ecx&t;&t;# Alignment uses up two bytes. &t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jae 1f&t;&t;&t;# Jump if we had at least two bytes. &t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;addl $2, %%ecx&t;&t;# ecx was &lt; 2.  Deal with it. &t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jmp 4f &t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1000: &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t; 1:&t;movw (%%esi), %%bx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;addl $2, %%esi&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1001:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movw %%bx, (%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;addl $2, %%edi&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;addw %%bx, %%ax&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl $0, %%eax&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;2:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;pushl %%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;shrl $5, %%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jz 2f&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;testl %%esi, %%esi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1002:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1:&t;movl (%%esi), %%ebx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1003:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 4(%%esi), %%edx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%ebx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1004:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%ebx, (%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%edx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1005:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%edx, 4(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t; &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1006:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 8(%%esi), %%ebx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1007:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 12(%%esi), %%edx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%ebx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1008:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%ebx, 8(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%edx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1009:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%edx, 12(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t; &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1010: &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 16(%%esi), %%ebx &t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1011: &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 20(%%esi), %%edx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%ebx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1012:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%ebx, 16(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%edx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1013:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%edx, 20(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1014:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 24(%%esi), %%ebx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1015:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl 28(%%esi), %%edx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%ebx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1016:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%ebx, 24(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%edx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1017:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%edx, 28(%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t; &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1018:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;lea 32(%%esi), %%esi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1019:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;lea 32(%%edi), %%edi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;dec %%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jne 1b&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl $0, %%eax&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;2:&t;popl %%edx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%edx, %%ecx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;andl $0x1c, %%edx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;je 4f&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;shrl $2, %%edx&t;&t;# This clears CF&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1020:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;3:&t;movl (%%esi), %%ebx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl %%ebx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1021:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movl %%ebx, (%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1022:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;lea 4(%%esi), %%esi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1023:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;lea 4(%%edi), %%edi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;dec %%edx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jne 3b&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl $0, %%eax&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;4:&t;andl $3, %%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jz 7f&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;cmpl $2, %%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;jb 5f&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1024:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movw (%%esi), %%cx&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1025:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;leal 2(%%esi), %%esi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1026:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movw %%cx, (%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1027:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;leal 2(%%edi), %%edi&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;je 6f&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;shll $16,%%ecx&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1028:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;5:&t;movb (%%esi), %%cl&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;1029:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;movb %%cl, (%%edi)&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;6:&t;addl %%ecx, %%eax&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;adcl $0, %%eax&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;7:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;2000:&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;     &t;   .section .fixup,&bslash;&quot;ax&bslash;&quot;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;3000:&t;&t;movl %7,%1&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;/* FIXME: zero out the rest of the buffer here !!!!!! */&t;&t;&t;&bslash;&n;&quot;&t;&t;jmp 2000b&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;.previous&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;.align 4                   &t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot; &bslash;&n;SRC(  &quot;        .long 1000b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1001b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1002b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1003b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1004b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1005b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1006b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1007b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1008b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1009b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1010b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1011b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1012b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1013b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1014b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1015b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1016b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1017b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1018b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1019b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1020b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1021b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1022b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1023b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1024b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1025b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1026b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1027b,3000b        &bslash;n  &quot;    ) &bslash;&n;SRC(  &quot;        .long 1028b,3000b        &bslash;n  &quot;    ) &bslash;&n;DST(  &quot;        .long 1029b,3000b        &bslash;n  &quot;    ) &bslash;&n;&quot;        .previous                      &bslash;n  &quot; &t;&t;&t;&t;&bslash;&n;&t;: &quot;=a&quot; (sum), &quot;=r&quot; (*__csum_err)   &t;&t;&t;&t;&bslash;&n;&t;:  &quot;0&quot; (sum), &quot;c&quot; (len), &quot;S&quot; (src), &quot;D&quot; (dst), &t;&t;&t;&bslash;&n;&t;&t;&quot;1&quot; (*__csum_err), &quot;i&quot; (-EFAULT)   &t;&t;&t;&bslash;&n;&t;: &quot;bx&quot;, &quot;cx&quot;, &quot;dx&quot;, &quot;si&quot;, &quot;di&quot; );  &t;&t;&t;&t;&bslash;&n; &t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    return(sum);  &t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; *  Currently we need only 2 out of the 4 possible type combinations:&n; */
multiline_comment|/*&n; * Generate &squot;csum_partial_copy_from_user()&squot;, we need to do exception&n; * handling for source addresses.&n; */
DECL|macro|SRC
mdefine_line|#define SRC(x) x
DECL|macro|DST
mdefine_line|#define DST(x)
DECL|function|csum_partial_copy_type
id|csum_partial_copy_type
c_func
(paren
id|_from_user
)paren
DECL|macro|SRC
macro_line|#undef SRC
DECL|macro|DST
macro_line|#undef DST
multiline_comment|/*&n; * Generate &squot;csum_partial_copy_nocheck()&squot;, no need to do exception&n; * handling.&n; */
DECL|macro|SRC
mdefine_line|#define SRC(x)
DECL|macro|DST
mdefine_line|#define DST(x)
id|csum_partial_copy_type
c_func
(paren
id|_nocheck_generic
)paren
DECL|macro|SRC
macro_line|#undef SRC
DECL|macro|DST
macro_line|#undef DST
multiline_comment|/*&n; * Generate &squot;csum_partial_copy_old()&squot;, old and slow compability stuff,&n; * full checking.&n; *&n; * tell us if you see something printk-ing on this. This function will be&n; * removed soon.&n; */
DECL|macro|SRC
mdefine_line|#define SRC(x) x
DECL|macro|DST
mdefine_line|#define DST(x) x
id|csum_partial_copy_type
c_func
(paren
id|_old
)paren
DECL|macro|SRC
macro_line|#undef SRC
DECL|macro|DST
macro_line|#undef DST
r_int
r_int
id|csum_partial_copy
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
id|sum
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|csum_partial_copy_old
(paren
op_amp
id|error
comma
id|src
comma
id|dst
comma
id|len
comma
id|sum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
l_string|&quot;csum_partial_copy_old(): tell mingo to convert me!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
