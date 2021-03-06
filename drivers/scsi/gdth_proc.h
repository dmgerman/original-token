macro_line|#ifndef _GDTH_PROC_H
DECL|macro|_GDTH_PROC_H
mdefine_line|#define _GDTH_PROC_H
multiline_comment|/* gdth_proc.h &n; * $Id: gdth_proc.h,v 1.6 1999/03/05 14:32:36 achim Exp $&n; */
r_static
r_int
id|gdth_set_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|vh
comma
r_int
id|hanum
comma
r_int
id|busnum
)paren
suffix:semicolon
r_static
r_int
id|gdth_set_asc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_static
r_int
id|gdth_set_bin_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_static
r_int
id|gdth_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|vh
comma
r_int
id|hanum
comma
r_int
id|busnum
)paren
suffix:semicolon
r_static
r_int
id|gdth_ioctl_alloc
c_func
(paren
r_int
id|hanum
comma
id|ushort
id|size
)paren
suffix:semicolon
r_static
r_void
id|gdth_ioctl_free
c_func
(paren
r_int
id|hanum
)paren
suffix:semicolon
r_static
r_void
id|gdth_wait_completion
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_void
id|gdth_stop_timeout
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_void
id|gdth_start_timeout
c_func
(paren
r_int
id|hanum
comma
r_int
id|busnum
comma
r_int
id|id
)paren
suffix:semicolon
r_static
r_int
id|gdth_update_timeout
c_func
(paren
r_int
id|hanum
comma
id|Scsi_Cmnd
op_star
id|scp
comma
r_int
id|timeout
)paren
suffix:semicolon
r_static
r_void
id|gdth_do_cmd
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
comma
id|gdth_cmd_str
op_star
id|cmd
comma
r_int
id|timeout
)paren
suffix:semicolon
r_void
id|gdth_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
macro_line|#endif
eof
