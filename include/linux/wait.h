macro_line|#ifndef _LINUX_WAIT_H
DECL|macro|_LINUX_WAIT_H
mdefine_line|#define _LINUX_WAIT_H
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;0x00000001
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;0x00000002
DECL|macro|__WCLONE
mdefine_line|#define __WCLONE&t;0x80000000
DECL|struct|wait_queue
r_struct
id|wait_queue
(brace
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|next
r_struct
id|wait_queue
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|select_table_entry
r_struct
id|select_table_entry
(brace
DECL|member|wait
r_struct
id|wait_queue
id|wait
suffix:semicolon
DECL|member|wait_address
r_struct
id|wait_queue
op_star
op_star
id|wait_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|select_table_struct
r_typedef
r_struct
id|select_table_struct
(brace
DECL|member|nr
r_int
id|nr
suffix:semicolon
DECL|member|entry
r_struct
id|select_table_entry
op_star
id|entry
suffix:semicolon
DECL|typedef|select_table
)brace
id|select_table
suffix:semicolon
DECL|macro|__MAX_SELECT_TABLE_ENTRIES
mdefine_line|#define __MAX_SELECT_TABLE_ENTRIES (4096 / sizeof (struct select_table_entry))
macro_line|#endif
eof
