multiline_comment|/*********************************************************************&n; *                &n; * Filename:      uircc.h&n; * Version:       0.1&n; * Description:   Driver for the Sharp Universal Infrared &n; *                Communications Controller (UIRCC)&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Dec 26 11:00:49 1998&n; * Modified at:   Tue Jan 19 23:52:46 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef UIRCC_H
DECL|macro|UIRCC_H
mdefine_line|#define UIRCC_H
multiline_comment|/* Control registers (write only) */
DECL|macro|UIRCC_CR0
mdefine_line|#define UIRCC_CR0           0x00 /* Control register 0 */
DECL|macro|UIRCC_CR0_XMIT_RST
mdefine_line|#define UIRCC_CR0_XMIT_RST  0x20 /* Transmit reset */
DECL|macro|UIRCC_CR0_RECV_RST
mdefine_line|#define UIRCC_CR0_RECV_RST  0x10 /* Receive reset */
DECL|macro|UIRCC_CR0_TMR_RST
mdefine_line|#define UIRCC_CR0_TMR_RST   0x08 /* Timer reset */
DECL|macro|UIRCC_CR0_SYS_RST
mdefine_line|#define UIRCC_CR0_SYS_RST   0x04 /* System reset */
DECL|macro|UIRCC_CR0_CARR_RST
mdefine_line|#define UIRCC_CR0_CARR_RST  0x02 /* Carrier latch reset */
DECL|macro|UIRCC_CR0_CNT_SWT
mdefine_line|#define UIRCC_CR0_CNT_SWT   0x01 /* Transmit/receive length counter reset */
DECL|macro|UIRCC_CR1
mdefine_line|#define UIRCC_CR1           0x01 /* Transmit/receive mode setting register */
DECL|macro|UIRCC_CR1_RX_DMA
mdefine_line|#define UIRCC_CR1_RX_DMA    0x80 /* Rx DMA mode */
DECL|macro|UIRCC_CR1_TX_DMA
mdefine_line|#define UIRCC_CR1_TX_DMA    0x20 /* Tx DMA mode */
DECL|macro|UIRCC_CR1_DMA_BRST
mdefine_line|#define UIRCC_CR1_DMA_BRST  0x10 /* DMA burst mode */
DECL|macro|UIRCC_CR1_MUST_SET
mdefine_line|#define UIRCC_CR1_MUST_SET  0x0c /* Must be set */
DECL|macro|UIRCC_CR2
mdefine_line|#define UIRCC_CR2           0x02 /* Interrupt mask register */
DECL|macro|UIRCC_CR2_RECV_OVR
mdefine_line|#define UIRCC_CR2_RECV_OVR  0x40 /* Receive overrun error */
DECL|macro|UIRCC_CR2_RECV_FRM
mdefine_line|#define UIRCC_CR2_RECV_FRM  0x20 /* Receive frame error */
DECL|macro|UIRCC_CR2_RECV_END
mdefine_line|#define UIRCC_CR2_RECV_END  0x10 /* Receive end */
DECL|macro|UIRCC_CR2_TMR_OUT
mdefine_line|#define UIRCC_CR2_TMR_OUT   0x08 /* Timer time-out */
DECL|macro|UIRCC_CR2_XMIT_UNR
mdefine_line|#define UIRCC_CR2_XMIT_UNR  0x04 /* Transmit under-run error */
DECL|macro|UIRCC_CR2_XMIT_END
mdefine_line|#define UIRCC_CR2_XMIT_END  0x01 /* Transmit end */
DECL|macro|UIRCC_CR2_RECV_MASK
mdefine_line|#define UIRCC_CR2_RECV_MASK 0x70
DECL|macro|UIRCC_CR2_XMIT_MASK
mdefine_line|#define UIRCC_CR2_XMIT_MASK 0x05
DECL|macro|UIRCC_CR3
mdefine_line|#define UIRCC_CR3           0x03 /* Transmit/receive control */
DECL|macro|UIRCC_CR3_XMIT_EN
mdefine_line|#define UIRCC_CR3_XMIT_EN   0x80 /* Transmit enable */
DECL|macro|UIRCC_CR3_TX_CRC_EN
mdefine_line|#define UIRCC_CR3_TX_CRC_EN 0x40 /* Transmit UIRCC_CRC enable */
DECL|macro|UIRCC_CR3_RECV_EN
mdefine_line|#define UIRCC_CR3_RECV_EN   0x20 /* Receive enable */
DECL|macro|UIRCC_CR3_RX_CRC_EN
mdefine_line|#define UIRCC_CR3_RX_CRC_EN 0x10 /* Receive CRC enable */
DECL|macro|UIRCC_CR3_ADDR_CMP
mdefine_line|#define UIRCC_CR3_ADDR_CMP  0x08 /* Address comparison enable */
DECL|macro|UIRCC_CR3_MCAST_EN
mdefine_line|#define UIRCC_CR3_MCAST_EN  0x04 /* Multicast enable */
DECL|macro|UIRCC_CR4
mdefine_line|#define UIRCC_CR4           0x04 /* Transmit data length low byte */
DECL|macro|UIRCC_CR5
mdefine_line|#define UIRCC_CR5           0x05 /* Transmit data length high byte */
DECL|macro|UIRCC_CR6
mdefine_line|#define UIRCC_CR6           0x06 /* Transmit data writing low byte */
DECL|macro|UIRCC_CR7
mdefine_line|#define UIRCC_CR7           0x07 /* Transmit data writing high byte */
DECL|macro|UIRCC_CR8
mdefine_line|#define UIRCC_CR8           0x08 /* Self pole address */
DECL|macro|UIRCC_CR9
mdefine_line|#define UIRCC_CR9           0x09 /* System control 1 */
DECL|macro|UIRCC_CR10
mdefine_line|#define UIRCC_CR10          0x0a /* Modem selection */
DECL|macro|UIRCC_CR10_SIR
mdefine_line|#define UIRCC_CR10_SIR      0x22 /* Set SIR mode */
DECL|macro|UIRCC_CR10_FIR
mdefine_line|#define UIRCC_CR10_FIR      0x88 /* Set FIR mode */
DECL|macro|UIRCC_CR11
mdefine_line|#define UIRCC_CR11          0x0b /* System control 2 (same as SR11) */
DECL|macro|UIRCC_CR11_TMR_EN
mdefine_line|#define UIRCC_CR11_TMR_EN   0x08
DECL|macro|UIRCC_CR12
mdefine_line|#define UIRCC_CR12          0x0c /* Timer counter initial value (low byte) */
DECL|macro|UIRCC_CR13
mdefine_line|#define UIRCC_CR13          0x0d /* Timer counter initial value (high byte) */
multiline_comment|/* Status registers (read only) */
DECL|macro|UIRCC_SR0
mdefine_line|#define UIRCC_SR0           0x00 /* Transmit/receive status register */
DECL|macro|UIRCC_SR0_RX_RDY
mdefine_line|#define UIRCC_SR0_RX_RDY    0x80 /* Received data ready */
DECL|macro|UIRCC_SR0_RX_OVR
mdefine_line|#define UIRCC_SR0_RX_OVR    0x40 /* Receive overrun error */
DECL|macro|UIRCC_SR0_RX_CRCFRM
mdefine_line|#define UIRCC_SR0_RX_CRCFRM 0x20 /* Receive CRC or framing error */
DECL|macro|UIRCC_SR2
mdefine_line|#define UIRCC_SR2           0x02 /* Interrupt mask status */
DECL|macro|UIRCC_SR3
mdefine_line|#define UIRCC_SR3           0x03 /* Interrupt factor register */
DECL|macro|UIRCC_SR3_RX_OVR_ER
mdefine_line|#define UIRCC_SR3_RX_OVR_ER 0x40 /* Receive overrun error */
DECL|macro|UIRCC_SR3_RX_FRM_ER
mdefine_line|#define UIRCC_SR3_RX_FRM_ER 0x20 /* Receive frameing error */
DECL|macro|UIRCC_SR3_RX_EOF
mdefine_line|#define UIRCC_SR3_RX_EOF    0x10 /* Receive end of frame */
DECL|macro|UIRCC_SR3_TMR_OUT
mdefine_line|#define UIRCC_SR3_TMR_OUT   0x08 /* Timer timeout */
DECL|macro|UIRCC_SR3_TXUR
mdefine_line|#define UIRCC_SR3_TXUR      0x04 /* Transmit underrun */
DECL|macro|UIRCC_SR3_TX_DONE
mdefine_line|#define UIRCC_SR3_TX_DONE   0x01 /* Transmit all sent */
DECL|macro|UIRCC_SR4
mdefine_line|#define UIRCC_SR4           0x04 /* TX/RX data length counter low byte */
DECL|macro|UIRCC_SR5
mdefine_line|#define UIRCC_SR5           0x05 /* TX/RX data length counter high byte */
DECL|macro|UIRCC_SR8
mdefine_line|#define UIRCC_SR8           0x08 /* Chip version */
DECL|macro|UIRCC_SR9
mdefine_line|#define UIRCC_SR9           0x09 /* System status 1 */
DECL|macro|UIRCC_SR10
mdefine_line|#define UIRCC_SR10          0x0a /* Modem select status */
DECL|macro|UIRCC_SR12
mdefine_line|#define UIRCC_SR12          0x0c /* Timer counter status (low byte) */
DECL|macro|UIRCC_SR13
mdefine_line|#define UIRCC_SR13          0x0d /* Timer counter status (high byte) */
multiline_comment|/* Private data for each instance */
DECL|struct|uircc_cb
r_struct
id|uircc_cb
(brace
DECL|member|idev
r_struct
id|irda_device
id|idev
suffix:semicolon
DECL|member|cr3
id|__u8
id|cr3
suffix:semicolon
multiline_comment|/* Copy of register sr3 */
)brace
suffix:semicolon
DECL|macro|CR3_SET
mdefine_line|#define CR3_SET
macro_line|#endif
eof
