multiline_comment|/* $Id: sun4paddr.h,v 1.2 1998/02/09 13:26:41 jj Exp $&n; * sun4paddr.h:  Various physical addresses on sun4 machines&n; *&n; * Copyright (C) 1997 Anton Blanchard (anton@progsoc.uts.edu.au)&n; */
macro_line|#ifndef _SPARC_SUN4PADDR_H
DECL|macro|_SPARC_SUN4PADDR_H
mdefine_line|#define _SPARC_SUN4PADDR_H
DECL|macro|SUN4_MEMREG_PHYSADDR
mdefine_line|#define SUN4_MEMREG_PHYSADDR&t;&t;0xf4000000
DECL|macro|SUN4_IE_PHYSADDR
mdefine_line|#define SUN4_IE_PHYSADDR&t;&t;0xf5000000
DECL|macro|SUN4_300_MOSTEK_PHYSADDR
mdefine_line|#define SUN4_300_MOSTEK_PHYSADDR&t;0xf2000000
DECL|macro|SUN4_300_TIMER_PHYSADDR
mdefine_line|#define SUN4_300_TIMER_PHYSADDR&t;&t;0xef000000
DECL|macro|SUN4_300_ETH_PHYSADDR
mdefine_line|#define SUN4_300_ETH_PHYSADDR&t;&t;0xf9000000
DECL|macro|SUN4_300_BWTWO_PHYSADDR
mdefine_line|#define SUN4_300_BWTWO_PHYSADDR&t;&t;0xfb400000
DECL|macro|SUN4_300_DMA_PHYSADDR
mdefine_line|#define SUN4_300_DMA_PHYSADDR&t;&t;0xfa001000
DECL|macro|SUN4_300_ESP_PHYSADDR
mdefine_line|#define SUN4_300_ESP_PHYSADDR&t;&t;0xfa000000
macro_line|#endif /* !(_SPARC_SUN4PADDR_H) */
eof
