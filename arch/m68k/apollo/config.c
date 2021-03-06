macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/apollohw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|variable|sio01_physaddr
id|u_long
id|sio01_physaddr
suffix:semicolon
DECL|variable|sio23_physaddr
id|u_long
id|sio23_physaddr
suffix:semicolon
DECL|variable|rtc_physaddr
id|u_long
id|rtc_physaddr
suffix:semicolon
DECL|variable|pica_physaddr
id|u_long
id|pica_physaddr
suffix:semicolon
DECL|variable|picb_physaddr
id|u_long
id|picb_physaddr
suffix:semicolon
DECL|variable|cpuctrl_physaddr
id|u_long
id|cpuctrl_physaddr
suffix:semicolon
DECL|variable|timer_physaddr
id|u_long
id|timer_physaddr
suffix:semicolon
DECL|variable|apollo_model
id|u_long
id|apollo_model
suffix:semicolon
r_extern
r_void
id|dn_sched_init
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
id|dn_keyb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dn_dummy_kbdrate
c_func
(paren
r_struct
id|kbd_repeat
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dn_init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dn_request_irq
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
id|dn_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|dn_enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dn_disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|dn_get_irq_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|dn_gettimeoffset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_gettod
c_func
(paren
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dn_dummy_hwclk
c_func
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
id|dn_dummy_set_clock_mmss
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dn_mksound
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|ticks
)paren
suffix:semicolon
r_extern
r_void
id|dn_dummy_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dn_dummy_waitbut
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|fb_info
op_star
id|dn_fb_init
c_func
(paren
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dn_dummy_debug_init
c_func
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
r_extern
r_void
id|dn_dummy_video_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|dn_process_int
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
r_static
r_void
id|dn_heartbeat
c_func
(paren
r_int
id|on
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|dn_timer_int
c_func
(paren
r_int
id|irq
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|sched_timer_handler
r_static
r_void
(paren
op_star
id|sched_timer_handler
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
op_assign
l_int|NULL
suffix:semicolon
r_static
r_void
id|dn_get_model
c_func
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
DECL|variable|dn_cpuctrl
r_static
r_int
id|dn_cpuctrl
op_assign
l_int|0xff00
suffix:semicolon
DECL|variable|apollo_models
r_static
r_const
r_char
op_star
id|apollo_models
(braket
)braket
op_assign
(brace
l_string|&quot;DN3000 (Otter)&quot;
comma
l_string|&quot;DN3010 (Otter)&quot;
comma
l_string|&quot;DN3500 (Cougar II)&quot;
comma
l_string|&quot;DN4000 (Mink)&quot;
comma
l_string|&quot;DN4500 (Roadrunner)&quot;
)brace
suffix:semicolon
DECL|function|apollo_parse_bootinfo
r_int
id|apollo_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|record
)paren
(brace
r_int
id|unknown
op_assign
l_int|0
suffix:semicolon
r_const
r_int
r_int
op_star
id|data
op_assign
id|record-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|record-&gt;tag
)paren
(brace
r_case
id|BI_APOLLO_MODEL
suffix:colon
id|apollo_model
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|unknown
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|unknown
suffix:semicolon
)brace
DECL|function|dn_setup_model
r_void
id|dn_setup_model
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Apollo hardware found: &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%s]&bslash;n&quot;
comma
id|apollo_models
(braket
id|apollo_model
op_minus
id|APOLLO_DN3000
)braket
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|apollo_model
)paren
(brace
r_case
id|APOLLO_UNKNOWN
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unknown apollo model&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|APOLLO_DN3000
suffix:colon
r_case
id|APOLLO_DN3010
suffix:colon
id|sio01_physaddr
op_assign
id|SAU8_SIO01_PHYSADDR
suffix:semicolon
id|rtc_physaddr
op_assign
id|SAU8_RTC_PHYSADDR
suffix:semicolon
id|pica_physaddr
op_assign
id|SAU8_PICA
suffix:semicolon
id|picb_physaddr
op_assign
id|SAU8_PICB
suffix:semicolon
id|cpuctrl_physaddr
op_assign
id|SAU8_CPUCTRL
suffix:semicolon
id|timer_physaddr
op_assign
id|SAU8_TIMER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|APOLLO_DN4000
suffix:colon
id|sio01_physaddr
op_assign
id|SAU7_SIO01_PHYSADDR
suffix:semicolon
id|sio23_physaddr
op_assign
id|SAU7_SIO23_PHYSADDR
suffix:semicolon
id|rtc_physaddr
op_assign
id|SAU7_RTC_PHYSADDR
suffix:semicolon
id|pica_physaddr
op_assign
id|SAU7_PICA
suffix:semicolon
id|picb_physaddr
op_assign
id|SAU7_PICB
suffix:semicolon
id|cpuctrl_physaddr
op_assign
id|SAU7_CPUCTRL
suffix:semicolon
id|timer_physaddr
op_assign
id|SAU7_TIMER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|APOLLO_DN4500
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Apollo model not yet supported&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|APOLLO_DN3500
suffix:colon
id|sio01_physaddr
op_assign
id|SAU7_SIO01_PHYSADDR
suffix:semicolon
id|sio23_physaddr
op_assign
id|SAU7_SIO23_PHYSADDR
suffix:semicolon
id|rtc_physaddr
op_assign
id|SAU7_RTC_PHYSADDR
suffix:semicolon
id|pica_physaddr
op_assign
id|SAU7_PICA
suffix:semicolon
id|picb_physaddr
op_assign
id|SAU7_PICB
suffix:semicolon
id|cpuctrl_physaddr
op_assign
id|SAU7_CPUCTRL
suffix:semicolon
id|timer_physaddr
op_assign
id|SAU7_TIMER
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Undefined apollo model&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|dn_serial_console_wait_key
r_int
id|dn_serial_console_wait_key
c_func
(paren
r_struct
id|console
op_star
id|co
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|sio01.srb_csrb
op_amp
l_int|1
)paren
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|sio01.rhrb_thrb
suffix:semicolon
)brace
DECL|function|dn_serial_console_write
r_void
id|dn_serial_console_write
(paren
r_struct
id|console
op_star
id|co
comma
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|count
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|sio01.rhrb_thrb
op_assign
(paren
r_int
r_char
)paren
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|sio01.srb_csrb
op_amp
l_int|0x4
)paren
)paren
suffix:semicolon
)brace
id|sio01.rhrb_thrb
op_assign
(paren
r_int
r_char
)paren
op_star
id|str
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|sio01.srb_csrb
op_amp
l_int|0x4
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|dn_serial_print
r_void
id|dn_serial_print
(paren
r_const
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|sio01.rhrb_thrb
op_assign
(paren
r_int
r_char
)paren
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|sio01.srb_csrb
op_amp
l_int|0x4
)paren
)paren
suffix:semicolon
)brace
id|sio01.rhrb_thrb
op_assign
(paren
r_int
r_char
)paren
op_star
id|str
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|sio01.srb_csrb
op_amp
l_int|0x4
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|config_apollo
r_void
id|config_apollo
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|dn_setup_model
c_func
(paren
)paren
suffix:semicolon
id|mach_sched_init
op_assign
id|dn_sched_init
suffix:semicolon
multiline_comment|/* */
id|mach_keyb_init
op_assign
id|dn_keyb_init
suffix:semicolon
id|mach_kbdrate
op_assign
id|dn_dummy_kbdrate
suffix:semicolon
id|mach_init_IRQ
op_assign
id|dn_init_IRQ
suffix:semicolon
id|mach_default_handler
op_assign
l_int|NULL
suffix:semicolon
id|mach_request_irq
op_assign
id|dn_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|dn_free_irq
suffix:semicolon
id|enable_irq
op_assign
id|dn_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|dn_disable_irq
suffix:semicolon
id|mach_get_irq_list
op_assign
id|dn_get_irq_list
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|dn_gettimeoffset
suffix:semicolon
id|mach_gettod
op_assign
id|dn_gettod
suffix:semicolon
multiline_comment|/* */
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
id|mach_hwclk
op_assign
id|dn_dummy_hwclk
suffix:semicolon
multiline_comment|/* */
id|mach_set_clock_mmss
op_assign
id|dn_dummy_set_clock_mmss
suffix:semicolon
multiline_comment|/* */
id|mach_process_int
op_assign
id|dn_process_int
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|mach_floppy_init
op_assign
id|dn_dummy_floppy_init
suffix:semicolon
id|mach_floppy_setup
op_assign
id|dn_dummy_floppy_setup
suffix:semicolon
macro_line|#endif
id|mach_reset
op_assign
id|dn_dummy_reset
suffix:semicolon
multiline_comment|/* */
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|kd_mksound
op_assign
id|dn_mksound
suffix:semicolon
macro_line|#ifdef CONFIG_HEARTBEAT
id|mach_heartbeat
op_assign
id|dn_heartbeat
suffix:semicolon
macro_line|#endif
id|mach_get_model
op_assign
id|dn_get_model
suffix:semicolon
id|cpuctrl
op_assign
l_int|0xaa00
suffix:semicolon
multiline_comment|/* clear DMA translation table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x400
suffix:semicolon
id|i
op_increment
)paren
(brace
id|addr_xlat_map
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|dn_timer_int
r_void
id|dn_timer_int
c_func
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
r_volatile
r_int
r_char
id|x
suffix:semicolon
id|sched_timer_handler
c_func
(paren
id|irq
comma
id|dev_id
comma
id|fp
)paren
suffix:semicolon
id|x
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|3
)paren
suffix:semicolon
id|x
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|5
)paren
suffix:semicolon
)brace
DECL|function|dn_sched_init
r_void
id|dn_sched_init
c_func
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
multiline_comment|/* program timer 1 */
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|3
)paren
op_assign
l_int|0x01
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|1
)paren
op_assign
l_int|0x40
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|5
)paren
op_assign
l_int|0x09
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|7
)paren
op_assign
l_int|0xc4
suffix:semicolon
multiline_comment|/* enable IRQ of PIC B */
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|pica
op_plus
l_int|1
)paren
op_and_assign
(paren
op_complement
l_int|8
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;*(0x10803) %02x&bslash;n&quot;
comma
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|0x3
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;*(0x10803) %02x&bslash;n&quot;
comma
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|timer
op_plus
l_int|0x3
)paren
)paren
suffix:semicolon
macro_line|#endif
id|sched_timer_handler
op_assign
id|timer_routine
suffix:semicolon
id|request_irq
c_func
(paren
l_int|0
comma
id|dn_timer_int
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|dn_gettimeoffset
r_int
r_int
id|dn_gettimeoffset
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0xdeadbeef
suffix:semicolon
)brace
DECL|function|dn_gettod
r_void
id|dn_gettod
c_func
(paren
r_int
op_star
id|yearp
comma
r_int
op_star
id|monp
comma
r_int
op_star
id|dayp
comma
r_int
op_star
id|hourp
comma
r_int
op_star
id|minp
comma
r_int
op_star
id|secp
)paren
(brace
op_star
id|yearp
op_assign
id|rtc-&gt;year
suffix:semicolon
op_star
id|monp
op_assign
id|rtc-&gt;month
suffix:semicolon
op_star
id|dayp
op_assign
id|rtc-&gt;day_of_month
suffix:semicolon
op_star
id|hourp
op_assign
id|rtc-&gt;hours
suffix:semicolon
op_star
id|minp
op_assign
id|rtc-&gt;minute
suffix:semicolon
op_star
id|secp
op_assign
id|rtc-&gt;second
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;gettod: %d %d %d %d %d %d&bslash;n&quot;
comma
op_star
id|yearp
comma
op_star
id|monp
comma
op_star
id|dayp
comma
op_star
id|hourp
comma
op_star
id|minp
comma
op_star
id|secp
)paren
suffix:semicolon
)brace
DECL|function|dn_dummy_hwclk
r_int
id|dn_dummy_hwclk
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
op_logical_neg
id|op
)paren
(brace
multiline_comment|/* read */
id|t-&gt;sec
op_assign
id|rtc-&gt;second
suffix:semicolon
id|t-&gt;min
op_assign
id|rtc-&gt;minute
suffix:semicolon
id|t-&gt;hour
op_assign
id|rtc-&gt;hours
suffix:semicolon
id|t-&gt;day
op_assign
id|rtc-&gt;day_of_month
suffix:semicolon
id|t-&gt;wday
op_assign
id|rtc-&gt;day_of_week
suffix:semicolon
id|t-&gt;mon
op_assign
id|rtc-&gt;month
suffix:semicolon
id|t-&gt;year
op_assign
id|rtc-&gt;year
suffix:semicolon
)brace
r_else
(brace
id|rtc-&gt;second
op_assign
id|t-&gt;sec
suffix:semicolon
id|rtc-&gt;minute
op_assign
id|t-&gt;min
suffix:semicolon
id|rtc-&gt;hours
op_assign
id|t-&gt;hour
suffix:semicolon
id|rtc-&gt;day_of_month
op_assign
id|t-&gt;day
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;wday
op_ne
op_minus
l_int|1
)paren
(brace
id|rtc-&gt;day_of_week
op_assign
id|t-&gt;wday
suffix:semicolon
)brace
id|rtc-&gt;month
op_assign
id|t-&gt;mon
suffix:semicolon
id|rtc-&gt;year
op_assign
id|t-&gt;year
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_dummy_set_clock_mmss
r_int
id|dn_dummy_set_clock_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;set_clock_mmss&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_dummy_reset
r_void
id|dn_dummy_reset
c_func
(paren
r_void
)paren
(brace
id|dn_serial_print
c_func
(paren
l_string|&quot;The end !&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|dn_dummy_waitbut
r_void
id|dn_dummy_waitbut
c_func
(paren
r_void
)paren
(brace
id|dn_serial_print
c_func
(paren
l_string|&quot;waitbut&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|dn_get_model
r_static
r_void
id|dn_get_model
c_func
(paren
r_char
op_star
id|model
)paren
(brace
id|strcpy
c_func
(paren
id|model
comma
l_string|&quot;Apollo &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apollo_model
op_ge
id|APOLLO_DN3000
op_logical_and
id|apollo_model
op_le
id|APOLLO_DN4500
)paren
id|strcat
c_func
(paren
id|model
comma
id|apollo_models
(braket
id|apollo_model
op_minus
id|APOLLO_DN3000
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|function|dn_heartbeat
r_static
r_void
id|dn_heartbeat
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
(brace
id|dn_cpuctrl
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
id|cpuctrl
op_assign
id|dn_cpuctrl
suffix:semicolon
)brace
r_else
(brace
id|dn_cpuctrl
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
id|dn_cpuctrl
op_or_assign
l_int|0x100
suffix:semicolon
id|cpuctrl
op_assign
id|dn_cpuctrl
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
