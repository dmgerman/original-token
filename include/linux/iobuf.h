multiline_comment|/*&n; * iobuf.h&n; *&n; * Defines the structures used to track abstract kernel-space io buffers.&n; *&n; */
macro_line|#ifndef __LINUX_IOBUF_H
DECL|macro|__LINUX_IOBUF_H
mdefine_line|#define __LINUX_IOBUF_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * The kiobuf structure describes a physical set of pages reserved&n; * locked for IO.  The reference counts on each page will have been&n; * incremented, and the flags field will indicate whether or not we have&n; * pre-locked all of the pages for IO.&n; *&n; * kiobufs may be passed in arrays to form a kiovec, but we must&n; * preserve the property that no page is present more than once over the&n; * entire iovec.&n; */
DECL|macro|KIO_MAX_ATOMIC_IO
mdefine_line|#define KIO_MAX_ATOMIC_IO&t;64 /* in kb */
DECL|macro|KIO_MAX_ATOMIC_BYTES
mdefine_line|#define KIO_MAX_ATOMIC_BYTES&t;(64 * 1024)
DECL|macro|KIO_STATIC_PAGES
mdefine_line|#define KIO_STATIC_PAGES&t;(KIO_MAX_ATOMIC_IO / (PAGE_SIZE &gt;&gt; 10) + 1)
DECL|macro|KIO_MAX_SECTORS
mdefine_line|#define KIO_MAX_SECTORS&t;&t;(KIO_MAX_ATOMIC_IO * 2)
multiline_comment|/* The main kiobuf struct used for all our IO! */
DECL|struct|kiobuf
r_struct
id|kiobuf
(brace
DECL|member|nr_pages
r_int
id|nr_pages
suffix:semicolon
multiline_comment|/* Pages actually referenced */
DECL|member|array_len
r_int
id|array_len
suffix:semicolon
multiline_comment|/* Space in the allocated lists */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* Offset to start of valid data */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Number of valid bytes of data */
multiline_comment|/* Keep separate track of the physical addresses and page&n;&t; * structs involved.  If we do IO to a memory-mapped device&n;&t; * region, there won&squot;t necessarily be page structs defined for&n;&t; * every address. */
DECL|member|maplist
r_struct
id|page
op_star
op_star
id|maplist
suffix:semicolon
DECL|member|locked
r_int
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* If set, pages has been locked */
multiline_comment|/* Always embed enough struct pages for 64k of IO */
DECL|member|map_array
r_struct
id|page
op_star
id|map_array
(braket
id|KIO_STATIC_PAGES
)braket
suffix:semicolon
multiline_comment|/* Dynamic state for IO completion: */
DECL|member|io_count
id|atomic_t
id|io_count
suffix:semicolon
multiline_comment|/* IOs still in progress */
DECL|member|errno
r_int
id|errno
suffix:semicolon
multiline_comment|/* Status of completed IO */
DECL|member|end_io
r_void
(paren
op_star
id|end_io
)paren
(paren
r_struct
id|kiobuf
op_star
)paren
suffix:semicolon
multiline_comment|/* Completion callback */
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* mm/memory.c */
r_int
id|map_user_kiobuf
c_func
(paren
r_int
id|rw
comma
r_struct
id|kiobuf
op_star
comma
r_int
r_int
id|va
comma
r_int
id|len
)paren
suffix:semicolon
r_void
id|unmap_kiobuf
c_func
(paren
r_struct
id|kiobuf
op_star
id|iobuf
)paren
suffix:semicolon
r_int
id|lock_kiovec
c_func
(paren
r_int
id|nr
comma
r_struct
id|kiobuf
op_star
id|iovec
(braket
)braket
comma
r_int
id|wait
)paren
suffix:semicolon
r_int
id|unlock_kiovec
c_func
(paren
r_int
id|nr
comma
r_struct
id|kiobuf
op_star
id|iovec
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/* fs/iobuf.c */
r_void
id|__init
id|kiobuf_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|kiobuf_init
c_func
(paren
r_struct
id|kiobuf
op_star
)paren
suffix:semicolon
r_void
id|end_kio_request
c_func
(paren
r_struct
id|kiobuf
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|simple_wakeup_kiobuf
c_func
(paren
r_struct
id|kiobuf
op_star
)paren
suffix:semicolon
r_int
id|alloc_kiovec
c_func
(paren
r_int
id|nr
comma
r_struct
id|kiobuf
op_star
op_star
)paren
suffix:semicolon
r_void
id|free_kiovec
c_func
(paren
r_int
id|nr
comma
r_struct
id|kiobuf
op_star
op_star
)paren
suffix:semicolon
r_int
id|expand_kiobuf
c_func
(paren
r_struct
id|kiobuf
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|kiobuf_wait_for_io
c_func
(paren
r_struct
id|kiobuf
op_star
)paren
suffix:semicolon
multiline_comment|/* fs/buffer.c */
r_int
id|brw_kiovec
c_func
(paren
r_int
id|rw
comma
r_int
id|nr
comma
r_struct
id|kiobuf
op_star
id|iovec
(braket
)braket
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|b
(braket
)braket
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_IOBUF_H */
eof
