multiline_comment|/* sun_cg_common.h&n; * contains the definitions of the structures that various sun&n; * frame buffer can use to do console driver stuff.&n; * &n; * This is not in sun_framebuffer.h because you may not want cgXX&n; * support so you wont require this.&n; *&n; */
DECL|macro|BT_D4M3
mdefine_line|#define BT_D4M3(x) ((((x) &gt;&gt; 2) &lt;&lt; 1) + ((x) &gt;&gt; 2))     /* (x / 4) * 3 */
DECL|macro|BT_D4M4
mdefine_line|#define BT_D4M4(x) ((x) &amp; ~3)                           /* (x / 4) * 4 */
DECL|macro|D4M3
mdefine_line|#define D4M3(x) ((((x)&gt;&gt;2)&lt;&lt;1) + ((x)&gt;&gt;2))      /* (x/4)*3 */
DECL|macro|D4M4
mdefine_line|#define D4M4(x) ((x)&amp;~0x3)                      /* (x/4)*4 */
DECL|struct|bt_regs
r_struct
id|bt_regs
(brace
DECL|member|addr
r_volatile
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* address register */
DECL|member|color_map
r_volatile
r_int
r_int
id|color_map
suffix:semicolon
multiline_comment|/* color map */
DECL|member|control
r_volatile
r_int
r_int
id|control
suffix:semicolon
multiline_comment|/* control register */
DECL|member|cursor
r_volatile
r_int
r_int
id|cursor
suffix:semicolon
multiline_comment|/* cursor map register */
)brace
suffix:semicolon
multiline_comment|/* The cg3 driver, obio space addresses for mapping the cg3 stuff */
multiline_comment|/* We put these constants here, because the cg14 driver initially will emulate a cg3 */
DECL|macro|CG3_REGS
mdefine_line|#define CG3_REGS 0x400000
DECL|macro|CG3_RAM
mdefine_line|#define CG3_RAM&t; 0x800000
eof
