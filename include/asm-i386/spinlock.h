macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#ifndef __SMP__
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;do { } while(0)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;do { } while(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;do { } while(0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;do { } while(0)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock)&t;cli()
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;sti()
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { save_flags(flags); cli(); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;restore_flags(flags)
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
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;jmp 2f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;t&quot; &bslash;&n;&t;&quot;testb $1,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 1b&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;lock ; btsl $0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jc 1b&quot; &bslash;&n;&t;:&quot;=m&quot; (__dummy_lock(lock)))
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lock ; btrl $0,%0&quot; &bslash;&n;&t;:&quot;=m&quot; (__dummy_lock(lock)))
DECL|macro|spin_lock
macro_line|#undef spin_lock
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
id|stuck
op_assign
l_int|10000000
suffix:semicolon
id|l1
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jmp 2f&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;decl %1&bslash;n&bslash;t&quot;
l_string|&quot;je 3f&bslash;n&bslash;t&quot;
l_string|&quot;testb $1,%0&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&bslash;n&quot;
l_string|&quot;2:&bslash;t&quot;
l_string|&quot;lock ; btsl $0,%0&bslash;n&bslash;t&quot;
l_string|&quot;jc 1b&bslash;n&quot;
l_string|&quot;3:&quot;
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
l_string|&quot;=r&quot;
(paren
id|stuck
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
id|stuck
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stuck
)paren
(brace
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
)brace
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
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { __save_flags(flags); __cli(); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { spin_unlock(lock); __restore_flags(flags); } while (0)
macro_line|#endif /* SMP */
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
