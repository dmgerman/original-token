multiline_comment|/*&n; *  linux/arch/mips/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Tell us the machine setup..&n; */
DECL|variable|wait_available
r_char
id|wait_available
suffix:semicolon
multiline_comment|/* set if the &quot;wait&quot; instruction available */
multiline_comment|/*&n; * Bus types ..&n; */
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Setup options&n; */
DECL|variable|drive_info
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
r_extern
r_int
id|ramdisk_size
suffix:semicolon
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_int
id|end
suffix:semicolon
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * Initialise this structure so that it will be placed in the&n; * .data section of the object file&n; */
DECL|variable|boot_info
r_struct
id|bootinfo
id|boot_info
op_assign
id|BOOT_INFO
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;empty_zero_page
DECL|macro|EXT_MEM
mdefine_line|#define EXT_MEM (boot_info.memupper)
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (boot_info.drive_info)
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (screen_info)
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (boot_info.mount_root_rdonly)
DECL|macro|RAMDISK_SIZE
mdefine_line|#define RAMDISK_SIZE (boot_info.ramdisk_size)
macro_line|#if 0
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
macro_line|#endif
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE (boot_info.command_line)
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
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_char
id|c
op_assign
l_char|&squot; &squot;
comma
op_star
id|to
op_assign
id|command_line
comma
op_star
id|from
op_assign
id|COMMAND_LINE
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
id|ORIG_ROOT_DEV
)paren
suffix:semicolon
macro_line|#endif
id|drive_info
op_assign
id|DRIVE_INFO
suffix:semicolon
id|screen_info
op_assign
id|SCREEN_INFO
suffix:semicolon
macro_line|#if 0
id|aux_device_present
op_assign
id|AUX_DEVICE_INFO
suffix:semicolon
macro_line|#endif
id|memory_end
op_assign
id|EXT_MEM
suffix:semicolon
id|memory_end
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|ramdisk_size
op_assign
id|RAMDISK_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|MOUNT_ROOT_RDONLY
)paren
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|end
op_minus
id|KERNELBASE
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
op_star
(paren
r_int
r_int
op_star
)paren
id|from
op_eq
op_star
(paren
r_int
r_int
op_star
)paren
l_string|&quot;mem=&quot;
)paren
(brace
id|memory_end
op_assign
id|simple_strtoul
c_func
(paren
id|from
op_plus
l_int|4
comma
op_amp
id|from
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|10
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|20
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
)brace
id|c
op_assign
op_star
(paren
id|from
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|CL_SIZE
op_le
op_increment
id|len
)paren
r_break
suffix:semicolon
op_star
(paren
id|to
op_increment
)paren
op_assign
id|c
suffix:semicolon
)brace
op_star
id|to
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
id|memory_start
suffix:semicolon
op_star
id|memory_end_p
op_assign
id|memory_end
suffix:semicolon
)brace
eof
