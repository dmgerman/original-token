macro_line|#ifndef _LINUX_DN_H
DECL|macro|_LINUX_DN_H
mdefine_line|#define _LINUX_DN_H
multiline_comment|/*&n;&n;&t;DECnet Data Structures and Constants&n;&n;*/
multiline_comment|/* &n; * DNPROTO_NSP can&squot;t be the same as SOL_SOCKET, &n; * so increment each by one (compared to ULTRIX)&n; */
DECL|macro|DNPROTO_NSP
mdefine_line|#define DNPROTO_NSP     2                       /* NSP protocol number       */
DECL|macro|DNPROTO_ROU
mdefine_line|#define DNPROTO_ROU     3                       /* Routing protocol number   */
DECL|macro|DNPROTO_NML
mdefine_line|#define DNPROTO_NML     4                       /* Net mgt protocol number   */
DECL|macro|DNPROTO_EVL
mdefine_line|#define DNPROTO_EVL     5                       /* Evl protocol number (usr) */
DECL|macro|DNPROTO_EVR
mdefine_line|#define DNPROTO_EVR     6                       /* Evl protocol number (evl) */
DECL|macro|DNPROTO_NSPT
mdefine_line|#define DNPROTO_NSPT    7                       /* NSP trace protocol number */
DECL|macro|DN_ADDL
mdefine_line|#define DN_ADDL&t;&t;2
DECL|macro|DN_MAXADDL
mdefine_line|#define DN_MAXADDL&t;2 /* ULTRIX headers have 20 here, but pathworks has 2 */
DECL|macro|DN_MAXOPTL
mdefine_line|#define DN_MAXOPTL&t;16
DECL|macro|DN_MAXOBJL
mdefine_line|#define DN_MAXOBJL&t;16
DECL|macro|DN_MAXACCL
mdefine_line|#define DN_MAXACCL&t;40
DECL|macro|DN_MAXALIASL
mdefine_line|#define DN_MAXALIASL&t;128
DECL|macro|DN_MAXNODEL
mdefine_line|#define DN_MAXNODEL&t;256
DECL|macro|DNBUFSIZE
mdefine_line|#define DNBUFSIZE&t;65023
multiline_comment|/* &n; * SET/GET Socket options  - must match the DSO_ numbers below&n; */
DECL|macro|SO_CONDATA
mdefine_line|#define SO_CONDATA      1
DECL|macro|SO_CONACCESS
mdefine_line|#define SO_CONACCESS    2
DECL|macro|SO_PROXYUSR
mdefine_line|#define SO_PROXYUSR     3
DECL|macro|SO_LINKINFO
mdefine_line|#define SO_LINKINFO     7
DECL|macro|DSO_CONDATA
mdefine_line|#define DSO_CONDATA     1        /* Set/Get connect data                */
DECL|macro|DSO_DISDATA
mdefine_line|#define DSO_DISDATA     10       /* Set/Get disconnect data             */
DECL|macro|DSO_CONACCESS
mdefine_line|#define DSO_CONACCESS   2        /* Set/Get connect access data         */
DECL|macro|DSO_ACCEPTMODE
mdefine_line|#define DSO_ACCEPTMODE  4        /* Set/Get accept mode                 */
DECL|macro|DSO_CONACCEPT
mdefine_line|#define DSO_CONACCEPT   5        /* Accept deferred connection          */
DECL|macro|DSO_CONREJECT
mdefine_line|#define DSO_CONREJECT   6        /* Reject deferred connection          */
DECL|macro|DSO_LINKINFO
mdefine_line|#define DSO_LINKINFO    7        /* Set/Get link information            */
DECL|macro|DSO_STREAM
mdefine_line|#define DSO_STREAM      8        /* Set socket type to stream           */
DECL|macro|DSO_SEQPACKET
mdefine_line|#define DSO_SEQPACKET   9        /* Set socket type to sequenced packet */
DECL|macro|DSO_MAX
mdefine_line|#define DSO_MAX         10       /* Maximum option number               */
multiline_comment|/* LINK States */
DECL|macro|LL_INACTIVE
mdefine_line|#define LL_INACTIVE&t;0
DECL|macro|LL_CONNECTING
mdefine_line|#define LL_CONNECTING&t;1
DECL|macro|LL_RUNNING
mdefine_line|#define LL_RUNNING&t;2
DECL|macro|LL_DISCONNECTING
mdefine_line|#define LL_DISCONNECTING 3
DECL|macro|ACC_IMMED
mdefine_line|#define ACC_IMMED 0
DECL|macro|ACC_DEFER
mdefine_line|#define ACC_DEFER 1
DECL|macro|SDF_WILD
mdefine_line|#define SDF_WILD        1                  /* Wild card object          */
DECL|macro|SDF_PROXY
mdefine_line|#define SDF_PROXY       2                  /* Addr eligible for proxy   */
DECL|macro|SDF_UICPROXY
mdefine_line|#define SDF_UICPROXY    4                  /* Use uic-based proxy       */
multiline_comment|/* Structures */
DECL|struct|dn_naddr
r_struct
id|dn_naddr
(brace
DECL|member|a_len
r_int
r_int
id|a_len
suffix:semicolon
DECL|member|a_addr
r_int
r_char
id|a_addr
(braket
id|DN_MAXADDL
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sockaddr_dn
r_struct
id|sockaddr_dn
(brace
DECL|member|sdn_family
r_int
r_int
id|sdn_family
suffix:semicolon
DECL|member|sdn_flags
r_int
r_char
id|sdn_flags
suffix:semicolon
DECL|member|sdn_objnum
r_int
r_char
id|sdn_objnum
suffix:semicolon
DECL|member|sdn_objnamel
r_int
r_int
id|sdn_objnamel
suffix:semicolon
DECL|member|sdn_objname
r_int
r_char
id|sdn_objname
(braket
id|DN_MAXOBJL
)braket
suffix:semicolon
DECL|member|sdn_add
r_struct
id|dn_naddr
id|sdn_add
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|sdn_nodeaddrl
mdefine_line|#define sdn_nodeaddrl   sdn_add.a_len   /* Node address length  */
DECL|macro|sdn_nodeaddr
mdefine_line|#define sdn_nodeaddr    sdn_add.a_addr  /* Node address         */
multiline_comment|/*&n; * DECnet set/get DSO_CONDATA, DSO_DISDATA (optional data) structure&n; */
DECL|struct|optdata_dn
r_struct
id|optdata_dn
(brace
DECL|member|opt_status
r_int
r_int
id|opt_status
suffix:semicolon
multiline_comment|/* Extended status return */
DECL|macro|opt_sts
mdefine_line|#define opt_sts opt_status
DECL|member|opt_optl
r_int
r_int
id|opt_optl
suffix:semicolon
multiline_comment|/* Length of user data    */
DECL|member|opt_data
r_int
r_char
id|opt_data
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* User data              */
)brace
suffix:semicolon
DECL|struct|accessdata_dn
r_struct
id|accessdata_dn
(brace
DECL|member|acc_accl
r_int
r_char
id|acc_accl
suffix:semicolon
DECL|member|acc_acc
r_int
r_char
id|acc_acc
(braket
id|DN_MAXACCL
)braket
suffix:semicolon
DECL|member|acc_passl
r_int
r_char
id|acc_passl
suffix:semicolon
DECL|member|acc_pass
r_int
r_char
id|acc_pass
(braket
id|DN_MAXACCL
)braket
suffix:semicolon
DECL|member|acc_userl
r_int
r_char
id|acc_userl
suffix:semicolon
DECL|member|acc_user
r_int
r_char
id|acc_user
(braket
id|DN_MAXACCL
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * DECnet logical link information structure&n; */
DECL|struct|linkinfo_dn
r_struct
id|linkinfo_dn
(brace
DECL|member|idn_segsize
r_int
r_int
id|idn_segsize
suffix:semicolon
multiline_comment|/* Segment size for link */
DECL|member|idn_linkstate
r_int
r_char
id|idn_linkstate
suffix:semicolon
multiline_comment|/* Logical link state    */
)brace
suffix:semicolon
multiline_comment|/*&n; * Ethernet address format (for DECnet)&n; */
DECL|union|etheraddress
r_union
id|etheraddress
(brace
DECL|member|dne_addr
r_int
r_char
id|dne_addr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Full ethernet address */
r_struct
(brace
DECL|member|dne_hiord
r_int
r_char
id|dne_hiord
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* DECnet HIORD prefix   */
DECL|member|dne_nodeaddr
r_int
r_char
id|dne_nodeaddr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* DECnet node address   */
DECL|member|dne_remote
)brace
id|dne_remote
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * DECnet physical socket address format&n; */
DECL|struct|dn_addr
r_struct
id|dn_addr
(brace
DECL|member|dna_family
r_int
r_int
id|dna_family
suffix:semicolon
multiline_comment|/* AF_DECnet               */
DECL|member|dna_netaddr
r_union
id|etheraddress
id|dna_netaddr
suffix:semicolon
multiline_comment|/* DECnet ethernet address */
)brace
suffix:semicolon
DECL|macro|DECNET_IOCTL_BASE
mdefine_line|#define DECNET_IOCTL_BASE 0x89 /* PROTOPRIVATE range */
DECL|macro|SIOCSNETADDR
mdefine_line|#define SIOCSNETADDR  _IOW(DECNET_IOCTL_BASE, 0xe0, struct dn_naddr)
DECL|macro|SIOCGNETADDR
mdefine_line|#define SIOCGNETADDR  _IOR(DECNET_IOCTL_BASE, 0xe1, struct dn_naddr)
DECL|macro|OSIOCSNETADDR
mdefine_line|#define OSIOCSNETADDR _IOW(DECNET_IOCTL_BASE, 0xe0, int)
DECL|macro|OSIOCGNETADDR
mdefine_line|#define OSIOCGNETADDR _IOR(DECNET_IOCTL_BASE, 0xe1, int)
multiline_comment|/*&n; * An unofficial structure used to set/get routes.&n; * Be warned, this will probably change as the routing&n; * evolves. Also this is only for use with the ioctl()&n; * and the routing will use rtnetlink eventually.&n; */
DECL|struct|dn_fib_rtinfo
r_struct
id|dn_fib_rtinfo
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags */
DECL|macro|DN_FIB_RTINFO_F_REPLACE
mdefine_line|#define DN_FIB_RTINFO_F_REPLACE 0x0001  /* Replace any existing route */
DECL|macro|DN_FIB_RTINFO_F_DEVCOST
mdefine_line|#define DN_FIB_RTINFO_F_DEVCOST 0x0002  /* Add cost of device         */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* Time in seconds route should last */
DECL|member|src
r_int
r_int
id|src
suffix:semicolon
multiline_comment|/* Source Address, 0 = any */
DECL|member|dst
r_int
r_int
id|dst
suffix:semicolon
multiline_comment|/* Destination Address     */
DECL|member|nhp
r_int
r_int
id|nhp
suffix:semicolon
multiline_comment|/* Next Hop Address        */
DECL|member|hops
r_int
r_int
id|hops
suffix:semicolon
multiline_comment|/* Hops on path            */
DECL|member|cost
r_int
r_int
id|cost
suffix:semicolon
multiline_comment|/* Cost of path            */
DECL|member|device
r_char
id|device
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_DN_H */
eof
