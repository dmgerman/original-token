macro_line|#include &lt;linux/config.h&gt;
DECL|function|swap_statistics
r_void
id|swap_statistics
c_func
(paren
id|u8
op_star
id|p
)paren
(brace
id|u32
id|y
suffix:semicolon
id|u32
op_star
id|lp
comma
id|h_lp
suffix:semicolon
id|u16
op_star
id|sp
comma
id|h_sp
suffix:semicolon
id|u8
op_star
id|bp
suffix:semicolon
id|lp
op_assign
(paren
id|u32
op_star
)paren
id|p
suffix:semicolon
id|sp
op_assign
(paren
(paren
r_int
op_star
)paren
id|lp
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Convert Header */
id|h_sp
op_assign
op_star
id|sp
op_assign
id|ntohs
c_func
(paren
op_star
id|sp
)paren
suffix:semicolon
id|lp
op_increment
suffix:semicolon
r_do
(brace
id|sp
op_assign
(paren
id|u16
op_star
)paren
id|lp
suffix:semicolon
multiline_comment|/* Convert SubHeader */
op_star
id|sp
op_assign
id|ntohs
c_func
(paren
op_star
id|sp
)paren
suffix:semicolon
id|bp
op_assign
(paren
id|u8
op_star
)paren
id|lp
suffix:semicolon
id|y
op_assign
op_star
(paren
id|bp
op_plus
l_int|3
)paren
suffix:semicolon
id|lp
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|h_lp
op_assign
(paren
id|u32
)paren
id|lp
suffix:semicolon
(paren
id|u32
)paren
id|lp
OL
id|h_lp
op_plus
(paren
(paren
id|u32
)paren
op_star
(paren
id|bp
op_plus
l_int|3
)paren
)paren
suffix:semicolon
id|lp
op_increment
)paren
op_star
id|lp
op_assign
id|ntohl
c_func
(paren
op_star
id|lp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|u32
)paren
id|lp
OL
(paren
(paren
id|u32
)paren
id|p
)paren
op_plus
l_int|4
op_plus
id|h_sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * eata_set_info&n; * buffer : pointer to the data that has been written to the hostfile&n; * length : number of bytes written to the hostfile&n; * HBA_ptr: pointer to the Scsi_Host struct&n; */
DECL|function|eata_set_info
r_int
id|eata_set_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
comma
r_struct
id|Scsi_Host
op_star
id|HBA_ptr
)paren
(brace
r_int
id|orig_length
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|8
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;eata_dma&quot;
comma
l_int|8
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|9
suffix:semicolon
id|length
op_sub_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|8
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;latency&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|do_latency
op_assign
id|TRUE
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
l_int|10
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;nolatency&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
(brace
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|do_latency
op_assign
id|FALSE
suffix:semicolon
r_return
id|orig_length
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Unknown command:%s length: %d&bslash;n&quot;
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;Wrong Signature:%10s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * eata_proc_info&n; * inout : decides on the direction of the dataflow and the meaning of the &n; *&t;   variables&n; * buffer: If inout==FALSE data is being written to it else read from it&n; * *start: If inout==FALSE start of the valid data in the buffer&n; * offset: If inout==FALSE offset from the beginning of the imaginary file &n; *&t;   from which we start writing into the buffer&n; * length: If inout==FALSE max number of bytes to be written into the buffer &n; *&t;   else number of bytes in the buffer&n; */
DECL|function|eata_proc_info
r_int
id|eata_proc_info
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
macro_line|#ifdef CONFIG_PROC_FS
id|Scsi_Device
op_star
id|scd
comma
id|SDev
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|HBA_ptr
suffix:semicolon
id|Scsi_Cmnd
id|scmd
suffix:semicolon
r_char
id|cmnd
(braket
l_int|10
)braket
suffix:semicolon
r_static
id|u8
id|buff
(braket
l_int|512
)braket
suffix:semicolon
r_static
id|u8
id|buff2
(braket
l_int|512
)braket
suffix:semicolon
id|hst_cmd_stat
op_star
id|rhcs
comma
op_star
id|whcs
suffix:semicolon
id|coco
op_star
id|cc
suffix:semicolon
id|scsitrans
op_star
id|st
suffix:semicolon
id|scsimod
op_star
id|sm
suffix:semicolon
id|hobu
op_star
id|hb
suffix:semicolon
id|scbu
op_star
id|sb
suffix:semicolon
id|boty
op_star
id|bt
suffix:semicolon
id|memco
op_star
id|mc
suffix:semicolon
id|firm
op_star
id|fm
suffix:semicolon
id|subinf
op_star
id|si
suffix:semicolon
id|pcinf
op_star
id|pi
suffix:semicolon
id|arrlim
op_star
id|al
suffix:semicolon
r_int
id|i
comma
id|x
suffix:semicolon
r_int
id|size
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|scd
op_assign
l_int|NULL
suffix:semicolon
id|HBA_ptr
op_assign
id|first_HBA
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|registered_HBAs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|HBA_ptr-&gt;host_no
op_eq
id|hostno
)paren
r_break
suffix:semicolon
id|HBA_ptr
op_assign
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inout
op_eq
id|TRUE
)paren
(brace
multiline_comment|/* Has data been written to the file ? */
r_return
id|eata_set_info
c_func
(paren
id|buffer
comma
id|length
comma
id|HBA_ptr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_eq
l_int|0
)paren
id|memset
c_func
(paren
id|buff
comma
l_int|0
comma
r_sizeof
(paren
id|buff
)paren
)paren
suffix:semicolon
id|cc
op_assign
(paren
id|coco
op_star
)paren
(paren
id|buff
op_plus
l_int|0x148
)paren
suffix:semicolon
id|st
op_assign
(paren
id|scsitrans
op_star
)paren
(paren
id|buff
op_plus
l_int|0x164
)paren
suffix:semicolon
id|sm
op_assign
(paren
id|scsimod
op_star
)paren
(paren
id|buff
op_plus
l_int|0x16c
)paren
suffix:semicolon
id|hb
op_assign
(paren
id|hobu
op_star
)paren
(paren
id|buff
op_plus
l_int|0x172
)paren
suffix:semicolon
id|sb
op_assign
(paren
id|scbu
op_star
)paren
(paren
id|buff
op_plus
l_int|0x178
)paren
suffix:semicolon
id|bt
op_assign
(paren
id|boty
op_star
)paren
(paren
id|buff
op_plus
l_int|0x17e
)paren
suffix:semicolon
id|mc
op_assign
(paren
id|memco
op_star
)paren
(paren
id|buff
op_plus
l_int|0x186
)paren
suffix:semicolon
id|fm
op_assign
(paren
id|firm
op_star
)paren
(paren
id|buff
op_plus
l_int|0x18e
)paren
suffix:semicolon
id|si
op_assign
(paren
id|subinf
op_star
)paren
(paren
id|buff
op_plus
l_int|0x196
)paren
suffix:semicolon
id|pi
op_assign
(paren
id|pcinf
op_star
)paren
(paren
id|buff
op_plus
l_int|0x19c
)paren
suffix:semicolon
id|al
op_assign
(paren
id|arrlim
op_star
)paren
(paren
id|buff
op_plus
l_int|0x1a2
)paren
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
l_string|&quot;EATA (Extended Attachment) driver version: &quot;
l_string|&quot;%d.%d%s&bslash;n&quot;
comma
id|VER_MAJOR
comma
id|VER_MINOR
comma
id|VER_SUB
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;queued commands:     %10ld&bslash;n&quot;
l_string|&quot;processed interrupts:%10ld&bslash;n&quot;
comma
id|queue_counter
comma
id|int_counter
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nscsi%-2d: HBA %.10s&bslash;n&quot;
comma
id|HBA_ptr-&gt;host_no
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|name
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Firmware revision: v%s&bslash;n&quot;
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|revision
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Hardware Configuration:&bslash;n&quot;
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
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|broken_INQUIRY
op_eq
id|TRUE
)paren
(brace
r_if
c_cond
(paren
id|HBA_ptr-&gt;dma_channel
op_eq
id|BUSMASTER
)paren
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;DMA: BUSMASTER&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;DMA: %d&bslash;n&quot;
comma
id|HBA_ptr-&gt;dma_channel
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Base IO : %#.4x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|HBA_ptr-&gt;base
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Host Bus: EISA&bslash;n&quot;
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
)brace
r_else
(brace
id|memset
c_func
(paren
op_amp
id|SDev
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
id|scmd
comma
l_int|0
comma
r_sizeof
(paren
id|Scsi_Cmnd
)paren
)paren
suffix:semicolon
id|SDev.host
op_assign
id|HBA_ptr
suffix:semicolon
id|SDev.id
op_assign
id|HBA_ptr-&gt;this_id
suffix:semicolon
id|SDev.lun
op_assign
l_int|0
suffix:semicolon
id|SDev.channel
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|0
)braket
op_assign
id|LOG_SENSE
suffix:semicolon
id|cmnd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|2
)braket
op_assign
l_int|0x33
op_plus
(paren
l_int|3
op_lshift
l_int|6
)paren
suffix:semicolon
id|cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|7
)braket
op_assign
l_int|0x00
suffix:semicolon
id|cmnd
(braket
l_int|8
)braket
op_assign
l_int|0x66
suffix:semicolon
id|cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|scmd.cmd_len
op_assign
l_int|10
suffix:semicolon
id|scmd.host
op_assign
id|HBA_ptr
suffix:semicolon
id|scmd.device
op_assign
op_amp
id|SDev
suffix:semicolon
id|scmd.target
op_assign
id|HBA_ptr-&gt;this_id
suffix:semicolon
id|scmd.lun
op_assign
l_int|0
suffix:semicolon
id|scmd.channel
op_assign
l_int|0
suffix:semicolon
id|scmd.use_sg
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Do the command and wait for it to finish.&n;&t; */
(brace
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
id|scmd.request.rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|scmd.request.sem
op_assign
op_amp
id|sem
suffix:semicolon
id|scsi_do_cmd
(paren
op_amp
id|scmd
comma
id|cmnd
comma
id|buff
op_plus
l_int|0x144
comma
l_int|0x66
comma
id|eata_scsi_done
comma
l_int|1
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;IRQ: %2d, %s triggered&bslash;n&quot;
comma
id|cc-&gt;interrupt
comma
(paren
id|cc-&gt;intt
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;level&quot;
suffix:colon
l_string|&quot;edge&quot;
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
id|HBA_ptr-&gt;dma_channel
op_eq
l_int|0xff
)paren
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;DMA: BUSMASTER&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;DMA: %d&bslash;n&quot;
comma
id|HBA_ptr-&gt;dma_channel
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;CPU: MC680%02d %dMHz&bslash;n&quot;
comma
id|bt-&gt;cpu_type
comma
id|bt-&gt;cpu_speed
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Base IO : %#.4x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|HBA_ptr-&gt;base
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Host Bus: %s&bslash;n&quot;
comma
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|bustype
op_eq
id|IS_PCI
)paren
ques
c_cond
l_string|&quot;PCI &quot;
suffix:colon
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|bustype
op_eq
id|IS_EISA
)paren
ques
c_cond
l_string|&quot;EISA&quot;
suffix:colon
l_string|&quot;ISA &quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;SCSI Bus:%s%s Speed: %sMB/sec. %s&bslash;n&quot;
comma
(paren
id|sb-&gt;wide
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot; WIDE&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|sb-&gt;dif
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot; DIFFERENTIAL&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|sb-&gt;speed
op_eq
l_int|0
)paren
ques
c_cond
l_string|&quot;5&quot;
suffix:colon
(paren
id|sb-&gt;speed
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;10&quot;
suffix:colon
l_string|&quot;20&quot;
comma
(paren
id|sb-&gt;ext
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;With external cable detection&quot;
suffix:colon
l_string|&quot;&quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;SCSI channel expansion Module: %s present&bslash;n&quot;
comma
(paren
id|bt-&gt;sx1
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;SX1 (one channel)&quot;
suffix:colon
(paren
(paren
id|bt-&gt;sx2
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;SX2 (two channels)&quot;
suffix:colon
l_string|&quot;not&quot;
)paren
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;SmartRAID hardware: %spresent.&bslash;n&quot;
comma
(paren
id|cc-&gt;srs
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Type: %s&bslash;n&quot;
comma
(paren
(paren
id|cc-&gt;key
op_eq
id|TRUE
)paren
ques
c_cond
(paren
(paren
id|bt-&gt;dmi
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;integrated&quot;
suffix:colon
(paren
(paren
id|bt-&gt;dm4
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;DM401X&quot;
suffix:colon
(paren
id|bt-&gt;dm4k
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;DM4000&quot;
suffix:colon
l_string|&quot;-&quot;
)paren
)paren
suffix:colon
l_string|&quot;-&quot;
)paren
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Max array groups:              %d&bslash;n&quot;
comma
(paren
id|al-&gt;code
op_eq
l_int|0x0e
)paren
ques
c_cond
id|al-&gt;max_groups
suffix:colon
l_int|7
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Max drives per RAID 0 array:   %d&bslash;n&quot;
comma
(paren
id|al-&gt;code
op_eq
l_int|0x0e
)paren
ques
c_cond
id|al-&gt;raid0_drv
suffix:colon
l_int|7
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Max drives per RAID 3/5 array: %d&bslash;n&quot;
comma
(paren
id|al-&gt;code
op_eq
l_int|0x0e
)paren
ques
c_cond
id|al-&gt;raid35_drv
suffix:colon
l_int|7
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Cache Module: %spresent.&bslash;n&quot;
comma
(paren
id|cc-&gt;csh
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Type: %s&bslash;n&quot;
comma
(paren
(paren
id|cc-&gt;csh
op_eq
id|TRUE
)paren
ques
c_cond
(paren
(paren
id|bt-&gt;cmi
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;integrated&quot;
suffix:colon
(paren
(paren
id|bt-&gt;cm4
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;CM401X&quot;
suffix:colon
(paren
(paren
id|bt-&gt;cm4k
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;CM4000&quot;
suffix:colon
l_string|&quot;-&quot;
)paren
)paren
)paren
suffix:colon
l_string|&quot;-&quot;
)paren
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
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
op_le
l_int|3
suffix:semicolon
id|x
op_increment
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;    Bank%d: %dMB with%s ECC&bslash;n&quot;
comma
id|x
comma
id|mc-&gt;banksize
(braket
id|x
)braket
op_amp
l_int|0x7f
comma
(paren
id|mc-&gt;banksize
(braket
id|x
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;out&quot;
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
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Timer Mod.: %spresent&bslash;n&quot;
comma
(paren
id|cc-&gt;tmr
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;NVRAM     : %spresent&bslash;n&quot;
comma
(paren
id|cc-&gt;nvr
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;SmartROM  : %sabled&bslash;n&quot;
comma
(paren
id|bt-&gt;srom
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;dis&quot;
suffix:colon
l_string|&quot;en&quot;
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Alarm     : %s&bslash;n&quot;
comma
(paren
id|bt-&gt;alrm
op_eq
id|TRUE
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
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
r_if
c_cond
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|do_latency
op_eq
id|FALSE
)paren
(brace
id|cmnd
(braket
l_int|0
)braket
op_assign
id|LOG_SENSE
suffix:semicolon
id|cmnd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|2
)braket
op_assign
l_int|0x32
op_plus
(paren
l_int|3
op_lshift
l_int|6
)paren
suffix:semicolon
id|cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|cmnd
(braket
l_int|7
)braket
op_assign
l_int|0x01
suffix:semicolon
id|cmnd
(braket
l_int|8
)braket
op_assign
l_int|0x44
suffix:semicolon
id|cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|scmd.cmd_len
op_assign
l_int|10
suffix:semicolon
multiline_comment|/*&n;&t;     * Do the command and wait for it to finish.&n;&t;     */
(brace
r_struct
id|semaphore
id|sem
op_assign
id|MUTEX_LOCKED
suffix:semicolon
id|scmd.request.rq_status
op_assign
id|RQ_SCSI_BUSY
suffix:semicolon
id|scmd.request.sem
op_assign
op_amp
id|sem
suffix:semicolon
id|scsi_do_cmd
(paren
op_amp
id|scmd
comma
id|cmnd
comma
id|buff2
comma
l_int|0x144
comma
id|eata_scsi_done
comma
l_int|1
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
id|swap_statistics
c_func
(paren
id|buff2
)paren
suffix:semicolon
id|rhcs
op_assign
(paren
id|hst_cmd_stat
op_star
)paren
(paren
id|buff2
op_plus
l_int|0x2c
)paren
suffix:semicolon
id|whcs
op_assign
(paren
id|hst_cmd_stat
op_star
)paren
(paren
id|buff2
op_plus
l_int|0x8c
)paren
suffix:semicolon
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
op_le
l_int|11
suffix:semicolon
id|x
op_increment
)paren
(brace
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads
(braket
id|x
)braket
op_add_assign
id|rhcs-&gt;sizes
(braket
id|x
)braket
suffix:semicolon
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes
(braket
id|x
)braket
op_add_assign
id|whcs-&gt;sizes
(braket
id|x
)braket
suffix:semicolon
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads
(braket
l_int|12
)braket
op_add_assign
id|rhcs-&gt;sizes
(braket
id|x
)braket
suffix:semicolon
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes
(braket
l_int|12
)braket
op_add_assign
id|whcs-&gt;sizes
(braket
id|x
)braket
suffix:semicolon
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Host&lt;-&gt;Disk command statistics:&bslash;n&quot;
l_string|&quot;         Reads:&t;     Writes:&bslash;n&quot;
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
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
op_le
l_int|10
suffix:semicolon
id|x
op_increment
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%5dk:%12u %12u&bslash;n&quot;
comma
l_int|1
op_lshift
id|x
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads
(braket
id|x
)braket
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes
(braket
id|x
)braket
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
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&gt;1024k:%12u %12u&bslash;n&quot;
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads
(braket
l_int|11
)braket
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes
(braket
l_int|11
)braket
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Sum   :%12u %12u&bslash;n&quot;
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads
(braket
l_int|12
)braket
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes
(braket
l_int|12
)braket
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
)brace
)brace
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
r_if
c_cond
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|do_latency
op_eq
id|TRUE
)paren
(brace
r_int
id|factor
op_assign
l_int|1024
op_div
id|HZ
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
l_string|&quot;Host Latency Command Statistics:&bslash;n&quot;
l_string|&quot;Current timer resolution: %2dms&bslash;n&quot;
l_string|&quot;         Reads:&t;      Min:(ms)     Max:(ms)     Ave:(ms)&bslash;n&quot;
comma
id|factor
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
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
op_le
l_int|10
suffix:semicolon
id|x
op_increment
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%5dk:%12u %12u %12u %12u&bslash;n&quot;
comma
l_int|1
op_lshift
id|x
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
comma
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|1
)braket
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|1
)braket
op_star
id|factor
)paren
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|2
)braket
op_star
id|factor
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|3
)braket
op_star
id|factor
op_div
(paren
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
)paren
ques
c_cond
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
suffix:colon
l_int|1
)paren
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
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&gt;1024k:%12u %12u %12u %12u&bslash;n&quot;
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
l_int|11
)braket
(braket
l_int|0
)braket
comma
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
l_int|11
)braket
(braket
l_int|1
)braket
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
l_int|11
)braket
(braket
l_int|1
)braket
op_star
id|factor
)paren
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
l_int|11
)braket
(braket
l_int|2
)braket
op_star
id|factor
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
l_int|11
)braket
(braket
l_int|3
)braket
op_star
id|factor
op_div
(paren
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
)paren
ques
c_cond
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|reads_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
suffix:colon
l_int|1
)paren
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;         Writes:      Min:(ms)     Max:(ms)     Ave:(ms)&bslash;n&quot;
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
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
op_le
l_int|10
suffix:semicolon
id|x
op_increment
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%5dk:%12u %12u %12u %12u&bslash;n&quot;
comma
l_int|1
op_lshift
id|x
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
comma
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|1
)braket
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|1
)braket
op_star
id|factor
)paren
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|2
)braket
op_star
id|factor
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|3
)braket
op_star
id|factor
op_div
(paren
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
)paren
ques
c_cond
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
suffix:colon
l_int|1
)paren
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
)brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&gt;1024k:%12u %12u %12u %12u&bslash;n&quot;
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
l_int|11
)braket
(braket
l_int|0
)braket
comma
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
l_int|11
)braket
(braket
l_int|1
)braket
op_eq
l_int|0xffffffff
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|1
)braket
op_star
id|factor
)paren
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
l_int|11
)braket
(braket
l_int|2
)braket
op_star
id|factor
comma
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
l_int|11
)braket
(braket
l_int|3
)braket
op_star
id|factor
op_div
(paren
(paren
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
)paren
ques
c_cond
id|SD
c_func
(paren
id|HBA_ptr
)paren
op_member_access_from_pointer
id|writes_lat
(braket
id|x
)braket
(braket
l_int|0
)braket
suffix:colon
l_int|1
)paren
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
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;Attached devices: %s&bslash;n&quot;
comma
(paren
id|HBA_ptr-&gt;host_queue
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;none&quot;
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
r_for
c_loop
(paren
id|scd
op_assign
id|HBA_ptr-&gt;host_queue
suffix:semicolon
id|scd
suffix:semicolon
id|scd
op_assign
id|scd-&gt;next
)paren
(brace
id|proc_print_scsidevice
c_func
(paren
id|scd
comma
id|buffer
comma
op_amp
id|size
comma
id|len
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
id|stop_output
suffix:colon
id|DBG
c_func
(paren
id|DBG_PROC
comma
id|printk
c_func
(paren
l_string|&quot;2pos: %ld offset: %ld len: %d&bslash;n&quot;
comma
id|pos
comma
id|offset
comma
id|len
)paren
)paren
suffix:semicolon
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
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
multiline_comment|/* Ending slop */
id|DBG
c_func
(paren
id|DBG_PROC
comma
id|printk
c_func
(paren
l_string|&quot;3pos: %ld offset: %ld len: %d&bslash;n&quot;
comma
id|pos
comma
id|offset
comma
id|len
)paren
)paren
suffix:semicolon
r_return
(paren
id|len
)paren
suffix:semicolon
macro_line|#else /* CONFIG_PROC_FS */
r_return
l_int|0
suffix:semicolon
macro_line|#endif        
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * tab-width: 8&n; * End:&n; */
eof
