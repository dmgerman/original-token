multiline_comment|/*&n; * linux/ipc/util.h&n; * Copyright (C) 1999 Christoph Rohland&n; */
multiline_comment|/*&n; * IPCMNI is the absolute maximum for ipc identifier. This is used to&n; * detect stale identifiers&n; */
DECL|macro|IPCMNI
mdefine_line|#define IPCMNI (1&lt;&lt;15)          
r_extern
r_int
id|ipcperms
(paren
r_struct
id|ipc_perm
op_star
id|ipcp
comma
r_int
id|shmflg
)paren
suffix:semicolon
eof
