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
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED { }
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
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { save_flags(flags); cli(); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags) &bslash;&n;&t;restore_flags(flags)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { save_flags(flags); cli(); } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags) &bslash;&n;&t;restore_flags(flags)
macro_line|#else /* __SMP__ */
multiline_comment|/* Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
DECL|struct|_spinlock_debug
r_struct
id|_spinlock_debug
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_volatile
r_int
r_int
id|owner_pc
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|spinlock_t
r_typedef
r_struct
id|_spinlock_debug
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { 0, 0 }
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;{ 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp)&t;do { (lp)-&gt;owner_pc = 0; (lp)-&gt;lock = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lp)&t;do { barrier(); } while((lp)-&gt;lock)
r_extern
r_void
id|_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_lock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_unlock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_lock_irqsave
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_unlock_irqrestore
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lp)&t;&t;&t;_spin_lock(lp)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lp)&t;&t;_spin_trylock(lp)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lp)&t;&t;&t;_spin_unlock(lp)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lp)&t;&t;_spin_lock_irq(lp)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lp)&t;&t;_spin_unlock_irq(lp)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lp, flags)&t;do { __save_and_cli(flags); &bslash;&n;&t;&t;&t;&t;&t;     _spin_lock_irqsave(lp); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lp, flags) do { _spin_unlock_irqrestore(lp); &bslash;&n;&t;&t;&t;&t;&t;       __restore_flags(flags); } while(0)
macro_line|#if 0
r_extern
id|__inline__
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
l_string|&quot;stw 0,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
id|stuck
op_assign
l_int|10000000
suffix:semicolon
r_int
id|tmp
comma
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;mtctr %2&bslash;n&quot;
l_string|&quot;1:&t;lwarx %0,0,%3&bslash;n&quot;
l_string|&quot;&t;andi. %1,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;&t;ori %0,%0,1&bslash;n&bslash;t&quot;
l_string|&quot;&t;bne- 2f&bslash;n&bslash;t&quot;
l_string|&quot;&t;stwcx. %0,0,%3&bslash;n&bslash;t&quot;
l_string|&quot;2:&t;bdnzf- 2,1b&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|stuck
)paren
comma
l_string|&quot;r&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;ctr&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
(brace
r_int
r_int
id|__nip
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mfnip %0&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__nip
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;spinlock stuck at %08lx&bslash;n&quot;
comma
id|__nip
)paren
suffix:semicolon
)brace
)brace
mdefine_line|#define spin_trylock(lock) (!set_bit(0,(lock)))
mdefine_line|#define spin_lock_irq(lock) &bslash;&n;&t;do { __cli(); spin_lock(lock); } while (0)
mdefine_line|#define spin_unlock_irq(lock) &bslash;&n;&t;do { spin_unlock(lock); __sti(); } while (0)
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { __save_flags(flags); __cli(); spin_lock(lock); } while (0)
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { spin_unlock(lock); __restore_flags(flags); } while (0)
macro_line|#endif
DECL|struct|_rwlock_debug
r_struct
id|_rwlock_debug
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_int
r_int
id|owner_pc
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|rwlock_t
r_typedef
r_struct
id|_rwlock_debug
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED { 0, 0 }
r_extern
r_void
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&t;_read_lock(rw)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;_read_unlock(rw)
DECL|macro|write_lock
mdefine_line|#define write_lock(rw)&t;&t;_write_lock(rw)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw)&t;_write_unlock(rw)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(rw)&t;_read_lock_irq(rw)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(rw)&t;_read_unlock_irq(rw)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(rw)&t;_write_lock_irq(rw)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(rw)&t;_write_unlock_irq(rw)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(rw, flags) &bslash;&n;do { __save_and_cli(flags); _read_lock_irqsave(rw); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(rw, flags) do { _read_unlock_irqrestore(rw); &bslash;&n;&t;&t;&t;&t;&t;       __restore_flags(flags); } while(0)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(rw, flags) &bslash;&n;do { __save_and_cli(flags); _write_lock_irqsave(rw); } while(0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(rw, flags) do { _write_unlock_irqrestore(rw); &bslash;&n;&t;&t;&t;&t;&t;        __restore_flags(flags); } while(0)
macro_line|#endif /* SMP */
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
