multiline_comment|/*&n; *&t;&t;IP_MASQ_RAUDIO  - Real Audio masquerading module&n; *&n; *&n; * Version:&t;@(#)$Id: ip_masq_raudio.c,v 1.8 1997/11/28 15:32:32 alan Exp $&n; *&n; * Author:&t;Nigel Metheringham&n; *&t;&t;Real Time Streaming code by Progressive Networks&n; *&t;&t;[strongly based on ftp module by Juan Jose Ciarlante &amp; Wouter Gadeyne]&n; *&t;&t;[Real Audio information taken from Progressive Networks firewall docs]&n; *&t;&t;[Kudos to Progressive Networks for making the protocol specs available]&n; *&n; *&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&n; * Limitations&n; *&t;The IP Masquerading proxies at present do not have access to a processed&n; *&t;data stream.  Hence for a protocol like the Real Audio control protocol,&n; *&t;which depends on knowing where you are in the data stream, you either&n; *&t;to keep a *lot* of state in your proxy, or you cheat and simplify the&n; *&t;problem [needless to say I did the latter].&n; *&n; *&t;This proxy only handles data in the first packet.  Everything else is&n; *&t;passed transparently.  This means it should work under all normal&n; *&t;circumstances, but it could be fooled by new data formats or a&n; *&t;malicious application!&n; *&n; *&t;At present the &quot;first packet&quot; is defined as a packet starting with&n; *&t;the protocol ID string - &quot;PNA&quot;.&n; *&t;When the link is up there appears to be enough control data &n; *&t;crossing the control link to keep it open even if a long audio&n; *&t;piece is playing.&n; *&n; *&t;The Robust UDP support added in RealAudio 3.0 is supported, but due&n; *&t;to servers/clients not making great use of this has not been greatly&n; *&t;tested.  RealVideo (as used in the Real client version 4.0beta1) is&n; *&t;supported but again is not greatly tested (bandwidth requirements&n; *&t;appear to exceed that available at the sites supporting the protocol).&n; *&n; * Multiple Port Support&n; *&t;The helper can be made to handle up to MAX_MASQ_APP_PORTS (normally 12)&n; *&t;with the port numbers being defined at module load time.  The module&n; *&t;uses the symbol &quot;ports&quot; to define a list of monitored ports, which can&n; *&t;be specified on the insmod command line as&n; *&t;&t;ports=x1,x2,x3...&n; *&t;where x[n] are integer port numbers.  This option can be put into&n; *&t;/etc/conf.modules (or /etc/modules.conf depending on your config)&n; *&t;where modload will pick it up should you use modload to load your&n; *&t;modules.&n; *&n; * Fixes:&n; * &t;Juan Jose Ciarlante&t;:&t;Use control_add() for control chan&n; * &t;10/15/97 - Modifications to allow masquerading of RTSP connections as&n; *     &t;&t;well as PNA, which can potentially exist on the same port.&n; *&t;&t;Joe Rumsey &lt;ogre@real.com&gt;&n; *&t;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/ip_masq.h&gt;
multiline_comment|/*&n;#ifndef DEBUG_CONFIG_IP_MASQ_RAUDIO&n;#define DEBUG_CONFIG_IP_MASQ_RAUDIO 0&n;#endif&n;*/
DECL|macro|TOLOWER
mdefine_line|#define TOLOWER(c) (((c) &gt;= &squot;A&squot; &amp;&amp; (c) &lt;= &squot;Z&squot;) ? ((c) - &squot;A&squot; + &squot;a&squot;) : (c))
DECL|macro|ISDIGIT
mdefine_line|#define ISDIGIT(c) (((c) &gt;= &squot;0&squot;) &amp;&amp; ((c) &lt;= &squot;9&squot;))
DECL|struct|raudio_priv_data
r_struct
id|raudio_priv_data
(brace
multiline_comment|/* Associated data connection - setup but not used at present */
DECL|member|data_conn
r_struct
id|ip_masq
op_star
id|data_conn
suffix:semicolon
multiline_comment|/* UDP Error correction connection - setup but not used at present */
DECL|member|error_conn
r_struct
id|ip_masq
op_star
id|error_conn
suffix:semicolon
multiline_comment|/* Have we seen and performed setup */
DECL|member|seen_start
r_int
id|seen_start
suffix:semicolon
DECL|member|is_rtsp
r_int
id|is_rtsp
suffix:semicolon
)brace
suffix:semicolon
r_int
id|masq_rtsp_out
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
comma
r_struct
id|sk_buff
op_star
op_star
id|skb_p
comma
id|__u32
id|maddr
)paren
suffix:semicolon
multiline_comment|/* &n; * List of ports (up to MAX_MASQ_APP_PORTS) to be handled by helper&n; * First port is set to the default port.&n; */
DECL|variable|ports
r_int
id|ports
(braket
id|MAX_MASQ_APP_PORTS
)braket
op_assign
(brace
l_int|554
comma
l_int|7070
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* I rely on the trailing items being set to zero */
DECL|variable|masq_incarnations
r_struct
id|ip_masq_app
op_star
id|masq_incarnations
(braket
id|MAX_MASQ_APP_PORTS
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Debug level&n; */
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ports
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_MASQ_APP_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
r_static
r_int
DECL|function|masq_raudio_init_1
id|masq_raudio_init_1
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ms-&gt;app_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|raudio_priv_data
)paren
comma
id|GFP_ATOMIC
)paren
)paren
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;RealAudio: No memory for application data&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
r_struct
id|raudio_priv_data
op_star
id|priv
op_assign
(paren
r_struct
id|raudio_priv_data
op_star
)paren
id|ms-&gt;app_data
suffix:semicolon
id|priv-&gt;seen_start
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;data_conn
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;error_conn
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;is_rtsp
op_assign
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|masq_raudio_done_1
id|masq_raudio_done_1
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|ms-&gt;app_data
)paren
id|kfree_s
c_func
(paren
id|ms-&gt;app_data
comma
r_sizeof
(paren
r_struct
id|raudio_priv_data
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|masq_raudio_out
id|masq_raudio_out
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
comma
r_struct
id|sk_buff
op_star
op_star
id|skb_p
comma
id|__u32
id|maddr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|data
comma
op_star
id|data_limit
suffix:semicolon
r_struct
id|ip_masq
op_star
id|n_ms
suffix:semicolon
r_int
r_int
id|version
comma
id|msg_id
comma
id|msg_len
comma
id|udp_port
suffix:semicolon
r_struct
id|raudio_priv_data
op_star
id|priv
op_assign
(paren
r_struct
id|raudio_priv_data
op_star
)paren
id|ms-&gt;app_data
suffix:semicolon
multiline_comment|/* Everything running correctly already */
r_if
c_cond
(paren
id|priv
op_logical_and
id|priv-&gt;seen_start
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|priv
op_logical_and
id|priv-&gt;is_rtsp
)paren
(brace
r_return
id|masq_rtsp_out
c_func
(paren
id|mapp
comma
id|ms
comma
id|skb_p
comma
id|maddr
)paren
suffix:semicolon
)brace
id|skb
op_assign
op_star
id|skb_p
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
(braket
id|iph-&gt;ihl
op_star
l_int|4
)braket
)paren
suffix:semicolon
id|data
op_assign
(paren
r_char
op_star
)paren
op_amp
id|th
(braket
l_int|1
)braket
suffix:semicolon
id|data_limit
op_assign
id|skb-&gt;h.raw
op_plus
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;OPTIONS&quot;
comma
l_int|7
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;DESCRIBE&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: Detected RTSP connection&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* This is an RTSP client */
r_if
c_cond
(paren
id|priv
)paren
(brace
id|priv-&gt;is_rtsp
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|masq_rtsp_out
c_func
(paren
id|mapp
comma
id|ms
comma
id|skb_p
comma
id|maddr
)paren
suffix:semicolon
)brace
multiline_comment|/* Check to see if this is the first packet with protocol ID */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|data
comma
l_string|&quot;PNA&quot;
comma
l_int|3
)paren
)paren
(brace
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: not initial protocol packet - ignored&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|data
op_add_assign
l_int|3
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|version
comma
id|data
comma
l_int|2
)paren
suffix:semicolon
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: initial seen - protocol version %d&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|version
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv
)paren
id|priv-&gt;seen_start
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|version
)paren
op_ge
l_int|256
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;RealAudio: version (%d) not supported&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|version
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|data
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|data
op_plus
l_int|4
OL
id|data_limit
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|msg_id
comma
id|data
comma
l_int|2
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|msg_len
comma
id|data
comma
l_int|2
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|msg_id
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* The zero tag indicates the end of options */
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: packet end tag seen&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: msg %d - %d byte&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|msg_id
)paren
comma
id|ntohs
c_func
(paren
id|msg_len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|msg_id
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* The zero tag indicates the end of options */
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
id|data
suffix:semicolon
id|data
op_add_assign
id|ntohs
c_func
(paren
id|msg_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
OG
id|data_limit
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;RealAudio: Packet too short for data&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ntohs
c_func
(paren
id|msg_id
)paren
op_eq
l_int|1
)paren
op_logical_or
(paren
id|ntohs
c_func
(paren
id|msg_id
)paren
op_eq
l_int|7
)paren
)paren
(brace
multiline_comment|/* &n;&t;&t;&t; * MsgId == 1&n;&t;&t;&t; * Audio UDP data port on client&n;&t;&t;&t; *&n;&t;&t;&t; * MsgId == 7&n;&t;&t;&t; * Robust UDP error correction port number on client&n;&t;&t;&t; *&n;&t;&t;&t; * Since these messages are treated just the same, they&n;&t;&t;&t; * are bundled together here....&n;&t;&t;&t; */
id|memcpy
c_func
(paren
op_amp
id|udp_port
comma
id|p
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* &n;&t;&t;&t; * Sometimes a server sends a message 7 with a zero UDP port&n;&t;&t;&t; * Rather than do anything with this, just ignore it!&n;&t;&t;&t; */
r_if
c_cond
(paren
id|udp_port
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|n_ms
op_assign
id|ip_masq_new
c_func
(paren
id|IPPROTO_UDP
comma
id|maddr
comma
l_int|0
comma
id|ms-&gt;saddr
comma
id|udp_port
comma
id|ms-&gt;daddr
comma
l_int|0
comma
id|IP_MASQ_F_NO_DPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|ip_masq_listen
c_func
(paren
id|n_ms
)paren
suffix:semicolon
id|ip_masq_control_add
c_func
(paren
id|n_ms
comma
id|ms
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
op_amp
(paren
id|n_ms-&gt;mport
)paren
comma
l_int|2
)paren
suffix:semicolon
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: rewrote UDP port %d -&gt; %d in msg %d&bslash;n&quot;
comma
id|ntohs
c_func
(paren
id|udp_port
)paren
comma
id|ntohs
c_func
(paren
id|n_ms-&gt;mport
)paren
comma
id|ntohs
c_func
(paren
id|msg_id
)paren
)paren
suffix:semicolon
multiline_comment|/* Make ref in application data to data connection */
r_if
c_cond
(paren
id|priv
)paren
(brace
r_if
c_cond
(paren
id|ntohs
c_func
(paren
id|msg_id
)paren
op_eq
l_int|1
)paren
id|priv-&gt;data_conn
op_assign
id|n_ms
suffix:semicolon
r_else
id|priv-&gt;error_conn
op_assign
id|n_ms
suffix:semicolon
)brace
id|ip_masq_put
c_func
(paren
id|n_ms
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * masq_rtsp_out&n; *&n; * &n; */
r_int
DECL|function|masq_rtsp_out
id|masq_rtsp_out
(paren
r_struct
id|ip_masq_app
op_star
id|mapp
comma
r_struct
id|ip_masq
op_star
id|ms
comma
r_struct
id|sk_buff
op_star
op_star
id|skb_p
comma
id|__u32
id|maddr
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|th
suffix:semicolon
r_char
op_star
id|data
comma
op_star
id|data_limit
suffix:semicolon
r_struct
id|ip_masq
op_star
id|n_ms
comma
op_star
id|n_ms2
suffix:semicolon
r_int
r_int
id|udp_port
suffix:semicolon
r_struct
id|raudio_priv_data
op_star
id|priv
op_assign
(paren
r_struct
id|raudio_priv_data
op_star
)paren
id|ms-&gt;app_data
suffix:semicolon
r_const
r_char
op_star
id|srch
op_assign
l_string|&quot;transport:&quot;
suffix:semicolon
r_const
r_char
op_star
id|srchpos
op_assign
id|srch
suffix:semicolon
r_const
r_char
op_star
id|srchend
op_assign
id|srch
op_plus
id|strlen
c_func
(paren
id|srch
)paren
suffix:semicolon
r_int
id|state
op_assign
l_int|0
suffix:semicolon
r_char
id|firstport
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|firstportpos
op_assign
l_int|0
suffix:semicolon
r_char
id|secondport
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|secondportpos
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|portstart
op_assign
l_int|NULL
comma
op_star
id|portend
op_assign
l_int|NULL
suffix:semicolon
r_int
id|diff
suffix:semicolon
multiline_comment|/* Everything running correctly already */
r_if
c_cond
(paren
id|priv
op_logical_and
id|priv-&gt;seen_start
)paren
r_return
l_int|0
suffix:semicolon
id|skb
op_assign
op_star
id|skb_p
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|iph
)paren
(braket
id|iph-&gt;ihl
op_star
l_int|4
)braket
)paren
suffix:semicolon
id|data
op_assign
(paren
r_char
op_star
)paren
op_amp
id|th
(braket
l_int|1
)braket
suffix:semicolon
id|data_limit
op_assign
id|skb-&gt;h.raw
op_plus
id|skb-&gt;len
suffix:semicolon
id|firstport
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|secondport
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|data
OL
id|data_limit
op_logical_and
id|state
op_ge
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|TOLOWER
c_func
(paren
op_star
id|data
)paren
op_eq
op_star
id|srchpos
)paren
(brace
id|srchpos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|srchpos
op_eq
id|srchend
)paren
(brace
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;Found string %s in message&bslash;n&quot;
comma
id|srch
)paren
suffix:semicolon
id|state
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|1
)paren
(brace
id|srch
op_assign
l_string|&quot;client_port&quot;
suffix:semicolon
id|srchpos
op_assign
id|srch
suffix:semicolon
id|srchend
op_assign
id|srch
op_plus
id|strlen
c_func
(paren
id|srch
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|srchpos
op_assign
id|srch
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;=&squot;
)paren
(brace
id|state
op_assign
l_int|3
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|ISDIGIT
c_func
(paren
op_star
id|data
)paren
)paren
(brace
id|portstart
op_assign
id|data
suffix:semicolon
id|firstportpos
op_assign
l_int|0
suffix:semicolon
id|firstport
(braket
id|firstportpos
op_increment
)braket
op_assign
op_star
id|data
suffix:semicolon
id|state
op_assign
l_int|4
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|state
op_assign
l_int|5
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;;&squot;
)paren
(brace
id|portend
op_assign
id|data
op_minus
l_int|1
suffix:semicolon
id|firstport
(braket
id|firstportpos
)braket
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ISDIGIT
c_func
(paren
op_star
id|data
)paren
)paren
(brace
id|firstport
(braket
id|firstportpos
op_increment
)braket
op_assign
op_star
id|data
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot; &squot;
op_logical_and
op_star
id|data
op_ne
l_char|&squot;&bslash;t&squot;
)paren
(brace
multiline_comment|/* This is a badly formed RTSP message, let&squot;s bail out */
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;Badly formed RTSP Message&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
id|ISDIGIT
c_func
(paren
op_star
id|data
)paren
)paren
(brace
id|secondportpos
op_assign
l_int|0
suffix:semicolon
id|secondport
(braket
id|secondportpos
op_increment
)braket
op_assign
op_star
id|data
suffix:semicolon
id|state
op_assign
l_int|6
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;;&squot;
)paren
(brace
id|portend
op_assign
id|data
op_minus
l_int|1
suffix:semicolon
id|secondport
(braket
id|secondportpos
)braket
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
op_star
id|data
op_eq
l_char|&squot;;&squot;
)paren
(brace
id|portend
op_assign
id|data
op_minus
l_int|1
suffix:semicolon
id|secondport
(braket
id|secondportpos
)braket
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ISDIGIT
c_func
(paren
op_star
id|data
)paren
)paren
(brace
id|secondport
(braket
id|secondportpos
op_increment
)braket
op_assign
op_star
id|data
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|data
op_ne
l_char|&squot; &squot;
op_logical_and
op_star
id|data
op_ne
l_char|&squot;&bslash;t&squot;
)paren
(brace
multiline_comment|/* This is a badly formed RTSP message, let&squot;s bail out */
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;Badly formed RTSP Message&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|data
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state
op_ge
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|firstportpos
OG
l_int|0
)paren
(brace
r_char
id|newbuf
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* xxxxx-xxxxx&bslash;0 */
r_char
op_star
id|tmpptr
suffix:semicolon
id|udp_port
op_assign
id|htons
c_func
(paren
id|simple_strtoul
c_func
(paren
id|firstport
comma
op_amp
id|tmpptr
comma
l_int|10
)paren
)paren
suffix:semicolon
id|n_ms
op_assign
id|ip_masq_new
c_func
(paren
id|IPPROTO_UDP
comma
id|maddr
comma
l_int|0
comma
id|ms-&gt;saddr
comma
id|udp_port
comma
id|ms-&gt;daddr
comma
l_int|0
comma
id|IP_MASQ_F_NO_DPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|ip_masq_listen
c_func
(paren
id|n_ms
)paren
suffix:semicolon
id|ip_masq_control_add
c_func
(paren
id|n_ms
comma
id|ms
)paren
suffix:semicolon
r_if
c_cond
(paren
id|secondportpos
OG
l_int|0
)paren
(brace
id|udp_port
op_assign
id|htons
c_func
(paren
id|simple_strtoul
c_func
(paren
id|secondport
comma
op_amp
id|tmpptr
comma
l_int|10
)paren
)paren
suffix:semicolon
id|n_ms2
op_assign
id|ip_masq_new
c_func
(paren
id|IPPROTO_UDP
comma
id|maddr
comma
l_int|0
comma
id|ms-&gt;saddr
comma
id|udp_port
comma
id|ms-&gt;daddr
comma
l_int|0
comma
id|IP_MASQ_F_NO_DPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms2
op_eq
l_int|NULL
)paren
(brace
id|ip_masq_put
c_func
(paren
id|n_ms
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ip_masq_listen
c_func
(paren
id|n_ms2
)paren
suffix:semicolon
id|ip_masq_control_add
c_func
(paren
id|n_ms2
comma
id|ms
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|newbuf
comma
l_string|&quot;%d-%d&quot;
comma
id|ntohs
c_func
(paren
id|n_ms-&gt;mport
)paren
comma
id|ntohs
c_func
(paren
id|n_ms2-&gt;mport
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|sprintf
c_func
(paren
id|newbuf
comma
l_string|&quot;%d&quot;
comma
id|ntohs
c_func
(paren
id|n_ms-&gt;mport
)paren
)paren
suffix:semicolon
id|n_ms2
op_assign
l_int|NULL
suffix:semicolon
)brace
op_star
id|skb_p
op_assign
id|ip_masq_skb_replace
c_func
(paren
id|skb
comma
id|GFP_ATOMIC
comma
id|portstart
comma
id|portend
op_minus
id|portstart
op_plus
l_int|1
comma
id|newbuf
comma
id|strlen
c_func
(paren
id|newbuf
)paren
)paren
suffix:semicolon
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RTSP: rewrote client_port to %s&bslash;n&quot;
comma
id|newbuf
)paren
suffix:semicolon
id|diff
op_assign
id|strlen
c_func
(paren
id|newbuf
)paren
op_minus
(paren
id|portend
op_minus
id|portstart
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv
)paren
(brace
id|priv-&gt;seen_start
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|n_ms
)paren
(brace
id|priv-&gt;data_conn
op_assign
id|n_ms
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n_ms2
)paren
(brace
id|priv-&gt;error_conn
op_assign
id|n_ms2
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Release tunnels&n;&t; */
r_if
c_cond
(paren
id|n_ms
)paren
id|ip_masq_put
c_func
(paren
id|n_ms
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n_ms2
)paren
id|ip_masq_put
c_func
(paren
id|n_ms2
)paren
suffix:semicolon
r_return
id|diff
suffix:semicolon
)brace
DECL|variable|ip_masq_raudio
r_struct
id|ip_masq_app
id|ip_masq_raudio
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* next */
l_string|&quot;RealAudio&quot;
comma
multiline_comment|/* name */
l_int|0
comma
multiline_comment|/* type */
l_int|0
comma
multiline_comment|/* n_attach */
id|masq_raudio_init_1
comma
multiline_comment|/* ip_masq_init_1 */
id|masq_raudio_done_1
comma
multiline_comment|/* ip_masq_done_1 */
id|masq_raudio_out
comma
multiline_comment|/* pkt_out */
l_int|NULL
multiline_comment|/* pkt_in */
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;ip_masq_raudio initialization&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|ip_masq_raudio_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|MAX_MASQ_APP_PORTS
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
(paren
id|masq_incarnations
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ip_masq_app
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|masq_incarnations
(braket
id|i
)braket
comma
op_amp
id|ip_masq_raudio
comma
r_sizeof
(paren
r_struct
id|ip_masq_app
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|j
op_assign
id|register_ip_masq_app
c_func
(paren
id|masq_incarnations
(braket
id|i
)braket
comma
id|IPPROTO_TCP
comma
id|ports
(braket
id|i
)braket
)paren
)paren
)paren
(brace
r_return
id|j
suffix:semicolon
)brace
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: loaded support on port[%d] = %d&bslash;n&quot;
comma
id|i
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* To be safe, force the incarnation table entry to NULL */
id|masq_incarnations
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * &t;ip_masq_raudio fin.&n; */
DECL|function|ip_masq_raudio_done
r_int
id|ip_masq_raudio_done
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
id|k
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|MAX_MASQ_APP_PORTS
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|masq_incarnations
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
(paren
id|j
op_assign
id|unregister_ip_masq_app
c_func
(paren
id|masq_incarnations
(braket
id|i
)braket
)paren
)paren
)paren
(brace
id|k
op_assign
id|j
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|masq_incarnations
(braket
id|i
)braket
)paren
suffix:semicolon
id|masq_incarnations
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|IP_MASQ_DEBUG
c_func
(paren
l_int|1
op_minus
id|debug
comma
l_string|&quot;RealAudio: unloaded support on port[%d] = %d&bslash;n&quot;
comma
id|i
comma
id|ports
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|k
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_masq_raudio_init
c_func
(paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ip_masq_raudio_done
c_func
(paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip_masq_raudio: can&squot;t remove module&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
