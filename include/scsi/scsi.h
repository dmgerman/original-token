macro_line|#ifndef _LINUX_SCSI_H
DECL|macro|_LINUX_SCSI_H
mdefine_line|#define _LINUX_SCSI_H
multiline_comment|/*&n; * This header file contains public constants and structures used by&n; * the scsi code for linux.&n; */
multiline_comment|/*&n;    $Header: /usr/src/linux/include/linux/RCS/scsi.h,v 1.3 1993/09/24 12:20:33 drew Exp $&n;&n;    For documentation on the OPCODES, MESSAGES, and SENSE values,&n;    please consult the SCSI standard.&n;&n;*/
multiline_comment|/*&n; *      SCSI opcodes&n; */
DECL|macro|TEST_UNIT_READY
mdefine_line|#define TEST_UNIT_READY       0x00
DECL|macro|REZERO_UNIT
mdefine_line|#define REZERO_UNIT           0x01
DECL|macro|REQUEST_SENSE
mdefine_line|#define REQUEST_SENSE         0x03
DECL|macro|FORMAT_UNIT
mdefine_line|#define FORMAT_UNIT           0x04
DECL|macro|READ_BLOCK_LIMITS
mdefine_line|#define READ_BLOCK_LIMITS     0x05
DECL|macro|REASSIGN_BLOCKS
mdefine_line|#define REASSIGN_BLOCKS       0x07
DECL|macro|READ_6
mdefine_line|#define READ_6                0x08
DECL|macro|WRITE_6
mdefine_line|#define WRITE_6               0x0a
DECL|macro|SEEK_6
mdefine_line|#define SEEK_6                0x0b
DECL|macro|READ_REVERSE
mdefine_line|#define READ_REVERSE          0x0f
DECL|macro|WRITE_FILEMARKS
mdefine_line|#define WRITE_FILEMARKS       0x10
DECL|macro|SPACE
mdefine_line|#define SPACE                 0x11
DECL|macro|INQUIRY
mdefine_line|#define INQUIRY               0x12
DECL|macro|RECOVER_BUFFERED_DATA
mdefine_line|#define RECOVER_BUFFERED_DATA 0x14
DECL|macro|MODE_SELECT
mdefine_line|#define MODE_SELECT           0x15
DECL|macro|RESERVE
mdefine_line|#define RESERVE               0x16
DECL|macro|RELEASE
mdefine_line|#define RELEASE               0x17
DECL|macro|COPY
mdefine_line|#define COPY                  0x18
DECL|macro|ERASE
mdefine_line|#define ERASE                 0x19
DECL|macro|MODE_SENSE
mdefine_line|#define MODE_SENSE            0x1a
DECL|macro|START_STOP
mdefine_line|#define START_STOP            0x1b
DECL|macro|RECEIVE_DIAGNOSTIC
mdefine_line|#define RECEIVE_DIAGNOSTIC    0x1c
DECL|macro|SEND_DIAGNOSTIC
mdefine_line|#define SEND_DIAGNOSTIC       0x1d
DECL|macro|ALLOW_MEDIUM_REMOVAL
mdefine_line|#define ALLOW_MEDIUM_REMOVAL  0x1e
DECL|macro|SET_WINDOW
mdefine_line|#define SET_WINDOW            0x24
DECL|macro|READ_CAPACITY
mdefine_line|#define READ_CAPACITY         0x25
DECL|macro|READ_10
mdefine_line|#define READ_10               0x28
DECL|macro|WRITE_10
mdefine_line|#define WRITE_10              0x2a
DECL|macro|SEEK_10
mdefine_line|#define SEEK_10               0x2b
DECL|macro|WRITE_VERIFY
mdefine_line|#define WRITE_VERIFY          0x2e
DECL|macro|VERIFY
mdefine_line|#define VERIFY                0x2f
DECL|macro|SEARCH_HIGH
mdefine_line|#define SEARCH_HIGH           0x30
DECL|macro|SEARCH_EQUAL
mdefine_line|#define SEARCH_EQUAL          0x31
DECL|macro|SEARCH_LOW
mdefine_line|#define SEARCH_LOW            0x32
DECL|macro|SET_LIMITS
mdefine_line|#define SET_LIMITS            0x33
DECL|macro|PRE_FETCH
mdefine_line|#define PRE_FETCH             0x34
DECL|macro|READ_POSITION
mdefine_line|#define READ_POSITION         0x34
DECL|macro|SYNCHRONIZE_CACHE
mdefine_line|#define SYNCHRONIZE_CACHE     0x35
DECL|macro|LOCK_UNLOCK_CACHE
mdefine_line|#define LOCK_UNLOCK_CACHE     0x36
DECL|macro|READ_DEFECT_DATA
mdefine_line|#define READ_DEFECT_DATA      0x37
DECL|macro|MEDIUM_SCAN
mdefine_line|#define MEDIUM_SCAN           0x38
DECL|macro|COMPARE
mdefine_line|#define COMPARE               0x39
DECL|macro|COPY_VERIFY
mdefine_line|#define COPY_VERIFY           0x3a
DECL|macro|WRITE_BUFFER
mdefine_line|#define WRITE_BUFFER          0x3b
DECL|macro|READ_BUFFER
mdefine_line|#define READ_BUFFER           0x3c
DECL|macro|UPDATE_BLOCK
mdefine_line|#define UPDATE_BLOCK          0x3d
DECL|macro|READ_LONG
mdefine_line|#define READ_LONG             0x3e
DECL|macro|WRITE_LONG
mdefine_line|#define WRITE_LONG            0x3f
DECL|macro|CHANGE_DEFINITION
mdefine_line|#define CHANGE_DEFINITION     0x40
DECL|macro|WRITE_SAME
mdefine_line|#define WRITE_SAME            0x41
DECL|macro|LOG_SELECT
mdefine_line|#define LOG_SELECT            0x4c
DECL|macro|LOG_SENSE
mdefine_line|#define LOG_SENSE             0x4d
DECL|macro|MODE_SELECT_10
mdefine_line|#define MODE_SELECT_10        0x55
DECL|macro|MODE_SENSE_10
mdefine_line|#define MODE_SENSE_10         0x5a
DECL|macro|READ_12
mdefine_line|#define READ_12               0xa8
DECL|macro|WRITE_12
mdefine_line|#define WRITE_12              0xaa
DECL|macro|WRITE_VERIFY_12
mdefine_line|#define WRITE_VERIFY_12       0xae
DECL|macro|SEARCH_HIGH_12
mdefine_line|#define SEARCH_HIGH_12        0xb0
DECL|macro|SEARCH_EQUAL_12
mdefine_line|#define SEARCH_EQUAL_12       0xb1
DECL|macro|SEARCH_LOW_12
mdefine_line|#define SEARCH_LOW_12         0xb2
DECL|macro|SEND_VOLUME_TAG
mdefine_line|#define SEND_VOLUME_TAG       0xb6
DECL|macro|WRITE_LONG_2
mdefine_line|#define WRITE_LONG_2          0xea
multiline_comment|/*&n; *  Status codes&n; */
DECL|macro|GOOD
mdefine_line|#define GOOD                 0x00
DECL|macro|CHECK_CONDITION
mdefine_line|#define CHECK_CONDITION      0x01
DECL|macro|CONDITION_GOOD
mdefine_line|#define CONDITION_GOOD       0x02
DECL|macro|BUSY
mdefine_line|#define BUSY                 0x04
DECL|macro|INTERMEDIATE_GOOD
mdefine_line|#define INTERMEDIATE_GOOD    0x08
DECL|macro|INTERMEDIATE_C_GOOD
mdefine_line|#define INTERMEDIATE_C_GOOD  0x0a
DECL|macro|RESERVATION_CONFLICT
mdefine_line|#define RESERVATION_CONFLICT 0x0c
DECL|macro|QUEUE_FULL
mdefine_line|#define QUEUE_FULL           0x1a
DECL|macro|STATUS_MASK
mdefine_line|#define STATUS_MASK          0x1e
multiline_comment|/*&n; *  SENSE KEYS&n; */
DECL|macro|NO_SENSE
mdefine_line|#define NO_SENSE            0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR     0x01
DECL|macro|NOT_READY
mdefine_line|#define NOT_READY           0x02
DECL|macro|MEDIUM_ERROR
mdefine_line|#define MEDIUM_ERROR        0x03
DECL|macro|HARDWARE_ERROR
mdefine_line|#define HARDWARE_ERROR      0x04
DECL|macro|ILLEGAL_REQUEST
mdefine_line|#define ILLEGAL_REQUEST     0x05
DECL|macro|UNIT_ATTENTION
mdefine_line|#define UNIT_ATTENTION      0x06
DECL|macro|DATA_PROTECT
mdefine_line|#define DATA_PROTECT        0x07
DECL|macro|BLANK_CHECK
mdefine_line|#define BLANK_CHECK         0x08
DECL|macro|COPY_ABORTED
mdefine_line|#define COPY_ABORTED        0x0a
DECL|macro|ABORTED_COMMAND
mdefine_line|#define ABORTED_COMMAND     0x0b
DECL|macro|VOLUME_OVERFLOW
mdefine_line|#define VOLUME_OVERFLOW     0x0d
DECL|macro|MISCOMPARE
mdefine_line|#define MISCOMPARE          0x0e
multiline_comment|/*&n; *  DEVICE TYPES&n; */
DECL|macro|TYPE_DISK
mdefine_line|#define TYPE_DISK           0x00
DECL|macro|TYPE_TAPE
mdefine_line|#define TYPE_TAPE           0x01
DECL|macro|TYPE_PROCESSOR
mdefine_line|#define TYPE_PROCESSOR      0x03    /* HP scanners use this */
DECL|macro|TYPE_WORM
mdefine_line|#define TYPE_WORM           0x04    /* Treated as ROM by our system */
DECL|macro|TYPE_ROM
mdefine_line|#define TYPE_ROM            0x05
DECL|macro|TYPE_SCANNER
mdefine_line|#define TYPE_SCANNER        0x06
DECL|macro|TYPE_MOD
mdefine_line|#define TYPE_MOD            0x07    /* Magneto-optical disk - &n;&t;&t;&t;&t;     * - treated as TYPE_DISK */
DECL|macro|TYPE_NO_LUN
mdefine_line|#define TYPE_NO_LUN         0x7f
multiline_comment|/*&n; *  MESSAGE CODES&n; */
DECL|macro|COMMAND_COMPLETE
mdefine_line|#define COMMAND_COMPLETE    0x00
DECL|macro|EXTENDED_MESSAGE
mdefine_line|#define EXTENDED_MESSAGE    0x01
DECL|macro|EXTENDED_MODIFY_DATA_POINTER
mdefine_line|#define     EXTENDED_MODIFY_DATA_POINTER    0x00
DECL|macro|EXTENDED_SDTR
mdefine_line|#define     EXTENDED_SDTR                   0x01
DECL|macro|EXTENDED_EXTENDED_IDENTIFY
mdefine_line|#define     EXTENDED_EXTENDED_IDENTIFY      0x02    /* SCSI-I only */
DECL|macro|EXTENDED_WDTR
mdefine_line|#define     EXTENDED_WDTR                   0x03
DECL|macro|SAVE_POINTERS
mdefine_line|#define SAVE_POINTERS       0x02
DECL|macro|RESTORE_POINTERS
mdefine_line|#define RESTORE_POINTERS    0x03
DECL|macro|DISCONNECT
mdefine_line|#define DISCONNECT          0x04
DECL|macro|INITIATOR_ERROR
mdefine_line|#define INITIATOR_ERROR     0x05
DECL|macro|ABORT
mdefine_line|#define ABORT               0x06
DECL|macro|MESSAGE_REJECT
mdefine_line|#define MESSAGE_REJECT      0x07
DECL|macro|NOP
mdefine_line|#define NOP                 0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR    0x09
DECL|macro|LINKED_CMD_COMPLETE
mdefine_line|#define LINKED_CMD_COMPLETE 0x0a
DECL|macro|LINKED_FLG_CMD_COMPLETE
mdefine_line|#define LINKED_FLG_CMD_COMPLETE 0x0b
DECL|macro|BUS_DEVICE_RESET
mdefine_line|#define BUS_DEVICE_RESET    0x0c
DECL|macro|INITIATE_RECOVERY
mdefine_line|#define INITIATE_RECOVERY   0x0f            /* SCSI-II only */
DECL|macro|RELEASE_RECOVERY
mdefine_line|#define RELEASE_RECOVERY    0x10            /* SCSI-II only */
DECL|macro|SIMPLE_QUEUE_TAG
mdefine_line|#define SIMPLE_QUEUE_TAG    0x20
DECL|macro|HEAD_OF_QUEUE_TAG
mdefine_line|#define HEAD_OF_QUEUE_TAG   0x21
DECL|macro|ORDERED_QUEUE_TAG
mdefine_line|#define ORDERED_QUEUE_TAG   0x22
multiline_comment|/*&n; * Here are some scsi specific ioctl commands which are sometimes useful.&n; */
multiline_comment|/* These are a few other constants  only used by scsi  devices */
DECL|macro|SCSI_IOCTL_GET_IDLUN
mdefine_line|#define SCSI_IOCTL_GET_IDLUN 0x5382
multiline_comment|/* Used to turn on and off tagged queuing for scsi devices */
DECL|macro|SCSI_IOCTL_TAGGED_ENABLE
mdefine_line|#define SCSI_IOCTL_TAGGED_ENABLE 0x5383
DECL|macro|SCSI_IOCTL_TAGGED_DISABLE
mdefine_line|#define SCSI_IOCTL_TAGGED_DISABLE 0x5384
multiline_comment|/* Used to obtain the host number of a device. */
DECL|macro|SCSI_IOCTL_PROBE_HOST
mdefine_line|#define SCSI_IOCTL_PROBE_HOST 0x5385
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
macro_line|#endif
eof