multiline_comment|/*&n; * URB OHCI HCD (Host Controller Driver) for USB.&n; * &n; * (C) Copyright 1999 Roman Weissgaerber &lt;weissg@vienna.at&gt;&n; * (C) Copyright 2000 David Brownell &lt;david-b@pacbell.net&gt;&n; * &n; * usb-ohci.h&n; */
DECL|variable|cc_to_error
r_static
r_int
id|cc_to_error
(braket
l_int|16
)braket
op_assign
(brace
multiline_comment|/* mapping of the OHCI CC status to error codes */
multiline_comment|/* No  Error  */
id|USB_ST_NOERROR
comma
multiline_comment|/* CRC Error  */
id|USB_ST_CRC
comma
multiline_comment|/* Bit Stuff  */
id|USB_ST_BITSTUFF
comma
multiline_comment|/* Data Togg  */
id|USB_ST_CRC
comma
multiline_comment|/* Stall      */
id|USB_ST_STALL
comma
multiline_comment|/* DevNotResp */
id|USB_ST_NORESPONSE
comma
multiline_comment|/* PIDCheck   */
id|USB_ST_BITSTUFF
comma
multiline_comment|/* UnExpPID   */
id|USB_ST_BITSTUFF
comma
multiline_comment|/* DataOver   */
id|USB_ST_DATAOVERRUN
comma
multiline_comment|/* DataUnder  */
id|USB_ST_DATAUNDERRUN
comma
multiline_comment|/* reservd    */
id|USB_ST_NORESPONSE
comma
multiline_comment|/* reservd    */
id|USB_ST_NORESPONSE
comma
multiline_comment|/* BufferOver */
id|USB_ST_BUFFEROVERRUN
comma
multiline_comment|/* BuffUnder  */
id|USB_ST_BUFFERUNDERRUN
comma
multiline_comment|/* Not Access */
id|USB_ST_NORESPONSE
comma
multiline_comment|/* Not Access */
id|USB_ST_NORESPONSE
)brace
suffix:semicolon
multiline_comment|/* ED States */
DECL|macro|ED_NEW
mdefine_line|#define ED_NEW &t;&t;0x00
DECL|macro|ED_UNLINK
mdefine_line|#define ED_UNLINK &t;0x01
DECL|macro|ED_OPER
mdefine_line|#define ED_OPER&t;&t;0x02
DECL|macro|ED_DEL
mdefine_line|#define ED_DEL&t;&t;0x04
DECL|macro|ED_URB_DEL
mdefine_line|#define ED_URB_DEL  &t;0x08
multiline_comment|/* usb_ohci_ed */
DECL|struct|ed
r_typedef
r_struct
id|ed
(brace
DECL|member|hwINFO
id|__u32
id|hwINFO
suffix:semicolon
DECL|member|hwTailP
id|__u32
id|hwTailP
suffix:semicolon
DECL|member|hwHeadP
id|__u32
id|hwHeadP
suffix:semicolon
DECL|member|hwNextED
id|__u32
id|hwNextED
suffix:semicolon
DECL|member|ed_prev
r_struct
id|ed
op_star
id|ed_prev
suffix:semicolon
DECL|member|int_period
id|__u8
id|int_period
suffix:semicolon
DECL|member|int_branch
id|__u8
id|int_branch
suffix:semicolon
DECL|member|int_load
id|__u8
id|int_load
suffix:semicolon
DECL|member|int_interval
id|__u8
id|int_interval
suffix:semicolon
DECL|member|state
id|__u8
id|state
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|last_iso
id|__u16
id|last_iso
suffix:semicolon
DECL|member|ed_rm_list
r_struct
id|ed
op_star
id|ed_rm_list
suffix:semicolon
DECL|typedef|ed_t
)brace
id|ed_t
suffix:semicolon
multiline_comment|/* TD info field */
DECL|macro|TD_CC
mdefine_line|#define TD_CC       0xf0000000
DECL|macro|TD_CC_GET
mdefine_line|#define TD_CC_GET(td_p) ((td_p &gt;&gt;28) &amp; 0x0f)
DECL|macro|TD_CC_SET
mdefine_line|#define TD_CC_SET(td_p, cc) (td_p) = ((td_p) &amp; 0x0fffffff) | (((cc) &amp; 0x0f) &lt;&lt; 28)
DECL|macro|TD_EC
mdefine_line|#define TD_EC       0x0C000000
DECL|macro|TD_T
mdefine_line|#define TD_T        0x03000000
DECL|macro|TD_T_DATA0
mdefine_line|#define TD_T_DATA0  0x02000000
DECL|macro|TD_T_DATA1
mdefine_line|#define TD_T_DATA1  0x03000000
DECL|macro|TD_T_TOGGLE
mdefine_line|#define TD_T_TOGGLE 0x00000000
DECL|macro|TD_R
mdefine_line|#define TD_R        0x00040000
DECL|macro|TD_DI
mdefine_line|#define TD_DI       0x00E00000
DECL|macro|TD_DI_SET
mdefine_line|#define TD_DI_SET(X) (((X) &amp; 0x07)&lt;&lt; 21)
DECL|macro|TD_DP
mdefine_line|#define TD_DP       0x00180000
DECL|macro|TD_DP_SETUP
mdefine_line|#define TD_DP_SETUP 0x00000000
DECL|macro|TD_DP_IN
mdefine_line|#define TD_DP_IN    0x00100000
DECL|macro|TD_DP_OUT
mdefine_line|#define TD_DP_OUT   0x00080000
DECL|macro|TD_ISO
mdefine_line|#define TD_ISO&t;&t;0x00010000
DECL|macro|TD_DEL
mdefine_line|#define TD_DEL      0x00020000
multiline_comment|/* CC Codes */
DECL|macro|TD_CC_NOERROR
mdefine_line|#define TD_CC_NOERROR      0x00
DECL|macro|TD_CC_CRC
mdefine_line|#define TD_CC_CRC          0x01
DECL|macro|TD_CC_BITSTUFFING
mdefine_line|#define TD_CC_BITSTUFFING  0x02
DECL|macro|TD_CC_DATATOGGLEM
mdefine_line|#define TD_CC_DATATOGGLEM  0x03
DECL|macro|TD_CC_STALL
mdefine_line|#define TD_CC_STALL        0x04
DECL|macro|TD_DEVNOTRESP
mdefine_line|#define TD_DEVNOTRESP      0x05
DECL|macro|TD_PIDCHECKFAIL
mdefine_line|#define TD_PIDCHECKFAIL    0x06
DECL|macro|TD_UNEXPECTEDPID
mdefine_line|#define TD_UNEXPECTEDPID   0x07
DECL|macro|TD_DATAOVERRUN
mdefine_line|#define TD_DATAOVERRUN     0x08
DECL|macro|TD_DATAUNDERRUN
mdefine_line|#define TD_DATAUNDERRUN    0x09
DECL|macro|TD_BUFFEROVERRUN
mdefine_line|#define TD_BUFFEROVERRUN   0x0C
DECL|macro|TD_BUFFERUNDERRUN
mdefine_line|#define TD_BUFFERUNDERRUN  0x0D
DECL|macro|TD_NOTACCESSED
mdefine_line|#define TD_NOTACCESSED     0x0F
DECL|macro|MAXPSW
mdefine_line|#define MAXPSW 1
DECL|struct|td
r_typedef
r_struct
id|td
(brace
DECL|member|hwINFO
id|__u32
id|hwINFO
suffix:semicolon
DECL|member|hwCBP
id|__u32
id|hwCBP
suffix:semicolon
multiline_comment|/* Current Buffer Pointer */
DECL|member|hwNextTD
id|__u32
id|hwNextTD
suffix:semicolon
multiline_comment|/* Next TD Pointer */
DECL|member|hwBE
id|__u32
id|hwBE
suffix:semicolon
multiline_comment|/* Memory Buffer End Pointer */
DECL|member|hwPSW
id|__u16
id|hwPSW
(braket
id|MAXPSW
)braket
suffix:semicolon
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|index
id|__u8
id|index
suffix:semicolon
DECL|member|ed
r_struct
id|ed
op_star
id|ed
suffix:semicolon
DECL|member|next_dl_td
r_struct
id|td
op_star
id|next_dl_td
suffix:semicolon
DECL|member|urb
id|urb_t
op_star
id|urb
suffix:semicolon
DECL|typedef|td_t
)brace
id|td_t
suffix:semicolon
DECL|macro|OHCI_ED_SKIP
mdefine_line|#define OHCI_ED_SKIP&t;(1 &lt;&lt; 14)
multiline_comment|/*&n; * The HCCA (Host Controller Communications Area) is a 256 byte&n; * structure defined in the OHCI spec. that the host controller is&n; * told the base address of.  It must be 256-byte aligned.&n; */
DECL|macro|NUM_INTS
mdefine_line|#define NUM_INTS 32&t;/* part of the OHCI standard */
DECL|struct|ohci_hcca
r_struct
id|ohci_hcca
(brace
DECL|member|int_table
id|__u32
id|int_table
(braket
id|NUM_INTS
)braket
suffix:semicolon
multiline_comment|/* Interrupt ED table */
DECL|member|frame_no
id|__u16
id|frame_no
suffix:semicolon
multiline_comment|/* current frame number */
DECL|member|pad1
id|__u16
id|pad1
suffix:semicolon
multiline_comment|/* set to 0 on each frame_no change */
DECL|member|done_head
id|__u32
id|done_head
suffix:semicolon
multiline_comment|/* info returned for an interrupt */
DECL|member|reserved_for_hc
id|u8
id|reserved_for_hc
(braket
l_int|116
)braket
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Maximum number of root hub ports.  &n; */
DECL|macro|MAX_ROOT_PORTS
mdefine_line|#define MAX_ROOT_PORTS&t;15&t;/* maximum OHCI root hub ports */
multiline_comment|/*&n; * This is the structure of the OHCI controller&squot;s memory mapped I/O&n; * region.  This is Memory Mapped I/O.  You must use the readl() and&n; * writel() macros defined in asm/io.h to access these!!&n; */
DECL|struct|ohci_regs
r_struct
id|ohci_regs
(brace
multiline_comment|/* control and status registers */
DECL|member|revision
id|__u32
id|revision
suffix:semicolon
DECL|member|control
id|__u32
id|control
suffix:semicolon
DECL|member|cmdstatus
id|__u32
id|cmdstatus
suffix:semicolon
DECL|member|intrstatus
id|__u32
id|intrstatus
suffix:semicolon
DECL|member|intrenable
id|__u32
id|intrenable
suffix:semicolon
DECL|member|intrdisable
id|__u32
id|intrdisable
suffix:semicolon
multiline_comment|/* memory pointers */
DECL|member|hcca
id|__u32
id|hcca
suffix:semicolon
DECL|member|ed_periodcurrent
id|__u32
id|ed_periodcurrent
suffix:semicolon
DECL|member|ed_controlhead
id|__u32
id|ed_controlhead
suffix:semicolon
DECL|member|ed_controlcurrent
id|__u32
id|ed_controlcurrent
suffix:semicolon
DECL|member|ed_bulkhead
id|__u32
id|ed_bulkhead
suffix:semicolon
DECL|member|ed_bulkcurrent
id|__u32
id|ed_bulkcurrent
suffix:semicolon
DECL|member|donehead
id|__u32
id|donehead
suffix:semicolon
multiline_comment|/* frame counters */
DECL|member|fminterval
id|__u32
id|fminterval
suffix:semicolon
DECL|member|fmremaining
id|__u32
id|fmremaining
suffix:semicolon
DECL|member|fmnumber
id|__u32
id|fmnumber
suffix:semicolon
DECL|member|periodicstart
id|__u32
id|periodicstart
suffix:semicolon
DECL|member|lsthresh
id|__u32
id|lsthresh
suffix:semicolon
multiline_comment|/* Root hub ports */
DECL|struct|ohci_roothub_regs
r_struct
id|ohci_roothub_regs
(brace
DECL|member|a
id|__u32
id|a
suffix:semicolon
DECL|member|b
id|__u32
id|b
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|portstatus
id|__u32
id|portstatus
(braket
id|MAX_ROOT_PORTS
)braket
suffix:semicolon
DECL|member|roothub
)brace
id|roothub
suffix:semicolon
)brace
id|__attribute
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
multiline_comment|/* OHCI CONTROL AND STATUS REGISTER MASKS */
multiline_comment|/*&n; * HcControl (control) register masks&n; */
DECL|macro|OHCI_CTRL_CBSR
mdefine_line|#define OHCI_CTRL_CBSR&t;(3 &lt;&lt; 0)&t;/* control/bulk service ratio */
DECL|macro|OHCI_CTRL_PLE
mdefine_line|#define OHCI_CTRL_PLE&t;(1 &lt;&lt; 2)&t;/* periodic list enable */
DECL|macro|OHCI_CTRL_IE
mdefine_line|#define OHCI_CTRL_IE&t;(1 &lt;&lt; 3)&t;/* isochronous enable */
DECL|macro|OHCI_CTRL_CLE
mdefine_line|#define OHCI_CTRL_CLE&t;(1 &lt;&lt; 4)&t;/* control list enable */
DECL|macro|OHCI_CTRL_BLE
mdefine_line|#define OHCI_CTRL_BLE&t;(1 &lt;&lt; 5)&t;/* bulk list enable */
DECL|macro|OHCI_CTRL_HCFS
mdefine_line|#define OHCI_CTRL_HCFS&t;(3 &lt;&lt; 6)&t;/* host controller functional state */
DECL|macro|OHCI_CTRL_IR
mdefine_line|#define OHCI_CTRL_IR&t;(1 &lt;&lt; 8)&t;/* interrupt routing */
DECL|macro|OHCI_CTRL_RWC
mdefine_line|#define OHCI_CTRL_RWC&t;(1 &lt;&lt; 9)&t;/* remote wakeup connected */
DECL|macro|OHCI_CTRL_RWE
mdefine_line|#define OHCI_CTRL_RWE&t;(1 &lt;&lt; 10)&t;/* remote wakeup enable */
multiline_comment|/* pre-shifted values for HCFS */
DECL|macro|OHCI_USB_RESET
macro_line|#&t;define OHCI_USB_RESET&t;(0 &lt;&lt; 6)
DECL|macro|OHCI_USB_RESUME
macro_line|#&t;define OHCI_USB_RESUME&t;(1 &lt;&lt; 6)
DECL|macro|OHCI_USB_OPER
macro_line|#&t;define OHCI_USB_OPER&t;(2 &lt;&lt; 6)
DECL|macro|OHCI_USB_SUSPEND
macro_line|#&t;define OHCI_USB_SUSPEND&t;(3 &lt;&lt; 6)
multiline_comment|/*&n; * HcCommandStatus (cmdstatus) register masks&n; */
DECL|macro|OHCI_HCR
mdefine_line|#define OHCI_HCR&t;(1 &lt;&lt; 0)&t;/* host controller reset */
DECL|macro|OHCI_CLF
mdefine_line|#define OHCI_CLF  &t;(1 &lt;&lt; 1)&t;/* control list filled */
DECL|macro|OHCI_BLF
mdefine_line|#define OHCI_BLF  &t;(1 &lt;&lt; 2)&t;/* bulk list filled */
DECL|macro|OHCI_OCR
mdefine_line|#define OHCI_OCR  &t;(1 &lt;&lt; 3)&t;/* ownership change request */
DECL|macro|OHCI_SOC
mdefine_line|#define OHCI_SOC  &t;(3 &lt;&lt; 16)&t;/* scheduling overrun count */
multiline_comment|/*&n; * masks used with interrupt registers:&n; * HcInterruptStatus (intrstatus)&n; * HcInterruptEnable (intrenable)&n; * HcInterruptDisable (intrdisable)&n; */
DECL|macro|OHCI_INTR_SO
mdefine_line|#define OHCI_INTR_SO&t;(1 &lt;&lt; 0)&t;/* scheduling overrun */
DECL|macro|OHCI_INTR_WDH
mdefine_line|#define OHCI_INTR_WDH&t;(1 &lt;&lt; 1)&t;/* writeback of done_head */
DECL|macro|OHCI_INTR_SF
mdefine_line|#define OHCI_INTR_SF&t;(1 &lt;&lt; 2)&t;/* start frame */
DECL|macro|OHCI_INTR_RD
mdefine_line|#define OHCI_INTR_RD&t;(1 &lt;&lt; 3)&t;/* resume detect */
DECL|macro|OHCI_INTR_UE
mdefine_line|#define OHCI_INTR_UE&t;(1 &lt;&lt; 4)&t;/* unrecoverable error */
DECL|macro|OHCI_INTR_FNO
mdefine_line|#define OHCI_INTR_FNO&t;(1 &lt;&lt; 5)&t;/* frame number overflow */
DECL|macro|OHCI_INTR_RHSC
mdefine_line|#define OHCI_INTR_RHSC&t;(1 &lt;&lt; 6)&t;/* root hub status change */
DECL|macro|OHCI_INTR_OC
mdefine_line|#define OHCI_INTR_OC&t;(1 &lt;&lt; 30)&t;/* ownership change */
DECL|macro|OHCI_INTR_MIE
mdefine_line|#define OHCI_INTR_MIE&t;(1 &lt;&lt; 31)&t;/* master interrupt enable */
multiline_comment|/* Virtual Root HUB */
DECL|struct|virt_root_hub
r_struct
id|virt_root_hub
(brace
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
multiline_comment|/* Address of Root Hub endpoint */
DECL|member|urb
r_void
op_star
id|urb
suffix:semicolon
DECL|member|int_addr
r_void
op_star
id|int_addr
suffix:semicolon
DECL|member|send
r_int
id|send
suffix:semicolon
DECL|member|interval
r_int
id|interval
suffix:semicolon
DECL|member|rh_int_timer
r_struct
id|timer_list
id|rh_int_timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* USB HUB CONSTANTS (not OHCI-specific; see hub.h) */
multiline_comment|/* destination of request */
DECL|macro|RH_INTERFACE
mdefine_line|#define RH_INTERFACE               0x01
DECL|macro|RH_ENDPOINT
mdefine_line|#define RH_ENDPOINT                0x02
DECL|macro|RH_OTHER
mdefine_line|#define RH_OTHER                   0x03
DECL|macro|RH_CLASS
mdefine_line|#define RH_CLASS                   0x20
DECL|macro|RH_VENDOR
mdefine_line|#define RH_VENDOR                  0x40
multiline_comment|/* Requests: bRequest &lt;&lt; 8 | bmRequestType */
DECL|macro|RH_GET_STATUS
mdefine_line|#define RH_GET_STATUS           0x0080
DECL|macro|RH_CLEAR_FEATURE
mdefine_line|#define RH_CLEAR_FEATURE        0x0100
DECL|macro|RH_SET_FEATURE
mdefine_line|#define RH_SET_FEATURE          0x0300
DECL|macro|RH_SET_ADDRESS
mdefine_line|#define RH_SET_ADDRESS&t;&t;0x0500
DECL|macro|RH_GET_DESCRIPTOR
mdefine_line|#define RH_GET_DESCRIPTOR&t;0x0680
DECL|macro|RH_SET_DESCRIPTOR
mdefine_line|#define RH_SET_DESCRIPTOR       0x0700
DECL|macro|RH_GET_CONFIGURATION
mdefine_line|#define RH_GET_CONFIGURATION&t;0x0880
DECL|macro|RH_SET_CONFIGURATION
mdefine_line|#define RH_SET_CONFIGURATION&t;0x0900
DECL|macro|RH_GET_STATE
mdefine_line|#define RH_GET_STATE            0x0280
DECL|macro|RH_GET_INTERFACE
mdefine_line|#define RH_GET_INTERFACE        0x0A80
DECL|macro|RH_SET_INTERFACE
mdefine_line|#define RH_SET_INTERFACE        0x0B00
DECL|macro|RH_SYNC_FRAME
mdefine_line|#define RH_SYNC_FRAME           0x0C80
multiline_comment|/* Our Vendor Specific Request */
DECL|macro|RH_SET_EP
mdefine_line|#define RH_SET_EP               0x2000
multiline_comment|/* Hub port features */
DECL|macro|RH_PORT_CONNECTION
mdefine_line|#define RH_PORT_CONNECTION         0x00
DECL|macro|RH_PORT_ENABLE
mdefine_line|#define RH_PORT_ENABLE             0x01
DECL|macro|RH_PORT_SUSPEND
mdefine_line|#define RH_PORT_SUSPEND            0x02
DECL|macro|RH_PORT_OVER_CURRENT
mdefine_line|#define RH_PORT_OVER_CURRENT       0x03
DECL|macro|RH_PORT_RESET
mdefine_line|#define RH_PORT_RESET              0x04
DECL|macro|RH_PORT_POWER
mdefine_line|#define RH_PORT_POWER              0x08
DECL|macro|RH_PORT_LOW_SPEED
mdefine_line|#define RH_PORT_LOW_SPEED          0x09
DECL|macro|RH_C_PORT_CONNECTION
mdefine_line|#define RH_C_PORT_CONNECTION       0x10
DECL|macro|RH_C_PORT_ENABLE
mdefine_line|#define RH_C_PORT_ENABLE           0x11
DECL|macro|RH_C_PORT_SUSPEND
mdefine_line|#define RH_C_PORT_SUSPEND          0x12
DECL|macro|RH_C_PORT_OVER_CURRENT
mdefine_line|#define RH_C_PORT_OVER_CURRENT     0x13
DECL|macro|RH_C_PORT_RESET
mdefine_line|#define RH_C_PORT_RESET            0x14  
multiline_comment|/* Hub features */
DECL|macro|RH_C_HUB_LOCAL_POWER
mdefine_line|#define RH_C_HUB_LOCAL_POWER       0x00
DECL|macro|RH_C_HUB_OVER_CURRENT
mdefine_line|#define RH_C_HUB_OVER_CURRENT      0x01
DECL|macro|RH_DEVICE_REMOTE_WAKEUP
mdefine_line|#define RH_DEVICE_REMOTE_WAKEUP    0x00
DECL|macro|RH_ENDPOINT_STALL
mdefine_line|#define RH_ENDPOINT_STALL          0x01
DECL|macro|RH_ACK
mdefine_line|#define RH_ACK                     0x01
DECL|macro|RH_REQ_ERR
mdefine_line|#define RH_REQ_ERR                 -1
DECL|macro|RH_NACK
mdefine_line|#define RH_NACK                    0x00
multiline_comment|/* OHCI ROOT HUB REGISTER MASKS */
multiline_comment|/* roothub.portstatus [i] bits */
DECL|macro|RH_PS_CCS
mdefine_line|#define RH_PS_CCS            0x00000001   &t;/* current connect status */
DECL|macro|RH_PS_PES
mdefine_line|#define RH_PS_PES            0x00000002   &t;/* port enable status*/
DECL|macro|RH_PS_PSS
mdefine_line|#define RH_PS_PSS            0x00000004   &t;/* port suspend status */
DECL|macro|RH_PS_POCI
mdefine_line|#define RH_PS_POCI           0x00000008   &t;/* port over current indicator */
DECL|macro|RH_PS_PRS
mdefine_line|#define RH_PS_PRS            0x00000010  &t;/* port reset status */
DECL|macro|RH_PS_PPS
mdefine_line|#define RH_PS_PPS            0x00000100   &t;/* port power status */
DECL|macro|RH_PS_LSDA
mdefine_line|#define RH_PS_LSDA           0x00000200    &t;/* low speed device attached */
DECL|macro|RH_PS_CSC
mdefine_line|#define RH_PS_CSC            0x00010000 &t;/* connect status change */
DECL|macro|RH_PS_PESC
mdefine_line|#define RH_PS_PESC           0x00020000   &t;/* port enable status change */
DECL|macro|RH_PS_PSSC
mdefine_line|#define RH_PS_PSSC           0x00040000    &t;/* port suspend status change */
DECL|macro|RH_PS_OCIC
mdefine_line|#define RH_PS_OCIC           0x00080000    &t;/* over current indicator change */
DECL|macro|RH_PS_PRSC
mdefine_line|#define RH_PS_PRSC           0x00100000   &t;/* port reset status change */
multiline_comment|/* roothub.status bits */
DECL|macro|RH_HS_LPS
mdefine_line|#define RH_HS_LPS&t;     0x00000001&t;&t;/* local power status */
DECL|macro|RH_HS_OCI
mdefine_line|#define RH_HS_OCI&t;     0x00000002&t;&t;/* over current indicator */
DECL|macro|RH_HS_DRWE
mdefine_line|#define RH_HS_DRWE&t;     0x00008000&t;&t;/* device remote wakeup enable */
DECL|macro|RH_HS_LPSC
mdefine_line|#define RH_HS_LPSC&t;     0x00010000&t;&t;/* local power status change */
DECL|macro|RH_HS_OCIC
mdefine_line|#define RH_HS_OCIC&t;     0x00020000&t;&t;/* over current indicator change */
DECL|macro|RH_HS_CRWE
mdefine_line|#define RH_HS_CRWE&t;     0x80000000&t;&t;/* clear remote wakeup enable */
multiline_comment|/* roothub.b masks */
DECL|macro|RH_B_DR
mdefine_line|#define RH_B_DR&t;&t;0x0000ffff&t;&t;/* device removable flags */
DECL|macro|RH_B_PPCM
mdefine_line|#define RH_B_PPCM&t;0xffff0000&t;&t;/* port power control mask */
multiline_comment|/* roothub.a masks */
DECL|macro|RH_A_NDP
mdefine_line|#define&t;RH_A_NDP&t;(0xff &lt;&lt; 0)&t;&t;/* number of downstream ports */
DECL|macro|RH_A_PSM
mdefine_line|#define&t;RH_A_PSM&t;(1 &lt;&lt; 8)&t;&t;/* power switching mode */
DECL|macro|RH_A_NPS
mdefine_line|#define&t;RH_A_NPS&t;(1 &lt;&lt; 9)&t;&t;/* no power switching */
DECL|macro|RH_A_DT
mdefine_line|#define&t;RH_A_DT&t;&t;(1 &lt;&lt; 10)&t;&t;/* device type (mbz) */
DECL|macro|RH_A_OCPM
mdefine_line|#define&t;RH_A_OCPM&t;(1 &lt;&lt; 11)&t;&t;/* over current protection mode */
DECL|macro|RH_A_NOCP
mdefine_line|#define&t;RH_A_NOCP&t;(1 &lt;&lt; 12)&t;&t;/* no over current protection */
DECL|macro|RH_A_POTPGT
mdefine_line|#define&t;RH_A_POTPGT&t;(0xff &lt;&lt; 24)&t;&t;/* power on to power good time */
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))  
multiline_comment|/* urb */
r_typedef
r_struct
(brace
DECL|member|ed
id|ed_t
op_star
id|ed
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
singleline_comment|// number of tds associated with this request
DECL|member|td_cnt
id|__u16
id|td_cnt
suffix:semicolon
singleline_comment|// number of tds already serviced
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
op_star
id|wait
suffix:semicolon
DECL|member|td
id|td_t
op_star
id|td
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|// list pointer to all corresponding TDs associated with this request
DECL|typedef|urb_priv_t
)brace
id|urb_priv_t
suffix:semicolon
DECL|macro|URB_DEL
mdefine_line|#define URB_DEL 1
multiline_comment|/*&n; * This is the full ohci controller description&n; *&n; * Note how the &quot;proper&quot; USB information is just&n; * a subset of what the full implementation needs. (Linus)&n; */
DECL|struct|ohci
r_typedef
r_struct
id|ohci
(brace
DECL|member|hcca
r_struct
id|ohci_hcca
id|hcca
suffix:semicolon
multiline_comment|/* hcca */
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
multiline_comment|/* e.g. got a UE, we&squot;re hung */
DECL|member|resume_count
id|atomic_t
id|resume_count
suffix:semicolon
multiline_comment|/* defending against multiple resumes */
DECL|member|regs
r_struct
id|ohci_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* OHCI controller&squot;s memory */
DECL|member|ohci_hcd_list
r_struct
id|list_head
id|ohci_hcd_list
suffix:semicolon
multiline_comment|/* list of all ohci_hcd */
DECL|member|next
r_struct
id|ohci
op_star
id|next
suffix:semicolon
singleline_comment|// chain of uhci device contexts
singleline_comment|// struct list_head urb_list; &t;// list of all pending urbs
singleline_comment|// spinlock_t urb_list_lock; &t;// lock to keep consistency 
DECL|member|ohci_int_load
r_int
id|ohci_int_load
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* load of the 32 Interrupt Chains (for load balancing)*/
DECL|member|ed_rm_list
id|ed_t
op_star
id|ed_rm_list
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* lists of all endpoints to be removed */
DECL|member|ed_bulktail
id|ed_t
op_star
id|ed_bulktail
suffix:semicolon
multiline_comment|/* last endpoint of bulk list */
DECL|member|ed_controltail
id|ed_t
op_star
id|ed_controltail
suffix:semicolon
multiline_comment|/* last endpoint of control list */
DECL|member|ed_isotail
id|ed_t
op_star
id|ed_isotail
suffix:semicolon
multiline_comment|/* last endpoint of iso list */
DECL|member|intrstatus
r_int
id|intrstatus
suffix:semicolon
DECL|member|hc_control
id|__u32
id|hc_control
suffix:semicolon
multiline_comment|/* copy of the hc control reg */
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|rh
r_struct
id|virt_root_hub
id|rh
suffix:semicolon
multiline_comment|/* PCI device handle and settings */
DECL|member|ohci_dev
r_struct
id|pci_dev
op_star
id|ohci_dev
suffix:semicolon
DECL|member|pci_latency
id|u8
id|pci_latency
suffix:semicolon
DECL|typedef|ohci_t
)brace
id|ohci_t
suffix:semicolon
DECL|macro|NUM_TDS
mdefine_line|#define NUM_TDS&t;0&t;&t;/* num of preallocated transfer descriptors */
DECL|macro|NUM_EDS
mdefine_line|#define NUM_EDS 32&t;&t;/* num of preallocated endpoint descriptors */
DECL|struct|ohci_device
r_struct
id|ohci_device
(brace
DECL|member|ed
id|ed_t
id|ed
(braket
id|NUM_EDS
)braket
suffix:semicolon
DECL|member|ed_cnt
r_int
id|ed_cnt
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
op_star
id|wait
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// #define ohci_to_usb(ohci)&t;((ohci)-&gt;usb)
DECL|macro|usb_to_ohci
mdefine_line|#define usb_to_ohci(usb)&t;((struct ohci_device *)(usb)-&gt;hcpriv)
multiline_comment|/* hcd */
multiline_comment|/* endpoint */
r_static
r_int
id|ep_link
c_func
(paren
id|ohci_t
op_star
id|ohci
comma
id|ed_t
op_star
id|ed
)paren
suffix:semicolon
r_static
r_int
id|ep_unlink
c_func
(paren
id|ohci_t
op_star
id|ohci
comma
id|ed_t
op_star
id|ed
)paren
suffix:semicolon
r_static
id|ed_t
op_star
id|ep_add_ed
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_int
r_int
id|pipe
comma
r_int
id|interval
comma
r_int
id|load
)paren
suffix:semicolon
r_static
r_void
id|ep_rm_ed
c_func
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
id|ed_t
op_star
id|ed
)paren
suffix:semicolon
multiline_comment|/* td */
r_static
r_void
id|td_fill
c_func
(paren
r_int
r_int
id|info
comma
r_void
op_star
id|data
comma
r_int
id|len
comma
id|urb_t
op_star
id|urb
comma
r_int
id|index
)paren
suffix:semicolon
r_static
r_void
id|td_submit_urb
c_func
(paren
id|urb_t
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* root hub */
r_static
r_int
id|rh_submit_urb
c_func
(paren
id|urb_t
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|rh_unlink_urb
c_func
(paren
id|urb_t
op_star
id|urb
)paren
suffix:semicolon
r_static
r_int
id|rh_init_int_timer
c_func
(paren
id|urb_t
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|ALLOC_FLAGS
mdefine_line|#define ALLOC_FLAGS (in_interrupt () ? GFP_ATOMIC : GFP_KERNEL)
macro_line|#ifdef OHCI_MEM_SLAB
DECL|macro|__alloc
mdefine_line|#define&t;__alloc(t,c) kmem_cache_alloc(c,ALLOC_FLAGS)
DECL|macro|__free
mdefine_line|#define&t;__free(c,x) kmem_cache_free(c,x)
DECL|variable|td_cache
DECL|variable|ed_cache
r_static
id|kmem_cache_t
op_star
id|td_cache
comma
op_star
id|ed_cache
suffix:semicolon
multiline_comment|/*&n; * WARNING:  do NOT use this with &quot;forced slab debug&quot;; it won&squot;t respect&n; * our hardware alignment requirement.&n; */
macro_line|#ifndef OHCI_MEM_FLAGS
DECL|macro|OHCI_MEM_FLAGS
mdefine_line|#define&t;OHCI_MEM_FLAGS 0
macro_line|#endif
DECL|function|ohci_mem_init
r_static
r_int
id|ohci_mem_init
(paren
r_void
)paren
(brace
multiline_comment|/* redzoning (or forced debug!) breaks alignment */
r_int
id|flags
op_assign
(paren
id|OHCI_MEM_FLAGS
)paren
op_amp
op_complement
id|SLAB_RED_ZONE
suffix:semicolon
multiline_comment|/* TDs accessed by controllers and host */
id|td_cache
op_assign
id|kmem_cache_create
(paren
l_string|&quot;ohci_td&quot;
comma
r_sizeof
(paren
r_struct
id|td
)paren
comma
l_int|0
comma
id|flags
op_or
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|td_cache
)paren
(brace
id|dbg
(paren
l_string|&quot;no TD cache?&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* EDs are accessed by controllers and host;  dev part is host-only */
id|ed_cache
op_assign
id|kmem_cache_create
(paren
l_string|&quot;ohci_ed&quot;
comma
r_sizeof
(paren
r_struct
id|ohci_device
)paren
comma
l_int|0
comma
id|flags
op_or
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ed_cache
)paren
(brace
id|dbg
(paren
l_string|&quot;no ED cache?&quot;
)paren
suffix:semicolon
id|kmem_cache_destroy
(paren
id|td_cache
)paren
suffix:semicolon
id|td_cache
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;slab flags 0x%x&quot;
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_mem_cleanup
r_static
r_void
id|ohci_mem_cleanup
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ed_cache
op_logical_and
id|kmem_cache_destroy
(paren
id|ed_cache
)paren
)paren
id|err
(paren
l_string|&quot;ed_cache remained&quot;
)paren
suffix:semicolon
id|ed_cache
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|td_cache
op_logical_and
id|kmem_cache_destroy
(paren
id|td_cache
)paren
)paren
id|err
(paren
l_string|&quot;td_cache remained&quot;
)paren
suffix:semicolon
id|td_cache
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|__alloc
mdefine_line|#define&t;__alloc(t,c) kmalloc(sizeof(t),ALLOC_FLAGS)
DECL|macro|__free
mdefine_line|#define&t;__free(dev,x) kfree(x)
DECL|macro|td_cache
mdefine_line|#define td_cache 0
DECL|macro|ed_cache
mdefine_line|#define ed_cache 0
DECL|function|ohci_mem_init
r_static
r_inline
r_int
id|ohci_mem_init
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ohci_mem_cleanup
r_static
r_inline
r_void
id|ohci_mem_cleanup
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* FIXME: pci_consistent version */
macro_line|#endif
multiline_comment|/* TDs ... */
r_static
r_inline
r_struct
id|td
op_star
DECL|function|td_alloc
id|td_alloc
(paren
r_struct
id|ohci
op_star
id|hc
)paren
(brace
r_struct
id|td
op_star
id|td
op_assign
(paren
r_struct
id|td
op_star
)paren
id|__alloc
(paren
r_struct
id|td
comma
id|td_cache
)paren
suffix:semicolon
r_return
id|td
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|td_free
id|td_free
(paren
r_struct
id|ohci
op_star
id|hc
comma
r_struct
id|td
op_star
id|td
)paren
(brace
id|__free
(paren
id|td_cache
comma
id|td
)paren
suffix:semicolon
)brace
multiline_comment|/* DEV + EDs ... only the EDs need to be consistent */
r_static
r_inline
r_struct
id|ohci_device
op_star
DECL|function|dev_alloc
id|dev_alloc
(paren
r_struct
id|ohci
op_star
id|hc
)paren
(brace
r_struct
id|ohci_device
op_star
id|dev
op_assign
(paren
r_struct
id|ohci_device
op_star
)paren
id|__alloc
(paren
r_struct
id|ohci_device
comma
id|ed_cache
)paren
suffix:semicolon
r_return
id|dev
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|dev_free
id|dev_free
(paren
r_struct
id|ohci_device
op_star
id|dev
)paren
(brace
id|__free
(paren
id|ed_cache
comma
id|dev
)paren
suffix:semicolon
)brace
eof
