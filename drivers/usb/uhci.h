macro_line|#ifndef __LINUX_UHCI_H
DECL|macro|__LINUX_UHCI_H
mdefine_line|#define __LINUX_UHCI_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;usb.h&quot;
multiline_comment|/*&n; * Universal Host Controller Interface data structures and defines&n; */
multiline_comment|/* Command register */
DECL|macro|USBCMD
mdefine_line|#define USBCMD&t;&t;0
DECL|macro|USBCMD_RS
mdefine_line|#define   USBCMD_RS&t;&t;0x0001&t;/* Run/Stop */
DECL|macro|USBCMD_HCRESET
mdefine_line|#define   USBCMD_HCRESET&t;0x0002&t;/* Host reset */
DECL|macro|USBCMD_GRESET
mdefine_line|#define   USBCMD_GRESET&t;&t;0x0004&t;/* Global reset */
DECL|macro|USBCMD_EGSM
mdefine_line|#define   USBCMD_EGSM&t;&t;0x0008&t;/* Global Suspend Mode */
DECL|macro|USBCMD_FGR
mdefine_line|#define   USBCMD_FGR&t;&t;0x0010&t;/* Force Global Resume */
DECL|macro|USBCMD_SWDBG
mdefine_line|#define   USBCMD_SWDBG&t;&t;0x0020&t;/* SW Debug mode */
DECL|macro|USBCMD_CF
mdefine_line|#define   USBCMD_CF&t;&t;0x0040&t;/* Config Flag (sw only) */
DECL|macro|USBCMD_MAXP
mdefine_line|#define   USBCMD_MAXP&t;&t;0x0080&t;/* Max Packet (0 = 32, 1 = 64) */
multiline_comment|/* Status register */
DECL|macro|USBSTS
mdefine_line|#define USBSTS&t;&t;2
DECL|macro|USBSTS_USBINT
mdefine_line|#define   USBSTS_USBINT&t;&t;0x0001&t;/* Interrupt due to IOC */
DECL|macro|USBSTS_ERROR
mdefine_line|#define   USBSTS_ERROR&t;&t;0x0002&t;/* Interrupt due to error */
DECL|macro|USBSTS_RD
mdefine_line|#define   USBSTS_RD&t;&t;0x0004&t;/* Resume Detect */
DECL|macro|USBSTS_HSE
mdefine_line|#define   USBSTS_HSE&t;&t;0x0008&t;/* Host System Error - basically PCI problems */
DECL|macro|USBSTS_HCPE
mdefine_line|#define   USBSTS_HCPE&t;&t;0x0010&t;/* Host Controller Process Error - the scripts were buggy */
DECL|macro|USBSTS_HCH
mdefine_line|#define   USBSTS_HCH&t;&t;0x0020&t;/* HC Halted */
multiline_comment|/* Interrupt enable register */
DECL|macro|USBINTR
mdefine_line|#define USBINTR&t;&t;4
DECL|macro|USBINTR_TIMEOUT
mdefine_line|#define   USBINTR_TIMEOUT&t;0x0001&t;/* Timeout/CRC error enable */
DECL|macro|USBINTR_RESUME
mdefine_line|#define   USBINTR_RESUME&t;0x0002&t;/* Resume interrupt enable */
DECL|macro|USBINTR_IOC
mdefine_line|#define   USBINTR_IOC&t;&t;0x0004&t;/* Interrupt On Complete enable */
DECL|macro|USBINTR_SP
mdefine_line|#define   USBINTR_SP&t;&t;0x0008&t;/* Short packet interrupt enable */
DECL|macro|USBFRNUM
mdefine_line|#define USBFRNUM&t;6
DECL|macro|USBFLBASEADD
mdefine_line|#define USBFLBASEADD&t;8
DECL|macro|USBSOF
mdefine_line|#define USBSOF&t;&t;12
multiline_comment|/* USB port status and control registers */
DECL|macro|USBPORTSC1
mdefine_line|#define USBPORTSC1&t;16
DECL|macro|USBPORTSC2
mdefine_line|#define USBPORTSC2&t;18
DECL|macro|USBPORTSC_CCS
mdefine_line|#define   USBPORTSC_CCS&t;&t;0x0001&t;/* Current Connect Status (&quot;device present&quot;) */
DECL|macro|USBPORTSC_CSC
mdefine_line|#define   USBPORTSC_CSC&t;&t;0x0002&t;/* Connect Status Change */
DECL|macro|USBPORTSC_PE
mdefine_line|#define   USBPORTSC_PE&t;&t;0x0004&t;/* Port Enable */
DECL|macro|USBPORTSC_PEC
mdefine_line|#define   USBPORTSC_PEC&t;&t;0x0008&t;/* Port Enable Change */
DECL|macro|USBPORTSC_LS
mdefine_line|#define   USBPORTSC_LS&t;&t;0x0030&t;/* Line Status */
DECL|macro|USBPORTSC_RD
mdefine_line|#define   USBPORTSC_RD&t;&t;0x0040&t;/* Resume Detect */
DECL|macro|USBPORTSC_LSDA
mdefine_line|#define   USBPORTSC_LSDA&t;0x0100&t;/* Low Speed Device Attached */
DECL|macro|USBPORTSC_PR
mdefine_line|#define   USBPORTSC_PR&t;&t;0x0200&t;/* Port Reset */
DECL|macro|USBPORTSC_SUSP
mdefine_line|#define   USBPORTSC_SUSP&t;0x1000&t;/* Suspend */
multiline_comment|/* Legacy support register */
DECL|macro|USBLEGSUP
mdefine_line|#define USBLEGSUP 0xc0
DECL|macro|USBLEGSUP_DEFAULT
mdefine_line|#define USBLEGSUP_DEFAULT 0x2000 /* only PIRQ enable set */
DECL|macro|UHCI_NULL_DATA_SIZE
mdefine_line|#define UHCI_NULL_DATA_SIZE&t;0x7ff&t;/* for UHCI controller TD */
DECL|macro|UHCI_PTR_BITS
mdefine_line|#define UHCI_PTR_BITS&t;&t;0x000F
DECL|macro|UHCI_PTR_TERM
mdefine_line|#define UHCI_PTR_TERM&t;&t;0x0001
DECL|macro|UHCI_PTR_QH
mdefine_line|#define UHCI_PTR_QH&t;&t;0x0002
DECL|macro|UHCI_PTR_DEPTH
mdefine_line|#define UHCI_PTR_DEPTH&t;&t;0x0004
DECL|macro|UHCI_NUMFRAMES
mdefine_line|#define UHCI_NUMFRAMES&t;&t;1024&t;/* in the frame list [array] */
DECL|macro|UHCI_MAX_SOF_NUMBER
mdefine_line|#define UHCI_MAX_SOF_NUMBER&t;2047&t;/* in an SOF packet */
DECL|macro|CAN_SCHEDULE_FRAMES
mdefine_line|#define CAN_SCHEDULE_FRAMES&t;1000&t;/* how far future frames can be scheduled */
r_struct
id|uhci_td
suffix:semicolon
DECL|struct|uhci_qh
r_struct
id|uhci_qh
(brace
multiline_comment|/* Hardware fields */
DECL|member|link
id|__u32
id|link
suffix:semicolon
multiline_comment|/* Next queue */
DECL|member|element
id|__u32
id|element
suffix:semicolon
multiline_comment|/* Queue element pointer */
multiline_comment|/* Software fields */
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* Reference counting */
DECL|member|dev
r_struct
id|uhci_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* The owning device */
DECL|member|skel
r_struct
id|uhci_qh
op_star
id|skel
suffix:semicolon
multiline_comment|/* Skeleton head */
DECL|member|first
r_struct
id|uhci_td
op_star
id|first
suffix:semicolon
multiline_comment|/* First TD in the chain */
DECL|member|wakeup
id|wait_queue_head_t
id|wakeup
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|struct|uhci_framelist
r_struct
id|uhci_framelist
(brace
DECL|member|frame
id|__u32
id|frame
(braket
id|UHCI_NUMFRAMES
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|4096
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * for TD &lt;status&gt;:&n; */
DECL|macro|TD_CTRL_SPD
mdefine_line|#define TD_CTRL_SPD&t;&t;(1 &lt;&lt; 29)&t;/* Short Packet Detect */
DECL|macro|TD_CTRL_C_ERR_MASK
mdefine_line|#define TD_CTRL_C_ERR_MASK&t;(3 &lt;&lt; 27)&t;/* Error Counter bits */
DECL|macro|TD_CTRL_LS
mdefine_line|#define TD_CTRL_LS&t;&t;(1 &lt;&lt; 26)&t;/* Low Speed Device */
DECL|macro|TD_CTRL_IOS
mdefine_line|#define TD_CTRL_IOS&t;&t;(1 &lt;&lt; 25)&t;/* Isochronous Select */
DECL|macro|TD_CTRL_IOC
mdefine_line|#define TD_CTRL_IOC&t;&t;(1 &lt;&lt; 24)&t;/* Interrupt on Complete */
DECL|macro|TD_CTRL_ACTIVE
mdefine_line|#define TD_CTRL_ACTIVE&t;&t;(1 &lt;&lt; 23)&t;/* TD Active */
DECL|macro|TD_CTRL_STALLED
mdefine_line|#define TD_CTRL_STALLED&t;&t;(1 &lt;&lt; 22)&t;/* TD Stalled */
DECL|macro|TD_CTRL_DBUFERR
mdefine_line|#define TD_CTRL_DBUFERR&t;&t;(1 &lt;&lt; 21)&t;/* Data Buffer Error */
DECL|macro|TD_CTRL_BABBLE
mdefine_line|#define TD_CTRL_BABBLE&t;&t;(1 &lt;&lt; 20)&t;/* Babble Detected */
DECL|macro|TD_CTRL_NAK
mdefine_line|#define TD_CTRL_NAK&t;&t;(1 &lt;&lt; 19)&t;/* NAK Received */
DECL|macro|TD_CTRL_CRCTIMEO
mdefine_line|#define TD_CTRL_CRCTIMEO&t;(1 &lt;&lt; 18)&t;/* CRC/Time Out Error */
DECL|macro|TD_CTRL_BITSTUFF
mdefine_line|#define TD_CTRL_BITSTUFF&t;(1 &lt;&lt; 17)&t;/* Bit Stuff Error */
DECL|macro|TD_CTRL_ACTLEN_MASK
mdefine_line|#define TD_CTRL_ACTLEN_MASK&t;0x7ff&t;&t;/* actual length, encoded as n - 1 */
DECL|macro|TD_CTRL_ANY_ERROR
mdefine_line|#define TD_CTRL_ANY_ERROR&t;(TD_CTRL_STALLED | TD_CTRL_DBUFERR | &bslash;&n;&t;&t;&t;&t; TD_CTRL_BABBLE | TD_CTRL_CRCTIME | TD_CTRL_BITSTUFF)
DECL|macro|uhci_status_bits
mdefine_line|#define uhci_status_bits(ctrl_sts)&t;(ctrl_sts &amp; 0xFE0000)
DECL|macro|uhci_actual_length
mdefine_line|#define uhci_actual_length(ctrl_sts)&t;((ctrl_sts + 1) &amp; TD_CTRL_ACTLEN_MASK) /* 1-based */
DECL|macro|uhci_ptr_to_virt
mdefine_line|#define uhci_ptr_to_virt(x)&t;bus_to_virt(x &amp; ~UHCI_PTR_BITS)
multiline_comment|/*&n; * for TD &lt;flags&gt;:&n; */
DECL|macro|UHCI_TD_REMOVE
mdefine_line|#define UHCI_TD_REMOVE&t;&t;0x0001&t;&t;/* Remove when done */
multiline_comment|/*&n; * for TD &lt;info&gt;: (a.k.a. Token)&n; */
DECL|macro|TD_TOKEN_TOGGLE
mdefine_line|#define TD_TOKEN_TOGGLE&t;&t;19
DECL|macro|uhci_maxlen
mdefine_line|#define uhci_maxlen(token)&t;((token) &gt;&gt; 21)
DECL|macro|uhci_expected_length
mdefine_line|#define uhci_expected_length(info) (((info &gt;&gt; 21) + 1) &amp; TD_CTRL_ACTLEN_MASK) /* 1-based */
DECL|macro|uhci_toggle
mdefine_line|#define uhci_toggle(token)&t;(((token) &gt;&gt; TD_TOKEN_TOGGLE) &amp; 1)
DECL|macro|uhci_endpoint
mdefine_line|#define uhci_endpoint(token)&t;(((token) &gt;&gt; 15) &amp; 0xf)
DECL|macro|uhci_devaddr
mdefine_line|#define uhci_devaddr(token)&t;(((token) &gt;&gt; 8) &amp; 0x7f)
DECL|macro|uhci_devep
mdefine_line|#define uhci_devep(token)&t;(((token) &gt;&gt; 8) &amp; 0x7ff)
DECL|macro|uhci_packetid
mdefine_line|#define uhci_packetid(token)&t;((token) &amp; 0xff)
DECL|macro|uhci_packetout
mdefine_line|#define uhci_packetout(token)&t;(uhci_packetid(token) != USB_PID_IN)
DECL|macro|uhci_packetin
mdefine_line|#define uhci_packetin(token)&t;(uhci_packetid(token) == USB_PID_IN)
multiline_comment|/*&n; * The documentation says &quot;4 words for hardware, 4 words for software&quot;.&n; *&n; * That&squot;s silly, the hardware doesn&squot;t care. The hardware only cares that&n; * the hardware words are 16-byte aligned, and we can have any amount of&n; * sw space after the TD entry as far as I can tell.&n; *&n; * But let&squot;s just go with the documentation, at least for 32-bit machines.&n; * On 64-bit machines we probably want to take advantage of the fact that&n; * hw doesn&squot;t really care about the size of the sw-only area.&n; *&n; * Alas, not anymore, we have more than 4 words for software, woops&n; */
DECL|struct|uhci_td
r_struct
id|uhci_td
(brace
multiline_comment|/* Hardware fields */
DECL|member|link
id|__u32
id|link
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|info
id|__u32
id|info
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
multiline_comment|/* Software fields */
DECL|member|backptr
r_int
r_int
op_star
id|backptr
suffix:semicolon
multiline_comment|/* Where to remove this from.. */
DECL|member|irq_list
r_struct
id|list_head
id|irq_list
suffix:semicolon
multiline_comment|/* Active interrupt list.. */
DECL|member|completed
id|usb_device_irq
id|completed
suffix:semicolon
multiline_comment|/* Completion handler routine */
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* Reference counting */
DECL|member|dev
r_struct
id|uhci_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* The owning device */
DECL|member|qh
r_struct
id|uhci_qh
op_star
id|qh
suffix:semicolon
multiline_comment|/* QH this TD is a part of (ignored for Isochronous) */
DECL|member|pipetype
r_int
r_char
id|pipetype
suffix:semicolon
multiline_comment|/* Control, Bulk, Interrupt, Isoc */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Remove, etc */
DECL|member|isoc_td_number
r_int
id|isoc_td_number
suffix:semicolon
multiline_comment|/* 0-relative number within a usb_isoc_desc. */
DECL|member|bandwidth_alloc
r_int
id|bandwidth_alloc
suffix:semicolon
multiline_comment|/* in microsecs; used only for Interrupt&n;&t;&t;&t;&t;&t; * transfers, to return its bandwidth */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Note the alignment requirements of the entries&n; *&n; * Each UHCI device has pre-allocated QH and TD entries.&n; * You can use more than the pre-allocated ones, but I&n; * don&squot;t see you usually needing to.&n; */
r_struct
id|uhci
suffix:semicolon
multiline_comment|/* The usb device part must be first! Not anymore -jerdfelt */
DECL|struct|uhci_device
r_struct
id|uhci_device
(brace
DECL|member|usb
r_struct
id|usb_device
op_star
id|usb
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|uhci
r_struct
id|uhci
op_star
id|uhci
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|uhci_to_usb
mdefine_line|#define uhci_to_usb(uhci)&t;((uhci)-&gt;usb)
DECL|macro|usb_to_uhci
mdefine_line|#define usb_to_uhci(usb)&t;((struct uhci_device *)(usb)-&gt;hcpriv)
multiline_comment|/*&n; * There are various standard queues. We set up several different&n; * queues for each of the three basic queue types: interrupt,&n; * control, and bulk.&n; *&n; *  - There are various different interrupt latencies: ranging from&n; *    every other USB frame (2 ms apart) to every 256 USB frames (ie&n; *    256 ms apart). Make your choice according to how obnoxious you&n; *    want to be on the wire, vs how critical latency is for you.&n; *  - The control list is done every frame.&n; *  - There are 4 bulk lists, so that up to four devices can have a&n; *    bulk list of their own and when run concurrently all four lists&n; *    will be be serviced.&n; *&n; * This is a bit misleading, there are various interrupt latencies, but they&n; * vary a bit, interrupt2 isn&squot;t exactly 2ms, it can vary up to 4ms since the&n; * other queues can &quot;override&quot; it. interrupt4 can vary up to 8ms, etc. Minor&n; * problem&n; *&n; * In the case of the root hub, these QH&squot;s are just head&squot;s of qh&squot;s. Don&squot;t&n; * be scared, it kinda makes sense. Look at this wonderful picture care of&n; * Linus:&n; *&n; *  generic-  -&gt;  dev1-  -&gt;  generic-  -&gt;  dev1-  -&gt;  control-  -&gt;  bulk- -&gt; ...&n; *   iso-QH      iso-QH       irq-QH      irq-QH        QH           QH&n; *      |           |            |           |           |            |&n; *     End     dev1-iso-TD1     End     dev1-irq-TD1    ...          ... &n; *                  |&n; *             dev1-iso-TD2&n; *                  |&n; *                ....&n; *&n; * This may vary a bit (the UHCI docs don&squot;t explicitly say you can put iso&n; * transfers in QH&squot;s and all of their pictures don&squot;t have that either) but&n; * other than that, that is what we&squot;re doing now&n; *&n; * And now we don&squot;t put Iso transfers in QH&squot;s, so we don&squot;t waste one on it&n; * --jerdfelt&n; *&n; * To keep with Linus&squot; nomenclature, this is called the QH skeleton. These&n; * labels (below) are only signficant to the root hub&squot;s QH&squot;s&n; */
DECL|macro|UHCI_NUM_SKELQH
mdefine_line|#define UHCI_NUM_SKELQH&t;&t;11
DECL|macro|skel_int1_qh
mdefine_line|#define skel_int1_qh&t;&t;skelqh[0]
DECL|macro|skel_int2_qh
mdefine_line|#define skel_int2_qh&t;&t;skelqh[1]
DECL|macro|skel_int4_qh
mdefine_line|#define skel_int4_qh&t;&t;skelqh[2]
DECL|macro|skel_int8_qh
mdefine_line|#define skel_int8_qh&t;&t;skelqh[3]
DECL|macro|skel_int16_qh
mdefine_line|#define skel_int16_qh&t;&t;skelqh[4]
DECL|macro|skel_int32_qh
mdefine_line|#define skel_int32_qh&t;&t;skelqh[5]
DECL|macro|skel_int64_qh
mdefine_line|#define skel_int64_qh&t;&t;skelqh[6]
DECL|macro|skel_int128_qh
mdefine_line|#define skel_int128_qh&t;&t;skelqh[7]
DECL|macro|skel_int256_qh
mdefine_line|#define skel_int256_qh&t;&t;skelqh[8]
DECL|macro|skel_control_qh
mdefine_line|#define skel_control_qh&t;&t;skelqh[9]
DECL|macro|skel_bulk_qh
mdefine_line|#define skel_bulk_qh&t;&t;skelqh[10]
multiline_comment|/*&n; * Search tree for determining where &lt;interval&gt; fits in the&n; * skelqh[] skeleton.&n; *&n; * An interrupt request should be placed into the slowest skelqh[]&n; * which meets the interval/period/frequency requirement.&n; * An interrupt request is allowed to be faster than &lt;interval&gt; but not slower.&n; *&n; * For a given &lt;interval&gt;, this function returns the appropriate/matching&n; * skelqh[] index value.&n; *&n; * NOTE: For UHCI, we don&squot;t really need int256_qh since the maximum interval&n; * is 255 ms.  However, we do need an int1_qh since 1 is a valid interval&n; * and we should meet that frequency when requested to do so.&n; * This will require some change(s) to the UHCI skeleton.&n; */
DECL|function|__interval_to_skel
r_static
r_inline
r_int
id|__interval_to_skel
c_func
(paren
r_int
id|interval
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|2
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* int1 for 0-1 ms */
)brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* int2 for 2-3 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|8
)paren
(brace
r_return
l_int|2
suffix:semicolon
multiline_comment|/* int4 for 4-7 ms */
)brace
r_return
l_int|3
suffix:semicolon
multiline_comment|/* int8 for 8-15 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|64
)paren
(brace
r_if
c_cond
(paren
id|interval
OL
l_int|32
)paren
(brace
r_return
l_int|4
suffix:semicolon
multiline_comment|/* int16 for 16-31 ms */
)brace
r_return
l_int|5
suffix:semicolon
multiline_comment|/* int32 for 32-63 ms */
)brace
r_if
c_cond
(paren
id|interval
OL
l_int|128
)paren
r_return
l_int|6
suffix:semicolon
multiline_comment|/* int64 for 64-127 ms */
r_return
l_int|7
suffix:semicolon
multiline_comment|/* int128 for 128-255 ms (Max.) */
)brace
multiline_comment|/*&n; * This describes the full uhci information.&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs.&n; */
DECL|struct|uhci
r_struct
id|uhci
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|io_addr
r_int
r_int
id|io_addr
suffix:semicolon
DECL|member|io_size
r_int
r_int
id|io_size
suffix:semicolon
DECL|member|control_pid
r_int
id|control_pid
suffix:semicolon
DECL|member|control_running
r_int
id|control_running
suffix:semicolon
DECL|member|control_continue
r_int
id|control_continue
suffix:semicolon
DECL|member|uhci_list
r_struct
id|list_head
id|uhci_list
suffix:semicolon
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
DECL|member|skelqh
r_struct
id|uhci_qh
id|skelqh
(braket
id|UHCI_NUM_SKELQH
)braket
suffix:semicolon
multiline_comment|/* Skeleton QH&squot;s */
DECL|member|fl
r_struct
id|uhci_framelist
op_star
id|fl
suffix:semicolon
multiline_comment|/* Frame list */
DECL|member|interrupt_list
r_struct
id|list_head
id|interrupt_list
suffix:semicolon
multiline_comment|/* List of interrupt-active TD&squot;s for this uhci */
DECL|member|ticktd
r_struct
id|uhci_td
op_star
id|ticktd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* needed for the debugging code */
r_struct
id|uhci_td
op_star
id|uhci_link_to_td
c_func
(paren
r_int
r_int
id|element
)paren
suffix:semicolon
multiline_comment|/* Debugging code */
r_void
id|uhci_show_td
c_func
(paren
r_struct
id|uhci_td
op_star
id|td
)paren
suffix:semicolon
r_void
id|uhci_show_status
c_func
(paren
r_struct
id|uhci
op_star
id|uhci
)paren
suffix:semicolon
r_void
id|uhci_show_queue
c_func
(paren
r_struct
id|uhci_qh
op_star
id|qh
)paren
suffix:semicolon
r_void
id|uhci_show_queues
c_func
(paren
r_struct
id|uhci
op_star
id|uhci
)paren
suffix:semicolon
macro_line|#endif
eof
