multiline_comment|/*&n; *&t;Declarations of X.25 Packet Layer type objects.&n; *&n; * &t;History&n; *&t;nov/17/96&t;Jonathan Naylor&t;  Initial version.&t;&t;&n; *&t;mar/20/00&t;Daniela Squassoni Disabling/enabling of facilities &n; *&t;&t;&t;&t;&t;  negotiation.&n; */
macro_line|#ifndef _X25_H
DECL|macro|_X25_H
mdefine_line|#define _X25_H 
macro_line|#include &lt;linux/x25.h&gt;
DECL|macro|X25_ADDR_LEN
mdefine_line|#define&t;X25_ADDR_LEN&t;&t;&t;16
DECL|macro|X25_MAX_L2_LEN
mdefine_line|#define&t;X25_MAX_L2_LEN&t;&t;&t;18&t;/* 802.2 LLC */
DECL|macro|X25_STD_MIN_LEN
mdefine_line|#define&t;X25_STD_MIN_LEN&t;&t;&t;3
DECL|macro|X25_EXT_MIN_LEN
mdefine_line|#define&t;X25_EXT_MIN_LEN&t;&t;&t;4
DECL|macro|X25_GFI_SEQ_MASK
mdefine_line|#define&t;X25_GFI_SEQ_MASK&t;&t;0x30
DECL|macro|X25_GFI_STDSEQ
mdefine_line|#define&t;X25_GFI_STDSEQ&t;&t;&t;0x10
DECL|macro|X25_GFI_EXTSEQ
mdefine_line|#define&t;X25_GFI_EXTSEQ&t;&t;&t;0x20
DECL|macro|X25_Q_BIT
mdefine_line|#define&t;X25_Q_BIT&t;&t;&t;0x80
DECL|macro|X25_D_BIT
mdefine_line|#define&t;X25_D_BIT&t;&t;&t;0x40
DECL|macro|X25_STD_M_BIT
mdefine_line|#define&t;X25_STD_M_BIT&t;&t;&t;0x10
DECL|macro|X25_EXT_M_BIT
mdefine_line|#define&t;X25_EXT_M_BIT&t;&t;&t;0x01
DECL|macro|X25_CALL_REQUEST
mdefine_line|#define&t;X25_CALL_REQUEST&t;&t;0x0B
DECL|macro|X25_CALL_ACCEPTED
mdefine_line|#define&t;X25_CALL_ACCEPTED&t;&t;0x0F
DECL|macro|X25_CLEAR_REQUEST
mdefine_line|#define&t;X25_CLEAR_REQUEST&t;&t;0x13
DECL|macro|X25_CLEAR_CONFIRMATION
mdefine_line|#define&t;X25_CLEAR_CONFIRMATION&t;&t;0x17
DECL|macro|X25_DATA
mdefine_line|#define&t;X25_DATA&t;&t;&t;0x00
DECL|macro|X25_INTERRUPT
mdefine_line|#define&t;X25_INTERRUPT&t;&t;&t;0x23
DECL|macro|X25_INTERRUPT_CONFIRMATION
mdefine_line|#define&t;X25_INTERRUPT_CONFIRMATION&t;0x27
DECL|macro|X25_RR
mdefine_line|#define&t;X25_RR&t;&t;&t;&t;0x01
DECL|macro|X25_RNR
mdefine_line|#define&t;X25_RNR&t;&t;&t;&t;0x05
DECL|macro|X25_REJ
mdefine_line|#define&t;X25_REJ&t;&t;&t;&t;0x09
DECL|macro|X25_RESET_REQUEST
mdefine_line|#define&t;X25_RESET_REQUEST&t;&t;0x1B
DECL|macro|X25_RESET_CONFIRMATION
mdefine_line|#define&t;X25_RESET_CONFIRMATION&t;&t;0x1F
DECL|macro|X25_REGISTRATION_REQUEST
mdefine_line|#define&t;X25_REGISTRATION_REQUEST&t;0xF3
DECL|macro|X25_REGISTRATION_CONFIRMATION
mdefine_line|#define&t;X25_REGISTRATION_CONFIRMATION&t;0xF7
DECL|macro|X25_RESTART_REQUEST
mdefine_line|#define&t;X25_RESTART_REQUEST&t;&t;0xFB
DECL|macro|X25_RESTART_CONFIRMATION
mdefine_line|#define&t;X25_RESTART_CONFIRMATION&t;0xFF
DECL|macro|X25_DIAGNOSTIC
mdefine_line|#define&t;X25_DIAGNOSTIC&t;&t;&t;0xF1
DECL|macro|X25_ILLEGAL
mdefine_line|#define&t;X25_ILLEGAL&t;&t;&t;0xFD
multiline_comment|/* Define the various conditions that may exist */
DECL|macro|X25_COND_ACK_PENDING
mdefine_line|#define&t;X25_COND_ACK_PENDING&t;0x01
DECL|macro|X25_COND_OWN_RX_BUSY
mdefine_line|#define&t;X25_COND_OWN_RX_BUSY&t;0x02
DECL|macro|X25_COND_PEER_RX_BUSY
mdefine_line|#define&t;X25_COND_PEER_RX_BUSY&t;0x04
multiline_comment|/* Define Link State constants. */
r_enum
(brace
DECL|enumerator|X25_STATE_0
id|X25_STATE_0
comma
multiline_comment|/* Ready */
DECL|enumerator|X25_STATE_1
id|X25_STATE_1
comma
multiline_comment|/* Awaiting Call Accepted */
DECL|enumerator|X25_STATE_2
id|X25_STATE_2
comma
multiline_comment|/* Awaiting Clear Confirmation */
DECL|enumerator|X25_STATE_3
id|X25_STATE_3
comma
multiline_comment|/* Data Transfer */
DECL|enumerator|X25_STATE_4
id|X25_STATE_4
multiline_comment|/* Awaiting Reset Confirmation */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|X25_LINK_STATE_0
id|X25_LINK_STATE_0
comma
DECL|enumerator|X25_LINK_STATE_1
id|X25_LINK_STATE_1
comma
DECL|enumerator|X25_LINK_STATE_2
id|X25_LINK_STATE_2
comma
DECL|enumerator|X25_LINK_STATE_3
id|X25_LINK_STATE_3
)brace
suffix:semicolon
DECL|macro|X25_DEFAULT_T20
mdefine_line|#define X25_DEFAULT_T20&t;&t;(180 * HZ)&t;&t;/* Default T20 value */
DECL|macro|X25_DEFAULT_T21
mdefine_line|#define X25_DEFAULT_T21&t;&t;(200 * HZ)&t;&t;/* Default T21 value */
DECL|macro|X25_DEFAULT_T22
mdefine_line|#define X25_DEFAULT_T22&t;&t;(180 * HZ)&t;&t;/* Default T22 value */
DECL|macro|X25_DEFAULT_T23
mdefine_line|#define&t;X25_DEFAULT_T23&t;&t;(180 * HZ)&t;&t;/* Default T23 value */
DECL|macro|X25_DEFAULT_T2
mdefine_line|#define&t;X25_DEFAULT_T2&t;&t;(3   * HZ)&t;&t;/* Default ack holdback value */
DECL|macro|X25_DEFAULT_WINDOW_SIZE
mdefine_line|#define&t;X25_DEFAULT_WINDOW_SIZE&t;2&t;&t;&t;/* Default Window Size&t;*/
DECL|macro|X25_DEFAULT_PACKET_SIZE
mdefine_line|#define&t;X25_DEFAULT_PACKET_SIZE&t;X25_PS128&t;&t;/* Default Packet Size */
DECL|macro|X25_DEFAULT_THROUGHPUT
mdefine_line|#define&t;X25_DEFAULT_THROUGHPUT&t;0x0A&t;&t;&t;/* Deafult Throughput */
DECL|macro|X25_DEFAULT_REVERSE
mdefine_line|#define&t;X25_DEFAULT_REVERSE&t;0x00&t;&t;&t;/* Default Reverse Charging */
DECL|macro|X25_SMODULUS
mdefine_line|#define X25_SMODULUS &t;&t;8
DECL|macro|X25_EMODULUS
mdefine_line|#define&t;X25_EMODULUS&t;&t;128
multiline_comment|/*&n; *&t;X.25 Facilities constants.&n; */
DECL|macro|X25_FAC_CLASS_MASK
mdefine_line|#define&t;X25_FAC_CLASS_MASK&t;0xC0
DECL|macro|X25_FAC_CLASS_A
mdefine_line|#define&t;X25_FAC_CLASS_A&t;&t;0x00
DECL|macro|X25_FAC_CLASS_B
mdefine_line|#define&t;X25_FAC_CLASS_B&t;&t;0x40
DECL|macro|X25_FAC_CLASS_C
mdefine_line|#define&t;X25_FAC_CLASS_C&t;&t;0x80
DECL|macro|X25_FAC_CLASS_D
mdefine_line|#define&t;X25_FAC_CLASS_D&t;&t;0xC0
DECL|macro|X25_FAC_REVERSE
mdefine_line|#define&t;X25_FAC_REVERSE&t;&t;0x01
DECL|macro|X25_FAC_THROUGHPUT
mdefine_line|#define&t;X25_FAC_THROUGHPUT&t;0x02
DECL|macro|X25_FAC_PACKET_SIZE
mdefine_line|#define&t;X25_FAC_PACKET_SIZE&t;0x42
DECL|macro|X25_FAC_WINDOW_SIZE
mdefine_line|#define&t;X25_FAC_WINDOW_SIZE&t;0x43
DECL|macro|X25_MAX_FAC_LEN
mdefine_line|#define&t;X25_MAX_FAC_LEN&t;&t;20&t;&t;/* Plenty to spare */
DECL|macro|X25_MAX_CUD_LEN
mdefine_line|#define&t;X25_MAX_CUD_LEN&t;&t;128
DECL|struct|x25_route
r_struct
id|x25_route
(brace
DECL|member|next
r_struct
id|x25_route
op_star
id|next
suffix:semicolon
DECL|member|address
id|x25_address
id|address
suffix:semicolon
multiline_comment|/* Start of address range */
DECL|member|sigdigits
r_int
r_int
id|sigdigits
suffix:semicolon
multiline_comment|/* Number of sig digits */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* More than one for MLP */
)brace
suffix:semicolon
DECL|struct|x25_neigh
r_struct
id|x25_neigh
(brace
DECL|member|next
r_struct
id|x25_neigh
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|extended
r_int
r_int
id|extended
suffix:semicolon
DECL|member|queue
r_struct
id|sk_buff_head
id|queue
suffix:semicolon
DECL|member|t20
r_int
r_int
id|t20
suffix:semicolon
DECL|member|t20timer
r_struct
id|timer_list
id|t20timer
suffix:semicolon
DECL|member|global_facil_mask
r_int
r_int
id|global_facil_mask
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|source_addr
DECL|member|dest_addr
id|x25_address
id|source_addr
comma
id|dest_addr
suffix:semicolon
DECL|member|neighbour
r_struct
id|x25_neigh
op_star
id|neighbour
suffix:semicolon
DECL|member|lci
r_int
r_int
id|lci
suffix:semicolon
DECL|member|state
DECL|member|condition
DECL|member|qbitincl
DECL|member|intflag
r_int
r_char
id|state
comma
id|condition
comma
id|qbitincl
comma
id|intflag
suffix:semicolon
DECL|member|vs
DECL|member|vr
DECL|member|va
DECL|member|vl
r_int
r_int
id|vs
comma
id|vr
comma
id|va
comma
id|vl
suffix:semicolon
DECL|member|t2
DECL|member|t21
DECL|member|t22
DECL|member|t23
r_int
r_int
id|t2
comma
id|t21
comma
id|t22
comma
id|t23
suffix:semicolon
DECL|member|fraglen
r_int
r_int
id|fraglen
suffix:semicolon
DECL|member|ack_queue
r_struct
id|sk_buff_head
id|ack_queue
suffix:semicolon
DECL|member|fragment_queue
r_struct
id|sk_buff_head
id|fragment_queue
suffix:semicolon
DECL|member|interrupt_in_queue
r_struct
id|sk_buff_head
id|interrupt_in_queue
suffix:semicolon
DECL|member|interrupt_out_queue
r_struct
id|sk_buff_head
id|interrupt_out_queue
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
multiline_comment|/* Backlink to socket */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|causediag
r_struct
id|x25_causediag
id|causediag
suffix:semicolon
DECL|member|facilities
r_struct
id|x25_facilities
id|facilities
suffix:semicolon
DECL|member|calluserdata
r_struct
id|x25_calluserdata
id|calluserdata
suffix:semicolon
DECL|member|vc_facil_mask
r_int
r_int
id|vc_facil_mask
suffix:semicolon
multiline_comment|/* inc_call facilities mask */
DECL|typedef|x25_cb
)brace
id|x25_cb
suffix:semicolon
multiline_comment|/* af_x25.c */
r_extern
r_int
id|sysctl_x25_restart_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_x25_call_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_x25_reset_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_x25_clear_request_timeout
suffix:semicolon
r_extern
r_int
id|sysctl_x25_ack_holdback_timeout
suffix:semicolon
r_extern
r_int
id|x25_addr_ntoa
c_func
(paren
r_int
r_char
op_star
comma
id|x25_address
op_star
comma
id|x25_address
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_addr_aton
c_func
(paren
r_int
r_char
op_star
comma
id|x25_address
op_star
comma
id|x25_address
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|x25_new_lci
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|x25_find_socket
c_func
(paren
r_int
r_int
comma
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_destroy_socket
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_rx_call_request
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|x25_neigh
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|x25_kill_by_neigh
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
macro_line|#include &lt;net/x25call.h&gt;
multiline_comment|/* x25_dev.c */
r_extern
r_void
id|x25_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_lapb_receive_frame
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_llc_receive_frame
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
comma
r_struct
id|packet_type
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_establish_link
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_terminate_link
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
multiline_comment|/* x25_facilities.c */
r_extern
r_int
id|x25_parse_facilities
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|x25_facilities
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_create_facilities
c_func
(paren
r_int
r_char
op_star
comma
r_struct
id|x25_facilities
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|x25_negotiate_facilities
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|sock
op_star
comma
r_struct
id|x25_facilities
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_limit_facilities
c_func
(paren
r_struct
id|x25_facilities
op_star
comma
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
multiline_comment|/* x25_in.c */
r_extern
r_int
id|x25_process_rx_frame
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* x25_link.c */
r_extern
r_void
id|x25_link_control
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|x25_neigh
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|x25_link_device_up
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_link_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_link_established
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_link_terminated
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_transmit_restart_request
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_transmit_restart_confirmation
c_func
(paren
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_transmit_diagnostic
c_func
(paren
r_struct
id|x25_neigh
op_star
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|x25_transmit_clear_request
c_func
(paren
r_struct
id|x25_neigh
op_star
comma
r_int
r_int
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|x25_transmit_link
c_func
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|x25_neigh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_subscr_ioctl
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|x25_neigh
op_star
id|x25_get_neigh
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_link_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* x25_out.c */
r_extern
r_int
id|x25_output
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_kick
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_enquiry_response
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
multiline_comment|/* x25_route.c */
r_extern
r_struct
id|net_device
op_star
id|x25_get_route
c_func
(paren
id|x25_address
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|net_device
op_star
id|x25_dev_get
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_route_device_down
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_route_ioctl
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_routes_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|x25_route_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* x25_subr.c */
r_extern
r_void
id|x25_clear_queues
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_frames_acked
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|x25_requeue_frames
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x25_validate_nr
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|x25_write_internal
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|x25_decode
c_func
(paren
r_struct
id|sock
op_star
comma
r_struct
id|sk_buff
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_disconnect
c_func
(paren
r_struct
id|sock
op_star
comma
r_int
comma
r_int
r_char
comma
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/* x25_timer.c */
r_extern
r_void
id|x25_start_heartbeat
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_start_t2timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_start_t21timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_start_t22timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_start_t23timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_stop_heartbeat
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x25_stop_timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|x25_display_timer
c_func
(paren
r_struct
id|sock
op_star
)paren
suffix:semicolon
multiline_comment|/* sysctl_net_x25.c */
r_extern
r_void
id|x25_register_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|x25_unregister_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
