macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#ifdef __KERNEL__
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* one of the stranger aspects of C forward declarations.. */
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
id|next
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * We do most of the task switching in C, but we need&n; * to do the EIP/ESP switch in assembly..&n; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) do {&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long eax, edx, ecx;&t;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;pushl %%ebx&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushl %%esi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushl %%edi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;pushl %%ebp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;movl %%esp,%0&bslash;n&bslash;t&quot;&t;/* save ESP */&t;&t;&bslash;&n;&t;&t;     &quot;movl %5,%%esp&bslash;n&bslash;t&quot;&t;/* restore ESP */&t;&bslash;&n;&t;&t;     &quot;movl $1f,%1&bslash;n&bslash;t&quot;&t;&t;/* save EIP */&t;&t;&bslash;&n;&t;&t;     &quot;pushl %6&bslash;n&bslash;t&quot;&t;&t;/* restore EIP */&t;&bslash;&n;&t;&t;     &quot;jmp __switch_to&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;1:&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%ebp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%edi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%esi&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     &quot;popl %%ebx&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     :&quot;=m&quot; (prev-&gt;tss.esp),&quot;=m&quot; (prev-&gt;tss.eip),&t;&bslash;&n;&t;&t;      &quot;=a&quot; (eax), &quot;=d&quot; (edx), &quot;=c&quot; (ecx)&t;&t;&bslash;&n;&t;&t;     :&quot;m&quot; (next-&gt;tss.esp),&quot;m&quot; (next-&gt;tss.eip),&t;&t;&bslash;&n;&t;&t;      &quot;a&quot; (prev), &quot;d&quot; (next)); &t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_set_base
mdefine_line|#define _set_base(addr,base) do { unsigned long __pr; &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dh,%3&quot; &bslash;&n;&t;:&quot;=&amp;d&quot; (__pr) &bslash;&n;&t;:&quot;m&quot; (*((addr)+2)), &bslash;&n;&t; &quot;m&quot; (*((addr)+4)), &bslash;&n;&t; &quot;m&quot; (*((addr)+7)), &bslash;&n;         &quot;0&quot; (base) &bslash;&n;        ); } while(0)
DECL|macro|_set_limit
mdefine_line|#define _set_limit(addr,limit) do { unsigned long __lr; &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %2,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andb $0xf0,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orb %%dh,%%dl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%2&quot; &bslash;&n;&t;:&quot;=&amp;d&quot; (__lr) &bslash;&n;&t;:&quot;m&quot; (*(addr)), &bslash;&n;&t; &quot;m&quot; (*((addr)+6)), &bslash;&n;&t; &quot;0&quot; (limit) &bslash;&n;        ); } while(0)
DECL|macro|set_base
mdefine_line|#define set_base(ldt,base) _set_base( ((char *)&amp;(ldt)) , (base) )
DECL|macro|set_limit
mdefine_line|#define set_limit(ldt,limit) _set_limit( ((char *)&amp;(ldt)) , ((limit)-1)&gt;&gt;12 )
DECL|function|_get_base
r_static
r_inline
r_int
r_int
id|_get_base
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_int
r_int
id|__base
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movb %3,%%dh&bslash;n&bslash;t&quot;
l_string|&quot;movb %2,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;shll $16,%%edx&bslash;n&bslash;t&quot;
l_string|&quot;movw %1,%%dx&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|__base
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|2
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|4
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|7
)paren
)paren
)paren
suffix:semicolon
r_return
id|__base
suffix:semicolon
)brace
DECL|macro|get_base
mdefine_line|#define get_base(ldt) _get_base( ((char *)&amp;(ldt)) )
multiline_comment|/*&n; * Load a segment. Fall back on loading the zero&n; * segment if something goes wrong..&n; */
DECL|macro|loadsegment
mdefine_line|#define loadsegment(seg,value)&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %0,%%&quot; #seg &quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;pushl $0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;popl %%&quot; #seg &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.align 4&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.long 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: :&quot;m&quot; (*(unsigned int *)&amp;(value)))
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|read_cr0
mdefine_line|#define read_cr0() ({ &bslash;&n;&t;unsigned int __dummy; &bslash;&n;&t;__asm__( &bslash;&n;&t;&t;&quot;movl %%cr0,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;:&quot;=r&quot; (__dummy)); &bslash;&n;&t;__dummy; &bslash;&n;})
DECL|macro|write_cr0
mdefine_line|#define write_cr0(x) &bslash;&n;&t;__asm__(&quot;movl %0,%%cr0&quot;: :&quot;r&quot; (x));
DECL|macro|stts
mdefine_line|#define stts() write_cr0(8 | read_cr0())
macro_line|#endif&t;/* __KERNEL__ */
DECL|function|get_limit
r_static
r_inline
r_int
r_int
id|get_limit
c_func
(paren
r_int
r_int
id|segment
)paren
(brace
r_int
r_int
id|__limit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lsll %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__limit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|segment
)paren
)paren
suffix:semicolon
r_return
id|__limit
op_plus
l_int|1
suffix:semicolon
)brace
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|struct|__xchg_dummy
DECL|member|a
r_struct
id|__xchg_dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__xg
mdefine_line|#define __xg(x) ((struct __xchg_dummy *)(x))
multiline_comment|/*&n; * Note: no &quot;lock&quot; prefix even on SMP: xchg always implies lock anyway&n; */
DECL|function|__xchg
r_static
r_inline
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
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
l_int|1
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;xchgb %b0,%1&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;xchgw %w0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
c_func
(paren
l_string|&quot;xchgl %0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;0&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; *&n; * For now, &quot;wmb()&quot; doesn&squot;t actually do anything, as all&n; * intel CPU&squot;s follow what intel calls a *Processor Order*,&n; * in which all writes are seen in the program order even&n; * outside the CPU.&n; *&n; * I expect future intel CPU&squot;s to have a weaker ordering,&n; * but I&squot;d also expect them to finally get their act together&n; * and add some real memory barriers if so.&n; */
DECL|macro|mb
mdefine_line|#define mb() &t;__asm__ __volatile__ (&quot;lock; addl $0,0(%%esp)&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;__asm__ __volatile__ (&quot;&quot;: : :&quot;memory&quot;)
multiline_comment|/* interrupt control.. */
DECL|macro|__sti
mdefine_line|#define __sti() __asm__ __volatile__ (&quot;sti&quot;: : :&quot;memory&quot;)
DECL|macro|__cli
mdefine_line|#define __cli() __asm__ __volatile__ (&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x) &bslash;&n;__asm__ __volatile__(&quot;pushfl ; popl %0&quot;:&quot;=g&quot; (x): /* no input */ :&quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) &bslash;&n;__asm__ __volatile__(&quot;pushl %0 ; popfl&quot;: /* no output */ :&quot;g&quot; (x):&quot;memory&quot;)
macro_line|#ifdef __SMP__
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
)paren
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli() __global_cli()
DECL|macro|sti
mdefine_line|#define sti() __global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) ((x)=__global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __global_restore_flags(x)
macro_line|#else
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
macro_line|#endif
multiline_comment|/*&n; * disable hlt during certain critical i/o operations&n; */
DECL|macro|HAVE_DISABLE_HLT
mdefine_line|#define HAVE_DISABLE_HLT
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
