multiline_comment|/*&n; *&t;scsi.h Copyright (C) 1992 Drew Eckhardt &n; *&t;generic SCSI package header file by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SCSI_H
DECL|macro|_SCSI_H
mdefine_line|#define _SCSI_H
multiline_comment|/*&n;&t;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/scsi.h,v 1.1 1992/04/24 18:01:50 root Exp root $&n;&n;&t;For documentation on the OPCODES, MESSAGES, and SENSE values,&n;&t;please consult the SCSI standard.&n;&n;*/
multiline_comment|/*&n;&t;SCSI opcodes&n;*/
DECL|macro|TEST_UNIT_READY
mdefine_line|#define TEST_UNIT_READY &t;0x00
DECL|macro|REZERO_UNIT
mdefine_line|#define REZERO_UNIT&t;&t;0x01
DECL|macro|REQUEST_SENSE
mdefine_line|#define REQUEST_SENSE&t;&t;0x03
DECL|macro|FORMAT_UNIT
mdefine_line|#define FORMAT_UNIT&t;&t;0x04
DECL|macro|REASSIGN_BLOCKS
mdefine_line|#define REASSIGN_BLOCKS&t;&t;0x07
DECL|macro|READ_6
mdefine_line|#define READ_6&t;&t;&t;0x08
DECL|macro|WRITE_6
mdefine_line|#define WRITE_6&t;&t;&t;0x0a
DECL|macro|SEEK_6
mdefine_line|#define SEEK_6&t;&t;&t;0x0b
DECL|macro|INQUIRY
mdefine_line|#define INQUIRY&t;&t;&t;0x12
DECL|macro|MODE_SELECT
mdefine_line|#define MODE_SELECT&t;&t;0x15
DECL|macro|RESERVE
mdefine_line|#define RESERVE&t;&t;&t;0x16
DECL|macro|RELEASE
mdefine_line|#define RELEASE&t;&t;&t;0x17
DECL|macro|COPY
mdefine_line|#define COPY&t;&t;&t;0x18
DECL|macro|MODE_SENSE
mdefine_line|#define MODE_SENSE&t;&t;0x1a
DECL|macro|START_STOP
mdefine_line|#define START_STOP&t;&t;0x1b
DECL|macro|RECIEVE_DAIGNOSTIC
mdefine_line|#define RECIEVE_DAIGNOSTIC&t;0x1c
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
DECL|macro|COMPARE
mdefine_line|#define COMPARE&t;&t;&t;0x39
DECL|macro|COPY_VERIFY
mdefine_line|#define COPY_VERIFY&t;&t;0x3a
DECL|macro|COMMAND_SIZE
mdefine_line|#define COMMAND_SIZE(opcode) ((opcode) ? ((opcode) &gt; 0x20 ? 10 : 6) : 0)
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
DECL|macro|IDENTIFY
mdefine_line|#define IDENTIFY&t;&t;0x80
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
mdefine_line|#define SUGGEST_RETRY&t;&t;0x08
DECL|macro|SUGGEST_ABORT
mdefine_line|#define SUGGEST_ABORT&t;&t;0x09 
DECL|macro|SUGGEST_REMAP
mdefine_line|#define SUGGEST_REMAP&t;&t;0x0a
DECL|macro|SUGGEST_DIE
mdefine_line|#define SUGGEST_DIE&t;&t;0x0b
DECL|macro|DRIVER_SENSE
mdefine_line|#define DRIVER_SENSE&t;&t;0x10
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
DECL|macro|TYPE_NO_LUN
mdefine_line|#define TYPE_NO_LUN&t;0x7f
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
r_int
r_char
id|host_no
comma
id|id
comma
id|lun
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
DECL|macro|MAX_SCSI_DEVICE
mdefine_line|#define MAX_SCSI_DEVICE 2
r_extern
r_int
id|NR_SCSI_DEVICES
suffix:semicolon
r_extern
id|Scsi_Device
id|scsi_devices
(braket
id|MAX_SCSI_DEVICE
)braket
suffix:semicolon
multiline_comment|/*&n;&t;scsi_abort aborts the current command that is executing on host host.&n;&t;The error code, if non zero is returned in the host byte, otherwise &n;&t;DID_ABORT is returned in the hostbyte.&n;*/
r_extern
r_int
id|scsi_abort
(paren
r_int
id|host
comma
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/*&n;&t;Initializes all SCSI devices.  This scans all scsi busses.&n;*/
r_extern
r_void
id|scsi_dev_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t;You guesed it.  This sends a command to the selected SCSI host &n;*/
r_extern
r_void
id|scsi_do_cmd
(paren
r_int
id|host
comma
r_int
r_char
id|target
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
r_int
comma
r_int
)paren
comma
r_int
id|timeout
comma
r_int
r_char
op_star
id|sense_buffer
comma
r_int
id|retries
)paren
suffix:semicolon
r_int
id|scsi_reset
(paren
r_int
id|host
)paren
suffix:semicolon
macro_line|#endif
eof
