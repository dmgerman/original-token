macro_line|#ifndef _LINUX_LIST_H
DECL|macro|_LINUX_LIST_H
mdefine_line|#define _LINUX_LIST_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Simple doubly linked list implementation.&n; *&n; * Some of the internal functions (&quot;__xxx&quot;) are useful when&n; * manipulating whole lists rather than single entries, as&n; * sometimes we already know the next/prev entries and we can&n; * generate better code by using them directly rather than&n; * using the generic single-entry routines.&n; */
DECL|struct|list_head
r_struct
id|list_head
(brace
DECL|member|next
DECL|member|prev
r_struct
id|list_head
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LIST_HEAD_INIT
mdefine_line|#define LIST_HEAD_INIT(name) { &amp;(name), &amp;(name) }
DECL|macro|LIST_HEAD
mdefine_line|#define LIST_HEAD(name) &bslash;&n;&t;struct list_head name = LIST_HEAD_INIT(name)
DECL|macro|INIT_LIST_HEAD
mdefine_line|#define INIT_LIST_HEAD(ptr) do { &bslash;&n;&t;(ptr)-&gt;next = (ptr); (ptr)-&gt;prev = (ptr); &bslash;&n;} while (0)
multiline_comment|/*&n; * Insert a new entry between two known consecutive entries. &n; *&n; * This is only for internal list manipulation where we know&n; * the prev/next entries already!&n; */
DECL|function|__list_add
r_static
id|__inline__
r_void
id|__list_add
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|prev
comma
r_struct
id|list_head
op_star
id|next
)paren
(brace
id|next-&gt;prev
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|next
op_assign
id|next
suffix:semicolon
r_new
op_member_access_from_pointer
id|prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
r_new
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add - add a new entry&n; * @new: new entry to be added&n; * @head: list head to add it after&n; *&n; * Insert a new entry after the specified head.&n; * This is good for implementing stacks.&n; */
DECL|function|list_add
r_static
id|__inline__
r_void
id|list_add
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add
c_func
(paren
r_new
comma
id|head
comma
id|head-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_add_tail - add a new entry&n; * @new: new entry to be added&n; * @head: list head to add it before&n; *&n; * Insert a new entry before the specified head.&n; * This is useful for implementing queues.&n; */
DECL|function|list_add_tail
r_static
id|__inline__
r_void
id|list_add_tail
c_func
(paren
r_struct
id|list_head
op_star
r_new
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|__list_add
c_func
(paren
r_new
comma
id|head-&gt;prev
comma
id|head
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a list entry by making the prev/next entries&n; * point to each other.&n; *&n; * This is only for internal list manipulation where we know&n; * the prev/next entries already!&n; */
DECL|function|__list_del
r_static
id|__inline__
r_void
id|__list_del
c_func
(paren
r_struct
id|list_head
op_star
id|prev
comma
r_struct
id|list_head
op_star
id|next
)paren
(brace
id|next-&gt;prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
)brace
multiline_comment|/**&n; * list_del - deletes entry from list.&n; * @entry: the element to delete from the list.&n; * Note: list_empty on entry does not return true after this, the entry is in an undefined state.&n; */
DECL|function|list_del
r_static
id|__inline__
r_void
id|list_del
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
id|__list_del
c_func
(paren
id|entry-&gt;prev
comma
id|entry-&gt;next
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_del_init - deletes entry from list and reinitialize it.&n; * @entry: the element to delete from the list.n &n; */
DECL|function|list_del_init
r_static
id|__inline__
r_void
id|list_del_init
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
id|__list_del
c_func
(paren
id|entry-&gt;prev
comma
id|entry-&gt;next
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * list_empty - tests whether a list is empty&n; * @head: the list to test.&n; */
DECL|function|list_empty
r_static
id|__inline__
r_int
id|list_empty
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_return
id|head-&gt;next
op_eq
id|head
suffix:semicolon
)brace
multiline_comment|/**&n; * list_splice - join two lists&n; * @list: the new list to add.&n; * @head: the place to add it in the first list.&n; */
DECL|function|list_splice
r_static
id|__inline__
r_void
id|list_splice
c_func
(paren
r_struct
id|list_head
op_star
id|list
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|list_head
op_star
id|first
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|first
op_ne
id|list
)paren
(brace
r_struct
id|list_head
op_star
id|last
op_assign
id|list-&gt;prev
suffix:semicolon
r_struct
id|list_head
op_star
id|at
op_assign
id|head-&gt;next
suffix:semicolon
id|first-&gt;prev
op_assign
id|head
suffix:semicolon
id|head-&gt;next
op_assign
id|first
suffix:semicolon
id|last-&gt;next
op_assign
id|at
suffix:semicolon
id|at-&gt;prev
op_assign
id|last
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * list_entry - get the struct for this entry&n; * @ptr:&t;the &amp;struct list_head pointer.&n; * @type:&t;the type of the struct this is embedded in.&n; * @member:&t;the name of the list_struct within the struct.&n; */
DECL|macro|list_entry
mdefine_line|#define list_entry(ptr, type, member) &bslash;&n;&t;((type *)((char *)(ptr)-(unsigned long)(&amp;((type *)0)-&gt;member)))
multiline_comment|/**&n; * list_for_each&t;-&t;iterate over a list&n; * @pos:&t;the &amp;struct list_head to use as a loop counter.&n; * @head:&t;the head for your list.&n; */
DECL|macro|list_for_each
mdefine_line|#define list_for_each(pos, head) &bslash;&n;&t;for (pos = (head)-&gt;next; pos != (head); pos = pos-&gt;next)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
