macro_line|#ifndef _LINUX_HIGHUID_H
DECL|macro|_LINUX_HIGHUID_H
mdefine_line|#define _LINUX_HIGHUID_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * general notes:&n; *&n; * UID16_COMPAT_NEEDED is defined in include/asm-{arch}/posix_types.h&n; * if the given architecture needs to support backwards compatibility&n; * for old system calls.&n; *&n; * old_uid_t and old_gid_t are only used if UID16_COMPAT_NEEDED&n; * is defined.&n; *&n; * uid16_t and gid16_t are used on all architectures. (when dealing&n; * with structures hard coded to 16 bits, such as in filesystems)&n; */
macro_line|#ifdef UID16_COMPAT_NEEDED
multiline_comment|/*&n; * This is the &quot;overflow&quot; UID and GID. They are used to signify uid/gid&n; * overflow to old programs when they request uid/gid information but are&n; * using the old 16 bit interfaces.&n; * When you run a libc5 program, it will think that all highuid files or&n; * processes are owned by this uid/gid.&n; * The idea is that it&squot;s better to do so than possibly return 0 in lieu of&n; * 65536, etc.&n; */
r_extern
r_int
id|overflowuid
suffix:semicolon
r_extern
r_int
id|overflowgid
suffix:semicolon
DECL|macro|DEFAULT_OVERFLOWUID
mdefine_line|#define DEFAULT_OVERFLOWUID&t;65534
DECL|macro|DEFAULT_OVERFLOWGID
mdefine_line|#define DEFAULT_OVERFLOWGID&t;65534
multiline_comment|/* prevent uid mod 65536 effect by returning a default value for high UIDs */
DECL|macro|high2lowuid
mdefine_line|#define high2lowuid(uid) ((uid) &gt; 65535) ? (old_uid_t)overflowuid : (old_uid_t)(uid)
DECL|macro|high2lowgid
mdefine_line|#define high2lowgid(gid) ((gid) &gt; 65535) ? (old_gid_t)overflowgid : (old_gid_t)(gid)
multiline_comment|/*&n; * -1 is different in 16 bits than it is in 32 bits&n; * these macros are used by chown(), setreuid(), ...,&n; */
DECL|macro|low2highuid
mdefine_line|#define low2highuid(uid) ((uid) == (old_uid_t)-1) ? (uid_t)-1 : (uid_t)(uid)
DECL|macro|low2highgid
mdefine_line|#define low2highgid(gid) ((gid) == (old_gid_t)-1) ? (gid_t)-1 : (gid_t)(gid)
multiline_comment|/* Avoid extra ifdefs with these macros */
DECL|macro|SET_UID16
mdefine_line|#define SET_UID16(var, uid)&t;var = high2lowuid(uid)
DECL|macro|SET_GID16
mdefine_line|#define SET_GID16(var, gid)&t;var = high2lowgid(gid)
DECL|macro|NEW_TO_OLD_UID
mdefine_line|#define NEW_TO_OLD_UID(uid)&t;high2lowuid(uid)
DECL|macro|NEW_TO_OLD_GID
mdefine_line|#define NEW_TO_OLD_GID(gid)&t;high2lowgid(gid)
DECL|macro|SET_OLDSTAT_UID
mdefine_line|#define SET_OLDSTAT_UID(stat, uid)&t;(stat).st_uid = high2lowuid(uid)
DECL|macro|SET_OLDSTAT_GID
mdefine_line|#define SET_OLDSTAT_GID(stat, gid)&t;(stat).st_gid = high2lowgid(gid)
DECL|macro|SET_STAT_UID
mdefine_line|#define SET_STAT_UID(stat, uid)&t;&t;(stat).st_uid = high2lowuid(uid)
DECL|macro|SET_STAT_GID
mdefine_line|#define SET_STAT_GID(stat, gid)&t;&t;(stat).st_gid = high2lowgid(gid)
macro_line|#else
DECL|macro|SET_UID16
mdefine_line|#define SET_UID16(var, uid)&t;do { ; } while (0)
DECL|macro|SET_GID16
mdefine_line|#define SET_GID16(var, gid)&t;do { ; } while (0)
DECL|macro|NEW_TO_OLD_UID
mdefine_line|#define NEW_TO_OLD_UID(uid)&t;uid
DECL|macro|NEW_TO_OLD_GID
mdefine_line|#define NEW_TO_OLD_GID(gid)&t;gid
DECL|macro|SET_OLDSTAT_UID
mdefine_line|#define SET_OLDSTAT_UID(stat, uid)&t;(stat).st_uid = uid
DECL|macro|SET_OLDSTAT_GID
mdefine_line|#define SET_OLDSTAT_GID(stat, gid)&t;(stat).st_gid = gid
DECL|macro|SET_STAT_UID
mdefine_line|#define SET_STAT_UID(stat, uid)&t;&t;(stat).st_uid = uid
DECL|macro|SET_STAT_GID
mdefine_line|#define SET_STAT_GID(stat, gid)&t;&t;(stat).st_gid = gid
DECL|macro|high2lowuid
mdefine_line|#define high2lowuid(x)&t;&t;(x)
macro_line|#endif /* UID16_COMPAT_NEEDED */
multiline_comment|/*&n; * Everything below this line is needed on all architectures, to deal with&n; * filesystems that only store 16 bits of the UID/GID, etc.&n; */
multiline_comment|/*&n; * This is the UID and GID that will get written to disk if a filesystem&n; * only supports 16-bit UIDs and the kernel has a high UID/GID to write&n; */
r_extern
r_int
id|fs_overflowuid
suffix:semicolon
r_extern
r_int
id|fs_overflowgid
suffix:semicolon
DECL|macro|DEFAULT_FS_OVERFLOWUID
mdefine_line|#define DEFAULT_FS_OVERFLOWUID&t;65534
DECL|macro|DEFAULT_FS_OVERFLOWGID
mdefine_line|#define DEFAULT_FS_OVERFLOWGID&t;65534
multiline_comment|/*&n; * Since these macros are used in architectures that only need limited&n; * 16-bit UID back compatibility, we won&squot;t use old_uid_t and old_gid_t&n; */
DECL|macro|fs_high2lowuid
mdefine_line|#define fs_high2lowuid(uid) (uid &gt; 65535) ? (uid16_t)fs_overflowuid : (uid16_t)uid
DECL|macro|fs_high2lowgid
mdefine_line|#define fs_high2lowgid(gid) (gid &gt; 65535) ? (gid16_t)fs_overflowgid : (gid16_t)gid
DECL|macro|low_16_bits
mdefine_line|#define low_16_bits(x)&t;x &amp; 0xFFFF
DECL|macro|high_16_bits
mdefine_line|#define high_16_bits(x)&t;(x &amp; 0xFFFF0000) &gt;&gt; 16
macro_line|#endif /* _LINUX_HIGHUID_H */
eof
