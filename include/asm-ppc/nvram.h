multiline_comment|/*&n; * PreP compliant NVRAM access&n; */
macro_line|#ifndef _PPC_NVRAM_H
DECL|macro|_PPC_NVRAM_H
mdefine_line|#define _PPC_NVRAM_H
DECL|macro|NVRAM_AS0
mdefine_line|#define NVRAM_AS0  0x74
DECL|macro|NVRAM_AS1
mdefine_line|#define NVRAM_AS1  0x75
DECL|macro|NVRAM_DATA
mdefine_line|#define NVRAM_DATA 0x77
multiline_comment|/* RTC Offsets */
DECL|macro|RTC_SECONDS
mdefine_line|#define RTC_SECONDS&t;&t;0x1FF9
DECL|macro|RTC_MINUTES
mdefine_line|#define RTC_MINUTES&t;&t;0x1FFA
DECL|macro|RTC_HOURS
mdefine_line|#define RTC_HOURS&t;&t;0x1FFB
DECL|macro|RTC_DAY_OF_WEEK
mdefine_line|#define RTC_DAY_OF_WEEK&t;&t;0x1FFC
DECL|macro|RTC_DAY_OF_MONTH
mdefine_line|#define RTC_DAY_OF_MONTH&t;0x1FFD
DECL|macro|RTC_MONTH
mdefine_line|#define RTC_MONTH&t;&t;0x1FFE
DECL|macro|RTC_YEAR
mdefine_line|#define RTC_YEAR&t;&t;0x1FFF
macro_line|#ifndef BCD_TO_BIN
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
macro_line|#endif
macro_line|#ifndef BIN_TO_BCD
DECL|macro|BIN_TO_BCD
mdefine_line|#define BIN_TO_BCD(val) ((val)=(((val)/10)&lt;&lt;4) + (val)%10)
macro_line|#endif
macro_line|#endif
eof
