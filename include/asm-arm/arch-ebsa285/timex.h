multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/timex.h&n; *&n; * EBSA285 architecture timex specifications&n; *&n; * Copyright (C) 1998 Russell King&n; */
multiline_comment|/*&n; * On the EBSA, the clock ticks at weird rates.&n; * This is therefore not used to calculate the&n; * divisor.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(50000000 / 16)
eof
