macro_line|#ifndef __ALPHA_SYSTEM_H
DECL|macro|__ALPHA_SYSTEM_H
mdefine_line|#define __ALPHA_SYSTEM_H
macro_line|#include &lt;asm/pal.h&gt;&t;/* for backwards compatibility... */
multiline_comment|/*&n; * System defines.. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.&n; */
multiline_comment|/*&n; * We leave one page for the initial stack page, and one page for&n; * the initial process structure. Also, the console eats 3 MB for&n; * the initial bootloader (one of which we can reclaim later).&n; * With a few other pages for various reasons, we&squot;ll use an initial&n; * load address of 0xfffffc0000310000UL&n; */
DECL|macro|BOOT_PCB
mdefine_line|#define BOOT_PCB&t;0x20000000
DECL|macro|BOOT_ADDR
mdefine_line|#define BOOT_ADDR&t;0x20000000
multiline_comment|/* Remove when official MILO sources have ELF support: */
DECL|macro|BOOT_SIZE
mdefine_line|#define BOOT_SIZE&t;(16*1024)
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START&t;0xfffffc0000300000
DECL|macro|SWAPPER_PGD
mdefine_line|#define SWAPPER_PGD&t;0xfffffc0000300000
DECL|macro|INIT_STACK
mdefine_line|#define INIT_STACK&t;0xfffffc0000302000
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT&t;0xfffffc0000304000
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;0xfffffc0000308000
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;0xfffffc000030A000
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;0xfffffc0000310000
multiline_comment|/* Remove when official MILO sources have ELF support: */
DECL|macro|START_SIZE
mdefine_line|#define START_SIZE&t;(2*1024*1024)
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
id|wrent
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wrkgp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wrusp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|rdusp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|rdmces
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wrmces
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|whami
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wripir
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|halt
mdefine_line|#define halt() __asm__ __volatile__ (&quot;call_pal %0&quot; : : &quot;i&quot; (PAL_halt) : &quot;memory&quot;)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) do { &bslash;&n;&t;current = next; &bslash;&n;&t;alpha_switch_to((unsigned long) &amp;current-&gt;tss - IDENT_ADDR); &bslash;&n;} while (0)
r_extern
r_void
id|alpha_switch_to
c_func
(paren
r_int
r_int
id|pctxp
)paren
suffix:semicolon
DECL|macro|mb
mdefine_line|#define mb() &bslash;&n;__asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb() &bslash;&n;__asm__ __volatile__(&quot;wmb&quot;: : :&quot;memory&quot;)
DECL|macro|imb
mdefine_line|#define imb() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0&quot; : : &quot;i&quot; (PAL_imb) : &quot;memory&quot;)
DECL|macro|draina
mdefine_line|#define draina() &bslash;&n;__asm__ __volatile__ (&quot;call_pal %0&quot; : : &quot;i&quot; (PAL_draina) : &quot;memory&quot;)
DECL|macro|call_pal1
mdefine_line|#define call_pal1(palno,arg) &bslash;&n;({ &bslash;&n;&t;register unsigned long __r0 __asm__(&quot;$0&quot;); &bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;); __r16 = arg; &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %3&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__r0),&quot;=r&quot; (__r16) &bslash;&n;&t;&t;:&quot;1&quot; (__r16),&quot;i&quot; (palno) &bslash;&n;&t;&t;:&quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;&t;__r0; &bslash;&n;})
DECL|macro|getipl
mdefine_line|#define getipl() &bslash;&n;({ &bslash;&n;&t;register unsigned long r0 __asm__(&quot;$0&quot;); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %1&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (r0) &bslash;&n;&t;&t;:&quot;i&quot; (PAL_rdps) &bslash;&n;&t;&t;:&quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;&t;r0; &bslash;&n;})
macro_line|#ifdef THE_OLD_VERSION
DECL|macro|setipl
mdefine_line|#define setipl(ipl) &bslash;&n;do { &bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;) = (ipl); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %2&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__r16) &bslash;&n;&t;&t;:&quot;0&quot; (__r16),&quot;i&quot; (PAL_swpipl) &bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;} while (0)
DECL|macro|swpipl
mdefine_line|#define swpipl(ipl) &bslash;&n;({ &bslash;&n;&t;register unsigned long __r0 __asm__(&quot;$0&quot;); &bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;) = (ipl); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %3&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__r0),&quot;=r&quot; (__r16) &bslash;&n;&t;&t;:&quot;1&quot; (__r16),&quot;i&quot; (PAL_swpipl) &bslash;&n;&t;&t;:&quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;&t;__r0; &bslash;&n;})
macro_line|#else
DECL|macro|setipl
mdefine_line|#define setipl(ipl) &bslash;&n;do { &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;mov %0,$16; call_pal %1&quot; &bslash;&n;&t;&t;: /* no output */ &bslash;&n;&t;&t;:&quot;i,r&quot; (ipl), &quot;i,i&quot; (PAL_swpipl) &bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;} while (0)
DECL|macro|swpipl
mdefine_line|#define swpipl(ipl) &bslash;&n;({ &bslash;&n;&t;register unsigned long __r0 __asm__(&quot;$0&quot;); &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;mov %0,$16; call_pal %1&quot; &bslash;&n;&t;&t;: /* no output (bound to the template) */ &bslash;&n;&t;&t;: &quot;i,r&quot; (ipl), &quot;i,i&quot; (PAL_swpipl) &bslash;&n;&t;&t;: &quot;$0&quot;, &quot;$1&quot;, &quot;$16&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;, &quot;memory&quot;); &bslash;&n;&t;__r0; &bslash;&n;})
macro_line|#endif
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;setipl(7)
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;setipl(0)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags)&t;do { (flags) = getipl(); } while (0)
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(flags)&t;do { (flags) = swpipl(7); } while (0)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;setipl(flags)
macro_line|#ifdef __SMP__
r_extern
r_int
r_char
id|global_irq_holder
suffix:semicolon
DECL|macro|save_flags
mdefine_line|#define save_flags(x) &bslash;&n;do { &bslash;&n;&t;(x) = ((global_irq_holder == (unsigned char) smp_processor_id()) &bslash;&n;&t;&t;? 1 &bslash;&n;&t;&t;: ((getipl() &amp; 7) ? 2 : 0)); &bslash;&n;} while (0)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)   do { save_flags(flags); cli(); } while(0)
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
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)    __global_restore_flags(flags)
macro_line|#else /* __SMP__ */
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;setipl(7)
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;setipl(0)
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { (flags) = getipl(); } while (0)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;do { (flags) = swpipl(7); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;setipl(flags)
macro_line|#endif /* __SMP__ */
multiline_comment|/*&n; * TB routines..&n; */
DECL|macro|__tbi
mdefine_line|#define __tbi(nr,arg,arg1...) do { &bslash;&n;&t;register unsigned long __r16 __asm__(&quot;$16&quot;) = (nr); &bslash;&n;&t;register unsigned long __r17 __asm__(&quot;$17&quot;); arg; &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&t;&quot;call_pal %3&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__r16),&quot;=r&quot; (__r17) &bslash;&n;&t;&t;:&quot;0&quot; (__r16),&quot;i&quot; (PAL_tbi) ,##arg1 &bslash;&n;&t;&t;:&quot;$0&quot;, &quot;$1&quot;, &quot;$22&quot;, &quot;$23&quot;, &quot;$24&quot;, &quot;$25&quot;); &bslash;&n;} while (0)
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
l_string|&quot;&t;bis %3,%3,%1&bslash;n&quot;
l_string|&quot;&t;stl_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
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
l_string|&quot;r&quot;
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
l_string|&quot;&t;bis %3,%3,%1&bslash;n&quot;
l_string|&quot;&t;stq_c %1,%2&bslash;n&quot;
l_string|&quot;&t;beq %1,2f&bslash;n&quot;
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
l_string|&quot;r&quot;
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
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; *&n; * This only works if the compiler isn&squot;t horribly bad at optimizing.&n; * gcc-2.5.8 reportedly can&squot;t handle this, but as that doesn&squot;t work&n; * too well on the alpha anyway..&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__xchg
r_static
id|__inline__
r_int
r_int
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
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
