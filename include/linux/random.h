multiline_comment|/*&n; * include/linux/random.h&n; *&n; * Include file for the random number generator.&n; */
macro_line|#ifndef _LINUX_RANDOM_H
DECL|macro|_LINUX_RANDOM_H
mdefine_line|#define _LINUX_RANDOM_H
multiline_comment|/* ioctl()&squot;s for the random number generator */
DECL|macro|RNDGETENTCNT
mdefine_line|#define RNDGETENTCNT&t;0x01080000
DECL|macro|RNDADDTOENTCNT
mdefine_line|#define RNDADDTOENTCNT&t;0x01080001
DECL|macro|RNDGETPOOL
mdefine_line|#define RNDGETPOOL&t;0x01080002
DECL|macro|RNDADDENTROPY
mdefine_line|#define RNDADDENTROPY&t;0x01080003
DECL|macro|RNDZAPENTCNT
mdefine_line|#define RNDZAPENTCNT&t;0x01080004
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
