macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
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
mdefine_line|#define spin_lock_init(lock)&t;do { } while(0)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;do { } while(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;(1)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;do { } while(0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;do { } while(0)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock)&t;cli()
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;sti()
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(lock)&t;local_bh_disable()
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock)&t;local_bh_enable()
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { save_flags(flags); cli(); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;restore_flags(flags)
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
DECL|macro|read_lock_bh
mdefine_line|#define read_lock_bh(lock)&t;local_bh_disable()
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock)&t;local_bh_enable()
DECL|macro|write_lock_bh
mdefine_line|#define write_lock_bh(lock)&t;local_bh_disable()
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock)&t;local_bh_enable()
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
r_typedef
r_struct
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
DECL|member|owner_cpu
r_volatile
r_int
r_int
id|owner_cpu
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0, 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp) &t;do { (lp)-&gt;lock = 0; } while(0)
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
r_int
id|spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lp)&t;&t;&t;_spin_lock(lp)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lp)&t;&t;&t;_spin_unlock(lp)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock) &bslash;&n;&t;do { __cli(); spin_lock(lock); } while (0)
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(___lk) do { local_bh_disable(); spin_lock(___lk); } while(0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock) &bslash;&n;&t;do { spin_unlock(lock); __sti(); } while (0)
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(___lk) do { spin_unlock(___lk); local_bh_enable(); } while(0)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags) &bslash;&n;&t;do { __save_flags(flags); __cli(); spin_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { spin_unlock(lock); __restore_flags(flags); } while (0)
r_extern
r_int
r_int
id|__spin_trylock
c_func
(paren
r_volatile
r_int
r_int
op_star
id|lock
)paren
suffix:semicolon
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
DECL|member|owner_pc
r_volatile
r_int
r_int
id|owner_pc
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
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
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&t;_read_lock(rw)
DECL|macro|write_lock
mdefine_line|#define write_lock(rw)&t;&t;_write_lock(rw)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw)&t;_write_unlock(rw)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;_read_unlock(rw)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;do { __cli(); read_lock(lock); } while (0)
DECL|macro|read_lock_bh
mdefine_line|#define read_lock_bh(lock)&t;do { local_bh_disable(); read_lock(lock); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;do { read_unlock(lock); __sti(); } while (0)
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock)&t;do { read_unlock(lock); local_bh_enable(); } while (0)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;do { __cli(); write_lock(lock); } while (0)
DECL|macro|write_lock_bh
mdefine_line|#define write_lock_bh(lock)&t;do { local_bh_disable(); write_lock(lock); } while(0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;do { write_unlock(lock); __sti(); } while (0)
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock)&t;do { write_unlock(lock); local_bh_enable(); } while(0)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { __save_flags(flags); __cli(); read_lock(lock); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { read_unlock(lock); __restore_flags(flags); } while (0)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&bslash;&n;&t;do { __save_flags(flags); __cli(); write_lock(lock); } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags) &bslash;&n;&t;do { write_unlock(lock); __restore_flags(flags); } while (0)
macro_line|#endif /* SMP */
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
