multiline_comment|/*&n; *&t;seagate.h Copyright (C) 1992 Drew Eckhardt &n; *&t;low level scsi driver header for ST01/ST02 by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SEAGATE_H
DECL|macro|SEAGATE_H
mdefine_line|#define SEAGATE_H
multiline_comment|/*&n;&t;$Header&n;*/
macro_line|#ifndef ASM
r_int
id|seagate_st0x_detect
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|seagate_st0x_command
c_func
(paren
r_int
r_char
id|target
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buff
comma
r_int
id|bufflen
)paren
suffix:semicolon
r_int
id|seagate_st0x_abort
c_func
(paren
r_int
)paren
suffix:semicolon
r_char
op_star
id|seagate_st0x_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|seagate_st0x_reset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|macro|SEAGATE_ST0X
mdefine_line|#define SEAGATE_ST0X  {&quot;Seagate ST-01/ST-02&quot;, seagate_st0x_detect, &t;&bslash;&n;&t;&t;&t; seagate_st0x_info, seagate_st0x_command,  &t;&bslash;&n;&t;&t;&t; NULL, seagate_st0x_abort, seagate_st0x_reset,&t;&bslash;&n;&t;&t;&t; 0, 7, 0}
macro_line|#endif
multiline_comment|/*&n;&t;defining PARITY causes parity data to be checked&n;*/
DECL|macro|PARITY
mdefine_line|#define PARITY
multiline_comment|/*&n;&t;defining ARBITRATE causes the arbitration sequence to be used.  And speed to drop by a &n;&t;factor of ten.&n;*/
DECL|macro|ARBITRATE
macro_line|#undef ARBITRATE
multiline_comment|/*&n;&t;Thanks to Brian Antoine for the example code in his Messy-Loss ST-01&n;&t;&t;driver, and Mitsugu Suzuki for information on the ST-01&n;&t;&t;SCSI host.&n;*/
multiline_comment|/*&n;&t;CONTROL defines&n;*/
DECL|macro|CMD_RST
mdefine_line|#define CMD_RST &t;&t;0x01
DECL|macro|CMD_SEL
mdefine_line|#define CMD_SEL &t;&t;0x02
DECL|macro|CMD_BSY
mdefine_line|#define CMD_BSY &t;&t;0x04
DECL|macro|CMD_ATTN
mdefine_line|#define CMD_ATTN    &t;&t;0x08
DECL|macro|CMD_START_ARB
mdefine_line|#define CMD_START_ARB&t;&t;0x10
DECL|macro|CMD_EN_PARITY
mdefine_line|#define CMD_EN_PARITY&t;&t;0x20
DECL|macro|CMD_INTR
mdefine_line|#define CMD_INTR&t;&t;0x40
DECL|macro|CMD_DRVR_ENABLE
mdefine_line|#define CMD_DRVR_ENABLE&t;&t;0x80
multiline_comment|/*&n;&t;STATUS&n;*/
DECL|macro|STAT_BSY
mdefine_line|#define STAT_BSY&t;&t;0x01
DECL|macro|STAT_MSG
mdefine_line|#define STAT_MSG&t;&t;0x02
DECL|macro|STAT_IO
mdefine_line|#define STAT_IO&t;&t;&t;0x04
DECL|macro|STAT_CD
mdefine_line|#define STAT_CD&t;&t;&t;0x08
DECL|macro|STAT_REQ
mdefine_line|#define STAT_REQ&t;&t;0x10
DECL|macro|STAT_SEL
mdefine_line|#define STAT_SEL&t;&t;0x20
DECL|macro|STAT_PARITY
mdefine_line|#define STAT_PARITY&t;&t;0x40
DECL|macro|STAT_ARB_CMPL
mdefine_line|#define STAT_ARB_CMPL&t;&t;0x80
multiline_comment|/* &n;&t;REQUESTS&n;*/
DECL|macro|REQ_MASK
mdefine_line|#define REQ_MASK (STAT_CD |  STAT_IO | STAT_MSG)
DECL|macro|REQ_DATAOUT
mdefine_line|#define REQ_DATAOUT 0
DECL|macro|REQ_DATAIN
mdefine_line|#define REQ_DATAIN STAT_IO
DECL|macro|REQ_CMDOUT
mdefine_line|#define REQ_CMDOUT STAT_CD
DECL|macro|REQ_STATIN
mdefine_line|#define REQ_STATIN (STAT_CD | STAT_IO)
DECL|macro|REQ_MSGOUT
mdefine_line|#define REQ_MSGOUT (STAT_MSG | STAT_CD)
DECL|macro|REQ_MSGIN
mdefine_line|#define REQ_MSGIN (STAT_MSG | STAT_CD | STAT_IO)
r_extern
r_volatile
r_int
id|seagate_st0x_timeout
suffix:semicolon
macro_line|#ifdef PARITY
DECL|macro|BASE_CMD
mdefine_line|#define BASE_CMD CMD_EN_PARITY
macro_line|#else
DECL|macro|BASE_CMD
mdefine_line|#define BASE_CMD  0
macro_line|#endif
multiline_comment|/*&n;&t;Debugging code&n;*/
DECL|macro|PHASE_BUS_FREE
mdefine_line|#define PHASE_BUS_FREE 1
DECL|macro|PHASE_ARBITRATION
mdefine_line|#define PHASE_ARBITRATION 2
DECL|macro|PHASE_SELECTION
mdefine_line|#define PHASE_SELECTION 4
DECL|macro|PHASE_DATAIN
mdefine_line|#define PHASE_DATAIN 8 
DECL|macro|PHASE_DATAOUT
mdefine_line|#define PHASE_DATAOUT 0x10
DECL|macro|PHASE_CMDOUT
mdefine_line|#define PHASE_CMDOUT 0x20
DECL|macro|PHASE_MSGIN
mdefine_line|#define PHASE_MSGIN 0x40
DECL|macro|PHASE_MSGOUT
mdefine_line|#define PHASE_MSGOUT 0x80
DECL|macro|PHASE_STATUSIN
mdefine_line|#define PHASE_STATUSIN 0x100
DECL|macro|PHASE_ETC
mdefine_line|#define PHASE_ETC (PHASE_DATAIN | PHASE_DATA_OUT | PHASE_CMDOUT | PHASE_MSGIN | PHASE_MSGOUT | PHASE_STATUSIN)
DECL|macro|PRINT_COMMAND
mdefine_line|#define PRINT_COMMAND 0x200
DECL|macro|PHASE_EXIT
mdefine_line|#define PHASE_EXIT 0x400
multiline_comment|/* &n;&t;Control options - these are timeouts specified in .01 seconds.&n;*/
DECL|macro|ST0X_BUS_FREE_DELAY
mdefine_line|#define ST0X_BUS_FREE_DELAY 25
DECL|macro|ST0X_SELECTION_DELAY
mdefine_line|#define ST0X_SELECTION_DELAY 25
macro_line|#endif
eof
