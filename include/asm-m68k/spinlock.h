macro_line|#ifndef __M68K_SPINLOCK_H
DECL|macro|__M68K_SPINLOCK_H
mdefine_line|#define __M68K_SPINLOCK_H
multiline_comment|/*&n; * We don&squot;t do SMP on the m68k .... at least not yet.&n; */
multiline_comment|/*&n; * Gcc-2.7.x has a nasty bug with empty initializers.&n; */
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
mdefine_line|#define spin_lock(lock)&t;&t;(void)(lock) /* Not &quot;unused variable&quot;. */
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
mdefine_line|#define read_lock(lock)&t;&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;do { } while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;(void)(lock) /* Not &quot;unused variable&quot;. */
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
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&t;save_and_cli(flags)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags)&t;restore_flags(flags)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&t;save_and_cli(flags)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags)&t;restore_flags(flags)
macro_line|#endif
eof
