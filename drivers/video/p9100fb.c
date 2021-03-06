multiline_comment|/* $id: p9100fb.c,v 1.4 1999/08/18 10:55:01 shadow Exp $&n; * p9100fb.c: P9100 frame buffer driver&n; *&n; * Copyright 1999 Derrick J Brashear (shadow@dementia.org)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;video/sbusfb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &quot;p9100.h&quot;
DECL|variable|p9100_mmap_map
r_static
r_struct
id|sbus_mmap_map
id|p9100_mmap_map
(braket
)braket
op_assign
(brace
macro_line|#if 0 /* For now, play we&squot;re a dumb color fb */
(brace
id|P9100_CTL_OFF
comma
l_int|0x38000000
comma
l_int|0x2000
)brace
comma
(brace
id|P9100_CMD_OFF
comma
l_int|0x38002000
comma
l_int|0x2000
)brace
comma
(brace
id|P9100_FB_OFF
comma
l_int|0x38800000
comma
l_int|0x200000
)brace
comma
(brace
id|CG3_MMAP_OFFSET
comma
l_int|0x38800000
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
macro_line|#else
(brace
id|CG3_MMAP_OFFSET
comma
l_int|0x0
comma
id|SBUS_MMAP_FBSIZE
c_func
(paren
l_int|1
)paren
)brace
comma
macro_line|#endif
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|_READCTL
mdefine_line|#define _READCTL(member, out) &bslash;&n;{ &bslash;&n;  struct p9100_ctrl *actual; &bslash;&n;  actual = (struct p9100_ctrl *)fb-&gt;s.p9100.ctrl; &bslash;&n;  out = sbus_readl(&amp;actual-&gt; ## member ); &bslash;&n;}
DECL|macro|READCTL
mdefine_line|#define READCTL(member, out) &bslash;&n;{ &bslash;&n;  struct p9100_ctrl *enab, *actual; &bslash;&n;  actual = (struct p9100_ctrl *)fb-&gt;s.p9100.ctrl; &bslash;&n;  enab = (struct p9100_ctrl *)fb-&gt;s.p9100.fbmem; &bslash;&n;  out = sbus_readl(&amp;enab-&gt; ## member ); &bslash;&n;  out = sbus_readl(&amp;actual-&gt; ## member ); &bslash;&n;}
DECL|macro|WRITECTL
mdefine_line|#define WRITECTL(member, val) &bslash;&n;{ &bslash;&n;  u32 __writetmp; &bslash;&n;  struct p9100_ctrl *enab, *actual; &bslash;&n;  actual = (struct p9100_ctrl *)fb-&gt;s.p9100.ctrl; &bslash;&n;  enab = (struct p9100_ctrl *)fb-&gt;s.p9100.fbmem; &bslash;&n;  __writetmp = sbus_readl(&amp;enab-&gt; ## member ); &bslash;&n;  sbus_writel(val, &amp;actual-&gt; ## member ); &bslash;&n;}
DECL|function|p9100_loadcmap
r_static
r_void
id|p9100_loadcmap
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|index
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|_READCTL
c_func
(paren
id|pwrup_cfg
comma
id|tmp
)paren
suffix:semicolon
id|WRITECTL
c_func
(paren
id|ramdac_cmap_wridx
comma
(paren
id|index
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|index
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|i
op_increment
)paren
(brace
id|_READCTL
c_func
(paren
id|pwrup_cfg
comma
id|tmp
)paren
suffix:semicolon
id|WRITECTL
c_func
(paren
id|ramdac_palette_data
comma
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|0
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|_READCTL
c_func
(paren
id|pwrup_cfg
comma
id|tmp
)paren
suffix:semicolon
id|WRITECTL
c_func
(paren
id|ramdac_palette_data
comma
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|1
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
id|_READCTL
c_func
(paren
id|pwrup_cfg
comma
id|tmp
)paren
suffix:semicolon
id|WRITECTL
c_func
(paren
id|ramdac_palette_data
comma
(paren
id|fb-&gt;color_map
id|CM
c_func
(paren
id|i
comma
l_int|2
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|p9100_blank
r_static
r_void
id|p9100_blank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|READCTL
c_func
(paren
id|vid_screenpaint_timectl1
comma
id|val
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|SCREENPAINT_TIMECTL1_ENABLE_VIDEO
suffix:semicolon
id|WRITECTL
c_func
(paren
id|vid_screenpaint_timectl1
comma
id|val
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|p9100_unblank
r_static
r_void
id|p9100_unblank
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|READCTL
c_func
(paren
id|vid_screenpaint_timectl1
comma
id|val
)paren
suffix:semicolon
id|val
op_or_assign
id|SCREENPAINT_TIMECTL1_ENABLE_VIDEO
suffix:semicolon
id|WRITECTL
c_func
(paren
id|vid_screenpaint_timectl1
comma
id|val
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|fb-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|p9100_margins
r_static
r_void
id|p9100_margins
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|x_margin
comma
r_int
id|y_margin
)paren
(brace
id|p-&gt;screen_base
op_add_assign
(paren
id|y_margin
op_minus
id|fb-&gt;y_margin
)paren
op_star
id|p-&gt;line_length
op_plus
(paren
id|x_margin
op_minus
id|fb-&gt;x_margin
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_char
id|idstring
(braket
l_int|60
)braket
id|__initdata
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|function|p9100fb_init
r_char
op_star
id|__init
id|p9100fb_init
c_func
(paren
r_struct
id|fb_info_sbusfb
op_star
id|fb
)paren
(brace
r_struct
id|fb_fix_screeninfo
op_star
id|fix
op_assign
op_amp
id|fb-&gt;fix
suffix:semicolon
r_struct
id|display
op_star
id|disp
op_assign
op_amp
id|fb-&gt;disp
suffix:semicolon
r_struct
id|fbtype
op_star
id|type
op_assign
op_amp
id|fb-&gt;type
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
op_assign
id|fb-&gt;sbdp
suffix:semicolon
r_int
r_int
id|phys
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|2
)braket
dot
id|phys_addr
suffix:semicolon
r_int
id|tmp
suffix:semicolon
macro_line|#ifndef FBCON_HAS_CFB8
r_return
l_int|NULL
suffix:semicolon
macro_line|#endif
multiline_comment|/* Control regs: fb-&gt;sbdp-&gt;reg_addrs[0].phys_addr &n;&t; * Command regs: fb-&gt;sbdp-&gt;reg_addrs[1].phys_addr &n;&t; * Frame buffer: fb-&gt;sbdp-&gt;reg_addrs[2].phys_addr &n;         */
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;s.p9100.ctrl
)paren
(brace
id|fb-&gt;s.p9100.ctrl
op_assign
(paren
r_struct
id|p9100_ctrl
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
comma
l_string|&quot;p9100 ctrl&quot;
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|fb-&gt;info.modename
comma
l_string|&quot;p9100&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;p9100&quot;
)paren
suffix:semicolon
id|fix-&gt;accel
op_assign
id|FB_ACCEL_SUN_CGTHREE
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|fb-&gt;var.xres_virtual
suffix:semicolon
id|disp-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|disp-&gt;screen_base
)paren
id|disp-&gt;screen_base
op_assign
(paren
r_char
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|2
)braket
comma
l_int|0
comma
id|type-&gt;fb_size
comma
l_string|&quot;p9100 ram&quot;
)paren
suffix:semicolon
id|fb-&gt;s.p9100.fbmem
op_assign
(paren
r_volatile
id|u32
op_star
)paren
id|disp-&gt;screen_base
suffix:semicolon
id|disp-&gt;screen_base
op_add_assign
id|fix-&gt;line_length
op_star
id|fb-&gt;y_margin
op_plus
id|fb-&gt;x_margin
suffix:semicolon
id|READCTL
c_func
(paren
id|sys_config
comma
id|tmp
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|tmp
op_rshift
id|SYS_CONFIG_PIXELSIZE_SHIFT
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|7
suffix:colon
id|type-&gt;fb_depth
op_assign
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|type-&gt;fb_depth
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|type-&gt;fb_depth
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|type-&gt;fb_depth
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;p9100: screen depth unknown: 0x%x&quot;
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fb-&gt;dispsw
op_assign
id|fbcon_cfb8
suffix:semicolon
id|fb-&gt;margins
op_assign
id|p9100_margins
suffix:semicolon
id|fb-&gt;loadcmap
op_assign
id|p9100_loadcmap
suffix:semicolon
id|fb-&gt;blank
op_assign
id|p9100_blank
suffix:semicolon
id|fb-&gt;unblank
op_assign
id|p9100_unblank
suffix:semicolon
id|fb-&gt;physbase
op_assign
id|phys
suffix:semicolon
id|fb-&gt;mmap_map
op_assign
id|p9100_mmap_map
suffix:semicolon
id|sprintf
c_func
(paren
id|idstring
comma
l_string|&quot;%s at 0x%x&quot;
comma
l_string|&quot;p9100&quot;
comma
(paren
r_int
r_int
)paren
id|disp-&gt;screen_base
)paren
suffix:semicolon
r_return
id|idstring
suffix:semicolon
)brace
eof
