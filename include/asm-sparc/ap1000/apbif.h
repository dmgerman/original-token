multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/*&n;**&t;BIF data registers (system mode)&n;*/
DECL|macro|BIF_DATA
mdefine_line|#define BIF_DATA &t;(BIF+0x0000)&t;/* BIF send and receive data registe&t;*/
DECL|macro|BIF_EDATA
mdefine_line|#define BIF_EDATA  &t;(BIF+0x0004)&t;/* BIF end data register &t;&t;&t;&t;*/
multiline_comment|/*&n;**&t;BIF data registers (user mode) &n;*/
DECL|macro|UBIF_DATA
mdefine_line|#define UBIF_DATA &t;(UBIF+0x0000)&t;/* BIF send and receive data registe&t;*/
DECL|macro|UBIF_EDATA
mdefine_line|#define UBIF_EDATA  (UBIF+0x0004)&t;/* BIF end data register &t;&t;&t;&t;*/
multiline_comment|/*&n;**&t;BIF scatter and gather parameter register (system mode) &n;*/
DECL|macro|BIF_X0SK
mdefine_line|#define BIF_X0SK &t;(BIF+0x0010)&t;/* initial X-skip register &t;&t;&t;*/
DECL|macro|BIF_XSK
mdefine_line|#define BIF_XSK &t;(BIF+0x0014)&t;/* X-skip register &t;&t;&t;&t;&t;*/
DECL|macro|BIF_XSZ
mdefine_line|#define BIF_XSZ &t;(BIF+0x0018)&t;/* X-size register &t;&t;&t;&t;&t;*/
DECL|macro|BIF_Y0SK
mdefine_line|#define BIF_Y0SK &t;(BIF+0x001c)&t;/* initial Y-skip register &t;&t;&t;*/
DECL|macro|BIF_YSK
mdefine_line|#define BIF_YSK &t;(BIF+0x0020)&t;/* Y-skip register &t;&t;&t;&t;&t;*/
DECL|macro|BIF_YSZ
mdefine_line|#define BIF_YSZ &t;(BIF+0x0024)&t;/* Y-size register &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CX0SK
mdefine_line|#define BIF_CX0SK &t;(BIF+0x0028)&t;/* initial counter of X-skip &t;&t;*/
DECL|macro|BIF_CXSK
mdefine_line|#define BIF_CXSK &t;(BIF+0x002c)&t;/* X-skip counter &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CXSZ
mdefine_line|#define BIF_CXSZ &t;(BIF+0x0030)&t;/* X-size counter &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CY0SK
mdefine_line|#define BIF_CY0SK &t;(BIF+0x0034)&t;/* initial counter of Y-skip &t;&t;*/
DECL|macro|BIF_CYSK
mdefine_line|#define BIF_CYSK &t;(BIF+0x0038)&t;/* Y-skip counter &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CYSZ
mdefine_line|#define BIF_CYSZ &t;(BIF+0x003c)&t;/* Y-size counter &t;&t;&t;&t;&t;*/
DECL|macro|BIF_TTL
mdefine_line|#define BIF_TTL &t;(BIF+0x0040)&t;/* number of data transfer register */
DECL|macro|BIF_CTTL
mdefine_line|#define BIF_CTTL &t;(BIF+0x0044)&t;/* number of data transfer counter&t;*/
multiline_comment|/*&n;**&t;BIF scatter and gather parameter register (user mode) &n;*/
DECL|macro|UBIF_X0SK
mdefine_line|#define UBIF_X0SK &t;(UBIF+0x0010)&t;/* initial X-skip register &t;&t;&t;*/
DECL|macro|UBIF_XSK
mdefine_line|#define UBIF_XSK &t;(UBIF+0x0014)&t;/* X-skip register &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_XSZ
mdefine_line|#define UBIF_XSZ &t;(UBIF+0x0018)&t;/* X-size register &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_Y0SK
mdefine_line|#define UBIF_Y0SK &t;(UBIF+0x001c)&t;/* initial Y-skip register &t;&t;&t;*/
DECL|macro|UBIF_YSK
mdefine_line|#define UBIF_YSK &t;(UBIF+0x0020)&t;/* Y-skip register &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_YSZ
mdefine_line|#define UBIF_YSZ &t;(UBIF+0x0024)&t;/* Y-size register &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CX0SK
mdefine_line|#define UBIF_CX0SK &t;(UBIF+0x0028)&t;/* initial counter of X-skip &t;&t;*/
DECL|macro|UBIF_CXSK
mdefine_line|#define UBIF_CXSK &t;(UBIF+0x002c)&t;/* X-skip counter &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CXSZ
mdefine_line|#define UBIF_CXSZ &t;(UBIF+0x0030)&t;/* X-size counter &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CY0SK
mdefine_line|#define UBIF_CY0SK &t;(UBIF+0x0034)&t;/* initial counter of Y-skip &t;&t;*/
DECL|macro|UBIF_CYSK
mdefine_line|#define UBIF_CYSK &t;(UBIF+0x0038)&t;/* Y-skip counter &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CYSZ
mdefine_line|#define UBIF_CYSZ &t;(UBIF+0x003c)&t;/* Y-size counter &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_TTL
mdefine_line|#define UBIF_TTL &t;(UBIF+0x0040)&t;/* number of data transfer register */
DECL|macro|UBIF_CTTL
mdefine_line|#define UBIF_CTTL &t;(UBIF+0x0044)&t;/* number of data transfer counter&t;*/
multiline_comment|/*&n;**&t;BIF control registers (system mode)&n;*/
DECL|macro|BIF_CIDR0
mdefine_line|#define BIF_CIDR0 &t;(BIF+0x0048)&t;/* cell-id register 0 &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CIDR1
mdefine_line|#define BIF_CIDR1 &t;(BIF+0x004c)&t;/* cell-id register 1 (for cell mode) &t;*/
DECL|macro|BIF_CIDR2
mdefine_line|#define BIF_CIDR2 &t;(BIF+0x0050)&t;/* cell-id register 2 &t;&t;&t;&t;&t;*/
DECL|macro|BIF_CIDR3
mdefine_line|#define BIF_CIDR3 &t;(BIF+0x0054)&t;/* cell-id register 3 &t;&t;&t;&t;&t;*/
DECL|macro|BIF_HEADER
mdefine_line|#define BIF_HEADER &t;(BIF+0x0058)&t;/* header register &t;&t;&t;&t;&t;&t;*/
DECL|macro|BIF_INTR
mdefine_line|#define BIF_INTR &t;(BIF+0x006c)&t;/* BIF interrupt control register &t;&t;*/
DECL|macro|BIF_SDCSR
mdefine_line|#define BIF_SDCSR &t;(BIF+0x0070)&t;/* BIF data control set register &t;&t;*/
DECL|macro|BIF_RDCSR
mdefine_line|#define BIF_RDCSR &t;(BIF+0x0074)&t;/* BIF data control reset reregister&t;*/
DECL|macro|BIF_MHOCR
mdefine_line|#define BIF_MHOCR &t;(BIF+0x0078)&t;/* BIF extentional control reregister &t;*/
multiline_comment|/*&n;**&t;BIF control registers (user mode)&n;*/
DECL|macro|UBIF_CIDR0
mdefine_line|#define UBIF_CIDR0 &t;(UBIF+0x0048)&t;/* cell-id register 0 &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CIDR1
mdefine_line|#define UBIF_CIDR1 &t;(UBIF+0x004c)&t;/* cell-id register 1 (for cell mode) &t;*/
DECL|macro|UBIF_CIDR2
mdefine_line|#define UBIF_CIDR2 &t;(UBIF+0x0050)&t;/* cell-id register 2 &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_CIDR3
mdefine_line|#define UBIF_CIDR3 &t;(UBIF+0x0054)&t;/* cell-id register 3 &t;&t;&t;&t;&t;*/
DECL|macro|UBIF_HEADER
mdefine_line|#define UBIF_HEADER (UBIF+0x0058)&t;/* header register &t;&t;&t;&t;&t;&t;*/
DECL|macro|UBIF_INTR
mdefine_line|#define UBIF_INTR &t;(UBIF+0x006c)&t;/* BIF interrupt control register &t;&t;*/
DECL|macro|UBIF_SDCSR
mdefine_line|#define UBIF_SDCSR &t;(UBIF+0x0070)&t;/* BIF data control set register &t;&t;*/
DECL|macro|UBIF_RDCSR
mdefine_line|#define UBIF_RDCSR &t;(UBIF+0x0074)&t;/* BIF data control reset reregister&t;*/
DECL|macro|UBIF_MHOCR
mdefine_line|#define UBIF_MHOCR &t;(UBIF+0x0078)&t;/* BIF extentional control reregister &t;*/
multiline_comment|/*&n;** bit assignment &n;*/
DECL|macro|BIF_HEADER_ID
mdefine_line|#define BIF_HEADER_ID&t; 0xffff0000&t;/* cell-id   &t;&t;*/
DECL|macro|BIF_HEADER_BR
mdefine_line|#define BIF_HEADER_BR&t; 0x00008000&t;/* broad bit &t;&t;*/
DECL|macro|BIF_HEADER_IS
mdefine_line|#define BIF_HEADER_IS&t; 0x00006000&t;/* ID select&t;&t;*/
DECL|macro|BIF_HEADER_IS_00
mdefine_line|#define BIF_HEADER_IS_00 0x00000000 
DECL|macro|BIF_HEADER_IS_01
mdefine_line|#define BIF_HEADER_IS_01 0x00002000 
DECL|macro|BIF_HEADER_IS_10
mdefine_line|#define BIF_HEADER_IS_10 0x00004000 
DECL|macro|BIF_HEADER_IS_11
mdefine_line|#define BIF_HEADER_IS_11 0x00006000 
DECL|macro|BIF_HEADER_IN
mdefine_line|#define BIF_HEADER_IN&t; 0x00001000&t;/* interrupt bit&t;*/
DECL|macro|BIF_HEADER_LS
mdefine_line|#define BIF_HEADER_LS&t; 0x00000800&t;/* line send&t;&t;*/
DECL|macro|BIF_HEADER_SC
mdefine_line|#define BIF_HEADER_SC&t; 0x00000400&t;/* scatter bit &t;&t;*/
DECL|macro|BIF_HEADER_HS
mdefine_line|#define BIF_HEADER_HS&t; 0x00000200&t;/* header strip&t;&t;*/
DECL|macro|BIF_HEADER_RS
mdefine_line|#define BIF_HEADER_RS&t; 0x00000100&t;/* bus release &t;&t;*/
DECL|macro|BIF_HEADER_ID_SHIFT
mdefine_line|#define BIF_HEADER_ID_SHIFT 16
DECL|macro|BIF_INTR_GS
mdefine_line|#define BIF_INTR_GS&t;&t;0x00020000&t;/* grant interrupt select &t;&t;*/
DECL|macro|BIF_INTR_GM
mdefine_line|#define BIF_INTR_GM&t;&t;0x00010000&t;/* grant interrupt mask&t;&t;&t;*/
DECL|macro|BIF_INTR_GI
mdefine_line|#define BIF_INTR_GI&t;&t;0x00008000&t;/* grant interrupt request&t;&t;*/
DECL|macro|BIF_INTR_HS
mdefine_line|#define BIF_INTR_HS&t;&t;0x00004000&t;/* header interrupt select&t;&t;*/
DECL|macro|BIF_INTR_HM
mdefine_line|#define BIF_INTR_HM&t;&t;0x00002000&t;/* header interrupt mask&t;&t;*/
DECL|macro|BIF_INTR_HI
mdefine_line|#define BIF_INTR_HI&t;&t;0x00001000&t;/* header interrupt request&t;&t;*/
DECL|macro|BIF_INTR_SS
mdefine_line|#define BIF_INTR_SS&t;&t;0x00000800&t;/* send interrupt select&t;&t;*/
DECL|macro|BIF_INTR_SM
mdefine_line|#define BIF_INTR_SM&t;&t;0x00000400&t;/* send interrupt mask&t;&t;&t;*/
DECL|macro|BIF_INTR_SI
mdefine_line|#define BIF_INTR_SI&t;&t;0x00000200&t;/* send interrupt request&t;&t;*/
DECL|macro|BIF_INTR_RS
mdefine_line|#define BIF_INTR_RS&t;&t;0x00000100&t;/* receive interrupt select&t;&t;*/
DECL|macro|BIF_INTR_RM
mdefine_line|#define BIF_INTR_RM&t;&t;0x00000080&t;/* receive interrupt mask&t;&t;*/
DECL|macro|BIF_INTR_RI
mdefine_line|#define BIF_INTR_RI&t;&t;0x00000040&t;/* receive interrupt request&t;*/
DECL|macro|BIF_INTR_ES
mdefine_line|#define BIF_INTR_ES&t;&t;0x00000020&t;/* error interrupt select &t;&t;*/
DECL|macro|BIF_INTR_EM
mdefine_line|#define BIF_INTR_EM&t;&t;0x00000010&t;/* error interrupt mask &t;&t;*/
DECL|macro|BIF_INTR_EI
mdefine_line|#define BIF_INTR_EI&t;&t;0x00000008&t;/* error interrupt request &t;&t;*/
DECL|macro|BIF_INTR_AS
mdefine_line|#define BIF_INTR_AS&t;&t;0x00000004&t;/* attention interrupt select &t;*/
DECL|macro|BIF_INTR_AM
mdefine_line|#define BIF_INTR_AM&t;&t;0x00000002&t;/* attention interrupt mask &t;*/
DECL|macro|BIF_INTR_AI
mdefine_line|#define BIF_INTR_AI&t;&t;0x00000001&t;/* attention interrupt request  */
DECL|macro|BIF_SDCSR_ER
mdefine_line|#define BIF_SDCSR_ER    0x7fffc000  /* error  detected by BIF */
DECL|macro|BIF_SDCSR_PE
mdefine_line|#define BIF_SDCSR_PE&t;0x80000000&t;/* detect parity error in sync&t;&t;&t;*/
DECL|macro|BIF_SDCSR_SP
mdefine_line|#define BIF_SDCSR_SP&t;0x40000000&t;/* parity error in sync&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_LP
mdefine_line|#define BIF_SDCSR_LP&t;0x20000000&t;/* L-bus parity error&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_LR
mdefine_line|#define BIF_SDCSR_LR&t;0x10000000&t;/* */
DECL|macro|BIF_SDCSR_LW
mdefine_line|#define BIF_SDCSR_LW&t;0x08000000&t;/* */
DECL|macro|BIF_SDCSR_AL
mdefine_line|#define BIF_SDCSR_AL&t;0x04000000&t;/* specify end bit except of end data&t;*/
DECL|macro|BIF_SDCSR_SS
mdefine_line|#define BIF_SDCSR_SS&t;0x02000000&t;/* request bit but masked by slow sync&t;*/
DECL|macro|BIF_SDCSR_SC
mdefine_line|#define BIF_SDCSR_SC&t;0x01000000&t;/* clear bit but masked by slow sync&t;*/
DECL|macro|BIF_SDCSR_SY
mdefine_line|#define BIF_SDCSR_SY&t;0x00800000&t;/* set bit but masked by slow status&t;*/
DECL|macro|BIF_SDCSR_FS
mdefine_line|#define BIF_SDCSR_FS&t;0x00400000&t;/* request bit but masked by fast sync&t;*/
DECL|macro|BIF_SDCSR_FC
mdefine_line|#define BIF_SDCSR_FC&t;0x00200000&t;/* clear bit but masked by fast sync&t;*/
DECL|macro|BIF_SDCSR_FY
mdefine_line|#define BIF_SDCSR_FY&t;0x00100000&t;/* set bit but masked by fast status&t;*/
DECL|macro|BIF_SDCSR_CP
mdefine_line|#define BIF_SDCSR_CP&t;0x00080000&t;/* parity error in commnad bus&t;&t;&t;*/
DECL|macro|BIF_SDCSR_FP
mdefine_line|#define BIF_SDCSR_FP&t;0x00040000&t;/* execute scatter or gather but FN=0&t;*/
DECL|macro|BIF_SDCSR_PS
mdefine_line|#define BIF_SDCSR_PS&t;0x00020000&t;/* header receive error &t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_RA
mdefine_line|#define BIF_SDCSR_RA&t;0x00010000&t;/* change scatter,gather parameter&t;&t;*/
DECL|macro|BIF_SDCSR_PA
mdefine_line|#define BIF_SDCSR_PA&t;0x00008000&t;/* check if send or receive error&t;&t;*/
DECL|macro|BIF_SDCSR_DL
mdefine_line|#define BIF_SDCSR_DL&t;0x00004000&t;/* lost data&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_BB
mdefine_line|#define BIF_SDCSR_BB&t;0x00002000&t;/* check if some BIF use command bus&t;*/
DECL|macro|BIF_SDCSR_BG
mdefine_line|#define BIF_SDCSR_BG&t;0x00001000&t;/* check if command bus got&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_BR
mdefine_line|#define BIF_SDCSR_BR&t;0x00000800&t;/* request command bus&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_CN
mdefine_line|#define BIF_SDCSR_CN&t;0x00000400&t;/* release BIF from command bus&t;&t;&t;*/
DECL|macro|BIF_SDCSR_FN
mdefine_line|#define BIF_SDCSR_FN&t;0x00000200&t;/* scatter gather enable&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_EB
mdefine_line|#define BIF_SDCSR_EB&t;0x00000100&t;/* send data that have end bit&t;&t;&t;*/
DECL|macro|BIF_SDCSR_TB
mdefine_line|#define BIF_SDCSR_TB&t;0x000000E0&t;/* data in send FIFO&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_TB4
mdefine_line|#define BIF_SDCSR_TB4&t;0x00000080
DECL|macro|BIF_SDCSR_TB2
mdefine_line|#define BIF_SDCSR_TB2&t;0x00000040
DECL|macro|BIF_SDCSR_TB1
mdefine_line|#define BIF_SDCSR_TB1&t;0x00000020
DECL|macro|BIF_SDCSR_RB
mdefine_line|#define BIF_SDCSR_RB&t;0x0000001c&t;/* data in receive FIFO&t;&t;&t;&t;&t;*/
DECL|macro|BIF_SDCSR_RB4
mdefine_line|#define BIF_SDCSR_RB4&t;0x00000010
DECL|macro|BIF_SDCSR_RB2
mdefine_line|#define BIF_SDCSR_RB2&t;0x00000008&t;
DECL|macro|BIF_SDCSR_RB1
mdefine_line|#define BIF_SDCSR_RB1&t;0x00000004&t;
DECL|macro|BIF_SDCSR_DE
mdefine_line|#define BIF_SDCSR_DE&t;0x00000002&t;/* DMA interface enable bitr&t;&t;&t;*/
DECL|macro|BIF_SDCSR_DR
mdefine_line|#define BIF_SDCSR_DR&t;0x00000001&t;/* data transfer direction&t;&t;&t;&t;*/
DECL|macro|BIF_RDCSR_ER
mdefine_line|#define BIF_RDCSR_ER    BIF_SDCSR_ER    /* error  detected by BIF */
DECL|macro|BIF_RDCSR_PE
mdefine_line|#define BIF_RDCSR_PE&t;BIF_SDCSR_PE&t;/* detect parity error in sync&t;&t;*/
DECL|macro|BIF_RDCSR_SP
mdefine_line|#define BIF_RDCSR_SP&t;BIF_SDCSR_SP&t;/* parity error in sync&t;  */
DECL|macro|BIF_RDCSR_LP
mdefine_line|#define BIF_RDCSR_LP&t;BIF_SDCSR_LP&t;/* L-bus parity error&t;  */
DECL|macro|BIF_RDCSR_LR
mdefine_line|#define BIF_RDCSR_LR&t;BIF_SDCSR_LR&t;/* */
DECL|macro|BIF_RDCSR_LW
mdefine_line|#define BIF_RDCSR_LW&t;BIF_SDCSR_LW&t;/* */
DECL|macro|BIF_RDCSR_AL
mdefine_line|#define BIF_RDCSR_AL&t;BIF_SDCSR_AL&t;/* specify end bit except of end data */
DECL|macro|BIF_RDCSR_SS
mdefine_line|#define BIF_RDCSR_SS&t;BIF_SDCSR_SS&t;/* request bit but masked by slow sync&t;*/
DECL|macro|BIF_RDCSR_SC
mdefine_line|#define BIF_RDCSR_SC&t;BIF_SDCSR_SC&t;/* clear bit but masked by slow sync  */
DECL|macro|BIF_RDCSR_SY
mdefine_line|#define BIF_RDCSR_SY&t;BIF_SDCSR_SY&t;/* set bit but masked by slow status  */
DECL|macro|BIF_RDCSR_FS
mdefine_line|#define BIF_RDCSR_FS&t;BIF_SDCSR_FS&t;/* request bit but masked by fast sync*/
DECL|macro|BIF_RDCSR_FC
mdefine_line|#define BIF_RDCSR_FC&t;BIF_SDCSR_FC&t;/* clear bit but masked by fast sync  */
DECL|macro|BIF_RDCSR_FY
mdefine_line|#define BIF_RDCSR_FY&t;BIF_SDCSR_FY&t;/* set bit but masked by fast status  */
DECL|macro|BIF_RDCSR_CP
mdefine_line|#define BIF_RDCSR_CP&t;BIF_SDCSR_CP&t;/* parity error in commnad bus        */
DECL|macro|BIF_RDCSR_FP
mdefine_line|#define BIF_RDCSR_FP&t;BIF_SDCSR_FP&t;/* execute scatter or gather but FN=0 */
DECL|macro|BIF_RDCSR_PS
mdefine_line|#define BIF_RDCSR_PS&t;BIF_SDCSR_PS&t;/* header receive error &t;&t;&t;*/
DECL|macro|BIF_RDCSR_RA
mdefine_line|#define BIF_RDCSR_RA&t;BIF_SDCSR_RA&t;/* change scatter,gather parameter&t;&t;*/
DECL|macro|BIF_RDCSR_DL
mdefine_line|#define BIF_RDCSR_DL&t;BIF_SDCSR_DL&t;/* lost data&t;&t;&t;&t;&t;*/
DECL|macro|BIF_RDCSR_PA
mdefine_line|#define BIF_RDCSR_PA&t;BIF_SDCSR_PA&t;/* check if send or receive error&t;  */
DECL|macro|BIF_RDCSR_BB
mdefine_line|#define BIF_RDCSR_BB&t;BIF_SDCSR_BB&t;/* check if some BIF use command bus  */
DECL|macro|BIF_RDCSR_BG
mdefine_line|#define BIF_RDCSR_BG&t;BIF_SDCSR_BG&t;/* check if command bus got&t;&t;*/
DECL|macro|BIF_RDCSR_BR
mdefine_line|#define BIF_RDCSR_BR&t;BIF_SDCSR_BR&t;/* request command bus&t;&t;&t;*/
DECL|macro|BIF_RDCSR_CN
mdefine_line|#define BIF_RDCSR_CN&t;BIF_SDCSR_CN&t;/* release BIF from command bus&t;*/
DECL|macro|BIF_RDCSR_EB
mdefine_line|#define BIF_RDCSR_EB&t;BIF_SDCSR_EB&t;/* send data that have end bit&t;*/
DECL|macro|BIF_RDCSR_TB
mdefine_line|#define BIF_RDCSR_TB&t;BIF_SDCSR_TB&t;/* data in send FIFO&t;&t;&t;*/
DECL|macro|BIF_RDCSR_RB
mdefine_line|#define BIF_RDCSR_RB&t;BIF_SDCSR_RB&t;/* data in receive FIFO&t;&t;&t;*/
DECL|macro|BIF_RDCSR_DE
mdefine_line|#define BIF_RDCSR_DE&t;BIF_SDCSR_DE&t;/* DMA interface enable bitr&t;*/
DECL|macro|BIF_RDCSR_DR
mdefine_line|#define BIF_RDCSR_DR&t;BIF_SDCSR_DR&t;/* data transfer direction&t;&t;*/
DECL|macro|BIF_RDCSR_FN
mdefine_line|#define BIF_RDCSR_FN&t;BIF_SDCSR_FN&t;/* scatter gather enable&t;&t;*/
DECL|macro|BIF_MHOCR_RS
mdefine_line|#define BIF_MHOCR_RS&t;0x00000800&t;&t;/* bif reset&t;&t;&t;&t;&t;&t;*/
DECL|macro|BIF_MHOCR_RC
mdefine_line|#define BIF_MHOCR_RC&t;0x00000400&t;&t;/* commnad bus circuit reset&t;&t;*/
DECL|macro|BIF_MHOCR_RI
mdefine_line|#define BIF_MHOCR_RI&t;0x00000200&t;&t;/* remove input buffer data&t;&t;&t;*/
DECL|macro|BIF_MHOCR_RO
mdefine_line|#define BIF_MHOCR_RO&t;0x00000100&t;&t;/* remove output buffer data&t;&t;*/
DECL|macro|BIF_MHOCR_BA
mdefine_line|#define BIF_MHOCR_BA&t;0x00000008&t;&t;/* command bus arbitlater reset&t;&t;*/
DECL|macro|BIF_MHOCR_MD
mdefine_line|#define BIF_MHOCR_MD&t;0x00000006&t;&t;/* command bus mode&t;&t;&t;&t;&t;*/
DECL|macro|BIF_MHOCR_AT
mdefine_line|#define BIF_MHOCR_AT&t;0x00000001&t;&t;/* command bus attention signal&t;&t;*/
DECL|macro|BIF_MHOCR_MD_NORMAL
mdefine_line|#define BIF_MHOCR_MD_NORMAL&t;0x00000006&t;/* command bus mode [normal]&t;&t;*/
DECL|macro|BIF_MHOCR_MD_BUSWGR
mdefine_line|#define BIF_MHOCR_MD_BUSWGR&t;0x00000004&t;/* command bus mode [bus gather]&t;*/
DECL|macro|BIF_MHOCR_MD_SETCID
mdefine_line|#define BIF_MHOCR_MD_SETCID&t;0x00000002&t;/* command bus mode [set cid]&t;&t;*/
eof
