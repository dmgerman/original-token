multiline_comment|/*&n; * lists.h:  Simple list macros for Linux&n; */
DECL|macro|DLNODE
mdefine_line|#define DLNODE(ptype)&t;&t;&t;       &t;       &t;       &t;&bslash;&n;&t;struct {&t;&t;&t; &t;&t;&t;&bslash;&n;&t;&t;ptype * dl_prev;&t; &t;&t;&t;&bslash;&n;&t;&t;ptype * dl_next;&t; &t;&t;&t;&bslash;&n;&t;}
DECL|macro|DNODE_SINGLE
mdefine_line|#define DNODE_SINGLE(node) {(node),(node)}
DECL|macro|DNODE_NULL
mdefine_line|#define DNODE_NULL {0,0}
DECL|macro|DLIST_INIT
mdefine_line|#define DLIST_INIT(listnam)&t;                                &bslash;&n;&t;(listnam).dl_prev = &amp;(listnam);&t;&t;&t;&t;&bslash;&n;&t;(listnam).dl_next = &amp;(listnam);
DECL|macro|DLIST_NEXT
mdefine_line|#define DLIST_NEXT(listnam)&t;listnam.dl_next
DECL|macro|DLIST_PREV
mdefine_line|#define DLIST_PREV(listnam)&t;listnam.dl_prev
DECL|macro|DLIST_INSERT_AFTER
mdefine_line|#define DLIST_INSERT_AFTER(node, new, listnam)&t;do {&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_prev = (node);&t;&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_next = (node)-&gt;listnam.dl_next;&t;&bslash;&n;&t;(node)-&gt;listnam.dl_next-&gt;listnam.dl_prev = (new);&t;&bslash;&n;&t;(node)-&gt;listnam.dl_next = (new);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|DLIST_INSERT_BEFORE
mdefine_line|#define DLIST_INSERT_BEFORE(node, new, listnam)&t;do {&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_next = (node);&t;&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_prev = (node)-&gt;listnam.dl_prev;&t;&bslash;&n;&t;(node)-&gt;listnam.dl_prev-&gt;listnam.dl_next = (new);&t;&bslash;&n;&t;(node)-&gt;listnam.dl_prev = (new);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|DLIST_DELETE
mdefine_line|#define DLIST_DELETE(node, listnam)&t;do {&t;&t;&bslash;&n;&t;node-&gt;listnam.dl_prev-&gt;listnam.dl_next =&t;&t;&bslash;&n;&t;&t;node-&gt;listnam.dl_next;&t;&t;&t;&t;&bslash;&n;&t;node-&gt;listnam.dl_next-&gt;listnam.dl_prev =&t;&t;&bslash;&n;&t;&t;node-&gt;listnam.dl_prev;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * queue-style operations, which have a head and tail&n; */
DECL|macro|QUEUE_INIT
mdefine_line|#define QUEUE_INIT(head, listnam, ptype)&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;listnam.dl_prev = (head)-&gt;listnam.dl_next = (ptype)(head);
DECL|macro|QUEUE_FIRST
mdefine_line|#define QUEUE_FIRST(head, listnam) (head)-&gt;DLIST_NEXT(listnam)
DECL|macro|QUEUE_LAST
mdefine_line|#define QUEUE_LAST(head, listnam) (head)-&gt;DLIST_PREV(listnam)
DECL|macro|QUEUE_IS_EMPTY
mdefine_line|#define QUEUE_IS_EMPTY(head, listnam) &bslash;&n;&t;((QUEUE_FIRST(head, listnam) == QUEUE_LAST(head, listnam)) &amp;&amp; &bslash;&n;&t; ((u_long)QUEUE_FIRST(head, listnam) == (u_long)head)) 
DECL|macro|QUEUE_ENTER
mdefine_line|#define QUEUE_ENTER(head, new, listnam, ptype) do {&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_prev = (ptype)(head);&t;&t;&t;&bslash;&n;&t;(new)-&gt;listnam.dl_next = (head)-&gt;listnam.dl_next;&t;&bslash;&n;&t;(head)-&gt;listnam.dl_next-&gt;listnam.dl_prev = (new);&t;&bslash;&n;&t;(head)-&gt;listnam.dl_next = (new);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|QUEUE_REMOVE
mdefine_line|#define QUEUE_REMOVE(head, node, listnam) DLIST_DELETE(node, listnam)
eof
