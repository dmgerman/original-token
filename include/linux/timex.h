multiline_comment|/*****************************************************************************&n; *                                                                           *&n; * Copyright (c) David L. Mills 1993                                         *&n; *                                                                           *&n; * Permission to use, copy, modify, and distribute this software and its     *&n; * documentation for any purpose and without fee is hereby granted, provided *&n; * that the above copyright notice appears in all copies and that both the   *&n; * copyright notice and this permission notice appear in supporting          *&n; * documentation, and that the name University of Delaware not be used in    *&n; * advertising or publicity pertaining to distribution of the software       *&n; * without specific, written prior permission.  The University of Delaware   *&n; * makes no representations about the suitability this software for any      *&n; * purpose.  It is provided &quot;as is&quot; without express or implied warranty.     *&n; *                                                                           *&n; *****************************************************************************/
multiline_comment|/*&n; * Modification history timex.h&n; * &n; * 17 Sep 93    David L. Mills&n; *      Created file $NTP/include/sys/timex.h&n; * 07 Oct 93    Torsten Duwe&n; *      Derived linux/timex.h&n; */
macro_line|#ifndef _LINUX_TIMEX_H
DECL|macro|_LINUX_TIMEX_H
mdefine_line|#define _LINUX_TIMEX_H
multiline_comment|/*&n; * The following defines establish the engineering parameters of the PLL&n; * model. The HZ variable establishes the timer interrupt frequency, 100 Hz &n; * for the SunOS kernel, 256 Hz for the Ultrix kernel and 1024 Hz for the&n; * OSF/1 kernel. The SHIFT_HZ define expresses the same value as the&n; * nearest power of two in order to avoid hardware multiply operations.&n; */
DECL|macro|SHIFT_HZ
mdefine_line|#define SHIFT_HZ 7&t;&t;/* log2(HZ) */
multiline_comment|/*&n; * The SHIFT_KG and SHIFT_KF defines establish the damping of the PLL&n; * and are chosen by analysis for a slightly underdamped convergence&n; * characteristic. The MAXTC define establishes the maximum time constant&n; * of the PLL. With the parameters given and the default time constant of&n; * zero, the PLL will converge in about 15 minutes.&n; */
DECL|macro|SHIFT_KG
mdefine_line|#define SHIFT_KG 8&t;&t;/* shift for phase increment */
DECL|macro|SHIFT_KF
mdefine_line|#define SHIFT_KF 20&t;&t;/* shift for frequency increment */
DECL|macro|MAXTC
mdefine_line|#define MAXTC 6&t;&t;&t;/* maximum time constant (shift) */
multiline_comment|/*&n; * The SHIFT_SCALE define establishes the decimal point of the time_phase&n; * variable which serves as a an extension to the low-order bits of the&n; * system clock variable. The SHIFT_UPDATE define establishes the decimal&n; * point of the time_offset variable which represents the current offset&n; * with respect to standard time. The FINEUSEC define represents 1 usec in&n; * scaled units.&n; */
DECL|macro|SHIFT_SCALE
mdefine_line|#define SHIFT_SCALE 24&t;&t;/* shift for phase scale factor */
DECL|macro|SHIFT_UPDATE
mdefine_line|#define SHIFT_UPDATE (SHIFT_KG + MAXTC) /* shift for offset scale factor */
DECL|macro|FINEUSEC
mdefine_line|#define FINEUSEC (1 &lt;&lt; SHIFT_SCALE) /* 1 us in scaled units */
DECL|macro|MAXPHASE
mdefine_line|#define MAXPHASE 128000         /* max phase error (us) */
DECL|macro|MAXFREQ
mdefine_line|#define MAXFREQ 100             /* max frequency error (ppm) */
DECL|macro|MINSEC
mdefine_line|#define MINSEC 16               /* min interval between updates (s) */
DECL|macro|MAXSEC
mdefine_line|#define MAXSEC 1200             /* max interval between updates (s) */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193180 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|LATCH
mdefine_line|#define LATCH  ((CLOCK_TICK_RATE + HZ/2) / HZ)&t;/* For divider */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE (((((LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
multiline_comment|/*&n; * syscall interface - used (mainly by NTP daemon)&n; * to discipline kernel clock oscillator&n; */
DECL|struct|timex
r_struct
id|timex
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* mode selector */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* time offset (usec) */
DECL|member|frequency
r_int
id|frequency
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
DECL|member|maxerror
r_int
id|maxerror
suffix:semicolon
multiline_comment|/* maximum error (usec) */
DECL|member|esterror
r_int
id|esterror
suffix:semicolon
multiline_comment|/* estimated error (usec) */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* clock command/status */
DECL|member|time_constant
r_int
id|time_constant
suffix:semicolon
multiline_comment|/* pll time constant */
DECL|member|precision
r_int
id|precision
suffix:semicolon
multiline_comment|/* clock precision (usec) (read only) */
DECL|member|tolerance
r_int
id|tolerance
suffix:semicolon
multiline_comment|/* clock frequency tolerance (ppm)&n;&t;&t;&t;&t; * (read only)&n;&t;&t;&t;&t; */
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
multiline_comment|/* (read only) */
DECL|member|tick
r_int
id|tick
suffix:semicolon
multiline_comment|/* (modified) usecs between clock ticks */
)brace
suffix:semicolon
multiline_comment|/*&n; * Mode codes (timex.mode) &n; */
DECL|macro|ADJ_OFFSET
mdefine_line|#define ADJ_OFFSET&t;&t;0x0001&t;/* time offset */
DECL|macro|ADJ_FREQUENCY
mdefine_line|#define ADJ_FREQUENCY&t;&t;0x0002&t;/* frequency offset */
DECL|macro|ADJ_MAXERROR
mdefine_line|#define ADJ_MAXERROR&t;&t;0x0004&t;/* maximum time error */
DECL|macro|ADJ_ESTERROR
mdefine_line|#define ADJ_ESTERROR&t;&t;0x0008&t;/* estimated time error */
DECL|macro|ADJ_STATUS
mdefine_line|#define ADJ_STATUS&t;&t;0x0010&t;/* clock status */
DECL|macro|ADJ_TIMECONST
mdefine_line|#define ADJ_TIMECONST&t;&t;0x0020&t;/* pll time constant */
DECL|macro|ADJ_TICK
mdefine_line|#define ADJ_TICK&t;&t;0x4000&t;/* tick value */
DECL|macro|ADJ_OFFSET_SINGLESHOT
mdefine_line|#define ADJ_OFFSET_SINGLESHOT&t;0x8001&t;/* old-fashioned adjtime */
multiline_comment|/*&n; * Clock command/status codes (timex.status)&n; */
DECL|macro|TIME_OK
mdefine_line|#define TIME_OK&t;&t;0&t;/* clock synchronized */
DECL|macro|TIME_INS
mdefine_line|#define TIME_INS&t;1&t;/* insert leap second */
DECL|macro|TIME_DEL
mdefine_line|#define TIME_DEL&t;2&t;/* delete leap second */
DECL|macro|TIME_OOP
mdefine_line|#define TIME_OOP&t;3&t;/* leap second in progress */
DECL|macro|TIME_BAD
mdefine_line|#define TIME_BAD&t;4&t;/* clock not synchronized */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * kernel variables&n; */
r_extern
r_int
id|tick
suffix:semicolon
multiline_comment|/* timer interrupt period */
r_extern
r_int
id|tickadj
suffix:semicolon
multiline_comment|/* amount of adjustment per tick */
r_extern
r_volatile
r_struct
id|timeval
id|xtime
suffix:semicolon
multiline_comment|/* The current time */
multiline_comment|/*&n; * phase-lock loop variables&n; */
r_extern
r_int
id|time_status
suffix:semicolon
multiline_comment|/* clock synchronization status */
r_extern
r_int
id|time_offset
suffix:semicolon
multiline_comment|/* time adjustment (us) */
r_extern
r_int
id|time_constant
suffix:semicolon
multiline_comment|/* pll time constant */
r_extern
r_int
id|time_tolerance
suffix:semicolon
multiline_comment|/* frequency tolerance (ppm) */
r_extern
r_int
id|time_precision
suffix:semicolon
multiline_comment|/* clock precision (us) */
r_extern
r_int
id|time_maxerror
suffix:semicolon
multiline_comment|/* maximum error */
r_extern
r_int
id|time_esterror
suffix:semicolon
multiline_comment|/* estimated error */
r_extern
r_int
id|time_phase
suffix:semicolon
multiline_comment|/* phase offset (scaled us) */
r_extern
r_int
id|time_freq
suffix:semicolon
multiline_comment|/* frequency offset (scaled ppm) */
r_extern
r_int
id|time_adj
suffix:semicolon
multiline_comment|/* tick adjust (scaled 1 / HZ) */
r_extern
r_int
id|time_reftime
suffix:semicolon
multiline_comment|/* time at last adjustment (s) */
r_extern
r_int
id|time_adjust
suffix:semicolon
multiline_comment|/* The amount of adjtime left */
macro_line|#endif /* KERNEL */
macro_line|#endif /* LINUX_TIMEX_H */
eof
