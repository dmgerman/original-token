multiline_comment|/*&n; *              telephony.h&n; *&n; *              Basic Linux Telephony Interface&n; *&n; *              (c) Copyright 1999 Quicknet Technologies, Inc.&n; *&n; *              This program is free software; you can redistribute it and/or&n; *              modify it under the terms of the GNU General Public License&n; *              as published by the Free Software Foundation; either version&n; *              2 of the License, or (at your option) any later version.&n; *&n; * Authors:       Ed Okerson, &lt;eokerson@quicknet.net&gt;&n; *                Greg Herlein, &lt;gherlein@quicknet.net&gt;&n; *&n; * Contributors:  Alan Cox, &lt;acox@redhat.com&gt;&n; *                David Erhart, &lt;derhart@quicknet.net&gt;&n; *&n; * Version:       0.1.0 - December 19, 1999&n; *&n; * Fixes:&n; */
macro_line|#ifndef TELEPHONY_H
DECL|macro|TELEPHONY_H
mdefine_line|#define TELEPHONY_H
multiline_comment|/* vendor identification numbers */
DECL|macro|PHONE_VENDOR_IXJ
mdefine_line|#define PHONE_VENDOR_IXJ          1
DECL|macro|PHONE_VENDOR_QUICKNET
mdefine_line|#define PHONE_VENDOR_QUICKNET     PHONE_IXJ
DECL|macro|PHONE_VENDOR_VOICETRONIX
mdefine_line|#define PHONE_VENDOR_VOICETRONIX  2
DECL|macro|PHONE_VENDOR_ACULAB
mdefine_line|#define PHONE_VENDOR_ACULAB       3
DECL|macro|PHONE_VENDOR_DIGI
mdefine_line|#define PHONE_VENDOR_DIGI         4
DECL|macro|PHONE_VENDOR_FRANKLIN
mdefine_line|#define PHONE_VENDOR_FRANKLIN     5
multiline_comment|/******************************************************************************&n; *  Vendor Summary Information Area&n; *&n; *  Quicknet Technologies, Inc. - makes low density analog telephony cards&n; *    with audio compression, POTS and PSTN interfaces (www.quicknet.net)&n; *&n; *  (other vendors following this API shuld add a short description of&n; *  the telephony products they support under Linux)&n; *&n; *****************************************************************************/
multiline_comment|/******************************************************************************&n;*&n;* The capabilities ioctls can inform you of the capabilities of each phone&n;* device installed in your system.  The PHONECTL_CAPABILITIES ioctl&n;* returns an integer value indicating the number of capabilities the   &n;* device has.  The PHONECTL_CAPABILITIES_LIST will fill an array of &n;* capability structs with all of it&squot;s capabilities.  The&n;* PHONECTL_CAPABILITIES_CHECK takes a single capability struct and returns&n;* a TRUE if the device has that capability, otherwise it returns false.&n;* &n;******************************************************************************/
r_typedef
r_enum
(brace
DECL|enumerator|vendor
id|vendor
op_assign
l_int|0
comma
DECL|enumerator|device
id|device
comma
DECL|enumerator|port
id|port
comma
DECL|enumerator|codec
id|codec
comma
DECL|enumerator|dsp
id|dsp
DECL|typedef|phone_cap
)brace
id|phone_cap
suffix:semicolon
DECL|struct|phone_capability
r_struct
id|phone_capability
(brace
DECL|member|desc
r_char
id|desc
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|captype
id|phone_cap
id|captype
suffix:semicolon
DECL|member|cap
r_int
id|cap
suffix:semicolon
DECL|member|handle
r_int
id|handle
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|pots
id|pots
op_assign
l_int|0
comma
DECL|enumerator|pstn
id|pstn
comma
DECL|enumerator|handset
id|handset
comma
DECL|enumerator|speaker
id|speaker
DECL|typedef|phone_ports
)brace
id|phone_ports
suffix:semicolon
DECL|macro|PHONE_CAPABILITIES
mdefine_line|#define PHONE_CAPABILITIES              _IO  (&squot;q&squot;, 0x80)
DECL|macro|PHONE_CAPABILITIES_LIST
mdefine_line|#define PHONE_CAPABILITIES_LIST         _IOR (&squot;q&squot;, 0x81, struct phone_capability *)
DECL|macro|PHONE_CAPABILITIES_CHECK
mdefine_line|#define PHONE_CAPABILITIES_CHECK        _IOW (&squot;q&squot;, 0x82, struct phone_capability *)
DECL|macro|PHONE_RING
mdefine_line|#define PHONE_RING&t;&t;&t;_IO  (&squot;q&squot;, 0x83)
DECL|macro|PHONE_HOOKSTATE
mdefine_line|#define PHONE_HOOKSTATE&t;&t;&t;_IO  (&squot;q&squot;, 0x84)
DECL|macro|PHONE_MAXRINGS
mdefine_line|#define PHONE_MAXRINGS&t;&t;&t;_IOW (&squot;q&squot;, 0x85, char)
DECL|macro|PHONE_RING_CADENCE
mdefine_line|#define PHONE_RING_CADENCE&t;&t;_IOW (&squot;q&squot;, 0x86, short)
DECL|macro|PHONE_RING_START
mdefine_line|#define PHONE_RING_START&t;&t;_IO  (&squot;q&squot;, 0x87)
DECL|macro|PHONE_RING_STOP
mdefine_line|#define PHONE_RING_STOP&t;&t;&t;_IO  (&squot;q&squot;, 0x88)
DECL|macro|USA_RING_CADENCE
mdefine_line|#define USA_RING_CADENCE&t; 0xC0C0
DECL|macro|PHONE_REC_CODEC
mdefine_line|#define PHONE_REC_CODEC&t;&t;&t;_IOW (&squot;q&squot;, 0x89, int)
DECL|macro|PHONE_REC_START
mdefine_line|#define PHONE_REC_START&t;&t;&t;_IO  (&squot;q&squot;, 0x8A)
DECL|macro|PHONE_REC_STOP
mdefine_line|#define PHONE_REC_STOP&t;&t;&t;_IO  (&squot;q&squot;, 0x8B)
DECL|macro|PHONE_REC_DEPTH
mdefine_line|#define PHONE_REC_DEPTH&t;&t;&t;_IOW (&squot;q&squot;, 0x8C, int)
DECL|macro|PHONE_FRAME
mdefine_line|#define PHONE_FRAME&t;&t;&t;_IOW (&squot;q&squot;, 0x8D, int)
DECL|macro|PHONE_REC_VOLUME
mdefine_line|#define PHONE_REC_VOLUME&t;&t;_IOW (&squot;q&squot;, 0x8E, int)
DECL|macro|PHONE_REC_LEVEL
mdefine_line|#define PHONE_REC_LEVEL&t;&t;&t;_IO  (&squot;q&squot;, 0x8F)
DECL|macro|PHONE_PLAY_CODEC
mdefine_line|#define PHONE_PLAY_CODEC&t;&t;_IOW (&squot;q&squot;, 0x90, int)
DECL|macro|PHONE_PLAY_START
mdefine_line|#define PHONE_PLAY_START&t;&t;_IO  (&squot;q&squot;, 0x91)
DECL|macro|PHONE_PLAY_STOP
mdefine_line|#define PHONE_PLAY_STOP&t;&t;&t;_IO  (&squot;q&squot;, 0x92)
DECL|macro|PHONE_PLAY_DEPTH
mdefine_line|#define PHONE_PLAY_DEPTH&t;&t;_IOW (&squot;q&squot;, 0x93, int)
DECL|macro|PHONE_PLAY_VOLUME
mdefine_line|#define PHONE_PLAY_VOLUME&t;&t;_IOW (&squot;q&squot;, 0x94, int)
DECL|macro|PHONE_PLAY_LEVEL
mdefine_line|#define PHONE_PLAY_LEVEL&t;&t;_IO  (&squot;q&squot;, 0x95)
DECL|macro|PHONE_DTMF_READY
mdefine_line|#define PHONE_DTMF_READY&t;&t;_IOR (&squot;q&squot;, 0x96, int)
DECL|macro|PHONE_GET_DTMF
mdefine_line|#define PHONE_GET_DTMF&t;&t;&t;_IOR (&squot;q&squot;, 0x97, int)
DECL|macro|PHONE_GET_DTMF_ASCII
mdefine_line|#define PHONE_GET_DTMF_ASCII&t;&t;_IOR (&squot;q&squot;, 0x98, int)
DECL|macro|PHONE_DTMF_OOB
mdefine_line|#define PHONE_DTMF_OOB&t;&t;&t;_IOW (&squot;q&squot;, 0x99, int)
DECL|macro|PHONE_EXCEPTION
mdefine_line|#define PHONE_EXCEPTION&t;&t;&t;_IOR (&squot;q&squot;, 0x9A, int)
DECL|macro|PHONE_PLAY_TONE
mdefine_line|#define PHONE_PLAY_TONE&t;&t;&t;_IOW (&squot;q&squot;, 0x9B, char)
DECL|macro|PHONE_SET_TONE_ON_TIME
mdefine_line|#define PHONE_SET_TONE_ON_TIME&t;&t;_IOW (&squot;q&squot;, 0x9C, int)
DECL|macro|PHONE_SET_TONE_OFF_TIME
mdefine_line|#define PHONE_SET_TONE_OFF_TIME&t;&t;_IOW (&squot;q&squot;, 0x9D, int)
DECL|macro|PHONE_GET_TONE_ON_TIME
mdefine_line|#define PHONE_GET_TONE_ON_TIME&t;&t;_IO  (&squot;q&squot;, 0x9E)
DECL|macro|PHONE_GET_TONE_OFF_TIME
mdefine_line|#define PHONE_GET_TONE_OFF_TIME&t;&t;_IO  (&squot;q&squot;, 0x9F)
DECL|macro|PHONE_GET_TONE_STATE
mdefine_line|#define PHONE_GET_TONE_STATE&t;&t;_IO  (&squot;q&squot;, 0xA0)
DECL|macro|PHONE_BUSY
mdefine_line|#define PHONE_BUSY&t;&t;&t;_IO  (&squot;q&squot;, 0xA1)
DECL|macro|PHONE_RINGBACK
mdefine_line|#define PHONE_RINGBACK&t;&t;&t;_IO  (&squot;q&squot;, 0xA2)
DECL|macro|PHONE_DIALTONE
mdefine_line|#define PHONE_DIALTONE&t;&t;&t;_IO  (&squot;q&squot;, 0xA3)
DECL|macro|PHONE_CPT_STOP
mdefine_line|#define PHONE_CPT_STOP&t;&t;&t;_IO  (&squot;q&squot;, 0xA4)
DECL|macro|PHONE_PSTN_SET_STATE
mdefine_line|#define PHONE_PSTN_SET_STATE&t;&t;_IOW (&squot;q&squot;, 0xA4, int)
DECL|macro|PHONE_PSTN_GET_STATE
mdefine_line|#define PHONE_PSTN_GET_STATE&t;&t;_IO  (&squot;q&squot;, 0xA5)
DECL|macro|PSTN_ON_HOOK
mdefine_line|#define PSTN_ON_HOOK&t;&t;0
DECL|macro|PSTN_RINGING
mdefine_line|#define PSTN_RINGING&t;&t;1
DECL|macro|PSTN_OFF_HOOK
mdefine_line|#define PSTN_OFF_HOOK&t;&t;2
DECL|macro|PSTN_PULSE_DIAL
mdefine_line|#define PSTN_PULSE_DIAL&t;&t;3
multiline_comment|/******************************************************************************&n;* &n;* The wink duration is tunable with this ioctl.  The default wink duration  &n;* is 320ms.  You do not need to use this ioctl if you do not require a&n;* different wink duration.&n;* &n;******************************************************************************/
DECL|macro|PHONE_WINK_DURATION
mdefine_line|#define PHONE_WINK_DURATION&t;&t;_IOW (&squot;q&squot;, 0xA6, int)
multiline_comment|/******************************************************************************&n;* &n;*  Codec Definitions&n;* &n;******************************************************************************/
r_typedef
r_enum
(brace
DECL|enumerator|G723_63
id|G723_63
op_assign
l_int|1
comma
DECL|enumerator|G723_53
id|G723_53
op_assign
l_int|2
comma
DECL|enumerator|TS85
id|TS85
op_assign
l_int|3
comma
DECL|enumerator|TS48
id|TS48
op_assign
l_int|4
comma
DECL|enumerator|TS41
id|TS41
op_assign
l_int|5
comma
DECL|enumerator|G728
id|G728
op_assign
l_int|6
comma
DECL|enumerator|G729
id|G729
op_assign
l_int|7
comma
DECL|enumerator|ULAW
id|ULAW
op_assign
l_int|8
comma
DECL|enumerator|ALAW
id|ALAW
op_assign
l_int|9
comma
DECL|enumerator|LINEAR16
id|LINEAR16
op_assign
l_int|10
comma
DECL|enumerator|LINEAR8
id|LINEAR8
op_assign
l_int|11
comma
DECL|enumerator|WSS
id|WSS
op_assign
l_int|12
DECL|typedef|phone_codec
)brace
id|phone_codec
suffix:semicolon
DECL|struct|phone_codec_data
r_struct
id|phone_codec_data
(brace
DECL|member|type
id|phone_codec
id|type
suffix:semicolon
DECL|member|buf_min
DECL|member|buf_opt
DECL|member|buf_max
r_int
r_int
id|buf_min
comma
id|buf_opt
comma
id|buf_max
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PHONE_QUERY_CODEC
mdefine_line|#define PHONE_QUERY_CODEC&t;&t;_IOWR (&squot;q&squot;, 0xA7, struct phone_codec_data *)
DECL|macro|PHONE_PSTN_LINETEST
mdefine_line|#define PHONE_PSTN_LINETEST&t;&t;_IO (&squot;q&squot;, 0xA8)
multiline_comment|/******************************************************************************&n;*&n;* The exception structure allows us to multiplex multiple events onto the&n;* select() exception set.  If any of these flags are set select() will&n;* return with a positive indication on the exception set.  The dtmf_ready&n;* bit indicates if there is data waiting in the DTMF buffer.  The&n;* hookstate bit is set if there is a change in hookstate status, it does not&n;* indicate the current state of the hookswitch.  The pstn_ring bit&n;* indicates that the DAA on a LineJACK card has detected ring voltage on&n;* the PSTN port.  The caller_id bit indicates that caller_id data has been&n;* recieved and is available.  The pstn_wink bit indicates that the DAA on&n;* the LineJACK has recieved a wink from the telco switch.  The f0, f1, f2&n;* and f3 bits indicate that the filter has been triggered by detecting the&n;* frequency programmed into that filter.&n;*&n;* The remaining bits should be set to zero. They will become defined over time&n;* for other interface cards and their needs.&n;*&n;******************************************************************************/
DECL|struct|phone_except
r_struct
id|phone_except
(brace
DECL|member|dtmf_ready
r_int
r_int
id|dtmf_ready
suffix:colon
l_int|1
suffix:semicolon
DECL|member|hookstate
r_int
r_int
id|hookstate
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pstn_ring
r_int
r_int
id|pstn_ring
suffix:colon
l_int|1
suffix:semicolon
DECL|member|caller_id
r_int
r_int
id|caller_id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pstn_wink
r_int
r_int
id|pstn_wink
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f0
r_int
r_int
id|f0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f1
r_int
r_int
id|f1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f2
r_int
r_int
id|f2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f3
r_int
r_int
id|f3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:colon
l_int|23
suffix:semicolon
)brace
suffix:semicolon
DECL|union|telephony_exception
r_union
id|telephony_exception
(brace
DECL|member|bits
r_struct
id|phone_except
id|bits
suffix:semicolon
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* TELEPHONY_H */
eof
