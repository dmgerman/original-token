multiline_comment|/*********************************************************************&n; *                &n; * Filename:      qos.h&n; * Version:       0.1&n; * Description:   Quality of Service definitions&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Sep 19 23:21:09 1997&n; * Modified at:   Wed Dec  9 10:32:47 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli &lt;dagb@cs.uit.no&gt;, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef QOS_H
DECL|macro|QOS_H
mdefine_line|#define QOS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|PI_BAUD_RATE
mdefine_line|#define PI_BAUD_RATE     0x01
DECL|macro|PI_MAX_TURN_TIME
mdefine_line|#define PI_MAX_TURN_TIME 0x82
DECL|macro|PI_DATA_SIZE
mdefine_line|#define PI_DATA_SIZE     0x83
DECL|macro|PI_WINDOW_SIZE
mdefine_line|#define PI_WINDOW_SIZE   0x84
DECL|macro|PI_ADD_BOFS
mdefine_line|#define PI_ADD_BOFS      0x85
DECL|macro|PI_MIN_TURN_TIME
mdefine_line|#define PI_MIN_TURN_TIME 0x86
DECL|macro|PI_LINK_DISC
mdefine_line|#define PI_LINK_DISC     0x08
DECL|macro|PI_COMPRESSION
mdefine_line|#define PI_COMPRESSION   0x07 /* Just a random pick */
DECL|macro|IR_115200_MAX
mdefine_line|#define IR_115200_MAX 0x3f
multiline_comment|/* Baud rates (first byte) */
DECL|macro|IR_2400
mdefine_line|#define IR_2400    0x01
DECL|macro|IR_9600
mdefine_line|#define IR_9600    0x02
DECL|macro|IR_19200
mdefine_line|#define IR_19200   0x04
DECL|macro|IR_38400
mdefine_line|#define IR_38400   0x08
DECL|macro|IR_57600
mdefine_line|#define IR_57600   0x10
DECL|macro|IR_115200
mdefine_line|#define IR_115200  0x20
DECL|macro|IR_576000
mdefine_line|#define IR_576000  0x40
DECL|macro|IR_1152000
mdefine_line|#define IR_1152000 0x80
multiline_comment|/* Baud rates (second byte) */
DECL|macro|IR_4000000
mdefine_line|#define IR_4000000 0x01
multiline_comment|/* Quality of Service information */
r_typedef
r_struct
(brace
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|member|bits
id|__u16
id|bits
suffix:semicolon
multiline_comment|/* LSB is first byte, MSB is second byte */
DECL|typedef|qos_value_t
)brace
id|qos_value_t
suffix:semicolon
DECL|struct|qos_info
r_struct
id|qos_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_rate
id|qos_value_t
id|baud_rate
suffix:semicolon
multiline_comment|/* IR_11520O | ... */
DECL|member|max_turn_time
id|qos_value_t
id|max_turn_time
suffix:semicolon
DECL|member|data_size
id|qos_value_t
id|data_size
suffix:semicolon
DECL|member|window_size
id|qos_value_t
id|window_size
suffix:semicolon
DECL|member|additional_bofs
id|qos_value_t
id|additional_bofs
suffix:semicolon
DECL|member|min_turn_time
id|qos_value_t
id|min_turn_time
suffix:semicolon
DECL|member|link_disc_time
id|qos_value_t
id|link_disc_time
suffix:semicolon
DECL|member|power
id|qos_value_t
id|power
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA_COMPRESSION
multiline_comment|/* An experimental non IrDA field */
DECL|member|compression
id|qos_value_t
id|compression
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_int
id|baud_rates
(braket
)braket
suffix:semicolon
r_extern
r_int
id|data_size
(braket
)braket
suffix:semicolon
r_extern
r_int
id|min_turn_time
(braket
)braket
suffix:semicolon
r_extern
r_int
id|add_bofs
(braket
)braket
suffix:semicolon
r_extern
r_int
id|compression
(braket
)braket
suffix:semicolon
r_void
id|irda_init_max_qos_capabilies
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
r_void
id|irda_qos_compute_intersection
c_func
(paren
r_struct
id|qos_info
op_star
comma
r_struct
id|qos_info
op_star
)paren
suffix:semicolon
r_int
id|irda_insert_qos_negotiation_params
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
comma
id|__u8
op_star
id|fp
)paren
suffix:semicolon
r_void
id|irda_qos_negotiate
c_func
(paren
r_struct
id|qos_info
op_star
id|qos_rx
comma
r_struct
id|qos_info
op_star
id|qos_tx
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|msb_index
(paren
id|__u16
id|byte
)paren
suffix:semicolon
r_int
id|byte_value
c_func
(paren
id|__u8
id|byte
comma
r_int
op_star
id|array
)paren
suffix:semicolon
r_int
id|value_index
c_func
(paren
r_int
id|value
comma
r_int
op_star
id|array
)paren
suffix:semicolon
r_int
id|index_value
c_func
(paren
r_int
id|index
comma
r_int
op_star
id|array
)paren
suffix:semicolon
r_void
id|irda_qos_bits_to_value
c_func
(paren
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
macro_line|#endif
eof
