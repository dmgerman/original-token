multiline_comment|/*&n; *  NOTE!!! memcpy(dest,src,n) assumes ds=es=normal data segment. This&n; *  goes for all kernel functions (ds=es=kernel space, fs=local data,&n; *  gs=null), as well as for all well-behaving user programs (ds=es=&n; *  user data space). This is NOT a bug, as any user program that changes&n; *  es deserves to die if it isn&squot;t careful.&n; */
DECL|macro|memcpy
mdefine_line|#define memcpy(dest,src,n) ({ &bslash;&n;void * _res = dest; &bslash;&n;__asm__ (&quot;cld;rep;movsb&quot; &bslash;&n;&t;::&quot;D&quot; ((long)(_res)),&quot;S&quot; ((long)(src)),&quot;c&quot; ((long) (n)) &bslash;&n;&t;:&quot;di&quot;,&quot;si&quot;,&quot;cx&quot;); &bslash;&n;_res; &bslash;&n;})
eof
