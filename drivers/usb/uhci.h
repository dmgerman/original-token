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
DECL|struct|uhci_qh
r_struct
id|uhci_qh
(brace
DECL|member|link
r_int
r_int
id|link
suffix:semicolon
multiline_comment|/* Next queue */
DECL|member|element
r_int
r_int
id|element
suffix:semicolon
multiline_comment|/* Queue element pointer */
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
multiline_comment|/* Inuse? */
DECL|member|skel
r_struct
id|uhci_qh
op_star
id|skel
suffix:semicolon
multiline_comment|/* Skeleton head */
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
r_int
r_int
id|frame
(braket
l_int|1024
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
multiline_comment|/*&n; * The documentation says &quot;4 words for hardware, 4 words for software&quot;.&n; *&n; * That&squot;s silly, the hardware doesn&squot;t care. The hardware only cares that&n; * the hardware words are 16-byte aligned, and we can have any amount of&n; * sw space after the TD entry as far as I can tell.&n; *&n; * But let&squot;s just go with the documentation, at least for 32-bit machines.&n; * On 64-bit machines we probably want to take advantage of the fact that&n; * hw doesn&squot;t really care about the size of the sw-only area.&n; *&n; * Alas, not anymore, we have more than 4 words of software, woops&n; */
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
DECL|member|backptr
r_int
r_int
op_star
id|backptr
suffix:semicolon
multiline_comment|/* Where to remove this from.. */
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|inuse
r_int
id|inuse
suffix:semicolon
multiline_comment|/* Inuse? */
DECL|member|qh
r_struct
id|uhci_qh
op_star
id|qh
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Note the alignment requirements of the entries&n; *&n; * Each UHCI device has pre-allocated QH and TD entries.&n; * You can use more than the pre-allocated ones, but I&n; * don&squot;t see you usually needing to.&n; */
r_struct
id|uhci
suffix:semicolon
DECL|macro|UHCI_MAXTD
mdefine_line|#define UHCI_MAXTD 32
DECL|macro|UHCI_MAXQH
mdefine_line|#define UHCI_MAXQH&t;16
multiline_comment|/* The usb device part must be first! */
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
DECL|member|uhci
r_struct
id|uhci
op_star
id|uhci
suffix:semicolon
DECL|member|qh
r_struct
id|uhci_qh
id|qh
(braket
id|UHCI_MAXQH
)braket
suffix:semicolon
multiline_comment|/* These are the &quot;common&quot; qh&squot;s for each device */
DECL|member|td
r_struct
id|uhci_td
id|td
(braket
id|UHCI_MAXTD
)braket
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
multiline_comment|/*&n; * The root hub pre-allocated QH&squot;s and TD&squot;s have&n; * some special global uses..&n; */
DECL|macro|control_td
mdefine_line|#define control_td&t;td&t;&t;/* Td&squot;s 0-30 */
multiline_comment|/* This is only for the root hub&squot;s TD list */
DECL|macro|tick_td
mdefine_line|#define tick_td&t;&t;td[31]
multiline_comment|/*&n; * There are various standard queues. We set up several different&n; * queues for each of the three basic queue types: interrupt,&n; * control, and bulk.&n; *&n; *  - There are various different interrupt latencies: ranging from&n; *    every other USB frame (2 ms apart) to every 256 USB frames (ie&n; *    256 ms apart). Make your choice according to how obnoxious you&n; *    want to be on the wire, vs how critical latency is for you.&n; *  - The control list is done every frame.&n; *  - There are 4 bulk lists, so that up to four devices can have a&n; *    bulk list of their own and when run concurrently all four lists&n; *    will be be serviced.&n; *&n; * This is a bit misleading, there are various interrupt latencies, but they&n; * vary a bit, interrupt2 isn&squot;t exactly 2ms, it can vary up to 4ms since the&n; * other queues can &quot;override&quot; it. interrupt4 can vary up to 8ms, etc. Minor&n; * problem&n; *&n; * In the case of the root hub, these QH&squot;s are just head&squot;s of qh&squot;s. Don&squot;t&n; * be scared, it kinda makes sense. Look at this wonderful picture care of&n; * Linus:&n; *&n; *  generic-iso-QH  -&gt;  dev1-iso-QH  -&gt;  generic-irq-QH  -&gt;  dev1-irq-QH  -&gt; ...&n; *       |                       |                  |                   |&n; *      End          dev1-iso-TD1          End            dev1-irq-TD1&n; *                       |&n; *                   dev1-iso-TD2&n; *                       |&n; *                      ....&n; *&n; * This may vary a bit (the UHCI docs don&squot;t explicitly say you can put iso&n; * transfers in QH&squot;s and all of their pictures don&squot;t have that either) but&n; * other than that, that is what we&squot;re doing now&n; *&n; * To keep with Linus&squot; nomenclature, this is called the qh skeleton. These&n; * labels (below) are only signficant to the root hub&squot;s qh&squot;s&n; */
DECL|macro|skel_iso_qh
mdefine_line|#define skel_iso_qh&t;&t;qh[0]
DECL|macro|skel_int2_qh
mdefine_line|#define skel_int2_qh&t;&t;qh[1]
DECL|macro|skel_int4_qh
mdefine_line|#define skel_int4_qh&t;&t;qh[2]
DECL|macro|skel_int8_qh
mdefine_line|#define skel_int8_qh&t;&t;qh[3]
DECL|macro|skel_int16_qh
mdefine_line|#define skel_int16_qh&t;&t;qh[4]
DECL|macro|skel_int32_qh
mdefine_line|#define skel_int32_qh&t;&t;qh[5]
DECL|macro|skel_int64_qh
mdefine_line|#define skel_int64_qh&t;&t;qh[6]
DECL|macro|skel_int128_qh
mdefine_line|#define skel_int128_qh&t;&t;qh[7]
DECL|macro|skel_int256_qh
mdefine_line|#define skel_int256_qh&t;&t;qh[8]
DECL|macro|skel_control_qh
mdefine_line|#define skel_control_qh&t;&t;qh[9]
DECL|macro|skel_bulk0_qh
mdefine_line|#define skel_bulk0_qh&t;&t;qh[10]
DECL|macro|skel_bulk1_qh
mdefine_line|#define skel_bulk1_qh&t;&t;qh[11]
DECL|macro|skel_bulk2_qh
mdefine_line|#define skel_bulk2_qh&t;&t;qh[12]
DECL|macro|skel_bulk3_qh
mdefine_line|#define skel_bulk3_qh&t;&t;qh[13]
multiline_comment|/*&n; * These are significant to the devices allocation of QH&squot;s&n; */
macro_line|#if 0
mdefine_line|#define iso_qh&t;&t;&t;qh[0]
mdefine_line|#define int_qh&t;&t;&t;qh[1]&t;/* We have 2 &quot;common&quot; interrupt QH&squot;s */
mdefine_line|#define control_qh&t;&t;qh[3]
mdefine_line|#define bulk_qh&t;&t;&t;qh[4]&t;/* We have 4 &quot;common&quot; bulk QH&squot;s */
mdefine_line|#define extra_qh&t;&t;qh[8]&t;/* The rest, anything goes */
macro_line|#endif
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
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
macro_line|#if 0
multiline_comment|/* These are &quot;standard&quot; QH&squot;s for the entire bus */
r_struct
id|uhci_qh
id|qh
(braket
id|UHCI_MAXQH
)braket
suffix:semicolon
macro_line|#endif
DECL|member|root_hub
r_struct
id|uhci_device
op_star
id|root_hub
suffix:semicolon
multiline_comment|/* Root hub device descriptor.. */
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
id|show_td
c_func
(paren
r_struct
id|uhci_td
op_star
id|td
)paren
suffix:semicolon
r_void
id|show_status
c_func
(paren
r_struct
id|uhci
op_star
id|uhci
)paren
suffix:semicolon
r_void
id|show_queues
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
