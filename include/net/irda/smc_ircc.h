macro_line|#if 0
r_static
r_char
op_star
id|rcsid
op_assign
l_string|&quot;$Id: smc_ircc.h,v 1.5 1998/07/27 01:25:29 ratbert Exp $&quot;
suffix:semicolon
macro_line|#endif
macro_line|#ifndef SMC_IRCC_H
DECL|macro|SMC_IRCC_H
mdefine_line|#define SMC_IRCC_H
DECL|macro|FIR_XMIT
mdefine_line|#define FIR_XMIT&t;1
DECL|macro|FIR_RECEIVE
mdefine_line|#define FIR_RECEIVE&t;2
DECL|macro|SIR_XMIT
mdefine_line|#define SIR_XMIT&t;3
DECL|macro|SIR_RECEIVE
mdefine_line|#define SIR_RECEIVE&t;4
DECL|macro|MASTER
mdefine_line|#define MASTER&t;&t;&t;0x07
DECL|macro|MASTER_POWERDOWN
mdefine_line|#define MASTER_POWERDOWN&t;1&lt;&lt;7
DECL|macro|MASTER_RESET
mdefine_line|#define MASTER_RESET&t;&t;1&lt;&lt;6
DECL|macro|MASTER_INT_EN
mdefine_line|#define MASTER_INT_EN&t;&t;1&lt;&lt;5
DECL|macro|MASTER_ERROR_RESET
mdefine_line|#define MASTER_ERROR_RESET&t;1&lt;&lt;4
multiline_comment|/* Register block 0 */
DECL|macro|IIR
mdefine_line|#define IIR&t;0x01
DECL|macro|IER
mdefine_line|#define IER&t;0x02
DECL|macro|LSR
mdefine_line|#define LSR&t;0x03
DECL|macro|LCR_A
mdefine_line|#define LCR_A&t;0x04
DECL|macro|LCR_B
mdefine_line|#define LCR_B&t;0x05
DECL|macro|BSR
mdefine_line|#define BSR&t;0x06
DECL|macro|IIR_ACTIVE_FRAME
mdefine_line|#define IIR_ACTIVE_FRAME&t;1&lt;&lt;7
DECL|macro|IIR_EOM
mdefine_line|#define IIR_EOM &t;&t;1&lt;&lt;6
DECL|macro|IIR_RAW_MODE
mdefine_line|#define IIR_RAW_MODE&t;&t;1&lt;&lt;5
DECL|macro|IIR_FIFO
mdefine_line|#define IIR_FIFO&t;&t;1&lt;&lt;4
DECL|macro|IER_ACTIVE_FRAME
mdefine_line|#define IER_ACTIVE_FRAME&t;1&lt;&lt;7
DECL|macro|IER_EOM
mdefine_line|#define IER_EOM &t;&t;1&lt;&lt;6
DECL|macro|IER_RAW_MODE
mdefine_line|#define IER_RAW_MODE&t;&t;1&lt;&lt;5
DECL|macro|IER_FIFO
mdefine_line|#define IER_FIFO&t;&t;1&lt;&lt;4
DECL|macro|LSR_UNDER_RUN
mdefine_line|#define LSR_UNDER_RUN&t;&t;1&lt;&lt;7
DECL|macro|LSR_OVER_RUN
mdefine_line|#define LSR_OVER_RUN&t;&t;1&lt;&lt;6
DECL|macro|LSR_FRAME_ERROR
mdefine_line|#define LSR_FRAME_ERROR &t;1&lt;&lt;5
DECL|macro|LSR_SIZE_ERROR
mdefine_line|#define LSR_SIZE_ERROR&t;&t;1&lt;&lt;4
DECL|macro|LSR_CRC_ERROR
mdefine_line|#define LSR_CRC_ERROR&t;&t;1&lt;&lt;3
DECL|macro|LSR_FRAME_ABORT
mdefine_line|#define LSR_FRAME_ABORT &t;1&lt;&lt;2
DECL|macro|LCR_A_FIFO_RESET
mdefine_line|#define LCR_A_FIFO_RESET        1&lt;&lt;7
DECL|macro|LCR_A_FAST
mdefine_line|#define LCR_A_FAST              1&lt;&lt;6
DECL|macro|LCR_A_GP_DATA
mdefine_line|#define LCR_A_GP_DATA           1&lt;&lt;5
DECL|macro|LCR_A_RAW_TX
mdefine_line|#define LCR_A_RAW_TX            1&lt;&lt;4
DECL|macro|LCR_A_RAW_RX
mdefine_line|#define LCR_A_RAW_RX            1&lt;&lt;3
DECL|macro|LCR_A_ABORT
mdefine_line|#define LCR_A_ABORT             1&lt;&lt;2
DECL|macro|LCR_A_DATA_DONE
mdefine_line|#define LCR_A_DATA_DONE         1&lt;&lt;1
DECL|macro|LCR_B_SCE_MODE_DISABLED
mdefine_line|#define LCR_B_SCE_MODE_DISABLED &t;0x00&lt;&lt;6
DECL|macro|LCR_B_SCE_MODE_TRANSMIT
mdefine_line|#define LCR_B_SCE_MODE_TRANSMIT &t;0x01&lt;&lt;6
DECL|macro|LCR_B_SCE_MODE_RECEIVE
mdefine_line|#define LCR_B_SCE_MODE_RECEIVE&t;&t;0x02&lt;&lt;6
DECL|macro|LCR_B_SCE_MODE_UNDEFINED
mdefine_line|#define LCR_B_SCE_MODE_UNDEFINED&t;0x03&lt;&lt;6
DECL|macro|LCR_B_SIP_ENABLE
mdefine_line|#define LCR_B_SIP_ENABLE&t;&t;1&lt;&lt;5
DECL|macro|LCR_B_BRICK_WALL
mdefine_line|#define LCR_B_BRICK_WALL&t;&t;1&lt;&lt;4
DECL|macro|BSR_NOT_EMPTY
mdefine_line|#define BSR_NOT_EMPTY&t;1&lt;&lt;7
DECL|macro|BSR_FIFO_FULL
mdefine_line|#define BSR_FIFO_FULL&t;1&lt;&lt;6
DECL|macro|BSR_TIMEOUT
mdefine_line|#define BSR_TIMEOUT&t;1&lt;&lt;5
multiline_comment|/* Register block 1 */
DECL|macro|SCE_CFG_A
mdefine_line|#define SCE_CFG_A&t;0x00
DECL|macro|SCE_CFG_B
mdefine_line|#define SCE_CFG_B&t;0x01
DECL|macro|FIFO_THRESHOLD
mdefine_line|#define FIFO_THRESHOLD&t;0x02
DECL|macro|CFG_A_AUX_IR
mdefine_line|#define CFG_A_AUX_IR&t;&t;0x01&lt;&lt;7
DECL|macro|CFG_A_HALF_DUPLEX
mdefine_line|#define CFG_A_HALF_DUPLEX&t;0x01&lt;&lt;2
DECL|macro|CFG_A_TX_POLARITY
mdefine_line|#define CFG_A_TX_POLARITY&t;0x01&lt;&lt;1
DECL|macro|CFG_A_RX_POLARITY
mdefine_line|#define CFG_A_RX_POLARITY&t;0x01
DECL|macro|CFG_A_COM
mdefine_line|#define CFG_A_COM&t;&t;0x00&lt;&lt;3
DECL|macro|CFG_A_IRDA_SIR_A
mdefine_line|#define CFG_A_IRDA_SIR_A&t;0x01&lt;&lt;3
DECL|macro|CFG_A_ASK_SIR
mdefine_line|#define CFG_A_ASK_SIR&t;&t;0x02&lt;&lt;3
DECL|macro|CFG_A_IRDA_SIR_B
mdefine_line|#define CFG_A_IRDA_SIR_B&t;0x03&lt;&lt;3
DECL|macro|CFG_A_IRDA_HDLC
mdefine_line|#define CFG_A_IRDA_HDLC &t;0x04&lt;&lt;3
DECL|macro|CFG_A_IRDA_4PPM
mdefine_line|#define CFG_A_IRDA_4PPM &t;0x05&lt;&lt;3
DECL|macro|CFG_A_CONSUMER
mdefine_line|#define CFG_A_CONSUMER&t;&t;0x06&lt;&lt;3
DECL|macro|CFG_A_RAW_IR
mdefine_line|#define CFG_A_RAW_IR&t;&t;0x07&lt;&lt;3
DECL|macro|CFG_A_OTHER
mdefine_line|#define CFG_A_OTHER&t;&t;0x08&lt;&lt;3
DECL|macro|IR_HDLC
mdefine_line|#define IR_HDLC&t;&t;&t;0x04
DECL|macro|IR_4PPM
mdefine_line|#define IR_4PPM&t;&t;&t;0x01
DECL|macro|IR_CONSUMER
mdefine_line|#define IR_CONSUMER&t;&t;0x02
DECL|macro|CFG_B_LOOPBACK
mdefine_line|#define CFG_B_LOOPBACK&t;&t;0x01&lt;&lt;5
DECL|macro|CFG_B_LPBCK_TX_CRC
mdefine_line|#define CFG_B_LPBCK_TX_CRC&t;0x01&lt;&lt;4
DECL|macro|CFG_B_NOWAIT
mdefine_line|#define CFG_B_NOWAIT&t;&t;0x01&lt;&lt;3
DECL|macro|CFB_B_STRING_MOVE
mdefine_line|#define CFB_B_STRING_MOVE&t;0x01&lt;&lt;2
DECL|macro|CFG_B_DMA_BURST
mdefine_line|#define CFG_B_DMA_BURST &t;0x01&lt;&lt;1
DECL|macro|CFG_B_DMA_ENABLE
mdefine_line|#define CFG_B_DMA_ENABLE&t;0x01
DECL|macro|CFG_B_MUX_COM
mdefine_line|#define CFG_B_MUX_COM&t;&t;0x00&lt;&lt;6
DECL|macro|CFG_B_MUX_IR
mdefine_line|#define CFG_B_MUX_IR&t;&t;0x01&lt;&lt;6
DECL|macro|CFG_B_MUX_AUX
mdefine_line|#define CFG_B_MUX_AUX&t;&t;0x02&lt;&lt;6
DECL|macro|CFG_B_INACTIVE
mdefine_line|#define CFG_B_INACTIVE&t;&t;0x03&lt;&lt;6
multiline_comment|/* Register block 2 - Consumer IR - not used */
multiline_comment|/* Register block 3 - Identification Registers! */
DECL|macro|SMSC_ID_HIGH
mdefine_line|#define SMSC_ID_HIGH&t;0x00   /* 0x10 */
DECL|macro|SMSC_ID_LOW
mdefine_line|#define SMSC_ID_LOW&t;0x01   /* 0xB8 */
DECL|macro|CHIP_ID
mdefine_line|#define CHIP_ID &t;0x02   /* 0xF1 */
DECL|macro|VERSION_NUMBER
mdefine_line|#define VERSION_NUMBER&t;0x03   /* 0x01 */
DECL|macro|HOST_INTERFACE
mdefine_line|#define HOST_INTERFACE&t;0x04   /* low 4 = DMA, high 4 = IRQ */
multiline_comment|/* Register block 4 - IrDA */
DECL|macro|IR_CONTROL
mdefine_line|#define IR_CONTROL        0x00
DECL|macro|BOF_COUNT_LO
mdefine_line|#define BOF_COUNT_LO      0x01
DECL|macro|BRICK_WALL_CNT_LO
mdefine_line|#define BRICK_WALL_CNT_LO 0x02
DECL|macro|BRICK_TX_CNT_HI
mdefine_line|#define BRICK_TX_CNT_HI   0x03
DECL|macro|TX_DATA_SIZE_LO
mdefine_line|#define TX_DATA_SIZE_LO   0x04
DECL|macro|RX_DATA_SIZE_HI
mdefine_line|#define RX_DATA_SIZE_HI   0x05
DECL|macro|RX_DATA_SIZE_LO
mdefine_line|#define RX_DATA_SIZE_LO   0x06
DECL|macro|SELECT_1152
mdefine_line|#define SELECT_1152     0x01&lt;&lt;7
DECL|macro|CRC_SELECT
mdefine_line|#define CRC_SELECT      0x01&lt;&lt;6
macro_line|#endif
eof
