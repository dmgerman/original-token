multiline_comment|/* $Id: devmap.c,v 1.4 1997/05/01 01:41:31 davem Exp $&n; * promdevmap.c:  Map device/IO areas to virtual addresses.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* Just like the routines in palloc.c, these should not be used&n; * by the kernel at all.  Bootloader facility mainly.  And again,&n; * this is only available on V2 proms and above.&n; */
multiline_comment|/* Map physical device address &squot;paddr&squot; in IO space &squot;ios&squot; of size&n; * &squot;num_bytes&squot; to a virtual address, with &squot;vhint&squot; being a hint to&n; * the prom as to where you would prefer the mapping.  We return&n; * where the prom actually mapped it.&n; */
r_char
op_star
DECL|function|prom_mapio
id|prom_mapio
c_func
(paren
r_char
op_star
id|vhint
comma
r_int
id|ios
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|num_bytes
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|ret
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|num_bytes
op_eq
l_int|0
)paren
op_logical_or
(paren
id|paddr
op_eq
l_int|0
)paren
)paren
(brace
id|ret
op_assign
(paren
r_char
op_star
)paren
l_int|0x0
suffix:semicolon
)brace
r_else
id|ret
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops.v2_dumb_mmap
)paren
)paren
(paren
id|vhint
comma
id|ios
comma
id|paddr
comma
id|num_bytes
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%0], %%g6&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|current_set
(braket
id|hard_smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Unmap an IO/device area that was mapped using the above routine. */
r_void
DECL|function|prom_unmapio
id|prom_unmapio
c_func
(paren
r_char
op_star
id|vaddr
comma
r_int
r_int
id|num_bytes
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|num_bytes
op_eq
l_int|0x0
)paren
(brace
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops.v2_dumb_munmap
)paren
)paren
(paren
id|vaddr
comma
id|num_bytes
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%0], %%g6&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|current_set
(braket
id|hard_smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
