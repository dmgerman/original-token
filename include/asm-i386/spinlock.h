macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/rwlock.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_extern
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
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* It seems that people are forgetting to&n; * initialize their spinlocks properly, tsk tsk.&n; * Remember to turn this off in 2.4. -ben&n; */
DECL|macro|SPINLOCK_DEBUG
mdefine_line|#define SPINLOCK_DEBUG&t;1
multiline_comment|/*&n; * Your basic SMP spinlocks, allowing only a single CPU anywhere&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
DECL|member|magic
r_int
id|magic
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPINLOCK_MAGIC
mdefine_line|#define SPINLOCK_MAGIC&t;0xdead4ead
macro_line|#if SPINLOCK_DEBUG
DECL|macro|SPINLOCK_MAGIC_INIT
mdefine_line|#define SPINLOCK_MAGIC_INIT&t;, SPINLOCK_MAGIC
macro_line|#else
DECL|macro|SPINLOCK_MAGIC_INIT
mdefine_line|#define SPINLOCK_MAGIC_INIT&t;/* */
macro_line|#endif
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 SPINLOCK_MAGIC_INIT }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { *(x) = SPIN_LOCK_UNLOCKED; } while(0)
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while(((volatile spinlock_t *)(x))-&gt;lock)
DECL|macro|spin_lock_string
mdefine_line|#define spin_lock_string &bslash;&n;&t;&quot;&bslash;n1:&bslash;t&quot; &bslash;&n;&t;&quot;lock ; btsl $0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jc 2f&bslash;n&quot; &bslash;&n;&t;&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;testb $1,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&quot;.previous&quot;
multiline_comment|/*&n; * Sadly, some early PPro chips require the locked access,&n; * otherwise we could just always simply do&n; *&n; * &t;#define spin_unlock_string &bslash;&n; *&t;&t;&quot;movb $0,%0&quot;&n; *&n; * Which is noticeably faster.&n; */
DECL|macro|spin_unlock_string
mdefine_line|#define spin_unlock_string &bslash;&n;&t;&quot;lock ; btrl $0,%0&quot;
DECL|function|spin_lock
r_extern
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
macro_line|#if SPINLOCK_DEBUG
id|__label__
id|here
suffix:semicolon
id|here
suffix:colon
r_if
c_cond
(paren
id|lock-&gt;magic
op_ne
id|SPINLOCK_MAGIC
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;eip: %p&bslash;n&quot;
comma
op_logical_and
id|here
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
id|spin_lock_string
suffix:colon
l_string|&quot;=m&quot;
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
DECL|function|spin_unlock
r_extern
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
macro_line|#if SPINLOCK_DEBUG
r_if
c_cond
(paren
id|lock-&gt;magic
op_ne
id|SPINLOCK_MAGIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lock-&gt;lock
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
id|spin_unlock_string
suffix:colon
l_string|&quot;=m&quot;
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
mdefine_line|#define spin_trylock(lock) ({ !test_and_set_bit(0,(lock)); })
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
macro_line|#if SPINLOCK_DEBUG
DECL|member|magic
r_int
id|magic
suffix:semicolon
macro_line|#endif
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RWLOCK_MAGIC
mdefine_line|#define RWLOCK_MAGIC&t;0xdeaf1eed
macro_line|#if SPINLOCK_DEBUG
DECL|macro|RWLOCK_MAGIC_INIT
mdefine_line|#define RWLOCK_MAGIC_INIT&t;, RWLOCK_MAGIC
macro_line|#else
DECL|macro|RWLOCK_MAGIC_INIT
mdefine_line|#define RWLOCK_MAGIC_INIT&t;/* */
macro_line|#endif
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { RW_LOCK_BIAS RWLOCK_MAGIC_INIT }
multiline_comment|/*&n; * On x86, we implement read-write locks as a 32-bit counter&n; * with the high bit (sign) being the &quot;contended&quot; bit.&n; *&n; * The inline assembly is non-obvious. Think about it.&n; *&n; * Changed to use the same technique as rw semaphores.  See&n; * semaphore.h for details.  -ben&n; */
multiline_comment|/* the spinlock helpers are in arch/i386/kernel/semaphore.S */
DECL|function|read_lock
r_extern
r_inline
r_void
id|read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
macro_line|#if SPINLOCK_DEBUG
r_if
c_cond
(paren
id|rw-&gt;magic
op_ne
id|RWLOCK_MAGIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__build_read_lock
c_func
(paren
id|rw
comma
l_string|&quot;__read_lock_failed&quot;
)paren
suffix:semicolon
)brace
DECL|function|write_lock
r_extern
r_inline
r_void
id|write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
macro_line|#if SPINLOCK_DEBUG
r_if
c_cond
(paren
id|rw-&gt;magic
op_ne
id|RWLOCK_MAGIC
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|__build_write_lock
c_func
(paren
id|rw
comma
l_string|&quot;__write_lock_failed&quot;
)paren
suffix:semicolon
)brace
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;asm volatile(&quot;lock ; incl %0&quot; :&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw)&t;asm volatile(&quot;lock ; addl $&quot; RW_LOCK_BIAS_STR &quot;,%0&quot;:&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|function|write_trylock
r_extern
r_inline
r_int
id|write_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|atomic_t
op_star
id|count
op_assign
(paren
id|atomic_t
op_star
)paren
id|lock
suffix:semicolon
r_if
c_cond
(paren
id|atomic_sub_and_test
c_func
(paren
id|RW_LOCK_BIAS
comma
id|count
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|atomic_add
c_func
(paren
id|RW_LOCK_BIAS
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
