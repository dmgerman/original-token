macro_line|#ifndef _LINUX_TTY_H
DECL|macro|_LINUX_TTY_H
mdefine_line|#define _LINUX_TTY_H
multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/tty_ldisc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Note: don&squot;t mess with NR_PTYS until you understand the tty minor &n; * number allocation game...&n; * (Note: the *_driver.minor_start values 1, 64, 128, 192 are&n; * hardcoded at present.)&n; */
DECL|macro|MIN_NR_CONSOLES
mdefine_line|#define MIN_NR_CONSOLES&t;1&t;/* must be at least 1 */
DECL|macro|MAX_NR_CONSOLES
mdefine_line|#define MAX_NR_CONSOLES&t;63&t;/* serial lines start at 64 */
DECL|macro|MAX_NR_USER_CONSOLES
mdefine_line|#define MAX_NR_USER_CONSOLES 63&t;/* must be root to allocate above this */
multiline_comment|/* Note: the ioctl VT_GETSTATE does not work for&n;&t;&t;   consoles 16 and higher (since it returns a short) */
DECL|macro|NR_PTYS
mdefine_line|#define NR_PTYS&t;&t;64
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
multiline_comment|/*&n; * This character is the same as _POSIX_VDISABLE: it cannot be used as&n; * a c_cc[] character, but indicates that a particular special character&n; * isn&squot;t in use (eg VINTR has no character etc)&n; */
DECL|macro|__DISABLED_CHAR
mdefine_line|#define __DISABLED_CHAR &squot;&bslash;0&squot;
multiline_comment|/*&n; * This is the flip buffer used for the tty driver.  The buffer is&n; * located in the tty structure, and is used as a high speed interface&n; * between the tty driver and the tty line discipline.&n; */
DECL|macro|TTY_FLIPBUF_SIZE
mdefine_line|#define TTY_FLIPBUF_SIZE 512
DECL|struct|tty_flip_buffer
r_struct
id|tty_flip_buffer
(brace
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|char_buf
r_int
r_char
id|char_buf
(braket
l_int|2
op_star
id|TTY_FLIPBUF_SIZE
)braket
suffix:semicolon
DECL|member|flag_buf
r_char
id|flag_buf
(braket
l_int|2
op_star
id|TTY_FLIPBUF_SIZE
)braket
suffix:semicolon
DECL|member|char_buf_ptr
r_char
op_star
id|char_buf_ptr
suffix:semicolon
DECL|member|flag_buf_ptr
r_int
r_char
op_star
id|flag_buf_ptr
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|buf_num
r_int
id|buf_num
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * When a break, frame error, or parity error happens, these codes are&n; * stuffed into the flags buffer.&n; */
DECL|macro|TTY_NORMAL
mdefine_line|#define TTY_NORMAL&t;0
DECL|macro|TTY_BREAK
mdefine_line|#define TTY_BREAK&t;1
DECL|macro|TTY_FRAME
mdefine_line|#define TTY_FRAME&t;2
DECL|macro|TTY_PARITY
mdefine_line|#define TTY_PARITY&t;3
DECL|macro|TTY_OVERRUN
mdefine_line|#define TTY_OVERRUN&t;4
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
DECL|macro|TIME_CHAR
mdefine_line|#define TIME_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VTIME])
DECL|macro|MIN_CHAR
mdefine_line|#define MIN_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VMIN])
DECL|macro|SWTC_CHAR
mdefine_line|#define SWTC_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSWTC])
DECL|macro|START_CHAR
mdefine_line|#define START_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTART])
DECL|macro|STOP_CHAR
mdefine_line|#define STOP_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSTOP])
DECL|macro|SUSP_CHAR
mdefine_line|#define SUSP_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VSUSP])
DECL|macro|EOL_CHAR
mdefine_line|#define EOL_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOL])
DECL|macro|REPRINT_CHAR
mdefine_line|#define REPRINT_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VREPRINT])
DECL|macro|DISCARD_CHAR
mdefine_line|#define DISCARD_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VDISCARD])
DECL|macro|WERASE_CHAR
mdefine_line|#define WERASE_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VWERASE])
DECL|macro|LNEXT_CHAR
mdefine_line|#define LNEXT_CHAR(tty)&t;((tty)-&gt;termios-&gt;c_cc[VLNEXT])
DECL|macro|EOL2_CHAR
mdefine_line|#define EOL2_CHAR(tty) ((tty)-&gt;termios-&gt;c_cc[VEOL2])
DECL|macro|_I_FLAG
mdefine_line|#define _I_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_iflag &amp; (f))
DECL|macro|_O_FLAG
mdefine_line|#define _O_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_oflag &amp; (f))
DECL|macro|_C_FLAG
mdefine_line|#define _C_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_cflag &amp; (f))
DECL|macro|_L_FLAG
mdefine_line|#define _L_FLAG(tty,f)&t;((tty)-&gt;termios-&gt;c_lflag &amp; (f))
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
DECL|macro|I_ISTRIP
mdefine_line|#define I_ISTRIP(tty)&t;_I_FLAG((tty),ISTRIP)
DECL|macro|I_INLCR
mdefine_line|#define I_INLCR(tty)&t;_I_FLAG((tty),INLCR)
DECL|macro|I_IGNCR
mdefine_line|#define I_IGNCR(tty)&t;_I_FLAG((tty),IGNCR)
DECL|macro|I_ICRNL
mdefine_line|#define I_ICRNL(tty)&t;_I_FLAG((tty),ICRNL)
DECL|macro|I_IUCLC
mdefine_line|#define I_IUCLC(tty)&t;_I_FLAG((tty),IUCLC)
DECL|macro|I_IXON
mdefine_line|#define I_IXON(tty)&t;_I_FLAG((tty),IXON)
DECL|macro|I_IXANY
mdefine_line|#define I_IXANY(tty)&t;_I_FLAG((tty),IXANY)
DECL|macro|I_IXOFF
mdefine_line|#define I_IXOFF(tty)&t;_I_FLAG((tty),IXOFF)
DECL|macro|I_IMAXBEL
mdefine_line|#define I_IMAXBEL(tty)&t;_I_FLAG((tty),IMAXBEL)
DECL|macro|O_OPOST
mdefine_line|#define O_OPOST(tty)&t;_O_FLAG((tty),OPOST)
DECL|macro|O_OLCUC
mdefine_line|#define O_OLCUC(tty)&t;_O_FLAG((tty),OLCUC)
DECL|macro|O_ONLCR
mdefine_line|#define O_ONLCR(tty)&t;_O_FLAG((tty),ONLCR)
DECL|macro|O_OCRNL
mdefine_line|#define O_OCRNL(tty)&t;_O_FLAG((tty),OCRNL)
DECL|macro|O_ONOCR
mdefine_line|#define O_ONOCR(tty)&t;_O_FLAG((tty),ONOCR)
DECL|macro|O_ONLRET
mdefine_line|#define O_ONLRET(tty)&t;_O_FLAG((tty),ONLRET)
DECL|macro|O_OFILL
mdefine_line|#define O_OFILL(tty)&t;_O_FLAG((tty),OFILL)
DECL|macro|O_OFDEL
mdefine_line|#define O_OFDEL(tty)&t;_O_FLAG((tty),OFDEL)
DECL|macro|O_NLDLY
mdefine_line|#define O_NLDLY(tty)&t;_O_FLAG((tty),NLDLY)
DECL|macro|O_CRDLY
mdefine_line|#define O_CRDLY(tty)&t;_O_FLAG((tty),CRDLY)
DECL|macro|O_TABDLY
mdefine_line|#define O_TABDLY(tty)&t;_O_FLAG((tty),TABDLY)
DECL|macro|O_BSDLY
mdefine_line|#define O_BSDLY(tty)&t;_O_FLAG((tty),BSDLY)
DECL|macro|O_VTDLY
mdefine_line|#define O_VTDLY(tty)&t;_O_FLAG((tty),VTDLY)
DECL|macro|O_FFDLY
mdefine_line|#define O_FFDLY(tty)&t;_O_FLAG((tty),FFDLY)
DECL|macro|C_BAUD
mdefine_line|#define C_BAUD(tty)&t;_C_FLAG((tty),CBAUD)
DECL|macro|C_CSIZE
mdefine_line|#define C_CSIZE(tty)&t;_C_FLAG((tty),CSIZE)
DECL|macro|C_CSTOPB
mdefine_line|#define C_CSTOPB(tty)&t;_C_FLAG((tty),CSTOPB)
DECL|macro|C_CREAD
mdefine_line|#define C_CREAD(tty)&t;_C_FLAG((tty),CREAD)
DECL|macro|C_PARENB
mdefine_line|#define C_PARENB(tty)&t;_C_FLAG((tty),PARENB)
DECL|macro|C_PARODD
mdefine_line|#define C_PARODD(tty)&t;_C_FLAG((tty),PARODD)
DECL|macro|C_HUPCL
mdefine_line|#define C_HUPCL(tty)&t;_C_FLAG((tty),HUPCL)
DECL|macro|C_CLOCAL
mdefine_line|#define C_CLOCAL(tty)&t;_C_FLAG((tty),CLOCAL)
DECL|macro|C_CIBAUD
mdefine_line|#define C_CIBAUD(tty)&t;_C_FLAG((tty),CIBAUD)
DECL|macro|C_CRTSCTS
mdefine_line|#define C_CRTSCTS(tty)&t;_C_FLAG((tty),CRTSCTS)
DECL|macro|L_ISIG
mdefine_line|#define L_ISIG(tty)&t;_L_FLAG((tty),ISIG)
DECL|macro|L_ICANON
mdefine_line|#define L_ICANON(tty)&t;_L_FLAG((tty),ICANON)
DECL|macro|L_XCASE
mdefine_line|#define L_XCASE(tty)&t;_L_FLAG((tty),XCASE)
DECL|macro|L_ECHO
mdefine_line|#define L_ECHO(tty)&t;_L_FLAG((tty),ECHO)
DECL|macro|L_ECHOE
mdefine_line|#define L_ECHOE(tty)&t;_L_FLAG((tty),ECHOE)
DECL|macro|L_ECHOK
mdefine_line|#define L_ECHOK(tty)&t;_L_FLAG((tty),ECHOK)
DECL|macro|L_ECHONL
mdefine_line|#define L_ECHONL(tty)&t;_L_FLAG((tty),ECHONL)
DECL|macro|L_NOFLSH
mdefine_line|#define L_NOFLSH(tty)&t;_L_FLAG((tty),NOFLSH)
DECL|macro|L_TOSTOP
mdefine_line|#define L_TOSTOP(tty)&t;_L_FLAG((tty),TOSTOP)
DECL|macro|L_ECHOCTL
mdefine_line|#define L_ECHOCTL(tty)&t;_L_FLAG((tty),ECHOCTL)
DECL|macro|L_ECHOPRT
mdefine_line|#define L_ECHOPRT(tty)&t;_L_FLAG((tty),ECHOPRT)
DECL|macro|L_ECHOKE
mdefine_line|#define L_ECHOKE(tty)&t;_L_FLAG((tty),ECHOKE)
DECL|macro|L_FLUSHO
mdefine_line|#define L_FLUSHO(tty)&t;_L_FLAG((tty),FLUSHO)
DECL|macro|L_PENDIN
mdefine_line|#define L_PENDIN(tty)&t;_L_FLAG((tty),PENDIN)
DECL|macro|L_IEXTEN
mdefine_line|#define L_IEXTEN(tty)&t;_L_FLAG((tty),IEXTEN)
multiline_comment|/*&n; * Where all of the state associated with a tty is kept while the tty&n; * is open.  Since the termios state should be kept even if the tty&n; * has been closed --- for things like the baud rate, etc --- it is&n; * not stored here, but rather a pointer to the real state is stored&n; * here.  Possible the winsize structure should have the same&n; * treatment, but (1) the default 80x24 is usually right and (2) it&squot;s&n; * most often used by a windowing system, which will set the correct&n; * size each time the window is created or resized anyway.&n; * IMPORTANT: since this structure is dynamically allocated, it must&n; * be no larger than 4096 bytes.  Changing TTY_BUF_SIZE will change&n; * the size of this structure, and it needs to be done with care.&n; * &t;&t;&t;&t;&t;&t;- TYT, 9/14/92&n; */
DECL|struct|tty_struct
r_struct
id|tty_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|driver
r_struct
id|tty_driver
id|driver
suffix:semicolon
DECL|member|ldisc
r_struct
id|tty_ldisc
id|ldisc
suffix:semicolon
DECL|member|termios
DECL|member|termios_locked
r_struct
id|termios
op_star
id|termios
comma
op_star
id|termios_locked
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|device
id|dev_t
id|device
suffix:semicolon
DECL|member|flags
r_int
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
DECL|member|stopped
DECL|member|hw_stopped
DECL|member|packet
r_int
r_char
id|stopped
suffix:colon
l_int|1
comma
id|hw_stopped
suffix:colon
l_int|1
comma
id|packet
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ctrl_status
r_int
r_char
id|ctrl_status
suffix:semicolon
DECL|member|link
r_struct
id|tty_struct
op_star
id|link
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|flip
r_struct
id|tty_flip_buffer
id|flip
suffix:semicolon
DECL|member|max_flip_cnt
r_int
id|max_flip_cnt
suffix:semicolon
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
DECL|member|disc_data
r_void
op_star
id|disc_data
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
DECL|macro|N_TTY_BUF_SIZE
mdefine_line|#define N_TTY_BUF_SIZE 4096
multiline_comment|/*&n;&t; * The following is data for the N_TTY line discipline.  For&n;&t; * historical reasons, this is included in the tty structure.&n;&t; */
DECL|member|column
r_int
r_int
id|column
suffix:semicolon
DECL|member|lnext
DECL|member|erasing
DECL|member|raw
DECL|member|real_raw
DECL|member|icanon
r_int
r_char
id|lnext
suffix:colon
l_int|1
comma
id|erasing
suffix:colon
l_int|1
comma
id|raw
suffix:colon
l_int|1
comma
id|real_raw
suffix:colon
l_int|1
comma
id|icanon
suffix:colon
l_int|1
suffix:semicolon
DECL|member|closing
r_int
r_char
id|closing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|minimum_to_wake
r_int
r_int
id|minimum_to_wake
suffix:semicolon
DECL|member|overrun_time
r_int
id|overrun_time
suffix:semicolon
DECL|member|num_overrun
r_int
id|num_overrun
suffix:semicolon
DECL|member|process_char_map
r_int
id|process_char_map
(braket
l_int|256
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|read_buf
r_char
op_star
id|read_buf
suffix:semicolon
DECL|member|read_head
r_int
id|read_head
suffix:semicolon
DECL|member|read_tail
r_int
id|read_tail
suffix:semicolon
DECL|member|read_cnt
r_int
id|read_cnt
suffix:semicolon
DECL|member|read_flags
r_int
r_int
id|read_flags
(braket
id|N_TTY_BUF_SIZE
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
)braket
suffix:semicolon
DECL|member|canon_data
r_int
id|canon_data
suffix:semicolon
DECL|member|canon_head
r_int
r_int
id|canon_head
suffix:semicolon
DECL|member|canon_column
r_int
r_int
id|canon_column
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* tty magic number */
DECL|macro|TTY_MAGIC
mdefine_line|#define TTY_MAGIC&t;&t;0x5401
multiline_comment|/*&n; * These bits are used in the flags field of the tty structure.&n; * &n; * So that interrupts won&squot;t be able to mess up the queues,&n; * copy_to_cooked must be atomic with respect to itself, as must&n; * tty-&gt;write.  Thus, you must use the inline functions set_bit() and&n; * clear_bit() to make things atomic.&n; */
DECL|macro|TTY_THROTTLED
mdefine_line|#define TTY_THROTTLED 0
DECL|macro|TTY_IO_ERROR
mdefine_line|#define TTY_IO_ERROR 1
DECL|macro|TTY_SLAVE_CLOSED
mdefine_line|#define TTY_SLAVE_CLOSED 2
DECL|macro|TTY_EXCLUSIVE
mdefine_line|#define TTY_EXCLUSIVE 3
DECL|macro|TTY_DEBUG
mdefine_line|#define TTY_DEBUG 4
DECL|macro|TTY_DO_WRITE_WAKEUP
mdefine_line|#define TTY_DO_WRITE_WAKEUP 5
DECL|macro|TTY_PUSH
mdefine_line|#define TTY_PUSH 6
DECL|macro|TTY_CLOSING
mdefine_line|#define TTY_CLOSING 7
DECL|macro|TTY_WRITE_FLUSH
mdefine_line|#define TTY_WRITE_FLUSH(tty) tty_write_flush((tty))
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
r_struct
id|termios
id|tty_std_termios
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
r_struct
id|wait_queue
op_star
id|keypress_wait
suffix:semicolon
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
id|pty_init
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
r_int
id|vcs_init
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CYCLADES
r_extern
r_int
id|cy_init
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|tty_paranoia_check
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
id|dev_t
id|device
comma
r_const
r_char
op_star
id|routine
)paren
suffix:semicolon
r_extern
r_char
op_star
id|_tty_name
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_char
op_star
id|tty_name
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
id|tty_wait_until_sent
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|tty_check_change
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
id|stop_tty
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
id|start_tty
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
id|new_ldisc
)paren
suffix:semicolon
r_extern
r_int
id|tty_register_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_int
id|tty_unregister_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_int
id|tty_read_raw_data
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
op_star
id|bufp
comma
r_int
id|buflen
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
r_extern
r_void
id|disassociate_ctty
c_func
(paren
r_int
id|priv
)paren
suffix:semicolon
multiline_comment|/* n_tty.c */
r_extern
r_struct
id|tty_ldisc
id|tty_ldisc_N_TTY
suffix:semicolon
multiline_comment|/* tty_ioctl.c */
r_extern
r_int
id|n_tty_ioctl
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
