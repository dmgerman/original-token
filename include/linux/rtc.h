multiline_comment|/*&n; * Generic RTC interface.&n; * This version contains the part of the user interface to the Real Time Clock&n; * service. It is used with both the legacy mc146818 and also  EFI&n; * &n; * Copyright (C) 1999 Hewlett-Packard Co.&n; * Copyright (C) 1999 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#ifndef _LINUX_RTC_H
DECL|macro|_LINUX_RTC_H_
mdefine_line|#define _LINUX_RTC_H_
multiline_comment|/*&n; * The struct used to pass data via the following ioctl. Similar to the&n; * struct tm in &lt;time.h&gt;, but it needs to be here so that the kernel &n; * source is self contained, allowing cross-compiles, etc. etc.&n; */
DECL|struct|rtc_time
r_struct
id|rtc_time
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
multiline_comment|/*&n; * ioctl calls that are permitted to the /dev/rtc interface, if &n; * CONFIG_RTC/CONFIG_EFI_RTC was enabled.&n; */
DECL|macro|RTC_AIE_ON
mdefine_line|#define RTC_AIE_ON&t;_IO(&squot;p&squot;, 0x01)&t;/* Alarm int. enable on&t;&t;*/
DECL|macro|RTC_AIE_OFF
mdefine_line|#define RTC_AIE_OFF&t;_IO(&squot;p&squot;, 0x02)&t;/* ... off&t;&t;&t;*/
DECL|macro|RTC_UIE_ON
mdefine_line|#define RTC_UIE_ON&t;_IO(&squot;p&squot;, 0x03)&t;/* Update int. enable on&t;*/
DECL|macro|RTC_UIE_OFF
mdefine_line|#define RTC_UIE_OFF&t;_IO(&squot;p&squot;, 0x04)&t;/* ... off&t;&t;&t;*/
DECL|macro|RTC_PIE_ON
mdefine_line|#define RTC_PIE_ON&t;_IO(&squot;p&squot;, 0x05)&t;/* Periodic int. enable on&t;*/
DECL|macro|RTC_PIE_OFF
mdefine_line|#define RTC_PIE_OFF&t;_IO(&squot;p&squot;, 0x06)&t;/* ... off&t;&t;&t;*/
DECL|macro|RTC_ALM_SET
mdefine_line|#define RTC_ALM_SET&t;_IOW(&squot;p&squot;, 0x07, struct rtc_time) /* Set alarm time  */
DECL|macro|RTC_ALM_READ
mdefine_line|#define RTC_ALM_READ&t;_IOR(&squot;p&squot;, 0x08, struct rtc_time) /* Read alarm time */
DECL|macro|RTC_RD_TIME
mdefine_line|#define RTC_RD_TIME&t;_IOR(&squot;p&squot;, 0x09, struct rtc_time) /* Read RTC time   */
DECL|macro|RTC_SET_TIME
mdefine_line|#define RTC_SET_TIME&t;_IOW(&squot;p&squot;, 0x0a, struct rtc_time) /* Set RTC time    */
DECL|macro|RTC_IRQP_READ
mdefine_line|#define RTC_IRQP_READ&t;_IOR(&squot;p&squot;, 0x0b, unsigned long)&t; /* Read IRQ rate   */
DECL|macro|RTC_IRQP_SET
mdefine_line|#define RTC_IRQP_SET&t;_IOW(&squot;p&squot;, 0x0c, unsigned long)&t; /* Set IRQ rate    */
DECL|macro|RTC_EPOCH_READ
mdefine_line|#define RTC_EPOCH_READ&t;_IOR(&squot;p&squot;, 0x0d, unsigned long)&t; /* Read epoch      */
DECL|macro|RTC_EPOCH_SET
mdefine_line|#define RTC_EPOCH_SET&t;_IOW(&squot;p&squot;, 0x0e, unsigned long)&t; /* Set epoch       */
macro_line|#endif /* _LINUX_RTC_H_ */
eof
