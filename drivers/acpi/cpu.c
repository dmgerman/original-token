multiline_comment|/*&n; *  cpu.c - Processor handling&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;driver.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;OS_DEPENDENT
id|MODULE_NAME
(paren
l_string|&quot;cpu&quot;
)paren
DECL|variable|acpi_c2_exit_latency
r_int
r_int
id|acpi_c2_exit_latency
op_assign
id|ACPI_INFINITE
suffix:semicolon
DECL|variable|acpi_c3_exit_latency
r_int
r_int
id|acpi_c3_exit_latency
op_assign
id|ACPI_INFINITE
suffix:semicolon
DECL|variable|acpi_c2_enter_latency
r_int
r_int
id|acpi_c2_enter_latency
op_assign
id|ACPI_INFINITE
suffix:semicolon
DECL|variable|acpi_c3_enter_latency
r_int
r_int
id|acpi_c3_enter_latency
op_assign
id|ACPI_INFINITE
suffix:semicolon
DECL|variable|acpi_pblk
r_static
r_int
r_int
id|acpi_pblk
op_assign
id|ACPI_INVALID
suffix:semicolon
DECL|variable|acpi_c2_tested
r_static
r_int
id|acpi_c2_tested
op_assign
l_int|0
suffix:semicolon
DECL|variable|acpi_c3_tested
r_static
r_int
id|acpi_c3_tested
op_assign
l_int|0
suffix:semicolon
DECL|variable|acpi_max_c_state
r_static
r_int
id|acpi_max_c_state
op_assign
l_int|1
suffix:semicolon
DECL|variable|acpi_pm_tmr_len
r_static
r_int
id|acpi_pm_tmr_len
suffix:semicolon
multiline_comment|/*&n; * Clear busmaster activity flag&n; */
r_static
r_inline
r_void
DECL|function|acpi_clear_bm_activity
id|acpi_clear_bm_activity
c_func
(paren
r_void
)paren
(brace
id|acpi_hw_register_bit_access
c_func
(paren
id|ACPI_WRITE
comma
id|ACPI_MTX_LOCK
comma
id|BM_STS
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns 1 if there has been busmaster activity&n; */
r_static
r_inline
r_int
DECL|function|acpi_bm_activity
id|acpi_bm_activity
c_func
(paren
r_void
)paren
(brace
r_return
id|acpi_hw_register_bit_access
c_func
(paren
id|ACPI_READ
comma
id|ACPI_MTX_LOCK
comma
id|BM_STS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set system to sleep through busmaster requests&n; */
r_static
r_void
DECL|function|acpi_sleep_on_busmaster
id|acpi_sleep_on_busmaster
c_func
(paren
r_void
)paren
(brace
id|acpi_hw_register_bit_access
(paren
id|ACPI_WRITE
comma
id|ACPI_MTX_LOCK
comma
id|BM_RLD
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set system to wake on busmaster requests&n; */
r_static
r_void
DECL|function|acpi_wake_on_busmaster
id|acpi_wake_on_busmaster
c_func
(paren
r_void
)paren
(brace
id|acpi_hw_register_bit_access
(paren
id|ACPI_WRITE
comma
id|ACPI_MTX_LOCK
comma
id|BM_RLD
comma
l_int|0
)paren
suffix:semicolon
)brace
id|u32
DECL|function|acpi_read_pm_timer
id|acpi_read_pm_timer
c_func
(paren
r_void
)paren
(brace
r_return
id|acpi_hw_register_read
c_func
(paren
id|ACPI_MTX_LOCK
comma
id|PM_TIMER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a compare, accounting for 24/32bit rollover&n; */
r_static
id|u32
DECL|function|acpi_compare_pm_timers
id|acpi_compare_pm_timers
c_func
(paren
id|u32
id|first
comma
id|u32
id|second
)paren
(brace
r_if
c_cond
(paren
id|first
OL
id|second
)paren
(brace
r_return
(paren
id|second
op_minus
id|first
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|acpi_pm_tmr_len
op_eq
l_int|24
)paren
r_return
(paren
id|second
op_plus
(paren
l_int|0xFFFFFF
op_minus
id|first
)paren
)paren
suffix:semicolon
r_else
r_return
(paren
id|second
op_plus
(paren
l_int|0xFFFFFFFF
op_minus
id|first
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Idle loop (uniprocessor only)&n; */
r_static
r_void
DECL|function|acpi_idle
id|acpi_idle
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|sleep_level
op_assign
l_int|1
suffix:semicolon
id|FADT_DESCRIPTOR
op_star
id|fadt
op_assign
op_amp
id|acpi_fadt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fadt
op_logical_or
(paren
id|STRNCMP
c_func
(paren
id|fadt-&gt;header.signature
comma
id|ACPI_FADT_SIGNATURE
comma
id|ACPI_SIG_LEN
)paren
op_ne
l_int|0
)paren
op_logical_or
op_logical_neg
id|fadt-&gt;Xpm_tmr_blk.address
op_logical_or
op_logical_neg
id|acpi_pblk
)paren
r_goto
id|not_initialized
suffix:semicolon
multiline_comment|/*&n;&t; * start from the previous sleep level..&n;&t; */
r_if
c_cond
(paren
id|sleep_level
op_eq
l_int|1
op_logical_or
id|acpi_max_c_state
OL
l_int|2
)paren
r_goto
id|sleep1
suffix:semicolon
r_if
c_cond
(paren
id|sleep_level
op_eq
l_int|2
op_logical_or
id|acpi_max_c_state
OL
l_int|3
)paren
r_goto
id|sleep2
suffix:semicolon
id|sleep3
suffix:colon
id|sleep_level
op_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_c3_tested
)paren
(brace
id|DEBUG_PRINT
c_func
(paren
id|ACPI_INFO
comma
(paren
l_string|&quot;C3 works&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_c3_tested
op_assign
l_int|1
suffix:semicolon
)brace
id|acpi_wake_on_busmaster
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fadt-&gt;Xpm2_cnt_blk.address
)paren
r_goto
id|sleep3_with_arbiter
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|time
suffix:semicolon
r_int
r_int
id|diff
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bm_activity
c_func
(paren
)paren
)paren
r_goto
id|sleep2
suffix:semicolon
id|time
op_assign
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|acpi_pblk
op_plus
id|ACPI_P_LVL3
)paren
suffix:semicolon
multiline_comment|/* Dummy read, force synchronization with the PMU */
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|diff
op_assign
id|acpi_compare_pm_timers
c_func
(paren
id|time
comma
id|acpi_read_pm_timer
c_func
(paren
)paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
id|acpi_c3_exit_latency
)paren
r_goto
id|sleep2
suffix:semicolon
)brace
id|sleep3_with_arbiter
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|time
suffix:semicolon
r_int
r_int
id|diff
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bm_activity
c_func
(paren
)paren
)paren
r_goto
id|sleep2
suffix:semicolon
id|time
op_assign
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable arbiter, park on CPU */
id|acpi_hw_register_bit_access
c_func
(paren
id|ACPI_WRITE
comma
id|ACPI_MTX_LOCK
comma
id|ARB_DIS
comma
l_int|1
)paren
suffix:semicolon
id|inb
c_func
(paren
id|acpi_pblk
op_plus
id|ACPI_P_LVL3
)paren
suffix:semicolon
multiline_comment|/* Dummy read, force synchronization with the PMU */
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|diff
op_assign
id|acpi_compare_pm_timers
c_func
(paren
id|time
comma
id|acpi_read_pm_timer
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable arbiter again.. */
id|acpi_hw_register_bit_access
c_func
(paren
id|ACPI_WRITE
comma
id|ACPI_MTX_LOCK
comma
id|ARB_DIS
comma
l_int|0
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
id|acpi_c3_exit_latency
)paren
r_goto
id|sleep2
suffix:semicolon
)brace
id|sleep2
suffix:colon
id|sleep_level
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_c2_tested
)paren
(brace
id|DEBUG_PRINT
c_func
(paren
id|ACPI_INFO
comma
(paren
l_string|&quot;C2 works&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_c2_tested
op_assign
l_int|1
suffix:semicolon
)brace
id|acpi_wake_on_busmaster
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Required to track BM activity.. */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|time
suffix:semicolon
r_int
r_int
id|diff
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
id|time
op_assign
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|acpi_pblk
op_plus
id|ACPI_P_LVL2
)paren
suffix:semicolon
multiline_comment|/* Dummy read, force synchronization with the PMU */
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|diff
op_assign
id|acpi_compare_pm_timers
c_func
(paren
id|time
comma
id|acpi_read_pm_timer
c_func
(paren
)paren
)paren
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
OL
id|acpi_c2_exit_latency
)paren
r_goto
id|sleep1
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bm_activity
c_func
(paren
)paren
)paren
(brace
id|acpi_clear_bm_activity
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|diff
OG
id|acpi_c3_enter_latency
op_logical_and
id|acpi_max_c_state
op_ge
l_int|3
)paren
r_goto
id|sleep3
suffix:semicolon
)brace
id|sleep1
suffix:colon
id|sleep_level
op_assign
l_int|1
suffix:semicolon
id|acpi_sleep_on_busmaster
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|time
suffix:semicolon
r_int
r_int
id|diff
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
id|time
op_assign
id|acpi_read_pm_timer
c_func
(paren
)paren
suffix:semicolon
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
id|diff
op_assign
id|acpi_compare_pm_timers
c_func
(paren
id|time
comma
id|acpi_read_pm_timer
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|diff
OG
id|acpi_c2_enter_latency
op_logical_and
id|acpi_max_c_state
op_ge
l_int|2
)paren
r_goto
id|sleep2
suffix:semicolon
)brace
id|not_initialized
suffix:colon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get processor information&n; */
r_static
id|ACPI_STATUS
DECL|function|acpi_found_cpu
id|acpi_found_cpu
c_func
(paren
id|ACPI_HANDLE
id|handle
comma
id|u32
id|level
comma
r_void
op_star
id|ctx
comma
r_void
op_star
op_star
id|value
)paren
(brace
id|ACPI_OBJECT
id|obj
suffix:semicolon
id|ACPI_CX_STATE
id|lat
(braket
l_int|4
)braket
suffix:semicolon
id|ACPI_CPU_THROTTLING_STATE
id|throttle
(braket
id|ACPI_MAX_THROTTLE
)braket
suffix:semicolon
id|ACPI_BUFFER
id|buf
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
id|buf.length
op_assign
r_sizeof
(paren
id|obj
)paren
suffix:semicolon
id|buf.pointer
op_assign
op_amp
id|obj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_evaluate_object
c_func
(paren
id|handle
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|buf
)paren
)paren
)paren
r_return
id|AE_OK
suffix:semicolon
id|DEBUG_PRINT
c_func
(paren
id|ACPI_INFO
comma
(paren
l_string|&quot;PBLK %d @ 0x%04x:%d&bslash;n&quot;
comma
id|obj.processor.proc_id
comma
id|obj.processor.pblk_address
comma
id|obj.processor.pblk_length
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_pblk
op_ne
id|ACPI_INVALID
op_logical_or
op_logical_neg
id|obj.processor.pblk_address
op_logical_or
id|obj.processor.pblk_length
op_ne
l_int|6
)paren
r_return
id|AE_OK
suffix:semicolon
id|acpi_pblk
op_assign
id|obj.processor.pblk_address
suffix:semicolon
id|buf.length
op_assign
r_sizeof
(paren
id|lat
)paren
suffix:semicolon
id|buf.pointer
op_assign
id|lat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_get_processor_cx_info
c_func
(paren
id|handle
comma
op_amp
id|buf
)paren
)paren
)paren
r_return
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
id|lat
(braket
l_int|2
)braket
dot
id|latency
OL
id|MAX_CX_STATE_LATENCY
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: System firmware supports: C2&quot;
)paren
suffix:semicolon
id|acpi_c2_exit_latency
op_assign
id|lat
(braket
l_int|2
)braket
dot
id|latency
suffix:semicolon
id|acpi_max_c_state
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|lat
(braket
l_int|3
)braket
dot
id|latency
OL
id|MAX_CX_STATE_LATENCY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; C3&quot;
)paren
suffix:semicolon
id|acpi_c3_exit_latency
op_assign
id|lat
(braket
l_int|3
)braket
dot
id|latency
suffix:semicolon
id|acpi_max_c_state
op_assign
l_int|3
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|throttle
comma
l_int|0
comma
r_sizeof
(paren
id|throttle
)paren
)paren
suffix:semicolon
id|buf.length
op_assign
r_sizeof
(paren
id|throttle
)paren
suffix:semicolon
id|buf.pointer
op_assign
id|throttle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_get_processor_throttling_info
c_func
(paren
id|handle
comma
op_amp
id|buf
)paren
)paren
)paren
r_return
id|AE_OK
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_MAX_THROTTLE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|throttle
(braket
id|i
)braket
dot
id|percent_of_clock
)paren
id|count
op_increment
suffix:semicolon
)brace
multiline_comment|/* 0% throttled really doesn&squot;t count */
id|count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|DEBUG_PRINT
c_func
(paren
id|ACPI_INFO
comma
(paren
l_string|&quot;%d throttling states&bslash;n&quot;
comma
id|count
)paren
)paren
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pm_timer_init
id|acpi_pm_timer_init
c_func
(paren
r_void
)paren
(brace
id|FADT_DESCRIPTOR
op_star
id|fadt
op_assign
op_amp
id|acpi_fadt
suffix:semicolon
r_if
c_cond
(paren
id|fadt-&gt;tmr_val_ext
)paren
(brace
id|acpi_pm_tmr_len
op_assign
l_int|32
suffix:semicolon
)brace
r_else
(brace
id|acpi_pm_tmr_len
op_assign
l_int|24
suffix:semicolon
)brace
id|DEBUG_PRINT
c_func
(paren
id|ACPI_INFO
comma
(paren
l_string|&quot;PM Timer width: %d bits&bslash;n&quot;
comma
id|acpi_pm_tmr_len
)paren
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_int
DECL|function|acpi_cpu_init
id|acpi_cpu_init
c_func
(paren
r_void
)paren
(brace
id|acpi_walk_namespace
c_func
(paren
id|ACPI_TYPE_PROCESSOR
comma
id|ACPI_ROOT_OBJECT
comma
id|ACPI_UINT32_MAX
comma
id|acpi_found_cpu
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|acpi_pm_timer_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|smp_num_cpus
op_eq
l_int|1
)paren
id|pm_idle
op_assign
id|acpi_idle
suffix:semicolon
macro_line|#else
id|pm_idle
op_assign
id|acpi_idle
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
