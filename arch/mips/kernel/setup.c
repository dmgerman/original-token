multiline_comment|/*&n; *  linux/arch/mips/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 1995, 1996  Ralf Baechle&n; *  Copyright (C) 1996  Stoned Elipot&n; *&n; * $Id: setup.c,v 1.5 1997/12/06 08:55:42 ralf Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_RTC
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_SGI
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#endif
multiline_comment|/*&n; * How to handle the machine&squot;s features&n; */
DECL|variable|feature
r_struct
id|feature
op_star
id|feature
suffix:semicolon
multiline_comment|/*&n; * What to do to keep the caches consistent with memory&n; * We don&squot;t use the normal cacheflush routine to keep Tyne caches happier.&n; */
DECL|variable|fd_cacheflush
r_void
(paren
op_star
id|fd_cacheflush
)paren
(paren
r_const
r_void
op_star
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * Not all of the MIPS CPUs have the &quot;wait&quot; instruction available.  This&n; * is set to true if it is available.  The wait instruction stops the&n; * pipeline and reduces the power consumption of the CPU very much.&n; */
DECL|variable|wait_available
r_char
id|wait_available
suffix:semicolon
multiline_comment|/*&n; * Do we have a cyclecounter available?&n; */
DECL|variable|cyclecounter_available
r_char
id|cyclecounter_available
suffix:semicolon
multiline_comment|/*&n; * There are several bus types available for MIPS machines.  &quot;RISC PC&quot;&n; * type machines have ISA, EISA, VLB or PCI available, DECstations&n; * have Turbochannel or Q-Bus, SGI has GIO, there are lots of VME&n; * boxes ...&n; * This flag is set if a EISA slots are available.&n; */
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Milo passes some information to the kernel that looks like as if it&n; * had been returned by a Intel PC BIOS.  Milo doesn&squot;t fill the passed&n; * drive_info and Linux can find out about this anyway, so I&squot;m going to&n; * remove this sometime.  screen_info contains information about the &n; * resolution of the text screen.  For VGA graphics based machine this&n; * information is being use to continue the screen output just below&n; * the BIOS printed text and with the same text resolution.&n; */
DECL|variable|drive_info
r_struct
id|drive_info_struct
id|drive_info
op_assign
id|DEFAULT_DRIVE_INFO
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
id|DEFAULT_SCREEN_INFO
suffix:semicolon
multiline_comment|/*&n; * setup informations&n; *&n; * These are intialized so they are in the .data section&n; */
DECL|variable|mips_memory_upper
r_int
r_int
id|mips_memory_upper
op_assign
id|KSEG0
suffix:semicolon
multiline_comment|/* this is set by kernel_entry() */
DECL|variable|mips_cputype
r_int
r_int
id|mips_cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
DECL|variable|mips_machtype
r_int
r_int
id|mips_machtype
op_assign
id|MACH_UNKNOWN
suffix:semicolon
DECL|variable|mips_machgroup
r_int
r_int
id|mips_machgroup
op_assign
id|MACH_GROUP_UNKNOWN
suffix:semicolon
DECL|variable|mips_tlb_entries
r_int
r_int
id|mips_tlb_entries
op_assign
l_int|48
suffix:semicolon
multiline_comment|/* Guess which CPU I&squot;ve got :) */
DECL|variable|mips_vram_base
r_int
r_int
id|mips_vram_base
op_assign
id|KSEG0
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_int
id|_end
suffix:semicolon
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;empty_zero_page
macro_line|#if 0
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
macro_line|#endif
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned char *) (PARAM+0x210))
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START (*(unsigned long *) (PARAM+0x214))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x218))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x21c))
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|CL_SIZE
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
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * The board specific setup routine sets irq_setup to point to a board&n; * specific setup routine.&n; */
DECL|variable|irq_setup
r_void
(paren
op_star
id|irq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * mips_io_port_base is the begin of the address space to which x86 style&n; * I/O ports are mapped.&n; */
DECL|variable|mips_io_port_base
r_int
r_int
id|mips_io_port_base
suffix:semicolon
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is is mapped&n; * for the processor.&n; */
DECL|variable|isa_slot_offset
r_int
r_int
id|isa_slot_offset
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|default_irq_setup
c_func
(paren
r_void
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unknown machtype in init_IRQ&quot;
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|default_fd_cacheflush
c_func
(paren
r_const
r_void
op_star
id|addr
comma
r_int
id|size
)paren
)paren
(brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
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
)paren
(brace
r_int
r_int
id|memory_end
suffix:semicolon
id|tag
op_star
id|atag
suffix:semicolon
r_void
id|decstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|deskstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jazz_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sni_rm200_pci_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sgi_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Perhaps a lot of tags are not getting &squot;snarfed&squot; - */
multiline_comment|/* please help yourself */
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_machtype
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mips_machtype
comma
id|TAGVALPTR
c_func
(paren
id|atag
)paren
comma
id|atag-&gt;size
)paren
suffix:semicolon
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_machgroup
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mips_machgroup
comma
id|TAGVALPTR
c_func
(paren
id|atag
)paren
comma
id|atag-&gt;size
)paren
suffix:semicolon
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_vram_base
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mips_vram_base
comma
id|TAGVALPTR
c_func
(paren
id|atag
)paren
comma
id|atag-&gt;size
)paren
suffix:semicolon
id|irq_setup
op_assign
id|default_irq_setup
suffix:semicolon
id|fd_cacheflush
op_assign
id|default_fd_cacheflush
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machgroup
)paren
(brace
macro_line|#ifdef CONFIG_MIPS_DECSTATION
r_case
id|MACH_GROUP_DEC
suffix:colon
id|decstation_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_MIPS_ARC) 
multiline_comment|/*&n;&t; * Perhaps arch/mips/deskstation should be renamed to arch/mips/arc.&n;&t; * For now CONFIG_MIPS_ARC means DeskStation. -Stoned.&n;&t; */
r_case
id|MACH_GROUP_ARC
suffix:colon
id|deskstation_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_JAZZ
r_case
id|MACH_GROUP_JAZZ
suffix:colon
id|jazz_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI
r_case
id|MACH_GROUP_SGI
suffix:colon
id|sgi_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SNI_RM200_PCI
r_case
id|MACH_GROUP_SNI_RM
suffix:colon
id|sni_rm200_pci_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unsupported architecture&quot;
)paren
suffix:semicolon
)brace
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_drive_info
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|drive_info
comma
id|TAGVALPTR
c_func
(paren
id|atag
)paren
comma
id|atag-&gt;size
)paren
suffix:semicolon
id|memory_end
op_assign
id|mips_memory_upper
suffix:semicolon
multiline_comment|/*&n;&t; * Due to prefetching and similar mechanism the CPU sometimes&n;&t; * generates addresses beyond the end of memory.  We leave the size&n;&t; * of one cache line at the end of memory unused to make shure we&n;&t; * don&squot;t catch this type of bus errors.&n;&t; */
id|memory_end
op_sub_assign
l_int|128
suffix:semicolon
id|memory_end
op_and_assign
id|PAGE_MASK
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
id|rd_image_start
op_assign
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_PROMPT_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|rd_doload
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_mount_root_rdonly
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atag
)paren
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|atag
op_assign
id|bi_TagFind
c_func
(paren
id|tag_command_line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atag
)paren
id|memcpy
c_func
(paren
op_amp
id|command_line
comma
id|TAGVALPTR
c_func
(paren
id|atag
)paren
comma
id|atag-&gt;size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
id|CL_SIZE
)paren
suffix:semicolon
id|saved_command_line
(braket
id|CL_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
id|memory_end
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|LOADER_TYPE
)paren
(brace
id|initrd_start
op_assign
id|INITRD_START
suffix:semicolon
id|initrd_end
op_assign
id|INITRD_START
op_plus
id|INITRD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|initrd_end
OG
id|memory_end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
id|memory_end
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
eof
