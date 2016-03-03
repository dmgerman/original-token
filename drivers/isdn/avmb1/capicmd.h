multiline_comment|/*&n; * $Id: capicmd.h,v 1.2 2000/03/03 15:50:42 calle Exp $&n; * &n; * CAPI 2.0 Interface for Linux&n; * &n; * Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: capicmd.h,v $&n; * Revision 1.2  2000/03/03 15:50:42  calle&n; * - kernel CAPI:&n; *   - Changed parameter &quot;param&quot; in capi_signal from __u32 to void *.&n; *   - rewrote notifier handling in kcapi.c&n; *   - new notifier NCCI_UP and NCCI_DOWN&n; * - User CAPI:&n; *   - /dev/capi20 is now a cloning device.&n; *   - middleware extentions prepared.&n; * - capidrv.c&n; *   - locking of list operations and module count updates.&n; *&n; * Revision 1.1  1997/03/04 21:50:30  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; * &n; */
macro_line|#ifndef __CAPICMD_H__
DECL|macro|__CAPICMD_H__
mdefine_line|#define __CAPICMD_H__
DECL|macro|CAPI_MSG_BASELEN
mdefine_line|#define CAPI_MSG_BASELEN&t;&t;8
DECL|macro|CAPI_DATA_B3_REQ_LEN
mdefine_line|#define CAPI_DATA_B3_REQ_LEN&t;&t;(CAPI_MSG_BASELEN+4+4+2+2+2)
DECL|macro|CAPI_DATA_B3_RESP_LEN
mdefine_line|#define CAPI_DATA_B3_RESP_LEN&t;&t;(CAPI_MSG_BASELEN+4+2)
multiline_comment|/*----- CAPI commands -----*/
DECL|macro|CAPI_ALERT
mdefine_line|#define CAPI_ALERT&t;&t;    0x01
DECL|macro|CAPI_CONNECT
mdefine_line|#define CAPI_CONNECT&t;&t;    0x02
DECL|macro|CAPI_CONNECT_ACTIVE
mdefine_line|#define CAPI_CONNECT_ACTIVE&t;    0x03
DECL|macro|CAPI_CONNECT_B3_ACTIVE
mdefine_line|#define CAPI_CONNECT_B3_ACTIVE&t;    0x83
DECL|macro|CAPI_CONNECT_B3
mdefine_line|#define CAPI_CONNECT_B3 &t;    0x82
DECL|macro|CAPI_CONNECT_B3_T90_ACTIVE
mdefine_line|#define CAPI_CONNECT_B3_T90_ACTIVE  0x88
DECL|macro|CAPI_DATA_B3
mdefine_line|#define CAPI_DATA_B3&t;&t;    0x86
DECL|macro|CAPI_DISCONNECT_B3
mdefine_line|#define CAPI_DISCONNECT_B3&t;    0x84
DECL|macro|CAPI_DISCONNECT
mdefine_line|#define CAPI_DISCONNECT &t;    0x04
DECL|macro|CAPI_FACILITY
mdefine_line|#define CAPI_FACILITY&t;&t;    0x80
DECL|macro|CAPI_INFO
mdefine_line|#define CAPI_INFO&t;&t;    0x08
DECL|macro|CAPI_LISTEN
mdefine_line|#define CAPI_LISTEN&t;&t;    0x05
DECL|macro|CAPI_MANUFACTURER
mdefine_line|#define CAPI_MANUFACTURER&t;    0xff
DECL|macro|CAPI_RESET_B3
mdefine_line|#define CAPI_RESET_B3&t;&t;    0x87
DECL|macro|CAPI_SELECT_B_PROTOCOL
mdefine_line|#define CAPI_SELECT_B_PROTOCOL&t;    0x41
multiline_comment|/*----- CAPI subcommands -----*/
DECL|macro|CAPI_REQ
mdefine_line|#define CAPI_REQ    0x80
DECL|macro|CAPI_CONF
mdefine_line|#define CAPI_CONF   0x81
DECL|macro|CAPI_IND
mdefine_line|#define CAPI_IND    0x82
DECL|macro|CAPI_RESP
mdefine_line|#define CAPI_RESP   0x83
multiline_comment|/*----- CAPI combined commands -----*/
DECL|macro|CAPICMD
mdefine_line|#define CAPICMD(cmd,subcmd)&t;(((cmd)&lt;&lt;8)|(subcmd))
DECL|macro|CAPI_DISCONNECT_REQ
mdefine_line|#define CAPI_DISCONNECT_REQ&t;&t;CAPICMD(CAPI_DISCONNECT,CAPI_REQ)
DECL|macro|CAPI_DISCONNECT_CONF
mdefine_line|#define CAPI_DISCONNECT_CONF&t;&t;CAPICMD(CAPI_DISCONNECT,CAPI_CONF)
DECL|macro|CAPI_DISCONNECT_IND
mdefine_line|#define CAPI_DISCONNECT_IND&t;&t;CAPICMD(CAPI_DISCONNECT,CAPI_IND)
DECL|macro|CAPI_DISCONNECT_RESP
mdefine_line|#define CAPI_DISCONNECT_RESP&t;&t;CAPICMD(CAPI_DISCONNECT,CAPI_RESP)
DECL|macro|CAPI_ALERT_REQ
mdefine_line|#define CAPI_ALERT_REQ&t;&t;&t;CAPICMD(CAPI_ALERT,CAPI_REQ)
DECL|macro|CAPI_ALERT_CONF
mdefine_line|#define CAPI_ALERT_CONF&t;&t;&t;CAPICMD(CAPI_ALERT,CAPI_CONF)
DECL|macro|CAPI_CONNECT_REQ
mdefine_line|#define CAPI_CONNECT_REQ&t;&t;CAPICMD(CAPI_CONNECT,CAPI_REQ)
DECL|macro|CAPI_CONNECT_CONF
mdefine_line|#define CAPI_CONNECT_CONF&t;&t;CAPICMD(CAPI_CONNECT,CAPI_CONF)
DECL|macro|CAPI_CONNECT_IND
mdefine_line|#define CAPI_CONNECT_IND&t;&t;CAPICMD(CAPI_CONNECT,CAPI_IND)
DECL|macro|CAPI_CONNECT_RESP
mdefine_line|#define CAPI_CONNECT_RESP&t;&t;CAPICMD(CAPI_CONNECT,CAPI_RESP)
DECL|macro|CAPI_CONNECT_ACTIVE_REQ
mdefine_line|#define CAPI_CONNECT_ACTIVE_REQ&t;&t;CAPICMD(CAPI_CONNECT_ACTIVE,CAPI_REQ)
DECL|macro|CAPI_CONNECT_ACTIVE_CONF
mdefine_line|#define CAPI_CONNECT_ACTIVE_CONF&t;CAPICMD(CAPI_CONNECT_ACTIVE,CAPI_CONF)
DECL|macro|CAPI_CONNECT_ACTIVE_IND
mdefine_line|#define CAPI_CONNECT_ACTIVE_IND&t;&t;CAPICMD(CAPI_CONNECT_ACTIVE,CAPI_IND)
DECL|macro|CAPI_CONNECT_ACTIVE_RESP
mdefine_line|#define CAPI_CONNECT_ACTIVE_RESP&t;CAPICMD(CAPI_CONNECT_ACTIVE,CAPI_RESP)
DECL|macro|CAPI_SELECT_B_PROTOCOL_REQ
mdefine_line|#define CAPI_SELECT_B_PROTOCOL_REQ&t;CAPICMD(CAPI_SELECT_B_PROTOCOL,CAPI_REQ)
DECL|macro|CAPI_SELECT_B_PROTOCOL_CONF
mdefine_line|#define CAPI_SELECT_B_PROTOCOL_CONF&t;CAPICMD(CAPI_SELECT_B_PROTOCOL,CAPI_CONF)
DECL|macro|CAPI_CONNECT_B3_ACTIVE_REQ
mdefine_line|#define CAPI_CONNECT_B3_ACTIVE_REQ&t;CAPICMD(CAPI_CONNECT_B3_ACTIVE,CAPI_REQ)
DECL|macro|CAPI_CONNECT_B3_ACTIVE_CONF
mdefine_line|#define CAPI_CONNECT_B3_ACTIVE_CONF&t;CAPICMD(CAPI_CONNECT_B3_ACTIVE,CAPI_CONF)
DECL|macro|CAPI_CONNECT_B3_ACTIVE_IND
mdefine_line|#define CAPI_CONNECT_B3_ACTIVE_IND&t;CAPICMD(CAPI_CONNECT_B3_ACTIVE,CAPI_IND)
DECL|macro|CAPI_CONNECT_B3_ACTIVE_RESP
mdefine_line|#define CAPI_CONNECT_B3_ACTIVE_RESP&t;CAPICMD(CAPI_CONNECT_B3_ACTIVE,CAPI_RESP)
DECL|macro|CAPI_CONNECT_B3_REQ
mdefine_line|#define CAPI_CONNECT_B3_REQ&t;&t;CAPICMD(CAPI_CONNECT_B3,CAPI_REQ)
DECL|macro|CAPI_CONNECT_B3_CONF
mdefine_line|#define CAPI_CONNECT_B3_CONF&t;&t;CAPICMD(CAPI_CONNECT_B3,CAPI_CONF)
DECL|macro|CAPI_CONNECT_B3_IND
mdefine_line|#define CAPI_CONNECT_B3_IND&t;&t;CAPICMD(CAPI_CONNECT_B3,CAPI_IND)
DECL|macro|CAPI_CONNECT_B3_RESP
mdefine_line|#define CAPI_CONNECT_B3_RESP&t;&t;CAPICMD(CAPI_CONNECT_B3,CAPI_RESP)
DECL|macro|CAPI_CONNECT_B3_T90_ACTIVE_IND
mdefine_line|#define CAPI_CONNECT_B3_T90_ACTIVE_IND&t;CAPICMD(CAPI_CONNECT_B3_T90_ACTIVE,CAPI_IND)
DECL|macro|CAPI_CONNECT_B3_T90_ACTIVE_RESP
mdefine_line|#define CAPI_CONNECT_B3_T90_ACTIVE_RESP&t;CAPICMD(CAPI_CONNECT_B3_T90_ACTIVE,CAPI_RESP)
DECL|macro|CAPI_DATA_B3_REQ
mdefine_line|#define CAPI_DATA_B3_REQ&t;&t;CAPICMD(CAPI_DATA_B3,CAPI_REQ)
DECL|macro|CAPI_DATA_B3_CONF
mdefine_line|#define CAPI_DATA_B3_CONF&t;&t;CAPICMD(CAPI_DATA_B3,CAPI_CONF)
DECL|macro|CAPI_DATA_B3_IND
mdefine_line|#define CAPI_DATA_B3_IND&t;&t;CAPICMD(CAPI_DATA_B3,CAPI_IND)
DECL|macro|CAPI_DATA_B3_RESP
mdefine_line|#define CAPI_DATA_B3_RESP&t;&t;CAPICMD(CAPI_DATA_B3,CAPI_RESP)
DECL|macro|CAPI_DISCONNECT_B3_REQ
mdefine_line|#define CAPI_DISCONNECT_B3_REQ&t;&t;CAPICMD(CAPI_DISCONNECT_B3,CAPI_REQ)
DECL|macro|CAPI_DISCONNECT_B3_CONF
mdefine_line|#define CAPI_DISCONNECT_B3_CONF&t;&t;CAPICMD(CAPI_DISCONNECT_B3,CAPI_CONF)
DECL|macro|CAPI_DISCONNECT_B3_IND
mdefine_line|#define CAPI_DISCONNECT_B3_IND&t;&t;CAPICMD(CAPI_DISCONNECT_B3,CAPI_IND)
DECL|macro|CAPI_DISCONNECT_B3_RESP
mdefine_line|#define CAPI_DISCONNECT_B3_RESP&t;&t;CAPICMD(CAPI_DISCONNECT_B3,CAPI_RESP)
DECL|macro|CAPI_RESET_B3_REQ
mdefine_line|#define CAPI_RESET_B3_REQ&t;&t;CAPICMD(CAPI_RESET_B3,CAPI_REQ)
DECL|macro|CAPI_RESET_B3_CONF
mdefine_line|#define CAPI_RESET_B3_CONF&t;&t;CAPICMD(CAPI_RESET_B3,CAPI_CONF)
DECL|macro|CAPI_RESET_B3_IND
mdefine_line|#define CAPI_RESET_B3_IND&t;&t;CAPICMD(CAPI_RESET_B3,CAPI_IND)
DECL|macro|CAPI_RESET_B3_RESP
mdefine_line|#define CAPI_RESET_B3_RESP&t;&t;CAPICMD(CAPI_RESET_B3,CAPI_RESP)
DECL|macro|CAPI_LISTEN_REQ
mdefine_line|#define CAPI_LISTEN_REQ&t;&t;&t;CAPICMD(CAPI_LISTEN,CAPI_REQ)
DECL|macro|CAPI_LISTEN_CONF
mdefine_line|#define CAPI_LISTEN_CONF&t;&t;CAPICMD(CAPI_LISTEN,CAPI_CONF)
DECL|macro|CAPI_MANUFACTURER_REQ
mdefine_line|#define CAPI_MANUFACTURER_REQ&t;&t;CAPICMD(CAPI_MANUFACTURER,CAPI_REQ)
DECL|macro|CAPI_MANUFACTURER_CONF
mdefine_line|#define CAPI_MANUFACTURER_CONF&t;&t;CAPICMD(CAPI_MANUFACTURER,CAPI_CONF)
DECL|macro|CAPI_MANUFACTURER_IND
mdefine_line|#define CAPI_MANUFACTURER_IND&t;&t;CAPICMD(CAPI_MANUFACTURER,CAPI_IND)
DECL|macro|CAPI_MANUFACTURER_RESP
mdefine_line|#define CAPI_MANUFACTURER_RESP&t;&t;CAPICMD(CAPI_MANUFACTURER,CAPI_RESP)
DECL|macro|CAPI_FACILITY_REQ
mdefine_line|#define CAPI_FACILITY_REQ&t;&t;CAPICMD(CAPI_FACILITY,CAPI_REQ)
DECL|macro|CAPI_FACILITY_CONF
mdefine_line|#define CAPI_FACILITY_CONF&t;&t;CAPICMD(CAPI_FACILITY,CAPI_CONF)
DECL|macro|CAPI_FACILITY_IND
mdefine_line|#define CAPI_FACILITY_IND&t;&t;CAPICMD(CAPI_FACILITY,CAPI_IND)
DECL|macro|CAPI_FACILITY_RESP
mdefine_line|#define CAPI_FACILITY_RESP&t;&t;CAPICMD(CAPI_FACILITY,CAPI_RESP)
DECL|macro|CAPI_INFO_REQ
mdefine_line|#define CAPI_INFO_REQ&t;&t;&t;CAPICMD(CAPI_INFO,CAPI_REQ)
DECL|macro|CAPI_INFO_CONF
mdefine_line|#define CAPI_INFO_CONF&t;&t;&t;CAPICMD(CAPI_INFO,CAPI_CONF)
DECL|macro|CAPI_INFO_IND
mdefine_line|#define CAPI_INFO_IND&t;&t;&t;CAPICMD(CAPI_INFO,CAPI_IND)
DECL|macro|CAPI_INFO_RESP
mdefine_line|#define CAPI_INFO_RESP&t;&t;&t;CAPICMD(CAPI_INFO,CAPI_RESP)
macro_line|#endif&t;&t;&t;&t;/* __CAPICMD_H__ */
eof
