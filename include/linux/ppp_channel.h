macro_line|#ifndef _PPP_CHANNEL_H_
DECL|macro|_PPP_CHANNEL_H_
mdefine_line|#define _PPP_CHANNEL_H_
multiline_comment|/*&n; * Definitions for the interface between the generic PPP code&n; * and a PPP channel.&n; *&n; * A PPP channel provides a way for the generic PPP code to send&n; * and receive packets over some sort of communications medium.&n; * Packets are stored in sk_buffs and have the 2-byte PPP protocol&n; * number at the start, but not the address and control bytes.&n; *&n; * Copyright 1999 Paul Mackerras.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; * ==FILEVERSION 990909==&n; */
multiline_comment|/* $Id: ppp_channel.h,v 1.3 2000/01/31 01:42:48 davem Exp $ */
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_struct
id|ppp_channel
suffix:semicolon
DECL|struct|ppp_channel_ops
r_struct
id|ppp_channel_ops
(brace
multiline_comment|/* Send a packet (or multilink fragment) on this channel.&n;&t;   Returns 1 if it was accepted, 0 if not. */
DECL|member|start_xmit
r_int
(paren
op_star
id|start_xmit
)paren
(paren
r_struct
id|ppp_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ppp_channel
r_struct
id|ppp_channel
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
multiline_comment|/* channel private data */
DECL|member|ops
r_struct
id|ppp_channel_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* operations for this channel */
DECL|member|xmit_qlen
r_int
id|xmit_qlen
suffix:semicolon
multiline_comment|/* length of transmit queue (bytes) */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* transfer rate (bytes/second) */
DECL|member|latency
r_int
id|latency
suffix:semicolon
multiline_comment|/* overhead time in milliseconds */
DECL|member|hdrlen
r_int
id|hdrlen
suffix:semicolon
multiline_comment|/* amount of headroom channel needs */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* link in list of channels per unit */
DECL|member|ppp
r_void
op_star
id|ppp
suffix:semicolon
multiline_comment|/* opaque to channel */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Called by the channel when it can send some more data. */
r_extern
r_void
id|ppp_output_wakeup
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
multiline_comment|/* Called by the channel to process a received PPP packet.&n;   The packet should have just the 2-byte PPP protocol header. */
r_extern
r_void
id|ppp_input
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Called by the channel when an input error occurs, indicating&n;   that we may have missed a packet. */
r_extern
r_void
id|ppp_input_error
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/* Attach a channel to a given PPP unit. */
r_extern
r_int
id|ppp_register_channel
c_func
(paren
r_struct
id|ppp_channel
op_star
comma
r_int
id|unit
)paren
suffix:semicolon
multiline_comment|/* Detach a channel from its PPP unit (e.g. on hangup). */
r_extern
r_void
id|ppp_unregister_channel
c_func
(paren
r_struct
id|ppp_channel
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
