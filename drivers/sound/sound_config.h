multiline_comment|/* sound_config.h&n; *&n; * A driver for Soundcards, misc configuration parameters.&n; *&n; * &n; * Copyright by Hannu Savolainen 1993&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#include &quot;local.h&quot;
macro_line|#if defined(ISC) || defined(SCO) || defined(SVR42)
DECL|macro|GENERIC_SYSV
mdefine_line|#define GENERIC_SYSV
macro_line|#endif
multiline_comment|/*&n; * Disable the AD1848 driver if there are no other drivers requiring it.&n; */
macro_line|#if defined(EXCLUDE_GUS16) &amp;&amp; defined(EXCLUDE_MSS) &amp;&amp; defined(EXCLUDE_PSS) &amp;&amp; defined(EXCLUDE_GUSMAX)
DECL|macro|EXCLUDE_AD1848
mdefine_line|#define EXCLUDE_AD1848
macro_line|#endif
DECL|macro|CONFIGURE_SOUNDCARD
macro_line|#undef CONFIGURE_SOUNDCARD
DECL|macro|DYNAMIC_BUFFER
macro_line|#undef DYNAMIC_BUFFER
macro_line|#ifdef KERNEL_SOUNDCARD
DECL|macro|CONFIGURE_SOUNDCARD
mdefine_line|#define CONFIGURE_SOUNDCARD
DECL|macro|DYNAMIC_BUFFER
mdefine_line|#define DYNAMIC_BUFFER
DECL|macro|LOADABLE_SOUNDCARD
macro_line|#undef LOADABLE_SOUNDCARD
macro_line|#endif
macro_line|#ifdef EXCLUDE_SEQUENCER
DECL|macro|EXCLUDE_MIDI
mdefine_line|#define EXCLUDE_MIDI
DECL|macro|EXCLUDE_YM3812
mdefine_line|#define EXCLUDE_YM3812
DECL|macro|EXCLUDE_OPL3
mdefine_line|#define EXCLUDE_OPL3
macro_line|#endif
macro_line|#ifndef SND_DEFAULT_ENABLE
DECL|macro|SND_DEFAULT_ENABLE
mdefine_line|#define SND_DEFAULT_ENABLE&t;1
macro_line|#endif
macro_line|#ifdef CONFIGURE_SOUNDCARD
multiline_comment|/* ****** IO-address, DMA and IRQ settings ****&n;&n;If your card has nonstandard I/O address or IRQ number, change defines&n;   for the following settings in your kernel Makefile */
macro_line|#ifndef SBC_BASE
DECL|macro|SBC_BASE
mdefine_line|#define SBC_BASE&t;0x220&t;/* 0x220 is the factory default. */
macro_line|#endif
macro_line|#ifndef SBC_IRQ
DECL|macro|SBC_IRQ
mdefine_line|#define SBC_IRQ&t;&t;7&t;/* IQR7 is the factory default.&t; */
macro_line|#endif
macro_line|#ifndef SBC_DMA
DECL|macro|SBC_DMA
mdefine_line|#define SBC_DMA&t;&t;1
macro_line|#endif
macro_line|#ifndef SB16_DMA
DECL|macro|SB16_DMA
mdefine_line|#define SB16_DMA&t;6
macro_line|#endif
macro_line|#ifndef SB16MIDI_BASE
DECL|macro|SB16MIDI_BASE
mdefine_line|#define SB16MIDI_BASE&t;0x300
macro_line|#endif
macro_line|#ifndef PAS_BASE
DECL|macro|PAS_BASE
mdefine_line|#define PAS_BASE&t;0x388
macro_line|#endif
macro_line|#ifndef PAS_IRQ
DECL|macro|PAS_IRQ
mdefine_line|#define PAS_IRQ&t;&t;5
macro_line|#endif
macro_line|#ifndef PAS_DMA
DECL|macro|PAS_DMA
mdefine_line|#define PAS_DMA&t;&t;3
macro_line|#endif
macro_line|#ifndef GUS_BASE
DECL|macro|GUS_BASE
mdefine_line|#define GUS_BASE&t;0x220
macro_line|#endif
macro_line|#ifndef GUS_IRQ
DECL|macro|GUS_IRQ
mdefine_line|#define GUS_IRQ&t;&t;15
macro_line|#endif
macro_line|#ifndef GUS_MIDI_IRQ
DECL|macro|GUS_MIDI_IRQ
mdefine_line|#define GUS_MIDI_IRQ&t;GUS_IRQ
macro_line|#endif
macro_line|#ifndef GUS_DMA
DECL|macro|GUS_DMA
mdefine_line|#define GUS_DMA&t;&t;6
macro_line|#endif
macro_line|#ifndef MPU_BASE
DECL|macro|MPU_BASE
mdefine_line|#define MPU_BASE&t;0x330
macro_line|#endif
macro_line|#ifndef MPU_IRQ
DECL|macro|MPU_IRQ
mdefine_line|#define MPU_IRQ&t;&t;6
macro_line|#endif
multiline_comment|/* Echo Personal Sound System */
macro_line|#ifndef PSS_BASE
DECL|macro|PSS_BASE
mdefine_line|#define PSS_BASE        0x220   /* 0x240 or */
macro_line|#endif
macro_line|#ifndef PSS_IRQ
DECL|macro|PSS_IRQ
mdefine_line|#define PSS_IRQ         7
macro_line|#endif
macro_line|#ifndef PSS_DMA
DECL|macro|PSS_DMA
mdefine_line|#define PSS_DMA         1
macro_line|#endif
macro_line|#ifndef MAX_REALTIME_FACTOR
DECL|macro|MAX_REALTIME_FACTOR
mdefine_line|#define MAX_REALTIME_FACTOR&t;4
macro_line|#endif
multiline_comment|/************* PCM DMA buffer sizes *******************/
multiline_comment|/* If you are using high playback or recording speeds, the default buffersize&n;   is too small. DSP_BUFFSIZE must be 64k or less.&n;&n;   A rule of thumb is 64k for PAS16, 32k for PAS+, 16k for SB Pro and&n;   4k for SB.&n;&n;   If you change the DSP_BUFFSIZE, don&squot;t modify this file.&n;   Use the make config command instead. */
macro_line|#ifndef DSP_BUFFSIZE
DECL|macro|DSP_BUFFSIZE
mdefine_line|#define DSP_BUFFSIZE&t;&t;(4096)
macro_line|#endif
macro_line|#ifndef DSP_BUFFCOUNT
DECL|macro|DSP_BUFFCOUNT
mdefine_line|#define DSP_BUFFCOUNT&t;&t;2&t;/* 2 is recommended. */
macro_line|#endif
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT&t;&t;0x10
DECL|macro|FM_MONO
mdefine_line|#define FM_MONO&t;&t;0x388&t;/* This is the I/O address used by AdLib */
multiline_comment|/* SEQ_MAX_QUEUE is the maximum number of sequencer events buffered by the&n;   driver. (There is no need to alter this) */
DECL|macro|SEQ_MAX_QUEUE
mdefine_line|#define SEQ_MAX_QUEUE&t;1024
DECL|macro|SBFM_MAXINSTR
mdefine_line|#define SBFM_MAXINSTR&t;&t;(256)&t;/* Size of the FM Instrument bank */
multiline_comment|/* 128 instruments for general MIDI setup and 16 unassigned&t; */
multiline_comment|/*&n; * Minor numbers for the sound driver.&n; *&n; * Unfortunately Creative called the codec chip of SB as a DSP. For this&n; * reason the /dev/dsp is reserved for digitized audio use. There is a&n; * device for true DSP processors but it will be called something else.&n; * In v3.0 it&squot;s /dev/sndproc but this could be a temporary solution.&n; */
DECL|macro|SND_NDEVS
mdefine_line|#define SND_NDEVS&t;256&t;/* Number of supported devices */
DECL|macro|SND_DEV_CTL
mdefine_line|#define SND_DEV_CTL&t;0&t;/* Control port /dev/mixer */
DECL|macro|SND_DEV_SEQ
mdefine_line|#define SND_DEV_SEQ&t;1&t;/* Sequencer output /dev/sequencer (FM&n;&t;&t;&t;&t;   synthesizer and MIDI output) */
DECL|macro|SND_DEV_MIDIN
mdefine_line|#define SND_DEV_MIDIN&t;2&t;/* Raw midi access */
DECL|macro|SND_DEV_DSP
mdefine_line|#define SND_DEV_DSP&t;3&t;/* Digitized voice /dev/dsp */
DECL|macro|SND_DEV_AUDIO
mdefine_line|#define SND_DEV_AUDIO&t;4&t;/* Sparc compatible /dev/audio */
DECL|macro|SND_DEV_DSP16
mdefine_line|#define SND_DEV_DSP16&t;5&t;/* Like /dev/dsp but 16 bits/sample */
DECL|macro|SND_DEV_STATUS
mdefine_line|#define SND_DEV_STATUS&t;6&t;/* /dev/sndstat */
multiline_comment|/* #7 not in use now. Was in 2.4. Free for use after v3.0. */
DECL|macro|SND_DEV_SEQ2
mdefine_line|#define SND_DEV_SEQ2&t;8&t;/* /dev/sequencer, level 2 interface */
DECL|macro|SND_DEV_SNDPROC
mdefine_line|#define SND_DEV_SNDPROC 9&t;/* /dev/sndproc for programmable devices */
DECL|macro|SND_DEV_PSS
mdefine_line|#define SND_DEV_PSS&t;SND_DEV_SNDPROC
DECL|macro|DSP_DEFAULT_SPEED
mdefine_line|#define DSP_DEFAULT_SPEED&t;8000
DECL|macro|ON
mdefine_line|#define ON&t;&t;1
DECL|macro|OFF
mdefine_line|#define OFF&t;&t;0
DECL|macro|MAX_AUDIO_DEV
mdefine_line|#define MAX_AUDIO_DEV&t;5
DECL|macro|MAX_MIXER_DEV
mdefine_line|#define MAX_MIXER_DEV&t;2
DECL|macro|MAX_SYNTH_DEV
mdefine_line|#define MAX_SYNTH_DEV&t;3
DECL|macro|MAX_MIDI_DEV
mdefine_line|#define MAX_MIDI_DEV&t;6
DECL|macro|MAX_TIMER_DEV
mdefine_line|#define MAX_TIMER_DEV&t;3
DECL|struct|fileinfo
r_struct
id|fileinfo
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* Open mode */
)brace
suffix:semicolon
DECL|struct|address_info
r_struct
id|address_info
(brace
DECL|member|io_base
r_int
id|io_base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SYNTH_MAX_VOICES
mdefine_line|#define SYNTH_MAX_VOICES&t;32
DECL|struct|voice_alloc_info
r_struct
id|voice_alloc_info
(brace
DECL|member|max_voice
r_int
id|max_voice
suffix:semicolon
DECL|member|used_voices
r_int
id|used_voices
suffix:semicolon
DECL|member|ptr
r_int
id|ptr
suffix:semicolon
multiline_comment|/* For device specific use */
DECL|member|map
r_int
r_int
id|map
(braket
id|SYNTH_MAX_VOICES
)braket
suffix:semicolon
multiline_comment|/* (ch &lt;&lt; 8) | (note+1) */
)brace
suffix:semicolon
DECL|struct|channel_info
r_struct
id|channel_info
(brace
DECL|member|pgm_num
r_int
id|pgm_num
suffix:semicolon
DECL|member|controllers
r_int
r_char
id|controllers
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Process wakeup reasons&n; */
DECL|macro|WK_NONE
mdefine_line|#define WK_NONE&t;&t;0x00
DECL|macro|WK_WAKEUP
mdefine_line|#define WK_WAKEUP&t;0x01
DECL|macro|WK_TIMEOUT
mdefine_line|#define WK_TIMEOUT&t;0x02
DECL|macro|WK_SIGNAL
mdefine_line|#define WK_SIGNAL&t;0x04
DECL|macro|WK_SLEEP
mdefine_line|#define WK_SLEEP&t;0x08
DECL|macro|OPEN_READ
mdefine_line|#define OPEN_READ&t;1
DECL|macro|OPEN_WRITE
mdefine_line|#define OPEN_WRITE&t;2
DECL|macro|OPEN_READWRITE
mdefine_line|#define OPEN_READWRITE&t;3
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;sound_calls.h&quot;
macro_line|#include &quot;dev_table.h&quot;
macro_line|#ifndef DEB
DECL|macro|DEB
mdefine_line|#define DEB(x)
DECL|macro|TIMER_ARMED
mdefine_line|#define TIMER_ARMED&t;121234
DECL|macro|TIMER_NOT_ARMED
mdefine_line|#define TIMER_NOT_ARMED&t;1
DECL|macro|FUTURE_VERSION
mdefine_line|#define FUTURE_VERSION
macro_line|#endif
macro_line|#endif
eof
