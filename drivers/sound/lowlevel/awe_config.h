multiline_comment|/*&n; * sound/awe_config.h&n; *&n; * Configuration of AWE32 sound driver&n; *   version 0.2.99e; Dec. 10, 1997&n; *&n; * Copyright (C) 1996,1997 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_CONFIG_H_DEF
DECL|macro|AWE_CONFIG_H_DEF
mdefine_line|#define AWE_CONFIG_H_DEF
multiline_comment|/*----------------------------------------------------------------&n; * system configuration&n; *----------------------------------------------------------------*/
multiline_comment|/* if you&squot;re using obsolete VoxWare 3.0.x on Linux 1.2.x (or FreeBSD),&n; * define the following line.&n; */
DECL|macro|AWE_OBSOLETE_VOXWARE
macro_line|#undef AWE_OBSOLETE_VOXWARE
macro_line|#ifdef __FreeBSD__
DECL|macro|AWE_OBSOLETE_VOXWARE
macro_line|#  define AWE_OBSOLETE_VOXWARE
macro_line|#endif
multiline_comment|/* if you&squot;re using OSS-Lite on Linux 2.1.6 or later, define the&n; * following line.&n; */
DECL|macro|AWE_NEW_KERNEL_INTERFACE
mdefine_line|#define AWE_NEW_KERNEL_INTERFACE
multiline_comment|/* if you have lowlevel.h in the lowlevel directory (OSS-Lite), define&n; * the following line.&n; */
DECL|macro|HAS_LOWLEVEL_H
mdefine_line|#define HAS_LOWLEVEL_H
multiline_comment|/* if your system doesn&squot;t support patch manager (OSS 3.7 or newer),&n; * define the following line.&n; */
DECL|macro|AWE_NO_PATCHMGR
mdefine_line|#define AWE_NO_PATCHMGR
multiline_comment|/*----------------------------------------------------------------&n; * AWE32 card configuration:&n; * uncomment the following lines only when auto detection doesn&squot;t&n; * work properly on your machine.&n; *----------------------------------------------------------------*/
multiline_comment|/*#define AWE_DEFAULT_BASE_ADDR&t;0x620*/
multiline_comment|/* base port address */
multiline_comment|/*#define AWE_DEFAULT_MEM_SIZE&t;512*/
multiline_comment|/* kbytes */
multiline_comment|/*----------------------------------------------------------------&n; * maximum size of sample table:&n; * the followings are for ROM GM and 512k GS samples.  if your have&n; * additional DRAM and SoundFonts, increase these values.&n; *----------------------------------------------------------------*/
DECL|macro|AWE_MAX_SAMPLES
mdefine_line|#define AWE_MAX_SAMPLES 400
DECL|macro|AWE_MAX_INFOS
mdefine_line|#define AWE_MAX_INFOS 1500
multiline_comment|/*----------------------------------------------------------------&n; * chorus &amp; reverb effects send for FM chip: from 0 to 0xff&n; * larger numbers often cause weird sounds.&n; *----------------------------------------------------------------*/
DECL|macro|DEF_FM_CHORUS_DEPTH
mdefine_line|#define DEF_FM_CHORUS_DEPTH&t;0x10
DECL|macro|DEF_FM_REVERB_DEPTH
mdefine_line|#define DEF_FM_REVERB_DEPTH&t;0x10
multiline_comment|/*----------------------------------------------------------------*&n; * other compile conditions&n; *----------------------------------------------------------------*/
multiline_comment|/* initialize FM passthrough even without extended RAM */
DECL|macro|AWE_ALWAYS_INIT_FM
macro_line|#undef AWE_ALWAYS_INIT_FM
multiline_comment|/* debug on */
DECL|macro|AWE_DEBUG_ON
mdefine_line|#define AWE_DEBUG_ON
multiline_comment|/* verify checksum for uploading samples */
DECL|macro|AWE_CHECKSUM_DATA
mdefine_line|#define AWE_CHECKSUM_DATA
DECL|macro|AWE_CHECKSUM_MEMORY
mdefine_line|#define AWE_CHECKSUM_MEMORY
multiline_comment|/* GUS compatible mode */
DECL|macro|AWE_HAS_GUS_COMPATIBILITY
mdefine_line|#define AWE_HAS_GUS_COMPATIBILITY
multiline_comment|/* accept all notes/sounds off controls */
DECL|macro|AWE_ACCEPT_ALL_SOUNDS_CONTROL
macro_line|#undef AWE_ACCEPT_ALL_SOUNDS_CONTROL
macro_line|#ifdef linux
multiline_comment|/* i tested this only on my linux */
DECL|macro|INLINE
mdefine_line|#define INLINE  __inline__
macro_line|#else
DECL|macro|INLINE
mdefine_line|#define INLINE /**/
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* reading configuration of sound driver */
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
macro_line|#ifdef __FreeBSD__
macro_line|#  include &lt;i386/isa/sound/sound_config.h&gt;
macro_line|#else
macro_line|#  include &quot;sound_config.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_AWE32)
DECL|macro|CONFIG_AWE32_SYNTH
mdefine_line|#define CONFIG_AWE32_SYNTH
macro_line|#endif
macro_line|#else /* AWE_OBSOLETE_VOXWARE */
macro_line|#ifdef HAS_LOWLEVEL_H
macro_line|#include &quot;lowlevel.h&quot;
macro_line|#endif
macro_line|#include &quot;../sound_config.h&quot;
macro_line|#endif /* AWE_OBSOLETE_VOXWARE */
macro_line|#endif  /* AWE_CONFIG_H_DEF */
eof