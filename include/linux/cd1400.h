multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;cd1400.h  -- cd1400 UART hardware info.&n; *&n; *&t;Copyright (C) 1994,1995  Greg Ungerer (gerg@stallion.oz.au).&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef&t;_CD1400_H
DECL|macro|_CD1400_H
mdefine_line|#define&t;_CD1400_H
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the number of async ports per cd1400 uart chip.&n; */
DECL|macro|CD1400_PORTS
mdefine_line|#define&t;CD1400_PORTS&t;&t;4
DECL|macro|CD1400_CLKHZ
mdefine_line|#define&t;CD1400_CLKHZ&t;&t;25000000
multiline_comment|/*&n; *&t;Define the cd1400 uarts internal FIFO sizes.&n; */
DECL|macro|CD1400_TXFIFOSIZE
mdefine_line|#define&t;CD1400_TXFIFOSIZE&t;12
DECL|macro|CD1400_RXFIFOSIZE
mdefine_line|#define&t;CD1400_RXFIFOSIZE&t;12
multiline_comment|/*&n; *&t;Local RX FIFO thresh hold level. Also define the RTS thresh hold&n; *&t;based on the RX thresh hold.&n; */
DECL|macro|FIFO_RXTHRESHOLD
mdefine_line|#define&t;FIFO_RXTHRESHOLD&t;6
DECL|macro|FIFO_RTSTHRESHOLD
mdefine_line|#define&t;FIFO_RTSTHRESHOLD&t;7
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the cd1400 register addresses. These are all the valid&n; *&t;registers with the cd1400. Some are global, some virtual, some&n; *&t;per port.&n; */
DECL|macro|GFRCR
mdefine_line|#define&t;GFRCR&t;&t;0x40
DECL|macro|CAR
mdefine_line|#define&t;CAR&t;&t;0x68
DECL|macro|GCR
mdefine_line|#define&t;GCR&t;&t;0x4b
DECL|macro|SVRR
mdefine_line|#define&t;SVRR&t;&t;0x67
DECL|macro|RICR
mdefine_line|#define&t;RICR&t;&t;0x44
DECL|macro|TICR
mdefine_line|#define&t;TICR&t;&t;0x45
DECL|macro|MICR
mdefine_line|#define&t;MICR&t;&t;0x46
DECL|macro|RIR
mdefine_line|#define&t;RIR&t;&t;0x6b
DECL|macro|TIR
mdefine_line|#define&t;TIR&t;&t;0x6a
DECL|macro|MIR
mdefine_line|#define&t;MIR&t;&t;0x69
DECL|macro|PPR
mdefine_line|#define&t;PPR&t;&t;0x7e
DECL|macro|RIVR
mdefine_line|#define&t;RIVR&t;&t;0x43
DECL|macro|TIVR
mdefine_line|#define&t;TIVR&t;&t;0x42
DECL|macro|MIVR
mdefine_line|#define&t;MIVR&t;&t;0x41
DECL|macro|TDR
mdefine_line|#define&t;TDR&t;&t;0x63
DECL|macro|RDSR
mdefine_line|#define&t;RDSR&t;&t;0x62
DECL|macro|MISR
mdefine_line|#define&t;MISR&t;&t;0x4c
DECL|macro|EOSRR
mdefine_line|#define&t;EOSRR&t;&t;0x60
DECL|macro|LIVR
mdefine_line|#define&t;LIVR&t;&t;0x18
DECL|macro|CCR
mdefine_line|#define&t;CCR&t;&t;0x05
DECL|macro|SRER
mdefine_line|#define&t;SRER&t;&t;0x06
DECL|macro|COR1
mdefine_line|#define&t;COR1&t;&t;0x08
DECL|macro|COR2
mdefine_line|#define&t;COR2&t;&t;0x09
DECL|macro|COR3
mdefine_line|#define&t;COR3&t;&t;0x0a
DECL|macro|COR4
mdefine_line|#define&t;COR4&t;&t;0x1e
DECL|macro|COR5
mdefine_line|#define&t;COR5&t;&t;0x1f
DECL|macro|CCSR
mdefine_line|#define&t;CCSR&t;&t;0x0b
DECL|macro|RDCR
mdefine_line|#define&t;RDCR&t;&t;0x0e
DECL|macro|SCHR1
mdefine_line|#define&t;SCHR1&t;&t;0x1a
DECL|macro|SCHR2
mdefine_line|#define&t;SCHR2&t;&t;0x1b
DECL|macro|SCHR3
mdefine_line|#define&t;SCHR3&t;&t;0x1c
DECL|macro|SCHR4
mdefine_line|#define&t;SCHR4&t;&t;0x1d
DECL|macro|SCRL
mdefine_line|#define&t;SCRL&t;&t;0x22
DECL|macro|SCRH
mdefine_line|#define&t;SCRH&t;&t;0x23
DECL|macro|LNC
mdefine_line|#define&t;LNC&t;&t;0x24
DECL|macro|MCOR1
mdefine_line|#define&t;MCOR1&t;&t;0x15
DECL|macro|MCOR2
mdefine_line|#define&t;MCOR2&t;&t;0x16
DECL|macro|RTPR
mdefine_line|#define&t;RTPR&t;&t;0x21
DECL|macro|MSVR1
mdefine_line|#define&t;MSVR1&t;&t;0x6c
DECL|macro|MSVR2
mdefine_line|#define&t;MSVR2&t;&t;0x6d
DECL|macro|PSVR
mdefine_line|#define&t;PSVR&t;&t;0x6f
DECL|macro|RBPR
mdefine_line|#define&t;RBPR&t;&t;0x78
DECL|macro|RCOR
mdefine_line|#define&t;RCOR&t;&t;0x7c
DECL|macro|TBPR
mdefine_line|#define&t;TBPR&t;&t;0x72
DECL|macro|TCOR
mdefine_line|#define&t;TCOR&t;&t;0x76
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the set of baud rate clock divisors.&n; */
DECL|macro|CD1400_CLK0
mdefine_line|#define&t;CD1400_CLK0&t;8
DECL|macro|CD1400_CLK1
mdefine_line|#define&t;CD1400_CLK1&t;32
DECL|macro|CD1400_CLK2
mdefine_line|#define&t;CD1400_CLK2&t;128
DECL|macro|CD1400_CLK3
mdefine_line|#define&t;CD1400_CLK3&t;512
DECL|macro|CD1400_CLK4
mdefine_line|#define&t;CD1400_CLK4&t;2048
DECL|macro|CD1400_NUMCLKS
mdefine_line|#define&t;CD1400_NUMCLKS&t;5
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the clock pre-scalar value to be a 5 ms clock. This should be&n; *&t;OK for now. It would probably be better to make it 10 ms, but we&n; *&t;can&squot;t fit that divisor into 8 bits!&n; */
DECL|macro|PPR_SCALAR
mdefine_line|#define&t;PPR_SCALAR&t;244
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define values used to set character size options.&n; */
DECL|macro|COR1_CHL5
mdefine_line|#define&t;COR1_CHL5&t;0x00
DECL|macro|COR1_CHL6
mdefine_line|#define&t;COR1_CHL6&t;0x01
DECL|macro|COR1_CHL7
mdefine_line|#define&t;COR1_CHL7&t;0x02
DECL|macro|COR1_CHL8
mdefine_line|#define&t;COR1_CHL8&t;0x03
multiline_comment|/*&n; *&t;Define values used to set the number of stop bits.&n; */
DECL|macro|COR1_STOP1
mdefine_line|#define&t;COR1_STOP1&t;0x00
DECL|macro|COR1_STOP15
mdefine_line|#define&t;COR1_STOP15&t;0x04
DECL|macro|COR1_STOP2
mdefine_line|#define&t;COR1_STOP2&t;0x08
multiline_comment|/*&n; *&t;Define values used to set the parity scheme in use.&n; */
DECL|macro|COR1_PARNONE
mdefine_line|#define&t;COR1_PARNONE&t;0x00
DECL|macro|COR1_PARFORCE
mdefine_line|#define&t;COR1_PARFORCE&t;0x20
DECL|macro|COR1_PARENB
mdefine_line|#define&t;COR1_PARENB&t;0x40
DECL|macro|COR1_PARIGNORE
mdefine_line|#define&t;COR1_PARIGNORE&t;0x10
DECL|macro|COR1_PARODD
mdefine_line|#define&t;COR1_PARODD&t;0x80
DECL|macro|COR1_PAREVEN
mdefine_line|#define&t;COR1_PAREVEN&t;0x00
DECL|macro|COR2_IXM
mdefine_line|#define&t;COR2_IXM&t;0x80
DECL|macro|COR2_TXIBE
mdefine_line|#define&t;COR2_TXIBE&t;0x40
DECL|macro|COR2_ETC
mdefine_line|#define&t;COR2_ETC&t;0x20
DECL|macro|COR2_LLM
mdefine_line|#define&t;COR2_LLM&t;0x10
DECL|macro|COR2_RLM
mdefine_line|#define&t;COR2_RLM&t;0x08
DECL|macro|COR2_RTSAO
mdefine_line|#define&t;COR2_RTSAO&t;0x04
DECL|macro|COR2_CTSAE
mdefine_line|#define&t;COR2_CTSAE&t;0x02
DECL|macro|COR3_SCDRNG
mdefine_line|#define&t;COR3_SCDRNG&t;0x80
DECL|macro|COR3_SCD34
mdefine_line|#define&t;COR3_SCD34&t;0x40
DECL|macro|COR3_FCT
mdefine_line|#define&t;COR3_FCT&t;0x20
DECL|macro|COR3_SCD12
mdefine_line|#define&t;COR3_SCD12&t;0x10
multiline_comment|/*&n; *&t;Define values used by COR4.&n; */
DECL|macro|COR4_BRKINT
mdefine_line|#define&t;COR4_BRKINT&t;0x08
DECL|macro|COR4_IGNBRK
mdefine_line|#define&t;COR4_IGNBRK&t;0x18
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the modem control register values.&n; *&t;Note that the actual hardware is a little different to the conventional&n; *&t;pin names on the cd1400.&n; */
DECL|macro|MSVR1_DTR
mdefine_line|#define&t;MSVR1_DTR&t;0x01
DECL|macro|MSVR1_DSR
mdefine_line|#define&t;MSVR1_DSR&t;0x10
DECL|macro|MSVR1_RI
mdefine_line|#define&t;MSVR1_RI&t;0x20
DECL|macro|MSVR1_CTS
mdefine_line|#define&t;MSVR1_CTS&t;0x40
DECL|macro|MSVR1_DCD
mdefine_line|#define&t;MSVR1_DCD&t;0x80
DECL|macro|MSVR2_RTS
mdefine_line|#define&t;MSVR2_RTS&t;0x02
DECL|macro|MSVR2_DSR
mdefine_line|#define&t;MSVR2_DSR&t;0x10
DECL|macro|MSVR2_RI
mdefine_line|#define&t;MSVR2_RI&t;0x20
DECL|macro|MSVR2_CTS
mdefine_line|#define&t;MSVR2_CTS&t;0x40
DECL|macro|MSVR2_DCD
mdefine_line|#define&t;MSVR2_DCD&t;0x80
DECL|macro|MCOR1_DCD
mdefine_line|#define&t;MCOR1_DCD&t;0x80
DECL|macro|MCOR1_CTS
mdefine_line|#define&t;MCOR1_CTS&t;0x40
DECL|macro|MCOR1_RI
mdefine_line|#define&t;MCOR1_RI&t;0x20
DECL|macro|MCOR1_DSR
mdefine_line|#define&t;MCOR1_DSR&t;0x10
DECL|macro|MCOR2_DCD
mdefine_line|#define&t;MCOR2_DCD&t;0x80
DECL|macro|MCOR2_CTS
mdefine_line|#define&t;MCOR2_CTS&t;0x40
DECL|macro|MCOR2_RI
mdefine_line|#define&t;MCOR2_RI&t;0x20
DECL|macro|MCOR2_DSR
mdefine_line|#define&t;MCOR2_DSR&t;0x10
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the bits used with the service (interrupt) enable register.&n; */
DECL|macro|SRER_NNDT
mdefine_line|#define&t;SRER_NNDT&t;0x01
DECL|macro|SRER_TXEMPTY
mdefine_line|#define&t;SRER_TXEMPTY&t;0x02
DECL|macro|SRER_TXDATA
mdefine_line|#define&t;SRER_TXDATA&t;0x04
DECL|macro|SRER_RXDATA
mdefine_line|#define&t;SRER_RXDATA&t;0x10
DECL|macro|SRER_MODEM
mdefine_line|#define&t;SRER_MODEM&t;0x80
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define operational commands for the command register.&n; */
DECL|macro|CCR_RESET
mdefine_line|#define&t;CCR_RESET&t;0x80
DECL|macro|CCR_CORCHANGE
mdefine_line|#define&t;CCR_CORCHANGE&t;0x4e
DECL|macro|CCR_SENDCH
mdefine_line|#define&t;CCR_SENDCH&t;0x20
DECL|macro|CCR_CHANCTRL
mdefine_line|#define&t;CCR_CHANCTRL&t;0x10
DECL|macro|CCR_TXENABLE
mdefine_line|#define&t;CCR_TXENABLE&t;(CCR_CHANCTRL | 0x08)
DECL|macro|CCR_TXDISABLE
mdefine_line|#define&t;CCR_TXDISABLE&t;(CCR_CHANCTRL | 0x04)
DECL|macro|CCR_RXENABLE
mdefine_line|#define&t;CCR_RXENABLE&t;(CCR_CHANCTRL | 0x02)
DECL|macro|CCR_RXDISABLE
mdefine_line|#define&t;CCR_RXDISABLE&t;(CCR_CHANCTRL | 0x01)
DECL|macro|CCR_SENDSCHR1
mdefine_line|#define&t;CCR_SENDSCHR1&t;(CCR_SENDCH | 0x01)
DECL|macro|CCR_SENDSCHR2
mdefine_line|#define&t;CCR_SENDSCHR2&t;(CCR_SENDCH | 0x02)
DECL|macro|CCR_SENDSCHR3
mdefine_line|#define&t;CCR_SENDSCHR3&t;(CCR_SENDCH | 0x03)
DECL|macro|CCR_SENDSCHR4
mdefine_line|#define&t;CCR_SENDSCHR4&t;(CCR_SENDCH | 0x04)
DECL|macro|CCR_RESETCHAN
mdefine_line|#define&t;CCR_RESETCHAN&t;(CCR_RESET | 0x00)
DECL|macro|CCR_RESETFULL
mdefine_line|#define&t;CCR_RESETFULL&t;(CCR_RESET | 0x01)
DECL|macro|CCR_TXFLUSHFIFO
mdefine_line|#define&t;CCR_TXFLUSHFIFO&t;(CCR_RESET | 0x02)
DECL|macro|CCR_MAXWAIT
mdefine_line|#define&t;CCR_MAXWAIT&t;10000
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the valid acknowledgement types (for hw ack cycle).&n; */
DECL|macro|ACK_TYPMASK
mdefine_line|#define&t;ACK_TYPMASK&t;0x07
DECL|macro|ACK_TYPTX
mdefine_line|#define&t;ACK_TYPTX&t;0x02
DECL|macro|ACK_TYPMDM
mdefine_line|#define&t;ACK_TYPMDM&t;0x01
DECL|macro|ACK_TYPRXGOOD
mdefine_line|#define&t;ACK_TYPRXGOOD&t;0x03
DECL|macro|ACK_TYPRXBAD
mdefine_line|#define&t;ACK_TYPRXBAD&t;0x07
DECL|macro|SVRR_RX
mdefine_line|#define&t;SVRR_RX&t;&t;0x01
DECL|macro|SVRR_TX
mdefine_line|#define&t;SVRR_TX&t;&t;0x02
DECL|macro|SVRR_MDM
mdefine_line|#define&t;SVRR_MDM&t;0x04
DECL|macro|ST_OVERRUN
mdefine_line|#define&t;ST_OVERRUN&t;0x01
DECL|macro|ST_FRAMING
mdefine_line|#define&t;ST_FRAMING&t;0x02
DECL|macro|ST_PARITY
mdefine_line|#define&t;ST_PARITY&t;0x04
DECL|macro|ST_BREAK
mdefine_line|#define&t;ST_BREAK&t;0x08
DECL|macro|ST_SCHAR1
mdefine_line|#define&t;ST_SCHAR1&t;0x10
DECL|macro|ST_SCHAR2
mdefine_line|#define&t;ST_SCHAR2&t;0x20
DECL|macro|ST_SCHAR3
mdefine_line|#define&t;ST_SCHAR3&t;0x30
DECL|macro|ST_SCHAR4
mdefine_line|#define&t;ST_SCHAR4&t;0x40
DECL|macro|ST_RANGE
mdefine_line|#define&t;ST_RANGE&t;0x70
DECL|macro|ST_TIMEOUT
mdefine_line|#define&t;ST_TIMEOUT&t;0x80
DECL|macro|MISR_DCD
mdefine_line|#define&t;MISR_DCD&t;0x80
DECL|macro|MISR_CTS
mdefine_line|#define&t;MISR_CTS&t;0x40
DECL|macro|MISR_RI
mdefine_line|#define&t;MISR_RI&t;&t;0x20
DECL|macro|MISR_DSR
mdefine_line|#define&t;MISR_DSR&t;0x10
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Defines for the CCSR status register.&n; */
DECL|macro|CCSR_RXENABLED
mdefine_line|#define&t;CCSR_RXENABLED&t;0x80
DECL|macro|CCSR_RXFLOWON
mdefine_line|#define&t;CCSR_RXFLOWON&t;0x40
DECL|macro|CCSR_RXFLOWOFF
mdefine_line|#define&t;CCSR_RXFLOWOFF&t;0x20
DECL|macro|CCSR_TXENABLED
mdefine_line|#define&t;CCSR_TXENABLED&t;0x08
DECL|macro|CCSR_TXFLOWON
mdefine_line|#define&t;CCSR_TXFLOWON&t;0x04
DECL|macro|CCSR_TXFLOWOFF
mdefine_line|#define&t;CCSR_TXFLOWOFF&t;0x02
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;Define the embedded commands.&n; */
DECL|macro|ETC_CMD
mdefine_line|#define&t;ETC_CMD&t;&t;0x00
DECL|macro|ETC_STARTBREAK
mdefine_line|#define&t;ETC_STARTBREAK&t;0x81
DECL|macro|ETC_DELAY
mdefine_line|#define&t;ETC_DELAY&t;0x82
DECL|macro|ETC_STOPBREAK
mdefine_line|#define&t;ETC_STOPBREAK&t;0x83
multiline_comment|/*****************************************************************************/
macro_line|#endif
eof