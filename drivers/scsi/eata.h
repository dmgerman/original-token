multiline_comment|/*&n; *        eata.h - used by the low-level driver for EATA/DMA SCSI host adapters.&n; */
macro_line|#ifndef _EATA_H
DECL|macro|_EATA_H
mdefine_line|#define _EATA_H
macro_line|#include &lt;scsi/scsicam.h&gt;
r_int
id|eata2x_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|eata2x_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|eata2x_queuecommand
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
id|eata2x_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata2x_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|EATA_VERSION
mdefine_line|#define EATA_VERSION &quot;4.02.00&quot;
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#if LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,1,88)
DECL|macro|EATA
mdefine_line|#define EATA {                                                               &bslash;&n;                name:              &quot;EATA/DMA 2.0x rev. &quot; EATA_VERSION &quot; &quot;,   &bslash;&n;                detect:            eata2x_detect,                            &bslash;&n;                release:           eata2x_release,                           &bslash;&n;                queuecommand:      eata2x_queuecommand,                      &bslash;&n;                abort:             eata2x_abort,                             &bslash;&n;                reset:             eata2x_reset,                             &bslash;&n;                bios_param:        scsicam_bios_param,                       &bslash;&n;                this_id:           7,                                        &bslash;&n;                unchecked_isa_dma: 1,                                        &bslash;&n;                use_clustering:    ENABLE_CLUSTERING,                        &bslash;&n;                use_new_eh_code: 1    /* Enable new error code */            &bslash;&n;             }
macro_line|#else /* Use old scsi code */
DECL|macro|EATA
mdefine_line|#define EATA {                                                               &bslash;&n;                name:              &quot;EATA/DMA 2.0x rev. &quot; EATA_VERSION &quot; &quot;,   &bslash;&n;                detect:            eata2x_detect,                            &bslash;&n;                release:           eata2x_release,                           &bslash;&n;                queuecommand:      eata2x_queuecommand,                      &bslash;&n;                abort:             eata2x_abort,                             &bslash;&n;                reset:             eata2x_reset,                             &bslash;&n;                bios_param:        scsicam_bios_param,                       &bslash;&n;                this_id:           7,                                        &bslash;&n;                unchecked_isa_dma: 1,                                        &bslash;&n;                use_clustering:    ENABLE_CLUSTERING                         &bslash;&n;             }
macro_line|#endif
macro_line|#endif
eof
