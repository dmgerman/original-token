multiline_comment|/*&n; *      Copyright (C) 1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-proc.c,v $&n; * $Revision: 1.11 $&n; * $Date: 1997/10/24 14:47:37 $&n; *&n; *      This file contains the procfs interface for the&n; *      QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot; for Linux.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_FT_PROC_FS)
multiline_comment|/*  adding proc entries from inside a module is REALLY complicated &n; *  for pre-2.1.28 kernels. I don&squot;t want to care about it.&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VER(1,2,13) /* bail out */
macro_line|#error &bslash;&n;Please disable CONFIG_FT_PROC_FS in &quot;MCONFIG&quot; or upgrade to a newer kernel!
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,16)
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arg) __arg
macro_line|#endif
macro_line|#include &lt;linux/qic117.h&gt;
macro_line|#include &quot;../lowlevel/ftape-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-ctl.h&quot;
macro_line|#include &quot;../lowlevel/ftape-proc.h&quot;
macro_line|#include &quot;../lowlevel/ftape-tracing.h&quot;
r_static
r_int
id|ftape_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,28)
macro_line|#include &lt;asm/segment.h&gt; /* for memcpy_tofs() */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,0)
r_static
r_int
id|ftape_proc_read
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
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
suffix:semicolon
macro_line|#else
r_static
r_int
id|ftape_proc_read
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
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|FT_PROC_REGISTER
mdefine_line|#define FT_PROC_REGISTER(parent, child) proc_register_dynamic(parent, child)
multiline_comment|/*&n; *&t;Structures for interfacing with the /proc filesystem.&n; *&t;Router creates its own directory /proc/net/router with the folowing&n; *&t;entries:&n; *&t;config&t;&t;device configuration&n; *&t;status&t;&t;global device statistics&n; *&t;&lt;device&gt;&t;entry for each WAN device&n; */
multiline_comment|/*&n; *&t;Generic /proc/net/ftape/&lt;file&gt; file and inode operations&n; */
DECL|variable|ftape_proc_fops
r_static
r_struct
id|file_operations
id|ftape_proc_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek   */
id|ftape_proc_read
comma
multiline_comment|/* read&t;   */
l_int|NULL
comma
multiline_comment|/* write   */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select  */
l_int|NULL
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
comma
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|ftape_proc_inode_operations
r_static
r_struct
id|inode_operations
id|ftape_proc_inode_operations
op_assign
(brace
op_amp
id|ftape_proc_fops
comma
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* get_block */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* flushpage */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
multiline_comment|/*&n; * Proc filesystem directory entries.&n; */
DECL|function|ftape_get_info
r_static
r_int
id|ftape_get_info
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
id|dummy
)paren
(brace
r_int
id|dummy_eof
suffix:semicolon
r_return
id|ftape_read_proc
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
op_amp
id|dummy_eof
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|proc_ftape
r_static
r_struct
id|proc_dir_entry
id|proc_ftape
op_assign
(brace
l_int|0
comma
multiline_comment|/* low_ino    */
r_sizeof
(paren
l_string|&quot;ftape&quot;
)paren
op_minus
l_int|1
comma
multiline_comment|/* namelen    */
l_string|&quot;ftape&quot;
comma
multiline_comment|/* name       */
id|S_IFREG
op_or
id|S_IRUGO
comma
multiline_comment|/* mode       */
l_int|1
comma
multiline_comment|/* nlink      */
l_int|0
comma
multiline_comment|/* uid        */
l_int|0
comma
multiline_comment|/* gid        */
l_int|0
comma
multiline_comment|/* size       */
op_amp
id|ftape_proc_inode_operations
comma
multiline_comment|/* ops        */
id|ftape_get_info
comma
multiline_comment|/* get_info   */
l_int|NULL
comma
multiline_comment|/* fill_inode */
l_int|NULL
comma
multiline_comment|/* next       */
l_int|NULL
comma
multiline_comment|/* parent     */
l_int|NULL
comma
multiline_comment|/* subdir     */
l_int|NULL
multiline_comment|/* data       */
)brace
suffix:semicolon
multiline_comment|/*  Read ftape proc directory entry.&n; */
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE&t;PAGE_SIZE
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,0)
DECL|function|ftape_proc_read
r_static
r_int
id|ftape_proc_read
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
r_char
op_star
id|buf
comma
r_int
r_int
id|nbytes
)paren
macro_line|#else
r_static
r_int
id|ftape_proc_read
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
r_char
op_star
id|buf
comma
r_int
id|nbytes
)paren
macro_line|#endif
(brace
r_char
op_star
id|page
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|eof
op_assign
l_int|0
suffix:semicolon
r_int
id|n
comma
id|count
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dp
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
(paren
id|nbytes
OG
l_int|0
)paren
op_logical_and
op_logical_neg
id|eof
)paren
(brace
id|count
op_assign
id|PROC_BLOCK_SIZE
op_le
id|nbytes
ques
c_cond
id|PROC_BLOCK_SIZE
suffix:colon
id|nbytes
suffix:semicolon
id|start
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;get_info
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Handle backwards compatibility with the old net&n;&t;&t;&t; * routines.&n;&t;&t;&t; * &n;&t;&t;&t; * XXX What gives with the file-&gt;f_flags &amp; O_ACCMODE&n;&t;&t;&t; * test?  Seems stupid to me....&n;&t;&t;&t; */
id|n
op_assign
id|dp
op_member_access_from_pointer
id|get_info
c_func
(paren
id|page
comma
op_amp
id|start
comma
id|file-&gt;f_pos
comma
id|count
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDWR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|count
)paren
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * For proc files that are less than 4k&n;&t;&t;&t; */
id|start
op_assign
id|page
op_plus
id|file-&gt;f_pos
suffix:semicolon
id|n
op_sub_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|count
)paren
id|n
op_assign
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* End of file */
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
id|retval
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VER(2,1,3)
id|copy_to_user
c_func
(paren
id|buf
comma
id|start
comma
id|n
)paren
suffix:semicolon
macro_line|#else
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|start
comma
id|n
)paren
suffix:semicolon
macro_line|#endif
id|file-&gt;f_pos
op_add_assign
id|n
suffix:semicolon
multiline_comment|/* Move down the file */
id|nbytes
op_sub_assign
id|n
suffix:semicolon
id|buf
op_add_assign
id|n
suffix:semicolon
id|retval
op_add_assign
id|n
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else /* LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,28) */
DECL|macro|FT_PROC_REGISTER
mdefine_line|#define FT_PROC_REGISTER(parent, child) proc_register(parent, child)
multiline_comment|/*&n; * Proc filesystem directory entries.&n; */
DECL|variable|proc_ftape
r_static
r_struct
id|proc_dir_entry
id|proc_ftape
op_assign
(brace
l_int|0
comma
multiline_comment|/* low_ino    */
r_sizeof
(paren
l_string|&quot;ftape&quot;
)paren
op_minus
l_int|1
comma
multiline_comment|/* namelen    */
l_string|&quot;ftape&quot;
comma
multiline_comment|/* name       */
id|S_IFREG
op_or
id|S_IRUGO
comma
multiline_comment|/* mode       */
l_int|1
comma
multiline_comment|/* nlink      */
l_int|0
comma
multiline_comment|/* uid        */
l_int|0
comma
multiline_comment|/* gid        */
l_int|0
comma
multiline_comment|/* size       */
l_int|NULL
comma
multiline_comment|/* ops        */
l_int|NULL
comma
multiline_comment|/* get_info   */
l_int|NULL
comma
multiline_comment|/* fill_inode */
l_int|NULL
comma
multiline_comment|/* next       */
l_int|NULL
comma
multiline_comment|/* parent     */
l_int|NULL
comma
multiline_comment|/* subdir     */
l_int|NULL
comma
multiline_comment|/* data       */
id|ftape_read_proc
comma
multiline_comment|/* read_proc  */
l_int|NULL
multiline_comment|/* write_proc */
)brace
suffix:semicolon
macro_line|#endif
DECL|function|get_driver_info
r_static
r_int
id|get_driver_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_const
r_char
op_star
id|debug_level
(braket
)braket
op_assign
(brace
l_string|&quot;bugs&quot;
comma
l_string|&quot;errors&quot;
comma
l_string|&quot;warnings&quot;
comma
l_string|&quot;informational&quot;
comma
l_string|&quot;noisy&quot;
comma
l_string|&quot;program flow&quot;
comma
l_string|&quot;fdc and dma&quot;
comma
l_string|&quot;data flow&quot;
comma
l_string|&quot;anything&quot;
)brace
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;version       : %s&bslash;n&quot;
l_string|&quot;used data rate: %d kbit/sec&bslash;n&quot;
l_string|&quot;dma memory    : %d kb&bslash;n&quot;
l_string|&quot;debug messages: %s&bslash;n&quot;
comma
id|FTAPE_VERSION
comma
id|ft_data_rate
comma
id|FT_BUFF_SIZE
op_star
id|ft_nr_buffers
op_rshift
l_int|10
comma
id|debug_level
(braket
id|TRACE_LEVEL
)braket
)paren
suffix:semicolon
)brace
DECL|function|get_tapedrive_info
r_static
r_int
id|get_tapedrive_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;vendor id : 0x%04x&bslash;n&quot;
l_string|&quot;drive name: %s&bslash;n&quot;
l_string|&quot;wind speed: %d ips&bslash;n&quot;
l_string|&quot;wakeup    : %s&bslash;n&quot;
l_string|&quot;max. rate : %d kbit/sec&bslash;n&quot;
comma
id|ft_drive_type.vendor_id
comma
id|ft_drive_type.name
comma
id|ft_drive_type.speed
comma
(paren
(paren
id|ft_drive_type.wake_up
op_eq
id|no_wake_up
)paren
ques
c_cond
l_string|&quot;No wakeup needed&quot;
suffix:colon
(paren
(paren
id|ft_drive_type.wake_up
op_eq
id|wake_up_colorado
)paren
ques
c_cond
l_string|&quot;Colorado&quot;
suffix:colon
(paren
(paren
id|ft_drive_type.wake_up
op_eq
id|wake_up_mountain
)paren
ques
c_cond
l_string|&quot;Mountain&quot;
suffix:colon
(paren
(paren
id|ft_drive_type.wake_up
op_eq
id|wake_up_insight
)paren
ques
c_cond
l_string|&quot;Motor on&quot;
suffix:colon
l_string|&quot;Unknown&quot;
)paren
)paren
)paren
)paren
comma
id|ft_drive_max_rate
)paren
suffix:semicolon
)brace
DECL|function|get_cartridge_info
r_static
r_int
id|get_cartridge_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|ftape_init_drive_needed
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;uninitialized&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ft_no_tape
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;no cartridge inserted&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;segments  : %5d&bslash;n&quot;
l_string|&quot;tracks    : %5d&bslash;n&quot;
l_string|&quot;length    : %5dft&bslash;n&quot;
l_string|&quot;formatted : %3s&bslash;n&quot;
l_string|&quot;writable  : %3s&bslash;n&quot;
l_string|&quot;QIC spec. : QIC-%s&bslash;n&quot;
l_string|&quot;fmt-code  : %1d&bslash;n&quot;
comma
id|ft_segments_per_track
comma
id|ft_tracks_per_tape
comma
id|ftape_tape_len
comma
(paren
id|ft_formatted
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|ft_write_protected
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;no&quot;
suffix:colon
l_string|&quot;yes&quot;
comma
(paren
(paren
id|ft_qic_std
op_eq
id|QIC_TAPE_QIC40
)paren
ques
c_cond
l_string|&quot;40&quot;
suffix:colon
(paren
(paren
id|ft_qic_std
op_eq
id|QIC_TAPE_QIC80
)paren
ques
c_cond
l_string|&quot;80&quot;
suffix:colon
(paren
(paren
id|ft_qic_std
op_eq
id|QIC_TAPE_QIC3010
)paren
ques
c_cond
l_string|&quot;3010&quot;
suffix:colon
(paren
(paren
id|ft_qic_std
op_eq
id|QIC_TAPE_QIC3020
)paren
ques
c_cond
l_string|&quot;3020&quot;
suffix:colon
l_string|&quot;???&quot;
)paren
)paren
)paren
)paren
comma
id|ft_format_code
)paren
suffix:semicolon
)brace
DECL|function|get_controller_info
r_static
r_int
id|get_controller_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_const
r_char
op_star
id|fdc_name
(braket
)braket
op_assign
(brace
l_string|&quot;no fdc&quot;
comma
l_string|&quot;i8272&quot;
comma
l_string|&quot;i82077&quot;
comma
l_string|&quot;i82077AA&quot;
comma
l_string|&quot;Colorado FC-10 or FC-20&quot;
comma
l_string|&quot;i82078&quot;
comma
l_string|&quot;i82078_1&quot;
)brace
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;FDC type  : %s&bslash;n&quot;
l_string|&quot;FDC base  : 0x%03x&bslash;n&quot;
l_string|&quot;FDC irq   : %d&bslash;n&quot;
l_string|&quot;FDC dma   : %d&bslash;n&quot;
l_string|&quot;FDC thr.  : %d&bslash;n&quot;
l_string|&quot;max. rate : %d kbit/sec&bslash;n&quot;
comma
id|ft_mach2
ques
c_cond
l_string|&quot;Mountain MACH-2&quot;
suffix:colon
id|fdc_name
(braket
id|fdc.type
)braket
comma
id|fdc.sra
comma
id|fdc.irq
comma
id|fdc.dma
comma
id|ft_fdc_threshold
comma
id|ft_fdc_max_rate
)paren
suffix:semicolon
)brace
DECL|function|get_history_info
r_static
r_int
id|get_history_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nFDC isr statistics&bslash;n&quot;
l_string|&quot; id_am_errors     : %3d&bslash;n&quot;
l_string|&quot; id_crc_errors    : %3d&bslash;n&quot;
l_string|&quot; data_am_errors   : %3d&bslash;n&quot;
l_string|&quot; data_crc_errors  : %3d&bslash;n&quot;
l_string|&quot; overrun_errors   : %3d&bslash;n&quot;
l_string|&quot; no_data_errors   : %3d&bslash;n&quot;
l_string|&quot; retries          : %3d&bslash;n&quot;
comma
id|ft_history.id_am_errors
comma
id|ft_history.id_crc_errors
comma
id|ft_history.data_am_errors
comma
id|ft_history.data_crc_errors
comma
id|ft_history.overrun_errors
comma
id|ft_history.no_data_errors
comma
id|ft_history.retries
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;nECC statistics&bslash;n&quot;
l_string|&quot; crc_errors       : %3d&bslash;n&quot;
l_string|&quot; crc_failures     : %3d&bslash;n&quot;
l_string|&quot; ecc_failures     : %3d&bslash;n&quot;
l_string|&quot; sectors corrected: %3d&bslash;n&quot;
comma
id|ft_history.crc_errors
comma
id|ft_history.crc_failures
comma
id|ft_history.ecc_failures
comma
id|ft_history.corrected
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;ntape quality statistics&bslash;n&quot;
l_string|&quot; media defects    : %3d&bslash;n&quot;
comma
id|ft_history.defects
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;ntape motion statistics&bslash;n&quot;
l_string|&quot; repositions      : %3d&bslash;n&quot;
comma
id|ft_history.rewinds
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|ftape_read_proc
r_int
id|ftape_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|ptr
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
id|ptr
op_add_assign
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;Kernel Driver&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
id|get_driver_info
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;&bslash;nTape Drive&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
id|get_tapedrive_info
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;&bslash;nFDC Controller&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
id|get_controller_info
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;&bslash;nTape Cartridge&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
id|get_cartridge_info
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|ptr
op_add_assign
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;&bslash;nHistory Record&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|ptr
op_add_assign
id|get_history_info
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|page
)paren
suffix:semicolon
op_star
id|start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|off
op_plus
id|count
op_ge
id|len
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
op_star
id|eof
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|ftape_proc_init
c_func
(paren
r_void
)paren
)paren
(brace
r_return
id|FT_PROC_REGISTER
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_ftape
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|ftape_proc_destroy
r_void
id|ftape_proc_destroy
c_func
(paren
r_void
)paren
(brace
id|proc_unregister
c_func
(paren
op_amp
id|proc_root
comma
id|proc_ftape.low_ino
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* defined(CONFIG_PROC_FS) &amp;&amp; defined(CONFIG_FT_PROC_FS) */
eof
