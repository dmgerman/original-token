macro_line|#ifndef _I386_TERMIOS_H
DECL|macro|_I386_TERMIOS_H
mdefine_line|#define _I386_TERMIOS_H
multiline_comment|/* 0x54 is just a magic number to make these relatively unique (&squot;T&squot;) */
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;0x5401
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;0x5402
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;0x5403
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;0x5404
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;0x5405
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;0x5406
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;0x5407
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;0x5408
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;0x5409
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;0x540A
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;0x540B
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x540C
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x540D
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x540E
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;0x540F
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;0x5410
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ&t;0x5411
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x5412
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;0x5413
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;0x5414
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;0x5415
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;0x5416
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;0x5417
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;0x5418
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;0x5419
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;0x541A
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;0x541B
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x541C
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;0x541D
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x541E
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x541F
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;0x5420
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;0x5421
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;0x5422
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;0x5423
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;0x5424
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x5425&t;/* Needed for POSIX tcsendbreak() */
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x5426  /* For debugging only */
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;0x5450  /* these numbers need to be adjusted. */
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;0x5451
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;0x5452
DECL|macro|TIOCSERCONFIG
mdefine_line|#define TIOCSERCONFIG&t;0x5453
DECL|macro|TIOCSERGWILD
mdefine_line|#define TIOCSERGWILD&t;0x5454
DECL|macro|TIOCSERSWILD
mdefine_line|#define TIOCSERSWILD&t;0x5455
DECL|macro|TIOCGLCKTRMIOS
mdefine_line|#define TIOCGLCKTRMIOS&t;0x5456
DECL|macro|TIOCSLCKTRMIOS
mdefine_line|#define TIOCSLCKTRMIOS&t;0x5457
DECL|macro|TIOCSERGSTRUCT
mdefine_line|#define TIOCSERGSTRUCT&t;0x5458 /* For debugging only */
DECL|macro|TIOCSERGETLSR
mdefine_line|#define TIOCSERGETLSR   0x5459 /* Get line status register */
DECL|macro|TIOCSERGETMULTI
mdefine_line|#define TIOCSERGETMULTI 0x545A /* Get multiport config  */
DECL|macro|TIOCSERSETMULTI
mdefine_line|#define TIOCSERSETMULTI 0x545B /* Set multiport config */
multiline_comment|/* Used for packet mode */
DECL|macro|TIOCPKT_DATA
mdefine_line|#define TIOCPKT_DATA&t;&t; 0
DECL|macro|TIOCPKT_FLUSHREAD
mdefine_line|#define TIOCPKT_FLUSHREAD&t; 1
DECL|macro|TIOCPKT_FLUSHWRITE
mdefine_line|#define TIOCPKT_FLUSHWRITE&t; 2
DECL|macro|TIOCPKT_STOP
mdefine_line|#define TIOCPKT_STOP&t;&t; 4
DECL|macro|TIOCPKT_START
mdefine_line|#define TIOCPKT_START&t;&t; 8
DECL|macro|TIOCPKT_NOSTOP
mdefine_line|#define TIOCPKT_NOSTOP&t;&t;16
DECL|macro|TIOCPKT_DOSTOP
mdefine_line|#define TIOCPKT_DOSTOP&t;&t;32
DECL|struct|winsize
r_struct
id|winsize
(brace
DECL|member|ws_row
r_int
r_int
id|ws_row
suffix:semicolon
DECL|member|ws_col
r_int
r_int
id|ws_col
suffix:semicolon
DECL|member|ws_xpixel
r_int
r_int
id|ws_xpixel
suffix:semicolon
DECL|member|ws_ypixel
r_int
r_int
id|ws_ypixel
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCC
mdefine_line|#define NCC 8
DECL|struct|termio
r_struct
id|termio
(brace
DECL|member|c_iflag
r_int
r_int
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
r_int
r_int
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
r_int
r_int
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
r_int
r_int
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
DECL|member|c_line
r_int
r_char
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
r_int
r_char
id|c_cc
(braket
id|NCC
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
DECL|macro|NCCS
mdefine_line|#define NCCS 19
DECL|struct|termios
r_struct
id|termios
(brace
DECL|member|c_iflag
id|tcflag_t
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
DECL|member|c_oflag
id|tcflag_t
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
DECL|member|c_cflag
id|tcflag_t
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
DECL|member|c_lflag
id|tcflag_t
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
DECL|member|c_line
id|cc_t
id|c_line
suffix:semicolon
multiline_comment|/* line discipline */
DECL|member|c_cc
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
)brace
suffix:semicolon
multiline_comment|/* c_cc characters */
DECL|macro|VINTR
mdefine_line|#define VINTR 0
DECL|macro|VQUIT
mdefine_line|#define VQUIT 1
DECL|macro|VERASE
mdefine_line|#define VERASE 2
DECL|macro|VKILL
mdefine_line|#define VKILL 3
DECL|macro|VEOF
mdefine_line|#define VEOF 4
DECL|macro|VTIME
mdefine_line|#define VTIME 5
DECL|macro|VMIN
mdefine_line|#define VMIN 6
DECL|macro|VSWTC
mdefine_line|#define VSWTC 7
DECL|macro|VSTART
mdefine_line|#define VSTART 8
DECL|macro|VSTOP
mdefine_line|#define VSTOP 9
DECL|macro|VSUSP
mdefine_line|#define VSUSP 10
DECL|macro|VEOL
mdefine_line|#define VEOL 11
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT 12
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD 13
DECL|macro|VWERASE
mdefine_line|#define VWERASE 14
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT 15
DECL|macro|VEOL2
mdefine_line|#define VEOL2 16
macro_line|#ifdef __KERNEL__
multiline_comment|/*&t;intr=^C&t;&t;quit=^|&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;vtime=&bslash;0&t;vmin=&bslash;1&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;eol=&bslash;0&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;eol2=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;1&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;0&quot;
macro_line|#endif
multiline_comment|/* c_iflag bits */
DECL|macro|IGNBRK
mdefine_line|#define IGNBRK&t;0000001
DECL|macro|BRKINT
mdefine_line|#define BRKINT&t;0000002
DECL|macro|IGNPAR
mdefine_line|#define IGNPAR&t;0000004
DECL|macro|PARMRK
mdefine_line|#define PARMRK&t;0000010
DECL|macro|INPCK
mdefine_line|#define INPCK&t;0000020
DECL|macro|ISTRIP
mdefine_line|#define ISTRIP&t;0000040
DECL|macro|INLCR
mdefine_line|#define INLCR&t;0000100
DECL|macro|IGNCR
mdefine_line|#define IGNCR&t;0000200
DECL|macro|ICRNL
mdefine_line|#define ICRNL&t;0000400
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0001000
DECL|macro|IXON
mdefine_line|#define IXON&t;0002000
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0004000
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0010000
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0020000
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0000001
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0000002
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0000004
DECL|macro|OCRNL
mdefine_line|#define OCRNL&t;0000010
DECL|macro|ONOCR
mdefine_line|#define ONOCR&t;0000020
DECL|macro|ONLRET
mdefine_line|#define ONLRET&t;0000040
DECL|macro|OFILL
mdefine_line|#define OFILL&t;0000100
DECL|macro|OFDEL
mdefine_line|#define OFDEL&t;0000200
DECL|macro|NLDLY
mdefine_line|#define NLDLY&t;0000400
DECL|macro|NL0
mdefine_line|#define   NL0&t;0000000
DECL|macro|NL1
mdefine_line|#define   NL1&t;0000400
DECL|macro|CRDLY
mdefine_line|#define CRDLY&t;0003000
DECL|macro|CR0
mdefine_line|#define   CR0&t;0000000
DECL|macro|CR1
mdefine_line|#define   CR1&t;0001000
DECL|macro|CR2
mdefine_line|#define   CR2&t;0002000
DECL|macro|CR3
mdefine_line|#define   CR3&t;0003000
DECL|macro|TABDLY
mdefine_line|#define TABDLY&t;0014000
DECL|macro|TAB0
mdefine_line|#define   TAB0&t;0000000
DECL|macro|TAB1
mdefine_line|#define   TAB1&t;0004000
DECL|macro|TAB2
mdefine_line|#define   TAB2&t;0010000
DECL|macro|TAB3
mdefine_line|#define   TAB3&t;0014000
DECL|macro|XTABS
mdefine_line|#define   XTABS&t;0014000
DECL|macro|BSDLY
mdefine_line|#define BSDLY&t;0020000
DECL|macro|BS0
mdefine_line|#define   BS0&t;0000000
DECL|macro|BS1
mdefine_line|#define   BS1&t;0020000
DECL|macro|VTDLY
mdefine_line|#define VTDLY&t;0040000
DECL|macro|VT0
mdefine_line|#define   VT0&t;0000000
DECL|macro|VT1
mdefine_line|#define   VT1&t;0040000
DECL|macro|FFDLY
mdefine_line|#define FFDLY&t;0100000
DECL|macro|FF0
mdefine_line|#define   FF0&t;0000000
DECL|macro|FF1
mdefine_line|#define   FF1&t;0100000
multiline_comment|/* c_cflag bit meaning */
DECL|macro|CBAUD
mdefine_line|#define CBAUD&t;0010017
DECL|macro|B0
mdefine_line|#define  B0&t;0000000&t;&t;/* hang up */
DECL|macro|B50
mdefine_line|#define  B50&t;0000001
DECL|macro|B75
mdefine_line|#define  B75&t;0000002
DECL|macro|B110
mdefine_line|#define  B110&t;0000003
DECL|macro|B134
mdefine_line|#define  B134&t;0000004
DECL|macro|B150
mdefine_line|#define  B150&t;0000005
DECL|macro|B200
mdefine_line|#define  B200&t;0000006
DECL|macro|B300
mdefine_line|#define  B300&t;0000007
DECL|macro|B600
mdefine_line|#define  B600&t;0000010
DECL|macro|B1200
mdefine_line|#define  B1200&t;0000011
DECL|macro|B1800
mdefine_line|#define  B1800&t;0000012
DECL|macro|B2400
mdefine_line|#define  B2400&t;0000013
DECL|macro|B4800
mdefine_line|#define  B4800&t;0000014
DECL|macro|B9600
mdefine_line|#define  B9600&t;0000015
DECL|macro|B19200
mdefine_line|#define  B19200&t;0000016
DECL|macro|B38400
mdefine_line|#define  B38400&t;0000017
DECL|macro|EXTA
mdefine_line|#define EXTA B19200
DECL|macro|EXTB
mdefine_line|#define EXTB B38400
DECL|macro|CSIZE
mdefine_line|#define CSIZE&t;0000060
DECL|macro|CS5
mdefine_line|#define   CS5&t;0000000
DECL|macro|CS6
mdefine_line|#define   CS6&t;0000020
DECL|macro|CS7
mdefine_line|#define   CS7&t;0000040
DECL|macro|CS8
mdefine_line|#define   CS8&t;0000060
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;0000100
DECL|macro|CREAD
mdefine_line|#define CREAD&t;0000200
DECL|macro|PARENB
mdefine_line|#define PARENB&t;0000400
DECL|macro|PARODD
mdefine_line|#define PARODD&t;0001000
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;0002000
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;0004000
DECL|macro|CBAUDEX
mdefine_line|#define CBAUDEX 0010000
DECL|macro|B57600
mdefine_line|#define  B57600  0010001
DECL|macro|B115200
mdefine_line|#define  B115200 0010002
DECL|macro|B230400
mdefine_line|#define  B230400 0010003
DECL|macro|CIBAUD
mdefine_line|#define CIBAUD&t;  002003600000&t;/* input baud rate (not used) */
DECL|macro|CRTSCTS
mdefine_line|#define CRTSCTS&t;  020000000000&t;&t;/* flow control */
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0000001
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0000002
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0000004
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0000010
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0000020
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0000040
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0000100
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0000200
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0000400
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0001000
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0002000
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0004000
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0010000
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0040000
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0100000
multiline_comment|/* modem lines */
DECL|macro|TIOCM_LE
mdefine_line|#define TIOCM_LE&t;0x001
DECL|macro|TIOCM_DTR
mdefine_line|#define TIOCM_DTR&t;0x002
DECL|macro|TIOCM_RTS
mdefine_line|#define TIOCM_RTS&t;0x004
DECL|macro|TIOCM_ST
mdefine_line|#define TIOCM_ST&t;0x008
DECL|macro|TIOCM_SR
mdefine_line|#define TIOCM_SR&t;0x010
DECL|macro|TIOCM_CTS
mdefine_line|#define TIOCM_CTS&t;0x020
DECL|macro|TIOCM_CAR
mdefine_line|#define TIOCM_CAR&t;0x040
DECL|macro|TIOCM_RNG
mdefine_line|#define TIOCM_RNG&t;0x080
DECL|macro|TIOCM_DSR
mdefine_line|#define TIOCM_DSR&t;0x100
DECL|macro|TIOCM_CD
mdefine_line|#define TIOCM_CD&t;TIOCM_CAR
DECL|macro|TIOCM_RI
mdefine_line|#define TIOCM_RI&t;TIOCM_RNG
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
multiline_comment|/* tcflow() and TCXONC use these */
DECL|macro|TCOOFF
mdefine_line|#define&t;TCOOFF&t;&t;0
DECL|macro|TCOON
mdefine_line|#define&t;TCOON&t;&t;1
DECL|macro|TCIOFF
mdefine_line|#define&t;TCIOFF&t;&t;2
DECL|macro|TCION
mdefine_line|#define&t;TCION&t;&t;3
multiline_comment|/* tcflush() and TCFLSH use these */
DECL|macro|TCIFLUSH
mdefine_line|#define&t;TCIFLUSH&t;0
DECL|macro|TCOFLUSH
mdefine_line|#define&t;TCOFLUSH&t;1
DECL|macro|TCIOFLUSH
mdefine_line|#define&t;TCIOFLUSH&t;2
multiline_comment|/* tcsetattr uses these */
DECL|macro|TCSANOW
mdefine_line|#define&t;TCSANOW&t;&t;0
DECL|macro|TCSADRAIN
mdefine_line|#define&t;TCSADRAIN&t;1
DECL|macro|TCSAFLUSH
mdefine_line|#define&t;TCSAFLUSH&t;2
multiline_comment|/* line disciplines */
DECL|macro|N_TTY
mdefine_line|#define N_TTY&t;&t;0
DECL|macro|N_SLIP
mdefine_line|#define N_SLIP&t;&t;1
DECL|macro|N_MOUSE
mdefine_line|#define N_MOUSE&t;&t;2
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;&t;3
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate a &quot;termio&quot; structure into a &quot;termios&quot;. Ugh.&n; */
DECL|function|trans_from_termio
r_extern
r_inline
r_void
id|trans_from_termio
c_func
(paren
r_struct
id|termio
op_star
id|termio
comma
r_struct
id|termios
op_star
id|termios
)paren
(brace
DECL|macro|SET_LOW_BITS
mdefine_line|#define SET_LOW_BITS(x,y)&t;((x) = (0xffff0000 &amp; (x)) | (y))
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_iflag
comma
id|termio-&gt;c_iflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_oflag
comma
id|termio-&gt;c_oflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_cflag
comma
id|termio-&gt;c_cflag
)paren
suffix:semicolon
id|SET_LOW_BITS
c_func
(paren
id|termios-&gt;c_lflag
comma
id|termio-&gt;c_lflag
)paren
suffix:semicolon
DECL|macro|SET_LOW_BITS
macro_line|#undef SET_LOW_BITS
id|memcpy
c_func
(paren
id|termios-&gt;c_cc
comma
id|termio-&gt;c_cc
comma
id|NCC
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Translate a &quot;termios&quot; structure into a &quot;termio&quot;. Ugh.&n; */
DECL|function|trans_to_termio
r_extern
r_inline
r_void
id|trans_to_termio
c_func
(paren
r_struct
id|termios
op_star
id|termios
comma
r_struct
id|termio
op_star
id|termio
)paren
(brace
id|termio-&gt;c_iflag
op_assign
id|termios-&gt;c_iflag
suffix:semicolon
id|termio-&gt;c_oflag
op_assign
id|termios-&gt;c_oflag
suffix:semicolon
id|termio-&gt;c_cflag
op_assign
id|termios-&gt;c_cflag
suffix:semicolon
id|termio-&gt;c_lflag
op_assign
id|termios-&gt;c_lflag
suffix:semicolon
id|termio-&gt;c_line
op_assign
id|termios-&gt;c_line
suffix:semicolon
id|memcpy
c_func
(paren
id|termio-&gt;c_cc
comma
id|termios-&gt;c_cc
comma
id|NCC
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _I386_TERMIOS_H */
eof