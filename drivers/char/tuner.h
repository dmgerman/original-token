multiline_comment|/* &n;    tuner.h - definition for different tuners&n;&n;    Copyright (C) 1997 Markus Schroeder (schroedm@uni-duesseldorf.de)&n;    minor modifications by Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _TUNER_H
DECL|macro|_TUNER_H
mdefine_line|#define _TUNER_H
DECL|macro|TUNER_TEMIC_PAL
mdefine_line|#define TUNER_TEMIC_PAL     0  /*  Miro Gpio Coding -1 */
DECL|macro|TUNER_PHILIPS_PAL_I
mdefine_line|#define TUNER_PHILIPS_PAL_I 1
DECL|macro|TUNER_PHILIPS_NTSC
mdefine_line|#define TUNER_PHILIPS_NTSC  2
DECL|macro|TUNER_PHILIPS_SECAM
mdefine_line|#define TUNER_PHILIPS_SECAM 3
DECL|macro|TUNER_ABSENT
mdefine_line|#define TUNER_ABSENT        4
DECL|macro|TUNER_PHILIPS_PAL
mdefine_line|#define TUNER_PHILIPS_PAL   5
DECL|macro|TUNER_TEMIC_NTSC
mdefine_line|#define TUNER_TEMIC_NTSC    6
DECL|macro|TUNER_TEMIC_PAL_I
mdefine_line|#define TUNER_TEMIC_PAL_I   7
DECL|macro|NOTUNER
mdefine_line|#define NOTUNER 0
DECL|macro|PAL
mdefine_line|#define PAL     1
DECL|macro|PAL_I
mdefine_line|#define PAL_I   2
DECL|macro|NTSC
mdefine_line|#define NTSC    3
DECL|macro|SECAM
mdefine_line|#define SECAM   4
DECL|macro|NoTuner
mdefine_line|#define NoTuner 0
DECL|macro|Philips
mdefine_line|#define Philips 1
DECL|macro|TEMIC
mdefine_line|#define TEMIC   2
DECL|macro|Sony
mdefine_line|#define Sony    3
DECL|macro|TUNER_SET_TYPE
mdefine_line|#define TUNER_SET_TYPE               _IOW(&squot;t&squot;,1,int)    /* set tuner type */
DECL|macro|TUNER_SET_TVFREQ
mdefine_line|#define TUNER_SET_TVFREQ             _IOW(&squot;t&squot;,2,int)    /* set tv freq */
DECL|macro|TUNER_SET_RADIOFREQ
mdefine_line|#define TUNER_SET_RADIOFREQ          _IOW(&squot;t&squot;,3,int)    /* set radio freq */
macro_line|#endif
eof
