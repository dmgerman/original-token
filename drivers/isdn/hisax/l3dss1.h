multiline_comment|/* $Id: l3dss1.h,v 1.6 1998/03/19 13:18:50 keil Exp $&n; *&n; *  DSS1 (Euro) D-channel protocol defines&n; *&n; * $Log: l3dss1.h,v $&n; * Revision 1.6  1998/03/19 13:18:50  keil&n; * Start of a CAPI like interface for supplementary Service&n; * first service: SUSPEND&n; *&n; * Revision 1.5  1998/02/02 13:34:30  keil&n; * Support australian Microlink net and german AOCD&n; *&n; * Revision 1.4  1997/10/29 19:07:54  keil&n; * changes for 2.1&n; *&n; * Revision 1.3  1997/08/07 17:44:37  keil&n; * Fix RESTART&n; *&n; * Revision 1.2  1997/08/03 14:36:34  keil&n; * Implement RESTART procedure&n; *&n; * Revision 1.1  1997/07/27 21:08:38  keil&n; * new&n; *&n; *&n; *&n; */
DECL|macro|T303
mdefine_line|#define T303&t;4000
DECL|macro|T304
mdefine_line|#define T304&t;30000
DECL|macro|T305
mdefine_line|#define T305&t;30000
DECL|macro|T308
mdefine_line|#define T308&t;4000
DECL|macro|T310
mdefine_line|#define T310&t;30000
DECL|macro|T313
mdefine_line|#define T313&t;4000
DECL|macro|T318
mdefine_line|#define T318&t;4000
DECL|macro|T319
mdefine_line|#define T319&t;4000
multiline_comment|/*&n; * Message-Types&n; */
DECL|macro|MT_ALERTING
mdefine_line|#define MT_ALERTING            0x01
DECL|macro|MT_CALL_PROCEEDING
mdefine_line|#define MT_CALL_PROCEEDING     0x02
DECL|macro|MT_CONNECT
mdefine_line|#define MT_CONNECT             0x07
DECL|macro|MT_CONNECT_ACKNOWLEDGE
mdefine_line|#define MT_CONNECT_ACKNOWLEDGE 0x0f
DECL|macro|MT_PROGRESS
mdefine_line|#define MT_PROGRESS            0x03
DECL|macro|MT_SETUP
mdefine_line|#define MT_SETUP               0x05
DECL|macro|MT_SETUP_ACKNOWLEDGE
mdefine_line|#define MT_SETUP_ACKNOWLEDGE   0x0d
DECL|macro|MT_RESUME
mdefine_line|#define MT_RESUME              0x26
DECL|macro|MT_RESUME_ACKNOWLEDGE
mdefine_line|#define MT_RESUME_ACKNOWLEDGE  0x2e
DECL|macro|MT_RESUME_REJECT
mdefine_line|#define MT_RESUME_REJECT       0x22
DECL|macro|MT_SUSPEND
mdefine_line|#define MT_SUSPEND             0x25
DECL|macro|MT_SUSPEND_ACKNOWLEDGE
mdefine_line|#define MT_SUSPEND_ACKNOWLEDGE 0x2d
DECL|macro|MT_SUSPEND_REJECT
mdefine_line|#define MT_SUSPEND_REJECT      0x21
DECL|macro|MT_USER_INFORMATION
mdefine_line|#define MT_USER_INFORMATION    0x20
DECL|macro|MT_DISCONNECT
mdefine_line|#define MT_DISCONNECT          0x45
DECL|macro|MT_RELEASE
mdefine_line|#define MT_RELEASE             0x4d
DECL|macro|MT_RELEASE_COMPLETE
mdefine_line|#define MT_RELEASE_COMPLETE    0x5a
DECL|macro|MT_RESTART
mdefine_line|#define MT_RESTART             0x46
DECL|macro|MT_RESTART_ACKNOWLEDGE
mdefine_line|#define MT_RESTART_ACKNOWLEDGE 0x4e
DECL|macro|MT_SEGMENT
mdefine_line|#define MT_SEGMENT             0x60
DECL|macro|MT_CONGESTION_CONTROL
mdefine_line|#define MT_CONGESTION_CONTROL  0x79
DECL|macro|MT_INFORMATION
mdefine_line|#define MT_INFORMATION         0x7b
DECL|macro|MT_FACILITY
mdefine_line|#define MT_FACILITY            0x62
DECL|macro|MT_NOTIFY
mdefine_line|#define MT_NOTIFY              0x6e
DECL|macro|MT_STATUS
mdefine_line|#define MT_STATUS              0x7d
DECL|macro|MT_STATUS_ENQUIRY
mdefine_line|#define MT_STATUS_ENQUIRY      0x75
DECL|macro|MT_INVALID
mdefine_line|#define MT_INVALID             0xff
DECL|macro|IE_BEARER
mdefine_line|#define IE_BEARER              0x04
DECL|macro|IE_CAUSE
mdefine_line|#define IE_CAUSE               0x08
DECL|macro|IE_CALLID
mdefine_line|#define IE_CALLID              0x10
DECL|macro|IE_FACILITY
mdefine_line|#define IE_FACILITY            0x1c
DECL|macro|IE_CALL_STATE
mdefine_line|#define IE_CALL_STATE          0x14
DECL|macro|IE_CHANNEL_ID
mdefine_line|#define IE_CHANNEL_ID          0x18
DECL|macro|IE_RESTART_IND
mdefine_line|#define IE_RESTART_IND         0x79
eof
