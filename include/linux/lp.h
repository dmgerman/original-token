macro_line|#ifndef _LINUX_LP_H
DECL|macro|_LINUX_LP_H
mdefine_line|#define _LINUX_LP_H
multiline_comment|/*&n; * usr/include/linux/lp.h c.1991-1992 James Wiegand&n; * many modifications copyright (C) 1992 Michael K. Johnson&n; * Interrupt support added 1993 Nigel Gamble&n; */
multiline_comment|/*&n; * Per POSIX guidelines, this module reserves the LP and lp prefixes&n; * These are the lp_table[minor].flags flags...&n; */
DECL|macro|LP_EXIST
mdefine_line|#define LP_EXIST 0x0001
DECL|macro|LP_SELEC
mdefine_line|#define LP_SELEC 0x0002
DECL|macro|LP_BUSY
mdefine_line|#define LP_BUSY&t; 0x0004
DECL|macro|LP_OFFL
mdefine_line|#define LP_OFFL&t; 0x0008
DECL|macro|LP_NOPA
mdefine_line|#define LP_NOPA  0x0010
DECL|macro|LP_ERR
mdefine_line|#define LP_ERR   0x0020
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
mdefine_line|#define LP_INIT_TIME 2
multiline_comment|/* IOCTL numbers */
DECL|macro|LPCHAR
mdefine_line|#define LPCHAR   0x0001  /* corresponds to LP_INIT_CHAR */
DECL|macro|LPTIME
mdefine_line|#define LPTIME   0x0002  /* corresponds to LP_INIT_TIME */
DECL|macro|LPABORT
mdefine_line|#define LPABORT  0x0004  /* call with TRUE arg to abort on error,&n;&t;&t;&t;    FALSE to retry.  Default is retry.  */
DECL|macro|LPSETIRQ
mdefine_line|#define LPSETIRQ 0x0005  /* call with new IRQ number,&n;&t;&t;&t;    or 0 for polling (no IRQ) */
DECL|macro|LPGETIRQ
mdefine_line|#define LPGETIRQ 0x0006  /* get the current IRQ number */
DECL|macro|LPWAIT
mdefine_line|#define LPWAIT   0x0008  /* corresponds to LP_INIT_WAIT */
DECL|macro|LPCAREFUL
mdefine_line|#define LPCAREFUL   0x0009  /* call with TRUE arg to require out-of-paper, off-&n;&t;&t;&t;    line, and error indicators good on all writes,&n;&t;&t;&t;    FALSE to ignore them.  Default is ignore. */
DECL|macro|LPABORTOPEN
mdefine_line|#define LPABORTOPEN 0x000a  /* call with TRUE arg to abort open() on error,&n;&t;&t;&t;    FALSE to ignore error.  Default is ignore.  */
DECL|macro|LPGETSTATUS
mdefine_line|#define LPGETSTATUS 0x000b  /* return LP_S(minor) */
multiline_comment|/* timeout for printk&squot;ing a timeout, in jiffies (100ths of a second).&n;   This is also used for re-checking error conditions if LP_ABORT is&n;   not set.  This is the default behavior. */
DECL|macro|LP_TIMEOUT_INTERRUPT
mdefine_line|#define LP_TIMEOUT_INTERRUPT&t;(60 * HZ)
DECL|macro|LP_TIMEOUT_POLLED
mdefine_line|#define LP_TIMEOUT_POLLED&t;(10 * HZ)
DECL|macro|LP_B
mdefine_line|#define LP_B(minor)&t;lp_table[(minor)].base&t;&t;/* IO address */
DECL|macro|LP_F
mdefine_line|#define LP_F(minor)&t;lp_table[(minor)].flags&t;&t;/* flags for busy, etc. */
DECL|macro|LP_S
mdefine_line|#define LP_S(minor)&t;inb_p(LP_B((minor)) + 1)&t;/* status port */
DECL|macro|LP_C
mdefine_line|#define LP_C(minor)&t;(lp_table[(minor)].base + 2)&t;/* control port */
DECL|macro|LP_CHAR
mdefine_line|#define LP_CHAR(minor)&t;lp_table[(minor)].chars&t;&t;/* busy timeout */
DECL|macro|LP_TIME
mdefine_line|#define LP_TIME(minor)&t;lp_table[(minor)].time&t;&t;/* wait time */
DECL|macro|LP_WAIT
mdefine_line|#define LP_WAIT(minor)&t;lp_table[(minor)].wait&t;&t;/* strobe wait */
DECL|macro|LP_IRQ
mdefine_line|#define LP_IRQ(minor)&t;lp_table[(minor)].irq&t;&t;/* interrupt # */
multiline_comment|/* 0 means polled */
DECL|macro|LP_BUFFER_SIZE
mdefine_line|#define LP_BUFFER_SIZE 256
DECL|struct|lp_struct
r_struct
id|lp_struct
(brace
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|chars
r_int
r_int
id|chars
suffix:semicolon
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
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
DECL|member|lp_buffer
r_char
op_star
id|lp_buffer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * bit defines for 8255 status port&n; * base + 1&n; * accessed with LP_S(minor), which gets the byte...&n; */
DECL|macro|LP_PBUSY
mdefine_line|#define LP_PBUSY&t;0x80 /* active low */
DECL|macro|LP_PACK
mdefine_line|#define LP_PACK&t;&t;0x40 /* active low */
DECL|macro|LP_POUTPA
mdefine_line|#define LP_POUTPA&t;0x20
DECL|macro|LP_PSELECD
mdefine_line|#define LP_PSELECD&t;0x10
DECL|macro|LP_PERRORP
mdefine_line|#define LP_PERRORP&t;0x08 /* active low*/
multiline_comment|/* &n; * defines for 8255 control port&n; * base + 2 &n; * accessed with LP_C(minor)&n; */
DECL|macro|LP_PINTEN
mdefine_line|#define LP_PINTEN&t;0x10
DECL|macro|LP_PSELECP
mdefine_line|#define LP_PSELECP&t;0x08
DECL|macro|LP_PINITP
mdefine_line|#define LP_PINITP&t;0x04  /* active low */
DECL|macro|LP_PAUTOLF
mdefine_line|#define LP_PAUTOLF&t;0x02
DECL|macro|LP_PSTROBE
mdefine_line|#define LP_PSTROBE&t;0x01
multiline_comment|/* &n; * the value written to ports to test existence. PC-style ports will &n; * return the value written. AT-style ports will return 0. so why not&n; * make them the same ? &n; */
DECL|macro|LP_DUMMY
mdefine_line|#define LP_DUMMY&t;0x00
multiline_comment|/*&n; * This is the port delay time.  Your mileage may vary.&n; * It is used only in the lp_init() routine.&n; */
DECL|macro|LP_DELAY
mdefine_line|#define LP_DELAY &t;150000
multiline_comment|/*&n; * function prototypes&n; */
r_extern
r_int
id|lp_init
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
