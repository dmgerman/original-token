macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;mpc.h&quot;
macro_line|#include &quot;lec.h&quot;
multiline_comment|/*&n; * lane_mpoa_init.c: A couple of helper functions&n; * to make modular LANE and MPOA client easier to implement&n; */
multiline_comment|/*&n; * This is how it goes:&n; *&n; * if xxxx is not compiled as module, call atm_xxxx_init_ops()&n; *    from here&n; * else call atm_mpoa_init_ops() from init_module() within&n; *    the kernel when xxxx module is loaded&n; *&n; * In either case function pointers in struct atm_xxxx_ops&n; * are initialized to their correct values. Either they&n; * point to functions in the module or in the kernel&n; */
r_extern
r_struct
id|atm_mpoa_ops
id|atm_mpoa_ops
suffix:semicolon
multiline_comment|/* in common.c */
r_extern
r_struct
id|atm_lane_ops
id|atm_lane_ops
suffix:semicolon
multiline_comment|/* in common.c */
macro_line|#if defined(CONFIG_ATM_MPOA) || defined(CONFIG_ATM_MPOA_MODULE)
DECL|function|atm_mpoa_init
r_void
id|atm_mpoa_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_ATM_MPOA_MODULE /* not module */
id|atm_mpoa_init_ops
c_func
(paren
op_amp
id|atm_mpoa_ops
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_ATM_LANE) || defined(CONFIG_ATM_LANE_MODULE)
macro_line|#if defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
DECL|variable|lane_bridge_hook_lock
id|rwlock_t
id|lane_bridge_hook_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|br_fdb_get_hook
r_struct
id|net_bridge_fdb_entry
op_star
(paren
op_star
id|br_fdb_get_hook
)paren
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_char
op_star
id|addr
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|br_fdb_put_hook
r_void
(paren
op_star
id|br_fdb_put_hook
)paren
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if defined(CONFIG_ATM_LANE_MODULE) || defined(CONFIG_BRIDGE_MODULE)
DECL|variable|lane_bridge_hook_lock
id|EXPORT_SYMBOL
c_func
(paren
id|lane_bridge_hook_lock
)paren
suffix:semicolon
DECL|variable|br_fdb_get_hook
id|EXPORT_SYMBOL
c_func
(paren
id|br_fdb_get_hook
)paren
suffix:semicolon
DECL|variable|br_fdb_put_hook
id|EXPORT_SYMBOL
c_func
(paren
id|br_fdb_put_hook
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_ATM_LANE_MODULE) || defined(CONFIG_BRIDGE_MODULE) */
macro_line|#endif /* defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE) */
DECL|function|atm_lane_init
r_void
id|atm_lane_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_ATM_LANE_MODULE /* not module */
id|atm_lane_init_ops
c_func
(paren
op_amp
id|atm_lane_ops
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
macro_line|#endif
eof
