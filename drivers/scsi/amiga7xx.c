multiline_comment|/*&n; * Detection routine for the NCR53c710 based Amiga SCSI Controllers for Linux.&n; *  &t;&t;Amiga MacroSystemUS WarpEngine SCSI controller.&n; *&t;&t;Amiga Technologies A4000T SCSI controller.&n; *&t;&t;Amiga Technologies/DKB A4091 SCSI controller.&n; *&n; * Written 1997 by Alan Hourihane &lt;alanh@fairlite.demon.co.uk&gt;&n; * plus modifications of the 53c7xx.c driver to support the Amiga.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;53c7xx.h&quot;
macro_line|#include &quot;amiga7xx.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|variable|proc_scsi_amiga7xx
r_struct
id|proc_dir_entry
id|proc_scsi_amiga7xx
op_assign
(brace
id|PROC_SCSI_AMIGA7XX
comma
l_int|8
comma
l_string|&quot;Amiga7xx&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
)brace
suffix:semicolon
DECL|function|amiga7xx_detect
r_int
id|amiga7xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
r_char
id|called
op_assign
l_int|0
suffix:semicolon
r_int
id|key
comma
id|clock
suffix:semicolon
r_int
id|num
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_int
r_int
id|options
suffix:semicolon
r_struct
id|ConfigDev
op_star
id|cd
suffix:semicolon
r_if
c_cond
(paren
id|called
op_logical_or
op_logical_neg
id|MACH_IS_AMIGA
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_dir
op_assign
op_amp
id|proc_scsi_amiga7xx
suffix:semicolon
macro_line|#ifdef CONFIG_WARPENGINE_SCSI
r_if
c_cond
(paren
(paren
id|key
op_assign
id|zorro_find
c_func
(paren
id|MANUF_MACROSYSTEMS
comma
id|PROD_WARP_ENGINE
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
id|cd
op_assign
id|zorro_get_board
c_func
(paren
id|key
)paren
suffix:semicolon
id|address
op_assign
(paren
r_int
r_int
)paren
id|kernel_map
c_func
(paren
(paren
r_int
r_int
)paren
id|cd-&gt;cd_BoardAddr
comma
id|cd-&gt;cd_BoardSize
comma
id|KERNELMAP_NOCACHE_SER
comma
l_int|NULL
)paren
suffix:semicolon
id|options
op_assign
id|OPTION_MEMORY_MAPPED
op_or
id|OPTION_DEBUG_TEST1
op_or
id|OPTION_INTFLY
op_or
id|OPTION_SYNCHRONOUS
op_or
id|OPTION_ALWAYS_SYNCHRONOUS
op_or
id|OPTION_DISCONNECT
suffix:semicolon
id|clock
op_assign
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
(paren
id|u32
)paren
(paren
r_int
r_char
op_star
)paren
(paren
id|address
op_plus
l_int|0x40000
)paren
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|zorro_config_board
c_func
(paren
id|key
comma
l_int|0
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_A4000T_SCSI
r_if
c_cond
(paren
id|AMIGAHW_PRESENT
c_func
(paren
id|A4000_SCSI
)paren
)paren
(brace
id|options
op_assign
id|OPTION_MEMORY_MAPPED
op_or
id|OPTION_DEBUG_TEST1
op_or
id|OPTION_INTFLY
op_or
id|OPTION_SYNCHRONOUS
op_or
id|OPTION_ALWAYS_SYNCHRONOUS
op_or
id|OPTION_DISCONNECT
suffix:semicolon
id|clock
op_assign
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
(paren
id|u32
)paren
(paren
r_int
r_char
op_star
)paren
id|ZTWO_VADDR
c_func
(paren
l_int|0xDD0040
)paren
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_A4091_SCSI
r_while
c_loop
(paren
(paren
id|key
op_assign
id|zorro_find
c_func
(paren
id|MANUF_COMMODORE
comma
id|PROD_A4091
comma
l_int|0
comma
l_int|0
)paren
)paren
op_logical_or
(paren
id|key
op_assign
id|zorro_find
c_func
(paren
id|MANUF_COMMODORE2
comma
id|PROD_A4091_2
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
(brace
id|cd
op_assign
id|zorro_get_board
c_func
(paren
id|key
)paren
suffix:semicolon
id|address
op_assign
(paren
r_int
r_int
)paren
id|kernel_map
c_func
(paren
(paren
r_int
r_int
)paren
id|cd-&gt;cd_BoardAddr
comma
id|cd-&gt;cd_BoardSize
comma
id|KERNELMAP_NOCACHE_SER
comma
l_int|NULL
)paren
suffix:semicolon
id|options
op_assign
id|OPTION_MEMORY_MAPPED
op_or
id|OPTION_DEBUG_TEST1
op_or
id|OPTION_INTFLY
op_or
id|OPTION_SYNCHRONOUS
op_or
id|OPTION_ALWAYS_SYNCHRONOUS
op_or
id|OPTION_DISCONNECT
suffix:semicolon
id|clock
op_assign
l_int|50000000
suffix:semicolon
multiline_comment|/* 50MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
(paren
id|u32
)paren
(paren
r_int
r_char
op_star
)paren
(paren
id|address
op_plus
l_int|0x800000
)paren
comma
l_int|0
comma
id|IRQ_AMIGA_PORTS
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|zorro_config_board
c_func
(paren
id|key
comma
l_int|0
)paren
suffix:semicolon
id|num
op_increment
suffix:semicolon
)brace
macro_line|#endif
id|called
op_assign
l_int|1
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
eof
