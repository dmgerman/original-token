macro_line|#ifndef _SOUNDMODULE_H
DECL|macro|_SOUNDMODULE_H
mdefine_line|#define _SOUNDMODULE_H
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/notifier.h&gt;
r_extern
r_struct
id|notifier_block
op_star
id|sound_locker
suffix:semicolon
r_extern
r_void
id|sound_notifier_chain_register
c_func
(paren
r_struct
id|notifier_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|lock_depth
suffix:semicolon
macro_line|#ifdef SOUND_CORE
DECL|macro|SOUND_INC_USE_COUNT
mdefine_line|#define SOUND_INC_USE_COUNT&t;do { notifier_call_chain(&amp;sound_locker, 1, 0); lock_depth++; } while(0);
DECL|macro|SOUND_DEC_USE_COUNT
mdefine_line|#define SOUND_DEC_USE_COUNT&t;do { notifier_call_chain(&amp;sound_locker, 0, 0); lock_depth--; } while(0);
macro_line|#else
DECL|macro|SOUND_LOCK
mdefine_line|#define SOUND_LOCK&t;&t;sound_notifier_chain_register(&amp;sound_notifier); 
DECL|macro|SOUND_LOCK_END
mdefine_line|#define SOUND_LOCK_END&t;&t;notifier_chain_unregister(&amp;sound_locker, &amp;sound_notifier)
DECL|function|my_notifier_call
r_static
r_int
id|my_notifier_call
c_func
(paren
r_struct
id|notifier_block
op_star
id|b
comma
r_int
r_int
id|foo
comma
r_void
op_star
id|bar
)paren
(brace
r_if
c_cond
(paren
id|foo
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|sound_notifier
r_static
r_struct
id|notifier_block
id|sound_notifier
op_assign
(brace
id|my_notifier_call
comma
(paren
r_void
op_star
)paren
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
