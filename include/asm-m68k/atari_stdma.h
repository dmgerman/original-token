macro_line|#ifndef _atari_stdma_h
DECL|macro|_atari_stdma_h
mdefine_line|#define _atari_stdma_h
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/***************************** Prototypes *****************************/
r_void
id|stdma_lock
c_func
(paren
id|isrfunc
id|isr
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_void
id|stdma_release
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|stdma_others_waiting
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|stdma_islocked
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|stdma_locked_by
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|stdma_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/************************* End of Prototypes **************************/
macro_line|#endif  /* _atari_stdma_h */
eof