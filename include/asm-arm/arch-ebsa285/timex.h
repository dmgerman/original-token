multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/timex.h&n; *&n; * EBSA285 architecture timex specifications&n; *&n; * Copyright (C) 1998 Russell King&n; */
multiline_comment|/*&n; * On EBSA285 boards, the clock runs at 50MHz and is&n; * divided by a 4-bit prescaler.  Other boards use an&n; * ISA derived timer, and this is unused.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(50000000 / 16)
eof
