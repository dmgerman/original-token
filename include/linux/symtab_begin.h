macro_line|#ifdef CONFIG_MODVERSIONS /* CONFIG_MODVERSIONS */
DECL|macro|_set_ver
macro_line|#undef _set_ver
DECL|macro|X
macro_line|#undef X
macro_line|#ifndef __GENKSYMS__
macro_line|#ifdef MODULE
DECL|macro|_set_ver
mdefine_line|#define _set_ver(sym,ver) { (void *) &amp; sym ## _R ## ver, &quot;_&quot; #sym &quot;_R&quot; #ver }
macro_line|#else /* MODULE */
DECL|macro|_set_ver
mdefine_line|#define _set_ver(sym,ver) { (void *) &amp; sym, &quot;_&quot; #sym &quot;_R&quot; #ver }
macro_line|#endif /* MODULE */
DECL|macro|X
mdefine_line|#define X(a) a
macro_line|#endif /* __GENKSYMS__ */
macro_line|#else /* CONFIG_MODVERSIONS */
DECL|macro|X
mdefine_line|#define X(sym) { (void *) &amp; sym, &quot;_&quot; #sym }
macro_line|#endif /* CONFIG_MODVERSIONS */
DECL|macro|EMPTY
mdefine_line|#define EMPTY {0,0}
l_int|0
comma
l_int|0
comma
l_int|0
comma
(brace
eof
