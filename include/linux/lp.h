macro_line|#ifndef _LINUX_LP_H
DECL|macro|_LINUX_LP_H
mdefine_line|#define _LINUX_LP_H
multiline_comment|/*&n;$Header: /usr/src/linux/include/linux/lp.h,v 1.2 1992/01/21 23:59:24 james_r_wiegand Exp james_r_wiegand $&n;*/
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * usr/include/linux/lp.h c.1991-1992 James Wiegand&n; */
multiline_comment|/*&n; * caveat: my machine only has 1 printer @ lpt2 so lpt1 &amp; lpt3 are &n; * implemented but UNTESTED&n; */
multiline_comment|/*&n; * Per POSIX guidelines, this module reserves the LP and lp prefixes&n; */
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
DECL|macro|LP_TIMEOUT
mdefine_line|#define LP_TIMEOUT 200000
DECL|macro|LP_B
mdefine_line|#define LP_B(minor)&t;lp_table[(minor)].base
DECL|macro|LP_F
mdefine_line|#define LP_F(minor)&t;lp_table[(minor)].flags
DECL|macro|LP_S
mdefine_line|#define LP_S(minor)&t;inb(LP_B((minor)) + 1)
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
)brace
suffix:semicolon
multiline_comment|/* &n; * the BIOS manuals say there can be up to 4 lpt devices&n; * but I have not seen a board where the 4th address is listed&n; * if you have different hardware change the table below &n; * please let me know if you have different equipment&n; * if you have more than 3 printers, remember to increase LP_NO&n; */
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
)brace
comma
(brace
l_int|0x378
comma
l_int|0
comma
)brace
comma
(brace
l_int|0x278
comma
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|macro|LP_NO
mdefine_line|#define LP_NO 3
multiline_comment|/* &n; * bit defines for 8255 status port&n; * base + 1&n; */
DECL|macro|LP_PBUSY
mdefine_line|#define LP_PBUSY&t;0x80 /* active low */
DECL|macro|LP_PACK
mdefine_line|#define LP_PACK&t;&t;0x40 /* active low */
DECL|macro|LP_POUTPA
mdefine_line|#define LP_POUTPA&t;0x20
DECL|macro|LP_PSELECD
mdefine_line|#define LP_PSELECD&t;0x10
DECL|macro|LP_PERRORP
mdefine_line|#define LP_PERRORP&t;0x08 /*&#xfffd; active low*/
DECL|macro|LP_PIRQ
mdefine_line|#define LP_PIRQ&t;&t;0x04 /* active low */
multiline_comment|/* &n; * defines for 8255 control port&n; * base + 2 &n; */
DECL|macro|LP_PIRQEN
mdefine_line|#define LP_PIRQEN&t;0x10
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
multiline_comment|/*&n; * this is the port delay time. your mileage may vary&n; */
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
