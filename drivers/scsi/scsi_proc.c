multiline_comment|/*&n; * linux/drivers/scsi/scsi_proc.c&n; *&n; * The functions in this file provide an interface between&n; * the PROC file system and the SCSI device drivers&n; * It is mainly used for debugging, statistics and to pass &n; * information directly to the lowlevel driver.&n; *&n; * (c) 1995 Michael Neuffer neuffer@goofy.zdv.uni-mainz.de &n; * Version: 0.99.8   last change: 95/09/13&n; * &n; * generic command parser provided by: &n; * Andreas Heilwagen &lt;crashcar@informatik.uni-koblenz.de&gt;&n; *&n; * generic_proc_info() support of xxxx_info() by:&n; * Michael A. Griffith &lt;grif@acm.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;&t;/* for CONFIG_PROC_FS */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* generic_proc_info&n; * Used if the driver currently has no own support for /proc/scsi&n; */
DECL|function|generic_proc_info
r_int
id|generic_proc_info
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
r_const
r_char
op_star
(paren
op_star
id|info
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
comma
r_struct
id|Scsi_Host
op_star
id|sh
)paren
(brace
r_int
id|len
comma
id|pos
comma
id|begin
suffix:semicolon
id|begin
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|info
op_logical_and
id|sh
)paren
(brace
id|pos
op_assign
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|info
c_func
(paren
id|sh
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|pos
op_assign
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;The driver does not yet support the proc-fs&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* dispatch_scsi_info is the central dispatcher &n; * It is the interface between the proc-fs and the SCSI subsystem code&n; */
DECL|function|proc_scsi_read
r_static
r_int
id|proc_scsi_read
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
(brace
r_struct
id|Scsi_Host
op_star
id|hpnt
op_assign
id|data
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|hpnt-&gt;hostt-&gt;proc_info
op_eq
l_int|NULL
)paren
id|n
op_assign
id|generic_proc_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
id|hpnt-&gt;hostt-&gt;info
comma
id|hpnt
)paren
suffix:semicolon
r_else
id|n
op_assign
(paren
id|hpnt-&gt;hostt
op_member_access_from_pointer
id|proc_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
id|hpnt-&gt;host_no
comma
l_int|0
)paren
)paren
suffix:semicolon
op_star
id|eof
op_assign
(paren
id|n
OL
id|length
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE (3*1024)     /* 4K page size, but our output routines &n;&t;&t;&t;&t;      * use some slack for overruns &n;&t;&t;&t;&t;      */
DECL|function|proc_scsi_write
r_static
id|ssize_t
id|proc_scsi_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|hpnt
op_assign
id|data
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PROC_BLOCK_SIZE
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|copy_from_user
c_func
(paren
id|page
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hpnt-&gt;hostt-&gt;proc_info
op_eq
l_int|NULL
)paren
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_else
id|ret
op_assign
id|hpnt-&gt;hostt
op_member_access_from_pointer
id|proc_info
c_func
(paren
id|page
comma
op_amp
id|start
comma
l_int|0
comma
id|count
comma
id|hpnt-&gt;host_no
comma
l_int|1
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
id|ulong
)paren
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|build_proc_dir_entries
r_void
id|build_proc_dir_entries
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|hpnt
suffix:semicolon
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* see scsi_unregister_host() */
id|tpnt-&gt;proc_dir
op_assign
id|proc_mkdir
c_func
(paren
id|tpnt-&gt;proc_name
comma
id|proc_scsi
)paren
suffix:semicolon
id|tpnt-&gt;proc_dir-&gt;owner
op_assign
id|tpnt-&gt;module
suffix:semicolon
id|hpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_while
c_loop
(paren
id|hpnt
)paren
(brace
r_if
c_cond
(paren
id|tpnt
op_eq
id|hpnt-&gt;hostt
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|hpnt-&gt;host_no
)paren
suffix:semicolon
id|p
op_assign
id|create_proc_read_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|tpnt-&gt;proc_dir
comma
id|proc_scsi_read
comma
(paren
r_void
op_star
)paren
id|hpnt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|panic
c_func
(paren
l_string|&quot;Not enough memory to register SCSI HBA in /proc/scsi !&bslash;n&quot;
)paren
suffix:semicolon
id|p-&gt;write_proc
op_assign
id|proc_scsi_write
suffix:semicolon
id|p-&gt;owner
op_assign
id|tpnt-&gt;module
suffix:semicolon
)brace
id|hpnt
op_assign
id|hpnt-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  parseHandle *parseInit(char *buf, char *cmdList, int cmdNum); &n; *              gets a pointer to a null terminated data buffer&n; *              and a list of commands with blanks as delimiter &n; *      in between. &n; *      The commands have to be alphanumerically sorted. &n; *      cmdNum has to contain the number of commands.&n; *              On success, a pointer to a handle structure&n; *              is returned, NULL on failure&n; *&n; *      int parseOpt(parseHandle *handle, char **param);&n; *              processes the next parameter. On success, the&n; *              index of the appropriate command in the cmdList&n; *              is returned, starting with zero.&n; *              param points to the null terminated parameter string.&n; *              On failure, -1 is returned.&n; *&n; *      The databuffer buf may only contain pairs of commands&n; *          options, separated by blanks:&n; *              &lt;Command&gt; &lt;Parameter&gt; [&lt;Command&gt; &lt;Parameter&gt;]*&n; */
r_typedef
r_struct
(brace
DECL|member|buf
r_char
op_star
id|buf
comma
multiline_comment|/* command buffer  */
DECL|member|cmdList
op_star
id|cmdList
comma
multiline_comment|/* command list    */
DECL|member|bufPos
op_star
id|bufPos
comma
multiline_comment|/* actual position */
DECL|member|cmdPos
op_star
op_star
id|cmdPos
comma
multiline_comment|/* cmdList index   */
DECL|member|cmdNum
id|cmdNum
suffix:semicolon
multiline_comment|/* cmd number      */
DECL|typedef|parseHandle
)brace
id|parseHandle
suffix:semicolon
DECL|function|parseFree
r_inline
r_int
id|parseFree
c_func
(paren
id|parseHandle
op_star
id|handle
)paren
(brace
multiline_comment|/* free memory     */
id|kfree
c_func
(paren
id|handle-&gt;cmdPos
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|parseInit
id|parseHandle
op_star
id|parseInit
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|cmdList
comma
r_int
id|cmdNum
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* temp pointer    */
id|parseHandle
op_star
id|handle
suffix:semicolon
multiline_comment|/* new handle      */
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
op_logical_neg
id|cmdList
)paren
multiline_comment|/* bad input ?     */
r_return
l_int|NULL
suffix:semicolon
id|handle
op_assign
(paren
id|parseHandle
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|parseHandle
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* out of memory   */
id|handle-&gt;cmdPos
op_assign
(paren
r_char
op_star
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_int
)paren
op_star
id|cmdNum
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle-&gt;cmdPos
)paren
(brace
id|kfree
c_func
(paren
id|handle
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* out of memory   */
)brace
id|handle-&gt;buf
op_assign
id|handle-&gt;bufPos
op_assign
id|buf
suffix:semicolon
multiline_comment|/* init handle     */
id|handle-&gt;cmdList
op_assign
id|cmdList
suffix:semicolon
id|handle-&gt;cmdNum
op_assign
id|cmdNum
suffix:semicolon
id|handle-&gt;cmdPos
(braket
id|cmdNum
op_assign
l_int|0
)braket
op_assign
id|cmdList
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|cmdList
suffix:semicolon
op_star
id|ptr
suffix:semicolon
id|ptr
op_increment
)paren
(brace
multiline_comment|/* scan command string */
r_if
c_cond
(paren
op_star
id|ptr
op_eq
l_char|&squot; &squot;
)paren
(brace
multiline_comment|/* and insert zeroes   */
op_star
id|ptr
op_increment
op_assign
l_int|0
suffix:semicolon
id|handle-&gt;cmdPos
(braket
op_increment
id|cmdNum
)braket
op_assign
id|ptr
op_increment
suffix:semicolon
)brace
)brace
r_return
id|handle
suffix:semicolon
)brace
DECL|function|parseOpt
r_int
id|parseOpt
c_func
(paren
id|parseHandle
op_star
id|handle
comma
r_char
op_star
op_star
id|param
)paren
(brace
r_int
id|cmdIndex
op_assign
l_int|0
comma
id|cmdLen
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|startPos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
multiline_comment|/* invalid handle  */
r_return
(paren
id|parseFree
c_func
(paren
id|handle
)paren
)paren
suffix:semicolon
multiline_comment|/* skip spaces     */
r_for
c_loop
(paren
suffix:semicolon
op_star
(paren
id|handle-&gt;bufPos
)paren
op_logical_and
op_star
(paren
id|handle-&gt;bufPos
)paren
op_eq
l_char|&squot; &squot;
suffix:semicolon
id|handle-&gt;bufPos
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
(paren
id|handle-&gt;bufPos
)paren
)paren
r_return
(paren
id|parseFree
c_func
(paren
id|handle
)paren
)paren
suffix:semicolon
multiline_comment|/* end of data     */
id|startPos
op_assign
id|handle-&gt;bufPos
suffix:semicolon
multiline_comment|/* store cmd start */
r_for
c_loop
(paren
suffix:semicolon
id|handle-&gt;cmdPos
(braket
id|cmdIndex
)braket
(braket
id|cmdLen
)braket
op_logical_and
op_star
(paren
id|handle-&gt;bufPos
)paren
suffix:semicolon
id|handle-&gt;bufPos
op_increment
)paren
(brace
multiline_comment|/* no string end?  */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_star
(paren
id|handle-&gt;bufPos
)paren
op_eq
id|handle-&gt;cmdPos
(braket
id|cmdIndex
)braket
(braket
id|cmdLen
)braket
)paren
r_break
suffix:semicolon
multiline_comment|/* char matches ?  */
r_else
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|startPos
comma
(paren
r_char
op_star
)paren
(paren
id|handle-&gt;cmdPos
(braket
op_increment
id|cmdIndex
)braket
)paren
comma
id|cmdLen
)paren
)paren
r_return
(paren
id|parseFree
c_func
(paren
id|handle
)paren
)paren
suffix:semicolon
multiline_comment|/* unknown command */
r_if
c_cond
(paren
id|cmdIndex
op_ge
id|handle-&gt;cmdNum
)paren
r_return
(paren
id|parseFree
c_func
(paren
id|handle
)paren
)paren
suffix:semicolon
multiline_comment|/* unknown command */
)brace
id|cmdLen
op_increment
suffix:semicolon
multiline_comment|/* next char       */
)brace
multiline_comment|/* Get param. First skip all blanks, then insert zero after param  */
r_for
c_loop
(paren
suffix:semicolon
op_star
(paren
id|handle-&gt;bufPos
)paren
op_logical_and
op_star
(paren
id|handle-&gt;bufPos
)paren
op_eq
l_char|&squot; &squot;
suffix:semicolon
id|handle-&gt;bufPos
op_increment
)paren
suffix:semicolon
op_star
id|param
op_assign
id|handle-&gt;bufPos
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
(paren
id|handle-&gt;bufPos
)paren
op_logical_and
op_star
(paren
id|handle-&gt;bufPos
)paren
op_ne
l_char|&squot; &squot;
suffix:semicolon
id|handle-&gt;bufPos
op_increment
)paren
suffix:semicolon
op_star
(paren
id|handle-&gt;bufPos
op_increment
)paren
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|cmdIndex
)paren
suffix:semicolon
)brace
DECL|function|proc_print_scsidevice
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
id|scd
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|size
comma
r_int
id|len
)paren
(brace
r_int
id|x
comma
id|y
op_assign
op_star
id|size
suffix:semicolon
r_extern
r_const
r_char
op_star
r_const
id|scsi_device_types
(braket
id|MAX_SCSI_DEVICE_CODE
)braket
suffix:semicolon
id|y
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Host: scsi%d Channel: %02d Id: %02d Lun: %02d&bslash;n  Vendor: &quot;
comma
id|scd-&gt;host-&gt;host_no
comma
id|scd-&gt;channel
comma
id|scd-&gt;id
comma
id|scd-&gt;lun
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|8
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scd-&gt;vendor
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|scd-&gt;vendor
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; Model: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|16
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scd-&gt;model
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|scd-&gt;model
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; Rev: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
l_int|4
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|scd-&gt;rev
(braket
id|x
)braket
op_ge
l_int|0x20
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;%c&quot;
comma
id|scd-&gt;rev
(braket
id|x
)braket
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;  Type:   %s &quot;
comma
id|scd-&gt;type
OL
id|MAX_SCSI_DEVICE_CODE
ques
c_cond
id|scsi_device_types
(braket
(paren
r_int
)paren
id|scd-&gt;type
)braket
suffix:colon
l_string|&quot;Unknown          &quot;
)paren
suffix:semicolon
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;               ANSI&quot;
l_string|&quot; SCSI revision: %02x&quot;
comma
(paren
id|scd-&gt;scsi_level
op_minus
l_int|1
)paren
ques
c_cond
id|scd-&gt;scsi_level
op_minus
l_int|1
suffix:colon
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scd-&gt;scsi_level
op_eq
l_int|2
)paren
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot; CCS&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|y
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
op_plus
id|y
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|size
op_assign
id|y
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#else&t;&t;&t;&t;/* if !CONFIG_PROC_FS */
DECL|function|proc_print_scsidevice
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
id|scd
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|size
comma
r_int
id|len
)paren
(brace
)brace
macro_line|#endif&t;&t;&t;&t;/* CONFIG_PROC_FS */
multiline_comment|/*&n; * Overrides for Emacs so that we get a uniform tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
