DECL|macro|ALLOW_SELECT
mdefine_line|#define ALLOW_SELECT
DECL|macro|NO_INLINE_ASM
macro_line|#undef NO_INLINE_ASM
DECL|macro|SHORT_BANNERS
mdefine_line|#define SHORT_BANNERS
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef MODULE
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef MODVERSIONS
macro_line|#include &lt;linux/modversions.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;sys/kd.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
DECL|typedef|snd_rw_buf
r_typedef
r_char
id|snd_rw_buf
suffix:semicolon
DECL|typedef|ioctl_arg
r_typedef
id|caddr_t
id|ioctl_arg
suffix:semicolon
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
DECL|struct|snd_wait
r_struct
id|snd_wait
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|sound_alloc_dma
c_func
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_int
id|sound_open_dma
c_func
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_void
id|sound_free_dma
c_func
(paren
r_int
id|chn
)paren
suffix:semicolon
r_extern
r_void
id|sound_close_dma
c_func
(paren
r_int
id|chn
)paren
suffix:semicolon
DECL|macro|RUNTIME_DMA_ALLOC
mdefine_line|#define RUNTIME_DMA_ALLOC
r_extern
id|caddr_t
id|sound_mem_blocks
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
id|sound_num_blocks
suffix:semicolon
DECL|typedef|sound_os_info
r_typedef
r_int
id|sound_os_info
suffix:semicolon
DECL|macro|PSEUDO_DMA_AUTOINIT
macro_line|#undef PSEUDO_DMA_AUTOINIT
eof
