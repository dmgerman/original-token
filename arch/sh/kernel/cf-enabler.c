multiline_comment|/* $Id: cf-enabler.c,v 1.2 2000/06/08 05:50:10 gniibe Exp $&n; *&n; *  linux/drivers/block/cf-enabler.c&n; *&n; *  Copyright (C) 1999  Niibe Yutaka&n; *  Copyright (C) 2000  Toshiharu Nozawa&n; *&n; *  Enable the CF configuration.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hitachi_se.h&gt;
multiline_comment|/*&n; * SolutionEngine&n; *&n; * 0xB8400000 : Common Memory&n; * 0xB8500000 : Attribute&n; * 0xB8600000 : I/O&n; */
DECL|function|cf_init_se
r_static
r_int
id|__init
id|cf_init_se
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x000c
)paren
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Not detected */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x0080
)paren
op_eq
l_int|0
)paren
(brace
id|ctrl_outw
c_func
(paren
l_int|0x0674
comma
id|MRSHPC_CPWCR
)paren
suffix:semicolon
multiline_comment|/* Card Vcc is 3.3v? */
)brace
r_else
(brace
id|ctrl_outw
c_func
(paren
l_int|0x0678
comma
id|MRSHPC_CPWCR
)paren
suffix:semicolon
multiline_comment|/* Card Vcc is 5V */
)brace
multiline_comment|/*&n;&t; *  PC-Card window open &n;&t; *  flag == COMMON/ATTRIBUTE/IO&n;&t; */
multiline_comment|/* common window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a84
comma
id|MRSHPC_MW0CR1
)paren
suffix:semicolon
multiline_comment|/* window 0xb8400000 */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* common mode &amp; bus width 16bit SWAP = 1*/
id|ctrl_outw
c_func
(paren
l_int|0x0b00
comma
id|MRSHPC_MW0CR2
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* common mode &amp; bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x0300
comma
id|MRSHPC_MW0CR2
)paren
suffix:semicolon
multiline_comment|/* attribute window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a85
comma
id|MRSHPC_MW1CR1
)paren
suffix:semicolon
multiline_comment|/* window 0xb8500000 */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
multiline_comment|/* attribute mode &amp; bus width 16bit SWAP = 1*/
id|ctrl_outw
c_func
(paren
l_int|0x0a00
comma
id|MRSHPC_MW1CR2
)paren
suffix:semicolon
r_else
multiline_comment|/* attribute mode &amp; bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x0200
comma
id|MRSHPC_MW1CR2
)paren
suffix:semicolon
multiline_comment|/* I/O window open */
id|ctrl_outw
c_func
(paren
l_int|0x8a86
comma
id|MRSHPC_IOWCR1
)paren
suffix:semicolon
multiline_comment|/* I/O window 0xb8600000 */
id|ctrl_outw
c_func
(paren
l_int|0x0008
comma
id|MRSHPC_CDCR
)paren
suffix:semicolon
multiline_comment|/* I/O card mode */
r_if
c_cond
(paren
(paren
id|ctrl_inw
c_func
(paren
id|MRSHPC_CSR
)paren
op_amp
l_int|0x4000
)paren
op_ne
l_int|0
)paren
id|ctrl_outw
c_func
(paren
l_int|0x0a00
comma
id|MRSHPC_IOWCR2
)paren
suffix:semicolon
multiline_comment|/* bus width 16bit SWAP = 1*/
r_else
id|ctrl_outw
c_func
(paren
l_int|0x0200
comma
id|MRSHPC_IOWCR2
)paren
suffix:semicolon
multiline_comment|/* bus width 16bit SWAP = 0*/
id|ctrl_outw
c_func
(paren
l_int|0x2000
comma
id|MRSHPC_ICR
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0x00
comma
id|PA_MRSHPC_MW2
op_plus
l_int|0x206
)paren
suffix:semicolon
id|ctrl_outb
c_func
(paren
l_int|0x42
comma
id|PA_MRSHPC_MW2
op_plus
l_int|0x200
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|CF_CIS_BASE
mdefine_line|#define CF_CIS_BASE&t;0xb8000000
multiline_comment|/*&n; * You can connect Compact Flash directly to the bus of SuperH.&n; * This is the enabler for that.&n; *&n; * SIM: How generic is this really? It looks pretty board, or at&n; * least SH sub-type, specific to me.&n; * I know it doesn&squot;t work on the Overdrive!&n; */
multiline_comment|/*&n; * 0xB8000000 : Attribute&n; * 0xB8001000 : Common Memory&n; * 0xBA000000 : I/O&n; */
DECL|function|cf_init_default
r_static
r_int
id|__init
id|cf_init_default
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Enable the card, and set the level interrupt */
id|ctrl_outw
c_func
(paren
l_int|0x0042
comma
id|CF_CIS_BASE
op_plus
l_int|0x0200
)paren
suffix:semicolon
id|make_imask_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cf_init
r_int
id|__init
id|cf_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACH_SE
)paren
(brace
r_return
id|cf_init_se
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|cf_init_default
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|cf_init
id|__initcall
(paren
id|cf_init
)paren
suffix:semicolon
eof
