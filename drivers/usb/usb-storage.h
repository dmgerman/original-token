multiline_comment|/* Driver for USB mass storage - include file&n; *&n; * (c) 1999 Michael Gee (michael@linuxspecific.com)&n; * (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|USB_STORAGE
mdefine_line|#define USB_STORAGE &quot;usb-storage: &quot;
macro_line|#ifdef CONFIG_USB_STORAGE_DEBUG
r_void
id|us_show_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
suffix:semicolon
DECL|macro|US_DEBUGP
mdefine_line|#define US_DEBUGP(x...) printk( KERN_DEBUG USB_STORAGE ## x )
DECL|macro|US_DEBUGPX
mdefine_line|#define US_DEBUGPX(x...) printk( ## x )
DECL|macro|US_DEBUG
mdefine_line|#define US_DEBUG(x) x 
macro_line|#else
DECL|macro|US_DEBUGP
mdefine_line|#define US_DEBUGP(x...)
DECL|macro|US_DEBUGPX
mdefine_line|#define US_DEBUGPX(x...)
DECL|macro|US_DEBUG
mdefine_line|#define US_DEBUG(x)
macro_line|#endif
multiline_comment|/* bit set if input */
r_extern
r_int
r_char
id|us_direction
(braket
l_int|256
op_div
l_int|8
)braket
suffix:semicolon
DECL|macro|US_DIRECTION
mdefine_line|#define US_DIRECTION(x) ((us_direction[x&gt;&gt;3] &gt;&gt; (x &amp; 7)) &amp; 1)
multiline_comment|/* Sub Classes */
DECL|macro|US_SC_RBC
mdefine_line|#define US_SC_RBC&t;1&t;&t;/* Typically, flash devices */
DECL|macro|US_SC_8020
mdefine_line|#define US_SC_8020&t;2&t;&t;/* CD-ROM */
DECL|macro|US_SC_QIC
mdefine_line|#define US_SC_QIC&t;3&t;&t;/* QIC-157 Tapes */
DECL|macro|US_SC_UFI
mdefine_line|#define US_SC_UFI&t;4&t;&t;/* Floppy */
DECL|macro|US_SC_8070
mdefine_line|#define US_SC_8070&t;5&t;&t;/* Removable media */
DECL|macro|US_SC_SCSI
mdefine_line|#define US_SC_SCSI&t;6&t;&t;/* Transparent */
DECL|macro|US_SC_MIN
mdefine_line|#define US_SC_MIN&t;US_SC_RBC
DECL|macro|US_SC_MAX
mdefine_line|#define US_SC_MAX&t;US_SC_SCSI
multiline_comment|/* Protocols */
DECL|macro|US_PR_CB
mdefine_line|#define US_PR_CB&t;1&t;&t;/* Control/Bulk w/o interrupt */
DECL|macro|US_PR_CBI
mdefine_line|#define US_PR_CBI&t;0&t;&t;/* Control/Bulk/Interrupt */
DECL|macro|US_PR_BULK
mdefine_line|#define US_PR_BULK&t;0x50&t;&t;/* bulk only */
multiline_comment|/*&n; * Bulk only data structures (Zip 100, for example)&n; */
multiline_comment|/* command block wrapper */
DECL|struct|bulk_cb_wrap
r_struct
id|bulk_cb_wrap
(brace
DECL|member|Signature
id|__u32
id|Signature
suffix:semicolon
multiline_comment|/* contains &squot;USBC&squot; */
DECL|member|Tag
id|__u32
id|Tag
suffix:semicolon
multiline_comment|/* unique per command id */
DECL|member|DataTransferLength
id|__u32
id|DataTransferLength
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|Flags
id|__u8
id|Flags
suffix:semicolon
multiline_comment|/* direction in bit 0 */
DECL|member|Lun
id|__u8
id|Lun
suffix:semicolon
multiline_comment|/* LUN normally 0 */
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
multiline_comment|/* of of the CDB */
DECL|member|CDB
id|__u8
id|CDB
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* max command */
)brace
suffix:semicolon
DECL|macro|US_BULK_CB_WRAP_LEN
mdefine_line|#define US_BULK_CB_WRAP_LEN &t;31
DECL|macro|US_BULK_CB_SIGN
mdefine_line|#define US_BULK_CB_SIGN&t;&t;0x43425355
DECL|macro|US_BULK_FLAG_IN
mdefine_line|#define US_BULK_FLAG_IN&t;&t;1
DECL|macro|US_BULK_FLAG_OUT
mdefine_line|#define US_BULK_FLAG_OUT&t;0
multiline_comment|/* command status wrapper */
DECL|struct|bulk_cs_wrap
r_struct
id|bulk_cs_wrap
(brace
DECL|member|Signature
id|__u32
id|Signature
suffix:semicolon
multiline_comment|/* should = &squot;USBS&squot; */
DECL|member|Tag
id|__u32
id|Tag
suffix:semicolon
multiline_comment|/* same as original command */
DECL|member|Residue
id|__u32
id|Residue
suffix:semicolon
multiline_comment|/* amount not transferred */
DECL|member|Status
id|__u8
id|Status
suffix:semicolon
multiline_comment|/* see below */
DECL|member|Filler
id|__u8
id|Filler
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|US_BULK_CS_WRAP_LEN
mdefine_line|#define US_BULK_CS_WRAP_LEN&t;13
DECL|macro|US_BULK_CS_SIGN
mdefine_line|#define US_BULK_CS_SIGN&t;&t;0x53425355
DECL|macro|US_BULK_STAT_OK
mdefine_line|#define US_BULK_STAT_OK&t;&t;0
DECL|macro|US_BULK_STAT_FAIL
mdefine_line|#define US_BULK_STAT_FAIL&t;1
DECL|macro|US_BULK_STAT_PHASE
mdefine_line|#define US_BULK_STAT_PHASE&t;2
DECL|macro|US_BULK_RESET
mdefine_line|#define US_BULK_RESET&t;&t;0xff
DECL|macro|US_BULK_RESET_SOFT
mdefine_line|#define US_BULK_RESET_SOFT&t;1
DECL|macro|US_BULK_RESET_HARD
mdefine_line|#define US_BULK_RESET_HARD&t;0
multiline_comment|/*&n; * us_bulk_transfer() return codes&n; */
DECL|macro|US_BULK_TRANSFER_GOOD
mdefine_line|#define US_BULK_TRANSFER_GOOD   0
DECL|macro|US_BULK_TRANSFER_SHORT
mdefine_line|#define US_BULK_TRANSFER_SHORT  1
DECL|macro|US_BULK_TRANSFER_FAILED
mdefine_line|#define US_BULK_TRANSFER_FAILED 2
multiline_comment|/*&n; * Transport return codes&n; */
DECL|macro|USB_STOR_TRANSPORT_GOOD
mdefine_line|#define USB_STOR_TRANSPORT_GOOD    0   /* Transport good, command good     */
DECL|macro|USB_STOR_TRANSPORT_FAILED
mdefine_line|#define USB_STOR_TRANSPORT_FAILED  1   /* Transport good, command failed   */
DECL|macro|USB_STOR_TRANSPORT_ERROR
mdefine_line|#define USB_STOR_TRANSPORT_ERROR   2   /* Transport bad (i.e. device dead) */
multiline_comment|/*&n; * CBI accept device specific command&n; */
DECL|macro|US_CBI_ADSC
mdefine_line|#define US_CBI_ADSC&t;&t;0
multiline_comment|/* &n; * GUID definitions&n; */
DECL|macro|GUID
mdefine_line|#define GUID(x) __u32 x[3]
DECL|macro|GUID_EQUAL
mdefine_line|#define GUID_EQUAL(x, y) (x[0] == y[0] &amp;&amp; x[1] == y[1] &amp;&amp; x[2] == y[2])
DECL|macro|GUID_CLEAR
mdefine_line|#define GUID_CLEAR(x) x[0] = x[1] = x[2] = 0;
DECL|macro|GUID_NONE
mdefine_line|#define GUID_NONE(x) (!x[0] &amp;&amp; !x[1] &amp;&amp; !x[2])
DECL|macro|GUID_FORMAT
mdefine_line|#define GUID_FORMAT &quot;%08x%08x%08x&quot;
DECL|macro|GUID_ARGS
mdefine_line|#define GUID_ARGS(x) x[0], x[1], x[2]
DECL|function|make_guid
r_static
r_inline
r_void
id|make_guid
c_func
(paren
id|__u32
op_star
id|pg
comma
id|__u16
id|vendor
comma
id|__u16
id|product
comma
r_char
op_star
id|serial
)paren
(brace
id|pg
(braket
l_int|0
)braket
op_assign
(paren
id|vendor
op_lshift
l_int|16
)paren
op_or
id|product
suffix:semicolon
id|pg
(braket
l_int|1
)braket
op_assign
id|pg
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|serial
)paren
(brace
id|pg
(braket
l_int|1
)braket
op_lshift_assign
l_int|4
suffix:semicolon
id|pg
(braket
l_int|1
)braket
op_or_assign
id|pg
(braket
l_int|2
)braket
op_rshift
l_int|28
suffix:semicolon
id|pg
(braket
l_int|2
)braket
op_lshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_star
id|serial
op_ge
l_char|&squot;a&squot;
)paren
op_star
id|serial
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
id|pg
(braket
l_int|2
)braket
op_or_assign
(paren
op_star
id|serial
op_le
l_char|&squot;9&squot;
op_logical_and
op_star
id|serial
op_ge
l_char|&squot;0&squot;
)paren
ques
c_cond
op_star
id|serial
op_minus
l_char|&squot;0&squot;
suffix:colon
op_star
id|serial
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
id|serial
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* Flag definitions */
DECL|macro|US_FL_IP_STATUS
mdefine_line|#define US_FL_IP_STATUS&t;      0x00000001 /* status uses interrupt           */
DECL|macro|US_FL_FIXED_COMMAND
mdefine_line|#define US_FL_FIXED_COMMAND   0x00000002 /* expand commands to fixed size   */
DECL|macro|US_FL_MODE_XLATE
mdefine_line|#define US_FL_MODE_XLATE      0x00000004 /* translate _6 to _10 comands for&n;&t;&t;&t;&t;&t;            Win/MacOS compatibility */
DECL|macro|US_FL_CBI_AS_CB
mdefine_line|#define US_FL_CBI_AS_CB       0x00000008 /* treat a CBI dev as a CB dev     */
eof
