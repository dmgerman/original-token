multiline_comment|/*&n; * Copyright (c) 1991, 1993&n; *&t;The Regents of the University of California.  All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. All advertising materials mentioning features or use of this software&n; *    must display the following acknowledgement:&n; *&t;This product includes software developed by the University of&n; *&t;California, Berkeley and its contributors.&n; * 4. Neither the name of the University nor the names of its contributors&n; *    may be used to endorse or promote products derived from this software&n; *    without specific prior written permission.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; *&t;@(#)queue.h&t;8.5 (Berkeley) 8/20/94&n; * $Id: queue.h,v 1.21 1998/05/12 03:55:25 gibbs Exp $&n; */
macro_line|#ifndef _SYS_QUEUE_H_
DECL|macro|_SYS_QUEUE_H_
mdefine_line|#define&t;_SYS_QUEUE_H_
multiline_comment|/*&n; * This file defines five types of data structures: singly-linked lists,&n; * slingly-linked tail queues, lists, tail queues, and circular queues.&n; *&n; * A singly-linked list is headed by a single forward pointer. The elements&n; * are singly linked for minimum space and pointer manipulation overhead at&n; * the expense of O(n) removal for arbitrary elements. New elements can be&n; * added to the list after an existing element or at the head of the list.&n; * Elements being removed from the head of the list should use the explicit&n; * macro for this purpose for optimum efficiency. A singly-linked list may&n; * only be traversed in the forward direction.  Singly-linked lists are ideal&n; * for applications with large datasets and few or no removals or for&n; * implementing a LIFO queue.&n; *&n; * A singly-linked tail queue is headed by a pair of pointers, one to the&n; * head of the list and the other to the tail of the list. The elements are&n; * singly linked for minimum space and pointer manipulation overhead at the&n; * expense of O(n) removal for arbitrary elements. New elements can be added&n; * to the list after an existing element, at the head of the list, or at the&n; * end of the list. Elements being removed from the head of the tail queue&n; * should use the explicit macro for this purpose for optimum efficiency.&n; * A singly-linked tail queue may only be traversed in the forward direction.&n; * Singly-linked tail queues are ideal for applications with large datasets&n; * and few or no removals or for implementing a FIFO queue.&n; *&n; * A list is headed by a single forward pointer (or an array of forward&n; * pointers for a hash table header). The elements are doubly linked&n; * so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before&n; * or after an existing element or at the head of the list. A list&n; * may only be traversed in the forward direction.&n; *&n; * A tail queue is headed by a pair of pointers, one to the head of the&n; * list and the other to the tail of the list. The elements are doubly&n; * linked so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before or&n; * after an existing element, at the head of the list, or at the end of&n; * the list. A tail queue may only be traversed in the forward direction.&n; *&n; * A circle queue is headed by a pair of pointers, one to the head of the&n; * list and the other to the tail of the list. The elements are doubly&n; * linked so that an arbitrary element can be removed without a need to&n; * traverse the list. New elements can be added to the list before or after&n; * an existing element, at the head of the list, or at the end of the list.&n; * A circle queue may be traversed in either direction, but has a more&n; * complex end of list detection.&n; *&n; * For details on the use of these macros, see the queue(3) manual page.&n; *&n; *&n; *&t;&t;&t;SLIST&t;LIST&t;STAILQ&t;TAILQ&t;CIRCLEQ&n; * _HEAD&t;&t;+&t;+&t;+&t;+&t;+&n; * _ENTRY&t;&t;+&t;+&t;+&t;+&t;+&n; * _INIT&t;&t;+&t;+&t;+&t;+&t;+&n; * _EMPTY&t;&t;+&t;+&t;+&t;+&t;+&n; * _FIRST&t;&t;+&t;+&t;-&t;+&t;+&n; * _NEXT&t;&t;+&t;+&t;-&t;+&t;+&n; * _PREV&t;&t;-&t;-&t;-&t;+&t;+&n; * _LAST&t;&t;-&t;-&t;-&t;+&t;+&n; * _FOREACH&t;&t;+&t;+&t;-&t;+&t;-&n; * _INSERT_HEAD&t;&t;+&t;+&t;+&t;+&t;+&n; * _INSERT_BEFORE&t;-&t;+&t;-&t;+&t;+&n; * _INSERT_AFTER&t;+&t;+&t;+&t;+&t;+&n; * _INSERT_TAIL&t;&t;-&t;-&t;+&t;+&t;+&n; * _REMOVE_HEAD&t;&t;+&t;-&t;+&t;-&t;-&n; * _REMOVE&t;&t;+&t;+&t;+&t;+&t;+&n; *&n; */
multiline_comment|/*&n; * Singly-linked List definitions.&n; */
DECL|macro|SLIST_HEAD
mdefine_line|#define SLIST_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *slh_first;&t;/* first element */&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_ENTRY
mdefine_line|#define SLIST_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *sle_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked List functions.&n; */
DECL|macro|SLIST_EMPTY
mdefine_line|#define&t;SLIST_EMPTY(head)&t;((head)-&gt;slh_first == NULL)
DECL|macro|SLIST_FIRST
mdefine_line|#define&t;SLIST_FIRST(head)&t;((head)-&gt;slh_first)
DECL|macro|SLIST_FOREACH
mdefine_line|#define SLIST_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for((var) = (head)-&gt;slh_first; (var); (var) = (var)-&gt;field.sle_next)
DECL|macro|SLIST_INIT
mdefine_line|#define SLIST_INIT(head) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SLIST_INSERT_AFTER
mdefine_line|#define SLIST_INSERT_AFTER(slistelm, elm, field) do  {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.sle_next = (slistelm)-&gt;field.sle_next;&t;&t;&bslash;&n;&t;(slistelm)-&gt;field.sle_next = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_INSERT_HEAD
mdefine_line|#define SLIST_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.sle_next = (head)-&gt;slh_first;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_NEXT
mdefine_line|#define SLIST_NEXT(elm, field)&t;((elm)-&gt;field.sle_next)
DECL|macro|SLIST_REMOVE_HEAD
mdefine_line|#define SLIST_REMOVE_HEAD(head, field) do {&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;slh_first = (head)-&gt;slh_first-&gt;field.sle_next;&t;&t;&bslash;&n;} while (0)
DECL|macro|SLIST_REMOVE
mdefine_line|#define SLIST_REMOVE(head, elm, type, field) do {&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;slh_first == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;SLIST_REMOVE_HEAD((head), field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = (head)-&gt;slh_first;&t;&t;&bslash;&n;&t;&t;while( curelm-&gt;field.sle_next != (elm) )&t;&t;&bslash;&n;&t;&t;&t;curelm = curelm-&gt;field.sle_next;&t;&t;&bslash;&n;&t;&t;curelm-&gt;field.sle_next =&t;&t;&t;&t;&bslash;&n;&t;&t;    curelm-&gt;field.sle_next-&gt;field.sle_next;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Singly-linked Tail queue definitions.&n; */
DECL|macro|STAILQ_HEAD
mdefine_line|#define STAILQ_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqh_first;/* first element */&t;&t;&t;&bslash;&n;&t;struct type **stqh_last;/* addr of last next element */&t;&t;&bslash;&n;}
DECL|macro|STAILQ_ENTRY
mdefine_line|#define STAILQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *stqe_next;&t;/* next element */&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Singly-linked Tail queue functions.&n; */
DECL|macro|STAILQ_EMPTY
mdefine_line|#define STAILQ_EMPTY(head) ((head)-&gt;stqh_first == NULL)
DECL|macro|STAILQ_INIT
mdefine_line|#define&t;STAILQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;(head)-&gt;stqh_first;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_FIRST
mdefine_line|#define STAILQ_FIRST(head)&t;((head)-&gt;stqh_first)
DECL|macro|STAILQ_LAST
mdefine_line|#define STAILQ_LAST(head)&t;(*(head)-&gt;stqh_last)
DECL|macro|STAILQ_INSERT_HEAD
mdefine_line|#define STAILQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.stqe_next = (head)-&gt;stqh_first) == NULL)&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_INSERT_TAIL
mdefine_line|#define STAILQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.stqe_next = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;*(head)-&gt;stqh_last = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_INSERT_AFTER
mdefine_line|#define STAILQ_INSERT_AFTER(head, tqelm, elm, field) do {&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.stqe_next = (tqelm)-&gt;field.stqe_next) == NULL)&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(elm)-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;(tqelm)-&gt;field.stqe_next = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_NEXT
mdefine_line|#define STAILQ_NEXT(elm, field)&t;((elm)-&gt;field.stqe_next)
DECL|macro|STAILQ_REMOVE_HEAD
mdefine_line|#define STAILQ_REMOVE_HEAD(head, field) do {&t;&t;&t;&t;&bslash;&n;&t;if (((head)-&gt;stqh_first =&t;&t;&t;&t;&t;&bslash;&n;&t;     (head)-&gt;stqh_first-&gt;field.stqe_next) == NULL)&t;&t;&bslash;&n;&t;&t;(head)-&gt;stqh_last = &amp;(head)-&gt;stqh_first;&t;&t;&bslash;&n;} while (0)
DECL|macro|STAILQ_REMOVE
mdefine_line|#define STAILQ_REMOVE(head, elm, type, field) do {&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;stqh_first == (elm)) {&t;&t;&t;&t;&bslash;&n;&t;&t;STAILQ_REMOVE_HEAD(head, field);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;struct type *curelm = (head)-&gt;stqh_first;&t;&t;&bslash;&n;&t;&t;while( curelm-&gt;field.stqe_next != (elm) )&t;&t;&bslash;&n;&t;&t;&t;curelm = curelm-&gt;field.stqe_next;&t;&t;&bslash;&n;&t;&t;if((curelm-&gt;field.stqe_next =&t;&t;&t;&t;&bslash;&n;&t;&t;    curelm-&gt;field.stqe_next-&gt;field.stqe_next) == NULL)&t;&bslash;&n;&t;&t;&t;(head)-&gt;stqh_last = &amp;(curelm)-&gt;field.stqe_next;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * List definitions.&n; */
DECL|macro|LIST_ENTRY
mdefine_line|#define LIST_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *le_next;&t;/* next element */&t;&t;&t;&bslash;&n;&t;struct type **le_prev;&t;/* address of previous next element */&t;&bslash;&n;}
multiline_comment|/*&n; * List functions.&n; */
DECL|macro|LIST_EMPTY
mdefine_line|#define&t;LIST_EMPTY(head) ((head)-&gt;lh_first == NULL)
DECL|macro|LIST_FIRST
mdefine_line|#define LIST_FIRST(head)&t;((head)-&gt;lh_first)
DECL|macro|LIST_FOREACH
mdefine_line|#define LIST_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for((var) = (head)-&gt;lh_first; (var); (var) = (var)-&gt;field.le_next)
DECL|macro|LIST_INIT
mdefine_line|#define&t;LIST_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;lh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_AFTER
mdefine_line|#define LIST_INSERT_AFTER(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.le_next = (listelm)-&gt;field.le_next) != NULL)&t;&bslash;&n;&t;&t;(listelm)-&gt;field.le_next-&gt;field.le_prev =&t;&t;&bslash;&n;&t;&t;    &amp;(elm)-&gt;field.le_next;&t;&t;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.le_next = (elm);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = &amp;(listelm)-&gt;field.le_next;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_BEFORE
mdefine_line|#define LIST_INSERT_BEFORE(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = (listelm)-&gt;field.le_prev;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_next = (listelm);&t;&t;&t;&t;&bslash;&n;&t;*(listelm)-&gt;field.le_prev = (elm);&t;&t;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.le_prev = &amp;(elm)-&gt;field.le_next;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_INSERT_HEAD
mdefine_line|#define LIST_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.le_next = (head)-&gt;lh_first) != NULL)&t;&t;&bslash;&n;&t;&t;(head)-&gt;lh_first-&gt;field.le_prev = &amp;(elm)-&gt;field.le_next;&bslash;&n;&t;(head)-&gt;lh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.le_prev = &amp;(head)-&gt;lh_first;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|LIST_NEXT
mdefine_line|#define LIST_NEXT(elm, field)&t;((elm)-&gt;field.le_next)
DECL|macro|LIST_REMOVE
mdefine_line|#define LIST_REMOVE(elm, field) do {&t;&t;&t;&t;&t;&bslash;&n;&t;if ((elm)-&gt;field.le_next != NULL)&t;&t;&t;&t;&bslash;&n;&t;&t;(elm)-&gt;field.le_next-&gt;field.le_prev = &t;&t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.le_prev;&t;&t;&t;&t;&bslash;&n;&t;*(elm)-&gt;field.le_prev = (elm)-&gt;field.le_next;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Tail queue definitions.&n; */
DECL|macro|TAILQ_HEAD
mdefine_line|#define TAILQ_HEAD(name, type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *tqh_first;&t;/* first element */&t;&t;&t;&bslash;&n;&t;struct type **tqh_last;&t;/* addr of last next element */&t;&t;&bslash;&n;}
DECL|macro|TAILQ_HEAD_INITIALIZER
mdefine_line|#define TAILQ_HEAD_INITIALIZER(head)&t;&t;&t;&t;&t;&bslash;&n;&t;{ NULL, &amp;(head).tqh_first }
DECL|macro|TAILQ_ENTRY
mdefine_line|#define TAILQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *tqe_next;&t;/* next element */&t;&t;&t;&bslash;&n;&t;struct type **tqe_prev;&t;/* address of previous next element */&t;&bslash;&n;}
multiline_comment|/*&n; * Tail queue functions.&n; */
DECL|macro|TAILQ_EMPTY
mdefine_line|#define&t;TAILQ_EMPTY(head) ((head)-&gt;tqh_first == NULL)
DECL|macro|TAILQ_FOREACH
mdefine_line|#define TAILQ_FOREACH(var, head, field)&t;&t;&t;&t;&t;&bslash;&n;&t;for (var = TAILQ_FIRST(head); var; var = TAILQ_NEXT(var, field))
DECL|macro|TAILQ_FIRST
mdefine_line|#define&t;TAILQ_FIRST(head) ((head)-&gt;tqh_first)
DECL|macro|TAILQ_LAST
mdefine_line|#define&t;TAILQ_LAST(head, headname) &bslash;&n;&t;(*(((struct headname *)((head)-&gt;tqh_last))-&gt;tqh_last))
DECL|macro|TAILQ_NEXT
mdefine_line|#define&t;TAILQ_NEXT(elm, field) ((elm)-&gt;field.tqe_next)
DECL|macro|TAILQ_PREV
mdefine_line|#define TAILQ_PREV(elm, headname, field) &bslash;&n;&t;(*(((struct headname *)((elm)-&gt;field.tqe_prev))-&gt;tqh_last))
DECL|macro|TAILQ_INIT
mdefine_line|#define&t;TAILQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_first = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_last = &amp;(head)-&gt;tqh_first;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_HEAD
mdefine_line|#define TAILQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.tqe_next = (head)-&gt;tqh_first) != NULL)&t;&bslash;&n;&t;&t;(head)-&gt;tqh_first-&gt;field.tqe_prev =&t;&t;&t;&bslash;&n;&t;&t;    &amp;(elm)-&gt;field.tqe_next;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = &amp;(elm)-&gt;field.tqe_next;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = &amp;(head)-&gt;tqh_first;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_TAIL
mdefine_line|#define TAILQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_next = NULL;&t;&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = (head)-&gt;tqh_last;&t;&t;&t;&bslash;&n;&t;*(head)-&gt;tqh_last = (elm);&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;tqh_last = &amp;(elm)-&gt;field.tqe_next;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_AFTER
mdefine_line|#define TAILQ_INSERT_AFTER(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.tqe_next = (listelm)-&gt;field.tqe_next) != NULL)&bslash;&n;&t;&t;(elm)-&gt;field.tqe_next-&gt;field.tqe_prev = &t;&t;&bslash;&n;&t;&t;    &amp;(elm)-&gt;field.tqe_next;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = &amp;(elm)-&gt;field.tqe_next;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.tqe_next = (elm);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = &amp;(listelm)-&gt;field.tqe_next;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_INSERT_BEFORE
mdefine_line|#define TAILQ_INSERT_BEFORE(listelm, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_prev = (listelm)-&gt;field.tqe_prev;&t;&t;&bslash;&n;&t;(elm)-&gt;field.tqe_next = (listelm);&t;&t;&t;&t;&bslash;&n;&t;*(listelm)-&gt;field.tqe_prev = (elm);&t;&t;&t;&t;&bslash;&n;&t;(listelm)-&gt;field.tqe_prev = &amp;(elm)-&gt;field.tqe_next;&t;&t;&bslash;&n;} while (0)
DECL|macro|TAILQ_REMOVE
mdefine_line|#define TAILQ_REMOVE(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if (((elm)-&gt;field.tqe_next) != NULL)&t;&t;&t;&t;&bslash;&n;&t;&t;(elm)-&gt;field.tqe_next-&gt;field.tqe_prev = &t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.tqe_prev;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;tqh_last = (elm)-&gt;field.tqe_prev;&t;&t;&bslash;&n;&t;*(elm)-&gt;field.tqe_prev = (elm)-&gt;field.tqe_next;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Circular queue definitions.&n; */
DECL|macro|CIRCLEQ_HEAD
mdefine_line|#define CIRCLEQ_HEAD(name, type)&t;&t;&t;&t;&t;&bslash;&n;struct name {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *cqh_first;&t;&t;/* first element */&t;&t;&bslash;&n;&t;struct type *cqh_last;&t;&t;/* last element */&t;&t;&bslash;&n;}
DECL|macro|CIRCLEQ_ENTRY
mdefine_line|#define CIRCLEQ_ENTRY(type)&t;&t;&t;&t;&t;&t;&bslash;&n;struct {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct type *cqe_next;&t;&t;/* next element */&t;&t;&bslash;&n;&t;struct type *cqe_prev;&t;&t;/* previous element */&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Circular queue functions.&n; */
DECL|macro|CIRCLEQ_EMPTY
mdefine_line|#define CIRCLEQ_EMPTY(head) ((head)-&gt;cqh_first == (void *)(head))
DECL|macro|CIRCLEQ_FIRST
mdefine_line|#define CIRCLEQ_FIRST(head) ((head)-&gt;cqh_first)
DECL|macro|CIRCLEQ_FOREACH
mdefine_line|#define CIRCLEQ_FOREACH(var, head, field)&t;&t;&t;&t;&bslash;&n;&t;for((var) = (head)-&gt;cqh_first;&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) != (void *)(head);&t;&t;&t;&t;&t;&bslash;&n;&t;    (var) = (var)-&gt;field.cqe_next)
DECL|macro|CIRCLEQ_INIT
mdefine_line|#define&t;CIRCLEQ_INIT(head) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;cqh_first = (void *)(head);&t;&t;&t;&t;&bslash;&n;&t;(head)-&gt;cqh_last = (void *)(head);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_AFTER
mdefine_line|#define CIRCLEQ_INSERT_AFTER(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_next = (listelm)-&gt;field.cqe_next;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_prev = (listelm);&t;&t;&t;&t;&bslash;&n;&t;if ((listelm)-&gt;field.cqe_next == (void *)(head))&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_last = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(listelm)-&gt;field.cqe_next-&gt;field.cqe_prev = (elm);&t;&bslash;&n;&t;(listelm)-&gt;field.cqe_next = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_BEFORE
mdefine_line|#define CIRCLEQ_INSERT_BEFORE(head, listelm, elm, field) do {&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_next = (listelm);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_prev = (listelm)-&gt;field.cqe_prev;&t;&t;&bslash;&n;&t;if ((listelm)-&gt;field.cqe_prev == (void *)(head))&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_first = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(listelm)-&gt;field.cqe_prev-&gt;field.cqe_next = (elm);&t;&bslash;&n;&t;(listelm)-&gt;field.cqe_prev = (elm);&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_HEAD
mdefine_line|#define CIRCLEQ_INSERT_HEAD(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_next = (head)-&gt;cqh_first;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_prev = (void *)(head);&t;&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;cqh_last == (void *)(head))&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_last = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_first-&gt;field.cqe_prev = (elm);&t;&t;&bslash;&n;&t;(head)-&gt;cqh_first = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_INSERT_TAIL
mdefine_line|#define CIRCLEQ_INSERT_TAIL(head, elm, field) do {&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_next = (void *)(head);&t;&t;&t;&t;&bslash;&n;&t;(elm)-&gt;field.cqe_prev = (head)-&gt;cqh_last;&t;&t;&t;&bslash;&n;&t;if ((head)-&gt;cqh_first == (void *)(head))&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_first = (elm);&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_last-&gt;field.cqe_next = (elm);&t;&t;&bslash;&n;&t;(head)-&gt;cqh_last = (elm);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|CIRCLEQ_LAST
mdefine_line|#define CIRCLEQ_LAST(head) ((head)-&gt;cqh_last)
DECL|macro|CIRCLEQ_NEXT
mdefine_line|#define CIRCLEQ_NEXT(elm,field) ((elm)-&gt;field.cqe_next)
DECL|macro|CIRCLEQ_PREV
mdefine_line|#define CIRCLEQ_PREV(elm,field) ((elm)-&gt;field.cqe_prev)
DECL|macro|CIRCLEQ_REMOVE
mdefine_line|#define&t;CIRCLEQ_REMOVE(head, elm, field) do {&t;&t;&t;&t;&bslash;&n;&t;if ((elm)-&gt;field.cqe_next == (void *)(head))&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_last = (elm)-&gt;field.cqe_prev;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(elm)-&gt;field.cqe_next-&gt;field.cqe_prev =&t;&t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.cqe_prev;&t;&t;&t;&t;&bslash;&n;&t;if ((elm)-&gt;field.cqe_prev == (void *)(head))&t;&t;&t;&bslash;&n;&t;&t;(head)-&gt;cqh_first = (elm)-&gt;field.cqe_next;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(elm)-&gt;field.cqe_prev-&gt;field.cqe_next =&t;&t;&t;&bslash;&n;&t;&t;    (elm)-&gt;field.cqe_next;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#ifdef KERNEL
multiline_comment|/*&n; * XXX insque() and remque() are an old way of handling certain queues.&n; * They bogusly assumes that all queue heads look alike.&n; */
DECL|struct|quehead
r_struct
id|quehead
(brace
DECL|member|qh_link
r_struct
id|quehead
op_star
id|qh_link
suffix:semicolon
DECL|member|qh_rlink
r_struct
id|quehead
op_star
id|qh_rlink
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef&t;__GNUC__
r_static
id|__inline
r_void
DECL|function|insque
id|insque
c_func
(paren
r_void
op_star
id|a
comma
r_void
op_star
id|b
)paren
(brace
r_struct
id|quehead
op_star
id|element
op_assign
id|a
comma
op_star
id|head
op_assign
id|b
suffix:semicolon
id|element-&gt;qh_link
op_assign
id|head-&gt;qh_link
suffix:semicolon
id|element-&gt;qh_rlink
op_assign
id|head
suffix:semicolon
id|head-&gt;qh_link
op_assign
id|element
suffix:semicolon
id|element-&gt;qh_link-&gt;qh_rlink
op_assign
id|element
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|remque
id|remque
c_func
(paren
r_void
op_star
id|a
)paren
(brace
r_struct
id|quehead
op_star
id|element
op_assign
id|a
suffix:semicolon
id|element-&gt;qh_link-&gt;qh_rlink
op_assign
id|element-&gt;qh_rlink
suffix:semicolon
id|element-&gt;qh_rlink-&gt;qh_link
op_assign
id|element-&gt;qh_link
suffix:semicolon
id|element-&gt;qh_rlink
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#else /* !__GNUC__ */
r_void
id|insque
id|__P
c_func
(paren
(paren
r_void
op_star
id|a
comma
r_void
op_star
id|b
)paren
)paren
suffix:semicolon
r_void
id|remque
id|__P
c_func
(paren
(paren
r_void
op_star
id|a
)paren
)paren
suffix:semicolon
macro_line|#endif /* __GNUC__ */
macro_line|#endif /* KERNEL */
macro_line|#endif /* !_SYS_QUEUE_H_ */
eof
