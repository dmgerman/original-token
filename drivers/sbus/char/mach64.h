multiline_comment|/* $Id: mach64.h,v 1.3 1997/08/24 12:13:07 ecd Exp $&n; * mach64.h: Ultra/PCI mach64 driver constants etc.&n; *&n; * Copyright 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _MACH64_H
DECL|macro|_MACH64_H
mdefine_line|#define _MACH64_H 1
DECL|struct|mach64_info
r_struct
id|mach64_info
(brace
DECL|member|color_mode
r_int
r_int
id|color_mode
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|total_vram
r_int
r_int
id|total_vram
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The mach64_info flag bits. */
DECL|macro|MACH64_MASK_VT
mdefine_line|#define MACH64_MASK_VT&t;0x00000001
multiline_comment|/* NON-GUI MEMORY MAPPED Registers - expressed in BYTE offsets */
DECL|macro|CRTC_H_TOTAL_DISP
mdefine_line|#define CRTC_H_TOTAL_DISP       0x0000  /* Dword offset 00 */
DECL|macro|CRTC_H_SYNC_STRT_WID
mdefine_line|#define CRTC_H_SYNC_STRT_WID    0x0004  /* Dword offset 01 */
DECL|macro|CRTC_H_SYNC_STRT
mdefine_line|#define CRTC_H_SYNC_STRT        0x0004
DECL|macro|CRTC_H_SYNC_DLY
mdefine_line|#define CRTC_H_SYNC_DLY         0x0005
DECL|macro|CRTC_H_SYNC_WID
mdefine_line|#define CRTC_H_SYNC_WID         0x0006
DECL|macro|CRTC_V_TOTAL_DISP
mdefine_line|#define CRTC_V_TOTAL_DISP       0x0008  /* Dword offset 02 */
DECL|macro|CRTC_V_TOTAL
mdefine_line|#define CRTC_V_TOTAL            0x0008
DECL|macro|CRTC_V_DISP
mdefine_line|#define CRTC_V_DISP             0x000a
DECL|macro|CRTC_V_SYNC_STRT_WID
mdefine_line|#define CRTC_V_SYNC_STRT_WID    0x000C  /* Dword offset 03 */
DECL|macro|CRTC_V_SYNC_STRT
mdefine_line|#define CRTC_V_SYNC_STRT        0x000c
DECL|macro|CRTC_V_SYNC_WID
mdefine_line|#define CRTC_V_SYNC_WID         0x000e
DECL|macro|CRTC_VLINE_CRNT_VLINE
mdefine_line|#define CRTC_VLINE_CRNT_VLINE   0x0010  /* Dword offset 04 */
DECL|macro|CRTC_OFF_PITCH
mdefine_line|#define CRTC_OFF_PITCH          0x0014  /* Dword offset 05 */
DECL|macro|CRTC_OFFSET
mdefine_line|#define CRTC_OFFSET             0x0014
DECL|macro|CRTC_PITCH
mdefine_line|#define CRTC_PITCH              0x0016
DECL|macro|CRTC_INT_CNTL
mdefine_line|#define CRTC_INT_CNTL           0x0018  /* Dword offset 06 */
DECL|macro|CRTC_GEN_CNTL
mdefine_line|#define CRTC_GEN_CNTL           0x001C  /* Dword offset 07 */
DECL|macro|CRTC_PIX_WIDTH
mdefine_line|#define CRTC_PIX_WIDTH          0x001d
DECL|macro|CRTC_FIFO
mdefine_line|#define CRTC_FIFO               0x001e
DECL|macro|CRTC_EXT_DISP
mdefine_line|#define CRTC_EXT_DISP           0x001f
DECL|macro|OVR_CLR
mdefine_line|#define OVR_CLR                 0x0040  /* Dword offset 10 */
DECL|macro|OVR_WID_LEFT_RIGHT
mdefine_line|#define OVR_WID_LEFT_RIGHT      0x0044  /* Dword offset 11 */
DECL|macro|OVR_WID_TOP_BOTTOM
mdefine_line|#define OVR_WID_TOP_BOTTOM      0x0048  /* Dword offset 12 */
DECL|macro|CUR_CLR0
mdefine_line|#define CUR_CLR0                0x0060  /* Dword offset 18 */
DECL|macro|CUR_CLR1
mdefine_line|#define CUR_CLR1                0x0064  /* Dword offset 19 */
DECL|macro|CUR_OFFSET
mdefine_line|#define CUR_OFFSET              0x0068  /* Dword offset 1A */
DECL|macro|CUR_HORZ_VERT_POSN
mdefine_line|#define CUR_HORZ_VERT_POSN      0x006C  /* Dword offset 1B */
DECL|macro|CUR_HORZ_VERT_OFF
mdefine_line|#define CUR_HORZ_VERT_OFF       0x0070  /* Dword offset 1C */
DECL|macro|SCRATCH_REG0
mdefine_line|#define SCRATCH_REG0            0x0080  /* Dword offset 20 */
DECL|macro|SCRATCH_REG1
mdefine_line|#define SCRATCH_REG1            0x0084  /* Dword offset 21 */
DECL|macro|CLOCK_CNTL
mdefine_line|#define CLOCK_CNTL              0x0090  /* Dword offset 24 */
DECL|macro|CLOCK_SEL_CNTL
mdefine_line|#define CLOCK_SEL_CNTL          0x0090  
singleline_comment|// Dword offset 24
DECL|macro|BUS_CNTL
mdefine_line|#define BUS_CNTL                0x00A0  /* Dword offset 28 */
DECL|macro|MEM_CNTL
mdefine_line|#define MEM_CNTL                0x00B0  /* Dword offset 2C */
DECL|macro|MEM_VGA_WP_SEL
mdefine_line|#define MEM_VGA_WP_SEL          0x00B4  /* Dword offset 2D */
DECL|macro|MEM_VGA_RP_SEL
mdefine_line|#define MEM_VGA_RP_SEL          0x00B8  /* Dword offset 2E */
DECL|macro|DAC_REGS
mdefine_line|#define DAC_REGS                0x00C0  /* Dword offset 30 */
DECL|macro|DAC_W_INDEX
mdefine_line|#define DAC_W_INDEX             0x00C0  /* Dword offset 30 */
DECL|macro|DAC_DATA
mdefine_line|#define DAC_DATA                0x00C1  /* Dword offset 30 */
DECL|macro|DAC_MASK
mdefine_line|#define DAC_MASK                0x00C2  /* Dword offset 30 */
DECL|macro|DAC_R_INDEX
mdefine_line|#define DAC_R_INDEX             0x00C3  /* Dword offset 30 */
DECL|macro|DAC_CNTL
mdefine_line|#define DAC_CNTL                0x00C4  /* Dword offset 31 */
DECL|macro|GEN_TEST_CNTL
mdefine_line|#define GEN_TEST_CNTL           0x00D0  /* Dword offset 34 */
DECL|macro|CONFIG_CNTL
mdefine_line|#define CONFIG_CNTL&t;&t;0x00DC&t;/* Dword offset 37 (CT, ET, VT) */
DECL|macro|CONFIG_CHIP_ID
mdefine_line|#define CONFIG_CHIP_ID          0x00E0  /* Dword offset 38 */
DECL|macro|CONFIG_STAT0
mdefine_line|#define CONFIG_STAT0            0x00E4  /* Dword offset 39 */
DECL|macro|CONFIG_STAT1
mdefine_line|#define CONFIG_STAT1            0x00E8  /* Dword offset 3A */
multiline_comment|/* GUI MEMORY MAPPED Registers */
DECL|macro|DST_OFF_PITCH
mdefine_line|#define DST_OFF_PITCH           0x0100  /* Dword offset 40 */
DECL|macro|DST_X
mdefine_line|#define DST_X                   0x0104  /* Dword offset 41 */
DECL|macro|DST_Y
mdefine_line|#define DST_Y                   0x0108  /* Dword offset 42 */
DECL|macro|DST_Y_X
mdefine_line|#define DST_Y_X                 0x010C  /* Dword offset 43 */
DECL|macro|DST_WIDTH
mdefine_line|#define DST_WIDTH               0x0110  /* Dword offset 44 */
DECL|macro|DST_HEIGHT
mdefine_line|#define DST_HEIGHT              0x0114  /* Dword offset 45 */
DECL|macro|DST_HEIGHT_WIDTH
mdefine_line|#define DST_HEIGHT_WIDTH        0x0118  /* Dword offset 46 */
DECL|macro|DST_X_WIDTH
mdefine_line|#define DST_X_WIDTH             0x011C  /* Dword offset 47 */
DECL|macro|DST_BRES_LNTH
mdefine_line|#define DST_BRES_LNTH           0x0120  /* Dword offset 48 */
DECL|macro|DST_BRES_ERR
mdefine_line|#define DST_BRES_ERR            0x0124  /* Dword offset 49 */
DECL|macro|DST_BRES_INC
mdefine_line|#define DST_BRES_INC            0x0128  /* Dword offset 4A */
DECL|macro|DST_BRES_DEC
mdefine_line|#define DST_BRES_DEC            0x012C  /* Dword offset 4B */
DECL|macro|DST_CNTL
mdefine_line|#define DST_CNTL                0x0130  /* Dword offset 4C */
DECL|macro|SRC_OFF_PITCH
mdefine_line|#define SRC_OFF_PITCH           0x0180  /* Dword offset 60 */
DECL|macro|SRC_X
mdefine_line|#define SRC_X                   0x0184  /* Dword offset 61 */
DECL|macro|SRC_Y
mdefine_line|#define SRC_Y                   0x0188  /* Dword offset 62 */
DECL|macro|SRC_Y_X
mdefine_line|#define SRC_Y_X                 0x018C  /* Dword offset 63 */
DECL|macro|SRC_WIDTH1
mdefine_line|#define SRC_WIDTH1              0x0190  /* Dword offset 64 */
DECL|macro|SRC_HEIGHT1
mdefine_line|#define SRC_HEIGHT1             0x0194  /* Dword offset 65 */
DECL|macro|SRC_HEIGHT1_WIDTH1
mdefine_line|#define SRC_HEIGHT1_WIDTH1      0x0198  /* Dword offset 66 */
DECL|macro|SRC_X_START
mdefine_line|#define SRC_X_START             0x019C  /* Dword offset 67 */
DECL|macro|SRC_Y_START
mdefine_line|#define SRC_Y_START             0x01A0  /* Dword offset 68 */
DECL|macro|SRC_Y_X_START
mdefine_line|#define SRC_Y_X_START           0x01A4  /* Dword offset 69 */
DECL|macro|SRC_WIDTH2
mdefine_line|#define SRC_WIDTH2              0x01A8  /* Dword offset 6A */
DECL|macro|SRC_HEIGHT2
mdefine_line|#define SRC_HEIGHT2             0x01AC  /* Dword offset 6B */
DECL|macro|SRC_HEIGHT2_WIDTH2
mdefine_line|#define SRC_HEIGHT2_WIDTH2      0x01B0  /* Dword offset 6C */
DECL|macro|SRC_CNTL
mdefine_line|#define SRC_CNTL                0x01B4  /* Dword offset 6D */
DECL|macro|HOST_DATA0
mdefine_line|#define HOST_DATA0              0x0200  /* Dword offset 80 */
DECL|macro|HOST_DATA1
mdefine_line|#define HOST_DATA1              0x0204  /* Dword offset 81 */
DECL|macro|HOST_DATA2
mdefine_line|#define HOST_DATA2              0x0208  /* Dword offset 82 */
DECL|macro|HOST_DATA3
mdefine_line|#define HOST_DATA3              0x020C  /* Dword offset 83 */
DECL|macro|HOST_DATA4
mdefine_line|#define HOST_DATA4              0x0210  /* Dword offset 84 */
DECL|macro|HOST_DATA5
mdefine_line|#define HOST_DATA5              0x0214  /* Dword offset 85 */
DECL|macro|HOST_DATA6
mdefine_line|#define HOST_DATA6              0x0218  /* Dword offset 86 */
DECL|macro|HOST_DATA7
mdefine_line|#define HOST_DATA7              0x021C  /* Dword offset 87 */
DECL|macro|HOST_DATA8
mdefine_line|#define HOST_DATA8              0x0220  /* Dword offset 88 */
DECL|macro|HOST_DATA9
mdefine_line|#define HOST_DATA9              0x0224  /* Dword offset 89 */
DECL|macro|HOST_DATAA
mdefine_line|#define HOST_DATAA              0x0228  /* Dword offset 8A */
DECL|macro|HOST_DATAB
mdefine_line|#define HOST_DATAB              0x022C  /* Dword offset 8B */
DECL|macro|HOST_DATAC
mdefine_line|#define HOST_DATAC              0x0230  /* Dword offset 8C */
DECL|macro|HOST_DATAD
mdefine_line|#define HOST_DATAD              0x0234  /* Dword offset 8D */
DECL|macro|HOST_DATAE
mdefine_line|#define HOST_DATAE              0x0238  /* Dword offset 8E */
DECL|macro|HOST_DATAF
mdefine_line|#define HOST_DATAF              0x023C  /* Dword offset 8F */
DECL|macro|HOST_CNTL
mdefine_line|#define HOST_CNTL               0x0240  /* Dword offset 90 */
DECL|macro|PAT_REG0
mdefine_line|#define PAT_REG0                0x0280  /* Dword offset A0 */
DECL|macro|PAT_REG1
mdefine_line|#define PAT_REG1                0x0284  /* Dword offset A1 */
DECL|macro|PAT_CNTL
mdefine_line|#define PAT_CNTL                0x0288  /* Dword offset A2 */
DECL|macro|SC_LEFT
mdefine_line|#define SC_LEFT                 0x02A0  /* Dword offset A8 */
DECL|macro|SC_RIGHT
mdefine_line|#define SC_RIGHT                0x02A4  /* Dword offset A9 */
DECL|macro|SC_LEFT_RIGHT
mdefine_line|#define SC_LEFT_RIGHT           0x02A8  /* Dword offset AA */
DECL|macro|SC_TOP
mdefine_line|#define SC_TOP                  0x02AC  /* Dword offset AB */
DECL|macro|SC_BOTTOM
mdefine_line|#define SC_BOTTOM               0x02B0  /* Dword offset AC */
DECL|macro|SC_TOP_BOTTOM
mdefine_line|#define SC_TOP_BOTTOM           0x02B4  /* Dword offset AD */
DECL|macro|DP_BKGD_CLR
mdefine_line|#define DP_BKGD_CLR             0x02C0  /* Dword offset B0 */
DECL|macro|DP_FRGD_CLR
mdefine_line|#define DP_FRGD_CLR             0x02C4  /* Dword offset B1 */
DECL|macro|DP_WRITE_MASK
mdefine_line|#define DP_WRITE_MASK           0x02C8  /* Dword offset B2 */
DECL|macro|DP_CHAIN_MASK
mdefine_line|#define DP_CHAIN_MASK           0x02CC  /* Dword offset B3 */
DECL|macro|DP_PIX_WIDTH
mdefine_line|#define DP_PIX_WIDTH            0x02D0  /* Dword offset B4 */
DECL|macro|DP_MIX
mdefine_line|#define DP_MIX                  0x02D4  /* Dword offset B5 */
DECL|macro|DP_SRC
mdefine_line|#define DP_SRC                  0x02D8  /* Dword offset B6 */
DECL|macro|CLR_CMP_CLR
mdefine_line|#define CLR_CMP_CLR             0x0300  /* Dword offset C0 */
DECL|macro|CLR_CMP_MASK
mdefine_line|#define CLR_CMP_MASK            0x0304  /* Dword offset C1 */
DECL|macro|CLR_CMP_CNTL
mdefine_line|#define CLR_CMP_CNTL            0x0308  /* Dword offset C2 */
DECL|macro|FIFO_STAT
mdefine_line|#define FIFO_STAT               0x0310  /* Dword offset C4 */
DECL|macro|CONTEXT_MASK
mdefine_line|#define CONTEXT_MASK            0x0320  /* Dword offset C8 */
DECL|macro|CONTEXT_LOAD_CNTL
mdefine_line|#define CONTEXT_LOAD_CNTL       0x032C  /* Dword offset CB */
DECL|macro|GUI_TRAJ_CNTL
mdefine_line|#define GUI_TRAJ_CNTL           0x0330  /* Dword offset CC */
DECL|macro|GUI_STAT
mdefine_line|#define GUI_STAT                0x0338  /* Dword offset CE */
multiline_comment|/* CRTC control values (mostly CRTC_GEN_CNTL) */
DECL|macro|CRTC_H_SYNC_NEG
mdefine_line|#define CRTC_H_SYNC_NEG&t;&t;0x00200000
DECL|macro|CRTC_V_SYNC_NEG
mdefine_line|#define CRTC_V_SYNC_NEG&t;&t;0x00200000
DECL|macro|CRTC_DBL_SCAN_EN
mdefine_line|#define CRTC_DBL_SCAN_EN&t;0x00000001
DECL|macro|CRTC_INTERLACE_EN
mdefine_line|#define CRTC_INTERLACE_EN&t;0x00000002
DECL|macro|CRTC_HSYNC_DIS
mdefine_line|#define CRTC_HSYNC_DIS&t;&t;0x00000004
DECL|macro|CRTC_VSYNC_DIS
mdefine_line|#define CRTC_VSYNC_DIS&t;&t;0x00000008
DECL|macro|CRTC_CSYNC_EN
mdefine_line|#define CRTC_CSYNC_EN&t;&t;0x00000010
DECL|macro|CRTC_PIX_BY_2_EN
mdefine_line|#define CRTC_PIX_BY_2_EN&t;0x00000020
DECL|macro|CRTC_BLANK
mdefine_line|#define CRTC_BLANK&t;&t;0x00000040
DECL|macro|CRTC_PIX_WIDTH_MASK
mdefine_line|#define CRTC_PIX_WIDTH_MASK&t;0x00000700
DECL|macro|CRTC_PIX_WIDTH_4BPP
mdefine_line|#define CRTC_PIX_WIDTH_4BPP&t;0x00000100
DECL|macro|CRTC_PIX_WIDTH_8BPP
mdefine_line|#define CRTC_PIX_WIDTH_8BPP&t;0x00000200
DECL|macro|CRTC_PIX_WIDTH_15BPP
mdefine_line|#define CRTC_PIX_WIDTH_15BPP&t;0x00000300
DECL|macro|CRTC_PIX_WIDTH_16BPP
mdefine_line|#define CRTC_PIX_WIDTH_16BPP&t;0x00000400
DECL|macro|CRTC_PIX_WIDTH_24BPP
mdefine_line|#define CRTC_PIX_WIDTH_24BPP&t;0x00000500
DECL|macro|CRTC_PIX_WIDTH_32BPP
mdefine_line|#define CRTC_PIX_WIDTH_32BPP&t;0x00000600
DECL|macro|CRTC_BYTE_PIX_ORDER
mdefine_line|#define CRTC_BYTE_PIX_ORDER&t;0x00000800
DECL|macro|CRTC_PIX_ORDER_MSN_LSN
mdefine_line|#define CRTC_PIX_ORDER_MSN_LSN&t;0x00000000
DECL|macro|CRTC_PIX_ORDER_LSN_MSN
mdefine_line|#define CRTC_PIX_ORDER_LSN_MSN&t;0x00000800
DECL|macro|CRTC_FIFO_LWM
mdefine_line|#define CRTC_FIFO_LWM&t;&t;0x000f0000
DECL|macro|CRTC_EXT_DISP_EN
mdefine_line|#define CRTC_EXT_DISP_EN&t;0x01000000
DECL|macro|CRTC_EXT_EN
mdefine_line|#define CRTC_EXT_EN&t;&t;0x02000000
DECL|macro|CRTC_CRNT_VLINE
mdefine_line|#define CRTC_CRNT_VLINE&t;&t;0x07f00000
DECL|macro|CRTC_VBLANK
mdefine_line|#define CRTC_VBLANK&t;&t;0x00000001
multiline_comment|/* DAC control values */
DECL|macro|DAC_EXT_SEL_RS2
mdefine_line|#define DAC_EXT_SEL_RS2&t;&t;0x01
DECL|macro|DAC_EXT_SEL_RS3
mdefine_line|#define DAC_EXT_SEL_RS3&t;&t;0x02
DECL|macro|DAC_8BIT_EN
mdefine_line|#define DAC_8BIT_EN&t;&t;0x00000100
DECL|macro|DAC_PIX_DLY_MASK
mdefine_line|#define DAC_PIX_DLY_MASK&t;0x00000600
DECL|macro|DAC_PIX_DLY_0NS
mdefine_line|#define DAC_PIX_DLY_0NS&t;&t;0x00000000
DECL|macro|DAC_PIX_DLY_2NS
mdefine_line|#define DAC_PIX_DLY_2NS&t;&t;0x00000200
DECL|macro|DAC_PIX_DLY_4NS
mdefine_line|#define DAC_PIX_DLY_4NS&t;&t;0x00000400
DECL|macro|DAC_BLANK_ADJ_MASK
mdefine_line|#define DAC_BLANK_ADJ_MASK&t;0x00001800
DECL|macro|DAC_BLANK_ADJ_0
mdefine_line|#define DAC_BLANK_ADJ_0&t;&t;0x00000000
DECL|macro|DAC_BLANK_ADJ_1
mdefine_line|#define DAC_BLANK_ADJ_1&t;&t;0x00000800
DECL|macro|DAC_BLANK_ADJ_2
mdefine_line|#define DAC_BLANK_ADJ_2&t;&t;0x00001000
multiline_comment|/* Mix control values */
DECL|macro|MIX_NOT_DST
mdefine_line|#define MIX_NOT_DST                     0x0000
DECL|macro|MIX_0
mdefine_line|#define MIX_0                           0x0001
DECL|macro|MIX_1
mdefine_line|#define MIX_1                           0x0002
DECL|macro|MIX_DST
mdefine_line|#define MIX_DST                         0x0003
DECL|macro|MIX_NOT_SRC
mdefine_line|#define MIX_NOT_SRC                     0x0004
DECL|macro|MIX_XOR
mdefine_line|#define MIX_XOR                         0x0005
DECL|macro|MIX_XNOR
mdefine_line|#define MIX_XNOR                        0x0006
DECL|macro|MIX_SRC
mdefine_line|#define MIX_SRC                         0x0007
DECL|macro|MIX_NAND
mdefine_line|#define MIX_NAND                        0x0008
DECL|macro|MIX_NOT_SRC_OR_DST
mdefine_line|#define MIX_NOT_SRC_OR_DST              0x0009
DECL|macro|MIX_SRC_OR_NOT_DST
mdefine_line|#define MIX_SRC_OR_NOT_DST              0x000a
DECL|macro|MIX_OR
mdefine_line|#define MIX_OR                          0x000b
DECL|macro|MIX_AND
mdefine_line|#define MIX_AND                         0x000c
DECL|macro|MIX_SRC_AND_NOT_DST
mdefine_line|#define MIX_SRC_AND_NOT_DST             0x000d
DECL|macro|MIX_NOT_SRC_AND_DST
mdefine_line|#define MIX_NOT_SRC_AND_DST             0x000e
DECL|macro|MIX_NOR
mdefine_line|#define MIX_NOR                         0x000f
multiline_comment|/* Maximum engine dimensions */
DECL|macro|ENGINE_MIN_X
mdefine_line|#define ENGINE_MIN_X        0
DECL|macro|ENGINE_MIN_Y
mdefine_line|#define ENGINE_MIN_Y        0
DECL|macro|ENGINE_MAX_X
mdefine_line|#define ENGINE_MAX_X        4095
DECL|macro|ENGINE_MAX_Y
mdefine_line|#define ENGINE_MAX_Y        16383
multiline_comment|/* Mach64 engine bit constants - these are typically ORed together */
multiline_comment|/* BUS_CNTL register constants */
DECL|macro|BUS_FIFO_ERR_ACK
mdefine_line|#define BUS_FIFO_ERR_ACK        0x00200000
DECL|macro|BUS_HOST_ERR_ACK
mdefine_line|#define BUS_HOST_ERR_ACK        0x00800000
multiline_comment|/* GEN_TEST_CNTL register constants */
DECL|macro|GEN_OVR_OUTPUT_EN
mdefine_line|#define GEN_OVR_OUTPUT_EN       0x20
DECL|macro|HWCURSOR_ENABLE
mdefine_line|#define HWCURSOR_ENABLE         0x80
DECL|macro|GUI_ENGINE_ENABLE
mdefine_line|#define GUI_ENGINE_ENABLE       0x100
DECL|macro|BLOCK_WRITE_ENABLE
mdefine_line|#define BLOCK_WRITE_ENABLE      0x200
multiline_comment|/* CLOCK_CNTL register constants */
DECL|macro|CLOCK_SEL
mdefine_line|#define CLOCK_SEL&t;&t;0x0f
DECL|macro|CLOCK_DIV
mdefine_line|#define CLOCK_DIV&t;&t;0x30
DECL|macro|CLOCK_DIV1
mdefine_line|#define CLOCK_DIV1&t;&t;0x00
DECL|macro|CLOCK_DIV2
mdefine_line|#define CLOCK_DIV2&t;&t;0x10
DECL|macro|CLOCK_DIV4
mdefine_line|#define CLOCK_DIV4&t;&t;0x20
DECL|macro|CLOCK_STROBE
mdefine_line|#define CLOCK_STROBE&t;&t;0x40
DECL|macro|PLL_WR_EN
mdefine_line|#define PLL_WR_EN&t;&t;0x02
multiline_comment|/* PLL registers */
DECL|macro|PLL_MACRO_CNTL
mdefine_line|#define PLL_MACRO_CNTL&t;&t;0x01
DECL|macro|PLL_REF_DIV
mdefine_line|#define PLL_REF_DIV&t;&t;0x02
DECL|macro|PLL_GEN_CNTL
mdefine_line|#define PLL_GEN_CNTL&t;&t;0x03
DECL|macro|MCLK_FB_DIV
mdefine_line|#define MCLK_FB_DIV&t;&t;0x04
DECL|macro|PLL_VCLK_CNTL
mdefine_line|#define PLL_VCLK_CNTL&t;&t;0x05
DECL|macro|VCLK_POST_DIV
mdefine_line|#define VCLK_POST_DIV&t;&t;0x06
DECL|macro|VCLK0_FB_DIV
mdefine_line|#define VCLK0_FB_DIV&t;&t;0x07
DECL|macro|VCLK1_FB_DIV
mdefine_line|#define VCLK1_FB_DIV&t;&t;0x08
DECL|macro|VCLK2_FB_DIV
mdefine_line|#define VCLK2_FB_DIV&t;&t;0x09
DECL|macro|VCLK3_FB_DIV
mdefine_line|#define VCLK3_FB_DIV&t;&t;0x0A
DECL|macro|PLL_XCLK_CNTL
mdefine_line|#define PLL_XCLK_CNTL&t;&t;0x0B
DECL|macro|PLL_TEST_CTRL
mdefine_line|#define PLL_TEST_CTRL&t;&t;0x0E
DECL|macro|PLL_TEST_COUNT
mdefine_line|#define PLL_TEST_COUNT&t;&t;0x0F
multiline_comment|/* Fields in PLL registers */
DECL|macro|PLL_PC_GAIN
mdefine_line|#define PLL_PC_GAIN&t;&t;0x07
DECL|macro|PLL_VC_GAIN
mdefine_line|#define PLL_VC_GAIN&t;&t;0x18
DECL|macro|PLL_DUTY_CYC
mdefine_line|#define PLL_DUTY_CYC&t;&t;0xE0
DECL|macro|PLL_OVERRIDE
mdefine_line|#define PLL_OVERRIDE&t;&t;0x01
DECL|macro|PLL_MCLK_RST
mdefine_line|#define PLL_MCLK_RST&t;&t;0x02
DECL|macro|OSC_EN
mdefine_line|#define OSC_EN&t;&t;&t;0x04
DECL|macro|EXT_CLK_EN
mdefine_line|#define EXT_CLK_EN&t;&t;0x08
DECL|macro|MCLK_SRC_SEL
mdefine_line|#define MCLK_SRC_SEL&t;&t;0x70
DECL|macro|EXT_CLK_CNTL
mdefine_line|#define EXT_CLK_CNTL&t;&t;0x80
DECL|macro|VCLK_SRC_SEL
mdefine_line|#define VCLK_SRC_SEL&t;&t;0x03
DECL|macro|PLL_VCLK_RST
mdefine_line|#define PLL_VCLK_RST&t;&t;0x04
DECL|macro|VCLK_INVERT
mdefine_line|#define VCLK_INVERT&t;&t;0x08
DECL|macro|VCLK0_POST
mdefine_line|#define VCLK0_POST&t;&t;0x03
DECL|macro|VCLK1_POST
mdefine_line|#define VCLK1_POST&t;&t;0x0C
DECL|macro|VCLK2_POST
mdefine_line|#define VCLK2_POST&t;&t;0x30
DECL|macro|VCLK3_POST
mdefine_line|#define VCLK3_POST&t;&t;0xC0
multiline_comment|/* CONFIG_CNTL register constants */
DECL|macro|APERTURE_4M_ENABLE
mdefine_line|#define APERTURE_4M_ENABLE      1
DECL|macro|APERTURE_8M_ENABLE
mdefine_line|#define APERTURE_8M_ENABLE      2
DECL|macro|VGA_APERTURE_ENABLE
mdefine_line|#define VGA_APERTURE_ENABLE     4
multiline_comment|/* CONFIG_STAT0 register constants (GX, CX) */
DECL|macro|CFG_BUS_TYPE
mdefine_line|#define CFG_BUS_TYPE&t;&t;0x00000007
DECL|macro|CFG_MEM_TYPE
mdefine_line|#define CFG_MEM_TYPE&t;&t;0x00000038
DECL|macro|CFG_INIT_DAC_TYPE
mdefine_line|#define CFG_INIT_DAC_TYPE&t;0x00000e00
multiline_comment|/* CONFIG_STAT0 register constants (CT, ET, VT) */
DECL|macro|CFG_MEM_TYPE_xT
mdefine_line|#define CFG_MEM_TYPE_xT&t;&t;0x00000007
DECL|macro|ISA
mdefine_line|#define ISA&t;&t;&t;0
DECL|macro|EISA
mdefine_line|#define EISA&t;&t;&t;1
DECL|macro|LOCAL_BUS
mdefine_line|#define LOCAL_BUS&t;&t;6
DECL|macro|PCI
mdefine_line|#define PCI&t;&t;&t;7
multiline_comment|/* Memory types for GX, CX */
DECL|macro|DRAMx4
mdefine_line|#define DRAMx4&t;&t;&t;0
DECL|macro|VRAMx16
mdefine_line|#define VRAMx16&t;&t;&t;1
DECL|macro|VRAMx16ssr
mdefine_line|#define VRAMx16ssr&t;&t;2
DECL|macro|DRAMx16
mdefine_line|#define DRAMx16&t;&t;&t;3
DECL|macro|GraphicsDRAMx16
mdefine_line|#define GraphicsDRAMx16&t;&t;4
DECL|macro|EnhancedVRAMx16
mdefine_line|#define EnhancedVRAMx16&t;&t;5
DECL|macro|EnhancedVRAMx16ssr
mdefine_line|#define EnhancedVRAMx16ssr&t;6
multiline_comment|/* Memory types for CT, ET, VT, GT */
DECL|macro|DRAM
mdefine_line|#define DRAM&t;&t;&t;0
DECL|macro|EDO_DRAM
mdefine_line|#define EDO_DRAM&t;&t;1
DECL|macro|PSEUDO_EDO
mdefine_line|#define PSEUDO_EDO&t;&t;2
DECL|macro|SDRAM
mdefine_line|#define SDRAM&t;&t;&t;3
DECL|macro|DAC_INTERNAL
mdefine_line|#define DAC_INTERNAL&t;&t;0x00
DECL|macro|DAC_IBMRGB514
mdefine_line|#define DAC_IBMRGB514&t;&t;0x01
DECL|macro|DAC_ATI68875
mdefine_line|#define DAC_ATI68875&t;&t;0x02
DECL|macro|DAC_TVP3026_A
mdefine_line|#define DAC_TVP3026_A&t;&t;0x72
DECL|macro|DAC_BT476
mdefine_line|#define DAC_BT476&t;&t;0x03
DECL|macro|DAC_BT481
mdefine_line|#define DAC_BT481&t;&t;0x04
DECL|macro|DAC_ATT20C491
mdefine_line|#define DAC_ATT20C491&t;&t;0x14
DECL|macro|DAC_SC15026
mdefine_line|#define DAC_SC15026&t;&t;0x24
DECL|macro|DAC_MU9C1880
mdefine_line|#define DAC_MU9C1880&t;&t;0x34
DECL|macro|DAC_IMSG174
mdefine_line|#define DAC_IMSG174&t;&t;0x44
DECL|macro|DAC_ATI68860_B
mdefine_line|#define DAC_ATI68860_B&t;&t;0x05
DECL|macro|DAC_ATI68860_C
mdefine_line|#define DAC_ATI68860_C&t;&t;0x15
DECL|macro|DAC_TVP3026_B
mdefine_line|#define DAC_TVP3026_B&t;&t;0x75
DECL|macro|DAC_STG1700
mdefine_line|#define DAC_STG1700&t;&t;0x06
DECL|macro|DAC_ATT498
mdefine_line|#define DAC_ATT498&t;&t;0x16
DECL|macro|DAC_STG1702
mdefine_line|#define DAC_STG1702&t;&t;0x07
DECL|macro|DAC_SC15021
mdefine_line|#define DAC_SC15021&t;&t;0x17
DECL|macro|DAC_ATT21C498
mdefine_line|#define DAC_ATT21C498&t;&t;0x27
DECL|macro|DAC_STG1703
mdefine_line|#define DAC_STG1703&t;&t;0x37
DECL|macro|DAC_CH8398
mdefine_line|#define DAC_CH8398&t;&t;0x47
DECL|macro|DAC_ATT20C408
mdefine_line|#define DAC_ATT20C408&t;&t;0x57
DECL|macro|CLK_ATI18818_0
mdefine_line|#define CLK_ATI18818_0&t;&t;0
DECL|macro|CLK_ATI18818_1
mdefine_line|#define CLK_ATI18818_1&t;&t;1
DECL|macro|CLK_STG1703
mdefine_line|#define CLK_STG1703&t;&t;2
DECL|macro|CLK_CH8398
mdefine_line|#define CLK_CH8398&t;&t;3
DECL|macro|CLK_INTERNAL
mdefine_line|#define CLK_INTERNAL&t;&t;4
DECL|macro|CLK_ATT20C408
mdefine_line|#define CLK_ATT20C408&t;&t;5
DECL|macro|CLK_IBMRGB514
mdefine_line|#define CLK_IBMRGB514&t;&t;6
multiline_comment|/* MEM_CNTL register constants */
DECL|macro|MEM_SIZE_ALIAS
mdefine_line|#define MEM_SIZE_ALIAS&t;&t;0x00000007
DECL|macro|MEM_SIZE_512K
mdefine_line|#define MEM_SIZE_512K&t;&t;0x00000000
DECL|macro|MEM_SIZE_1M
mdefine_line|#define MEM_SIZE_1M&t;&t;0x00000001
DECL|macro|MEM_SIZE_2M
mdefine_line|#define MEM_SIZE_2M&t;&t;0x00000002
DECL|macro|MEM_SIZE_4M
mdefine_line|#define MEM_SIZE_4M&t;&t;0x00000003
DECL|macro|MEM_SIZE_6M
mdefine_line|#define MEM_SIZE_6M&t;&t;0x00000004
DECL|macro|MEM_SIZE_8M
mdefine_line|#define MEM_SIZE_8M&t;&t;0x00000005
DECL|macro|MEM_SIZE_ALIAS_GTB
mdefine_line|#define MEM_SIZE_ALIAS_GTB&t;0x0000000F
DECL|macro|MEM_SIZE_2M_GTB
mdefine_line|#define MEM_SIZE_2M_GTB&t;&t;0x00000003
DECL|macro|MEM_SIZE_4M_GTB
mdefine_line|#define MEM_SIZE_4M_GTB&t;&t;0x00000007
DECL|macro|MEM_SIZE_6M_GTB
mdefine_line|#define MEM_SIZE_6M_GTB&t;&t;0x00000009
DECL|macro|MEM_SIZE_8M_GTB
mdefine_line|#define MEM_SIZE_8M_GTB&t;&t;0x0000000B
DECL|macro|MEM_BNDRY
mdefine_line|#define MEM_BNDRY               0x00030000
DECL|macro|MEM_BNDRY_0K
mdefine_line|#define MEM_BNDRY_0K            0x00000000
DECL|macro|MEM_BNDRY_256K
mdefine_line|#define MEM_BNDRY_256K          0x00010000
DECL|macro|MEM_BNDRY_512K
mdefine_line|#define MEM_BNDRY_512K          0x00020000
DECL|macro|MEM_BNDRY_1M
mdefine_line|#define MEM_BNDRY_1M            0x00030000
DECL|macro|MEM_BNDRY_EN
mdefine_line|#define MEM_BNDRY_EN            0x00040000
multiline_comment|/* ATI PCI constants */
DECL|macro|PCI_ATI_VENDOR_ID
mdefine_line|#define PCI_ATI_VENDOR_ID&t;0x1002
DECL|macro|PCI_MACH64_GX
mdefine_line|#define PCI_MACH64_GX&t;&t;0x4758
DECL|macro|PCI_MACH64_CX
mdefine_line|#define PCI_MACH64_CX&t;&t;0x4358
DECL|macro|PCI_MACH64_CT
mdefine_line|#define PCI_MACH64_CT&t;&t;0x4354
DECL|macro|PCI_MACH64_ET
mdefine_line|#define PCI_MACH64_ET&t;&t;0x4554
DECL|macro|PCI_MACH64_VT
mdefine_line|#define PCI_MACH64_VT&t;&t;0x5654
DECL|macro|PCI_MACH64_GT
mdefine_line|#define PCI_MACH64_GT&t;&t;0x4754
multiline_comment|/* CONFIG_CHIP_ID register constants */
DECL|macro|CFG_CHIP_TYPE
mdefine_line|#define CFG_CHIP_TYPE&t;&t;0x0000FFFF
DECL|macro|CFG_CHIP_CLASS
mdefine_line|#define CFG_CHIP_CLASS&t;&t;0x00FF0000
DECL|macro|CFG_CHIP_REV
mdefine_line|#define CFG_CHIP_REV&t;&t;0xFF000000
DECL|macro|CFG_CHIP_VERSION
mdefine_line|#define CFG_CHIP_VERSION&t;0x07000000
DECL|macro|CFG_CHIP_FOUNDRY
mdefine_line|#define CFG_CHIP_FOUNDRY&t;0x38000000
DECL|macro|CFG_CHIP_REVISION
mdefine_line|#define CFG_CHIP_REVISION&t;0xC0000000
multiline_comment|/* Chip IDs read from CONFIG_CHIP_ID */
DECL|macro|MACH64_GX_ID
mdefine_line|#define MACH64_GX_ID&t;&t;0xD7
DECL|macro|MACH64_CX_ID
mdefine_line|#define MACH64_CX_ID&t;&t;0x57
DECL|macro|MACH64_CT_ID
mdefine_line|#define MACH64_CT_ID&t;&t;0x4354
DECL|macro|MACH64_ET_ID
mdefine_line|#define MACH64_ET_ID&t;&t;0x4554
DECL|macro|MACH64_VT_ID
mdefine_line|#define MACH64_VT_ID&t;&t;0x5654
DECL|macro|MACH64_GT_ID
mdefine_line|#define MACH64_GT_ID&t;&t;0x4754
multiline_comment|/* Mach64 chip types */
DECL|macro|MACH64_UNKNOWN
mdefine_line|#define MACH64_UNKNOWN&t;&t;0
DECL|macro|MACH64_GX
mdefine_line|#define MACH64_GX&t;&t;1
DECL|macro|MACH64_CX
mdefine_line|#define MACH64_CX&t;&t;2
DECL|macro|MACH64_CT
mdefine_line|#define MACH64_CT&t;&t;3
DECL|macro|MACH64_ET
mdefine_line|#define MACH64_ET&t;&t;4
DECL|macro|MACH64_VT
mdefine_line|#define MACH64_VT&t;&t;5
DECL|macro|MACH64_GT
mdefine_line|#define MACH64_GT&t;&t;6
multiline_comment|/* DST_CNTL register constants */
DECL|macro|DST_X_RIGHT_TO_LEFT
mdefine_line|#define DST_X_RIGHT_TO_LEFT     0
DECL|macro|DST_X_LEFT_TO_RIGHT
mdefine_line|#define DST_X_LEFT_TO_RIGHT     1
DECL|macro|DST_Y_BOTTOM_TO_TOP
mdefine_line|#define DST_Y_BOTTOM_TO_TOP     0
DECL|macro|DST_Y_TOP_TO_BOTTOM
mdefine_line|#define DST_Y_TOP_TO_BOTTOM     2
DECL|macro|DST_X_MAJOR
mdefine_line|#define DST_X_MAJOR             0
DECL|macro|DST_Y_MAJOR
mdefine_line|#define DST_Y_MAJOR             4
DECL|macro|DST_X_TILE
mdefine_line|#define DST_X_TILE              8
DECL|macro|DST_Y_TILE
mdefine_line|#define DST_Y_TILE              0x10
DECL|macro|DST_LAST_PEL
mdefine_line|#define DST_LAST_PEL            0x20
DECL|macro|DST_POLYGON_ENABLE
mdefine_line|#define DST_POLYGON_ENABLE      0x40
DECL|macro|DST_24_ROTATION_ENABLE
mdefine_line|#define DST_24_ROTATION_ENABLE  0x80
multiline_comment|/* SRC_CNTL register constants */
DECL|macro|SRC_PATTERN_ENABLE
mdefine_line|#define SRC_PATTERN_ENABLE      1
DECL|macro|SRC_ROTATION_ENABLE
mdefine_line|#define SRC_ROTATION_ENABLE     2
DECL|macro|SRC_LINEAR_ENABLE
mdefine_line|#define SRC_LINEAR_ENABLE       4
DECL|macro|SRC_BYTE_ALIGN
mdefine_line|#define SRC_BYTE_ALIGN          8
DECL|macro|SRC_LINE_X_RIGHT_TO_LEFT
mdefine_line|#define SRC_LINE_X_RIGHT_TO_LEFT 0
DECL|macro|SRC_LINE_X_LEFT_TO_RIGHT
mdefine_line|#define SRC_LINE_X_LEFT_TO_RIGHT 0x10
multiline_comment|/* HOST_CNTL register constants */
DECL|macro|HOST_BYTE_ALIGN
mdefine_line|#define HOST_BYTE_ALIGN         1
multiline_comment|/* GUI_TRAJ_CNTL register constants */
DECL|macro|PAT_MONO_8x8_ENABLE
mdefine_line|#define PAT_MONO_8x8_ENABLE     0x01000000
DECL|macro|PAT_CLR_4x2_ENABLE
mdefine_line|#define PAT_CLR_4x2_ENABLE      0x02000000
DECL|macro|PAT_CLR_8x1_ENABLE
mdefine_line|#define PAT_CLR_8x1_ENABLE      0x04000000
multiline_comment|/* DP_CHAIN_MASK register constants */
DECL|macro|DP_CHAIN_4BPP
mdefine_line|#define DP_CHAIN_4BPP&t;&t;0x8888
DECL|macro|DP_CHAIN_7BPP
mdefine_line|#define DP_CHAIN_7BPP&t;&t;0xD2D2
DECL|macro|DP_CHAIN_8BPP
mdefine_line|#define DP_CHAIN_8BPP&t;&t;0x8080
DECL|macro|DP_CHAIN_8BPP_RGB
mdefine_line|#define DP_CHAIN_8BPP_RGB&t;0x9292
DECL|macro|DP_CHAIN_15BPP
mdefine_line|#define DP_CHAIN_15BPP&t;&t;0x4210
DECL|macro|DP_CHAIN_16BPP
mdefine_line|#define DP_CHAIN_16BPP&t;&t;0x8410
DECL|macro|DP_CHAIN_24BPP
mdefine_line|#define DP_CHAIN_24BPP&t;&t;0x8080
DECL|macro|DP_CHAIN_32BPP
mdefine_line|#define DP_CHAIN_32BPP&t;&t;0x8080
multiline_comment|/* DP_PIX_WIDTH register constants */
DECL|macro|DST_1BPP
mdefine_line|#define DST_1BPP                0
DECL|macro|DST_4BPP
mdefine_line|#define DST_4BPP                1
DECL|macro|DST_8BPP
mdefine_line|#define DST_8BPP                2
DECL|macro|DST_15BPP
mdefine_line|#define DST_15BPP               3
DECL|macro|DST_16BPP
mdefine_line|#define DST_16BPP               4
DECL|macro|DST_32BPP
mdefine_line|#define DST_32BPP               6
DECL|macro|SRC_1BPP
mdefine_line|#define SRC_1BPP                0
DECL|macro|SRC_4BPP
mdefine_line|#define SRC_4BPP                0x100
DECL|macro|SRC_8BPP
mdefine_line|#define SRC_8BPP                0x200
DECL|macro|SRC_15BPP
mdefine_line|#define SRC_15BPP               0x300
DECL|macro|SRC_16BPP
mdefine_line|#define SRC_16BPP               0x400
DECL|macro|SRC_32BPP
mdefine_line|#define SRC_32BPP               0x600
DECL|macro|HOST_1BPP
mdefine_line|#define HOST_1BPP               0
DECL|macro|HOST_4BPP
mdefine_line|#define HOST_4BPP               0x10000
DECL|macro|HOST_8BPP
mdefine_line|#define HOST_8BPP               0x20000
DECL|macro|HOST_15BPP
mdefine_line|#define HOST_15BPP              0x30000
DECL|macro|HOST_16BPP
mdefine_line|#define HOST_16BPP              0x40000
DECL|macro|HOST_32BPP
mdefine_line|#define HOST_32BPP              0x60000
DECL|macro|BYTE_ORDER_MSB_TO_LSB
mdefine_line|#define BYTE_ORDER_MSB_TO_LSB   0
DECL|macro|BYTE_ORDER_LSB_TO_MSB
mdefine_line|#define BYTE_ORDER_LSB_TO_MSB   0x1000000
multiline_comment|/* DP_MIX register constants */
DECL|macro|BKGD_MIX_NOT_D
mdefine_line|#define BKGD_MIX_NOT_D              0
DECL|macro|BKGD_MIX_ZERO
mdefine_line|#define BKGD_MIX_ZERO               1
DECL|macro|BKGD_MIX_ONE
mdefine_line|#define BKGD_MIX_ONE                2
DECL|macro|BKGD_MIX_D
mdefine_line|#define BKGD_MIX_D                  3
DECL|macro|BKGD_MIX_NOT_S
mdefine_line|#define BKGD_MIX_NOT_S              4
DECL|macro|BKGD_MIX_D_XOR_S
mdefine_line|#define BKGD_MIX_D_XOR_S            5
DECL|macro|BKGD_MIX_NOT_D_XOR_S
mdefine_line|#define BKGD_MIX_NOT_D_XOR_S        6
DECL|macro|BKGD_MIX_S
mdefine_line|#define BKGD_MIX_S                  7
DECL|macro|BKGD_MIX_NOT_D_OR_NOT_S
mdefine_line|#define BKGD_MIX_NOT_D_OR_NOT_S     8
DECL|macro|BKGD_MIX_D_OR_NOT_S
mdefine_line|#define BKGD_MIX_D_OR_NOT_S         9
DECL|macro|BKGD_MIX_NOT_D_OR_S
mdefine_line|#define BKGD_MIX_NOT_D_OR_S         10
DECL|macro|BKGD_MIX_D_OR_S
mdefine_line|#define BKGD_MIX_D_OR_S             11
DECL|macro|BKGD_MIX_D_AND_S
mdefine_line|#define BKGD_MIX_D_AND_S            12
DECL|macro|BKGD_MIX_NOT_D_AND_S
mdefine_line|#define BKGD_MIX_NOT_D_AND_S        13
DECL|macro|BKGD_MIX_D_AND_NOT_S
mdefine_line|#define BKGD_MIX_D_AND_NOT_S        14
DECL|macro|BKGD_MIX_NOT_D_AND_NOT_S
mdefine_line|#define BKGD_MIX_NOT_D_AND_NOT_S    15
DECL|macro|BKGD_MIX_D_PLUS_S_DIV2
mdefine_line|#define BKGD_MIX_D_PLUS_S_DIV2      0x17
DECL|macro|FRGD_MIX_NOT_D
mdefine_line|#define FRGD_MIX_NOT_D              0
DECL|macro|FRGD_MIX_ZERO
mdefine_line|#define FRGD_MIX_ZERO               0x10000
DECL|macro|FRGD_MIX_ONE
mdefine_line|#define FRGD_MIX_ONE                0x20000
DECL|macro|FRGD_MIX_D
mdefine_line|#define FRGD_MIX_D                  0x30000
DECL|macro|FRGD_MIX_NOT_S
mdefine_line|#define FRGD_MIX_NOT_S              0x40000
DECL|macro|FRGD_MIX_D_XOR_S
mdefine_line|#define FRGD_MIX_D_XOR_S            0x50000
DECL|macro|FRGD_MIX_NOT_D_XOR_S
mdefine_line|#define FRGD_MIX_NOT_D_XOR_S        0x60000
DECL|macro|FRGD_MIX_S
mdefine_line|#define FRGD_MIX_S                  0x70000
DECL|macro|FRGD_MIX_NOT_D_OR_NOT_S
mdefine_line|#define FRGD_MIX_NOT_D_OR_NOT_S     0x80000
DECL|macro|FRGD_MIX_D_OR_NOT_S
mdefine_line|#define FRGD_MIX_D_OR_NOT_S         0x90000
DECL|macro|FRGD_MIX_NOT_D_OR_S
mdefine_line|#define FRGD_MIX_NOT_D_OR_S         0xa0000
DECL|macro|FRGD_MIX_D_OR_S
mdefine_line|#define FRGD_MIX_D_OR_S             0xb0000
DECL|macro|FRGD_MIX_D_AND_S
mdefine_line|#define FRGD_MIX_D_AND_S            0xc0000
DECL|macro|FRGD_MIX_NOT_D_AND_S
mdefine_line|#define FRGD_MIX_NOT_D_AND_S        0xd0000
DECL|macro|FRGD_MIX_D_AND_NOT_S
mdefine_line|#define FRGD_MIX_D_AND_NOT_S        0xe0000
DECL|macro|FRGD_MIX_NOT_D_AND_NOT_S
mdefine_line|#define FRGD_MIX_NOT_D_AND_NOT_S    0xf0000
DECL|macro|FRGD_MIX_D_PLUS_S_DIV2
mdefine_line|#define FRGD_MIX_D_PLUS_S_DIV2      0x170000
multiline_comment|/* DP_SRC register constants */
DECL|macro|BKGD_SRC_BKGD_CLR
mdefine_line|#define BKGD_SRC_BKGD_CLR           0
DECL|macro|BKGD_SRC_FRGD_CLR
mdefine_line|#define BKGD_SRC_FRGD_CLR           1
DECL|macro|BKGD_SRC_HOST
mdefine_line|#define BKGD_SRC_HOST               2
DECL|macro|BKGD_SRC_BLIT
mdefine_line|#define BKGD_SRC_BLIT               3
DECL|macro|BKGD_SRC_PATTERN
mdefine_line|#define BKGD_SRC_PATTERN            4
DECL|macro|FRGD_SRC_BKGD_CLR
mdefine_line|#define FRGD_SRC_BKGD_CLR           0
DECL|macro|FRGD_SRC_FRGD_CLR
mdefine_line|#define FRGD_SRC_FRGD_CLR           0x100
DECL|macro|FRGD_SRC_HOST
mdefine_line|#define FRGD_SRC_HOST               0x200
DECL|macro|FRGD_SRC_BLIT
mdefine_line|#define FRGD_SRC_BLIT               0x300
DECL|macro|FRGD_SRC_PATTERN
mdefine_line|#define FRGD_SRC_PATTERN            0x400
DECL|macro|MONO_SRC_ONE
mdefine_line|#define MONO_SRC_ONE                0
DECL|macro|MONO_SRC_PATTERN
mdefine_line|#define MONO_SRC_PATTERN            0x10000
DECL|macro|MONO_SRC_HOST
mdefine_line|#define MONO_SRC_HOST               0x20000
DECL|macro|MONO_SRC_BLIT
mdefine_line|#define MONO_SRC_BLIT               0x30000
multiline_comment|/* CLR_CMP_CNTL register constants */
DECL|macro|COMPARE_FALSE
mdefine_line|#define COMPARE_FALSE               0
DECL|macro|COMPARE_TRUE
mdefine_line|#define COMPARE_TRUE                1
DECL|macro|COMPARE_NOT_EQUAL
mdefine_line|#define COMPARE_NOT_EQUAL           4
DECL|macro|COMPARE_EQUAL
mdefine_line|#define COMPARE_EQUAL               5
DECL|macro|COMPARE_DESTINATION
mdefine_line|#define COMPARE_DESTINATION         0
DECL|macro|COMPARE_SOURCE
mdefine_line|#define COMPARE_SOURCE              0x1000000
multiline_comment|/* FIFO_STAT register constants */
DECL|macro|FIFO_ERR
mdefine_line|#define FIFO_ERR                    0x80000000
multiline_comment|/* CONTEXT_LOAD_CNTL constants */
DECL|macro|CONTEXT_NO_LOAD
mdefine_line|#define CONTEXT_NO_LOAD             0
DECL|macro|CONTEXT_LOAD
mdefine_line|#define CONTEXT_LOAD                0x10000
DECL|macro|CONTEXT_LOAD_AND_DO_FILL
mdefine_line|#define CONTEXT_LOAD_AND_DO_FILL    0x20000
DECL|macro|CONTEXT_LOAD_AND_DO_LINE
mdefine_line|#define CONTEXT_LOAD_AND_DO_LINE    0x30000
DECL|macro|CONTEXT_EXECUTE
mdefine_line|#define CONTEXT_EXECUTE             0
DECL|macro|CONTEXT_CMD_DISABLE
mdefine_line|#define CONTEXT_CMD_DISABLE         0x80000000
multiline_comment|/* GUI_STAT register constants */
DECL|macro|ENGINE_IDLE
mdefine_line|#define ENGINE_IDLE                 0
DECL|macro|ENGINE_BUSY
mdefine_line|#define ENGINE_BUSY                 1
DECL|macro|SCISSOR_LEFT_FLAG
mdefine_line|#define SCISSOR_LEFT_FLAG           0x10
DECL|macro|SCISSOR_RIGHT_FLAG
mdefine_line|#define SCISSOR_RIGHT_FLAG          0x20
DECL|macro|SCISSOR_TOP_FLAG
mdefine_line|#define SCISSOR_TOP_FLAG            0x40
DECL|macro|SCISSOR_BOTTOM_FLAG
mdefine_line|#define SCISSOR_BOTTOM_FLAG         0x80
multiline_comment|/* ATI VGA Extended Regsiters */
DECL|macro|sioATIEXT
mdefine_line|#define sioATIEXT&t;0x1ce
DECL|macro|bioATIEXT
mdefine_line|#define bioATIEXT&t;0x3ce
DECL|macro|ATI2E
mdefine_line|#define ATI2E&t;&t;0xae
DECL|macro|ATI32
mdefine_line|#define ATI32&t;&t;0xb2
DECL|macro|ATI36
mdefine_line|#define ATI36&t;&t;0xb6
multiline_comment|/* VGA Graphics Controller Registers */
DECL|macro|VGAGRA
mdefine_line|#define VGAGRA&t;&t;0x3ce
DECL|macro|GRA06
mdefine_line|#define GRA06&t;&t;0x06
multiline_comment|/* VGA Seququencer Registers */
DECL|macro|VGASEQ
mdefine_line|#define VGASEQ&t;&t;0x3c4
DECL|macro|SEQ02
mdefine_line|#define SEQ02&t;&t;0x02
DECL|macro|SEQ04
mdefine_line|#define SEQ04&t;&t;0x04
DECL|macro|MACH64_MAX_X
mdefine_line|#define MACH64_MAX_X&t;ENGINE_MAX_X
DECL|macro|MACH64_MAX_Y
mdefine_line|#define MACH64_MAX_Y&t;ENGINE_MAX_Y
DECL|macro|INC_X
mdefine_line|#define INC_X           0x0020
DECL|macro|INC_Y
mdefine_line|#define INC_Y           0x0080
DECL|macro|RGB16_555
mdefine_line|#define RGB16_555               0x0000
DECL|macro|RGB16_565
mdefine_line|#define RGB16_565               0x0040
DECL|macro|RGB16_655
mdefine_line|#define RGB16_655               0x0080
DECL|macro|RGB16_664
mdefine_line|#define RGB16_664               0x00c0
DECL|macro|POLY_TEXT_TYPE
mdefine_line|#define POLY_TEXT_TYPE          0x0001
DECL|macro|IMAGE_TEXT_TYPE
mdefine_line|#define IMAGE_TEXT_TYPE         0x0002
DECL|macro|TEXT_TYPE_8_BIT
mdefine_line|#define TEXT_TYPE_8_BIT         0x0004
DECL|macro|TEXT_TYPE_16_BIT
mdefine_line|#define TEXT_TYPE_16_BIT        0x0008
DECL|macro|POLY_TEXT_TYPE_8
mdefine_line|#define POLY_TEXT_TYPE_8        (POLY_TEXT_TYPE | TEXT_TYPE_8_BIT)
DECL|macro|IMAGE_TEXT_TYPE_8
mdefine_line|#define IMAGE_TEXT_TYPE_8       (IMAGE_TEXT_TYPE | TEXT_TYPE_8_BIT)
DECL|macro|POLY_TEXT_TYPE_16
mdefine_line|#define POLY_TEXT_TYPE_16       (POLY_TEXT_TYPE | TEXT_TYPE_16_BIT)
DECL|macro|IMAGE_TEXT_TYPE_16
mdefine_line|#define IMAGE_TEXT_TYPE_16      (IMAGE_TEXT_TYPE | TEXT_TYPE_16_BIT)
DECL|macro|MACH64_NUM_CLOCKS
mdefine_line|#define MACH64_NUM_CLOCKS&t;16
DECL|macro|MACH64_NUM_FREQS
mdefine_line|#define MACH64_NUM_FREQS&t;50
macro_line|#endif /* !(_MACH64_H) */
eof
