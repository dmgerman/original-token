multiline_comment|/* $Id: sh-sci.h,v 1.5 2000-03-05 13:54:32+09 gniibe Exp $&n; *&n; *  linux/drivers/char/sh-sci.h&n; *&n; *  SuperH on-chip serial module support.  (SCI with no FIFO / with FIFO)&n; *  Copyright (C) 1999, 2000  Niibe Yutaka&n; *  Copyright (C) 2000  Greg Banks&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_SH_SCI_SERIAL)
macro_line|#if defined(__sh3__)
DECL|macro|SCSMR
mdefine_line|#define SCSMR  (volatile unsigned char *)0xfffffe80
DECL|macro|SCBRR
mdefine_line|#define SCBRR  0xfffffe82
DECL|macro|SCSCR
mdefine_line|#define SCSCR  (volatile unsigned char *)0xfffffe84
DECL|macro|SC_TDR
mdefine_line|#define SC_TDR  0xfffffe86
DECL|macro|SC_SR
mdefine_line|#define SC_SR  (volatile unsigned char *)0xfffffe88
DECL|macro|SC_RDR
mdefine_line|#define SC_RDR  0xfffffe8a
DECL|macro|SCSPTR
mdefine_line|#define SCSPTR 0xffffff7c
DECL|macro|SCSCR_INIT
mdefine_line|#define SCSCR_INIT&t;0x30&t;/* TIE=0,RIE=0,TE=1,RE=1 */
macro_line|#elif defined(__SH4__)
id|Not
id|yet
dot
macro_line|#endif
DECL|macro|SCI_TD_E
mdefine_line|#define SCI_TD_E  0x80
DECL|macro|SCI_RD_F
mdefine_line|#define SCI_RD_F  0x40
DECL|macro|SCI_ORER
mdefine_line|#define SCI_ORER  0x20
DECL|macro|SCI_FER
mdefine_line|#define SCI_FER   0x10
DECL|macro|SCI_PER
mdefine_line|#define SCI_PER   0x08
DECL|macro|SCI_TEND
mdefine_line|#define SCI_TEND  0x04
DECL|macro|SCI_ERRORS
mdefine_line|#define SCI_ERRORS ( SCI_PER | SCI_FER | SCI_ORER)
DECL|macro|SCI_TD_E_CLEAR
mdefine_line|#define SCI_TD_E_CLEAR&t;&t;0x78
DECL|macro|SCI_RDRF_CLEAR
mdefine_line|#define SCI_RDRF_CLEAR&t;&t;0xbc
DECL|macro|SCI_ERROR_CLEAR
mdefine_line|#define SCI_ERROR_CLEAR&t;&t;0xc4
DECL|macro|SCI_CTRL_FLAGS_TIE
mdefine_line|#define SCI_CTRL_FLAGS_TIE  0x80
DECL|macro|SCI_CTRL_FLAGS_RIE
mdefine_line|#define SCI_CTRL_FLAGS_RIE  0x40
DECL|macro|SCI_CTRL_FLAGS_TE
mdefine_line|#define SCI_CTRL_FLAGS_TE   0x20
DECL|macro|SCI_CTRL_FLAGS_RE
mdefine_line|#define SCI_CTRL_FLAGS_RE   0x10
multiline_comment|/* TEIE=0x04 */
DECL|macro|SCI_CTRL_FLAGS_CKE1
mdefine_line|#define SCI_CTRL_FLAGS_CKE1 0x02
DECL|macro|SCI_CTRL_FLAGS_CKE0
mdefine_line|#define SCI_CTRL_FLAGS_CKE0 0x01
DECL|macro|RFCR
mdefine_line|#define RFCR    0xffffff74
DECL|macro|SCI_ERI_IRQ
mdefine_line|#define SCI_ERI_IRQ&t;23
DECL|macro|SCI_RXI_IRQ
mdefine_line|#define SCI_RXI_IRQ&t;24
DECL|macro|SCI_TXI_IRQ
mdefine_line|#define SCI_TXI_IRQ&t;25
DECL|macro|SCI_TEI_IRQ
mdefine_line|#define SCI_TEI_IRQ&t;26
DECL|macro|SCI_IRQ_END
mdefine_line|#define SCI_IRQ_END&t;27
DECL|macro|SCI_IPR_OFFSET
mdefine_line|#define SCI_IPR_OFFSET&t;(16+4)
macro_line|#endif
"&f;"
macro_line|#if defined(CONFIG_SH_SCIF_SERIAL)
macro_line|#if defined(__sh3__)
DECL|macro|SCSMR
mdefine_line|#define SCSMR  (volatile unsigned char *)0xA4000150
DECL|macro|SCBRR
mdefine_line|#define SCBRR  0xA4000152
DECL|macro|SCSCR
mdefine_line|#define SCSCR  (volatile unsigned char *)0xA4000154
DECL|macro|SC_TDR
mdefine_line|#define SC_TDR 0xA4000156
DECL|macro|SC_SR
mdefine_line|#define SC_SR  (volatile unsigned short *)0xA4000158
DECL|macro|SC_RDR
mdefine_line|#define SC_RDR 0xA400015A
DECL|macro|SCFCR
mdefine_line|#define SCFCR  (volatile unsigned char *)0xA400015C
DECL|macro|SCFDR
mdefine_line|#define SCFDR  0xA400015E
DECL|macro|SCSPTR
macro_line|#undef  SCSPTR /* Is there any register for RTS?? */
DECL|macro|SCLSR
macro_line|#undef  SCLSR
DECL|macro|RFCR
mdefine_line|#define RFCR   0xffffff74
DECL|macro|SCSCR_INIT
mdefine_line|#define SCSCR_INIT&t;0x30&t;/* TIE=0,RIE=0,TE=1,RE=1 */
multiline_comment|/* 0x33 when external clock is used */
DECL|macro|SCI_IPR_OFFSET
mdefine_line|#define SCI_IPR_OFFSET&t;(64+4)
macro_line|#elif defined(__SH4__)
mdefine_line|#define SCSMR  (volatile unsigned short *)0xFFE80000
mdefine_line|#define SCBRR  0xFFE80004
mdefine_line|#define SCSCR  (volatile unsigned short *)0xFFE80008
mdefine_line|#define SC_TDR 0xFFE8000C
mdefine_line|#define SC_SR  (volatile unsigned short *)0xFFE80010
mdefine_line|#define SC_RDR 0xFFE80014
mdefine_line|#define SCFCR  (volatile unsigned short *)0xFFE80018
mdefine_line|#define SCFDR  0xFFE8001C
mdefine_line|#define SCSPTR 0xFFE80020
mdefine_line|#define SCLSR  0xFFE80024
mdefine_line|#define RFCR   0xFF800028
mdefine_line|#define SCSCR_INIT&t;0x0038&t;/* TIE=0,RIE=0,TE=1,RE=1,REIE=1 */
mdefine_line|#define SCI_IPR_OFFSET&t;(32+4)
macro_line|#endif
DECL|macro|SCI_ER
mdefine_line|#define SCI_ER    0x0080
DECL|macro|SCI_TEND
mdefine_line|#define SCI_TEND  0x0040
DECL|macro|SCI_TD_E
mdefine_line|#define SCI_TD_E  0x0020
DECL|macro|SCI_BRK
mdefine_line|#define SCI_BRK   0x0010
DECL|macro|SCI_FER
mdefine_line|#define SCI_FER   0x0008
DECL|macro|SCI_PER
mdefine_line|#define SCI_PER   0x0004
DECL|macro|SCI_RD_F
mdefine_line|#define SCI_RD_F  0x0002
DECL|macro|SCI_DR
mdefine_line|#define SCI_DR    0x0001
DECL|macro|SCI_ERRORS
mdefine_line|#define SCI_ERRORS ( SCI_PER | SCI_FER | SCI_ER | SCI_BRK)
DECL|macro|SCI_TD_E_CLEAR
mdefine_line|#define SCI_TD_E_CLEAR&t;&t;0x00df
DECL|macro|SCI_TEND_CLEAR
mdefine_line|#define SCI_TEND_CLEAR&t;&t;0x00bf
DECL|macro|SCI_RDRF_CLEAR
mdefine_line|#define SCI_RDRF_CLEAR&t;&t;0x00fc
DECL|macro|SCI_ERROR_CLEAR
mdefine_line|#define SCI_ERROR_CLEAR&t;&t;0x0063
DECL|macro|SCI_CTRL_FLAGS_TIE
mdefine_line|#define SCI_CTRL_FLAGS_TIE  0x80
DECL|macro|SCI_CTRL_FLAGS_RIE
mdefine_line|#define SCI_CTRL_FLAGS_RIE  0x40
DECL|macro|SCI_CTRL_FLAGS_TE
mdefine_line|#define SCI_CTRL_FLAGS_TE   0x20
DECL|macro|SCI_CTRL_FLAGS_RE
mdefine_line|#define SCI_CTRL_FLAGS_RE   0x10
DECL|macro|SCI_CTRL_FLAGS_REIE
mdefine_line|#define SCI_CTRL_FLAGS_REIE 0x08
DECL|macro|SCI_CTRL_FLAGS_CKE1
mdefine_line|#define SCI_CTRL_FLAGS_CKE1 0x02
macro_line|#if defined(__sh3__)
DECL|macro|SCI_ERI_IRQ
mdefine_line|#define SCI_ERI_IRQ&t;56
DECL|macro|SCI_RXI_IRQ
mdefine_line|#define SCI_RXI_IRQ&t;57
DECL|macro|SCI_BRI_IRQ
mdefine_line|#define SCI_BRI_IRQ&t;58
DECL|macro|SCI_TXI_IRQ
mdefine_line|#define SCI_TXI_IRQ&t;59
DECL|macro|SCI_IRQ_END
mdefine_line|#define SCI_IRQ_END&t;60
macro_line|#elif defined(__SH4__)
mdefine_line|#define SCI_ERI_IRQ&t;40
mdefine_line|#define SCI_RXI_IRQ&t;41
mdefine_line|#define SCI_BRI_IRQ&t;42
mdefine_line|#define SCI_TXI_IRQ&t;43
mdefine_line|#define SCI_IRQ_END&t;44
macro_line|#endif
macro_line|#endif
"&f;"
DECL|macro|SCI_PRIORITY
mdefine_line|#define SCI_PRIORITY&t;3
DECL|macro|SCI_MINOR_START
mdefine_line|#define SCI_MINOR_START&t;&t;64
DECL|macro|SCI_RX_THROTTLE
mdefine_line|#define SCI_RX_THROTTLE&t;&t;0x0000001
DECL|macro|O_OTHER
mdefine_line|#define O_OTHER(tty)    &bslash;&n;      ((O_OLCUC(tty))  ||&bslash;&n;      (O_ONLCR(tty))   ||&bslash;&n;      (O_OCRNL(tty))   ||&bslash;&n;      (O_ONOCR(tty))   ||&bslash;&n;      (O_ONLRET(tty))  ||&bslash;&n;      (O_OFILL(tty))   ||&bslash;&n;      (O_OFDEL(tty))   ||&bslash;&n;      (O_NLDLY(tty))   ||&bslash;&n;      (O_CRDLY(tty))   ||&bslash;&n;      (O_TABDLY(tty))  ||&bslash;&n;      (O_BSDLY(tty))   ||&bslash;&n;      (O_VTDLY(tty))   ||&bslash;&n;      (O_FFDLY(tty)))
DECL|macro|I_OTHER
mdefine_line|#define I_OTHER(tty)    &bslash;&n;      ((I_INLCR(tty))  ||&bslash;&n;      (I_IGNCR(tty))   ||&bslash;&n;      (I_ICRNL(tty))   ||&bslash;&n;      (I_IUCLC(tty))   ||&bslash;&n;      (L_ISIG(tty)))
DECL|macro|SCI_MAGIC
mdefine_line|#define SCI_MAGIC 0xbabeface
DECL|struct|sci_port
r_struct
id|sci_port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
DECL|member|old_cflag
r_int
r_int
id|old_cflag
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|WAIT_RFCR_COUNTER
mdefine_line|#define WAIT_RFCR_COUNTER 200
multiline_comment|/*&n; * Values for the BitRate Register (SCBRR)&n; *&n; * The values are actually divisors for a frequency which can&n; * be internal to the SH3 (14.7456MHz) or derived from an external&n; * clock source.  This driver assumes the internal clock is used;&n; * to support using an external clock source, config options or&n; * possibly command-line options would need to be added.&n; *&n; * Also, to support speeds below 2400 (why?) the lower 2 bits of&n; * the SCSMR register would also need to be set to non-zero values.&n; *&n; * -- Greg Banks 27Feb2000&n; */
macro_line|#if defined(__sh3__)
DECL|macro|BPS_2400
mdefine_line|#define BPS_2400       191
DECL|macro|BPS_4800
mdefine_line|#define BPS_4800       95
DECL|macro|BPS_9600
mdefine_line|#define BPS_9600       47
DECL|macro|BPS_19200
mdefine_line|#define BPS_19200      23
DECL|macro|BPS_38400
mdefine_line|#define BPS_38400      11
DECL|macro|BPS_115200
mdefine_line|#define BPS_115200     3
macro_line|#elif defined(__SH4__)
multiline_comment|/* Values for SH-4 please! */
DECL|macro|BPS_115200
mdefine_line|#define BPS_115200     8
macro_line|#endif
eof
