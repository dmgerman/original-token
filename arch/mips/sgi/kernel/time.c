multiline_comment|/* $Id: time.c,v 1.2 1998/05/01 01:35:20 ralf Exp $&n; * time.c: Generic SGI time_init() code, this will dispatch to the&n; *         appropriate per-architecture time/counter init code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_void
id|indy_timer_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|time_init
c_func
(paren
r_void
)paren
)paren
(brace
multiline_comment|/* XXX assume INDY for now XXX */
id|indy_timer_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
