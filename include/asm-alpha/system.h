macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * System defines.. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.&n; */
multiline_comment|/*&n; * We leave one page for the initial stack page, and one page for&n; * the initial process structure. Also, the console eats 3 MB for&n; * the initial bootloader (one of which we can reclaim later).&n; * With a few other pages for various reasons, we&squot;ll use an initial&n; * load address of PAGE_OFFSET+0x310000UL&n; */
DECL|macro|BOOT_PCB
mdefine_line|#define BOOT_PCB&t;0x20000000
DECL|macro|BOOT_ADDR
mdefine_line|#define BOOT_ADDR&t;0x20000000
multiline_comment|/* Remove when official MILO sources have ELF support: */
DECL|macro|BOOT_SIZE
mdefine_line|#define BOOT_SIZE&t;(16*1024)
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;(PAGE_OFFSET+0x300000)
DECL|macro|SWAPPER_PGD
mdefine_line|#define SWAPPER_PGD&t;(PAGE_OFFSET+0x300000)
DECL|macro|INIT_STACK
mdefine_line|#define INIT_STACK&t;(PAGE_OFFSET+0x302000)
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT&t;(PAGE_OFFSET+0x304000)
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;(PAGE_OFFSET+0x308000)
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;(PAGE_OFFSET+0x30A000)
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;(PAGE_OFFSET+0x310000)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * This is the logout header that should be common to all platforms&n; * (assuming they are running OSF/1 PALcode, I guess).&n; */
DECL|struct|el_common
r_struct
id|el_common
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size in bytes of logout area */
DECL|member|sbz1
r_int
id|sbz1
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/* should be zero */
DECL|member|err2
r_int
id|err2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* second error */
DECL|member|retry
r_int
id|retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* retry flag */
DECL|member|proc_offset
r_int
r_int
id|proc_offset
suffix:semicolon
multiline_comment|/* processor-specific offset */
DECL|member|sys_offset
r_int
r_int
id|sys_offset
suffix:semicolon
multiline_comment|/* system-specific offset */
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
multiline_comment|/* machine check code */
)brace
suffix:semicolon
multiline_comment|/* Machine Check Frame for uncorrectable errors (Large format)&n; *      --- This is used to log uncorrectable errors such as&n; *          double bit ECC errors.&n; *      --- These errors are detected by both processor and systems.&n; */
DECL|struct|el_common_EV5_uncorrectable_mcheck
r_struct
id|el_common_EV5_uncorrectable_mcheck
(brace
DECL|member|shadow
r_int
r_int
id|shadow
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Shadow reg. 8-14, 25           */
DECL|member|paltemp
r_int
r_int
id|paltemp
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* PAL TEMP REGS.                 */
DECL|member|exc_addr
r_int
r_int
id|exc_addr
suffix:semicolon
multiline_comment|/* Address of excepting instruction*/
DECL|member|exc_sum
r_int
r_int
id|exc_sum
suffix:semicolon
multiline_comment|/* Summary of arithmetic traps.   */
DECL|member|exc_mask
r_int
r_int
id|exc_mask
suffix:semicolon
multiline_comment|/* Exception mask (from exc_sum). */
DECL|member|pal_base
r_int
r_int
id|pal_base
suffix:semicolon
multiline_comment|/* Base address for PALcode.      */
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
multiline_comment|/* Interrupt Status Reg.          */
DECL|member|icsr
r_int
r_int
id|icsr
suffix:semicolon
multiline_comment|/* CURRENT SETUP OF EV5 IBOX      */
DECL|member|ic_perr_stat
r_int
r_int
id|ic_perr_stat
suffix:semicolon
multiline_comment|/* I-CACHE Reg. &lt;11&gt; set Data parity&n;                                                         &lt;12&gt; set TAG parity*/
DECL|member|dc_perr_stat
r_int
r_int
id|dc_perr_stat
suffix:semicolon
multiline_comment|/* D-CACHE error Reg. Bits set to 1:&n;                                                     &lt;2&gt; Data error in bank 0&n;                                                     &lt;3&gt; Data error in bank 1&n;                                                     &lt;4&gt; Tag error in bank 0&n;                                                     &lt;5&gt; Tag error in bank 1 */
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* Effective VA of fault or miss. */
DECL|member|mm_stat
r_int
r_int
id|mm_stat
suffix:semicolon
multiline_comment|/* Holds the reason for D-stream &n;                                             fault or D-cache parity errors */
DECL|member|sc_addr
r_int
r_int
id|sc_addr
suffix:semicolon
multiline_comment|/* Address that was being accessed&n;                                             when EV5 detected Secondary cache&n;                                             failure.                 */
DECL|member|sc_stat
r_int
r_int
id|sc_stat
suffix:semicolon
multiline_comment|/* Helps determine if the error was&n;                                             TAG/Data parity(Secondary Cache)*/
DECL|member|bc_tag_addr
r_int
r_int
id|bc_tag_addr
suffix:semicolon
multiline_comment|/* Contents of EV5 BC_TAG_ADDR    */
DECL|member|ei_addr
r_int
r_int
id|ei_addr
suffix:semicolon
multiline_comment|/* Physical address of any transfer&n;                                             that is logged in EV5 EI_STAT */
DECL|member|fill_syndrome
r_int
r_int
id|fill_syndrome
suffix:semicolon
multiline_comment|/* For correcting ECC errors.     */
DECL|member|ei_stat
r_int
r_int
id|ei_stat
suffix:semicolon
multiline_comment|/* Helps identify reason of any &n;                                             processor uncorrectable error&n;                                             at its external interface.     */
DECL|member|ld_lock
r_int
r_int
id|ld_lock
suffix:semicolon
multiline_comment|/* Contents of EV5 LD_LOCK register*/
)brace
suffix:semicolon
r_extern
r_void
id|halt
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long pcbb;&t;&t;&t;&t;&bslash;&n;&t;current = (next);&t;&t;&t;&t;&bslash;&n;&t;pcbb = virt_to_phys(&amp;current-&gt;tss);&t;&t;&bslash;&n;&t;(last) = alpha_switch_to(pcbb, (prev));&t;&t;&bslash;&n;} while (0)
r_extern
r_struct
id|task_struct
op_star
id|alpha_switch_to
c_func
(paren
r_int
r_int
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|mb
mdefine_line|#define mb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb() &bslash;&n;__asm__ __volatile__(&quot;wmb&quot;: : :&quot;memory&quot;)
DECL|macro|imb
mdefine_line|#define imb() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0 #imb&quot; : : &quot;i&quot; (PAL_imb) : &quot;memory&quot;)
DECL|macro|draina
mdefine_line|#define draina() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0 #draina&quot; : : &quot;i&quot; (PAL_draina) : &quot;memory&quot;)
DECL|enum|implver_enum
r_enum
id|implver_enum
(brace
DECL|enumerator|IMPLVER_EV4
id|IMPLVER_EV4
comma
DECL|enumerator|IMPLVER_EV5
id|IMPLVER_EV5
comma
DECL|enumerator|IMPLVER_EV6
id|IMPLVER_EV6
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_GENERIC
DECL|macro|implver
mdefine_line|#define implver()&t;&t;&t;&t;&bslash;&n;({ unsigned long __implver;&t;&t;&t;&bslash;&n;   __asm__ (&quot;implver %0&quot; : &quot;=r&quot;(__implver));&t;&bslash;&n;   (enum implver_enum) __implver; })
macro_line|#else
multiline_comment|/* Try to eliminate some dead code.  */
macro_line|#ifdef CONFIG_ALPHA_EV4
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV4
macro_line|#endif
macro_line|#ifdef CONFIG_ALPHA_EV5
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV5
macro_line|#endif
macro_line|#ifdef CONFIG_ALPHA_EV6
DECL|macro|implver
mdefine_line|#define implver() IMPLVER_EV6
macro_line|#endif
macro_line|#endif
DECL|enum|amask_enum
r_enum
id|amask_enum
(brace
DECL|enumerator|AMASK_BWX
id|AMASK_BWX
op_assign
(paren
l_int|1UL
op_lshift
l_int|0
)paren
comma
DECL|enumerator|AMASK_FIX
id|AMASK_FIX
op_assign
(paren
l_int|1UL
op_lshift
l_int|1
)paren
comma
DECL|enumerator|AMASK_MAX
id|AMASK_MAX
op_assign
(paren
l_int|1UL
op_lshift
l_int|8
)paren
comma
DECL|enumerator|AMASK_PRECISE_TRAP
id|AMASK_PRECISE_TRAP
op_assign
(paren
l_int|1UL
op_lshift
l_int|9
)paren
comma
)brace
suffix:semicolon
DECL|macro|amask
mdefine_line|#define amask(mask)&t;&t;&t;&t;&t;&t;&bslash;&n;({ unsigned long __amask, __input = (mask);&t;&t;&t;&bslash;&n;   __asm__ (&quot;amask %1,%0&quot; : &quot;=r&quot;(__amask) : &quot;rI&quot;(__input));&t;&bslash;&n;   __amask; })
DECL|macro|__CALL_PAL_R0
mdefine_line|#define __CALL_PAL_R0(NAME, TYPE)&t;&t;&t;&t;&bslash;&n;static inline TYPE NAME(void)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %1 # &quot; #NAME&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;=r&quot; (__r0)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;i&quot; (PAL_ ## NAME)&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_W1
mdefine_line|#define __CALL_PAL_W1(NAME, TYPE0)&t;&t;&t;&t;&bslash;&n;static inline void NAME(TYPE0 arg0)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %1 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16)&t;&t;&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_W2
mdefine_line|#define __CALL_PAL_W2(NAME, TYPE0, TYPE1)&t;&t;&t;&bslash;&n;static inline void NAME(TYPE0 arg0, TYPE1 arg1)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;register TYPE1 __r17 __asm__(&quot;$17&quot;) = arg1;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %2 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r17)&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16), &quot;1&quot;(__r17)&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_RW1
mdefine_line|#define __CALL_PAL_RW1(NAME, RTYPE, TYPE0)&t;&t;&t;&bslash;&n;static inline RTYPE NAME(TYPE0 arg0)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register RTYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %2 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r0)&t;&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16)&t;&t;&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__CALL_PAL_RW2
mdefine_line|#define __CALL_PAL_RW2(NAME, RTYPE, TYPE0, TYPE1)&t;&t;&bslash;&n;static inline RTYPE NAME(TYPE0 arg0, TYPE1 arg1)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register RTYPE __r0 __asm__(&quot;$0&quot;);&t;&t;&t;&bslash;&n;&t;register TYPE0 __r16 __asm__(&quot;$16&quot;) = arg0;&t;&t;&bslash;&n;&t;register TYPE1 __r17 __asm__(&quot;$17&quot;) = arg1;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %3 # &quot;#NAME&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(__r16), &quot;=r&quot;(__r17), &quot;=r&quot;(__r0)&t;&t;&bslash;&n;&t;&t;: &quot;i&quot;(PAL_ ## NAME), &quot;0&quot;(__r16), &quot;1&quot;(__r17)&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&t;&bslash;&n;&t;return __r0;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|__CALL_PAL_R0
c_func
(paren
id|rdmces
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|rdps
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|rdusp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_RW1
c_func
(paren
id|swpipl
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_R0
c_func
(paren
id|whami
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W2
c_func
(paren
id|wrent
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wripir
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrkgp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrmces
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_RW2
c_func
(paren
id|wrperfmon
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrusp
comma
r_int
r_int
)paren
suffix:semicolon
id|__CALL_PAL_W1
c_func
(paren
id|wrvptptr
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;((void) swpipl(7))
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;((void) swpipl(0))
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags)&t;((flags) = rdps())
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags)&t;((flags) = swpipl(7))
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;((void) swpipl(flags))
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;&t;__save_and_cli(flags)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;__restore_flags(flags)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;__sti()
macro_line|#ifdef __SMP__
r_extern
r_int
id|global_irq_holder
suffix:semicolon
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)     (save_flags(flags), cli())
r_extern
r_void
id|__global_cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_restore_flags
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli()                   __global_cli()
DECL|macro|sti
mdefine_line|#define sti()                   __global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;((flags) = __global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)    __global_restore_flags(flags)
macro_line|#else /* __SMP__ */
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;__cli()
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;__sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;__save_flags(flags)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;__save_and_cli(flags)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;__restore_flags(flags)
macro_line|#endif /* __SMP__ */
multiline_comment|/*&n; * TB routines..&n; */
DECL|macro|__tbi
mdefine_line|#define __tbi(nr,arg,arg1...)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;) = (nr);&t;&bslash;&n;&t;register unsigned long __r17 __asm__(&quot;$17&quot;); arg;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;call_pal %3 #__tbi&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;:&quot;=r&quot; (__r16),&quot;=r&quot; (__r17)&t;&t;&t;&bslash;&n;&t;&t;:&quot;0&quot; (__r16),&quot;i&quot; (PAL_tbi) ,##arg1&t;&t;&bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;);&t;&bslash;&n;})
DECL|macro|tbi
mdefine_line|#define tbi(x,y)&t;__tbi(x,__r17=(y),&quot;1&quot; (__r17))
DECL|macro|tbisi
mdefine_line|#define tbisi(x)&t;__tbi(1,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbisd
mdefine_line|#define tbisd(x)&t;__tbi(2,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbis
mdefine_line|#define tbis(x)&t;&t;__tbi(3,__r17=(x),&quot;1&quot; (__r17))
DECL|macro|tbiap
mdefine_line|#define tbiap()&t;&t;__tbi(-1, /* no second argument */)
DECL|macro|tbia
mdefine_line|#define tbia()&t;&t;__tbi(-2, /* no second argument */)
multiline_comment|/*&n; * Give prototypes to shut up gcc.&n; */
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
id|__inline__
r_int
r_int
id|xchg_u64
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|xchg_u32
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldl_l %0,%2&bslash;n&quot;
l_string|&quot;&t;bis $31,%3,%1&bslash;n&quot;
l_string|&quot;&t;stl_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;rI&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg_u64
r_extern
id|__inline__
r_int
r_int
id|xchg_u64
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%2&bslash;n&quot;
l_string|&quot;&t;bis $31,%3,%1&bslash;n&quot;
l_string|&quot;&t;stq_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
l_string|&quot;&t;mb&bslash;n&quot;
l_string|&quot;.section .text2,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;rI&quot;
(paren
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|m
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; *&n; * This only works if the compiler isn&squot;t horribly bad at optimizing.&n; * gcc-2.5.8 reportedly can&squot;t handle this, but as that doesn&squot;t work&n; * too well on the alpha anyway..&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
id|xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;  ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
