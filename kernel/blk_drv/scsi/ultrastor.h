multiline_comment|/*&n; *&t;ultrastor.c&t;(C) 1991 David B. Gentzel&n; *&t;Low-level scsi driver for UltraStor 14F&n; *&t;by David B. Gentzel, Whitfield Software Services, Carnegie, PA&n; *&t;    (gentzel@nova.enet.dec.com)&n; *&t;Thanks to UltraStor for providing the necessary documentation&n; */
macro_line|#ifndef _ULTRASTOR_H
DECL|macro|_ULTRASTOR_H
mdefine_line|#define _ULTRASTOR_H
multiline_comment|/* ??? These don&squot;t really belong here */
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE 0
macro_line|#endif
multiline_comment|/* ??? This should go eventually, once I&squot;m convinced the queueing stuff is&n;   stable enough... */
multiline_comment|/* #define NO_QUEUEING */
r_int
id|ultrastor_14f_detect
c_func
(paren
r_int
)paren
suffix:semicolon
r_const
r_char
op_star
id|ultrastor_14f_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ultrastor_14f_queuecommand
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
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_int
comma
r_int
)paren
)paren
suffix:semicolon
macro_line|#ifdef NO_QUEUEING
r_int
id|ultrastor_14f_command
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
macro_line|#endif
r_int
id|ultrastor_14f_abort
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|ultrastor_14f_reset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef NO_QUEUEING
DECL|macro|ULTRASTOR_14F
mdefine_line|#define ULTRASTOR_14F &bslash;&n;    { &quot;UltraStor 14F&quot;, ultrastor_14f_detect, ultrastor_14f_info, 0, &bslash;&n;      ultrastor_14f_queuecommand, ultrastor_14f_abort, ultrastor_14f_reset, &bslash;&n;      1, 0, 0 }
multiline_comment|/* ??? What should can_queue be set to?  Currently 1... */
macro_line|#else
DECL|macro|ULTRASTOR_14F
mdefine_line|#define ULTRASTOR_14F &bslash;&n;    { &quot;UltraStor 14F&quot;, ultrastor_14f_detect, ultrastor_14f_info, &bslash;&n;      ultrastor_14f_command, 0, ultrastor_14f_abort, ultrastor_14f_reset, &bslash;&n;      0, 0, 0 }
macro_line|#endif
DECL|macro|UD_ABORT
mdefine_line|#define UD_ABORT 0x0001
DECL|macro|UD_COMMAND
mdefine_line|#define UD_COMMAND 0x0002
DECL|macro|UD_DETECT
mdefine_line|#define UD_DETECT 0x0004
DECL|macro|UD_INTERRUPT
mdefine_line|#define UD_INTERRUPT 0x0008
DECL|macro|UD_RESET
mdefine_line|#define UD_RESET 0x0010
macro_line|#ifdef ULTRASTOR_PRIVATE
multiline_comment|/* #define PORT_OVERRIDE 0x330 */
multiline_comment|/* Port addresses (relative to the base address) */
DECL|macro|LCL_DOORBELL_MASK
mdefine_line|#define LCL_DOORBELL_MASK(port) ((port) + 0x0)
DECL|macro|LCL_DOORBELL_INTR
mdefine_line|#define LCL_DOORBELL_INTR(port) ((port) + 0x1)
DECL|macro|SYS_DOORBELL_MASK
mdefine_line|#define SYS_DOORBELL_MASK(port) ((port) + 0x2)
DECL|macro|SYS_DOORBELL_INTR
mdefine_line|#define SYS_DOORBELL_INTR(port) ((port) + 0x3)
DECL|macro|PRODUCT_ID
mdefine_line|#define PRODUCT_ID(port) ((port) + 0x4)
DECL|macro|CONFIG
mdefine_line|#define CONFIG(port) ((port) + 0x6)
DECL|macro|OGM_DATA_PTR
mdefine_line|#define OGM_DATA_PTR(port) ((port) + 0x8)
DECL|macro|ICM_DATA_PTR
mdefine_line|#define ICM_DATA_PTR(port) ((port) + 0xC)
multiline_comment|/* Values for the PRODUCT_ID ports for the 14F */
DECL|macro|US14F_PRODUCT_ID_0
mdefine_line|#define US14F_PRODUCT_ID_0 0x56
DECL|macro|US14F_PRODUCT_ID_1
mdefine_line|#define US14F_PRODUCT_ID_1 0x40&t;&t;/* NOTE: Only upper nibble is used */
multiline_comment|/* MSCP field values */
multiline_comment|/* Opcode */
DECL|macro|OP_HOST_ADAPTER
mdefine_line|#define OP_HOST_ADAPTER 0x1
DECL|macro|OP_SCSI
mdefine_line|#define OP_SCSI 0x2
DECL|macro|OP_RESET
mdefine_line|#define OP_RESET 0x4
multiline_comment|/* Date Transfer Direction */
DECL|macro|DTD_SCSI
mdefine_line|#define DTD_SCSI 0x0
DECL|macro|DTD_IN
mdefine_line|#define DTD_IN 0x1
DECL|macro|DTD_OUT
mdefine_line|#define DTD_OUT 0x2
DECL|macro|DTD_NONE
mdefine_line|#define DTD_NONE 0x3
multiline_comment|/* Host Adapter command subcodes */
DECL|macro|HA_CMD_INQUIRY
mdefine_line|#define HA_CMD_INQUIRY 0x1
DECL|macro|HA_CMD_SELF_DIAG
mdefine_line|#define HA_CMD_SELF_DIAG 0x2
DECL|macro|HA_CMD_READ_BUFF
mdefine_line|#define HA_CMD_READ_BUFF 0x3
DECL|macro|HA_CMD_WRITE_BUFF
mdefine_line|#define HA_CMD_WRITE_BUFF 0x4
macro_line|#endif
macro_line|#endif
eof
