multiline_comment|/*&n; *  scsi.h Copyright (C) 1992 Drew Eckhardt &n; *         Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *  generic SCSI package header file by&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@aib.com to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
multiline_comment|/*&n; * Some of the public constants are being moved to this file.&n; * We include it here so that what came from where is transparent.&n; */
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;linux/random.h&gt;
multiline_comment|/*&n; * Some defs, in case these are not defined elsewhere.&n; */
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE 0
macro_line|#endif
r_extern
r_void
id|scsi_make_blocked_list
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_volatile
r_int
id|in_scan_scsis
suffix:semicolon
r_extern
r_const
r_int
r_char
id|scsi_command_size
(braket
l_int|8
)braket
suffix:semicolon
DECL|macro|COMMAND_SIZE
mdefine_line|#define COMMAND_SIZE(opcode) scsi_command_size[((opcode) &gt;&gt; 5) &amp; 7]
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE       0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;     ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;     ((lun) &amp; 0x07)) 
multiline_comment|/*&n; *  the return of the status word will be in the following format :&n; *  The low byte is the status returned by the SCSI command, &n; *  with vendor specific bits masked.&n; *  &n; *  The next byte is the message which followed the SCSI status.&n; *  This allows a stos to be used, since the Intel is a little&n; *  endian machine.&n; *  &n; *  The final byte is a host return code, which is one of the following.&n; *  &n; *  IE &n; *  lsb     msb&n; *  status  msg host code   &n; *  &n; *  Our errors returned by OUR driver, NOT SCSI message.  Or&squot;d with&n; *  SCSI message passed back to driver &lt;IF any&gt;.&n; */
DECL|macro|DID_OK
mdefine_line|#define DID_OK          0x00 /* NO error                                */
DECL|macro|DID_NO_CONNECT
mdefine_line|#define DID_NO_CONNECT  0x01 /* Couldn&squot;t connect before timeout period  */
DECL|macro|DID_BUS_BUSY
mdefine_line|#define DID_BUS_BUSY    0x02 /* BUS stayed busy through time out period */
DECL|macro|DID_TIME_OUT
mdefine_line|#define DID_TIME_OUT    0x03 /* TIMED OUT for other reason              */
DECL|macro|DID_BAD_TARGET
mdefine_line|#define DID_BAD_TARGET  0x04 /* BAD target.                             */
DECL|macro|DID_ABORT
mdefine_line|#define DID_ABORT       0x05 /* Told to abort for some other reason     */
DECL|macro|DID_PARITY
mdefine_line|#define DID_PARITY      0x06 /* Parity error                            */
DECL|macro|DID_ERROR
mdefine_line|#define DID_ERROR       0x07 /* Internal error                          */
DECL|macro|DID_RESET
mdefine_line|#define DID_RESET       0x08 /* Reset by somebody.                      */
DECL|macro|DID_BAD_INTR
mdefine_line|#define DID_BAD_INTR    0x09 /* Got an interrupt we weren&squot;t expecting.  */ 
DECL|macro|DRIVER_OK
mdefine_line|#define DRIVER_OK       0x00 /* Driver status                           */ 
multiline_comment|/*&n; *  These indicate the error that occurred, and what is available.&n; */
DECL|macro|DRIVER_BUSY
mdefine_line|#define DRIVER_BUSY         0x01
DECL|macro|DRIVER_SOFT
mdefine_line|#define DRIVER_SOFT         0x02
DECL|macro|DRIVER_MEDIA
mdefine_line|#define DRIVER_MEDIA        0x03
DECL|macro|DRIVER_ERROR
mdefine_line|#define DRIVER_ERROR        0x04    
DECL|macro|DRIVER_INVALID
mdefine_line|#define DRIVER_INVALID      0x05
DECL|macro|DRIVER_TIMEOUT
mdefine_line|#define DRIVER_TIMEOUT      0x06
DECL|macro|DRIVER_HARD
mdefine_line|#define DRIVER_HARD         0x07
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;    0x08
DECL|macro|SUGGEST_RETRY
mdefine_line|#define SUGGEST_RETRY       0x10
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT       0x20 
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP       0x30
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE         0x40
DECL|macro|SUGGEST_SENSE
mdefine_line|#define SUGGEST_SENSE       0x80
DECL|macro|SUGGEST_IS_OK
mdefine_line|#define SUGGEST_IS_OK       0xff
DECL|macro|DRIVER_MASK
mdefine_line|#define DRIVER_MASK         0x0f
DECL|macro|SUGGEST_MASK
mdefine_line|#define SUGGEST_MASK        0xf0
DECL|macro|MAX_COMMAND_SIZE
mdefine_line|#define MAX_COMMAND_SIZE    12
multiline_comment|/*&n; *  SCSI command sets&n; */
DECL|macro|SCSI_UNKNOWN
mdefine_line|#define SCSI_UNKNOWN    0
DECL|macro|SCSI_1
mdefine_line|#define SCSI_1          1
DECL|macro|SCSI_1_CCS
mdefine_line|#define SCSI_1_CCS      2
DECL|macro|SCSI_2
mdefine_line|#define SCSI_2          3
multiline_comment|/*&n; *  Every SCSI command starts with a one byte OP-code.&n; *  The next byte&squot;s high three bits are the LUN of the&n; *  device.  Any multi-byte quantities are stored high byte&n; *  first, and may have a 5 bit MSB in the same byte&n; *  as the LUN.&n; */
multiline_comment|/*&n; *      Manufacturers list&n; */
DECL|macro|SCSI_MAN_UNKNOWN
mdefine_line|#define SCSI_MAN_UNKNOWN     0
DECL|macro|SCSI_MAN_NEC
mdefine_line|#define SCSI_MAN_NEC         1
DECL|macro|SCSI_MAN_TOSHIBA
mdefine_line|#define SCSI_MAN_TOSHIBA     2
DECL|macro|SCSI_MAN_NEC_OLDCDR
mdefine_line|#define SCSI_MAN_NEC_OLDCDR  3
DECL|macro|SCSI_MAN_SONY
mdefine_line|#define SCSI_MAN_SONY        4
DECL|macro|SCSI_MAN_PIONEER
mdefine_line|#define SCSI_MAN_PIONEER     5
multiline_comment|/*&n; *  As the scsi do command functions are intelligent, and may need to&n; *  redo a command, we need to keep track of the last command&n; *  executed on each one.&n; */
DECL|macro|WAS_RESET
mdefine_line|#define WAS_RESET       0x01
DECL|macro|WAS_TIMEDOUT
mdefine_line|#define WAS_TIMEDOUT    0x02
DECL|macro|WAS_SENSE
mdefine_line|#define WAS_SENSE       0x04
DECL|macro|IS_RESETTING
mdefine_line|#define IS_RESETTING    0x08
DECL|macro|IS_ABORTING
mdefine_line|#define IS_ABORTING     0x10
DECL|macro|ASKED_FOR_SENSE
mdefine_line|#define ASKED_FOR_SENSE 0x20
multiline_comment|/*&n; *  The scsi_device struct contains what we know about each given scsi&n; *  device.&n; */
DECL|struct|scsi_device
r_typedef
r_struct
id|scsi_device
(brace
DECL|member|next
r_struct
id|scsi_device
op_star
id|next
suffix:semicolon
multiline_comment|/* Used for linked list */
DECL|member|id
DECL|member|lun
DECL|member|channel
r_int
r_char
id|id
comma
id|lun
comma
id|channel
suffix:semicolon
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
multiline_comment|/* Manufacturer of device, for using &n;&t;&t;&t;&t;     * vendor-specific cmd&squot;s */
DECL|member|attached
r_int
id|attached
suffix:semicolon
multiline_comment|/* # of high level drivers attached to &n;&t;&t;&t;&t;     * this */
DECL|member|access_count
r_int
id|access_count
suffix:semicolon
multiline_comment|/* Count of open channels/mounts */
DECL|member|device_wait
r_struct
id|wait_queue
op_star
id|device_wait
suffix:semicolon
multiline_comment|/* Used to wait if device is busy */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|scsi_request_fn
r_void
(paren
op_star
id|scsi_request_fn
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Used to jumpstart things after an &n;&t;&t;&t;&t;     * ioctl */
DECL|member|device_queue
r_struct
id|scsi_cmnd
op_star
id|device_queue
suffix:semicolon
multiline_comment|/* queue of SCSI Command structures */
DECL|member|hostdata
r_void
op_star
id|hostdata
suffix:semicolon
multiline_comment|/* available to low-level driver */
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|scsi_level
r_char
id|scsi_level
suffix:semicolon
DECL|member|vendor
DECL|member|model
DECL|member|rev
r_char
id|vendor
(braket
l_int|8
)braket
comma
id|model
(braket
l_int|16
)braket
comma
id|rev
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|current_tag
r_int
r_char
id|current_tag
suffix:semicolon
multiline_comment|/* current tag */
DECL|member|sync_min_period
r_int
r_char
id|sync_min_period
suffix:semicolon
multiline_comment|/* Not less than this period */
DECL|member|sync_max_offset
r_int
r_char
id|sync_max_offset
suffix:semicolon
multiline_comment|/* Not greater than this offset */
DECL|member|queue_depth
r_int
r_char
id|queue_depth
suffix:semicolon
multiline_comment|/* How deep a queue to use */
DECL|member|writeable
r_int
id|writeable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|removable
r_int
id|removable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|random
r_int
id|random
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_cmdblocks
r_int
id|has_cmdblocks
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changed
r_int
id|changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data invalid due to media change */
DECL|member|busy
r_int
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Used to prevent races */
DECL|member|lockable
r_int
id|lockable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Able to prevent media removal */
DECL|member|borken
r_int
id|borken
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tell the Seagate driver to be &n;&t;&t;&t;&t;     * painfully slow on this device */
DECL|member|tagged_supported
r_int
id|tagged_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports SCSI-II tagged queuing */
DECL|member|tagged_queue
r_int
id|tagged_queue
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SCSI-II tagged queuing enabled */
DECL|member|disconnect
r_int
id|disconnect
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* can disconnect */
DECL|member|soft_reset
r_int
id|soft_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Uses soft reset option */
DECL|member|sync
r_int
id|sync
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Negotiate for sync transfers */
DECL|member|single_lun
r_int
id|single_lun
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates we should only allow I/O to&n;                                     * one of the luns for the device at a &n;                                     * time. */
DECL|member|was_reset
r_int
id|was_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* There was a bus reset on the bus for &n;                                     * this device */
DECL|member|expecting_cc_ua
r_int
id|expecting_cc_ua
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Expecting a CHECK_CONDITION/UNIT_ATTN&n;                                     * because we did a bus reset. */
DECL|typedef|Scsi_Device
)brace
id|Scsi_Device
suffix:semicolon
multiline_comment|/*&n; *  Use these to separate status msg and our bytes&n; */
DECL|macro|status_byte
mdefine_line|#define status_byte(result) (((result) &gt;&gt; 1) &amp; 0xf)
DECL|macro|msg_byte
mdefine_line|#define msg_byte(result)    (((result) &gt;&gt; 8) &amp; 0xff)
DECL|macro|host_byte
mdefine_line|#define host_byte(result)   (((result) &gt;&gt; 16) &amp; 0xff)
DECL|macro|driver_byte
mdefine_line|#define driver_byte(result) (((result) &gt;&gt; 24) &amp; 0xff)
DECL|macro|suggestion
mdefine_line|#define suggestion(result)  (driver_byte(result) &amp; SUGGEST_MASK)
DECL|macro|sense_class
mdefine_line|#define sense_class(sense)  (((sense) &gt;&gt; 4) &amp; 0x7)
DECL|macro|sense_error
mdefine_line|#define sense_error(sense)  ((sense) &amp; 0xf)
DECL|macro|sense_valid
mdefine_line|#define sense_valid(sense)  ((sense) &amp; 0x80);
multiline_comment|/*&n; *  These are the SCSI devices available on the system.&n; */
r_extern
id|Scsi_Device
op_star
id|scsi_devices
suffix:semicolon
multiline_comment|/*&n; *  Initializes all SCSI devices.  This scans all scsi busses.&n; */
r_extern
r_int
id|scsi_dev_init
(paren
r_void
)paren
suffix:semicolon
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|address
r_char
op_star
id|address
suffix:semicolon
multiline_comment|/* Location data is to be transferred to */
DECL|member|alt_address
r_char
op_star
id|alt_address
suffix:semicolon
multiline_comment|/* Location of actual if address is a &n;&t;&t;&t; * dma indirect buffer.  NULL otherwise */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __alpha__
DECL|macro|ISA_DMA_THRESHOLD
macro_line|# define ISA_DMA_THRESHOLD (~0UL)
macro_line|#else
DECL|macro|ISA_DMA_THRESHOLD
macro_line|# define ISA_DMA_THRESHOLD (0x00ffffff)
macro_line|#endif
DECL|macro|CONTIGUOUS_BUFFERS
mdefine_line|#define CONTIGUOUS_BUFFERS(X,Y) ((X-&gt;b_data+X-&gt;b_size) == Y-&gt;b_data)
multiline_comment|/*&n; * These are the return codes for the abort and reset functions.  The mid-level&n; * code uses these to decide what to do next.  Each of the low level abort&n; * and reset functions must correctly indicate what it has done.&n; * The descriptions are written from the point of view of the mid-level code,&n; * so that the return code is telling the mid-level drivers exactly what&n; * the low level driver has already done, and what remains to be done.&n; */
multiline_comment|/* We did not do anything.  &n; * Wait some more for this command to complete, and if this does not work, &n; * try something more serious. */
DECL|macro|SCSI_ABORT_SNOOZE
mdefine_line|#define SCSI_ABORT_SNOOZE 0
multiline_comment|/* This means that we were able to abort the command.  We have already&n; * called the mid-level done function, and do not expect an interrupt that &n; * will lead to another call to the mid-level done function for this command */
DECL|macro|SCSI_ABORT_SUCCESS
mdefine_line|#define SCSI_ABORT_SUCCESS 1
multiline_comment|/* We called for an abort of this command, and we should get an interrupt &n; * when this succeeds.  Thus we should not restore the timer for this&n; * command in the mid-level abort function. */
DECL|macro|SCSI_ABORT_PENDING
mdefine_line|#define SCSI_ABORT_PENDING 2
multiline_comment|/* Unable to abort - command is currently on the bus.  Grin and bear it. */
DECL|macro|SCSI_ABORT_BUSY
mdefine_line|#define SCSI_ABORT_BUSY 3
multiline_comment|/* The command is not active in the low level code. Command probably&n; * finished. */
DECL|macro|SCSI_ABORT_NOT_RUNNING
mdefine_line|#define SCSI_ABORT_NOT_RUNNING 4
multiline_comment|/* Something went wrong.  The low level driver will indicate the correct&n; * error condition when it calls scsi_done, so the mid-level abort function&n; * can simply wait until this comes through */
DECL|macro|SCSI_ABORT_ERROR
mdefine_line|#define SCSI_ABORT_ERROR 5
multiline_comment|/* We do not know how to reset the bus, or we do not want to.  Bummer.&n; * Anyway, just wait a little more for the command in question, and hope that&n; * it eventually finishes.  If it never finishes, the SCSI device could&n; * hang, so use this with caution. */
DECL|macro|SCSI_RESET_SNOOZE
mdefine_line|#define SCSI_RESET_SNOOZE 0
multiline_comment|/* We do not know how to reset the bus, or we do not want to.  Bummer.&n; * We have given up on this ever completing.  The mid-level code will&n; * request sense information to decide how to proceed from here. */
DECL|macro|SCSI_RESET_PUNT
mdefine_line|#define SCSI_RESET_PUNT 1
multiline_comment|/* This means that we were able to reset the bus.  We have restarted all of&n; * the commands that should be restarted, and we should be able to continue&n; * on normally from here.  We do not expect any interrupts that will return&n; * DID_RESET to any of the other commands in the host_queue, and the mid-level&n; * code does not need to do anything special to keep the commands alive. &n; * If a hard reset was performed then all outstanding commands on the&n; * bus have been restarted. */
DECL|macro|SCSI_RESET_SUCCESS
mdefine_line|#define SCSI_RESET_SUCCESS 2
multiline_comment|/* We called for a reset of this bus, and we should get an interrupt &n; * when this succeeds.  Each command should get its own status&n; * passed up to scsi_done, but this has not happened yet. &n; * If a hard reset was performed, then we expect an interrupt&n; * for *each* of the outstanding commands that will have the&n; * effect of restarting the commands.&n; */
DECL|macro|SCSI_RESET_PENDING
mdefine_line|#define SCSI_RESET_PENDING 3
multiline_comment|/* We did a reset, but do not expect an interrupt to signal DID_RESET.&n; * This tells the upper level code to request the sense info, and this&n; * should keep the command alive. */
DECL|macro|SCSI_RESET_WAKEUP
mdefine_line|#define SCSI_RESET_WAKEUP 4
multiline_comment|/* The command is not active in the low level code. Command probably&n;   finished. */
DECL|macro|SCSI_RESET_NOT_RUNNING
mdefine_line|#define SCSI_RESET_NOT_RUNNING 5
multiline_comment|/* Something went wrong, and we do not know how to fix it. */
DECL|macro|SCSI_RESET_ERROR
mdefine_line|#define SCSI_RESET_ERROR 6
DECL|macro|SCSI_RESET_SYNCHRONOUS
mdefine_line|#define SCSI_RESET_SYNCHRONOUS&t;&t;0x01
DECL|macro|SCSI_RESET_ASYNCHRONOUS
mdefine_line|#define SCSI_RESET_ASYNCHRONOUS&t;&t;0x02
DECL|macro|SCSI_RESET_SUGGEST_BUS_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_BUS_RESET&t;0x04
DECL|macro|SCSI_RESET_SUGGEST_HOST_RESET
mdefine_line|#define SCSI_RESET_SUGGEST_HOST_RESET&t;0x08
multiline_comment|/*&n; * This is a bitmask that is ored with one of the above codes.&n; * It tells the mid-level code that we did a hard reset.&n; */
DECL|macro|SCSI_RESET_BUS_RESET
mdefine_line|#define SCSI_RESET_BUS_RESET 0x100
multiline_comment|/*&n; * This is a bitmask that is ored with one of the above codes.&n; * It tells the mid-level code that we did a host adapter reset.&n; */
DECL|macro|SCSI_RESET_HOST_RESET
mdefine_line|#define SCSI_RESET_HOST_RESET 0x200
multiline_comment|/*&n; * Used to mask off bits and to obtain the basic action that was&n; * performed.  &n; */
DECL|macro|SCSI_RESET_ACTION
mdefine_line|#define SCSI_RESET_ACTION   0xff
r_void
op_star
id|scsi_malloc
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
id|scsi_free
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|dma_free_sectors
suffix:semicolon
multiline_comment|/* How much room do we have left */
r_extern
r_int
r_int
id|need_isa_buffer
suffix:semicolon
multiline_comment|/* True if some devices need indirection&n;&t;&t;&t;&t;&t;* buffers */
multiline_comment|/*&n; * The Scsi_Cmnd structure is used by scsi.c internally, and for communication&n; * with low level drivers that support multiple outstanding commands.&n; */
DECL|struct|scsi_pointer
r_typedef
r_struct
id|scsi_pointer
(brace
DECL|member|ptr
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* data pointer */
DECL|member|this_residual
r_int
id|this_residual
suffix:semicolon
multiline_comment|/* left in this buffer */
DECL|member|buffer
r_struct
id|scatterlist
op_star
id|buffer
suffix:semicolon
multiline_comment|/* which buffer */
DECL|member|buffers_residual
r_int
id|buffers_residual
suffix:semicolon
multiline_comment|/* how many buffers left */
DECL|member|Status
r_volatile
r_int
id|Status
suffix:semicolon
DECL|member|Message
r_volatile
r_int
id|Message
suffix:semicolon
DECL|member|have_data_in
r_volatile
r_int
id|have_data_in
suffix:semicolon
DECL|member|sent_command
r_volatile
r_int
id|sent_command
suffix:semicolon
DECL|member|phase
r_volatile
r_int
id|phase
suffix:semicolon
DECL|typedef|Scsi_Pointer
)brace
id|Scsi_Pointer
suffix:semicolon
DECL|struct|scsi_cmnd
r_typedef
r_struct
id|scsi_cmnd
(brace
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|target
DECL|member|lun
DECL|member|channel
r_int
r_char
id|target
comma
id|lun
comma
id|channel
suffix:semicolon
DECL|member|cmd_len
r_int
r_char
id|cmd_len
suffix:semicolon
DECL|member|old_cmd_len
r_int
r_char
id|old_cmd_len
suffix:semicolon
DECL|member|next
DECL|member|prev
DECL|member|device_next
DECL|member|reset_chain
r_struct
id|scsi_cmnd
op_star
id|next
comma
op_star
id|prev
comma
op_star
id|device_next
comma
op_star
id|reset_chain
suffix:semicolon
multiline_comment|/* These elements define the operation we are about to perform */
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|request_bufflen
r_int
id|request_bufflen
suffix:semicolon
multiline_comment|/* Actual request size */
DECL|member|request_buffer
r_void
op_star
id|request_buffer
suffix:semicolon
multiline_comment|/* Actual requested buffer */
multiline_comment|/* These elements define the operation we ultimately want to perform */
DECL|member|data_cmnd
r_int
r_char
id|data_cmnd
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|old_use_sg
r_int
r_int
id|old_use_sg
suffix:semicolon
multiline_comment|/* We save  use_sg here when requesting&n;&t;&t;&t;&t; * sense info */
DECL|member|use_sg
r_int
r_int
id|use_sg
suffix:semicolon
multiline_comment|/* Number of pieces of scatter-gather */
DECL|member|sglist_len
r_int
r_int
id|sglist_len
suffix:semicolon
multiline_comment|/* size of malloc&squot;d scatter-gather list */
DECL|member|abort_reason
r_int
r_int
id|abort_reason
suffix:semicolon
multiline_comment|/* If the mid-level code requests an&n;&t;&t;&t;&t; * abort, this is the reason. */
DECL|member|bufflen
r_int
id|bufflen
suffix:semicolon
multiline_comment|/* Size of data buffer */
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Data buffer */
DECL|member|underflow
r_int
id|underflow
suffix:semicolon
multiline_comment|/* Return error if less than this amount is &n;&t;&t;&t;&t; * transfered */
DECL|member|transfersize
r_int
id|transfersize
suffix:semicolon
multiline_comment|/* How much we are guaranteed to transfer with&n;&t;&t;&t;&t; * each SCSI transfer (ie, between disconnect /&n;&t;&t;&t;&t; * reconnects.&t; Probably == sector size */
DECL|member|request
r_struct
id|request
id|request
suffix:semicolon
multiline_comment|/* A copy of the command we are working on */
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Sense for this command, if needed */
multiline_comment|/*&n;      A SCSI Command is assigned a nonzero serial_number when internal_cmnd&n;      passes it to the driver&squot;s queue command function.  The serial_number&n;      is cleared when scsi_done is entered indicating that the command has&n;      been completed.  If a timeout occurs, the serial number at the moment&n;      of timeout is copied into serial_number_at_timeout.  By subsequently&n;      comparing the serial_number and serial_number_at_timeout fields&n;      during abort or reset processing, we can detect whether the command&n;      has already completed.  This also detects cases where the command has&n;      completed and the SCSI Command structure has already being reused&n;      for another command, so that we can avoid incorrectly aborting or&n;      resetting the new command.&n;    */
DECL|member|serial_number
r_int
r_int
id|serial_number
suffix:semicolon
DECL|member|serial_number_at_timeout
r_int
r_int
id|serial_number_at_timeout
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
DECL|member|allowed
r_int
id|allowed
suffix:semicolon
DECL|member|timeout_per_command
DECL|member|timeout_total
DECL|member|timeout
r_int
id|timeout_per_command
comma
id|timeout_total
comma
id|timeout
suffix:semicolon
multiline_comment|/*&n;     *&t;We handle the timeout differently if it happens when a reset, &n;     *&t;abort, etc are in process. &n;     */
DECL|member|internal_timeout
r_int
r_volatile
r_char
id|internal_timeout
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* These variables are for the cdrom only. Once we have variable size &n;     * buffers in the buffer cache, they will go away. */
DECL|member|this_count
r_int
id|this_count
suffix:semicolon
multiline_comment|/* End of special cdrom variables */
multiline_comment|/* Low-level done function - can be used by low-level driver to point&n;     *&t;to completion function.&t; Not used by mid/upper level code. */
DECL|member|scsi_done
r_void
(paren
op_star
id|scsi_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* Mid-level done function */
multiline_comment|/*&n;     * The following fields can be written to by the host specific code. &n;     * Everything else should be left alone. &n;     */
DECL|member|SCp
id|Scsi_Pointer
id|SCp
suffix:semicolon
multiline_comment|/* Scratchpad used by some host adapters */
DECL|member|host_scribble
r_int
r_char
op_star
id|host_scribble
suffix:semicolon
multiline_comment|/* The host adapter is allowed to&n;&t;&t;&t;&t;    * call scsi_malloc and get some memory&n;&t;&t;&t;&t;    * and hang it here.&t; The host adapter&n;&t;&t;&t;&t;    * is also expected to call scsi_free&n;&t;&t;&t;&t;    * to release this memory.  (The memory&n;&t;&t;&t;&t;    * obtained by scsi_malloc is guaranteed&n;&t;&t;&t;&t;    * to be at an address &lt; 16Mb). */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
multiline_comment|/* SCSI-II queued command tag */
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
multiline_comment|/* Process ID, starts at 0 */
DECL|typedef|Scsi_Cmnd
)brace
id|Scsi_Cmnd
suffix:semicolon
multiline_comment|/*&n; *  scsi_abort aborts the current command that is executing on host host.&n; *  The error code, if non zero is returned in the host byte, otherwise &n; *  DID_ABORT is returned in the hostbyte.&n; */
r_extern
r_int
id|scsi_abort
(paren
id|Scsi_Cmnd
op_star
comma
r_int
id|code
)paren
suffix:semicolon
r_extern
r_void
id|scsi_do_cmd
(paren
id|Scsi_Cmnd
op_star
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buffer
comma
r_int
id|bufflen
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
comma
r_int
id|timeout
comma
r_int
id|retries
)paren
suffix:semicolon
r_extern
id|Scsi_Cmnd
op_star
id|allocate_device
c_func
(paren
r_struct
id|request
op_star
op_star
comma
id|Scsi_Device
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|Scsi_Cmnd
op_star
id|request_queueable
c_func
(paren
r_struct
id|request
op_star
comma
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_reset
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|max_scsi_hosts
suffix:semicolon
r_extern
r_void
id|proc_print_scsidevice
c_func
(paren
id|Scsi_Device
op_star
comma
r_char
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|print_command
c_func
(paren
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_driverbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|print_hostbyte
c_func
(paren
r_int
id|scsiresult
)paren
suffix:semicolon
r_extern
r_void
id|scsi_mark_host_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|Host
)paren
suffix:semicolon
r_extern
r_void
id|scsi_mark_bus_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|Host
comma
r_int
id|channel
)paren
suffix:semicolon
macro_line|#if defined(MAJOR_NR) &amp;&amp; (MAJOR_NR != SCSI_TAPE_MAJOR)
macro_line|#include &quot;hosts.h&quot;
DECL|function|end_scsi_request
r_static
id|Scsi_Cmnd
op_star
id|end_scsi_request
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|uptodate
comma
r_int
id|sectors
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|req
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
id|req-&gt;errors
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uptodate
)paren
(brace
id|printk
c_func
(paren
id|DEVICE_NAME
l_string|&quot; I/O error: dev %s, sector %lu&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|req-&gt;rq_dev
)paren
comma
id|req-&gt;sector
)paren
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
id|req-&gt;nr_sectors
op_sub_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|req-&gt;sector
op_add_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
id|bh-&gt;b_reqnext
op_assign
l_int|NULL
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
id|uptodate
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|sectors
op_sub_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|req-&gt;bh
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;current_nr_sectors
op_assign
id|bh-&gt;b_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;nr_sectors
OL
id|req-&gt;current_nr_sectors
)paren
(brace
id|req-&gt;nr_sectors
op_assign
id|req-&gt;current_nr_sectors
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;end_scsi_request: buffer-list destroyed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_while
c_loop
(paren
id|sectors
op_logical_and
id|bh
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;bh
)paren
(brace
id|req-&gt;buffer
op_assign
id|bh-&gt;b_data
suffix:semicolon
r_return
id|SCpnt
suffix:semicolon
)brace
id|DEVICE_OFF
c_func
(paren
id|req-&gt;rq_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;sem
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|req-&gt;sem
)paren
suffix:semicolon
)brace
id|add_blkdev_randomness
c_func
(paren
id|MAJOR
c_func
(paren
id|req-&gt;rq_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;host-&gt;block
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|SCpnt-&gt;host-&gt;block
suffix:semicolon
id|next
op_ne
id|SCpnt-&gt;host
suffix:semicolon
id|next
op_assign
id|next-&gt;block
)paren
id|wake_up
c_func
(paren
op_amp
id|next-&gt;host_wait
)paren
suffix:semicolon
)brace
id|req-&gt;rq_status
op_assign
id|RQ_INACTIVE
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|SCpnt-&gt;device-&gt;device_wait
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* This is just like INIT_REQUEST, but we need to be aware of the fact&n; * that an interrupt may start another request, so we run this with interrupts&n; * turned off &n; */
DECL|macro|INIT_SCSI_REQUEST
mdefine_line|#define INIT_SCSI_REQUEST       &bslash;&n;    if (!CURRENT) {             &bslash;&n;&t;CLEAR_INTR;             &bslash;&n;&t;restore_flags(flags);&t;&bslash;&n;&t;return;                 &bslash;&n;    }                           &bslash;&n;    if (MAJOR(CURRENT-&gt;rq_dev) != MAJOR_NR)           &bslash;&n;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;);&bslash;&n;    if (CURRENT-&gt;bh) {                                &bslash;&n;&t;if (!buffer_locked(CURRENT-&gt;bh))              &bslash;&n;&t;    panic(DEVICE_NAME &quot;: block not locked&quot;);  &bslash;&n;    }
macro_line|#endif
DECL|macro|SCSI_SLEEP
mdefine_line|#define SCSI_SLEEP(QUEUE, CONDITION) {&t;&t;    &bslash;&n;    if (CONDITION) {&t;&t;&t;            &bslash;&n;&t;struct wait_queue wait = { current, NULL};  &bslash;&n;&t;add_wait_queue(QUEUE, &amp;wait);&t;&t;    &bslash;&n;&t;for(;;) {&t;&t;&t;            &bslash;&n;&t;current-&gt;state = TASK_UNINTERRUPTIBLE;&t;    &bslash;&n;&t;if (CONDITION) {&t;&t;            &bslash;&n;            if (intr_count)&t;                    &bslash;&n;&t;        panic(&quot;scsi: trying to call schedule() in interrupt&quot; &bslash;&n;&t;&t;      &quot;, file %s, line %d.&bslash;n&quot;, __FILE__, __LINE__);  &bslash;&n;&t;    schedule();&t;&t;&t;&bslash;&n;        }&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;        &bslash;&n;&t;    break;      &t;&t;&bslash;&n;&t;}&t;&t;&t;        &bslash;&n;&t;remove_wait_queue(QUEUE, &amp;wait);&bslash;&n;&t;current-&gt;state = TASK_RUNNING;&t;&bslash;&n;    }; }
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
