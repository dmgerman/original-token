multiline_comment|/*+M*************************************************************************&n; * Adaptec AIC7xxx register and scratch ram definitions.&n; *&n; * Copyright (c) 1994, 1995, 1996 Justin T. Gibbs.&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Id: aic7xxx_reg.h,v 1.2 1996/02/10 06:23:39 deang Exp $&n; *-M*************************************************************************/
multiline_comment|/*&n; * This header is shared by the sequencer code and the kernel level driver.&n; *&n; * All page numbers refer to the Adaptec AIC-7770 Data Book availible from&n; * Adaptec&squot;s Technical Documents Department 1-800-934-2766&n; */
multiline_comment|/*&n; * SCSI Sequence Control (p. 3-11).&n; * Each bit, when set starts a specific SCSI sequence on the bus&n; */
DECL|macro|SCSISEQ
mdefine_line|#define SCSISEQ&t;&t;&t;0x000
DECL|macro|TEMODEO
mdefine_line|#define&t;&t;TEMODEO&t;&t;0x80
DECL|macro|ENSELO
mdefine_line|#define&t;&t;ENSELO&t;&t;0x40
DECL|macro|ENSELI
mdefine_line|#define&t;&t;ENSELI&t;&t;0x20
DECL|macro|ENRSELI
mdefine_line|#define&t;&t;ENRSELI&t;&t;0x10
DECL|macro|ENAUTOATNO
mdefine_line|#define&t;&t;ENAUTOATNO&t;0x08
DECL|macro|ENAUTOATNI
mdefine_line|#define&t;&t;ENAUTOATNI&t;0x04
DECL|macro|ENAUTOATNP
mdefine_line|#define&t;&t;ENAUTOATNP&t;0x02
DECL|macro|SCSIRSTO
mdefine_line|#define&t;&t;SCSIRSTO&t;0x01
multiline_comment|/*&n; * SCSI Transfer Control 0 Register (pp. 3-13).&n; * Controls the SCSI module data path.&n; */
DECL|macro|SXFRCTL0
mdefine_line|#define&t;SXFRCTL0&t;&t;0x001
DECL|macro|DFON
mdefine_line|#define&t;&t;DFON&t;&t;0x80
DECL|macro|DFPEXP
mdefine_line|#define&t;&t;DFPEXP&t;&t;0x40
DECL|macro|ULTRAEN
mdefine_line|#define&t;&t;ULTRAEN&t;&t;0x20
DECL|macro|CLRSTCNT
mdefine_line|#define&t;&t;CLRSTCNT&t;0x10
DECL|macro|SPIOEN
mdefine_line|#define&t;&t;SPIOEN&t;&t;0x08
DECL|macro|SCAMEN
mdefine_line|#define&t;&t;SCAMEN&t;&t;0x04
DECL|macro|CLRCHN
mdefine_line|#define&t;&t;CLRCHN&t;&t;0x02
multiline_comment|/*  UNUSED&t;&t;&t;0x01 */
multiline_comment|/*&n; * SCSI Transfer Control 1 Register (pp. 3-14,15).&n; * Controls the SCSI module data path.&n; */
DECL|macro|SXFRCTL1
mdefine_line|#define&t;SXFRCTL1&t;&t;0x002
DECL|macro|BITBUCKET
mdefine_line|#define&t;&t;BITBUCKET&t;0x80
DECL|macro|SWRAPEN
mdefine_line|#define&t;&t;SWRAPEN&t;&t;0x40
DECL|macro|ENSPCHK
mdefine_line|#define&t;&t;ENSPCHK&t;&t;0x20
DECL|macro|STIMESEL
mdefine_line|#define&t;&t;STIMESEL&t;0x18
DECL|macro|ENSTIMER
mdefine_line|#define&t;&t;ENSTIMER&t;0x04
DECL|macro|ACTNEGEN
mdefine_line|#define&t;&t;ACTNEGEN&t;0x02
DECL|macro|STPWEN
mdefine_line|#define&t;&t;STPWEN&t;&t;0x01&t;/* Powered Termination */
multiline_comment|/*&n; * SCSI Control Signal Read Register (p. 3-15).&n; * Reads the actual state of the SCSI bus pins&n; */
DECL|macro|SCSISIGI
mdefine_line|#define SCSISIGI&t;&t;0x003
DECL|macro|CDI
mdefine_line|#define&t;&t;CDI&t;&t;0x80
DECL|macro|IOI
mdefine_line|#define&t;&t;IOI&t;&t;0x40
DECL|macro|MSGI
mdefine_line|#define&t;&t;MSGI&t;&t;0x20
DECL|macro|ATNI
mdefine_line|#define&t;&t;ATNI&t;&t;0x10
DECL|macro|SELI
mdefine_line|#define&t;&t;SELI&t;&t;0x08
DECL|macro|BSYI
mdefine_line|#define&t;&t;BSYI&t;&t;0x04
DECL|macro|REQI
mdefine_line|#define&t;&t;REQI&t;&t;0x02
DECL|macro|ACKI
mdefine_line|#define&t;&t;ACKI&t;&t;0x01
multiline_comment|/*&n; * Possible phases in SCSISIGI&n; */
DECL|macro|PHASE_MASK
mdefine_line|#define&t;&t;PHASE_MASK&t;0xe0
DECL|macro|P_DATAOUT
mdefine_line|#define&t;&t;P_DATAOUT&t;0x00
DECL|macro|P_DATAIN
mdefine_line|#define&t;&t;P_DATAIN&t;0x40
DECL|macro|P_COMMAND
mdefine_line|#define&t;&t;P_COMMAND&t;0x80
DECL|macro|P_MESGOUT
mdefine_line|#define&t;&t;P_MESGOUT&t;0xa0
DECL|macro|P_STATUS
mdefine_line|#define&t;&t;P_STATUS&t;0xc0
DECL|macro|P_MESGIN
mdefine_line|#define&t;&t;P_MESGIN&t;0xe0
multiline_comment|/*&n; * SCSI Contol Signal Write Register (p. 3-16).&n; * Writing to this register modifies the control signals on the bus.  Only&n; * those signals that are allowed in the current mode (Initiator/Target) are&n; * asserted.&n; */
DECL|macro|SCSISIGO
mdefine_line|#define SCSISIGO&t;&t;0x003
DECL|macro|CDO
mdefine_line|#define&t;&t;CDO&t;&t;0x80
DECL|macro|IOO
mdefine_line|#define&t;&t;IOO&t;&t;0x40
DECL|macro|MSGO
mdefine_line|#define&t;&t;MSGO&t;&t;0x20
DECL|macro|ATNO
mdefine_line|#define&t;&t;ATNO&t;&t;0x10
DECL|macro|SELO
mdefine_line|#define&t;&t;SELO&t;&t;0x08
DECL|macro|BSYO
mdefine_line|#define&t;&t;BSYO&t;&t;0x04
DECL|macro|REQO
mdefine_line|#define&t;&t;REQO&t;&t;0x02
DECL|macro|ACKO
mdefine_line|#define&t;&t;ACKO&t;&t;0x01
multiline_comment|/* &n; * SCSI Rate Control (p. 3-17).&n; * Contents of this register determine the Synchronous SCSI data transfer&n; * rate and the maximum synchronous Req/Ack offset.  An offset of 0 in the&n; * SOFS (3:0) bits disables synchronous data transfers.  Any offset value&n; * greater than 0 enables synchronous transfers.&n; */
DECL|macro|SCSIRATE
mdefine_line|#define SCSIRATE&t;&t;0x004
DECL|macro|WIDEXFER
mdefine_line|#define&t;&t;WIDEXFER&t;0x80&t;&t;/* Wide transfer control */
DECL|macro|SXFR
mdefine_line|#define&t;&t;SXFR&t;&t;0x70&t;&t;/* Sync transfer rate */
DECL|macro|SOFS
mdefine_line|#define&t;&t;SOFS&t;&t;0x0f&t;&t;/* Sync offset */
multiline_comment|/*&n; * SCSI ID (p. 3-18).&n; * Contains the ID of the board and the current target on the&n; * selected channel.&n; */
DECL|macro|SCSIID
mdefine_line|#define SCSIID&t;&t;&t;0x005
DECL|macro|TID
mdefine_line|#define&t;&t;TID&t;&t;0xf0&t;&t;/* Target ID mask */
DECL|macro|OID
mdefine_line|#define&t;&t;OID&t;&t;0x0f&t;&t;/* Our ID mask */
multiline_comment|/*&n; * SCSI Latched Data (p. 3-19).&n; * Read/Write latchs used to transfer data on the SCSI bus during&n; * Automatic or Manual PIO mode.  SCSIDATH can be used for the&n; * upper byte of a 16bit wide asyncronouse data phase transfer.&n; */
DECL|macro|SCSIDATL
mdefine_line|#define SCSIDATL&t;&t;0x006
DECL|macro|SCSIDATH
mdefine_line|#define SCSIDATH&t;&t;0x007
multiline_comment|/*&n; * SCSI Transfer Count (pp. 3-19,20)&n; * These registers count down the number of bytes transfered&n; * across the SCSI bus.  The counter is decremented only once&n; * the data has been safely transfered.  SDONE in SSTAT0 is&n; * set when STCNT goes to 0&n; */
DECL|macro|STCNT
mdefine_line|#define STCNT&t;&t;&t;0x008
DECL|macro|STCNT0
mdefine_line|#define STCNT0&t;&t;&t;0x008
DECL|macro|STCNT1
mdefine_line|#define STCNT1&t;&t;&t;0x009
DECL|macro|STCNT2
mdefine_line|#define STCNT2&t;&t;&t;0x00a
multiline_comment|/*&n; * Clear SCSI Interrupt 0 (p. 3-20)&n; * Writing a 1 to a bit clears the associated SCSI Interrupt in SSTAT0.&n; */
DECL|macro|CLRSINT0
mdefine_line|#define&t;CLRSINT0&t;&t;0x00b
DECL|macro|CLRSELDO
mdefine_line|#define&t;&t;CLRSELDO&t;0x40
DECL|macro|CLRSELDI
mdefine_line|#define&t;&t;CLRSELDI&t;0x20
DECL|macro|CLRSELINGO
mdefine_line|#define&t;&t;CLRSELINGO&t;0x10
DECL|macro|CLRSWRAP
mdefine_line|#define&t;&t;CLRSWRAP&t;0x08
multiline_comment|/*  UNUSED&t;&t;&t;0x04 */
DECL|macro|CLRSPIORDY
mdefine_line|#define&t;&t;CLRSPIORDY&t;0x02
multiline_comment|/*  UNUSED&t;&t;&t;0x01 */
multiline_comment|/*&n; * SCSI Status 0 (p. 3-21)&n; * Contains one set of SCSI Interrupt codes&n; * These are most likely of interest to the sequencer&n; */
DECL|macro|SSTAT0
mdefine_line|#define SSTAT0&t;&t;&t;0x00b
DECL|macro|TARGET
mdefine_line|#define&t;&t;TARGET&t;&t;0x80&t;&t;/* Board acting as target */
DECL|macro|SELDO
mdefine_line|#define&t;&t;SELDO&t;&t;0x40&t;&t;/* Selection Done */
DECL|macro|SELDI
mdefine_line|#define&t;&t;SELDI&t;&t;0x20&t;&t;/* Board has been selected */
DECL|macro|SELINGO
mdefine_line|#define&t;&t;SELINGO&t;&t;0x10&t;&t;/* Selection In Progress */
DECL|macro|SWRAP
mdefine_line|#define&t;&t;SWRAP&t;&t;0x08&t;&t;/* 24bit counter wrap */
DECL|macro|SDONE
mdefine_line|#define&t;&t;SDONE&t;&t;0x04&t;&t;/* STCNT = 0x000000 */
DECL|macro|SPIORDY
mdefine_line|#define&t;&t;SPIORDY&t;&t;0x02&t;&t;/* SCSI PIO Ready */
DECL|macro|DMADONE
mdefine_line|#define&t;&t;DMADONE&t;&t;0x01&t;&t;/* DMA transfer completed */
multiline_comment|/*&n; * Clear SCSI Interrupt 1 (p. 3-23)&n; * Writing a 1 to a bit clears the associated SCSI Interrupt in SSTAT1.&n; */
DECL|macro|CLRSINT1
mdefine_line|#define CLRSINT1&t;&t;0x00c
DECL|macro|CLRSELTIMEO
mdefine_line|#define&t;&t;CLRSELTIMEO&t;0x80
DECL|macro|CLRATNO
mdefine_line|#define&t;&t;CLRATNO&t;&t;0x40
DECL|macro|CLRSCSIRSTI
mdefine_line|#define&t;&t;CLRSCSIRSTI&t;0x20
multiline_comment|/*  UNUSED&t;&t;&t;0x10 */
DECL|macro|CLRBUSFREE
mdefine_line|#define&t;&t;CLRBUSFREE&t;0x08
DECL|macro|CLRSCSIPERR
mdefine_line|#define&t;&t;CLRSCSIPERR&t;0x04
DECL|macro|CLRPHASECHG
mdefine_line|#define&t;&t;CLRPHASECHG&t;0x02
DECL|macro|CLRREQINIT
mdefine_line|#define&t;&t;CLRREQINIT&t;0x01
multiline_comment|/*&n; * SCSI Status 1 (p. 3-24)&n; */
DECL|macro|SSTAT1
mdefine_line|#define SSTAT1&t;&t;&t;0x00c
DECL|macro|SELTO
mdefine_line|#define&t;&t;SELTO&t;&t;0x80
DECL|macro|ATNTARG
mdefine_line|#define&t;&t;ATNTARG &t;0x40
DECL|macro|SCSIRSTI
mdefine_line|#define&t;&t;SCSIRSTI&t;0x20
DECL|macro|PHASEMIS
mdefine_line|#define&t;&t;PHASEMIS&t;0x10
DECL|macro|BUSFREE
mdefine_line|#define&t;&t;BUSFREE&t;&t;0x08
DECL|macro|SCSIPERR
mdefine_line|#define&t;&t;SCSIPERR&t;0x04
DECL|macro|PHASECHG
mdefine_line|#define&t;&t;PHASECHG&t;0x02
DECL|macro|REQINIT
mdefine_line|#define&t;&t;REQINIT&t;&t;0x01
multiline_comment|/*&n; * SCSI Interrupt Mode 1 (pp. 3-28,29)&n; * Setting any bit will enable the corresponding function&n; * in SIMODE1 to interrupt via the IRQ pin.&n; */
DECL|macro|SIMODE1
mdefine_line|#define&t;SIMODE1&t;&t;&t;0x011
DECL|macro|ENSELTIMO
mdefine_line|#define&t;&t;ENSELTIMO&t;0x80
DECL|macro|ENATNTARG
mdefine_line|#define&t;&t;ENATNTARG&t;0x40
DECL|macro|ENSCSIRST
mdefine_line|#define&t;&t;ENSCSIRST&t;0x20
DECL|macro|ENPHASEMIS
mdefine_line|#define&t;&t;ENPHASEMIS&t;0x10
DECL|macro|ENBUSFREE
mdefine_line|#define&t;&t;ENBUSFREE&t;0x08
DECL|macro|ENSCSIPERR
mdefine_line|#define&t;&t;ENSCSIPERR&t;0x04
DECL|macro|ENPHASECHG
mdefine_line|#define&t;&t;ENPHASECHG&t;0x02
DECL|macro|ENREQINIT
mdefine_line|#define&t;&t;ENREQINIT&t;0x01
multiline_comment|/*&n; * SCSI Data Bus (High) (p. 3-29)&n; * This register reads data on the SCSI Data bus directly.&n; */
DECL|macro|SCSIBUSL
mdefine_line|#define&t;SCSIBUSL&t;&t;0x012
DECL|macro|SCSIBUSH
mdefine_line|#define&t;SCSIBUSH&t;&t;0x013
multiline_comment|/*&n; * SCSI/Host Address (p. 3-30)&n; * These registers hold the host address for the byte about to be&n; * transfered on the SCSI bus.  They are counted up in the same&n; * manner as STCNT is counted down.  SHADDR should always be used&n; * to determine the address of the last byte transfered since HADDR&n; * can be squewed by write ahead.&n; */
DECL|macro|SHADDR
mdefine_line|#define&t;SHADDR&t;&t;&t;0x014
DECL|macro|SHADDR0
mdefine_line|#define&t;SHADDR0&t;&t;&t;0x014
DECL|macro|SHADDR1
mdefine_line|#define&t;SHADDR1&t;&t;&t;0x015
DECL|macro|SHADDR2
mdefine_line|#define&t;SHADDR2&t;&t;&t;0x016
DECL|macro|SHADDR3
mdefine_line|#define&t;SHADDR3&t;&t;&t;0x017
multiline_comment|/*&n; * Selection/Reselection ID (p. 3-31)&n; * Upper four bits are the device id.  The ONEBIT is set when the re/selecting&n; * device did not set its own ID.&n; */
DECL|macro|SELID
mdefine_line|#define SELID&t;&t;&t;0x019
DECL|macro|SELID_MASK
mdefine_line|#define&t;&t;SELID_MASK&t;0xf0
DECL|macro|ONEBIT
mdefine_line|#define&t;&t;ONEBIT&t;&t;0x08
multiline_comment|/*  UNUSED&t;&t;&t;0x07 */
multiline_comment|/*&n; * SCSI Block Control (p. 3-32)&n; * Controls Bus type and channel selection.  In a twin channel configuration&n; * addresses 0x00-0x1e are gated to the appropriate channel based on this&n; * register.  SELWIDE allows for the coexistence of 8bit and 16bit devices&n; * on a wide bus.&n; */
DECL|macro|SBLKCTL
mdefine_line|#define SBLKCTL&t;&t;&t;0x01f
DECL|macro|DIAGLEDEN
mdefine_line|#define&t;&t;DIAGLEDEN&t;0x80&t;/* Aic78X0 only */
DECL|macro|DIAGLEDON
mdefine_line|#define&t;&t;DIAGLEDON&t;0x40&t;/* Aic78X0 only */
DECL|macro|AUTOFLUSHDIS
mdefine_line|#define&t;&t;AUTOFLUSHDIS&t;0x20
multiline_comment|/*  UNUSED&t;&t;&t;0x10 */
DECL|macro|SELBUS_MASK
mdefine_line|#define&t;&t;SELBUS_MASK&t;0x0a
DECL|macro|SELBUSB
mdefine_line|#define&t;&t;SELBUSB&t;&t;0x08
multiline_comment|/*  UNUSED&t;&t;&t;0x04 */
DECL|macro|SELWIDE
mdefine_line|#define&t;&t;SELWIDE&t;&t;0x02
multiline_comment|/*  UNUSED&t;&t;&t;0x01 */
DECL|macro|SELNARROW
mdefine_line|#define&t;&t;SELNARROW&t;0x00
multiline_comment|/*&n; * Sequencer Control (p. 3-33)&n; * Error detection mode and speed configuration&n; */
DECL|macro|SEQCTL
mdefine_line|#define SEQCTL&t;&t;&t;0x060
DECL|macro|PERRORDIS
mdefine_line|#define&t;&t;PERRORDIS&t;0x80
DECL|macro|PAUSEDIS
mdefine_line|#define&t;&t;PAUSEDIS&t;0x40
DECL|macro|FAILDIS
mdefine_line|#define&t;&t;FAILDIS&t;&t;0x20
DECL|macro|FASTMODE
mdefine_line|#define &t;FASTMODE&t;0x10
DECL|macro|BRKADRINTEN
mdefine_line|#define&t;&t;BRKADRINTEN&t;0x08
DECL|macro|STEP
mdefine_line|#define&t;&t;STEP&t;&t;0x04
DECL|macro|SEQRESET
mdefine_line|#define&t;&t;SEQRESET&t;0x02
DECL|macro|LOADRAM
mdefine_line|#define&t;&t;LOADRAM&t;&t;0x01
multiline_comment|/*&n; * Sequencer RAM Data (p. 3-34)&n; * Single byte window into the Scratch Ram area starting at the address&n; * specified by SEQADDR0 and SEQADDR1.  To write a full word, simply write&n; * four bytes in sucessesion.  The SEQADDRs will increment after the most&n; * significant byte is written&n; */
DECL|macro|SEQRAM
mdefine_line|#define SEQRAM&t;&t;&t;0x061
multiline_comment|/*&n; * Sequencer Address Registers (p. 3-35)&n; * Only the first bit of SEQADDR1 holds addressing information&n; */
DECL|macro|SEQADDR0
mdefine_line|#define SEQADDR0&t;&t;0x062
DECL|macro|SEQADDR1
mdefine_line|#define SEQADDR1&t;&t;0x063
DECL|macro|SEQADDR1_MASK
mdefine_line|#define &t;SEQADDR1_MASK&t;0x01
multiline_comment|/*&n; * Accumulator&n; * We cheat by passing arguments in the Accumulator up to the kernel driver&n; */
DECL|macro|ACCUM
mdefine_line|#define ACCUM&t;&t;&t;0x064
DECL|macro|SINDEX
mdefine_line|#define SINDEX&t;&t;&t;0x065
DECL|macro|DINDEX
mdefine_line|#define DINDEX&t;&t;&t;0x066
DECL|macro|ALLZEROS
mdefine_line|#define ALLZEROS&t;&t;0x06a
DECL|macro|NONE
mdefine_line|#define NONE&t;&t;&t;0x06a
DECL|macro|SINDIR
mdefine_line|#define SINDIR&t;&t;&t;0x06c
DECL|macro|DINDIR
mdefine_line|#define DINDIR&t;&t;&t;0x06d
DECL|macro|FUNCTION1
mdefine_line|#define FUNCTION1&t;&t;0x06e
multiline_comment|/*&n; * Host Address (p. 3-48)&n; * This register contains the address of the byte about&n; * to be transfered across the host bus.&n; */
DECL|macro|HADDR
mdefine_line|#define HADDR&t;&t;&t;0x088
DECL|macro|HADDR0
mdefine_line|#define HADDR0&t;&t;&t;0x088
DECL|macro|HADDR1
mdefine_line|#define HADDR1&t;&t;&t;0x089
DECL|macro|HADDR2
mdefine_line|#define HADDR2&t;&t;&t;0x08a
DECL|macro|HADDR3
mdefine_line|#define HADDR3&t;&t;&t;0x08b
DECL|macro|HCNT
mdefine_line|#define HCNT&t;&t;&t;0x08c
DECL|macro|HCNT0
mdefine_line|#define HCNT0&t;&t;&t;0x08c
DECL|macro|HCNT1
mdefine_line|#define HCNT1&t;&t;&t;0x08d
DECL|macro|HCNT2
mdefine_line|#define HCNT2&t;&t;&t;0x08e
multiline_comment|/*&n; * SCB Pointer (p. 3-49)&n; * Gate one of the four SCBs into the SCBARRAY window.&n; */
DECL|macro|SCBPTR
mdefine_line|#define SCBPTR&t;&t;&t;0x090
multiline_comment|/*&n; * Board Control (p. 3-43)&n; */
DECL|macro|BCTL
mdefine_line|#define BCTL&t;&t;&t;0x084
multiline_comment|/*   RSVD&t;&t;&t;0xf0 */
DECL|macro|ACE
mdefine_line|#define&t;&t;ACE&t;&t;0x08&t;/* Support for external processors */
multiline_comment|/*   RSVD&t;&t;&t;0x06 */
DECL|macro|ENABLE
mdefine_line|#define&t;&t;ENABLE&t;&t;0x01
multiline_comment|/*&n; * On the aic78X0 chips, Board Control is replaced by the DSCommand&n; * register (p. 4-64)&n; */
DECL|macro|DSCOMMAND
mdefine_line|#define&t;DSCOMMAND&t;&t;0x084
DECL|macro|CACHETHEN
mdefine_line|#define&t;&t;CACHETHEN&t;0x80&t;/* Cache Threshold enable */
DECL|macro|DPARCKEN
mdefine_line|#define&t;&t;DPARCKEN&t;0x40&t;/* Data Parity Check Enable */
DECL|macro|MPARCKEN
mdefine_line|#define&t;&t;MPARCKEN&t;0x20&t;/* Memory Parity Check Enable */
DECL|macro|EXTREQLCK
mdefine_line|#define&t;&t;EXTREQLCK&t;0x10&t;/* External Request Lock */
multiline_comment|/*&n; * Bus On/Off Time (p. 3-44)&n; */
DECL|macro|BUSTIME
mdefine_line|#define BUSTIME&t;&t;&t;0x085
DECL|macro|BOFF
mdefine_line|#define&t;&t;BOFF&t;&t;0xf0
DECL|macro|BON
mdefine_line|#define&t;&t;BON&t;&t;0x0f
DECL|macro|BOFF_60BCLKS
mdefine_line|#define&t;&t;BOFF_60BCLKS&t;0xf0
multiline_comment|/*&n; * Bus Speed (p. 3-45)&n; */
DECL|macro|BUSSPD
mdefine_line|#define&t;BUSSPD&t;&t;&t;0x086
DECL|macro|DFTHRSH
mdefine_line|#define&t;&t;DFTHRSH&t;&t;0xc0
DECL|macro|STBOFF
mdefine_line|#define&t;&t;STBOFF&t;&t;0x38
DECL|macro|STBON
mdefine_line|#define&t;&t;STBON&t;&t;0x07
DECL|macro|DFTHRSH_100
mdefine_line|#define&t;&t;DFTHRSH_100&t;0xc0
multiline_comment|/*&n; * Host Control (p. 3-47) R/W&n; * Overal host control of the device.&n; */
DECL|macro|HCNTRL
mdefine_line|#define HCNTRL&t;&t;&t;0x087
multiline_comment|/*    UNUSED&t;&t;&t;0x80 */
DECL|macro|POWRDN
mdefine_line|#define&t;&t;POWRDN&t;&t;0x40
multiline_comment|/*    UNUSED&t;&t;&t;0x20 */
DECL|macro|SWINT
mdefine_line|#define&t;&t;SWINT&t;&t;0x10
DECL|macro|IRQMS
mdefine_line|#define&t;&t;IRQMS&t;&t;0x08
DECL|macro|PAUSE
mdefine_line|#define&t;&t;PAUSE&t;&t;0x04
DECL|macro|INTEN
mdefine_line|#define&t;&t;INTEN&t;&t;0x02
DECL|macro|CHIPRST
mdefine_line|#define&t;&t;CHIPRST&t;&t;0x01
multiline_comment|/*&n; * Interrupt Status (p. 3-50)&n; * Status for system interrupts&n; */
DECL|macro|INTSTAT
mdefine_line|#define INTSTAT&t;&t;&t;0x091
DECL|macro|SEQINT_MASK
mdefine_line|#define&t;&t;SEQINT_MASK&t;0xf1&t;&t;/* SEQINT Status Codes */
DECL|macro|BAD_PHASE
mdefine_line|#define&t;&t;&t;BAD_PHASE&t;0x01&t;/* unknown scsi bus phase */
DECL|macro|SEND_REJECT
mdefine_line|#define&t;&t;&t;SEND_REJECT&t;0x11&t;/* sending a message reject */
DECL|macro|NO_IDENT
mdefine_line|#define&t;&t;&t;NO_IDENT&t;0x21&t;/* no IDENTIFY after reconnect*/
DECL|macro|NO_MATCH
mdefine_line|#define&t;&t;&t;NO_MATCH&t;0x31&t;/* no cmd match for reconnect */
DECL|macro|SDTR_MSG
mdefine_line|#define&t;&t;&t;SDTR_MSG&t;0x41&t;/* SDTR message recieved */
DECL|macro|WDTR_MSG
mdefine_line|#define&t;&t;&t;WDTR_MSG&t;0x51&t;/* WDTR message recieved */
DECL|macro|REJECT_MSG
mdefine_line|#define&t;&t;&t;REJECT_MSG&t;0x61&t;/* Reject message recieved */
DECL|macro|BAD_STATUS
mdefine_line|#define&t;&t;&t;BAD_STATUS&t;0x71&t;/* Bad status from target */
DECL|macro|RESIDUAL
mdefine_line|#define&t;&t;&t;RESIDUAL&t;0x81&t;/* Residual byte count != 0 */
DECL|macro|ABORT_TAG
mdefine_line|#define&t;&t;&t;ABORT_TAG&t;0x91&t;/* Sent an ABORT_TAG message */
DECL|macro|AWAITING_MSG
mdefine_line|#define&t;&t;&t;AWAITING_MSG&t;0xa1&t;/*&n;&t;&t;&t;&t;&t;&t; * Kernel requested to specify&n;                                                 * a message to this target&n;                                                 * (command was null), so tell&n;                                                 * it that it can fill the&n;                                                 * message buffer.&n;                                                 */
DECL|macro|IMMEDDONE
mdefine_line|#define&t;&t;&t;IMMEDDONE&t;0xb1&t;/*&n;&t;&t;&t;&t;&t;&t; * An immediate command has&n;&t;&t;&t;&t;&t;&t; * completed&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|MSG_BUFFER_BUSY
mdefine_line|#define&t;&t;&t;MSG_BUFFER_BUSY&t;0xc1&t;/*&n;&t;&t;&t;&t;&t;&t; * Sequencer wants to use the&n;&t;&t;&t;&t;&t;&t; * message buffer, but it&n;&t;&t;&t;&t;&t;&t; * already contains a message&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|MSGIN_PHASEMIS
mdefine_line|#define&t;&t;&t;MSGIN_PHASEMIS&t;0xd1&t;/*&n;&t;&t;&t;&t;&t;&t; * Target changed phase on us&n;&t;&t;&t;&t;&t;&t; * when we were expecting&n;&t;&t;&t;&t;&t;&t; * another msgin byte.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|PARITY_ERROR
mdefine_line|#define&t;&t;&t;PARITY_ERROR&t;0xe1&t;/*&n;&t;&t;&t;&t;&t;&t; * Sequencer detected a parity&n;&t;&t;&t;&t;&t;&t; * error.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|BRKADRINT
mdefine_line|#define &t;BRKADRINT 0x08
DECL|macro|SCSIINT
mdefine_line|#define&t;&t;SCSIINT&t;  0x04
DECL|macro|CMDCMPLT
mdefine_line|#define&t;&t;CMDCMPLT  0x02
DECL|macro|SEQINT
mdefine_line|#define&t;&t;SEQINT    0x01
DECL|macro|INT_PEND
mdefine_line|#define&t;&t;INT_PEND  (BRKADRINT | SEQINT | SCSIINT | CMDCMPLT)
multiline_comment|/*&n; * Hard Error (p. 3-53)&n; * Reporting of catastrophic errors.  You usually cannot recover from&n; * these without a full board reset.&n; */
DECL|macro|ERROR
mdefine_line|#define ERROR&t;&t;&t;0x092
multiline_comment|/*    UNUSED&t;&t;&t;0xf0 */
DECL|macro|PARERR
mdefine_line|#define&t;&t;PARERR&t;&t;0x08
DECL|macro|ILLOPCODE
mdefine_line|#define&t;&t;ILLOPCODE&t;0x04
DECL|macro|ILLSADDR
mdefine_line|#define&t;&t;ILLSADDR&t;0x02
DECL|macro|ILLHADDR
mdefine_line|#define&t;&t;ILLHADDR&t;0x01
multiline_comment|/*&n; * Clear Interrupt Status (p. 3-52)&n; */
DECL|macro|CLRINT
mdefine_line|#define CLRINT&t;&t;&t;0x092
DECL|macro|CLRBRKADRINT
mdefine_line|#define&t;&t;CLRBRKADRINT&t;0x08
DECL|macro|CLRSCSIINT
mdefine_line|#define&t;&t;CLRSCSIINT      0x04
DECL|macro|CLRCMDINT
mdefine_line|#define&t;&t;CLRCMDINT &t;0x02
DECL|macro|CLRSEQINT
mdefine_line|#define&t;&t;CLRSEQINT &t;0x01
DECL|macro|DFCNTRL
mdefine_line|#define&t;DFCNTRL&t;&t;&t;0x093
DECL|macro|WIDEODD
mdefine_line|#define&t;&t;WIDEODD&t;&t;0x40
DECL|macro|SCSIEN
mdefine_line|#define&t;&t;SCSIEN&t;&t;0x20
DECL|macro|SDMAEN
mdefine_line|#define&t;&t;SDMAEN&t;&t;0x10
DECL|macro|SDMAENACK
mdefine_line|#define&t;&t;SDMAENACK&t;0x10
DECL|macro|HDMAEN
mdefine_line|#define&t;&t;HDMAEN&t;&t;0x08
DECL|macro|HDMAENACK
mdefine_line|#define&t;&t;HDMAENACK&t;0x08
DECL|macro|DIRECTION
mdefine_line|#define&t;&t;DIRECTION&t;0x04
DECL|macro|FIFOFLUSH
mdefine_line|#define&t;&t;FIFOFLUSH&t;0x02
DECL|macro|FIFORESET
mdefine_line|#define&t;&t;FIFORESET&t;0x01
DECL|macro|DFSTATUS
mdefine_line|#define&t;DFSTATUS&t;&t;0x094
DECL|macro|HDONE
mdefine_line|#define&t;&t;HDONE&t;&t;0x08
DECL|macro|FIFOEMP
mdefine_line|#define&t;&t;FIFOEMP&t;&t;0x01
DECL|macro|DFDAT
mdefine_line|#define&t;DFDAT&t;&t;&t;0x099
multiline_comment|/*&n; * SCB Auto Increment (p. 3-59)&n; * Byte offset into the SCB Array and an optional bit to allow auto&n; * incrementing of the address during download and upload operations&n; */
DECL|macro|SCBCNT
mdefine_line|#define SCBCNT&t;&t;&t;0x09a
DECL|macro|SCBAUTO
mdefine_line|#define&t;&t;SCBAUTO&t;&t;0x80
DECL|macro|SCBCNT_MASK
mdefine_line|#define&t;&t;SCBCNT_MASK&t;0x1f
multiline_comment|/*&n; * Queue In FIFO (p. 3-60)&n; * Input queue for queued SCBs (commands that the seqencer has yet to start)&n; */
DECL|macro|QINFIFO
mdefine_line|#define QINFIFO&t;&t;&t;0x09b
multiline_comment|/*&n; * Queue In Count (p. 3-60)&n; * Number of queued SCBs&n; */
DECL|macro|QINCNT
mdefine_line|#define QINCNT&t;&t;&t;0x09c
multiline_comment|/*&n; * Queue Out FIFO (p. 3-61)&n; * Queue of SCBs that have completed and await the host&n; */
DECL|macro|QOUTFIFO
mdefine_line|#define QOUTFIFO&t;&t;0x09d
multiline_comment|/*&n; * Queue Out Count (p. 3-61)&n; * Number of queued SCBs in the Out FIFO&n; */
DECL|macro|QOUTCNT
mdefine_line|#define QOUTCNT&t;&t;&t;0x09e
multiline_comment|/*&n; * SCB Definition (p. 5-4)&n; * The two reserved bytes at SCBARRAY+1[23] are expected to be set to&n; * zero. Bit 3 in SCBARRAY+0 is used as an internal flag to indicate&n; * whether or not to DMA an SCB from host ram. This flag prevents the&n; * &quot;re-fetching&quot; of transactions that are requed because the target is&n; * busy with another command. We also use bits 6 &amp; 7 to indicate whether&n; * or not to initiate SDTR or WDTR repectively when starting this command.&n; */
DECL|macro|SCBARRAY
mdefine_line|#define SCBARRAY&t;&t;0x0a0
DECL|macro|SCB_CONTROL
mdefine_line|#define&t;SCB_CONTROL&t;&t;0x0a0
DECL|macro|NEEDWDTR
mdefine_line|#define&t;&t;NEEDWDTR        0x80
DECL|macro|DISCENB
mdefine_line|#define&t;&t;DISCENB         0x40
DECL|macro|TAG_ENB
mdefine_line|#define&t;&t;TAG_ENB&t;&t;0x20
DECL|macro|NEEDSDTR
mdefine_line|#define&t;&t;NEEDSDTR&t;0x10
DECL|macro|DISCONNECTED
mdefine_line|#define&t;&t;DISCONNECTED&t;0x04
DECL|macro|SCB_TAG_TYPE
mdefine_line|#define&t;&t;SCB_TAG_TYPE&t;0x03
DECL|macro|SCB_TCL
mdefine_line|#define&t;SCB_TCL&t;&t;&t;0x0a1
DECL|macro|SCB_TARGET_STATUS
mdefine_line|#define&t;SCB_TARGET_STATUS&t;0x0a2
DECL|macro|SCB_SGCOUNT
mdefine_line|#define&t;SCB_SGCOUNT&t;&t;0x0a3
DECL|macro|SCB_SGPTR
mdefine_line|#define&t;SCB_SGPTR&t;&t;0x0a4
DECL|macro|SCB_SGPTR0
mdefine_line|#define&t;&t;SCB_SGPTR0&t;0x0a4
DECL|macro|SCB_SGPTR1
mdefine_line|#define&t;&t;SCB_SGPTR1&t;0x0a5
DECL|macro|SCB_SGPTR2
mdefine_line|#define&t;&t;SCB_SGPTR2&t;0x0a6
DECL|macro|SCB_SGPTR3
mdefine_line|#define&t;&t;SCB_SGPTR3&t;0x0a7
DECL|macro|SCB_RESID_SGCNT
mdefine_line|#define&t;SCB_RESID_SGCNT&t;&t;0x0a8
DECL|macro|SCB_RESID_DCNT
mdefine_line|#define SCB_RESID_DCNT&t;&t;0x0a9
DECL|macro|SCB_RESID_DCNT0
mdefine_line|#define&t;&t;SCB_RESID_DCNT0&t;0x0a9
DECL|macro|SCB_RESID_DCNT1
mdefine_line|#define&t;&t;SCB_RESID_DCNT1&t;0x0aa
DECL|macro|SCB_RESID_DCNT2
mdefine_line|#define&t;&t;SCB_RESID_DCNT2&t;0x0ab
DECL|macro|SCB_DATAPTR
mdefine_line|#define SCB_DATAPTR&t;&t;0x0ac
DECL|macro|SCB_DATAPTR0
mdefine_line|#define&t;&t;SCB_DATAPTR0&t;0x0ac
DECL|macro|SCB_DATAPTR1
mdefine_line|#define&t;&t;SCB_DATAPTR1&t;0x0ad
DECL|macro|SCB_DATAPTR2
mdefine_line|#define&t;&t;SCB_DATAPTR2&t;0x0ae
DECL|macro|SCB_DATAPTR3
mdefine_line|#define&t;&t;SCB_DATAPTR3&t;0x0af
DECL|macro|SCB_DATACNT
mdefine_line|#define&t;SCB_DATACNT&t;&t;0x0b0
DECL|macro|SCB_DATACNT0
mdefine_line|#define&t;&t;SCB_DATACNT0&t;0x0b0
DECL|macro|SCB_DATACNT1
mdefine_line|#define&t;&t;SCB_DATACNT1&t;0x0b1
DECL|macro|SCB_DATACNT2
mdefine_line|#define&t;&t;SCB_DATACNT2&t;0x0b2
multiline_comment|/* UNUSED - QUAD PADDING&t;0x0b3 */
DECL|macro|SCB_CMDPTR
mdefine_line|#define SCB_CMDPTR&t;&t;0x0b4
DECL|macro|SCB_CMDPTR0
mdefine_line|#define&t;&t;SCB_CMDPTR0&t;0x0b4
DECL|macro|SCB_CMDPTR1
mdefine_line|#define&t;&t;SCB_CMDPTR1&t;0x0b5
DECL|macro|SCB_CMDPTR2
mdefine_line|#define&t;&t;SCB_CMDPTR2&t;0x0b6
DECL|macro|SCB_CMDPTR3
mdefine_line|#define&t;&t;SCB_CMDPTR3&t;0x0b7
DECL|macro|SCB_CMDLEN
mdefine_line|#define&t;SCB_CMDLEN&t;&t;0x0b8
DECL|macro|SCB_NEXT_WAITING
mdefine_line|#define&t;SCB_NEXT_WAITING&t;0x0b9
macro_line|#ifdef linux
DECL|macro|SG_SIZEOF
mdefine_line|#define&t;SG_SIZEOF&t;&t;0x0c&t;&t;/* sizeof(struct scatterlist) */
macro_line|#else
DECL|macro|SG_SIZEOF
mdefine_line|#define&t;SG_SIZEOF&t;&t;0x08&t;&t;/* sizeof(struct ahc_dma) */
macro_line|#endif
multiline_comment|/* --------------------- AHA-2840-only definitions -------------------- */
DECL|macro|SEECTL_2840
mdefine_line|#define&t;SEECTL_2840&t;&t;0x0c0
multiline_comment|/*&t;UNUSED&t;&t;&t;0xf8 */
DECL|macro|CS_2840
mdefine_line|#define&t;&t;CS_2840&t;&t;0x04
DECL|macro|CK_2840
mdefine_line|#define&t;&t;CK_2840&t;&t;0x02
DECL|macro|DO_2840
mdefine_line|#define&t;&t;DO_2840&t;&t;0x01
DECL|macro|STATUS_2840
mdefine_line|#define&t;STATUS_2840&t;&t;0x0c1
DECL|macro|EEPROM_TF
mdefine_line|#define&t;&t;EEPROM_TF&t;0x80
DECL|macro|BIOS_SEL
mdefine_line|#define&t;&t;BIOS_SEL&t;0x60
DECL|macro|ADSEL
mdefine_line|#define&t;&t;ADSEL&t;&t;0x1e
DECL|macro|DI_2840
mdefine_line|#define&t;&t;DI_2840&t;&t;0x01
multiline_comment|/* --------------------- AIC-7870-only definitions -------------------- */
DECL|macro|DSPCISTATUS
mdefine_line|#define DSPCISTATUS&t;&t;0x086
multiline_comment|/*&n; * Serial EEPROM Control (p. 4-92 in 7870 Databook)&n; * Controls the reading and writing of an external serial 1-bit&n; * EEPROM Device.  In order to access the serial EEPROM, you must&n; * first set the SEEMS bit that generates a request to the memory&n; * port for access to the serial EEPROM device.  When the memory&n; * port is not busy servicing another request, it reconfigures&n; * to allow access to the serial EEPROM.  When this happens, SEERDY&n; * gets set high to verify that the memory port access has been&n; * granted.  &n; *&n; * After successful arbitration for the memory port, the SEECS bit of &n; * the SEECTL register is connected to the chip select.  The SEECK, &n; * SEEDO, and SEEDI are connected to the clock, data out, and data in &n; * lines respectively.  The SEERDY bit of SEECTL is useful in that it &n; * gives us an 800 nsec timer.  After a write to the SEECTL register, &n; * the SEERDY goes high 800 nsec later.  The one exception to this is &n; * when we first request access to the memory port.  The SEERDY goes &n; * high to signify that access has been granted and, for this case, has &n; * no implied timing.&n; *&n; * See 93cx6.c for detailed information on the protocol necessary to &n; * read the serial EEPROM.&n; */
DECL|macro|SEECTL
mdefine_line|#define SEECTL&t;&t;&t;0x01e
DECL|macro|EXTARBACK
mdefine_line|#define&t;&t;EXTARBACK&t;0x80
DECL|macro|EXTARBREQ
mdefine_line|#define&t;&t;EXTARBREQ&t;0x40
DECL|macro|SEEMS
mdefine_line|#define&t;&t;SEEMS&t;&t;0x20
DECL|macro|SEERDY
mdefine_line|#define&t;&t;SEERDY&t;&t;0x10
DECL|macro|SEECS
mdefine_line|#define&t;&t;SEECS&t;&t;0x08
DECL|macro|SEECK
mdefine_line|#define&t;&t;SEECK&t;&t;0x04
DECL|macro|SEEDO
mdefine_line|#define&t;&t;SEEDO&t;&t;0x02
DECL|macro|SEEDI
mdefine_line|#define&t;&t;SEEDI&t;&t;0x01
multiline_comment|/* ---------------------- Scratch RAM Offsets ------------------------- */
multiline_comment|/* These offsets are either to values that are initialized by the board&squot;s&n; * BIOS or are specified by the sequencer code.&n; *&n; * The host adapter card (at least the BIOS) uses 20-2f for SCSI&n; * device information, 32-33 and 5a-5f as well. As it turns out, the&n; * BIOS trashes 20-2f, writing the synchronous negotiation results&n; * on top of the BIOS values, so we re-use those for our per-target&n; * scratchspace (actually a value that can be copied directly into&n; * SCSIRATE).  The kernel driver will enable synchronous negotiation&n; * for all targets that have a value other than 0 in the lower four&n; * bits of the target scratch space.  This should work regardless of&n; * whether the bios has been installed.&n; */
multiline_comment|/*&n; * 1 byte per target starting at this address for configuration values&n; */
DECL|macro|TARG_SCRATCH
mdefine_line|#define TARG_SCRATCH&t;&t;0x020
multiline_comment|/*&n; * The sequencer will stick the frist byte of any rejected message here so&n; * we can see what is getting thrown away.&n; */
DECL|macro|REJBYTE
mdefine_line|#define REJBYTE&t;&t;&t;0x031
multiline_comment|/*&n; * Bit vector of targets that have disconnection disabled.&n; */
DECL|macro|DISC_DSB
mdefine_line|#define&t;DISC_DSB&t;&t;0x032
DECL|macro|DISC_DSB_A
mdefine_line|#define&t;&t;DISC_DSB_A&t;0x032
DECL|macro|DISC_DSB_B
mdefine_line|#define&t;&t;DISC_DSB_B&t;0x033
multiline_comment|/*&n; * Length of pending message&n; */
DECL|macro|MSG_LEN
mdefine_line|#define MSG_LEN&t;&t;&t;0x034
DECL|macro|MSG0
mdefine_line|#define MSG0&t;&t;&t;0x035
DECL|macro|COMP_MSG0
mdefine_line|#define&t;&t;COMP_MSG0&t;0xcb      /* 2&squot;s complement of MSG0 */
DECL|macro|MSG1
mdefine_line|#define MSG1&t;&t;&t;0x036
DECL|macro|MSG2
mdefine_line|#define MSG2&t;&t;&t;0x037
DECL|macro|MSG3
mdefine_line|#define MSG3&t;&t;&t;0x038
DECL|macro|MSG4
mdefine_line|#define MSG4&t;&t;&t;0x039
DECL|macro|MSG5
mdefine_line|#define MSG5&t;&t;&t;0x03a
multiline_comment|/*&n; * These are offsets into the card&squot;s scratch ram.  Some of the values are&n; * specified in the AHA2742 technical reference manual and are initialized&n; * by the BIOS at boot time.&n; */
DECL|macro|LASTPHASE
mdefine_line|#define LASTPHASE&t;&t;0x049
DECL|macro|ARG_1
mdefine_line|#define ARG_1&t;&t;&t;0x04a
DECL|macro|RETURN_1
mdefine_line|#define RETURN_1&t;&t;0x04a
DECL|macro|SEND_SENSE
mdefine_line|#define&t;&t;SEND_SENSE&t;0x80
DECL|macro|SEND_WDTR
mdefine_line|#define&t;&t;SEND_WDTR&t;0x80
DECL|macro|SEND_SDTR
mdefine_line|#define&t;&t;SEND_SDTR&t;0x80
DECL|macro|SEND_REJ
mdefine_line|#define&t;&t;SEND_REJ&t;0x40
DECL|macro|SIGSTATE
mdefine_line|#define SIGSTATE&t;&t;0x04b
DECL|macro|DMAPARAMS
mdefine_line|#define DMAPARAMS&t;&t;0x04c&t;/* Parameters for DMA Logic */
DECL|macro|SG_COUNT
mdefine_line|#define&t;SG_COUNT&t;&t;0x04d
DECL|macro|SG_NEXT
mdefine_line|#define&t;SG_NEXT&t;&t;&t;0x04e&t;/* working value of SG pointer */
DECL|macro|SG_NEXT0
mdefine_line|#define&t;&t;SG_NEXT0&t;0x04e
DECL|macro|SG_NEXT1
mdefine_line|#define&t;&t;SG_NEXT1&t;0x04f
DECL|macro|SG_NEXT2
mdefine_line|#define&t;&t;SG_NEXT2&t;0x050
DECL|macro|SG_NEXT3
mdefine_line|#define&t;&t;SG_NEXT3&t;0x051
DECL|macro|SCBCOUNT
mdefine_line|#define&t;SCBCOUNT&t;&t;0x052&t;/*&n;&t;&t;&t;&t;&t; * Number of SCBs supported by&n;&t;&t;&t;&t;&t; * this card.&n;&t;&t;&t;&t;&t; */
DECL|macro|FLAGS
mdefine_line|#define FLAGS&t;&t;&t;0x053
DECL|macro|SINGLE_BUS
mdefine_line|#define&t;&t;SINGLE_BUS&t;0x00
DECL|macro|TWIN_BUS
mdefine_line|#define&t;&t;TWIN_BUS&t;0x01
DECL|macro|WIDE_BUS
mdefine_line|#define&t;&t;WIDE_BUS&t;0x02
DECL|macro|DPHASE
mdefine_line|#define&t;&t;DPHASE&t;&t;0x04
DECL|macro|MAXOFFSET
mdefine_line|#define&t;&t;MAXOFFSET&t;0x08
DECL|macro|IDENTIFY_SEEN
mdefine_line|#define&t;&t;IDENTIFY_SEEN&t;0x40
DECL|macro|RESELECTED
mdefine_line|#define&t;&t;RESELECTED&t;0x80
DECL|macro|ACTIVE_A
mdefine_line|#define&t;ACTIVE_A&t;&t;0x054
DECL|macro|ACTIVE_B
mdefine_line|#define&t;ACTIVE_B&t;&t;0x055
DECL|macro|SAVED_TCL
mdefine_line|#define&t;SAVED_TCL&t;&t;0x056&t;/*&n;&t;&t;&t;&t;&t; * Temporary storage for the&n;&t;&t;&t;&t;&t; * target/channel/lun of a&n;&t;&t;&t;&t;&t; * reconnecting target&n;&t;&t;&t;&t;&t; */
DECL|macro|WAITING_SCBH
mdefine_line|#define WAITING_SCBH&t;&t;0x057&t;/*&n;&t;&t;&t;&t;&t; * head of list of SCBs awaiting&n;&t;&t;&t;&t;&t; * selection&n;&t;&t;&t;&t;&t; */
DECL|macro|WAITING_SCBT
mdefine_line|#define WAITING_SCBT&t;&t;0x058&t;/*&n;&t;&t;&t;&t;&t; * tail of list of SCBs awaiting&n;&t;&t;&t;&t;&t; * selection&n;&t;&t;&t;&t;&t; */
DECL|macro|COMP_SCBCOUNT
mdefine_line|#define&t;COMP_SCBCOUNT&t;&t;0x059
DECL|macro|SCB_LIST_NULL
mdefine_line|#define&t;&t;SCB_LIST_NULL&t;0xff
DECL|macro|SCSICONF
mdefine_line|#define SCSICONF&t;&t;0x05a
DECL|macro|HOSTCONF
mdefine_line|#define HOSTCONF&t;&t;0x05d
DECL|macro|HA_274_BIOSCTRL
mdefine_line|#define HA_274_BIOSCTRL&t;&t;0x05f
DECL|macro|BIOSMODE
mdefine_line|#define BIOSMODE&t;&t;0x30
DECL|macro|BIOSDISABLED
mdefine_line|#define BIOSDISABLED&t;&t;0x30
multiline_comment|/* Message codes */
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED&t;&t;0x01
DECL|macro|MSG_SDTR
mdefine_line|#define&t;&t;MSG_SDTR&t;0x01
DECL|macro|MSG_WDTR
mdefine_line|#define&t;&t;MSG_WDTR&t;0x03
DECL|macro|MSG_SDPTRS
mdefine_line|#define MSG_SDPTRS&t;&t;0x02
DECL|macro|MSG_RDPTRS
mdefine_line|#define MSG_RDPTRS&t;&t;0x03
DECL|macro|MSG_DISCONNECT
mdefine_line|#define MSG_DISCONNECT&t;&t;0x04
DECL|macro|MSG_INITIATOR_DET_ERROR
mdefine_line|#define MSG_INITIATOR_DET_ERROR&t;0x05
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT&t;&t;0x06
DECL|macro|MSG_REJECT
mdefine_line|#define&t;MSG_REJECT&t;&t;0x07
DECL|macro|MSG_NOP
mdefine_line|#define MSG_NOP&t;&t;&t;0x08
DECL|macro|MSG_MSG_PARITY_ERROR
mdefine_line|#define MSG_MSG_PARITY_ERROR&t;0x09
DECL|macro|MSG_BUS_DEVICE_RESET
mdefine_line|#define MSG_BUS_DEVICE_RESET&t;0x0c
DECL|macro|MSG_SIMPLE_TAG
mdefine_line|#define MSG_SIMPLE_TAG&t;&t;0x20
DECL|macro|MSG_IDENTIFY
mdefine_line|#define MSG_IDENTIFY&t;&t;0x80
multiline_comment|/* WDTR Message values */
DECL|macro|BUS_8_BIT
mdefine_line|#define&t;BUS_8_BIT&t;&t;0x00
DECL|macro|BUS_16_BIT
mdefine_line|#define BUS_16_BIT&t;&t;0x01
DECL|macro|BUS_32_BIT
mdefine_line|#define BUS_32_BIT&t;&t;0x02
DECL|macro|MAX_OFFSET_8BIT
mdefine_line|#define MAX_OFFSET_8BIT&t;&t;0x0f
DECL|macro|MAX_OFFSET_16BIT
mdefine_line|#define MAX_OFFSET_16BIT&t;0x08
eof
