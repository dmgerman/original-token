macro_line|#ifndef SOUNDCARD_H
DECL|macro|SOUNDCARD_H
mdefine_line|#define SOUNDCARD_H
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE&n; * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; * &n; */
multiline_comment|/* &n;  * If you make modifications to this file, please contact me before&n;  * distributing the modified version. There is already enough &n;  * divercity in the world.&n;  *&n;  * Regards,&n;  * Hannu Savolainen&n;  * hannu@voxware.pp.fi, Hannu.Savolainen@helsinki.fi&n;  */
DECL|macro|SOUND_VERSION
mdefine_line|#define SOUND_VERSION&t;203
DECL|macro|VOXWARE
mdefine_line|#define VOXWARE
macro_line|#include &lt;sys/ioctl.h&gt;
multiline_comment|/*&n; *&t;Supported card ID numbers (Should be somewhere else?)&n; */
DECL|macro|SNDCARD_ADLIB
mdefine_line|#define SNDCARD_ADLIB&t;1
DECL|macro|SNDCARD_SB
mdefine_line|#define SNDCARD_SB&t;2
DECL|macro|SNDCARD_PAS
mdefine_line|#define SNDCARD_PAS&t;3
DECL|macro|SNDCARD_GUS
mdefine_line|#define SNDCARD_GUS&t;4
DECL|macro|SNDCARD_MPU401
mdefine_line|#define SNDCARD_MPU401&t;5
DECL|macro|SNDCARD_SB16
mdefine_line|#define SNDCARD_SB16&t;6
DECL|macro|SNDCARD_SB16MIDI
mdefine_line|#define SNDCARD_SB16MIDI 7
multiline_comment|/***********************************&n; * IOCTL Commands for /dev/sequencer&n; */
macro_line|#ifndef _IOWR
multiline_comment|/*&t;@(#)ioctlp.h */
multiline_comment|/* Ioctl&squot;s have the command encoded in the lower word,&n; * and the size of any in or out parameters in the upper&n; * word.  The high 2 bits of the upper word are used&n; * to encode the in/out status of the parameter; for now&n; * we restrict parameters to at most 128 bytes.&n; */
multiline_comment|/* #define&t;IOCTYPE&t;&t;(0xff&lt;&lt;8) */
DECL|macro|IOCPARM_MASK
mdefine_line|#define&t;IOCPARM_MASK&t;0x7f&t;&t;/* parameters must be &lt; 128 bytes */
DECL|macro|IOC_VOID
mdefine_line|#define&t;IOC_VOID&t;0x00000000&t;/* no parameters */
DECL|macro|IOC_OUT
mdefine_line|#define&t;IOC_OUT&t;&t;0x20000000&t;/* copy out parameters */
DECL|macro|IOC_IN
mdefine_line|#define&t;IOC_IN&t;&t;0x40000000&t;/* copy in parameters */
DECL|macro|IOC_INOUT
mdefine_line|#define&t;IOC_INOUT&t;(IOC_IN|IOC_OUT)
multiline_comment|/* the 0x20000000 is so we can distinguish new ioctl&squot;s from old */
DECL|macro|_IO
mdefine_line|#define&t;_IO(x,y)&t;((int)(IOC_VOID|(x&lt;&lt;8)|y))
DECL|macro|_IOR
mdefine_line|#define&t;_IOR(x,y,t)&t;((int)(IOC_OUT|((sizeof(t)&amp;IOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
DECL|macro|_IOW
mdefine_line|#define&t;_IOW(x,y,t)&t;((int)(IOC_IN|((sizeof(t)&amp;IOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
multiline_comment|/* this should be _IORW, but stdio got there first */
DECL|macro|_IOWR
mdefine_line|#define&t;_IOWR(x,y,t)&t;((int)(IOC_INOUT|((sizeof(t)&amp;IOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
macro_line|#endif  /* !_IOWR */
DECL|macro|SNDCTL_SEQ_RESET
mdefine_line|#define SNDCTL_SEQ_RESET&t;&t;_IO  (&squot;Q&squot;, 0)
DECL|macro|SNDCTL_SEQ_SYNC
mdefine_line|#define SNDCTL_SEQ_SYNC&t;&t;&t;_IO  (&squot;Q&squot;, 1)
DECL|macro|SNDCTL_SYNTH_INFO
mdefine_line|#define SNDCTL_SYNTH_INFO&t;&t;_IOWR(&squot;Q&squot;, 2, struct synth_info)
DECL|macro|SNDCTL_SEQ_CTRLRATE
mdefine_line|#define SNDCTL_SEQ_CTRLRATE&t;&t;_IOWR(&squot;Q&squot;, 3, int)&t;/* Set/get timer resolution (HZ) */
DECL|macro|SNDCTL_SEQ_GETOUTCOUNT
mdefine_line|#define SNDCTL_SEQ_GETOUTCOUNT&t;&t;_IOR (&squot;Q&squot;, 4, int)
DECL|macro|SNDCTL_SEQ_GETINCOUNT
mdefine_line|#define SNDCTL_SEQ_GETINCOUNT&t;&t;_IOR (&squot;Q&squot;, 5, int)
DECL|macro|SNDCTL_SEQ_PERCMODE
mdefine_line|#define SNDCTL_SEQ_PERCMODE&t;&t;_IOW (&squot;Q&squot;, 6, int)
DECL|macro|SNDCTL_FM_LOAD_INSTR
mdefine_line|#define SNDCTL_FM_LOAD_INSTR&t;&t;_IOW (&squot;Q&squot;, 7, struct sbi_instrument)&t;/* Valid for FM only */
DECL|macro|SNDCTL_SEQ_TESTMIDI
mdefine_line|#define SNDCTL_SEQ_TESTMIDI&t;&t;_IOW (&squot;Q&squot;, 8, int)
DECL|macro|SNDCTL_SEQ_RESETSAMPLES
mdefine_line|#define SNDCTL_SEQ_RESETSAMPLES&t;&t;_IOW (&squot;Q&squot;, 9, int)
DECL|macro|SNDCTL_SEQ_NRSYNTHS
mdefine_line|#define SNDCTL_SEQ_NRSYNTHS&t;&t;_IOR (&squot;Q&squot;,10, int)
DECL|macro|SNDCTL_SEQ_NRMIDIS
mdefine_line|#define SNDCTL_SEQ_NRMIDIS&t;&t;_IOR (&squot;Q&squot;,11, int)
DECL|macro|SNDCTL_MIDI_INFO
mdefine_line|#define SNDCTL_MIDI_INFO&t;&t;_IOWR(&squot;Q&squot;,12, struct midi_info)
DECL|macro|SNDCTL_SEQ_TRESHOLD
mdefine_line|#define SNDCTL_SEQ_TRESHOLD&t;&t;_IOW (&squot;Q&squot;,13, int)
DECL|macro|SNDCTL_SYNTH_MEMAVL
mdefine_line|#define SNDCTL_SYNTH_MEMAVL&t;&t;_IOWR(&squot;Q&squot;,14, int)&t;/* in=dev#, out=memsize */
DECL|macro|SNDCTL_FM_4OP_ENABLE
mdefine_line|#define SNDCTL_FM_4OP_ENABLE&t;&t;_IOW (&squot;Q&squot;,15, int)&t;/* in=dev# */
DECL|macro|SNDCTL_PMGR_ACCESS
mdefine_line|#define SNDCTL_PMGR_ACCESS&t;&t;_IOWR(&squot;Q&squot;,16, struct patmgr_info)
multiline_comment|/*&n; *&t;Sample loading mechanism for internal synthesizers (/dev/sequencer)&n; *&t;The following patch_info structure has been designed to support&n; *&t;Gravis UltraSound. It tries to be universal format for uploading&n; *&t;sample based patches but is propably too limited.&n; */
DECL|struct|patch_info
r_struct
id|patch_info
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* Use GUS_PATCH here */
DECL|macro|GUS_PATCH
mdefine_line|#define GUS_PATCH&t;0x04fd
DECL|macro|OBSOLETE_GUS_PATCH
mdefine_line|#define OBSOLETE_GUS_PATCH&t;0x02fd
DECL|member|device_no
r_int
id|device_no
suffix:semicolon
multiline_comment|/* Synthesizer number */
DECL|member|instr_no
r_int
id|instr_no
suffix:semicolon
multiline_comment|/* Midi pgm# */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/*&n; * The least significant byte has the same format than the GUS .PAT&n; * files&n; */
DECL|macro|WAVE_16_BITS
mdefine_line|#define WAVE_16_BITS&t;0x01&t;/* bit 0 = 8 or 16 bit wave data. */
DECL|macro|WAVE_UNSIGNED
mdefine_line|#define WAVE_UNSIGNED&t;0x02&t;/* bit 1 = Signed - Unsigned data. */
DECL|macro|WAVE_LOOPING
mdefine_line|#define WAVE_LOOPING&t;0x04&t;/* bit 2 = looping enabled-1. */
DECL|macro|WAVE_BIDIR_LOOP
mdefine_line|#define WAVE_BIDIR_LOOP&t;0x08&t;/* bit 3 = Set is bidirectional looping. */
DECL|macro|WAVE_LOOP_BACK
mdefine_line|#define WAVE_LOOP_BACK&t;0x10&t;/* bit 4 = Set is looping backward. */
DECL|macro|WAVE_SUSTAIN_ON
mdefine_line|#define WAVE_SUSTAIN_ON&t;0x20&t;/* bit 5 = Turn sustaining on. (Env. pts. 3)*/
DECL|macro|WAVE_ENVELOPES
mdefine_line|#define WAVE_ENVELOPES&t;0x40&t;/* bit 6 = Enable envelopes - 1 */
multiline_comment|/* &t;(use the env_rate/env_offs fields). */
multiline_comment|/* Linux specific bits */
DECL|macro|WAVE_VIBRATO
mdefine_line|#define WAVE_VIBRATO&t;0x00010000&t;/* The vibrato info is valid */
DECL|macro|WAVE_TREMOLO
mdefine_line|#define WAVE_TREMOLO&t;0x00020000&t;/* The tremolo info is valid */
DECL|macro|WAVE_SCALE
mdefine_line|#define WAVE_SCALE&t;0x00040000&t;/* The scaling info is valid */
multiline_comment|/* Other bits must be zeroed */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Size of the wave data in bytes */
DECL|member|loop_start
DECL|member|loop_end
r_int
id|loop_start
comma
id|loop_end
suffix:semicolon
multiline_comment|/* Byte offsets from the beginning */
multiline_comment|/* &n; * The base_freq and base_note fields are used when computing the&n; * playback speed for a note. The base_note defines the tone frequency&n; * which is heard if the sample is played using the base_freq as the&n; * playback speed.&n; *&n; * The low_note and high_note fields define the minimum and maximum note&n; * frequencies for which this sample is valid. It is possible to define&n; * more than one samples for a instrument number at the same time. The&n; * low_note and high_note fields are used to select the most suitable one.&n; *&n; * The fields base_note, high_note and low_note should contain&n; * the note frequency multiplied by 1000. For example value for the&n; * middle A is 440*1000.&n; */
DECL|member|base_freq
r_int
r_int
id|base_freq
suffix:semicolon
DECL|member|base_note
r_int
r_int
id|base_note
suffix:semicolon
DECL|member|high_note
r_int
r_int
id|high_note
suffix:semicolon
DECL|member|low_note
r_int
r_int
id|low_note
suffix:semicolon
DECL|member|panning
r_int
id|panning
suffix:semicolon
multiline_comment|/* -128=left, 127=right */
DECL|member|detuning
r_int
id|detuning
suffix:semicolon
multiline_comment|/*&t;New fields introduced in version 1.99.5&t;*/
multiline_comment|/* Envelope. Enabled by mode bit WAVE_ENVELOPES&t;*/
DECL|member|env_rate
r_int
r_char
id|env_rate
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* GUS HW ramping rate */
DECL|member|env_offset
r_int
r_char
id|env_offset
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 255 == 100% */
multiline_comment|/* &n;&t; * The tremolo, vibrato and scale info are not supported yet.&n;&t; * Enable by setting the mode bits WAVE_TREMOLO, WAVE_VIBRATO or&n;&t; * WAVE_SCALE&n;&t; */
DECL|member|tremolo_sweep
r_int
r_char
id|tremolo_sweep
suffix:semicolon
DECL|member|tremolo_rate
r_int
r_char
id|tremolo_rate
suffix:semicolon
DECL|member|tremolo_depth
r_int
r_char
id|tremolo_depth
suffix:semicolon
DECL|member|vibrato_sweep
r_int
r_char
id|vibrato_sweep
suffix:semicolon
DECL|member|vibrato_rate
r_int
r_char
id|vibrato_rate
suffix:semicolon
DECL|member|vibrato_depth
r_int
r_char
id|vibrato_depth
suffix:semicolon
DECL|member|scale_frequency
r_int
id|scale_frequency
suffix:semicolon
DECL|member|scale_factor
r_int
r_int
id|scale_factor
suffix:semicolon
multiline_comment|/* from 0 to 2048 or 0 to 2 */
DECL|member|volume
r_int
id|volume
suffix:semicolon
DECL|member|spare
r_int
id|spare
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* The waveform data starts here */
)brace
suffix:semicolon
multiline_comment|/*&n; * Patch management interface (/dev/sequencer, /dev/patmgr#)&n; * Don&squot;t use these calls if you want to maintain compatibility with&n; * the future versions of the driver.&n; */
DECL|macro|PS_NO_PATCHES
mdefine_line|#define &t;PS_NO_PATCHES&t;&t;0&t;/* No patch support on device */
DECL|macro|PS_MGR_NOT_OK
mdefine_line|#define&t;&t;PS_MGR_NOT_OK&t;&t;1&t;/* Plain patch support (no mgr) */
DECL|macro|PS_MGR_OK
mdefine_line|#define&t;&t;PS_MGR_OK&t;&t;2&t;/* Patch manager supported */
DECL|macro|PS_MANAGED
mdefine_line|#define&t;&t;PS_MANAGED&t;&t;3&t;/* Patch manager running */
DECL|macro|SNDCTL_PMGR_IFACE
mdefine_line|#define SNDCTL_PMGR_IFACE&t;&t;_IOWR(&squot;P&squot;, 1, struct patmgr_info)
multiline_comment|/*&n; * The patmgr_info is a fixed size structure which is used for two&n; * different purposes. The intended use is for communication between&n; * the application using /dev/sequencer and the patch manager daemon&n; * associated with a synthesizer device (ioctl(SNDCTL_PMGR_ACCESS)).&n; *&n; * This structure is also used with ioctl(SNDCTL_PGMR_IFACE) which allows&n; * a patch manager daemon to read and write device parameters. This&n; * ioctl available through /dev/sequencer also. Avoid using it since it&squot;s&n; * extremely hardware dependent. In addition access trough /dev/sequencer &n; * may confuse the patch manager daemon.&n; */
DECL|struct|patmgr_info
r_struct
id|patmgr_info
(brace
multiline_comment|/* Note! size must be &lt; 4k since kmalloc() is used */
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
multiline_comment|/* Don&squot;t worry. Reserved for communication&n;&t;  &t;&t;&t;   between the patch manager and the driver. */
DECL|macro|PM_K_EVENT
mdefine_line|#define PM_K_EVENT&t;&t;1 /* Event from the /dev/sequencer driver */
DECL|macro|PM_K_COMMAND
mdefine_line|#define PM_K_COMMAND&t;&t;2 /* Request from a application */
DECL|macro|PM_K_RESPONSE
mdefine_line|#define PM_K_RESPONSE&t;&t;3 /* From patmgr to application */
DECL|macro|PM_ERROR
mdefine_line|#define PM_ERROR&t;&t;4 /* Error returned by the patmgr */
DECL|member|device
r_int
id|device
suffix:semicolon
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* &n; * Commands 0x000 to 0xfff reserved for patch manager programs &n; */
DECL|macro|PM_GET_DEVTYPE
mdefine_line|#define PM_GET_DEVTYPE&t;1&t;/* Returns type of the patch mgr interface of dev */
DECL|macro|PMTYPE_FM2
mdefine_line|#define&t;&t;PMTYPE_FM2&t;1&t;/* 2 OP fm */
DECL|macro|PMTYPE_FM4
mdefine_line|#define&t;&t;PMTYPE_FM4&t;2&t;/* Mixed 4 or 2 op FM (OPL-3) */
DECL|macro|PMTYPE_WAVE
mdefine_line|#define&t;&t;PMTYPE_WAVE&t;3&t;/* Wave table synthesizer (GUS) */
DECL|macro|PM_GET_NRPGM
mdefine_line|#define PM_GET_NRPGM&t;2&t;/* Returns max # of midi programs in parm1 */
DECL|macro|PM_GET_PGMMAP
mdefine_line|#define PM_GET_PGMMAP&t;3&t;/* Returns map of loaded midi programs in data8 */
DECL|macro|PM_GET_PGM_PATCHES
mdefine_line|#define PM_GET_PGM_PATCHES 4&t;/* Return list of patches of a program (parm1) */
DECL|macro|PM_GET_PATCH
mdefine_line|#define PM_GET_PATCH&t;5&t;/* Return patch header of patch parm1 */
DECL|macro|PM_SET_PATCH
mdefine_line|#define PM_SET_PATCH&t;6&t;/* Set patch header of patch parm1 */
DECL|macro|PM_READ_PATCH
mdefine_line|#define PM_READ_PATCH&t;7&t;/* Read patch (wave) data */
DECL|macro|PM_WRITE_PATCH
mdefine_line|#define PM_WRITE_PATCH&t;8&t;/* Write patch (wave) data */
multiline_comment|/*&n; * Commands 0x1000 to 0xffff are for communication between the patch manager&n; * and the client&n; */
DECL|macro|_PM_LOAD_PATCH
mdefine_line|#define _PM_LOAD_PATCH&t;0x100
multiline_comment|/* &n; * Commands above 0xffff reserved for device specific use&n; */
DECL|member|parm1
r_int
id|parm1
suffix:semicolon
DECL|member|parm2
r_int
id|parm2
suffix:semicolon
DECL|member|parm3
r_int
id|parm3
suffix:semicolon
r_union
(brace
DECL|member|data8
r_int
r_char
id|data8
(braket
l_int|4000
)braket
suffix:semicolon
DECL|member|data16
r_int
r_int
id|data16
(braket
l_int|2000
)braket
suffix:semicolon
DECL|member|data32
r_int
r_int
id|data32
(braket
l_int|1000
)braket
suffix:semicolon
DECL|member|patch
r_struct
id|patch_info
id|patch
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * When a patch manager daemon is present, it will be informed by the&n; * driver when something important happens. For example when the&n; * /dev/sequencer is opened or closed. A record with key == PM_K_EVENT is&n; * returned. The command field contains the event type:&n; */
DECL|macro|PM_E_OPENED
mdefine_line|#define PM_E_OPENED&t;&t;1&t;/* /dev/sequencer opened */
DECL|macro|PM_E_CLOSED
mdefine_line|#define PM_E_CLOSED&t;&t;2&t;/* /dev/sequencer closed */
DECL|macro|PM_E_PATCH_RESET
mdefine_line|#define PM_E_PATCH_RESET&t;3&t;/* SNDCTL_RESETSAMPLES called */
DECL|macro|PM_E_PATCH_LOADED
mdefine_line|#define PM_E_PATCH_LOADED&t;4&t;/* A patch has been loaded by appl */
multiline_comment|/*&n; * /dev/sequencer input events.&n; *&n; * The data written to the /dev/sequencer is a stream of events. Events&n; * are records of 4 or 8 bytes. The first byte defines the size. &n; * Any number of events can be written with a write call. There&n; * is a set of macros for sending these events. Use these macros if you&n; * want to maximize portability of your program.&n; *&n; * Events SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO. Are also input events.&n; * (All input events are currently 4 bytes long. Be prepared to support&n; * 8 byte events also. If you receive any event having first byte &gt;= 0xf0,&n; * it&squot;s a 8 byte event.&n; *&n; * The events are documented at the end of this file.&n; *&n; * Normal events (4 bytes)&n; * There is also a 8 byte version of most of the 4 byte events. The&n; * 8 byte one is recommended.&n; */
DECL|macro|SEQ_NOTEOFF
mdefine_line|#define SEQ_NOTEOFF&t;&t;0
DECL|macro|SEQ_FMNOTEOFF
mdefine_line|#define SEQ_FMNOTEOFF&t;&t;SEQ_NOTEOFF&t;/* Just old name */
DECL|macro|SEQ_NOTEON
mdefine_line|#define SEQ_NOTEON&t;&t;1
DECL|macro|SEQ_FMNOTEON
mdefine_line|#define&t;SEQ_FMNOTEON&t;&t;SEQ_NOTEON
DECL|macro|SEQ_WAIT
mdefine_line|#define SEQ_WAIT&t;&t;2
DECL|macro|SEQ_PGMCHANGE
mdefine_line|#define SEQ_PGMCHANGE&t;&t;3
DECL|macro|SEQ_FMPGMCHANGE
mdefine_line|#define SEQ_FMPGMCHANGE&t;&t;SEQ_PGMCHANGE
DECL|macro|SEQ_SYNCTIMER
mdefine_line|#define SEQ_SYNCTIMER&t;&t;4
DECL|macro|SEQ_MIDIPUTC
mdefine_line|#define SEQ_MIDIPUTC&t;&t;5
DECL|macro|SEQ_DRUMON
mdefine_line|#define SEQ_DRUMON&t;&t;6&t;/*** OBSOLETE ***/
DECL|macro|SEQ_DRUMOFF
mdefine_line|#define SEQ_DRUMOFF&t;&t;7&t;/*** OBSOLETE ***/
DECL|macro|SEQ_ECHO
mdefine_line|#define SEQ_ECHO&t;&t;8&t;/* For synching programs with output */
DECL|macro|SEQ_AFTERTOUCH
mdefine_line|#define SEQ_AFTERTOUCH&t;&t;9
DECL|macro|SEQ_CONTROLLER
mdefine_line|#define SEQ_CONTROLLER&t;&t;10
DECL|macro|CTRL_PITCH_BENDER
mdefine_line|#define    CTRL_PITCH_BENDER&t;&t;255
DECL|macro|CTRL_PITCH_BENDER_RANGE
mdefine_line|#define    CTRL_PITCH_BENDER_RANGE&t;254
DECL|macro|CTRL_EXPRESSION
mdefine_line|#define    CTRL_EXPRESSION&t;&t;253
DECL|macro|CTRL_MAIN_VOLUME
mdefine_line|#define    CTRL_MAIN_VOLUME&t;&t;252
DECL|macro|SEQ_BALANCE
mdefine_line|#define SEQ_BALANCE&t;&t;11
DECL|macro|SEQ_VOLMODE
mdefine_line|#define SEQ_VOLMODE             12
multiline_comment|/*&n; * Volume mode decides how volumes are used&n; */
DECL|macro|VOL_METHOD_ADAGIO
mdefine_line|#define VOL_METHOD_ADAGIO&t;1
DECL|macro|VOL_METHOD_LINEAR
mdefine_line|#define VOL_METHOD_LINEAR&t;2
multiline_comment|/*&n; * Note! SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO are used also as&n; *&t; input events.&n; */
multiline_comment|/*&n; * Event codes 0xf0 to 0xfc are reserved for future extensions.&n; */
DECL|macro|SEQ_FULLSIZE
mdefine_line|#define SEQ_FULLSIZE&t;&t;0xfd&t;/* Long events */
multiline_comment|/*&n; *&t;SEQ_FULLSIZE events are used for loading patches/samples to the&n; *&t;synthesizer devices. These events are passed directly to the driver&n; *&t;of the associated synthesizer device. There is no limit to the size&n; *&t;of the extended events. These events are not queued but executed&n; *&t;immediately when the write() is called (execution can take several&n; *&t;seconds of time). &n; *&n; *&t;When a SEQ_FULLSIZE message is written to the device, it must&n; *&t;be written using exactly one write() call. Other events cannot&n; *&t;be mixed to the same write.&n; *&t;&n; *&t;For FM synths (YM3812/OPL3) use struct sbi_instrument and write it to the &n; *&t;/dev/sequencer. Don&squot;t write other data together with the instrument structure&n; *&t;Set the key field of the structure to FM_PATCH. The device field is used to&n; *&t;route the patch to the corresponding device.&n; *&n; *&t;For Gravis UltraSound use struct patch_info. Initialize the key field&n; *      to GUS_PATCH.&n; */
DECL|macro|SEQ_PRIVATE
mdefine_line|#define SEQ_PRIVATE&t;&t;0xfe&t;/* Low level HW dependent events (8 bytes) */
DECL|macro|SEQ_EXTENDED
mdefine_line|#define SEQ_EXTENDED&t;&t;0xff&t;/* Extended events (8 bytes) */
multiline_comment|/*&n; *&t;Extended events for synthesizers (8 bytes)&n; *&n; *&t;Format:&n; *&n; *&t;&t;b0&t;= SEQ_EXTENDED&n; *&t;&t;b1&t;= command&n; *&t;&t;b2&t;= device&n; *&t;&t;b3-b7&t;= parameters&n; *&n; *&t;Command&t;&t;&t;&t;b3&t;b4&t;b5&t;b6&t;b7&n; *&t;----------------------------------------------------------------------------&n; *&t;SEQ_NOTEON&t;&t;&t;voice&t;note&t;volume&t;0&t;0&n; *&t;SEQ_NOTEOFF&t;&t;&t;voice&t;note&t;volume&t;0&t;0&n; *&t;SEQ_PGMCHANGE&t;&t;&t;voice&t;pgm&t;0&t;0&t;0&n; *&t;SEQ_DRUMON&t;&t;&t;(voice)&t;drum#&t;volume&t;0&t;0&n; *&t;SEQ_DRUMOFF&t;&t;&t;(voice)&t;drum#&t;volume&t;0&t;0&n; */
multiline_comment|/*&n; * Record for FM patches&n; */
DECL|typedef|sbi_instr_data
r_typedef
r_int
r_char
id|sbi_instr_data
(braket
l_int|32
)braket
suffix:semicolon
DECL|struct|sbi_instrument
r_struct
id|sbi_instrument
(brace
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
multiline_comment|/* &t;Initialize to FM_PATCH or OPL3_PATCH */
DECL|macro|FM_PATCH
mdefine_line|#define FM_PATCH&t;0x01fd
DECL|macro|OPL3_PATCH
mdefine_line|#define OPL3_PATCH&t;0x03fd
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/*&t;Synth# (0-4)&t;*/
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/*&t;Program# to be initialized &t;*/
DECL|member|operators
id|sbi_instr_data
id|operators
suffix:semicolon
multiline_comment|/*&t;Register settings for operator cells (.SBI format)&t;*/
)brace
suffix:semicolon
DECL|struct|synth_info
r_struct
id|synth_info
(brace
multiline_comment|/* Read only */
DECL|member|name
r_char
id|name
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* 0-N. INITIALIZE BEFORE CALLING */
DECL|member|synth_type
r_int
id|synth_type
suffix:semicolon
DECL|macro|SYNTH_TYPE_FM
mdefine_line|#define SYNTH_TYPE_FM&t;&t;&t;0
DECL|macro|SYNTH_TYPE_SAMPLE
mdefine_line|#define SYNTH_TYPE_SAMPLE&t;&t;1
DECL|member|synth_subtype
r_int
id|synth_subtype
suffix:semicolon
DECL|macro|FM_TYPE_ADLIB
mdefine_line|#define FM_TYPE_ADLIB&t;&t;&t;0x00
DECL|macro|FM_TYPE_OPL3
mdefine_line|#define FM_TYPE_OPL3&t;&t;&t;0x01
DECL|macro|SAMPLE_TYPE_GUS
mdefine_line|#define SAMPLE_TYPE_GUS&t;&t;&t;0x10
DECL|member|perc_mode
r_int
id|perc_mode
suffix:semicolon
multiline_comment|/* No longer supported */
DECL|member|nr_voices
r_int
id|nr_voices
suffix:semicolon
DECL|member|nr_drums
r_int
id|nr_drums
suffix:semicolon
multiline_comment|/* Obsolete field */
DECL|member|instr_bank_size
r_int
id|instr_bank_size
suffix:semicolon
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
DECL|macro|SYNTH_CAP_PERCMODE
mdefine_line|#define SYNTH_CAP_PERCMODE&t;&t;0x00000001 /* No longer used */
DECL|macro|SYNTH_CAP_OPL3
mdefine_line|#define SYNTH_CAP_OPL3&t;&t;&t;0x00000002 /* Set if OPL3 supported */
DECL|member|dummies
r_int
id|dummies
(braket
l_int|19
)braket
suffix:semicolon
multiline_comment|/* Reserve space */
)brace
suffix:semicolon
DECL|struct|midi_info
r_struct
id|midi_info
(brace
DECL|member|name
r_char
id|name
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* 0-N. INITIALIZE BEFORE CALLING */
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* To be defined later */
DECL|member|dev_type
r_int
id|dev_type
suffix:semicolon
DECL|member|dummies
r_int
id|dummies
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* Reserve space */
)brace
suffix:semicolon
multiline_comment|/********************************************&n; * IOCTL commands for /dev/dsp and /dev/audio&n; */
DECL|macro|SNDCTL_DSP_RESET
mdefine_line|#define SNDCTL_DSP_RESET&t;&t;_IO  (&squot;P&squot;, 0)
DECL|macro|SNDCTL_DSP_SYNC
mdefine_line|#define SNDCTL_DSP_SYNC&t;&t;&t;_IO  (&squot;P&squot;, 1)
DECL|macro|SNDCTL_DSP_SPEED
mdefine_line|#define SNDCTL_DSP_SPEED&t;&t;_IOWR(&squot;P&squot;, 2, int)
DECL|macro|SNDCTL_DSP_STEREO
mdefine_line|#define SNDCTL_DSP_STEREO&t;&t;_IOWR(&squot;P&squot;, 3, int)
DECL|macro|SNDCTL_DSP_GETBLKSIZE
mdefine_line|#define SNDCTL_DSP_GETBLKSIZE&t;&t;_IOWR(&squot;P&squot;, 4, int)
DECL|macro|SNDCTL_DSP_SAMPLESIZE
mdefine_line|#define SNDCTL_DSP_SAMPLESIZE&t;&t;_IOWR(&squot;P&squot;, 5, int)&t;/* 8, 12 or 16 */
DECL|macro|SOUND_PCM_WRITE_CHANNELS
mdefine_line|#define SOUND_PCM_WRITE_CHANNELS&t;_IOWR(&squot;P&squot;, 6, int)
DECL|macro|SOUND_PCM_WRITE_FILTER
mdefine_line|#define SOUND_PCM_WRITE_FILTER&t;&t;_IOWR(&squot;P&squot;, 7, int)
DECL|macro|SNDCTL_DSP_POST
mdefine_line|#define SNDCTL_DSP_POST&t;&t;&t;_IO  (&squot;P&squot;, 8)
DECL|macro|SNDCTL_DSP_SUBDIVIDE
mdefine_line|#define SNDCTL_DSP_SUBDIVIDE&t;&t;_IOWR(&squot;P&squot;, 9, int)
DECL|macro|SOUND_PCM_READ_RATE
mdefine_line|#define SOUND_PCM_READ_RATE&t;&t;_IOR (&squot;P&squot;, 2, int)
DECL|macro|SOUND_PCM_READ_CHANNELS
mdefine_line|#define SOUND_PCM_READ_CHANNELS&t;&t;_IOR (&squot;P&squot;, 6, int)
DECL|macro|SOUND_PCM_READ_BITS
mdefine_line|#define SOUND_PCM_READ_BITS&t;&t;_IOR (&squot;P&squot;, 5, int)
DECL|macro|SOUND_PCM_READ_FILTER
mdefine_line|#define SOUND_PCM_READ_FILTER&t;&t;_IOR (&squot;P&squot;, 7, int)
multiline_comment|/* Some alias names */
DECL|macro|SOUND_PCM_WRITE_BITS
mdefine_line|#define SOUND_PCM_WRITE_BITS&t;&t;SNDCTL_DSP_SAMPLESIZE
DECL|macro|SOUND_PCM_WRITE_RATE
mdefine_line|#define SOUND_PCM_WRITE_RATE&t;&t;SNDCTL_DSP_SPEED
DECL|macro|SOUND_PCM_POST
mdefine_line|#define SOUND_PCM_POST&t;&t;&t;SNDCTL_DSP_POST
DECL|macro|SOUND_PCM_RESET
mdefine_line|#define SOUND_PCM_RESET&t;&t;&t;SNDCTL_DSP_RESET
DECL|macro|SOUND_PCM_SYNC
mdefine_line|#define SOUND_PCM_SYNC&t;&t;&t;SNDCTL_DSP_SYNC
DECL|macro|SOUND_PCM_SUBDIVIDE
mdefine_line|#define SOUND_PCM_SUBDIVIDE&t;&t;SNDCTL_DSP_SUBDIVIDE
multiline_comment|/*********************************************&n; * IOCTL commands for /dev/mixer&n; */
multiline_comment|/* &n; * Mixer devices&n; *&n; * There can be up to 20 different analog mixer channels. The&n; * SOUND_MIXER_NRDEVICES gives the currently supported maximum. &n; * The SOUND_MIXER_READ_DEVMASK returns a bitmask which tells&n; * the devices supported by the particular mixer.&n; */
DECL|macro|SOUND_MIXER_NRDEVICES
mdefine_line|#define SOUND_MIXER_NRDEVICES&t;12
DECL|macro|SOUND_MIXER_VOLUME
mdefine_line|#define SOUND_MIXER_VOLUME&t;0
DECL|macro|SOUND_MIXER_BASS
mdefine_line|#define SOUND_MIXER_BASS&t;1
DECL|macro|SOUND_MIXER_TREBLE
mdefine_line|#define SOUND_MIXER_TREBLE&t;2
DECL|macro|SOUND_MIXER_SYNTH
mdefine_line|#define SOUND_MIXER_SYNTH&t;3
DECL|macro|SOUND_MIXER_PCM
mdefine_line|#define SOUND_MIXER_PCM&t;&t;4
DECL|macro|SOUND_MIXER_SPEAKER
mdefine_line|#define SOUND_MIXER_SPEAKER&t;5
DECL|macro|SOUND_MIXER_LINE
mdefine_line|#define SOUND_MIXER_LINE&t;6
DECL|macro|SOUND_MIXER_MIC
mdefine_line|#define SOUND_MIXER_MIC&t;&t;7
DECL|macro|SOUND_MIXER_CD
mdefine_line|#define SOUND_MIXER_CD&t;&t;8
DECL|macro|SOUND_MIXER_IMIX
mdefine_line|#define SOUND_MIXER_IMIX&t;9&t;/*  Recording monitor  */
DECL|macro|SOUND_MIXER_ALTPCM
mdefine_line|#define SOUND_MIXER_ALTPCM&t;10
DECL|macro|SOUND_MIXER_RECLEV
mdefine_line|#define SOUND_MIXER_RECLEV&t;11&t;/* Recording level */
multiline_comment|/* Some on/off settings (SOUND_SPECIAL_MIN - SOUND_SPECIAL_MAX) */
multiline_comment|/* Not counted to SOUND_MIXER_NRDEVICES, but use the same number space */
DECL|macro|SOUND_ONOFF_MIN
mdefine_line|#define SOUND_ONOFF_MIN&t;&t;28
DECL|macro|SOUND_ONOFF_MAX
mdefine_line|#define SOUND_ONOFF_MAX&t;&t;30
DECL|macro|SOUND_MIXER_MUTE
mdefine_line|#define SOUND_MIXER_MUTE&t;28&t;/* 0 or 1 */
DECL|macro|SOUND_MIXER_ENHANCE
mdefine_line|#define SOUND_MIXER_ENHANCE&t;29&t;/* Enhanced stereo (0, 40, 60 or 80) */
DECL|macro|SOUND_MIXER_LOUD
mdefine_line|#define SOUND_MIXER_LOUD&t;30&t;/* 0 or 1 */
multiline_comment|/* Note!&t;Number 31 cannot be used since the sign bit is reserved */
DECL|macro|SOUND_DEVICE_LABELS
mdefine_line|#define SOUND_DEVICE_LABELS&t;{&quot;Vol  &quot;, &quot;Bass &quot;, &quot;Trebl&quot;, &quot;Synth&quot;, &quot;Pcm  &quot;, &quot;Spkr &quot;, &quot;Line &quot;, &bslash;&n;&t;&t;&t;&t; &quot;Mic  &quot;, &quot;CD   &quot;, &quot;Mix  &quot;, &quot;Pcm2 &quot;, &quot;rec&quot;}
DECL|macro|SOUND_DEVICE_NAMES
mdefine_line|#define SOUND_DEVICE_NAMES&t;{&quot;vol&quot;, &quot;bass&quot;, &quot;treble&quot;, &quot;synth&quot;, &quot;pcm&quot;, &quot;speaker&quot;, &quot;line&quot;, &bslash;&n;&t;&t;&t;&t; &quot;mic&quot;, &quot;cd&quot;, &quot;mix&quot;, &quot;pcm2&quot;, &quot;rec&quot;}
multiline_comment|/*&t;Device bitmask identifiers&t;*/
DECL|macro|SOUND_MIXER_RECSRC
mdefine_line|#define SOUND_MIXER_RECSRC&t;0xff&t;/* Arg contains a bit for each recording source */
DECL|macro|SOUND_MIXER_DEVMASK
mdefine_line|#define SOUND_MIXER_DEVMASK&t;0xfe&t;/* Arg contains a bit for each supported device */
DECL|macro|SOUND_MIXER_RECMASK
mdefine_line|#define SOUND_MIXER_RECMASK&t;0xfd&t;/* Arg contains a bit for each supported recording source */
DECL|macro|SOUND_MIXER_CAPS
mdefine_line|#define SOUND_MIXER_CAPS&t;0xfc
DECL|macro|SOUND_CAP_EXCL_INPUT
mdefine_line|#define SOUND_CAP_EXCL_INPUT&t;0x00000001&t;/* Only one recording source at a time */
DECL|macro|SOUND_MIXER_STEREODEVS
mdefine_line|#define SOUND_MIXER_STEREODEVS&t;0xfb&t;/* Mixer channels supporting stereo */
multiline_comment|/*&t;Device mask bits&t;*/
DECL|macro|SOUND_MASK_VOLUME
mdefine_line|#define SOUND_MASK_VOLUME&t;(1 &lt;&lt; SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MASK_BASS
mdefine_line|#define SOUND_MASK_BASS&t;&t;(1 &lt;&lt; SOUND_MIXER_BASS)
DECL|macro|SOUND_MASK_TREBLE
mdefine_line|#define SOUND_MASK_TREBLE&t;(1 &lt;&lt; SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MASK_SYNTH
mdefine_line|#define SOUND_MASK_SYNTH&t;(1 &lt;&lt; SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MASK_PCM
mdefine_line|#define SOUND_MASK_PCM&t;&t;(1 &lt;&lt; SOUND_MIXER_PCM)
DECL|macro|SOUND_MASK_SPEAKER
mdefine_line|#define SOUND_MASK_SPEAKER&t;(1 &lt;&lt; SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MASK_LINE
mdefine_line|#define SOUND_MASK_LINE&t;&t;(1 &lt;&lt; SOUND_MIXER_LINE)
DECL|macro|SOUND_MASK_MIC
mdefine_line|#define SOUND_MASK_MIC&t;&t;(1 &lt;&lt; SOUND_MIXER_MIC)
DECL|macro|SOUND_MASK_CD
mdefine_line|#define SOUND_MASK_CD&t;&t;(1 &lt;&lt; SOUND_MIXER_CD)
DECL|macro|SOUND_MASK_IMIX
mdefine_line|#define SOUND_MASK_IMIX&t;&t;(1 &lt;&lt; SOUND_MIXER_IMIX)
DECL|macro|SOUND_MASK_ALTPCM
mdefine_line|#define SOUND_MASK_ALTPCM&t;(1 &lt;&lt; SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MASK_RECLEV
mdefine_line|#define SOUND_MASK_RECLEV&t;(1 &lt;&lt; SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MASK_MUTE
mdefine_line|#define SOUND_MASK_MUTE&t;&t;(1 &lt;&lt; SOUND_MIXER_MUTE)
DECL|macro|SOUND_MASK_ENHANCE
mdefine_line|#define SOUND_MASK_ENHANCE&t;(1 &lt;&lt; SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MASK_LOUD
mdefine_line|#define SOUND_MASK_LOUD&t;&t;(1 &lt;&lt; SOUND_MIXER_LOUD)
DECL|macro|MIXER_READ
mdefine_line|#define MIXER_READ(dev)&t;&t;_IOR(&squot;M&squot;, dev, int)
DECL|macro|SOUND_MIXER_READ_VOLUME
mdefine_line|#define SOUND_MIXER_READ_VOLUME&t;&t;MIXER_READ(SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MIXER_READ_BASS
mdefine_line|#define SOUND_MIXER_READ_BASS&t;&t;MIXER_READ(SOUND_MIXER_BASS)
DECL|macro|SOUND_MIXER_READ_TREBLE
mdefine_line|#define SOUND_MIXER_READ_TREBLE&t;&t;MIXER_READ(SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MIXER_READ_SYNTH
mdefine_line|#define SOUND_MIXER_READ_SYNTH&t;&t;MIXER_READ(SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MIXER_READ_PCM
mdefine_line|#define SOUND_MIXER_READ_PCM&t;&t;MIXER_READ(SOUND_MIXER_PCM)
DECL|macro|SOUND_MIXER_READ_SPEAKER
mdefine_line|#define SOUND_MIXER_READ_SPEAKER&t;MIXER_READ(SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_READ_LINE
mdefine_line|#define SOUND_MIXER_READ_LINE&t;&t;MIXER_READ(SOUND_MIXER_LINE)
DECL|macro|SOUND_MIXER_READ_MIC
mdefine_line|#define SOUND_MIXER_READ_MIC&t;&t;MIXER_READ(SOUND_MIXER_MIC)
DECL|macro|SOUND_MIXER_READ_CD
mdefine_line|#define SOUND_MIXER_READ_CD&t;&t;MIXER_READ(SOUND_MIXER_CD)
DECL|macro|SOUND_MIXER_READ_IMIX
mdefine_line|#define SOUND_MIXER_READ_IMIX&t;&t;MIXER_READ(SOUND_MIXER_IMIX)
DECL|macro|SOUND_MIXER_READ_ALTPCM
mdefine_line|#define SOUND_MIXER_READ_ALTPCM&t;&t;MIXER_READ(SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MIXER_READ_RECLEV
mdefine_line|#define SOUND_MIXER_READ_RECLEV&t;&t;MIXER_READ(SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MIXER_READ_MUTE
mdefine_line|#define SOUND_MIXER_READ_MUTE&t;&t;MIXER_READ(SOUND_MIXER_MUTE)
DECL|macro|SOUND_MIXER_READ_ENHANCE
mdefine_line|#define SOUND_MIXER_READ_ENHANCE&t;MIXER_READ(SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MIXER_READ_LOUD
mdefine_line|#define SOUND_MIXER_READ_LOUD&t;&t;MIXER_READ(SOUND_MIXER_LOUD)
DECL|macro|SOUND_MIXER_READ_RECSRC
mdefine_line|#define SOUND_MIXER_READ_RECSRC&t;&t;MIXER_READ(SOUND_MIXER_RECSRC)
DECL|macro|SOUND_MIXER_READ_DEVMASK
mdefine_line|#define SOUND_MIXER_READ_DEVMASK&t;MIXER_READ(SOUND_MIXER_DEVMASK)
DECL|macro|SOUND_MIXER_READ_RECMASK
mdefine_line|#define SOUND_MIXER_READ_RECMASK&t;MIXER_READ(SOUND_MIXER_RECMASK)
DECL|macro|SOUND_MIXER_READ_STEREODEVS
mdefine_line|#define SOUND_MIXER_READ_STEREODEVS&t;MIXER_READ(SOUND_MIXER_STEREODEVS)
DECL|macro|SOUND_MIXER_READ_CAPS
mdefine_line|#define SOUND_MIXER_READ_CAPS&t;&t;MIXER_READ(SOUND_MIXER_CAPS)
DECL|macro|MIXER_WRITE
mdefine_line|#define MIXER_WRITE(dev)&t;&t;_IOWR(&squot;M&squot;, dev, int)
DECL|macro|SOUND_MIXER_WRITE_VOLUME
mdefine_line|#define SOUND_MIXER_WRITE_VOLUME&t;MIXER_WRITE(SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MIXER_WRITE_BASS
mdefine_line|#define SOUND_MIXER_WRITE_BASS&t;&t;MIXER_WRITE(SOUND_MIXER_BASS)
DECL|macro|SOUND_MIXER_WRITE_TREBLE
mdefine_line|#define SOUND_MIXER_WRITE_TREBLE&t;MIXER_WRITE(SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MIXER_WRITE_SYNTH
mdefine_line|#define SOUND_MIXER_WRITE_SYNTH&t;&t;MIXER_WRITE(SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MIXER_WRITE_PCM
mdefine_line|#define SOUND_MIXER_WRITE_PCM&t;&t;MIXER_WRITE(SOUND_MIXER_PCM)
DECL|macro|SOUND_MIXER_WRITE_SPEAKER
mdefine_line|#define SOUND_MIXER_WRITE_SPEAKER&t;MIXER_WRITE(SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_WRITE_LINE
mdefine_line|#define SOUND_MIXER_WRITE_LINE&t;&t;MIXER_WRITE(SOUND_MIXER_LINE)
DECL|macro|SOUND_MIXER_WRITE_MIC
mdefine_line|#define SOUND_MIXER_WRITE_MIC&t;&t;MIXER_WRITE(SOUND_MIXER_MIC)
DECL|macro|SOUND_MIXER_WRITE_CD
mdefine_line|#define SOUND_MIXER_WRITE_CD&t;&t;MIXER_WRITE(SOUND_MIXER_CD)
DECL|macro|SOUND_MIXER_WRITE_IMIX
mdefine_line|#define SOUND_MIXER_WRITE_IMIX&t;&t;MIXER_WRITE(SOUND_MIXER_IMIX)
DECL|macro|SOUND_MIXER_WRITE_ALTPCM
mdefine_line|#define SOUND_MIXER_WRITE_ALTPCM&t;MIXER_WRITE(SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MIXER_WRITE_RECLEV
mdefine_line|#define SOUND_MIXER_WRITE_RECLEV&t;MIXER_WRITE(SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MIXER_WRITE_MUTE
mdefine_line|#define SOUND_MIXER_WRITE_MUTE&t;&t;MIXER_WRITE(SOUND_MIXER_MUTE)
DECL|macro|SOUND_MIXER_WRITE_ENHANCE
mdefine_line|#define SOUND_MIXER_WRITE_ENHANCE&t;MIXER_WRITE(SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MIXER_WRITE_LOUD
mdefine_line|#define SOUND_MIXER_WRITE_LOUD&t;&t;MIXER_WRITE(SOUND_MIXER_LOUD)
DECL|macro|SOUND_MIXER_WRITE_RECSRC
mdefine_line|#define SOUND_MIXER_WRITE_RECSRC&t;MIXER_WRITE(SOUND_MIXER_RECSRC)
multiline_comment|/*&n; *&t;The following mixer ioctl calls are compatible with the BSD driver by&n; *&t;  Steve Haehnichen &lt;shaehnic@ucsd.edu&gt;&n; *&n; * Since this interface is entirely SB specific, it will be dropped in the&n; * near future.&n; */
DECL|typedef|S_BYTE
r_typedef
r_int
r_char
id|S_BYTE
suffix:semicolon
DECL|typedef|S_FLAG
r_typedef
r_int
r_char
id|S_FLAG
suffix:semicolon
DECL|struct|stereo_vol
r_struct
id|stereo_vol
(brace
DECL|member|l
id|S_BYTE
id|l
suffix:semicolon
multiline_comment|/* Left volume */
DECL|member|r
id|S_BYTE
id|r
suffix:semicolon
multiline_comment|/* Right volume */
)brace
suffix:semicolon
DECL|macro|MIXER_IOCTL_SET_LEVELS
mdefine_line|#define MIXER_IOCTL_SET_LEVELS &t;&t;_IOW (&squot;s&squot;, 20, struct sb_mixer_levels)
DECL|macro|MIXER_IOCTL_SET_PARAMS
mdefine_line|#define MIXER_IOCTL_SET_PARAMS &t;&t;_IOW (&squot;s&squot;, 21, struct sb_mixer_params)
DECL|macro|MIXER_IOCTL_READ_LEVELS
mdefine_line|#define MIXER_IOCTL_READ_LEVELS &t;_IOR (&squot;s&squot;, 22, struct sb_mixer_levels)
DECL|macro|MIXER_IOCTL_READ_PARAMS
mdefine_line|#define MIXER_IOCTL_READ_PARAMS &t;_IOR (&squot;s&squot;, 23, struct sb_mixer_params)
DECL|macro|MIXER_IOCTL_RESET
mdefine_line|#define MIXER_IOCTL_RESET&t;&t;_IO  (&squot;s&squot;, 24)
multiline_comment|/*&n; * Mixer volume levels for MIXER_IOCTL_SET_VOL &amp; MIXER_IOCTL_READ_VOL&n; */
DECL|struct|sb_mixer_levels
r_struct
id|sb_mixer_levels
(brace
DECL|member|master
r_struct
id|stereo_vol
id|master
suffix:semicolon
multiline_comment|/* Master volume */
DECL|member|voc
r_struct
id|stereo_vol
id|voc
suffix:semicolon
multiline_comment|/* DSP Voice volume */
DECL|member|fm
r_struct
id|stereo_vol
id|fm
suffix:semicolon
multiline_comment|/* FM volume */
DECL|member|line
r_struct
id|stereo_vol
id|line
suffix:semicolon
multiline_comment|/* Line-in volume */
DECL|member|cd
r_struct
id|stereo_vol
id|cd
suffix:semicolon
multiline_comment|/* CD audio */
DECL|member|mic
id|S_BYTE
id|mic
suffix:semicolon
multiline_comment|/* Microphone level */
)brace
suffix:semicolon
multiline_comment|/*&n; * Mixer parameters for MIXER_IOCTL_SET_PARAMS &amp; MIXER_IOCTL_READ_PARAMS&n; */
DECL|struct|sb_mixer_params
r_struct
id|sb_mixer_params
(brace
DECL|member|record_source
id|S_BYTE
id|record_source
suffix:semicolon
multiline_comment|/* Recording source (See SRC_xxx below) */
DECL|member|hifreq_filter
id|S_FLAG
id|hifreq_filter
suffix:semicolon
multiline_comment|/* Filter frequency (hi/low) */
DECL|member|filter_input
id|S_FLAG
id|filter_input
suffix:semicolon
multiline_comment|/* ANFI input filter */
DECL|member|filter_output
id|S_FLAG
id|filter_output
suffix:semicolon
multiline_comment|/* DNFI output filter */
DECL|member|dsp_stereo
id|S_FLAG
id|dsp_stereo
suffix:semicolon
multiline_comment|/* 1 if DSP is in Stereo mode */
)brace
suffix:semicolon
DECL|macro|SRC_MIC
mdefine_line|#define SRC_MIC         1&t;/* Select Microphone recording source */
DECL|macro|SRC_CD
mdefine_line|#define SRC_CD          3&t;/* Select CD recording source */
DECL|macro|SRC_LINE
mdefine_line|#define SRC_LINE        7&t;/* Use Line-in for recording source */
macro_line|#if !defined(KERNEL) &amp;&amp; !defined(INKERNEL)
multiline_comment|/*&n; *&t;Some convenience macros to simplify programming of the&n; *&t;/dev/sequencer interface&n; *&n; *&t;These macros define the API which should be used when possible.&n; */
r_void
id|seqbuf_dump
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* This function must be provided by programs */
multiline_comment|/* Sample seqbuf_dump() implementation:&n; *&n; *&t;SEQ_DEFINEBUF (2048);&t;-- Defines a buffer for 2048 bytes&n; *&n; *&t;int seqfd;&t;&t;-- The file descriptor for /dev/sequencer.&n; *&n; *&t;void&n; *&t;seqbuf_dump ()&n; *&t;{&n; *&t;  if (_seqbufptr)&n; *&t;    if (write (seqfd, _seqbuf, _seqbufptr) == -1)&n; *&t;      {&n; *&t;&t;perror (&quot;write /dev/sequencer&quot;);&n; *&t;&t;exit (-1);&n; *&t;      }&n; *&t;  _seqbufptr = 0;&n; *&t;}&n; */
DECL|macro|SEQ_DEFINEBUF
mdefine_line|#define SEQ_DEFINEBUF(len)&t;&t;unsigned char _seqbuf[len]; int _seqbuflen = len; int _seqbufptr = 0
DECL|macro|SEQ_DECLAREBUF
mdefine_line|#define SEQ_DECLAREBUF()&t;&t;extern unsigned char _seqbuf[]; extern int _seqbuflen;extern int _seqbufptr
DECL|macro|SEQ_PM_DEFINES
mdefine_line|#define SEQ_PM_DEFINES&t;&t;&t;struct patmgr_info _pm_info
DECL|macro|_SEQ_NEEDBUF
mdefine_line|#define _SEQ_NEEDBUF(len)&t;&t;if ((_seqbufptr+(len)) &gt; _seqbuflen) seqbuf_dump()
DECL|macro|_SEQ_ADVBUF
mdefine_line|#define _SEQ_ADVBUF(len)&t;&t;_seqbufptr += len
DECL|macro|SEQ_DUMPBUF
mdefine_line|#define SEQ_DUMPBUF&t;&t;&t;seqbuf_dump
DECL|macro|PM_LOAD_PATCH
mdefine_line|#define PM_LOAD_PATCH(dev, bank, pgm)&t;(SEQ_DUMPBUF(), _pm_info.command = _PM_LOAD_PATCH, &bslash;&n;&t;&t;&t;&t;&t;_pm_info.device=dev, _pm_info.data.data8[0]=pgm, &bslash;&n;&t;&t;&t;&t;&t;_pm_info.parm1 = bank, _pm_info.parm2 = 1, &bslash;&n;&t;&t;&t;&t;&t;ioctl(seqfd, SNDCTL_PMGR_ACCESS, &amp;_pm_info))
DECL|macro|PM_LOAD_PATCHES
mdefine_line|#define PM_LOAD_PATCHES(dev, bank, pgm) (SEQ_DUMPBUF(), _pm_info.command = _PM_LOAD_PATCH, &bslash;&n;&t;&t;&t;&t;&t;_pm_info.device=dev, memcpy(_pm_info.data.data8, pgm, 128), &bslash;&n;&t;&t;&t;&t;&t;_pm_info.parm1 = bank, _pm_info.parm2 = 128, &bslash;&n;&t;&t;&t;&t;&t;ioctl(seqfd, SNDCTL_PMGR_ACCESS, &amp;_pm_info))
DECL|macro|SEQ_VOLUME_MODE
mdefine_line|#define SEQ_VOLUME_MODE(dev, mode)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_VOLMODE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (mode);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_START_NOTE
mdefine_line|#define SEQ_START_NOTE(dev, voice, note, vol)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_NOTEON;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (note);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = (vol);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_STOP_NOTE
mdefine_line|#define SEQ_STOP_NOTE(dev, voice, note, vol)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_NOTEOFF;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (note);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = (vol);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_CHN_PRESSURE
mdefine_line|#define SEQ_CHN_PRESSURE(dev, voice, pressure)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_AFTERTOUCH;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (pressure);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_PANNING
mdefine_line|#define SEQ_PANNING(dev, voice, pos)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_BALANCE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;(char)_seqbuf[_seqbufptr+4] = (pos);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_CONTROL
mdefine_line|#define SEQ_CONTROL(dev, voice, controller, value)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_CONTROLLER;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (controller);&bslash;&n;&t;&t;&t;&t;&t;*(short *)&amp;_seqbuf[_seqbufptr+5] = (value);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_PITCHBEND
mdefine_line|#define SEQ_PITCHBEND(dev, voice, value) SEQ_CONTROL(dev, voice, CTRL_PITCH_BENDER, value)
DECL|macro|SEQ_BENDER_RANGE
mdefine_line|#define SEQ_BENDER_RANGE(dev, voice, value) SEQ_CONTROL(dev, voice, CTRL_PITCH_BENDER_RANGE, value)
DECL|macro|SEQ_EXPRESSION
mdefine_line|#define SEQ_EXPRESSION(dev, voice, value) SEQ_CONTROL(dev, voice, CTRL_EXPRESSION, value)
DECL|macro|SEQ_MAIN_VOLUME
mdefine_line|#define SEQ_MAIN_VOLUME(dev, voice, value) SEQ_CONTROL(dev, voice, CTRL_MAIN_VOLUME, value)
DECL|macro|SEQ_START_TIMER
mdefine_line|#define SEQ_START_TIMER()&t;&t;{_SEQ_NEEDBUF(4);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_SYNCTIMER;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(4);}
DECL|macro|SEQ_SET_PATCH
mdefine_line|#define SEQ_SET_PATCH(dev, voice, patch)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_PGMCHANGE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (patch);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_WAIT_TIME
mdefine_line|#define SEQ_WAIT_TIME(ticks)&t;&t;{_SEQ_NEEDBUF(4);&bslash;&n;&t;&t;&t;&t; &t;*(unsigned long *)&amp;_seqbuf[_seqbufptr] = SEQ_WAIT | ((ticks) &lt;&lt; 8);&bslash;&n;&t;&t;&t;&t; &t;_SEQ_ADVBUF(4);}
DECL|macro|SEQ_ECHO_BACK
mdefine_line|#define SEQ_ECHO_BACK(key)&t;&t;{_SEQ_NEEDBUF(4);&bslash;&n;&t;&t;&t;&t; &t;*(unsigned long *)&amp;_seqbuf[_seqbufptr] = SEQ_ECHO | ((key) &lt;&lt; 8);&bslash;&n;&t;&t;&t;&t; &t;_SEQ_ADVBUF(4);}
DECL|macro|SEQ_MIDIOUT
mdefine_line|#define SEQ_MIDIOUT(device, byte)&t;{_SEQ_NEEDBUF(4);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_MIDIPUTC;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (byte);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (device);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(4);}
DECL|macro|SEQ_WRPATCH
mdefine_line|#define SEQ_WRPATCH(patchx, len)&t;{if (_seqbufptr) seqbuf_dump();&bslash;&n;&t;&t;&t;&t;&t;if (write(seqfd, (char*)(patchx), len)==-1) &bslash;&n;&t;&t;&t;&t;&t;   perror(&quot;Write patch: /dev/sequencer&quot;);}
macro_line|#endif
r_int
id|soundcard_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
eof
