multiline_comment|/*&n; *  ISA Plug &amp; Play support&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef LINUX_ISAPNP_H
DECL|macro|LINUX_ISAPNP_H
mdefine_line|#define LINUX_ISAPNP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/*&n; *  Configuration registers (TODO: change by specification)&n; */
DECL|macro|ISAPNP_CFG_ACTIVATE
mdefine_line|#define ISAPNP_CFG_ACTIVATE&t;&t;0x30&t;/* byte */
DECL|macro|ISAPNP_CFG_MEM
mdefine_line|#define ISAPNP_CFG_MEM&t;&t;&t;0x40&t;/* 4 * dword */
DECL|macro|ISAPNP_CFG_PORT
mdefine_line|#define ISAPNP_CFG_PORT&t;&t;&t;0x60&t;/* 8 * word */
DECL|macro|ISAPNP_CFG_IRQ
mdefine_line|#define ISAPNP_CFG_IRQ&t;&t;&t;0x70&t;/* 2 * word */
DECL|macro|ISAPNP_CFG_DMA
mdefine_line|#define ISAPNP_CFG_DMA&t;&t;&t;0x74&t;/* 2 * byte */
multiline_comment|/*&n; *&n; */
DECL|macro|ISAPNP_VENDOR
mdefine_line|#define ISAPNP_VENDOR(a,b,c)&t;(((((a)-&squot;A&squot;+1)&amp;0x3f)&lt;&lt;2)|&bslash;&n;&t;&t;&t;&t;((((b)-&squot;A&squot;+1)&amp;0x18)&gt;&gt;3)|((((b)-&squot;A&squot;+1)&amp;7)&lt;&lt;13)|&bslash;&n;&t;&t;&t;&t;((((c)-&squot;A&squot;+1)&amp;0x1f)&lt;&lt;8))
DECL|macro|ISAPNP_DEVICE
mdefine_line|#define ISAPNP_DEVICE(x)&t;((((x)&amp;0xf000)&gt;&gt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x0f00)&gt;&gt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x00f0)&lt;&lt;8)|&bslash;&n;&t;&t;&t;&t; (((x)&amp;0x000f)&lt;&lt;8))
DECL|macro|ISAPNP_FUNCTION
mdefine_line|#define ISAPNP_FUNCTION(x)&t;ISAPNP_DEVICE(x)
multiline_comment|/*&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|ISAPNP_PORT_FLAG_16BITADDR
mdefine_line|#define ISAPNP_PORT_FLAG_16BITADDR&t;(1&lt;&lt;0)
DECL|macro|ISAPNP_PORT_FLAG_FIXED
mdefine_line|#define ISAPNP_PORT_FLAG_FIXED&t;&t;(1&lt;&lt;1)
DECL|struct|isapnp_port
r_struct
id|isapnp_port
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* min base number */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* max base number */
DECL|member|align
r_int
r_char
id|align
suffix:semicolon
multiline_comment|/* align boundary */
DECL|member|size
r_int
r_char
id|size
suffix:semicolon
multiline_comment|/* size of range */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* port flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|res
r_struct
id|isapnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|isapnp_port
op_star
id|next
suffix:semicolon
multiline_comment|/* next port */
)brace
suffix:semicolon
DECL|struct|isapnp_irq
r_struct
id|isapnp_irq
(brace
DECL|member|map
r_int
r_int
id|map
suffix:semicolon
multiline_comment|/* bitmaks for IRQ lines */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* IRQ flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|res
r_struct
id|isapnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|isapnp_irq
op_star
id|next
suffix:semicolon
multiline_comment|/* next IRQ */
)brace
suffix:semicolon
DECL|struct|isapnp_dma
r_struct
id|isapnp_dma
(brace
DECL|member|map
r_int
r_char
id|map
suffix:semicolon
multiline_comment|/* bitmask for DMA channels */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* DMA flags */
DECL|member|res
r_struct
id|isapnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|isapnp_dma
op_star
id|next
suffix:semicolon
multiline_comment|/* next port */
)brace
suffix:semicolon
DECL|struct|isapnp_mem
r_struct
id|isapnp_mem
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* min base number */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* max base number */
DECL|member|align
r_int
r_int
id|align
suffix:semicolon
multiline_comment|/* align boundary */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of range */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* memory flags */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* pad */
DECL|member|res
r_struct
id|isapnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|isapnp_mem
op_star
id|next
suffix:semicolon
multiline_comment|/* next memory resource */
)brace
suffix:semicolon
DECL|struct|isapnp_mem32
r_struct
id|isapnp_mem32
(brace
multiline_comment|/* TODO */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|res
r_struct
id|isapnp_resources
op_star
id|res
suffix:semicolon
multiline_comment|/* parent */
DECL|member|next
r_struct
id|isapnp_mem32
op_star
id|next
suffix:semicolon
multiline_comment|/* next 32-bit memory resource */
)brace
suffix:semicolon
DECL|struct|isapnp_fixup
r_struct
id|isapnp_fixup
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
multiline_comment|/* matching vendor */
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* matching device */
DECL|member|quirk_function
r_void
(paren
op_star
id|quirk_function
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* fixup function */
)brace
suffix:semicolon
DECL|macro|ISAPNP_RES_PRIORITY_PREFERRED
mdefine_line|#define ISAPNP_RES_PRIORITY_PREFERRED&t;0
DECL|macro|ISAPNP_RES_PRIORITY_ACCEPTABLE
mdefine_line|#define ISAPNP_RES_PRIORITY_ACCEPTABLE&t;1
DECL|macro|ISAPNP_RES_PRIORITY_FUNCTIONAL
mdefine_line|#define ISAPNP_RES_PRIORITY_FUNCTIONAL&t;2
DECL|macro|ISAPNP_RES_PRIORITY_INVALID
mdefine_line|#define ISAPNP_RES_PRIORITY_INVALID&t;65535
DECL|struct|isapnp_resources
r_struct
id|isapnp_resources
(brace
DECL|member|priority
r_int
r_int
id|priority
suffix:semicolon
multiline_comment|/* priority */
DECL|member|dependent
r_int
r_int
id|dependent
suffix:semicolon
multiline_comment|/* dependent resources */
DECL|member|port
r_struct
id|isapnp_port
op_star
id|port
suffix:semicolon
multiline_comment|/* first port */
DECL|member|irq
r_struct
id|isapnp_irq
op_star
id|irq
suffix:semicolon
multiline_comment|/* first IRQ */
DECL|member|dma
r_struct
id|isapnp_dma
op_star
id|dma
suffix:semicolon
multiline_comment|/* first DMA */
DECL|member|mem
r_struct
id|isapnp_mem
op_star
id|mem
suffix:semicolon
multiline_comment|/* first memory resource */
DECL|member|mem32
r_struct
id|isapnp_mem32
op_star
id|mem32
suffix:semicolon
multiline_comment|/* first 32-bit memory */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* parent */
DECL|member|alt
r_struct
id|isapnp_resources
op_star
id|alt
suffix:semicolon
multiline_comment|/* alternative resource (aka dependent resources) */
DECL|member|next
r_struct
id|isapnp_resources
op_star
id|next
suffix:semicolon
multiline_comment|/* next resource */
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_ISAPNP) || defined(CONFIG_ISAPNP_MODULE)
multiline_comment|/* lowlevel configuration */
r_int
id|isapnp_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isapnp_cfg_begin
c_func
(paren
r_int
id|csn
comma
r_int
id|device
)paren
suffix:semicolon
r_int
id|isapnp_cfg_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_char
id|isapnp_read_byte
c_func
(paren
r_int
r_char
id|idx
)paren
suffix:semicolon
r_int
r_int
id|isapnp_read_word
c_func
(paren
r_int
r_char
id|idx
)paren
suffix:semicolon
r_int
r_int
id|isapnp_read_dword
c_func
(paren
r_int
r_char
id|idx
)paren
suffix:semicolon
r_void
id|isapnp_write_byte
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_void
id|isapnp_write_word
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_void
id|isapnp_write_dword
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_void
id|isapnp_wake
c_func
(paren
r_int
r_char
id|csn
)paren
suffix:semicolon
r_void
id|isapnp_device
c_func
(paren
r_int
r_char
id|device
)paren
suffix:semicolon
r_void
id|isapnp_activate
c_func
(paren
r_int
r_char
id|device
)paren
suffix:semicolon
r_void
id|isapnp_deactivate
c_func
(paren
r_int
r_char
id|device
)paren
suffix:semicolon
r_void
id|isapnp_fixup_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
op_star
id|isapnp_alloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_int
id|isapnp_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|isapnp_proc_done
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* manager */
r_struct
id|pci_bus
op_star
id|isapnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pci_bus
op_star
id|from
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|isapnp_find_dev
c_func
(paren
r_struct
id|pci_bus
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_struct
id|pci_dev
op_star
id|from
)paren
suffix:semicolon
multiline_comment|/* misc */
r_void
id|isapnp_resource_change
c_func
(paren
r_struct
id|resource
op_star
id|resource
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* init/main.c */
r_int
id|isapnp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|isapnp_cards
suffix:semicolon
r_extern
r_struct
id|list_head
id|isapnp_devices
suffix:semicolon
DECL|macro|isapnp_for_each_card
mdefine_line|#define isapnp_for_each_card(card) &bslash;&n;&t;for(card = pci_bus_b(isapnp_cards.next); card != pci_bus_b(&amp;isapnp_cards); card = pci_bus_b(card-&gt;node.next))
DECL|macro|isapnp_for_each_dev
mdefine_line|#define isapnp_for_each_dev(dev) &bslash;&n;&t;for(dev = pci_dev_g(isapnp_devices.next); dev != pci_dev_g(&amp;isapnp_devices); dev = pci_dev_g(dev-&gt;global_list.next))
macro_line|#else /* !CONFIG_ISAPNP */
multiline_comment|/* lowlevel configuration */
DECL|function|isapnp_present
r_extern
r_inline
r_int
id|isapnp_present
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|isapnp_cfg_begin
r_extern
r_inline
r_int
id|isapnp_cfg_begin
c_func
(paren
r_int
id|csn
comma
r_int
id|device
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|isapnp_cfg_end
r_extern
r_inline
r_int
id|isapnp_cfg_end
c_func
(paren
r_void
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|isapnp_read_byte
r_extern
r_inline
r_int
r_char
id|isapnp_read_byte
c_func
(paren
r_int
r_char
id|idx
)paren
(brace
r_return
l_int|0xff
suffix:semicolon
)brace
DECL|function|isapnp_read_word
r_extern
r_inline
r_int
r_int
id|isapnp_read_word
c_func
(paren
r_int
r_char
id|idx
)paren
(brace
r_return
l_int|0xffff
suffix:semicolon
)brace
DECL|function|isapnp_read_dword
r_extern
r_inline
r_int
r_int
id|isapnp_read_dword
c_func
(paren
r_int
r_char
id|idx
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
DECL|function|isapnp_write_byte
r_extern
r_inline
r_void
id|isapnp_write_byte
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_char
id|val
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_write_word
r_extern
r_inline
r_void
id|isapnp_write_word
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_int
id|val
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_write_dword
r_extern
r_inline
r_void
id|isapnp_write_dword
c_func
(paren
r_int
r_char
id|idx
comma
r_int
r_int
id|val
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_wake
r_extern
r_inline
r_void
id|isapnp_wake
c_func
(paren
r_int
r_char
id|csn
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_device
r_extern
r_inline
r_void
id|isapnp_device
c_func
(paren
r_int
r_char
id|device
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_activate
r_extern
r_inline
r_void
id|isapnp_activate
c_func
(paren
r_int
r_char
id|device
)paren
(brace
suffix:semicolon
)brace
DECL|function|isapnp_deactivate
r_extern
r_inline
r_void
id|isapnp_deactivate
c_func
(paren
r_int
r_char
id|device
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* manager */
DECL|function|isapnp_find_card
r_extern
r_inline
r_struct
id|pci_bus
op_star
id|isapnp_find_card
c_func
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
comma
r_struct
id|pci_bus
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|isapnp_find_dev
r_extern
r_inline
r_struct
id|pci_dev
op_star
id|isapnp_find_dev
c_func
(paren
r_struct
id|pci_bus
op_star
id|card
comma
r_int
r_int
id|vendor
comma
r_int
r_int
id|function
comma
r_struct
id|pci_dev
op_star
id|from
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|isapnp_resource_change
r_extern
r_inline
r_void
id|isapnp_resource_change
c_func
(paren
r_struct
id|resource
op_star
id|resource
comma
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ISAPNP */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_ISAPNP_H */
eof
