multiline_comment|/*&n; * sbpcd.h   Specify interface address and interface type here.&n; */
multiline_comment|/*&n; * the definitions for the first controller can get overridden by&n; * the kernel command line (&quot;lilo boot option&quot;).&n; * Examples:&n; *                                 sbpcd=0x230,SoundBlaster&n; *                             or&n; *                                 sbpcd=0x300,LaserMate&n; *                             or&n; *                                 sbpcd=0x330,SPEA&n; *&n; * These strings are case sensitive !!!&n; */
multiline_comment|/*&n; * put your CDROM port base address into CDROM_PORT&n; * and specify the type of your interface in SBPRO.&n; *&n; * SBPRO addresses typically are 0x0230 (=0x220+0x10), 0x0250, ...&n; * LASERMATE (CI-101P, WDH-7001C) addresses typically are 0x0300, 0x0310, ...&n; * SPEA addresses are 0x320, 0x330, 0x340, 0x350&n; * there are some soundcards on the market with 0x0630, 0x0650, ...&n; *&n; * example: if your SBPRO audio address is 0x220, specify 0x230.&n; *&n; *&n; * set SBPRO to 1 for &quot;true&quot; SoundBlaster card&n; * set SBPRO to 0 for &quot;poor&quot; (no sound) interface cards&n; *                and for &quot;compatible&quot; soundcards.&n; * set SBPRO to 2 for the SPEA Media FX card&n; *&n; * most &quot;compatible&quot; sound boards like Galaxy need to set SBPRO to 0 !!!&n; * if SBPRO gets set wrong, the drive will get found - but any&n; * data access will give errors (audio access will work).&n; * The OmniCD interface card from CreativeLabs needs SBPRO 1.&n; *&n; * mail to emoenke@gwdg.de if your &quot;compatible&quot; card needs SBPRO 1&n; * (currently I do not know any &quot;compatible&quot; with SBPRO 1)&n; * then I can include better information with the next release.&n; */
macro_line|#if !(SBPCD_ISSUE-1) /* first (or if you have only one) interface board: */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x0340
DECL|macro|SBPRO
mdefine_line|#define SBPRO     0
macro_line|#endif
multiline_comment|/*&n; * If you have a &quot;compatible&quot; soundcard of type &quot;SBPRO 0&quot; or &quot;SBPRO 2&quot;,&n; * enter your sound card&squot;s base address here if you want sbpcd to turn&n; * the CD sound channels on.&n; *&n; * Example: #define SOUND_BASE 0x220 enables the sound card&squot;s CD channels&n; *          #define SOUND_BASE 0     leaves the soundcard untouched&n; */
DECL|macro|SOUND_BASE
mdefine_line|#define SOUND_BASE 0x220
multiline_comment|/* ignore the rest if you have only one interface board &amp; driver */
macro_line|#if !(SBPCD_ISSUE-2) /* second interface board: */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x0370
DECL|macro|SBPRO
mdefine_line|#define SBPRO     0
macro_line|#endif
macro_line|#if !(SBPCD_ISSUE-3) /* third interface board: */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x0330
DECL|macro|SBPRO
mdefine_line|#define SBPRO     0
macro_line|#endif
macro_line|#if !(SBPCD_ISSUE-4) /* fourth interface board: */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x0230
DECL|macro|SBPRO
mdefine_line|#define SBPRO     1
macro_line|#endif
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * nothing to change below here if you are not experimenting&n; */
macro_line|#ifndef _LINUX_SBPCD_H
DECL|macro|_LINUX_SBPCD_H
mdefine_line|#define _LINUX_SBPCD_H
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * DDI interface definitions&n; * &quot;invented&quot; by Fred N. van Kempen..&n; */
DECL|macro|DDIOCSDBG
mdefine_line|#define DDIOCSDBG&t;0x9000
DECL|macro|DPRINTF
mdefine_line|#define DPRINTF(x)&t;sbpcd_dprintf x
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * Debug output levels&n; */
DECL|macro|DBG_INF
mdefine_line|#define DBG_INF&t;&t;1&t;/* necessary information */
DECL|macro|DBG_BSZ
mdefine_line|#define DBG_BSZ&t;&t;2&t;/* BLOCK_SIZE trace */
DECL|macro|DBG_REA
mdefine_line|#define DBG_REA&t;&t;3&t;/* &quot;read&quot; status trace */
DECL|macro|DBG_CHK
mdefine_line|#define DBG_CHK&t;&t;4&t;/* &quot;media check&quot; trace */
DECL|macro|DBG_TIM
mdefine_line|#define DBG_TIM&t;&t;5&t;/* datarate timer test */
DECL|macro|DBG_INI
mdefine_line|#define DBG_INI&t;&t;6&t;/* initialization trace */
DECL|macro|DBG_TOC
mdefine_line|#define DBG_TOC&t;&t;7&t;/* tell TocEntry values */
DECL|macro|DBG_IOC
mdefine_line|#define DBG_IOC         8&t;/* ioctl trace */
DECL|macro|DBG_STA
mdefine_line|#define DBG_STA&t;&t;9&t;/* &quot;ResponseStatus&quot; trace */
DECL|macro|DBG_ERR
mdefine_line|#define DBG_ERR&t;&t;10&t;/* &quot;xx_ReadError&quot; trace */
DECL|macro|DBG_CMD
mdefine_line|#define DBG_CMD&t;&t;11&t;/* &quot;cmd_out&quot; trace */
DECL|macro|DBG_WRN
mdefine_line|#define DBG_WRN&t;&t;12&t;/* give explanation before auto-probing */
DECL|macro|DBG_MUL
mdefine_line|#define DBG_MUL         13      /* multi session code test */
DECL|macro|DBG_ID
mdefine_line|#define DBG_ID&t;&t;14&t;/* &quot;drive_id !=0&quot; test code */
DECL|macro|DBG_IOX
mdefine_line|#define DBG_IOX&t;&t;15&t;/* some special information */
DECL|macro|DBG_DID
mdefine_line|#define DBG_DID&t;&t;16&t;/* drive ID test */
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES&t;&t;17&t;/* drive reset info */
DECL|macro|DBG_SPI
mdefine_line|#define DBG_SPI&t;&t;18&t;/* SpinUp test */
DECL|macro|DBG_IOS
mdefine_line|#define DBG_IOS&t;&t;19&t;/* ioctl trace: &quot;subchannel&quot; */
DECL|macro|DBG_IO2
mdefine_line|#define DBG_IO2&t;&t;20&t;/* ioctl trace: general */
DECL|macro|DBG_UPC
mdefine_line|#define DBG_UPC&t;&t;21&t;/* show UPC information */
DECL|macro|DBG_XA
mdefine_line|#define DBG_XA &t;&t;22&t;/* XA mode debugging */
DECL|macro|DBG_LCK
mdefine_line|#define DBG_LCK&t;&t;23&t;/* door (un)lock info */
DECL|macro|DBG_SQ
mdefine_line|#define DBG_SQ &t;&t;24&t;/* dump SubQ frame */
DECL|macro|DBG_AUD
mdefine_line|#define DBG_AUD&t;&t;25      /* &quot;read audio&quot; debugging */
DECL|macro|DBG_SEQ
mdefine_line|#define DBG_SEQ&t;&t;26      /* Sequoia interface configuration trace */
DECL|macro|DBG_LCS
mdefine_line|#define DBG_LCS&t;&t;27      /* Longshine LCS-7260 debugging trace */
DECL|macro|DBG_TEA
mdefine_line|#define DBG_TEA&t;&t;28      /* TEAC CD-55A debugging trace */
DECL|macro|DBG_CD2
mdefine_line|#define DBG_CD2&t;&t;29      /* MKE CD200 debugging trace */
DECL|macro|DBG_000
mdefine_line|#define DBG_000&t;&t;30      /* unnecessary information */
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * bits of flags_cmd_out:&n; */
DECL|macro|f_respo3
mdefine_line|#define f_respo3&t;&t;0x100
DECL|macro|f_putcmd
mdefine_line|#define f_putcmd&t;&t;0x80
DECL|macro|f_respo2
mdefine_line|#define f_respo2&t;&t;0x40
DECL|macro|f_lopsta
mdefine_line|#define f_lopsta&t;&t;0x20
DECL|macro|f_getsta
mdefine_line|#define f_getsta&t;&t;0x10
DECL|macro|f_ResponseStatus
mdefine_line|#define f_ResponseStatus&t;0x08
DECL|macro|f_obey_p_check
mdefine_line|#define f_obey_p_check&t;&t;0x04
DECL|macro|f_bit1
mdefine_line|#define f_bit1&t;&t;&t;0x02
DECL|macro|f_wait_if_busy
mdefine_line|#define f_wait_if_busy&t;&t;0x01
multiline_comment|/*&n; * diskstate_flags:&n; */
DECL|macro|x80_bit
mdefine_line|#define x80_bit&t;&t;&t;0x80
DECL|macro|upc_bit
mdefine_line|#define upc_bit&t;&t;&t;0x40
DECL|macro|volume_bit
mdefine_line|#define volume_bit&t;&t;0x20
DECL|macro|toc_bit
mdefine_line|#define toc_bit&t;&t;&t;0x10
DECL|macro|multisession_bit
mdefine_line|#define multisession_bit&t;0x08
DECL|macro|cd_size_bit
mdefine_line|#define cd_size_bit&t;&t;0x04
DECL|macro|subq_bit
mdefine_line|#define subq_bit&t;&t;0x02
DECL|macro|frame_size_bit
mdefine_line|#define frame_size_bit&t;&t;0x01
multiline_comment|/*&n; * disk states (bits of diskstate_flags):&n; */
DECL|macro|upc_valid
mdefine_line|#define upc_valid (DriveStruct[d].diskstate_flags&amp;upc_bit)
DECL|macro|volume_valid
mdefine_line|#define volume_valid (DriveStruct[d].diskstate_flags&amp;volume_bit)
DECL|macro|toc_valid
mdefine_line|#define toc_valid (DriveStruct[d].diskstate_flags&amp;toc_bit)
DECL|macro|cd_size_valid
mdefine_line|#define cd_size_valid (DriveStruct[d].diskstate_flags&amp;cd_size_bit)
DECL|macro|subq_valid
mdefine_line|#define subq_valid (DriveStruct[d].diskstate_flags&amp;subq_bit)
DECL|macro|frame_size_valid
mdefine_line|#define frame_size_valid (DriveStruct[d].diskstate_flags&amp;frame_size_bit)
multiline_comment|/*&n; * bits of the status_byte (result of xx_ReadStatus):&n; */
DECL|macro|p_door_closed
mdefine_line|#define p_door_closed 0x80
DECL|macro|p_caddy_in
mdefine_line|#define p_caddy_in 0x40
DECL|macro|p_spinning
mdefine_line|#define p_spinning 0x20
DECL|macro|p_check
mdefine_line|#define p_check 0x10
DECL|macro|p_busy_new
mdefine_line|#define p_busy_new 0x08
DECL|macro|p_door_locked
mdefine_line|#define p_door_locked 0x04
DECL|macro|p_bit_1
mdefine_line|#define p_bit_1 0x02 /* hopefully unused now */
DECL|macro|p_lcs_door_locked
mdefine_line|#define p_lcs_door_locked 0x02 /* new use of old bit */
DECL|macro|p_disk_ok
mdefine_line|#define p_disk_ok 0x01
DECL|macro|p_lcs_door_closed
mdefine_line|#define p_lcs_door_closed 0x01 /* new use of old bit */
multiline_comment|/*&n; * &quot;old&quot; drives status result bits:&n; */
DECL|macro|p_caddin_old
mdefine_line|#define p_caddin_old 0x40
DECL|macro|p_success_old
mdefine_line|#define p_success_old 0x08
DECL|macro|p_busy_old
mdefine_line|#define p_busy_old 0x04
multiline_comment|/*&n; * &quot;generation specific&quot; defs of the status_byte:&n; */
DECL|macro|p0_door_closed
mdefine_line|#define p0_door_closed&t;0x80
DECL|macro|p0_caddy_in
mdefine_line|#define p0_caddy_in&t;0x40
DECL|macro|p0_spinning
mdefine_line|#define p0_spinning&t;0x20
DECL|macro|p0_check
mdefine_line|#define p0_check&t;0x10
DECL|macro|p0_success
mdefine_line|#define p0_success&t;0x08 /* unused */
DECL|macro|p0_busy
mdefine_line|#define p0_busy&t;&t;0x04
DECL|macro|p0_bit_1
mdefine_line|#define p0_bit_1&t;0x02 /* unused */
DECL|macro|p0_disk_ok
mdefine_line|#define p0_disk_ok&t;0x01
DECL|macro|p1_door_closed
mdefine_line|#define p1_door_closed&t;0x80
DECL|macro|p1_disk_in
mdefine_line|#define p1_disk_in&t;0x40
DECL|macro|p1_spinning
mdefine_line|#define p1_spinning&t;0x20
DECL|macro|p1_check
mdefine_line|#define p1_check&t;0x10
DECL|macro|p1_busy
mdefine_line|#define p1_busy&t;&t;0x08
DECL|macro|p1_door_locked
mdefine_line|#define p1_door_locked&t;0x04
DECL|macro|p1_bit_1
mdefine_line|#define p1_bit_1&t;0x02 /* unused */
DECL|macro|p1_disk_ok
mdefine_line|#define p1_disk_ok&t;0x01
DECL|macro|p2_disk_ok
mdefine_line|#define p2_disk_ok&t;0x80
DECL|macro|p2_door_locked
mdefine_line|#define p2_door_locked&t;0x40
DECL|macro|p2_spinning
mdefine_line|#define p2_spinning&t;0x20
DECL|macro|p2_busy2
mdefine_line|#define p2_busy2&t;0x10
DECL|macro|p2_busy1
mdefine_line|#define p2_busy1&t;0x08
DECL|macro|p2_door_closed
mdefine_line|#define p2_door_closed&t;0x04
DECL|macro|p2_disk_in
mdefine_line|#define p2_disk_in&t;0x02
DECL|macro|p2_check
mdefine_line|#define p2_check&t;0x01
multiline_comment|/*&n; * used drive states:&n; */
DECL|macro|st_door_closed
mdefine_line|#define st_door_closed (DriveStruct[d].status_byte&amp;p_door_closed)
DECL|macro|st_caddy_in
mdefine_line|#define st_caddy_in (DriveStruct[d].status_byte&amp;p_caddy_in)
DECL|macro|st_spinning
mdefine_line|#define st_spinning (DriveStruct[d].status_byte&amp;p_spinning)
DECL|macro|st_check
mdefine_line|#define st_check (DriveStruct[d].status_byte&amp;p_check)
DECL|macro|st_busy
mdefine_line|#define st_busy (DriveStruct[d].status_byte&amp;p_busy_new)
DECL|macro|st_door_locked
mdefine_line|#define st_door_locked (DriveStruct[d].status_byte&amp;p_door_locked)
DECL|macro|st_diskok
mdefine_line|#define st_diskok (DriveStruct[d].status_byte&amp;p_disk_ok)
multiline_comment|/*&n; * bits of the CDi_status register:&n; */
DECL|macro|s_not_result_ready
mdefine_line|#define s_not_result_ready 0x04  /* 0: &quot;result ready&quot; */
DECL|macro|s_not_data_ready
mdefine_line|#define s_not_data_ready 0x02    /* 0: &quot;data ready&quot;   */
DECL|macro|s_attention
mdefine_line|#define s_attention 0x01         /* 1: &quot;attention required&quot; */
multiline_comment|/*&n; * usable as:&n; */
DECL|macro|DRV_ATTN
mdefine_line|#define DRV_ATTN               ((inb(CDi_status)&amp;s_attention)!=0)
DECL|macro|DATA_READY
mdefine_line|#define DATA_READY             ((inb(CDi_status)&amp;s_not_data_ready)==0)
DECL|macro|RESULT_READY
mdefine_line|#define RESULT_READY           ((inb(CDi_status)&amp;s_not_result_ready)==0)
multiline_comment|/*&n; * drive types (firmware versions):&n; */
DECL|macro|drv_fam0
mdefine_line|#define drv_fam0 0x08   /* CR-52x family */
DECL|macro|drv_199
mdefine_line|#define drv_199 (drv_fam0+0x01)    /* &lt;200 */
DECL|macro|drv_200
mdefine_line|#define drv_200 (drv_fam0+0x02)    /* &lt;201 */
DECL|macro|drv_201
mdefine_line|#define drv_201 (drv_fam0+0x03)    /* &lt;210 */
DECL|macro|drv_210
mdefine_line|#define drv_210 (drv_fam0+0x04)    /* &lt;211 */
DECL|macro|drv_211
mdefine_line|#define drv_211 (drv_fam0+0x05)    /* &lt;300 */
DECL|macro|drv_300
mdefine_line|#define drv_300 (drv_fam0+0x06)    /* &gt;=300 */
DECL|macro|drv_famL
mdefine_line|#define drv_famL 0x10    /* Longshine family */
DECL|macro|drv_260
mdefine_line|#define drv_260 (drv_famL+0x01)    /* LCS-7260 */
DECL|macro|drv_fam1
mdefine_line|#define drv_fam1 0x20    /* CR-56x family */
DECL|macro|drv_099
mdefine_line|#define drv_099 (drv_fam1+0x01)    /* &lt;100 */
DECL|macro|drv_100
mdefine_line|#define drv_100 (drv_fam1+0x02)    /* &gt;=100 */
DECL|macro|drv_famT
mdefine_line|#define drv_famT 0x40    /* TEAC CD-55A */
DECL|macro|drv_fam2
mdefine_line|#define drv_fam2 0x80    /* CD200 family */
DECL|macro|fam0_drive
mdefine_line|#define fam0_drive (DriveStruct[d].drv_type&amp;drv_fam0)
DECL|macro|famL_drive
mdefine_line|#define famL_drive (DriveStruct[d].drv_type&amp;drv_famL)
DECL|macro|fam1_drive
mdefine_line|#define fam1_drive (DriveStruct[d].drv_type&amp;drv_fam1)
DECL|macro|famT_drive
mdefine_line|#define famT_drive (DriveStruct[d].drv_type&amp;drv_famT)
DECL|macro|fam2_drive
mdefine_line|#define fam2_drive (DriveStruct[d].drv_type&amp;drv_fam2)
DECL|macro|fam0L_drive
mdefine_line|#define fam0L_drive (DriveStruct[d].drv_type&amp;(drv_fam0|drv_famL))
DECL|macro|fam1L_drive
mdefine_line|#define fam1L_drive (DriveStruct[d].drv_type&amp;(drv_fam1|drv_famL))
DECL|macro|fam01_drive
mdefine_line|#define fam01_drive (DriveStruct[d].drv_type&amp;(drv_fam0|drv_fam1))
multiline_comment|/*&n; * audio states:&n; */
DECL|macro|audio_playing
mdefine_line|#define audio_playing 2
DECL|macro|audio_pausing
mdefine_line|#define audio_pausing 1
multiline_comment|/*&n; * drv_pattern, drv_options:&n; */
DECL|macro|speed_auto
mdefine_line|#define speed_auto&t;0x80
DECL|macro|speed_300
mdefine_line|#define speed_300&t;0x40
DECL|macro|speed_150
mdefine_line|#define speed_150&t;0x20
DECL|macro|audio_mono
mdefine_line|#define audio_mono&t;0x04
multiline_comment|/*&n; * values of cmd_type (0 else):&n; */
DECL|macro|READ_M1
mdefine_line|#define READ_M1  0x01 /* &quot;data mode 1&quot;: 2048 bytes per frame */
DECL|macro|READ_M2
mdefine_line|#define READ_M2  0x02 /* &quot;data mode 2&quot;: 12+2048+280 bytes per frame */
DECL|macro|READ_SC
mdefine_line|#define READ_SC  0x04 /* &quot;subchannel info&quot;: 96 bytes per frame */
DECL|macro|READ_AU
mdefine_line|#define READ_AU  0x08 /* &quot;audio frame&quot;: 2352 bytes per frame */
multiline_comment|/*&n; * sense_byte:&n; *&n; *          values: 00&n; *                  01&n; *                  81&n; *                  82 &quot;raw audio&quot; mode&n; *                  xx from infobuf[0] after 85 00 00 00 00 00 00&n; */
multiline_comment|/* audio status (bin) */
DECL|macro|aud_00
mdefine_line|#define aud_00 0x00 /* Audio status byte not supported or not valid */
DECL|macro|audx11
mdefine_line|#define audx11 0x0b /* Audio play operation in progress             */
DECL|macro|audx12
mdefine_line|#define audx12 0x0c /* Audio play operation paused                  */
DECL|macro|audx13
mdefine_line|#define audx13 0x0d /* Audio play operation successfully completed  */
DECL|macro|audx14
mdefine_line|#define audx14 0x0e /* Audio play operation stopped due to error    */
DECL|macro|audx15
mdefine_line|#define audx15 0x0f /* No current audio status to return            */
multiline_comment|/* audio status (bcd) */
DECL|macro|aud_11
mdefine_line|#define aud_11 0x11 /* Audio play operation in progress             */
DECL|macro|aud_12
mdefine_line|#define aud_12 0x12 /* Audio play operation paused                  */
DECL|macro|aud_13
mdefine_line|#define aud_13 0x13 /* Audio play operation successfully completed  */
DECL|macro|aud_14
mdefine_line|#define aud_14 0x14 /* Audio play operation stopped due to error    */
DECL|macro|aud_15
mdefine_line|#define aud_15 0x15 /* No current audio status to return            */
multiline_comment|/*&n; * highest allowed drive number (MINOR+1)&n; */
DECL|macro|NR_SBPCD
mdefine_line|#define NR_SBPCD 4
multiline_comment|/*&n; * we try to never disable interrupts - seems to work&n; */
DECL|macro|SBPCD_DIS_IRQ
mdefine_line|#define SBPCD_DIS_IRQ 0
multiline_comment|/*&n; * &quot;write byte to port&quot;&n; */
DECL|macro|OUT
mdefine_line|#define OUT(x,y) outb(y,x)
multiline_comment|/*&n; * use &quot;REP INSB&quot; for strobing the data in:&n; */
DECL|macro|READ_DATA
mdefine_line|#define READ_DATA(port, buf, nr) insb(port, buf, nr)
multiline_comment|/*==========================================================================*/
DECL|macro|MIXER_CD_Volume
mdefine_line|#define MIXER_CD_Volume&t;0x28 /* internal SB Pro register address */
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * Creative Labs Programmers did this:&n; */
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS&t;120 /* why more than 99? */
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * To make conversions easier (machine dependent!)&n; */
DECL|union|_msf
r_typedef
r_union
id|_msf
(brace
DECL|member|n
id|u_int
id|n
suffix:semicolon
DECL|member|c
id|u_char
id|c
(braket
l_int|4
)braket
suffix:semicolon
)brace
DECL|typedef|MSF
id|MSF
suffix:semicolon
DECL|union|_blk
r_typedef
r_union
id|_blk
(brace
DECL|member|n
id|u_int
id|n
suffix:semicolon
DECL|member|c
id|u_char
id|c
(braket
l_int|4
)braket
suffix:semicolon
)brace
DECL|typedef|BLK
id|BLK
suffix:semicolon
multiline_comment|/*==========================================================================*/
multiline_comment|/*============================================================================&n;==============================================================================&n;&n;COMMAND SET of &quot;old&quot; drives like CR-521, CR-522&n;               (the CR-562 family is different):&n;&n;No.&t;Command&t;&t;&t;       Code&n;--------------------------------------------&n;&n;Drive Commands:&n; 1&t;Seek&t;&t;&t;&t;01&t;&n; 2&t;Read Data&t;&t;&t;02&n; 3&t;Read XA-Data&t;&t;&t;03&n; 4&t;Read Header&t;&t;&t;04&n; 5&t;Spin Up&t;&t;&t;&t;05&n; 6&t;Spin Down&t;&t;&t;06&n; 7&t;Diagnostic&t;&t;&t;07&n; 8&t;Read UPC&t;&t;&t;08&n; 9&t;Read ISRC&t;&t;&t;09&n;10&t;Play Audio&t;&t;&t;0A&n;11&t;Play Audio MSF&t;&t;&t;0B&n;12&t;Play Audio Track/Index&t;&t;0C&n;&n;Status Commands:&n;13&t;Read Status&t;&t;&t;81&t;&n;14&t;Read Error&t;&t;&t;82&n;15&t;Read Drive Version&t;&t;83&n;16&t;Mode Select&t;&t;&t;84&n;17&t;Mode Sense&t;&t;&t;85&n;18&t;Set XA Parameter&t;&t;86&n;19&t;Read XA Parameter&t;&t;87&n;20&t;Read Capacity&t;&t;&t;88&n;21&t;Read SUB_Q&t;&t;&t;89&n;22&t;Read Disc Code&t;&t;&t;8A&n;23&t;Read Disc Information&t;&t;8B&n;24&t;Read TOC&t;&t;&t;8C&n;25&t;Pause/Resume&t;&t;&t;8D&n;26&t;Read Packet&t;&t;&t;8E&n;27&t;Read Path Check&t;&t;&t;00&n; &n; &n;all numbers (lba, msf-bin, msf-bcd, counts) to transfer high byte first&n;&n;mnemo     7-byte command        #bytes response (r0...rn)&n;________ ____________________  ____ &n;&n;Read Status:&n;status:  81.                    (1)  one-byte command, gives the main&n;                                                          status byte&n;Read Error:&n;check1:  82 00 00 00 00 00 00.  (6)  r1: audio status&n;&n;Read Packet:&n;check2:  8e xx 00 00 00 00 00. (xx)  gets xx bytes response, relating&n;                                        to commands 01 04 05 07 08 09&n;&n;Play Audio:&n;play:    0a ll-bb-aa nn-nn-nn.  (0)  play audio, ll-bb-aa: starting block (lba),&n;                                                 nn-nn-nn: #blocks&n;Play Audio MSF:&n;         0b mm-ss-ff mm-ss-ff   (0)  play audio from/to&n;&n;Play Audio Track/Index:&n;         0c ...&n;&n;Pause/Resume:&n;pause:   8d pr 00 00 00 00 00.  (0)  pause (pr=00) &n;                                     resume (pr=80) audio playing&n;&n;Mode Select:&n;         84 00 nn-nn ??-?? 00   (0)  nn-nn: 2048 or 2340&n;                                     possibly defines transfer size&n;&n;set_vol: 84 83 00 00 sw le 00.  (0)  sw(itch): lrxxxxxx (off=1)&n;                                     le(vel): min=0, max=FF, else half&n;&t;&t;&t;&t;     (firmware 2.11)&n;&n;Mode Sense:&n;get_vol: 85 03 00 00 00 00 00.  (2)  tell current audio volume setting&n;&n;Read Disc Information:&n;tocdesc: 8b 00 00 00 00 00 00.  (6)  read the toc descriptor (&quot;msf-bin&quot;-format)&n;&n;Read TOC:&n;tocent:  8c fl nn 00 00 00 00.  (8)  read toc entry #nn&n;                                       (fl=0:&quot;lba&quot;-, =2:&quot;msf-bin&quot;-format)&n;&n;Read Capacity:&n;capacit: 88 00 00 00 00 00 00.  (5)  &quot;read CD-ROM capacity&quot;&n;&n;&n;Read Path Check:&n;ping:    00 00 00 00 00 00 00.  (2)  r0=AA, r1=55&n;                                     (&quot;ping&quot; if the drive is connected)&n;&n;Read Drive Version:&n;ident:   83 00 00 00 00 00 00. (12)  gives &quot;MATSHITAn.nn&quot; &n;                                     (n.nn = 2.01, 2.11., 3.00, ...)&n;&n;Seek:&n;seek:    01 00 ll-bb-aa 00 00.  (0)  &n;seek:    01 02 mm-ss-ff 00 00.  (0)  &n;&n;Read Data:&n;read:    02 xx-xx-xx nn-nn fl. (??)  read nn-nn blocks of 2048 bytes,&n;                                     starting at block xx-xx-xx  &n;                                     fl=0: &quot;lba&quot;-, =2:&quot;msf-bcd&quot;-coded xx-xx-xx&n;&n;Read XA-Data:&n;read:    03 xx-xx-xx nn-nn fl. (??)  read nn-nn blocks of 2340 bytes, &n;                                     starting at block xx-xx-xx&n;                                     fl=0: &quot;lba&quot;-, =2:&quot;msf-bcd&quot;-coded xx-xx-xx&n;&n;Read SUB_Q:&n;         89 fl 00 00 00 00 00. (13)  r0: audio status, r4-r7: lba/msf, &n;                                       fl=0: &quot;lba&quot;, fl=2: &quot;msf&quot;&n;&n;Read Disc Code:&n;         8a 00 00 00 00 00 00. (14)  possibly extended &quot;check condition&quot;-info&n;&n;Read Header:&n;         04 00 ll-bb-aa 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;         04 02 mm-ss-ff 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;&n;Spin Up:&n;         05 00 ll-bb-aa 00 00.  (0)  possibly implies a &quot;seek&quot;&n;&n;Spin Down:&n;         06 ...&n;&n;Diagnostic:&n;         07 00 ll-bb-aa 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;         07 02 mm-ss-ff 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;&n;Read UPC:&n;         08 00 ll-bb-aa 00 00. (16)  &n;         08 02 mm-ss-ff 00 00. (16)  &n;&n;Read ISRC:&n;         09 00 ll-bb-aa 00 00. (15)  15 bytes response with &quot;check2&quot;&n;         09 02 mm-ss-ff 00 00. (15)  15 bytes response with &quot;check2&quot;&n;&n;Set XA Parameter:&n;         86 ...&n;&n;Read XA Parameter:&n;         87 ...&n;&n;==============================================================================&n;============================================================================*/
multiline_comment|/*&n; * commands&n; *&n; * CR-52x:      CMD0_&n; * CR-56x:      CMD1_&n; * CD200:       CMD2_&n; * LCS-7260:    CMDL_&n; * TEAC CD-55A: CMDT_&n; */
DECL|macro|CMD1_RESET
mdefine_line|#define CMD1_RESET&t;0x0a
DECL|macro|CMD2_RESET
mdefine_line|#define CMD2_RESET&t;0x01
DECL|macro|CMDL_RESET
mdefine_line|#define CMDL_RESET&t;0x0a
DECL|macro|CMDT_RESET
mdefine_line|#define CMDT_RESET&t;0xc0
DECL|macro|CMD1_LOCK_CTL
mdefine_line|#define CMD1_LOCK_CTL&t;0x0c
DECL|macro|CMD2_LOCK_CTL
mdefine_line|#define CMD2_LOCK_CTL&t;0x1e
DECL|macro|CMDL_LOCK_CTL
mdefine_line|#define CMDL_LOCK_CTL&t;0x0e
DECL|macro|CMDT_LOCK_CTL
mdefine_line|#define CMDT_LOCK_CTL&t;0x1e
DECL|macro|CMD1_TRAY_CTL
mdefine_line|#define CMD1_TRAY_CTL&t;0x07
DECL|macro|CMD2_TRAY_CTL
mdefine_line|#define CMD2_TRAY_CTL&t;0x1b
DECL|macro|CMDL_TRAY_CTL
mdefine_line|#define CMDL_TRAY_CTL&t;0x0d
DECL|macro|CMDT_TRAY_CTL
mdefine_line|#define CMDT_TRAY_CTL&t;0x1b
DECL|macro|CMD1_MULTISESS
mdefine_line|#define CMD1_MULTISESS&t;0x8d
DECL|macro|CMD2_MULTISESS
mdefine_line|#define CMD2_MULTISESS&t;0x43
DECL|macro|CMDL_MULTISESS
mdefine_line|#define CMDL_MULTISESS&t;0x8c
DECL|macro|CMD1_SUBCHANINF
mdefine_line|#define CMD1_SUBCHANINF&t;0x11
DECL|macro|CMD2_SUBCHANINF
mdefine_line|#define CMD2_SUBCHANINF&t;0x
DECL|macro|CMD2_x02
mdefine_line|#define CMD2_x02&t;0x02
DECL|macro|CMD1_x08
mdefine_line|#define CMD1_x08&t;0x08
DECL|macro|CMD2_x08
mdefine_line|#define CMD2_x08&t;0x08
DECL|macro|CMDT_x08
mdefine_line|#define CMDT_x08&t;0x08
DECL|macro|CMD2_xD4
mdefine_line|#define CMD2_xD4&t;0xd4
DECL|macro|CMD2_xDA
mdefine_line|#define CMD2_xDA&t;0xda
DECL|macro|CMD0_PATH_CHECK
mdefine_line|#define CMD0_PATH_CHECK&t;0x00
DECL|macro|CMD1_PATH_CHECK
mdefine_line|#define CMD1_PATH_CHECK&t;0x00
DECL|macro|CMD2_PATH_CHECK
mdefine_line|#define CMD2_PATH_CHECK&t;0x
DECL|macro|CMDL_PATH_CHECK
mdefine_line|#define CMDL_PATH_CHECK&t;0x00
DECL|macro|CMD0_SEEK
mdefine_line|#define CMD0_SEEK&t;0x01
DECL|macro|CMD1_SEEK
mdefine_line|#define CMD1_SEEK&t;0x01
DECL|macro|CMD2_SEEK
mdefine_line|#define CMD2_SEEK&t;0x2b
DECL|macro|CMDL_SEEK
mdefine_line|#define CMDL_SEEK&t;0x01
DECL|macro|CMDT_SEEK
mdefine_line|#define CMDT_SEEK&t;0x2b
DECL|macro|CMD0_READ
mdefine_line|#define CMD0_READ&t;0x02
DECL|macro|CMD1_READ
mdefine_line|#define CMD1_READ&t;0x10
DECL|macro|CMD2_READ
mdefine_line|#define CMD2_READ&t;0x28
DECL|macro|CMDL_READ
mdefine_line|#define CMDL_READ&t;0x02
DECL|macro|CMDT_READ
mdefine_line|#define CMDT_READ&t;0x28
DECL|macro|CMD0_READ_XA
mdefine_line|#define CMD0_READ_XA&t;0x03
DECL|macro|CMDL_READ_XA
mdefine_line|#define CMDL_READ_XA&t;0x03 /* really ?? */
DECL|macro|CMD0_READ_HEAD
mdefine_line|#define CMD0_READ_HEAD&t;0x04
DECL|macro|CMD0_SPINUP
mdefine_line|#define CMD0_SPINUP&t;0x05
DECL|macro|CMD1_SPINUP
mdefine_line|#define CMD1_SPINUP&t;0x02
DECL|macro|CMD2_SPINUP
mdefine_line|#define CMD2_SPINUP&t;CMD2_TRAY_CTL
DECL|macro|CMDL_SPINUP
mdefine_line|#define CMDL_SPINUP&t;0x05
DECL|macro|CMD0_SPINDOWN
mdefine_line|#define CMD0_SPINDOWN&t;0x06 /* really??? */
DECL|macro|CMD1_SPINDOWN
mdefine_line|#define CMD1_SPINDOWN&t;0x06
DECL|macro|CMD2_SPINDOWN
mdefine_line|#define CMD2_SPINDOWN&t;CMD2_TRAY_CTL
DECL|macro|CMDL_SPINDOWN
mdefine_line|#define CMDL_SPINDOWN&t;0x0d
DECL|macro|CMD0_DIAG
mdefine_line|#define CMD0_DIAG&t;0x07
DECL|macro|CMD0_READ_UPC
mdefine_line|#define CMD0_READ_UPC&t;0x08
DECL|macro|CMD1_READ_UPC
mdefine_line|#define CMD1_READ_UPC&t;0x88
DECL|macro|CMD2_READ_UPC
mdefine_line|#define CMD2_READ_UPC&t;0x
DECL|macro|CMDL_READ_UPC
mdefine_line|#define CMDL_READ_UPC&t;0x08
DECL|macro|CMD0_READ_ISRC
mdefine_line|#define CMD0_READ_ISRC&t;0x09
DECL|macro|CMD0_PLAY
mdefine_line|#define CMD0_PLAY&t;0x0a
DECL|macro|CMD1_PLAY
mdefine_line|#define CMD1_PLAY&t;0x
DECL|macro|CMD2_PLAY
mdefine_line|#define CMD2_PLAY&t;0x
DECL|macro|CMDL_PLAY
mdefine_line|#define CMDL_PLAY&t;0x0a
DECL|macro|CMD0_PLAY_MSF
mdefine_line|#define CMD0_PLAY_MSF&t;0x0b
DECL|macro|CMD1_PLAY_MSF
mdefine_line|#define CMD1_PLAY_MSF&t;0x0e
DECL|macro|CMD2_PLAY_MSF
mdefine_line|#define CMD2_PLAY_MSF&t;0x47
DECL|macro|CMDL_PLAY_MSF
mdefine_line|#define CMDL_PLAY_MSF&t;0x
DECL|macro|CMDT_PLAY_MSF
mdefine_line|#define CMDT_PLAY_MSF&t;0x47
DECL|macro|CMD0_PLAY_TI
mdefine_line|#define CMD0_PLAY_TI&t;0x0c
DECL|macro|CMD0_STATUS
mdefine_line|#define CMD0_STATUS&t;0x81
DECL|macro|CMD1_STATUS
mdefine_line|#define CMD1_STATUS&t;0x05
DECL|macro|CMD2_STATUS
mdefine_line|#define CMD2_STATUS&t;0x00
DECL|macro|CMDL_STATUS
mdefine_line|#define CMDL_STATUS&t;0x81
DECL|macro|CMDT_STATUS
mdefine_line|#define CMDT_STATUS&t;0x00
DECL|macro|CMD0_READ_ERR
mdefine_line|#define CMD0_READ_ERR&t;0x82
DECL|macro|CMD1_READ_ERR
mdefine_line|#define CMD1_READ_ERR&t;0x82
DECL|macro|CMD2_READ_ERR
mdefine_line|#define CMD2_READ_ERR&t;0x03
DECL|macro|CMDL_READ_ERR
mdefine_line|#define CMDL_READ_ERR&t;0x82
DECL|macro|CMDT_READ_ERR
mdefine_line|#define CMDT_READ_ERR&t;0x03 /* get audio status */
DECL|macro|CMD0_READ_VER
mdefine_line|#define CMD0_READ_VER&t;0x83
DECL|macro|CMD1_READ_VER
mdefine_line|#define CMD1_READ_VER&t;0x83
DECL|macro|CMD2_READ_VER
mdefine_line|#define CMD2_READ_VER&t;0x12
DECL|macro|CMDT_READ_VER
mdefine_line|#define CMDT_READ_VER&t;0x12 /* ??? (unused) */
DECL|macro|CMDL_READ_VER
mdefine_line|#define CMDL_READ_VER&t;0x83
DECL|macro|CMD0_SETMODE
mdefine_line|#define CMD0_SETMODE&t;0x84
DECL|macro|CMD1_SETMODE
mdefine_line|#define CMD1_SETMODE&t;0x09
DECL|macro|CMD2_SETMODE
mdefine_line|#define CMD2_SETMODE&t;0x55
DECL|macro|CMDL_SETMODE
mdefine_line|#define CMDL_SETMODE&t;0x84
DECL|macro|CMDT_SETMODE
mdefine_line|#define CMDT_SETMODE&t;0x55
DECL|macro|CMD0_GETMODE
mdefine_line|#define CMD0_GETMODE&t;0x85
DECL|macro|CMD1_GETMODE
mdefine_line|#define CMD1_GETMODE&t;0x84
DECL|macro|CMD2_GETMODE
mdefine_line|#define CMD2_GETMODE&t;0x5a
DECL|macro|CMDL_GETMODE
mdefine_line|#define CMDL_GETMODE&t;0x85
DECL|macro|CMDT_GETMODE
mdefine_line|#define CMDT_GETMODE&t;0x5a
DECL|macro|CMD0_SET_XA
mdefine_line|#define CMD0_SET_XA&t;0x86
DECL|macro|CMD0_GET_XA
mdefine_line|#define CMD0_GET_XA&t;0x87
DECL|macro|CMD0_CAPACITY
mdefine_line|#define CMD0_CAPACITY&t;0x88
DECL|macro|CMD1_CAPACITY
mdefine_line|#define CMD1_CAPACITY&t;0x85
DECL|macro|CMD2_CAPACITY
mdefine_line|#define CMD2_CAPACITY&t;0x25
DECL|macro|CMDL_CAPACITY
mdefine_line|#define CMDL_CAPACITY&t;0x88
DECL|macro|CMD0_READSUBQ
mdefine_line|#define CMD0_READSUBQ&t;0x89
DECL|macro|CMD1_READSUBQ
mdefine_line|#define CMD1_READSUBQ&t;0x87
DECL|macro|CMD2_READSUBQ
mdefine_line|#define CMD2_READSUBQ&t;0x42
DECL|macro|CMDL_READSUBQ
mdefine_line|#define CMDL_READSUBQ&t;0x89
DECL|macro|CMDT_READSUBQ
mdefine_line|#define CMDT_READSUBQ&t;0x42
DECL|macro|CMD0_DISKCODE
mdefine_line|#define CMD0_DISKCODE&t;0x8a
DECL|macro|CMD0_DISKINFO
mdefine_line|#define CMD0_DISKINFO&t;0x8b
DECL|macro|CMD1_DISKINFO
mdefine_line|#define CMD1_DISKINFO&t;0x8b
DECL|macro|CMD2_DISKINFO
mdefine_line|#define CMD2_DISKINFO&t;0x
DECL|macro|CMDL_DISKINFO
mdefine_line|#define CMDL_DISKINFO&t;0x8b
DECL|macro|CMDT_DISKINFO
mdefine_line|#define CMDT_DISKINFO&t;0x43
DECL|macro|CMD0_READTOC
mdefine_line|#define CMD0_READTOC&t;0x8c
DECL|macro|CMD1_READTOC
mdefine_line|#define CMD1_READTOC&t;0x8c
DECL|macro|CMD2_READTOC
mdefine_line|#define CMD2_READTOC&t;0x
DECL|macro|CMDL_READTOC
mdefine_line|#define CMDL_READTOC&t;0x8c
DECL|macro|CMD0_PAU_RES
mdefine_line|#define CMD0_PAU_RES&t;0x8d
DECL|macro|CMD1_PAU_RES
mdefine_line|#define CMD1_PAU_RES&t;0x0d
DECL|macro|CMD2_PAU_RES
mdefine_line|#define CMD2_PAU_RES&t;0x4b
DECL|macro|CMDL_PAU_RES
mdefine_line|#define CMDL_PAU_RES&t;0x8d
DECL|macro|CMDT_PAU_RES
mdefine_line|#define CMDT_PAU_RES&t;0x4b
DECL|macro|CMD0_PACKET
mdefine_line|#define CMD0_PACKET&t;0x8e
DECL|macro|CMD1_PACKET
mdefine_line|#define CMD1_PACKET&t;0x8e
DECL|macro|CMD2_PACKET
mdefine_line|#define CMD2_PACKET&t;0x
DECL|macro|CMDL_PACKET
mdefine_line|#define CMDL_PACKET&t;0x8e
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
macro_line|#endif _LINUX_SBPCD_H
eof
