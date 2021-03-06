multiline_comment|/*&n; * partition.c&n; *&n; * PURPOSE&n; *      Partition handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *      E-mail regarding any portion of the Linux UDF file system should be&n; *      directed to the development team mailing list (run by majordomo):&n; *              linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *      This file is distributed under the terms of the GNU General Public&n; *      License (GPL). Copies of the GPL can be obtained from:&n; *              ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *      Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998-2000 Ben Fennema&n; *&n; * HISTORY&n; *&n; * 12/06/98 blf  Created file. &n; *&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
DECL|function|udf_get_pblock
r_inline
id|Uint32
id|udf_get_pblock
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|Uint32
id|block
comma
id|Uint16
id|partition
comma
id|Uint32
id|offset
)paren
(brace
r_if
c_cond
(paren
id|partition
op_ge
id|UDF_SB_NUMPARTS
c_func
(paren
id|sb
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;block=%d, partition=%d, offset=%d: invalid partition&bslash;n&quot;
comma
id|block
comma
id|partition
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0xFFFFFFFF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|UDF_SB_PARTFUNC
c_func
(paren
id|sb
comma
id|partition
)paren
)paren
r_return
id|UDF_SB_PARTFUNC
c_func
(paren
id|sb
comma
id|partition
)paren
(paren
id|sb
comma
id|block
comma
id|partition
comma
id|offset
)paren
suffix:semicolon
r_else
r_return
id|UDF_SB_PARTROOT
c_func
(paren
id|sb
comma
id|partition
)paren
op_plus
id|block
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|udf_get_pblock_virt15
id|Uint32
id|udf_get_pblock_virt15
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|Uint32
id|block
comma
id|Uint16
id|partition
comma
id|Uint32
id|offset
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|Uint32
id|newblock
suffix:semicolon
id|Uint32
id|index
suffix:semicolon
id|Uint32
id|loc
suffix:semicolon
id|index
op_assign
(paren
id|sb-&gt;s_blocksize
op_minus
id|UDF_SB_TYPEVIRT
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_start_offset
)paren
op_div
r_sizeof
(paren
id|Uint32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
OG
id|UDF_SB_TYPEVIRT
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_num_entries
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;Trying to access block beyond end of VAT (%d max %d)&bslash;n&quot;
comma
id|block
comma
id|UDF_SB_TYPEVIRT
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_num_entries
)paren
suffix:semicolon
r_return
l_int|0xFFFFFFFF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
op_ge
id|index
)paren
(brace
id|block
op_sub_assign
id|index
suffix:semicolon
id|newblock
op_assign
l_int|1
op_plus
(paren
id|block
op_div
(paren
id|sb-&gt;s_blocksize
op_div
r_sizeof
(paren
id|Uint32
)paren
)paren
)paren
suffix:semicolon
id|index
op_assign
id|block
op_mod
(paren
id|sb-&gt;s_blocksize
op_div
r_sizeof
(paren
id|Uint32
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|newblock
op_assign
l_int|0
suffix:semicolon
id|index
op_assign
id|UDF_SB_TYPEVIRT
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_start_offset
op_div
r_sizeof
(paren
id|Uint32
)paren
op_plus
id|block
suffix:semicolon
)brace
id|loc
op_assign
id|udf_locked_block_map
c_func
(paren
id|UDF_SB_VAT
c_func
(paren
id|sb
)paren
comma
id|newblock
)paren
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
id|sb-&gt;s_dev
comma
id|loc
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;get_pblock(UDF_VIRTUAL_MAP:%p,%d,%d) VAT: %d[%d]&bslash;n&quot;
comma
id|sb
comma
id|block
comma
id|partition
comma
id|loc
comma
id|index
)paren
suffix:semicolon
r_return
l_int|0xFFFFFFFF
suffix:semicolon
)brace
id|loc
op_assign
id|le32_to_cpu
c_func
(paren
(paren
(paren
id|Uint32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
id|index
)braket
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_LOCATION
c_func
(paren
id|UDF_SB_VAT
c_func
(paren
id|sb
)paren
)paren
dot
id|partitionReferenceNum
op_eq
id|partition
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;recursive call to udf_get_pblock!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0xFFFFFFFF
suffix:semicolon
)brace
r_return
id|udf_get_pblock
c_func
(paren
id|sb
comma
id|loc
comma
id|UDF_I_LOCATION
c_func
(paren
id|UDF_SB_VAT
c_func
(paren
id|sb
)paren
)paren
dot
id|partitionReferenceNum
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|udf_get_pblock_virt20
r_inline
id|Uint32
id|udf_get_pblock_virt20
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|Uint32
id|block
comma
id|Uint16
id|partition
comma
id|Uint32
id|offset
)paren
(brace
r_return
id|udf_get_pblock_virt15
c_func
(paren
id|sb
comma
id|block
comma
id|partition
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|udf_get_pblock_spar15
id|Uint32
id|udf_get_pblock_spar15
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|Uint32
id|block
comma
id|Uint16
id|partition
comma
id|Uint32
id|offset
)paren
(brace
id|Uint32
id|packet
op_assign
(paren
id|block
op_plus
id|offset
)paren
op_rshift
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_pshift
suffix:semicolon
id|Uint32
id|index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_indexsize
op_eq
l_int|8
)paren
id|index
op_assign
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_remap.s_spar_remap8
(braket
id|packet
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_indexsize
op_eq
l_int|16
)paren
id|index
op_assign
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_remap.s_spar_remap16
(braket
id|packet
)braket
suffix:semicolon
r_else
r_if
c_cond
(paren
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_indexsize
op_eq
l_int|32
)paren
id|index
op_assign
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_remap.s_spar_remap32
(braket
id|packet
)braket
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
(paren
(paren
l_int|1
op_lshift
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_indexsize
)paren
op_minus
l_int|1
)paren
)paren
r_return
id|UDF_SB_PARTROOT
c_func
(paren
id|sb
comma
id|partition
)paren
op_plus
id|block
op_plus
id|offset
suffix:semicolon
id|packet
op_assign
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_map
(braket
id|index
)braket
suffix:semicolon
r_return
id|packet
op_plus
(paren
(paren
id|block
op_plus
id|offset
)paren
op_amp
(paren
(paren
l_int|1
op_lshift
id|UDF_SB_TYPESPAR
c_func
(paren
id|sb
comma
id|partition
)paren
dot
id|s_spar_pshift
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|udf_fill_spartable
r_void
id|udf_fill_spartable
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|udf_sparing_data
op_star
id|sdata
comma
r_int
id|partlen
)paren
(brace
id|Uint16
id|ident
suffix:semicolon
id|Uint32
id|spartable
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|SparingTable
op_star
id|st
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|spartable
op_assign
id|sdata-&gt;s_spar_loc
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|bh
op_assign
id|udf_read_tagged
c_func
(paren
id|sb
comma
id|spartable
comma
id|spartable
comma
op_amp
id|ident
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|sdata-&gt;s_spar_loc
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ident
op_eq
l_int|0
)paren
(brace
id|st
op_assign
(paren
r_struct
id|SparingTable
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|st-&gt;sparingIdent.ident
comma
id|UDF_ID_SPARING
comma
id|strlen
c_func
(paren
id|UDF_ID_SPARING
)paren
)paren
)paren
(brace
id|SparingEntry
op_star
id|se
suffix:semicolon
id|Uint16
id|rtl
op_assign
id|le16_to_cpu
c_func
(paren
id|st-&gt;reallocationTableLen
)paren
suffix:semicolon
r_int
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sdata-&gt;s_spar_map
)paren
(brace
r_int
id|num
op_assign
l_int|1
comma
id|mapsize
suffix:semicolon
id|sdata-&gt;s_spar_indexsize
op_assign
l_int|8
suffix:semicolon
r_while
c_loop
(paren
id|rtl
op_star
r_sizeof
(paren
id|Uint32
)paren
op_ge
(paren
l_int|1
op_lshift
id|sdata-&gt;s_spar_indexsize
)paren
)paren
(brace
id|num
op_increment
suffix:semicolon
id|sdata-&gt;s_spar_indexsize
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|mapsize
op_assign
(paren
id|rtl
op_star
r_sizeof
(paren
id|Uint32
)paren
)paren
op_plus
(paren
(paren
id|partlen
op_div
(paren
l_int|1
op_lshift
id|sdata-&gt;s_spar_pshift
)paren
)paren
op_star
r_sizeof
(paren
id|Uint8
)paren
op_star
id|num
)paren
suffix:semicolon
id|sdata-&gt;s_spar_map
op_assign
id|kmalloc
c_func
(paren
id|mapsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|sdata-&gt;s_spar_remap.s_spar_remap32
op_assign
op_amp
id|sdata-&gt;s_spar_map
(braket
id|rtl
)braket
suffix:semicolon
id|memset
c_func
(paren
id|sdata-&gt;s_spar_map
comma
l_int|0xFF
comma
id|mapsize
)paren
suffix:semicolon
)brace
id|index
op_assign
r_sizeof
(paren
r_struct
id|SparingTable
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
id|rtl
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|index
OG
id|sb-&gt;s_blocksize
)paren
(brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|udf_tread
c_func
(paren
id|sb
comma
op_increment
id|spartable
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|sdata-&gt;s_spar_loc
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|index
op_assign
l_int|0
suffix:semicolon
)brace
id|se
op_assign
(paren
id|SparingEntry
op_star
)paren
op_amp
(paren
id|bh-&gt;b_data
(braket
id|index
)braket
)paren
suffix:semicolon
id|index
op_add_assign
r_sizeof
(paren
id|SparingEntry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sdata-&gt;s_spar_map
(braket
id|i
)braket
op_eq
l_int|0xFFFFFFFF
)paren
id|sdata-&gt;s_spar_map
(braket
id|i
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|se-&gt;mappedLocation
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_map
(braket
id|i
)braket
op_ne
id|le32_to_cpu
c_func
(paren
id|se-&gt;mappedLocation
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;Found conflicting Sparing Data (%d vs %d for entry %d)&bslash;n&quot;
comma
id|sdata-&gt;s_spar_map
(braket
id|i
)braket
comma
id|le32_to_cpu
c_func
(paren
id|se-&gt;mappedLocation
)paren
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|se-&gt;origLocation
)paren
OL
l_int|0xFFFFFFF0
)paren
(brace
r_int
id|packet
op_assign
id|le32_to_cpu
c_func
(paren
id|se-&gt;origLocation
)paren
op_rshift
id|sdata-&gt;s_spar_pshift
suffix:semicolon
r_if
c_cond
(paren
id|sdata-&gt;s_spar_indexsize
op_eq
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap8
(braket
id|packet
)braket
op_eq
l_int|0xFF
)paren
id|sdata-&gt;s_spar_remap.s_spar_remap8
(braket
id|packet
)braket
op_assign
id|i
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap8
(braket
id|packet
)braket
op_ne
id|i
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;Found conflicting Sparing Data (%d vs %d)&bslash;n&quot;
comma
id|sdata-&gt;s_spar_remap.s_spar_remap8
(braket
id|packet
)braket
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_indexsize
op_eq
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap16
(braket
id|packet
)braket
op_eq
l_int|0xFFFF
)paren
id|sdata-&gt;s_spar_remap.s_spar_remap16
(braket
id|packet
)braket
op_assign
id|i
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap16
(braket
id|packet
)braket
op_ne
id|i
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;Found conflicting Sparing Data (%d vs %d)&bslash;n&quot;
comma
id|sdata-&gt;s_spar_remap.s_spar_remap16
(braket
id|packet
)braket
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_indexsize
op_eq
l_int|32
)paren
(brace
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap32
(braket
id|packet
)braket
op_eq
l_int|0xFFFFFFFF
)paren
id|sdata-&gt;s_spar_remap.s_spar_remap32
(braket
id|packet
)braket
op_assign
id|i
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sdata-&gt;s_spar_remap.s_spar_remap32
(braket
id|packet
)braket
op_ne
id|i
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;Found conflicting Sparing Data (%d vs %d)&bslash;n&quot;
comma
id|sdata-&gt;s_spar_remap.s_spar_remap32
(braket
id|packet
)braket
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
)brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
eof
