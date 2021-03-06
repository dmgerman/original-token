multiline_comment|/*&n; * linux/ipc/util.h&n; * Copyright (C) 1999 Christoph Rohland&n; *&n; * ipc helper functions (c) 1999 Manfred Spraul &lt;manfreds@colorfullife.com&gt;&n; */
DECL|macro|USHRT_MAX
mdefine_line|#define USHRT_MAX 0xffff
DECL|macro|SEQ_MULTIPLIER
mdefine_line|#define SEQ_MULTIPLIER&t;(IPCMNI)
r_void
id|sem_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|msg_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|shm_init
(paren
r_void
)paren
suffix:semicolon
DECL|struct|ipc_ids
r_struct
id|ipc_ids
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|in_use
r_int
id|in_use
suffix:semicolon
DECL|member|max_id
r_int
id|max_id
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
DECL|member|seq_max
r_int
r_int
id|seq_max
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|ary
id|spinlock_t
id|ary
suffix:semicolon
DECL|member|entries
r_struct
id|ipc_id
op_star
id|entries
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipc_id
r_struct
id|ipc_id
(brace
DECL|member|p
r_struct
id|kern_ipc_perm
op_star
id|p
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
id|ipc_init_ids
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* must be called with ids-&gt;sem acquired.*/
r_int
id|ipc_findkey
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
id|key_t
id|key
)paren
suffix:semicolon
r_int
id|ipc_addid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_struct
id|kern_ipc_perm
op_star
r_new
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* must be called with both locks acquired. */
r_struct
id|kern_ipc_perm
op_star
id|ipc_rmid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
suffix:semicolon
r_int
id|ipcperms
(paren
r_struct
id|kern_ipc_perm
op_star
id|ipcp
comma
r_int
id|flg
)paren
suffix:semicolon
multiline_comment|/* for rare, potentially huge allocations.&n; * both function can sleep&n; */
r_void
op_star
id|ipc_alloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_void
id|ipc_free
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
suffix:semicolon
DECL|function|ipc_lockall
r_extern
r_inline
r_void
id|ipc_lockall
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|ids-&gt;ary
)paren
suffix:semicolon
)brace
DECL|function|ipc_get
r_extern
r_inline
r_struct
id|kern_ipc_perm
op_star
id|ipc_get
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
r_struct
id|kern_ipc_perm
op_star
id|out
suffix:semicolon
r_int
id|lid
op_assign
id|id
op_mod
id|SEQ_MULTIPLIER
suffix:semicolon
r_if
c_cond
(paren
id|lid
OG
id|ids-&gt;size
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|out
op_assign
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|ipc_unlockall
r_extern
r_inline
r_void
id|ipc_unlockall
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|ids-&gt;ary
)paren
suffix:semicolon
)brace
DECL|function|ipc_lock
r_extern
r_inline
r_struct
id|kern_ipc_perm
op_star
id|ipc_lock
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
r_struct
id|kern_ipc_perm
op_star
id|out
suffix:semicolon
r_int
id|lid
op_assign
id|id
op_mod
id|SEQ_MULTIPLIER
suffix:semicolon
r_if
c_cond
(paren
id|lid
OG
id|ids-&gt;size
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|ids-&gt;ary
)paren
suffix:semicolon
id|out
op_assign
id|ids-&gt;entries
(braket
id|lid
)braket
dot
id|p
suffix:semicolon
r_if
c_cond
(paren
id|out
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|ids-&gt;ary
)paren
suffix:semicolon
)brace
r_return
id|out
suffix:semicolon
)brace
DECL|function|ipc_unlock
r_extern
r_inline
r_void
id|ipc_unlock
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|ids-&gt;ary
)paren
suffix:semicolon
)brace
DECL|function|ipc_buildid
r_extern
r_inline
r_int
id|ipc_buildid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_int
id|id
comma
r_int
id|seq
)paren
(brace
r_return
id|SEQ_MULTIPLIER
op_star
id|seq
op_plus
id|id
suffix:semicolon
)brace
DECL|function|ipc_checkid
r_extern
r_inline
r_int
id|ipc_checkid
c_func
(paren
r_struct
id|ipc_ids
op_star
id|ids
comma
r_struct
id|kern_ipc_perm
op_star
id|ipcp
comma
r_int
id|uid
)paren
(brace
r_if
c_cond
(paren
id|uid
op_div
id|SEQ_MULTIPLIER
op_ne
id|ipcp-&gt;seq
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|kernel_to_ipc64_perm
c_func
(paren
r_struct
id|kern_ipc_perm
op_star
id|in
comma
r_struct
id|ipc64_perm
op_star
id|out
)paren
suffix:semicolon
r_void
id|ipc64_perm_to_ipc_perm
c_func
(paren
r_struct
id|ipc64_perm
op_star
id|in
comma
r_struct
id|ipc_perm
op_star
id|out
)paren
suffix:semicolon
macro_line|#ifdef __ia64__
multiline_comment|/* On IA-64, we always use the &quot;64-bit version&quot; of the IPC structures.  */
DECL|macro|ipc_parse_version
macro_line|# define ipc_parse_version(cmd)&t;IPC_64
macro_line|#else
r_int
id|ipc_parse_version
(paren
r_int
op_star
id|cmd
)paren
suffix:semicolon
macro_line|#endif
eof
