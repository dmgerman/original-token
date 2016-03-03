macro_line|#ifndef __INCE1PC_H__
DECL|macro|__INCE1PC_H__
mdefine_line|#define __INCE1PC_H__
multiline_comment|/****************************************************************************&r;&n;&r;&n;    FILE:       ince1pc.h&r;&n;&r;&n;    AUTHOR:     M.Steinkopf&r;&n;&r;&n;    PURPOSE:    common definitions for both sides of the bus:&r;&n;&t;&t;- conventions both spoolers must know&r;&n;&t;&t;- channel numbers agreed upon&r;&n;&r;&n;*****************************************************************************/
multiline_comment|/*  basic scalar definitions have same meanning,&r;&n; *  but their declaration location depends on environment&r;&n; */
multiline_comment|/*--------------------------------------channel numbers---------------------*/
DECL|macro|CHAN_SYSTEM
mdefine_line|#define CHAN_SYSTEM     0x0001      /* system channel (spooler to spooler) */
DECL|macro|CHAN_ERRLOG
mdefine_line|#define CHAN_ERRLOG     0x0005      /* error logger */
DECL|macro|CHAN_CAPI
mdefine_line|#define CHAN_CAPI       0x0064      /* CAPI interface */
DECL|macro|CHAN_NDIS_DATA
mdefine_line|#define CHAN_NDIS_DATA  0x1001      /* NDIS data transfer */
multiline_comment|/*--------------------------------------POF ready msg-----------------------*/
multiline_comment|/* NOTE: after booting POF sends system ready message to PC: */
DECL|macro|RDY_MAGIC
mdefine_line|#define RDY_MAGIC       0x52535953UL    /* &squot;SYSR&squot; reversed */
DECL|macro|RDY_MAGIC_SIZE
mdefine_line|#define RDY_MAGIC_SIZE  4               /* size in bytes */
DECL|macro|MAX_N_TOK_BYTES
mdefine_line|#define MAX_N_TOK_BYTES 255
DECL|macro|MIN_RDY_MSG_SIZE
mdefine_line|#define MIN_RDY_MSG_SIZE    RDY_MAGIC_SIZE
DECL|macro|MAX_RDY_MSG_SIZE
mdefine_line|#define MAX_RDY_MSG_SIZE    (RDY_MAGIC_SIZE+MAX_N_TOK_BYTES)
DECL|macro|SYSR_TOK_END
mdefine_line|#define SYSR_TOK_END            0
DECL|macro|SYSR_TOK_B_CHAN
mdefine_line|#define SYSR_TOK_B_CHAN         1   /* nr. of B-Channels;   DataLen=1; def: 2 */
DECL|macro|SYSR_TOK_FAX_CHAN
mdefine_line|#define SYSR_TOK_FAX_CHAN       2   /* nr. of FAX Channels; DataLen=1; def: 0 */
DECL|macro|SYSR_TOK_MAC_ADDR
mdefine_line|#define SYSR_TOK_MAC_ADDR       3   /* MAC-Address; DataLen=6; def: auto */
DECL|macro|SYSR_TOK_ESC
mdefine_line|#define SYSR_TOK_ESC            255 /* undefined data size yet */
multiline_comment|/* default values, if not corrected by token: */
DECL|macro|SYSR_TOK_B_CHAN_DEF
mdefine_line|#define SYSR_TOK_B_CHAN_DEF     2   /* assume 2 B-Channels */
DECL|macro|SYSR_TOK_FAX_CHAN_DEF
mdefine_line|#define SYSR_TOK_FAX_CHAN_DEF   1   /* assume 1 FAX Channel */
multiline_comment|/*  syntax of new SYSR token stream:&r;&n; *  channel: CHAN_SYSTEM&r;&n; *  msgsize: MIN_RDY_MSG_SIZE &lt;= x &lt;= MAX_RDY_MSG_SIZE&r;&n; *           RDY_MAGIC_SIZE   &lt;= x &lt;= (RDY_MAGIC_SIZE+MAX_N_TOK_BYTES)&r;&n; *  msg    : 0 1 2 3 {4 5 6 ..}&r;&n; *           S Y S R  MAX_N_TOK_BYTES bytes of TokenStream&r;&n; *&r;&n; *  TokenStream     :=   empty&r;&n; *                     | {NonEndTokenChunk} EndToken RotlCRC&r;&n; *  NonEndTokenChunk:= NonEndTokenId DataLen [Data]&r;&n; *  NonEndTokenId   := 0x01 .. 0xFE                 1 BYTE&r;&n; *  DataLen         := 0x00 .. 0xFF                 1 BYTE&r;&n; *  Data            := DataLen bytes&r;&n; *  EndToken        := 0x00&r;&n; *  RotlCRC         := special 1 byte CRC over all NonEndTokenChunk bytes&r;&n; *                     s. RotlCRC algorithm&r;&n; *&r;&n; *  RotlCRC algorithm:&r;&n; *      ucSum= 0                        1 uchar&r;&n; *      for all NonEndTokenChunk bytes:&r;&n; *          ROTL(ucSum,1)               rotate left by 1&r;&n; *          ucSum += Char;              add current byte with swap around&r;&n; *      RotlCRC= ~ucSum;                invert all bits for result&r;&n; *&r;&n; *  note:&r;&n; *  - for 16-bit FIFO add padding 0 byte to achieve even token data bytes!&r;&n; */
multiline_comment|/*--------------------------------------error logger------------------------*/
multiline_comment|/* note: pof needs final 0 ! */
DECL|macro|ERRLOG_CMD_REQ
mdefine_line|#define ERRLOG_CMD_REQ          &quot;ERRLOG ON&quot;
DECL|macro|ERRLOG_CMD_REQ_SIZE
mdefine_line|#define ERRLOG_CMD_REQ_SIZE     10              /* with final 0 byte ! */
DECL|macro|ERRLOG_CMD_STOP
mdefine_line|#define ERRLOG_CMD_STOP         &quot;ERRLOG OFF&quot;
DECL|macro|ERRLOG_CMD_STOP_SIZE
mdefine_line|#define ERRLOG_CMD_STOP_SIZE    11              /* with final 0 byte ! */
DECL|macro|ERRLOG_ENTRY_SIZE
mdefine_line|#define ERRLOG_ENTRY_SIZE       64      /* sizeof(tErrLogEntry) */
multiline_comment|/* remaining text size = 55 */
DECL|macro|ERRLOG_TEXT_SIZE
mdefine_line|#define ERRLOG_TEXT_SIZE    (ERRLOG_ENTRY_SIZE-2*4-1)
DECL|struct|ErrLogEntry_tag
r_typedef
r_struct
id|ErrLogEntry_tag
(brace
DECL|member|ulErrType
multiline_comment|/*00 */
id|ulong
id|ulErrType
suffix:semicolon
DECL|member|ulErrSubtype
multiline_comment|/*04 */
id|ulong
id|ulErrSubtype
suffix:semicolon
DECL|member|ucTextSize
multiline_comment|/*08 */
id|uchar
id|ucTextSize
suffix:semicolon
DECL|member|ucText
multiline_comment|/*09 */
id|uchar
id|ucText
(braket
id|ERRLOG_TEXT_SIZE
)braket
suffix:semicolon
multiline_comment|/* ASCIIZ of len ucTextSize-1 */
multiline_comment|/*40 */
DECL|typedef|tErrLogEntry
)brace
id|tErrLogEntry
suffix:semicolon
macro_line|#if defined(__TURBOC__)
macro_line|#if sizeof(tErrLogEntry) != ERRLOG_ENTRY_SIZE
macro_line|#error size of tErrLogEntry != ERRLOG_ENTRY_SIZE
macro_line|#endif&t;&t;&t;&t;/* &r; */
macro_line|#endif&t;&t;&t;&t;/* &r; */
multiline_comment|/*--------------------------------------DPRAM boot spooler------------------*/
multiline_comment|/*  this is the struture used between pc and&r;&n;&t;&t;&t;&t; *  hyperstone to exchange boot data&r;&n;&t;&t;&t;&t; */
mdefine_line|#define DPRAM_SPOOLER_DATA_SIZE 0x20
DECL|member|Len
r_typedef
r_struct
id|DpramBootSpooler_tag
(brace
DECL|member|RdPtr
multiline_comment|/*00 */
id|uchar
id|Len
suffix:semicolon
DECL|member|WrPtr
multiline_comment|/*01 */
r_volatile
id|uchar
id|RdPtr
suffix:semicolon
DECL|member|Data
multiline_comment|/*02 */
id|uchar
id|WrPtr
suffix:semicolon
multiline_comment|/*03 */
id|uchar
id|Data
(braket
id|DPRAM_SPOOLER_DATA_SIZE
)braket
suffix:semicolon
multiline_comment|/*23 */
)brace
id|tDpramBootSpooler
suffix:semicolon
mdefine_line|#define DPRAM_SPOOLER_MIN_SIZE  5       /* Len+RdPtr+Wrptr+2*data */
mdefine_line|#define DPRAM_SPOOLER_DEF_SIZE  0x23    /* current default size   */
DECL|macro|SIZE_RSV_SOFT_UART
multiline_comment|/*--------------------------------------HYCARD/ERGO DPRAM SoftUart----------*/
multiline_comment|/* at DPRAM offset 0x1C00: */
mdefine_line|#define SIZE_RSV_SOFT_UART  0x1B0   /* 432 bytes reserved for SoftUart */
macro_line|#endif&t;/* __INCE1PC_H__ */
eof
