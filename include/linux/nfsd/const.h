multiline_comment|/*&n; * include/linux/nfsd/nfsconst.h&n; *&n; * Various constants related to NFS.&n; *&n; * Copyright (C) 1995 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef __NFSCONST_H__
DECL|macro|__NFSCONST_H__
mdefine_line|#define __NFSCONST_H__
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/dirent.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
multiline_comment|/*&n; * Maximum protocol version supported by knfsd&n; */
DECL|macro|NFSSVC_MAXVERS
mdefine_line|#define NFSSVC_MAXVERS&t;&t;3
multiline_comment|/*&n; * Maximum blocksize supported by daemon currently at 8K&n; */
DECL|macro|NFSSVC_MAXBLKSIZE
mdefine_line|#define NFSSVC_MAXBLKSIZE&t;8192
DECL|macro|NFS2_MAXPATHLEN
mdefine_line|#define NFS2_MAXPATHLEN&t;&t;1024
DECL|macro|NFS2_MAXNAMLEN
mdefine_line|#define NFS2_MAXNAMLEN&t;&t;255
DECL|macro|NFS2_FHSIZE
mdefine_line|#define NFS2_FHSIZE&t;&t;NFS_FHSIZE
DECL|macro|NFS2_COOKIESIZE
mdefine_line|#define NFS2_COOKIESIZE&t;&t;4
DECL|macro|NFS3_MAXPATHLEN
mdefine_line|#define NFS3_MAXPATHLEN&t;&t;PATH_MAX
DECL|macro|NFS3_MAXNAMLEN
mdefine_line|#define NFS3_MAXNAMLEN&t;&t;NAME_MAX
DECL|macro|NFS3_FHSIZE
mdefine_line|#define NFS3_FHSIZE&t;&t;NFS_FHSIZE
DECL|macro|NFS3_COOKIEVERFSIZE
mdefine_line|#define NFS3_COOKIEVERFSIZE&t;8
DECL|macro|NFS3_CREATEVERFSIZE
mdefine_line|#define NFS3_CREATEVERFSIZE&t;8
DECL|macro|NFS3_WRITEVERFSIZE
mdefine_line|#define NFS3_WRITEVERFSIZE&t;8
macro_line|#ifdef __KERNEL__
macro_line|#ifndef NFS_SUPER_MAGIC
DECL|macro|NFS_SUPER_MAGIC
macro_line|# define NFS_SUPER_MAGIC&t;0x6969
macro_line|#endif
multiline_comment|/*&n; * NFS stats. The good thing with these values is that NFSv3 errors are&n; * a superset of NFSv2 errors (with the exception of NFSERR_WFLUSH which&n; * no-one uses anyway), so we can happily mix code as long as we make sure&n; * no NFSv3 errors are returned to NFSv2 clients.&n; */
DECL|macro|NFS_OK
mdefine_line|#define NFS_OK&t;&t;&t;0&t;&t;/* v2 v3 */
DECL|macro|NFSERR_PERM
mdefine_line|#define NFSERR_PERM&t;&t;1&t;&t;/* v2 v3 */
DECL|macro|NFSERR_NOENT
mdefine_line|#define NFSERR_NOENT&t;&t;2&t;&t;/* v2 v3 */
DECL|macro|NFSERR_IO
mdefine_line|#define NFSERR_IO&t;&t;5&t;&t;/* v2 v3 */
DECL|macro|NFSERR_NXIO
mdefine_line|#define NFSERR_NXIO&t;&t;6&t;&t;/* v2 v3 */
DECL|macro|NFSERR_ACCES
mdefine_line|#define NFSERR_ACCES&t;&t;13&t;&t;/* v2 v3 */
DECL|macro|NFSERR_EXIST
mdefine_line|#define NFSERR_EXIST&t;&t;17&t;&t;/* v2 v3 */
DECL|macro|NFSERR_XDEV
mdefine_line|#define NFSERR_XDEV&t;&t;18&t;&t;/*    v3 */
DECL|macro|NFSERR_NODEV
mdefine_line|#define NFSERR_NODEV&t;&t;19&t;&t;/* v2 v3 */
DECL|macro|NFSERR_NOTDIR
mdefine_line|#define NFSERR_NOTDIR&t;&t;20&t;&t;/* v2 v3 */
DECL|macro|NFSERR_ISDIR
mdefine_line|#define NFSERR_ISDIR&t;&t;21&t;&t;/* v2 v3 */
DECL|macro|NFSERR_INVAL
mdefine_line|#define NFSERR_INVAL&t;&t;22&t;&t;/*    v3 */
DECL|macro|NFSERR_FBIG
mdefine_line|#define NFSERR_FBIG&t;&t;27&t;&t;/* v2 v3 */
DECL|macro|NFSERR_NOSPC
mdefine_line|#define NFSERR_NOSPC&t;&t;28&t;&t;/* v2 v3 */
DECL|macro|NFSERR_ROFS
mdefine_line|#define NFSERR_ROFS&t;&t;30&t;&t;/* v2 v3 */
DECL|macro|NFSERR_MLINK
mdefine_line|#define NFSERR_MLINK&t;&t;31&t;&t;/*    v3 */
DECL|macro|NFSERR_NAMETOOLONG
mdefine_line|#define NFSERR_NAMETOOLONG&t;63&t;&t;/* v2 v3 */
DECL|macro|NFSERR_NOTEMPTY
mdefine_line|#define NFSERR_NOTEMPTY&t;&t;66&t;&t;/* v2 v3 */
DECL|macro|NFSERR_DQUOT
mdefine_line|#define NFSERR_DQUOT&t;&t;69&t;&t;/* v2 v3 */
DECL|macro|NFSERR_STALE
mdefine_line|#define NFSERR_STALE&t;&t;70&t;&t;/* v2 v3 */
DECL|macro|NFSERR_REMOTE
mdefine_line|#define NFSERR_REMOTE&t;&t;71&t;&t;/*    v3 */
DECL|macro|NFSERR_WFLUSH
mdefine_line|#define NFSERR_WFLUSH&t;&t;99&t;&t;/* v2    */
DECL|macro|NFSERR_BADHANDLE
mdefine_line|#define NFSERR_BADHANDLE&t;10001&t;&t;/*    v3 */
DECL|macro|NFSERR_NOT_SYNC
mdefine_line|#define NFSERR_NOT_SYNC&t;&t;10002&t;&t;/*    v3 */
DECL|macro|NFSERR_BAD_COOKIE
mdefine_line|#define NFSERR_BAD_COOKIE&t;10003&t;&t;/*    v3 */
DECL|macro|NFSERR_NOTSUPP
mdefine_line|#define NFSERR_NOTSUPP&t;&t;10004&t;&t;/*    v3 */
DECL|macro|NFSERR_TOOSMALL
mdefine_line|#define NFSERR_TOOSMALL&t;&t;10005&t;&t;/*    v3 */
DECL|macro|NFSERR_SERVERFAULT
mdefine_line|#define NFSERR_SERVERFAULT&t;10006&t;&t;/*    v3 */
DECL|macro|NFSERR_BADTYPE
mdefine_line|#define NFSERR_BADTYPE&t;&t;10007&t;&t;/*    v3 */
DECL|macro|NFSERR_JUKEBOX
mdefine_line|#define NFSERR_JUKEBOX&t;&t;10008&t;&t;/*    v3 */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __NFSCONST_H__ */
eof
