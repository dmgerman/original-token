multiline_comment|/* $Id: auxio.h,v 1.11 1996/04/25 06:12:45 davem Exp $&n; * auxio.h:  Definitions and code for the Auxiliary I/O register.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_AUXIO_H
DECL|macro|_SPARC_AUXIO_H
mdefine_line|#define _SPARC_AUXIO_H
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
r_extern
r_int
r_char
op_star
id|auxio_register
suffix:semicolon
multiline_comment|/* This register is an unsigned char in IO space.  It does two things.&n; * First, it is used to control the front panel LED light on machines&n; * that have it (good for testing entry points to trap handlers and irq&squot;s)&n; * Secondly, it controls various floppy drive parameters.&n; */
DECL|macro|AUXIO_ORMEIN
mdefine_line|#define AUXIO_ORMEIN      0xf0    /* All writes must set these bits. */
DECL|macro|AUXIO_ORMEIN4M
mdefine_line|#define AUXIO_ORMEIN4M    0xc0    /* sun4m - All writes must set these bits. */
DECL|macro|AUXIO_FLPY_DENS
mdefine_line|#define AUXIO_FLPY_DENS   0x20    /* Floppy density, high if set. Read only. */
DECL|macro|AUXIO_FLPY_DCHG
mdefine_line|#define AUXIO_FLPY_DCHG   0x10    /* A disk change occurred.  Read only. */
DECL|macro|AUXIO_EDGE_ON
mdefine_line|#define AUXIO_EDGE_ON     0x10    /* sun4m - On means Jumper block is in. */
DECL|macro|AUXIO_FLPY_DSEL
mdefine_line|#define AUXIO_FLPY_DSEL   0x08    /* Drive select/start-motor. Write only. */
multiline_comment|/* Set the following to one, then zero, after doing a pseudo DMA transfer. */
DECL|macro|AUXIO_FLPY_TCNT
mdefine_line|#define AUXIO_FLPY_TCNT   0x04    /* Floppy terminal count. Write only. */
multiline_comment|/* Set the following to zero to eject the floppy. */
DECL|macro|AUXIO_FLPY_EJCT
mdefine_line|#define AUXIO_FLPY_EJCT   0x02    /* Eject floppy disk.  Write only. */
DECL|macro|AUXIO_LED
mdefine_line|#define AUXIO_LED         0x01    /* On if set, off if unset. Read/Write */
DECL|macro|AUXREG
mdefine_line|#define AUXREG   ((volatile unsigned char *)(auxio_register))
DECL|macro|TURN_ON_LED
mdefine_line|#define TURN_ON_LED   *AUXREG = (*AUXREG | AUXIO_ORMEIN | AUXIO_LED)
DECL|macro|TURN_OFF_LED
mdefine_line|#define TURN_OFF_LED  *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_LED))
DECL|macro|FLIP_LED
mdefine_line|#define FLIP_LED      *AUXREG = ((*AUXREG | AUXIO_ORMEIN) ^ AUXIO_LED)
DECL|macro|FLPY_MOTORON
mdefine_line|#define FLPY_MOTORON  *AUXREG = ((*AUXREG | AUXIO_ORMEIN) | AUXIO_FLPY_DSEL)
DECL|macro|FLPY_MOTOROFF
mdefine_line|#define FLPY_MOTOROFF *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_DSEL))
DECL|macro|FLPY_TCNTON
mdefine_line|#define FLPY_TCNTON   *AUXREG = ((*AUXREG | AUXIO_ORMEIN) | AUXIO_FLPY_TCNT)
DECL|macro|FLPY_TCNTOFF
mdefine_line|#define FLPY_TCNTOFF  *AUXREG = ((*AUXREG | AUXIO_ORMEIN) &amp; (~AUXIO_FLPY_TCNT))
macro_line|#ifndef __ASSEMBLY__
DECL|function|set_auxio
r_extern
r_inline
r_void
id|set_auxio
c_func
(paren
r_int
r_char
id|bits_on
comma
r_int
r_char
id|bits_off
)paren
(brace
r_int
r_char
id|regval
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sparc_cpu_model
)paren
(brace
r_case
id|sun4c
suffix:colon
id|regval
op_assign
op_star
id|AUXREG
suffix:semicolon
op_star
id|AUXREG
op_assign
(paren
(paren
id|regval
op_or
id|bits_on
)paren
op_amp
op_complement
id|bits_off
)paren
op_or
id|AUXIO_ORMEIN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sun4m
suffix:colon
id|regval
op_assign
op_star
id|AUXREG
suffix:semicolon
op_star
id|AUXREG
op_assign
(paren
(paren
id|regval
op_or
id|bits_on
)paren
op_amp
op_complement
id|bits_off
)paren
op_or
id|AUXIO_ORMEIN4M
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Can&squot;t set AUXIO register on this machine.&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(_SPARC_AUXIO_H) */
eof
