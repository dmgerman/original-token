multiline_comment|/*&n; * linux/ipc/util.c&n; * Copyright (C) 1992 Krishna Balasubramanian&n; *&n; * Sep 1997 - Call suser() last after &quot;normal&quot; permission checks so we&n; *            get BSD style process accounting right.&n; *            Occurs in several places in the IPC code.&n; *            Chris Evans, &lt;chris@ferret.lmh.ox.ac.uk&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/msg.h&gt;
macro_line|#if defined(CONFIG_SYSVIPC)
r_extern
r_void
id|sem_init
(paren
r_void
)paren
comma
id|msg_init
(paren
r_void
)paren
comma
id|shm_init
(paren
r_void
)paren
suffix:semicolon
DECL|function|ipc_init
r_void
id|__init
id|ipc_init
(paren
r_void
)paren
(brace
id|sem_init
c_func
(paren
)paren
suffix:semicolon
id|msg_init
c_func
(paren
)paren
suffix:semicolon
id|shm_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* &n; * Check user, group, other permissions for access&n; * to ipc resources. return 0 if allowed&n; */
DECL|function|ipcperms
r_int
id|ipcperms
(paren
r_struct
id|ipc_perm
op_star
id|ipcp
comma
r_int
id|flag
)paren
(brace
multiline_comment|/* flag will most probably be 0 or S_...UGO from &lt;linux/stat.h&gt; */
r_int
id|requested_mode
comma
id|granted_mode
suffix:semicolon
id|requested_mode
op_assign
(paren
id|flag
op_rshift
l_int|6
)paren
op_or
(paren
id|flag
op_rshift
l_int|3
)paren
op_or
id|flag
suffix:semicolon
id|granted_mode
op_assign
id|ipcp-&gt;mode
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
id|ipcp-&gt;cuid
op_logical_or
id|current-&gt;euid
op_eq
id|ipcp-&gt;uid
)paren
id|granted_mode
op_rshift_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in_group_p
c_func
(paren
id|ipcp-&gt;cgid
)paren
op_logical_or
id|in_group_p
c_func
(paren
id|ipcp-&gt;gid
)paren
)paren
id|granted_mode
op_rshift_assign
l_int|3
suffix:semicolon
multiline_comment|/* is there some bit set in requested_mode but not in granted_mode? */
r_if
c_cond
(paren
(paren
id|requested_mode
op_amp
op_complement
id|granted_mode
op_amp
l_int|0007
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_OWNER
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; * Dummy functions when SYSV IPC isn&squot;t configured&n; */
DECL|function|sem_exit
r_void
id|sem_exit
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|shm_swap
r_int
id|shm_swap
(paren
r_int
id|prio
comma
r_int
id|gfp_mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_semget
id|asmlinkage
r_int
id|sys_semget
(paren
id|key_t
id|key
comma
r_int
id|nsems
comma
r_int
id|semflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_semop
id|asmlinkage
r_int
id|sys_semop
(paren
r_int
id|semid
comma
r_struct
id|sembuf
op_star
id|sops
comma
r_int
id|nsops
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_semctl
id|asmlinkage
r_int
id|sys_semctl
(paren
r_int
id|semid
comma
r_int
id|semnum
comma
r_int
id|cmd
comma
r_union
id|semun
id|arg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgget
id|asmlinkage
r_int
id|sys_msgget
(paren
id|key_t
id|key
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgsnd
id|asmlinkage
r_int
id|sys_msgsnd
(paren
r_int
id|msqid
comma
r_struct
id|msgbuf
op_star
id|msgp
comma
r_int
id|msgsz
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgrcv
id|asmlinkage
r_int
id|sys_msgrcv
(paren
r_int
id|msqid
comma
r_struct
id|msgbuf
op_star
id|msgp
comma
r_int
id|msgsz
comma
r_int
id|msgtyp
comma
r_int
id|msgflg
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_msgctl
id|asmlinkage
r_int
id|sys_msgctl
(paren
r_int
id|msqid
comma
r_int
id|cmd
comma
r_struct
id|msqid_ds
op_star
id|buf
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmget
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
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmat
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
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmdt
id|asmlinkage
r_int
id|sys_shmdt
(paren
r_char
op_star
id|shmaddr
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|sys_shmctl
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
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|shm_unuse
r_void
id|shm_unuse
c_func
(paren
id|pte_t
id|entry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
)brace
macro_line|#endif /* CONFIG_SYSVIPC */
eof
