macro_line|#ifndef _STDARG_H
DECL|macro|_STDARG_H
mdefine_line|#define _STDARG_H
DECL|typedef|va_list
r_typedef
r_char
op_star
id|va_list
suffix:semicolon
multiline_comment|/* Amount of space required in an argument list for an arg of type TYPE.&n;   TYPE may alternatively be an expression whose type is used.  */
DECL|macro|__va_rounded_size
mdefine_line|#define __va_rounded_size(TYPE)  &bslash;&n;  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))
macro_line|#ifndef __sparc__
DECL|macro|va_start
mdefine_line|#define va_start(AP, LASTARG) &t;&t;&t;&t;&t;&t;&bslash;&n; (AP = ((char *) &amp;(LASTARG) + __va_rounded_size (LASTARG)))
macro_line|#else
DECL|macro|va_start
mdefine_line|#define va_start(AP, LASTARG) &t;&t;&t;&t;&t;&t;&bslash;&n; (__builtin_saveregs (),&t;&t;&t;&t;&t;&t;&bslash;&n;  AP = ((char *) &amp;(LASTARG) + __va_rounded_size (LASTARG)))
macro_line|#endif
r_void
id|va_end
(paren
id|va_list
)paren
suffix:semicolon
multiline_comment|/* Defined in gnulib */
DECL|macro|va_end
mdefine_line|#define va_end(AP)
DECL|macro|va_arg
mdefine_line|#define va_arg(AP, TYPE)&t;&t;&t;&t;&t;&t;&bslash;&n; (AP += __va_rounded_size (TYPE),&t;&t;&t;&t;&t;&bslash;&n;  *((TYPE *) (AP - __va_rounded_size (TYPE))))
macro_line|#endif /* _STDARG_H */
eof
