multiline_comment|/* -*- mode: c; c-basic-offset: 2 -*- */
macro_line|#ifndef _LINUX_ISDN_PPP_H
DECL|macro|_LINUX_ISDN_PPP_H
mdefine_line|#define _LINUX_ISDN_PPP_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|CALLTYPE_INCOMING
mdefine_line|#define CALLTYPE_INCOMING 0x1
DECL|macro|CALLTYPE_OUTGOING
mdefine_line|#define CALLTYPE_OUTGOING 0x2
DECL|macro|CALLTYPE_CALLBACK
mdefine_line|#define CALLTYPE_CALLBACK 0x4
DECL|macro|IPPP_VERSION
mdefine_line|#define IPPP_VERSION    &quot;2.2.0&quot;
DECL|struct|pppcallinfo
r_struct
id|pppcallinfo
(brace
DECL|member|calltype
r_int
id|calltype
suffix:semicolon
DECL|member|local_num
r_int
r_char
id|local_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|remote_num
r_int
r_char
id|remote_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|charge_units
r_int
id|charge_units
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PPPIOCGCALLINFO
mdefine_line|#define PPPIOCGCALLINFO _IOWR(&squot;t&squot;,128,struct pppcallinfo)
DECL|macro|PPPIOCBUNDLE
mdefine_line|#define PPPIOCBUNDLE   _IOW(&squot;t&squot;,129,int)
DECL|macro|PPPIOCGMPFLAGS
mdefine_line|#define PPPIOCGMPFLAGS _IOR(&squot;t&squot;,130,int)
DECL|macro|PPPIOCSMPFLAGS
mdefine_line|#define PPPIOCSMPFLAGS _IOW(&squot;t&squot;,131,int)
DECL|macro|PPPIOCSMPMTU
mdefine_line|#define PPPIOCSMPMTU   _IOW(&squot;t&squot;,132,int)
DECL|macro|PPPIOCSMPMRU
mdefine_line|#define PPPIOCSMPMRU   _IOW(&squot;t&squot;,133,int)
DECL|macro|PPPIOCGCOMPRESSORS
mdefine_line|#define PPPIOCGCOMPRESSORS _IOR(&squot;t&squot;,134,unsigned long [8])
DECL|macro|PPPIOCSCOMPRESSOR
mdefine_line|#define PPPIOCSCOMPRESSOR _IOW(&squot;t&squot;,135,int)
DECL|macro|PPPIOCGIFNAME
mdefine_line|#define PPPIOCGIFNAME      _IOR(&squot;t&squot;,136, char [IFNAMSIZ] )
DECL|macro|PPP_MP
mdefine_line|#define PPP_MP          0x003d
DECL|macro|PPP_LINK_COMP
mdefine_line|#define PPP_LINK_COMP   0x00fb
DECL|macro|PPP_LINK_CCP
mdefine_line|#define PPP_LINK_CCP    0x80fb
DECL|macro|SC_MP_PROT
mdefine_line|#define SC_MP_PROT       0x00000200
DECL|macro|SC_REJ_MP_PROT
mdefine_line|#define SC_REJ_MP_PROT   0x00000400
DECL|macro|SC_OUT_SHORT_SEQ
mdefine_line|#define SC_OUT_SHORT_SEQ 0x00000800
DECL|macro|SC_IN_SHORT_SEQ
mdefine_line|#define SC_IN_SHORT_SEQ  0x00004000
DECL|macro|SC_DECOMP_ON
mdefine_line|#define SC_DECOMP_ON&t;&t;0x01
DECL|macro|SC_COMP_ON
mdefine_line|#define SC_COMP_ON&t;&t;0x02
DECL|macro|SC_DECOMP_DISCARD
mdefine_line|#define SC_DECOMP_DISCARD&t;0x04
DECL|macro|SC_COMP_DISCARD
mdefine_line|#define SC_COMP_DISCARD&t;&t;0x08
DECL|macro|SC_LINK_DECOMP_ON
mdefine_line|#define SC_LINK_DECOMP_ON&t;0x10
DECL|macro|SC_LINK_COMP_ON
mdefine_line|#define SC_LINK_COMP_ON&t;&t;0x20
DECL|macro|SC_LINK_DECOMP_DISCARD
mdefine_line|#define SC_LINK_DECOMP_DISCARD&t;0x40
DECL|macro|SC_LINK_COMP_DISCARD
mdefine_line|#define SC_LINK_COMP_DISCARD&t;0x80
DECL|macro|DECOMP_ERR_NOMEM
mdefine_line|#define DECOMP_ERR_NOMEM&t;(-10)
DECL|macro|MP_END_FRAG
mdefine_line|#define MP_END_FRAG    0x40
DECL|macro|MP_BEGIN_FRAG
mdefine_line|#define MP_BEGIN_FRAG  0x80
DECL|macro|ISDN_PPP_COMP_MAX_OPTIONS
mdefine_line|#define ISDN_PPP_COMP_MAX_OPTIONS 16
DECL|macro|IPPP_COMP_FLAG_XMIT
mdefine_line|#define IPPP_COMP_FLAG_XMIT 0x1
DECL|macro|IPPP_COMP_FLAG_LINK
mdefine_line|#define IPPP_COMP_FLAG_LINK 0x2
DECL|struct|isdn_ppp_comp_data
r_struct
id|isdn_ppp_comp_data
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
DECL|member|options
r_int
r_char
id|options
(braket
id|ISDN_PPP_COMP_MAX_OPTIONS
)braket
suffix:semicolon
DECL|member|optlen
r_int
id|optlen
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * We need a way for the decompressor to influence the generation of CCP&n; * Reset-Requests in a variety of ways. The decompressor is already returning&n; * a lot of information (generated skb length, error conditions) so we use&n; * another parameter. This parameter is a pointer to a structure which is&n; * to be marked valid by the decompressor and only in this case is ever used.&n; * Furthermore, the only case where this data is used is when the decom-&n; * pressor returns DECOMP_ERROR.&n; *&n; * We use this same struct for the reset entry of the compressor to commu-&n; * nicate to its caller how to deal with sending of a Reset Ack. In this&n; * case, expra is not used, but other options still apply (supressing&n; * sending with rsend, appending arbitrary data, etc).&n; */
DECL|macro|IPPP_RESET_MAXDATABYTES
mdefine_line|#define IPPP_RESET_MAXDATABYTES&t;32
DECL|struct|isdn_ppp_resetparams
r_struct
id|isdn_ppp_resetparams
(brace
DECL|member|valid
r_int
r_char
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is this structure filled at all ? */
DECL|member|rsend
r_int
r_char
id|rsend
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Should we send one at all ? */
DECL|member|idval
r_int
r_char
id|idval
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is the id field valid ? */
DECL|member|dtval
r_int
r_char
id|dtval
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is the data field valid ? */
DECL|member|expra
r_int
r_char
id|expra
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is an Ack expected for this Req ? */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
multiline_comment|/* wo Send CCP ResetReq with this id */
DECL|member|maxdlen
r_int
r_int
id|maxdlen
suffix:semicolon
multiline_comment|/* ro Max bytes to be stored in data field */
DECL|member|dlen
r_int
r_int
id|dlen
suffix:semicolon
multiline_comment|/* rw Bytes stored in data field */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* wo Data for ResetReq info field */
)brace
suffix:semicolon
multiline_comment|/*&n; * this is an &squot;old friend&squot; from ppp-comp.h under a new name &n; * check the original include for more information&n; */
DECL|struct|isdn_ppp_compressor
r_struct
id|isdn_ppp_compressor
(brace
DECL|member|next
DECL|member|prev
r_struct
id|isdn_ppp_compressor
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* CCP compression protocol number */
DECL|member|alloc
r_void
op_star
(paren
op_star
id|alloc
)paren
(paren
r_struct
id|isdn_ppp_comp_data
op_star
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|isdn_ppp_comp_data
op_star
comma
r_int
id|unit
comma
r_int
id|debug
)paren
suffix:semicolon
multiline_comment|/* The reset entry needs to get more exact information about the&n;     ResetReq or ResetAck it was called with. The parameters are&n;     obvious. If reset is called without a Req or Ack frame which&n;     could be handed into it, code MUST be set to 0. Using rsparm,&n;     the reset entry can control if and how a ResetAck is returned. */
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
id|code
comma
r_int
r_char
id|id
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
comma
r_struct
id|isdn_ppp_resetparams
op_star
id|rsparm
)paren
suffix:semicolon
DECL|member|compress
r_int
(paren
op_star
id|compress
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_struct
id|sk_buff
op_star
id|skb_out
comma
r_int
id|proto
)paren
suffix:semicolon
DECL|member|decompress
r_int
(paren
op_star
id|decompress
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_struct
id|sk_buff
op_star
id|skb_out
comma
r_struct
id|isdn_ppp_resetparams
op_star
id|rsparm
)paren
suffix:semicolon
DECL|member|incomp
r_void
(paren
op_star
id|incomp
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_int
id|proto
)paren
suffix:semicolon
DECL|member|stat
r_void
(paren
op_star
id|stat
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|compstat
op_star
id|stats
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|isdn_ppp_register_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_unregister_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_dial_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_hangup_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|struct|ippp_bundle
r_struct
id|ippp_bundle
(brace
DECL|member|mp_mrru
r_int
id|mp_mrru
suffix:semicolon
multiline_comment|/* unused                             */
DECL|member|last
r_struct
id|mpqueue
op_star
id|last
suffix:semicolon
multiline_comment|/* currently defined in isdn_net_dev  */
DECL|member|min
r_int
id|min
suffix:semicolon
multiline_comment|/* currently calculated &squot;on the fly&squot;  */
DECL|member|next_num
r_int
id|next_num
suffix:semicolon
multiline_comment|/* we wanna see this seq.-number next */
DECL|member|sq
r_struct
id|sqqueue
op_star
id|sq
suffix:semicolon
DECL|member|modify
r_int
id|modify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set to 1 while modifying sqqueue   */
DECL|member|bundled
r_int
id|bundled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* bundle active ?                    */
)brace
suffix:semicolon
DECL|macro|NUM_RCV_BUFFS
mdefine_line|#define NUM_RCV_BUFFS     64
DECL|struct|sqqueue
r_struct
id|sqqueue
(brace
DECL|member|next
r_struct
id|sqqueue
op_star
id|next
suffix:semicolon
DECL|member|sqno_start
r_int
id|sqno_start
suffix:semicolon
DECL|member|sqno_end
r_int
id|sqno_end
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|timer
r_int
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpqueue
r_struct
id|mpqueue
(brace
DECL|member|next
r_struct
id|mpqueue
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|mpqueue
op_star
id|last
suffix:semicolon
DECL|member|sqno
r_int
id|sqno
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|BEbyte
r_int
id|BEbyte
suffix:semicolon
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ippp_buf_queue
r_struct
id|ippp_buf_queue
(brace
DECL|member|next
r_struct
id|ippp_buf_queue
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|ippp_buf_queue
op_star
id|last
suffix:semicolon
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* NULL here indicates end of queue */
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The data structure for one CCP reset transaction */
DECL|enum|ippp_ccp_reset_states
r_enum
id|ippp_ccp_reset_states
(brace
DECL|enumerator|CCPResetIdle
id|CCPResetIdle
comma
DECL|enumerator|CCPResetSentReq
id|CCPResetSentReq
comma
DECL|enumerator|CCPResetRcvdReq
id|CCPResetRcvdReq
comma
DECL|enumerator|CCPResetSentAck
id|CCPResetSentAck
comma
DECL|enumerator|CCPResetRcvdAck
id|CCPResetRcvdAck
)brace
suffix:semicolon
DECL|struct|ippp_ccp_reset_state
r_struct
id|ippp_ccp_reset_state
(brace
DECL|member|state
r_enum
id|ippp_ccp_reset_states
id|state
suffix:semicolon
multiline_comment|/* State of this transaction */
DECL|member|is
r_struct
id|ippp_struct
op_star
id|is
suffix:semicolon
multiline_comment|/* Backlink to device stuff */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
multiline_comment|/* Backlink id index */
DECL|member|ta
r_int
r_char
id|ta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The timer is active (flag) */
DECL|member|expra
r_int
r_char
id|expra
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We expect a ResetAck at all */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* Databytes stored in data */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* For timeouts/retries */
multiline_comment|/* This is a hack but seems sufficient for the moment. We do not want&n;     to have this be yet another allocation for some bytes, it is more&n;     memory management overhead than the whole mess is worth. */
DECL|member|data
r_int
r_char
id|data
(braket
id|IPPP_RESET_MAXDATABYTES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The data structure keeping track of the currently outstanding CCP Reset&n;   transactions. */
DECL|struct|ippp_ccp_reset
r_struct
id|ippp_ccp_reset
(brace
DECL|member|rs
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* One per possible id */
DECL|member|lastid
r_int
r_char
id|lastid
suffix:semicolon
multiline_comment|/* Last id allocated by the engine */
)brace
suffix:semicolon
DECL|struct|ippp_struct
r_struct
id|ippp_struct
(brace
DECL|member|next_link
r_struct
id|ippp_struct
op_star
id|next_link
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|rq
r_struct
id|ippp_buf_queue
id|rq
(braket
id|NUM_RCV_BUFFS
)braket
suffix:semicolon
multiline_comment|/* packet queue for isdn_ppp_read() */
DECL|member|first
r_struct
id|ippp_buf_queue
op_star
id|first
suffix:semicolon
multiline_comment|/* pointer to (current) first packet */
DECL|member|last
r_struct
id|ippp_buf_queue
op_star
id|last
suffix:semicolon
multiline_comment|/* pointer to (current) last used packet in queue */
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|tk
r_struct
id|task_struct
op_star
id|tk
suffix:semicolon
DECL|member|mpppcfg
r_int
r_int
id|mpppcfg
suffix:semicolon
DECL|member|pppcfg
r_int
r_int
id|pppcfg
suffix:semicolon
DECL|member|mru
r_int
r_int
id|mru
suffix:semicolon
DECL|member|mpmru
r_int
r_int
id|mpmru
suffix:semicolon
DECL|member|mpmtu
r_int
r_int
id|mpmtu
suffix:semicolon
DECL|member|maxcid
r_int
r_int
id|maxcid
suffix:semicolon
DECL|member|lp
r_struct
id|isdn_net_local_s
op_star
id|lp
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|last_link_seqno
r_int
id|last_link_seqno
suffix:semicolon
DECL|member|mp_seqno
r_int
id|mp_seqno
suffix:semicolon
DECL|member|range
r_int
id|range
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_PPP_VJ
DECL|member|cbuf
r_int
r_char
op_star
id|cbuf
suffix:semicolon
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
macro_line|#endif
DECL|member|debug
r_int
r_int
id|debug
suffix:semicolon
DECL|member|compressor
DECL|member|decompressor
r_struct
id|isdn_ppp_compressor
op_star
id|compressor
comma
op_star
id|decompressor
suffix:semicolon
DECL|member|link_compressor
DECL|member|link_decompressor
r_struct
id|isdn_ppp_compressor
op_star
id|link_compressor
comma
op_star
id|link_decompressor
suffix:semicolon
DECL|member|decomp_stat
DECL|member|comp_stat
DECL|member|link_decomp_stat
DECL|member|link_comp_stat
r_void
op_star
id|decomp_stat
comma
op_star
id|comp_stat
comma
op_star
id|link_decomp_stat
comma
op_star
id|link_comp_stat
suffix:semicolon
DECL|member|reset
r_struct
id|ippp_ccp_reset
op_star
id|reset
suffix:semicolon
multiline_comment|/* Allocated on demand, may never be needed */
DECL|member|compflags
r_int
r_int
id|compflags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_ISDN_PPP_H */
eof
