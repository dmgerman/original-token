macro_line|#ifndef _M68K_MVME16xHW_H_
DECL|macro|_M68K_MVME16xHW_H_
mdefine_line|#define _M68K_MVME16xHW_H_
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* Board ID data structure - pointer to this retrieved from Bug by head.S */
multiline_comment|/* Note, bytes 12 and 13 are board no in BCD (0162,0166,0167,0177,etc) */
r_extern
r_int
id|mvme_bdid_ptr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|bdid
r_char
id|bdid
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rev
DECL|member|mth
DECL|member|day
DECL|member|yr
id|u_char
id|rev
comma
id|mth
comma
id|day
comma
id|yr
suffix:semicolon
DECL|member|size
DECL|member|reserved
id|u_short
id|size
comma
id|reserved
suffix:semicolon
DECL|member|brdno
id|u_short
id|brdno
suffix:semicolon
DECL|member|brdsuffix
r_char
id|brdsuffix
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|options
id|u_long
id|options
suffix:semicolon
DECL|member|clun
DECL|member|dlun
DECL|member|ctype
DECL|member|dnum
id|u_short
id|clun
comma
id|dlun
comma
id|ctype
comma
id|dnum
suffix:semicolon
DECL|member|option2
id|u_long
id|option2
suffix:semicolon
DECL|typedef|t_bdid
DECL|typedef|p_bdid
)brace
id|t_bdid
comma
op_star
id|p_bdid
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ack_icr
id|u_char
id|ack_icr
comma
DECL|member|flt_icr
id|flt_icr
comma
DECL|member|sel_icr
id|sel_icr
comma
DECL|member|pe_icr
id|pe_icr
comma
DECL|member|bsy_icr
id|bsy_icr
comma
DECL|member|spare1
id|spare1
comma
DECL|member|isr
id|isr
comma
DECL|member|cr
id|cr
comma
DECL|member|spare2
id|spare2
comma
DECL|member|spare3
id|spare3
comma
DECL|member|spare4
id|spare4
comma
DECL|member|data
id|data
suffix:semicolon
DECL|typedef|lpr_ctrl
)brace
id|lpr_ctrl
suffix:semicolon
DECL|macro|LPR_REGS
mdefine_line|#define LPR_REGS&t;((volatile lpr_ctrl *)0xfff42030)
DECL|macro|I596_BASE
mdefine_line|#define I596_BASE&t;0xfff46000
DECL|macro|SCC_A_ADDR
mdefine_line|#define SCC_A_ADDR&t;0xfff45005
DECL|macro|SCC_B_ADDR
mdefine_line|#define SCC_B_ADDR&t;0xfff45001
DECL|macro|IRQ_MVME162_TYPE_PRIO
mdefine_line|#define IRQ_MVME162_TYPE_PRIO&t;0
DECL|macro|IRQ_MVME167_PRN
mdefine_line|#define IRQ_MVME167_PRN&t;&t;0x54
DECL|macro|IRQ_MVME16x_I596
mdefine_line|#define IRQ_MVME16x_I596&t;0x57
DECL|macro|IRQ_MVME16x_SCSI
mdefine_line|#define IRQ_MVME16x_SCSI&t;0x55
DECL|macro|IRQ_MVME16x_FLY
mdefine_line|#define IRQ_MVME16x_FLY&t;&t;0x7f
DECL|macro|IRQ_MVME167_SER_ERR
mdefine_line|#define IRQ_MVME167_SER_ERR&t;0x5c
DECL|macro|IRQ_MVME167_SER_MODEM
mdefine_line|#define IRQ_MVME167_SER_MODEM&t;0x5d
DECL|macro|IRQ_MVME167_SER_TX
mdefine_line|#define IRQ_MVME167_SER_TX&t;0x5e
DECL|macro|IRQ_MVME167_SER_RX
mdefine_line|#define IRQ_MVME167_SER_RX&t;0x5f
DECL|macro|IRQ_MVME16x_TIMER
mdefine_line|#define IRQ_MVME16x_TIMER&t;0x59
multiline_comment|/* SCC interrupts, for MVME162 */
DECL|macro|IRQ_MVME162_SCC_BASE
mdefine_line|#define IRQ_MVME162_SCC_BASE&t;&t;0x40
DECL|macro|IRQ_MVME162_SCCB_TX
mdefine_line|#define IRQ_MVME162_SCCB_TX&t;&t;0x40
DECL|macro|IRQ_MVME162_SCCB_STAT
mdefine_line|#define IRQ_MVME162_SCCB_STAT&t;&t;0x42
DECL|macro|IRQ_MVME162_SCCB_RX
mdefine_line|#define IRQ_MVME162_SCCB_RX&t;&t;0x44
DECL|macro|IRQ_MVME162_SCCB_SPCOND
mdefine_line|#define IRQ_MVME162_SCCB_SPCOND&t;&t;0x46
DECL|macro|IRQ_MVME162_SCCA_TX
mdefine_line|#define IRQ_MVME162_SCCA_TX&t;&t;0x48
DECL|macro|IRQ_MVME162_SCCA_STAT
mdefine_line|#define IRQ_MVME162_SCCA_STAT&t;&t;0x4a
DECL|macro|IRQ_MVME162_SCCA_RX
mdefine_line|#define IRQ_MVME162_SCCA_RX&t;&t;0x4c
DECL|macro|IRQ_MVME162_SCCA_SPCOND
mdefine_line|#define IRQ_MVME162_SCCA_SPCOND&t;&t;0x4e
multiline_comment|/* MVME162 version register */
DECL|macro|MVME162_VERSION_REG
mdefine_line|#define MVME162_VERSION_REG&t;0xfff4202e
r_extern
r_int
r_int
id|mvme16x_config
suffix:semicolon
multiline_comment|/* Lower 8 bits must match the revision register in the MC2 chip */
DECL|macro|MVME16x_CONFIG_SPEED_32
mdefine_line|#define MVME16x_CONFIG_SPEED_32&t;&t;0x0001
DECL|macro|MVME16x_CONFIG_NO_VMECHIP2
mdefine_line|#define MVME16x_CONFIG_NO_VMECHIP2&t;0x0002
DECL|macro|MVME16x_CONFIG_NO_SCSICHIP
mdefine_line|#define MVME16x_CONFIG_NO_SCSICHIP&t;0x0004
DECL|macro|MVME16x_CONFIG_NO_ETHERNET
mdefine_line|#define MVME16x_CONFIG_NO_ETHERNET&t;0x0008
DECL|macro|MVME16x_CONFIG_GOT_FPU
mdefine_line|#define MVME16x_CONFIG_GOT_FPU&t;&t;0x0010
DECL|macro|MVME16x_CONFIG_GOT_LP
mdefine_line|#define MVME16x_CONFIG_GOT_LP&t;&t;0x0100
DECL|macro|MVME16x_CONFIG_GOT_CD2401
mdefine_line|#define MVME16x_CONFIG_GOT_CD2401&t;0x0200
DECL|macro|MVME16x_CONFIG_GOT_SCCA
mdefine_line|#define MVME16x_CONFIG_GOT_SCCA&t;&t;0x0400
DECL|macro|MVME16x_CONFIG_GOT_SCCB
mdefine_line|#define MVME16x_CONFIG_GOT_SCCB&t;&t;0x0800
multiline_comment|/* Specials for the ethernet driver */
DECL|macro|CA
mdefine_line|#define CA()&t;&t;(((struct i596_reg *)dev-&gt;base_addr)-&gt;ca = 1)
DECL|macro|MPU_PORT
mdefine_line|#define MPU_PORT(c,x)&t;&bslash;&n;  ((struct i596_reg *)(dev-&gt;base_addr))-&gt;porthi = ((c) | (u32)(x)) &amp; 0xffff; &bslash;&n;  ((struct i596_reg *)(dev-&gt;base_addr))-&gt;portlo = ((c) | (u32)(x)) &gt;&gt; 16
DECL|macro|SCP_SYSBUS
mdefine_line|#define SCP_SYSBUS&t;0x00000054
DECL|macro|WSWAPrfd
mdefine_line|#define WSWAPrfd(x)&t;((struct i596_rfd *) (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPrbd
mdefine_line|#define WSWAPrbd(x)&t;((struct i596_rbd *) (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPiscp
mdefine_line|#define WSWAPiscp(x)&t;((struct i596_iscp *)(((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPscb
mdefine_line|#define WSWAPscb(x)&t;((struct i596_scb *) (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPcmd
mdefine_line|#define WSWAPcmd(x)&t;((struct i596_cmd *) (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPtbd
mdefine_line|#define WSWAPtbd(x)&t;((struct i596_tbd *) (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
DECL|macro|WSWAPchar
mdefine_line|#define WSWAPchar(x)&t;((char *)            (((u32)(x)&lt;&lt;16) | ((((u32)(x)))&gt;&gt;16)))
multiline_comment|/*&n; * The MPU_PORT command allows direct access to the 82596. With PORT access&n; * the following commands are available (p5-18). The 32-bit port command&n; * must be word-swapped with the most significant word written first.&n; */
DECL|macro|PORT_RESET
mdefine_line|#define PORT_RESET&t;0x00&t;/* reset 82596 */
DECL|macro|PORT_SELFTEST
mdefine_line|#define PORT_SELFTEST&t;0x01&t;/* selftest */
DECL|macro|PORT_ALTSCP
mdefine_line|#define PORT_ALTSCP&t;0x02&t;/* alternate SCB address */
DECL|macro|PORT_ALTDUMP
mdefine_line|#define PORT_ALTDUMP&t;0x03&t;/* Alternate DUMP address */
DECL|macro|ISCP_BUSY
mdefine_line|#define ISCP_BUSY&t;0x00010000
macro_line|#endif /* _M68K_MVME16xHW_H_ */
eof
