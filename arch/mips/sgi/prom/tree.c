multiline_comment|/* $Id: tree.c,v 1.1 1997/06/06 09:37:29 ralf Exp $&n; * tree.c: PROM component device tree code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;asm/sgialib.h&gt;
DECL|macro|DEBUG_PROM_TREE
mdefine_line|#define DEBUG_PROM_TREE
DECL|function|prom_getsibling
id|pcomponent
op_star
id|prom_getsibling
c_func
(paren
id|pcomponent
op_star
id|this
)paren
(brace
r_if
c_cond
(paren
id|this
op_eq
id|PROM_NULL_COMPONENT
)paren
(brace
r_return
id|PROM_NULL_COMPONENT
suffix:semicolon
)brace
r_return
id|romvec
op_member_access_from_pointer
id|next_component
c_func
(paren
id|this
)paren
suffix:semicolon
)brace
DECL|function|prom_getchild
id|pcomponent
op_star
id|prom_getchild
c_func
(paren
id|pcomponent
op_star
id|this
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|child_component
c_func
(paren
id|this
)paren
suffix:semicolon
)brace
DECL|function|prom_getparent
id|pcomponent
op_star
id|prom_getparent
c_func
(paren
id|pcomponent
op_star
id|child
)paren
(brace
r_if
c_cond
(paren
id|child
op_eq
id|PROM_NULL_COMPONENT
)paren
(brace
r_return
id|PROM_NULL_COMPONENT
suffix:semicolon
)brace
r_return
id|romvec
op_member_access_from_pointer
id|parent_component
c_func
(paren
id|child
)paren
suffix:semicolon
)brace
DECL|function|prom_getcdata
r_int
id|prom_getcdata
c_func
(paren
r_void
op_star
id|buffer
comma
id|pcomponent
op_star
id|this
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|component_data
c_func
(paren
id|buffer
comma
id|this
)paren
suffix:semicolon
)brace
DECL|function|prom_childadd
id|pcomponent
op_star
id|prom_childadd
c_func
(paren
id|pcomponent
op_star
id|this
comma
id|pcomponent
op_star
id|tmp
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|child_add
c_func
(paren
id|this
comma
id|tmp
comma
id|data
)paren
suffix:semicolon
)brace
DECL|function|prom_delcomponent
r_int
id|prom_delcomponent
c_func
(paren
id|pcomponent
op_star
id|this
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|comp_del
c_func
(paren
id|this
)paren
suffix:semicolon
)brace
DECL|function|prom_componentbypath
id|pcomponent
op_star
id|prom_componentbypath
c_func
(paren
r_char
op_star
id|path
)paren
(brace
r_return
id|romvec
op_member_access_from_pointer
id|component_by_path
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_PROM_TREE
DECL|variable|classes
r_static
r_char
op_star
id|classes
(braket
)braket
op_assign
(brace
l_string|&quot;system&quot;
comma
l_string|&quot;processor&quot;
comma
l_string|&quot;cache&quot;
comma
l_string|&quot;adapter&quot;
comma
l_string|&quot;controller&quot;
comma
l_string|&quot;peripheral&quot;
comma
l_string|&quot;memory&quot;
)brace
suffix:semicolon
DECL|variable|types
r_static
r_char
op_star
id|types
(braket
)braket
op_assign
(brace
l_string|&quot;arc&quot;
comma
l_string|&quot;cpu&quot;
comma
l_string|&quot;fpu&quot;
comma
l_string|&quot;picache&quot;
comma
l_string|&quot;pdcache&quot;
comma
l_string|&quot;sicache&quot;
comma
l_string|&quot;sdcache&quot;
comma
l_string|&quot;sccache&quot;
comma
l_string|&quot;memdev&quot;
comma
l_string|&quot;eisa adapter&quot;
comma
l_string|&quot;tc adapter&quot;
comma
l_string|&quot;scsi adapter&quot;
comma
l_string|&quot;dti adapter&quot;
comma
l_string|&quot;multi-func adapter&quot;
comma
l_string|&quot;disk controller&quot;
comma
l_string|&quot;tp controller&quot;
comma
l_string|&quot;cdrom controller&quot;
comma
l_string|&quot;worm controller&quot;
comma
l_string|&quot;serial controller&quot;
comma
l_string|&quot;net controller&quot;
comma
l_string|&quot;display controller&quot;
comma
l_string|&quot;parallel controller&quot;
comma
l_string|&quot;pointer controller&quot;
comma
l_string|&quot;keyboard controller&quot;
comma
l_string|&quot;audio controller&quot;
comma
l_string|&quot;misc controller&quot;
comma
l_string|&quot;disk peripheral&quot;
comma
l_string|&quot;floppy peripheral&quot;
comma
l_string|&quot;tp peripheral&quot;
comma
l_string|&quot;modem peripheral&quot;
comma
l_string|&quot;monitor peripheral&quot;
comma
l_string|&quot;printer peripheral&quot;
comma
l_string|&quot;pointer peripheral&quot;
comma
l_string|&quot;keyboard peripheral&quot;
comma
l_string|&quot;terminal peripheral&quot;
comma
l_string|&quot;line peripheral&quot;
comma
l_string|&quot;net peripheral&quot;
comma
l_string|&quot;misc peripheral&quot;
comma
l_string|&quot;anonymous&quot;
)brace
suffix:semicolon
DECL|variable|iflags
r_static
r_char
op_star
id|iflags
(braket
)braket
op_assign
(brace
l_string|&quot;bogus&quot;
comma
l_string|&quot;read only&quot;
comma
l_string|&quot;removable&quot;
comma
l_string|&quot;console in&quot;
comma
l_string|&quot;console out&quot;
comma
l_string|&quot;input&quot;
comma
l_string|&quot;output&quot;
)brace
suffix:semicolon
DECL|function|dump_component
r_static
r_void
id|dump_component
c_func
(paren
id|pcomponent
op_star
id|p
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;[%p]:class&lt;%s&gt;type&lt;%s&gt;flags&lt;%s&gt;ver&lt;%d&gt;rev&lt;%d&gt;&quot;
comma
id|p
comma
id|classes
(braket
id|p
op_member_access_from_pointer
r_class
)braket
comma
id|types
(braket
id|p-&gt;type
)braket
comma
id|iflags
(braket
id|p-&gt;iflags
)braket
comma
id|p-&gt;vers
comma
id|p-&gt;rev
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;key&lt;%08lx&gt;&bslash;n&bslash;tamask&lt;%08lx&gt;cdsize&lt;%d&gt;ilen&lt;%d&gt;iname&lt;%s&gt;&bslash;n&quot;
comma
id|p-&gt;key
comma
id|p-&gt;amask
comma
(paren
r_int
)paren
id|p-&gt;cdsize
comma
(paren
r_int
)paren
id|p-&gt;ilen
comma
id|p-&gt;iname
)paren
suffix:semicolon
)brace
DECL|function|traverse
r_static
r_void
id|traverse
c_func
(paren
id|pcomponent
op_star
id|p
comma
r_int
id|op
)paren
(brace
id|dump_component
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_getchild
c_func
(paren
id|p
)paren
)paren
(brace
id|traverse
c_func
(paren
id|prom_getchild
c_func
(paren
id|p
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prom_getsibling
c_func
(paren
id|p
)paren
op_logical_and
id|op
)paren
(brace
id|traverse
c_func
(paren
id|prom_getsibling
c_func
(paren
id|p
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|prom_testtree
r_void
id|prom_testtree
c_func
(paren
r_void
)paren
(brace
id|pcomponent
op_star
id|p
suffix:semicolon
id|p
op_assign
id|prom_getchild
c_func
(paren
id|PROM_NULL_COMPONENT
)paren
suffix:semicolon
id|dump_component
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|prom_getchild
c_func
(paren
id|p
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
id|dump_component
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_assign
id|prom_getsibling
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;press a key&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof