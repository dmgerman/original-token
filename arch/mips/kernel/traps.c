multiline_comment|/*&n; * arch/mips/kernel/traps.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * &squot;traps.c&squot; handles hardware traps and faults after we have saved some&n; * state in &squot;asm.s&squot;. Currently mostly a debugging-aid, will be extended&n; * to mainly kill the offending process (probably by giving it a signal,&n; * but possibly by killing it outright if necessary).&n; *&n; * FIXME: This is the place for a fpu emulator.&n; *&n; * Modified for R3000 by Paul M. Antoine, 1995, 1996&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/branch.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/watch.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_SGI
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#endif
DECL|macro|CONF_DEBUG_EXCEPTIONS
macro_line|#undef CONF_DEBUG_EXCEPTIONS
DECL|function|console_verbose
r_static
r_inline
r_void
id|console_verbose
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|console_loglevel
suffix:semicolon
id|console_loglevel
op_assign
l_int|15
suffix:semicolon
)brace
multiline_comment|/*&n; * Machine specific interrupt handlers&n; */
r_extern
id|asmlinkage
r_void
id|acer_pica_61_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|decstation_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|deskstation_rpc44_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|deskstation_tyne_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|mips_magnum_4000_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4k_handle_mod
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_handle_mod
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4k_handle_tlbl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_handle_tlbl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4k_handle_tlbs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_handle_tlbs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_adel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ades
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ibe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_dbe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_sys
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_bp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ri
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_cpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_ov
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_tr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_vcei
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_fpe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_vced
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_watch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_reserved
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cpu_names
r_static
r_char
op_star
id|cpu_names
(braket
)braket
op_assign
id|CPU_NAMES
suffix:semicolon
DECL|variable|page_colour_mask
r_int
r_int
id|page_colour_mask
suffix:semicolon
DECL|variable|watch_available
r_int
r_int
id|watch_available
op_assign
l_int|0
suffix:semicolon
DECL|variable|ibe_board_handler
r_void
(paren
op_star
id|ibe_board_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|dbe_board_handler
r_void
(paren
op_star
id|dbe_board_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|kstack_depth_to_print
r_int
id|kstack_depth_to_print
op_assign
l_int|24
suffix:semicolon
multiline_comment|/*&n; * These constant is for searching for possible module text segments.&n; * MODULE_RANGE is a guess of how much space is likely to be vmalloced.&n; */
DECL|macro|MODULE_RANGE
mdefine_line|#define MODULE_RANGE (8*1024*1024)
multiline_comment|/*&n; * This routine abuses get_user()/put_user() to reference pointers&n; * with at least a bit of error checking ...&n; */
DECL|function|show_registers
r_void
id|show_registers
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
op_star
id|stack
suffix:semicolon
id|u32
op_star
id|sp
comma
op_star
id|pc
comma
id|addr
comma
id|module_start
comma
id|module_end
suffix:semicolon
r_extern
r_char
id|start_kernel
comma
id|_etext
suffix:semicolon
id|sp
op_assign
(paren
id|u32
op_star
)paren
id|regs-&gt;regs
(braket
l_int|29
)braket
suffix:semicolon
id|pc
op_assign
(paren
id|u32
op_star
)paren
id|regs-&gt;cp0_epc
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dump the stack&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stackpage=%08lx)&bslash;nStack: &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
(paren
r_int
r_int
)paren
id|current
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
op_star
id|sp
op_increment
)paren
suffix:semicolon
)brace
id|stack
op_assign
(paren
r_int
op_star
)paren
id|sp
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
id|kstack_depth_to_print
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|stackdata
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|u32
)paren
id|stack
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n       &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|stackdata
comma
id|stack
op_increment
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(Bad stack address)&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|stackdata
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nCall Trace: &quot;
)paren
suffix:semicolon
id|stack
op_assign
(paren
r_int
op_star
)paren
id|sp
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
id|module_start
op_assign
id|VMALLOC_START
suffix:semicolon
id|module_end
op_assign
id|module_start
op_plus
id|MODULE_RANGE
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
)paren
id|stack
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|addr
comma
id|stack
op_increment
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;(Bad address)&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If the address is either in the text segment of the&n;&t;&t; * kernel, or in the region which contains vmalloc&squot;ed&n;&t;&t; * memory, it *may* be the address of a calling&n;&t;&t; * routine; if so, print it so that someone tracing&n;&t;&t; * down the cause of the crash will be able to figure&n;&t;&t; * out the call path that was taken.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|addr
op_ge
(paren
id|u32
)paren
op_amp
id|start_kernel
)paren
op_logical_and
(paren
id|addr
op_le
(paren
id|u32
)paren
op_amp
id|_etext
)paren
)paren
op_logical_or
(paren
(paren
id|addr
op_ge
id|module_start
)paren
op_logical_and
(paren
id|addr
op_le
id|module_end
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_logical_and
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n       &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|addr
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nCode : &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|KSEGX
c_func
(paren
id|pc
)paren
op_eq
id|KSEG0
op_logical_or
id|KSEGX
c_func
(paren
id|pc
)paren
op_eq
id|KSEG1
)paren
op_logical_and
(paren
(paren
(paren
r_int
r_int
)paren
id|pc
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
op_star
id|pc
op_increment
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;(Bad address in epc)&bslash;n&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
multiline_comment|/*&n;&t; * Just return if in user mode.&n;&t; * XXX&n;&t; */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2)
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|regs
)paren
op_member_access_from_pointer
id|cp0_status
op_amp
l_int|0x4
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4)
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;cp0_status
op_amp
l_int|0x18
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %04lx&bslash;n&quot;
comma
id|str
comma
id|err
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|default_be_board_handler
r_static
r_void
id|default_be_board_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Assume it would be too dangerous to continue ...&n;&t; */
id|printk
(paren
l_string|&quot;BE HANDLER&bslash;n&quot;
)paren
suffix:semicolon
id|show_regs
(paren
id|regs
)paren
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGBUS
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_ibe
r_void
id|do_ibe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ibe_board_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_dbe
r_void
id|do_dbe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dbe_board_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_ov
r_void
id|do_ov
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONF_DEBUG_EXCEPTIONS
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_goto
id|out
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGFPE
comma
id|current
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_fpe
r_void
id|do_fpe
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|fcr31
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONF_DEBUG_EXCEPTIONS
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;Caught floating exception at epc == %08lx, fcr31 == %08x&bslash;n&quot;
comma
id|regs-&gt;cp0_epc
comma
id|fcr31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_goto
id|out
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGFPE
comma
id|current
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_insn_opcode
r_static
r_inline
r_int
id|get_insn_opcode
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
op_star
id|opcode
)paren
(brace
r_int
r_int
op_star
id|epc
suffix:semicolon
id|epc
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
r_int
r_int
)paren
id|regs-&gt;cp0_epc
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;cp0_cause
op_amp
id|CAUSEF_BD
)paren
id|epc
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|epc
comma
l_int|4
)paren
)paren
(brace
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
op_star
id|opcode
op_assign
op_star
id|epc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|do_bp_and_tr
id|do_bp_and_tr
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_char
op_star
id|exc
comma
r_int
r_int
id|trapcode
)paren
(brace
multiline_comment|/*&n;&t; * (A short test says that IRIX 5.3 sends SIGTRAP for all break&n;&t; * insns, even for break codes that indicate arithmetic failures.&n;&t; * Wiered ...)&n;&t; */
id|force_sig
c_func
(paren
id|SIGTRAP
comma
id|current
)paren
suffix:semicolon
macro_line|#ifdef CONF_DEBUG_EXCEPTIONS
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|do_bp
r_void
id|do_bp
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|opcode
comma
id|bcode
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There is the ancient bug in the MIPS assemblers that the break&n;&t; * code starts left to bit 16 instead to bit 6 in the opcode.&n;&t; * Gas is bug-compatible ...&n;&t; */
macro_line|#ifdef CONF_DEBUG_EXCEPTIONS
id|printk
c_func
(paren
l_string|&quot;BREAKPOINT at %08lx&bslash;n&quot;
comma
id|regs-&gt;cp0_epc
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|get_insn_opcode
c_func
(paren
id|regs
comma
op_amp
id|opcode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|bcode
op_assign
(paren
(paren
id|opcode
op_rshift
l_int|16
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|do_bp_and_tr
c_func
(paren
id|regs
comma
l_string|&quot;bp&quot;
comma
id|bcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_goto
id|out
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_tr
r_void
id|do_tr
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|opcode
comma
id|bcode
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_insn_opcode
c_func
(paren
id|regs
comma
op_amp
id|opcode
)paren
)paren
r_goto
id|out
suffix:semicolon
id|bcode
op_assign
(paren
(paren
id|opcode
op_rshift
l_int|6
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|do_bp_and_tr
c_func
(paren
id|regs
comma
l_string|&quot;tr&quot;
comma
id|bcode
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_ri
r_void
id|do_ri
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONF_DEBUG_EXCEPTIONS
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;[%s:%d] Illegal instruction at %08lx ra=%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compute_return_epc
c_func
(paren
id|regs
)paren
)paren
r_goto
id|out
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_cpu
r_void
id|do_cpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cpid
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|cpid
op_assign
(paren
id|regs-&gt;cp0_cause
op_rshift
id|CAUSEB_CE
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|cpid
op_eq
l_int|1
)paren
(brace
id|regs-&gt;cp0_status
op_or_assign
id|ST0_CU1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|SIGILL
comma
id|current
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_vcei
r_void
id|do_vcei
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only possible on R4[04]00[SM]C. No handler because I don&squot;t have&n;&t; * such a cpu.  Theory says this exception doesn&squot;t happen.&n;&t; */
id|panic
c_func
(paren
l_string|&quot;Caught VCEI exception - should not happen&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_vced
r_void
id|do_vced
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only possible on R4[04]00[SM]C. No handler because I don&squot;t have&n;&t; * such a cpu.  Theory says this exception doesn&squot;t happen.&n;&t; */
id|panic
c_func
(paren
l_string|&quot;Caught VCE exception - should not happen&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_watch
r_void
id|do_watch
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We use the watch exception where available to detect stack&n;&t; * overflows.&n;&t; */
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Caught WATCH exception - probably caused by stack overflow.&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_reserved
r_void
id|do_reserved
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Game over - no way to handle this if it ever occurs.&n;&t; * Most probably caused by a new unknown cpu type or&n;&t; * after another deadly hard/software error.&n;&t; */
id|panic
c_func
(paren
l_string|&quot;Caught reserved exception - should not happen.&quot;
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|watch_init
r_static
r_inline
r_void
id|watch_init
c_func
(paren
r_int
r_int
id|cputype
)paren
(brace
r_switch
c_cond
(paren
id|cputype
)paren
(brace
r_case
id|CPU_R10000
suffix:colon
r_case
id|CPU_R4000MC
suffix:colon
r_case
id|CPU_R4400MC
suffix:colon
r_case
id|CPU_R4000SC
suffix:colon
r_case
id|CPU_R4400SC
suffix:colon
r_case
id|CPU_R4000PC
suffix:colon
r_case
id|CPU_R4400PC
suffix:colon
r_case
id|CPU_R4200
suffix:colon
r_case
id|CPU_R4300
suffix:colon
id|set_except_vector
c_func
(paren
l_int|23
comma
id|handle_watch
)paren
suffix:semicolon
id|watch_available
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|typedef|syscall_t
r_typedef
id|asmlinkage
r_int
(paren
op_star
id|syscall_t
)paren
(paren
r_void
op_star
id|a0
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|variable|do_syscalls
id|asmlinkage
r_int
(paren
op_star
id|do_syscalls
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|syscall_t
id|fun
comma
r_int
id|narg
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|r4k_do_syscalls
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|syscall_t
id|fun
comma
r_int
id|narg
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|r2300_do_syscalls
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|syscall_t
id|fun
comma
r_int
id|narg
)paren
suffix:semicolon
DECL|variable|save_fp_context
id|asmlinkage
r_void
(paren
op_star
id|save_fp_context
)paren
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4k_save_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_save_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r6000_save_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
DECL|variable|restore_fp_context
id|asmlinkage
r_void
(paren
op_star
id|restore_fp_context
)paren
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4k_restore_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_restore_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r6000_restore_fp_context
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r4xx0_resume
c_func
(paren
r_void
op_star
id|tsk
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|r2300_resume
c_func
(paren
r_void
op_star
id|tsk
)paren
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|trap_init
c_func
(paren
r_void
)paren
)paren
(brace
r_extern
r_char
id|except_vec0_r4000
comma
id|except_vec0_r4600
comma
id|except_vec0_r2300
suffix:semicolon
r_extern
r_char
id|except_vec1_generic
comma
id|except_vec2_generic
suffix:semicolon
r_extern
r_char
id|except_vec3_generic
comma
id|except_vec3_r4000
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|mips_machtype
op_eq
id|MACH_MIPS_MAGNUM_4000
op_logical_or
id|mips_machtype
op_eq
id|MACH_DESKSTATION_RPC44
op_logical_or
id|mips_machtype
op_eq
id|MACH_SNI_RM200_PCI
)paren
(brace
id|EISA_bus
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Copy the generic exception handler code to it&squot;s final destination. */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x80
)paren
comma
op_amp
id|except_vec1_generic
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x100
)paren
comma
op_amp
id|except_vec2_generic
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x180
)paren
comma
op_amp
id|except_vec3_generic
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup default vectors&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|31
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_except_vector
c_func
(paren
id|i
comma
id|handle_reserved
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Only some CPUs have the watch exception.&n;&t; */
id|watch_init
c_func
(paren
id|mips_cputype
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Handling the following exceptions depends mostly of the cpu type&n;&t; */
r_switch
c_cond
(paren
id|mips_cputype
)paren
(brace
r_case
id|CPU_R10000
suffix:colon
multiline_comment|/*&n;&t;&t; * The R10000 is in most aspects similar to the R4400.  It&n;&t;&t; * should get some special optimizations.&n;&t;&t; */
id|write_32bit_cp0_register
c_func
(paren
id|CP0_FRAMEMASK
comma
l_int|0
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_XX
comma
id|ST0_XX
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Actually this mask stands for only 16k cache.  This is&n;&t;&t; * correct since the R10000 has multiple ways in it&squot;s cache.&n;&t;&t; */
id|page_colour_mask
op_assign
l_int|0x3000
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The R10k might even work for Linux/MIPS - but we&squot;re paranoid&n;&t;&t; * and refuse to run until this is tested on real silicon&n;&t;&t; */
id|panic
c_func
(paren
l_string|&quot;CPU too expensive - making holiday in the ANDES!&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_R4000MC
suffix:colon
r_case
id|CPU_R4400MC
suffix:colon
r_case
id|CPU_R4000SC
suffix:colon
r_case
id|CPU_R4400SC
suffix:colon
multiline_comment|/* XXX The following won&squot;t work because we _cannot_&n;&t;&t; * XXX perform any load/store before the VCE handler.&n;&t;&t; */
id|set_except_vector
c_func
(paren
l_int|14
comma
id|handle_vcei
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|31
comma
id|handle_vced
)paren
suffix:semicolon
r_case
id|CPU_R4000PC
suffix:colon
r_case
id|CPU_R4400PC
suffix:colon
r_case
id|CPU_R4200
suffix:colon
r_case
id|CPU_R4300
suffix:colon
multiline_comment|/* case CPU_R4640: */
r_case
id|CPU_R4600
suffix:colon
r_case
id|CPU_R5000
suffix:colon
r_if
c_cond
(paren
id|mips_cputype
op_ne
id|CPU_R4600
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_r4000
comma
l_int|0x80
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_r4600
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The idea is that this special r4000 general exception&n;&t;&t; * vector will check for VCE exceptions before calling&n;&t;&t; * out of the exception array.  XXX TODO&n;&t;&t; */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x100
)paren
comma
(paren
r_void
op_star
)paren
id|KSEG0
comma
l_int|0x80
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|KSEG0
op_plus
l_int|0x180
)paren
comma
op_amp
id|except_vec3_r4000
comma
l_int|0x80
)paren
suffix:semicolon
id|do_syscalls
op_assign
id|r4k_do_syscalls
suffix:semicolon
id|save_fp_context
op_assign
id|r4k_save_fp_context
suffix:semicolon
id|restore_fp_context
op_assign
id|r4k_restore_fp_context
suffix:semicolon
id|resume
op_assign
id|r4xx0_resume
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|1
comma
id|r4k_handle_mod
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|2
comma
id|r4k_handle_tlbl
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|3
comma
id|r4k_handle_tlbs
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|4
comma
id|handle_adel
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|5
comma
id|handle_ades
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The following two are signaled by onboard hardware and&n;&t;&t; * should get board specific handlers to get maximum&n;&t;&t; * available information.&n;&t;&t; */
id|set_except_vector
c_func
(paren
l_int|6
comma
id|handle_ibe
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|7
comma
id|handle_dbe
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|8
comma
id|handle_sys
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|9
comma
id|handle_bp
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|10
comma
id|handle_ri
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|11
comma
id|handle_cpu
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|12
comma
id|handle_ov
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|13
comma
id|handle_tr
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|15
comma
id|handle_fpe
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Compute mask for page_colour().  This is based on the&n;&t;&t; * size of the data cache.&n;&t;&t; */
id|i
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_CONFIG
)paren
suffix:semicolon
id|i
op_assign
(paren
id|i
op_rshift
l_int|26
)paren
op_amp
l_int|7
suffix:semicolon
id|page_colour_mask
op_assign
l_int|1
op_lshift
(paren
l_int|12
op_plus
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_R6000
suffix:colon
r_case
id|CPU_R6000A
suffix:colon
id|save_fp_context
op_assign
id|r6000_save_fp_context
suffix:semicolon
id|restore_fp_context
op_assign
id|r6000_restore_fp_context
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n;&t;&t; * The R6000 is the only R-series CPU that features a machine&n;&t;&t; * check exception (similar to the R4000 cache error) and&n;&t;&t; * unaligned ldc1/sdc1 exception.  The handlers have not been&n;&t;&t; * written yet.  Well, anyway there is no R6000 machine on the&n;&t;&t; * current list of targets for Linux/MIPS.&n;&t;&t; */
id|set_except_vector
c_func
(paren
l_int|14
comma
id|handle_mc
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|15
comma
id|handle_ndc
)paren
suffix:semicolon
macro_line|#endif
r_case
id|CPU_R2000
suffix:colon
r_case
id|CPU_R3000
suffix:colon
r_case
id|CPU_R3000A
suffix:colon
multiline_comment|/*&n;&t;&t; * Actually don&squot;t know about these, but let&squot;s guess - PMA&n;&t;&t; */
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|KSEG0
comma
op_amp
id|except_vec0_r2300
comma
l_int|0x80
)paren
suffix:semicolon
id|do_syscalls
op_assign
id|r2300_do_syscalls
suffix:semicolon
id|save_fp_context
op_assign
id|r2300_save_fp_context
suffix:semicolon
id|restore_fp_context
op_assign
id|r2300_restore_fp_context
suffix:semicolon
id|resume
op_assign
id|r2300_resume
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|1
comma
id|r2300_handle_mod
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|2
comma
id|r2300_handle_tlbl
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|3
comma
id|r2300_handle_tlbs
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|4
comma
id|handle_adel
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|5
comma
id|handle_ades
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The Data Bus Error/ Instruction Bus Errors are signaled&n;&t;&t; * by external hardware.  Therefore these two expection have&n;&t;&t; * board specific handlers.&n;&t;&t; */
id|set_except_vector
c_func
(paren
l_int|6
comma
id|handle_ibe
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|7
comma
id|handle_dbe
)paren
suffix:semicolon
id|ibe_board_handler
op_assign
id|default_be_board_handler
suffix:semicolon
id|dbe_board_handler
op_assign
id|default_be_board_handler
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|8
comma
id|handle_sys
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|9
comma
id|handle_bp
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|10
comma
id|handle_ri
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|11
comma
id|handle_cpu
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|12
comma
id|handle_ov
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|13
comma
id|handle_tr
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|15
comma
id|handle_fpe
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Compute mask for page_colour().  This is based on the&n;&t;&t; * size of the data cache.  Does the size of the icache&n;&t;&t; * need to be accounted for?&n;&t;&t; *&n;&t;&t; * FIXME: is any of this necessary for the R3000, which&n;&t;&t; *        doesn&squot;t have a config register?&n;&t;&t; *        (No, the R2000, R3000 family has a physical indexed&n;&t;&t; *        cache and doesn&squot;t need this braindamage.)&n;&t;&t;i = read_32bit_cp0_register(CP0_CONFIG);&n;&t;&t;i = (i &gt;&gt; 26) &amp; 7;&n;&t;&t;page_colour_mask = 1 &lt;&lt; (12 + i);&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|CPU_R3041
suffix:colon
r_case
id|CPU_R3051
suffix:colon
r_case
id|CPU_R3052
suffix:colon
r_case
id|CPU_R3081
suffix:colon
r_case
id|CPU_R3081E
suffix:colon
r_case
id|CPU_R8000
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Detected unsupported CPU type %s.&bslash;n&quot;
comma
id|cpu_names
(braket
id|mips_cputype
)braket
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Can&squot;t handle CPU&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_UNKNOWN
suffix:colon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown CPU type&quot;
)paren
suffix:semicolon
)brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
eof
