multiline_comment|/*&n; * linux/drivers/block/ide-tape.h&t;Version 1.0 - ALPHA&t;Dec  3, 1995&n; *&n; * Copyright (C) 1995 Gadi Oxman &lt;tgud@tochnapc2.technion.ac.il&gt;&n; */
multiline_comment|/*&n; * Include file for the IDE ATAPI streaming tape driver.&n; *&n; * This file contains various ide-tape related structures and function&n; * prototypes which are already used in ide.h.&n; *&n; * The various compile time options are described below.&n; */
macro_line|#ifndef IDETAPE_H
DECL|macro|IDETAPE_H
mdefine_line|#define IDETAPE_H 
multiline_comment|/**************************** Tunable parameters *****************************/
multiline_comment|/*&n; *&t;Setting IDETAPE_DEBUG to 1 will:&n; *&n; *&t;&t;1.&t;Generally log all driver actions.&n; *&t;&t;2.&t;Enable self-sanity checks in some places.&n; *&n; *&t;Use IDETAPE_DEBUG when encountering a problem with the driver.&n; *&n; *&t;Setting IDETAPE_DEBUG to 0 will restore normal operation mode:&n; *&n; *&t;&t;1.&t;Disable logging normal successful operations.&n; *&t;&t;2.&t;Disable self-sanity checks.&n; *&t;&t;3.&t;Errors will still be logged, of course.&n; */
DECL|macro|IDETAPE_DEBUG
mdefine_line|#define&t;IDETAPE_DEBUG&t;&t;0
multiline_comment|/*&n; *&t;After each failed packet command we issue a request sense command&n; *&t;and retry the packet command IDETAPE_MAX_PC_RETRIES times.&n; *&n; *&t;Setting IDETAPE_MAX_PC_RETRIES to 0 will disable retries.&n; */
DECL|macro|IDETAPE_MAX_PC_RETRIES
mdefine_line|#define&t;IDETAPE_MAX_PC_RETRIES&t;2
multiline_comment|/*&n; *&t;In case the tape is not at the requested block, we re-position the&n; *&t;tape. Repeat the procedure for IDETAPE_LOCATE_RETRIES times before&n; *&t;we give up and abort the request. Note that this should not usually&n; *&t;happen when using only the character device interface.&n; */
DECL|macro|IDETAPE_LOCATE_RETRIES
mdefine_line|#define&t;IDETAPE_LOCATE_RETRIES&t;1
multiline_comment|/*&n; *&t;With each packet command, we allocate a buffer of&n; *&t;IDETAPE_TEMP_BUFFER_SIZE bytes. This is used for several packet&n; *&t;commands (Not for READ/WRITE commands).&n; *&n; *&t;The default below is too high - We should be using around 100 bytes&n; *&t;typically, but I didn&squot;t check all the cases, so I rather be on the&n; *&t;safe size.&n; */
DECL|macro|IDETAPE_TEMP_BUFFER_SIZE
mdefine_line|#define&t;IDETAPE_TEMP_BUFFER_SIZE 256
multiline_comment|/*&n; *&t;In various places in the driver, we need to allocate storage&n; *&t;for packet commands and requests, which will remain valid while&n; *&t;we leave the driver to wait for an interrupt or a timeout event.&n; *&n; *&t;In the corresponding ide_drive_t structure, we pre-allocate storage&n; *&t;for IDETAPE_PC_STACK packet commands and requests. This storage is&n; *&t;used as a circular array - Each time we reach the last entry, we&n; *&t;warp around to the first.&n; *&n; *&t;It is crucial that we have enough entries for the maximum number&n; *&t;of packet commands / sub-requests which we need to allocate during&n; *&t;the handling of a specific request.&n; *&n; *&t;Follows a worse case calculation of the required storage, with a&n; *&t;large safety margin. Hopefully. :-)&n; */
DECL|macro|IDETAPE_PC_STACK
mdefine_line|#define&t;IDETAPE_PC_STACK&t;10+&bslash;&n;&t;&t;&t;&t;IDETAPE_MAX_PC_RETRIES+&bslash;&n;&t;&t;&t;&t;3*IDETAPE_LOCATE_RETRIES*IDETAPE_MAX_PC_RETRIES
multiline_comment|/*&n; *&t;Media access packet command (like the LOCATE command) have immediate&n; *&t;status with a delayed (and usually long) execution. The tape doesn&squot;t&n; *&t;issue an interrupt when the command is actually complete (so that the&n; *&t;bus is freed to use the other IDE device on the same interface), so we&n; *&t;must for poll for this event.&n; *&n; *&t;We set a timer with polling frequency of 1/IDETAPE_DSC_MEDIA_ACCESS_FREQUENCY&n; *&t;in this case. We also poll for DSC *before* read/write commands. At&n; *&t;this time the DSC role is changed and instead of signalling command&n; *&t;completion, it will signal buffer availability. Since read/write&n; *&t;commands are fast in comparision to media access commands, the polling&n; *&t;frequency here should be much higher.&n; *&n; *&t;We will insist of reading DSC=1 for IDETAPE_DSC_COUNT times in a row,&n; *&t;to accommodate for random fluctuations in the sampling of DSC.&n; *&t;We will also set IDETAPE_DSC_POLLING_FREQUENCY to a rather low&n; *&t;frequency which besides freeing the CPU and the bus will let&n; *&t;random fluctuations a time to settle down.&n; *&n; *&t;We also set a timeout for the timer, in case something goes wrong.&n; *&t;The timeout should be longer then the maximum execution time of a&n; *&t;tape operation. I still have to measure exactly how much time does&n; *&t;it take to space over a far filemark, etc. It seemed that 15 minutes&n; *&t;was way too low, so I am meanwhile setting it to a rather large&n; *&t;timeout - 2 Hours.&n; *&n; *&t;Once we pass a threshold, the polling frequency will change to&n; *&t;a slow frequency: On relatively fast operations, there is a point&n; *&t;in polling fast, but if we sense that the operation is taking too&n; *&t;much time, we will poll at a lower frequency.&n; */
DECL|macro|IDETAPE_DSC_FAST_MEDIA_ACCESS_FREQUENCY
mdefine_line|#define&t;IDETAPE_DSC_FAST_MEDIA_ACCESS_FREQUENCY&t;1*HZ&t;&t;/* 1 second */
DECL|macro|IDETAPE_FAST_SLOW_THRESHOLD
mdefine_line|#define&t;IDETAPE_FAST_SLOW_THRESHOLD&t;&t;5*60*HZ&t;&t;/* 5 minutes */
DECL|macro|IDETAPE_DSC_SLOW_MEDIA_ACCESS_FREQUENCY
mdefine_line|#define IDETAPE_DSC_SLOW_MEDIA_ACCESS_FREQUENCY&t;60*HZ&t;&t;/* 1 minute */
DECL|macro|IDETAPE_DSC_READ_WRITE_FREQUENCY
mdefine_line|#define&t;IDETAPE_DSC_READ_WRITE_FREQUENCY&t;HZ/20&t;&t;/* 50 msec */
DECL|macro|IDETAPE_DSC_TIMEOUT
mdefine_line|#define&t;IDETAPE_DSC_TIMEOUT&t;&t;&t;2*60*60*HZ&t;/* 2 hours */
DECL|macro|IDETAPE_DSC_COUNT
mdefine_line|#define IDETAPE_DSC_COUNT&t;&t;&t;1&t;&t;/* Assume no DSC fluctuations */
multiline_comment|/*&n; *&t;As explained in many places through the code, we provide both a block&n; *&t;device and a character device interface to the tape. The block device&n; *&t;interface is needed for compatibility with ide.c. The character device&n; *&t;interface is the higher level of the driver, and passes requests&n; *&t;to the lower part of the driver which interfaces with ide.c.&n; *&t;Using the block device interface, we can bypass this high level&n; *&t;of the driver, talking directly with the lower level part.&n; *&n; *&t;It is intended that the character device interface will be used by&n; *&t;the user. To prevent mistakes in this regard, opening of the block&n; *&t;device interface will be refused if ALLOW_OPENING_BLOCK_DEVICE is 0.&n; *&n; *&t;Do not change the following parameter unless you are developing&n; *&t;the driver itself.&n; */
DECL|macro|IDETAPE_ALLOW_OPENING_BLOCK_DEVICE
mdefine_line|#define IDETAPE_ALLOW_OPENING_BLOCK_DEVICE&t;0
multiline_comment|/*************************** End of tunable parameters ***********************/
multiline_comment|/*&n; *&t;Definitions which are already needed in ide.h&n; */
multiline_comment|/*&n; *&t;The following is currently not used.&n; */
DECL|enumerator|no_excess_data
DECL|enumerator|excess_data_read
DECL|enumerator|excess_data_write
DECL|typedef|excess_data_status_t
r_typedef
r_enum
(brace
id|no_excess_data
comma
id|excess_data_read
comma
id|excess_data_write
)brace
id|excess_data_status_t
suffix:semicolon
r_struct
id|ide_drive_s
suffix:semicolon
multiline_comment|/* Forward declaration - Will be defined later in ide.h */
DECL|typedef|idetape_pc_completed_t
r_typedef
r_void
(paren
id|idetape_pc_completed_t
)paren
(paren
r_struct
id|ide_drive_s
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Our view of a packet command.&n; */
DECL|struct|idetape_packet_command_s
r_typedef
r_struct
id|idetape_packet_command_s
(brace
DECL|member|c
id|byte
id|c
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Actual packet bytes */
DECL|member|retries
id|byte
id|retries
suffix:semicolon
multiline_comment|/* On each retry, we increment retries */
DECL|member|error
id|byte
id|error
suffix:semicolon
multiline_comment|/* Set when an error occured */
DECL|member|active
id|byte
id|active
suffix:semicolon
multiline_comment|/* Set when a packet command is in progress */
DECL|member|wait_for_dsc
id|byte
id|wait_for_dsc
suffix:semicolon
multiline_comment|/* 1 When polling for DSC */
DECL|member|dsc_count
id|byte
id|dsc_count
suffix:semicolon
DECL|member|request_transfer
r_int
r_int
id|request_transfer
suffix:semicolon
multiline_comment|/* Bytes to transfer */
DECL|member|actually_transferred
r_int
r_int
id|actually_transferred
suffix:semicolon
multiline_comment|/* Bytes actually transferred */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Size of our data buffer */
DECL|member|buffer
id|byte
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|current_position
id|byte
op_star
id|current_position
suffix:semicolon
multiline_comment|/* Pointer into the above buffer */
DECL|member|writing
id|byte
id|writing
suffix:semicolon
multiline_comment|/* Data direction */
DECL|member|callback
id|idetape_pc_completed_t
op_star
id|callback
suffix:semicolon
multiline_comment|/* Called when this packet command is completed */
DECL|member|temp_buffer
id|byte
id|temp_buffer
(braket
id|IDETAPE_TEMP_BUFFER_SIZE
)braket
suffix:semicolon
multiline_comment|/* Temporary buffer */
DECL|typedef|idetape_packet_command_t
)brace
id|idetape_packet_command_t
suffix:semicolon
multiline_comment|/*&n; *&t;Capabilities and Mechanical Status Page&n; */
r_typedef
r_struct
(brace
DECL|member|page_code
r_int
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page code - Should be 0x2a */
DECL|member|reserved1_67
r_int
id|reserved1_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|page_length
id|byte
id|page_length
suffix:semicolon
multiline_comment|/* Page Length - Should be 0x12 */
DECL|member|reserved2
id|byte
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|byte
id|reserved3
suffix:semicolon
DECL|member|ro
r_int
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read Only Mode */
DECL|member|reserved4_1234
r_int
id|reserved4_1234
suffix:colon
l_int|4
suffix:semicolon
DECL|member|sprev
r_int
id|sprev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SPACE in the reverse direction */
DECL|member|reserved4_67
r_int
id|reserved4_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved5_012
r_int
id|reserved5_012
suffix:colon
l_int|3
suffix:semicolon
DECL|member|efmt
r_int
id|efmt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports ERASE command initiated formatting */
DECL|member|reserved5_4
r_int
id|reserved5_4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|qfa
r_int
id|qfa
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports the QFA two partition formats */
DECL|member|reserved5_67
r_int
id|reserved5_67
suffix:colon
l_int|2
suffix:semicolon
DECL|member|lock
r_int
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports locking the volume */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The volume is locked */
DECL|member|prevent
r_int
id|prevent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device defaults in the prevent state after power up */
DECL|member|eject
r_int
id|eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device can eject the volume */
DECL|member|reserved6_45
r_int
id|reserved6_45
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ecc
r_int
id|ecc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports error correction */
DECL|member|cmprs
r_int
id|cmprs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports data compression */
DECL|member|reserved7_0
r_int
id|reserved7_0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|blk512
r_int
id|blk512
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 512 bytes block size */
DECL|member|blk1024
r_int
id|blk1024
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports 1024 bytes block size */
DECL|member|reserved7_3_6
r_int
id|reserved7_3_6
suffix:colon
l_int|4
suffix:semicolon
DECL|member|slowb
r_int
id|slowb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The device restricts the byte count for PIO */
multiline_comment|/* transfers for slow buffer memory ??? */
DECL|member|max_speed
r_int
r_int
id|max_speed
suffix:semicolon
multiline_comment|/* Maximum speed supported in KBps */
DECL|member|reserved10
id|byte
id|reserved10
suffix:semicolon
DECL|member|reserved11
id|byte
id|reserved11
suffix:semicolon
DECL|member|ctl
r_int
r_int
id|ctl
suffix:semicolon
multiline_comment|/* Continuous Transfer Limit in blocks */
DECL|member|speed
r_int
r_int
id|speed
suffix:semicolon
multiline_comment|/* Current Speed, in KBps */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Buffer Size, in 512 bytes */
DECL|member|reserved18
id|byte
id|reserved18
suffix:semicolon
DECL|member|reserved19
id|byte
id|reserved19
suffix:semicolon
DECL|typedef|idetape_capabilities_page_t
)brace
id|idetape_capabilities_page_t
suffix:semicolon
multiline_comment|/*&n; *&t;Most of our global data which we need to save even as we leave the&n; *&t;driver due to an interrupt or a timer event is stored in a variable&n; *&t;of type tape_info, defined below.&n; *&n; *&t;Additional global variables which provide the link between the&n; *&t;character device interface to this structure are defined in&n; *&t;ide-tape.c&n; */
r_typedef
r_struct
(brace
multiline_comment|/*&n;&t; *&t;Since a typical character device operation requires more&n;&t; *&t;than one packet command, we provide here enough memory&n;&t; *&t;for the maximum of interconnected packet commands.&n;&t; *&t;The packet commands are stored in the circular array pc_stack.&n;&t; *&t;pc_stack_index points to the last used entry, and warps around&n;&t; *&t;to the start when we get to the last array entry.&n;&t; *&n;&t; *&t;pc points to the current processed packet command.&n;&t; *&n;&t; *&t;failed_pc points to the last failed packet command, or contains&n;&t; *&t;NULL if we do not need to retry any packet command. This is&n;&t; *&t;required since an additional packet command is needed before the&n;&t; *&t;retry, to get detailed information on what went wrong.&n;      &t; */
DECL|member|pc
id|idetape_packet_command_t
op_star
id|pc
suffix:semicolon
multiline_comment|/* Current packet command */
DECL|member|failed_pc
id|idetape_packet_command_t
op_star
id|failed_pc
suffix:semicolon
multiline_comment|/* Last failed packet command */
DECL|member|pc_stack
id|idetape_packet_command_t
id|pc_stack
(braket
id|IDETAPE_PC_STACK
)braket
suffix:semicolon
multiline_comment|/* Packet command stack */
DECL|member|pc_stack_index
id|byte
id|pc_stack_index
suffix:semicolon
multiline_comment|/* Next free packet command storage space */
multiline_comment|/* &n;&t; *&t;The Linux ide driver basically traverses the request lists&n;&t; *&t;of the ide block devices, finds the next request, completes&n;&t; *&t;it, and passes to the next one. This is done in ide_do_request.&n;&t; *&n;&t; *&t;In this regard, ide-tape.c is fully compatible with the rest of&n;&t; *&t;the ide driver - From the point of view of ide.c, we are just&n;&t; *&t;another ide block device which receives requests and completes&n;&t; *&t;them.&n;&t; *&n;&t; *&t;However, our requests usually don&squot;t originate in the buffer&n;&t; *&t;cache but rather in ide-tape.c itself. Here we provide safe&n;&t; *&t;storage for such requests.&n;&t; */
DECL|member|rq_stack
r_struct
id|request
id|rq_stack
(braket
id|IDETAPE_PC_STACK
)braket
suffix:semicolon
DECL|member|rq_stack_index
id|byte
id|rq_stack_index
suffix:semicolon
multiline_comment|/* We implement a circular array */
multiline_comment|/*&n;&t; *&t;While polling for DSC we use postponed_rq to postpone the&n;&t; *&t;current request so that ide.c will be able to service&n;&t; *&t;pending requests on the other device.&n;&t; */
DECL|member|postponed_rq
r_struct
id|request
op_star
id|postponed_rq
suffix:semicolon
DECL|member|dsc_count
id|byte
id|dsc_count
suffix:semicolon
DECL|member|dsc_polling_start
r_int
r_int
id|dsc_polling_start
suffix:semicolon
DECL|member|dsc_timer
r_struct
id|timer_list
id|dsc_timer
suffix:semicolon
multiline_comment|/* Timer used to poll for dsc */
DECL|member|dsc_polling_frequency
r_int
r_int
id|dsc_polling_frequency
suffix:semicolon
DECL|member|dsc_timeout
r_int
r_int
id|dsc_timeout
suffix:semicolon
multiline_comment|/* Maximum waiting time */
DECL|member|dsc_received
id|byte
id|dsc_received
suffix:semicolon
multiline_comment|/* Position information */
DECL|member|partition_num
id|byte
id|partition_num
suffix:semicolon
multiline_comment|/* Currently not used */
DECL|member|block_address
r_int
r_int
id|block_address
suffix:semicolon
multiline_comment|/* Current block */
DECL|member|block_address_valid
id|byte
id|block_address_valid
suffix:semicolon
multiline_comment|/* 0 When the tape position is unknown */
multiline_comment|/* (To the tape or to us) */
DECL|member|locate_to
r_int
r_int
id|locate_to
suffix:semicolon
multiline_comment|/* We want to reach this block, as a part */
multiline_comment|/* of handling the current request */
DECL|member|locate_retries
id|byte
id|locate_retries
suffix:semicolon
multiline_comment|/* Each time, increase locate_retries */
DECL|member|last_written_block
r_int
r_int
id|last_written_block
suffix:semicolon
multiline_comment|/* Once writing started, we don&squot;t allow read */
DECL|member|last_written_valid
id|byte
id|last_written_valid
suffix:semicolon
multiline_comment|/* access beyond the last written block */
multiline_comment|/* ??? Should I remove this ? */
multiline_comment|/* Last error information */
DECL|member|sense_key
DECL|member|asc
DECL|member|ascq
id|byte
id|sense_key
comma
id|asc
comma
id|ascq
suffix:semicolon
multiline_comment|/* Character device operation */
DECL|member|last_dt_was_write
r_int
r_char
id|last_dt_was_write
suffix:semicolon
multiline_comment|/* Last character device data transfer was a write */
DECL|member|busy
id|byte
id|busy
suffix:semicolon
multiline_comment|/* Device already opened */
multiline_comment|/* Device information */
DECL|member|tape_block_size
r_int
r_int
id|tape_block_size
suffix:semicolon
DECL|member|capabilities
id|idetape_capabilities_page_t
id|capabilities
suffix:semicolon
multiline_comment|/* Capabilities and Mechanical Page */
multiline_comment|/* Data buffer */
DECL|member|data_buffer
r_char
op_star
id|data_buffer
suffix:semicolon
DECL|typedef|idetape_tape_t
)brace
id|idetape_tape_t
suffix:semicolon
macro_line|#endif /* IDETAPE_H */
eof
