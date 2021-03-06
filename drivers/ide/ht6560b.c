multiline_comment|/*&n; *  linux/drivers/ide/ht6560b.c&t;&t;Version 0.07&t;Feb  1, 2000&n; *&n; *  Copyright (C) 1995-2000  Linus Torvalds &amp; author (see below)&n; */
multiline_comment|/*&n; *&n; *  Version 0.01        Initial version hacked out of ide.c&n; *&n; *  Version 0.02        Added support for PIO modes, auto-tune&n; *&n; *  Version 0.03        Some cleanups&n; *&n; *  Version 0.05        PIO mode cycle timings auto-tune using bus-speed&n; *&n; *  Version 0.06        Prefetch mode now defaults no OFF. To set&n; *                      prefetch mode OFF/ON use &quot;hdparm -p8/-p9&quot;.&n; *                      Unmask irq is disabled when prefetch mode&n; *                      is enabled.&n; *&n; *  Version 0.07        Trying to fix CD-ROM detection problem.&n; *                      &quot;Prefetch&quot; mode bit OFF for ide disks and&n; *                      ON for anything else.&n; *&n; *&n; *  HT-6560B EIDE-controller support&n; *  To activate controller support use kernel parameter &quot;ide0=ht6560b&quot;.&n; *  Use hdparm utility to enable PIO mode support.&n; *&n; *  Author:    Mikko Ala-Fossi            &lt;maf@iki.fi&gt;&n; *             Jan Evert van Grootheest   &lt;janevert@iae.nl&gt;&n; *&n; *  Try:  http://www.maf.iki.fi/~maf/ht6560b/&n; */
DECL|macro|HT6560B_VERSION
mdefine_line|#define HT6560B_VERSION &quot;v0.07&quot;
DECL|macro|REALLY_SLOW_IO
macro_line|#undef REALLY_SLOW_IO&t;&t;/* most systems can safely undef this */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ide_modes.h&quot;
multiline_comment|/* #define DEBUG */
multiline_comment|/* remove comments for DEBUG messages */
multiline_comment|/*&n; * The special i/o-port that HT-6560B uses to configuration:&n; *    bit0 (0x01): &quot;1&quot; selects secondary interface&n; *    bit2 (0x04): &quot;1&quot; enables FIFO function&n; *    bit5 (0x20): &quot;1&quot; enables prefetched data read function  (???)&n; *&n; * The special i/o-port that HT-6560A uses to configuration:&n; *    bit0 (0x01): &quot;1&quot; selects secondary interface&n; *    bit1 (0x02): &quot;1&quot; enables prefetched data read function&n; *    bit2 (0x04): &quot;0&quot; enables multi-master system&t;      (?)&n; *    bit3 (0x08): &quot;1&quot; 3 cycle time, &quot;0&quot; 2 cycle time&t;      (?)&n; */
DECL|macro|HT_CONFIG_PORT
mdefine_line|#define HT_CONFIG_PORT&t;  0x3e6
DECL|macro|HT_CONFIG
mdefine_line|#define HT_CONFIG(drivea) (byte)(((drivea)-&gt;drive_data &amp; 0xff00) &gt;&gt; 8)
multiline_comment|/*&n; * FIFO + PREFETCH (both a/b-model)&n; */
DECL|macro|HT_CONFIG_DEFAULT
mdefine_line|#define HT_CONFIG_DEFAULT 0x1c /* no prefetch */
multiline_comment|/* #define HT_CONFIG_DEFAULT 0x3c */
multiline_comment|/* with prefetch */
DECL|macro|HT_SECONDARY_IF
mdefine_line|#define HT_SECONDARY_IF&t;  0x01
DECL|macro|HT_PREFETCH_MODE
mdefine_line|#define HT_PREFETCH_MODE  0x20
multiline_comment|/*&n; * ht6560b Timing values:&n; *&n; * I reviewed some assembler source listings of htide drivers and found&n; * out how they setup those cycle time interfacing values, as they at Holtek&n; * call them. IDESETUP.COM that is supplied with the drivers figures out&n; * optimal values and fetches those values to drivers. I found out that&n; * they use IDE_SELECT_REG to fetch timings to the ide board right after&n; * interface switching. After that it was quite easy to add code to&n; * ht6560b.c.&n; *&n; * IDESETUP.COM gave me values 0x24, 0x45, 0xaa, 0xff that worked fine&n; * for hda and hdc. But hdb needed higher values to work, so I guess&n; * that sometimes it is necessary to give higher value than IDESETUP&n; * gives.   [see cmd640.c for an extreme example of this. -ml]&n; *&n; * Perhaps I should explain something about these timing values:&n; * The higher nibble of value is the Recovery Time  (rt) and the lower nibble&n; * of the value is the Active Time  (at). Minimum value 2 is the fastest and&n; * the maximum value 15 is the slowest. Default values should be 15 for both.&n; * So 0x24 means 2 for rt and 4 for at. Each of the drives should have&n; * both values, and IDESETUP gives automatically rt=15 st=15 for CDROMs or&n; * similar. If value is too small there will be all sorts of failures.&n; *&n; * Timing byte consists of&n; *&t;High nibble:  Recovery Cycle Time  (rt)&n; *&t;     The valid values range from 2 to 15. The default is 15.&n; *&n; *&t;Low nibble:   Active Cycle Time&t;   (at)&n; *&t;     The valid values range from 2 to 15. The default is 15.&n; *&n; * You can obtain optimized timing values by running Holtek IDESETUP.COM&n; * for DOS. DOS drivers get their timing values from command line, where&n; * the first value is the Recovery Time and the second value is the&n; * Active Time for each drive. Smaller value gives higher speed.&n; * In case of failures you should probably fall back to a higher value.&n; */
DECL|macro|HT_TIMING
mdefine_line|#define HT_TIMING(drivea) (byte)((drivea)-&gt;drive_data &amp; 0x00ff)
DECL|macro|HT_TIMING_DEFAULT
mdefine_line|#define HT_TIMING_DEFAULT 0xff
multiline_comment|/*&n; * This routine handles interface switching for the peculiar hardware design&n; * on the F.G.I./Holtek HT-6560B VLB IDE interface.&n; * The HT-6560B can only enable one IDE port at a time, and requires a&n; * silly sequence (below) whenever we switch between primary and secondary.&n; */
multiline_comment|/*&n; * This routine is invoked from ide.c to prepare for access to a given drive.&n; */
DECL|function|ht6560b_selectproc
r_static
r_void
id|ht6560b_selectproc
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_static
id|byte
id|current_select
op_assign
l_int|0
suffix:semicolon
r_static
id|byte
id|current_timing
op_assign
l_int|0
suffix:semicolon
id|byte
id|select
comma
id|timing
suffix:semicolon
id|__save_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|__cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
id|select
op_assign
id|HT_CONFIG
c_func
(paren
id|drive
)paren
suffix:semicolon
id|timing
op_assign
id|HT_TIMING
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|select
op_ne
id|current_select
op_logical_or
id|timing
op_ne
id|current_timing
)paren
(brace
id|current_select
op_assign
id|select
suffix:semicolon
id|current_timing
op_assign
id|timing
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;media
op_ne
id|ide_disk
op_logical_or
op_logical_neg
id|drive-&gt;present
)paren
id|select
op_or_assign
id|HT_PREFETCH_MODE
suffix:semicolon
(paren
r_void
)paren
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
suffix:semicolon
(paren
r_void
)paren
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
suffix:semicolon
(paren
r_void
)paren
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
suffix:semicolon
(paren
r_void
)paren
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|select
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set timing for this drive:&n;&t;&t; */
id|outb
c_func
(paren
id|timing
comma
id|IDE_SELECT_REG
)paren
suffix:semicolon
(paren
r_void
)paren
id|inb
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ht6560b: %s: select=%#x timing=%#x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|select
comma
id|timing
)paren
suffix:semicolon
macro_line|#endif
)brace
id|__restore_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* local CPU only */
)brace
multiline_comment|/*&n; * Autodetection and initialization of ht6560b&n; */
DECL|function|try_to_init_ht6560b
r_static
r_int
id|__init
id|try_to_init_ht6560b
c_func
(paren
r_void
)paren
(brace
id|byte
id|orig_value
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Autodetect ht6560b */
r_if
c_cond
(paren
(paren
id|orig_value
op_assign
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
)paren
op_eq
l_int|0xff
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|outb
c_func
(paren
l_int|0x00
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
op_complement
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
)paren
op_amp
l_int|0x3f
)paren
)paren
(brace
id|outb
c_func
(paren
id|orig_value
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
l_int|0x00
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_complement
id|inb
c_func
(paren
id|HT_CONFIG_PORT
)paren
)paren
op_amp
l_int|0x3f
)paren
(brace
id|outb
c_func
(paren
id|orig_value
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ht6560b autodetected&n;&t; */
id|outb
c_func
(paren
id|HT_CONFIG_DEFAULT
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|HT_TIMING_DEFAULT
comma
l_int|0x1f6
)paren
suffix:semicolon
multiline_comment|/* IDE_SELECT_REG */
(paren
r_void
)paren
id|inb
c_func
(paren
l_int|0x1f7
)paren
suffix:semicolon
multiline_comment|/* IDE_STATUS_REG */
id|printk
c_func
(paren
l_string|&quot;&bslash;nht6560b &quot;
id|HT6560B_VERSION
l_string|&quot;: chipset detected and initialized&quot;
macro_line|#ifdef DEBUG
l_string|&quot; with debug enabled&quot;
macro_line|#endif
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|ht_pio2timings
r_static
id|byte
id|ht_pio2timings
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_int
id|active_time
comma
id|recovery_time
suffix:semicolon
r_int
id|active_cycles
comma
id|recovery_cycles
suffix:semicolon
id|ide_pio_data_t
id|d
suffix:semicolon
r_int
id|bus_speed
op_assign
id|system_bus_clock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pio
)paren
(brace
id|pio
op_assign
id|ide_get_best_pio_mode
c_func
(paren
id|drive
comma
id|pio
comma
l_int|5
comma
op_amp
id|d
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Just like opti621.c we try to calculate the&n;&t;&t; *  actual cycle time for recovery and activity&n;&t;&t; *  according system bus speed.&n;&t;&t; */
id|active_time
op_assign
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|active_time
suffix:semicolon
id|recovery_time
op_assign
id|d.cycle_time
op_minus
id|active_time
op_minus
id|ide_pio_timings
(braket
id|pio
)braket
dot
id|setup_time
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Cycle times should be Vesa bus cycles&n;&t;&t; */
id|active_cycles
op_assign
(paren
id|active_time
op_star
id|bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
id|recovery_cycles
op_assign
(paren
id|recovery_time
op_star
id|bus_speed
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Upper and lower limits&n;&t;&t; */
r_if
c_cond
(paren
id|active_cycles
OL
l_int|2
)paren
id|active_cycles
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|recovery_cycles
OL
l_int|2
)paren
id|recovery_cycles
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|active_cycles
OG
l_int|15
)paren
id|active_cycles
op_assign
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|recovery_cycles
OG
l_int|15
)paren
id|recovery_cycles
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0==16 */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ht6560b: drive %s setting pio=%d recovery=%d (%dns) active=%d (%dns)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
comma
id|recovery_cycles
comma
id|recovery_time
comma
id|active_cycles
comma
id|active_time
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|byte
)paren
(paren
(paren
id|recovery_cycles
op_lshift
l_int|4
)paren
op_or
id|active_cycles
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ht6560b: drive %s setting pio=0&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#endif
r_return
id|HT_TIMING_DEFAULT
suffix:semicolon
multiline_comment|/* default setting */
)brace
)brace
multiline_comment|/*&n; *  Enable/Disable so called prefetch mode&n; */
DECL|function|ht_set_prefetch
r_static
r_void
id|ht_set_prefetch
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|t
op_assign
id|HT_PREFETCH_MODE
op_lshift
l_int|8
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
multiline_comment|/*&n;&t; *  Prefetch mode and unmask irq seems to conflict&n;&t; */
r_if
c_cond
(paren
id|state
)paren
(brace
id|drive-&gt;drive_data
op_or_assign
id|t
suffix:semicolon
multiline_comment|/* enable prefetch mode */
id|drive-&gt;no_unmask
op_assign
l_int|1
suffix:semicolon
id|drive-&gt;unmask
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|drive-&gt;drive_data
op_and_assign
op_complement
id|t
suffix:semicolon
multiline_comment|/* disable prefetch mode */
id|drive-&gt;no_unmask
op_assign
l_int|0
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ht6560b: drive %s prefetch mode %sabled&bslash;n&quot;
comma
id|drive-&gt;name
comma
(paren
id|state
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|tune_ht6560b
r_static
r_void
id|tune_ht6560b
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|pio
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|byte
id|timing
suffix:semicolon
r_switch
c_cond
(paren
id|pio
)paren
(brace
r_case
l_int|8
suffix:colon
multiline_comment|/* set prefetch off */
r_case
l_int|9
suffix:colon
multiline_comment|/* set prefetch on */
id|ht_set_prefetch
c_func
(paren
id|drive
comma
id|pio
op_amp
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|timing
op_assign
id|ht_pio2timings
c_func
(paren
id|drive
comma
id|pio
)paren
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
id|drive-&gt;drive_data
op_and_assign
l_int|0xff00
suffix:semicolon
id|drive-&gt;drive_data
op_or_assign
id|timing
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* all CPUs */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ht6560b: drive %s tuned to pio mode %#x timing=%#x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|pio
comma
id|timing
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|init_ht6560b
r_void
id|__init
id|init_ht6560b
(paren
r_void
)paren
(brace
r_int
id|t
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|HT_CONFIG_PORT
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ht6560b: PORT %#x ALREADY IN USE&bslash;n&quot;
comma
id|HT_CONFIG_PORT
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|try_to_init_ht6560b
c_func
(paren
)paren
)paren
(brace
id|request_region
c_func
(paren
id|HT_CONFIG_PORT
comma
l_int|1
comma
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|name
)paren
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|chipset
op_assign
id|ide_ht6560b
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|chipset
op_assign
id|ide_ht6560b
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|selectproc
op_assign
op_amp
id|ht6560b_selectproc
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|selectproc
op_assign
op_amp
id|ht6560b_selectproc
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_ht6560b
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|tuneproc
op_assign
op_amp
id|tune_ht6560b
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* is this needed? */
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|serialized
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* is this needed? */
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|mate
op_assign
op_amp
id|ide_hwifs
(braket
l_int|1
)braket
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|mate
op_assign
op_amp
id|ide_hwifs
(braket
l_int|0
)braket
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|channel
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Setting default configurations for drives&n;&t;&t;&t; */
id|t
op_assign
(paren
id|HT_CONFIG_DEFAULT
op_lshift
l_int|8
)paren
suffix:semicolon
id|t
op_or_assign
id|HT_TIMING_DEFAULT
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|drive_data
op_assign
id|t
suffix:semicolon
id|ide_hwifs
(braket
l_int|0
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|drive_data
op_assign
id|t
suffix:semicolon
id|t
op_or_assign
(paren
id|HT_SECONDARY_IF
op_lshift
l_int|8
)paren
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|0
)braket
dot
id|drive_data
op_assign
id|t
suffix:semicolon
id|ide_hwifs
(braket
l_int|1
)braket
dot
id|drives
(braket
l_int|1
)braket
dot
id|drive_data
op_assign
id|t
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ht6560b: not found&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
