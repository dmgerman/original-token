multiline_comment|/* $Id: eicon_pci.h,v 1.3 1999/03/29 11:19:51 armin Exp $&n; *&n; * ISDN low-level module for Eicon.Diehl active ISDN-Cards (PCI part).&n; *&n; * Copyright 1998,99 by Armin Schindler (mac@melware.de)&n; * Copyright 1999    Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: eicon_pci.h,v $&n; * Revision 1.3  1999/03/29 11:19:51  armin&n; * I/O stuff now in seperate file (eicon_io.c)&n; * Old ISA type cards (S,SX,SCOM,Quadro,S2M) implemented.&n; *&n; * Revision 1.2  1999/03/02 12:37:50  armin&n; * Added some important checks.&n; * Analog Modem with DSP.&n; * Channels will be added to Link-Level after loading firmware.&n; *&n; * Revision 1.1  1999/01/01 18:09:46  armin&n; * First checkin of new eicon driver.&n; * DIVA-Server BRI/PCI and PRI/PCI are supported.&n; * Old diehl code is obsolete.&n; *&n; *&n; */
macro_line|#ifndef eicon_pci_h
DECL|macro|eicon_pci_h
mdefine_line|#define eicon_pci_h
macro_line|#ifdef __KERNEL__
DECL|macro|PCI_VENDOR_EICON
mdefine_line|#define PCI_VENDOR_EICON        0x1133
DECL|macro|PCI_DIVA_PRO20
mdefine_line|#define PCI_DIVA_PRO20          0xe001&t;/* Not supported */
DECL|macro|PCI_DIVA20
mdefine_line|#define PCI_DIVA20              0xe002&t;/* Not supported */
DECL|macro|PCI_DIVA_PRO20_U
mdefine_line|#define PCI_DIVA_PRO20_U        0xe003&t;/* Not supported */
DECL|macro|PCI_DIVA20_U
mdefine_line|#define PCI_DIVA20_U            0xe004&t;/* Not supported */
DECL|macro|PCI_MAESTRA
mdefine_line|#define PCI_MAESTRA             0xe010
DECL|macro|PCI_MAESTRAQ
mdefine_line|#define PCI_MAESTRAQ            0xe012
DECL|macro|PCI_MAESTRAQ_U
mdefine_line|#define PCI_MAESTRAQ_U          0xe013
DECL|macro|PCI_MAESTRAP
mdefine_line|#define PCI_MAESTRAP            0xe014
DECL|macro|DIVA_PRO20
mdefine_line|#define DIVA_PRO20          1
DECL|macro|DIVA20
mdefine_line|#define DIVA20              2
DECL|macro|DIVA_PRO20_U
mdefine_line|#define DIVA_PRO20_U        3
DECL|macro|DIVA20_U
mdefine_line|#define DIVA20_U            4
DECL|macro|MAESTRA
mdefine_line|#define MAESTRA             5
DECL|macro|MAESTRAQ
mdefine_line|#define MAESTRAQ            6
DECL|macro|MAESTRAQ_U
mdefine_line|#define MAESTRAQ_U          7
DECL|macro|MAESTRAP
mdefine_line|#define MAESTRAP            8
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|DIVAS_SIGNATURE
mdefine_line|#define DIVAS_SIGNATURE 0x4447
multiline_comment|/* MAESTRA BRI PCI */
DECL|macro|M_RESET
mdefine_line|#define M_RESET&t;&t;0x10&t;&t;/* offset of reset register */
DECL|macro|M_DATA
mdefine_line|#define M_DATA&t;&t;0x00&t;&t;/* offset of data register */
DECL|macro|M_ADDR
mdefine_line|#define M_ADDR&t;&t;0x04&t;&t;/* offset of address register */
DECL|macro|M_ADDRH
mdefine_line|#define M_ADDRH&t;&t;0x0c&t;&t;/* offset of high address register */
DECL|macro|M_DSP_CODE_LEN
mdefine_line|#define M_DSP_CODE_LEN            0xbf7d0000
DECL|macro|M_DSP_CODE
mdefine_line|#define M_DSP_CODE                0xbf7d0004  /* max 128K DSP-Code */ 
DECL|macro|M_DSP_CODE_BASE
mdefine_line|#define M_DSP_CODE_BASE           0xbf7a0000  
DECL|macro|M_MAX_DSP_CODE_SIZE
mdefine_line|#define M_MAX_DSP_CODE_SIZE       0x00050000  /* max 320K DSP-Code (Telindus) */
multiline_comment|/* MAESTRA PRI PCI */
DECL|macro|MP_SHARED_RAM_OFFSET
mdefine_line|#define MP_SHARED_RAM_OFFSET 0x1000  /* offset of shared RAM base in the DRAM memory bar */
DECL|macro|MP_IRQ_RESET
mdefine_line|#define MP_IRQ_RESET     0xc18       /* offset of interrupt status register in the CONFIG memory bar */
DECL|macro|MP_IRQ_RESET_VAL
mdefine_line|#define MP_IRQ_RESET_VAL 0xfe        /* value to clear an interrupt */
DECL|macro|MP_PROTOCOL_ADDR
mdefine_line|#define MP_PROTOCOL_ADDR 0xa0011000  /* load address of protocol code */
DECL|macro|MP_DSP_ADDR
mdefine_line|#define MP_DSP_ADDR      0xa03c0000  /* load address of DSP code */
DECL|macro|MP_MAX_PROTOCOL_CODE_SIZE
mdefine_line|#define MP_MAX_PROTOCOL_CODE_SIZE  0x000a0000   /* max 640K Protocol-Code */
DECL|macro|MP_DSP_CODE_BASE
mdefine_line|#define MP_DSP_CODE_BASE           0xa03a0000
DECL|macro|MP_MAX_DSP_CODE_SIZE
mdefine_line|#define MP_MAX_DSP_CODE_SIZE       0x00060000   /* max 384K DSP-Code */
DECL|macro|MP_RESET
mdefine_line|#define MP_RESET         0x20        /* offset of RESET register in the DEVICES memory bar */
multiline_comment|/* RESET register bits */
DECL|macro|_MP_S2M_RESET
mdefine_line|#define _MP_S2M_RESET    0x10        /* active lo   */
DECL|macro|_MP_LED2
mdefine_line|#define _MP_LED2         0x08        /* 1 = on      */
DECL|macro|_MP_LED1
mdefine_line|#define _MP_LED1         0x04        /* 1 = on      */
DECL|macro|_MP_DSP_RESET
mdefine_line|#define _MP_DSP_RESET    0x02        /* active lo   */
DECL|macro|_MP_RISC_RESET
mdefine_line|#define _MP_RISC_RESET   0x81        /* active hi, bit 7 for compatibility with old boards */
multiline_comment|/* boot interface structure */
r_typedef
r_struct
(brace
DECL|member|cmd
id|__u32
id|cmd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|addr
id|__u32
id|addr
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|len
id|__u32
id|len
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|err
id|__u32
id|err
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|live
id|__u32
id|live
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
(paren
l_int|0x1020
op_rshift
l_int|2
)paren
op_minus
l_int|6
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|signature
id|__u32
id|signature
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* real interface description */
DECL|typedef|eicon_pci_boot
)brace
id|eicon_pci_boot
suffix:semicolon
DECL|macro|DL_PARA_IO_TYPE
mdefine_line|#define DL_PARA_IO_TYPE   0
DECL|macro|DL_PARA_MEM_TYPE
mdefine_line|#define DL_PARA_MEM_TYPE  1
DECL|struct|tag_dsp_download_space
r_typedef
r_struct
id|tag_dsp_download_space
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
multiline_comment|/* see definitions above to differ union elements */
r_union
(brace
r_struct
(brace
DECL|member|r3addr
id|__u32
id|r3addr
suffix:semicolon
DECL|member|ioADDR
id|__u16
id|ioADDR
suffix:semicolon
DECL|member|ioADDRH
id|__u16
id|ioADDRH
suffix:semicolon
DECL|member|ioDATA
id|__u16
id|ioDATA
suffix:semicolon
DECL|member|BadData
id|__u16
id|BadData
suffix:semicolon
multiline_comment|/* in case of verify error */
DECL|member|GoodData
id|__u16
id|GoodData
suffix:semicolon
DECL|member|io
)brace
id|io
suffix:semicolon
multiline_comment|/* for io based adapters */
r_struct
(brace
DECL|member|r3addr
id|__u32
id|r3addr
suffix:semicolon
DECL|member|boot
id|eicon_pci_boot
op_star
id|boot
suffix:semicolon
DECL|member|BadData
id|__u32
id|BadData
suffix:semicolon
multiline_comment|/* in case of verify error */
DECL|member|GoodData
id|__u32
id|GoodData
suffix:semicolon
DECL|member|timeout
id|__u16
id|timeout
suffix:semicolon
DECL|member|mem
)brace
id|mem
suffix:semicolon
multiline_comment|/* for memory based adapters */
DECL|member|dat
)brace
id|dat
suffix:semicolon
DECL|typedef|t_dsp_download_space
)brace
id|t_dsp_download_space
suffix:semicolon
multiline_comment|/* Shared memory */
r_typedef
r_union
(brace
DECL|member|boot
id|eicon_pci_boot
id|boot
suffix:semicolon
DECL|typedef|eicon_pci_shmem
)brace
id|eicon_pci_shmem
suffix:semicolon
multiline_comment|/*&n; * card&squot;s description&n; */
r_typedef
r_struct
(brace
DECL|member|ramsize
r_int
id|ramsize
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ&t;&t;          */
DECL|member|PCIram
r_int
r_int
id|PCIram
suffix:semicolon
DECL|member|PCIreg
r_int
r_int
id|PCIreg
suffix:semicolon
DECL|member|PCIcfg
r_int
r_int
id|PCIcfg
suffix:semicolon
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* Serial No.&t;&t;  */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* No. of supported channels  */
DECL|member|card
r_void
op_star
id|card
suffix:semicolon
DECL|member|shmem
id|eicon_pci_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Shared-memory area         */
DECL|member|intack
r_int
r_char
op_star
id|intack
suffix:semicolon
multiline_comment|/* Int-Acknowledge            */
DECL|member|stopcpu
r_int
r_char
op_star
id|stopcpu
suffix:semicolon
multiline_comment|/* Writing here stops CPU     */
DECL|member|startcpu
r_int
r_char
op_star
id|startcpu
suffix:semicolon
multiline_comment|/* Writing here starts CPU    */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* card type                  */
DECL|member|irqprobe
r_int
r_char
id|irqprobe
suffix:semicolon
multiline_comment|/* Flag: IRQ-probing          */
DECL|member|mvalid
r_int
r_char
id|mvalid
suffix:semicolon
multiline_comment|/* Flag: Memory is valid      */
DECL|member|ivalid
r_int
r_char
id|ivalid
suffix:semicolon
multiline_comment|/* Flag: IRQ is valid         */
DECL|member|master
r_int
r_char
id|master
suffix:semicolon
multiline_comment|/* Flag: Card is Quadro 1/4   */
DECL|member|generic
r_void
op_star
id|generic
suffix:semicolon
multiline_comment|/* Ptr to generic card struct */
DECL|typedef|eicon_pci_card
)brace
id|eicon_pci_card
suffix:semicolon
r_extern
r_int
id|eicon_pci_load_pri
c_func
(paren
id|eicon_pci_card
op_star
id|card
comma
id|eicon_pci_codebuf
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_int
id|eicon_pci_load_bri
c_func
(paren
id|eicon_pci_card
op_star
id|card
comma
id|eicon_pci_codebuf
op_star
id|cb
)paren
suffix:semicolon
r_extern
r_void
id|eicon_pci_release
c_func
(paren
id|eicon_pci_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|eicon_pci_printpar
c_func
(paren
id|eicon_pci_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_int
id|eicon_pci_find_card
c_func
(paren
r_char
op_star
id|ID
)paren
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* eicon_pci_h */
eof
