macro_line|#ifndef _XOR_H
DECL|macro|_XOR_H
mdefine_line|#define _XOR_H
macro_line|#include &lt;linux/raid/md.h&gt;
DECL|macro|MAX_XOR_BLOCKS
mdefine_line|#define MAX_XOR_BLOCKS 4
r_extern
r_void
id|calibrate_xor_block
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|xor_block
)paren
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
suffix:semicolon
macro_line|#endif
eof
