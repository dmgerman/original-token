multiline_comment|/*&n; *    sound/pnp.c - Temporary kludge for PnP soundcards.&n; *&n; *      Copyright by Hannu Savolainen 1997.&n; *&n; *      This file is just a temporary solution to be used with&n; *      PnP soundcards until final kernel PnP support gets ready.&n; *      The code contained in this file is largely untested and&n; *      may cause failures in some systems. In particular it will&n; *      cause troubles with other PnP ISA cards such as network cards.&n; *      This file is also incompatible with (future) PnP support in kernel.&n; *&n; *      For the above reasons I don&squot;t want this file to be widely distributed.&n; *      You have permission to use this file with this particular sound driver&n; *      and only for your own evaluation purposes. Any other use of this file&n; *      or parts of it requires written permission by the author.&n; */
r_extern
r_int
id|pnp_trace
suffix:semicolon
DECL|variable|pnp_trace_io
r_int
id|pnp_trace_io
op_assign
l_int|0
suffix:semicolon
DECL|macro|UDELAY
mdefine_line|#define UDELAY(x) udelay(x)
macro_line|#ifdef TEST_PNP
macro_line|#include &quot;pnp.h&quot;
macro_line|#include &lt;malloc.h&gt;
macro_line|#include &lt;stdio.h&gt;
DECL|macro|printk
mdefine_line|#define printk printf
DECL|macro|MALLOC
mdefine_line|#define MALLOC(sz) malloc(sz)
DECL|variable|res
r_int
r_char
id|res
(braket
l_int|10000
)braket
suffix:semicolon
DECL|variable|rp
r_int
id|rp
suffix:semicolon
macro_line|#else
macro_line|#include &quot;sound_config.h&quot;
macro_line|#endif
eof
