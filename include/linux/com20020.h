multiline_comment|/*&n; * Linux ARCnet driver - COM20020 chipset support - function declarations&n; * &n; * Written 1997 by David Woodhouse.&n; * Written 1994-1999 by Avery Pennarun.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#ifndef __COM20020_H
DECL|macro|__COM20020_H
mdefine_line|#define __COM20020_H
r_int
id|com20020_check
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|com20020_found
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|shared
)paren
suffix:semicolon
multiline_comment|/* The number of low I/O ports used by the card. */
DECL|macro|ARCNET_TOTAL_SIZE
mdefine_line|#define ARCNET_TOTAL_SIZE 9
multiline_comment|/* various register addresses */
DECL|macro|_INTMASK
mdefine_line|#define _INTMASK  (ioaddr+0)&t;/* writable */
DECL|macro|_STATUS
mdefine_line|#define _STATUS   (ioaddr+0)&t;/* readable */
DECL|macro|_COMMAND
mdefine_line|#define _COMMAND  (ioaddr+1)&t;/* standard arcnet commands */
DECL|macro|_DIAGSTAT
mdefine_line|#define _DIAGSTAT (ioaddr+1)&t;/* diagnostic status register */
DECL|macro|_ADDR_HI
mdefine_line|#define _ADDR_HI  (ioaddr+2)&t;/* control registers for IO-mapped memory */
DECL|macro|_ADDR_LO
mdefine_line|#define _ADDR_LO  (ioaddr+3)
DECL|macro|_MEMDATA
mdefine_line|#define _MEMDATA  (ioaddr+4)&t;/* data port for IO-mapped memory */
DECL|macro|_CONFIG
mdefine_line|#define _CONFIG   (ioaddr+6)&t;/* configuration register */
DECL|macro|_SETUP
mdefine_line|#define _SETUP    (ioaddr+7)&t;/* setup register */
multiline_comment|/* in the ADDR_HI register */
DECL|macro|RDDATAflag
mdefine_line|#define RDDATAflag&t;0x80&t;/* next access is a read (not a write) */
multiline_comment|/* in the DIAGSTAT register */
DECL|macro|NEWNXTIDflag
mdefine_line|#define NEWNXTIDflag&t;0x02&t;/* ID to which token is passed has changed */
multiline_comment|/* in the CONFIG register */
DECL|macro|RESETcfg
mdefine_line|#define RESETcfg&t;0x80&t;/* put card in reset state */
DECL|macro|TXENcfg
mdefine_line|#define TXENcfg&t;&t;0x20&t;/* enable TX */
multiline_comment|/* in SETUP register */
DECL|macro|PROMISCset
mdefine_line|#define PROMISCset&t;0x10&t;/* enable RCV_ALL */
DECL|macro|REGTENTID
mdefine_line|#define REGTENTID (lp-&gt;config &amp;= ~3);
DECL|macro|REGNID
mdefine_line|#define REGNID (lp-&gt;config = (lp-&gt;config&amp;~2)|1);
DECL|macro|REGSETUP
mdefine_line|#define REGSETUP (lp-&gt;config = (lp-&gt;config&amp;~1)|2);
DECL|macro|REGNXTID
mdefine_line|#define REGNXTID (lp-&gt;config |= 3);
DECL|macro|ARCRESET
macro_line|#undef ARCRESET
DECL|macro|ASTATUS
macro_line|#undef ASTATUS
DECL|macro|ACOMMAND
macro_line|#undef ACOMMAND
DECL|macro|AINTMASK
macro_line|#undef AINTMASK
DECL|macro|ARCRESET
mdefine_line|#define ARCRESET { outb(lp-&gt;config | 0x80, _CONFIG); &bslash;&n;&t;&t;    udelay(5);                        &bslash;&n;&t;&t;    outb(lp-&gt;config , _CONFIG);       &bslash;&n;                  }
DECL|macro|ARCRESET0
mdefine_line|#define ARCRESET0 { outb(0x18 | 0x80, _CONFIG);   &bslash;&n;&t;&t;    udelay(5);                       &bslash;&n;&t;&t;    outb(0x18 , _CONFIG);            &bslash;&n;                  }
DECL|macro|ASTATUS
mdefine_line|#define ASTATUS()&t;inb(_STATUS)
DECL|macro|ACOMMAND
mdefine_line|#define ACOMMAND(cmd)&t;outb((cmd),_COMMAND)
DECL|macro|AINTMASK
mdefine_line|#define AINTMASK(msk)&t;outb((msk),_INTMASK)
DECL|macro|SETCONF
mdefine_line|#define SETCONF(cfg)&t;outb(cfg, _CONFIG)
macro_line|#endif /* __COM20020_H */
eof
