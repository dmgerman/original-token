multiline_comment|/* &n; * Copyright (c) 1991, 1993&n; *&t;The Regents of the University of California.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. All advertising materials mentioning features or use of this software&n; *    must display the following acknowledgement:&n; *&t;This product includes software developed by the University of&n; *&t;California, Berkeley and its contributors.&n; * 4. Neither the name of the University nor the names of its contributors&n; *    may be used to endorse or promote products derived from this software&n; *    without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; *&t;@(#)queue.h&t;8.3 (Berkeley) 12/13/93&n; */
multiline_comment|/*&n; * Define the BSD singly linked queues which Linux doesn&squot;t&n; * define (yet).&n; */
macro_line|#include &lt;sys/queue.h&gt;
macro_line|#if !defined(SLIST_HEAD) &amp;&amp; !defined(__BSD_Q__)
DECL|macro|__BSD_Q__
mdefine_line|#define __BSD_Q__
DECL|macro|SLIST_HEAD
mdefine_line|#define SLIST_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *slh_first;&t;/* first element */&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_ENTRY
mdefine_line|#define SLIST_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *sle_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked List functions.&n; */
DECL|macro|SLIST_EMPTY
mdefine_line|#define&t;SLIST_EMPTY(head)&t;((head)-&gt;slh_first == NULL)
DECL|macro|SLIST_FIRST
mdefine_line|#define&t;SLIST_FIRST(head)&t;((head)-&gt;slh_first)
DECL|macro|SLIST_INIT
mdefine_line|#define SLIST_INIT(head) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_INSERT_AFTER
mdefine_line|#define SLIST_INSERT_AFTER(slistelm, elm, field) {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.sle_next = (slistelm)-&gt;field.sle_next;&t;&t;&bslash;&n;&t;(slistelm)-&gt;field.sle_next = (elm);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_INSERT_HEAD
mdefine_line|#define SLIST_INSERT_HEAD(head, elm, field) {&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.sle_next = (head)-&gt;slh_first;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_NEXT
mdefine_line|#define SLIST_NEXT(elm, field)&t;((elm)-&gt;field.sle_next)
DECL|macro|SLIST_REMOVE_HEAD
mdefine_line|#define SLIST_REMOVE_HEAD(head, field) {&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = (head)-&gt;slh_first-&gt;field.sle_next;&t;&t;&bslash;&n;}
DECL|macro|SLIST_REMOVE
mdefine_line|#define SLIST_REMOVE(head, elm, type, field) {&t;&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;slh_first == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;SLIST_REMOVE_HEAD((head), field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = (head)-&gt;slh_first;&t;&t;&bslash;&n;&t;&t;while( curelm-&gt;field.sle_next != (elm) )&t;&t;&bslash;&n;&t;&t;&t;curelm = curelm-&gt;field.sle_next;&t;&t;&bslash;&n;&t;&t;curelm-&gt;field.sle_next =&t;&t;&t;&t;&bslash;&n;&t;&t;    curelm-&gt;field.sle_next-&gt;field.sle_next;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked Tail queue definitions.&n; */
DECL|macro|STAILQ_HEAD
mdefine_line|#define STAILQ_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqh_first;/* first element */&t;&t;&t;&bslash;&n;&t;struct type **stqh_last;/* addr of last next element */&t;&t;&bslash;&n;}
DECL|macro|STAILQ_ENTRY
mdefine_line|#define STAILQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqe_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked Tail queue functions.&n; */
DECL|macro|STAILQ_INIT
mdefine_line|#define&t;STAILQ_INIT(head) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;(head)-&gt;stqh_first;&t;&t;&t;&bslash;&n;}
DECL|macro|STAILQ_INSERT_HEAD
mdefine_line|#define STAILQ_INSERT_HEAD(head, elm, field) {&t;&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.stqe_next = (head)-&gt;stqh_first) == NULL)&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|STAILQ_INSERT_TAIL
mdefine_line|#define STAILQ_INSERT_TAIL(head, elm, field) {&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.stqe_next = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;*(head)-&gt;stqh_last = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&t;&bslash;&n;}
DECL|macro|STAILQ_INSERT_AFTER
mdefine_line|#define STAILQ_INSERT_AFTER(head, tqelm, elm, field) {&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.stqe_next = (tqelm)-&gt;field.stqe_next) == NULL)&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;(tqelm)-&gt;field.stqe_next = (elm);&t;&t;&t;&t;&bslash;&n;}
DECL|macro|STAILQ_REMOVE_HEAD
mdefine_line|#define STAILQ_REMOVE_HEAD(head, field) {&t;&t;&t;&t;&bslash;&n;&t;if (((head)-&gt;stqh_first =&t;&t;&t;&t;&t;&bslash;&n;&t;     (head)-&gt;stqh_first-&gt;field.stqe_next) == NULL)&t;&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(head)-&gt;stqh_first;&t;&t;&bslash;&n;}
DECL|macro|STAILQ_REMOVE
mdefine_line|#define STAILQ_REMOVE(head, elm, type, field) {&t;&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;stqh_first == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;STAILQ_REMOVE_HEAD(head, field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = (head)-&gt;stqh_first;&t;&t;&bslash;&n;&t;&t;while( curelm-&gt;field.stqe_next != (elm) )&t;&t;&bslash;&n;&t;&t;&t;curelm = curelm-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;&t;if((curelm-&gt;field.stqe_next =&t;&t;&t;&t;&bslash;&n;&t;&t;    curelm-&gt;field.stqe_next-&gt;field.stqe_next) == NULL)&t;&bslash;&n;&t;&t;&t;(head)-&gt;stqh_last = &amp;(curelm)-&gt;field.stqe_next;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof
