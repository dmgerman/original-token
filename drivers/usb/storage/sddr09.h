multiline_comment|/* Driver for SanDisk SDDR-09 SmartMedia reader&n; * Header File&n; *&n; * Current development and maintainance by:&n; *   (c) 2000 Robert Baruch (autophile@dol.net)&n; *&n; * See sddr09.c for more explanation&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_SHUTTLE_EUSB_SDDR09_H
DECL|macro|_USB_SHUTTLE_EUSB_SDDR09_H
mdefine_line|#define _USB_SHUTTLE_EUSB_SDDR09_H
multiline_comment|/* Sandisk SDDR-09 stuff */
r_extern
r_int
id|sddr09_transport
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
suffix:semicolon
DECL|struct|sddr09_card_info
r_struct
id|sddr09_card_info
(brace
DECL|member|capacity
r_int
r_int
id|capacity
suffix:semicolon
multiline_comment|/* Size of card in bytes */
DECL|member|pagesize
r_int
id|pagesize
suffix:semicolon
multiline_comment|/* Size of page in bytes */
DECL|member|lba_to_pba
r_int
op_star
id|lba_to_pba
suffix:semicolon
multiline_comment|/* logical to physical map */
DECL|member|pba_to_lba
r_int
op_star
id|pba_to_lba
suffix:semicolon
multiline_comment|/* physical to logical map */
)brace
suffix:semicolon
macro_line|#endif
eof
