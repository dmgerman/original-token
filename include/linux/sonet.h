multiline_comment|/* sonet.h - SONET/SHD physical layer control */
multiline_comment|/* Written 1995 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef LINUX_SONET_H
DECL|macro|LINUX_SONET_H
mdefine_line|#define LINUX_SONET_H
DECL|struct|sonet_stats
r_struct
id|sonet_stats
(brace
DECL|member|section_bip
r_int
id|section_bip
suffix:semicolon
multiline_comment|/* section parity errors (B1) */
DECL|member|line_bip
r_int
id|line_bip
suffix:semicolon
multiline_comment|/* line parity errors (B2) */
DECL|member|path_bip
r_int
id|path_bip
suffix:semicolon
multiline_comment|/* path parity errors (B3) */
DECL|member|line_febe
r_int
id|line_febe
suffix:semicolon
multiline_comment|/* line parity errors at remote */
DECL|member|path_febe
r_int
id|path_febe
suffix:semicolon
multiline_comment|/* path parity errors at remote */
DECL|member|corr_hcs
r_int
id|corr_hcs
suffix:semicolon
multiline_comment|/* correctable header errors */
DECL|member|uncorr_hcs
r_int
id|uncorr_hcs
suffix:semicolon
multiline_comment|/* uncorrectable header errors */
DECL|member|tx_cells
r_int
id|tx_cells
suffix:semicolon
multiline_comment|/* cells sent */
DECL|member|rx_cells
r_int
id|rx_cells
suffix:semicolon
multiline_comment|/* cells received */
)brace
suffix:semicolon
DECL|macro|SONET_GETSTAT
mdefine_line|#define SONET_GETSTAT&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP,struct sonet_stats)
multiline_comment|/* get statistics */
DECL|macro|SONET_GETSTATZ
mdefine_line|#define SONET_GETSTATZ&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP+1,struct sonet_stats)
multiline_comment|/* ... and zero counters */
DECL|macro|SONET_SETDIAG
mdefine_line|#define SONET_SETDIAG&t;_IOWR(&squot;a&squot;,ATMIOC_PHYTYP+2,int)
multiline_comment|/* set error insertion */
DECL|macro|SONET_CLRDIAG
mdefine_line|#define SONET_CLRDIAG&t;_IOWR(&squot;a&squot;,ATMIOC_PHYTYP+3,int)
multiline_comment|/* clear error insertion */
DECL|macro|SONET_GETDIAG
mdefine_line|#define SONET_GETDIAG&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP+4,int)
multiline_comment|/* query error insertion */
DECL|macro|SONET_SETFRAMING
mdefine_line|#define SONET_SETFRAMING _IO(&squot;a&squot;,ATMIOC_PHYTYP+5)
multiline_comment|/* set framing mode (SONET/SDH) */
DECL|macro|SONET_GETFRAMING
mdefine_line|#define SONET_GETFRAMING _IOR(&squot;a&squot;,ATMIOC_PHYTYP+6,int)
multiline_comment|/* get framing mode */
DECL|macro|SONET_GETFRSENSE
mdefine_line|#define SONET_GETFRSENSE _IOR(&squot;a&squot;,ATMIOC_PHYTYP+7, &bslash;&n;  unsigned char[SONET_FRSENSE_SIZE])&t;/* get framing sense information */
DECL|macro|SONET_INS_SBIP
mdefine_line|#define SONET_INS_SBIP&t;  1&t;&t;/* section BIP */
DECL|macro|SONET_INS_LBIP
mdefine_line|#define SONET_INS_LBIP&t;  2&t;&t;/* line BIP */
DECL|macro|SONET_INS_PBIP
mdefine_line|#define SONET_INS_PBIP&t;  4&t;&t;/* path BIP */
DECL|macro|SONET_INS_FRAME
mdefine_line|#define SONET_INS_FRAME&t;  8&t;&t;/* out of frame */
DECL|macro|SONET_INS_LOS
mdefine_line|#define SONET_INS_LOS&t; 16&t;&t;/* set line to zero */
DECL|macro|SONET_INS_LAIS
mdefine_line|#define SONET_INS_LAIS&t; 32&t;&t;/* line alarm indication signal */
DECL|macro|SONET_INS_PAIS
mdefine_line|#define SONET_INS_PAIS&t; 64&t;&t;/* path alarm indication signal */
DECL|macro|SONET_INS_HCS
mdefine_line|#define SONET_INS_HCS&t;128&t;&t;/* insert HCS error */
DECL|macro|SONET_FRAME_SONET
mdefine_line|#define SONET_FRAME_SONET 0&t;&t;/* SONET STS-3 framing */
DECL|macro|SONET_FRAME_SDH
mdefine_line|#define SONET_FRAME_SDH   1&t;&t;/* SDH STM-1 framing */
DECL|macro|SONET_FRSENSE_SIZE
mdefine_line|#define SONET_FRSENSE_SIZE 6&t;&t;/* C1[3],H1[3] (0xff for unknown) */
macro_line|#endif
eof
