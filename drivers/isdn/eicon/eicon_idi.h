multiline_comment|/* $Id: eicon_idi.h,v 1.4 1999/03/29 11:19:44 armin Exp $&n; *&n; * ISDN lowlevel-module for the Eicon.Diehl active cards.&n; * IDI-Interface&n; *&n; * Copyright 1998,99 by Armin Schindler (mac@melware.de)&n; * Copyright 1999    Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: eicon_idi.h,v $&n; * Revision 1.4  1999/03/29 11:19:44  armin&n; * I/O stuff now in seperate file (eicon_io.c)&n; * Old ISA type cards (S,SX,SCOM,Quadro,S2M) implemented.&n; *&n; * Revision 1.3  1999/03/02 12:37:45  armin&n; * Added some important checks.&n; * Analog Modem with DSP.&n; * Channels will be added to Link-Level after loading firmware.&n; *&n; * Revision 1.2  1999/01/24 20:14:18  armin&n; * Changed and added debug stuff.&n; * Better data sending. (still problems with tty&squot;s flip buffer)&n; *&n; * Revision 1.1  1999/01/01 18:09:42  armin&n; * First checkin of new eicon driver.&n; * DIVA-Server BRI/PCI and PRI/PCI are supported.&n; * Old diehl code is obsolete.&n; *&n; *&n; */
macro_line|#ifndef IDI_H
DECL|macro|IDI_H
mdefine_line|#define IDI_H
DECL|macro|ASSIGN
mdefine_line|#define ASSIGN  0x01
DECL|macro|REMOVE
mdefine_line|#define REMOVE  0xff
DECL|macro|CALL_REQ
mdefine_line|#define CALL_REQ 1      /* call request                             */
DECL|macro|CALL_CON
mdefine_line|#define CALL_CON 1      /* call confirmation                        */
DECL|macro|CALL_IND
mdefine_line|#define CALL_IND 2      /* incoming call connected                  */
DECL|macro|LISTEN_REQ
mdefine_line|#define LISTEN_REQ 2    /* listen request                           */
DECL|macro|HANGUP
mdefine_line|#define HANGUP 3        /* hangup request/indication                */
DECL|macro|SUSPEND
mdefine_line|#define SUSPEND 4       /* call suspend request/confirm             */
DECL|macro|RESUME
mdefine_line|#define RESUME 5        /* call resume request/confirm              */
DECL|macro|SUSPEND_REJ
mdefine_line|#define SUSPEND_REJ 6   /* suspend rejected indication              */
DECL|macro|USER_DATA
mdefine_line|#define USER_DATA 8     /* user data for user to user signaling     */
DECL|macro|CONGESTION
mdefine_line|#define CONGESTION 9    /* network congestion indication            */
DECL|macro|INDICATE_REQ
mdefine_line|#define INDICATE_REQ 10 /* request to indicate an incoming call     */
DECL|macro|INDICATE_IND
mdefine_line|#define INDICATE_IND 10 /* indicates that there is an incoming call */
DECL|macro|CALL_RES
mdefine_line|#define CALL_RES 11     /* accept an incoming call                  */
DECL|macro|CALL_ALERT
mdefine_line|#define CALL_ALERT 12   /* send ALERT for incoming call             */
DECL|macro|INFO_REQ
mdefine_line|#define INFO_REQ 13     /* INFO request                             */
DECL|macro|INFO_IND
mdefine_line|#define INFO_IND 13     /* INFO indication                          */
DECL|macro|REJECT
mdefine_line|#define REJECT 14       /* reject an incoming call                  */
DECL|macro|RESOURCES
mdefine_line|#define RESOURCES 15    /* reserve B-Channel hardware resources     */
DECL|macro|TEL_CTRL
mdefine_line|#define TEL_CTRL 16     /* Telephone control request/indication     */
DECL|macro|STATUS_REQ
mdefine_line|#define STATUS_REQ 17   /* Request D-State (returned in INFO_IND)   */
DECL|macro|FAC_REG_REQ
mdefine_line|#define FAC_REG_REQ 18  /* connection idependent fac registration   */
DECL|macro|FAC_REG_ACK
mdefine_line|#define FAC_REG_ACK 19  /* fac registration acknowledge             */
DECL|macro|FAC_REG_REJ
mdefine_line|#define FAC_REG_REJ 20  /* fac registration reject                  */
DECL|macro|CALL_COMPLETE
mdefine_line|#define CALL_COMPLETE 21/* send a CALL_PROC for incoming call       */
DECL|macro|AOC_IND
mdefine_line|#define AOC_IND       26/* Advice of Charge                         */
DECL|macro|IDI_N_MDATA
mdefine_line|#define IDI_N_MDATA         (0x01)
DECL|macro|IDI_N_CONNECT
mdefine_line|#define IDI_N_CONNECT       (0x02)
DECL|macro|IDI_N_CONNECT_ACK
mdefine_line|#define IDI_N_CONNECT_ACK   (0x03)
DECL|macro|IDI_N_DISC
mdefine_line|#define IDI_N_DISC          (0x04)
DECL|macro|IDI_N_DISC_ACK
mdefine_line|#define IDI_N_DISC_ACK      (0x05)
DECL|macro|IDI_N_RESET
mdefine_line|#define IDI_N_RESET         (0x06)
DECL|macro|IDI_N_RESET_ACK
mdefine_line|#define IDI_N_RESET_ACK     (0x07)
DECL|macro|IDI_N_DATA
mdefine_line|#define IDI_N_DATA          (0x08)
DECL|macro|IDI_N_EDATA
mdefine_line|#define IDI_N_EDATA         (0x09)
DECL|macro|IDI_N_UDATA
mdefine_line|#define IDI_N_UDATA         (0x0a)
DECL|macro|IDI_N_BDATA
mdefine_line|#define IDI_N_BDATA         (0x0b)
DECL|macro|IDI_N_DATA_ACK
mdefine_line|#define IDI_N_DATA_ACK      (0x0c)
DECL|macro|IDI_N_EDATA_ACK
mdefine_line|#define IDI_N_EDATA_ACK     (0x0d)
DECL|macro|N_Q_BIT
mdefine_line|#define N_Q_BIT         0x10    /* Q-bit for req/ind                */
DECL|macro|N_M_BIT
mdefine_line|#define N_M_BIT         0x20    /* M-bit for req/ind                */
DECL|macro|N_D_BIT
mdefine_line|#define N_D_BIT         0x40    /* D-bit for req/ind                */
DECL|macro|SHIFT
mdefine_line|#define SHIFT 0x90              /* codeset shift                    */
DECL|macro|MORE
mdefine_line|#define MORE 0xa0               /* more data                        */
DECL|macro|CL
mdefine_line|#define CL 0xb0                 /* congestion level                 */
multiline_comment|/* codeset 0                                                */
DECL|macro|BC
mdefine_line|#define BC  0x04                /* Bearer Capability                */
DECL|macro|CAU
mdefine_line|#define CAU 0x08                /* cause                            */
DECL|macro|CAD
mdefine_line|#define CAD 0x0c                /* Connected address                */
DECL|macro|CAI
mdefine_line|#define CAI 0x10                /* call identity                    */
DECL|macro|CHI
mdefine_line|#define CHI 0x18                /* channel identification           */
DECL|macro|LLI
mdefine_line|#define LLI 0x19                /* logical link id                  */
DECL|macro|CHA
mdefine_line|#define CHA 0x1a                /* charge advice                    */
DECL|macro|FTY
mdefine_line|#define FTY 0x1c
DECL|macro|PI
mdefine_line|#define PI  0x1e&t;&t;/* Progress Indicator&t;&t;    */
DECL|macro|NI
mdefine_line|#define NI  0x27&t;&t;/* Notification Indicator&t;    */
DECL|macro|DT
mdefine_line|#define DT  0x29                /* ETSI date/time                   */
DECL|macro|KEY
mdefine_line|#define KEY 0x2c                /* keypad information element       */
DECL|macro|DSP
mdefine_line|#define DSP 0x28                /* display                          */
DECL|macro|OAD
mdefine_line|#define OAD 0x6c                /* origination address              */
DECL|macro|OSA
mdefine_line|#define OSA 0x6d                /* origination sub-address          */
DECL|macro|CPN
mdefine_line|#define CPN 0x70                /* called party number              */
DECL|macro|DSA
mdefine_line|#define DSA 0x71                /* destination sub-address          */
DECL|macro|RDN
mdefine_line|#define RDN 0x74&t;&t;/* redirecting number&t;&t;    */
DECL|macro|LLC
mdefine_line|#define LLC 0x7c                /* low layer compatibility          */
DECL|macro|HLC
mdefine_line|#define HLC 0x7d                /* high layer compatibility         */
DECL|macro|UUI
mdefine_line|#define UUI 0x7e                /* user user information            */
DECL|macro|ESC
mdefine_line|#define ESC 0x7f                /* escape extension                 */
DECL|macro|DLC
mdefine_line|#define DLC 0x20                /* data link layer configuration    */
DECL|macro|NLC
mdefine_line|#define NLC 0x21                /* network layer configuration      */
multiline_comment|/* codeset 6                                                */
DECL|macro|SIN
mdefine_line|#define SIN 0x01                /* service indicator                */
DECL|macro|CIF
mdefine_line|#define CIF 0x02                /* charging information             */
DECL|macro|DATE
mdefine_line|#define DATE 0x03               /* date                             */
DECL|macro|CPS
mdefine_line|#define CPS 0x07                /* called party status              */
multiline_comment|/*------------------------------------------------------------------*/
multiline_comment|/* return code coding                                               */
multiline_comment|/*------------------------------------------------------------------*/
DECL|macro|UNKNOWN_COMMAND
mdefine_line|#define UNKNOWN_COMMAND         0x01    /* unknown command          */
DECL|macro|WRONG_COMMAND
mdefine_line|#define WRONG_COMMAND           0x02    /* wrong command            */
DECL|macro|WRONG_ID
mdefine_line|#define WRONG_ID                0x03    /* unknown task/entity id   */
DECL|macro|WRONG_CH
mdefine_line|#define WRONG_CH                0x04    /* wrong task/entity id     */
DECL|macro|UNKNOWN_IE
mdefine_line|#define UNKNOWN_IE              0x05    /* unknown information el.  */
DECL|macro|WRONG_IE
mdefine_line|#define WRONG_IE                0x06    /* wrong information el.    */
DECL|macro|OUT_OF_RESOURCES
mdefine_line|#define OUT_OF_RESOURCES        0x07    /* card out of res.         */
DECL|macro|N_FLOW_CONTROL
mdefine_line|#define N_FLOW_CONTROL          0x10    /* Flow-Control, retry      */
DECL|macro|ASSIGN_RC
mdefine_line|#define ASSIGN_RC               0xe0    /* ASSIGN acknowledgement   */
DECL|macro|ASSIGN_OK
mdefine_line|#define ASSIGN_OK               0xef    /* ASSIGN OK                */
DECL|macro|OK_FC
mdefine_line|#define OK_FC                   0xfc    /* Flow-Control RC          */
DECL|macro|READY_INT
mdefine_line|#define READY_INT               0xfd    /* Ready interrupt          */
DECL|macro|TIMER_INT
mdefine_line|#define TIMER_INT               0xfe    /* timer interrupt          */
DECL|macro|OK
mdefine_line|#define OK                      0xff    /* command accepted         */
multiline_comment|/*------------------------------------------------------------------*/
r_typedef
r_struct
(brace
DECL|member|cpn
r_char
id|cpn
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|oad
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|dsa
r_char
id|dsa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|plan
id|__u8
id|plan
suffix:semicolon
DECL|member|screen
id|__u8
id|screen
suffix:semicolon
DECL|member|sin
id|__u8
id|sin
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|chi
id|__u8
id|chi
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_chi
id|__u8
id|e_chi
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bc
id|__u8
id|bc
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|e_bc
id|__u8
id|e_bc
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|llc
id|__u8
id|llc
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|hlc
id|__u8
id|hlc
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|cau
id|__u8
id|cau
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|e_cau
id|__u8
id|e_cau
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|e_mt
id|__u8
id|e_mt
suffix:semicolon
DECL|member|dt
id|__u8
id|dt
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|display
r_char
id|display
(braket
l_int|83
)braket
suffix:semicolon
DECL|member|keypad
r_char
id|keypad
(braket
l_int|35
)braket
suffix:semicolon
DECL|member|rdn
r_char
id|rdn
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|idi_ind_message
)brace
id|idi_ind_message
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Req
id|__u8
id|Req
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ReqId
id|__u8
id|ReqId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ReqCh
id|__u8
id|ReqCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved1
id|__u8
id|Reserved1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
(braket
l_int|8
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|XBuffer
id|eicon_PBUFFER
id|XBuffer
suffix:semicolon
DECL|typedef|eicon_REQ
)brace
id|eicon_REQ
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Rc
id|__u8
id|Rc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RcId
id|__u8
id|RcId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RcCh
id|__u8
id|RcCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved1
id|__u8
id|Reserved1
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|8
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|eicon_RC
)brace
id|eicon_RC
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|next
id|__u16
id|next
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Ind
id|__u8
id|Ind
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|IndId
id|__u8
id|IndId
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|IndCh
id|__u8
id|IndCh
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|MInd
id|__u8
id|MInd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|MLength
id|__u16
id|MLength
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reference
id|__u16
id|Reference
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RNR
id|__u8
id|RNR
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Reserved
id|__u8
id|Reserved
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Ack
id|__u32
id|Ack
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|RBuffer
id|eicon_PBUFFER
id|RBuffer
suffix:semicolon
DECL|typedef|eicon_IND
)brace
id|eicon_IND
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|NextReq
id|__u16
id|NextReq
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Req Buffer */
DECL|member|NextRc
id|__u16
id|NextRc
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Rc Buffer  */
DECL|member|NextInd
id|__u16
id|NextInd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pointer to next Ind Buffer */
DECL|member|ReqInput
id|__u8
id|ReqInput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Req Buffers sent */
DECL|member|ReqOutput
id|__u8
id|ReqOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Req Buffers returned */
DECL|member|ReqReserved
id|__u8
id|ReqReserved
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*number of Req Buffers reserved */
DECL|member|Int
id|__u8
id|Int
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISDN-P interrupt           */
DECL|member|XLock
id|__u8
id|XLock
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Lock field for arbitration */
DECL|member|RcOutput
id|__u8
id|RcOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Rc buffers received */
DECL|member|IndOutput
id|__u8
id|IndOutput
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of Ind buffers received */
DECL|member|IMask
id|__u8
id|IMask
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt Mask Flag        */
DECL|member|Reserved1
id|__u8
id|Reserved1
(braket
l_int|2
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* reserved field, do not use */
DECL|member|ReadyInt
id|__u8
id|ReadyInt
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* request field for ready int */
DECL|member|Reserved2
id|__u8
id|Reserved2
(braket
l_int|12
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* reserved field, do not use */
DECL|member|InterfaceType
id|__u8
id|InterfaceType
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* interface type 1=16K    */
DECL|member|Signature
id|__u16
id|Signature
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISDN-P initialized ind  */
DECL|member|B
id|__u8
id|B
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* buffer space for Req,Ind and Rc */
DECL|typedef|eicon_pr_ram
)brace
id|eicon_pr_ram
suffix:semicolon
r_extern
r_int
id|idi_do_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_int
id|cmd
comma
r_int
id|layer
)paren
suffix:semicolon
r_extern
r_int
id|idi_hangup
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|idi_connect_res
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|eicon_idi_listen_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|idi_connect_req
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_char
op_star
id|phone
comma
r_char
op_star
id|eazmsn
comma
r_int
id|si1
comma
r_int
id|si2
)paren
suffix:semicolon
r_extern
r_void
id|idi_handle_ack
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|idi_handle_ind
c_func
(paren
id|eicon_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|eicon_idi_manage
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_manifbuf
op_star
id|mb
)paren
suffix:semicolon
r_extern
r_int
id|idi_send_data
c_func
(paren
id|eicon_card
op_star
id|card
comma
id|eicon_chan
op_star
id|chan
comma
r_int
id|ack
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
macro_line|#endif
eof
