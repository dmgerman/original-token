multiline_comment|/*&n; *  linux/include/asm-arm/hardware/pci_v3.h&n; *&n; *  Internal header file PCI V3 chip&n; *&n; *  Copyright (C) ARM Limited&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef ASM_ARM_HARDWARE_PCI_V3_H
DECL|macro|ASM_ARM_HARDWARE_PCI_V3_H
mdefine_line|#define ASM_ARM_HARDWARE_PCI_V3_H
multiline_comment|/* -------------------------------------------------------------------------------&n; *  V3 Local Bus to PCI Bridge definitions&n; * -------------------------------------------------------------------------------&n; *  Registers (these are taken from page 129 of the EPC User&squot;s Manual Rev 1.04&n; *  All V3 register names are prefaced by V3_ to avoid clashing with any other&n; *  PCI definitions.  Their names match the user&squot;s manual.&n; * &n; *  I&squot;m assuming that I20 is disabled.&n; * &n; */
DECL|macro|V3_PCI_VENDOR
mdefine_line|#define V3_PCI_VENDOR                   0x00000000
DECL|macro|V3_PCI_DEVICE
mdefine_line|#define V3_PCI_DEVICE                   0x00000002
DECL|macro|V3_PCI_CMD
mdefine_line|#define V3_PCI_CMD                      0x00000004
DECL|macro|V3_PCI_STAT
mdefine_line|#define V3_PCI_STAT                     0x00000006
DECL|macro|V3_PCI_CC_REV
mdefine_line|#define V3_PCI_CC_REV                   0x00000008
DECL|macro|V3_PCI_HDR_CFG
mdefine_line|#define V3_PCI_HDR_CFG                  0x0000000C
DECL|macro|V3_PCI_IO_BASE
mdefine_line|#define V3_PCI_IO_BASE                  0x00000010
DECL|macro|V3_PCI_BASE0
mdefine_line|#define V3_PCI_BASE0                    0x00000014
DECL|macro|V3_PCI_BASE1
mdefine_line|#define V3_PCI_BASE1                    0x00000018
DECL|macro|V3_PCI_SUB_VENDOR
mdefine_line|#define V3_PCI_SUB_VENDOR               0x0000002C
DECL|macro|V3_PCI_SUB_ID
mdefine_line|#define V3_PCI_SUB_ID                   0x0000002E
DECL|macro|V3_PCI_ROM
mdefine_line|#define V3_PCI_ROM                      0x00000030
DECL|macro|V3_PCI_BPARAM
mdefine_line|#define V3_PCI_BPARAM                   0x0000003C
DECL|macro|V3_PCI_MAP0
mdefine_line|#define V3_PCI_MAP0                     0x00000040
DECL|macro|V3_PCI_MAP1
mdefine_line|#define V3_PCI_MAP1                     0x00000044
DECL|macro|V3_PCI_INT_STAT
mdefine_line|#define V3_PCI_INT_STAT                 0x00000048
DECL|macro|V3_PCI_INT_CFG
mdefine_line|#define V3_PCI_INT_CFG                  0x0000004C 
DECL|macro|V3_LB_BASE0
mdefine_line|#define V3_LB_BASE0                     0x00000054
DECL|macro|V3_LB_BASE1
mdefine_line|#define V3_LB_BASE1                     0x00000058
DECL|macro|V3_LB_MAP0
mdefine_line|#define V3_LB_MAP0                      0x0000005E
DECL|macro|V3_LB_MAP1
mdefine_line|#define V3_LB_MAP1                      0x00000062
DECL|macro|V3_LB_BASE2
mdefine_line|#define V3_LB_BASE2                     0x00000064
DECL|macro|V3_LB_MAP2
mdefine_line|#define V3_LB_MAP2                      0x00000066
DECL|macro|V3_LB_SIZE
mdefine_line|#define V3_LB_SIZE                      0x00000068
DECL|macro|V3_LB_IO_BASE
mdefine_line|#define V3_LB_IO_BASE                   0x0000006E
DECL|macro|V3_FIFO_CFG
mdefine_line|#define V3_FIFO_CFG                     0x00000070
DECL|macro|V3_FIFO_PRIORITY
mdefine_line|#define V3_FIFO_PRIORITY                0x00000072
DECL|macro|V3_FIFO_STAT
mdefine_line|#define V3_FIFO_STAT                    0x00000074
DECL|macro|V3_LB_ISTAT
mdefine_line|#define V3_LB_ISTAT                     0x00000076
DECL|macro|V3_LB_IMASK
mdefine_line|#define V3_LB_IMASK                     0x00000077
DECL|macro|V3_SYSTEM
mdefine_line|#define V3_SYSTEM                       0x00000078
DECL|macro|V3_LB_CFG
mdefine_line|#define V3_LB_CFG                       0x0000007A
DECL|macro|V3_PCI_CFG
mdefine_line|#define V3_PCI_CFG                      0x0000007C
DECL|macro|V3_DMA_PCI_ADR0
mdefine_line|#define V3_DMA_PCI_ADR0                 0x00000080
DECL|macro|V3_DMA_PCI_ADR1
mdefine_line|#define V3_DMA_PCI_ADR1                 0x00000090
DECL|macro|V3_DMA_LOCAL_ADR0
mdefine_line|#define V3_DMA_LOCAL_ADR0               0x00000084
DECL|macro|V3_DMA_LOCAL_ADR1
mdefine_line|#define V3_DMA_LOCAL_ADR1               0x00000094
DECL|macro|V3_DMA_LENGTH0
mdefine_line|#define V3_DMA_LENGTH0                  0x00000088
DECL|macro|V3_DMA_LENGTH1
mdefine_line|#define V3_DMA_LENGTH1                  0x00000098
DECL|macro|V3_DMA_CSR0
mdefine_line|#define V3_DMA_CSR0                     0x0000008B
DECL|macro|V3_DMA_CSR1
mdefine_line|#define V3_DMA_CSR1                     0x0000009B
DECL|macro|V3_DMA_CTLB_ADR0
mdefine_line|#define V3_DMA_CTLB_ADR0                0x0000008C
DECL|macro|V3_DMA_CTLB_ADR1
mdefine_line|#define V3_DMA_CTLB_ADR1                0x0000009C
DECL|macro|V3_DMA_DELAY
mdefine_line|#define V3_DMA_DELAY                    0x000000E0
DECL|macro|V3_MAIL_DATA
mdefine_line|#define V3_MAIL_DATA                    0x000000C0
DECL|macro|V3_PCI_MAIL_IEWR
mdefine_line|#define V3_PCI_MAIL_IEWR                0x000000D0
DECL|macro|V3_PCI_MAIL_IERD
mdefine_line|#define V3_PCI_MAIL_IERD                0x000000D2
DECL|macro|V3_LB_MAIL_IEWR
mdefine_line|#define V3_LB_MAIL_IEWR                 0x000000D4
DECL|macro|V3_LB_MAIL_IERD
mdefine_line|#define V3_LB_MAIL_IERD                 0x000000D6
DECL|macro|V3_MAIL_WR_STAT
mdefine_line|#define V3_MAIL_WR_STAT                 0x000000D8
DECL|macro|V3_MAIL_RD_STAT
mdefine_line|#define V3_MAIL_RD_STAT                 0x000000DA
DECL|macro|V3_QBA_MAP
mdefine_line|#define V3_QBA_MAP                      0x000000DC
multiline_comment|/*  PCI COMMAND REGISTER bits&n; */
DECL|macro|V3_COMMAND_M_FBB_EN
mdefine_line|#define V3_COMMAND_M_FBB_EN             BIT9
DECL|macro|V3_COMMAND_M_SERR_EN
mdefine_line|#define V3_COMMAND_M_SERR_EN            BIT8
DECL|macro|V3_COMMAND_M_PAR_EN
mdefine_line|#define V3_COMMAND_M_PAR_EN             BIT6
DECL|macro|V3_COMMAND_M_MASTER_EN
mdefine_line|#define V3_COMMAND_M_MASTER_EN          BIT2
DECL|macro|V3_COMMAND_M_MEM_EN
mdefine_line|#define V3_COMMAND_M_MEM_EN             BIT1
DECL|macro|V3_COMMAND_M_IO_EN
mdefine_line|#define V3_COMMAND_M_IO_EN              BIT0
multiline_comment|/*  SYSTEM REGISTER bits&n; */
DECL|macro|V3_SYSTEM_M_RST_OUT
mdefine_line|#define V3_SYSTEM_M_RST_OUT             BIT15
DECL|macro|V3_SYSTEM_M_LOCK
mdefine_line|#define V3_SYSTEM_M_LOCK                BIT14 
multiline_comment|/*  PCI_CFG bits&n; */
DECL|macro|V3_PCI_CFG_M_RETRY_EN
mdefine_line|#define V3_PCI_CFG_M_RETRY_EN           BIT10
DECL|macro|V3_PCI_CFG_M_AD_LOW1
mdefine_line|#define V3_PCI_CFG_M_AD_LOW1            BIT9
DECL|macro|V3_PCI_CFG_M_AD_LOW0
mdefine_line|#define V3_PCI_CFG_M_AD_LOW0            BIT8
multiline_comment|/*  PCI_BASE register bits (PCI -&gt; Local Bus)&n; */
DECL|macro|V3_PCI_BASE_M_ADR_BASE
mdefine_line|#define V3_PCI_BASE_M_ADR_BASE          0xFFF00000
DECL|macro|V3_PCI_BASE_M_ADR_BASEL
mdefine_line|#define V3_PCI_BASE_M_ADR_BASEL         0x000FFF00
DECL|macro|V3_PCI_BASE_M_PREFETCH
mdefine_line|#define V3_PCI_BASE_M_PREFETCH          BIT3
DECL|macro|V3_PCI_BASE_M_TYPE
mdefine_line|#define V3_PCI_BASE_M_TYPE              BIT2+BIT1
DECL|macro|V3_PCI_BASE_M_IO
mdefine_line|#define V3_PCI_BASE_M_IO                BIT0
multiline_comment|/*  PCI MAP register bits (PCI -&gt; Local bus)&n; */
DECL|macro|V3_PCI_MAP_M_MAP_ADR
mdefine_line|#define V3_PCI_MAP_M_MAP_ADR            0xFFF00000
DECL|macro|V3_PCI_MAP_M_RD_POST_INH
mdefine_line|#define V3_PCI_MAP_M_RD_POST_INH        BIT15
DECL|macro|V3_PCI_MAP_M_ROM_SIZE
mdefine_line|#define V3_PCI_MAP_M_ROM_SIZE           BIT11+BIT10
DECL|macro|V3_PCI_MAP_M_SWAP
mdefine_line|#define V3_PCI_MAP_M_SWAP               BIT9+BIT8
DECL|macro|V3_PCI_MAP_M_ADR_SIZE
mdefine_line|#define V3_PCI_MAP_M_ADR_SIZE           0x000000F0
DECL|macro|V3_PCI_MAP_M_REG_EN
mdefine_line|#define V3_PCI_MAP_M_REG_EN             BIT1&t;
DECL|macro|V3_PCI_MAP_M_ENABLE
mdefine_line|#define V3_PCI_MAP_M_ENABLE             BIT0
multiline_comment|/*  9 =&gt; 512M window size&n; */
DECL|macro|V3_PCI_MAP_M_ADR_SIZE_512M
mdefine_line|#define V3_PCI_MAP_M_ADR_SIZE_512M      0x00000090
multiline_comment|/*  A =&gt; 1024M window size&n; */
DECL|macro|V3_PCI_MAP_M_ADR_SIZE_1024M
mdefine_line|#define V3_PCI_MAP_M_ADR_SIZE_1024M     0x000000A0      
multiline_comment|/*  LB_BASE register bits (Local bus -&gt; PCI)&n; */
DECL|macro|V3_LB_BASE_M_MAP_ADR
mdefine_line|#define V3_LB_BASE_M_MAP_ADR            0xFFF00000
DECL|macro|V3_LB_BASE_M_SWAP
mdefine_line|#define V3_LB_BASE_M_SWAP               BIT9+BIT8
DECL|macro|V3_LB_BASE_M_ADR_SIZE
mdefine_line|#define V3_LB_BASE_M_ADR_SIZE           0x000000F0
DECL|macro|V3_LB_BASE_M_PREFETCH
mdefine_line|#define V3_LB_BASE_M_PREFETCH           BIT3
DECL|macro|V3_LB_BASE_M_ENABLE
mdefine_line|#define V3_LB_BASE_M_ENABLE             BIT0
multiline_comment|/*  LB_MAP register bits (Local bus -&gt; PCI)&n; */
DECL|macro|V3_LB_MAP_M_MAP_ADR
mdefine_line|#define V3_LB_MAP_M_MAP_ADR             0xFFF0
DECL|macro|V3_LB_MAP_M_TYPE
mdefine_line|#define V3_LB_MAP_M_TYPE                0x000E
DECL|macro|V3_LB_MAP_M_AD_LOW_EN
mdefine_line|#define V3_LB_MAP_M_AD_LOW_EN           BIT0
macro_line|#endif
eof
