multiline_comment|/*&n; *&t;eata.h - used by the low-level driver for EATA/DMA SCSI host adapters.&n; */
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
mdefine_line|#define EATA_VERSION &quot;3.11.00&quot;
DECL|macro|EATA
mdefine_line|#define EATA {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;name:              &quot;EATA/DMA 2.0x rev. &quot; EATA_VERSION &quot; &quot;,      &bslash;&n;&t;&t;detect:            eata2x_detect,&t;&t;&t;&t;&bslash;&n;&t;&t;release:           eata2x_release,          &t;&t;        &bslash;&n;&t;&t;queuecommand:      eata2x_queuecommand,&t;&t;&t;        &bslash;&n;&t;&t;abort:             eata2x_abort,&t;&t;&t;&t;&bslash;&n;&t;&t;reset:             eata2x_reset,&t;&t;&t;&t;&bslash;&n;&t;&t;bios_param:        scsicam_bios_param,   &t;&t;&t;&bslash;&n;&t;&t;this_id:           7,   /* this_id, reset by detect */          &bslash;&n;&t;&t;unchecked_isa_dma: 1,   /* unchecked isa dma, reset by detect */&bslash;&n;&t;&t;use_clustering:    ENABLE_CLUSTERING                            &bslash;&n;&t;&t;}
macro_line|#endif
eof
