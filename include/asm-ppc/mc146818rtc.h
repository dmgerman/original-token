multiline_comment|/* mc146818rtc.h - register definitions for the Real-Time-Clock / CMOS RAM&n; * Copyright Torsten Duwe &lt;duwe@informatik.uni-erlangen.de&gt; 1993&n; * derived from Data Sheet, Copyright Motorola 1984 (!).&n; * It was written to be part of the Linux operating system.&n; */
multiline_comment|/* permission is hereby granted to copy, modify and redistribute this code&n; * in terms of the GNU Library General Public License, Version 2 or later,&n; * at your option.&n; */
macro_line|#ifndef _MC146818RTC_H
DECL|macro|_MC146818RTC_H
mdefine_line|#define _MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef MCRTC_PORT
DECL|macro|MCRTC_PORT
mdefine_line|#define MCRTC_PORT(x)&t;(0x70 + (x))
DECL|macro|MCRTC_ALWAYS_BCD
mdefine_line|#define MCRTC_ALWAYS_BCD&t;1
macro_line|#endif
DECL|macro|CMOS_MCRTC_READ
mdefine_line|#define CMOS_MCRTC_READ(addr) ({ &bslash;&n;outb_p((addr),MCRTC_PORT(0)); &bslash;&n;inb_p(MCRTC_PORT(1)); &bslash;&n;})
DECL|macro|CMOS_MCRTC_WRITE
mdefine_line|#define CMOS_MCRTC_WRITE(val, addr) ({ &bslash;&n;outb_p((addr),MCRTC_PORT(0)); &bslash;&n;outb_p((val),MCRTC_PORT(1)); &bslash;&n;})
multiline_comment|/**********************************************************************&n; * register summary&n; **********************************************************************/
DECL|macro|MCRTC_SECONDS
mdefine_line|#define MCRTC_SECONDS&t;&t;0
DECL|macro|MCRTC_SECONDS_ALARM
mdefine_line|#define MCRTC_SECONDS_ALARM&t;1
DECL|macro|MCRTC_MINUTES
mdefine_line|#define MCRTC_MINUTES&t;&t;2
DECL|macro|MCRTC_MINUTES_ALARM
mdefine_line|#define MCRTC_MINUTES_ALARM&t;3
DECL|macro|MCRTC_HOURS
mdefine_line|#define MCRTC_HOURS&t;&t;4
DECL|macro|MCRTC_HOURS_ALARM
mdefine_line|#define MCRTC_HOURS_ALARM&t;&t;5
multiline_comment|/* RTC_*_alarm is always true if 2 MSBs are set */
DECL|macro|MCRTC_ALARM_DONT_CARE
macro_line|# define MCRTC_ALARM_DONT_CARE &t;0xC0
DECL|macro|MCRTC_DAY_OF_WEEK
mdefine_line|#define MCRTC_DAY_OF_WEEK&t;&t;6
DECL|macro|MCRTC_DAY_OF_MONTH
mdefine_line|#define MCRTC_DAY_OF_MONTH&t;7
DECL|macro|MCRTC_MONTH
mdefine_line|#define MCRTC_MONTH&t;&t;8
DECL|macro|MCRTC_YEAR
mdefine_line|#define MCRTC_YEAR&t;&t;9
multiline_comment|/* control registers - Moto names&n; */
DECL|macro|MCRTC_REG_A
mdefine_line|#define MCRTC_REG_A&t;&t;10
DECL|macro|MCRTC_REG_B
mdefine_line|#define MCRTC_REG_B&t;&t;11
DECL|macro|MCRTC_REG_C
mdefine_line|#define MCRTC_REG_C&t;&t;12
DECL|macro|MCRTC_REG_D
mdefine_line|#define MCRTC_REG_D&t;&t;13
multiline_comment|/**********************************************************************&n; * register details&n; **********************************************************************/
DECL|macro|MCRTC_FREQ_SELECT
mdefine_line|#define MCRTC_FREQ_SELECT&t;MCRTC_REG_A
multiline_comment|/* update-in-progress  - set to &quot;1&quot; 244 microsecs before RTC goes off the bus,&n; * reset after update (may take 1.984ms @ 32768Hz RefClock) is complete,&n; * totalling to a max high interval of 2.228 ms.&n; */
DECL|macro|MCRTC_UIP
macro_line|# define MCRTC_UIP&t;&t;0x80
DECL|macro|MCRTC_DIV_CTL
macro_line|# define MCRTC_DIV_CTL&t;&t;0x70
multiline_comment|/* divider control: refclock values 4.194 / 1.049 MHz / 32.768 kHz */
DECL|macro|MCRTC_REF_CLCK_4MHZ
macro_line|#  define MCRTC_REF_CLCK_4MHZ&t;0x00
DECL|macro|MCRTC_REF_CLCK_1MHZ
macro_line|#  define MCRTC_REF_CLCK_1MHZ&t;0x10
DECL|macro|MCRTC_REF_CLCK_32KHZ
macro_line|#  define MCRTC_REF_CLCK_32KHZ&t;0x20
multiline_comment|/* 2 values for divider stage reset, others for &quot;testing purposes only&quot; */
DECL|macro|MCRTC_DIV_RESET1
macro_line|#  define MCRTC_DIV_RESET1&t;0x60
DECL|macro|MCRTC_DIV_RESET2
macro_line|#  define MCRTC_DIV_RESET2&t;0x70
multiline_comment|/* Periodic intr. / Square wave rate select. 0=none, 1=32.8kHz,... 15=2Hz */
DECL|macro|MCRTC_RATE_SELECT
macro_line|# define MCRTC_RATE_SELECT &t;0x0F
multiline_comment|/**********************************************************************/
DECL|macro|MCRTC_CONTROL
mdefine_line|#define MCRTC_CONTROL&t;MCRTC_REG_B
DECL|macro|MCRTC_SET
macro_line|# define MCRTC_SET 0x80&t;&t;/* disable updates for clock setting */
DECL|macro|MCRTC_PIE
macro_line|# define MCRTC_PIE 0x40&t;&t;/* periodic interrupt enable */
DECL|macro|MCRTC_AIE
macro_line|# define MCRTC_AIE 0x20&t;&t;/* alarm interrupt enable */
DECL|macro|MCRTC_UIE
macro_line|# define MCRTC_UIE 0x10&t;&t;/* update-finished interrupt enable */
DECL|macro|MCRTC_SQWE
macro_line|# define MCRTC_SQWE 0x08&t;&t;/* enable square-wave output */
DECL|macro|MCRTC_DM_BINARY
macro_line|# define MCRTC_DM_BINARY 0x04&t;/* all time/date values are BCD if clear */
DECL|macro|MCRTC_24H
macro_line|# define MCRTC_24H 0x02&t;&t;/* 24 hour mode - else hours bit 7 means pm */
DECL|macro|MCRTC_DST_EN
macro_line|# define MCRTC_DST_EN 0x01&t;/* auto switch DST - works f. USA only */
multiline_comment|/**********************************************************************/
DECL|macro|MCRTC_INTR_FLAGS
mdefine_line|#define MCRTC_INTR_FLAGS&t;MCRTC_REG_C
multiline_comment|/* caution - cleared by read */
DECL|macro|MCRTC_IRQF
macro_line|# define MCRTC_IRQF 0x80&t;&t;/* any of the following 3 is active */
DECL|macro|MCRTC_PF
macro_line|# define MCRTC_PF 0x40
DECL|macro|MCRTC_AF
macro_line|# define MCRTC_AF 0x20
DECL|macro|MCRTC_UF
macro_line|# define MCRTC_UF 0x10
multiline_comment|/**********************************************************************/
DECL|macro|MCRTC_VALID
mdefine_line|#define MCRTC_VALID&t;MCRTC_REG_D
DECL|macro|MCRTC_VRT
macro_line|# define MCRTC_VRT 0x80&t;&t;/* valid RAM and time */
multiline_comment|/**********************************************************************/
multiline_comment|/* example: !(CMOS_READ(MCRTC_CONTROL) &amp; MCRTC_DM_BINARY) &n; * determines if the following two #defines are needed&n; */
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
macro_line|#endif /* _MC146818RTC_H */
eof
