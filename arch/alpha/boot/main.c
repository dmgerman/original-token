multiline_comment|/*&n; * arch/alpha/boot/main.c&n; *&n; * Copyright (C) 1994, 1995 Linus Torvalds&n; *&n; * This file is the bootloader for the Linux/AXP kernel&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;stdarg.h&gt;
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
r_extern
r_int
r_int
id|switch_to_osf_pal
c_func
(paren
r_int
r_int
id|nr
comma
r_struct
id|pcb_struct
op_star
id|pcb_va
comma
r_struct
id|pcb_struct
op_star
id|pcb_pa
comma
r_int
r_int
id|vptb
comma
r_int
r_int
op_star
id|kstk
)paren
suffix:semicolon
DECL|function|printk
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|puts
c_func
(paren
id|buf
comma
id|i
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|macro|hwrpb
mdefine_line|#define hwrpb (*INIT_HWRPB)
multiline_comment|/*&n; * Find a physical address of a virtual object..&n; *&n; * This is easy using the virtual page table address.&n; */
DECL|function|find_pa
r_struct
id|pcb_struct
op_star
id|find_pa
c_func
(paren
r_int
r_int
op_star
id|vptb
comma
r_struct
id|pcb_struct
op_star
id|pcb
)paren
(brace
r_int
r_int
id|address
op_assign
(paren
r_int
r_int
)paren
id|pcb
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|result
op_assign
id|vptb
(braket
id|address
op_rshift
l_int|13
)braket
suffix:semicolon
id|result
op_rshift_assign
l_int|32
suffix:semicolon
id|result
op_lshift_assign
l_int|13
suffix:semicolon
id|result
op_or_assign
id|address
op_amp
l_int|0x1fff
suffix:semicolon
r_return
(paren
r_struct
id|pcb_struct
op_star
)paren
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This function moves into OSF/1 pal-code, and has a temporary&n; * PCB for that. The kernel proper should replace this PCB with&n; * the real one as soon as possible.&n; *&n; * The page table muckery in here depends on the fact that the boot&n; * code has the L1 page table identity-map itself in the second PTE&n; * in the L1 page table. Thus the L1-page is virtually addressable&n; * itself (through three levels) at virtual address 0x200802000.&n; *&n; * As we don&squot;t want it there anyway, we also move the L1 self-map&n; * up as high as we can, so that the last entry in the L1 page table&n; * maps the page tables.&n; *&n; * As a result, the OSF/1 pal-code will instead use a virtual page table&n; * map located at 0xffffffe00000000.&n; */
DECL|macro|pcb_va
mdefine_line|#define pcb_va ((struct pcb_struct *) 0x20000000)
DECL|macro|old_vptb
mdefine_line|#define old_vptb (0x0000000200000000UL)
DECL|macro|new_vptb
mdefine_line|#define new_vptb (0xfffffffe00000000UL)
DECL|function|pal_init
r_void
id|pal_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|rev
comma
id|sum
suffix:semicolon
r_int
r_int
op_star
id|L1
comma
op_star
id|l
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|percpu
suffix:semicolon
r_struct
id|pcb_struct
op_star
id|pcb_pa
suffix:semicolon
multiline_comment|/* Find the level 1 page table and duplicate it in high memory */
id|L1
op_assign
(paren
r_int
r_int
op_star
)paren
l_int|0x200802000UL
suffix:semicolon
multiline_comment|/* (1&lt;&lt;33 | 1&lt;&lt;23 | 1&lt;&lt;13) */
id|L1
(braket
l_int|1023
)braket
op_assign
id|L1
(braket
l_int|1
)braket
suffix:semicolon
id|percpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
id|hwrpb.processor_offset
op_plus
(paren
r_int
r_int
)paren
op_amp
id|hwrpb
)paren
comma
id|pcb_va-&gt;ksp
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;usp
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;ptbr
op_assign
id|L1
(braket
l_int|1
)braket
op_rshift
l_int|32
suffix:semicolon
id|pcb_va-&gt;asn
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;pcc
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;unique
op_assign
l_int|0
suffix:semicolon
id|pcb_va-&gt;flags
op_assign
l_int|1
suffix:semicolon
id|pcb_pa
op_assign
id|find_pa
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|old_vptb
comma
id|pcb_va
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Switching to OSF PAL-code .. &quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * a0 = 2 (OSF)&n;&t; * a1 = return address, but we give the asm the virtual addr of the PCB&n;&t; * a2 = physical addr of PCB&n;&t; * a3 = new virtual page table pointer&n;&t; * a4 = KSP (but we give it 0, asm sets it)&n;&t; */
id|i
op_assign
id|switch_to_osf_pal
c_func
(paren
l_int|2
comma
id|pcb_va
comma
id|pcb_pa
comma
id|new_vptb
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;failed, code %ld&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|rev
op_assign
id|percpu-&gt;pal_revision
op_assign
id|percpu-&gt;palcode_avail
(braket
l_int|2
)braket
suffix:semicolon
id|hwrpb.vptb
op_assign
id|new_vptb
suffix:semicolon
multiline_comment|/* update checksum: */
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|hwrpb
suffix:semicolon
id|l
OL
(paren
r_int
r_int
op_star
)paren
op_amp
id|hwrpb.chksum
suffix:semicolon
op_increment
id|l
)paren
id|sum
op_add_assign
op_star
id|l
suffix:semicolon
id|hwrpb.chksum
op_assign
id|sum
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Ok (rev %lx)&bslash;n&quot;
comma
id|rev
)paren
suffix:semicolon
multiline_comment|/* remove the old virtual page-table mapping */
id|L1
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|invalidate_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_int
id|_end
suffix:semicolon
DECL|function|openboot
r_static
r_inline
r_int
id|openboot
c_func
(paren
r_void
)paren
(brace
r_char
id|bootdev
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
op_assign
id|dispatch
c_func
(paren
id|CCB_GET_ENV
comma
id|ENV_BOOTED_DEV
comma
id|bootdev
comma
l_int|255
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
r_return
id|dispatch
c_func
(paren
id|CCB_OPEN
comma
id|bootdev
comma
id|result
op_amp
l_int|255
)paren
suffix:semicolon
)brace
DECL|function|close
r_static
r_inline
r_int
id|close
c_func
(paren
r_int
id|dev
)paren
(brace
r_return
id|dispatch
c_func
(paren
id|CCB_CLOSE
comma
id|dev
)paren
suffix:semicolon
)brace
DECL|function|load
r_static
r_inline
r_int
id|load
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|count
)paren
(brace
r_char
id|bootfile
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|result
op_assign
id|dispatch
c_func
(paren
id|CCB_GET_ENV
comma
id|ENV_BOOTED_FILE
comma
id|bootfile
comma
l_int|255
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_return
id|result
suffix:semicolon
id|result
op_and_assign
l_int|255
suffix:semicolon
id|bootfile
(braket
id|result
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|printk
c_func
(paren
l_string|&quot;Boot file specification (%s) not implemented&bslash;n&quot;
comma
id|bootfile
)paren
suffix:semicolon
r_return
id|dispatch
c_func
(paren
id|CCB_READ
comma
id|dev
comma
id|count
comma
id|addr
comma
id|BOOT_SIZE
op_div
l_int|512
op_plus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the kernel.&n; */
DECL|function|runkernel
r_static
r_void
id|runkernel
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;bis %1,%1,$30&bslash;n&bslash;t&quot;
l_string|&quot;bis %0,%0,$26&bslash;n&bslash;t&quot;
l_string|&quot;ret ($26)&quot;
suffix:colon
multiline_comment|/* no outputs: it doesn&squot;t even return */
suffix:colon
l_string|&quot;r&quot;
(paren
id|START_ADDR
)paren
comma
l_string|&quot;r&quot;
(paren
id|PAGE_SIZE
op_plus
id|INIT_STACK
)paren
)paren
suffix:semicolon
)brace
DECL|function|start_kernel
r_void
id|start_kernel
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_int
id|nbytes
suffix:semicolon
r_char
id|envval
(braket
l_int|256
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Linux/AXP bootloader for Linux &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwrpb.pagesize
op_ne
l_int|8192
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Expected 8kB pages, got %ldkB&bslash;n&quot;
comma
id|hwrpb.pagesize
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pal_init
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|openboot
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to open boot device: %016lx&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Loading vmlinux ...&quot;
)paren
suffix:semicolon
id|i
op_assign
id|load
c_func
(paren
id|dev
comma
id|START_ADDR
comma
id|START_SIZE
)paren
suffix:semicolon
id|close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|START_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed (%lx)&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|nbytes
op_assign
id|dispatch
c_func
(paren
id|CCB_GET_ENV
comma
id|ENV_BOOTED_OSFLAGS
comma
id|envval
comma
r_sizeof
(paren
id|envval
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OG
l_int|0
)paren
(brace
id|envval
(braket
id|nbytes
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|strcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|ZERO_PGE
comma
id|envval
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; Ok&bslash;nNow booting the kernel&bslash;n&quot;
)paren
suffix:semicolon
id|runkernel
c_func
(paren
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
l_int|0x100000000
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* nothing */
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
eof