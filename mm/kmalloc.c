multiline_comment|/*&n; *  linux/mm/kmalloc.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds &amp; Roger Wolff.&n; *&n; *  Written by R.E. Wolff Sept/Oct &squot;93.&n; *&n; */
multiline_comment|/*&n; * Modified by Alex Bligh (alex@cconcepts.co.uk) 4 Apr 1994 to use multiple&n; * pages. So for &squot;page&squot; throughout, read &squot;area&squot;.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
multiline_comment|/* I want this low enough for a while to catch errors.&n;   I want this number to be increased in the near future:&n;        loadable device drivers should use this function to get memory */
DECL|macro|MAX_KMALLOC_K
mdefine_line|#define MAX_KMALLOC_K ((PAGE_SIZE&lt;&lt;(NUM_AREA_ORDERS-1))&gt;&gt;10)
multiline_comment|/* This defines how many times we should try to allocate a free page before&n;   giving up. Normally this shouldn&squot;t happen at all. */
DECL|macro|MAX_GET_FREE_PAGE_TRIES
mdefine_line|#define MAX_GET_FREE_PAGE_TRIES 4
multiline_comment|/* Private flags. */
DECL|macro|MF_USED
mdefine_line|#define MF_USED 0xffaa0055
DECL|macro|MF_DMA
mdefine_line|#define MF_DMA  0xff00aa55
DECL|macro|MF_FREE
mdefine_line|#define MF_FREE 0x0055ffaa
multiline_comment|/*&n; * Much care has gone into making these routines in this file reentrant.&n; *&n; * The fancy bookkeeping of nbytesmalloced and the like are only used to&n; * report them to the user (oooohhhhh, aaaaahhhhh....) are not&n; * protected by cli(). (If that goes wrong. So what?)&n; *&n; * These routines restore the interrupt status to allow calling with ints&n; * off.&n; */
multiline_comment|/*&n; * A block header. This is in front of every malloc-block, whether free or not.&n; */
DECL|struct|block_header
r_struct
id|block_header
(brace
DECL|member|bh_flags
r_int
r_int
id|bh_flags
suffix:semicolon
r_union
(brace
DECL|member|ubh_length
r_int
r_int
id|ubh_length
suffix:semicolon
DECL|member|fbh_next
r_struct
id|block_header
op_star
id|fbh_next
suffix:semicolon
DECL|member|vp
)brace
id|vp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bh_length
mdefine_line|#define bh_length vp.ubh_length
DECL|macro|bh_next
mdefine_line|#define bh_next   vp.fbh_next
DECL|macro|BH
mdefine_line|#define BH(p) ((struct block_header *)(p))
multiline_comment|/*&n; * The page descriptor is at the front of every page that malloc has in use.&n; */
DECL|struct|page_descriptor
r_struct
id|page_descriptor
(brace
DECL|member|next
r_struct
id|page_descriptor
op_star
id|next
suffix:semicolon
DECL|member|firstfree
r_struct
id|block_header
op_star
id|firstfree
suffix:semicolon
DECL|member|order
r_int
id|order
suffix:semicolon
DECL|member|nfree
r_int
id|nfree
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PAGE_DESC
mdefine_line|#define PAGE_DESC(p) ((struct page_descriptor *)(((unsigned long)(p)) &amp; PAGE_MASK))
multiline_comment|/*&n; * A size descriptor describes a specific class of malloc sizes.&n; * Each class of sizes has its own freelist.&n; */
DECL|struct|size_descriptor
r_struct
id|size_descriptor
(brace
DECL|member|firstfree
r_struct
id|page_descriptor
op_star
id|firstfree
suffix:semicolon
DECL|member|dmafree
r_struct
id|page_descriptor
op_star
id|dmafree
suffix:semicolon
multiline_comment|/* DMA-able memory */
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|nblocks
r_int
id|nblocks
suffix:semicolon
DECL|member|nmallocs
r_int
id|nmallocs
suffix:semicolon
DECL|member|nfrees
r_int
id|nfrees
suffix:semicolon
DECL|member|nbytesmalloced
r_int
id|nbytesmalloced
suffix:semicolon
DECL|member|npages
r_int
id|npages
suffix:semicolon
DECL|member|gfporder
r_int
r_int
id|gfporder
suffix:semicolon
multiline_comment|/* number of pages in the area required */
)brace
suffix:semicolon
multiline_comment|/*&n; * For now it is unsafe to allocate bucket sizes between n &amp; n=16 where n is&n; * 4096 * any power of two&n; */
macro_line|#if PAGE_SIZE == 4096
DECL|variable|sizes
r_struct
id|size_descriptor
id|sizes
(braket
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|32
comma
l_int|127
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|64
comma
l_int|63
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|128
comma
l_int|31
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|252
comma
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|508
comma
l_int|8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|1020
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|2040
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|4096
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|8192
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|16384
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|32768
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|65536
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|131072
op_minus
l_int|16
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|5
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#elif PAGE_SIZE == 8192
DECL|variable|sizes
r_struct
id|size_descriptor
id|sizes
(braket
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|64
comma
l_int|127
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|128
comma
l_int|63
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|248
comma
l_int|31
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|504
comma
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|1016
comma
l_int|8
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|2040
comma
l_int|4
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|4080
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|8192
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|16384
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|32768
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|65536
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|131072
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|262144
op_minus
l_int|32
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|5
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
macro_line|#else
macro_line|#error you need to make a version for your pagesize
macro_line|#endif
DECL|macro|NBLOCKS
mdefine_line|#define NBLOCKS(order)          (sizes[order].nblocks)
DECL|macro|BLOCKSIZE
mdefine_line|#define BLOCKSIZE(order)        (sizes[order].size)
DECL|macro|AREASIZE
mdefine_line|#define AREASIZE(order)&t;&t;(PAGE_SIZE&lt;&lt;(sizes[order].gfporder))
DECL|function|kmalloc_init
r_int
id|kmalloc_init
c_func
(paren
r_int
id|start_mem
comma
r_int
id|end_mem
)paren
(brace
r_int
id|order
suffix:semicolon
multiline_comment|/*&n; * Check the static info array. Things will blow up terribly if it&squot;s&n; * incorrect. This is a late &quot;compile time&quot; check.....&n; */
r_for
c_loop
(paren
id|order
op_assign
l_int|0
suffix:semicolon
id|BLOCKSIZE
c_func
(paren
id|order
)paren
suffix:semicolon
id|order
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|NBLOCKS
c_func
(paren
id|order
)paren
op_star
id|BLOCKSIZE
c_func
(paren
id|order
)paren
op_plus
r_sizeof
(paren
r_struct
id|page_descriptor
)paren
)paren
OG
id|AREASIZE
c_func
(paren
id|order
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Cannot use %d bytes out of %d in order = %d block mallocs&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
id|NBLOCKS
c_func
(paren
id|order
)paren
op_star
id|BLOCKSIZE
c_func
(paren
id|order
)paren
op_plus
r_sizeof
(paren
r_struct
id|page_descriptor
)paren
)paren
comma
(paren
r_int
)paren
id|AREASIZE
c_func
(paren
id|order
)paren
comma
id|BLOCKSIZE
c_func
(paren
id|order
)paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;This only happens if someone messes with kmalloc&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|start_mem
suffix:semicolon
)brace
DECL|function|get_order
r_int
id|get_order
c_func
(paren
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
multiline_comment|/* Add the size of the header */
id|size
op_add_assign
r_sizeof
(paren
r_struct
id|block_header
)paren
suffix:semicolon
r_for
c_loop
(paren
id|order
op_assign
l_int|0
suffix:semicolon
id|BLOCKSIZE
c_func
(paren
id|order
)paren
suffix:semicolon
id|order
op_increment
)paren
r_if
c_cond
(paren
id|size
op_le
id|BLOCKSIZE
c_func
(paren
id|order
)paren
)paren
r_return
id|order
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|kmalloc
r_void
op_star
id|kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|priority
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|max_addr
comma
id|type
suffix:semicolon
r_int
id|order
comma
id|i
comma
id|sz
suffix:semicolon
r_struct
id|block_header
op_star
id|p
suffix:semicolon
r_struct
id|page_descriptor
op_star
id|page
comma
op_star
op_star
id|pg
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|order
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc of too large a block (%d bytes).&bslash;n&quot;
comma
(paren
r_int
)paren
id|size
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|max_addr
op_assign
op_complement
l_int|0UL
suffix:semicolon
id|type
op_assign
id|MF_USED
suffix:semicolon
id|pg
op_assign
op_amp
id|sizes
(braket
id|order
)braket
dot
id|firstfree
suffix:semicolon
r_if
c_cond
(paren
id|priority
op_amp
id|GFP_DMA
)paren
(brace
id|max_addr
op_assign
id|MAX_DMA_ADDRESS
suffix:semicolon
id|type
op_assign
id|MF_DMA
suffix:semicolon
id|pg
op_assign
op_amp
id|sizes
(braket
id|order
)braket
dot
id|dmafree
suffix:semicolon
)brace
id|priority
op_and_assign
id|GFP_LEVEL_MASK
suffix:semicolon
multiline_comment|/* Sanity check... */
r_if
c_cond
(paren
id|intr_count
op_logical_and
id|priority
op_ne
id|GFP_ATOMIC
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kmalloc called nonatomically from interrupt %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|priority
op_assign
id|GFP_ATOMIC
suffix:semicolon
)brace
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
id|page
op_assign
op_star
id|pg
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|p
op_assign
id|page-&gt;firstfree
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bh_flags
op_ne
id|MF_FREE
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Problem: block on freelist at %08lx isn&squot;t free.&bslash;n&quot;
comma
(paren
r_int
)paren
id|p
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_goto
id|found_it
suffix:semicolon
)brace
multiline_comment|/* We need to get a new free page..... */
multiline_comment|/* sz is the size of the blocks we&squot;re dealing with */
id|sz
op_assign
id|BLOCKSIZE
c_func
(paren
id|order
)paren
suffix:semicolon
multiline_comment|/* This can be done with ints on: This is private to this invocation */
id|page
op_assign
(paren
r_struct
id|page_descriptor
op_star
)paren
id|__get_free_pages
c_func
(paren
id|priority
op_amp
id|GFP_LEVEL_MASK
comma
id|sizes
(braket
id|order
)braket
dot
id|gfporder
comma
id|max_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
r_static
r_int
r_int
id|last
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|last
op_plus
l_int|10
op_star
id|HZ
OL
id|jiffies
)paren
(brace
id|last
op_assign
id|jiffies
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t get a free page.....&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|sizes
(braket
id|order
)braket
dot
id|npages
op_increment
suffix:semicolon
multiline_comment|/* Loop for all but last block: */
r_for
c_loop
(paren
id|i
op_assign
id|NBLOCKS
c_func
(paren
id|order
)paren
comma
id|p
op_assign
id|BH
c_func
(paren
id|page
op_plus
l_int|1
)paren
suffix:semicolon
id|i
OG
l_int|1
suffix:semicolon
id|i
op_decrement
comma
id|p
op_assign
id|p-&gt;bh_next
)paren
(brace
id|p-&gt;bh_flags
op_assign
id|MF_FREE
suffix:semicolon
id|p-&gt;bh_next
op_assign
id|BH
c_func
(paren
(paren
(paren
r_int
)paren
id|p
)paren
op_plus
id|sz
)paren
suffix:semicolon
)brace
multiline_comment|/* Last block: */
id|p-&gt;bh_flags
op_assign
id|MF_FREE
suffix:semicolon
id|p-&gt;bh_next
op_assign
l_int|NULL
suffix:semicolon
id|page-&gt;order
op_assign
id|order
suffix:semicolon
id|page-&gt;nfree
op_assign
id|NBLOCKS
c_func
(paren
id|order
)paren
suffix:semicolon
id|p
op_assign
id|BH
c_func
(paren
id|page
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now we&squot;re going to muck with the &quot;global&quot; freelist&n;&t; * for this size: this should be uninterruptible&n;&t; */
id|cli
c_func
(paren
)paren
suffix:semicolon
id|page-&gt;next
op_assign
op_star
id|pg
suffix:semicolon
op_star
id|pg
op_assign
id|page
suffix:semicolon
id|found_it
suffix:colon
id|page-&gt;firstfree
op_assign
id|p-&gt;bh_next
suffix:semicolon
id|page-&gt;nfree
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page-&gt;nfree
)paren
op_star
id|pg
op_assign
id|page-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sizes
(braket
id|order
)braket
dot
id|nmallocs
op_increment
suffix:semicolon
id|sizes
(braket
id|order
)braket
dot
id|nbytesmalloced
op_add_assign
id|size
suffix:semicolon
id|p-&gt;bh_flags
op_assign
id|type
suffix:semicolon
multiline_comment|/* As of now this block is officially in use */
id|p-&gt;bh_length
op_assign
id|size
suffix:semicolon
r_return
id|p
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Pointer arithmetic: increments past header */
)brace
DECL|function|kfree
r_void
id|kfree
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_int
id|size
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|order
suffix:semicolon
r_register
r_struct
id|block_header
op_star
id|p
suffix:semicolon
r_struct
id|page_descriptor
op_star
id|page
comma
op_star
op_star
id|pg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr
)paren
r_return
suffix:semicolon
id|p
op_assign
(paren
(paren
r_struct
id|block_header
op_star
)paren
id|ptr
)paren
op_minus
l_int|1
suffix:semicolon
id|page
op_assign
id|PAGE_DESC
c_func
(paren
id|p
)paren
suffix:semicolon
id|order
op_assign
id|page-&gt;order
suffix:semicolon
id|pg
op_assign
op_amp
id|sizes
(braket
id|order
)braket
dot
id|firstfree
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;bh_flags
op_eq
id|MF_DMA
)paren
(brace
id|p-&gt;bh_flags
op_assign
id|MF_USED
suffix:semicolon
id|pg
op_assign
op_amp
id|sizes
(braket
id|order
)braket
dot
id|dmafree
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|order
OL
l_int|0
)paren
op_logical_or
(paren
id|order
OG
r_sizeof
(paren
id|sizes
)paren
op_div
r_sizeof
(paren
id|sizes
(braket
l_int|0
)braket
)paren
)paren
op_logical_or
(paren
(paren
(paren
r_int
)paren
(paren
id|page-&gt;next
)paren
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_logical_or
(paren
id|p-&gt;bh_flags
op_ne
id|MF_USED
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kfree of non-kmalloced memory: %p, next= %p, order=%d&bslash;n&quot;
comma
id|p
comma
id|page-&gt;next
comma
id|page-&gt;order
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|size
op_assign
id|p-&gt;bh_length
suffix:semicolon
id|p-&gt;bh_flags
op_assign
id|MF_FREE
suffix:semicolon
multiline_comment|/* As of now this block is officially free */
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
id|p-&gt;bh_next
op_assign
id|page-&gt;firstfree
suffix:semicolon
id|page-&gt;firstfree
op_assign
id|p
suffix:semicolon
id|page-&gt;nfree
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|page-&gt;nfree
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Page went from full to one free block: put it on the freelist. */
id|page-&gt;next
op_assign
op_star
id|pg
suffix:semicolon
op_star
id|pg
op_assign
id|page
suffix:semicolon
)brace
multiline_comment|/* If page is completely free, free it */
r_if
c_cond
(paren
id|page-&gt;nfree
op_eq
id|NBLOCKS
c_func
(paren
id|order
)paren
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|page_descriptor
op_star
id|tmp
op_assign
op_star
id|pg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ooops. page %p doesn&squot;t show on freelist.&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmp
op_eq
id|page
)paren
(brace
op_star
id|pg
op_assign
id|page-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pg
op_assign
op_amp
id|tmp-&gt;next
suffix:semicolon
)brace
id|sizes
(braket
id|order
)braket
dot
id|npages
op_decrement
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
)paren
id|page
comma
id|sizes
(braket
id|order
)braket
dot
id|gfporder
)paren
suffix:semicolon
)brace
id|sizes
(braket
id|order
)braket
dot
id|nfrees
op_increment
suffix:semicolon
id|sizes
(braket
id|order
)braket
dot
id|nbytesmalloced
op_sub_assign
id|size
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
