multiline_comment|/* $Id: psycho.h,v 1.5 1999/04/01 12:27:28 davem Exp $&n; * psycho.h: UltraSparc AX specific PCI definitions.&n; *&n; * Copyright (C) 1997 Eddie C. Dost (ecd@skynet.be)&n; */
macro_line|#ifndef __SPARC64_PSYCHO_H
DECL|macro|__SPARC64_PSYCHO_H
mdefine_line|#define __SPARC64_PSYCHO_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* Ultra AX PSYCHO Register Set, one per controller probed. */
DECL|struct|psycho_regs
r_struct
id|psycho_regs
(brace
DECL|member|upa_id
multiline_comment|/*0x0000*/
id|u64
id|upa_id
suffix:semicolon
multiline_comment|/* PSYCHO UPA Port ID Register&t;*/
DECL|member|upa_cfg
multiline_comment|/*0x0008*/
id|u64
id|upa_cfg
suffix:semicolon
multiline_comment|/* PSYCHO UPA Config Register&t;*/
DECL|member|control
multiline_comment|/*0x0010*/
id|u64
id|control
suffix:semicolon
multiline_comment|/* PSYCHO Control Register&t;*/
DECL|member|__pad0
multiline_comment|/*0x0018*/
id|u64
id|__pad0
suffix:semicolon
DECL|member|ecc_control
multiline_comment|/*0x0020*/
id|u64
id|ecc_control
suffix:semicolon
multiline_comment|/* ECC Control Register&t;&t;*/
DECL|member|__pad1
multiline_comment|/*0x0028*/
id|u64
id|__pad1
suffix:semicolon
multiline_comment|/* Uncorrectable Error Fault Registers */
DECL|member|ue_afsr
multiline_comment|/*0x0030*/
id|u64
id|ue_afsr
suffix:semicolon
multiline_comment|/* UE Async Fault Status&t;*/
DECL|member|ue_afar
multiline_comment|/*0x0038*/
id|u64
id|ue_afar
suffix:semicolon
multiline_comment|/* UE Async Fault Address&t;*/
multiline_comment|/* Correctable Error Fault Registers */
DECL|member|ce_afsr
multiline_comment|/*0x0040*/
id|u64
id|ce_afsr
suffix:semicolon
multiline_comment|/* CE Async Fault Status&t;*/
DECL|member|ce_afar
multiline_comment|/*0x0048*/
id|u64
id|ce_afar
suffix:semicolon
multiline_comment|/* CE Async Fault Address&t;*/
DECL|member|__pad2
id|u64
id|__pad2
(braket
l_int|0x16
)braket
suffix:semicolon
multiline_comment|/* Performance Monitoring Registers */
DECL|member|pmon_control
multiline_comment|/*0x0100*/
id|u64
id|pmon_control
suffix:semicolon
DECL|member|pmon_counter
multiline_comment|/*0x0108*/
id|u64
id|pmon_counter
suffix:semicolon
DECL|member|__pad3
id|u64
id|__pad3
(braket
l_int|0x1e
)braket
suffix:semicolon
multiline_comment|/* PCI Bus IOMMU lives here */
DECL|member|iommu_control
multiline_comment|/*0x0200*/
id|u64
id|iommu_control
suffix:semicolon
multiline_comment|/* IOMMU Control&t;&t;*/
DECL|member|iommu_tsbbase
multiline_comment|/*0x0208*/
id|u64
id|iommu_tsbbase
suffix:semicolon
multiline_comment|/* IOMMU TSB Base&t;&t;*/
DECL|member|iommu_flush
multiline_comment|/*0x0210*/
id|u64
id|iommu_flush
suffix:semicolon
multiline_comment|/* IOMMU Flush Register&t;&t;*/
DECL|member|__pad4
id|u64
id|__pad4
(braket
l_int|0x13d
)braket
suffix:semicolon
multiline_comment|/* Interrupt mapping/control registers */
DECL|member|imap_a_slot0
multiline_comment|/*0x0c00*/
id|u64
id|imap_a_slot0
suffix:semicolon
multiline_comment|/* PCI A Slot 0 Int Mapping&t;*/
DECL|member|imap_a_slot1
multiline_comment|/*0x0c08*/
id|u64
id|imap_a_slot1
suffix:semicolon
multiline_comment|/* PCI A Slot 1 Int Mapping&t;*/
DECL|member|imap_a_slot2
multiline_comment|/*0x0c10*/
id|u64
id|imap_a_slot2
suffix:semicolon
multiline_comment|/* PCI A Slot 2 Int Mapping (IIi only)*/
DECL|member|imap_a_slot3
multiline_comment|/*0x0c18*/
id|u64
id|imap_a_slot3
suffix:semicolon
multiline_comment|/* PCI A Slot 3 Int Mapping (IIi only)*/
DECL|member|imap_b_slot0
multiline_comment|/*0x0c20*/
id|u64
id|imap_b_slot0
suffix:semicolon
multiline_comment|/* PCI B Slot 0 Int Mapping&t;*/
DECL|member|imap_b_slot1
multiline_comment|/*0x0c28*/
id|u64
id|imap_b_slot1
suffix:semicolon
multiline_comment|/* PCI B Slot 1 Int Mapping&t;*/
DECL|member|imap_b_slot2
multiline_comment|/*0x0c30*/
id|u64
id|imap_b_slot2
suffix:semicolon
multiline_comment|/* PCI B Slot 2 Int Mapping&t;*/
DECL|member|imap_b_slot3
multiline_comment|/*0x0c38*/
id|u64
id|imap_b_slot3
suffix:semicolon
multiline_comment|/* PCI B Slot 3 Int Mapping&t;*/
DECL|member|__pad6
id|u64
id|__pad6
(braket
l_int|0x78
)braket
suffix:semicolon
DECL|member|imap_scsi
multiline_comment|/*0x1000*/
id|u64
id|imap_scsi
suffix:semicolon
multiline_comment|/* SCSI Int Mapping&t;&t;*/
DECL|member|imap_eth
multiline_comment|/*0x1008*/
id|u64
id|imap_eth
suffix:semicolon
multiline_comment|/* Ethernet Int Mapping&t;&t;*/
DECL|member|imap_bpp
multiline_comment|/*0x1010*/
id|u64
id|imap_bpp
suffix:semicolon
multiline_comment|/* Parallel Port Int Mapping&t;*/
DECL|member|imap_au_rec
multiline_comment|/*0x1018*/
id|u64
id|imap_au_rec
suffix:semicolon
multiline_comment|/* Audio Record Int Mapping&t;*/
DECL|member|imap_au_play
multiline_comment|/*0x1020*/
id|u64
id|imap_au_play
suffix:semicolon
multiline_comment|/* Audio Playback Int Mapping&t;*/
DECL|member|imap_pfail
multiline_comment|/*0x1028*/
id|u64
id|imap_pfail
suffix:semicolon
multiline_comment|/* Power Fail Int Mapping&t;*/
DECL|member|imap_kms
multiline_comment|/*0x1030*/
id|u64
id|imap_kms
suffix:semicolon
multiline_comment|/* Kbd/Mouse/Ser Int Mapping&t;*/
DECL|member|imap_flpy
multiline_comment|/*0x1038*/
id|u64
id|imap_flpy
suffix:semicolon
multiline_comment|/* Floppy Int Mapping&t;&t;*/
DECL|member|imap_shw
multiline_comment|/*0x1040*/
id|u64
id|imap_shw
suffix:semicolon
multiline_comment|/* Spare HW Int Mapping&t;&t;*/
DECL|member|imap_kbd
multiline_comment|/*0x1048*/
id|u64
id|imap_kbd
suffix:semicolon
multiline_comment|/* Kbd Only Int Mapping&t;&t;*/
DECL|member|imap_ms
multiline_comment|/*0x1050*/
id|u64
id|imap_ms
suffix:semicolon
multiline_comment|/* Mouse Only Int Mapping&t;*/
DECL|member|imap_ser
multiline_comment|/*0x1058*/
id|u64
id|imap_ser
suffix:semicolon
multiline_comment|/* Serial Only Int Mapping&t;*/
DECL|member|imap_tim0
multiline_comment|/*0x1060*/
id|u64
id|imap_tim0
suffix:semicolon
multiline_comment|/* Timer 0 Int Mapping&t;&t;*/
DECL|member|imap_tim1
multiline_comment|/*0x1068*/
id|u64
id|imap_tim1
suffix:semicolon
multiline_comment|/* Timer 1 Int Mapping&t;&t;*/
DECL|member|imap_ue
multiline_comment|/*0x1070*/
id|u64
id|imap_ue
suffix:semicolon
multiline_comment|/* UE Int Mapping&t;&t;*/
DECL|member|imap_ce
multiline_comment|/*0x1078*/
id|u64
id|imap_ce
suffix:semicolon
multiline_comment|/* CE Int Mapping&t;&t;*/
DECL|member|imap_a_err
multiline_comment|/*0x1080*/
id|u64
id|imap_a_err
suffix:semicolon
multiline_comment|/* PCI A Err Int Mapping&t;*/
DECL|member|imap_b_err
multiline_comment|/*0x1088*/
id|u64
id|imap_b_err
suffix:semicolon
multiline_comment|/* PCI B Err Int Mapping&t;*/
DECL|member|imap_pmgmt
multiline_comment|/*0x1090*/
id|u64
id|imap_pmgmt
suffix:semicolon
multiline_comment|/* Power Mgmt Int Mapping&t;*/
DECL|member|imap_gfx
multiline_comment|/*0x1098*/
id|u64
id|imap_gfx
suffix:semicolon
multiline_comment|/* OB Graphics Int Mapping&t;*/
DECL|member|imap_eupa
multiline_comment|/*0x10a0*/
id|u64
id|imap_eupa
suffix:semicolon
multiline_comment|/* UPA Expansion Int Mapping&t;*/
DECL|member|__pad7
id|u64
id|__pad7
(braket
l_int|0x6b
)braket
suffix:semicolon
multiline_comment|/* Interrupt Clear Registers */
DECL|member|iclr_a_slot0
multiline_comment|/*0x1400*/
id|u64
id|iclr_a_slot0
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI A Slot 0 Clear Int Reg */
DECL|member|iclr_a_slot1
multiline_comment|/*0x1420*/
id|u64
id|iclr_a_slot1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI A Slot 1 Clear Int Reg */
DECL|member|iclr_a_slot2
multiline_comment|/*0x1440*/
id|u64
id|iclr_a_slot2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI A Slot 2 Clear Int Reg */
DECL|member|iclr_a_slot3
multiline_comment|/*0x1460*/
id|u64
id|iclr_a_slot3
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI A Slot 3 Clear Int Reg */
DECL|member|iclr_b_slot0
multiline_comment|/*0x1480*/
id|u64
id|iclr_b_slot0
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI B Slot 0 Clear Int Reg */
DECL|member|iclr_b_slot1
multiline_comment|/*0x14a0*/
id|u64
id|iclr_b_slot1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI B Slot 1 Clear Int Reg */
DECL|member|iclr_b_slot2
multiline_comment|/*0x14c0*/
id|u64
id|iclr_b_slot2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI B Slot 2 Clear Int Reg */
DECL|member|iclr_b_slot3
multiline_comment|/*0x14e0*/
id|u64
id|iclr_b_slot3
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* PCI B Slot 3 Clear Int Reg */
DECL|member|__pad9
id|u64
id|__pad9
(braket
l_int|0x60
)braket
suffix:semicolon
DECL|member|iclr_scsi
multiline_comment|/*0x1800*/
id|u64
id|iclr_scsi
suffix:semicolon
DECL|member|iclr_eth
multiline_comment|/*0x1808*/
id|u64
id|iclr_eth
suffix:semicolon
DECL|member|iclr_bpp
multiline_comment|/*0x1810*/
id|u64
id|iclr_bpp
suffix:semicolon
DECL|member|iclr_au_rec
multiline_comment|/*0x1818*/
id|u64
id|iclr_au_rec
suffix:semicolon
DECL|member|iclr_au_play
multiline_comment|/*0x1820*/
id|u64
id|iclr_au_play
suffix:semicolon
DECL|member|iclr_pfail
multiline_comment|/*0x1828*/
id|u64
id|iclr_pfail
suffix:semicolon
DECL|member|iclr_kms
multiline_comment|/*0x1830*/
id|u64
id|iclr_kms
suffix:semicolon
DECL|member|iclr_flpy
multiline_comment|/*0x1838*/
id|u64
id|iclr_flpy
suffix:semicolon
DECL|member|iclr_shw
multiline_comment|/*0x1840*/
id|u64
id|iclr_shw
suffix:semicolon
DECL|member|iclr_kbd
multiline_comment|/*0x1848*/
id|u64
id|iclr_kbd
suffix:semicolon
DECL|member|iclr_ms
multiline_comment|/*0x1850*/
id|u64
id|iclr_ms
suffix:semicolon
DECL|member|iclr_ser
multiline_comment|/*0x1858*/
id|u64
id|iclr_ser
suffix:semicolon
DECL|member|iclr_tim0
multiline_comment|/*0x1860*/
id|u64
id|iclr_tim0
suffix:semicolon
DECL|member|iclr_tim1
multiline_comment|/*0x1868*/
id|u64
id|iclr_tim1
suffix:semicolon
DECL|member|iclr_ue
multiline_comment|/*0x1870*/
id|u64
id|iclr_ue
suffix:semicolon
DECL|member|iclr_ce
multiline_comment|/*0x1878*/
id|u64
id|iclr_ce
suffix:semicolon
DECL|member|iclr_a_err
multiline_comment|/*0x1880*/
id|u64
id|iclr_a_err
suffix:semicolon
DECL|member|iclr_b_err
multiline_comment|/*0x1888*/
id|u64
id|iclr_b_err
suffix:semicolon
DECL|member|iclr_pmgmt
multiline_comment|/*0x1890*/
id|u64
id|iclr_pmgmt
suffix:semicolon
DECL|member|__pad10
id|u64
id|__pad10
(braket
l_int|0x2d
)braket
suffix:semicolon
multiline_comment|/* Interrupt Retry Timer. */
DECL|member|irq_retry
multiline_comment|/*0x1a00*/
id|u64
id|irq_retry
suffix:semicolon
DECL|member|__pad11
id|u64
id|__pad11
(braket
l_int|0x3f
)braket
suffix:semicolon
multiline_comment|/* Counters/Timers */
DECL|member|tim0_cnt
multiline_comment|/*0x1c00*/
id|u64
id|tim0_cnt
suffix:semicolon
DECL|member|tim0_lim
multiline_comment|/*0x1c08*/
id|u64
id|tim0_lim
suffix:semicolon
DECL|member|tim1_cnt
multiline_comment|/*0x1c10*/
id|u64
id|tim1_cnt
suffix:semicolon
DECL|member|tim1_lim
multiline_comment|/*0x1c18*/
id|u64
id|tim1_lim
suffix:semicolon
DECL|member|pci_dma_wsync
multiline_comment|/*0x1c20*/
id|u64
id|pci_dma_wsync
suffix:semicolon
multiline_comment|/* PCI DMA Write Sync Register (IIi) */
DECL|member|__pad12
id|u64
id|__pad12
(braket
l_int|0x7b
)braket
suffix:semicolon
multiline_comment|/* PCI Bus A Registers */
DECL|member|pci_a_control
multiline_comment|/*0x2000*/
id|u64
id|pci_a_control
suffix:semicolon
multiline_comment|/* PCI Bus A Control Register&t;*/
DECL|member|__pad13
multiline_comment|/*0x2008*/
id|u64
id|__pad13
suffix:semicolon
DECL|member|pci_a_afsr
multiline_comment|/*0x2010*/
id|u64
id|pci_a_afsr
suffix:semicolon
multiline_comment|/* PCI Bus A Async Fault Status&t;*/
DECL|member|pci_a_afar
multiline_comment|/*0x2018*/
id|u64
id|pci_a_afar
suffix:semicolon
multiline_comment|/* PCI Bus A Async Fault Address*/
DECL|member|pci_a_diag
multiline_comment|/*0x2020*/
id|u64
id|pci_a_diag
suffix:semicolon
multiline_comment|/* PCI Bus A Diag Register&t;*/
DECL|member|pci_tasr
multiline_comment|/*0x2028*/
id|u64
id|pci_tasr
suffix:semicolon
multiline_comment|/* PCI Target Address Space Reg (IIi) */
DECL|member|__pad14
id|u64
id|__pad14
(braket
l_int|0xfa
)braket
suffix:semicolon
multiline_comment|/* PCI Bus A/IOMMU Streaming Buffer Registers */
DECL|member|sbuf_a_control
multiline_comment|/*0x2800*/
id|u64
id|sbuf_a_control
suffix:semicolon
multiline_comment|/* StrBuffer Control&t;&t;*/
DECL|member|sbuf_a_pflush
multiline_comment|/*0x2808*/
id|u64
id|sbuf_a_pflush
suffix:semicolon
multiline_comment|/* StrBuffer Page Flush&t;&t;*/
DECL|member|sbuf_a_fsync
multiline_comment|/*0x2810*/
id|u64
id|sbuf_a_fsync
suffix:semicolon
multiline_comment|/* StrBuffer Flush Sync Reg&t;*/
DECL|member|__pad15
id|u64
id|__pad15
(braket
l_int|0x2fd
)braket
suffix:semicolon
multiline_comment|/* PCI Bus B Registers */
DECL|member|pci_b_control
multiline_comment|/*0x4000*/
id|u64
id|pci_b_control
suffix:semicolon
multiline_comment|/* PCI Bus B Control Register&t;*/
DECL|member|__pad16
multiline_comment|/*0x4008*/
id|u64
id|__pad16
suffix:semicolon
DECL|member|pci_b_afsr
multiline_comment|/*0x4010*/
id|u64
id|pci_b_afsr
suffix:semicolon
multiline_comment|/* PCI Bus B Async Fault Status&t;*/
DECL|member|pci_b_afar
multiline_comment|/*0x4018*/
id|u64
id|pci_b_afar
suffix:semicolon
multiline_comment|/* PCI Bus B Async Fault Address*/
DECL|member|pci_b_diag
multiline_comment|/*0x4020*/
id|u64
id|pci_b_diag
suffix:semicolon
multiline_comment|/* PCI Bus B Diag Register&t;*/
DECL|member|__pad17
id|u64
id|__pad17
(braket
l_int|0x7b
)braket
suffix:semicolon
multiline_comment|/* IOMMU diagnostic things */
DECL|member|iommu_vdiag
multiline_comment|/*0x4400*/
id|u64
id|iommu_vdiag
suffix:semicolon
multiline_comment|/* VADDR Diagnostic Register&t;*/
DECL|member|iommu_tcompare
multiline_comment|/*0x4408*/
id|u64
id|iommu_tcompare
suffix:semicolon
multiline_comment|/* IOMMU TLB Tag Compare&t;*/
DECL|member|__pad18
id|u64
id|__pad18
(braket
l_int|0x7e
)braket
suffix:semicolon
multiline_comment|/* PCI Bus B/IOMMU Streaming Buffer Registers */
DECL|member|sbuf_b_control
multiline_comment|/*0x4800*/
id|u64
id|sbuf_b_control
suffix:semicolon
multiline_comment|/* StrBuffer Control&t;&t;*/
DECL|member|sbuf_b_pflush
multiline_comment|/*0x4808*/
id|u64
id|sbuf_b_pflush
suffix:semicolon
multiline_comment|/* StrBuffer Page Flush&t;&t;*/
DECL|member|sbuf_b_fsync
multiline_comment|/*0x4810*/
id|u64
id|sbuf_b_fsync
suffix:semicolon
multiline_comment|/* StrBuffer Flush Sync Reg&t;*/
DECL|member|__pad19
id|u64
id|__pad19
(braket
l_int|0xafd
)braket
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diagnostic Registers */
DECL|member|dscore_reg0
multiline_comment|/*0xa000*/
id|u64
id|dscore_reg0
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diag Reg 0&t;*/
DECL|member|dscore_reg1
multiline_comment|/*0xa008*/
id|u64
id|dscore_reg1
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diag Reg 1&t;*/
DECL|member|__pad20
id|u64
id|__pad20
(braket
l_int|0x9e
)braket
suffix:semicolon
multiline_comment|/* More IOMMU diagnostic things */
DECL|member|iommu_lru
multiline_comment|/*0xa500*/
id|u64
id|iommu_lru
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* IOMMU LRU Queue Diag&t;&t;*/
DECL|member|iommu_tag
multiline_comment|/*0xa580*/
id|u64
id|iommu_tag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* IOMMU TLB Tag Diag&t;&t;*/
DECL|member|iommu_data
multiline_comment|/*0xa600*/
id|u64
id|iommu_data
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* IOMMU TLB Data RAM Diag&t;*/
DECL|member|__pad21
id|u64
id|__pad21
(braket
l_int|0x30
)braket
suffix:semicolon
multiline_comment|/* Interrupt State Diagnostics */
DECL|member|pci_istate
multiline_comment|/*0xa800*/
id|u64
id|pci_istate
suffix:semicolon
DECL|member|obio_istate
multiline_comment|/*0xa808*/
id|u64
id|obio_istate
suffix:semicolon
DECL|member|__pad22
id|u64
id|__pad22
(braket
l_int|0xfe
)braket
suffix:semicolon
multiline_comment|/* Streaming Buffer A Diagnostic Area */
DECL|member|sbuf_a_data
multiline_comment|/*0xb000*/
id|u64
id|sbuf_a_data
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Data Ram Diag&t;*/
DECL|member|sbuf_a_errs
multiline_comment|/*0xb400*/
id|u64
id|sbuf_a_errs
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Error Status Diag*/
DECL|member|sbuf_a_ptag
multiline_comment|/*0xb800*/
id|u64
id|sbuf_a_ptag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Page Tag Diag&t;*/
DECL|member|__pad23
multiline_comment|/*0xb880*/
id|u64
id|__pad23
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sbuf_a_ltag
multiline_comment|/*0xb900*/
id|u64
id|sbuf_a_ltag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Line Tag Diag&t;*/
DECL|member|__pad24
id|u64
id|__pad24
(braket
l_int|0xd0
)braket
suffix:semicolon
multiline_comment|/* Streaming Buffer B Diagnostic Area */
DECL|member|sbuf_b_data
multiline_comment|/*0xc000*/
id|u64
id|sbuf_b_data
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Data Ram Diag&t;*/
DECL|member|sbuf_b_errs
multiline_comment|/*0xc400*/
id|u64
id|sbuf_b_errs
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Error Status Diag*/
DECL|member|sbuf_b_ptag
multiline_comment|/*0xc800*/
id|u64
id|sbuf_b_ptag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Page Tag Diag&t;*/
DECL|member|__pad25
multiline_comment|/*0xc880*/
id|u64
id|__pad25
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sbuf_b_ltag
multiline_comment|/*0xc900*/
id|u64
id|sbuf_b_ltag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Line Tag Diag&t;*/
)brace
suffix:semicolon
multiline_comment|/* PSYCHO UPA Port ID */
DECL|macro|PSYCHO_UPPID_FESC
mdefine_line|#define PSYCHO_UPPID_FESC&t;0xff00000000000000 /* FCode escape, 0xfc           */
DECL|macro|PSYCHO_UPPID_RESV1
mdefine_line|#define PSYCHO_UPPID_RESV1&t;0x00fffff800000000 /* Reserved                     */
DECL|macro|PSYCHO_UPPID_ENV
mdefine_line|#define PSYCHO_UPPID_ENV&t;0x0000000400000000 /* Cannot generate ECC          */
DECL|macro|PSYCHO_UPPID_ORD
mdefine_line|#define PSYCHO_UPPID_ORD&t;0x0000000200000000 /* One Outstanding Read         */
DECL|macro|PSYCHO_UPPID_RESV2
mdefine_line|#define PSYCHO_UPPID_RESV2&t;0x0000000180000000 /* Reserved                     */
DECL|macro|PSYCHO_UPPID_PDQ
mdefine_line|#define PSYCHO_UPPID_PDQ&t;0x000000007e000000 /* Data Queue size              */
DECL|macro|PSYCHO_UPPID_PRQ
mdefine_line|#define PSYCHO_UPPID_PRQ&t;0x0000000001e00000 /* Request Queue size           */
DECL|macro|PSYCHO_UPPID_UCAP
mdefine_line|#define PSYCHO_UPPID_UCAP&t;0x00000000001f0000 /* UPA Capabilities             */
DECL|macro|PSYCHO_UPPID_JEDEC
mdefine_line|#define PSYCHO_UPPID_JEDEC&t;0x000000000000ffff /* JEDEC ID for PSYCHO          */
multiline_comment|/* PSYCHO UPA Configuration Register */
DECL|macro|PSYCHO_UPCFG_RESV
mdefine_line|#define PSYCHO_UPCFG_RESV&t;0xffffffffffffff00 /* Reserved                     */
DECL|macro|PSYCHO_UPCFG_SCIQ1
mdefine_line|#define PSYCHO_UPCFG_SCIQ1&t;0x00000000000000f0 /* Unused, always zero          */
DECL|macro|PSYCHO_UPCFG_SCIQ2
mdefine_line|#define PSYCHO_UPCFG_SCIQ2&t;0x000000000000000f /* Requests Queue size 0x2 &t;   */
multiline_comment|/* PSYCHO Control Register */
DECL|macro|PSYCHO_CONTROL_IMPL
mdefine_line|#define PSYCHO_CONTROL_IMPL&t;0xf000000000000000 /* Implementation of this PSYCHO*/
DECL|macro|PSYCHO_CONTROL_VER
mdefine_line|#define PSYCHO_CONTROL_VER&t;0x0f00000000000000 /* Version of this PSYCHO       */
DECL|macro|PSYCHO_CONTROL_MID
mdefine_line|#define PSYCHO_CONTROL_MID&t;0x00f8000000000000 /* UPA Module ID of PSYCHO      */
DECL|macro|PSYCHO_CONTROL_IGN
mdefine_line|#define PSYCHO_CONTROL_IGN&t;0x0007c00000000000 /* Interrupt Group Number       */
DECL|macro|PSYCHO_CONTROL_RESV
mdefine_line|#define PSYCHO_CONTROL_RESV     0x00003ffffffffff0 /* Reserved                     */
DECL|macro|PSYCHO_CONTROL_APCKEN
mdefine_line|#define PSYCHO_CONTROL_APCKEN&t;0x0000000000000008 /* Address Parity Check Enable  */
DECL|macro|PSYCHO_CONTROL_APERR
mdefine_line|#define PSYCHO_CONTROL_APERR&t;0x0000000000000004 /* Incoming System Addr Parerr  */
DECL|macro|PSYCHO_CONTROL_IAP
mdefine_line|#define PSYCHO_CONTROL_IAP&t;0x0000000000000002 /* Invert UPA Parity            */
DECL|macro|PSYCHO_CONTROL_MODE
mdefine_line|#define PSYCHO_CONTROL_MODE&t;0x0000000000000001 /* PSYCHO clock mode            */
multiline_comment|/* PSYCHO ECC Control Register */
DECL|macro|PSYCHO_ECNTRL_ECCEN
mdefine_line|#define PSYCHO_ECNTRL_ECCEN&t;0x8000000000000000 /* Enable ECC Checking&t;   */
DECL|macro|PSYCHO_ECNTRL_UEEN
mdefine_line|#define PSYCHO_ECNTRL_UEEN&t;0x4000000000000000 /* Enable UE Interrupts         */
DECL|macro|PSYCHO_ECNTRL_CEEN
mdefine_line|#define PSYCHO_ECNTRL_CEEN&t;0x2000000000000000 /* Enable CE Interrupts         */
multiline_comment|/* Uncorrectable Error AFSR, AFAR holds low 40bits of faulting physical address. */
DECL|macro|PSYCHO_UEAFSR_PPIO
mdefine_line|#define PSYCHO_UEAFSR_PPIO&t;0x8000000000000000 /* Primary PIO is cause         */
DECL|macro|PSYCHO_UEAFSR_PDRD
mdefine_line|#define PSYCHO_UEAFSR_PDRD&t;0x4000000000000000 /* Primary DVMA read is cause   */
DECL|macro|PSYCHO_UEAFSR_PDWR
mdefine_line|#define PSYCHO_UEAFSR_PDWR&t;0x2000000000000000 /* Primary DVMA write is cause  */
DECL|macro|PSYCHO_UEAFSR_SPIO
mdefine_line|#define PSYCHO_UEAFSR_SPIO&t;0x1000000000000000 /* Secondary PIO is cause       */
DECL|macro|PSYCHO_UEAFSR_SDRD
mdefine_line|#define PSYCHO_UEAFSR_SDRD&t;0x0800000000000000 /* Secondary DVMA read is cause */
DECL|macro|PSYCHO_UEAFSR_SDWR
mdefine_line|#define PSYCHO_UEAFSR_SDWR&t;0x0400000000000000 /* Secondary DVMA write is cause*/
DECL|macro|PSYCHO_UEAFSR_RESV1
mdefine_line|#define PSYCHO_UEAFSR_RESV1&t;0x03ff000000000000 /* Reserved                     */
DECL|macro|PSYCHO_UEAFSR_BMSK
mdefine_line|#define PSYCHO_UEAFSR_BMSK&t;0x0000ffff00000000 /* Bytemask of failed transfer  */
DECL|macro|PSYCHO_UEAFSR_DOFF
mdefine_line|#define PSYCHO_UEAFSR_DOFF&t;0x00000000e0000000 /* Doubleword Offset            */
DECL|macro|PSYCHO_UEAFSR_MID
mdefine_line|#define PSYCHO_UEAFSR_MID&t;0x000000001f000000 /* UPA MID causing the fault    */
DECL|macro|PSYCHO_UEAFSR_BLK
mdefine_line|#define PSYCHO_UEAFSR_BLK&t;0x0000000000800000 /* Trans was block operation    */
DECL|macro|PSYCHO_UEAFSR_RESV2
mdefine_line|#define PSYCHO_UEAFSR_RESV2&t;0x00000000007fffff /* Reserved                     */
multiline_comment|/* Correctable Error AFSR, AFAR holds low 40bits of faulting physical address. */
DECL|macro|PSYCHO_CEAFSR_PPIO
mdefine_line|#define PSYCHO_CEAFSR_PPIO&t;0x8000000000000000 /* Primary PIO is cause         */
DECL|macro|PSYCHO_CEAFSR_PDRD
mdefine_line|#define PSYCHO_CEAFSR_PDRD&t;0x4000000000000000 /* Primary DVMA read is cause   */
DECL|macro|PSYCHO_CEAFSR_PDWR
mdefine_line|#define PSYCHO_CEAFSR_PDWR&t;0x2000000000000000 /* Primary DVMA write is cause  */
DECL|macro|PSYCHO_CEAFSR_SPIO
mdefine_line|#define PSYCHO_CEAFSR_SPIO&t;0x1000000000000000 /* Secondary PIO is cause       */
DECL|macro|PSYCHO_CEAFSR_SDRD
mdefine_line|#define PSYCHO_CEAFSR_SDRD&t;0x0800000000000000 /* Secondary DVMA read is cause */
DECL|macro|PSYCHO_CEAFSR_SDWR
mdefine_line|#define PSYCHO_CEAFSR_SDWR&t;0x0400000000000000 /* Secondary DVMA write is cause*/
DECL|macro|PSYCHO_CEAFSR_RESV1
mdefine_line|#define PSYCHO_CEAFSR_RESV1&t;0x0300000000000000 /* Reserved                     */
DECL|macro|PSYCHO_CEAFSR_ESYND
mdefine_line|#define PSYCHO_CEAFSR_ESYND&t;0x00ff000000000000 /* Syndrome Bits                */
DECL|macro|PSYCHO_CEAFSR_SIZE
mdefine_line|#define PSYCHO_CEAFSR_SIZE&t;0x0000ffff00000000 /* Bytemask of failed transfer  */
DECL|macro|PSYCHO_CEAFSR_DOFF
mdefine_line|#define PSYCHO_CEAFSR_DOFF&t;0x00000000e0000000 /* Double Offset                */
DECL|macro|PSYCHO_CEAFSR_MID
mdefine_line|#define PSYCHO_CEAFSR_MID&t;0x000000001f000000 /* UPA MID causing the fault    */
DECL|macro|PSYCHO_CEAFSR_BLK
mdefine_line|#define PSYCHO_CEAFSR_BLK&t;0x0000000000800000 /* Trans was block operation    */
DECL|macro|PSYCHO_CEAFSR_RESV2
mdefine_line|#define PSYCHO_CEAFSR_RESV2&t;0x00000000007fffff /* Reserved                     */
multiline_comment|/* PSYCHO Performance Monitor Register, the counter holds 2 32-bit event counters. */
DECL|macro|PSYCHO_PMCTRL_RESV3
mdefine_line|#define PSYCHO_PMCTRL_RESV3&t;0xffffffffffff0000 /* Reserved                     */
DECL|macro|PSYCHO_PMCTRL_CLR1
mdefine_line|#define PSYCHO_PMCTRL_CLR1&t;0x0000000000008000 /* Clear SEL1 counter           */
DECL|macro|PSYCHO_PMCTRL_RESV2
mdefine_line|#define PSYCHO_PMCTRL_RESV2&t;0x0000000000006000 /* Reserved                     */
DECL|macro|PSYCHO_PMCTRL_SEL1
mdefine_line|#define PSYCHO_PMCTRL_SEL1&t;0x0000000000001f00 /* Event source 1               */
DECL|macro|PSYCHO_PMCTRL_CLR0
mdefine_line|#define PSYCHO_PMCTRL_CLR0&t;0x0000000000000080 /* Clear SEL0 counter           */
DECL|macro|PSYCHO_PMCTRL_RESV1
mdefine_line|#define PSYCHO_PMCTRL_RESV1&t;0x0000000000000060 /* Reserved                     */
DECL|macro|PSYCHO_PMCTRL_SEL0
mdefine_line|#define PSYCHO_PMCTRL_SEL0&t;0x000000000000001f /* Event source 0               */
multiline_comment|/* SEL0/SEL1 each can take any one of the following values. */
DECL|macro|PMCTRL_SEL_NSDRA
mdefine_line|#define PMCTRL_SEL_NSDRA&t;0x00  /* # of streaming dvma reads for PCI A       */
DECL|macro|PMCTRL_SEL_NSDWA
mdefine_line|#define PMCTRL_SEL_NSDWA&t;0x01  /* # of streaming dvma writes for PCI A      */
DECL|macro|PMCTRL_SEL_NCDRA
mdefine_line|#define PMCTRL_SEL_NCDRA&t;0x02  /* # of consistent dvma reads for PCI A      */
DECL|macro|PMCTRL_SEL_NCDWA
mdefine_line|#define PMCTRL_SEL_NCDWA&t;0x03  /* # of consistent dvma writes for PCI A     */
DECL|macro|PMCTRL_SEL_SBMA
mdefine_line|#define PMCTRL_SEL_SBMA&t;&t;0x04  /* # of streaming buffer misses on PCI A     */
DECL|macro|PMCTRL_SEL_DCGA
mdefine_line|#define PMCTRL_SEL_DCGA&t;&t;0x05  /* # of DVMA granted cycles on PCI A         */
DECL|macro|PMCTRL_SEL_DWTA
mdefine_line|#define PMCTRL_SEL_DWTA&t;&t;0x06  /* # of DVMA words transferred on PCI A      */
DECL|macro|PMCTRL_SEL_CPIOA
mdefine_line|#define PMCTRL_SEL_CPIOA&t;0x07  /* # of PIO cycles used by PSYCHO on PCI A   */
DECL|macro|PMCTRL_SEL_NSDRB
mdefine_line|#define PMCTRL_SEL_NSDRB&t;0x08  /* # of streaming dvma reads for PCI B       */
DECL|macro|PMCTRL_SEL_NSDWB
mdefine_line|#define PMCTRL_SEL_NSDWB&t;0x09  /* # of streaming dvma writes for PCI B      */
DECL|macro|PMCTRL_SEL_NCDRB
mdefine_line|#define PMCTRL_SEL_NCDRB&t;0x0a  /* # of consistent dvma reads for PCI B      */
DECL|macro|PMCTRL_SEL_NCDWB
mdefine_line|#define PMCTRL_SEL_NCDWB&t;0x0b  /* # of consistent dvma writes for PCI B     */
DECL|macro|PMCTRL_SEL_SBMB
mdefine_line|#define PMCTRL_SEL_SBMB&t;&t;0x0c  /* # of streaming buffer misses on PCI B     */
DECL|macro|PMCTRL_SEL_DCGB
mdefine_line|#define PMCTRL_SEL_DCGB&t;&t;0x0d  /* # of DVMA granted cycles on PCI B         */
DECL|macro|PMCTRL_SEL_DWTB
mdefine_line|#define PMCTRL_SEL_DWTB&t;&t;0x0e  /* # of DVMA words transferred on PCI B      */
DECL|macro|PMCTRL_SEL_CPIOB
mdefine_line|#define PMCTRL_SEL_CPIOB&t;0x0f  /* # of PIO cycles used by PSYCHO on PCI B   */
DECL|macro|PMCTRL_SEL_TMISS
mdefine_line|#define PMCTRL_SEL_TMISS&t;0x10  /* # of IOMMU TLB misses                     */
DECL|macro|PMCTRL_SEL_IRQ
mdefine_line|#define PMCTRL_SEL_IRQ&t;&t;0x11  /* # of interrupts                           */
DECL|macro|PMCTRL_SEL_INACK
mdefine_line|#define PMCTRL_SEL_INACK&t;0x12  /* # of interrupt NACKs on UPA               */
DECL|macro|PMCTRL_SEL_PRD
mdefine_line|#define PMCTRL_SEL_PRD&t;&t;0x13  /* # of PIO reads                            */
DECL|macro|PMCTRL_SEL_PWR
mdefine_line|#define PMCTRL_SEL_PWR&t;&t;0x14  /* # of PIO writes                           */
DECL|macro|PMCTRL_SEL_MBT
mdefine_line|#define PMCTRL_SEL_MBT&t;&t;0x15  /* # of Merge Buffer transactions            */
DECL|macro|PMCTRL_SEL_PDRTA
mdefine_line|#define PMCTRL_SEL_PDRTA&t;0x16  /* # of PCI A DVMA tablewalk induced retries */
DECL|macro|PMCTRL_SEL_PDRSA
mdefine_line|#define PMCTRL_SEL_PDRSA&t;0x17  /* # of PCI A DVMA str buf induced retries   */
DECL|macro|PMCTRL_SEL_PDRTB
mdefine_line|#define PMCTRL_SEL_PDRTB&t;0x18  /* # of PCI B DVMA tablewalk induced retries */
DECL|macro|PMCTRL_SEL_PDRSB
mdefine_line|#define PMCTRL_SEL_PDRSB&t;0x19  /* # of PCI B DVMA str buf induced retries   */
multiline_comment|/* Values 0x1a --&gt; 0x1f are reserved. */
multiline_comment|/* PSYCHO PCI Control Register */
DECL|macro|PSYCHO_PCICTRL_RESV1
mdefine_line|#define PSYCHO_PCICTRL_RESV1&t;0xfffffff000000000 /* Reserved                     */
DECL|macro|PSYCHO_PCICTRL_SBH_ERR
mdefine_line|#define PSYCHO_PCICTRL_SBH_ERR&t;0x0000000800000000 /* Streaming byte hole error    */
DECL|macro|PSYCHO_PCICTRL_SERR
mdefine_line|#define PSYCHO_PCICTRL_SERR&t;0x0000000400000000 /* SERR signal asserted         */
DECL|macro|PSYCHO_PCICTRL_SPEED
mdefine_line|#define PSYCHO_PCICTRL_SPEED&t;0x0000000200000000 /* PCI speed (1 is U2P clock)   */
DECL|macro|PSYCHO_PCICTRL_RESV2
mdefine_line|#define PSYCHO_PCICTRL_RESV2&t;0x00000001ffc00000 /* Reserved                     */
DECL|macro|PSYCHO_PCICTRL_ARB_PARK
mdefine_line|#define PSYCHO_PCICTRL_ARB_PARK&t;0x0000000000200000 /* PCI arbitration parking      */
DECL|macro|PSYCHO_PCICTRL_RESV3
mdefine_line|#define PSYCHO_PCICTRL_RESV3&t;0x00000000001ff800 /* Reserved                     */
DECL|macro|PSYCHO_PCICTRL_SBH_INT
mdefine_line|#define PSYCHO_PCICTRL_SBH_INT&t;0x0000000000000400 /* Streaming byte hole int enab */
DECL|macro|PSYCHO_PCICTRL_WEN
mdefine_line|#define PSYCHO_PCICTRL_WEN&t;0x0000000000000200 /* Power Mgmt Wake Enable       */
DECL|macro|PSYCHO_PCICTRL_EEN
mdefine_line|#define PSYCHO_PCICTRL_EEN&t;0x0000000000000100 /* PCI Error Interrupt Enable   */
DECL|macro|PSYCHO_PCICTRL_RESV4
mdefine_line|#define PSYCHO_PCICTRL_RESV4&t;0x00000000000000c0 /* Reserved                     */
DECL|macro|PSYCHO_PCICTRL_AEN
mdefine_line|#define PSYCHO_PCICTRL_AEN&t;0x000000000000003f /* PCI DVMA Arbitration Enable  */
multiline_comment|/* PSYCHO PCI AFSR, AFAR holds low 40 bits of physical address causing the fault. */
DECL|macro|PSYCHO_PCIAFSR_PMA
mdefine_line|#define PSYCHO_PCIAFSR_PMA&t;0x8000000000000000 /* Primary Master Abort Error   */
DECL|macro|PSYCHO_PCIAFSR_PTA
mdefine_line|#define PSYCHO_PCIAFSR_PTA&t;0x4000000000000000 /* Primary Target Abort Error   */
DECL|macro|PSYCHO_PCIAFSR_PRTRY
mdefine_line|#define PSYCHO_PCIAFSR_PRTRY&t;0x2000000000000000 /* Primary Excessive Retries    */
DECL|macro|PSYCHO_PCIAFSR_PPERR
mdefine_line|#define PSYCHO_PCIAFSR_PPERR&t;0x1000000000000000 /* Primary Parity Error         */
DECL|macro|PSYCHO_PCIAFSR_SMA
mdefine_line|#define PSYCHO_PCIAFSR_SMA&t;0x0800000000000000 /* Secondary Master Abort Error */
DECL|macro|PSYCHO_PCIAFSR_STA
mdefine_line|#define PSYCHO_PCIAFSR_STA&t;0x0400000000000000 /* Secondary Target Abort Error */
DECL|macro|PSYCHO_PCIAFSR_SRTRY
mdefine_line|#define PSYCHO_PCIAFSR_SRTRY&t;0x0200000000000000 /* Secondary Excessive Retries  */
DECL|macro|PSYCHO_PCIAFSR_SPERR
mdefine_line|#define PSYCHO_PCIAFSR_SPERR&t;0x0100000000000000 /* Secondary Parity Error       */
DECL|macro|PSYCHO_PCIAFSR_RESV1
mdefine_line|#define PSYCHO_PCIAFSR_RESV1&t;0x00ff000000000000 /* Reserved                     */
DECL|macro|PSYCHO_PCIAFSR_SIZE
mdefine_line|#define PSYCHO_PCIAFSR_SIZE&t;0x0000ffff00000000 /* Bytemask of failed transfer  */
DECL|macro|PSYCHO_PCIAFSR_BLK
mdefine_line|#define PSYCHO_PCIAFSR_BLK&t;0x0000000080000000 /* Trans was block operation    */
DECL|macro|PSYCHO_PCIAFSR_RESV2
mdefine_line|#define PSYCHO_PCIAFSR_RESV2&t;0x0000000040000000 /* Reserved                     */
DECL|macro|PSYCHO_PCIAFSR_MID
mdefine_line|#define PSYCHO_PCIAFSR_MID&t;0x000000003e000000 /* MID causing the error        */
DECL|macro|PSYCHO_PCIAFSR_RESV3
mdefine_line|#define PSYCHO_PCIAFSR_RESV3&t;0x0000000001ffffff /* Reserved                     */
multiline_comment|/* PSYCHO Diagnostic Register. */
DECL|macro|PSYCHO_PSYDIAG_RESV
mdefine_line|#define PSYCHO_PSYDIAG_RESV&t;0xffffffffffffff80 /* Reserved                     */
DECL|macro|PSYCHO_PCIDIAG_DRETRY
mdefine_line|#define PSYCHO_PCIDIAG_DRETRY&t;0x0000000000000040 /* Disable retry limit          */
DECL|macro|PSYCHO_PCIDIAG_DISYNC
mdefine_line|#define PSYCHO_PCIDIAG_DISYNC&t;0x0000000000000020 /* Disable DMA wr / irq sync    */
DECL|macro|PSYCHO_PCIDIAG_DDWSYNC
mdefine_line|#define PSYCHO_PCIDIAG_DDWSYNC&t;0x0000000000000010 /* Disable DMA wr / PIO rd sync */
DECL|macro|PSYCHO_PCIDIAG_IDDPAR
mdefine_line|#define PSYCHO_PCIDIAG_IDDPAR&t;0x0000000000000008 /* Invert DMA data parity       */
DECL|macro|PSYCHO_PCIDIAG_IPDPAR
mdefine_line|#define PSYCHO_PCIDIAG_IPDPAR&t;0x0000000000000004 /* Invert PIO data parity       */
DECL|macro|PSYCHO_PCIDIAG_IPAPAR
mdefine_line|#define PSYCHO_PCIDIAG_IPAPAR&t;0x0000000000000002 /* Invert PIO address parity    */
DECL|macro|PSYCHO_PCIDIAG_LPBACK
mdefine_line|#define PSYCHO_PCIDIAG_LPBACK&t;0x0000000000000001 /* Enable loopback mode         */
multiline_comment|/* IOMMU things defined fully in asm-sparc64/iommu.h */
multiline_comment|/* Streaming Buffer Control Register */
DECL|macro|PSYCHO_SBUFCTRL_RESV
mdefine_line|#define PSYCHO_SBUFCTRL_RESV&t;0xffffffffffffff80 /* Reserved                     */
DECL|macro|PSYCHO_SBUFCTRL_LRU_LP
mdefine_line|#define PSYCHO_SBUFCTRL_LRU_LP&t;0x0000000000000070 /* LRU Lock Pointer             */
DECL|macro|PSYCHO_SBUFCTRL_LRU_LE
mdefine_line|#define PSYCHO_SBUFCTRL_LRU_LE&t;0x0000000000000008 /* LRU Lock Enable              */
DECL|macro|PSYCHO_SBUFCTRL_RR_DIS
mdefine_line|#define PSYCHO_SBUFCTRL_RR_DIS&t;0x0000000000000004 /* Rerun Disable                */
DECL|macro|PSYCHO_SBUFCTRL_DE
mdefine_line|#define PSYCHO_SBUFCTRL_DE&t;0x0000000000000002 /* Diag Mode Enable             */
DECL|macro|PSYCHO_SBUFCTRL_SB_EN
mdefine_line|#define PSYCHO_SBUFCTRL_SB_EN&t;0x0000000000000001 /* Streaming Buffer Enable      */
multiline_comment|/* Streaming Buffer Page Invalidate/Flush Register */
DECL|macro|PSYCHO_SBUFFLUSH_ADDR
mdefine_line|#define PSYCHO_SBUFFLUSH_ADDR&t;0x00000000ffffe000 /* DVMA Page to be flushed      */
DECL|macro|PSYCHO_SBUFFLUSH_RESV
mdefine_line|#define PSYCHO_SBUFFLUSH_RESV&t;0x0000000000001fff /* Ignored bits                 */
multiline_comment|/* Streaming Buffer Flush Synchronization Register */
DECL|macro|PSYCHO_SBUFSYNC_ADDR
mdefine_line|#define PSYCHO_SBUFSYNC_ADDR&t;0x000001ffffffffc0 /* Physical address to update   */
DECL|macro|PSYCHO_SBUFSYNC_RESV
mdefine_line|#define PSYCHO_SBUFSYNC_RESV&t;0x000000000000003f /* Ignored bits                 */
multiline_comment|/* DMA Scoreboard Diagnostic Register(s) */
DECL|macro|PSYCHO_DSCORE_VALID
mdefine_line|#define PSYCHO_DSCORE_VALID&t;0x8000000000000000 /* Entry is valid               */
DECL|macro|PSYCHO_DSCORE_C
mdefine_line|#define PSYCHO_DSCORE_C&t;&t;0x4000000000000000 /* Transaction cacheable        */
DECL|macro|PSYCHO_DSCORE_READ
mdefine_line|#define PSYCHO_DSCORE_READ&t;0x2000000000000000 /* Transaction was a read       */
DECL|macro|PSYCHO_DSCORE_TAG
mdefine_line|#define PSYCHO_DSCORE_TAG&t;0x1f00000000000000 /* Transaction ID               */
DECL|macro|PSYCHO_DSCORE_ADDR
mdefine_line|#define PSYCHO_DSCORE_ADDR&t;0x00fffffffff80000 /* Transaction PADDR            */
DECL|macro|PSYCHO_DSCORE_BMSK
mdefine_line|#define PSYCHO_DSCORE_BMSK&t;0x000000000007fff8 /* Bytemask of pending transfer */
DECL|macro|PSYCHO_DSCORE_SRC
mdefine_line|#define PSYCHO_DSCORE_SRC&t;0x0000000000000007 /* Transaction source           */
multiline_comment|/* PSYCHO Interrupt mapping register(s). */
DECL|macro|PSYCHO_IMAP_RESV1
mdefine_line|#define PSYCHO_IMAP_RESV1&t;0xffffffff00000000 /* Reserved                     */
DECL|macro|PSYCHO_IMAP_VALID
mdefine_line|#define PSYCHO_IMAP_VALID&t;0x0000000080000000 /* This enables delivery.&t;   */
DECL|macro|PSYCHO_IMAP_TID
mdefine_line|#define PSYCHO_IMAP_TID&t;&t;0x000000007c000000 /* Target ID (MID to send it to)*/
DECL|macro|PSYCHO_IMAP_RESV2
mdefine_line|#define PSYCHO_IMAP_RESV2&t;0x0000000003fff800 /* Reserved &t;&t;&t;   */
DECL|macro|PSYCHO_IMAP_IGN
mdefine_line|#define PSYCHO_IMAP_IGN&t;&t;0x00000000000007c0 /* Interrupt Group Number.&t;   */
DECL|macro|PSYCHO_IMAP_INO
mdefine_line|#define PSYCHO_IMAP_INO&t;&t;0x000000000000003f /* Interrupt Number Offset.&t;   */
DECL|macro|PSYCHO_IMAP_INR
mdefine_line|#define PSYCHO_IMAP_INR&t;&t;0x00000000000007ff /* Interrupt # (Gfx/UPA_slave)  */
multiline_comment|/* PSYCHO Interrupt clear pseudo register(s). */
DECL|macro|PSYCHO_ICLR_RESV1
mdefine_line|#define PSYCHO_ICLR_RESV1 &t;0xfffffffffffffff0 /* Reserved&t;&t;&t;   */
DECL|macro|PSYCHO_ICLR_IDLE
mdefine_line|#define PSYCHO_ICLR_IDLE&t;0x0000000000000000 /* Transition to idle state.&t;   */
DECL|macro|PSYCHO_ICLR_TRANSMIT
mdefine_line|#define PSYCHO_ICLR_TRANSMIT&t;0x0000000000000001 /* Transition to transmit state */
DECL|macro|PSYCHO_ICLR_RESV2
mdefine_line|#define PSYCHO_ICLR_RESV2&t;0x0000000000000002 /* Reserved.&t;&t;&t;   */
DECL|macro|PSYCHO_ICLR_PENDING
mdefine_line|#define PSYCHO_ICLR_PENDING&t;0x0000000000000003 /* Transition to pending state. */
multiline_comment|/* PSYCHO Interrupt Retry Timer register. */
DECL|macro|PSYCHO_IRETRY_LIMIT
mdefine_line|#define PSYCHO_IRETRY_LIMIT&t;0x00000000000fffff /* The retry interval.&t;   */
multiline_comment|/* PSYCHO Interrupt State registers. XXX fields to be documented later */
multiline_comment|/* PSYCHO Counter register. XXX fields to be documented later */
multiline_comment|/* PSYCHO Limit register. XXX fields to be documented later */
multiline_comment|/* PSYCHO Performance Monitor Control register. XXX fields to be documented later */
multiline_comment|/* PSYCHO Performance Monitor Counter register. XXX fields to be documented later */
macro_line|#endif /* !(__SPARC64_PSYCHO_H) */
eof
