macro_line|#ifndef _MIPS_BYTEORDER_H
DECL|macro|_MIPS_BYTEORDER_H
mdefine_line|#define _MIPS_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#if defined (__MIPSEB__)
macro_line|#  include &lt;linux/byteorder_big_endian.h&gt;
macro_line|#elif defined (__MIPSEL__)
macro_line|#  include &lt;linux/byteorder_little_endian.h&gt;
macro_line|#else
macro_line|#  error What&squot;s that? MIPS, but neither MIPSEB, nor MIPSEL???
macro_line|#endif
macro_line|#endif /* _MIPS_BYTEORDER_H */
eof
