multiline_comment|/*&n; * $Id: capidev.h,v 1.1 1997/03/04 21:50:30 calle Exp $&n; *&n; * CAPI 2.0 Interface for Linux&n; *&n; * (c) Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * $Log: capidev.h,v $&n; * Revision 1.1  1997/03/04 21:50:30  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; */
DECL|struct|capidev
r_struct
id|capidev
(brace
DECL|member|is_open
r_int
id|is_open
suffix:semicolon
DECL|member|is_registered
r_int
id|is_registered
suffix:semicolon
DECL|member|applid
id|__u16
id|applid
suffix:semicolon
DECL|member|recv_queue
r_struct
id|sk_buff_head
id|recv_queue
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 131841
DECL|member|recv_wait
r_struct
id|wait_queue
op_star
id|recv_wait
suffix:semicolon
macro_line|#else
DECL|member|recv_wait
id|wait_queue_head_t
id|recv_wait
suffix:semicolon
macro_line|#endif
DECL|member|errcode
id|__u16
id|errcode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CAPI_MAXMINOR
mdefine_line|#define CAPI_MAXMINOR&t;CAPI_MAXAPPL
eof
