multiline_comment|/*&n; * queue.h: queue handling&n; *&n; * Copyright (C) 1997 Russell King&n; */
macro_line|#ifndef QUEUE_H
DECL|macro|QUEUE_H
mdefine_line|#define QUEUE_H
r_typedef
r_struct
(brace
DECL|member|head
r_struct
id|queue_entry
op_star
id|head
suffix:semicolon
multiline_comment|/* head of queue */
DECL|member|tail
r_struct
id|queue_entry
op_star
id|tail
suffix:semicolon
multiline_comment|/* tail of queue */
DECL|member|free
r_struct
id|queue_entry
op_star
id|free
suffix:semicolon
multiline_comment|/* free list */
DECL|member|alloc
r_void
op_star
id|alloc
suffix:semicolon
multiline_comment|/* start of allocated mem */
DECL|typedef|Queue_t
)brace
id|Queue_t
suffix:semicolon
multiline_comment|/*&n; * Function: void queue_initialise (Queue_t *queue)&n; * Purpose : initialise a queue&n; * Params  : queue - queue to initialise&n; */
r_extern
r_int
id|queue_initialise
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: void queue_free (Queue_t *queue)&n; * Purpose : free a queue&n; * Params  : queue - queue to free&n; */
r_extern
r_void
id|queue_free
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove (queue)&n; * Purpose : removes first SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
r_extern
id|Scsi_Cmnd
op_star
id|queue_remove
(paren
id|Queue_t
op_star
id|queue
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_exclude_ref (queue, exclude, ref)&n; * Purpose : remove a SCSI command from a queue&n; * Params  : queue   - queue to remove command from&n; *&t;     exclude - array of busy LUNs&n; *&t;     ref     - a reference that can be used to put the command back&n; * Returns : Scsi_Cmnd if successful (and a reference), or NULL if no command available&n; */
r_extern
id|Scsi_Cmnd
op_star
id|queue_remove_exclude
(paren
id|Queue_t
op_star
id|queue
comma
r_int
r_char
op_star
id|exclude
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_add_cmd_ordered (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : Add a new command onto a queue, queueing REQUEST_SENSE first&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; * Returns : 0 on error, !0 on success&n; */
r_extern
r_int
id|queue_add_cmd_ordered
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_add_cmd_tail (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : Add a new command onto a queue, queueing at end of list&n; * Params  : queue - destination queue&n; *&t;     SCpnt - command to add&n; * Returns : 0 on error, !0 on success&n; */
r_extern
r_int
id|queue_add_cmd_tail
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: Scsi_Cmnd *queue_remove_tgtluntag (queue, target, lun, tag)&n; * Purpose : remove a SCSI command from the queue for a specified target/lun/tag&n; * Params  : queue  - queue to remove command from&n; *&t;     target - target that we want&n; *&t;     lun    - lun on device&n; *&t;     tag    - tag on device&n; * Returns : Scsi_Cmnd if successful, or NULL if no command satisfies requirements&n; */
r_extern
id|Scsi_Cmnd
op_star
id|queue_remove_tgtluntag
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
comma
r_int
id|tag
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_probetgtlun (queue, target, lun)&n; * Purpose : check to see if we have a command in the queue for the specified&n; *&t;     target/lun.&n; * Params  : queue  - queue to look in&n; *&t;     target - target we want to probe&n; *&t;     lun    - lun on target&n; * Returns : 0 if not found, != 0 if found&n; */
r_extern
r_int
id|queue_probetgtlun
(paren
id|Queue_t
op_star
id|queue
comma
r_int
id|target
comma
r_int
id|lun
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_cmdonqueue (queue, SCpnt)&n; * Purpose : check to see if we have a command on the queue&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found, != 0 if found&n; */
r_int
id|queue_cmdonqueue
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
multiline_comment|/*&n; * Function: int queue_removecmd (Queue_t *queue, Scsi_Cmnd *SCpnt)&n; * Purpose : remove a specific command from the queues&n; * Params  : queue - queue to look in&n; *&t;     SCpnt - command to find&n; * Returns : 0 if not found&n; */
r_int
id|queue_removecmd
(paren
id|Queue_t
op_star
id|queue
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
macro_line|#endif /* QUEUE_H */
eof
