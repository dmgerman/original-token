multiline_comment|/*  fs/tunnel.c: utility functions to support VFS tunnelling&n;&n;    Copyright (C) 1999  Richard Gooch&n;&n;    This library is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU Library General Public&n;    License as published by the Free Software Foundation; either&n;    version 2 of the License, or (at your option) any later version.&n;&n;    This library is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    Library General Public License for more details.&n;&n;    You should have received a copy of the GNU Library General Public&n;    License along with this library; if not, write to the Free&n;    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Richard Gooch may be reached by email at  rgooch@atnf.csiro.au&n;    The postal address is:&n;      Richard Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.&n;&n;    ChangeLog&n;&n;    19991121   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created.&n;*/
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/*PUBLIC_FUNCTION*/
DECL|function|vfs_tunnel_lookup
r_struct
id|dentry
op_star
id|vfs_tunnel_lookup
(paren
r_const
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_struct
id|dentry
op_star
id|parent
comma
r_const
r_struct
id|dentry
op_star
id|covered
)paren
multiline_comment|/*  [SUMMARY] Lookup the corresponding dentry in the mounted-over FS.&n;    &lt;dentry&gt; The dentry which is in the overmounting FS.&n;    &lt;parent&gt; The parent of the dentry in the mounted-over FS. This may be NULL.&n;    &lt;covered&gt; The dentry covered by the root dentry of the overmounting FS.&n;    [RETURNS] A dentry on success, else NULL.&n;*/
(brace
r_struct
id|dentry
op_star
id|root
op_assign
id|dentry-&gt;d_sb-&gt;s_root
suffix:semicolon
r_if
c_cond
(paren
id|covered
op_eq
id|root
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
r_return
id|lookup_dentry
(paren
id|dentry-&gt;d_name.name
comma
id|parent
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*  End Function vfs_tunnel_lookup  */
eof
