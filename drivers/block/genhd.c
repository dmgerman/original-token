multiline_comment|/*&n; *  Code extracted from&n; *  linux/kernel/hd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *&n; *  devfs support - jj, rgooch, 980122&n; *&n; *  Moved partition checking code to fs/partitions* - Russell King&n; *  (linux@arm.uk.linux.org)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
r_extern
r_int
id|parport_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|chr_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_DAC960
r_extern
r_void
id|DAC960_Initialize
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|scsi_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|net_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|console_map_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|soc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atmdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|i2o_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpqarray_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ieee1394_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|device_init
r_void
id|__init
id|device_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PARPORT
id|parport_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *&t;I2O must come before block and char as the I2O layer may&n;&t; *&t;in future claim devices that block/char most not touch.&n;&t; */
macro_line|#ifdef CONFIG_I2O
id|i2o_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|chr_dev_init
c_func
(paren
)paren
suffix:semicolon
id|blk_dev_init
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_DAC960
id|DAC960_Initialize
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FC4_SOC
multiline_comment|/* This has to be done before scsi_dev_init */
id|soc_probe
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI
id|scsi_dev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IEEE1394
id|ieee1394_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_CPQ_DA
id|cpqarray_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET
id|net_dev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATM
(paren
r_void
)paren
id|atmdev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
id|console_map_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
