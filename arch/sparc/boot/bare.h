multiline_comment|/* $Id: bare.h,v 1.2 1995/11/25 00:57:41 davem Exp $&n; * bare.h:  Defines for the low level entry code of the BOOT program.&n; *          We include in the head.h stuff that the real kernel uses&n; *          and this saves a lot of repetition here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/cprefix.h&gt;
DECL|macro|SANE_PIL
mdefine_line|#define     SANE_PIL  (0xd00)    /* No interrupts except clock and unmaskable NMI&squot;s */
DECL|macro|SANE_PSR
mdefine_line|#define     SANE_PSR  (SANE_PIL|PSR_S|PSR_ET)
DECL|macro|BOOTBLOCK_NENTRIES
mdefine_line|#define     BOOTBLOCK_NENTRIES   0x40      /* Number of entries in the boot block */
DECL|macro|BOOTBLOCK_ENTSIZE
mdefine_line|#define     BOOTBLOCK_ENTSIZE    0x04      /* Size in bytes of each boot block entry */
eof
