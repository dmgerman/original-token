macro_line|#ifndef _M68K_IDE_H
DECL|macro|_M68K_IDE_H
mdefine_line|#define _M68K_IDE_H
multiline_comment|/* Copyright(c) 1996 Kars de Jong */
multiline_comment|/* Based on the ide driver from 1.2.13pl8 */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amihdreg.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#endif /* CONFIG_AMIGA */
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atarihdreg.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
macro_line|#endif /* CONFIG_ATARI */
macro_line|#include &lt;asm/bootinfo.h&gt;
DECL|struct|hd_regs_struct
r_struct
id|hd_regs_struct
(brace
DECL|member|hd_error
r_int
r_int
id|hd_error
comma
DECL|member|hd_nsector
id|hd_nsector
comma
DECL|member|hd_sector
id|hd_sector
comma
DECL|member|hd_lcyl
id|hd_lcyl
comma
DECL|member|hd_hcyl
id|hd_hcyl
comma
DECL|member|hd_select
id|hd_select
comma
DECL|member|hd_status
id|hd_status
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|hd_regs
r_static
r_struct
id|hd_regs_struct
id|hd_regs
suffix:semicolon
r_static
r_void
id|probe_m68k_ide
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Undefine these again, they were defined for the PC. */
DECL|macro|IDE_ERROR_OFFSET
macro_line|#undef IDE_ERROR_OFFSET
DECL|macro|IDE_NSECTOR_OFFSET
macro_line|#undef IDE_NSECTOR_OFFSET
DECL|macro|IDE_SECTOR_OFFSET
macro_line|#undef IDE_SECTOR_OFFSET
DECL|macro|IDE_LCYL_OFFSET
macro_line|#undef IDE_LCYL_OFFSET
DECL|macro|IDE_HCYL_OFFSET
macro_line|#undef IDE_HCYL_OFFSET
DECL|macro|IDE_SELECT_OFFSET
macro_line|#undef IDE_SELECT_OFFSET
DECL|macro|IDE_STATUS_OFFSET
macro_line|#undef IDE_STATUS_OFFSET
DECL|macro|IDE_FEATURE_OFFSET
macro_line|#undef IDE_FEATURE_OFFSET
DECL|macro|IDE_COMMAND_OFFSET
macro_line|#undef IDE_COMMAND_OFFSET
DECL|macro|SELECT_DRIVE
macro_line|#undef SELECT_DRIVE
DECL|macro|IDE_ERROR_OFFSET
mdefine_line|#define IDE_ERROR_OFFSET&t;hd_regs.hd_error
DECL|macro|IDE_NSECTOR_OFFSET
mdefine_line|#define IDE_NSECTOR_OFFSET&t;hd_regs.hd_nsector
DECL|macro|IDE_SECTOR_OFFSET
mdefine_line|#define IDE_SECTOR_OFFSET&t;hd_regs.hd_sector
DECL|macro|IDE_LCYL_OFFSET
mdefine_line|#define IDE_LCYL_OFFSET&t;&t;hd_regs.hd_lcyl
DECL|macro|IDE_HCYL_OFFSET
mdefine_line|#define IDE_HCYL_OFFSET&t;&t;hd_regs.hd_hcyl
DECL|macro|IDE_SELECT_OFFSET
mdefine_line|#define IDE_SELECT_OFFSET&t;hd_regs.hd_select
DECL|macro|IDE_STATUS_OFFSET
mdefine_line|#define IDE_STATUS_OFFSET&t;hd_regs.hd_status
DECL|macro|IDE_FEATURE_OFFSET
mdefine_line|#define IDE_FEATURE_OFFSET&t;IDE_ERROR_OFFSET
DECL|macro|IDE_COMMAND_OFFSET
mdefine_line|#define IDE_COMMAND_OFFSET&t;IDE_STATUS_OFFSET
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC 0
DECL|macro|HD_DATA
macro_line|#undef HD_DATA
DECL|macro|HD_DATA
mdefine_line|#define HD_DATA NULL
multiline_comment|/* MSch: changed sti() to STI() wherever possible in ide.c; moved STI() def. &n; * to asm/ide.h &n; */
multiline_comment|/* The Atari interrupt structure strictly requires that the IPL isn&squot;t lowered&n; * uncontrolled in an interrupt handler. In the concrete case, the IDE&n; * interrupt is already a slow int, so the irq is already disabled at the time&n; * the handler is called, and the IPL has been lowered to the minimum value&n; * possible. To avoid going below that, STI() checks for being called inside&n; * an interrupt, and in that case it does nothing. Hope that is reasonable and&n; * works. (Roman)&n; */
macro_line|#if defined(CONFIG_ATARI) &amp;&amp; !defined(CONFIG_AMIGA)
DECL|macro|STI
mdefine_line|#define&t;STI()&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&bslash;&n;&t;if (!intr_count) sti();&t;&t;&t;&bslash;&n;    } while(0)
macro_line|#elif defined(CONFIG_ATARI)
DECL|macro|STI
mdefine_line|#define&t;STI()&t;&t;&t;&t;&t;&t;&bslash;&n;    do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!MACH_IS_ATARI || !intr_count) sti();&t;&bslash;&n;    } while(0)
macro_line|#else /* !defined(CONFIG_ATARI) */
DECL|macro|STI
mdefine_line|#define&t;STI()&t;sti()
macro_line|#endif
DECL|macro|SELECT_DRIVE
mdefine_line|#define SELECT_DRIVE(hwif,drive)  OUT_BYTE((drive)-&gt;select.all, hwif-&gt;io_base+IDE_SELECT_OFFSET);
DECL|macro|insl
mdefine_line|#define insl(data_reg, buffer, wcount) insw(data_reg, buffer, wcount&lt;&lt;1)
DECL|macro|outsl
mdefine_line|#define outsl(data_reg, buffer, wcount) outsw(data_reg, buffer, wcount&lt;&lt;1)
DECL|macro|insw
mdefine_line|#define insw(port, buf, nr) &bslash;&n;    if (nr % 16) &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a0@,%/a1@+; &bslash;&n;&t;&t; dbra %/d6,1b&quot; : &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;    else &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; lsrl  #4,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; movew %/a0@,%/a1@+; &bslash;&n;&t;&t; dbra %/d6,1b&quot; : &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;);
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, nr) &bslash;&n;    if (nr % 16) &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a1@+,%/a0@; &bslash;&n;&t;&t; dbra %/d6,1b&quot; : &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;); &bslash;&n;    else &bslash;&n;&t;__asm__ __volatile__ &bslash;&n;&t;       (&quot;movel %0,%/a0; &bslash;&n;&t;&t; movel %1,%/a1; &bslash;&n;&t;&t; movel %2,%/d6; &bslash;&n;&t;&t; lsrl  #4,%/d6; &bslash;&n;&t;&t; subql #1,%/d6; &bslash;&n;&t;       1:movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; movew %/a1@+,%/a0@; &bslash;&n;&t;&t; dbra %/d6,1b&quot; : &bslash;&n;&t;&t;: &quot;g&quot; (port), &quot;g&quot; (buf), &quot;g&quot; (nr) &bslash;&n;&t;&t;: &quot;a0&quot;, &quot;a1&quot;, &quot;d6&quot;);
DECL|macro|T_CHAR
mdefine_line|#define T_CHAR          (0x0000)        /* char:  don&squot;t touch  */
DECL|macro|T_SHORT
mdefine_line|#define T_SHORT         (0x4000)        /* short: 12 -&gt; 21     */
DECL|macro|T_INT
mdefine_line|#define T_INT           (0x8000)        /* int:   1234 -&gt; 4321 */
DECL|macro|T_TEXT
mdefine_line|#define T_TEXT          (0xc000)        /* text:  12 -&gt; 21     */
DECL|macro|T_MASK_TYPE
mdefine_line|#define T_MASK_TYPE     (0xc000)
DECL|macro|T_MASK_COUNT
mdefine_line|#define T_MASK_COUNT    (0x3fff)
DECL|macro|D_CHAR
mdefine_line|#define D_CHAR(cnt)     (T_CHAR  | (cnt))
DECL|macro|D_SHORT
mdefine_line|#define D_SHORT(cnt)    (T_SHORT | (cnt))
DECL|macro|D_INT
mdefine_line|#define D_INT(cnt)      (T_INT   | (cnt))
DECL|macro|D_TEXT
mdefine_line|#define D_TEXT(cnt)     (T_TEXT  | (cnt))
DECL|variable|driveid_types
r_static
id|u_short
id|driveid_types
(braket
)braket
op_assign
(brace
id|D_SHORT
c_func
(paren
l_int|10
)paren
comma
multiline_comment|/* config - vendor2 */
id|D_TEXT
c_func
(paren
l_int|20
)paren
comma
multiline_comment|/* serial_no */
id|D_SHORT
c_func
(paren
l_int|3
)paren
comma
multiline_comment|/* buf_type - ecc_bytes */
id|D_TEXT
c_func
(paren
l_int|48
)paren
comma
multiline_comment|/* fw_rev - model */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* max_multsect - vendor3 */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* dword_io */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* vendor4 - capability */
id|D_SHORT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* reserved50 */
id|D_CHAR
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* vendor5 - tDMA */
id|D_SHORT
c_func
(paren
l_int|4
)paren
comma
multiline_comment|/* field_valid - cur_sectors */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* cur_capacity */
id|D_CHAR
c_func
(paren
l_int|2
)paren
comma
multiline_comment|/* multsect - multsect_valid */
id|D_INT
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* lba_capacity */
id|D_SHORT
c_func
(paren
l_int|194
)paren
multiline_comment|/* dma_1word - reservedyy */
)brace
suffix:semicolon
DECL|macro|num_driveid_types
mdefine_line|#define num_driveid_types       (sizeof(driveid_types)/sizeof(*driveid_types))
DECL|function|big_endianize_driveid
r_static
id|__inline__
r_void
id|big_endianize_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
id|id
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|cnt
suffix:semicolon
id|u_char
id|t
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
id|num_driveid_types
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cnt
op_assign
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_COUNT
suffix:semicolon
r_switch
c_cond
(paren
id|driveid_types
(braket
id|i
)braket
op_amp
id|T_MASK_TYPE
)paren
(brace
r_case
id|T_CHAR
suffix:colon
id|p
op_add_assign
id|cnt
suffix:semicolon
r_break
suffix:semicolon
r_case
id|T_SHORT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_INT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_increment
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|3
)braket
suffix:semicolon
id|p
(braket
l_int|3
)braket
op_assign
id|t
suffix:semicolon
id|t
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|p
(braket
l_int|2
)braket
suffix:semicolon
id|p
(braket
l_int|2
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|T_TEXT
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|cnt
suffix:semicolon
id|j
op_add_assign
l_int|2
)paren
(brace
id|t
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
id|p
(braket
l_int|0
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|p
(braket
l_int|1
)braket
op_assign
id|t
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* _M68K_IDE_H */
eof
