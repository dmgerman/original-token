multiline_comment|/*&n; *  arch/m68k/q40/config.c&n; *&n; * originally based on:&n; *&n; *  linux/bvme/config.c&n; *&n; *  Copyright (C) 1993 Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/q40_master.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
r_extern
r_void
id|fd_floppy_eject
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fd_floppy_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|q40_process_int
(paren
r_int
id|level
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|q40_sys_default_handler
(braket
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* added just for debugging */
r_extern
r_void
id|q40_init_IRQ
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_free_irq
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|q40_get_irq_list
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|q40_enable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|q40_disable_irq
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
r_void
id|q40_get_model
c_func
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_static
r_int
id|q40_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|q40_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|q40_sched_init
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|q40_keyb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|q40_kbdrate
(paren
r_struct
id|kbd_repeat
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|q40_gettimeoffset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_gettod
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
suffix:semicolon
r_extern
r_int
id|q40_hwclk
(paren
r_int
comma
r_struct
id|hwclk_time
op_star
)paren
suffix:semicolon
r_extern
r_int
id|q40_set_clock_mmss
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|q40_reset
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|q40_waitbut
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|q40_set_vectors
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|kd_mksound
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|q40_mksound
c_func
(paren
r_int
r_int
multiline_comment|/*freq*/
comma
r_int
r_int
multiline_comment|/*ticks*/
)paren
suffix:semicolon
r_extern
r_char
op_star
id|saved_command_line
suffix:semicolon
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
r_static
r_void
id|q40_mem_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|b
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|variable|ql_ticks
r_static
r_int
id|ql_ticks
op_assign
l_int|0
suffix:semicolon
DECL|variable|sound_ticks
r_static
r_int
id|sound_ticks
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_char
id|bcd2bin
(paren
r_int
r_char
id|b
)paren
suffix:semicolon
r_static
r_int
r_char
id|bin2bcd
(paren
r_int
r_char
id|b
)paren
suffix:semicolon
DECL|function|q40_wait_key
r_static
r_int
(def_block
id|q40_wait_key
c_func
(paren
r_struct
id|console
op_star
id|co
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)def_block
DECL|variable|q40_console_driver
r_static
r_struct
id|console
id|q40_console_driver
op_assign
(brace
l_string|&quot;debug&quot;
comma
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* device */
id|q40_wait_key
comma
multiline_comment|/* wait_key */
l_int|NULL
comma
multiline_comment|/* unblank */
l_int|NULL
comma
multiline_comment|/* setup */
id|CON_PRINTBUFFER
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* Save tick handler routine pointer, will point to do_timer() in&n; * kernel/sched.c */
multiline_comment|/* static void (*tick_handler)(int, void *, struct pt_regs *); */
multiline_comment|/* early debugging function:*/
r_extern
r_char
op_star
id|q40_mem_cptr
suffix:semicolon
multiline_comment|/*=(char *)0xff020000;*/
DECL|variable|_cpleft
r_static
r_int
id|_cpleft
suffix:semicolon
DECL|function|q40_mem_console_write
r_static
r_void
id|q40_mem_console_write
c_func
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|count
)paren
(brace
r_char
op_star
id|p
op_assign
(paren
r_char
op_star
)paren
id|s
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|_cpleft
)paren
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|q40_mem_cptr
op_assign
op_star
id|p
op_increment
suffix:semicolon
id|q40_mem_cptr
op_add_assign
l_int|4
suffix:semicolon
id|_cpleft
op_decrement
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_void
id|printq40
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|l
op_assign
id|strlen
c_func
(paren
id|str
)paren
suffix:semicolon
r_char
op_star
id|p
op_assign
id|q40_mem_cptr
suffix:semicolon
r_while
c_loop
(paren
id|l
op_decrement
OG
l_int|0
op_logical_and
id|_cpleft
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|p
op_assign
op_star
id|str
op_increment
suffix:semicolon
id|p
op_add_assign
l_int|4
suffix:semicolon
)brace
id|q40_mem_cptr
op_assign
id|p
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0
r_int
id|q40_kbdrate
(paren
r_struct
id|kbd_repeat
op_star
id|k
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|q40_reset
r_void
id|q40_reset
c_func
(paren
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;n&bslash;n*******************************************&bslash;n&quot;
l_string|&quot;Called q40_reset : press the RESET button!! &bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;*******************************************&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|q40_get_model
r_static
r_void
id|q40_get_model
c_func
(paren
r_char
op_star
id|model
)paren
(brace
id|sprintf
c_func
(paren
id|model
comma
l_string|&quot;Q40&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* No hardware options on Q40? */
DECL|function|q40_get_hardware_list
r_static
r_int
id|q40_get_hardware_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
op_star
id|buffer
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|config_q40
c_func
(paren
r_void
)paren
)paren
(brace
id|mach_sched_init
op_assign
id|q40_sched_init
suffix:semicolon
multiline_comment|/* ok */
multiline_comment|/*mach_kbdrate         = q40_kbdrate;*/
multiline_comment|/* unneeded ?*/
id|mach_keyb_init
op_assign
id|q40_keyb_init
suffix:semicolon
multiline_comment|/* OK */
id|mach_init_IRQ
op_assign
id|q40_init_IRQ
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|q40_gettimeoffset
suffix:semicolon
id|mach_gettod
op_assign
id|q40_gettod
suffix:semicolon
id|mach_hwclk
op_assign
id|q40_hwclk
suffix:semicolon
id|mach_set_clock_mmss
op_assign
id|q40_set_clock_mmss
suffix:semicolon
multiline_comment|/*  mach_mksound         = q40_mksound; */
id|mach_reset
op_assign
id|q40_reset
suffix:semicolon
multiline_comment|/* use reset button instead !*/
id|mach_free_irq
op_assign
id|q40_free_irq
suffix:semicolon
id|mach_process_int
op_assign
id|q40_process_int
suffix:semicolon
id|mach_get_irq_list
op_assign
id|q40_get_irq_list
suffix:semicolon
id|mach_request_irq
op_assign
id|q40_request_irq
suffix:semicolon
id|enable_irq
op_assign
id|q40_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|q40_disable_irq
suffix:semicolon
id|mach_default_handler
op_assign
op_amp
id|q40_sys_default_handler
suffix:semicolon
id|mach_get_model
op_assign
id|q40_get_model
suffix:semicolon
multiline_comment|/* no use..*/
id|mach_get_hardware_list
op_assign
id|q40_get_hardware_list
suffix:semicolon
multiline_comment|/* no use */
id|kd_mksound
op_assign
id|q40_mksound
suffix:semicolon
multiline_comment|/*mach_kbd_leds        = q40kbd_leds;*/
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|mach_sysrq_key
op_assign
l_int|0x54
suffix:semicolon
macro_line|#endif
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|mach_floppy_setup
op_assign
id|fd_floppy_setup
suffix:semicolon
id|mach_floppy_eject
op_assign
id|fd_floppy_eject
suffix:semicolon
multiline_comment|/**/
macro_line|#endif
id|mach_max_dma_address
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no DMA at all */
multiline_comment|/* userfull for early debuging stages writes kernel messages into SRAM */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|m68k_debug_device
comma
l_string|&quot;mem&quot;
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/*printk(&quot;using NVRAM debug, q40_mem_cptr=%p&bslash;n&quot;,q40_mem_cptr);*/
id|_cpleft
op_assign
l_int|2000
op_minus
(paren
(paren
r_int
)paren
id|q40_mem_cptr
op_minus
l_int|0xff020000
)paren
op_div
l_int|4
suffix:semicolon
id|q40_console_driver.write
op_assign
id|q40_mem_console_write
suffix:semicolon
id|register_console
c_func
(paren
op_amp
id|q40_console_driver
)paren
suffix:semicolon
)brace
)brace
DECL|function|q40_parse_bootinfo
r_int
id|q40_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|rec
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* unknown */
)brace
DECL|macro|DAC_LEFT
mdefine_line|#define DAC_LEFT  ((unsigned char *)0xff008000)
DECL|macro|DAC_RIGHT
mdefine_line|#define DAC_RIGHT ((unsigned char *)0xff008004)
DECL|function|q40_mksound
r_void
id|q40_mksound
c_func
(paren
r_int
r_int
id|hz
comma
r_int
r_int
id|ticks
)paren
(brace
multiline_comment|/* for now ignore hz, except that hz==0 switches off sound */
multiline_comment|/* simply alternate the ampl 0-255-0-.. at 200Hz */
r_if
c_cond
(paren
id|hz
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sound_ticks
)paren
id|sound_ticks
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* atomic - no irq spinlock used */
op_star
id|DAC_LEFT
op_assign
l_int|0
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* sound itself is done in q40_timer_int */
r_if
c_cond
(paren
id|sound_ticks
op_eq
l_int|0
)paren
id|sound_ticks
op_assign
l_int|1000
suffix:semicolon
multiline_comment|/* pretty long beep */
id|sound_ticks
op_assign
id|ticks
op_lshift
l_int|1
suffix:semicolon
)brace
DECL|variable|q40_timer_routine
r_static
r_void
(paren
op_star
id|q40_timer_routine
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|function|q40_timer_int
r_static
r_void
id|q40_timer_int
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
macro_line|#if (HZ==10000)
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
macro_line|#else /* must be 50 or 100 */
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|FRAME_CLEAR_REG
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if (HZ==100)
id|ql_ticks
op_assign
id|ql_ticks
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sound_ticks
)paren
(brace
r_int
r_char
id|sval
op_assign
(paren
id|sound_ticks
op_amp
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|255
suffix:semicolon
id|sound_ticks
op_decrement
suffix:semicolon
op_star
id|DAC_LEFT
op_assign
id|sval
suffix:semicolon
op_star
id|DAC_RIGHT
op_assign
id|sval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ql_ticks
)paren
r_return
suffix:semicolon
macro_line|#endif
id|q40_timer_routine
c_func
(paren
id|irq
comma
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
DECL|function|q40_sched_init
r_void
id|q40_sched_init
(paren
r_void
(paren
op_star
id|timer_routine
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
r_int
id|timer_irq
suffix:semicolon
id|q40_timer_routine
op_assign
id|timer_routine
suffix:semicolon
macro_line|#if (HZ==10000)
id|timer_irq
op_assign
id|Q40_IRQ_TIMER
suffix:semicolon
macro_line|#else
id|timer_irq
op_assign
id|Q40_IRQ_FRAME
suffix:semicolon
macro_line|#endif
multiline_comment|/*printk(&quot;registering sched/timer IRQ %d&bslash;n&quot;, timer_irq);*/
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|timer_irq
comma
id|q40_timer_int
comma
l_int|0
comma
l_string|&quot;timer&quot;
comma
id|q40_timer_int
)paren
)paren
id|panic
(paren
l_string|&quot;Couldn&squot;t register timer int&quot;
)paren
suffix:semicolon
macro_line|#if (HZ==10000)
id|master_outb
c_func
(paren
id|SAMPLE_LOW
comma
id|SAMPLE_RATE_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|SAMPLE_CLEAR_REG
)paren
suffix:semicolon
id|master_outb
c_func
(paren
l_int|1
comma
id|SAMPLE_ENABLE_REG
)paren
suffix:semicolon
macro_line|#else
id|master_outb
c_func
(paren
op_minus
l_int|1
comma
id|FRAME_CLEAR_REG
)paren
suffix:semicolon
multiline_comment|/* not necessary ? */
macro_line|#if (HZ==100)
id|master_outb
c_func
(paren
l_int|1
comma
id|FRAME_RATE_REG
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
DECL|function|q40_gettimeoffset
r_int
r_int
id|q40_gettimeoffset
(paren
r_void
)paren
(brace
macro_line|#if (HZ==100)
r_return
l_int|5000
op_star
(paren
id|ql_ticks
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|q40_gettod
r_extern
r_void
id|q40_gettod
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
(brace
id|RTC_CTRL
op_or_assign
id|RTC_READ
suffix:semicolon
op_star
id|year
op_assign
id|bcd2bin
(paren
id|RTC_YEAR
)paren
suffix:semicolon
op_star
id|mon
op_assign
id|bcd2bin
(paren
id|RTC_MNTH
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|day
op_assign
id|bcd2bin
(paren
id|RTC_DATE
)paren
suffix:semicolon
op_star
id|hour
op_assign
id|bcd2bin
(paren
id|RTC_HOUR
)paren
suffix:semicolon
op_star
id|min
op_assign
id|bcd2bin
(paren
id|RTC_MINS
)paren
suffix:semicolon
op_star
id|sec
op_assign
id|bcd2bin
(paren
id|RTC_SECS
)paren
suffix:semicolon
id|RTC_CTRL
op_and_assign
op_complement
(paren
id|RTC_READ
)paren
suffix:semicolon
)brace
DECL|function|bcd2bin
r_static
r_int
r_char
id|bcd2bin
(paren
r_int
r_char
id|b
)paren
(brace
r_return
(paren
(paren
id|b
op_rshift
l_int|4
)paren
op_star
l_int|10
op_plus
(paren
id|b
op_amp
l_int|15
)paren
)paren
suffix:semicolon
)brace
DECL|function|bin2bcd
r_static
r_int
r_char
id|bin2bcd
(paren
r_int
r_char
id|b
)paren
(brace
r_return
(paren
(paren
(paren
id|b
op_div
l_int|10
)paren
op_star
l_int|16
)paren
op_plus
(paren
id|b
op_mod
l_int|10
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Looks like op is non-zero for setting the clock, and zero for&n; * reading the clock.&n; *&n; *  struct hwclk_time {&n; *         unsigned        sec;       0..59&n; *         unsigned        min;       0..59&n; *         unsigned        hour;      0..23&n; *         unsigned        day;       1..31&n; *         unsigned        mon;       0..11&n; *         unsigned        year;      00...&n; *         int             wday;      0..6, 0 is Sunday, -1 means unknown/don&squot;t set&n; * };&n; */
DECL|function|q40_hwclk
r_int
id|q40_hwclk
c_func
(paren
r_int
id|op
comma
r_struct
id|hwclk_time
op_star
id|t
)paren
(brace
r_if
c_cond
(paren
id|op
)paren
(brace
multiline_comment|/* Write.... */
id|RTC_CTRL
op_or_assign
id|RTC_WRITE
suffix:semicolon
id|RTC_SECS
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;sec
)paren
suffix:semicolon
id|RTC_MINS
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;min
)paren
suffix:semicolon
id|RTC_HOUR
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;hour
)paren
suffix:semicolon
id|RTC_DATE
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;day
)paren
suffix:semicolon
id|RTC_MNTH
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;mon
op_plus
l_int|1
)paren
suffix:semicolon
id|RTC_YEAR
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;year
op_mod
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;wday
op_ge
l_int|0
)paren
id|RTC_DOW
op_assign
id|bin2bcd
c_func
(paren
id|t-&gt;wday
op_plus
l_int|1
)paren
suffix:semicolon
id|RTC_CTRL
op_and_assign
op_complement
(paren
id|RTC_WRITE
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Read....  */
id|RTC_CTRL
op_or_assign
id|RTC_READ
suffix:semicolon
id|t-&gt;year
op_assign
id|bcd2bin
(paren
id|RTC_YEAR
)paren
suffix:semicolon
id|t-&gt;mon
op_assign
id|bcd2bin
(paren
id|RTC_MNTH
)paren
op_minus
l_int|1
suffix:semicolon
id|t-&gt;day
op_assign
id|bcd2bin
(paren
id|RTC_DATE
)paren
suffix:semicolon
id|t-&gt;hour
op_assign
id|bcd2bin
(paren
id|RTC_HOUR
)paren
suffix:semicolon
id|t-&gt;min
op_assign
id|bcd2bin
(paren
id|RTC_MINS
)paren
suffix:semicolon
id|t-&gt;sec
op_assign
id|bcd2bin
(paren
id|RTC_SECS
)paren
suffix:semicolon
id|RTC_CTRL
op_and_assign
op_complement
(paren
id|RTC_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;year
OL
l_int|70
)paren
id|t-&gt;year
op_add_assign
l_int|100
suffix:semicolon
id|t-&gt;wday
op_assign
id|bcd2bin
c_func
(paren
id|RTC_DOW
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the minutes and seconds from seconds value &squot;nowtime&squot;.  Fail if&n; * clock is out by &gt; 30 minutes.  Logic lifted from atari code.&n; * Algorithm is to wait for the 10ms register to change, and then to&n; * wait a short while, and then set it.&n; */
DECL|function|q40_set_clock_mmss
r_int
id|q40_set_clock_mmss
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
comma
id|real_minutes
op_assign
(paren
id|nowtime
op_div
l_int|60
)paren
op_mod
l_int|60
suffix:semicolon
r_int
id|rtc_minutes
suffix:semicolon
id|rtc_minutes
op_assign
id|bcd2bin
(paren
id|RTC_MINS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtc_minutes
OL
id|real_minutes
ques
c_cond
id|real_minutes
op_minus
id|rtc_minutes
suffix:colon
id|rtc_minutes
op_minus
id|real_minutes
)paren
OL
l_int|30
)paren
(brace
id|RTC_CTRL
op_or_assign
id|RTC_WRITE
suffix:semicolon
id|RTC_MINS
op_assign
id|bin2bcd
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|RTC_SECS
op_assign
id|bin2bcd
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|RTC_CTRL
op_and_assign
op_complement
(paren
id|RTC_WRITE
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
r_void
id|q40kbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|q40_keyb_init
r_int
id|q40_keyb_init
(paren
r_void
)paren
(brace
id|q40kbd_init_hw
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* dummy to cause */
r_void
id|q40_slow_io
c_func
(paren
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif
eof
