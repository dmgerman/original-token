macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/un.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &quot;kern_sock.h&quot;
DECL|struct|unix_proto_data
r_static
r_struct
id|unix_proto_data
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
multiline_comment|/* cnt of reference 0=free */
DECL|member|socket
r_struct
id|socket
op_star
id|socket
suffix:semicolon
multiline_comment|/* socket we&squot;re bound to */
DECL|member|protocol
r_int
id|protocol
suffix:semicolon
DECL|member|sockaddr_un
r_struct
id|sockaddr_un
id|sockaddr_un
suffix:semicolon
DECL|member|sockaddr_len
r_int
id|sockaddr_len
suffix:semicolon
multiline_comment|/* &gt;0 if name bound */
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|bp_head
DECL|member|bp_tail
r_int
id|bp_head
comma
id|bp_tail
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|peerupd
r_struct
id|unix_proto_data
op_star
id|peerupd
suffix:semicolon
DECL|variable|unix_datas
)brace
id|unix_datas
(braket
id|NSOCKETS
)braket
suffix:semicolon
DECL|macro|last_unix_data
mdefine_line|#define last_unix_data (unix_datas + NSOCKETS - 1)
DECL|macro|UN_DATA
mdefine_line|#define UN_DATA(SOCK) ((struct unix_proto_data *)(SOCK)-&gt;data)
DECL|macro|UN_PATH_OFFSET
mdefine_line|#define UN_PATH_OFFSET ((unsigned long)((struct sockaddr_un *)0)-&gt;sun_path)
multiline_comment|/*&n; * buffer size must be power of 2. buffer mgmt inspired by pipe code.&n; * note that buffer contents can wraparound, and we can write one byte less&n; * than full size to discern full vs empty.&n; */
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE PAGE_SIZE
DECL|macro|UN_BUF_AVAIL
mdefine_line|#define UN_BUF_AVAIL(UPD) (((UPD)-&gt;bp_head - (UPD)-&gt;bp_tail) &amp; (BUF_SIZE-1))
DECL|macro|UN_BUF_SPACE
mdefine_line|#define UN_BUF_SPACE(UPD) ((BUF_SIZE-1) - UN_BUF_AVAIL(UPD))
r_static
r_int
id|unix_proto_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_dup
c_func
(paren
r_struct
id|socket
op_star
id|newsock
comma
r_struct
id|socket
op_star
id|oldsock
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|peer
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|umyaddr
comma
r_int
id|sockaddr_len
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_connect
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uservaddr
comma
r_int
id|sockaddr_len
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_socketpair
c_func
(paren
r_struct
id|socket
op_star
id|sock1
comma
r_struct
id|socket
op_star
id|sock2
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_accept
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|newsock
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|usockaddr
comma
r_int
op_star
id|usockaddr_len
comma
r_int
id|peer
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_read
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_char
op_star
id|ubuf
comma
r_int
id|size
comma
r_int
id|nonblock
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_write
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_char
op_star
id|ubuf
comma
r_int
id|size
comma
r_int
id|nonblock
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_select
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|which
)paren
suffix:semicolon
r_static
r_int
id|unix_proto_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|variable|unix_proto_ops
r_struct
id|proto_ops
id|unix_proto_ops
op_assign
(brace
id|unix_proto_init
comma
id|unix_proto_create
comma
id|unix_proto_dup
comma
id|unix_proto_release
comma
id|unix_proto_bind
comma
id|unix_proto_connect
comma
id|unix_proto_socketpair
comma
id|unix_proto_accept
comma
id|unix_proto_getname
comma
id|unix_proto_read
comma
id|unix_proto_write
comma
id|unix_proto_select
comma
id|unix_proto_ioctl
)brace
suffix:semicolon
macro_line|#ifdef SOCK_DEBUG
r_void
DECL|function|sockaddr_un_printk
id|sockaddr_un_printk
c_func
(paren
r_struct
id|sockaddr_un
op_star
id|sockun
comma
r_int
id|sockaddr_len
)paren
(brace
r_char
id|buf
(braket
r_sizeof
(paren
id|sockun-&gt;sun_path
)paren
op_plus
l_int|1
)braket
suffix:semicolon
id|sockaddr_len
op_sub_assign
id|UN_PATH_OFFSET
suffix:semicolon
r_if
c_cond
(paren
id|sockun-&gt;sun_family
op_ne
id|AF_UNIX
)paren
id|printk
c_func
(paren
l_string|&quot;sockaddr_un: &lt;BAD FAMILY: %d&gt;&bslash;n&quot;
comma
id|sockun-&gt;sun_family
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sockaddr_len
op_le
l_int|0
op_logical_or
id|sockaddr_len
op_ge
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;sockaddr_un: &lt;BAD LENGTH: %d&gt;&bslash;n&quot;
comma
id|sockaddr_len
)paren
suffix:semicolon
r_else
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|sockun-&gt;sun_path
comma
id|sockaddr_len
)paren
suffix:semicolon
id|buf
(braket
id|sockaddr_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sockaddr_un: &squot;%s&squot;[%d]&bslash;n&quot;
comma
id|buf
comma
id|sockaddr_len
op_plus
id|UN_PATH_OFFSET
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_static
r_struct
id|unix_proto_data
op_star
DECL|function|unix_data_lookup
id|unix_data_lookup
c_func
(paren
r_struct
id|sockaddr_un
op_star
id|sockun
comma
r_int
id|sockaddr_len
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
r_for
c_loop
(paren
id|upd
op_assign
id|unix_datas
suffix:semicolon
id|upd
op_le
id|last_unix_data
suffix:semicolon
op_increment
id|upd
)paren
(brace
r_if
c_cond
(paren
id|upd-&gt;refcnt
op_logical_and
id|upd-&gt;socket
op_logical_and
id|upd-&gt;sockaddr_len
op_eq
id|sockaddr_len
op_logical_and
id|memcmp
c_func
(paren
op_amp
id|upd-&gt;sockaddr_un
comma
id|sockun
comma
id|sockaddr_len
)paren
op_eq
l_int|0
)paren
r_return
id|upd
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_struct
id|unix_proto_data
op_star
DECL|function|unix_data_alloc
id|unix_data_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|upd
op_assign
id|unix_datas
suffix:semicolon
id|upd
op_le
id|last_unix_data
suffix:semicolon
op_increment
id|upd
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|upd-&gt;refcnt
)paren
(brace
id|upd-&gt;refcnt
op_assign
l_int|1
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|upd-&gt;socket
op_assign
l_int|NULL
suffix:semicolon
id|upd-&gt;sockaddr_len
op_assign
l_int|0
suffix:semicolon
id|upd-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|upd-&gt;bp_head
op_assign
id|upd-&gt;bp_tail
op_assign
l_int|0
suffix:semicolon
id|upd-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
id|upd-&gt;peerupd
op_assign
l_int|NULL
suffix:semicolon
r_return
id|upd
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|unix_data_ref
id|unix_data_ref
c_func
(paren
r_struct
id|unix_proto_data
op_star
id|upd
)paren
(brace
op_increment
id|upd-&gt;refcnt
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_data_ref: refing data 0x%x (%d)&bslash;n&quot;
comma
id|upd
comma
id|upd-&gt;refcnt
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|unix_data_deref
id|unix_data_deref
c_func
(paren
r_struct
id|unix_proto_data
op_star
id|upd
)paren
(brace
r_if
c_cond
(paren
id|upd-&gt;refcnt
op_eq
l_int|1
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_data_deref: releasing data 0x%x&bslash;n&quot;
comma
id|upd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|upd-&gt;buf
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|upd-&gt;buf
)paren
suffix:semicolon
id|upd-&gt;buf
op_assign
l_int|NULL
suffix:semicolon
id|upd-&gt;bp_head
op_assign
id|upd-&gt;bp_tail
op_assign
l_int|0
suffix:semicolon
)brace
)brace
op_decrement
id|upd-&gt;refcnt
suffix:semicolon
)brace
multiline_comment|/*&n; * upon a create, we allocate an empty protocol data, and grab a page to&n; * buffer writes&n; */
r_static
r_int
DECL|function|unix_proto_create
id|unix_proto_create
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|protocol
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_create: socket 0x%x, proto %d&bslash;n&quot;
comma
id|sock
comma
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|protocol
op_ne
l_int|0
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_create: protocol != 0&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|upd
op_assign
id|unix_data_alloc
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unix_proto_create: can&squot;t allocate buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|upd-&gt;buf
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unix_proto_create: can&squot;t get page!&bslash;n&quot;
)paren
suffix:semicolon
id|unix_data_deref
c_func
(paren
id|upd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|upd-&gt;protocol
op_assign
id|protocol
suffix:semicolon
id|upd-&gt;socket
op_assign
id|sock
suffix:semicolon
id|UN_DATA
c_func
(paren
id|sock
)paren
op_assign
id|upd
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_create: allocated data 0x%x&bslash;n&quot;
comma
id|upd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|unix_proto_dup
id|unix_proto_dup
c_func
(paren
r_struct
id|socket
op_star
id|newsock
comma
r_struct
id|socket
op_star
id|oldsock
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|oldsock
)paren
suffix:semicolon
r_return
id|unix_proto_create
c_func
(paren
id|newsock
comma
id|upd-&gt;protocol
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|unix_proto_release
id|unix_proto_release
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|peer
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_release: socket 0x%x, unix_data 0x%x&bslash;n&quot;
comma
id|sock
comma
id|upd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|upd
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|upd-&gt;socket
op_ne
id|sock
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unix_proto_release: socket link mismatch!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|upd-&gt;inode
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_release: releasing inode 0x%x&bslash;n&quot;
comma
id|upd-&gt;inode
)paren
suffix:semicolon
id|iput
c_func
(paren
id|upd-&gt;inode
)paren
suffix:semicolon
id|upd-&gt;inode
op_assign
l_int|NULL
suffix:semicolon
)brace
id|UN_DATA
c_func
(paren
id|sock
)paren
op_assign
l_int|NULL
suffix:semicolon
id|upd-&gt;socket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|upd-&gt;peerupd
)paren
id|unix_data_deref
c_func
(paren
id|upd-&gt;peerupd
)paren
suffix:semicolon
id|unix_data_deref
c_func
(paren
id|upd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * bind a name to a socket. this is where much of the work is done. we&n; * allocate a fresh page for the buffer, grab the appropriate inode and&n; * set things up.&n; *&n; * XXX what should we do if an address is already bound? here we return&n; * EINVAL, but it may be necessary to re-bind. i think thats what bsd does&n; * in the case of datagram sockets&n; */
r_static
r_int
DECL|function|unix_proto_bind
id|unix_proto_bind
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|umyaddr
comma
r_int
id|sockaddr_len
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
r_char
id|fname
(braket
r_sizeof
(paren
(paren
(paren
r_struct
id|sockaddr_un
op_star
)paren
l_int|0
)paren
op_member_access_from_pointer
id|sun_path
)paren
op_plus
l_int|1
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|old_fs
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_bind: socket 0x%x, len=%d&bslash;n&quot;
comma
id|sock
comma
id|sockaddr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockaddr_len
op_le
id|UN_PATH_OFFSET
op_logical_or
id|sockaddr_len
op_ge
r_sizeof
(paren
r_struct
id|sockaddr_un
)paren
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_bind: bad length %d&bslash;n&quot;
comma
id|sockaddr_len
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|upd-&gt;sockaddr_len
op_logical_or
id|upd-&gt;inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unix_proto_bind: already bound!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|verify_area
c_func
(paren
id|umyaddr
comma
id|sockaddr_len
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|upd-&gt;sockaddr_un
comma
id|umyaddr
comma
id|sockaddr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|upd-&gt;sockaddr_un.sun_family
op_ne
id|AF_UNIX
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_bind: family is %d, not AF_UNIX (%d)&bslash;n&quot;
comma
id|upd-&gt;sockaddr_un.sun_family
comma
id|AF_UNIX
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|fname
comma
id|upd-&gt;sockaddr_un.sun_path
comma
id|sockaddr_len
op_minus
id|UN_PATH_OFFSET
)paren
suffix:semicolon
id|fname
(braket
id|sockaddr_len
op_minus
id|UN_PATH_OFFSET
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|i
op_assign
id|do_mknod
c_func
(paren
id|fname
comma
id|S_IFSOCK
op_or
l_int|0777
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
id|i
op_assign
id|open_namei
c_func
(paren
id|fname
comma
l_int|0
comma
id|S_IFSOCK
comma
op_amp
id|upd-&gt;inode
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unix_proto_bind: can&squot;t open socket %s&bslash;n&quot;
comma
id|fname
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|upd-&gt;sockaddr_len
op_assign
id|sockaddr_len
suffix:semicolon
multiline_comment|/* now its legal */
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_bind: bound socket address: &quot;
)paren
suffix:semicolon
macro_line|#ifdef SOCK_DEBUG
id|sockaddr_un_printk
c_func
(paren
op_amp
id|upd-&gt;sockaddr_un
comma
id|upd-&gt;sockaddr_len
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * perform a connection. we can only connect to unix sockets (i can&squot;t for&n; * the life of me find an application where that wouldn&squot;t be the case!)&n; */
r_static
r_int
DECL|function|unix_proto_connect
id|unix_proto_connect
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|uservaddr
comma
r_int
id|sockaddr_len
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|unix_proto_data
op_star
id|serv_upd
suffix:semicolon
r_struct
id|sockaddr_un
id|sockun
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_connect: socket 0x%x, servlen=%d&bslash;n&quot;
comma
id|sock
comma
id|sockaddr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockaddr_len
op_le
id|UN_PATH_OFFSET
op_logical_or
id|sockaddr_len
op_ge
r_sizeof
(paren
r_struct
id|sockaddr_un
)paren
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_connect: bad length %d&bslash;n&quot;
comma
id|sockaddr_len
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|verify_area
c_func
(paren
id|uservaddr
comma
id|sockaddr_len
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|sockun
comma
id|uservaddr
comma
id|sockaddr_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sockun.sun_family
op_ne
id|AF_UNIX
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_connect: family is %d, not AF_UNIX (%d)&bslash;n&quot;
comma
id|sockun.sun_family
comma
id|AF_UNIX
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|serv_upd
op_assign
id|unix_data_lookup
c_func
(paren
op_amp
id|sockun
comma
id|sockaddr_len
)paren
)paren
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_connect: can&squot;t locate peer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|i
op_assign
id|sock_awaitconn
c_func
(paren
id|sock
comma
id|serv_upd-&gt;socket
)paren
)paren
OL
l_int|0
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_connect: can&squot;t await connection&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
id|unix_data_ref
c_func
(paren
id|UN_DATA
c_func
(paren
id|sock-&gt;conn
)paren
)paren
suffix:semicolon
id|UN_DATA
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|peerupd
op_assign
id|UN_DATA
c_func
(paren
id|sock-&gt;conn
)paren
suffix:semicolon
multiline_comment|/* ref server */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * to do a socketpair, we make just connect the two datas, easy! since we&n; * always wait on the socket inode, they&squot;re no contention for a wait area,&n; * and deadlock prevention in the case of a process writing to itself is,&n; * ignored, in true unix fashion!&n; */
r_static
r_int
DECL|function|unix_proto_socketpair
id|unix_proto_socketpair
c_func
(paren
r_struct
id|socket
op_star
id|sock1
comma
r_struct
id|socket
op_star
id|sock2
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd1
op_assign
id|UN_DATA
c_func
(paren
id|sock1
)paren
comma
op_star
id|upd2
op_assign
id|UN_DATA
c_func
(paren
id|sock2
)paren
suffix:semicolon
id|unix_data_ref
c_func
(paren
id|upd1
)paren
suffix:semicolon
id|unix_data_ref
c_func
(paren
id|upd2
)paren
suffix:semicolon
id|upd1-&gt;peerupd
op_assign
id|upd2
suffix:semicolon
id|upd2-&gt;peerupd
op_assign
id|upd1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * on accept, we ref the peer&squot;s data for safe writes&n; */
r_static
r_int
DECL|function|unix_proto_accept
id|unix_proto_accept
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|socket
op_star
id|newsock
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_accept: socket 0x%x accepted via socket 0x%x&bslash;n&quot;
comma
id|sock
comma
id|newsock
)paren
suffix:semicolon
id|unix_data_ref
c_func
(paren
id|UN_DATA
c_func
(paren
id|newsock-&gt;conn
)paren
)paren
suffix:semicolon
id|UN_DATA
c_func
(paren
id|newsock
)paren
op_member_access_from_pointer
id|peerupd
op_assign
id|UN_DATA
c_func
(paren
id|newsock-&gt;conn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * gets the current name or the name of the connected socket.&n; */
r_static
r_int
DECL|function|unix_proto_getname
id|unix_proto_getname
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|sockaddr
op_star
id|usockaddr
comma
r_int
op_star
id|usockaddr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
r_int
id|len
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_getname: socket 0x%x for %s&bslash;n&quot;
comma
id|sock
comma
id|peer
ques
c_cond
l_string|&quot;peer&quot;
suffix:colon
l_string|&quot;self&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peer
)paren
(brace
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_getname: socket not connected&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock-&gt;conn
)paren
suffix:semicolon
)brace
r_else
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|usockaddr_len
comma
r_sizeof
(paren
op_star
id|usockaddr_len
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|get_fs_long
c_func
(paren
id|usockaddr_len
)paren
)paren
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|upd-&gt;sockaddr_len
)paren
id|len
op_assign
id|upd-&gt;sockaddr_len
suffix:semicolon
r_if
c_cond
(paren
id|len
)paren
(brace
id|verify_area
c_func
(paren
id|usockaddr
comma
id|len
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|usockaddr
comma
op_amp
id|upd-&gt;sockaddr_un
comma
id|len
)paren
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
id|len
comma
id|usockaddr_len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * we read from our own buf.&n; */
r_static
r_int
DECL|function|unix_proto_read
id|unix_proto_read
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_char
op_star
id|ubuf
comma
r_int
id|size
comma
r_int
id|nonblock
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
r_int
id|todo
comma
id|avail
suffix:semicolon
r_if
c_cond
(paren
(paren
id|todo
op_assign
id|size
)paren
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|avail
op_assign
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: socket not connected&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|sock-&gt;state
op_eq
id|SS_DISCONNECTING
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
)brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: no data available...&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nonblock
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
id|sock-&gt;wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_DISCONNECTING
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: disconnected&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * copy from the read buffer into the user&squot;s buffer, watching for&n;&t; * wraparound. then we wake up the writer&n;&t; */
r_do
(brace
r_int
id|part
comma
id|cando
suffix:semicolon
r_if
c_cond
(paren
id|avail
op_le
l_int|0
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: AVAIL IS NEGATIVE!!!&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cando
op_assign
id|todo
)paren
OG
id|avail
)paren
id|cando
op_assign
id|avail
suffix:semicolon
r_if
c_cond
(paren
id|cando
OG
(paren
id|part
op_assign
id|BUF_SIZE
op_minus
id|upd-&gt;bp_tail
)paren
)paren
id|cando
op_assign
id|part
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_read: avail=%d, todo=%d, cando=%d&bslash;n&quot;
comma
id|avail
comma
id|todo
comma
id|cando
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|ubuf
comma
id|cando
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|ubuf
comma
id|upd-&gt;buf
op_plus
id|upd-&gt;bp_tail
comma
id|cando
)paren
suffix:semicolon
id|upd-&gt;bp_tail
op_assign
(paren
id|upd-&gt;bp_tail
op_plus
id|cando
)paren
op_amp
(paren
id|BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|ubuf
op_add_assign
id|cando
suffix:semicolon
id|todo
op_sub_assign
id|cando
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_CONNECTED
)paren
id|wake_up
c_func
(paren
id|sock-&gt;conn-&gt;wait
)paren
suffix:semicolon
id|avail
op_assign
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|todo
op_logical_and
id|avail
)paren
suffix:semicolon
r_return
id|size
op_minus
id|todo
suffix:semicolon
)brace
multiline_comment|/*&n; * we write to our peer&squot;s buf. when we connected we ref&squot;d this peer so we&n; * are safe that the buffer remains, even after the peer has disconnected,&n; * which we check other ways.&n; */
r_static
r_int
DECL|function|unix_proto_write
id|unix_proto_write
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_char
op_star
id|ubuf
comma
r_int
id|size
comma
r_int
id|nonblock
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|pupd
suffix:semicolon
r_int
id|todo
comma
id|space
suffix:semicolon
r_if
c_cond
(paren
(paren
id|todo
op_assign
id|size
)paren
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: socket not connected&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_DISCONNECTING
)paren
(brace
id|send_sig
c_func
(paren
id|SIGPIPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pupd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
op_member_access_from_pointer
id|peerupd
suffix:semicolon
multiline_comment|/* safer than sock-&gt;conn */
r_while
c_loop
(paren
op_logical_neg
(paren
id|space
op_assign
id|UN_BUF_SPACE
c_func
(paren
id|pupd
)paren
)paren
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: no space left...&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nonblock
)paren
r_return
l_int|0
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
id|sock-&gt;wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_DISCONNECTING
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: disconnected (SIGPIPE)&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGPIPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * copy from the user&squot;s buffer to the write buffer, watching for&n;&t; * wraparound. then we wake up the reader&n;&t; */
r_do
(brace
r_int
id|part
comma
id|cando
suffix:semicolon
r_if
c_cond
(paren
id|space
op_le
l_int|0
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: SPACE IS NEGATIVE!!!&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * we may become disconnected inside this loop, so watch&n;&t;&t; * for it (peerupd is safe until we close)&n;&t;&t; */
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_DISCONNECTING
)paren
(brace
id|send_sig
c_func
(paren
id|SIGPIPE
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cando
op_assign
id|todo
)paren
OG
id|space
)paren
id|cando
op_assign
id|space
suffix:semicolon
r_if
c_cond
(paren
id|cando
OG
(paren
id|part
op_assign
id|BUF_SIZE
op_minus
id|pupd-&gt;bp_head
)paren
)paren
id|cando
op_assign
id|part
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_write: space=%d, todo=%d, cando=%d&bslash;n&quot;
comma
id|space
comma
id|todo
comma
id|cando
)paren
suffix:semicolon
id|verify_area
c_func
(paren
id|ubuf
comma
id|cando
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|pupd-&gt;buf
op_plus
id|pupd-&gt;bp_head
comma
id|ubuf
comma
id|cando
)paren
suffix:semicolon
id|pupd-&gt;bp_head
op_assign
(paren
id|pupd-&gt;bp_head
op_plus
id|cando
)paren
op_amp
(paren
id|BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|ubuf
op_add_assign
id|cando
suffix:semicolon
id|todo
op_sub_assign
id|cando
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_CONNECTED
)paren
id|wake_up
c_func
(paren
id|sock-&gt;conn-&gt;wait
)paren
suffix:semicolon
id|space
op_assign
id|UN_BUF_SPACE
c_func
(paren
id|pupd
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|todo
op_logical_and
id|space
)paren
suffix:semicolon
r_return
id|size
op_minus
id|todo
suffix:semicolon
)brace
r_static
r_int
DECL|function|unix_proto_select
id|unix_proto_select
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|which
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
comma
op_star
id|peerupd
suffix:semicolon
r_if
c_cond
(paren
id|which
op_eq
id|SEL_IN
)paren
(brace
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_select: there is%s data available&bslash;n&quot;
comma
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; no&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
)paren
multiline_comment|/* even if disconnected */
r_return
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_select: socket not connected (read EOF)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|which
op_eq
id|SEL_OUT
)paren
(brace
r_if
c_cond
(paren
id|sock-&gt;state
op_ne
id|SS_CONNECTED
)paren
(brace
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_select: socket not connected (write EOF)&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|peerupd
op_assign
id|UN_DATA
c_func
(paren
id|sock-&gt;conn
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_select: there is%s space available&bslash;n&quot;
comma
id|UN_BUF_SPACE
c_func
(paren
id|peerupd
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; no&quot;
)paren
suffix:semicolon
r_return
(paren
id|UN_BUF_SPACE
c_func
(paren
id|peerupd
)paren
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* SEL_EX */
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_select: there are no exceptions here?!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|unix_proto_ioctl
id|unix_proto_ioctl
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
comma
op_star
id|peerupd
suffix:semicolon
id|upd
op_assign
id|UN_DATA
c_func
(paren
id|sock
)paren
suffix:semicolon
id|peerupd
op_assign
(paren
id|sock-&gt;state
op_eq
id|SS_CONNECTED
)paren
ques
c_cond
id|UN_DATA
c_func
(paren
id|sock-&gt;conn
)paren
suffix:colon
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TIOCINQ
suffix:colon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
op_logical_or
id|peerupd
)paren
id|put_fs_long
c_func
(paren
id|UN_BUF_AVAIL
c_func
(paren
id|upd
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_else
id|put_fs_long
c_func
(paren
l_int|1
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
multiline_comment|/* read EOF */
r_break
suffix:semicolon
r_case
id|TIOCOUTQ
suffix:colon
id|verify_area
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|peerupd
)paren
id|put_fs_long
c_func
(paren
id|UN_BUF_SPACE
c_func
(paren
id|peerupd
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_else
id|put_fs_long
c_func
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|unix_proto_init
id|unix_proto_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|unix_proto_data
op_star
id|upd
suffix:semicolon
id|PRINTK
c_func
(paren
l_string|&quot;unix_proto_init: initializing...&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|upd
op_assign
id|unix_datas
suffix:semicolon
id|upd
op_le
id|last_unix_data
suffix:semicolon
op_increment
id|upd
)paren
id|upd-&gt;refcnt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
