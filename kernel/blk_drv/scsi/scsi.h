multiline_comment|/*&n; *&t;scsi.h Copyright (C) 1992 Drew Eckhardt &n; *&t;generic SCSI package header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@tantalus.nrl.navy.mil to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/scsi.h,v 1.1 1992/07/24 06:27:38 root Exp root $&n;&n;&t;For documentation on the OPCODES, MESSAGES, and SENSE values,&n;&t;please consult the SCSI standard.&n;&n;*/
multiline_comment|/*&n;&t;SCSI opcodes&n;*/
DECL|macro|TEST_UNIT_READY
mdefine_line|#define TEST_UNIT_READY &t;0x00
DECL|macro|REZERO_UNIT
mdefine_line|#define REZERO_UNIT&t;&t;0x01
DECL|macro|REQUEST_SENSE
mdefine_line|#define REQUEST_SENSE&t;&t;0x03
DECL|macro|FORMAT_UNIT
mdefine_line|#define FORMAT_UNIT&t;&t;0x04
DECL|macro|READ_BLOCK_LIMITS
mdefine_line|#define READ_BLOCK_LIMITS&t;0x05
DECL|macro|REASSIGN_BLOCKS
mdefine_line|#define REASSIGN_BLOCKS&t;&t;0x07
DECL|macro|READ_6
mdefine_line|#define READ_6&t;&t;&t;0x08
DECL|macro|WRITE_6
mdefine_line|#define WRITE_6&t;&t;&t;0x0a
DECL|macro|SEEK_6
mdefine_line|#define SEEK_6&t;&t;&t;0x0b
DECL|macro|READ_REVERSE
mdefine_line|#define READ_REVERSE&t;&t;0x0f
DECL|macro|WRITE_FILEMARKS
mdefine_line|#define WRITE_FILEMARKS&t;&t;0x10
DECL|macro|SPACE
mdefine_line|#define SPACE&t;&t;&t;0x11
DECL|macro|INQUIRY
mdefine_line|#define INQUIRY&t;&t;&t;0x12
DECL|macro|RECOVER_BUFFERED_DATA
mdefine_line|#define RECOVER_BUFFERED_DATA&t;0x14
DECL|macro|MODE_SELECT
mdefine_line|#define MODE_SELECT&t;&t;0x15
DECL|macro|RESERVE
mdefine_line|#define RESERVE&t;&t;&t;0x16
DECL|macro|RELEASE
mdefine_line|#define RELEASE&t;&t;&t;0x17
DECL|macro|COPY
mdefine_line|#define COPY&t;&t;&t;0x18
DECL|macro|ERASE
mdefine_line|#define ERASE&t;&t;&t;0x19
DECL|macro|MODE_SENSE
mdefine_line|#define MODE_SENSE&t;&t;0x1a
DECL|macro|START_STOP
mdefine_line|#define START_STOP&t;&t;0x1b
DECL|macro|RECEIVE_DIAGNOSTIC
mdefine_line|#define RECEIVE_DIAGNOSTIC&t;0x1c
DECL|macro|SEND_DIAGNOSTIC
mdefine_line|#define SEND_DIAGNOSTIC&t;&t;0x1d
DECL|macro|ALLOW_MEDIUM_REMOVAL
mdefine_line|#define ALLOW_MEDIUM_REMOVAL&t;0x1e
DECL|macro|READ_CAPACITY
mdefine_line|#define READ_CAPACITY&t;&t;0x25
DECL|macro|READ_10
mdefine_line|#define READ_10&t;&t;&t;0x28
DECL|macro|WRITE_10
mdefine_line|#define WRITE_10&t;&t;0x2a
DECL|macro|SEEK_10
mdefine_line|#define SEEK_10&t;&t;&t;0x2b
DECL|macro|WRITE_VERIFY
mdefine_line|#define WRITE_VERIFY&t;&t;0x2e
DECL|macro|VERIFY
mdefine_line|#define VERIFY&t;&t;&t;0x2f
DECL|macro|SEARCH_HIGH
mdefine_line|#define SEARCH_HIGH&t;&t;0x30
DECL|macro|SEARCH_EQUAL
mdefine_line|#define SEARCH_EQUAL&t;&t;0x31
DECL|macro|SEARCH_LOW
mdefine_line|#define SEARCH_LOW&t;&t;0x32
DECL|macro|SET_LIMITS
mdefine_line|#define SET_LIMITS&t;&t;0x33
DECL|macro|PRE_FETCH
mdefine_line|#define PRE_FETCH&t;&t;0x34
DECL|macro|READ_POSITION
mdefine_line|#define READ_POSITION&t;&t;0x34
DECL|macro|SYNCRONIZE_CACHE
mdefine_line|#define SYNCRONIZE_CACHE&t;0x35
DECL|macro|LOCK_UNLOCK_CACHE
mdefine_line|#define LOCK_UNLOCK_CACHE&t;0x36
DECL|macro|READ_DEFECT_DATA
mdefine_line|#define READ_DEFECT_DATA&t;0x37
DECL|macro|COMPARE
mdefine_line|#define COMPARE&t;&t;&t;0x39
DECL|macro|COPY_VERIFY
mdefine_line|#define COPY_VERIFY&t;&t;0x3a
DECL|macro|WRITE_BUFFER
mdefine_line|#define WRITE_BUFFER&t;&t;0x3b
DECL|macro|READ_BUFFER
mdefine_line|#define READ_BUFFER&t;&t;0x3c
DECL|macro|READ_LONG
mdefine_line|#define READ_LONG&t;&t;0x3e
DECL|macro|CHANGE_DEFINITION
mdefine_line|#define CHANGE_DEFINITION&t;0x40
DECL|macro|LOG_SELECT
mdefine_line|#define LOG_SELECT&t;&t;0x4c
DECL|macro|LOG_SENSE
mdefine_line|#define LOG_SENSE&t;&t;0x4d
DECL|macro|MODE_SELECT_10
mdefine_line|#define MODE_SELECT_10&t;&t;0x55
DECL|macro|MODE_SENSE_10
mdefine_line|#define MODE_SENSE_10&t;&t;0x5a
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
multiline_comment|/*&n;&t;MESSAGE CODES&n;*/
DECL|macro|COMMAND_COMPLETE
mdefine_line|#define COMMAND_COMPLETE&t;0x00
DECL|macro|EXTENDED_MESSAGE
mdefine_line|#define EXTENDED_MESSAGE&t;0x01
DECL|macro|SAVE_POINTERS
mdefine_line|#define SAVE_POINTERS&t;&t;0x02
DECL|macro|RESTORE_POINTERS
mdefine_line|#define RESTORE_POINTERS &t;0x03
DECL|macro|DISCONNECT
mdefine_line|#define DISCONNECT&t;&t;0x04
DECL|macro|INITIATOR_ERROR
mdefine_line|#define INITIATOR_ERROR&t;&t;0x05
DECL|macro|ABORT
mdefine_line|#define ABORT&t;&t;&t;0x06
DECL|macro|MESSAGE_REJECT
mdefine_line|#define MESSAGE_REJECT&t;&t;0x07
DECL|macro|NOP
mdefine_line|#define NOP&t;&t;&t;0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR&t;0x09
DECL|macro|LINKED_CMD_COMPLETE
mdefine_line|#define LINKED_CMD_COMPLETE&t;0x0a
DECL|macro|LINKED_FLG_CMD_COMPLETE
mdefine_line|#define LINKED_FLG_CMD_COMPLETE&t;0x0b
DECL|macro|BUS_DEVICE_RESET
mdefine_line|#define BUS_DEVICE_RESET&t;0x0c
DECL|macro|IDENTIFY_BASE
mdefine_line|#define IDENTIFY_BASE&t;&t;0x80
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY(can_disconnect, lun)   (IDENTIFY_BASE |&bslash;&n;&t;&t;&t;&t;&t; ((can_disconnect) ?  0x40 : 0) |&bslash;&n;&t;&t;&t;&t;&t; ((lun) &amp; 0x07)) 
multiline_comment|/*&n;&t;Status codes&n;*/
DECL|macro|GOOD
mdefine_line|#define GOOD&t;&t;&t;0x00
DECL|macro|CHECK_CONDITION
mdefine_line|#define CHECK_CONDITION&t;&t;0x01
DECL|macro|CONDITION_GOOD
mdefine_line|#define CONDITION_GOOD&t;&t;0x02
DECL|macro|BUSY
mdefine_line|#define BUSY&t;&t;&t;0x04
DECL|macro|INTERMEDIATE_GOOD
mdefine_line|#define INTERMEDIATE_GOOD&t;0x08
DECL|macro|INTERMEDIATE_C_GOOD
mdefine_line|#define INTERMEDIATE_C_GOOD&t;0x0a
DECL|macro|RESERVATION_CONFLICT
mdefine_line|#define RESERVATION_CONFLICT&t;0x0c
DECL|macro|STATUS_MASK
mdefine_line|#define STATUS_MASK&t;&t;0x1e
multiline_comment|/*&n;&t;the return of the status word will be in the following format :&n;&t;The low byte is the status returned by the SCSI command, &n;&t;with vendor specific bits masked.&n;&n;&t;The next byte is the message which followed the SCSI status.&n;&t;This allows a stos to be used, since the Intel is a little&n;&t;endian machine.&n;&n;&t;The final byte is a host return code, which is one of the following.&n;&n;&t;IE &n;&t;lsb&t;&t;msb&n;&t;status&t;msg&t;host code&t;&n;&n;        Our errors returned by OUR driver, NOT SCSI message.  Orr&squot;d with&n;        SCSI message passed back to driver &lt;IF any&gt;.&n;*/
multiline_comment|/* &t;NO error&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|DID_OK
mdefine_line|#define DID_OK &t;&t;&t;0x00
multiline_comment|/* &t;Couldn&squot;t connect before timeout period&t;&t;&t;&t;*/
DECL|macro|DID_NO_CONNECT
mdefine_line|#define DID_NO_CONNECT&t;&t;0x01
multiline_comment|/*&t;BUS stayed busy through time out period&t;&t;&t;&t;*/
DECL|macro|DID_BUS_BUSY
mdefine_line|#define DID_BUS_BUSY&t;&t;0x02
multiline_comment|/*&t;TIMED OUT for other reason&t;&t;&t;&t;&t;*/
DECL|macro|DID_TIME_OUT
mdefine_line|#define DID_TIME_OUT&t;&t;0x03
multiline_comment|/*&t;BAD target.&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|DID_BAD_TARGET
mdefine_line|#define DID_BAD_TARGET&t;&t;0x04
multiline_comment|/*&t;Told to abort for some other reason&t;&t;&t;&t;*/
DECL|macro|DID_ABORT
mdefine_line|#define&t;DID_ABORT&t;&t;0x05
multiline_comment|/*&n;&t;Parity error&n;*/
DECL|macro|DID_PARITY
mdefine_line|#define DID_PARITY&t;&t;0x06
multiline_comment|/*&n;&t;Internal error&n;*/
DECL|macro|DID_ERROR
mdefine_line|#define DID_ERROR &t;&t;0x07&t;
multiline_comment|/*&n;&t;Reset by somebody.&n;*/
DECL|macro|DID_RESET
mdefine_line|#define DID_RESET &t;&t;0x08
multiline_comment|/*&n;&t;Got an interrupt we weren&squot;t expecting.&n;*/
DECL|macro|DID_BAD_INTR
mdefine_line|#define&t;DID_BAD_INTR&t;&t;0x09
multiline_comment|/*&n;&t;Driver status&n;*/
DECL|macro|DRIVER_OK
mdefine_line|#define DRIVER_OK&t;&t;0x00
multiline_comment|/*&n;&t;These indicate the error that occured, and what is available.&n;*/
DECL|macro|DRIVER_BUSY
mdefine_line|#define DRIVER_BUSY&t;&t;0x01
DECL|macro|DRIVER_SOFT
mdefine_line|#define DRIVER_SOFT&t;&t;0x02
DECL|macro|DRIVER_MEDIA
mdefine_line|#define DRIVER_MEDIA&t;&t;0x03
DECL|macro|DRIVER_ERROR
mdefine_line|#define DRIVER_ERROR&t;&t;0x04&t;
DECL|macro|DRIVER_INVALID
mdefine_line|#define DRIVER_INVALID&t;&t;0x05
DECL|macro|DRIVER_TIMEOUT
mdefine_line|#define DRIVER_TIMEOUT&t;&t;0x06
DECL|macro|DRIVER_HARD
mdefine_line|#define DRIVER_HARD&t;&t;0x07
DECL|macro|SUGGEST_RETRY
mdefine_line|#define SUGGEST_RETRY&t;&t;0x10
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT&t;&t;0x20 
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP&t;&t;0x30
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE&t;&t;0x40
DECL|macro|SUGGEST_SENSE
mdefine_line|#define SUGGEST_SENSE&t;&t;0x80
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;&t;0x08
DECL|macro|DRIVER_MASK
mdefine_line|#define DRIVER_MASK 0x0f
DECL|macro|SUGGEST_MASK
mdefine_line|#define SUGGEST_MASK 0xf0
multiline_comment|/*&n;&n;&t;SENSE KEYS&n;*/
DECL|macro|NO_SENSE
mdefine_line|#define NO_SENSE &t;&t;0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR&t;&t;0x01
DECL|macro|NOT_READY
mdefine_line|#define NOT_READY&t;&t;0x02
DECL|macro|MEDIUM_ERROR
mdefine_line|#define MEDIUM_ERROR&t;&t;0x03
DECL|macro|HARDWARE_ERROR
mdefine_line|#define&t;HARDWARE_ERROR&t;&t;0x04
DECL|macro|ILLEGAL_REQUEST
mdefine_line|#define ILLEGAL_REQUEST&t;&t;0x05
DECL|macro|UNIT_ATTENTION
mdefine_line|#define UNIT_ATTENTION&t;&t;0x06
DECL|macro|DATA_PROTECT
mdefine_line|#define DATA_PROTECT&t;&t;0x07
DECL|macro|BLANK_CHECK
mdefine_line|#define BLANK_CHECK&t;&t;0x08
DECL|macro|COPY_ABORTED
mdefine_line|#define COPY_ABORTED&t;&t;0x0a
DECL|macro|ABORTED_COMMAND
mdefine_line|#define ABORTED_COMMAND&t;&t;0x0b
DECL|macro|VOLUME_OVERFLOW
mdefine_line|#define&t;VOLUME_OVERFLOW&t;&t;0x0d
DECL|macro|MISCOMPARE
mdefine_line|#define MISCOMPARE&t;&t;0x0e
multiline_comment|/*&n;&t;DEVICE TYPES&n;&n;*/
DECL|macro|TYPE_DISK
mdefine_line|#define TYPE_DISK&t;0x00
DECL|macro|TYPE_TAPE
mdefine_line|#define TYPE_TAPE&t;0x01
DECL|macro|TYPE_WORM
mdefine_line|#define TYPE_WORM&t;0x04&t;/* Treated as ROM by our system */
DECL|macro|TYPE_ROM
mdefine_line|#define TYPE_ROM&t;0x05
DECL|macro|TYPE_MOD
mdefine_line|#define TYPE_MOD&t;0x07  /* Magneto-optical disk - treated as TYPE_DISK */
DECL|macro|TYPE_NO_LUN
mdefine_line|#define TYPE_NO_LUN&t;0x7f
multiline_comment|/*&n;&t;SCSI command sets&n;&n;*/
DECL|macro|SCSI_UNKNOWN
mdefine_line|#define SCSI_UNKNOWN&t;0
DECL|macro|SCSI_1
mdefine_line|#define&t;SCSI_1&t;&t;1
DECL|macro|SCSI_1_CCS
mdefine_line|#define&t;SCSI_1_CCS&t;2
DECL|macro|SCSI_2
mdefine_line|#define&t;SCSI_2&t;&t;3
multiline_comment|/*&n;&t;Every SCSI command starts with a one byte OP-code.&n;&t;The next byte&squot;s high three bits are the LUN of the&n;&t;device.  Any multi-byte quantities are stored high byte&n;&t;first, and may have a 5 bit MSB in the same byte&n;&t;as the LUN.&n;*/
multiline_comment|/*&n;&t;The scsi_device struct contains what we know about each given scsi&n;&t;device.&n;*/
DECL|struct|scsi_device
r_typedef
r_struct
id|scsi_device
(brace
DECL|member|host_no
DECL|member|id
DECL|member|lun
DECL|member|index
r_int
r_char
id|host_no
comma
id|id
comma
id|lun
comma
id|index
suffix:semicolon
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
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|scsi_level
r_char
id|scsi_level
suffix:semicolon
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
multiline_comment|/* Tell the Seagate driver to be &n;&t;&t;&t;&t;   painfully slow on this device */
DECL|typedef|Scsi_Device
)brace
id|Scsi_Device
suffix:semicolon
multiline_comment|/*&n;&t;Use these to separate status msg and our bytes&n;*/
DECL|macro|status_byte
mdefine_line|#define status_byte(result) (((result) &gt;&gt; 1) &amp; 0xf)
DECL|macro|msg_byte
mdefine_line|#define msg_byte(result) (((result) &gt;&gt; 8) &amp; 0xff)
DECL|macro|host_byte
mdefine_line|#define host_byte(result) (((result) &gt;&gt; 16) &amp; 0xff)
DECL|macro|driver_byte
mdefine_line|#define driver_byte(result) (((result) &gt;&gt; 24) &amp; 0xff)
DECL|macro|sugestion
mdefine_line|#define sugestion(result) (driver_byte(result) &amp; SUGGEST_MASK)
DECL|macro|sense_class
mdefine_line|#define sense_class(sense) (((sense) &gt;&gt; 4) &amp; 0x7)
DECL|macro|sense_error
mdefine_line|#define sense_error(sense) ((sense) &amp; 0xf)
DECL|macro|sense_valid
mdefine_line|#define sense_valid(sense) ((sense) &amp; 0x80);
multiline_comment|/*&n;&t;These are the SCSI devices available on the system.&n;*/
r_extern
r_int
id|NR_SCSI_DEVICES
suffix:semicolon
r_extern
id|Scsi_Device
op_star
id|scsi_devices
suffix:semicolon
multiline_comment|/*&n;&t;Initializes all SCSI devices.  This scans all scsi busses.&n;*/
r_extern
r_int
r_int
id|scsi_dev_init
(paren
r_int
r_int
comma
r_int
r_int
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
multiline_comment|/* Location of actual if address is a &n;&t;&t;&t;    dma indirect buffer.  NULL otherwise */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0x00ffffff)
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
multiline_comment|/* True if some devices need indirection&n;&t;&t;&t;&t; buffers */
multiline_comment|/*&n;&t;The Scsi_Cmnd structure is used by scsi.c internally, and for communication with&n;&t;low level drivers that support multiple outstanding commands.&n;*/
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
r_int
id|host
suffix:semicolon
DECL|member|target
DECL|member|lun
DECL|member|index
r_int
r_char
id|target
comma
id|lun
comma
id|index
suffix:semicolon
DECL|member|next
DECL|member|prev
r_struct
id|scsi_cmnd
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
multiline_comment|/* These elements define the operation we are about to perform */
DECL|member|cmnd
r_int
r_char
id|cmnd
(braket
l_int|10
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
multiline_comment|/* We save  use_sg here when requesting&n;&t;&t;&t;&t;       sense info */
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
multiline_comment|/* Return error if less than this amount is &n;&t;&t;&t;&t;   transfered */
DECL|member|transfersize
r_int
id|transfersize
suffix:semicolon
multiline_comment|/* How much we are guranteed to transfer with&n;&t;&t;&t;&t;   each SCSI transfer (ie, between disconnect /&n;&t;&t;&t;&t;   reconnects.   Probably == sector size */
DECL|member|request
r_struct
id|request
id|request
suffix:semicolon
multiline_comment|/* A copy of the command we are working on*/
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Sense for this command, if needed*/
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
multiline_comment|/*&n; *&t;We handle the timeout differently if it happens when a reset, &n; *&t;abort, etc are in process. &n; */
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
multiline_comment|/* These variables are for the cdrom only.  Once we have variable size buffers&n;   in the buffer cache, they will go away. */
DECL|member|this_count
r_int
id|this_count
suffix:semicolon
multiline_comment|/* End of special cdrom variables */
multiline_comment|/* Low-level done function - can be used by low-level driver to point&n;&t; to completion function.  Not used by mid/upper level code. */
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
multiline_comment|/* The following fields can be written to by the host specific code. &n;   Everything else should be left alone. */
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
multiline_comment|/* The host adapter is allowed to&n;&t;&t;&t;&t;&t;  call scsi_malloc and get some memory&n;&t;&t;&t;&t;&t;  and hang it here.  The host adapter&n;&t;&t;&t;&t;&t;  is also expected to call scsi_free&n;&t;&t;&t;&t;&t;  to release this memory.  (The memory&n;&t;&t;&t;&t;&t;  obtained by scsi_malloc is guaranteed&n;&t;&t;&t;&t;&t;  to be at an address &lt; 16Mb). */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* Status code from lower level driver */
DECL|typedef|Scsi_Cmnd
)brace
id|Scsi_Cmnd
suffix:semicolon
multiline_comment|/*&n;&t;scsi_abort aborts the current command that is executing on host host.&n;&t;The error code, if non zero is returned in the host byte, otherwise &n;&t;DID_ABORT is returned in the hostbyte.&n;*/
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
r_int
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
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_reset
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|max_scsi_hosts
suffix:semicolon
r_extern
r_int
id|MAX_SD
comma
id|NR_SD
comma
id|MAX_ST
comma
id|NR_ST
comma
id|MAX_SR
comma
id|NR_SR
suffix:semicolon
r_extern
r_int
r_int
id|sd_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sd_init1
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sd_attach
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sr_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sr_init1
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|sr_attach
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|st_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|st_init1
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|st_attach
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
macro_line|#if defined(MAJOR_NR) &amp;&amp; (MAJOR_NR != 9)
DECL|function|end_scsi_request
r_static
r_void
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
r_struct
id|task_struct
op_star
id|p
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
l_string|&quot; I/O error&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dev %04x, sector %d&bslash;n&quot;
comma
id|req-&gt;dev
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
id|bh-&gt;b_uptodate
op_assign
id|uptodate
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
suffix:semicolon
)brace
suffix:semicolon
id|DEVICE_OFF
c_func
(paren
id|req-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|req-&gt;waiting
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;waiting
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;counter
OG
id|current-&gt;counter
)paren
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
id|req-&gt;dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|scsi_devices
(braket
id|SCpnt-&gt;index
)braket
dot
id|device_wait
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* This is just like INIT_REQUEST, but we need to be aware of the fact&n;   that an interrupt may start another request, so we run this with interrupts&n;   turned off */
DECL|macro|INIT_SCSI_REQUEST
mdefine_line|#define INIT_SCSI_REQUEST &bslash;&n;&t;if (!CURRENT) {&bslash;&n;&t;&t;CLEAR_INTR; &bslash;&n;&t;&t;sti();   &bslash;&n;&t;&t;return; &bslash;&n;&t;} &bslash;&n;&t;if (MAJOR(CURRENT-&gt;dev) != MAJOR_NR) &bslash;&n;&t;&t;panic(DEVICE_NAME &quot;: request list destroyed&quot;); &bslash;&n;&t;if (CURRENT-&gt;bh) { &bslash;&n;&t;&t;if (!CURRENT-&gt;bh-&gt;b_lock) &bslash;&n;&t;&t;&t;panic(DEVICE_NAME &quot;: block not locked&quot;); &bslash;&n;&t;}
macro_line|#endif
DECL|macro|SCSI_SLEEP
mdefine_line|#define SCSI_SLEEP(QUEUE, CONDITION) {&t;&t;&t;&t;&bslash;&n;&t;if (CONDITION) {&t;&t;&t;&t;&t;&bslash;&n;                struct wait_queue wait = { current, NULL};      &bslash;&n;&t;&t;add_wait_queue(QUEUE, &amp;wait);&t;&t;&t;&bslash;&n;sleep_repeat:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current-&gt;state = TASK_UNINTERRUPTIBLE;&t;&t;&bslash;&n;&t;&t;if (CONDITION) {&t;&t;&t;&t;&bslash;&n;&t;&t;&t;schedule();&t;&t;&t;&t;&bslash;&n;&t;&t;&t;goto sleep_repeat;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;remove_wait_queue(QUEUE, &amp;wait);&t;&t;&bslash;&n;&t;&t;current-&gt;state = TASK_RUNNING;&t;&t;&t;&bslash;&n;&t;}; }
macro_line|#endif
eof
