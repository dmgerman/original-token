multiline_comment|/*&n; * Frame Diversion, Benoit Locher &lt;Benoit.Locher@skf.com&gt;&n; *&n; * Changes:&n; * &t;&t;06/09/2000&t;BL:&t;initial version&n; * &n; */
macro_line|#ifndef _LINUX_DIVERT_H
DECL|macro|_LINUX_DIVERT_H
mdefine_line|#define _LINUX_DIVERT_H
DECL|macro|MAX_DIVERT_PORTS
mdefine_line|#define&t;MAX_DIVERT_PORTS&t;8&t;/* Max number of ports to divert (tcp, udp) */
multiline_comment|/* Divertable protocols */
DECL|macro|DIVERT_PROTO_NONE
mdefine_line|#define&t;DIVERT_PROTO_NONE&t;0x0000
DECL|macro|DIVERT_PROTO_IP
mdefine_line|#define&t;DIVERT_PROTO_IP&t;&t;0x0001
DECL|macro|DIVERT_PROTO_ICMP
mdefine_line|#define&t;DIVERT_PROTO_ICMP&t;0x0002
DECL|macro|DIVERT_PROTO_TCP
mdefine_line|#define&t;DIVERT_PROTO_TCP&t;0x0004
DECL|macro|DIVERT_PROTO_UDP
mdefine_line|#define&t;DIVERT_PROTO_UDP&t;0x0008
macro_line|#ifdef __KERNEL__
DECL|macro|S16
mdefine_line|#define S16     s16
DECL|macro|U16
mdefine_line|#define U16     u16
DECL|macro|S32
mdefine_line|#define S32     s32
DECL|macro|U32
mdefine_line|#define U32     u32
DECL|macro|S64
mdefine_line|#define S64     s64
DECL|macro|U64
mdefine_line|#define U64     u64
macro_line|#else
DECL|macro|S16
mdefine_line|#define&t;S16&t;&t;__s16
DECL|macro|U16
mdefine_line|#define&t;U16&t;&t;__u16
DECL|macro|S32
mdefine_line|#define&t;S32&t;&t;__s32
DECL|macro|U32
mdefine_line|#define&t;U32&t;&t;__u32
DECL|macro|S64
mdefine_line|#define&t;S64&t;&t;__s64
DECL|macro|U64
mdefine_line|#define&t;U64&t;&t;__u64
macro_line|#endif
multiline_comment|/*&n; *&t;This is an Ethernet Frame Diverter option block&n; */
DECL|struct|divert_blk
r_struct
id|divert_blk
(brace
DECL|member|divert
r_int
id|divert
suffix:semicolon
multiline_comment|/* are we active */
DECL|member|protos
r_int
r_int
id|protos
suffix:semicolon
multiline_comment|/* protocols */
DECL|member|tcp_dst
id|U16
id|tcp_dst
(braket
id|MAX_DIVERT_PORTS
)braket
suffix:semicolon
multiline_comment|/* specific tcp dst ports to divert */
DECL|member|tcp_src
id|U16
id|tcp_src
(braket
id|MAX_DIVERT_PORTS
)braket
suffix:semicolon
multiline_comment|/* specific tcp src ports to divert */
DECL|member|udp_dst
id|U16
id|udp_dst
(braket
id|MAX_DIVERT_PORTS
)braket
suffix:semicolon
multiline_comment|/* specific udp dst ports to divert */
DECL|member|udp_src
id|U16
id|udp_src
(braket
id|MAX_DIVERT_PORTS
)braket
suffix:semicolon
multiline_comment|/* specific udp src ports to divert */
)brace
suffix:semicolon
multiline_comment|/*&n; * Diversion control block, for configuration with the userspace tool&n; * divert&n; */
DECL|union|_divert_cf_arg
r_typedef
r_union
id|_divert_cf_arg
(brace
DECL|member|int16
id|S16
id|int16
suffix:semicolon
DECL|member|uint16
id|U16
id|uint16
suffix:semicolon
DECL|member|int32
id|S32
id|int32
suffix:semicolon
DECL|member|uint32
id|U32
id|uint32
suffix:semicolon
DECL|member|int64
id|S64
id|int64
suffix:semicolon
DECL|member|uint64
id|U64
id|uint64
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|typedef|divert_cf_arg
)brace
id|divert_cf_arg
suffix:semicolon
DECL|struct|divert_cf
r_struct
id|divert_cf
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Command */
DECL|member|arg1
id|divert_cf_arg
id|arg1
comma
DECL|member|arg2
id|arg2
comma
DECL|member|arg3
id|arg3
suffix:semicolon
DECL|member|dev_index
r_int
id|dev_index
suffix:semicolon
multiline_comment|/* device index (eth0=0, etc...) */
)brace
suffix:semicolon
multiline_comment|/* Diversion commands */
DECL|macro|DIVCMD_DIVERT
mdefine_line|#define&t;DIVCMD_DIVERT&t;&t;&t;1 /* ENABLE/DISABLE diversion */
DECL|macro|DIVCMD_IP
mdefine_line|#define&t;DIVCMD_IP&t;&t;&t;&t;2 /* ENABLE/DISABLE whold IP diversion */
DECL|macro|DIVCMD_TCP
mdefine_line|#define&t;DIVCMD_TCP&t;&t;&t;&t;3 /* ENABLE/DISABLE whold TCP diversion */
DECL|macro|DIVCMD_TCPDST
mdefine_line|#define&t;DIVCMD_TCPDST&t;&t;&t;4 /* ADD/REMOVE TCP DST port for diversion */
DECL|macro|DIVCMD_TCPSRC
mdefine_line|#define&t;DIVCMD_TCPSRC&t;&t;&t;5 /* ADD/REMOVE TCP SRC port for diversion */
DECL|macro|DIVCMD_UDP
mdefine_line|#define&t;DIVCMD_UDP&t;&t;&t;&t;6 /* ENABLE/DISABLE whole UDP diversion */
DECL|macro|DIVCMD_UDPDST
mdefine_line|#define&t;DIVCMD_UDPDST&t;&t;&t;7 /* ADD/REMOVE UDP DST port for diversion */
DECL|macro|DIVCMD_UDPSRC
mdefine_line|#define&t;DIVCMD_UDPSRC&t;&t;&t;8 /* ADD/REMOVE UDP SRC port for diversion */
DECL|macro|DIVCMD_ICMP
mdefine_line|#define&t;DIVCMD_ICMP&t;&t;&t;&t;9 /* ENABLE/DISABLE whole ICMP diversion */
DECL|macro|DIVCMD_GETSTATUS
mdefine_line|#define&t;DIVCMD_GETSTATUS&t;&t;10 /* GET the status of the diverter */
DECL|macro|DIVCMD_RESET
mdefine_line|#define&t;DIVCMD_RESET&t;&t;&t;11 /* Reset the diverter on the specified dev */
DECL|macro|DIVCMD_GETVERSION
mdefine_line|#define DIVCMD_GETVERSION&t;&t;12 /* Retrieve the diverter code version (char[32]) */
multiline_comment|/* General syntax of the commands:&n; * &n; * DIVCMD_xxxxxx(arg1, arg2, arg3, dev_index)&n; * &n; * SIOCSIFDIVERT:&n; *   DIVCMD_DIVERT(DIVARG1_ENABLE|DIVARG1_DISABLE, , ,ifindex)&n; *   DIVCMD_IP(DIVARG1_ENABLE|DIVARG1_DISABLE, , , ifindex)&n; *   DIVCMD_TCP(DIVARG1_ENABLE|DIVARG1_DISABLE, , , ifindex)&n; *   DIVCMD_TCPDST(DIVARG1_ADD|DIVARG1_REMOVE, port, , ifindex)&n; *   DIVCMD_TCPSRC(DIVARG1_ADD|DIVARG1_REMOVE, port, , ifindex)&n; *   DIVCMD_UDP(DIVARG1_ENABLE|DIVARG1_DISABLE, , , ifindex)&n; *   DIVCMD_UDPDST(DIVARG1_ADD|DIVARG1_REMOVE, port, , ifindex)&n; *   DIVCMD_UDPSRC(DIVARG1_ADD|DIVARG1_REMOVE, port, , ifindex)&n; *   DIVCMD_ICMP(DIVARG1_ENABLE|DIVARG1_DISABLE, , , ifindex)&n; *   DIVCMD_RESET(, , , ifindex)&n; *   &n; * SIOGIFDIVERT:&n; *   DIVCMD_GETSTATUS(divert_blk, , , ifindex)&n; *   DIVCMD_GETVERSION(string[3])&n; */
multiline_comment|/* Possible values for arg1 */
DECL|macro|DIVARG1_ENABLE
mdefine_line|#define&t;DIVARG1_ENABLE&t;&t;&t;0 /* ENABLE something */
DECL|macro|DIVARG1_DISABLE
mdefine_line|#define&t;DIVARG1_DISABLE&t;&t;&t;1 /* DISABLE something */
DECL|macro|DIVARG1_ADD
mdefine_line|#define DIVARG1_ADD&t;&t;&t;&t;2 /* ADD something */
DECL|macro|DIVARG1_REMOVE
mdefine_line|#define DIVARG1_REMOVE&t;&t;&t;3 /* REMOVE something */
macro_line|#ifdef __KERNEL__
multiline_comment|/* diverter functions */
macro_line|#include &lt;linux/skbuff.h&gt;
r_int
id|alloc_divert_blk
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_void
id|free_divert_blk
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_int
id|divert_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_struct
id|divert_cf
op_star
id|arg
)paren
suffix:semicolon
r_void
id|divert_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif __KERNEL__
macro_line|#endif&t;/* _LINUX_DIVERT_H */
eof
