multiline_comment|/*&n; *  linux/drivers/ide/ide_modes.h&n; *&n; *  Copyright (C) 1996  Linus Torvalds, Igor Abramov, and Mark Lord&n; */
macro_line|#ifndef _IDE_MODES_H
DECL|macro|_IDE_MODES_H
mdefine_line|#define _IDE_MODES_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Shared data/functions for determining best PIO mode for an IDE drive.&n; * Most of this stuff originally lived in cmd640.c, and changes to the&n; * ide_pio_blacklist[] table should be made with EXTREME CAUTION to avoid&n; * breaking the fragile cmd640.c support.&n; */
macro_line|#ifdef CONFIG_BLK_DEV_IDE_MODES
multiline_comment|/*&n; * Standard (generic) timings for PIO modes, from ATA2 specification.&n; * These timings are for access to the IDE data port register *only*.&n; * Some drives may specify a mode, while also specifying a different&n; * value for cycle_time (from drive identification data).&n; */
DECL|struct|ide_pio_timings_s
r_typedef
r_struct
id|ide_pio_timings_s
(brace
DECL|member|setup_time
r_int
id|setup_time
suffix:semicolon
multiline_comment|/* Address setup (ns) minimum */
DECL|member|active_time
r_int
id|active_time
suffix:semicolon
multiline_comment|/* Active pulse (ns) minimum */
DECL|member|cycle_time
r_int
id|cycle_time
suffix:semicolon
multiline_comment|/* Cycle time (ns) minimum = (setup + active + recovery) */
DECL|typedef|ide_pio_timings_t
)brace
id|ide_pio_timings_t
suffix:semicolon
DECL|struct|ide_pio_data_s
r_typedef
r_struct
id|ide_pio_data_s
(brace
DECL|member|pio_mode
id|byte
id|pio_mode
suffix:semicolon
DECL|member|use_iordy
id|byte
id|use_iordy
suffix:semicolon
DECL|member|overridden
id|byte
id|overridden
suffix:semicolon
DECL|member|blacklisted
id|byte
id|blacklisted
suffix:semicolon
DECL|member|cycle_time
r_int
r_int
id|cycle_time
suffix:semicolon
DECL|typedef|ide_pio_data_t
)brace
id|ide_pio_data_t
suffix:semicolon
macro_line|#ifndef _IDE_C
r_int
id|ide_scan_pio_blacklist
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
id|byte
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|mode_wanted
comma
id|byte
id|max_mode
comma
id|ide_pio_data_t
op_star
id|d
)paren
suffix:semicolon
r_extern
r_const
id|ide_pio_timings_t
id|ide_pio_timings
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#else /* _IDE_C */
DECL|variable|ide_pio_timings
r_const
id|ide_pio_timings_t
id|ide_pio_timings
(braket
l_int|6
)braket
op_assign
(brace
(brace
l_int|70
comma
l_int|165
comma
l_int|600
)brace
comma
multiline_comment|/* PIO Mode 0 */
(brace
l_int|50
comma
l_int|125
comma
l_int|383
)brace
comma
multiline_comment|/* PIO Mode 1 */
(brace
l_int|30
comma
l_int|100
comma
l_int|240
)brace
comma
multiline_comment|/* PIO Mode 2 */
(brace
l_int|30
comma
l_int|80
comma
l_int|180
)brace
comma
multiline_comment|/* PIO Mode 3 with IORDY */
(brace
l_int|25
comma
l_int|70
comma
l_int|120
)brace
comma
multiline_comment|/* PIO Mode 4 with IORDY */
(brace
l_int|20
comma
l_int|50
comma
l_int|100
)brace
multiline_comment|/* PIO Mode 5 with IORDY (nonstandard) */
)brace
suffix:semicolon
multiline_comment|/*&n; * Black list. Some drives incorrectly report their maximal PIO mode,&n; * at least in respect to CMD640. Here we keep info on some known drives.&n; */
DECL|struct|ide_pio_info
r_static
r_struct
id|ide_pio_info
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|pio
r_int
id|pio
suffix:semicolon
DECL|variable|ide_pio_blacklist
)brace
id|ide_pio_blacklist
(braket
)braket
op_assign
(brace
multiline_comment|/*&t;{ &quot;Conner Peripherals 1275MB - CFS1275A&quot;, 4 }, */
(brace
l_string|&quot;Conner Peripherals 540MB - CFS540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2700&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2540&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2420&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2340&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC2250&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC2200&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC21200&quot;
comma
l_int|4
)brace
comma
(brace
l_string|&quot;WDC AC2120&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;WDC AC2850&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC1270&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC1170&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;WDC AC1210&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;WDC AC280&quot;
comma
l_int|0
)brace
comma
multiline_comment|/*&t;{ &quot;WDC AC21000&quot;, 4 }, */
(brace
l_string|&quot;WDC AC31000&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;WDC AC31200&quot;
comma
l_int|3
)brace
comma
multiline_comment|/*&t;{ &quot;WDC AC31600&quot;, 4 }, */
(brace
l_string|&quot;Maxtor 7131 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7171 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7213 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7245 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7345 AT&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;Maxtor 7546 AT&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;Maxtor 7540 AV&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3121A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3122A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;SAMSUNG SHD-3172A&quot;
comma
l_int|1
)brace
comma
multiline_comment|/*&t;{ &quot;ST51080A&quot;, 4 },&n; *&t;{ &quot;ST51270A&quot;, 4 },&n; *&t;{ &quot;ST31220A&quot;, 4 },&n; *&t;{ &quot;ST31640A&quot;, 4 },&n; *&t;{ &quot;ST32140A&quot;, 4 },&n; *&t;{ &quot;ST3780A&quot;,  4 },&n; */
(brace
l_string|&quot;ST5660A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3660A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3630A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3655A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3391A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;ST3390A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ST3600A&quot;
comma
l_int|1
)brace
comma
(brace
l_string|&quot;ST3290A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ST3144A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;ST3491A&quot;
comma
l_int|1
)brace
comma
multiline_comment|/* reports 3, should be 1 or 2 (depending on */
multiline_comment|/* drive) according to Seagates FIND-ATA program */
(brace
l_string|&quot;QUANTUM ELS127A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM ELS170A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS240A&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;QUANTUM LPS210A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS270A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS365A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LPS540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LIGHTNING 540A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM LIGHTNING 730A&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_540&quot;
comma
l_int|3
)brace
comma
multiline_comment|/* Older Quantum Fireballs don&squot;t work */
(brace
l_string|&quot;QUANTUM FIREBALL_640&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_1080&quot;
comma
l_int|3
)brace
comma
(brace
l_string|&quot;QUANTUM FIREBALL_1280&quot;
comma
l_int|3
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * This routine searches the ide_pio_blacklist for an entry&n; * matching the start/whole of the supplied model name.&n; *&n; * Returns -1 if no match found.&n; * Otherwise returns the recommended PIO mode from ide_pio_blacklist[].&n; */
DECL|function|ide_scan_pio_blacklist
r_int
id|ide_scan_pio_blacklist
(paren
r_char
op_star
id|model
)paren
(brace
r_struct
id|ide_pio_info
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|ide_pio_blacklist
suffix:semicolon
id|p-&gt;name
op_ne
l_int|NULL
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|p-&gt;name
comma
id|model
comma
id|strlen
c_func
(paren
id|p-&gt;name
)paren
)paren
op_eq
l_int|0
)paren
r_return
id|p-&gt;pio
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine returns the recommended PIO settings for a given drive,&n; * based on the drive-&gt;id information and the ide_pio_blacklist[].&n; * This is used by most chipset support modules when &quot;auto-tuning&quot;.&n; */
multiline_comment|/*&n; * Drive PIO mode auto selection&n; */
DECL|function|ide_get_best_pio_mode
id|byte
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
id|mode_wanted
comma
id|byte
id|max_mode
comma
id|ide_pio_data_t
op_star
id|d
)paren
(brace
r_int
id|pio_mode
suffix:semicolon
r_int
id|cycle_time
op_assign
l_int|0
suffix:semicolon
r_int
id|use_iordy
op_assign
l_int|0
suffix:semicolon
r_struct
id|hd_driveid
op_star
id|id
op_assign
id|drive-&gt;id
suffix:semicolon
r_int
id|overridden
op_assign
l_int|0
suffix:semicolon
r_int
id|blacklisted
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mode_wanted
op_ne
l_int|255
)paren
(brace
id|pio_mode
op_assign
id|mode_wanted
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;id
)paren
(brace
id|pio_mode
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pio_mode
op_assign
id|ide_scan_pio_blacklist
c_func
(paren
id|id-&gt;model
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|overridden
op_assign
l_int|1
suffix:semicolon
id|blacklisted
op_assign
l_int|1
suffix:semicolon
id|use_iordy
op_assign
(paren
id|pio_mode
OG
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|pio_mode
op_assign
id|id-&gt;tPIO
suffix:semicolon
r_if
c_cond
(paren
id|pio_mode
OG
l_int|2
)paren
(brace
multiline_comment|/* 2 is maximum allowed tPIO value */
id|pio_mode
op_assign
l_int|2
suffix:semicolon
id|overridden
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
multiline_comment|/* drive implements ATA2? */
r_if
c_cond
(paren
id|id-&gt;capability
op_amp
l_int|8
)paren
(brace
multiline_comment|/* drive supports use_iordy? */
id|use_iordy
op_assign
l_int|1
suffix:semicolon
id|cycle_time
op_assign
id|id-&gt;eide_pio_iordy
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|7
)paren
(brace
id|overridden
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|4
)paren
id|pio_mode
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|id-&gt;eide_pio_modes
op_amp
l_int|2
)paren
id|pio_mode
op_assign
l_int|4
suffix:semicolon
r_else
id|pio_mode
op_assign
l_int|3
suffix:semicolon
)brace
)brace
r_else
(brace
id|cycle_time
op_assign
id|id-&gt;eide_pio
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|drive-&gt;id-&gt;major_rev_num
op_amp
l_int|0x0004
)paren
id|printf
c_func
(paren
l_string|&quot;ATA-2 &quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Conservative &quot;downgrade&quot; for all pre-ATA2 drives&n;&t;&t; */
r_if
c_cond
(paren
id|pio_mode
op_logical_and
id|pio_mode
OL
l_int|4
)paren
(brace
id|pio_mode
op_decrement
suffix:semicolon
id|overridden
op_assign
l_int|1
suffix:semicolon
macro_line|#if 0
id|use_iordy
op_assign
(paren
id|pio_mode
OG
l_int|2
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|cycle_time
op_logical_and
id|cycle_time
OL
id|ide_pio_timings
(braket
id|pio_mode
)braket
dot
id|cycle_time
)paren
id|cycle_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* use standard timing */
)brace
)brace
r_if
c_cond
(paren
id|pio_mode
OG
id|max_mode
)paren
(brace
id|pio_mode
op_assign
id|max_mode
suffix:semicolon
id|cycle_time
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
)paren
(brace
id|d-&gt;pio_mode
op_assign
id|pio_mode
suffix:semicolon
id|d-&gt;cycle_time
op_assign
id|cycle_time
ques
c_cond
id|cycle_time
suffix:colon
id|ide_pio_timings
(braket
id|pio_mode
)braket
dot
id|cycle_time
suffix:semicolon
id|d-&gt;use_iordy
op_assign
id|use_iordy
suffix:semicolon
id|d-&gt;overridden
op_assign
id|overridden
suffix:semicolon
id|d-&gt;blacklisted
op_assign
id|blacklisted
suffix:semicolon
)brace
r_return
id|pio_mode
suffix:semicolon
)brace
macro_line|#endif /* _IDE_C */
macro_line|#endif /* CONFIG_BLK_DEV_IDE_MODES */
macro_line|#endif /* _IDE_MODES_H */
eof
