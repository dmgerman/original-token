multiline_comment|/*********************************************************************&n; *&n; * msnd_classic.h&n; *&n; * Turtle Beach MultiSound Sound Card Driver for Linux&n; *&n; * Some parts of this header file were derived from the Turtle Beach&n; * MultiSound Driver Development Kit.&n; *&n; * Copyright (C) 1998 Andrew Veliath&n; * Copyright (C) 1993 Turtle Beach Systems, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; * &n; * $Id: msnd_classic.h,v 1.4 1998/07/14 22:59:25 andrewtv Exp $&n; *&n; ********************************************************************/
macro_line|#ifndef __MSND_CLASSIC_H
DECL|macro|__MSND_CLASSIC_H
mdefine_line|#define __MSND_CLASSIC_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DSP_NUMIO
mdefine_line|#define DSP_NUMIO&t;&t;0x10
DECL|macro|HP_MEMM
mdefine_line|#define&t;HP_MEMM&t;&t;&t;0x08
DECL|macro|HP_BITM
mdefine_line|#define&t;HP_BITM&t;&t;&t;0x0E
DECL|macro|HP_WAIT
mdefine_line|#define&t;HP_WAIT&t;&t;&t;0x0D
DECL|macro|HP_DSPR
mdefine_line|#define&t;HP_DSPR&t;&t;&t;0x0A
DECL|macro|HP_PROR
mdefine_line|#define&t;HP_PROR&t;&t;&t;0x0B
DECL|macro|HP_BLKS
mdefine_line|#define&t;HP_BLKS&t;&t;&t;0x0C
DECL|macro|HPPRORESET_OFF
mdefine_line|#define&t;HPPRORESET_OFF&t;&t;0
DECL|macro|HPPRORESET_ON
mdefine_line|#define HPPRORESET_ON&t;&t;1
DECL|macro|HPDSPRESET_OFF
mdefine_line|#define HPDSPRESET_OFF&t;&t;0
DECL|macro|HPDSPRESET_ON
mdefine_line|#define HPDSPRESET_ON&t;&t;1
DECL|macro|HPBLKSEL_0
mdefine_line|#define HPBLKSEL_0&t;&t;0
DECL|macro|HPBLKSEL_1
mdefine_line|#define HPBLKSEL_1&t;&t;1
DECL|macro|HPWAITSTATE_0
mdefine_line|#define HPWAITSTATE_0&t;&t;0
DECL|macro|HPWAITSTATE_1
mdefine_line|#define HPWAITSTATE_1&t;&t;1
DECL|macro|HPBITMODE_16
mdefine_line|#define HPBITMODE_16&t;&t;0
DECL|macro|HPBITMODE_8
mdefine_line|#define HPBITMODE_8&t;&t;1
DECL|macro|HIDSP_INT_PLAY_UNDER
mdefine_line|#define&t;HIDSP_INT_PLAY_UNDER&t;0x00
DECL|macro|HIDSP_INT_RECORD_OVER
mdefine_line|#define&t;HIDSP_INT_RECORD_OVER&t;0x01
DECL|macro|HIDSP_INPUT_CLIPPING
mdefine_line|#define&t;HIDSP_INPUT_CLIPPING&t;0x02
DECL|macro|HIDSP_MIDI_IN_OVER
mdefine_line|#define&t;HIDSP_MIDI_IN_OVER&t;0x10
DECL|macro|HIDSP_MIDI_OVERRUN_ERR
mdefine_line|#define&t;HIDSP_MIDI_OVERRUN_ERR  0x13
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
DECL|macro|TIME_PRO_RESET_DONE
mdefine_line|#define TIME_PRO_RESET_DONE&t;0x028A
DECL|macro|TIME_PRO_SYSEX
mdefine_line|#define TIME_PRO_SYSEX&t;&t;0x0040
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
mdefine_line|#define MIDQ_BUFF_SIZE&t;&t;0x200
DECL|macro|DSPQ_BUFF_SIZE
mdefine_line|#define DSPQ_BUFF_SIZE&t;&t;0x40
DECL|macro|DAPQ_DATA_BUFF
mdefine_line|#define DAPQ_DATA_BUFF&t;&t;0x6C00
DECL|macro|DARQ_DATA_BUFF
mdefine_line|#define DARQ_DATA_BUFF&t;&t;0x6C30
DECL|macro|MODQ_DATA_BUFF
mdefine_line|#define MODQ_DATA_BUFF&t;&t;0x6C60
DECL|macro|MIDQ_DATA_BUFF
mdefine_line|#define MIDQ_DATA_BUFF&t;&t;0x7060
DECL|macro|DSPQ_DATA_BUFF
mdefine_line|#define DSPQ_DATA_BUFF&t;&t;0x7260
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
DECL|macro|MOP_PROTEUS
mdefine_line|#define MOP_PROTEUS&t;&t;0x10
DECL|macro|MOP_EXTOUT
mdefine_line|#define MOP_EXTOUT&t;&t;0x32
DECL|macro|MOP_EXTTHRU
mdefine_line|#define MOP_EXTTHRU&t;&t;0x02
DECL|macro|MOP_OUTMASK
mdefine_line|#define MOP_OUTMASK&t;&t;0x01
DECL|macro|MIP_EXTIN
mdefine_line|#define MIP_EXTIN&t;&t;0x01
DECL|macro|MIP_PROTEUS
mdefine_line|#define MIP_PROTEUS&t;&t;0x00
DECL|macro|MIP_INMASK
mdefine_line|#define MIP_INMASK&t;&t;0x32
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
DECL|member|wUser_3
id|WORD
id|wUser_3
suffix:semicolon
DECL|member|wUser_4
id|WORD
id|wUser_4
suffix:semicolon
DECL|member|dwUser_5
id|DWORD
id|dwUser_5
suffix:semicolon
DECL|member|dwUser_6
id|DWORD
id|dwUser_6
suffix:semicolon
DECL|member|wUser_7
id|WORD
id|wUser_7
suffix:semicolon
DECL|member|wReserved_A
id|WORD
id|wReserved_A
suffix:semicolon
DECL|member|wReserved_B
id|WORD
id|wReserved_B
suffix:semicolon
DECL|member|wReserved_C
id|WORD
id|wReserved_C
suffix:semicolon
DECL|member|wReserved_D
id|WORD
id|wReserved_D
suffix:semicolon
DECL|member|wReserved_E
id|WORD
id|wReserved_E
suffix:semicolon
DECL|member|wReserved_F
id|WORD
id|wReserved_F
suffix:semicolon
DECL|member|wReserved_G
id|WORD
id|wReserved_G
suffix:semicolon
DECL|member|wReserved_H
id|WORD
id|wReserved_H
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
DECL|member|wExtDSPbits
id|WORD
id|wExtDSPbits
suffix:semicolon
DECL|member|bExtHostbits
id|BYTE
id|bExtHostbits
suffix:semicolon
DECL|member|bBoardLevel
id|BYTE
id|bBoardLevel
suffix:semicolon
DECL|member|bInPotPosRight
id|BYTE
id|bInPotPosRight
suffix:semicolon
DECL|member|bInPotPosLeft
id|BYTE
id|bInPotPosLeft
suffix:semicolon
DECL|member|bAuxPotPosRight
id|BYTE
id|bAuxPotPosRight
suffix:semicolon
DECL|member|bAuxPotPosLeft
id|BYTE
id|bAuxPotPosLeft
suffix:semicolon
DECL|member|wCurrMastVolLeft
id|WORD
id|wCurrMastVolLeft
suffix:semicolon
DECL|member|wCurrMastVolRight
id|WORD
id|wCurrMastVolRight
suffix:semicolon
DECL|member|bUser_12
id|BYTE
id|bUser_12
suffix:semicolon
DECL|member|bUser_13
id|BYTE
id|bUser_13
suffix:semicolon
DECL|member|wUser_14
id|WORD
id|wUser_14
suffix:semicolon
DECL|member|wUser_15
id|WORD
id|wUser_15
suffix:semicolon
DECL|member|wCalFreqAtoD
id|WORD
id|wCalFreqAtoD
suffix:semicolon
DECL|member|wUser_16
id|WORD
id|wUser_16
suffix:semicolon
DECL|member|wUser_17
id|WORD
id|wUser_17
suffix:semicolon
DECL|variable|GCC_PACKED
)brace
id|GCC_PACKED
suffix:semicolon
macro_line|#ifdef HAVE_DSPCODEH
macro_line|#  include &quot;msndperm.c&quot;
macro_line|#  include &quot;msndinit.c&quot;
DECL|macro|PERMCODE
macro_line|#  define PERMCODE&t;&t;msndperm
DECL|macro|INITCODE
macro_line|#  define INITCODE&t;&t;msndinit
DECL|macro|PERMCODESIZE
macro_line|#  define PERMCODESIZE&t;&t;sizeof(msndperm)
DECL|macro|INITCODESIZE
macro_line|#  define INITCODESIZE&t;&t;sizeof(msndinit)
macro_line|#else
macro_line|#  ifndef CONFIG_MSNDCLAS_INIT_FILE
DECL|macro|CONFIG_MSNDCLAS_INIT_FILE
macro_line|#    define CONFIG_MSNDCLAS_INIT_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/msndinit.bin&quot;
macro_line|#  endif
macro_line|#  ifndef CONFIG_MSNDCLAS_PERM_FILE
DECL|macro|CONFIG_MSNDCLAS_PERM_FILE
macro_line|#    define CONFIG_MSNDCLAS_PERM_FILE&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&quot;/etc/sound/msndperm.bin&quot;
macro_line|#  endif
DECL|macro|PERMCODEFILE
macro_line|#  define PERMCODEFILE&t;&t;CONFIG_MSNDCLAS_PERM_FILE
DECL|macro|INITCODEFILE
macro_line|#  define INITCODEFILE&t;&t;CONFIG_MSNDCLAS_INIT_FILE
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
mdefine_line|#define LONGNAME&t;&t;&quot;MultiSound (Classic/Monterey/Tahiti)&quot;
macro_line|#endif /* __MSND_CLASSIC_H */
eof
