multiline_comment|/*&n; * include/asm-arm/leds.h&n; *&n; * Copyright (C) 1998 Russell King&n; *&n; * Event-driven interface for LEDs on machines&n; *&n; * Added led_start and led_stop- Alex Holden, 28th Dec 1998.&n; */
macro_line|#ifndef ASM_ARM_LEDS_H
DECL|macro|ASM_ARM_LEDS_H
mdefine_line|#define ASM_ARM_LEDS_H
macro_line|#include &lt;linux/config.h&gt;
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
comma
DECL|enumerator|led_claim
id|led_claim
comma
multiline_comment|/* override idle &amp; timer leds */
DECL|enumerator|led_release
id|led_release
comma
multiline_comment|/* restore idle &amp; timer leds */
DECL|enumerator|led_green_on
id|led_green_on
comma
DECL|enumerator|led_green_off
id|led_green_off
comma
DECL|enumerator|led_amber_on
id|led_amber_on
comma
DECL|enumerator|led_amber_off
id|led_amber_off
comma
DECL|enumerator|led_red_on
id|led_red_on
comma
DECL|enumerator|led_red_off
id|led_red_off
DECL|typedef|led_event_t
)brace
id|led_event_t
suffix:semicolon
multiline_comment|/* Use this routine to handle LEDs */
macro_line|#ifdef CONFIG_LEDS
r_extern
r_void
(paren
op_star
id|leds_event
)paren
(paren
id|led_event_t
)paren
suffix:semicolon
DECL|macro|set_leds_event
mdefine_line|#define set_leds_event(r)&t;leds_event = r
macro_line|#else
DECL|macro|leds_event
mdefine_line|#define leds_event(e)
DECL|macro|set_leds_event
mdefine_line|#define set_leds_event(r)
macro_line|#endif
macro_line|#endif
eof
