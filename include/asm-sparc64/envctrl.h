multiline_comment|/* $Id: envctrl.h,v 1.1 1998/05/16 17:26:07 ecd Exp $&n; *&n; * envctrl.h: Definitions for access to the i2c environment&n; *            monitoring on Ultrasparc systems.&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC64_ENVCTRL_H
DECL|macro|_SPARC64_ENVCTRL_H
mdefine_line|#define _SPARC64_ENVCTRL_H 1
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|I2CIOCSADR
mdefine_line|#define I2CIOCSADR _IOW(&squot;p&squot;, 0x40, int)
DECL|macro|I2CIOCGADR
mdefine_line|#define I2CIOCGADR _IOR(&squot;p&squot;, 0x41, int)
macro_line|#endif /* !(_SPARC64_ENVCTRL_H) */
eof
