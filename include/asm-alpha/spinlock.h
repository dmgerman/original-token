macro_line|#ifndef _ALPHA_SPINLOCK_H
DECL|macro|_ALPHA_SPINLOCK_H
mdefine_line|#define _ALPHA_SPINLOCK_H
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * These are the generic versions of the spinlocks&n; * and read-write locks.. We should actually do a&n; * &lt;linux/spinlock.h&gt; with all of this. Oh, well.&n; */
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;  do { local_irq_save(flags); spin_lock(lock); } while (0)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock) &bslash;&n;  do { local_irq_disable(); spin_lock(lock); } while (0)
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(lock) &bslash;&n;  do { local_bh_disable(); spin_lock(lock); } while (0)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags) &bslash;&n;  do { local_irq_save(flags); read_lock(lock); } while (0)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock) &bslash;&n;  do { local_irq_disable(); read_lock(lock); } while (0)
DECL|macro|read_lock_bh
mdefine_line|#define read_lock_bh(lock) &bslash;&n;  do { local_bh_disable(); read_lock(lock); } while (0)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags) &bslash;&n;  do { local_irq_save(flags); write_lock(lock); } while (0)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock) &bslash;&n;  do { local_irq_disable(); write_lock(lock); } while (0)
DECL|macro|write_lock_bh
mdefine_line|#define write_lock_bh(lock) &bslash;&n;  do { local_bh_disable(); write_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;  do { spin_unlock(lock); local_irq_restore(flags); } while (0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock) &bslash;&n;  do { spin_unlock(lock); local_irq_enable(); } while (0)
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock) &bslash;&n;  do { spin_unlock(lock); local_bh_enable(); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags) &bslash;&n;  do { read_unlock(lock); local_irq_restore(flags); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock) &bslash;&n;  do { read_unlock(lock); local_irq_enable(); } while (0)
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock) &bslash;&n;  do { read_unlock(lock); local_bh_enable(); } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags) &bslash;&n;  do { write_unlock(lock); local_irq_restore(flags); } while (0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock) &bslash;&n;  do { write_unlock(lock); local_irq_enable(); } while (0)
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock) &bslash;&n;  do { write_unlock(lock); local_bh_enable(); } while (0)
macro_line|#ifndef __SMP__
multiline_comment|/*&n; * Your basic spinlocks, allowing only a single CPU anywhere&n; *&n; * Gcc-2.7.x has a nasty bug with empty initializers.&n; */
macro_line|#if (__GNUC__ &gt; 2) || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &gt;= 8)
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { }
macro_line|#else
DECL|member|gcc_is_buggy
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
r_int
id|gcc_is_buggy
suffix:semicolon
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
macro_line|#endif
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;&t;&t;((void)(lock))
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;&t;&t;((void)(lock))
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;&t;&t;((void)(lock), 1)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;&t;&t;((void)(lock))
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;&t;&t;((void)(lock))
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;&t;&t;((void)(lock), 0)
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; *&n; * Gcc-2.7.x has a nasty bug with empty initializers.&n; */
macro_line|#if (__GNUC__ &gt; 2) || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &gt;= 8)
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { }
macro_line|#else
DECL|member|gcc_is_buggy
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
r_int
id|gcc_is_buggy
suffix:semicolon
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0 }
macro_line|#endif
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;&t;&t;((void)(lock))
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;&t;&t;((void)(lock))
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;&t;&t;((void)(lock))
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;&t;&t;((void)(lock))
macro_line|#else /* __SMP__ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/current.h&gt;
DECL|macro|DEBUG_SPINLOCK
mdefine_line|#define DEBUG_SPINLOCK 1
DECL|macro|DEBUG_RWLOCK
mdefine_line|#define DEBUG_RWLOCK 1
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
multiline_comment|/*__attribute__((aligned(32))) */
suffix:semicolon
macro_line|#if DEBUG_SPINLOCK
DECL|member|on_cpu
r_int
id|on_cpu
suffix:semicolon
DECL|member|line_no
r_int
id|line_no
suffix:semicolon
DECL|member|previous
r_void
op_star
id|previous
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|base_file
r_const
r_char
op_star
id|base_file
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
macro_line|#if DEBUG_SPINLOCK
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) {0, -1, 0, 0, 0, 0}
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((x)-&gt;lock = 0, (x)-&gt;on_cpu = -1, (x)-&gt;previous = 0, (x)-&gt;task = 0)
macro_line|#else
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;((x)-&gt;lock = 0)
macro_line|#endif
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;({ do { barrier(); } while ((x)-&gt;lock); })
DECL|member|a
DECL|typedef|__dummy_lock_t
r_typedef
r_struct
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
id|__dummy_lock_t
suffix:semicolon
DECL|macro|__dummy_lock
mdefine_line|#define __dummy_lock(lock) (*(__dummy_lock_t *)(lock))
macro_line|#if DEBUG_SPINLOCK
r_extern
r_void
id|spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|debug_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|debug_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|spin_lock
mdefine_line|#define spin_lock(LOCK) debug_spin_lock(LOCK, __BASE_FILE__, __LINE__)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(LOCK) debug_spin_trylock(LOCK, __BASE_FILE__, __LINE__)
DECL|macro|spin_lock_own
mdefine_line|#define spin_lock_own(LOCK, LOCATION)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!((LOCK)-&gt;lock &amp;&amp; (LOCK)-&gt;on_cpu == smp_processor_id()))&t;&bslash;&n;&t;&t;printk(&quot;%s: called on %d from %p but lock %s on %d&bslash;n&quot;,&t;&bslash;&n;&t;&t;       LOCATION, smp_processor_id(),&t;&t;&t;&bslash;&n;&t;&t;       __builtin_return_address(0),&t;&t;&t;&bslash;&n;&t;&t;       (LOCK)-&gt;lock ? &quot;taken&quot; : &quot;freed&quot;, (LOCK)-&gt;on_cpu); &bslash;&n;} while (0)
macro_line|#else
DECL|function|spin_unlock
r_static
r_inline
r_void
id|spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
id|lock-&gt;lock
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|spin_lock
r_static
r_inline
r_void
id|spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
id|tmp
suffix:semicolon
multiline_comment|/* Use sub-sections to put the actual loop at the end&n;&t;   of this object file&squot;s text section so as to perfect&n;&t;   branch prediction.  */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;or&t;%0,1,%0&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;ldl&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock) (!test_and_set_bit(0,(lock)))
DECL|macro|spin_lock_own
mdefine_line|#define spin_lock_own(LOCK, LOCATION)&t;((void)0)
macro_line|#endif /* DEBUG_SPINLOCK */
multiline_comment|/***********************************************************/
r_typedef
r_struct
(brace
DECL|member|write_lock
DECL|member|read_counter
r_volatile
r_int
id|write_lock
suffix:colon
l_int|1
comma
id|read_counter
suffix:colon
l_int|31
suffix:semicolon
DECL|typedef|rwlock_t
)brace
multiline_comment|/*__attribute__((aligned(32)))*/
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
macro_line|#if DEBUG_RWLOCK
r_extern
r_void
id|write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#else
DECL|function|write_lock
r_static
r_inline
r_void
id|write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;bne&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;or&t;$31,1,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;bne&t;%1,6b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|read_lock
r_static
r_inline
r_void
id|read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;blbs&t;%1,6f&bslash;n&quot;
l_string|&quot;&t;subl&t;%1,2,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;blbs&t;%1,6b&bslash;n&quot;
l_string|&quot;&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_RWLOCK */
DECL|function|write_unlock
r_static
r_inline
r_void
id|write_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
op_star
)paren
id|lock
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|read_unlock
r_static
r_inline
r_void
id|read_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
id|regx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;addl&t;%1,2,%1&bslash;n&quot;
l_string|&quot;&t;stl_c&t;%1,%0&bslash;n&quot;
l_string|&quot;&t;beq&t;%1,6f&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;br&t;1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regx
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|__dummy_lock
c_func
(paren
id|lock
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* SMP */
macro_line|#endif /* _ALPHA_SPINLOCK_H */
eof
