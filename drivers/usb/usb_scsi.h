multiline_comment|/* Driver for USB scsi - include file&n; * &n; * (C) Michael Gee (michael@linuxspecific.com) 1999&n; *&n; * This driver is scitzoid  - it make a USB scanner appear as both a SCSI device&n; * and a character device. The latter is only available if the device has an&n; * interrupt endpoint, and is used specifically to receive interrupt events.&n; *&n; * In order to support various &squot;strange&squot; scanners, this module supports plug in&n; * device specific filter modules, which can do their own thing when required.&n; *&n; */
DECL|macro|USB_SCSI
mdefine_line|#define USB_SCSI &quot;usbscsi: &quot;
r_extern
r_int
id|usbscsi_debug
suffix:semicolon
macro_line|#ifdef CONFIG_USB_SCSI_DEBUG
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
mdefine_line|#define US_DEBUGP(x...) { if(usbscsi_debug) printk( KERN_DEBUG USB_SCSI ## x ); }
DECL|macro|US_DEBUGPX
mdefine_line|#define US_DEBUGPX(x...) { if(usbscsi_debug) printk( ## x ); }
DECL|macro|US_DEBUG
mdefine_line|#define US_DEBUG(x)  { if(usbscsi_debug) x; }
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
DECL|macro|US_PR_ZIP
mdefine_line|#define US_PR_ZIP&t;0x50&t;&t;/* bulk only */
multiline_comment|/* #define US_PR_BULK&t;?? */
multiline_comment|/*&n; * Bulk only data structures (Zip 100, for example)&n; */
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
mdefine_line|#define US_BULK_CS_WRAP_LEN&t;31
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
multiline_comment|/*&n; * CBI style&n; */
DECL|macro|US_CBI_ADSC
mdefine_line|#define US_CBI_ADSC&t;&t;0
multiline_comment|/*&n; * Filter device definitions&n; */
DECL|struct|usb_scsi_filter
r_struct
id|usb_scsi_filter
(brace
DECL|member|next
r_struct
id|usb_scsi_filter
op_star
id|next
suffix:semicolon
multiline_comment|/* usb_scsi driver only */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* not really required */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Filter flags */
DECL|member|probe
r_void
op_star
(paren
op_star
id|probe
)paren
(paren
r_struct
id|usb_device
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/* probe device */
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* device gone */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_void
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/* all commands */
)brace
suffix:semicolon
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
mdefine_line|#define US_FL_IP_STATUS&t;&t;0x00000001&t;&t;/* status uses interrupt */
DECL|macro|US_FL_FIXED_COMMAND
mdefine_line|#define US_FL_FIXED_COMMAND&t;0x00000002&t;&t;/* expand commands to fixed size */
multiline_comment|/*&n; * Called by filters to register/unregister the mini driver&n; *&n; * WARNING - the supplied probe function may be called before exiting this fn&n; */
r_int
id|usb_scsi_register
c_func
(paren
r_struct
id|usb_scsi_filter
op_star
)paren
suffix:semicolon
r_void
id|usb_scsi_deregister
c_func
(paren
r_struct
id|usb_scsi_filter
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB_HP4100
r_int
id|hp4100_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
