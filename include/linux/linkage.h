macro_line|#ifndef _LINUX_LINKAGE_H
DECL|macro|_LINUX_LINKAGE_H
mdefine_line|#define _LINUX_LINKAGE_H
macro_line|#ifdef __cplusplus
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage extern &quot;C&quot;
macro_line|#else
DECL|macro|asmlinkage
mdefine_line|#define asmlinkage
macro_line|#endif
DECL|macro|SYMBOL_NAME_STR
mdefine_line|#define SYMBOL_NAME_STR(X) #X
DECL|macro|SYMBOL_NAME
mdefine_line|#define SYMBOL_NAME(X) X
macro_line|#ifdef __STDC__
DECL|macro|SYMBOL_NAME_LABEL
mdefine_line|#define SYMBOL_NAME_LABEL(X) X##:
macro_line|#else
DECL|macro|SYMBOL_NAME_LABEL
mdefine_line|#define SYMBOL_NAME_LABEL(X) X/**/:
macro_line|#endif
macro_line|#if !defined(__i486__) &amp;&amp; !defined(__i586__)
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 4,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 4,0x90&quot;
macro_line|#else  /* __i486__/__i586__ */
DECL|macro|__ALIGN
mdefine_line|#define __ALIGN .align 16,0x90
DECL|macro|__ALIGN_STR
mdefine_line|#define __ALIGN_STR &quot;.align 16,0x90&quot;
macro_line|#endif /* __i486__/__i586__ */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|ALIGN
mdefine_line|#define ALIGN __ALIGN
DECL|macro|ALIGN_STRING
mdefine_line|#define ALIGN_STRING __ALIGN_STRING
DECL|macro|ENTRY
mdefine_line|#define ENTRY(name) &bslash;&n;  .globl SYMBOL_NAME(name); &bslash;&n;  ALIGN; &bslash;&n;  SYMBOL_NAME_LABEL(name)
macro_line|#endif
macro_line|#endif
eof
