multiline_comment|/*&n; * &squot;tty.h&squot; defines some structures used by tty_io.c and some defines.&n; *&n; * NOTE! Don&squot;t touch this without checking that nothing in rs_io.s or&n; * con_io.s breaks. Some constants are hardwired into the system (mainly&n; * offsets into &squot;tty_queue&squot;&n; */
macro_line|#ifndef _TTY_H
DECL|macro|_TTY_H
mdefine_line|#define _TTY_H
macro_line|#include &lt;termios.h&gt;
DECL|macro|TTY_BUF_SIZE
mdefine_line|#define TTY_BUF_SIZE 1024
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
r_char
id|buf
(braket
id|TTY_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INC
mdefine_line|#define INC(a) ((a) = ((a)+1) &amp; (TTY_BUF_SIZE-1))
DECL|macro|DEC
mdefine_line|#define DEC(a) ((a) = ((a)-1) &amp; (TTY_BUF_SIZE-1))
DECL|macro|EMPTY
mdefine_line|#define EMPTY(a) ((a).head == (a).tail)
DECL|macro|LEFT
mdefine_line|#define LEFT(a) (((a).tail-(a).head-1)&amp;(TTY_BUF_SIZE-1))
DECL|macro|LAST
mdefine_line|#define LAST(a) ((a).buf[(TTY_BUF_SIZE-1)&amp;((a).head-1)])
DECL|macro|FULL
mdefine_line|#define FULL(a) (!LEFT(a))
DECL|macro|CHARS
mdefine_line|#define CHARS(a) (((a).head-(a).tail)&amp;(TTY_BUF_SIZE-1))
DECL|macro|GETCH
mdefine_line|#define GETCH(queue,c) &bslash;&n;(void)({c=(queue).buf[(queue).tail];INC((queue).tail);})
DECL|macro|PUTCH
mdefine_line|#define PUTCH(c,queue) &bslash;&n;(void)({(queue).buf[(queue).head]=(c);INC((queue).head);})
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
DECL|member|stopped
r_int
id|stopped
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
r_extern
r_struct
id|tty_struct
id|tty_table
(braket
)braket
suffix:semicolon
multiline_comment|/*&t;intr=^C&t;&t;quit=^|&t;&t;erase=del&t;kill=^U&n;&t;eof=^D&t;&t;vtime=&bslash;0&t;vmin=&bslash;1&t;&t;sxtc=&bslash;0&n;&t;start=^Q&t;stop=^S&t;&t;susp=^Z&t;&t;eol=&bslash;0&n;&t;reprint=^R&t;discard=^U&t;werase=^W&t;lnext=^V&n;&t;eol2=&bslash;0&n;*/
DECL|macro|INIT_C_CC
mdefine_line|#define INIT_C_CC &quot;&bslash;003&bslash;034&bslash;177&bslash;025&bslash;004&bslash;0&bslash;1&bslash;0&bslash;021&bslash;023&bslash;032&bslash;0&bslash;022&bslash;017&bslash;027&bslash;026&bslash;0&quot;
r_void
id|rs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|con_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|tty_read
c_func
(paren
r_int
id|c
comma
r_char
op_star
id|buf
comma
r_int
id|n
)paren
suffix:semicolon
r_int
id|tty_write
c_func
(paren
r_int
id|c
comma
r_char
op_star
id|buf
comma
r_int
id|n
)paren
suffix:semicolon
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
macro_line|#endif
eof
