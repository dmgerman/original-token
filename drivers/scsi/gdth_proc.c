multiline_comment|/* gdth_proc.c &n; * $Id: gdth_proc.c,v 1.6 1997/10/31 10:36:24 achim Exp $&n; */
macro_line|#include &quot;gdth_ioctl.h&quot;
DECL|function|gdth_proc_info
r_int
id|gdth_proc_info
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
id|hostno
comma
r_int
id|inout
)paren
(brace
r_int
id|hanum
comma
id|busnum
comma
id|i
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_proc_info() length %d ha %d offs %d inout %d&bslash;n&quot;
comma
id|length
comma
id|hostno
comma
id|offset
comma
id|inout
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|gdth_ctr_vcount
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|gdth_ctr_vtab
(braket
id|i
)braket
op_member_access_from_pointer
id|host_no
op_eq
id|hostno
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|gdth_ctr_vcount
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hanum
op_assign
id|NUMDATA
c_func
(paren
id|gdth_ctr_vtab
(braket
id|i
)braket
)paren
op_member_access_from_pointer
id|hanum
suffix:semicolon
id|busnum
op_assign
id|NUMDATA
c_func
(paren
id|gdth_ctr_vtab
(braket
id|i
)braket
)paren
op_member_access_from_pointer
id|busnum
suffix:semicolon
r_if
c_cond
(paren
id|inout
)paren
r_return
id|gdth_set_info
c_func
(paren
id|buffer
comma
id|length
comma
id|i
comma
id|hanum
comma
id|busnum
)paren
suffix:semicolon
r_else
r_return
id|gdth_get_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
comma
id|i
comma
id|hanum
comma
id|busnum
)paren
suffix:semicolon
)brace
DECL|function|gdth_set_info
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
(brace
r_int
id|ret_val
suffix:semicolon
id|Scsi_Cmnd
id|scp
suffix:semicolon
id|Scsi_Device
id|sdev
suffix:semicolon
id|gdth_iowr_str
op_star
id|piowr
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_set_info() ha %d bus %d&bslash;n&quot;
comma
id|hanum
comma
id|busnum
)paren
)paren
suffix:semicolon
id|piowr
op_assign
(paren
id|gdth_iowr_str
op_star
)paren
id|buffer
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sdev
comma
l_int|0
comma
r_sizeof
(paren
id|Scsi_Device
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|scp
comma
l_int|0
comma
r_sizeof
(paren
id|Scsi_Cmnd
)paren
)paren
suffix:semicolon
id|sdev.host
op_assign
id|gdth_ctr_vtab
(braket
id|vh
)braket
suffix:semicolon
id|sdev.id
op_assign
id|sdev.host-&gt;this_id
suffix:semicolon
id|scp.cmd_len
op_assign
l_int|12
suffix:semicolon
id|scp.host
op_assign
id|gdth_ctr_vtab
(braket
id|vh
)braket
suffix:semicolon
id|scp.target
op_assign
id|sdev.host-&gt;this_id
suffix:semicolon
id|scp.device
op_assign
op_amp
id|sdev
suffix:semicolon
id|scp.use_sg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;gdth&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|5
suffix:semicolon
id|length
op_sub_assign
l_int|5
suffix:semicolon
id|ret_val
op_assign
id|gdth_set_asc_info
c_func
(paren
id|buffer
comma
id|length
comma
id|hanum
comma
id|scp
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|piowr-&gt;magic
op_eq
id|GDTIOCTL_MAGIC
)paren
(brace
id|ret_val
op_assign
id|gdth_set_bin_info
c_func
(paren
id|buffer
comma
id|length
comma
id|hanum
comma
id|scp
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;GDT: Wrong signature: %6s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
id|ret_val
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_else
(brace
id|ret_val
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|ret_val
suffix:semicolon
)brace
DECL|function|gdth_set_asc_info
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
id|scp
)paren
(brace
r_int
id|orig_length
comma
id|drive
comma
id|wb_mode
suffix:semicolon
r_char
id|cmnd
(braket
l_int|12
)braket
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|found
suffix:semicolon
id|gdth_ha_str
op_star
id|ha
suffix:semicolon
id|gdth_cmd_str
id|gdtcmd
suffix:semicolon
id|gdth_cpar_str
op_star
id|pcpar
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_set_asc_info() ha %d&bslash;n&quot;
comma
id|hanum
)paren
)paren
suffix:semicolon
id|ha
op_assign
id|HADATA
c_func
(paren
id|gdth_ctr_tab
(braket
id|hanum
)braket
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cmnd
comma
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|orig_length
op_assign
id|length
op_plus
l_int|5
suffix:semicolon
id|drive
op_assign
op_minus
l_int|1
suffix:semicolon
id|wb_mode
op_assign
l_int|0
suffix:semicolon
id|found
op_assign
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|5
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;flush&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|6
suffix:semicolon
id|length
op_sub_assign
l_int|6
suffix:semicolon
r_if
c_cond
(paren
id|length
op_logical_and
op_star
id|buffer
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|buffer
op_le
l_char|&squot;9&squot;
)paren
(brace
id|drive
op_assign
(paren
r_int
)paren
(paren
op_star
id|buffer
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
op_decrement
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
op_logical_and
op_star
id|buffer
op_ge
l_char|&squot;0&squot;
op_logical_and
op_star
id|buffer
op_le
l_char|&squot;9&squot;
)paren
(brace
id|drive
op_assign
id|drive
op_star
l_int|10
op_plus
(paren
r_int
)paren
(paren
op_star
id|buffer
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
op_increment
id|buffer
suffix:semicolon
op_decrement
id|length
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;GDT: Flushing host drive %d .. &quot;
comma
id|drive
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;GDT: Flushing all host drives .. &quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAXBUS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAXID
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|ha-&gt;id
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|type
op_eq
id|CACHE_DTYP
)paren
(brace
r_if
c_cond
(paren
id|drive
op_ne
op_minus
l_int|1
op_logical_and
id|ha-&gt;id
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|hostdrive
op_ne
(paren
id|ushort
)paren
id|drive
)paren
r_continue
suffix:semicolon
id|found
op_assign
id|TRUE
suffix:semicolon
id|gdtcmd.BoardNode
op_assign
id|LOCALBOARD
suffix:semicolon
id|gdtcmd.Service
op_assign
id|CACHESERVICE
suffix:semicolon
id|gdtcmd.OpCode
op_assign
id|GDT_FLUSH
suffix:semicolon
id|gdtcmd.u.cache.DeviceNo
op_assign
id|ha-&gt;id
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|hostdrive
suffix:semicolon
id|gdtcmd.u.cache.BlockNo
op_assign
l_int|1
suffix:semicolon
id|gdtcmd.u.cache.sg_canz
op_assign
l_int|0
suffix:semicolon
(brace
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
id|scp.request.rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|scp.request.sem
op_assign
op_amp
id|sem
suffix:semicolon
id|scsi_do_cmd
c_func
(paren
op_amp
id|scp
comma
id|cmnd
comma
op_amp
id|gdtcmd
comma
r_sizeof
(paren
id|gdth_cmd_str
)paren
comma
id|gdth_scsi_done
comma
l_int|30
op_star
id|HZ
comma
l_int|1
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nNo host drive found !&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|orig_length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
op_ge
l_int|7
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;wbp_off&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|8
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GDT: Disabling write back permanently .. &quot;
)paren
suffix:semicolon
id|wb_mode
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|length
op_ge
l_int|6
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;wbp_on&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|7
suffix:semicolon
id|length
op_sub_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GDT: Enabling write back permanently .. &quot;
)paren
suffix:semicolon
id|wb_mode
op_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|length
op_ge
l_int|6
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;wb_off&quot;
comma
l_int|6
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|7
suffix:semicolon
id|length
op_sub_assign
l_int|7
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GDT: Disabling write back commands .. &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;cache_feat
op_amp
id|GDT_WR_THROUGH
)paren
(brace
id|gdth_write_through
op_assign
id|TRUE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Not supported !&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|orig_length
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|length
op_ge
l_int|5
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;wb_on&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|6
suffix:semicolon
id|length
op_sub_assign
l_int|6
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GDT: Enabling write back commands .. &quot;
)paren
suffix:semicolon
id|gdth_write_through
op_assign
id|FALSE
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|orig_length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wb_mode
)paren
(brace
id|pcpar
op_assign
(paren
id|gdth_cpar_str
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|gdth_cpar_str
)paren
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcpar
op_eq
l_int|NULL
)paren
(brace
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_set_info(): Unable to allocate memory.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unable to allocate memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|pcpar
comma
op_amp
id|ha-&gt;cpar
comma
r_sizeof
(paren
id|gdth_cpar_str
)paren
)paren
suffix:semicolon
id|gdtcmd.BoardNode
op_assign
id|LOCALBOARD
suffix:semicolon
id|gdtcmd.Service
op_assign
id|CACHESERVICE
suffix:semicolon
id|gdtcmd.OpCode
op_assign
id|GDT_IOCTL
suffix:semicolon
id|gdtcmd.u.ioctl.p_param
op_assign
id|virt_to_bus
c_func
(paren
id|pcpar
)paren
suffix:semicolon
id|gdtcmd.u.ioctl.param_size
op_assign
r_sizeof
(paren
id|gdth_cpar_str
)paren
suffix:semicolon
id|gdtcmd.u.ioctl.subfunc
op_assign
id|CACHE_CONFIG
suffix:semicolon
id|gdtcmd.u.ioctl.channel
op_assign
id|INVALID_CHANNEL
suffix:semicolon
id|pcpar-&gt;write_back
op_assign
id|wb_mode
op_eq
l_int|1
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
(brace
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
id|scp.request.rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|scp.request.sem
op_assign
op_amp
id|sem
suffix:semicolon
id|scsi_do_cmd
c_func
(paren
op_amp
id|scp
comma
id|cmnd
comma
op_amp
id|gdtcmd
comma
r_sizeof
(paren
id|gdth_cmd_str
)paren
comma
id|gdth_scsi_done
comma
l_int|30
op_star
id|HZ
comma
l_int|1
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|pcpar
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|orig_length
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;GDT: Unknown command: %s  Length: %d&bslash;n&quot;
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|gdth_set_bin_info
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
id|scp
)paren
(brace
r_char
id|cmnd
(braket
l_int|12
)braket
suffix:semicolon
r_int
id|id
suffix:semicolon
id|unchar
id|i
comma
id|j
comma
id|k
comma
id|found
suffix:semicolon
id|gdth_ha_str
op_star
id|ha
suffix:semicolon
id|gdth_iowr_str
op_star
id|piowr
suffix:semicolon
id|gdth_iord_str
op_star
id|piord
suffix:semicolon
id|gdth_cmd_str
op_star
id|pcmd
suffix:semicolon
id|ulong
op_star
id|ppadd
suffix:semicolon
id|ulong
id|add_size
comma
id|flags
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_set_bin_info() ha %d&bslash;n&quot;
comma
id|hanum
)paren
)paren
suffix:semicolon
id|ha
op_assign
id|HADATA
c_func
(paren
id|gdth_ctr_tab
(braket
id|hanum
)braket
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cmnd
comma
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|piowr
op_assign
(paren
id|gdth_iowr_str
op_star
)paren
id|buffer
suffix:semicolon
id|piord
op_assign
l_int|NULL
suffix:semicolon
id|pcmd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|GDTOFFSOF
c_func
(paren
id|gdth_iowr_str
comma
id|iu
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|piowr-&gt;ioctl
)paren
(brace
r_case
id|GDTIOCTL_GENERAL
suffix:colon
r_if
c_cond
(paren
id|length
OL
id|GDTOFFSOF
c_func
(paren
id|gdth_iowr_str
comma
id|iu.general.data
(braket
l_int|0
)braket
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pcmd
op_assign
(paren
id|gdth_cmd_str
op_star
)paren
id|piowr-&gt;iu.general.command
suffix:semicolon
id|pcmd-&gt;Service
op_assign
id|piowr-&gt;service
suffix:semicolon
r_if
c_cond
(paren
id|pcmd-&gt;OpCode
op_eq
id|GDT_IOCTL
)paren
(brace
id|ppadd
op_assign
op_amp
id|pcmd-&gt;u.ioctl.p_param
suffix:semicolon
id|add_size
op_assign
id|pcmd-&gt;u.ioctl.param_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|piowr-&gt;service
op_eq
id|CACHESERVICE
)paren
(brace
id|add_size
op_assign
id|pcmd-&gt;u.cache.BlockCnt
op_star
id|SECTOR_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;cache_feat
op_amp
id|SCATTER_GATHER
)paren
(brace
id|ppadd
op_assign
op_amp
id|pcmd-&gt;u.cache.sg_lst
(braket
l_int|0
)braket
dot
id|sg_ptr
suffix:semicolon
id|pcmd-&gt;u.cache.DestAddr
op_assign
op_minus
l_int|1UL
suffix:semicolon
id|pcmd-&gt;u.cache.sg_lst
(braket
l_int|0
)braket
dot
id|sg_len
op_assign
id|add_size
suffix:semicolon
id|pcmd-&gt;u.cache.sg_canz
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ppadd
op_assign
op_amp
id|pcmd-&gt;u.cache.DestAddr
suffix:semicolon
id|pcmd-&gt;u.cache.sg_canz
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|piowr-&gt;service
op_eq
id|SCSIRAWSERVICE
)paren
(brace
id|add_size
op_assign
id|pcmd-&gt;u.raw.sdlen
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;raw_feat
op_amp
id|SCATTER_GATHER
)paren
(brace
id|ppadd
op_assign
op_amp
id|pcmd-&gt;u.raw.sg_lst
(braket
l_int|0
)braket
dot
id|sg_ptr
suffix:semicolon
id|pcmd-&gt;u.raw.sdata
op_assign
op_minus
l_int|1UL
suffix:semicolon
id|pcmd-&gt;u.raw.sg_lst
(braket
l_int|0
)braket
dot
id|sg_len
op_assign
id|add_size
suffix:semicolon
id|pcmd-&gt;u.raw.sg_ranz
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ppadd
op_assign
op_amp
id|pcmd-&gt;u.raw.sdata
suffix:semicolon
id|pcmd-&gt;u.raw.sg_ranz
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
op_plus
id|add_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
op_plus
id|add_size
suffix:semicolon
r_if
c_cond
(paren
id|add_size
OG
l_int|0
)paren
(brace
id|memcpy
c_func
(paren
id|piord-&gt;iu.general.data
comma
id|piowr-&gt;iu.general.data
comma
id|add_size
)paren
suffix:semicolon
op_star
id|ppadd
op_assign
id|virt_to_bus
c_func
(paren
id|piord-&gt;iu.general.data
)paren
suffix:semicolon
)brace
multiline_comment|/* do IOCTL */
(brace
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
id|scp.request.rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|scp.request.sem
op_assign
op_amp
id|sem
suffix:semicolon
id|scp.SCp.this_residual
op_assign
id|IOCTL_PRI
suffix:semicolon
id|scsi_do_cmd
c_func
(paren
op_amp
id|scp
comma
id|cmnd
comma
id|pcmd
comma
r_sizeof
(paren
id|gdth_cmd_str
)paren
comma
id|gdth_scsi_done
comma
id|piowr-&gt;timeout
op_star
id|HZ
comma
l_int|1
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
(paren
id|ulong
)paren
id|scp.SCp.Message
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|GDTIOCTL_DRVERS
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
id|piord-&gt;iu.drvers.version
op_assign
(paren
id|GDTH_VERSION
op_lshift
l_int|8
)paren
op_or
id|GDTH_SUBVERSION
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_CTRTYPE
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;type
op_eq
id|GDT_ISA
op_logical_or
id|ha-&gt;type
op_eq
id|GDT_EISA
)paren
(brace
id|piord-&gt;iu.ctrtype.type
op_assign
(paren
id|unchar
)paren
(paren
(paren
id|ha-&gt;stype
op_rshift
l_int|20
)paren
op_minus
l_int|10
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ha-&gt;type
op_ne
id|GDT_PCIMPR
)paren
(brace
id|piord-&gt;iu.ctrtype.type
op_assign
(paren
id|unchar
)paren
(paren
(paren
id|ha-&gt;stype
op_lshift
l_int|8
)paren
op_plus
l_int|6
)paren
suffix:semicolon
)brace
r_else
(brace
id|piord-&gt;iu.ctrtype.type
op_assign
l_int|0xfe
suffix:semicolon
id|piord-&gt;iu.ctrtype.ext_type
op_assign
l_int|0x6000
op_or
id|ha-&gt;stype
suffix:semicolon
)brace
id|piord-&gt;iu.ctrtype.info
op_assign
id|ha-&gt;brd_phys
suffix:semicolon
id|piord-&gt;iu.ctrtype.oem_id
op_assign
(paren
id|ushort
)paren
id|GDT3_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_CTRCNT
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
id|piord-&gt;iu.ctrcnt.count
op_assign
(paren
id|ushort
)paren
id|gdth_ctr_count
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_OSVERS
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
id|piord-&gt;iu.osvers.version
op_assign
(paren
id|unchar
)paren
(paren
id|LINUX_VERSION_CODE
op_rshift
l_int|16
)paren
suffix:semicolon
id|piord-&gt;iu.osvers.subversion
op_assign
(paren
id|unchar
)paren
(paren
id|LINUX_VERSION_CODE
op_rshift
l_int|8
)paren
suffix:semicolon
id|piord-&gt;iu.osvers.revision
op_assign
(paren
id|ushort
)paren
(paren
id|LINUX_VERSION_CODE
op_amp
l_int|0xff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_LOCKDRV
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|k
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|piowr-&gt;iu.lockdrv.drive_cnt
suffix:semicolon
op_increment
id|i
)paren
(brace
id|found
op_assign
id|FALSE
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ha-&gt;bus_cnt
suffix:semicolon
op_increment
id|j
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|MAXID
suffix:semicolon
op_increment
id|k
)paren
(brace
r_if
c_cond
(paren
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|type
op_eq
id|CACHE_DTYP
op_logical_and
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|hostdrive
op_eq
id|piowr-&gt;iu.lockdrv.drives
(braket
id|i
)braket
)paren
(brace
id|found
op_assign
id|TRUE
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|piowr-&gt;iu.lockdrv.lock
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|lock
op_assign
l_int|1
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gdth_wait_completion
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
id|gdth_stop_timeout
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
)brace
r_else
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|lock
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gdth_start_timeout
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
id|gdth_next
c_func
(paren
id|hanum
)paren
suffix:semicolon
)brace
)brace
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_LOCKCHN
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
comma
id|j
op_assign
id|piowr-&gt;iu.lockchn.channel
suffix:semicolon
id|k
OL
id|MAXID
suffix:semicolon
op_increment
id|k
)paren
(brace
r_if
c_cond
(paren
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|type
op_ne
id|RAW_DTYP
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|piowr-&gt;iu.lockchn.lock
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|lock
op_assign
l_int|1
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gdth_wait_completion
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
id|gdth_stop_timeout
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
)brace
r_else
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha-&gt;id
(braket
id|j
)braket
(braket
id|k
)braket
dot
id|lock
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gdth_start_timeout
c_func
(paren
id|hanum
comma
id|j
comma
id|k
)paren
suffix:semicolon
id|gdth_next
c_func
(paren
id|hanum
)paren
suffix:semicolon
)brace
)brace
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GDTIOCTL_EVENT
suffix:colon
id|id
op_assign
id|gdth_ioctl_alloc
c_func
(paren
id|hanum
comma
r_sizeof
(paren
id|gdth_iord_str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
r_if
c_cond
(paren
id|piowr-&gt;iu.event.erase
op_eq
l_int|0
)paren
(brace
id|piord-&gt;iu.event.handle
op_assign
id|gdth_read_event
c_func
(paren
id|piowr-&gt;iu.event.handle
comma
(paren
id|gdth_evt_str
op_star
)paren
id|piord-&gt;iu.event.evt
)paren
suffix:semicolon
)brace
r_else
(brace
id|piord-&gt;iu.event.handle
op_assign
id|piowr-&gt;iu.event.handle
suffix:semicolon
id|gdth_readapp_event
c_func
(paren
(paren
id|unchar
)paren
id|piowr-&gt;iu.event.erase
comma
(paren
id|gdth_evt_str
op_star
)paren
id|piord-&gt;iu.event.evt
)paren
suffix:semicolon
)brace
id|piord-&gt;size
op_assign
r_sizeof
(paren
id|gdth_iord_str
)paren
suffix:semicolon
id|piord-&gt;status
op_assign
id|S_OK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* we return a buffer ID to detect the right buffer during READ-IOCTL */
r_return
id|id
suffix:semicolon
)brace
DECL|function|gdth_get_info
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
(brace
r_int
id|size
op_assign
l_int|0
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
comma
id|pos
op_assign
l_int|0
suffix:semicolon
id|gdth_ha_str
op_star
id|ha
suffix:semicolon
id|gdth_iord_str
op_star
id|piord
suffix:semicolon
r_int
id|id
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_get_info() ha %d bus %d&bslash;n&quot;
comma
id|hanum
comma
id|busnum
)paren
)paren
suffix:semicolon
id|ha
op_assign
id|HADATA
c_func
(paren
id|gdth_ctr_tab
(braket
id|hanum
)braket
)paren
suffix:semicolon
id|id
op_assign
id|length
suffix:semicolon
multiline_comment|/* look for buffer ID in length */
r_if
c_cond
(paren
id|id
OG
l_int|4
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020000
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%s SCSI Disk Array Controller&bslash;n&quot;
comma
id|gdth_ctr_name
c_func
(paren
id|hanum
)paren
)paren
suffix:semicolon
macro_line|#else
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%s SCSI Disk Array Controller (SCSI Bus %d)&bslash;n&quot;
comma
id|gdth_ctr_name
c_func
(paren
id|hanum
)paren
comma
id|busnum
)paren
suffix:semicolon
macro_line|#endif
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Firmware Version: %d.%2d&bslash;tDriver Version: %s&bslash;n&quot;
comma
(paren
id|unchar
)paren
(paren
id|ha-&gt;cpar.version
op_rshift
l_int|8
)paren
comma
(paren
id|unchar
)paren
(paren
id|ha-&gt;cpar.version
)paren
comma
id|GDTH_VERSION_STR
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_goto
id|stop_output
suffix:semicolon
)brace
r_else
(brace
id|piord
op_assign
(paren
id|gdth_iord_str
op_star
)paren
id|gdth_ioctl_tab
(braket
id|id
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
suffix:semicolon
r_if
c_cond
(paren
id|piord
op_eq
l_int|NULL
)paren
r_goto
id|stop_output
suffix:semicolon
id|length
op_assign
id|piord-&gt;size
suffix:semicolon
id|memcpy
c_func
(paren
id|buffer
op_plus
id|len
comma
(paren
r_char
op_star
)paren
id|piord
comma
id|length
)paren
suffix:semicolon
id|gdth_ioctl_free
c_func
(paren
id|hanum
comma
id|id
)paren
suffix:semicolon
id|len
op_add_assign
id|length
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_goto
id|stop_output
suffix:semicolon
)brace
id|stop_output
suffix:colon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
id|TRACE2
c_func
(paren
(paren
l_string|&quot;get_info() len %d pos %d begin %d offset %d length %d size %d&bslash;n&quot;
comma
id|len
comma
id|pos
comma
id|begin
comma
id|offset
comma
id|length
comma
id|size
)paren
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|gdth_scsi_done
r_void
id|gdth_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
(brace
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_scsi_done()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|scp-&gt;request.rq_status
op_assign
id|RQ_SCSI_DONE
suffix:semicolon
r_if
c_cond
(paren
id|scp-&gt;request.sem
op_ne
l_int|NULL
)paren
id|up
c_func
(paren
id|scp-&gt;request.sem
)paren
suffix:semicolon
)brace
DECL|function|gdth_ioctl_alloc
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
(brace
id|ulong
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|gdth_ioctl_tab
(braket
id|i
)braket
(braket
id|hanum
)braket
op_eq
l_int|NULL
)paren
(brace
id|gdth_ioctl_tab
(braket
id|i
)braket
(braket
id|hanum
)braket
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|4
op_logical_or
id|gdth_ioctl_tab
(braket
id|i
)braket
(braket
id|hanum
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|i
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|gdth_ioctl_free
r_static
r_void
id|gdth_ioctl_free
c_func
(paren
r_int
id|hanum
comma
r_int
id|idx
)paren
(brace
id|ulong
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gdth_ioctl_tab
(braket
id|idx
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
)paren
suffix:semicolon
id|gdth_ioctl_tab
(braket
id|idx
op_minus
l_int|1
)braket
(braket
id|hanum
)braket
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|gdth_wait_completion
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
(brace
id|ulong
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|Scsi_Cmnd
op_star
id|scp
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|GDTH_MAXCMDS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|scp
op_assign
id|gdth_cmd_tab
(braket
id|i
)braket
(braket
id|hanum
)braket
dot
id|cmnd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SPECIAL_SCP
c_func
(paren
id|scp
)paren
op_logical_and
id|scp-&gt;target
op_eq
(paren
id|unchar
)paren
id|id
op_logical_and
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020000
id|scp-&gt;channel
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#else
id|NUMDATA
c_func
(paren
id|scp-&gt;host
)paren
op_member_access_from_pointer
id|busnum
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#endif
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|scp-&gt;SCp.have_data_in
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|gdth_stop_timeout
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
(brace
id|ulong
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|scp
suffix:semicolon
id|gdth_ha_str
op_star
id|ha
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha
op_assign
id|HADATA
c_func
(paren
id|gdth_ctr_tab
(braket
id|hanum
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|scp
op_assign
id|ha-&gt;req_first
suffix:semicolon
id|scp
suffix:semicolon
id|scp
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|scp-&gt;SCp.ptr
)paren
(brace
r_if
c_cond
(paren
id|scp-&gt;target
op_eq
(paren
id|unchar
)paren
id|id
op_logical_and
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020000
id|scp-&gt;channel
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#else
id|NUMDATA
c_func
(paren
id|scp-&gt;host
)paren
op_member_access_from_pointer
id|busnum
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#endif
(brace
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_stop_timeout(): update_timeout()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|scp-&gt;SCp.buffers_residual
op_assign
id|gdth_update_timeout
c_func
(paren
id|scp
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|gdth_start_timeout
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
(brace
id|ulong
id|flags
suffix:semicolon
id|Scsi_Cmnd
op_star
id|scp
suffix:semicolon
id|gdth_ha_str
op_star
id|ha
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ha
op_assign
id|HADATA
c_func
(paren
id|gdth_ctr_tab
(braket
id|hanum
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|scp
op_assign
id|ha-&gt;req_first
suffix:semicolon
id|scp
suffix:semicolon
id|scp
op_assign
(paren
id|Scsi_Cmnd
op_star
)paren
id|scp-&gt;SCp.ptr
)paren
(brace
r_if
c_cond
(paren
id|scp-&gt;target
op_eq
(paren
id|unchar
)paren
id|id
op_logical_and
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020000
id|scp-&gt;channel
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#else
id|NUMDATA
c_func
(paren
id|scp-&gt;host
)paren
op_member_access_from_pointer
id|busnum
op_eq
(paren
id|unchar
)paren
id|busnum
)paren
macro_line|#endif
(brace
id|TRACE2
c_func
(paren
(paren
l_string|&quot;gdth_start_timeout(): update_timeout()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|gdth_update_timeout
c_func
(paren
id|scp
comma
id|scp-&gt;SCp.buffers_residual
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|gdth_update_timeout
r_static
r_int
id|gdth_update_timeout
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
comma
r_int
id|timeout
)paren
(brace
id|ulong
id|flags
suffix:semicolon
r_int
id|oldto
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|oldto
op_assign
id|scp-&gt;timeout
suffix:semicolon
id|scp-&gt;timeout
op_assign
id|timeout
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|timer_table
(braket
id|GDTH_TIMER
)braket
dot
id|expires
op_eq
l_int|0
)paren
(brace
id|timer_table
(braket
id|GDTH_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|GDTH_TIMER
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|jiffies
op_plus
id|timeout
OL
id|timer_table
(braket
id|GDTH_TIMER
)braket
dot
id|expires
)paren
id|timer_table
(braket
id|GDTH_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
id|timeout
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|oldto
suffix:semicolon
)brace
eof
