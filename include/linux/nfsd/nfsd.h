multiline_comment|/*&n; * linux/include/linux/nfsd/nfsd.h&n; *&n; * Hodge-podge collection of knfsd-related stuff.&n; * I will sort this out later.&n; *&n; * Copyright (C) 1995 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_NFSD_H
DECL|macro|LINUX_NFSD_NFSD_H
mdefine_line|#define LINUX_NFSD_NFSD_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfsd/debug.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/nfsd/export.h&gt;
macro_line|#include &lt;linux/nfsd/auth.h&gt;
macro_line|#include &lt;linux/nfsd/stats.h&gt;
multiline_comment|/*&n; * nfsd version&n; */
DECL|macro|NFSD_VERSION
mdefine_line|#define NFSD_VERSION&t;&t;&quot;0.4&quot;
multiline_comment|/*&n; * Maximum number of nfsd processes&n; */
DECL|macro|NFSD_MAXSERVS
mdefine_line|#define NFSD_MAXSERVS&t;&t;16
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Special flags for nfsd_permission. These must be different from MAY_READ,&n; * MAY_WRITE, and MAY_EXEC.&n; */
DECL|macro|MAY_NOP
mdefine_line|#define MAY_NOP&t;&t;&t;0
DECL|macro|MAY_SATTR
mdefine_line|#define MAY_SATTR&t;&t;8
DECL|macro|MAY_TRUNC
mdefine_line|#define MAY_TRUNC&t;&t;16
macro_line|#if (MAY_SATTR | MAY_TRUNC) &amp; (MAY_READ | MAY_WRITE | MAY_EXEC)
macro_line|# error &quot;please use a different value for MAY_SATTR or MAY_TRUNC.&quot;
macro_line|#endif
DECL|macro|MAY_CREATE
mdefine_line|#define MAY_CREATE&t;&t;(MAY_EXEC|MAY_WRITE)
DECL|macro|MAY_REMOVE
mdefine_line|#define MAY_REMOVE&t;&t;(MAY_EXEC|MAY_WRITE|MAY_TRUNC)
multiline_comment|/*&n; * Callback function for readdir&n; */
DECL|struct|readdir_cd
r_struct
id|readdir_cd
(brace
DECL|member|rqstp
r_struct
id|svc_rqst
op_star
id|rqstp
suffix:semicolon
DECL|member|dirfh
r_struct
id|svc_fh
op_star
id|dirfh
suffix:semicolon
DECL|member|buffer
id|u32
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
DECL|member|offset
id|u32
op_star
id|offset
suffix:semicolon
multiline_comment|/* previous dirent-&gt;d_next */
DECL|member|plus
r_char
id|plus
suffix:semicolon
multiline_comment|/* readdirplus */
DECL|member|eob
r_char
id|eob
suffix:semicolon
multiline_comment|/* end of buffer */
DECL|member|dotonly
r_char
id|dotonly
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|encode_dent_fn
r_typedef
r_int
(paren
op_star
id|encode_dent_fn
)paren
(paren
r_struct
id|readdir_cd
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|off_t
comma
id|ino_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Procedure table for NFSv2&n; */
r_extern
r_struct
id|svc_procedure
id|nfsd_procedures2
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|svc_program
id|nfsd_program
suffix:semicolon
multiline_comment|/*&n; * Function prototypes.&n; */
r_int
id|nfsd_svc
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|nrservs
)paren
suffix:semicolon
r_void
id|nfsd_racache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nfsd_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|nfsd_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_int
id|nfsd_create
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|iattr
op_star
id|attrs
comma
r_int
id|type
comma
id|dev_t
id|rdev
comma
r_struct
id|svc_fh
op_star
id|res
)paren
suffix:semicolon
r_int
id|nfsd_open
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
comma
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_void
id|nfsd_close
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|nfsd_read
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
r_char
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_int
id|nfsd_write
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
r_char
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|nfsd_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|nfsd_symlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
id|name
comma
r_int
id|len
comma
r_char
op_star
id|path
comma
r_int
id|plen
comma
r_struct
id|svc_fh
op_star
id|res
)paren
suffix:semicolon
r_int
id|nfsd_link
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|nfsd_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|nfsd_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|nfsd_unlink
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|nfsd_truncate
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|nfsd_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
id|loff_t
comma
id|encode_dent_fn
comma
id|u32
op_star
id|buffer
comma
r_int
op_star
id|countp
)paren
suffix:semicolon
r_int
id|nfsd_statfs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|svc_fh
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
r_int
id|nfsd_notify_change
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_int
id|nfsd_permission
c_func
(paren
r_struct
id|svc_export
op_star
comma
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|nfsd_write_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|nfsd_iget
c_func
(paren
id|dev_t
id|dev
comma
id|ino_t
id|ino
)paren
suffix:semicolon
r_int
id|nfsd_parentdev
c_func
(paren
id|dev_t
op_star
id|devp
)paren
suffix:semicolon
multiline_comment|/*&n; * lockd binding&n; */
r_void
id|nfsd_lockd_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_lockd_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_lockd_unexport
c_func
(paren
r_struct
id|svc_client
op_star
)paren
suffix:semicolon
macro_line|#ifndef makedev
DECL|macro|makedev
mdefine_line|#define makedev(maj, min)&t;(((maj) &lt;&lt; 8) | (min))
macro_line|#endif
multiline_comment|/*&n; * These variables contain pre-xdr&squot;ed values for faster operation.&n; * FIXME: should be replaced by macros for big-endian machines.&n; */
r_extern
id|u32
id|nfs_ok
comma
id|nfserr_perm
comma
id|nfserr_noent
comma
id|nfserr_io
comma
id|nfserr_nxio
comma
id|nfserr_acces
comma
id|nfserr_exist
comma
id|nfserr_xdev
comma
id|nfserr_nodev
comma
id|nfserr_notdir
comma
id|nfserr_isdir
comma
id|nfserr_inval
comma
id|nfserr_fbig
comma
id|nfserr_nospc
comma
id|nfserr_rofs
comma
id|nfserr_mlink
comma
id|nfserr_nametoolong
comma
id|nfserr_dquot
comma
id|nfserr_stale
comma
id|nfserr_remote
comma
id|nfserr_badhandle
comma
id|nfserr_notsync
comma
id|nfserr_badcookie
comma
id|nfserr_notsupp
comma
id|nfserr_toosmall
comma
id|nfserr_serverfault
comma
id|nfserr_badtype
comma
id|nfserr_jukebox
suffix:semicolon
multiline_comment|/*&n; * Time of server startup&n; */
r_extern
r_struct
id|timeval
id|nfssvc_boot
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_NFSD_H */
eof