DECL|macro|__MACHVEC_HDR
mdefine_line|#define __MACHVEC_HDR(n)&t;&t;&lt;asm/machvec_##n##.h&gt;
DECL|macro|__MACHVEC_EXPAND
mdefine_line|#define __MACHVEC_EXPAND(n)&t;&t;__MACHVEC_HDR(n)
DECL|macro|MACHVEC_PLATFORM_HEADER
mdefine_line|#define MACHVEC_PLATFORM_HEADER&t;&t;__MACHVEC_EXPAND(MACHVEC_PLATFORM_NAME)
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|MACHVEC_HELPER
mdefine_line|#define MACHVEC_HELPER(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; struct ia64_machine_vector machvec_##name __attribute__ ((unused, __section__ (&quot;.machvec&quot;)))&t;&bslash;&n;&t;= MACHVEC_INIT(name);
DECL|macro|MACHVEC_DEFINE
mdefine_line|#define MACHVEC_DEFINE(name)&t;MACHVEC_HELPER(name)
id|MACHVEC_DEFINE
c_func
(paren
id|MACHVEC_PLATFORM_NAME
)paren
eof
