multiline_comment|/* $Id: floppy.h,v 1.1 1996/11/20 15:31:07 davem Exp $&n; * asm-sparc64/floppy.h: Sparc specific parts of the Floppy driver.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC64_FLOPPY_H
DECL|macro|__ASM_SPARC64_FLOPPY_H
mdefine_line|#define __ASM_SPARC64_FLOPPY_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/machines.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* References:&n; * 1) Netbsd Sun floppy driver.&n; * 2) NCR 82077 controller manual&n; * 3) Intel 82077 controller manual&n; */
DECL|struct|sun_flpy_controller
r_struct
id|sun_flpy_controller
(brace
DECL|member|status_82072
r_volatile
r_int
r_char
id|status_82072
suffix:semicolon
multiline_comment|/* Main Status reg. */
DECL|macro|dcr_82072
mdefine_line|#define dcr_82072              status_82072   /* Digital Control reg. */
DECL|macro|status1_82077
mdefine_line|#define status1_82077          status_82072   /* Auxiliary Status reg. 1 */
DECL|member|data_82072
r_volatile
r_int
r_char
id|data_82072
suffix:semicolon
multiline_comment|/* Data fifo. */
DECL|macro|status2_82077
mdefine_line|#define status2_82077          data_82072     /* Auxiliary Status reg. 2 */
DECL|member|dor_82077
r_volatile
r_int
r_char
id|dor_82077
suffix:semicolon
multiline_comment|/* Digital Output reg. */
DECL|member|tapectl_82077
r_volatile
r_int
r_char
id|tapectl_82077
suffix:semicolon
multiline_comment|/* What the? Tape control reg? */
DECL|member|status_82077
r_volatile
r_int
r_char
id|status_82077
suffix:semicolon
multiline_comment|/* Main Status Register. */
DECL|macro|drs_82077
mdefine_line|#define drs_82077              status_82077   /* Digital Rate Select reg. */
DECL|member|data_82077
r_volatile
r_int
r_char
id|data_82077
suffix:semicolon
multiline_comment|/* Data fifo. */
DECL|member|___unused
r_volatile
r_int
r_char
id|___unused
suffix:semicolon
DECL|member|dir_82077
r_volatile
r_int
r_char
id|dir_82077
suffix:semicolon
multiline_comment|/* Digital Input reg. */
DECL|macro|dcr_82077
mdefine_line|#define dcr_82077              dir_82077      /* Config Control reg. */
)brace
suffix:semicolon
multiline_comment|/* You&squot;ll only ever find one controller on a SparcStation anyways. */
DECL|variable|sun_fdc
r_static
r_struct
id|sun_flpy_controller
op_star
id|sun_fdc
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|fdc_status
r_volatile
r_int
r_char
op_star
id|fdc_status
suffix:semicolon
DECL|struct|sun_floppy_ops
r_struct
id|sun_floppy_ops
(brace
DECL|member|fd_inb
r_int
r_char
(paren
op_star
id|fd_inb
)paren
(paren
r_int
id|port
)paren
suffix:semicolon
DECL|member|fd_outb
r_void
(paren
op_star
id|fd_outb
)paren
(paren
r_int
r_char
id|value
comma
r_int
id|port
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sun_fdops
r_static
r_struct
id|sun_floppy_ops
id|sun_fdops
suffix:semicolon
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)              sun_fdops.fd_inb(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(value,port)       sun_fdops.fd_outb(value,port)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()           sun_fd_enable_dma()
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()          sun_fd_disable_dma()
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()          (0) /* nothing... */
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()             /* nothing... */
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()         /* nothing... */
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)     sun_fd_set_dma_mode(mode)
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)     sun_fd_set_dma_addr(addr)
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(count)   sun_fd_set_dma_count(count)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()           /* nothing... */
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()          /* nothing... */
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr, size) /* nothing... */
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()          sun_fd_request_irq()
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()             /* nothing... */
macro_line|#if 0  /* P3: added by Alain, these cause a MMU corruption. 19960524 XXX */
mdefine_line|#define fd_dma_mem_alloc(size)    ((unsigned long) vmalloc(size))
mdefine_line|#define fd_dma_mem_free(addr,size) (vfree((void *)(addr)))
macro_line|#endif
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK         0x10
multiline_comment|/* It&squot;s all the same... */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(x)            (x)
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(x)            (x)
multiline_comment|/* XXX This isn&squot;t really correct. XXX */
DECL|macro|get_dma_residue
mdefine_line|#define get_dma_residue(x)        (0)
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE  4
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE  0
multiline_comment|/* Super paranoid... */
DECL|macro|HAVE_DISABLE_HLT
macro_line|#undef HAVE_DISABLE_HLT
multiline_comment|/* Here is where we catch the floppy driver trying to initialize,&n; * therefore this is where we call the PROM device tree probing&n; * routine etc. on the Sparc.&n; */
DECL|macro|FDC1
mdefine_line|#define FDC1                      sun_floppy_init()
DECL|variable|FDC2
r_static
r_int
id|FDC2
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|N_FDC
mdefine_line|#define N_FDC    1
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE  8
multiline_comment|/* No 64k boundary crossing problems on the Sparc. */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) (0)
multiline_comment|/* Routines unique to each controller type on a Sun. */
DECL|function|sun_82072_fd_inb
r_static
r_int
r_char
id|sun_82072_fd_inb
c_func
(paren
r_int
id|port
)paren
(brace
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to read unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
r_return
id|sun_fdc-&gt;status_82072
op_amp
op_complement
id|STATUS_DMA
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
r_return
id|sun_fdc-&gt;data_82072
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DIR */
r_return
(paren
op_star
id|AUXREG
op_amp
id|AUXIO_FLPY_DCHG
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;sun_82072_fd_inb: How did I get here?&quot;
)paren
suffix:semicolon
)brace
DECL|function|sun_82072_fd_outb
r_static
r_void
id|sun_82072_fd_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
id|port
)paren
(brace
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to write to unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* FD_DOR */
multiline_comment|/* Oh geese, 82072 on the Sun has no DOR register,&n;&t;&t; * the functionality is implemented via the AUXIO&n;&t;&t; * I/O register.  So we must emulate the behavior.&n;&t;&t; *&n;&t;&t; * ASSUMPTIONS:  There will only ever be one floppy&n;&t;&t; *               drive attached to a Sun controller&n;&t;&t; *               and it will be at drive zero.&n;&t;&t; */
(brace
r_int
id|bits
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x10
)paren
id|bits
op_or_assign
id|AUXIO_FLPY_DSEL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|bits
op_or_assign
id|AUXIO_FLPY_EJCT
suffix:semicolon
id|set_auxio
c_func
(paren
id|bits
comma
(paren
op_complement
id|bits
)paren
op_amp
(paren
id|AUXIO_FLPY_DSEL
op_or
id|AUXIO_FLPY_EJCT
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
id|sun_fdc-&gt;data_82072
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DCR */
id|sun_fdc-&gt;dcr_82072
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
id|sun_fdc-&gt;status_82072
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sun_82077_fd_inb
r_static
r_int
r_char
id|sun_82077_fd_inb
c_func
(paren
r_int
id|port
)paren
(brace
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to read unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
r_return
id|sun_fdc-&gt;status_82077
op_amp
op_complement
id|STATUS_DMA
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
r_return
id|sun_fdc-&gt;data_82077
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DIR */
multiline_comment|/* XXX: Is DCL on 0x80 in sun4m? */
r_return
id|sun_fdc-&gt;dir_82077
suffix:semicolon
)brace
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;sun_82072_fd_inb: How did I get here?&quot;
)paren
suffix:semicolon
)brace
DECL|function|sun_82077_fd_outb
r_static
r_void
id|sun_82077_fd_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
id|port
)paren
(brace
r_switch
c_cond
(paren
id|port
op_amp
l_int|7
)paren
(brace
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;floppy: Asked to write to unknown port %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Port bolixed.&quot;
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* FD_DOR */
multiline_comment|/* Happily, the 82077 has a real DOR register. */
id|sun_fdc-&gt;dor_82077
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* FD_DATA */
id|sun_fdc-&gt;data_82077
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/* FD_DCR */
id|sun_fdc-&gt;dcr_82077
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* FD_STATUS */
id|sun_fdc-&gt;status_82077
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* For pseudo-dma (Sun floppy drives have no real DMA available to&n; * them so we must eat the data fifo bytes directly ourselves) we have&n; * three state variables.  doing_pdma tells our inline low-level&n; * assembly floppy interrupt entry point whether it should sit and eat&n; * bytes from the fifo or just transfer control up to the higher level&n; * floppy interrupt c-code.  I tried very hard but I could not get the&n; * pseudo-dma to work in c-code without getting many overruns and&n; * underruns.  If non-zero, doing_pdma encodes the direction of&n; * the transfer for debugging.  1=read 2=write&n; */
DECL|variable|pdma_vaddr
r_char
op_star
id|pdma_vaddr
suffix:semicolon
DECL|variable|pdma_size
r_int
r_int
id|pdma_size
suffix:semicolon
DECL|variable|doing_pdma
r_volatile
r_int
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is software state */
DECL|variable|pdma_base
r_char
op_star
id|pdma_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|pdma_areasize
r_int
r_int
id|pdma_areasize
suffix:semicolon
multiline_comment|/* Common routines to all controller types on the Sparc. */
DECL|function|virtual_dma_init
r_static
id|__inline__
r_void
id|virtual_dma_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing... */
)brace
DECL|function|sun_fd_disable_dma
r_static
id|__inline__
r_void
id|sun_fd_disable_dma
c_func
(paren
r_void
)paren
(brace
id|doing_pdma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pdma_base
)paren
(brace
id|mmu_unlockarea
c_func
(paren
id|pdma_base
comma
id|pdma_areasize
)paren
suffix:semicolon
id|pdma_base
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|sun_fd_set_dma_mode
r_static
id|__inline__
r_void
id|sun_fd_set_dma_mode
c_func
(paren
r_int
id|mode
)paren
(brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|DMA_MODE_READ
suffix:colon
id|doing_pdma
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_MODE_WRITE
suffix:colon
id|doing_pdma
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown dma mode %d&bslash;n&quot;
comma
id|mode
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;floppy: Giving up...&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|sun_fd_set_dma_addr
r_static
id|__inline__
r_void
id|sun_fd_set_dma_addr
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
id|pdma_vaddr
op_assign
id|buffer
suffix:semicolon
)brace
DECL|function|sun_fd_set_dma_count
r_static
id|__inline__
r_void
id|sun_fd_set_dma_count
c_func
(paren
r_int
id|length
)paren
(brace
id|pdma_size
op_assign
id|length
suffix:semicolon
)brace
DECL|function|sun_fd_enable_dma
r_static
id|__inline__
r_void
id|sun_fd_enable_dma
c_func
(paren
r_void
)paren
(brace
id|pdma_vaddr
op_assign
id|mmu_lockarea
c_func
(paren
id|pdma_vaddr
comma
id|pdma_size
)paren
suffix:semicolon
id|pdma_base
op_assign
id|pdma_vaddr
suffix:semicolon
id|pdma_areasize
op_assign
id|pdma_size
suffix:semicolon
)brace
multiline_comment|/* Our low-level entry point in arch/sparc/kernel/entry.S */
r_extern
r_void
id|floppy_hardint
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|unused
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|function|sun_fd_request_irq
r_static
r_int
id|sun_fd_request_irq
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|once
)paren
(brace
id|once
op_assign
l_int|1
suffix:semicolon
id|error
op_assign
id|request_fast_irq
c_func
(paren
id|FLOPPY_IRQ
comma
id|floppy_hardint
comma
id|SA_INTERRUPT
comma
l_string|&quot;floppy&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
id|error
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|fd_regs
r_static
r_struct
id|linux_prom_registers
id|fd_regs
(braket
l_int|2
)braket
suffix:semicolon
DECL|function|sun_floppy_init
r_static
r_int
id|sun_floppy_init
c_func
(paren
r_void
)paren
(brace
r_char
id|state
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|tnode
comma
id|fd_node
comma
id|num_regs
suffix:semicolon
id|use_virtual_dma
op_assign
l_int|1
suffix:semicolon
id|FLOPPY_IRQ
op_assign
l_int|11
suffix:semicolon
multiline_comment|/* Forget it if we aren&squot;t on a machine that could possibly&n;&t; * ever have a floppy drive.&n;&t; */
r_if
c_cond
(paren
(paren
id|sparc_cpu_model
op_ne
id|sun4c
op_logical_and
id|sparc_cpu_model
op_ne
id|sun4m
)paren
op_logical_or
(paren
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4C
op_or
id|SM_4C_SLC
)paren
)paren
op_logical_or
(paren
id|idprom-&gt;id_machtype
op_eq
(paren
id|SM_SUN4C
op_or
id|SM_4C_ELC
)paren
)paren
)paren
)paren
(brace
multiline_comment|/* We certainly don&squot;t have a floppy controller. */
r_goto
id|no_sun_fdc
suffix:semicolon
)brace
multiline_comment|/* Well, try to find one. */
id|tnode
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|fd_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|tnode
comma
l_string|&quot;obio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd_node
op_ne
l_int|0
)paren
(brace
id|tnode
op_assign
id|prom_getchild
c_func
(paren
id|fd_node
)paren
suffix:semicolon
id|fd_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|tnode
comma
l_string|&quot;SUNW,fdtwo&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|fd_node
op_assign
id|prom_searchsiblings
c_func
(paren
id|tnode
comma
l_string|&quot;fd&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fd_node
op_eq
l_int|0
)paren
(brace
r_goto
id|no_sun_fdc
suffix:semicolon
)brace
multiline_comment|/* The sun4m lets us know if the controller is actually usable. */
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4m
)paren
(brace
id|prom_getproperty
c_func
(paren
id|fd_node
comma
l_string|&quot;status&quot;
comma
id|state
comma
r_sizeof
(paren
id|state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|state
comma
l_string|&quot;disabled&quot;
)paren
)paren
(brace
r_goto
id|no_sun_fdc
suffix:semicolon
)brace
)brace
id|num_regs
op_assign
id|prom_getproperty
c_func
(paren
id|fd_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
id|fd_regs
comma
r_sizeof
(paren
id|fd_regs
)paren
)paren
suffix:semicolon
id|num_regs
op_assign
(paren
id|num_regs
op_div
r_sizeof
(paren
id|fd_regs
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|prom_apply_obio_ranges
c_func
(paren
id|fd_regs
comma
id|num_regs
)paren
suffix:semicolon
id|sun_fdc
op_assign
(paren
r_struct
id|sun_flpy_controller
op_star
)paren
id|sparc_alloc_io
c_func
(paren
id|fd_regs
(braket
l_int|0
)braket
dot
id|phys_addr
comma
l_int|0x0
comma
id|fd_regs
(braket
l_int|0
)braket
dot
id|reg_size
comma
l_string|&quot;floppy&quot;
comma
id|fd_regs
(braket
l_int|0
)braket
dot
id|which_io
comma
l_int|0x0
)paren
suffix:semicolon
multiline_comment|/* Last minute sanity check... */
r_if
c_cond
(paren
id|sun_fdc-&gt;status_82072
op_eq
l_int|0xff
)paren
(brace
id|sun_fdc
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|no_sun_fdc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sparc_cpu_model
op_eq
id|sun4c
)paren
(brace
id|sun_fdops.fd_inb
op_assign
id|sun_82072_fd_inb
suffix:semicolon
id|sun_fdops.fd_outb
op_assign
id|sun_82072_fd_outb
suffix:semicolon
id|fdc_status
op_assign
op_amp
id|sun_fdc-&gt;status_82072
suffix:semicolon
multiline_comment|/* printk(&quot;AUXIO @0x%p&bslash;n&quot;, auxio_register); */
multiline_comment|/* P3 */
)brace
r_else
(brace
id|sun_fdops.fd_inb
op_assign
id|sun_82077_fd_inb
suffix:semicolon
id|sun_fdops.fd_outb
op_assign
id|sun_82077_fd_outb
suffix:semicolon
id|fdc_status
op_assign
op_amp
id|sun_fdc-&gt;status_82077
suffix:semicolon
multiline_comment|/* printk(&quot;DOR @0x%p&bslash;n&quot;, &amp;sun_fdc-&gt;dor_82077); */
multiline_comment|/* P3 */
)brace
multiline_comment|/* Success... */
r_return
(paren
r_int
)paren
id|sun_fdc
suffix:semicolon
id|no_sun_fdc
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|sparc_eject
r_static
r_int
id|sparc_eject
c_func
(paren
r_void
)paren
(brace
id|set_dor
c_func
(paren
l_int|0x00
comma
l_int|0xff
comma
l_int|0x90
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
id|set_dor
c_func
(paren
l_int|0x00
comma
l_int|0x6f
comma
l_int|0x00
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|fd_eject
mdefine_line|#define fd_eject(drive) sparc_eject()
macro_line|#endif /* !(__ASM_SPARC64_FLOPPY_H) */
eof