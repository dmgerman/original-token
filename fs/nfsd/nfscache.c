multiline_comment|/*&n; * linux/fs/nfsd/nfscache.c&n; *&n; * Request reply cache. This is currently a global cache, but this may&n; * change in the future and be a per-client cache.&n; *&n; * This code is heavily inspired by the 44BSD implementation, although&n; * it does things a bit differently.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
multiline_comment|/* Size of reply cache. Common values are:&n; * 4.3BSD:&t;128&n; * 4.4BSD:&t;256&n; * Solaris2:&t;1024&n; * DEC Unix:&t;512-4096&n; */
DECL|macro|CACHESIZE
mdefine_line|#define CACHESIZE&t;&t;1024
DECL|macro|HASHSIZE
mdefine_line|#define HASHSIZE&t;&t;64
DECL|macro|REQHASH
mdefine_line|#define REQHASH(xid)&t;&t;((((xid) &gt;&gt; 24) ^ (xid)) &amp; (HASHSIZE-1))
DECL|struct|nfscache_head
r_struct
id|nfscache_head
(brace
DECL|member|next
r_struct
id|svc_cacherep
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|svc_cacherep
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|hash_list
r_static
r_struct
id|nfscache_head
id|hash_list
(braket
id|HASHSIZE
)braket
suffix:semicolon
DECL|variable|lru_head
r_static
r_struct
id|svc_cacherep
op_star
id|lru_head
suffix:semicolon
DECL|variable|lru_tail
r_static
r_struct
id|svc_cacherep
op_star
id|lru_tail
suffix:semicolon
DECL|variable|nfscache
r_static
r_struct
id|svc_cacherep
id|nfscache
(braket
id|CACHESIZE
)braket
suffix:semicolon
DECL|variable|cache_initialized
r_static
r_int
id|cache_initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|cache_disabled
r_static
r_int
id|cache_disabled
op_assign
l_int|1
suffix:semicolon
r_static
r_int
id|nfsd_cache_append
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_buf
op_star
id|data
)paren
suffix:semicolon
r_void
DECL|function|nfsd_cache_init
id|nfsd_cache_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|rp
suffix:semicolon
r_struct
id|nfscache_head
op_star
id|rh
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cache_initialized
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|rh
op_assign
id|hash_list
suffix:semicolon
id|i
OL
id|HASHSIZE
suffix:semicolon
id|i
op_increment
comma
id|rh
op_increment
)paren
id|rh-&gt;next
op_assign
id|rh-&gt;prev
op_assign
(paren
r_struct
id|svc_cacherep
op_star
)paren
id|rh
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|rp
op_assign
id|nfscache
suffix:semicolon
id|i
OL
id|CACHESIZE
suffix:semicolon
id|i
op_increment
comma
id|rp
op_increment
)paren
(brace
id|rp-&gt;c_state
op_assign
id|RC_UNUSED
suffix:semicolon
id|rp-&gt;c_type
op_assign
id|RC_NOCACHE
suffix:semicolon
id|rp-&gt;c_hash_next
op_assign
id|rp-&gt;c_hash_prev
op_assign
id|rp
suffix:semicolon
id|rp-&gt;c_lru_next
op_assign
id|rp
op_plus
l_int|1
suffix:semicolon
id|rp-&gt;c_lru_prev
op_assign
id|rp
op_minus
l_int|1
suffix:semicolon
)brace
id|lru_head
op_assign
id|nfscache
suffix:semicolon
id|lru_tail
op_assign
id|nfscache
op_plus
id|CACHESIZE
op_minus
l_int|1
suffix:semicolon
id|lru_head-&gt;c_lru_prev
op_assign
l_int|NULL
suffix:semicolon
id|lru_tail-&gt;c_lru_next
op_assign
l_int|NULL
suffix:semicolon
id|cache_initialized
op_assign
l_int|1
suffix:semicolon
id|cache_disabled
op_assign
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|nfsd_cache_shutdown
id|nfsd_cache_shutdown
c_func
(paren
r_void
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|rp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cache_initialized
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|rp
op_assign
id|lru_head
suffix:semicolon
id|rp
suffix:semicolon
id|rp
op_assign
id|rp-&gt;c_lru_next
)paren
(brace
r_if
c_cond
(paren
id|rp-&gt;c_state
op_eq
id|RC_DONE
op_logical_and
id|rp-&gt;c_type
op_eq
id|RC_REPLBUFF
)paren
id|kfree
c_func
(paren
id|rp-&gt;c_replbuf.buf
)paren
suffix:semicolon
)brace
id|cache_initialized
op_assign
l_int|0
suffix:semicolon
id|cache_disabled
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Move cache entry to front of LRU list&n; */
r_static
r_void
DECL|function|lru_put_front
id|lru_put_front
c_func
(paren
r_struct
id|svc_cacherep
op_star
id|rp
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|prev
op_assign
id|rp-&gt;c_lru_prev
comma
op_star
id|next
op_assign
id|rp-&gt;c_lru_next
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;c_lru_next
op_assign
id|next
suffix:semicolon
r_else
id|lru_head
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
id|next-&gt;c_lru_prev
op_assign
id|prev
suffix:semicolon
r_else
id|lru_tail
op_assign
id|prev
suffix:semicolon
id|rp-&gt;c_lru_next
op_assign
id|lru_head
suffix:semicolon
id|rp-&gt;c_lru_prev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|lru_head
)paren
id|lru_head-&gt;c_lru_prev
op_assign
id|rp
suffix:semicolon
id|lru_head
op_assign
id|rp
suffix:semicolon
)brace
multiline_comment|/*&n; * Move a cache entry from one hash list to another&n; */
r_static
r_void
DECL|function|hash_refile
id|hash_refile
c_func
(paren
r_struct
id|svc_cacherep
op_star
id|rp
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|prev
op_assign
id|rp-&gt;c_hash_prev
comma
op_star
id|next
op_assign
id|rp-&gt;c_hash_next
suffix:semicolon
r_struct
id|nfscache_head
op_star
id|head
op_assign
id|hash_list
op_plus
id|REQHASH
c_func
(paren
id|rp-&gt;c_xid
)paren
suffix:semicolon
id|prev-&gt;c_hash_next
op_assign
id|next
suffix:semicolon
id|next-&gt;c_hash_prev
op_assign
id|prev
suffix:semicolon
id|rp-&gt;c_hash_next
op_assign
id|head-&gt;next
suffix:semicolon
id|rp-&gt;c_hash_prev
op_assign
(paren
r_struct
id|svc_cacherep
op_star
)paren
id|head
suffix:semicolon
id|head-&gt;next-&gt;c_hash_prev
op_assign
id|rp
suffix:semicolon
id|head-&gt;next
op_assign
id|rp
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to find an entry matching the current call in the cache. When none&n; * is found, we grab the oldest unlocked entry off the LRU list.&n; * Note that no operation within the loop may sleep.&n; */
r_int
DECL|function|nfsd_cache_lookup
id|nfsd_cache_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_int
id|type
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|rh
comma
op_star
id|rp
suffix:semicolon
r_struct
id|svc_client
op_star
id|clp
op_assign
id|rqstp-&gt;rq_client
suffix:semicolon
id|u32
id|xid
op_assign
id|rqstp-&gt;rq_xid
comma
id|proc
op_assign
id|rqstp-&gt;rq_proc
suffix:semicolon
r_int
r_int
id|age
suffix:semicolon
id|rqstp-&gt;rq_cacherep
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|cache_disabled
op_logical_or
id|type
op_eq
id|RC_NOCACHE
)paren
(brace
id|nfsdstats.rcnocache
op_increment
suffix:semicolon
r_return
id|RC_DOIT
suffix:semicolon
)brace
id|rp
op_assign
id|rh
op_assign
(paren
r_struct
id|svc_cacherep
op_star
)paren
op_amp
id|hash_list
(braket
id|REQHASH
c_func
(paren
id|xid
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|rp
op_assign
id|rp-&gt;c_hash_next
)paren
op_ne
id|rh
)paren
(brace
r_if
c_cond
(paren
id|rp-&gt;c_state
op_ne
id|RC_UNUSED
op_logical_and
id|xid
op_eq
id|rp-&gt;c_xid
op_logical_and
id|proc
op_eq
id|rp-&gt;c_proc
op_logical_and
id|exp_checkaddr
c_func
(paren
id|clp
comma
id|rp-&gt;c_client
)paren
)paren
(brace
id|nfsdstats.rchits
op_increment
suffix:semicolon
r_goto
id|found_entry
suffix:semicolon
)brace
)brace
id|nfsdstats.rcmisses
op_increment
suffix:semicolon
multiline_comment|/* This loop shouldn&squot;t take more than a few iterations normally */
(brace
r_int
id|safe
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|rp
op_assign
id|lru_tail
suffix:semicolon
id|rp
suffix:semicolon
id|rp
op_assign
id|rp-&gt;c_lru_prev
)paren
(brace
r_if
c_cond
(paren
id|rp-&gt;c_state
op_ne
id|RC_INPROG
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|safe
op_increment
OG
id|CACHESIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfsd: loop in repcache LRU list&bslash;n&quot;
)paren
suffix:semicolon
id|cache_disabled
op_assign
l_int|1
suffix:semicolon
r_return
id|RC_DOIT
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This should not happen */
r_if
c_cond
(paren
id|rp
op_eq
l_int|NULL
)paren
(brace
r_static
r_int
id|complaints
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: all repcache entries locked!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|complaints
OG
l_int|5
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: disabling repcache.&bslash;n&quot;
)paren
suffix:semicolon
id|cache_disabled
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|RC_DOIT
suffix:semicolon
)brace
id|rqstp-&gt;rq_cacherep
op_assign
id|rp
suffix:semicolon
id|rp-&gt;c_state
op_assign
id|RC_INPROG
suffix:semicolon
id|rp-&gt;c_xid
op_assign
id|xid
suffix:semicolon
id|rp-&gt;c_proc
op_assign
id|proc
suffix:semicolon
id|rp-&gt;c_client
op_assign
id|rqstp-&gt;rq_addr.sin_addr
suffix:semicolon
id|hash_refile
c_func
(paren
id|rp
)paren
suffix:semicolon
multiline_comment|/* release any buffer */
r_if
c_cond
(paren
id|rp-&gt;c_type
op_eq
id|RC_REPLBUFF
)paren
(brace
id|kfree
c_func
(paren
id|rp-&gt;c_replbuf.buf
)paren
suffix:semicolon
id|rp-&gt;c_replbuf.buf
op_assign
l_int|NULL
suffix:semicolon
)brace
id|rp-&gt;c_type
op_assign
id|RC_NOCACHE
suffix:semicolon
r_return
id|RC_DOIT
suffix:semicolon
id|found_entry
suffix:colon
multiline_comment|/* We found a matching entry which is either in progress or done. */
id|age
op_assign
id|jiffies
op_minus
id|rp-&gt;c_timestamp
suffix:semicolon
id|rp-&gt;c_timestamp
op_assign
id|jiffies
suffix:semicolon
id|lru_put_front
c_func
(paren
id|rp
)paren
suffix:semicolon
multiline_comment|/* Request being processed or excessive rexmits */
r_if
c_cond
(paren
id|rp-&gt;c_state
op_eq
id|RC_INPROG
op_logical_or
id|age
OL
id|RC_DELAY
)paren
r_return
id|RC_DROPIT
suffix:semicolon
multiline_comment|/* From the hall of fame of impractical attacks:&n;&t; * Is this a user who tries to snoop on the cache? */
r_if
c_cond
(paren
op_logical_neg
id|rqstp-&gt;rq_secure
op_logical_and
id|rp-&gt;c_secure
)paren
r_return
id|RC_DOIT
suffix:semicolon
multiline_comment|/* Compose RPC reply header */
r_switch
c_cond
(paren
id|rp-&gt;c_type
)paren
(brace
r_case
id|RC_NOCACHE
suffix:colon
r_return
id|RC_DOIT
suffix:semicolon
r_case
id|RC_REPLSTAT
suffix:colon
id|svc_putlong
c_func
(paren
op_amp
id|rqstp-&gt;rq_resbuf
comma
id|rp-&gt;c_replstat
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RC_REPLBUFF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|nfsd_cache_append
c_func
(paren
id|rqstp
comma
op_amp
id|rp-&gt;c_replbuf
)paren
)paren
r_return
id|RC_DOIT
suffix:semicolon
multiline_comment|/* should not happen */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: bad repcache type %d&bslash;n&quot;
comma
id|rp-&gt;c_type
)paren
suffix:semicolon
id|rp-&gt;c_state
op_assign
id|RC_UNUSED
suffix:semicolon
r_return
id|RC_DOIT
suffix:semicolon
)brace
r_return
id|RC_REPLY
suffix:semicolon
)brace
multiline_comment|/*&n; * Update a cache entry. This is called from nfsd_dispatch when&n; * the procedure has been executed and the complete reply is in&n; * rqstp-&gt;rq_res.&n; *&n; * We&squot;re copying around data here rather than swapping buffers because&n; * the toplevel loop requires max-sized buffers, which would be a waste&n; * of memory for a cache with a max reply size of 100 bytes (diropokres).&n; *&n; * If we should start to use different types of cache entries tailored&n; * specifically for attrstat and fh&squot;s, we may save even more space.&n; *&n; * Also note that a cachetype of RC_NOCACHE can legally be passed when&n; * nfsd failed to encode a reply that otherwise would have been cached.&n; * In this case, nfsd_cache_update is called with statp == NULL.&n; */
r_void
DECL|function|nfsd_cache_update
id|nfsd_cache_update
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_int
id|cachetype
comma
id|u32
op_star
id|statp
)paren
(brace
r_struct
id|svc_cacherep
op_star
id|rp
suffix:semicolon
r_struct
id|svc_buf
op_star
id|resp
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
comma
op_star
id|cachp
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rp
op_assign
id|rqstp-&gt;rq_cacherep
)paren
op_logical_or
id|cache_disabled
)paren
r_return
suffix:semicolon
multiline_comment|/* Don&squot;t cache excessive amounts of data and XDR failures */
r_if
c_cond
(paren
op_logical_neg
id|statp
op_logical_or
(paren
id|len
op_assign
id|resp-&gt;buf
op_minus
id|statp
)paren
OG
(paren
l_int|256
op_rshift
l_int|2
)paren
)paren
(brace
id|rp-&gt;c_state
op_assign
id|RC_UNUSED
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cachetype
)paren
(brace
r_case
id|RC_REPLSTAT
suffix:colon
r_if
c_cond
(paren
id|len
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;nfsd: RC_REPLSTAT/reply len %d!&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
id|rp-&gt;c_replstat
op_assign
op_star
id|statp
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RC_REPLBUFF
suffix:colon
id|cachp
op_assign
op_amp
id|rp-&gt;c_replbuf
suffix:semicolon
id|cachp-&gt;buf
op_assign
(paren
id|u32
op_star
)paren
id|kmalloc
c_func
(paren
id|len
op_lshift
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cachp-&gt;buf
)paren
(brace
id|rp-&gt;c_state
op_assign
id|RC_UNUSED
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cachp-&gt;len
op_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|cachp-&gt;buf
comma
id|statp
comma
id|len
op_lshift
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|lru_put_front
c_func
(paren
id|rp
)paren
suffix:semicolon
id|rp-&gt;c_secure
op_assign
id|rqstp-&gt;rq_secure
suffix:semicolon
id|rp-&gt;c_type
op_assign
id|cachetype
suffix:semicolon
id|rp-&gt;c_state
op_assign
id|RC_DONE
suffix:semicolon
id|rp-&gt;c_timestamp
op_assign
id|jiffies
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy cached reply to current reply buffer. Should always fit.&n; */
r_static
r_int
DECL|function|nfsd_cache_append
id|nfsd_cache_append
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_buf
op_star
id|data
)paren
(brace
r_struct
id|svc_buf
op_star
id|resp
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;len
op_plus
id|data-&gt;len
OG
id|resp-&gt;buflen
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: cached reply too large (%d).&bslash;n&quot;
comma
id|data-&gt;len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|resp-&gt;buf
comma
id|data-&gt;buf
comma
id|data-&gt;len
)paren
suffix:semicolon
id|resp-&gt;buf
op_add_assign
(paren
(paren
id|data-&gt;len
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|resp-&gt;len
op_add_assign
id|data-&gt;len
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof