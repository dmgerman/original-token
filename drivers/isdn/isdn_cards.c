macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ISDN_DRV_ICN
r_extern
r_void
id|icn_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN_DRV_TELES
r_extern
r_void
id|teles_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|isdn_cards_init
r_void
id|isdn_cards_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if CONFIG_ISDN_DRV_ICN
id|icn_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN_DRV_TELES
id|teles_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
