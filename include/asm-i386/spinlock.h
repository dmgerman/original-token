macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#ifndef __SMP__
multiline_comment|/*&n; * Your basic spinlocks, allowing only a single CPU anywhere&n; */
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
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;do { } while(0)
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
macro_line|#else
multiline_comment|/*&n; * Simple spin lock operations.  There are two variants, one clears IRQ&squot;s&n; * on the local processor, one does not.&n; *&n; * We make no fairness assumptions. They have a cost.&n; */
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
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 0; (x)-&gt;previous = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while(((volatile spinlock_t *)(x))-&gt;lock)
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
mdefine_line|#define spin_lock(lock) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;&bslash;n1:&bslash;t&quot; &bslash;&n;&t;&quot;lock ; btsl $0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jc 2f&bslash;n&quot; &bslash;&n;&t;&quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;t&quot; &bslash;&n;&t;&quot;testb $1,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=m&quot; (__dummy_lock(lock)))
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lock ; btrl $0,%0&quot; &bslash;&n;&t;:&quot;=m&quot; (__dummy_lock(lock)))
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
DECL|member|previous
r_int
r_int
id|previous
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED { 0, 0 }
multiline_comment|/*&n; * On x86, we implement read-write locks as a 32-bit counter&n; * with the high bit (sign) being the &quot;write&quot; bit.&n; *&n; * The inline assembly is non-obvious. Think about it.&n; */
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n1:&bslash;t&quot; &bslash;&n;&t;&t;     &quot;lock ; incl %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;js 2f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;tlock ; decl %0&bslash;n&quot; &bslash;&n;&t;&t;     &quot;3:&bslash;tcmpl $0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;js 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 1b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     :&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw) &bslash;&n;&t;asm volatile(&quot;lock ; decl %0&quot; &bslash;&n;&t;&t;:&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|macro|write_lock
mdefine_line|#define write_lock(rw) &bslash;&n;&t;asm volatile(&quot;&bslash;n1:&bslash;t&quot; &bslash;&n;&t;&t;     &quot;lock ; btsl $31,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jc 3f&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;testl $0x7fffffff,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jne 4f&bslash;n&quot; &bslash;&n;&t;&t;     &quot;2:&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;     &quot;3:&bslash;ttestl $-1,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;js 3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;lock ; btsl $31,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jc 3b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;4:&bslash;ttestl $0x7fffffff,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jne 4b&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;     &quot;jmp 2b&bslash;n&quot; &bslash;&n;&t;&t;     &quot;.previous&quot; &bslash;&n;&t;&t;     :&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw) &bslash;&n;&t;asm volatile(&quot;lock ; btrl $31,%0&quot;:&quot;=m&quot; (__dummy_lock(&amp;(rw)-&gt;lock)))
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;do { __cli(); read_lock(lock); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;do { read_unlock(lock); __sti(); } while (0)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;do { __cli(); write_lock(lock); } while (0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;do { write_unlock(lock); __sti(); } while (0)
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
