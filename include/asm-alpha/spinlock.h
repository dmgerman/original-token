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
macro_line|#else
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
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;do { (lock)-&gt;lock = 0; (lock)-&gt;previous = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;do { barrier(); } while(((volatile spinlock_t *)lock)-&gt;lock)
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
id|__label__
id|l1
suffix:semicolon
r_int
id|tmp
suffix:semicolon
r_int
id|stuck
op_assign
l_int|0x100000000
suffix:semicolon
id|l1
suffix:colon
multiline_comment|/* Use sub-sections to put the actual loop at the end&n;&t;   of this object file&squot;s text section so as to perfect&n;&t;   branch prediction.  */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;subq&t;%2,1,%2&bslash;n&quot;
l_string|&quot;&t;blbs&t;%0,2f&bslash;n&quot;
l_string|&quot;&t;or&t;%0,1,%0&bslash;n&quot;
l_string|&quot;&t;stq_c&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;beq&t;%0,3f&bslash;n&quot;
l_string|&quot;4:&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;ldq&t;%0,%1&bslash;n&quot;
l_string|&quot;&t;subq&t;%2,1,%2&bslash;n&quot;
l_string|&quot;3:&t;blt&t;%2,4b&bslash;n&quot;
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
comma
l_string|&quot;=r&quot;
(paren
id|stuck
)paren
suffix:colon
l_string|&quot;2&quot;
(paren
id|stuck
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stuck
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;spinlock stuck at %p (%lx)&bslash;n&quot;
comma
op_logical_and
id|l1
comma
id|lock-&gt;previous
)paren
suffix:semicolon
r_else
id|lock-&gt;previous
op_assign
(paren
r_int
r_int
)paren
op_logical_and
id|l1
suffix:semicolon
)brace
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock) (!set_bit(0,(lock)))
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock) &bslash;&n;&t;do { __cli(); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock) &bslash;&n;&t;do { spin_unlock(lock); __sti(); } while (0)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { flags = swpipl(7); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { spin_unlock(lock); setipl(flags); } while (0)
macro_line|#endif /* SMP */
macro_line|#endif /* _ALPHA_SPINLOCK_H */
eof
