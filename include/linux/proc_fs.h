macro_line|#ifndef _LINUX_PROC_FS_H
DECL|macro|_LINUX_PROC_FS_H
mdefine_line|#define _LINUX_PROC_FS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * The proc filesystem constants/structures&n; */
DECL|enum|root_directory_inos
r_enum
id|root_directory_inos
(brace
DECL|enumerator|PROC_ROOT_INO
id|PROC_ROOT_INO
op_assign
l_int|1
comma
DECL|enumerator|PROC_LOADAVG
id|PROC_LOADAVG
comma
DECL|enumerator|PROC_UPTIME
id|PROC_UPTIME
comma
DECL|enumerator|PROC_MEMINFO
id|PROC_MEMINFO
comma
DECL|enumerator|PROC_KMSG
id|PROC_KMSG
comma
DECL|enumerator|PROC_VERSION
id|PROC_VERSION
comma
DECL|enumerator|PROC_CPUINFO
id|PROC_CPUINFO
comma
DECL|enumerator|PROC_PCI
id|PROC_PCI
comma
DECL|enumerator|PROC_SELF
id|PROC_SELF
comma
multiline_comment|/* will change inode # */
DECL|enumerator|PROC_NET
id|PROC_NET
comma
macro_line|#ifdef CONFIG_DEBUG_MALLOC
DECL|enumerator|PROC_MALLOC
id|PROC_MALLOC
comma
macro_line|#endif
DECL|enumerator|PROC_KCORE
id|PROC_KCORE
comma
DECL|enumerator|PROC_MODULES
id|PROC_MODULES
comma
DECL|enumerator|PROC_STAT
id|PROC_STAT
comma
DECL|enumerator|PROC_DEVICES
id|PROC_DEVICES
comma
DECL|enumerator|PROC_INTERRUPTS
id|PROC_INTERRUPTS
comma
DECL|enumerator|PROC_FILESYSTEMS
id|PROC_FILESYSTEMS
comma
DECL|enumerator|PROC_KSYMS
id|PROC_KSYMS
comma
DECL|enumerator|PROC_DMA
id|PROC_DMA
comma
DECL|enumerator|PROC_IOPORTS
id|PROC_IOPORTS
comma
DECL|enumerator|PROC_PROFILE
id|PROC_PROFILE
multiline_comment|/* whether enabled or not */
)brace
suffix:semicolon
DECL|enum|pid_directory_inos
r_enum
id|pid_directory_inos
(brace
DECL|enumerator|PROC_PID_INO
id|PROC_PID_INO
op_assign
l_int|2
comma
DECL|enumerator|PROC_PID_MEM
id|PROC_PID_MEM
comma
DECL|enumerator|PROC_PID_CWD
id|PROC_PID_CWD
comma
DECL|enumerator|PROC_PID_ROOT
id|PROC_PID_ROOT
comma
DECL|enumerator|PROC_PID_EXE
id|PROC_PID_EXE
comma
DECL|enumerator|PROC_PID_FD
id|PROC_PID_FD
comma
DECL|enumerator|PROC_PID_ENVIRON
id|PROC_PID_ENVIRON
comma
DECL|enumerator|PROC_PID_CMDLINE
id|PROC_PID_CMDLINE
comma
DECL|enumerator|PROC_PID_STAT
id|PROC_PID_STAT
comma
DECL|enumerator|PROC_PID_STATM
id|PROC_PID_STATM
comma
DECL|enumerator|PROC_PID_MAPS
id|PROC_PID_MAPS
)brace
suffix:semicolon
DECL|enum|pid_subdirectory_inos
r_enum
id|pid_subdirectory_inos
(brace
DECL|enumerator|PROC_PID_FD_DIR
id|PROC_PID_FD_DIR
op_assign
l_int|1
)brace
suffix:semicolon
DECL|enum|net_directory_inos
r_enum
id|net_directory_inos
(brace
DECL|enumerator|PROC_NET_UNIX
id|PROC_NET_UNIX
op_assign
l_int|128
comma
macro_line|#ifdef CONFIG_INET
DECL|enumerator|PROC_NET_ARP
id|PROC_NET_ARP
comma
DECL|enumerator|PROC_NET_ROUTE
id|PROC_NET_ROUTE
comma
DECL|enumerator|PROC_NET_DEV
id|PROC_NET_DEV
comma
DECL|enumerator|PROC_NET_RAW
id|PROC_NET_RAW
comma
DECL|enumerator|PROC_NET_TCP
id|PROC_NET_TCP
comma
DECL|enumerator|PROC_NET_UDP
id|PROC_NET_UDP
comma
DECL|enumerator|PROC_NET_SNMP
id|PROC_NET_SNMP
comma
macro_line|#ifdef CONFIG_INET_RARP
DECL|enumerator|PROC_NET_RARP
id|PROC_NET_RARP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IP_MULTICAST
DECL|enumerator|PROC_NET_IGMP
id|PROC_NET_IGMP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IP_FIREWALL
DECL|enumerator|PROC_NET_IPFWFWD
id|PROC_NET_IPFWFWD
comma
DECL|enumerator|PROC_NET_IPFWFWD0
id|PROC_NET_IPFWFWD0
comma
DECL|enumerator|PROC_NET_IPFWBLK
id|PROC_NET_IPFWBLK
comma
DECL|enumerator|PROC_NET_IPFWBLK0
id|PROC_NET_IPFWBLK0
comma
macro_line|#endif
macro_line|#ifdef CONFIG_IP_ACCT
DECL|enumerator|PROC_NET_IPACCT
id|PROC_NET_IPACCT
comma
DECL|enumerator|PROC_NET_IPACCT0
id|PROC_NET_IPACCT0
comma
macro_line|#endif
macro_line|#if&t;defined(CONFIG_WAVELAN)
DECL|enumerator|PROC_NET_WAVELAN
id|PROC_NET_WAVELAN
comma
macro_line|#endif&t;/* defined(CONFIG_WAVELAN) */
macro_line|#endif
macro_line|#ifdef CONFIG_IPX
DECL|enumerator|PROC_NET_IPX_INTERFACE
id|PROC_NET_IPX_INTERFACE
comma
DECL|enumerator|PROC_NET_IPX_ROUTE
id|PROC_NET_IPX_ROUTE
comma
DECL|enumerator|PROC_NET_IPX
id|PROC_NET_IPX
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ATALK
DECL|enumerator|PROC_NET_ATALK
id|PROC_NET_ATALK
comma
DECL|enumerator|PROC_NET_AT_ROUTE
id|PROC_NET_AT_ROUTE
comma
DECL|enumerator|PROC_NET_ATIF
id|PROC_NET_ATIF
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AX25
DECL|enumerator|PROC_NET_AX25_ROUTE
id|PROC_NET_AX25_ROUTE
comma
DECL|enumerator|PROC_NET_AX25
id|PROC_NET_AX25
comma
macro_line|#ifdef CONFIG_NETROM
DECL|enumerator|PROC_NET_NR_NODES
id|PROC_NET_NR_NODES
comma
DECL|enumerator|PROC_NET_NR_NEIGH
id|PROC_NET_NR_NEIGH
comma
DECL|enumerator|PROC_NET_NR
id|PROC_NET_NR
comma
macro_line|#endif
macro_line|#endif
DECL|enumerator|PROC_NET_SOCKSTAT
id|PROC_NET_SOCKSTAT
comma
DECL|enumerator|PROC_NET_LAST
id|PROC_NET_LAST
)brace
suffix:semicolon
DECL|macro|PROC_SUPER_MAGIC
mdefine_line|#define PROC_SUPER_MAGIC 0x9fa0
DECL|struct|proc_dir_entry
r_struct
id|proc_dir_entry
(brace
DECL|member|low_ino
r_int
r_int
id|low_ino
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|proc_read_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|proc_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_write_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_match
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_root_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_base_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_net_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_mem_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_array_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_arraylong_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_kcore_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_profile_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_kmsg_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_link_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_fd_inode_operations
suffix:semicolon
macro_line|#endif
eof
