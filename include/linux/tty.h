multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; *&n; * NOTE! Don&squot;t touch this without checking that nothing in rs_io.s or&n; * con_io.s breaks. Some constants are hardwired into the system (mainly&n; * offsets into &squot;tty_queue&squot;&n; */
macro_line|#ifndef _TTY_H
DECL|macro|_TTY_H
mdefine_line|#define _TTY_H
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NR_CONSOLES
mdefine_line|#define NR_CONSOLES&t;8
DECL|macro|NR_SERIALS
mdefine_line|#define NR_SERIALS&t;4
DECL|macro|NR_PTYS
mdefine_line|#define NR_PTYS&t;&t;4
multiline_comment|/*&n; * This character is the same as _POSIX_VDISABLE: it cannot be used as&n; * a c_cc[] character, but indicates that a particular special character&n; * isn&squot;t in use (eg VINTR ahs no character etc)&n; */
DECL|macro|__DISABLED_CHAR
mdefine_line|#define __DISABLED_CHAR &squot;&bslash;0&squot;
macro_line|#include &lt;termios.h&gt;
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
id|task_struct
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
DECL|function|PUTCH
r_static
r_inline
r_void
id|PUTCH
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
(brace
r_int
id|head
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|head
op_assign
(paren
id|queue-&gt;head
op_plus
l_int|1
)paren
op_amp
(paren
id|TTY_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ne
id|queue-&gt;tail
)paren
(brace
id|queue-&gt;buf
(braket
id|queue-&gt;head
)braket
op_assign
id|c
suffix:semicolon
id|queue-&gt;head
op_assign
id|head
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|GETCH
r_static
r_inline
r_int
id|GETCH
c_func
(paren
r_struct
id|tty_queue
op_star
id|queue
)paren
(brace
r_int
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|queue-&gt;tail
op_ne
id|queue-&gt;head
)paren
(brace
id|result
op_assign
l_int|0xff
op_amp
id|queue-&gt;buf
(braket
id|queue-&gt;tail
)braket
suffix:semicolon
id|queue-&gt;tail
op_assign
(paren
id|queue-&gt;tail
op_plus
l_int|1
)paren
op_amp
(paren
id|TTY_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
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
DECL|member|busy
r_int
id|busy
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
multiline_comment|/*&n; * so that interrupts won&squot;t be able to mess up the&n; * queues, copy_to_cooked must be atomic with repect&n; * to itself, as must tty-&gt;write.&n; */
DECL|macro|TTY_WRITE_BUSY
mdefine_line|#define TTY_WRITE_BUSY 1
DECL|macro|TTY_READ_BUSY
mdefine_line|#define TTY_READ_BUSY 2
DECL|macro|TTY_WRITE_FLUSH
mdefine_line|#define TTY_WRITE_FLUSH(tty) &bslash;&n;do { &bslash;&n;&t;cli(); &bslash;&n;&t;if (!EMPTY((tty)-&gt;write_q) &amp;&amp; !(TTY_WRITE_BUSY &amp; (tty)-&gt;busy)) { &bslash;&n;&t;&t;(tty)-&gt;busy |= TTY_WRITE_BUSY; &bslash;&n;&t;&t;sti(); &bslash;&n;&t;&t;(tty)-&gt;write((tty)); &bslash;&n;&t;&t;cli(); &bslash;&n;&t;&t;(tty)-&gt;busy &amp;= ~TTY_WRITE_BUSY; &bslash;&n;&t;} &bslash;&n;&t;sti(); &bslash;&n;} while (0)
DECL|macro|TTY_READ_FLUSH
mdefine_line|#define TTY_READ_FLUSH(tty) &bslash;&n;do { &bslash;&n;&t;cli(); &bslash;&n;&t;if (!EMPTY((tty)-&gt;read_q) &amp;&amp; !(TTY_READ_BUSY &amp; (tty)-&gt;busy)) { &bslash;&n;&t;&t;(tty)-&gt;busy |= TTY_READ_BUSY; &bslash;&n;&t;&t;sti(); &bslash;&n;&t;&t;copy_to_cooked((tty)); &bslash;&n;&t;&t;cli(); &bslash;&n;&t;&t;(tty)-&gt;busy &amp;= ~TTY_READ_BUSY; &bslash;&n;&t;} &bslash;&n;&t;sti(); &bslash;&n;} while (0)
r_extern
r_struct
id|tty_struct
id|tty_table
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
id|flush
c_func
(paren
r_struct
id|tty_queue
op_star
id|queue
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
r_extern
r_void
id|serial_open
c_func
(paren
r_int
r_int
id|line
)paren
suffix:semicolon
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
macro_line|#endif
eof
