multiline_comment|/*&n; *  linux/include/asm-ppc/ide.h&n; *&n; *  Copyright (C) 1994-1996  Linus Torvalds &amp; authors&n; */
multiline_comment|/*&n; *  This file contains the ppc architecture specific IDE code.&n; */
macro_line|#ifndef __ASMPPC_IDE_H
DECL|macro|__ASMPPC_IDE_H
mdefine_line|#define __ASMPPC_IDE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_APUS
macro_line|#include &lt;linux/hdreg.h&gt;
DECL|macro|ide_init_hwif_ports
mdefine_line|#define ide_init_hwif_ports m68k_ide_init_hwif_ports 
macro_line|#include &lt;asm-m68k/ide.h&gt;
DECL|macro|ide_init_hwif_ports
macro_line|#undef ide_init_hwif_ports
DECL|macro|insw
macro_line|#undef insw
r_void
id|ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|ide_insw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_void
id|ide_outsw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns) &t;do {&t;&t;&t;&bslash;&n;&t;if ( _machine != _MACH_Pmac &amp;&amp; _machine != _MACH_apus )&t;&bslash;&n;&t;&t;/* this must be the same as insw in io.h!! */&t;&bslash;&n;&t;&t;_insw((unsigned short *)((port)+_IO_BASE), (buf), (ns)); &bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ide_insw((port), (buf), (ns));&t;&t;&bslash;&n;} while (0)
DECL|macro|outsw
macro_line|#undef outsw
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns) &t;do {&t;&t;&t;&bslash;&n;&t;if ( _machine != _MACH_Pmac &amp;&amp; _machine != _MACH_apus )&t;&bslash;&n;&t;&t;/* this must be the same as outsw in io.h!! */&t;&bslash;&n;&t;&t;_outsw((unsigned short *)((port)+_IO_BASE), (buf), (ns)); &bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ide_outsw((port), (buf), (ns));&t;&t;&bslash;&n;} while (0)
macro_line|#else /* CONFIG_APUS */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* so we can redefine insw/outsw */
macro_line|#ifndef MAX_HWIFS
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;4
macro_line|#endif
DECL|macro|SUPPORT_SLOW_DATA_PORTS
macro_line|#undef&t;SUPPORT_SLOW_DATA_PORTS
DECL|macro|SUPPORT_SLOW_DATA_PORTS
mdefine_line|#define&t;SUPPORT_SLOW_DATA_PORTS&t;0
DECL|macro|SUPPORT_VLB_SYNC
macro_line|#undef&t;SUPPORT_VLB_SYNC
DECL|macro|SUPPORT_VLB_SYNC
mdefine_line|#define SUPPORT_VLB_SYNC&t;0
DECL|macro|ide__sti
mdefine_line|#define ide__sti()&t;__sti()
DECL|typedef|ide_ioreg_t
r_typedef
r_int
r_int
id|ide_ioreg_t
suffix:semicolon
r_void
id|ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|prep_ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|mbx_ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|pmac_ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|chrp_ide_init_hwif_ports
c_func
(paren
id|ide_ioreg_t
op_star
id|p
comma
id|ide_ioreg_t
id|base
comma
r_int
op_star
id|irq
)paren
suffix:semicolon
r_void
id|ide_insw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_void
id|ide_outsw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_int
id|pmac_ide_ports_known
suffix:semicolon
r_extern
id|ide_ioreg_t
id|pmac_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
r_int
id|pmac_ide_irq
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
r_void
id|pmac_ide_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|chrp_ide_ports_known
suffix:semicolon
r_extern
id|ide_ioreg_t
id|chrp_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
r_extern
id|ide_ioreg_t
id|chrp_idedma_regbase
suffix:semicolon
multiline_comment|/* one for both channels */
r_extern
r_int
r_int
id|chrp_ide_irq
suffix:semicolon
r_extern
r_void
id|chrp_ide_probe
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|ide_default_irq
r_static
id|__inline__
r_int
id|ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_if
c_cond
(paren
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
op_logical_or
(paren
id|_machine
op_eq
id|_MACH_mbx
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_chrp
)paren
(brace
r_if
c_cond
(paren
id|chrp_ide_ports_known
op_eq
l_int|0
)paren
id|chrp_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|chrp_ide_irq
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|0x1f0
suffix:colon
r_return
l_int|13
suffix:semicolon
r_case
l_int|0x170
suffix:colon
r_return
l_int|13
suffix:semicolon
r_case
l_int|0x1e8
suffix:colon
r_return
l_int|11
suffix:semicolon
r_case
l_int|0x168
suffix:colon
r_return
l_int|10
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|ide_default_io_base
r_static
id|__inline__
id|ide_ioreg_t
id|ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
(brace
r_return
id|pmac_ide_regbase
(braket
id|index
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_mbx
)paren
r_return
id|index
suffix:semicolon
r_if
c_cond
(paren
id|_machine
op_eq
id|_MACH_chrp
)paren
(brace
r_if
c_cond
(paren
id|chrp_ide_ports_known
op_eq
l_int|0
)paren
id|chrp_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|chrp_ide_regbase
(braket
id|index
)braket
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|index
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
l_int|0x1f0
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
l_int|0x170
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
l_int|0x1e8
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
l_int|0x168
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|ide_check_region
r_static
id|__inline__
r_int
id|ide_check_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_if
c_cond
(paren
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
op_logical_or
(paren
id|_machine
op_eq
id|_MACH_mbx
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|check_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
DECL|function|ide_request_region
r_static
id|__inline__
r_void
id|ide_request_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
op_logical_or
(paren
id|_machine
op_eq
id|_MACH_mbx
)paren
)paren
r_return
suffix:semicolon
id|request_region
c_func
(paren
id|from
comma
id|extent
comma
id|name
)paren
suffix:semicolon
)brace
DECL|function|ide_release_region
r_static
id|__inline__
r_void
id|ide_release_region
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_if
c_cond
(paren
(paren
id|_machine
op_eq
id|_MACH_Pmac
)paren
op_logical_or
(paren
id|_machine
op_eq
id|_MACH_mbx
)paren
)paren
r_return
suffix:semicolon
id|release_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
DECL|macro|ide_fix_driveid
mdefine_line|#define ide_fix_driveid(id)&t;do {&t;&t;&t;&bslash;&n;&t;int nh;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short *p = (unsigned short *) id;&t;&bslash;&n;&t;if (( _machine == _MACH_Pmac ) || (_machine == _MACH_chrp)|| (_machine == _MACH_mbx) )&t;&bslash;&n;&t;&t;for (nh = SECTOR_WORDS * 2; nh != 0; --nh, ++p)&t;&bslash;&n;&t;&t;&t;*p = (*p &lt;&lt; 8) + (*p &gt;&gt; 8);&t;&bslash;&n;} while (0)
DECL|macro|insw
macro_line|#undef insw
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns) &t;do {&t;&t;&t;&bslash;&n;&t;if ( _machine == _MACH_chrp)  {&bslash;&n;&t;&t; ide_insw((port)+_IO_BASE, (buf), (ns));  &bslash;&n;&t;}&bslash;&n;&t;else if ( (_machine == _MACH_Pmac) || (_machine == _MACH_mbx) )&t;&t;&t;&bslash;&n;&t;&t;ide_insw((port), (buf), (ns));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* this must be the same as insw in io.h!! */&t;&bslash;&n;&t;&t;_insw((unsigned short *)((port)+_IO_BASE), (buf), (ns)); &bslash;&n;} while (0)
DECL|macro|outsw
macro_line|#undef outsw
multiline_comment|/*&t;printk(&quot;port: %x buf: %p ns: %d&bslash;n&quot;,port,buf,ns); &bslash; */
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns) &t;do {&t;&t;&t;&bslash;&n;&t;if ( _machine == _MACH_chrp) {&bslash;&n;&t;&t;ide_outsw((port)+_IO_BASE, (buf), (ns)); &bslash;&n;&t;}&bslash;&n;&t;else if ( (_machine == _MACH_Pmac) || (_machine == _MACH_mbx) )&t;&t;&t;&bslash;&n;&t;&t;ide_outsw((port), (buf), (ns));&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;/* this must be the same as outsw in io.h!! */&t;&bslash;&n;&t;&t;_outsw((unsigned short *)((port)+_IO_BASE), (buf), (ns)); &bslash;&n;} while (0)
DECL|macro|inb
macro_line|#undef inb
DECL|macro|inb
mdefine_line|#define inb(port)&t;&bslash;&n;&t;in_8((unsigned char *)((port) + ((_machine==_MACH_Pmac)? 0: _IO_BASE)))
DECL|macro|inb_p
macro_line|#undef inb_p
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;inb(port)
DECL|macro|outb
macro_line|#undef outb
DECL|macro|outb
mdefine_line|#define outb(val, port)&t;&bslash;&n;&t;out_8((unsigned char *)((port) + ((_machine==_MACH_Pmac)? 0: _IO_BASE)), (val))
DECL|macro|outb_p
macro_line|#undef outb_p
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)&t;outb(val, port)
r_typedef
r_union
(brace
r_int
id|all
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all of the bits together */
r_struct
(brace
DECL|member|bit7
r_int
id|bit7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|lba
r_int
id|lba
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using LBA instead of CHS */
DECL|member|bit5
r_int
id|bit5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1 */
DECL|member|unit
r_int
id|unit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive select number, 0/1 */
DECL|member|head
r_int
id|head
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* always zeros here */
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|select_t
)brace
id|select_t
suffix:semicolon
DECL|function|ide_request_irq
r_static
id|__inline__
r_int
id|ide_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|device
comma
r_void
op_star
id|dev_id
)paren
(brace
r_return
id|request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|device
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|ide_free_irq
r_static
id|__inline__
r_void
id|ide_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following are not needed for the non-m68k ports&n; */
DECL|macro|ide_ack_intr
mdefine_line|#define ide_ack_intr(base, irq)&t;&t;(1)
DECL|macro|ide_release_lock
mdefine_line|#define ide_release_lock(lock)&t;&t;do {} while (0)
DECL|macro|ide_get_lock
mdefine_line|#define ide_get_lock(lock, hdlr, data)&t;do {} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* CONFIG_APUS */
macro_line|#endif /* __ASMPPC_IDE_H */
eof
