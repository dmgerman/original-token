multiline_comment|/*&n; * Access to machine-specific registers (available on 586 and better only)&n; * Note: the rd* operations modify the parameters directly (without using&n; * pointer indirection), this allows gcc to optimize better&n; */
DECL|macro|rdmsr
mdefine_line|#define rdmsr(msr,val1,val2) &bslash;&n;       __asm__ __volatile__(&quot;rdmsr&quot; &bslash;&n;&t;&t;&t;    : &quot;=a&quot; (val1), &quot;=d&quot; (val2) &bslash;&n;&t;&t;&t;    : &quot;c&quot; (msr))
DECL|macro|wrmsr
mdefine_line|#define wrmsr(msr,val1,val2) &bslash;&n;     __asm__ __volatile__(&quot;wrmsr&quot; &bslash;&n;&t;&t;&t;  : /* no outputs */ &bslash;&n;&t;&t;&t;  : &quot;c&quot; (msr), &quot;a&quot; (val1), &quot;d&quot; (val2))
DECL|macro|rdtsc
mdefine_line|#define rdtsc(low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdtsc&quot; : &quot;=a&quot; (low), &quot;=d&quot; (high))
DECL|macro|rdtscl
mdefine_line|#define rdtscl(low) &bslash;&n;     __asm__ __volatile__ (&quot;rdtsc&quot; : &quot;=a&quot; (low) : : &quot;edx&quot;)
DECL|macro|rdtscll
mdefine_line|#define rdtscll(val) &bslash;&n;     __asm__ __volatile__ (&quot;rdtsc&quot; : &quot;=A&quot; (val))
DECL|macro|rdpmc
mdefine_line|#define rdpmc(counter,low,high) &bslash;&n;     __asm__ __volatile__(&quot;rdpmc&quot; &bslash;&n;&t;&t;&t;  : &quot;=a&quot; (low), &quot;=d&quot; (high) &bslash;&n;&t;&t;&t;  : &quot;c&quot; (counter))
eof
