macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_1GB
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW 0xC0000000
macro_line|#elif defined(CONFIG_2GB)
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW 0x80000000
macro_line|#elif defined(CONFIG_3GB)
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW 0x40000000
macro_line|#endif
eof
