macro_line|#ifndef DLISTS_H
DECL|macro|DLISTS_H
mdefine_line|#define DLISTS_H
multiline_comment|/*&n; * include/linux/dlists.h - macros for double linked lists&n; *&n; * Copyright (C) 1997, Thomas Schoebel-Theuer,&n; * &lt;schoebel@informatik.uni-stuttgart.de&gt;.&n; */
multiline_comment|/* dlists are cyclic ringlists, so the last element cannot be tested&n; * for NULL. Use the following construct for traversing cyclic lists:&n; * ptr = anchor;&n; * if(ptr) do {&n; *      ...&n; *      ptr = ptr-&gt;{something}_{next,prev};&n; * } while(ptr != anchor);&n; * The effort here is paid off with much simpler inserts/removes.&n; * Examples for usage of these macros can be found in fs/ninode.c.&n; * To access the last element in constant time, simply use&n; * anchor-&gt;{something}_prev.&n; */
DECL|macro|DEF_GENERIC_INSERT
mdefine_line|#define DEF_GENERIC_INSERT(CHANGE,PREFIX,NAME,TYPE,NEXT,PREV) &bslash;&n;static inline void PREFIX##NAME(TYPE ** anchor, TYPE * elem)&bslash;&n;{&bslash;&n;&t;TYPE * oldfirst = *anchor;&bslash;&n;&t;if(!oldfirst) {&bslash;&n;&t;&t;elem-&gt;NEXT = elem-&gt;PREV = *anchor = elem;&bslash;&n;&t;} else {&bslash;&n;&t;&t;elem-&gt;PREV = oldfirst-&gt;PREV;&bslash;&n;&t;&t;elem-&gt;NEXT = oldfirst;&bslash;&n;&t;&t;oldfirst-&gt;PREV-&gt;NEXT = elem;&bslash;&n;&t;&t;oldfirst-&gt;PREV = elem;&bslash;&n;&t;&t;if(CHANGE)&bslash;&n;&t;&t;&t;*anchor = elem;&bslash;&n;&t;}&bslash;&n;}
multiline_comment|/* insert_* is always at the first position */
DECL|macro|DEF_INSERT
mdefine_line|#define DEF_INSERT(NAME,TYPE,NEXT,PREV) &bslash;&n;                   DEF_GENERIC_INSERT(1,insert_,NAME,TYPE,NEXT,PREV)
multiline_comment|/* append_* is always at the tail  */
DECL|macro|DEF_APPEND
mdefine_line|#define DEF_APPEND(NAME,TYPE,NEXT,PREV) &bslash;&n;                   DEF_GENERIC_INSERT(0,append_,NAME,TYPE,NEXT,PREV)
multiline_comment|/* use this to insert _before_ oldelem somewhere in the middle of the list.&n; * the list must not be empty, and oldelem must be already a member.*/
DECL|macro|DEF_INSERT_MIDDLE
mdefine_line|#define DEF_INSERT_MIDDLE(NAME,TYPE) &bslash;&n;static inline void insert_middle_##NAME(TYPE ** anchor, TYPE * oldelem, TYPE * elem)&bslash;&n;{&bslash;&n;&t;int status = (oldelem == *anchor);&bslash;&n;&t;insert_##NAME(&amp;oldelem, elem);&bslash;&n;&t;if(status)&bslash;&n;&t;&t;*anchor = oldelem;&bslash;&n;}
multiline_comment|/* remove can be done with any element in the list */
DECL|macro|DEF_REMOVE
mdefine_line|#define DEF_REMOVE(NAME,TYPE,NEXT,PREV) &bslash;&n;static inline void remove_##NAME(TYPE ** anchor, TYPE * elem)&bslash;&n;{&bslash;&n;&t;TYPE * next = elem-&gt;NEXT;&bslash;&n;&t;if(next == elem) {&bslash;&n;&t;&t;*anchor = NULL;&bslash;&n;&t;} else {&bslash;&n;&t;&t;TYPE * prev = elem-&gt;PREV;&bslash;&n;&t;&t;prev-&gt;NEXT = next;&bslash;&n;&t;&t;next-&gt;PREV = prev;&bslash;&n;&t;&t;elem-&gt;NEXT = elem-&gt;PREV = NULL;/*leave this during debugging*/&bslash;&n;&t;&t;if(*anchor == elem)&bslash;&n;&t;&t;&t;*anchor = next;&bslash;&n;&t;}&bslash;&n;}
multiline_comment|/* According to ideas from David S. Miller, here is a slightly&n; * more efficient plug-in compatible version using non-cyclic lists,&n; * but allowing neither backward traversals nor constant time access&n; * to the last element.&n; * Note that although the interface is the same, the PPREV pointer must be&n; * declared doubly indirect and the test for end-of-list is different. */
multiline_comment|/* as above, this inserts always at the head */
DECL|macro|DEF_LIN_INSERT
mdefine_line|#define DEF_LIN_INSERT(NAME,TYPE,NEXT,PPREV) &bslash;&n;static inline void insert_##NAME(TYPE ** anchor, TYPE * elem)&bslash;&n;{&bslash;&n;&t;TYPE * first;&bslash;&n;&t;if((elem-&gt;NEXT = first = *anchor))&bslash;&n;&t;&t;first-&gt;PPREV = &amp;elem-&gt;NEXT;&bslash;&n;&t;*anchor = elem;&bslash;&n;&t;elem-&gt;PPREV = anchor;&bslash;&n;}
multiline_comment|/* as above, this works with any list element */
DECL|macro|DEF_LIN_REMOVE
mdefine_line|#define DEF_LIN_REMOVE(NAME,TYPE,NEXT,PPREV) &bslash;&n;static inline void remove_##NAME(TYPE ** anchor, TYPE * elem)&bslash;&n;{&bslash;&n;&t;TYPE * pprev;&bslash;&n;&t;if((pprev = elem-&gt;PPREV)) {&bslash;&n;&t;&t;TYPE * next;&bslash;&n;&t;&t;if((next = elem-&gt;NEXT))&bslash;&n;&t;&t;&t;next-&gt;PPREV = pprev;&bslash;&n;&t;&t;*pprev = next;&bslash;&n;&t;&t;elem-&gt;PPREV = elem-&gt;NEXT = NULL; /*leave this for debugging*/&bslash;&n;&t;}&bslash;&n;}
macro_line|#endif
eof
