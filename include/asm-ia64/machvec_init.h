DECL|macro|MACHVEC_INHIBIT_RENAMING
mdefine_line|#define MACHVEC_INHIBIT_RENAMING
macro_line|#include &lt;asm/machvec.h&gt;
DECL|macro|MACHVEC_HELPER
mdefine_line|#define MACHVEC_HELPER(name)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; struct ia64_machine_vector machvec_##name __attribute__ ((unused, __section__ (&quot;.machvec&quot;)))&t;&bslash;&n;&t;= MACHVEC_INIT(name);
DECL|macro|MACHVEC_DEFINE
mdefine_line|#define MACHVEC_DEFINE(name)&t;MACHVEC_HELPER(name)
eof
