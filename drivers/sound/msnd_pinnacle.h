multiline_comment|/*********************************************************************&n; *&n; * msnd_pinnacle.h&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Some parts of this header file were derived from the Turtle Beach&n; * MultiSound Driver Development Kit.&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; * Copyright (C) 1993 Turtle Beach Systems, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Id: msnd_pinnacle.h,v 1.5 1998/07/18 00:12:16 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#ifndef __MSND_PINNACLE_H
DECL|macro|__MSND_PINNACLE_H
mdefine_line|#define __MSND_PINNACLE_H
DECL|macro|DSP_NUMIO
mdefine_line|#define DSP_NUMIO&t;&t;0x08
DECL|macro|HP_DSPR
mdefine_line|#define&t;HP_DSPR&t;&t;&t;0x04
DECL|macro|HP_BLKS
mdefine_line|#define&t;HP_BLKS&t;&t;&t;0x04
DECL|macro|HPDSPRESET_OFF
mdefine_line|#define HPDSPRESET_OFF&t;&t;2
DECL|macro|HPDSPRESET_ON
mdefine_line|#define HPDSPRESET_ON&t;&t;0
DECL|macro|HPBLKSEL_0
mdefine_line|#define HPBLKSEL_0&t;&t;2
DECL|macro|HPBLKSEL_1
mdefine_line|#define HPBLKSEL_1&t;&t;3
DECL|macro|HIMT_DAT_OFF
mdefine_line|#define&t;HIMT_DAT_OFF&t;&t;0x03
DECL|macro|HIDSP_PLAY_UNDER
mdefine_line|#define&t;HIDSP_PLAY_UNDER&t;0x00
DECL|macro|HIDSP_INT_PLAY_UNDER
mdefine_line|#define&t;HIDSP_INT_PLAY_UNDER&t;0x01
DECL|macro|HIDSP_SSI_TX_UNDER
mdefine_line|#define&t;HIDSP_SSI_TX_UNDER  &t;0x02
DECL|macro|HIDSP_RECQ_OVERFLOW
mdefine_line|#define HIDSP_RECQ_OVERFLOW&t;0x08
DECL|macro|HIDSP_INT_RECORD_OVER
mdefine_line|#define HIDSP_INT_RECORD_OVER&t;0x09
DECL|macro|HIDSP_SSI_RX_OVERFLOW
mdefine_line|#define HIDSP_SSI_RX_OVERFLOW&t;0x0a
DECL|macro|HIDSP_MIDI_IN_OVER
mdefine_line|#define&t;HIDSP_MIDI_IN_OVER&t;0x10
DECL|macro|HIDSP_MIDI_FRAME_ERR
mdefine_line|#define&t;HIDSP_MIDI_FRAME_ERR&t;0x11
DECL|macro|HIDSP_MIDI_PARITY_ERR
mdefine_line|#define&t;HIDSP_MIDI_PARITY_ERR&t;0x12
DECL|macro|HIDSP_MIDI_OVERRUN_ERR
mdefine_line|#define&t;HIDSP_MIDI_OVERRUN_ERR&t;0x13
DECL|macro|HIDSP_INPUT_CLIPPING
mdefine_line|#define HIDSP_INPUT_CLIPPING&t;0x20
DECL|macro|HIDSP_MIX_CLIPPING
mdefine_line|#define&t;HIDSP_MIX_CLIPPING&t;0x30
DECL|macro|HIDSP_DAT_IN_OFF
mdefine_line|#define HIDSP_DAT_IN_OFF&t;0x21
DECL|macro|HDEXAR_SET_ANA_IN
mdefine_line|#define&t;HDEXAR_SET_ANA_IN&t;0
DECL|macro|HDEXAR_CLEAR_PEAKS
mdefine_line|#define&t;HDEXAR_CLEAR_PEAKS&t;1
DECL|macro|HDEXAR_IN_SET_POTS
mdefine_line|#define&t;HDEXAR_IN_SET_POTS&t;2
DECL|macro|HDEXAR_AUX_SET_POTS
mdefine_line|#define&t;HDEXAR_AUX_SET_POTS&t;3
DECL|macro|HDEXAR_CAL_A_TO_D
mdefine_line|#define&t;HDEXAR_CAL_A_TO_D&t;4
DECL|macro|HDEXAR_RD_EXT_DSP_BITS
mdefine_line|#define&t;HDEXAR_RD_EXT_DSP_BITS&t;5
DECL|macro|HDEXAR_SET_SYNTH_IN
mdefine_line|#define&t;HDEXAR_SET_SYNTH_IN     4
DECL|macro|HDEXAR_READ_DAT_IN
mdefine_line|#define&t;HDEXAR_READ_DAT_IN      5
DECL|macro|HDEXAR_MIC_SET_POTS
mdefine_line|#define&t;HDEXAR_MIC_SET_POTS     6
DECL|macro|HDEXAR_SET_DAT_IN
mdefine_line|#define&t;HDEXAR_SET_DAT_IN       7
DECL|macro|HDEXAR_SET_SYNTH_48
mdefine_line|#define HDEXAR_SET_SYNTH_48     8
DECL|macro|HDEXAR_SET_SYNTH_44
mdefine_line|#define HDEXAR_SET_SYNTH_44     9
DECL|macro|TIME_PRO_RESET_DONE
mdefine_line|#define TIME_PRO_RESET_DONE&t;0x028A
DECL|macro|TIME_PRO_SYSEX
mdefine_line|#define TIME_PRO_SYSEX&t;&t;0x001E
DECL|macro|TIME_PRO_RESET
mdefine_line|#define TIME_PRO_RESET&t;&t;0x0032
DECL|macro|AGND
mdefine_line|#define AGND&t;&t;&t;0x01
DECL|macro|SIGNAL
mdefine_line|#define SIGNAL&t;&t;&t;0x02
DECL|macro|EXT_DSP_BIT_DCAL
mdefine_line|#define EXT_DSP_BIT_DCAL&t;0x0001
DECL|macro|EXT_DSP_BIT_MIDI_CON
mdefine_line|#define EXT_DSP_BIT_MIDI_CON&t;0x0002
DECL|macro|BUFFSIZE
mdefine_line|#define BUFFSIZE&t;&t;0x8000
DECL|macro|HOSTQ_SIZE
mdefine_line|#define HOSTQ_SIZE&t;&t;0x40
DECL|macro|SRAM_CNTL_START
mdefine_line|#define SRAM_CNTL_START&t;&t;0x7F00
DECL|macro|SMA_STRUCT_START
mdefine_line|#define SMA_STRUCT_START&t;0x7F40
DECL|macro|DAP_BUFF_SIZE
mdefine_line|#define DAP_BUFF_SIZE&t;&t;0x2400
DECL|macro|DAR_BUFF_SIZE
mdefine_line|#define DAR_BUFF_SIZE&t;&t;0x2000
DECL|macro|DAPQ_STRUCT_SIZE
mdefine_line|#define DAPQ_STRUCT_SIZE&t;0x10
DECL|macro|DARQ_STRUCT_SIZE
mdefine_line|#define DARQ_STRUCT_SIZE&t;0x10
DECL|macro|DAPQ_BUFF_SIZE
mdefine_line|#define DAPQ_BUFF_SIZE&t;&t;(3 * 0x10)
DECL|macro|DARQ_BUFF_SIZE
mdefine_line|#define DARQ_BUFF_SIZE&t;&t;(3 * 0x10)
DECL|macro|MODQ_BUFF_SIZE
mdefine_line|#define MODQ_BUFF_SIZE&t;&t;0x400
DECL|macro|MIDQ_BUFF_SIZE
mdefine_line|#define MIDQ_BUFF_SIZE&t;&t;0x800
DECL|macro|DSPQ_BUFF_SIZE
mdefine_line|#define DSPQ_BUFF_SIZE&t;&t;0x5A0
DECL|macro|DAPQ_DATA_BUFF
mdefine_line|#define DAPQ_DATA_BUFF&t;&t;0x6C00
DECL|macro|DARQ_DATA_BUFF
mdefine_line|#define DARQ_DATA_BUFF&t;&t;0x6C30
DECL|macro|MODQ_DATA_BUFF
mdefine_line|#define MODQ_DATA_BUFF&t;&t;0x6C60
DECL|macro|MIDQ_DATA_BUFF
mdefine_line|#define MIDQ_DATA_BUFF&t;&t;0x7060
DECL|macro|DSPQ_DATA_BUFF
mdefine_line|#define DSPQ_DATA_BUFF&t;&t;0x7860
DECL|macro|DAPQ_OFFSET
mdefine_line|#define DAPQ_OFFSET&t;&t;SRAM_CNTL_START
DECL|macro|DARQ_OFFSET
mdefine_line|#define DARQ_OFFSET&t;&t;(SRAM_CNTL_START + 0x08)
DECL|macro|MODQ_OFFSET
mdefine_line|#define MODQ_OFFSET&t;&t;(SRAM_CNTL_START + 0x10)
DECL|macro|MIDQ_OFFSET
mdefine_line|#define MIDQ_OFFSET&t;&t;(SRAM_CNTL_START + 0x18)
DECL|macro|DSPQ_OFFSET
mdefine_line|#define DSPQ_OFFSET&t;&t;(SRAM_CNTL_START + 0x20)
DECL|macro|WAVEHDR_MOP
mdefine_line|#define WAVEHDR_MOP&t;&t;0
DECL|macro|EXTOUT_MOP
mdefine_line|#define EXTOUT_MOP&t;&t;1
DECL|macro|HWINIT_MOP
mdefine_line|#define HWINIT_MOP&t;&t;0xFE
DECL|macro|NO_MOP
mdefine_line|#define NO_MOP&t;&t;&t;0xFF
DECL|macro|MAX_MOP
mdefine_line|#define MAX_MOP&t;&t;&t;1
DECL|macro|EXTIN_MIP
mdefine_line|#define EXTIN_MIP&t;&t;0
DECL|macro|WAVEHDR_MIP
mdefine_line|#define WAVEHDR_MIP&t;&t;1
DECL|macro|HWINIT_MIP
mdefine_line|#define HWINIT_MIP&t;&t;0xFE
DECL|macro|MAX_MIP
mdefine_line|#define MAX_MIP&t;&t;&t;1
DECL|struct|SMA0_CommonData
r_struct
id|SMA0_CommonData
(brace
DECL|member|wCurrPlayBytes
id|WORD
id|wCurrPlayBytes
suffix:semicolon
DECL|member|wCurrRecordBytes
id|WORD
id|wCurrRecordBytes
suffix:semicolon
DECL|member|wCurrPlayVolLeft
id|WORD
id|wCurrPlayVolLeft
suffix:semicolon
DECL|member|wCurrPlayVolRight
id|WORD
id|wCurrPlayVolRight
suffix:semicolon
DECL|member|wCurrInVolLeft
id|WORD
id|wCurrInVolLeft
suffix:semicolon
DECL|member|wCurrInVolRight
id|WORD
id|wCurrInVolRight
suffix:semicolon
DECL|member|wCurrMHdrVolLeft
id|WORD
id|wCurrMHdrVolLeft
suffix:semicolon
DECL|member|wCurrMHdrVolRight
id|WORD
id|wCurrMHdrVolRight
suffix:semicolon
DECL|member|dwCurrPlayPitch
id|DWORD
id|dwCurrPlayPitch
suffix:semicolon
DECL|member|dwCurrPlayRate
id|DWORD
id|dwCurrPlayRate
suffix:semicolon
DECL|member|wCurrMIDIIOPatch
id|WORD
id|wCurrMIDIIOPatch
suffix:semicolon
DECL|member|wCurrPlayFormat
id|WORD
id|wCurrPlayFormat
suffix:semicolon
DECL|member|wCurrPlaySampleSize
id|WORD
id|wCurrPlaySampleSize
suffix:semicolon
DECL|member|wCurrPlayChannels
id|WORD
id|wCurrPlayChannels
suffix:semicolon
DECL|member|wCurrPlaySampleRate
id|WORD
id|wCurrPlaySampleRate
suffix:semicolon
DECL|member|wCurrRecordFormat
id|WORD
id|wCurrRecordFormat
suffix:semicolon
DECL|member|wCurrRecordSampleSize
id|WORD
id|wCurrRecordSampleSize
suffix:semicolon
DECL|member|wCurrRecordChannels
id|WORD
id|wCurrRecordChannels
suffix:semicolon
DECL|member|wCurrRecordSampleRate
id|WORD
id|wCurrRecordSampleRate
suffix:semicolon
DECL|member|wCurrDSPStatusFlags
id|WORD
id|wCurrDSPStatusFlags
suffix:semicolon
DECL|member|wCurrHostStatusFlags
id|WORD
id|wCurrHostStatusFlags
suffix:semicolon
DECL|member|wCurrInputTagBits
id|WORD
id|wCurrInputTagBits
suffix:semicolon
DECL|member|wCurrLeftPeak
id|WORD
id|wCurrLeftPeak
suffix:semicolon
DECL|member|wCurrRightPeak
id|WORD
id|wCurrRightPeak
suffix:semicolon
DECL|member|bMicPotPosLeft
id|BYTE
id|bMicPotPosLeft
suffix:semicolon
DECL|member|bMicPotPosRight
id|BYTE
id|bMicPotPosRight
suffix:semicolon
DECL|member|bMicPotMaxLeft
id|BYTE
id|bMicPotMaxLeft
suffix:semicolon
DECL|member|bMicPotMaxRight
id|BYTE
id|bMicPotMaxRight
suffix:semicolon
DECL|member|bInPotPosLeft
id|BYTE
id|bInPotPosLeft
suffix:semicolon
DECL|member|bInPotPosRight
id|BYTE
id|bInPotPosRight
suffix:semicolon
DECL|member|bAuxPotPosLeft
id|BYTE
id|bAuxPotPosLeft
suffix:semicolon
DECL|member|bAuxPotPosRight
id|BYTE
id|bAuxPotPosRight
suffix:semicolon
DECL|member|bInPotMaxLeft
id|BYTE
id|bInPotMaxLeft
suffix:semicolon
DECL|member|bInPotMaxRight
id|BYTE
id|bInPotMaxRight
suffix:semicolon
DECL|member|bAuxPotMaxLeft
id|BYTE
id|bAuxPotMaxLeft
suffix:semicolon
DECL|member|bAuxPotMaxRight
id|BYTE
id|bAuxPotMaxRight
suffix:semicolon
DECL|member|bInPotMaxMethod
id|BYTE
id|bInPotMaxMethod
suffix:semicolon
DECL|member|bAuxPotMaxMethod
id|BYTE
id|bAuxPotMaxMethod
suffix:semicolon
DECL|member|wCurrMastVolLeft
id|WORD
id|wCurrMastVolLeft
suffix:semicolon
DECL|member|wCurrMastVolRight
id|WORD
id|wCurrMastVolRight
suffix:semicolon
DECL|member|wCalFreqAtoD
id|WORD
id|wCalFreqAtoD
suffix:semicolon
DECL|member|wCurrAuxVolLeft
id|WORD
id|wCurrAuxVolLeft
suffix:semicolon
DECL|member|wCurrAuxVolRight
id|WORD
id|wCurrAuxVolRight
suffix:semicolon
DECL|member|wCurrPlay1VolLeft
id|WORD
id|wCurrPlay1VolLeft
suffix:semicolon
DECL|member|wCurrPlay1VolRight
id|WORD
id|wCurrPlay1VolRight
suffix:semicolon
DECL|member|wCurrPlay2VolLeft
id|WORD
id|wCurrPlay2VolLeft
suffix:semicolon
DECL|member|wCurrPlay2VolRight
id|WORD
id|wCurrPlay2VolRight
suffix:semicolon
DECL|member|wCurrPlay3VolLeft
id|WORD
id|wCurrPlay3VolLeft
suffix:semicolon
DECL|member|wCurrPlay3VolRight
id|WORD
id|wCurrPlay3VolRight
suffix:semicolon
DECL|member|wCurrPlay4VolLeft
id|WORD
id|wCurrPlay4VolLeft
suffix:semicolon
DECL|member|wCurrPlay4VolRight
id|WORD
id|wCurrPlay4VolRight
suffix:semicolon
DECL|member|wCurrPlay1PeakLeft
id|WORD
id|wCurrPlay1PeakLeft
suffix:semicolon
DECL|member|wCurrPlay1PeakRight
id|WORD
id|wCurrPlay1PeakRight
suffix:semicolon
DECL|member|wCurrPlay2PeakLeft
id|WORD
id|wCurrPlay2PeakLeft
suffix:semicolon
DECL|member|wCurrPlay2PeakRight
id|WORD
id|wCurrPlay2PeakRight
suffix:semicolon
DECL|member|wCurrPlay3PeakLeft
id|WORD
id|wCurrPlay3PeakLeft
suffix:semicolon
DECL|member|wCurrPlay3PeakRight
id|WORD
id|wCurrPlay3PeakRight
suffix:semicolon
DECL|member|wCurrPlay4PeakLeft
id|WORD
id|wCurrPlay4PeakLeft
suffix:semicolon
DECL|member|wCurrPlay4PeakRight
id|WORD
id|wCurrPlay4PeakRight
suffix:semicolon
DECL|member|wCurrPlayPeakLeft
id|WORD
id|wCurrPlayPeakLeft
suffix:semicolon
DECL|member|wCurrPlayPeakRight
id|WORD
id|wCurrPlayPeakRight
suffix:semicolon
DECL|member|wCurrDATSR
id|WORD
id|wCurrDATSR
suffix:semicolon
DECL|member|wCurrDATRXCHNL
id|WORD
id|wCurrDATRXCHNL
suffix:semicolon
DECL|member|wCurrDATTXCHNL
id|WORD
id|wCurrDATTXCHNL
suffix:semicolon
DECL|member|wCurrDATRXRate
id|WORD
id|wCurrDATRXRate
suffix:semicolon
DECL|member|dwDSPPlayCount
id|DWORD
id|dwDSPPlayCount
suffix:semicolon
DECL|variable|GCC_PACKED
)brace
id|GCC_PACKED
suffix:semicolon
macro_line|#ifdef HAVE_DSPCODEH
macro_line|#  include &quot;pndsperm.c&quot;
macro_line|#  include &quot;pndspini.c&quot;
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;pndsperm
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;pndspini
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof(pndsperm)
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof(pndspini)
macro_line|#else
macro_line|#  ifndef CONFIG_MSNDPIN_INIT_FILE
DECL|macro|CONFIG_MSNDPIN_INIT_FILE
macro_line|#    define CONFIG_MSNDPIN_INIT_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/pndspini.bin&quot;
macro_line|#  endif
macro_line|#  ifndef CONFIG_MSNDPIN_PERM_FILE
DECL|macro|CONFIG_MSNDPIN_PERM_FILE
macro_line|#    define CONFIG_MSNDPIN_PERM_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/pndsperm.bin&quot;
macro_line|#  endif
DECL|macro|PERMCODEFILE
macro_line|#  define PERMCODEFILE&t;&t;CONFIG_MSNDPIN_PERM_FILE
DECL|macro|INITCODEFILE
macro_line|#  define INITCODEFILE&t;&t;CONFIG_MSNDPIN_INIT_FILE
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;dspini
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;permini
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof_dspini
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof_permini
macro_line|#endif
DECL|macro|LONGNAME
mdefine_line|#define LONGNAME&t;&t;&quot;MultiSound (Pinnacle/Fiji)&quot;
macro_line|#endif /* __MSND_PINNACLE_H */
eof
