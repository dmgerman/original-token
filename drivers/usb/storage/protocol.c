multiline_comment|/* Driver for USB Mass Storage compliant devices&n; *&n; * $Id: protocol.c,v 1.4 2000/08/01 22:01:19 mdharm Exp $&n; *&n; * Current development and maintainance by:&n; *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Developed with the assistance of:&n; *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)&n; *&n; * Initial work by:&n; *   (c) 1999 Michael Gee (michael@linuxspecific.com)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;scsiglue.h&quot;
macro_line|#include &quot;transport.h&quot;
multiline_comment|/***********************************************************************&n; * Helper routines&n; ***********************************************************************/
multiline_comment|/* Fix-up the return data from an INQUIRY command to show &n; * ANSI SCSI rev 2 so we don&squot;t confuse the SCSI layers above us&n; */
DECL|function|fix_inquiry_data
r_void
id|fix_inquiry_data
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
(brace
r_int
r_char
op_star
id|data_ptr
suffix:semicolon
multiline_comment|/* verify that it&squot;s an INQUIRY command */
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_ne
id|INQUIRY
)paren
r_return
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Fixing INQUIRY data to show SCSI rev 2&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* find the location of the data */
r_if
c_cond
(paren
id|srb-&gt;use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|srb-&gt;request_buffer
suffix:semicolon
id|data_ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|sg
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
)brace
r_else
id|data_ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|srb-&gt;request_buffer
suffix:semicolon
multiline_comment|/* Change the SCSI revision number */
id|data_ptr
(braket
l_int|2
)braket
op_or_assign
l_int|0x2
suffix:semicolon
)brace
multiline_comment|/***********************************************************************&n; * Protocol routines&n; ***********************************************************************/
DECL|function|usb_stor_qic157_command
r_void
id|usb_stor_qic157_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
multiline_comment|/* Pad the ATAPI command with zeros &n;&t; * NOTE: This only works because a Scsi_Cmnd struct field contains&n;&t; * a unsigned char cmnd[12], so we know we have storage available&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|srb-&gt;cmd_len
OL
l_int|12
suffix:semicolon
id|srb-&gt;cmd_len
op_increment
)paren
id|srb-&gt;cmnd
(braket
id|srb-&gt;cmd_len
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set command length to 12 bytes */
id|srb-&gt;cmd_len
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* send the command to the transport layer */
id|usb_stor_invoke_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
multiline_comment|/* fix the INQUIRY data if necessary */
id|fix_inquiry_data
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
DECL|function|usb_stor_ATAPI_command
r_void
id|usb_stor_ATAPI_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
id|old_cmnd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Fix some commands -- this is a form of mode translation&n;&t; * ATAPI devices only accept 12 byte long commands &n;&t; *&n;&t; * NOTE: This only works because a Scsi_Cmnd struct field contains&n;&t; * a unsigned char cmnd[12], so we know we have storage available&n;&t; */
multiline_comment|/* Pad the ATAPI command with zeros */
r_for
c_loop
(paren
suffix:semicolon
id|srb-&gt;cmd_len
OL
l_int|12
suffix:semicolon
id|srb-&gt;cmd_len
op_increment
)paren
id|srb-&gt;cmnd
(braket
id|srb-&gt;cmd_len
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set command length to 12 bytes */
id|srb-&gt;cmd_len
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* determine the correct (or minimum) data length for these commands */
r_switch
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* change MODE_SENSE/MODE_SELECT from 6 to 10 byte commands */
r_case
id|MODE_SENSE
suffix:colon
r_case
id|MODE_SELECT
suffix:colon
multiline_comment|/* save the command so we can tell what it was */
id|old_cmnd
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|4
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_or
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* change READ_6/WRITE_6 to READ_10/WRITE_10, which &n;&t;&t; * are ATAPI commands */
r_case
id|WRITE_6
suffix:colon
r_case
id|READ_6
suffix:colon
id|srb-&gt;cmnd
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|4
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|3
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0x1F
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0xE0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_or
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* end switch on cmnd[0] */
multiline_comment|/* convert MODE_SELECT data here */
r_if
c_cond
(paren
id|old_cmnd
op_eq
id|MODE_SELECT
)paren
id|usb_stor_scsiSense6to10
c_func
(paren
id|srb
)paren
suffix:semicolon
multiline_comment|/* send the command to the transport layer */
id|usb_stor_invoke_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
multiline_comment|/* Fix the MODE_SENSE data if we translated the command */
r_if
c_cond
(paren
(paren
id|old_cmnd
op_eq
id|MODE_SENSE
)paren
op_logical_and
(paren
id|srb-&gt;result
op_eq
id|GOOD
)paren
)paren
id|usb_stor_scsiSense10to6
c_func
(paren
id|srb
)paren
suffix:semicolon
multiline_comment|/* fix the INQUIRY data if necessary */
id|fix_inquiry_data
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
DECL|function|usb_stor_ufi_command
r_void
id|usb_stor_ufi_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
id|old_cmnd
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* fix some commands -- this is a form of mode translation&n;&t; * UFI devices only accept 12 byte long commands &n;&t; *&n;&t; * NOTE: This only works because a Scsi_Cmnd struct field contains&n;&t; * a unsigned char cmnd[12], so we know we have storage available&n;&t; */
multiline_comment|/* set command length to 12 bytes (this affects the transport layer) */
id|srb-&gt;cmd_len
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* determine the correct (or minimum) data length for these commands */
r_switch
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* for INQUIRY, UFI devices only ever return 36 bytes */
r_case
id|INQUIRY
suffix:colon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
l_int|36
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* change MODE_SENSE/MODE_SELECT from 6 to 10 byte commands */
r_case
id|MODE_SENSE
suffix:colon
r_case
id|MODE_SELECT
suffix:colon
multiline_comment|/* save the command so we can tell what it was */
id|old_cmnd
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if we&squot;re sending data, we send all.&t;If getting data, &n;&t;&t; * get the minimum */
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|MODE_SELECT
)paren
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|4
)braket
suffix:semicolon
r_else
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
l_int|8
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_or
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* again, for MODE_SENSE_10, we get the minimum (8) */
r_case
id|MODE_SENSE_10
suffix:colon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* for REQUEST_SENSE, UFI devices only ever return 18 bytes */
r_case
id|REQUEST_SENSE
suffix:colon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
l_int|18
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* change READ_6/WRITE_6 to READ_10/WRITE_10, which &n;&t;&t; * are UFI commands */
r_case
id|WRITE_6
suffix:colon
r_case
id|READ_6
suffix:colon
id|srb-&gt;cmnd
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|4
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|3
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0x1F
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|1
)braket
op_amp
l_int|0xE0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_or
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* end switch on cmnd[0] */
multiline_comment|/* convert MODE_SELECT data here */
r_if
c_cond
(paren
id|old_cmnd
op_eq
id|MODE_SELECT
)paren
id|usb_stor_scsiSense6to10
c_func
(paren
id|srb
)paren
suffix:semicolon
multiline_comment|/* send the command to the transport layer */
id|usb_stor_invoke_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
multiline_comment|/* Fix the MODE_SENSE data if we translated the command */
r_if
c_cond
(paren
(paren
id|old_cmnd
op_eq
id|MODE_SENSE
)paren
op_logical_and
(paren
id|srb-&gt;result
op_eq
id|GOOD
)paren
)paren
id|usb_stor_scsiSense10to6
c_func
(paren
id|srb
)paren
suffix:semicolon
multiline_comment|/* Fix the data for an INQUIRY, if necessary */
id|fix_inquiry_data
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
DECL|function|usb_stor_transparent_scsi_command
r_void
id|usb_stor_transparent_scsi_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
multiline_comment|/* This code supports devices which do not support {READ|WRITE}_6&n;&t; * Apparently, neither Windows or MacOS will use these commands,&n;&t; * so some devices do not support them&n;&t; */
r_if
c_cond
(paren
id|us-&gt;flags
op_amp
id|US_FL_MODE_XLATE
)paren
(brace
multiline_comment|/* translate READ_6 to READ_10 */
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0x08
)paren
(brace
multiline_comment|/* get the control */
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* get the length */
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|6
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set the reserved area to 0 */
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* get LBA */
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|3
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* LUN and other info in cmnd[1] can stay */
multiline_comment|/* fix command code */
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
l_int|0x28
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Changing READ_6 to READ_10&bslash;n&quot;
)paren
suffix:semicolon
id|US_DEBUG
c_func
(paren
id|usb_stor_show_command
c_func
(paren
id|srb
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* translate WRITE_6 to WRITE_10 */
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
l_int|0x0A
)paren
(brace
multiline_comment|/* get the control */
id|srb-&gt;cmnd
(braket
l_int|9
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* get the length */
id|srb-&gt;cmnd
(braket
l_int|8
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|4
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set the reserved area to 0 */
id|srb-&gt;cmnd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* get LBA */
id|srb-&gt;cmnd
(braket
l_int|5
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|3
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|4
)braket
op_assign
id|us-&gt;srb-&gt;cmnd
(braket
l_int|2
)braket
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* LUN and other info in cmnd[1] can stay */
multiline_comment|/* fix command code */
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_assign
l_int|0x2A
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Changing WRITE_6 to WRITE_10&bslash;n&quot;
)paren
suffix:semicolon
id|US_DEBUG
c_func
(paren
id|usb_stor_show_command
c_func
(paren
id|us-&gt;srb
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* if (us-&gt;flags &amp; US_FL_MODE_XLATE) */
multiline_comment|/* send the command to the transport layer */
id|usb_stor_invoke_transport
c_func
(paren
id|srb
comma
id|us
)paren
suffix:semicolon
multiline_comment|/* fix the INQUIRY data if necessary */
id|fix_inquiry_data
c_func
(paren
id|srb
)paren
suffix:semicolon
)brace
eof
