macro_line|#ifndef _AHA152X_H
DECL|macro|_AHA152X_H
mdefine_line|#define _AHA152X_H
multiline_comment|/*&n; * $Id: aha152x.h,v 1.15 1996/04/30 14:59:35 fischer Exp $&n; */
macro_line|#if defined(__KERNEL__)
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;asm/io.h&gt;
r_int
id|aha152x_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|aha152x_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_queue
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
id|aha152x_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|aha152x_biosparam
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
id|aha152x_proc_info
c_func
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
multiline_comment|/* number of queueable commands&n;   (unless we support more than 1 cmd_per_lun this should do) */
DECL|macro|AHA152X_MAXQUEUE
mdefine_line|#define AHA152X_MAXQUEUE&t;7&t;&t;
DECL|macro|AHA152X_REVID
mdefine_line|#define AHA152X_REVID &quot;Adaptec 152x SCSI driver; $Revision: 1.15 $&quot;
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_aha152x
suffix:semicolon
multiline_comment|/* Initial value of Scsi_Host entry */
DECL|macro|AHA152X
mdefine_line|#define AHA152X       { /* next */&t;&t;NULL,&t;&t;&t;    &bslash;&n;&t;&t;&t;/* usage_count */  &t;NULL,&t;&t;&t;    &bslash;&n;&t;&t;&t;/* proc_dir */&t;&t;&amp;proc_scsi_aha152x,         &bslash;&n;&t;&t;&t;/* proc_info */&t;&t;aha152x_proc_info,          &bslash;&n;&t;&t;&t;/* name */&t;&t;AHA152X_REVID, &t;&t;    &bslash;&n;&t;&t;&t;/* detect */&t;&t;aha152x_detect,             &bslash;&n;&t;&t;&t;/* release */&t;&t;NULL,&t;&t;&t;    &bslash;&n;&t;&t;&t;/* info */&t;&t;NULL,&t;&t;&t;    &bslash;&n;&t;&t;&t;/* command */&t;&t;aha152x_command,            &bslash;&n;&t;&t;&t;/* queuecommand */&t;aha152x_queue,              &bslash;&n;&t;&t;&t;/* abort */&t;&t;aha152x_abort,              &bslash;&n;&t;&t;&t;/* reset */&t;&t;aha152x_reset,              &bslash;&n;&t;&t;&t;/* slave_attach */&t;/* NULL */  0,              &bslash;&n;&t;&t;&t;/* bios_param */&t;aha152x_biosparam,          &bslash;&n;&t;&t;&t;/* can_queue */&t;&t;1,                          &bslash;&n;&t;&t;&t;/* this_id */&t;&t;7,                          &bslash;&n;&t;&t;&t;/* sg_tablesize */&t;SG_ALL,                     &bslash;&n;&t;&t;&t;/* cmd_per_lun */&t;1,                          &bslash;&n;&t;&t;&t;/* present */&t;&t;0,                          &bslash;&n;&t;&t;&t;/* unchecked_isa_dma */&t;0,&t;&t;&t;    &bslash;&n;&t;&t;&t;/* use_clustering */&t;DISABLE_CLUSTERING }
macro_line|#endif
multiline_comment|/* port addresses */
DECL|macro|SCSISEQ
mdefine_line|#define SCSISEQ&t;&t;(shpnt-&gt;io_port+0x00)&t;/* SCSI sequence control */
DECL|macro|SXFRCTL0
mdefine_line|#define SXFRCTL0&t;(shpnt-&gt;io_port+0x01)&t;/* SCSI transfer control 0 */
DECL|macro|SXFRCTL1
mdefine_line|#define SXFRCTL1&t;(shpnt-&gt;io_port+0x02)&t;/* SCSI transfer control 1 */
DECL|macro|SCSISIG
mdefine_line|#define SCSISIG&t;&t;(shpnt-&gt;io_port+0x03)&t;/* SCSI signal in/out */
DECL|macro|SCSIRATE
mdefine_line|#define SCSIRATE&t;(shpnt-&gt;io_port+0x04)&t;/* SCSI rate control */
DECL|macro|SELID
mdefine_line|#define SELID&t;&t;(shpnt-&gt;io_port+0x05)&t;/* selection/reselection ID */
DECL|macro|SCSIID
mdefine_line|#define SCSIID&t;&t;SELID&t;&t;&t;/* SCSI ID */
DECL|macro|SCSIDAT
mdefine_line|#define SCSIDAT&t;&t;(shpnt-&gt;io_port+0x06)&t;/* SCSI latched data */
DECL|macro|SCSIBUS
mdefine_line|#define SCSIBUS&t;&t;(shpnt-&gt;io_port+0x07)&t;/* SCSI data bus */
DECL|macro|STCNT0
mdefine_line|#define STCNT0&t;&t;(shpnt-&gt;io_port+0x08)&t;/* SCSI transfer count 0 */
DECL|macro|STCNT1
mdefine_line|#define STCNT1&t;&t;(shpnt-&gt;io_port+0x09)&t;/* SCSI transfer count 1 */
DECL|macro|STCNT2
mdefine_line|#define STCNT2&t;&t;(shpnt-&gt;io_port+0x0a)&t;/* SCSI transfer count 2 */
DECL|macro|SSTAT0
mdefine_line|#define SSTAT0&t;&t;(shpnt-&gt;io_port+0x0b)&t;/* SCSI interrupt status 0 */
DECL|macro|SSTAT1
mdefine_line|#define SSTAT1&t;&t;(shpnt-&gt;io_port+0x0c)&t;/* SCSI interrupt status 1 */
DECL|macro|SSTAT2
mdefine_line|#define SSTAT2&t;&t;(shpnt-&gt;io_port+0x0d)&t;/* SCSI interrupt status 2 */
DECL|macro|SCSITEST
mdefine_line|#define SCSITEST&t;(shpnt-&gt;io_port+0x0e)&t;/* SCSI test control */
DECL|macro|SSTAT3
mdefine_line|#define SSTAT3&t;&t;SCSITEST                /* SCSI interrupt status 3 */
DECL|macro|SSTAT4
mdefine_line|#define SSTAT4&t;&t;(shpnt-&gt;io_port+0x0f)&t;/* SCSI status 4 */
DECL|macro|SIMODE0
mdefine_line|#define SIMODE0&t;&t;(shpnt-&gt;io_port+0x10)&t;/* SCSI interrupt mode 0 */
DECL|macro|SIMODE1
mdefine_line|#define SIMODE1&t;&t;(shpnt-&gt;io_port+0x11)&t;/* SCSI interrupt mode 1 */
DECL|macro|DMACNTRL0
mdefine_line|#define DMACNTRL0&t;(shpnt-&gt;io_port+0x12)&t;/* DMA control 0 */
DECL|macro|DMACNTRL1
mdefine_line|#define DMACNTRL1&t;(shpnt-&gt;io_port+0x13)&t;/* DMA control 1 */
DECL|macro|DMASTAT
mdefine_line|#define DMASTAT&t;&t;(shpnt-&gt;io_port+0x14)&t;/* DMA status */
DECL|macro|FIFOSTAT
mdefine_line|#define FIFOSTAT&t;(shpnt-&gt;io_port+0x15)&t;/* FIFO status */
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT&t;(shpnt-&gt;io_port+0x16)&t;/* DATA port */
DECL|macro|BRSTCNTRL
mdefine_line|#define BRSTCNTRL&t;(shpnt-&gt;io_port+0x18)&t;/* burst control */
DECL|macro|PORTA
mdefine_line|#define PORTA&t;&t;(shpnt-&gt;io_port+0x1a)&t;/* PORT A */
DECL|macro|PORTB
mdefine_line|#define PORTB&t;&t;(shpnt-&gt;io_port+0x1b)&t;/* PORT B */
DECL|macro|REV
mdefine_line|#define REV&t;&t;(shpnt-&gt;io_port+0x1c)&t;/* revision */
DECL|macro|STACK
mdefine_line|#define STACK&t;&t;(shpnt-&gt;io_port+0x1d)&t;/* stack */
DECL|macro|TEST
mdefine_line|#define TEST&t;&t;(shpnt-&gt;io_port+0x1e)&t;/* test register */
multiline_comment|/* used in aha152x_porttest */
DECL|macro|O_PORTA
mdefine_line|#define O_PORTA&t;&t;(0x1a)                  /* PORT A */
DECL|macro|O_PORTB
mdefine_line|#define O_PORTB&t;&t;(0x1b)                  /* PORT B */
DECL|macro|O_DMACNTRL1
mdefine_line|#define O_DMACNTRL1&t;(0x13)                  /* DMA control 1 */
DECL|macro|O_STACK
mdefine_line|#define O_STACK         (0x1d)                  /* stack */
DECL|macro|IO_RANGE
mdefine_line|#define IO_RANGE&t;0x20
multiline_comment|/* bits and bitmasks to ports */
multiline_comment|/* SCSI sequence control */
DECL|macro|TEMODEO
mdefine_line|#define&t;TEMODEO&t;&t;0x80
DECL|macro|ENSELO
mdefine_line|#define ENSELO&t;&t;0x40
DECL|macro|ENSELI
mdefine_line|#define ENSELI&t;&t;0x20
DECL|macro|ENRESELI
mdefine_line|#define ENRESELI&t;0x10
DECL|macro|ENAUTOATNO
mdefine_line|#define ENAUTOATNO&t;0x08
DECL|macro|ENAUTOATNI
mdefine_line|#define ENAUTOATNI&t;0x04
DECL|macro|ENAUTOATNP
mdefine_line|#define ENAUTOATNP&t;0x02
DECL|macro|SCSIRSTO
mdefine_line|#define SCSIRSTO&t;0x01
multiline_comment|/* SCSI transfer control 0 */
DECL|macro|SCSIEN
mdefine_line|#define&t;SCSIEN&t;&t;0x80
DECL|macro|DMAEN
mdefine_line|#define DMAEN&t;&t;0x40
DECL|macro|CH1
mdefine_line|#define CH1&t;&t;0x20
DECL|macro|CLRSTCNT
mdefine_line|#define CLRSTCNT&t;0x10
DECL|macro|SPIOEN
mdefine_line|#define SPIOEN&t;&t;0x08
DECL|macro|CLRCH1
mdefine_line|#define CLRCH1&t;&t;0x02
multiline_comment|/* SCSI transfer control 1 */
DECL|macro|BITBUCKET
mdefine_line|#define&t;BITBUCKET&t;0x80
DECL|macro|SWRAPEN
mdefine_line|#define SWRAPEN&t;&t;0x40
DECL|macro|ENSPCHK
mdefine_line|#define ENSPCHK&t;&t;0x20
DECL|macro|STIMESEL
mdefine_line|#define&t;STIMESEL&t;0x18&t;/* mask */
DECL|macro|STIMESEL_
mdefine_line|#define STIMESEL_&t;3
DECL|macro|ENSTIMER
mdefine_line|#define ENSTIMER&t;0x04
DECL|macro|BYTEALIGN
mdefine_line|#define BYTEALIGN&t;0x02
multiline_comment|/* SCSI signal IN */
DECL|macro|CDI
mdefine_line|#define&t;CDI&t;&t;0x80
DECL|macro|IOI
mdefine_line|#define IOI&t;&t;0x40
DECL|macro|MSGI
mdefine_line|#define MSGI&t;&t;0x20
DECL|macro|ATNI
mdefine_line|#define ATNI&t;&t;0x10
DECL|macro|SELI
mdefine_line|#define SELI&t;&t;0x08
DECL|macro|BSYI
mdefine_line|#define BSYI&t;&t;0x04
DECL|macro|REQI
mdefine_line|#define REQI&t;&t;0x02
DECL|macro|ACKI
mdefine_line|#define ACKI&t;&t;0x01
multiline_comment|/* SCSI Phases */
DECL|macro|P_MASK
mdefine_line|#define P_MASK&t;&t;(MSGI|CDI|IOI)
DECL|macro|P_DATAO
mdefine_line|#define P_DATAO&t;&t;(0)
DECL|macro|P_DATAI
mdefine_line|#define P_DATAI&t;&t;(IOI)
DECL|macro|P_CMD
mdefine_line|#define&t;P_CMD&t;&t;(CDI)
DECL|macro|P_STATUS
mdefine_line|#define P_STATUS&t;(CDI|IOI)
DECL|macro|P_MSGO
mdefine_line|#define P_MSGO&t;&t;(MSGI|CDI)
DECL|macro|P_MSGI
mdefine_line|#define P_MSGI&t;&t;(MSGI|CDI|IOI)
multiline_comment|/* SCSI signal OUT */
DECL|macro|CDO
mdefine_line|#define&t;CDO&t;&t;0x80
DECL|macro|IOO
mdefine_line|#define IOO&t;&t;0x40
DECL|macro|MSGO
mdefine_line|#define MSGO&t;&t;0x20
DECL|macro|ATNO
mdefine_line|#define ATNO&t;&t;0x10
DECL|macro|SELO
mdefine_line|#define SELO&t;&t;0x08
DECL|macro|BSYO
mdefine_line|#define BSYO&t;&t;0x04
DECL|macro|REQO
mdefine_line|#define REQO&t;&t;0x02
DECL|macro|ACKO
mdefine_line|#define ACKO&t;&t;0x01
multiline_comment|/* SCSI rate control */
DECL|macro|SXFR
mdefine_line|#define SXFR&t;&t;0x70&t;/* mask */
DECL|macro|SXFR_
mdefine_line|#define SXFR_&t;&t;4
DECL|macro|SOFS
mdefine_line|#define SOFS&t;&t;0x0f&t;/* mask */
multiline_comment|/* SCSI ID */
DECL|macro|OID
mdefine_line|#define&t;OID&t;&t;0x70
DECL|macro|OID_
mdefine_line|#define OID_&t;&t;4
DECL|macro|TID
mdefine_line|#define TID&t;&t;0x07
multiline_comment|/* SCSI transfer count */
DECL|macro|GETSTCNT
mdefine_line|#define GETSTCNT()   ( (GETPORT(STCNT2)&lt;&lt;16) &bslash;&n;&t;&t;     + (GETPORT(STCNT1)&lt;&lt; 8) &bslash;&n;&t;&t;     + GETPORT(STCNT0) )
DECL|macro|SETSTCNT
mdefine_line|#define SETSTCNT(X)  { SETPORT(STCNT2, ((X) &amp; 0xFF0000) &gt;&gt; 16); &bslash;&n;&t;&t;       SETPORT(STCNT1, ((X) &amp; 0x00FF00) &gt;&gt;  8); &bslash;&n;&t;&t;       SETPORT(STCNT0, ((X) &amp; 0x0000FF) ); }
multiline_comment|/* SCSI interrupt status */
DECL|macro|TARGET
mdefine_line|#define&t;TARGET&t;&t;0x80
DECL|macro|SELDO
mdefine_line|#define SELDO&t;&t;0x40
DECL|macro|SELDI
mdefine_line|#define&t;SELDI&t;&t;0x20
DECL|macro|SELINGO
mdefine_line|#define SELINGO&t;&t;0x10
DECL|macro|SWRAP
mdefine_line|#define SWRAP&t;&t;0x08
DECL|macro|SDONE
mdefine_line|#define&t;SDONE&t;&t;0x04
DECL|macro|SPIORDY
mdefine_line|#define SPIORDY&t;&t;0x02
DECL|macro|DMADONE
mdefine_line|#define DMADONE&t;&t;0x01
DECL|macro|SETSDONE
mdefine_line|#define SETSDONE&t;0x80
DECL|macro|CLRSELDO
mdefine_line|#define CLRSELDO&t;0x40
DECL|macro|CLRSELDI
mdefine_line|#define CLRSELDI&t;0x20
DECL|macro|CLRSELINGO
mdefine_line|#define CLRSELINGO&t;0x10
DECL|macro|CLRSWRAP
mdefine_line|#define CLRSWRAP&t;0x08
DECL|macro|CLRSDONE
mdefine_line|#define CLRSDONE&t;0x04
DECL|macro|CLRSPIORDY
mdefine_line|#define CLRSPIORDY&t;0x02
DECL|macro|CLRDMADONE
mdefine_line|#define CLRDMADONE&t;0x01
multiline_comment|/* SCSI status 1 */
DECL|macro|SELTO
mdefine_line|#define SELTO&t;&t;0x80
DECL|macro|ATNTARG
mdefine_line|#define ATNTARG&t;&t;0x40
DECL|macro|SCSIRSTI
mdefine_line|#define SCSIRSTI&t;0x20
DECL|macro|PHASEMIS
mdefine_line|#define PHASEMIS&t;0x10
DECL|macro|BUSFREE
mdefine_line|#define BUSFREE&t;&t;0x08
DECL|macro|SCSIPERR
mdefine_line|#define SCSIPERR&t;0x04
DECL|macro|PHASECHG
mdefine_line|#define PHASECHG&t;0x02
DECL|macro|REQINIT
mdefine_line|#define&t;REQINIT&t;&t;0x01
DECL|macro|CLRSELTIMO
mdefine_line|#define CLRSELTIMO&t;0x80
DECL|macro|CLRATNO
mdefine_line|#define CLRATNO&t;&t;0x40
DECL|macro|CLRSCSIRSTI
mdefine_line|#define CLRSCSIRSTI&t;0x20
DECL|macro|CLRBUSFREE
mdefine_line|#define CLRBUSFREE&t;0x08
DECL|macro|CLRSCSIPERR
mdefine_line|#define&t;CLRSCSIPERR&t;0x04
DECL|macro|CLRPHASECHG
mdefine_line|#define CLRPHASECHG&t;0x02
DECL|macro|CLRREQINIT
mdefine_line|#define CLRREQINIT&t;0x01
multiline_comment|/* SCSI status 2 */
DECL|macro|SOFFSET
mdefine_line|#define SOFFSET&t;&t;0x20
DECL|macro|SEMPTY
mdefine_line|#define SEMPTY&t;&t;0x10
DECL|macro|SFULL
mdefine_line|#define&t;SFULL&t;&t;0x08
DECL|macro|SFCNT
mdefine_line|#define&t;SFCNT&t;&t;0x07&t;/* mask */
multiline_comment|/* SCSI status 3 */
DECL|macro|SCSICNT
mdefine_line|#define&t;SCSICNT&t;&t;0xf0&t;/* mask */
DECL|macro|SCSICNT_
mdefine_line|#define&t;SCSICNT_&t;4
DECL|macro|OFFCNT
mdefine_line|#define OFFCNT&t;&t;0x0f&t;/* mask */
multiline_comment|/* SCSI TEST control */
DECL|macro|SCTESTU
mdefine_line|#define&t;SCTESTU&t;&t;0x08
DECL|macro|SCTESTD
mdefine_line|#define&t;SCTESTD&t;&t;0x04
DECL|macro|STCTEST
mdefine_line|#define STCTEST&t;&t;0x01
multiline_comment|/* SCSI status 4 */
DECL|macro|SYNCERR
mdefine_line|#define&t;SYNCERR&t;&t;0x04
DECL|macro|FWERR
mdefine_line|#define FWERR&t;&t;0x02
DECL|macro|FRERR
mdefine_line|#define FRERR&t;&t;0x01
DECL|macro|CLRSYNCERR
mdefine_line|#define&t;CLRSYNCERR&t;0x04
DECL|macro|CLRFWERR
mdefine_line|#define CLRFWERR&t;0x02
DECL|macro|CLRFRERR
mdefine_line|#define&t;CLRFRERR&t;0x01
multiline_comment|/* SCSI interrupt mode 0 */
DECL|macro|ENSELDO
mdefine_line|#define ENSELDO&t;&t;0x40
DECL|macro|ENSELDI
mdefine_line|#define ENSELDI&t;&t;0x20
DECL|macro|ENSELINGO
mdefine_line|#define ENSELINGO&t;0x10
DECL|macro|ENSWRAP
mdefine_line|#define ENSWRAP&t;&t;0x08
DECL|macro|ENSDONE
mdefine_line|#define ENSDONE&t;&t;0x04
DECL|macro|ENSPIORDY
mdefine_line|#define ENSPIORDY&t;0x02
DECL|macro|ENDMADONE
mdefine_line|#define ENDMADONE&t;0x01
multiline_comment|/* SCSI interrupt mode 1 */
DECL|macro|ENSELTIMO
mdefine_line|#define&t;ENSELTIMO&t;0x80
DECL|macro|ENATNTARG
mdefine_line|#define ENATNTARG&t;0x40
DECL|macro|ENSCSIRST
mdefine_line|#define ENSCSIRST&t;0x20
DECL|macro|ENPHASEMIS
mdefine_line|#define ENPHASEMIS&t;0x10
DECL|macro|ENBUSFREE
mdefine_line|#define ENBUSFREE&t;0x08
DECL|macro|ENSCSIPERR
mdefine_line|#define ENSCSIPERR&t;0x04
DECL|macro|ENPHASECHG
mdefine_line|#define ENPHASECHG&t;0x02
DECL|macro|ENREQINIT
mdefine_line|#define ENREQINIT&t;0x01
multiline_comment|/* DMA control 0 */
DECL|macro|ENDMA
mdefine_line|#define ENDMA&t;&t;0x80
DECL|macro|_8BIT
mdefine_line|#define _8BIT&t;&t;0x40
DECL|macro|DMA
mdefine_line|#define&t;DMA&t;&t;0x20
DECL|macro|WRITE_READ
mdefine_line|#define&t;WRITE_READ&t;0x08
DECL|macro|INTEN
mdefine_line|#define&t;INTEN&t;&t;0x04
DECL|macro|RSTFIFO
mdefine_line|#define RSTFIFO&t;&t;0x02
DECL|macro|SWINT
mdefine_line|#define SWINT&t;&t;0x01
multiline_comment|/* DMA control 1 */
DECL|macro|PWRDWN
mdefine_line|#define PWRDWN&t;&t;0x80
DECL|macro|STK
mdefine_line|#define STK&t;&t;0x07&t;/* mask */
multiline_comment|/* DMA status */
DECL|macro|ATDONE
mdefine_line|#define ATDONE&t;&t;0x80
DECL|macro|WORDRDY
mdefine_line|#define WORDRDY&t;&t;0x40
DECL|macro|INTSTAT
mdefine_line|#define INTSTAT&t;&t;0x20
DECL|macro|DFIFOFULL
mdefine_line|#define DFIFOFULL&t;0x10
DECL|macro|DFIFOEMP
mdefine_line|#define DFIFOEMP&t;0x08
multiline_comment|/* BURST control */
DECL|macro|BON
mdefine_line|#define BON&t;&t;0xf0
DECL|macro|BOFF
mdefine_line|#define BOFF&t;&t;0x0f
multiline_comment|/* TEST REGISTER */
DECL|macro|BOFFTMR
mdefine_line|#define&t;BOFFTMR&t;&t;0x40
DECL|macro|BONTMR
mdefine_line|#define BONTMR&t;&t;0x20
DECL|macro|STCNTH
mdefine_line|#define STCNTH&t;&t;0x10
DECL|macro|STCNTM
mdefine_line|#define STCNTM&t;&t;0x08
DECL|macro|STCNTL
mdefine_line|#define STCNTL&t;&t;0x04
DECL|macro|SCSIBLK
mdefine_line|#define SCSIBLK&t;&t;0x02
DECL|macro|DMABLK
mdefine_line|#define DMABLK&t;&t;0x01
multiline_comment|/* On the AHA-152x board PORTA and PORTB contain&n;   some information about the board&squot;s configuration. */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|tardisc
r_int
id|tardisc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Target disconnect: 0=disabled, 1=enabled */
DECL|member|syncneg
r_int
id|syncneg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Initial sync neg: 0=disabled, 1=enabled */
DECL|member|msgclasses
r_int
id|msgclasses
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Message classes&n;&t;&t;&t;&t;   0=#4&n;&t;&t;&t;&t;   1=#0, #1, #2, #3, #4&n;&t;&t;&t;&t;   2=#0, #3, #4&n;&t;&t;&t;&t;   3=#0, #4&n;&t;&t;&t;&t;*/
DECL|member|boot
r_int
id|boot
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* boot: 0=disabled, 1=enabled */
DECL|member|dma
r_int
id|dma
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transfer mode: 0=PIO; 1=DMA */
DECL|member|id
r_int
id|id
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* SCSI-id */
DECL|member|irq
r_int
id|irq
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* IRQ-Channel: 0,3=12, 1=10, 2=11 */
DECL|member|dmachan
r_int
id|dmachan
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DMA-Channel: 0=0, 1=5, 2=6, 3=7 */
DECL|member|parity
r_int
id|parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SCSI-parity: 1=enabled 0=disabled */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|typedef|aha152x_config
)brace
id|aha152x_config
suffix:semicolon
DECL|macro|cf_parity
mdefine_line|#define cf_parity&t;fields.parity
DECL|macro|cf_dmachan
mdefine_line|#define cf_dmachan&t;fields.dmachan
DECL|macro|cf_irq
mdefine_line|#define cf_irq&t;&t;fields.irq
DECL|macro|cf_id
mdefine_line|#define cf_id&t;&t;fields.id
DECL|macro|cf_dma
mdefine_line|#define cf_dma&t;&t;fields.dma
DECL|macro|cf_boot
mdefine_line|#define cf_boot&t;&t;fields.boot
DECL|macro|cf_msgclasses
mdefine_line|#define&t;cf_msgclasses&t;fields.msgclasses
DECL|macro|cf_syncneg
mdefine_line|#define cf_syncneg&t;fields.syncneg
DECL|macro|cf_tardisc
mdefine_line|#define cf_tardisc&t;fields.tardisc
DECL|macro|cf_port
mdefine_line|#define cf_port&t;&t;port
multiline_comment|/* Some macros to manipulate ports and their bits */
DECL|macro|SETPORT
mdefine_line|#define SETPORT(PORT, VAL)&t;&bslash;&n;&t;outb( (VAL), (PORT) )
DECL|macro|SETPORTP
mdefine_line|#define SETPORTP(PORT, VAL)&t;&bslash;&n;&t;outb_p( (VAL), (PORT) )
DECL|macro|SETPORTW
mdefine_line|#define SETPORTW(PORT, VAL)&t;&bslash;&n;&t;outw( (VAL), (PORT) )
DECL|macro|GETPORT
mdefine_line|#define GETPORT(PORT)&t;&bslash;&n;&t;inb( PORT )
DECL|macro|GETPORTW
mdefine_line|#define GETPORTW(PORT)&t;&bslash;&n;&t;inw( PORT )
DECL|macro|SETBITS
mdefine_line|#define SETBITS(PORT, BITS)&t;&bslash;&n;&t;outb( (inb(PORT) | (BITS)), (PORT) )
DECL|macro|CLRBITS
mdefine_line|#define CLRBITS(PORT, BITS)&t;&bslash;&n;&t;outb( (inb(PORT) &amp; ~(BITS)), (PORT) )
DECL|macro|CLRSETBITS
mdefine_line|#define CLRSETBITS(PORT, CLR, SET)&t;&bslash;&n;&t;outb( (inb(PORT) &amp; ~(CLR)) | (SET) , (PORT) )
DECL|macro|TESTHI
mdefine_line|#define TESTHI(PORT, BITS)&t;&bslash;&n;&t;((inb(PORT) &amp; (BITS)) == BITS)
DECL|macro|TESTLO
mdefine_line|#define TESTLO(PORT, BITS)&t;&bslash;&n;&t;((inb(PORT) &amp; (BITS)) == 0)
macro_line|#ifdef DEBUG_AHA152X
r_enum
(brace
DECL|enumerator|debug_skipports
id|debug_skipports
op_assign
l_int|0x0001
comma
DECL|enumerator|debug_queue
id|debug_queue
op_assign
l_int|0x0002
comma
DECL|enumerator|debug_intr
id|debug_intr
op_assign
l_int|0x0004
comma
DECL|enumerator|debug_selection
id|debug_selection
op_assign
l_int|0x0008
comma
DECL|enumerator|debug_msgo
id|debug_msgo
op_assign
l_int|0x0010
comma
DECL|enumerator|debug_msgi
id|debug_msgi
op_assign
l_int|0x0020
comma
DECL|enumerator|debug_status
id|debug_status
op_assign
l_int|0x0040
comma
DECL|enumerator|debug_cmd
id|debug_cmd
op_assign
l_int|0x0080
comma
DECL|enumerator|debug_datai
id|debug_datai
op_assign
l_int|0x0100
comma
DECL|enumerator|debug_datao
id|debug_datao
op_assign
l_int|0x0200
comma
DECL|enumerator|debug_abort
id|debug_abort
op_assign
l_int|0x0400
comma
DECL|enumerator|debug_done
id|debug_done
op_assign
l_int|0x0800
comma
DECL|enumerator|debug_biosparam
id|debug_biosparam
op_assign
l_int|0x1000
comma
DECL|enumerator|debug_phases
id|debug_phases
op_assign
l_int|0x2000
comma
DECL|enumerator|debug_queues
id|debug_queues
op_assign
l_int|0x4000
comma
DECL|enumerator|debug_reset
id|debug_reset
op_assign
l_int|0x8000
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _AHA152X_H */
eof
