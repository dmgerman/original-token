multiline_comment|/*&n; * linux/fs/hfs/btree.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file contains the code to manipulate the B-tree structure.&n; * The catalog and extents files are both B-trees.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; *&n; * The code in this file initializes some structures which contain&n; * pointers by calling memset(&amp;foo, 0, sizeof(foo)).&n; * This produces the desired behavior only due to the non-ANSI&n; * assumption that the machine representation of NULL is all zeros.&n; */
macro_line|#include &quot;hfs_btree.h&quot;
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * hfs_bnode_ditch() &n; *&n; * Description:&n; *   This function deletes an entire linked list of bnodes, so it&n; *   does not need to keep the linked list consistent as&n; *   hfs_bnode_delete() does.&n; *   Called by hfs_btree_init() for error cleanup and by hfs_btree_free().&n; * Input Variable(s):&n; *   struct hfs_bnode *bn: pointer to the first (struct hfs_bnode) in&n; *    the linked list to be deleted.&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;bn&squot; is NULL or points to a &quot;valid&quot; (struct hfs_bnode) with a &squot;prev&squot;&n; *    field of NULL.&n; * Postconditions:&n; *   &squot;bn&squot; and all (struct hfs_bnode)s in the chain of &squot;next&squot; pointers&n; *   are deleted, freeing the associated memory and hfs_buffer_put()ing&n; *   the associated buffer.&n; */
DECL|function|hfs_bnode_ditch
r_static
r_void
id|hfs_bnode_ditch
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|bn
)paren
(brace
r_struct
id|hfs_bnode
op_star
id|tmp
suffix:semicolon
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
r_extern
r_int
id|bnode_count
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|bn
op_ne
l_int|NULL
)paren
(brace
id|tmp
op_assign
id|bn-&gt;next
suffix:semicolon
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
id|hfs_warn
c_func
(paren
l_string|&quot;deleting node %d from tree %d with count %d&bslash;n&quot;
comma
id|bn-&gt;node
comma
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|bn-&gt;tree-&gt;entry.cnid
)paren
comma
id|bn-&gt;count
)paren
suffix:semicolon
op_decrement
id|bnode_count
suffix:semicolon
macro_line|#endif
id|hfs_buffer_put
c_func
(paren
id|bn-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* safe: checks for NULL argument */
multiline_comment|/* free all but the header */
r_if
c_cond
(paren
id|bn-&gt;node
)paren
(brace
id|HFS_DELETE
c_func
(paren
id|bn
)paren
suffix:semicolon
)brace
id|bn
op_assign
id|tmp
suffix:semicolon
)brace
)brace
multiline_comment|/*================ Global functions ================*/
multiline_comment|/*&n; * hfs_btree_free()&n; *&n; * Description:&n; *   This function frees a (struct hfs_btree) obtained from hfs_btree_init().&n; *   Called by hfs_put_super().&n; * Input Variable(s):&n; *   struct hfs_btree *bt: pointer to the (struct hfs_btree) to free&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;bt&squot; is NULL or points to a &quot;valid&quot; (struct hfs_btree)&n; * Postconditions:&n; *   If &squot;bt&squot; points to a &quot;valid&quot; (struct hfs_btree) then all (struct&n; *    hfs_bnode)s associated with &squot;bt&squot; are freed by calling&n; *    hfs_bnode_ditch() and the memory associated with the (struct&n; *    hfs_btree) is freed.&n; *   If &squot;bt&squot; is NULL or not &quot;valid&quot; an error is printed and nothing&n; *    is changed.&n; */
DECL|function|hfs_btree_free
r_void
id|hfs_btree_free
c_func
(paren
r_struct
id|hfs_btree
op_star
id|bt
)paren
(brace
r_int
id|lcv
suffix:semicolon
r_if
c_cond
(paren
id|bt
op_logical_and
(paren
id|bt-&gt;magic
op_eq
id|HFS_BTREE_MAGIC
)paren
)paren
(brace
id|hfs_extent_free
c_func
(paren
op_amp
id|bt-&gt;entry.u.file.data_fork
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lcv
op_assign
l_int|0
suffix:semicolon
id|lcv
OL
id|HFS_CACHELEN
suffix:semicolon
op_increment
id|lcv
)paren
(brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
id|hfs_warn
c_func
(paren
l_string|&quot;deleting nodes from bucket %d:&bslash;n&quot;
comma
id|lcv
)paren
suffix:semicolon
macro_line|#endif
id|hfs_bnode_ditch
c_func
(paren
id|bt-&gt;cache
(braket
id|lcv
)braket
)paren
suffix:semicolon
)brace
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
id|hfs_warn
c_func
(paren
l_string|&quot;deleting header and bitmap nodes&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|hfs_bnode_ditch
c_func
(paren
op_amp
id|bt-&gt;head
)paren
suffix:semicolon
macro_line|#if defined(DEBUG_BNODES) || defined(DEBUG_ALL)
id|hfs_warn
c_func
(paren
l_string|&quot;deleting root node&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|hfs_bnode_ditch
c_func
(paren
id|bt-&gt;root
)paren
suffix:semicolon
id|HFS_DELETE
c_func
(paren
id|bt
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bt
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_btree_free: corrupted hfs_btree.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * hfs_btree_init()&n; *&n; * Description:&n; *   Given some vital information from the MDB (HFS superblock),&n; *   initializes the fields of a (struct hfs_btree).&n; * Input Variable(s):&n; *   struct hfs_mdb *mdb: pointer to the MDB&n; *   ino_t cnid: the CNID (HFS_CAT_CNID or HFS_EXT_CNID) of the B-tree&n; *   hfs_u32 tsize: the size, in bytes, of the B-tree&n; *   hfs_u32 csize: the size, in bytes, of the clump size for the B-tree&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   (struct hfs_btree *): pointer to the initialized hfs_btree on success,&n; *    or NULL on failure&n; * Preconditions:&n; *   &squot;mdb&squot; points to a &quot;valid&quot; (struct hfs_mdb)&n; * Postconditions:&n; *   Assuming the inputs are what they claim to be, no errors occur&n; *   reading from disk, and no inconsistencies are noticed in the data&n; *   read from disk, the return value is a pointer to a &quot;valid&quot;&n; *   (struct hfs_btree).  If there are errors reading from disk or&n; *   inconsistencies are noticed in the data read from disk, then and&n; *   all resources that were allocated are released and NULL is&n; *   returned.&t;If the inputs are not what they claim to be or if they&n; *   are unnoticed inconsistencies in the data read from disk then the&n; *   returned hfs_btree is probably going to lead to errors when it is&n; *   used in a non-trivial way.&n; */
DECL|function|hfs_btree_init
r_struct
id|hfs_btree
op_star
id|hfs_btree_init
c_func
(paren
r_struct
id|hfs_mdb
op_star
id|mdb
comma
id|ino_t
id|cnid
comma
id|hfs_byte_t
id|ext
(braket
l_int|12
)braket
comma
id|hfs_u32
id|tsize
comma
id|hfs_u32
id|csize
)paren
(brace
r_struct
id|hfs_btree
op_star
id|bt
suffix:semicolon
r_struct
id|BTHdrRec
op_star
id|th
suffix:semicolon
r_struct
id|hfs_bnode
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|next
suffix:semicolon
macro_line|#if defined(DEBUG_HEADER) || defined(DEBUG_ALL)
r_int
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|mdb
op_logical_or
op_logical_neg
id|ext
op_logical_or
op_logical_neg
id|HFS_NEW
c_func
(paren
id|bt
)paren
)paren
(brace
r_goto
id|bail3
suffix:semicolon
)brace
id|bt-&gt;magic
op_assign
id|HFS_BTREE_MAGIC
suffix:semicolon
id|bt-&gt;sys_mdb
op_assign
id|mdb-&gt;sys_mdb
suffix:semicolon
id|bt-&gt;reserved
op_assign
l_int|0
suffix:semicolon
id|bt-&gt;lock
op_assign
l_int|0
suffix:semicolon
id|bt-&gt;wait
op_assign
l_int|NULL
suffix:semicolon
id|bt-&gt;dirt
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|bt-&gt;cache
comma
l_int|0
comma
r_sizeof
(paren
id|bt-&gt;cache
)paren
)paren
suffix:semicolon
id|bt-&gt;entry.mdb
op_assign
id|mdb
suffix:semicolon
id|bt-&gt;entry.cnid
op_assign
id|cnid
suffix:semicolon
id|bt-&gt;entry.type
op_assign
id|HFS_CDR_FIL
suffix:semicolon
id|bt-&gt;entry.u.file.magic
op_assign
id|HFS_FILE_MAGIC
suffix:semicolon
id|bt-&gt;entry.u.file.clumpablks
op_assign
(paren
id|csize
op_div
id|mdb-&gt;alloc_blksz
)paren
op_rshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|bt-&gt;entry.u.file.data_fork.entry
op_assign
op_amp
id|bt-&gt;entry
suffix:semicolon
id|bt-&gt;entry.u.file.data_fork.lsize
op_assign
id|tsize
suffix:semicolon
id|bt-&gt;entry.u.file.data_fork.psize
op_assign
id|tsize
op_rshift
id|HFS_SECTOR_SIZE_BITS
suffix:semicolon
id|bt-&gt;entry.u.file.data_fork.fork
op_assign
id|HFS_FK_DATA
suffix:semicolon
id|hfs_extent_in
c_func
(paren
op_amp
id|bt-&gt;entry.u.file.data_fork
comma
id|ext
)paren
suffix:semicolon
id|hfs_bnode_read
c_func
(paren
op_amp
id|bt-&gt;head
comma
id|bt
comma
l_int|0
comma
id|HFS_STICKY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|bt-&gt;head.buf
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|th
op_assign
(paren
r_struct
id|BTHdrRec
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|bt-&gt;head.buf
)paren
op_plus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
)paren
suffix:semicolon
multiline_comment|/* read in the bitmap nodes (if any) */
id|tmp
op_assign
op_amp
id|bt-&gt;head
suffix:semicolon
r_while
c_loop
(paren
(paren
id|next
op_assign
id|tmp-&gt;ndFLink
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|HFS_NEW
c_func
(paren
id|tmp-&gt;next
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|hfs_bnode_read
c_func
(paren
id|tmp-&gt;next
comma
id|bt
comma
id|next
comma
id|HFS_STICKY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|tmp-&gt;next-&gt;buf
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|tmp-&gt;next-&gt;prev
op_assign
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hfs_get_ns
c_func
(paren
id|th-&gt;bthNodeSize
)paren
op_ne
id|htons
c_func
(paren
id|HFS_SECTOR_SIZE
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;hfs_btree_init: bthNodeSize!=512 not supported&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnid
op_eq
id|htonl
c_func
(paren
id|HFS_CAT_CNID
)paren
)paren
(brace
id|bt-&gt;compare
op_assign
(paren
id|hfs_cmpfn
)paren
id|hfs_cat_compare
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cnid
op_eq
id|htonl
c_func
(paren
id|HFS_EXT_CNID
)paren
)paren
(brace
id|bt-&gt;compare
op_assign
(paren
id|hfs_cmpfn
)paren
id|hfs_ext_compare
suffix:semicolon
)brace
r_else
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|bt-&gt;bthDepth
op_assign
id|hfs_get_hs
c_func
(paren
id|th-&gt;bthDepth
)paren
suffix:semicolon
id|bt-&gt;bthRoot
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthRoot
)paren
suffix:semicolon
id|bt-&gt;bthNRecs
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthNRecs
)paren
suffix:semicolon
id|bt-&gt;bthFNode
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthFNode
)paren
suffix:semicolon
id|bt-&gt;bthLNode
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthLNode
)paren
suffix:semicolon
id|bt-&gt;bthNNodes
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthNNodes
)paren
suffix:semicolon
id|bt-&gt;bthFree
op_assign
id|hfs_get_hl
c_func
(paren
id|th-&gt;bthFree
)paren
suffix:semicolon
id|bt-&gt;bthKeyLen
op_assign
id|hfs_get_hs
c_func
(paren
id|th-&gt;bthKeyLen
)paren
suffix:semicolon
macro_line|#if defined(DEBUG_HEADER) || defined(DEBUG_ALL)
id|hfs_warn
c_func
(paren
l_string|&quot;bthDepth %d&bslash;n&quot;
comma
id|bt-&gt;bthDepth
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthRoot %d&bslash;n&quot;
comma
id|bt-&gt;bthRoot
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthNRecs %d&bslash;n&quot;
comma
id|bt-&gt;bthNRecs
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthFNode %d&bslash;n&quot;
comma
id|bt-&gt;bthFNode
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthLNode %d&bslash;n&quot;
comma
id|bt-&gt;bthLNode
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthKeyLen %d&bslash;n&quot;
comma
id|bt-&gt;bthKeyLen
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthNNodes %d&bslash;n&quot;
comma
id|bt-&gt;bthNNodes
)paren
suffix:semicolon
id|hfs_warn
c_func
(paren
l_string|&quot;bthFree %d&bslash;n&quot;
comma
id|bt-&gt;bthFree
)paren
suffix:semicolon
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|bt-&gt;head.buf
)paren
suffix:semicolon
id|q
op_assign
id|p
op_plus
id|HFS_SECTOR_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|q
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;%02x %02x %02x %02x %02x %02x %02x %02x &quot;
l_string|&quot;%02x %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
comma
op_star
id|p
op_increment
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Read in the root if it exists.&n;&t;   The header always exists, but the root exists only if the&n;&t;   tree is non-empty */
r_if
c_cond
(paren
id|bt-&gt;bthDepth
op_logical_and
id|bt-&gt;bthRoot
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|HFS_NEW
c_func
(paren
id|bt-&gt;root
)paren
)paren
(brace
r_goto
id|bail2
suffix:semicolon
)brace
id|hfs_bnode_read
c_func
(paren
id|bt-&gt;root
comma
id|bt
comma
id|bt-&gt;bthRoot
comma
id|HFS_STICKY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hfs_buffer_ok
c_func
(paren
id|bt-&gt;root-&gt;buf
)paren
)paren
(brace
r_goto
id|bail1
suffix:semicolon
)brace
)brace
r_else
(brace
id|bt-&gt;root
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|bt
suffix:semicolon
id|bail1
suffix:colon
id|hfs_bnode_ditch
c_func
(paren
id|bt-&gt;root
)paren
suffix:semicolon
id|bail2
suffix:colon
id|hfs_bnode_ditch
c_func
(paren
op_amp
id|bt-&gt;head
)paren
suffix:semicolon
id|HFS_DELETE
c_func
(paren
id|bt
)paren
suffix:semicolon
id|bail3
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_btree_commit()&n; *&n; * Called to write a possibly dirty btree back to disk.&n; */
DECL|function|hfs_btree_commit
r_void
id|hfs_btree_commit
c_func
(paren
r_struct
id|hfs_btree
op_star
id|bt
comma
id|hfs_byte_t
id|ext
(braket
l_int|12
)braket
comma
id|hfs_lword_t
id|size
)paren
(brace
r_if
c_cond
(paren
id|bt-&gt;dirt
)paren
(brace
r_struct
id|BTHdrRec
op_star
id|th
suffix:semicolon
id|th
op_assign
(paren
r_struct
id|BTHdrRec
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hfs_buffer_data
c_func
(paren
id|bt-&gt;head.buf
)paren
op_plus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
)paren
suffix:semicolon
id|hfs_put_hs
c_func
(paren
id|bt-&gt;bthDepth
comma
id|th-&gt;bthDepth
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthRoot
comma
id|th-&gt;bthRoot
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthNRecs
comma
id|th-&gt;bthNRecs
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthFNode
comma
id|th-&gt;bthFNode
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthLNode
comma
id|th-&gt;bthLNode
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthNNodes
comma
id|th-&gt;bthNNodes
)paren
suffix:semicolon
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthFree
comma
id|th-&gt;bthFree
)paren
suffix:semicolon
id|hfs_buffer_dirty
c_func
(paren
id|bt-&gt;head.buf
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Commit the bnodes which are not cached.&n;&t;&t; * The map nodes don&squot;t need to be committed here because&n;&t;&t; * they are committed every time they are changed.&n;&t;&t; */
id|hfs_bnode_commit
c_func
(paren
op_amp
id|bt-&gt;head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bt-&gt;root
)paren
(brace
id|hfs_bnode_commit
c_func
(paren
id|bt-&gt;root
)paren
suffix:semicolon
)brace
id|hfs_put_hl
c_func
(paren
id|bt-&gt;bthNNodes
op_lshift
id|HFS_SECTOR_SIZE_BITS
comma
id|size
)paren
suffix:semicolon
id|hfs_extent_out
c_func
(paren
op_amp
id|bt-&gt;entry.u.file.data_fork
comma
id|ext
)paren
suffix:semicolon
multiline_comment|/* hfs_buffer_dirty(mdb-&gt;buf); (Done by caller) */
id|bt-&gt;dirt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof