macro_line|#ifndef _TIME_H
DECL|macro|_TIME_H
mdefine_line|#define _TIME_H
macro_line|#ifndef _TIME_T
DECL|macro|_TIME_T
mdefine_line|#define _TIME_T
DECL|typedef|time_t
r_typedef
r_int
id|time_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _SIZE_T
DECL|macro|_SIZE_T
mdefine_line|#define _SIZE_T
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
DECL|macro|CLOCKS_PER_SEC
mdefine_line|#define CLOCKS_PER_SEC 100
DECL|typedef|clock_t
r_typedef
r_int
id|clock_t
suffix:semicolon
DECL|struct|tm
r_struct
id|tm
(brace
DECL|member|tm_sec
r_int
id|tm_sec
suffix:semicolon
DECL|member|tm_min
r_int
id|tm_min
suffix:semicolon
DECL|member|tm_hour
r_int
id|tm_hour
suffix:semicolon
DECL|member|tm_mday
r_int
id|tm_mday
suffix:semicolon
DECL|member|tm_mon
r_int
id|tm_mon
suffix:semicolon
DECL|member|tm_year
r_int
id|tm_year
suffix:semicolon
DECL|member|tm_wday
r_int
id|tm_wday
suffix:semicolon
DECL|member|tm_yday
r_int
id|tm_yday
suffix:semicolon
DECL|member|tm_isdst
r_int
id|tm_isdst
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__isleap
mdefine_line|#define&t;__isleap(year)&t;&bslash;&n;  ((year) % 4 == 0 &amp;&amp; ((year) % 100 != 0 || (year) % 400 == 0))
id|clock_t
id|clock
c_func
(paren
r_void
)paren
suffix:semicolon
id|time_t
id|time
c_func
(paren
id|time_t
op_star
id|tp
)paren
suffix:semicolon
r_float
id|difftime
c_func
(paren
id|time_t
id|time2
comma
id|time_t
id|time1
)paren
suffix:semicolon
id|time_t
id|mktime
c_func
(paren
r_struct
id|tm
op_star
id|tp
)paren
suffix:semicolon
r_char
op_star
id|asctime
c_func
(paren
r_const
r_struct
id|tm
op_star
id|tp
)paren
suffix:semicolon
r_char
op_star
id|ctime
c_func
(paren
r_const
id|time_t
op_star
id|tp
)paren
suffix:semicolon
r_struct
id|tm
op_star
id|gmtime
c_func
(paren
r_const
id|time_t
op_star
id|tp
)paren
suffix:semicolon
r_struct
id|tm
op_star
id|localtime
c_func
(paren
r_const
id|time_t
op_star
id|tp
)paren
suffix:semicolon
r_int
id|strftime
c_func
(paren
r_char
op_star
id|s
comma
r_int
id|smax
comma
r_const
r_char
op_star
id|fmt
comma
r_const
r_struct
id|tm
op_star
id|tp
)paren
suffix:semicolon
r_void
id|tzset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
