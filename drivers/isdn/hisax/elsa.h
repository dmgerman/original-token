multiline_comment|/* $Id: elsa.h,v 1.6 1997/03/23 21:45:48 keil Exp $&n; *&n; * elsa.h   Header for Elsa ISDN cards&n; *&n; * Author&t;Karsten Keil (keil@temic-ech.spacenet.de)&n; *&n; * Thanks to    Elsa GmbH for documents and informations&n; *&n; *&n; * $Log: elsa.h,v $&n; * Revision 1.6  1997/03/23 21:45:48  keil&n; * Add support for ELSA PCMCIA&n; *&n; * Revision 1.5  1997/03/04 15:58:13  keil&n; * ELSA PC changes, some stuff for new cards&n; *&n; * Revision 1.4  1997/01/21 22:21:05  keil&n; * Elsa Quickstep support&n; *&n; * Revision 1.3  1996/12/08 19:47:38  keil&n; * ARCOFI support&n; *&n; * Revision 1.2  1996/11/18 15:33:35  keil&n; * PCC and PCFPro support&n; *&n; * Revision 1.1  1996/10/13 20:03:45  keil&n; * Initial revision&n; *&n; *&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_HISAX_ELSA_PCMCIA
DECL|macro|CARD_ISAC
mdefine_line|#define CARD_ISAC&t;1
DECL|macro|CARD_HSCX
mdefine_line|#define CARD_HSCX&t;2
DECL|macro|CARD_ALE
mdefine_line|#define CARD_ALE&t;4
macro_line|#else
DECL|macro|CARD_ISAC
mdefine_line|#define CARD_ISAC&t;0
DECL|macro|CARD_ITAC
mdefine_line|#define CARD_ITAC&t;1
DECL|macro|CARD_HSCX
mdefine_line|#define CARD_HSCX&t;2
DECL|macro|CARD_ALE
mdefine_line|#define CARD_ALE&t;3
DECL|macro|CARD_CONTROL
mdefine_line|#define CARD_CONTROL&t;4
DECL|macro|CARD_CONFIG
mdefine_line|#define CARD_CONFIG&t;5
DECL|macro|CARD_START_TIMER
mdefine_line|#define CARD_START_TIMER 6
DECL|macro|CARD_TRIG_IRQ
mdefine_line|#define CARD_TRIG_IRQ&t;7
macro_line|#endif
DECL|macro|ELSA_PC
mdefine_line|#define ELSA_PC      1
DECL|macro|ELSA_PCC8
mdefine_line|#define ELSA_PCC8    2
DECL|macro|ELSA_PCC16
mdefine_line|#define ELSA_PCC16   3
DECL|macro|ELSA_PCF
mdefine_line|#define ELSA_PCF     4
DECL|macro|ELSA_PCFPRO
mdefine_line|#define ELSA_PCFPRO  5
DECL|macro|ELSA_PCMCIA
mdefine_line|#define ELSA_PCMCIA  6
DECL|macro|ELSA_QS1000
mdefine_line|#define ELSA_QS1000  7
DECL|macro|ELSA_QS3000
mdefine_line|#define ELSA_QS3000  8
multiline_comment|/* ITAC Registeradressen (only Microlink PC) */
DECL|macro|ITAC_SYS
mdefine_line|#define ITAC_SYS&t;0x34
DECL|macro|ITAC_ISEN
mdefine_line|#define ITAC_ISEN&t;0x48
DECL|macro|ITAC_RFIE
mdefine_line|#define ITAC_RFIE&t;0x4A
DECL|macro|ITAC_XFIE
mdefine_line|#define ITAC_XFIE&t;0x4C
DECL|macro|ITAC_SCIE
mdefine_line|#define ITAC_SCIE&t;0x4E
DECL|macro|ITAC_STIE
mdefine_line|#define ITAC_STIE&t;0x46
multiline_comment|/***                                                                    ***&n; ***   Makros als Befehle fuer die Kartenregister                       ***&n; ***   (mehrere Befehle werden durch Bit-Oderung kombiniert)            ***&n; ***                                                                    ***/
multiline_comment|/* Config-Register (Read) */
DECL|macro|TIMER_RUN
mdefine_line|#define TIMER_RUN       0x02    /* Bit 1 des Config-Reg     */
DECL|macro|TIMER_RUN_PCC8
mdefine_line|#define TIMER_RUN_PCC8  0x01    /* Bit 0 des Config-Reg  bei PCC */
DECL|macro|IRQ_INDEX
mdefine_line|#define IRQ_INDEX       0x38    /* Bit 3,4,5 des Config-Reg */
DECL|macro|IRQ_INDEX_PCC8
mdefine_line|#define IRQ_INDEX_PCC8  0x30    /* Bit 4,5 des Config-Reg */
DECL|macro|IRQ_INDEX_PC
mdefine_line|#define IRQ_INDEX_PC    0x0c    /* Bit 2,3 des Config-Reg */
multiline_comment|/* Control-Register (Write) */
DECL|macro|LINE_LED
mdefine_line|#define LINE_LED        0x02    /* Bit 1 Gelbe LED */
DECL|macro|STAT_LED
mdefine_line|#define STAT_LED        0x08    /* Bit 3 Gruene LED */
DECL|macro|ISDN_RESET
mdefine_line|#define ISDN_RESET      0x20    /* Bit 5 Reset-Leitung */
DECL|macro|ENABLE_TIM_INT
mdefine_line|#define ENABLE_TIM_INT  0x80    /* Bit 7 Freigabe Timer Interrupt */
multiline_comment|/* ALE-Register (Read) */
DECL|macro|HW_RELEASE
mdefine_line|#define HW_RELEASE      0x07    /* Bit 0-2 Hardwarerkennung */
DECL|macro|S0_POWER_BAD
mdefine_line|#define S0_POWER_BAD    0x08    /* Bit 3 S0-Bus Spannung fehlt */
r_extern
r_void
id|elsa_report
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|sp
)paren
suffix:semicolon
r_extern
r_void
id|release_io_elsa
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|setup_elsa
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|initelsa
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|sp
)paren
suffix:semicolon
eof
