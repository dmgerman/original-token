multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_ruffian.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999, 2000 Richard Henderson&n; *&n; * Code supporting the RUFFIAN.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
r_static
r_void
id|__init
DECL|function|ruffian_init_irq
id|ruffian_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Invert 6&amp;7 for i82371 */
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_HILO
op_assign
l_int|0x000000c0UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vulp
)paren
id|PYXIS_INT_CNFG
op_assign
l_int|0x00002064UL
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all clear */
id|outb
c_func
(paren
l_int|0x11
comma
l_int|0xA0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x02
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x11
comma
l_int|0x20
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x04
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* Finish writing the 82C59A PIC Operation Control Words */
id|outb
c_func
(paren
l_int|0x20
comma
l_int|0xA0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
l_int|0x20
)paren
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Not interested in the bogus interrupts (0,3,6),&n;&t;   NMI (1), HALT (2), flash (5), or 21142 (8).  */
id|init_pyxis_irqs
c_func
(paren
l_int|0x16f0000
)paren
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|ruffian_init_rtc
id|ruffian_init_rtc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Ruffian does not have the RTC connected to the CPU timer&n;&t;   interrupt.  Instead, it uses the PIT connected to IRQ 0.  */
multiline_comment|/* Setup interval timer.  */
id|outb
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|outb
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|outb
c_func
(paren
l_int|0xb6
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* pit counter 2: speaker */
id|outb
c_func
(paren
l_int|0x31
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x13
comma
l_int|0x42
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|0
comma
op_amp
id|timer_irqaction
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ruffian_kill_arch
id|ruffian_kill_arch
(paren
r_int
id|mode
)paren
(brace
macro_line|#if 0
multiline_comment|/* This only causes re-entry to ARCSBIOS */
multiline_comment|/* Perhaps this works for other PYXIS as well?  */
op_star
(paren
id|vuip
)paren
id|PYXIS_RESET
op_assign
l_int|0x0000dead
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_static
r_int
id|__init
DECL|function|ruffian_map_irq
id|ruffian_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
multiline_comment|/* We don&squot;t know anything about the PCI routing, so leave&n;&t;   the IRQ unchanged.  */
r_return
id|dev-&gt;irq
suffix:semicolon
)brace
macro_line|#ifdef BUILDING_FOR_MILO
multiline_comment|/*&n; * The DeskStation Ruffian motherboard firmware does not place&n; * the memory size in the PALimpure area.  Therefore, we use&n; * the Bank Configuration Registers in PYXIS to obtain the size.&n; */
r_static
r_int
r_int
id|__init
DECL|function|ruffian_get_bank_size
id|ruffian_get_bank_size
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
id|bank_addr
comma
id|bank
comma
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Valid offsets are: 0x800, 0x840 and 0x880&n;&t;   since Ruffian only uses three banks.  */
id|bank_addr
op_assign
(paren
r_int
r_int
)paren
id|PYXIS_MCR
op_plus
id|offset
suffix:semicolon
id|bank
op_assign
op_star
(paren
id|vulp
)paren
id|bank_addr
suffix:semicolon
multiline_comment|/* Check BANK_ENABLE */
r_if
c_cond
(paren
id|bank
op_amp
l_int|0x01
)paren
(brace
r_static
r_int
r_int
id|size
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x40000000UL
comma
multiline_comment|/* 0x00,   1G */
l_int|0x20000000UL
comma
multiline_comment|/* 0x02, 512M */
l_int|0x10000000UL
comma
multiline_comment|/* 0x04, 256M */
l_int|0x08000000UL
comma
multiline_comment|/* 0x06, 128M */
l_int|0x04000000UL
comma
multiline_comment|/* 0x08,  64M */
l_int|0x02000000UL
comma
multiline_comment|/* 0x0a,  32M */
l_int|0x01000000UL
comma
multiline_comment|/* 0x0c,  16M */
l_int|0x00800000UL
comma
multiline_comment|/* 0x0e,   8M */
l_int|0x80000000UL
comma
multiline_comment|/* 0x10,   2G */
)brace
suffix:semicolon
id|bank
op_assign
(paren
id|bank
op_amp
l_int|0x1e
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bank
OL
r_sizeof
(paren
id|size
)paren
op_div
r_sizeof
(paren
op_star
id|size
)paren
)paren
id|ret
op_assign
id|size
(braket
id|bank
)braket
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* BUILDING_FOR_MILO */
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|ruffian_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Ruffian&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_PYXIS_IO
comma
id|DO_CIA_BUS
comma
id|machine_check
suffix:colon
id|cia_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_RUFFIAN_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|pyxis_device_interrupt
comma
id|init_arch
suffix:colon
id|pyxis_init_arch
comma
id|init_irq
suffix:colon
id|ruffian_init_irq
comma
id|init_rtc
suffix:colon
id|ruffian_init_rtc
comma
id|init_pci
suffix:colon
id|cia_init_pci
comma
id|kill_arch
suffix:colon
id|ruffian_kill_arch
comma
id|pci_map_irq
suffix:colon
id|ruffian_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|ruffian
)paren
eof
