multiline_comment|/*&n; *  linux/drivers/block/macide.c -- Macintosh IDE Driver&n; *&n; *     Copyright (C) 1998 by Michael Schmitz&n; *&n; *  This driver was written based on information obtained from the MacOS IDE&n; *  driver binary by Mikael Forselius&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/machw.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
multiline_comment|/*&n;     *  Base of the IDE interface (see ATAManager ROM code)&n;     */
DECL|macro|MAC_HD_BASE
mdefine_line|#define MAC_HD_BASE&t;0x50f1a000
multiline_comment|/*&n;     *  Offsets from the above base (scaling 4)&n;     */
DECL|macro|MAC_HD_DATA
mdefine_line|#define MAC_HD_DATA&t;0x00
DECL|macro|MAC_HD_ERROR
mdefine_line|#define MAC_HD_ERROR&t;0x04&t;&t;/* see err-bits */
DECL|macro|MAC_HD_NSECTOR
mdefine_line|#define MAC_HD_NSECTOR&t;0x08&t;&t;/* nr of sectors to read/write */
DECL|macro|MAC_HD_SECTOR
mdefine_line|#define MAC_HD_SECTOR&t;0x0c&t;&t;/* starting sector */
DECL|macro|MAC_HD_LCYL
mdefine_line|#define MAC_HD_LCYL&t;0x10&t;&t;/* starting cylinder */
DECL|macro|MAC_HD_HCYL
mdefine_line|#define MAC_HD_HCYL&t;0x14&t;&t;/* high byte of starting cyl */
DECL|macro|MAC_HD_SELECT
mdefine_line|#define MAC_HD_SELECT&t;0x18&t;&t;/* 101dhhhh , d=drive, hhhh=head */
DECL|macro|MAC_HD_STATUS
mdefine_line|#define MAC_HD_STATUS&t;0x1c&t;&t;/* see status-bits */
DECL|macro|MAC_HD_CONTROL
mdefine_line|#define MAC_HD_CONTROL&t;0x38&t;&t;/* control/altstatus */
DECL|variable|macide_offsets
r_static
r_int
id|macide_offsets
(braket
id|IDE_NR_PORTS
)braket
op_assign
(brace
id|MAC_HD_DATA
comma
id|MAC_HD_ERROR
comma
id|MAC_HD_NSECTOR
comma
id|MAC_HD_SECTOR
comma
id|MAC_HD_LCYL
comma
id|MAC_HD_HCYL
comma
id|MAC_HD_SELECT
comma
id|MAC_HD_STATUS
comma
id|MAC_HD_CONTROL
)brace
suffix:semicolon
multiline_comment|/*&n;&t; * Other registers&n;&t; */
multiline_comment|/* &n;&t; * IDE interrupt status register for both (?) hwifs on Quadra&n;&t; * Initial setting: 0xc&n;&t; * Guessing again:&n;&t; * Bit 0+1: some interrupt flags&n;&t; * Bit 2+3: some interrupt enable&n;&t; * Bit 4:   ??&n;&t; * Bit 5:   IDE interrupt flag (any hwif)&n;&t; * Bit 6:   maybe IDE interrupt enable (any hwif) ??&n;&t; * Bit 7:   Any interrupt condition&n;&t; *&n;&t; * Only relevant item: bit 5, to be checked by mac_ack_intr&n;&t; */
DECL|macro|MAC_HD_ISR
mdefine_line|#define MAC_HD_ISR&t;0x101
DECL|function|mac_ack_intr
r_static
r_int
id|mac_ack_intr
c_func
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
r_int
r_char
id|isr
suffix:semicolon
id|isr
op_assign
id|readb
c_func
(paren
id|MAC_HD_BASE
op_plus
id|MAC_HD_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
(brace
id|writeb
c_func
(paren
id|isr
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
id|MAC_HD_BASE
op_plus
id|MAC_HD_ISR
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Probe for a Macintosh IDE interface&n;     */
DECL|function|macide_init
r_void
id|macide_init
c_func
(paren
r_void
)paren
(brace
id|hw_regs_t
id|hw
suffix:semicolon
r_int
id|index
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
op_logical_or
id|macintosh_config-&gt;ide_type
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|macintosh_config-&gt;ide_type
)paren
(brace
r_case
id|MAC_IDE_QUADRA
suffix:colon
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
id|MAC_HD_BASE
comma
id|macide_offsets
comma
l_int|0
comma
(paren
id|ide_ioreg_t
)paren
(paren
id|MAC_HD_BASE
op_plus
id|MAC_HD_ISR
)paren
comma
id|mac_ack_intr
comma
id|IRQ_NUBUS_F
)paren
suffix:semicolon
id|index
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ide_setup_ports
c_func
(paren
op_amp
id|hw
comma
(paren
id|ide_ioreg_t
)paren
id|MAC_HD_BASE
comma
id|macide_offsets
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|IRQ_NUBUS_C
)paren
suffix:semicolon
id|index
op_assign
id|ide_register_hw
c_func
(paren
op_amp
id|hw
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|macintosh_config-&gt;ide_type
op_eq
id|MAC_IDE_QUADRA
)paren
id|printk
c_func
(paren
l_string|&quot;ide%d: Macintosh Quadra IDE interface&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;ide%d: Macintosh Powerbook IDE interface&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
)brace
)brace
eof
