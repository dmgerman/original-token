macro_line|#ifndef _SYS_TIME_H
DECL|macro|_SYS_TIME_H
mdefine_line|#define _SYS_TIME_H
multiline_comment|/* gettimofday returns this */
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
DECL|macro|DST_NONE
mdefine_line|#define&t;DST_NONE&t;0&t;/* not on dst */
DECL|macro|DST_USA
mdefine_line|#define&t;DST_USA&t;&t;1&t;/* USA style dst */
DECL|macro|DST_AUST
mdefine_line|#define&t;DST_AUST&t;2&t;/* Australian style dst */
DECL|macro|DST_WET
mdefine_line|#define&t;DST_WET&t;&t;3&t;/* Western European dst */
DECL|macro|DST_MET
mdefine_line|#define&t;DST_MET&t;&t;4&t;/* Middle European dst */
DECL|macro|DST_EET
mdefine_line|#define&t;DST_EET&t;&t;5&t;/* Eastern European dst */
DECL|macro|DST_CAN
mdefine_line|#define&t;DST_CAN&t;&t;6&t;/* Canada */
DECL|macro|DST_GB
mdefine_line|#define&t;DST_GB&t;&t;7&t;/* Great Britain and Eire */
DECL|macro|DST_RUM
mdefine_line|#define&t;DST_RUM&t;&t;8&t;/* Rumania */
DECL|macro|DST_TUR
mdefine_line|#define&t;DST_TUR&t;&t;9&t;/* Turkey */
DECL|macro|DST_AUSTALT
mdefine_line|#define&t;DST_AUSTALT&t;10&t;/* Australian style with shift in 1986 */
DECL|macro|FD_SET
mdefine_line|#define FD_SET(fd,fdsetp)&t;(*(fdsetp) |= (1 &lt;&lt; (fd)))
DECL|macro|FD_CLR
mdefine_line|#define FD_CLR(fd,fdsetp)&t;(*(fdsetp) &amp;= ~(1 &lt;&lt; (fd)))
DECL|macro|FD_ISSET
mdefine_line|#define FD_ISSET(fd,fdsetp)&t;((*(fdsetp) &gt;&gt; fd) &amp; 1)
DECL|macro|FD_ZERO
mdefine_line|#define FD_ZERO(fdsetp)&t;&t;(*(fdsetp) = 0)
multiline_comment|/*&n; * Operations on timevals.&n; *&n; * NB: timercmp does not work for &gt;= or &lt;=.&n; */
DECL|macro|timerisset
mdefine_line|#define&t;timerisset(tvp)&t;&t;((tvp)-&gt;tv_sec || (tvp)-&gt;tv_usec)
DECL|macro|timercmp
mdefine_line|#define&t;timercmp(tvp, uvp, cmp)&t;&bslash;&n;&t;((tvp)-&gt;tv_sec cmp (uvp)-&gt;tv_sec || &bslash;&n;&t; (tvp)-&gt;tv_sec == (uvp)-&gt;tv_sec &amp;&amp; (tvp)-&gt;tv_usec cmp (uvp)-&gt;tv_usec)
DECL|macro|timerclear
mdefine_line|#define&t;timerclear(tvp)&t;&t;((tvp)-&gt;tv_sec = (tvp)-&gt;tv_usec = 0)
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
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;sys/types.h&gt;
r_int
id|gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tp
comma
r_struct
id|timezone
op_star
id|tz
)paren
suffix:semicolon
r_int
id|select
c_func
(paren
r_int
id|width
comma
id|fd_set
op_star
id|readfds
comma
id|fd_set
op_star
id|writefds
comma
id|fd_set
op_star
id|exceptfds
comma
r_struct
id|timeval
op_star
id|timeout
)paren
suffix:semicolon
macro_line|#endif /*_SYS_TIME_H*/
eof
