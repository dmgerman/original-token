multiline_comment|/*&n; *  linux/kernel/hd.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * This is the low-level hd interrupt support. It traverses the&n; * request-list, using interrupts to jump between functions. As&n; * all the functions are called within interrupts, we may not&n; * sleep. Special care is recommended.&n; * &n; *  modified by Drew Eckhardt to check nr of hd&squot;s from the CMOS.&n; *&n; *  Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug&n; *  in the early extended-partition checks and added DM partitions&n; */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 3
macro_line|#include &quot;blk.h&quot;
DECL|function|CMOS_READ
r_static
r_inline
r_int
r_char
id|CMOS_READ
c_func
(paren
r_int
r_char
id|addr
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x80
op_or
id|addr
comma
l_int|0x70
)paren
suffix:semicolon
r_return
id|inb_p
c_func
(paren
l_int|0x71
)paren
suffix:semicolon
)brace
multiline_comment|/* Max read/write errors/sector */
DECL|macro|MAX_ERRORS
mdefine_line|#define MAX_ERRORS&t;7
DECL|macro|MAX_HD
mdefine_line|#define MAX_HD&t;&t;2
r_static
r_void
id|recal_intr
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|bad_rw_intr
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|recalibrate
r_static
r_int
id|recalibrate
op_assign
l_int|0
suffix:semicolon
DECL|variable|reset
r_static
r_int
id|reset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *  This struct defines the HD&squot;s and their types.&n; */
DECL|struct|hd_i_struct
r_struct
id|hd_i_struct
(brace
DECL|member|head
DECL|member|sect
DECL|member|cyl
DECL|member|wpcom
DECL|member|lzone
DECL|member|ctl
r_int
r_int
id|head
comma
id|sect
comma
id|cyl
comma
id|wpcom
comma
id|lzone
comma
id|ctl
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef HD_TYPE
DECL|variable|hd_info
r_struct
id|hd_i_struct
id|hd_info
(braket
)braket
op_assign
(brace
id|HD_TYPE
)brace
suffix:semicolon
DECL|macro|NR_HD
mdefine_line|#define NR_HD ((sizeof (hd_info))/(sizeof (struct hd_i_struct)))
macro_line|#else
DECL|variable|hd_info
r_struct
id|hd_i_struct
id|hd_info
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|NR_HD
r_static
r_int
id|NR_HD
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|struct|hd_struct
r_static
r_struct
id|hd_struct
(brace
DECL|member|start_sect
r_int
id|start_sect
suffix:semicolon
DECL|member|nr_sects
r_int
id|nr_sects
suffix:semicolon
DECL|variable|hd
)brace
id|hd
(braket
id|MAX_HD
op_lshift
l_int|6
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|hd_sizes
r_static
r_int
id|hd_sizes
(braket
id|MAX_HD
op_lshift
l_int|6
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|macro|port_read
mdefine_line|#define port_read(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;insw&quot;::&quot;d&quot; (port),&quot;D&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;di&quot;)
DECL|macro|port_write
mdefine_line|#define port_write(port,buf,nr) &bslash;&n;__asm__(&quot;cld;rep;outsw&quot;::&quot;d&quot; (port),&quot;S&quot; (buf),&quot;c&quot; (nr):&quot;cx&quot;,&quot;si&quot;)
r_extern
r_void
id|hd_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rd_load
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|current_minor
r_static
r_int
r_int
id|current_minor
suffix:semicolon
multiline_comment|/*&n; * Create devices for each logical partition in an extended partition.&n; * The logical partitions form a linked list, with each entry being&n; * a partition table with two entries.  The first entry&n; * is the real data partition (with a start relative to the partition&n; * table start).  The second is a pointer to the next logical partition&n; * (with a start relative to the entire extended partition).&n; * We do not create a Linux partition for the partition tables, but&n; * only for the actual data partitions.&n; */
DECL|function|extended_partition
r_static
r_void
id|extended_partition
c_func
(paren
r_int
r_int
id|dev
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
r_int
id|first_sector
comma
id|this_sector
suffix:semicolon
id|first_sector
op_assign
id|hd
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
dot
id|start_sect
suffix:semicolon
id|this_sector
op_assign
id|first_sector
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
l_int|0x3f
)paren
op_ge
l_int|60
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to read partition table of device %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   * This block is from a device that we&squot;re about to stomp on.&n;&t;   * So make sure nobody thinks this block is usable.&n;&t;   */
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|510
)paren
op_eq
l_int|0xAA55
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Process the first entry, which should be the real&n;&t;&t; * data partition.&n;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_eq
id|EXTENDED_PARTITION
op_logical_or
op_logical_neg
(paren
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* shouldn&squot;t happen */
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|this_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  Logical part %d start %d size %d end %d&bslash;n&bslash;r&quot;
comma
id|current_minor
comma
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
comma
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
comma
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
op_plus
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
id|current_minor
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Process the second entry, which should be a link&n;&t;&t; * to the next logical partition.  Create a minor&n;&t;&t; * for this just long enough to get the next partition&n;&t;&t; * table.  The minor will be reused for the real&n;&t;&t; * data partition.&n;&t;&t; */
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_ne
id|EXTENDED_PARTITION
op_logical_or
op_logical_neg
(paren
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_goto
id|done
suffix:semicolon
multiline_comment|/* no more logicals in this partition */
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|this_sector
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|dev
op_assign
l_int|0x0300
op_or
id|current_minor
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
r_goto
id|done
suffix:semicolon
)brace
id|done
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|check_partition
r_static
r_void
id|check_partition
c_func
(paren
r_int
r_int
id|dev
)paren
(brace
r_int
id|i
comma
id|minor
op_assign
id|current_minor
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|partition
op_star
id|p
suffix:semicolon
r_int
r_int
id|first_sector
suffix:semicolon
id|first_sector
op_assign
id|hd
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
dot
id|start_sect
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|bread
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to read partition table of device %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Drive %d:&bslash;n&bslash;r&quot;
comma
id|minor
op_rshift
l_int|6
)paren
suffix:semicolon
id|current_minor
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* first &quot;extra&quot; minor */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|510
)paren
op_eq
l_int|0xAA55
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|minor
op_increment
comma
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|hd
(braket
id|minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
)paren
)paren
r_continue
suffix:semicolon
id|hd
(braket
id|minor
)braket
dot
id|start_sect
op_assign
id|first_sector
op_plus
id|p-&gt;start_sect
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; part %d start %d size %d end %d &bslash;n&bslash;r&quot;
comma
id|i
comma
id|hd
(braket
id|minor
)braket
dot
id|start_sect
comma
id|hd
(braket
id|minor
)braket
dot
id|nr_sects
comma
id|hd
(braket
id|minor
)braket
dot
id|start_sect
op_plus
id|hd
(braket
id|minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
l_int|0x3f
)paren
op_ge
l_int|60
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sys_ind
op_eq
id|EXTENDED_PARTITION
)paren
(brace
id|extended_partition
c_func
(paren
l_int|0x0300
op_or
id|minor
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * check for Disk Manager partition table&n;&t;&t; */
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
l_int|0xfc
)paren
op_eq
l_int|0x55AA
)paren
(brace
id|p
op_assign
l_int|0x1BE
op_plus
(paren
r_void
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
comma
id|current_minor
op_increment
)paren
(brace
id|p
op_decrement
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_minor
op_amp
l_int|0x3f
)paren
op_ge
l_int|60
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;start_sect
op_logical_and
id|p-&gt;nr_sects
)paren
)paren
r_continue
suffix:semicolon
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
op_assign
id|p-&gt;start_sect
suffix:semicolon
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
op_assign
id|p-&gt;nr_sects
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; DM part %d start %d size %d end %d&bslash;n&bslash;r&quot;
comma
id|current_minor
comma
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
comma
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
comma
id|hd
(braket
id|current_minor
)braket
dot
id|start_sect
op_plus
id|hd
(braket
id|current_minor
)braket
dot
id|nr_sects
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Bad partition table on dev %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/* This may be used only once, enforced by &squot;static int callable&squot; */
DECL|function|sys_setup
r_int
id|sys_setup
c_func
(paren
r_void
op_star
id|BIOS
)paren
(brace
r_static
r_int
id|callable
op_assign
l_int|1
suffix:semicolon
r_int
id|i
comma
id|drive
suffix:semicolon
r_int
r_char
id|cmos_disks
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|callable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|callable
op_assign
l_int|0
suffix:semicolon
macro_line|#ifndef HD_TYPE
r_for
c_loop
(paren
id|drive
op_assign
l_int|0
suffix:semicolon
id|drive
OL
l_int|2
suffix:semicolon
id|drive
op_increment
)paren
(brace
id|hd_info
(braket
id|drive
)braket
dot
id|cyl
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|BIOS
suffix:semicolon
id|hd_info
(braket
id|drive
)braket
dot
id|head
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
(paren
l_int|2
op_plus
id|BIOS
)paren
suffix:semicolon
id|hd_info
(braket
id|drive
)braket
dot
id|wpcom
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
l_int|5
op_plus
id|BIOS
)paren
suffix:semicolon
id|hd_info
(braket
id|drive
)braket
dot
id|ctl
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
(paren
l_int|8
op_plus
id|BIOS
)paren
suffix:semicolon
id|hd_info
(braket
id|drive
)braket
dot
id|lzone
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
l_int|12
op_plus
id|BIOS
)paren
suffix:semicolon
id|hd_info
(braket
id|drive
)braket
dot
id|sect
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
(paren
l_int|14
op_plus
id|BIOS
)paren
suffix:semicolon
id|BIOS
op_add_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;We querry CMOS about hard disks : it could be that &n;&t;&t;we have a SCSI/ESDI/etc controller that is BIOS&n;&t;&t;compatable with ST-506, and thus showing up in our&n;&t;&t;BIOS table, but not register compatable, and therefore&n;&t;&t;not present in CMOS.&n;&n;&t;&t;Furthurmore, we will assume that our ST-506 drives&n;&t;&t;&lt;if any&gt; are the primary drives in the system, and &n;&t;&t;the ones reflected as drive 1 or 2.&n;&n;&t;&t;The first drive is stored in the high nibble of CMOS&n;&t;&t;byte 0x12, the second in the low nibble.  This will be&n;&t;&t;either a 4 bit drive type or 0xf indicating use byte 0x19 &n;&t;&t;for an 8 bit type, drive 1, 0x1a for drive 2 in CMOS.&n;&n;&t;&t;Needless to say, a non-zero value means we have &n;&t;&t;an AT controller hard disk for that drive.&n;&n;&t;&t;&n;&t;*/
r_if
c_cond
(paren
(paren
id|cmos_disks
op_assign
id|CMOS_READ
c_func
(paren
l_int|0x12
)paren
)paren
op_amp
l_int|0xf0
)paren
r_if
c_cond
(paren
id|cmos_disks
op_amp
l_int|0x0f
)paren
id|NR_HD
op_assign
l_int|2
suffix:semicolon
r_else
id|NR_HD
op_assign
l_int|1
suffix:semicolon
r_else
id|NR_HD
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|MAX_HD
op_lshift
l_int|6
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hd
(braket
id|i
)braket
dot
id|start_sect
op_assign
l_int|0
suffix:semicolon
id|hd
(braket
id|i
)braket
dot
id|nr_sects
op_assign
l_int|0
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
id|NR_HD
suffix:semicolon
id|i
op_increment
)paren
id|hd
(braket
id|i
op_lshift
l_int|6
)braket
dot
id|nr_sects
op_assign
id|hd_info
(braket
id|i
)braket
dot
id|head
op_star
id|hd_info
(braket
id|i
)braket
dot
id|sect
op_star
id|hd_info
(braket
id|i
)braket
dot
id|cyl
suffix:semicolon
r_for
c_loop
(paren
id|drive
op_assign
l_int|0
suffix:semicolon
id|drive
OL
id|NR_HD
suffix:semicolon
id|drive
op_increment
)paren
(brace
id|current_minor
op_assign
l_int|1
op_plus
(paren
id|drive
op_lshift
l_int|6
)paren
suffix:semicolon
id|check_partition
c_func
(paren
l_int|0x0300
op_plus
(paren
id|drive
op_lshift
l_int|6
)paren
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
(paren
id|MAX_HD
op_lshift
l_int|6
)paren
suffix:semicolon
id|i
op_increment
)paren
id|hd_sizes
(braket
id|i
)braket
op_assign
id|hd
(braket
id|i
)braket
dot
id|nr_sects
op_rshift
l_int|1
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|hd_sizes
suffix:semicolon
r_if
c_cond
(paren
id|NR_HD
)paren
id|printk
c_func
(paren
l_string|&quot;Partition table%s ok.&bslash;n&bslash;r&quot;
comma
(paren
id|NR_HD
OG
l_int|1
)paren
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|rd_load
c_func
(paren
)paren
suffix:semicolon
id|mount_root
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|controller_ready
r_static
r_int
id|controller_ready
c_func
(paren
r_void
)paren
(brace
r_int
id|retries
op_assign
l_int|100000
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|retries
op_logical_and
(paren
id|inb_p
c_func
(paren
id|HD_STATUS
)paren
op_amp
l_int|0x80
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retries
)paren
id|printk
c_func
(paren
l_string|&quot;controller_ready: status = %02x&bslash;n&bslash;r&quot;
comma
(paren
r_int
r_char
)paren
id|inb_p
c_func
(paren
id|HD_STATUS
)paren
)paren
suffix:semicolon
r_return
(paren
id|retries
)paren
suffix:semicolon
)brace
DECL|function|win_result
r_static
r_int
id|win_result
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
id|inb_p
c_func
(paren
id|HD_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_amp
(paren
id|BUSY_STAT
op_or
id|READY_STAT
op_or
id|WRERR_STAT
op_or
id|SEEK_STAT
op_or
id|ERR_STAT
)paren
)paren
op_eq
(paren
id|READY_STAT
op_or
id|SEEK_STAT
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ok */
r_if
c_cond
(paren
id|i
op_amp
l_int|1
)paren
id|i
op_assign
id|inb
c_func
(paren
id|HD_ERROR
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|hd_out
r_static
r_void
id|hd_out
c_func
(paren
r_int
r_int
id|drive
comma
r_int
r_int
id|nsect
comma
r_int
r_int
id|sect
comma
r_int
r_int
id|head
comma
r_int
r_int
id|cyl
comma
r_int
r_int
id|cmd
comma
r_void
(paren
op_star
id|intr_addr
)paren
(paren
r_void
)paren
)paren
(brace
r_int
r_int
id|port
suffix:semicolon
r_if
c_cond
(paren
id|drive
OG
l_int|1
op_logical_or
id|head
OG
l_int|15
)paren
id|panic
c_func
(paren
l_string|&quot;Trying to write bad sector&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
op_logical_or
op_logical_neg
id|controller_ready
c_func
(paren
)paren
)paren
(brace
id|reset
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|SET_INTR
c_func
(paren
id|intr_addr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|hd_info
(braket
id|drive
)braket
dot
id|ctl
comma
id|HD_CMD
)paren
suffix:semicolon
id|port
op_assign
id|HD_DATA
suffix:semicolon
id|outb_p
c_func
(paren
id|hd_info
(braket
id|drive
)braket
dot
id|wpcom
op_rshift
l_int|2
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|nsect
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|sect
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cyl
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|cyl
op_rshift
l_int|8
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xA0
op_or
(paren
id|drive
op_lshift
l_int|4
)paren
op_or
id|head
comma
op_increment
id|port
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cmd
comma
op_increment
id|port
)paren
suffix:semicolon
)brace
DECL|function|drive_busy
r_static
r_int
id|drive_busy
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
r_char
id|c
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
l_int|500000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
id|inb_p
c_func
(paren
id|HD_STATUS
)paren
suffix:semicolon
id|c
op_and_assign
(paren
id|BUSY_STAT
op_or
id|READY_STAT
op_or
id|SEEK_STAT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
(paren
id|READY_STAT
op_or
id|SEEK_STAT
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;HD controller times out, c=%02x&bslash;n&bslash;r&quot;
comma
id|c
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|reset_controller
r_static
r_void
id|reset_controller
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|outb
c_func
(paren
l_int|4
comma
id|HD_CMD
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
l_int|1000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nop
c_func
(paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|hd_info
(braket
l_int|0
)braket
dot
id|ctl
op_amp
l_int|0x0f
comma
id|HD_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drive_busy
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;HD-controller still busy&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|inb
c_func
(paren
id|HD_ERROR
)paren
)paren
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;HD-controller reset failed: %02x&bslash;n&bslash;r&quot;
comma
id|i
)paren
suffix:semicolon
)brace
DECL|function|reset_hd
r_static
r_void
id|reset_hd
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|i
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
id|reset
)paren
(brace
id|reset
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
id|reset_controller
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|win_result
c_func
(paren
)paren
)paren
(brace
id|bad_rw_intr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_goto
id|repeat
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|NR_HD
)paren
(brace
id|hd_out
c_func
(paren
id|i
comma
id|hd_info
(braket
id|i
)braket
dot
id|sect
comma
id|hd_info
(braket
id|i
)braket
dot
id|sect
comma
id|hd_info
(braket
id|i
)braket
dot
id|head
op_minus
l_int|1
comma
id|hd_info
(braket
id|i
)braket
dot
id|cyl
comma
id|WIN_SPECIFY
comma
op_amp
id|reset_hd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_goto
id|repeat
suffix:semicolon
)brace
r_else
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, don&squot;t know what to do with the unexpected interrupts: on some machines&n; * doing a reset and a retry seems to result in an eternal loop. Right now I&n; * ignore it, and just set the timeout.&n; */
DECL|function|unexpected_hd_interrupt
r_void
id|unexpected_hd_interrupt
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unexpected HD interrupt&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|SET_TIMER
suffix:semicolon
macro_line|#if 0
id|reset
op_assign
l_int|1
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bad_rw_intr
r_static
r_void
id|bad_rw_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|CURRENT
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|CURRENT-&gt;errors
op_ge
id|MAX_ERRORS
)paren
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;errors
OG
id|MAX_ERRORS
op_div
l_int|2
)paren
id|reset
op_assign
l_int|1
suffix:semicolon
r_else
id|recalibrate
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|read_intr
r_static
r_void
id|read_intr
c_func
(paren
r_void
)paren
(brace
id|SET_INTR
c_func
(paren
op_amp
id|read_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|win_result
c_func
(paren
)paren
)paren
(brace
id|SET_INTR
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|bad_rw_intr
c_func
(paren
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|port_read
c_func
(paren
id|HD_DATA
comma
id|CURRENT-&gt;buffer
comma
l_int|256
)paren
suffix:semicolon
id|CURRENT-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|CURRENT-&gt;buffer
op_add_assign
l_int|512
suffix:semicolon
id|CURRENT-&gt;sector
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|CURRENT-&gt;nr_sectors
)paren
r_return
suffix:semicolon
id|SET_INTR
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write_intr
r_static
r_void
id|write_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|win_result
c_func
(paren
)paren
)paren
(brace
id|bad_rw_intr
c_func
(paren
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|CURRENT-&gt;nr_sectors
)paren
(brace
id|CURRENT-&gt;sector
op_increment
suffix:semicolon
id|CURRENT-&gt;buffer
op_add_assign
l_int|512
suffix:semicolon
id|SET_INTR
c_func
(paren
op_amp
id|write_intr
)paren
suffix:semicolon
id|port_write
c_func
(paren
id|HD_DATA
comma
id|CURRENT-&gt;buffer
comma
l_int|256
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|recal_intr
r_static
r_void
id|recal_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|win_result
c_func
(paren
)paren
)paren
id|bad_rw_intr
c_func
(paren
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is another of the error-routines I don&squot;t know what to do with. The&n; * best idea seems to just set reset, and start all over again.&n; */
DECL|function|hd_times_out
r_static
r_void
id|hd_times_out
c_func
(paren
r_void
)paren
(brace
id|do_hd
op_assign
l_int|NULL
suffix:semicolon
id|reset
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CURRENT
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HD timeout&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|CURRENT-&gt;errors
op_ge
id|MAX_ERRORS
)paren
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_hd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_hd_request
r_static
r_void
id|do_hd_request
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|r
suffix:semicolon
r_int
r_int
id|block
comma
id|dev
suffix:semicolon
r_int
r_int
id|sec
comma
id|head
comma
id|cyl
suffix:semicolon
r_int
r_int
id|nsect
suffix:semicolon
id|INIT_REQUEST
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
suffix:semicolon
id|block
op_assign
id|CURRENT-&gt;sector
suffix:semicolon
id|nsect
op_assign
id|CURRENT-&gt;nr_sectors
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
(paren
id|NR_HD
op_lshift
l_int|6
)paren
op_logical_or
id|block
op_plus
id|nsect
OG
id|hd
(braket
id|dev
)braket
dot
id|nr_sects
)paren
(brace
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|block
op_add_assign
id|hd
(braket
id|dev
)braket
dot
id|start_sect
suffix:semicolon
id|dev
op_rshift_assign
l_int|6
suffix:semicolon
id|sec
op_assign
id|block
op_mod
id|hd_info
(braket
id|dev
)braket
dot
id|sect
suffix:semicolon
id|block
op_div_assign
id|hd_info
(braket
id|dev
)braket
dot
id|sect
suffix:semicolon
id|head
op_assign
id|block
op_mod
id|hd_info
(braket
id|dev
)braket
dot
id|head
suffix:semicolon
id|cyl
op_assign
id|block
op_div
id|hd_info
(braket
id|dev
)braket
dot
id|head
suffix:semicolon
id|sec
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
(brace
id|recalibrate
op_assign
l_int|1
suffix:semicolon
id|reset_hd
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recalibrate
)paren
(brace
id|recalibrate
op_assign
l_int|0
suffix:semicolon
id|hd_out
c_func
(paren
id|dev
comma
id|hd_info
(braket
id|dev
)braket
dot
id|sect
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|WIN_RESTORE
comma
op_amp
id|recal_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_goto
id|repeat
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|WRITE
)paren
(brace
id|hd_out
c_func
(paren
id|dev
comma
id|nsect
comma
id|sec
comma
id|head
comma
id|cyl
comma
id|WIN_WRITE
comma
op_amp
id|write_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_goto
id|repeat
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
l_int|10000
op_logical_and
op_logical_neg
(paren
id|r
op_assign
id|inb_p
c_func
(paren
id|HD_STATUS
)paren
op_amp
id|DRQ_STAT
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
(brace
id|bad_rw_intr
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|port_write
c_func
(paren
id|HD_DATA
comma
id|CURRENT-&gt;buffer
comma
l_int|256
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|READ
)paren
(brace
id|hd_out
c_func
(paren
id|dev
comma
id|nsect
comma
id|sec
comma
id|head
comma
id|cyl
comma
id|WIN_READ
comma
op_amp
id|read_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_goto
id|repeat
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;unknown hd-command&quot;
)paren
suffix:semicolon
)brace
DECL|function|hd_ioctl
r_static
r_int
id|hd_ioctl
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
id|hd_geometry
op_star
id|loc
op_assign
(paren
r_void
op_star
)paren
id|arg
suffix:semicolon
r_int
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|loc
op_logical_or
op_logical_neg
id|inode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|NR_HD
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|HDIO_REQ
suffix:colon
id|put_fs_byte
c_func
(paren
id|hd_info
(braket
id|dev
)braket
dot
id|head
comma
(paren
r_char
op_star
)paren
op_amp
id|loc-&gt;heads
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
id|hd_info
(braket
id|dev
)braket
dot
id|sect
comma
(paren
r_char
op_star
)paren
op_amp
id|loc-&gt;sectors
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|hd_info
(braket
id|dev
)braket
dot
id|cyl
comma
(paren
r_int
op_star
)paren
op_amp
id|loc-&gt;cylinders
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|variable|hd_fops
r_static
r_struct
id|file_operations
id|hd_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|block_read
comma
multiline_comment|/* read - general block-dev read */
id|block_write
comma
multiline_comment|/* write - general block-dev write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* close - default */
l_int|NULL
comma
multiline_comment|/* select */
id|hd_ioctl
multiline_comment|/* ioctl */
)brace
suffix:semicolon
DECL|function|hd_init
r_void
id|hd_init
c_func
(paren
r_void
)paren
(brace
id|blk_dev
(braket
id|MAJOR_NR
)braket
dot
id|request_fn
op_assign
id|DEVICE_REQUEST
suffix:semicolon
id|blkdev_fops
(braket
id|MAJOR_NR
)braket
op_assign
op_amp
id|hd_fops
suffix:semicolon
id|set_intr_gate
c_func
(paren
l_int|0x2E
comma
op_amp
id|hd_interrupt
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_amp
l_int|0xfb
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0xA1
)paren
op_amp
l_int|0xbf
comma
l_int|0xA1
)paren
suffix:semicolon
id|timer_table
(braket
id|HD_TIMER
)braket
dot
id|fn
op_assign
id|hd_times_out
suffix:semicolon
)brace
eof
