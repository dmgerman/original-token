multiline_comment|/*&n; *  $Id: debug.h,v 1.1 1996/11/07 13:07:42 fritz Exp $&n; *  Copyright (C) 1996  SpellCaster Telecommunications Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  For more information, please contact gpl-info@spellcast.com or write:&n; *&n; *     SpellCaster Telecommunications Inc.&n; *     5621 Finch Avenue East, Unit #3&n; *     Scarborough, Ontario  Canada&n; *     M1B 2T9&n; *     +1 (416) 297-8565&n; *     +1 (416) 297-6433 Facsimile&n; */
macro_line|#if LINUX_VERSION_CODE &lt; 131072
macro_line|#error You cant use this driver on kernels older than 2.0
macro_line|#else
DECL|macro|REQUEST_IRQ
mdefine_line|#define REQUEST_IRQ(a,b,c,d,e) request_irq(a,b,c,d,e)
DECL|macro|FREE_IRQ
mdefine_line|#define FREE_IRQ(a,b) free_irq(a,b)
macro_line|#endif
eof