multiline_comment|/*********************************************************************&n; *                &n; * Filename:      pc87108.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Nov 13 14:37:40 1998&n; * Modified at:   Mon Nov  8 10:00:27 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     Copyright (c) 1998 Lichen Wang, &lt;lwang@actisys.com&gt;&n; *     Copyright (c) 1998 Actisys Corp., www.actisys.com&n; *     All Rights Reserved&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef PC87108_H
DECL|macro|PC87108_H
mdefine_line|#define PC87108_H
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Flags for configuration register CRF0 */
DECL|macro|APEDCRC
mdefine_line|#define APEDCRC&t;&t;0x02
DECL|macro|ENBNKSEL
mdefine_line|#define ENBNKSEL&t;0x01
multiline_comment|/* Set 0 */
DECL|macro|TXD
mdefine_line|#define TXD             0x00 /* Transmit data port */
DECL|macro|RXD
mdefine_line|#define RXD             0x00 /* Receive data port */
multiline_comment|/* Register 1 */
DECL|macro|IER
mdefine_line|#define IER&t;&t;0x01 /* Interrupt Enable Register*/
DECL|macro|IER_RXHDL_IE
mdefine_line|#define IER_RXHDL_IE    0x01 /* Receiver high data level interrupt */
DECL|macro|IER_TXLDL_IE
mdefine_line|#define IER_TXLDL_IE    0x02 /* Transeiver low data level interrupt */
DECL|macro|IER_LS_IE
mdefine_line|#define IER_LS_IE&t;0x04
singleline_comment|//* Link Status Interrupt */
DECL|macro|IER_ETXURI
mdefine_line|#define IER_ETXURI      0x04 /* Tx underrun */
DECL|macro|IER_DMA_IE
mdefine_line|#define IER_DMA_IE&t;0x10 /* DMA finished interrupt */
DECL|macro|IER_TXEMP_IE
mdefine_line|#define IER_TXEMP_IE    0x20
DECL|macro|IER_SFIF_IE
mdefine_line|#define IER_SFIF_IE     0x40 /* Frame status FIFO intr */
DECL|macro|IER_TMR_IE
mdefine_line|#define IER_TMR_IE      0x80 /* Timer event */
DECL|macro|FCR
mdefine_line|#define FCR&t;&t;0x02 /* (write only) */
DECL|macro|FCR_FIFO_EN
mdefine_line|#define FCR_FIFO_EN     0x01 /* Enable FIFO&squot;s */
DECL|macro|FCR_RXSR
mdefine_line|#define FCR_RXSR        0x02 /* Rx FIFO soft reset */
DECL|macro|FCR_TXSR
mdefine_line|#define FCR_TXSR        0x04 /* Tx FIFO soft reset */
DECL|macro|FCR_RXTH
mdefine_line|#define FCR_RXTH&t;0x80 /* Rx FIFO threshold (set to 16) */
DECL|macro|FCR_TXTH
mdefine_line|#define FCR_TXTH&t;0x20 /* Tx FIFO threshold (set to 17) */
DECL|macro|EIR
mdefine_line|#define EIR&t;&t;0x02 /* (read only) */
DECL|macro|EIR_RXHDL_EV
mdefine_line|#define EIR_RXHDL_EV&t;0x01
DECL|macro|EIR_TXLDL_EV
mdefine_line|#define EIR_TXLDL_EV    0x02
DECL|macro|EIR_LS_EV
mdefine_line|#define EIR_LS_EV&t;0x04
DECL|macro|EIR_DMA_EV
mdefine_line|#define EIR_DMA_EV&t;0x10
DECL|macro|EIR_TXEMP_EV
mdefine_line|#define EIR_TXEMP_EV&t;0x20
DECL|macro|EIR_SFIF_EV
mdefine_line|#define EIR_SFIF_EV     0x40
DECL|macro|EIR_TMR_EV
mdefine_line|#define EIR_TMR_EV      0x80
DECL|macro|LCR
mdefine_line|#define LCR             0x03 /* Link control register */
DECL|macro|LCR_WLS_8
mdefine_line|#define LCR_WLS_8       0x03 /* 8 bits */
DECL|macro|BSR
mdefine_line|#define BSR &t;        0x03 /* Bank select register */
DECL|macro|BSR_BKSE
mdefine_line|#define BSR_BKSE        0x80
DECL|macro|BANK0
mdefine_line|#define BANK0 &t;        LCR_WLS_8 /* Must make sure that we set 8N1 */
DECL|macro|BANK1
mdefine_line|#define BANK1&t;        0x80
DECL|macro|BANK2
mdefine_line|#define BANK2&t;        0xe0
DECL|macro|BANK3
mdefine_line|#define BANK3&t;        0xe4
DECL|macro|BANK4
mdefine_line|#define BANK4&t;        0xe8
DECL|macro|BANK5
mdefine_line|#define BANK5&t;        0xec
DECL|macro|BANK6
mdefine_line|#define BANK6&t;        0xf0
DECL|macro|BANK7
mdefine_line|#define BANK7     &t;0xf4
DECL|macro|MCR
mdefine_line|#define MCR&t;&t;0x04 /* Mode Control Register */
DECL|macro|MCR_MODE_MASK
mdefine_line|#define MCR_MODE_MASK&t;~(0xd0)
DECL|macro|MCR_UART
mdefine_line|#define MCR_UART        0x00
DECL|macro|MCR_RESERVED
mdefine_line|#define MCR_RESERVED  &t;0x20&t;
DECL|macro|MCR_SHARP_IR
mdefine_line|#define MCR_SHARP_IR    0x40
DECL|macro|MCR_SIR
mdefine_line|#define MCR_SIR         0x60
DECL|macro|MCR_MIR
mdefine_line|#define MCR_MIR  &t;0x80
DECL|macro|MCR_FIR
mdefine_line|#define MCR_FIR&t;&t;0xa0
DECL|macro|MCR_CEIR
mdefine_line|#define MCR_CEIR        0xb0
DECL|macro|MCR_DMA_EN
mdefine_line|#define MCR_DMA_EN&t;0x04
DECL|macro|MCR_EN_IRQ
mdefine_line|#define MCR_EN_IRQ&t;0x08
DECL|macro|MCR_TX_DFR
mdefine_line|#define MCR_TX_DFR&t;0x08
DECL|macro|LSR
mdefine_line|#define LSR             0x05 /* Link status register */
DECL|macro|LSR_RXDA
mdefine_line|#define LSR_RXDA        0x01 /* Receiver data available */
DECL|macro|LSR_TXRDY
mdefine_line|#define LSR_TXRDY       0x20 /* Transmitter ready */
DECL|macro|LSR_TXEMP
mdefine_line|#define LSR_TXEMP       0x40 /* Transmitter empty */
DECL|macro|ASCR
mdefine_line|#define ASCR            0x07 /* Auxillary Status and Control Register */
DECL|macro|ASCR_RXF_TOUT
mdefine_line|#define ASCR_RXF_TOUT   0x01 /* Rx FIFO timeout */
DECL|macro|ASCR_FEND_INF
mdefine_line|#define ASCR_FEND_INF   0x02 /* Frame end bytes in rx FIFO */
DECL|macro|ASCR_S_EOT
mdefine_line|#define ASCR_S_EOT      0x04 /* Set end of transmission */
DECL|macro|ASCT_RXBSY
mdefine_line|#define ASCT_RXBSY      0x20 /* Rx busy */
DECL|macro|ASCR_TXUR
mdefine_line|#define ASCR_TXUR       0x40 /* Transeiver underrun */
DECL|macro|ASCR_CTE
mdefine_line|#define ASCR_CTE        0x80 /* Clear timer event */
multiline_comment|/* Bank 2 */
DECL|macro|BGDL
mdefine_line|#define BGDL            0x00 /* Baud Generator Divisor Port (Low Byte) */
DECL|macro|BGDH
mdefine_line|#define BGDH            0x01 /* Baud Generator Divisor Port (High Byte) */
DECL|macro|ECR1
mdefine_line|#define ECR1&t;&t;0x02 /* Extended Control Register 1 */
DECL|macro|ECR1_EXT_SL
mdefine_line|#define ECR1_EXT_SL&t;0x01 /* Extended Mode Select */
DECL|macro|ECR1_DMANF
mdefine_line|#define ECR1_DMANF&t;0x02 /* DMA Fairness */
DECL|macro|ECR1_DMATH
mdefine_line|#define ECR1_DMATH      0x04
DECL|macro|ECR1_DMASWP
mdefine_line|#define ECR1_DMASWP&t;0x08 /* DMA Swap */
DECL|macro|EXCR2
mdefine_line|#define EXCR2&t;&t;0x04
DECL|macro|EXCR2_TFSIZ
mdefine_line|#define EXCR2_TFSIZ&t;0x01 /* Rx FIFO size = 32 */
DECL|macro|EXCR2_RFSIZ
mdefine_line|#define EXCR2_RFSIZ&t;0x04 /* Tx FIFO size = 32 */
DECL|macro|TXFLV
mdefine_line|#define TXFLV           0x06 /* Tx FIFO level */
DECL|macro|RXFLV
mdefine_line|#define RXFLV           0x07 /* Rx FIFO level */
multiline_comment|/* Bank 3 */
DECL|macro|MID
mdefine_line|#define MID&t;&t;0x00
multiline_comment|/* Bank 4 */
DECL|macro|TMRL
mdefine_line|#define TMRL            0x00 /* Timer low byte */
DECL|macro|TMRH
mdefine_line|#define TMRH            0x01 /* Timer high byte */
DECL|macro|IRCR1
mdefine_line|#define IRCR1           0x02 /* Infrared control register 1 */
DECL|macro|IRCR1_TMR_EN
mdefine_line|#define IRCR1_TMR_EN    0x01 /* Timer enable */
DECL|macro|TFRLL
mdefine_line|#define TFRLL&t;&t;0x04
DECL|macro|TFRLH
mdefine_line|#define TFRLH&t;&t;0x05
DECL|macro|RFRLL
mdefine_line|#define RFRLL&t;&t;0x06
DECL|macro|RFRLH
mdefine_line|#define RFRLH&t;&t;0x07
multiline_comment|/* Bank 5 */
DECL|macro|IRCR2
mdefine_line|#define IRCR2           0x04 /* Infrared control register 2 */
DECL|macro|IRCR2_MDRS
mdefine_line|#define IRCR2_MDRS      0x04 /* MIR data rate select */
DECL|macro|IRCR2_FEND_MD
mdefine_line|#define IRCR2_FEND_MD   0x20 /* */
DECL|macro|FRM_ST
mdefine_line|#define FRM_ST          0x05 /* Frame status FIFO */
DECL|macro|FRM_ST_VLD
mdefine_line|#define FRM_ST_VLD      0x80 /* Frame status FIFO data valid */
DECL|macro|FRM_ST_ERR_MSK
mdefine_line|#define FRM_ST_ERR_MSK  0x5f
DECL|macro|FRM_ST_LOST_FR
mdefine_line|#define FRM_ST_LOST_FR  0x40 /* Frame lost */
DECL|macro|FRM_ST_MAX_LEN
mdefine_line|#define FRM_ST_MAX_LEN  0x10 /* Max frame len exceeded */
DECL|macro|FRM_ST_PHY_ERR
mdefine_line|#define FRM_ST_PHY_ERR  0x08 /* Physical layer error */
DECL|macro|FRM_ST_BAD_CRC
mdefine_line|#define FRM_ST_BAD_CRC  0x04 
DECL|macro|FRM_ST_OVR1
mdefine_line|#define FRM_ST_OVR1     0x02 /* Receive overrun */
DECL|macro|FRM_ST_OVR2
mdefine_line|#define FRM_ST_OVR2     0x01 /* Frame status FIFO overrun */
DECL|macro|RFLFL
mdefine_line|#define RFLFL           0x06
DECL|macro|RFLFH
mdefine_line|#define RFLFH           0x07
multiline_comment|/* Bank 6 */
DECL|macro|IR_CFG2
mdefine_line|#define IR_CFG2&t;&t;0x00
DECL|macro|IR_CFG2_DIS_CRC
mdefine_line|#define IR_CFG2_DIS_CRC&t;0x02
multiline_comment|/* Bank 7 */
DECL|macro|IRM_CR
mdefine_line|#define IRM_CR&t;&t;0x07 /* Infrared module control register */
DECL|macro|IRM_CR_IRX_MSL
mdefine_line|#define IRM_CR_IRX_MSL&t;0x40
DECL|macro|IRM_CR_AF_MNT
mdefine_line|#define IRM_CR_AF_MNT   0x80 /* Automatic format */
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
DECL|struct|pc87108
r_struct
id|pc87108
(brace
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
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
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
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
)brace
suffix:semicolon
DECL|function|switch_bank
r_static
r_inline
r_void
id|switch_bank
c_func
(paren
r_int
id|iobase
comma
r_int
id|bank
)paren
(brace
id|outb
c_func
(paren
id|bank
comma
id|iobase
op_plus
id|BSR
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
