DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode() &bslash;&n;__asm__ __volatile__ (&quot;movl %%esp,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $0x17&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl %%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushfl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $0x0f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;pushl $1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;iret&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tmovl $0x17,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%ds&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%es&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%fs&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mov %%ax,%%gs&quot; &bslash;&n;&t;:::&quot;ax&quot;)
DECL|macro|sti
mdefine_line|#define sti() __asm__ __volatile__ (&quot;sti&quot;::)
DECL|macro|cli
mdefine_line|#define cli() __asm__ __volatile__ (&quot;cli&quot;::)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;::)
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;iret&quot;::)
DECL|macro|_set_gate
mdefine_line|#define _set_gate(gate_addr,type,dpl,addr) &bslash;&n;__asm__ __volatile__ (&quot;movw %%dx,%%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %0,%%dx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%eax,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movl %%edx,%2&quot; &bslash;&n;&t;:: &quot;i&quot; ((short) (0x8000+(dpl&lt;&lt;13)+(type&lt;&lt;8))), &bslash;&n;&t;&quot;m&quot; (*((char *) (gate_addr))), &bslash;&n;&t;&quot;m&quot; (*(4+(char *) (gate_addr))), &bslash;&n;&t;&quot;d&quot; ((char *) (addr)),&quot;a&quot; (0x00080000) &bslash;&n;&t;:&quot;ax&quot;,&quot;dx&quot;)
DECL|macro|set_intr_gate
mdefine_line|#define set_intr_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],14,0,addr)
DECL|macro|set_trap_gate
mdefine_line|#define set_trap_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,0,addr)
DECL|macro|set_system_gate
mdefine_line|#define set_system_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,3,addr)
DECL|macro|_set_seg_desc
mdefine_line|#define _set_seg_desc(gate_addr,type,dpl,base,limit) {&bslash;&n;&t;*(gate_addr) = ((base) &amp; 0xff000000) | &bslash;&n;&t;&t;(((base) &amp; 0x00ff0000)&gt;&gt;16) | &bslash;&n;&t;&t;((limit) &amp; 0xf0000) | &bslash;&n;&t;&t;((dpl)&lt;&lt;13) | &bslash;&n;&t;&t;(0x00408000) | &bslash;&n;&t;&t;((type)&lt;&lt;8); &bslash;&n;&t;*((gate_addr)+1) = (((base) &amp; 0x0000ffff)&lt;&lt;16) | &bslash;&n;&t;&t;((limit) &amp; 0x0ffff); }
DECL|macro|_set_tssldt_desc
mdefine_line|#define _set_tssldt_desc(n,addr,limit,type) &bslash;&n;__asm__ __volatile__ (&quot;movw $&quot; #limit &quot;,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %%ax,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%al,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $&quot; type &quot;,%4&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb $0x00,%5&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%ah,%6&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%eax&quot; &bslash;&n;&t;::&quot;a&quot; (addr+0xc0000000), &quot;m&quot; (*(n)), &quot;m&quot; (*(n+2)), &quot;m&quot; (*(n+4)), &bslash;&n;&t; &quot;m&quot; (*(n+5)), &quot;m&quot; (*(n+6)), &quot;m&quot; (*(n+7)) &bslash;&n;&t;)
DECL|macro|set_tss_desc
mdefine_line|#define set_tss_desc(n,addr) _set_tssldt_desc(((char *) (n)),((int)(addr)),231,&quot;0x89&quot;)
DECL|macro|set_ldt_desc
mdefine_line|#define set_ldt_desc(n,addr) _set_tssldt_desc(((char *) (n)),((int)(addr)),23,&quot;0x82&quot;)
eof
