multiline_comment|/*&n; * linux/fs/nfsd/nfsctl.c&n; *&n; * Syscall interface to knfsd.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|NFS_GETFH_NEW
mdefine_line|#define NFS_GETFH_NEW
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
macro_line|#include &lt;linux/nfsd/syscall.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#else
DECL|macro|copy_from_user
macro_line|# define copy_from_user&t;&t;memcpy_fromfs
DECL|macro|copy_to_user
macro_line|# define copy_to_user&t;&t;memcpy_tofs
DECL|macro|access_ok
macro_line|# define access_ok&t;&t;!verify_area
macro_line|#endif
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
r_extern
r_int
id|sys_call_table
(braket
)braket
suffix:semicolon
r_static
r_int
id|nfsctl_svc
c_func
(paren
r_struct
id|nfsctl_svc
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_addclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_delclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_export
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_unexport
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_getfh
c_func
(paren
r_struct
id|nfsctl_fhparm
op_star
comma
r_struct
id|knfs_fh
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfsctl_getfd
c_func
(paren
r_struct
id|nfsctl_fdparm
op_star
comma
r_struct
id|knfs_fh
op_star
)paren
suffix:semicolon
multiline_comment|/* static int&t;nfsctl_ugidupdate(struct nfsctl_ugidmap *data); */
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
r_int
id|exp_procfs_exports
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
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|function|proc_export_init
r_void
id|proc_export_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
l_string|&quot;fs/nfs&quot;
comma
l_int|0
)paren
)paren
r_return
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;fs/nfs/exports&quot;
comma
l_int|0
comma
l_int|0
comma
id|exp_procfs_exports
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize nfsd&n; */
r_static
r_void
DECL|function|nfsd_init
id|nfsd_init
c_func
(paren
r_void
)paren
(brace
id|nfsd_xdr_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XDR */
id|nfsd_stat_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Statistics */
id|nfsd_cache_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* RPC reply cache */
id|nfsd_export_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Exports table */
id|nfsd_lockd_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* lockd-&gt;nfsd callbacks */
id|proc_export_init
c_func
(paren
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_svc
id|nfsctl_svc
c_func
(paren
r_struct
id|nfsctl_svc
op_star
id|data
)paren
(brace
r_return
id|nfsd_svc
c_func
(paren
id|data-&gt;svc_port
comma
id|data-&gt;svc_nthreads
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_addclient
id|nfsctl_addclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|data
)paren
(brace
r_return
id|exp_addclient
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_delclient
id|nfsctl_delclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|data
)paren
(brace
r_return
id|exp_delclient
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_export
id|nfsctl_export
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|data
)paren
(brace
r_return
id|exp_export
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_unexport
id|nfsctl_unexport
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|data
)paren
(brace
r_return
id|exp_unexport
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
macro_line|#ifdef notyet
r_static
r_inline
r_int
DECL|function|nfsctl_ugidupdate
id|nfsctl_ugidupdate
c_func
(paren
id|nfs_ugidmap
op_star
id|data
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
r_static
r_inline
r_int
DECL|function|nfsctl_getfd
id|nfsctl_getfd
c_func
(paren
r_struct
id|nfsctl_fdparm
op_star
id|data
comma
r_struct
id|knfs_fh
op_star
id|res
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
r_struct
id|svc_client
op_star
id|clp
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;gd_addr.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;gd_version
template_param
id|NFSSVC_MAXVERS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|data-&gt;gd_addr
suffix:semicolon
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|exp_getclient
c_func
(paren
id|sin
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|err
op_assign
id|exp_rootfh
c_func
(paren
id|clp
comma
l_int|0
comma
l_int|0
comma
id|data-&gt;gd_path
comma
id|res
)paren
suffix:semicolon
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfsctl_getfh
id|nfsctl_getfh
c_func
(paren
r_struct
id|nfsctl_fhparm
op_star
id|data
comma
r_struct
id|knfs_fh
op_star
id|res
)paren
(brace
r_struct
id|sockaddr_in
op_star
id|sin
suffix:semicolon
r_struct
id|svc_client
op_star
id|clp
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;gf_addr.sa_family
op_ne
id|AF_INET
)paren
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;gf_version
template_param
id|NFSSVC_MAXVERS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sin
op_assign
(paren
r_struct
id|sockaddr_in
op_star
)paren
op_amp
id|data-&gt;gf_addr
suffix:semicolon
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|exp_getclient
c_func
(paren
id|sin
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|err
op_assign
id|exp_rootfh
c_func
(paren
id|clp
comma
id|to_kdev_t
c_func
(paren
id|data-&gt;gf_dev
)paren
comma
id|data-&gt;gf_ino
comma
l_int|NULL
comma
id|res
)paren
suffix:semicolon
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NFSD
DECL|macro|handle_sys_nfsservctl
mdefine_line|#define handle_sys_nfsservctl sys_nfsservctl
macro_line|#endif
r_int
DECL|function|handle_sys_nfsservctl
id|asmlinkage
id|handle_sys_nfsservctl
c_func
(paren
r_int
id|cmd
comma
r_void
op_star
id|opaque_argp
comma
r_void
op_star
id|opaque_resp
)paren
(brace
r_struct
id|nfsctl_arg
op_star
id|argp
op_assign
id|opaque_argp
suffix:semicolon
r_union
id|nfsctl_res
op_star
id|resp
op_assign
id|opaque_resp
suffix:semicolon
r_struct
id|nfsctl_arg
op_star
id|arg
op_assign
l_int|NULL
suffix:semicolon
r_union
id|nfsctl_res
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_kernel
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
id|nfsd_init
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|argp
comma
r_sizeof
(paren
op_star
id|argp
)paren
)paren
op_logical_or
(paren
id|resp
op_logical_and
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|resp
comma
r_sizeof
(paren
op_star
id|resp
)paren
)paren
)paren
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* ??? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|arg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|arg
)paren
comma
id|GFP_USER
)paren
)paren
op_logical_or
(paren
id|resp
op_logical_and
op_logical_neg
(paren
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
comma
id|GFP_USER
)paren
)paren
)paren
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|copy_from_user
c_func
(paren
id|arg
comma
id|argp
comma
r_sizeof
(paren
op_star
id|argp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg-&gt;ca_version
op_ne
id|NFSCTL_VERSION
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: incompatible version in syscall.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NFSCTL_SVC
suffix:colon
id|err
op_assign
id|nfsctl_svc
c_func
(paren
op_amp
id|arg-&gt;ca_svc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NFSCTL_ADDCLIENT
suffix:colon
id|err
op_assign
id|nfsctl_addclient
c_func
(paren
op_amp
id|arg-&gt;ca_client
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NFSCTL_DELCLIENT
suffix:colon
id|err
op_assign
id|nfsctl_delclient
c_func
(paren
op_amp
id|arg-&gt;ca_client
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NFSCTL_EXPORT
suffix:colon
id|err
op_assign
id|nfsctl_export
c_func
(paren
op_amp
id|arg-&gt;ca_export
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NFSCTL_UNEXPORT
suffix:colon
id|err
op_assign
id|nfsctl_unexport
c_func
(paren
op_amp
id|arg-&gt;ca_export
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef notyet
r_case
id|NFSCTL_UGIDUPDATE
suffix:colon
id|err
op_assign
id|nfsctl_ugidupdate
c_func
(paren
op_amp
id|arg-&gt;ca_umap
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|NFSCTL_GETFH
suffix:colon
id|err
op_assign
id|nfsctl_getfh
c_func
(paren
op_amp
id|arg-&gt;ca_getfh
comma
op_amp
id|res-&gt;cr_getfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NFSCTL_GETFD
suffix:colon
id|err
op_assign
id|nfsctl_getfd
c_func
(paren
op_amp
id|arg-&gt;ca_getfd
comma
op_amp
id|res-&gt;cr_getfh
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|resp
)paren
id|copy_to_user
c_func
(paren
id|resp
comma
id|res
comma
r_sizeof
(paren
op_star
id|resp
)paren
)paren
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|arg
)paren
id|kfree
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
id|unlock_kernel
(paren
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* New-style module support since 2.1.18 */
macro_line|#if LINUX_VERSION_CODE &gt;= 131346
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Olaf Kirch &lt;okir@monad.swb.de&gt;&quot;
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
(paren
op_star
id|do_nfsservctl
)paren
(paren
r_int
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize the module&n; */
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Installing knfsd (copyright (C) 1996 okir@monad.swb.de).&bslash;n&quot;
)paren
suffix:semicolon
id|do_nfsservctl
op_assign
id|handle_sys_nfsservctl
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Clean up the mess before unloading the module&n; */
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfsd: nfsd busy, remove delayed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|do_nfsservctl
op_assign
l_int|NULL
suffix:semicolon
id|nfsd_export_shutdown
c_func
(paren
)paren
suffix:semicolon
id|nfsd_cache_shutdown
c_func
(paren
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/nfs/exports&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;fs/nfs&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|nfsd_stat_shutdown
c_func
(paren
)paren
suffix:semicolon
id|nfsd_lockd_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
