multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: oak_setup.c&n; *&n; *    Description:&n; *      Architecture- / platform-specific boot-time initialization code for&n; *      the IBM PowerPC 403GCX &quot;Oak&quot; evaluation board. Adapted from original&n; *      code by Gary Thomas, Cort Dougan &lt;cort@cs.nmt.edu&gt;, and Dan Malek&n; *      &lt;dmalek@jlc.net&gt;.&n; *&n; */
macro_line|#ifndef&t;__OAK_SETUP_H__
DECL|macro|__OAK_SETUP_H__
mdefine_line|#define&t;__OAK_SETUP_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
r_extern
r_void
id|oak_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|ird_start
comma
r_int
r_int
id|ird_end
comma
r_int
r_int
id|cline_start
comma
r_int
r_int
id|cline_end
)paren
suffix:semicolon
r_extern
r_void
id|oak_setup_arch
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __OAK_SETUP_H__ */
eof
