macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/termios.h&gt;&t;/* For TIOCOUTQ/INQ */
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;net/datalink.h&gt;
macro_line|#include &lt;net/p8022.h&gt;
macro_line|#include &lt;net/psnap.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
DECL|macro|NETBEUI_DEBUG
macro_line|#undef NETBEUI_DEBUG
macro_line|#ifdef NETBEUI_DEBUG
DECL|macro|DPRINT
mdefine_line|#define DPRINT(x)&t;&t;print(x)
macro_line|#else
DECL|macro|DPRINT
mdefine_line|#define DPRINT(x)
macro_line|#endif
DECL|macro|min
mdefine_line|#define min(a,b)&t;(((a)&lt;(b))?(a):(b))
multiline_comment|/***********************************************************************************************************************&bslash;&n;*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n;*&t;&t;&t;&t;&t;&t;Handlers for the socket list.&t;&t;&t;&t;&t;&t;*&n;*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n;&bslash;***********************************************************************************************************************/
DECL|variable|netbeui_socket_list
r_static
id|netbeui_socket
op_star
id|netbeui_socket_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; *&t;Note: Sockets may not be removed _during_ an interrupt or inet_bh&n; *&t;handler using this technique. They can be added although we do not&n; *&t;use this facility.&n; */
DECL|function|netbeui_remove_socket
r_extern
r_inline
r_void
id|netbeui_remove_socket
c_func
(paren
id|netbeui_socket
op_star
id|sk
)paren
(brace
id|sklist_remove_socket
c_func
(paren
op_amp
id|netbeui_socket_list
comma
id|sk
)paren
suffix:semicolon
)brace
DECL|function|netbeui_insert_socket
id|extenr
r_inline
r_void
id|netbeui_insert_socket
c_func
(paren
id|netbeui_socket
op_star
id|sk
)paren
(brace
id|sklist_insert_socket
c_func
(paren
op_amp
id|netbeui_socket_list
comma
id|sk
)paren
suffix:semicolon
id|netbeui_socket_list
op_assign
id|sk
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|netbeui_destroy_socket
r_static
r_void
id|netbeui_destroy_socket
c_func
(paren
id|netbeui_socket
op_star
id|sk
)paren
(brace
multiline_comment|/*&n;&t; *&t;Release netbios logical channels first&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;af_nb.nb_link
)paren
(brace
id|netbeui_delete_channel
c_func
(paren
id|sk-&gt;af_nb.nb_link
)paren
suffix:semicolon
id|sk-&gt;af_nb.nb_link
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;af_nb.src_name
)paren
(brace
id|netbeui_release_name
c_func
(paren
id|sk-&gt;af_nb.src_name
)paren
suffix:semicolon
id|sk-&gt;af_nb.src_name
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;af_nb.dst_name
)paren
(brace
id|netbeui_release_name
c_func
(paren
id|sk-&gt;af_nb.dst_name
)paren
suffix:semicolon
id|sk-&gt;af_nb.dst_name
op_assign
l_int|NULL
suffix:semicolon
)brace
id|netbeui_remove_listener
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sklist_destroy_socket
c_func
(paren
op_amp
id|netbeui_socket
comma
id|sk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Called from proc fs&n; */
DECL|function|netbeui_get_info
r_int
id|netbeui_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;A device event has occurred. Watch for devices going down and&n; *&t;delete our use of them (iface and route).&n; */
DECL|function|nb_device_event
r_static
r_int
id|nb_device_event
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|event
comma
r_void
op_star
id|ptr
)paren
(brace
r_if
c_cond
(paren
id|event
op_eq
id|NETDEV_DOWN
)paren
(brace
multiline_comment|/* Discard any use of this */
id|netbeui_drop_device
c_func
(paren
(paren
r_struct
id|device
op_star
)paren
id|ptr
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************************************************&bslash;&n;*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;            *&n;*&t;      Handling for system calls applied via the various interfaces to a netbeui socket object&t;&t;    *&n;*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;    *&n;&bslash;*******************************************************************************************************************/
DECL|function|netbeui_listen
r_static
r_int
id|netbeui_listen
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_int
id|backlog
)paren
(brace
r_struct
id|sock
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_CLOSED
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|backlog
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|backlog
OL
l_int|128
)paren
(brace
id|sk-&gt;backlog
op_assign
id|backlog
suffix:semicolon
)brace
r_else
id|sk-&gt;backlog
op_assign
l_int|128
suffix:semicolon
id|sk-&gt;state
op_assign
id|TCP_LISTEN
suffix:semicolon
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
id|netbeui_add_listener
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Create a socket. Initialise the socket, blank the addresses&n; *&t;set the state.&n; */
DECL|function|netbeui_create
r_static
r_int
id|netbeui_create
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
id|netbeui_socket
op_star
id|sk
suffix:semicolon
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sk_alloc
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|sock-&gt;type
)paren
(brace
r_case
id|SOCK_DGRAM
suffix:colon
r_break
suffix:semicolon
r_case
id|SOCK_SEQPACKET
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|sk_free
c_func
(paren
(paren
r_void
op_star
)paren
id|sk
)paren
suffix:semicolon
r_return
op_minus
id|ESOCKTNOSUPPORT
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|sock_init_data
c_func
(paren
id|sock
comma
id|sk
)paren
suffix:semicolon
id|sk-&gt;mtu
op_assign
l_int|1500
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Copy a socket. No work needed.&n; */
DECL|function|netbeui_dup
r_static
r_int
id|netbeui_dup
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
r_return
id|netbeui_create
c_func
(paren
id|newsock
comma
id|oldsock-&gt;type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Free a socket. No work needed&n; */
DECL|function|netbeui_release
r_static
r_int
id|netbeui_release
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
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sk-&gt;dead
)paren
(brace
id|sk
op_member_access_from_pointer
id|state_change
c_func
(paren
id|sk
)paren
suffix:semicolon
)brace
id|sk-&gt;dead
op_assign
l_int|1
suffix:semicolon
id|sock-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|netbeui_destroy_socket
c_func
(paren
id|sk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set the address &squot;our end&squot; of the connection.&n; */
DECL|function|netbeui_bind
r_static
r_int
id|netbeui_bind
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
id|uaddr
comma
r_int
id|addr_len
)paren
(brace
id|netbeui_socket
op_star
id|sk
suffix:semicolon
r_struct
id|sockaddr_netbeui
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_netbeui
op_star
)paren
id|uaddr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;zapped
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr_len
op_ne
r_sizeof
(paren
r_struct
id|sockaddr_netbeui
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr-&gt;snb_family
op_ne
id|AF_NETBEUI
)paren
(brace
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;This will sleep. To meet POSIX it is non interruptible.&n;&t; *&t;Someone should give the 1003.1g authors an injection of&n;&t; *&t;imagination...&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;af_nb.src_name
op_ne
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Try and get the name. It may return various &squot;invalid&squot; name&n;&t; *&t;problem reports or EADDRINUSE if we or another node holds&n;&t; *&t;the desired name.&n;&t; */
id|sk-&gt;af_nb.src_name
op_assign
id|netbeui_alloc_name
c_func
(paren
id|addr
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;af_nb.src_name
op_eq
l_int|NULL
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Add us to the active socket list &n;&t; */
id|netbeui_insert_socket
c_func
(paren
id|sk
)paren
suffix:semicolon
id|sk-&gt;zapped
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Set the address we talk to.&n; */
DECL|function|netbeui_connect
r_static
r_int
id|netbeui_connect
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
id|uaddr
comma
r_int
id|addr_len
comma
r_int
id|flags
)paren
(brace
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_struct
id|sockaddr_netbeui
op_star
id|addr
op_assign
(paren
r_struct
id|sockaddr_netbeui
op_star
)paren
id|uaddr
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check pending operations&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
op_logical_and
id|sock-&gt;state
op_eq
id|SS_CONNECTING
)paren
(brace
id|sock-&gt;state
op_eq
id|SS_CONNECTED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_CLOSE
op_amp
id|sock-&gt;state
op_eq
id|SS_CONNECTING
)paren
(brace
id|sock-&gt;state
op_eq
id|SS_UNCONNECTED
suffix:semicolon
r_return
op_minus
id|ECONNREFUSED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sock-&gt;state
op_eq
id|SS_CONNECTING
op_logical_and
(paren
id|flags
op_amp
id|O_NONBLOCK
)paren
)paren
(brace
r_return
op_minus
id|EINPROGRESS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sk-&gt;state
op_eq
id|TCP_ESTABLISHED
)paren
(brace
r_return
op_minus
id|EISCONN
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;If this is new it must really be new...&n;&t; */
r_if
c_cond
(paren
id|sk-&gt;af_nb.dst_name
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|addr_len
op_ne
r_sizeof
(paren
r_struct
id|sockaddr_nb
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|addr-&gt;snb_family
op_ne
id|AF_NETBEUI
)paren
(brace
r_return
op_minus
id|EAFNOSUPPORT
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Try and find the name&n;&t;&t; */
)brace
)brace
multiline_comment|/*&n; *&t;Not relevant&n; */
DECL|function|netbeui_socketpair
r_static
r_int
id|netbeui_socketpair
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
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;WRITE ME&n; */
DECL|function|netbeui_accept
r_static
r_int
id|netbeui_accept
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
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|newsock-&gt;data
)paren
(brace
id|sk_free
c_func
(paren
id|newsock-&gt;data
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Find the name of a netbeui socket. Just copy the right&n; *&t;fields into the sockaddr.&n; */
DECL|function|netbeui_getname
r_static
r_int
id|netbeui_getname
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
id|uaddr
comma
r_int
op_star
id|uaddr_len
comma
r_int
id|peer
)paren
(brace
r_struct
id|sockaddr_netbeui
id|snb
suffix:semicolon
id|netbeui_socket
op_star
id|sk
suffix:semicolon
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;zapped
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|uaddr_len
op_assign
r_sizeof
(paren
r_struct
id|sockaddr_netbeui
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
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
r_return
op_minus
id|ENOTCONN
suffix:semicolon
)brace
)brace
r_else
(brace
)brace
id|snb.snb_family
op_assign
id|AF_NETBEUI
suffix:semicolon
id|memcpy
c_func
(paren
id|uaddr
comma
op_amp
id|snb
comma
r_sizeof
(paren
id|snb
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Receive a packet (in skb) from device dev.&n; */
DECL|function|netbeui_rcv
r_static
r_int
id|netbeui_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
(brace
r_return
id|nb_llc_rcv
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|netbeui_sendmsg
r_static
r_int
id|netbeui_sendmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|len
comma
r_int
id|nonblock
comma
r_int
id|flags
)paren
(brace
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_struct
id|sockaddr_nb
op_star
id|usnb
op_assign
(paren
r_struct
id|sockaddr_nb
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_struct
id|nbhdr
op_star
id|nbp
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|netbeui_route
op_star
id|rt
suffix:semicolon
r_int
id|loopback
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|flags
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
l_int|1500
)paren
(brace
multiline_comment|/* - headers!! */
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usnb
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;zapped
)paren
(brace
r_if
c_cond
(paren
id|netbeui_autobind
c_func
(paren
id|sk
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|msg-&gt;msg_namelen
OL
r_sizeof
(paren
op_star
id|usnb
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usnb-&gt;snb_family
op_ne
id|AF_NETBEUI
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Check broadcast */
)brace
r_else
(brace
r_if
c_cond
(paren
id|sk-&gt;state
op_ne
id|TCP_ESTABLISHED
)paren
(brace
r_return
op_minus
id|ENOTCONN
suffix:semicolon
)brace
multiline_comment|/* Connected .. */
)brace
multiline_comment|/* Build a packet */
id|SOCK_DEBUG
c_func
(paren
id|sk
comma
l_string|&quot;SK %p: Got address.&bslash;n&quot;
comma
id|sk
)paren
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
r_struct
id|nbhdr
)paren
op_plus
id|len
op_plus
id|nb_dl-&gt;header_length
suffix:semicolon
multiline_comment|/* For headers */
id|SOCK_DEBUG
c_func
(paren
id|sk
comma
l_string|&quot;SK %p: Size needed %d, device %s&bslash;n&quot;
comma
id|sk
comma
id|size
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|size
op_add_assign
id|dev-&gt;hard_header_len
suffix:semicolon
id|skb
op_assign
id|sock_alloc_send_skb
c_func
(paren
id|sk
comma
id|size
comma
l_int|0
comma
l_int|0
comma
op_amp
id|err
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
r_return
id|err
suffix:semicolon
)brace
id|skb-&gt;sk
op_assign
id|sk
suffix:semicolon
id|skb-&gt;free
op_assign
l_int|1
suffix:semicolon
id|skb-&gt;arp
op_assign
l_int|1
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|nb_dl-&gt;header_length
)paren
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
id|dev-&gt;hard_header_len
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|SOCK_DEBUG
c_func
(paren
id|sk
comma
l_string|&quot;SK %p: Begin build.&bslash;n&quot;
comma
id|sk
)paren
suffix:semicolon
id|nbp
op_assign
(paren
r_struct
id|nbhdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|nbhdr
)paren
)paren
suffix:semicolon
id|SOCK_DEBUG
c_func
(paren
id|sk
comma
l_string|&quot;SK %p: Copy user data (%d bytes).&bslash;n&quot;
comma
id|sk
comma
id|len
)paren
suffix:semicolon
id|err
op_assign
id|memcpy_fromiovec
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
comma
id|msg-&gt;msg_iov
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FIREWALL
r_if
c_cond
(paren
id|call_out_firewall
c_func
(paren
id|AF_NETBEUI
comma
id|skb-&gt;dev
comma
id|nbp
comma
l_int|NULL
)paren
op_ne
id|FW_ACCEPT
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|nb_send_low
c_func
(paren
id|dev
comma
id|skb
comma
op_amp
id|usat-&gt;sat_addr
comma
l_int|NULL
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
)brace
id|SOCK_DEBUG
c_func
(paren
id|sk
comma
l_string|&quot;SK %p: Done write (%d).&bslash;n&quot;
comma
id|sk
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|netbeui_recvmsg
r_static
r_int
id|netbeui_recvmsg
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|size
comma
r_int
id|noblock
comma
r_int
id|flags
comma
r_int
op_star
id|addr_len
)paren
(brace
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_struct
id|sockaddr_nb
op_star
id|snb
op_assign
(paren
r_struct
id|sockaddr_nb
op_star
)paren
id|msg-&gt;msg_name
suffix:semicolon
r_struct
id|nbphdr
op_star
id|nbp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|er
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|addr_len
)paren
(brace
op_star
id|addr_len
op_assign
r_sizeof
(paren
op_star
id|snb
)paren
suffix:semicolon
)brace
id|skb
op_assign
id|skb_recv_datagram
c_func
(paren
id|sk
comma
id|flags
comma
id|noblock
comma
op_amp
id|er
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
r_return
id|er
suffix:semicolon
)brace
id|snb
op_assign
(paren
r_struct
id|nbphdr
op_star
)paren
(paren
id|skb-&gt;h.raw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;type
op_eq
id|SOCK_RAW
)paren
(brace
id|copied
op_assign
id|skb-&gt;len
r_if
c_cond
(paren
id|copied
OG
id|size
)paren
(brace
id|copied
op_assign
id|size
suffix:semicolon
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
)brace
id|er
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
l_int|0
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
id|copied
op_assign
id|skb-&gt;len
op_minus
r_sizeof
(paren
op_star
id|nbp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copied
OG
id|size
)paren
(brace
id|copied
op_assign
id|size
suffix:semicolon
id|msg-&gt;msg_flags
op_or_assign
id|MSG_TRUNC
suffix:semicolon
)brace
id|er
op_assign
id|skb_copy_datagram_iovec
c_func
(paren
id|skb
comma
r_sizeof
(paren
op_star
id|nbp
)paren
comma
id|msg-&gt;msg_iov
comma
id|copied
)paren
suffix:semicolon
r_if
c_cond
(paren
id|er
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snb
)paren
(brace
id|sat-&gt;sat_family
op_assign
id|AF_NETBEUI
suffix:semicolon
multiline_comment|/* Copy name over */
)brace
id|out
suffix:colon
id|skb_free_datagram
c_func
(paren
id|sk
comma
id|skb
)paren
suffix:semicolon
r_return
id|er
ques
c_cond
id|er
suffix:colon
(paren
id|copied
)paren
suffix:semicolon
)brace
DECL|function|netbeui_shutdown
r_static
r_int
id|netbeui_shutdown
c_func
(paren
r_struct
id|socket
op_star
id|sk
comma
r_int
id|how
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|netbeui_poll
r_static
r_int
id|netbeui_poll
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_return
id|datagram_poll
c_func
(paren
id|sk
comma
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Netbeui ioctl calls.&n; */
DECL|function|netbeui_ioctl
r_static
r_int
id|netbeui_ioctl
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
r_int
id|amount
op_assign
l_int|0
suffix:semicolon
id|netbeui_socket
op_star
id|sk
op_assign
(paren
id|netbeui_socket
op_star
)paren
id|sock-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Protocol layer&n;&t;&t; */
r_case
id|TIOCOUTQ
suffix:colon
id|amount
op_assign
id|sk-&gt;sndbuf
op_minus
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;wmem_alloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amount
OL
l_int|0
)paren
(brace
id|amount
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TIOCINQ
suffix:colon
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* These two are safe on a single CPU system as only user tasks fiddle here */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_peek
c_func
(paren
op_amp
id|sk-&gt;receive_queue
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|amount
op_assign
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ddpehdr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|SIOCGSTAMP
suffix:colon
r_if
c_cond
(paren
id|sk
)paren
(brace
r_if
c_cond
(paren
id|sk-&gt;stamp.tv_sec
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|sk-&gt;stamp
comma
r_sizeof
(paren
r_struct
id|timeval
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Routing&n;&t;&t; */
r_case
id|SIOCADDRT
suffix:colon
r_case
id|SIOCDELRT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|nbrtr_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Interface&n;&t;&t; */
r_case
id|SIOCGIFADDR
suffix:colon
r_case
id|SIOCSIFADDR
suffix:colon
r_case
id|SIOCGIFBRDADDR
suffix:colon
r_return
id|nbif_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Physical layer ioctl calls&n;&t;&t; */
r_case
id|SIOCSIFLINK
suffix:colon
r_case
id|SIOCGIFHWADDR
suffix:colon
r_case
id|SIOCSIFHWADDR
suffix:colon
r_case
id|SIOCGIFFLAGS
suffix:colon
r_case
id|SIOCSIFFLAGS
suffix:colon
r_case
id|SIOCGIFMTU
suffix:colon
r_case
id|SIOCGIFCONF
suffix:colon
r_case
id|SIOCADDMULTI
suffix:colon
r_case
id|SIOCDELMULTI
suffix:colon
r_return
id|dev_ioctl
c_func
(paren
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SIOCSIFMETRIC
suffix:colon
r_case
id|SIOCSIFBRDADDR
suffix:colon
r_case
id|SIOCGIFNETMASK
suffix:colon
r_case
id|SIOCSIFNETMASK
suffix:colon
r_case
id|SIOCGIFMEM
suffix:colon
r_case
id|SIOCSIFMEM
suffix:colon
r_case
id|SIOCGIFDSTADDR
suffix:colon
r_case
id|SIOCSIFDSTADDR
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|put_user
c_func
(paren
id|amount
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|variable|netbeui_proto_ops
r_static
r_struct
id|proto_ops
id|netbeui_proto_ops
op_assign
(brace
id|AF_NETBEUI
comma
id|netbeui_create
comma
id|netbeui_dup
comma
id|netbeui_release
comma
id|netbeui_bind
comma
id|netbeui_connect
comma
id|netbeui_socketpair
comma
id|netbeui_accept
comma
id|netbeui_getname
comma
id|netbeui_poll
comma
id|netbeui_ioctl
comma
id|netbeui_listen
comma
id|netbeui_shutdown
comma
id|sock_no_setsockopt
comma
id|sock_no_getsockopt
comma
id|sock_no_fcntl
comma
id|netbeui_sendmsg
comma
id|netbeui_recvmsg
)brace
suffix:semicolon
DECL|variable|nb_notifier
r_static
r_struct
id|notifier_block
id|nb_notifier
op_assign
initialization_block
suffix:semicolon
DECL|variable|nb_snap_id
r_static
r_char
id|nb_snap_id
(braket
)braket
op_assign
initialization_block
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_netbeui
r_static
r_struct
id|proc_dir_entry
id|proc_netbeui
op_assign
(brace
id|PROC_NET_NETBEUI
comma
l_int|9
comma
l_string|&quot;netbeui&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
l_int|0
comma
op_amp
id|proc_net_inode_operations
comma
id|netbeui_get_info
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Called by proto.c on kernel start up */
DECL|function|netbeui_proto_init
r_void
id|netbeui_proto_init
c_func
(paren
r_struct
id|net_proto
op_star
id|pro
)paren
(brace
(paren
r_void
)paren
id|sock_register
c_func
(paren
id|netbeui_proto_ops.family
comma
op_amp
id|netbeui_proto_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nb_dl
op_assign
id|register_8022_client
c_func
(paren
id|nb_8022_id
comma
id|netbeui_rcv
)paren
)paren
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unable to register Netbeui with 802.2.&bslash;n&quot;
)paren
suffix:semicolon
id|register_netdevice_notifier
c_func
(paren
op_amp
id|nb_notifier
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_register
c_func
(paren
op_amp
id|proc_netbeui
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NetBEUI 0.03 for Linux NET3.037&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|netbeui_proto_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_net_unregister
c_func
(paren
id|PROC_NET_NETBEUI
)paren
suffix:semicolon
macro_line|#endif
id|unregister_netdevice_notifier
c_func
(paren
op_amp
id|nb_notifier
)paren
suffix:semicolon
id|unregister_snap_client
c_func
(paren
id|nb_snap_id
)paren
suffix:semicolon
id|sock_unregister
c_func
(paren
id|netbeui_proto_ops.family
)paren
suffix:semicolon
)brace
macro_line|#endif  /* MODULE */
eof
