multiline_comment|/*&n; *  $Id: nfsroot.c,v 1.45 1998/03/07 10:44:46 mj Exp $&n; *&n; *  Copyright (C) 1995, 1996  Gero Kuhlmann &lt;gero@gkminix.han.de&gt;&n; *&n; *  Allow an NFS filesystem to be mounted as root. The way this works is:&n; *     (1) Use the IP autoconfig mechanism to set local IP addresses and routes.&n; *     (2) Handle RPC negotiation with the system which replied to RARP or&n; *         was reported as a boot server by BOOTP or manually.&n; *     (3) The actual mounting is done later, when init() is running.&n; *&n; *&n; *&t;Changes:&n; *&n; *&t;Alan Cox&t;:&t;Removed get_address name clash with FPU.&n; *&t;Alan Cox&t;:&t;Reformatted a bit.&n; *&t;Gero Kuhlmann&t;:&t;Code cleanup&n; *&t;Michael Rausch  :&t;Fixed recognition of an incoming RARP answer.&n; *&t;Martin Mares&t;: (2.0)&t;Auto-configuration via BOOTP supported.&n; *&t;Martin Mares&t;:&t;Manual selection of interface &amp; BOOTP/RARP.&n; *&t;Martin Mares&t;:&t;Using network routes instead of host routes,&n; *&t;&t;&t;&t;allowing the default configuration to be used&n; *&t;&t;&t;&t;for normal operation of the host.&n; *&t;Martin Mares&t;:&t;Randomized timer with exponential backoff&n; *&t;&t;&t;&t;installed to minimize network congestion.&n; *&t;Martin Mares&t;:&t;Code cleanup.&n; *&t;Martin Mares&t;: (2.1)&t;BOOTP and RARP made configuration options.&n; *&t;Martin Mares&t;:&t;Server hostname generation fixed.&n; *&t;Gerd Knorr&t;:&t;Fixed wired inode handling&n; *&t;Martin Mares&t;: (2.2)&t;&quot;0.0.0.0&quot; addresses from command line ignored.&n; *&t;Martin Mares&t;:&t;RARP replies not tested for server address.&n; *&t;Gero Kuhlmann&t;: (2.3) Some bug fixes and code cleanup again (please&n; *&t;&t;&t;&t;send me your new patches _before_ bothering&n; *&t;&t;&t;&t;Linus so that I don&squot; always have to cleanup&n; *&t;&t;&t;&t;_afterwards_ - thanks)&n; *&t;Gero Kuhlmann&t;:&t;Last changes of Martin Mares undone.&n; *&t;Gero Kuhlmann&t;: &t;RARP replies are tested for specified server&n; *&t;&t;&t;&t;again. However, it&squot;s now possible to have&n; *&t;&t;&t;&t;different RARP and NFS servers.&n; *&t;Gero Kuhlmann&t;:&t;&quot;0.0.0.0&quot; addresses from command line are&n; *&t;&t;&t;&t;now mapped to INADDR_NONE.&n; *&t;Gero Kuhlmann&t;:&t;Fixed a bug which prevented BOOTP path name&n; *&t;&t;&t;&t;from being used (thanks to Leo Spiekman)&n; *&t;Andy Walker&t;:&t;Allow to specify the NFS server in nfs_root&n; *&t;&t;&t;&t;without giving a path name&n; *&t;Swen Th&#xfffd;mmler&t;:&t;Allow to specify the NFS options in nfs_root&n; *&t;&t;&t;&t;without giving a path name. Fix BOOTP request&n; *&t;&t;&t;&t;for domainname (domainname is NIS domain, not&n; *&t;&t;&t;&t;DNS domain!). Skip dummy devices for BOOTP.&n; *&t;Jacek Zapala&t;:&t;Fixed a bug which prevented server-ip address&n; *&t;&t;&t;&t;from nfsroot parameter from being used.&n; *&t;Olaf Kirch&t;:&t;Adapted to new NFS code.&n; *&t;Jakub Jelinek&t;:&t;Free used code segment.&n; *&t;Marko Kohtala&t;:&t;Fixed some bugs.&n; *&t;Martin Mares&t;:&t;Debug message cleanup&n; *&t;Martin Mares&t;:&t;Changed to use the new generic IP layer autoconfig&n; *&t;&t;&t;&t;code. BOOTP and RARP moved there.&n; *&t;Martin Mares&t;:&t;Default path now contains host name instead of&n; *&t;&t;&t;&t;host IP address (but host name defaults to IP&n; *&t;&t;&t;&t;address anyway).&n; *&t;Martin Mares&t;:&t;Use root_server_addr appropriately during setup.&n; *&t;Martin Mares&t;:&t;Rewrote parameter parsing, now hopefully giving&n; *&t;&t;&t;&t;correct overriding.&n; *&t;Trond Myklebust :&t;Add in preliminary support for NFSv3 and TCP.&n; *&t;&t;&t;&t;Fix bug in root_nfs_addr(). nfs_data.namlen&n; *&t;&t;&t;&t;is NOT for the length of the hostname.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;net/ipconfig.h&gt;
multiline_comment|/* Define this to allow debugging output */
DECL|macro|NFSROOT_DEBUG
macro_line|#undef NFSROOT_DEBUG
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY NFSDBG_ROOT
multiline_comment|/* Default path we try to mount. &quot;%s&quot; gets replaced by our IP address */
DECL|macro|NFS_ROOT
mdefine_line|#define NFS_ROOT&t;&t;&quot;/tftpboot/%s&quot;
multiline_comment|/* Parameters passed from the kernel command line */
DECL|variable|__initdata
r_static
r_char
id|nfs_root_name
(braket
l_int|256
)braket
id|__initdata
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* Address of NFS server */
DECL|variable|__initdata
r_static
id|__u32
id|servaddr
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Name of directory to mount */
DECL|variable|__initdata
r_static
r_char
id|nfs_path
(braket
id|NFS_MAXPATHLEN
)braket
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* NFS-related data */
DECL|variable|__initdata
r_static
r_struct
id|nfs_mount_data
id|nfs_data
id|__initdata
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* NFS mount info */
DECL|variable|__initdata
r_static
r_int
id|nfs_port
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Port to connect to for NFS */
DECL|variable|__initdata
r_static
r_int
id|mount_port
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Mount daemon port number */
multiline_comment|/***************************************************************************&n;&n;&t;&t;&t;     Parsing of options&n;&n; ***************************************************************************/
multiline_comment|/*&n; *  The following integer options are recognized&n; */
DECL|struct|nfs_int_opts
r_static
r_struct
id|nfs_int_opts
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|val
r_int
op_star
id|val
suffix:semicolon
DECL|variable|__initdata
)brace
id|root_int_opts
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_string|&quot;port&quot;
comma
op_amp
id|nfs_port
)brace
comma
(brace
l_string|&quot;rsize&quot;
comma
op_amp
id|nfs_data.rsize
)brace
comma
(brace
l_string|&quot;wsize&quot;
comma
op_amp
id|nfs_data.wsize
)brace
comma
(brace
l_string|&quot;timeo&quot;
comma
op_amp
id|nfs_data.timeo
)brace
comma
(brace
l_string|&quot;retrans&quot;
comma
op_amp
id|nfs_data.retrans
)brace
comma
(brace
l_string|&quot;acregmin&quot;
comma
op_amp
id|nfs_data.acregmin
)brace
comma
(brace
l_string|&quot;acregmax&quot;
comma
op_amp
id|nfs_data.acregmax
)brace
comma
(brace
l_string|&quot;acdirmin&quot;
comma
op_amp
id|nfs_data.acdirmin
)brace
comma
(brace
l_string|&quot;acdirmax&quot;
comma
op_amp
id|nfs_data.acdirmax
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *  And now the flag options&n; */
DECL|struct|nfs_bool_opts
r_static
r_struct
id|nfs_bool_opts
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|and_mask
r_int
id|and_mask
suffix:semicolon
DECL|member|or_mask
r_int
id|or_mask
suffix:semicolon
DECL|variable|__initdata
)brace
id|root_bool_opts
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_string|&quot;soft&quot;
comma
op_complement
id|NFS_MOUNT_SOFT
comma
id|NFS_MOUNT_SOFT
)brace
comma
(brace
l_string|&quot;hard&quot;
comma
op_complement
id|NFS_MOUNT_SOFT
comma
l_int|0
)brace
comma
(brace
l_string|&quot;intr&quot;
comma
op_complement
id|NFS_MOUNT_INTR
comma
id|NFS_MOUNT_INTR
)brace
comma
(brace
l_string|&quot;nointr&quot;
comma
op_complement
id|NFS_MOUNT_INTR
comma
l_int|0
)brace
comma
(brace
l_string|&quot;posix&quot;
comma
op_complement
id|NFS_MOUNT_POSIX
comma
id|NFS_MOUNT_POSIX
)brace
comma
(brace
l_string|&quot;noposix&quot;
comma
op_complement
id|NFS_MOUNT_POSIX
comma
l_int|0
)brace
comma
(brace
l_string|&quot;cto&quot;
comma
op_complement
id|NFS_MOUNT_NOCTO
comma
l_int|0
)brace
comma
(brace
l_string|&quot;nocto&quot;
comma
op_complement
id|NFS_MOUNT_NOCTO
comma
id|NFS_MOUNT_NOCTO
)brace
comma
(brace
l_string|&quot;ac&quot;
comma
op_complement
id|NFS_MOUNT_NOAC
comma
l_int|0
)brace
comma
(brace
l_string|&quot;noac&quot;
comma
op_complement
id|NFS_MOUNT_NOAC
comma
id|NFS_MOUNT_NOAC
)brace
comma
(brace
l_string|&quot;lock&quot;
comma
op_complement
id|NFS_MOUNT_NONLM
comma
l_int|0
)brace
comma
(brace
l_string|&quot;nolock&quot;
comma
op_complement
id|NFS_MOUNT_NONLM
comma
id|NFS_MOUNT_NONLM
)brace
comma
macro_line|#ifdef CONFIG_NFS_V3
(brace
l_string|&quot;v2&quot;
comma
op_complement
id|NFS_MOUNT_VER3
comma
l_int|0
)brace
comma
(brace
l_string|&quot;v3&quot;
comma
op_complement
id|NFS_MOUNT_VER3
comma
id|NFS_MOUNT_VER3
)brace
comma
macro_line|#endif
(brace
l_string|&quot;udp&quot;
comma
op_complement
id|NFS_MOUNT_TCP
comma
l_int|0
)brace
comma
(brace
l_string|&quot;tcp&quot;
comma
op_complement
id|NFS_MOUNT_TCP
comma
id|NFS_MOUNT_TCP
)brace
comma
(brace
l_string|&quot;broken_suid&quot;
comma
op_complement
id|NFS_MOUNT_BROKEN_SUID
comma
id|NFS_MOUNT_BROKEN_SUID
)brace
comma
(brace
l_int|NULL
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *  Extract IP address from the parameter string if needed. Note that we&n; *  need to have root_server_addr set _before_ IPConfig gets called as it&n; *  can override it.&n; */
DECL|function|root_nfs_parse_addr
r_static
r_void
id|__init
id|root_nfs_parse_addr
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_int
id|octets
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|cq
suffix:semicolon
id|cp
op_assign
id|cq
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
id|octets
OL
l_int|4
)paren
(brace
r_while
c_loop
(paren
op_star
id|cp
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|cp
op_le
l_char|&squot;9&squot;
)paren
id|cp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cp
op_eq
id|cq
op_logical_or
id|cp
op_minus
id|cq
OG
l_int|3
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;.&squot;
op_logical_or
id|octets
op_eq
l_int|3
)paren
id|octets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|octets
OL
l_int|4
)paren
id|cp
op_increment
suffix:semicolon
id|cq
op_assign
id|cp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|octets
op_eq
l_int|4
op_logical_and
(paren
op_star
id|cp
op_eq
l_char|&squot;:&squot;
op_logical_or
op_star
id|cp
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;:&squot;
)paren
op_star
id|cp
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|root_server_addr
op_assign
id|in_aton
c_func
(paren
id|name
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|name
comma
id|cp
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Parse option string.&n; */
DECL|function|root_nfs_parse
r_static
r_void
id|__init
id|root_nfs_parse
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|options
comma
op_star
id|val
comma
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|options
op_assign
id|strchr
c_func
(paren
id|name
comma
l_char|&squot;,&squot;
)paren
)paren
)paren
(brace
op_star
id|options
op_increment
op_assign
l_int|0
suffix:semicolon
id|cp
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cp
)paren
(brace
r_if
c_cond
(paren
(paren
id|val
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;=&squot;
)paren
)paren
)paren
(brace
r_struct
id|nfs_int_opts
op_star
id|opts
op_assign
id|root_int_opts
suffix:semicolon
op_star
id|val
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|opts-&gt;name
op_logical_and
id|strcmp
c_func
(paren
id|opts-&gt;name
comma
id|cp
)paren
)paren
id|opts
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name
)paren
op_star
(paren
id|opts-&gt;val
)paren
op_assign
(paren
r_int
)paren
id|simple_strtoul
c_func
(paren
id|val
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|nfs_bool_opts
op_star
id|opts
op_assign
id|root_bool_opts
suffix:semicolon
r_while
c_loop
(paren
id|opts-&gt;name
op_logical_and
id|strcmp
c_func
(paren
id|opts-&gt;name
comma
id|cp
)paren
)paren
id|opts
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|opts-&gt;name
)paren
(brace
id|nfs_data.flags
op_and_assign
id|opts-&gt;and_mask
suffix:semicolon
id|nfs_data.flags
op_or_assign
id|opts-&gt;or_mask
suffix:semicolon
)brace
)brace
id|cp
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_logical_and
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;default&quot;
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|buf
comma
id|name
comma
id|NFS_MAXPATHLEN
op_minus
l_int|1
)paren
suffix:semicolon
id|buf
(braket
id|NFS_MAXPATHLEN
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Prepare the NFS data structure and parse all options.&n; */
DECL|function|root_nfs_name
r_static
r_int
id|__init
id|root_nfs_name
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_char
id|buf
(braket
id|NFS_MAXPATHLEN
)braket
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
multiline_comment|/* Set some default values */
id|memset
c_func
(paren
op_amp
id|nfs_data
comma
l_int|0
comma
r_sizeof
(paren
id|nfs_data
)paren
)paren
suffix:semicolon
id|nfs_port
op_assign
op_minus
l_int|1
suffix:semicolon
id|nfs_data.version
op_assign
id|NFS_MOUNT_VERSION
suffix:semicolon
id|nfs_data.flags
op_assign
id|NFS_MOUNT_NONLM
suffix:semicolon
multiline_comment|/* No lockd in nfs root yet */
id|nfs_data.rsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
id|nfs_data.wsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
id|nfs_data.bsize
op_assign
l_int|0
suffix:semicolon
id|nfs_data.timeo
op_assign
l_int|7
suffix:semicolon
id|nfs_data.retrans
op_assign
l_int|3
suffix:semicolon
id|nfs_data.acregmin
op_assign
l_int|3
suffix:semicolon
id|nfs_data.acregmax
op_assign
l_int|60
suffix:semicolon
id|nfs_data.acdirmin
op_assign
l_int|30
suffix:semicolon
id|nfs_data.acdirmax
op_assign
l_int|60
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
id|NFS_ROOT
)paren
suffix:semicolon
multiline_comment|/* Process options received from the remote server */
id|root_nfs_parse
c_func
(paren
id|root_server_path
comma
id|buf
)paren
suffix:semicolon
multiline_comment|/* Override them by options set on kernel command-line */
id|root_nfs_parse
c_func
(paren
id|name
comma
id|buf
)paren
suffix:semicolon
id|cp
op_assign
id|system_utsname.nodename
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|buf
)paren
op_plus
id|strlen
c_func
(paren
id|cp
)paren
OG
id|NFS_MAXPATHLEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Pathname for remote directory too long.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|nfs_path
comma
id|buf
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get NFS server address.&n; */
DECL|function|root_nfs_addr
r_static
r_int
id|__init
id|root_nfs_addr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|servaddr
op_assign
id|root_server_addr
)paren
op_eq
id|INADDR_NONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: No NFS server available, giving up.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|nfs_data.hostname
comma
id|in_ntoa
c_func
(paren
id|servaddr
)paren
comma
r_sizeof
(paren
id|nfs_data.hostname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Tell the user what&squot;s going on.&n; */
macro_line|#ifdef NFSROOT_DEBUG
DECL|function|root_nfs_print
r_static
r_void
id|__init
id|root_nfs_print
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS: Mounting %s on server %s as root&bslash;n&quot;
comma
id|nfs_path
comma
id|nfs_data.hostname
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     rsize = %d, wsize = %d, timeo = %d, retrans = %d&bslash;n&quot;
comma
id|nfs_data.rsize
comma
id|nfs_data.wsize
comma
id|nfs_data.timeo
comma
id|nfs_data.retrans
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     acreg (min,max) = (%d,%d), acdir (min,max) = (%d,%d)&bslash;n&quot;
comma
id|nfs_data.acregmin
comma
id|nfs_data.acregmax
comma
id|nfs_data.acdirmin
comma
id|nfs_data.acdirmax
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Root-NFS:     nfsd port = %d, mountd port = %d, flags = %08x&bslash;n&quot;
comma
id|nfs_port
comma
id|mount_port
comma
id|nfs_data.flags
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|root_nfs_init
r_int
id|__init
id|root_nfs_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef NFSROOT_DEBUG
id|nfs_debug
op_or_assign
id|NFSDBG_ROOT
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Decode the root directory path name and NFS options from&n;&t; * the kernel command line. This has to go here in order to&n;&t; * be able to use the client IP address for the remote root&n;&t; * directory (necessary for pure RARP booting).&n;&t; */
r_if
c_cond
(paren
id|root_nfs_name
c_func
(paren
id|nfs_root_name
)paren
OL
l_int|0
op_logical_or
id|root_nfs_addr
c_func
(paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef NFSROOT_DEBUG
id|root_nfs_print
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Parse NFS server and directory information passed on the kernel&n; *  command line.&n; */
DECL|function|nfs_root_setup
r_int
id|__init
id|nfs_root_setup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|UNNAMED_MAJOR
comma
l_int|255
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;/&squot;
op_logical_or
id|line
(braket
l_int|0
)braket
op_eq
l_char|&squot;,&squot;
op_logical_or
(paren
id|line
(braket
l_int|0
)braket
op_ge
l_char|&squot;0&squot;
op_logical_and
id|line
(braket
l_int|0
)braket
op_le
l_char|&squot;9&squot;
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|nfs_root_name
comma
id|line
comma
r_sizeof
(paren
id|nfs_root_name
)paren
)paren
suffix:semicolon
id|nfs_root_name
(braket
r_sizeof
(paren
id|nfs_root_name
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|line
)paren
op_plus
id|strlen
c_func
(paren
id|NFS_ROOT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ge
r_sizeof
(paren
id|nfs_root_name
)paren
)paren
id|line
(braket
r_sizeof
(paren
id|nfs_root_name
)paren
op_minus
id|strlen
c_func
(paren
id|NFS_ROOT
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|nfs_root_name
comma
id|NFS_ROOT
comma
id|line
)paren
suffix:semicolon
)brace
id|root_nfs_parse_addr
c_func
(paren
id|nfs_root_name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nfsroot=&quot;
comma
id|nfs_root_setup
)paren
suffix:semicolon
multiline_comment|/***************************************************************************&n;&n;&t;       Routines to actually mount the root directory&n;&n; ***************************************************************************/
multiline_comment|/*&n; *  Construct sockaddr_in from address and port number.&n; */
r_static
r_inline
r_void
DECL|function|set_sockaddr
id|set_sockaddr
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin
comma
id|__u32
id|addr
comma
id|__u16
id|port
)paren
(brace
id|sin-&gt;sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin-&gt;sin_addr.s_addr
op_assign
id|addr
suffix:semicolon
id|sin-&gt;sin_port
op_assign
id|port
suffix:semicolon
)brace
multiline_comment|/*&n; *  Query server portmapper for the port of a daemon program.&n; */
DECL|function|root_nfs_getport
r_static
r_int
id|__init
id|root_nfs_getport
c_func
(paren
r_int
id|program
comma
r_int
id|version
comma
r_int
id|proto
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Looking up port of RPC %d/%d on %s&bslash;n&quot;
comma
id|program
comma
id|version
comma
id|in_ntoa
c_func
(paren
id|servaddr
)paren
)paren
suffix:semicolon
id|set_sockaddr
c_func
(paren
op_amp
id|sin
comma
id|servaddr
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rpc_getport_external
c_func
(paren
op_amp
id|sin
comma
id|program
comma
id|version
comma
id|proto
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Use portmapper to find mountd and nfsd port numbers if not overriden&n; *  by the user. Use defaults if portmapper is not available.&n; *  XXX: Is there any nfs server with no portmapper?&n; */
DECL|function|root_nfs_ports
r_static
r_int
id|__init
id|root_nfs_ports
c_func
(paren
r_void
)paren
(brace
r_int
id|port
suffix:semicolon
r_int
id|nfsd_ver
comma
id|mountd_ver
suffix:semicolon
r_int
id|nfsd_port
comma
id|mountd_port
suffix:semicolon
r_int
id|proto
suffix:semicolon
r_if
c_cond
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_VER3
)paren
(brace
id|nfsd_ver
op_assign
id|NFS3_VERSION
suffix:semicolon
id|mountd_ver
op_assign
id|NFS_MNT3_VERSION
suffix:semicolon
id|nfsd_port
op_assign
id|NFS_PORT
suffix:semicolon
id|mountd_port
op_assign
id|NFS_MNT_PORT
suffix:semicolon
)brace
r_else
(brace
id|nfsd_ver
op_assign
id|NFS2_VERSION
suffix:semicolon
id|mountd_ver
op_assign
id|NFS_MNT_VERSION
suffix:semicolon
id|nfsd_port
op_assign
id|NFS_PORT
suffix:semicolon
id|mountd_port
op_assign
id|NFS_MNT_PORT
suffix:semicolon
)brace
id|proto
op_assign
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_TCP
)paren
ques
c_cond
id|IPPROTO_TCP
suffix:colon
id|IPPROTO_UDP
suffix:semicolon
r_if
c_cond
(paren
id|nfs_port
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|port
op_assign
id|root_nfs_getport
c_func
(paren
id|NFS_PROGRAM
comma
id|nfsd_ver
comma
id|proto
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Unable to get nfsd port &quot;
l_string|&quot;number from server, using default&bslash;n&quot;
)paren
suffix:semicolon
id|port
op_assign
id|nfsd_port
suffix:semicolon
)brace
id|nfs_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Root-NFS: Portmapper on server returned %d &quot;
l_string|&quot;as nfsd port&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|port
op_assign
id|root_nfs_getport
c_func
(paren
id|NFS_MNT_PROGRAM
comma
id|nfsd_ver
comma
id|proto
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Unable to get mountd port &quot;
l_string|&quot;number from server, using default&bslash;n&quot;
)paren
suffix:semicolon
id|port
op_assign
id|mountd_port
suffix:semicolon
)brace
id|mount_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Root-NFS: mountd port is %d&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get a file handle from the server for the directory which is to be&n; *  mounted.&n; */
DECL|function|root_nfs_get_handle
r_static
r_int
id|__init
id|root_nfs_get_handle
c_func
(paren
r_void
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
r_int
id|status
suffix:semicolon
id|set_sockaddr
c_func
(paren
op_amp
id|sin
comma
id|servaddr
comma
id|mount_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfs_data.flags
op_amp
id|NFS_MOUNT_VER3
)paren
id|status
op_assign
id|nfs3_mount
c_func
(paren
op_amp
id|sin
comma
id|nfs_path
comma
op_amp
id|nfs_data.root
)paren
suffix:semicolon
r_else
id|status
op_assign
id|nfs_mount
c_func
(paren
op_amp
id|sin
comma
id|nfs_path
comma
op_amp
id|nfs_data.root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Root-NFS: Server returned error %d &quot;
l_string|&quot;while mounting %s&bslash;n&quot;
comma
id|status
comma
id|nfs_path
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get the NFS port numbers and file handle, and return the prepared &squot;data&squot;&n; *  argument for -&gt;read_super() if everything went OK. Return NULL otherwise.&n; */
DECL|function|nfs_root_data
r_void
op_star
id|__init
id|nfs_root_data
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|root_nfs_init
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|root_nfs_ports
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|root_nfs_get_handle
c_func
(paren
)paren
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|set_sockaddr
c_func
(paren
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|nfs_data.addr
comma
id|servaddr
comma
id|nfs_port
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
op_amp
id|nfs_data
suffix:semicolon
)brace
eof
