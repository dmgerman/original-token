multiline_comment|/*&n; * lowlevel/init.c - Calls initialization code for configured drivers.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_LOWLEVEL_SOUND
r_extern
r_int
id|attach_aci
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unload_aci
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
DECL|function|sound_init_lowlevel_drivers
id|sound_init_lowlevel_drivers
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ACI_MIXER
id|attach_aci
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|sound_unload_lowlevel_drivers
id|sound_unload_lowlevel_drivers
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_ACI_MIXER
id|unload_aci
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof
