multiline_comment|/*&n; *  linux/arch/alpha/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_ALPHA_LCA etc */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#ifdef CONFIG_RTC
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
id|setup_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|smp_info
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if 1
DECL|macro|DBG_SRM
macro_line|# define DBG_SRM(args)         printk args
macro_line|#else
DECL|macro|DBG_SRM
macro_line|# define DBG_SRM(args)
macro_line|#endif
DECL|variable|hae
r_struct
id|hae
id|hae
op_assign
(brace
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|HAE_ADDRESS
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
DECL|variable|srm_hae
r_int
r_int
id|srm_hae
suffix:semicolon
macro_line|#endif
DECL|variable|hwrpb
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
multiline_comment|/*&n; * This is setup by the secondary bootstrap loader.  Because&n; * the zero page is zeroed out as soon as the vm system is&n; * initialized, we need to copy things out into a more permanent&n; * place.&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;&t;&t;ZERO_PAGE
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE&t;&t;((char*)(PARAM + 0x0000))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;256
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * The format of &quot;screen_info&quot; is strange, and due to early&n; * i386-setup code. This is just enough to make the console&n; * code think we&squot;re on a VGA color display.&n; */
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
macro_line|#if defined(CONFIG_ALPHA_BOOK1)
multiline_comment|/* the AlphaBook1 has LCD video fixed at 800x600, 37 rows and 100 cols */
l_int|0
comma
l_int|37
comma
multiline_comment|/* orig-x, orig-y */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|100
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|37
comma
multiline_comment|/* orig-video-lines */
l_int|1
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
macro_line|#else
l_int|0
comma
l_int|25
comma
multiline_comment|/* orig-x, orig-y */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|80
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|25
comma
multiline_comment|/* orig-video-lines */
l_int|1
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize Programmable Interval Timers with standard values.  Some&n; * drivers depend on them being initialized (e.g., joystick driver).&n; */
DECL|function|init_pit
r_static
r_void
id|init_pit
(paren
r_void
)paren
(brace
macro_line|#if 0
multiline_comment|/*&n;     * Leave refresh timer alone---nobody should depend on&n;     * a particular value anyway.&n;     */
id|outb
c_func
(paren
l_int|0x54
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* counter 1: refresh timer */
id|outb
c_func
(paren
l_int|0x18
comma
l_int|0x41
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RTC /* setup interval timer if /dev/rtc is being used */
id|outb
c_func
(paren
l_int|0x34
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|outb
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
multiline_comment|/* reserve pit */
macro_line|#else /* RTC */
macro_line|#if !defined(CONFIG_ALPHA_RUFFIAN)
multiline_comment|/* Ruffian depends on the system timer established in MILO!! */
id|outb
c_func
(paren
l_int|0x36
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* counter 0: system timer */
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x40
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x40
)paren
suffix:semicolon
macro_line|#endif /* RUFFIAN */
id|request_region
c_func
(paren
l_int|0x70
comma
l_int|0x10
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
multiline_comment|/* reserve rtc */
macro_line|#endif /* RTC */
id|outb
c_func
(paren
l_int|0xb6
comma
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* counter 2: speaker */
id|outb
c_func
(paren
l_int|0x31
comma
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x13
comma
l_int|0x42
)paren
suffix:semicolon
)brace
DECL|function|find_end_memory
r_static
r_int
r_int
id|find_end_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|high
op_assign
l_int|0
suffix:semicolon
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|INIT_HWRPB-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|INIT_HWRPB
)paren
suffix:semicolon
id|cluster
op_assign
id|memdesc-&gt;cluster
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|memdesc-&gt;numclusters
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|cluster
op_increment
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|high
)paren
id|high
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* round it up to an even number of pages.. */
id|high
op_assign
(paren
id|high
op_plus
id|PAGE_SIZE
)paren
op_amp
(paren
id|PAGE_MASK
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|PAGE_OFFSET
op_plus
id|high
suffix:semicolon
)brace
DECL|function|setup_arch
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
comma
r_int
r_int
op_star
id|memory_start_p
comma
r_int
r_int
op_star
id|memory_end_p
)paren
(brace
r_extern
r_int
id|_end
suffix:semicolon
id|init_pit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FREQ_SELECT
)paren
op_amp
l_int|0x3f
)paren
op_ne
l_int|0x26
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_arch: setting RTC_FREQ to 1024/sec&bslash;n&quot;
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
l_int|0x26
comma
id|RTC_FREQ_SELECT
)paren
suffix:semicolon
)brace
id|hwrpb
op_assign
(paren
r_struct
id|hwrpb_struct
op_star
)paren
(paren
id|IDENT_ADDR
op_plus
id|INIT_HWRPB-&gt;phys_addr
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_ALPHA_TSUNAMI)
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
id|srm_hae
op_assign
op_star
id|hae.reg
suffix:semicolon
multiline_comment|/* save SRM setting for restoration */
id|DBG_SRM
c_func
(paren
(paren
l_string|&quot;setup_arch: old HAE base: 0x%016lx&bslash;n&quot;
comma
id|srm_hae
)paren
)paren
suffix:semicolon
macro_line|#endif /* SRM_SETUP */
id|set_hae
c_func
(paren
id|hae.cache
)paren
suffix:semicolon
multiline_comment|/* sync HAE register w/hae_cache */
macro_line|#endif /* !TSUNAMI */
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
multiline_comment|/* reset enable correctable error reports */
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0802
)paren
suffix:semicolon
multiline_comment|/* sda2 */
id|command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Hack for Jensen... since we&squot;re restricted to 8 or 16 &n;&t; * chars for boot flags depending on the boot mode,&n;&t; * we need some shorthand.  This should do for &n;&t; * installation.  Later we&squot;ll add other abbreviations&n;&t; * as well...&n;&t; */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|COMMAND_LINE
comma
l_string|&quot;INSTALL&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|strcpy
c_func
(paren
id|command_line
comma
l_string|&quot;root=/dev/fd0 load_ramdisk=1&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|command_line
comma
id|COMMAND_LINE
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|saved_command_line
comma
id|COMMAND_LINE
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Command line: %s&bslash;n&quot;
comma
id|command_line
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
op_star
id|memory_start_p
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
op_star
id|memory_end_p
op_assign
id|find_end_memory
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_LCA)
op_star
id|memory_start_p
op_assign
id|lca_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_APECS)
op_star
id|memory_start_p
op_assign
id|apecs_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_CIA)
op_star
id|memory_start_p
op_assign
id|cia_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_PYXIS)
op_star
id|memory_start_p
op_assign
id|pyxis_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_T2)
op_star
id|memory_start_p
op_assign
id|t2_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_TSUNAMI)
op_star
id|memory_start_p
op_assign
id|tsunami_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_MCPCIA)
op_star
id|memory_start_p
op_assign
id|mcpcia_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __SMP__
id|setup_smp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VGA_CONSOLE
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB
multiline_comment|/* Frame buffer device based console */
id|conswitchp
op_assign
op_amp
id|fb_con
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|N
mdefine_line|#define N(a) (sizeof(a)/sizeof(a[0]))
multiline_comment|/* A change was made to the HWRPB via an ECO and the following code tracks&n; * a part of the ECO.  In HWRPB versions less than 5, the ECO was not&n; * implemented in the console firmware.  If it&squot;s revision 5 or greater we can&n; * get the name of the platform as an ASCII string from the HWRPB.  That&squot;s what&n; * this function does.  It checks the revision level and if the string is in&n; * the HWRPB it returns the address of the string--a pointer to the name of the&n; * platform.&n; *&n; * Returns:&n; *      - Pointer to a ASCII string if it&squot;s in the HWRPB&n; *      - Pointer to a blank string if the data is not in the HWRPB.&n; */
r_static
r_char
op_star
DECL|function|platform_string
id|platform_string
c_func
(paren
r_void
)paren
(brace
r_struct
id|dsr_struct
op_star
id|dsr
suffix:semicolon
r_static
r_char
id|unk_system_string
(braket
)braket
op_assign
l_string|&quot;N/A&quot;
suffix:semicolon
multiline_comment|/* Go to the console for the string pointer.&n;         * If the rpb_vers is not 5 or greater the rpb&n;&t; * is old and does not have this data in it.&n;&t; */
r_if
c_cond
(paren
id|hwrpb-&gt;revision
OL
l_int|5
)paren
r_return
(paren
id|unk_system_string
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* The Dynamic System Recognition struct&n;&t;&t; * has the system platform name starting&n;&t;&t; * after the character count of the string.&n;&t;&t; */
id|dsr
op_assign
(paren
(paren
r_struct
id|dsr_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;dsr_offset
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
r_char
op_star
)paren
id|dsr
op_plus
(paren
id|dsr-&gt;sysname_off
op_plus
r_sizeof
(paren
r_int
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|get_sysnames
id|get_sysnames
c_func
(paren
r_int
id|type
comma
r_int
id|variation
comma
r_char
op_star
op_star
id|type_name
comma
r_char
op_star
op_star
id|variation_name
)paren
(brace
r_static
r_char
op_star
id|sys_unknown
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
r_static
r_char
op_star
id|systype_names
(braket
)braket
op_assign
(brace
l_string|&quot;0&quot;
comma
l_string|&quot;ADU&quot;
comma
l_string|&quot;Cobra&quot;
comma
l_string|&quot;Ruby&quot;
comma
l_string|&quot;Flamingo&quot;
comma
l_string|&quot;Mannequin&quot;
comma
l_string|&quot;Jensen&quot;
comma
l_string|&quot;Pelican&quot;
comma
l_string|&quot;Morgan&quot;
comma
l_string|&quot;Sable&quot;
comma
l_string|&quot;Medulla&quot;
comma
l_string|&quot;Noname&quot;
comma
l_string|&quot;Turbolaser&quot;
comma
l_string|&quot;Avanti&quot;
comma
l_string|&quot;Mustang&quot;
comma
l_string|&quot;Alcor&quot;
comma
l_string|&quot;Tradewind&quot;
comma
l_string|&quot;Mikasa&quot;
comma
l_string|&quot;EB64&quot;
comma
l_string|&quot;EB66&quot;
comma
l_string|&quot;EB64+&quot;
comma
l_string|&quot;AlphaBook1&quot;
comma
l_string|&quot;Rawhide&quot;
comma
l_string|&quot;K2&quot;
comma
l_string|&quot;Lynx&quot;
comma
l_string|&quot;XL&quot;
comma
l_string|&quot;EB164&quot;
comma
l_string|&quot;Noritake&quot;
comma
l_string|&quot;Cortex&quot;
comma
l_string|&quot;29&quot;
comma
l_string|&quot;Miata&quot;
comma
l_string|&quot;XXM&quot;
comma
l_string|&quot;Takara&quot;
comma
l_string|&quot;Yukon&quot;
comma
l_string|&quot;Tsunami&quot;
comma
l_string|&quot;Wildfire&quot;
comma
l_string|&quot;CUSCO&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|unofficial_names
(braket
)braket
op_assign
(brace
l_string|&quot;100&quot;
comma
l_string|&quot;Ruffian&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|eb164_names
(braket
)braket
op_assign
(brace
l_string|&quot;EB164&quot;
comma
l_string|&quot;PC164&quot;
comma
l_string|&quot;LX164&quot;
comma
l_string|&quot;SX164&quot;
)brace
suffix:semicolon
r_static
r_int
id|eb164_indices
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
)brace
suffix:semicolon
r_static
r_char
op_star
id|alcor_names
(braket
)braket
op_assign
(brace
l_string|&quot;Alcor&quot;
comma
l_string|&quot;Maverick&quot;
comma
l_string|&quot;Bret&quot;
)brace
suffix:semicolon
r_static
r_int
id|alcor_indices
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|2
)brace
suffix:semicolon
r_static
r_char
op_star
id|eb64p_names
(braket
)braket
op_assign
(brace
l_string|&quot;EB64+&quot;
comma
l_string|&quot;Cabriolet&quot;
comma
l_string|&quot;AlphaPCI64&quot;
)brace
suffix:semicolon
r_static
r_int
id|eb64p_indices
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_float|1.2
)brace
suffix:semicolon
r_static
r_char
op_star
id|eb66_names
(braket
)braket
op_assign
(brace
l_string|&quot;EB66&quot;
comma
l_string|&quot;EB66+&quot;
)brace
suffix:semicolon
r_static
r_int
id|eb66_indices
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
)brace
suffix:semicolon
r_static
r_char
op_star
id|rawhide_names
(braket
)braket
op_assign
(brace
l_string|&quot;Dodge&quot;
comma
l_string|&quot;Wrangler&quot;
comma
l_string|&quot;Durango&quot;
comma
l_string|&quot;Tincup&quot;
comma
l_string|&quot;DaVinci&quot;
)brace
suffix:semicolon
r_static
r_int
id|rawhide_indices
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|3
comma
l_int|3
comma
l_int|4
comma
l_int|4
)brace
suffix:semicolon
r_int
id|member
suffix:semicolon
multiline_comment|/* Restore real CABRIO and EB66+ family names, ie EB64+ and EB66 */
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
id|type
op_assign
op_minus
id|type
suffix:semicolon
multiline_comment|/* If not in the tables, make it UNKNOWN,&n;&t;   else set type name to family */
r_if
c_cond
(paren
id|type
OL
id|N
c_func
(paren
id|systype_names
)paren
)paren
(brace
op_star
id|type_name
op_assign
id|systype_names
(braket
id|type
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|type
OG
id|ST_UNOFFICIAL_BIAS
)paren
op_logical_and
(paren
id|type
op_minus
id|ST_UNOFFICIAL_BIAS
)paren
OL
id|N
c_func
(paren
id|unofficial_names
)paren
)paren
(brace
op_star
id|type_name
op_assign
id|unofficial_names
(braket
id|type
op_minus
id|ST_UNOFFICIAL_BIAS
)braket
suffix:semicolon
)brace
r_else
(brace
op_star
id|type_name
op_assign
id|sys_unknown
suffix:semicolon
op_star
id|variation_name
op_assign
id|sys_unknown
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Set variation to &quot;0&quot;; if variation is zero, done */
op_star
id|variation_name
op_assign
id|systype_names
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|variation
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
id|member
op_assign
(paren
id|variation
op_rshift
l_int|10
)paren
op_amp
l_int|0x3f
suffix:semicolon
multiline_comment|/* member ID is a bit-field */
r_switch
c_cond
(paren
id|type
)paren
(brace
multiline_comment|/* select by family */
r_default
suffix:colon
multiline_comment|/* default to variation &quot;0&quot; for now */
r_break
suffix:semicolon
r_case
id|ST_DEC_EB164
suffix:colon
r_if
c_cond
(paren
id|member
OL
id|N
c_func
(paren
id|eb164_indices
)paren
)paren
op_star
id|variation_name
op_assign
id|eb164_names
(braket
id|eb164_indices
(braket
id|member
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST_DEC_ALCOR
suffix:colon
r_if
c_cond
(paren
id|member
OL
id|N
c_func
(paren
id|alcor_indices
)paren
)paren
op_star
id|variation_name
op_assign
id|alcor_names
(braket
id|alcor_indices
(braket
id|member
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST_DEC_EB64P
suffix:colon
r_if
c_cond
(paren
id|member
OL
id|N
c_func
(paren
id|eb64p_indices
)paren
)paren
op_star
id|variation_name
op_assign
id|eb64p_names
(braket
id|eb64p_indices
(braket
id|member
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST_DEC_EB66
suffix:colon
r_if
c_cond
(paren
id|member
OL
id|N
c_func
(paren
id|eb66_indices
)paren
)paren
op_star
id|variation_name
op_assign
id|eb66_names
(braket
id|eb66_indices
(braket
id|member
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ST_DEC_RAWHIDE
suffix:colon
r_if
c_cond
(paren
id|member
OL
id|N
c_func
(paren
id|rawhide_indices
)paren
)paren
op_star
id|variation_name
op_assign
id|rawhide_names
(braket
id|rawhide_indices
(braket
id|member
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* end family switch */
)brace
multiline_comment|/*&n; * BUFFER is PAGE_SIZE bytes long.&n; */
DECL|function|get_cpuinfo
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_static
r_char
op_star
id|cpu_names
(braket
)braket
op_assign
(brace
l_string|&quot;EV3&quot;
comma
l_string|&quot;EV4&quot;
comma
l_string|&quot;Unknown&quot;
comma
l_string|&quot;LCA4&quot;
comma
l_string|&quot;EV5&quot;
comma
l_string|&quot;EV45&quot;
comma
l_string|&quot;EV56&quot;
comma
l_string|&quot;EV6&quot;
comma
l_string|&quot;PCA56&quot;
comma
l_string|&quot;PCA57&quot;
)brace
suffix:semicolon
r_extern
r_struct
id|unaligned_stat
(brace
r_int
r_int
id|count
comma
id|va
comma
id|pc
suffix:semicolon
)brace
id|unaligned
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|cpu
suffix:semicolon
r_int
r_int
id|cpu_index
suffix:semicolon
r_char
op_star
id|cpu_name
suffix:semicolon
r_char
op_star
id|systype_name
suffix:semicolon
r_char
op_star
id|sysvariation_name
suffix:semicolon
id|cpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
id|cpu_index
op_assign
(paren
r_int
)paren
(paren
id|cpu-&gt;type
op_minus
l_int|1
)paren
suffix:semicolon
id|cpu_name
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
r_if
c_cond
(paren
id|cpu_index
OL
id|N
c_func
(paren
id|cpu_names
)paren
)paren
id|cpu_name
op_assign
id|cpu_names
(braket
id|cpu_index
)braket
suffix:semicolon
id|get_sysnames
c_func
(paren
id|hwrpb-&gt;sys_type
comma
id|hwrpb-&gt;sys_variation
comma
op_amp
id|systype_name
comma
op_amp
id|sysvariation_name
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;CPU&bslash;t&bslash;t&bslash;t: Alpha&bslash;n&quot;
l_string|&quot;CPU model&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;CPU variation&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;CPU revision&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;CPU serial number&bslash;t: %s&bslash;n&quot;
l_string|&quot;system type&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;system variation&bslash;t: %s&bslash;n&quot;
l_string|&quot;system revision&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;system serial number&bslash;t: %s&bslash;n&quot;
l_string|&quot;cycle frequency [Hz]&bslash;t: %lu&bslash;n&quot;
l_string|&quot;timer frequency [Hz]&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;page size [bytes]&bslash;t: %ld&bslash;n&quot;
l_string|&quot;phys. address bits&bslash;t: %ld&bslash;n&quot;
l_string|&quot;max. addr. space #&bslash;t: %ld&bslash;n&quot;
l_string|&quot;BogoMIPS&bslash;t&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;kernel unaligned acc&bslash;t: %ld (pc=%lx,va=%lx)&bslash;n&quot;
l_string|&quot;user unaligned acc&bslash;t: %ld (pc=%lx,va=%lx)&bslash;n&quot;
l_string|&quot;platform string&bslash;t&bslash;t: %s&bslash;n&quot;
macro_line|#ifdef __SMP__
l_string|&quot;%s&quot;
macro_line|#endif
comma
id|cpu_name
comma
id|cpu-&gt;variation
comma
id|cpu-&gt;revision
comma
(paren
r_char
op_star
)paren
id|cpu-&gt;serial_no
comma
id|systype_name
comma
id|sysvariation_name
comma
id|hwrpb-&gt;sys_revision
comma
(paren
r_char
op_star
)paren
id|hwrpb-&gt;ssn
comma
id|hwrpb-&gt;cycle_freq
comma
id|hwrpb-&gt;intr_freq
op_div
l_int|4096
comma
(paren
l_int|100
op_star
id|hwrpb-&gt;intr_freq
op_div
l_int|4096
)paren
op_mod
l_int|100
comma
id|hwrpb-&gt;pagesize
comma
id|hwrpb-&gt;pa_bits
comma
id|hwrpb-&gt;max_asn
comma
id|loops_per_sec
op_div
l_int|500000
comma
(paren
id|loops_per_sec
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|count
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|pc
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|va
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|count
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|pc
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|va
comma
id|platform_string
c_func
(paren
)paren
macro_line|#ifdef __SMP__
comma
id|smp_info
c_func
(paren
)paren
macro_line|#endif
)paren
suffix:semicolon
)brace
eof
