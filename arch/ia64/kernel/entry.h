multiline_comment|/*&n; * Preserved registers that are shared between code in ivt.S and entry.S.  Be&n; * careful not to step on these!&n; */
DECL|macro|pEOI
mdefine_line|#define pEOI&t;&t;p1&t;/* should leave_kernel write EOI? */
DECL|macro|pKern
mdefine_line|#define pKern&t;&t;p2&t;/* will leave_kernel return to kernel-mode? */
DECL|macro|pSys
mdefine_line|#define pSys&t;&t;p4&t;/* are we processing a (synchronous) system call? */
DECL|macro|pNonSys
mdefine_line|#define pNonSys&t;&t;p5&t;/* complement of pSys */
eof
