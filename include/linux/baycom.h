multiline_comment|/*&n; * The Linux BAYCOM driver for the Baycom serial 1200 baud modem&n; * and the parallel 9600 baud modem&n; * (C) 1996 by Thomas Sailer, HB9JNX&n; */
macro_line|#ifndef _BAYCOM_H
DECL|macro|_BAYCOM_H
mdefine_line|#define _BAYCOM_H
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * structs for the IOCTL commands&n; */
DECL|struct|baycom_debug_data
r_struct
id|baycom_debug_data
(brace
DECL|member|debug1
r_int
r_int
id|debug1
suffix:semicolon
DECL|member|debug2
r_int
r_int
id|debug2
suffix:semicolon
DECL|member|debug3
r_int
id|debug3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|baycom_modem_type
r_struct
id|baycom_modem_type
(brace
DECL|member|modem_type
r_int
r_char
id|modem_type
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|baycom_ioctl
r_struct
id|baycom_ioctl
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
r_union
(brace
DECL|member|mt
r_struct
id|baycom_modem_type
id|mt
suffix:semicolon
DECL|member|dbg
r_struct
id|baycom_debug_data
id|dbg
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------- */
multiline_comment|/*&n; * modem types&n; */
DECL|macro|BAYCOM_MODEM_INVALID
mdefine_line|#define BAYCOM_MODEM_INVALID 0
DECL|macro|BAYCOM_MODEM_SER12
mdefine_line|#define BAYCOM_MODEM_SER12   1
DECL|macro|BAYCOM_MODEM_PAR96
mdefine_line|#define BAYCOM_MODEM_PAR96   2
multiline_comment|/*&n; * modem options; bit mask&n; */
DECL|macro|BAYCOM_OPTIONS_SOFTDCD
mdefine_line|#define BAYCOM_OPTIONS_SOFTDCD  1
multiline_comment|/*&n; * ioctl values change for baycom_net&n; */
DECL|macro|BAYCOMCTL_GETMODEMTYPE
mdefine_line|#define BAYCOMCTL_GETMODEMTYPE   0x90
DECL|macro|BAYCOMCTL_SETMODEMTYPE
mdefine_line|#define BAYCOMCTL_SETMODEMTYPE   0x91
DECL|macro|BAYCOMCTL_GETDEBUG
mdefine_line|#define BAYCOMCTL_GETDEBUG       0x92
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#endif /* _BAYCOM_H */
multiline_comment|/* --------------------------------------------------------------------- */
eof
