macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/segment.h&gt;
DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode() &bslash;&n;__asm__ __volatile__ (&quot;movl %%esp,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushfl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;iret&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovl %0,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%gs&quot; &bslash;&n;&t;: /* no outputs */ :&quot;i&quot; (USER_DS), &quot;i&quot; (USER_CS):&quot;ax&quot;)
DECL|macro|sti
mdefine_line|#define sti() __asm__ __volatile__ (&quot;sti&quot;: : :&quot;memory&quot;)
DECL|macro|cli
mdefine_line|#define cli() __asm__ __volatile__ (&quot;cli&quot;: : :&quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
multiline_comment|/*&n; * Clear and set &squot;TS&squot; bit respectively&n; */
DECL|macro|clts
mdefine_line|#define clts() __asm__ __volatile__ (&quot;clts&quot;)
DECL|macro|stts
mdefine_line|#define stts() &bslash;&n;__asm__ __volatile__ ( &bslash;&n;&t;&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orl $8,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%%cr0&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;:&quot;ax&quot;)
DECL|function|tas
r_extern
r_inline
r_int
id|tas
c_func
(paren
r_char
op_star
id|m
)paren
(brace
r_char
id|res
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;xchgb %0,%1&quot;
suffix:colon
l_string|&quot;=q&quot;
(paren
id|res
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0x1
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
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
macro_line|#endif
eof
