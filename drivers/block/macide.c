multiline_comment|/*&n; *  linux/drivers/block/macide.c -- Macintosh IDE Driver&n; *&n; *     Copyright (C) 1998 by Michael Schmitz&n; *&n; *  This driver was written based on information obtained from the MacOS IDE&n; *  driver binary by Mikael Forselius&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
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
multiline_comment|/*&n;&t; * IDE interrupt glue - seems to be wired to Nubus, Slot C?&n;&t; * (ROM code disassembly again)&n;&t; * First try: just use Nubus interrupt for Slot C. Have Nubus code call&n;&t; * a wrapper to ide_intr that checks the ISR (see above).&n;&t; * Need to #define IDE_IRQ_NUBUS though.&n;&t; * Alternative method: set a mac_ide_hook function pointer to the wrapper &n;&t; * here and have via_do_nubus call that hook if set. &n;&t; *&n;&t; * Quadra needs the hook, Powerbook can use Nubus slot C. &n;&t; * Checking the ISR on Quadra is done by mac_ack_intr (see Amiga code). mac_ide_intr&n;&t; * mac_ide_intr is obsolete except for providing the hwgroup argument.&n;&t; */
multiline_comment|/* The Mac hwif data, for passing hwgroup to ide_intr */
DECL|variable|mac_hwif
r_static
id|ide_hwif_t
op_star
id|mac_hwif
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* The function pointer used in the Nubus handler */
DECL|variable|mac_ide_intr_hook
r_void
(paren
op_star
id|mac_ide_intr_hook
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Only purpose: feeds the hwgroup to the main IDE handler. &n;&t; * Obsolete as soon as Nubus code is fixed WRT pseudo slot C int.&n;&t; * (should be the case on Powerbooks)&n;&t; * Alas, second purpose: feed correct irq to IDE handler (I know,&n;&t; * that&squot;s cheating) :-(((&n;&t; * Fix needed for interrupt code: accept Nubus ints in the regular&n;&t; * request_irq code, then register Powerbook IDE as Nubus slot C, &n;&t; * Quadra as slot F (F for fictious).&n;&t; */
DECL|function|mac_ide_intr
r_void
id|mac_ide_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|ide_intr
c_func
(paren
id|mac_hwif-&gt;irq
comma
id|mac_hwif-&gt;hwgroup
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Check the interrupt status&n;     *&n;     *  Note: In 2.0 kernels, there have been timing problems with the &n;     *  Powerbook IDE interface (BUSY was asserted too long after the&n;     *  interrupt triggered). Result: repeated errors, recalibrate etc. &n;     *  Adding a wait loop to read_intr, write_intr and set_geom_intr&n;     *  fixed the problem (waits in read/write_intr were present for Amiga&n;     *  already). &n;     *  Powerbooks were not tested with 2.1 due to lack of FPU emulation&n;     *  (thanks Apple for using LC040). If the BUSY problem resurfaces in &n;     *  2.1, my best bet would be to add the wait loop right here, afterr&n;     *  checking the interrupt register.&n;     */
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
id|ch
suffix:semicolon
id|ch
op_assign
id|inb
c_func
(paren
id|hwif-&gt;io_ports
(braket
id|IDE_IRQ_OFFSET
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch
op_amp
l_int|0x20
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
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
id|MACH_IS_MAC
)paren
(brace
r_switch
c_cond
(paren
id|macintosh_config-&gt;ide_type
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
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
id|IRQ_MAC_NUBUS
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
op_amp
id|mac_hwif
)paren
suffix:semicolon
id|mac_ide_intr_hook
op_assign
id|mac_ide_intr
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
id|IRQ_MAC_NUBUS
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
op_amp
id|mac_hwif
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
)brace
eof
