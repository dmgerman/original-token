multiline_comment|/*&n; * -- &lt;linux/cdrom.h&gt;&n; * General header file for linux CD-ROM drivers &n; * Copyright (C) 1992         David Giller, rafetmad@oxy.edu&n; *               1994, 1995   Eberhard Moenkeberg, emoenke@gwdg.de&n; *               1996         David van Leeuwen, david@tm.tno.nl&n; *               1997         Erik Andersen, andersee@debian.org&n; */
macro_line|#ifndef&t;_LINUX_CDROM_H
DECL|macro|_LINUX_CDROM_H
mdefine_line|#define&t;_LINUX_CDROM_H
multiline_comment|/*******************************************************&n; * As of Linux 2.1.x, all Linux CD-ROM application programs will use this &n; * (and only this) include file.  It is my hope to provide Linux with&n; * a uniform interface between software accessing CD-ROMs and the various &n; * device drivers that actually talk to the drives.  There may still be&n; * 23 different kinds of strange CD-ROM drives, but at least there will &n; * now be one, and only one, Linux CD-ROM interface.&n; *&n; * Additionally, as of Linux 2.1.x, all Linux application programs &n; * should use the O_NONBLOCK option when opening a CD-ROM device &n; * for subsequent ioctl commands.  This allows for neat system errors &n; * like &quot;No medium found&quot; or &quot;Wrong medium type&quot; upon attempting to &n; * mount or play an empty slot, mount an audio disc, or play a data disc.&n; * Generally, changing an application program to support O_NONBLOCK&n; * is as easy as the following:&n; *       -    drive = open(&quot;/dev/cdrom&quot;, O_RDONLY);&n; *       +    drive = open(&quot;/dev/cdrom&quot;, O_RDONLY | O_NONBLOCK);&n; * It is worth the small change.&n; *&n; *  Patches for many common CD programs (provided by David A. van Leeuwen)&n; *  can be found at:  ftp://ftp.gwdg.de/pub/linux/cdrom/drivers/cm206/&n; * &n; *******************************************************/
multiline_comment|/* When a driver supports a certain function, but the cdrom drive we are &n; * using doesn&squot;t, we will return the error EDRIVE_CANT_DO_THIS.  We will &n; * borrow the &quot;Operation not supported&quot; error from the network folks to &n; * accomplish this.  Maybe someday we will get a more targeted error code, &n; * but this will do for now... */
DECL|macro|EDRIVE_CANT_DO_THIS
mdefine_line|#define EDRIVE_CANT_DO_THIS  EOPNOTSUPP
multiline_comment|/*******************************************************&n; * The CD-ROM IOCTL commands  -- these should be supported by &n; * all the various cdrom drivers.  For the CD-ROM ioctls, we &n; * will commandeer byte 0x53, or &squot;S&squot;.&n; *******************************************************/
DECL|macro|CDROMPAUSE
mdefine_line|#define CDROMPAUSE&t;&t;0x5301 /* Pause Audio Operation */ 
DECL|macro|CDROMRESUME
mdefine_line|#define CDROMRESUME&t;&t;0x5302 /* Resume paused Audio Operation */
DECL|macro|CDROMPLAYMSF
mdefine_line|#define CDROMPLAYMSF&t;&t;0x5303 /* Play Audio MSF (struct cdrom_msf) */
DECL|macro|CDROMPLAYTRKIND
mdefine_line|#define CDROMPLAYTRKIND&t;&t;0x5304 /* Play Audio Track/index &n;                                           (struct cdrom_ti) */
DECL|macro|CDROMREADTOCHDR
mdefine_line|#define CDROMREADTOCHDR&t;&t;0x5305 /* Read TOC header &n;                                           (struct cdrom_tochdr) */
DECL|macro|CDROMREADTOCENTRY
mdefine_line|#define CDROMREADTOCENTRY&t;0x5306 /* Read TOC entry &n;                                           (struct cdrom_tocentry) */
DECL|macro|CDROMSTOP
mdefine_line|#define CDROMSTOP&t;&t;0x5307 /* Stop the cdrom drive */
DECL|macro|CDROMSTART
mdefine_line|#define CDROMSTART&t;&t;0x5308 /* Start the cdrom drive */
DECL|macro|CDROMEJECT
mdefine_line|#define CDROMEJECT&t;&t;0x5309 /* Ejects the cdrom media */
DECL|macro|CDROMVOLCTRL
mdefine_line|#define CDROMVOLCTRL&t;&t;0x530a /* Control output volume &n;                                           (struct cdrom_volctrl) */
DECL|macro|CDROMSUBCHNL
mdefine_line|#define CDROMSUBCHNL&t;&t;0x530b /* Read subchannel data &n;                                           (struct cdrom_subchnl) */
DECL|macro|CDROMREADMODE2
mdefine_line|#define CDROMREADMODE2&t;&t;0x530c /* Read CDROM mode 2 data (2336 Bytes) &n;                                           (struct cdrom_read) */
DECL|macro|CDROMREADMODE1
mdefine_line|#define CDROMREADMODE1&t;&t;0x530d /* Read CDROM mode 1 data (2048 Bytes)&n;                                           (struct cdrom_read) */
DECL|macro|CDROMREADAUDIO
mdefine_line|#define CDROMREADAUDIO&t;&t;0x530e /* (struct cdrom_read_audio) */
DECL|macro|CDROMEJECT_SW
mdefine_line|#define CDROMEJECT_SW&t;&t;0x530f /* enable(1)/disable(0) auto-ejecting */
DECL|macro|CDROMMULTISESSION
mdefine_line|#define CDROMMULTISESSION&t;0x5310 /* Obtain the start-of-last-session &n;                                           address of multi session disks &n;                                           (struct cdrom_multisession) */
DECL|macro|CDROM_GET_MCN
mdefine_line|#define CDROM_GET_MCN&t;&t;0x5311 /* Obtain the &quot;Universal Product Code&quot; &n;                                           if available (struct cdrom_mcn) */
DECL|macro|CDROM_GET_UPC
mdefine_line|#define CDROM_GET_UPC&t;&t;CDROM_GET_MCN  /* This one is depricated, &n;                                          but here anyway for compatability */
DECL|macro|CDROMRESET
mdefine_line|#define CDROMRESET&t;&t;0x5312 /* hard-reset the drive */
DECL|macro|CDROMVOLREAD
mdefine_line|#define CDROMVOLREAD&t;&t;0x5313 /* Get the drive&squot;s volume setting &n;                                          (struct cdrom_volctrl) */
DECL|macro|CDROMREADRAW
mdefine_line|#define CDROMREADRAW&t;&t;0x5314&t;/* read data in raw mode (2352 Bytes)&n;                                           (struct cdrom_read) */
multiline_comment|/* &n; * These ioctls are used only used in aztcd.c and optcd.c&n; */
DECL|macro|CDROMREADCOOKED
mdefine_line|#define CDROMREADCOOKED&t;&t;0x5315&t;/* read data in cooked mode */
DECL|macro|CDROMSEEK
mdefine_line|#define CDROMSEEK&t;&t;0x5316  /* seek msf address */
multiline_comment|/*&n; * This ioctl is only used by the scsi-cd driver.  &n;   It is for playing audio in logical block addressing mode.&n; */
DECL|macro|CDROMPLAYBLK
mdefine_line|#define CDROMPLAYBLK&t;&t;0x5317&t;/* (struct cdrom_blk) */
multiline_comment|/* &n; * These ioctls are used only used in optcd.c&n; */
DECL|macro|CDROMREADALL
mdefine_line|#define CDROMREADALL&t;&t;0x5318&t;/* read all 2646 bytes */
DECL|macro|CDROMCLOSETRAY
mdefine_line|#define CDROMCLOSETRAY&t;&t;0x5319&t;/* pendant of CDROMEJECT */
multiline_comment|/* &n; * These ioctls are implemented through the uniform CD-ROM driver&n; * They _will_ be adopted by all CD-ROM drivers, when all the CD-ROM&n; * drivers are eventually ported to the uniform CD-ROM driver interface.&n; */
DECL|macro|CDROM_SET_OPTIONS
mdefine_line|#define CDROM_SET_OPTIONS&t;0x5320  /* Set behavior options */
DECL|macro|CDROM_CLEAR_OPTIONS
mdefine_line|#define CDROM_CLEAR_OPTIONS&t;0x5321  /* Clear behavior options */
DECL|macro|CDROM_SELECT_SPEED
mdefine_line|#define CDROM_SELECT_SPEED&t;0x5322  /* Set the CD-ROM speed */
DECL|macro|CDROM_SELECT_DISC
mdefine_line|#define CDROM_SELECT_DISC&t;0x5323  /* Select disc (for juke-boxes) */
DECL|macro|CDROM_MEDIA_CHANGED
mdefine_line|#define CDROM_MEDIA_CHANGED&t;0x5325  /* Check is media changed  */
DECL|macro|CDROM_DRIVE_STATUS
mdefine_line|#define CDROM_DRIVE_STATUS&t;0x5326  /* Get tray position, etc. */
DECL|macro|CDROM_DISC_STATUS
mdefine_line|#define CDROM_DISC_STATUS&t;0x5327  /* Get disc type, etc. */
DECL|macro|CDROM_CHANGER_NSLOTS
mdefine_line|#define CDROM_CHANGER_NSLOTS    0x5328  /* Get number of slots */
multiline_comment|/* This ioctl is only used by sbpcd at the moment */
DECL|macro|CDROMAUDIOBUFSIZ
mdefine_line|#define CDROMAUDIOBUFSIZ        0x5382&t;/* set the audio buffer size */
multiline_comment|/*******************************************************&n; * CDROM IOCTL structures&n; *******************************************************/
multiline_comment|/* Address in MSF format */
DECL|struct|cdrom_msf0
r_struct
id|cdrom_msf0
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
multiline_comment|/* Address in either MSF or logical format */
DECL|union|cdrom_addr
r_union
id|cdrom_addr
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
multiline_comment|/* This struct is used by the CDROMPLAYMSF ioctl */
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
multiline_comment|/* This struct is used by the CDROMPLAYTRKIND ioctl */
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
multiline_comment|/* This struct is used by the CDROMREADTOCHDR ioctl */
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
multiline_comment|/* This struct is used by the CDROMVOLCTRL and CDROMVOLREAD ioctls */
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
multiline_comment|/* This struct is used by the CDROMSUBCHNL ioctl */
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
multiline_comment|/* This struct is used by the CDROMREADTOCENTRY ioctl */
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
multiline_comment|/* This struct is used by the CDROMREADMODE1, and CDROMREADMODE2 ioctls */
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
multiline_comment|/* This struct is used by the CDROMREADAUDIO ioctl */
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
multiline_comment|/* number of 2352-byte-frames to read at once */
DECL|member|buf
id|u_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* frame buffer (size: nframes*2352 bytes) */
)brace
suffix:semicolon
multiline_comment|/* This struct is used with the CDROMMULTISESSION ioctl */
DECL|struct|cdrom_multisession
r_struct
id|cdrom_multisession
(brace
DECL|member|addr
r_union
id|cdrom_addr
id|addr
suffix:semicolon
multiline_comment|/* frame address: start-of-last-session &n;&t;                           (not the new &quot;frame 16&quot;!).  Only valid&n;&t;                           if the &quot;xa_flag&quot; is true. */
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
multiline_comment|/* This struct is used with the CDROM_GET_MCN ioctl.  &n; * Very few audio discs actually have Universal Product Code information, &n; * which should just be the Medium Catalog Number on the box.  Also note &n; * that the way the codeis written on CD is _not_ uniform across all discs!&n; */
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
multiline_comment|/* This is used by the CDROMPLAYBLK ioctl */
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
multiline_comment|/*&n; * A CD-ROM physical sector size is 2048, 2052, 2056, 2324, 2332, 2336, &n; * 2340, or 2352 bytes long.  &n;&n;*         Sector types of the standard CD-ROM data formats:&n; *&n; * format   sector type               user data size (bytes)&n; * -----------------------------------------------------------------------------&n; *   1     (Red Book)    CD-DA          2352    (CD_FRAMESIZE_RAW)&n; *   2     (Yellow Book) Mode1 Form1    2048    (CD_FRAMESIZE)&n; *   3     (Yellow Book) Mode1 Form2    2336    (CD_FRAMESIZE_RAW0)&n; *   4     (Green Book)  Mode2 Form1    2048    (CD_FRAMESIZE)&n; *   5     (Green Book)  Mode2 Form2    2328    (2324+4 spare bytes)&n; *&n; *&n; *       The layout of the standard CD-ROM data formats:&n; * -----------------------------------------------------------------------------&n; * - audio (red):                  | audio_sample_bytes |&n; *                                 |        2352        |&n; *&n; * - data (yellow, mode1):         | sync - head - data - EDC - zero - ECC |&n; *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |&n; *&n; * - data (yellow, mode2):         | sync - head - data |&n; *                                 |  12  -   4  - 2336 |&n; *&n; * - XA data (green, mode2 form1): | sync - head - sub - data - EDC - ECC |&n; *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |&n; *&n; * - XA data (green, mode2 form2): | sync - head - sub - data - Spare |&n; *                                 |  12  -   4  -  8  - 2324 -  4    |&n; *&n; */
multiline_comment|/* Some generally useful CD-ROM information -- mostly based on the above */
DECL|macro|CD_MINS
mdefine_line|#define CD_MINS              74 /* max. minutes per CD, not really a limit */
DECL|macro|CD_SECS
mdefine_line|#define CD_SECS              60 /* seconds per minute */
DECL|macro|CD_FRAMES
mdefine_line|#define CD_FRAMES            75 /* frames per second */
DECL|macro|CD_SYNC_SIZE
mdefine_line|#define CD_SYNC_SIZE         12 /* 12 sync bytes per raw data frame */
DECL|macro|CD_MSF_OFFSET
mdefine_line|#define CD_MSF_OFFSET       150 /* MSF numbering offset of first frame */
DECL|macro|CD_CHUNK_SIZE
mdefine_line|#define CD_CHUNK_SIZE        24 /* lowest-level &quot;data bytes piece&quot; */
DECL|macro|CD_NUM_OF_CHUNKS
mdefine_line|#define CD_NUM_OF_CHUNKS     98 /* chunks per frame */
DECL|macro|CD_FRAMESIZE_SUB
mdefine_line|#define CD_FRAMESIZE_SUB     96 /* subchannel data &quot;frame&quot; size */
DECL|macro|CD_HEAD_SIZE
mdefine_line|#define CD_HEAD_SIZE          4 /* header (address) bytes per raw data frame */
DECL|macro|CD_SUBHEAD_SIZE
mdefine_line|#define CD_SUBHEAD_SIZE       8 /* subheader bytes per raw XA data frame */
DECL|macro|CD_EDC_SIZE
mdefine_line|#define CD_EDC_SIZE           4 /* bytes EDC per most raw data frame types */
DECL|macro|CD_ZERO_SIZE
mdefine_line|#define CD_ZERO_SIZE          8 /* bytes zero per yellow book mode 1 frame */
DECL|macro|CD_ECC_SIZE
mdefine_line|#define CD_ECC_SIZE         276 /* bytes ECC per most raw data frame types */
DECL|macro|CD_FRAMESIZE
mdefine_line|#define CD_FRAMESIZE       2048 /* bytes per frame, &quot;cooked&quot; mode */
DECL|macro|CD_FRAMESIZE_RAW
mdefine_line|#define CD_FRAMESIZE_RAW   2352 /* bytes per frame, &quot;raw&quot; mode */
DECL|macro|CD_FRAMESIZE_RAWER
mdefine_line|#define CD_FRAMESIZE_RAWER 2646 /* The maximum possible returned bytes */ 
multiline_comment|/* most drives don&squot;t deliver everything: */
DECL|macro|CD_FRAMESIZE_RAW1
mdefine_line|#define CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE) /*2340*/
DECL|macro|CD_FRAMESIZE_RAW0
mdefine_line|#define CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /*2336*/
DECL|macro|CD_XA_HEAD
mdefine_line|#define CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* &quot;before data&quot; part of raw XA frame */
DECL|macro|CD_XA_TAIL
mdefine_line|#define CD_XA_TAIL        (CD_EDC_SIZE+CD_ECC_SIZE) /* &quot;after data&quot; part of raw XA frame */
DECL|macro|CD_XA_SYNC_HEAD
mdefine_line|#define CD_XA_SYNC_HEAD   (CD_SYNC_SIZE+CD_XA_HEAD) /* sync bytes + header of XA frame */
multiline_comment|/* CD-ROM address types (cdrom_tocentry.cdte_format) */
DECL|macro|CDROM_LBA
mdefine_line|#define&t;CDROM_LBA 0x01 /* &quot;logical block&quot;: first frame is #0 */
DECL|macro|CDROM_MSF
mdefine_line|#define&t;CDROM_MSF 0x02 /* &quot;minute-second-frame&quot;: binary, not bcd here! */
multiline_comment|/* bit to tell whether track is data or audio (cdrom_tocentry.cdte_ctrl) */
DECL|macro|CDROM_DATA_TRACK
mdefine_line|#define&t;CDROM_DATA_TRACK&t;0x04
multiline_comment|/* The leadout track is always 0xAA, regardless of # of tracks on disc */
DECL|macro|CDROM_LEADOUT
mdefine_line|#define&t;CDROM_LEADOUT&t;&t;0xAA
multiline_comment|/* audio states (from SCSI-2, but seen with other drives, too) */
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
multiline_comment|/* CD-ROM-specific SCSI command opcodes */
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
multiline_comment|/* capability flags used with the uniform CD-ROM driver */
DECL|macro|CDC_CLOSE_TRAY
mdefine_line|#define CDC_CLOSE_TRAY&t;&t;0x1     /* caddy systems _can&squot;t_ close */
DECL|macro|CDC_OPEN_TRAY
mdefine_line|#define CDC_OPEN_TRAY&t;&t;0x2     /* but _can_ eject.  */
DECL|macro|CDC_LOCK
mdefine_line|#define CDC_LOCK&t;&t;0x4     /* disable manual eject */
DECL|macro|CDC_SELECT_SPEED
mdefine_line|#define CDC_SELECT_SPEED &t;0x8     /* programmable speed */
DECL|macro|CDC_SELECT_DISC
mdefine_line|#define CDC_SELECT_DISC&t;&t;0x10    /* select disc from juke-box */
DECL|macro|CDC_MULTI_SESSION
mdefine_line|#define CDC_MULTI_SESSION &t;0x20    /* read sessions&gt;1 */
DECL|macro|CDC_MCN
mdefine_line|#define CDC_MCN&t;&t;&t;0x40    /* Medium Catalog Number */
DECL|macro|CDC_MEDIA_CHANGED
mdefine_line|#define CDC_MEDIA_CHANGED &t;0x80    /* media changed */
DECL|macro|CDC_PLAY_AUDIO
mdefine_line|#define CDC_PLAY_AUDIO&t;&t;0x100   /* audio functions */
DECL|macro|CDC_RESET
mdefine_line|#define CDC_RESET               0x200   /* hard reset device */
DECL|macro|CDC_IOCTLS
mdefine_line|#define CDC_IOCTLS              0x400   /* driver has non-standard ioctls */
DECL|macro|CDC_DRIVE_STATUS
mdefine_line|#define CDC_DRIVE_STATUS        0x800   /* driver implements drive status */
multiline_comment|/* drive status possibilities used with the uniform CD-ROM driver */
DECL|macro|CDS_NO_INFO
mdefine_line|#define CDS_NO_INFO&t;&t;0               /* if not implemented */
DECL|macro|CDS_NO_DISC
mdefine_line|#define CDS_NO_DISC&t;&t;1
DECL|macro|CDS_TRAY_OPEN
mdefine_line|#define CDS_TRAY_OPEN&t;&t;2
DECL|macro|CDS_DRIVE_NOT_READY
mdefine_line|#define CDS_DRIVE_NOT_READY&t;3
DECL|macro|CDS_DISC_OK
mdefine_line|#define CDS_DISC_OK&t;&t;4
multiline_comment|/* disc status possibilities, other than CDS_NO_DISC and CDS_NO_INFO */
DECL|macro|CDS_AUDIO
mdefine_line|#define CDS_AUDIO&t;&t;100
DECL|macro|CDS_DATA_1
mdefine_line|#define CDS_DATA_1&t;&t;101
DECL|macro|CDS_DATA_2
mdefine_line|#define CDS_DATA_2&t;&t;102
DECL|macro|CDS_XA_2_1
mdefine_line|#define CDS_XA_2_1&t;&t;103
DECL|macro|CDS_XA_2_2
mdefine_line|#define CDS_XA_2_2&t;&t;104
multiline_comment|/* User-configurable behavior options for the uniform CD-ROM driver */
DECL|macro|CDO_AUTO_CLOSE
mdefine_line|#define CDO_AUTO_CLOSE&t;&t;0x1     /* close tray on first open() */
DECL|macro|CDO_AUTO_EJECT
mdefine_line|#define CDO_AUTO_EJECT&t;&t;0x2     /* open tray on last release() */
DECL|macro|CDO_USE_FFLAGS
mdefine_line|#define CDO_USE_FFLAGS&t;&t;0x4     /* use O_NONBLOCK information on open */
DECL|macro|CDO_LOCK
mdefine_line|#define CDO_LOCK&t;&t;0x8     /* lock tray on open files */
DECL|macro|CDO_CHECK_TYPE
mdefine_line|#define CDO_CHECK_TYPE&t;&t;0x10    /* check type on open for data */
multiline_comment|/* Special codes used when specifying changer slots. */
DECL|macro|CDSL_NONE
mdefine_line|#define CDSL_NONE       &t;((int) (~0U&gt;&gt;1)-1)
DECL|macro|CDSL_CURRENT
mdefine_line|#define CDSL_CURRENT    &t;((int) (~0U&gt;&gt;1))
macro_line|#ifdef __KERNEL__
multiline_comment|/* Uniform cdrom data structures for cdrom.c */
DECL|struct|cdrom_device_info
r_struct
id|cdrom_device_info
(brace
DECL|member|ops
r_struct
id|cdrom_device_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* link to device_ops */
DECL|member|next
r_struct
id|cdrom_device_info
op_star
id|next
suffix:semicolon
multiline_comment|/* next device_info for this major */
DECL|member|handle
r_void
op_star
id|handle
suffix:semicolon
multiline_comment|/* driver-dependent data */
multiline_comment|/* specifications */
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
multiline_comment|/* device number */
DECL|member|mask
r_int
id|mask
suffix:semicolon
multiline_comment|/* mask of capability: disables them */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* maximum speed for reading data */
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
multiline_comment|/* number of discs in jukebox */
multiline_comment|/* device-related storage */
DECL|member|options
r_int
id|options
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/* options flags */
DECL|member|mc_flags
r_int
id|mc_flags
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* media change buffer flags */
DECL|member|use_count
r_int
id|use_count
suffix:semicolon
multiline_comment|/* number of times device opened */
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* name of the device type */
)brace
suffix:semicolon
DECL|struct|cdrom_device_ops
r_struct
id|cdrom_device_ops
(brace
multiline_comment|/* routines */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
DECL|member|drive_status
r_int
(paren
op_star
id|drive_status
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|media_changed
r_int
(paren
op_star
id|media_changed
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|tray_move
r_int
(paren
op_star
id|tray_move
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|lock_door
r_int
(paren
op_star
id|lock_door
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|select_speed
r_int
(paren
op_star
id|select_speed
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|select_disc
r_int
(paren
op_star
id|select_disc
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|get_last_session
r_int
(paren
op_star
id|get_last_session
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_multisession
op_star
)paren
suffix:semicolon
DECL|member|get_mcn
r_int
(paren
op_star
id|get_mcn
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_mcn
op_star
)paren
suffix:semicolon
multiline_comment|/* hard reset device */
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
multiline_comment|/* play stuff */
DECL|member|audio_ioctl
r_int
(paren
op_star
id|audio_ioctl
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* dev-specific */
DECL|member|dev_ioctl
r_int
(paren
op_star
id|dev_ioctl
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* driver specifications */
DECL|member|capability
r_const
r_int
id|capability
suffix:semicolon
multiline_comment|/* capability flags */
DECL|member|n_minors
r_int
id|n_minors
suffix:semicolon
multiline_comment|/* number of active minor devices */
)brace
suffix:semicolon
multiline_comment|/* the general file operations structure: */
r_extern
r_struct
id|file_operations
id|cdrom_fops
suffix:semicolon
r_extern
r_int
id|register_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
r_extern
r_int
id|unregister_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
macro_line|#endif  /* End of kernel only stuff */ 
macro_line|#endif  _LINUX_CDROM_H
eof
