multiline_comment|/*&n; * sound/awe_config.h&n; *&n; * Configuration of AWE32/SB32/AWE64 wave table synth driver.&n; *   version 0.4.3; Mar. 1, 1998&n; *&n; * Copyright (C) 1996-1998 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_CONFIG_H_DEF
DECL|macro|AWE_CONFIG_H_DEF
mdefine_line|#define AWE_CONFIG_H_DEF
multiline_comment|/*----------------------------------------------------------------&n; * system configuration&n; *----------------------------------------------------------------*/
multiline_comment|/* if your kernel support module for each soundcard, define this.&n; * NOTE: it will be automatically set on linux-2.1.x kernels.&n; *       only define here if you have moduler sound system on&n; *       2.0.x kernel (like RedHat).&n; */
DECL|macro|AWE_MODULE_SUPPORT
macro_line|#undef AWE_MODULE_SUPPORT
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
multiline_comment|/* GUS compatible mode */
DECL|macro|AWE_HAS_GUS_COMPATIBILITY
mdefine_line|#define AWE_HAS_GUS_COMPATIBILITY
multiline_comment|/* add MIDI emulation by wavetable */
DECL|macro|CONFIG_AWE32_MIDIEMU
mdefine_line|#define CONFIG_AWE32_MIDIEMU
multiline_comment|/* add mixer control of emu8000 equalizer */
DECL|macro|CONFIG_AWE32_MIXER
macro_line|#undef CONFIG_AWE32_MIXER
multiline_comment|/* use new volume calculation method as default */
DECL|macro|AWE_USE_NEW_VOLUME_CALC
mdefine_line|#define AWE_USE_NEW_VOLUME_CALC
multiline_comment|/* check current volume target for searching empty voices */
DECL|macro|AWE_CHECK_VTARGET
mdefine_line|#define AWE_CHECK_VTARGET
multiline_comment|/* allow sample sharing */
DECL|macro|AWE_ALLOW_SAMPLE_SHARING
mdefine_line|#define AWE_ALLOW_SAMPLE_SHARING
multiline_comment|/*================================================================&n; * Usually, you don&squot;t have to touch the following options.&n; *================================================================*/
multiline_comment|/*----------------------------------------------------------------&n; * AWE32 card configuration:&n; * uncomment the following lines *ONLY* when auto detection doesn&squot;t&n; * work properly on your machine.&n; *----------------------------------------------------------------*/
multiline_comment|/*#define AWE_DEFAULT_BASE_ADDR&t;0x620*/
multiline_comment|/* base port address */
multiline_comment|/*#define AWE_DEFAULT_MEM_SIZE&t;512*/
multiline_comment|/* kbytes */
multiline_comment|/*----------------------------------------------------------------&n; * maximum size of soundfont list table&n; *----------------------------------------------------------------*/
DECL|macro|AWE_MAX_SF_LISTS
mdefine_line|#define AWE_MAX_SF_LISTS 16
multiline_comment|/*----------------------------------------------------------------&n; * chunk size of sample and voice tables&n; *----------------------------------------------------------------*/
DECL|macro|AWE_MAX_SAMPLES
mdefine_line|#define AWE_MAX_SAMPLES 400
DECL|macro|AWE_MAX_INFOS
mdefine_line|#define AWE_MAX_INFOS 800
macro_line|#endif  /* AWE_CONFIG_H_DEF */
eof
