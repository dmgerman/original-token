multiline_comment|/*&n; * include/linux/random.h&n; *&n; * Include file for the random number generator.&n; */
macro_line|#ifndef _LINUX_RANDOM_H
DECL|macro|_LINUX_RANDOM_H
mdefine_line|#define _LINUX_RANDOM_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* ioctl()&squot;s for the random number generator */
multiline_comment|/* Get the entropy count. */
DECL|macro|RNDGETENTCNT
mdefine_line|#define RNDGETENTCNT&t;_IOR( &squot;R&squot;, 0x00, int )
multiline_comment|/* Add to (or subtract from) the entropy count.  (Superuser only.) */
DECL|macro|RNDADDTOENTCNT
mdefine_line|#define RNDADDTOENTCNT&t;_IOW( &squot;R&squot;, 0x01, int )
multiline_comment|/* Get the contents of the entropy pool.  (Superuser only.) */
DECL|macro|RNDGETPOOL
mdefine_line|#define RNDGETPOOL&t;_IOR( &squot;R&squot;, 0x02, int [2] )
multiline_comment|/* &n; * Write bytes into the entropy pool and add to the entropy count.&n; * (Superuser only.)&n; */
DECL|macro|RNDADDENTROPY
mdefine_line|#define RNDADDENTROPY&t;_IOW( &squot;R&squot;, 0x03, int [2] )
multiline_comment|/* Clear entropy count to 0.  (Superuser only.) */
DECL|macro|RNDZAPENTCNT
mdefine_line|#define RNDZAPENTCNT&t;_IO( &squot;R&squot;, 0x04 )
multiline_comment|/* Clear the entropy pool and associated counters.  (Superuser only.) */
DECL|macro|RNDCLEARPOOL
mdefine_line|#define RNDCLEARPOOL&t;_IO( &squot;R&squot;, 0x06 )
DECL|struct|rand_pool_info
r_struct
id|rand_pool_info
(brace
DECL|member|entropy_count
r_int
id|entropy_count
suffix:semicolon
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
DECL|member|buf
id|__u32
id|buf
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Exported functions */
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|rand_initialize
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|rand_initialize_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|rand_initialize_blkdev
c_func
(paren
r_int
id|irq
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|add_keyboard_randomness
c_func
(paren
r_int
r_char
id|scancode
)paren
suffix:semicolon
r_extern
r_void
id|add_mouse_randomness
c_func
(paren
id|__u32
id|mouse_data
)paren
suffix:semicolon
r_extern
r_void
id|add_interrupt_randomness
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|add_blkdev_randomness
c_func
(paren
r_int
id|major
)paren
suffix:semicolon
r_extern
r_void
id|get_random_bytes
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|nbytes
)paren
suffix:semicolon
r_extern
id|__u32
id|secure_tcp_sequence_number
c_func
(paren
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
id|__u16
id|sport
comma
id|__u16
id|dport
)paren
suffix:semicolon
r_extern
id|__u32
id|secure_tcp_syn_cookie
c_func
(paren
id|__u32
id|saddr
comma
id|__u32
id|daddr
comma
id|__u16
id|sport
comma
id|__u16
id|dport
comma
id|__u32
id|sseq
comma
id|__u32
id|count
)paren
suffix:semicolon
macro_line|#ifndef MODULE
r_extern
r_struct
id|file_operations
id|random_fops
comma
id|urandom_fops
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL___ */
macro_line|#endif /* _LINUX_RANDOM_H */
eof
