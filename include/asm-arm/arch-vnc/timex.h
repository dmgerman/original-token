multiline_comment|/*&n; * linux/include/asm-arm/arch-vnc/timex.h&n; *&n; * Corel Video NC architecture timex specifications&n; *&n; * Copyright (C) 1998 Corel Computer/Russell King&n; */
multiline_comment|/*&n; * On the VNC, the clock runs at 66MHz and is divided&n; * by a 4-bit prescaler.&n; */
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;(66000000 / 16)
eof
