multiline_comment|/*&n; *&t;hosts.h Copyright (C) 1992 Drew Eckhardt &n; *&t;mid to low-level SCSI driver interface header by&t;&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@tantalus.nrl.navy.mil to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; * &n; *&t;Further modified by Eric Youngdale to support multiple host adapters&n; *&t;of the same type.&n; */
macro_line|#ifndef _HOSTS_H
DECL|macro|_HOSTS_H
mdefine_line|#define _HOSTS_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/hosts.h,v 1.3 1993/09/24 12:21:00 drew Exp drew $&n;*/
multiline_comment|/* It is senseless to set SG_ALL any higher than this - the performance&n;   does not get any better, and it wastes memory */
DECL|macro|SG_NONE
mdefine_line|#define SG_NONE 0
DECL|macro|SG_ALL
mdefine_line|#define SG_ALL 0xff
DECL|macro|DISABLE_CLUSTERING
mdefine_line|#define DISABLE_CLUSTERING 0
DECL|macro|ENABLE_CLUSTERING
mdefine_line|#define ENABLE_CLUSTERING 1
multiline_comment|/* The various choices mean:&n;   NONE: Self evident.  Host adapter is not capable of scatter-gather.&n;   ALL:  Means that the host adapter module can do scatter-gather,&n;         and that there is no limit to the size of the table to which&n;&t; we scatter/gather data.&n;  Anything else:  Indicates the maximum number of chains that can be&n;        used in one scatter-gather request.&n;*/
multiline_comment|/*&n;&t;The Scsi_Host_Template type has all that is needed to interface with a SCSI&n;&t;host in a device independent matter.  There is one entry for each different&n;&t;type of host adapter that is supported on the system.&n;*/
DECL|typedef|Disk
r_typedef
r_struct
id|scsi_disk
id|Disk
suffix:semicolon
DECL|struct|SHT
r_typedef
r_struct
id|SHT
(brace
multiline_comment|/* Used with loadable modules so we can construct a linked list. */
DECL|member|next
r_struct
id|SHT
op_star
id|next
suffix:semicolon
multiline_comment|/* Used with loadable modules so that we know when it is safe to unload */
DECL|member|usage_count
r_int
op_star
id|usage_count
suffix:semicolon
multiline_comment|/*&n;&t;&t;The name pointer is a pointer to the name of the SCSI&n;&t;&t;device detected.&n;&t;*/
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/*&n;&t;&t;The detect function shall return non zero on detection,&n;&t;&t;indicating the number of host adapters of this particular&n;&t;&t;type were found.  It should also&n;&t;&t;initialize all data necessary for this particular&n;&t;&t;SCSI driver.  It is passed the host number, so this host&n;&t;&t;knows where the first entry is in the scsi_hosts[] array.&n;&n;&t;&t;Note that the detect routine MUST not call any of the mid level&n;&t;&t;functions to queue commands because things are not guaranteed&n;&t;&t;to be set up yet.  The detect routine can send commands to&n;&t;&t;the host adapter as long as the program control will not be&n;&t;&t;passed to scsi.c in the processing of the command.  Note&n;&t;&t;especially that scsi_malloc/scsi_free must not be called.&n;&t;*/
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
multiline_comment|/* Used with loadable modules to unload the host structures.  Note:&n;&t;   there is a default action built into the modules code which may&n;&t;   be sufficient for most host adapters.  Thus you may not have to supply&n;&t;   this at all. */
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;The info function will return whatever useful&n;&t;&t;information the developer sees fit.  If not provided, then&n;&t;&t;the name field will be used instead.&n;&t;*/
DECL|member|info
r_const
r_char
op_star
(paren
op_star
id|info
)paren
(paren
r_struct
id|Scsi_Host
op_star
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
multiline_comment|/*&n;&t;&t;Since the mid level driver handles time outs, etc, we want to &n;&t;&t;be able to abort the current command.  Abort returns 0 if the &n;&t;&t;abortion was successful.  The field SCpnt-&gt;abort reason&n;&t;&t;can be filled in with the appropriate reason why we wanted&n;&t;&t;the abort in the first place, and this will be used&n;&t;&t;in the mid-level code instead of the host_byte().&n;&t;&t;If non-zero, the code passed to it &n;&t;&t;will be used as the return code, otherwise &n;&t;&t;DID_ABORT  should be returned.&n;&n;&t;&t;Note that the scsi driver should &quot;clean up&quot; after itself, &n;&t;&t;resetting the bus, etc.  if necessary. &n;&t;*/
DECL|member|abort
r_int
(paren
op_star
m_abort
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;The reset function will reset the SCSI bus.  Any executing &n;&t;&t;commands should fail with a DID_RESET in the host byte.&n;&t;&t;The Scsi_Cmnd  is passed so that the reset routine can figure&n;&t;&t;out which host adapter should be reset, and also which command&n;&t;&t;within the command block was responsible for the reset in&n;&t;&t;the first place.  Some hosts do not implement a reset function,&n;&t;&t;and these hosts must call scsi_request_sense(SCpnt) to keep&n;&t;&t;the command alive.&n;&t;*/
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
id|Scsi_Cmnd
op_star
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
id|Disk
op_star
comma
r_int
comma
r_int
(braket
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;This determines if we will use a non-interrupt driven&n;&t;&t;or an interrupt driven scheme,  It is set to the maximum number&n;&t;&t;of simultaneous commands a given host adapter will accept.&n;&t;*/
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
multiline_comment|/*&n;&t;&t;In many instances, especially where disconnect / reconnect are &n;&t;&t;supported, our host also has an ID on the SCSI bus.  If this is &n;&t;&t;the case, then it must be reserved.  Please set this_id to -1 if&n; &t;&t;your setup is in single initiator mode, and the host lacks an &n;&t;&t;ID.&n;&t;*/
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
multiline_comment|/*&n;&t;&t;present contains counter indicating how many boards of this&n;&t;&t;type were found when we did the scan.&n;&t;*/
DECL|member|present
r_int
r_char
id|present
suffix:semicolon
multiline_comment|/*&n;&t;  true if this host adapter uses unchecked DMA onto an ISA bus.&n;&t;*/
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;  true if this host adapter can make good use of clustering.&n;&t;  I originally thought that if the tablesize was large that it&n;&t;  was a waste of CPU cycles to prepare a cluster list, but&n;&t;  it works out that the Buslogic is faster if you use a smaller&n;&t;  number of segments (i.e. use clustering).  I guess it is&n;&t;  inefficient.&n;&t;*/
DECL|member|use_clustering
r_int
id|use_clustering
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|Scsi_Host_Template
)brace
id|Scsi_Host_Template
suffix:semicolon
multiline_comment|/*&n;&t;The scsi_hosts array is&t;the array containing the data for all &n;&t;possible &lt;supported&gt; scsi hosts.   This is similar to the&n;&t;Scsi_Host_Template, except that we have one entry for each&n;&t;actual physical host adapter on the system, stored as a linked&n;&t;list.  Note that if there are 2 aha1542 boards, then there will&n;&t;be two Scsi_Host entries, but only 1 Scsi_Host_Template entries.&n;*/
DECL|struct|Scsi_Host
r_struct
id|Scsi_Host
(brace
DECL|member|next
r_struct
id|Scsi_Host
op_star
id|next
suffix:semicolon
DECL|member|extra_bytes
r_int
r_int
id|extra_bytes
suffix:semicolon
DECL|member|host_busy
r_volatile
r_int
r_char
id|host_busy
suffix:semicolon
DECL|member|host_no
r_char
id|host_no
suffix:semicolon
multiline_comment|/* Used for IOCTL_GET_IDLUN */
DECL|member|last_reset
r_int
id|last_reset
suffix:semicolon
DECL|member|host_wait
r_struct
id|wait_queue
op_star
id|host_wait
suffix:semicolon
DECL|member|host_queue
id|Scsi_Cmnd
op_star
id|host_queue
suffix:semicolon
DECL|member|hostt
id|Scsi_Host_Template
op_star
id|hostt
suffix:semicolon
multiline_comment|/* Pointer to a circularly linked list - this indicates the hosts&n;&t;&t;   that should be locked out of performing I/O while we have an active&n;&t;&t;   command on this host. */
DECL|member|block
r_struct
id|Scsi_Host
op_star
id|block
suffix:semicolon
multiline_comment|/* These parameters should be set by the detect routine */
DECL|member|base
r_int
r_char
op_star
id|base
suffix:semicolon
DECL|member|io_port
r_int
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|n_io_port
r_int
r_char
id|n_io_port
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|dma_channel
r_int
r_char
id|dma_channel
suffix:semicolon
multiline_comment|/*&n;&t;&t;  Set these if there are conflicts between memory&n;&t;&t;  in the &lt; 1mb region and regions at 16mb multiples.&n;&t;&t;  The address must be on a page boundary.&n;&t;&t;*/
DECL|member|forbidden_addr
r_int
r_int
id|forbidden_addr
suffix:semicolon
DECL|member|forbidden_size
r_int
r_int
id|forbidden_size
suffix:semicolon
multiline_comment|/*&n;&t;&t;  The rest can be copied from the template, or specifically&n;&t;&t;  initialized, as required.&n;&t;&t;*/
DECL|member|this_id
r_int
id|this_id
suffix:semicolon
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
DECL|member|cmd_per_lun
r_int
id|cmd_per_lun
suffix:semicolon
DECL|member|sg_tablesize
r_int
r_int
r_int
id|sg_tablesize
suffix:semicolon
DECL|member|unchecked_isa_dma
r_int
id|unchecked_isa_dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;   True if this host was loaded as a loadable module&n;&t;&t;*/
DECL|member|loaded_as_module
r_int
id|loaded_as_module
suffix:colon
l_int|1
suffix:semicolon
DECL|member|hostdata
r_int
id|hostdata
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Used for storage of host specific stuff */
)brace
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_hostlist
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
op_star
id|scsi_devicelist
suffix:semicolon
r_extern
id|Scsi_Host_Template
op_star
id|scsi_hosts
suffix:semicolon
multiline_comment|/*&n;&t;scsi_init initializes the scsi hosts.&n;*/
multiline_comment|/* We use these goofy things because the MM is not set up when we init&n;   the scsi subsystem.  By using these functions we can write code that&n;   looks normal.  Also, it makes it possible to use the same code for a&n;   loadable module. */
r_extern
r_void
op_star
id|scsi_init_malloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_extern
r_void
id|scsi_init_free
c_func
(paren
r_char
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
id|scan_scsis
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_extern
r_int
id|next_scsi_host
suffix:semicolon
r_extern
r_int
id|scsi_loadable_module_flag
suffix:semicolon
r_int
r_int
id|scsi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_register
c_func
(paren
id|Scsi_Host_Template
op_star
comma
r_int
id|j
)paren
suffix:semicolon
r_extern
r_void
id|scsi_unregister
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|i
)paren
suffix:semicolon
r_extern
r_int
id|scsicam_bios_param
(paren
id|Disk
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|BLANK_HOST
mdefine_line|#define BLANK_HOST {&quot;&quot;, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
DECL|struct|Scsi_Device_Template
r_struct
id|Scsi_Device_Template
(brace
DECL|member|next
r_struct
id|Scsi_Device_Template
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|tag
r_char
op_star
id|tag
suffix:semicolon
DECL|member|scsi_type
r_int
r_char
id|scsi_type
suffix:semicolon
DECL|member|major
r_int
r_char
id|major
suffix:semicolon
DECL|member|nr_dev
r_int
r_char
id|nr_dev
suffix:semicolon
multiline_comment|/* Number currently attached */
DECL|member|dev_noticed
r_int
r_char
id|dev_noticed
suffix:semicolon
multiline_comment|/* Number of devices detected. */
DECL|member|dev_max
r_int
r_char
id|dev_max
suffix:semicolon
multiline_comment|/* Current size of arrays */
DECL|member|blk
r_int
id|blk
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 if character device */
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if we can attach this device */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Sizes arrays based upon number of devices detected */
DECL|member|finish
r_void
(paren
op_star
id|finish
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Perform initialization after attachment */
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/* Attach devices to arrays */
DECL|member|detach
r_void
(paren
op_star
id|detach
)paren
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
id|sd_template
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
id|st_template
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
id|sr_template
suffix:semicolon
r_extern
r_struct
id|Scsi_Device_Template
id|sg_template
suffix:semicolon
r_int
id|scsi_register_device
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
id|sdpnt
)paren
suffix:semicolon
multiline_comment|/* These are used by loadable modules */
r_extern
r_int
id|scsi_register_module
c_func
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_unregister_module
c_func
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* The different types of modules that we can load and unload */
DECL|macro|MODULE_SCSI_HA
mdefine_line|#define MODULE_SCSI_HA 1
DECL|macro|MODULE_SCSI_CONST
mdefine_line|#define MODULE_SCSI_CONST 2
DECL|macro|MODULE_SCSI_IOCTL
mdefine_line|#define MODULE_SCSI_IOCTL 3
DECL|macro|MODULE_SCSI_DEV
mdefine_line|#define MODULE_SCSI_DEV 4
multiline_comment|/*&n; * This is an ugly hack.  If we expect to be able to load devices at run time, we need&n; * to leave extra room in some of the data structures.  Doing a realloc to enlarge&n; * the structures would be riddled with race conditions, so until a better solution &n; * is discovered, we use this crude approach&n; */
DECL|macro|SD_EXTRA_DEVS
mdefine_line|#define SD_EXTRA_DEVS 2
DECL|macro|ST_EXTRA_DEVS
mdefine_line|#define ST_EXTRA_DEVS 2
DECL|macro|SR_EXTRA_DEVS
mdefine_line|#define SR_EXTRA_DEVS 2
DECL|macro|SG_EXTRA_DEVS
mdefine_line|#define SG_EXTRA_DEVS (SD_EXTRA_DEVS + SR_EXTRA_DEVS + ST_EXTRA_DEVS)
macro_line|#endif
eof
