multiline_comment|/* drivers/atm/atmdev_init.c - ATM device driver initialization */
multiline_comment|/* Written 1995-1997 by Werner Almesberger, EPFL LRC */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_ATM_ENI
r_extern
r_int
id|eni_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_ZATM
r_extern
r_int
id|zatm_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_TNETA1570
r_extern
r_int
id|tneta1570_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_NICSTAR
r_extern
r_int
id|nicstar_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_AMBASSADOR
r_extern
r_int
id|amb_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_HORIZON
r_extern
r_int
id|hrz_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_IA
r_extern
r_int
id|ia_detect
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|atmdev_init
r_int
id|__init
id|atmdev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|devs
suffix:semicolon
id|devs
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ATM_ENI
id|devs
op_add_assign
id|eni_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_ZATM
id|devs
op_add_assign
id|zatm_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_TNETA1570
id|devs
op_add_assign
id|tneta1570_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_NICSTAR
id|devs
op_add_assign
id|nicstar_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_AMBASSADOR
id|devs
op_add_assign
id|amb_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_HORIZON
id|devs
op_add_assign
id|hrz_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM_IA
id|devs
op_add_assign
id|ia_detect
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|devs
suffix:semicolon
)brace
eof
