multiline_comment|/*&n; * include/asm-ppc/serial.h&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_APUS
macro_line|#include &lt;asm-m68k/serial.h&gt;
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD ( 1843200 / 16 )
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
macro_line|#endif
macro_line|#endif /* CONFIG_APUS */
eof
