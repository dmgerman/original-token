multiline_comment|/* Automatically generated. Do not edit. */
macro_line|#ifndef __ASM_OFFSETS_H__
DECL|macro|__ASM_OFFSETS_H__
mdefine_line|#define __ASM_OFFSETS_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
macro_line|# if !((__GNUC__ &gt; 2) || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &gt;= 8))
macro_line|#  error Please issue &squot;make check_asm&squot; in linux top-level directory first
macro_line|# endif
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
DECL|macro|AOFF_task_state
mdefine_line|#define AOFF_task_state&t;0x00000000
DECL|macro|ASIZ_task_state
mdefine_line|#define ASIZ_task_state&t;0x00000008
DECL|macro|AOFF_task_flags
mdefine_line|#define AOFF_task_flags&t;0x00000008
DECL|macro|ASIZ_task_flags
mdefine_line|#define ASIZ_task_flags&t;0x00000008
DECL|macro|AOFF_task_sigpending
mdefine_line|#define AOFF_task_sigpending&t;0x00000010
DECL|macro|ASIZ_task_sigpending
mdefine_line|#define ASIZ_task_sigpending&t;0x00000004
DECL|macro|AOFF_task_addr_limit
mdefine_line|#define AOFF_task_addr_limit&t;0x00000014
DECL|macro|ASIZ_task_addr_limit
mdefine_line|#define ASIZ_task_addr_limit&t;0x00000001
DECL|macro|AOFF_task_exec_domain
mdefine_line|#define AOFF_task_exec_domain&t;0x00000018
DECL|macro|ASIZ_task_exec_domain
mdefine_line|#define ASIZ_task_exec_domain&t;0x00000008
DECL|macro|AOFF_task_need_resched
mdefine_line|#define AOFF_task_need_resched&t;0x00000020
DECL|macro|ASIZ_task_need_resched
mdefine_line|#define ASIZ_task_need_resched&t;0x00000008
DECL|macro|AOFF_task_avg_slice
mdefine_line|#define AOFF_task_avg_slice&t;0x00000028
DECL|macro|ASIZ_task_avg_slice
mdefine_line|#define ASIZ_task_avg_slice&t;0x00000008
DECL|macro|AOFF_task_lock_depth
mdefine_line|#define AOFF_task_lock_depth&t;0x00000030
DECL|macro|ASIZ_task_lock_depth
mdefine_line|#define ASIZ_task_lock_depth&t;0x00000004
DECL|macro|AOFF_task_counter
mdefine_line|#define AOFF_task_counter&t;0x00000038
DECL|macro|ASIZ_task_counter
mdefine_line|#define ASIZ_task_counter&t;0x00000008
DECL|macro|AOFF_task_priority
mdefine_line|#define AOFF_task_priority&t;0x00000040
DECL|macro|ASIZ_task_priority
mdefine_line|#define ASIZ_task_priority&t;0x00000008
DECL|macro|AOFF_task_policy
mdefine_line|#define AOFF_task_policy&t;0x00000048
DECL|macro|ASIZ_task_policy
mdefine_line|#define ASIZ_task_policy&t;0x00000008
DECL|macro|AOFF_task_mm
mdefine_line|#define AOFF_task_mm&t;0x00000050
DECL|macro|ASIZ_task_mm
mdefine_line|#define ASIZ_task_mm&t;0x00000008
DECL|macro|AOFF_task_active_mm
mdefine_line|#define AOFF_task_active_mm&t;0x00000058
DECL|macro|ASIZ_task_active_mm
mdefine_line|#define ASIZ_task_active_mm&t;0x00000008
DECL|macro|AOFF_task_has_cpu
mdefine_line|#define AOFF_task_has_cpu&t;0x00000060
DECL|macro|ASIZ_task_has_cpu
mdefine_line|#define ASIZ_task_has_cpu&t;0x00000004
DECL|macro|AOFF_task_processor
mdefine_line|#define AOFF_task_processor&t;0x00000064
DECL|macro|ASIZ_task_processor
mdefine_line|#define ASIZ_task_processor&t;0x00000004
DECL|macro|AOFF_task_run_list
mdefine_line|#define AOFF_task_run_list&t;0x00000068
DECL|macro|ASIZ_task_run_list
mdefine_line|#define ASIZ_task_run_list&t;0x00000010
DECL|macro|AOFF_task_next_task
mdefine_line|#define AOFF_task_next_task&t;0x00000078
DECL|macro|ASIZ_task_next_task
mdefine_line|#define ASIZ_task_next_task&t;0x00000008
DECL|macro|AOFF_task_prev_task
mdefine_line|#define AOFF_task_prev_task&t;0x00000080
DECL|macro|ASIZ_task_prev_task
mdefine_line|#define ASIZ_task_prev_task&t;0x00000008
DECL|macro|AOFF_task_last_processor
mdefine_line|#define AOFF_task_last_processor&t;0x00000088
DECL|macro|ASIZ_task_last_processor
mdefine_line|#define ASIZ_task_last_processor&t;0x00000004
DECL|macro|AOFF_task_binfmt
mdefine_line|#define AOFF_task_binfmt&t;0x00000090
DECL|macro|ASIZ_task_binfmt
mdefine_line|#define ASIZ_task_binfmt&t;0x00000008
DECL|macro|AOFF_task_exit_code
mdefine_line|#define AOFF_task_exit_code&t;0x00000098
DECL|macro|ASIZ_task_exit_code
mdefine_line|#define ASIZ_task_exit_code&t;0x00000004
DECL|macro|AOFF_task_exit_signal
mdefine_line|#define AOFF_task_exit_signal&t;0x0000009c
DECL|macro|ASIZ_task_exit_signal
mdefine_line|#define ASIZ_task_exit_signal&t;0x00000004
DECL|macro|AOFF_task_pdeath_signal
mdefine_line|#define AOFF_task_pdeath_signal&t;0x000000a0
DECL|macro|ASIZ_task_pdeath_signal
mdefine_line|#define ASIZ_task_pdeath_signal&t;0x00000004
DECL|macro|AOFF_task_personality
mdefine_line|#define AOFF_task_personality&t;0x000000a8
DECL|macro|ASIZ_task_personality
mdefine_line|#define ASIZ_task_personality&t;0x00000008
DECL|macro|AOFF_task_pid
mdefine_line|#define AOFF_task_pid&t;0x000000b4
DECL|macro|ASIZ_task_pid
mdefine_line|#define ASIZ_task_pid&t;0x00000004
DECL|macro|AOFF_task_pgrp
mdefine_line|#define AOFF_task_pgrp&t;0x000000b8
DECL|macro|ASIZ_task_pgrp
mdefine_line|#define ASIZ_task_pgrp&t;0x00000004
DECL|macro|AOFF_task_tty_old_pgrp
mdefine_line|#define AOFF_task_tty_old_pgrp&t;0x000000bc
DECL|macro|ASIZ_task_tty_old_pgrp
mdefine_line|#define ASIZ_task_tty_old_pgrp&t;0x00000004
DECL|macro|AOFF_task_session
mdefine_line|#define AOFF_task_session&t;0x000000c0
DECL|macro|ASIZ_task_session
mdefine_line|#define ASIZ_task_session&t;0x00000004
DECL|macro|AOFF_task_leader
mdefine_line|#define AOFF_task_leader&t;0x000000c4
DECL|macro|ASIZ_task_leader
mdefine_line|#define ASIZ_task_leader&t;0x00000004
DECL|macro|AOFF_task_p_opptr
mdefine_line|#define AOFF_task_p_opptr&t;0x000000c8
DECL|macro|ASIZ_task_p_opptr
mdefine_line|#define ASIZ_task_p_opptr&t;0x00000008
DECL|macro|AOFF_task_p_pptr
mdefine_line|#define AOFF_task_p_pptr&t;0x000000d0
DECL|macro|ASIZ_task_p_pptr
mdefine_line|#define ASIZ_task_p_pptr&t;0x00000008
DECL|macro|AOFF_task_p_cptr
mdefine_line|#define AOFF_task_p_cptr&t;0x000000d8
DECL|macro|ASIZ_task_p_cptr
mdefine_line|#define ASIZ_task_p_cptr&t;0x00000008
DECL|macro|AOFF_task_p_ysptr
mdefine_line|#define AOFF_task_p_ysptr&t;0x000000e0
DECL|macro|ASIZ_task_p_ysptr
mdefine_line|#define ASIZ_task_p_ysptr&t;0x00000008
DECL|macro|AOFF_task_p_osptr
mdefine_line|#define AOFF_task_p_osptr&t;0x000000e8
DECL|macro|ASIZ_task_p_osptr
mdefine_line|#define ASIZ_task_p_osptr&t;0x00000008
DECL|macro|AOFF_task_pidhash_next
mdefine_line|#define AOFF_task_pidhash_next&t;0x000000f0
DECL|macro|ASIZ_task_pidhash_next
mdefine_line|#define ASIZ_task_pidhash_next&t;0x00000008
DECL|macro|AOFF_task_pidhash_pprev
mdefine_line|#define AOFF_task_pidhash_pprev&t;0x000000f8
DECL|macro|ASIZ_task_pidhash_pprev
mdefine_line|#define ASIZ_task_pidhash_pprev&t;0x00000008
DECL|macro|AOFF_task_wait_chldexit
mdefine_line|#define AOFF_task_wait_chldexit&t;0x00000100
DECL|macro|ASIZ_task_wait_chldexit
mdefine_line|#define ASIZ_task_wait_chldexit&t;0x00000028
DECL|macro|AOFF_task_vfork_sem
mdefine_line|#define AOFF_task_vfork_sem&t;0x00000128
DECL|macro|ASIZ_task_vfork_sem
mdefine_line|#define ASIZ_task_vfork_sem&t;0x00000008
DECL|macro|AOFF_task_rt_priority
mdefine_line|#define AOFF_task_rt_priority&t;0x00000130
DECL|macro|ASIZ_task_rt_priority
mdefine_line|#define ASIZ_task_rt_priority&t;0x00000008
DECL|macro|AOFF_task_it_real_value
mdefine_line|#define AOFF_task_it_real_value&t;0x00000138
DECL|macro|ASIZ_task_it_real_value
mdefine_line|#define ASIZ_task_it_real_value&t;0x00000008
DECL|macro|AOFF_task_it_prof_value
mdefine_line|#define AOFF_task_it_prof_value&t;0x00000140
DECL|macro|ASIZ_task_it_prof_value
mdefine_line|#define ASIZ_task_it_prof_value&t;0x00000008
DECL|macro|AOFF_task_it_virt_value
mdefine_line|#define AOFF_task_it_virt_value&t;0x00000148
DECL|macro|ASIZ_task_it_virt_value
mdefine_line|#define ASIZ_task_it_virt_value&t;0x00000008
DECL|macro|AOFF_task_it_real_incr
mdefine_line|#define AOFF_task_it_real_incr&t;0x00000150
DECL|macro|ASIZ_task_it_real_incr
mdefine_line|#define ASIZ_task_it_real_incr&t;0x00000008
DECL|macro|AOFF_task_it_prof_incr
mdefine_line|#define AOFF_task_it_prof_incr&t;0x00000158
DECL|macro|ASIZ_task_it_prof_incr
mdefine_line|#define ASIZ_task_it_prof_incr&t;0x00000008
DECL|macro|AOFF_task_it_virt_incr
mdefine_line|#define AOFF_task_it_virt_incr&t;0x00000160
DECL|macro|ASIZ_task_it_virt_incr
mdefine_line|#define ASIZ_task_it_virt_incr&t;0x00000008
DECL|macro|AOFF_task_real_timer
mdefine_line|#define AOFF_task_real_timer&t;0x00000168
DECL|macro|ASIZ_task_real_timer
mdefine_line|#define ASIZ_task_real_timer&t;0x00000030
DECL|macro|AOFF_task_times
mdefine_line|#define AOFF_task_times&t;0x00000198
DECL|macro|ASIZ_task_times
mdefine_line|#define ASIZ_task_times&t;0x00000020
DECL|macro|AOFF_task_start_time
mdefine_line|#define AOFF_task_start_time&t;0x000001b8
DECL|macro|ASIZ_task_start_time
mdefine_line|#define ASIZ_task_start_time&t;0x00000008
DECL|macro|AOFF_task_per_cpu_utime
mdefine_line|#define AOFF_task_per_cpu_utime&t;0x000001c0
DECL|macro|ASIZ_task_per_cpu_utime
mdefine_line|#define ASIZ_task_per_cpu_utime&t;0x00000008
DECL|macro|AOFF_task_min_flt
mdefine_line|#define AOFF_task_min_flt&t;0x000001d0
DECL|macro|ASIZ_task_min_flt
mdefine_line|#define ASIZ_task_min_flt&t;0x00000008
DECL|macro|AOFF_task_maj_flt
mdefine_line|#define AOFF_task_maj_flt&t;0x000001d8
DECL|macro|ASIZ_task_maj_flt
mdefine_line|#define ASIZ_task_maj_flt&t;0x00000008
DECL|macro|AOFF_task_nswap
mdefine_line|#define AOFF_task_nswap&t;0x000001e0
DECL|macro|ASIZ_task_nswap
mdefine_line|#define ASIZ_task_nswap&t;0x00000008
DECL|macro|AOFF_task_cmin_flt
mdefine_line|#define AOFF_task_cmin_flt&t;0x000001e8
DECL|macro|ASIZ_task_cmin_flt
mdefine_line|#define ASIZ_task_cmin_flt&t;0x00000008
DECL|macro|AOFF_task_cmaj_flt
mdefine_line|#define AOFF_task_cmaj_flt&t;0x000001f0
DECL|macro|ASIZ_task_cmaj_flt
mdefine_line|#define ASIZ_task_cmaj_flt&t;0x00000008
DECL|macro|AOFF_task_cnswap
mdefine_line|#define AOFF_task_cnswap&t;0x000001f8
DECL|macro|ASIZ_task_cnswap
mdefine_line|#define ASIZ_task_cnswap&t;0x00000008
DECL|macro|AOFF_task_uid
mdefine_line|#define AOFF_task_uid&t;0x00000204
DECL|macro|ASIZ_task_uid
mdefine_line|#define ASIZ_task_uid&t;0x00000004
DECL|macro|AOFF_task_euid
mdefine_line|#define AOFF_task_euid&t;0x00000208
DECL|macro|ASIZ_task_euid
mdefine_line|#define ASIZ_task_euid&t;0x00000004
DECL|macro|AOFF_task_suid
mdefine_line|#define AOFF_task_suid&t;0x0000020c
DECL|macro|ASIZ_task_suid
mdefine_line|#define ASIZ_task_suid&t;0x00000004
DECL|macro|AOFF_task_fsuid
mdefine_line|#define AOFF_task_fsuid&t;0x00000210
DECL|macro|ASIZ_task_fsuid
mdefine_line|#define ASIZ_task_fsuid&t;0x00000004
DECL|macro|AOFF_task_gid
mdefine_line|#define AOFF_task_gid&t;0x00000214
DECL|macro|ASIZ_task_gid
mdefine_line|#define ASIZ_task_gid&t;0x00000004
DECL|macro|AOFF_task_egid
mdefine_line|#define AOFF_task_egid&t;0x00000218
DECL|macro|ASIZ_task_egid
mdefine_line|#define ASIZ_task_egid&t;0x00000004
DECL|macro|AOFF_task_sgid
mdefine_line|#define AOFF_task_sgid&t;0x0000021c
DECL|macro|ASIZ_task_sgid
mdefine_line|#define ASIZ_task_sgid&t;0x00000004
DECL|macro|AOFF_task_fsgid
mdefine_line|#define AOFF_task_fsgid&t;0x00000220
DECL|macro|ASIZ_task_fsgid
mdefine_line|#define ASIZ_task_fsgid&t;0x00000004
DECL|macro|AOFF_task_ngroups
mdefine_line|#define AOFF_task_ngroups&t;0x00000224
DECL|macro|ASIZ_task_ngroups
mdefine_line|#define ASIZ_task_ngroups&t;0x00000004
DECL|macro|AOFF_task_groups
mdefine_line|#define AOFF_task_groups&t;0x00000228
DECL|macro|ASIZ_task_groups
mdefine_line|#define ASIZ_task_groups&t;0x00000080
DECL|macro|AOFF_task_cap_effective
mdefine_line|#define AOFF_task_cap_effective&t;0x000002a8
DECL|macro|ASIZ_task_cap_effective
mdefine_line|#define ASIZ_task_cap_effective&t;0x00000004
DECL|macro|AOFF_task_cap_inheritable
mdefine_line|#define AOFF_task_cap_inheritable&t;0x000002ac
DECL|macro|ASIZ_task_cap_inheritable
mdefine_line|#define ASIZ_task_cap_inheritable&t;0x00000004
DECL|macro|AOFF_task_cap_permitted
mdefine_line|#define AOFF_task_cap_permitted&t;0x000002b0
DECL|macro|ASIZ_task_cap_permitted
mdefine_line|#define ASIZ_task_cap_permitted&t;0x00000004
DECL|macro|AOFF_task_user
mdefine_line|#define AOFF_task_user&t;0x000002b8
DECL|macro|ASIZ_task_user
mdefine_line|#define ASIZ_task_user&t;0x00000008
DECL|macro|AOFF_task_rlim
mdefine_line|#define AOFF_task_rlim&t;0x000002c0
DECL|macro|ASIZ_task_rlim
mdefine_line|#define ASIZ_task_rlim&t;0x000000a0
DECL|macro|AOFF_task_used_math
mdefine_line|#define AOFF_task_used_math&t;0x00000360
DECL|macro|ASIZ_task_used_math
mdefine_line|#define ASIZ_task_used_math&t;0x00000002
DECL|macro|AOFF_task_comm
mdefine_line|#define AOFF_task_comm&t;0x00000362
DECL|macro|ASIZ_task_comm
mdefine_line|#define ASIZ_task_comm&t;0x00000010
DECL|macro|AOFF_task_link_count
mdefine_line|#define AOFF_task_link_count&t;0x00000374
DECL|macro|ASIZ_task_link_count
mdefine_line|#define ASIZ_task_link_count&t;0x00000004
DECL|macro|AOFF_task_tty
mdefine_line|#define AOFF_task_tty&t;0x00000378
DECL|macro|ASIZ_task_tty
mdefine_line|#define ASIZ_task_tty&t;0x00000008
DECL|macro|AOFF_task_semundo
mdefine_line|#define AOFF_task_semundo&t;0x00000380
DECL|macro|ASIZ_task_semundo
mdefine_line|#define ASIZ_task_semundo&t;0x00000008
DECL|macro|AOFF_task_semsleeping
mdefine_line|#define AOFF_task_semsleeping&t;0x00000388
DECL|macro|ASIZ_task_semsleeping
mdefine_line|#define ASIZ_task_semsleeping&t;0x00000008
DECL|macro|AOFF_task_thread
mdefine_line|#define AOFF_task_thread&t;0x00000390
DECL|macro|ASIZ_task_thread
mdefine_line|#define ASIZ_task_thread&t;0x00000450
DECL|macro|AOFF_task_fs
mdefine_line|#define AOFF_task_fs&t;0x000007e0
DECL|macro|ASIZ_task_fs
mdefine_line|#define ASIZ_task_fs&t;0x00000008
DECL|macro|AOFF_task_files
mdefine_line|#define AOFF_task_files&t;0x000007e8
DECL|macro|ASIZ_task_files
mdefine_line|#define ASIZ_task_files&t;0x00000008
DECL|macro|AOFF_task_sigmask_lock
mdefine_line|#define AOFF_task_sigmask_lock&t;0x000007f0
DECL|macro|ASIZ_task_sigmask_lock
mdefine_line|#define ASIZ_task_sigmask_lock&t;0x00000004
DECL|macro|AOFF_task_sig
mdefine_line|#define AOFF_task_sig&t;0x000007f8
DECL|macro|ASIZ_task_sig
mdefine_line|#define ASIZ_task_sig&t;0x00000008
DECL|macro|AOFF_task_signal
mdefine_line|#define AOFF_task_signal&t;0x00000800
DECL|macro|ASIZ_task_signal
mdefine_line|#define ASIZ_task_signal&t;0x00000008
DECL|macro|AOFF_task_blocked
mdefine_line|#define AOFF_task_blocked&t;0x00000808
DECL|macro|ASIZ_task_blocked
mdefine_line|#define ASIZ_task_blocked&t;0x00000008
DECL|macro|AOFF_task_sigqueue
mdefine_line|#define AOFF_task_sigqueue&t;0x00000810
DECL|macro|ASIZ_task_sigqueue
mdefine_line|#define ASIZ_task_sigqueue&t;0x00000008
DECL|macro|AOFF_task_sigqueue_tail
mdefine_line|#define AOFF_task_sigqueue_tail&t;0x00000818
DECL|macro|ASIZ_task_sigqueue_tail
mdefine_line|#define ASIZ_task_sigqueue_tail&t;0x00000008
DECL|macro|AOFF_task_sas_ss_sp
mdefine_line|#define AOFF_task_sas_ss_sp&t;0x00000820
DECL|macro|ASIZ_task_sas_ss_sp
mdefine_line|#define ASIZ_task_sas_ss_sp&t;0x00000008
DECL|macro|AOFF_task_sas_ss_size
mdefine_line|#define AOFF_task_sas_ss_size&t;0x00000828
DECL|macro|ASIZ_task_sas_ss_size
mdefine_line|#define ASIZ_task_sas_ss_size&t;0x00000008
DECL|macro|AOFF_task_parent_exec_id
mdefine_line|#define AOFF_task_parent_exec_id&t;0x00000830
DECL|macro|ASIZ_task_parent_exec_id
mdefine_line|#define ASIZ_task_parent_exec_id&t;0x00000004
DECL|macro|AOFF_task_self_exec_id
mdefine_line|#define AOFF_task_self_exec_id&t;0x00000834
DECL|macro|ASIZ_task_self_exec_id
mdefine_line|#define ASIZ_task_self_exec_id&t;0x00000004
DECL|macro|AOFF_task_exit_sem
mdefine_line|#define AOFF_task_exit_sem&t;0x00000838
DECL|macro|ASIZ_task_exit_sem
mdefine_line|#define ASIZ_task_exit_sem&t;0x00000038
DECL|macro|ASIZ_task
mdefine_line|#define ASIZ_task&t;0x00000870
DECL|macro|AOFF_mm_mmap
mdefine_line|#define AOFF_mm_mmap&t;0x00000000
DECL|macro|ASIZ_mm_mmap
mdefine_line|#define ASIZ_mm_mmap&t;0x00000008
DECL|macro|AOFF_mm_mmap_avl
mdefine_line|#define AOFF_mm_mmap_avl&t;0x00000008
DECL|macro|ASIZ_mm_mmap_avl
mdefine_line|#define ASIZ_mm_mmap_avl&t;0x00000008
DECL|macro|AOFF_mm_mmap_cache
mdefine_line|#define AOFF_mm_mmap_cache&t;0x00000010
DECL|macro|ASIZ_mm_mmap_cache
mdefine_line|#define ASIZ_mm_mmap_cache&t;0x00000008
DECL|macro|AOFF_mm_pgd
mdefine_line|#define AOFF_mm_pgd&t;0x00000018
DECL|macro|ASIZ_mm_pgd
mdefine_line|#define ASIZ_mm_pgd&t;0x00000008
DECL|macro|AOFF_mm_mm_users
mdefine_line|#define AOFF_mm_mm_users&t;0x00000020
DECL|macro|ASIZ_mm_mm_users
mdefine_line|#define ASIZ_mm_mm_users&t;0x00000004
DECL|macro|AOFF_mm_mm_count
mdefine_line|#define AOFF_mm_mm_count&t;0x00000024
DECL|macro|ASIZ_mm_mm_count
mdefine_line|#define ASIZ_mm_mm_count&t;0x00000004
DECL|macro|AOFF_mm_map_count
mdefine_line|#define AOFF_mm_map_count&t;0x00000028
DECL|macro|ASIZ_mm_map_count
mdefine_line|#define ASIZ_mm_map_count&t;0x00000004
DECL|macro|AOFF_mm_mmap_sem
mdefine_line|#define AOFF_mm_mmap_sem&t;0x00000030
DECL|macro|ASIZ_mm_mmap_sem
mdefine_line|#define ASIZ_mm_mmap_sem&t;0x00000038
DECL|macro|AOFF_mm_page_table_lock
mdefine_line|#define AOFF_mm_page_table_lock&t;0x00000068
DECL|macro|ASIZ_mm_page_table_lock
mdefine_line|#define ASIZ_mm_page_table_lock&t;0x00000004
DECL|macro|AOFF_mm_context
mdefine_line|#define AOFF_mm_context&t;0x00000070
DECL|macro|ASIZ_mm_context
mdefine_line|#define ASIZ_mm_context&t;0x00000008
DECL|macro|AOFF_mm_start_code
mdefine_line|#define AOFF_mm_start_code&t;0x00000078
DECL|macro|ASIZ_mm_start_code
mdefine_line|#define ASIZ_mm_start_code&t;0x00000008
DECL|macro|AOFF_mm_end_code
mdefine_line|#define AOFF_mm_end_code&t;0x00000080
DECL|macro|ASIZ_mm_end_code
mdefine_line|#define ASIZ_mm_end_code&t;0x00000008
DECL|macro|AOFF_mm_start_data
mdefine_line|#define AOFF_mm_start_data&t;0x00000088
DECL|macro|ASIZ_mm_start_data
mdefine_line|#define ASIZ_mm_start_data&t;0x00000008
DECL|macro|AOFF_mm_end_data
mdefine_line|#define AOFF_mm_end_data&t;0x00000090
DECL|macro|ASIZ_mm_end_data
mdefine_line|#define ASIZ_mm_end_data&t;0x00000008
DECL|macro|AOFF_mm_start_brk
mdefine_line|#define AOFF_mm_start_brk&t;0x00000098
DECL|macro|ASIZ_mm_start_brk
mdefine_line|#define ASIZ_mm_start_brk&t;0x00000008
DECL|macro|AOFF_mm_brk
mdefine_line|#define AOFF_mm_brk&t;0x000000a0
DECL|macro|ASIZ_mm_brk
mdefine_line|#define ASIZ_mm_brk&t;0x00000008
DECL|macro|AOFF_mm_start_stack
mdefine_line|#define AOFF_mm_start_stack&t;0x000000a8
DECL|macro|ASIZ_mm_start_stack
mdefine_line|#define ASIZ_mm_start_stack&t;0x00000008
DECL|macro|AOFF_mm_arg_start
mdefine_line|#define AOFF_mm_arg_start&t;0x000000b0
DECL|macro|ASIZ_mm_arg_start
mdefine_line|#define ASIZ_mm_arg_start&t;0x00000008
DECL|macro|AOFF_mm_arg_end
mdefine_line|#define AOFF_mm_arg_end&t;0x000000b8
DECL|macro|ASIZ_mm_arg_end
mdefine_line|#define ASIZ_mm_arg_end&t;0x00000008
DECL|macro|AOFF_mm_env_start
mdefine_line|#define AOFF_mm_env_start&t;0x000000c0
DECL|macro|ASIZ_mm_env_start
mdefine_line|#define ASIZ_mm_env_start&t;0x00000008
DECL|macro|AOFF_mm_env_end
mdefine_line|#define AOFF_mm_env_end&t;0x000000c8
DECL|macro|ASIZ_mm_env_end
mdefine_line|#define ASIZ_mm_env_end&t;0x00000008
DECL|macro|AOFF_mm_rss
mdefine_line|#define AOFF_mm_rss&t;0x000000d0
DECL|macro|ASIZ_mm_rss
mdefine_line|#define ASIZ_mm_rss&t;0x00000008
DECL|macro|AOFF_mm_total_vm
mdefine_line|#define AOFF_mm_total_vm&t;0x000000d8
DECL|macro|ASIZ_mm_total_vm
mdefine_line|#define ASIZ_mm_total_vm&t;0x00000008
DECL|macro|AOFF_mm_locked_vm
mdefine_line|#define AOFF_mm_locked_vm&t;0x000000e0
DECL|macro|ASIZ_mm_locked_vm
mdefine_line|#define ASIZ_mm_locked_vm&t;0x00000008
DECL|macro|AOFF_mm_def_flags
mdefine_line|#define AOFF_mm_def_flags&t;0x000000e8
DECL|macro|ASIZ_mm_def_flags
mdefine_line|#define ASIZ_mm_def_flags&t;0x00000008
DECL|macro|AOFF_mm_cpu_vm_mask
mdefine_line|#define AOFF_mm_cpu_vm_mask&t;0x000000f0
DECL|macro|ASIZ_mm_cpu_vm_mask
mdefine_line|#define ASIZ_mm_cpu_vm_mask&t;0x00000008
DECL|macro|AOFF_mm_swap_cnt
mdefine_line|#define AOFF_mm_swap_cnt&t;0x000000f8
DECL|macro|ASIZ_mm_swap_cnt
mdefine_line|#define ASIZ_mm_swap_cnt&t;0x00000008
DECL|macro|AOFF_mm_swap_address
mdefine_line|#define AOFF_mm_swap_address&t;0x00000100
DECL|macro|ASIZ_mm_swap_address
mdefine_line|#define ASIZ_mm_swap_address&t;0x00000008
DECL|macro|AOFF_mm_segments
mdefine_line|#define AOFF_mm_segments&t;0x00000108
DECL|macro|ASIZ_mm_segments
mdefine_line|#define ASIZ_mm_segments&t;0x00000008
DECL|macro|ASIZ_mm
mdefine_line|#define ASIZ_mm&t;0x00000110
DECL|macro|AOFF_thread_ksp
mdefine_line|#define AOFF_thread_ksp&t;0x00000000
DECL|macro|ASIZ_thread_ksp
mdefine_line|#define ASIZ_thread_ksp&t;0x00000008
DECL|macro|AOFF_thread_wstate
mdefine_line|#define AOFF_thread_wstate&t;0x00000008
DECL|macro|ASIZ_thread_wstate
mdefine_line|#define ASIZ_thread_wstate&t;0x00000001
DECL|macro|AOFF_thread_cwp
mdefine_line|#define AOFF_thread_cwp&t;0x00000009
DECL|macro|ASIZ_thread_cwp
mdefine_line|#define ASIZ_thread_cwp&t;0x00000001
DECL|macro|AOFF_thread_flags
mdefine_line|#define AOFF_thread_flags&t;0x0000000a
DECL|macro|ASIZ_thread_flags
mdefine_line|#define ASIZ_thread_flags&t;0x00000001
DECL|macro|AOFF_thread_current_ds
mdefine_line|#define AOFF_thread_current_ds&t;0x0000000b
DECL|macro|ASIZ_thread_current_ds
mdefine_line|#define ASIZ_thread_current_ds&t;0x00000001
DECL|macro|AOFF_thread_w_saved
mdefine_line|#define AOFF_thread_w_saved&t;0x0000000c
DECL|macro|ASIZ_thread_w_saved
mdefine_line|#define ASIZ_thread_w_saved&t;0x00000001
DECL|macro|AOFF_thread_fpdepth
mdefine_line|#define AOFF_thread_fpdepth&t;0x0000000d
DECL|macro|ASIZ_thread_fpdepth
mdefine_line|#define ASIZ_thread_fpdepth&t;0x00000001
DECL|macro|AOFF_thread_fault_code
mdefine_line|#define AOFF_thread_fault_code&t;0x0000000e
DECL|macro|ASIZ_thread_fault_code
mdefine_line|#define ASIZ_thread_fault_code&t;0x00000001
DECL|macro|AOFF_thread_use_blkcommit
mdefine_line|#define AOFF_thread_use_blkcommit&t;0x0000000f
DECL|macro|ASIZ_thread_use_blkcommit
mdefine_line|#define ASIZ_thread_use_blkcommit&t;0x00000001
DECL|macro|AOFF_thread_fault_address
mdefine_line|#define AOFF_thread_fault_address&t;0x00000010
DECL|macro|ASIZ_thread_fault_address
mdefine_line|#define ASIZ_thread_fault_address&t;0x00000008
DECL|macro|AOFF_thread_fpsaved
mdefine_line|#define AOFF_thread_fpsaved&t;0x00000018
DECL|macro|ASIZ_thread_fpsaved
mdefine_line|#define ASIZ_thread_fpsaved&t;0x00000007
DECL|macro|AOFF_thread___pad2
mdefine_line|#define AOFF_thread___pad2&t;0x0000001f
DECL|macro|ASIZ_thread___pad2
mdefine_line|#define ASIZ_thread___pad2&t;0x00000001
DECL|macro|AOFF_thread_kregs
mdefine_line|#define AOFF_thread_kregs&t;0x00000020
DECL|macro|ASIZ_thread_kregs
mdefine_line|#define ASIZ_thread_kregs&t;0x00000008
DECL|macro|AOFF_thread_utraps
mdefine_line|#define AOFF_thread_utraps&t;0x00000028
DECL|macro|ASIZ_thread_utraps
mdefine_line|#define ASIZ_thread_utraps&t;0x00000008
DECL|macro|AOFF_thread_gsr
mdefine_line|#define AOFF_thread_gsr&t;0x00000030
DECL|macro|ASIZ_thread_gsr
mdefine_line|#define ASIZ_thread_gsr&t;0x00000007
DECL|macro|AOFF_thread___pad3
mdefine_line|#define AOFF_thread___pad3&t;0x00000037
DECL|macro|ASIZ_thread___pad3
mdefine_line|#define ASIZ_thread___pad3&t;0x00000001
DECL|macro|AOFF_thread_xfsr
mdefine_line|#define AOFF_thread_xfsr&t;0x00000038
DECL|macro|ASIZ_thread_xfsr
mdefine_line|#define ASIZ_thread_xfsr&t;0x00000038
DECL|macro|AOFF_thread_reg_window
mdefine_line|#define AOFF_thread_reg_window&t;0x00000070
DECL|macro|ASIZ_thread_reg_window
mdefine_line|#define ASIZ_thread_reg_window&t;0x00000380
DECL|macro|AOFF_thread_rwbuf_stkptrs
mdefine_line|#define AOFF_thread_rwbuf_stkptrs&t;0x000003f0
DECL|macro|ASIZ_thread_rwbuf_stkptrs
mdefine_line|#define ASIZ_thread_rwbuf_stkptrs&t;0x00000038
DECL|macro|AOFF_thread_user_cntd0
mdefine_line|#define AOFF_thread_user_cntd0&t;0x00000428
DECL|macro|ASIZ_thread_user_cntd0
mdefine_line|#define ASIZ_thread_user_cntd0&t;0x00000008
DECL|macro|AOFF_thread_user_cntd1
mdefine_line|#define AOFF_thread_user_cntd1&t;0x00000430
DECL|macro|ASIZ_thread_user_cntd1
mdefine_line|#define ASIZ_thread_user_cntd1&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd0
mdefine_line|#define AOFF_thread_kernel_cntd0&t;0x00000438
DECL|macro|ASIZ_thread_kernel_cntd0
mdefine_line|#define ASIZ_thread_kernel_cntd0&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd1
mdefine_line|#define AOFF_thread_kernel_cntd1&t;0x00000440
DECL|macro|ASIZ_thread_kernel_cntd1
mdefine_line|#define ASIZ_thread_kernel_cntd1&t;0x00000008
DECL|macro|AOFF_thread_pcr_reg
mdefine_line|#define AOFF_thread_pcr_reg&t;0x00000448
DECL|macro|ASIZ_thread_pcr_reg
mdefine_line|#define ASIZ_thread_pcr_reg&t;0x00000008
DECL|macro|ASIZ_thread
mdefine_line|#define ASIZ_thread&t;0x00000450
macro_line|#else /* CONFIG_SMP */
macro_line|#ifndef SPIN_LOCK_DEBUG
DECL|macro|AOFF_task_state
mdefine_line|#define AOFF_task_state&t;0x00000000
DECL|macro|ASIZ_task_state
mdefine_line|#define ASIZ_task_state&t;0x00000008
DECL|macro|AOFF_task_flags
mdefine_line|#define AOFF_task_flags&t;0x00000008
DECL|macro|ASIZ_task_flags
mdefine_line|#define ASIZ_task_flags&t;0x00000008
DECL|macro|AOFF_task_sigpending
mdefine_line|#define AOFF_task_sigpending&t;0x00000010
DECL|macro|ASIZ_task_sigpending
mdefine_line|#define ASIZ_task_sigpending&t;0x00000004
DECL|macro|AOFF_task_addr_limit
mdefine_line|#define AOFF_task_addr_limit&t;0x00000014
DECL|macro|ASIZ_task_addr_limit
mdefine_line|#define ASIZ_task_addr_limit&t;0x00000001
DECL|macro|AOFF_task_exec_domain
mdefine_line|#define AOFF_task_exec_domain&t;0x00000018
DECL|macro|ASIZ_task_exec_domain
mdefine_line|#define ASIZ_task_exec_domain&t;0x00000008
DECL|macro|AOFF_task_need_resched
mdefine_line|#define AOFF_task_need_resched&t;0x00000020
DECL|macro|ASIZ_task_need_resched
mdefine_line|#define ASIZ_task_need_resched&t;0x00000008
DECL|macro|AOFF_task_avg_slice
mdefine_line|#define AOFF_task_avg_slice&t;0x00000028
DECL|macro|ASIZ_task_avg_slice
mdefine_line|#define ASIZ_task_avg_slice&t;0x00000008
DECL|macro|AOFF_task_lock_depth
mdefine_line|#define AOFF_task_lock_depth&t;0x00000030
DECL|macro|ASIZ_task_lock_depth
mdefine_line|#define ASIZ_task_lock_depth&t;0x00000004
DECL|macro|AOFF_task_counter
mdefine_line|#define AOFF_task_counter&t;0x00000038
DECL|macro|ASIZ_task_counter
mdefine_line|#define ASIZ_task_counter&t;0x00000008
DECL|macro|AOFF_task_priority
mdefine_line|#define AOFF_task_priority&t;0x00000040
DECL|macro|ASIZ_task_priority
mdefine_line|#define ASIZ_task_priority&t;0x00000008
DECL|macro|AOFF_task_policy
mdefine_line|#define AOFF_task_policy&t;0x00000048
DECL|macro|ASIZ_task_policy
mdefine_line|#define ASIZ_task_policy&t;0x00000008
DECL|macro|AOFF_task_mm
mdefine_line|#define AOFF_task_mm&t;0x00000050
DECL|macro|ASIZ_task_mm
mdefine_line|#define ASIZ_task_mm&t;0x00000008
DECL|macro|AOFF_task_active_mm
mdefine_line|#define AOFF_task_active_mm&t;0x00000058
DECL|macro|ASIZ_task_active_mm
mdefine_line|#define ASIZ_task_active_mm&t;0x00000008
DECL|macro|AOFF_task_has_cpu
mdefine_line|#define AOFF_task_has_cpu&t;0x00000060
DECL|macro|ASIZ_task_has_cpu
mdefine_line|#define ASIZ_task_has_cpu&t;0x00000004
DECL|macro|AOFF_task_processor
mdefine_line|#define AOFF_task_processor&t;0x00000064
DECL|macro|ASIZ_task_processor
mdefine_line|#define ASIZ_task_processor&t;0x00000004
DECL|macro|AOFF_task_run_list
mdefine_line|#define AOFF_task_run_list&t;0x00000068
DECL|macro|ASIZ_task_run_list
mdefine_line|#define ASIZ_task_run_list&t;0x00000010
DECL|macro|AOFF_task_next_task
mdefine_line|#define AOFF_task_next_task&t;0x00000078
DECL|macro|ASIZ_task_next_task
mdefine_line|#define ASIZ_task_next_task&t;0x00000008
DECL|macro|AOFF_task_prev_task
mdefine_line|#define AOFF_task_prev_task&t;0x00000080
DECL|macro|ASIZ_task_prev_task
mdefine_line|#define ASIZ_task_prev_task&t;0x00000008
DECL|macro|AOFF_task_last_processor
mdefine_line|#define AOFF_task_last_processor&t;0x00000088
DECL|macro|ASIZ_task_last_processor
mdefine_line|#define ASIZ_task_last_processor&t;0x00000004
DECL|macro|AOFF_task_binfmt
mdefine_line|#define AOFF_task_binfmt&t;0x00000090
DECL|macro|ASIZ_task_binfmt
mdefine_line|#define ASIZ_task_binfmt&t;0x00000008
DECL|macro|AOFF_task_exit_code
mdefine_line|#define AOFF_task_exit_code&t;0x00000098
DECL|macro|ASIZ_task_exit_code
mdefine_line|#define ASIZ_task_exit_code&t;0x00000004
DECL|macro|AOFF_task_exit_signal
mdefine_line|#define AOFF_task_exit_signal&t;0x0000009c
DECL|macro|ASIZ_task_exit_signal
mdefine_line|#define ASIZ_task_exit_signal&t;0x00000004
DECL|macro|AOFF_task_pdeath_signal
mdefine_line|#define AOFF_task_pdeath_signal&t;0x000000a0
DECL|macro|ASIZ_task_pdeath_signal
mdefine_line|#define ASIZ_task_pdeath_signal&t;0x00000004
DECL|macro|AOFF_task_personality
mdefine_line|#define AOFF_task_personality&t;0x000000a8
DECL|macro|ASIZ_task_personality
mdefine_line|#define ASIZ_task_personality&t;0x00000008
DECL|macro|AOFF_task_pid
mdefine_line|#define AOFF_task_pid&t;0x000000b4
DECL|macro|ASIZ_task_pid
mdefine_line|#define ASIZ_task_pid&t;0x00000004
DECL|macro|AOFF_task_pgrp
mdefine_line|#define AOFF_task_pgrp&t;0x000000b8
DECL|macro|ASIZ_task_pgrp
mdefine_line|#define ASIZ_task_pgrp&t;0x00000004
DECL|macro|AOFF_task_tty_old_pgrp
mdefine_line|#define AOFF_task_tty_old_pgrp&t;0x000000bc
DECL|macro|ASIZ_task_tty_old_pgrp
mdefine_line|#define ASIZ_task_tty_old_pgrp&t;0x00000004
DECL|macro|AOFF_task_session
mdefine_line|#define AOFF_task_session&t;0x000000c0
DECL|macro|ASIZ_task_session
mdefine_line|#define ASIZ_task_session&t;0x00000004
DECL|macro|AOFF_task_leader
mdefine_line|#define AOFF_task_leader&t;0x000000c4
DECL|macro|ASIZ_task_leader
mdefine_line|#define ASIZ_task_leader&t;0x00000004
DECL|macro|AOFF_task_p_opptr
mdefine_line|#define AOFF_task_p_opptr&t;0x000000c8
DECL|macro|ASIZ_task_p_opptr
mdefine_line|#define ASIZ_task_p_opptr&t;0x00000008
DECL|macro|AOFF_task_p_pptr
mdefine_line|#define AOFF_task_p_pptr&t;0x000000d0
DECL|macro|ASIZ_task_p_pptr
mdefine_line|#define ASIZ_task_p_pptr&t;0x00000008
DECL|macro|AOFF_task_p_cptr
mdefine_line|#define AOFF_task_p_cptr&t;0x000000d8
DECL|macro|ASIZ_task_p_cptr
mdefine_line|#define ASIZ_task_p_cptr&t;0x00000008
DECL|macro|AOFF_task_p_ysptr
mdefine_line|#define AOFF_task_p_ysptr&t;0x000000e0
DECL|macro|ASIZ_task_p_ysptr
mdefine_line|#define ASIZ_task_p_ysptr&t;0x00000008
DECL|macro|AOFF_task_p_osptr
mdefine_line|#define AOFF_task_p_osptr&t;0x000000e8
DECL|macro|ASIZ_task_p_osptr
mdefine_line|#define ASIZ_task_p_osptr&t;0x00000008
DECL|macro|AOFF_task_pidhash_next
mdefine_line|#define AOFF_task_pidhash_next&t;0x000000f0
DECL|macro|ASIZ_task_pidhash_next
mdefine_line|#define ASIZ_task_pidhash_next&t;0x00000008
DECL|macro|AOFF_task_pidhash_pprev
mdefine_line|#define AOFF_task_pidhash_pprev&t;0x000000f8
DECL|macro|ASIZ_task_pidhash_pprev
mdefine_line|#define ASIZ_task_pidhash_pprev&t;0x00000008
DECL|macro|AOFF_task_wait_chldexit
mdefine_line|#define AOFF_task_wait_chldexit&t;0x00000100
DECL|macro|ASIZ_task_wait_chldexit
mdefine_line|#define ASIZ_task_wait_chldexit&t;0x00000028
DECL|macro|AOFF_task_vfork_sem
mdefine_line|#define AOFF_task_vfork_sem&t;0x00000128
DECL|macro|ASIZ_task_vfork_sem
mdefine_line|#define ASIZ_task_vfork_sem&t;0x00000008
DECL|macro|AOFF_task_rt_priority
mdefine_line|#define AOFF_task_rt_priority&t;0x00000130
DECL|macro|ASIZ_task_rt_priority
mdefine_line|#define ASIZ_task_rt_priority&t;0x00000008
DECL|macro|AOFF_task_it_real_value
mdefine_line|#define AOFF_task_it_real_value&t;0x00000138
DECL|macro|ASIZ_task_it_real_value
mdefine_line|#define ASIZ_task_it_real_value&t;0x00000008
DECL|macro|AOFF_task_it_prof_value
mdefine_line|#define AOFF_task_it_prof_value&t;0x00000140
DECL|macro|ASIZ_task_it_prof_value
mdefine_line|#define ASIZ_task_it_prof_value&t;0x00000008
DECL|macro|AOFF_task_it_virt_value
mdefine_line|#define AOFF_task_it_virt_value&t;0x00000148
DECL|macro|ASIZ_task_it_virt_value
mdefine_line|#define ASIZ_task_it_virt_value&t;0x00000008
DECL|macro|AOFF_task_it_real_incr
mdefine_line|#define AOFF_task_it_real_incr&t;0x00000150
DECL|macro|ASIZ_task_it_real_incr
mdefine_line|#define ASIZ_task_it_real_incr&t;0x00000008
DECL|macro|AOFF_task_it_prof_incr
mdefine_line|#define AOFF_task_it_prof_incr&t;0x00000158
DECL|macro|ASIZ_task_it_prof_incr
mdefine_line|#define ASIZ_task_it_prof_incr&t;0x00000008
DECL|macro|AOFF_task_it_virt_incr
mdefine_line|#define AOFF_task_it_virt_incr&t;0x00000160
DECL|macro|ASIZ_task_it_virt_incr
mdefine_line|#define ASIZ_task_it_virt_incr&t;0x00000008
DECL|macro|AOFF_task_real_timer
mdefine_line|#define AOFF_task_real_timer&t;0x00000168
DECL|macro|ASIZ_task_real_timer
mdefine_line|#define ASIZ_task_real_timer&t;0x00000030
DECL|macro|AOFF_task_times
mdefine_line|#define AOFF_task_times&t;0x00000198
DECL|macro|ASIZ_task_times
mdefine_line|#define ASIZ_task_times&t;0x00000020
DECL|macro|AOFF_task_start_time
mdefine_line|#define AOFF_task_start_time&t;0x000001b8
DECL|macro|ASIZ_task_start_time
mdefine_line|#define ASIZ_task_start_time&t;0x00000008
DECL|macro|AOFF_task_per_cpu_utime
mdefine_line|#define AOFF_task_per_cpu_utime&t;0x000001c0
DECL|macro|ASIZ_task_per_cpu_utime
mdefine_line|#define ASIZ_task_per_cpu_utime&t;0x00000100
DECL|macro|AOFF_task_min_flt
mdefine_line|#define AOFF_task_min_flt&t;0x000003c0
DECL|macro|ASIZ_task_min_flt
mdefine_line|#define ASIZ_task_min_flt&t;0x00000008
DECL|macro|AOFF_task_maj_flt
mdefine_line|#define AOFF_task_maj_flt&t;0x000003c8
DECL|macro|ASIZ_task_maj_flt
mdefine_line|#define ASIZ_task_maj_flt&t;0x00000008
DECL|macro|AOFF_task_nswap
mdefine_line|#define AOFF_task_nswap&t;0x000003d0
DECL|macro|ASIZ_task_nswap
mdefine_line|#define ASIZ_task_nswap&t;0x00000008
DECL|macro|AOFF_task_cmin_flt
mdefine_line|#define AOFF_task_cmin_flt&t;0x000003d8
DECL|macro|ASIZ_task_cmin_flt
mdefine_line|#define ASIZ_task_cmin_flt&t;0x00000008
DECL|macro|AOFF_task_cmaj_flt
mdefine_line|#define AOFF_task_cmaj_flt&t;0x000003e0
DECL|macro|ASIZ_task_cmaj_flt
mdefine_line|#define ASIZ_task_cmaj_flt&t;0x00000008
DECL|macro|AOFF_task_cnswap
mdefine_line|#define AOFF_task_cnswap&t;0x000003e8
DECL|macro|ASIZ_task_cnswap
mdefine_line|#define ASIZ_task_cnswap&t;0x00000008
DECL|macro|AOFF_task_uid
mdefine_line|#define AOFF_task_uid&t;0x000003f4
DECL|macro|ASIZ_task_uid
mdefine_line|#define ASIZ_task_uid&t;0x00000004
DECL|macro|AOFF_task_euid
mdefine_line|#define AOFF_task_euid&t;0x000003f8
DECL|macro|ASIZ_task_euid
mdefine_line|#define ASIZ_task_euid&t;0x00000004
DECL|macro|AOFF_task_suid
mdefine_line|#define AOFF_task_suid&t;0x000003fc
DECL|macro|ASIZ_task_suid
mdefine_line|#define ASIZ_task_suid&t;0x00000004
DECL|macro|AOFF_task_fsuid
mdefine_line|#define AOFF_task_fsuid&t;0x00000400
DECL|macro|ASIZ_task_fsuid
mdefine_line|#define ASIZ_task_fsuid&t;0x00000004
DECL|macro|AOFF_task_gid
mdefine_line|#define AOFF_task_gid&t;0x00000404
DECL|macro|ASIZ_task_gid
mdefine_line|#define ASIZ_task_gid&t;0x00000004
DECL|macro|AOFF_task_egid
mdefine_line|#define AOFF_task_egid&t;0x00000408
DECL|macro|ASIZ_task_egid
mdefine_line|#define ASIZ_task_egid&t;0x00000004
DECL|macro|AOFF_task_sgid
mdefine_line|#define AOFF_task_sgid&t;0x0000040c
DECL|macro|ASIZ_task_sgid
mdefine_line|#define ASIZ_task_sgid&t;0x00000004
DECL|macro|AOFF_task_fsgid
mdefine_line|#define AOFF_task_fsgid&t;0x00000410
DECL|macro|ASIZ_task_fsgid
mdefine_line|#define ASIZ_task_fsgid&t;0x00000004
DECL|macro|AOFF_task_ngroups
mdefine_line|#define AOFF_task_ngroups&t;0x00000414
DECL|macro|ASIZ_task_ngroups
mdefine_line|#define ASIZ_task_ngroups&t;0x00000004
DECL|macro|AOFF_task_groups
mdefine_line|#define AOFF_task_groups&t;0x00000418
DECL|macro|ASIZ_task_groups
mdefine_line|#define ASIZ_task_groups&t;0x00000080
DECL|macro|AOFF_task_cap_effective
mdefine_line|#define AOFF_task_cap_effective&t;0x00000498
DECL|macro|ASIZ_task_cap_effective
mdefine_line|#define ASIZ_task_cap_effective&t;0x00000004
DECL|macro|AOFF_task_cap_inheritable
mdefine_line|#define AOFF_task_cap_inheritable&t;0x0000049c
DECL|macro|ASIZ_task_cap_inheritable
mdefine_line|#define ASIZ_task_cap_inheritable&t;0x00000004
DECL|macro|AOFF_task_cap_permitted
mdefine_line|#define AOFF_task_cap_permitted&t;0x000004a0
DECL|macro|ASIZ_task_cap_permitted
mdefine_line|#define ASIZ_task_cap_permitted&t;0x00000004
DECL|macro|AOFF_task_user
mdefine_line|#define AOFF_task_user&t;0x000004a8
DECL|macro|ASIZ_task_user
mdefine_line|#define ASIZ_task_user&t;0x00000008
DECL|macro|AOFF_task_rlim
mdefine_line|#define AOFF_task_rlim&t;0x000004b0
DECL|macro|ASIZ_task_rlim
mdefine_line|#define ASIZ_task_rlim&t;0x000000a0
DECL|macro|AOFF_task_used_math
mdefine_line|#define AOFF_task_used_math&t;0x00000550
DECL|macro|ASIZ_task_used_math
mdefine_line|#define ASIZ_task_used_math&t;0x00000002
DECL|macro|AOFF_task_comm
mdefine_line|#define AOFF_task_comm&t;0x00000552
DECL|macro|ASIZ_task_comm
mdefine_line|#define ASIZ_task_comm&t;0x00000010
DECL|macro|AOFF_task_link_count
mdefine_line|#define AOFF_task_link_count&t;0x00000564
DECL|macro|ASIZ_task_link_count
mdefine_line|#define ASIZ_task_link_count&t;0x00000004
DECL|macro|AOFF_task_tty
mdefine_line|#define AOFF_task_tty&t;0x00000568
DECL|macro|ASIZ_task_tty
mdefine_line|#define ASIZ_task_tty&t;0x00000008
DECL|macro|AOFF_task_semundo
mdefine_line|#define AOFF_task_semundo&t;0x00000570
DECL|macro|ASIZ_task_semundo
mdefine_line|#define ASIZ_task_semundo&t;0x00000008
DECL|macro|AOFF_task_semsleeping
mdefine_line|#define AOFF_task_semsleeping&t;0x00000578
DECL|macro|ASIZ_task_semsleeping
mdefine_line|#define ASIZ_task_semsleeping&t;0x00000008
DECL|macro|AOFF_task_thread
mdefine_line|#define AOFF_task_thread&t;0x00000580
DECL|macro|ASIZ_task_thread
mdefine_line|#define ASIZ_task_thread&t;0x00000450
DECL|macro|AOFF_task_fs
mdefine_line|#define AOFF_task_fs&t;0x000009d0
DECL|macro|ASIZ_task_fs
mdefine_line|#define ASIZ_task_fs&t;0x00000008
DECL|macro|AOFF_task_files
mdefine_line|#define AOFF_task_files&t;0x000009d8
DECL|macro|ASIZ_task_files
mdefine_line|#define ASIZ_task_files&t;0x00000008
DECL|macro|AOFF_task_sigmask_lock
mdefine_line|#define AOFF_task_sigmask_lock&t;0x000009e0
DECL|macro|ASIZ_task_sigmask_lock
mdefine_line|#define ASIZ_task_sigmask_lock&t;0x00000001
DECL|macro|AOFF_task_sig
mdefine_line|#define AOFF_task_sig&t;0x000009e8
DECL|macro|ASIZ_task_sig
mdefine_line|#define ASIZ_task_sig&t;0x00000008
DECL|macro|AOFF_task_signal
mdefine_line|#define AOFF_task_signal&t;0x000009f0
DECL|macro|ASIZ_task_signal
mdefine_line|#define ASIZ_task_signal&t;0x00000008
DECL|macro|AOFF_task_blocked
mdefine_line|#define AOFF_task_blocked&t;0x000009f8
DECL|macro|ASIZ_task_blocked
mdefine_line|#define ASIZ_task_blocked&t;0x00000008
DECL|macro|AOFF_task_sigqueue
mdefine_line|#define AOFF_task_sigqueue&t;0x00000a00
DECL|macro|ASIZ_task_sigqueue
mdefine_line|#define ASIZ_task_sigqueue&t;0x00000008
DECL|macro|AOFF_task_sigqueue_tail
mdefine_line|#define AOFF_task_sigqueue_tail&t;0x00000a08
DECL|macro|ASIZ_task_sigqueue_tail
mdefine_line|#define ASIZ_task_sigqueue_tail&t;0x00000008
DECL|macro|AOFF_task_sas_ss_sp
mdefine_line|#define AOFF_task_sas_ss_sp&t;0x00000a10
DECL|macro|ASIZ_task_sas_ss_sp
mdefine_line|#define ASIZ_task_sas_ss_sp&t;0x00000008
DECL|macro|AOFF_task_sas_ss_size
mdefine_line|#define AOFF_task_sas_ss_size&t;0x00000a18
DECL|macro|ASIZ_task_sas_ss_size
mdefine_line|#define ASIZ_task_sas_ss_size&t;0x00000008
DECL|macro|AOFF_task_parent_exec_id
mdefine_line|#define AOFF_task_parent_exec_id&t;0x00000a20
DECL|macro|ASIZ_task_parent_exec_id
mdefine_line|#define ASIZ_task_parent_exec_id&t;0x00000004
DECL|macro|AOFF_task_self_exec_id
mdefine_line|#define AOFF_task_self_exec_id&t;0x00000a24
DECL|macro|ASIZ_task_self_exec_id
mdefine_line|#define ASIZ_task_self_exec_id&t;0x00000004
DECL|macro|AOFF_task_exit_sem
mdefine_line|#define AOFF_task_exit_sem&t;0x00000a28
DECL|macro|ASIZ_task_exit_sem
mdefine_line|#define ASIZ_task_exit_sem&t;0x00000038
DECL|macro|ASIZ_task
mdefine_line|#define ASIZ_task&t;0x00000a60
DECL|macro|AOFF_mm_mmap
mdefine_line|#define AOFF_mm_mmap&t;0x00000000
DECL|macro|ASIZ_mm_mmap
mdefine_line|#define ASIZ_mm_mmap&t;0x00000008
DECL|macro|AOFF_mm_mmap_avl
mdefine_line|#define AOFF_mm_mmap_avl&t;0x00000008
DECL|macro|ASIZ_mm_mmap_avl
mdefine_line|#define ASIZ_mm_mmap_avl&t;0x00000008
DECL|macro|AOFF_mm_mmap_cache
mdefine_line|#define AOFF_mm_mmap_cache&t;0x00000010
DECL|macro|ASIZ_mm_mmap_cache
mdefine_line|#define ASIZ_mm_mmap_cache&t;0x00000008
DECL|macro|AOFF_mm_pgd
mdefine_line|#define AOFF_mm_pgd&t;0x00000018
DECL|macro|ASIZ_mm_pgd
mdefine_line|#define ASIZ_mm_pgd&t;0x00000008
DECL|macro|AOFF_mm_mm_users
mdefine_line|#define AOFF_mm_mm_users&t;0x00000020
DECL|macro|ASIZ_mm_mm_users
mdefine_line|#define ASIZ_mm_mm_users&t;0x00000004
DECL|macro|AOFF_mm_mm_count
mdefine_line|#define AOFF_mm_mm_count&t;0x00000024
DECL|macro|ASIZ_mm_mm_count
mdefine_line|#define ASIZ_mm_mm_count&t;0x00000004
DECL|macro|AOFF_mm_map_count
mdefine_line|#define AOFF_mm_map_count&t;0x00000028
DECL|macro|ASIZ_mm_map_count
mdefine_line|#define ASIZ_mm_map_count&t;0x00000004
DECL|macro|AOFF_mm_mmap_sem
mdefine_line|#define AOFF_mm_mmap_sem&t;0x00000030
DECL|macro|ASIZ_mm_mmap_sem
mdefine_line|#define ASIZ_mm_mmap_sem&t;0x00000038
DECL|macro|AOFF_mm_page_table_lock
mdefine_line|#define AOFF_mm_page_table_lock&t;0x00000068
DECL|macro|ASIZ_mm_page_table_lock
mdefine_line|#define ASIZ_mm_page_table_lock&t;0x00000001
DECL|macro|AOFF_mm_context
mdefine_line|#define AOFF_mm_context&t;0x00000070
DECL|macro|ASIZ_mm_context
mdefine_line|#define ASIZ_mm_context&t;0x00000008
DECL|macro|AOFF_mm_start_code
mdefine_line|#define AOFF_mm_start_code&t;0x00000078
DECL|macro|ASIZ_mm_start_code
mdefine_line|#define ASIZ_mm_start_code&t;0x00000008
DECL|macro|AOFF_mm_end_code
mdefine_line|#define AOFF_mm_end_code&t;0x00000080
DECL|macro|ASIZ_mm_end_code
mdefine_line|#define ASIZ_mm_end_code&t;0x00000008
DECL|macro|AOFF_mm_start_data
mdefine_line|#define AOFF_mm_start_data&t;0x00000088
DECL|macro|ASIZ_mm_start_data
mdefine_line|#define ASIZ_mm_start_data&t;0x00000008
DECL|macro|AOFF_mm_end_data
mdefine_line|#define AOFF_mm_end_data&t;0x00000090
DECL|macro|ASIZ_mm_end_data
mdefine_line|#define ASIZ_mm_end_data&t;0x00000008
DECL|macro|AOFF_mm_start_brk
mdefine_line|#define AOFF_mm_start_brk&t;0x00000098
DECL|macro|ASIZ_mm_start_brk
mdefine_line|#define ASIZ_mm_start_brk&t;0x00000008
DECL|macro|AOFF_mm_brk
mdefine_line|#define AOFF_mm_brk&t;0x000000a0
DECL|macro|ASIZ_mm_brk
mdefine_line|#define ASIZ_mm_brk&t;0x00000008
DECL|macro|AOFF_mm_start_stack
mdefine_line|#define AOFF_mm_start_stack&t;0x000000a8
DECL|macro|ASIZ_mm_start_stack
mdefine_line|#define ASIZ_mm_start_stack&t;0x00000008
DECL|macro|AOFF_mm_arg_start
mdefine_line|#define AOFF_mm_arg_start&t;0x000000b0
DECL|macro|ASIZ_mm_arg_start
mdefine_line|#define ASIZ_mm_arg_start&t;0x00000008
DECL|macro|AOFF_mm_arg_end
mdefine_line|#define AOFF_mm_arg_end&t;0x000000b8
DECL|macro|ASIZ_mm_arg_end
mdefine_line|#define ASIZ_mm_arg_end&t;0x00000008
DECL|macro|AOFF_mm_env_start
mdefine_line|#define AOFF_mm_env_start&t;0x000000c0
DECL|macro|ASIZ_mm_env_start
mdefine_line|#define ASIZ_mm_env_start&t;0x00000008
DECL|macro|AOFF_mm_env_end
mdefine_line|#define AOFF_mm_env_end&t;0x000000c8
DECL|macro|ASIZ_mm_env_end
mdefine_line|#define ASIZ_mm_env_end&t;0x00000008
DECL|macro|AOFF_mm_rss
mdefine_line|#define AOFF_mm_rss&t;0x000000d0
DECL|macro|ASIZ_mm_rss
mdefine_line|#define ASIZ_mm_rss&t;0x00000008
DECL|macro|AOFF_mm_total_vm
mdefine_line|#define AOFF_mm_total_vm&t;0x000000d8
DECL|macro|ASIZ_mm_total_vm
mdefine_line|#define ASIZ_mm_total_vm&t;0x00000008
DECL|macro|AOFF_mm_locked_vm
mdefine_line|#define AOFF_mm_locked_vm&t;0x000000e0
DECL|macro|ASIZ_mm_locked_vm
mdefine_line|#define ASIZ_mm_locked_vm&t;0x00000008
DECL|macro|AOFF_mm_def_flags
mdefine_line|#define AOFF_mm_def_flags&t;0x000000e8
DECL|macro|ASIZ_mm_def_flags
mdefine_line|#define ASIZ_mm_def_flags&t;0x00000008
DECL|macro|AOFF_mm_cpu_vm_mask
mdefine_line|#define AOFF_mm_cpu_vm_mask&t;0x000000f0
DECL|macro|ASIZ_mm_cpu_vm_mask
mdefine_line|#define ASIZ_mm_cpu_vm_mask&t;0x00000008
DECL|macro|AOFF_mm_swap_cnt
mdefine_line|#define AOFF_mm_swap_cnt&t;0x000000f8
DECL|macro|ASIZ_mm_swap_cnt
mdefine_line|#define ASIZ_mm_swap_cnt&t;0x00000008
DECL|macro|AOFF_mm_swap_address
mdefine_line|#define AOFF_mm_swap_address&t;0x00000100
DECL|macro|ASIZ_mm_swap_address
mdefine_line|#define ASIZ_mm_swap_address&t;0x00000008
DECL|macro|AOFF_mm_segments
mdefine_line|#define AOFF_mm_segments&t;0x00000108
DECL|macro|ASIZ_mm_segments
mdefine_line|#define ASIZ_mm_segments&t;0x00000008
DECL|macro|ASIZ_mm
mdefine_line|#define ASIZ_mm&t;0x00000110
DECL|macro|AOFF_thread_ksp
mdefine_line|#define AOFF_thread_ksp&t;0x00000000
DECL|macro|ASIZ_thread_ksp
mdefine_line|#define ASIZ_thread_ksp&t;0x00000008
DECL|macro|AOFF_thread_wstate
mdefine_line|#define AOFF_thread_wstate&t;0x00000008
DECL|macro|ASIZ_thread_wstate
mdefine_line|#define ASIZ_thread_wstate&t;0x00000001
DECL|macro|AOFF_thread_cwp
mdefine_line|#define AOFF_thread_cwp&t;0x00000009
DECL|macro|ASIZ_thread_cwp
mdefine_line|#define ASIZ_thread_cwp&t;0x00000001
DECL|macro|AOFF_thread_flags
mdefine_line|#define AOFF_thread_flags&t;0x0000000a
DECL|macro|ASIZ_thread_flags
mdefine_line|#define ASIZ_thread_flags&t;0x00000001
DECL|macro|AOFF_thread_current_ds
mdefine_line|#define AOFF_thread_current_ds&t;0x0000000b
DECL|macro|ASIZ_thread_current_ds
mdefine_line|#define ASIZ_thread_current_ds&t;0x00000001
DECL|macro|AOFF_thread_w_saved
mdefine_line|#define AOFF_thread_w_saved&t;0x0000000c
DECL|macro|ASIZ_thread_w_saved
mdefine_line|#define ASIZ_thread_w_saved&t;0x00000001
DECL|macro|AOFF_thread_fpdepth
mdefine_line|#define AOFF_thread_fpdepth&t;0x0000000d
DECL|macro|ASIZ_thread_fpdepth
mdefine_line|#define ASIZ_thread_fpdepth&t;0x00000001
DECL|macro|AOFF_thread_fault_code
mdefine_line|#define AOFF_thread_fault_code&t;0x0000000e
DECL|macro|ASIZ_thread_fault_code
mdefine_line|#define ASIZ_thread_fault_code&t;0x00000001
DECL|macro|AOFF_thread_use_blkcommit
mdefine_line|#define AOFF_thread_use_blkcommit&t;0x0000000f
DECL|macro|ASIZ_thread_use_blkcommit
mdefine_line|#define ASIZ_thread_use_blkcommit&t;0x00000001
DECL|macro|AOFF_thread_fault_address
mdefine_line|#define AOFF_thread_fault_address&t;0x00000010
DECL|macro|ASIZ_thread_fault_address
mdefine_line|#define ASIZ_thread_fault_address&t;0x00000008
DECL|macro|AOFF_thread_fpsaved
mdefine_line|#define AOFF_thread_fpsaved&t;0x00000018
DECL|macro|ASIZ_thread_fpsaved
mdefine_line|#define ASIZ_thread_fpsaved&t;0x00000007
DECL|macro|AOFF_thread___pad2
mdefine_line|#define AOFF_thread___pad2&t;0x0000001f
DECL|macro|ASIZ_thread___pad2
mdefine_line|#define ASIZ_thread___pad2&t;0x00000001
DECL|macro|AOFF_thread_kregs
mdefine_line|#define AOFF_thread_kregs&t;0x00000020
DECL|macro|ASIZ_thread_kregs
mdefine_line|#define ASIZ_thread_kregs&t;0x00000008
DECL|macro|AOFF_thread_utraps
mdefine_line|#define AOFF_thread_utraps&t;0x00000028
DECL|macro|ASIZ_thread_utraps
mdefine_line|#define ASIZ_thread_utraps&t;0x00000008
DECL|macro|AOFF_thread_gsr
mdefine_line|#define AOFF_thread_gsr&t;0x00000030
DECL|macro|ASIZ_thread_gsr
mdefine_line|#define ASIZ_thread_gsr&t;0x00000007
DECL|macro|AOFF_thread___pad3
mdefine_line|#define AOFF_thread___pad3&t;0x00000037
DECL|macro|ASIZ_thread___pad3
mdefine_line|#define ASIZ_thread___pad3&t;0x00000001
DECL|macro|AOFF_thread_xfsr
mdefine_line|#define AOFF_thread_xfsr&t;0x00000038
DECL|macro|ASIZ_thread_xfsr
mdefine_line|#define ASIZ_thread_xfsr&t;0x00000038
DECL|macro|AOFF_thread_reg_window
mdefine_line|#define AOFF_thread_reg_window&t;0x00000070
DECL|macro|ASIZ_thread_reg_window
mdefine_line|#define ASIZ_thread_reg_window&t;0x00000380
DECL|macro|AOFF_thread_rwbuf_stkptrs
mdefine_line|#define AOFF_thread_rwbuf_stkptrs&t;0x000003f0
DECL|macro|ASIZ_thread_rwbuf_stkptrs
mdefine_line|#define ASIZ_thread_rwbuf_stkptrs&t;0x00000038
DECL|macro|AOFF_thread_user_cntd0
mdefine_line|#define AOFF_thread_user_cntd0&t;0x00000428
DECL|macro|ASIZ_thread_user_cntd0
mdefine_line|#define ASIZ_thread_user_cntd0&t;0x00000008
DECL|macro|AOFF_thread_user_cntd1
mdefine_line|#define AOFF_thread_user_cntd1&t;0x00000430
DECL|macro|ASIZ_thread_user_cntd1
mdefine_line|#define ASIZ_thread_user_cntd1&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd0
mdefine_line|#define AOFF_thread_kernel_cntd0&t;0x00000438
DECL|macro|ASIZ_thread_kernel_cntd0
mdefine_line|#define ASIZ_thread_kernel_cntd0&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd1
mdefine_line|#define AOFF_thread_kernel_cntd1&t;0x00000440
DECL|macro|ASIZ_thread_kernel_cntd1
mdefine_line|#define ASIZ_thread_kernel_cntd1&t;0x00000008
DECL|macro|AOFF_thread_pcr_reg
mdefine_line|#define AOFF_thread_pcr_reg&t;0x00000448
DECL|macro|ASIZ_thread_pcr_reg
mdefine_line|#define ASIZ_thread_pcr_reg&t;0x00000008
DECL|macro|ASIZ_thread
mdefine_line|#define ASIZ_thread&t;0x00000450
macro_line|#else /* SPIN_LOCK_DEBUG */
DECL|macro|AOFF_task_state
mdefine_line|#define AOFF_task_state&t;0x00000000
DECL|macro|ASIZ_task_state
mdefine_line|#define ASIZ_task_state&t;0x00000008
DECL|macro|AOFF_task_flags
mdefine_line|#define AOFF_task_flags&t;0x00000008
DECL|macro|ASIZ_task_flags
mdefine_line|#define ASIZ_task_flags&t;0x00000008
DECL|macro|AOFF_task_sigpending
mdefine_line|#define AOFF_task_sigpending&t;0x00000010
DECL|macro|ASIZ_task_sigpending
mdefine_line|#define ASIZ_task_sigpending&t;0x00000004
DECL|macro|AOFF_task_addr_limit
mdefine_line|#define AOFF_task_addr_limit&t;0x00000014
DECL|macro|ASIZ_task_addr_limit
mdefine_line|#define ASIZ_task_addr_limit&t;0x00000001
DECL|macro|AOFF_task_exec_domain
mdefine_line|#define AOFF_task_exec_domain&t;0x00000018
DECL|macro|ASIZ_task_exec_domain
mdefine_line|#define ASIZ_task_exec_domain&t;0x00000008
DECL|macro|AOFF_task_need_resched
mdefine_line|#define AOFF_task_need_resched&t;0x00000020
DECL|macro|ASIZ_task_need_resched
mdefine_line|#define ASIZ_task_need_resched&t;0x00000008
DECL|macro|AOFF_task_avg_slice
mdefine_line|#define AOFF_task_avg_slice&t;0x00000028
DECL|macro|ASIZ_task_avg_slice
mdefine_line|#define ASIZ_task_avg_slice&t;0x00000008
DECL|macro|AOFF_task_lock_depth
mdefine_line|#define AOFF_task_lock_depth&t;0x00000030
DECL|macro|ASIZ_task_lock_depth
mdefine_line|#define ASIZ_task_lock_depth&t;0x00000004
DECL|macro|AOFF_task_counter
mdefine_line|#define AOFF_task_counter&t;0x00000038
DECL|macro|ASIZ_task_counter
mdefine_line|#define ASIZ_task_counter&t;0x00000008
DECL|macro|AOFF_task_priority
mdefine_line|#define AOFF_task_priority&t;0x00000040
DECL|macro|ASIZ_task_priority
mdefine_line|#define ASIZ_task_priority&t;0x00000008
DECL|macro|AOFF_task_policy
mdefine_line|#define AOFF_task_policy&t;0x00000048
DECL|macro|ASIZ_task_policy
mdefine_line|#define ASIZ_task_policy&t;0x00000008
DECL|macro|AOFF_task_mm
mdefine_line|#define AOFF_task_mm&t;0x00000050
DECL|macro|ASIZ_task_mm
mdefine_line|#define ASIZ_task_mm&t;0x00000008
DECL|macro|AOFF_task_active_mm
mdefine_line|#define AOFF_task_active_mm&t;0x00000058
DECL|macro|ASIZ_task_active_mm
mdefine_line|#define ASIZ_task_active_mm&t;0x00000008
DECL|macro|AOFF_task_has_cpu
mdefine_line|#define AOFF_task_has_cpu&t;0x00000060
DECL|macro|ASIZ_task_has_cpu
mdefine_line|#define ASIZ_task_has_cpu&t;0x00000004
DECL|macro|AOFF_task_processor
mdefine_line|#define AOFF_task_processor&t;0x00000064
DECL|macro|ASIZ_task_processor
mdefine_line|#define ASIZ_task_processor&t;0x00000004
DECL|macro|AOFF_task_run_list
mdefine_line|#define AOFF_task_run_list&t;0x00000068
DECL|macro|ASIZ_task_run_list
mdefine_line|#define ASIZ_task_run_list&t;0x00000010
DECL|macro|AOFF_task_next_task
mdefine_line|#define AOFF_task_next_task&t;0x00000078
DECL|macro|ASIZ_task_next_task
mdefine_line|#define ASIZ_task_next_task&t;0x00000008
DECL|macro|AOFF_task_prev_task
mdefine_line|#define AOFF_task_prev_task&t;0x00000080
DECL|macro|ASIZ_task_prev_task
mdefine_line|#define ASIZ_task_prev_task&t;0x00000008
DECL|macro|AOFF_task_last_processor
mdefine_line|#define AOFF_task_last_processor&t;0x00000088
DECL|macro|ASIZ_task_last_processor
mdefine_line|#define ASIZ_task_last_processor&t;0x00000004
DECL|macro|AOFF_task_binfmt
mdefine_line|#define AOFF_task_binfmt&t;0x00000090
DECL|macro|ASIZ_task_binfmt
mdefine_line|#define ASIZ_task_binfmt&t;0x00000008
DECL|macro|AOFF_task_exit_code
mdefine_line|#define AOFF_task_exit_code&t;0x00000098
DECL|macro|ASIZ_task_exit_code
mdefine_line|#define ASIZ_task_exit_code&t;0x00000004
DECL|macro|AOFF_task_exit_signal
mdefine_line|#define AOFF_task_exit_signal&t;0x0000009c
DECL|macro|ASIZ_task_exit_signal
mdefine_line|#define ASIZ_task_exit_signal&t;0x00000004
DECL|macro|AOFF_task_pdeath_signal
mdefine_line|#define AOFF_task_pdeath_signal&t;0x000000a0
DECL|macro|ASIZ_task_pdeath_signal
mdefine_line|#define ASIZ_task_pdeath_signal&t;0x00000004
DECL|macro|AOFF_task_personality
mdefine_line|#define AOFF_task_personality&t;0x000000a8
DECL|macro|ASIZ_task_personality
mdefine_line|#define ASIZ_task_personality&t;0x00000008
DECL|macro|AOFF_task_pid
mdefine_line|#define AOFF_task_pid&t;0x000000b4
DECL|macro|ASIZ_task_pid
mdefine_line|#define ASIZ_task_pid&t;0x00000004
DECL|macro|AOFF_task_pgrp
mdefine_line|#define AOFF_task_pgrp&t;0x000000b8
DECL|macro|ASIZ_task_pgrp
mdefine_line|#define ASIZ_task_pgrp&t;0x00000004
DECL|macro|AOFF_task_tty_old_pgrp
mdefine_line|#define AOFF_task_tty_old_pgrp&t;0x000000bc
DECL|macro|ASIZ_task_tty_old_pgrp
mdefine_line|#define ASIZ_task_tty_old_pgrp&t;0x00000004
DECL|macro|AOFF_task_session
mdefine_line|#define AOFF_task_session&t;0x000000c0
DECL|macro|ASIZ_task_session
mdefine_line|#define ASIZ_task_session&t;0x00000004
DECL|macro|AOFF_task_leader
mdefine_line|#define AOFF_task_leader&t;0x000000c4
DECL|macro|ASIZ_task_leader
mdefine_line|#define ASIZ_task_leader&t;0x00000004
DECL|macro|AOFF_task_p_opptr
mdefine_line|#define AOFF_task_p_opptr&t;0x000000c8
DECL|macro|ASIZ_task_p_opptr
mdefine_line|#define ASIZ_task_p_opptr&t;0x00000008
DECL|macro|AOFF_task_p_pptr
mdefine_line|#define AOFF_task_p_pptr&t;0x000000d0
DECL|macro|ASIZ_task_p_pptr
mdefine_line|#define ASIZ_task_p_pptr&t;0x00000008
DECL|macro|AOFF_task_p_cptr
mdefine_line|#define AOFF_task_p_cptr&t;0x000000d8
DECL|macro|ASIZ_task_p_cptr
mdefine_line|#define ASIZ_task_p_cptr&t;0x00000008
DECL|macro|AOFF_task_p_ysptr
mdefine_line|#define AOFF_task_p_ysptr&t;0x000000e0
DECL|macro|ASIZ_task_p_ysptr
mdefine_line|#define ASIZ_task_p_ysptr&t;0x00000008
DECL|macro|AOFF_task_p_osptr
mdefine_line|#define AOFF_task_p_osptr&t;0x000000e8
DECL|macro|ASIZ_task_p_osptr
mdefine_line|#define ASIZ_task_p_osptr&t;0x00000008
DECL|macro|AOFF_task_pidhash_next
mdefine_line|#define AOFF_task_pidhash_next&t;0x000000f0
DECL|macro|ASIZ_task_pidhash_next
mdefine_line|#define ASIZ_task_pidhash_next&t;0x00000008
DECL|macro|AOFF_task_pidhash_pprev
mdefine_line|#define AOFF_task_pidhash_pprev&t;0x000000f8
DECL|macro|ASIZ_task_pidhash_pprev
mdefine_line|#define ASIZ_task_pidhash_pprev&t;0x00000008
DECL|macro|AOFF_task_wait_chldexit
mdefine_line|#define AOFF_task_wait_chldexit&t;0x00000100
DECL|macro|ASIZ_task_wait_chldexit
mdefine_line|#define ASIZ_task_wait_chldexit&t;0x00000030
DECL|macro|AOFF_task_vfork_sem
mdefine_line|#define AOFF_task_vfork_sem&t;0x00000130
DECL|macro|ASIZ_task_vfork_sem
mdefine_line|#define ASIZ_task_vfork_sem&t;0x00000008
DECL|macro|AOFF_task_rt_priority
mdefine_line|#define AOFF_task_rt_priority&t;0x00000138
DECL|macro|ASIZ_task_rt_priority
mdefine_line|#define ASIZ_task_rt_priority&t;0x00000008
DECL|macro|AOFF_task_it_real_value
mdefine_line|#define AOFF_task_it_real_value&t;0x00000140
DECL|macro|ASIZ_task_it_real_value
mdefine_line|#define ASIZ_task_it_real_value&t;0x00000008
DECL|macro|AOFF_task_it_prof_value
mdefine_line|#define AOFF_task_it_prof_value&t;0x00000148
DECL|macro|ASIZ_task_it_prof_value
mdefine_line|#define ASIZ_task_it_prof_value&t;0x00000008
DECL|macro|AOFF_task_it_virt_value
mdefine_line|#define AOFF_task_it_virt_value&t;0x00000150
DECL|macro|ASIZ_task_it_virt_value
mdefine_line|#define ASIZ_task_it_virt_value&t;0x00000008
DECL|macro|AOFF_task_it_real_incr
mdefine_line|#define AOFF_task_it_real_incr&t;0x00000158
DECL|macro|ASIZ_task_it_real_incr
mdefine_line|#define ASIZ_task_it_real_incr&t;0x00000008
DECL|macro|AOFF_task_it_prof_incr
mdefine_line|#define AOFF_task_it_prof_incr&t;0x00000160
DECL|macro|ASIZ_task_it_prof_incr
mdefine_line|#define ASIZ_task_it_prof_incr&t;0x00000008
DECL|macro|AOFF_task_it_virt_incr
mdefine_line|#define AOFF_task_it_virt_incr&t;0x00000168
DECL|macro|ASIZ_task_it_virt_incr
mdefine_line|#define ASIZ_task_it_virt_incr&t;0x00000008
DECL|macro|AOFF_task_real_timer
mdefine_line|#define AOFF_task_real_timer&t;0x00000170
DECL|macro|ASIZ_task_real_timer
mdefine_line|#define ASIZ_task_real_timer&t;0x00000030
DECL|macro|AOFF_task_times
mdefine_line|#define AOFF_task_times&t;0x000001a0
DECL|macro|ASIZ_task_times
mdefine_line|#define ASIZ_task_times&t;0x00000020
DECL|macro|AOFF_task_start_time
mdefine_line|#define AOFF_task_start_time&t;0x000001c0
DECL|macro|ASIZ_task_start_time
mdefine_line|#define ASIZ_task_start_time&t;0x00000008
DECL|macro|AOFF_task_per_cpu_utime
mdefine_line|#define AOFF_task_per_cpu_utime&t;0x000001c8
DECL|macro|ASIZ_task_per_cpu_utime
mdefine_line|#define ASIZ_task_per_cpu_utime&t;0x00000100
DECL|macro|AOFF_task_min_flt
mdefine_line|#define AOFF_task_min_flt&t;0x000003c8
DECL|macro|ASIZ_task_min_flt
mdefine_line|#define ASIZ_task_min_flt&t;0x00000008
DECL|macro|AOFF_task_maj_flt
mdefine_line|#define AOFF_task_maj_flt&t;0x000003d0
DECL|macro|ASIZ_task_maj_flt
mdefine_line|#define ASIZ_task_maj_flt&t;0x00000008
DECL|macro|AOFF_task_nswap
mdefine_line|#define AOFF_task_nswap&t;0x000003d8
DECL|macro|ASIZ_task_nswap
mdefine_line|#define ASIZ_task_nswap&t;0x00000008
DECL|macro|AOFF_task_cmin_flt
mdefine_line|#define AOFF_task_cmin_flt&t;0x000003e0
DECL|macro|ASIZ_task_cmin_flt
mdefine_line|#define ASIZ_task_cmin_flt&t;0x00000008
DECL|macro|AOFF_task_cmaj_flt
mdefine_line|#define AOFF_task_cmaj_flt&t;0x000003e8
DECL|macro|ASIZ_task_cmaj_flt
mdefine_line|#define ASIZ_task_cmaj_flt&t;0x00000008
DECL|macro|AOFF_task_cnswap
mdefine_line|#define AOFF_task_cnswap&t;0x000003f0
DECL|macro|ASIZ_task_cnswap
mdefine_line|#define ASIZ_task_cnswap&t;0x00000008
DECL|macro|AOFF_task_uid
mdefine_line|#define AOFF_task_uid&t;0x000003fc
DECL|macro|ASIZ_task_uid
mdefine_line|#define ASIZ_task_uid&t;0x00000004
DECL|macro|AOFF_task_euid
mdefine_line|#define AOFF_task_euid&t;0x00000400
DECL|macro|ASIZ_task_euid
mdefine_line|#define ASIZ_task_euid&t;0x00000004
DECL|macro|AOFF_task_suid
mdefine_line|#define AOFF_task_suid&t;0x00000404
DECL|macro|ASIZ_task_suid
mdefine_line|#define ASIZ_task_suid&t;0x00000004
DECL|macro|AOFF_task_fsuid
mdefine_line|#define AOFF_task_fsuid&t;0x00000408
DECL|macro|ASIZ_task_fsuid
mdefine_line|#define ASIZ_task_fsuid&t;0x00000004
DECL|macro|AOFF_task_gid
mdefine_line|#define AOFF_task_gid&t;0x0000040c
DECL|macro|ASIZ_task_gid
mdefine_line|#define ASIZ_task_gid&t;0x00000004
DECL|macro|AOFF_task_egid
mdefine_line|#define AOFF_task_egid&t;0x00000410
DECL|macro|ASIZ_task_egid
mdefine_line|#define ASIZ_task_egid&t;0x00000004
DECL|macro|AOFF_task_sgid
mdefine_line|#define AOFF_task_sgid&t;0x00000414
DECL|macro|ASIZ_task_sgid
mdefine_line|#define ASIZ_task_sgid&t;0x00000004
DECL|macro|AOFF_task_fsgid
mdefine_line|#define AOFF_task_fsgid&t;0x00000418
DECL|macro|ASIZ_task_fsgid
mdefine_line|#define ASIZ_task_fsgid&t;0x00000004
DECL|macro|AOFF_task_ngroups
mdefine_line|#define AOFF_task_ngroups&t;0x0000041c
DECL|macro|ASIZ_task_ngroups
mdefine_line|#define ASIZ_task_ngroups&t;0x00000004
DECL|macro|AOFF_task_groups
mdefine_line|#define AOFF_task_groups&t;0x00000420
DECL|macro|ASIZ_task_groups
mdefine_line|#define ASIZ_task_groups&t;0x00000080
DECL|macro|AOFF_task_cap_effective
mdefine_line|#define AOFF_task_cap_effective&t;0x000004a0
DECL|macro|ASIZ_task_cap_effective
mdefine_line|#define ASIZ_task_cap_effective&t;0x00000004
DECL|macro|AOFF_task_cap_inheritable
mdefine_line|#define AOFF_task_cap_inheritable&t;0x000004a4
DECL|macro|ASIZ_task_cap_inheritable
mdefine_line|#define ASIZ_task_cap_inheritable&t;0x00000004
DECL|macro|AOFF_task_cap_permitted
mdefine_line|#define AOFF_task_cap_permitted&t;0x000004a8
DECL|macro|ASIZ_task_cap_permitted
mdefine_line|#define ASIZ_task_cap_permitted&t;0x00000004
DECL|macro|AOFF_task_user
mdefine_line|#define AOFF_task_user&t;0x000004b0
DECL|macro|ASIZ_task_user
mdefine_line|#define ASIZ_task_user&t;0x00000008
DECL|macro|AOFF_task_rlim
mdefine_line|#define AOFF_task_rlim&t;0x000004b8
DECL|macro|ASIZ_task_rlim
mdefine_line|#define ASIZ_task_rlim&t;0x000000a0
DECL|macro|AOFF_task_used_math
mdefine_line|#define AOFF_task_used_math&t;0x00000558
DECL|macro|ASIZ_task_used_math
mdefine_line|#define ASIZ_task_used_math&t;0x00000002
DECL|macro|AOFF_task_comm
mdefine_line|#define AOFF_task_comm&t;0x0000055a
DECL|macro|ASIZ_task_comm
mdefine_line|#define ASIZ_task_comm&t;0x00000010
DECL|macro|AOFF_task_link_count
mdefine_line|#define AOFF_task_link_count&t;0x0000056c
DECL|macro|ASIZ_task_link_count
mdefine_line|#define ASIZ_task_link_count&t;0x00000004
DECL|macro|AOFF_task_tty
mdefine_line|#define AOFF_task_tty&t;0x00000570
DECL|macro|ASIZ_task_tty
mdefine_line|#define ASIZ_task_tty&t;0x00000008
DECL|macro|AOFF_task_semundo
mdefine_line|#define AOFF_task_semundo&t;0x00000578
DECL|macro|ASIZ_task_semundo
mdefine_line|#define ASIZ_task_semundo&t;0x00000008
DECL|macro|AOFF_task_semsleeping
mdefine_line|#define AOFF_task_semsleeping&t;0x00000580
DECL|macro|ASIZ_task_semsleeping
mdefine_line|#define ASIZ_task_semsleeping&t;0x00000008
DECL|macro|AOFF_task_thread
mdefine_line|#define AOFF_task_thread&t;0x00000590
DECL|macro|ASIZ_task_thread
mdefine_line|#define ASIZ_task_thread&t;0x00000450
DECL|macro|AOFF_task_fs
mdefine_line|#define AOFF_task_fs&t;0x000009e0
DECL|macro|ASIZ_task_fs
mdefine_line|#define ASIZ_task_fs&t;0x00000008
DECL|macro|AOFF_task_files
mdefine_line|#define AOFF_task_files&t;0x000009e8
DECL|macro|ASIZ_task_files
mdefine_line|#define ASIZ_task_files&t;0x00000008
DECL|macro|AOFF_task_sigmask_lock
mdefine_line|#define AOFF_task_sigmask_lock&t;0x000009f0
DECL|macro|ASIZ_task_sigmask_lock
mdefine_line|#define ASIZ_task_sigmask_lock&t;0x0000000c
DECL|macro|AOFF_task_sig
mdefine_line|#define AOFF_task_sig&t;0x00000a00
DECL|macro|ASIZ_task_sig
mdefine_line|#define ASIZ_task_sig&t;0x00000008
DECL|macro|AOFF_task_signal
mdefine_line|#define AOFF_task_signal&t;0x00000a08
DECL|macro|ASIZ_task_signal
mdefine_line|#define ASIZ_task_signal&t;0x00000008
DECL|macro|AOFF_task_blocked
mdefine_line|#define AOFF_task_blocked&t;0x00000a10
DECL|macro|ASIZ_task_blocked
mdefine_line|#define ASIZ_task_blocked&t;0x00000008
DECL|macro|AOFF_task_sigqueue
mdefine_line|#define AOFF_task_sigqueue&t;0x00000a18
DECL|macro|ASIZ_task_sigqueue
mdefine_line|#define ASIZ_task_sigqueue&t;0x00000008
DECL|macro|AOFF_task_sigqueue_tail
mdefine_line|#define AOFF_task_sigqueue_tail&t;0x00000a20
DECL|macro|ASIZ_task_sigqueue_tail
mdefine_line|#define ASIZ_task_sigqueue_tail&t;0x00000008
DECL|macro|AOFF_task_sas_ss_sp
mdefine_line|#define AOFF_task_sas_ss_sp&t;0x00000a28
DECL|macro|ASIZ_task_sas_ss_sp
mdefine_line|#define ASIZ_task_sas_ss_sp&t;0x00000008
DECL|macro|AOFF_task_sas_ss_size
mdefine_line|#define AOFF_task_sas_ss_size&t;0x00000a30
DECL|macro|ASIZ_task_sas_ss_size
mdefine_line|#define ASIZ_task_sas_ss_size&t;0x00000008
DECL|macro|AOFF_task_parent_exec_id
mdefine_line|#define AOFF_task_parent_exec_id&t;0x00000a38
DECL|macro|ASIZ_task_parent_exec_id
mdefine_line|#define ASIZ_task_parent_exec_id&t;0x00000004
DECL|macro|AOFF_task_self_exec_id
mdefine_line|#define AOFF_task_self_exec_id&t;0x00000a3c
DECL|macro|ASIZ_task_self_exec_id
mdefine_line|#define ASIZ_task_self_exec_id&t;0x00000004
DECL|macro|AOFF_task_exit_sem
mdefine_line|#define AOFF_task_exit_sem&t;0x00000a40
DECL|macro|ASIZ_task_exit_sem
mdefine_line|#define ASIZ_task_exit_sem&t;0x00000040
DECL|macro|ASIZ_task
mdefine_line|#define ASIZ_task&t;0x00000a80
DECL|macro|AOFF_mm_mmap
mdefine_line|#define AOFF_mm_mmap&t;0x00000000
DECL|macro|ASIZ_mm_mmap
mdefine_line|#define ASIZ_mm_mmap&t;0x00000008
DECL|macro|AOFF_mm_mmap_avl
mdefine_line|#define AOFF_mm_mmap_avl&t;0x00000008
DECL|macro|ASIZ_mm_mmap_avl
mdefine_line|#define ASIZ_mm_mmap_avl&t;0x00000008
DECL|macro|AOFF_mm_mmap_cache
mdefine_line|#define AOFF_mm_mmap_cache&t;0x00000010
DECL|macro|ASIZ_mm_mmap_cache
mdefine_line|#define ASIZ_mm_mmap_cache&t;0x00000008
DECL|macro|AOFF_mm_pgd
mdefine_line|#define AOFF_mm_pgd&t;0x00000018
DECL|macro|ASIZ_mm_pgd
mdefine_line|#define ASIZ_mm_pgd&t;0x00000008
DECL|macro|AOFF_mm_mm_users
mdefine_line|#define AOFF_mm_mm_users&t;0x00000020
DECL|macro|ASIZ_mm_mm_users
mdefine_line|#define ASIZ_mm_mm_users&t;0x00000004
DECL|macro|AOFF_mm_mm_count
mdefine_line|#define AOFF_mm_mm_count&t;0x00000024
DECL|macro|ASIZ_mm_mm_count
mdefine_line|#define ASIZ_mm_mm_count&t;0x00000004
DECL|macro|AOFF_mm_map_count
mdefine_line|#define AOFF_mm_map_count&t;0x00000028
DECL|macro|ASIZ_mm_map_count
mdefine_line|#define ASIZ_mm_map_count&t;0x00000004
DECL|macro|AOFF_mm_mmap_sem
mdefine_line|#define AOFF_mm_mmap_sem&t;0x00000030
DECL|macro|ASIZ_mm_mmap_sem
mdefine_line|#define ASIZ_mm_mmap_sem&t;0x00000040
DECL|macro|AOFF_mm_page_table_lock
mdefine_line|#define AOFF_mm_page_table_lock&t;0x00000070
DECL|macro|ASIZ_mm_page_table_lock
mdefine_line|#define ASIZ_mm_page_table_lock&t;0x0000000c
DECL|macro|AOFF_mm_context
mdefine_line|#define AOFF_mm_context&t;0x00000080
DECL|macro|ASIZ_mm_context
mdefine_line|#define ASIZ_mm_context&t;0x00000008
DECL|macro|AOFF_mm_start_code
mdefine_line|#define AOFF_mm_start_code&t;0x00000088
DECL|macro|ASIZ_mm_start_code
mdefine_line|#define ASIZ_mm_start_code&t;0x00000008
DECL|macro|AOFF_mm_end_code
mdefine_line|#define AOFF_mm_end_code&t;0x00000090
DECL|macro|ASIZ_mm_end_code
mdefine_line|#define ASIZ_mm_end_code&t;0x00000008
DECL|macro|AOFF_mm_start_data
mdefine_line|#define AOFF_mm_start_data&t;0x00000098
DECL|macro|ASIZ_mm_start_data
mdefine_line|#define ASIZ_mm_start_data&t;0x00000008
DECL|macro|AOFF_mm_end_data
mdefine_line|#define AOFF_mm_end_data&t;0x000000a0
DECL|macro|ASIZ_mm_end_data
mdefine_line|#define ASIZ_mm_end_data&t;0x00000008
DECL|macro|AOFF_mm_start_brk
mdefine_line|#define AOFF_mm_start_brk&t;0x000000a8
DECL|macro|ASIZ_mm_start_brk
mdefine_line|#define ASIZ_mm_start_brk&t;0x00000008
DECL|macro|AOFF_mm_brk
mdefine_line|#define AOFF_mm_brk&t;0x000000b0
DECL|macro|ASIZ_mm_brk
mdefine_line|#define ASIZ_mm_brk&t;0x00000008
DECL|macro|AOFF_mm_start_stack
mdefine_line|#define AOFF_mm_start_stack&t;0x000000b8
DECL|macro|ASIZ_mm_start_stack
mdefine_line|#define ASIZ_mm_start_stack&t;0x00000008
DECL|macro|AOFF_mm_arg_start
mdefine_line|#define AOFF_mm_arg_start&t;0x000000c0
DECL|macro|ASIZ_mm_arg_start
mdefine_line|#define ASIZ_mm_arg_start&t;0x00000008
DECL|macro|AOFF_mm_arg_end
mdefine_line|#define AOFF_mm_arg_end&t;0x000000c8
DECL|macro|ASIZ_mm_arg_end
mdefine_line|#define ASIZ_mm_arg_end&t;0x00000008
DECL|macro|AOFF_mm_env_start
mdefine_line|#define AOFF_mm_env_start&t;0x000000d0
DECL|macro|ASIZ_mm_env_start
mdefine_line|#define ASIZ_mm_env_start&t;0x00000008
DECL|macro|AOFF_mm_env_end
mdefine_line|#define AOFF_mm_env_end&t;0x000000d8
DECL|macro|ASIZ_mm_env_end
mdefine_line|#define ASIZ_mm_env_end&t;0x00000008
DECL|macro|AOFF_mm_rss
mdefine_line|#define AOFF_mm_rss&t;0x000000e0
DECL|macro|ASIZ_mm_rss
mdefine_line|#define ASIZ_mm_rss&t;0x00000008
DECL|macro|AOFF_mm_total_vm
mdefine_line|#define AOFF_mm_total_vm&t;0x000000e8
DECL|macro|ASIZ_mm_total_vm
mdefine_line|#define ASIZ_mm_total_vm&t;0x00000008
DECL|macro|AOFF_mm_locked_vm
mdefine_line|#define AOFF_mm_locked_vm&t;0x000000f0
DECL|macro|ASIZ_mm_locked_vm
mdefine_line|#define ASIZ_mm_locked_vm&t;0x00000008
DECL|macro|AOFF_mm_def_flags
mdefine_line|#define AOFF_mm_def_flags&t;0x000000f8
DECL|macro|ASIZ_mm_def_flags
mdefine_line|#define ASIZ_mm_def_flags&t;0x00000008
DECL|macro|AOFF_mm_cpu_vm_mask
mdefine_line|#define AOFF_mm_cpu_vm_mask&t;0x00000100
DECL|macro|ASIZ_mm_cpu_vm_mask
mdefine_line|#define ASIZ_mm_cpu_vm_mask&t;0x00000008
DECL|macro|AOFF_mm_swap_cnt
mdefine_line|#define AOFF_mm_swap_cnt&t;0x00000108
DECL|macro|ASIZ_mm_swap_cnt
mdefine_line|#define ASIZ_mm_swap_cnt&t;0x00000008
DECL|macro|AOFF_mm_swap_address
mdefine_line|#define AOFF_mm_swap_address&t;0x00000110
DECL|macro|ASIZ_mm_swap_address
mdefine_line|#define ASIZ_mm_swap_address&t;0x00000008
DECL|macro|AOFF_mm_segments
mdefine_line|#define AOFF_mm_segments&t;0x00000118
DECL|macro|ASIZ_mm_segments
mdefine_line|#define ASIZ_mm_segments&t;0x00000008
DECL|macro|ASIZ_mm
mdefine_line|#define ASIZ_mm&t;0x00000120
DECL|macro|AOFF_thread_ksp
mdefine_line|#define AOFF_thread_ksp&t;0x00000000
DECL|macro|ASIZ_thread_ksp
mdefine_line|#define ASIZ_thread_ksp&t;0x00000008
DECL|macro|AOFF_thread_wstate
mdefine_line|#define AOFF_thread_wstate&t;0x00000008
DECL|macro|ASIZ_thread_wstate
mdefine_line|#define ASIZ_thread_wstate&t;0x00000001
DECL|macro|AOFF_thread_cwp
mdefine_line|#define AOFF_thread_cwp&t;0x00000009
DECL|macro|ASIZ_thread_cwp
mdefine_line|#define ASIZ_thread_cwp&t;0x00000001
DECL|macro|AOFF_thread_flags
mdefine_line|#define AOFF_thread_flags&t;0x0000000a
DECL|macro|ASIZ_thread_flags
mdefine_line|#define ASIZ_thread_flags&t;0x00000001
DECL|macro|AOFF_thread_current_ds
mdefine_line|#define AOFF_thread_current_ds&t;0x0000000b
DECL|macro|ASIZ_thread_current_ds
mdefine_line|#define ASIZ_thread_current_ds&t;0x00000001
DECL|macro|AOFF_thread_w_saved
mdefine_line|#define AOFF_thread_w_saved&t;0x0000000c
DECL|macro|ASIZ_thread_w_saved
mdefine_line|#define ASIZ_thread_w_saved&t;0x00000001
DECL|macro|AOFF_thread_fpdepth
mdefine_line|#define AOFF_thread_fpdepth&t;0x0000000d
DECL|macro|ASIZ_thread_fpdepth
mdefine_line|#define ASIZ_thread_fpdepth&t;0x00000001
DECL|macro|AOFF_thread_fault_code
mdefine_line|#define AOFF_thread_fault_code&t;0x0000000e
DECL|macro|ASIZ_thread_fault_code
mdefine_line|#define ASIZ_thread_fault_code&t;0x00000001
DECL|macro|AOFF_thread_use_blkcommit
mdefine_line|#define AOFF_thread_use_blkcommit&t;0x0000000f
DECL|macro|ASIZ_thread_use_blkcommit
mdefine_line|#define ASIZ_thread_use_blkcommit&t;0x00000001
DECL|macro|AOFF_thread_fault_address
mdefine_line|#define AOFF_thread_fault_address&t;0x00000010
DECL|macro|ASIZ_thread_fault_address
mdefine_line|#define ASIZ_thread_fault_address&t;0x00000008
DECL|macro|AOFF_thread_fpsaved
mdefine_line|#define AOFF_thread_fpsaved&t;0x00000018
DECL|macro|ASIZ_thread_fpsaved
mdefine_line|#define ASIZ_thread_fpsaved&t;0x00000007
DECL|macro|AOFF_thread___pad2
mdefine_line|#define AOFF_thread___pad2&t;0x0000001f
DECL|macro|ASIZ_thread___pad2
mdefine_line|#define ASIZ_thread___pad2&t;0x00000001
DECL|macro|AOFF_thread_kregs
mdefine_line|#define AOFF_thread_kregs&t;0x00000020
DECL|macro|ASIZ_thread_kregs
mdefine_line|#define ASIZ_thread_kregs&t;0x00000008
DECL|macro|AOFF_thread_utraps
mdefine_line|#define AOFF_thread_utraps&t;0x00000028
DECL|macro|ASIZ_thread_utraps
mdefine_line|#define ASIZ_thread_utraps&t;0x00000008
DECL|macro|AOFF_thread_gsr
mdefine_line|#define AOFF_thread_gsr&t;0x00000030
DECL|macro|ASIZ_thread_gsr
mdefine_line|#define ASIZ_thread_gsr&t;0x00000007
DECL|macro|AOFF_thread___pad3
mdefine_line|#define AOFF_thread___pad3&t;0x00000037
DECL|macro|ASIZ_thread___pad3
mdefine_line|#define ASIZ_thread___pad3&t;0x00000001
DECL|macro|AOFF_thread_xfsr
mdefine_line|#define AOFF_thread_xfsr&t;0x00000038
DECL|macro|ASIZ_thread_xfsr
mdefine_line|#define ASIZ_thread_xfsr&t;0x00000038
DECL|macro|AOFF_thread_reg_window
mdefine_line|#define AOFF_thread_reg_window&t;0x00000070
DECL|macro|ASIZ_thread_reg_window
mdefine_line|#define ASIZ_thread_reg_window&t;0x00000380
DECL|macro|AOFF_thread_rwbuf_stkptrs
mdefine_line|#define AOFF_thread_rwbuf_stkptrs&t;0x000003f0
DECL|macro|ASIZ_thread_rwbuf_stkptrs
mdefine_line|#define ASIZ_thread_rwbuf_stkptrs&t;0x00000038
DECL|macro|AOFF_thread_user_cntd0
mdefine_line|#define AOFF_thread_user_cntd0&t;0x00000428
DECL|macro|ASIZ_thread_user_cntd0
mdefine_line|#define ASIZ_thread_user_cntd0&t;0x00000008
DECL|macro|AOFF_thread_user_cntd1
mdefine_line|#define AOFF_thread_user_cntd1&t;0x00000430
DECL|macro|ASIZ_thread_user_cntd1
mdefine_line|#define ASIZ_thread_user_cntd1&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd0
mdefine_line|#define AOFF_thread_kernel_cntd0&t;0x00000438
DECL|macro|ASIZ_thread_kernel_cntd0
mdefine_line|#define ASIZ_thread_kernel_cntd0&t;0x00000008
DECL|macro|AOFF_thread_kernel_cntd1
mdefine_line|#define AOFF_thread_kernel_cntd1&t;0x00000440
DECL|macro|ASIZ_thread_kernel_cntd1
mdefine_line|#define ASIZ_thread_kernel_cntd1&t;0x00000008
DECL|macro|AOFF_thread_pcr_reg
mdefine_line|#define AOFF_thread_pcr_reg&t;0x00000448
DECL|macro|ASIZ_thread_pcr_reg
mdefine_line|#define ASIZ_thread_pcr_reg&t;0x00000008
DECL|macro|ASIZ_thread
mdefine_line|#define ASIZ_thread&t;0x00000450
macro_line|#endif /* SPIN_LOCK_DEBUG */
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_OFFSETS_H__ */
eof
