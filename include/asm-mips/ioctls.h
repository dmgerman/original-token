macro_line|#ifndef __ASM_MIPS_IOCTLS_H
DECL|macro|__ASM_MIPS_IOCTLS_H
mdefine_line|#define __ASM_MIPS_IOCTLS_H
macro_line|#include &lt;asm/ioctl.h&gt;
DECL|macro|TCGETA
mdefine_line|#define TCGETA&t;&t;0x5401
DECL|macro|TCSETA
mdefine_line|#define TCSETA&t;&t;0x5402
DECL|macro|TCSETAW
mdefine_line|#define TCSETAW&t;&t;0x5403
DECL|macro|TCSETAF
mdefine_line|#define TCSETAF&t;&t;0x5404
DECL|macro|TCSBRK
mdefine_line|#define TCSBRK&t;&t;0x5405
DECL|macro|TCXONC
mdefine_line|#define TCXONC&t;&t;0x5406
DECL|macro|TCFLSH
mdefine_line|#define TCFLSH&t;&t;0x5407
DECL|macro|TCGETS
mdefine_line|#define TCGETS&t;&t;0x540d
DECL|macro|TCSETS
mdefine_line|#define TCSETS&t;&t;0x540e
DECL|macro|TCSETSW
mdefine_line|#define TCSETSW&t;&t;0x540f
DECL|macro|TCSETSF
mdefine_line|#define TCSETSF&t;&t;0x5410
DECL|macro|TIOCEXCL
mdefine_line|#define TIOCEXCL&t;0x740d&t;&t;/* set exclusive use of tty */
DECL|macro|TIOCNXCL
mdefine_line|#define TIOCNXCL&t;0x740e&t;&t;/* reset exclusive use of tty */
DECL|macro|TIOCOUTQ
mdefine_line|#define TIOCOUTQ&t;0x7472&t;&t;/* output queue size */
DECL|macro|TIOCSTI
mdefine_line|#define TIOCSTI&t;&t;0x5472&t;&t;/* simulate terminal input */
DECL|macro|TIOCMGET
mdefine_line|#define TIOCMGET&t;0x741d&t;&t;/* get all modem bits */
DECL|macro|TIOCMBIS
mdefine_line|#define TIOCMBIS&t;0x741b&t;&t;/* bis modem bits */
DECL|macro|TIOCMBIC
mdefine_line|#define TIOCMBIC&t;0x741c&t;&t;/* bic modem bits */
DECL|macro|TIOCMSET
mdefine_line|#define TIOCMSET&t;0x741a&t;&t;/* set all modem bits */
DECL|macro|TIOCPKT
mdefine_line|#define TIOCPKT&t;&t;0x5470&t;&t;/* pty: set/clear packet mode */
DECL|macro|TIOCPKT_DATA
mdefine_line|#define&t;&t;TIOCPKT_DATA&t;&t;0x00&t;/* data packet */
DECL|macro|TIOCPKT_FLUSHREAD
mdefine_line|#define&t;&t;TIOCPKT_FLUSHREAD&t;0x01&t;/* flush packet */
DECL|macro|TIOCPKT_FLUSHWRITE
mdefine_line|#define&t;&t;TIOCPKT_FLUSHWRITE&t;0x02&t;/* flush packet */
DECL|macro|TIOCPKT_STOP
mdefine_line|#define&t;&t;TIOCPKT_STOP&t;&t;0x04&t;/* stop output */
DECL|macro|TIOCPKT_START
mdefine_line|#define&t;&t;TIOCPKT_START&t;&t;0x08&t;/* start output */
DECL|macro|TIOCPKT_NOSTOP
mdefine_line|#define&t;&t;TIOCPKT_NOSTOP&t;&t;0x10&t;/* no more ^S, ^Q */
DECL|macro|TIOCPKT_DOSTOP
mdefine_line|#define&t;&t;TIOCPKT_DOSTOP&t;&t;0x20&t;/* now do ^S ^Q */
macro_line|#if 0
mdefine_line|#define&t;&t;TIOCPKT_IOCTL&t;&t;0x40&t;/* state change of pty driver */
macro_line|#endif
DECL|macro|TIOCSWINSZ
mdefine_line|#define TIOCSWINSZ&t;_IOW(&squot;t&squot;, 103, struct winsize)&t;/* set window size */
DECL|macro|TIOCGWINSZ
mdefine_line|#define TIOCGWINSZ&t;_IOR(&squot;t&squot;, 104, struct winsize)&t;/* get window size */
DECL|macro|TIOCNOTTY
mdefine_line|#define TIOCNOTTY&t;0x5471&t;&t;/* void tty association */
DECL|macro|TIOCSETD
mdefine_line|#define TIOCSETD&t;0x7401
DECL|macro|TIOCGETD
mdefine_line|#define TIOCGETD&t;0x7400
DECL|macro|FIOCLEX
mdefine_line|#define FIOCLEX&t;&t;0x6601
DECL|macro|FIONCLEX
mdefine_line|#define FIONCLEX&t;0x6602&t;&t;/* these numbers need to be adjusted. */
DECL|macro|FIOASYNC
mdefine_line|#define FIOASYNC&t;0x667d
DECL|macro|FIONBIO
mdefine_line|#define FIONBIO&t;&t;0x667e
multiline_comment|/* 116-117 compat */
DECL|macro|TIOCSPGRP
mdefine_line|#define TIOCSPGRP&t;_IOW(&squot;t&squot;, 118, int)&t;/* set pgrp of tty */
DECL|macro|TIOCGPGRP
mdefine_line|#define TIOCGPGRP&t;_IOR(&squot;t&squot;, 119, int)&t;/* get pgrp of tty */
DECL|macro|TIOCCONS
mdefine_line|#define TIOCCONS&t;_IOW(&squot;t&squot;, 120, int)&t;/* become virtual console */
DECL|macro|FIONREAD
mdefine_line|#define FIONREAD&t;0x467f
DECL|macro|TIOCINQ
mdefine_line|#define TIOCINQ&t;&t;FIONREAD
macro_line|#if 0
mdefine_line|#define&t;TIOCSETA&t;_IOW(&squot;t&squot;, 20, struct termios) /* set termios struct */
mdefine_line|#define&t;TIOCSETAW&t;_IOW(&squot;t&squot;, 21, struct termios) /* drain output, set */
mdefine_line|#define&t;TIOCSETAF&t;_IOW(&squot;t&squot;, 22, struct termios) /* drn out, fls in, set */
mdefine_line|#define&t;TIOCGETD&t;_IOR(&squot;t&squot;, 26, int)&t;/* get line discipline */
mdefine_line|#define&t;TIOCSETD&t;_IOW(&squot;t&squot;, 27, int)&t;/* set line discipline */
multiline_comment|/* 127-124 compat */
macro_line|#endif
multiline_comment|/* I hope the range from 0x5480 on is free ... */
DECL|macro|TIOCSCTTY
mdefine_line|#define TIOCSCTTY&t;0x5480&t;&t;/* become controlling tty */
DECL|macro|TIOCGSOFTCAR
mdefine_line|#define TIOCGSOFTCAR&t;0x5481
DECL|macro|TIOCSSOFTCAR
mdefine_line|#define TIOCSSOFTCAR&t;0x5482
DECL|macro|TIOCLINUX
mdefine_line|#define TIOCLINUX&t;0x5483
DECL|macro|TIOCGSERIAL
mdefine_line|#define TIOCGSERIAL&t;0x5484
DECL|macro|TIOCSSERIAL
mdefine_line|#define TIOCSSERIAL&t;0x5485
DECL|macro|TCSBRKP
mdefine_line|#define TCSBRKP&t;&t;0x5486&t;/* Needed for POSIX tcsendbreak() */
DECL|macro|TIOCTTYGSTRUCT
mdefine_line|#define TIOCTTYGSTRUCT&t;0x5487  /* For debugging only */
DECL|macro|TIOCSERCONFIG
mdefine_line|#define TIOCSERCONFIG&t;0x5488
DECL|macro|TIOCSERGWILD
mdefine_line|#define TIOCSERGWILD&t;0x5489
DECL|macro|TIOCSERSWILD
mdefine_line|#define TIOCSERSWILD&t;0x548a
DECL|macro|TIOCGLCKTRMIOS
mdefine_line|#define TIOCGLCKTRMIOS&t;0x548b
DECL|macro|TIOCSLCKTRMIOS
mdefine_line|#define TIOCSLCKTRMIOS&t;0x548c
DECL|macro|TIOCSERGSTRUCT
mdefine_line|#define TIOCSERGSTRUCT&t;0x548d /* For debugging only */
DECL|macro|TIOCSERGETLSR
mdefine_line|#define TIOCSERGETLSR   0x548e /* Get line status register */
DECL|macro|TIOCSERGETMULTI
mdefine_line|#define TIOCSERGETMULTI 0x548f /* Get multiport config  */
DECL|macro|TIOCSERSETMULTI
mdefine_line|#define TIOCSERSETMULTI 0x5490 /* Set multiport config */
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* c_cc characters */
DECL|macro|VINTR
mdefine_line|#define VINTR&t;&t; 0&t;&t;/* Interrupt character [ISIG].  */
DECL|macro|VQUIT
mdefine_line|#define VQUIT&t;&t; 1&t;&t;/* Quit character [ISIG].  */
DECL|macro|VERASE
mdefine_line|#define VERASE&t;&t; 2&t;&t;/* Erase character [ICANON].  */
DECL|macro|VKILL
mdefine_line|#define VKILL&t;&t; 3&t;&t;/* Kill-line character [ICANON].  */
DECL|macro|VEOF
mdefine_line|#define VEOF&t;&t; 4&t;&t;/* End-of-file character [ICANON].  */
DECL|macro|VMIN
mdefine_line|#define VMIN&t;&t;VEOF&t;&t;/* Minimum number of bytes read at once [!ICANON].  */
DECL|macro|VEOL
mdefine_line|#define VEOL&t;&t; 5&t;&t;/* End-of-line character [ICANON].  */
DECL|macro|VTIME
mdefine_line|#define VTIME&t;&t;VEOL&t;&t;/* Time-out value (tenths of a second) [!ICANON].  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|VEOL2
mdefine_line|#define VEOL2&t;&t; 6&t;&t;/* Second EOL character [ICANON].  */
multiline_comment|/* The next two are guesses ... */
DECL|macro|VSWTC
mdefine_line|#define VSWTC&t;&t; 7&t;&t;/* ??? */
macro_line|#endif
DECL|macro|VSWTCH
mdefine_line|#define VSWTCH&t;&t;VSWTC
DECL|macro|VSTART
mdefine_line|#define VSTART&t;&t; 8&t;&t;/* Start (X-ON) character [IXON, IXOFF].  */
DECL|macro|VSTOP
mdefine_line|#define VSTOP&t;&t; 9&t;&t;/* Stop (X-OFF) character [IXON, IXOFF].  */
DECL|macro|VSUSP
mdefine_line|#define VSUSP&t;&t;10&t;&t;/* Suspend character [ISIG].  */
macro_line|#if 0
multiline_comment|/*&n; * VDSUSP is not supported&n; */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
mdefine_line|#define VDSUSP&t;&t;11&t;&t;/* Delayed suspend character [ISIG].  */
macro_line|#endif
macro_line|#endif
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|VREPRINT
mdefine_line|#define VREPRINT&t;12&t;&t;/* Reprint-line character [ICANON].  */
macro_line|#endif
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|VDISCARD
mdefine_line|#define VDISCARD&t;13&t;&t;/* Discard character [IEXTEN].  */
DECL|macro|VWERASE
mdefine_line|#define VWERASE&t;&t;14&t;&t;/* Word-erase character [ICANON].  */
DECL|macro|VLNEXT
mdefine_line|#define VLNEXT&t;&t;15&t;&t;/* Literal-next character [IEXTEN].  */
macro_line|#endif
multiline_comment|/*&n; * 17 - 19 are reserved&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&t;intr=^C&t;&t;quit=^|&t;&t;erase=del&t;kill=^U&n; *&t;eof=^D&t;&t;eol=time=&bslash;0&t;eol2=&bslash;0&t;&t;swtc=&bslash;0&n; *&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;vdsusp=&n; *&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n; */
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;0&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&quot;
macro_line|#endif
multiline_comment|/* c_iflag bits */
DECL|macro|IGNBRK
mdefine_line|#define IGNBRK&t;0000001&t;&t;/* Ignore break condition.  */
DECL|macro|BRKINT
mdefine_line|#define BRKINT&t;0000002&t;&t;/* Signal interrupt on break.  */
DECL|macro|IGNPAR
mdefine_line|#define IGNPAR&t;0000004&t;&t;/* Ignore characters with parity errors.  */
DECL|macro|PARMRK
mdefine_line|#define PARMRK&t;0000010&t;&t;/* Mark parity and framing errors.  */
DECL|macro|INPCK
mdefine_line|#define INPCK&t;0000020&t;&t;/* Enable input parity check.  */
DECL|macro|ISTRIP
mdefine_line|#define ISTRIP&t;0000040&t;&t;/* Strip 8th bit off characters.  */
DECL|macro|INLCR
mdefine_line|#define INLCR&t;0000100&t;&t;/* Map NL to CR on input.  */
DECL|macro|IGNCR
mdefine_line|#define IGNCR&t;0000200&t;&t;/* Ignore CR.  */
DECL|macro|ICRNL
mdefine_line|#define ICRNL&t;0000400&t;&t;/* Map CR to NL on input.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|IUCLC
mdefine_line|#define IUCLC&t;0001000&t;&t;/* Map upper case to lower case on input.  */
macro_line|#endif
DECL|macro|IXON
mdefine_line|#define IXON&t;0002000&t;&t;/* Enable start/stop output control.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|IXANY
mdefine_line|#define IXANY&t;0004000&t;&t;/* Any character will restart after stop.  */
macro_line|#endif
DECL|macro|IXOFF
mdefine_line|#define IXOFF&t;0010000&t;&t;/* Enable start/stop input control.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|IMAXBEL
mdefine_line|#define IMAXBEL&t;0020000&t;&t;/* Ring bell when input queue is full.  */
macro_line|#endif
multiline_comment|/* c_oflag bits */
DECL|macro|OPOST
mdefine_line|#define OPOST&t;0000001&t;&t;/* Perform output processing.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|OLCUC
mdefine_line|#define OLCUC&t;0000002&t;&t;/* Map lower case to upper case on output.  */
DECL|macro|ONLCR
mdefine_line|#define ONLCR&t;0000004&t;&t;/* Map NL to CR-NL on output.  */
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
multiline_comment|/*&n;#define PAGEOUT ???&n;#define WRAP    ???&n; */
macro_line|#endif
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
mdefine_line|#define CSIZE&t;0000060&t;&t;/* Number of bits per byte (mask).  */
DECL|macro|CS5
mdefine_line|#define   CS5&t;0000000&t;&t;/* 5 bits per byte.  */
DECL|macro|CS6
mdefine_line|#define   CS6&t;0000020&t;&t;/* 6 bits per byte.  */
DECL|macro|CS7
mdefine_line|#define   CS7&t;0000040&t;&t;/* 7 bits per byte.  */
DECL|macro|CS8
mdefine_line|#define   CS8&t;0000060&t;&t;/* 8 bits per byte.  */
DECL|macro|CSTOPB
mdefine_line|#define CSTOPB&t;0000100&t;&t;/* Two stop bits instead of one.  */
DECL|macro|CREAD
mdefine_line|#define CREAD&t;0000200&t;&t;/* Enable receiver.  */
DECL|macro|PARENB
mdefine_line|#define PARENB&t;0000400&t;&t;/* Parity enable.  */
DECL|macro|PARODD
mdefine_line|#define PARODD&t;0001000&t;&t;/* Odd parity instead of even.  */
DECL|macro|HUPCL
mdefine_line|#define HUPCL&t;0002000&t;&t;/* Hang up on last close.  */
DECL|macro|CLOCAL
mdefine_line|#define CLOCAL&t;0004000&t;&t;/* Ignore modem status lines.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
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
macro_line|#endif
multiline_comment|/* c_lflag bits */
DECL|macro|ISIG
mdefine_line|#define ISIG&t;0000001&t;&t;/* Enable signals.  */
DECL|macro|ICANON
mdefine_line|#define ICANON&t;0000002&t;&t;/* Do erase and kill processing.  */
DECL|macro|XCASE
mdefine_line|#define XCASE&t;0000004
DECL|macro|ECHO
mdefine_line|#define ECHO&t;0000010&t;&t;/* Enable echo.  */
DECL|macro|ECHOE
mdefine_line|#define ECHOE&t;0000020&t;&t;/* Visual erase for ERASE.  */
DECL|macro|ECHOK
mdefine_line|#define ECHOK&t;0000040&t;&t;/* Echo NL after KILL.  */
DECL|macro|ECHONL
mdefine_line|#define ECHONL&t;0000100&t;&t;/* Echo NL even if ECHO is off.  */
DECL|macro|NOFLSH
mdefine_line|#define NOFLSH&t;0000200&t;&t;/* Disable flush after interrupt.  */
DECL|macro|IEXTEN
mdefine_line|#define IEXTEN&t;0000400&t;&t;/* Enable DISCARD and LNEXT.  */
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|ECHOCTL
mdefine_line|#define ECHOCTL&t;0001000&t;&t;/* Echo control characters as ^X.  */
DECL|macro|ECHOPRT
mdefine_line|#define ECHOPRT&t;0002000&t;&t;/* Hardcopy visual erase.  */
DECL|macro|ECHOKE
mdefine_line|#define ECHOKE&t;0004000&t;&t;/* Visual erase for KILL.  */
macro_line|#endif
DECL|macro|FLUSHO
mdefine_line|#define FLUSHO&t;0020000
macro_line|#if defined (__USE_BSD) || defined (__KERNEL__)
DECL|macro|PENDIN
mdefine_line|#define PENDIN&t;0040000&t;&t;/* Retype pending input (state).  */
macro_line|#endif
DECL|macro|TOSTOP
mdefine_line|#define TOSTOP&t;0100000&t;&t;/* Send SIGTTOU for background output.  */
DECL|macro|ITOSTOP
mdefine_line|#define ITOSTOP&t;TOSTOP
multiline_comment|/* modem lines */
DECL|macro|TIOCM_LE
mdefine_line|#define TIOCM_LE&t;0x001&t;&t;/* line enable */
DECL|macro|TIOCM_DTR
mdefine_line|#define TIOCM_DTR&t;0x002&t;&t;/* data terminal ready */
DECL|macro|TIOCM_RTS
mdefine_line|#define TIOCM_RTS&t;0x004&t;&t;/* request to send */
DECL|macro|TIOCM_ST
mdefine_line|#define TIOCM_ST&t;0x010&t;&t;/* secondary transmit */
DECL|macro|TIOCM_SR
mdefine_line|#define TIOCM_SR&t;0x020&t;&t;/* secondary receive */
DECL|macro|TIOCM_CTS
mdefine_line|#define TIOCM_CTS&t;0x040&t;&t;/* clear to send */
DECL|macro|TIOCM_CAR
mdefine_line|#define TIOCM_CAR&t;0x100&t;&t;/* carrier detect */
DECL|macro|TIOCM_CD
mdefine_line|#define TIOCM_CD&t;TIOCM_CAR
DECL|macro|TIOCM_RNG
mdefine_line|#define TIOCM_RNG&t;0x200&t;&t;/* ring */
DECL|macro|TIOCM_RI
mdefine_line|#define TIOCM_RI&t;TIOCM_RNG
DECL|macro|TIOCM_DSR
mdefine_line|#define TIOCM_DSR&t;0x400&t;&t;/* data set ready */
multiline_comment|/* ioctl (fd, TIOCSERGETLSR, &amp;result) where result may be as below */
DECL|macro|TIOCSER_TEMT
mdefine_line|#define TIOCSER_TEMT    0x01&t;/* Transmitter physically empty */
multiline_comment|/* tcflow() and TCXONC use these */
DECL|macro|TCOOFF
mdefine_line|#define&t;TCOOFF&t;&t;0&t;/* Suspend output.  */
DECL|macro|TCOON
mdefine_line|#define&t;TCOON&t;&t;1&t;/* Restart suspended output.  */
DECL|macro|TCIOFF
mdefine_line|#define&t;TCIOFF&t;&t;2&t;/* Send a STOP character.  */
DECL|macro|TCION
mdefine_line|#define&t;TCION&t;&t;3&t;/* Send a START character.  */
multiline_comment|/* tcflush() and TCFLSH use these */
DECL|macro|TCIFLUSH
mdefine_line|#define&t;TCIFLUSH&t;0&t;/* Discard data received but not yet read.  */
DECL|macro|TCOFLUSH
mdefine_line|#define&t;TCOFLUSH&t;1&t;/* Discard data written but not yet sent.  */
DECL|macro|TCIOFLUSH
mdefine_line|#define&t;TCIOFLUSH&t;2&t;/* Discard all pending data.  */
multiline_comment|/* tcsetattr uses these */
DECL|macro|TCSANOW
mdefine_line|#define&t;TCSANOW&t;&t;TCSETS&t;/* Change immediately.  */
DECL|macro|TCSADRAIN
mdefine_line|#define&t;TCSADRAIN&t;TCSETSW&t;/* Change when pending output is written.  */
DECL|macro|TCSAFLUSH
mdefine_line|#define&t;TCSAFLUSH&t;TCSETSF&t;/* Flush pending input before changing.  */
multiline_comment|/* line disciplines */
DECL|macro|N_TTY
mdefine_line|#define N_TTY&t;&t;0
DECL|macro|N_SLIP
mdefine_line|#define N_SLIP&t;&t;1
DECL|macro|N_MOUSE
mdefine_line|#define N_MOUSE&t;&t;2
DECL|macro|N_PPP
mdefine_line|#define N_PPP&t;&t;3
macro_line|#endif /* __ASM_MIPS_IOCTLS_H */
eof
