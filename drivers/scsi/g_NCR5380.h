multiline_comment|/*&n; * Generic Generic NCR5380 driver defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * ALPHA RELEASE 1. &n; *&n; * For more information, please consult &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: generic_NCR5380.h,v $&n; */
macro_line|#ifndef GENERIC_NCR5380_H
DECL|macro|GENERIC_NCR5380_H
mdefine_line|#define GENERIC_NCR5380_H
DECL|macro|GENERIC_NCR5380_PUBLIC_RELEASE
mdefine_line|#define GENERIC_NCR5380_PUBLIC_RELEASE 1
macro_line|#ifndef ASM
r_int
id|generic_NCR5380_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|generic_NCR5380_detect
c_func
(paren
r_int
)paren
suffix:semicolon
r_const
r_char
op_star
id|generic_NCR5380_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|generic_NCR5380_queue_command
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
id|generic_NCR5380_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 16
macro_line|#endif
macro_line|#ifdef HOSTS_C
DECL|macro|GENERIC_NCR5380
mdefine_line|#define GENERIC_NCR5380 {&quot;Trantor T128/T128F/T228&quot;, &t;&t;&t;&bslash;&n;&t;generic_NCR5380_detect, generic_NCR5380_info, NULL, &t;&t;&bslash;&n;&t;generic_NCR5380_queue_command, generic_NCR5380_abort, &t;&t;&bslash;&n;&t;generic_NCR5380_reset, NULL, &t;&t;&t;&t;&t;&bslash;&n;&t;NULL, /* can queue */ CAN_QUEUE, /* id */ 7, SG_ALL,&t;&t;&bslash;&n;&t;/* cmd per lun */ CMD_PER_LUN , 0, 0, DISABLE_CLUSTERING}
macro_line|#else
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    register int port
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    port = (instance)-&gt;io_port
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (inb(port + (reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) (outb((value), (port + (reg))))
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr generic_NCR5380_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command generic_NCR5380_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort generic_NCR5380_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset generic_NCR5380_reset
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* GENERIC_NCR5380_H */
eof
