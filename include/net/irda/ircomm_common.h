multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_common.h&n; * Version:       &n; * Description:   An implementation of IrCOMM service interface and state machine &n; * Status:        Experimental.&n; * Author:        Takahide Higuchi &lt;thiguchi@pluto.dti.ne.jp&gt;&n; *&n; *     Copyright (c) 1998, Takahide Higuchi, &lt;thiguchi@pluto.dti.ne.jp&gt;,&n; *     All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     I, Takahide Higuchi, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
multiline_comment|/* #define DEBUG(n, args...) printk( KERN_DEBUG args) */
multiline_comment|/* enable all debug message */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt; 
r_typedef
r_enum
(brace
DECL|enumerator|COMM_DISCOVERY
id|COMM_DISCOVERY
comma
DECL|enumerator|COMM_IDLE
id|COMM_IDLE
comma
DECL|enumerator|COMM_WAITI
id|COMM_WAITI
comma
DECL|enumerator|COMM_WAITR
id|COMM_WAITR
comma
DECL|enumerator|COMM_CONN
id|COMM_CONN
comma
DECL|typedef|IRCOMM_STATE
)brace
id|IRCOMM_STATE
suffix:semicolon
multiline_comment|/* IrCOMM Events */
r_typedef
r_enum
(brace
DECL|enumerator|IRCOMM_CONNECT_REQUEST
id|IRCOMM_CONNECT_REQUEST
comma
DECL|enumerator|TTP_CONNECT_INDICATION
id|TTP_CONNECT_INDICATION
comma
DECL|enumerator|LMP_CONNECT_INDICATION
id|LMP_CONNECT_INDICATION
comma
DECL|enumerator|TTP_CONNECT_CONFIRM
id|TTP_CONNECT_CONFIRM
comma
DECL|enumerator|TTP_DISCONNECT_INDICATION
id|TTP_DISCONNECT_INDICATION
comma
DECL|enumerator|LMP_CONNECT_CONFIRM
id|LMP_CONNECT_CONFIRM
comma
DECL|enumerator|LMP_DISCONNECT_INDICATION
id|LMP_DISCONNECT_INDICATION
comma
DECL|enumerator|IRCOMM_CONNECT_RESPONSE
id|IRCOMM_CONNECT_RESPONSE
comma
DECL|enumerator|IRCOMM_DISCONNECT_REQUEST
id|IRCOMM_DISCONNECT_REQUEST
comma
DECL|enumerator|TTP_DATA_INDICATION
id|TTP_DATA_INDICATION
comma
DECL|enumerator|IRCOMM_DATA_REQUEST
id|IRCOMM_DATA_REQUEST
comma
DECL|enumerator|LMP_DATA_INDICATION
id|LMP_DATA_INDICATION
comma
DECL|enumerator|IRCOMM_CONTROL_REQUEST
id|IRCOMM_CONTROL_REQUEST
comma
DECL|typedef|IRCOMM_EVENT
)brace
id|IRCOMM_EVENT
suffix:semicolon
DECL|macro|IRCOMM_MAGIC
mdefine_line|#define IRCOMM_MAGIC            0x434f4d4d
DECL|macro|COMM_INIT_CTRL_PARAM
mdefine_line|#define COMM_INIT_CTRL_PARAM    3          /* length of initial control parameters */
DECL|macro|COMM_CTRL_MIN
mdefine_line|#define COMM_CTRL_MIN           1          /* length of clen field */
DECL|macro|COMM_HEADER_SIZE
mdefine_line|#define COMM_HEADER_SIZE        (LAP_HEADER+LMP_HEADER+TTP_HEADER+COMM_CTRL_MIN)
DECL|macro|COMM_DEFAULT_DATA_SIZE
mdefine_line|#define COMM_DEFAULT_DATA_SIZE  64
DECL|macro|IRCOMM_MAX_CONNECTION
mdefine_line|#define IRCOMM_MAX_CONNECTION   1          /* Don&squot;t change */
DECL|macro|IAS_PARAM
mdefine_line|#define IAS_PARAM               1
DECL|macro|CONTROL_CHANNEL
mdefine_line|#define CONTROL_CHANNEL         2
DECL|macro|UNKNOWN
mdefine_line|#define UNKNOWN         0x00            /* not defined yet. */
multiline_comment|/* we use 9wire if servicetype=DEFAULT, but is it good? */
DECL|macro|DEFAULT
mdefine_line|#define DEFAULT         0x0a            /* private number */
DECL|macro|THREE_WIRE_RAW
mdefine_line|#define THREE_WIRE_RAW&t;0x01&t;&t;/* bit 0 */
DECL|macro|THREE_WIRE
mdefine_line|#define THREE_WIRE&t;0x02&t;&t;/* bit 1 */
DECL|macro|NINE_WIRE
mdefine_line|#define NINE_WIRE&t;0x04&t;&t;/* bit 2 */
DECL|macro|CENTRONICS
mdefine_line|#define CENTRONICS&t;0x08&t;&t;/* bit 3 */
DECL|macro|SERIAL
mdefine_line|#define SERIAL&t;&t;0x01&t;&t;/* bit 0 */
DECL|macro|PARALLEL
mdefine_line|#define PARALLEL&t;0x02&t;&t;/* bit 1 */
DECL|macro|SERVICETYPE
mdefine_line|#define SERVICETYPE 0x00
DECL|macro|PORT_TYPE
mdefine_line|#define PORT_TYPE 0x02
DECL|macro|PORT_NAME
mdefine_line|#define PORT_NAME 0x02
DECL|macro|FIXED_PORT_NAME
mdefine_line|#define FIXED_PORT_NAME 0x82
DECL|macro|DATA_RATE
mdefine_line|#define DATA_RATE 0x10
DECL|macro|DATA_FORMAT
mdefine_line|#define DATA_FORMAT 0x11
DECL|macro|FLOW_CONTROL
mdefine_line|#define FLOW_CONTROL 0x12
DECL|macro|XON_XOFF_CHAR
mdefine_line|#define XON_XOFF_CHAR 0x13
DECL|macro|ENQ_ACK_CHAR
mdefine_line|#define ENQ_ACK_CHAR 0x14
DECL|macro|LINESTATUS
mdefine_line|#define LINESTATUS 0x15
DECL|macro|BREAK_SIGNAL
mdefine_line|#define BREAK_SIGNAL 0x16
DECL|macro|DTELINE_STATE
mdefine_line|#define DTELINE_STATE 0x20
DECL|macro|DCELINE_STATE
mdefine_line|#define DCELINE_STATE 0x21
DECL|macro|POLL_FOR_LINE_SETTINGS
mdefine_line|#define POLL_FOR_LINE_SETTINGS 0x22
DECL|macro|STATUS_QUERY
mdefine_line|#define STATUS_QUERY 0x30
DECL|macro|SET_BUSY_TIMEOUT
mdefine_line|#define SET_BUSY_TIMEOUT 0x31
DECL|macro|IEEE1284_MODE_SUPPORT
mdefine_line|#define IEEE1284_MODE_SUPPORT 0x32
DECL|macro|IEEE1284_DEVICEID
mdefine_line|#define IEEE1284_DEVICEID 0x33
DECL|macro|IEEE1284_MODE
mdefine_line|#define IEEE1284_MODE 0x34
DECL|macro|IEEE1284_ECP_EPP_DATA_TRANSFER
mdefine_line|#define IEEE1284_ECP_EPP_DATA_TRANSFER 0x35
DECL|macro|TX_READY
mdefine_line|#define TX_READY 0xFE  /* FIXME: this is not defined in IrCOMM spec */
DECL|macro|TX_BUSY
mdefine_line|#define TX_BUSY  0XFF  /*         so we should find another way */
multiline_comment|/*  parameters of FLOW_CONTROL  */
DECL|macro|USE_RTS
mdefine_line|#define USE_RTS 0x08  /* use RTS on output */
DECL|macro|USE_CTS
mdefine_line|#define USE_CTS 0x04  /* use CTS on input */
DECL|macro|USE_DTR
mdefine_line|#define USE_DTR 0x20  /* use DTR on output */
multiline_comment|/*  parameters of DTELINE_STATE  */
DECL|macro|DELTA_DTR
mdefine_line|#define DELTA_DTR 0x01
DECL|macro|DELTA_RTS
mdefine_line|#define DELTA_RTS 0x02
DECL|macro|MCR_DTR
mdefine_line|#define MCR_DTR 0x04
DECL|macro|MCR_RTS
mdefine_line|#define MCR_RTS 0x08
multiline_comment|/*  parameters of DCELINE_STATE  */
DECL|macro|DELTA_CTS
mdefine_line|#define DELTA_CTS 0x01
DECL|macro|DELTA_DSR
mdefine_line|#define DELTA_DSR 0x02
DECL|macro|DELTA_RI
mdefine_line|#define DELTA_RI  0x04 
DECL|macro|DELTA_DCD
mdefine_line|#define DELTA_DCD 0x08
DECL|macro|MSR_CTS
mdefine_line|#define MSR_CTS   0x10
DECL|macro|MSR_DSR
mdefine_line|#define MSR_DSR   0x20
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI    0x40 
DECL|macro|MSR_DCD
mdefine_line|#define MSR_DCD   0x80
multiline_comment|/*  parameters of DATA_FORMAT */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE     0x02    /* Overrun error indicator */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE     0x04    /* Parity error indicator */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE     0x08    /* Frame error indicator */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI     0x01    /* Break interrupt indicator */
DECL|struct|ircomm_cb
r_struct
id|ircomm_cb
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Current state of IrCOMM layer: &n;&t;&t;&t;     *  DISCOVERY,COMM_IDLE, COMM_WAITR,&n;&t;&t;&t;     *  COMM_WAITI, COMM_CONN&n;&t;&t;&t;     */
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|null_modem_mode
r_int
id|null_modem_mode
suffix:semicolon
multiline_comment|/* switch for null modem emulation */
DECL|member|ttp_stop
r_int
id|ttp_stop
suffix:semicolon
DECL|member|max_txbuff_size
r_int
id|max_txbuff_size
suffix:semicolon
DECL|member|maxsdusize
r_int
id|maxsdusize
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Device address of the peer device */
DECL|member|d_handler
r_void
(paren
op_star
id|d_handler
)paren
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
DECL|member|notify
r_struct
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* container of callbacks */
DECL|member|ctrl_skb
r_struct
id|sk_buff
op_star
id|ctrl_skb
suffix:semicolon
multiline_comment|/* queue of control channel */
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
multiline_comment|/* IrTTP/LMP handle */
DECL|member|qos
r_struct
id|qos_info
op_star
id|qos
suffix:semicolon
multiline_comment|/* Quality of Service */
DECL|member|reason
r_int
id|reason
suffix:semicolon
multiline_comment|/* I don&squot;t know about reason: &n;&t;&t;&t;&t;see Irlmp.c or somewhere :p)*/
DECL|member|dlsap
id|__u8
id|dlsap
suffix:semicolon
multiline_comment|/* IrLMP dlsap */
DECL|member|lsap
id|__u8
id|lsap
suffix:semicolon
multiline_comment|/* sap of local device */
DECL|member|pi
id|__u8
id|pi
suffix:semicolon
multiline_comment|/* instruction of control channel*/
DECL|member|port_type
id|__u8
id|port_type
suffix:semicolon
DECL|member|peer_port_type
id|__u8
id|peer_port_type
suffix:semicolon
DECL|member|servicetype
id|__u8
id|servicetype
suffix:semicolon
DECL|member|peer_servicetype
id|__u8
id|peer_servicetype
suffix:semicolon
DECL|member|data_format
id|__u8
id|data_format
suffix:semicolon
DECL|member|peer_data_format
id|__u8
id|peer_data_format
suffix:semicolon
DECL|member|flow_ctrl
id|__u8
id|flow_ctrl
suffix:semicolon
DECL|member|peer_flow_ctrl
id|__u8
id|peer_flow_ctrl
suffix:semicolon
DECL|member|line_status
id|__u8
id|line_status
suffix:semicolon
DECL|member|peer_line_status
id|__u8
id|peer_line_status
suffix:semicolon
DECL|member|break_signal
id|__u8
id|break_signal
suffix:semicolon
DECL|member|peer_break_signal
id|__u8
id|peer_break_signal
suffix:semicolon
DECL|member|dte
id|__u8
id|dte
suffix:semicolon
DECL|member|peer_dte
id|__u8
id|peer_dte
suffix:semicolon
DECL|member|dce
id|__u8
id|dce
suffix:semicolon
DECL|member|peer_dce
id|__u8
id|peer_dce
suffix:semicolon
DECL|member|xon_char
id|__u8
id|xon_char
suffix:semicolon
DECL|member|xoff_char
id|__u8
id|xoff_char
suffix:semicolon
DECL|member|peer_xon_char
id|__u8
id|peer_xon_char
suffix:semicolon
DECL|member|peer_xoff_char
id|__u8
id|peer_xoff_char
suffix:semicolon
DECL|member|enq_char
id|__u8
id|enq_char
suffix:semicolon
DECL|member|ack_char
id|__u8
id|ack_char
suffix:semicolon
DECL|member|peer_enq_char
id|__u8
id|peer_enq_char
suffix:semicolon
DECL|member|peer_ack_char
id|__u8
id|peer_ack_char
suffix:semicolon
DECL|member|busy_timeout
id|__u8
id|busy_timeout
suffix:semicolon
DECL|member|peer_busy_timeout
id|__u8
id|peer_busy_timeout
suffix:semicolon
DECL|member|ecp_epp_mode
id|__u8
id|ecp_epp_mode
suffix:semicolon
DECL|member|peer_ecp_epp_mode
id|__u8
id|peer_ecp_epp_mode
suffix:semicolon
DECL|member|channel_or_addr
id|__u8
id|channel_or_addr
suffix:semicolon
DECL|member|peer_channel_or_addr
id|__u8
id|peer_channel_or_addr
suffix:semicolon
DECL|member|data_rate
id|__u32
id|data_rate
suffix:semicolon
DECL|member|peer_data_rate
id|__u32
id|peer_data_rate
suffix:semicolon
DECL|member|port_name
r_char
id|port_name
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
r_void
id|ircomm_connect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_int
id|maxsdusize
)paren
suffix:semicolon
r_void
id|ircomm_connect_response
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
comma
r_int
id|maxsdusize
)paren
suffix:semicolon
r_void
id|ircomm_disconnect_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|ircomm_data_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|userdata
)paren
suffix:semicolon
r_void
id|ircomm_control_request
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|ircomm_append_ctrl
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|__u8
id|instruction
)paren
suffix:semicolon
r_struct
id|ircomm_cb
op_star
id|ircomm_attach_cable
c_func
(paren
id|__u8
id|servicetype
comma
r_struct
id|notify_t
id|notify
comma
r_void
op_star
id|handler
)paren
suffix:semicolon
r_int
id|ircomm_detach_cable
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
r_void
id|ircomm_accept_data_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_accept_connect_confirm
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|maxsdusize
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_accept_connect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_int
id|maxsdusize
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_accept_disconnect_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LM_REASON
id|reason
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|ircomm_accept_flow_indication
c_func
(paren
r_void
op_star
id|instance
comma
r_void
op_star
id|sap
comma
id|LOCAL_FLOW
id|flow
)paren
suffix:semicolon
r_void
id|ircomm_next_state
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
comma
id|IRCOMM_STATE
id|state
)paren
suffix:semicolon
eof
