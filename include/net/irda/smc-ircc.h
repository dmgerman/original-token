multiline_comment|/*********************************************************************&n; *                &n; * Filename:      smc-ircc.h&n; * Version:       0.3&n; * Description:   Definitions for the SMC IrCC chipset&n; * Status:        Experimental.&n; * Author:        Thomas Davis (tadavis@jps.net)&n; *&n; *     Copyright (c) 1999-2000, Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     Copyright (c) 1998-1999, Thomas Davis (tadavis@jps.net&gt;&n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *&n; ********************************************************************/
macro_line|#ifndef SMC_IRCC_H
DECL|macro|SMC_IRCC_H
mdefine_line|#define SMC_IRCC_H
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;net/irda/irport.h&gt;
multiline_comment|/* DMA modes needed */
DECL|macro|DMA_TX_MODE
mdefine_line|#define DMA_TX_MODE              0x08    /* Mem to I/O, ++, demand. */
DECL|macro|DMA_RX_MODE
mdefine_line|#define DMA_RX_MODE              0x04    /* I/O to mem, ++, demand. */
DECL|macro|IRCC_MASTER
mdefine_line|#define IRCC_MASTER              0x07
DECL|macro|IRCC_MASTER_POWERDOWN
mdefine_line|#define IRCC_MASTER_POWERDOWN&t; 1&lt;&lt;7
DECL|macro|IRCC_MASTER_RESET
mdefine_line|#define IRCC_MASTER_RESET        1&lt;&lt;6
DECL|macro|IRCC_MASTER_INT_EN
mdefine_line|#define IRCC_MASTER_INT_EN       1&lt;&lt;5
DECL|macro|IRCC_MASTER_ERROR_RESET
mdefine_line|#define IRCC_MASTER_ERROR_RESET&t; 1&lt;&lt;4
multiline_comment|/* Register block 0 */
DECL|macro|IRCC_IIR
mdefine_line|#define IRCC_IIR                 0x01
DECL|macro|IRCC_IER
mdefine_line|#define IRCC_IER                 0x02
DECL|macro|IRCC_LSR
mdefine_line|#define IRCC_LSR                 0x03
DECL|macro|IRCC_LCR_A
mdefine_line|#define IRCC_LCR_A               0x04
DECL|macro|IRCC_LCR_B
mdefine_line|#define IRCC_LCR_B               0x05
DECL|macro|IRCC_BSR
mdefine_line|#define IRCC_BSR                 0x06
DECL|macro|IRCC_IIR_ACTIVE_FRAME
mdefine_line|#define IRCC_IIR_ACTIVE_FRAME    1&lt;&lt;7
DECL|macro|IRCC_IIR_EOM
mdefine_line|#define IRCC_IIR_EOM             1&lt;&lt;6
DECL|macro|IRCC_IIR_RAW_MODE
mdefine_line|#define IRCC_IIR_RAW_MODE        1&lt;&lt;5
DECL|macro|IRCC_IIR_FIFO
mdefine_line|#define IRCC_IIR_FIFO&t;&t; 1&lt;&lt;4
DECL|macro|IRCC_IER_ACTIVE_FRAME
mdefine_line|#define IRCC_IER_ACTIVE_FRAME&t; 1&lt;&lt;7
DECL|macro|IRCC_IER_EOM
mdefine_line|#define IRCC_IER_EOM &t;&t; 1&lt;&lt;6
DECL|macro|IRCC_IER_RAW_MODE
mdefine_line|#define IRCC_IER_RAW_MODE        1&lt;&lt;5
DECL|macro|IRCC_IER_FIFO
mdefine_line|#define IRCC_IER_FIFO&t;&t; 1&lt;&lt;4
DECL|macro|IRCC_LSR_UNDERRUN
mdefine_line|#define IRCC_LSR_UNDERRUN        1&lt;&lt;7
DECL|macro|IRCC_LSR_OVERRUN
mdefine_line|#define IRCC_LSR_OVERRUN         1&lt;&lt;6
DECL|macro|IRCC_LSR_FRAME_ERROR
mdefine_line|#define IRCC_LSR_FRAME_ERROR     1&lt;&lt;5
DECL|macro|IRCC_LSR_SIZE_ERROR
mdefine_line|#define IRCC_LSR_SIZE_ERROR      1&lt;&lt;4
DECL|macro|IRCC_LSR_CRC_ERROR
mdefine_line|#define IRCC_LSR_CRC_ERROR       1&lt;&lt;3
DECL|macro|IRCC_LSR_FRAME_ABORT
mdefine_line|#define IRCC_LSR_FRAME_ABORT &t; 1&lt;&lt;2
DECL|macro|IRCC_LCR_A_FIFO_RESET
mdefine_line|#define IRCC_LCR_A_FIFO_RESET    1&lt;&lt;7
DECL|macro|IRCC_LCR_A_FAST
mdefine_line|#define IRCC_LCR_A_FAST          1&lt;&lt;6
DECL|macro|IRCC_LCR_A_GP_DATA
mdefine_line|#define IRCC_LCR_A_GP_DATA       1&lt;&lt;5
DECL|macro|IRCC_LCR_A_RAW_TX
mdefine_line|#define IRCC_LCR_A_RAW_TX        1&lt;&lt;4
DECL|macro|IRCC_LCR_A_RAW_RX
mdefine_line|#define IRCC_LCR_A_RAW_RX        1&lt;&lt;3
DECL|macro|IRCC_LCR_A_ABORT
mdefine_line|#define IRCC_LCR_A_ABORT         1&lt;&lt;2
DECL|macro|IRCC_LCR_A_DATA_DONE
mdefine_line|#define IRCC_LCR_A_DATA_DONE     1&lt;&lt;1
DECL|macro|IRCC_LCR_B_SCE_DISABLED
mdefine_line|#define IRCC_LCR_B_SCE_DISABLED  0x00&lt;&lt;6
DECL|macro|IRCC_LCR_B_SCE_TRANSMIT
mdefine_line|#define IRCC_LCR_B_SCE_TRANSMIT  0x01&lt;&lt;6
DECL|macro|IRCC_LCR_B_SCE_RECEIVE
mdefine_line|#define IRCC_LCR_B_SCE_RECEIVE&t; 0x02&lt;&lt;6
DECL|macro|IRCC_LCR_B_SCE_UNDEFINED
mdefine_line|#define IRCC_LCR_B_SCE_UNDEFINED 0x03&lt;&lt;6
DECL|macro|IRCC_LCR_B_SIP_ENABLE
mdefine_line|#define IRCC_LCR_B_SIP_ENABLE&t; 1&lt;&lt;5
DECL|macro|IRCC_LCR_B_BRICK_WALL
mdefine_line|#define IRCC_LCR_B_BRICK_WALL    1&lt;&lt;4
DECL|macro|IRCC_BSR_NOT_EMPTY
mdefine_line|#define IRCC_BSR_NOT_EMPTY&t; 1&lt;&lt;7
DECL|macro|IRCC_BSR_FIFO_FULL
mdefine_line|#define IRCC_BSR_FIFO_FULL&t; 1&lt;&lt;6
DECL|macro|IRCC_BSR_TIMEOUT
mdefine_line|#define IRCC_BSR_TIMEOUT&t; 1&lt;&lt;5
multiline_comment|/* Register block 1 */
DECL|macro|IRCC_SCE_CFGA
mdefine_line|#define IRCC_SCE_CFGA&t;         0x00
DECL|macro|IRCC_SCE_CFGB
mdefine_line|#define IRCC_SCE_CFGB&t;         0x01
DECL|macro|IRCC_FIFO_THRESHOLD
mdefine_line|#define IRCC_FIFO_THRESHOLD&t; 0x02
DECL|macro|IRCC_CFGA_AUX_IR
mdefine_line|#define IRCC_CFGA_AUX_IR&t; 0x01&lt;&lt;7
DECL|macro|IRCC_CFGA_HALF_DUPLEX
mdefine_line|#define IRCC_CFGA_HALF_DUPLEX&t; 0x01&lt;&lt;2
DECL|macro|IRCC_CFGA_TX_POLARITY
mdefine_line|#define IRCC_CFGA_TX_POLARITY&t; 0x01&lt;&lt;1
DECL|macro|IRCC_CFGA_RX_POLARITY
mdefine_line|#define IRCC_CFGA_RX_POLARITY&t; 0x01
DECL|macro|IRCC_CFGA_COM
mdefine_line|#define IRCC_CFGA_COM&t;&t; 0x00&lt;&lt;3
DECL|macro|IRCC_CFGA_IRDA_SIR_A
mdefine_line|#define IRCC_CFGA_IRDA_SIR_A&t; 0x01&lt;&lt;3
DECL|macro|IRCC_CFGA_ASK_SIR
mdefine_line|#define IRCC_CFGA_ASK_SIR&t; 0x02&lt;&lt;3
DECL|macro|IRCC_CFGA_IRDA_SIR_B
mdefine_line|#define IRCC_CFGA_IRDA_SIR_B&t; 0x03&lt;&lt;3
DECL|macro|IRCC_CFGA_IRDA_HDLC
mdefine_line|#define IRCC_CFGA_IRDA_HDLC &t; 0x04&lt;&lt;3
DECL|macro|IRCC_CFGA_IRDA_4PPM
mdefine_line|#define IRCC_CFGA_IRDA_4PPM &t; 0x05&lt;&lt;3
DECL|macro|IRCC_CFGA_CONSUMER
mdefine_line|#define IRCC_CFGA_CONSUMER&t; 0x06&lt;&lt;3
DECL|macro|IRCC_CFGA_RAW_IR
mdefine_line|#define IRCC_CFGA_RAW_IR&t; 0x07&lt;&lt;3
DECL|macro|IRCC_CFGA_OTHER
mdefine_line|#define IRCC_CFGA_OTHER&t;&t; 0x08&lt;&lt;3
DECL|macro|IRCC_IR_HDLC
mdefine_line|#define IRCC_IR_HDLC             0x04
DECL|macro|IRCC_IR_4PPM
mdefine_line|#define IRCC_IR_4PPM             0x01
DECL|macro|IRCC_IR_CONSUMER
mdefine_line|#define IRCC_IR_CONSUMER         0x02
DECL|macro|IRCC_CFGB_LOOPBACK
mdefine_line|#define IRCC_CFGB_LOOPBACK       0x01&lt;&lt;5
DECL|macro|IRCC_CFGB_LPBCK_TX_CRC
mdefine_line|#define IRCC_CFGB_LPBCK_TX_CRC&t; 0x01&lt;&lt;4
DECL|macro|IRCC_CFGB_NOWAIT
mdefine_line|#define IRCC_CFGB_NOWAIT&t; 0x01&lt;&lt;3
DECL|macro|IRCC_CFGB_STRING_MOVE
mdefine_line|#define IRCC_CFGB_STRING_MOVE&t; 0x01&lt;&lt;2
DECL|macro|IRCC_CFGB_DMA_BURST
mdefine_line|#define IRCC_CFGB_DMA_BURST &t; 0x01&lt;&lt;1
DECL|macro|IRCC_CFGB_DMA_ENABLE
mdefine_line|#define IRCC_CFGB_DMA_ENABLE&t; 0x01
DECL|macro|IRCC_CFGB_COM
mdefine_line|#define IRCC_CFGB_COM&t;&t; 0x00&lt;&lt;6
DECL|macro|IRCC_CFGB_IR
mdefine_line|#define IRCC_CFGB_IR&t;&t; 0x01&lt;&lt;6
DECL|macro|IRCC_CFGB_AUX
mdefine_line|#define IRCC_CFGB_AUX&t;&t; 0x02&lt;&lt;6
DECL|macro|IRCC_CFGB_INACTIVE
mdefine_line|#define IRCC_CFGB_INACTIVE&t; 0x03&lt;&lt;6
multiline_comment|/* Register block 3 - Identification Registers! */
DECL|macro|IRCC_ID_HIGH
mdefine_line|#define IRCC_ID_HIGH&t;         0x00   /* 0x10 */
DECL|macro|IRCC_ID_LOW
mdefine_line|#define IRCC_ID_LOW&t;         0x01   /* 0xB8 */
DECL|macro|IRCC_CHIP_ID
mdefine_line|#define IRCC_CHIP_ID &t;         0x02   /* 0xF1 */
DECL|macro|IRCC_VERSION
mdefine_line|#define IRCC_VERSION&t;         0x03   /* 0x01 */
DECL|macro|IRCC_INTERFACE
mdefine_line|#define IRCC_INTERFACE&t;         0x04   /* low 4 = DMA, high 4 = IRQ */
multiline_comment|/* Register block 4 - IrDA */
DECL|macro|IRCC_CONTROL
mdefine_line|#define IRCC_CONTROL             0x00
DECL|macro|IRCC_BOF_COUNT_LO
mdefine_line|#define IRCC_BOF_COUNT_LO        0x01
DECL|macro|IRCC_BRICKWALL_CNT_LO
mdefine_line|#define IRCC_BRICKWALL_CNT_LO    0x02
DECL|macro|IRCC_BRICKWALL_TX_CNT_HI
mdefine_line|#define IRCC_BRICKWALL_TX_CNT_HI 0x03
DECL|macro|IRCC_TX_SIZE_LO
mdefine_line|#define IRCC_TX_SIZE_LO          0x04
DECL|macro|IRCC_RX_SIZE_HI
mdefine_line|#define IRCC_RX_SIZE_HI          0x05
DECL|macro|IRCC_RX_SIZE_LO
mdefine_line|#define IRCC_RX_SIZE_LO          0x06
DECL|macro|IRCC_1152
mdefine_line|#define IRCC_1152                0x01&lt;&lt;7
DECL|macro|IRCC_CRC
mdefine_line|#define IRCC_CRC                 0x01&lt;&lt;6
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
DECL|member|irport
r_struct
id|irport_cb
op_star
id|irport
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
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
macro_line|#endif /* SMC_IRCC_H */
eof
