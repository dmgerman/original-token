multiline_comment|/*&n; * This is &lt;linux/capability.h&gt;&n; *&n; * Andrew G. Morgan &lt;morgan@parc.power.net&gt;&n; * Alexander Kjeldaas &lt;astor@guardian.no&gt;&n; * with help from Aleph1, Roland Buresund and Andrew Main.&n; */
macro_line|#ifndef _LINUX_CAPABILITY_H
DECL|macro|_LINUX_CAPABILITY_H
mdefine_line|#define _LINUX_CAPABILITY_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/* User-level do most of the mapping between kernel and user&n;   capabilities based on the version tag given by the kernel. The&n;   kernel might be somewhat backwards compatible, but don&squot;t bet on&n;   it. */
DECL|macro|_LINUX_CAPABILITY_VERSION
mdefine_line|#define _LINUX_CAPABILITY_VERSION  0x19980330
DECL|struct|_user_cap_struct
r_typedef
r_struct
id|_user_cap_struct
(brace
DECL|member|version
id|__u32
id|version
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|cap
id|__u8
id|cap
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|cap_t
)brace
op_star
id|cap_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|kernel_cap_struct
r_typedef
r_struct
id|kernel_cap_struct
(brace
DECL|member|cap
r_int
id|cap
suffix:semicolon
DECL|typedef|kernel_cap_t
)brace
id|kernel_cap_t
suffix:semicolon
macro_line|#endif
multiline_comment|/**&n; ** POSIX-draft defined capabilities. &n; **/
multiline_comment|/* In a system with the [_POSIX_CHOWN_RESTRICTED] option defined, this&n;   overrides the restriction of changing file ownership and group&n;   ownership. */
DECL|macro|CAP_CHOWN
mdefine_line|#define CAP_CHOWN            0
multiline_comment|/* Override all DAC access, including ACL execute access if&n;   [_POSIX_ACL] is defined. Excluding DAC access covered by&n;   CAP_LINUX_IMMUTABLE */
DECL|macro|CAP_DAC_OVERRIDE
mdefine_line|#define CAP_DAC_OVERRIDE     1
multiline_comment|/* Overrides all DAC restrictions regarding read and search on files&n;   and directories, including ACL restrictions if [_POSIX_ACL] is&n;   defined. Excluding DAC access covered by CAP_LINUX_IMMUTABLE */
DECL|macro|CAP_DAC_READ_SEARCH
mdefine_line|#define CAP_DAC_READ_SEARCH  2
multiline_comment|/* Overrides all restrictions about allowed operations on files, where&n;   file owner ID must be equal to the user ID, except where CAP_FSETID&n;   is applicable. It doesn&squot;t override MAC and DAC restrictions. */
DECL|macro|CAP_FOWNER
mdefine_line|#define CAP_FOWNER           3
multiline_comment|/* Overrides the following restrictions that the effective user ID&n;   shall match the file owner ID when setting the S_ISUID and S_ISGID&n;   bits on that file; that the effective group ID (or one of the&n;   supplementary group IDs shall match the file owner ID when setting&n;   the S_ISGID bit on that file; that the S_ISUID and S_ISGID bits are&n;   cleared on successful return from chown(2). */
DECL|macro|CAP_FSETID
mdefine_line|#define CAP_FSETID           4
multiline_comment|/* Used to decide between falling back on the old suser() or fsuser(). */
DECL|macro|CAP_FS_MASK
mdefine_line|#define CAP_FS_MASK          0x1f
multiline_comment|/* Overrides the restriction that the real or effective user ID of a&n;   process sending a signal must match the real or effective user ID&n;   of the process receiving the signal. */
DECL|macro|CAP_KILL
mdefine_line|#define CAP_KILL             5
multiline_comment|/* Allows setgid(2) manipulation */
DECL|macro|CAP_SETGID
mdefine_line|#define CAP_SETGID           6
multiline_comment|/* Allows setuid(2) manipulation */
DECL|macro|CAP_SETUID
mdefine_line|#define CAP_SETUID           7
multiline_comment|/**&n; ** Linux-specific capabilities&n; **/
multiline_comment|/* Transfer any capability in your permitted set to any pid,&n;   remove any capability in your permitted set from any pid */
DECL|macro|CAP_SETPCAP
mdefine_line|#define CAP_SETPCAP          8
multiline_comment|/* Allow modification of S_IMMUTABLE and S_APPEND file attributes */
DECL|macro|CAP_LINUX_IMMUTABLE
mdefine_line|#define CAP_LINUX_IMMUTABLE  9
multiline_comment|/* Allows binding to TCP/UDP sockets below 1024 */
DECL|macro|CAP_NET_BIND_SERVICE
mdefine_line|#define CAP_NET_BIND_SERVICE 10
multiline_comment|/* Allow broadcasting, listen to multicast */
DECL|macro|CAP_NET_BROADCAST
mdefine_line|#define CAP_NET_BROADCAST    11
multiline_comment|/* Allow interface configuration */
multiline_comment|/* Allow configuring of firewall stuff */
multiline_comment|/* Allow setting debug option on sockets */
multiline_comment|/* Allow modification of routing tables */
DECL|macro|CAP_NET_ADMIN
mdefine_line|#define CAP_NET_ADMIN        12
multiline_comment|/* Allow use of RAW sockets */
multiline_comment|/* Allow use of PACKET sockets */
DECL|macro|CAP_NET_RAW
mdefine_line|#define CAP_NET_RAW          13
multiline_comment|/* Allow locking of segments in memory */
DECL|macro|CAP_IPC_LOCK
mdefine_line|#define CAP_IPC_LOCK         14
multiline_comment|/* Override IPC ownership checks */
DECL|macro|CAP_IPC_OWNER
mdefine_line|#define CAP_IPC_OWNER        15
multiline_comment|/* Insert and remove kernel modules */
DECL|macro|CAP_SYS_MODULE
mdefine_line|#define CAP_SYS_MODULE       16
multiline_comment|/* Allow ioperm/iopl access */
DECL|macro|CAP_SYS_RAWIO
mdefine_line|#define CAP_SYS_RAWIO        17
multiline_comment|/* Allow use of chroot() */
DECL|macro|CAP_SYS_CHROOT
mdefine_line|#define CAP_SYS_CHROOT       18
multiline_comment|/* Allow ptrace() of any process */
DECL|macro|CAP_SYS_PTRACE
mdefine_line|#define CAP_SYS_PTRACE       19
multiline_comment|/* Allow configuration of process accounting */
DECL|macro|CAP_SYS_PACCT
mdefine_line|#define CAP_SYS_PACCT        20
multiline_comment|/* Allow configuration of the secure attention key */
multiline_comment|/* Allow administration of the random device */
multiline_comment|/* Allow device administration */
multiline_comment|/* Allow examination and configuration of disk quotas */
multiline_comment|/* System Admin functions: mount et al */
DECL|macro|CAP_SYS_ADMIN
mdefine_line|#define CAP_SYS_ADMIN        21
multiline_comment|/* Allow use of reboot() */
DECL|macro|CAP_SYS_BOOT
mdefine_line|#define CAP_SYS_BOOT         22
multiline_comment|/* Allow use of renice() on others, and raising of priority */
DECL|macro|CAP_SYS_NICE
mdefine_line|#define CAP_SYS_NICE         23
multiline_comment|/* Override resource limits */
DECL|macro|CAP_SYS_RESOURCE
mdefine_line|#define CAP_SYS_RESOURCE     24
multiline_comment|/* Allow manipulation of system clock */
DECL|macro|CAP_SYS_TIME
mdefine_line|#define CAP_SYS_TIME         25
multiline_comment|/* Allow configuration of tty devices */
DECL|macro|CAP_SYS_TTY_CONFIG
mdefine_line|#define CAP_SYS_TTY_CONFIG   26
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Internal kernel functions only&n; */
DECL|macro|CAP_EMPTY_SET
mdefine_line|#define CAP_EMPTY_SET       {  0 }
DECL|macro|CAP_FULL_SET
mdefine_line|#define CAP_FULL_SET        { ~0 }
DECL|macro|CAP_TO_MASK
mdefine_line|#define CAP_TO_MASK(x) (1 &lt;&lt; (x))
DECL|macro|cap_raise
mdefine_line|#define cap_raise(c, flag)   (c.cap |=  CAP_TO_MASK(flag))
DECL|macro|cap_lower
mdefine_line|#define cap_lower(c, flag)   (c.cap &amp;= ~CAP_TO_MASK(flag))
DECL|macro|cap_raised
mdefine_line|#define cap_raised(c, flag)  (c.cap &amp;   CAP_TO_MASK(flag))
DECL|macro|cap_isclear
mdefine_line|#define cap_isclear(c) (!c.cap)
DECL|macro|cap_copy
mdefine_line|#define cap_copy(dest,src) do { (dest).cap = (src).cap; } while(0)
DECL|macro|cap_clear
mdefine_line|#define cap_clear(c)       do {  c.cap =  0; } while(0)
DECL|macro|cap_set_full
mdefine_line|#define cap_set_full(c)    do {  c.cap = ~0; } while(0)
DECL|macro|cap_is_fs_cap
mdefine_line|#define cap_is_fs_cap(c)     ((c) &amp; CAP_FS_MASK)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !_LINUX_CAPABILITY_H */
eof
