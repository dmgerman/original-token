macro_line|#ifndef _ASM_IA64_CACHE_H
DECL|macro|_ASM_IA64_CACHE_H
mdefine_line|#define _ASM_IA64_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/* Bytes per L1 (data) cache line.  */
DECL|macro|LOG_L1_CACHE_BYTES
mdefine_line|#define LOG_L1_CACHE_BYTES&t;6
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;(1 &lt;&lt; LOG_L1_CACHE_BYTES)
macro_line|#ifdef CONFIG_SMP
DECL|macro|SMP_LOG_CACHE_BYTES
macro_line|# define SMP_LOG_CACHE_BYTES&t;LOG_L1_CACHE_BYTES
DECL|macro|SMP_CACHE_BYTES
macro_line|# define SMP_CACHE_BYTES&t;L1_CACHE_BYTES
macro_line|#else
multiline_comment|/*&n;   * The &quot;aligned&quot; directive can only _increase_ alignment, so this is&n;   * safe and provides an easy way to avoid wasting space on a&n;   * uni-processor:&n;   */
DECL|macro|SMP_LOG_CACHE_BYTES
macro_line|# define SMP_LOG_CACHE_BYTES&t;3
DECL|macro|SMP_CACHE_BYTES
macro_line|# define SMP_CACHE_BYTES&t;(1 &lt;&lt; 3)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_CACHE_H */
eof
