multiline_comment|/*&n; *&t;OS Specific settings for Linux&n; * &n; * Copyright by Hannu Savolainen 1993&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
DECL|macro|ALLOW_SELECT
mdefine_line|#define ALLOW_SELECT
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
macro_line|#include &lt;linux/soundcard.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|typedef|snd_rw_buf
r_typedef
r_char
id|snd_rw_buf
suffix:semicolon
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(d, s, o, c)&t;memcpy_fromfs((d), &amp;((s)[o]), (c))
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER(d, o, s, c)&t;memcpy_tofs(&amp;((d)[o]), (s), (c))
DECL|macro|IOCTL_FROM_USER
mdefine_line|#define IOCTL_FROM_USER(d, s, o, c)&t;memcpy_fromfs((d), &amp;((s)[o]), (c))
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(d, o, s, c)&t;memcpy_tofs(&amp;((d)[o]), (s), (c))
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target, addr, offs)&t;target = get_fs_byte(&amp;((addr)[offs]))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target, addr, offs)&t;target = get_fs_word(&amp;((addr)[offs]))
DECL|macro|GET_WORD_FROM_USER
mdefine_line|#define GET_WORD_FROM_USER(target, addr, offs)&t;target = get_fs_long((long*)&amp;((addr)[offs]))
DECL|macro|PUT_WORD_TO_USER
mdefine_line|#define PUT_WORD_TO_USER(addr, offs, data)&t;put_fs_long(data, (long*)&amp;((addr)[offs]))
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;&t;&t;get_fs_long((long *)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg, ret)&t;&t;snd_ioctl_return((int *)arg, ret)
DECL|struct|snd_wait
r_struct
id|snd_wait
(brace
DECL|member|mode
DECL|member|aborting
r_int
id|mode
suffix:semicolon
r_int
id|aborting
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEFINE_WAIT_QUEUE
mdefine_line|#define DEFINE_WAIT_QUEUE(name, flag) static struct wait_queue *name = NULL; &bslash;&n;&t;static volatile struct snd_wait flag = {0}
DECL|macro|DEFINE_WAIT_QUEUES
mdefine_line|#define DEFINE_WAIT_QUEUES(name, flag) static struct wait_queue *name = {NULL}; &bslash;&n;&t;static volatile struct snd_wait flag = {{0}}
DECL|macro|RESET_WAIT_QUEUE
mdefine_line|#define RESET_WAIT_QUEUE(q, f) {f.aborting = 0;f.mode = WK_NONE;}
DECL|macro|PROCESS_ABORTING
mdefine_line|#define PROCESS_ABORTING(q, f) (f.aborting | (current-&gt;signal &amp; ~current-&gt;blocked))
DECL|macro|SET_ABORT_FLAG
mdefine_line|#define SET_ABORT_FLAG(q, f) f.aborting = 1
DECL|macro|TIMED_OUT
mdefine_line|#define TIMED_OUT(q, f) (f.mode &amp; WK_TIMEOUT)
DECL|macro|DO_SLEEP
mdefine_line|#define DO_SLEEP(q, f, time_limit)&t;&bslash;&n;&t;{ unsigned long tl;&bslash;&n;&t;  if (time_limit) tl = current-&gt;timeout = jiffies + (time_limit); &bslash;&n;&t;     else tl = 0xffffffff; &bslash;&n;&t;  f.mode = WK_SLEEP;interruptible_sleep_on(&amp;q); &bslash;&n;&t;  if (!(f.mode &amp; WK_WAKEUP)) &bslash;&n;&t;   { &bslash;&n;&t;     if (current-&gt;signal &amp; ~current-&gt;blocked) &bslash;&n;&t;        f.aborting = 1; &bslash;&n;&t;     else &bslash;&n;&t;        if (jiffies &gt;= tl) f.mode |= WK_TIMEOUT; &bslash;&n;&t;   } &bslash;&n;&t;  f.mode &amp;= ~WK_SLEEP; &bslash;&n;&t;}
DECL|macro|SOMEONE_WAITING
mdefine_line|#define SOMEONE_WAITING(q, f) (f.mode &amp; WK_SLEEP)
DECL|macro|WAKE_UP
mdefine_line|#define WAKE_UP(q, f)&t;&t;&t;{f.mode = WK_WAKEUP;wake_up(&amp;q);}
DECL|macro|ALLOC_DMA_CHN
mdefine_line|#define ALLOC_DMA_CHN(chn)&t;&t;request_dma(chn)
DECL|macro|RELEASE_DMA_CHN
mdefine_line|#define RELEASE_DMA_CHN(chn)&t;&t;free_dma(chn)
DECL|macro|GET_TIME
mdefine_line|#define GET_TIME()&t;&t;&t;jiffies
DECL|macro|RELEASE_IRQ
mdefine_line|#define RELEASE_IRQ&t;&t;&t;free_irq
DECL|macro|RET_ERROR
mdefine_line|#define RET_ERROR(err)&t;&t;&t;-err
multiline_comment|/* DISABLE_INTR is used to disable interrupts.&n;   These macros store the current flags to the (unsigned long) variable given&n;   as a parameter. RESTORE_INTR returns the interrupt ebable bit to state&n;   before DISABLE_INTR or ENABLE_INTR */
DECL|macro|DISABLE_INTR
mdefine_line|#define DISABLE_INTR(flags)&t;__asm__ __volatile__(&quot;pushfl ; popl %0 ; cli&quot;:&quot;=r&quot; (flags));
DECL|macro|RESTORE_INTR
mdefine_line|#define RESTORE_INTR(flags)&t;__asm__ __volatile__(&quot;pushl %0 ; popfl&quot;: &bslash;&n;&t;&t;&t;&t;&t;&t;&t;:&quot;r&quot; (flags));
multiline_comment|/* &n;   KERNEL_MALLOC() allocates requested number of memory  and &n;   KERNEL_FREE is used to free it. &n;   These macros are never called from interrupt, in addition the&n;   nbytes will never be more than 4096 bytes. Generally the driver&n;   will allocate memory in blocks of 4k. If the kernel has just a&n;   page level memory allocation, 4K can be safely used as the size&n;   (the nbytes parameter can be ignored).&n;*/
DECL|macro|KERNEL_MALLOC
mdefine_line|#define KERNEL_MALLOC(nbytes)&t;kmalloc(nbytes, GFP_KERNEL)
DECL|macro|KERNEL_FREE
mdefine_line|#define KERNEL_FREE(addr)&t;kfree(addr)
multiline_comment|/*&n; * The macro PERMANENT_MALLOC(typecast, mem_ptr, size, linux_ptr)&n; * returns size bytes of&n; * (kernel virtual) memory which will never get freed by the driver.&n; * This macro is called only during boot. The linux_ptr is a linux specific&n; * parameter which should be ignored in other operating systems.&n; * The mem_ptr is a pointer variable where the macro assigns pointer to the&n; * memory area. The type is the type of the mem_ptr.&n; */
DECL|macro|PERMANENT_MALLOC
mdefine_line|#define PERMANENT_MALLOC(typecast, mem_ptr, size, linux_ptr) &bslash;&n;  {mem_ptr = (typecast)linux_ptr; &bslash;&n;   linux_ptr += (size);}
multiline_comment|/*&n; * The macro DEFINE_TIMER defines variables for the ACTIVATE_TIMER if&n; * required. The name is the variable/name to be used and the proc is&n; * the procedure to be called when the timer expires.&n; */
DECL|macro|DEFINE_TIMER
mdefine_line|#define DEFINE_TIMER(name, proc) &bslash;&n;  static struct timer_list name = &bslash;&n;  {NULL, 0, 0, 0, proc}
multiline_comment|/*&n; * The ACTIVATE_TIMER requests system to call &squot;proc&squot; after &squot;time&squot; ticks.&n; */
DECL|macro|ACTIVATE_TIMER
mdefine_line|#define ACTIVATE_TIMER(name, proc, time) &bslash;&n;  {name.expires = time; &bslash;&n;  add_timer (&amp;name);}
DECL|macro|INB
mdefine_line|#define INB&t;inb
DECL|macro|OUTB
mdefine_line|#define OUTB&t;outb
eof
