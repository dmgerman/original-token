macro_line|#ifndef __LINUX_SMP_H
DECL|macro|__LINUX_SMP_H
mdefine_line|#define __LINUX_SMP_H
multiline_comment|/*&n; *&t;Generic SMP support&n; *&t;&t;Alan Cox. &lt;alan@cymru.net&gt;&n; */
macro_line|#ifdef __SMP__
macro_line|#include &lt;asm/smp.h&gt;
r_extern
r_void
id|smp_message_pass
c_func
(paren
r_int
id|target
comma
r_int
id|msg
comma
r_int
r_int
id|data
comma
r_int
id|wait
)paren
suffix:semicolon
r_extern
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Boot processor call to load the other CPU&squot;s */
r_extern
r_void
id|smp_callin
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Processor call in. Must hold processors until .. */
r_extern
r_void
id|smp_commence
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Multiprocessors may now schedule */
r_extern
r_int
id|smp_num_cpus
suffix:semicolon
r_extern
r_int
id|smp_threads_ready
suffix:semicolon
multiline_comment|/* True once the per process idle is forked */
r_extern
r_volatile
r_int
r_int
id|smp_spins
suffix:semicolon
multiline_comment|/* Count of spins */
r_extern
r_volatile
r_int
r_int
id|smp_msg_data
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_src_cpu
suffix:semicolon
r_extern
r_volatile
r_int
id|smp_msg_id
suffix:semicolon
DECL|macro|MSG_ALL_BUT_SELF
mdefine_line|#define MSG_ALL_BUT_SELF&t;0x8000&t;&t;/* Assume &lt;32768 CPU&squot;s */
DECL|macro|MSG_ALL
mdefine_line|#define MSG_ALL&t;&t;&t;0x8001
DECL|macro|MSG_INVALIDATE_TLB
mdefine_line|#define MSG_INVALIDATE_TLB&t;0x0001&t;&t;/* Remote processor TLB invalidate */
DECL|macro|MSG_STOP_CPU
mdefine_line|#define MSG_STOP_CPU&t;&t;0x0002&t;&t;/* Sent to shut down slave CPU&squot;s when rebooting */
DECL|macro|MSG_RESCHEDULE
mdefine_line|#define MSG_RESCHEDULE&t;&t;0x0003&t;&t;/* Reschedule request from master CPU */
macro_line|#else
multiline_comment|/*&n; *&t;These macros fold the SMP functionality into a single CPU system&n; */
DECL|macro|smp_num_cpus
mdefine_line|#define smp_num_cpus&t;&t;&t;1
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;&t;0
DECL|macro|smp_message_pass
mdefine_line|#define smp_message_pass(t,m,d,w)&t;
DECL|macro|smp_threads_ready
mdefine_line|#define smp_threads_ready&t;&t;1
macro_line|#endif
macro_line|#endif
eof
