multiline_comment|/*&n; * include/asm-mips/system.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_MIPS_SYSTEM_H_
DECL|macro|_ASM_MIPS_SYSTEM_H_
mdefine_line|#define _ASM_MIPS_SYSTEM_H_
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;mips/mipsregs.h&gt;
multiline_comment|/*&n; * move_to_user_mode() doesn&squot;t switch to user mode on the mips, since&n; * that would run us into problems: The kernel is located at virtual&n; * address 0x80000000. If we now would switch over to user mode, we&n; * we would immediately get an address error exception.&n; * Anyway - we don&squot;t have problems with a task running in kernel mode,&n; * as long it&squot;s code is foolproof.&n; */
DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode()
DECL|macro|sti
mdefine_line|#define sti() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;mfc0&bslash;t$1,&quot;STR(CP0_STATUS)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;ori&bslash;t$1,$1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mtc0&bslash;t$1,&quot;STR(CP0_STATUS)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;: &quot;$1&quot;,&quot;memory&quot;)
DECL|macro|cli
mdefine_line|#define cli() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;mfc0&bslash;t$1,&quot;STR(CP0_STATUS)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;srl&bslash;t$1,$1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;sll&bslash;t$1,$1,1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mtc0&bslash;t$1,&quot;STR(CP0_STATUS)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;: /* no outputs */ &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;: &quot;$1&quot;,&quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|save_flags
mdefine_line|#define save_flags(x) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mfc0&bslash;t%0,$12&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: &quot;=r&quot; (x) &bslash;&n;&t;: /* no inputs */ &bslash;&n;&t;: &quot;memory&quot;)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;mtc0&bslash;t%0,$12&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;treorder&quot; &bslash;&n;&t;: /* no output */ &bslash;&n;&t;: &quot;r&quot; (x) &bslash;&n;&t;: &quot;memory&quot;)
macro_line|#endif /* _ASM_MIPS_SYSTEM_H_ */
eof
