multiline_comment|/*&n; * ddi.h&t;Define the structure for linking in I/O drivers into the&n; *&t;&t;operating system kernel.  This method is currently only&n; *&t;&t;used by NET layer drivers, but it will be expanded into&n; *&t;&t;a link methos for ALL kernel-resident device drivers.&n; *&n; * Version:&t;@(#)ddi.h&t;1.0.2&t;04/22/93&n; *&n; * Author:&t;Fred N. van Kempen, &lt;waltje@uwalt.nl.mugnet.org&gt;&n; */
macro_line|#ifndef _LINUX_DDI_H
DECL|macro|_LINUX_DDI_H
mdefine_line|#define _LINUX_DDI_H
multiline_comment|/* DDI control block flags. */
DECL|macro|DDI_FREADY
mdefine_line|#define DDI_FREADY&t;0x10000000&t;/* device is initialized&t;*/
DECL|macro|DDI_FPRESENT
mdefine_line|#define DDI_FPRESENT&t;0x20000000&t;/* device hardware is present&t;*/
DECL|macro|DDI_FBLKDEV
mdefine_line|#define DDI_FBLKDEV&t;0x00000001&t;/* device has a BLK spec. file&t;*/
DECL|macro|DDI_FCHRDEV
mdefine_line|#define DDI_FCHRDEV&t;0x00000002&t;/* device has a CHR spec. file&t;*/
multiline_comment|/* Various constants. */
DECL|macro|DDI_MAXNAME
mdefine_line|#define DDI_MAXNAME&t;16&t;&t;/* length of a DDI ID string&t;*/
multiline_comment|/* This structure is used to set up a DDI driver. */
DECL|struct|ddconf
r_struct
id|ddconf
(brace
DECL|member|ioaddr
r_int
id|ioaddr
suffix:semicolon
multiline_comment|/* main I/O (port) address&t;*/
DECL|member|ioaux
r_int
id|ioaux
suffix:semicolon
multiline_comment|/* auxiliary I/O (HD, AST)&t;*/
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ channel&t;&t;&t;*/
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA channel to use&t;&t;*/
DECL|member|memsize
r_int
r_int
id|memsize
suffix:semicolon
multiline_comment|/* size of onboard memory&t;*/
DECL|member|memaddr
r_int
r_int
id|memaddr
suffix:semicolon
multiline_comment|/* base address of memory&t;*/
)brace
suffix:semicolon
multiline_comment|/* The DDI device control block. */
DECL|struct|ddi_device
r_struct
id|ddi_device
(brace
DECL|member|title
r_char
op_star
id|title
suffix:semicolon
multiline_comment|/* title of the driver&t;&t;*/
DECL|member|name
r_char
id|name
(braket
id|DDI_MAXNAME
)braket
suffix:semicolon
multiline_comment|/* unit name of the I/O driver&t;*/
DECL|member|unit
r_int
r_int
id|unit
suffix:semicolon
multiline_comment|/* unit number of this driver&t;*/
DECL|member|nunits
r_int
r_int
id|nunits
suffix:semicolon
multiline_comment|/* number of units in driver&t;*/
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|ddi_device
op_star
)paren
suffix:semicolon
multiline_comment|/* initialization func&t;&t;*/
DECL|member|handler
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* command handler&t;&t;*/
DECL|member|major
r_int
r_int
id|major
suffix:semicolon
multiline_comment|/* driver major dev number&t;*/
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
multiline_comment|/* driver minor dev number&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags&t;&t;*/
DECL|member|config
r_struct
id|ddconf
id|config
suffix:semicolon
multiline_comment|/* driver HW setup&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* This structure is used to set up networking protocols. */
DECL|struct|ddi_proto
r_struct
id|ddi_proto
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* protocol name&t;&t;*/
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|ddi_proto
op_star
)paren
suffix:semicolon
multiline_comment|/* initialization func&t;*/
)brace
suffix:semicolon
multiline_comment|/* This structure is used to link a STREAMS interface. */
DECL|struct|iflink
r_struct
id|iflink
(brace
DECL|member|id
r_char
id|id
(braket
id|DDI_MAXNAME
)braket
suffix:semicolon
multiline_comment|/* DDI ID string&t;&t;*/
DECL|member|stream
r_char
id|stream
(braket
id|DDI_MAXNAME
)braket
suffix:semicolon
multiline_comment|/* STREAMS interface name&t;*/
DECL|member|family
r_int
id|family
suffix:semicolon
multiline_comment|/* address (protocol) family&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* any flags needed (unused)&t;*/
)brace
suffix:semicolon
multiline_comment|/* DDI control requests. */
DECL|macro|DDIOCSDBG
mdefine_line|#define DDIOCSDBG&t;0x9000&t;&t;/* set DDI debug level&t;&t;*/
DECL|macro|DDIOCGNAME
mdefine_line|#define DDIOCGNAME&t;0x9001&t;&t;/* get DDI ID name&t;&t;*/
DECL|macro|DDIOCGCONF
mdefine_line|#define DDIOCGCONF&t;0x9002&t;&t;/* get DDI HW config&t;&t;*/
DECL|macro|DDIOCSCONF
mdefine_line|#define DDIOCSCONF&t;0x9003&t;&t;/* set DDI HW config&t;&t;*/
multiline_comment|/* DDI global functions. */
r_extern
r_void
id|ddi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|ddi_device
op_star
id|ddi_map
c_func
(paren
r_const
r_char
op_star
id|id
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_DDI_H */
eof
