multiline_comment|/*&n; * linux/include/linux/lockd/nlm.h&n; *&n; * Declarations for the Network Lock Manager protocol.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_NLM_H
DECL|macro|LINUX_LOCKD_NLM_H
mdefine_line|#define LINUX_LOCKD_NLM_H
multiline_comment|/* Maximum file offset in file_lock.fl_end */
macro_line|#ifdef OFFSET_MAX
DECL|macro|NLM_OFFSET_MAX
macro_line|# define NLM_OFFSET_MAX&t;&t;OFFSET_MAX
macro_line|#else
DECL|macro|NLM_OFFSET_MAX
macro_line|# define NLM_OFFSET_MAX&t;&t;((off_t) 0x7fffffff)
macro_line|#endif
multiline_comment|/* Return states for NLM */
r_enum
(brace
DECL|enumerator|NLM_LCK_GRANTED
id|NLM_LCK_GRANTED
op_assign
l_int|0
comma
DECL|enumerator|NLM_LCK_DENIED
id|NLM_LCK_DENIED
comma
DECL|enumerator|NLM_LCK_DENIED_NOLOCKS
id|NLM_LCK_DENIED_NOLOCKS
comma
DECL|enumerator|NLM_LCK_BLOCKED
id|NLM_LCK_BLOCKED
comma
DECL|enumerator|NLM_LCK_DENIED_GRACE_PERIOD
id|NLM_LCK_DENIED_GRACE_PERIOD
comma
)brace
suffix:semicolon
DECL|macro|NLM_PROGRAM
mdefine_line|#define NLM_PROGRAM&t;&t;100021
DECL|macro|NLMPROC_NULL
mdefine_line|#define NLMPROC_NULL&t;&t;0
DECL|macro|NLMPROC_TEST
mdefine_line|#define NLMPROC_TEST&t;&t;1
DECL|macro|NLMPROC_LOCK
mdefine_line|#define NLMPROC_LOCK&t;&t;2
DECL|macro|NLMPROC_CANCEL
mdefine_line|#define NLMPROC_CANCEL&t;&t;3
DECL|macro|NLMPROC_UNLOCK
mdefine_line|#define NLMPROC_UNLOCK&t;&t;4
DECL|macro|NLMPROC_GRANTED
mdefine_line|#define NLMPROC_GRANTED&t;&t;5
DECL|macro|NLMPROC_TEST_MSG
mdefine_line|#define NLMPROC_TEST_MSG&t;6
DECL|macro|NLMPROC_LOCK_MSG
mdefine_line|#define NLMPROC_LOCK_MSG&t;7
DECL|macro|NLMPROC_CANCEL_MSG
mdefine_line|#define NLMPROC_CANCEL_MSG&t;8
DECL|macro|NLMPROC_UNLOCK_MSG
mdefine_line|#define NLMPROC_UNLOCK_MSG&t;9
DECL|macro|NLMPROC_GRANTED_MSG
mdefine_line|#define NLMPROC_GRANTED_MSG&t;10
DECL|macro|NLMPROC_TEST_RES
mdefine_line|#define NLMPROC_TEST_RES&t;11
DECL|macro|NLMPROC_LOCK_RES
mdefine_line|#define NLMPROC_LOCK_RES&t;12
DECL|macro|NLMPROC_CANCEL_RES
mdefine_line|#define NLMPROC_CANCEL_RES&t;13
DECL|macro|NLMPROC_UNLOCK_RES
mdefine_line|#define NLMPROC_UNLOCK_RES&t;14
DECL|macro|NLMPROC_GRANTED_RES
mdefine_line|#define NLMPROC_GRANTED_RES&t;15
DECL|macro|NLMPROC_SHARE
mdefine_line|#define NLMPROC_SHARE&t;&t;20
DECL|macro|NLMPROC_UNSHARE
mdefine_line|#define NLMPROC_UNSHARE&t;&t;21
DECL|macro|NLMPROC_NM_LOCK
mdefine_line|#define NLMPROC_NM_LOCK&t;&t;22
DECL|macro|NLMPROC_FREE_ALL
mdefine_line|#define NLMPROC_FREE_ALL&t;23
DECL|macro|NLMPROC_NSM_NOTIFY
mdefine_line|#define NLMPROC_NSM_NOTIFY&t;24&t;&t;/* statd callback */
macro_line|#endif /* LINUX_LOCKD_NLM_H */
eof
