multiline_comment|/****************************************************************************************&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; * general (not only SCSI) header library for linux CDROM drivers                       *&n; * (C) 1992 David Giller rafetmad@oxy.edu&t;&t;&t;&t;&t;&t;*&n; *     1994 Eberhard Moenkeberg emoenke@gwdg.de (&quot;read audio&quot; and some other stuff)&t;*&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; * &lt;linux/cdrom.h&gt; -- CD-ROM IOCTLs and structs&t;&t; &t;&t;&t;&t;*&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; ****************************************************************************************/
macro_line|#ifndef&t;_LINUX_CDROM_H
DECL|macro|_LINUX_CDROM_H
mdefine_line|#define&t;_LINUX_CDROM_H
multiline_comment|/*&n; * some fix numbers&n; */
DECL|macro|CD_MINS
mdefine_line|#define CD_MINS                   74  /* max. minutes per CD             */
DECL|macro|CD_SECS
mdefine_line|#define CD_SECS                   60  /* seconds per minute              */
DECL|macro|CD_FRAMES
mdefine_line|#define CD_FRAMES                 75  /* frames per second               */
DECL|macro|CD_CHUNK_SIZE
mdefine_line|#define CD_CHUNK_SIZE             24  /* lowest-level &quot;data bytes piece&quot; */
DECL|macro|CD_NUM_OF_CHUNKS
mdefine_line|#define CD_NUM_OF_CHUNKS          98  /* chunks per frame                */
DECL|macro|CD_FRAMESIZE
mdefine_line|#define CD_FRAMESIZE            2048  /* bytes per frame, cooked mode    */
DECL|macro|CD_FRAMESIZE_RAW0
mdefine_line|#define CD_FRAMESIZE_RAW0       2336  /* bytes per frame, &quot;raw&quot; mode     */
DECL|macro|CD_FRAMESIZE_XA
mdefine_line|#define CD_FRAMESIZE_XA         2340  /* bytes per frame, &quot;xa&quot; mode      */
DECL|macro|CD_FRAMESIZE_RAW
mdefine_line|#define CD_FRAMESIZE_RAW        2352  /* bytes per frame, &quot;raw&quot; mode     */
DECL|macro|CD_FRAMESIZE_SUB
mdefine_line|#define CD_FRAMESIZE_SUB          96  /* subchannel data size            */
DECL|macro|CD_BLOCK_OFFSET
mdefine_line|#define CD_BLOCK_OFFSET          150  /* offset of first logical frame   */
DECL|macro|CD_XA_HEAD
mdefine_line|#define CD_XA_HEAD                12  /* header size of XA frame         */
DECL|macro|CD_XA_TAIL
mdefine_line|#define CD_XA_TAIL               280  /* tail size of XA frame           */
multiline_comment|/*&n; *&n; * For IOCTL calls, we will commandeer byte 0x53, or &squot;S&squot;.&n; *&n; */
multiline_comment|/*&n; * CD-ROM-specific SCSI command opcodes&n; */
multiline_comment|/*&n; * Group 2 (10-byte).  All of these are called &squot;optional&squot; by SCSI-II.&n; */
DECL|macro|SCMD_READ_TOC
mdefine_line|#define&t;SCMD_READ_TOC&t;&t;0x43&t;&t;/* read table of contents&t;*/
DECL|macro|SCMD_PLAYAUDIO_MSF
mdefine_line|#define&t;SCMD_PLAYAUDIO_MSF&t;0x47&t;&t;/* play data at time offset&t;*/
DECL|macro|SCMD_PLAYAUDIO_TI
mdefine_line|#define&t;SCMD_PLAYAUDIO_TI&t;0x48&t;&t;/* play data at track/index&t;*/
DECL|macro|SCMD_PAUSE_RESUME
mdefine_line|#define&t;SCMD_PAUSE_RESUME&t;0x4B&t;&t;/* pause/resume audio&t;&t;*/
DECL|macro|SCMD_READ_SUBCHANNEL
mdefine_line|#define&t;SCMD_READ_SUBCHANNEL&t;0x42&t;&t;/* read SC info on playing disc */
DECL|macro|SCMD_PLAYAUDIO10
mdefine_line|#define&t;SCMD_PLAYAUDIO10&t;0x45&t;&t;/* play data at logical block&t;*/
DECL|macro|SCMD_READ_HEADER
mdefine_line|#define&t;SCMD_READ_HEADER&t;0x44&t;&t;/* read TOC header&t;&t;*/
multiline_comment|/*&n; * Group 5&n; */
DECL|macro|SCMD_PLAYAUDIO12
mdefine_line|#define&t;SCMD_PLAYAUDIO12&t;0xA5 &t;&t;/* play data at logical block&t;*/
DECL|macro|SCMD_PLAYTRACK_REL12
mdefine_line|#define&t;SCMD_PLAYTRACK_REL12&t;0xA9&t;&t;/* play track at relative offset*/
multiline_comment|/*&n; * Group 6 Commands&n; */
DECL|macro|SCMD_CD_PLAYBACK_CONTROL
mdefine_line|#define&t;SCMD_CD_PLAYBACK_CONTROL 0xC9&t;&t;/* Sony vendor-specific audio&t;*/
DECL|macro|SCMD_CD_PLAYBACK_STATUS
mdefine_line|#define&t;SCMD_CD_PLAYBACK_STATUS 0xC4&t;&t;/* control opcodes. info please!*/
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
mdefine_line|#define&t;ERR_RECOVERY_PARMS&t;0x01
DECL|macro|DISCO_RECO_PARMS
mdefine_line|#define&t;DISCO_RECO_PARMS&t;0x02
DECL|macro|FORMAT_PARMS
mdefine_line|#define&t;FORMAT_PARMS&t;&t;0x03
DECL|macro|GEOMETRY_PARMS
mdefine_line|#define&t;GEOMETRY_PARMS&t;&t;0x04
DECL|macro|CERTIFICATION_PARMS
mdefine_line|#define&t;CERTIFICATION_PARMS&t;0x06
DECL|macro|CACHE_PARMS
mdefine_line|#define&t;CACHE_PARMS&t;&t;0x38
multiline_comment|/*&n; * standard mode-select header prepended to all mode-select commands&n; */
DECL|struct|ccs_modesel_head
r_struct
id|ccs_modesel_head
(brace
DECL|member|_r1
id|u_char
id|_r1
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|medium
id|u_char
id|medium
suffix:semicolon
multiline_comment|/* device-specific medium type &t;&t;*/
DECL|member|_r2
id|u_char
id|_r2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|block_desc_length
id|u_char
id|block_desc_length
suffix:semicolon
multiline_comment|/* block descriptor length &t;&t;*/
DECL|member|density
id|u_char
id|density
suffix:semicolon
multiline_comment|/* device-specific density code&t;&t;*/
DECL|member|number_blocks_hi
id|u_char
id|number_blocks_hi
suffix:semicolon
multiline_comment|/* number of blocks in this block desc&t;*/
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
multiline_comment|/* block length for blocks in this desc&t;*/
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
multiline_comment|/* reserved &t;&t;&t;&t;*/
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code &t;&t;&t;&t;*/
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length&t;&t; &t;&t;*/
DECL|member|awre
id|u_char
id|awre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auto write realloc enabled &t;&t;*/
DECL|member|arre
id|u_char
id|arre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auto read realloc enabled &t;&t;*/
DECL|member|tb
id|u_char
id|tb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* transfer block &t;&t;&t;*/
DECL|member|rc
id|u_char
id|rc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* read continuous &t;&t;&t;*/
DECL|member|eec
id|u_char
id|eec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* enable early correction &t;&t;*/
DECL|member|per
id|u_char
id|per
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* post error &t;&t;&t;&t;*/
DECL|member|dte
id|u_char
id|dte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable transfer on error &t;&t;*/
DECL|member|dcr
id|u_char
id|dcr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disable correction &t;&t;&t;*/
DECL|member|retry_count
id|u_char
id|retry_count
suffix:semicolon
multiline_comment|/* error retry count&t;&t;&t;*/
DECL|member|correction_span
id|u_char
id|correction_span
suffix:semicolon
multiline_comment|/* largest recov. to be attempted, bits&t;*/
DECL|member|head_offset_count
id|u_char
id|head_offset_count
suffix:semicolon
multiline_comment|/* head offset (2&squot;s C) for each retry&t;*/
DECL|member|strobe_offset_count
id|u_char
id|strobe_offset_count
suffix:semicolon
multiline_comment|/* data strobe &quot;&t;&t;&t;*/
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
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code&t;&t; &t;&t;*/
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length&t;&t;&t;&t;*/
DECL|member|buffer_full_ratio
id|u_char
id|buffer_full_ratio
suffix:semicolon
multiline_comment|/* write buffer reconnect threshold&t;*/
DECL|member|buffer_empty_ratio
id|u_char
id|buffer_empty_ratio
suffix:semicolon
multiline_comment|/* read &quot;&t;&t;&t;&t;*/
DECL|member|bus_inactivity_limit
id|u_short
id|bus_inactivity_limit
suffix:semicolon
multiline_comment|/* limit on bus inactivity time&t;&t;*/
DECL|member|disconnect_time_limit
id|u_short
id|disconnect_time_limit
suffix:semicolon
multiline_comment|/* minimum disconnect time&t;&t;*/
DECL|member|connect_time_limit
id|u_short
id|connect_time_limit
suffix:semicolon
multiline_comment|/* minimum connect time&t;&t;&t;*/
DECL|member|_r2
id|u_short
id|_r2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;&t;*/
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
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code&t;&t;&t;&t;*/
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length&t;&t;&t;&t;*/
DECL|member|cyl_ub
id|u_char
id|cyl_ub
suffix:semicolon
multiline_comment|/* #cyls&t;&t;&t;&t;*/
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
multiline_comment|/* #heads&t;&t;&t;&t;*/
DECL|member|precomp_cyl_ub
id|u_char
id|precomp_cyl_ub
suffix:semicolon
multiline_comment|/* precomp start&t;&t;&t;*/
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
multiline_comment|/* reduced current start&t;&t;*/
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
multiline_comment|/* stepping motor rate&t;&t;&t;*/
DECL|member|landing_cyl_ub
id|u_char
id|landing_cyl_ub
suffix:semicolon
multiline_comment|/* landing zone&t;&t;&t;&t;*/
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
multiline_comment|/* reserved&t;&t;&t;&t;*/
DECL|member|page_code
id|u_char
id|page_code
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* page code&t;&t;&t;&t;*/
DECL|member|page_length
id|u_char
id|page_length
suffix:semicolon
multiline_comment|/* page length&t;&t;&t;&t;*/
DECL|member|mode
id|u_char
id|mode
suffix:semicolon
multiline_comment|/* cache control byte&t;&t;&t;*/
DECL|member|threshold
id|u_char
id|threshold
suffix:semicolon
multiline_comment|/* prefetch threshold&t;&t;&t;*/
DECL|member|max_prefetch
id|u_char
id|max_prefetch
suffix:semicolon
multiline_comment|/* maximum prefetch size&t;&t;*/
DECL|member|max_multiplier
id|u_char
id|max_multiplier
suffix:semicolon
multiline_comment|/* maximum prefetch multiplier &t;&t;*/
DECL|member|min_prefetch
id|u_char
id|min_prefetch
suffix:semicolon
multiline_comment|/* minimum prefetch size&t;&t;*/
DECL|member|min_multiplier
id|u_char
id|min_multiplier
suffix:semicolon
multiline_comment|/* minimum prefetch multiplier &t;&t;*/
DECL|member|_r2
id|u_char
id|_r2
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * CDROM IOCTL structures&n; */
DECL|struct|cdrom_msf
r_struct
id|cdrom_msf
(brace
DECL|member|cdmsf_min0
id|u_char
id|cdmsf_min0
suffix:semicolon
multiline_comment|/* start minute &t;&t;&t;*/
DECL|member|cdmsf_sec0
id|u_char
id|cdmsf_sec0
suffix:semicolon
multiline_comment|/* start second &t;&t;&t;*/
DECL|member|cdmsf_frame0
id|u_char
id|cdmsf_frame0
suffix:semicolon
multiline_comment|/* start frame  &t;&t;&t;*/
DECL|member|cdmsf_min1
id|u_char
id|cdmsf_min1
suffix:semicolon
multiline_comment|/* end minute   &t;&t;&t;*/
DECL|member|cdmsf_sec1
id|u_char
id|cdmsf_sec1
suffix:semicolon
multiline_comment|/* end second   &t;&t;&t;*/
DECL|member|cdmsf_frame1
id|u_char
id|cdmsf_frame1
suffix:semicolon
multiline_comment|/* end frame&t;   &t;&t;&t;*/
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
multiline_comment|/* start track &t;&t;&t;&t;*/
DECL|member|cdti_ind0
id|u_char
id|cdti_ind0
suffix:semicolon
multiline_comment|/* start index &t;&t;&t;&t;*/
DECL|member|cdti_trk1
id|u_char
id|cdti_trk1
suffix:semicolon
multiline_comment|/* end track &t;&t;&t;&t;*/
DECL|member|cdti_ind1
id|u_char
id|cdti_ind1
suffix:semicolon
multiline_comment|/* end index &t;&t;&t;&t;*/
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
multiline_comment|/* start track &t;&t;&t;&t;*/
DECL|member|cdth_trk1
id|u_char
id|cdth_trk1
suffix:semicolon
multiline_comment|/* end track &t;&t;&t;&t;*/
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
r_union
(brace
r_struct
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
DECL|member|msf
)brace
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|cdte_addr
)brace
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
multiline_comment|/*&n; * bit to tell whether track is data or audio&n; */
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
r_union
(brace
r_struct
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
DECL|member|msf
)brace
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|cdsc_absaddr
)brace
id|cdsc_absaddr
suffix:semicolon
r_union
(brace
r_struct
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
DECL|member|msf
)brace
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|cdsc_reladdr
)brace
id|cdsc_reladdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * return value from READ SUBCHANNEL DATA&n; */
DECL|macro|CDROM_AUDIO_INVALID
mdefine_line|#define&t;CDROM_AUDIO_INVALID&t;0x00&t;/* audio status not supported &t;&t;*/
DECL|macro|CDROM_AUDIO_PLAY
mdefine_line|#define&t;CDROM_AUDIO_PLAY&t;0x11&t;/* audio play operation in progress &t;*/
DECL|macro|CDROM_AUDIO_PAUSED
mdefine_line|#define&t;CDROM_AUDIO_PAUSED&t;0x12&t;/* audio play operation paused &t;&t;*/
DECL|macro|CDROM_AUDIO_COMPLETED
mdefine_line|#define&t;CDROM_AUDIO_COMPLETED&t;0x13&t;/* audio play successfully completed &t;*/
DECL|macro|CDROM_AUDIO_ERROR
mdefine_line|#define&t;CDROM_AUDIO_ERROR&t;0x14&t;/* audio play stopped due to error &t;*/
DECL|macro|CDROM_AUDIO_NO_STATUS
mdefine_line|#define&t;CDROM_AUDIO_NO_STATUS&t;0x15&t;/* no current audio status to return &t;*/
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
multiline_comment|/*&n; * preliminary extensions for transferring audio frames&n; * currently used by sbpcd.c&n; * (still may change if other drivers will use it, too):&n; */
DECL|struct|cdrom_read_audio
r_struct
id|cdrom_read_audio
(brace
r_union
(brace
r_struct
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
DECL|member|msf
)brace
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|addr
)brace
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
macro_line|#ifdef FIVETWELVE
DECL|macro|CDROM_MODE1_SIZE
mdefine_line|#define&t;CDROM_MODE1_SIZE&t;512
macro_line|#else
DECL|macro|CDROM_MODE1_SIZE
mdefine_line|#define&t;CDROM_MODE1_SIZE&t;2048
macro_line|#endif FIVETWELVE
DECL|macro|CDROM_MODE2_SIZE
mdefine_line|#define&t;CDROM_MODE2_SIZE&t;2336
multiline_comment|/*&n; * CD-ROM IOCTL commands&n; */
DECL|macro|CDROMPAUSE
mdefine_line|#define&t;CDROMPAUSE&t;&t;0x5301&t;&t;/* pause&t;&t;&t;*/
DECL|macro|CDROMRESUME
mdefine_line|#define&t;CDROMRESUME&t;&t;0x5302&t;&t;/* resume&t;&t;&t;*/
DECL|macro|CDROMPLAYMSF
mdefine_line|#define&t;CDROMPLAYMSF&t;&t;0x5303&t;&t;/* (struct cdrom_msf)&t;&t;*/
multiline_comment|/* SCMD_PLAY_AUDIO_MSF&t;&t;*/
DECL|macro|CDROMPLAYTRKIND
mdefine_line|#define&t;CDROMPLAYTRKIND&t;&t;0x5304&t;&t;/* (struct cdrom_ti)&t;&t;*/
multiline_comment|/* SCMD_PLAY_AUDIO_TI&t;&t;*/
DECL|macro|CDROMREADTOCHDR
mdefine_line|#define&t;CDROMREADTOCHDR&t;&t;0x5305&t;&t;/* (struct cdrom_tochdr)&t;*/
multiline_comment|/* read the TOC header&t;&t;*/
DECL|macro|CDROMREADTOCENTRY
mdefine_line|#define&t;CDROMREADTOCENTRY&t;0x5306&t;&t;/* (struct cdrom_tocentry)&t;*/
multiline_comment|/* read a TOC entry&t;&t;*/
DECL|macro|CDROMSTOP
mdefine_line|#define&t;CDROMSTOP&t;&t;0x5307&t;&t;/* stop the drive motor&t;&t;*/
DECL|macro|CDROMSTART
mdefine_line|#define&t;CDROMSTART&t;&t;0x5308&t;&t;/* turn the motor on &t;&t;*/
DECL|macro|CDROMEJECT
mdefine_line|#define&t;CDROMEJECT&t;&t;0x5309&t;&t;/* eject CD-ROM media&t;&t;*/
DECL|macro|CDROMVOLCTRL
mdefine_line|#define&t;CDROMVOLCTRL&t;&t;0x530a&t;&t;/* (struct cdrom_volctrl)&t;*/
multiline_comment|/* volume control&t;&t;*/
DECL|macro|CDROMSUBCHNL
mdefine_line|#define&t;CDROMSUBCHNL&t;&t;0x530b&t;&t;/* (struct cdrom_subchnl)&t;*/
multiline_comment|/* read Q sub-channel data &t;*/
DECL|macro|CDROMREADMODE2
mdefine_line|#define&t;CDROMREADMODE2&t;&t;0x530c&t;&t;/* (struct cdrom_read)&t;&t;*/
multiline_comment|/* read type-2 data (not suppt)&t;*/
DECL|macro|CDROMREADMODE1
mdefine_line|#define&t;CDROMREADMODE1&t;&t;0x530d&t;&t;/* (struct cdrom_read)&t;&t;*/
multiline_comment|/* read type-1 data &t;&t;*/
multiline_comment|/*&n; * preliminary extension for transferring audio frames&n; * currently used by sbpcd.c&n; * (still may change if other drivers will use it, too):&n; */
DECL|macro|CDROMREADAUDIO
mdefine_line|#define&t;CDROMREADAUDIO&t;&t;0x530e&t;&t;/* (struct cdrom_read_audio)&t;*/
macro_line|#endif  _LINUX_CDROM_H
eof
