multiline_comment|/*&n; *&t;SUCS NET3:&n; *&n; *&t;Generic datagram handling routines. These are generic for all protocols. Possibly a generic IP version on top&n; *&t;of these would make sense. Not tonight however 8-).&n; *&t;This is used because UDP, RAW, PACKET, DDP, IPX, AX.25 and NetROM layer all have identical select code and mostly&n; *&t;identical recvmsg() code. So we share it here. The select was shared before but buried in udp.c so I moved it.&n; *&n; *&t;Authors:&t;Alan Cox &lt;alan@cymru.net&gt;. (datagram_select() from old udp.c code)&n; *&n; *&t;Fixes:&n; *&t;&t;Alan Cox&t;:&t;NULL return from skb_peek_copy() understood&n; *&t;&t;Alan Cox&t;:&t;Rewrote skb_read_datagram to avoid the skb_peek_copy stuff.&n; *&t;&t;Alan Cox&t;:&t;Added support for SOCK_SEQPACKET. IPX can no longer use the SO_TYPE hack but&n; *&t;&t;&t;&t;&t;AX.25 now works right, and SPX is feasible.&n; *&t;&t;Alan Cox&t;:&t;Fixed write select of non IP protocol crash.&n; *&t;&t;Florian  La Roche:&t;Changed for my new skbuff handling.&n; *&t;&t;Darryl Miles&t;:&t;Fixed non-blocking SOCK_SEQPACKET.&n; *&t;&t;Linus Torvalds&t;:&t;BSD semantic fixes.&n; *&t;&t;Alan Cox&t;:&t;Datagram iovec handling&n; *&t;&t;Darryl Miles&t;:&t;Fixed non-blocking SOCK_STREAM.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/*&n; * Wait for a packet..&n; *&n; * Interrupts off so that no packet arrives before we begin sleeping.&n; * Otherwise we might miss our wake up&n; */
DECL|function|wait_for_packet
r_static
r_inline
r_void
id|wait_for_packet
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
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
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
op_eq
l_int|NULL
)paren
id|interruptible_sleep_on
c_func
(paren
id|sk-&gt;sleep
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Is a socket &squot;connection oriented&squot; ?&n; */
DECL|function|connection_based
r_static
r_inline
r_int
id|connection_based
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
(paren
id|sk-&gt;type
op_eq
id|SOCK_SEQPACKET
op_logical_or
id|sk-&gt;type
op_eq
id|SOCK_STREAM
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Get a datagram skbuff, understands the peeking, nonblocking wakeups and possible&n; *&t;races. This replaces identical code in packet,raw and udp, as well as the IPX&n; *&t;AX.25 and Appletalk. It also finally fixes the long standing peek and read&n; *&t;race for datagram sockets. If you alter this routine remember it must be&n; *&t;re-entrant.&n; *&n; *&t;This function will lock the socket if a skb is returned, so the caller&n; *&t;needs to unlock the socket in that case (usually by calling skb_free_datagram)&n; */
DECL|function|skb_recv_datagram
r_struct
id|sk_buff
op_star
id|skb_recv_datagram
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|flags
comma
r_int
id|noblock
comma
r_int
op_star
id|err
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|lock_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
id|restart
suffix:colon
r_while
c_loop
(paren
id|skb_queue_empty
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
multiline_comment|/* No data */
(brace
multiline_comment|/* Socket errors? */
id|error
op_assign
id|sock_error
c_func
(paren
id|sk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|no_packet
suffix:semicolon
multiline_comment|/* Socket shut down? */
r_if
c_cond
(paren
id|sk-&gt;shutdown
op_amp
id|RCV_SHUTDOWN
)paren
r_goto
id|no_packet
suffix:semicolon
multiline_comment|/* Sequenced packets can come disconnected. If so we report the problem */
id|error
op_assign
op_minus
id|ENOTCONN
suffix:semicolon
r_if
c_cond
(paren
id|connection_based
c_func
(paren
id|sk
)paren
op_logical_and
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
r_goto
id|no_packet
suffix:semicolon
)brace
multiline_comment|/* User doesn&squot;t want to wait */
id|error
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|noblock
)paren
r_goto
id|no_packet
suffix:semicolon
multiline_comment|/* handle signals */
id|error
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_goto
id|no_packet
suffix:semicolon
id|wait_for_packet
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/* Again only user level code calls this function, so nothing interrupt level&n;&t;   will suddenly eat the receive_queue */
r_if
c_cond
(paren
id|flags
op_amp
id|MSG_PEEK
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
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;users
op_increment
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* shouldn&squot;t happen but .. */
r_goto
id|restart
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
multiline_comment|/* Avoid race if someone beats us to the data */
r_goto
id|restart
suffix:semicolon
id|skb-&gt;users
op_increment
suffix:semicolon
r_return
id|skb
suffix:semicolon
id|no_packet
suffix:colon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
op_star
id|err
op_assign
id|error
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|skb_free_datagram
r_void
id|skb_free_datagram
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
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
id|skb-&gt;users
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;users
op_le
l_int|0
)paren
(brace
multiline_comment|/* See if it needs destroying */
multiline_comment|/* Been dequeued by someone - ie it&squot;s read */
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;next
op_logical_and
op_logical_neg
id|skb-&gt;prev
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_READ
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|release_sock
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Copy a datagram to a linear buffer.&n; */
DECL|function|skb_copy_datagram
r_int
id|skb_copy_datagram
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|offset
comma
r_char
op_star
id|to
comma
r_int
id|size
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|to
comma
id|skb-&gt;h.raw
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Copy a datagram to an iovec.&n; */
DECL|function|skb_copy_datagram_iovec
r_int
id|skb_copy_datagram_iovec
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|offset
comma
r_struct
id|iovec
op_star
id|to
comma
r_int
id|size
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|memcpy_toiovec
c_func
(paren
id|to
comma
id|skb-&gt;h.raw
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Datagram select: Again totally generic. Moved from udp.c&n; *&t;Now does seqpacket.&n; */
DECL|function|datagram_select
r_int
id|datagram_select
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;err
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|sel_type
)paren
(brace
r_case
id|SEL_IN
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;shutdown
op_amp
id|RCV_SHUTDOWN
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|connection_based
c_func
(paren
id|sk
)paren
op_logical_and
id|sk-&gt;state
op_eq
id|TCP_CLOSE
)paren
(brace
multiline_comment|/* Connection closed: Wake up */
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
(brace
multiline_comment|/* This appears to be consistent&n;&t;&t;&t;&t;   with other stacks */
r_return
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SEL_OUT
suffix:colon
r_if
c_cond
(paren
id|sk-&gt;shutdown
op_amp
id|SEND_SHUTDOWN
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|connection_based
c_func
(paren
id|sk
)paren
op_logical_and
id|sk-&gt;state
op_eq
id|TCP_SYN_SENT
)paren
(brace
multiline_comment|/* Connection still in progress */
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;prot
op_logical_and
id|sock_wspace
c_func
(paren
id|sk
)paren
op_ge
id|MIN_WRITE_SPACE
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;prot
op_eq
l_int|NULL
op_logical_and
id|sk-&gt;sndbuf
op_minus
id|sk-&gt;wmem_alloc
op_ge
id|MIN_WRITE_SPACE
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SEL_EX
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* select failed.. */
id|select_wait
c_func
(paren
id|sk-&gt;sleep
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
