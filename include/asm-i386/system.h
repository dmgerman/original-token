macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * Entry into gdt where to find first TSS. GDT layout:&n; *   0 - null&n; *   1 - not used&n; *   2 - kernel code segment&n; *   3 - kernel data segment&n; *   4 - user code segment&n; *   5 - user data segment&n; *   6 - not used&n; *   7 - not used&n; *   8 - APM BIOS support&n; *   9 - APM BIOS support&n; *  10 - APM BIOS support&n; *  11 - APM BIOS support&n; *  12 - TSS #0&n; *  13 - LDT #0&n; *  14 - TSS #1&n; *  15 - LDT #1&n; */
DECL|macro|FIRST_TSS_ENTRY
mdefine_line|#define FIRST_TSS_ENTRY 12
DECL|macro|FIRST_LDT_ENTRY
mdefine_line|#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
DECL|macro|_TSS
mdefine_line|#define _TSS(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_TSS_ENTRY&lt;&lt;3))
DECL|macro|_LDT
mdefine_line|#define _LDT(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_LDT_ENTRY&lt;&lt;3))
DECL|macro|load_TR
mdefine_line|#define load_TR(n) __asm__ __volatile__(&quot;ltr %%ax&quot;: /* no output */ :&quot;a&quot; (_TSS(n)))
DECL|macro|load_ldt
mdefine_line|#define load_ldt(n) __asm__ __volatile__(&quot;lldt %%ax&quot;: /* no output */ :&quot;a&quot; (_LDT(n)))
DECL|macro|store_TR
mdefine_line|#define store_TR(n) &bslash;&n;__asm__(&quot;str %%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subl %2,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;shrl $4,%%eax&quot; &bslash;&n;&t;:&quot;=a&quot; (n) &bslash;&n;&t;:&quot;0&quot; (0),&quot;i&quot; (FIRST_TSS_ENTRY&lt;&lt;3))
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
mdefine_line|#define _set_base(addr,base) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dh,%2&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;m&quot; (*((addr)+2)), &bslash;&n;&t; &quot;m&quot; (*((addr)+4)), &bslash;&n;&t; &quot;m&quot; (*((addr)+7)), &bslash;&n;&t; &quot;d&quot; (base) &bslash;&n;&t;:&quot;dx&quot;)
DECL|macro|_set_limit
mdefine_line|#define _set_limit(addr,limit) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %1,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andb $0xf0,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orb %%dh,%%dl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;m&quot; (*(addr)), &bslash;&n;&t; &quot;m&quot; (*((addr)+6)), &bslash;&n;&t; &quot;d&quot; (limit) &bslash;&n;&t;:&quot;dx&quot;)
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
mdefine_line|#define loadsegment(seg,value)&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl %0,%%&quot; #seg &quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;3:&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;pushl $0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;popl %%&quot; #seg &quot;&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;jmp 2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;.align 4&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.long 1b,3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&bslash;&n;&t;&t;: :&quot;m&quot; (*(unsigned int *)&amp;(value)))
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|stts
mdefine_line|#define stts() &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orl $8,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%%cr0&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;:&quot;ax&quot;)
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
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; */
DECL|macro|mb
mdefine_line|#define mb() &t;__asm__ __volatile__ (&quot;lock; addl $0,0(%%esp)&quot;: : :&quot;memory&quot;)
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
DECL|macro|_set_gate
mdefine_line|#define _set_gate(gate_addr,type,dpl,addr) &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %2,%%dx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%edx,%1&quot; &bslash;&n;&t;:&quot;=m&quot; (*((long *) (gate_addr))), &bslash;&n;&t; &quot;=m&quot; (*(1+(long *) (gate_addr))) &bslash;&n;&t;:&quot;i&quot; ((short) (0x8000+(dpl&lt;&lt;13)+(type&lt;&lt;8))), &bslash;&n;&t; &quot;d&quot; ((char *) (addr)),&quot;a&quot; (__KERNEL_CS &lt;&lt; 16) &bslash;&n;&t;:&quot;ax&quot;,&quot;dx&quot;)
DECL|macro|set_intr_gate
mdefine_line|#define set_intr_gate(n,addr) &bslash;&n;&t;_set_gate(idt+(n),14,0,addr)
DECL|macro|set_trap_gate
mdefine_line|#define set_trap_gate(n,addr) &bslash;&n;&t;_set_gate(idt+(n),15,0,addr)
DECL|macro|set_system_gate
mdefine_line|#define set_system_gate(n,addr) &bslash;&n;&t;_set_gate(idt+(n),15,3,addr)
DECL|macro|set_call_gate
mdefine_line|#define set_call_gate(a,addr) &bslash;&n;&t;_set_gate(a,12,3,addr)
DECL|macro|_set_seg_desc
mdefine_line|#define _set_seg_desc(gate_addr,type,dpl,base,limit) {&bslash;&n;&t;*((gate_addr)+1) = ((base) &amp; 0xff000000) | &bslash;&n;&t;&t;(((base) &amp; 0x00ff0000)&gt;&gt;16) | &bslash;&n;&t;&t;((limit) &amp; 0xf0000) | &bslash;&n;&t;&t;((dpl)&lt;&lt;13) | &bslash;&n;&t;&t;(0x00408000) | &bslash;&n;&t;&t;((type)&lt;&lt;8); &bslash;&n;&t;*(gate_addr) = (((base) &amp; 0x0000ffff)&lt;&lt;16) | &bslash;&n;&t;&t;((limit) &amp; 0x0ffff); }
DECL|macro|_set_tssldt_desc
mdefine_line|#define _set_tssldt_desc(n,addr,limit,type) &bslash;&n;__asm__ __volatile__ (&quot;movw %3,0(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %%ax,2(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%al,4(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %4,5(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $0,6(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%ah,7(%2)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&quot; &bslash;&n;&t;: &quot;=m&quot;(*(n)) : &quot;a&quot; (addr), &quot;r&quot;(n), &quot;ir&quot;(limit), &quot;i&quot;(type))
DECL|macro|set_tss_desc
mdefine_line|#define set_tss_desc(n,addr) &bslash;&n;&t;_set_tssldt_desc(((char *) (n)),((int)(addr)),235,0x89)
DECL|macro|set_ldt_desc
mdefine_line|#define set_ldt_desc(n,addr,size) &bslash;&n;&t;_set_tssldt_desc(((char *) (n)),((int)(addr)),((size &lt;&lt; 3) - 1),0x82)
multiline_comment|/*&n; * This is the ldt that every process will get unless we need&n; * something other than this.&n; */
r_extern
r_struct
id|desc_struct
id|default_ldt
suffix:semicolon
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
