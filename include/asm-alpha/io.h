macro_line|#ifndef __ALPHA_IO_H
DECL|macro|__ALPHA_IO_H
mdefine_line|#define __ALPHA_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef mb
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__(&quot;mb&quot;: : :&quot;memory&quot;)
macro_line|#endif
multiline_comment|/*&n; * There are different version of the alpha motherboards: the&n; * &quot;interesting&quot; (read: slightly braindead) Jensen type hardware&n; * and the PCI version&n; */
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/lca.h&gt;&t;&t;/* get chip-specific definitions */
macro_line|#else
macro_line|#include &lt;asm/jensen.h&gt;
macro_line|#endif
macro_line|#endif
eof
