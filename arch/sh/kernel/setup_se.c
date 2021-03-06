multiline_comment|/* $Id: setup_se.c,v 1.6 2000/05/14 08:41:25 gniibe Exp $&n; *&n; * linux/arch/sh/kernel/setup_se.c&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Hitachi SolutionEngine Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hitachi_se.h&gt;
macro_line|#include &lt;asm/smc37c93x.h&gt;
multiline_comment|/*&n; * Configure the Super I/O chip&n; */
DECL|function|smsc_config
r_static
r_void
id|__init
id|smsc_config
c_func
(paren
r_int
id|index
comma
r_int
id|data
)paren
(brace
id|outb_p
c_func
(paren
id|index
comma
id|INDEX_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data
comma
id|DATA_PORT
)paren
suffix:semicolon
)brace
DECL|function|init_smsc
r_static
r_void
id|__init
id|init_smsc
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
id|CONFIG_ENTER
comma
id|CONFIG_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|CONFIG_ENTER
comma
id|CONFIG_PORT
)paren
suffix:semicolon
multiline_comment|/* FDC */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_FDC
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/* IRQ6 */
multiline_comment|/* IDE1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_IDE1
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|14
)paren
suffix:semicolon
multiline_comment|/* IRQ14 */
multiline_comment|/* AUXIO (GPIO): to use IDE1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_AUXIO
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|GPIO46_INDEX
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* nIOROP */
id|smsc_config
c_func
(paren
id|GPIO47_INDEX
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* nIOWOP */
multiline_comment|/* COM1 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_COM1
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_HI_INDEX
comma
l_int|0x03
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_LO_INDEX
comma
l_int|0xf8
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* IRQ4 */
multiline_comment|/* COM2 */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_COM2
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_HI_INDEX
comma
l_int|0x02
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IO_BASE_LO_INDEX
comma
l_int|0xf8
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* IRQ3 */
multiline_comment|/* RTC */
id|smsc_config
c_func
(paren
id|CURRENT_LDN_INDEX
comma
id|LDN_RTC
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|ACTIVATE_INDEX
comma
l_int|0x01
)paren
suffix:semicolon
id|smsc_config
c_func
(paren
id|IRQ_SELECT_INDEX
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* IRQ8 */
multiline_comment|/* XXX: PARPORT, KBD, and MOUSE will come here... */
id|outb_p
c_func
(paren
id|CONFIG_EXIT
comma
id|CONFIG_PORT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize IRQ setting&n; */
DECL|function|init_se_IRQ
r_void
id|__init
id|init_se_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Super I/O (Just mimic PC):&n;&t; *  1: keyboard&n;&t; *  3: serial 0&n;&t; *  4: serial 1&n;&t; *  5: printer&n;&t; *  6: floppy&n;&t; *  8: rtc&n;&t; * 12: mouse&n;&t; * 14: ide0&n;&t; */
id|make_ipr_irq
c_func
(paren
l_int|14
comma
id|BCR_ILCRA
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|14
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|12
comma
id|BCR_ILCRA
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|12
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|8
comma
id|BCR_ILCRB
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|8
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|6
comma
id|BCR_ILCRC
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|6
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|5
comma
id|BCR_ILCRC
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|5
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|4
comma
id|BCR_ILCRC
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|4
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|3
comma
id|BCR_ILCRC
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|3
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|1
comma
id|BCR_ILCRD
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|1
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|10
comma
id|BCR_ILCRD
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|10
)paren
suffix:semicolon
multiline_comment|/* LAN */
id|make_ipr_irq
c_func
(paren
l_int|0
comma
id|BCR_ILCRE
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|0
)paren
suffix:semicolon
multiline_comment|/* PCIRQ3 */
id|make_ipr_irq
c_func
(paren
l_int|11
comma
id|BCR_ILCRE
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|11
)paren
suffix:semicolon
multiline_comment|/* PCIRQ2 */
id|make_ipr_irq
c_func
(paren
l_int|9
comma
id|BCR_ILCRE
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|9
)paren
suffix:semicolon
multiline_comment|/* PCIRQ1 */
id|make_ipr_irq
c_func
(paren
l_int|7
comma
id|BCR_ILCRE
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|7
)paren
suffix:semicolon
multiline_comment|/* PCIRQ0 */
multiline_comment|/* #2, #13 are allocated for SLOT IRQ #1 and #2 (for now) */
multiline_comment|/* NOTE: #2 and #13 are not used on PC */
id|make_ipr_irq
c_func
(paren
l_int|13
comma
id|BCR_ILCRG
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|13
)paren
suffix:semicolon
multiline_comment|/* SLOTIRQ2 */
id|make_ipr_irq
c_func
(paren
l_int|2
comma
id|BCR_ILCRG
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* SLOTIRQ1 */
)brace
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|setup_se
r_void
id|__init
id|setup_se
c_func
(paren
r_void
)paren
(brace
id|init_smsc
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX: RTC setting comes here */
)brace
eof
