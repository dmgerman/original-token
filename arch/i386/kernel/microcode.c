multiline_comment|/*&n; *&t;Intel CPU Microcode Update driver for Linux&n; *&n; *&t;Copyright (C) 2000 Tigran Aivazian&n; *&n; *&t;This driver allows to upgrade microcode on Intel processors&n; *&t;belonging to IA-32 family - PentiumPro, Pentium II, &n; *&t;Pentium III, Xeon, Pentium 4, etc.&n; *&n; *&t;Reference: Section 8.10 of Volume III, Intel Pentium 4 Manual, &n; *&t;Order Number 245472 or free download from:&n; *&t;&t;&n; *&t;http://developer.intel.com/design/pentium4/manuals/245472.htm&n; *&n; *&t;For more information, go to http://www.urbanmyth.org/microcode&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;1.0&t;16 Feb 2000, Tigran Aivazian &lt;tigran@sco.com&gt;&n; *&t;&t;Initial release.&n; *&t;1.01&t;18 Feb 2000, Tigran Aivazian &lt;tigran@sco.com&gt;&n; *&t;&t;Added read() support + cleanups.&n; *&t;1.02&t;21 Feb 2000, Tigran Aivazian &lt;tigran@sco.com&gt;&n; *&t;&t;Added &squot;device trimming&squot; support. open(O_WRONLY) zeroes&n; *&t;&t;and frees the saved copy of applied microcode.&n; *&t;1.03&t;29 Feb 2000, Tigran Aivazian &lt;tigran@sco.com&gt;&n; *&t;&t;Made to use devfs (/dev/cpu/microcode) + cleanups.&n; *&t;1.04&t;06 Jun 2000, Simon Trimmer &lt;simon@veritas.com&gt;&n; *&t;&t;Added misc device support (now uses both devfs and misc).&n; *&t;&t;Added MICROCODE_IOCFREE ioctl to clear memory.&n; *&t;1.05&t;09 Jun 2000, Simon Trimmer &lt;simon@veritas.com&gt;&n; *&t;&t;Messages for error cases (non intel &amp; no suitable microcode).&n; *&t;1.06&t;03 Aug 2000, Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;&t;Removed -&gt;release(). Removed exclusive open and status bitmap.&n; *&t;&t;Added microcode_rwsem to serialize read()/write()/ioctl().&n; *&t;&t;Removed global kernel lock usage.&n; *&t;1.07&t;07 Sep 2000, Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;&t;Write 0 to 0x8B msr and then cpuid before reading revision,&n; *&t;&t;so that it works even if there were no update done by the&n; *&t;&t;BIOS. Otherwise, reading from 0x8B gives junk (which happened&n; *&t;&t;to be 0 on my machine which is why it worked even when I&n; *&t;&t;disabled update by the BIOS)&n; *&t;&t;Thanks to Eric W. Biederman &lt;ebiederman@lnxi.com&gt; for the fix.&n; *&t;1.08&t;11 Dec 2000, Richard Schaal &lt;richard.schaal@intel.com&gt; and&n; *&t;&t;&t;     Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;&t;Intel Pentium 4 processor support and bugfixes.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|macro|MICROCODE_VERSION
mdefine_line|#define MICROCODE_VERSION &t;&quot;1.08&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Intel CPU (IA-32) microcode update driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tigran Aivazian &lt;tigran@veritas.com&gt;&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|macro|MICRO_DEBUG
mdefine_line|#define MICRO_DEBUG 0
macro_line|#if MICRO_DEBUG
DECL|macro|printf
mdefine_line|#define printf(x...) printk(##x)
macro_line|#else
DECL|macro|printf
mdefine_line|#define printf(x...)
macro_line|#endif
multiline_comment|/* VFS interface */
r_static
r_int
id|microcode_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|microcode_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|microcode_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|microcode_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|do_microcode_update
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|do_update_one
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* read()/write()/ioctl() are serialized on this */
r_static
id|DECLARE_RWSEM
c_func
(paren
id|microcode_rwsem
)paren
suffix:semicolon
DECL|variable|microcode
r_static
r_struct
id|microcode
op_star
id|microcode
suffix:semicolon
multiline_comment|/* array of 2048byte microcode blocks */
DECL|variable|microcode_num
r_static
r_int
r_int
id|microcode_num
suffix:semicolon
multiline_comment|/* number of chunks in microcode */
DECL|variable|mc_applied
r_static
r_char
op_star
id|mc_applied
suffix:semicolon
multiline_comment|/* array of applied microcode blocks */
DECL|variable|mc_fsize
r_static
r_int
r_int
id|mc_fsize
suffix:semicolon
multiline_comment|/* file size of /dev/cpu/microcode */
multiline_comment|/* we share file_operations between misc and devfs mechanisms */
DECL|variable|microcode_fops
r_static
r_struct
id|file_operations
id|microcode_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|microcode_read
comma
id|write
suffix:colon
id|microcode_write
comma
id|ioctl
suffix:colon
id|microcode_ioctl
comma
id|open
suffix:colon
id|microcode_open
comma
)brace
suffix:semicolon
DECL|variable|microcode_dev
r_static
r_struct
id|miscdevice
id|microcode_dev
op_assign
(brace
id|minor
suffix:colon
id|MICROCODE_MINOR
comma
id|name
suffix:colon
l_string|&quot;microcode&quot;
comma
id|fops
suffix:colon
op_amp
id|microcode_fops
comma
)brace
suffix:semicolon
DECL|variable|devfs_handle
r_static
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
DECL|function|microcode_init
r_static
r_int
id|__init
id|microcode_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|misc_register
c_func
(paren
op_amp
id|microcode_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;microcode: can&squot;t misc_register on minor=%d&bslash;n&quot;
comma
id|MICROCODE_MINOR
)paren
suffix:semicolon
id|devfs_handle
op_assign
id|devfs_register
c_func
(paren
l_int|NULL
comma
l_string|&quot;cpu/microcode&quot;
comma
id|DEVFS_FL_DEFAULT
comma
l_int|0
comma
l_int|0
comma
id|S_IFREG
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|microcode_fops
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devfs_handle
op_eq
l_int|NULL
op_logical_and
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: failed to devfs_register()&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IA-32 Microcode Update Driver: v%s &lt;tigran@veritas.com&gt;&bslash;n&quot;
comma
id|MICROCODE_VERSION
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|microcode_exit
r_static
r_void
id|__exit
id|microcode_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|microcode_dev
)paren
suffix:semicolon
id|devfs_unregister
c_func
(paren
id|devfs_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mc_applied
)paren
id|kfree
c_func
(paren
id|mc_applied
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IA-32 Microcode Update Driver v%s unregistered&bslash;n&quot;
comma
id|MICROCODE_VERSION
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|microcode_init
)paren
id|module_exit
c_func
(paren
id|microcode_exit
)paren
DECL|function|microcode_open
r_static
r_int
id|microcode_open
c_func
(paren
r_struct
id|inode
op_star
id|unused1
comma
r_struct
id|file
op_star
id|unused2
)paren
(brace
r_return
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/*&n; * update_req[cpu].err is set to 1 if update failed on &squot;cpu&squot;, 0 otherwise&n; * if err==0, microcode[update_req[cpu].slot] points to applied block of microcode&n; */
DECL|struct|update_req
r_struct
id|update_req
(brace
DECL|member|err
r_int
id|err
suffix:semicolon
DECL|member|slot
r_int
id|slot
suffix:semicolon
DECL|variable|update_req
)brace
id|update_req
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|do_microcode_update
r_static
r_int
id|do_microcode_update
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|error
op_assign
l_int|0
comma
id|err
suffix:semicolon
r_struct
id|microcode
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
id|smp_call_function
c_func
(paren
id|do_update_one
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: IPI timeout, giving up&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|do_update_one
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
id|err
op_assign
id|update_req
(braket
id|i
)braket
dot
id|err
suffix:semicolon
id|error
op_add_assign
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|m
op_assign
(paren
r_struct
id|microcode
op_star
)paren
id|mc_applied
op_plus
id|i
suffix:semicolon
id|memcpy
c_func
(paren
id|m
comma
op_amp
id|microcode
(braket
id|update_req
(braket
id|i
)braket
dot
id|slot
)braket
comma
r_sizeof
(paren
r_struct
id|microcode
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|do_update_one
r_static
r_void
id|do_update_one
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|cpu_num
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
op_plus
id|cpu_num
suffix:semicolon
r_struct
id|update_req
op_star
id|req
op_assign
id|update_req
op_plus
id|cpu_num
suffix:semicolon
r_int
r_int
id|pf
op_assign
l_int|0
comma
id|val
(braket
l_int|2
)braket
comma
id|rev
comma
id|sig
suffix:semicolon
r_int
id|i
comma
id|found
op_assign
l_int|0
suffix:semicolon
id|req-&gt;err
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* assume update will fail on this cpu */
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
op_logical_or
id|c-&gt;x86
OL
l_int|6
op_logical_or
id|test_bit
c_func
(paren
id|X86_FEATURE_IA64
comma
op_amp
id|c-&gt;x86_capability
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: CPU%d not a capable Intel processor&bslash;n&quot;
comma
id|cpu_num
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sig
op_assign
id|c-&gt;x86_mask
op_plus
(paren
id|c-&gt;x86_model
op_lshift
l_int|4
)paren
op_plus
(paren
id|c-&gt;x86
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86_model
op_ge
l_int|5
)paren
op_logical_or
(paren
id|c-&gt;x86
OG
l_int|6
)paren
)paren
(brace
multiline_comment|/* get processor flags from MSR 0x17 */
id|rdmsr
c_func
(paren
id|MSR_IA32_PLATFORM_ID
comma
id|val
(braket
l_int|0
)braket
comma
id|val
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pf
op_assign
l_int|1
op_lshift
(paren
(paren
id|val
(braket
l_int|1
)braket
op_rshift
l_int|18
)paren
op_amp
l_int|7
)paren
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
id|microcode_num
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|microcode
(braket
id|i
)braket
dot
id|sig
op_eq
id|sig
op_logical_and
id|microcode
(braket
id|i
)braket
dot
id|pf
op_eq
id|pf
op_logical_and
id|microcode
(braket
id|i
)braket
dot
id|ldrver
op_eq
l_int|1
op_logical_and
id|microcode
(braket
id|i
)braket
dot
id|hdrver
op_eq
l_int|1
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Microcode&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Header Revision %d&bslash;n&quot;
comma
id|microcode
(braket
id|i
)braket
dot
id|hdrver
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Date %x/%x/%x&bslash;n&quot;
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|date
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|date
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
comma
(paren
id|microcode
(braket
id|i
)braket
dot
id|date
op_amp
l_int|0xFFFF
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Type %x Family %x Model %x Stepping %x&bslash;n&quot;
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|sig
op_rshift
l_int|12
)paren
op_amp
l_int|0x3
)paren
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|sig
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
)paren
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|sig
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
comma
(paren
(paren
id|microcode
(braket
id|i
)braket
dot
id|sig
op_amp
l_int|0xf
)paren
)paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Checksum %x&bslash;n&quot;
comma
id|microcode
(braket
id|i
)braket
dot
id|cksum
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Loader Revision %x&bslash;n&quot;
comma
id|microcode
(braket
id|i
)braket
dot
id|ldrver
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;   Processor Flags %x&bslash;n&bslash;n&quot;
comma
id|microcode
(braket
id|i
)braket
dot
id|pf
)paren
suffix:semicolon
multiline_comment|/* trick, to work even if there was no prior update by the BIOS */
id|wrmsr
c_func
(paren
id|MSR_IA32_UCODE_REV
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;cpuid&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
multiline_comment|/* get current (on-cpu) revision into rev (ignore val[0]) */
id|rdmsr
c_func
(paren
id|MSR_IA32_UCODE_REV
comma
id|val
(braket
l_int|0
)braket
comma
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|microcode
(braket
id|i
)braket
dot
id|rev
OL
id|rev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: CPU%d not &squot;upgrading&squot; to earlier revision&quot;
l_string|&quot; %d (current=%d)&bslash;n&quot;
comma
id|cpu_num
comma
id|microcode
(braket
id|i
)braket
dot
id|rev
comma
id|rev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|microcode
(braket
id|i
)braket
dot
id|rev
op_eq
id|rev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: CPU%d already up-to-date (revision %d)&bslash;n&quot;
comma
id|cpu_num
comma
id|rev
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_struct
id|microcode
op_star
id|m
op_assign
op_amp
id|microcode
(braket
id|i
)braket
suffix:semicolon
r_int
r_int
op_star
id|sump
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|m
op_plus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|sump
op_ge
(paren
r_int
r_int
op_star
)paren
id|m
)paren
id|sum
op_add_assign
op_star
id|sump
suffix:semicolon
r_if
c_cond
(paren
id|sum
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: CPU%d aborting, &quot;
l_string|&quot;bad checksum&bslash;n&quot;
comma
id|cpu_num
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* write microcode via MSR 0x79 */
id|wrmsr
c_func
(paren
id|MSR_IA32_UCODE_WRITE
comma
(paren
r_int
r_int
)paren
(paren
id|m-&gt;bits
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* serialize */
id|__asm__
id|__volatile__
(paren
l_string|&quot;cpuid&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
comma
l_string|&quot;bx&quot;
comma
l_string|&quot;cx&quot;
comma
l_string|&quot;dx&quot;
)paren
suffix:semicolon
multiline_comment|/* get the current revision from MSR 0x8B */
id|rdmsr
c_func
(paren
id|MSR_IA32_UCODE_REV
comma
id|val
(braket
l_int|0
)braket
comma
id|val
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* notify the caller of success on this cpu */
id|req-&gt;err
op_assign
l_int|0
suffix:semicolon
id|req-&gt;slot
op_assign
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;microcode: CPU%d updated from revision &quot;
l_string|&quot;%d to %d, date=%08x&bslash;n&quot;
comma
id|cpu_num
comma
id|rev
comma
id|val
(braket
l_int|1
)braket
comma
id|m-&gt;date
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: CPU%d no microcode found! (sig=%x, pflags=%d)&bslash;n&quot;
comma
id|cpu_num
comma
id|sig
comma
id|pf
)paren
suffix:semicolon
)brace
)brace
DECL|function|microcode_read
r_static
id|ssize_t
id|microcode_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_ge
id|mc_fsize
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
op_plus
id|len
OG
id|mc_fsize
)paren
id|len
op_assign
id|mc_fsize
op_minus
op_star
id|ppos
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|mc_applied
op_plus
op_star
id|ppos
comma
id|len
)paren
)paren
r_goto
id|out
suffix:semicolon
op_star
id|ppos
op_add_assign
id|len
suffix:semicolon
id|ret
op_assign
id|len
suffix:semicolon
id|out
suffix:colon
id|up_read
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|microcode_write
r_static
id|ssize_t
id|microcode_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|ssize_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|len
op_mod
r_sizeof
(paren
r_struct
id|microcode
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: can only write in N*%d bytes units&bslash;n&quot;
comma
r_sizeof
(paren
r_struct
id|microcode
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mc_applied
)paren
(brace
id|mc_applied
op_assign
id|kmalloc
c_func
(paren
id|smp_num_cpus
op_star
r_sizeof
(paren
r_struct
id|microcode
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mc_applied
)paren
(brace
id|up_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: out of memory for saved microcode&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
id|microcode_num
op_assign
id|len
op_div
r_sizeof
(paren
r_struct
id|microcode
)paren
suffix:semicolon
id|microcode
op_assign
id|vmalloc
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|microcode
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|microcode
comma
id|buf
comma
id|len
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out_fsize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|do_microcode_update
c_func
(paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_fsize
suffix:semicolon
)brace
r_else
(brace
id|mc_fsize
op_assign
id|smp_num_cpus
op_star
r_sizeof
(paren
r_struct
id|microcode
)paren
suffix:semicolon
id|ret
op_assign
(paren
id|ssize_t
)paren
id|len
suffix:semicolon
)brace
id|out_fsize
suffix:colon
id|devfs_set_file_size
c_func
(paren
id|devfs_handle
comma
id|mc_fsize
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|microcode
)paren
suffix:semicolon
id|out_unlock
suffix:colon
id|up_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|microcode_ioctl
r_static
r_int
id|microcode_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MICROCODE_IOCFREE
suffix:colon
id|down_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mc_applied
)paren
(brace
r_int
id|bytes
op_assign
id|smp_num_cpus
op_star
r_sizeof
(paren
r_struct
id|microcode
)paren
suffix:semicolon
id|devfs_set_file_size
c_func
(paren
id|devfs_handle
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mc_applied
)paren
suffix:semicolon
id|mc_applied
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;microcode: freed %d bytes&bslash;n&quot;
comma
id|bytes
)paren
suffix:semicolon
id|mc_fsize
op_assign
l_int|0
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|microcode_rwsem
)paren
suffix:semicolon
r_return
op_minus
id|ENODATA
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;microcode: unknown ioctl cmd=%d&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
