multiline_comment|/* This is the hardware interface for newport graphics.  It&squot;s taken from&n;   IRIX.&n;&n;   Alex deVries &lt;puffin@redhat.com&gt;&n;&n;*/
macro_line|#ifndef __SYS_NG1HW_H__
DECL|macro|__SYS_NG1HW_H__
mdefine_line|#define __SYS_NG1HW_H__
macro_line|#ident &quot;$Revision: 1.1 $&quot;
DECL|macro|BIT
mdefine_line|#define BIT(n)&t;(0x1 &lt;&lt; n)
macro_line|#ifndef REX_ASMCODE
r_typedef
r_union
(brace
DECL|member|flt
r_volatile
r_float
id|flt
suffix:semicolon
DECL|member|word
r_volatile
r_int
r_int
id|word
suffix:semicolon
DECL|typedef|float_long
)brace
id|float_long
suffix:semicolon
DECL|typedef|vol_ulong
r_typedef
r_volatile
r_int
r_int
id|vol_ulong
suffix:semicolon
DECL|typedef|fixed16
r_typedef
r_volatile
r_int
r_int
id|fixed16
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|byword
id|vol_ulong
id|byword
suffix:semicolon
r_struct
(brace
DECL|member|s0
r_volatile
r_int
r_int
id|s0
suffix:semicolon
DECL|member|s1
r_volatile
r_int
r_int
id|s1
suffix:semicolon
DECL|member|byshort
)brace
id|byshort
suffix:semicolon
r_struct
(brace
DECL|member|b0
DECL|member|b1
DECL|member|b2
r_volatile
r_int
r_char
id|b0
comma
id|b1
comma
id|b2
suffix:semicolon
DECL|member|b3
r_volatile
r_int
r_char
id|b3
suffix:semicolon
DECL|member|bybyte
)brace
id|bybyte
suffix:semicolon
DECL|typedef|DCB_reg
)brace
id|DCB_reg
suffix:semicolon
macro_line|#ifndef REXSIM
DECL|struct|rex3regs
r_typedef
r_struct
id|rex3regs
(brace
multiline_comment|/* THE CHIP */
DECL|member|drawmode1
id|vol_ulong
id|drawmode1
suffix:semicolon
multiline_comment|/* extra mode bits for GL &t;0x0000 */
DECL|member|drawmode0
id|vol_ulong
id|drawmode0
suffix:semicolon
multiline_comment|/* command register &t;&t;0x0004 */
DECL|member|lsmode
id|vol_ulong
id|lsmode
suffix:semicolon
multiline_comment|/* line stipple mode&t;&t;0x0008 */
DECL|member|lspattern
id|vol_ulong
id|lspattern
suffix:semicolon
multiline_comment|/* 32 bit pixel lspattern&t;0x000c */
DECL|member|lspatsave
id|vol_ulong
id|lspatsave
suffix:semicolon
multiline_comment|/* save register for lspattern&t;0x0010 */
DECL|member|zpattern
id|vol_ulong
id|zpattern
suffix:semicolon
multiline_comment|/* 32 bit pixel zpattern&t;0x0014 */
DECL|member|colorback
id|vol_ulong
id|colorback
suffix:semicolon
multiline_comment|/* background color&t;&t;0x0018 */
DECL|member|colorvram
id|vol_ulong
id|colorvram
suffix:semicolon
multiline_comment|/* fast vram clear color&t;0x001c */
DECL|member|alpharef
id|vol_ulong
id|alpharef
suffix:semicolon
multiline_comment|/* afunction reference value&t;0x0020 */
DECL|member|pad0
id|vol_ulong
id|pad0
suffix:semicolon
multiline_comment|/* padding &t;&t;&t;0x0024 */
DECL|member|smask0x
id|vol_ulong
id|smask0x
suffix:semicolon
multiline_comment|/* screen mask 0, window rel,&t;0x0028 */
DECL|member|smask0y
id|vol_ulong
id|smask0y
suffix:semicolon
multiline_comment|/* exclusively for the GL&t;0x002c */
DECL|member|_setup
id|vol_ulong
id|_setup
suffix:semicolon
multiline_comment|/* do line/span setup, no iter  0x0030 */
DECL|member|_stepz
id|vol_ulong
id|_stepz
suffix:semicolon
multiline_comment|/* Enable ZPATTERN for this pix 0x0034 */
DECL|member|_lsrestore
id|vol_ulong
id|_lsrestore
suffix:semicolon
multiline_comment|/* Restore lspattern,count&t;0x0038 */
DECL|member|_lssave
id|vol_ulong
id|_lssave
suffix:semicolon
multiline_comment|/* Backup lspattern,count&t;0x003c */
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x100
op_minus
l_int|0x40
)braket
suffix:semicolon
DECL|member|_xstart
id|float_long
id|_xstart
suffix:semicolon
multiline_comment|/* 16.4(7) current x&t;&t;0x0100 */
DECL|member|_ystart
id|float_long
id|_ystart
suffix:semicolon
multiline_comment|/* 16.4(7) current y&t;&t;0x0104 */
DECL|member|_xend
id|float_long
id|_xend
suffix:semicolon
multiline_comment|/* 16.4(7)&t;&t;&t;0x0108 */
DECL|member|_yend
id|float_long
id|_yend
suffix:semicolon
multiline_comment|/* 16.4(7)&t;&t;&t;0x010c */
DECL|member|xsave
id|vol_ulong
id|xsave
suffix:semicolon
multiline_comment|/* 16&t;x save for blocks&t;0x0110 */
DECL|member|xymove
id|vol_ulong
id|xymove
suffix:semicolon
multiline_comment|/* x,y copy dest offset&t;&t;0x0114 */
DECL|member|bresd
id|float_long
id|bresd
suffix:semicolon
multiline_comment|/* s19.8 bres d error term&t;0x0118 */
DECL|member|bress1
id|float_long
id|bress1
suffix:semicolon
multiline_comment|/* s2.15 bres s coverage term&t;0x011c */
DECL|member|bresoctinc1
id|vol_ulong
id|bresoctinc1
suffix:semicolon
multiline_comment|/* 3(4)17.3 octant+inc1 value&t;0x0120 */
DECL|member|bresrndinc2
r_volatile
r_int
id|bresrndinc2
suffix:semicolon
multiline_comment|/* 8(3)18.3 bres inc2 value&t;0x0124 */
DECL|member|brese1
id|vol_ulong
id|brese1
suffix:semicolon
multiline_comment|/* 1.15 bres e1 (minor slope)&t;0x0128 */
DECL|member|bress2
id|vol_ulong
id|bress2
suffix:semicolon
multiline_comment|/* s18.8 bres s2 coverage term  0x012c */
DECL|member|aweight0
id|vol_ulong
id|aweight0
suffix:semicolon
multiline_comment|/* antialiasing weights&t;&t;0x0130 */
DECL|member|aweight1
id|vol_ulong
id|aweight1
suffix:semicolon
multiline_comment|/* antialiasing weights&t;&t;0x0134 */
DECL|member|xstartf
id|float_long
id|xstartf
suffix:semicolon
multiline_comment|/* 12.4(7) GL version of _xstart0x0138 */
DECL|member|ystartf
id|float_long
id|ystartf
suffix:semicolon
multiline_comment|/* 12.4(7)&t;&t;&t;0x013c */
DECL|member|xendf
id|float_long
id|xendf
suffix:semicolon
multiline_comment|/* 12.4(7)&t;&t;&t;0x0140 */
DECL|member|yendf
id|float_long
id|yendf
suffix:semicolon
multiline_comment|/* 12.4(7)&t;&t;&t;0x0144 */
DECL|member|xstarti
id|fixed16
id|xstarti
suffix:semicolon
multiline_comment|/* 16 integer format for xstart 0x0148 */
DECL|member|xendf1
id|float_long
id|xendf1
suffix:semicolon
multiline_comment|/* 12.4(7) same as xend&t;&t;0x014c */
DECL|member|xystarti
id|fixed16
id|xystarti
suffix:semicolon
multiline_comment|/* 16,16&t;&t;&t;0x0150 */
DECL|member|xyendi
id|fixed16
id|xyendi
suffix:semicolon
multiline_comment|/* 16,16&t;&t;&t;0x0154 */
DECL|member|xstartendi
id|fixed16
id|xstartendi
suffix:semicolon
multiline_comment|/* 16,16&t;&t;&t;0x0158 */
DECL|member|_pad2
r_char
id|_pad2
(braket
l_int|0x200
op_minus
l_int|0x15c
)braket
suffix:semicolon
DECL|member|colorred
id|float_long
id|colorred
suffix:semicolon
multiline_comment|/* o12.11 red (also foreground)&t;0x0200 */
DECL|member|coloralpha
id|float_long
id|coloralpha
suffix:semicolon
multiline_comment|/* o8.11 alpha&t;&t;&t;0x0204 */
DECL|member|colorgrn
id|float_long
id|colorgrn
suffix:semicolon
multiline_comment|/* o8.11 green&t;&t;&t;0x0208 */
DECL|member|colorblue
id|float_long
id|colorblue
suffix:semicolon
multiline_comment|/* o8.11 blue&t;&t;&t;0x020c */
DECL|member|slopered
id|float_long
id|slopered
suffix:semicolon
multiline_comment|/* s9.11&t;&t;&t;0x0210 */
DECL|member|slopealpha
id|float_long
id|slopealpha
suffix:semicolon
multiline_comment|/* s9.11&t;&t;&t;0x0214 */
DECL|member|slopegrn
id|float_long
id|slopegrn
suffix:semicolon
multiline_comment|/* s9.11&t;&t;&t;0x0218 */
DECL|member|slopeblue
id|float_long
id|slopeblue
suffix:semicolon
multiline_comment|/* s9.11&t;&t;&t;0x021c */
DECL|member|wrmask
id|vol_ulong
id|wrmask
suffix:semicolon
multiline_comment|/* writemask&t;&t;&t;0x0220 */
DECL|member|colori
id|vol_ulong
id|colori
suffix:semicolon
multiline_comment|/* packed bgr/ci&t;&t;0x0224 */
DECL|member|colorx
id|float_long
id|colorx
suffix:semicolon
multiline_comment|/* 12.11 red (no overflow)&t;0x0228 */
DECL|member|slopered1
id|float_long
id|slopered1
suffix:semicolon
multiline_comment|/* same as slopered&t;&t;0x022c */
DECL|member|hostrw0
id|vol_ulong
id|hostrw0
suffix:semicolon
multiline_comment|/* host PIO/DMA port (msw)&t;0x0230 */
DECL|member|hostrw1
id|vol_ulong
id|hostrw1
suffix:semicolon
multiline_comment|/* host PIO/DMA port (lsw)&t;0x0234 */
DECL|member|dcbmode
id|vol_ulong
id|dcbmode
suffix:semicolon
multiline_comment|/* display ctrl bus mode reg &t;0x0238 */
DECL|member|pad3
r_volatile
r_int
id|pad3
suffix:semicolon
multiline_comment|/* 0x023c */
DECL|member|dcbdata0
id|DCB_reg
id|dcbdata0
suffix:semicolon
multiline_comment|/* display ctrl bus port (msw)&t;0x0240 */
DECL|member|dcbdata1
id|vol_ulong
id|dcbdata1
suffix:semicolon
multiline_comment|/* display ctrl bus port (lsw)&t;0x0244 */
DECL|typedef|Rex3regs
)brace
id|Rex3regs
suffix:semicolon
DECL|struct|configregs
r_typedef
r_struct
id|configregs
(brace
DECL|member|smask1x
id|vol_ulong
id|smask1x
suffix:semicolon
multiline_comment|/* screenmask1 right,left edges 0x1300 */
DECL|member|smask1y
id|vol_ulong
id|smask1y
suffix:semicolon
multiline_comment|/* screenmask1 bottom,top edges 0x1304 */
DECL|member|smask2x
id|vol_ulong
id|smask2x
suffix:semicolon
multiline_comment|/* screenmask2 right,left edges 0x1308 */
DECL|member|smask2y
id|vol_ulong
id|smask2y
suffix:semicolon
multiline_comment|/* screenmask2 bottom,top edges 0x130c */
DECL|member|smask3x
id|vol_ulong
id|smask3x
suffix:semicolon
multiline_comment|/* screenmask3 right,left edges 0x1310 */
DECL|member|smask3y
id|vol_ulong
id|smask3y
suffix:semicolon
multiline_comment|/* screenmask3 bottom,top edges 0x1314 */
DECL|member|smask4x
id|vol_ulong
id|smask4x
suffix:semicolon
multiline_comment|/* screenmask4 right,left edges 0x1318 */
DECL|member|smask4y
id|vol_ulong
id|smask4y
suffix:semicolon
multiline_comment|/* screenmask4 bottom,top edges 0x131c */
DECL|member|topscan
id|vol_ulong
id|topscan
suffix:semicolon
multiline_comment|/* y coord of top screen line&t;0x1320 */
DECL|member|xywin
id|vol_ulong
id|xywin
suffix:semicolon
multiline_comment|/* window offset &t;&t;0x1324 */
DECL|member|clipmode
id|vol_ulong
id|clipmode
suffix:semicolon
multiline_comment|/* cid,smask settings &t;&t;0x1328 */
DECL|member|pad0
id|vol_ulong
id|pad0
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;0x132c */
DECL|member|config
id|vol_ulong
id|config
suffix:semicolon
multiline_comment|/* miscellaneous  config bits &t;0x1330 */
DECL|member|pad1
id|vol_ulong
id|pad1
suffix:semicolon
multiline_comment|/*&t;&t;&t;&t;0x1334 */
DECL|member|status
id|vol_ulong
id|status
suffix:semicolon
multiline_comment|/* chip busy, FIFO, int status  0x1338 */
multiline_comment|/* read clears interrupt status bits   */
DECL|member|ustatus
id|vol_ulong
id|ustatus
suffix:semicolon
multiline_comment|/* padding on rex rev a, &squot;read-only&squot; 0x133c */
multiline_comment|/* copy of status on rex rev b.&t;       */
DECL|member|dcbreset
id|vol_ulong
id|dcbreset
suffix:semicolon
multiline_comment|/* resets DCB and flushes BFIFO 0x1340 */
DECL|typedef|Configregs
)brace
id|Configregs
suffix:semicolon
DECL|struct|rex3chip
r_typedef
r_struct
id|rex3chip
(brace
multiline_comment|/* page 0 */
DECL|member|set
r_struct
id|rex3regs
id|set
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|_pad0
r_char
id|_pad0
(braket
l_int|0x7fc
op_minus
r_sizeof
(paren
r_struct
id|rex3regs
)paren
)braket
suffix:semicolon
DECL|member|dummy
r_volatile
r_int
r_int
id|dummy
suffix:semicolon
multiline_comment|/* 0x7fc */
DECL|member|go
r_struct
id|rex3regs
id|go
suffix:semicolon
multiline_comment|/* 0x0800 */
DECL|member|_pad1
r_char
id|_pad1
(braket
l_int|0x1300
op_minus
l_int|0x800
op_minus
r_sizeof
(paren
r_struct
id|rex3regs
)paren
)braket
suffix:semicolon
multiline_comment|/* page 1 */
r_struct
(brace
DECL|member|set
r_struct
id|configregs
id|set
suffix:semicolon
multiline_comment|/* 0x1300 */
DECL|member|_pad0
r_char
id|_pad0
(braket
l_int|0x800
op_minus
r_sizeof
(paren
r_struct
id|configregs
)paren
)braket
suffix:semicolon
DECL|member|go
r_struct
id|configregs
id|go
suffix:semicolon
multiline_comment|/* 0x1b00 */
DECL|member|p1
)brace
id|p1
suffix:semicolon
DECL|typedef|rex3Chip
DECL|typedef|Rex3chip
)brace
id|rex3Chip
comma
id|Rex3chip
suffix:semicolon
macro_line|#endif /* REX_ASMCODE */
macro_line|#endif /* REXSIM */
multiline_comment|/* Since alot of flags went away, define here as null bits&n;   and leave the code as it is for now, &n;   marking where we have to change stuff.&n;&n;   NONE of these should be defined !   - billt&n;   */
DECL|macro|LSCONTINUE
mdefine_line|#define LSCONTINUE 0
DECL|macro|SHADECONTINUE
mdefine_line|#define SHADECONTINUE 0
DECL|macro|XYCONTINUE
mdefine_line|#define XYCONTINUE 0
DECL|macro|XMAJOR
mdefine_line|#define XMAJOR 0
DECL|macro|YMAJOR
mdefine_line|#define YMAJOR 0
DECL|macro|QUADMODE
mdefine_line|#define QUADMODE 0
DECL|macro|LRQPOLY
mdefine_line|#define LRQPOLY 0
multiline_comment|/* RGBMODE, DITHER now live in DM1 */
DECL|macro|RGBMODECMD
mdefine_line|#define RGBMODECMD 0
DECL|macro|DITHER
mdefine_line|#define DITHER 0
DECL|macro|DITHERRANGE
mdefine_line|#define DITHERRANGE 0
multiline_comment|/* BLOCK is a function of ADDRMODE */
DECL|macro|BLOCK
mdefine_line|#define BLOCK 0
DECL|macro|STOPONX
mdefine_line|#define STOPONX 0
DECL|macro|STOPONY
mdefine_line|#define STOPONY 0
multiline_comment|/* COLORCOMPARE is a combo of 3 bits (&lt;, = , &gt;) */
DECL|macro|COLORCOMP
mdefine_line|#define COLORCOMP 0
multiline_comment|/* FRACTIONS are gone... */
DECL|macro|INITFRAC
mdefine_line|#define INITFRAC 0
DECL|macro|FRACTION1
mdefine_line|#define FRACTION1 0
multiline_comment|/* -- some old AUX1 junk -- */
DECL|macro|DOUBLEBUF
mdefine_line|#define DOUBLEBUF 0
DECL|macro|DBLDST0
mdefine_line|#define DBLDST0 0
DECL|macro|DBLDST1
mdefine_line|#define DBLDST1 0
DECL|macro|DBLSRC
mdefine_line|#define DBLSRC 0
DECL|macro|COLORAUX
mdefine_line|#define COLORAUX 0
multiline_comment|/* --- a couple of old cmds also only for conversion --- */
DECL|macro|REX_LDPIXEL
mdefine_line|#define REX_LDPIXEL 0x1
DECL|macro|REX_ANTIAUX
mdefine_line|#define REX_ANTIAUX 0
DECL|macro|REX_DRAW
mdefine_line|#define REX_DRAW 0
DECL|macro|LOGICSRC
mdefine_line|#define LOGICSRC 0
multiline_comment|/* --- Blech! locicops are in DM1 too! */
DECL|macro|REX_LO_ZERO
mdefine_line|#define REX_LO_ZERO REX_LO_ZERO 
DECL|macro|REX_LO_AND
mdefine_line|#define REX_LO_AND DM1_LO_AND
DECL|macro|REX_LO_ANDR
mdefine_line|#define REX_LO_ANDR DM1_LO_ANDR
DECL|macro|REX_LO_SRC
mdefine_line|#define REX_LO_SRC DM1_LO_SRC
DECL|macro|REX_LO_ANDI
mdefine_line|#define REX_LO_ANDI DM1_LO_ANDI
DECL|macro|REX_LO_DST
mdefine_line|#define REX_LO_DST DM1_LO_DST
DECL|macro|REX_LO_XOR
mdefine_line|#define REX_LO_XOR DM1_LO_XOR
DECL|macro|REX_LO_OR
mdefine_line|#define REX_LO_OR DM1_LO_OR
DECL|macro|REX_LO_NOR
mdefine_line|#define REX_LO_NOR DM1_LO_NOR
DECL|macro|REX_LO_XNOR
mdefine_line|#define REX_LO_XNOR DM1_LO_XNOR
DECL|macro|REX_LO_NDST
mdefine_line|#define REX_LO_NDST DM1_LO_NDST
DECL|macro|REX_LO_ORR
mdefine_line|#define REX_LO_ORR DM1_LO_ORR
DECL|macro|REX_LO_NSRC
mdefine_line|#define REX_LO_NSRC DM1_LO_NSRC
DECL|macro|REX_LO_ORI
mdefine_line|#define REX_LO_ORI DM1_LO_ORI
DECL|macro|REX_LO_NAND
mdefine_line|#define REX_LO_NAND DM1_LO_NAND
DECL|macro|REX_LO_ONE
mdefine_line|#define REX_LO_ONE DM1_LO_ONE
multiline_comment|/*&n; *  drawmode flags&n; */
DECL|macro|DM0_OPCODE
mdefine_line|#define DM0_OPCODE&t;0x3&t;&t;/* opcode(1:0)&t;*/
DECL|macro|DM0_NOP
macro_line|#&t;define DM0_NOP&t;&t;0x0
DECL|macro|DM0_READ
macro_line|#&t;define DM0_READ&t;&t;0x1
DECL|macro|DM0_DRAW
macro_line|#&t;define DM0_DRAW&t;&t;0x2
DECL|macro|DM0_SCR2SCR
macro_line|#&t;define DM0_SCR2SCR&t;0x3
DECL|macro|DM0_ADRMODE_SHIFT
mdefine_line|#define DM0_ADRMODE_SHIFT&t;2&t;/* adrmode(2:0)&t;*/
DECL|macro|DM0_ADRMODE
macro_line|#&t;define DM0_ADRMODE&t;(0x7&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_SPAN
macro_line|#&t;define DM0_SPAN&t;&t;(0x0&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_BLOCK
macro_line|#&t;define DM0_BLOCK&t;(0x1&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_ILINE
macro_line|#&t;define DM0_ILINE&t;(0x2&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_FLINE
macro_line|#&t;define DM0_FLINE&t;(0x3&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_ALINE
macro_line|#&t;define DM0_ALINE&t;(0x4&lt;&lt;DM0_ADRMODE_SHIFT)
macro_line|#ifdef OLDJUNK
multiline_comment|/* XXX These definitions are obsolete */
DECL|macro|DM0_AELINE
macro_line|#&t;define DM0_AELINE&t;(0x5&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_ACWEDGE
macro_line|#&t;define DM0_ACWEDGE&t;(0x6&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_ACCWEDGE
macro_line|#&t;define DM0_ACCWEDGE&t;(0x7&lt;&lt;DM0_ADRMODE_SHIFT)
macro_line|#else
multiline_comment|/* XXX These are according to 11/2/92 spec */
DECL|macro|DM0_TLINE
macro_line|#       define DM0_TLINE        (0x5&lt;&lt;DM0_ADRMODE_SHIFT)
DECL|macro|DM0_BLINE
macro_line|#       define DM0_BLINE        (0x6&lt;&lt;DM0_ADRMODE_SHIFT)
macro_line|#endif /* OLDJUNK */
DECL|macro|DM0_DOSETUP
mdefine_line|#define DM0_DOSETUP&t;BIT(5)
DECL|macro|DM0_COLORHOST
mdefine_line|#define DM0_COLORHOST&t;BIT(6)
DECL|macro|DM0_ALPHAHOST
mdefine_line|#define DM0_ALPHAHOST&t;BIT(7)
DECL|macro|DM0_STOPONX
mdefine_line|#define DM0_STOPONX&t;BIT(8)
DECL|macro|DM0_STOPONY
mdefine_line|#define DM0_STOPONY&t;BIT(9)
DECL|macro|DM0_STOPONXY
mdefine_line|#define DM0_STOPONXY&t;(DM0_STOPONX | DM0_STOPONY)
DECL|macro|DM0_SKIPFIRST
mdefine_line|#define DM0_SKIPFIRST&t;BIT(10)
DECL|macro|DM0_SKIPLAST
mdefine_line|#define DM0_SKIPLAST&t;BIT(11)
DECL|macro|DM0_ENZPATTERN
mdefine_line|#define DM0_ENZPATTERN&t;BIT(12)
DECL|macro|DM0_ENLSPATTERN
mdefine_line|#define DM0_ENLSPATTERN&t;BIT(13)
DECL|macro|DM0_LSADVLAST
mdefine_line|#define DM0_LSADVLAST&t;BIT(14)
DECL|macro|DM0_LENGTH32
mdefine_line|#define DM0_LENGTH32&t;BIT(15)
DECL|macro|DM0_ZOPAQUE
mdefine_line|#define DM0_ZOPAQUE&t;BIT(16)
DECL|macro|DM0_LSOPAQUE
mdefine_line|#define DM0_LSOPAQUE&t;BIT(17)
DECL|macro|DM0_SHADE
mdefine_line|#define DM0_SHADE&t;BIT(18)
DECL|macro|DM0_LRONLY
mdefine_line|#define DM0_LRONLY&t;BIT(19)
macro_line|#ifdef OLDJUNK
multiline_comment|/* XXX These definitions are obsolete */
DECL|macro|DM0_CICLAMP
mdefine_line|#define DM0_CICLAMP     BIT(20)
DECL|macro|DM0_ENDPTFILTER
mdefine_line|#define DM0_ENDPTFILTER BIT(21)
macro_line|#else
multiline_comment|/* XXX These are according to 11/2/92 spec */
DECL|macro|DM0_XYOFFSET
mdefine_line|#define DM0_XYOFFSET    BIT(20)
DECL|macro|DM0_CICLAMP
mdefine_line|#define DM0_CICLAMP     BIT(21)
DECL|macro|DM0_ENDPTFILTER
mdefine_line|#define DM0_ENDPTFILTER BIT(22)
macro_line|#endif&t;/* OLDJUNK */
multiline_comment|/* New Feature in REX REV B */
DECL|macro|DM0_YSTRIDE
mdefine_line|#define&t;DM0_YSTRIDE&t;BIT(23)
DECL|macro|DM1_PLANES_SHIFT
mdefine_line|#define DM1_PLANES_SHIFT&t;0
DECL|macro|DM1_PLANES
mdefine_line|#define DM1_PLANES&t;0x7&t;&t;/* planes(2:0)&t;*/
DECL|macro|DM1_NOPLANES
macro_line|#&t;define DM1_NOPLANES&t;0x0
DECL|macro|DM1_RGBPLANES
macro_line|#&t;define DM1_RGBPLANES&t;0x1
DECL|macro|DM1_RGBAPLANES
macro_line|#&t;define DM1_RGBAPLANES&t;0x2
DECL|macro|DM1_OLAYPLANES
macro_line|#&t;define DM1_OLAYPLANES&t;0x4
DECL|macro|DM1_PUPPLANES
macro_line|#&t;define DM1_PUPPLANES&t;0x5
DECL|macro|DM1_CIDPLANES
macro_line|#&t;define DM1_CIDPLANES&t;0x6
DECL|macro|DM1_DRAWDEPTH_SHIFT
mdefine_line|#define DM1_DRAWDEPTH_SHIFT&t;3&t;/* drawdepth(1:0)&t;*/
DECL|macro|DM1_DRAWDEPTH_MASK
mdefine_line|#define DM1_DRAWDEPTH_MASK      (3 &lt;&lt; DM1_DRAWDEPTH_SHIFT)
DECL|macro|DM1_DRAWDEPTH
macro_line|#&t;define DM1_DRAWDEPTH&t;(0x3 &lt;&lt; DM1_DRAWDEPTH_SHIFT)&t;
DECL|macro|DM1_DRAWDEPTH4
macro_line|#&t;define DM1_DRAWDEPTH4&t;(0x0 &lt;&lt; DM1_DRAWDEPTH_SHIFT)
DECL|macro|DM1_DRAWDEPTH8
macro_line|#&t;define DM1_DRAWDEPTH8&t;(0x1 &lt;&lt; DM1_DRAWDEPTH_SHIFT)
DECL|macro|DM1_DRAWDEPTH12
macro_line|#&t;define DM1_DRAWDEPTH12&t;(0x2 &lt;&lt; DM1_DRAWDEPTH_SHIFT)
DECL|macro|DM1_DRAWDEPTH24
macro_line|#&t;define DM1_DRAWDEPTH24&t;(0x3 &lt;&lt; DM1_DRAWDEPTH_SHIFT)
DECL|macro|DM1_DBLSRC
mdefine_line|#define DM1_DBLSRC&t;&t;BIT(5)
DECL|macro|DM1_YFLIP
mdefine_line|#define DM1_YFLIP&t;&t;BIT(6)
DECL|macro|DM1_RWPACKED
mdefine_line|#define DM1_RWPACKED&t;&t;BIT(7)
DECL|macro|DM1_HOSTDEPTH_SHIFT
mdefine_line|#define DM1_HOSTDEPTH_SHIFT &t;8&t;/* hostdepth(1:0)&t;*/
DECL|macro|DM1_HOSTDEPTH_MASK
mdefine_line|#define DM1_HOSTDEPTH_MASK      (3 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_HOSTDEPTH
macro_line|#&t;define DM1_HOSTDEPTH&t;(0x3 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_HOSTDEPTH4
macro_line|#&t;define DM1_HOSTDEPTH4&t;(0x0 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_HOSTDEPTH8
macro_line|#&t;define DM1_HOSTDEPTH8&t;(0x1 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_HOSTDEPTH12
macro_line|#&t;define DM1_HOSTDEPTH12&t;(0x2 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_HOSTDEPTH32
macro_line|#&t;define DM1_HOSTDEPTH32&t;(0x3 &lt;&lt; DM1_HOSTDEPTH_SHIFT)
DECL|macro|DM1_RWDOUBLE
mdefine_line|#define DM1_RWDOUBLE&t;&t;BIT(10)
DECL|macro|DM1_SWAPENDIAN
mdefine_line|#define DM1_SWAPENDIAN&t;&t;BIT(11)
DECL|macro|DM1_COLORCOMPARE_SHIFT
mdefine_line|#define DM1_COLORCOMPARE_SHIFT  12&t;/* compare (2:0)&t;*/
DECL|macro|DM1_COLORCOMPARE_MASK
mdefine_line|#define DM1_COLORCOMPARE_MASK  (7 &lt;&lt; DM1_COLORCOMPARE_SHIFT)
DECL|macro|DM1_COLORCOMPARE
macro_line|#&t;define DM1_COLORCOMPARE (0x7 &lt;&lt; DM1_COLORCOMPARE_SHIFT)
DECL|macro|DM1_COLORCOMPLT
macro_line|#&t;define DM1_COLORCOMPLT&t;BIT(12)
DECL|macro|DM1_COLORCOMPEQ
macro_line|#&t;define DM1_COLORCOMPEQ&t;BIT(13)
DECL|macro|DM1_COLORCOMPGT
macro_line|#&t;define DM1_COLORCOMPGT&t;BIT(14)
DECL|macro|DM1_RGBMODE
mdefine_line|#define DM1_RGBMODE&t;&t;BIT(15)
DECL|macro|DM1_ENDITHER
mdefine_line|#define DM1_ENDITHER&t;&t;BIT(16)
DECL|macro|DM1_FASTCLEAR
mdefine_line|#define DM1_FASTCLEAR&t;&t;BIT(17)
DECL|macro|DM1_ENBLEND
mdefine_line|#define DM1_ENBLEND&t;&t;BIT(18)
DECL|macro|DM1_SF_SHIFT
mdefine_line|#define DM1_SF_SHIFT&t;&t;19&t;/* sfactor(2:0)&t;*/
DECL|macro|DM1_SF_MASK
mdefine_line|#define DM1_SF_MASK   &t;&t;(7 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF
macro_line|#&t;define DM1_SF&t;&t;(0x7 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_ZERO
macro_line|#&t;define DM1_SF_ZERO&t;(0x0 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_ONE
macro_line|#&t;define DM1_SF_ONE&t;(0x1 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_DC
macro_line|#&t;define DM1_SF_DC&t;(0x2 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_MDC
macro_line|#&t;define DM1_SF_MDC&t;(0x3 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_SA
macro_line|#&t;define DM1_SF_SA&t;(0x4 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_SF_MSA
macro_line|#&t;define DM1_SF_MSA&t;(0x5 &lt;&lt; DM1_SF_SHIFT)
DECL|macro|DM1_DF_SHIFT
mdefine_line|#define DM1_DF_SHIFT&t;&t;22&t;/* dfactor(2:0)&t;*/
DECL|macro|DM1_DF_MASK
mdefine_line|#define DM1_DF_MASK     (7 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF
macro_line|#&t;define DM1_DF&t;&t;(0x7 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_ZERO
macro_line|#&t;define DM1_DF_ZERO&t;(0x0 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_ONE
macro_line|#&t;define DM1_DF_ONE&t;(0x1 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_SC
macro_line|#&t;define DM1_DF_SC&t;(0x2 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_MSC
macro_line|#&t;define DM1_DF_MSC&t;(0x3 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_SA
macro_line|#&t;define DM1_DF_SA&t;(0x4 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_DF_MSA
macro_line|#&t;define DM1_DF_MSA&t;(0x5 &lt;&lt; DM1_DF_SHIFT)
DECL|macro|DM1_ENBACKBLEND
mdefine_line|#define DM1_ENBACKBLEND&t;&t;BIT(25)
DECL|macro|DM1_ENPREFETCH
mdefine_line|#define DM1_ENPREFETCH&t;&t;BIT(26)
DECL|macro|DM1_BLENDALPHA
mdefine_line|#define DM1_BLENDALPHA&t;&t;BIT(27)
DECL|macro|DM1_LO_SHIFT
mdefine_line|#define DM1_LO_SHIFT&t;&t;28&t;/* logicop(3:0)&t;*/
DECL|macro|DM1_LO
macro_line|#&t;define DM1_LO&t;&t;(0xF &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_MASK
macro_line|#       define DM1_LO_MASK      DM1_LO
DECL|macro|DM1_LO_ZERO
macro_line|#&t;define DM1_LO_ZERO&t;(0x0 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_AND
macro_line|#&t;define DM1_LO_AND&t;(0x1 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_ANDR
macro_line|#&t;define DM1_LO_ANDR&t;(0x2 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_SRC
macro_line|#&t;define DM1_LO_SRC&t;(0x3 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_ANDI
macro_line|#&t;define DM1_LO_ANDI&t;(0x4 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_DST
macro_line|#&t;define DM1_LO_DST&t;(0x5 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_XOR
macro_line|#&t;define DM1_LO_XOR&t;(0x6 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_OR
macro_line|#&t;define DM1_LO_OR&t;(0x7 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_NOR
macro_line|#&t;define DM1_LO_NOR&t;(0x8 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_XNOR
macro_line|#&t;define DM1_LO_XNOR&t;(0x9 &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_NDST
macro_line|#&t;define DM1_LO_NDST&t;(0xa &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_ORR
macro_line|#&t;define DM1_LO_ORR&t;(0xb &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_NSRC
macro_line|#&t;define DM1_LO_NSRC&t;(0xc &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_ORI
macro_line|#&t;define DM1_LO_ORI&t;(0xd &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_NAND
macro_line|#&t;define DM1_LO_NAND&t;(0xe &lt;&lt; DM1_LO_SHIFT)
DECL|macro|DM1_LO_ONE
macro_line|#&t;define DM1_LO_ONE&t;(0xf &lt;&lt; DM1_LO_SHIFT)
multiline_comment|/*&n; * Clipmode register bits&n; */
DECL|macro|SMASK0
mdefine_line|#define SMASK0&t;BIT(0)
DECL|macro|SMASK1
mdefine_line|#define SMASK1&t;BIT(1)
DECL|macro|SMASK2
mdefine_line|#define SMASK2&t;BIT(2)
DECL|macro|SMASK3
mdefine_line|#define SMASK3&t;BIT(3)
DECL|macro|SMASK4
mdefine_line|#define SMASK4&t;BIT(4)
DECL|macro|ALL_SMASKS
mdefine_line|#define ALL_SMASKS&t;31
DECL|macro|CM_CIDMATCH_SHIFT
mdefine_line|#define CM_CIDMATCH_SHIFT       9
DECL|macro|CM_CIDMATCH_MASK
mdefine_line|#define CM_CIDMATCH_MASK        (0xf &lt;&lt; CM_CIDMATCH_SHIFT)
multiline_comment|/*&n; * Status register bits&n; */
DECL|macro|REX3VERSION_MASK
mdefine_line|#define REX3VERSION_MASK 7
DECL|macro|GFXBUSY
mdefine_line|#define GFXBUSY         BIT(3)
DECL|macro|BACKBUSY
mdefine_line|#define BACKBUSY        BIT(4)
DECL|macro|VRINT
mdefine_line|#define VRINT           BIT(5)
DECL|macro|VIDEOINT
mdefine_line|#define VIDEOINT        BIT(6)
DECL|macro|GFIFO_LEVEL_SHIFT
mdefine_line|#define GFIFO_LEVEL_SHIFT       7
DECL|macro|GFIFO_LEVEL_MASK
mdefine_line|#define GFIFO_LEVEL_MASK        (0x3f &lt;&lt; GFIFO_LEVEL_SHIFT)
DECL|macro|BFIFO_LEVEL_SHIFT
mdefine_line|#define BFIFO_LEVEL_SHIFT       13
DECL|macro|BFIFO_LEVEL_MASK
mdefine_line|#define BFIFO_LEVEL_MASK        (0x1f &lt;&lt; BFIFO_LEVEL_SHIFT)
DECL|macro|BFIFO_INT
mdefine_line|#define BFIFO_INT        BIT(18)
DECL|macro|GFIFO_INT
mdefine_line|#define GFIFO_INT        BIT(19)
multiline_comment|/*&n; * Config register bits&n; */
DECL|macro|GIO32MODE
mdefine_line|#define GIO32MODE       BIT(0)
DECL|macro|BUSWIDTH
mdefine_line|#define BUSWIDTH        BIT(1)
DECL|macro|EXTREGXCVR
mdefine_line|#define EXTREGXCVR      BIT(2)
DECL|macro|BFIFODEPTH_SHIFT
mdefine_line|#define BFIFODEPTH_SHIFT        3
DECL|macro|BFIFODEPTH_MASK
mdefine_line|#define BFIFODEPTH_MASK         (0xf &lt;&lt; BFIFODEPTH_SHIFT)
DECL|macro|BFIFOABOVEINT
mdefine_line|#define BFIFOABOVEINT   BIT(7)
DECL|macro|GFIFODEPTH_SHIFT
mdefine_line|#define GFIFODEPTH_SHIFT        8
DECL|macro|GFIFODEPTH_MASK
mdefine_line|#define GFIFODEPTH_MASK         (0x1f &lt;&lt; GFIFODEPTH_SHIFT)
DECL|macro|GFIFOABOVEINT
mdefine_line|#define GFIFOABOVEINT   BIT(13)
DECL|macro|TIMEOUT_SHIFT
mdefine_line|#define TIMEOUT_SHIFT   14
DECL|macro|TIMEOUT_MASK
mdefine_line|#define TIMEOUT_MASK    (7 &lt;&lt; TIMEOUT_SHIFT)
DECL|macro|VREFRESH_SHIFT
mdefine_line|#define VREFRESH_SHIFT  17
DECL|macro|VREFRESH_MASK
mdefine_line|#define VREFRESH_MASK   (0x7 &lt;&lt; VREFRESH_SHIFT)
DECL|macro|FB_TYPE
mdefine_line|#define FB_TYPE         BIT(20)
multiline_comment|/*&n; * Display Control Bus (DCB) macros&n; */
DECL|macro|DCB_DATAWIDTH_MASK
mdefine_line|#define DCB_DATAWIDTH_MASK  (0x3)
DECL|macro|DCB_ENDATAPACK
mdefine_line|#define DCB_ENDATAPACK      BIT(2)
DECL|macro|DCB_ENCRSINC
mdefine_line|#define DCB_ENCRSINC        BIT(3)
DECL|macro|DCB_CRS_SHIFT
mdefine_line|#define DCB_CRS_SHIFT    4
DECL|macro|DCB_CRS_MASK
mdefine_line|#define DCB_CRS_MASK     (0x7 &lt;&lt; DCB_CRS_SHIFT)
DECL|macro|DCB_ADDR_SHIFT
mdefine_line|#define DCB_ADDR_SHIFT   7
DECL|macro|DCB_ADDR_MASK
mdefine_line|#define DCB_ADDR_MASK    (0xf &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_ENSYNCACK
mdefine_line|#define DCB_ENSYNCACK       BIT(11)
DECL|macro|DCB_ENASYNCACK
mdefine_line|#define DCB_ENASYNCACK      BIT(12)
DECL|macro|DCB_CSWIDTH_SHIFT
mdefine_line|#define DCB_CSWIDTH_SHIFT   13
DECL|macro|DCB_CSWIDTH_MASK
mdefine_line|#define DCB_CSWIDTH_MASK    (0x1f &lt;&lt; CSWIDTH_SHIFT)
DECL|macro|DCB_CSHOLD_SHIFT
mdefine_line|#define DCB_CSHOLD_SHIFT    18
DECL|macro|DCB_CSHOLD_MASK
mdefine_line|#define DCB_CSHOLD_MASK     (0x1f &lt;&lt; CSHOLD_SHIFT)
DECL|macro|DCB_CSSETUP_SHIFT
mdefine_line|#define DCB_CSSETUP_SHIFT   23
DECL|macro|DCB_CSSETUP_MASK
mdefine_line|#define DCB_CSSETUP_MASK    (0x1f &lt;&lt; CSSETUP_SHIFT)
DECL|macro|DCB_SWAPENDIAN
mdefine_line|#define DCB_SWAPENDIAN      BIT(28)
multiline_comment|/*&n; * Some values for DCBMODE fields&n; */
DECL|macro|DCB_DATAWIDTH_4
mdefine_line|#define DCB_DATAWIDTH_4&t;&t;0x0
DECL|macro|DCB_DATAWIDTH_1
mdefine_line|#define DCB_DATAWIDTH_1&t;&t;0x1
DECL|macro|DCB_DATAWIDTH_2
mdefine_line|#define DCB_DATAWIDTH_2&t;&t;0x2
DECL|macro|DCB_DATAWIDTH_3
mdefine_line|#define DCB_DATAWIDTH_3&t;&t;0x3
multiline_comment|/*&n; * DCB_ADDR values to select the various dcb slave devices&n; */
DECL|macro|DCB_VC2
mdefine_line|#define DCB_VC2          (0 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP_ALL
mdefine_line|#define DCB_CMAP_ALL     (1 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP0
mdefine_line|#define DCB_CMAP0        (2 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_CMAP1
mdefine_line|#define DCB_CMAP1        (3 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP_ALL
mdefine_line|#define DCB_XMAP_ALL     (4 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP0
mdefine_line|#define DCB_XMAP0        (5 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_XMAP1
mdefine_line|#define DCB_XMAP1        (6 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_BT445
mdefine_line|#define DCB_BT445        (7 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_VCC1
mdefine_line|#define DCB_VCC1         (8 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_VAB1
mdefine_line|#define DCB_VAB1         (9 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_LG3_BDVERS0
mdefine_line|#define DCB_LG3_BDVERS0      (10 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_LG3_ICS1562
mdefine_line|#define DCB_LG3_ICS1562      (11 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_RESERVED
mdefine_line|#define DCB_RESERVED     (15 &lt;&lt; DCB_ADDR_SHIFT)
multiline_comment|/*&n; * New DCB Addresses which are used in (new) Indigo2 Video and Galileo 1.5&n; * since these boards have to work with Mardi Gras also. Yet, these&n; * are not necessarily the MGRAS address, these translate to the Mardi Gras&n; * addresses when the lower 2 bits are swapped (which will happen on &n; * the Newport to new video board flex cable).&n; */
DECL|macro|DCB_VAB1_NEW
mdefine_line|#define DCB_VAB1_NEW     (9 &lt;&lt; DCB_ADDR_SHIFT)
multiline_comment|/*&n; * While the Presenter is currently using address 12 and&n; * conflicting with the CC1, it has been changed for Mardi Gras&n; * To use the new video boards with Newport (an unreleased product)&n; * the presenter probe must be disabled by changing the presenter&n; * DCB address in gfx/kern/sys/pcd.h (and possibly&n; * lotus/stand/arcs/lib/libsk/graphics/NEWPORT/pcd.h), so &n; * it is probed at address 11.  This will of course not work with&n; * the presenter card but it will allow you to test new video&n; * boards will Newport&n; */
DECL|macro|DCB_VCC1_NEW
mdefine_line|#define DCB_VCC1_NEW     (12 &lt;&lt; DCB_ADDR_SHIFT)
multiline_comment|/*#define DCB_VCC1_NEW     (8 &lt;&lt; DCB_ADDR_SHIFT)*/
multiline_comment|/*&n; * Addresses being used for Galileo 1.5.&n; */
DECL|macro|DCB_VCC1_GAL
mdefine_line|#define DCB_VCC1_GAL     (8 &lt;&lt; DCB_ADDR_SHIFT) /* was 12 and will return */
DECL|macro|DCB_VAB1_GAL
mdefine_line|#define DCB_VAB1_GAL     (9 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_TMI_CSC
mdefine_line|#define DCB_TMI_CSC      (13 &lt;&lt; DCB_ADDR_SHIFT)
DECL|macro|DCB_GAL
mdefine_line|#define DCB_GAL          (14 &lt;&lt; DCB_ADDR_SHIFT)
multiline_comment|/*&n; * LG3 - (Newport for Fullhouse) board defines&n; */
multiline_comment|/* Version 0 register */
DECL|macro|LG3_VC2_UNRESET
mdefine_line|#define LG3_VC2_UNRESET BIT(0)
DECL|macro|LG3_GFX_UNRESET
mdefine_line|#define&t;LG3_GFX_UNRESET&t;BIT(1)
DECL|macro|LG3_PLL_UNRESET
mdefine_line|#define LG3_PLL_UNRESET BIT(2)
DECL|macro|LG3_DLHD_MASTER
mdefine_line|#define LG3_DLHD_MASTER BIT(3)
DECL|macro|LG3_BDVERS_PROTOCOL
mdefine_line|#define LG3_BDVERS_PROTOCOL ((2 &lt;&lt; DCB_CSWIDTH_SHIFT) | (1 &lt;&lt; DCB_CSHOLD_SHIFT) | (1 &lt;&lt; DCB_CSSETUP_SHIFT))
DECL|macro|lg3BdVersGet
mdefine_line|#define lg3BdVersGet(rex3, data)&t;&t;&t; &t;&t;&bslash;&n;        rex3-&gt;set.dcbmode = DCB_LG3_BDVERS0 | &bslash;&n;&t;&t;LG3_BDVERS_PROTOCOL | DCB_DATAWIDTH_1 ;&t;&t;&t;&bslash;&n;        data = rex3-&gt;set.dcbdata0.bybyte.b3
DECL|macro|lg3BdVersSet
mdefine_line|#define lg3BdVersSet(rex3, data)&t;&t;&t; &t;&t;&bslash;&n;        rex3-&gt;set.dcbmode = DCB_LG3_BDVERS0 | &bslash;&n;&t;&t;LG3_BDVERS_PROTOCOL | DCB_DATAWIDTH_1 ;&t;&t;&bslash;&n;&t;rex3-&gt;set.dcbdata0.bybyte.b3 = (data)
DECL|macro|Ics1562Set
mdefine_line|#define Ics1562Set(rex3, data)&t;&t;&t; &t;&t;&bslash;&n;        rex3-&gt;set.dcbmode = DCB_LG3_ICS1562 | LG3_BDVERS_PROTOCOL | DCB_DATAWIDTH_1 ; &bslash;&n;&t;rex3-&gt;set.dcbdata0.bybyte.b3 = (data)
DECL|macro|LG3_BD_001
mdefine_line|#define&t;LG3_BD_001&t;0x7
DECL|macro|LG3_BD_002
mdefine_line|#define&t;LG3_BD_002&t;0x0
multiline_comment|/*&n; * Lsmode register bits&n; */
DECL|macro|LSRCOUNT_SHIFT
mdefine_line|#define LSRCOUNT_SHIFT  0
DECL|macro|LSRCOUNT_MASK
mdefine_line|#define LSRCOUNT_MASK   (0xff &lt;&lt; LSRCOUNT_SHIFT)
DECL|macro|LSREPEAT_SHIFT
mdefine_line|#define LSREPEAT_SHIFT  8
DECL|macro|LSREPEAT_MASK
mdefine_line|#define LSREPEAT_MASK   (0xff &lt;&lt; LSREPEAT_SHIFT)
DECL|macro|LSRCNTSAVE_SHIFT
mdefine_line|#define LSRCNTSAVE_SHIFT        16
DECL|macro|LSRCNTSAVE_MASK
mdefine_line|#define LSRCNTSAVE_MASK (0xff &lt;&lt; LSRCNTSAVE_SHIFT)
DECL|macro|LSLENGTH_SHIFT
mdefine_line|#define LSLENGTH_SHIFT  24
DECL|macro|LSLENGTH_MASK
mdefine_line|#define LSLENGTH_MASK   (0xf &lt;&lt; LSLENGTH_SHIFT)
macro_line|#if&t;defined ( _KERNEL ) &amp;&amp; defined ( REX3_RUNTIME_REV_CHECK )
r_extern
r_void
id|_newport_poll_status
(paren
r_register
r_struct
id|rex3chip
op_star
comma
r_register
r_int
)paren
suffix:semicolon
DECL|macro|REX3WAIT
mdefine_line|#define REX3WAIT(rex3)  _newport_poll_status (rex3, GFXBUSY)
DECL|macro|BFIFOWAIT
mdefine_line|#define BFIFOWAIT(rex3)  _newport_poll_status (rex3, BACKBUSY)
macro_line|#else
multiline_comment|/* XXX  When we drop support for rex rev b,&n; * change status to ustatus in the macros below.&n; */
DECL|macro|REX3WAIT
mdefine_line|#define REX3WAIT(rex3)  while ((rex3)-&gt;p1.set.status &amp; GFXBUSY)
DECL|macro|BFIFOWAIT
mdefine_line|#define BFIFOWAIT(rex3)  while ((rex3)-&gt;p1.set.status &amp; BACKBUSY)
macro_line|#endif
multiline_comment|/*&n; * Legal GIO bus addresses for Newport graphics boards.&n; */
DECL|macro|REX3_GIO_ADDR_0
mdefine_line|#define REX3_GIO_ADDR_0         0x1f0f0000
DECL|macro|REX3_GIO_ADDR_1
mdefine_line|#define REX3_GIO_ADDR_1         0x1f4f0000
DECL|macro|REX3_GIO_ADDR_2
mdefine_line|#define REX3_GIO_ADDR_2         0x1f8f0000
DECL|macro|REX3_GIO_ADDR_3
mdefine_line|#define REX3_GIO_ADDR_3         0x1fcf0000
DECL|macro|NG1_XSIZE
mdefine_line|#define NG1_XSIZE       1280    /* screen size in x */
DECL|macro|NG1_YSIZE
mdefine_line|#define NG1_YSIZE       1024    /* screen size in y */
multiline_comment|/*&n; * XXX Correct values TBD.  Depends on video timing&n; */
DECL|macro|CURSOR_XOFF
mdefine_line|#define CURSOR_XOFF 29
DECL|macro|CURSOR_YOFF
mdefine_line|#define CURSOR_YOFF 31
macro_line|#ifdef _STANDALONE
r_struct
id|rex3chip
suffix:semicolon
r_struct
id|ng1_info
suffix:semicolon
r_void
id|Ng1RegisterInit
c_func
(paren
r_struct
id|rex3chip
op_star
comma
r_struct
id|ng1_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ng1checkboard
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|vc2LoadSRAM
c_func
(paren
r_struct
id|rex3chip
op_star
comma
r_int
r_int
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __SYS_NG1HW_H__ */
eof
