multiline_comment|/*********************************************************************&n; *                &n; * Filename:      smc-ircc.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Thomas Davis (tadavis@jps.net)&n; *&n; *     Copyright (c) 1998, 1999 Thomas Davis (tadavis@jps.net&gt;&n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     I, Thomas Davis, admit no liability nor provide warranty for any&n; *     of this software. This material is provided &quot;AS-IS&quot; and at no charge.&n; *     &n; * Definitions for the SMC IrCC controller.&n; *&n; ********************************************************************/
macro_line|#include &lt;net/irda/irport.h&gt;
macro_line|#ifndef SMC_IRCC_H
DECL|macro|SMC_IRCC_H
mdefine_line|#define SMC_IRCC_H
DECL|macro|UART_MASTER
mdefine_line|#define UART_MASTER&t;&t;&t;0x07
DECL|macro|UART_MASTER_POWERDOWN
mdefine_line|#define UART_MASTER_POWERDOWN&t;1&lt;&lt;7
DECL|macro|UART_MASTER_RESET
mdefine_line|#define UART_MASTER_RESET&t;&t;1&lt;&lt;6
DECL|macro|UART_MASTER_INT_EN
mdefine_line|#define UART_MASTER_INT_EN&t;&t;1&lt;&lt;5
DECL|macro|UART_MASTER_ERROR_RESET
mdefine_line|#define UART_MASTER_ERROR_RESET&t;1&lt;&lt;4
multiline_comment|/* Register block 0 */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0x01
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;0x02
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;0x03
DECL|macro|UART_LCR_A
mdefine_line|#define UART_LCR_A&t;0x04
DECL|macro|UART_LCR_B
mdefine_line|#define UART_LCR_B&t;0x05
DECL|macro|UART_BSR
mdefine_line|#define UART_BSR&t;0x06
DECL|macro|UART_IIR_ACTIVE_FRAME
mdefine_line|#define UART_IIR_ACTIVE_FRAME&t;1&lt;&lt;7
DECL|macro|UART_IIR_EOM
mdefine_line|#define UART_IIR_EOM &t;&t;1&lt;&lt;6
DECL|macro|UART_IIR_RAW_MODE
mdefine_line|#define UART_IIR_RAW_MODE&t;&t;1&lt;&lt;5
DECL|macro|UART_IIR_FIFO
mdefine_line|#define UART_IIR_FIFO&t;&t;1&lt;&lt;4
DECL|macro|UART_IER_ACTIVE_FRAME
mdefine_line|#define UART_IER_ACTIVE_FRAME&t;1&lt;&lt;7
DECL|macro|UART_IER_EOM
mdefine_line|#define UART_IER_EOM &t;&t;1&lt;&lt;6
DECL|macro|UART_IER_RAW_MODE
mdefine_line|#define UART_IER_RAW_MODE&t;&t;1&lt;&lt;5
DECL|macro|UART_IER_FIFO
mdefine_line|#define UART_IER_FIFO&t;&t;1&lt;&lt;4
DECL|macro|UART_LSR_UNDERRUN
mdefine_line|#define UART_LSR_UNDERRUN&t;&t;1&lt;&lt;7
DECL|macro|UART_LSR_OVERRUN
mdefine_line|#define UART_LSR_OVERRUN&t;&t;1&lt;&lt;6
DECL|macro|UART_LSR_FRAME_ERROR
mdefine_line|#define UART_LSR_FRAME_ERROR &t;1&lt;&lt;5
DECL|macro|UART_LSR_SIZE_ERROR
mdefine_line|#define UART_LSR_SIZE_ERROR&t;&t;1&lt;&lt;4
DECL|macro|UART_LSR_CRC_ERROR
mdefine_line|#define UART_LSR_CRC_ERROR&t;&t;1&lt;&lt;3
DECL|macro|UART_LSR_FRAME_ABORT
mdefine_line|#define UART_LSR_FRAME_ABORT &t;1&lt;&lt;2
DECL|macro|UART_LCR_A_FIFO_RESET
mdefine_line|#define UART_LCR_A_FIFO_RESET        1&lt;&lt;7
DECL|macro|UART_LCR_A_FAST
mdefine_line|#define UART_LCR_A_FAST              1&lt;&lt;6
DECL|macro|UART_LCR_A_GP_DATA
mdefine_line|#define UART_LCR_A_GP_DATA           1&lt;&lt;5
DECL|macro|UART_LCR_A_RAW_TX
mdefine_line|#define UART_LCR_A_RAW_TX            1&lt;&lt;4
DECL|macro|UART_LCR_A_RAW_RX
mdefine_line|#define UART_LCR_A_RAW_RX            1&lt;&lt;3
DECL|macro|UART_LCR_A_ABORT
mdefine_line|#define UART_LCR_A_ABORT             1&lt;&lt;2
DECL|macro|UART_LCR_A_DATA_DONE
mdefine_line|#define UART_LCR_A_DATA_DONE         1&lt;&lt;1
DECL|macro|UART_LCR_B_SCE_DISABLED
mdefine_line|#define UART_LCR_B_SCE_DISABLED &t;0x00&lt;&lt;6
DECL|macro|UART_LCR_B_SCE_TRANSMIT
mdefine_line|#define UART_LCR_B_SCE_TRANSMIT &t;0x01&lt;&lt;6
DECL|macro|UART_LCR_B_SCE_RECEIVE
mdefine_line|#define UART_LCR_B_SCE_RECEIVE&t;&t;0x02&lt;&lt;6
DECL|macro|UART_LCR_B_SCE_UNDEFINED
mdefine_line|#define UART_LCR_B_SCE_UNDEFINED&t;0x03&lt;&lt;6
DECL|macro|UART_LCR_B_SIP_ENABLE
mdefine_line|#define UART_LCR_B_SIP_ENABLE&t;&t;1&lt;&lt;5
DECL|macro|UART_LCR_B_BRICK_WALL
mdefine_line|#define UART_LCR_B_BRICK_WALL&t;&t;1&lt;&lt;4
DECL|macro|UART_BSR_NOT_EMPTY
mdefine_line|#define UART_BSR_NOT_EMPTY&t;1&lt;&lt;7
DECL|macro|UART_BSR_FIFO_FULL
mdefine_line|#define UART_BSR_FIFO_FULL&t;1&lt;&lt;6
DECL|macro|UART_BSR_TIMEOUT
mdefine_line|#define UART_BSR_TIMEOUT&t;1&lt;&lt;5
multiline_comment|/* Register block 1 */
DECL|macro|UART_SCE_CFGA
mdefine_line|#define UART_SCE_CFGA&t;0x00
DECL|macro|UART_SCE_CFGB
mdefine_line|#define UART_SCE_CFGB&t;0x01
DECL|macro|UART_FIFO_THRESHOLD
mdefine_line|#define UART_FIFO_THRESHOLD&t;0x02
DECL|macro|UART_CFGA_AUX_IR
mdefine_line|#define UART_CFGA_AUX_IR&t;0x01&lt;&lt;7
DECL|macro|UART_CFGA_HALF_DUPLEX
mdefine_line|#define UART_CFGA_HALF_DUPLEX&t;0x01&lt;&lt;2
DECL|macro|UART_CFGA_TX_POLARITY
mdefine_line|#define UART_CFGA_TX_POLARITY&t;0x01&lt;&lt;1
DECL|macro|UART_CFGA_RX_POLARITY
mdefine_line|#define UART_CFGA_RX_POLARITY&t;0x01
DECL|macro|UART_CFGA_COM
mdefine_line|#define UART_CFGA_COM&t;&t;0x00&lt;&lt;3
DECL|macro|UART_CFGA_IRDA_SIR_A
mdefine_line|#define UART_CFGA_IRDA_SIR_A&t;0x01&lt;&lt;3
DECL|macro|UART_CFGA_ASK_SIR
mdefine_line|#define UART_CFGA_ASK_SIR&t;0x02&lt;&lt;3
DECL|macro|UART_CFGA_IRDA_SIR_B
mdefine_line|#define UART_CFGA_IRDA_SIR_B&t;0x03&lt;&lt;3
DECL|macro|UART_CFGA_IRDA_HDLC
mdefine_line|#define UART_CFGA_IRDA_HDLC &t;0x04&lt;&lt;3
DECL|macro|UART_CFGA_IRDA_4PPM
mdefine_line|#define UART_CFGA_IRDA_4PPM &t;0x05&lt;&lt;3
DECL|macro|UART_CFGA_CONSUMER
mdefine_line|#define UART_CFGA_CONSUMER&t;0x06&lt;&lt;3
DECL|macro|UART_CFGA_RAW_IR
mdefine_line|#define UART_CFGA_RAW_IR&t;0x07&lt;&lt;3
DECL|macro|UART_CFGA_OTHER
mdefine_line|#define UART_CFGA_OTHER&t;&t;0x08&lt;&lt;3
DECL|macro|UART_IR_HDLC
mdefine_line|#define UART_IR_HDLC&t;&t;&t;0x04
DECL|macro|UART_IR_4PPM
mdefine_line|#define UART_IR_4PPM&t;&t;&t;0x01
DECL|macro|UART_IR_CONSUMER
mdefine_line|#define UART_IR_CONSUMER&t;&t;0x02
DECL|macro|UART_CFGB_LOOPBACK
mdefine_line|#define UART_CFGB_LOOPBACK      0x01&lt;&lt;5
DECL|macro|UART_CFGB_LPBCK_TX_CRC
mdefine_line|#define UART_CFGB_LPBCK_TX_CRC&t;0x01&lt;&lt;4
DECL|macro|UART_CFGB_NOWAIT
mdefine_line|#define UART_CFGB_NOWAIT&t;0x01&lt;&lt;3
DECL|macro|UART_CFGB_STRING_MOVE
mdefine_line|#define UART_CFGB_STRING_MOVE&t;0x01&lt;&lt;2
DECL|macro|UART_CFGB_DMA_BURST
mdefine_line|#define UART_CFGB_DMA_BURST &t;0x01&lt;&lt;1
DECL|macro|UART_CFGB_DMA_ENABLE
mdefine_line|#define UART_CFGB_DMA_ENABLE&t;0x01
DECL|macro|UART_CFGB_COM
mdefine_line|#define UART_CFGB_COM&t;&t;0x00&lt;&lt;6
DECL|macro|UART_CFGB_IR
mdefine_line|#define UART_CFGB_IR&t;&t;0x01&lt;&lt;6
DECL|macro|UART_CFGB_AUX
mdefine_line|#define UART_CFGB_AUX&t;&t;0x02&lt;&lt;6
DECL|macro|UART_CFGB_INACTIVE
mdefine_line|#define UART_CFGB_INACTIVE&t;0x03&lt;&lt;6
multiline_comment|/* Register block 2 - Consumer IR - not used */
multiline_comment|/* Register block 3 - Identification Registers! */
DECL|macro|UART_ID_HIGH
mdefine_line|#define UART_ID_HIGH&t;0x00   /* 0x10 */
DECL|macro|UART_ID_LOW
mdefine_line|#define UART_ID_LOW&t;0x01   /* 0xB8 */
DECL|macro|UART_CHIP_ID
mdefine_line|#define UART_CHIP_ID &t;0x02   /* 0xF1 */
DECL|macro|UART_VERSION
mdefine_line|#define UART_VERSION&t;0x03   /* 0x01 */
DECL|macro|UART_INTERFACE
mdefine_line|#define UART_INTERFACE&t;0x04   /* low 4 = DMA, high 4 = IRQ */
multiline_comment|/* Register block 4 - IrDA */
DECL|macro|UART_CONTROL
mdefine_line|#define UART_CONTROL             0x00
DECL|macro|UART_BOF_COUNT_LO
mdefine_line|#define UART_BOF_COUNT_LO        0x01
DECL|macro|UART_BRICKWALL_CNT_LO
mdefine_line|#define UART_BRICKWALL_CNT_LO    0x02
DECL|macro|UART_BRICKWALL_TX_CNT_HI
mdefine_line|#define UART_BRICKWALL_TX_CNT_HI 0x03
DECL|macro|UART_TX_SIZE_LO
mdefine_line|#define UART_TX_SIZE_LO          0x04
DECL|macro|UART_RX_SIZE_HI
mdefine_line|#define UART_RX_SIZE_HI          0x05
DECL|macro|UART_RX_SIZE_LO
mdefine_line|#define UART_RX_SIZE_LO          0x06
DECL|macro|UART_1152
mdefine_line|#define UART_1152     0x01&lt;&lt;7
DECL|macro|UART_CRC
mdefine_line|#define UART_CRC      0x01&lt;&lt;6
multiline_comment|/* For storing entries in the status FIFO */
DECL|struct|st_fifo_entry
r_struct
id|st_fifo_entry
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|st_fifo
r_struct
id|st_fifo
(brace
DECL|member|entries
r_struct
id|st_fifo_entry
id|entries
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Private data for each instance */
DECL|struct|ircc_cb
r_struct
id|ircc_cb
(brace
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
DECL|member|io
r_struct
id|chipio_t
id|io
suffix:semicolon
multiline_comment|/* IrDA controller information */
DECL|member|tx_buff
r_struct
id|iobuff_t
id|tx_buff
suffix:semicolon
multiline_comment|/* Transmit buffer */
DECL|member|rx_buff
r_struct
id|iobuff_t
id|rx_buff
suffix:semicolon
multiline_comment|/* Receive buffer */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
DECL|member|irport
r_struct
id|irport_cb
op_star
id|irport
suffix:semicolon
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|st_fifo
r_struct
id|st_fifo
id|st_fifo
suffix:semicolon
DECL|member|tx_buff_offsets
r_int
id|tx_buff_offsets
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Offsets between frames in tx_buff */
DECL|member|tx_len
r_int
id|tx_len
suffix:semicolon
multiline_comment|/* Number of frames in tx_buff */
)brace
suffix:semicolon
macro_line|#endif
eof
