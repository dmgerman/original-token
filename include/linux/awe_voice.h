multiline_comment|/*&n; * sound/awe_voice.h&n; *&n; * Voice information definitions for the low level driver for the &n; * AWE32/Sound Blaster 32 wave table synth.&n; *   version 0.3.1b; Jan. 21, 1997&n; *&n; * Copyright (C) 1996,1997 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_VOICE_H
DECL|macro|AWE_VOICE_H
mdefine_line|#define AWE_VOICE_H
macro_line|#ifndef SAMPLE_TYPE_AWE32
DECL|macro|SAMPLE_TYPE_AWE32
mdefine_line|#define SAMPLE_TYPE_AWE32&t;0x20
macro_line|#endif
macro_line|#ifndef _PATCHKEY
DECL|macro|_PATCHKEY
mdefine_line|#define _PATCHKEY(id) ((id&lt;&lt;8)|0xfd)
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------&n; * patch information record&n; *----------------------------------------------------------------*/
multiline_comment|/* patch interface header: 16 bytes */
DECL|struct|awe_patch_info
r_typedef
r_struct
id|awe_patch_info
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* use AWE_PATCH here */
DECL|macro|AWE_PATCH
mdefine_line|#define AWE_PATCH&t;_PATCHKEY(0x07)
DECL|member|device_no
r_int
id|device_no
suffix:semicolon
multiline_comment|/* synthesizer number */
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|sf_version
r_int
id|sf_version
suffix:semicolon
multiline_comment|/* patch version (not referred) */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* data length (without this header) */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* following data type */
DECL|macro|AWE_LOAD_INFO
mdefine_line|#define AWE_LOAD_INFO&t;&t;0
DECL|macro|AWE_LOAD_DATA
mdefine_line|#define AWE_LOAD_DATA&t;&t;1
DECL|macro|AWE_APPEND_DATA
mdefine_line|#define AWE_APPEND_DATA&t;&t;0x00
DECL|macro|AWE_REPLACE_DATA
mdefine_line|#define AWE_REPLACE_DATA&t;0x80
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* word alignment data */
multiline_comment|/* the actual patch data begins after this */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|member|data
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|awe_patch_info
)brace
id|awe_patch_info
suffix:semicolon
DECL|macro|AWE_PATCH_INFO_SIZE
mdefine_line|#define AWE_PATCH_INFO_SIZE&t;16
multiline_comment|/*----------------------------------------------------------------&n; * raw voice information record&n; *----------------------------------------------------------------*/
multiline_comment|/* wave table envelope &amp; effect parameters to control EMU8000 */
DECL|struct|_awe_voice_parm
r_typedef
r_struct
id|_awe_voice_parm
(brace
DECL|member|moddelay
r_int
r_int
id|moddelay
suffix:semicolon
multiline_comment|/* modulation delay (0x8000) */
DECL|member|modatkhld
r_int
r_int
id|modatkhld
suffix:semicolon
multiline_comment|/* modulation attack &amp; hold time (0x7f7f) */
DECL|member|moddcysus
r_int
r_int
id|moddcysus
suffix:semicolon
multiline_comment|/* modulation decay &amp; sustain (0x7f7f) */
DECL|member|modrelease
r_int
r_int
id|modrelease
suffix:semicolon
multiline_comment|/* modulation release time (0x807f) */
DECL|member|modkeyhold
DECL|member|modkeydecay
r_int
id|modkeyhold
comma
id|modkeydecay
suffix:semicolon
multiline_comment|/* envelope change per key (not used) */
DECL|member|voldelay
r_int
r_int
id|voldelay
suffix:semicolon
multiline_comment|/* volume delay (0x8000) */
DECL|member|volatkhld
r_int
r_int
id|volatkhld
suffix:semicolon
multiline_comment|/* volume attack &amp; hold time (0x7f7f) */
DECL|member|voldcysus
r_int
r_int
id|voldcysus
suffix:semicolon
multiline_comment|/* volume decay &amp; sustain (0x7f7f) */
DECL|member|volrelease
r_int
r_int
id|volrelease
suffix:semicolon
multiline_comment|/* volume release time (0x807f) */
DECL|member|volkeyhold
DECL|member|volkeydecay
r_int
id|volkeyhold
comma
id|volkeydecay
suffix:semicolon
multiline_comment|/* envelope change per key (not used) */
DECL|member|lfo1delay
r_int
r_int
id|lfo1delay
suffix:semicolon
multiline_comment|/* LFO1 delay (0x8000) */
DECL|member|lfo2delay
r_int
r_int
id|lfo2delay
suffix:semicolon
multiline_comment|/* LFO2 delay (0x8000) */
DECL|member|pefe
r_int
r_int
id|pefe
suffix:semicolon
multiline_comment|/* modulation pitch &amp; cutoff (0x0000) */
DECL|member|fmmod
r_int
r_int
id|fmmod
suffix:semicolon
multiline_comment|/* LFO1 pitch &amp; cutoff (0x0000) */
DECL|member|tremfrq
r_int
r_int
id|tremfrq
suffix:semicolon
multiline_comment|/* LFO1 volume &amp; freq (0x0000) */
DECL|member|fm2frq2
r_int
r_int
id|fm2frq2
suffix:semicolon
multiline_comment|/* LFO2 pitch &amp; freq (0x0000) */
DECL|member|cutoff
r_int
r_char
id|cutoff
suffix:semicolon
multiline_comment|/* initial cutoff (0xff) */
DECL|member|filterQ
r_int
r_char
id|filterQ
suffix:semicolon
multiline_comment|/* initial filter Q [0-15] (0x0) */
DECL|member|chorus
r_int
r_char
id|chorus
suffix:semicolon
multiline_comment|/* chorus send (0x00) */
DECL|member|reverb
r_int
r_char
id|reverb
suffix:semicolon
multiline_comment|/* reverb send (0x00) */
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* not used */
DECL|typedef|awe_voice_parm
)brace
id|awe_voice_parm
suffix:semicolon
DECL|macro|AWE_VOICE_PARM_SIZE
mdefine_line|#define AWE_VOICE_PARM_SIZE&t;48
multiline_comment|/* wave table parameters: 92 bytes */
DECL|struct|_awe_voice_info
r_typedef
r_struct
id|_awe_voice_info
(brace
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|sample
r_int
r_int
id|sample
suffix:semicolon
multiline_comment|/* sample id */
DECL|member|start
DECL|member|end
r_int
id|start
comma
id|end
suffix:semicolon
multiline_comment|/* sample offset correction */
DECL|member|loopstart
DECL|member|loopend
r_int
id|loopstart
comma
id|loopend
suffix:semicolon
multiline_comment|/* loop offset correction */
DECL|member|rate_offset
r_int
id|rate_offset
suffix:semicolon
multiline_comment|/* sample rate pitch offset */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* sample mode */
DECL|macro|AWE_MODE_ROMSOUND
mdefine_line|#define AWE_MODE_ROMSOUND&t;&t;0x8000
DECL|macro|AWE_MODE_STEREO
mdefine_line|#define AWE_MODE_STEREO&t;&t;&t;1
DECL|macro|AWE_MODE_LOOPING
mdefine_line|#define AWE_MODE_LOOPING&t;&t;2
DECL|macro|AWE_MODE_NORELEASE
mdefine_line|#define AWE_MODE_NORELEASE&t;&t;4&t;/* obsolete */
DECL|macro|AWE_MODE_INIT_PARM
mdefine_line|#define AWE_MODE_INIT_PARM&t;&t;8
DECL|member|root
r_int
id|root
suffix:semicolon
multiline_comment|/* midi root key */
DECL|member|tune
r_int
id|tune
suffix:semicolon
multiline_comment|/* pitch tuning (in cents) */
DECL|member|low
DECL|member|high
r_char
id|low
comma
id|high
suffix:semicolon
multiline_comment|/* key note range */
DECL|member|vellow
DECL|member|velhigh
r_char
id|vellow
comma
id|velhigh
suffix:semicolon
multiline_comment|/* velocity range */
DECL|member|fixkey
DECL|member|fixvel
r_char
id|fixkey
comma
id|fixvel
suffix:semicolon
multiline_comment|/* fixed key, velocity */
DECL|member|pan
DECL|member|fixpan
r_char
id|pan
comma
id|fixpan
suffix:semicolon
multiline_comment|/* panning, fixed panning */
DECL|member|exclusiveClass
r_int
id|exclusiveClass
suffix:semicolon
multiline_comment|/* exclusive class (0 = none) */
DECL|member|amplitude
r_int
r_char
id|amplitude
suffix:semicolon
multiline_comment|/* sample volume (127 max) */
DECL|member|attenuation
r_int
r_char
id|attenuation
suffix:semicolon
multiline_comment|/* attenuation (0.375dB) */
DECL|member|scaleTuning
r_int
id|scaleTuning
suffix:semicolon
multiline_comment|/* pitch scale tuning(%), normally 100 */
DECL|member|parm
id|awe_voice_parm
id|parm
suffix:semicolon
multiline_comment|/* voice envelope parameters */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* internal index (set by driver) */
DECL|typedef|awe_voice_info
)brace
id|awe_voice_info
suffix:semicolon
DECL|macro|AWE_VOICE_INFO_SIZE
mdefine_line|#define AWE_VOICE_INFO_SIZE&t;92
multiline_comment|/*----------------------------------------------------------------*/
multiline_comment|/* The info entry of awe_voice_rec is changed from 0 to 1&n; * for some compilers refusing zero size array.&n; * Due to this change, sizeof(awe_voice_rec) becomes different&n; * from older versions.&n; * Use AWE_VOICE_REC_SIZE instead.&n; */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|macro|AWE_INFOARRAY_SIZE
mdefine_line|#define AWE_INFOARRAY_SIZE&t;0
macro_line|#else
DECL|macro|AWE_INFOARRAY_SIZE
mdefine_line|#define AWE_INFOARRAY_SIZE&t;1
macro_line|#endif
multiline_comment|/* instrument info header: 4 bytes */
DECL|struct|_awe_voice_rec
r_typedef
r_struct
id|_awe_voice_rec
(brace
DECL|member|bank
r_int
r_char
id|bank
suffix:semicolon
multiline_comment|/* midi bank number */
DECL|member|instr
r_int
r_char
id|instr
suffix:semicolon
multiline_comment|/* midi preset number */
DECL|member|nvoices
r_int
id|nvoices
suffix:semicolon
multiline_comment|/* number of voices */
multiline_comment|/* voice information follows here */
DECL|member|info
id|awe_voice_info
id|info
(braket
id|AWE_INFOARRAY_SIZE
)braket
suffix:semicolon
DECL|typedef|awe_voice_rec
)brace
id|awe_voice_rec
suffix:semicolon
DECL|macro|AWE_VOICE_REC_SIZE
mdefine_line|#define AWE_VOICE_REC_SIZE&t;4
multiline_comment|/*----------------------------------------------------------------&n; * sample wave information&n; *----------------------------------------------------------------*/
multiline_comment|/* wave table sample header: 32 bytes */
DECL|struct|awe_sample_info
r_typedef
r_struct
id|awe_sample_info
(brace
DECL|member|sf_id
r_int
r_int
id|sf_id
suffix:semicolon
multiline_comment|/* file id (should be zero) */
DECL|member|sample
r_int
r_int
id|sample
suffix:semicolon
multiline_comment|/* sample id */
DECL|member|start
DECL|member|end
r_int
id|start
comma
id|end
suffix:semicolon
multiline_comment|/* start &amp; end offset */
DECL|member|loopstart
DECL|member|loopend
r_int
id|loopstart
comma
id|loopend
suffix:semicolon
multiline_comment|/* loop start &amp; end offset */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size (0 = ROM) */
DECL|member|checksum_flag
r_int
id|checksum_flag
suffix:semicolon
multiline_comment|/* use check sum = 1 */
DECL|member|mode_flags
r_int
r_int
id|mode_flags
suffix:semicolon
multiline_comment|/* mode flags */
DECL|macro|AWE_SAMPLE_8BITS
mdefine_line|#define AWE_SAMPLE_8BITS&t;1&t;/* wave data is 8bits */
DECL|macro|AWE_SAMPLE_UNSIGNED
mdefine_line|#define AWE_SAMPLE_UNSIGNED&t;2&t;/* wave data is unsigned */
DECL|macro|AWE_SAMPLE_NO_BLANK
mdefine_line|#define AWE_SAMPLE_NO_BLANK&t;4&t;/* no blank loop is attached */
DECL|macro|AWE_SAMPLE_SINGLESHOT
mdefine_line|#define AWE_SAMPLE_SINGLESHOT&t;8&t;/* single-shot w/o loop */
DECL|macro|AWE_SAMPLE_BIDIR_LOOP
mdefine_line|#define AWE_SAMPLE_BIDIR_LOOP&t;16&t;/* bidirectional looping */
DECL|macro|AWE_SAMPLE_STEREO_LEFT
mdefine_line|#define AWE_SAMPLE_STEREO_LEFT&t;32&t;/* stereo left sound */
DECL|macro|AWE_SAMPLE_STEREO_RIGHT
mdefine_line|#define AWE_SAMPLE_STEREO_RIGHT&t;64&t;/* stereo right sound */
DECL|macro|AWE_SAMPLE_REVERSE_LOOP
mdefine_line|#define AWE_SAMPLE_REVERSE_LOOP 128&t;/* reverse looping */
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
multiline_comment|/* check sum */
macro_line|#if defined(AWE_COMPAT_030) &amp;&amp; AWE_COMPAT_030
DECL|member|data
r_int
r_int
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* sample data follows here */
macro_line|#endif
DECL|typedef|awe_sample_info
)brace
id|awe_sample_info
suffix:semicolon
DECL|macro|AWE_SAMPLE_INFO_SIZE
mdefine_line|#define AWE_SAMPLE_INFO_SIZE&t;32
multiline_comment|/*----------------------------------------------------------------&n; * awe hardware controls&n; *----------------------------------------------------------------*/
DECL|struct|_awe_mode_rec
r_typedef
r_struct
id|_awe_mode_rec
(brace
DECL|member|base_addr
r_int
id|base_addr
suffix:semicolon
DECL|member|mem_size
r_int
id|mem_size
suffix:semicolon
multiline_comment|/* word size */
DECL|member|max_voices
DECL|member|max_infos
DECL|member|max_samples
r_int
id|max_voices
comma
id|max_infos
comma
id|max_samples
suffix:semicolon
DECL|member|current_sf_id
r_int
r_int
id|current_sf_id
suffix:semicolon
DECL|member|free_mem
r_int
id|free_mem
suffix:semicolon
multiline_comment|/* word offset */
DECL|member|free_info
r_int
id|free_info
suffix:semicolon
DECL|member|free_sample
r_int
id|free_sample
suffix:semicolon
DECL|member|reverb_mode
r_int
id|reverb_mode
suffix:semicolon
DECL|member|chorus_mode
r_int
id|chorus_mode
suffix:semicolon
DECL|member|init_atten
r_int
r_int
id|init_atten
suffix:semicolon
DECL|member|channel_mode
r_int
id|channel_mode
suffix:semicolon
DECL|member|gus_bank
r_int
id|gus_bank
suffix:semicolon
DECL|member|exclusive_sound
r_int
id|exclusive_sound
suffix:semicolon
DECL|member|drum_flags
r_int
r_int
id|drum_flags
suffix:semicolon
DECL|member|debug_mode
r_int
id|debug_mode
suffix:semicolon
DECL|typedef|awe_mode_rec
)brace
id|awe_mode_rec
suffix:semicolon
DECL|macro|_AWE_DEBUG_MODE
mdefine_line|#define _AWE_DEBUG_MODE&t;&t;&t;0x00
DECL|macro|_AWE_REVERB_MODE
mdefine_line|#define _AWE_REVERB_MODE&t;&t;0x01
DECL|macro|_AWE_CHORUS_MODE
mdefine_line|#define _AWE_CHORUS_MODE&t;&t;0x02
DECL|macro|_AWE_REMOVE_LAST_SAMPLES
mdefine_line|#define _AWE_REMOVE_LAST_SAMPLES&t;0x03
DECL|macro|_AWE_INITIALIZE_CHIP
mdefine_line|#define _AWE_INITIALIZE_CHIP&t;&t;0x04
DECL|macro|_AWE_SEND_EFFECT
mdefine_line|#define _AWE_SEND_EFFECT&t;&t;0x05
DECL|macro|_AWE_TERMINATE_CHANNEL
mdefine_line|#define _AWE_TERMINATE_CHANNEL&t;&t;0x06
DECL|macro|_AWE_TERMINATE_ALL
mdefine_line|#define _AWE_TERMINATE_ALL&t;&t;0x07
DECL|macro|_AWE_INITIAL_VOLUME
mdefine_line|#define _AWE_INITIAL_VOLUME&t;&t;0x08
DECL|macro|_AWE_SET_GUS_BANK
mdefine_line|#define _AWE_SET_GUS_BANK&t;&t;0x09
DECL|macro|_AWE_CHANNEL_MODE
mdefine_line|#define _AWE_CHANNEL_MODE&t;&t;0x0a&t;/* v0.3 features */
DECL|macro|_AWE_DRUM_CHANNELS
mdefine_line|#define _AWE_DRUM_CHANNELS&t;&t;0x0b&t;/* v0.3 features */
DECL|macro|_AWE_EXCLUSIVE_SOUND
mdefine_line|#define _AWE_EXCLUSIVE_SOUND&t;&t;0x0c&t;/* v0.3 features */
DECL|macro|_AWE_INITIAL_ATTEN
mdefine_line|#define _AWE_INITIAL_ATTEN&t;_AWE_INITIAL_VOLUME
DECL|macro|_AWE_NOTEOFF_ALL
mdefine_line|#define _AWE_NOTEOFF_ALL&t;&t;0x0e
DECL|macro|_AWE_GET_CURRENT_MODE
mdefine_line|#define _AWE_GET_CURRENT_MODE&t;&t;0x10&t;/* v0.3 features */
DECL|macro|_AWE_MODE_FLAG
mdefine_line|#define _AWE_MODE_FLAG&t;&t;&t;0x80
DECL|macro|_AWE_COOKED_FLAG
mdefine_line|#define _AWE_COOKED_FLAG&t;&t;0x40&t;/* not supported */
DECL|macro|_AWE_MODE_VALUE_MASK
mdefine_line|#define _AWE_MODE_VALUE_MASK&t;&t;0x3F
DECL|macro|_AWE_CMD
mdefine_line|#define _AWE_CMD(chn, voice, cmd, p1, p2) &bslash;&n;{_SEQ_NEEDBUF(8); _seqbuf[_seqbufptr] = SEQ_PRIVATE;&bslash;&n; _seqbuf[_seqbufptr+1] = chn;&bslash;&n; _seqbuf[_seqbufptr+2] = _AWE_MODE_FLAG|(cmd);&bslash;&n; _seqbuf[_seqbufptr+3] = voice;&bslash;&n; *(unsigned short*)&amp;_seqbuf[_seqbufptr+4] = p1;&bslash;&n; *(unsigned short*)&amp;_seqbuf[_seqbufptr+6] = p2;&bslash;&n; _SEQ_ADVBUF(8);}
DECL|macro|AWE_DEBUG_MODE
mdefine_line|#define AWE_DEBUG_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_DEBUG_MODE, p1, 0)
DECL|macro|AWE_REVERB_MODE
mdefine_line|#define AWE_REVERB_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_REVERB_MODE, p1, 0)
DECL|macro|AWE_CHORUS_MODE
mdefine_line|#define AWE_CHORUS_MODE(dev,p1)&t;_AWE_CMD(dev, 0, _AWE_CHORUS_MODE, p1, 0)
DECL|macro|AWE_REMOVE_LAST_SAMPLES
mdefine_line|#define AWE_REMOVE_LAST_SAMPLES(dev) _AWE_CMD(dev, 0, _AWE_REMOVE_LAST_SAMPLES, 0, 0)
DECL|macro|AWE_INITIALIZE_CHIP
mdefine_line|#define AWE_INITIALIZE_CHIP(dev) _AWE_CMD(dev, 0, _AWE_INITIALIZE_CHIP, 0, 0)
DECL|macro|AWE_SEND_EFFECT
mdefine_line|#define AWE_SEND_EFFECT(dev,voice,type,value) _AWE_CMD(dev,voice,_AWE_SEND_EFFECT,type,value)
DECL|macro|AWE_TERMINATE_CHANNEL
mdefine_line|#define AWE_TERMINATE_CHANNEL(dev,voice) _AWE_CMD(dev,voice,_AWE_TERMINATE_CHANNEL,0,0)
DECL|macro|AWE_TERMINATE_ALL
mdefine_line|#define AWE_TERMINATE_ALL(dev) _AWE_CMD(dev, 0, _AWE_TERMINATE_ALL, 0, 0)
DECL|macro|AWE_NOTEOFF_ALL
mdefine_line|#define AWE_NOTEOFF_ALL(dev) _AWE_CMD(dev, 0, _AWE_NOTEOFF_ALL, 0, 0)
DECL|macro|AWE_INITIAL_VOLUME
mdefine_line|#define AWE_INITIAL_VOLUME(dev,atten) _AWE_CMD(dev, 0, _AWE_INITIAL_VOLUME, atten, 0)
DECL|macro|AWE_INITIAL_ATTEN
mdefine_line|#define AWE_INITIAL_ATTEN  AWE_INITIAL_VOLUME
DECL|macro|AWE_SET_GUS_BANK
mdefine_line|#define AWE_SET_GUS_BANK(dev,bank) _AWE_CMD(dev, 0, _AWE_SET_GUS_BANK, bank, 0)
DECL|macro|AWE_SET_CHANNEL_MODE
mdefine_line|#define AWE_SET_CHANNEL_MODE(dev,mode) _AWE_CMD(dev, 0, _AWE_CHANNEL_MODE, mode, 0)
DECL|macro|AWE_DRUM_CHANNELS
mdefine_line|#define AWE_DRUM_CHANNELS(dev,channels) _AWE_CMD(dev, 0, _AWE_DRUM_CHANNELS, channels, 0)
DECL|macro|AWE_EXCLUSIVE_SOUND
mdefine_line|#define AWE_EXCLUSIVE_SOUND(dev,mode) _AWE_CMD(dev, 0, _AWE_EXCLUSIVE_SOUND, mode, 0)
multiline_comment|/* it must be direct access */
DECL|macro|AWE_GET_CURRENT_MODE
mdefine_line|#define AWE_GET_CURRENT_MODE(dev,addr) &bslash;&n;{char tmpbuf[8];&bslash;&n; tmpbuf[0] = SEQ_PRIVATE; tmpbuf[1] = dev;&bslash;&n; tmpbuf[2] = _AWE_MODE_FLAG|_AWE_GET_CURRENT_MODE;&bslash;&n; tmpbuf[3] = 0; *(awe_mode_rec**)(tmpbuf +4) = (awe_mode_rec*)(addr);&bslash;&n; write(seqfd, tmpbuf, 8);}
multiline_comment|/* extended pressure controls; not portable with other sound drivers */
DECL|macro|AWE_KEY_PRESSURE
mdefine_line|#define AWE_KEY_PRESSURE(dev,ch,note,vel) SEQ_START_NOTE(dev,ch,(note)+128,vel)
DECL|macro|AWE_CHN_PRESSURE
mdefine_line|#define AWE_CHN_PRESSURE(dev,ch,vel) SEQ_START_NOTE(dev,(ch)+128,0,vel)
multiline_comment|/* reverb mode */
DECL|macro|AWE_REVERB_ROOM1
mdefine_line|#define&t;AWE_REVERB_ROOM1&t;0
DECL|macro|AWE_REVERB_ROOM2
mdefine_line|#define AWE_REVERB_ROOM2&t;1
DECL|macro|AWE_REVERB_ROOM3
mdefine_line|#define&t;AWE_REVERB_ROOM3&t;2
DECL|macro|AWE_REVERB_HALL1
mdefine_line|#define&t;AWE_REVERB_HALL1&t;3
DECL|macro|AWE_REVERB_HALL2
mdefine_line|#define&t;AWE_REVERB_HALL2&t;4
DECL|macro|AWE_REVERB_PLATE
mdefine_line|#define&t;AWE_REVERB_PLATE&t;5
DECL|macro|AWE_REVERB_DELAY
mdefine_line|#define&t;AWE_REVERB_DELAY&t;6
DECL|macro|AWE_REVERB_PANNINGDELAY
mdefine_line|#define&t;AWE_REVERB_PANNINGDELAY 7
multiline_comment|/* chorus mode */
DECL|macro|AWE_CHORUS_1
mdefine_line|#define AWE_CHORUS_1&t;&t;0
DECL|macro|AWE_CHORUS_2
mdefine_line|#define&t;AWE_CHORUS_2&t;&t;1
DECL|macro|AWE_CHORUS_3
mdefine_line|#define&t;AWE_CHORUS_3&t;&t;2
DECL|macro|AWE_CHORUS_4
mdefine_line|#define&t;AWE_CHORUS_4&t;&t;3
DECL|macro|AWE_CHORUS_FEEDBACK
mdefine_line|#define&t;AWE_CHORUS_FEEDBACK&t;4
DECL|macro|AWE_CHORUS_FLANGER
mdefine_line|#define&t;AWE_CHORUS_FLANGER&t;5
DECL|macro|AWE_CHORUS_SHORTDELAY
mdefine_line|#define&t;AWE_CHORUS_SHORTDELAY&t;6
DECL|macro|AWE_CHORUS_SHORTDELAY2
mdefine_line|#define&t;AWE_CHORUS_SHORTDELAY2&t;7
multiline_comment|/* effects */
r_enum
(brace
multiline_comment|/* modulation envelope parameters */
DECL|enumerator|AWE_FX_ENV1_DELAY
multiline_comment|/* 0*/
id|AWE_FX_ENV1_DELAY
comma
multiline_comment|/* WORD: ENVVAL */
DECL|enumerator|AWE_FX_ENV1_ATTACK
multiline_comment|/* 1*/
id|AWE_FX_ENV1_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLD */
DECL|enumerator|AWE_FX_ENV1_HOLD
multiline_comment|/* 2*/
id|AWE_FX_ENV1_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLD */
DECL|enumerator|AWE_FX_ENV1_DECAY
multiline_comment|/* 3*/
id|AWE_FX_ENV1_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|AWE_FX_ENV1_RELEASE
multiline_comment|/* 4*/
id|AWE_FX_ENV1_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUS */
DECL|enumerator|AWE_FX_ENV1_SUSTAIN
multiline_comment|/* 5*/
id|AWE_FX_ENV1_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUS */
DECL|enumerator|AWE_FX_ENV1_PITCH
multiline_comment|/* 6*/
id|AWE_FX_ENV1_PITCH
comma
multiline_comment|/* BYTE: up PEFE */
DECL|enumerator|AWE_FX_ENV1_CUTOFF
multiline_comment|/* 7*/
id|AWE_FX_ENV1_CUTOFF
comma
multiline_comment|/* BYTE: lw PEFE */
multiline_comment|/* volume envelope parameters */
DECL|enumerator|AWE_FX_ENV2_DELAY
multiline_comment|/* 8*/
id|AWE_FX_ENV2_DELAY
comma
multiline_comment|/* WORD: ENVVOL */
DECL|enumerator|AWE_FX_ENV2_ATTACK
multiline_comment|/* 9*/
id|AWE_FX_ENV2_ATTACK
comma
multiline_comment|/* BYTE: up ATKHLDV */
DECL|enumerator|AWE_FX_ENV2_HOLD
multiline_comment|/*10*/
id|AWE_FX_ENV2_HOLD
comma
multiline_comment|/* BYTE: lw ATKHLDV */
DECL|enumerator|AWE_FX_ENV2_DECAY
multiline_comment|/*11*/
id|AWE_FX_ENV2_DECAY
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|AWE_FX_ENV2_RELEASE
multiline_comment|/*12*/
id|AWE_FX_ENV2_RELEASE
comma
multiline_comment|/* BYTE: lw DCYSUSV */
DECL|enumerator|AWE_FX_ENV2_SUSTAIN
multiline_comment|/*13*/
id|AWE_FX_ENV2_SUSTAIN
comma
multiline_comment|/* BYTE: up DCYSUSV */
multiline_comment|/* LFO1 (tremolo &amp; vibrato) parameters */
DECL|enumerator|AWE_FX_LFO1_DELAY
multiline_comment|/*14*/
id|AWE_FX_LFO1_DELAY
comma
multiline_comment|/* WORD: LFO1VAL */
DECL|enumerator|AWE_FX_LFO1_FREQ
multiline_comment|/*15*/
id|AWE_FX_LFO1_FREQ
comma
multiline_comment|/* BYTE: lo TREMFRQ */
DECL|enumerator|AWE_FX_LFO1_VOLUME
multiline_comment|/*16*/
id|AWE_FX_LFO1_VOLUME
comma
multiline_comment|/* BYTE: up TREMFRQ */
DECL|enumerator|AWE_FX_LFO1_PITCH
multiline_comment|/*17*/
id|AWE_FX_LFO1_PITCH
comma
multiline_comment|/* BYTE: up FMMOD */
DECL|enumerator|AWE_FX_LFO1_CUTOFF
multiline_comment|/*18*/
id|AWE_FX_LFO1_CUTOFF
comma
multiline_comment|/* BYTE: lo FMMOD */
multiline_comment|/* LFO2 (vibrato) parameters */
DECL|enumerator|AWE_FX_LFO2_DELAY
multiline_comment|/*19*/
id|AWE_FX_LFO2_DELAY
comma
multiline_comment|/* WORD: LFO2VAL */
DECL|enumerator|AWE_FX_LFO2_FREQ
multiline_comment|/*20*/
id|AWE_FX_LFO2_FREQ
comma
multiline_comment|/* BYTE: lo FM2FRQ2 */
DECL|enumerator|AWE_FX_LFO2_PITCH
multiline_comment|/*21*/
id|AWE_FX_LFO2_PITCH
comma
multiline_comment|/* BYTE: up FM2FRQ2 */
multiline_comment|/* Other overall effect parameters */
DECL|enumerator|AWE_FX_INIT_PITCH
multiline_comment|/*22*/
id|AWE_FX_INIT_PITCH
comma
multiline_comment|/* SHORT: pitch offset */
DECL|enumerator|AWE_FX_CHORUS
multiline_comment|/*23*/
id|AWE_FX_CHORUS
comma
multiline_comment|/* BYTE: chorus effects send (0-255) */
DECL|enumerator|AWE_FX_REVERB
multiline_comment|/*24*/
id|AWE_FX_REVERB
comma
multiline_comment|/* BYTE: reverb effects send (0-255) */
DECL|enumerator|AWE_FX_CUTOFF
multiline_comment|/*25*/
id|AWE_FX_CUTOFF
comma
multiline_comment|/* BYTE: up IFATN */
DECL|enumerator|AWE_FX_FILTERQ
multiline_comment|/*26*/
id|AWE_FX_FILTERQ
comma
multiline_comment|/* BYTE: up CCCA */
multiline_comment|/* Sample / loop offset changes */
DECL|enumerator|AWE_FX_SAMPLE_START
multiline_comment|/*27*/
id|AWE_FX_SAMPLE_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_LOOP_START
multiline_comment|/*28*/
id|AWE_FX_LOOP_START
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_LOOP_END
multiline_comment|/*29*/
id|AWE_FX_LOOP_END
comma
multiline_comment|/* SHORT: offset */
DECL|enumerator|AWE_FX_COARSE_SAMPLE_START
multiline_comment|/*30*/
id|AWE_FX_COARSE_SAMPLE_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_COARSE_LOOP_START
multiline_comment|/*31*/
id|AWE_FX_COARSE_LOOP_START
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_COARSE_LOOP_END
multiline_comment|/*32*/
id|AWE_FX_COARSE_LOOP_END
comma
multiline_comment|/* SHORT: upper word offset */
DECL|enumerator|AWE_FX_END
id|AWE_FX_END
comma
)brace
suffix:semicolon
macro_line|#endif /* AWE_VOICE_H */
eof
