macro_line|#ifndef _ASM_IA64_SPINLOCK_H
DECL|macro|_ASM_IA64_SPINLOCK_H
mdefine_line|#define _ASM_IA64_SPINLOCK_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * This file is used for SMP configurations only.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
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
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;&t;&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;&t;&t;((x)-&gt;lock = 0) 
multiline_comment|/*&n; * Streamlined test_and_set_bit(0, (x)).  We use test-and-test-and-set&n; * rather than a simple xchg to avoid writing the cache-line when&n; * there is contention.&n; */
macro_line|#if 1 /* Bad code generation? */
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x) __asm__ __volatile__ ( &bslash;&n;       &quot;mov ar.ccv = r0&bslash;n&quot; &bslash;&n;       &quot;mov r29 = 1&bslash;n&quot; &bslash;&n;       &quot;;;&bslash;n&quot; &bslash;&n;       &quot;1:&bslash;n&quot; &bslash;&n;       &quot;ld4 r2 = %0&bslash;n&quot; &bslash;&n;       &quot;;;&bslash;n&quot; &bslash;&n;       &quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot; &bslash;&n;       &quot;(p7) br.cond.spnt.few 1b &bslash;n&quot; &bslash;&n;       &quot;cmpxchg4.acq r2 = %0, r29, ar.ccv&bslash;n&quot; &bslash;&n;       &quot;;;&bslash;n&quot; &bslash;&n;       &quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot; &bslash;&n;       &quot;(p7) br.cond.spnt.few 1b&bslash;n&quot; &bslash;&n;       &quot;;;&bslash;n&quot; &bslash;&n;       :: &quot;m&quot; __atomic_fool_gcc((x)) : &quot;r2&quot;, &quot;r29&quot;)
macro_line|#else 
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spinlock_t *__x = (x);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (__x-&gt;lock);&t;&t;&t;&bslash;&n;&t;} while (cmpxchg_acq(&amp;__x-&gt;lock, 0, 1));&t;&bslash;&n;}
macro_line|#endif
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x)&t;&t;(((spinlock_t *) x)-&gt;lock = 0)
multiline_comment|/* Streamlined !test_and_set_bit(0, (x)) */
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(x)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spinlock_t *__x = (x);&t;&t;&t;&t;&t;&bslash;&n;&t;__u32 old;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;old = __x-&gt;lock;&t;&t;&t;&t;&bslash;&n;&t;} while (cmpxchg_acq(&amp;__x-&gt;lock, old, 1) != old);&t;&bslash;&n;&t;old == 0;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x) &bslash;&n;&t;({ do { barrier(); } while(((volatile spinlock_t *)x)-&gt;lock); })
r_typedef
r_struct
(brace
DECL|member|read_counter
r_volatile
r_int
id|read_counter
suffix:colon
l_int|31
suffix:semicolon
DECL|member|write_lock
r_volatile
r_int
id|write_lock
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int tmp = 0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;1:&bslash;tfetchadd4.acq %0 = %1, 1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 2f&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;2:&bslash;tfetchadd4.rel %0 = %1, -1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;3:&bslash;tld4.acq %0 = %1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;br.cond.sptk.few 1b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.previous&bslash;n&quot;: &quot;=r&quot; (tmp), &quot;=m&quot; (__atomic_fool_gcc(rw)));&t;&bslash;&n;} while(0)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int tmp = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;fetchadd4.rel %0 = %1, -1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      : &quot;=r&quot; (tmp) : &quot;m&quot; (__atomic_fool_gcc(rw)));&t;&bslash;&n;} while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(rw)&t;&t;&t;&t;&bslash;&n;while(1) {&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;} while (!test_and_set_bit(31, (rw)));&t;&bslash;&n;&t;if ((rw)-&gt;read_counter) {&t;&t;&bslash;&n;&t;&t;clear_bit(31, (rw));&t;&t;&bslash;&n;&t;&t;while ((rw)-&gt;read_counter)&t;&bslash;&n;&t;&t;&t;;&t;&t;&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|write_unlock
mdefine_line|#define write_unlock(x)&t;&t;&t;&t;(clear_bit(31, (x)))
macro_line|#endif /*  _ASM_IA64_SPINLOCK_H */
eof
