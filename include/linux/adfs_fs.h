macro_line|#ifndef _ADFS_FS_H
DECL|macro|_ADFS_FS_H
mdefine_line|#define _ADFS_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Disc Record at disc address 0xc00&n; */
DECL|struct|adfs_discrecord
r_struct
id|adfs_discrecord
(brace
DECL|member|log2secsize
id|__u8
id|log2secsize
suffix:semicolon
DECL|member|secspertrack
id|__u8
id|secspertrack
suffix:semicolon
DECL|member|heads
id|__u8
id|heads
suffix:semicolon
DECL|member|density
id|__u8
id|density
suffix:semicolon
DECL|member|idlen
id|__u8
id|idlen
suffix:semicolon
DECL|member|log2bpmb
id|__u8
id|log2bpmb
suffix:semicolon
DECL|member|skew
id|__u8
id|skew
suffix:semicolon
DECL|member|bootoption
id|__u8
id|bootoption
suffix:semicolon
DECL|member|lowsector
id|__u8
id|lowsector
suffix:semicolon
DECL|member|nzones
id|__u8
id|nzones
suffix:semicolon
DECL|member|zone_spare
id|__u16
id|zone_spare
suffix:semicolon
DECL|member|root
id|__u32
id|root
suffix:semicolon
DECL|member|disc_size
id|__u32
id|disc_size
suffix:semicolon
DECL|member|disc_id
id|__u16
id|disc_id
suffix:semicolon
DECL|member|disc_name
id|__u8
id|disc_name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|disc_type
id|__u32
id|disc_type
suffix:semicolon
DECL|member|disc_size_high
id|__u32
id|disc_size_high
suffix:semicolon
DECL|member|log2sharesize
id|__u8
id|log2sharesize
suffix:colon
l_int|4
suffix:semicolon
DECL|member|unused40
id|__u8
id|unused40
suffix:colon
l_int|4
suffix:semicolon
DECL|member|big_flag
id|__u8
id|big_flag
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused41
id|__u8
id|unused41
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nzones_high
id|__u8
id|nzones_high
suffix:semicolon
DECL|member|format_version
id|__u32
id|format_version
suffix:semicolon
DECL|member|root_size
id|__u32
id|root_size
suffix:semicolon
DECL|member|unused52
id|__u8
id|unused52
(braket
l_int|60
op_minus
l_int|52
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ADFS_DISCRECORD
mdefine_line|#define ADFS_DISCRECORD&t;&t;(0xc00)
DECL|macro|ADFS_DR_OFFSET
mdefine_line|#define ADFS_DR_OFFSET&t;&t;(0x1c0)
DECL|macro|ADFS_DR_SIZE
mdefine_line|#define ADFS_DR_SIZE&t;&t; 60
DECL|macro|ADFS_DR_SIZE_BITS
mdefine_line|#define ADFS_DR_SIZE_BITS&t;(ADFS_DR_SIZE &lt;&lt; 3)
DECL|macro|ADFS_SUPER_MAGIC
mdefine_line|#define ADFS_SUPER_MAGIC&t; 0xadf5
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Calculate the boot block checksum on an ADFS drive.  Note that this will&n; * appear to be correct if the sector contains all zeros, so also check that&n; * the disk size is non-zero!!!&n; */
DECL|function|adfs_checkbblk
r_static
r_inline
r_int
id|adfs_checkbblk
c_func
(paren
r_int
r_char
op_star
id|ptr
)paren
(brace
r_int
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|ptr
op_plus
l_int|511
suffix:semicolon
r_do
(brace
id|result
op_assign
(paren
id|result
op_amp
l_int|0xff
)paren
op_plus
(paren
id|result
op_rshift
l_int|8
)paren
suffix:semicolon
id|result
op_assign
id|result
op_plus
op_star
op_decrement
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
id|ptr
)paren
suffix:semicolon
r_return
(paren
id|result
op_amp
l_int|0xff
)paren
op_ne
id|ptr
(braket
l_int|511
)braket
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
