multiline_comment|/*&n; *  linux/fs/filesystems.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  table of configured filesystems&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/hpfs_fs.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/efs_fs.h&gt;
macro_line|#include &lt;linux/romfs_fs.h&gt;
macro_line|#include &lt;linux/auto_fs.h&gt;
macro_line|#include &lt;linux/qnx4_fs.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;linux/ntfs_fs.h&gt;
macro_line|#include &lt;linux/hfs_fs.h&gt;
macro_line|#include &lt;linux/devpts_fs.h&gt;
macro_line|#include &lt;linux/bfs_fs.h&gt;
macro_line|#include &lt;linux/adfs_fs.h&gt;
macro_line|#include &lt;linux/openprom_fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/lockd/bind.h&gt;
macro_line|#include &lt;linux/lockd/xdr.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/nls.h&gt;
macro_line|#ifdef CONFIG_CODA_FS
r_extern
r_int
id|init_coda
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEVPTS_FS
r_extern
r_int
id|init_devpts_fs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|filesystem_setup
r_void
id|__init
id|filesystem_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_MINIX_FS
id|init_minix_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ROMFS_FS
id|init_romfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UMSDOS_FS
id|init_umsdos_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FAT_FS
id|init_fat_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MSDOS_FS
id|init_msdos_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VFAT_FS
id|init_vfat_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|init_proc_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LOCKD
id|nlmxdr_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NFS_FS
id|init_nfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CODA_FS
id|init_coda
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMB_FS
id|init_smb_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NCP_FS
id|init_ncp_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISO9660_FS
id|init_iso9660_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSV_FS
id|init_sysv_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HPFS_FS
id|init_hpfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NTFS_FS
id|init_ntfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HFS_FS
id|init_hfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AFFS_FS
id|init_affs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UFS_FS
id|init_ufs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EFS_FS
id|init_efs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUTOFS_FS
id|init_autofs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ADFS_FS
id|init_adfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DEVPTS_FS
id|init_devpts_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_QNX4FS_FS
id|init_qnx4_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_UDF_FS
id|init_udf_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BFS_FS
id|init_bfs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN_OPENPROMFS
id|init_openprom_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NLS
id|init_nls
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifndef CONFIG_NFSD
macro_line|#ifdef CONFIG_NFSD_MODULE
DECL|variable|do_nfsservctl
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
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_int
DECL|function|sys_nfsservctl
id|asmlinkage
id|sys_nfsservctl
c_func
(paren
r_int
id|cmd
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
macro_line|#ifndef CONFIG_NFSD_MODULE
r_return
op_minus
id|ENOSYS
suffix:semicolon
macro_line|#else
r_int
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_nfsservctl
)paren
(brace
id|ret
op_assign
id|do_nfsservctl
c_func
(paren
id|cmd
comma
id|argp
comma
id|resp
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|request_module
(paren
l_string|&quot;nfsd&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|do_nfsservctl
)paren
id|ret
op_assign
id|do_nfsservctl
c_func
(paren
id|cmd
comma
id|argp
comma
id|resp
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_KMOD */
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif /* CONFIG_NFSD_MODULE */
)brace
macro_line|#endif /* CONFIG_NFSD */
eof
