multiline_comment|/*&n; * sbpcd.h   Specify interface address and interface type here.&n; */
multiline_comment|/*&n; * the definitions for the first controller can get overridden by&n; * the kernel command line (&quot;lilo boot option&quot;).&n; * Examples:&n; *                                 sbpcd=0x230,SoundBlaster&n; *                             or&n; *                                 sbpcd=0x300,LaserMate&n; *                             or&n; *                                 sbpcd=0x330,SPEA&n; *&n; * These strings are case sensitive !!!&n; */
multiline_comment|/*&n; * put your CDROM port base address into CDROM_PORT&n; * and specify the type of your interface in SBPRO.&n; *&n; * SBPRO addresses typically are 0x0230 (=0x220+0x10), 0x0250, ...&n; * LASERMATE (CI-101P, WDH-7001C) adresses typically are 0x0300, 0x0310, ...&n; * SPEA addresses are 0x320, 0x330, 0x340, 0x350&n; * there are some soundcards on the market with 0x0630, 0x0650, ...&n; *&n; * example: if your SBPRO audio address is 0x220, specify 0x230.&n; *&n; *&n; * set SBPRO to 1 for &quot;true&quot; SoundBlaster card&n; * set SBPRO to 0 for &quot;poor&quot; (no sound) interface cards&n; *                and for &quot;compatible&quot; soundcards.&n; * set SBPRO to 2 for the SPEA Media FX card&n; *&n; * most &quot;compatible&quot; sound boards like Galaxy need to set SBPRO to 0 !!!&n; * if SBPRO gets set wrong, the drive will get found - but any&n; * data access will give errors (audio access will work).&n; * The OmniCD interface card from CreativeLabs needs SBPRO 1.&n; *&n; * mail to emoenke@gwdg.de if your &quot;compatible&quot; card needs SBPRO 1&n; * (currently I do not know any &quot;compatible&quot; with SBPRO 1)&n; * then I can include better information with the next release.&n; */
macro_line|#if !(SBPCD_ISSUE-1) /* first (or if you have only one) interface board: */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x0230
DECL|macro|SBPRO
mdefine_line|#define SBPRO     1
macro_line|#endif
multiline_comment|/*&n; * If you have a &quot;compatible&quot; soundcard of type &quot;SBPRO 0&quot; or &quot;SBPRO 2&quot;,&n; * enter your sound card&squot;s base address here if you want sbpcd to turn&n; * the CD sound channels on.&n; *&n; * Example: #define SOUND_BASE 0x220 enables the sound card&squot;s CD channels&n; *          #define SOUND_BASE 0     leaves the soundcard untouched&n; */
DECL|macro|SOUND_BASE
mdefine_line|#define SOUND_BASE 0
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
mdefine_line|#define CDROM_PORT 0x0340
DECL|macro|SBPRO
mdefine_line|#define SBPRO     0
macro_line|#endif
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * nothing to change below here if you are not experimenting&n; */
macro_line|#ifndef _LINUX_SBPCD_H
DECL|macro|_LINUX_SBPCD_H
mdefine_line|#define _LINUX_SBPCD_H
multiline_comment|/*==========================================================================*/
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
DECL|macro|DBG_000
mdefine_line|#define DBG_000&t;&t;27      /* unnecessary information */
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * bits of flags_cmd_out:&n; */
DECL|macro|f_respo3
mdefine_line|#define f_respo3 0x100
DECL|macro|f_putcmd
mdefine_line|#define f_putcmd 0x80
DECL|macro|f_respo2
mdefine_line|#define f_respo2 0x40
DECL|macro|f_lopsta
mdefine_line|#define f_lopsta 0x20
DECL|macro|f_getsta
mdefine_line|#define f_getsta 0x10
DECL|macro|f_ResponseStatus
mdefine_line|#define f_ResponseStatus 0x08
DECL|macro|f_obey_p_check
mdefine_line|#define f_obey_p_check 0x04
DECL|macro|f_bit1
mdefine_line|#define f_bit1 0x02
DECL|macro|f_wait_if_busy
mdefine_line|#define f_wait_if_busy 0x01
multiline_comment|/*&n; * diskstate_flags:&n; */
DECL|macro|upc_bit
mdefine_line|#define upc_bit 0x40
DECL|macro|volume_bit
mdefine_line|#define volume_bit 0x20
DECL|macro|toc_bit
mdefine_line|#define toc_bit 0x10
DECL|macro|multisession_bit
mdefine_line|#define multisession_bit 0x08
DECL|macro|cd_size_bit
mdefine_line|#define cd_size_bit 0x04
DECL|macro|subq_bit
mdefine_line|#define subq_bit 0x02
DECL|macro|frame_size_bit
mdefine_line|#define frame_size_bit 0x01
multiline_comment|/*&n; * disk states (bits of diskstate_flags):&n; */
DECL|macro|upc_valid
mdefine_line|#define upc_valid (DriveStruct[d].diskstate_flags&amp;upc_bit)
DECL|macro|volume_valid
mdefine_line|#define volume_valid (DriveStruct[d].diskstate_flags&amp;volume_bit)
DECL|macro|toc_valid
mdefine_line|#define toc_valid (DriveStruct[d].diskstate_flags&amp;toc_bit)
DECL|macro|multisession_valid
mdefine_line|#define multisession_valid (DriveStruct[d].diskstate_flags&amp;multisession_bit)
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
mdefine_line|#define p_bit_1 0x02
DECL|macro|p_disk_ok
mdefine_line|#define p_disk_ok 0x01
multiline_comment|/*&n; * &quot;old&quot; drives status result bits:&n; */
DECL|macro|p_caddin_old
mdefine_line|#define p_caddin_old 0x40
DECL|macro|p_success_old
mdefine_line|#define p_success_old 0x08
DECL|macro|p_busy_old
mdefine_line|#define p_busy_old 0x04
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
DECL|macro|drv_199
mdefine_line|#define drv_199 0       /* &lt;200 */
DECL|macro|drv_200
mdefine_line|#define drv_200 1       /* &lt;201 */
DECL|macro|drv_201
mdefine_line|#define drv_201 2       /* &lt;210 */
DECL|macro|drv_210
mdefine_line|#define drv_210 3       /* &lt;211 */
DECL|macro|drv_211
mdefine_line|#define drv_211 4       /* &lt;300 */
DECL|macro|drv_300
mdefine_line|#define drv_300 5       /* else */
DECL|macro|drv_099
mdefine_line|#define drv_099 0x10    /* new,  &lt;100 */
DECL|macro|drv_100
mdefine_line|#define drv_100 0x11    /* new, &gt;=100 */
DECL|macro|drv_new
mdefine_line|#define drv_new 0x10    /* all new drives have that bit set */
DECL|macro|drv_old
mdefine_line|#define drv_old 0x00    /*  */
multiline_comment|/*&n; * drv_099 and drv_100 are the &quot;new&quot; drives&n; */
DECL|macro|new_drive
mdefine_line|#define new_drive (DriveStruct[d].drv_type&amp;0x10)
multiline_comment|/*&n; * audio states:&n; */
DECL|macro|audio_playing
mdefine_line|#define audio_playing 2
DECL|macro|audio_pausing
mdefine_line|#define audio_pausing 1
multiline_comment|/*&n; * drv_pattern, drv_options:&n; */
DECL|macro|speed_auto
mdefine_line|#define speed_auto 0x80
DECL|macro|speed_300
mdefine_line|#define speed_300 0x40
DECL|macro|speed_150
mdefine_line|#define speed_150 0x20
DECL|macro|sax_a
mdefine_line|#define sax_a 0x04
DECL|macro|sax_xn2
mdefine_line|#define sax_xn2 0x02
DECL|macro|sax_xn1
mdefine_line|#define sax_xn1 0x01
multiline_comment|/*&n; * values of cmd_type (0 else):&n; */
DECL|macro|READ_M1
mdefine_line|#define READ_M1  0x01 /* &quot;data mode 1&quot;: 2048 bytes per frame */
DECL|macro|READ_M2
mdefine_line|#define READ_M2  0x02 /* &quot;data mode 2&quot;: 12+2048+280 bytes per frame */
DECL|macro|READ_SC
mdefine_line|#define READ_SC  0x04 /* &quot;subchannel info&quot;: 96 bytes per frame */
DECL|macro|READ_AU
mdefine_line|#define READ_AU  0x08 /* &quot;audio frame&quot;: 2352 bytes per frame */
multiline_comment|/*&n; * sense byte: used only if new_drive&n; *                  only during cmd 09 00 xx ah al 00 00&n; *&n; *          values: 00&n; *                  82 &quot;raw audio&quot; mode&n; *                  xx from infobuf[0] after 85 00 00 00 00 00 00&n; */
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
multiline_comment|/*============================================================================&n;==============================================================================&n;&n;COMMAND SET of &quot;old&quot; drives like CR-521, CR-522&n;               (the CR-562 family is different):&n;&n;No.&t;Command&t;&t;&t;       Code&n;--------------------------------------------&n;&n;Drive Commands:&n; 1&t;Seek&t;&t;&t;&t;01&t;&n; 2&t;Read Data&t;&t;&t;02&n; 3&t;Read XA-Data&t;&t;&t;03&n; 4&t;Read Header&t;&t;&t;04&n; 5&t;Spin Up&t;&t;&t;&t;05&n; 6&t;Spin Down&t;&t;&t;06&n; 7&t;Diagnostic&t;&t;&t;07&n; 8&t;Read UPC&t;&t;&t;08&n; 9&t;Read ISRC&t;&t;&t;09&n;10&t;Play Audio&t;&t;&t;0A&n;11&t;Play Audio MSF&t;&t;&t;0B&n;12&t;Play Audio Track/Index&t;&t;0C&n;&n;Status Commands:&n;13&t;Read Status&t;&t;&t;81&t;&n;14&t;Read Error&t;&t;&t;82&n;15&t;Read Drive Version&t;&t;83&n;16&t;Mode Select&t;&t;&t;84&n;17&t;Mode Sense&t;&t;&t;85&n;18&t;Set XA Parameter&t;&t;86&n;19&t;Read XA Parameter&t;&t;87&n;20&t;Read Capacity&t;&t;&t;88&n;21&t;Read SUB_Q&t;&t;&t;89&n;22&t;Read Disc Code&t;&t;&t;8A&n;23&t;Read Disc Information&t;&t;8B&n;24&t;Read TOC&t;&t;&t;8C&n;25&t;Pause/Resume&t;&t;&t;8D&n;26&t;Read Packet&t;&t;&t;8E&n;27&t;Read Path Check&t;&t;&t;00&n; &n; &n;all numbers (lba, msf-bin, msf-bcd, counts) to transfer high byte first&n;&n;mnemo     7-byte command        #bytes response (r0...rn)&n;________ ____________________  ____ &n;&n;Read Status:&n;status:  81.                    (1)  one-byte command, gives the main&n;                                                          status byte&n;Read Error:&n;check1:  82 00 00 00 00 00 00.  (6)  r1: audio status&n;&n;Read Packet:&n;check2:  8e xx 00 00 00 00 00. (xx)  gets xx bytes response, relating&n;                                        to commands 01 04 05 07 08 09&n;&n;Play Audio:&n;play:    0a ll-bb-aa nn-nn-nn.  (0)  play audio, ll-bb-aa: starting block (lba),&n;                                                 nn-nn-nn: #blocks&n;Play Audio MSF:&n;         0b mm-ss-ff mm-ss-ff   (0)  play audio from/to&n;&n;Play Audio Track/Index:&n;         0c ...&n;&n;Pause/Resume:&n;pause:   8d pr 00 00 00 00 00.  (0)  pause (pr=00) &n;                                     resume (pr=80) audio playing&n;&n;Mode Select:&n;         84 00 nn-nn ??-?? 00   (0)  nn-nn: 2048 or 2340&n;                                     possibly defines transfer size&n;&n;set_vol: 84 83 00 00 sw le 00.  (0)  sw(itch): lrxxxxxx (off=1)&n;                                     le(vel): min=0, max=FF, else half&n;&t;&t;&t;&t;     (firmware 2.11)&n;&n;Mode Sense:&n;get_vol: 85 03 00 00 00 00 00.  (2)  tell current audio volume setting&n;&n;Read Disc Information:&n;tocdesc: 8b 00 00 00 00 00 00.  (6)  read the toc descriptor (&quot;msf-bin&quot;-format)&n;&n;Read TOC:&n;tocent:  8c fl nn 00 00 00 00.  (8)  read toc entry #nn&n;                                       (fl=0:&quot;lba&quot;-, =2:&quot;msf-bin&quot;-format)&n;&n;Read Capacity:&n;capacit: 88 00 00 00 00 00 00.  (5)  &quot;read CD-ROM capacity&quot;&n;&n;&n;Read Path Check:&n;ping:    00 00 00 00 00 00 00.  (2)  r0=AA, r1=55&n;                                     (&quot;ping&quot; if the drive is connected)&n;&n;Read Drive Version:&n;ident:   83 00 00 00 00 00 00. (12)  gives &quot;MATSHITAn.nn&quot; &n;                                     (n.nn = 2.01, 2.11., 3.00, ...)&n;&n;Seek:&n;seek:    01 00 ll-bb-aa 00 00.  (0)  &n;seek:    01 02 mm-ss-ff 00 00.  (0)  &n;&n;Read Data:&n;read:    02 xx-xx-xx nn-nn fl. (??)  read nn-nn blocks of 2048 bytes,&n;                                     starting at block xx-xx-xx  &n;                                     fl=0: &quot;lba&quot;-, =2:&quot;msf-bcd&quot;-coded xx-xx-xx&n;&n;Read XA-Data:&n;read:    03 ll-bb-aa nn-nn 00. (??)  read nn-nn blocks of 2340 bytes, &n;                                     starting at block ll-bb-aa&n;&n;Read SUB_Q:&n;         89 fl 00 00 00 00 00. (13)  r0: audio status, r4-r7: lba/msf, &n;                                       fl=0: &quot;lba&quot;, fl=2: &quot;msf&quot;&n;&n;Read Disc Code:&n;         8a 00 00 00 00 00 00. (14)  possibly extended &quot;check condition&quot;-info&n;&n;Read Header:&n;         04 00 ll-bb-aa 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;         04 02 mm-ss-ff 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;&n;Spin Up:&n;         05 00 ll-bb-aa 00 00.  (0)  possibly implies a &quot;seek&quot;&n;&n;Spin Down:&n;         06 ...&n;&n;Diagnostic:&n;         07 00 ll-bb-aa 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;         07 02 mm-ss-ff 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;&n;Read UPC:&n;         08 00 ll-bb-aa 00 00. (16)  &n;         08 02 mm-ss-ff 00 00. (16)  &n;&n;Read ISRC:&n;         09 00 ll-bb-aa 00 00. (15)  15 bytes response with &quot;check2&quot;&n;         09 02 mm-ss-ff 00 00. (15)  15 bytes response with &quot;check2&quot;&n;&n;Set XA Parameter:&n;         86 ...&n;&n;Read XA Parameter:&n;         87 ...&n;&n;==============================================================================&n;============================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
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
macro_line|#endif _LINUX_SBPCD_H
eof
