multiline_comment|/*&n; * PowerPC atomic operations&n; */
macro_line|#ifndef _ASM_PPC_ATOMIC_H_ 
DECL|macro|_ASM_PPC_ATOMIC_H_
mdefine_line|#define _ASM_PPC_ATOMIC_H_
DECL|typedef|atomic_t
r_typedef
r_int
id|atomic_t
suffix:semicolon
multiline_comment|/*&n; * Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
DECL|macro|__atomic_fool_gcc
mdefine_line|#define __atomic_fool_gcc(x) (*(struct { int a[100]; } *)x)
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) ({atomic_sub(1,(v));(v);})
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) ({atomic_add(1,(v));(v);})
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
macro_line|#endif
eof
