multiline_comment|/* idprom.h: Macros and defines for idprom routines&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_IDPROM_H
DECL|macro|_SPARC_IDPROM_H
mdefine_line|#define _SPARC_IDPROM_H
r_extern
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
multiline_comment|/* Offset into the EEPROM where the id PROM is located on the 4c */
DECL|macro|IDPROM_OFFSET
mdefine_line|#define IDPROM_OFFSET  0x7d8
multiline_comment|/* On sun4m; physical. */
multiline_comment|/* MicroSPARC(-II) does not decode 31rd bit, but it works. */
DECL|macro|IDPROM_OFFSET_M
mdefine_line|#define IDPROM_OFFSET_M  0xfd8
DECL|struct|idp_struct
r_struct
id|idp_struct
(brace
DECL|member|id_f_id
r_int
r_char
id|id_f_id
suffix:semicolon
multiline_comment|/* format identifier */
DECL|member|id_machtype
r_int
r_char
id|id_machtype
suffix:semicolon
multiline_comment|/* Machine type */
DECL|member|id_eaddr
r_int
r_char
id|id_eaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* hardware ethernet address */
DECL|member|id_domf
r_int
id|id_domf
suffix:semicolon
multiline_comment|/* Date when this machine was manufactured */
DECL|member|id_sernum
r_int
r_int
id|id_sernum
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Unique serial number */
DECL|member|id_cksum
r_int
r_char
id|id_cksum
suffix:semicolon
multiline_comment|/* XXX */
DECL|member|dummy
r_int
r_char
id|dummy
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* XXX */
)brace
suffix:semicolon
r_extern
r_struct
id|idp_struct
op_star
id|idprom
suffix:semicolon
DECL|macro|IDPROM_SIZE
mdefine_line|#define IDPROM_SIZE  (sizeof(struct idp_struct))
macro_line|#endif /* !(_SPARC_IDPROM_H) */
eof