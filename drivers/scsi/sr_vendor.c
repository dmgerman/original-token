multiline_comment|/* -*-linux-c-*-&n; *&n; * vendor-specific code for SCSI CD-ROM&squot;s goes here.&n; *&n; * This is needed becauce most of the new features (multisession and&n; * the like) are to new to be included into the SCSI-II standard (to&n; * be exact: there is&squot;nt anything in my draft copy).&n; *&n; *   Gerd Knorr &lt;kraxel@cs.tu-berlin.de&gt; &n; *&n; * --------------------------------------------------------------------------&n; *&n; * support for XA/multisession-CD&squot;s&n; * &n; *   - NEC:     Detection and support of multisession CD&squot;s.&n; *     &n; *   - TOSHIBA: Detection and support of multisession CD&squot;s.&n; *              Some XA-Sector tweaking, required for older drives.&n; *&n; *   - SONY:&t;Detection and support of multisession CD&squot;s.&n; *              added by Thomas Quinot &lt;operator@melchior.cuivre.fdn.fr&gt;&n; *&n; *   - PIONEER, HITACHI, PLEXTOR, MATSHITA, TEAC: known to work with SONY code.&n; *&n; *   - HP:&t;Much like SONY, but a little different... (Thomas)&n; *              HP-Writers only ??? Maybe other CD-Writers work with this too ?&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/ucdrom.h&gt;
macro_line|#include &quot;sr.h&quot;
multiline_comment|/* here are some constants to sort the vendors into groups */
DECL|macro|VENDOR_CAN_NOT_HANDLE
mdefine_line|#define VENDOR_CAN_NOT_HANDLE  1   /* don&squot;t know how to handle */
DECL|macro|VENDOR_NEC
mdefine_line|#define VENDOR_NEC             2
DECL|macro|VENDOR_TOSHIBA
mdefine_line|#define VENDOR_TOSHIBA         3
DECL|macro|VENDOR_SONY_LIKE
mdefine_line|#define VENDOR_SONY_LIKE       4   /* much drives are Sony compatible */
DECL|macro|VENDOR_HP
mdefine_line|#define VENDOR_HP              5   /* HP Writers, others too ?? */
macro_line|#if 0
mdefine_line|#define DEBUG
macro_line|#endif
r_void
DECL|function|sr_vendor_init
id|sr_vendor_init
c_func
(paren
r_int
id|minor
)paren
(brace
r_char
op_star
id|vendor
op_assign
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;vendor
suffix:semicolon
r_char
op_star
id|model
op_assign
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;model
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|vendor
comma
l_string|&quot;HP&quot;
comma
l_int|2
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|vendor
comma
l_string|&quot;PHILIPS&quot;
comma
l_int|7
)paren
)paren
op_logical_and
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;type
op_eq
id|TYPE_WORM
)paren
(brace
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
op_assign
id|VENDOR_HP
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|vendor
comma
l_string|&quot;NEC&quot;
comma
l_int|3
)paren
)paren
(brace
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
op_assign
id|VENDOR_NEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:25&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:36&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:83&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:84 &quot;
comma
l_int|16
)paren
)paren
multiline_comment|/* these can&squot;t handle multisession, may hang */
id|scsi_CDs
(braket
id|minor
)braket
dot
id|cdi.mask
op_or_assign
id|CDC_MULTI_SESSION
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|vendor
comma
l_string|&quot;TOSHIBA&quot;
comma
l_int|7
)paren
)paren
(brace
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
op_assign
id|VENDOR_TOSHIBA
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* most drives can handled like sony ones, so we take&n;&t;&t; * it as default */
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
op_assign
id|VENDOR_SONY_LIKE
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sr: using &bslash;&quot;Sony group&bslash;&quot; multisession code&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
multiline_comment|/* small handy function for switching block length using MODE SELECT,&n; * used by sr_read_sector() */
r_static
r_int
DECL|function|set_density_and_blocklength
id|set_density_and_blocklength
c_func
(paren
r_int
id|minor
comma
r_int
r_char
op_star
id|buffer
comma
r_int
id|density
comma
r_int
id|blocklength
)paren
(brace
r_int
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_struct
id|ccs_modesel_head
op_star
id|modesel
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|MODE_SELECT
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
suffix:semicolon
id|cmd
(braket
l_int|4
)braket
op_assign
l_int|12
suffix:semicolon
id|modesel
op_assign
(paren
r_struct
id|ccs_modesel_head
op_star
)paren
id|buffer
suffix:semicolon
id|memset
c_func
(paren
id|modesel
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|modesel
)paren
)paren
suffix:semicolon
id|modesel-&gt;block_desc_length
op_assign
l_int|0x08
suffix:semicolon
id|modesel-&gt;density
op_assign
id|density
suffix:semicolon
id|modesel-&gt;block_length_med
op_assign
(paren
id|blocklength
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|modesel-&gt;block_length_lo
op_assign
id|blocklength
op_amp
l_int|0xff
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
r_sizeof
(paren
op_star
id|modesel
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|rc
)paren
id|printk
c_func
(paren
l_string|&quot;sr: switching blocklength to %d bytes failed&bslash;n&quot;
comma
id|blocklength
)paren
suffix:semicolon
macro_line|#endif
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* read a sector with other than 2048 bytes length &n; * dest is assumed to be allocated with scsi_malloc&n; *&n; * XXX maybe we have to do some locking here.&n; */
r_int
DECL|function|sr_read_sector
id|sr_read_sector
c_func
(paren
r_int
id|minor
comma
r_int
id|lba
comma
r_int
id|blksize
comma
r_int
r_char
op_star
id|dest
)paren
(brace
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* the buffer for the ioctl */
r_int
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_int
id|rc
comma
id|density
suffix:semicolon
id|density
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
op_eq
id|VENDOR_TOSHIBA
)paren
ques
c_cond
l_int|0x83
suffix:colon
l_int|0
suffix:semicolon
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|rc
op_assign
id|set_density_and_blocklength
c_func
(paren
id|minor
comma
id|buffer
comma
id|density
comma
id|blksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
(brace
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_10
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
id|cmd
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|lba
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|lba
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|lba
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_char
)paren
id|lba
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|1
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|dest
comma
id|blksize
)paren
suffix:semicolon
id|set_density_and_blocklength
c_func
(paren
id|minor
comma
id|buffer
comma
id|density
comma
l_int|2048
)paren
suffix:semicolon
)brace
id|scsi_free
c_func
(paren
id|buffer
comma
l_int|512
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* This function gets called after a media change. Checks if the CD is&n;   multisession, asks for offset etc. */
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(x)    ((((int)x &amp; 0xf0) &gt;&gt; 4)*10 + ((int)x &amp; 0x0f))
DECL|function|sr_cd_check
r_int
id|sr_cd_check
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
(brace
r_int
r_int
id|sector
comma
id|min
comma
id|sec
comma
id|frame
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* the buffer for the ioctl */
r_int
r_char
op_star
id|raw_sector
suffix:semicolon
r_int
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_int
id|rc
comma
id|is_xa
comma
id|no_multi
comma
id|minor
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|cdi.mask
op_amp
id|CDC_MULTI_SESSION
)paren
r_return
l_int|0
suffix:semicolon
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|sector
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* the multisession sector offset goes here  */
id|is_xa
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* flag: the CD uses XA-Sectors              */
id|no_multi
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* flag: the drive can&squot;t handle multisession */
id|rc
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
)paren
(brace
r_case
id|VENDOR_NEC
suffix:colon
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
l_int|0xde
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
op_or
l_int|0x03
suffix:semicolon
id|cmd
(braket
l_int|2
)braket
op_assign
l_int|0xb0
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
l_int|0x16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|14
)braket
op_ne
l_int|0
op_logical_and
id|buffer
(braket
l_int|14
)braket
op_ne
l_int|0xb0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr (nec): Hmm, seems the cdrom doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|min
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|sec
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|16
)braket
)paren
suffix:semicolon
id|frame
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|17
)braket
)paren
suffix:semicolon
id|sector
op_assign
id|min
op_star
id|CD_SECS
op_star
id|CD_FRAMES
op_plus
id|sec
op_star
id|CD_FRAMES
op_plus
id|frame
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VENDOR_TOSHIBA
suffix:colon
multiline_comment|/* we request some disc information (is it a XA-CD ?,&n;&t;&t; * where starts the last session ?) */
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
l_int|0xc7
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
op_or
l_int|3
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0x28000002
op_logical_and
op_logical_neg
id|scsi_ioctl
c_func
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device
comma
id|SCSI_IOCTL_TEST_UNIT_READY
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr (toshiba): Hmm, seems the drive doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|min
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sec
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|frame
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sector
op_assign
id|min
op_star
id|CD_SECS
op_star
id|CD_FRAMES
op_plus
id|sec
op_star
id|CD_FRAMES
op_plus
id|frame
suffix:semicolon
r_if
c_cond
(paren
id|sector
)paren
id|sector
op_sub_assign
id|CD_BLOCK_OFFSET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VENDOR_HP
suffix:colon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|0x04
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|buffer
(braket
l_int|2
)braket
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;sr (hp): No finished session&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
multiline_comment|/* Read TOC */
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
id|cmd
(braket
l_int|6
)braket
op_assign
id|rc
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* number of last session */
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|0x0c
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
DECL|macro|STRICT_HP
macro_line|#undef STRICT_HP
macro_line|#ifdef STRICT_HP
id|sector
op_assign
id|buffer
(braket
l_int|11
)braket
op_plus
(paren
id|buffer
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
op_plus
(paren
id|buffer
(braket
l_int|9
)braket
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* HP documentation states that Logical Start Address is&n;&t;&t;   returned as three (!) bytes, and that buffer[8] is&n;&t;&t;   reserved. This is strange, because a LBA usually is&n;&t;&t;   4 bytes long. */
macro_line|#else
id|sector
op_assign
id|buffer
(braket
l_int|11
)braket
op_plus
(paren
id|buffer
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
op_plus
(paren
id|buffer
(braket
l_int|9
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|buffer
(braket
l_int|8
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|VENDOR_SONY_LIKE
suffix:colon
multiline_comment|/* Thomas QUINOT &lt;thomas@melchior.cuivre.fdn.fr&gt; */
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|12
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|buffer
comma
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|buffer
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|buffer
(braket
l_int|1
)braket
OL
l_int|0x0a
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr (sony): Hmm, seems the drive doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sector
op_assign
id|buffer
(braket
l_int|11
)braket
op_plus
(paren
id|buffer
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
op_plus
(paren
id|buffer
(braket
l_int|9
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|buffer
(braket
l_int|8
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|6
)braket
op_le
l_int|1
)paren
(brace
multiline_comment|/* ignore sector offsets from first track */
id|sector
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|VENDOR_CAN_NOT_HANDLE
suffix:colon
id|sector
op_assign
l_int|0
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* should not happen */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sr: unknown vendor code (%i), not initialized ?&bslash;n&quot;
comma
id|scsi_CDs
(braket
id|minor
)braket
dot
id|vendor
)paren
suffix:semicolon
id|sector
op_assign
l_int|0
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|scsi_CDs
(braket
id|minor
)braket
dot
id|xa_flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|CDS_AUDIO
op_ne
id|sr_disk_status
c_func
(paren
id|cdi
)paren
)paren
(brace
multiline_comment|/* read a sector in raw mode to check the sector format */
id|raw_sector
op_assign
(paren
r_int
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
l_int|2048
op_plus
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|sr_read_sector
c_func
(paren
id|minor
comma
id|sector
op_plus
l_int|16
comma
id|CD_FRAMESIZE_RAW1
comma
id|raw_sector
)paren
)paren
(brace
id|is_xa
op_assign
(paren
id|raw_sector
(braket
l_int|3
)braket
op_eq
l_int|0x02
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sector
OG
l_int|0
op_logical_and
op_logical_neg
id|is_xa
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr: broken CD found: It is &quot;
l_string|&quot;multisession, but has&squot;nt XA sectors&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* read a raw sector failed for some reason. */
id|is_xa
op_assign
(paren
id|sector
OG
l_int|0
)paren
suffix:semicolon
)brace
id|scsi_free
c_func
(paren
id|raw_sector
comma
l_int|2048
op_plus
l_int|512
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_else
id|printk
c_func
(paren
l_string|&quot;sr: audio CD found&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|scsi_CDs
(braket
id|minor
)braket
dot
id|ms_offset
op_assign
id|sector
suffix:semicolon
id|scsi_CDs
(braket
id|minor
)braket
dot
id|xa_flag
op_assign
id|is_xa
suffix:semicolon
r_if
c_cond
(paren
id|no_multi
)paren
id|cdi-&gt;mask
op_or_assign
id|CDC_MULTI_SESSION
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sr: multisession offset=%lu, XA=%s&bslash;n&quot;
comma
id|sector
comma
id|is_xa
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
macro_line|#endif
id|scsi_free
c_func
(paren
id|buffer
comma
l_int|512
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
