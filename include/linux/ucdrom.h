multiline_comment|/* ucdrom.h. Uniform cdrom data structures for cdrom.c. &t;-*- linux-c -*-&n;   Copyright (c) 1996 David van Leeuwen. &n; */
macro_line|#ifndef LINUX_UCDROM_H
DECL|macro|LINUX_UCDROM_H
mdefine_line|#define LINUX_UCDROM_H
macro_line|#ifdef __KERNEL__
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
DECL|member|disc_status
r_int
(paren
op_star
id|disc_status
)paren
(paren
r_struct
id|cdrom_device_info
op_star
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
macro_line|#endif
multiline_comment|/* capability flags */
DECL|macro|CDC_CLOSE_TRAY
mdefine_line|#define CDC_CLOSE_TRAY&t;0x1             /* caddy systems _can&squot;t_ close */
DECL|macro|CDC_OPEN_TRAY
mdefine_line|#define CDC_OPEN_TRAY&t;0x2             /* but _can_ eject.  */
DECL|macro|CDC_LOCK
mdefine_line|#define CDC_LOCK&t;0x4             /* disable manual eject */
DECL|macro|CDC_SELECT_SPEED
mdefine_line|#define CDC_SELECT_SPEED 0x8            /* programmable speed */
DECL|macro|CDC_SELECT_DISC
mdefine_line|#define CDC_SELECT_DISC&t;0x10            /* select disc from juke-box */
DECL|macro|CDC_MULTI_SESSION
mdefine_line|#define CDC_MULTI_SESSION 0x20          /* read sessions&gt;1 */
DECL|macro|CDC_MCN
mdefine_line|#define CDC_MCN&t;&t;0x40            /* Medium Catalog Number */
DECL|macro|CDC_MEDIA_CHANGED
mdefine_line|#define CDC_MEDIA_CHANGED 0x80          /* media changed */
DECL|macro|CDC_PLAY_AUDIO
mdefine_line|#define CDC_PLAY_AUDIO&t;0x100           /* audio functions */
multiline_comment|/* drive status possibilities */
DECL|macro|CDS_NO_INFO
mdefine_line|#define CDS_NO_INFO&t;0               /* if not implemented */
DECL|macro|CDS_NO_DISC
mdefine_line|#define CDS_NO_DISC&t;1
DECL|macro|CDS_TRAY_OPEN
mdefine_line|#define CDS_TRAY_OPEN&t;2
DECL|macro|CDS_DRIVE_NOT_READY
mdefine_line|#define CDS_DRIVE_NOT_READY&t;3
DECL|macro|CDS_DISC_OK
mdefine_line|#define CDS_DISC_OK&t;4
multiline_comment|/* disc status possibilities, other than CDS_NO_DISC */
DECL|macro|CDS_AUDIO
mdefine_line|#define CDS_AUDIO&t;100
DECL|macro|CDS_DATA_1
mdefine_line|#define CDS_DATA_1&t;101
DECL|macro|CDS_DATA_2
mdefine_line|#define CDS_DATA_2&t;102
DECL|macro|CDS_XA_2_1
mdefine_line|#define CDS_XA_2_1&t;103
DECL|macro|CDS_XA_2_2
mdefine_line|#define CDS_XA_2_2&t;104
multiline_comment|/* User-configurable behavior options */
DECL|macro|CDO_AUTO_CLOSE
mdefine_line|#define CDO_AUTO_CLOSE&t;0x1             /* close tray on first open() */
DECL|macro|CDO_AUTO_EJECT
mdefine_line|#define CDO_AUTO_EJECT&t;0x2             /* open tray on last release() */
DECL|macro|CDO_USE_FFLAGS
mdefine_line|#define CDO_USE_FFLAGS&t;0x4             /* use O_NONBLOCK information on open */
DECL|macro|CDO_LOCK
mdefine_line|#define CDO_LOCK&t;0x8             /* lock tray on open files */
DECL|macro|CDO_CHECK_TYPE
mdefine_line|#define CDO_CHECK_TYPE&t;0x10            /* check type on open for data */
multiline_comment|/* Special codes for specifying changer slots. */
DECL|macro|CDSL_NONE
mdefine_line|#define CDSL_NONE       ((int) (~0U&gt;&gt;1)-1)
DECL|macro|CDSL_CURRENT
mdefine_line|#define CDSL_CURRENT    ((int) (~0U&gt;&gt;1))
multiline_comment|/* Some more ioctls to control these options */
DECL|macro|CDROM_SET_OPTIONS
mdefine_line|#define CDROM_SET_OPTIONS&t;0x5320
DECL|macro|CDROM_CLEAR_OPTIONS
mdefine_line|#define CDROM_CLEAR_OPTIONS&t;0x5321
DECL|macro|CDROM_SELECT_SPEED
mdefine_line|#define CDROM_SELECT_SPEED&t;0x5322  /* head-speed */
DECL|macro|CDROM_SELECT_DISC
mdefine_line|#define CDROM_SELECT_DISC&t;0x5323  /* for juke-boxes */
DECL|macro|CDROM_MEDIA_CHANGED
mdefine_line|#define CDROM_MEDIA_CHANGED&t;0x5325
DECL|macro|CDROM_DRIVE_STATUS
mdefine_line|#define CDROM_DRIVE_STATUS&t;0x5326  /* tray position, etc. */
DECL|macro|CDROM_DISC_STATUS
mdefine_line|#define CDROM_DISC_STATUS&t;0x5327  /* disc type etc. */
DECL|macro|CDROM_CHANGER_NSLOTS
mdefine_line|#define CDROM_CHANGER_NSLOTS    0x5328
multiline_comment|/* Rename an old ioctl */
DECL|macro|CDROM_GET_MCN
mdefine_line|#define CDROM_GET_MCN&t;CDROM_GET_UPC&t;/* medium catalog number */
macro_line|#ifdef __KERNEL__
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
comma
r_char
op_star
id|name
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
macro_line|#endif
macro_line|#endif&t;/* LINUX_UCDROM_H */
multiline_comment|/*&n; * Local variables:&n; * comment-column: 40&n; * End:&n; */
eof
