macro_line|#ifndef _LINUX_LP_H
DECL|macro|_LINUX_LP_H
mdefine_line|#define _LINUX_LP_H
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * usr/include/linux/lp.h c.1991-1992 James Wiegand&n; * many modifications copyright (C) 1992 Michael K. Johnson&n; */
multiline_comment|/*&n; * caveat: my machine only has 1 printer @ lpt2 so lpt1 &amp; lpt3 are &n; * implemented but UNTESTED&n; *&n; * My machine (Michael K. Johnson) has only lpt1...  dupla caveat...&n; */
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
multiline_comment|/* timeout for each character  (This is a good case 50 Mhz computer&n;   at a poor case 10 KBS xfer rate to the printer, as best as I can&n;   tell.)  This is in instruction cycles, kinda -- it is the count&n;   in a busy loop.  THIS IS THE VALUE TO CHANGE if you have extremely&n;   slow printing, or if the machine seems to slow down a lot when you&n;   print.  If you have slow printing, increase this number and recompile,&n;   and if your system gets bogged down, decrease this number.*/
DECL|macro|LP_TIME_CHAR
mdefine_line|#define LP_TIME_CHAR 5000
multiline_comment|/* timeout for printk&squot;ing a timeout, in jiffies (100ths of a second).&n;   If your printer isn&squot;t printing at least one character every five seconds,&n;   you have worse problems than a slow printer driver and lp_timeout printed&n;   every five seconds while trying to print. */
DECL|macro|LP_TIMEOUT
mdefine_line|#define LP_TIMEOUT 5000
DECL|macro|LP_B
mdefine_line|#define LP_B(minor)&t;lp_table[(minor)].base&t;&t;/* IO address */
DECL|macro|LP_F
mdefine_line|#define LP_F(minor)&t;lp_table[(minor)].flags&t;&t;/* flags for busy, etc. */
DECL|macro|LP_S
mdefine_line|#define LP_S(minor)&t;inb(LP_B((minor)) + 1)&t;&t;/* status port */
DECL|macro|LP_C
mdefine_line|#define LP_C(minor)&t;(lp_table[(minor)].base + 2)&t;/* control port */
DECL|macro|LP_COUNT
mdefine_line|#define LP_COUNT(minor)&t;lp_table[(minor)].count&t;&t;/* last count */
DECL|macro|LP_TIME
mdefine_line|#define LP_TIME(minor)&t;lp_table[(minor)].time&t;&t;/* last time */
multiline_comment|/* &n;since we are dealing with a horribly slow device&n;I don&squot;t see the need for a queue&n;*/
DECL|struct|lp_struct
r_struct
id|lp_struct
(brace
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|time
r_int
id|time
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is the starting value for the heuristic algorithm.  If you&n; * want to tune this and have a fast printer (i.e. HPIIIP), decrease&n; * this number, and if you have a slow printer, increase this number.&n; * This is not stricly necessary, as the algorithm should be able to&n; * adapt to your printer relatively quickly.&n; * this is in hundredths of a second, the default 50 being .5 seconds.&n; */
DECL|macro|LP_INIT_TIME
mdefine_line|#define LP_INIT_TIME 50
multiline_comment|/* This is our first guess at the size of the buffer on the printer,&n; * in characters.  I am assuming a 4K buffer because most newer printers&n; * have larger ones, which will be adapted to.  At this time, it really&n; * doesn&squot;t matter, as this value isn&squot;t used.&n; */
DECL|macro|LP_INIT_COUNT
mdefine_line|#define LP_INIT_COUNT 4096
multiline_comment|/* the BIOS manuals say there can be up to 4 lpt devices&n; * but I have not seen a board where the 4th address is listed&n; * if you have different hardware change the table below &n; * please let me know if you have different equipment&n; * if you have more than 3 printers, remember to increase LP_NO&n; */
DECL|variable|lp_table
r_struct
id|lp_struct
id|lp_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x3bc
comma
l_int|0
comma
id|LP_INIT_COUNT
comma
id|LP_INIT_TIME
comma
)brace
comma
(brace
l_int|0x378
comma
l_int|0
comma
id|LP_INIT_COUNT
comma
id|LP_INIT_TIME
comma
)brace
comma
(brace
l_int|0x278
comma
l_int|0
comma
id|LP_INIT_COUNT
comma
id|LP_INIT_TIME
comma
)brace
)brace
suffix:semicolon
DECL|macro|LP_NO
mdefine_line|#define LP_NO 3
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
