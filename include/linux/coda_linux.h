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
r_extern
r_int
id|cfsnc_use
suffix:semicolon
multiline_comment|/*   */
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
r_void
id|coda_load_creds
c_func
(paren
r_struct
id|CodaCred
op_star
id|cred
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
r_struct
id|super_block
op_star
id|coda_find_super
c_func
(paren
id|kdev_t
id|device
)paren
suffix:semicolon
DECL|macro|INIT_IN
mdefine_line|#define INIT_IN(in, op) &bslash;&n;&t;  (in)-&gt;opcode = (op); &bslash;&n;&t;  (in)-&gt;pid = current-&gt;pid; &bslash;&n;          (in)-&gt;pgid = current-&gt;gid; 
multiline_comment|/* debugging aids */
DECL|macro|coda_panic
mdefine_line|#define coda_panic printk
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
multiline_comment|/* until we are really good, ... */
DECL|macro|coda_panic
mdefine_line|#define coda_panic printk
DECL|macro|CDEBUG
mdefine_line|#define CDEBUG(mask, format, a...)                                &bslash;&n;  do {                                                            &bslash;&n;  if (coda_debug &amp; mask) {                                        &bslash;&n;    printk(&quot;(%s,l. %d): &quot;,  __FUNCTION__, __LINE__);              &bslash;&n;    printk(format, ## a); }                                       &bslash;&n;} while (0) ;                            
DECL|macro|ENTRY
mdefine_line|#define ENTRY    &bslash;&n;    if(coda_print_entry) printk(&quot;Process %d entered %s&bslash;n&quot;,current-&gt;pid,__FUNCTION__)
DECL|macro|EXIT
mdefine_line|#define EXIT    &bslash;&n;    if(coda_print_entry) printk(&quot;Process %d leaving %s&bslash;n&quot;,current-&gt;pid,__FUNCTION__)
multiline_comment|/* inode to cnode */
DECL|macro|ITOC
mdefine_line|#define ITOC(the_inode)  ((struct cnode *)(the_inode)-&gt;u.generic_ip)
multiline_comment|/* cnode to inode */
DECL|macro|CTOI
mdefine_line|#define CTOI(the_cnode)  ((the_cnode)-&gt;c_vnode)
DECL|macro|CHECK_CNODE
mdefine_line|#define CHECK_CNODE(c)                                                &bslash;&n;do {                                                                  &bslash;&n;  struct cnode *cnode = (c);                                          &bslash;&n;  if (!cnode)                                                         &bslash;&n;    coda_panic (&quot;%s(%d): cnode is null&bslash;n&quot;, __FUNCTION__, __LINE__);        &bslash;&n;  if (cnode-&gt;c_magic != CODA_CNODE_MAGIC)                             &bslash;&n;    coda_panic (&quot;%s(%d): cnode magic wrong&bslash;n&quot;, __FUNCTION__, __LINE__);    &bslash;&n;  if (!cnode-&gt;c_vnode)                                                &bslash;&n;    coda_panic (&quot;%s(%d): cnode has null inode&bslash;n&quot;, __FUNCTION__, __LINE__); &bslash;&n;  if ( (struct cnode *)cnode-&gt;c_vnode-&gt;u.generic_ip != cnode )           &bslash;&n;    coda_panic(&quot;AAooh, %s(%d) cnode doesn&squot;t link right!&bslash;n&quot;, __FUNCTION__,__LINE__);&bslash;&n;} while (0);
multiline_comment|/* ioctl stuff */
multiline_comment|/* this needs to be sorted out XXXX */
macro_line|#ifdef&t;__linux__
DECL|macro|IOCPARM_MASK
mdefine_line|#define IOCPARM_MASK 0x0000ffff
macro_line|#endif 
DECL|macro|CODA_ALLOC
mdefine_line|#define CODA_ALLOC(ptr, cast, size)                                       &bslash;&n;do {                                                                      &bslash;&n;    if (size &lt; 3000) {                                                    &bslash;&n;        ptr = (cast)kmalloc((unsigned long) size, GFP_KERNEL);            &bslash;&n;                CDEBUG(D_MALLOC, &quot;kmalloced: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);&bslash;&n;     }  else {                                                             &bslash;&n;        ptr = (cast)vmalloc((unsigned long) size);                        &bslash;&n;&t;CDEBUG(D_MALLOC, &quot;vmalloced: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);}&bslash;&n;    if (ptr == 0) {                                                       &bslash;&n;        coda_panic(&quot;kernel malloc returns 0 at %s:%d&bslash;n&quot;, __FILE__, __LINE__);  &bslash;&n;    }                                                                     &bslash;&n;    memset( ptr, 0, size );                                                   &bslash;&n;} while (0)
DECL|macro|CODA_FREE
mdefine_line|#define CODA_FREE(ptr,size) do {if (size &lt; 3000) { kfree_s((ptr), (size)); CDEBUG(D_MALLOC, &quot;kfreed: %x at %x.&bslash;n&quot;, (int) size, (int) ptr); } else { vfree((ptr)); CDEBUG(D_MALLOC, &quot;vfreed: %x at %x.&bslash;n&quot;, (int) size, (int) ptr);} } while (0)
multiline_comment|/*&n; * Macros to manipulate the queue &n; */
DECL|macro|crfree
mdefine_line|#define crfree(cred) CODA_FREE( (cred), sizeof(struct ucred))
macro_line|#ifndef INIT_QUEUE
DECL|struct|queue
r_struct
id|queue
(brace
DECL|member|forw
DECL|member|back
r_struct
id|queue
op_star
id|forw
comma
op_star
id|back
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_QUEUE
mdefine_line|#define INIT_QUEUE(head)                     &bslash;&n;do {                                         &bslash;&n;    (head).forw = (struct queue *)&amp;(head);   &bslash;&n;    (head).back = (struct queue *)&amp;(head);   &bslash;&n;} while (0)
DECL|macro|GETNEXT
mdefine_line|#define GETNEXT(head) (head).forw
DECL|macro|EMPTY
mdefine_line|#define EMPTY(head) ((head).forw == &amp;(head))
DECL|macro|EOQ
mdefine_line|#define EOQ(el, head) ((struct queue *)(el) == (struct queue *)&amp;(head))
DECL|macro|INSQUE
mdefine_line|#define INSQUE(el, head)                             &bslash;&n;do {                                                 &bslash;&n;&t;(el).forw = ((head).back)-&gt;forw;             &bslash;&n;&t;(el).back = (head).back;                     &bslash;&n;&t;((head).back)-&gt;forw = (struct queue *)&amp;(el); &bslash;&n;&t;(head).back = (struct queue *)&amp;(el);         &bslash;&n;} while (0)
DECL|macro|REMQUE
mdefine_line|#define REMQUE(el)                         &bslash;&n;do {                                       &bslash;&n;&t;((el).forw)-&gt;back = (el).back;     &bslash;&n;&t;(el).back-&gt;forw = (el).forw;       &bslash;&n;}  while (0)
macro_line|#endif INIT_QUEUE
macro_line|#endif _LINUX_CODA_FS
eof
