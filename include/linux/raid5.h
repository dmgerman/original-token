macro_line|#ifndef _RAID5_H
DECL|macro|_RAID5_H
mdefine_line|#define _RAID5_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/md.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|disk_info
r_struct
id|disk_info
(brace
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
DECL|member|operational
r_int
id|operational
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|raid_disk
r_int
id|raid_disk
suffix:semicolon
DECL|member|write_only
r_int
id|write_only
suffix:semicolon
DECL|member|spare
r_int
id|spare
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stripe_head
r_struct
id|stripe_head
(brace
DECL|member|hash_next
DECL|member|hash_pprev
r_struct
id|stripe_head
op_star
id|hash_next
comma
op_star
op_star
id|hash_pprev
suffix:semicolon
multiline_comment|/* hash pointers */
DECL|member|free_next
r_struct
id|stripe_head
op_star
id|free_next
suffix:semicolon
multiline_comment|/* pool of free sh&squot;s */
DECL|member|buffer_pool
r_struct
id|buffer_head
op_star
id|buffer_pool
suffix:semicolon
multiline_comment|/* pool of free buffers */
DECL|member|bh_pool
r_struct
id|buffer_head
op_star
id|bh_pool
suffix:semicolon
multiline_comment|/* pool of free bh&squot;s */
DECL|member|raid_conf
r_struct
id|raid5_data
op_star
id|raid_conf
suffix:semicolon
DECL|member|bh_old
r_struct
id|buffer_head
op_star
id|bh_old
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* disk image */
DECL|member|bh_new
r_struct
id|buffer_head
op_star
id|bh_new
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* buffers of the MD device (present in buffer cache) */
DECL|member|bh_copy
r_struct
id|buffer_head
op_star
id|bh_copy
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* copy on write of bh_new (bh_new can change from under us) */
DECL|member|bh_req
r_struct
id|buffer_head
op_star
id|bh_req
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* copy of bh_new (only the buffer heads), queued to the lower levels */
DECL|member|cmd_new
r_int
id|cmd_new
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* READ/WRITE for new */
DECL|member|new
r_int
r_new
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
multiline_comment|/* buffer added since the last handle_stripe() */
DECL|member|sector
r_int
r_int
id|sector
suffix:semicolon
multiline_comment|/* sector of this row */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* buffers size */
DECL|member|pd_idx
r_int
id|pd_idx
suffix:semicolon
multiline_comment|/* parity disk index */
DECL|member|nr_pending
r_int
id|nr_pending
suffix:semicolon
multiline_comment|/* nr of pending cmds */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* state flags */
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
multiline_comment|/* stripe cmd */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* nr of waiters */
DECL|member|write_method
r_int
id|write_method
suffix:semicolon
multiline_comment|/* reconstruct-write / read-modify-write */
DECL|member|phase
r_int
id|phase
suffix:semicolon
multiline_comment|/* PHASE_BEGIN, ..., PHASE_COMPLETE */
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
multiline_comment|/* processes waiting for this stripe */
)brace
suffix:semicolon
multiline_comment|/*&n; * Phase&n; */
DECL|macro|PHASE_BEGIN
mdefine_line|#define PHASE_BEGIN&t;&t;0
DECL|macro|PHASE_READ_OLD
mdefine_line|#define PHASE_READ_OLD&t;&t;1
DECL|macro|PHASE_WRITE
mdefine_line|#define PHASE_WRITE&t;&t;2
DECL|macro|PHASE_READ
mdefine_line|#define PHASE_READ&t;&t;3
DECL|macro|PHASE_COMPLETE
mdefine_line|#define PHASE_COMPLETE&t;&t;4
multiline_comment|/*&n; * Write method&n; */
DECL|macro|METHOD_NONE
mdefine_line|#define METHOD_NONE&t;&t;0
DECL|macro|RECONSTRUCT_WRITE
mdefine_line|#define RECONSTRUCT_WRITE&t;1
DECL|macro|READ_MODIFY_WRITE
mdefine_line|#define READ_MODIFY_WRITE&t;2
multiline_comment|/*&n; * Stripe state&n; */
DECL|macro|STRIPE_LOCKED
mdefine_line|#define STRIPE_LOCKED&t;&t;0
DECL|macro|STRIPE_ERROR
mdefine_line|#define STRIPE_ERROR&t;&t;1
multiline_comment|/*&n; * Stripe commands&n; */
DECL|macro|STRIPE_NONE
mdefine_line|#define STRIPE_NONE&t;&t;0
DECL|macro|STRIPE_WRITE
mdefine_line|#define&t;STRIPE_WRITE&t;&t;1
DECL|macro|STRIPE_READ
mdefine_line|#define STRIPE_READ&t;&t;2
DECL|struct|raid5_data
r_struct
id|raid5_data
(brace
DECL|member|stripe_hashtbl
r_struct
id|stripe_head
op_star
op_star
id|stripe_hashtbl
suffix:semicolon
DECL|member|mddev
r_struct
id|md_dev
op_star
id|mddev
suffix:semicolon
DECL|member|thread
DECL|member|resync_thread
r_struct
id|md_thread
op_star
id|thread
comma
op_star
id|resync_thread
suffix:semicolon
DECL|member|disks
r_struct
id|disk_info
id|disks
(braket
id|MD_SB_DISKS
)braket
suffix:semicolon
DECL|member|spare
r_struct
id|disk_info
op_star
id|spare
suffix:semicolon
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
DECL|member|chunk_size
DECL|member|level
DECL|member|algorithm
r_int
id|chunk_size
comma
id|level
comma
id|algorithm
suffix:semicolon
DECL|member|raid_disks
DECL|member|working_disks
DECL|member|failed_disks
r_int
id|raid_disks
comma
id|working_disks
comma
id|failed_disks
suffix:semicolon
DECL|member|sector_count
r_int
id|sector_count
suffix:semicolon
DECL|member|next_sector
r_int
r_int
id|next_sector
suffix:semicolon
DECL|member|nr_handle
id|atomic_t
id|nr_handle
suffix:semicolon
DECL|member|next_free_stripe
r_struct
id|stripe_head
op_star
id|next_free_stripe
suffix:semicolon
DECL|member|nr_stripes
r_int
id|nr_stripes
suffix:semicolon
DECL|member|resync_parity
r_int
id|resync_parity
suffix:semicolon
DECL|member|max_nr_stripes
r_int
id|max_nr_stripes
suffix:semicolon
DECL|member|clock
r_int
id|clock
suffix:semicolon
DECL|member|nr_hashed_stripes
r_int
id|nr_hashed_stripes
suffix:semicolon
DECL|member|nr_locked_stripes
r_int
id|nr_locked_stripes
suffix:semicolon
DECL|member|nr_pending_stripes
r_int
id|nr_pending_stripes
suffix:semicolon
DECL|member|nr_cached_stripes
r_int
id|nr_cached_stripes
suffix:semicolon
multiline_comment|/*&n;&t; * Free stripes pool&n;&t; */
DECL|member|nr_free_sh
r_int
id|nr_free_sh
suffix:semicolon
DECL|member|free_sh_list
r_struct
id|stripe_head
op_star
id|free_sh_list
suffix:semicolon
DECL|member|wait_for_stripe
r_struct
id|wait_queue
op_star
id|wait_for_stripe
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Our supported algorithms&n; */
DECL|macro|ALGORITHM_LEFT_ASYMMETRIC
mdefine_line|#define ALGORITHM_LEFT_ASYMMETRIC&t;0
DECL|macro|ALGORITHM_RIGHT_ASYMMETRIC
mdefine_line|#define ALGORITHM_RIGHT_ASYMMETRIC&t;1
DECL|macro|ALGORITHM_LEFT_SYMMETRIC
mdefine_line|#define ALGORITHM_LEFT_SYMMETRIC&t;2
DECL|macro|ALGORITHM_RIGHT_SYMMETRIC
mdefine_line|#define ALGORITHM_RIGHT_SYMMETRIC&t;3
macro_line|#endif
eof
