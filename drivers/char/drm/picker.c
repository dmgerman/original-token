macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef CONFIG_SMP
DECL|macro|CONFIG_SMP
mdefine_line|#define CONFIG_SMP 0
macro_line|#endif
macro_line|#ifndef CONFIG_MODVERSIONS
DECL|macro|CONFIG_MODVERSIONS
mdefine_line|#define CONFIG_MODVERSIONS 0
macro_line|#endif
macro_line|#ifndef CONFIG_AGP_MODULE
DECL|macro|CONFIG_AGP_MODULE
mdefine_line|#define CONFIG_AGP_MODULE 0
macro_line|#endif
macro_line|#ifndef CONFIG_AGP
DECL|macro|CONFIG_AGP
mdefine_line|#define CONFIG_AGP 0
macro_line|#endif
macro_line|#ifndef CONFIG_FB_SIS
DECL|macro|CONFIG_FB_SIS
mdefine_line|#define CONFIG_FB_SIS 0
macro_line|#endif
id|SMP
op_assign
id|CONFIG_SMP
id|MODVERSIONS
op_assign
id|CONFIG_MODVERSIONS
id|AGP
op_assign
id|CONFIG_AGP
id|AGP_MODULE
op_assign
id|CONFIG_AGP_MODULE
id|RELEASE
op_assign
id|UTS_RELEASE
id|SIS
op_assign
id|CONFIG_FB_SIS
eof
