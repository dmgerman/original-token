multiline_comment|/*&n; * The Linux BAYCOM driver for the Baycom serial 1200 baud modem&n; * and the parallel 9600 baud modem&n; * (C) 1996 by Thomas Sailer, HB9JNX&n; */
macro_line|#ifndef _BAYCOM_H
DECL|macro|_BAYCOM_H
mdefine_line|#define _BAYCOM_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* -------------------------------------------------------------------- */
DECL|struct|baycom_statistics
r_struct
id|baycom_statistics
(brace
DECL|member|rx_packets
DECL|member|tx_packets
r_int
r_int
id|rx_packets
comma
id|tx_packets
suffix:semicolon
DECL|member|ptt_keyed
r_int
r_int
id|ptt_keyed
suffix:semicolon
DECL|member|rx_bufferoverrun
DECL|member|tx_bufferoverrun
r_int
r_int
id|rx_bufferoverrun
comma
id|tx_bufferoverrun
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|baycom_params
r_struct
id|baycom_params
(brace
DECL|member|modem_type
r_int
id|modem_type
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|options
r_int
id|options
suffix:semicolon
DECL|member|tx_delay
r_int
id|tx_delay
suffix:semicolon
multiline_comment|/* the transmitter keyup delay in 10ms units */
DECL|member|tx_tail
r_int
id|tx_tail
suffix:semicolon
multiline_comment|/* the transmitter keyoff delay in 10ms units */
DECL|member|slottime
r_int
id|slottime
suffix:semicolon
multiline_comment|/* the slottime in 10ms; usually 10 = 100ms */
DECL|member|ppersist
r_int
id|ppersist
suffix:semicolon
multiline_comment|/* the p-persistence 0..255 */
DECL|member|fulldup
r_int
id|fulldup
suffix:semicolon
multiline_comment|/* the driver does not support full duplex, setting */
multiline_comment|/* this just makes the driver send even if DCD is on */
)brace
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------- */
DECL|macro|BAYCOM_MAJOR
mdefine_line|#define BAYCOM_MAJOR &t;&t;51
multiline_comment|/* maximum packet length, excluding CRC */
DECL|macro|BAYCOM_MAXFLEN
mdefine_line|#define BAYCOM_MAXFLEN &t;&t;400&t;
multiline_comment|/* the ioctl type of this driver */
DECL|macro|BAYCOM_IOCTL_TYPE
mdefine_line|#define BAYCOM_IOCTL_TYPE       &squot;B&squot;
DECL|macro|KISS_FEND
mdefine_line|#define KISS_FEND   ((unsigned char)0300)
DECL|macro|KISS_FESC
mdefine_line|#define KISS_FESC   ((unsigned char)0333)
DECL|macro|KISS_TFEND
mdefine_line|#define KISS_TFEND  ((unsigned char)0334)
DECL|macro|KISS_TFESC
mdefine_line|#define KISS_TFESC  ((unsigned char)0335)
DECL|macro|KISS_CMD_DATA
mdefine_line|#define KISS_CMD_DATA       0
DECL|macro|KISS_CMD_TXDELAY
mdefine_line|#define KISS_CMD_TXDELAY    1
DECL|macro|KISS_CMD_PPERSIST
mdefine_line|#define KISS_CMD_PPERSIST   2
DECL|macro|KISS_CMD_SLOTTIME
mdefine_line|#define KISS_CMD_SLOTTIME   3
DECL|macro|KISS_CMD_TXTAIL
mdefine_line|#define KISS_CMD_TXTAIL     4
DECL|macro|KISS_CMD_FULLDUP
mdefine_line|#define KISS_CMD_FULLDUP    5
multiline_comment|/*&n; * modem types&n; */
DECL|macro|BAYCOM_MODEM_INVALID
mdefine_line|#define BAYCOM_MODEM_INVALID 0
DECL|macro|BAYCOM_MODEM_SER12
mdefine_line|#define BAYCOM_MODEM_SER12   1
DECL|macro|BAYCOM_MODEM_PAR96
mdefine_line|#define BAYCOM_MODEM_PAR96   2
multiline_comment|/*&n; * modem options; bit mask&n; */
DECL|macro|BAYCOM_OPTIONS_SOFTDCD
mdefine_line|#define BAYCOM_OPTIONS_SOFTDCD  1
multiline_comment|/*&n; * ioctl constants&n; */
DECL|macro|BAYCOMCTL_GETDCD
mdefine_line|#define BAYCOMCTL_GETDCD           _IOR(BAYCOM_IOCTL_TYPE, 0, unsigned char)
DECL|macro|BAYCOMCTL_GETPTT
mdefine_line|#define BAYCOMCTL_GETPTT           _IOR(BAYCOM_IOCTL_TYPE, 1, unsigned char)
DECL|macro|BAYCOMCTL_PARAM_TXDELAY
mdefine_line|#define BAYCOMCTL_PARAM_TXDELAY    _IO(BAYCOM_IOCTL_TYPE, 2)
DECL|macro|BAYCOMCTL_PARAM_PPERSIST
mdefine_line|#define BAYCOMCTL_PARAM_PPERSIST   _IO(BAYCOM_IOCTL_TYPE, 3)
DECL|macro|BAYCOMCTL_PARAM_SLOTTIME
mdefine_line|#define BAYCOMCTL_PARAM_SLOTTIME   _IO(BAYCOM_IOCTL_TYPE, 4)
DECL|macro|BAYCOMCTL_PARAM_TXTAIL
mdefine_line|#define BAYCOMCTL_PARAM_TXTAIL     _IO(BAYCOM_IOCTL_TYPE, 5)
DECL|macro|BAYCOMCTL_PARAM_FULLDUP
mdefine_line|#define BAYCOMCTL_PARAM_FULLDUP    _IO(BAYCOM_IOCTL_TYPE, 6)
DECL|macro|BAYCOMCTL_GETSTAT
mdefine_line|#define BAYCOMCTL_GETSTAT          _IOR(BAYCOM_IOCTL_TYPE, 7, &bslash;&n;&t;&t;&t;&t;&t;struct baycom_statistics)
DECL|macro|BAYCOMCTL_GETPARAMS
mdefine_line|#define BAYCOMCTL_GETPARAMS        _IOR(BAYCOM_IOCTL_TYPE, 8, &bslash;&n;&t;&t;&t;&t;&t;struct baycom_params)
DECL|macro|BAYCOMCTL_SETPARAMS
mdefine_line|#define BAYCOMCTL_SETPARAMS        _IOR(BAYCOM_IOCTL_TYPE, 9, &bslash;&n;&t;&t;&t;&t;&t;struct baycom_params)
DECL|macro|BAYCOMCTL_CALIBRATE
mdefine_line|#define BAYCOMCTL_CALIBRATE        _IO(BAYCOM_IOCTL_TYPE, 10)
macro_line|#ifdef BAYCOM_DEBUG
multiline_comment|/*&n; * these are mainly for debugging purposes&n; */
DECL|macro|BAYCOMCTL_GETSAMPLES
mdefine_line|#define BAYCOMCTL_GETSAMPLES       _IOR(BAYCOM_IOCTL_TYPE, 16, unsigned char)
DECL|macro|BAYCOMCTL_GETBITS
mdefine_line|#define BAYCOMCTL_GETBITS          _IOR(BAYCOM_IOCTL_TYPE, 17, unsigned char)
DECL|macro|BAYCOMCTL_DEBUG1
mdefine_line|#define BAYCOMCTL_DEBUG1           _IOR(BAYCOM_IOCTL_TYPE, 18, unsigned long)
DECL|macro|BAYCOMCTL_DEBUG2
mdefine_line|#define BAYCOMCTL_DEBUG2           _IOR(BAYCOM_IOCTL_TYPE, 19, unsigned long)
DECL|macro|BAYCOMCTL_DEBUG3
mdefine_line|#define BAYCOMCTL_DEBUG3           _IOR(BAYCOM_IOCTL_TYPE, 20, unsigned long)
macro_line|#endif /* BAYCOM_DEBUG */
multiline_comment|/* -------------------------------------------------------------------- */
macro_line|#endif /* _BAYCOM_H */
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
