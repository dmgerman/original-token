multiline_comment|/* $Id: isdn_cards.c,v 1.10 1999/07/20 06:41:28 calle Exp $&n;&n; * Linux ISDN subsystem, initialization for non-modularized drivers.&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@isdn4linux.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: isdn_cards.c,v $&n; * Revision 1.10  1999/07/20 06:41:28  calle&n; * Bugfix: After the redesign of the AVM B1 driver, the driver didn&squot;t even&n; *         compile, if not selected as modules.&n; *&n; * Revision 1.9  1999/04/12 12:33:11  fritz&n; * Changes from 2.0 tree.&n; *&n; * Revision 1.8  1999/03/29 11:13:23  armin&n; * Added eicon driver init.&n; *&n; * Revision 1.7  1998/02/20 17:24:28  fritz&n; * Added ACT2000 init.&n; *&n; * Revision 1.6  1997/04/23 18:56:03  fritz&n; * Old Teles driver removed, Changed doc and scripts accordingly.&n; *&n; * Revision 1.5  1997/03/30 17:10:36  calle&n; * added support for AVM-B1-PCI card.&n; *&n; * Revision 1.4  1997/03/04 21:59:44  calle&n; * Added AVM-B1-CAPI2.0 driver&n; *&n; * Revision 1.3  1997/02/03 23:31:14  fritz&n; * Reformatted according CodingStyle&n; *&n; * Revision 1.2  1996/10/13 19:52:17  keil&n; * HiSax support&n; *&n; * Revision 1.1  1996/04/20 16:04:36  fritz&n; * Initial revision&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ISDN_DRV_ICN
r_extern
r_void
id|icn_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_HISAX
r_extern
r_void
id|HiSax_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_PCBIT
r_extern
r_void
id|pcbit_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_EICON
r_extern
r_void
id|eicon_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1
r_extern
r_void
id|kcapi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|capi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|capidrv_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|act2000_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|isdn_cards_init
id|isdn_cards_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if CONFIG_ISDN_DRV_ICN
id|icn_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_HISAX
id|HiSax_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_PCBIT
id|pcbit_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_AVMB1
id|kcapi_init
c_func
(paren
)paren
suffix:semicolon
id|capi_init
c_func
(paren
)paren
suffix:semicolon
id|capidrv_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_ACT2000
id|act2000_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_EICON
id|eicon_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
