DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;teles.h&quot;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
r_void
DECL|function|BufPoolInit
id|BufPoolInit
c_func
(paren
r_struct
id|BufPool
op_star
id|bp
comma
r_int
id|order
comma
r_int
id|bpps
comma
r_int
id|maxpages
)paren
(brace
macro_line|#ifdef DEBUG_MAGIC
id|generateerror
id|bp-&gt;magic
op_assign
l_int|010167
suffix:semicolon
macro_line|#endif
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolInit bp %x&bslash;n&quot;
comma
id|bp
)paren
suffix:semicolon
macro_line|#endif
id|bp-&gt;freelist
op_assign
l_int|NULL
suffix:semicolon
id|bp-&gt;pageslist
op_assign
l_int|NULL
suffix:semicolon
id|bp-&gt;pageorder
op_assign
id|order
suffix:semicolon
id|bp-&gt;pagescount
op_assign
l_int|0
suffix:semicolon
id|bp-&gt;bpps
op_assign
id|bpps
suffix:semicolon
id|bp-&gt;bufsize
op_assign
id|BUFFER_SIZE
c_func
(paren
id|order
comma
id|bpps
)paren
suffix:semicolon
id|bp-&gt;maxpages
op_assign
id|maxpages
suffix:semicolon
)brace
r_int
DECL|function|BufPoolAdd
id|BufPoolAdd
c_func
(paren
r_struct
id|BufPool
op_star
id|bp
comma
r_int
id|priority
)paren
(brace
r_struct
id|Pages
op_star
id|ptr
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|byte
op_star
id|bptr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|BufHeader
op_star
id|bh
op_assign
l_int|NULL
comma
op_star
id|prev
comma
op_star
id|first
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolAdd bp %x&bslash;n&quot;
comma
id|bp
)paren
suffix:semicolon
macro_line|#endif
id|ptr
op_assign
(paren
r_struct
id|Pages
op_star
)paren
id|__get_free_pages
c_func
(paren
id|priority
comma
id|bp-&gt;pageorder
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;BufPoolAdd couldn&squot;t get pages!&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Order %d pages allocated at %x&bslash;n&quot;
comma
id|bp-&gt;pageorder
comma
id|ptr
)paren
suffix:semicolon
macro_line|#endif
id|ptr-&gt;next
op_assign
id|bp-&gt;pageslist
suffix:semicolon
id|bp-&gt;pageslist
op_assign
id|ptr
suffix:semicolon
id|bp-&gt;pagescount
op_increment
suffix:semicolon
id|bptr
op_assign
(paren
id|byte
op_star
)paren
id|ptr
op_plus
r_sizeof
(paren
r_struct
id|Pages
op_star
)paren
suffix:semicolon
id|i
op_assign
id|bp-&gt;bpps
suffix:semicolon
id|first
op_assign
(paren
r_struct
id|BufHeader
op_star
)paren
id|bptr
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
id|bh
op_assign
(paren
r_struct
id|BufHeader
op_star
)paren
id|bptr
suffix:semicolon
macro_line|#ifdef DEBUG_MAGIC
id|bh-&gt;magic
op_assign
l_int|020167
suffix:semicolon
macro_line|#endif
id|bh-&gt;next
op_assign
id|prev
suffix:semicolon
id|prev
op_assign
id|bh
suffix:semicolon
id|bh-&gt;bp
op_assign
id|bp
suffix:semicolon
id|bptr
op_add_assign
id|PART_SIZE
c_func
(paren
id|bp-&gt;pageorder
comma
id|bp-&gt;bpps
)paren
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|first-&gt;next
op_assign
id|bp-&gt;freelist
suffix:semicolon
id|bp-&gt;freelist
op_assign
id|bh
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|BufPoolFree
id|BufPoolFree
c_func
(paren
r_struct
id|BufPool
op_star
id|bp
)paren
(brace
r_struct
id|Pages
op_star
id|p
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolFree bp %x&bslash;n&quot;
comma
id|bp
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|bp-&gt;pagescount
op_decrement
)paren
(brace
id|p
op_assign
id|bp-&gt;pageslist-&gt;next
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|bp-&gt;pageslist
comma
id|bp-&gt;pageorder
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Free pages %x order %d&bslash;n&quot;
comma
id|bp-&gt;pageslist
comma
id|bp-&gt;pageorder
)paren
suffix:semicolon
macro_line|#endif
id|bp-&gt;pageslist
op_assign
id|p
suffix:semicolon
)brace
)brace
r_int
DECL|function|BufPoolGet
id|BufPoolGet
c_func
(paren
r_struct
id|BufHeader
op_star
op_star
id|bh
comma
r_struct
id|BufPool
op_star
id|bp
comma
r_int
id|priority
comma
r_void
op_star
id|heldby
comma
r_int
id|where
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
macro_line|#ifdef DEBUG_MAGIC
r_if
c_cond
(paren
id|bp-&gt;magic
op_ne
l_int|010167
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolGet: not a BufHeader&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|bp-&gt;freelist
)paren
(brace
op_star
id|bh
op_assign
id|bp-&gt;freelist
suffix:semicolon
id|bp-&gt;freelist
op_assign
id|bp-&gt;freelist-&gt;next
suffix:semicolon
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|heldby
op_assign
id|heldby
suffix:semicolon
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|where
op_assign
id|where
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|0
)paren
op_logical_and
(paren
id|bp-&gt;pagescount
OL
id|bp-&gt;maxpages
)paren
)paren
(brace
r_if
c_cond
(paren
id|BufPoolAdd
c_func
(paren
id|bp
comma
id|priority
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_else
(brace
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|BufPoolRelease
id|BufPoolRelease
c_func
(paren
r_struct
id|BufHeader
op_star
id|bh
)paren
(brace
r_struct
id|BufPool
op_star
id|bp
suffix:semicolon
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_MAGIC
r_if
c_cond
(paren
id|bh-&gt;magic
op_ne
l_int|020167
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolRelease: not a BufHeader&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;called from %x&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|bp
op_assign
id|bh-&gt;bp
suffix:semicolon
macro_line|#ifdef DEBUG_MAGIC
r_if
c_cond
(paren
id|bp-&gt;magic
op_ne
l_int|010167
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;BufPoolRelease: not a BufPool&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|bh-&gt;next
op_assign
id|bp-&gt;freelist
suffix:semicolon
id|bp-&gt;freelist
op_assign
id|bh
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|BufQueueLink
id|BufQueueLink
c_func
(paren
r_struct
id|BufQueue
op_star
id|bq
comma
r_struct
id|BufHeader
op_star
id|bh
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bq-&gt;head
)paren
id|bq-&gt;head
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|bq-&gt;tail
)paren
id|bq-&gt;tail-&gt;next
op_assign
id|bh
suffix:semicolon
id|bq-&gt;tail
op_assign
id|bh
suffix:semicolon
id|bh-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|BufQueueLinkFront
id|BufQueueLinkFront
c_func
(paren
r_struct
id|BufQueue
op_star
id|bq
comma
r_struct
id|BufHeader
op_star
id|bh
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|bh-&gt;next
op_assign
id|bq-&gt;head
suffix:semicolon
id|bq-&gt;head
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bq-&gt;tail
)paren
id|bq-&gt;tail
op_assign
id|bh
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|BufQueueUnlink
id|BufQueueUnlink
c_func
(paren
r_struct
id|BufHeader
op_star
op_star
id|bh
comma
r_struct
id|BufQueue
op_star
id|bq
)paren
(brace
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bq-&gt;head
)paren
(brace
r_if
c_cond
(paren
id|bq-&gt;tail
op_eq
id|bq-&gt;head
)paren
id|bq-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
op_star
id|bh
op_assign
id|bq-&gt;head
suffix:semicolon
id|bq-&gt;head
op_assign
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|BufQueueInit
id|BufQueueInit
c_func
(paren
r_struct
id|BufQueue
op_star
id|bq
)paren
(brace
macro_line|#ifdef DEBUG_MAGIC
id|bq-&gt;magic
op_assign
l_int|030167
suffix:semicolon
macro_line|#endif
id|bq-&gt;head
op_assign
l_int|NULL
suffix:semicolon
id|bq-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|BufQueueRelease
id|BufQueueRelease
c_func
(paren
r_struct
id|BufQueue
op_star
id|bq
)paren
(brace
r_struct
id|BufHeader
op_star
id|bh
suffix:semicolon
r_while
c_loop
(paren
id|bq-&gt;head
)paren
(brace
id|BufQueueUnlink
c_func
(paren
op_amp
id|bh
comma
id|bq
)paren
suffix:semicolon
id|BufPoolRelease
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|BufQueueLength
id|BufQueueLength
c_func
(paren
r_struct
id|BufQueue
op_star
id|bq
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|BufHeader
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|bq-&gt;head
suffix:semicolon
r_while
c_loop
(paren
id|bh
)paren
(brace
id|i
op_increment
suffix:semicolon
id|bh
op_assign
id|bh-&gt;next
suffix:semicolon
)brace
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
r_void
DECL|function|BufQueueDiscard
id|BufQueueDiscard
c_func
(paren
r_struct
id|BufQueue
op_star
id|q
comma
r_int
id|pr
comma
r_void
op_star
id|heldby
comma
r_int
id|releasetoo
)paren
(brace
r_int
id|flags
suffix:semicolon
r_struct
id|BufHeader
op_star
id|sp
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
l_int|0
)paren
(brace
id|sp
op_assign
id|q-&gt;head
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sp
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sp-&gt;primitive
op_eq
id|pr
)paren
op_logical_and
(paren
id|sp-&gt;heldby
op_eq
id|heldby
)paren
)paren
(brace
id|q-&gt;head
op_assign
id|sp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|q-&gt;tail
op_eq
id|sp
)paren
id|q-&gt;tail
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|releasetoo
)paren
id|BufPoolRelease
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|sp
op_assign
id|q-&gt;head
suffix:semicolon
r_if
c_cond
(paren
id|sp
)paren
r_while
c_loop
(paren
id|sp-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
id|sp-&gt;next-&gt;primitive
op_eq
id|pr
)paren
op_logical_and
(paren
id|sp-&gt;next-&gt;heldby
op_eq
id|heldby
)paren
)paren
(brace
r_if
c_cond
(paren
id|q-&gt;tail
op_eq
id|sp-&gt;next
)paren
id|q-&gt;tail
op_assign
id|sp
suffix:semicolon
r_if
c_cond
(paren
id|releasetoo
)paren
id|BufPoolRelease
c_func
(paren
id|sp-&gt;next
)paren
suffix:semicolon
id|sp-&gt;next
op_assign
id|sp-&gt;next-&gt;next
suffix:semicolon
)brace
r_else
id|sp
op_assign
id|sp-&gt;next
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|Sfree
id|Sfree
c_func
(paren
id|byte
op_star
id|ptr
)paren
(brace
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Sfree %x&bslash;n&quot;
comma
id|ptr
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
id|byte
op_star
DECL|function|Smalloc
id|Smalloc
c_func
(paren
r_int
id|size
comma
r_int
id|pr
comma
r_char
op_star
id|why
)paren
(brace
id|byte
op_star
id|p
suffix:semicolon
id|p
op_assign
(paren
id|byte
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|pr
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Smalloc %s size %d res %x&bslash;n&quot;
comma
id|why
comma
id|size
comma
id|p
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|p
)paren
suffix:semicolon
)brace
eof