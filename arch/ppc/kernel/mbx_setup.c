multiline_comment|/*&n; *  linux/arch/ppc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; *  Modified for MBX using prep/chrp/pmac functions by Dan (dmalek@jlc.net)&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ide.h&gt;
macro_line|#include &lt;asm/mbx.h&gt;
r_extern
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|variable|empty_zero_page
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#endif
r_extern
r_char
id|saved_command_line
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_int
id|find_available_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mbx_cpm_reset
c_func
(paren
id|uint
)paren
suffix:semicolon
DECL|function|mbx_ide_init_hwif_ports
r_void
id|mbx_ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
(brace
op_star
id|p
op_assign
l_int|0
suffix:semicolon
op_star
id|irq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ne
l_int|0
)paren
multiline_comment|/* Only map the first ATA flash drive */
r_return
suffix:semicolon
macro_line|#ifdef ATA_FLASH
id|base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|PCMCIA_MEM_ADDR
comma
l_int|0x200
)paren
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
l_int|8
suffix:semicolon
op_increment
id|i
)paren
op_star
id|p
op_increment
op_assign
id|base
op_increment
suffix:semicolon
op_star
id|p
op_assign
op_increment
id|base
suffix:semicolon
multiline_comment|/* Does not matter */
r_if
c_cond
(paren
id|irq
)paren
op_star
id|irq
op_assign
l_int|13
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|mbx_get_cpuinfo
id|mbx_get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|pvr
op_assign
id|_get_PVR
c_func
(paren
)paren
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
op_star
id|model
suffix:semicolon
id|bd_t
op_star
id|bp
suffix:semicolon
r_extern
id|RESIDUAL
id|res
suffix:semicolon
multiline_comment|/* I know the MPC860 is 0x50.  I don&squot;t have the book handy&n;&t; * to check the others.&n;&t; */
r_if
c_cond
(paren
(paren
id|pvr
op_rshift
l_int|16
)paren
op_eq
l_int|0x50
)paren
id|model
op_assign
l_string|&quot;MPC860&quot;
suffix:semicolon
r_else
id|model
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
macro_line|#ifdef __SMP__
DECL|macro|CD
mdefine_line|#define CD(X)&t;&t;(cpu_data[n].X)  
macro_line|#else
mdefine_line|#define CD(X) (X)
mdefine_line|#define CPUN 0
macro_line|#endif
id|bp
op_assign
(paren
id|bd_t
op_star
)paren
op_amp
id|res
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;revision&bslash;t: %d.%d&bslash;n&quot;
l_string|&quot;clock&bslash;t&bslash;t: %d MHz&bslash;n&quot;
l_string|&quot;bus clock&bslash;t: %d MHz&bslash;n&quot;
comma
id|CPUN
comma
id|model
comma
id|MAJOR
c_func
(paren
id|pvr
)paren
comma
id|MINOR
c_func
(paren
id|pvr
)paren
comma
id|bp-&gt;bi_intfreq
op_div
l_int|1000000
comma
id|bp-&gt;bi_busfreq
op_div
l_int|1000000
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|mbx_setup_arch
c_func
(paren
r_int
r_int
op_star
id|memory_start_p
comma
r_int
r_int
op_star
id|memory_end_p
)paren
)paren
(brace
r_int
id|cpm_page
suffix:semicolon
id|cpm_page
op_assign
op_star
id|memory_start_p
suffix:semicolon
op_star
id|memory_start_p
op_add_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* Reset the Communication Processor Module.&n;&t;*/
id|mbx_cpm_reset
c_func
(paren
id|cpm_page
)paren
suffix:semicolon
macro_line|#ifdef notdef
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0301
)paren
suffix:semicolon
multiline_comment|/* hda1 */
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#if 0
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0200
)paren
suffix:semicolon
multiline_comment|/* floppy */
id|rd_prompt
op_assign
l_int|1
suffix:semicolon
id|rd_doload
op_assign
l_int|1
suffix:semicolon
id|rd_image_start
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* initrd_start and size are setup by boot/head.S and kernel/head.S */
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
r_if
c_cond
(paren
id|initrd_end
OG
op_star
id|memory_end_p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#ifdef notdef
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|abort
m_abort
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_XMON
r_extern
r_void
id|xmon
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
eof
