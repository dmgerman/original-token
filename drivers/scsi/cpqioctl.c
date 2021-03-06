singleline_comment|// Test program for CPQFCTS ioctl calls
singleline_comment|// build with:
singleline_comment|// gcc -o cpqioctl cpqioctl.c
singleline_comment|// ld -o cpqioctl /lib/crt0.o cpqioctl.o -lc
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;../../include/scsi/scsi.h&quot;
macro_line|#include &quot;cpqfcTSioctl.h&quot;
DECL|struct|scsi_fctargaddress
r_typedef
r_struct
id|scsi_fctargaddress
(brace
DECL|member|host_port_id
r_int
r_int
id|host_port_id
suffix:semicolon
DECL|member|host_wwn
r_int
r_char
id|host_wwn
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|Scsi_FCTargAddress
)brace
id|Scsi_FCTargAddress
suffix:semicolon
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|fd
comma
id|i
suffix:semicolon
id|Scsi_FCTargAddress
id|targ
suffix:semicolon
r_int
id|uselect
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;usage: cpqioctl &lt;Devfile&gt;&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|O_RDONLY
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;open&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|SCSI_IOCTL_FC_TARGET_ADDRESS
comma
op_amp
id|targ
)paren
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;ioctl&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;portid: %08x. wwn: &quot;
comma
id|targ.host_port_id
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|printf
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|targ.host_wwn
(braket
id|i
)braket
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|uselect
op_ne
l_int|27
)paren
singleline_comment|// not ESC key
(brace
id|printf
c_func
(paren
l_string|&quot;&bslash;n IOCTL &bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;1. Get PCI info&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;2. Send Passthru&bslash;n&quot;
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; ==&gt; &quot;
)paren
suffix:semicolon
id|scanf
c_func
(paren
l_string|&quot;%c&quot;
comma
op_amp
id|uselect
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|uselect
)paren
(brace
r_case
l_char|&squot;1&squot;
suffix:colon
(brace
id|cciss_pci_info_struct
id|pciinfo
suffix:semicolon
r_if
c_cond
(paren
id|ioctl
c_func
(paren
id|fd
comma
id|CCPQFCTS_GETPCIINFO
comma
op_amp
id|pciinfo
)paren
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;ioctl&quot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;&bslash;nPCI bus %d, dev_fn %d, board_id %Xh&bslash;n&quot;
comma
id|pciinfo.bus
comma
id|pciinfo.dev_fn
comma
id|pciinfo.board_id
)paren
suffix:semicolon
)brace
)brace
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
