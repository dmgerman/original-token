macro_line|#ifndef _ALPHA_SPINLOCK_H
DECL|macro|_ALPHA_SPINLOCK_H
mdefine_line|#define _ALPHA_SPINLOCK_H
macro_line|#ifndef __SMP__
multiline_comment|/* gcc 2.7.2 can crash initializing an empty structure.  */
DECL|member|dummy
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
r_int
id|dummy
suffix:semicolon
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;&t;&t;do { } while(0)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;&t;&t;do { } while(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;&t;&t;do { } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;&t;&t;do { } while(0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;&t;&t;do { } while(0)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock)&t;&t;&t;setipl(7)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;&t;&t;setipl(0)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags)&t;&t;do { (flags) = swpipl(7); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags)&t;setipl(flags)
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
DECL|member|dummy
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
r_int
id|dummy
suffix:semicolon
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED { 0 }
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;do { } while(0)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;do { } while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;do { } while(0)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;do { } while(0)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;cli()
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;sti()
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;cli()
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;sti()
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&t;do { (flags) = swpipl(7); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags)&t;setipl(flags)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&t;do { (flags) = swpipl(7); } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags)&t;setipl(flags)
macro_line|#else /* __SMP__ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/current.h&gt;
multiline_comment|/* Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|previous
r_int
r_int
id|previous
suffix:semicolon
DECL|member|task
r_int
r_int
id|task
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x) &bslash;&n;&t;do { (x)-&gt;lock = 0; (x)-&gt;previous = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x) &bslash;&n;&t;do { barrier(); } while(((volatile spinlock_t *)x)-&gt;lock)
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mb; stq $31,%0&quot;
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
macro_line|#if 1
DECL|macro|DEBUG_SPINLOCK
mdefine_line|#define DEBUG_SPINLOCK
macro_line|#else
DECL|macro|DEBUG_SPINLOCK
macro_line|#undef DEBUG_SPINLOCK
macro_line|#endif
macro_line|#ifdef DEBUG_SPINLOCK
r_extern
r_void
id|spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#else
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
l_string|&quot;1:&t;ldq_l&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;or&t;%0,1,%0&bslash;n&quot;
l_string|&quot;&t;stq_c&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,2f&bslash;n&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;ldq&t;%0,%1&bslash;n&quot;
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
)paren
suffix:semicolon
)brace
macro_line|#endif /* DEBUG_SPINLOCK */
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock) (!test_and_set_bit(0,(lock)))
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock) &bslash;&n;&t;do { __cli(); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock) &bslash;&n;&t;do { spin_unlock(lock); __sti(); } while (0)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { __save_and_cli(flags); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { spin_unlock(lock); __restore_flags(flags); } while (0)
multiline_comment|/***********************************************************/
macro_line|#if 1
DECL|macro|DEBUG_RWLOCK
mdefine_line|#define DEBUG_RWLOCK
macro_line|#else
DECL|macro|DEBUG_RWLOCK
macro_line|#undef DEBUG_RWLOCK
macro_line|#endif
DECL|member|write_lock
DECL|member|read_counter
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
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
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED { 0, 0 }
macro_line|#ifdef DEBUG_RWLOCK
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
comma
id|regy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l&t;%1,%0;&quot;
l_string|&quot;&t;blbs&t;%1,6f;&quot;
l_string|&quot;&t;or&t;%1,1,%2;&quot;
l_string|&quot;&t;stl_c&t;%2,%0;&quot;
l_string|&quot;&t;beq&t;%2,6f;&quot;
l_string|&quot;&t;blt&t;%1,8f;&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0;&quot;
l_string|&quot;&t;blbs&t;%1,6b;&quot;
l_string|&quot;&t;br&t;1b;&quot;
l_string|&quot;8:&t;ldl&t;%1,%0;&quot;
l_string|&quot;&t;blt&t;%1,8b;&quot;
l_string|&quot;9:&t;br&t;4b&bslash;n&quot;
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
comma
l_string|&quot;=&amp;r&quot;
(paren
id|regy
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mb; stl $31,%0&quot;
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
macro_line|#ifdef DEBUG_RWLOCK
r_extern
r_void
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#else
DECL|function|_read_lock
r_static
r_inline
r_void
id|_read_lock
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
l_string|&quot;1:&t;ldl_l&t;%1,%0;&quot;
l_string|&quot;&t;blbs&t;%1,6f;&quot;
l_string|&quot;&t;subl&t;%1,2,%1;&quot;
l_string|&quot;&t;stl_c&t;%1,%0;&quot;
l_string|&quot;&t;beq&t;%1,6f;&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;6:&t;ldl&t;%1,%0;&quot;
l_string|&quot;&t;blbs&t;%1,6b;&quot;
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
macro_line|#endif /* DEBUG_RWLOCK */
DECL|macro|read_lock
mdefine_line|#define read_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_read_lock(lock); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
DECL|function|_read_unlock
r_static
r_inline
r_void
id|_read_unlock
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
l_string|&quot;1:&t;ldl_l&t;%1,%0;&quot;
l_string|&quot;&t;addl&t;%1,2,%1;&quot;
l_string|&quot;&t;stl_c&t;%1,%0;&quot;
l_string|&quot;&t;beq&t;%1,6f;&quot;
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
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_read_unlock(lock); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;do { __cli(); _read_lock(lock); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;do { _read_unlock(lock); __sti(); } while (0)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;do { __cli(); write_lock(lock); } while (0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;do { write_unlock(lock); __sti(); } while (0)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { __save_and_cli(flags); _read_lock(lock); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { _read_unlock(lock); __restore_flags(flags); } while (0)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { __save_and_cli(flags); write_lock(lock); } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { write_unlock(lock); __restore_flags(flags); } while (0)
macro_line|#endif /* SMP */
macro_line|#endif /* _ALPHA_SPINLOCK_H */
eof
