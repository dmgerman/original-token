macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#ifdef MODVERSIONS
DECL|macro|_set_ver
macro_line|# undef _set_ver
DECL|macro|X
macro_line|# undef X
macro_line|# ifndef __GENKSYMS__
macro_line|#  ifdef MODULE
DECL|macro|_set_ver
macro_line|#    define _set_ver(sym,ver) &bslash;&n;&t;{ (void *) &amp; sym ## _R ## ver, SYMBOL_NAME_STR(sym) &quot;_R&quot; #ver }
macro_line|#  else /* !MODULE */
DECL|macro|_set_ver
macro_line|#    define _set_ver(sym,ver) &bslash;&n;&t;{ (void *) &amp; sym, SYMBOL_NAME_STR(sym) &quot;_R&quot; #ver }
macro_line|#  endif /* !MODULE */
DECL|macro|X
macro_line|#  define X(a) a
macro_line|# endif /* !__GENKSYMS__ */
macro_line|#else /* !MODVERSIONS */
DECL|macro|X
macro_line|# define X(sym) { (void *) &amp; sym, SYMBOL_NAME_STR(sym)}
macro_line|#endif /* MODVERSIONS */
multiline_comment|/*&n; * Some symbols always need to be unversioned.  This includes&n; * compiler generated calls to functions.&n; */
DECL|macro|XNOVERS
mdefine_line|#define XNOVERS(sym) { (void *) &amp; sym, SYMBOL_NAME_STR(sym)}
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
