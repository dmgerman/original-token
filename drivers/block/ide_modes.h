macro_line|#ifndef _IDE_MODES_H
DECL|macro|_IDE_MODES_H
mdefine_line|#define _IDE_MODES_H
multiline_comment|/*&n; *  linux/drivers/block/ide_modes.h&n; *&n; *  Copyright (C) 1996  Linus Torvalds, Igor Abramov, and Mark Lord&n; */
multiline_comment|/*&n; * Shared data/functions for determining best PIO mode for an IDE drive.&n; * Most of this stuff originally lived in cmd640.c, and changes to the&n; * ide_pio_blacklist[] table should be made with EXTREME CAUTION to avoid&n; * breaking the fragile cmd640.c support.&n; */
macro_line|#if defined(CONFIG_BLK_DEV_CMD640) || defined(CONFIG_IDE_CHIPSETS)
macro_line|#ifndef _IDE_C
r_int
id|ide_scan_pio_blacklist
(paren
r_char
op_star
id|model
)paren
suffix:semicolon
r_int
r_int
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
macro_line|#else /* _IDE_C */
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
multiline_comment|/*&t;{ &quot;WDC AC21200&quot;, 4 }, */
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
l_string|&quot;QUANTUM FIREBALL&quot;
comma
l_int|3
)brace
comma
multiline_comment|/* For models 540/640/1080/1280 */
multiline_comment|/* 1080A works fine in mode4 with triton */
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
multiline_comment|/*&n; * This routine returns the recommended PIO mode for a given drive,&n; * based on the drive-&gt;id information and the ide_pio_blacklist[].&n; * This is used by most chipset support modules when &quot;auto-tuning&quot;.&n; */
DECL|function|ide_get_best_pio_mode
r_int
r_int
id|ide_get_best_pio_mode
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_int
r_int
id|pio
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
r_if
c_cond
(paren
id|id
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|chipset
op_ne
id|ide_cmd640
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;QUANTUM FIREBALL1080A&quot;
comma
id|id-&gt;model
)paren
)paren
id|pio
op_assign
l_int|4
suffix:semicolon
r_else
id|pio
op_assign
id|ide_scan_pio_blacklist
c_func
(paren
id|id-&gt;model
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pio
op_eq
op_minus
l_int|1
)paren
(brace
id|pio
op_assign
(paren
id|id-&gt;tPIO
OL
l_int|2
)paren
ques
c_cond
id|id-&gt;tPIO
suffix:colon
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;field_valid
op_amp
l_int|2
)paren
(brace
id|byte
id|modes
op_assign
id|id-&gt;eide_pio_modes
suffix:semicolon
r_if
c_cond
(paren
id|modes
op_amp
l_int|4
)paren
id|pio
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|modes
op_amp
l_int|2
)paren
id|pio
op_assign
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|modes
op_amp
l_int|1
)paren
id|pio
op_assign
l_int|3
suffix:semicolon
)brace
)brace
)brace
r_return
id|pio
suffix:semicolon
)brace
macro_line|#endif /* _IDE_C */
macro_line|#endif /* defined(CONFIG_BLK_DEV_CMD640) || defined(CONFIG_IDE_CHIPSETS) */
macro_line|#endif /* _IDE_MODES_H */
eof
