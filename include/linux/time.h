macro_line|#ifndef _LINUX_TIME_H
DECL|macro|_LINUX_TIME_H
mdefine_line|#define _LINUX_TIME_H
DECL|struct|timeval
r_struct
id|timeval
(brace
DECL|member|tv_sec
r_int
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_usec
r_int
id|tv_usec
suffix:semicolon
multiline_comment|/* microseconds */
)brace
suffix:semicolon
DECL|struct|timezone
r_struct
id|timezone
(brace
DECL|member|tz_minuteswest
r_int
id|tz_minuteswest
suffix:semicolon
multiline_comment|/* minutes west of Greenwich */
DECL|member|tz_dsttime
r_int
id|tz_dsttime
suffix:semicolon
multiline_comment|/* type of dst correction */
)brace
suffix:semicolon
DECL|macro|FD_SETSIZE
mdefine_line|#define FD_SETSIZE&t;&t;(8*sizeof(fd_set))
DECL|macro|FD_SET
mdefine_line|#define FD_SET(fd,fdsetp)&t;(*(fdsetp) |= (1 &lt;&lt; (fd)))
DECL|macro|FD_CLR
mdefine_line|#define FD_CLR(fd,fdsetp)&t;(*(fdsetp) &amp;= ~(1 &lt;&lt; (fd)))
DECL|macro|FD_ISSET
mdefine_line|#define FD_ISSET(fd,fdsetp)&t;((*(fdsetp) &gt;&gt; fd) &amp; 1)
DECL|macro|FD_ZERO
mdefine_line|#define FD_ZERO(fdsetp)&t;&t;(*(fdsetp) = 0)
multiline_comment|/*&n; * Names of the interval timers, and structure&n; * defining a timer setting.&n; */
DECL|macro|ITIMER_REAL
mdefine_line|#define&t;ITIMER_REAL&t;0
DECL|macro|ITIMER_VIRTUAL
mdefine_line|#define&t;ITIMER_VIRTUAL&t;1
DECL|macro|ITIMER_PROF
mdefine_line|#define&t;ITIMER_PROF&t;2
DECL|struct|itimerval
r_struct
id|itimerval
(brace
DECL|member|it_interval
r_struct
id|timeval
id|it_interval
suffix:semicolon
multiline_comment|/* timer interval */
DECL|member|it_value
r_struct
id|timeval
id|it_value
suffix:semicolon
multiline_comment|/* current value */
)brace
suffix:semicolon
macro_line|#endif
eof
