multiline_comment|/* -*- linux-c -*-&n; *&n; *&t;$Id: sysrq.h,v 1.2 1997/05/31 18:33:41 mj Exp $&n; *&n; *&t;Linux Magic System Request Key Hacks&n; *&n; *&t;(c) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
id|emergency_sync_scheduled
suffix:semicolon
DECL|macro|EMERG_SYNC
mdefine_line|#define EMERG_SYNC 1
DECL|macro|EMERG_REMOUNT
mdefine_line|#define EMERG_REMOUNT 2
r_extern
r_void
id|do_emergency_sync
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
DECL|macro|CHECK_EMERGENCY_SYNC
mdefine_line|#define CHECK_EMERGENCY_SYNC&t;&t;&t;&bslash;&n;&t;if (emergency_sync_scheduled)&t;&t;&bslash;&n;&t;&t;do_emergency_sync();
macro_line|#else
DECL|macro|CHECK_EMERGENCY_SYNC
mdefine_line|#define CHECK_EMERGENCY_SYNC
macro_line|#endif
eof
