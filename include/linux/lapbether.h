macro_line|#ifndef&t;__LAPBETHER_H
DECL|macro|__LAPBETHER_H
mdefine_line|#define&t;__LAPBETHER_H
multiline_comment|/*&n; * &t;Defines for the LAPBETHER pseudo device driver&n; */
macro_line|#ifndef __LINUX_IF_ETHER_H
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#endif
DECL|macro|SIOCSLAPBETHADDR
mdefine_line|#define SIOCSLAPBETHADDR&t;(SIOCDEVPRIVATE+1)
DECL|struct|lapbeth_ethaddr
r_struct
id|lapbeth_ethaddr
(brace
DECL|member|destination
r_int
r_char
id|destination
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|accept
r_int
r_char
id|accept
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
