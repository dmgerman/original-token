multiline_comment|/*********************************************************************&n; *                &n; * Filename:      ircomm_common.h&n; * Version:       &n; * Description:   An implementation of IrCOMM service interface and state machine &n; * Status:        Experimental.&n; * Author:        Takahide Higuchi &lt;thiguchi@pluto.dti.ne.jp&gt;&n; *&n; *     Copyright (c) 1998, Takahide Higuchi, &lt;thiguchi@pluto.dti.ne.jp&gt;,&n; *     All Rights Reserved.&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     I, Takahide Higuchi, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRCOMM_H
DECL|macro|IRCOMM_H
mdefine_line|#define IRCOMM_H
multiline_comment|/* #define DEBUG(n, args...) printk( KERN_DEBUG args) */
multiline_comment|/* enable all debug message */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt; 
r_typedef
r_enum
(brace
DECL|enumerator|COMM_IDLE
id|COMM_IDLE
comma
DECL|enumerator|COMM_DISCOVERY_WAIT
id|COMM_DISCOVERY_WAIT
comma
DECL|enumerator|COMM_QUERYPARAM_WAIT
id|COMM_QUERYPARAM_WAIT
comma
DECL|enumerator|COMM_QUERYLSAP_WAIT
id|COMM_QUERYLSAP_WAIT
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
DECL|enumerator|DISCOVERY_INDICATION
id|DISCOVERY_INDICATION
comma
DECL|enumerator|GOT_PARAMETERS
id|GOT_PARAMETERS
comma
DECL|enumerator|GOT_LSAPSEL
id|GOT_LSAPSEL
comma
DECL|enumerator|QUERYIAS_ERROR
id|QUERYIAS_ERROR
comma
DECL|typedef|IRCOMM_EVENT
)brace
id|IRCOMM_EVENT
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|TX_READY
id|TX_READY
comma
DECL|enumerator|TX_BUSY
id|TX_BUSY
comma
DECL|enumerator|IAS_PARAM
id|IAS_PARAM
comma
DECL|enumerator|CONTROL_CHANNEL
id|CONTROL_CHANNEL
comma
DECL|typedef|IRCOMM_CMD
)brace
id|IRCOMM_CMD
suffix:semicolon
DECL|macro|IRCOMM_MAGIC
mdefine_line|#define IRCOMM_MAGIC            0x434f4d4d
DECL|macro|COMM_INIT_CTRL_PARAM
mdefine_line|#define COMM_INIT_CTRL_PARAM    3          /* length of initial control parameters */
DECL|macro|COMM_HEADER
mdefine_line|#define COMM_HEADER             1          /* length of clen field */
DECL|macro|COMM_HEADER_SIZE
mdefine_line|#define COMM_HEADER_SIZE        (LAP_HEADER+LMP_HEADER+TTP_HEADER+COMM_HEADER)
DECL|macro|COMM_DEFAULT_DATA_SIZE
mdefine_line|#define COMM_DEFAULT_DATA_SIZE  64
DECL|macro|IRCOMM_MAX_CONNECTION
mdefine_line|#define IRCOMM_MAX_CONNECTION   1          /* Don&squot;t change for now */
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
mdefine_line|#define PORT_TYPE 0x01
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
DECL|macro|IRCOMM_WLEN5
mdefine_line|#define IRCOMM_WLEN5   0x00       /* word length is 5bit */
DECL|macro|IRCOMM_WLEN6
mdefine_line|#define IRCOMM_WLEN6   0x01       /* word length is 6bit */
DECL|macro|IRCOMM_WLEN7
mdefine_line|#define IRCOMM_WLEN7   0x02       /* word length is 7bit */
DECL|macro|IRCOMM_WLEN8
mdefine_line|#define IRCOMM_WLEN8   0x03       /* word length is 8bit */
DECL|macro|IRCOMM_STOP2
mdefine_line|#define IRCOMM_STOP2   0x04       /* 2 stop bits mode */
DECL|macro|IRCOMM_PARENB
mdefine_line|#define IRCOMM_PARENB  0x08       /* parity enable */
DECL|macro|IRCOMM_PARODD
mdefine_line|#define IRCOMM_PARODD  0x00       /*  odd parity */
DECL|macro|IRCOMM_PAREVEN
mdefine_line|#define IRCOMM_PAREVEN 0x10       /*  even parity */
DECL|macro|IRCOMM_PARMARK
mdefine_line|#define IRCOMM_PARMARK 0x20
DECL|macro|IRCOMM_PARSPC
mdefine_line|#define IRCOMM_PARSPC  0x30
multiline_comment|/*  parameters of LINE_STATUS */
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
id|__u32
id|maxsdusize
suffix:semicolon
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* Device address of the peer device */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
DECL|member|skey
id|__u32
id|skey
suffix:semicolon
DECL|member|ckey
id|__u32
id|ckey
suffix:semicolon
DECL|member|queryias_lock
r_int
id|queryias_lock
suffix:semicolon
DECL|member|ias_type
r_int
id|ias_type
suffix:semicolon
DECL|member|disconnect_priority
r_int
id|disconnect_priority
suffix:semicolon
multiline_comment|/* P_NORMAL or P_HIGH. see irttp.h */
DECL|member|notify
r_struct
id|notify_t
id|notify
suffix:semicolon
multiline_comment|/* container of callbacks */
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
DECL|member|control_ch_pending
r_int
id|control_ch_pending
suffix:semicolon
DECL|member|ctrl_skb
r_struct
id|sk_buff
op_star
id|ctrl_skb
suffix:semicolon
multiline_comment|/* queue of control channel */
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
DECL|member|peer_cap
r_int
id|peer_cap
suffix:semicolon
multiline_comment|/* capability of peer device */
DECL|member|discovery_wait
id|wait_queue_head_t
id|discovery_wait
suffix:semicolon
DECL|member|ias_wait
id|wait_queue_head_t
id|ias_wait
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|tx_packets
r_int
id|tx_packets
suffix:semicolon
DECL|member|rx_packets
r_int
id|rx_packets
suffix:semicolon
DECL|member|tx_controls
r_int
id|tx_controls
suffix:semicolon
DECL|member|pending_control_tuples
r_int
id|pending_control_tuples
suffix:semicolon
DECL|member|ignored_control_tuples
r_int
id|ignored_control_tuples
suffix:semicolon
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
l_int|33
)braket
suffix:semicolon
DECL|member|port_name_critical
r_int
id|port_name_critical
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
id|__u8
id|servicetype
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
id|__u32
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
comma
r_int
id|priority
)paren
suffix:semicolon
r_int
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
comma
id|__u8
id|instruction
)paren
suffix:semicolon
r_void
id|ircomm_parse_tuples
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
id|skb
comma
r_int
id|type
)paren
suffix:semicolon
r_struct
id|ircomm_cb
op_star
id|ircomm_open_instance
c_func
(paren
r_struct
id|notify_t
id|notify
)paren
suffix:semicolon
r_int
id|ircomm_close_instance
c_func
(paren
r_struct
id|ircomm_cb
op_star
id|self
)paren
suffix:semicolon
macro_line|#endif
eof
