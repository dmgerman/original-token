macro_line|#ifndef _IDE_CD_H
DECL|macro|_IDE_CD_H
mdefine_line|#define _IDE_CD_H
multiline_comment|/*&n; *  linux/drivers/block/ide_modes.h&n; *&n; *  Copyright (C) 1996  Erik Andersen&n; *  Copyright (C) 1998, 1999 Jens Axboe&n; */
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* Turn this on to have the driver print out the meanings of the&n;   ATAPI error codes.  This will use up additional kernel-space&n;   memory, though. */
macro_line|#ifndef VERBOSE_IDE_CD_ERRORS
DECL|macro|VERBOSE_IDE_CD_ERRORS
mdefine_line|#define VERBOSE_IDE_CD_ERRORS 1
macro_line|#endif
multiline_comment|/* Turning this on will remove code to work around various nonstandard&n;   ATAPI implementations.  If you know your drive follows the standard,&n;   this will give you a slightly smaller kernel. */
macro_line|#ifndef STANDARD_ATAPI
DECL|macro|STANDARD_ATAPI
mdefine_line|#define STANDARD_ATAPI 0
macro_line|#endif
multiline_comment|/* Turning this on will disable the door-locking functionality.&n;   This is apparently needed for supermount. */
macro_line|#ifndef NO_DOOR_LOCKING
DECL|macro|NO_DOOR_LOCKING
mdefine_line|#define NO_DOOR_LOCKING 0
macro_line|#endif
multiline_comment|/* Size of buffer to allocate, in blocks, for audio reads. */
macro_line|#ifndef CDROM_NBLOCKS_BUFFER
DECL|macro|CDROM_NBLOCKS_BUFFER
mdefine_line|#define CDROM_NBLOCKS_BUFFER 8
macro_line|#endif
multiline_comment|/************************************************************************/
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE 512
DECL|macro|SECTOR_BITS
mdefine_line|#define SECTOR_BITS 9
DECL|macro|SECTORS_PER_FRAME
mdefine_line|#define SECTORS_PER_FRAME (CD_FRAMESIZE / SECTOR_SIZE)
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a) &lt; (b) ? (a) : (b))
multiline_comment|/* special command codes for strategy routine. */
DECL|macro|PACKET_COMMAND
mdefine_line|#define PACKET_COMMAND        4315
DECL|macro|REQUEST_SENSE_COMMAND
mdefine_line|#define REQUEST_SENSE_COMMAND 4316
DECL|macro|RESET_DRIVE_COMMAND
mdefine_line|#define RESET_DRIVE_COMMAND   4317
multiline_comment|/*&n; * For controlling drive spindown time.&n; */
DECL|macro|CDROMGETSPINDOWN
mdefine_line|#define CDROMGETSPINDOWN        0x531d
DECL|macro|CDROMSETSPINDOWN
mdefine_line|#define CDROMSETSPINDOWN        0x531e
multiline_comment|/* Some ATAPI command opcodes (just like SCSI).&n;   (Some other cdrom-specific codes are in cdrom.h.) */
DECL|macro|TEST_UNIT_READY
mdefine_line|#define TEST_UNIT_READY         0x00
DECL|macro|REQUEST_SENSE
mdefine_line|#define REQUEST_SENSE           0x03
DECL|macro|INQUIRY
mdefine_line|#define INQUIRY                 0x12
DECL|macro|START_STOP
mdefine_line|#define START_STOP              0x1b
DECL|macro|ALLOW_MEDIUM_REMOVAL
mdefine_line|#define ALLOW_MEDIUM_REMOVAL    0x1e
DECL|macro|READ_CAPACITY
mdefine_line|#define READ_CAPACITY           0x25
DECL|macro|READ_10
mdefine_line|#define READ_10                 0x28
DECL|macro|SEEK
mdefine_line|#define SEEK&t;&t;&t;0x2b
DECL|macro|READ_HEADER
mdefine_line|#define READ_HEADER             0x44
DECL|macro|STOP_PLAY_SCAN
mdefine_line|#define STOP_PLAY_SCAN&t;&t;0x4e
DECL|macro|MODE_SELECT_10
mdefine_line|#define MODE_SELECT_10          0x55
DECL|macro|MODE_SENSE_10
mdefine_line|#define MODE_SENSE_10           0x5a
DECL|macro|LOAD_UNLOAD
mdefine_line|#define LOAD_UNLOAD             0xa6
DECL|macro|READ_12
mdefine_line|#define READ_12                 0xa8
DECL|macro|READ_CD_MSF
mdefine_line|#define READ_CD_MSF             0xb9
DECL|macro|SCAN
mdefine_line|#define SCAN&t;&t;&t;0xba
DECL|macro|SET_CD_SPEED
mdefine_line|#define SET_CD_SPEED            0xbb
DECL|macro|PLAY_CD
mdefine_line|#define PLAY_CD                 0xbc
DECL|macro|MECHANISM_STATUS
mdefine_line|#define MECHANISM_STATUS        0xbd
DECL|macro|READ_CD
mdefine_line|#define READ_CD                 0xbe
multiline_comment|/* DVD Opcodes */
DECL|macro|DVD_GET_PERFORMANCE
mdefine_line|#define DVD_GET_PERFORMANCE&t;0xac
multiline_comment|/* Page codes for mode sense/set */
DECL|macro|PAGE_READERR
mdefine_line|#define PAGE_READERR            0x01
DECL|macro|PAGE_CDROM
mdefine_line|#define PAGE_CDROM              0x0d
DECL|macro|PAGE_AUDIO
mdefine_line|#define PAGE_AUDIO              0x0e
DECL|macro|PAGE_CAPABILITIES
mdefine_line|#define PAGE_CAPABILITIES       0x2a
DECL|macro|PAGE_ALL
mdefine_line|#define PAGE_ALL                0x3f
multiline_comment|/* ATAPI sense keys (from table 140 of ATAPI 2.6) */
DECL|macro|NO_SENSE
mdefine_line|#define NO_SENSE                0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR         0x01
DECL|macro|NOT_READY
mdefine_line|#define NOT_READY               0x02
DECL|macro|MEDIUM_ERROR
mdefine_line|#define MEDIUM_ERROR            0x03
DECL|macro|HARDWARE_ERROR
mdefine_line|#define HARDWARE_ERROR          0x04
DECL|macro|ILLEGAL_REQUEST
mdefine_line|#define ILLEGAL_REQUEST         0x05
DECL|macro|UNIT_ATTENTION
mdefine_line|#define UNIT_ATTENTION          0x06
DECL|macro|DATA_PROTECT
mdefine_line|#define DATA_PROTECT            0x07
DECL|macro|ABORTED_COMMAND
mdefine_line|#define ABORTED_COMMAND         0x0b
DECL|macro|MISCOMPARE
mdefine_line|#define MISCOMPARE              0x0e
multiline_comment|/* We want some additional flags for CDROM drives.&n;   To save space in the ide_drive_t struct, use some fields which&n;   doesn&squot;t make sense for CDROMs -- `bios_cyl&squot; and `bios_head&squot;. */
multiline_comment|/* Configuration flags.  These describe the capabilities of the drive.&n;   They generally do not change after initialization, unless we learn&n;   more about the drive from stuff failing. */
DECL|struct|ide_cd_config_flags
r_struct
id|ide_cd_config_flags
(brace
DECL|member|drq_interrupt
id|__u8
id|drq_interrupt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Device sends an interrupt when ready&n;&t;&t;&t;&t;      for a packet command. */
DECL|member|no_doorlock
id|__u8
id|no_doorlock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive cannot lock the door. */
DECL|member|no_eject
id|__u8
id|no_eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive cannot eject the disc. */
DECL|member|nec260
id|__u8
id|nec260
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a pre-1.2 NEC 260 drive. */
DECL|member|playmsf_as_bcd
id|__u8
id|playmsf_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PLAYMSF command takes BCD args. */
DECL|member|tocaddr_as_bcd
id|__u8
id|tocaddr_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TOC addresses are in BCD. */
DECL|member|toctracks_as_bcd
id|__u8
id|toctracks_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TOC track numbers are in BCD. */
DECL|member|subchan_as_bcd
id|__u8
id|subchan_as_bcd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel info is in BCD. */
DECL|member|is_changer
id|__u8
id|is_changer
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a changer. */
DECL|member|cd_r
id|__u8
id|cd_r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R media . */
DECL|member|cd_rw
id|__u8
id|cd_rw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R/W media . */
DECL|member|dvd
id|__u8
id|dvd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a DVD-ROM */
DECL|member|dvd_r
id|__u8
id|dvd_r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM */
DECL|member|dvd_rw
id|__u8
id|dvd_rw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R/W */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can fake writes */
DECL|member|supp_disc_present
id|__u8
id|supp_disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changer can report exact contents&n;&t;&t;&t;&t;      of slots. */
DECL|member|limit_nframes
id|__u8
id|limit_nframes
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive does not provide data in&n;&t;&t;&t;&t;      multiples of SECTOR_SIZE when more&n;&t;&t;&t;&t;      than one interrupt is needed. */
DECL|member|seeking
id|__u8
id|seeking
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Seeking in progress */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|max_speed
id|byte
id|max_speed
suffix:semicolon
multiline_comment|/* Max speed of the drive */
)brace
suffix:semicolon
DECL|macro|CDROM_CONFIG_FLAGS
mdefine_line|#define CDROM_CONFIG_FLAGS(drive) (&amp;(((struct cdrom_info *)(drive-&gt;driver_data))-&gt;config_flags))
multiline_comment|/* State flags.  These give information about the current state of the&n;   drive, and will change during normal operation. */
DECL|struct|ide_cd_state_flags
r_struct
id|ide_cd_state_flags
(brace
DECL|member|media_changed
id|__u8
id|media_changed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Driver has noticed a media change. */
DECL|member|toc_valid
id|__u8
id|toc_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Saved TOC information is current. */
DECL|member|door_locked
id|__u8
id|door_locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We think that the drive door is locked. */
DECL|member|sanyo_slot
id|__u8
id|sanyo_slot
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Sanyo 3 CD changer support */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|current_speed
id|byte
id|current_speed
suffix:semicolon
multiline_comment|/* Current speed of the drive */
)brace
suffix:semicolon
DECL|macro|CDROM_STATE_FLAGS
mdefine_line|#define CDROM_STATE_FLAGS(drive) (&amp;(((struct cdrom_info *)(drive-&gt;driver_data))-&gt;state_flags))
DECL|struct|atapi_request_sense
r_struct
id|atapi_request_sense
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|valid
r_int
r_char
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|error_code
r_int
r_char
id|error_code
suffix:colon
l_int|7
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
r_int
r_char
id|error_code
suffix:colon
l_int|7
suffix:semicolon
r_int
r_char
id|valid
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|reserved1
id|byte
id|reserved1
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ili
r_int
r_char
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sense_key
r_int
r_char
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|sense_key
r_int
r_char
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved2
r_int
r_char
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ili
r_int
r_char
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
r_int
r_char
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|info
id|byte
id|info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|sense_len
id|byte
id|sense_len
suffix:semicolon
DECL|member|command_info
id|byte
id|command_info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|asc
id|byte
id|asc
suffix:semicolon
DECL|member|ascq
id|byte
id|ascq
suffix:semicolon
DECL|member|fru
id|byte
id|fru
suffix:semicolon
DECL|member|sense_key_specific
id|byte
id|sense_key_specific
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|packet_command
r_struct
id|packet_command
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
id|buflen
suffix:semicolon
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|sense_data
r_struct
id|atapi_request_sense
op_star
id|sense_data
suffix:semicolon
DECL|member|c
r_int
r_char
id|c
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure of a MSF cdrom address. */
DECL|struct|atapi_msf
r_struct
id|atapi_msf
(brace
DECL|member|reserved
id|byte
id|reserved
suffix:semicolon
DECL|member|minute
id|byte
id|minute
suffix:semicolon
DECL|member|second
id|byte
id|second
suffix:semicolon
DECL|member|frame
id|byte
id|frame
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Space to hold the disk TOC. */
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS 99
DECL|struct|atapi_toc_header
r_struct
id|atapi_toc_header
(brace
DECL|member|toc_length
r_int
r_int
id|toc_length
suffix:semicolon
DECL|member|first_track
id|byte
id|first_track
suffix:semicolon
DECL|member|last_track
id|byte
id|last_track
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc_entry
r_struct
id|atapi_toc_entry
(brace
DECL|member|reserved1
id|byte
id|reserved1
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|adr
id|__u8
id|adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|control
id|__u8
id|control
suffix:colon
l_int|4
suffix:semicolon
DECL|member|adr
id|__u8
id|adr
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|track
id|byte
id|track
suffix:semicolon
DECL|member|reserved2
id|byte
id|reserved2
suffix:semicolon
r_union
(brace
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|addr
)brace
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_toc
r_struct
id|atapi_toc
(brace
DECL|member|last_session_lba
r_int
id|last_session_lba
suffix:semicolon
DECL|member|xa_flag
r_int
id|xa_flag
suffix:semicolon
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
DECL|member|hdr
r_struct
id|atapi_toc_header
id|hdr
suffix:semicolon
DECL|member|ent
r_struct
id|atapi_toc_entry
id|ent
(braket
id|MAX_TRACKS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* One extra for the leadout. */
)brace
suffix:semicolon
multiline_comment|/* This structure is annoyingly close to, but not identical with,&n;   the cdrom_subchnl structure from cdrom.h. */
DECL|struct|atapi_cdrom_subchnl
r_struct
id|atapi_cdrom_subchnl
(brace
DECL|member|acdsc_reserved
id|u_char
id|acdsc_reserved
suffix:semicolon
DECL|member|acdsc_audiostatus
id|u_char
id|acdsc_audiostatus
suffix:semicolon
DECL|member|acdsc_length
id|u_short
id|acdsc_length
suffix:semicolon
DECL|member|acdsc_format
id|u_char
id|acdsc_format
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|acdsc_ctrl
id|u_char
id|acdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|acdsc_adr
id|u_char
id|acdsc_adr
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|acdsc_adr
id|u_char
id|acdsc_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|acdsc_ctrl
id|u_char
id|acdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|acdsc_trk
id|u_char
id|acdsc_trk
suffix:semicolon
DECL|member|acdsc_ind
id|u_char
id|acdsc_ind
suffix:semicolon
r_union
(brace
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|acdsc_absaddr
)brace
id|acdsc_absaddr
suffix:semicolon
r_union
(brace
DECL|member|msf
r_struct
id|atapi_msf
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|acdsc_reladdr
)brace
id|acdsc_reladdr
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|mechtype_caddy
id|mechtype_caddy
op_assign
l_int|0
comma
DECL|enumerator|mechtype_tray
id|mechtype_tray
op_assign
l_int|1
comma
DECL|enumerator|mechtype_popup
id|mechtype_popup
op_assign
l_int|2
comma
DECL|enumerator|mechtype_individual_changer
id|mechtype_individual_changer
op_assign
l_int|4
comma
DECL|enumerator|mechtype_cartridge_changer
id|mechtype_cartridge_changer
op_assign
l_int|5
DECL|typedef|mechtype_t
)brace
id|mechtype_t
suffix:semicolon
DECL|struct|atapi_capabilities_page
r_struct
id|atapi_capabilities_page
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|parameters_saveable
id|__u8
id|parameters_saveable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_code
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|parameters_saveable
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|page_length
id|byte
id|page_length
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-RAM discs */
DECL|member|dvd_ram_read
id|__u8
id|dvd_ram_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-R discs */
DECL|member|dvd_r_read
id|__u8
id|dvd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-ROM discs */
DECL|member|dvd_rom
id|__u8
id|dvd_rom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading CD-R discs with addressing method 2 */
DECL|member|method2
id|__u8
id|method2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can read from CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_read
id|__u8
id|cd_rw_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports read from CD-R discs (orange book, part II) */
DECL|member|cd_r_read
id|__u8
id|cd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive supports read from CD-R discs (orange book, part II) */
DECL|member|cd_r_read
id|__u8
id|cd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can read from CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_read
id|__u8
id|cd_rw_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports reading CD-R discs with addressing method 2 */
DECL|member|method2
id|__u8
id|method2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-ROM discs */
DECL|member|dvd_rom
id|__u8
id|dvd_rom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-R discs */
DECL|member|dvd_r_read
id|__u8
id|dvd_r_read
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports reading of DVD-RAM discs */
DECL|member|dvd_ram_read
id|__u8
id|dvd_ram_read
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM discs */
DECL|member|dvd_ram_write
id|__u8
id|dvd_ram_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R discs */
DECL|member|dvd_r_write
id|__u8
id|dvd_r_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3a
id|__u8
id|reserved3a
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can fake writes */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write to CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_write
id|__u8
id|cd_rw_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports write to CD-R discs (orange book, part II) */
DECL|member|cd_r_write
id|__u8
id|cd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can write to CD-R discs (orange book, part II) */
DECL|member|cd_r_write
id|__u8
id|cd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can write to CD-R/W (CD-E) discs (orange book, part III) */
DECL|member|cd_rw_write
id|__u8
id|cd_rw_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive can fake writes */
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3a
id|__u8
id|reserved3a
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-R discs */
DECL|member|dvd_r_write
id|__u8
id|dvd_r_write
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can write DVD-RAM discs */
DECL|member|dvd_ram_write
id|__u8
id|dvd_ram_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|2
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved4
id|__u8
id|reserved4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read multisession discs. */
DECL|member|multisession
id|__u8
id|multisession
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 2 data. */
DECL|member|mode2_form2
id|__u8
id|mode2_form2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 1 (XA) data. */
DECL|member|mode2_form1
id|__u8
id|mode2_form1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 2. */
DECL|member|digport2
id|__u8
id|digport2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 1. */
DECL|member|digport1
id|__u8
id|digport1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can deliver a composite audio/video data stream. */
DECL|member|composite
id|__u8
id|composite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports audio play operations. */
DECL|member|audio_play
id|__u8
id|audio_play
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive supports audio play operations. */
DECL|member|audio_play
id|__u8
id|audio_play
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can deliver a composite audio/video data stream. */
DECL|member|composite
id|__u8
id|composite
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 1. */
DECL|member|digport1
id|__u8
id|digport1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports digital output on port 2. */
DECL|member|digport2
id|__u8
id|digport2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 1 (XA) data. */
DECL|member|mode2_form1
id|__u8
id|mode2_form1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read mode 2, form 2 data. */
DECL|member|mode2_form2
id|__u8
id|mode2_form2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read multisession discs. */
DECL|member|multisession
id|__u8
id|multisession
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
id|__u8
id|reserved4
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return Media Catalog Number (UPC) info. */
DECL|member|upc
id|__u8
id|upc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return International Standard Recording Code info. */
DECL|member|isrc
id|__u8
id|isrc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports C2 error pointers. */
DECL|member|c2_pointers
id|__u8
id|c2_pointers
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* R-W data will be returned deinterleaved and error corrected. */
DECL|member|rw_corr
id|__u8
id|rw_corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel reads can return combined R-W information. */
DECL|member|rw_supported
id|__u8
id|rw_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can continue a read cdda operation from a loss of streaming.*/
DECL|member|cdda_accurate
id|__u8
id|cdda_accurate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can read Red Book audio data. */
DECL|member|cdda
id|__u8
id|cdda
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can read Red Book audio data. */
DECL|member|cdda
id|__u8
id|cdda
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can continue a read cdda operation from a loss of streaming.*/
DECL|member|cdda_accurate
id|__u8
id|cdda_accurate
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Subchannel reads can return combined R-W information. */
DECL|member|rw_supported
id|__u8
id|rw_supported
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* R-W data will be returned deinterleaved and error corrected. */
DECL|member|rw_corr
id|__u8
id|rw_corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive supports C2 error pointers. */
DECL|member|c2_pointers
id|__u8
id|c2_pointers
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return International Standard Recording Code info. */
DECL|member|isrc
id|__u8
id|isrc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can return Media Catalog Number (UPC) info. */
DECL|member|upc
id|__u8
id|upc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
multiline_comment|/* Drive mechanism types. */
DECL|member|mechtype
id|mechtype_t
id|mechtype
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can eject a disc or changer cartridge. */
DECL|member|eject
id|__u8
id|eject
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* State of prevent/allow jumper. */
DECL|member|prevent_jumper
id|__u8
id|prevent_jumper
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Present state of door lock. */
DECL|member|lock_state
id|__u8
id|lock_state
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can lock the door. */
DECL|member|lock
id|__u8
id|lock
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Drive can lock the door. */
DECL|member|lock
id|__u8
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Present state of door lock. */
DECL|member|lock_state
id|__u8
id|lock_state
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* State of prevent/allow jumper. */
DECL|member|prevent_jumper
id|__u8
id|prevent_jumper
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive can eject a disc or changer cartridge. */
DECL|member|eject
id|__u8
id|eject
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive mechanism types. */
DECL|member|mechtype
id|mechtype_t
id|mechtype
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved7
id|__u8
id|reserved7
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Drive supports software slot selection. */
DECL|member|sss
id|__u8
id|sss
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Changer can report exact contents of slots. */
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Audio for each channel can be muted independently. */
DECL|member|separate_mute
id|__u8
id|separate_mute
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Audio level for each channel can be controlled independently. */
DECL|member|separate_volume
id|__u8
id|separate_volume
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
multiline_comment|/* Audio level for each channel can be controlled independently. */
DECL|member|separate_volume
id|__u8
id|separate_volume
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Audio for each channel can be muted independently. */
DECL|member|separate_mute
id|__u8
id|separate_mute
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changer can report exact contents of slots. */
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
multiline_comment|/* Drive supports software slot selection. */
DECL|member|sss
id|__u8
id|sss
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved in 1.2 */
DECL|member|reserved7
id|__u8
id|reserved7
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
multiline_comment|/* Note: the following four fields are returned in big-endian form. */
multiline_comment|/* Maximum speed (in kB/s). */
DECL|member|maxspeed
r_int
r_int
id|maxspeed
suffix:semicolon
multiline_comment|/* Number of discrete volume levels. */
DECL|member|n_vol_levels
r_int
r_int
id|n_vol_levels
suffix:semicolon
multiline_comment|/* Size of cache in drive, in kB. */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Current speed (in kB/s). */
DECL|member|curspeed
r_int
r_int
id|curspeed
suffix:semicolon
multiline_comment|/* Truncate the structure here, so we don&squot;t have headaches reading&n;&t;   from older drives. */
)brace
suffix:semicolon
DECL|struct|atapi_mechstat_header
r_struct
id|atapi_mechstat_header
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|fault
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changer_state
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
DECL|member|curslot
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|mech_state
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|5
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|mech_state
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|curlba
id|byte
id|curlba
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|nslots
id|byte
id|nslots
suffix:semicolon
DECL|member|slot_tablelen
id|__u8
r_int
id|slot_tablelen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_slot
r_struct
id|atapi_slot
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|change
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|reserved2
id|byte
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atapi_changer_info
r_struct
id|atapi_changer_info
(brace
DECL|member|hdr
r_struct
id|atapi_mechstat_header
id|hdr
suffix:semicolon
DECL|member|slots
r_struct
id|atapi_slot
id|slots
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Extra per-device info for cdrom drives. */
DECL|struct|cdrom_info
r_struct
id|cdrom_info
(brace
multiline_comment|/* Buffer for table of contents.  NULL if we haven&squot;t allocated&n;&t;   a TOC buffer for this device yet. */
DECL|member|toc
r_struct
id|atapi_toc
op_star
id|toc
suffix:semicolon
multiline_comment|/* Sector buffer.  If a read request wants only the first part&n;&t;   of a cdrom block, we cache the rest of the block here,&n;&t;   in the expectation that the data is going to be wanted soon.&n;&t;   SECTOR_BUFFERED is the number of the first buffered sector,&n;&t;   and NSECTORS_BUFFERED is the number of sectors in the buffer.&n;&t;   Before the buffer is allocated, we should have&n;&t;   SECTOR_BUFFER == NULL and NSECTORS_BUFFERED == 0. */
DECL|member|sector_buffered
r_int
r_int
id|sector_buffered
suffix:semicolon
DECL|member|nsectors_buffered
r_int
r_int
id|nsectors_buffered
suffix:semicolon
DECL|member|sector_buffer
r_char
op_star
id|sector_buffer
suffix:semicolon
multiline_comment|/* The result of the last successful request sense command&n;&t;   on this device. */
DECL|member|sense_data
r_struct
id|atapi_request_sense
id|sense_data
suffix:semicolon
DECL|member|request_sense_request
r_struct
id|request
id|request_sense_request
suffix:semicolon
DECL|member|request_sense_pc
r_struct
id|packet_command
id|request_sense_pc
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|last_block
r_int
r_int
id|last_block
suffix:semicolon
DECL|member|start_seek
r_int
r_int
id|start_seek
suffix:semicolon
multiline_comment|/* Buffer to hold mechanism status and changer slot table. */
DECL|member|changer_info
r_struct
id|atapi_changer_info
op_star
id|changer_info
suffix:semicolon
DECL|member|config_flags
r_struct
id|ide_cd_config_flags
id|config_flags
suffix:semicolon
DECL|member|state_flags
r_struct
id|ide_cd_state_flags
id|state_flags
suffix:semicolon
multiline_comment|/* Per-device info needed by cdrom.c generic driver. */
DECL|member|devinfo
r_struct
id|cdrom_device_info
id|devinfo
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SECTOR_BUFFER_SIZE
mdefine_line|#define SECTOR_BUFFER_SIZE CD_FRAMESIZE
multiline_comment|/****************************************************************************&n; * Descriptions of ATAPI error codes.&n; */
DECL|macro|ARY_LEN
mdefine_line|#define ARY_LEN(a) ((sizeof(a) / sizeof(a[0])))
macro_line|#if VERBOSE_IDE_CD_ERRORS
multiline_comment|/* From Table 124 of the ATAPI 1.2 spec.&n;   Unchanged in Table 140 of the ATAPI 2.6 draft standard. */
DECL|variable|sense_key_texts
r_const
r_char
op_star
r_const
id|sense_key_texts
(braket
l_int|16
)braket
op_assign
(brace
l_string|&quot;No sense data&quot;
comma
l_string|&quot;Recovered error&quot;
comma
l_string|&quot;Not ready&quot;
comma
l_string|&quot;Medium error&quot;
comma
l_string|&quot;Hardware error&quot;
comma
l_string|&quot;Illegal request&quot;
comma
l_string|&quot;Unit attention&quot;
comma
l_string|&quot;Data protect&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;Aborted command&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;(reserved)&quot;
comma
l_string|&quot;Miscompare&quot;
comma
l_string|&quot;(reserved)&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* From Table 37 of the ATAPI 2.6 draft standard. */
r_const
r_struct
(brace
DECL|member|packet_command
r_int
r_int
id|packet_command
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
r_const
id|text
suffix:semicolon
DECL|variable|packet_command_texts
)brace
id|packet_command_texts
(braket
)braket
op_assign
(brace
(brace
id|TEST_UNIT_READY
comma
l_string|&quot;Test Unit Ready&quot;
)brace
comma
(brace
id|REQUEST_SENSE
comma
l_string|&quot;Request Sense&quot;
)brace
comma
(brace
id|INQUIRY
comma
l_string|&quot;Inquiry&quot;
)brace
comma
(brace
id|START_STOP
comma
l_string|&quot;Start Stop Unit&quot;
)brace
comma
(brace
id|ALLOW_MEDIUM_REMOVAL
comma
l_string|&quot;Prevent/Allow Medium Removal&quot;
)brace
comma
(brace
id|READ_CAPACITY
comma
l_string|&quot;Read CD-ROM Capacity&quot;
)brace
comma
(brace
id|READ_10
comma
l_string|&quot;Read(10)&quot;
)brace
comma
(brace
id|SEEK
comma
l_string|&quot;Seek&quot;
)brace
comma
(brace
id|SCMD_READ_TOC
comma
l_string|&quot;Read TOC&quot;
)brace
comma
(brace
id|SCMD_READ_SUBCHANNEL
comma
l_string|&quot;Read Sub-Channel&quot;
)brace
comma
(brace
id|READ_HEADER
comma
l_string|&quot;Read Header&quot;
)brace
comma
(brace
id|STOP_PLAY_SCAN
comma
l_string|&quot;Stop Play/Scan&quot;
)brace
comma
(brace
id|SCMD_PLAYAUDIO10
comma
l_string|&quot;Play Audio&quot;
)brace
comma
(brace
id|SCMD_PLAYAUDIO_MSF
comma
l_string|&quot;Play Audio MSF&quot;
)brace
comma
(brace
id|SCMD_PAUSE_RESUME
comma
l_string|&quot;Pause/Resume&quot;
)brace
comma
(brace
id|MODE_SELECT_10
comma
l_string|&quot;Mode Select&quot;
)brace
comma
(brace
id|MODE_SENSE_10
comma
l_string|&quot;Mode Sense&quot;
)brace
comma
(brace
id|LOAD_UNLOAD
comma
l_string|&quot;Load/Unload CD&quot;
)brace
comma
(brace
id|READ_12
comma
l_string|&quot;Read(12)&quot;
)brace
comma
(brace
id|READ_CD_MSF
comma
l_string|&quot;Read CD MSF&quot;
)brace
comma
(brace
id|SCAN
comma
l_string|&quot;Scan&quot;
)brace
comma
(brace
id|SET_CD_SPEED
comma
l_string|&quot;Set CD Speed&quot;
)brace
comma
(brace
id|PLAY_CD
comma
l_string|&quot;Play CD&quot;
)brace
comma
(brace
id|MECHANISM_STATUS
comma
l_string|&quot;Mechanism Status&quot;
)brace
comma
(brace
id|READ_CD
comma
l_string|&quot;Read CD&quot;
)brace
comma
(brace
id|DVD_GET_PERFORMANCE
comma
l_string|&quot;Get Performance&quot;
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* From Table 125 of the ATAPI 1.2 spec.,&n;   with additions from Tables 141 and 142 of the ATAPI 2.6 draft standard. */
r_const
r_struct
(brace
DECL|member|asc_ascq
r_int
r_int
id|asc_ascq
suffix:semicolon
DECL|member|text
r_const
r_char
op_star
r_const
id|text
suffix:semicolon
DECL|variable|sense_data_texts
)brace
id|sense_data_texts
(braket
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_string|&quot;No additional sense information&quot;
)brace
comma
(brace
l_int|0x0011
comma
l_string|&quot;Audio play operation in progress&quot;
)brace
comma
(brace
l_int|0x0012
comma
l_string|&quot;Audio play operation paused&quot;
)brace
comma
(brace
l_int|0x0013
comma
l_string|&quot;Audio play operation successfully completed&quot;
)brace
comma
(brace
l_int|0x0014
comma
l_string|&quot;Audio play operation stopped due to error&quot;
)brace
comma
(brace
l_int|0x0015
comma
l_string|&quot;No current audio status to return&quot;
)brace
comma
(brace
l_int|0x0100
comma
l_string|&quot;Mechanical positioning or changer error&quot;
)brace
comma
(brace
l_int|0x0200
comma
l_string|&quot;No seek complete&quot;
)brace
comma
(brace
l_int|0x0400
comma
l_string|&quot;Logical unit not ready - cause not reportable&quot;
)brace
comma
(brace
l_int|0x0401
comma
l_string|&quot;Logical unit not ready - in progress (sic) of becoming ready&quot;
)brace
comma
(brace
l_int|0x0402
comma
l_string|&quot;Logical unit not ready - initializing command required&quot;
)brace
comma
(brace
l_int|0x0403
comma
l_string|&quot;Logical unit not ready - manual intervention required&quot;
)brace
comma
(brace
l_int|0x0501
comma
l_string|&quot;Media load - eject failed&quot;
)brace
comma
(brace
l_int|0x0600
comma
l_string|&quot;No reference position found&quot;
)brace
comma
(brace
l_int|0x0900
comma
l_string|&quot;Track following error&quot;
)brace
comma
(brace
l_int|0x0901
comma
l_string|&quot;Tracking servo failure&quot;
)brace
comma
(brace
l_int|0x0902
comma
l_string|&quot;Focus servo failure&quot;
)brace
comma
(brace
l_int|0x0903
comma
l_string|&quot;Spindle servo failure&quot;
)brace
comma
(brace
l_int|0x1100
comma
l_string|&quot;Unrecovered read error&quot;
)brace
comma
(brace
l_int|0x1106
comma
l_string|&quot;CIRC unrecovered error&quot;
)brace
comma
(brace
l_int|0x1500
comma
l_string|&quot;Random positioning error&quot;
)brace
comma
(brace
l_int|0x1501
comma
l_string|&quot;Mechanical positioning or changer error&quot;
)brace
comma
(brace
l_int|0x1502
comma
l_string|&quot;Positioning error detected by read of medium&quot;
)brace
comma
(brace
l_int|0x1700
comma
l_string|&quot;Recovered data with no error correction applied&quot;
)brace
comma
(brace
l_int|0x1701
comma
l_string|&quot;Recovered data with retries&quot;
)brace
comma
(brace
l_int|0x1702
comma
l_string|&quot;Recovered data with positive head offset&quot;
)brace
comma
(brace
l_int|0x1703
comma
l_string|&quot;Recovered data with negative head offset&quot;
)brace
comma
(brace
l_int|0x1704
comma
l_string|&quot;Recovered data with retries and/or CIRC applied&quot;
)brace
comma
(brace
l_int|0x1705
comma
l_string|&quot;Recovered data using previous sector ID&quot;
)brace
comma
(brace
l_int|0x1800
comma
l_string|&quot;Recovered data with error correction applied&quot;
)brace
comma
(brace
l_int|0x1801
comma
l_string|&quot;Recovered data with error correction and retries applied&quot;
)brace
comma
(brace
l_int|0x1802
comma
l_string|&quot;Recovered data - the data was auto-reallocated&quot;
)brace
comma
(brace
l_int|0x1803
comma
l_string|&quot;Recovered data with CIRC&quot;
)brace
comma
(brace
l_int|0x1804
comma
l_string|&quot;Recovered data with L-EC&quot;
)brace
comma
multiline_comment|/* Following two not in 2.6. */
(brace
l_int|0x1805
comma
l_string|&quot;Recovered data - recommend reassignment&quot;
)brace
comma
(brace
l_int|0x1806
comma
l_string|&quot;Recovered data - recommend rewrite&quot;
)brace
comma
(brace
l_int|0x1a00
comma
l_string|&quot;Parameter list length error&quot;
)brace
comma
(brace
l_int|0x2000
comma
l_string|&quot;Invalid command operation code&quot;
)brace
comma
(brace
l_int|0x2100
comma
l_string|&quot;Logical block address out of range&quot;
)brace
comma
(brace
l_int|0x2400
comma
l_string|&quot;Invalid field in command packet&quot;
)brace
comma
(brace
l_int|0x2600
comma
l_string|&quot;Invalid field in parameter list&quot;
)brace
comma
(brace
l_int|0x2601
comma
l_string|&quot;Parameter not supported&quot;
)brace
comma
(brace
l_int|0x2602
comma
l_string|&quot;Parameter value invalid&quot;
)brace
comma
multiline_comment|/* Following code not in 2.6. */
(brace
l_int|0x2603
comma
l_string|&quot;Threshold parameters not supported&quot;
)brace
comma
(brace
l_int|0x2800
comma
l_string|&quot;Not ready to ready transition, medium may have changed&quot;
)brace
comma
(brace
l_int|0x2900
comma
l_string|&quot;Power on, reset or bus device reset occurred&quot;
)brace
comma
(brace
l_int|0x2a00
comma
l_string|&quot;Parameters changed&quot;
)brace
comma
(brace
l_int|0x2a01
comma
l_string|&quot;Mode parameters changed&quot;
)brace
comma
(brace
l_int|0x3000
comma
l_string|&quot;Incompatible medium installed&quot;
)brace
comma
(brace
l_int|0x3001
comma
l_string|&quot;Cannot read medium - unknown format&quot;
)brace
comma
(brace
l_int|0x3002
comma
l_string|&quot;Cannot read medium - incompatible format&quot;
)brace
comma
multiline_comment|/* Following code not in 2.6. */
(brace
l_int|0x3700
comma
l_string|&quot;Rounded parameter&quot;
)brace
comma
(brace
l_int|0x3900
comma
l_string|&quot;Saving parameters not supported&quot;
)brace
comma
(brace
l_int|0x3a00
comma
l_string|&quot;Medium not present&quot;
)brace
comma
(brace
l_int|0x3f00
comma
l_string|&quot;ATAPI CD-ROM drive operating conditions have changed&quot;
)brace
comma
(brace
l_int|0x3f01
comma
l_string|&quot;Microcode has been changed&quot;
)brace
comma
multiline_comment|/* Following two not in 2.6. */
(brace
l_int|0x3f02
comma
l_string|&quot;Changed operating definition&quot;
)brace
comma
(brace
l_int|0x3f03
comma
l_string|&quot;Inquiry data has changed&quot;
)brace
comma
(brace
l_int|0x4000
comma
l_string|&quot;Diagnostic failure on component (ASCQ)&quot;
)brace
comma
(brace
l_int|0x4400
comma
l_string|&quot;Internal ATAPI CD-ROM drive failure&quot;
)brace
comma
(brace
l_int|0x4e00
comma
l_string|&quot;Overlapped commands attempted&quot;
)brace
comma
(brace
l_int|0x5300
comma
l_string|&quot;Media load or eject failed&quot;
)brace
comma
(brace
l_int|0x5302
comma
l_string|&quot;Medium removal prevented&quot;
)brace
comma
(brace
l_int|0x5700
comma
l_string|&quot;Unable to recover table of contents&quot;
)brace
comma
(brace
l_int|0x5a00
comma
l_string|&quot;Operator request or state change input (unspecified)&quot;
)brace
comma
(brace
l_int|0x5a01
comma
l_string|&quot;Operator medium removal request&quot;
)brace
comma
multiline_comment|/* Following two not in 2.6. */
(brace
l_int|0x5b00
comma
l_string|&quot;Threshold condition met&quot;
)brace
comma
(brace
l_int|0x5c00
comma
l_string|&quot;Status change&quot;
)brace
comma
(brace
l_int|0x6300
comma
l_string|&quot;End of user area encountered on this track&quot;
)brace
comma
(brace
l_int|0x6400
comma
l_string|&quot;Illegal mode for this track or incompatible medium&quot;
)brace
comma
multiline_comment|/* Following error is misspelled in ATAPI 2.6 */
(brace
l_int|0xb900
comma
l_string|&quot;Play operation oborted [sic]&quot;
)brace
comma
(brace
l_int|0xbf00
comma
l_string|&quot;Loss of streaming&quot;
)brace
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _IDE_CD_H */
eof
