multiline_comment|/*&n; * include/asm-arm/leds.h&n; *&n; * Copyright (C) 1998 Russell King&n; *&n; * Event-driven interface for LEDs on machines&n; *&n; * Added led_start and led_stop- Alex Holden, 28th Dec 1998.&n; */
macro_line|#ifndef ASM_ARM_LEDS_H
DECL|macro|ASM_ARM_LEDS_H
mdefine_line|#define ASM_ARM_LEDS_H
r_typedef
r_enum
(brace
DECL|enumerator|led_idle_start
id|led_idle_start
comma
DECL|enumerator|led_idle_end
id|led_idle_end
comma
DECL|enumerator|led_timer
id|led_timer
comma
DECL|enumerator|led_start
id|led_start
comma
DECL|enumerator|led_stop
id|led_stop
DECL|typedef|led_event_t
)brace
id|led_event_t
suffix:semicolon
multiline_comment|/* Use this routine to handle LEDs */
r_extern
r_void
id|leds_event
c_func
(paren
id|led_event_t
)paren
suffix:semicolon
macro_line|#endif
eof
