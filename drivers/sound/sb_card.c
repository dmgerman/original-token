multiline_comment|/*&n; * sound/sb_card.c&n; *&n; * Detection routine for the Sound Blaster cards.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIG_SBDSP)
macro_line|#include &quot;sb_mixer.h&quot;
macro_line|#include &quot;sb.h&quot;
r_void
DECL|function|attach_sb_card
id|attach_sb_card
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if defined(CONFIG_AUDIO) || defined(CONFIG_MIDI)
id|sb_dsp_init
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|probe_sb
id|probe_sb
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|16
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;&bslash;n&bslash;nsb_dsp.c: I/O port %x already in use&bslash;n&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|sb_dsp_detect
(paren
id|hw_config
)paren
suffix:semicolon
)brace
r_void
DECL|function|unload_sb
id|unload_sb
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|sb_dsp_unload
(paren
id|hw_config
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
