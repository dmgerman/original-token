multiline_comment|/*&n; * lowlevel/init.c - Calls initialization code for configured drivers.&n; */
macro_line|#include &quot;lowlevel.h&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;../soundvers.h&quot;
macro_line|#ifdef LOWLEVEL_MODULE
DECL|variable|lowlevel_version
r_char
op_star
id|lowlevel_version
op_assign
id|SOUND_VERSION_STRING
suffix:semicolon
macro_line|#endif
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
r_extern
r_int
id|attach_awe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unload_awe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_aedsp16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|uninit_aedsp16
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * There are two places where you can insert initialization calls of&n; * low level drivers. sound_init_lowlevel_drivers() is called after&n; * the sound driver has been initialized (the normal case)&n; * while sound_preinit_lowlevel_drivers() is called before that.&n; */
r_void
DECL|function|sound_preinit_lowlevel_drivers
id|sound_preinit_lowlevel_drivers
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_AEDSP16) &amp;&amp; !defined(MODULE)
id|init_aedsp16
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
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
macro_line|#ifdef CONFIG_AWE32_SYNTH
id|attach_awe
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
macro_line|#ifdef CONFIG_AWE32_SYNTH
id|unload_awe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AEDSP16
id|uninit_aedsp16
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|sound_init_lowlevel_drivers
id|EXPORT_SYMBOL
c_func
(paren
id|sound_init_lowlevel_drivers
)paren
suffix:semicolon
DECL|variable|sound_unload_lowlevel_drivers
id|EXPORT_SYMBOL
c_func
(paren
id|sound_unload_lowlevel_drivers
)paren
suffix:semicolon
DECL|variable|sound_preinit_lowlevel_drivers
id|EXPORT_SYMBOL
c_func
(paren
id|sound_preinit_lowlevel_drivers
)paren
suffix:semicolon
eof