DECL|struct|cyclades_card
r_struct
id|cyclades_card
(brace
DECL|member|base_addr
r_int
id|base_addr
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|num_chips
r_int
id|num_chips
suffix:semicolon
multiline_comment|/* implies card type, 0 if card is absent */
DECL|member|first_line
r_int
id|first_line
suffix:semicolon
multiline_comment|/* line number of first channel of first chip on card */
)brace
suffix:semicolon
DECL|struct|cyclades_chip
r_struct
id|cyclades_chip
(brace
DECL|member|filler
r_int
id|filler
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cyclades_monitor
r_struct
id|cyclades_monitor
(brace
DECL|member|int_count
r_int
r_int
id|int_count
suffix:semicolon
DECL|member|char_count
r_int
r_int
id|char_count
suffix:semicolon
DECL|member|char_max
r_int
r_int
id|char_max
suffix:semicolon
DECL|member|char_last
r_int
r_int
id|char_last
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|cyclades_port
r_struct
id|cyclades_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|card
r_int
id|card
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|cor1
DECL|member|cor2
DECL|member|cor3
DECL|member|cor4
DECL|member|cor5
r_int
id|cor1
comma
id|cor2
comma
id|cor3
comma
id|cor4
comma
id|cor5
suffix:semicolon
DECL|member|tbpr
DECL|member|tco
DECL|member|rbpr
DECL|member|rco
r_int
id|tbpr
comma
id|tco
comma
id|rbpr
comma
id|rco
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|IER
r_int
id|IER
suffix:semicolon
multiline_comment|/* Interrupt Enable Register */
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* to be pushed out ASAP */
DECL|member|x_break
r_int
id|x_break
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|default_threshold
r_int
id|default_threshold
suffix:semicolon
DECL|member|default_timeout
r_int
id|default_timeout
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
DECL|member|mon
r_struct
id|cyclades_monitor
id|mon
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CYCLADES_MAGIC
mdefine_line|#define CYCLADES_MAGIC  0x4359
DECL|macro|CYGETMON
mdefine_line|#define CYGETMON                0x435901
DECL|macro|CYGETTHRESH
mdefine_line|#define CYGETTHRESH             0x435902
DECL|macro|CYSETTHRESH
mdefine_line|#define CYSETTHRESH             0x435903
DECL|macro|CYGETDEFTHRESH
mdefine_line|#define CYGETDEFTHRESH          0x435904
DECL|macro|CYSETDEFTHRESH
mdefine_line|#define CYSETDEFTHRESH          0x435905
DECL|macro|CYGETTIMEOUT
mdefine_line|#define CYGETTIMEOUT            0x435906
DECL|macro|CYSETTIMEOUT
mdefine_line|#define CYSETTIMEOUT            0x435907
DECL|macro|CYGETDEFTIMEOUT
mdefine_line|#define CYGETDEFTIMEOUT         0x435908
DECL|macro|CYSETDEFTIMEOUT
mdefine_line|#define CYSETDEFTIMEOUT         0x435909
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at cy interrupt time.&n; */
DECL|macro|Cy_EVENT_READ_PROCESS
mdefine_line|#define Cy_EVENT_READ_PROCESS&t;0
DECL|macro|Cy_EVENT_WRITE_WAKEUP
mdefine_line|#define Cy_EVENT_WRITE_WAKEUP&t;1
DECL|macro|Cy_EVENT_HANGUP
mdefine_line|#define Cy_EVENT_HANGUP&t;&t;2
DECL|macro|Cy_EVENT_BREAK
mdefine_line|#define Cy_EVENT_BREAK&t;&t;3
DECL|macro|Cy_EVENT_OPEN_WAKEUP
mdefine_line|#define Cy_EVENT_OPEN_WAKEUP&t;4
DECL|macro|CyMaxChipsPerCard
mdefine_line|#define CyMaxChipsPerCard 8
multiline_comment|/**** CD1400 registers ****/
DECL|macro|CyRegSize
mdefine_line|#define CyRegSize  0x0400
DECL|macro|Cy_HwReset
mdefine_line|#define Cy_HwReset 0x1400
DECL|macro|Cy_ClrIntr
mdefine_line|#define Cy_ClrIntr 0x1800
multiline_comment|/* Global Registers */
DECL|macro|CyGFRCR
mdefine_line|#define CyGFRCR&t;&t;(0x40*2)
DECL|macro|CyRevE
mdefine_line|#define      CyRevE&t;&t;(44)
DECL|macro|CyCAR
mdefine_line|#define CyCAR&t;&t;(0x68*2)
DECL|macro|CyCHAN_0
mdefine_line|#define      CyCHAN_0&t;&t;(0x00)
DECL|macro|CyCHAN_1
mdefine_line|#define      CyCHAN_1&t;&t;(0x01)
DECL|macro|CyCHAN_2
mdefine_line|#define      CyCHAN_2&t;&t;(0x02)
DECL|macro|CyCHAN_3
mdefine_line|#define      CyCHAN_3&t;&t;(0x03)
DECL|macro|CyGCR
mdefine_line|#define CyGCR&t;&t;(0x4B*2)
DECL|macro|CyCH0_SERIAL
mdefine_line|#define      CyCH0_SERIAL&t;(0x00)
DECL|macro|CyCH0_PARALLEL
mdefine_line|#define      CyCH0_PARALLEL&t;(0x80)
DECL|macro|CySVRR
mdefine_line|#define CySVRR&t;&t;(0x67*2)
DECL|macro|CySRModem
mdefine_line|#define      CySRModem&t;&t;(0x04)
DECL|macro|CySRTransmit
mdefine_line|#define      CySRTransmit&t;(0x02)
DECL|macro|CySRReceive
mdefine_line|#define      CySRReceive&t;(0x01)
DECL|macro|CyRICR
mdefine_line|#define CyRICR&t;&t;(0x44*2)
DECL|macro|CyTICR
mdefine_line|#define CyTICR&t;&t;(0x45*2)
DECL|macro|CyMICR
mdefine_line|#define CyMICR&t;&t;(0x46*2)
DECL|macro|CyICR0
mdefine_line|#define      CyICR0&t;&t;(0x00)
DECL|macro|CyICR1
mdefine_line|#define      CyICR1&t;&t;(0x01)
DECL|macro|CyICR2
mdefine_line|#define      CyICR2&t;&t;(0x02)
DECL|macro|CyICR3
mdefine_line|#define      CyICR3&t;&t;(0x03)
DECL|macro|CyRIR
mdefine_line|#define CyRIR&t;&t;(0x6B*2)
DECL|macro|CyTIR
mdefine_line|#define CyTIR&t;&t;(0x6A*2)
DECL|macro|CyMIR
mdefine_line|#define CyMIR&t;&t;(0x69*2)
DECL|macro|CyIRDirEq
mdefine_line|#define      CyIRDirEq&t;&t;(0x80)
DECL|macro|CyIRBusy
mdefine_line|#define      CyIRBusy&t;&t;(0x40)
DECL|macro|CyIRUnfair
mdefine_line|#define      CyIRUnfair&t;&t;(0x20)
DECL|macro|CyIRContext
mdefine_line|#define      CyIRContext&t;(0x1C)
DECL|macro|CyIRChannel
mdefine_line|#define      CyIRChannel&t;(0x03)
DECL|macro|CyPPR
mdefine_line|#define CyPPR &t;&t;(0x7E*2)
DECL|macro|CyCLOCK_20_1MS
mdefine_line|#define      CyCLOCK_20_1MS&t;(0x27)
DECL|macro|CyCLOCK_25_1MS
mdefine_line|#define      CyCLOCK_25_1MS&t;(0x31)
multiline_comment|/* Virtual Registers */
DECL|macro|CyRIVR
mdefine_line|#define CyRIVR&t;&t;(0x43*2)
DECL|macro|CyTIVR
mdefine_line|#define CyTIVR&t;&t;(0x42*2)
DECL|macro|CyMIVR
mdefine_line|#define CyMIVR&t;&t;(0x41*2)
DECL|macro|CyIVRMask
mdefine_line|#define      CyIVRMask (0x07)
DECL|macro|CyIVRRxEx
mdefine_line|#define      CyIVRRxEx (0x07)
DECL|macro|CyIVRRxOK
mdefine_line|#define      CyIVRRxOK (0x03)
DECL|macro|CyIVRTxOK
mdefine_line|#define      CyIVRTxOK (0x02)
DECL|macro|CyIVRMdmOK
mdefine_line|#define      CyIVRMdmOK (0x01)
DECL|macro|CyTDR
mdefine_line|#define CyTDR&t;&t;(0x63*2)
DECL|macro|CyRDSR
mdefine_line|#define CyRDSR&t;&t;(0x62*2)
DECL|macro|CyTIMEOUT
mdefine_line|#define      CyTIMEOUT&t;&t;(0x80)
DECL|macro|CySPECHAR
mdefine_line|#define      CySPECHAR&t;&t;(0x70)
DECL|macro|CyBREAK
mdefine_line|#define      CyBREAK&t;&t;(0x08)
DECL|macro|CyPARITY
mdefine_line|#define      CyPARITY&t;&t;(0x04)
DECL|macro|CyFRAME
mdefine_line|#define      CyFRAME&t;&t;(0x02)
DECL|macro|CyOVERRUN
mdefine_line|#define      CyOVERRUN&t;&t;(0x01)
DECL|macro|CyMISR
mdefine_line|#define CyMISR&t;&t;(0x4C*2)
multiline_comment|/* see CyMCOR_ and CyMSVR_ for bits*/
DECL|macro|CyEOSRR
mdefine_line|#define CyEOSRR&t;&t;(0x60*2)
multiline_comment|/* Channel Registers */
DECL|macro|CyLIVR
mdefine_line|#define CyLIVR&t;&t;(0x18*2)
DECL|macro|CyMscsr
mdefine_line|#define      CyMscsr&t;&t;(0x01)
DECL|macro|CyTdsr
mdefine_line|#define      CyTdsr&t;&t;(0x02)
DECL|macro|CyRgdsr
mdefine_line|#define      CyRgdsr&t;&t;(0x03)
DECL|macro|CyRedsr
mdefine_line|#define      CyRedsr&t;&t;(0x07)
DECL|macro|CyCCR
mdefine_line|#define CyCCR&t;&t;(0x05*2)
multiline_comment|/* Format 1 */
DECL|macro|CyCHAN_RESET
mdefine_line|#define      CyCHAN_RESET&t;(0x80)
DECL|macro|CyCHIP_RESET
mdefine_line|#define      CyCHIP_RESET&t;(0x81)
DECL|macro|CyFlushTransFIFO
mdefine_line|#define      CyFlushTransFIFO&t;(0x82)
multiline_comment|/* Format 2 */
DECL|macro|CyCOR_CHANGE
mdefine_line|#define      CyCOR_CHANGE&t;(0x40)
DECL|macro|CyCOR1ch
mdefine_line|#define      CyCOR1ch&t;&t;(0x02)
DECL|macro|CyCOR2ch
mdefine_line|#define      CyCOR2ch&t;&t;(0x04)
DECL|macro|CyCOR3ch
mdefine_line|#define      CyCOR3ch&t;&t;(0x08)
multiline_comment|/* Format 3 */
DECL|macro|CySEND_SPEC_1
mdefine_line|#define      CySEND_SPEC_1&t;(0x21)
DECL|macro|CySEND_SPEC_2
mdefine_line|#define      CySEND_SPEC_2&t;(0x22)
DECL|macro|CySEND_SPEC_3
mdefine_line|#define      CySEND_SPEC_3&t;(0x23)
DECL|macro|CySEND_SPEC_4
mdefine_line|#define      CySEND_SPEC_4&t;(0x24)
multiline_comment|/* Format 4 */
DECL|macro|CyCHAN_CTL
mdefine_line|#define      CyCHAN_CTL&t;&t;(0x10)
DECL|macro|CyDIS_RCVR
mdefine_line|#define      CyDIS_RCVR&t;&t;(0x01)
DECL|macro|CyENB_RCVR
mdefine_line|#define      CyENB_RCVR&t;&t;(0x02)
DECL|macro|CyDIS_XMTR
mdefine_line|#define      CyDIS_XMTR&t;&t;(0x04)
DECL|macro|CyENB_XMTR
mdefine_line|#define      CyENB_XMTR&t;&t;(0x08)
DECL|macro|CySRER
mdefine_line|#define CySRER&t;&t;(0x06*2)
DECL|macro|CyMdmCh
mdefine_line|#define      CyMdmCh&t;&t;(0x80)
DECL|macro|CyRxData
mdefine_line|#define      CyRxData&t;&t;(0x10)
DECL|macro|CyTxRdy
mdefine_line|#define      CyTxRdy&t;&t;(0x04)
DECL|macro|CyTxMpty
mdefine_line|#define      CyTxMpty&t;&t;(0x02)
DECL|macro|CyNNDT
mdefine_line|#define      CyNNDT&t;&t;(0x01)
DECL|macro|CyCOR1
mdefine_line|#define CyCOR1&t;&t;(0x08*2)
DECL|macro|CyPARITY_NONE
mdefine_line|#define      CyPARITY_NONE&t;(0x00)
DECL|macro|CyPARITY_0
mdefine_line|#define      CyPARITY_0&t;&t;(0x20)
DECL|macro|CyPARITY_1
mdefine_line|#define      CyPARITY_1&t;&t;(0xA0)
DECL|macro|CyPARITY_E
mdefine_line|#define      CyPARITY_E&t;&t;(0x40)
DECL|macro|CyPARITY_O
mdefine_line|#define      CyPARITY_O&t;&t;(0xC0)
DECL|macro|Cy_1_STOP
mdefine_line|#define      Cy_1_STOP&t;&t;(0x00)
DECL|macro|Cy_1_5_STOP
mdefine_line|#define      Cy_1_5_STOP&t;(0x04)
DECL|macro|Cy_2_STOP
mdefine_line|#define      Cy_2_STOP&t;&t;(0x08)
DECL|macro|Cy_5_BITS
mdefine_line|#define      Cy_5_BITS&t;&t;(0x00)
DECL|macro|Cy_6_BITS
mdefine_line|#define      Cy_6_BITS&t;&t;(0x01)
DECL|macro|Cy_7_BITS
mdefine_line|#define      Cy_7_BITS&t;&t;(0x02)
DECL|macro|Cy_8_BITS
mdefine_line|#define      Cy_8_BITS&t;&t;(0x03)
DECL|macro|CyCOR2
mdefine_line|#define CyCOR2&t;&t;(0x09*2)
DECL|macro|CyIXM
mdefine_line|#define      CyIXM&t;&t;(0x80)
DECL|macro|CyTxIBE
mdefine_line|#define      CyTxIBE&t;&t;(0x40)
DECL|macro|CyETC
mdefine_line|#define      CyETC&t;&t;(0x20)
DECL|macro|CyAUTO_TXFL
mdefine_line|#define      CyAUTO_TXFL&t;(0x60)
DECL|macro|CyLLM
mdefine_line|#define      CyLLM&t;&t;(0x10)
DECL|macro|CyRLM
mdefine_line|#define      CyRLM&t;&t;(0x08)
DECL|macro|CyRtsAO
mdefine_line|#define      CyRtsAO&t;&t;(0x04)
DECL|macro|CyCtsAE
mdefine_line|#define      CyCtsAE&t;&t;(0x02)
DECL|macro|CyDsrAE
mdefine_line|#define      CyDsrAE&t;&t;(0x01)
DECL|macro|CyCOR3
mdefine_line|#define CyCOR3&t;&t;(0x0A*2)
DECL|macro|CySPL_CH_DRANGE
mdefine_line|#define      CySPL_CH_DRANGE&t;(0x80)  /* special character detect range */
DECL|macro|CySPL_CH_DET1
mdefine_line|#define      CySPL_CH_DET1&t;(0x40)  /* enable special character detection&n;                                                               on SCHR4-SCHR3 */
DECL|macro|CyFL_CTRL_TRNSP
mdefine_line|#define      CyFL_CTRL_TRNSP&t;(0x20)  /* Flow Control Transparency */
DECL|macro|CySPL_CH_DET2
mdefine_line|#define      CySPL_CH_DET2&t;(0x10)  /* Enable special character detection&n;                                                               on SCHR2-SCHR1 */
DECL|macro|CyREC_FIFO
mdefine_line|#define      CyREC_FIFO&t;&t;(0x0F)  /* Receive FIFO threshold */
DECL|macro|CyCOR4
mdefine_line|#define CyCOR4&t;&t;(0x1E*2)
DECL|macro|CyCOR5
mdefine_line|#define CyCOR5&t;&t;(0x1F*2)
DECL|macro|CyCCSR
mdefine_line|#define CyCCSR&t;&t;(0x0B*2)
DECL|macro|CyRxEN
mdefine_line|#define      CyRxEN&t;&t;(0x80)
DECL|macro|CyRxFloff
mdefine_line|#define      CyRxFloff&t;&t;(0x40)
DECL|macro|CyRxFlon
mdefine_line|#define      CyRxFlon&t;&t;(0x20)
DECL|macro|CyTxEN
mdefine_line|#define      CyTxEN&t;&t;(0x08)
DECL|macro|CyTxFloff
mdefine_line|#define      CyTxFloff&t;&t;(0x04)
DECL|macro|CyTxFlon
mdefine_line|#define      CyTxFlon&t;&t;(0x02)
DECL|macro|CyRDCR
mdefine_line|#define CyRDCR&t;&t;(0x0E*2)
DECL|macro|CySCHR1
mdefine_line|#define CySCHR1&t;&t;(0x1A*2)
DECL|macro|CySCHR2
mdefine_line|#define CySCHR2 &t;(0x1B*2)
DECL|macro|CySCHR3
mdefine_line|#define CySCHR3&t;&t;(0x1C*2)
DECL|macro|CySCHR4
mdefine_line|#define CySCHR4&t;&t;(0x1D*2)
DECL|macro|CySCRL
mdefine_line|#define CySCRL&t;&t;(0x22*2)
DECL|macro|CySCRH
mdefine_line|#define CySCRH&t;&t;(0x23*2)
DECL|macro|CyLNC
mdefine_line|#define CyLNC&t;&t;(0x24*2)
DECL|macro|CyMCOR1
mdefine_line|#define CyMCOR1 &t;(0x15*2)
DECL|macro|CyMCOR2
mdefine_line|#define CyMCOR2&t;&t;(0x16*2)
DECL|macro|CyRTPR
mdefine_line|#define CyRTPR&t;&t;(0x21*2)
DECL|macro|CyMSVR1
mdefine_line|#define CyMSVR1&t;&t;(0x6C*2)
DECL|macro|CyMSVR2
mdefine_line|#define CyMSVR2&t;&t;(0x6D*2)
DECL|macro|CyDSR
mdefine_line|#define      CyDSR&t;&t;(0x80)
DECL|macro|CyCTS
mdefine_line|#define      CyCTS&t;&t;(0x40)
DECL|macro|CyRI
mdefine_line|#define      CyRI&t;&t;(0x20)
DECL|macro|CyDCD
mdefine_line|#define      CyDCD&t;&t;(0x10)
DECL|macro|CyDTR
mdefine_line|#define      CyDTR              (0x02)
DECL|macro|CyRTS
mdefine_line|#define      CyRTS              (0x01)
DECL|macro|CyPVSR
mdefine_line|#define CyPVSR&t;&t;(0x6F*2)
DECL|macro|CyRBPR
mdefine_line|#define CyRBPR&t;&t;(0x78*2)
DECL|macro|CyRCOR
mdefine_line|#define CyRCOR&t;&t;(0x7C*2)
DECL|macro|CyTBPR
mdefine_line|#define CyTBPR&t;&t;(0x72*2)
DECL|macro|CyTCOR
mdefine_line|#define CyTCOR&t;&t;(0x76*2)
multiline_comment|/* max number of chars in the FIFO */
DECL|macro|CyMAX_CHAR_FIFO
mdefine_line|#define CyMAX_CHAR_FIFO&t;12
multiline_comment|/***************************************************************************/
eof
