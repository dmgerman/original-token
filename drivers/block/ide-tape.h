multiline_comment|/*&n; * linux/drivers/block/ide-tape.h&t;Version 1.5 - ALPHA&t;Apr  12, 1996&n; *&n; * Copyright (C) 1995, 1996 Gadi Oxman &lt;gadio@netvision.net.il&gt;&n; */
multiline_comment|/*&n; * Include file for the IDE ATAPI streaming tape driver.&n; *&n; * This file contains various ide-tape related structures and function&n; * prototypes which are already used in ide.h.&n; *&n; * The various compile time options are described below.&n; */
macro_line|#ifndef IDETAPE_H
DECL|macro|IDETAPE_H
mdefine_line|#define IDETAPE_H 
multiline_comment|/**************************** Tunable parameters *****************************/
multiline_comment|/*&n; *&t;This is probably the most important configuration option.&n; *&n; *&t;Pipelined operation mode has the potential to maximize the&n; *&t;performance of the driver and thus to saturate the throughput&n; *&t;to the maximum value supported by the tape.&n; *&n; *&t;In pipelined mode we are servicing requests without blocking the&n; *&t;user backup program. For example, on a write request, we will add it&n; *&t;to the pipeline and return without waiting for it to complete. The&n; *&t;user program will then have enough time to prepare the next blocks&n; *&t;while the tape is still busy working on the previous requests.&n; *&n; *&t;Pipelined operation mode is enabled by default, but since it has a&n; *&t;few downfalls as well, you may wish to disable it.&n; *&t;Further explanation of pipelined mode is available in ide-tape.c .&n; */
DECL|macro|IDETAPE_PIPELINE
mdefine_line|#define&t;IDETAPE_PIPELINE&t;1
multiline_comment|/*&n; *&t;Pipelined mode parameters.&n; *&n; *&t;We try to use the minimum number of stages which is enough to&n; *&t;keep the tape constantly streaming. To accomplish that, we implement&n; *&t;a feedback loop around the maximum number of stages:&n; *&n; *&t;We start from MIN maximum stages (we will not even use MIN stages&n; *      if we don&squot;t need them), increment it by RATE*(MAX-MIN)&n; *&t;whenever we sense that the pipeline is empty, until we reach&n; *&t;the optimum value or until we reach MAX.&n; */
DECL|macro|IDETAPE_MIN_PIPELINE_STAGES
mdefine_line|#define&t;IDETAPE_MIN_PIPELINE_STAGES&t;&t;100
DECL|macro|IDETAPE_MAX_PIPELINE_STAGES
mdefine_line|#define&t;IDETAPE_MAX_PIPELINE_STAGES&t;&t;200
DECL|macro|IDETAPE_INCREASE_STAGES_RATE
mdefine_line|#define&t;IDETAPE_INCREASE_STAGES_RATE&t;&t;20
multiline_comment|/*&n; *&t;Assuming the tape shares an interface with another device, the default&n; *&t;behavior is to service our pending pipeline requests as soon as&n; *&t;possible, but to gracefully postpone them in favor of the other device&n; *&t;when the tape is busy. This has the potential to maximize our&n; *&t;throughput and in the same time, to make efficient use of the IDE bus.&n; *&n; *&t;Note that when we transfer data to / from the tape, we co-operate with&n; *&t;the relatively fast tape buffers and the tape will perform the&n; *&t;actual media access in the background, without blocking the IDE&n; *&t;bus. This means that as long as the maximum IDE bus throughput is much&n; *&t;higher than the sum of our maximum throughput and the maximum&n; *&t;throughput of the other device, we should probably leave the default&n; *&t;behavior.&n; *&n; *&t;However, if it is still desired to give the other device a share even&n; *&t;in our own (small) bus bandwidth, you can set IDETAPE_LOW_TAPE_PRIORITY&n; *&t;to 1. This will let the other device finish *all* its pending requests&n; *&t;before we even check if we can service our next pending request.&n; */
DECL|macro|IDETAPE_LOW_TAPE_PRIORITY
mdefine_line|#define IDETAPE_LOW_TAPE_PRIORITY&t;&t;0
multiline_comment|/*&n; *&t;It seems that dynamically allocating buffers of about 32KB&n; *&t;each is doomed to fail, unless we are in or very near the&n; *&t;initialization stage. Take care when changing this value, as it&n; *&t;is now optimized with the design of kmalloc, so that we will not&n; *&t;allocate parts of a page. Setting the size to 512 bytes, for example,&n; *&t;would cause kmalloc to allocate for us 1024 bytes, and to&n; *&t;unnecessarily waste double amount of memory.&n; */
macro_line|#if PAGE_SIZE == 4096
DECL|macro|IDETAPE_ALLOCATION_BLOCK
mdefine_line|#define&t;IDETAPE_ALLOCATION_BLOCK&t;&t;500
macro_line|#elif PAGE_SIZE == 8192
DECL|macro|IDETAPE_ALLOCATION_BLOCK
mdefine_line|#define&t;IDETAPE_ALLOCATION_BLOCK&t;&t;496
macro_line|#else /* ??? Not defined by linux/mm/kmalloc.c */
DECL|macro|IDETAPE_ALLOCATION_BLOCK
mdefine_line|#define IDETAPE_ALLOCATION_BLOCK&t;&t;512
macro_line|#endif
multiline_comment|/*&n; *&t;ide-tape currently uses two continuous buffers, each of the size of&n; *&t;one stage. By default, those buffers are allocated at initialization&n; *&t;time and never released, since dynamic allocation of pages bigger&n; *&t;than PAGE_SIZE may fail as memory becomes fragmented.&n; *&n; *&t;This results in about 100 KB memory usage when the tape is idle.&n; *&t;Setting IDETAPE_MINIMIZE_IDLE_MEMORY_USAGE to 1 will let ide-tape&n; *&t;to dynamically allocate those buffers, resulting in about 20 KB idle&n; *&t;memory usage.&n; */
DECL|macro|IDETAPE_MINIMIZE_IDLE_MEMORY_USAGE
mdefine_line|#define&t;IDETAPE_MINIMIZE_IDLE_MEMORY_USAGE&t;0
multiline_comment|/*&n; *&t;The following are used to debug the driver:&n; *&n; *&t;Setting IDETAPE_DEBUG_LOG to 1 will log driver flow control.&n; *&t;Setting IDETAPE_DEBUG_BUGS to 1 will enable self-sanity checks in&n; *&t;some places.&n; *&n; *&t;Setting them to 0 will restore normal operation mode:&n; *&n; *&t;&t;1.&t;Disable logging normal successful operations.&n; *&t;&t;2.&t;Disable self-sanity checks.&n; *&t;&t;3.&t;Errors will still be logged, of course.&n; *&n; *&t;All the #if DEBUG code will be removed some day, when the driver&n; *&t;is verified to be stable enough. This will make it much more&n; *&t;esthetic.&n; */
DECL|macro|IDETAPE_DEBUG_LOG
mdefine_line|#define&t;IDETAPE_DEBUG_LOG&t;&t;0
DECL|macro|IDETAPE_DEBUG_BUGS
mdefine_line|#define&t;IDETAPE_DEBUG_BUGS&t;&t;1
multiline_comment|/*&n; *&t;After each failed packet command we issue a request sense command&n; *&t;and retry the packet command IDETAPE_MAX_PC_RETRIES times.&n; *&n; *&t;Setting IDETAPE_MAX_PC_RETRIES to 0 will disable retries.&n; */
DECL|macro|IDETAPE_MAX_PC_RETRIES
mdefine_line|#define&t;IDETAPE_MAX_PC_RETRIES&t;3
multiline_comment|/*&n; *&t;With each packet command, we allocate a buffer of&n; *&t;IDETAPE_TEMP_BUFFER_SIZE bytes. This is used for several packet&n; *&t;commands (Not for READ/WRITE commands).&n; *&n; *&t;The default below is too high - We should be using around 100 bytes&n; *&t;typically, but I didn&squot;t check all the cases, so I rather be on the&n; *&t;safe size.&n; */
DECL|macro|IDETAPE_TEMP_BUFFER_SIZE
mdefine_line|#define&t;IDETAPE_TEMP_BUFFER_SIZE 256
multiline_comment|/*&n; *&t;In various places in the driver, we need to allocate storage&n; *&t;for packet commands and requests, which will remain valid while&n; *&t;we leave the driver to wait for an interrupt or a timeout event.&n; *&n; *&t;In the corresponding ide_drive_t structure, we pre-allocate storage&n; *&t;for IDETAPE_PC_STACK packet commands and requests. This storage is&n; *&t;used as a circular array - Each time we reach the last entry, we&n; *&t;warp around to the first.&n; *&n; *&t;It is crucial that we have enough entries for the maximum number&n; *&t;of packet commands / sub-requests which we need to allocate during&n; *&t;the handling of a specific request.&n; *&n; *&t;Follows a worse case calculation of the required storage, with a&n; *&t;large safety margin.&n; */
DECL|macro|IDETAPE_PC_STACK
mdefine_line|#define&t;IDETAPE_PC_STACK&t;20+IDETAPE_MAX_PC_RETRIES
multiline_comment|/*&n; *&t;DSC polling parameters.&n; *&n; *&t;Polling for DSC (a single bit in the status register) is a very&n; *&t;important function in ide-tape. There are two cases in which we&n; *&t;poll for DSC:&n; *&n; *&t;1.&t;Before a read/write packet command, to ensure that we&n; *&t;&t;can transfer data from/to the tape&squot;s data buffers, without&n; *&t;&t;causing an actual media access. In case the tape is not&n; *&t;&t;ready yet, we take out our request from the device&n; *&t;&t;request queue, so that ide.c will service requests from&n; *&t;&t;the other device on the same interface meanwhile.&n; *&n; *&t;&t;We can now automatically select the &quot;best&quot; polling frequency.&n; *&t;&t;Have a look at IDETAPE_ANTICIPATE_READ_WRITE_DSC below.&n; *&n; *&t;&t;In case you don&squot;t want to use the automatic selection,&n; *&t;&t;choose it to be relatively fast. The default fallback&n; *&t;&t;frequency is 1/50 msec.&n; *&n; *&t;2.&t;After the successful initialization of a &quot;media access&n; *&t;&t;packet command&quot;, which is a command which can take a long&n; *&t;&t;time to complete (it can be several seconds or even an hour).&n; *&n; *&t;&t;Again, we postpone our request in the middle to free the bus&n; *&t;&t;for the other device. The polling frequency here should be&n; *&t;&t;lower than the read/write frequency since those media access&n; *&t;&t;commands are slow. We start from a &quot;fast&quot; frequency -&n; *&t;&t;IDETAPE_DSC_FAST_MEDIA_ACCESS_FREQUENCY (one second), and&n; *&t;&t;if we don&squot;t receive DSC after IDETAPE_FAST_SLOW_THRESHOLD&n; *&t;&t;(5 minutes), we switch it to a lower frequency -&n; *&t;&t;IDETAPE_DSC_SLOW_MEDIA_ACCESS_FREQUENCY (1 minute).&n; *&t;&t;&n; *&t;We also set a timeout for the timer, in case something goes wrong.&n; *&t;The timeout should be longer then the maximum execution time of a&n; *&t;tape operation. I still have to measure exactly how much time does&n; *&t;it take to space over a far filemark, etc. It seemed that 15 minutes&n; *&t;was way too low, so I am meanwhile setting it to a rather large&n; *&t;timeout - 2 Hours ...&n; *&n; */
multiline_comment|/*&n; *&t;Setting IDETAPE_ANTICIPATE_READ_WRITE_DSC to 1 will allow ide-tape&n; *&t;to cleverly select the lowest possible frequency which will&n; *&t;not affect performance, based on the tape parameters and our operation&n; *&t;mode. This has potential to dramatically decrease our polling load&n; *&t;on Linux.&n; *&n; *&t;However, for the cases in which our calculation fails, setting&n; *&t;the following option to 0 will force the use of the &quot;fallback&quot;&n; *&t;polling period defined below (defaults to 50 msec).&n; *&n; *&t;In any case, the frequency will be between the &quot;lowest&quot; value&n; *&t;to the &quot;fallback&quot; value, to ensure that our selected &quot;best&quot; frequency&n; *&t;is reasonable.&n; */
DECL|macro|IDETAPE_ANTICIPATE_READ_WRITE_DSC
mdefine_line|#define IDETAPE_ANTICIPATE_READ_WRITE_DSC&t;1
multiline_comment|/*&n; *&t;DSC timings.&n; */
DECL|macro|IDETAPE_DSC_READ_WRITE_FALLBACK_FREQUENCY
mdefine_line|#define&t;IDETAPE_DSC_READ_WRITE_FALLBACK_FREQUENCY   5*HZ/100&t;/* 50 msec */
DECL|macro|IDETAPE_DSC_READ_WRITE_LOWEST_FREQUENCY
mdefine_line|#define IDETAPE_DSC_READ_WRITE_LOWEST_FREQUENCY&t;30*HZ/100&t;/* 300 msec */
DECL|macro|IDETAPE_DSC_FAST_MEDIA_ACCESS_FREQUENCY
mdefine_line|#define&t;IDETAPE_DSC_FAST_MEDIA_ACCESS_FREQUENCY&t;1*HZ&t;&t;/* 1 second */
DECL|macro|IDETAPE_FAST_SLOW_THRESHOLD
mdefine_line|#define&t;IDETAPE_FAST_SLOW_THRESHOLD&t;&t;5*60*HZ&t;&t;/* 5 minutes */
DECL|macro|IDETAPE_DSC_SLOW_MEDIA_ACCESS_FREQUENCY
mdefine_line|#define IDETAPE_DSC_SLOW_MEDIA_ACCESS_FREQUENCY&t;60*HZ&t;&t;/* 1 minute */
DECL|macro|IDETAPE_DSC_TIMEOUT
mdefine_line|#define&t;IDETAPE_DSC_TIMEOUT&t;&t;&t;2*60*60*HZ&t;/* 2 hours */
multiline_comment|/*************************** End of tunable parameters ***********************/
multiline_comment|/*&n; *&t;Definitions which are already needed in ide.h&n; */
multiline_comment|/*&n; *&t;Current character device data transfer direction.&n; */
DECL|enumerator|idetape_direction_none
DECL|enumerator|idetape_direction_read
DECL|enumerator|idetape_direction_write
DECL|typedef|chrdev_direction_t
r_typedef
r_enum
(brace
id|idetape_direction_none
comma
id|idetape_direction_read
comma
id|idetape_direction_write
)brace
id|chrdev_direction_t
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
multiline_comment|/* Error code */
DECL|member|abort
id|byte
m_abort
suffix:semicolon
multiline_comment|/* Set when an error is considered normal - We won&squot;t retry */
DECL|member|wait_for_dsc
id|byte
id|wait_for_dsc
suffix:semicolon
multiline_comment|/* 1 When polling for DSC on a media access command */
DECL|member|dma_recommended
id|byte
id|dma_recommended
suffix:semicolon
multiline_comment|/* 1 when we prefer to use DMA if possible */
DECL|member|dma_in_progress
id|byte
id|dma_in_progress
suffix:semicolon
multiline_comment|/* 1 while DMA in progress */
DECL|member|dma_error
id|byte
id|dma_error
suffix:semicolon
multiline_comment|/* 1 when encountered problem during DMA */
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
multiline_comment|/*&n; *&t;A pipeline stage contains several small buffers of type&n; *&t;idetape_buffer_head_t. This is necessary since dynamical allocation&n; *&t;of large (32 KB or so) continuous memory blocks will usually fail.&n; */
DECL|struct|idetape_buffer_head_s
r_typedef
r_struct
id|idetape_buffer_head_s
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to data (512 bytes by default) */
DECL|member|next
r_struct
id|idetape_buffer_head_s
op_star
id|next
suffix:semicolon
DECL|typedef|idetape_buffer_head_t
)brace
id|idetape_buffer_head_t
suffix:semicolon
multiline_comment|/*&n; *&t;A pipeline stage.&n; *&n; *&t;In a pipeline stage we have a request, pointer to a list of small&n; *&t;buffers, and pointers to the near stages.&n; */
DECL|struct|idetape_pipeline_stage_s
r_typedef
r_struct
id|idetape_pipeline_stage_s
(brace
DECL|member|rq
r_struct
id|request
id|rq
suffix:semicolon
multiline_comment|/* The corresponding request */
DECL|member|bh
id|idetape_buffer_head_t
op_star
id|bh
suffix:semicolon
multiline_comment|/* The data buffers */
DECL|member|next
DECL|member|prev
r_struct
id|idetape_pipeline_stage_s
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
multiline_comment|/* Pointers to the next and previous stages */
DECL|typedef|idetape_pipeline_stage_t
)brace
id|idetape_pipeline_stage_t
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
multiline_comment|/* &n;&t; *&t;The Linux ide driver basically traverses the request lists&n;&t; *&t;of the ide block devices, finds the next request, completes&n;&t; *&t;it, and passes to the next one. This is done in ide_do_request.&n;&t; *&n;&t; *&t;In this regard, ide-tape.c is fully compatible with the rest of&n;&t; *&t;the ide driver - From the point of view of ide.c, we are just&n;&t; *&t;another ide block device which receives requests and completes&n;&t; *&t;them.&n;&t; *&n;&t; *&t;However, our requests don&squot;t originate in the buffer cache but&n;&t; *&t;rather in ide-tape.c itself. Here we provide safe storage for&n;&t; *&t;such requests.&n;&t; */
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
multiline_comment|/*&n;&t; *&t;While polling for DSC we use postponed_rq to postpone the&n;&t; *&t;current request so that ide.c will be able to service&n;&t; *&t;pending requests on the other device. Note that at most&n;&t; *&t;we will have only one DSC (usually data transfer) request&n;&t; *&t;in the device request queue. Additional request can be&n;&t; *&t;queued in our internal pipeline, but they will be visible&n;&t; *&t;to ide.c only one at a time.&n;&t; */
DECL|member|postponed_rq
r_struct
id|request
op_star
id|postponed_rq
suffix:semicolon
multiline_comment|/*&n;&t; *&t;DSC polling variables.&n;&t; */
DECL|member|dsc_count
id|byte
id|dsc_count
suffix:semicolon
multiline_comment|/* We received DSC dsc_count times in a row */
DECL|member|dsc_polling_start
r_int
r_int
id|dsc_polling_start
suffix:semicolon
multiline_comment|/* The time in which we started polling for DSC */
DECL|member|dsc_timer
r_struct
id|timer_list
id|dsc_timer
suffix:semicolon
multiline_comment|/* Timer used to poll for dsc */
multiline_comment|/*&n;&t; *&t;We can now be much more clever in our selection of the&n;&t; *&t;read/write polling frequency. This is used along with&n;&t; *&t;the compile time option IDETAPE_ANTICIPATE_DSC.&n;&t; */
DECL|member|best_dsc_rw_frequency
r_int
r_int
id|best_dsc_rw_frequency
suffix:semicolon
multiline_comment|/* Read/Write dsc polling frequency */
DECL|member|dsc_polling_frequency
r_int
r_int
id|dsc_polling_frequency
suffix:semicolon
multiline_comment|/* The current polling frequency */
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
multiline_comment|/* Set when we receive DSC */
DECL|member|request_status
id|byte
id|request_status
suffix:semicolon
DECL|member|last_status
id|byte
id|last_status
suffix:semicolon
multiline_comment|/* Contents of the tape status register */
multiline_comment|/* before the current request (saved for us */
multiline_comment|/* by ide.c) */
multiline_comment|/*&n;&t; *&t;After an ATAPI software reset, the status register will be&n;&t; *&t;locked, and thus we need to ignore it when checking DSC for&n;&t; *&t;the first time.&n;&t; */
DECL|member|reset_issued
id|byte
id|reset_issued
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
DECL|member|chrdev_direction
id|chrdev_direction_t
id|chrdev_direction
suffix:semicolon
multiline_comment|/* Current character device data transfer direction */
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
multiline_comment|/* Usually 512 or 1024 bytes */
DECL|member|capabilities
id|idetape_capabilities_page_t
id|capabilities
suffix:semicolon
multiline_comment|/* Copy of the tape&squot;s Capabilities and Mechanical Page */
multiline_comment|/*&n;&t; *&t;Active data transfer request parameters.&n;&t; *&n;&t; *&t;At most, there is only one ide-tape originated data transfer&n;&t; *&t;request in the device request queue. This allows ide.c to&n;&t; *&t;easily service requests from the other device when we&n;&t; *&t;postpone our active request. In the pipelined operation&n;&t; *&t;mode, we use our internal pipeline structure to hold&n;&t; *&t;more data requests.&n;&t; *&n;&t; *&t;The data buffer size is chosen based on the tape&squot;s&n;&t; *&t;recommendation.&n;&t; */
DECL|member|active_data_request
r_struct
id|request
op_star
id|active_data_request
suffix:semicolon
multiline_comment|/* Pointer to the request which is waiting in the device request queue */
DECL|member|data_buffer
r_char
op_star
id|data_buffer
suffix:semicolon
multiline_comment|/* The corresponding data buffer (for read/write requests) */
DECL|member|data_buffer_size
r_int
id|data_buffer_size
suffix:semicolon
multiline_comment|/* Data buffer size (chosen based on the tape&squot;s recommendation */
DECL|member|merge_buffer
r_char
op_star
id|merge_buffer
suffix:semicolon
multiline_comment|/* Temporary buffer for user &lt;-&gt; kernel space data transfer */
DECL|member|merge_buffer_offset
r_int
id|merge_buffer_offset
suffix:semicolon
DECL|member|merge_buffer_size
r_int
id|merge_buffer_size
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Pipeline parameters.&n;&t; *&n;&t; *&t;To accomplish non-pipelined mode, we simply set the following&n;&t; *&t;variables to zero (or NULL, where appropriate).&n;&t; */
DECL|member|current_number_of_stages
r_int
id|current_number_of_stages
suffix:semicolon
multiline_comment|/* Number of currently used stages */
DECL|member|max_number_of_stages
r_int
id|max_number_of_stages
suffix:semicolon
multiline_comment|/* We will not allocate more than this number of stages */
DECL|member|first_stage
id|idetape_pipeline_stage_t
op_star
id|first_stage
suffix:semicolon
multiline_comment|/* The first stage which will be removed from the pipeline */
DECL|member|active_stage
id|idetape_pipeline_stage_t
op_star
id|active_stage
suffix:semicolon
multiline_comment|/* The currently active stage */
DECL|member|next_stage
id|idetape_pipeline_stage_t
op_star
id|next_stage
suffix:semicolon
multiline_comment|/* Will be serviced after the currently active request */
DECL|member|last_stage
id|idetape_pipeline_stage_t
op_star
id|last_stage
suffix:semicolon
multiline_comment|/* New requests will be added to the pipeline here */
DECL|member|error_in_pipeline_stage
r_int
id|error_in_pipeline_stage
suffix:semicolon
multiline_comment|/* Set when an error was detected in one of the pipeline stages */
DECL|typedef|idetape_tape_t
)brace
id|idetape_tape_t
suffix:semicolon
multiline_comment|/*&n; *&t;The following is used to have a quick look at the tape&squot;s status&n; *&t;register between requests of the other device.&n; */
DECL|macro|POLL_HWIF_TAPE_DRIVE
mdefine_line|#define POLL_HWIF_TAPE_DRIVE&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (hwif-&gt;tape_drive != NULL) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (hwif-&gt;tape_drive-&gt;tape.request_status) {&t;&t;&t;&bslash;&n;&t;&t;&t;SELECT_DRIVE(hwif,hwif-&gt;tape_drive);&t;&t;&t;&bslash;&n;&t;&t;&t;hwif-&gt;tape_drive-&gt;tape.last_status=GET_STAT();&t;&t;&bslash;&n;&t;&t;&t;hwif-&gt;tape_drive-&gt;tape.request_status=0;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#endif /* IDETAPE_H */
eof
