multiline_comment|/* $Id$&n; * Definitions for a AztechCD268 CD-ROM interface&n; *&t;Copyright (C) 1994, 1995  Werner Zimmermann&n; *&n; *&t;based on Mitsumi CDROM driver by Martin Harriss&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  History:&t;W.Zimmermann adaption to Aztech CD268-01A Version 1.3&n; *&t;&t;Oktober 1994 Email: zimmerma@rz.fht-esslingen.de&n; *  Note:&t;Points marked with ??? are questionable !&n; */
multiline_comment|/* *** change this to set the I/O port address */
DECL|macro|AZT_BASE_ADDR
mdefine_line|#define AZT_BASE_ADDR&t;&t;0x320
multiline_comment|/* Increase this if you get lots of timeouts; if you get kernel panic, replace&n;   STEN_LOW_WAIT by STEN_LOW in the source code */
DECL|macro|AZT_STATUS_DELAY
mdefine_line|#define AZT_STATUS_DELAY&t;400       /*for timer wait, STEN_LOW_WAIT*/
DECL|macro|AZT_TIMEOUT
mdefine_line|#define AZT_TIMEOUT&t;&t;8000000   /*for busy wait STEN_LOW, DTEN_LOW*/
DECL|macro|AZT_FAST_TIMEOUT
mdefine_line|#define AZT_FAST_TIMEOUT&t;10000     /*for reading the version string*/
multiline_comment|/* number of times to retry a command before giving up */
DECL|macro|AZT_RETRY_ATTEMPTS
mdefine_line|#define AZT_RETRY_ATTEMPTS&t;3
multiline_comment|/*defines for compatibility with mcd.c/mcd.h for Mitsumi drive, will probably&n;  go away, when the AZTECH driver is integrated in the standard Linux kernel*/
macro_line|#ifdef CONFIG_AZTCD
macro_line|#else
DECL|macro|AZTCD_TIMER
mdefine_line|#define AZTCD_TIMER&t;&t;    MCD_TIMER
DECL|macro|aztcd_init
mdefine_line|#define aztcd_init&t;&t;    mcd_init
DECL|macro|do_aztcd_request
mdefine_line|#define do_aztcd_request&t;    do_mcd_request
DECL|macro|aztcd_setup
mdefine_line|#define aztcd_setup&t;&t;    mcd_setup
DECL|macro|check_aztcd_media_change
mdefine_line|#define check_aztcd_media_change    check_mcd_media_change
macro_line|#endif
multiline_comment|/* port access macros */
DECL|macro|CMD_PORT
mdefine_line|#define CMD_PORT&t;&t;azt_port
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;&t;azt_port
DECL|macro|STATUS_PORT
mdefine_line|#define STATUS_PORT&t;&t;azt_port+1
DECL|macro|MODE_PORT
mdefine_line|#define MODE_PORT&t;&t;azt_port+2
multiline_comment|/* status bits */
DECL|macro|AST_CMD_CHECK
mdefine_line|#define AST_CMD_CHECK&t;&t;0x80&t;&t;/* command error */
DECL|macro|AST_DSK_CHG
mdefine_line|#define AST_DSK_CHG&t;&t;0x20&t;&t;/* disk removed or changed */
DECL|macro|AST_NOT_READY
mdefine_line|#define AST_NOT_READY&t;&t;0x02&t;&t;/* no disk in the drive */
DECL|macro|AST_DOOR_OPEN
mdefine_line|#define AST_DOOR_OPEN&t;&t;0x40&t;&t;/* door is open */
DECL|macro|AST_MODE_BITS
mdefine_line|#define AST_MODE_BITS&t;&t;0x1C&t;&t;/* Mode Bits */
DECL|macro|AST_INITIAL
mdefine_line|#define AST_INITIAL&t;&t;0x0C&t;&t;/* initial, only valid ... */
DECL|macro|AST_BUSY
mdefine_line|#define AST_BUSY&t;&t;0x04&t;&t;/* now playing, only valid&n;&t;&t;&t;&t;&t;&t;   in combination with mode&n;&t;&t;&t;&t;&t;&t;   bits */
multiline_comment|/* flag bits */
DECL|macro|AFL_DATA
mdefine_line|#define AFL_DATA&t;&t;0x02&t;&t;/* data available if low */
DECL|macro|AFL_STATUS
mdefine_line|#define AFL_STATUS&t;&t;0x04&t;&t;/* status available if low */
DECL|macro|AFL_OP_OK
mdefine_line|#define AFL_OP_OK&t;&t;0x01&t;&t;/* OP_OK command correct*/
DECL|macro|AFL_PA_OK
mdefine_line|#define AFL_PA_OK&t;&t;0x02&t;&t;/* PA_OK parameter correct*/
DECL|macro|AFL_OP_ERR
mdefine_line|#define AFL_OP_ERR&t;&t;0x05&t;&t;/* error in command*/
DECL|macro|AFL_PA_ERR
mdefine_line|#define AFL_PA_ERR&t;&t;0x06&t;&t;/* error in parameters*/
DECL|macro|POLLED
mdefine_line|#define POLLED&t;&t;&t;0x04&t;&t;/* polled mode */
multiline_comment|/* commands */
DECL|macro|ACMD_SOFT_RESET
mdefine_line|#define ACMD_SOFT_RESET&t;&t;0x10&t;&t;/* reset drive */
DECL|macro|ACMD_PLAY_READ
mdefine_line|#define ACMD_PLAY_READ&t;&t;0x20&t;&t;/* read data track in cooked mode */
DECL|macro|ACMD_DATA_READ_RAW
mdefine_line|#define ACMD_DATA_READ_RAW      0x21&t;&t;/* reading in raw mode*/
DECL|macro|ACMD_SEEK_TO_LEADIN
mdefine_line|#define ACMD_SEEK_TO_LEADIN     0x31&t;&t;/* seek to leadin track*/
DECL|macro|ACMD_GET_ERROR
mdefine_line|#define ACMD_GET_ERROR&t;&t;0x40&t;&t;/* get error code */
DECL|macro|ACMD_GET_STATUS
mdefine_line|#define ACMD_GET_STATUS&t;&t;0x41&t;&t;/* get status */
DECL|macro|ACMD_GET_Q_CHANNEL
mdefine_line|#define ACMD_GET_Q_CHANNEL      0x50&t;&t;/* read info from q channel */
DECL|macro|ACMD_EJECT
mdefine_line|#define ACMD_EJECT&t;&t;0x60&t;&t;/* eject/open */
DECL|macro|ACMD_PAUSE
mdefine_line|#define ACMD_PAUSE&t;&t;0x80&t;&t;/* pause */
DECL|macro|ACMD_STOP
mdefine_line|#define ACMD_STOP&t;&t;0x81&t;&t;/* stop play */
DECL|macro|ACMD_PLAY_AUDIO
mdefine_line|#define ACMD_PLAY_AUDIO&t;&t;0x90&t;&t;/* play audio track */
DECL|macro|ACMD_GET_VERSION
mdefine_line|#define ACMD_GET_VERSION&t;0xA0&t;&t;/* get firmware version */
DECL|macro|ACMD_SET_MODE
mdefine_line|#define ACMD_SET_MODE&t;&t;0xA1&t;&t;/* set drive mode */
DECL|macro|ACMD_SET_VOLUME
mdefine_line|#define ACMD_SET_VOLUME&t;&t;0xAE&t;&t;/* set audio level */
multiline_comment|/* borrowed from hd.c */
DECL|macro|SET_TIMER
mdefine_line|#define SET_TIMER(func, jifs) &bslash;&n;&t;((timer_table[AZTCD_TIMER].expires = jiffies + jifs), &bslash;&n;&t;(timer_table[AZTCD_TIMER].fn = func), &bslash;&n;&t;(timer_active |= 1&lt;&lt;AZTCD_TIMER))
DECL|macro|CLEAR_TIMER
mdefine_line|#define CLEAR_TIMER&t;&t;timer_active &amp;= ~(1&lt;&lt;AZTCD_TIMER)
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
DECL|struct|azt_Play_msf
r_struct
id|azt_Play_msf
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
DECL|struct|azt_DiskInfo
r_struct
id|azt_DiskInfo
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
DECL|struct|azt_Toc
r_struct
id|azt_Toc
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
eof
