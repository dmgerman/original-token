multiline_comment|/* &n; * Coda File System, Linux Kernel module&n; * &n; * Original version, adapted from cfs_mach.c, (C) Carnegie Mellon University&n; * Linux modifications (C) 1996, Peter J. Braam&n; * Rewritten for Linux 2.1 (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon University encourages users of this software to&n; * contribute improvements to the Coda project.&n; */
macro_line|#ifndef _LINUX_CODA_FS
DECL|macro|_LINUX_CODA_FS
mdefine_line|#define _LINUX_CODA_FS
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt; 
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/wait.h&gt;&t;&t;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/* operations */
r_extern
r_struct
id|inode_operations
id|coda_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|coda_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|coda_ioctl_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|coda_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|coda_ioctl_operations
suffix:semicolon
multiline_comment|/* operations shared over more than one file */
r_int
id|coda_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_release
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
suffix:semicolon
r_int
id|coda_permission
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
multiline_comment|/* global variables */
r_extern
r_int
id|coda_debug
suffix:semicolon
r_extern
r_int
id|coda_print_entry
suffix:semicolon
r_extern
r_int
id|coda_access_cache
suffix:semicolon
multiline_comment|/* this file:  heloers */
r_char
op_star
id|coda_f2s
c_func
(paren
id|ViceFid
op_star
id|f
comma
r_char
op_star
id|s
)paren
suffix:semicolon
r_int
id|coda_isroot
c_func
(paren
r_struct
id|inode
op_star
id|i
)paren
suffix:semicolon
r_int
id|coda_iscontrol
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|length
)paren
suffix:semicolon
r_void
id|coda_load_creds
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred
)paren
suffix:semicolon
r_int
id|coda_mycred
c_func
(paren
r_struct
id|coda_cred
op_star
)paren
suffix:semicolon
r_void
id|coda_vattr_to_iattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|coda_vattr
op_star
)paren
suffix:semicolon
r_void
id|coda_iattr_to_vattr
c_func
(paren
r_struct
id|iattr
op_star
comma
r_struct
id|coda_vattr
op_star
)paren
suffix:semicolon
r_int
r_int
id|coda_flags_to_cflags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|print_vattr
c_func
(paren
r_struct
id|coda_vattr
op_star
id|attr
)paren
suffix:semicolon
r_int
id|coda_cred_ok
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred
)paren
suffix:semicolon
r_int
id|coda_cred_eq
c_func
(paren
r_struct
id|coda_cred
op_star
id|cred1
comma
r_struct
id|coda_cred
op_star
id|cred2
)paren
suffix:semicolon
multiline_comment|/* defined in  file.c */
r_void
id|coda_prepare_openfile
c_func
(paren
r_struct
id|inode
op_star
id|coda_inode
comma
r_struct
id|file
op_star
id|coda_file
comma
r_struct
id|inode
op_star
id|open_inode
comma
r_struct
id|file
op_star
id|open_file
comma
r_struct
id|dentry
op_star
id|open_dentry
)paren
suffix:semicolon
r_void
id|coda_restore_codafile
c_func
(paren
r_struct
id|inode
op_star
id|coda_inode
comma
r_struct
id|file
op_star
id|coda_file
comma
r_struct
id|inode
op_star
id|open_inode
comma
r_struct
id|file
op_star
id|open_file
)paren
suffix:semicolon
r_int
id|coda_inode_grab
c_func
(paren
id|dev_t
id|dev
comma
id|ino_t
id|ino
comma
r_struct
id|inode
op_star
op_star
id|ind
)paren
suffix:semicolon
DECL|macro|NB_SFS_SIZ
mdefine_line|#define NB_SFS_SIZ 0x895440
multiline_comment|/* debugging masks */
DECL|macro|D_SUPER
mdefine_line|#define D_SUPER     1   /* print results returned by Venus */ 
DECL|macro|D_INODE
mdefine_line|#define D_INODE     2   /* print entry and exit into procedure */
DECL|macro|D_FILE
mdefine_line|#define D_FILE      4   /* print malloc, de-alloc information */
DECL|macro|D_CACHE
mdefine_line|#define D_CACHE     8   /* cache debugging */
DECL|macro|D_MALLOC
mdefine_line|#define D_MALLOC    16
DECL|macro|D_CNODE
mdefine_line|#define D_CNODE     32
DECL|macro|D_UPCALL
mdefine_line|#define D_UPCALL    64  /* up and downcall debugging */
DECL|macro|D_PSDEV
mdefine_line|#define D_PSDEV    128  
DECL|macro|D_PIOCTL
mdefine_line|#define D_PIOCTL   256
DECL|macro|D_SPECIAL
mdefine_line|#define D_SPECIAL  512
DECL|macro|D_TIMING
mdefine_line|#define D_TIMING  1024
DECL|macro|D_DOWNCALL
mdefine_line|#define D_DOWNCALL 2048
DECL|macro|CDEBUG
mdefine_line|#define CDEBUG(mask, format, a...)                                &bslash;&n;  do {                                                            &bslash;&n;  if (coda_debug &amp; mask) {                                        &bslash;&n;    printk(&quot;(%s,l. %d): &quot;,  __FUNCTION__, __LINE__);              &bslash;&n;    printk(format, ## a); }                                       &bslash;&n;} while (0) ;                            
DECL|macro|ENTRY
mdefine_line|#define ENTRY    &bslash;&n;    if(coda_print_entry) printk(&quot;Process %d entered %s&bslash;n&quot;,current-&gt;pid,__FUNCTION__)
DECL|macro|EXIT
mdefine_line|#define EXIT    &bslash;&n;    if(coda_print_entry) printk(&quot;Process %d leaving %s&bslash;n&quot;,current-&gt;pid,__FUNCTION__)
DECL|macro|CHECK_CNODE
mdefine_line|#define CHECK_CNODE(c)                                                &bslash;&n;do {                                                                  &bslash;&n;  if ( coda_debug ) {&bslash;&n;    struct cnode *cnode = (c);                                          &bslash;&n;  if (!cnode)                                                         &bslash;&n;    printk (&quot;%s(%d): cnode is null&bslash;n&quot;, __FUNCTION__, __LINE__);        &bslash;&n;  if (cnode-&gt;c_magic != CODA_CNODE_MAGIC)                             &bslash;&n;    printk (&quot;%s(%d): cnode magic wrong&bslash;n&quot;, __FUNCTION__, __LINE__);    &bslash;&n;  if (!cnode-&gt;c_vnode)                                                &bslash;&n;    printk (&quot;%s(%d): cnode has null inode&bslash;n&quot;, __FUNCTION__, __LINE__); &bslash;&n;  if ( (struct cnode *)cnode-&gt;c_vnode-&gt;u.generic_ip != cnode )           &bslash;&n;    printk(&quot;AAooh, %s(%d) cnode doesn&squot;t link right!&bslash;n&quot;, __FUNCTION__,__LINE__);&bslash;&n;}} while (0);
DECL|macro|CODA_ALLOC
mdefine_line|#define CODA_ALLOC(ptr, cast, size)                                       &bslash;&n;do {                                                                      &bslash;&n;    if (size &lt; 3000) {                                                    &bslash;&n;        ptr = (cast)kmalloc((unsigned long) size, GFP_KERNEL);            &bslash;&n;                CDEBUG(D_MALLOC, &quot;kmalloced: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);&bslash;&n;     }  else {                                                             &bslash;&n;        ptr = (cast)vmalloc((unsigned long) size);                        &bslash;&n;&t;CDEBUG(D_MALLOC, &quot;vmalloced: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);}&bslash;&n;    if (ptr == 0) {                                                       &bslash;&n;        printk(&quot;kernel malloc returns 0 at %s:%d&bslash;n&quot;, __FILE__, __LINE__);  &bslash;&n;    }                                                                     &bslash;&n;    memset( ptr, 0, size );                                                   &bslash;&n;} while (0)
DECL|macro|CODA_FREE
mdefine_line|#define CODA_FREE(ptr,size) do {if (size &lt; 3000) { kfree_s((ptr), (size)); CDEBUG(D_MALLOC, &quot;kfreed: %x at %x.&bslash;n&quot;, (int) size, (int) ptr); } else { vfree((ptr)); CDEBUG(D_MALLOC, &quot;vfreed: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);} } while (0)
macro_line|#endif
eof
