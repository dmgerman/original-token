multiline_comment|/********************************************************&n;* Header file for eata_pio.c Linux EATA-PIO SCSI driver *&n;* (c) 1993,94,95 Michael Neuffer                        *&n;*********************************************************&n;* last change: 95/06/21                                 *&n;********************************************************/
macro_line|#ifndef _EATA_PIO_H
DECL|macro|_EATA_PIO_H
mdefine_line|#define _EATA_PIO_H
macro_line|#include &quot;../block/blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;linux/scsicam.h&gt;
macro_line|#ifndef HOSTS_C
macro_line|#include &quot;eata_generic.h&quot;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 0
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 0
DECL|macro|VER_SUB
mdefine_line|#define VER_SUB   &quot;1a&quot;
multiline_comment|/************************************************************************&n; * Here you can switch parts of the code on and of                      *&n; ************************************************************************/
DECL|macro|VERBOSE_SETUP
mdefine_line|#define VERBOSE_SETUP                   /* show startup screen of 2001 */
DECL|macro|ALLOW_DMA_BOARDS
mdefine_line|#define ALLOW_DMA_BOARDS 1
multiline_comment|/************************************************************************&n; * Debug options.                                                       * &n; * Enable DEBUG and whichever options you require.                      *&n; ************************************************************************/
DECL|macro|DEBUG_EATA
mdefine_line|#define DEBUG_EATA      1   /* Enable debug code.                       */
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG       0   /* Bobs special                             */
DECL|macro|DBG_DELAY
mdefine_line|#define DBG_DELAY       0   /* Build in delays so debug messages can be&n;&t;&t;&t;     * be read before they vanish of the top of&n;&t;&t;&t;     * the screen!&n;&t;&t;&t;     */
DECL|macro|DBG_PROBE
mdefine_line|#define DBG_PROBE       0   /* Debug probe routines.                    */
DECL|macro|DBG_ISA
mdefine_line|#define DBG_ISA         0   /* Trace ISA routines                       */ 
DECL|macro|DBG_EISA
mdefine_line|#define DBG_EISA        0   /* Trace EISA routines                      */ 
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI         0   /* Trace PCI routines                       */ 
DECL|macro|DBG_PIO
mdefine_line|#define DBG_PIO         0   /* Trace get_config_PIO                     */
DECL|macro|DBG_COM
mdefine_line|#define DBG_COM         0   /* Trace command call                       */
DECL|macro|DBG_QUEUE
mdefine_line|#define DBG_QUEUE       0   /* Trace command queueing.                  */
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR        0   /* Trace interrupt service routine.         */
DECL|macro|DBG_INTR2
mdefine_line|#define DBG_INTR2       0   /* Trace interrupt service routine.         */
DECL|macro|DBG_PROC
mdefine_line|#define DBG_PROC        0   /* Debug proc-fs related statistics         */
DECL|macro|DBG_PROC_WRITE
mdefine_line|#define DBG_PROC_WRITE  0
DECL|macro|DBG_REGISTER
mdefine_line|#define DBG_REGISTER    0   /* */
DECL|macro|DBG_ABNORM
mdefine_line|#define DBG_ABNORM      1   /* Debug abnormal actions (reset, abort)    */
macro_line|#if DEBUG_EATA 
DECL|macro|DBG
mdefine_line|#define DBG(x, y)   if ((x)) {y;} 
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x, y)
macro_line|#endif
macro_line|#endif /* !HOSTS_C */
r_int
id|eata_pio_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|eata_pio_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_queue
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
id|eata_pio_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_pio_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|eata_pio_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|eata_pio_release
mdefine_line|#define eata_pio_release NULL  
macro_line|#endif
r_extern
r_int
id|generic_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|EATA_PIO
mdefine_line|#define EATA_PIO {                   &bslash;&n;&t;NULL, NULL,                  &bslash;&n;&t;eata_pio_proc_info,/* procinfo       */  &bslash;&n;&t;&quot;eata_pio&quot;,        /* proc dir entry */  &bslash;&n;&t;PROC_SCSI_EATA_PIO,/* proc dir inode */  &bslash;&n;&t; &quot;EATA (Extended Attachment) PIO driver&quot;,&bslash;&n;&t;eata_pio_detect,             &bslash;&n;&t;eata_pio_release,            &bslash;&n;&t;NULL, NULL,                  &bslash;&n;&t;eata_pio_queue,              &bslash;&n;&t;eata_pio_abort,              &bslash;&n;&t;eata_pio_reset,              &bslash;&n;&t;NULL,   /* Slave attach */   &bslash;&n;&t;scsicam_bios_param,          &bslash;&n;&t;0,      /* Canqueue     */   &bslash;&n;&t;0,      /* this_id      */   &bslash;&n;&t;0,      /* sg_tablesize */   &bslash;&n;&t;0,      /* cmd_per_lun  */   &bslash;&n;&t;0,      /* present      */   &bslash;&n;&t;1,      /* True if ISA  */   &bslash;&n;&t;ENABLE_CLUSTERING }
macro_line|#endif /* _EATA_PIO_H */
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 4&n; * End:&n; */
eof
