macro_line|#ifndef __LINUX_ACCT_H
DECL|macro|__LINUX_ACCT_H
mdefine_line|#define __LINUX_ACCT_H
DECL|macro|ACCT_COMM
mdefine_line|#define ACCT_COMM 16
DECL|struct|acct
r_struct
id|acct
(brace
DECL|member|ac_comm
r_char
id|ac_comm
(braket
id|ACCT_COMM
)braket
suffix:semicolon
multiline_comment|/* Accounting command name */
DECL|member|ac_utime
id|time_t
id|ac_utime
suffix:semicolon
multiline_comment|/* Accounting user time */
DECL|member|ac_stime
id|time_t
id|ac_stime
suffix:semicolon
multiline_comment|/* Accounting system time */
DECL|member|ac_etime
id|time_t
id|ac_etime
suffix:semicolon
multiline_comment|/* Accounting elapsed time */
DECL|member|ac_btime
id|time_t
id|ac_btime
suffix:semicolon
multiline_comment|/* Beginning time */
DECL|member|ac_uid
id|uid_t
id|ac_uid
suffix:semicolon
multiline_comment|/* Accounting user ID */
DECL|member|ac_gid
id|gid_t
id|ac_gid
suffix:semicolon
multiline_comment|/* Accounting group ID */
DECL|member|ac_tty
id|dev_t
id|ac_tty
suffix:semicolon
multiline_comment|/* controlling tty */
DECL|member|ac_flag
r_char
id|ac_flag
suffix:semicolon
multiline_comment|/* Accounting flag */
DECL|member|ac_minflt
r_int
id|ac_minflt
suffix:semicolon
multiline_comment|/* Accounting minor pagefaults */
DECL|member|ac_majflt
r_int
id|ac_majflt
suffix:semicolon
multiline_comment|/* Accounting major pagefaults */
DECL|member|ac_exitcode
r_int
id|ac_exitcode
suffix:semicolon
multiline_comment|/* Accounting process exitcode */
)brace
suffix:semicolon
DECL|macro|AFORK
mdefine_line|#define AFORK&t;0001&t;/* has executed fork, but no exec */
DECL|macro|ASU
mdefine_line|#define ASU&t;0002&t;/* used super-user privileges */
DECL|macro|ACORE
mdefine_line|#define ACORE&t;0004&t;/* dumped core */
DECL|macro|AXSIG
mdefine_line|#define AXSIG&t;0010&t;/* killed by a signal */
DECL|macro|AHZ
mdefine_line|#define AHZ     100
macro_line|#endif
eof
