macro_line|#ifndef _VENDORS_H
DECL|macro|_VENDORS_H
mdefine_line|#define _VENDORS_H
multiline_comment|/*&n; *      Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/vendors.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.34 $&n; $Date: 1995/05/27 08:54:21 $&n; $State: Beta $&n; *&n; *      This file contains the supported drive types&n; *      with their QIC-117 spec. vendor code and&n; *      drive dependent configuration information.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|unknown_wake_up
id|unknown_wake_up
op_assign
l_int|0
comma
DECL|enumerator|no_wake_up
id|no_wake_up
comma
DECL|enumerator|wake_up_colorado
id|wake_up_colorado
comma
DECL|enumerator|wake_up_mountain
id|wake_up_mountain
comma
DECL|enumerator|wake_up_insight
id|wake_up_insight
comma
DECL|typedef|wake_up_types
)brace
id|wake_up_types
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|wake_up
id|wake_up_types
id|wake_up
suffix:semicolon
multiline_comment|/* see wake_up_types */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Text describing the drive */
DECL|typedef|wakeup_method
)brace
id|wakeup_method
suffix:semicolon
multiline_comment|/*  Note: order of entries in WAKEUP_METHODS must be so that a variable&n; *        of type wake_up_types can be used as an index in the array.&n; */
DECL|macro|WAKEUP_METHODS
mdefine_line|#define WAKEUP_METHODS { &bslash;&n;  { unknown_wake_up,    &quot;Unknown&quot; }, &bslash;&n;  { no_wake_up,         &quot;None&quot; }, &bslash;&n;  { wake_up_colorado,   &quot;Colorado&quot; }, &bslash;&n;  { wake_up_mountain,   &quot;Mountain&quot; }, &bslash;&n;  { wake_up_insight,    &quot;Motor-on&quot; }, &bslash;&n;}
r_typedef
r_struct
(brace
DECL|member|vendor_id
r_int
r_int
id|vendor_id
suffix:semicolon
multiline_comment|/* vendor id from drive */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* maximum tape transport speed (ips) */
DECL|member|wake_up
id|wake_up_types
id|wake_up
suffix:semicolon
multiline_comment|/* see wake_up_types */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Text describing the drive */
DECL|typedef|vendor_struct
)brace
id|vendor_struct
suffix:semicolon
DECL|macro|UNKNOWN_VENDOR
mdefine_line|#define UNKNOWN_VENDOR (-1)
DECL|macro|QIC117_VENDORS
mdefine_line|#define QIC117_VENDORS { &bslash;&n;/* see _vendor_struct */ &bslash;&n;  { 0x00000,  82, wake_up_colorado,  &quot;Colorado DJ-10 (old)&quot; }, &bslash;&n;  { 0x00047,  90, wake_up_colorado,  &quot;Colorado DJ-10/DJ-20&quot; }, &bslash;&n;  { 0x011c2,  84, wake_up_colorado,  &quot;Colorado 700&quot; }, &bslash;&n;  { 0x011c3,  90, wake_up_colorado,  &quot;Colorado 1400&quot; }, &bslash;&n;  { 0x011c4,  84, wake_up_colorado,  &quot;Colorado DJ-10/DJ-20 (new)&quot; }, &bslash;&n;  { 0x011c5,  84, wake_up_colorado,  &quot;HP Colorado T1000&quot; }, &bslash;&n;  { 0x00005,  45, wake_up_mountain,  &quot;Archive 5580i&quot; }, &bslash;&n;  { 0x10005,  50, wake_up_insight,   &quot;Insight 80Mb, Irwin 80SX&quot; }, &bslash;&n;  { 0x00140,  74, wake_up_mountain,  &quot;Archive S.Hornet [Identity/Escom]&quot; }, &bslash;&n;  { 0x00146,  72, wake_up_mountain,  &quot;Archive 31250Q [Escom]&quot; }, &bslash;&n;  { 0x0014a, 100, wake_up_mountain,  &quot;Archive XL9250i [Conner/Escom]&quot; }, &bslash;&n;  { 0x0014c,  98, wake_up_mountain,  &quot;Conner C250MQT&quot; }, &bslash;&n;  { 0x0014e,  80, wake_up_mountain,  &quot;Conner C250MQ&quot; }, &bslash;&n;  { 0x00150,  80, wake_up_mountain,  &quot;Conner TSM420R/TST800R&quot; }, &bslash;&n;  { 0x00152,  80, wake_up_mountain,  &quot;Conner TSM850R&quot; }, &bslash;&n;  { 0x00156,  80, wake_up_mountain,  &quot;Conner TSM850R/1700R/TST3200R&quot; }, &bslash;&n;  { 0x00180,   0, wake_up_mountain,  &quot;Summit SE 150&quot; }, &bslash;&n;  { 0x00181,  85, wake_up_mountain,  &quot;Summit SE 250, Mountain FS8000&quot; }, &bslash;&n;  { 0x001c1,  82, no_wake_up,        &quot;Wangtek 3040F&quot; }, &bslash;&n;  { 0x001c8,  64, no_wake_up,        &quot;Wangtek 3080F&quot; }, &bslash;&n;  { 0x001c8,  64, wake_up_colorado,  &quot;Wangtek 3080F&quot; }, &bslash;&n;  { 0x001ca,  67, no_wake_up,        &quot;Wangtek 3080F (new)&quot; }, &bslash;&n;  { 0x001cc,  77, wake_up_colorado,  &quot;Wangtek 3200&quot; }, &bslash;&n;  { 0x001cd,  75, wake_up_colorado,  &quot;Reveal TB1400&quot; }, &bslash;&n;  { 0x00380,   0, wake_up_colorado,  &quot;Exabyte EXB-1500&quot; }, &bslash;&n;  { 0x08880,  64, no_wake_up,        &quot;Iomega 250&quot; }, &bslash;&n;  { 0x08880,  64, wake_up_colorado,  &quot;Iomega 250, Ditto 800&quot; }, &bslash;&n;  { 0x08880,  64, wake_up_insight,   &quot;Iomega 250&quot; }, &bslash;&n;  { 0x08881,   0, wake_up_colorado,  &quot;Iomega 700&quot; }, &bslash;&n;  { 0x08882,  80, wake_up_colorado,  &quot;Iomega 3200&quot; }, &bslash;&n;  { 0x00021,  70, no_wake_up,        &quot;AIWA CT-803&quot; }, &bslash;&n;  { 0x00021,   0, wake_up_mountain,  &quot;COREtape QIC80&quot; }, &bslash;&n;}
DECL|macro|QIC117_MAKE_CODES
mdefine_line|#define QIC117_MAKE_CODES { &bslash;&n;  { 0, &quot;Unassigned&quot; }, &bslash;&n;  { 1, &quot;Alloy Computer Products&quot; }, &bslash;&n;  { 2, &quot;3M&quot; }, &bslash;&n;  { 3, &quot;Tandberg Data&quot; }, &bslash;&n;  { 4, &quot;Colorado&quot; }, &bslash;&n;  { 5, &quot;Archive/Conner&quot; }, &bslash;&n;  { 6, &quot;Mountain/Summit Memory Systems&quot; }, &bslash;&n;  { 7, &quot;Wangtek/Rexon/Tecmar&quot; }, &bslash;&n;  { 8, &quot;Sony&quot; }, &bslash;&n;  { 9, &quot;Cipher Data Products&quot; }, &bslash;&n;  { 10, &quot;Irwin Magnetic Systems&quot; }, &bslash;&n;  { 11, &quot;Braemar&quot; }, &bslash;&n;  { 12, &quot;Verbatim&quot; }, &bslash;&n;  { 13, &quot;Core International&quot; }, &bslash;&n;  { 14, &quot;Exabyte&quot; }, &bslash;&n;  { 15, &quot;Teac&quot; }, &bslash;&n;  { 16, &quot;Gigatek&quot; }, &bslash;&n;  { 17, &quot;ComByte&quot; }, &bslash;&n;  { 18, &quot;PERTEC Memories&quot; }, &bslash;&n;  { 71, &quot;Colorado&quot; }, &bslash;&n;  { 546, &quot;Iomega Inc&quot; }, &bslash;&n;}
macro_line|#endif
eof
