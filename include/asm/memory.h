multiline_comment|/*&n; *  NOTE!!! memcpy(dest,src,n) assumes ds=es=normal data segment. This&n; *  goes for all kernel functions (ds=es=kernel space, fs=local data,&n; *  gs=null), as well as for all well-behaving user programs (ds=es=&n; *  user data space). This is NOT a bug, as any user program that changes&n; *  es deserves to die if it isn&squot;t careful.&n; */
macro_line|#if 0
mdefine_line|#define memcpy(dest,src,n) ({ &bslash;&n;void * _res = dest; &bslash;&n;__asm__ __volatile__ (&quot;cld;rep;movsb&quot; &bslash;&n;&t;::&quot;D&quot; ((long)(_res)),&quot;S&quot; ((long)(src)),&quot;c&quot; ((long) (n)) &bslash;&n;&t;:&quot;di&quot;,&quot;si&quot;,&quot;cx&quot;); &bslash;&n;_res; &bslash;&n;})
macro_line|#else
multiline_comment|/* this is basically memcpy_tofs.  It should be faster.&n;   I&squot;ve reorder it.  This should be a little faster. -RAB */
DECL|macro|memcpy
mdefine_line|#define memcpy(dest, src, n) f_memcpy(dest, src, n)
DECL|function|f_memcpy
r_extern
r_inline
r_void
op_star
id|f_memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cld&bslash;n&bslash;t&quot;
l_string|&quot;movl %%edx, %%ecx&bslash;n&bslash;t&quot;
l_string|&quot;shrl $2,%%ecx&bslash;n&bslash;t&quot;
l_string|&quot;rep ; movsl&bslash;n&bslash;t&quot;
l_string|&quot;testb $1,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
l_string|&quot;movsb&bslash;n&quot;
l_string|&quot;1:&bslash;ttestb $2,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;je 2f&bslash;n&bslash;t&quot;
l_string|&quot;movsw&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
op_scope_resolution
l_string|&quot;d&quot;
(paren
id|n
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|to
)paren
comma
l_string|&quot;S&quot;
(paren
(paren
r_int
)paren
id|from
)paren
suffix:colon
l_string|&quot;cx&quot;
comma
l_string|&quot;di&quot;
comma
l_string|&quot;si&quot;
)paren
suffix:semicolon
r_return
(paren
id|to
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
