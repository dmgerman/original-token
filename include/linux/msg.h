macro_line|#ifndef _LINUX_MSG_H
DECL|macro|_LINUX_MSG_H
mdefine_line|#define _LINUX_MSG_H
macro_line|#include &lt;linux/ipc.h&gt;
multiline_comment|/* msgrcv options */
DECL|macro|MSG_NOERROR
mdefine_line|#define MSG_NOERROR     010000  /* no error if message is too big */
DECL|macro|MSG_EXCEPT
mdefine_line|#define MSG_EXCEPT      020000  /* recv any msg except of specified type.*/
multiline_comment|/* one msqid structure for each queue on the system */
DECL|struct|msqid_ds
r_struct
id|msqid_ds
(brace
DECL|member|msg_perm
r_struct
id|ipc_perm
id|msg_perm
suffix:semicolon
DECL|member|msg_first
r_struct
id|msg
op_star
id|msg_first
suffix:semicolon
multiline_comment|/* first message on queue */
DECL|member|msg_last
r_struct
id|msg
op_star
id|msg_last
suffix:semicolon
multiline_comment|/* last message in queue */
DECL|member|msg_stime
id|time_t
id|msg_stime
suffix:semicolon
multiline_comment|/* last msgsnd time */
DECL|member|msg_rtime
id|time_t
id|msg_rtime
suffix:semicolon
multiline_comment|/* last msgrcv time */
DECL|member|msg_ctime
id|time_t
id|msg_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|wwait
r_struct
id|wait_queue
op_star
id|wwait
suffix:semicolon
DECL|member|rwait
r_struct
id|wait_queue
op_star
id|rwait
suffix:semicolon
DECL|member|msg_cbytes
id|ushort
id|msg_cbytes
suffix:semicolon
multiline_comment|/* current number of bytes on queue */
DECL|member|msg_qnum
id|ushort
id|msg_qnum
suffix:semicolon
multiline_comment|/* number of messages in queue */
DECL|member|msg_qbytes
id|ushort
id|msg_qbytes
suffix:semicolon
multiline_comment|/* max number of bytes on queue */
DECL|member|msg_lspid
id|ushort
id|msg_lspid
suffix:semicolon
multiline_comment|/* pid of last msgsnd */
DECL|member|msg_lrpid
id|ushort
id|msg_lrpid
suffix:semicolon
multiline_comment|/* last receive pid */
)brace
suffix:semicolon
multiline_comment|/* message buffer for msgsnd and msgrcv calls */
DECL|struct|msgbuf
r_struct
id|msgbuf
(brace
DECL|member|mtype
r_int
id|mtype
suffix:semicolon
multiline_comment|/* type of message */
DECL|member|mtext
r_char
id|mtext
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* message text */
)brace
suffix:semicolon
multiline_comment|/* buffer for msgctl calls IPC_INFO, MSG_INFO */
DECL|struct|msginfo
r_struct
id|msginfo
(brace
DECL|member|msgpool
r_int
id|msgpool
suffix:semicolon
DECL|member|msgmap
r_int
id|msgmap
suffix:semicolon
DECL|member|msgmax
r_int
id|msgmax
suffix:semicolon
DECL|member|msgmnb
r_int
id|msgmnb
suffix:semicolon
DECL|member|msgmni
r_int
id|msgmni
suffix:semicolon
DECL|member|msgssz
r_int
id|msgssz
suffix:semicolon
DECL|member|msgtql
r_int
id|msgtql
suffix:semicolon
DECL|member|msgseg
id|ushort
id|msgseg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MSGMNI
mdefine_line|#define MSGMNI   128   /* &lt;= 1K */     /* max # of msg queue identifiers */
DECL|macro|MSGMAX
mdefine_line|#define MSGMAX  4056   /* &lt;= 4056 */   /* max size of message (bytes) */
DECL|macro|MSGMNB
mdefine_line|#define MSGMNB 16384   /* ? */        /* default max size of a message queue */
multiline_comment|/* unused */
DECL|macro|MSGPOOL
mdefine_line|#define MSGPOOL (MSGMNI*MSGMNB/1024)  /* size in kilobytes of message pool */
DECL|macro|MSGTQL
mdefine_line|#define MSGTQL  MSGMNB            /* number of system message headers */
DECL|macro|MSGMAP
mdefine_line|#define MSGMAP  MSGMNB            /* number of entries in message map */
DECL|macro|MSGSSZ
mdefine_line|#define MSGSSZ  16                /* message segment size */
DECL|macro|__MSGSEG
mdefine_line|#define __MSGSEG ((MSGPOOL*1024)/ MSGSSZ) /* max no. of segments */
DECL|macro|MSGSEG
mdefine_line|#define MSGSEG (__MSGSEG &lt;= 0xffff ? __MSGSEG : 0xffff)
macro_line|#ifdef __KERNEL__
multiline_comment|/* one msg structure for each message */
DECL|struct|msg
r_struct
id|msg
(brace
DECL|member|msg_next
r_struct
id|msg
op_star
id|msg_next
suffix:semicolon
multiline_comment|/* next message on queue */
DECL|member|msg_type
r_int
id|msg_type
suffix:semicolon
DECL|member|msg_spot
r_char
op_star
id|msg_spot
suffix:semicolon
multiline_comment|/* message text address */
DECL|member|msg_ts
r_int
id|msg_ts
suffix:semicolon
multiline_comment|/* message text size */
)brace
suffix:semicolon
multiline_comment|/* ipcs ctl commands */
DECL|macro|MSG_STAT
mdefine_line|#define MSG_STAT 11
DECL|macro|MSG_INFO
mdefine_line|#define MSG_INFO 12
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MSG_H */
eof
