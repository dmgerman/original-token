multiline_comment|/*&n; * Venus interface for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
multiline_comment|/*&n; *&n; * Based on cfs.h from Mach, but revamped for increased simplicity.&n; * Linux modifications by Peter Braam, Aug 1996&n; */
macro_line|#ifndef _CFS_HEADER_
DECL|macro|_CFS_HEADER_
mdefine_line|#define _CFS_HEADER_
multiline_comment|/* Catch new _KERNEL defn for NetBSD */
macro_line|#ifdef __NetBSD__
macro_line|#include &lt;sys/types.h&gt;
macro_line|#ifdef _KERNEL
DECL|macro|KERNEL
mdefine_line|#define KERNEL
macro_line|#endif 
macro_line|#endif 
macro_line|#if 0
macro_line|#ifndef _SCALAR_T_
mdefine_line|#define _SCALAR_T_ 1
r_typedef
r_int
r_int
id|u_int32_t
suffix:semicolon
r_typedef
r_int
r_int
id|u_int16_t
suffix:semicolon
r_typedef
r_int
r_char
id|u_int8_t
suffix:semicolon
macro_line|#endif 
macro_line|#endif 
macro_line|#ifdef __linux__
macro_line|#ifndef _UQUAD_T_
DECL|macro|_UQUAD_T_
mdefine_line|#define _UQUAD_T_ 1
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif 
macro_line|#ifdef __KERNEL__
DECL|macro|KERNEL
mdefine_line|#define KERNEL
macro_line|#endif __KERNEL__
macro_line|#endif
multiline_comment|/*&n; * Cfs constants&n; */
DECL|macro|CFS_MAXNAMLEN
mdefine_line|#define CFS_MAXNAMLEN 256
DECL|macro|CFS_MAXPATHLEN
mdefine_line|#define CFS_MAXPATHLEN 256
DECL|macro|CODA_MAXSYMLINK
mdefine_line|#define CODA_MAXSYMLINK 10
multiline_comment|/* types used in kernel and user mode */
macro_line|#ifndef _VENUS_DIRENT_T_
DECL|macro|_VENUS_DIRENT_T_
mdefine_line|#define _VENUS_DIRENT_T_ 1
DECL|struct|venus_dirent
r_struct
id|venus_dirent
(brace
DECL|member|d_fileno
r_int
r_int
id|d_fileno
suffix:semicolon
multiline_comment|/* file number of entry */
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
multiline_comment|/* length of this record */
DECL|member|d_type
r_char
id|d_type
suffix:semicolon
multiline_comment|/* file type, see below */
DECL|member|d_namlen
r_char
id|d_namlen
suffix:semicolon
multiline_comment|/* length of string in d_name */
DECL|member|d_name
r_char
id|d_name
(braket
id|CFS_MAXNAMLEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* name must be no longer than this */
)brace
suffix:semicolon
DECL|macro|DIRSIZ
macro_line|#undef DIRSIZ
DECL|macro|DIRSIZ
mdefine_line|#define DIRSIZ(dp)      ((sizeof (struct venus_dirent) - (CFS_MAXNAMLEN+1)) + &bslash;&n;                         (((dp)-&gt;d_namlen+1 + 3) &amp;~ 3))
multiline_comment|/*&n; * File types&n; */
DECL|macro|DT_UNKNOWN
mdefine_line|#define&t;DT_UNKNOWN&t; 0
DECL|macro|DT_FIFO
mdefine_line|#define&t;DT_FIFO&t;&t; 1
DECL|macro|DT_CHR
mdefine_line|#define&t;DT_CHR&t;&t; 2
DECL|macro|DT_DIR
mdefine_line|#define&t;DT_DIR&t;&t; 4
DECL|macro|DT_BLK
mdefine_line|#define&t;DT_BLK&t;&t; 6
DECL|macro|DT_REG
mdefine_line|#define&t;DT_REG&t;&t; 8
DECL|macro|DT_LNK
mdefine_line|#define&t;DT_LNK&t;&t;10
DECL|macro|DT_SOCK
mdefine_line|#define&t;DT_SOCK&t;&t;12
DECL|macro|DT_WHT
mdefine_line|#define&t;DT_WHT&t;&t;14
multiline_comment|/*&n; * Convert between stat structure types and directory types.&n; */
DECL|macro|IFTODT
mdefine_line|#define&t;IFTODT(mode)&t;(((mode) &amp; 0170000) &gt;&gt; 12)
DECL|macro|DTTOIF
mdefine_line|#define&t;DTTOIF(dirtype)&t;((dirtype) &lt;&lt; 12)
macro_line|#endif
macro_line|#ifndef&t;_FID_T_
DECL|macro|_FID_T_
mdefine_line|#define _FID_T_&t;1
DECL|typedef|VolumeId
r_typedef
id|u_long
id|VolumeId
suffix:semicolon
DECL|typedef|VnodeId
r_typedef
id|u_long
id|VnodeId
suffix:semicolon
DECL|typedef|Unique_t
r_typedef
id|u_long
id|Unique_t
suffix:semicolon
DECL|typedef|FileVersion
r_typedef
id|u_long
id|FileVersion
suffix:semicolon
macro_line|#endif 
macro_line|#ifndef&t;_VICEFID_T_
DECL|macro|_VICEFID_T_
mdefine_line|#define _VICEFID_T_&t;1
DECL|struct|ViceFid
r_typedef
r_struct
id|ViceFid
(brace
DECL|member|Volume
id|VolumeId
id|Volume
suffix:semicolon
DECL|member|Vnode
id|VnodeId
id|Vnode
suffix:semicolon
DECL|member|Unique
id|Unique_t
id|Unique
suffix:semicolon
DECL|typedef|ViceFid
)brace
id|ViceFid
suffix:semicolon
macro_line|#endif&t;/* VICEFID */
macro_line|#ifndef _VUID_T_
DECL|macro|_VUID_T_
mdefine_line|#define _VUID_T_
DECL|typedef|vuid_t
r_typedef
id|u_long
id|vuid_t
suffix:semicolon
DECL|typedef|vgid_t
r_typedef
id|u_long
id|vgid_t
suffix:semicolon
macro_line|#endif /*_VUID_T_ */
macro_line|#ifndef _CODACRED_T_
DECL|macro|_CODACRED_T_
mdefine_line|#define _CODACRED_T_
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS 32
DECL|struct|CodaCred
r_struct
id|CodaCred
(brace
DECL|member|cr_uid
DECL|member|cr_euid
DECL|member|cr_suid
DECL|member|cr_fsuid
id|vuid_t
id|cr_uid
comma
id|cr_euid
comma
id|cr_suid
comma
id|cr_fsuid
suffix:semicolon
multiline_comment|/* Real, efftve, set, fs uid*/
DECL|member|cr_gid
DECL|member|cr_egid
DECL|member|cr_sgid
DECL|member|cr_fsgid
id|vgid_t
id|cr_gid
comma
id|cr_egid
comma
id|cr_sgid
comma
id|cr_fsgid
suffix:semicolon
multiline_comment|/* same for groups */
DECL|member|cr_groups
id|vgid_t
id|cr_groups
(braket
id|NGROUPS
)braket
suffix:semicolon
multiline_comment|/* Group membership for caller */
)brace
suffix:semicolon
macro_line|#endif 
macro_line|#ifndef _VENUS_VATTR_T_
DECL|macro|_VENUS_VATTR_T_
mdefine_line|#define _VENUS_VATTR_T_
multiline_comment|/*&n; * Vnode types.  VNON means no type.&n; */
DECL|enum|coda_vtype
DECL|enumerator|VNON
DECL|enumerator|VREG
DECL|enumerator|VDIR
DECL|enumerator|VBLK
DECL|enumerator|VCHR
DECL|enumerator|VLNK
DECL|enumerator|VSOCK
DECL|enumerator|VFIFO
DECL|enumerator|VBAD
r_enum
id|coda_vtype
(brace
id|VNON
comma
id|VREG
comma
id|VDIR
comma
id|VBLK
comma
id|VCHR
comma
id|VLNK
comma
id|VSOCK
comma
id|VFIFO
comma
id|VBAD
)brace
suffix:semicolon
DECL|struct|coda_vattr
r_struct
id|coda_vattr
(brace
DECL|member|va_type
r_enum
id|coda_vtype
id|va_type
suffix:semicolon
multiline_comment|/* vnode type (for create) */
DECL|member|va_mode
id|u_short
id|va_mode
suffix:semicolon
multiline_comment|/* files access mode and type */
DECL|member|va_nlink
r_int
id|va_nlink
suffix:semicolon
multiline_comment|/* number of references to file */
DECL|member|va_uid
id|vuid_t
id|va_uid
suffix:semicolon
multiline_comment|/* owner user id */
DECL|member|va_gid
id|vgid_t
id|va_gid
suffix:semicolon
multiline_comment|/* owner group id */
DECL|member|va_fsid
r_int
id|va_fsid
suffix:semicolon
multiline_comment|/* file system id (dev for now) */
DECL|member|va_fileid
r_int
id|va_fileid
suffix:semicolon
multiline_comment|/* file id */
DECL|member|va_size
id|u_quad_t
id|va_size
suffix:semicolon
multiline_comment|/* file size in bytes */
DECL|member|va_blocksize
r_int
id|va_blocksize
suffix:semicolon
multiline_comment|/* blocksize preferred for i/o */
DECL|member|va_atime
r_struct
id|timespec
id|va_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|va_mtime
r_struct
id|timespec
id|va_mtime
suffix:semicolon
multiline_comment|/* time of last modification */
DECL|member|va_ctime
r_struct
id|timespec
id|va_ctime
suffix:semicolon
multiline_comment|/* time file changed */
DECL|member|va_gen
id|u_long
id|va_gen
suffix:semicolon
multiline_comment|/* generation number of file */
DECL|member|va_flags
id|u_long
id|va_flags
suffix:semicolon
multiline_comment|/* flags defined for file */
DECL|member|va_rdev
id|dev_t
id|va_rdev
suffix:semicolon
multiline_comment|/* device the special file represents */
DECL|member|va_bytes
id|u_quad_t
id|va_bytes
suffix:semicolon
multiline_comment|/* bytes of disk space held by file */
DECL|member|va_filerev
id|u_quad_t
id|va_filerev
suffix:semicolon
multiline_comment|/* file modification number */
DECL|member|va_vaflags
id|u_int
id|va_vaflags
suffix:semicolon
multiline_comment|/* operations flags, see below */
DECL|member|va_spare
r_int
id|va_spare
suffix:semicolon
multiline_comment|/* remain quad aligned */
)brace
suffix:semicolon
DECL|macro|VREAD
mdefine_line|#define VREAD 00400
DECL|macro|VWRITE
mdefine_line|#define VWRITE 00200
macro_line|#endif 
multiline_comment|/*&n; * opcode constants&n; */
DECL|macro|CFS_ROOT
mdefine_line|#define CFS_ROOT&t;((u_long) 2)
DECL|macro|CFS_SYNC
mdefine_line|#define CFS_SYNC&t;((u_long) 3)
DECL|macro|CFS_OPEN
mdefine_line|#define CFS_OPEN&t;((u_long) 4)
DECL|macro|CFS_CLOSE
mdefine_line|#define CFS_CLOSE&t;((u_long) 5)
DECL|macro|CFS_IOCTL
mdefine_line|#define CFS_IOCTL&t;((u_long) 6)
DECL|macro|CFS_GETATTR
mdefine_line|#define CFS_GETATTR&t;((u_long) 7)
DECL|macro|CFS_SETATTR
mdefine_line|#define CFS_SETATTR&t;((u_long) 8)
DECL|macro|CFS_ACCESS
mdefine_line|#define CFS_ACCESS&t;((u_long) 9)
DECL|macro|CFS_LOOKUP
mdefine_line|#define CFS_LOOKUP&t;((u_long) 10)
DECL|macro|CFS_CREATE
mdefine_line|#define CFS_CREATE&t;((u_long) 11)
DECL|macro|CFS_REMOVE
mdefine_line|#define CFS_REMOVE&t;((u_long) 12)
DECL|macro|CFS_LINK
mdefine_line|#define CFS_LINK&t;((u_long) 13)
DECL|macro|CFS_RENAME
mdefine_line|#define CFS_RENAME&t;((u_long) 14)
DECL|macro|CFS_MKDIR
mdefine_line|#define CFS_MKDIR&t;((u_long) 15)
DECL|macro|CFS_RMDIR
mdefine_line|#define CFS_RMDIR&t;((u_long) 16)
DECL|macro|CFS_READDIR
mdefine_line|#define CFS_READDIR&t;((u_long) 17)
DECL|macro|CFS_SYMLINK
mdefine_line|#define CFS_SYMLINK&t;((u_long) 18)
DECL|macro|CFS_READLINK
mdefine_line|#define CFS_READLINK&t;((u_long) 19)
DECL|macro|CFS_FSYNC
mdefine_line|#define CFS_FSYNC&t;((u_long) 20)
DECL|macro|CFS_INACTIVE
mdefine_line|#define CFS_INACTIVE&t;((u_long) 21)
DECL|macro|CFS_VGET
mdefine_line|#define&t;CFS_VGET&t;((u_long) 22)
DECL|macro|CFS_SIGNAL
mdefine_line|#define&t;CFS_SIGNAL&t;((u_long) 23)
DECL|macro|CFS_REPLACE
mdefine_line|#define CFS_REPLACE&t;((u_long) 24)
DECL|macro|CFS_FLUSH
mdefine_line|#define CFS_FLUSH       ((u_long) 25)
DECL|macro|CFS_PURGEUSER
mdefine_line|#define CFS_PURGEUSER   ((u_long) 26)
DECL|macro|CFS_ZAPFILE
mdefine_line|#define CFS_ZAPFILE     ((u_long) 27)
DECL|macro|CFS_ZAPDIR
mdefine_line|#define CFS_ZAPDIR      ((u_long) 28)
DECL|macro|CFS_ZAPVNODE
mdefine_line|#define CFS_ZAPVNODE    ((u_long) 29)
DECL|macro|CFS_PURGEFID
mdefine_line|#define CFS_PURGEFID    ((u_long) 30)
DECL|macro|CFS_RDWR
mdefine_line|#define&t;CFS_RDWR&t;((u_long) 31)
DECL|macro|ODY_MOUNT
mdefine_line|#define ODY_MOUNT&t;((u_long) 32) 
DECL|macro|ODY_LOOKUP
mdefine_line|#define ODY_LOOKUP&t;((u_long) 33)
DECL|macro|ODY_EXPAND
mdefine_line|#define ODY_EXPAND&t;((u_long) 34)
DECL|macro|CFS_NCALLS
mdefine_line|#define CFS_NCALLS 35
DECL|macro|DOWNCALL
mdefine_line|#define DOWNCALL(opcode) (opcode &gt;= CFS_REPLACE &amp;&amp; opcode &lt;= CFS_PURGEFID)
multiline_comment|/*&n; *        Venus &lt;-&gt; Coda  RPC arguments&n; */
DECL|struct|inputArgs
r_struct
id|inputArgs
(brace
DECL|member|opcode
id|u_long
id|opcode
suffix:semicolon
DECL|member|unique
id|u_long
id|unique
suffix:semicolon
multiline_comment|/* Keep multiple outstanding msgs distinct */
DECL|member|pid
id|u_short
id|pid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|pgid
id|u_short
id|pgid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|cred
r_struct
id|CodaCred
id|cred
suffix:semicolon
multiline_comment|/* Common to all */
r_union
(brace
multiline_comment|/* Nothing needed for cfs_root */
multiline_comment|/* Nothing needed for cfs_sync */
DECL|struct|cfs_open_in
r_struct
id|cfs_open_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|cfs_open
)brace
id|cfs_open
suffix:semicolon
DECL|struct|cfs_close_in
r_struct
id|cfs_close_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|cfs_close
)brace
id|cfs_close
suffix:semicolon
DECL|struct|cfs_ioctl_in
r_struct
id|cfs_ioctl_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|rwflag
r_int
id|rwflag
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_ioctl
)brace
id|cfs_ioctl
suffix:semicolon
DECL|struct|cfs_getattr_in
r_struct
id|cfs_getattr_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|cfs_getattr
)brace
id|cfs_getattr
suffix:semicolon
DECL|struct|cfs_setattr_in
r_struct
id|cfs_setattr_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|cfs_setattr
)brace
id|cfs_setattr
suffix:semicolon
DECL|struct|cfs_access_in
r_struct
id|cfs_access_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|cfs_access
)brace
id|cfs_access
suffix:semicolon
DECL|struct|cfs_lookup_in
r_struct
id|cfs_lookup_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_lookup
)brace
id|cfs_lookup
suffix:semicolon
DECL|struct|cfs_create_in
r_struct
id|cfs_create_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|excl
r_int
id|excl
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_create
)brace
id|cfs_create
suffix:semicolon
DECL|struct|cfs_remove_in
r_struct
id|cfs_remove_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_remove
)brace
id|cfs_remove
suffix:semicolon
DECL|struct|cfs_link_in
r_struct
id|cfs_link_in
(brace
DECL|member|sourceFid
id|ViceFid
id|sourceFid
suffix:semicolon
multiline_comment|/* cnode to link *to* */
DECL|member|destFid
id|ViceFid
id|destFid
suffix:semicolon
multiline_comment|/* Directory in which to place link */
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_link
)brace
id|cfs_link
suffix:semicolon
DECL|struct|cfs_rename_in
r_struct
id|cfs_rename_in
(brace
DECL|member|sourceFid
id|ViceFid
id|sourceFid
suffix:semicolon
DECL|member|srcname
r_char
op_star
id|srcname
suffix:semicolon
DECL|member|destFid
id|ViceFid
id|destFid
suffix:semicolon
DECL|member|destname
r_char
op_star
id|destname
suffix:semicolon
DECL|member|cfs_rename
)brace
id|cfs_rename
suffix:semicolon
DECL|struct|cfs_mkdir_in
r_struct
id|cfs_mkdir_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_mkdir
)brace
id|cfs_mkdir
suffix:semicolon
DECL|struct|cfs_rmdir_in
r_struct
id|cfs_rmdir_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_rmdir
)brace
id|cfs_rmdir
suffix:semicolon
DECL|struct|cfs_readdir_in
r_struct
id|cfs_readdir_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|cfs_readdir
)brace
id|cfs_readdir
suffix:semicolon
DECL|struct|cfs_symlink_in
r_struct
id|cfs_symlink_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
multiline_comment|/* Directory to put symlink in */
DECL|member|srcname
r_char
op_star
id|srcname
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
DECL|member|cfs_symlink
)brace
id|cfs_symlink
suffix:semicolon
DECL|struct|cfs_readlink_in
r_struct
id|cfs_readlink_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_readlink
)brace
id|cfs_readlink
suffix:semicolon
DECL|struct|cfs_fsync_in
r_struct
id|cfs_fsync_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_fsync
)brace
id|cfs_fsync
suffix:semicolon
DECL|struct|cfs_inactive_in
r_struct
id|cfs_inactive_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_inactive
)brace
id|cfs_inactive
suffix:semicolon
DECL|struct|cfs_vget_in
r_struct
id|cfs_vget_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_vget
)brace
id|cfs_vget
suffix:semicolon
multiline_comment|/* CFS_SIGNAL is out-of-band, doesn&squot;t need data. */
multiline_comment|/* CFS_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CFS_FLUSH is a venus-&gt;kernel call */
multiline_comment|/* CFS_PURGEUSER is a venus-&gt;kernel call */
multiline_comment|/* CFS_ZAPFILE is a venus-&gt;kernel call */
multiline_comment|/* CFS_ZAPDIR is a venus-&gt;kernel call */
multiline_comment|/* CFS_ZAPVNODE is a venus-&gt;kernel call */
multiline_comment|/* CFS_PURGEFID is a venus-&gt;kernel call */
DECL|struct|cfs_rdwr_in
r_struct
id|cfs_rdwr_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|rwflag
r_int
id|rwflag
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|ioflag
r_int
id|ioflag
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_rdwr
)brace
id|cfs_rdwr
suffix:semicolon
DECL|struct|ody_mount_in
r_struct
id|ody_mount_in
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|ody_mount
)brace
id|ody_mount
suffix:semicolon
DECL|struct|ody_lookup_in
r_struct
id|ody_lookup_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|ody_lookup
)brace
id|ody_lookup
suffix:semicolon
DECL|struct|ody_expand_in
r_struct
id|ody_expand_in
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of buffer to return. */
DECL|member|ody_expand
)brace
id|ody_expand
suffix:semicolon
multiline_comment|/* CFS_REPLACE is a venus-&gt;kernel call */
DECL|member|d
)brace
id|d
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Occasionally, don&squot;t cache the fid returned by CFS_LOOKUP. For&n; * instance, if the fid is inconsistent. This case is handled by&n; * setting the top bit of the return result parameter.  */
DECL|macro|CFS_NOCACHE
mdefine_line|#define CFS_NOCACHE          0x80000000
DECL|macro|INIT_OUT
mdefine_line|#define INIT_OUT(out, opcode, result) &bslash;&n;    out-&gt;opcode = (opcode); out-&gt;result = (result);
multiline_comment|/*  IMPORTANT: opcode and unique must be first two fields! */
DECL|struct|outputArgs
r_struct
id|outputArgs
(brace
DECL|member|opcode
id|u_long
id|opcode
suffix:semicolon
DECL|member|unique
id|u_long
id|unique
suffix:semicolon
multiline_comment|/* Keep multiple outstanding msgs distinct */
DECL|member|result
id|u_long
id|result
suffix:semicolon
r_union
(brace
DECL|struct|cfs_root_out
r_struct
id|cfs_root_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_root
)brace
id|cfs_root
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_sync */
DECL|struct|cfs_open_out
r_struct
id|cfs_open_out
(brace
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|inode
id|ino_t
id|inode
suffix:semicolon
DECL|member|cfs_open
)brace
id|cfs_open
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_close */
DECL|struct|cfs_ioctl_out
r_struct
id|cfs_ioctl_out
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_ioctl
)brace
id|cfs_ioctl
suffix:semicolon
DECL|struct|cfs_getattr_out
r_struct
id|cfs_getattr_out
(brace
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|cfs_getattr
)brace
id|cfs_getattr
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_setattr */
multiline_comment|/* Nothing needed for cfs_access */
DECL|struct|cfs_lookup_out
r_struct
id|cfs_lookup_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
DECL|member|cfs_lookup
)brace
id|cfs_lookup
suffix:semicolon
DECL|struct|cfs_create_out
r_struct
id|cfs_create_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|cfs_create
)brace
id|cfs_create
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_remove */
multiline_comment|/* Nothing needed for cfs_link */
multiline_comment|/* Nothing needed for cfs_rename */
DECL|struct|cfs_mkdir_out
r_struct
id|cfs_mkdir_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|cfs_mkdir
)brace
id|cfs_mkdir
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_rmdir */
DECL|struct|cfs_readdir_out
r_struct
id|cfs_readdir_out
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_readdir
)brace
id|cfs_readdir
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_symlink */
DECL|struct|cfs_readlink_out
r_struct
id|cfs_readlink_out
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_readlink
)brace
id|cfs_readlink
suffix:semicolon
multiline_comment|/* Nothing needed for cfs_fsync */
multiline_comment|/* Nothing needed for cfs_inactive */
DECL|struct|cfs_vget_out
r_struct
id|cfs_vget_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
DECL|member|cfs_vget
)brace
id|cfs_vget
suffix:semicolon
multiline_comment|/* CFS_SIGNAL is out-of-band, doesn&squot;t need data. */
multiline_comment|/* CFS_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CFS_FLUSH is a venus-&gt;kernel call */
DECL|struct|cfs_purgeuser_out
r_struct
id|cfs_purgeuser_out
(brace
multiline_comment|/* CFS_PURGEUSER is a venus-&gt;kernel call */
DECL|member|cred
r_struct
id|CodaCred
id|cred
suffix:semicolon
DECL|member|cfs_purgeuser
)brace
id|cfs_purgeuser
suffix:semicolon
DECL|struct|cfs_zapfile_out
r_struct
id|cfs_zapfile_out
(brace
multiline_comment|/* CFS_ZAPFILE is a venus-&gt;kernel call */
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
DECL|member|cfs_zapfile
)brace
id|cfs_zapfile
suffix:semicolon
DECL|struct|cfs_zapdir_out
r_struct
id|cfs_zapdir_out
(brace
multiline_comment|/* CFS_ZAPDIR is a venus-&gt;kernel call */
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
DECL|member|cfs_zapdir
)brace
id|cfs_zapdir
suffix:semicolon
DECL|struct|cfs_zapvnode_out
r_struct
id|cfs_zapvnode_out
(brace
multiline_comment|/* CFS_ZAPVNODE is a venus-&gt;kernel call */
DECL|member|cred
r_struct
id|CodaCred
id|cred
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|cfs_zapvnode
)brace
id|cfs_zapvnode
suffix:semicolon
DECL|struct|cfs_purgefid_out
r_struct
id|cfs_purgefid_out
(brace
multiline_comment|/* CFS_PURGEFID is a venus-&gt;kernel call */
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
DECL|member|cfs_purgefid
)brace
id|cfs_purgefid
suffix:semicolon
DECL|struct|cfs_rdwr_out
r_struct
id|cfs_rdwr_out
(brace
DECL|member|rwflag
r_int
id|rwflag
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|cfs_rdwr
)brace
id|cfs_rdwr
suffix:semicolon
DECL|struct|ody_mount_out
r_struct
id|ody_mount_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|ody_mount
)brace
id|ody_mount
suffix:semicolon
DECL|struct|ody_lookup_out
r_struct
id|ody_lookup_out
(brace
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|ody_lookup
)brace
id|ody_lookup
suffix:semicolon
DECL|struct|ody_expand_out
r_struct
id|ody_expand_out
(brace
multiline_comment|/* Eventually it would be nice to get some */
DECL|member|links
r_char
id|links
(braket
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
multiline_comment|/* Place holder for data. */
DECL|member|ody_expand
)brace
id|ody_expand
suffix:semicolon
DECL|struct|cfs_replace_out
r_struct
id|cfs_replace_out
(brace
multiline_comment|/* cfs_replace is a venus-&gt;kernel call */
DECL|member|NewFid
id|ViceFid
id|NewFid
suffix:semicolon
DECL|member|OldFid
id|ViceFid
id|OldFid
suffix:semicolon
DECL|member|cfs_replace
)brace
id|cfs_replace
suffix:semicolon
DECL|member|d
)brace
id|d
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * how big are the inputArgs and outputArgs structures&n; * for the varying types of calls?&n; */
DECL|macro|VC_IN_NO_DATA
mdefine_line|#define&t;VC_IN_NO_DATA&t;    (2 * (int)sizeof(u_long)    &bslash;&n;                             + 2 * (int)sizeof(u_short) &bslash;&n;&t;&t;&t;     + (int)sizeof(struct CodaCred))
DECL|macro|VC_OUT_NO_DATA
mdefine_line|#define&t;VC_OUT_NO_DATA&t;    (3 * (int)sizeof(u_long))
DECL|macro|VC_INSIZE
mdefine_line|#define VC_INSIZE(member)   (VC_IN_NO_DATA + (int)sizeof(struct member))
DECL|macro|VC_OUTSIZE
mdefine_line|#define VC_OUTSIZE(member)  (VC_OUT_NO_DATA + (int)sizeof(struct member))
multiline_comment|/* Now for venus. C++ doesn&squot;t know what struct foo means. */
DECL|macro|VC_SIZE
mdefine_line|#define VC_SIZE(Thing, Member)   (VC_OUT_NO_DATA                    &bslash;&n;                                  + (int)sizeof((Thing)-&gt;d.Member))
DECL|macro|VC_BIGGER_OF_IN_OR_OUT
mdefine_line|#define VC_BIGGER_OF_IN_OR_OUT  (sizeof(struct outputArgs)   &bslash;&n;                                  &gt; sizeof(struct inputArgs) &bslash;&n;                                ? sizeof(struct outputArgs)  &bslash;&n;                                : sizeof(struct inputArgs))
DECL|macro|VC_DATASIZE
mdefine_line|#define VC_DATASIZE&t;    8192
DECL|macro|VC_MAXMSGSIZE
mdefine_line|#define&t;VC_MAXMSGSIZE&t;    (VC_DATASIZE + VC_BIGGER_OF_IN_OR_OUT)
multiline_comment|/*&n; * Used for identifying usage of &quot;Control&quot; and pioctls&n; */
DECL|struct|ViceIoctl
r_struct
id|ViceIoctl
(brace
DECL|member|in
DECL|member|out
id|caddr_t
id|in
comma
id|out
suffix:semicolon
multiline_comment|/* Data to be transferred in, or out */
DECL|member|in_size
r_int
id|in_size
suffix:semicolon
multiline_comment|/* Size of input buffer &lt;= 2K */
DECL|member|out_size
r_int
id|out_size
suffix:semicolon
multiline_comment|/* Maximum size of output buffer, &lt;= 2K */
)brace
suffix:semicolon
DECL|struct|PioctlData
r_struct
id|PioctlData
(brace
DECL|member|path
r_const
r_char
op_star
id|path
suffix:semicolon
DECL|member|follow
r_int
id|follow
suffix:semicolon
DECL|member|vi
r_struct
id|ViceIoctl
id|vi
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CFS_CONTROL
mdefine_line|#define&t;CFS_CONTROL&t;&t;&quot;.CONTROL&quot;
DECL|macro|CFS_CONTROLLEN
mdefine_line|#define CFS_CONTROLLEN           8
DECL|macro|CTL_VOL
mdefine_line|#define&t;CTL_VOL&t;&t;&t;-1
DECL|macro|CTL_VNO
mdefine_line|#define&t;CTL_VNO&t;&t;&t;-1
DECL|macro|CTL_UNI
mdefine_line|#define&t;CTL_UNI&t;&t;&t;-1
DECL|macro|CTL_INO
mdefine_line|#define CTL_INO                 -1
DECL|macro|CTL_FILE
mdefine_line|#define&t;CTL_FILE    &quot;/coda/.CONTROL&quot;
DECL|macro|IOCPARM_MASK
mdefine_line|#define IOCPARM_MASK 0x0000ffff
DECL|macro|IS_CTL_FID
mdefine_line|#define&t;IS_CTL_FID(fidp)&t;((fidp)-&gt;Volume == CTL_VOL &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Vnode == CTL_VNO &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Unique == CTL_UNI)
multiline_comment|/*#define&t;ISDIR(fid)&t;&t;((fid).Vnode &amp; 0x1) */
macro_line|#endif 
eof
