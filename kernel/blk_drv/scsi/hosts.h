multiline_comment|/*&n; *&t;hosts.h Copyright (C) 1992 Drew Eckhardt &n; *&t;mid to low-level SCSI driver interface header by&t;&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@tantalus.nrl.navy.mil to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _HOSTS_H
DECL|macro|_HOSTS_H
mdefine_line|#define _HOSTS_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/hosts.h,v 1.1 1992/07/24 06:27:38 root Exp root $&n;*/
multiline_comment|/*&n;&t;The Scsi_Host type has all that is needed to interface with a SCSI&n;&t;host in a device independant matter.  &n;*/
DECL|macro|SG_NONE
mdefine_line|#define SG_NONE 0
DECL|macro|SG_ALL
mdefine_line|#define SG_ALL 0xff
multiline_comment|/* The various choices mean:&n;   NONE: Self evident.  Host adapter is not capable of scatter-gather.&n;   ALL:  Means that the host adapter module can do scatter-gather,&n;         and that there is no limit to the size of the table to which&n;&t; we scatter/gather data.&n;  Anything else:  Indicates the maximum number of chains that can be&n;        used in one scatter-gather request.&n;*/
r_typedef
r_struct
(brace
multiline_comment|/*&n;&t;&t;The name pointer is a pointer to the name of the SCSI&n;&t;&t;device detected.&n;&t;*/
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t;&t;The detect function shall return non zero on detection,&n;&t;&t;and initialize all data necessary for this particular&n;&t;&t;SCSI driver.  It is passed the host number, so this host&n;&t;&t;knows where it is in the hosts array&n;&t;*/
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;The info function will return whatever useful&n;&t;&t;information the developer sees fit.              &n;&t;*/
DECL|member|info
r_const
r_char
op_star
(paren
op_star
id|info
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;The command function takes a target, a command (this is a SCSI &n;&t;&t;command formatted as per the SCSI spec, nothing strange), a &n;&t;&t;data buffer pointer, and data buffer length pointer.  The return&n;&t;&t;is a status int, bit fielded as follows : &n;&t;&t;Byte&t;What&n;&t;&t;0&t;SCSI status code&n;&t;&t;1&t;SCSI 1 byte message&n;&t;&t;2 &t;host error return.&n;&t;&t;3&t;mid level error return&n;&t;*/
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;                The QueueCommand function works in a similar manner&n;                to the command function.  It takes an additional parameter,&n;                void (* done)(int host, int code) which is passed the host &n;&t;&t;# and exit result when the command is complete.  &n;&t;&t;Host number is the POSITION IN THE hosts array of THIS&n;&t;&t;host adapter.&n;        */
DECL|member|queuecommand
r_int
(paren
op_star
id|queuecommand
)paren
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;Since the mid level driver handles time outs, etc, we want to &n;&t;&t;be able to abort the current command.  Abort returns 0 if the &n;&t;&t;abortion was successful.  If non-zero, the code passed to it &n;&t;&t;will be used as the return code, otherwise &n;&t;&t;DID_ABORT  should be returned.&n;&n;&t;&t;Note that the scsi driver should &quot;clean up&quot; after itself, &n;&t;&t;resetting the bus, etc.  if necessary. &n;&t;*/
DECL|member|abort
r_int
(paren
op_star
m_abort
)paren
(paren
id|Scsi_Cmnd
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;The reset function will reset the SCSI bus.  Any executing &n;&t;&t;commands should fail with a DID_RESET in the host byte.&n;&t;*/
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;This function is used to select synchronous communications,&n;&t;&t;which will result in a higher data throughput.  Not implemented&n;&t;&t;yet.&n;&t;*/
DECL|member|slave_attach
r_int
(paren
op_star
id|slave_attach
)paren
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;This function determines the bios parameters for a given&n;&t;&t;harddisk.  These tend to be numbers that are made up by&n;&t;&t;the host adapter.  Parameters:&n;&t;&t;size, device number, list (heads, sectors, cylinders)&n;&t;*/
DECL|member|bios_param
r_int
(paren
op_star
id|bios_param
)paren
(paren
r_int
comma
r_int
comma
r_int
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;This determines if we will use a non-interrupt driven&n;&t;&t;or an interrupt driven scheme,  It is set to the maximum number&n;&t;&t;of simulataneous commands a given host adapter will accept.&n;&t;*/
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
multiline_comment|/*&n;&t;&t;In many instances, especially where disconnect / reconnect are &n;&t;&t;supported, our host also has an ID on the SCSI bus.  If this is &n;&t;&t;the case, then it must be reserved.  Please set this_id to -1 if&n; &t;&t;your settup is in single initiator mode, and the host lacks an &n;&t;&t;ID.&n;&t;*/
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
multiline_comment|/*&n;&t;        This determines the degree to which the host adapter is capable&n;&t;&t;of scatter-gather.&n;&t;*/
DECL|member|sg_tablesize
r_int
r_int
r_int
id|sg_tablesize
suffix:semicolon
multiline_comment|/*&n;&t;  True if this host adapter can make good use of linked commands.&n;&t;  This will allow more than one command to be queued to a given&n;&t;  unit on a given host.  Set this to the maximum number of command&n;&t;  blocks to be provided for each device.  Set this to 1 for one&n;&t;  command block per lun, 2 for two, etc.  Do not set this to 0.&n;&t;  You should make sure that the host adapter will do the right thing&n;&t;  before you try setting this above 1.&n;&t; */
DECL|member|cmd_per_lun
r_int
id|cmd_per_lun
suffix:semicolon
multiline_comment|/*&n;&t;&t;present contains a flag as to weather we are present -&n;&t;&t;so we don&squot;t have to call detect multiple times.&n;&t;*/
DECL|member|present
r_int
id|present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;  true if this host adapter uses unchecked DMA onto an ISA bus.&n;&t;*/
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|Scsi_Host
)brace
id|Scsi_Host
suffix:semicolon
multiline_comment|/*&n;&t;The scsi_hosts array is&t;the array containing the data for all &n;&t;possible &lt;supported&gt; scsi hosts.   &n;*/
r_extern
id|Scsi_Host
id|scsi_hosts
(braket
)braket
suffix:semicolon
multiline_comment|/*&n;&t;This is our semaphore array, used by scsi.c, sd.c, st.c.&n;&t;Other routines SHOULD NOT mess with it.  Your driver should NOT mess with it.&n;&t;This is used to protect against contention by disk and tape drivers.&n;*/
r_extern
r_volatile
r_int
r_char
id|host_busy
(braket
)braket
suffix:semicolon
multiline_comment|/*&n;&t;This is the queue of currently pending commands for a given&n;&t;SCSI host.&n;*/
r_extern
id|Scsi_Cmnd
op_star
id|host_queue
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|wait_queue
op_star
id|host_wait
(braket
)braket
suffix:semicolon
multiline_comment|/* For waiting until host available*/
multiline_comment|/*&n;&t;scsi_init initializes the scsi hosts.&n;*/
r_void
id|scsi_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BLANK_HOST
mdefine_line|#define BLANK_HOST {&quot;&quot;, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
macro_line|#endif
eof
