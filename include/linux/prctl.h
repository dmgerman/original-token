macro_line|#ifndef _LINUX_PRCTL_H
DECL|macro|_LINUX_PRCTL_H
mdefine_line|#define _LINUX_PRCTL_H
multiline_comment|/* Values to pass as first argument to prctl() */
DECL|macro|PR_SET_PDEATHSIG
mdefine_line|#define PR_SET_PDEATHSIG  1  /* Second arg is a signal */
DECL|macro|PR_GET_PDEATHSIG
mdefine_line|#define PR_GET_PDEATHSIG  2  /* Second arg is a ptr to return the signal */
multiline_comment|/* Get/set current-&gt;dumpable */
DECL|macro|PR_GET_DUMPABLE
mdefine_line|#define PR_GET_DUMPABLE   3
DECL|macro|PR_SET_DUMPABLE
mdefine_line|#define PR_SET_DUMPABLE   4
macro_line|#endif /* _LINUX_PRCTL_H */
eof
