multiline_comment|/* $Id: parport_ll_io.h,v 1.1.2.1 1997/03/26 13:01:09 phil Exp $ &n; * David Campbell&squot;s &quot;favourite IO routines&quot; for parallel ports&n; */
DECL|macro|r_dtr
mdefine_line|#define r_dtr(x)&t;inb((x)-&gt;base)
DECL|macro|r_str
mdefine_line|#define r_str(x)&t;inb((x)-&gt;base+1)
DECL|macro|r_ctr
mdefine_line|#define r_ctr(x)&t;inb((x)-&gt;base+2)
DECL|macro|r_epp
mdefine_line|#define r_epp(x)&t;inb((x)-&gt;base+4)
DECL|macro|r_fifo
mdefine_line|#define r_fifo(x)&t;inb((x)-&gt;base+0x400)
DECL|macro|r_ecr
mdefine_line|#define r_ecr(x)&t;inb((x)-&gt;base+0x402)
DECL|macro|r_cnfgA
mdefine_line|#define r_cnfgA(x)&t;inb((x)-&gt;base+0x400)
DECL|macro|r_cnfgB
mdefine_line|#define r_cnfgB(x)&t;inb((x)-&gt;base+0x401)
DECL|macro|w_dtr
mdefine_line|#define w_dtr(x,y)&t;outb((y), (x)-&gt;base)
DECL|macro|w_str
mdefine_line|#define w_str(x,y)&t;outb((y), (x)-&gt;base+1)
DECL|macro|w_ctr
mdefine_line|#define w_ctr(x,y)&t;outb((y), (x)-&gt;base+2)
DECL|macro|w_epp
mdefine_line|#define w_epp(x,y)&t;outb((y), (x)-&gt;base+4)
DECL|macro|w_fifo
mdefine_line|#define w_fifo(x,y)&t;outb((y), (x)-&gt;base+0x400)
DECL|macro|w_ecr
mdefine_line|#define w_ecr(x,y)&t;outb((y), (x)-&gt;base+0x402)
DECL|macro|w_cnfgA
mdefine_line|#define w_cnfgA(x,y)&t;outb((y), (x)-&gt;base+0x400)
DECL|macro|w_cnfgB
mdefine_line|#define w_cnfgB(x,y)&t;outb((y), (x)-&gt;base+0x401)
eof
