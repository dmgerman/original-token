multiline_comment|/*&n; * linux/fs/hfs/bins_del.c&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU Public License.&n; *&n; * This file contains the code common to inserting and deleting records&n; * in a B-tree.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; *&n; * In function preconditions the term &quot;valid&quot; applied to a pointer to&n; * a structure means that the pointer is non-NULL and the structure it&n; * points to has all fields initialized to consistent values.&n; */
macro_line|#include &quot;hfs_btree.h&quot;
multiline_comment|/*================ File-local functions ================*/
multiline_comment|/*&n; * hfs_bnode_update_key()&n; *&n; * Description:&n; *   Updates the key for a bnode in its parent.&n; *   The key change is propagated up the tree as necessary.&n; * Input Variable(s):&n; *   struct hfs_brec *brec: the search path to update keys in&n; *   struct hfs_belem *belem: the search path element with the changed key&n; *   struct hfs_bnode *bnode: the bnode with the changed key&n; *   int offset: the &quot;distance&quot; from &squot;belem-&gt;bn&squot; to &squot;bnode&squot;:&n; *    0 if the change is in &squot;belem-&gt;bn&squot;,&n; *    1 if the change is in its right sibling, etc.&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;brec&squot; points to a valid (struct hfs_brec)&n; *   &squot;belem&squot; points to a valid (struct hfs_belem) in &squot;brec&squot;.&n; *   &squot;bnode&squot; points to a valid (struct hfs_bnode) which is non-empty&n; *    and is &squot;belem-&gt;bn&squot; or one of its siblings.&n; *   &squot;offset&squot; is as described above.&n; * Postconditions:&n; *   The key change is propagated up the tree as necessary.&n; */
DECL|function|hfs_bnode_update_key
r_void
id|hfs_bnode_update_key
c_func
(paren
r_struct
id|hfs_brec
op_star
id|brec
comma
r_struct
id|hfs_belem
op_star
id|belem
comma
r_struct
id|hfs_bnode
op_star
id|bnode
comma
r_int
id|offset
)paren
(brace
r_int
id|record
op_assign
(paren
op_decrement
id|belem
)paren
op_member_access_from_pointer
id|record
op_plus
id|offset
suffix:semicolon
r_void
op_star
id|key
op_assign
id|bnode_datastart
c_func
(paren
id|bnode
)paren
op_plus
l_int|1
suffix:semicolon
r_int
id|keysize
op_assign
id|brec-&gt;tree-&gt;bthKeyLen
suffix:semicolon
r_struct
id|hfs_belem
op_star
id|limit
suffix:semicolon
id|memcpy
c_func
(paren
l_int|1
op_plus
id|bnode_key
c_func
(paren
id|belem-&gt;bnr.bn
comma
id|record
)paren
comma
id|key
comma
id|keysize
)paren
suffix:semicolon
multiline_comment|/* don&squot;t trash the header */
r_if
c_cond
(paren
id|brec-&gt;top
OG
op_amp
id|brec-&gt;elem
(braket
l_int|1
)braket
)paren
(brace
id|limit
op_assign
id|brec-&gt;top
suffix:semicolon
)brace
r_else
(brace
id|limit
op_assign
op_amp
id|brec-&gt;elem
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|belem
OG
id|limit
)paren
op_logical_and
(paren
id|record
op_eq
l_int|1
)paren
)paren
(brace
id|record
op_assign
(paren
op_decrement
id|belem
)paren
op_member_access_from_pointer
id|record
suffix:semicolon
id|memcpy
c_func
(paren
l_int|1
op_plus
id|belem_key
c_func
(paren
id|belem
)paren
comma
id|key
comma
id|keysize
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * hfs_bnode_shift_right()&n; *&n; * Description:&n; *   Shifts some records from a node to its right neighbor.&n; * Input Variable(s):&n; *   struct hfs_bnode* left: the node to shift records from&n; *   struct hfs_bnode* right: the node to shift records to&n; *   hfs_u16 first: the number of the first record in &squot;left&squot; to move to &squot;right&squot;&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;left&squot; and &squot;right&squot; point to valid (struct hfs_bnode)s.&n; *   &squot;left&squot; contains at least &squot;first&squot; records.&n; *   &squot;right&squot; has enough free space to hold the records to be moved from &squot;left&squot;&n; * Postconditions:&n; *   The record numbered &squot;first&squot; and all records after it in &squot;left&squot; are&n; *   placed at the beginning of &squot;right&squot;.&n; *   The key corresponding to &squot;right&squot; in its parent is NOT updated.&n; */
DECL|function|hfs_bnode_shift_right
r_void
id|hfs_bnode_shift_right
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|left
comma
r_struct
id|hfs_bnode
op_star
id|right
comma
r_int
id|first
)paren
(brace
r_int
id|i
comma
id|adjust
comma
id|nrecs
suffix:semicolon
r_int
id|size
suffix:semicolon
id|hfs_u16
op_star
id|to
comma
op_star
id|from
suffix:semicolon
r_if
c_cond
(paren
(paren
id|first
op_le
l_int|0
)paren
op_logical_or
(paren
id|first
OG
id|left-&gt;ndNRecs
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;bad argument to shift_right: first=%d, nrecs=%d&bslash;n&quot;
comma
id|first
comma
id|left-&gt;ndNRecs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* initialize variables */
id|nrecs
op_assign
id|left-&gt;ndNRecs
op_plus
l_int|1
op_minus
id|first
suffix:semicolon
id|size
op_assign
id|bnode_end
c_func
(paren
id|left
)paren
op_minus
id|bnode_offset
c_func
(paren
id|left
comma
id|first
)paren
suffix:semicolon
multiline_comment|/* move (possibly empty) contents of right node forward */
id|memmove
c_func
(paren
id|bnode_datastart
c_func
(paren
id|right
)paren
op_plus
id|size
comma
id|bnode_datastart
c_func
(paren
id|right
)paren
comma
id|bnode_end
c_func
(paren
id|right
)paren
op_minus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
)paren
suffix:semicolon
multiline_comment|/* copy in new records */
id|memcpy
c_func
(paren
id|bnode_datastart
c_func
(paren
id|right
)paren
comma
id|bnode_key
c_func
(paren
id|left
comma
id|first
)paren
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* fix up offsets in right node */
id|i
op_assign
id|right-&gt;ndNRecs
op_plus
l_int|1
suffix:semicolon
id|from
op_assign
id|RECTBL
c_func
(paren
id|right
comma
id|i
)paren
suffix:semicolon
id|to
op_assign
id|from
op_minus
id|nrecs
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|hfs_put_hs
c_func
(paren
id|hfs_get_hs
c_func
(paren
id|from
op_increment
)paren
op_plus
id|size
comma
id|to
op_increment
)paren
suffix:semicolon
)brace
id|adjust
op_assign
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
op_minus
id|bnode_offset
c_func
(paren
id|left
comma
id|first
)paren
suffix:semicolon
id|i
op_assign
id|nrecs
op_minus
l_int|1
suffix:semicolon
id|from
op_assign
id|RECTBL
c_func
(paren
id|left
comma
id|first
op_plus
id|i
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|hfs_put_hs
c_func
(paren
id|hfs_get_hs
c_func
(paren
id|from
op_increment
)paren
op_plus
id|adjust
comma
id|to
op_increment
)paren
suffix:semicolon
)brace
multiline_comment|/* fix record counts */
id|left-&gt;ndNRecs
op_sub_assign
id|nrecs
suffix:semicolon
id|right-&gt;ndNRecs
op_add_assign
id|nrecs
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_bnode_shift_left()&n; *&n; * Description:&n; *   Shifts some records from a node to its left neighbor.&n; * Input Variable(s):&n; *   struct hfs_bnode* left: the node to shift records to&n; *   struct hfs_bnode* right: the node to shift records from&n; *   hfs_u16 last: the number of the last record in &squot;right&squot; to move to &squot;left&squot;&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   void&n; * Preconditions:&n; *   &squot;left&squot; and &squot;right&squot; point to valid (struct hfs_bnode)s.&n; *   &squot;right&squot; contains at least &squot;last&squot; records.&n; *   &squot;left&squot; has enough free space to hold the records to be moved from &squot;right&squot;&n; * Postconditions:&n; *   The record numbered &squot;last&squot; and all records before it in &squot;right&squot; are&n; *   placed at the end of &squot;left&squot;.&n; *   The key corresponding to &squot;right&squot; in its parent is NOT updated.&n; */
DECL|function|hfs_bnode_shift_left
r_void
id|hfs_bnode_shift_left
c_func
(paren
r_struct
id|hfs_bnode
op_star
id|left
comma
r_struct
id|hfs_bnode
op_star
id|right
comma
r_int
id|last
)paren
(brace
r_int
id|i
comma
id|adjust
comma
id|nrecs
suffix:semicolon
r_int
id|size
suffix:semicolon
id|hfs_u16
op_star
id|to
comma
op_star
id|from
suffix:semicolon
r_if
c_cond
(paren
(paren
id|last
op_le
l_int|0
)paren
op_logical_or
(paren
id|last
OG
id|right-&gt;ndNRecs
)paren
)paren
(brace
id|hfs_warn
c_func
(paren
l_string|&quot;bad argument to shift_left: last=%d, nrecs=%d&bslash;n&quot;
comma
id|last
comma
id|right-&gt;ndNRecs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* initialize variables */
id|size
op_assign
id|bnode_offset
c_func
(paren
id|right
comma
id|last
op_plus
l_int|1
)paren
op_minus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
suffix:semicolon
multiline_comment|/* copy records to left node */
id|memcpy
c_func
(paren
id|bnode_dataend
c_func
(paren
id|left
)paren
comma
id|bnode_datastart
c_func
(paren
id|right
)paren
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* move (possibly empty) remainder of right node backward */
id|memmove
c_func
(paren
id|bnode_datastart
c_func
(paren
id|right
)paren
comma
id|bnode_datastart
c_func
(paren
id|right
)paren
op_plus
id|size
comma
id|bnode_end
c_func
(paren
id|right
)paren
op_minus
id|bnode_offset
c_func
(paren
id|right
comma
id|last
op_plus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* fix up offsets */
id|nrecs
op_assign
id|left-&gt;ndNRecs
suffix:semicolon
id|i
op_assign
id|last
suffix:semicolon
id|from
op_assign
id|RECTBL
c_func
(paren
id|right
comma
l_int|2
)paren
suffix:semicolon
id|to
op_assign
id|RECTBL
c_func
(paren
id|left
comma
id|nrecs
op_plus
l_int|2
)paren
suffix:semicolon
id|adjust
op_assign
id|bnode_offset
c_func
(paren
id|left
comma
id|nrecs
op_plus
l_int|1
)paren
op_minus
r_sizeof
(paren
r_struct
id|NodeDescriptor
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|hfs_put_hs
c_func
(paren
id|hfs_get_hs
c_func
(paren
id|from
op_decrement
)paren
op_plus
id|adjust
comma
id|to
op_decrement
)paren
suffix:semicolon
)brace
id|i
op_assign
id|right-&gt;ndNRecs
op_plus
l_int|1
op_minus
id|last
suffix:semicolon
op_increment
id|from
suffix:semicolon
id|to
op_assign
id|RECTBL
c_func
(paren
id|right
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|hfs_put_hs
c_func
(paren
id|hfs_get_hs
c_func
(paren
id|from
op_decrement
)paren
op_minus
id|size
comma
id|to
op_decrement
)paren
suffix:semicolon
)brace
multiline_comment|/* fix record counts */
id|left-&gt;ndNRecs
op_add_assign
id|last
suffix:semicolon
id|right-&gt;ndNRecs
op_sub_assign
id|last
suffix:semicolon
)brace
multiline_comment|/*&n; * hfs_bnode_in_brec()&n; *&n; * Description:&n; *   Determines whethet a given bnode is part of a given brec.&n; *   This is used to avoid deadlock in the case of a corrupted b-tree.&n; * Input Variable(s):&n; *   hfs_u32 node: the number of the node to check for.&n; *   struct hfs_brec* brec: the brec to check in.&n; * Output Variable(s):&n; *   NONE&n; * Returns:&n; *   int: 1 it found, 0 if not&n; * Preconditions:&n; *   &squot;brec&squot; points to a valid struct hfs_brec.&n; * Postconditions:&n; *   &squot;brec&squot; is unchanged.&n; */
DECL|function|hfs_bnode_in_brec
r_int
id|hfs_bnode_in_brec
c_func
(paren
id|hfs_u32
id|node
comma
r_const
r_struct
id|hfs_brec
op_star
id|brec
)paren
(brace
r_const
r_struct
id|hfs_belem
op_star
id|belem
op_assign
id|brec-&gt;bottom
suffix:semicolon
r_while
c_loop
(paren
id|belem
op_logical_and
(paren
id|belem
op_ge
id|brec-&gt;top
)paren
)paren
(brace
r_if
c_cond
(paren
id|belem-&gt;bnr.bn
op_logical_and
(paren
id|belem-&gt;bnr.bn-&gt;node
op_eq
id|node
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
op_decrement
id|belem
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof