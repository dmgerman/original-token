macro_line|#ifndef _LINUX_IPC_H
DECL|macro|_LINUX_IPC_H
mdefine_line|#define _LINUX_IPC_H
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|key_t
r_typedef
r_int
id|key_t
suffix:semicolon
multiline_comment|/* should go in &lt;types.h&gt; type for IPC key */
DECL|macro|IPC_PRIVATE
mdefine_line|#define IPC_PRIVATE ((key_t) 0)  
DECL|struct|ipc_perm
r_struct
id|ipc_perm
(brace
DECL|member|key
id|key_t
id|key
suffix:semicolon
DECL|member|uid
id|ushort
id|uid
suffix:semicolon
multiline_comment|/* owner euid and egid */
DECL|member|gid
id|ushort
id|gid
suffix:semicolon
DECL|member|cuid
id|ushort
id|cuid
suffix:semicolon
multiline_comment|/* creator euid and egid */
DECL|member|cgid
id|ushort
id|cgid
suffix:semicolon
DECL|member|mode
id|ushort
id|mode
suffix:semicolon
multiline_comment|/* access modes see mode flags below */
DECL|member|seq
id|ushort
id|seq
suffix:semicolon
multiline_comment|/* sequence number */
)brace
suffix:semicolon
multiline_comment|/* resource get request flags */
DECL|macro|IPC_CREAT
mdefine_line|#define IPC_CREAT  00001000   /* create if key is nonexistent */
DECL|macro|IPC_EXCL
mdefine_line|#define IPC_EXCL   00002000   /* fail if key exists */
DECL|macro|IPC_NOWAIT
mdefine_line|#define IPC_NOWAIT 00004000   /* return error on wait */
multiline_comment|/* &n; * Control commands used with semctl, msgctl and shmctl &n; * see also specific commands in sem.h, msg.h and shm.h&n; */
DECL|macro|IPC_RMID
mdefine_line|#define IPC_RMID 0     /* remove resource */
DECL|macro|IPC_SET
mdefine_line|#define IPC_SET  1     /* set ipc_perm options */
DECL|macro|IPC_STAT
mdefine_line|#define IPC_STAT 2     /* get ipc_perm options */
DECL|macro|IPC_INFO
mdefine_line|#define IPC_INFO 3     /* see ipcs */
macro_line|#ifdef __KERNEL__
multiline_comment|/* special shmsegs[id], msgque[id] or semary[id]  values */
DECL|macro|IPC_UNUSED
mdefine_line|#define IPC_UNUSED&t;((void *) -1)
DECL|macro|IPC_NOID
mdefine_line|#define IPC_NOID&t;((void *) -2)&t;&t;/* being allocated/destroyed */
multiline_comment|/* &n; * These are used to wrap system calls. See ipc/util.c, libipc.c &n; */
DECL|struct|ipc_kludge
r_struct
id|ipc_kludge
(brace
DECL|member|msgp
r_struct
id|msgbuf
op_star
id|msgp
suffix:semicolon
DECL|member|msgtyp
r_int
id|msgtyp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEMOP
mdefine_line|#define SEMOP&t; &t;1
DECL|macro|SEMGET
mdefine_line|#define SEMGET &t;&t;2
DECL|macro|SEMCTL
mdefine_line|#define SEMCTL &t;&t;3
DECL|macro|MSGSND
mdefine_line|#define MSGSND &t;&t;11
DECL|macro|MSGRCV
mdefine_line|#define MSGRCV &t;&t;12
DECL|macro|MSGGET
mdefine_line|#define MSGGET &t;&t;13
DECL|macro|MSGCTL
mdefine_line|#define MSGCTL &t;&t;14
DECL|macro|SHMAT
mdefine_line|#define SHMAT &t;&t;21
DECL|macro|SHMDT
mdefine_line|#define SHMDT &t;&t;22
DECL|macro|SHMGET
mdefine_line|#define SHMGET &t;&t;23
DECL|macro|SHMCTL
mdefine_line|#define SHMCTL &t;&t;24
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_IPC_H */
eof
