macro_line|#ifdef MODVERSIONS /* MODVERSIONS */
DECL|macro|_set_ver
macro_line|#undef _set_ver
macro_line|#if defined(MODULE) &amp;&amp; !defined(__GENKSYMS__)
DECL|macro|_set_ver
mdefine_line|#define _set_ver(sym,vers) sym ## _R ## vers
macro_line|#else
DECL|macro|_set_ver
mdefine_line|#define _set_ver(a,b) a
macro_line|#endif
macro_line|#endif /* MODVERSIONS */
DECL|macro|X
macro_line|#undef X
DECL|macro|EMPTY
macro_line|#undef EMPTY
multiline_comment|/* mark end of table, last entry above ended with a comma! */
(brace
(paren
r_void
op_star
)paren
l_int|0
comma
(paren
r_char
op_star
)paren
l_int|0
)brace
)brace
comma
multiline_comment|/* no module refs, insmod will take care of that instead! */
(brace
(brace
(paren
r_struct
id|module
op_star
)paren
l_int|0
comma
(paren
r_struct
id|module_ref
op_star
)paren
l_int|0
)brace
)brace
eof
