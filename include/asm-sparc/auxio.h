multiline_comment|/* auxio.h:  Definitons and code for the Auxiliary I/O register.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_AUXIO_H
DECL|macro|_SPARC_AUXIO_H
mdefine_line|#define _SPARC_AUXIO_H
multiline_comment|/* This defines the register as I know it on the Sun4c, it may be&n; * different or not exist at all on sun4m&squot;s.&n; */
DECL|macro|AUXIO_IOADDR
mdefine_line|#define AUXIO_IOADDR  0xf7400000  /* Physical address is IO space */
multiline_comment|/* This register is an unsigned char in IO space.  It does two things.&n; * First, it is used to control the front panel LED light on machines&n; * that have it (good for testing entry points to trap handlers and irq&squot;s)&n; * Secondly, it controls various floppy drive parameters on machines that&n; * have a drive.&n; */
DECL|macro|AUXIO_ORMEIN
mdefine_line|#define AUXIO_ORMEIN      0xf0    /* All writes must set these bits. */
DECL|macro|AUXIO_FLPY_DENS
mdefine_line|#define AUXIO_FLPY_DENS   0x20    /* Floppy density, high if set. */
DECL|macro|AUXIO_FLPY_DCHG
mdefine_line|#define AUXIO_FLPY_DCHG   0x10    /* A disk change occurred. */
DECL|macro|AUXIO_FLPY_DSEL
mdefine_line|#define AUXIO_FLPY_DSEL   0x08    /* Drive select, 0 &squot;a drive&squot; 1 &squot;b drive&squot;. */
DECL|macro|AUXIO_FLPY_TCNT
mdefine_line|#define AUXIO_FLPY_TCNT   0x04    /* Floppy terminal count... ??? */
DECL|macro|AUXIO_FLPY_EJCT
mdefine_line|#define AUXIO_FLPY_EJCT   0x02    /* Eject floppy disk. */
DECL|macro|AUXIO_LED
mdefine_line|#define AUXIO_LED         0x01    /* On if set, off if unset. */
DECL|macro|AUXREG
mdefine_line|#define AUXREG ((volatile unsigned char *)(AUXIO_VADDR + 3))
DECL|macro|TURN_ON_LED
mdefine_line|#define TURN_ON_LED  *AUXREG = AUXIO_ORMEIN | AUXIO_FLPY_EJCT | AUXIO_LED
DECL|macro|TURN_OFF_LED
mdefine_line|#define TURN_OFF_LED *AUXREG = AUXIO_ORMEIN | AUXIO_FLPY_EJCT
DECL|macro|FLIP_LED
mdefine_line|#define FLIP_LED     *AUXREG = (*AUXREG | AUXIO_ORMEIN) ^ AUXIO_LED
macro_line|#endif /* !(_SPARC_AUXIO_H) */
eof
