macro_line|#ifndef _LINUX_PROC_FS_H
DECL|macro|_LINUX_PROC_FS_H
mdefine_line|#define _LINUX_PROC_FS_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
multiline_comment|/*&n; * The proc filesystem constants/structures&n; */
multiline_comment|/*&n; * We always define these enumerators&n; */
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
DECL|enumerator|PROC_SCSI
id|PROC_SCSI
comma
DECL|enumerator|PROC_MALLOC
id|PROC_MALLOC
comma
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
macro_line|#ifdef __SMP_PROF__
DECL|enumerator|PROC_SMP_PROF
id|PROC_SMP_PROF
comma
macro_line|#endif
DECL|enumerator|PROC_PROFILE
id|PROC_PROFILE
comma
multiline_comment|/* whether enabled or not */
DECL|enumerator|PROC_CMDLINE
id|PROC_CMDLINE
comma
DECL|enumerator|PROC_SYS
id|PROC_SYS
comma
DECL|enumerator|PROC_MTAB
id|PROC_MTAB
comma
DECL|enumerator|PROC_MD
id|PROC_MD
comma
DECL|enumerator|PROC_RTC
id|PROC_RTC
comma
DECL|enumerator|PROC_LOCKS
id|PROC_LOCKS
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
DECL|enumerator|PROC_PID_STATUS
id|PROC_PID_STATUS
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
DECL|enumerator|PROC_NET_RARP
id|PROC_NET_RARP
comma
DECL|enumerator|PROC_NET_IGMP
id|PROC_NET_IGMP
comma
DECL|enumerator|PROC_NET_IPMR_VIF
id|PROC_NET_IPMR_VIF
comma
DECL|enumerator|PROC_NET_IPMR_MFC
id|PROC_NET_IPMR_MFC
comma
DECL|enumerator|PROC_NET_IPFWFWD
id|PROC_NET_IPFWFWD
comma
DECL|enumerator|PROC_NET_IPFWIN
id|PROC_NET_IPFWIN
comma
DECL|enumerator|PROC_NET_IPFWOUT
id|PROC_NET_IPFWOUT
comma
DECL|enumerator|PROC_NET_IPACCT
id|PROC_NET_IPACCT
comma
DECL|enumerator|PROC_NET_IPMSQHST
id|PROC_NET_IPMSQHST
comma
DECL|enumerator|PROC_NET_WAVELAN
id|PROC_NET_WAVELAN
comma
DECL|enumerator|PROC_NET_IPX_INTERFACE
id|PROC_NET_IPX_INTERFACE
comma
DECL|enumerator|PROC_NET_IPX_ROUTE
id|PROC_NET_IPX_ROUTE
comma
DECL|enumerator|PROC_NET_IPX
id|PROC_NET_IPX
comma
DECL|enumerator|PROC_NET_ATALK
id|PROC_NET_ATALK
comma
DECL|enumerator|PROC_NET_AT_ROUTE
id|PROC_NET_AT_ROUTE
comma
DECL|enumerator|PROC_NET_ATIF
id|PROC_NET_ATIF
comma
DECL|enumerator|PROC_NET_AX25_ROUTE
id|PROC_NET_AX25_ROUTE
comma
DECL|enumerator|PROC_NET_AX25
id|PROC_NET_AX25
comma
DECL|enumerator|PROC_NET_AX25_CALLS
id|PROC_NET_AX25_CALLS
comma
DECL|enumerator|PROC_NET_NR_NODES
id|PROC_NET_NR_NODES
comma
DECL|enumerator|PROC_NET_NR_NEIGH
id|PROC_NET_NR_NEIGH
comma
DECL|enumerator|PROC_NET_NR
id|PROC_NET_NR
comma
DECL|enumerator|PROC_NET_SOCKSTAT
id|PROC_NET_SOCKSTAT
comma
DECL|enumerator|PROC_NET_RTCACHE
id|PROC_NET_RTCACHE
comma
DECL|enumerator|PROC_NET_AX25_BPQETHER
id|PROC_NET_AX25_BPQETHER
comma
DECL|enumerator|PROC_NET_ALIAS_TYPES
id|PROC_NET_ALIAS_TYPES
comma
DECL|enumerator|PROC_NET_ALIASES
id|PROC_NET_ALIASES
comma
DECL|enumerator|PROC_NET_IP_MASQ_APP
id|PROC_NET_IP_MASQ_APP
comma
DECL|enumerator|PROC_NET_RT6
id|PROC_NET_RT6
comma
DECL|enumerator|PROC_NET_RT6_STATS
id|PROC_NET_RT6_STATS
comma
DECL|enumerator|PROC_NET_STRIP_STATUS
id|PROC_NET_STRIP_STATUS
comma
DECL|enumerator|PROC_NET_STRIP_TRACE
id|PROC_NET_STRIP_TRACE
comma
DECL|enumerator|PROC_NET_Z8530
id|PROC_NET_Z8530
comma
DECL|enumerator|PROC_NET_LAST
id|PROC_NET_LAST
)brace
suffix:semicolon
DECL|enum|scsi_directory_inos
r_enum
id|scsi_directory_inos
(brace
DECL|enumerator|PROC_SCSI_SCSI
id|PROC_SCSI_SCSI
op_assign
l_int|256
comma
DECL|enumerator|PROC_SCSI_ADVANSYS
id|PROC_SCSI_ADVANSYS
comma
DECL|enumerator|PROC_SCSI_EATA
id|PROC_SCSI_EATA
comma
DECL|enumerator|PROC_SCSI_EATA_PIO
id|PROC_SCSI_EATA_PIO
comma
DECL|enumerator|PROC_SCSI_AHA152X
id|PROC_SCSI_AHA152X
comma
DECL|enumerator|PROC_SCSI_AHA1542
id|PROC_SCSI_AHA1542
comma
DECL|enumerator|PROC_SCSI_AHA1740
id|PROC_SCSI_AHA1740
comma
DECL|enumerator|PROC_SCSI_AIC7XXX
id|PROC_SCSI_AIC7XXX
comma
DECL|enumerator|PROC_SCSI_BUSLOGIC
id|PROC_SCSI_BUSLOGIC
comma
DECL|enumerator|PROC_SCSI_U14_34F
id|PROC_SCSI_U14_34F
comma
DECL|enumerator|PROC_SCSI_FDOMAIN
id|PROC_SCSI_FDOMAIN
comma
DECL|enumerator|PROC_SCSI_GENERIC_NCR5380
id|PROC_SCSI_GENERIC_NCR5380
comma
DECL|enumerator|PROC_SCSI_IN2000
id|PROC_SCSI_IN2000
comma
DECL|enumerator|PROC_SCSI_PAS16
id|PROC_SCSI_PAS16
comma
DECL|enumerator|PROC_SCSI_QLOGICFAS
id|PROC_SCSI_QLOGICFAS
comma
DECL|enumerator|PROC_SCSI_QLOGICISP
id|PROC_SCSI_QLOGICISP
comma
DECL|enumerator|PROC_SCSI_SEAGATE
id|PROC_SCSI_SEAGATE
comma
DECL|enumerator|PROC_SCSI_T128
id|PROC_SCSI_T128
comma
DECL|enumerator|PROC_SCSI_NCR53C7xx
id|PROC_SCSI_NCR53C7xx
comma
DECL|enumerator|PROC_SCSI_NCR53C8XX
id|PROC_SCSI_NCR53C8XX
comma
DECL|enumerator|PROC_SCSI_ULTRASTOR
id|PROC_SCSI_ULTRASTOR
comma
DECL|enumerator|PROC_SCSI_7000FASST
id|PROC_SCSI_7000FASST
comma
DECL|enumerator|PROC_SCSI_EATA2X
id|PROC_SCSI_EATA2X
comma
DECL|enumerator|PROC_SCSI_AM53C974
id|PROC_SCSI_AM53C974
comma
DECL|enumerator|PROC_SCSI_SSC
id|PROC_SCSI_SSC
comma
DECL|enumerator|PROC_SCSI_NCR53C406A
id|PROC_SCSI_NCR53C406A
comma
DECL|enumerator|PROC_SCSI_PPA
id|PROC_SCSI_PPA
comma
DECL|enumerator|PROC_SCSI_ESP
id|PROC_SCSI_ESP
comma
DECL|enumerator|PROC_SCSI_A3000
id|PROC_SCSI_A3000
comma
DECL|enumerator|PROC_SCSI_A2091
id|PROC_SCSI_A2091
comma
DECL|enumerator|PROC_SCSI_GVP11
id|PROC_SCSI_GVP11
comma
DECL|enumerator|PROC_SCSI_ATARI
id|PROC_SCSI_ATARI
comma
DECL|enumerator|PROC_SCSI_SCSI_DEBUG
id|PROC_SCSI_SCSI_DEBUG
comma
DECL|enumerator|PROC_SCSI_NOT_PRESENT
id|PROC_SCSI_NOT_PRESENT
comma
DECL|enumerator|PROC_SCSI_FILE
id|PROC_SCSI_FILE
comma
multiline_comment|/* I&squot;m assuming here that we */
DECL|enumerator|PROC_SCSI_LAST
id|PROC_SCSI_LAST
op_assign
(paren
id|PROC_SCSI_FILE
op_plus
l_int|16
)paren
multiline_comment|/* won&squot;t ever see more than */
)brace
suffix:semicolon
multiline_comment|/* 16 HBAs in one machine   */
multiline_comment|/* Finally, the dynamically allocatable proc entries are reserved: */
DECL|macro|PROC_DYNAMIC_FIRST
mdefine_line|#define PROC_DYNAMIC_FIRST 4096
DECL|macro|PROC_NDYNAMIC
mdefine_line|#define PROC_NDYNAMIC      4096
DECL|macro|PROC_SUPER_MAGIC
mdefine_line|#define PROC_SUPER_MAGIC 0x9fa0
multiline_comment|/*&n; * This is not completely implemented yet. The idea is to&n; * create an in-memory tree (like the actual /proc filesystem&n; * tree) of these proc_dir_entries, so that we can dynamically&n; * add new files to /proc.&n; *&n; * The &quot;next&quot; pointer creates a linked list of one /proc directory,&n; * while parent/subdir create the directory structure (every&n; * /proc file has a parent, but &quot;subdir&quot; is NULL for all&n; * non-directory entries).&n; *&n; * &quot;get_info&quot; is called at &quot;read&quot;, while &quot;fill_inode&quot; is used to&n; * fill in file type/protection/owner information specific to the&n; * particular /proc file.&n; */
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
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|nlink
id|nlink_t
id|nlink
suffix:semicolon
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|ops
r_struct
id|inode_operations
op_star
id|ops
suffix:semicolon
DECL|member|get_info
r_int
(paren
op_star
id|get_info
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|fill_inode
r_void
(paren
op_star
id|fill_inode
)paren
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
DECL|member|next
DECL|member|parent
DECL|member|subdir
r_struct
id|proc_dir_entry
op_star
id|next
comma
op_star
id|parent
comma
op_star
id|subdir
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
(paren
op_star
id|dispatch_scsi_info_ptr
)paren
(paren
r_int
id|ino
comma
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
id|inout
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_root
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_net
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_sys
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_pid
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_pid_fd
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_scsi_inode_operations
suffix:semicolon
r_extern
r_void
id|proc_root_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|proc_base_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|proc_net_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|proc_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_register_dynamic
c_func
(paren
r_struct
id|proc_dir_entry
op_star
comma
r_struct
id|proc_dir_entry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_unregister
c_func
(paren
r_struct
id|proc_dir_entry
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|proc_net_register
r_static
r_inline
r_int
id|proc_net_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|x
)paren
(brace
r_return
id|proc_register
c_func
(paren
op_amp
id|proc_net
comma
id|x
)paren
suffix:semicolon
)brace
DECL|function|proc_net_unregister
r_static
r_inline
r_int
id|proc_net_unregister
c_func
(paren
r_int
id|x
)paren
(brace
r_return
id|proc_unregister
c_func
(paren
op_amp
id|proc_net
comma
id|x
)paren
suffix:semicolon
)brace
DECL|function|proc_scsi_register
r_static
r_inline
r_int
id|proc_scsi_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|driver
comma
r_struct
id|proc_dir_entry
op_star
id|x
)paren
(brace
id|x-&gt;ops
op_assign
op_amp
id|proc_scsi_inode_operations
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;low_ino
OL
id|PROC_SCSI_FILE
)paren
(brace
r_return
id|proc_register
c_func
(paren
op_amp
id|proc_scsi
comma
id|x
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|proc_register
c_func
(paren
id|driver
comma
id|x
)paren
suffix:semicolon
)brace
)brace
DECL|function|proc_scsi_unregister
r_static
r_inline
r_int
id|proc_scsi_unregister
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|driver
comma
r_int
id|x
)paren
(brace
r_extern
r_void
id|scsi_init_free
c_func
(paren
r_char
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
op_le
id|PROC_SCSI_FILE
)paren
(brace
r_return
id|proc_unregister
c_func
(paren
op_amp
id|proc_scsi
comma
id|x
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|proc_dir_entry
op_star
op_star
id|p
op_assign
op_amp
id|driver-&gt;subdir
comma
op_star
id|dp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dp
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;low_ino
op_eq
id|x
)paren
r_break
suffix:semicolon
id|p
op_assign
op_amp
id|dp-&gt;next
suffix:semicolon
)brace
id|ret
op_assign
id|proc_unregister
c_func
(paren
id|driver
comma
id|x
)paren
suffix:semicolon
id|scsi_init_free
c_func
(paren
(paren
r_char
op_star
)paren
id|dp
comma
r_sizeof
(paren
r_struct
id|proc_dir_entry
)paren
op_plus
l_int|4
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
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
r_int
id|init_proc_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|proc_get_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|proc_dir_entry
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
comma
r_int
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
multiline_comment|/*&n; * These are generic /proc routines that use the internal&n; * &quot;struct proc_dir_entry&quot; tree to traverse the filesystem.&n; *&n; * The /proc root directory has extended versions to take care&n; * of the /proc/&lt;pid&gt; subdirectories.&n; */
r_extern
r_int
id|proc_readdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_extern
r_int
id|proc_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_net_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_netdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_scsi_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_mem_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_sys_inode_operations
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
