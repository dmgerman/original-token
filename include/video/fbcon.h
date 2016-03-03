multiline_comment|/*&n; *  linux/drivers/video/fbcon.h -- Low level frame buffer based console driver&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _VIDEO_FBCON_H
DECL|macro|_VIDEO_FBCON_H
mdefine_line|#define _VIDEO_FBCON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/vt_buffer.h&gt;
multiline_comment|/*                                  &n;     *  `switch&squot; for the Low Level Operations&n;     */
DECL|struct|display_switch
r_struct
id|display_switch
(brace
DECL|member|setup
r_void
(paren
op_star
id|setup
)paren
(paren
r_struct
id|display
op_star
id|p
)paren
suffix:semicolon
DECL|member|bmove
r_void
(paren
op_star
id|bmove
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
multiline_comment|/* for clear, conp may be NULL, which means use a blanking (black) color */
DECL|member|clear
r_void
(paren
op_star
id|clear
)paren
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
suffix:semicolon
DECL|member|putc
r_void
(paren
op_star
id|putc
)paren
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
DECL|member|putcs
r_void
(paren
op_star
id|putcs
)paren
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
)paren
suffix:semicolon
DECL|member|revc
r_void
(paren
op_star
id|revc
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
suffix:semicolon
DECL|member|cursor
r_void
(paren
op_star
id|cursor
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|xx
comma
r_int
id|yy
)paren
suffix:semicolon
DECL|member|set_font
r_int
(paren
op_star
id|set_font
)paren
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|width
comma
r_int
id|height
)paren
suffix:semicolon
DECL|member|clear_margins
r_void
(paren
op_star
id|clear_margins
)paren
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|bottom_only
)paren
suffix:semicolon
DECL|member|fontwidthmask
r_int
r_int
id|fontwidthmask
suffix:semicolon
multiline_comment|/* 1 at (1 &lt;&lt; (width - 1)) if width is supported */
)brace
suffix:semicolon
r_extern
r_struct
id|display_switch
id|fbcon_dummy
suffix:semicolon
DECL|macro|fontheight
mdefine_line|#define fontheight(p) ((p)-&gt;_fontheight)
DECL|macro|fontheightlog
mdefine_line|#define fontheightlog(p) ((p)-&gt;_fontheightlog)
macro_line|#ifdef CONFIG_FBCON_FONTWIDTH8_ONLY
multiline_comment|/* fontwidth w is supported by dispsw */
DECL|macro|FONTWIDTH
mdefine_line|#define FONTWIDTH(w)&t;(1 &lt;&lt; ((8) - 1))
multiline_comment|/* fontwidths w1-w2 inclusive are supported by dispsw */
DECL|macro|FONTWIDTHRANGE
mdefine_line|#define FONTWIDTHRANGE(w1,w2)&t;FONTWIDTH(8)
DECL|macro|fontwidth
mdefine_line|#define fontwidth(p) (8)
DECL|macro|fontwidthlog
mdefine_line|#define fontwidthlog(p) (0)
macro_line|#else
multiline_comment|/* fontwidth w is supported by dispsw */
DECL|macro|FONTWIDTH
mdefine_line|#define FONTWIDTH(w)&t;(1 &lt;&lt; ((w) - 1))
multiline_comment|/* fontwidths w1-w2 inclusive are supported by dispsw */
DECL|macro|FONTWIDTHRANGE
mdefine_line|#define FONTWIDTHRANGE(w1,w2)&t;(FONTWIDTH(w2+1) - FONTWIDTH(w1))
DECL|macro|fontwidth
mdefine_line|#define fontwidth(p) ((p)-&gt;_fontwidth)
DECL|macro|fontwidthlog
mdefine_line|#define fontwidthlog(p) ((p)-&gt;_fontwidthlog)
macro_line|#endif
multiline_comment|/*&n;     *  Attribute Decoding&n;     */
multiline_comment|/* Color */
DECL|macro|attr_fgcol
mdefine_line|#define attr_fgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;fgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol
mdefine_line|#define attr_bgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;bgshift)) &amp; 0x0f)
DECL|macro|attr_bgcol_ec
mdefine_line|#define&t;attr_bgcol_ec(p,conp) &bslash;&n;&t;((conp) ? (((conp)-&gt;vc_video_erase_char &gt;&gt; ((p)-&gt;bgshift)) &amp; 0x0f) : 0)
multiline_comment|/* Monochrome */
DECL|macro|attr_bold
mdefine_line|#define attr_bold(p,s) &bslash;&n;&t;((s) &amp; 0x200)
DECL|macro|attr_reverse
mdefine_line|#define attr_reverse(p,s) &bslash;&n;&t;(((s) &amp; 0x800) ^ ((p)-&gt;inverse ? 0x800 : 0))
DECL|macro|attr_underline
mdefine_line|#define attr_underline(p,s) &bslash;&n;&t;((s) &amp; 0x400)
DECL|macro|attr_blink
mdefine_line|#define attr_blink(p,s) &bslash;&n;&t;((s) &amp; 0x8000)
multiline_comment|/*&n;     *  Scroll Method&n;     */
multiline_comment|/* Internal flags */
DECL|macro|__SCROLL_YPAN
mdefine_line|#define __SCROLL_YPAN&t;&t;0x001
DECL|macro|__SCROLL_YWRAP
mdefine_line|#define __SCROLL_YWRAP&t;&t;0x002
DECL|macro|__SCROLL_YMOVE
mdefine_line|#define __SCROLL_YMOVE&t;&t;0x003
DECL|macro|__SCROLL_YREDRAW
mdefine_line|#define __SCROLL_YREDRAW&t;0x004
DECL|macro|__SCROLL_YMASK
mdefine_line|#define __SCROLL_YMASK&t;&t;0x00f
DECL|macro|__SCROLL_YFIXED
mdefine_line|#define __SCROLL_YFIXED&t;&t;0x010
DECL|macro|__SCROLL_YNOMOVE
mdefine_line|#define __SCROLL_YNOMOVE&t;0x020
DECL|macro|__SCROLL_YPANREDRAW
mdefine_line|#define __SCROLL_YPANREDRAW&t;0x040
DECL|macro|__SCROLL_YNOPARTIAL
mdefine_line|#define __SCROLL_YNOPARTIAL&t;0x080
multiline_comment|/* Only these should be used by the drivers */
multiline_comment|/* Which one should you use? If you have a fast card and slow bus,&n;   then probably just 0 to indicate fbcon should choose between&n;   YWRAP/YPAN+MOVE/YMOVE. On the other side, if you have a fast bus&n;   and even better if your card can do fonting (1-&gt;8/32bit painting),&n;   you should consider either SCROLL_YREDRAW (if your card is&n;   able to do neither YPAN/YWRAP), or SCROLL_YNOMOVE.&n;   The best is to test it with some real life scrolling (usually, not&n;   all lines on the screen are filled completely with non-space characters,&n;   and REDRAW performs much better on such lines, so don&squot;t cat a file&n;   with every line covering all screen columns, it would not be the right&n;   benchmark).&n; */
DECL|macro|SCROLL_YREDRAW
mdefine_line|#define SCROLL_YREDRAW&t;&t;(__SCROLL_YFIXED|__SCROLL_YREDRAW)
DECL|macro|SCROLL_YNOMOVE
mdefine_line|#define SCROLL_YNOMOVE&t;&t;(__SCROLL_YNOMOVE|__SCROLL_YPANREDRAW)
multiline_comment|/* SCROLL_YNOPARTIAL, used in combination with the above, is for video&n;   cards which can not handle using panning to scroll a portion of the&n;   screen without excessive flicker.  Panning will only be used for&n;   whole screens.&n; */
multiline_comment|/* Namespace consistency */
DECL|macro|SCROLL_YNOPARTIAL
mdefine_line|#define SCROLL_YNOPARTIAL&t;__SCROLL_YNOPARTIAL
r_extern
r_void
id|fbcon_redraw_bmove
c_func
(paren
r_struct
id|display
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ================================================================= */
multiline_comment|/*                      Utility Assembler Functions                  */
multiline_comment|/* ================================================================= */
macro_line|#if defined(__mc68000__)
multiline_comment|/* ====================================================================== */
multiline_comment|/* Those of a delicate disposition might like to skip the next couple of&n; * pages.&n; *&n; * These functions are drop in replacements for memmove and&n; * memset(_, 0, _). However their five instances add at least a kilobyte&n; * to the object file. You have been warned.&n; *&n; * Not a great fan of assembler for the sake of it, but I think&n; * that these routines are at least 10 times faster than their C&n; * equivalents for large blits, and that&squot;s important to the lowest level of&n; * a graphics driver. Question is whether some scheme with the blitter&n; * would be faster. I suspect not for simple text system - not much&n; * asynchrony.&n; *&n; * Code is very simple, just gruesome expansion. Basic strategy is to&n; * increase data moved/cleared at each step to 16 bytes to reduce&n; * instruction per data move overhead. movem might be faster still&n; * For more than 15 bytes, we try to align the write direction on a&n; * longword boundary to get maximum speed. This is even more gruesome.&n; * Unaligned read/write used requires 68020+ - think this is a problem?&n; *&n; * Sorry!&n; */
multiline_comment|/* ++roman: I&squot;ve optimized Robert&squot;s original versions in some minor&n; * aspects, e.g. moveq instead of movel, let gcc choose the registers,&n; * use movem in some places...&n; * For other modes than 1 plane, lots of more such assembler functions&n; * were needed (e.g. the ones using movep or expanding color values).&n; */
multiline_comment|/* ++andreas: more optimizations:&n;   subl #65536,d0 replaced by clrw d0; subql #1,d0 for dbcc&n;   addal is faster than addaw&n;   movep is rather expensive compared to ordinary move&squot;s&n;   some functions rewritten in C for clarity, no speed loss */
DECL|function|mymemclear_small
r_static
id|__inline__
r_void
op_star
id|mymemclear_small
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%1 ; jcc 1f ; moveb %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movew %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movel %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movel %2,%0@- ; movel %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: subql  #1,%1 ; jcs 3f&bslash;n&bslash;t&quot;
l_string|&quot;2: moveml %2/%3/%4/%5,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,2b&bslash;n&bslash;t&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;d&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mymemclear
r_static
id|__inline__
r_void
op_star
id|mymemclear
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|16
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%1 ; jcc 1f ; clrb %0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; clrw %0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; clrl %0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; clrl %0@+ ; clrl %0@+&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movel %1,%2&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcc 1f ; clrb %0@+ ; subqw #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcs 2f&bslash;n&bslash;t&quot;
multiline_comment|/* %0 increased=&gt;bit 2 switched*/
l_string|&quot;clrw   %0@+  ; subqw  #2,%1 ; jra 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 2f&bslash;n&bslash;t&quot;
l_string|&quot;clrw   %0@+  ; subqw  #2,%1&bslash;n&bslash;t&quot;
l_string|&quot;2: movew %1,%2; lsrl #2,%1 ; jeq 6f&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%1 ; jcc 3f ; clrl %0@+&bslash;n&bslash;t&quot;
l_string|&quot;3: lsrl   #1,%1 ; jcc 4f ; clrl %0@+ ; clrl %0@+&bslash;n&bslash;t&quot;
l_string|&quot;4: subql  #1,%1 ; jcs 6f&bslash;n&bslash;t&quot;
l_string|&quot;5: clrl %0@+; clrl %0@+ ; clrl %0@+ ; clrl %0@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,5b   ; clrw %1; subql #1,%1; jcc 5b&bslash;n&bslash;t&quot;
l_string|&quot;6: movew %2,%1; btst #1,%1 ; jeq 7f ; clrw %0@+&bslash;n&bslash;t&quot;
l_string|&quot;7:            ; btst #0,%1 ; jeq 8f ; clrb %0@+&bslash;n&bslash;t&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|s
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mymemset
r_static
id|__inline__
r_void
op_star
id|mymemset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%1 ; jcc 1f ; moveb %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movew %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movel %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%1 ; jcc 1f ; movel %2,%0@- ; movel %2,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: subql  #1,%1 ; jcs 3f&bslash;n&bslash;t&quot;
l_string|&quot;2: moveml %2/%3/%4/%5,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,2b&bslash;n&bslash;t&quot;
l_string|&quot;3:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_minus
l_int|1
)paren
comma
l_string|&quot;d&quot;
(paren
op_minus
l_int|1
)paren
comma
l_string|&quot;d&quot;
(paren
op_minus
l_int|1
)paren
comma
l_string|&quot;d&quot;
(paren
op_minus
l_int|1
)paren
comma
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mymemmove
r_static
id|__inline__
r_void
op_star
id|mymemmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
r_if
c_cond
(paren
id|count
OL
l_int|16
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%2 ; jcc 1f ; moveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movew %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@+,%0@+ ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|d
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movel  %0,%3&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcc 1f ; moveb %1@+,%0@+ ; subqw #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcs 2f&bslash;n&bslash;t&quot;
multiline_comment|/* %0 increased=&gt;bit 2 switched*/
l_string|&quot;movew  %1@+,%0@+  ; subqw  #2,%2 ; jra 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%3 ; jcc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movew  %1@+,%0@+  ; subqw  #2,%2&bslash;n&bslash;t&quot;
l_string|&quot;2: movew  %2,%-; lsrl #2,%2 ; jeq 6f&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcc 3f ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;3: lsrl   #1,%2 ; jcc 4f ; movel %1@+,%0@+ ; movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;4: subql  #1,%2 ; jcs 6f&bslash;n&bslash;t&quot;
l_string|&quot;5: movel  %1@+,%0@+;movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;movel  %1@+,%0@+;movel %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra   %2,5b ; clrw %2; subql #1,%2; jcc 5b&bslash;n&bslash;t&quot;
l_string|&quot;6: movew  %+,%2; btst #1,%2 ; jeq 7f ; movew %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;7:              ; btst #0,%2 ; jeq 8f ; moveb %1@+,%0@+&bslash;n&bslash;t&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|d
)paren
comma
l_string|&quot;1&quot;
(paren
id|s
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|count
OL
l_int|16
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lsrl   #1,%2 ; jcc 1f ; moveb %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movew %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%2 ; jcc 1f ; movel %1@-,%0@- ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|d
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movel %0,%3&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcc 1f ; moveb %1@-,%0@- ; subqw #1,%2&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%3 ; jcs 2f&bslash;n&bslash;t&quot;
multiline_comment|/* %0 increased=&gt;bit 2 switched*/
l_string|&quot;movew  %1@-,%0@-  ; subqw  #2,%2 ; jra 2f&bslash;n&bslash;t&quot;
l_string|&quot;1: lsrl   #1,%3 ; jcc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movew  %1@-,%0@-  ; subqw  #2,%2&bslash;n&bslash;t&quot;
l_string|&quot;2: movew %2,%-; lsrl #2,%2 ; jeq 6f&bslash;n&bslash;t&quot;
l_string|&quot;lsrl   #1,%2 ; jcc 3f ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;3: lsrl   #1,%2 ; jcc 4f ; movel %1@-,%0@- ; movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;4: subql  #1,%2 ; jcs 6f&bslash;n&bslash;t&quot;
l_string|&quot;5: movel %1@-,%0@-;movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;movel %1@-,%0@-;movel %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;dbra %2,5b ; clrw %2; subql #1,%2; jcc 5b&bslash;n&bslash;t&quot;
l_string|&quot;6: movew %+,%2; btst #1,%2 ; jeq 7f ; movew %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;7:              ; btst #0,%2 ; jeq 8f ; moveb %1@-,%0@-&bslash;n&bslash;t&quot;
l_string|&quot;8:&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|d
)paren
comma
l_string|&quot;=a&quot;
(paren
id|s
)paren
comma
l_string|&quot;=d&quot;
(paren
id|count
)paren
comma
l_string|&quot;=d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
(paren
r_char
op_star
)paren
id|d
op_plus
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_char
op_star
)paren
id|s
op_plus
id|count
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ++andreas: Simple and fast version of memmove, assumes size is&n;   divisible by 16, suitable for moving the whole screen bitplane */
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dst
OL
id|src
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&quot;
l_string|&quot;  moveml %0@+,%/d0/%/d1/%/a0/%/a1&bslash;n&quot;
l_string|&quot;  moveml %/d0/%/d1/%/a0/%/a1,%1@&bslash;n&quot;
l_string|&quot;  addql #8,%1; addql #8,%1&bslash;n&quot;
l_string|&quot;  dbra %2,1b&bslash;n&quot;
l_string|&quot;  clrw %2; subql #1,%2&bslash;n&quot;
l_string|&quot;  jcc 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=d&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
)paren
comma
l_string|&quot;1&quot;
(paren
id|dst
)paren
comma
l_string|&quot;2&quot;
(paren
id|size
op_div
l_int|16
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;d1&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|__asm__
id|__volatile__
(paren
l_string|&quot;1:&quot;
l_string|&quot;  subql #8,%0; subql #8,%0&bslash;n&quot;
l_string|&quot;  moveml %0@,%/d0/%/d1/%/a0/%/a1&bslash;n&quot;
l_string|&quot;  moveml %/d0/%/d1/%/a0/%/a1,%1@-&bslash;n&quot;
l_string|&quot;  dbra %2,1b&bslash;n&quot;
l_string|&quot;  clrw %2; subql #1,%2&bslash;n&quot;
l_string|&quot;  jcc 1b&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=d&quot;
(paren
id|size
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|src
op_plus
id|size
)paren
comma
l_string|&quot;1&quot;
(paren
id|dst
op_plus
id|size
)paren
comma
l_string|&quot;2&quot;
(paren
id|size
op_div
l_int|16
op_minus
l_int|1
)paren
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;d1&quot;
comma
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_SUN4)
multiline_comment|/* You may think that I&squot;m crazy and that I should use generic&n;   routines.  No, I&squot;m not: sun4&squot;s framebuffer crashes if we std&n;   into it, so we cannot use memset.  */
DECL|function|sun4_memset
r_static
id|__inline__
r_void
op_star
id|sun4_memset
c_func
(paren
r_void
op_star
id|s
comma
r_char
id|val
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|i
)braket
op_assign
id|val
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|mymemset
r_static
id|__inline__
r_void
op_star
id|mymemset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|sun4_memset
c_func
(paren
id|s
comma
l_int|255
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|mymemclear
r_static
id|__inline__
r_void
op_star
id|mymemclear
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|sun4_memset
c_func
(paren
id|s
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|mymemclear_small
r_static
id|__inline__
r_void
op_star
id|mymemclear_small
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|sun4_memset
c_func
(paren
id|s
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* To be honest, this is slow_memmove :). But sun4 is crappy, so what we can do. */
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_char
op_star
)paren
id|d
)paren
(braket
id|i
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(paren
(paren
r_char
op_star
)paren
id|d
)paren
(braket
id|count
op_minus
id|i
op_minus
l_int|1
)braket
op_assign
(paren
(paren
r_char
op_star
)paren
id|s
)paren
(braket
id|count
op_minus
id|i
op_minus
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|mymemmove
r_static
id|__inline__
r_void
op_star
id|mymemmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|fast_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|size
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
macro_line|#else
DECL|function|mymemclear_small
r_static
id|__inline__
r_void
op_star
id|mymemclear_small
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|mymemclear
r_static
id|__inline__
r_void
op_star
id|mymemclear
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|mymemset
r_static
id|__inline__
r_void
op_star
id|mymemset
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|memset
c_func
(paren
id|s
comma
l_int|255
comma
id|count
)paren
suffix:semicolon
)brace
macro_line|#if defined(__i386__)
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_int
id|d0
comma
id|d1
comma
id|d2
comma
id|d3
suffix:semicolon
r_if
c_cond
(paren
id|d
OL
id|s
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;tshrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;trep&bslash;n&bslash;t&quot;
l_string|&quot;movsl&quot;
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
(paren
r_int
)paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
(paren
r_int
)paren
id|s
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;std&bslash;n&bslash;t&quot;
l_string|&quot;shrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 1f&bslash;n&bslash;t&quot;
l_string|&quot;movb 3(%%esi),%%al&bslash;n&bslash;t&quot;
l_string|&quot;movb %%al,3(%%edi)&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&quot;
l_string|&quot;1:&bslash;tshrl $1,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;jnc 2f&bslash;n&bslash;t&quot;
l_string|&quot;movw 2(%%esi),%%ax&bslash;n&bslash;t&quot;
l_string|&quot;movw %%ax,2(%%edi)&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%esi&bslash;n&bslash;t&quot;
l_string|&quot;decl %%edi&bslash;n&quot;
l_string|&quot;2:&bslash;trep&bslash;n&bslash;t&quot;
l_string|&quot;movsl&bslash;n&bslash;t&quot;
l_string|&quot;cld&quot;
suffix:colon
l_string|&quot;=&amp;c&quot;
(paren
id|d0
)paren
comma
l_string|&quot;=&amp;D&quot;
(paren
id|d1
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d2
)paren
comma
l_string|&quot;=&amp;a&quot;
(paren
id|d3
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|count
)paren
comma
l_string|&quot;1&quot;
(paren
id|count
op_minus
l_int|4
op_plus
(paren
r_int
)paren
id|d
)paren
comma
l_string|&quot;2&quot;
(paren
id|count
op_minus
l_int|4
op_plus
(paren
r_int
)paren
id|s
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|mymemmove
r_static
id|__inline__
r_void
op_star
id|mymemmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|fast_memmove
c_func
(paren
id|dst
comma
id|src
comma
id|size
)paren
suffix:semicolon
r_return
id|dst
suffix:semicolon
)brace
macro_line|#else /* !i386 */
multiline_comment|/*&n;     *  Anyone who&squot;d like to write asm functions for other CPUs?&n;     *   (Why are these functions better than those from include/asm/string.h?)&n;     */
DECL|function|mymemmove
r_static
id|__inline__
r_void
op_star
id|mymemmove
c_func
(paren
r_void
op_star
id|d
comma
r_const
r_void
op_star
id|s
comma
r_int
id|count
)paren
(brace
r_return
id|memmove
c_func
(paren
id|d
comma
id|s
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|fast_memmove
r_static
id|__inline__
r_void
id|fast_memmove
c_func
(paren
r_char
op_star
id|dst
comma
r_const
r_char
op_star
id|src
comma
r_int
id|size
)paren
(brace
id|memmove
c_func
(paren
id|dst
comma
id|src
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif /* !i386 */
macro_line|#endif
macro_line|#if defined(__i386__) || defined(__alpha__)
DECL|macro|fb_readb
mdefine_line|#define fb_readb __raw_readb
DECL|macro|fb_readw
mdefine_line|#define fb_readw __raw_readw
DECL|macro|fb_readl
mdefine_line|#define fb_readl __raw_readl
DECL|macro|fb_writeb
mdefine_line|#define fb_writeb __raw_writeb
DECL|macro|fb_writew
mdefine_line|#define fb_writew __raw_writew
DECL|macro|fb_writel
mdefine_line|#define fb_writel __raw_writel
macro_line|#else
DECL|macro|fb_readb
mdefine_line|#define fb_readb(addr) (*(volatile u8 *) (addr))
DECL|macro|fb_readw
mdefine_line|#define fb_readw(addr) (*(volatile u16 *) (addr))
DECL|macro|fb_readl
mdefine_line|#define fb_readl(addr) (*(volatile u32 *) (addr))
DECL|macro|fb_writeb
mdefine_line|#define fb_writeb(b,addr) (*(volatile u8 *) (addr) = (b))
DECL|macro|fb_writew
mdefine_line|#define fb_writew(b,addr) (*(volatile u16 *) (addr) = (b))
DECL|macro|fb_writel
mdefine_line|#define fb_writel(b,addr) (*(volatile u32 *) (addr) = (b))
macro_line|#endif
macro_line|#endif /* _VIDEO_FBCON_H */
eof
