multiline_comment|/*&n; *&t;buslogic.h&t;(C) 1993 David B. Gentzel&n; *&t;Low-level scsi driver for BusLogic adapters&n; *&t;by David B. Gentzel, Whitfield Software Services, Carnegie, PA&n; *&t;    (gentzel@nova.enet.dec.com)&n; *&t;Thanks to BusLogic for providing the necessary documentation&n; *&n; *&t;The original version of this driver was derived from aha1542.[ch] which&n; *&t;is Copyright (C) 1992 Tommy Thorn.  Much has been reworked, but most of&n; *&t;basic structure and substantial chunks of code still remain.&n; */
macro_line|#ifndef _BUSLOGIC_H
r_int
id|buslogic_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|buslogic_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|buslogic_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|buslogic_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|buslogic_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|buslogic_biosparam
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|BUSLOGIC_CMDLUN
mdefine_line|#define BUSLOGIC_CMDLUN 4&t;/* ??? */
DECL|macro|BUSLOGIC
mdefine_line|#define BUSLOGIC { NULL, &t;&t;&t;&bslash;&n;&t;&t;   &quot;BusLogic&quot;,&t;&t;&t;&bslash;&n;&t;&t;   buslogic_detect,&t;&t;&bslash;&n;&t;&t;   NULL,&t;&t;&t;&bslash;&n;&t;&t;   buslogic_info,&t;&t;&bslash;&n;&t;&t;   0,&t;/* no command func */&t;&bslash;&n;&t;&t;   buslogic_queuecommand,&t;&bslash;&n;&t;&t;   buslogic_abort,&t;&t;&bslash;&n;&t;&t;   buslogic_reset,&t;&t;&bslash;&n;&t;&t;   0,&t;/* slave_attach NYI */&t;&bslash;&n;&t;&t;   buslogic_biosparam,&t;&t;&bslash;&n;&t;&t;   0,&t;/* set by driver */&t;&bslash;&n;&t;&t;   0,&t;/* set by driver */&t;&bslash;&n;&t;&t;   0,&t;/* set by driver */&t;&bslash;&n;&t;&t;   BUSLOGIC_CMDLUN,&t;&t;&bslash;&n;&t;&t;   0,&t;&t;&t;&t;&bslash;&n;&t;&t;   0,&t;/* set by driver */&t;&bslash;&n;&t;&t;   ENABLE_CLUSTERING&t;&t;&bslash;&n;&t;&t; }
macro_line|#ifdef BUSLOGIC_PRIVATE_H
multiline_comment|/* ??? These don&squot;t really belong here */
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE 0
macro_line|#endif
DECL|macro|ARRAY_SIZE
mdefine_line|#define ARRAY_SIZE(arr) (sizeof (arr) / sizeof (arr)[0])
DECL|macro|PACKED
mdefine_line|#define PACKED __attribute__((packed))
DECL|macro|BD_ABORT
mdefine_line|#define BD_ABORT&t;0x0001
DECL|macro|BD_COMMAND
mdefine_line|#define BD_COMMAND&t;0x0002
DECL|macro|BD_DETECT
mdefine_line|#define BD_DETECT&t;0x0004
DECL|macro|BD_INTERRUPT
mdefine_line|#define BD_INTERRUPT&t;0x0008
DECL|macro|BD_RESET
mdefine_line|#define BD_RESET&t;0x0010
multiline_comment|/* I/O Port interface */
multiline_comment|/* READ */
DECL|macro|STATUS
mdefine_line|#define STATUS(base) (base)
DECL|macro|DACT
mdefine_line|#define DACT 0x80&t;&t;/* Diagnostic Active */
DECL|macro|DFAIL
mdefine_line|#define DFAIL 0x40&t;&t;/* Diagonostic Failure */
DECL|macro|INREQ
mdefine_line|#define INREQ 0x20&t;&t;/* Initialization Required */
DECL|macro|HARDY
mdefine_line|#define HARDY 0x10&t;&t;/* Host Adapter Ready */
DECL|macro|CPRBSY
mdefine_line|#define CPRBSY 0x08&t;&t;/* Command/Parameter Register Busy */
DECL|macro|DIRRDY
mdefine_line|#define DIRRDY 0x04&t;&t;/* Data In Register Ready */
DECL|macro|CMDINV
mdefine_line|#define CMDINV 0x01&t;&t;/* Command Invalid */
DECL|macro|STATMASK
mdefine_line|#define STATMASK 0xFD&t;&t;/* 0x02 is reserved */
DECL|macro|DATA_IN
mdefine_line|#define DATA_IN(base) (STATUS(base) + 1)
DECL|macro|INTERRUPT
mdefine_line|#define INTERRUPT(base) (STATUS(base) + 2)
DECL|macro|INTV
mdefine_line|#define INTV 0x80&t;&t;/* Interrupt Valid */
DECL|macro|RSTS
mdefine_line|#define RSTS 0x08&t;&t;/* SCSI Reset State */
DECL|macro|CMDC
mdefine_line|#define CMDC 0x04&t;&t;/* Command Complete */
DECL|macro|MBOR
mdefine_line|#define MBOR 0x02&t;&t;/* Mailbox Out Ready */
DECL|macro|IMBL
mdefine_line|#define IMBL 0x01&t;&t;/* Incoming Mailbox Loaded */
DECL|macro|INTRMASK
mdefine_line|#define INTRMASK 0x8F&t;&t;/* 0x70 are reserved */
multiline_comment|/* WRITE */
DECL|macro|CONTROL
mdefine_line|#define CONTROL(base) STATUS(base)
DECL|macro|RHARD
mdefine_line|#define RHARD 0x80&t;&t;/* Hard Reset */
DECL|macro|RSOFT
mdefine_line|#define RSOFT 0x40&t;&t;/* Soft Reset */
DECL|macro|RINT
mdefine_line|#define RINT 0x20&t;&t;/* Interrupt Reset */
DECL|macro|RSBUS
mdefine_line|#define RSBUS 0x10&t;&t;/* SCSI Bus Reset */
DECL|macro|COMMAND_PARAMETER
mdefine_line|#define COMMAND_PARAMETER(base) (STATUS(base) + 1)
DECL|macro|CMD_TSTCMDCINT
mdefine_line|#define CMD_TSTCMDCINT 0x00&t;/* Test CMDC Interrupt */
DECL|macro|CMD_INITMB
mdefine_line|#define CMD_INITMB 0x01&t;&t;/* Initialize Mailbox */
DECL|macro|CMD_START_SCSI
mdefine_line|#define CMD_START_SCSI 0x02&t;/* Start Mailbox */
DECL|macro|CMD_START_BIOS
mdefine_line|#define CMD_START_BIOS 0x03&t;/* Start BIOS */
DECL|macro|CMD_INQUIRY
mdefine_line|#define CMD_INQUIRY 0x04&t;/* Inquire Board ID */
DECL|macro|CMD_ENBOMBRINT
mdefine_line|#define CMD_ENBOMBRINT 0x05&t;/* Enable OMBR Interrupt */
DECL|macro|CMD_SETSELTIMOUT
mdefine_line|#define CMD_SETSELTIMOUT 0x06&t;/* Set SCSI Selection Time-Out */
DECL|macro|CMD_BUSON_TIME
mdefine_line|#define CMD_BUSON_TIME 0x07&t;/* Set Bus-On Time */
DECL|macro|CMD_BUSOFF_TIME
mdefine_line|#define CMD_BUSOFF_TIME 0x08&t;/* Set Bus-Off Time */
DECL|macro|CMD_BUSXFR_RATE
mdefine_line|#define CMD_BUSXFR_RATE 0x09&t;/* Set Bus Transfer Rate */
DECL|macro|CMD_INQ_DEVICES
mdefine_line|#define CMD_INQ_DEVICES 0x0A&t;/* Inquire Installed Devices */
DECL|macro|CMD_RETCONF
mdefine_line|#define CMD_RETCONF 0x0B&t;/* Return Configuration */
DECL|macro|CMD_TARGET_MODE
mdefine_line|#define CMD_TARGET_MODE 0x0C&t;/* Set Target Mode */
DECL|macro|CMD_INQ_SETUP_INFO
mdefine_line|#define CMD_INQ_SETUP_INFO 0x0D&t;/* Inquire Set-up Information */
DECL|macro|CMD_WRITE_LCL_RAM
mdefine_line|#define CMD_WRITE_LCL_RAM 0x1A&t;/* Write Adapter Local RAM */
DECL|macro|CMD_READ_LCL_RAM
mdefine_line|#define CMD_READ_LCL_RAM 0x1B&t;/* Read Adapter Local RAM */
DECL|macro|CMD_WRITE_BM_FIFO
mdefine_line|#define CMD_WRITE_BM_FIFO 0x1C&t;/* Write Bus Master Chip FIFO */
DECL|macro|CMD_READ_BM_FIFO
mdefine_line|#define CMD_READ_BM_FIFO 0x1D&t;/* Read Bus Master Chip FIFO */
DECL|macro|CMD_ECHO
mdefine_line|#define CMD_ECHO 0x1F&t;&t;/* Echo Data Byte */
DECL|macro|CMD_HA_DIAG
mdefine_line|#define CMD_HA_DIAG 0x20&t;/* Host Adapter Diagnostic */
DECL|macro|CMD_HA_OPTIONS
mdefine_line|#define CMD_HA_OPTIONS 0x21&t;/* Host Adapter Options */
DECL|macro|CMD_INITEXTMB
mdefine_line|#define CMD_INITEXTMB 0x81&t;/* Initialize Extended Mailbox */
DECL|macro|CMD_INQEXTSETUP
mdefine_line|#define CMD_INQEXTSETUP 0x8D&t;/* Inquire Extended Set-up Information */
DECL|macro|CMD_WRITE_INQ_BUF
mdefine_line|#define CMD_WRITE_INQ_BUF 0x9A&t;/* Write Inquery Data Buffer&n;&t;&t;&t;&t;   (Target Mode Only) */
DECL|macro|CMD_READ_INQ_BUF
mdefine_line|#define CMD_READ_INQ_BUF 0x9B&t;/* Read Inquery Data Buffer&n;&t;&t;&t;&t;   (Target Mode Only) */
DECL|macro|MBX_NOT_IN_USE
mdefine_line|#define MBX_NOT_IN_USE 0x00
DECL|macro|MBX_ACTION_START
mdefine_line|#define MBX_ACTION_START 0x01
DECL|macro|MBX_ACTION_ABORT
mdefine_line|#define MBX_ACTION_ABORT 0x02
DECL|macro|MBX_COMPLETION_OK
mdefine_line|#define MBX_COMPLETION_OK 0x01
DECL|macro|MBX_COMPLETION_ABORTED
mdefine_line|#define MBX_COMPLETION_ABORTED 0x02
DECL|macro|MBX_COMPLETION_NOT_FOUND
mdefine_line|#define MBX_COMPLETION_NOT_FOUND 0x03
DECL|macro|MBX_COMPLETION_ERROR
mdefine_line|#define MBX_COMPLETION_ERROR 0x04
multiline_comment|/* Mailbox Definition */
DECL|struct|mailbox
r_struct
id|mailbox
(brace
DECL|member|ccbptr
r_void
op_star
id|ccbptr
suffix:semicolon
multiline_comment|/* lsb, ..., msb */
DECL|member|btstat
r_int
r_char
id|btstat
suffix:semicolon
DECL|member|sdstat
r_int
r_char
id|sdstat
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* Command/Status */
)brace
suffix:semicolon
multiline_comment|/* This is used with scatter-gather */
DECL|struct|chain
r_struct
id|chain
(brace
DECL|member|datalen
r_int
r_int
id|datalen
suffix:semicolon
multiline_comment|/* Size of this part of chain */
DECL|member|dataptr
r_void
op_star
id|dataptr
suffix:semicolon
multiline_comment|/* Location of data */
)brace
suffix:semicolon
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|struct|ccb
r_struct
id|ccb
(brace
multiline_comment|/* Command Control Block */
DECL|member|op
r_int
r_char
id|op
suffix:semicolon
multiline_comment|/* Command Control Block Operation Code */
DECL|member|dir
r_int
r_char
id|dir
suffix:semicolon
DECL|member|cdblen
r_int
r_char
id|cdblen
suffix:semicolon
multiline_comment|/* SCSI Command Length */
DECL|member|rsalen
r_int
r_char
id|rsalen
suffix:semicolon
multiline_comment|/* Request Sense Allocation Length/Disable */
DECL|member|datalen
r_int
r_int
id|datalen
suffix:semicolon
multiline_comment|/* Data Length (msb, ..., lsb) */
DECL|member|dataptr
r_void
op_star
id|dataptr
suffix:semicolon
multiline_comment|/* Data Pointer */
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hastat
r_int
r_char
id|hastat
suffix:semicolon
multiline_comment|/* Host Adapter Status (HASTAT) */
DECL|member|tarstat
r_int
r_char
id|tarstat
suffix:semicolon
multiline_comment|/* Target Device Status */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|lun
r_int
r_char
id|lun
suffix:semicolon
DECL|member|cdb
r_int
r_char
id|cdb
(braket
id|MAX_CDB
)braket
suffix:semicolon
DECL|member|ccbcontrol
r_int
r_char
id|ccbcontrol
suffix:semicolon
DECL|member|commlinkid
r_int
r_char
id|commlinkid
suffix:semicolon
multiline_comment|/* Command Linking Identifier */
DECL|member|linkptr
r_void
op_star
id|linkptr
suffix:semicolon
multiline_comment|/* Link Pointer */
DECL|member|senseptr
r_void
op_star
id|senseptr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CCB_OP_INIT
mdefine_line|#define CCB_OP_INIT 0x00&t;/* Initiator CCB */
DECL|macro|CCB_OP_TARG
mdefine_line|#define CCB_OP_TARG 0x01&t;/* Target CCB */
DECL|macro|CCB_OP_INIT_SG
mdefine_line|#define CCB_OP_INIT_SG 0x02&t;/* Initiator CCB with scatter-gather */
DECL|macro|CCB_OP_INIT_R
mdefine_line|#define CCB_OP_INIT_R 0x03&t;/* Initiator CCB with residual data length&n;&t;&t;&t;&t;   returned */
DECL|macro|CCB_OP_INIT_SG_R
mdefine_line|#define CCB_OP_INIT_SG_R 0x04&t;/* Initiator CCB with scatter-gather and&n;&t;&t;&t;&t;   residual data length returned */
DECL|macro|CCB_OP_BUS_RESET
mdefine_line|#define CCB_OP_BUS_RESET 0x81&t;/* SCSI bus device reset */
macro_line|#endif
macro_line|#endif
eof
