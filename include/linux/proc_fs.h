macro_line|#ifndef _LINUX_PROC_FS_H
DECL|macro|_LINUX_PROC_FS_H
mdefine_line|#define _LINUX_PROC_FS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
multiline_comment|/*&n; * The proc filesystem constants/structures&n; */
multiline_comment|/*&n; * Offset of the first process in the /proc root directory..&n; */
DECL|macro|FIRST_PROCESS_ENTRY
mdefine_line|#define FIRST_PROCESS_ENTRY 256
multiline_comment|/*&n; * We always define these enumerators&n; */
r_enum
(brace
DECL|enumerator|PROC_ROOT_INO
id|PROC_ROOT_INO
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|enum|scsi_directory_inos
r_enum
id|scsi_directory_inos
(brace
DECL|enumerator|PROC_SCSI_ADVANSYS
id|PROC_SCSI_ADVANSYS
op_assign
l_int|256
comma
DECL|enumerator|PROC_SCSI_PCI2000
id|PROC_SCSI_PCI2000
comma
DECL|enumerator|PROC_SCSI_PCI2220I
id|PROC_SCSI_PCI2220I
comma
DECL|enumerator|PROC_SCSI_PSI240I
id|PROC_SCSI_PSI240I
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
DECL|enumerator|PROC_SCSI_GDTH
id|PROC_SCSI_GDTH
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
DECL|enumerator|PROC_SCSI_QLOGICFC
id|PROC_SCSI_QLOGICFC
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
DECL|enumerator|PROC_SCSI_SYM53C8XX
id|PROC_SCSI_SYM53C8XX
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
DECL|enumerator|PROC_SCSI_IBMMCA
id|PROC_SCSI_IBMMCA
comma
DECL|enumerator|PROC_SCSI_FD_MCS
id|PROC_SCSI_FD_MCS
comma
DECL|enumerator|PROC_SCSI_EATA2X
id|PROC_SCSI_EATA2X
comma
DECL|enumerator|PROC_SCSI_DC390T
id|PROC_SCSI_DC390T
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
DECL|enumerator|PROC_SCSI_SYM53C416
id|PROC_SCSI_SYM53C416
comma
DECL|enumerator|PROC_SCSI_MEGARAID
id|PROC_SCSI_MEGARAID
comma
DECL|enumerator|PROC_SCSI_PPA
id|PROC_SCSI_PPA
comma
DECL|enumerator|PROC_SCSI_ATP870U
id|PROC_SCSI_ATP870U
comma
DECL|enumerator|PROC_SCSI_ESP
id|PROC_SCSI_ESP
comma
DECL|enumerator|PROC_SCSI_QLOGICPTI
id|PROC_SCSI_QLOGICPTI
comma
DECL|enumerator|PROC_SCSI_AMIGA7XX
id|PROC_SCSI_AMIGA7XX
comma
DECL|enumerator|PROC_SCSI_MVME147
id|PROC_SCSI_MVME147
comma
DECL|enumerator|PROC_SCSI_MVME16x
id|PROC_SCSI_MVME16x
comma
DECL|enumerator|PROC_SCSI_BVME6000
id|PROC_SCSI_BVME6000
comma
DECL|enumerator|PROC_SCSI_SIM710
id|PROC_SCSI_SIM710
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
DECL|enumerator|PROC_SCSI_MAC
id|PROC_SCSI_MAC
comma
DECL|enumerator|PROC_SCSI_IDESCSI
id|PROC_SCSI_IDESCSI
comma
DECL|enumerator|PROC_SCSI_SGIWD93
id|PROC_SCSI_SGIWD93
comma
DECL|enumerator|PROC_SCSI_MESH
id|PROC_SCSI_MESH
comma
DECL|enumerator|PROC_SCSI_53C94
id|PROC_SCSI_53C94
comma
DECL|enumerator|PROC_SCSI_PLUTO
id|PROC_SCSI_PLUTO
comma
DECL|enumerator|PROC_SCSI_INI9100U
id|PROC_SCSI_INI9100U
comma
DECL|enumerator|PROC_SCSI_INIA100
id|PROC_SCSI_INIA100
comma
DECL|enumerator|PROC_SCSI_IPH5526_FC
id|PROC_SCSI_IPH5526_FC
comma
DECL|enumerator|PROC_SCSI_FCAL
id|PROC_SCSI_FCAL
comma
DECL|enumerator|PROC_SCSI_I2O
id|PROC_SCSI_I2O
comma
DECL|enumerator|PROC_SCSI_USB_SCSI
id|PROC_SCSI_USB_SCSI
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
DECL|enum|mca_directory_inos
r_enum
id|mca_directory_inos
(brace
DECL|enumerator|PROC_MCA_MACHINE
id|PROC_MCA_MACHINE
op_assign
(paren
id|PROC_SCSI_LAST
op_plus
l_int|1
)paren
comma
DECL|enumerator|PROC_MCA_REGISTERS
id|PROC_MCA_REGISTERS
comma
DECL|enumerator|PROC_MCA_VIDEO
id|PROC_MCA_VIDEO
comma
DECL|enumerator|PROC_MCA_SCSI
id|PROC_MCA_SCSI
comma
DECL|enumerator|PROC_MCA_SLOT
id|PROC_MCA_SLOT
comma
multiline_comment|/* the 8 adapter slots */
DECL|enumerator|PROC_MCA_LAST
id|PROC_MCA_LAST
op_assign
(paren
id|PROC_MCA_SLOT
op_plus
l_int|8
)paren
)brace
suffix:semicolon
multiline_comment|/* Finally, the dynamically allocatable proc entries are reserved: */
DECL|macro|PROC_DYNAMIC_FIRST
mdefine_line|#define PROC_DYNAMIC_FIRST 4096
DECL|macro|PROC_NDYNAMIC
mdefine_line|#define PROC_NDYNAMIC      4096
DECL|macro|PROC_OPENPROM_FIRST
mdefine_line|#define PROC_OPENPROM_FIRST (PROC_DYNAMIC_FIRST+PROC_NDYNAMIC)
DECL|macro|PROC_OPENPROM
mdefine_line|#define PROC_OPENPROM&t;   PROC_OPENPROM_FIRST
DECL|macro|PROC_NOPENPROM
mdefine_line|#define PROC_NOPENPROM&t;   4096
DECL|macro|PROC_OPENPROMD_FIRST
mdefine_line|#define PROC_OPENPROMD_FIRST (PROC_OPENPROM_FIRST+PROC_NOPENPROM)
DECL|macro|PROC_NOPENPROMD
mdefine_line|#define PROC_NOPENPROMD&t;   4096
DECL|macro|PROC_SUPER_MAGIC
mdefine_line|#define PROC_SUPER_MAGIC 0x9fa0
multiline_comment|/*&n; * This is not completely implemented yet. The idea is to&n; * create an in-memory tree (like the actual /proc filesystem&n; * tree) of these proc_dir_entries, so that we can dynamically&n; * add new files to /proc.&n; *&n; * The &quot;next&quot; pointer creates a linked list of one /proc directory,&n; * while parent/subdir create the directory structure (every&n; * /proc file has a parent, but &quot;subdir&quot; is NULL for all&n; * non-directory entries).&n; *&n; * &quot;get_info&quot; is called at &quot;read&quot;, while &quot;fill_inode&quot; is used to&n; * fill in file type/protection/owner information specific to the&n; * particular /proc file.&n; */
DECL|typedef|read_proc_t
r_typedef
r_int
(paren
id|read_proc_t
)paren
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|typedef|write_proc_t
r_typedef
r_int
(paren
id|write_proc_t
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|typedef|get_info_t
r_typedef
r_int
(paren
id|get_info_t
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
id|get_info_t
op_star
id|get_info
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
comma
r_int
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
DECL|member|read_proc
id|read_proc_t
op_star
id|read_proc
suffix:semicolon
DECL|member|write_proc
id|write_proc_t
op_star
id|write_proc
suffix:semicolon
DECL|member|readlink_proc
r_int
(paren
op_star
id|readlink_proc
)paren
(paren
r_struct
id|proc_dir_entry
op_star
id|de
comma
r_char
op_star
id|page
)paren
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* use count */
DECL|member|deleted
r_int
id|deleted
suffix:semicolon
multiline_comment|/* delete flag */
)brace
suffix:semicolon
macro_line|#if 0 /* FIXME! /proc/scsi is broken right now */
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
id|inode_operations
id|proc_scsi_inode_operations
suffix:semicolon
macro_line|#endif
DECL|macro|PROC_INODE_PROPER
mdefine_line|#define PROC_INODE_PROPER(inode) ((inode)-&gt;i_ino &amp; ~0xffff)
DECL|macro|PROC_INODE_OPENPROM
mdefine_line|#define PROC_INODE_OPENPROM(inode) &bslash;&n;&t;((inode-&gt;i_ino &gt;= PROC_OPENPROM_FIRST) &bslash;&n;&t;    &amp;&amp; (inode-&gt;i_ino &lt; PROC_OPENPROM_FIRST + PROC_NOPENPROM))
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_struct
id|proc_dir_entry
id|proc_root
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_root_fs
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_net
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
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
id|proc_openprom
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
id|proc_dir_entry
op_star
id|proc_mca
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_bus
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_sysvipc
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|proc_root_driver
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_root_kcore
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
id|proc_misc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|proc_pid_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_void
id|proc_pid_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_int
id|proc_pid_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
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
r_extern
r_struct
id|proc_dir_entry
op_star
id|create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
suffix:semicolon
r_extern
r_void
id|remove_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
suffix:semicolon
DECL|function|proc_scsi_register
r_extern
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
macro_line|#if 0 /* FIXME! */
id|x-&gt;ops
op_assign
op_amp
id|proc_scsi_inode_operations
suffix:semicolon
macro_line|#endif
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
r_extern
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
OL
id|PROC_SCSI_FILE
)paren
(brace
r_return
id|proc_unregister
c_func
(paren
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
multiline_comment|/*&n; * retrieve the proc_dir_entry associated with /proc/driver/$module_name&n; */
r_extern
r_inline
DECL|function|proc_driver_find
r_struct
id|proc_dir_entry
op_star
id|proc_driver_find
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|p
op_assign
id|proc_root_driver-&gt;subdir
suffix:semicolon
r_while
c_loop
(paren
id|p
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|strcmp
(paren
id|p-&gt;name
comma
id|module_name
)paren
op_eq
l_int|0
)paren
r_return
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * remove /proc/driver/$module_name, and all its contents&n; */
DECL|function|proc_driver_unregister
r_extern
r_inline
r_int
id|proc_driver_unregister
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
id|remove_proc_entry
(paren
id|module_name
comma
id|proc_root_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * create driver-specific playground directory, /proc/driver/$module_name&n; */
DECL|function|proc_driver_register
r_extern
r_inline
r_int
id|proc_driver_register
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|p
op_assign
id|create_proc_entry
(paren
id|module_name
comma
id|S_IFDIR
comma
id|proc_root_driver
)paren
suffix:semicolon
r_return
(paren
id|p
op_eq
l_int|NULL
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_extern
r_struct
id|super_block
op_star
id|proc_super_blocks
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|proc_dentry_operations
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
r_int
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
r_struct
id|dentry
op_star
id|proc_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
DECL|struct|openpromfs_dev
r_struct
id|openpromfs_dev
(brace
DECL|member|next
r_struct
id|openpromfs_dev
op_star
id|next
suffix:semicolon
DECL|member|node
id|u32
id|node
suffix:semicolon
DECL|member|inode
id|ino_t
id|inode
suffix:semicolon
DECL|member|rdev
id|kdev_t
id|rdev
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|inode_operations
op_star
id|proc_openprom_register
c_func
(paren
r_int
(paren
op_star
id|readdir
)paren
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
comma
r_struct
id|dentry
op_star
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
comma
r_void
(paren
op_star
id|use
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
comma
r_struct
id|openpromfs_dev
op_star
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|proc_openprom_deregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|proc_openprom_use
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|proc_openprom_regdev
c_func
(paren
r_struct
id|openpromfs_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_openprom_unregdev
c_func
(paren
r_struct
id|openpromfs_dev
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
id|proc_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_netdir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_openprom_inode_operations
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
macro_line|#if CONFIG_AP1000
r_extern
r_struct
id|inode_operations
id|proc_ringbuf_inode_operations
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|inode_operations
id|proc_omirr_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_ppc_htab_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|proc_sysvipc_inode_operations
suffix:semicolon
multiline_comment|/*&n; * proc_tty.c&n; */
r_extern
r_void
id|proc_tty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|proc_tty_register_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
r_extern
r_void
id|proc_tty_unregister_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
suffix:semicolon
multiline_comment|/*&n; * proc_devtree.c&n; */
r_extern
r_void
id|proc_device_tree_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|create_proc_read_entry
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|create_proc_read_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|base
comma
id|read_proc_t
op_star
id|read_proc
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|res
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|mode
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|res-&gt;read_proc
op_assign
id|read_proc
suffix:semicolon
id|res-&gt;data
op_assign
id|data
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|create_proc_info_entry
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|create_proc_info_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|base
comma
id|get_info_t
op_star
id|get_info
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|res
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|mode
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|res-&gt;get_info
op_assign
id|get_info
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|proc_net_create
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|proc_net_create
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
id|get_info_t
op_star
id|get_info
)paren
(brace
r_return
id|create_proc_info_entry
c_func
(paren
id|name
comma
id|mode
comma
id|proc_net
comma
id|get_info
)paren
suffix:semicolon
)brace
DECL|function|proc_net_remove
r_extern
r_inline
r_void
id|proc_net_remove
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|name
comma
id|proc_net
)paren
suffix:semicolon
)brace
DECL|function|proc_net_register
r_extern
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
id|proc_net
comma
id|x
)paren
suffix:semicolon
)brace
DECL|function|proc_net_unregister
r_extern
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
id|proc_net
comma
id|x
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|proc_register
r_extern
r_inline
r_int
id|proc_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|a
comma
r_struct
id|proc_dir_entry
op_star
id|b
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_unregister
r_extern
r_inline
r_int
id|proc_unregister
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|a
comma
r_int
id|b
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_net_create
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|proc_net_create
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
id|get_info_t
op_star
id|get_info
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|proc_net_remove
r_extern
r_inline
r_void
id|proc_net_remove
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
)brace
DECL|function|proc_net_register
r_extern
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
l_int|0
suffix:semicolon
)brace
DECL|function|proc_net_unregister
r_extern
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
l_int|0
suffix:semicolon
)brace
DECL|function|proc_scsi_register
r_extern
r_inline
r_int
id|proc_scsi_register
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|b
comma
r_struct
id|proc_dir_entry
op_star
id|c
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_scsi_unregister
r_extern
r_inline
r_int
id|proc_scsi_unregister
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|a
comma
r_int
id|x
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_proc_entry
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|remove_proc_entry
r_extern
r_inline
r_void
id|remove_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
)brace
suffix:semicolon
DECL|function|create_proc_read_entry
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|create_proc_read_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|base
comma
r_int
(paren
op_star
id|read_proc
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
op_star
comma
r_void
op_star
)paren
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|create_proc_info_entry
r_extern
r_inline
r_struct
id|proc_dir_entry
op_star
id|create_proc_info_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|base
comma
id|get_info_t
op_star
id|get_info
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|proc_tty_register_driver
r_extern
r_inline
r_void
id|proc_tty_register_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
(brace
)brace
suffix:semicolon
DECL|function|proc_tty_unregister_driver
r_extern
r_inline
r_void
id|proc_tty_unregister_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
(brace
)brace
suffix:semicolon
r_extern
r_inline
DECL|function|proc_driver_find
r_struct
id|proc_dir_entry
op_star
id|proc_driver_find
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|proc_driver_unregister
r_extern
r_inline
r_int
id|proc_driver_unregister
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_driver_register
r_extern
r_inline
r_int
id|proc_driver_register
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_struct
id|proc_dir_entry
id|proc_root
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#endif /* _LINUX_PROC_FS_H */
eof
