macro_line|#ifndef _QIC117_H
DECL|macro|_QIC117_H
mdefine_line|#define _QIC117_H
multiline_comment|/*&n; *      Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/qic117.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.27 $&n; $Date: 1995/05/01 19:02:20 $&n; $State: Beta $&n; *&n; *      This file contains QIC-117 spec. related definitions&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; *&n; *      These data were taken from the Quarter-Inch Cartridge&n; *      Drive Standards, Inc. document titled:&n; *      `Common Command Set Interface Specification for Flexible&n; *       Disk Controller Based Minicartridge Tape Drives&squot;&n; *       document QIC-117 Revision C, 3 Dec 92.&n; *      For more information, contact:&n; *       Quarter-Inch Cartridge Drive Standards, Inc.&n; *       311 East Carrillo Street&n; *       Santa Barbara, California 93101&n; *       Telephone (805) 963-3853&n; *       Fax       (805) 962-1541&n; *&n; *      Current QIC standard revisions (of interest) are:&n; *       QIC-80-MC,   Rev. M, 15 Jun 95.&n; *       QIC-117,     Rev. I, 15 Mar 95.&n; *       QIC-122,     Rev. B,  6 Mar 91.&n; *       QIC-130,     Rev. C,  2 Sep 92.&n; *       QIC-3010-MC, Rev. F, 14 Jun 95.&n; *       QIC-3020-MC, Rev. G, 31 Aug 95.&n; *       QIC-CRF3,    Rev. B, 15 Jun 95.&n; *&n; */
multiline_comment|/*&n; *      QIC-117 common command set rev. I.&n; *      These commands are sent to the tape unit&n; *      as number of pulses over the step line.&n; */
DECL|macro|QIC_RESET
mdefine_line|#define QIC_RESET&t;&t;&t;1
DECL|macro|QIC_REPORT_NEXT_BIT
mdefine_line|#define QIC_REPORT_NEXT_BIT&t;&t;2
DECL|macro|QIC_PAUSE
mdefine_line|#define QIC_PAUSE&t;&t;&t;3
DECL|macro|QIC_MICRO_STEP_PAUSE
mdefine_line|#define QIC_MICRO_STEP_PAUSE&t;&t;4
DECL|macro|QIC_ALTERNATE_TIMEOUT
mdefine_line|#define QIC_ALTERNATE_TIMEOUT&t;&t;5
DECL|macro|QIC_REPORT_DRIVE_STATUS
mdefine_line|#define QIC_REPORT_DRIVE_STATUS&t;&t;6
DECL|macro|QIC_REPORT_ERROR_CODE
mdefine_line|#define QIC_REPORT_ERROR_CODE&t;&t;7
DECL|macro|QIC_REPORT_DRIVE_CONFIGURATION
mdefine_line|#define QIC_REPORT_DRIVE_CONFIGURATION&t;8
DECL|macro|QIC_REPORT_ROM_VERSION
mdefine_line|#define QIC_REPORT_ROM_VERSION&t;&t;9
DECL|macro|QIC_LOGICAL_FORWARD
mdefine_line|#define QIC_LOGICAL_FORWARD&t;&t;10
DECL|macro|QIC_PHYSICAL_REVERSE
mdefine_line|#define QIC_PHYSICAL_REVERSE&t;&t;11
DECL|macro|QIC_PHYSICAL_FORWARD
mdefine_line|#define QIC_PHYSICAL_FORWARD&t;&t;12
DECL|macro|QIC_SEEK_HEAD_TO_TRACK
mdefine_line|#define QIC_SEEK_HEAD_TO_TRACK&t;&t;13
DECL|macro|QIC_SEEK_LOAD_POINT
mdefine_line|#define QIC_SEEK_LOAD_POINT&t;&t;14
DECL|macro|QIC_ENTER_FORMAT_MODE
mdefine_line|#define QIC_ENTER_FORMAT_MODE&t;&t;15
DECL|macro|QIC_WRITE_REFERENCE_BURST
mdefine_line|#define QIC_WRITE_REFERENCE_BURST&t;16
DECL|macro|QIC_ENTER_VERIFY_MODE
mdefine_line|#define QIC_ENTER_VERIFY_MODE&t;&t;17
DECL|macro|QIC_STOP_TAPE
mdefine_line|#define QIC_STOP_TAPE&t;&t;&t;18
multiline_comment|/* commands 19-20: reserved */
DECL|macro|QIC_MICRO_STEP_HEAD_UP
mdefine_line|#define QIC_MICRO_STEP_HEAD_UP&t;&t;21
DECL|macro|QIC_MICRO_STEP_HEAD_DOWN
mdefine_line|#define QIC_MICRO_STEP_HEAD_DOWN&t;22
DECL|macro|QIC_SOFT_SELECT
mdefine_line|#define QIC_SOFT_SELECT&t;&t;&t;23
DECL|macro|QIC_SOFT_DESELECT
mdefine_line|#define QIC_SOFT_DESELECT&t;&t;24
DECL|macro|QIC_SKIP_REVERSE
mdefine_line|#define QIC_SKIP_REVERSE&t;&t;25
DECL|macro|QIC_SKIP_FORWARD
mdefine_line|#define QIC_SKIP_FORWARD&t;&t;26
DECL|macro|QIC_SELECT_RATE
mdefine_line|#define QIC_SELECT_RATE&t;&t;&t;27
multiline_comment|/* command 27, in ccs2: Select Rate or Format */
DECL|macro|QIC_ENTER_DIAGNOSTIC_1
mdefine_line|#define QIC_ENTER_DIAGNOSTIC_1&t;&t;28
DECL|macro|QIC_ENTER_DIAGNOSTIC_2
mdefine_line|#define QIC_ENTER_DIAGNOSTIC_2&t;&t;29
DECL|macro|QIC_ENTER_PRIMARY_MODE
mdefine_line|#define QIC_ENTER_PRIMARY_MODE&t;&t;30
multiline_comment|/* command 31: vendor unique */
DECL|macro|QIC_REPORT_VENDOR_ID
mdefine_line|#define QIC_REPORT_VENDOR_ID&t;&t;32
DECL|macro|QIC_REPORT_TAPE_STATUS
mdefine_line|#define QIC_REPORT_TAPE_STATUS&t;&t;33
DECL|macro|QIC_SKIP_EXTENDED_REVERSE
mdefine_line|#define QIC_SKIP_EXTENDED_REVERSE&t;34
DECL|macro|QIC_SKIP_EXTENDED_FORWARD
mdefine_line|#define QIC_SKIP_EXTENDED_FORWARD&t;35
DECL|macro|QIC_CALIBRATE_TAPE_LENGTH
mdefine_line|#define QIC_CALIBRATE_TAPE_LENGTH&t;36
DECL|macro|QIC_REPORT_FORMAT_SEGMENTS
mdefine_line|#define QIC_REPORT_FORMAT_SEGMENTS&t;37
DECL|macro|QIC_SET_FORMAT_SEGMENTS
mdefine_line|#define QIC_SET_FORMAT_SEGMENTS&t;&t;38
multiline_comment|/* commands 39-45: reserved */
DECL|macro|QIC_PHANTOM_SELECT
mdefine_line|#define QIC_PHANTOM_SELECT&t;&t;46
DECL|macro|QIC_PHANTOM_DESELECT
mdefine_line|#define QIC_PHANTOM_DESELECT&t;&t;47
r_typedef
r_enum
(brace
DECL|enumerator|discretional
DECL|enumerator|required
DECL|enumerator|ccs1
DECL|enumerator|ccs2
id|discretional
op_assign
l_int|0
comma
id|required
comma
id|ccs1
comma
id|ccs2
DECL|typedef|qic_compatibility
)brace
id|qic_compatibility
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|unused
DECL|enumerator|mode
DECL|enumerator|motion
DECL|enumerator|report
id|unused
comma
id|mode
comma
id|motion
comma
id|report
DECL|typedef|command_types
)brace
id|command_types
suffix:semicolon
DECL|struct|qic117_command_table
r_struct
id|qic117_command_table
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mask
id|byte
id|mask
suffix:semicolon
DECL|member|state
id|byte
id|state
suffix:semicolon
DECL|member|cmd_type
id|byte
id|cmd_type
suffix:semicolon
DECL|member|non_intr
id|byte
id|non_intr
suffix:semicolon
DECL|member|level
id|byte
id|level
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|QIC117_COMMANDS
mdefine_line|#define QIC117_COMMANDS {&bslash;&n;/* command                           mask  state cmd_type           */&bslash;&n;/* |    name                         |     |     |       non_intr   */&bslash;&n;/* |    |                            |     |     |       |  level   */&bslash;&n;/* 0*/ {NULL,                        0x00, 0x00, mode,   0, discretional},&bslash;&n;/* 1*/ {&quot;soft reset&quot;,                0x00, 0x00, motion, 1, required},&bslash;&n;/* 2*/ {&quot;report next bit&quot;,           0x00, 0x00, report, 0, required},&bslash;&n;/* 3*/ {&quot;pause&quot;,                     0x36, 0x24, motion, 1, required},&bslash;&n;/* 4*/ {&quot;micro step pause&quot;,          0x36, 0x24, motion, 1, required},&bslash;&n;/* 5*/ {&quot;alternate command timeout&quot;, 0x00, 0x00, mode,   0, required},&bslash;&n;/* 6*/ {&quot;report drive status&quot;,       0x00, 0x00, report, 0, required},&bslash;&n;/* 7*/ {&quot;report error code&quot;,         0x01, 0x01, report, 0, required},&bslash;&n;/* 8*/ {&quot;report drive configuration&quot;,0x00, 0x00, report, 0, required},&bslash;&n;/* 9*/ {&quot;report rom version&quot;,        0x00, 0x00, report, 0, required},&bslash;&n;/*10*/ {&quot;logical forward&quot;,           0x37, 0x25, motion, 0, required},&bslash;&n;/*11*/ {&quot;physical reverse&quot;,          0x17, 0x05, motion, 0, required},&bslash;&n;/*12*/ {&quot;physical forward&quot;,          0x17, 0x05, motion, 0, required},&bslash;&n;/*13*/ {&quot;seek head to track&quot;,        0x37, 0x25, motion, 0, required},&bslash;&n;/*14*/ {&quot;seek load point&quot;,           0x17, 0x05, motion, 1, required},&bslash;&n;/*15*/ {&quot;enter format mode&quot;,         0x1f, 0x05, mode,   0, required},&bslash;&n;/*16*/ {&quot;write reference burst&quot;,     0x1f, 0x05, motion, 1, required},&bslash;&n;/*17*/ {&quot;enter verify mode&quot;,         0x37, 0x25, mode,   0, required},&bslash;&n;/*18*/ {&quot;stop tape&quot;,                 0x00, 0x00, motion, 1, required},&bslash;&n;/*19*/ {&quot;reserved (19)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*20*/ {&quot;reserved (20)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*21*/ {&quot;micro step head up&quot;,        0x02, 0x00, motion, 0, required},&bslash;&n;/*22*/ {&quot;micro step head down&quot;,      0x02, 0x00, motion, 0, required},&bslash;&n;/*23*/ {&quot;soft select&quot;,               0x00, 0x00, mode,   0, discretional},&bslash;&n;/*24*/ {&quot;soft deselect&quot;,             0x00, 0x00, mode,   0, discretional},&bslash;&n;/*25*/ {&quot;skip segments reverse&quot;,     0x36, 0x24, motion, 1, required},&bslash;&n;/*26*/ {&quot;skip segments forward&quot;,     0x36, 0x24, motion, 1, required},&bslash;&n;/*27*/ {&quot;select rate [or format]&quot;,   0x03, 0x01, mode,   0, required /* [ccs2] */},&bslash;&n;/*28*/ {&quot;enter diag mode 1&quot;,         0x00, 0x00, mode,   0, discretional},&bslash;&n;/*29*/ {&quot;enter diag mode 2&quot;,         0x00, 0x00, mode,   0, discretional},&bslash;&n;/*30*/ {&quot;enter primary mode&quot;,        0x00, 0x00, mode,   0, required},&bslash;&n;/*31*/ {&quot;vendor unique (31)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*32*/ {&quot;report vendor id&quot;,          0x00, 0x00, report, 0, required},&bslash;&n;/*33*/ {&quot;report tape status&quot;,        0x04, 0x04, report, 0, ccs1},&bslash;&n;/*34*/ {&quot;skip extended reverse&quot;,     0x36, 0x24, motion, 1, ccs1},&bslash;&n;/*35*/ {&quot;skip extended forward&quot;,     0x36, 0x24, motion, 1, ccs1},&bslash;&n;/*36*/ {&quot;calibrate tape length&quot;,     0x17, 0x05, motion, 1, ccs2},&bslash;&n;/*37*/ {&quot;report format segments&quot;,    0x17, 0x05, report, 0, ccs2},&bslash;&n;/*38*/ {&quot;set format segments&quot;,       0x17, 0x05, mode,   0, ccs2},&bslash;&n;/*39*/ {&quot;reserved (39)&quot;,             0x00, 0x00, unused, 0, discretional},&bslash;&n;/*40*/ {&quot;vendor unique (40)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*41*/ {&quot;vendor unique (41)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*42*/ {&quot;vendor unique (42)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*43*/ {&quot;vendor unique (43)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*44*/ {&quot;vendor unique (44)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*45*/ {&quot;vendor unique (45)&quot;,        0x00, 0x00, unused, 0, discretional},&bslash;&n;/*46*/ {&quot;phantom select&quot;,            0x00, 0x00, mode,   0, discretional},&bslash;&n;/*47*/ {&quot;phantom deselect&quot;,          0x00, 0x00, mode,   0, discretional},&bslash;&n;}
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_DRIVE_STATUS&n; */
DECL|macro|QIC_STATUS_READY
mdefine_line|#define QIC_STATUS_READY&t;0x01&t;/* Drive is ready or idle. */
DECL|macro|QIC_STATUS_ERROR
mdefine_line|#define QIC_STATUS_ERROR&t;0x02&t;/* Error detected, must read&n;&t;&t;&t;&t;&t;   error code to clear this */
DECL|macro|QIC_STATUS_CARTRIDGE_PRESENT
mdefine_line|#define QIC_STATUS_CARTRIDGE_PRESENT 0x04&t;/* Tape is present */
DECL|macro|QIC_STATUS_WRITE_PROTECT
mdefine_line|#define QIC_STATUS_WRITE_PROTECT 0x08&t;/* Tape is write protected */
DECL|macro|QIC_STATUS_NEW_CARTRIDGE
mdefine_line|#define QIC_STATUS_NEW_CARTRIDGE 0x10&t;/* New cartridge inserted, must&n;&t;&t;&t;&t;&t;   read error status to clear. */
DECL|macro|QIC_STATUS_REFERENCED
mdefine_line|#define QIC_STATUS_REFERENCED&t;0x20&t;/* Cartridge appears to have been&n;&t;&t;&t;&t;&t;   formatted. */
DECL|macro|QIC_STATUS_AT_BOT
mdefine_line|#define QIC_STATUS_AT_BOT&t;0x40&t;/* Cartridge is at physical&n;&t;&t;&t;&t;&t;   beginning of tape. */
DECL|macro|QIC_STATUS_AT_EOT
mdefine_line|#define QIC_STATUS_AT_EOT&t;0x80&t;/* Cartridge is at physical end&n;&t;&t;&t;&t;&t;   of tape. */
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_DRIVE_CONFIGURATION&n; */
DECL|macro|QIC_CONFIG_RATE_MASK
mdefine_line|#define QIC_CONFIG_RATE_MASK&t;0x18
DECL|macro|QIC_CONFIG_RATE_SHIFT
mdefine_line|#define QIC_CONFIG_RATE_SHIFT&t;3
DECL|macro|QIC_CONFIG_RATE_250
mdefine_line|#define QIC_CONFIG_RATE_250&t;0
DECL|macro|QIC_CONFIG_RATE_500
mdefine_line|#define QIC_CONFIG_RATE_500&t;2
DECL|macro|QIC_CONFIG_RATE_1000
mdefine_line|#define QIC_CONFIG_RATE_1000&t;3
DECL|macro|QIC_CONFIG_RATE_2000
mdefine_line|#define QIC_CONFIG_RATE_2000&t;1
DECL|macro|QIC_CONFIG_LONG
mdefine_line|#define QIC_CONFIG_LONG&t;&t;0x40&t;/* Extra Length Tape Detected */
DECL|macro|QIC_CONFIG_80
mdefine_line|#define QIC_CONFIG_80&t;&t;0x80&t;/* QIC-80 detected. */
multiline_comment|/*&n; *      Status bits returned by QIC_REPORT_TAPE_STATUS&n; */
DECL|macro|QIC_TAPE_STD_MASK
mdefine_line|#define QIC_TAPE_STD_MASK       0x0f
DECL|macro|QIC_TAPE_QIC40
mdefine_line|#define QIC_TAPE_QIC40  &t;0x01
DECL|macro|QIC_TAPE_QIC80
mdefine_line|#define QIC_TAPE_QIC80  &t;0x02
DECL|macro|QIC_TAPE_QIC3020
mdefine_line|#define QIC_TAPE_QIC3020  &t;0x03
DECL|macro|QIC_TAPE_QIC3010
mdefine_line|#define QIC_TAPE_QIC3010  &t;0x04
DECL|macro|QIC_TAPE_LEN_MASK
mdefine_line|#define QIC_TAPE_LEN_MASK       0x70
DECL|macro|QIC_TAPE_205FT
mdefine_line|#define QIC_TAPE_205FT          0x10
DECL|macro|QIC_TAPE_307FT
mdefine_line|#define QIC_TAPE_307FT          0x20
DECL|macro|QIC_TAPE_400FT
mdefine_line|#define QIC_TAPE_400FT          0x30
DECL|macro|QIC_TAPE_1100FT
mdefine_line|#define QIC_TAPE_1100FT         0x40
DECL|macro|QIC_TAPE_FLEX
mdefine_line|#define QIC_TAPE_FLEX&t;&t;0x60
DECL|macro|QIC_TAPE_WIDE
mdefine_line|#define QIC_TAPE_WIDE&t;&t;0x80
multiline_comment|/*&n; *      Errors: List of error codes, and their severity.&n; */
r_typedef
r_struct
(brace
DECL|member|message
r_char
op_star
id|message
suffix:semicolon
multiline_comment|/* Text describing the error. */
DECL|member|fatal
r_int
id|fatal
suffix:semicolon
multiline_comment|/* Non-zero if the error is fatal. */
DECL|typedef|ftape_error
)brace
id|ftape_error
suffix:semicolon
DECL|macro|QIC117_ERRORS
mdefine_line|#define QIC117_ERRORS {&bslash;&n;  /* 0*/ { &quot;No error&quot;, 0, },&bslash;&n;  /* 1*/ { &quot;Command Received while Drive Not Ready&quot;, 0, },&bslash;&n;  /* 2*/ { &quot;Cartridge Not Present or Removed&quot;, 1, },&bslash;&n;  /* 3*/ { &quot;Motor Speed Error (not within 1%)&quot;, 1, },&bslash;&n;  /* 4*/ { &quot;Motor Speed Fault (jammed, or gross speed error&quot;, 1, },&bslash;&n;  /* 5*/ { &quot;Cartridge Write Protected&quot;, 1, },&bslash;&n;  /* 6*/ { &quot;Undefined or Reserved Command Code&quot;, 1, },&bslash;&n;  /* 7*/ { &quot;Illegal Track Address Specified for Seek&quot;, 1, },&bslash;&n;  /* 8*/ { &quot;Illegal Command in Report Subcontext&quot;, 0, },&bslash;&n;  /* 9*/ { &quot;Illegal Entry into a Diagnostic Mode&quot;, 1, },&bslash;&n;  /*10*/ { &quot;Broken Tape Detected (based on hole sensor)&quot;, 1, },&bslash;&n;  /*11*/ { &quot;Warning--Read Gain Setting Error&quot;, 1, },&bslash;&n;  /*12*/ { &quot;Command Received While Error Status Pending (obs)&quot;, 1, },&bslash;&n;  /*13*/ { &quot;Command Received While New Cartridge Pending&quot;, 1, },&bslash;&n;  /*14*/ { &quot;Command Illegal or Undefined in Primary Mode&quot;, 1, },&bslash;&n;  /*15*/ { &quot;Command Illegal or Undefined in Format Mode&quot;, 1, },&bslash;&n;  /*16*/ { &quot;Command Illegal or Undefined in Verify Mode&quot;, 1, },&bslash;&n;  /*17*/ { &quot;Logical Forward Not a Logical BOT or no Format Segments in Format Mode&quot;, 1, },&bslash;&n;  /*18*/ { &quot;Logical EOT Before All Segments generated&quot;, 1, },&bslash;&n;  /*19*/ { &quot;Command Illegal When Cartridge Not Referenced&quot;, 1, },&bslash;&n;  /*20*/ { &quot;Self-Diagnostic Failed (cannot be cleared)&quot;, 1, },&bslash;&n;  /*21*/ { &quot;Warning EEPROM Not Initialized, Defaults Set&quot;, 1, },&bslash;&n;  /*22*/ { &quot;EEPROM Corrupted or Hardware Failure&quot;, 1, },&bslash;&n;  /*23*/ { &quot;Motion Time-out Error&quot;, 1, },&bslash;&n;  /*24*/ { &quot;Data Segment Too Long -- Logical Forward or Pause&quot;, 1, },&bslash;&n;  /*25*/ { &quot;Transmit Overrun (obs)&quot;, 1, },&bslash;&n;  /*26*/ { &quot;Power On Reset Occurred&quot;, 0, },&bslash;&n;  /*27*/ { &quot;Software Reset Occurred&quot;, 0, },&bslash;&n;  /*28*/ { &quot;Diagnostic Mode 1 Error&quot;, 1, },&bslash;&n;  /*29*/ { &quot;Diagnostic Mode 2 Error&quot;, 1, },&bslash;&n;  /*30*/ { &quot;Command Received During Non-Interruptable Process&quot;, 1, },&bslash;&n;  /*31*/ { &quot;Rate or Format Selection Error&quot;, 1, },&bslash;&n;  /*32*/ { &quot;Illegal Command While in High Speed Mode&quot;, 1, },&bslash;&n;  /*33*/ { &quot;Illegal Seek Segment Value&quot;, 1, },&bslash;&n;  /*34*/ { &quot;Invalid Media&quot;, 1, },&bslash;&n;  /*35*/ { &quot;Head Positioning Failure&quot;, 1, },&bslash;&n;  /*36*/ { &quot;Write Reference Burst Failure&quot;, 1, },&bslash;&n;  /*37*/ { &quot;Prom Code Missing&quot;, 1, },&bslash;&n;  /*38*/ { &quot;Invalid Format&quot;, 1, },&bslash;&n;  /*39*/ { &quot;EOT/BOT System Failure&quot;, 1, },&bslash;&n;  /*40*/ { &quot;Prom A Checksum Error&quot;, 1, },&bslash;&n;  /*41*/ { &quot;Drive Wakeup Reset Occurred&quot;, 1, },&bslash;&n;  /*42*/ { &quot;Prom B Checksum Error&quot;, 1, },&bslash;&n;  /*43*/ { &quot;Illegal Entry into Format Mode&quot;, 1, },&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _QIC117_H */
eof
