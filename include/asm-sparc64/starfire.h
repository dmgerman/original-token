multiline_comment|/* $Id: starfire.h,v 1.1 2000/09/21 06:18:53 anton Exp $&n; * starfire.h: Group all starfire specific code together.&n; *&n; * Copyright (C) 2000 Anton Blanchard (anton@linuxcare.com)&n; */
macro_line|#ifndef _SPARC64_STARFIRE_H
DECL|macro|_SPARC64_STARFIRE_H
mdefine_line|#define _SPARC64_STARFIRE_H
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
id|this_is_starfire
suffix:semicolon
r_extern
r_void
id|check_if_starfire
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|starfire_cpu_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|starfire_hard_smp_processor_id
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|starfire_hookup
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|starfire_translate
c_func
(paren
r_int
r_int
id|imap
comma
r_int
r_int
id|upaid
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
