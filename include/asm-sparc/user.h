multiline_comment|/* $Id: user.h,v 1.2 1995/11/25 02:33:15 davem Exp $&n; * asm-sparc/user.h: Core file definitions for the Sparc.&n; *&n; * Copyright (C) 1995 (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_USER_H
DECL|macro|_SPARC_USER_H
mdefine_line|#define _SPARC_USER_H
DECL|struct|user
r_struct
id|user
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|24
op_plus
l_int|32
)braket
suffix:semicolon
multiline_comment|/* locals, ins, globals + fpu regs */
DECL|member|u_tsize
r_int
id|u_tsize
suffix:semicolon
DECL|member|u_dsize
r_int
id|u_dsize
suffix:semicolon
DECL|member|u_ssize
r_int
id|u_ssize
suffix:semicolon
DECL|member|start_code
r_int
r_int
id|start_code
suffix:semicolon
DECL|member|start_data
r_int
r_int
id|start_data
suffix:semicolon
DECL|member|start_stack
r_int
r_int
id|start_stack
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|u_ar0
r_int
r_int
op_star
id|u_ar0
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NBPG
mdefine_line|#define NBPG                   PAGE_SIZE
DECL|macro|UPAGES
mdefine_line|#define UPAGES                 1
DECL|macro|HOST_TEXT_START_ADDR
mdefine_line|#define HOST_TEXT_START_ADDR   (u.start_code)
DECL|macro|HOST_DATA_START_ADDR
mdefine_line|#define HOST_DATA_START_ADDR   (u.start_data)
DECL|macro|HOST_STACK_END_ADDR
mdefine_line|#define HOST_STACK_END_ADDR    (u.start_stack + u.u_ssize * NBPG)
macro_line|#endif /* !(_SPARC_USER_H) */
eof
