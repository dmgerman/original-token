multiline_comment|/*&n; *  ioctl.c&n; *&n; *  Copyright (C) 1995 by Volker Lendecke&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT
macro_line|#endif
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/smb_fs.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
r_int
DECL|function|smb_ioctl
id|smb_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|result
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SMB_IOC_GETMOUNTUID
suffix:colon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
id|uid_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|uid_t
)paren
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|result
suffix:semicolon
)brace
id|put_fs_word
c_func
(paren
id|SMB_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|m.mounted_uid
comma
(paren
id|uid_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
