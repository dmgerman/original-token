multiline_comment|/* $Id: fs_mount.h,v 1.2 1997/04/18 14:34:46 jj Exp $&n; * fs_mount.h:  Definitions for mount structure conversions.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __ASM_FS_MOUNT_H
DECL|macro|__ASM_FS_MOUNT_H
mdefine_line|#define __ASM_FS_MOUNT_H
macro_line|#if defined(CONFIG_SPARC32_COMPAT) || defined(CONFIG_SPARC32_COMPAT_MODULE)
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* We need this to convert 32bit mount structures to 64bit */
r_extern
r_void
op_star
id|do_ncp_super_data_conv
c_func
(paren
r_void
op_star
id|raw_data
)paren
suffix:semicolon
r_extern
r_void
op_star
id|do_smb_super_data_conv
c_func
(paren
r_void
op_star
id|raw_data
)paren
suffix:semicolon
DECL|function|ncp_super_data_conv
r_extern
id|__inline__
r_void
op_star
id|ncp_super_data_conv
c_func
(paren
r_void
op_star
id|raw_data
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
r_return
id|do_ncp_super_data_conv
c_func
(paren
id|raw_data
)paren
suffix:semicolon
r_else
r_return
id|raw_data
suffix:semicolon
)brace
DECL|function|smb_super_data_conv
r_extern
id|__inline__
r_void
op_star
id|smb_super_data_conv
c_func
(paren
r_void
op_star
id|raw_data
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;tss.flags
op_amp
id|SPARC_FLAG_32BIT
)paren
r_return
id|do_smb_super_data_conv
c_func
(paren
id|raw_data
)paren
suffix:semicolon
r_else
r_return
id|raw_data
suffix:semicolon
)brace
macro_line|#else /* CONFIG_SPARC32_COMPAT* */
DECL|macro|ncp_super_data_conv
mdefine_line|#define ncp_super_data_conv(__x) __x
DECL|macro|smb_super_data_conv
mdefine_line|#define smb_super_data_conv(__x) __x
macro_line|#endif /* CONFIG_SPARC32_COMPAT* */
DECL|macro|nfs_super_data_conv
mdefine_line|#define nfs_super_data_conv(__x) __x
macro_line|#endif /* __ASM_FS_MOUNT_H */
eof
