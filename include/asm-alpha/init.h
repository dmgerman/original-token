macro_line|#ifndef _ALPHA_INIT_H
DECL|macro|_ALPHA_INIT_H
mdefine_line|#define _ALPHA_INIT_H
macro_line|#ifndef MODULE
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;.text.init,&quot;ax&quot;
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;.data.init,&quot;a&quot;
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(32)))
multiline_comment|/*&n; * Used for initialization calls.&n; */
DECL|typedef|initcall_t
r_typedef
r_int
(paren
op_star
id|initcall_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|initcall_t
id|__initcall_start
comma
id|__initcall_end
suffix:semicolon
DECL|macro|__initcall
mdefine_line|#define __initcall(fn)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static __attribute__ ((unused, __section__ (&quot;.initcall.init&quot;)))&t;&bslash;&n;&t;  initcall_t __initcall_##fn = fn
multiline_comment|/*&n; * Used for kernel command line parameter setup.&n; */
DECL|struct|kernel_param
r_struct
id|kernel_param
(brace
DECL|member|str
r_const
r_char
op_star
id|str
suffix:semicolon
DECL|member|setup_func
r_int
(paren
op_star
id|setup_func
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|kernel_param
id|__setup_start
comma
id|__setup_end
suffix:semicolon
DECL|macro|__setup
mdefine_line|#define __setup(str, fn)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static __attribute__ ((__section__ (&quot;.data.init&quot;)))&t;&t;&bslash;&n;&t;  char __setup_str_##fn[] = str;&t;&t;&t;&t;&bslash;&n;&t;static __attribute__ ((unused, __section__ (&quot;.setup.init&quot;)))&t;&bslash;&n;&t;  struct kernel_param __setup_##fn = { __setup_str_##fn, fn }
macro_line|#endif /* MODULE */
macro_line|#endif /* _ALPHA_INIT_H */
eof
