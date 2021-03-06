multiline_comment|/*&n; *  linux/arch/arm/kernel/arch.c&n; *&n; *  Architecture specific fixups.  This is where any&n; *  parameters in the params struct are fixed up, or&n; *  any additional architecture specific information&n; *  is pulled from the params struct.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
DECL|variable|vram_size
r_int
r_int
id|vram_size
suffix:semicolon
r_extern
r_void
id|setup_initrd
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|setup_ramdisk
c_func
(paren
r_int
id|doload
comma
r_int
id|prompt
comma
r_int
id|start
comma
r_int
r_int
id|rd_sz
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_ACORN
DECL|variable|memc_ctrl_reg
r_int
r_int
id|memc_ctrl_reg
suffix:semicolon
DECL|variable|number_mfm_drives
r_int
r_int
id|number_mfm_drives
suffix:semicolon
r_static
r_void
id|__init
DECL|function|fixup_acorn
id|fixup_acorn
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|params
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
r_if
c_cond
(paren
id|machine_is_riscpc
c_func
(paren
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t;&t; * RiscPC can&squot;t handle half-word loads and stores&n;&t;&t; */
id|elf_hwcap
op_and_assign
op_complement
id|HWCAP_HALF
suffix:semicolon
r_switch
c_cond
(paren
id|params-&gt;u1.s.pages_in_vram
)paren
(brace
r_case
l_int|512
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_case
l_int|256
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vram_size
)paren
(brace
id|desc-&gt;video_start
op_assign
l_int|0x02000000
suffix:semicolon
id|desc-&gt;video_end
op_assign
l_int|0x02000000
op_plus
id|vram_size
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
op_assign
id|PHYS_OFFSET
op_plus
(paren
id|i
op_lshift
l_int|26
)paren
suffix:semicolon
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|node
op_assign
l_int|0
suffix:semicolon
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_assign
id|params-&gt;u1.s.pages_in_bank
(braket
id|i
)braket
op_star
id|params-&gt;u1.s.page_size
suffix:semicolon
)brace
id|mi-&gt;nr_banks
op_assign
l_int|4
suffix:semicolon
)brace
id|memc_ctrl_reg
op_assign
id|params-&gt;u1.s.memc_control_reg
suffix:semicolon
id|number_mfm_drives
op_assign
(paren
id|params-&gt;u1.s.adfsdrives
op_rshift
l_int|3
)paren
op_amp
l_int|3
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_RPC
r_extern
r_void
id|__init
id|rpc_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|RISCPC
comma
l_string|&quot;Acorn-RiscPC&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0x03000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x10000100
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|1
)paren
id|FIXUP
c_func
(paren
id|fixup_acorn
)paren
id|MAPIO
c_func
(paren
id|rpc_map_io
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_ARC
id|MACHINE_START
c_func
(paren
id|ARCHIMEDES
comma
l_string|&quot;Acorn-Archimedes&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Dave Gilbert&quot;
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0207c000
)paren
id|FIXUP
c_func
(paren
id|fixup_acorn
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_A5K
id|MACHINE_START
c_func
(paren
id|A5K
comma
l_string|&quot;Acorn-A5000&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x0207c000
)paren
id|FIXUP
c_func
(paren
id|fixup_acorn
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_L7200
r_static
r_void
id|__init
DECL|function|fixup_l7200
id|fixup_l7200
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|params
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
id|mi-&gt;nr_banks
op_assign
l_int|1
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|start
op_assign
id|PHYS_OFFSET
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|size
op_assign
(paren
l_int|32
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|mi-&gt;bank
(braket
l_int|0
)braket
dot
id|node
op_assign
l_int|0
suffix:semicolon
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|setup_ramdisk
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|8192
)paren
suffix:semicolon
id|setup_initrd
c_func
(paren
id|__phys_to_virt
c_func
(paren
l_int|0xf1000000
)paren
comma
l_int|0x00162b0d
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__init
id|l7200_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|L7200
comma
l_string|&quot;LinkUp Systems L7200SDB&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Steve Hill&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xf0000000
comma
l_int|0x80040000
comma
l_int|0xd0000000
)paren
id|FIXUP
c_func
(paren
id|fixup_l7200
)paren
id|MAPIO
c_func
(paren
id|l7200_map_io
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_EBSA110
r_extern
r_void
id|__init
id|ebsa110_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|EBSA110
comma
l_string|&quot;EBSA110&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0xe0000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000400
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|2
)paren
id|SOFT_REBOOT
id|MAPIO
c_func
(paren
id|ebsa110_map_io
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_NEXUSPCI
r_extern
r_void
id|__init
id|nexuspci_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|NEXUSPCI
comma
l_string|&quot;FTV/PCI&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Philip Blundell&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x40000000
comma
l_int|0x10000000
comma
l_int|0xe0000000
)paren
id|MAPIO
c_func
(paren
id|nexuspci_map_io
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_TBOX
r_extern
r_void
id|__init
id|tbox_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|TBOX
comma
l_string|&quot;unknown-TBOX&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Philip Blundell&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x80000000
comma
l_int|0x00400000
comma
l_int|0xe0000000
)paren
id|MAPIO
c_func
(paren
id|tbox_map_io
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CLPS7110
id|MACHINE_START
c_func
(paren
id|CLPS7110
comma
l_string|&quot;CL-PS7110&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Werner Almesberger&quot;
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_ETOILE
id|MACHINE_START
c_func
(paren
id|ETOILE
comma
l_string|&quot;Etoile&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Alex de Vries&quot;
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_LACIE_NAS
id|MACHINE_START
c_func
(paren
id|LACIE_NAS
comma
l_string|&quot;LaCie_NAS&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Benjamin Herrenschmidt&quot;
)paren
id|MACHINE_END
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CLPS7500
r_extern
r_void
id|__init
id|clps7500_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|CLPS7500
comma
l_string|&quot;CL-PS7500&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Philip Blundell&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0x03000000
comma
l_int|0xe0000000
)paren
id|MAPIO
c_func
(paren
id|clps7500_map_io
)paren
id|MACHINE_END
macro_line|#endif
eof
