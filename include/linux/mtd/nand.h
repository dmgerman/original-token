multiline_comment|/* Defines for NAND flash devices           */
multiline_comment|/* (c) 1999 Machine Vision Holdings, Inc.   */
multiline_comment|/* Author: David Woodhouse &lt;dwmw2@mvhi.com&gt; */
multiline_comment|/* $Id: nand.h,v 1.2 1999/08/17 22:57:08 dwmw2 Exp $ */
macro_line|#ifndef __MTD_NAND_H__
DECL|macro|__MTD_NAND_H__
mdefine_line|#define __MTD_NAND_H__
DECL|macro|NAND_CMD_READ0
mdefine_line|#define NAND_CMD_READ0 0
DECL|macro|NAND_CMD_READ1
mdefine_line|#define NAND_CMD_READ1 1
DECL|macro|NAND_CMD_PAGEPROG
mdefine_line|#define NAND_CMD_PAGEPROG 0x10
DECL|macro|NAND_CMD_READOOB
mdefine_line|#define NAND_CMD_READOOB 0x50
DECL|macro|NAND_CMD_ERASE1
mdefine_line|#define NAND_CMD_ERASE1 0x60
DECL|macro|NAND_CMD_STATUS
mdefine_line|#define NAND_CMD_STATUS 0x70
DECL|macro|NAND_CMD_SEQIN
mdefine_line|#define NAND_CMD_SEQIN 0x80
DECL|macro|NAND_CMD_READID
mdefine_line|#define NAND_CMD_READID 0x90
DECL|macro|NAND_CMD_ERASE2
mdefine_line|#define NAND_CMD_ERASE2 0xd0
DECL|macro|NAND_CMD_RESET
mdefine_line|#define NAND_CMD_RESET 0xff
DECL|macro|NAND_MFR_TOSHIBA
mdefine_line|#define NAND_MFR_TOSHIBA 0x98
DECL|macro|NAND_MFR_SAMSUNG
mdefine_line|#define NAND_MFR_SAMSUNG 0xec
macro_line|#endif /* __MTD_NAND_H__ */
eof
