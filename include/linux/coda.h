multiline_comment|/*&n; *&n; * Based on cfs.h from Mach, but revamped for increased simplicity.&n; * Linux modifications by Peter Braam, Aug 1996&n; */
macro_line|#ifndef _CFS_HEADER_
DECL|macro|_CFS_HEADER_
mdefine_line|#define _CFS_HEADER_
multiline_comment|/* Catch new _KERNEL defn for NetBSD */
macro_line|#ifdef __NetBSD__
macro_line|#include &lt;sys/types.h&gt;
macro_line|#endif 
macro_line|#ifdef DJGPP
macro_line|#ifdef KERNEL
DECL|typedef|u_long
r_typedef
r_int
r_int
id|u_long
suffix:semicolon
DECL|typedef|u_int
r_typedef
r_int
r_int
id|u_int
suffix:semicolon
DECL|typedef|u_short
r_typedef
r_int
r_int
id|u_short
suffix:semicolon
DECL|typedef|ino_t
r_typedef
id|u_long
id|ino_t
suffix:semicolon
DECL|typedef|dev_t
r_typedef
id|u_long
id|dev_t
suffix:semicolon
DECL|typedef|caddr_t
r_typedef
r_void
op_star
id|caddr_t
suffix:semicolon
DECL|typedef|u_quad_t
r_typedef
id|u_long
id|u_quad_t
suffix:semicolon
DECL|macro|inline
mdefine_line|#define inline
DECL|struct|timespec
r_struct
id|timespec
(brace
DECL|member|ts_sec
r_int
id|ts_sec
suffix:semicolon
DECL|member|ts_nsec
r_int
id|ts_nsec
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else  /* DJGPP but not KERNEL */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/time.h&gt;
DECL|typedef|u_quad_t
r_typedef
id|u_long
id|u_quad_t
suffix:semicolon
macro_line|#endif /* !KERNEL */
macro_line|#endif /* !DJGPP */
macro_line|#if defined(__linux__) || defined(__CYGWIN32__)
DECL|macro|cdev_t
mdefine_line|#define cdev_t u_quad_t
macro_line|#if !defined(_UQUAD_T_) &amp;&amp; (!defined(__GLIBC__) || __GLIBC__ &lt; 2)
DECL|macro|_UQUAD_T_
mdefine_line|#define _UQUAD_T_ 1
DECL|typedef|u_quad_t
r_typedef
r_int
r_int
r_int
id|u_quad_t
suffix:semicolon
macro_line|#endif
macro_line|#else
DECL|macro|cdev_t
mdefine_line|#define cdev_t dev_t
macro_line|#endif
macro_line|#ifdef __CYGWIN32__
DECL|typedef|u_int8_t
r_typedef
r_int
r_char
id|u_int8_t
suffix:semicolon
DECL|struct|timespec
r_struct
id|timespec
(brace
DECL|member|tv_sec
id|time_t
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_nsec
r_int
id|tv_nsec
suffix:semicolon
multiline_comment|/* nanoseconds */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Cfs constants&n; */
DECL|macro|CFS_MAXNAMLEN
mdefine_line|#define CFS_MAXNAMLEN   255
DECL|macro|CFS_MAXPATHLEN
mdefine_line|#define CFS_MAXPATHLEN  1024
DECL|macro|CFS_MAXSYMLINK
mdefine_line|#define CFS_MAXSYMLINK  10
multiline_comment|/* these are Coda&squot;s version of O_RDONLY etc combinations&n; * to deal with VFS open modes&n; */
DECL|macro|C_O_READ
mdefine_line|#define&t;C_O_READ&t;0x001
DECL|macro|C_O_WRITE
mdefine_line|#define&t;C_O_WRITE       0x002
DECL|macro|C_O_TRUNC
mdefine_line|#define C_O_TRUNC       0x010
DECL|macro|C_O_EXCL
mdefine_line|#define C_O_EXCL&t;0x100
multiline_comment|/* these are to find mode bits in Venus */
DECL|macro|C_M_READ
mdefine_line|#define C_M_READ  00400
DECL|macro|C_M_WRITE
mdefine_line|#define C_M_WRITE 00200
multiline_comment|/* for access Venus will use */
DECL|macro|C_A_R_OK
mdefine_line|#define C_A_R_OK    4               /* Test for read permission.  */
DECL|macro|C_A_W_OK
mdefine_line|#define C_A_W_OK    2               /* Test for write permission.  */
DECL|macro|C_A_X_OK
mdefine_line|#define C_A_X_OK    1               /* Test for execute permission.  */
DECL|macro|C_A_F_OK
mdefine_line|#define C_A_F_OK    0               /* Test for existence.  */
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
DECL|macro|CDT_UNKNOWN
mdefine_line|#define&t;CDT_UNKNOWN&t; 0
DECL|macro|CDT_FIFO
mdefine_line|#define&t;CDT_FIFO&t;&t; 1
DECL|macro|CDT_CHR
mdefine_line|#define&t;CDT_CHR&t;&t; 2
DECL|macro|CDT_DIR
mdefine_line|#define&t;CDT_DIR&t;&t; 4
DECL|macro|CDT_BLK
mdefine_line|#define&t;CDT_BLK&t;&t; 6
DECL|macro|CDT_REG
mdefine_line|#define&t;CDT_REG&t;&t; 8
DECL|macro|CDT_LNK
mdefine_line|#define&t;CDT_LNK&t;&t;10
DECL|macro|CDT_SOCK
mdefine_line|#define&t;CDT_SOCK&t;&t;12
DECL|macro|CDT_WHT
mdefine_line|#define&t;CDT_WHT&t;&t;14
multiline_comment|/*&n; * Convert between stat structure types and directory types.&n; */
DECL|macro|IFTOCDT
mdefine_line|#define&t;IFTOCDT(mode)&t;(((mode) &amp; 0170000) &gt;&gt; 12)
DECL|macro|CDTTOIF
mdefine_line|#define&t;CDTTOIF(dirtype)&t;((dirtype) &lt;&lt; 12)
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
DECL|function|coda_f2i
r_static
r_inline
id|ino_t
id|coda_f2i
c_func
(paren
r_struct
id|ViceFid
op_star
id|fid
)paren
(brace
r_if
c_cond
(paren
id|fid
)paren
(brace
r_return
(paren
id|fid-&gt;Unique
op_plus
(paren
id|fid-&gt;Vnode
op_lshift
l_int|10
)paren
op_plus
(paren
id|fid-&gt;Volume
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
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
DECL|struct|coda_cred
r_struct
id|coda_cred
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
macro_line|#if&t;defined(__NetBSD__) || defined(__FreeBSD__)
DECL|member|cr_groupid
DECL|member|cr_egid
DECL|member|cr_sgid
DECL|member|cr_fsgid
id|vgid_t
id|cr_groupid
comma
id|cr_egid
comma
id|cr_sgid
comma
id|cr_fsgid
suffix:semicolon
multiline_comment|/* same for groups */
macro_line|#else
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
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif 
macro_line|#ifndef _VENUS_VATTR_T_
DECL|macro|_VENUS_VATTR_T_
mdefine_line|#define _VENUS_VATTR_T_
multiline_comment|/*&n; * Vnode types.  VNON means no type.&n; */
DECL|enum|coda_vtype
DECL|enumerator|C_VNON
DECL|enumerator|C_VREG
DECL|enumerator|C_VDIR
DECL|enumerator|C_VBLK
DECL|enumerator|C_VCHR
DECL|enumerator|C_VLNK
DECL|enumerator|C_VSOCK
DECL|enumerator|C_VFIFO
DECL|enumerator|C_VBAD
r_enum
id|coda_vtype
(brace
id|C_VNON
comma
id|C_VREG
comma
id|C_VDIR
comma
id|C_VBLK
comma
id|C_VCHR
comma
id|C_VLNK
comma
id|C_VSOCK
comma
id|C_VFIFO
comma
id|C_VBAD
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
id|cdev_t
id|va_rdev
suffix:semicolon
multiline_comment|/* device special file represents */
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
)brace
suffix:semicolon
macro_line|#endif 
multiline_comment|/*&n; * Kernel &lt;--&gt; Venus communications.&n; */
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
mdefine_line|#define CFS_VGET&t;((u_long) 22)
DECL|macro|CFS_SIGNAL
mdefine_line|#define CFS_SIGNAL&t;((u_long) 23)
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
DECL|macro|CFS_OPEN_BY_PATH
mdefine_line|#define CFS_OPEN_BY_PATH ((u_long) 31)
DECL|macro|CFS_NCALLS
mdefine_line|#define CFS_NCALLS 32
DECL|macro|DOWNCALL
mdefine_line|#define DOWNCALL(opcode) (opcode &gt;= CFS_REPLACE &amp;&amp; opcode &lt;= CFS_PURGEFID)
DECL|macro|VC_MAXDATASIZE
mdefine_line|#define VC_MAXDATASIZE&t;    8192
DECL|macro|VC_MAXMSGSIZE
mdefine_line|#define VC_MAXMSGSIZE      sizeof(union inputArgs)+sizeof(union outputArgs) +&bslash;&n;                            VC_MAXDATASIZE  
multiline_comment|/*&n; *        Venus &lt;-&gt; Coda  RPC arguments&n; */
DECL|struct|cfs_in_hdr
r_struct
id|cfs_in_hdr
(brace
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
DECL|member|unique
r_int
r_int
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
DECL|member|sid
id|u_short
id|sid
suffix:semicolon
multiline_comment|/* Common to all */
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
multiline_comment|/* Common to all */
)brace
suffix:semicolon
multiline_comment|/* Really important that opcode and unique are 1st two fields! */
DECL|struct|cfs_out_hdr
r_struct
id|cfs_out_hdr
(brace
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|result
r_int
r_int
id|result
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_root: NO_IN */
DECL|struct|cfs_root_out
r_struct
id|cfs_root_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_root_in
r_struct
id|cfs_root_in
(brace
DECL|member|in
r_struct
id|cfs_in_hdr
id|in
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_sync: */
multiline_comment|/* Nothing needed for cfs_sync */
multiline_comment|/* cfs_open: */
DECL|struct|cfs_open_in
r_struct
id|cfs_open_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_open_out
r_struct
id|cfs_open_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|dev
id|cdev_t
id|dev
suffix:semicolon
DECL|member|inode
id|ino_t
id|inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_close: */
DECL|struct|cfs_close_in
r_struct
id|cfs_close_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_close_out
r_struct
id|cfs_close_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_ioctl: */
DECL|struct|cfs_ioctl_in
r_struct
id|cfs_ioctl_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|cfs_ioctl_out
r_struct
id|cfs_ioctl_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
multiline_comment|/* cfs_getattr: */
DECL|struct|cfs_getattr_in
r_struct
id|cfs_getattr_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_getattr_out
r_struct
id|cfs_getattr_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_setattr: NO_OUT */
DECL|struct|cfs_setattr_in
r_struct
id|cfs_setattr_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_setattr_out
r_struct
id|cfs_setattr_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_access: NO_OUT */
DECL|struct|cfs_access_in
r_struct
id|cfs_access_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_access_out
r_struct
id|cfs_access_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_lookup: */
DECL|struct|cfs_lookup_in
r_struct
id|cfs_lookup_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_lookup_out
r_struct
id|cfs_lookup_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_create: */
DECL|struct|cfs_create_in
r_struct
id|cfs_create_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_create_out
r_struct
id|cfs_create_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_remove: NO_OUT */
DECL|struct|cfs_remove_in
r_struct
id|cfs_remove_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_remove_out
r_struct
id|cfs_remove_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_link: NO_OUT */
DECL|struct|cfs_link_in
r_struct
id|cfs_link_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
r_int
id|tname
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_link_out
r_struct
id|cfs_link_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_rename: NO_OUT */
DECL|struct|cfs_rename_in
r_struct
id|cfs_rename_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|sourceFid
id|ViceFid
id|sourceFid
suffix:semicolon
DECL|member|srcname
r_int
id|srcname
suffix:semicolon
DECL|member|destFid
id|ViceFid
id|destFid
suffix:semicolon
DECL|member|destname
r_int
id|destname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_rename_out
r_struct
id|cfs_rename_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_mkdir: */
DECL|struct|cfs_mkdir_in
r_struct
id|cfs_mkdir_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_mkdir_out
r_struct
id|cfs_mkdir_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_rmdir: NO_OUT */
DECL|struct|cfs_rmdir_in
r_struct
id|cfs_rmdir_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|name
r_int
id|name
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
DECL|struct|cfs_rmdir_out
r_struct
id|cfs_rmdir_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_readdir: */
DECL|struct|cfs_readdir_in
r_struct
id|cfs_readdir_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|cfs_readdir_out
r_struct
id|cfs_readdir_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|data
id|caddr_t
id|data
suffix:semicolon
multiline_comment|/* Place holder for data. */
)brace
suffix:semicolon
multiline_comment|/* cfs_symlink: NO_OUT */
DECL|struct|cfs_symlink_in
r_struct
id|cfs_symlink_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
multiline_comment|/* Directory to put symlink in */
DECL|member|srcname
r_int
id|srcname
suffix:semicolon
DECL|member|attr
r_struct
id|coda_vattr
id|attr
suffix:semicolon
DECL|member|tname
r_int
id|tname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_symlink_out
r_struct
id|cfs_symlink_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_readlink: */
DECL|struct|cfs_readlink_in
r_struct
id|cfs_readlink_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_readlink_out
r_struct
id|cfs_readlink_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
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
)brace
suffix:semicolon
multiline_comment|/* cfs_fsync: NO_OUT */
DECL|struct|cfs_fsync_in
r_struct
id|cfs_fsync_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_fsync_out
r_struct
id|cfs_fsync_out
(brace
DECL|member|out
r_struct
id|cfs_out_hdr
id|out
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_inactive: NO_OUT */
DECL|struct|cfs_inactive_in
r_struct
id|cfs_inactive_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_vget: */
DECL|struct|cfs_vget_in
r_struct
id|cfs_vget_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_vget_out
r_struct
id|cfs_vget_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|vtype
r_int
id|vtype
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CFS_SIGNAL is out-of-band, doesn&squot;t need data. */
multiline_comment|/* CFS_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CFS_FLUSH is a venus-&gt;kernel call */
multiline_comment|/* cfs_purgeuser: */
multiline_comment|/* CFS_PURGEUSER is a venus-&gt;kernel call */
DECL|struct|cfs_purgeuser_out
r_struct
id|cfs_purgeuser_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_zapfile: */
multiline_comment|/* CFS_ZAPFILE is a venus-&gt;kernel call */
DECL|struct|cfs_zapfile_out
r_struct
id|cfs_zapfile_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_zapdir: */
multiline_comment|/* CFS_ZAPDIR is a venus-&gt;kernel call */
DECL|struct|cfs_zapdir_out
r_struct
id|cfs_zapdir_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_zapnode: */
multiline_comment|/* CFS_ZAPVNODE is a venus-&gt;kernel call */
DECL|struct|cfs_zapvnode_out
r_struct
id|cfs_zapvnode_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|cred
r_struct
id|coda_cred
id|cred
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_purgefid: */
multiline_comment|/* CFS_PURGEFID is a venus-&gt;kernel call */
DECL|struct|cfs_purgefid_out
r_struct
id|cfs_purgefid_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|CodaFid
id|ViceFid
id|CodaFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_rdwr: */
DECL|struct|cfs_rdwr_in
r_struct
id|cfs_rdwr_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|cfs_rdwr_out
r_struct
id|cfs_rdwr_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
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
)brace
suffix:semicolon
multiline_comment|/* cfs_replace: */
multiline_comment|/* CFS_REPLACE is a venus-&gt;kernel call */
DECL|struct|cfs_replace_out
r_struct
id|cfs_replace_out
(brace
multiline_comment|/* cfs_replace is a venus-&gt;kernel call */
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|NewFid
id|ViceFid
id|NewFid
suffix:semicolon
DECL|member|OldFid
id|ViceFid
id|OldFid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cfs_open_by_path: */
DECL|struct|cfs_open_by_path_in
r_struct
id|cfs_open_by_path_in
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
DECL|member|VFid
id|ViceFid
id|VFid
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cfs_open_by_path_out
r_struct
id|cfs_open_by_path_out
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
DECL|member|path
r_int
id|path
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Occasionally, don&squot;t cache the fid returned by CFS_LOOKUP. For instance, if&n; * the fid is inconsistent. This case is handled by setting the top bit of the&n; * return result parameter.&n; */
DECL|macro|CFS_NOCACHE
mdefine_line|#define CFS_NOCACHE          0x80000000
DECL|union|inputArgs
r_union
id|inputArgs
(brace
DECL|member|ih
r_struct
id|cfs_in_hdr
id|ih
suffix:semicolon
multiline_comment|/* NB: every struct below begins with an ih */
DECL|member|cfs_open
r_struct
id|cfs_open_in
id|cfs_open
suffix:semicolon
DECL|member|cfs_close
r_struct
id|cfs_close_in
id|cfs_close
suffix:semicolon
DECL|member|cfs_ioctl
r_struct
id|cfs_ioctl_in
id|cfs_ioctl
suffix:semicolon
DECL|member|cfs_getattr
r_struct
id|cfs_getattr_in
id|cfs_getattr
suffix:semicolon
DECL|member|cfs_setattr
r_struct
id|cfs_setattr_in
id|cfs_setattr
suffix:semicolon
DECL|member|cfs_access
r_struct
id|cfs_access_in
id|cfs_access
suffix:semicolon
DECL|member|cfs_lookup
r_struct
id|cfs_lookup_in
id|cfs_lookup
suffix:semicolon
DECL|member|cfs_create
r_struct
id|cfs_create_in
id|cfs_create
suffix:semicolon
DECL|member|cfs_remove
r_struct
id|cfs_remove_in
id|cfs_remove
suffix:semicolon
DECL|member|cfs_link
r_struct
id|cfs_link_in
id|cfs_link
suffix:semicolon
DECL|member|cfs_rename
r_struct
id|cfs_rename_in
id|cfs_rename
suffix:semicolon
DECL|member|cfs_mkdir
r_struct
id|cfs_mkdir_in
id|cfs_mkdir
suffix:semicolon
DECL|member|cfs_rmdir
r_struct
id|cfs_rmdir_in
id|cfs_rmdir
suffix:semicolon
DECL|member|cfs_readdir
r_struct
id|cfs_readdir_in
id|cfs_readdir
suffix:semicolon
DECL|member|cfs_symlink
r_struct
id|cfs_symlink_in
id|cfs_symlink
suffix:semicolon
DECL|member|cfs_readlink
r_struct
id|cfs_readlink_in
id|cfs_readlink
suffix:semicolon
DECL|member|cfs_fsync
r_struct
id|cfs_fsync_in
id|cfs_fsync
suffix:semicolon
DECL|member|cfs_inactive
r_struct
id|cfs_inactive_in
id|cfs_inactive
suffix:semicolon
DECL|member|cfs_vget
r_struct
id|cfs_vget_in
id|cfs_vget
suffix:semicolon
DECL|member|cfs_rdwr
r_struct
id|cfs_rdwr_in
id|cfs_rdwr
suffix:semicolon
DECL|member|cfs_open_by_path
r_struct
id|cfs_open_by_path_in
id|cfs_open_by_path
suffix:semicolon
)brace
suffix:semicolon
DECL|union|outputArgs
r_union
id|outputArgs
(brace
DECL|member|oh
r_struct
id|cfs_out_hdr
id|oh
suffix:semicolon
multiline_comment|/* NB: every struct below begins with an oh */
DECL|member|cfs_root
r_struct
id|cfs_root_out
id|cfs_root
suffix:semicolon
DECL|member|cfs_open
r_struct
id|cfs_open_out
id|cfs_open
suffix:semicolon
DECL|member|cfs_ioctl
r_struct
id|cfs_ioctl_out
id|cfs_ioctl
suffix:semicolon
DECL|member|cfs_getattr
r_struct
id|cfs_getattr_out
id|cfs_getattr
suffix:semicolon
DECL|member|cfs_lookup
r_struct
id|cfs_lookup_out
id|cfs_lookup
suffix:semicolon
DECL|member|cfs_create
r_struct
id|cfs_create_out
id|cfs_create
suffix:semicolon
DECL|member|cfs_mkdir
r_struct
id|cfs_mkdir_out
id|cfs_mkdir
suffix:semicolon
DECL|member|cfs_readdir
r_struct
id|cfs_readdir_out
id|cfs_readdir
suffix:semicolon
DECL|member|cfs_readlink
r_struct
id|cfs_readlink_out
id|cfs_readlink
suffix:semicolon
DECL|member|cfs_vget
r_struct
id|cfs_vget_out
id|cfs_vget
suffix:semicolon
DECL|member|cfs_purgeuser
r_struct
id|cfs_purgeuser_out
id|cfs_purgeuser
suffix:semicolon
DECL|member|cfs_zapfile
r_struct
id|cfs_zapfile_out
id|cfs_zapfile
suffix:semicolon
DECL|member|cfs_zapdir
r_struct
id|cfs_zapdir_out
id|cfs_zapdir
suffix:semicolon
DECL|member|cfs_zapvnode
r_struct
id|cfs_zapvnode_out
id|cfs_zapvnode
suffix:semicolon
DECL|member|cfs_purgefid
r_struct
id|cfs_purgefid_out
id|cfs_purgefid
suffix:semicolon
DECL|member|cfs_rdwr
r_struct
id|cfs_rdwr_out
id|cfs_rdwr
suffix:semicolon
DECL|member|cfs_replace
r_struct
id|cfs_replace_out
id|cfs_replace
suffix:semicolon
DECL|member|cfs_open_by_path
r_struct
id|cfs_open_by_path_out
id|cfs_open_by_path
suffix:semicolon
)brace
suffix:semicolon
DECL|union|cfs_downcalls
r_union
id|cfs_downcalls
(brace
multiline_comment|/* CFS_INVALIDATE is a venus-&gt;kernel call */
multiline_comment|/* CFS_FLUSH is a venus-&gt;kernel call */
DECL|member|purgeuser
r_struct
id|cfs_purgeuser_out
id|purgeuser
suffix:semicolon
DECL|member|zapfile
r_struct
id|cfs_zapfile_out
id|zapfile
suffix:semicolon
DECL|member|zapdir
r_struct
id|cfs_zapdir_out
id|zapdir
suffix:semicolon
DECL|member|zapvnode
r_struct
id|cfs_zapvnode_out
id|zapvnode
suffix:semicolon
DECL|member|purgefid
r_struct
id|cfs_purgefid_out
id|purgefid
suffix:semicolon
DECL|member|replace
r_struct
id|cfs_replace_out
id|replace
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Used for identifying usage of &quot;Control&quot; and pioctls&n; */
DECL|macro|PIOCPARM_MASK
mdefine_line|#define PIOCPARM_MASK 0x0000ffff
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
mdefine_line|#define&t;CTL_FILE&t;&t;&quot;/coda/.CONTROL&quot;
DECL|macro|IS_CTL_FID
mdefine_line|#define&t;IS_CTL_FID(fidp)&t;((fidp)-&gt;Volume == CTL_VOL &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Vnode == CTL_VNO &amp;&amp;&bslash;&n;&t;&t;&t;&t; (fidp)-&gt;Unique == CTL_UNI)
macro_line|#endif 
eof
