macro_line|#ifndef _ASM_IA64_SPINLOCK_H
DECL|macro|_ASM_IA64_SPINLOCK_H
mdefine_line|#define _ASM_IA64_SPINLOCK_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * This file is used for SMP configurations only.&n; */
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
multiline_comment|/* Streamlined test_and_set_bit(0, (x)) */
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x) __asm__ __volatile__ ( &bslash;&n;&t;&quot;mov ar.ccv = r0&bslash;n&quot; &bslash;&n;&t;&quot;mov r29 = 1&bslash;n&quot; &bslash;&n;&t;&quot;;;&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;n&quot; &bslash;&n;&t;&quot;ld4 r2 = [%0]&bslash;n&quot; &bslash;&n;&t;&quot;;;&bslash;n&quot; &bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot; &bslash;&n;&t;&quot;(p7) br.cond.dptk.few 1b &bslash;n&quot; &bslash;&n;&t;&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv&bslash;n&quot; &bslash;&n;&t;&quot;;;&bslash;n&quot; &bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot; &bslash;&n;&t;&quot;(p7) br.cond.dptk.few 1b&bslash;n&quot; &bslash;&n;&t;&quot;;;&bslash;n&quot; &bslash;&n;&t;:: &quot;m&quot; __atomic_fool_gcc((x)) : &quot;r2&quot;, &quot;r29&quot;)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x) __asm__ __volatile__ (&quot;st4.rel [%0] = r0;;&quot; : &quot;=m&quot; (__atomic_fool_gcc((x))))
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(x) (!test_and_set_bit(0, (x)))
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
mdefine_line|#define read_lock(rw) &bslash;&n;do { &bslash;&n;&t;int tmp = 0; &bslash;&n;&t;__asm__ __volatile__ (&quot;1:&bslash;tfetchadd4.acq %0 = %1, 1&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 2f&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;2:&bslash;tfetchadd4.rel %0 = %1, -1&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;3:&bslash;tld4.acq %0 = %1&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 3b&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;br.cond.sptk.few 1b&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot; &bslash;&n;&t;&t;&t;      &quot;.previous&bslash;n&quot;: &quot;=r&quot; (tmp), &quot;=m&quot; (__atomic_fool_gcc(rw))); &bslash;&n;} while(0)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw) &bslash;&n;do { &bslash;&n;&t;int tmp = 0; &bslash;&n;&t;__asm__ __volatile__ (&quot;fetchadd4.rel %0 = %1, -1&bslash;n&quot; &bslash;&n;&t;&t;&t;      : &quot;=r&quot; (tmp) : &quot;m&quot; (__atomic_fool_gcc(rw))); &bslash;&n;} while(0)
multiline_comment|/*&n; * These may need to be rewhacked in asm().&n; * XXX FIXME SDV - This may have a race on real hardware but is sufficient for SoftSDV&n; */
DECL|macro|write_lock
mdefine_line|#define write_lock(rw) &bslash;&n;while(1) {&bslash;&n;&t;do { &bslash;&n;&t;} while (!test_and_set_bit(31, (rw))); &bslash;&n;&t;if ((rw)-&gt;read_counter) { &bslash;&n;&t;&t;clear_bit(31, (rw)); &bslash;&n;&t;&t;while ((rw)-&gt;read_counter) &bslash;&n;&t;&t;&t;; &bslash;&n;&t;} else { &bslash;&n;&t;&t;break; &bslash;&n;&t;} &bslash;&n;}
DECL|macro|write_unlock
mdefine_line|#define write_unlock(x)&t;&t;&t;&t;(clear_bit(31, (x)))
macro_line|#endif /*  _ASM_IA64_SPINLOCK_H */
eof
