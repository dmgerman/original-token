macro_line|#ifndef _LINUX_PPP_H
DECL|macro|_LINUX_PPP_H
mdefine_line|#define _LINUX_PPP_H
multiline_comment|/* definitions for kernel PPP module&n;   Michael Callahan &lt;callahan@maths.ox.ac.uk&gt;&n;   Nov. 4 1993 */
multiline_comment|/* how many PPP units? */
DECL|macro|PPP_NRUNIT
mdefine_line|#define PPP_NRUNIT     4
DECL|macro|PPP_VERSION
mdefine_line|#define PPP_VERSION  &quot;0.2.7&quot;
multiline_comment|/* line discipline number */
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;       3
multiline_comment|/* Magic value for the ppp structure */
DECL|macro|PPP_MAGIC
mdefine_line|#define PPP_MAGIC 0x5002
DECL|macro|PPPIOCGFLAGS
mdefine_line|#define&t;PPPIOCGFLAGS&t; 0x5490&t;/* get configuration flags */
DECL|macro|PPPIOCSFLAGS
mdefine_line|#define&t;PPPIOCSFLAGS&t; 0x5491&t;/* set configuration flags */
DECL|macro|PPPIOCGASYNCMAP
mdefine_line|#define&t;PPPIOCGASYNCMAP&t; 0x5492&t;/* get async map */
DECL|macro|PPPIOCSASYNCMAP
mdefine_line|#define&t;PPPIOCSASYNCMAP&t; 0x5493&t;/* set async map */
DECL|macro|PPPIOCGUNIT
mdefine_line|#define&t;PPPIOCGUNIT&t; 0x5494&t;/* get ppp unit number */
DECL|macro|PPPIOCSINPSIG
mdefine_line|#define PPPIOCSINPSIG&t; 0x5495&t;/* set input ready signal */
DECL|macro|PPPIOCSDEBUG
mdefine_line|#define PPPIOCSDEBUG&t; 0x5497&t;/* set debug level */
DECL|macro|PPPIOCGDEBUG
mdefine_line|#define PPPIOCGDEBUG&t; 0x5498&t;/* get debug level */
DECL|macro|PPPIOCGSTAT
mdefine_line|#define PPPIOCGSTAT&t; 0x5499&t;/* read PPP statistic information */
DECL|macro|PPPIOCGTIME
mdefine_line|#define PPPIOCGTIME&t; 0x549A&t;/* read time delta information */
DECL|macro|PPPIOCGXASYNCMAP
mdefine_line|#define&t;PPPIOCGXASYNCMAP 0x549B&t;/* get async table */
DECL|macro|PPPIOCSXASYNCMAP
mdefine_line|#define&t;PPPIOCSXASYNCMAP 0x549C&t;/* set async table */
DECL|macro|PPPIOCSMRU
mdefine_line|#define PPPIOCSMRU&t; 0x549D&t;/* set receive unit size for PPP */
DECL|macro|PPPIOCRASYNCMAP
mdefine_line|#define PPPIOCRASYNCMAP&t; 0x549E&t;/* set receive async map */
DECL|macro|PPPIOCSMAXCID
mdefine_line|#define PPPIOCSMAXCID    0x549F /* set the maximum compression slot id */
multiline_comment|/* special characters in the framing protocol */
DECL|macro|PPP_ALLSTATIONS
mdefine_line|#define&t;PPP_ALLSTATIONS&t;0xff&t;/* All-Stations broadcast address */
DECL|macro|PPP_UI
mdefine_line|#define&t;PPP_UI&t;&t;0x03&t;/* Unnumbered Information */
DECL|macro|PPP_FLAG
mdefine_line|#define PPP_FLAG&t;0x7E&t;/* frame delimiter -- marks frame boundaries */
DECL|macro|PPP_ADDRESS
mdefine_line|#define PPP_ADDRESS&t;0xFF&t;/* first character of frame   &lt;--  (may be   */
DECL|macro|PPP_CONTROL
mdefine_line|#define PPP_CONTROL&t;0x03&t;/* second character of frame  &lt;-- compressed)*/
DECL|macro|PPP_TRANS
mdefine_line|#define&t;PPP_TRANS&t;0x20&t;/* Asynchronous transparency modifier */
DECL|macro|PPP_ESC
mdefine_line|#define PPP_ESC&t;&t;0x7d&t;/* escape character -- next character is&n;&t;&t;&t;&t;   data, and the PPP_TRANS bit should be&n;&t;&t;&t;&t;   toggled. PPP_ESC PPP_FLAG is illegal */
multiline_comment|/* protocol numbers */
DECL|macro|PROTO_IP
mdefine_line|#define PROTO_IP       0x0021
DECL|macro|PROTO_VJCOMP
mdefine_line|#define PROTO_VJCOMP   0x002d
DECL|macro|PROTO_VJUNCOMP
mdefine_line|#define PROTO_VJUNCOMP 0x002f
multiline_comment|/* FCS support */
DECL|macro|PPP_FCS_INIT
mdefine_line|#define PPP_FCS_INIT   0xffff
DECL|macro|PPP_FCS_GOOD
mdefine_line|#define PPP_FCS_GOOD   0xf0b8
multiline_comment|/* initial MTU */
DECL|macro|PPP_MTU
mdefine_line|#define PPP_MTU&t;       1500
multiline_comment|/* initial MRU */
DECL|macro|PPP_MRU
mdefine_line|#define PPP_MRU&t;       PPP_MTU
multiline_comment|/* flags */
DECL|macro|SC_COMP_PROT
mdefine_line|#define SC_COMP_PROT&t;0x00000001&t;/* protocol compression (output) */
DECL|macro|SC_COMP_AC
mdefine_line|#define SC_COMP_AC&t;0x00000002&t;/* header compression (output) */
DECL|macro|SC_COMP_TCP
mdefine_line|#define&t;SC_COMP_TCP&t;0x00000004&t;/* TCP (VJ) compression (output) */
DECL|macro|SC_NO_TCP_CCID
mdefine_line|#define SC_NO_TCP_CCID&t;0x00000008&t;/* disable VJ connection-id comp. */
DECL|macro|SC_REJ_COMP_AC
mdefine_line|#define SC_REJ_COMP_AC&t;0x00000010&t;/* reject adrs/ctrl comp. on input */
DECL|macro|SC_REJ_COMP_TCP
mdefine_line|#define SC_REJ_COMP_TCP&t;0x00000020&t;/* reject TCP (VJ) comp. on input */
DECL|macro|SC_ENABLE_IP
mdefine_line|#define SC_ENABLE_IP&t;0x00000100&t;/* IP packets may be exchanged */
DECL|macro|SC_IP_DOWN
mdefine_line|#define SC_IP_DOWN&t;0x00000200&t;/* give ip frames to pppd */
DECL|macro|SC_IP_FLUSH
mdefine_line|#define SC_IP_FLUSH&t;0x00000400&t;/* &quot;next time&quot; flag for IP_DOWN */
DECL|macro|SC_DEBUG
mdefine_line|#define SC_DEBUG&t;0x00010000&t;/* enable debug messages */
DECL|macro|SC_LOG_INPKT
mdefine_line|#define SC_LOG_INPKT&t;0x00020000&t;/* log contents of good pkts recvd */
DECL|macro|SC_LOG_OUTPKT
mdefine_line|#define SC_LOG_OUTPKT&t;0x00040000&t;/* log contents of pkts sent */
DECL|macro|SC_LOG_RAWIN
mdefine_line|#define SC_LOG_RAWIN&t;0x00080000&t;/* log all chars received */
DECL|macro|SC_LOG_FLUSH
mdefine_line|#define SC_LOG_FLUSH&t;0x00100000&t;/* log all chars flushed */
multiline_comment|/* Flag bits to determine state of input characters */
DECL|macro|SC_RCV_B7_0
mdefine_line|#define SC_RCV_B7_0&t;0x01000000&t;/* have rcvd char with bit 7 = 0 */
DECL|macro|SC_RCV_B7_1
mdefine_line|#define SC_RCV_B7_1&t;0x02000000&t;/* have rcvd char with bit 7 = 0 */
DECL|macro|SC_RCV_EVNP
mdefine_line|#define SC_RCV_EVNP&t;0x04000000&t;/* have rcvd char with even parity */
DECL|macro|SC_RCV_ODDP
mdefine_line|#define SC_RCV_ODDP&t;0x08000000&t;/* have rcvd char with odd parity */
DECL|macro|SC_MASK
mdefine_line|#define&t;SC_MASK&t;&t;0x0fffffff&t;/* bits that user can change */
multiline_comment|/* flag for doing transmitter lockout */
DECL|macro|SC_XMIT_BUSY
mdefine_line|#define SC_XMIT_BUSY&t;0x10000000&t;/* ppp_write_wakeup is active */
multiline_comment|/*&n; * This is the format of the data buffer of a LQP packet. The packet data&n; * is sent/received to the peer.&n; */
DECL|struct|ppp_lqp_packet_hdr
r_struct
id|ppp_lqp_packet_hdr
(brace
DECL|member|LastOutLQRs
r_int
r_int
id|LastOutLQRs
suffix:semicolon
multiline_comment|/* Copied from PeerOutLQRs&t; */
DECL|member|LastOutPackets
r_int
r_int
id|LastOutPackets
suffix:semicolon
multiline_comment|/* Copied from PeerOutPackets&t; */
DECL|member|LastOutOctets
r_int
r_int
id|LastOutOctets
suffix:semicolon
multiline_comment|/* Copied from PeerOutOctets&t; */
DECL|member|PeerInLQRs
r_int
r_int
id|PeerInLQRs
suffix:semicolon
multiline_comment|/* Copied from SavedInLQRs&t; */
DECL|member|PeerInPackets
r_int
r_int
id|PeerInPackets
suffix:semicolon
multiline_comment|/* Copied from SavedInPackets&t; */
DECL|member|PeerInDiscards
r_int
r_int
id|PeerInDiscards
suffix:semicolon
multiline_comment|/* Copied from SavedInDiscards&t; */
DECL|member|PeerInErrors
r_int
r_int
id|PeerInErrors
suffix:semicolon
multiline_comment|/* Copied from SavedInErrors&t; */
DECL|member|PeerInOctets
r_int
r_int
id|PeerInOctets
suffix:semicolon
multiline_comment|/* Copied from SavedInOctets&t; */
DECL|member|PeerOutLQRs
r_int
r_int
id|PeerOutLQRs
suffix:semicolon
multiline_comment|/* Copied from OutLQRs, plus 1&t; */
DECL|member|PeerOutPackets
r_int
r_int
id|PeerOutPackets
suffix:semicolon
multiline_comment|/* Current ifOutUniPackets, + 1&t; */
DECL|member|PeerOutOctets
r_int
r_int
id|PeerOutOctets
suffix:semicolon
multiline_comment|/* Current ifOutOctets + LQR&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * This data is not sent to the remote. It is updated by the driver when&n; * a packet is received.&n; */
DECL|struct|ppp_lqp_packet_trailer
r_struct
id|ppp_lqp_packet_trailer
(brace
DECL|member|SaveInLQRs
r_int
r_int
id|SaveInLQRs
suffix:semicolon
multiline_comment|/* Current InLQRs on reception&t; */
DECL|member|SaveInPackets
r_int
r_int
id|SaveInPackets
suffix:semicolon
multiline_comment|/* Current ifInUniPackets&t; */
DECL|member|SaveInDiscards
r_int
r_int
id|SaveInDiscards
suffix:semicolon
multiline_comment|/* Current ifInDiscards&t;&t; */
DECL|member|SaveInErrors
r_int
r_int
id|SaveInErrors
suffix:semicolon
multiline_comment|/* Current ifInErrors&t;&t; */
DECL|member|SaveInOctets
r_int
r_int
id|SaveInOctets
suffix:semicolon
multiline_comment|/* Current ifInOctects&t;&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * PPP LQP packet. The packet is changed by the driver immediately prior&n; * to transmission and updated upon reception with the current values.&n; * So, it must be known to the driver as well as the pppd software.&n; */
DECL|struct|ppp_lpq_packet
r_struct
id|ppp_lpq_packet
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* current magic value&t;&t; */
DECL|member|hdr
r_struct
id|ppp_lqp_packet_hdr
id|hdr
suffix:semicolon
multiline_comment|/* Header fields for structure&t; */
DECL|member|tail
r_struct
id|ppp_lqp_packet_trailer
id|tail
suffix:semicolon
multiline_comment|/* Trailer fields (not sent)&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * PPP interface statistics. (used by LQP / pppstats)&n; */
DECL|struct|ppp_stats
r_struct
id|ppp_stats
(brace
DECL|member|rbytes
r_int
r_int
id|rbytes
suffix:semicolon
multiline_comment|/* bytes received&t;&t; */
DECL|member|rcomp
r_int
r_int
id|rcomp
suffix:semicolon
multiline_comment|/* compressed packets received&t; */
DECL|member|runcomp
r_int
r_int
id|runcomp
suffix:semicolon
multiline_comment|/* uncompressed packets received */
DECL|member|rothers
r_int
r_int
id|rothers
suffix:semicolon
multiline_comment|/* non-ip frames received&t; */
DECL|member|rerrors
r_int
r_int
id|rerrors
suffix:semicolon
multiline_comment|/* received errors&t;&t; */
DECL|member|roverrun
r_int
r_int
id|roverrun
suffix:semicolon
multiline_comment|/* &quot;buffer overrun&quot; counter&t; */
DECL|member|tossed
r_int
r_int
id|tossed
suffix:semicolon
multiline_comment|/* packets discarded&t;&t; */
DECL|member|runts
r_int
r_int
id|runts
suffix:semicolon
multiline_comment|/* frames too short to process&t; */
DECL|member|rgiants
r_int
r_int
id|rgiants
suffix:semicolon
multiline_comment|/* frames too large to process&t; */
DECL|member|sbytes
r_int
r_int
id|sbytes
suffix:semicolon
multiline_comment|/* bytes sent&t;&t;&t; */
DECL|member|scomp
r_int
r_int
id|scomp
suffix:semicolon
multiline_comment|/* compressed packets sent&t; */
DECL|member|suncomp
r_int
r_int
id|suncomp
suffix:semicolon
multiline_comment|/* uncompressed packets sent&t; */
DECL|member|sothers
r_int
r_int
id|sothers
suffix:semicolon
multiline_comment|/* non-ip frames sent&t;&t; */
DECL|member|serrors
r_int
r_int
id|serrors
suffix:semicolon
multiline_comment|/* transmitter errors&t;&t; */
DECL|member|sbusy
r_int
r_int
id|sbusy
suffix:semicolon
multiline_comment|/* &quot;transmitter busy&quot; counter&t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * Demand dial fields&n; */
DECL|struct|ppp_ddinfo
r_struct
id|ppp_ddinfo
(brace
DECL|member|ip_sjiffies
r_int
r_int
id|ip_sjiffies
suffix:semicolon
multiline_comment|/* time when last IP frame sent */
DECL|member|ip_rjiffies
r_int
r_int
id|ip_rjiffies
suffix:semicolon
multiline_comment|/* time when last IP frame recvd*/
DECL|member|nip_sjiffies
r_int
r_int
id|nip_sjiffies
suffix:semicolon
multiline_comment|/* time when last NON-IP sent&t;*/
DECL|member|nip_rjiffies
r_int
r_int
id|nip_rjiffies
suffix:semicolon
multiline_comment|/* time when last NON-IP recvd&t;*/
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|ppp
r_struct
id|ppp
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic value for structure&t;*/
multiline_comment|/* Bitmapped flag fields. */
DECL|member|inuse
r_char
id|inuse
suffix:semicolon
multiline_comment|/* are we allocated?&t;&t;*/
DECL|member|sending
r_char
id|sending
suffix:semicolon
multiline_comment|/* &quot;channel busy&quot; indicator&t;*/
DECL|member|escape
r_char
id|escape
suffix:semicolon
multiline_comment|/* 0x20 if prev char was PPP_ESC*/
DECL|member|toss
r_char
id|toss
suffix:semicolon
multiline_comment|/* toss this frame&t;&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* miscellany&t;&t;&t;*/
DECL|member|xmit_async_map
r_int
r_int
id|xmit_async_map
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is quoted on output*/
DECL|member|recv_async_map
r_int
r_int
id|recv_async_map
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is ignored on input*/
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
multiline_comment|/* maximum xmit frame size&t;*/
DECL|member|mru
r_int
id|mru
suffix:semicolon
multiline_comment|/* maximum receive frame size&t;*/
DECL|member|fcs
r_int
r_int
id|fcs
suffix:semicolon
multiline_comment|/* FCS field of current frame&t;*/
multiline_comment|/* Various fields. */
DECL|member|line
r_int
id|line
suffix:semicolon
multiline_comment|/* PPP channel number&t;&t;*/
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;&t;*/
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* easy for intr handling&t;*/
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
multiline_comment|/* for header compression&t;*/
DECL|member|last_xmit
r_int
r_int
id|last_xmit
suffix:semicolon
multiline_comment|/* time of last transmission&t;*/
multiline_comment|/* These are pointers to the malloc()ed frame buffers.&n;     These buffers are used while processing a packet.&t;If a packet&n;     has to hang around for the user process to read it, it lingers in&n;     the user buffers below. */
DECL|member|rbuff
r_int
r_char
op_star
id|rbuff
suffix:semicolon
multiline_comment|/* receiver buffer&t;&t;*/
DECL|member|xbuff
r_int
r_char
op_star
id|xbuff
suffix:semicolon
multiline_comment|/* transmitter buffer&t;&t;*/
DECL|member|cbuff
r_int
r_char
op_star
id|cbuff
suffix:semicolon
multiline_comment|/* compression buffer&t;&t;*/
multiline_comment|/* These are the various pointers into the buffers. */
DECL|member|rhead
r_int
r_char
op_star
id|rhead
suffix:semicolon
multiline_comment|/* RECV buffer pointer (head)&t;*/
DECL|member|rend
r_int
r_char
op_star
id|rend
suffix:semicolon
multiline_comment|/* RECV buffer pointer (end)&t;*/
DECL|member|rcount
r_int
id|rcount
suffix:semicolon
multiline_comment|/* PPP receive counter&t;&t;*/
DECL|member|xhead
r_int
r_char
op_star
id|xhead
suffix:semicolon
multiline_comment|/* XMIT buffer pointer (head)&t;*/
DECL|member|xtail
r_int
r_char
op_star
id|xtail
suffix:semicolon
multiline_comment|/* XMIT buffer pointer (end) &t;*/
multiline_comment|/* Structures for interfacing with the user process. */
DECL|macro|RBUFSIZE
mdefine_line|#define RBUFSIZE 4000
DECL|member|us_rbuff
r_int
r_char
op_star
id|us_rbuff
suffix:semicolon
multiline_comment|/* circular incoming packet buf.*/
DECL|member|us_rbuff_end
r_int
r_char
op_star
id|us_rbuff_end
suffix:semicolon
multiline_comment|/* end of allocated space&t;*/
DECL|member|us_rbuff_head
r_int
r_char
op_star
id|us_rbuff_head
suffix:semicolon
multiline_comment|/* head of waiting packets&t;*/
DECL|member|us_rbuff_tail
r_int
r_char
op_star
id|us_rbuff_tail
suffix:semicolon
multiline_comment|/* tail of waiting packets&t;*/
DECL|member|us_rbuff_lock
r_int
r_char
id|us_rbuff_lock
suffix:semicolon
multiline_comment|/* lock: bit 0 head bit 1 tail&t;*/
DECL|member|inp_sig
r_int
id|inp_sig
suffix:semicolon
multiline_comment|/* input ready signal for pgrp&t;*/
DECL|member|inp_sig_pid
r_int
id|inp_sig_pid
suffix:semicolon
multiline_comment|/* process to get notified&t;*/
multiline_comment|/* items to support the select() function */
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
multiline_comment|/* queue for reading processes&t;*/
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
multiline_comment|/* queue for writing processes&t;*/
multiline_comment|/* PPP interface statistics. */
DECL|member|stats
r_struct
id|ppp_stats
id|stats
suffix:semicolon
multiline_comment|/* statistic information&t;*/
multiline_comment|/* PPP demand dial information. */
DECL|member|ddinfo
r_struct
id|ppp_ddinfo
id|ddinfo
suffix:semicolon
multiline_comment|/* demand dial information&t;*/
)brace
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_PPP_H */
eof
