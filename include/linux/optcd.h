multiline_comment|/* Defines for the Optics Storage 8000AT CDROM drive. */
macro_line|#ifndef _LINUX_OPTCD_H
DECL|macro|_LINUX_OPTCD_H
mdefine_line|#define _LINUX_OPTCD_H
multiline_comment|/* Drive registers */
DECL|macro|OPTCD_PORTBASE
mdefine_line|#define OPTCD_PORTBASE&t;0x340
multiline_comment|/* Read */
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;optcd_port&t;/* Read data/status */
DECL|macro|STATUS_PORT
mdefine_line|#define STATUS_PORT&t;optcd_port+1&t;/* Indicate data/status availability */
multiline_comment|/* Write */
DECL|macro|COMIN_PORT
mdefine_line|#define COMIN_PORT&t;optcd_port&t;/* For passing command/parameter */
DECL|macro|RESET_PORT
mdefine_line|#define RESET_PORT&t;optcd_port+1&t;/* Write anything and wait 0.5 sec */
DECL|macro|HCON_PORT
mdefine_line|#define HCON_PORT&t;optcd_port+2&t;/* Host Xfer Configuration */
multiline_comment|/* Command completion/status read from DATA register */
DECL|macro|ST_DRVERR
mdefine_line|#define ST_DRVERR&t;&t;0x80
DECL|macro|ST_DOOR_OPEN
mdefine_line|#define ST_DOOR_OPEN&t;&t;0x40
DECL|macro|ST_MIXEDMODE_DISK
mdefine_line|#define ST_MIXEDMODE_DISK&t;0x20
DECL|macro|ST_MODE_BITS
mdefine_line|#define ST_MODE_BITS&t;&t;0x1c
DECL|macro|ST_M_STOP
mdefine_line|#define ST_M_STOP&t;&t;0x00
DECL|macro|ST_M_READ
mdefine_line|#define ST_M_READ&t;&t;0x04
DECL|macro|ST_M_AUDIO
mdefine_line|#define ST_M_AUDIO&t;&t;0x04
DECL|macro|ST_M_PAUSE
mdefine_line|#define ST_M_PAUSE&t;&t;0x08
DECL|macro|ST_M_INITIAL
mdefine_line|#define ST_M_INITIAL&t;&t;0x0c
DECL|macro|ST_M_ERROR
mdefine_line|#define ST_M_ERROR&t;&t;0x10
DECL|macro|ST_M_OTHERS
mdefine_line|#define ST_M_OTHERS&t;&t;0x14
DECL|macro|ST_MODE2TRACK
mdefine_line|#define&t;ST_MODE2TRACK&t;&t;0x02
DECL|macro|ST_DSK_CHG
mdefine_line|#define&t;ST_DSK_CHG&t;&t;0x01
DECL|macro|ST_L_LOCK
mdefine_line|#define ST_L_LOCK&t;&t;0x01
DECL|macro|ST_CMD_OK
mdefine_line|#define ST_CMD_OK&t;&t;0x00
DECL|macro|ST_OP_OK
mdefine_line|#define ST_OP_OK&t;&t;0x01
DECL|macro|ST_PA_OK
mdefine_line|#define ST_PA_OK&t;&t;0x02
DECL|macro|ST_OP_ERROR
mdefine_line|#define ST_OP_ERROR&t;&t;0x05
DECL|macro|ST_PA_ERROR
mdefine_line|#define ST_PA_ERROR&t;&t;0x06
multiline_comment|/* Error codes (appear as command completion code from DATA register) */
multiline_comment|/* Player related errors */
DECL|macro|ERR_ILLCMD
mdefine_line|#define ERR_ILLCMD&t;0x11&t;/* Illegal command to player module */
DECL|macro|ERR_ILLPARM
mdefine_line|#define ERR_ILLPARM&t;0x12&t;/* Illegal parameter to player module */
DECL|macro|ERR_SLEDGE
mdefine_line|#define ERR_SLEDGE&t;0x13
DECL|macro|ERR_FOCUS
mdefine_line|#define ERR_FOCUS&t;0x14
DECL|macro|ERR_MOTOR
mdefine_line|#define ERR_MOTOR&t;0x15
DECL|macro|ERR_RADIAL
mdefine_line|#define ERR_RADIAL&t;0x16
DECL|macro|ERR_PLL
mdefine_line|#define ERR_PLL&t;&t;0x17&t;/* PLL lock error */
DECL|macro|ERR_SUB_TIM
mdefine_line|#define ERR_SUB_TIM&t;0x18&t;/* Subcode timeout error */
DECL|macro|ERR_SUB_NF
mdefine_line|#define ERR_SUB_NF&t;0x19&t;/* Subcode not found error */
DECL|macro|ERR_TRAY
mdefine_line|#define ERR_TRAY&t;0x1a
DECL|macro|ERR_TOC
mdefine_line|#define ERR_TOC&t;&t;0x1b&t;/* Table of Contents read error */
DECL|macro|ERR_JUMP
mdefine_line|#define ERR_JUMP&t;0x1c
multiline_comment|/* Data errors */
DECL|macro|ERR_MODE
mdefine_line|#define ERR_MODE&t;0x21
DECL|macro|ERR_FORM
mdefine_line|#define ERR_FORM&t;0x22
DECL|macro|ERR_HEADADDR
mdefine_line|#define ERR_HEADADDR&t;0x23&t;/* Header Address not found */
DECL|macro|ERR_CRC
mdefine_line|#define ERR_CRC&t;&t;0x24
DECL|macro|ERR_ECC
mdefine_line|#define ERR_ECC&t;&t;0x25&t;/* Uncorrectable ECC error */
DECL|macro|ERR_CRC_UNC
mdefine_line|#define ERR_CRC_UNC&t;0x26&t;/* CRC error and uncorrectable error */
DECL|macro|ERR_ILLBSYNC
mdefine_line|#define ERR_ILLBSYNC&t;0x27&t;/* Illegal block sync error */
DECL|macro|ERR_VDST
mdefine_line|#define ERR_VDST&t;0x28&t;/* VDST not found */
multiline_comment|/* Timeout errors */
DECL|macro|ERR_READ_TIM
mdefine_line|#define ERR_READ_TIM&t;0x31&t;/* Read timeout error */
DECL|macro|ERR_DEC_STP
mdefine_line|#define ERR_DEC_STP&t;0x32&t;/* Decoder stopped */
DECL|macro|ERR_DEC_TIM
mdefine_line|#define ERR_DEC_TIM&t;0x33&t;/* Decoder interrupt timeout error */
multiline_comment|/* Function abort codes */
DECL|macro|ERR_KEY
mdefine_line|#define ERR_KEY&t;&t;0x41&t;/* Key -Detected abort */
DECL|macro|ERR_READ_FINISH
mdefine_line|#define ERR_READ_FINISH&t;0x42&t;/* Read Finish */
multiline_comment|/* Second Byte diagnostic codes */
DECL|macro|ERR_NOBSYNC
mdefine_line|#define ERR_NOBSYNC&t;0x01&t;/* No block sync */
DECL|macro|ERR_SHORTB
mdefine_line|#define ERR_SHORTB&t;0x02&t;/* Short block */
DECL|macro|ERR_LONGB
mdefine_line|#define ERR_LONGB&t;0x03&t;/* Long block */
DECL|macro|ERR_SHORTDSP
mdefine_line|#define ERR_SHORTDSP&t;0x04&t;/* Short DSP word */
DECL|macro|ERR_LONGDSP
mdefine_line|#define ERR_LONGDSP&t;0x05&t;/* Long DSP word */
multiline_comment|/* Status availability flags read from STATUS register */
DECL|macro|FL_EJECT
mdefine_line|#define FL_EJECT&t;0x20
DECL|macro|FL_WAIT
mdefine_line|#define FL_WAIT&t;&t;0x10&t;/* active low */
DECL|macro|FL_EOP
mdefine_line|#define FL_EOP&t;&t;0x08&t;/* active low */
DECL|macro|FL_STEN
mdefine_line|#define FL_STEN&t;&t;0x04&t;/* Status available when low */
DECL|macro|FL_DTEN
mdefine_line|#define FL_DTEN&t;&t;0x02&t;/* Data available when low */
DECL|macro|FL_DRQ
mdefine_line|#define FL_DRQ&t;&t;0x01&t;/* active low */
DECL|macro|FL_RESET
mdefine_line|#define FL_RESET&t;0xde&t;/* These bits are high after a reset */
DECL|macro|FL_STDT
mdefine_line|#define FL_STDT&t;&t;(FL_STEN|FL_DTEN)
multiline_comment|/* Transfer mode, written to HCON register */
DECL|macro|HCON_DTS
mdefine_line|#define HCON_DTS&t;0x08
DECL|macro|HCON_SDRQB
mdefine_line|#define HCON_SDRQB&t;0x04
DECL|macro|HCON_LOHI
mdefine_line|#define HCON_LOHI&t;0x02
DECL|macro|HCON_DMA16
mdefine_line|#define HCON_DMA16&t;0x01
multiline_comment|/* Drive command set, written to COMIN register */
multiline_comment|/* Quick response commands */
DECL|macro|COMDRVST
mdefine_line|#define COMDRVST&t;0x20&t;/* Drive Status Read */
DECL|macro|COMERRST
mdefine_line|#define COMERRST&t;0x21&t;/* Error Status Read */
DECL|macro|COMIOCTLISTAT
mdefine_line|#define COMIOCTLISTAT&t;0x22&t;/* Status Read; reset disk changed bit */
DECL|macro|COMINITSINGLE
mdefine_line|#define COMINITSINGLE&t;0x28&t;/* Initialize Single Speed */
DECL|macro|COMINITDOUBLE
mdefine_line|#define COMINITDOUBLE&t;0x29&t;/* Initialize Double Speed */
DECL|macro|COMUNLOCK
mdefine_line|#define COMUNLOCK&t;0x30&t;/* Unlock */
DECL|macro|COMLOCK
mdefine_line|#define COMLOCK&t;&t;0x31&t;/* Lock */
DECL|macro|COMLOCKST
mdefine_line|#define COMLOCKST&t;0x32&t;/* Lock/Unlock Status */
DECL|macro|COMVERSION
mdefine_line|#define COMVERSION&t;0x40&t;/* Get Firmware Revision */
DECL|macro|COMVOIDREADMODE
mdefine_line|#define COMVOIDREADMODE&t;0x50&t;/* Void Data Read Mode */
multiline_comment|/* Read commands */
DECL|macro|COMFETCH
mdefine_line|#define COMFETCH&t;0x60&t;/* Prefetch Data */
DECL|macro|COMREAD
mdefine_line|#define COMREAD&t;&t;0x61&t;/* Read */
DECL|macro|COMREADRAW
mdefine_line|#define COMREADRAW&t;0x62&t;/* Read Raw Data */
DECL|macro|COMREADALL
mdefine_line|#define COMREADALL&t;0x63&t;/* Read All 2646 Bytes */
multiline_comment|/* Player control commands */
DECL|macro|COMLEADIN
mdefine_line|#define COMLEADIN&t;0x70&t;/* Seek To Lead-in */
DECL|macro|COMSEEK
mdefine_line|#define COMSEEK&t;&t;0x71&t;/* Seek */
DECL|macro|COMPAUSEON
mdefine_line|#define COMPAUSEON&t;0x80&t;/* Pause On */
DECL|macro|COMPAUSEOFF
mdefine_line|#define COMPAUSEOFF&t;0x81&t;/* Pause Off */
DECL|macro|COMSTOP
mdefine_line|#define COMSTOP&t;&t;0x82&t;/* Stop */
DECL|macro|COMOPEN
mdefine_line|#define COMOPEN&t;&t;0x90&t;/* Open Tray Door */
DECL|macro|COMCLOSE
mdefine_line|#define COMCLOSE&t;0x91&t;/* Close Tray Door */
DECL|macro|COMPLAY
mdefine_line|#define COMPLAY&t;&t;0xa0&t;/* Audio Play */
DECL|macro|COMPLAY_TNO
mdefine_line|#define COMPLAY_TNO&t;0xa2&t;/* Audio Play By Track Number */
DECL|macro|COMSUBQ
mdefine_line|#define COMSUBQ&t;&t;0xb0&t;/* Read Sub-q Code */
DECL|macro|COMLOCATION
mdefine_line|#define COMLOCATION&t;0xb1&t;/* Read Head Position */
multiline_comment|/* Audio control commands */
DECL|macro|COMCHCTRL
mdefine_line|#define COMCHCTRL&t;0xc0&t;/* Audio Channel Control */
multiline_comment|/* Miscellaneous (test) commands */
DECL|macro|COMDRVTEST
mdefine_line|#define COMDRVTEST&t;0xd0&t;/* Write Test Bytes */
DECL|macro|COMTEST
mdefine_line|#define COMTEST&t;&t;0xd1&t;/* Diagnostic Test */
DECL|macro|BUSY_TIMEOUT
mdefine_line|#define BUSY_TIMEOUT&t;&t;10000000&t;/* for busy wait */
DECL|macro|SLEEP_TIMEOUT
mdefine_line|#define SLEEP_TIMEOUT&t;&t;400&t;&t;/* for timer wait */
DECL|macro|READ_TIMEOUT
mdefine_line|#define READ_TIMEOUT&t;&t;3000&t;&t;/* for poll wait */
DECL|macro|RESET_WAIT
mdefine_line|#define RESET_WAIT&t;&t;1000
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER(func, jifs) &bslash;&n;&t;delay_timer.expires = jiffies+(jifs); &bslash;&n;&t;delay_timer.function = (void *) (func); &bslash;&n;&t;add_timer(&amp;delay_timer);
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER&t;&t;del_timer(&amp;delay_timer)
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS&t;&t;104
DECL|struct|msf
r_struct
id|msf
(brace
DECL|member|min
r_int
r_char
id|min
suffix:semicolon
DECL|member|sec
r_int
r_char
id|sec
suffix:semicolon
DECL|member|frame
r_int
r_char
id|frame
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|opt_Play_msf
r_struct
id|opt_Play_msf
(brace
DECL|member|start
r_struct
id|msf
id|start
suffix:semicolon
DECL|member|end
r_struct
id|msf
id|end
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|opt_DiskInfo
r_struct
id|opt_DiskInfo
(brace
DECL|member|first
r_int
r_char
id|first
suffix:semicolon
DECL|member|last
r_int
r_char
id|last
suffix:semicolon
DECL|member|diskLength
r_struct
id|msf
id|diskLength
suffix:semicolon
DECL|member|firstTrack
r_struct
id|msf
id|firstTrack
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|opt_Toc
r_struct
id|opt_Toc
(brace
DECL|member|ctrl_addr
r_int
r_char
id|ctrl_addr
suffix:semicolon
DECL|member|track
r_int
r_char
id|track
suffix:semicolon
DECL|member|pointIndex
r_int
r_char
id|pointIndex
suffix:semicolon
DECL|member|trackTime
r_struct
id|msf
id|trackTime
suffix:semicolon
DECL|member|diskTime
r_struct
id|msf
id|diskTime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CURRENT_VALID
mdefine_line|#define CURRENT_VALID &bslash;&n;&t;(CURRENT &amp;&amp; MAJOR(CURRENT -&gt; rq_dev) == MAJOR_NR &bslash;&n;&t; &amp;&amp; CURRENT -&gt; cmd == READ &amp;&amp; CURRENT -&gt; sector != -1)
DECL|macro|DEBUG_DRIVE_IF
macro_line|#undef&t;DEBUG_DRIVE_IF&t;&t;/* Low level drive interface */
DECL|macro|DEBUG_COMMANDS
macro_line|#undef&t;DEBUG_COMMANDS&t;&t;/* Commands sent to drive */
DECL|macro|DEBUG_VFS
macro_line|#undef&t;DEBUG_VFS&t;&t;/* VFS interface */
DECL|macro|DEBUG_CONV
macro_line|#undef&t;DEBUG_CONV&t;&t;/* Address conversions */
DECL|macro|DEBUG_TOC
macro_line|#undef&t;DEBUG_TOC&t;&t;/* Q-channel and Table of Contents */
DECL|macro|DEBUG_BUFFERS
macro_line|#undef&t;DEBUG_BUFFERS&t;&t;/* Buffering and block size conversion */
DECL|macro|DEBUG_REQUEST
macro_line|#undef&t;DEBUG_REQUEST&t;&t;/* Request mechanism */
DECL|macro|DEBUG_STATE
macro_line|#undef&t;DEBUG_STATE&t;&t;/* State machine */
multiline_comment|/* Low level drive interface */
multiline_comment|/* Errors that can occur in the low level interface */
DECL|macro|ERR_IF_CMD_TIMEOUT
mdefine_line|#define ERR_IF_CMD_TIMEOUT&t;0x100
DECL|macro|ERR_IF_ERR_TIMEOUT
mdefine_line|#define ERR_IF_ERR_TIMEOUT&t;0x101
DECL|macro|ERR_IF_RESP_TIMEOUT
mdefine_line|#define ERR_IF_RESP_TIMEOUT&t;0x102
DECL|macro|ERR_IF_DATA_TIMEOUT
mdefine_line|#define ERR_IF_DATA_TIMEOUT&t;0x103
DECL|macro|ERR_IF_NOSTAT
mdefine_line|#define ERR_IF_NOSTAT&t;&t;0x104
multiline_comment|/* Errors in table of contents */
DECL|macro|ERR_TOC_MISSINGINFO
mdefine_line|#define ERR_TOC_MISSINGINFO&t;0x120
DECL|macro|ERR_TOC_MISSINGENTRY
mdefine_line|#define ERR_TOC_MISSINGENTRY&t;0x121
multiline_comment|/* End .h defines */
macro_line|#endif _LINUX_OPTCD_H
eof
