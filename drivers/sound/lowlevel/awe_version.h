multiline_comment|/*&n; * sound/awe_version.h&n; *&n; * Version defines for the AWE32/SB32/AWE64 wave table synth driver.&n; *   version 0.4.3; Mar. 1, 1998&n; *&n; * Copyright (C) 1996-1998 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* AWE32 driver version number */
macro_line|#ifndef AWE_VERSION_H_DEF
DECL|macro|AWE_VERSION_H_DEF
mdefine_line|#define AWE_VERSION_H_DEF
DECL|macro|AWE_MAJOR_VERSION
mdefine_line|#define AWE_MAJOR_VERSION&t;0
DECL|macro|AWE_MINOR_VERSION
mdefine_line|#define AWE_MINOR_VERSION&t;4
DECL|macro|AWE_TINY_VERSION
mdefine_line|#define AWE_TINY_VERSION&t;3
DECL|macro|AWE_VERSION_NUMBER
mdefine_line|#define AWE_VERSION_NUMBER&t;((AWE_MAJOR_VERSION&lt;&lt;16)|(AWE_MINOR_VERSION&lt;&lt;8)|AWE_TINY_VERSION)
DECL|macro|AWEDRV_VERSION
mdefine_line|#define AWEDRV_VERSION&t;&t;&quot;0.4.3&quot;
macro_line|#endif
eof
