multiline_comment|/*&n; *  linux/drivers/video/fbcon.h -- Low level frame buffer based console driver&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef __VIDEO_FBCON_H
DECL|macro|__VIDEO_FBCON_H
mdefine_line|#define __VIDEO_FBCON_H
macro_line|#include &lt;linux/console_struct.h&gt;
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
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Attribute Decoding&n;     */
multiline_comment|/* Color */
DECL|macro|attr_fgcol
mdefine_line|#define attr_fgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;inverse ? 12 : 8)) &amp; 0x0f)
DECL|macro|attr_bgcol
mdefine_line|#define attr_bgcol(p,s)    &bslash;&n;&t;(((s) &gt;&gt; ((p)-&gt;inverse ? 8 : 12)) &amp; 0x0f)
DECL|macro|attr_bgcol_ec
mdefine_line|#define&t;attr_bgcol_ec(p,conp) &bslash;&n;&t;(((conp)-&gt;vc_video_erase_char &gt;&gt; ((p)-&gt;inverse ? 8 : 12)) &amp; 0x0f)
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
DECL|macro|SCROLL_YWRAP
mdefine_line|#define SCROLL_YWRAP&t;(0)
DECL|macro|SCROLL_YPAN
mdefine_line|#define SCROLL_YPAN&t;(1)
DECL|macro|SCROLL_YMOVE
mdefine_line|#define SCROLL_YMOVE&t;(2)
DECL|macro|SCROLL_YREDRAW
mdefine_line|#define SCROLL_YREDRAW&t;(3)
multiline_comment|/* ================================================================= */
multiline_comment|/*                      Utility Assembler Functions                  */
multiline_comment|/* ================================================================= */
macro_line|#ifdef __mc68000__
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
macro_line|#else /* !m68k */
multiline_comment|/*&n;     *  Anyone who&squot;d like to write asm functions for other CPUs?&n;     */
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
macro_line|#ifdef __i386__
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
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|count
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|d
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|s
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
comma
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
l_string|&quot;movsl&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;c&quot;
(paren
id|count
)paren
comma
l_string|&quot;D&quot;
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
l_string|&quot;S&quot;
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
l_string|&quot;ax&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
comma
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
macro_line|#else
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
macro_line|#endif&t;/* !i386 */
macro_line|#endif /* !m68k */
macro_line|#endif /* __VIDEO_FBCON_H */
eof
