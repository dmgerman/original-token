multiline_comment|/*&n; *  linux/kernel/time.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  This file contains the interface functions for the various&n; *  time related system calls: time, stime, gettimeofday, settimeofday,&n; *&t;&t;&t;       adjtime&n; */
multiline_comment|/*&n; * Modification history kernel/time.c&n; * &n; * 02 Sep 93    Philip Gladstone&n; *      Created file with time related functions from sched.c and adjtimex() &n; * 08 Oct 93    Torsten Duwe&n; *      adjtime interface update and CMOS clock write code&n; * 02 Jul 94&t;Alan Modra&n; *&t;fixed set_rtc_mmss, fixed time.year for &gt;= 2000, new mktime&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
multiline_comment|/* converts date to days since 1/1/1970&n; * assumes year,mon,day in normal date format&n; * ie. 1/1/1970 =&gt; year=1970, mon=1, day=1&n; *&n; * For the Julian calendar (which was used in Russia before 1917,&n; * Britain &amp; colonies before 1752, anywhere else before 1582,&n; * and is still in use by some communities) leave out the&n; * -year/100+year/400 terms, and add 10.&n; *&n; * This algorithm was first published by Gauss (I think).&n; */
DECL|function|mktime
r_static
r_inline
r_int
r_int
id|mktime
c_func
(paren
r_int
r_int
id|year
comma
r_int
r_int
id|mon
comma
r_int
r_int
id|day
comma
r_int
r_int
id|hour
comma
r_int
r_int
id|min
comma
r_int
r_int
id|sec
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ge
(paren
r_int
)paren
(paren
id|mon
op_sub_assign
l_int|2
)paren
)paren
(brace
multiline_comment|/* 1..12 -&gt; 11,12,1..10 */
id|mon
op_add_assign
l_int|12
suffix:semicolon
multiline_comment|/* Puts Feb last since it has leap day */
id|year
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_return
(paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|year
op_div
l_int|4
op_minus
id|year
op_div
l_int|100
op_plus
id|year
op_div
l_int|400
op_plus
l_int|367
op_star
id|mon
op_div
l_int|12
op_plus
id|day
)paren
op_plus
id|year
op_star
l_int|365
op_minus
l_int|719499
)paren
op_star
l_int|24
op_plus
id|hour
multiline_comment|/* now have hours */
)paren
op_star
l_int|60
op_plus
id|min
multiline_comment|/* now have minutes */
)paren
op_star
l_int|60
op_plus
id|sec
suffix:semicolon
multiline_comment|/* finally seconds */
)brace
DECL|function|time_init
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* checking for Update-In-Progress could be done more elegantly&n;&t; * (using the &quot;update finished&quot;-interrupt for example), but that&n;&t; * would require excessive testing. promise I&squot;ll do that when I find&n;&t; * the time.&t;&t;&t;- Torsten&n;&t; */
multiline_comment|/* read RTC exactly on falling edge of update flag */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* may take up to 1 second... */
r_if
c_cond
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
r_break
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* must try at least 2.228 ms*/
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
id|RTC_UIP
)paren
)paren
r_break
suffix:semicolon
r_do
(brace
multiline_comment|/* Isn&squot;t this overkill ? UIP above should guarantee consistency */
id|sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|hour
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mon
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|year
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|sec
op_ne
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|year
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|year
op_add_assign
l_int|1900
)paren
OL
l_int|1970
)paren
id|year
op_add_assign
l_int|100
suffix:semicolon
id|xtime.tv_sec
op_assign
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * The timezone where the local system is located.  Used as a default by some&n; * programs who obtain this value by using gettimeofday.&n; */
DECL|variable|sys_tz
r_struct
id|timezone
id|sys_tz
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|sys_time
id|asmlinkage
r_int
id|sys_time
c_func
(paren
r_int
op_star
id|tloc
)paren
(brace
r_int
id|i
comma
id|error
suffix:semicolon
id|i
op_assign
id|CURRENT_TIME
suffix:semicolon
r_if
c_cond
(paren
id|tloc
)paren
(brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|tloc
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|put_fs_long
c_func
(paren
id|i
comma
(paren
r_int
r_int
op_star
)paren
id|tloc
)paren
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
DECL|function|sys_stime
id|asmlinkage
r_int
id|sys_stime
c_func
(paren
r_int
r_int
op_star
id|tptr
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|tptr
comma
r_sizeof
(paren
op_star
id|tptr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|value
op_assign
id|get_fs_long
c_func
(paren
id|tptr
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|value
suffix:semicolon
id|xtime.tv_usec
op_assign
l_int|0
suffix:semicolon
id|time_status
op_assign
id|TIME_BAD
suffix:semicolon
id|time_maxerror
op_assign
l_int|0x70000000
suffix:semicolon
id|time_esterror
op_assign
l_int|0x70000000
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This function must be called with interrupts disabled &n; * It was inspired by Steve McCanne&squot;s microtime-i386 for BSD.  -- jrs&n; * &n; * However, the pc-audio speaker driver changes the divisor so that&n; * it gets interrupted rather more often - it loads 64 into the&n; * counter rather than 11932! This has an adverse impact on&n; * do_gettimeoffset() -- it stops working! What is also not&n; * good is that the interval that our timer function gets called&n; * is no longer 10.0002 msecs, but 9.9767 msec. To get around this&n; * would require using a different timing source. Maybe someone&n; * could use the RTC - I know that this can interrupt at frequencies&n; * ranging from 8192Hz to 2Hz. If I had the energy, I&squot;d somehow fix&n; * it so that at startup, the timer code in sched.c would select&n; * using either the RTC or the 8253 timer. The decision would be&n; * based on whether there was any other device around that needed&n; * to trample on the 8253. I&squot;d set up the RTC to interrupt at 1024Hz,&n; * and then do some jiggery to have a version of do_timer that &n; * advanced the clock by 1/1024 sec. Every time that reached over 1/100&n; * of a second, then do all the old code. If the time was kept correct&n; * then do_gettimeoffset could just return 0 - there is no low order&n; * divider that can be accessed.&n; *&n; * Ideally, you would be able to use the RTC for the speaker driver,&n; * but it appears that the speaker driver really needs interrupt more&n; * often than every 120us or so.&n; *&n; * Anyway, this needs more thought....&t;&t;pjsg (28 Aug 93)&n; * &n; * If you are really that interested, you should be reading&n; * comp.protocols.time.ntp!&n; */
DECL|macro|TICK_SIZE
mdefine_line|#define TICK_SIZE tick
DECL|function|do_gettimeoffset
r_static
r_inline
r_int
r_int
id|do_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* timer count may underflow right here */
id|outb_p
c_func
(paren
l_int|0x00
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* latch the count ASAP */
id|count
op_assign
id|inb_p
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* read the latched count */
id|count
op_or_assign
id|inb
c_func
(paren
l_int|0x40
)paren
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* we know probability of underflow is always MUCH less than 1% */
r_if
c_cond
(paren
id|count
OG
(paren
id|LATCH
op_minus
id|LATCH
op_div
l_int|100
)paren
)paren
(brace
multiline_comment|/* check for pending timer interrupt */
id|outb_p
c_func
(paren
l_int|0x0a
comma
l_int|0x20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|1
)paren
id|offset
op_assign
id|TICK_SIZE
suffix:semicolon
)brace
id|count
op_assign
(paren
(paren
id|LATCH
op_minus
l_int|1
)paren
op_minus
id|count
)paren
op_star
id|TICK_SIZE
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
id|LATCH
op_div
l_int|2
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|offset
op_plus
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * This version of gettimeofday has near microsecond resolution.&n; */
DECL|function|do_gettimeofday
r_void
id|do_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|tv
op_assign
id|xtime
suffix:semicolon
macro_line|#if defined (__i386__) || defined (__mips__)
id|tv-&gt;tv_usec
op_add_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv-&gt;tv_usec
op_ge
l_int|1000000
)paren
(brace
id|tv-&gt;tv_usec
op_sub_assign
l_int|1000000
suffix:semicolon
id|tv-&gt;tv_sec
op_increment
suffix:semicolon
)brace
macro_line|#endif /* !defined (__i386__) &amp;&amp; !defined (__mips__) */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sys_gettimeofday
id|asmlinkage
r_int
id|sys_gettimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|tv
)paren
(brace
r_struct
id|timeval
id|ktv
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|tv
comma
r_sizeof
op_star
id|tv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|ktv
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ktv.tv_sec
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tv-&gt;tv_sec
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ktv.tv_usec
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|tv-&gt;tv_usec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|tz
comma
r_sizeof
op_star
id|tz
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sys_tz.tz_minuteswest
comma
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|sys_tz.tz_dsttime
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|tz
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust the time obtained from the CMOS to be GMT time instead of&n; * local time.&n; * &n; * This is ugly, but preferable to the alternatives.  Otherwise we&n; * would either need to write a program to do it in /etc/rc (and risk&n; * confusion if the program gets run more than once; it would also be &n; * hard to make the program warp the clock precisely n hours)  or&n; * compile in the timezone information into the kernel.  Bad, bad....&n; *&n; * XXX Currently does not adjust for daylight savings time.  May not&n; * need to do anything, depending on how smart (dumb?) the BIOS&n; * is.  Blast it all.... the best thing to do not depend on the CMOS&n; * clock at all, but get the time via NTP or timed if you&squot;re on a &n; * network....&t;&t;&t;&t;- TYT, 1/1/92&n; */
DECL|function|warp_clock
r_inline
r_static
r_void
id|warp_clock
c_func
(paren
r_void
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_sec
op_add_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The first time we set the timezone, we will warp the clock so that&n; * it is ticking GMT time instead of local time.  Presumably, &n; * if someone is setting the timezone then we are running in an&n; * environment where the programs understand about timezones.&n; * This should be done at boot time in the /etc/rc script, as&n; * soon as possible, so that the clock can be set right.  Otherwise,&n; * various programs will get confused when the clock gets warped.&n; */
DECL|function|sys_settimeofday
id|asmlinkage
r_int
id|sys_settimeofday
c_func
(paren
r_struct
id|timeval
op_star
id|tv
comma
r_struct
id|timezone
op_star
id|tz
)paren
(brace
r_static
r_int
id|firsttime
op_assign
l_int|1
suffix:semicolon
r_struct
id|timeval
id|new_tv
suffix:semicolon
r_struct
id|timezone
id|new_tz
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|tv
)paren
(brace
r_int
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|tv
comma
r_sizeof
(paren
op_star
id|tv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|new_tv
comma
id|tv
comma
r_sizeof
(paren
op_star
id|tv
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
r_int
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|tz
comma
r_sizeof
(paren
op_star
id|tz
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|new_tz
comma
id|tz
comma
r_sizeof
(paren
op_star
id|tz
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tz
)paren
(brace
id|sys_tz
op_assign
id|new_tz
suffix:semicolon
r_if
c_cond
(paren
id|firsttime
)paren
(brace
id|firsttime
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tv
)paren
id|warp_clock
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|tv
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This is revolting. We need to set the xtime.tv_usec&n;&t;&t; * correctly. However, the value in this location is&n;&t;&t; * is value at the last tick.&n;&t;&t; * Discover what correction gettimeofday&n;&t;&t; * would have done, and then undo it!&n;&t;&t; */
id|new_tv.tv_usec
op_sub_assign
id|do_gettimeoffset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_tv.tv_usec
OL
l_int|0
)paren
(brace
id|new_tv.tv_usec
op_add_assign
l_int|1000000
suffix:semicolon
id|new_tv.tv_sec
op_decrement
suffix:semicolon
)brace
id|xtime
op_assign
id|new_tv
suffix:semicolon
id|time_status
op_assign
id|TIME_BAD
suffix:semicolon
id|time_maxerror
op_assign
l_int|0x70000000
suffix:semicolon
id|time_esterror
op_assign
l_int|0x70000000
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* adjtimex mainly allows reading (and writing, if superuser) of&n; * kernel time-keeping variables. used by xntpd.&n; */
DECL|function|sys_adjtimex
id|asmlinkage
r_int
id|sys_adjtimex
c_func
(paren
r_struct
id|timex
op_star
id|txc_p
)paren
(brace
r_int
id|ltemp
comma
id|mtemp
comma
id|save_adjust
suffix:semicolon
r_int
id|error
suffix:semicolon
multiline_comment|/* Local copy of parameter */
r_struct
id|timex
id|txc
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|txc_p
comma
r_sizeof
(paren
r_struct
id|timex
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* Copy the user data space into the kernel copy&n;&t; * structure. But bear in mind that the structures&n;&t; * may change&n;&t; */
id|memcpy_fromfs
c_func
(paren
op_amp
id|txc
comma
id|txc_p
comma
r_sizeof
(paren
r_struct
id|timex
)paren
)paren
suffix:semicolon
multiline_comment|/* In order to modify anything, you gotta be super-user! */
r_if
c_cond
(paren
id|txc.mode
op_logical_and
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Now we validate the data before disabling interrupts&n;&t; */
r_if
c_cond
(paren
id|txc.mode
op_ne
id|ADJ_OFFSET_SINGLESHOT
op_logical_and
(paren
id|txc.mode
op_amp
id|ADJ_OFFSET
)paren
)paren
multiline_comment|/* Microsec field limited to -131000 .. 131000 usecs */
r_if
c_cond
(paren
id|txc.offset
op_le
op_minus
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|SHIFT_UPDATE
)paren
)paren
op_logical_or
id|txc.offset
op_ge
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|SHIFT_UPDATE
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* time_status must be in a fairly small range */
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_STATUS
)paren
r_if
c_cond
(paren
id|txc.status
template_param
id|TIME_BAD
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* if the quartz is off by more than 10% something is VERY wrong ! */
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_TICK
)paren
r_if
c_cond
(paren
id|txc.tick
template_param
l_int|1100000
op_div
id|HZ
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Save for later - semantics of adjtime is to return old value */
id|save_adjust
op_assign
id|time_adjust
suffix:semicolon
multiline_comment|/* If there are input parameters, then process them */
r_if
c_cond
(paren
id|txc.mode
)paren
(brace
r_if
c_cond
(paren
id|time_status
op_eq
id|TIME_BAD
)paren
id|time_status
op_assign
id|TIME_OK
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_STATUS
)paren
id|time_status
op_assign
id|txc.status
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_FREQUENCY
)paren
id|time_freq
op_assign
id|txc.frequency
op_lshift
(paren
id|SHIFT_KF
op_minus
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_MAXERROR
)paren
id|time_maxerror
op_assign
id|txc.maxerror
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_ESTERROR
)paren
id|time_esterror
op_assign
id|txc.esterror
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_TIMECONST
)paren
id|time_constant
op_assign
id|txc.time_constant
suffix:semicolon
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_OFFSET
)paren
r_if
c_cond
(paren
id|txc.mode
op_eq
id|ADJ_OFFSET_SINGLESHOT
)paren
(brace
id|time_adjust
op_assign
id|txc.offset
suffix:semicolon
)brace
r_else
multiline_comment|/* XXX should give an error if other bits set */
(brace
id|time_offset
op_assign
id|txc.offset
op_lshift
id|SHIFT_UPDATE
suffix:semicolon
id|mtemp
op_assign
id|xtime.tv_sec
op_minus
id|time_reftime
suffix:semicolon
id|time_reftime
op_assign
id|xtime.tv_sec
suffix:semicolon
r_if
c_cond
(paren
id|mtemp
OG
(paren
id|MAXSEC
op_plus
l_int|2
)paren
op_logical_or
id|mtemp
OL
l_int|0
)paren
id|mtemp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|txc.offset
OL
l_int|0
)paren
id|time_freq
op_sub_assign
(paren
op_minus
id|txc.offset
op_star
id|mtemp
)paren
op_rshift
(paren
id|time_constant
op_plus
id|time_constant
)paren
suffix:semicolon
r_else
id|time_freq
op_add_assign
(paren
id|txc.offset
op_star
id|mtemp
)paren
op_rshift
(paren
id|time_constant
op_plus
id|time_constant
)paren
suffix:semicolon
id|ltemp
op_assign
id|time_tolerance
op_lshift
id|SHIFT_KF
suffix:semicolon
r_if
c_cond
(paren
id|time_freq
OG
id|ltemp
)paren
id|time_freq
op_assign
id|ltemp
suffix:semicolon
r_else
r_if
c_cond
(paren
id|time_freq
OL
op_minus
id|ltemp
)paren
id|time_freq
op_assign
op_minus
id|ltemp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|txc.mode
op_amp
id|ADJ_TICK
)paren
id|tick
op_assign
id|txc.tick
suffix:semicolon
)brace
id|txc.offset
op_assign
id|save_adjust
suffix:semicolon
id|txc.frequency
op_assign
(paren
(paren
id|time_freq
op_plus
l_int|1
)paren
op_rshift
(paren
id|SHIFT_KF
op_minus
l_int|16
)paren
)paren
suffix:semicolon
id|txc.maxerror
op_assign
id|time_maxerror
suffix:semicolon
id|txc.esterror
op_assign
id|time_esterror
suffix:semicolon
id|txc.status
op_assign
id|time_status
suffix:semicolon
id|txc.time_constant
op_assign
id|time_constant
suffix:semicolon
id|txc.precision
op_assign
id|time_precision
suffix:semicolon
id|txc.tolerance
op_assign
id|time_tolerance
suffix:semicolon
id|txc.time
op_assign
id|xtime
suffix:semicolon
id|txc.tick
op_assign
id|tick
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|txc_p
comma
op_amp
id|txc
comma
r_sizeof
(paren
r_struct
id|timex
)paren
)paren
suffix:semicolon
r_return
id|time_status
suffix:semicolon
)brace
DECL|function|set_rtc_mmss
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
r_int
r_char
id|save_control
comma
id|save_freq_select
suffix:semicolon
id|save_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
multiline_comment|/* tell the clock it&squot;s being set */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_control
op_or
id|RTC_SET
)paren
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|save_freq_select
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
multiline_comment|/* stop and reset prescaler */
id|CMOS_WRITE
c_func
(paren
(paren
id|save_freq_select
op_or
id|RTC_DIV_RESET2
)paren
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|cmos_minutes
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
id|BCD_TO_BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/* since we&squot;re only adjusting minutes and seconds,&n;   * don&squot;t interfere with hour overflow. This avoids&n;   * messing with unknown time zones but requires your&n;   * RTC not to be off by more than 15 minutes&n;   */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
suffix:semicolon
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|save_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
)brace
id|CMOS_WRITE
c_func
(paren
id|real_seconds
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|real_minutes
comma
id|RTC_MINUTES
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_freq_select
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|save_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
