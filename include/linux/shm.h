macro_line|#ifndef _LINUX_SHM_H_
DECL|macro|_LINUX_SHM_H_
mdefine_line|#define _LINUX_SHM_H_
macro_line|#include &lt;linux/ipc.h&gt;
macro_line|#include &lt;asm/shmparam.h&gt;
DECL|struct|shmid_ds
r_struct
id|shmid_ds
(brace
DECL|member|shm_perm
r_struct
id|ipc_perm
id|shm_perm
suffix:semicolon
multiline_comment|/* operation perms */
DECL|member|shm_segsz
r_int
id|shm_segsz
suffix:semicolon
multiline_comment|/* size of segment (bytes) */
DECL|member|shm_atime
id|time_t
id|shm_atime
suffix:semicolon
multiline_comment|/* last attach time */
DECL|member|shm_dtime
id|time_t
id|shm_dtime
suffix:semicolon
multiline_comment|/* last detach time */
DECL|member|shm_ctime
id|time_t
id|shm_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|shm_cpid
r_int
r_int
id|shm_cpid
suffix:semicolon
multiline_comment|/* pid of creator */
DECL|member|shm_lpid
r_int
r_int
id|shm_lpid
suffix:semicolon
multiline_comment|/* pid of last operator */
DECL|member|shm_nattch
r_int
id|shm_nattch
suffix:semicolon
multiline_comment|/* no. of current attaches */
multiline_comment|/* the following are private */
DECL|member|shm_npages
r_int
r_int
id|shm_npages
suffix:semicolon
multiline_comment|/* size of segment (pages) */
DECL|member|shm_pages
r_int
r_int
op_star
id|shm_pages
suffix:semicolon
multiline_comment|/* array of ptrs to frames -&gt; SHMMAX */
DECL|member|attaches
r_struct
id|vm_area_struct
op_star
id|attaches
suffix:semicolon
multiline_comment|/* descriptors for attaches */
)brace
suffix:semicolon
multiline_comment|/* permission flag for shmget */
DECL|macro|SHM_R
mdefine_line|#define SHM_R&t;&t;0400&t;/* or S_IRUGO from &lt;linux/stat.h&gt; */
DECL|macro|SHM_W
mdefine_line|#define SHM_W&t;&t;0200&t;/* or S_IWUGO from &lt;linux/stat.h&gt; */
multiline_comment|/* mode for attach */
DECL|macro|SHM_RDONLY
mdefine_line|#define&t;SHM_RDONLY&t;010000&t;/* read-only access */
DECL|macro|SHM_RND
mdefine_line|#define&t;SHM_RND&t;&t;020000&t;/* round attach address to SHMLBA boundary */
DECL|macro|SHM_REMAP
mdefine_line|#define&t;SHM_REMAP&t;040000&t;/* take-over region on attach */
multiline_comment|/* super user shmctl commands */
DECL|macro|SHM_LOCK
mdefine_line|#define SHM_LOCK &t;11
DECL|macro|SHM_UNLOCK
mdefine_line|#define SHM_UNLOCK &t;12
DECL|struct|shminfo
r_struct
id|shminfo
(brace
DECL|member|shmmax
r_int
id|shmmax
suffix:semicolon
DECL|member|shmmin
r_int
id|shmmin
suffix:semicolon
DECL|member|shmmni
r_int
id|shmmni
suffix:semicolon
DECL|member|shmseg
r_int
id|shmseg
suffix:semicolon
DECL|member|shmall
r_int
id|shmall
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* shm_mode upper byte flags */
DECL|macro|SHM_DEST
mdefine_line|#define&t;SHM_DEST&t;01000&t;/* segment will be destroyed on last detach */
DECL|macro|SHM_LOCKED
mdefine_line|#define SHM_LOCKED      02000   /* segment will not be swapped */
multiline_comment|/* ipcs ctl commands */
DECL|macro|SHM_STAT
mdefine_line|#define SHM_STAT &t;13
DECL|macro|SHM_INFO
mdefine_line|#define SHM_INFO &t;14
DECL|struct|shm_info
r_struct
id|shm_info
(brace
DECL|member|used_ids
r_int
id|used_ids
suffix:semicolon
DECL|member|shm_tot
id|ulong
id|shm_tot
suffix:semicolon
multiline_comment|/* total allocated shm */
DECL|member|shm_rss
id|ulong
id|shm_rss
suffix:semicolon
multiline_comment|/* total resident shm */
DECL|member|shm_swp
id|ulong
id|shm_swp
suffix:semicolon
multiline_comment|/* total swapped shm */
DECL|member|swap_attempts
id|ulong
id|swap_attempts
suffix:semicolon
DECL|member|swap_successes
id|ulong
id|swap_successes
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_shmget
(paren
id|key_t
id|key
comma
r_int
id|size
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_shmat
(paren
r_int
id|shmid
comma
r_char
op_star
id|shmaddr
comma
r_int
id|shmflg
comma
id|ulong
op_star
id|addr
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_shmdt
(paren
r_char
op_star
id|shmaddr
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_shmctl
(paren
r_int
id|shmid
comma
r_int
id|cmd
comma
r_struct
id|shmid_ds
op_star
id|buf
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SHM_H_ */
eof
