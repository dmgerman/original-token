multiline_comment|/*&n; * Definitions for the Mitsumi CDROM interface&n; * (H) Hackright 1996 by Marcin Dalecki &lt;dalecki@namu03.gwdg.de&gt;&n; * VERSION: 2.5&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __MCDX_H
DECL|macro|__MCDX_H
mdefine_line|#define __MCDX_H
multiline_comment|/*&n; * &t;PLEASE CONFIGURE THIS ACCORDING TO YOUR HARDWARE/JUMPER SETTINGS.&n; *&n; *      o       MCDX_NDRIVES  :  number of used entries of the following table&n; *      o       MCDX_DRIVEMAP :  table of {i/o base, irq} per controller&n; *&n; *      NOTE: Don&squot;t even think about connecting the drive to IRQ 9(2).&n; *&t;In the AT architecture this interrupt is used to cascade the two&n; *&t;interrupt controllers and isn&squot;t therefore usable for anything else!&n; */
multiline_comment|/* #define I_WAS_IN_MCDX_H */
DECL|macro|MCDX_NDRIVES
mdefine_line|#define MCDX_NDRIVES 1
DECL|macro|MCDX_DRIVEMAP
mdefine_line|#define MCDX_DRIVEMAP {&t;{0x230, 11},&t;&bslash;&n;&t;&t;&t;{0x304, 05},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;&t;&t;&t;{0x000, 00},  &t;&bslash;&n;}
multiline_comment|/* &n; * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!NO USER INTERVENTION NEEDED BELOW&n; * If You are sure that all configuration is done, please uncomment the&n; * line below. &n; */
DECL|macro|MCDX_DEBUG
macro_line|#undef MCDX_DEBUG&t;/* This is *REALLY* only for development! */
macro_line|#ifdef MCDX_DEBUG
DECL|macro|MCDX_TRACE
mdefine_line|#define MCDX_TRACE(x) printk x
DECL|macro|MCDX_TRACE_IOCTL
mdefine_line|#define MCDX_TRACE_IOCTL(x) printk x
macro_line|#else
DECL|macro|MCDX_TRACE
mdefine_line|#define MCDX_TRACE(x)
DECL|macro|MCDX_TRACE_IOCTL
mdefine_line|#define MCDX_TRACE_IOCTL(x)
macro_line|#endif
multiline_comment|/*      The name of the device */
DECL|macro|MCDX
mdefine_line|#define MCDX &quot;mcdx&quot;
multiline_comment|/*&n; *      Per controller 4 bytes i/o are needed. &n; */
DECL|macro|MCDX_IO_SIZE
mdefine_line|#define MCDX_IO_SIZE&t;&t;4
multiline_comment|/* &n; * Masks for the status byte, returned from every command, set if&n; * the description is true &n; */
DECL|macro|MCDX_RBIT_OPEN
mdefine_line|#define MCDX_RBIT_OPEN       0x80&t;/* door is open */
DECL|macro|MCDX_RBIT_DISKSET
mdefine_line|#define MCDX_RBIT_DISKSET    0x40&t;/* disk set (recognised) */
DECL|macro|MCDX_RBIT_CHANGED
mdefine_line|#define MCDX_RBIT_CHANGED    0x20&t;/* disk was changed */
DECL|macro|MCDX_RBIT_CHECK
mdefine_line|#define MCDX_RBIT_CHECK      0x10&t;/* disk rotates, servo is on */
DECL|macro|MCDX_RBIT_AUDIOTR
mdefine_line|#define MCDX_RBIT_AUDIOTR    0x08&t;/* current track is audio */
DECL|macro|MCDX_RBIT_RDERR
mdefine_line|#define MCDX_RBIT_RDERR      0x04&t;/* read error, refer SENSE KEY */
DECL|macro|MCDX_RBIT_AUDIOBS
mdefine_line|#define MCDX_RBIT_AUDIOBS    0x02&t;/* currently playing audio */
DECL|macro|MCDX_RBIT_CMDERR
mdefine_line|#define MCDX_RBIT_CMDERR     0x01&t;/* command, param or format error */
multiline_comment|/* &n; * The I/O Register holding the h/w status of the drive,&n; * can be read at i/o base + 1 &n; */
DECL|macro|MCDX_RBIT_DOOR
mdefine_line|#define MCDX_RBIT_DOOR       0x10&t;/* door is open */
DECL|macro|MCDX_RBIT_STEN
mdefine_line|#define MCDX_RBIT_STEN       0x04&t;/* if 0, i/o base contains drive status */
DECL|macro|MCDX_RBIT_DTEN
mdefine_line|#define MCDX_RBIT_DTEN       0x02&t;/* if 0, i/o base contains data */
multiline_comment|/*&n; *    The commands.&n; */
DECL|macro|MCDX_CMD_GET_TOC
mdefine_line|#define MCDX_CMD_GET_TOC&t;&t;0x10
DECL|macro|MCDX_CMD_GET_MDISK_INFO
mdefine_line|#define MCDX_CMD_GET_MDISK_INFO&t;&t;0x11
DECL|macro|MCDX_CMD_GET_SUBQ_CODE
mdefine_line|#define MCDX_CMD_GET_SUBQ_CODE&t;&t;0x20
DECL|macro|MCDX_CMD_GET_STATUS
mdefine_line|#define MCDX_CMD_GET_STATUS&t;&t;0x40
DECL|macro|MCDX_CMD_SET_DRIVE_MODE
mdefine_line|#define MCDX_CMD_SET_DRIVE_MODE&t;&t;0x50
DECL|macro|MCDX_CMD_RESET
mdefine_line|#define MCDX_CMD_RESET&t;&t;&t;0x60
DECL|macro|MCDX_CMD_HOLD
mdefine_line|#define MCDX_CMD_HOLD&t;&t;&t;0x70
DECL|macro|MCDX_CMD_CONFIG
mdefine_line|#define MCDX_CMD_CONFIG&t;&t;&t;0x90
DECL|macro|MCDX_CMD_SET_ATTENATOR
mdefine_line|#define MCDX_CMD_SET_ATTENATOR&t;&t;0xae
DECL|macro|MCDX_CMD_PLAY
mdefine_line|#define MCDX_CMD_PLAY&t;&t;&t;0xc0
DECL|macro|MCDX_CMD_PLAY_2X
mdefine_line|#define MCDX_CMD_PLAY_2X&t;&t;0xc1
DECL|macro|MCDX_CMD_GET_DRIVE_MODE
mdefine_line|#define MCDX_CMD_GET_DRIVE_MODE&t;&t;0xc2
DECL|macro|MCDX_CMD_SET_INTERLEAVE
mdefine_line|#define MCDX_CMD_SET_INTERLEAVE&t;&t;0xc8
DECL|macro|MCDX_CMD_GET_FIRMWARE
mdefine_line|#define MCDX_CMD_GET_FIRMWARE&t;&t;0xdc
DECL|macro|MCDX_CMD_SET_DATA_MODE
mdefine_line|#define MCDX_CMD_SET_DATA_MODE&t;&t;0xa0
DECL|macro|MCDX_CMD_STOP
mdefine_line|#define MCDX_CMD_STOP&t;&t;&t;0xf0
DECL|macro|MCDX_CMD_EJECT
mdefine_line|#define MCDX_CMD_EJECT&t;&t;&t;0xf6
DECL|macro|MCDX_CMD_CLOSE_DOOR
mdefine_line|#define MCDX_CMD_CLOSE_DOOR&t;&t;0xf8
DECL|macro|MCDX_CMD_LOCK_DOOR
mdefine_line|#define MCDX_CMD_LOCK_DOOR&t;&t;0xfe
DECL|macro|READ_AHEAD
mdefine_line|#define READ_AHEAD&t;&t;&t;8&t;/* 16 Sectors (4K) */
macro_line|#ifndef I_WAS_IN_MCDX_H
macro_line|#warning You have not edited mcdx.h
macro_line|#warning Perhaps irq and i/o settings are wrong.
macro_line|#endif
macro_line|#endif &t;/* __MCDX_H */
eof
