multiline_comment|/* $Id: eicon_dsp.h,v 1.2 1999/03/29 11:19:42 armin Exp $&n; *&n; * ISDN lowlevel-module for Eicon.Diehl active cards.&n; *        DSP definitions&n; *&n; * Copyright 1999    by Armin Schindler (mac@melware.de)&n; * Copyright 1999    Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: eicon_dsp.h,v $&n; * Revision 1.2  1999/03/29 11:19:42  armin&n; * I/O stuff now in seperate file (eicon_io.c)&n; * Old ISA type cards (S,SX,SCOM,Quadro,S2M) implemented.&n; *&n; * Revision 1.1  1999/03/02 12:18:54  armin&n; * First checkin of DSP defines for audio features.&n; *&n; *&n; */
macro_line|#ifndef DSP_H
DECL|macro|DSP_H
mdefine_line|#define DSP_H
DECL|macro|DSP_UDATA_REQUEST_RECONFIGURE
mdefine_line|#define DSP_UDATA_REQUEST_RECONFIGURE           0
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; reconfigure delay (in 8kHz samples)&n;  &lt;word&gt; reconfigure code&n;  &lt;byte&gt; reconfigure hdlc preamble flags&n;*/
DECL|macro|DSP_RECONFIGURE_TX_FLAG
mdefine_line|#define DSP_RECONFIGURE_TX_FLAG             0x8000
DECL|macro|DSP_RECONFIGURE_SHORT_TRAIN_FLAG
mdefine_line|#define DSP_RECONFIGURE_SHORT_TRAIN_FLAG    0x4000
DECL|macro|DSP_RECONFIGURE_ECHO_PROTECT_FLAG
mdefine_line|#define DSP_RECONFIGURE_ECHO_PROTECT_FLAG   0x2000
DECL|macro|DSP_RECONFIGURE_HDLC_FLAG
mdefine_line|#define DSP_RECONFIGURE_HDLC_FLAG           0x1000
DECL|macro|DSP_RECONFIGURE_SYNC_FLAG
mdefine_line|#define DSP_RECONFIGURE_SYNC_FLAG           0x0800
DECL|macro|DSP_RECONFIGURE_PROTOCOL_MASK
mdefine_line|#define DSP_RECONFIGURE_PROTOCOL_MASK       0x00ff
DECL|macro|DSP_RECONFIGURE_IDLE
mdefine_line|#define DSP_RECONFIGURE_IDLE                0
DECL|macro|DSP_RECONFIGURE_V25
mdefine_line|#define DSP_RECONFIGURE_V25                 1
DECL|macro|DSP_RECONFIGURE_V21_CH2
mdefine_line|#define DSP_RECONFIGURE_V21_CH2             2
DECL|macro|DSP_RECONFIGURE_V27_2400
mdefine_line|#define DSP_RECONFIGURE_V27_2400            3
DECL|macro|DSP_RECONFIGURE_V27_4800
mdefine_line|#define DSP_RECONFIGURE_V27_4800            4
DECL|macro|DSP_RECONFIGURE_V29_7200
mdefine_line|#define DSP_RECONFIGURE_V29_7200            5
DECL|macro|DSP_RECONFIGURE_V29_9600
mdefine_line|#define DSP_RECONFIGURE_V29_9600            6
DECL|macro|DSP_RECONFIGURE_V33_12000
mdefine_line|#define DSP_RECONFIGURE_V33_12000           7
DECL|macro|DSP_RECONFIGURE_V33_14400
mdefine_line|#define DSP_RECONFIGURE_V33_14400           8
DECL|macro|DSP_RECONFIGURE_V17_7200
mdefine_line|#define DSP_RECONFIGURE_V17_7200            9
DECL|macro|DSP_RECONFIGURE_V17_9600
mdefine_line|#define DSP_RECONFIGURE_V17_9600            10
DECL|macro|DSP_RECONFIGURE_V17_12000
mdefine_line|#define DSP_RECONFIGURE_V17_12000           11
DECL|macro|DSP_RECONFIGURE_V17_14400
mdefine_line|#define DSP_RECONFIGURE_V17_14400           12
multiline_comment|/*&n;data indications if transparent framer&n;  &lt;byte&gt; data 0&n;  &lt;byte&gt; data 1&n;  ...&n;&n;data indications if HDLC framer&n;  &lt;byte&gt; data 0&n;  &lt;byte&gt; data 1&n;  ...&n;  &lt;byte&gt; CRC 0&n;  &lt;byte&gt; CRC 1&n;  &lt;byte&gt; preamble flags&n;*/
DECL|macro|DSP_UDATA_REQUEST_SWITCH_FRAMER
mdefine_line|#define DSP_UDATA_REQUEST_SWITCH_FRAMER         1
multiline_comment|/*&n;parameters:&n;  &lt;byte&gt; transmit framer type&n;  &lt;byte&gt; receive framer type&n;*/
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_HDLC
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_HDLC          0
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_TRANSPARENT
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_TRANSPARENT   1
DECL|macro|DSP_REQUEST_SWITCH_FRAMER_ASYNC
mdefine_line|#define DSP_REQUEST_SWITCH_FRAMER_ASYNC         2
DECL|macro|DSP_UDATA_REQUEST_CLEARDOWN
mdefine_line|#define DSP_UDATA_REQUEST_CLEARDOWN             2
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_REQUEST_TX_CONFIRMATION_ON
mdefine_line|#define DSP_UDATA_REQUEST_TX_CONFIRMATION_ON    3
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_REQUEST_TX_CONFIRMATION_OFF
mdefine_line|#define DSP_UDATA_REQUEST_TX_CONFIRMATION_OFF   4
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_SYNC
mdefine_line|#define DSP_UDATA_INDICATION_SYNC               0
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of sync (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_DCD_OFF
mdefine_line|#define DSP_UDATA_INDICATION_DCD_OFF            1
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of DCD off (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_DCD_ON
mdefine_line|#define DSP_UDATA_INDICATION_DCD_ON             2
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of DCD on (sampled from counter at 8kHz)&n;  &lt;byte&gt; connected norm&n;  &lt;word&gt; connected options&n;  &lt;dword&gt; connected speed (bit/s, max of tx and rx speed)&n;  &lt;word&gt; roundtrip delay (ms)&n;  &lt;dword&gt; connected speed tx (bit/s)&n;  &lt;dword&gt; connected speed rx (bit/s)&n;*/
DECL|macro|DSP_UDATA_INDICATION_CTS_OFF
mdefine_line|#define DSP_UDATA_INDICATION_CTS_OFF            3
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of CTS off (sampled from counter at 8kHz)&n;*/
DECL|macro|DSP_UDATA_INDICATION_CTS_ON
mdefine_line|#define DSP_UDATA_INDICATION_CTS_ON             4
multiline_comment|/*&n;returns:&n;  &lt;word&gt; time of CTS on (sampled from counter at 8kHz)&n;  &lt;byte&gt; connected norm&n;  &lt;word&gt; connected options&n;  &lt;dword&gt; connected speed (bit/s, max of tx and rx speed)&n;  &lt;word&gt; roundtrip delay (ms)&n;  &lt;dword&gt; connected speed tx (bit/s)&n;  &lt;dword&gt; connected speed rx (bit/s)&n;*/
DECL|struct|eicon_dsp_ind
r_typedef
r_struct
id|eicon_dsp_ind
(brace
DECL|member|time
id|__u16
id|time
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|norm
id|__u8
id|norm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|options
id|__u16
id|options
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|speed
id|__u32
id|speed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|delay
id|__u16
id|delay
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|txspeed
id|__u32
id|txspeed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|rxspeed
id|__u32
id|rxspeed
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_dsp_ind
)brace
id|eicon_dsp_ind
suffix:semicolon
DECL|macro|DSP_CONNECTED_NORM_UNSPECIFIED
mdefine_line|#define DSP_CONNECTED_NORM_UNSPECIFIED      0
DECL|macro|DSP_CONNECTED_NORM_V21
mdefine_line|#define DSP_CONNECTED_NORM_V21              1
DECL|macro|DSP_CONNECTED_NORM_V23
mdefine_line|#define DSP_CONNECTED_NORM_V23              2
DECL|macro|DSP_CONNECTED_NORM_V22
mdefine_line|#define DSP_CONNECTED_NORM_V22              3
DECL|macro|DSP_CONNECTED_NORM_V22_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V22_BIS          4
DECL|macro|DSP_CONNECTED_NORM_V32_BIS
mdefine_line|#define DSP_CONNECTED_NORM_V32_BIS          5
DECL|macro|DSP_CONNECTED_NORM_V34
mdefine_line|#define DSP_CONNECTED_NORM_V34              6
DECL|macro|DSP_CONNECTED_NORM_V8
mdefine_line|#define DSP_CONNECTED_NORM_V8               7
DECL|macro|DSP_CONNECTED_NORM_BELL_212A
mdefine_line|#define DSP_CONNECTED_NORM_BELL_212A        8
DECL|macro|DSP_CONNECTED_NORM_BELL_103
mdefine_line|#define DSP_CONNECTED_NORM_BELL_103         9
DECL|macro|DSP_CONNECTED_NORM_V29_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V29_LEASED_LINE  10
DECL|macro|DSP_CONNECTED_NORM_V33_LEASED_LINE
mdefine_line|#define DSP_CONNECTED_NORM_V33_LEASED_LINE  11
DECL|macro|DSP_CONNECTED_NORM_V90
mdefine_line|#define DSP_CONNECTED_NORM_V90              12
DECL|macro|DSP_CONNECTED_NORM_V21_CH2
mdefine_line|#define DSP_CONNECTED_NORM_V21_CH2          13
DECL|macro|DSP_CONNECTED_NORM_V27_TER
mdefine_line|#define DSP_CONNECTED_NORM_V27_TER          14
DECL|macro|DSP_CONNECTED_NORM_V29
mdefine_line|#define DSP_CONNECTED_NORM_V29              15
DECL|macro|DSP_CONNECTED_NORM_V33
mdefine_line|#define DSP_CONNECTED_NORM_V33              16
DECL|macro|DSP_CONNECTED_NORM_V17
mdefine_line|#define DSP_CONNECTED_NORM_V17              17
DECL|macro|DSP_CONNECTED_OPTION_TRELLIS
mdefine_line|#define DSP_CONNECTED_OPTION_TRELLIS             0x0001
DECL|macro|DSP_CONNECTED_OPTION_V42_TRANS
mdefine_line|#define DSP_CONNECTED_OPTION_V42_TRANS           0x0002
DECL|macro|DSP_CONNECTED_OPTION_V42_LAPM
mdefine_line|#define DSP_CONNECTED_OPTION_V42_LAPM            0x0004
DECL|macro|DSP_CONNECTED_OPTION_SHORT_TRAIN
mdefine_line|#define DSP_CONNECTED_OPTION_SHORT_TRAIN         0x0008
DECL|macro|DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT
mdefine_line|#define DSP_CONNECTED_OPTION_TALKER_ECHO_PROTECT 0x0010
DECL|macro|DSP_UDATA_INDICATION_DISCONNECT
mdefine_line|#define DSP_UDATA_INDICATION_DISCONNECT         5
multiline_comment|/*&n;returns:&n;  &lt;byte&gt; cause&n;*/
DECL|macro|DSP_DISCONNECT_CAUSE_NONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_NONE               0x00
DECL|macro|DSP_DISCONNECT_CAUSE_BUSY_TONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_BUSY_TONE          0x01
DECL|macro|DSP_DISCONNECT_CAUSE_CONGESTION_TONE
mdefine_line|#define DSP_DISCONNECT_CAUSE_CONGESTION_TONE    0x02
DECL|macro|DSP_DISCONNECT_CAUSE_INCOMPATIBILITY
mdefine_line|#define DSP_DISCONNECT_CAUSE_INCOMPATIBILITY    0x03
DECL|macro|DSP_DISCONNECT_CAUSE_CLEARDOWN
mdefine_line|#define DSP_DISCONNECT_CAUSE_CLEARDOWN          0x04
DECL|macro|DSP_DISCONNECT_CAUSE_TRAINING_TIMEOUT
mdefine_line|#define DSP_DISCONNECT_CAUSE_TRAINING_TIMEOUT   0x05
DECL|macro|DSP_UDATA_INDICATION_TX_CONFIRMATION
mdefine_line|#define DSP_UDATA_INDICATION_TX_CONFIRMATION    6
multiline_comment|/*&n;returns:&n;  &lt;word&gt; confirmation number&n;*/
DECL|macro|DSP_UDATA_REQUEST_SEND_DTMF_DIGITS
mdefine_line|#define DSP_UDATA_REQUEST_SEND_DTMF_DIGITS      16
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; tone duration (ms)&n;  &lt;word&gt; gap duration (ms)&n;  &lt;byte&gt; digit 0 tone code&n;  ...&n;  &lt;byte&gt; digit n tone code&n;*/
DECL|macro|DSP_SEND_DTMF_DIGITS_HEADER_LENGTH
mdefine_line|#define DSP_SEND_DTMF_DIGITS_HEADER_LENGTH      5
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_697_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_697_HZ    0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_770_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_770_HZ    0x01
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_852_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_852_HZ    0x02
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_941_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_941_HZ    0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_LOW_GROUP_MASK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_LOW_GROUP_MASK      0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1209_HZ  0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1336_HZ  0x04
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1477_HZ  0x08
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_1633_HZ  0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_HIGH_GROUP_MASK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_HIGH_GROUP_MASK     0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_0
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_0              0x07
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_1
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_1              0x00
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_2
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_2              0x04
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_3
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_3              0x08
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_4
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_4              0x01
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_5
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_5              0x05
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_6
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_6              0x09
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_7
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_7              0x02
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_8
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_8              0x06
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_9
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_9              0x0a
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_STAR
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_STAR           0x03
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_HASHMARK
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_HASHMARK       0x0b
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_A
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_A              0x0c
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_B
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_B              0x0d
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_C
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_C              0x0e
DECL|macro|DSP_DTMF_DIGIT_TONE_CODE_D
mdefine_line|#define DSP_DTMF_DIGIT_TONE_CODE_D              0x0f
DECL|macro|DSP_UDATA_INDICATION_DTMF_DIGITS_SENT
mdefine_line|#define DSP_UDATA_INDICATION_DTMF_DIGITS_SENT   16
multiline_comment|/*&n;returns:&n;  - none -&n;  One indication will be sent for every request.&n;*/
DECL|macro|DSP_UDATA_REQUEST_ENABLE_DTMF_RECEIVER
mdefine_line|#define DSP_UDATA_REQUEST_ENABLE_DTMF_RECEIVER  17
multiline_comment|/*&n;parameters:&n;  &lt;word&gt; tone duration (ms)&n;  &lt;word&gt; gap duration (ms)&n;*/
DECL|macro|DSP_UDATA_REQUEST_DISABLE_DTMF_RECEIVER
mdefine_line|#define DSP_UDATA_REQUEST_DISABLE_DTMF_RECEIVER 18
multiline_comment|/*&n;parameters:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_DTMF_DIGITS_RECEIVED
mdefine_line|#define DSP_UDATA_INDICATION_DTMF_DIGITS_RECEIVED 17
multiline_comment|/*&n;returns:&n;  &lt;byte&gt; digit 0 tone code&n;  ...&n;  &lt;byte&gt; digit n tone code&n;*/
DECL|macro|DSP_DTMF_DIGITS_RECEIVED_HEADER_LENGTH
mdefine_line|#define DSP_DTMF_DIGITS_RECEIVED_HEADER_LENGTH  1
DECL|macro|DSP_UDATA_INDICATION_MODEM_CALLING_TONE
mdefine_line|#define DSP_UDATA_INDICATION_MODEM_CALLING_TONE 18
multiline_comment|/*&n;returns:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_FAX_CALLING_TONE
mdefine_line|#define DSP_UDATA_INDICATION_FAX_CALLING_TONE   19
multiline_comment|/*&n;returns:&n;  - none -&n;*/
DECL|macro|DSP_UDATA_INDICATION_ANSWER_TONE
mdefine_line|#define DSP_UDATA_INDICATION_ANSWER_TONE        20
multiline_comment|/*&n;returns:&n;  - none -&n;*/
macro_line|#endif&t;/* DSP_H */
eof
