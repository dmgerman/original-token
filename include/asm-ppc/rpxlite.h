multiline_comment|/*&n; * A collection of structures, addresses, and values associated with&n; * the RPCG RPX-Lite board.  Copied from the MBX stuff.&n; *&n; * Copyright (c) 1998 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __MACH_RPX_DEFS
DECL|macro|__MACH_RPX_DEFS
mdefine_line|#define __MACH_RPX_DEFS
multiline_comment|/* A Board Information structure that is given to a program when&n; * prom starts it up.&n; */
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* Memory start address */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* Memory (end) size in bytes */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in Hz */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
multiline_comment|/* Memory map is configured by the PROM startup.&n; * We just map a few things we need.  The CSR is actually 4 byte-wide&n; * registers that can be accessed as 8-, 16-, or 32-bit values.&n; */
DECL|macro|RPX_CSR_ADDR
mdefine_line|#define RPX_CSR_ADDR&t;&t;((uint)0xfa400000)
DECL|macro|RPX_CSR_SIZE
mdefine_line|#define RPX_CSR_SIZE&t;&t;((uint)(4 * 1024))
DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;&t;((uint)0xfa200000)
DECL|macro|IMAP_SIZE
mdefine_line|#define IMAP_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|HIOX_CSR_ADDR
mdefine_line|#define HIOX_CSR_ADDR&t;&t;((uint)0xfac00000)
DECL|macro|HIOX_CSR_SIZE
mdefine_line|#define HIOX_CSR_SIZE&t;&t;((uint)(4 * 1024))
DECL|macro|PCMCIA_MEM_ADDR
mdefine_line|#define PCMCIA_MEM_ADDR&t;&t;((uint)0x04000000)
DECL|macro|PCMCIA_MEM_SIZE
mdefine_line|#define PCMCIA_MEM_SIZE&t;&t;((uint)(64 * 1024))
DECL|macro|PCMCIA_IO_ADDR
mdefine_line|#define PCMCIA_IO_ADDR&t;&t;((uint)0x04400000)
DECL|macro|PCMCIA_IO_SIZE
mdefine_line|#define PCMCIA_IO_SIZE&t;&t;((uint)(4 * 1024))
multiline_comment|/* Things of interest in the CSR.&n;*/
DECL|macro|BCSR0_ETHEN
mdefine_line|#define BCSR0_ETHEN&t;&t;((uint)0x80000000)
DECL|macro|BCSR0_ETHLPBK
mdefine_line|#define BCSR0_ETHLPBK&t;&t;((uint)0x40000000)
DECL|macro|BCSR0_COLTESTDIS
mdefine_line|#define BCSR0_COLTESTDIS&t;((uint)0x20000000)
DECL|macro|BCSR0_FULLDPLXDIS
mdefine_line|#define BCSR0_FULLDPLXDIS&t;((uint)0x10000000)
DECL|macro|BCSR0_LEDOFF
mdefine_line|#define BCSR0_LEDOFF&t;&t;((uint)0x08000000)
DECL|macro|BCSR0_USBDISABLE
mdefine_line|#define BCSR0_USBDISABLE&t;((uint)0x04000000)
DECL|macro|BCSR0_USBHISPEED
mdefine_line|#define BCSR0_USBHISPEED&t;((uint)0x02000000)
DECL|macro|BCSR0_USBPWREN
mdefine_line|#define BCSR0_USBPWREN&t;&t;((uint)0x01000000)
DECL|macro|BCSR0_PCMCIAVOLT
mdefine_line|#define BCSR0_PCMCIAVOLT&t;((uint)0x000f0000)
DECL|macro|BCSR0_PCMCIA3VOLT
mdefine_line|#define BCSR0_PCMCIA3VOLT&t;((uint)0x000a0000)
DECL|macro|BCSR0_PCMCIA5VOLT
mdefine_line|#define BCSR0_PCMCIA5VOLT&t;((uint)0x00060000)
multiline_comment|/* HIO Expansion card.&n;*/
DECL|macro|HIOX_CSR_ENAUDIO
mdefine_line|#define HIOX_CSR_ENAUDIO&t;((uint)0x00000200)
DECL|macro|HIOX_CSR_RSTAUDIO
mdefine_line|#define HIOX_CSR_RSTAUDIO&t;((uint)0x00000100)&t;/* 0 == reset */
multiline_comment|/* We don&squot;t use the 8259.&n;*/
DECL|macro|NR_8259_INTS
mdefine_line|#define NR_8259_INTS&t;0
multiline_comment|/* Machine type&n;*/
DECL|macro|_MACH_8xx
mdefine_line|#define _MACH_8xx (_MACH_rpxlite)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
