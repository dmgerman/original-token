multiline_comment|/*&n; * -- &lt;linux/cdrom.h&gt;&n; * general (not only SCSI) header library for linux CDROM drivers&n; * (C) 1992         David Giller rafetmad@oxy.edu&n; *     1994, 1995   Eberhard Moenkeberg emoenke@gwdg.de&n; *&n; */
macro_line|#ifndef&t;_LINUX_CDROM_H
DECL|macro|_LINUX_CDROM_H
mdefine_line|#define&t;_LINUX_CDROM_H
multiline_comment|/*&n; * some fix numbers&n; */
DECL|macro|CD_MINS
mdefine_line|#define CD_MINS             74 /* max. minutes per CD, not really a limit */
DECL|macro|CD_SECS
mdefine_line|#define CD_SECS             60 /* seconds per minute */
DECL|macro|CD_FRAMES
mdefine_line|#define CD_FRAMES           75 /* frames per second */
DECL|macro|CD_SYNC_SIZE
mdefine_line|#define CD_SYNC_SIZE        12 /* 12 sync bytes per raw data frame, not transfered by the drive */
DECL|macro|CD_HEAD_SIZE
mdefine_line|#define CD_HEAD_SIZE         4 /* header (address) bytes per raw data frame */
DECL|macro|CD_SUBHEAD_SIZE
mdefine_line|#define CD_SUBHEAD_SIZE      8 /* subheader bytes per raw XA data frame */
DECL|macro|CD_XA_HEAD
mdefine_line|#define CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* &quot;before data&quot; part of raw XA frame */
DECL|macro|CD_XA_SYNC_HEAD
mdefine_line|#define CD_XA_SYNC_HEAD   (CD_SYNC_SIZE+CD_XA_HEAD)/* sync bytes + header of XA frame */
DECL|macro|CD_FRAMESIZE
mdefine_line|#define CD_FRAMESIZE      2048 /* bytes per frame, &quot;cooked&quot; mode */
DECL|macro|CD_FRAMESIZE_RAW
mdefine_line|#define CD_FRAMESIZE_RAW  2352 /* bytes per frame, &quot;raw&quot; mode */
multiline_comment|/* most drives don&squot;t deliver everything: */
DECL|macro|CD_FRAMESIZE_RAW1
mdefine_line|#define CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE) /* 2340 */
DECL|macro|CD_FRAMESIZE_RAW0
mdefine_line|#define CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /* 2336 */
multiline_comment|/* Optics drive also has a &squot;read all&squot; mode: */
DECL|macro|CD_FRAMESIZE_RAWER
mdefine_line|#define CD_FRAMESIZE_RAWER 2646 /* bytes per frame */
DECL|macro|CD_EDC_SIZE
mdefine_line|#define CD_EDC_SIZE         4 /* bytes EDC per most raw data frame types */
DECL|macro|CD_ZERO_SIZE
mdefine_line|#define CD_ZERO_SIZE        8 /* bytes zero per yellow book mode 1 frame */
DECL|macro|CD_ECC_SIZE
mdefine_line|#define CD_ECC_SIZE       276 /* bytes ECC per most raw data frame types */
DECL|macro|CD_XA_TAIL
mdefine_line|#define CD_XA_TAIL        (CD_EDC_SIZE+CD_ECC_SIZE) /* &quot;after data&quot; part of raw XA frame */
DECL|macro|CD_FRAMESIZE_SUB
mdefine_line|#define CD_FRAMESIZE_SUB    96 /* subchannel data &quot;frame&quot; size */
DECL|macro|CD_MSF_OFFSET
mdefine_line|#define CD_MSF_OFFSET      150 /* MSF numbering offset of first frame */
DECL|macro|CD_CHUNK_SIZE
mdefine_line|#define CD_CHUNK_SIZE       24 /* lowest-level &quot;data bytes piece&quot; */
DECL|macro|CD_NUM_OF_CHUNKS
mdefine_line|#define CD_NUM_OF_CHUNKS    98 /* chunks per frame */
DECL|macro|CD_FRAMESIZE_XA
mdefine_line|#define CD_FRAMESIZE_XA CD_FRAMESIZE_RAW1 /* obsolete name */
DECL|macro|CD_BLOCK_OFFSET
mdefine_line|#define CD_BLOCK_OFFSET    CD_MSF_OFFSET /* obsolete name */
multiline_comment|/*&n; * the raw frame layout:&n; *&n; * - audio (red):                  | audio_sample_bytes |&n; *                                 |        2352        |&n; *&n; * - data (yellow, mode1):         | sync - head - data - EDC - zero - ECC |&n; *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |&n; *&n; * - data (yellow, mode2):         | sync - head - data |&n; *                                 |  12  -   4  - 2336 |&n; *&n; * - XA data (green, mode2 form1): | sync - head - sub - data - EDC - ECC |&n; *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |&n; *&n; * - XA data (green, mode2 form2): | sync - head - sub - data - EDC |&n; *                                 |  12  -   4  -  8  - 2324 -  4  |&n; */
multiline_comment|/*&n; * CDROM IOCTL structures&n; */
DECL|struct|cdrom_blk
r_struct
id|cdrom_blk
(brace
DECL|member|from
r_int
id|from
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_msf
r_struct
id|cdrom_msf
(brace
DECL|member|cdmsf_min0
id|u_char
id|cdmsf_min0
suffix:semicolon
multiline_comment|/* start minute */
DECL|member|cdmsf_sec0
id|u_char
id|cdmsf_sec0
suffix:semicolon
multiline_comment|/* start second */
DECL|member|cdmsf_frame0
id|u_char
id|cdmsf_frame0
suffix:semicolon
multiline_comment|/* start frame */
DECL|member|cdmsf_min1
id|u_char
id|cdmsf_min1
suffix:semicolon
multiline_comment|/* end minute */
DECL|member|cdmsf_sec1
id|u_char
id|cdmsf_sec1
suffix:semicolon
multiline_comment|/* end second */
DECL|member|cdmsf_frame1
id|u_char
id|cdmsf_frame1
suffix:semicolon
multiline_comment|/* end frame */
)brace
suffix:semicolon
DECL|struct|cdrom_ti
r_struct
id|cdrom_ti
(brace
DECL|member|cdti_trk0
id|u_char
id|cdti_trk0
suffix:semicolon
multiline_comment|/* start track */
DECL|member|cdti_ind0
id|u_char
id|cdti_ind0
suffix:semicolon
multiline_comment|/* start index */
DECL|member|cdti_trk1
id|u_char
id|cdti_trk1
suffix:semicolon
multiline_comment|/* end track */
DECL|member|cdti_ind1
id|u_char
id|cdti_ind1
suffix:semicolon
multiline_comment|/* end index */
)brace
suffix:semicolon
DECL|struct|cdrom_tochdr
r_struct
id|cdrom_tochdr
(brace
DECL|member|cdth_trk0
id|u_char
id|cdth_trk0
suffix:semicolon
multiline_comment|/* start track */
DECL|member|cdth_trk1
id|u_char
id|cdth_trk1
suffix:semicolon
multiline_comment|/* end track */
)brace
suffix:semicolon
DECL|struct|cdrom_msf0
r_struct
id|cdrom_msf0
multiline_comment|/* address in MSF format */
(brace
DECL|member|minute
id|u_char
id|minute
suffix:semicolon
DECL|member|second
id|u_char
id|second
suffix:semicolon
DECL|member|frame
id|u_char
id|frame
suffix:semicolon
)brace
suffix:semicolon
DECL|union|cdrom_addr
r_union
id|cdrom_addr
multiline_comment|/* address in either MSF or logical format */
(brace
DECL|member|msf
r_struct
id|cdrom_msf0
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_tocentry
r_struct
id|cdrom_tocentry
(brace
DECL|member|cdte_track
id|u_char
id|cdte_track
suffix:semicolon
DECL|member|cdte_adr
id|u_char
id|cdte_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdte_ctrl
id|u_char
id|cdte_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdte_format
id|u_char
id|cdte_format
suffix:semicolon
DECL|member|cdte_addr
r_union
id|cdrom_addr
id|cdte_addr
suffix:semicolon
DECL|member|cdte_datamode
id|u_char
id|cdte_datamode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CD-ROM address types (cdrom_tocentry.cdte_format)&n; */
DECL|macro|CDROM_LBA
mdefine_line|#define&t;CDROM_LBA 0x01 /* &quot;logical block&quot;: first frame is #0 */
DECL|macro|CDROM_MSF
mdefine_line|#define&t;CDROM_MSF 0x02 /* &quot;minute-second-frame&quot;: binary, not bcd here! */
multiline_comment|/*&n; * bit to tell whether track is data or audio (cdrom_tocentry.cdte_ctrl)&n; */
DECL|macro|CDROM_DATA_TRACK
mdefine_line|#define&t;CDROM_DATA_TRACK&t;0x04
multiline_comment|/*&n; * The leadout track is always 0xAA, regardless of # of tracks on disc&n; */
DECL|macro|CDROM_LEADOUT
mdefine_line|#define&t;CDROM_LEADOUT&t;0xAA
DECL|struct|cdrom_subchnl
r_struct
id|cdrom_subchnl
(brace
DECL|member|cdsc_format
id|u_char
id|cdsc_format
suffix:semicolon
DECL|member|cdsc_audiostatus
id|u_char
id|cdsc_audiostatus
suffix:semicolon
DECL|member|cdsc_adr
id|u_char
id|cdsc_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdsc_ctrl
id|u_char
id|cdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdsc_trk
id|u_char
id|cdsc_trk
suffix:semicolon
DECL|member|cdsc_ind
id|u_char
id|cdsc_ind
suffix:semicolon
DECL|member|cdsc_absaddr
r_union
id|cdrom_addr
id|cdsc_absaddr
suffix:semicolon
DECL|member|cdsc_reladdr
r_union
id|cdrom_addr
id|cdsc_reladdr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_mcn
r_struct
id|cdrom_mcn
(brace
DECL|member|medium_catalog_number
id|u_char
id|medium_catalog_number
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* 13 ASCII digits, null-terminated */
)brace
suffix:semicolon
multiline_comment|/*&n; * audio states (from SCSI-2, but seen with other drives, too)&n; */
DECL|macro|CDROM_AUDIO_INVALID
mdefine_line|#define&t;CDROM_AUDIO_INVALID&t;0x00&t;/* audio status not supported */
DECL|macro|CDROM_AUDIO_PLAY
mdefine_line|#define&t;CDROM_AUDIO_PLAY&t;0x11&t;/* audio play operation in progress */
DECL|macro|CDROM_AUDIO_PAUSED
mdefine_line|#define&t;CDROM_AUDIO_PAUSED&t;0x12&t;/* audio play operation paused */
DECL|macro|CDROM_AUDIO_COMPLETED
mdefine_line|#define&t;CDROM_AUDIO_COMPLETED&t;0x13&t;/* audio play successfully completed */
DECL|macro|CDROM_AUDIO_ERROR
mdefine_line|#define&t;CDROM_AUDIO_ERROR&t;0x14&t;/* audio play stopped due to error */
DECL|macro|CDROM_AUDIO_NO_STATUS
mdefine_line|#define&t;CDROM_AUDIO_NO_STATUS&t;0x15&t;/* no current audio status to return */
DECL|struct|cdrom_volctrl
r_struct
id|cdrom_volctrl
(brace
DECL|member|channel0
id|u_char
id|channel0
suffix:semicolon
DECL|member|channel1
id|u_char
id|channel1
suffix:semicolon
DECL|member|channel2
id|u_char
id|channel2
suffix:semicolon
DECL|member|channel3
id|u_char
id|channel3
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_read
r_struct
id|cdrom_read
(brace
DECL|member|cdread_lba
r_int
id|cdread_lba
suffix:semicolon
DECL|member|cdread_bufaddr
id|caddr_t
id|cdread_bufaddr
suffix:semicolon
DECL|member|cdread_buflen
r_int
id|cdread_buflen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * extensions for transferring audio frames&n; * currently used by sbpcd.c, cdu31a.c, ide-cd.c&n; */
DECL|struct|cdrom_read_audio
r_struct
id|cdrom_read_audio
(brace
DECL|member|addr
r_union
id|cdrom_addr
id|addr
suffix:semicolon
multiline_comment|/* frame address */
DECL|member|addr_format
id|u_char
id|addr_format
suffix:semicolon
multiline_comment|/* CDROM_LBA or CDROM_MSF */
DECL|member|nframes
r_int
id|nframes
suffix:semicolon
multiline_comment|/* number of 2352-byte-frames to read at once, limited by the drivers */
DECL|member|buf
id|u_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* frame buffer (size: nframes*2352 bytes) */
)brace
suffix:semicolon
multiline_comment|/*&n; * this has to be the &quot;arg&quot; of the CDROMMULTISESSION ioctl&n; * for obtaining multi session info.&n; * The returned &quot;addr&quot; is valid only if &quot;xa_flag&quot; is true.&n; */
DECL|struct|cdrom_multisession
r_struct
id|cdrom_multisession
(brace
DECL|member|addr
r_union
id|cdrom_addr
id|addr
suffix:semicolon
multiline_comment|/* frame address: start-of-last-session (not the new &quot;frame 16&quot;!)*/
DECL|member|xa_flag
id|u_char
id|xa_flag
suffix:semicolon
multiline_comment|/* 1: &quot;is XA disk&quot; */
DECL|member|addr_format
id|u_char
id|addr_format
suffix:semicolon
multiline_comment|/* CDROM_LBA or CDROM_MSF */
)brace
suffix:semicolon
macro_line|#ifdef FIVETWELVE
DECL|macro|CDROM_MODE1_SIZE
mdefine_line|#define&t;CDROM_MODE1_SIZE&t;512
macro_line|#else
DECL|macro|CDROM_MODE1_SIZE
mdefine_line|#define&t;CDROM_MODE1_SIZE&t;2048
macro_line|#endif FIVETWELVE
DECL|macro|CDROM_MODE2_SIZE
mdefine_line|#define&t;CDROM_MODE2_SIZE&t;2336
multiline_comment|/*&n; * CD-ROM IOCTL commands&n; * For IOCTL calls, we will commandeer byte 0x53, or &squot;S&squot;.&n; */
DECL|macro|CDROMPAUSE
mdefine_line|#define CDROMPAUSE&t;&t;0x5301
DECL|macro|CDROMRESUME
mdefine_line|#define CDROMRESUME&t;&t;0x5302
DECL|macro|CDROMPLAYMSF
mdefine_line|#define CDROMPLAYMSF&t;&t;0x5303&t;/* (struct cdrom_msf) */
DECL|macro|CDROMPLAYTRKIND
mdefine_line|#define CDROMPLAYTRKIND&t;&t;0x5304&t;/* (struct cdrom_ti) */
DECL|macro|CDROMREADTOCHDR
mdefine_line|#define CDROMREADTOCHDR&t;&t;0x5305&t;/* (struct cdrom_tochdr) */
DECL|macro|CDROMREADTOCENTRY
mdefine_line|#define CDROMREADTOCENTRY&t;0x5306&t;/* (struct cdrom_tocentry) */
DECL|macro|CDROMSTOP
mdefine_line|#define CDROMSTOP&t;&t;0x5307&t;/* stop the drive motor&t;*/
DECL|macro|CDROMSTART
mdefine_line|#define CDROMSTART&t;&t;0x5308&t;/* turn the motor on */
DECL|macro|CDROMEJECT
mdefine_line|#define CDROMEJECT&t;&t;0x5309&t;/* eject CD-ROM media */
DECL|macro|CDROMVOLCTRL
mdefine_line|#define CDROMVOLCTRL&t;&t;0x530a&t;/* (struct cdrom_volctrl) */
DECL|macro|CDROMSUBCHNL
mdefine_line|#define CDROMSUBCHNL&t;&t;0x530b&t;/* (struct cdrom_subchnl) */
DECL|macro|CDROMREADMODE2
mdefine_line|#define CDROMREADMODE2&t;&t;0x530c&t;/* (struct cdrom_read) */
multiline_comment|/* read type-2 data */
DECL|macro|CDROMREADMODE1
mdefine_line|#define CDROMREADMODE1&t;&t;0x530d&t;/* (struct cdrom_read) */
multiline_comment|/* read type-1 data */
DECL|macro|CDROMREADAUDIO
mdefine_line|#define CDROMREADAUDIO&t;&t;0x530e&t;/* (struct cdrom_read_audio) */
multiline_comment|/*&n; * enable (1) / disable (0) auto-ejecting&n; */
DECL|macro|CDROMEJECT_SW
mdefine_line|#define CDROMEJECT_SW&t;&t;0x530f&t;/* arg: 0 or 1 */
multiline_comment|/*&n; * obtain the start-of-last-session address of multi session disks&n; */
DECL|macro|CDROMMULTISESSION
mdefine_line|#define CDROMMULTISESSION&t;0x5310&t;/* (struct cdrom_multisession) */
multiline_comment|/*&n; * obtain the &quot;universal product code&quot; number&n; * (only some data disks have it coded)&n; */
DECL|macro|CDROM_GET_UPC
mdefine_line|#define CDROM_GET_UPC&t;&t;0x5311&t;/* 8 bytes returned */
DECL|macro|CDROMRESET
mdefine_line|#define CDROMRESET&t;&t;0x5312&t;/* hard-reset the drive */
DECL|macro|CDROMVOLREAD
mdefine_line|#define CDROMVOLREAD&t;&t;0x5313&t;/* let the drive tell its volume setting */
multiline_comment|/* (struct cdrom_volctrl) */
multiline_comment|/* &n; * these ioctls are used in aztcd.c and optcd.c&n; */
DECL|macro|CDROMREADRAW
mdefine_line|#define CDROMREADRAW&t;&t;0x5314&t;/* read data in raw mode */
DECL|macro|CDROMREADCOOKED
mdefine_line|#define CDROMREADCOOKED&t;&t;0x5315&t;/* read data in cooked mode */
DECL|macro|CDROMSEEK
mdefine_line|#define CDROMSEEK&t;&t;0x5316  /* seek msf address */
multiline_comment|/*&n; * for playing audio in logical block addressing mode&n; */
DECL|macro|CDROMPLAYBLK
mdefine_line|#define CDROMPLAYBLK&t;&t;0x5317&t;/* (struct cdrom_blk) */
multiline_comment|/* &n; * these ioctls are used in optcd.c&n; */
DECL|macro|CDROMREADALL
mdefine_line|#define CDROMREADALL&t;&t;0x5318&t;/* read all 2646 bytes */
DECL|macro|CDROMCLOSETRAY
mdefine_line|#define CDROMCLOSETRAY&t;&t;0x5319&t;/* pendant of CDROMEJECT */
multiline_comment|/*&n; * For controlling a changer.  (Used by ATAPI driver.)&n; * This ioctl is depreciated in favor of CDROM_SELECT_DISC from&n; * ucdrom.h.  It will probably be deleted during the 2.1 kernel series.&n; */
DECL|macro|CDROMLOADFROMSLOT
mdefine_line|#define CDROMLOADFROMSLOT&t;0x531a&t;/* LOAD disk from slot*/
multiline_comment|/*&n; * CD-ROM-specific SCSI command opcodes&n; */
multiline_comment|/*&n; * Group 2 (10-byte).  All of these are called &squot;optional&squot; by SCSI-II.&n; */
DECL|macro|SCMD_READ_TOC
mdefine_line|#define SCMD_READ_TOC&t;&t;0x43&t;/* read table of contents */
DECL|macro|SCMD_PLAYAUDIO_MSF
mdefine_line|#define SCMD_PLAYAUDIO_MSF&t;0x47&t;/* play data at time offset */
DECL|macro|SCMD_PLAYAUDIO_TI
mdefine_line|#define SCMD_PLAYAUDIO_TI&t;0x48&t;/* play data at track/index */
DECL|macro|SCMD_PAUSE_RESUME
mdefine_line|#define SCMD_PAUSE_RESUME&t;0x4B&t;/* pause/resume audio */
DECL|macro|SCMD_READ_SUBCHANNEL
mdefine_line|#define SCMD_READ_SUBCHANNEL&t;0x42&t;/* read SC info on playing disc */
DECL|macro|SCMD_PLAYAUDIO10
mdefine_line|#define SCMD_PLAYAUDIO10&t;0x45&t;/* play data at logical block */
DECL|macro|SCMD_READ_HEADER
mdefine_line|#define SCMD_READ_HEADER&t;0x44&t;/* read TOC header */
multiline_comment|/*&n; * Group 5&n; */
DECL|macro|SCMD_PLAYAUDIO12
mdefine_line|#define SCMD_PLAYAUDIO12&t;0xA5 &t;/* play data at logical block */
DECL|macro|SCMD_PLAYTRACK_REL12
mdefine_line|#define SCMD_PLAYTRACK_REL12&t;0xA9&t;/* play track at relative offset */
multiline_comment|/*&n; * Group 6 Commands&n; */
DECL|macro|SCMD_CD_PLAYBACK_CONTROL
mdefine_line|#define SCMD_CD_PLAYBACK_CONTROL 0xC9&t;/* Sony vendor-specific audio */
DECL|macro|SCMD_CD_PLAYBACK_STATUS
mdefine_line|#define SCMD_CD_PLAYBACK_STATUS 0xC4&t;/* control opcodes */
multiline_comment|/*&n; * CD-ROM capacity structure.&n; */
DECL|struct|scsi_capacity
r_struct
id|scsi_capacity
(brace
DECL|member|capacity
id|u_long
id|capacity
suffix:semicolon
DECL|member|lbasize
id|u_long
id|lbasize
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CD-ROM MODE_SENSE/MODE_SELECT parameters&n; */
DECL|macro|ERR_RECOVERY_PARMS
mdefine_line|#define ERR_RECOVERY_PARMS&t;0x01
DECL|macro|DISCO_RECO_PARMS
mdefine_line|#define DISCO_RECO_PARMS&t;0x02
DECL|macro|FORMAT_PARMS
mdefine_line|#define FORMAT_PARMS&t;&t;0x03
DECL|macro|GEOMETRY_PARMS
mdefine_line|#define GEOMETRY_PARMS&t;&t;0x04
DECL|macro|CERTIFICATION_PARMS
mdefine_line|#define CERTIFICATION_PARMS&t;0x06
DECL|macro|CACHE_PARMS
mdefine_line|#define CACHE_PARMS&t;&t;0x38
multiline_comment|/*&n; * standard mode-select header prepended to all mode-select commands&n; */
DECL|struct|ccs_modesel_head
r_struct
id|ccs_modesel_head
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|medium
id|u_char
id|medium
suffix:semicolon
multiline_comment|/* device-specific medium type */
DECL|member|_r2
id|u_char
id|_r2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|block_desc_length
id|u_char
id|block_desc_length
suffix:semicolon
multiline_comment|/* block descriptor length */
DECL|member|density
id|u_char
id|density
suffix:semicolon
multiline_comment|/* device-specific density code */
DECL|member|number_blocks_hi
id|u_char
id|number_blocks_hi
suffix:semicolon
multiline_comment|/* number of blocks in this block desc */
DECL|member|number_blocks_med
id|u_char
id|number_blocks_med
suffix:semicolon
DECL|member|number_blocks_lo
id|u_char
id|number_blocks_lo
suffix:semicolon
DECL|member|_r3
id|u_char
id|_r3
suffix:semicolon
DECL|member|block_length_hi
id|u_char
id|block_length_hi
suffix:semicolon
multiline_comment|/* block length for blocks in this desc */
DECL|member|block_length
id|u_short
id|block_length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * error recovery parameters&n; */
DECL|struct|ccs_err_recovery
r_struct
id|ccs_err_recovery
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code */
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length */
DECL|member|awre
id|u_char
id|awre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auto write realloc enabled */
DECL|member|arre
id|u_char
id|arre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auto read realloc enabled */
DECL|member|tb
id|u_char
id|tb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* transfer block */
DECL|member|rc
id|u_char
id|rc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* read continuous */
DECL|member|eec
id|u_char
id|eec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enable early correction */
DECL|member|per
id|u_char
id|per
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* post error */
DECL|member|dte
id|u_char
id|dte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable transfer on error */
DECL|member|dcr
id|u_char
id|dcr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable correction */
DECL|member|retry_count
id|u_char
id|retry_count
suffix:semicolon
multiline_comment|/* error retry count */
DECL|member|correction_span
id|u_char
id|correction_span
suffix:semicolon
multiline_comment|/* largest recov. to be attempted, bits */
DECL|member|head_offset_count
id|u_char
id|head_offset_count
suffix:semicolon
multiline_comment|/* head offset (2&squot;s C) for each retry */
DECL|member|strobe_offset_count
id|u_char
id|strobe_offset_count
suffix:semicolon
multiline_comment|/* data strobe */
DECL|member|recovery_time_limit
id|u_char
id|recovery_time_limit
suffix:semicolon
multiline_comment|/* time limit on recovery attempts&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * disco/reco parameters&n; */
DECL|struct|ccs_disco_reco
r_struct
id|ccs_disco_reco
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code */
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length */
DECL|member|buffer_full_ratio
id|u_char
id|buffer_full_ratio
suffix:semicolon
multiline_comment|/* write buffer reconnect threshold */
DECL|member|buffer_empty_ratio
id|u_char
id|buffer_empty_ratio
suffix:semicolon
multiline_comment|/* read */
DECL|member|bus_inactivity_limit
id|u_short
id|bus_inactivity_limit
suffix:semicolon
multiline_comment|/* limit on bus inactivity time */
DECL|member|disconnect_time_limit
id|u_short
id|disconnect_time_limit
suffix:semicolon
multiline_comment|/* minimum disconnect time */
DECL|member|connect_time_limit
id|u_short
id|connect_time_limit
suffix:semicolon
multiline_comment|/* minimum connect time */
DECL|member|_r2
id|u_short
id|_r2
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
multiline_comment|/*&n; * drive geometry parameters&n; */
DECL|struct|ccs_geometry
r_struct
id|ccs_geometry
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code */
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length */
DECL|member|cyl_ub
id|u_char
id|cyl_ub
suffix:semicolon
multiline_comment|/* #cyls */
DECL|member|cyl_mb
id|u_char
id|cyl_mb
suffix:semicolon
DECL|member|cyl_lb
id|u_char
id|cyl_lb
suffix:semicolon
DECL|member|heads
id|u_char
id|heads
suffix:semicolon
multiline_comment|/* #heads */
DECL|member|precomp_cyl_ub
id|u_char
id|precomp_cyl_ub
suffix:semicolon
multiline_comment|/* precomp start */
DECL|member|precomp_cyl_mb
id|u_char
id|precomp_cyl_mb
suffix:semicolon
DECL|member|precomp_cyl_lb
id|u_char
id|precomp_cyl_lb
suffix:semicolon
DECL|member|current_cyl_ub
id|u_char
id|current_cyl_ub
suffix:semicolon
multiline_comment|/* reduced current start */
DECL|member|current_cyl_mb
id|u_char
id|current_cyl_mb
suffix:semicolon
DECL|member|current_cyl_lb
id|u_char
id|current_cyl_lb
suffix:semicolon
DECL|member|step_rate
id|u_short
id|step_rate
suffix:semicolon
multiline_comment|/* stepping motor rate */
DECL|member|landing_cyl_ub
id|u_char
id|landing_cyl_ub
suffix:semicolon
multiline_comment|/* landing zone */
DECL|member|landing_cyl_mb
id|u_char
id|landing_cyl_mb
suffix:semicolon
DECL|member|landing_cyl_lb
id|u_char
id|landing_cyl_lb
suffix:semicolon
DECL|member|_r2
id|u_char
id|_r2
suffix:semicolon
DECL|member|_r3
id|u_char
id|_r3
suffix:semicolon
DECL|member|_r4
id|u_char
id|_r4
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * cache parameters&n; */
DECL|struct|ccs_cache
r_struct
id|ccs_cache
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code */
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length */
DECL|member|mode
id|u_char
id|mode
suffix:semicolon
multiline_comment|/* cache control byte */
DECL|member|threshold
id|u_char
id|threshold
suffix:semicolon
multiline_comment|/* prefetch threshold */
DECL|member|max_prefetch
id|u_char
id|max_prefetch
suffix:semicolon
multiline_comment|/* maximum prefetch size */
DECL|member|max_multiplier
id|u_char
id|max_multiplier
suffix:semicolon
multiline_comment|/* maximum prefetch multiplier */
DECL|member|min_prefetch
id|u_char
id|min_prefetch
suffix:semicolon
multiline_comment|/* minimum prefetch size */
DECL|member|min_multiplier
id|u_char
id|min_multiplier
suffix:semicolon
multiline_comment|/* minimum prefetch multiplier */
DECL|member|_r2
id|u_char
id|_r2
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif  _LINUX_CDROM_H
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file. &n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
