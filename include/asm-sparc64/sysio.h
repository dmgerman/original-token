multiline_comment|/* $Id: sysio.h,v 1.6 1997/08/15 06:44:53 davem Exp $&n; * sysio.h: UltraSparc sun5 specific SBUS definitions.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SYSIO_H
DECL|macro|__SPARC64_SYSIO_H
mdefine_line|#define __SPARC64_SYSIO_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* SUN5 SYSIO Register Set, one per controller probed. */
DECL|struct|sysio_regs
r_struct
id|sysio_regs
(brace
DECL|member|upa_id
multiline_comment|/*0x0000*/
id|u64
id|upa_id
suffix:semicolon
multiline_comment|/* SYSIO UPA Port ID Register&t;&t;*/
DECL|member|upa_cfg
multiline_comment|/*0x0008*/
id|u64
id|upa_cfg
suffix:semicolon
multiline_comment|/* SYSIO UPA Config Register&t;&t;*/
DECL|member|control
multiline_comment|/*0x0010*/
id|u64
id|control
suffix:semicolon
multiline_comment|/* SYSIO Control Register&t;&t;*/
DECL|member|_unused1
multiline_comment|/*0x0018*/
id|u64
id|_unused1
suffix:semicolon
DECL|member|ecc_control
multiline_comment|/*0x0020*/
id|u64
id|ecc_control
suffix:semicolon
multiline_comment|/* ECC Control Register&t;&t;&t;*/
DECL|member|_unused2
multiline_comment|/*0x0028*/
id|u64
id|_unused2
suffix:semicolon
multiline_comment|/* Uncorrectable Error Fault Registers */
DECL|member|ue_afsr
multiline_comment|/*0x0030*/
id|u64
id|ue_afsr
suffix:semicolon
multiline_comment|/* UE Async Fault Status&t;&t;*/
DECL|member|ue_afar
multiline_comment|/*0x0038*/
id|u64
id|ue_afar
suffix:semicolon
multiline_comment|/* UE Async Fault Address&t;&t;*/
multiline_comment|/* Correctable Error Fault Registers */
DECL|member|ce_afsr
multiline_comment|/*0x0040*/
id|u64
id|ce_afsr
suffix:semicolon
multiline_comment|/* CE Async Fault Status&t;&t;*/
DECL|member|ce_afar
multiline_comment|/*0x0048*/
id|u64
id|ce_afar
suffix:semicolon
multiline_comment|/* CE Async Fault Address&t;&t;*/
DECL|member|__pad0
id|u64
id|__pad0
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
DECL|member|__pad1
id|u64
id|__pad1
(braket
l_int|0x3de
)braket
suffix:semicolon
multiline_comment|/* SBUS Module Registers */
DECL|member|sbus_control
multiline_comment|/*0x2000*/
id|u64
id|sbus_control
suffix:semicolon
multiline_comment|/* SBUS Control Register&t;&t;*/
DECL|member|_unused3
multiline_comment|/*0x2008*/
id|u64
id|_unused3
suffix:semicolon
DECL|member|sbus_afsr
multiline_comment|/*0x2010*/
id|u64
id|sbus_afsr
suffix:semicolon
multiline_comment|/* SBUS Async Fault Status&t;&t;*/
DECL|member|sbus_afar
multiline_comment|/*0x2018*/
id|u64
id|sbus_afar
suffix:semicolon
multiline_comment|/* SBUS Async Fault Address&t;&t;*/
multiline_comment|/* SBUS Slot Configuration Registers.&n;&t;&t; * On Fusion/Electron/Pulsar desktops/servers slots 4--&gt;6&n;&t;&t; * are for on-board devices, in particular for Electron/Pulsar&n;&t;&t; * they are:&n;&t;&t; *&n;&t;&t; *&t;slot 4) Audio&n;&t;&t; *&t;slot 5) MACIO&n;&t;&t; *&t;slot 6) SLAVIO&n;&t;&t; *&n;&t;&t; * On Sunfire/Starfire/Wildfire enterprise boxen these upper slots&n;&t;&t; * are unused.&n;&t;&t; */
DECL|member|sbus_s0cfg
multiline_comment|/*0x2020*/
id|u64
id|sbus_s0cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 0 Config&t;&t;&t;*/
DECL|member|sbus_s1cfg
multiline_comment|/*0x2028*/
id|u64
id|sbus_s1cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 1 Config&t;&t;&t;*/
DECL|member|sbus_s2cfg
multiline_comment|/*0x2030*/
id|u64
id|sbus_s2cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 2 Config&t;&t;&t;*/
DECL|member|sbus_s3cfg
multiline_comment|/*0x2038*/
id|u64
id|sbus_s3cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 3 Config&t;&t;&t;*/
DECL|member|sbus_s4cfg
multiline_comment|/*0x2040*/
id|u64
id|sbus_s4cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 4 Config&t;&t;&t;*/
DECL|member|sbus_s5cfg
multiline_comment|/*0x2048*/
id|u64
id|sbus_s5cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 5 Config&t;&t;&t;*/
DECL|member|sbus_s6cfg
multiline_comment|/*0x2050*/
id|u64
id|sbus_s6cfg
suffix:semicolon
multiline_comment|/* SBUS Slot 6 Config&t;&t;&t;*/
DECL|member|__pad2
id|u64
id|__pad2
(braket
l_int|0x75
)braket
suffix:semicolon
multiline_comment|/* SBUS IOMMU lives here */
DECL|member|iommu_control
multiline_comment|/*0x2400*/
id|u64
id|iommu_control
suffix:semicolon
multiline_comment|/* IOMMU Control&t;&t;&t;*/
DECL|member|iommu_tsbbase
multiline_comment|/*0x2408*/
id|u64
id|iommu_tsbbase
suffix:semicolon
multiline_comment|/* IOMMU TSB Base&t;&t;&t;*/
DECL|member|iommu_flush
multiline_comment|/*0x2410*/
id|u64
id|iommu_flush
suffix:semicolon
multiline_comment|/* IOMMU Flush Register&t;&t;&t;*/
DECL|member|__pad3
id|u64
id|__pad3
(braket
l_int|0x7d
)braket
suffix:semicolon
multiline_comment|/* SBUS/IOMMU Streaming Buffer Registers */
DECL|member|sbuf_control
multiline_comment|/*0x2800*/
id|u64
id|sbuf_control
suffix:semicolon
multiline_comment|/* StrBuffer Control&t;&t;&t;*/
DECL|member|sbuf_pflush
multiline_comment|/*0x2808*/
id|u64
id|sbuf_pflush
suffix:semicolon
multiline_comment|/* StrBuffer Page Flush&t;&t;&t;*/
DECL|member|sbuf_fsync
multiline_comment|/*0x2810*/
id|u64
id|sbuf_fsync
suffix:semicolon
multiline_comment|/* StrBuffer Flush Synchronization Reg&t;*/
DECL|member|__pad4
id|u64
id|__pad4
(braket
l_int|0x7d
)braket
suffix:semicolon
multiline_comment|/* Interrupt mapping/control registers */
DECL|member|_uim0
DECL|member|imap_slot0
multiline_comment|/*0x2c00*/
id|u32
id|_uim0
comma
id|imap_slot0
suffix:semicolon
multiline_comment|/* SBUS Slot 0 Int Mapping&t;*/
DECL|member|_uim1
DECL|member|imap_slot1
multiline_comment|/*0x2c08*/
id|u32
id|_uim1
comma
id|imap_slot1
suffix:semicolon
multiline_comment|/* SBUS Slot 1 Int Mapping&t;*/
DECL|member|_uim2
DECL|member|imap_slot2
multiline_comment|/*0x2c10*/
id|u32
id|_uim2
comma
id|imap_slot2
suffix:semicolon
multiline_comment|/* SBUS Slot 2 Int Mapping&t;*/
DECL|member|_uim3
DECL|member|imap_slot3
multiline_comment|/*0x2c18*/
id|u32
id|_uim3
comma
id|imap_slot3
suffix:semicolon
multiline_comment|/* SBUS Slot 3 Int Mapping&t;*/
multiline_comment|/* Interrupt Retry Timer. */
DECL|member|_irpad
DECL|member|irq_retry
multiline_comment|/*0x2c20*/
id|u32
id|_irpad
comma
id|irq_retry
suffix:semicolon
DECL|member|__pad5
id|u64
id|__pad5
(braket
l_int|0x7b
)braket
suffix:semicolon
multiline_comment|/* The following are only used on Fusion/Electron/Pulsar&n;&t;&t; * desktop systems, they mean nothing on Sunfire/Starfire/Wildfire&n;&t;&t; */
DECL|member|_uis
DECL|member|imap_scsi
multiline_comment|/*0x3000*/
id|u32
id|_uis
comma
id|imap_scsi
suffix:semicolon
multiline_comment|/* SCSI Int Mapping&t;&t;*/
DECL|member|_uie
DECL|member|imap_eth
multiline_comment|/*0x3008*/
id|u32
id|_uie
comma
id|imap_eth
suffix:semicolon
multiline_comment|/* Ethernet Int Mapping&t;&t;*/
DECL|member|_uip
DECL|member|imap_bpp
multiline_comment|/*0x3010*/
id|u32
id|_uip
comma
id|imap_bpp
suffix:semicolon
multiline_comment|/* Parallel Port Int Mapping&t;*/
DECL|member|_uia
DECL|member|imap_audio
multiline_comment|/*0x3018*/
id|u32
id|_uia
comma
id|imap_audio
suffix:semicolon
multiline_comment|/* Audio Int Mapping&t;&t;*/
DECL|member|_uipf
DECL|member|imap_pfail
multiline_comment|/*0x3020*/
id|u32
id|_uipf
comma
id|imap_pfail
suffix:semicolon
multiline_comment|/* Power Fail Int Mapping&t;*/
DECL|member|_uik
DECL|member|imap_kms
multiline_comment|/*0x3028*/
id|u32
id|_uik
comma
id|imap_kms
suffix:semicolon
multiline_comment|/* Kbd/Mouse/Serial Int Mapping&t;*/
DECL|member|_uif
DECL|member|imap_flpy
multiline_comment|/*0x3030*/
id|u32
id|_uif
comma
id|imap_flpy
suffix:semicolon
multiline_comment|/* Floppy Int Mapping&t;&t;*/
DECL|member|_uishw
DECL|member|imap_shw
multiline_comment|/*0x3038*/
id|u32
id|_uishw
comma
id|imap_shw
suffix:semicolon
multiline_comment|/* Spare HW Int Mapping&t;&t;*/
DECL|member|_uikbd
DECL|member|imap_kbd
multiline_comment|/*0x3040*/
id|u32
id|_uikbd
comma
id|imap_kbd
suffix:semicolon
multiline_comment|/* Kbd Only Int Mapping&t;&t;*/
DECL|member|_uims
DECL|member|imap_ms
multiline_comment|/*0x3048*/
id|u32
id|_uims
comma
id|imap_ms
suffix:semicolon
multiline_comment|/* Mouse Only Int Mapping&t;*/
DECL|member|_uiser
DECL|member|imap_ser
multiline_comment|/*0x3050*/
id|u32
id|_uiser
comma
id|imap_ser
suffix:semicolon
multiline_comment|/* Serial Only Int Mapping&t;*/
DECL|member|_imap_unused
multiline_comment|/*0x3058*/
id|u64
id|_imap_unused
suffix:semicolon
DECL|member|_uit0
DECL|member|imap_tim0
multiline_comment|/*0x3060*/
id|u32
id|_uit0
comma
id|imap_tim0
suffix:semicolon
multiline_comment|/* Timer 0 Int Mapping&t;&t;*/
DECL|member|_uit1
DECL|member|imap_tim1
multiline_comment|/*0x3068*/
id|u32
id|_uit1
comma
id|imap_tim1
suffix:semicolon
multiline_comment|/* Timer 1 Int Mapping&t;&t;*/
DECL|member|_uiue
DECL|member|imap_ue
multiline_comment|/*0x3070*/
id|u32
id|_uiue
comma
id|imap_ue
suffix:semicolon
multiline_comment|/* UE Int Mapping&t;&t;*/
DECL|member|_uice
DECL|member|imap_ce
multiline_comment|/*0x3078*/
id|u32
id|_uice
comma
id|imap_ce
suffix:semicolon
multiline_comment|/* CE Int Mapping&t;&t;*/
DECL|member|_uisbe
DECL|member|imap_sberr
multiline_comment|/*0x3080*/
id|u32
id|_uisbe
comma
id|imap_sberr
suffix:semicolon
multiline_comment|/* SBUS Err Int Mapping&t;&t;*/
DECL|member|_uipm
DECL|member|imap_pmgmt
multiline_comment|/*0x3088*/
id|u32
id|_uipm
comma
id|imap_pmgmt
suffix:semicolon
multiline_comment|/* Power Mgmt Int Mapping&t;*/
DECL|member|_uigfx
DECL|member|imap_gfx
multiline_comment|/*0x3090*/
id|u32
id|_uigfx
comma
id|imap_gfx
suffix:semicolon
multiline_comment|/* OB Graphics Int Mapping&t;*/
DECL|member|_uieupa
DECL|member|imap_eupa
multiline_comment|/*0x3098*/
id|u32
id|_uieupa
comma
id|imap_eupa
suffix:semicolon
multiline_comment|/* UPA Expansion Int Mapping&t;*/
DECL|member|__pad6
id|u64
id|__pad6
(braket
l_int|0x6c
)braket
suffix:semicolon
multiline_comment|/* Interrupt Clear Registers */
DECL|member|__ucu0
DECL|member|iclr_unused0
multiline_comment|/*0x3400*/
id|u32
id|__ucu0
comma
id|iclr_unused0
suffix:semicolon
DECL|member|_ucs0
DECL|member|iclr_slot0
multiline_comment|/*0x3408*/
id|u32
id|_ucs0
comma
id|iclr_slot0
suffix:semicolon
DECL|member|__pad7
id|u64
id|__pad7
(braket
l_int|0x7
)braket
suffix:semicolon
DECL|member|_ucs1
DECL|member|iclr_slot1
multiline_comment|/*0x3448*/
id|u32
id|_ucs1
comma
id|iclr_slot1
suffix:semicolon
DECL|member|__pad8
id|u64
id|__pad8
(braket
l_int|0x7
)braket
suffix:semicolon
DECL|member|_ucs2
DECL|member|iclr_slot2
multiline_comment|/*0x3488*/
id|u32
id|_ucs2
comma
id|iclr_slot2
suffix:semicolon
DECL|member|__pad9
id|u64
id|__pad9
(braket
l_int|0x7
)braket
suffix:semicolon
DECL|member|_ucs3
DECL|member|iclr_slot3
multiline_comment|/*0x34c8*/
id|u32
id|_ucs3
comma
id|iclr_slot3
suffix:semicolon
DECL|member|__pad10
id|u64
id|__pad10
(braket
l_int|0x66
)braket
suffix:semicolon
DECL|member|_ucscsi
DECL|member|iclr_scsi
multiline_comment|/*0x3800*/
id|u32
id|_ucscsi
comma
id|iclr_scsi
suffix:semicolon
DECL|member|_uceth
DECL|member|iclr_eth
multiline_comment|/*0x3808*/
id|u32
id|_uceth
comma
id|iclr_eth
suffix:semicolon
DECL|member|_ucbpp
DECL|member|iclr_bpp
multiline_comment|/*0x3810*/
id|u32
id|_ucbpp
comma
id|iclr_bpp
suffix:semicolon
DECL|member|_ucaudio
DECL|member|iclr_audio
multiline_comment|/*0x3818*/
id|u32
id|_ucaudio
comma
id|iclr_audio
suffix:semicolon
DECL|member|_ucpfail
DECL|member|iclr_pfail
multiline_comment|/*0x3820*/
id|u32
id|_ucpfail
comma
id|iclr_pfail
suffix:semicolon
DECL|member|_uckms
DECL|member|iclr_kms
multiline_comment|/*0x3828*/
id|u32
id|_uckms
comma
id|iclr_kms
suffix:semicolon
DECL|member|_ucflpy
DECL|member|iclr_flpt
multiline_comment|/*0x3830*/
id|u32
id|_ucflpy
comma
id|iclr_flpt
suffix:semicolon
DECL|member|_ucshw
DECL|member|iclr_shw
multiline_comment|/*0x3838*/
id|u32
id|_ucshw
comma
id|iclr_shw
suffix:semicolon
DECL|member|_uckbd
DECL|member|iclr_kbd
multiline_comment|/*0x3840*/
id|u32
id|_uckbd
comma
id|iclr_kbd
suffix:semicolon
DECL|member|_ucms
DECL|member|iclr_ms
multiline_comment|/*0x3848*/
id|u32
id|_ucms
comma
id|iclr_ms
suffix:semicolon
DECL|member|_ucser
DECL|member|iclr_ser
multiline_comment|/*0x3850*/
id|u32
id|_ucser
comma
id|iclr_ser
suffix:semicolon
DECL|member|iclr_unused1
multiline_comment|/*0x3858*/
id|u64
id|iclr_unused1
suffix:semicolon
DECL|member|_uctim0
DECL|member|iclr_tim0
multiline_comment|/*0x3860*/
id|u32
id|_uctim0
comma
id|iclr_tim0
suffix:semicolon
DECL|member|_uctim1
DECL|member|iclr_tim1
multiline_comment|/*0x3868*/
id|u32
id|_uctim1
comma
id|iclr_tim1
suffix:semicolon
DECL|member|_ucue
DECL|member|iclr_ue
multiline_comment|/*0x3870*/
id|u32
id|_ucue
comma
id|iclr_ue
suffix:semicolon
DECL|member|_ucce
DECL|member|iclr_ce
multiline_comment|/*0x3878*/
id|u32
id|_ucce
comma
id|iclr_ce
suffix:semicolon
DECL|member|_ucserr
DECL|member|iclr_serr
multiline_comment|/*0x3880*/
id|u32
id|_ucserr
comma
id|iclr_serr
suffix:semicolon
DECL|member|_ucpmgmt
DECL|member|iclr_pmgmt
multiline_comment|/*0x3888*/
id|u32
id|_ucpmgmt
comma
id|iclr_pmgmt
suffix:semicolon
DECL|member|__pad11
id|u64
id|__pad11
(braket
l_int|0x6e
)braket
suffix:semicolon
multiline_comment|/* Counters/Timers */
DECL|member|tim0_cnt
multiline_comment|/*0x3c00*/
id|u64
id|tim0_cnt
suffix:semicolon
DECL|member|tim0_lim
multiline_comment|/*0x3c08*/
id|u64
id|tim0_lim
suffix:semicolon
DECL|member|tim1_cnt
multiline_comment|/*0x3c10*/
id|u64
id|tim1_cnt
suffix:semicolon
DECL|member|tim1_lim
multiline_comment|/*0x3c18*/
id|u64
id|tim1_lim
suffix:semicolon
DECL|member|__pad12
id|u64
id|__pad12
(braket
l_int|0x7c
)braket
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diagnostic Registers */
DECL|member|dscore_reg0
multiline_comment|/*0x4000*/
id|u64
id|dscore_reg0
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diag Reg 0&t;&t;*/
DECL|member|dscore_reg1
multiline_comment|/*0x4008*/
id|u64
id|dscore_reg1
suffix:semicolon
multiline_comment|/* DMA Scoreboard Diag Reg 1&t;&t;*/
DECL|member|__pad13
id|u64
id|__pad13
(braket
l_int|0x7e
)braket
suffix:semicolon
multiline_comment|/* SBUS IOMMU Diagnostic Registers */
DECL|member|sbus_vdiag
multiline_comment|/*0x4400*/
id|u64
id|sbus_vdiag
suffix:semicolon
multiline_comment|/* SBUS VADDR Diagnostic Register&t;*/
DECL|member|sbus_tcompare
multiline_comment|/*0x4408*/
id|u64
id|sbus_tcompare
suffix:semicolon
multiline_comment|/* SBUS IOMMU TLB Tag Compare&t;&t;*/
DECL|member|__pad14
id|u64
id|__pad14
(braket
l_int|0x1e
)braket
suffix:semicolon
multiline_comment|/* More IOMMU diagnostic things */
DECL|member|iommu_lru
multiline_comment|/*0x4500*/
id|u64
id|iommu_lru
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* IOMMU LRU Queue Diagnostic Access&t;*/
DECL|member|iommu_tag
multiline_comment|/*0x4580*/
id|u64
id|iommu_tag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* IOMMU TLB Tag Diagnostic Access&t;*/
DECL|member|iommu_data
multiline_comment|/*0x4600*/
id|u64
id|iommu_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* IOMMU TLB Data RAM Diagnostic Access&t;*/
DECL|member|__pad15
id|u64
id|__pad15
(braket
l_int|0x20
)braket
suffix:semicolon
multiline_comment|/* Interrupt State Diagnostics */
DECL|member|sbus_istate
multiline_comment|/*0x4800*/
id|u64
id|sbus_istate
suffix:semicolon
DECL|member|obio_istate
multiline_comment|/*0x4808*/
id|u64
id|obio_istate
suffix:semicolon
DECL|member|__pad16
id|u64
id|__pad16
(braket
l_int|0xfe
)braket
suffix:semicolon
multiline_comment|/* Streaming Buffer Diagnostic Area */
DECL|member|sbuf_data
multiline_comment|/*0x5000*/
id|u64
id|sbuf_data
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Data Ram Diagnostic&t;*/
DECL|member|sbuf_errs
multiline_comment|/*0x5400*/
id|u64
id|sbuf_errs
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Error Status Diagnostics&t;*/
DECL|member|sbuf_ptag
multiline_comment|/*0x5800*/
id|u64
id|sbuf_ptag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Page Tag Diagnostics&t;*/
DECL|member|_unusedXXX
multiline_comment|/*0x5880*/
id|u64
id|_unusedXXX
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sbuf_ltag
multiline_comment|/*0x5900*/
id|u64
id|sbuf_ltag
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* StrBuffer Line Tag Diagnostics&t;*/
)brace
suffix:semicolon
multiline_comment|/* SYSIO UPA Port ID */
DECL|macro|SYSIO_UPPID_FESC
mdefine_line|#define SYSIO_UPPID_FESC&t;0xff00000000000000 /* FCode escape, 0xfc           */
DECL|macro|SYSIO_UPPID_RESV1
mdefine_line|#define SYSIO_UPPID_RESV1&t;0x00fffff800000000 /* Reserved                     */
DECL|macro|SYSIO_UPPID_ENV
mdefine_line|#define SYSIO_UPPID_ENV&t;&t;0x0000000400000000 /* Cannot generate ECC          */
DECL|macro|SYSIO_UPPID_ORD
mdefine_line|#define SYSIO_UPPID_ORD&t;&t;0x0000000200000000 /* One Outstanding Read         */
DECL|macro|SYSIO_UPPID_RESV2
mdefine_line|#define SYSIO_UPPID_RESV2&t;0x0000000180000000 /* Reserved                     */
DECL|macro|SYSIO_UPPID_PDQ
mdefine_line|#define SYSIO_UPPID_PDQ&t;&t;0x000000007e000000 /* Data Queue size              */
DECL|macro|SYSIO_UPPID_PRQ
mdefine_line|#define SYSIO_UPPID_PRQ&t;&t;0x0000000001e00000 /* Request Queue size           */
DECL|macro|SYSIO_UPPID_UCAP
mdefine_line|#define SYSIO_UPPID_UCAP&t;0x00000000001f0000 /* UPA Capabilities             */
DECL|macro|SYSIO_UPPID_JEDEC
mdefine_line|#define SYSIO_UPPID_JEDEC&t;0x000000000000ffff /* JEDEC ID for SYSIO           */
multiline_comment|/* SYSIO UPA Configuration Register */
DECL|macro|SYSIO_UPCFG_RESV
mdefine_line|#define SYSIO_UPCFG_RESV&t;0xffffffffffffff00 /* Reserved                     */
DECL|macro|SYSIO_UPCFG_SCIQ1
mdefine_line|#define SYSIO_UPCFG_SCIQ1&t;0x00000000000000f0 /* Unused, always zero          */
DECL|macro|SYSIO_UPCFG_SCIQ2
mdefine_line|#define SYSIO_UPCFG_SCIQ2&t;0x000000000000000f /* Requests Queue size (0x2)    */
multiline_comment|/* SYSIO Control Register */
DECL|macro|SYSIO_CONTROL_IMPL
mdefine_line|#define SYSIO_CONTROL_IMPL&t;0xf000000000000000 /* Implementation of this SYSIO */
DECL|macro|SYSIO_CONTROL_VER
mdefine_line|#define SYSIO_CONTROL_VER&t;0x0f00000000000000 /* Version of this SYSIO        */
DECL|macro|SYSIO_CONTROL_MID
mdefine_line|#define SYSIO_CONTROL_MID&t;0x00f8000000000000 /* UPA Module ID of SYSIO       */
DECL|macro|SYSIO_CONTROL_IGN
mdefine_line|#define SYSIO_CONTROL_IGN&t;0x0007c00000000000 /* Interrupt Group Number       */
DECL|macro|SYSIO_CONTROL_RESV
mdefine_line|#define SYSIO_CONTROL_RESV      0x00003ffffffffff0 /* Reserved                     */
DECL|macro|SYSIO_CONTROL_APCKEN
mdefine_line|#define SYSIO_CONTROL_APCKEN&t;0x0000000000000008 /* Address Parity Check Enable  */
DECL|macro|SYSIO_CONTROL_APERR
mdefine_line|#define SYSIO_CONTROL_APERR&t;0x0000000000000004 /* Incoming System Addr Parerr  */
DECL|macro|SYSIO_CONTROL_IAP
mdefine_line|#define SYSIO_CONTROL_IAP&t;0x0000000000000002 /* Invert UPA Parity            */
DECL|macro|SYSIO_CONTROL_MODE
mdefine_line|#define SYSIO_CONTROL_MODE&t;0x0000000000000001 /* SYSIO clock mode             */
multiline_comment|/* SYSIO ECC Control Register */
DECL|macro|SYSIO_ECNTRL_ECCEN
mdefine_line|#define SYSIO_ECNTRL_ECCEN&t;0x8000000000000000 /* Enable ECC Checking          */
DECL|macro|SYSIO_ECNTRL_UEEN
mdefine_line|#define SYSIO_ECNTRL_UEEN&t;0x4000000000000000 /* Enable UE Interrupts         */
DECL|macro|SYSIO_ECNTRL_CEEN
mdefine_line|#define SYSIO_ECNTRL_CEEN&t;0x2000000000000000 /* Enable CE Interrupts         */
multiline_comment|/* Uncorrectable Error AFSR, AFAR holds low 40bits of faulting physical address. */
DECL|macro|SYSIO_UEAFSR_PPIO
mdefine_line|#define SYSIO_UEAFSR_PPIO&t;0x8000000000000000 /* Primary PIO is cause         */
DECL|macro|SYSIO_UEAFSR_PDRD
mdefine_line|#define SYSIO_UEAFSR_PDRD&t;0x4000000000000000 /* Primary DVMA read is cause   */
DECL|macro|SYSIO_UEAFSR_PDWR
mdefine_line|#define SYSIO_UEAFSR_PDWR&t;0x2000000000000000 /* Primary DVMA write is cause  */
DECL|macro|SYSIO_UEAFSR_SPIO
mdefine_line|#define SYSIO_UEAFSR_SPIO&t;0x1000000000000000 /* Secondary PIO is cause       */
DECL|macro|SYSIO_UEAFSR_SDRD
mdefine_line|#define SYSIO_UEAFSR_SDRD&t;0x0800000000000000 /* Secondary DVMA read is cause */
DECL|macro|SYSIO_UEAFSR_SDWR
mdefine_line|#define SYSIO_UEAFSR_SDWR&t;0x0400000000000000 /* Secondary DVMA write is cause*/
DECL|macro|SYSIO_UEAFSR_RESV1
mdefine_line|#define SYSIO_UEAFSR_RESV1&t;0x03ff000000000000 /* Reserved                     */
DECL|macro|SYSIO_UEAFSR_DOFF
mdefine_line|#define SYSIO_UEAFSR_DOFF&t;0x0000e00000000000 /* Doubleword Offset            */
DECL|macro|SYSIO_UEAFSR_SIZE
mdefine_line|#define SYSIO_UEAFSR_SIZE&t;0x00001c0000000000 /* Bad transfer size is 2**SIZE */
DECL|macro|SYSIO_UEAFSR_MID
mdefine_line|#define SYSIO_UEAFSR_MID&t;0x000003e000000000 /* UPA MID causing the fault    */
DECL|macro|SYSIO_UEAFSR_RESV2
mdefine_line|#define SYSIO_UEAFSR_RESV2&t;0x0000001fffffffff /* Reserved                     */
multiline_comment|/* Correctable Error AFSR, AFAR holds low 40bits of faulting physical address. */
DECL|macro|SYSIO_CEAFSR_PPIO
mdefine_line|#define SYSIO_CEAFSR_PPIO&t;0x8000000000000000 /* Primary PIO is cause         */
DECL|macro|SYSIO_CEAFSR_PDRD
mdefine_line|#define SYSIO_CEAFSR_PDRD&t;0x4000000000000000 /* Primary DVMA read is cause   */
DECL|macro|SYSIO_CEAFSR_PDWR
mdefine_line|#define SYSIO_CEAFSR_PDWR&t;0x2000000000000000 /* Primary DVMA write is cause  */
DECL|macro|SYSIO_CEAFSR_SPIO
mdefine_line|#define SYSIO_CEAFSR_SPIO&t;0x1000000000000000 /* Secondary PIO is cause       */
DECL|macro|SYSIO_CEAFSR_SDRD
mdefine_line|#define SYSIO_CEAFSR_SDRD&t;0x0800000000000000 /* Secondary DVMA read is cause */
DECL|macro|SYSIO_CEAFSR_SDWR
mdefine_line|#define SYSIO_CEAFSR_SDWR&t;0x0400000000000000 /* Secondary DVMA write is cause*/
DECL|macro|SYSIO_CEAFSR_RESV1
mdefine_line|#define SYSIO_CEAFSR_RESV1&t;0x0300000000000000 /* Reserved                     */
DECL|macro|SYSIO_CEAFSR_ESYND
mdefine_line|#define SYSIO_CEAFSR_ESYND&t;0x00ff000000000000 /* Syndrome Bits                */
DECL|macro|SYSIO_CEAFSR_DOFF
mdefine_line|#define SYSIO_CEAFSR_DOFF&t;0x0000e00000000000 /* Double Offset                */
DECL|macro|SYSIO_CEAFSR_SIZE
mdefine_line|#define SYSIO_CEAFSR_SIZE&t;0x00001c0000000000 /* Bad transfer size is 2**SIZE */
DECL|macro|SYSIO_CEAFSR_MID
mdefine_line|#define SYSIO_CEAFSR_MID&t;0x000003e000000000 /* UPA MID causing the fault    */
DECL|macro|SYSIO_CEAFSR_RESV2
mdefine_line|#define SYSIO_CEAFSR_RESV2&t;0x0000001fffffffff /* Reserved                     */
multiline_comment|/* DMA Scoreboard Diagnostic Register(s) */
DECL|macro|SYSIO_DSCORE_VALID
mdefine_line|#define SYSIO_DSCORE_VALID&t;0x0040000000000000 /* Entry is valid               */
DECL|macro|SYSIO_DSCORE_C
mdefine_line|#define SYSIO_DSCORE_C&t;&t;0x0020000000000000 /* Transaction cacheable        */
DECL|macro|SYSIO_DSCORE_READ
mdefine_line|#define SYSIO_DSCORE_READ&t;0x0010000000000000 /* Transaction was a read       */
DECL|macro|SYSIO_DSCORE_TAG
mdefine_line|#define SYSIO_DSCORE_TAG&t;0x000f000000000000 /* Transaction ID               */
DECL|macro|SYSIO_DSCORE_ADDR
mdefine_line|#define SYSIO_DSCORE_ADDR&t;0x0000ffffffffff80 /* Transaction PADDR            */
DECL|macro|SYSIO_DSCORE_SIZE
mdefine_line|#define SYSIO_DSCORE_SIZE&t;0x0000000000000030 /* Transaction size             */
DECL|macro|SYSIO_DSCORE_SRC
mdefine_line|#define SYSIO_DSCORE_SRC&t;0x000000000000000f /* Transaction source           */
multiline_comment|/* SYSIO SBUS Control Register */
DECL|macro|SYSIO_SBCNTRL_IMPL
mdefine_line|#define SYSIO_SBCNTRL_IMPL&t;0xf000000000000000 /* Implementation               */
DECL|macro|SYSIO_SBCNTRL_REV
mdefine_line|#define SYSIO_SBCNTRL_REV&t;0x0f00000000000000 /* Revision                     */
DECL|macro|SYSIO_SBCNTRL_RESV1
mdefine_line|#define SYSIO_SBCNTRL_RESV1&t;0x00c0000000000000 /* Reserved                     */
DECL|macro|SYSIO_SBCNTRL_DPERR
mdefine_line|#define SYSIO_SBCNTRL_DPERR&t;0x003f000000000000 /* DMA Write Parity Error       */
DECL|macro|SYSIO_SBCNTRL_RESV2
mdefine_line|#define SYSIO_SBCNTRL_RESV2&t;0x0000800000000000 /* Reserved                     */
DECL|macro|SYSIO_SBCNTRL_PPERR
mdefine_line|#define SYSIO_SBCNTRL_PPERR&t;0x00007f0000000000 /* PIO Load Parity Error        */
DECL|macro|SYSIO_SBCNTRL_RESV
mdefine_line|#define SYSIO_SBCNTRL_RESV&t;0x000000fffffffc00 /* Reserved                     */
DECL|macro|SYSIO_SBCNTRL_WEN
mdefine_line|#define SYSIO_SBCNTRL_WEN&t;0x0000000000000200 /* Power Mgmt Wake Enable       */
DECL|macro|SYSIO_SBCNTRL_EEN
mdefine_line|#define SYSIO_SBCNTRL_EEN&t;0x0000000000000100 /* SBUS Error Interrupt Enable  */
DECL|macro|SYSIO_SBCNTRL_RESV3
mdefine_line|#define SYSIO_SBCNTRL_RESV3&t;0x00000000000000c0 /* Reserved                     */
DECL|macro|SYSIO_SBCNTRL_AEN
mdefine_line|#define SYSIO_SBCNTRL_AEN&t;0x000000000000003f /* SBUS DVMA Arbitration Enable */
multiline_comment|/* SYSIO SBUS AFSR, AFAR holds low 40 bits of physical address causing the fault. */
DECL|macro|SYSIO_SBAFSR_PLE
mdefine_line|#define SYSIO_SBAFSR_PLE&t;0x8000000000000000 /* Primary Late PIO Error       */
DECL|macro|SYSIO_SBAFSR_PTO
mdefine_line|#define SYSIO_SBAFSR_PTO&t;0x4000000000000000 /* Primary SBUS Timeout         */
DECL|macro|SYSIO_SBAFSR_PBERR
mdefine_line|#define SYSIO_SBAFSR_PBERR&t;0x2000000000000000 /* Primary SBUS Error ACK       */
DECL|macro|SYSIO_SBAFSR_SLE
mdefine_line|#define SYSIO_SBAFSR_SLE&t;0x1000000000000000 /* Secondary Late PIO Error     */
DECL|macro|SYSIO_SBAFSR_STO
mdefine_line|#define SYSIO_SBAFSR_STO&t;0x0800000000000000 /* Secondary SBUS Timeout       */
DECL|macro|SYSIO_SBAFSR_SBERR
mdefine_line|#define SYSIO_SBAFSR_SBERR&t;0x0400000000000000 /* Secondary SBUS Error ACK     */
DECL|macro|SYSIO_SBAFSR_RESV1
mdefine_line|#define SYSIO_SBAFSR_RESV1&t;0x03ff000000000000 /* Reserved                     */
DECL|macro|SYSIO_SBAFSR_RD
mdefine_line|#define SYSIO_SBAFSR_RD&t;&t;0x0000800000000000 /* Primary was late PIO read    */
DECL|macro|SYSIO_SBAFSR_RESV2
mdefine_line|#define SYSIO_SBAFSR_RESV2&t;0x0000600000000000 /* Reserved                     */
DECL|macro|SYSIO_SBAFSR_SIZE
mdefine_line|#define SYSIO_SBAFSR_SIZE&t;0x00001c0000000000 /* Size of transfer             */
DECL|macro|SYSIO_SBAFSR_MID
mdefine_line|#define SYSIO_SBAFSR_MID&t;0x000003e000000000 /* MID causing the error        */
DECL|macro|SYSIO_SBAFSR_RESV3
mdefine_line|#define SYSIO_SBAFSR_RESV3&t;0x0000001fffffffff /* Reserved                     */
multiline_comment|/* SYSIO SBUS Slot Configuration Register */
DECL|macro|SYSIO_SBSCFG_RESV1
mdefine_line|#define SYSIO_SBSCFG_RESV1&t;0xfffffffff8000000 /* Reserved                     */
DECL|macro|SYSIO_SBSCFG_SADDR
mdefine_line|#define SYSIO_SBSCFG_SADDR&t;0x0000000007ff0000 /* Segment Address (PA[40:30])  */
DECL|macro|SYSIO_SBSCFG_CP
mdefine_line|#define SYSIO_SBSCFG_CP&t;&t;0x0000000000008000 /* Bypasses are cacheable       */
DECL|macro|SYSIO_SBSCFG_ETM
mdefine_line|#define SYSIO_SBSCFG_ETM&t;0x0000000000004000 /* Ext Transfer Mode supported  */
DECL|macro|SYSIO_SBSCFG_PE
mdefine_line|#define SYSIO_SBSCFG_PE&t;&t;0x0000000000002000 /* SBUS Parity Checking Enable  */
DECL|macro|SYSIO_SBSCFG_RESV2
mdefine_line|#define SYSIO_SBSCFG_RESV2&t;0x0000000000001fe0 /* Reserved                     */
DECL|macro|SYSIO_SBSCFG_BA64
mdefine_line|#define SYSIO_SBSCFG_BA64&t;0x0000000000000010 /* 64-byte bursts supported     */
DECL|macro|SYSIO_SBSCFG_BA32
mdefine_line|#define SYSIO_SBSCFG_BA32&t;0x0000000000000008 /* 32-byte bursts supported     */
DECL|macro|SYSIO_SBSCFG_BA16
mdefine_line|#define SYSIO_SBSCFG_BA16&t;0x0000000000000004 /* 16-byte bursts supported     */
DECL|macro|SYSIO_SBSCFG_BA8
mdefine_line|#define SYSIO_SBSCFG_BA8&t;0x0000000000000002 /* 8-byte bursts supported      */
DECL|macro|SYSIO_SBSCFG_BY
mdefine_line|#define SYSIO_SBSCFG_BY&t;&t;0x0000000000000001 /* IOMMU Bypass Enable          */
multiline_comment|/* IOMMU things defined fully in asm-sparc64/iommu.h */
multiline_comment|/* Streaming Buffer Control Register */
DECL|macro|SYSIO_SBUFCTRL_IMPL
mdefine_line|#define SYSIO_SBUFCTRL_IMPL&t;0xf000000000000000 /* Implementation               */
DECL|macro|SYSIO_SBUFCTRL_REV
mdefine_line|#define SYSIO_SBUFCTRL_REV&t;0x0f00000000000000 /* Revision                     */
DECL|macro|SYSIO_SBUFCTRL_DE
mdefine_line|#define SYSIO_SBUFCTRL_DE&t;0x0000000000000002 /* Diag Mode Enable             */
DECL|macro|SYSIO_SBUFCTRL_SB_EN
mdefine_line|#define SYSIO_SBUFCTRL_SB_EN&t;0x0000000000000001 /* Streaming Buffer Enable      */
multiline_comment|/* Streaming Buffer Page Invalidate/Flush Register */
DECL|macro|SYSIO_SBUFFLUSH_ADDR
mdefine_line|#define SYSIO_SBUFFLUSH_ADDR&t;0x00000000ffffe000 /* DVMA Page to be flushed      */
DECL|macro|SYSIO_SBUFFLUSH_RESV
mdefine_line|#define SYSIO_SBUFFLUSH_RESV    0x0000000000001fff /* Ignored bits                 */
multiline_comment|/* Streaming Buffer Flush Synchronization Register */
DECL|macro|SYSIO_SBUFSYNC_ADDR
mdefine_line|#define SYSIO_SBUFSYNC_ADDR&t;0x000001fffffffffc /* Physical address to update   */
DECL|macro|SYSIO_SBUFSYNC_RESV
mdefine_line|#define SYSIO_SBUFSYNC_RESV&t;0x0000000000000003 /* Ignored bits                 */
multiline_comment|/* SYSIO Interrupt mapping register(s). */
DECL|macro|SYSIO_IMAP_VALID
mdefine_line|#define SYSIO_IMAP_VALID&t;0x80000000&t;/* This enables delivery.&t;   */
DECL|macro|SYSIO_IMAP_TID
mdefine_line|#define SYSIO_IMAP_TID&t;&t;0x7c000000&t;/* Target ID (MID to send it to)   */
DECL|macro|SYSIO_IMAP_RESV
mdefine_line|#define SYSIO_IMAP_RESV&t;&t;0x03fff800&t;/* Reserved.&t;&t;&t;   */
DECL|macro|SYSIO_IMAP_IGN
mdefine_line|#define SYSIO_IMAP_IGN&t;&t;0x000007c0&t;/* Interrupt Group Number.&t;   */
DECL|macro|SYSIO_IMAP_INO
mdefine_line|#define SYSIO_IMAP_INO&t;&t;0x0000003f&t;/* Interrupt Number Offset.&t;   */
DECL|macro|SYSIO_IMAP_INR
mdefine_line|#define SYSIO_IMAP_INR&t;&t;0x000007ff&t;/* Interrupt # (Gfx/UPA_slave only)*/
multiline_comment|/* SYSIO Interrupt clear pseudo register(s). */
DECL|macro|SYSIO_ICLR_IDLE
mdefine_line|#define SYSIO_ICLR_IDLE&t;&t;0x00000000&t;/* Transition to idle state.&t;   */
DECL|macro|SYSIO_ICLR_TRANSMIT
mdefine_line|#define SYSIO_ICLR_TRANSMIT&t;0x00000001&t;/* Transition to transmit state.   */
DECL|macro|SYSIO_ICLR_RESV
mdefine_line|#define SYSIO_ICLR_RESV&t;&t;0x00000002&t;/* Reserved.&t;&t;&t;   */
DECL|macro|SYSIO_ICLR_PENDING
mdefine_line|#define SYSIO_ICLR_PENDING&t;0x00000003&t;/* Transition to pending state.&t;   */
multiline_comment|/* SYSIO Interrupt Retry Timer register. */
DECL|macro|SYSIO_IRETRY_LIMIT
mdefine_line|#define SYSIO_IRETRY_LIMIT&t;0x000000ff&t;/* The retry interval.&t;&t;   */
multiline_comment|/* SYSIO Interrupt State registers. XXX fields to be documented later */
multiline_comment|/* SYSIO Counter register. XXX fields to be documented later */
multiline_comment|/* SYSIO Limit register. XXX fields to be documented later */
multiline_comment|/* SYSIO Performance Monitor Control register. XXX fields to be documented later */
multiline_comment|/* SYSIO Performance Monitor Counter register. XXX fields to be documented later */
macro_line|#endif /* !(__SPARC64_SYSIO_H) */
eof
