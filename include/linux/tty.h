macro_line|#ifndef _LINUX_TTY_H
DECL|macro|_LINUX_TTY_H
mdefine_line|#define _LINUX_TTY_H
multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; */
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NR_CONSOLES
mdefine_line|#define NR_CONSOLES&t;8
DECL|macro|NR_LDISCS
mdefine_line|#define NR_LDISCS&t;16
multiline_comment|/*&n; * These are set up by the setup-routine at boot-time:&n; */
DECL|struct|screen_info
r_struct
id|screen_info
(brace
DECL|member|orig_x
r_int
r_char
id|orig_x
suffix:semicolon
DECL|member|orig_y
r_int
r_char
id|orig_y
suffix:semicolon
DECL|member|unused1
r_int
r_char
id|unused1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|orig_video_page
r_int
r_int
id|orig_video_page
suffix:semicolon
DECL|member|orig_video_mode
r_int
r_char
id|orig_video_mode
suffix:semicolon
DECL|member|orig_video_cols
r_int
r_char
id|orig_video_cols
suffix:semicolon
DECL|member|orig_video_ega_ax
r_int
r_int
id|orig_video_ega_ax
suffix:semicolon
DECL|member|orig_video_ega_bx
r_int
r_int
id|orig_video_ega_bx
suffix:semicolon
DECL|member|orig_video_ega_cx
r_int
r_int
id|orig_video_ega_cx
suffix:semicolon
DECL|member|orig_video_lines
r_int
r_char
id|orig_video_lines
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|macro|ORIG_X
mdefine_line|#define ORIG_X&t;&t;&t;(screen_info.orig_x)
DECL|macro|ORIG_Y
mdefine_line|#define ORIG_Y&t;&t;&t;(screen_info.orig_y)
DECL|macro|ORIG_VIDEO_PAGE
mdefine_line|#define ORIG_VIDEO_PAGE&t;&t;(screen_info.orig_video_page)
DECL|macro|ORIG_VIDEO_MODE
mdefine_line|#define ORIG_VIDEO_MODE&t;&t;(screen_info.orig_video_mode)
DECL|macro|ORIG_VIDEO_COLS
mdefine_line|#define ORIG_VIDEO_COLS &t;(screen_info.orig_video_cols)
DECL|macro|ORIG_VIDEO_EGA_AX
mdefine_line|#define ORIG_VIDEO_EGA_AX&t;(screen_info.orig_video_ega_ax)
DECL|macro|ORIG_VIDEO_EGA_BX
mdefine_line|#define ORIG_VIDEO_EGA_BX&t;(screen_info.orig_video_ega_bx)
DECL|macro|ORIG_VIDEO_EGA_CX
mdefine_line|#define ORIG_VIDEO_EGA_CX&t;(screen_info.orig_video_ega_cx)
DECL|macro|ORIG_VIDEO_LINES
mdefine_line|#define ORIG_VIDEO_LINES&t;(screen_info.orig_video_lines)
DECL|macro|VIDEO_TYPE_MDA
mdefine_line|#define VIDEO_TYPE_MDA&t;&t;0x10&t;/* Monochrome Text Display&t;*/
DECL|macro|VIDEO_TYPE_CGA
mdefine_line|#define VIDEO_TYPE_CGA&t;&t;0x11&t;/* CGA Display &t;&t;&t;*/
DECL|macro|VIDEO_TYPE_EGAM
mdefine_line|#define VIDEO_TYPE_EGAM&t;&t;0x20&t;/* EGA/VGA in Monochrome Mode&t;*/
DECL|macro|VIDEO_TYPE_EGAC
mdefine_line|#define VIDEO_TYPE_EGAC&t;&t;0x21&t;/* EGA/VGA in Color Mode&t;*/
multiline_comment|/*&n; * This character is the same as _POSIX_VDISABLE: it cannot be used as&n; * a c_cc[] character, but indicates that a particular special character&n; * isn&squot;t in use (eg VINTR ahs no character etc)&n; */
DECL|macro|__DISABLED_CHAR
mdefine_line|#define __DISABLED_CHAR &squot;&bslash;0&squot;
multiline_comment|/*&n; * See comment for the tty_struct structure before changing&n; * TTY_BUF_SIZE.  Actually, there should be different sized tty_queue&n; * structures for different purposes.  1024 bytes for the transmit&n; * queue is way overkill.  TYT, 9/14/92&n; */
DECL|macro|TTY_BUF_SIZE
mdefine_line|#define TTY_BUF_SIZE 1024&t;/* Must be a power of 2 */
DECL|struct|tty_queue
r_struct
id|tty_queue
(brace
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|proc_list
r_struct
id|wait_queue
op_star
id|proc_list
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|TTY_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|serial_struct
r_struct
id|serial_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|close_delay
r_char
id|close_delay
suffix:semicolon
DECL|member|reserved_char
r_char
id|reserved_char
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * These are the supported serial types.&n; */
DECL|macro|PORT_UNKNOWN
mdefine_line|#define PORT_UNKNOWN&t;0
DECL|macro|PORT_8250
mdefine_line|#define PORT_8250&t;1
DECL|macro|PORT_16450
mdefine_line|#define PORT_16450&t;2
DECL|macro|PORT_16550
mdefine_line|#define PORT_16550&t;3
DECL|macro|PORT_16550A
mdefine_line|#define PORT_16550A&t;4
DECL|macro|PORT_MAX
mdefine_line|#define PORT_MAX&t;4
multiline_comment|/*&n; * Definitions for async_struct (and serial_struct) flags field&n; */
DECL|macro|ASYNC_HUP_NOTIFY
mdefine_line|#define ASYNC_HUP_NOTIFY 0x0001 /* Notify blocked open on hangups */
DECL|macro|ASYNC_FOURPORT
mdefine_line|#define ASYNC_FOURPORT  0x0002&t;/* Set OU1, OUT2 per AST Fourport settings */
DECL|macro|ASYNC_SAK
mdefine_line|#define ASYNC_SAK&t;0x0004&t;/* Secure Attention Key (Orange book) */
DECL|macro|ASYNC_SKIP_TEST
mdefine_line|#define ASYNC_SKIP_TEST 0x0008&t;/* Skip UART test on bootup */
DECL|macro|ASYNC_SPD_MASK
mdefine_line|#define ASYNC_SPD_MASK&t;0x0030
DECL|macro|ASYNC_SPD_HI
mdefine_line|#define ASYNC_SPD_HI&t;0x0010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|ASYNC_SPD_VHI
mdefine_line|#define ASYNC_SPD_VHI&t;0x0020  /* Use 115200 instead of 38400 bps */
DECL|macro|ASYNC_SPD_CUST
mdefine_line|#define ASYNC_SPD_CUST&t;0x0030  /* Use user-specified divisor */
DECL|macro|ASYNC_FLAGS
mdefine_line|#define ASYNC_FLAGS&t;0x0037&t;/* Possible legal async flags */
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|ASYNC_INITIALIZED
mdefine_line|#define ASYNC_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|ASYNC_CALLOUT_ACTIVE
mdefine_line|#define ASYNC_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|ASYNC_NORMAL_ACTIVE
mdefine_line|#define ASYNC_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|IS_A_CONSOLE
mdefine_line|#define IS_A_CONSOLE(min)&t;(((min) &amp; 0xC0) == 0x00)
DECL|macro|IS_A_SERIAL
mdefine_line|#define IS_A_SERIAL(min)&t;(((min) &amp; 0xC0) == 0x40)
DECL|macro|IS_A_PTY
mdefine_line|#define IS_A_PTY(min)&t;&t;((min) &amp; 0x80)
DECL|macro|IS_A_PTY_MASTER
mdefine_line|#define IS_A_PTY_MASTER(min)&t;(((min) &amp; 0xC0) == 0x80)
DECL|macro|IS_A_PTY_SLAVE
mdefine_line|#define IS_A_PTY_SLAVE(min)&t;(((min) &amp; 0xC0) == 0xC0)
DECL|macro|PTY_OTHER
mdefine_line|#define PTY_OTHER(min)&t;&t;((min) ^ 0x40)
DECL|macro|SL_TO_DEV
mdefine_line|#define SL_TO_DEV(line)&t;&t;((line) | 0x40)
DECL|macro|DEV_TO_SL
mdefine_line|#define DEV_TO_SL(min)&t;&t;((min) &amp; 0x3F)
DECL|macro|INC
mdefine_line|#define INC(a) ((a) = ((a)+1) &amp; (TTY_BUF_SIZE-1))
DECL|macro|DEC
mdefine_line|#define DEC(a) ((a) = ((a)-1) &amp; (TTY_BUF_SIZE-1))
DECL|macro|EMPTY
mdefine_line|#define EMPTY(a) ((a)-&gt;head == (a)-&gt;tail)
DECL|macro|LEFT
mdefine_line|#define LEFT(a) (((a)-&gt;tail-(a)-&gt;head-1)&amp;(TTY_BUF_SIZE-1))
DECL|macro|LAST
mdefine_line|#define LAST(a) ((a)-&gt;buf[(TTY_BUF_SIZE-1)&amp;((a)-&gt;head-1)])
DECL|macro|FULL
mdefine_line|#define FULL(a) (!LEFT(a))
DECL|macro|CHARS
mdefine_line|#define CHARS(a) (((a)-&gt;head-(a)-&gt;tail)&amp;(TTY_BUF_SIZE-1))
r_extern
r_void
id|put_tty_queue
c_func
(paren
r_char
id|c
comma
r_struct
id|tty_queue
op_star
id|queue
)paren
suffix:semicolon
r_extern
r_int
id|get_tty_queue
c_func
(paren
r_struct
id|tty_queue
op_star
id|queue
)paren
suffix:semicolon
DECL|macro|INTR_CHAR
mdefine_line|#define INTR_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VINTR])
DECL|macro|QUIT_CHAR
mdefine_line|#define QUIT_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VQUIT])
DECL|macro|ERASE_CHAR
mdefine_line|#define ERASE_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VERASE])
DECL|macro|KILL_CHAR
mdefine_line|#define KILL_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VKILL])
DECL|macro|EOF_CHAR
mdefine_line|#define EOF_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOF])
DECL|macro|START_CHAR
mdefine_line|#define START_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTART])
DECL|macro|STOP_CHAR
mdefine_line|#define STOP_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTOP])
DECL|macro|SUSPEND_CHAR
mdefine_line|#define SUSPEND_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSUSP])
DECL|macro|LNEXT_CHAR
mdefine_line|#define LNEXT_CHAR(tty)&t;((tty)-&gt;termios-&gt;c_cc[VLNEXT])
DECL|macro|_L_FLAG
mdefine_line|#define _L_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_lflag &amp; f)
DECL|macro|_I_FLAG
mdefine_line|#define _I_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_iflag &amp; f)
DECL|macro|_O_FLAG
mdefine_line|#define _O_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_oflag &amp; f)
DECL|macro|_C_FLAG
mdefine_line|#define _C_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_cflag &amp; f)
DECL|macro|L_CANON
mdefine_line|#define L_CANON(tty)&t;_L_FLAG((tty),ICANON)
DECL|macro|L_ISIG
mdefine_line|#define L_ISIG(tty)&t;_L_FLAG((tty),ISIG)
DECL|macro|L_ECHO
mdefine_line|#define L_ECHO(tty)&t;_L_FLAG((tty),ECHO)
DECL|macro|L_ECHOE
mdefine_line|#define L_ECHOE(tty)&t;_L_FLAG((tty),ECHOE)
DECL|macro|L_ECHOK
mdefine_line|#define L_ECHOK(tty)&t;_L_FLAG((tty),ECHOK)
DECL|macro|L_ECHONL
mdefine_line|#define L_ECHONL(tty)&t;_L_FLAG((tty),ECHONL)
DECL|macro|L_ECHOCTL
mdefine_line|#define L_ECHOCTL(tty)&t;_L_FLAG((tty),ECHOCTL)
DECL|macro|L_ECHOKE
mdefine_line|#define L_ECHOKE(tty)&t;_L_FLAG((tty),ECHOKE)
DECL|macro|L_TOSTOP
mdefine_line|#define L_TOSTOP(tty)&t;_L_FLAG((tty),TOSTOP)
DECL|macro|I_IGNBRK
mdefine_line|#define I_IGNBRK(tty)&t;_I_FLAG((tty),IGNBRK)
DECL|macro|I_BRKINT
mdefine_line|#define I_BRKINT(tty)&t;_I_FLAG((tty),BRKINT)
DECL|macro|I_IGNPAR
mdefine_line|#define I_IGNPAR(tty)&t;_I_FLAG((tty),IGNPAR)
DECL|macro|I_PARMRK
mdefine_line|#define I_PARMRK(tty)&t;_I_FLAG((tty),PARMRK)
DECL|macro|I_INPCK
mdefine_line|#define I_INPCK(tty)&t;_I_FLAG((tty),INPCK)
DECL|macro|I_UCLC
mdefine_line|#define I_UCLC(tty)&t;_I_FLAG((tty),IUCLC)
DECL|macro|I_NLCR
mdefine_line|#define I_NLCR(tty)&t;_I_FLAG((tty),INLCR)
DECL|macro|I_CRNL
mdefine_line|#define I_CRNL(tty)&t;_I_FLAG((tty),ICRNL)
DECL|macro|I_NOCR
mdefine_line|#define I_NOCR(tty)&t;_I_FLAG((tty),IGNCR)
DECL|macro|I_IXON
mdefine_line|#define I_IXON(tty)&t;_I_FLAG((tty),IXON)
DECL|macro|I_IXANY
mdefine_line|#define I_IXANY(tty)&t;_I_FLAG((tty),IXANY)
DECL|macro|I_STRP
mdefine_line|#define I_STRP(tty)&t;_I_FLAG((tty),ISTRIP)
DECL|macro|O_POST
mdefine_line|#define O_POST(tty)&t;_O_FLAG((tty),OPOST)
DECL|macro|O_NLCR
mdefine_line|#define O_NLCR(tty)&t;_O_FLAG((tty),ONLCR)
DECL|macro|O_CRNL
mdefine_line|#define O_CRNL(tty)&t;_O_FLAG((tty),OCRNL)
DECL|macro|O_NLRET
mdefine_line|#define O_NLRET(tty)&t;_O_FLAG((tty),ONLRET)
DECL|macro|O_LCUC
mdefine_line|#define O_LCUC(tty)&t;_O_FLAG((tty),OLCUC)
DECL|macro|C_LOCAL
mdefine_line|#define C_LOCAL(tty)&t;_C_FLAG((tty),CLOCAL)
DECL|macro|C_RTSCTS
mdefine_line|#define C_RTSCTS(tty)&t;_C_FLAG((tty),CRTSCTS)
DECL|macro|C_SPEED
mdefine_line|#define C_SPEED(tty)&t;((tty)-&gt;termios-&gt;c_cflag &amp; CBAUD)
DECL|macro|C_HUP
mdefine_line|#define C_HUP(tty)&t;(C_SPEED((tty)) == B0)
multiline_comment|/*&n; * Where all of the state associated with a tty is kept while the tty&n; * is open.  Since the termios state should be kept even if the tty&n; * has been closed --- for things like the baud rate, etc --- it is&n; * not stored here, but rather a pointer to the real state is stored&n; * here.  Possible the winsize structure should have the same&n; * treatment, but (1) the default 80x24 is usually right and (2) it&squot;s&n; * most often used by a windowing system, which will set the correct&n; * size each time the window is created or resized anyway.&n; * IMPORTANT: since this structure is dynamically allocated, it must&n; * be no larger than 4096 bytes.  Changing TTY_BUF_SIZE will change&n; * the size of this structure, and it needs to be done with care.&n; * &t;&t;&t;&t;&t;&t;- TYT, 9/14/92&n; */
DECL|struct|tty_struct
r_struct
id|tty_struct
(brace
DECL|member|termios
r_struct
id|termios
op_star
id|termios
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|stopped
DECL|member|status_changed
DECL|member|packet
DECL|member|lnext
r_int
r_char
id|stopped
suffix:colon
l_int|1
comma
id|status_changed
suffix:colon
l_int|1
comma
id|packet
suffix:colon
l_int|1
comma
id|lnext
suffix:colon
l_int|1
suffix:semicolon
DECL|member|char_error
r_int
r_char
id|char_error
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ctrl_status
r_int
r_char
id|ctrl_status
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|disc
r_int
id|disc
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|winsize
r_struct
id|winsize
id|winsize
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|throttle
r_void
(paren
op_star
id|throttle
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|status
)paren
suffix:semicolon
DECL|member|set_termios
r_void
(paren
op_star
id|set_termios
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old
)paren
suffix:semicolon
DECL|member|link
r_struct
id|tty_struct
op_star
id|link
suffix:semicolon
DECL|member|write_data_ptr
r_int
r_char
op_star
id|write_data_ptr
suffix:semicolon
DECL|member|write_data_cnt
r_int
id|write_data_cnt
suffix:semicolon
DECL|member|write_data_callback
r_void
(paren
op_star
id|write_data_callback
)paren
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|write_data_arg
r_void
op_star
id|write_data_arg
suffix:semicolon
DECL|member|readq_flags
r_int
id|readq_flags
(braket
id|TTY_BUF_SIZE
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|read_q
r_struct
id|tty_queue
id|read_q
suffix:semicolon
DECL|member|write_q
r_struct
id|tty_queue
id|write_q
suffix:semicolon
DECL|member|secondary
r_struct
id|tty_queue
id|secondary
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tty_ldisc
r_struct
id|tty_ldisc
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * The following routines are called from above.&n;&t; */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The following routines are called from below.&n;&t; */
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LDISC_FLAG_DEFINED
mdefine_line|#define LDISC_FLAG_DEFINED&t;0x00000001
multiline_comment|/*&n; * These are the different types of thottle status which can be sent&n; * to the low-level tty driver.  The tty_io.c layer is responsible for&n; * notifying the low-level tty driver of the following conditions:&n; * secondary queue full, secondary queue available, and read queue&n; * available.  The low-level driver must send the read queue full&n; * command to itself, if it is interested in that condition.&n; *&n; * Note that the low-level tty driver may elect to ignore one or both&n; * of these conditions; normally, however, it will use ^S/^Q or some&n; * sort of hardware flow control to regulate the input to try to avoid&n; * overflow.  While the low-level driver is responsible for all&n; * receiving flow control, note that the ^S/^Q handling (but not&n; * hardware flow control) is handled by the upper layer, in&n; * copy_to_cooked.  &n; */
DECL|macro|TTY_THROTTLE_SQ_FULL
mdefine_line|#define TTY_THROTTLE_SQ_FULL&t;1
DECL|macro|TTY_THROTTLE_SQ_AVAIL
mdefine_line|#define TTY_THROTTLE_SQ_AVAIL&t;2
DECL|macro|TTY_THROTTLE_RQ_FULL
mdefine_line|#define TTY_THROTTLE_RQ_FULL&t;3
DECL|macro|TTY_THROTTLE_RQ_AVAIL
mdefine_line|#define TTY_THROTTLE_RQ_AVAIL&t;4
multiline_comment|/*&n; * This defines the low- and high-watermarks for the various conditions.&n; * Again, the low-level driver is free to ignore any of these, and has&n; * to implement RQ_THREHOLD_LW for itself if it wants it.&n; */
DECL|macro|SQ_THRESHOLD_LW
mdefine_line|#define SQ_THRESHOLD_LW&t;16
DECL|macro|SQ_THRESHOLD_HW
mdefine_line|#define SQ_THRESHOLD_HW 768
DECL|macro|RQ_THRESHOLD_LW
mdefine_line|#define RQ_THRESHOLD_LW 16
DECL|macro|RQ_THRESHOLD_HW
mdefine_line|#define RQ_THRESHOLD_HW 768
multiline_comment|/*&n; * These bits are used in the flags field of the tty structure.&n; * &n; * So that interrupts won&squot;t be able to mess up the queues,&n; * copy_to_cooked must be atomic with repect to itself, as must&n; * tty-&gt;write.  Thus, you must use the inline functions set_bit() and&n; * clear_bit() to make things atomic.&n; */
DECL|macro|TTY_WRITE_BUSY
mdefine_line|#define TTY_WRITE_BUSY 0
DECL|macro|TTY_READ_BUSY
mdefine_line|#define TTY_READ_BUSY 1
DECL|macro|TTY_CR_PENDING
mdefine_line|#define TTY_CR_PENDING 2
DECL|macro|TTY_SQ_THROTTLED
mdefine_line|#define TTY_SQ_THROTTLED 3
DECL|macro|TTY_RQ_THROTTLED
mdefine_line|#define TTY_RQ_THROTTLED 4
DECL|macro|TTY_IO_ERROR
mdefine_line|#define TTY_IO_ERROR 5
multiline_comment|/*&n; * When a break, frame error, or parity error happens, these codes are&n; * stuffed into the read queue, and the relevant bit in readq_flag bit&n; * array is set.&n; */
DECL|macro|TTY_BREAK
mdefine_line|#define TTY_BREAK&t;1
DECL|macro|TTY_FRAME
mdefine_line|#define TTY_FRAME&t;2
DECL|macro|TTY_PARITY
mdefine_line|#define TTY_PARITY&t;3
DECL|macro|TTY_WRITE_FLUSH
mdefine_line|#define TTY_WRITE_FLUSH(tty) tty_write_flush((tty))
DECL|macro|TTY_READ_FLUSH
mdefine_line|#define TTY_READ_FLUSH(tty) tty_read_flush((tty))
r_extern
r_void
id|tty_write_flush
c_func
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|tty_read_flush
c_func
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|tty_struct
op_star
id|tty_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|tty_check_write
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|tty_struct
op_star
id|redirect
suffix:semicolon
r_extern
r_struct
id|tty_ldisc
id|ldiscs
(braket
)braket
suffix:semicolon
r_extern
r_int
id|fg_console
suffix:semicolon
r_extern
r_int
r_int
id|video_num_columns
suffix:semicolon
r_extern
r_int
r_int
id|video_num_lines
suffix:semicolon
r_extern
r_struct
id|wait_queue
op_star
id|keypress_wait
suffix:semicolon
DECL|macro|TTY_TABLE_IDX
mdefine_line|#define TTY_TABLE_IDX(nr)&t;((nr) ? (nr) : (fg_console+1))
DECL|macro|TTY_TABLE
mdefine_line|#define TTY_TABLE(nr) &t;&t;(tty_table[TTY_TABLE_IDX(nr)])
multiline_comment|/*&t;intr=^C&t;&t;quit=^|&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;vtime=&bslash;0&t;vmin=&bslash;1&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;eol=&bslash;0&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;eol2=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;1&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;0&quot;
r_extern
r_int
id|rs_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|lp_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|con_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|tty_init
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_input
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|flush_output
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|wait_until_sent
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|copy_to_cooked
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|tty_register_ldisc
c_func
(paren
r_int
id|disc
comma
r_struct
id|tty_ldisc
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|tty_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|is_orphaned_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
r_extern
r_int
id|is_ignored
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|tty_signal
c_func
(paren
r_int
id|sig
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|kill_pg
c_func
(paren
r_int
id|pgrp
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|kill_sl
c_func
(paren
r_int
id|sess
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_void
id|tty_hangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|tty_vhangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|tty_unhangup
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_int
id|tty_hung_up_p
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|do_SAK
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
multiline_comment|/* tty write functions */
r_extern
r_void
id|rs_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_void
id|con_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
multiline_comment|/* serial.c */
r_extern
r_int
id|rs_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* pty.c */
r_extern
r_int
id|pty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* console.c */
r_extern
r_int
id|con_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|update_screen
c_func
(paren
r_int
id|new_console
)paren
suffix:semicolon
r_extern
r_void
id|blank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unblank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* vt.c */
r_extern
r_int
id|vt_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif
eof
