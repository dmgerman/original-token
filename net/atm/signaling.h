multiline_comment|/* net/atm/signaling.h - ATM signaling */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_SIGNALING_H
DECL|macro|NET_ATM_SIGNALING_H
mdefine_line|#define NET_ATM_SIGNALING_H
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atmsvc.h&gt;
DECL|macro|WAITING
mdefine_line|#define WAITING 1 /* for reply: 0: no error, &lt; 0: error, ... */
r_extern
r_struct
id|atm_vcc
op_star
id|sigd
suffix:semicolon
multiline_comment|/* needed in svc_release */
r_void
id|sigd_enq
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_enum
id|atmsvc_msg_type
id|type
comma
r_const
r_struct
id|atm_vcc
op_star
id|listen_vcc
comma
r_const
r_struct
id|sockaddr_atmpvc
op_star
id|pvc
comma
r_const
r_struct
id|sockaddr_atmsvc
op_star
id|svc
)paren
suffix:semicolon
r_int
id|sigd_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
r_void
id|signaling_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
