DECL|macro|acornfb_valid_pixrate
mdefine_line|#define acornfb_valid_pixrate(rate) (rate &gt;= 39325 &amp;&amp; rate &lt;= 40119)
r_static
r_inline
r_void
DECL|function|acornfb_vidc20_find_rates
id|acornfb_vidc20_find_rates
c_func
(paren
r_struct
id|vidc_timing
op_star
id|vidc
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
id|u_int
id|bandwidth
suffix:semicolon
id|vidc-&gt;control
op_or_assign
id|VIDC20_CTRL_PIX_CK
suffix:semicolon
multiline_comment|/* Calculate bandwidth */
id|bandwidth
op_assign
id|var-&gt;pixclock
op_star
l_int|8
op_div
id|var-&gt;bits_per_pixel
suffix:semicolon
multiline_comment|/* Encode bandwidth as VIDC20 setting */
r_if
c_cond
(paren
id|bandwidth
OG
l_int|16667
op_star
l_int|2
)paren
id|vidc-&gt;control
op_or_assign
id|VIDC20_CTRL_FIFO_16
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bandwidth
OG
l_int|13333
op_star
l_int|2
)paren
id|vidc-&gt;control
op_or_assign
id|VIDC20_CTRL_FIFO_20
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bandwidth
OG
l_int|11111
op_star
l_int|2
)paren
id|vidc-&gt;control
op_or_assign
id|VIDC20_CTRL_FIFO_24
suffix:semicolon
r_else
id|vidc-&gt;control
op_or_assign
id|VIDC20_CTRL_FIFO_28
suffix:semicolon
id|vidc-&gt;pll_ctl
op_assign
l_int|0x2020
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_CHRONTEL_7003
DECL|macro|acornfb_default_control
mdefine_line|#define acornfb_default_control()&t;VIDC20_CTRL_PIX_HCLK
macro_line|#else
DECL|macro|acornfb_default_control
mdefine_line|#define acornfb_default_control()&t;VIDC20_CTRL_PIX_VCLK
macro_line|#endif
DECL|macro|acornfb_default_econtrol
mdefine_line|#define acornfb_default_econtrol()&t;VIDC20_ECTL_DAC | VIDC20_ECTL_REG(3) | VIDC20_ECTL_ECK
eof
