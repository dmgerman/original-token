macro_line|#ifndef _ASM_I386_UNISTD_H_
DECL|macro|_ASM_I386_UNISTD_H_
mdefine_line|#define _ASM_I386_UNISTD_H_
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name)); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,atype,a) &bslash;&n;type name(atype a) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,atype,a,btype,b) &bslash;&n;type name(atype a,btype b) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,atype,a,btype,b,ctype,c) &bslash;&n;type name(atype a,btype b,ctype c) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b)),&quot;d&quot; ((long)(c))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,atype,a,btype,b,ctype,c,dtype,d) &bslash;&n;type name (atype a, btype b, ctype c, dtype d) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b)), &bslash;&n;&t;  &quot;d&quot; ((long)(c)),&quot;S&quot; ((long)(d))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) &bslash;&n;type name (atype a,btype b,ctype c,dtype d,etype e) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(a)),&quot;c&quot; ((long)(b)), &bslash;&n;&t;  &quot;d&quot; ((long)(c)),&quot;S&quot; ((long)(d)),&quot;D&quot; ((long)(e))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#endif /* _ASM_I386_UNISTD_H_ */
eof
