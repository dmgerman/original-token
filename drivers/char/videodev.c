multiline_comment|/*&n; * Video capture interface for Linux&n; *&n; *&t;&t;A generic video device interface for the LINUX operating system&n; *&t;&t;using a set of device structures/vectors for low level operations.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; * Author:&t;Alan Cox, &lt;alan@cymru.net&gt;&n; *&n; * Fixes:&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
DECL|macro|VIDEO_NUM_DEVICES
mdefine_line|#define VIDEO_NUM_DEVICES&t;256 
multiline_comment|/*&n; *&t;Active devices &n; */
DECL|variable|video_device
r_static
r_struct
id|video_device
op_star
id|video_device
(braket
id|VIDEO_NUM_DEVICES
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_VIDEO_BT848
r_extern
r_int
id|init_bttv_cards
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_tuner_init
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_SAA5249
r_extern
r_int
id|init_saa_5249
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef CONFIG_VIDEO_CQCAM
r_extern
r_int
id|init_colour_qcams
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_BWQCAM
r_extern
r_int
id|init_bw_qcams
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_PLANB
r_extern
r_int
id|init_planbs
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RADIO_AZTECH
r_extern
r_int
id|aztech_init
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RADIO_RTRACK
r_extern
r_int
id|rtrack_init
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RADIO_SF16FMI
r_extern
r_int
id|fmi_init
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RADIO_MIROPCM20
r_extern
r_int
id|pcm20_init
c_func
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|video_init_list
r_static
r_struct
id|video_init
id|video_init_list
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/*&n; *&t;Read will do some smarts later on. Buffer pin etc.&n; */
DECL|function|video_read
r_static
id|ssize_t
id|video_read
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;read
)paren
(brace
r_return
id|vfl
op_member_access_from_pointer
id|read
c_func
(paren
id|vfl
comma
id|buf
comma
id|count
comma
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Write for now does nothing. No reason it shouldnt do overlay setting&n; *&t;for some boards I guess..&n; */
DECL|function|video_write
r_static
id|ssize_t
id|video_write
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;write
)paren
(brace
r_return
id|vfl
op_member_access_from_pointer
id|write
c_func
(paren
id|vfl
comma
id|buf
comma
id|count
comma
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Poll to see if we&squot;re readable, can probably be used for timing on incoming&n; *  frames, etc..&n; */
DECL|function|video_poll
r_static
r_int
r_int
id|video_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;poll
)paren
(brace
r_return
id|vfl
op_member_access_from_pointer
id|poll
c_func
(paren
id|vfl
comma
id|file
comma
id|wait
)paren
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Open a video device.&n; */
DECL|function|video_open
r_static
r_int
id|video_open
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
)paren
(brace
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_struct
id|video_device
op_star
id|vfl
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|VIDEO_NUM_DEVICES
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|vfl
op_assign
id|video_device
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
r_char
id|modname
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
(paren
id|modname
comma
l_string|&quot;char-major-%d-%d&quot;
comma
id|VIDEO_MAJOR
comma
id|minor
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|vfl
op_assign
id|video_device
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl
op_eq
l_int|NULL
)paren
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vfl-&gt;busy
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|vfl-&gt;busy
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* In case vfl-&gt;open sleeps */
r_if
c_cond
(paren
id|vfl-&gt;open
)paren
(brace
id|err
op_assign
id|vfl
op_member_access_from_pointer
id|open
c_func
(paren
id|vfl
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Tell the device it is open */
r_if
c_cond
(paren
id|err
)paren
(brace
id|vfl-&gt;busy
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Last close of a video for Linux device&n; */
DECL|function|video_release
r_static
r_int
id|video_release
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
)paren
(brace
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;close
)paren
(brace
id|vfl
op_member_access_from_pointer
id|close
c_func
(paren
id|vfl
)paren
suffix:semicolon
)brace
id|vfl-&gt;busy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Question: Should we be able to capture and then seek around the&n; *&t;image ?&n; */
DECL|function|video_lseek
r_static
r_int
r_int
id|video_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|function|video_ioctl
r_static
r_int
id|video_ioctl
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
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_int
id|err
op_assign
id|vfl
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|vfl
comma
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOIOCTLCMD
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;We need to do MMAP support&n; */
DECL|function|video_mmap
r_int
id|video_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|video_device
op_star
id|vfl
op_assign
id|video_device
(braket
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vfl-&gt;mmap
)paren
(brace
r_return
id|vfl
op_member_access_from_pointer
id|mmap
c_func
(paren
id|vfl
comma
(paren
r_char
op_star
)paren
id|vma-&gt;vm_start
comma
(paren
r_int
r_int
)paren
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Video For Linux device drivers request registration here.&n; */
DECL|function|video_register_device
r_int
id|video_register_device
c_func
(paren
r_struct
id|video_device
op_star
id|vfd
comma
r_int
id|type
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|base
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|end
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|VFL_TYPE_GRABBER
suffix:colon
id|base
op_assign
l_int|0
suffix:semicolon
id|end
op_assign
l_int|64
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_VTX
suffix:colon
id|base
op_assign
l_int|192
suffix:semicolon
id|end
op_assign
l_int|224
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_VBI
suffix:colon
id|base
op_assign
l_int|224
suffix:semicolon
id|end
op_assign
l_int|240
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VFL_TYPE_RADIO
suffix:colon
id|base
op_assign
l_int|64
suffix:semicolon
id|end
op_assign
l_int|128
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|base
suffix:semicolon
id|i
OL
id|end
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|video_device
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
id|video_device
(braket
id|i
)braket
op_assign
id|vfd
suffix:semicolon
id|vfd-&gt;minor
op_assign
id|i
suffix:semicolon
multiline_comment|/* The init call may sleep so we book the slot out&n;&t;&t;&t;   then call */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|vfd-&gt;initialize
)paren
(brace
id|err
op_assign
id|vfd
op_member_access_from_pointer
id|initialize
c_func
(paren
id|vfd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|video_device
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Unregister an unused video for linux device&n; */
DECL|function|video_unregister_device
r_void
id|video_unregister_device
c_func
(paren
r_struct
id|video_device
op_star
id|vfd
)paren
(brace
r_if
c_cond
(paren
id|video_device
(braket
id|vfd-&gt;minor
)braket
op_ne
id|vfd
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;vfd: bad unregister&quot;
)paren
suffix:semicolon
)brace
id|video_device
(braket
id|vfd-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|video_fops
r_static
r_struct
id|file_operations
id|video_fops
op_assign
(brace
id|video_lseek
comma
id|video_read
comma
id|video_write
comma
l_int|NULL
comma
multiline_comment|/* readdir */
id|video_poll
comma
multiline_comment|/* poll */
id|video_ioctl
comma
id|video_mmap
comma
id|video_open
comma
l_int|NULL
comma
multiline_comment|/* flush */
id|video_release
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Initialise video for linux&n; */
DECL|function|videodev_init
r_int
id|videodev_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|video_init
op_star
id|vfli
op_assign
id|video_init_list
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Linux video capture interface: v1.00&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
l_string|&quot;video_capture&quot;
comma
op_amp
id|video_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;video_dev: unable to get major %d&bslash;n&quot;
comma
id|VIDEO_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Init kernel installed video drivers&n;&t; */
r_while
c_loop
(paren
id|vfli-&gt;init
op_ne
l_int|NULL
)paren
(brace
id|vfli
op_member_access_from_pointer
id|init
c_func
(paren
id|vfli
)paren
suffix:semicolon
id|vfli
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE&t;&t;
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|videodev_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|VIDEO_MAJOR
comma
l_string|&quot;video_capture&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|video_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|video_register_device
)paren
suffix:semicolon
DECL|variable|video_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|video_unregister_device
)paren
suffix:semicolon
eof
