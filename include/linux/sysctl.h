multiline_comment|/*&n; * sysctl.h: General linux system control interface&n; *&n; * Begun 24 March 1995, Stephen Tweedie&n; */
macro_line|#include &lt;linux/lists.h&gt;
macro_line|#ifndef _LINUX_SYSCTL_H
DECL|macro|_LINUX_SYSCTL_H
mdefine_line|#define _LINUX_SYSCTL_H
DECL|macro|CTL_MAXNAME
mdefine_line|#define CTL_MAXNAME 10
DECL|struct|__sysctl_args
r_struct
id|__sysctl_args
(brace
DECL|member|name
r_int
op_star
id|name
suffix:semicolon
DECL|member|nlen
r_int
id|nlen
suffix:semicolon
DECL|member|oldval
r_void
op_star
id|oldval
suffix:semicolon
DECL|member|oldlenp
r_int
op_star
id|oldlenp
suffix:semicolon
DECL|member|newval
r_void
op_star
id|newval
suffix:semicolon
DECL|member|newlen
r_int
id|newlen
suffix:semicolon
DECL|member|__unused
r_int
r_int
id|__unused
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Define sysctl names first */
multiline_comment|/* Top-level names: */
multiline_comment|/* For internal pattern-matching use only: */
macro_line|#ifdef __KERNEL__
DECL|macro|CTL_ANY
mdefine_line|#define CTL_ANY&t;&t;-1&t;/* Matches any name */
DECL|macro|CTL_NONE
mdefine_line|#define CTL_NONE&t;&t;0
macro_line|#endif
DECL|macro|CTL_KERN
mdefine_line|#define CTL_KERN&t;1&t;/* General kernel info and control */
DECL|macro|CTL_VM
mdefine_line|#define CTL_VM&t;&t;2&t;/* VM management */
DECL|macro|CTL_NET
mdefine_line|#define CTL_NET&t;&t;3&t;/* Networking */
DECL|macro|CTL_PROC
mdefine_line|#define CTL_PROC&t;4&t;/* Process info */
DECL|macro|CTL_FS
mdefine_line|#define CTL_FS&t;&t;5&t;/* Filesystems */
DECL|macro|CTL_DEBUG
mdefine_line|#define CTL_DEBUG&t;6&t;/* Debugging */
DECL|macro|CTL_DEV
mdefine_line|#define CTL_DEV&t;&t;7&t;/* Devices */
DECL|macro|CTL_MAXID
mdefine_line|#define CTL_MAXID&t;8
multiline_comment|/* CTL_KERN names: */
DECL|macro|KERN_OSTYPE
mdefine_line|#define KERN_OSTYPE&t;1&t;/* string: system version */
DECL|macro|KERN_OSRELEASE
mdefine_line|#define KERN_OSRELEASE&t;2&t;/* string: system release */
DECL|macro|KERN_OSREV
mdefine_line|#define KERN_OSREV&t;3&t;/* int: system revision */
DECL|macro|KERN_VERSION
mdefine_line|#define KERN_VERSION&t;4&t;/* string: compile time info */
DECL|macro|KERN_SECUREMASK
mdefine_line|#define KERN_SECUREMASK 5&t;/* struct: maximum rights mask */
DECL|macro|KERN_PROF
mdefine_line|#define KERN_PROF &t;6&t;/* table: profiling information */
DECL|macro|KERN_NODENAME
mdefine_line|#define KERN_NODENAME   7
DECL|macro|KERN_DOMAINNAME
mdefine_line|#define KERN_DOMAINNAME 8
DECL|macro|KERN_NRINODE
mdefine_line|#define KERN_NRINODE&t;9
DECL|macro|KERN_MAXINODE
mdefine_line|#define KERN_MAXINODE&t;10
DECL|macro|KERN_NRFILE
mdefine_line|#define KERN_NRFILE&t;11
DECL|macro|KERN_MAXFILE
mdefine_line|#define KERN_MAXFILE&t;12
DECL|macro|KERN_MAXID
mdefine_line|#define KERN_MAXID&t;13
DECL|macro|KERN_SECURELVL
mdefine_line|#define KERN_SECURELVL&t;14&t;/* int: system security level */
multiline_comment|/* CTL_VM names: */
DECL|macro|VM_SWAPCTL
mdefine_line|#define VM_SWAPCTL&t;1&t;/* struct: Set vm swapping control */
DECL|macro|VM_KSWAPD
mdefine_line|#define VM_KSWAPD&t;2&t;/* struct: control background pagout */
DECL|macro|VM_FREEPG
mdefine_line|#define VM_FREEPG&t;3&t;/* struct: Set free page thresholds */
DECL|macro|VM_MAXID
mdefine_line|#define VM_MAXID&t;4
multiline_comment|/* CTL_NET names: */
multiline_comment|/* CTL_PROC names: */
multiline_comment|/* CTL_FS names: */
multiline_comment|/* CTL_DEBUG names: */
multiline_comment|/* CTL_DEV names: */
macro_line|#ifdef __KERNEL__
r_extern
id|asmlinkage
r_int
id|sys_sysctl
c_func
(paren
r_struct
id|__sysctl_args
op_star
)paren
suffix:semicolon
r_extern
r_void
id|init_sysctl
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ctl_table
r_typedef
r_struct
id|ctl_table
id|ctl_table
suffix:semicolon
DECL|typedef|ctl_handler
r_typedef
r_int
id|ctl_handler
(paren
id|ctl_table
op_star
id|table
comma
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
DECL|typedef|proc_handler
r_typedef
r_int
id|proc_handler
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
r_extern
r_int
id|proc_dostring
c_func
(paren
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|proc_dointvec
c_func
(paren
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|do_sysctl
(paren
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
)paren
suffix:semicolon
r_extern
r_int
id|do_sysctl_strategy
(paren
id|ctl_table
op_star
id|table
comma
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
r_extern
id|ctl_handler
id|sysctl_string
suffix:semicolon
r_extern
r_int
id|do_string
(paren
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_int
id|rdwr
comma
r_char
op_star
id|data
comma
r_int
id|max
)paren
suffix:semicolon
r_extern
r_int
id|do_int
(paren
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_int
id|rdwr
comma
r_int
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|do_struct
(paren
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_int
id|rdwr
comma
r_void
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/*&n; * Register a set of sysctl names by calling register_sysctl_table&n; * with an initialised array of ctl_table&squot;s.  An entry with zero&n; * ctl_name terminates the table.  table-&gt;de will be set up by the&n; * registration and need not be initialised in advance.&n; *&n; * sysctl names can be mirrored automatically under /proc/sys.  The&n; * procname supplied controls /proc naming.&n; *&n; * The table&squot;s mode will be honoured both for sys_sysctl(2) and&n; * proc-fs access.&n; *&n; * Leaf nodes in the sysctl tree will be represented by a single file&n; * under /proc; non-leaf nodes will be represented by directories.  A&n; * null procname disables /proc mirroring at this node.&n; * &n; * sysctl(2) can automatically manage read and write requests through&n; * the sysctl table.  The data and maxlen fields of the ctl_table&n; * struct enable minimal validation of the values being written to be&n; * performed, and the mode field allows minimal authentication.&n; * &n; * More sophisticated management can be enabled by the provision of a&n; * strategy routine with the table entry.  This will be called before&n; * any automatic read or write of the data is performed.&n; * &n; * The strategy routine may return:&n; * &lt;0: Error occurred (error is passed to user process)&n; * 0:  OK - proceed with automatic read or write.&n; * &gt;0: OK - read or write has been done by the strategy routine, so &n; *     return immediately.&n; * &n; * There must be a proc_handler routine for any terminal nodes&n; * mirrored under /proc/sys (non-terminals are handled by a built-in&n; * directory handler).  Several default handlers are available to&n; * cover common cases.&n; */
multiline_comment|/* A sysctl table is an array of struct ctl_table: */
DECL|struct|ctl_table
r_struct
id|ctl_table
(brace
DECL|member|ctl_name
r_int
id|ctl_name
suffix:semicolon
multiline_comment|/* Binary ID */
DECL|member|procname
r_const
r_char
op_star
id|procname
suffix:semicolon
multiline_comment|/* Text ID for /proc/sys, or zero */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|maxlen
r_int
id|maxlen
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|child
id|ctl_table
op_star
id|child
suffix:semicolon
DECL|member|proc_handler
id|proc_handler
op_star
id|proc_handler
suffix:semicolon
multiline_comment|/* Callback for text formatting */
DECL|member|strategy
id|ctl_handler
op_star
id|strategy
suffix:semicolon
multiline_comment|/* Callback function for all r/w */
DECL|member|de
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
multiline_comment|/* /proc control block */
)brace
suffix:semicolon
multiline_comment|/* struct ctl_table_header is used to maintain dynamic lists of&n;   ctl_table trees. */
DECL|struct|ctl_table_header
r_struct
id|ctl_table_header
(brace
DECL|member|ctl_table
id|ctl_table
op_star
id|ctl_table
suffix:semicolon
DECL|member|ctl_entry
id|DLNODE
c_func
(paren
r_struct
id|ctl_table_header
)paren
id|ctl_entry
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|ctl_table_header
op_star
id|register_sysctl_table
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|insert_at_head
)paren
suffix:semicolon
r_void
id|unregister_sysctl_table
c_func
(paren
r_struct
id|ctl_table_header
op_star
id|table
)paren
suffix:semicolon
macro_line|#else /* __KERNEL__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SYSCTL_H */
eof
