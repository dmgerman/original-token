multiline_comment|/*&n; * DTC controller, taken from T128 driver by...&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 1. &n; *&n; * For more information, please consult &n; *&n; * &n; * &n; * and &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
macro_line|#ifndef DTC3280_H
DECL|macro|DTC3280_H
mdefine_line|#define DTC3280_H
DECL|macro|DTC_PUBLIC_RELEASE
mdefine_line|#define DTC_PUBLIC_RELEASE 1
multiline_comment|/*#define DTCDEBUG 0x1*/
DECL|macro|DTCDEBUG_INIT
mdefine_line|#define DTCDEBUG_INIT&t;0x1
DECL|macro|DTCDEBUG_TRANSFER
mdefine_line|#define DTCDEBUG_TRANSFER 0x2
multiline_comment|/*&n; * The DTC3180 &amp; 3280 boards are memory mapped.&n; * &n; */
multiline_comment|/*&n; */
multiline_comment|/* Offset from DTC_5380_OFFSET */
DECL|macro|DTC_CONTROL_REG
mdefine_line|#define DTC_CONTROL_REG&t;&t;0x100&t;/* rw */
DECL|macro|D_CR_ACCESS
mdefine_line|#define D_CR_ACCESS&t;&t;0x80&t;/* ro set=can access 3280 registers */
DECL|macro|CSR_DIR_READ
mdefine_line|#define CSR_DIR_READ&t;&t;0x40&t;/* rw direction, 1 = read 0 = write */
DECL|macro|CSR_RESET
mdefine_line|#define CSR_RESET              0x80    /* wo  Resets 53c400 */
DECL|macro|CSR_5380_REG
mdefine_line|#define CSR_5380_REG           0x80    /* ro  5380 registers can be accessed */
DECL|macro|CSR_TRANS_DIR
mdefine_line|#define CSR_TRANS_DIR          0x40    /* rw  Data transfer direction */
DECL|macro|CSR_SCSI_BUFF_INTR
mdefine_line|#define CSR_SCSI_BUFF_INTR     0x20    /* rw  Enable int on transfer ready */
DECL|macro|CSR_5380_INTR
mdefine_line|#define CSR_5380_INTR          0x10    /* rw  Enable 5380 interrupts */
DECL|macro|CSR_SHARED_INTR
mdefine_line|#define CSR_SHARED_INTR        0x08    /* rw  Interrupt sharing */
DECL|macro|CSR_HOST_BUF_NOT_RDY
mdefine_line|#define CSR_HOST_BUF_NOT_RDY   0x04    /* ro  Host buffer not ready */
DECL|macro|CSR_SCSI_BUF_RDY
mdefine_line|#define CSR_SCSI_BUF_RDY       0x02    /* ro  SCSI buffer ready */
DECL|macro|CSR_GATED_5380_IRQ
mdefine_line|#define CSR_GATED_5380_IRQ     0x01    /* ro  Last block xferred */
DECL|macro|CSR_INT_BASE
mdefine_line|#define CSR_INT_BASE (CSR_SCSI_BUFF_INTR | CSR_5380_INTR)
DECL|macro|DTC_BLK_CNT
mdefine_line|#define DTC_BLK_CNT&t;&t;0x101   /* rw &n;&t;&t;&t;&t;&t; * # of 128-byte blocks to transfer */
DECL|macro|D_CR_ACCESS
mdefine_line|#define D_CR_ACCESS             0x80    /* ro set=can access 3280 registers */
DECL|macro|DTC_SWITCH_REG
mdefine_line|#define DTC_SWITCH_REG&t;&t;0x3982&t;/* ro - DIP switches */
DECL|macro|DTC_RESUME_XFER
mdefine_line|#define DTC_RESUME_XFER&t;&t;0x3982&t;/* wo - resume data xfer &n;&t;&t;&t;&t;&t;   * after disconnect/reconnect*/
DECL|macro|DTC_5380_OFFSET
mdefine_line|#define DTC_5380_OFFSET&t;&t;0x3880&t;/* 8 registers here, see NCR5380.h */
multiline_comment|/*!!!! for dtc, it&squot;s a 128 byte buffer at 3900 !!! */
DECL|macro|DTC_DATA_BUF
mdefine_line|#define DTC_DATA_BUF&t;&t;0x3900  /* rw 128 bytes long */
macro_line|#ifndef ASM
r_int
id|dtc_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|dtc_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|dtc_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|dtc_queue_command
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
id|dtc_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|dtc_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
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
mdefine_line|#define CAN_QUEUE 32 
macro_line|#endif
multiline_comment|/* &n; * I hadn&squot;t thought of this with the earlier drivers - but to prevent&n; * macro definition conflicts, we shouldn&squot;t define all of the internal&n; * macros when this is being used solely for the host stub.&n; */
macro_line|#if defined(HOSTS_C) || defined(MODULE)
DECL|macro|DTC3x80
mdefine_line|#define DTC3x80 {NULL, NULL, NULL, NULL, &bslash;&n;&t;&quot;DTC 3180/3280 &quot;, dtc_detect, NULL,  &bslash;&n;&t;NULL,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;NULL, dtc_queue_command, dtc_abort, dtc_reset, NULL, &t;&bslash;&n;&t;dtc_biosparam, &t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* can queue */ CAN_QUEUE, /* id */ 7, SG_ALL,&t;&t;&t;&bslash;&n;&t;/* cmd per lun */ CMD_PER_LUN , 0, 0, DISABLE_CLUSTERING}
macro_line|#endif
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    volatile unsigned char *base
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    volatile unsigned char *base
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    base = (volatile unsigned char *) (instance)-&gt;base
DECL|macro|DTC_address
mdefine_line|#define DTC_address(reg) (base + DTC_5380_OFFSET + reg)
DECL|macro|dbNCR5380_read
mdefine_line|#define dbNCR5380_read(reg)                                              &bslash;&n;    (rval=*(DTC_address(reg)), &bslash;&n;     (((unsigned char) printk(&quot;DTC : read register %d at addr %08x is: %02x&bslash;n&quot;&bslash;&n;    , (reg), (int)DTC_address(reg), rval)), rval ) )
DECL|macro|dbNCR5380_write
mdefine_line|#define dbNCR5380_write(reg, value) do {                                  &bslash;&n;    printk(&quot;DTC : write %02x to register %d at address %08x&bslash;n&quot;,         &bslash;&n;            (value), (reg), (int)DTC_address(reg));     &bslash;&n;    *(DTC_address(reg)) = (value);} while(0)
macro_line|#if !(DTCDEBUG &amp; DTCDEBUG_TRANSFER) 
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (*(DTC_address(reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) (*(DTC_address(reg)) = (value))
macro_line|#else
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (*(DTC_address(reg)))
DECL|macro|xNCR5380_read
mdefine_line|#define xNCR5380_read(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;    (((unsigned char) printk(&quot;DTC : read register %d at address %08x&bslash;n&quot;&bslash;&n;    , (reg), DTC_address(reg))), *(DTC_address(reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) do {&t;&t;&t;&t;&t;&bslash;&n;    printk(&quot;DTC : write %02x to register %d at address %08x&bslash;n&quot;, &t;&bslash;&n;&t;    (value), (reg), (int)DTC_address(reg));&t;&bslash;&n;    *(DTC_address(reg)) = (value);&t;&t;} while(0)
macro_line|#endif
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr dtc_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command dtc_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort dtc_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset dtc_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info dtc_proc_info 
multiline_comment|/* 15 12 11 10&n;   1001 1100 0000 0000 */
DECL|macro|DTC_IRQS
mdefine_line|#define DTC_IRQS 0x9c00
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* DTC3280_H */
eof
