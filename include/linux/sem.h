macro_line|#ifndef _LINUX_SEM_H
DECL|macro|_LINUX_SEM_H
mdefine_line|#define _LINUX_SEM_H
macro_line|#include &lt;linux/ipc.h&gt;
multiline_comment|/* semop flags */
DECL|macro|SEM_UNDO
mdefine_line|#define SEM_UNDO        010000  /* undo the operation on exit */
multiline_comment|/* semctl Command Definitions. */
DECL|macro|GETPID
mdefine_line|#define GETPID  11       /* get sempid */
DECL|macro|GETVAL
mdefine_line|#define GETVAL  12       /* get semval */
DECL|macro|GETALL
mdefine_line|#define GETALL  13       /* get all semval&squot;s */
DECL|macro|GETNCNT
mdefine_line|#define GETNCNT 14       /* get semncnt */
DECL|macro|GETZCNT
mdefine_line|#define GETZCNT 15       /* get semzcnt */
DECL|macro|SETVAL
mdefine_line|#define SETVAL  16       /* set semval */
DECL|macro|SETALL
mdefine_line|#define SETALL  17       /* set all semval&squot;s */
multiline_comment|/* One semid data structure for each set of semaphores in the system. */
DECL|struct|semid_ds
r_struct
id|semid_ds
(brace
DECL|member|sem_perm
r_struct
id|ipc_perm
id|sem_perm
suffix:semicolon
multiline_comment|/* permissions .. see ipc.h */
DECL|member|sem_otime
id|time_t
id|sem_otime
suffix:semicolon
multiline_comment|/* last semop time */
DECL|member|sem_ctime
id|time_t
id|sem_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|sem_base
r_struct
id|sem
op_star
id|sem_base
suffix:semicolon
multiline_comment|/* ptr to first semaphore in array */
DECL|member|eventn
r_struct
id|wait_queue
op_star
id|eventn
suffix:semicolon
DECL|member|eventz
r_struct
id|wait_queue
op_star
id|eventz
suffix:semicolon
DECL|member|undo
r_struct
id|sem_undo
op_star
id|undo
suffix:semicolon
multiline_comment|/* undo requests on this array */
DECL|member|sem_nsems
id|ushort
id|sem_nsems
suffix:semicolon
multiline_comment|/* no. of semaphores in array */
)brace
suffix:semicolon
multiline_comment|/* One semaphore structure for each semaphore in the system. */
DECL|struct|sem
r_struct
id|sem
(brace
DECL|member|sempid
r_int
id|sempid
suffix:semicolon
multiline_comment|/* pid of last operation */
DECL|member|semval
id|ushort
id|semval
suffix:semicolon
multiline_comment|/* current value */
DECL|member|semncnt
id|ushort
id|semncnt
suffix:semicolon
multiline_comment|/* num procs awaiting increase in semval */
DECL|member|semzcnt
id|ushort
id|semzcnt
suffix:semicolon
multiline_comment|/* num procs awaiting semval = 0 */
)brace
suffix:semicolon
multiline_comment|/* semop system calls takes an array of these.*/
DECL|struct|sembuf
r_struct
id|sembuf
(brace
DECL|member|sem_num
id|ushort
id|sem_num
suffix:semicolon
multiline_comment|/* semaphore index in array */
DECL|member|sem_op
r_int
id|sem_op
suffix:semicolon
multiline_comment|/* semaphore operation */
DECL|member|sem_flg
r_int
id|sem_flg
suffix:semicolon
multiline_comment|/* operation flags */
)brace
suffix:semicolon
multiline_comment|/* arg for semctl system calls. */
DECL|union|semun
r_union
id|semun
(brace
DECL|member|val
r_int
id|val
suffix:semicolon
multiline_comment|/* value for SETVAL */
DECL|member|buf
r_struct
id|semid_ds
op_star
id|buf
suffix:semicolon
multiline_comment|/* buffer for IPC_STAT &amp; IPC_SET */
DECL|member|array
id|ushort
op_star
id|array
suffix:semicolon
multiline_comment|/* array for GETALL &amp; SETALL */
)brace
suffix:semicolon
DECL|struct|seminfo
r_struct
id|seminfo
(brace
DECL|member|semmap
r_int
id|semmap
suffix:semicolon
DECL|member|semmni
r_int
id|semmni
suffix:semicolon
DECL|member|semmns
r_int
id|semmns
suffix:semicolon
DECL|member|semmnu
r_int
id|semmnu
suffix:semicolon
DECL|member|semmsl
r_int
id|semmsl
suffix:semicolon
DECL|member|semopm
r_int
id|semopm
suffix:semicolon
DECL|member|semume
r_int
id|semume
suffix:semicolon
DECL|member|semusz
r_int
id|semusz
suffix:semicolon
DECL|member|semvmx
r_int
id|semvmx
suffix:semicolon
DECL|member|semaem
r_int
id|semaem
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEMMNI
mdefine_line|#define SEMMNI  128             /* ?  max # of semaphore identifiers */
DECL|macro|SEMMSL
mdefine_line|#define SEMMSL  32              /* &lt;= 512 max num of semaphores per id */
DECL|macro|SEMMNS
mdefine_line|#define SEMMNS  (SEMMNI*SEMMSL) /* ? max # of semaphores in system */
DECL|macro|SEMOPM
mdefine_line|#define SEMOPM  32&t;        /* ~ 100 max num of ops per semop call */
DECL|macro|SEMVMX
mdefine_line|#define SEMVMX  32767           /* semaphore maximum value */
multiline_comment|/* unused */
DECL|macro|SEMUME
mdefine_line|#define SEMUME  SEMOPM          /* max num of undo entries per process */
DECL|macro|SEMMNU
mdefine_line|#define SEMMNU  SEMMNS          /* num of undo structures system wide */
DECL|macro|SEMAEM
mdefine_line|#define SEMAEM  (SEMVMX &gt;&gt; 1)   /* adjust on exit max value */
DECL|macro|SEMMAP
mdefine_line|#define SEMMAP  SEMMNS          /* # of entries in semaphore map */
DECL|macro|SEMUSZ
mdefine_line|#define SEMUSZ  20&t;&t;/* sizeof struct sem_undo */ 
macro_line|#ifdef __KERNEL__
multiline_comment|/* ipcs ctl cmds */
DECL|macro|SEM_STAT
mdefine_line|#define SEM_STAT 18&t;
DECL|macro|SEM_INFO
mdefine_line|#define SEM_INFO 19
multiline_comment|/* per process undo requests */
multiline_comment|/* this gets linked into the task_struct */
DECL|struct|sem_undo
r_struct
id|sem_undo
(brace
DECL|member|proc_next
r_struct
id|sem_undo
op_star
id|proc_next
suffix:semicolon
DECL|member|id_next
r_struct
id|sem_undo
op_star
id|id_next
suffix:semicolon
DECL|member|semid
r_int
id|semid
suffix:semicolon
DECL|member|semadj
r_int
id|semadj
suffix:semicolon
multiline_comment|/* semval adjusted by exit */
DECL|member|sem_num
id|ushort
id|sem_num
suffix:semicolon
multiline_comment|/* semaphore index in array semid */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SEM_H */
eof