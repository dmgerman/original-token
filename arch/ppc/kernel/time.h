multiline_comment|/*&n; * $Id: time.h,v 1.3 1997/08/12 08:22:14 cort Exp $&n; * Common time prototypes and such for all ppc machines.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu) to merge&n; * Paul Mackerras&squot; version and mine for PReP and Pmac.&n; */
multiline_comment|/* time.c */
id|__inline__
r_int
r_int
id|get_dec
c_func
(paren
r_void
)paren
suffix:semicolon
id|__inline__
r_void
id|set_dec
c_func
(paren
r_int
id|val
)paren
suffix:semicolon
r_void
id|prep_calibrate_decr_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_void
id|prep_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pmac_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|decrementer_count
suffix:semicolon
r_extern
r_int
id|count_period_num
suffix:semicolon
r_extern
r_int
id|count_period_den
suffix:semicolon
multiline_comment|/* pmac/prep_time.c */
r_int
r_int
id|prep_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|pmac_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|prep_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_int
id|pmac_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_void
id|pmac_read_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
eof
