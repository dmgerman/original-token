multiline_comment|/*&n; * Berkshire PC Watchdog Defines&n; * For version 0.41 of the driver&n; */
DECL|macro|PCWD_IOCTL_BASE
mdefine_line|#define&t;PCWD_IOCTL_BASE&t;&squot;W&squot;
DECL|macro|PCWD_GETSTAT
mdefine_line|#define&t;PCWD_GETSTAT&t;_IOR(PCWD_IOCTL_BASE, 1, int)
DECL|macro|PCWD_PING
mdefine_line|#define&t;PCWD_PING&t;_IOR(PCWD_IOCTL_BASE, 2, int)
DECL|macro|PCWD_PREVRESET
mdefine_line|#define&t;PCWD_PREVRESET&t;0x01&t;/* System previously reset by card */
DECL|macro|PCWD_TEMPSENSE
mdefine_line|#define&t;PCWD_TEMPSENSE&t;0x02&t;/* Temperature overheat sense */
eof
