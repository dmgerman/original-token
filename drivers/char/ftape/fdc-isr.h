macro_line|#ifndef _FDC_ISR_H
DECL|macro|_FDC_ISR_H
mdefine_line|#define _FDC_ISR_H
multiline_comment|/*&n; * Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/fdc-isr.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.8 $&n; $Date: 1995/04/22 07:30:15 $&n; $State: Beta $&n; *&n; *      This file contains the low level functions&n; *      that communicate with the floppy disk controller,&n; *      for the QIC-40/80 floppy-tape driver for Linux.&n; */
multiline_comment|/*&n; *      fdc-isr.c defined public variables&n; */
r_extern
r_volatile
r_int
id|expected_stray_interrupts
suffix:semicolon
multiline_comment|/* masks stray interrupts */
r_extern
r_volatile
r_int
id|seek_completed
suffix:semicolon
multiline_comment|/* flag set by isr */
r_extern
r_volatile
r_int
id|interrupt_seen
suffix:semicolon
multiline_comment|/* flag set by isr */
r_extern
r_volatile
r_int
id|expect_stray_interrupt
suffix:semicolon
multiline_comment|/*&n; *      fdc-io.c defined public functions&n; */
r_extern
r_void
id|fdc_isr
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; *      A kernel hook that steals one interrupt from the floppy&n; *      driver (Should be fixed when the new fdc driver gets ready)&n; *      See the linux kernel source files:&n; *          drivers/block/floppy.c &amp; drivers/block/blk.h&n; *      for the details.&n; */
r_extern
r_void
(paren
op_star
id|do_floppy
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
