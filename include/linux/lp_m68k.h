macro_line|#ifndef _LINUX_LP_H
DECL|macro|_LINUX_LP_H
mdefine_line|#define _LINUX_LP_H
multiline_comment|/*&n; * split in two parts by Joerg Dorchain&n; * usr/include/linux/lp.h  modified for Amiga by Michael Rausch&n; * modified for Atari by Andreas Schwab&n; * bug fixed by Jes Sorensen 18/8-94:&n; *     It was not possible to compile the kernel only for Atari or Amiga.&n; *&n; * linux i386 version  c.1991-1992 James Wiegand&n; * many modifications copyright (C) 1992 Michael K. Johnson&n; * Interrupt support added 1993 Nigel Gamble&n; */
multiline_comment|/*&n; *  many many printers are we going to support? currently, this is the&n; *  hardcoded limit&n; */
DECL|macro|MAX_LP
mdefine_line|#define MAX_LP 5
multiline_comment|/*&n; * Per POSIX guidelines, this module reserves the LP and lp prefixes&n; * These are the lp_table[minor].flags flags...&n; */
DECL|macro|LP_EXIST
mdefine_line|#define LP_EXIST 0x0001
DECL|macro|LP_BUSY
mdefine_line|#define LP_BUSY&t; 0x0004
DECL|macro|LP_ABORT
mdefine_line|#define LP_ABORT 0x0040
DECL|macro|LP_CAREFUL
mdefine_line|#define LP_CAREFUL 0x0080
DECL|macro|LP_ABORTOPEN
mdefine_line|#define LP_ABORTOPEN 0x0100
multiline_comment|/* timeout for each character.  This is relative to bus cycles -- it&n; * is the count in a busy loop.  THIS IS THE VALUE TO CHANGE if you&n; * have extremely slow printing, or if the machine seems to slow down&n; * a lot when you print.  If you have slow printing, increase this&n; * number and recompile, and if your system gets bogged down, decrease&n; * this number.  This can be changed with the tunelp(8) command as well.&n; */
DECL|macro|LP_INIT_CHAR
mdefine_line|#define LP_INIT_CHAR 1000
multiline_comment|/* The parallel port specs apparently say that there needs to be&n; * a .5usec wait before and after the strobe.  Since there are wildly&n; * different computers running linux, I can&squot;t come up with a perfect&n; * value, but since it worked well on most printers before without,&n; * I&squot;ll initialize it to 0.&n; */
DECL|macro|LP_INIT_WAIT
mdefine_line|#define LP_INIT_WAIT 0
multiline_comment|/* This is the amount of time that the driver waits for the printer to&n; * catch up when the printer&squot;s buffer appears to be filled.  If you&n; * want to tune this and have a fast printer (i.e. HPIIIP), decrease&n; * this number, and if you have a slow printer, increase this number.&n; * This is in hundredths of a second, the default 2 being .05 second.&n; * Or use the tunelp(8) command, which is especially nice if you want&n; * change back and forth between character and graphics printing, which&n; * are wildly different...&n; */
DECL|macro|LP_INIT_TIME
mdefine_line|#define LP_INIT_TIME 40
multiline_comment|/* IOCTL numbers */
DECL|macro|LPCHAR
mdefine_line|#define LPCHAR   0x0601  /* corresponds to LP_INIT_CHAR */
DECL|macro|LPTIME
mdefine_line|#define LPTIME   0x0602  /* corresponds to LP_INIT_TIME */
DECL|macro|LPABORT
mdefine_line|#define LPABORT  0x0604  /* call with TRUE arg to abort on error,&n;&t;&t;&t;    FALSE to retry.  Default is retry.  */
DECL|macro|LPSETIRQ
mdefine_line|#define LPSETIRQ 0x0605  /* call with new IRQ number,&n;&t;&t;&t;    or 0 for polling (no IRQ) */
DECL|macro|LPGETIRQ
mdefine_line|#define LPGETIRQ 0x0606  /* get the current IRQ number */
DECL|macro|LPWAIT
mdefine_line|#define LPWAIT   0x0608  /* corresponds to LP_INIT_WAIT */
DECL|macro|LPCAREFUL
mdefine_line|#define LPCAREFUL   0x0609  /* call with TRUE arg to require out-of-paper, off-&n;&t;&t;&t;    line, and error indicators good on all writes,&n;&t;&t;&t;    FALSE to ignore them.  Default is ignore. */
DECL|macro|LPABORTOPEN
mdefine_line|#define LPABORTOPEN 0x060a  /* call with TRUE arg to abort open() on error,&n;&t;&t;&t;    FALSE to ignore error.  Default is ignore.  */
DECL|macro|LPGETSTATUS
mdefine_line|#define LPGETSTATUS 0x060b  /* return LP_S(minor) */
DECL|macro|LPRESET
mdefine_line|#define LPRESET     0x060c  /* reset printer */
multiline_comment|/* timeout for printk&squot;ing a timeout, in jiffies (100ths of a second).&n;   This is also used for re-checking error conditions if LP_ABORT is&n;   not set.  This is the default behavior. */
DECL|macro|LP_TIMEOUT_INTERRUPT
mdefine_line|#define LP_TIMEOUT_INTERRUPT&t;(60 * HZ)
DECL|macro|LP_TIMEOUT_POLLED
mdefine_line|#define LP_TIMEOUT_POLLED&t;(10 * HZ)
DECL|macro|LP_BUFFER_SIZE
mdefine_line|#define LP_BUFFER_SIZE 1024 /*256*/
DECL|enum|lp_type
r_enum
id|lp_type
(brace
DECL|enumerator|LP_UNKNOWN
id|LP_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|LP_AMIGA
id|LP_AMIGA
op_assign
l_int|1
comma
DECL|enumerator|LP_ATARI
id|LP_ATARI
op_assign
l_int|2
comma
DECL|enumerator|LP_MFC
id|LP_MFC
op_assign
l_int|3
)brace
suffix:semicolon
multiline_comment|/*&n; * warning: this structure is in kernel space and has to fit in one page,&n; * i.e. must not be larger than 4k&n; */
DECL|struct|lp_struct
r_struct
id|lp_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|lp_out
r_void
(paren
op_star
id|lp_out
)paren
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*output char function*/
DECL|member|lp_is_busy
r_int
(paren
op_star
id|lp_is_busy
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|lp_has_pout
r_int
(paren
op_star
id|lp_has_pout
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|lp_is_online
r_int
(paren
op_star
id|lp_is_online
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|lp_my_interrupt
r_int
(paren
op_star
id|lp_my_interrupt
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|lp_ioctl
r_int
(paren
op_star
id|lp_ioctl
)paren
(paren
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|lp_open
r_void
(paren
op_star
id|lp_open
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for module use counter */
DECL|member|lp_release
r_void
(paren
op_star
id|lp_release
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for module use counter */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/*for BUSY... */
DECL|member|chars
r_int
r_int
id|chars
suffix:semicolon
multiline_comment|/*busy timeout */
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
multiline_comment|/*wait time */
DECL|member|wait
r_int
r_int
id|wait
suffix:semicolon
DECL|member|lp_wait_q
r_struct
id|wait_queue
op_star
id|lp_wait_q
suffix:semicolon
multiline_comment|/*strobe wait */
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
multiline_comment|/* hardware drivers internal use*/
DECL|member|type
r_enum
id|lp_type
id|type
suffix:semicolon
DECL|member|lp_buffer
r_char
id|lp_buffer
(braket
id|LP_BUFFER_SIZE
)braket
suffix:semicolon
DECL|member|do_print
r_int
id|do_print
suffix:semicolon
DECL|member|copy_size
DECL|member|bytes_written
r_int
r_int
id|copy_size
comma
id|bytes_written
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|lp_struct
op_star
id|lp_table
(braket
id|MAX_LP
)braket
suffix:semicolon
r_extern
r_int
r_int
id|lp_irq
suffix:semicolon
r_void
id|lp_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
id|lp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|register_parallel
c_func
(paren
r_struct
id|lp_struct
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|unregister_parallel
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
