DECL|macro|outb
mdefine_line|#define outb(value,port) &bslash;&n;__asm__ (&quot;outb %%al,%%dx&quot;::&quot;a&quot; (value),&quot;d&quot; (port))
DECL|macro|inb
mdefine_line|#define inb(port) ({ &bslash;&n;unsigned char _v; &bslash;&n;__asm__ volatile (&quot;inb %%dx,%%al&quot;:&quot;=a&quot; (_v):&quot;d&quot; (port)); &bslash;&n;_v; &bslash;&n;})
DECL|macro|outb_p
mdefine_line|#define outb_p(value,port) &bslash;&n;__asm__ (&quot;outb %%al,%%dx&bslash;n&quot; &bslash;&n;&t;&t;&quot;&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&t;&quot;1:&quot;::&quot;a&quot; (value),&quot;d&quot; (port))
DECL|macro|inb_p
mdefine_line|#define inb_p(port) ({ &bslash;&n;unsigned char _v; &bslash;&n;__asm__ volatile (&quot;inb %%dx,%%al&bslash;n&quot; &bslash;&n;&t;&quot;&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tjmp 1f&bslash;n&quot; &bslash;&n;&t;&quot;1:&quot;:&quot;=a&quot; (_v):&quot;d&quot; (port)); &bslash;&n;_v; &bslash;&n;})
eof
