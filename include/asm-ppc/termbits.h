macro_line|#ifndef _PPC_TERMBITS_H
DECL|macro|_PPC_TERMBITS_H
mdefine_line|#define _PPC_TERMBITS_H
macro_line|#include &lt;linux/posix_types.h&gt;
DECL|typedef|cc_t
r_typedef
r_int
r_char
id|cc_t
suffix:semicolon
DECL|typedef|speed_t
r_typedef
r_int
r_int
id|speed_t
suffix:semicolon
DECL|typedef|tcflag_t
r_typedef
r_int
r_int
id|tcflag_t
suffix:semicolon
macro_line|#if 0 /* This is how it&squot;s done on Alpha - maybe later. */
multiline_comment|/*&n; * termios type and macro definitions.  Be careful about adding stuff&n; * to this file since it&squot;s used in GNU libc and there are strict rules&n; * concerning namespace pollution.&n; */
mdefine_line|#define NCCS 19
r_struct
id|termios
(brace
id|tcflag_t
id|c_iflag
suffix:semicolon
multiline_comment|/* input mode flags */
id|tcflag_t
id|c_oflag
suffix:semicolon
multiline_comment|/* output mode flags */
id|tcflag_t
id|c_cflag
suffix:semicolon
multiline_comment|/* control mode flags */
id|tcflag_t
id|c_lflag
suffix:semicolon
multiline_comment|/* local mode flags */
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
multiline_comment|/* control characters */
id|cc_t
id|c_line
suffix:semicolon
multiline_comment|/* line discipline (== c_cc[19]) */
id|speed_t
id|c_ispeed
suffix:semicolon
multiline_comment|/* input speed */
id|speed_t
id|c_ospeed
suffix:semicolon
multiline_comment|/* output speed */
)brace
suffix:semicolon
multiline_comment|/* c_cc characters */
mdefine_line|#define VEOF 0
mdefine_line|#define VEOL 1
mdefine_line|#define VEOL2 2
mdefine_line|#define VERASE 3
mdefine_line|#define VWERASE 4
mdefine_line|#define VKILL 5
mdefine_line|#define VREPRINT 6
mdefine_line|#define VSWTC 7
mdefine_line|#define VINTR 8
mdefine_line|#define VQUIT 9
mdefine_line|#define VSUSP 10
mdefine_line|#define VSTART 12
mdefine_line|#define VSTOP 13
mdefine_line|#define VLNEXT 14
mdefine_line|#define VDISCARD 15
mdefine_line|#define VMIN 16
mdefine_line|#define VTIME 17
multiline_comment|/* c_iflag bits */
mdefine_line|#define IGNBRK&t;0000001
mdefine_line|#define BRKINT&t;0000002
mdefine_line|#define IGNPAR&t;0000004
mdefine_line|#define PARMRK&t;0000010
mdefine_line|#define INPCK&t;0000020
mdefine_line|#define ISTRIP&t;0000040
mdefine_line|#define INLCR&t;0000100
mdefine_line|#define IGNCR&t;0000200
mdefine_line|#define ICRNL&t;0000400
mdefine_line|#define IXON&t;0001000
mdefine_line|#define IXOFF&t;0002000
macro_line|#if !defined(KERNEL) || defined(__USE_BSD)
multiline_comment|/* POSIX.1 doesn&squot;t want these... */
macro_line|# define IXANY&t;&t;0004000
macro_line|# define IUCLC&t;&t;0010000
macro_line|# define IMAXBEL&t;0020000
macro_line|#endif
multiline_comment|/* c_oflag bits */
mdefine_line|#define OPOST&t;0000001
mdefine_line|#define ONLCR&t;0000002
mdefine_line|#define OLCUC&t;0000004
mdefine_line|#define OCRNL&t;0000010
mdefine_line|#define ONOCR&t;0000020
mdefine_line|#define ONLRET&t;0000040
mdefine_line|#define OFILL&t;00000100
mdefine_line|#define OFDEL&t;00000200
mdefine_line|#define NLDLY&t;00001400
mdefine_line|#define   NL0&t;00000000
mdefine_line|#define   NL1&t;00000400
mdefine_line|#define   NL2&t;00001000
mdefine_line|#define   NL3&t;00001400
mdefine_line|#define TABDLY&t;00006000
mdefine_line|#define   TAB0&t;00000000
mdefine_line|#define   TAB1&t;00002000
mdefine_line|#define   TAB2&t;00004000
mdefine_line|#define   TAB3&t;00006000
mdefine_line|#define CRDLY&t;00030000
mdefine_line|#define   CR0&t;00000000
mdefine_line|#define   CR1&t;00010000
mdefine_line|#define   CR2&t;00020000
mdefine_line|#define   CR3&t;00030000
mdefine_line|#define FFDLY&t;00040000
mdefine_line|#define   FF0&t;00000000
mdefine_line|#define   FF1&t;00040000
mdefine_line|#define BSDLY&t;00100000
mdefine_line|#define   BS0&t;00000000
mdefine_line|#define   BS1&t;00100000
mdefine_line|#define VTDLY&t;00200000
mdefine_line|#define   VT0&t;00000000
mdefine_line|#define   VT1&t;00200000
mdefine_line|#define XTABS&t;01000000 /* Hmm.. Linux/i386 considers this part of TABDLY.. */
multiline_comment|/* c_cflag bit meaning */
mdefine_line|#define CBAUD&t;0000017
mdefine_line|#define  B0&t;0000000&t;&t;/* hang up */
mdefine_line|#define  B50&t;0000001
mdefine_line|#define  B75&t;0000002
mdefine_line|#define  B110&t;0000003
mdefine_line|#define  B134&t;0000004
mdefine_line|#define  B150&t;0000005
mdefine_line|#define  B200&t;0000006
mdefine_line|#define  B300&t;0000007
mdefine_line|#define  B600&t;0000010
mdefine_line|#define  B1200&t;0000011
mdefine_line|#define  B1800&t;0000012
mdefine_line|#define  B2400&t;0000013
mdefine_line|#define  B4800&t;0000014
mdefine_line|#define  B9600&t;0000015
mdefine_line|#define  B19200&t;0000016
mdefine_line|#define  B38400&t;0000017
mdefine_line|#define EXTA B19200
mdefine_line|#define EXTB B38400
mdefine_line|#define CBAUDEX 0000020
mdefine_line|#define  B57600   00020
mdefine_line|#define  B115200  00021
mdefine_line|#define  B230400  00022
mdefine_line|#define CSIZE&t;00001400
mdefine_line|#define   CS5&t;00000000
mdefine_line|#define   CS6&t;00000400
mdefine_line|#define   CS7&t;00001000
mdefine_line|#define   CS8&t;00001400
mdefine_line|#define CSTOPB&t;00002000
mdefine_line|#define CREAD&t;00004000
mdefine_line|#define PARENB&t;00010000
mdefine_line|#define PARODD&t;00020000
mdefine_line|#define HUPCL&t;00040000
mdefine_line|#define CLOCAL&t;00100000
mdefine_line|#define CRTSCTS&t;  020000000000&t;&t;/* flow control */
multiline_comment|/* c_lflag bits */
mdefine_line|#define ISIG&t;0x00000080
mdefine_line|#define ICANON&t;0x00000100
mdefine_line|#define XCASE&t;0x00004000
mdefine_line|#define ECHO&t;0x00000008
mdefine_line|#define ECHOE&t;0x00000002
mdefine_line|#define ECHOK&t;0x00000004
mdefine_line|#define ECHONL&t;0x00000010
mdefine_line|#define NOFLSH&t;0x80000000
mdefine_line|#define TOSTOP&t;0x00400000
mdefine_line|#define ECHOCTL&t;0x00000040
mdefine_line|#define ECHOPRT&t;0x00000020
mdefine_line|#define ECHOKE&t;0x00000001
mdefine_line|#define FLUSHO&t;0x00800000
mdefine_line|#define PENDIN&t;0x20000000
mdefine_line|#define IEXTEN&t;0x00000400
multiline_comment|/* Values for the ACTION argument to `tcflow&squot;.  */
mdefine_line|#define&t;TCOOFF&t;&t;0
mdefine_line|#define&t;TCOON&t;&t;1
mdefine_line|#define&t;TCIOFF&t;&t;2
mdefine_line|#define&t;TCION&t;&t;3
multiline_comment|/* Values for the QUEUE_SELECTOR argument to `tcflush&squot;.  */
mdefine_line|#define&t;TCIFLUSH&t;0
mdefine_line|#define&t;TCOFLUSH&t;1
mdefine_line|#define&t;TCIOFLUSH&t;2
multiline_comment|/* Values for the OPTIONAL_ACTIONS argument to `tcsetattr&squot;.  */
mdefine_line|#define&t;TCSANOW&t;&t;0
mdefine_line|#define&t;TCSADRAIN&t;1
mdefine_line|#define&t;TCSAFLUSH&t;2
macro_line|#endif
macro_line|#endif /* _PPC_TERMBITS_H */
eof
