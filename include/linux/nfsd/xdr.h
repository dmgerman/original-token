multiline_comment|/*&n; * linux/inxlude/linux/nfsd/xdr.h&n; *&n; * XDR types for nfsd. This is mainly a typing exercise.&n; */
macro_line|#ifndef LINUX_NFSD_H
DECL|macro|LINUX_NFSD_H
mdefine_line|#define LINUX_NFSD_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
DECL|struct|nfsd_fhandle
r_struct
id|nfsd_fhandle
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_sattrargs
r_struct
id|nfsd_sattrargs
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|attrs
r_struct
id|iattr
id|attrs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_diropargs
r_struct
id|nfsd_diropargs
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_readargs
r_struct
id|nfsd_readargs
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|totalsize
id|__u32
id|totalsize
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_writeargs
r_struct
id|nfsd_writeargs
(brace
DECL|member|fh
id|svc_fh
id|fh
suffix:semicolon
DECL|member|beginoffset
id|__u32
id|beginoffset
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|totalcount
id|__u32
id|totalcount
suffix:semicolon
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_createargs
r_struct
id|nfsd_createargs
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|attrs
r_struct
id|iattr
id|attrs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_renameargs
r_struct
id|nfsd_renameargs
(brace
DECL|member|ffh
r_struct
id|svc_fh
id|ffh
suffix:semicolon
DECL|member|fname
r_char
op_star
id|fname
suffix:semicolon
DECL|member|flen
r_int
id|flen
suffix:semicolon
DECL|member|tfh
r_struct
id|svc_fh
id|tfh
suffix:semicolon
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
DECL|member|tlen
r_int
id|tlen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_linkargs
r_struct
id|nfsd_linkargs
(brace
DECL|member|ffh
r_struct
id|svc_fh
id|ffh
suffix:semicolon
DECL|member|tfh
r_struct
id|svc_fh
id|tfh
suffix:semicolon
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
DECL|member|tlen
r_int
id|tlen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_symlinkargs
r_struct
id|nfsd_symlinkargs
(brace
DECL|member|ffh
r_struct
id|svc_fh
id|ffh
suffix:semicolon
DECL|member|fname
r_char
op_star
id|fname
suffix:semicolon
DECL|member|flen
r_int
id|flen
suffix:semicolon
DECL|member|tname
r_char
op_star
id|tname
suffix:semicolon
DECL|member|tlen
r_int
id|tlen
suffix:semicolon
DECL|member|attrs
r_struct
id|iattr
id|attrs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_readdirargs
r_struct
id|nfsd_readdirargs
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|cookie
id|__u32
id|cookie
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_attrstat
r_struct
id|nfsd_attrstat
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_diropres
r_struct
id|nfsd_diropres
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_readlinkres
r_struct
id|nfsd_readlinkres
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_readres
r_struct
id|nfsd_readres
(brace
DECL|member|fh
r_struct
id|svc_fh
id|fh
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_readdirres
r_struct
id|nfsd_readdirres
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfsd_statfsres
r_struct
id|nfsd_statfsres
(brace
DECL|member|stats
r_struct
id|statfs
id|stats
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Storage requirements for XDR arguments and results.&n; */
DECL|union|nfsd_xdrstore
r_union
id|nfsd_xdrstore
(brace
DECL|member|sattr
r_struct
id|nfsd_sattrargs
id|sattr
suffix:semicolon
DECL|member|dirop
r_struct
id|nfsd_diropargs
id|dirop
suffix:semicolon
DECL|member|read
r_struct
id|nfsd_readargs
id|read
suffix:semicolon
DECL|member|write
r_struct
id|nfsd_writeargs
id|write
suffix:semicolon
DECL|member|create
r_struct
id|nfsd_createargs
id|create
suffix:semicolon
DECL|member|rename
r_struct
id|nfsd_renameargs
id|rename
suffix:semicolon
DECL|member|link
r_struct
id|nfsd_linkargs
id|link
suffix:semicolon
DECL|member|symlink
r_struct
id|nfsd_symlinkargs
id|symlink
suffix:semicolon
DECL|member|readdir
r_struct
id|nfsd_readdirargs
id|readdir
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFSSVC_XDRSIZE
mdefine_line|#define NFSSVC_XDRSIZE&t;&t;sizeof(union nfsd_xdrstore)
r_void
id|nfsd_xdr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nfssvc_decode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|svc_fh
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_sattrargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_sattrargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_diropargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_diropargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_readargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_readargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_writeargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_writeargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_createargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_createargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_renameargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_renameargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_linkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_linkargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_symlinkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_symlinkargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_decode_readdirargs
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_readdirargs
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_attrstat
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_attrstat
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_diropres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_diropres
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_readlinkres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_readlinkres
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_readres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_readres
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_statfsres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_statfsres
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_readdirres
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_readdirres
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_release_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
id|u32
op_star
comma
r_struct
id|nfsd_fhandle
op_star
)paren
suffix:semicolon
r_int
id|nfssvc_encode_entry
c_func
(paren
r_struct
id|readdir_cd
op_star
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|off_t
id|offset
comma
id|ino_t
id|ino
)paren
suffix:semicolon
macro_line|#endif /* LINUX_NFSD_H */
eof