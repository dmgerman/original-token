macro_line|#ifndef _ASM_I386_UNISTD_H_
DECL|macro|_ASM_I386_UNISTD_H_
mdefine_line|#define _ASM_I386_UNISTD_H_
multiline_comment|/* XXX - _foo needs to be __foo, while __NR_bar could be _NR_bar. */
DECL|macro|_syscall0
mdefine_line|#define _syscall0(type,name) &bslash;&n;type name(void) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name)); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall1
mdefine_line|#define _syscall1(type,name,type1,arg1) &bslash;&n;type name(type1 arg1) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall2
mdefine_line|#define _syscall2(type,name,type1,arg1,type2,arg2) &bslash;&n;type name(type1 arg1,type2 arg2) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2))); &bslash;&n;if (__res &gt;= 0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno = -__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall3
mdefine_line|#define _syscall3(type,name,type1,arg1,type2,arg2,type3,arg3) &bslash;&n;type name(type1 arg1,type2 arg2,type3 arg3) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;&t;  &quot;d&quot; ((long)(arg3))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
DECL|macro|_syscall4
mdefine_line|#define _syscall4(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) &bslash;&n;type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;S&quot; ((long)(arg4))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;} 
DECL|macro|_syscall5
mdefine_line|#define _syscall5(type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, &bslash;&n;&t;  type5,arg5) &bslash;&n;type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) &bslash;&n;{ &bslash;&n;long __res; &bslash;&n;__asm__ volatile (&quot;int $0x80&quot; &bslash;&n;&t;: &quot;=a&quot; (__res) &bslash;&n;&t;: &quot;0&quot; (__NR_##name),&quot;b&quot; ((long)(arg1)),&quot;c&quot; ((long)(arg2)), &bslash;&n;&t;  &quot;d&quot; ((long)(arg3)),&quot;S&quot; ((long)(arg4)),&quot;D&quot; ((long)(arg5))); &bslash;&n;if (__res&gt;=0) &bslash;&n;&t;return (type) __res; &bslash;&n;errno=-__res; &bslash;&n;return -1; &bslash;&n;}
macro_line|#endif /* _ASM_I386_UNISTD_H_ */
eof
