multiline_comment|/*&n; *  linux/fs/filesystems.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  table of configured filesystems&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/xia_fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/umsdos_fs.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/hpfs_fs.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/ncp_fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
r_extern
r_void
id|device_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|binfmt_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* This may be used only once, enforced by &squot;static int callable&squot; */
DECL|function|sys_setup
id|asmlinkage
r_int
id|sys_setup
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|callable
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|callable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|callable
op_assign
l_int|0
suffix:semicolon
id|device_setup
c_func
(paren
)paren
suffix:semicolon
id|binfmt_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EXT_FS
id|init_ext_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_EXT2_FS
id|init_ext2_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_XIA_FS
id|init_xiafs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MINIX_FS
id|init_minix_fs
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
macro_line|#ifdef CONFIG_NFS_FS
id|init_nfs_fs
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
macro_line|#ifdef CONFIG_UFS_FS
id|init_ufs_fs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|mount_root
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
