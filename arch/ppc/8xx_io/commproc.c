multiline_comment|/*&n; * General Purpose functions for the global management of the&n; * Communication Processor Module.&n; * Copyright (c) 1997 Dan Malek (dmalek@jlc.net)&n; *&n; * In addition to the individual control of the communication&n; * channels, there are a few functions that globally affect the&n; * communication processor.&n; *&n; * Buffer descriptors must be allocated from the dual ported memory&n; * space.  The allocator for that is here.  When the communication&n; * process is reset, we reclaim the memory available.  There is&n; * currently no deallocator for this memory.&n; * The amount of space available is platform dependent.  On the&n; * MBX, the EPPC software loads additional microcode into the&n; * communication processor, and uses some of the DP ram for this&n; * purpose.  Current, the first 512 bytes and the last 256 bytes of&n; * memory are used.  Right now I am conservative and only use the&n; * memory that can never be used for microcode.  If there are&n; * applications that require more DP ram, we can expand the boundaries&n; * but then we have to be careful of any downloaded microcode.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mbx.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &quot;commproc.h&quot;
DECL|variable|dp_alloc_base
r_static
id|uint
id|dp_alloc_base
suffix:semicolon
multiline_comment|/* Starting offset in DP ram */
DECL|variable|dp_alloc_top
r_static
id|uint
id|dp_alloc_top
suffix:semicolon
multiline_comment|/* Max offset + 1 */
DECL|variable|host_buffer
r_static
id|uint
id|host_buffer
suffix:semicolon
multiline_comment|/* One page of host buffer */
DECL|variable|host_end
r_static
id|uint
id|host_end
suffix:semicolon
multiline_comment|/* end + 1 */
DECL|variable|cpmp
id|cpm8xx_t
op_star
id|cpmp
suffix:semicolon
multiline_comment|/* Pointer to comm processor space */
multiline_comment|/* CPM interrupt vector functions.&n;*/
DECL|struct|cpm_action
r_struct
id|cpm_action
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|cpm_vecs
r_static
r_struct
id|cpm_action
id|cpm_vecs
(braket
id|CPMVEC_NR
)braket
suffix:semicolon
r_static
r_void
id|cpm_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|cpm_error_interrupt
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
DECL|function|mbx_cpm_reset
id|mbx_cpm_reset
c_func
(paren
id|uint
id|host_page_addr
)paren
(brace
r_volatile
id|immap_t
op_star
id|imp
suffix:semicolon
r_volatile
id|cpm8xx_t
op_star
id|commproc
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|imp
op_assign
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
suffix:semicolon
id|commproc
op_assign
(paren
id|cpm8xx_t
op_star
)paren
op_amp
id|imp-&gt;im_cpm
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* We can&squot;t do this.  It seems to blow away the microcode&n;&t; * patch that EPPC-Bug loaded for us.  EPPC-Bug uses SCC1 for&n;&t; * Ethernet, SMC1 for the console, and I2C for serial EEPROM.&n;&t; * Our own drivers quickly reset all of these.&n;&t; */
multiline_comment|/* Perform a reset.&n;&t;*/
id|commproc-&gt;cp_cpcr
op_assign
(paren
id|CPM_CR_RST
op_or
id|CPM_CR_FLG
)paren
suffix:semicolon
multiline_comment|/* Wait for it.&n;&t;*/
r_while
c_loop
(paren
id|commproc-&gt;cp_cpcr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set SDMA Bus Request priority 5.&n;&t;*/
id|imp-&gt;im_siu_conf.sc_sdcr
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Reclaim the DP memory for our use.&n;&t;*/
id|dp_alloc_base
op_assign
id|CPM_DATAONLY_BASE
suffix:semicolon
id|dp_alloc_top
op_assign
id|dp_alloc_base
op_plus
id|CPM_DATAONLY_SIZE
suffix:semicolon
multiline_comment|/* Set the host page for allocation.&n;&t;*/
id|host_buffer
op_assign
id|host_page_addr
suffix:semicolon
multiline_comment|/* Host virtual page address */
id|host_end
op_assign
id|host_page_addr
op_plus
id|PAGE_SIZE
suffix:semicolon
id|pte
op_assign
id|va_to_pte
c_func
(paren
op_amp
id|init_task
comma
id|host_page_addr
)paren
suffix:semicolon
id|pte_val
c_func
(paren
op_star
id|pte
)paren
op_or_assign
id|_PAGE_NO_CACHE
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|current-&gt;mm-&gt;mmap
comma
id|host_buffer
)paren
suffix:semicolon
multiline_comment|/* Tell everyone where the comm processor resides.&n;&t;*/
id|cpmp
op_assign
(paren
id|cpm8xx_t
op_star
)paren
id|commproc
suffix:semicolon
multiline_comment|/* Initialize the CPM interrupt controller.&n;&t;*/
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cicr
op_assign
(paren
id|CICR_SCD_SCC4
op_or
id|CICR_SCC_SCC3
op_or
id|CICR_SCB_SCC2
op_or
id|CICR_SCA_SCC1
)paren
op_or
(paren
(paren
id|CPM_INTERRUPT
op_div
l_int|2
)paren
op_lshift
l_int|13
)paren
op_or
id|CICR_HP_MASK
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cimr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set our interrupt handler with the core CPU.&n;&t;*/
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|CPM_INTERRUPT
comma
id|cpm_interrupt
comma
l_int|0
comma
l_string|&quot;cpm&quot;
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Could not allocate CPM IRQ!&quot;
)paren
suffix:semicolon
multiline_comment|/* Install our own error handler.&n;&t;*/
id|cpm_install_handler
c_func
(paren
id|CPMVEC_ERROR
comma
id|cpm_error_interrupt
comma
l_int|NULL
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cicr
op_or_assign
id|CICR_IEN
suffix:semicolon
)brace
multiline_comment|/* CPM interrupt controller interrupt.&n;*/
r_static
r_void
DECL|function|cpm_interrupt
id|cpm_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|uint
id|vec
suffix:semicolon
multiline_comment|/* Get the vector by setting the ACK bit and then reading&n;&t; * the register.&n;&t; */
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_civr
op_assign
l_int|1
suffix:semicolon
id|vec
op_assign
(paren
(paren
r_volatile
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_civr
suffix:semicolon
id|vec
op_rshift_assign
l_int|11
suffix:semicolon
r_if
c_cond
(paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
op_ne
l_int|0
)paren
(paren
op_star
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
)paren
(paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|dev_id
)paren
suffix:semicolon
r_else
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cimr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
multiline_comment|/* After servicing the interrupt, we have to remove the status&n;&t; * indicator.&n;&t; */
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cisr
op_or_assign
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
)brace
multiline_comment|/* The CPM can generate the error interrupt when there is a race condition&n; * between generating and masking interrupts.  All we have to do is ACK it&n; * and return.  This is a no-op function so we don&squot;t need any special&n; * tests in the interrupt handler.&n; */
r_static
r_void
DECL|function|cpm_error_interrupt
id|cpm_error_interrupt
c_func
(paren
r_void
op_star
id|dev
)paren
(brace
)brace
multiline_comment|/* Install a CPM interrupt handler.&n;*/
r_void
DECL|function|cpm_install_handler
id|cpm_install_handler
c_func
(paren
r_int
id|vec
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;CPM interrupt %x replacing %x&bslash;n&quot;
comma
(paren
id|uint
)paren
id|handler
comma
(paren
id|uint
)paren
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
)paren
suffix:semicolon
id|cpm_vecs
(braket
id|vec
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|cpm_vecs
(braket
id|vec
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|MBX_IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_cpic.cpic_cimr
op_or_assign
(paren
l_int|1
op_lshift
id|vec
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate some memory from the dual ported ram.  We may want to&n; * enforce alignment restrictions, but right now everyone is a good&n; * citizen.&n; */
id|uint
DECL|function|mbx_cpm_dpalloc
id|mbx_cpm_dpalloc
c_func
(paren
id|uint
id|size
)paren
(brace
id|uint
id|retloc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp_alloc_base
op_plus
id|size
)paren
op_ge
id|dp_alloc_top
)paren
r_return
id|CPM_DP_NOSPACE
suffix:semicolon
id|retloc
op_assign
id|dp_alloc_base
suffix:semicolon
id|dp_alloc_base
op_add_assign
id|size
suffix:semicolon
r_return
id|retloc
suffix:semicolon
)brace
multiline_comment|/* We also own one page of host buffer space for the allocation of&n; * UART &quot;fifos&quot; and the like.&n; */
id|uint
DECL|function|mbx_cpm_hostalloc
id|mbx_cpm_hostalloc
c_func
(paren
id|uint
id|size
)paren
(brace
id|uint
id|retloc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|host_buffer
op_plus
id|size
)paren
op_ge
id|host_end
)paren
r_return
l_int|0
suffix:semicolon
id|retloc
op_assign
id|host_buffer
suffix:semicolon
id|host_buffer
op_add_assign
id|size
suffix:semicolon
r_return
id|retloc
suffix:semicolon
)brace
multiline_comment|/* Set a baud rate generator.  This needs lots of work.  There are&n; * four BRGs, any of which can be wired to any channel.&n; * The internal baud rate clock is the system clock divided by 16.&n; * I need to find a way to get this system clock frequency, which is&n; * part of the VPD.......&n; */
DECL|macro|BRG_INT_CLK
mdefine_line|#define BRG_INT_CLK&t;(40000000/16)
r_void
DECL|function|mbx_cpm_setbrg
id|mbx_cpm_setbrg
c_func
(paren
id|uint
id|brg
comma
id|uint
id|rate
)paren
(brace
r_volatile
id|uint
op_star
id|bp
suffix:semicolon
multiline_comment|/* This is good enough to get SMCs running.....&n;&t;*/
id|bp
op_assign
(paren
id|uint
op_star
)paren
op_amp
id|cpmp-&gt;cp_brgc1
suffix:semicolon
id|bp
op_add_assign
id|brg
suffix:semicolon
op_star
id|bp
op_assign
(paren
(paren
id|BRG_INT_CLK
op_div
id|rate
)paren
op_lshift
l_int|1
)paren
op_or
id|CPM_BRG_EN
suffix:semicolon
)brace
eof
