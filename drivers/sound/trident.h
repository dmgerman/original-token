macro_line|#ifndef __TRID4DWAVE_H
DECL|macro|__TRID4DWAVE_H
mdefine_line|#define __TRID4DWAVE_H
multiline_comment|/*&n; *  audio@tridentmicro.com&n; *  Fri Feb 19 15:55:28 MST 1999&n; *  Definitions for Trident 4DWave DX/NX chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef PCI_VENDOR_ID_TRIDENT
DECL|macro|PCI_VENDOR_ID_TRIDENT
mdefine_line|#define PCI_VENDOR_ID_TRIDENT&t;&t;0x1023
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_SI
DECL|macro|PCI_VENDOR_ID_SI
mdefine_line|#define PCI_VENDOR_ID_SI&t;&t;&t;0x0139
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_DX
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_DX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_DX&t;0x2000
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TRIDENT_4DWAVE_NX
DECL|macro|PCI_DEVICE_ID_TRIDENT_4DWAVE_NX
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_4DWAVE_NX&t;0x2001
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_7018
DECL|macro|PCI_DEVICE_ID_SI_7018
mdefine_line|#define PCI_DEVICE_ID_SI_7018&t;&t;0x7018
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
mdefine_line|#define CHANNEL_REGS&t;5
DECL|macro|CHANNEL_START
mdefine_line|#define CHANNEL_START&t;0xe0   
singleline_comment|// The first bytes of the contiguous register space.
DECL|macro|BANK_A
mdefine_line|#define BANK_A 0
DECL|macro|BANK_B
mdefine_line|#define BANK_B 1
DECL|macro|NUM_BANKS
mdefine_line|#define NUM_BANKS 2
DECL|macro|ID_4DWAVE_DX
mdefine_line|#define ID_4DWAVE_DX&t;0x2000
DECL|macro|ID_4DWAVE_NX
mdefine_line|#define ID_4DWAVE_NX&t;0x2001
DECL|macro|ID_SI_7018
mdefine_line|#define ID_SI_7018&t;0x7018
singleline_comment|// Register definitions
singleline_comment|// Global registers
singleline_comment|// T2 legacy dma control registers.
DECL|macro|LEGACY_DMAR0
mdefine_line|#define LEGACY_DMAR0&t;&t;0x00  
singleline_comment|// ADR0
DECL|macro|LEGACY_DMAR4
mdefine_line|#define LEGACY_DMAR4&t;&t;0x04  
singleline_comment|// CNT0
DECL|macro|LEGACY_DMAR11
mdefine_line|#define LEGACY_DMAR11&t;&t;0x0b  
singleline_comment|// MOD 
DECL|macro|LEGACY_DMAR15
mdefine_line|#define LEGACY_DMAR15&t;&t;0x0f  
singleline_comment|// MMR 
DECL|macro|T4D_START_A
mdefine_line|#define T4D_START_A&t;&t;0x80
DECL|macro|T4D_STOP_A
mdefine_line|#define T4D_STOP_A&t;&t;0x84
DECL|macro|T4D_DLY_A
mdefine_line|#define T4D_DLY_A&t;&t;&t;0x88
DECL|macro|T4D_SIGN_CSO_A
mdefine_line|#define T4D_SIGN_CSO_A&t;&t;0x8c
DECL|macro|T4D_CSPF_A
mdefine_line|#define T4D_CSPF_A&t;&t;0x90
DECL|macro|T4D_CEBC_A
mdefine_line|#define T4D_CEBC_A&t;&t;0x94
DECL|macro|T4D_AINT_A
mdefine_line|#define T4D_AINT_A&t;&t;0x98
DECL|macro|T4D_EINT_A
mdefine_line|#define T4D_EINT_A&t;&t;0x9c
DECL|macro|T4D_LFO_GC_CIR
mdefine_line|#define T4D_LFO_GC_CIR&t;&t;0xa0
DECL|macro|T4D_AINTEN_A
mdefine_line|#define T4D_AINTEN_A&t;&t;0xa4
DECL|macro|T4D_MUSICVOL_WAVEVOL
mdefine_line|#define T4D_MUSICVOL_WAVEVOL&t;0xa8
DECL|macro|T4D_SBDELTA_DELTA_R
mdefine_line|#define T4D_SBDELTA_DELTA_R&t;0xac
DECL|macro|T4D_MISCINT
mdefine_line|#define T4D_MISCINT&t;&t;0xb0
DECL|macro|T4D_START_B
mdefine_line|#define T4D_START_B&t;&t;0xb4
DECL|macro|T4D_STOP_B
mdefine_line|#define T4D_STOP_B&t;&t;0xb8
DECL|macro|T4D_CSPF_B
mdefine_line|#define T4D_CSPF_B&t;&t;0xbc
DECL|macro|T4D_SBBL_SBCL
mdefine_line|#define T4D_SBBL_SBCL&t;&t;0xc0
DECL|macro|T4D_SBCTRL_SBE2R_SBDD
mdefine_line|#define T4D_SBCTRL_SBE2R_SBDD&t;0xc4
DECL|macro|T4D_STIMER
mdefine_line|#define T4D_STIMER&t;&t;0xc8
DECL|macro|T4D_LFO_B_I2S_DELTA
mdefine_line|#define T4D_LFO_B_I2S_DELTA&t;0xcc
DECL|macro|T4D_AINT_B
mdefine_line|#define T4D_AINT_B&t;&t;0xd8
DECL|macro|T4D_AINTEN_B
mdefine_line|#define T4D_AINTEN_B&t;&t;0xdc
singleline_comment|// MPU-401 UART
DECL|macro|T4D_MPU401_BASE
mdefine_line|#define T4D_MPU401_BASE&t;&t;0x20
DECL|macro|T4D_MPUR0
mdefine_line|#define T4D_MPUR0&t;&t;&t;0x20
DECL|macro|T4D_MPUR1
mdefine_line|#define T4D_MPUR1&t;&t;&t;0x21
DECL|macro|T4D_MPUR2
mdefine_line|#define T4D_MPUR2&t;&t;&t;0x22
DECL|macro|T4D_MPUR3
mdefine_line|#define T4D_MPUR3&t;&t;&t;0x23
singleline_comment|// S/PDIF Registers
DECL|macro|NX_SPCTRL_SPCSO
mdefine_line|#define NX_SPCTRL_SPCSO&t;&t;0x24
DECL|macro|NX_SPLBA
mdefine_line|#define NX_SPLBA&t;&t;&t;0x28
DECL|macro|NX_SPESO
mdefine_line|#define NX_SPESO&t;&t;&t;0x2c
DECL|macro|NX_SPCSTATUS
mdefine_line|#define NX_SPCSTATUS&t;&t;0x64
singleline_comment|// Channel Registers
DECL|macro|CH_DX_CSO_ALPHA_FMS
mdefine_line|#define CH_DX_CSO_ALPHA_FMS&t;0xe0
DECL|macro|CH_DX_ESO_DELTA
mdefine_line|#define CH_DX_ESO_DELTA&t;&t;0xe8
DECL|macro|CH_DX_FMC_RVOL_CVOL
mdefine_line|#define CH_DX_FMC_RVOL_CVOL&t;0xec
DECL|macro|CH_NX_DELTA_CSO
mdefine_line|#define CH_NX_DELTA_CSO&t;&t;0xe0
DECL|macro|CH_NX_DELTA_ESO
mdefine_line|#define CH_NX_DELTA_ESO&t;&t;0xe8
DECL|macro|CH_NX_ALPHA_FMS_FMC_RVOL_CVOL
mdefine_line|#define CH_NX_ALPHA_FMS_FMC_RVOL_CVOL 0xec
DECL|macro|CH_LBA
mdefine_line|#define CH_LBA&t;&t;&t;0xe4
DECL|macro|CH_GVSEL_PAN_VOL_CTRL_EC
mdefine_line|#define CH_GVSEL_PAN_VOL_CTRL_EC&t;0xf0
singleline_comment|// AC-97 Registers
DECL|macro|DX_ACR0_AC97_W
mdefine_line|#define DX_ACR0_AC97_W&t;&t;0x40
DECL|macro|DX_ACR1_AC97_R
mdefine_line|#define DX_ACR1_AC97_R&t;&t;0x44
DECL|macro|DX_ACR2_AC97_COM_STAT
mdefine_line|#define DX_ACR2_AC97_COM_STAT&t;0x48
DECL|macro|NX_ACR0_AC97_COM_STAT
mdefine_line|#define NX_ACR0_AC97_COM_STAT&t;0x40
DECL|macro|NX_ACR1_AC97_W
mdefine_line|#define NX_ACR1_AC97_W&t;&t;0x44
DECL|macro|NX_ACR2_AC97_R_PRIMARY
mdefine_line|#define NX_ACR2_AC97_R_PRIMARY&t;0x48
DECL|macro|NX_ACR3_AC97_R_SECONDARY
mdefine_line|#define NX_ACR3_AC97_R_SECONDARY&t;0x4c
DECL|macro|SI_AC97_WRITE
mdefine_line|#define SI_AC97_WRITE&t;&t;0x40
DECL|macro|SI_AC97_READ
mdefine_line|#define SI_AC97_READ&t;&t;0x44
DECL|macro|SI_SERIAL_INTF_CTRL
mdefine_line|#define SI_SERIAL_INTF_CTRL&t;0x48
DECL|macro|SI_AC97_GPIO
mdefine_line|#define SI_AC97_GPIO&t;&t;0x4c
DECL|macro|AC97_SIGMATEL_DAC2INVERT
mdefine_line|#define AC97_SIGMATEL_DAC2INVERT&t;0x6E
DECL|macro|AC97_SIGMATEL_BIAS1
mdefine_line|#define AC97_SIGMATEL_BIAS1&t;0x70
DECL|macro|AC97_SIGMATEL_BIAS2
mdefine_line|#define AC97_SIGMATEL_BIAS2&t;0x72
DECL|macro|AC97_SIGMATEL_CIC1
mdefine_line|#define AC97_SIGMATEL_CIC1&t;0x76
DECL|macro|AC97_SIGMATEL_CIC2
mdefine_line|#define AC97_SIGMATEL_CIC2&t;0x78
DECL|macro|SI_AC97_BUSY_WRITE
mdefine_line|#define SI_AC97_BUSY_WRITE 0x8000
DECL|macro|SI_AC97_AUDIO_BUSY
mdefine_line|#define SI_AC97_AUDIO_BUSY 0x4000
DECL|macro|DX_AC97_BUSY_WRITE
mdefine_line|#define DX_AC97_BUSY_WRITE 0x8000
DECL|macro|NX_AC97_BUSY_WRITE
mdefine_line|#define NX_AC97_BUSY_WRITE 0x0800
DECL|macro|SI_AC97_BUSY_READ
mdefine_line|#define SI_AC97_BUSY_READ  0x8000
DECL|macro|DX_AC97_BUSY_READ
mdefine_line|#define DX_AC97_BUSY_READ 0x8000
DECL|macro|NX_AC97_BUSY_READ
mdefine_line|#define NX_AC97_BUSY_READ 0x0800
DECL|macro|AC97_REG_ADDR
mdefine_line|#define AC97_REG_ADDR      0x000000ff
DECL|macro|DX_AC97_REG_ADDR
mdefine_line|#define DX_AC97_REG_ADDR   0x000000ff
DECL|macro|NX_AC97_REG_ADDR
mdefine_line|#define NX_AC97_REG_ADDR   0x000000ff
DECL|enum|global_control_bits
r_enum
id|global_control_bits
(brace
DECL|enumerator|CHANNLE_IDX
DECL|enumerator|PB_RESET
id|CHANNLE_IDX
op_assign
l_int|0x0000003f
comma
id|PB_RESET
op_assign
l_int|0x00000100
comma
DECL|enumerator|PAUSE_ENG
id|PAUSE_ENG
op_assign
l_int|0x00000200
comma
DECL|enumerator|OVERRUN_IE
DECL|enumerator|UNDERRUN_IE
id|OVERRUN_IE
op_assign
l_int|0x00000400
comma
id|UNDERRUN_IE
op_assign
l_int|0x00000800
comma
DECL|enumerator|ENDLP_IE
DECL|enumerator|MIDLP_IE
id|ENDLP_IE
op_assign
l_int|0x00001000
comma
id|MIDLP_IE
op_assign
l_int|0x00002000
comma
DECL|enumerator|ETOG_IE
id|ETOG_IE
op_assign
l_int|0x00004000
comma
DECL|enumerator|EDROP_IE
DECL|enumerator|BANK_B_EN
id|EDROP_IE
op_assign
l_int|0x00008000
comma
id|BANK_B_EN
op_assign
l_int|0x00010000
)brace
suffix:semicolon
DECL|enum|miscint_bits
r_enum
id|miscint_bits
(brace
DECL|enumerator|PB_UNDERRUN_IRO
DECL|enumerator|REC_OVERRUN_IRQ
id|PB_UNDERRUN_IRO
op_assign
l_int|0x00000001
comma
id|REC_OVERRUN_IRQ
op_assign
l_int|0x00000002
comma
DECL|enumerator|SB_IRQ
DECL|enumerator|MPU401_IRQ
id|SB_IRQ
op_assign
l_int|0x00000004
comma
id|MPU401_IRQ
op_assign
l_int|0x00000008
comma
DECL|enumerator|OPL3_IRQ
DECL|enumerator|ADDRESS_IRQ
id|OPL3_IRQ
op_assign
l_int|0x00000010
comma
id|ADDRESS_IRQ
op_assign
l_int|0x00000020
comma
DECL|enumerator|ENVELOPE_IRQ
DECL|enumerator|ST_IRQ
id|ENVELOPE_IRQ
op_assign
l_int|0x00000040
comma
id|ST_IRQ
op_assign
l_int|0x00000080
comma
DECL|enumerator|PB_UNDERRUN
DECL|enumerator|REC_OVERRUN
id|PB_UNDERRUN
op_assign
l_int|0x00000100
comma
id|REC_OVERRUN
op_assign
l_int|0x00000200
comma
DECL|enumerator|MIXER_UNDERFLOW
DECL|enumerator|MIXER_OVERFLOW
id|MIXER_UNDERFLOW
op_assign
l_int|0x00000400
comma
id|MIXER_OVERFLOW
op_assign
l_int|0x00000800
comma
DECL|enumerator|ST_TARGET_REACHED
DECL|enumerator|PB_24K_MODE
id|ST_TARGET_REACHED
op_assign
l_int|0x00008000
comma
id|PB_24K_MODE
op_assign
l_int|0x00010000
comma
DECL|enumerator|ST_IRQ_EN
DECL|enumerator|ACGPIO_IRQ
id|ST_IRQ_EN
op_assign
l_int|0x00800000
comma
id|ACGPIO_IRQ
op_assign
l_int|0x01000000
)brace
suffix:semicolon
DECL|macro|IWriteAinten
mdefine_line|#define IWriteAinten( x ) &bslash;&n;&t;{int i; &bslash;&n;&t; for( i= 0; i &lt; ChanDwordCount; i++) &bslash;&n;&t;&t;outl((x)-&gt;lpChAinten[i], TRID_REG(trident, (x)-&gt;lpAChAinten[i]));}
DECL|macro|IReadAinten
mdefine_line|#define IReadAinten( x ) &bslash;&n;&t;{int i; &bslash;&n;&t; for( i= 0; i &lt; ChanDwordCount; i++) &bslash;&n;&t; (x)-&gt;lpChAinten[i] = inl(TRID_REG(trident, (x)-&gt;lpAChAinten[i]));}
DECL|macro|ReadAint
mdefine_line|#define ReadAint( x ) &bslash;&n;&t;IReadAint( x ) 
DECL|macro|WriteAint
mdefine_line|#define WriteAint( x ) &bslash;&n;&t;IWriteAint( x ) 
DECL|macro|IWriteAint
mdefine_line|#define IWriteAint( x ) &bslash;&n;&t;{int i; &bslash;&n;&t; for( i= 0; i &lt; ChanDwordCount; i++) &bslash;&n;&t; outl((x)-&gt;lpChAint[i], TRID_REG(trident, (x)-&gt;lpAChAint[i]));}
DECL|macro|IReadAint
mdefine_line|#define IReadAint( x ) &bslash;&n;&t;{int i; &bslash;&n;&t; for( i= 0; i &lt; ChanDwordCount; i++) &bslash;&n;&t; (x)-&gt;lpChAint[i] = inl(TRID_REG(trident, (x)-&gt;lpAChAint[i]));}
DECL|macro|VALIDATE_MAGIC
mdefine_line|#define VALIDATE_MAGIC(FOO,MAG)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;if (!(FOO) || (FOO)-&gt;magic != MAG) { &bslash;&n;&t;&t;printk(invalid_magic,__FUNCTION__);&t;       &bslash;&n;&t;&t;return -ENXIO;&t;&t;&t;  &bslash;&n;&t;}&t;&t;&t;&t;&t;  &bslash;&n;})
DECL|macro|VALIDATE_STATE
mdefine_line|#define VALIDATE_STATE(a) VALIDATE_MAGIC(a,TRIDENT_STATE_MAGIC)
DECL|macro|VALIDATE_CARD
mdefine_line|#define VALIDATE_CARD(a) VALIDATE_MAGIC(a,TRIDENT_CARD_MAGIC)
macro_line|#endif /* __TRID4DWAVE_H */
eof
