macro_line|#ifndef _LINUX_TTY_H
DECL|macro|_LINUX_TTY_H
mdefine_line|#define _LINUX_TTY_H
multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; *&n; * NOTE! Don&squot;t touch this without checking that nothing in rs_io.s or&n; * con_io.s breaks. Some constants are hardwired into the system (mainly&n; * offsets into &squot;tty_queue&squot;&n; */
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NR_CONSOLES
mdefine_line|#define NR_CONSOLES&t;8
DECL|macro|NR_SERIALS
mdefine_line|#define NR_SERIALS&t;4
DECL|macro|NR_PTYS
mdefine_line|#define NR_PTYS&t;&t;4
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
DECL|macro|TTY_BUF_SIZE
mdefine_line|#define TTY_BUF_SIZE 2048
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
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
r_int
id|line
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
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
mdefine_line|#define INTR_CHAR(tty) ((tty)-&gt;termios.c_cc[VINTR])
DECL|macro|QUIT_CHAR
mdefine_line|#define QUIT_CHAR(tty) ((tty)-&gt;termios.c_cc[VQUIT])
DECL|macro|ERASE_CHAR
mdefine_line|#define ERASE_CHAR(tty) ((tty)-&gt;termios.c_cc[VERASE])
DECL|macro|KILL_CHAR
mdefine_line|#define KILL_CHAR(tty) ((tty)-&gt;termios.c_cc[VKILL])
DECL|macro|EOF_CHAR
mdefine_line|#define EOF_CHAR(tty) ((tty)-&gt;termios.c_cc[VEOF])
DECL|macro|START_CHAR
mdefine_line|#define START_CHAR(tty) ((tty)-&gt;termios.c_cc[VSTART])
DECL|macro|STOP_CHAR
mdefine_line|#define STOP_CHAR(tty) ((tty)-&gt;termios.c_cc[VSTOP])
DECL|macro|SUSPEND_CHAR
mdefine_line|#define SUSPEND_CHAR(tty) ((tty)-&gt;termios.c_cc[VSUSP])
DECL|macro|_L_FLAG
mdefine_line|#define _L_FLAG(tty,f)&t;((tty)-&gt;termios.c_lflag &amp; f)
DECL|macro|_I_FLAG
mdefine_line|#define _I_FLAG(tty,f)&t;((tty)-&gt;termios.c_iflag &amp; f)
DECL|macro|_O_FLAG
mdefine_line|#define _O_FLAG(tty,f)&t;((tty)-&gt;termios.c_oflag &amp; f)
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
DECL|macro|C_SPEED
mdefine_line|#define C_SPEED(tty)&t;((tty)-&gt;termios.c_cflag &amp; CBAUD)
DECL|macro|C_HUP
mdefine_line|#define C_HUP(tty)&t;(C_SPEED((tty)) == B0)
DECL|struct|tty_struct
r_struct
id|tty_struct
(brace
DECL|member|termios
r_struct
id|termios
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
r_int
id|stopped
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
DECL|member|link
r_struct
id|tty_struct
op_star
id|link
suffix:semicolon
DECL|member|read_q
r_struct
id|tty_queue
op_star
id|read_q
suffix:semicolon
DECL|member|write_q
r_struct
id|tty_queue
op_star
id|write_q
suffix:semicolon
DECL|member|secondary
r_struct
id|tty_queue
op_star
id|secondary
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * so that interrupts won&squot;t be able to mess up the&n; * queues, copy_to_cooked must be atomic with repect&n; * to itself, as must tty-&gt;write. These are the flag&n; * bit-numbers. Use the set_bit() and clear_bit()&n; * macros to make it all atomic.&n; */
DECL|macro|TTY_WRITE_BUSY
mdefine_line|#define TTY_WRITE_BUSY 0
DECL|macro|TTY_READ_BUSY
mdefine_line|#define TTY_READ_BUSY 1
DECL|macro|TTY_CR_PENDING
mdefine_line|#define TTY_CR_PENDING 2
multiline_comment|/*&n; * These have to be done with inline assembly: that way the bit-setting&n; * is guaranteed to be atomic. Both set_bit and clear_bit return 0&n; * if the bit-setting went ok, != 0 if the bit already was set/cleared.&n; */
DECL|function|set_bit
r_extern
r_inline
r_int
id|set_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_char
id|ok
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btsl %1,%2&bslash;n&bslash;tsetb %0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|ok
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
DECL|function|clear_bit
r_extern
r_inline
r_int
id|clear_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
r_char
id|ok
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btrl %1,%2&bslash;n&bslash;tsetnb %0&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|ok
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
id|addr
)paren
)paren
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
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
id|tty_table
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|serial_struct
id|serial_table
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
DECL|macro|TTY_TABLE
mdefine_line|#define TTY_TABLE(nr) &bslash;&n;(tty_table + ((nr) ? (((nr) &lt; 64)? (nr)-1:(nr))&t;: fg_console))
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
r_extern
r_void
id|mpty_write
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
id|spty_write
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
id|serial_open
c_func
(paren
r_int
r_int
id|line
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|serial_close
c_func
(paren
r_int
r_int
id|line
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|change_speed
c_func
(paren
r_int
r_int
id|line
)paren
suffix:semicolon
r_extern
r_void
id|send_break
c_func
(paren
r_int
r_int
id|line
)paren
suffix:semicolon
r_extern
r_int
id|get_serial_info
c_func
(paren
r_int
r_int
comma
r_struct
id|serial_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|set_serial_info
c_func
(paren
r_int
r_int
comma
r_struct
id|serial_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* pty.c */
r_extern
r_int
id|pty_open
c_func
(paren
r_int
r_int
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_void
id|pty_close
c_func
(paren
r_int
r_int
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* console.c */
r_void
id|update_screen
c_func
(paren
r_int
id|new_console
)paren
suffix:semicolon
r_void
id|blank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|unblank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
