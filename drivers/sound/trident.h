macro_line|#ifndef __TRID4DWAVE_H
DECL|macro|__TRID4DWAVE_H
mdefine_line|#define __TRID4DWAVE_H
multiline_comment|/*&n; *  audio@tridentmicro.com&n; *  Fri Feb 19 15:55:28 MST 1999&n; *  Definitions for Trident 4DWave DX/NX chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef PCI_VENDOR_ID_TRIDENT
DECL|macro|PCI_VENDOR_ID_TRIDENT
mdefine_line|#define PCI_VENDOR_ID_TRIDENT          0x1023
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_DX 
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_DX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_DX 0x2000
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_NX 
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_NX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_NX 0x2001
macro_line|#endif
multiline_comment|/*&n; * Direct registers&n; */
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
DECL|macro|TRUE
mdefine_line|#define TRUE  1
macro_line|#endif
DECL|macro|TRID_REG
mdefine_line|#define TRID_REG( trident, x ) ( (trident) -&gt; iobase + (x) )
DECL|macro|CHANNEL_REGS
mdefine_line|#define CHANNEL_REGS    5
DECL|macro|CHANNEL_START
mdefine_line|#define CHANNEL_START   0xe0   
singleline_comment|// The first bytes of the contiguous register space.
DECL|macro|ID_4DWAVE_DX
mdefine_line|#define ID_4DWAVE_DX        0x2000
DECL|macro|ID_4DWAVE_NX
mdefine_line|#define ID_4DWAVE_NX        0x2001
singleline_comment|// Register definitions
singleline_comment|// Global registers
singleline_comment|// T2 legacy dma control registers.
DECL|macro|LEGACY_DMAR0
mdefine_line|#define LEGACY_DMAR0                0x00  
singleline_comment|// ADR0
DECL|macro|LEGACY_DMAR4
mdefine_line|#define LEGACY_DMAR4                0x04  
singleline_comment|// CNT0
DECL|macro|LEGACY_DMAR11
mdefine_line|#define LEGACY_DMAR11               0x0b  
singleline_comment|// MOD 
DECL|macro|LEGACY_DMAR15
mdefine_line|#define LEGACY_DMAR15               0x0f  
singleline_comment|// MMR 
DECL|macro|T4D_START_A
mdefine_line|#define T4D_START_A&t;&t;     0x80
DECL|macro|T4D_STOP_A
mdefine_line|#define T4D_STOP_A&t;&t;     0x84
DECL|macro|T4D_DLY_A
mdefine_line|#define T4D_DLY_A&t;&t;     0x88
DECL|macro|T4D_SIGN_CSO_A
mdefine_line|#define T4D_SIGN_CSO_A&t;&t;     0x8c
DECL|macro|T4D_CSPF_A
mdefine_line|#define T4D_CSPF_A&t;&t;     0x90
DECL|macro|T4D_CEBC_A
mdefine_line|#define T4D_CEBC_A&t;&t;     0x94
DECL|macro|T4D_AINT_A
mdefine_line|#define T4D_AINT_A&t;&t;     0x98
DECL|macro|T4D_AINTEN_A
mdefine_line|#define T4D_AINTEN_A&t;&t;     0x9c
DECL|macro|T4D_LFO_GC_CIR
mdefine_line|#define T4D_LFO_GC_CIR               0xa0
DECL|macro|T4D_MUSICVOL_WAVEVOL
mdefine_line|#define T4D_MUSICVOL_WAVEVOL         0xa8
DECL|macro|T4D_SBDELTA_DELTA_R
mdefine_line|#define T4D_SBDELTA_DELTA_R          0xac
DECL|macro|T4D_MISCINT
mdefine_line|#define T4D_MISCINT                  0xb0
DECL|macro|T4D_START_B
mdefine_line|#define T4D_START_B                  0xb4
DECL|macro|T4D_STOP_B
mdefine_line|#define T4D_STOP_B                   0xb8
DECL|macro|T4D_SBBL_SBCL
mdefine_line|#define T4D_SBBL_SBCL                0xc0
DECL|macro|T4D_SBCTRL_SBE2R_SBDD
mdefine_line|#define T4D_SBCTRL_SBE2R_SBDD        0xc4
DECL|macro|T4D_AINT_B
mdefine_line|#define T4D_AINT_B                   0xd8
DECL|macro|T4D_AINTEN_B
mdefine_line|#define T4D_AINTEN_B                 0xdc
singleline_comment|// MPU-401 UART
DECL|macro|T4D_MPU401_BASE
mdefine_line|#define T4D_MPU401_BASE             0x20
DECL|macro|T4D_MPUR0
mdefine_line|#define T4D_MPUR0                   0x20
DECL|macro|T4D_MPUR1
mdefine_line|#define T4D_MPUR1                   0x21
DECL|macro|T4D_MPUR2
mdefine_line|#define T4D_MPUR2                   0x22
DECL|macro|T4D_MPUR3
mdefine_line|#define T4D_MPUR3                   0x23
singleline_comment|// S/PDIF Registers
DECL|macro|NX_SPCTRL_SPCSO
mdefine_line|#define NX_SPCTRL_SPCSO             0x24
DECL|macro|NX_SPLBA
mdefine_line|#define NX_SPLBA                    0x28
DECL|macro|NX_SPESO
mdefine_line|#define NX_SPESO                    0x2c
DECL|macro|NX_SPCSTATUS
mdefine_line|#define NX_SPCSTATUS                0x64
singleline_comment|// Channel Registers
DECL|macro|CH_DX_CSO_ALPHA_FMS
mdefine_line|#define CH_DX_CSO_ALPHA_FMS         0xe0
DECL|macro|CH_DX_ESO_DELTA
mdefine_line|#define CH_DX_ESO_DELTA             0xe8
DECL|macro|CH_DX_FMC_RVOL_CVOL
mdefine_line|#define CH_DX_FMC_RVOL_CVOL         0xec
DECL|macro|CH_NX_DELTA_CSO
mdefine_line|#define CH_NX_DELTA_CSO             0xe0
DECL|macro|CH_NX_DELTA_ESO
mdefine_line|#define CH_NX_DELTA_ESO             0xe8
DECL|macro|CH_NX_ALPHA_FMS_FMC_RVOL_CVOL
mdefine_line|#define CH_NX_ALPHA_FMS_FMC_RVOL_CVOL 0xec
DECL|macro|CH_LBA
mdefine_line|#define CH_LBA                      0xe4
DECL|macro|CH_GVSEL_PAN_VOL_CTRL_EC
mdefine_line|#define CH_GVSEL_PAN_VOL_CTRL_EC    0xf0
singleline_comment|// AC-97 Registers
DECL|macro|DX_ACR0_AC97_W
mdefine_line|#define DX_ACR0_AC97_W              0x40
DECL|macro|DX_ACR1_AC97_R
mdefine_line|#define DX_ACR1_AC97_R              0x44
DECL|macro|DX_ACR2_AC97_COM_STAT
mdefine_line|#define DX_ACR2_AC97_COM_STAT       0x48
DECL|macro|NX_ACR0_AC97_COM_STAT
mdefine_line|#define NX_ACR0_AC97_COM_STAT       0x40
DECL|macro|NX_ACR1_AC97_W
mdefine_line|#define NX_ACR1_AC97_W              0x44
DECL|macro|NX_ACR2_AC97_R_PRIMARY
mdefine_line|#define NX_ACR2_AC97_R_PRIMARY      0x48
DECL|macro|NX_ACR3_AC97_R_SECONDARY
mdefine_line|#define NX_ACR3_AC97_R_SECONDARY    0x4c
DECL|macro|AC97_SIGMATEL_DAC2INVERT
mdefine_line|#define AC97_SIGMATEL_DAC2INVERT    0x6E
DECL|macro|AC97_SIGMATEL_BIAS1
mdefine_line|#define AC97_SIGMATEL_BIAS1         0x70
DECL|macro|AC97_SIGMATEL_BIAS2
mdefine_line|#define AC97_SIGMATEL_BIAS2         0x72
DECL|macro|AC97_SIGMATEL_CIC1
mdefine_line|#define AC97_SIGMATEL_CIC1          0x76
DECL|macro|AC97_SIGMATEL_CIC2
mdefine_line|#define AC97_SIGMATEL_CIC2          0x78
macro_line|#endif&t;&t;&t;&t;/* __TRID4DWAVE_H */
eof
