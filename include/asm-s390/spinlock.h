multiline_comment|/*&n; *  include/asm-s390/spinlock.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;include/asm-i386/spinlock.h&quot;&n; */
macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
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
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp) do { (lp)-&gt;lock = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lp)&t;do { barrier(); } while((volatile spinlock_t *)(lp)-&gt;lock)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x) ((x)-&gt;lock != 0)
DECL|function|spin_lock
r_extern
r_inline
r_void
id|spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lp
)paren
(brace
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;    lhi   1,-1&bslash;n&quot;
l_string|&quot;0:  slr   0,0&bslash;n&quot;
l_string|&quot;    cs    0,1,%1&bslash;n&quot;
l_string|&quot;    jl    0b&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|function|spin_trylock
r_extern
r_inline
r_int
id|spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lp
)paren
(brace
r_int
r_int
id|result
suffix:semicolon
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;    slr   %1,%1&bslash;n&quot;
l_string|&quot;    lhi   0,-1&bslash;n&quot;
l_string|&quot;0:  cs    %1,0,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|lp-&gt;lock
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|lp-&gt;lock
)paren
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
op_logical_neg
id|result
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
id|lp
)paren
(brace
id|__asm__
id|__volatile
c_func
(paren
l_string|&quot;    xc 0(4,%0),0(%0)&bslash;n&quot;
l_string|&quot;    bcr 15,0&quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;a&quot;
(paren
id|lp
)paren
)paren
suffix:semicolon
)brace
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
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)   &bslash;&n;        asm volatile(&quot;   l     2,%0&bslash;n&quot;   &bslash;&n;                     &quot;0: sll   2,1&bslash;n&quot;    &bslash;&n;                     &quot;   srl   2,1&bslash;n&quot;     /* clear high (=write) bit */ &bslash;&n;                     &quot;   lr    3,2&bslash;n&quot;    &bslash;&n;                     &quot;   ahi   3,1&bslash;n&quot;     /* one more reader */ &bslash;&n;                     &quot;   cs    2,3,%0&bslash;n&quot;  /* try to write new value */ &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : : &quot;2&quot;, &quot;3&quot; );
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw) &bslash;&n;        asm volatile(&quot;   l     2,%0&bslash;n&quot;   &bslash;&n;                     &quot;0: lr    3,2&bslash;n&quot;    &bslash;&n;                     &quot;   ahi   3,-1&bslash;n&quot;    /* one less reader */ &bslash;&n;                     &quot;   cs    2,3,%0&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : : &quot;2&quot;, &quot;3&quot; );
DECL|macro|write_lock
mdefine_line|#define write_lock(rw) &bslash;&n;        asm volatile(&quot;   lhi   3,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   3,31&bslash;n&quot;    /* new lock value = 0x80000000 */ &bslash;&n;                     &quot;0: slr   2,2&bslash;n&quot;     /* old lock value must be 0 */ &bslash;&n;                     &quot;   cs    2,3,%0&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : : &quot;2&quot;, &quot;3&quot; );
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw) &bslash;&n;        asm volatile(&quot;   slr   3,3&bslash;n&quot;     /* new lock value = 0 */ &bslash;&n;                     &quot;0: lhi   2,1&bslash;n&quot;    &bslash;&n;                     &quot;   sll   2,31&bslash;n&quot;    /* old lock value must be 0x80000000 */ &bslash;&n;                     &quot;   cs    2,3,%0&bslash;n&quot; &bslash;&n;                     &quot;   jl    0b&quot;       &bslash;&n;                     : &quot;+m&quot; ((rw)-&gt;lock) : : &quot;2&quot;, &quot;3&quot; );
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
