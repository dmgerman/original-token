macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/*&n; * Entry into gdt where to find first TSS. GDT layout:&n; *   0 - nul&n; *   1 - kernel code segment&n; *   2 - kernel data segment&n; *   3 - user code segment&n; *   4 - user data segment&n; * ...&n; *   8 - TSS #0&n; *   9 - LDT #0&n; *  10 - TSS #1&n; *  11 - LDT #1&n; */
DECL|macro|FIRST_TSS_ENTRY
mdefine_line|#define FIRST_TSS_ENTRY 8
DECL|macro|FIRST_LDT_ENTRY
mdefine_line|#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
DECL|macro|_TSS
mdefine_line|#define _TSS(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_TSS_ENTRY&lt;&lt;3))
DECL|macro|_LDT
mdefine_line|#define _LDT(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_LDT_ENTRY&lt;&lt;3))
DECL|macro|load_TR
mdefine_line|#define load_TR(n) __asm__(&quot;ltr %%ax&quot;: /* no output */ :&quot;a&quot; (_TSS(n)))
DECL|macro|load_ldt
mdefine_line|#define load_ldt(n) __asm__(&quot;lldt %%ax&quot;: /* no output */ :&quot;a&quot; (_LDT(n)))
DECL|macro|store_TR
mdefine_line|#define store_TR(n) &bslash;&n;__asm__(&quot;str %%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subl %2,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;shrl $4,%%eax&quot; &bslash;&n;&t;:&quot;=a&quot; (n) &bslash;&n;&t;:&quot;0&quot; (0),&quot;i&quot; (FIRST_TSS_ENTRY&lt;&lt;3))
multiline_comment|/* This special macro can be used to load a debugging register */
DECL|macro|loaddebug
mdefine_line|#define loaddebug(tsk,register) &bslash;&n;&t;&t;__asm__(&quot;movl %0,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&quot;movl %%edx,%%db&quot; #register &quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;: /* no output */ &bslash;&n;&t;&t;&t;:&quot;m&quot; (tsk-&gt;debugreg[register]) &bslash;&n;&t;&t;&t;:&quot;dx&quot;);
multiline_comment|/*&n; *&t;switch_to(n) should switch tasks to task nr n, first&n; * checking that n isn&squot;t the current task, in which case it does nothing.&n; * This also clears the TS-flag if the task we switched to has used&n; * the math co-processor latest.&n; *&n; * It also reloads the debug regs if necessary..&n; */
macro_line|#ifdef __SMP__
multiline_comment|/*&n;&t; *&t;Keep the lock depth straight. If we switch on an interrupt from&n;&t; *&t;kernel-&gt;user task we need to lose a depth, and if we switch the&n;&t; *&t;other way we need to gain a depth. Same layer switches come out&n;&t; *&t;the same.&n;&t; *&n;&t; *&t;We spot a switch in user mode because the kernel counter is the&n;&t; *&t;same as the interrupt counter depth. (We never switch during the&n;&t; *&t;message/invalidate IPI).&n;&t; *&n;&t; *&t;We fsave/fwait so that an exception goes off at the right time&n;&t; *&t;(as a call from the fsave or fwait in effect) rather than to&n;&t; *&t;the wrong process.&n;&t; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) do { &bslash;&n;&t;cli();&bslash;&n;&t;if(prev-&gt;flags&amp;PF_USEDFPU) &bslash;&n;&t;{ &bslash;&n;&t;&t;__asm__ __volatile__(&quot;fnsave %0&quot;:&quot;=m&quot; (prev-&gt;tss.i387.hard)); &bslash;&n;&t;&t;__asm__ __volatile__(&quot;fwait&quot;); &bslash;&n;&t;&t;prev-&gt;flags&amp;=~PF_USEDFPU;&t; &bslash;&n;&t;} &bslash;&n;&t;prev-&gt;lock_depth=syscall_count; &bslash;&n;&t;kernel_counter+=next-&gt;lock_depth-prev-&gt;lock_depth; &bslash;&n;&t;syscall_count=next-&gt;lock_depth; &bslash;&n;__asm__(&quot;pushl %%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl &quot;SYMBOL_NAME_STR(apic_reg)&quot;,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl 0x20(%%edx), %%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;shrl $22,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;and  $0x3C,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%ecx,&quot;SYMBOL_NAME_STR(current_set)&quot;(,%%edx)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;popl %%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;ljmp %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sti&bslash;n&bslash;t&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;m&quot; (*(((char *)&amp;next-&gt;tss.tr)-4)), &bslash;&n;&t; &quot;c&quot; (next)); &bslash;&n;&t;/* Now maybe reload the debug registers */ &bslash;&n;&t;if(prev-&gt;debugreg[7]){ &bslash;&n;&t;&t;loaddebug(prev,0); &bslash;&n;&t;&t;loaddebug(prev,1); &bslash;&n;&t;&t;loaddebug(prev,2); &bslash;&n;&t;&t;loaddebug(prev,3); &bslash;&n;&t;&t;loaddebug(prev,6); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#else
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) do { &bslash;&n;__asm__(&quot;movl %2,&quot;SYMBOL_NAME_STR(current_set)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;ljmp %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;cmpl %1,&quot;SYMBOL_NAME_STR(last_task_used_math)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;clts&bslash;n&quot; &bslash;&n;&t;&quot;1:&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;:&quot;m&quot; (*(((char *)&amp;next-&gt;tss.tr)-4)), &bslash;&n;&t; &quot;r&quot; (prev), &quot;r&quot; (next)); &bslash;&n;&t;/* Now maybe reload the debug registers */ &bslash;&n;&t;if(prev-&gt;debugreg[7]){ &bslash;&n;&t;&t;loaddebug(prev,0); &bslash;&n;&t;&t;loaddebug(prev,1); &bslash;&n;&t;&t;loaddebug(prev,2); &bslash;&n;&t;&t;loaddebug(prev,3); &bslash;&n;&t;&t;loaddebug(prev,6); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|_set_base
mdefine_line|#define _set_base(addr,base) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dh,%2&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;m&quot; (*((addr)+2)), &bslash;&n;&t; &quot;m&quot; (*((addr)+4)), &bslash;&n;&t; &quot;m&quot; (*((addr)+7)), &bslash;&n;&t; &quot;d&quot; (base) &bslash;&n;&t;:&quot;dx&quot;)
DECL|macro|_set_limit
mdefine_line|#define _set_limit(addr,limit) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %1,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andb $0xf0,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orb %%dh,%%dl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;m&quot; (*(addr)), &bslash;&n;&t; &quot;m&quot; (*((addr)+6)), &bslash;&n;&t; &quot;d&quot; (limit) &bslash;&n;&t;:&quot;dx&quot;)
DECL|macro|set_base
mdefine_line|#define set_base(ldt,base) _set_base( ((char *)&amp;(ldt)) , base )
DECL|macro|set_limit
mdefine_line|#define set_limit(ldt,limit) _set_limit( ((char *)&amp;(ldt)) , (limit-1)&gt;&gt;12 )
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
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|stts
mdefine_line|#define stts() &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orl $8,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%%cr0&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;:&quot;ax&quot;)
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
l_string|&quot;=&amp;q&quot;
(paren
id|x
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
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
l_string|&quot;=&amp;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
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
l_string|&quot;=&amp;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|sti
mdefine_line|#define sti() __asm__ __volatile__ (&quot;sti&quot;: : :&quot;memory&quot;)
DECL|macro|cli
mdefine_line|#define cli() __asm__ __volatile__ (&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|save_flags
mdefine_line|#define save_flags(x) &bslash;&n;__asm__ __volatile__(&quot;pushfl ; popl %0&quot;:&quot;=r&quot; (x): /* no input */ :&quot;memory&quot;)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) &bslash;&n;__asm__ __volatile__(&quot;pushl %0 ; popfl&quot;: /* no output */ :&quot;r&quot; (x):&quot;memory&quot;)
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;iret&quot;: : :&quot;memory&quot;)
DECL|macro|_set_gate
mdefine_line|#define _set_gate(gate_addr,type,dpl,addr) &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %2,%%dx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%edx,%1&quot; &bslash;&n;&t;:&quot;=m&quot; (*((long *) (gate_addr))), &bslash;&n;&t; &quot;=m&quot; (*(1+(long *) (gate_addr))) &bslash;&n;&t;:&quot;i&quot; ((short) (0x8000+(dpl&lt;&lt;13)+(type&lt;&lt;8))), &bslash;&n;&t; &quot;d&quot; ((char *) (addr)),&quot;a&quot; (KERNEL_CS &lt;&lt; 16) &bslash;&n;&t;:&quot;ax&quot;,&quot;dx&quot;)
DECL|macro|set_intr_gate
mdefine_line|#define set_intr_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],14,0,addr)
DECL|macro|set_trap_gate
mdefine_line|#define set_trap_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,0,addr)
DECL|macro|set_system_gate
mdefine_line|#define set_system_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,3,addr)
DECL|macro|set_call_gate
mdefine_line|#define set_call_gate(a,addr) &bslash;&n;&t;_set_gate(a,12,3,addr)
DECL|macro|_set_seg_desc
mdefine_line|#define _set_seg_desc(gate_addr,type,dpl,base,limit) {&bslash;&n;&t;*((gate_addr)+1) = ((base) &amp; 0xff000000) | &bslash;&n;&t;&t;(((base) &amp; 0x00ff0000)&gt;&gt;16) | &bslash;&n;&t;&t;((limit) &amp; 0xf0000) | &bslash;&n;&t;&t;((dpl)&lt;&lt;13) | &bslash;&n;&t;&t;(0x00408000) | &bslash;&n;&t;&t;((type)&lt;&lt;8); &bslash;&n;&t;*(gate_addr) = (((base) &amp; 0x0000ffff)&lt;&lt;16) | &bslash;&n;&t;&t;((limit) &amp; 0x0ffff); }
DECL|macro|_set_tssldt_desc
mdefine_line|#define _set_tssldt_desc(n,addr,limit,type) &bslash;&n;__asm__ __volatile__ (&quot;movw $&quot; #limit &quot;,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %%ax,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%al,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $&quot; type &quot;,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $0x00,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%ah,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;:&quot;a&quot; (addr+0xc0000000), &quot;m&quot; (*(n)), &quot;m&quot; (*(n+2)), &quot;m&quot; (*(n+4)), &bslash;&n;&t; &quot;m&quot; (*(n+5)), &quot;m&quot; (*(n+6)), &quot;m&quot; (*(n+7)) &bslash;&n;&t;)
DECL|macro|set_tss_desc
mdefine_line|#define set_tss_desc(n,addr) _set_tssldt_desc(((char *) (n)),((int)(addr)),235,&quot;0x89&quot;)
DECL|macro|set_ldt_desc
mdefine_line|#define set_ldt_desc(n,addr,size) &bslash;&n;&t;_set_tssldt_desc(((char *) (n)),((int)(addr)),((size &lt;&lt; 3) - 1),&quot;0x82&quot;)
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
