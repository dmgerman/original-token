multiline_comment|/*&n; * This is a module which is used for queueing IPv4 packets and&n; * communicating with userspace via netlink.&n; *&n; * (C) 2000 James Morris&n; */
macro_line|#ifndef _IP_QUEUE_H
DECL|macro|_IP_QUEUE_H
mdefine_line|#define _IP_QUEUE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifdef DEBUG_IPQ
DECL|macro|QDEBUG
mdefine_line|#define QDEBUG(x...) printk(KERN_DEBUG ## x)
macro_line|#else
DECL|macro|QDEBUG
mdefine_line|#define QDEBUG(x...)
macro_line|#endif  /* DEBUG_IPQ */
macro_line|#else
macro_line|#include &lt;net/if.h&gt;
macro_line|#endif&t;/* ! __KERNEL__ */
multiline_comment|/* Messages sent from kernel */
DECL|struct|ipq_packet_msg
r_typedef
r_struct
id|ipq_packet_msg
(brace
DECL|member|packet_id
r_int
r_int
id|packet_id
suffix:semicolon
multiline_comment|/* ID of queued packet */
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
multiline_comment|/* Netfilter mark value */
DECL|member|timestamp_sec
r_int
id|timestamp_sec
suffix:semicolon
multiline_comment|/* Packet arrival time (seconds) */
DECL|member|timestamp_usec
r_int
id|timestamp_usec
suffix:semicolon
multiline_comment|/* Packet arrvial time (+useconds) */
DECL|member|hook
r_int
r_int
id|hook
suffix:semicolon
multiline_comment|/* Netfilter hook we rode in on */
DECL|member|indev_name
r_char
id|indev_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name of incoming interface */
DECL|member|outdev_name
r_char
id|outdev_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name of outgoing interface */
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
multiline_comment|/* Length of packet data */
multiline_comment|/* Optional packet data follows */
DECL|typedef|ipq_packet_msg_t
)brace
id|ipq_packet_msg_t
suffix:semicolon
multiline_comment|/* Messages sent from userspace */
DECL|struct|ipq_mode_msg
r_typedef
r_struct
id|ipq_mode_msg
(brace
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
multiline_comment|/* Requested mode */
DECL|member|range
r_int
id|range
suffix:semicolon
multiline_comment|/* Optional range of packet requested */
DECL|typedef|ipq_mode_msg_t
)brace
id|ipq_mode_msg_t
suffix:semicolon
DECL|struct|ipq_verdict_msg
r_typedef
r_struct
id|ipq_verdict_msg
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* Verdict to hand to netfilter */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* Packet ID for this verdict */
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
multiline_comment|/* Length of replacement data */
multiline_comment|/* Optional replacement data follows */
DECL|typedef|ipq_verdict_msg_t
)brace
id|ipq_verdict_msg_t
suffix:semicolon
DECL|struct|ipq_peer_msg
r_typedef
r_struct
id|ipq_peer_msg
(brace
r_union
(brace
DECL|member|verdict
id|ipq_verdict_msg_t
id|verdict
suffix:semicolon
DECL|member|mode
id|ipq_mode_msg_t
id|mode
suffix:semicolon
DECL|member|msg
)brace
id|msg
suffix:semicolon
DECL|typedef|ipq_peer_msg_t
)brace
id|ipq_peer_msg_t
suffix:semicolon
multiline_comment|/* Each queued packet has one of these states */
r_enum
(brace
DECL|enumerator|IPQ_PS_NEW
id|IPQ_PS_NEW
comma
multiline_comment|/* Newly arrived packet */
DECL|enumerator|IPQ_PS_WAITING
id|IPQ_PS_WAITING
comma
multiline_comment|/* User has been notified of packet, &n;&t;                           we&squot;re waiting for a verdict */
DECL|enumerator|IPQ_PS_VERDICT
id|IPQ_PS_VERDICT
multiline_comment|/* Packet has been assigned verdict,&n;&t;                           waiting to be reinjected */
)brace
suffix:semicolon
DECL|macro|IPQ_PS_MAX
mdefine_line|#define IPQ_PS_MAX IPQ_PS_VERDICT
multiline_comment|/* The queue operates in one of these states */
r_enum
(brace
DECL|enumerator|IPQ_QS_HOLD
id|IPQ_QS_HOLD
comma
multiline_comment|/* Hold all packets in queue */
DECL|enumerator|IPQ_QS_COPY
id|IPQ_QS_COPY
comma
multiline_comment|/* Copy metadata and/or packets to user */
DECL|enumerator|IPQ_QS_FLUSH
id|IPQ_QS_FLUSH
multiline_comment|/* Flush and drop all queue entries */
)brace
suffix:semicolon
DECL|macro|IPQ_QS_MAX
mdefine_line|#define IPQ_QS_MAX IPQ_QS_FLUSH
multiline_comment|/* Modes requested by peer */
r_enum
(brace
DECL|enumerator|IPQ_COPY_NONE
id|IPQ_COPY_NONE
comma
multiline_comment|/* Copy nothing */
DECL|enumerator|IPQ_COPY_META
id|IPQ_COPY_META
comma
multiline_comment|/* Copy metadata */
DECL|enumerator|IPQ_COPY_PACKET
id|IPQ_COPY_PACKET
multiline_comment|/* Copy metadata + packet (range) */
)brace
suffix:semicolon
DECL|macro|IPQ_COPY_MAX
mdefine_line|#define IPQ_COPY_MAX IPQ_COPY_PACKET
multiline_comment|/* Types of messages */
DECL|macro|IPQM_BASE
mdefine_line|#define IPQM_BASE&t;0x10&t;/* standard netlink messages below this */
DECL|macro|IPQM_MODE
mdefine_line|#define IPQM_MODE&t;(IPQM_BASE + 1)&t;/* Mode request from peer */
DECL|macro|IPQM_VERDICT
mdefine_line|#define IPQM_VERDICT&t;(IPQM_BASE + 2)&t;/* Verdict from peer */ 
DECL|macro|IPQM_PACKET
mdefine_line|#define IPQM_PACKET&t;(IPQM_BASE + 3)&t;/* Packet from kernel */
DECL|macro|IPQM_MAX
mdefine_line|#define IPQM_MAX&t;(IPQM_BASE + 4)
macro_line|#endif /*_IP_QUEUE_H*/
eof
