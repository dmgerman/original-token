multiline_comment|/*&n; * File...........: linux/drivers/s390/block/dasd_types.h&n; * Author.........: Holger Smolinski &lt;Holger.Smolinski@de.ibm.com&gt;&n; * Created........: 08/31/1999&n; * Last Modified..: 09/29/1999&n; * (C) IBM Corporation, IBM Deutschland Entwicklung GmbH, 1999,2000&n;&n; * List of Changes:&n; - Initial Release as of 09/29/1999&n;&n; * Description&n;&n; * Restrictions&n;&n; * Known Bugs&n;&n; * Todo-List&n;&n; */
macro_line|#ifndef DASD_TYPES_H
DECL|macro|DASD_TYPES_H
mdefine_line|#define DASD_TYPES_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/dasd.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|CCW_DEFINE_EXTENT
mdefine_line|#define CCW_DEFINE_EXTENT 0x63
DECL|macro|CCW_LOCATE_RECORD
mdefine_line|#define CCW_LOCATE_RECORD 0x43
DECL|macro|CCW_READ_DEVICE_CHARACTERISTICS
mdefine_line|#define CCW_READ_DEVICE_CHARACTERISTICS 0x64
r_typedef
r_enum
(brace
DECL|enumerator|dasd_none
id|dasd_none
op_assign
op_minus
l_int|1
comma
macro_line|#ifdef CONFIG_DASD_ECKD
DECL|enumerator|dasd_eckd
id|dasd_eckd
comma
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_ECKD */
macro_line|#ifdef CONFIG_DASD_MDSK                                        
DECL|enumerator|dasd_mdsk
id|dasd_mdsk
comma
macro_line|#endif                          /* CONFIG_DASD_MDSK */         
macro_line|#ifdef CONFIG_DASD_CKD                                        
DECL|enumerator|dasd_ckd
id|dasd_ckd
comma
macro_line|#endif                          /* CONFIG_DASD_CKD */         
DECL|enumerator|dasd_end
id|dasd_end
DECL|typedef|dasd_type_t
)brace
id|dasd_type_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cu_type
id|__u16
id|cu_type
suffix:semicolon
r_struct
(brace
DECL|member|support
r_int
r_char
id|support
suffix:colon
l_int|2
suffix:semicolon
DECL|member|async
r_int
r_char
id|async
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cache_info
r_int
r_char
id|cache_info
suffix:colon
l_int|1
suffix:semicolon
DECL|member|model
r_int
r_char
id|model
suffix:colon
l_int|3
suffix:semicolon
DECL|member|cu_model
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|cu_model
suffix:semicolon
DECL|member|dev_type
id|__u16
id|dev_type
suffix:semicolon
DECL|member|dev_model
id|__u8
id|dev_model
suffix:semicolon
r_struct
(brace
DECL|member|mult_burst
r_int
r_char
id|mult_burst
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RT_in_LR
r_int
r_char
id|RT_in_LR
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
r_int
r_char
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RD_IN_LR
r_int
r_char
id|RD_IN_LR
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:colon
l_int|8
suffix:semicolon
DECL|member|defect_wr
r_int
r_char
id|defect_wr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
r_int
r_char
id|reserved4
suffix:colon
l_int|2
suffix:semicolon
DECL|member|striping
r_int
r_char
id|striping
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved5
r_int
r_char
id|reserved5
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cfw
r_int
r_char
id|cfw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved6
r_int
r_char
id|reserved6
suffix:colon
l_int|2
suffix:semicolon
DECL|member|cache
r_int
r_char
id|cache
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dual_copy
r_int
r_char
id|dual_copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfw
r_int
r_char
id|dfw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reset_alleg
r_int
r_char
id|reset_alleg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sense_down
r_int
r_char
id|sense_down
suffix:colon
l_int|1
suffix:semicolon
DECL|member|facilities
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|facilities
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
suffix:semicolon
DECL|member|unit_type
id|__u8
id|unit_type
suffix:semicolon
DECL|member|no_cyl
id|__u16
id|no_cyl
suffix:semicolon
DECL|member|trk_per_cyl
id|__u16
id|trk_per_cyl
suffix:semicolon
DECL|member|sec_per_trk
id|__u8
id|sec_per_trk
suffix:semicolon
DECL|member|byte_per_track
id|__u8
id|byte_per_track
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|home_bytes
id|__u16
id|home_bytes
suffix:semicolon
DECL|member|formula
id|__u8
id|formula
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|f1
id|__u8
id|f1
suffix:semicolon
DECL|member|f2
id|__u16
id|f2
suffix:semicolon
DECL|member|f3
id|__u16
id|f3
suffix:semicolon
DECL|member|f_0x01
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|f_0x01
suffix:semicolon
r_struct
(brace
DECL|member|f1
id|__u8
id|f1
suffix:semicolon
DECL|member|f2
id|__u8
id|f2
suffix:semicolon
DECL|member|f3
id|__u8
id|f3
suffix:semicolon
DECL|member|f4
id|__u8
id|f4
suffix:semicolon
DECL|member|f5
id|__u8
id|f5
suffix:semicolon
DECL|member|f_0x02
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|f_0x02
suffix:semicolon
DECL|member|factors
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|factors
suffix:semicolon
DECL|member|first_alt_trk
id|__u16
id|first_alt_trk
suffix:semicolon
DECL|member|no_alt_trk
id|__u16
id|no_alt_trk
suffix:semicolon
DECL|member|first_dia_trk
id|__u16
id|first_dia_trk
suffix:semicolon
DECL|member|no_dia_trk
id|__u16
id|no_dia_trk
suffix:semicolon
DECL|member|first_sup_trk
id|__u16
id|first_sup_trk
suffix:semicolon
DECL|member|no_sup_trk
id|__u16
id|no_sup_trk
suffix:semicolon
DECL|member|MDR_ID
id|__u8
id|MDR_ID
suffix:semicolon
DECL|member|OBR_ID
id|__u8
id|OBR_ID
suffix:semicolon
DECL|member|director
id|__u8
id|director
suffix:semicolon
DECL|member|rd_trk_set
id|__u8
id|rd_trk_set
suffix:semicolon
DECL|member|max_rec_zero
id|__u16
id|max_rec_zero
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|RWANY_in_LR
id|__u8
id|RWANY_in_LR
suffix:semicolon
DECL|member|factor6
id|__u8
id|factor6
suffix:semicolon
DECL|member|factor7
id|__u8
id|factor7
suffix:semicolon
DECL|member|factor8
id|__u8
id|factor8
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
(braket
l_int|10
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
(paren
l_int|32
)paren
)paren
)paren
DECL|typedef|dasd_eckd_characteristics_t
id|dasd_eckd_characteristics_t
suffix:semicolon
multiline_comment|/* eckd count area */
r_typedef
r_struct
(brace
DECL|member|cyl
id|__u16
id|cyl
suffix:semicolon
DECL|member|head
id|__u16
id|head
suffix:semicolon
DECL|member|record
id|__u8
id|record
suffix:semicolon
DECL|member|kl
id|__u8
id|kl
suffix:semicolon
DECL|member|dl
id|__u16
id|dl
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|eckd_count_t
id|eckd_count_t
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_CKD
DECL|struct|dasd_ckd_characteristics
r_struct
id|dasd_ckd_characteristics
(brace
DECL|member|info
r_char
id|info
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_CKD */
macro_line|#ifdef CONFIG_DASD_ECKD
DECL|struct|dasd_eckd_characteristics
r_struct
id|dasd_eckd_characteristics
(brace
DECL|member|info
r_char
id|info
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_ECKD */
r_typedef
r_union
(brace
DECL|member|bytes
r_char
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
id|bytes
(braket
l_int|64
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_DASD_CKD
DECL|member|ckd
r_struct
id|dasd_ckd_characteristics
id|ckd
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_CKD */
macro_line|#ifdef CONFIG_DASD_ECKD
DECL|member|eckd
id|dasd_eckd_characteristics_t
id|eckd
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_DASD_ECKD */
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|32
)paren
)paren
)paren
DECL|typedef|dasd_characteristics_t
id|dasd_characteristics_t
suffix:semicolon
DECL|macro|CQR_STATUS_EMPTY
mdefine_line|#define CQR_STATUS_EMPTY  0x00
DECL|macro|CQR_STATUS_FILLED
mdefine_line|#define CQR_STATUS_FILLED 0x01
DECL|macro|CQR_STATUS_QUEUED
mdefine_line|#define CQR_STATUS_QUEUED 0x02
DECL|macro|CQR_STATUS_IN_IO
mdefine_line|#define CQR_STATUS_IN_IO  0x04
DECL|macro|CQR_STATUS_DONE
mdefine_line|#define CQR_STATUS_DONE   0x08
DECL|macro|CQR_STATUS_RETRY
mdefine_line|#define CQR_STATUS_RETRY  0x10
DECL|macro|CQR_STATUS_ERROR
mdefine_line|#define CQR_STATUS_ERROR  0x20
DECL|macro|CQR_STATUS_FAILED
mdefine_line|#define CQR_STATUS_FAILED 0x40
DECL|macro|CQR_STATUS_SLEEP
mdefine_line|#define CQR_STATUS_SLEEP  0x80
DECL|macro|CQR_FLAGS_SLEEP
mdefine_line|#define CQR_FLAGS_SLEEP   0x01
DECL|macro|CQR_FLAGS_WAIT
mdefine_line|#define CQR_FLAGS_WAIT    0x02
DECL|macro|CQR_FLAGS_NOLOCK
mdefine_line|#define CQR_FLAGS_NOLOCK  0x04
DECL|macro|CQR_FLAGS_NORETRY
mdefine_line|#define CQR_FLAGS_NORETRY 0x08
r_typedef
DECL|struct|cqr_t
r_struct
id|cqr_t
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number should be &quot;DASD&quot; */
DECL|member|status
id|atomic_t
id|status
suffix:semicolon
multiline_comment|/* current status of request */
DECL|member|retries
r_int
r_int
id|retries
suffix:semicolon
multiline_comment|/* counter for retry in error case */
DECL|member|cplength
r_int
r_int
id|cplength
suffix:semicolon
multiline_comment|/* Length of channel program  (CP) */
DECL|member|devindex
r_int
r_int
id|devindex
suffix:semicolon
multiline_comment|/* device number */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags for execution */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* additional data area for CP */
DECL|member|cpaddr
id|ccw1_t
op_star
id|cpaddr
suffix:semicolon
multiline_comment|/* Address of CP */
DECL|member|req
r_struct
id|request
op_star
id|req
suffix:semicolon
multiline_comment|/* backpointer to struct request */
DECL|member|next
r_struct
id|cqr_t
op_star
id|next
suffix:semicolon
multiline_comment|/* forward chain in chanq */
DECL|member|int4cqr
r_struct
id|cqr_t
op_star
id|int4cqr
suffix:semicolon
multiline_comment|/* which cqr ist the nect PCI for? */
DECL|member|buildclk
r_int
r_int
r_int
id|buildclk
suffix:semicolon
DECL|member|startclk
r_int
r_int
r_int
id|startclk
suffix:semicolon
DECL|member|stopclk
r_int
r_int
r_int
id|stopclk
suffix:semicolon
DECL|member|endclk
r_int
r_int
r_int
id|endclk
suffix:semicolon
DECL|member|dstat
id|devstat_t
op_star
id|dstat
suffix:semicolon
multiline_comment|/* savearea for devstat */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|options
r_int
id|options
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|cqr_t
id|cqr_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|kbytes
r_int
r_int
r_int
id|kbytes
suffix:semicolon
DECL|member|bp_sector
r_int
r_int
id|bp_sector
suffix:semicolon
DECL|member|bp_block
r_int
r_int
id|bp_block
suffix:semicolon
DECL|member|blocks
r_int
r_int
id|blocks
suffix:semicolon
DECL|member|s2b_shift
r_int
r_int
id|s2b_shift
suffix:semicolon
DECL|member|b2k_shift
r_int
r_int
id|b2k_shift
suffix:semicolon
DECL|member|label_block
r_int
r_int
id|label_block
suffix:semicolon
DECL|typedef|dasd_sizes_t
)brace
id|dasd_sizes_t
suffix:semicolon
DECL|macro|DASD_CHANQ_ACTIVE
mdefine_line|#define DASD_CHANQ_ACTIVE 0x01
DECL|macro|DASD_CHANQ_BUSY
mdefine_line|#define DASD_CHANQ_BUSY 0x02
DECL|macro|DASD_REQUEST_Q_BROKEN
mdefine_line|#define DASD_REQUEST_Q_BROKEN 0x04
r_typedef
DECL|struct|dasd_chanq_t
r_struct
id|dasd_chanq_t
(brace
DECL|member|head
r_volatile
id|cqr_t
op_star
id|head
suffix:semicolon
DECL|member|tail
r_volatile
id|cqr_t
op_star
id|tail
suffix:semicolon
DECL|member|q_lock
id|spinlock_t
id|q_lock
suffix:semicolon
multiline_comment|/* lock for queue operations */
DECL|member|f_lock
id|spinlock_t
id|f_lock
suffix:semicolon
multiline_comment|/* lock for flag operations */
DECL|member|queued_requests
r_int
id|queued_requests
suffix:semicolon
DECL|member|flags
id|atomic_t
id|flags
suffix:semicolon
DECL|member|dirty_requests
id|atomic_t
id|dirty_requests
suffix:semicolon
DECL|member|next_q
r_struct
id|dasd_chanq_t
op_star
id|next_q
suffix:semicolon
multiline_comment|/* pointer to next queue */
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
(paren
l_int|16
)paren
)paren
)paren
DECL|typedef|dasd_chanq_t
id|dasd_chanq_t
suffix:semicolon
DECL|macro|DASD_INFO_FLAGS_INITIALIZED
mdefine_line|#define DASD_INFO_FLAGS_INITIALIZED 0x01
DECL|macro|DASD_INFO_FLAGS_NOT_FORMATTED
mdefine_line|#define DASD_INFO_FLAGS_NOT_FORMATTED 0x02
DECL|macro|DASD_INFO_FLAGS_PARTNS_DETECTED
mdefine_line|#define DASD_INFO_FLAGS_PARTNS_DETECTED 0x04
r_typedef
DECL|struct|dasd_information_t
r_struct
id|dasd_information_t
(brace
DECL|member|dev_status
id|devstat_t
id|dev_status
suffix:semicolon
DECL|member|rdc_data
id|dasd_characteristics_t
op_star
id|rdc_data
suffix:semicolon
DECL|member|label
id|dasd_volume_label_t
op_star
id|label
suffix:semicolon
DECL|member|type
id|dasd_type_t
id|type
suffix:semicolon
DECL|member|info
id|dev_info_t
id|info
suffix:semicolon
DECL|member|sizes
id|dasd_sizes_t
id|sizes
suffix:semicolon
DECL|member|queue
id|dasd_chanq_t
id|queue
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|proc_device
r_struct
id|proc_dir_entry
op_star
id|proc_device
suffix:semicolon
DECL|member|devfs_entry
id|devfs_handle_t
id|devfs_entry
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|count_data
id|eckd_count_t
id|count_data
suffix:semicolon
DECL|member|eckd
)brace
id|eckd
suffix:semicolon
r_struct
(brace
DECL|member|dummy
r_char
id|dummy
suffix:semicolon
DECL|member|fba
)brace
id|fba
suffix:semicolon
r_struct
(brace
DECL|member|dummy
r_char
id|dummy
suffix:semicolon
DECL|member|mdsk
)brace
id|mdsk
suffix:semicolon
r_struct
(brace
DECL|member|dummy
r_char
id|dummy
suffix:semicolon
DECL|member|ckd
)brace
id|ckd
suffix:semicolon
DECL|member|private
)brace
r_private
suffix:semicolon
DECL|typedef|dasd_information_t
)brace
id|dasd_information_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|start_unit
r_int
id|start_unit
suffix:semicolon
DECL|member|stop_unit
r_int
id|stop_unit
suffix:semicolon
DECL|member|blksize
r_int
id|blksize
suffix:semicolon
DECL|typedef|format_data_t
)brace
id|format_data_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ck_devinfo
r_int
(paren
op_star
id|ck_devinfo
)paren
(paren
id|dev_info_t
op_star
)paren
suffix:semicolon
DECL|member|get_req_ccw
id|cqr_t
op_star
(paren
op_star
id|get_req_ccw
)paren
(paren
r_int
comma
r_struct
id|request
op_star
)paren
suffix:semicolon
DECL|member|rw_label
id|cqr_t
op_star
(paren
op_star
id|rw_label
)paren
(paren
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
DECL|member|ck_characteristics
r_int
(paren
op_star
id|ck_characteristics
)paren
(paren
id|dasd_characteristics_t
op_star
)paren
suffix:semicolon
DECL|member|fill_sizes_first
id|cqr_t
op_star
(paren
op_star
id|fill_sizes_first
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|fill_sizes_last
r_int
(paren
op_star
id|fill_sizes_last
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|dasd_format
r_int
(paren
op_star
id|dasd_format
)paren
(paren
r_int
comma
id|format_data_t
op_star
)paren
suffix:semicolon
DECL|typedef|dasd_operations_t
)brace
id|dasd_operations_t
suffix:semicolon
r_extern
id|dasd_information_t
op_star
id|dasd_info
(braket
)braket
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* DASD_TYPES_H */
eof
