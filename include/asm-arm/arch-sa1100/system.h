multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/system.h&n; *&n; * Copyright (c) 1999 Nicolas Pitre &lt;nico@visuaide.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SA1100_VICTOR
DECL|macro|arch_reset
mdefine_line|#define arch_reset( x ) {&t;&t;&t;&t;&t;&bslash;&n;&t;/* switch off power supply */&t;&t;&t;&t;&bslash;&n;&t;mdelay(2000); &t;&t;&t;&t;&t;&t;&bslash;&n;&t;GPCR = GPIO_GPIO23;&t;&t;&t;&t;&t;&bslash;&n;&t;while(1);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|arch_reset
mdefine_line|#define arch_reset(x) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ volatile (&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;mcr&t;p15, 0, %0, c1, c0&t;@ MMU off&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;mov&t;pc, #0&bslash;n&quot; : : &quot;r&quot; (cpu_reset()) : &quot;cc&quot;);&t;&bslash;&n;&t;}
macro_line|#endif
multiline_comment|/* Enter SA1100 idle mode (see data sheet sec 9.5).&n; * It seems that the wait-on-interrupt just hang the CPU forever if it&squot;s&n; * on the end of a cache line.  Workaround: we force an explicit alignment&n; * before it.&n; */
DECL|macro|arch_do_idle
mdefine_line|#define arch_do_idle() &bslash;&n;&t;do { &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&quot;&t;mcr&t;p15, 0, %0, c15, c2, 2&t;@ Disable clock switching &bslash;n&quot; &bslash;&n;&quot;&t;ldr&t;%0, [%0]&t;&t;@ Must perform a non-cached access &bslash;n&quot; &bslash;&n;&quot;&t;b&t;1f&t;&t;&t;@ Seems we must align the next &bslash;n&quot; &bslash;&n;&quot;&t;.align 5&t;&t;&t;@ instruction on a cache line &bslash;n&quot; &bslash;&n;&quot;1:&t;mcr&t;p15, 0, %0, c15, c8, 2&t;@ Wait for interrupts &bslash;n&quot; &bslash;&n;&quot;&t;mcr&t;p15, 0, %0, c15, c1, 2&t;@ Reenable clock switching &bslash;n&quot; &bslash;&n;&t;: : &quot;r&quot; (&amp;ICIP) : &quot;cc&quot; ); &bslash;&n;&t;} while (0)
eof
