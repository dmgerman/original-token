multiline_comment|/* interrupt.h */
macro_line|#ifndef _LINUX_INTERRUPT_H
DECL|macro|_LINUX_INTERRUPT_H
mdefine_line|#define _LINUX_INTERRUPT_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|struct|irqaction
r_struct
id|irqaction
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
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
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|next
r_struct
id|irqaction
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Who gets which entry in bh_base.  Things which will occur most often&n;   should come first */
r_enum
(brace
DECL|enumerator|TIMER_BH
id|TIMER_BH
op_assign
l_int|0
comma
DECL|enumerator|TQUEUE_BH
id|TQUEUE_BH
comma
DECL|enumerator|DIGI_BH
id|DIGI_BH
comma
DECL|enumerator|SERIAL_BH
id|SERIAL_BH
comma
DECL|enumerator|RISCOM8_BH
id|RISCOM8_BH
comma
DECL|enumerator|SPECIALIX_BH
id|SPECIALIX_BH
comma
DECL|enumerator|AURORA_BH
id|AURORA_BH
comma
DECL|enumerator|ESP_BH
id|ESP_BH
comma
DECL|enumerator|SCSI_BH
id|SCSI_BH
comma
DECL|enumerator|IMMEDIATE_BH
id|IMMEDIATE_BH
comma
DECL|enumerator|CYCLADES_BH
id|CYCLADES_BH
comma
DECL|enumerator|CM206_BH
id|CM206_BH
comma
DECL|enumerator|JS_BH
id|JS_BH
comma
DECL|enumerator|MACSERIAL_BH
id|MACSERIAL_BH
comma
DECL|enumerator|ISICOM_BH
id|ISICOM_BH
)brace
suffix:semicolon
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
multiline_comment|/* PLEASE, avoid to allocate new softirqs, if you need not _really_ high&n;   frequency threaded job scheduling. For almost all the purposes&n;   tasklets are more than enough. F.e. all serial device BHs et&n;   al. should be converted to tasklets, not to softirqs.&n; */
r_enum
(brace
DECL|enumerator|HI_SOFTIRQ
id|HI_SOFTIRQ
op_assign
l_int|0
comma
DECL|enumerator|NET_TX_SOFTIRQ
id|NET_TX_SOFTIRQ
comma
DECL|enumerator|NET_RX_SOFTIRQ
id|NET_RX_SOFTIRQ
comma
DECL|enumerator|TASKLET_SOFTIRQ
id|TASKLET_SOFTIRQ
)brace
suffix:semicolon
macro_line|#if SMP_CACHE_BYTES &lt;= 32
multiline_comment|/* It is trick to make assembly easier. */
DECL|macro|SOFTIRQ_STATE_PAD
mdefine_line|#define SOFTIRQ_STATE_PAD 32
macro_line|#else
DECL|macro|SOFTIRQ_STATE_PAD
mdefine_line|#define SOFTIRQ_STATE_PAD SMP_CACHE_BYTES
macro_line|#endif
DECL|struct|softirq_state
r_struct
id|softirq_state
(brace
DECL|member|active
id|__u32
id|active
suffix:semicolon
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__aligned__
c_func
(paren
id|SOFTIRQ_STATE_PAD
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|softirq_state
id|softirq_state
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|struct|softirq_action
r_struct
id|softirq_action
(brace
DECL|member|action
r_void
(paren
op_star
id|action
)paren
(paren
r_struct
id|softirq_action
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
id|asmlinkage
r_void
id|do_softirq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|open_softirq
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|action
)paren
(paren
r_struct
id|softirq_action
op_star
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|function|__cpu_raise_softirq
r_extern
id|__inline__
r_void
id|__cpu_raise_softirq
c_func
(paren
r_int
id|cpu
comma
r_int
id|nr
)paren
(brace
id|softirq_state
(braket
id|cpu
)braket
dot
id|active
op_or_assign
(paren
l_int|1
op_lshift
id|nr
)paren
suffix:semicolon
)brace
multiline_comment|/* I do not want to use atomic variables now, so that cli/sti */
DECL|function|raise_softirq
r_extern
id|__inline__
r_void
id|raise_softirq
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_void
id|softirq_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Tasklets --- multithreaded analogue of BHs.&n;&n;   Main feature differing them of generic softirqs: tasklet&n;   is running only on one CPU simultaneously.&n;&n;   Main feature differing them of BHs: different tasklets&n;   may be run simultaneously on different CPUs.&n;&n;   Properties:&n;   * If tasklet_schedule() is called, then tasklet is guaranteed&n;     to be executed on some cpu at least once after this.&n;   * If the tasklet is already scheduled, but its excecution is still not&n;     started, it will be executed only once.&n;   * If this tasklet is already running on another CPU (or schedule is called&n;     from tasklet itself), it is rescheduled for later.&n;   * Tasklet is strictly serialized wrt itself, but not&n;     wrt another tasklets. If client needs some intertask synchronization,&n;     he makes it with spinlocks.&n; */
DECL|struct|tasklet_struct
r_struct
id|tasklet_struct
(brace
DECL|member|next
r_struct
id|tasklet_struct
op_star
id|next
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|func
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DECLARE_TASKLET
mdefine_line|#define DECLARE_TASKLET(name, func, data) &bslash;&n;struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(0), func, data }
DECL|macro|DECLARE_TASKLET_DISABLED
mdefine_line|#define DECLARE_TASKLET_DISABLED(name, func, data) &bslash;&n;struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(1), func, data }
r_enum
(brace
DECL|enumerator|TASKLET_STATE_SCHED
id|TASKLET_STATE_SCHED
comma
multiline_comment|/* Tasklet is scheduled for execution */
DECL|enumerator|TASKLET_STATE_RUN
id|TASKLET_STATE_RUN
multiline_comment|/* Tasklet is running (SMP only) */
)brace
suffix:semicolon
DECL|struct|tasklet_head
r_struct
id|tasklet_head
(brace
DECL|member|list
r_struct
id|tasklet_struct
op_star
id|list
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__aligned__
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|tasklet_head
id|tasklet_vec
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_struct
id|tasklet_head
id|tasklet_hi_vec
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef __SMP__
DECL|macro|tasklet_trylock
mdefine_line|#define tasklet_trylock(t) (!test_and_set_bit(TASKLET_STATE_RUN, &amp;(t)-&gt;state))
DECL|macro|tasklet_unlock_wait
mdefine_line|#define tasklet_unlock_wait(t) while (test_bit(TASKLET_STATE_RUN, &amp;(t)-&gt;state)) { /* NOTHING */ }
DECL|macro|tasklet_unlock
mdefine_line|#define tasklet_unlock(t) clear_bit(TASKLET_STATE_RUN, &amp;(t)-&gt;state)
macro_line|#else
DECL|macro|tasklet_trylock
mdefine_line|#define tasklet_trylock(t) 1
DECL|macro|tasklet_unlock_wait
mdefine_line|#define tasklet_unlock_wait(t) do { } while (0)
DECL|macro|tasklet_unlock
mdefine_line|#define tasklet_unlock(t) do { } while (0)
macro_line|#endif
DECL|function|tasklet_schedule
r_extern
id|__inline__
r_void
id|tasklet_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|t-&gt;next
op_assign
id|tasklet_vec
(braket
id|cpu
)braket
dot
id|list
suffix:semicolon
id|tasklet_vec
(braket
id|cpu
)braket
dot
id|list
op_assign
id|t
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|cpu
comma
id|TASKLET_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|tasklet_hi_schedule
r_extern
id|__inline__
r_void
id|tasklet_hi_schedule
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|TASKLET_STATE_SCHED
comma
op_amp
id|t-&gt;state
)paren
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|t-&gt;next
op_assign
id|tasklet_hi_vec
(braket
id|cpu
)braket
dot
id|list
suffix:semicolon
id|tasklet_hi_vec
(braket
id|cpu
)braket
dot
id|list
op_assign
id|t
suffix:semicolon
id|__cpu_raise_softirq
c_func
(paren
id|cpu
comma
id|HI_SOFTIRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|tasklet_disable_nosync
r_extern
id|__inline__
r_void
id|tasklet_disable_nosync
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|t-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|tasklet_disable
r_extern
id|__inline__
r_void
id|tasklet_disable
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|tasklet_disable_nosync
c_func
(paren
id|t
)paren
suffix:semicolon
id|tasklet_unlock_wait
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
DECL|function|tasklet_enable
r_extern
id|__inline__
r_void
id|tasklet_enable
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|t-&gt;count
)paren
suffix:semicolon
)brace
r_extern
r_void
id|tasklet_kill
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|tasklet_init
c_func
(paren
r_struct
id|tasklet_struct
op_star
id|t
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|data
)paren
suffix:semicolon
macro_line|#ifdef __SMP__
DECL|macro|SMP_TIMER_NAME
mdefine_line|#define SMP_TIMER_NAME(name) name##__thr
DECL|macro|SMP_TIMER_DEFINE
mdefine_line|#define SMP_TIMER_DEFINE(name, task) &bslash;&n;DECLARE_TASKLET(task, name##__thr, 0); &bslash;&n;static void name (unsigned long dummy) &bslash;&n;{ &bslash;&n;&t;tasklet_schedule(&amp;(task)); &bslash;&n;}
macro_line|#else /* __SMP__ */
DECL|macro|SMP_TIMER_NAME
mdefine_line|#define SMP_TIMER_NAME(name) name
DECL|macro|SMP_TIMER_DEFINE
mdefine_line|#define SMP_TIMER_DEFINE(name, task)
macro_line|#endif /* __SMP__ */
multiline_comment|/* Old BH definitions */
r_extern
r_struct
id|tasklet_struct
id|bh_task_vec
(braket
)braket
suffix:semicolon
multiline_comment|/* It is exported _ONLY_ for wait_on_irq(). */
r_extern
id|spinlock_t
id|global_bh_lock
suffix:semicolon
DECL|function|mark_bh
r_extern
id|__inline__
r_void
id|mark_bh
c_func
(paren
r_int
id|nr
)paren
(brace
id|tasklet_hi_schedule
c_func
(paren
id|bh_task_vec
op_plus
id|nr
)paren
suffix:semicolon
)brace
r_extern
r_void
id|init_bh
c_func
(paren
r_int
id|nr
comma
r_void
(paren
op_star
id|routine
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|remove_bh
c_func
(paren
r_int
id|nr
)paren
suffix:semicolon
multiline_comment|/*&n; * Autoprobing for irqs:&n; *&n; * probe_irq_on() and probe_irq_off() provide robust primitives&n; * for accurate IRQ probing during kernel initialization.  They are&n; * reasonably simple to use, are not &quot;fooled&quot; by spurious interrupts,&n; * and, unlike other attempts at IRQ probing, they do not get hung on&n; * stuck interrupts (such as unused PS2 mouse interfaces on ASUS boards).&n; *&n; * For reasonably foolproof probing, use them as follows:&n; *&n; * 1. clear and/or mask the device&squot;s internal interrupt.&n; * 2. sti();&n; * 3. irqs = probe_irq_on();      // &quot;take over&quot; all unassigned idle IRQs&n; * 4. enable the device and cause it to trigger an interrupt.&n; * 5. wait for the device to interrupt, using non-intrusive polling or a delay.&n; * 6. irq = probe_irq_off(irqs);  // get IRQ number, 0=none, negative=multiple&n; * 7. service the device to clear its pending interrupt.&n; * 8. loop again if paranoia is required.&n; *&n; * probe_irq_on() returns a mask of allocated irq&squot;s.&n; *&n; * probe_irq_off() takes the mask as a parameter,&n; * and returns the irq number which occurred,&n; * or zero if none occurred, or a negative irq number&n; * if more than one irq occurred.&n; */
r_extern
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* returns 0 on failure */
r_extern
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* returns 0 or negative on failure */
r_extern
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* returns mask of ISA interrupts */
macro_line|#endif
eof
