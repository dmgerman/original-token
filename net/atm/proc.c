multiline_comment|/* net/atm/proc.c - ATM /proc interface */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
multiline_comment|/*&n; * The mechanism used here isn&squot;t designed for speed but rather for convenience&n; * of implementation. We only return one entry per read system call, so we can&n; * be reasonably sure not to overrun the page and race conditions may lead to&n; * the addition or omission of some lines but never to any corruption of a&n; * line&squot;s internal structure.&n; *&n; * Making the whole thing slightly more efficient is left as an exercise to the&n; * reader. (Suggestions: wrapper which loops to get several entries per system&n; * call; or make --left slightly more clever to avoid O(n^2) characteristics.)&n; * I find it fast enough on my unloaded 266 MHz Pentium 2 :-)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt; /* for EXPORT_SYMBOL */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/atmclip.h&gt;
macro_line|#include &lt;linux/atmarp.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/init.h&gt; /* for __init */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/param.h&gt; /* for HZ */
macro_line|#include &quot;resources.h&quot;
macro_line|#include &quot;common.h&quot; /* atm_proc_init prototype */
macro_line|#include &quot;signaling.h&quot; /* to get sigd - ugly too */
macro_line|#ifdef CONFIG_ATM_CLIP
macro_line|#include &lt;net/atmclip.h&gt;
macro_line|#include &quot;ipcommon.h&quot;
r_extern
r_void
id|clip_push
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
macro_line|#include &quot;lec.h&quot;
macro_line|#include &quot;lec_arpc.h&quot;
r_extern
r_struct
id|atm_lane_ops
id|atm_lane_ops
suffix:semicolon
multiline_comment|/* in common.c */
macro_line|#endif
r_static
id|ssize_t
id|proc_dev_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
r_static
id|ssize_t
id|proc_spec_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
suffix:semicolon
DECL|variable|proc_dev_atm_operations
r_static
r_struct
id|file_operations
id|proc_dev_atm_operations
op_assign
(brace
id|read
suffix:colon
id|proc_dev_atm_read
comma
)brace
suffix:semicolon
DECL|variable|proc_spec_atm_operations
r_static
r_struct
id|file_operations
id|proc_spec_atm_operations
op_assign
(brace
id|read
suffix:colon
id|proc_spec_atm_read
comma
)brace
suffix:semicolon
DECL|function|add_stats
r_static
r_void
id|add_stats
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|aal
comma
r_const
r_struct
id|k_atm_aal_stats
op_star
id|stats
)paren
(brace
id|sprintf
c_func
(paren
id|strchr
c_func
(paren
id|buf
comma
l_int|0
)paren
comma
l_string|&quot;%s ( %d %d %d %d %d )&quot;
comma
id|aal
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;tx
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;tx_err
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx_err
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|stats-&gt;rx_drop
)paren
)paren
suffix:semicolon
)brace
DECL|function|dev_info
r_static
r_void
id|dev_info
c_func
(paren
r_const
r_struct
id|atm_dev
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|off
comma
id|i
suffix:semicolon
id|off
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%3d %-8s&quot;
comma
id|dev-&gt;number
comma
id|dev-&gt;type
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ESI_LEN
suffix:semicolon
id|i
op_increment
)paren
id|off
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;%02x&quot;
comma
id|dev-&gt;esi
(braket
id|i
)braket
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|add_stats
c_func
(paren
id|buf
comma
l_string|&quot;0&quot;
comma
op_amp
id|dev-&gt;stats.aal0
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|add_stats
c_func
(paren
id|buf
comma
l_string|&quot;5&quot;
comma
op_amp
id|dev-&gt;stats.aal5
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ATM_CLIP
DECL|function|svc_addr
r_static
r_int
id|svc_addr
c_func
(paren
r_char
op_star
id|buf
comma
r_struct
id|sockaddr_atmsvc
op_star
id|addr
)paren
(brace
r_static
r_int
id|code
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|10
comma
l_int|6
comma
l_int|1
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
id|e164
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|8
comma
l_int|4
comma
l_int|6
comma
l_int|1
comma
l_int|0
)brace
suffix:semicolon
r_int
op_star
id|fields
suffix:semicolon
r_int
id|len
comma
id|i
comma
id|j
comma
id|pos
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|addr-&gt;sas_addr.pub
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
id|addr-&gt;sas_addr.pub
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|addr-&gt;sas_addr.pub
)paren
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
op_star
id|addr-&gt;sas_addr.prv
)paren
(brace
op_star
id|buf
op_increment
op_assign
l_char|&squot;+&squot;
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
op_star
id|addr-&gt;sas_addr.prv
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
l_string|&quot;(none)&quot;
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|addr-&gt;sas_addr.prv
)paren
(brace
id|len
op_add_assign
l_int|44
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
id|fields
op_assign
op_star
id|addr-&gt;sas_addr.prv
op_eq
id|ATM_AFI_E164
ques
c_cond
id|e164
suffix:colon
id|code
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|fields
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
id|fields
(braket
id|i
)braket
suffix:semicolon
id|j
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%02X&quot;
comma
id|addr-&gt;sas_addr.prv
(braket
id|pos
op_increment
)braket
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fields
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_star
id|buf
op_increment
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|atmarp_info
r_static
r_void
id|atmarp_info
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|atmarp_entry
op_star
id|entry
comma
r_struct
id|clip_vcc
op_star
id|clip_vcc
comma
r_char
op_star
id|buf
)paren
(brace
r_int
r_char
op_star
id|ip
suffix:semicolon
r_int
id|svc
comma
id|off
comma
id|ip_len
suffix:semicolon
id|svc
op_assign
op_logical_neg
id|clip_vcc
op_logical_or
id|clip_vcc-&gt;vcc-&gt;family
op_eq
id|AF_ATMSVC
suffix:semicolon
id|off
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%-6s%-4s%-4s%5ld &quot;
comma
id|dev-&gt;name
comma
id|svc
ques
c_cond
l_string|&quot;SVC&quot;
suffix:colon
l_string|&quot;PVC&quot;
comma
op_logical_neg
id|clip_vcc
op_logical_or
id|clip_vcc-&gt;encap
ques
c_cond
l_string|&quot;LLC&quot;
suffix:colon
l_string|&quot;NULL&quot;
comma
(paren
id|jiffies
op_minus
(paren
id|clip_vcc
ques
c_cond
id|clip_vcc-&gt;last_use
suffix:colon
id|entry-&gt;neigh-&gt;used
)paren
)paren
op_div
id|HZ
)paren
suffix:semicolon
id|ip
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|entry-&gt;ip
suffix:semicolon
id|ip_len
op_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;%d.%d.%d.%d&quot;
comma
id|ip
(braket
l_int|0
)braket
comma
id|ip
(braket
l_int|1
)braket
comma
id|ip
(braket
l_int|2
)braket
comma
id|ip
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|off
op_add_assign
id|ip_len
suffix:semicolon
r_while
c_loop
(paren
id|ip_len
op_increment
OL
l_int|16
)paren
id|buf
(braket
id|off
op_increment
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clip_vcc
)paren
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|entry-&gt;expires
)paren
)paren
id|strcpy
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;(resolving)&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;(expired, ref %d)&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|entry-&gt;neigh-&gt;refcnt
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|svc
)paren
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;%d.%d.%d&bslash;n&quot;
comma
id|clip_vcc-&gt;vcc-&gt;dev-&gt;number
comma
id|clip_vcc-&gt;vcc-&gt;vpi
comma
id|clip_vcc-&gt;vcc-&gt;vci
)paren
suffix:semicolon
r_else
(brace
id|off
op_add_assign
id|svc_addr
c_func
(paren
id|buf
op_plus
id|off
comma
op_amp
id|clip_vcc-&gt;vcc-&gt;remote
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|pvc_info
r_static
r_void
id|pvc_info
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_char
op_star
id|buf
)paren
(brace
r_static
r_const
r_char
op_star
id|class_name
(braket
)braket
op_assign
(brace
l_string|&quot;off&quot;
comma
l_string|&quot;UBR&quot;
comma
l_string|&quot;CBR&quot;
comma
l_string|&quot;VBR&quot;
comma
l_string|&quot;ABR&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
id|aal_name
(braket
)braket
op_assign
(brace
l_string|&quot;---&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3/4&quot;
comma
multiline_comment|/*  0- 3 */
l_string|&quot;???&quot;
comma
l_string|&quot;5&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
multiline_comment|/*  4- 7 */
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
comma
multiline_comment|/*  8-11 */
l_string|&quot;???&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;???&quot;
comma
l_string|&quot;???&quot;
)brace
suffix:semicolon
multiline_comment|/* 12-15 */
r_int
id|off
suffix:semicolon
id|off
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%3d %3d %5d %-3s %7d %-5s %7d %-6s&quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
comma
id|vcc-&gt;qos.aal
op_ge
r_sizeof
(paren
id|aal_name
)paren
op_div
r_sizeof
(paren
id|aal_name
(braket
l_int|0
)braket
)paren
ques
c_cond
l_string|&quot;err&quot;
suffix:colon
id|aal_name
(braket
id|vcc-&gt;qos.aal
)braket
comma
id|vcc-&gt;qos.rxtp.min_pcr
comma
id|class_name
(braket
id|vcc-&gt;qos.rxtp.traffic_class
)braket
comma
id|vcc-&gt;qos.txtp.min_pcr
comma
id|class_name
(braket
id|vcc-&gt;qos.txtp.traffic_class
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ATM_CLIP
r_if
c_cond
(paren
id|vcc-&gt;push
op_eq
id|clip_push
)paren
(brace
r_struct
id|clip_vcc
op_star
id|clip_vcc
op_assign
id|CLIP_VCC
c_func
(paren
id|vcc
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|dev
op_assign
id|clip_vcc-&gt;entry
ques
c_cond
id|clip_vcc-&gt;entry-&gt;neigh-&gt;dev
suffix:colon
l_int|NULL
suffix:semicolon
id|off
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;CLIP, Itf:%s, Encap:&quot;
comma
id|dev
ques
c_cond
id|dev-&gt;name
suffix:colon
l_string|&quot;none?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clip_vcc-&gt;encap
)paren
id|off
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;LLC/SNAP&quot;
)paren
suffix:semicolon
r_else
id|off
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;None&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|strcpy
c_func
(paren
id|buf
op_plus
id|off
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|vcc_state
r_static
r_const
r_char
op_star
id|vcc_state
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
(brace
r_static
r_const
r_char
op_star
id|map
(braket
)braket
op_assign
(brace
id|ATM_VS2TXT_MAP
)brace
suffix:semicolon
r_return
id|map
(braket
id|ATM_VF2VS
c_func
(paren
id|vcc-&gt;flags
)paren
)braket
suffix:semicolon
)brace
DECL|function|vc_info
r_static
r_void
id|vc_info
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|here
suffix:semicolon
id|here
op_assign
id|buf
op_plus
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%p &quot;
comma
id|vcc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev
)paren
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;Unassigned    &quot;
)paren
suffix:semicolon
r_else
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;%3d %3d %5d &quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|vcc-&gt;family
)paren
(brace
r_case
id|AF_ATMPVC
suffix:colon
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;PVC&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AF_ATMSVC
suffix:colon
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;SVC&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;%3d&quot;
comma
id|vcc-&gt;family
)paren
suffix:semicolon
)brace
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot; %04x  %5d %7d/%7d %7d/%7d&bslash;n&quot;
comma
id|vcc-&gt;flags.bits
comma
id|vcc-&gt;reply
comma
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;tx_inuse
)paren
comma
id|vcc-&gt;sk-&gt;sndbuf
comma
id|atomic_read
c_func
(paren
op_amp
id|vcc-&gt;rx_inuse
)paren
comma
id|vcc-&gt;sk-&gt;rcvbuf
)paren
suffix:semicolon
)brace
DECL|function|svc_info
r_static
r_void
id|svc_info
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|here
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vcc-&gt;dev
)paren
id|sprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
r_void
op_star
)paren
op_eq
l_int|4
ques
c_cond
l_string|&quot;N/A@%p%10s&quot;
suffix:colon
l_string|&quot;N/A@%p%2s&quot;
comma
id|vcc
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%3d %3d %5d         &quot;
comma
id|vcc-&gt;dev-&gt;number
comma
id|vcc-&gt;vpi
comma
id|vcc-&gt;vci
)paren
suffix:semicolon
id|here
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;%-10s &quot;
comma
id|vcc_state
c_func
(paren
id|vcc
)paren
)paren
suffix:semicolon
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;%s%s&quot;
comma
id|vcc-&gt;remote.sas_addr.pub
comma
op_star
id|vcc-&gt;remote.sas_addr.pub
op_logical_and
op_star
id|vcc-&gt;remote.sas_addr.prv
ques
c_cond
l_string|&quot;+&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|vcc-&gt;remote.sas_addr.prv
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ATM_ESA_LEN
suffix:semicolon
id|i
op_increment
)paren
id|here
op_add_assign
id|sprintf
c_func
(paren
id|here
comma
l_string|&quot;%02x&quot;
comma
id|vcc-&gt;remote.sas_addr.prv
(braket
id|i
)braket
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|here
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
r_static
r_char
op_star
DECL|function|lec_arp_get_status_string
id|lec_arp_get_status_string
c_func
(paren
r_int
r_char
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|ESI_UNKNOWN
suffix:colon
r_return
l_string|&quot;ESI_UNKNOWN       &quot;
suffix:semicolon
r_case
id|ESI_ARP_PENDING
suffix:colon
r_return
l_string|&quot;ESI_ARP_PENDING   &quot;
suffix:semicolon
r_case
id|ESI_VC_PENDING
suffix:colon
r_return
l_string|&quot;ESI_VC_PENDING    &quot;
suffix:semicolon
r_case
id|ESI_FLUSH_PENDING
suffix:colon
r_return
l_string|&quot;ESI_FLUSH_PENDING &quot;
suffix:semicolon
r_case
id|ESI_FORWARD_DIRECT
suffix:colon
r_return
l_string|&quot;ESI_FORWARD_DIRECT&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;&lt;Unknown&gt;         &quot;
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|lec_info
id|lec_info
c_func
(paren
r_struct
id|lec_arp_table
op_star
id|entry
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|j
comma
id|offset
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ETH_ALEN
suffix:semicolon
id|j
op_increment
)paren
(brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;%2.2x&quot;
comma
l_int|0xff
op_amp
id|entry-&gt;mac_addr
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ATM_ESA_LEN
suffix:semicolon
id|j
op_increment
)paren
(brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;%2.2x&quot;
comma
l_int|0xff
op_amp
id|entry-&gt;atm_addr
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot; %s %4.4x&quot;
comma
id|lec_arp_get_status_string
c_func
(paren
id|entry-&gt;status
)paren
comma
id|entry-&gt;flags
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;vcc
)paren
(brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;%3d %3d &quot;
comma
id|entry-&gt;vcc-&gt;vpi
comma
id|entry-&gt;vcc-&gt;vci
)paren
suffix:semicolon
)brace
r_else
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;        &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;recv_vcc
)paren
(brace
id|offset
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;     %3d %3d&quot;
comma
id|entry-&gt;recv_vcc-&gt;vpi
comma
id|entry-&gt;recv_vcc-&gt;vci
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
op_plus
id|offset
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|atm_devices_info
r_static
r_int
id|atm_devices_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_int
id|left
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Itf Type    ESI/&bslash;&quot;MAC&bslash;&quot;addr &quot;
l_string|&quot;AAL(TX,err,RX,err,drop) ...&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|left
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|atm_devs
suffix:semicolon
id|dev
op_logical_and
id|left
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
id|left
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
id|dev_info
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME: it isn&squot;t safe to walk the VCC list without turning off interrupts.&n; * What is really needed is some lock on the devices. Ditto for ATMARP.&n; */
DECL|function|atm_pvc_info
r_static
r_int
id|atm_pvc_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|left
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Itf VPI VCI   AAL RX(PCR,Class) &quot;
l_string|&quot;TX(PCR,Class)&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|left
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|atm_devs
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
r_for
c_loop
(paren
id|vcc
op_assign
id|dev-&gt;vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
r_if
c_cond
(paren
id|vcc-&gt;family
op_eq
id|PF_ATMPVC
op_logical_and
id|vcc-&gt;dev
op_logical_and
op_logical_neg
id|left
op_decrement
)paren
(brace
id|pvc_info
c_func
(paren
id|vcc
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_vc_info
r_static
r_int
id|atm_vc_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|left
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
r_void
op_star
)paren
op_eq
l_int|4
ques
c_cond
l_string|&quot;%-8s%s&quot;
suffix:colon
l_string|&quot;%-16s%s&quot;
comma
l_string|&quot;Address&quot;
comma
l_string|&quot; Itf VPI VCI   Fam Flags Reply Send buffer&quot;
l_string|&quot;     Recv buffer&bslash;n&quot;
)paren
suffix:semicolon
id|left
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|atm_devs
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
r_for
c_loop
(paren
id|vcc
op_assign
id|dev-&gt;vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|left
op_decrement
)paren
(brace
id|vc_info
c_func
(paren
id|vcc
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|vcc
op_assign
id|nodev_vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|left
op_decrement
)paren
(brace
id|vc_info
c_func
(paren
id|vcc
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atm_svc_info
r_static
r_int
id|atm_svc_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
r_int
id|left
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Itf VPI VCI           State      Remote&bslash;n&quot;
)paren
suffix:semicolon
id|left
op_assign
id|pos
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|atm_devs
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
r_for
c_loop
(paren
id|vcc
op_assign
id|dev-&gt;vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
r_if
c_cond
(paren
id|vcc-&gt;family
op_eq
id|PF_ATMSVC
op_logical_and
op_logical_neg
id|left
op_decrement
)paren
(brace
id|svc_info
c_func
(paren
id|vcc
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|vcc
op_assign
id|nodev_vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
r_if
c_cond
(paren
id|vcc-&gt;family
op_eq
id|PF_ATMSVC
op_logical_and
op_logical_neg
id|left
op_decrement
)paren
(brace
id|svc_info
c_func
(paren
id|vcc
comma
id|buf
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ATM_CLIP
DECL|function|atm_arp_info
r_static
r_int
id|atm_arp_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|neighbour
op_star
id|n
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;IPitf TypeEncp Idle IP address      &quot;
l_string|&quot;ATM address&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|count
op_assign
id|pos
suffix:semicolon
id|read_lock_bh
c_func
(paren
op_amp
id|clip_tbl.lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|NEIGH_HASHMASK
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|n
op_assign
id|clip_tbl.hash_buckets
(braket
id|i
)braket
suffix:semicolon
id|n
suffix:semicolon
id|n
op_assign
id|n-&gt;next
)paren
(brace
r_struct
id|atmarp_entry
op_star
id|entry
op_assign
id|NEIGH2ENTRY
c_func
(paren
id|n
)paren
suffix:semicolon
r_struct
id|clip_vcc
op_star
id|vcc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;vccs
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|atmarp_info
c_func
(paren
id|n-&gt;dev
comma
id|entry
comma
l_int|NULL
comma
id|buf
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|clip_tbl.lock
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|vcc
op_assign
id|entry-&gt;vccs
suffix:semicolon
id|vcc
suffix:semicolon
id|vcc
op_assign
id|vcc-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|atmarp_info
c_func
(paren
id|n-&gt;dev
comma
id|entry
comma
id|vcc
comma
id|buf
)paren
suffix:semicolon
id|read_unlock_bh
c_func
(paren
op_amp
id|clip_tbl.lock
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
id|read_unlock_bh
c_func
(paren
op_amp
id|clip_tbl.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
DECL|function|atm_lec_info
r_static
r_int
id|atm_lec_info
c_func
(paren
id|loff_t
id|pos
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|lec_priv
op_star
id|priv
suffix:semicolon
r_struct
id|lec_arp_table
op_star
id|entry
suffix:semicolon
r_int
id|i
comma
id|count
comma
id|d
comma
id|e
suffix:semicolon
r_struct
id|net_device
op_star
op_star
id|dev_lec
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pos
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Itf  MAC          ATM destination&quot;
l_string|&quot;                          Status            Flags &quot;
l_string|&quot;VPI/VCI Recv VPI/VCI&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atm_lane_ops.get_lecs
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* the lane module is not there yet */
r_else
id|dev_lec
op_assign
id|atm_lane_ops
dot
id|get_lecs
c_func
(paren
)paren
suffix:semicolon
id|count
op_assign
id|pos
suffix:semicolon
r_for
c_loop
(paren
id|d
op_assign
l_int|0
suffix:semicolon
id|d
OL
id|MAX_LEC_ITF
suffix:semicolon
id|d
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev_lec
(braket
id|d
)braket
op_logical_or
op_logical_neg
(paren
id|priv
op_assign
(paren
r_struct
id|lec_priv
op_star
)paren
id|dev_lec
(braket
id|d
)braket
op_member_access_from_pointer
id|priv
)paren
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|LEC_ARP_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
id|priv-&gt;lec_arp_tables
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|e
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s &quot;
comma
id|dev_lec
(braket
id|d
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|lec_info
c_func
(paren
id|entry
comma
id|buf
op_plus
id|e
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|entry
op_assign
id|priv-&gt;lec_arp_empty_ones
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|e
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s &quot;
comma
id|dev_lec
(braket
id|d
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|lec_info
c_func
(paren
id|entry
comma
id|buf
op_plus
id|e
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|entry
op_assign
id|priv-&gt;lec_no_forward
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|e
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s &quot;
comma
id|dev_lec
(braket
id|d
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|lec_info
c_func
(paren
id|entry
comma
id|buf
op_plus
id|e
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|entry
op_assign
id|priv-&gt;mcast_fwds
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|count
)paren
r_continue
suffix:semicolon
id|e
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s &quot;
comma
id|dev_lec
(braket
id|d
)braket
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
id|lec_info
c_func
(paren
id|entry
comma
id|buf
op_plus
id|e
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|proc_dev_atm_read
r_static
id|ssize_t
id|proc_dev_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|atm_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_int
id|length
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
(paren
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;u.generic_ip
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;ops-&gt;proc_read
)paren
id|length
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
(brace
id|length
op_assign
id|dev-&gt;ops
op_member_access_from_pointer
id|proc_read
c_func
(paren
id|dev
comma
id|pos
comma
(paren
r_char
op_star
)paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|count
)paren
id|length
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|page
comma
id|length
)paren
)paren
id|length
op_assign
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|proc_spec_atm_read
r_static
id|ssize_t
id|proc_spec_atm_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_int
id|length
suffix:semicolon
r_int
(paren
op_star
id|info
)paren
(paren
id|loff_t
comma
r_char
op_star
)paren
suffix:semicolon
id|info
op_assign
(paren
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;u.generic_ip
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|length
op_assign
(paren
op_star
id|info
)paren
(paren
op_star
id|pos
comma
(paren
r_char
op_star
)paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|count
)paren
id|length
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|page
comma
id|length
)paren
)paren
id|length
op_assign
op_minus
id|EFAULT
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|variable|atm_proc_root
r_struct
id|proc_dir_entry
op_star
id|atm_proc_root
suffix:semicolon
DECL|variable|atm_proc_root
id|EXPORT_SYMBOL
c_func
(paren
id|atm_proc_root
)paren
suffix:semicolon
DECL|function|atm_proc_dev_register
r_int
id|atm_proc_dev_register
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
r_int
id|digits
comma
id|num
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|digits
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
id|dev-&gt;number
suffix:semicolon
id|num
suffix:semicolon
id|num
op_div_assign
l_int|10
)paren
id|digits
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|digits
)paren
id|digits
op_increment
suffix:semicolon
id|dev-&gt;proc_name
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|dev-&gt;type
)paren
op_plus
id|digits
op_plus
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;proc_name
)paren
r_goto
id|fail1
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;proc_name
comma
l_string|&quot;%s:%d&quot;
comma
id|dev-&gt;type
comma
id|dev-&gt;number
)paren
suffix:semicolon
id|dev-&gt;proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|dev-&gt;proc_name
comma
l_int|0
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;proc_entry
)paren
r_goto
id|fail0
suffix:semicolon
id|dev-&gt;proc_entry-&gt;data
op_assign
id|dev
suffix:semicolon
id|dev-&gt;proc_entry-&gt;proc_fops
op_assign
op_amp
id|proc_dev_atm_operations
suffix:semicolon
id|dev-&gt;proc_entry-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;proc_entry
)paren
suffix:semicolon
id|fail0
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;proc_name
)paren
suffix:semicolon
id|fail1
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|atm_proc_dev_deregister
r_void
id|atm_proc_dev_deregister
c_func
(paren
r_struct
id|atm_dev
op_star
id|dev
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|dev-&gt;proc_name
comma
id|atm_proc_root
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;proc_name
)paren
suffix:semicolon
)brace
DECL|macro|CREATE_ENTRY
mdefine_line|#define CREATE_ENTRY(name) &bslash;&n;    name = create_proc_entry(#name,0,atm_proc_root); &bslash;&n;    if (!name) goto cleanup; &bslash;&n;    name-&gt;data = atm_##name##_info; &bslash;&n;    name-&gt;proc_fops = &amp;proc_spec_atm_operations; &bslash;&n;    name-&gt;owner = THIS_MODULE
DECL|function|atm_proc_init
r_int
id|__init
id|atm_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|devices
op_assign
l_int|NULL
comma
op_star
id|pvc
op_assign
l_int|NULL
comma
op_star
id|svc
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|arp
op_assign
l_int|NULL
comma
op_star
id|lec
op_assign
l_int|NULL
comma
op_star
id|vc
op_assign
l_int|NULL
suffix:semicolon
id|atm_proc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net/atm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atm_proc_root
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|CREATE_ENTRY
c_func
(paren
id|devices
)paren
suffix:semicolon
id|CREATE_ENTRY
c_func
(paren
id|pvc
)paren
suffix:semicolon
id|CREATE_ENTRY
c_func
(paren
id|svc
)paren
suffix:semicolon
id|CREATE_ENTRY
c_func
(paren
id|vc
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ATM_CLIP
id|CREATE_ENTRY
c_func
(paren
id|arp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
id|CREATE_ENTRY
c_func
(paren
id|lec
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|devices
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;devices&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pvc
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;pvc&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|svc
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;svc&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arp
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;arp&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lec
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;lec&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vc
)paren
id|remove_proc_entry
c_func
(paren
l_string|&quot;vc&quot;
comma
id|atm_proc_root
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/atm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
eof
