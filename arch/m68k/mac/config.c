multiline_comment|/*&n; *  linux/arch/m68k/mac/config.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/*&n; * Miscellaneous linux stuff&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/* keyb */
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/* keyb */
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|BOOTINFO_COMPAT_1_0
mdefine_line|#define BOOTINFO_COMPAT_1_0
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &quot;via6522.h&quot;
multiline_comment|/* Mac bootinfo struct */
DECL|variable|mac_bi_data
r_struct
id|mac_booter_data
id|mac_bi_data
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|mac_bisize
r_int
id|mac_bisize
op_assign
r_sizeof
id|mac_bi_data
suffix:semicolon
multiline_comment|/* New m68k bootinfo stuff and videobase */
r_extern
r_int
id|m68k_num_memory
suffix:semicolon
r_extern
r_struct
id|mem_info
id|m68k_memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
r_extern
r_struct
id|mem_info
id|m68k_ramdisk
suffix:semicolon
r_extern
r_char
id|m68k_command_line
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|variable|mac_env
r_void
op_star
id|mac_env
suffix:semicolon
multiline_comment|/* Loaded by the boot asm */
multiline_comment|/* The logical video addr. determined by head.S - testing */
r_extern
r_int
r_int
id|mac_videobase
suffix:semicolon
multiline_comment|/* The phys. video addr. - might be bogus on some machines */
DECL|variable|mac_orig_videoaddr
r_int
r_int
id|mac_orig_videoaddr
suffix:semicolon
r_extern
r_int
id|mac_keyb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mac_kbdrate
c_func
(paren
r_struct
id|kbd_repeat
op_star
id|k
)paren
suffix:semicolon
r_extern
r_void
id|mac_kbd_leds
c_func
(paren
r_int
r_int
id|leds
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
id|mac_mksound
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|mac_floppy_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mac_floppy_setup
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
id|mac_gettod
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
r_void
id|nubus_sweep_video
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|via_init_clock
c_func
(paren
r_void
(paren
op_star
id|func
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
r_void
id|mac_debugging_long
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Mac specific debug functions (in debug.c) */
r_extern
r_void
id|mac_debug_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
multiline_comment|/* XXX FIXME: Atari scancodes still */
DECL|variable|mac_sysrq_xlate
r_static
r_char
id|mac_sysrq_xlate
(braket
l_int|128
)braket
op_assign
l_string|&quot;&bslash;000&bslash;0331234567890-=&bslash;177&bslash;t&quot;
multiline_comment|/* 0x00 - 0x0f */
l_string|&quot;qwertyuiop[]&bslash;r&bslash;000as&quot;
multiline_comment|/* 0x10 - 0x1f */
l_string|&quot;dfghjkl;&squot;`&bslash;000&bslash;&bslash;zxcv&quot;
multiline_comment|/* 0x20 - 0x2f */
l_string|&quot;bnm,./&bslash;000&bslash;000&bslash;000 &bslash;000&bslash;201&bslash;202&bslash;203&bslash;204&bslash;205&quot;
multiline_comment|/* 0x30 - 0x3f */
l_string|&quot;&bslash;206&bslash;207&bslash;210&bslash;211&bslash;212&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000-&bslash;000&bslash;000&bslash;000+&bslash;000&quot;
multiline_comment|/* 0x40 - 0x4f */
l_string|&quot;&bslash;000&bslash;000&bslash;000&bslash;177&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&quot;
multiline_comment|/* 0x50 - 0x5f */
l_string|&quot;&bslash;000&bslash;000&bslash;000()/*789456123&quot;
multiline_comment|/* 0x60 - 0x6f */
l_string|&quot;0.&bslash;r&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&bslash;000&quot;
suffix:semicolon
multiline_comment|/* 0x70 - 0x7f */
macro_line|#endif
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
r_static
r_void
id|mac_get_model
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|function|mac_bang
r_void
id|mac_bang
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|vector
comma
r_struct
id|pt_regs
op_star
id|p
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Resetting ...&bslash;n&quot;
)paren
suffix:semicolon
id|mac_reset
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|mac_sched_init
r_void
id|mac_sched_init
c_func
(paren
r_void
(paren
op_star
id|vector
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
id|via_init_clock
c_func
(paren
id|vector
)paren
suffix:semicolon
)brace
DECL|function|mac_gettimeoffset
r_int
r_int
id|mac_gettimeoffset
(paren
r_void
)paren
(brace
r_return
l_int|0L
suffix:semicolon
)brace
r_extern
r_int
id|console_loglevel
suffix:semicolon
multiline_comment|/*&n; * This function translates the boot timeval into a proper date, to initialize&n; * the system time.&n; * Known problem: off by one after Feb. 27 on leap years&n; */
DECL|function|mac_gettod
r_void
id|mac_gettod
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
r_int
r_int
id|time
suffix:semicolon
r_int
id|leap
comma
id|oldleap
comma
id|isleap
suffix:semicolon
r_int
id|mon_days
(braket
l_int|14
)braket
op_assign
(brace
op_minus
l_int|1
comma
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
op_minus
l_int|1
)brace
suffix:semicolon
id|time
op_assign
id|mac_bi_data.boottime
op_minus
l_int|60
op_star
id|mac_bi_data.gmtbias
suffix:semicolon
multiline_comment|/* seconds */
op_star
id|minp
op_assign
id|time
op_div
l_int|60
suffix:semicolon
op_star
id|secp
op_assign
id|time
op_minus
(paren
op_star
id|minp
op_star
l_int|60
)paren
suffix:semicolon
id|time
op_assign
op_star
id|minp
suffix:semicolon
multiline_comment|/* minutes now */
op_star
id|hourp
op_assign
id|time
op_div
l_int|60
suffix:semicolon
op_star
id|minp
op_assign
id|time
op_minus
(paren
op_star
id|hourp
op_star
l_int|60
)paren
suffix:semicolon
id|time
op_assign
op_star
id|hourp
suffix:semicolon
multiline_comment|/* hours now */
op_star
id|dayp
op_assign
id|time
op_div
l_int|24
suffix:semicolon
op_star
id|hourp
op_assign
id|time
op_minus
(paren
op_star
id|dayp
op_star
l_int|24
)paren
suffix:semicolon
id|time
op_assign
op_star
id|dayp
suffix:semicolon
multiline_comment|/* days now ... */
multiline_comment|/* for leap day calculation */
op_star
id|yearp
op_assign
(paren
id|time
op_div
l_int|365
)paren
op_plus
l_int|1970
suffix:semicolon
multiline_comment|/* approx. year */
multiline_comment|/* leap year calculation - there&squot;s an easier way, I bet. And it&squot;s broken :-( */
multiline_comment|/* calculate leap days up to previous year */
id|oldleap
op_assign
(paren
op_star
id|yearp
op_minus
l_int|1
)paren
op_div
l_int|4
op_minus
(paren
op_star
id|yearp
op_minus
l_int|1
)paren
op_div
l_int|100
op_plus
(paren
op_star
id|yearp
op_minus
l_int|1
)paren
op_div
l_int|400
suffix:semicolon
multiline_comment|/* calculate leap days incl. this year */
id|leap
op_assign
op_star
id|yearp
op_div
l_int|4
op_minus
op_star
id|yearp
op_div
l_int|100
op_plus
op_star
id|yearp
op_div
l_int|400
suffix:semicolon
multiline_comment|/* this year a leap year ?? */
id|isleap
op_assign
(paren
id|leap
op_ne
id|oldleap
)paren
suffix:semicolon
multiline_comment|/* adjust days: days, excluding past leap days since epoch */
id|time
op_sub_assign
id|oldleap
op_minus
(paren
l_int|1970
op_div
l_int|4
op_minus
l_int|1970
op_div
l_int|100
op_plus
l_int|1970
op_div
l_int|400
)paren
suffix:semicolon
multiline_comment|/* precise year, and day in year */
op_star
id|yearp
op_assign
(paren
id|time
op_div
l_int|365
)paren
suffix:semicolon
multiline_comment|/* #years since epoch */
op_star
id|dayp
op_assign
id|time
op_minus
(paren
op_star
id|yearp
op_star
l_int|365
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* #days this year (0: Jan 1) */
op_star
id|yearp
op_add_assign
l_int|70
suffix:semicolon
multiline_comment|/* add epoch :-) */
id|time
op_assign
op_star
id|dayp
suffix:semicolon
r_if
c_cond
(paren
id|isleap
)paren
multiline_comment|/* add leap day ?? */
id|mon_days
(braket
l_int|2
)braket
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* count the months */
r_for
c_loop
(paren
op_star
id|monp
op_assign
l_int|1
suffix:semicolon
id|time
OG
id|mon_days
(braket
op_star
id|monp
)braket
suffix:semicolon
(paren
op_star
id|monp
)paren
op_increment
)paren
id|time
op_sub_assign
id|mon_days
(braket
op_star
id|monp
)braket
suffix:semicolon
op_star
id|dayp
op_assign
id|time
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mac_waitbut
r_void
id|mac_waitbut
(paren
r_void
)paren
(brace
suffix:semicolon
)brace
r_extern
r_struct
id|consw
id|fb_con
suffix:semicolon
r_extern
r_struct
id|fb_info
op_star
id|mac_fb_init
c_func
(paren
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mac_video_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|variable|mac_handlers
r_void
(paren
op_star
id|mac_handlers
(braket
l_int|8
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
op_assign
(brace
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
comma
id|mac_default_handler
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Parse a Macintosh-specific record in the bootinfo&n;     */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|mac_parse_bootinfo
c_func
(paren
r_const
r_struct
id|bi_record
op_star
id|record
)paren
)paren
(brace
r_int
id|unknown
op_assign
l_int|0
suffix:semicolon
r_const
id|u_long
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
id|BI_MAC_MODEL
suffix:colon
id|mac_bi_data.id
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VADDR
suffix:colon
multiline_comment|/* save booter supplied videobase; use the one mapped in head.S! */
id|mac_orig_videoaddr
op_assign
op_star
id|data
suffix:semicolon
id|mac_bi_data.videoaddr
op_assign
id|mac_videobase
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VDEPTH
suffix:colon
id|mac_bi_data.videodepth
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VROW
suffix:colon
id|mac_bi_data.videorow
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VDIM
suffix:colon
id|mac_bi_data.dimensions
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_VLOGICAL
suffix:colon
id|mac_bi_data.videological
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_SCCBASE
suffix:colon
id|mac_bi_data.sccbase
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_BTIME
suffix:colon
id|mac_bi_data.boottime
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_GMTBIAS
suffix:colon
id|mac_bi_data.gmtbias
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_MEMSIZE
suffix:colon
id|mac_bi_data.memsize
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BI_MAC_CPUID
suffix:colon
id|mac_bi_data.cpuid
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
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|config_mac
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_ATARI
op_logical_or
id|MACH_IS_AMIGA
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERROR: no Mac, but config_mac() called!! &bslash;n&quot;
)paren
suffix:semicolon
)brace
id|mac_debug_init
c_func
(paren
)paren
suffix:semicolon
id|mach_sched_init
op_assign
id|mac_sched_init
suffix:semicolon
id|mach_keyb_init
op_assign
id|mac_keyb_init
suffix:semicolon
id|mach_kbdrate
op_assign
id|mac_kbdrate
suffix:semicolon
id|mach_kbd_leds
op_assign
id|mac_kbd_leds
suffix:semicolon
id|mach_init_IRQ
op_assign
id|mac_init_IRQ
suffix:semicolon
id|mach_request_irq
op_assign
id|mac_request_irq
suffix:semicolon
id|mach_free_irq
op_assign
id|mac_free_irq
suffix:semicolon
id|enable_irq
op_assign
id|mac_enable_irq
suffix:semicolon
id|disable_irq
op_assign
id|mac_disable_irq
suffix:semicolon
macro_line|#if 1
id|mach_default_handler
op_assign
op_amp
id|mac_handlers
suffix:semicolon
macro_line|#endif
id|mach_get_model
op_assign
id|mac_get_model
suffix:semicolon
id|mach_get_irq_list
op_assign
id|mac_get_irq_list
suffix:semicolon
id|mach_gettimeoffset
op_assign
id|mac_gettimeoffset
suffix:semicolon
id|mach_gettod
op_assign
id|mac_gettod
suffix:semicolon
macro_line|#if 0
id|mach_mksound
op_assign
id|mac_mksound
suffix:semicolon
macro_line|#endif
id|mach_reset
op_assign
id|mac_reset
suffix:semicolon
id|conswitchp
op_assign
op_amp
id|fb_con
suffix:semicolon
id|mach_max_dma_address
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#if 0
id|mach_debug_init
op_assign
id|mac_debug_init
suffix:semicolon
id|mach_video_setup
op_assign
id|mac_video_setup
suffix:semicolon
macro_line|#endif
id|kd_mksound
op_assign
id|mac_mksound
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|mach_sysrq_key
op_assign
l_int|98
suffix:semicolon
multiline_comment|/* HELP */
id|mach_sysrq_shift_state
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Alt */
id|mach_sysrq_shift_mask
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* all modifiers except CapsLock */
id|mach_sysrq_xlate
op_assign
id|mac_sysrq_xlate
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
macro_line|#if 0
id|mach_heartbeat
op_assign
id|mac_heartbeat
suffix:semicolon
id|mach_heartbeat_irq
op_assign
id|IRQ_MAC_TIMER
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;     * Determine hardware present&n;     */
id|mac_identify
c_func
(paren
)paren
suffix:semicolon
id|mac_report_hardware
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* goes on forever if timers broken */
macro_line|#ifdef MAC_DEBUG_SOUND
id|mac_mksound
c_func
(paren
l_int|1000
comma
l_int|10
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;     * Check for machine specific fixups.&n;     */
id|nubus_sweep_video
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Macintosh Table: hardcoded model configuration data. &n; *&n; *&t;Much of this was defined by Alan, based on who knows what docs. &n; *&t;I&squot;ve added a lot more, and some of that was pure guesswork based &n; *&t;on hardware pages present on the Mac web site. Possibly wildly &n; *&t;inaccurate, so look here if a new Mac model won&squot;t run. Example: if&n; *&t;a Mac crashes immediately after the VIA1 registers have been dumped&n; *&t;to the screen, it probably died attempting to read DirB on a RBV. &n; *&t;Meaning it should have MAC_VIA_IIci here :-)&n; */
DECL|variable|macintosh_config
r_struct
id|mac_model
op_star
id|macintosh_config
suffix:semicolon
DECL|variable|mac_data_table
r_static
r_struct
id|mac_model
id|mac_data_table
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&t; *&t;Original MacII hardware&n;&t; *&t;&n;&t; */
(brace
id|MAC_MODEL_II
comma
l_string|&quot;II&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIX
comma
l_string|&quot;IIx&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IICX
comma
l_string|&quot;IIcx&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_SE30
comma
l_string|&quot;SE/30&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_II
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Weirdified MacII hardware - all subtley different. Gee thanks&n;&t; *&t;Apple. All these boxes seem to have VIA2 in a different place to&n;&t; *&t;the MacII (+1A000 rather than +4000)&n;&t; *&n;&t; *&t;The IIfx apparently has different ADB hardware, and stuff&n;&t; *&t;so zany nobody knows how to drive it.&n;&t; *&t;Even so, with Marten&squot;s help we&squot;ll try to deal with it :-)&n;&t; */
(brace
id|MAC_MODEL_IICI
comma
l_string|&quot;IIci&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIFX
comma
l_string|&quot;IIfx&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IISI
comma
l_string|&quot;IIsi&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIVI
comma
l_string|&quot;IIvi&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_IIVX
comma
l_string|&quot;IIvx&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Classic models (guessing: similar to SE/30 ?? Nope, similar to LC ...)&n;&t; */
(brace
id|MAC_MODEL_CLII
comma
l_string|&quot;Classic II&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_CCL
comma
l_string|&quot;Color Classic&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Some Mac LC machines. Basically the same as the IIci, ADB like IIsi&n;&t; */
(brace
id|MAC_MODEL_LC
comma
l_string|&quot;LC&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_LCII
comma
l_string|&quot;LC II&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_LCIII
comma
l_string|&quot;LC III&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Quadra (only 68030 ones will actually work!). Not much odd. Video is at&n;&t; *&t;0xF9000000, via is like a MacII. We label it differently as some of the&n;&t; *&t;stuff connected to VIA2 seems different. Better SCSI chip and ???? onboard ethernet&n;&t; *&t;in all cases using a NatSemi SONIC. The 700, 900 and 950 have some I/O chips in the wrong&n;&t; *&t;place to confuse us. The 840 seems to have a scsi location of its own&n;&t; */
(brace
id|MAC_MODEL_Q605
comma
l_string|&quot;Quadra 605&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q610
comma
l_string|&quot;Quadra 610&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q630
comma
l_string|&quot;Quadra 630&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_QUADRA
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q650
comma
l_string|&quot;Quadra 650&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&t;The Q700 does have a NS Sonic */
(brace
id|MAC_MODEL_Q700
comma
l_string|&quot;Quadra 700&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA2
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q800
comma
l_string|&quot;Quadra 800&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/* Does the 840 have ethernet ??? documents seem to indicate its not quite a&n;&t;   Quadra in this respect ? */
(brace
id|MAC_MODEL_Q840
comma
l_string|&quot;Quadra 840&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA3
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/* These might have IOP problems */
(brace
id|MAC_MODEL_Q900
comma
l_string|&quot;Quadra 900&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_IOP
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_Q950
comma
l_string|&quot;Quadra 950&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA2
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_IOP
comma
id|MAC_ETHER_SONIC
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/* &n;&t; *&t;Performa - more LC type machines&n;&t; */
(brace
id|MAC_MODEL_P460
comma
l_string|&quot;Performa 460&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P475
comma
l_string|&quot;Performa 475&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P475F
comma
l_string|&quot;Performa 475&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P520
comma
l_string|&quot;Performa 520&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P550
comma
l_string|&quot;Performa 550&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P575
comma
l_string|&quot;Performa 575&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P588
comma
l_string|&quot;Performa 588&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_TV
comma
l_string|&quot;TV&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_P600
comma
l_string|&quot;Performa 600&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
macro_line|#if 0&t;/* other sources seem to suggest the P630/Q630/LC630 is more like LCIII */
(brace
id|MAC_MODEL_P630
comma
l_string|&quot;Performa 630&quot;
comma
id|MAC_ADB_IISI
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_II
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Centris - just guessing again; maybe like Quadra&n;&t; */
(brace
id|MAC_MODEL_C610
comma
l_string|&quot;Centris 610&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_C650
comma
l_string|&quot;Centris 650&quot;
comma
id|MAC_ADB_II
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_C660
comma
l_string|&quot;Centris 660AV&quot;
comma
id|MAC_ADB_CUDA
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *      Power books - seem similar to early Quadras ? (most have 030 though)&n;&t; */
(brace
id|MAC_MODEL_PB140
comma
l_string|&quot;PowerBook 140&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB145
comma
l_string|&quot;PowerBook 145&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&t;The PB150 has IDE, and IIci style VIA */
(brace
id|MAC_MODEL_PB150
comma
l_string|&quot;PowerBook 150&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_PB
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB160
comma
l_string|&quot;PowerBook 160&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB165
comma
l_string|&quot;PowerBook 165&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB165C
comma
l_string|&quot;PowerBook 165c&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB170
comma
l_string|&quot;PowerBook 170&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB180
comma
l_string|&quot;PowerBook 180&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB180C
comma
l_string|&quot;PowerBook 180c&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB190
comma
l_string|&quot;PowerBook 190cs&quot;
comma
id|MAC_ADB_PB1
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_PB
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB520
comma
l_string|&quot;PowerBook 520&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *      Power book Duos - similar to Power books, I hope&n;&t; */
(brace
id|MAC_MODEL_PB210
comma
l_string|&quot;PowerBook Duo 210&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB230
comma
l_string|&quot;PowerBook Duo 230&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_IIci
comma
id|MAC_SCSI_OLD
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB250
comma
l_string|&quot;PowerBook Duo 250&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB270C
comma
l_string|&quot;PowerBook Duo 270c&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB280
comma
l_string|&quot;PowerBook Duo 280&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
(brace
id|MAC_MODEL_PB280C
comma
l_string|&quot;PowerBook Duo 280c&quot;
comma
id|MAC_ADB_PB2
comma
id|MAC_VIA_QUADRA
comma
id|MAC_SCSI_QUADRA
comma
id|MAC_IDE_NONE
comma
id|MAC_SCC_QUADRA
comma
id|MAC_ETHER_NONE
comma
id|MAC_NUBUS
)brace
comma
multiline_comment|/*&n;&t; *&t;Other stuff ??&n;&t; */
(brace
op_minus
l_int|1
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|mac_identify
r_void
id|mac_identify
c_func
(paren
r_void
)paren
(brace
r_struct
id|mac_model
op_star
id|m
op_assign
op_amp
id|mac_data_table
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Penguin data useful? */
r_int
id|model
op_assign
id|mac_bi_data.id
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|model
)paren
(brace
multiline_comment|/* no bootinfo model id -&gt; NetBSD booter was used! */
multiline_comment|/* XXX FIXME: breaks for model &gt; 31 */
id|model
op_assign
(paren
id|mac_bi_data.cpuid
op_rshift
l_int|2
)paren
op_amp
l_int|63
suffix:semicolon
id|printk
(paren
l_string|&quot;No bootinfo model ID, using cpuid instead (hey, use Penguin!)&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;Detected Macintosh model: %d &bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
r_while
c_loop
(paren
id|m-&gt;ident
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;ident
op_eq
id|model
)paren
(brace
r_break
suffix:semicolon
)brace
id|m
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m-&gt;ident
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nUnknown macintosh model %d, probably unsupported.&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|model
op_assign
id|MAC_MODEL_Q800
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Defaulting to: Quadra800, model id %d&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Please report this case to linux-mac68k@wave.lm.com&bslash;n&quot;
)paren
suffix:semicolon
id|m
op_assign
op_amp
id|mac_data_table
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|m-&gt;ident
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;ident
op_eq
id|model
)paren
(brace
r_break
suffix:semicolon
)brace
id|m
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|m-&gt;ident
op_eq
op_minus
l_int|1
)paren
(brace
id|mac_boom
c_func
(paren
l_int|5
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Report booter data:&n;&t; */
id|printk
(paren
l_string|&quot; Penguin bootinfo data:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Video: addr 0x%lx row 0x%lx depth %lx dimensions %d x %d&bslash;n&quot;
comma
id|mac_bi_data.videoaddr
comma
id|mac_bi_data.videorow
comma
id|mac_bi_data.videodepth
comma
id|mac_bi_data.dimensions
op_amp
l_int|0xFFFF
comma
id|mac_bi_data.dimensions
op_rshift
l_int|16
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Videological 0x%lx phys. 0x%lx, SCC at 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.videological
comma
id|mac_orig_videoaddr
comma
id|mac_bi_data.sccbase
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Boottime: 0x%lx GMTBias: 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.boottime
comma
id|mac_bi_data.gmtbias
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; Machine ID: %ld CPUid: 0x%lx memory size: 0x%lx &bslash;n&quot;
comma
id|mac_bi_data.id
comma
id|mac_bi_data.cpuid
comma
id|mac_bi_data.memsize
)paren
suffix:semicolon
macro_line|#if 0
id|printk
(paren
l_string|&quot;Ramdisk: addr 0x%lx size 0x%lx&bslash;n&quot;
comma
id|m68k_ramdisk.addr
comma
id|m68k_ramdisk.size
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;Save the pointer&n;&t; */
id|macintosh_config
op_assign
id|m
suffix:semicolon
multiline_comment|/*&n;&t; * TODO: set the various fields in macintosh_config-&gt;hw_present here!&n;&t; */
)brace
DECL|function|mac_report_hardware
r_void
id|mac_report_hardware
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Apple Macintosh %s&bslash;n&quot;
comma
id|macintosh_config-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|mac_get_model
r_static
r_void
id|mac_get_model
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|strcpy
c_func
(paren
id|str
comma
l_string|&quot;Macintosh &quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|str
comma
id|macintosh_config-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 4&n; *  tab-width: 8&n; * End:&n; */
eof
