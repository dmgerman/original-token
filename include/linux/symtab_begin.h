macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#ifdef MODVERSIONS
DECL|macro|_set_ver
macro_line|# undef _set_ver
DECL|macro|X
macro_line|# undef X
multiline_comment|/*&n; * These two macros _will_ get enough arguments from the X* macros&n; * since &quot;sym&quot; expands to &quot;symaddr, symstr&quot; from the #define in *.ver&n; */
DECL|macro|_basic_version
macro_line|# define _basic_version(symaddr,symstr)  symaddr, symstr
DECL|macro|_alias_version
macro_line|# define _alias_version(really,symaddr,symstr)  (void *) &amp; really , symstr
macro_line|# ifndef __GENKSYMS__
macro_line|#  ifdef MODULE
DECL|macro|_set_ver
macro_line|#    define _set_ver(sym,ver) &bslash;&n;&t;(void *) &amp; sym ## _R ## ver, SYMBOL_NAME_STR(sym) &quot;_R&quot; #ver
macro_line|#  else /* !MODULE */
DECL|macro|_set_ver
macro_line|#    define _set_ver(sym,ver) &bslash;&n;&t;(void *) &amp; sym, SYMBOL_NAME_STR(sym) &quot;_R&quot; #ver
macro_line|#  endif /* !MODULE */
DECL|macro|X
macro_line|#  define X(sym) { _basic_version(sym) }
multiline_comment|/*&n; * For _really_ stacked modules:&n; *&n; * Use &quot;Xalias(local_symbol, symbol_from_other_module)&quot;&n; * to make subsequent modules really use &quot;local_symbol&quot;&n; * when they think that they are using &quot;symbol_from_other_module&quot;&n; *&n; * The &quot;aliasing&quot; module can still use &quot;symbol_from_other_module&quot;,&n; * but can now replace and/or modify the behaviour of that symbol.&n; */
DECL|macro|Xalias
macro_line|#  define Xalias(really,sym) { _alias_version(really,sym) }
macro_line|# endif /* !__GENKSYMS__ */
macro_line|#else /* !MODVERSIONS */
DECL|macro|X
macro_line|# define X(sym) { (void *) &amp; sym, SYMBOL_NAME_STR(sym)}
DECL|macro|Xalias
macro_line|# define Xalias(really,sym) { (void *) &amp; really, SYMBOL_NAME_STR(sym)}
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
