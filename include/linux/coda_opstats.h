macro_line|#ifndef _BLURB_
DECL|macro|_BLURB_
mdefine_line|#define _BLURB_
multiline_comment|/*&n;&n;            Coda: an Experimental Distributed File System&n;                             Release 3.1&n;&n;          Copyright (c) 1987-1996 Carnegie Mellon University&n;                         All Rights Reserved&n;&n;Permission  to  use, copy, modify and distribute this software and its&n;documentation is hereby granted,  provided  that  both  the  copyright&n;notice  and  this  permission  notice  appear  in  all  copies  of the&n;software, derivative works or  modified  versions,  and  any  portions&n;thereof, and that both notices appear in supporting documentation, and&n;that credit is given to Carnegie Mellon University  in  all  documents&n;and publicity pertaining to direct or indirect use of this code or its&n;derivatives.&n;&n;CODA IS AN EXPERIMENTAL SOFTWARE SYSTEM AND IS  KNOWN  TO  HAVE  BUGS,&n;SOME  OF  WHICH MAY HAVE SERIOUS CONSEQUENCES.  CARNEGIE MELLON ALLOWS&n;FREE USE OF THIS SOFTWARE IN ITS &quot;AS IS&quot; CONDITION.   CARNEGIE  MELLON&n;DISCLAIMS  ANY  LIABILITY  OF  ANY  KIND  FOR  ANY  DAMAGES WHATSOEVER&n;RESULTING DIRECTLY OR INDIRECTLY FROM THE USE OF THIS SOFTWARE  OR  OF&n;ANY DERIVATIVE WORK.&n;&n;Carnegie  Mellon  encourages  users  of  this  software  to return any&n;improvements or extensions that  they  make,  and  to  grant  Carnegie&n;Mellon the rights to redistribute these changes without encumbrance.&n;*/
DECL|variable|rcsid
r_static
r_char
op_star
id|rcsid
op_assign
l_string|&quot;$Header: /afs/cs/project/coda-src/cvs/coda/kernel-src/vfs/linux/cfs_opstats.h,v 4.1 1997/01/08 21:53:19 rvb Exp $&quot;
suffix:semicolon
macro_line|#endif /*_BLURB_*/
multiline_comment|/*&n; * operation stats: what the minicache can intercept that&n; * *isn&squot;t* seen by venus.  These stats are kept to augment&n; * the stats maintained by the Volume-Session mechanism.&n; */
multiline_comment|/* vfsops:&n; *          mount: not currently bounced to Venus&n; *          umount: nope&n; *          root: only first call, rest is cached.&n; *          statfs: none (bogus)&n; *          sync: none (bogus)&n; *          vget: all&n; */
DECL|macro|CFS_MOUNT_STATS
mdefine_line|#define CFS_MOUNT_STATS  0
DECL|macro|CFS_UMOUNT_STATS
mdefine_line|#define CFS_UMOUNT_STATS 1
DECL|macro|CFS_ROOT_STATS
mdefine_line|#define CFS_ROOT_STATS   2
DECL|macro|CFS_STATFS_STATS
mdefine_line|#define CFS_STATFS_STATS 3
DECL|macro|CFS_SYNC_STATS
mdefine_line|#define CFS_SYNC_STATS   4
DECL|macro|CFS_VGET_STATS
mdefine_line|#define CFS_VGET_STATS   5
DECL|macro|CFS_VFSOPS_SIZE
mdefine_line|#define CFS_VFSOPS_SIZE  6
multiline_comment|/* vnodeops:&n; *            open: all to venus&n; *            close: all to venus&n; *            rdrw: bogus.  Maybe redirected to UFS.&n; *                          May call open/close for internal opens/closes&n; *                          (Does exec not call open?)&n; *            ioctl: causes a lookupname&n; *                   passes through&n; *            select: can&squot;t get there from here.&n; *            getattr: can be satsified by cache&n; *            setattr: all go through&n; *            access: can be satisfied by cache&n; *            readlink: can be satisfied by cache&n; *            fsync: passes through&n; *            inactive: passes through&n; *            lookup: can be satisfied by cache&n; *            create: passes through&n; *            remove: passes through&n; *            link: passes through&n; *            rename: passes through&n; *            mkdir: passes through&n; *            rmdir: passes through&n; *            symlink: passes through&n; *            readdir: may be redirected to UFS&n; *                     may cause an &quot;internal&quot; open/close&n; */
DECL|macro|CFS_OPEN_STATS
mdefine_line|#define CFS_OPEN_STATS     0
DECL|macro|CFS_CLOSE_STATS
mdefine_line|#define CFS_CLOSE_STATS    1
DECL|macro|CFS_RDWR_STATS
mdefine_line|#define CFS_RDWR_STATS     2
DECL|macro|CFS_IOCTL_STATS
mdefine_line|#define CFS_IOCTL_STATS    3
DECL|macro|CFS_SELECT_STATS
mdefine_line|#define CFS_SELECT_STATS   4
DECL|macro|CFS_GETATTR_STATS
mdefine_line|#define CFS_GETATTR_STATS  5
DECL|macro|CFS_SETATTR_STATS
mdefine_line|#define CFS_SETATTR_STATS  6
DECL|macro|CFS_ACCESS_STATS
mdefine_line|#define CFS_ACCESS_STATS   7
DECL|macro|CFS_READLINK_STATS
mdefine_line|#define CFS_READLINK_STATS 8
DECL|macro|CFS_FSYNC_STATS
mdefine_line|#define CFS_FSYNC_STATS    9
DECL|macro|CFS_INACTIVE_STATS
mdefine_line|#define CFS_INACTIVE_STATS 10
DECL|macro|CFS_LOOKUP_STATS
mdefine_line|#define CFS_LOOKUP_STATS   11
DECL|macro|CFS_CREATE_STATS
mdefine_line|#define CFS_CREATE_STATS   12
DECL|macro|CFS_REMOVE_STATS
mdefine_line|#define CFS_REMOVE_STATS   13
DECL|macro|CFS_LINK_STATS
mdefine_line|#define CFS_LINK_STATS     14
DECL|macro|CFS_RENAME_STATS
mdefine_line|#define CFS_RENAME_STATS   15
DECL|macro|CFS_MKDIR_STATS
mdefine_line|#define CFS_MKDIR_STATS    16
DECL|macro|CFS_RMDIR_STATS
mdefine_line|#define CFS_RMDIR_STATS    17
DECL|macro|CFS_SYMLINK_STATS
mdefine_line|#define CFS_SYMLINK_STATS  18
DECL|macro|CFS_READDIR_STATS
mdefine_line|#define CFS_READDIR_STATS  19
DECL|macro|CFS_VNODEOPS_SIZE
mdefine_line|#define CFS_VNODEOPS_SIZE  20
multiline_comment|/*&n; * I propose the following structres:&n; */
DECL|struct|cfs_op_stats
r_struct
id|cfs_op_stats
(brace
DECL|member|opcode
r_int
id|opcode
suffix:semicolon
multiline_comment|/* vfs opcode */
DECL|member|entries
r_int
id|entries
suffix:semicolon
multiline_comment|/* number of times call attempted */
DECL|member|sat_intrn
r_int
id|sat_intrn
suffix:semicolon
multiline_comment|/* number of times call satisfied by cache */
DECL|member|unsat_intrn
r_int
id|unsat_intrn
suffix:semicolon
multiline_comment|/* number of times call failed in cache, but&n;                         was not bounced to venus proper. */
DECL|member|gen_intrn
r_int
id|gen_intrn
suffix:semicolon
multiline_comment|/* number of times call generated internally */
multiline_comment|/* (do we need that?) */
)brace
suffix:semicolon
multiline_comment|/*&n; * With each call to the minicache, we&squot;ll bump the counters whenver&n; * a call is satisfied internally (through the cache or through a&n; * redirect), and whenever an operation is caused internally.&n; * Then, we can add the total operations caught by the minicache&n; * to the world-wide totals, and leave a caveat for the specific&n; * graphs later.&n; */
eof
