multiline_comment|/*&n; * linux/fs/hfs/part_tbl.c&n; *&n; * Copyright (C) 1996-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * Original code to handle the new style Mac partition table based on&n; * a patch contributed by Holger Schemel (aeglos@valinor.owl.de).&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; * The code in this file initializes some structures which contain&n; * pointers by calling memset(&amp;foo, 0, sizeof(foo)).&n; * This produces the desired behavior only due to the non-ANSI&n; * assumption that the machine representation of NULL is all zeros.&n; */
macro_line|#include &quot;hfs.h&quot;
multiline_comment|/*================ File-local data types ================*/
multiline_comment|/*&n; * The Macintosh Driver Descriptor Block&n; *&n; * On partitioned Macintosh media this is block 0.&n; * We really only need the &quot;magic number&quot; to check for partitioned media.&n; */
DECL|struct|hfs_drvr_desc
r_struct
id|hfs_drvr_desc
(brace
DECL|member|ddSig
id|hfs_word_t
id|ddSig
suffix:semicolon
multiline_comment|/* The signature word */
multiline_comment|/* a bunch more stuff we don&squot;t need */
)brace
suffix:semicolon
multiline_comment|/* &n; * The new style Mac partition map&n; *&n; * For each partition on the media there is a physical block (512-byte&n; * block) containing one of these structures.  These blocks are&n; * contiguous starting at block 1.&n; */
DECL|struct|new_pmap
r_struct
id|new_pmap
(brace
DECL|member|pmSig
id|hfs_word_t
id|pmSig
suffix:semicolon
multiline_comment|/* Signature bytes to verify&n;&t;&t;&t;&t;&t;   that this is a partition&n;&t;&t;&t;&t;&t;   map block */
DECL|member|reSigPad
id|hfs_word_t
id|reSigPad
suffix:semicolon
multiline_comment|/* padding */
DECL|member|pmMapBlkCnt
id|hfs_lword_t
id|pmMapBlkCnt
suffix:semicolon
multiline_comment|/* (At least in block 1) this&n;&t;&t;&t;&t;&t;   is the number of partition&n;&t;&t;&t;&t;&t;   map blocks */
DECL|member|pmPyPartStart
id|hfs_lword_t
id|pmPyPartStart
suffix:semicolon
multiline_comment|/* The physical block number&n;&t;&t;&t;&t;&t;   of the first block in this&n;&t;&t;&t;&t;&t;   partition */
DECL|member|pmPartBlkCnt
id|hfs_lword_t
id|pmPartBlkCnt
suffix:semicolon
multiline_comment|/* The number of physical&n;&t;&t;&t;&t;&t;   blocks in this partition */
DECL|member|pmPartName
id|hfs_byte_t
id|pmPartName
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* (null terminated?) string&n;&t;&t;&t;&t;&t;   giving the name of this&n;&t;&t;&t;&t;&t;   partition */
DECL|member|pmPartType
id|hfs_byte_t
id|pmPartType
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* (null terminated?) string&n;&t;&t;&t;&t;&t;   giving the type of this&n;&t;&t;&t;&t;&t;   partition */
multiline_comment|/* a bunch more stuff we don&squot;t need */
)brace
suffix:semicolon
multiline_comment|/* &n; * The old style Mac partition map&n; *&n; * The partition map consists for a 2-byte signature followed by an&n; * array of these structures.  The map is terminated with an all-zero&n; * one of these.&n; */
DECL|struct|old_pmap
r_struct
id|old_pmap
(brace
DECL|member|pdSig
id|hfs_word_t
id|pdSig
suffix:semicolon
multiline_comment|/* Signature bytes */
DECL|struct|old_pmap_entry
r_struct
id|old_pmap_entry
(brace
DECL|member|pdStart
id|hfs_lword_t
id|pdStart
suffix:semicolon
DECL|member|pdSize
id|hfs_lword_t
id|pdSize
suffix:semicolon
DECL|member|pdFSID
id|hfs_lword_t
id|pdFSID
suffix:semicolon
DECL|member|pdEntry
)brace
id|pdEntry
(braket
l_int|42
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * parse_new_part_table()&n; *&n; * Parse a new style partition map looking for the&n; * start and length of the &squot;part&squot;th HFS partition.&n; */
DECL|function|parse_new_part_table
r_static
r_int
id|parse_new_part_table
c_func
(paren
id|hfs_sysmdb
id|sys_mdb
comma
id|hfs_buffer
id|buf
comma
r_int
id|part
comma
id|hfs_s32
op_star
id|size
comma
id|hfs_s32
op_star
id|start
)paren
(brace
r_struct
id|new_pmap
op_star
id|pm
op_assign
(paren
r_struct
id|new_pmap
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|buf
)paren
suffix:semicolon
id|hfs_u32
id|pmap_entries
op_assign
id|hfs_get_hl
c_func
(paren
id|pm-&gt;pmMapBlkCnt
)paren
suffix:semicolon
r_int
id|hfs_part
op_assign
l_int|0
suffix:semicolon
r_int
id|entry
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
(paren
id|entry
OL
id|pmap_entries
)paren
op_logical_and
op_logical_neg
(paren
op_star
id|start
)paren
suffix:semicolon
op_increment
id|entry
)paren
(brace
r_if
c_cond
(paren
id|entry
)paren
(brace
multiline_comment|/* read the next partition map entry */
id|buf
op_assign
id|hfs_buffer_get
c_func
(paren
id|sys_mdb
comma
id|HFS_PMAP_BLK
op_plus
id|entry
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|buf
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to &quot;
l_string|&quot;read partition map.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
id|pm
op_assign
(paren
r_struct
id|new_pmap
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hfs_get_ns
c_func
(paren
id|pm-&gt;pmSig
)paren
op_ne
id|htons
c_func
(paren
id|HFS_NEW_PMAP_MAGIC
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: invalid &quot;
l_string|&quot;entry in partition map&bslash;n&quot;
)paren
suffix:semicolon
id|hfs_buffer_put
c_func
(paren
id|buf
)paren
suffix:semicolon
r_goto
id|bail
suffix:semicolon
)brace
)brace
multiline_comment|/* look for an HFS partition */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|pm-&gt;pmPartType
comma
l_string|&quot;Apple_HFS&quot;
comma
l_int|9
)paren
op_logical_and
(paren
(paren
id|hfs_part
op_increment
)paren
op_eq
id|part
)paren
)paren
(brace
multiline_comment|/* Found it! */
op_star
id|start
op_assign
id|hfs_get_hl
c_func
(paren
id|pm-&gt;pmPyPartStart
)paren
suffix:semicolon
op_star
id|size
op_assign
id|hfs_get_hl
c_func
(paren
id|pm-&gt;pmPartBlkCnt
)paren
suffix:semicolon
)brace
id|hfs_buffer_put
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|bail
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * parse_old_part_table()&n; *&n; * Parse a old style partition map looking for the&n; * start and length of the &squot;part&squot;th HFS partition.&n; */
DECL|function|parse_old_part_table
r_static
r_int
id|parse_old_part_table
c_func
(paren
id|hfs_sysmdb
id|sys_mdb
comma
id|hfs_buffer
id|buf
comma
r_int
id|part
comma
id|hfs_s32
op_star
id|size
comma
id|hfs_s32
op_star
id|start
)paren
(brace
r_struct
id|old_pmap
op_star
id|pm
op_assign
(paren
r_struct
id|old_pmap
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|buf
)paren
suffix:semicolon
r_struct
id|old_pmap_entry
op_star
id|p
op_assign
op_amp
id|pm-&gt;pdEntry
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|hfs_part
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|p-&gt;pdStart
op_logical_or
id|p-&gt;pdSize
op_logical_or
id|p-&gt;pdFSID
)paren
op_logical_and
op_logical_neg
(paren
op_star
id|start
)paren
)paren
(brace
multiline_comment|/* look for an HFS partition */
r_if
c_cond
(paren
(paren
id|hfs_get_nl
c_func
(paren
id|p-&gt;pdFSID
)paren
op_eq
id|htonl
c_func
(paren
l_int|0x54465331
)paren
multiline_comment|/*&quot;TFS1&quot;*/
)paren
op_logical_and
(paren
(paren
id|hfs_part
op_increment
)paren
op_eq
id|part
)paren
)paren
(brace
multiline_comment|/* Found it! */
op_star
id|start
op_assign
id|hfs_get_hl
c_func
(paren
id|p-&gt;pdStart
)paren
suffix:semicolon
op_star
id|size
op_assign
id|hfs_get_hl
c_func
(paren
id|p-&gt;pdSize
)paren
suffix:semicolon
)brace
op_increment
id|p
suffix:semicolon
)brace
id|hfs_buffer_put
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_part_find()&n; *&n; * Parse the partition map looking for the&n; * start and length of the &squot;part&squot;th HFS partition.&n; */
DECL|function|hfs_part_find
r_int
id|hfs_part_find
c_func
(paren
id|hfs_sysmdb
id|sys_mdb
comma
r_int
id|part
comma
r_int
id|silent
comma
id|hfs_s32
op_star
id|size
comma
id|hfs_s32
op_star
id|start
)paren
(brace
id|hfs_buffer
id|buf
suffix:semicolon
id|hfs_u16
id|sig
suffix:semicolon
r_int
id|dd_found
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Read block 0 to see if this media is partitioned */
id|buf
op_assign
id|hfs_buffer_get
c_func
(paren
id|sys_mdb
comma
id|HFS_DD_BLK
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|buf
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: Unable to read block 0.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|sig
op_assign
id|hfs_get_ns
c_func
(paren
(paren
(paren
r_struct
id|hfs_drvr_desc
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|buf
)paren
)paren
op_member_access_from_pointer
id|ddSig
)paren
suffix:semicolon
id|hfs_buffer_put
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|htons
c_func
(paren
id|HFS_DRVR_DESC_MAGIC
)paren
)paren
(brace
multiline_comment|/* We are definitely on partitioned media. */
id|dd_found
op_assign
l_int|1
suffix:semicolon
)brace
id|buf
op_assign
id|hfs_buffer_get
c_func
(paren
id|sys_mdb
comma
id|HFS_PMAP_BLK
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|buf
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: Unable to read block 1.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
op_star
id|size
op_assign
op_star
id|start
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|hfs_get_ns
c_func
(paren
id|hfs_buffer_data
c_func
(paren
id|buf
)paren
)paren
)paren
(brace
r_case
id|__constant_htons
c_func
(paren
id|HFS_OLD_PMAP_MAGIC
)paren
suffix:colon
id|retval
op_assign
id|parse_old_part_table
c_func
(paren
id|sys_mdb
comma
id|buf
comma
id|part
comma
id|size
comma
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__constant_htons
c_func
(paren
id|HFS_NEW_PMAP_MAGIC
)paren
suffix:colon
id|retval
op_assign
id|parse_new_part_table
c_func
(paren
id|sys_mdb
comma
id|buf
comma
id|part
comma
id|size
comma
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|dd_found
)paren
(brace
multiline_comment|/* The media claimed to have a partition map */
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: This disk has an &quot;
l_string|&quot;unrecognized partition map type.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Conclude that the media is not partitioned */
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
op_star
id|start
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|part
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to locate &quot;
l_string|&quot;HFS partition number %d.&bslash;n&quot;
comma
id|part
)paren
suffix:semicolon
)brace
r_else
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: unable to locate any &quot;
l_string|&quot;HFS partitions.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|size
OL
l_int|0
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: Partition size &gt; 1 Terabyte.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|start
OL
l_int|0
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_fs: Partition begins beyond 1 &quot;
l_string|&quot;Terabyte.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
)brace
id|done
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
eof