multiline_comment|/*&n; * driver/usb/usb-core.c&n; *&n; * (C) Copyright David Waite 1999&n; * based on code from usb.c, by Linus Torvalds&n; *&n; * The purpose of this file is to pull any and all generic modular code from&n; * usb.c and put it in a separate file. This way usb.c is kept as a generic&n; * library, while this file handles starting drivers, etc.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;inits.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#ifndef CONFIG_USB_MODULE
macro_line|#&t;ifdef CONFIG_USB_UHCI
r_int
id|uhci_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_OHCI
r_int
id|ohci_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_OHCI_HCD
r_int
id|ohci_hcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#endif
DECL|function|usb_init
r_int
id|usb_init
c_func
(paren
r_void
)paren
(brace
id|usb_major_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB_PROC
id|proc_usb_init
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_USB_MODULE
macro_line|#&t;ifdef CONFIG_USB_UHCI
id|uhci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_OHCI
id|ohci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_OHCI_HCD
id|ohci_hcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_MOUSE
id|usb_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#       ifdef CONFIG_USB_HP_SCANNER
id|usb_hp_scanner_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#       endif
macro_line|#&t;ifdef CONFIG_USB_KBD
id|usb_kbd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_AUDIO
id|usb_audio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_ACM
id|usb_acm_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_PRINTER
id|usb_printer_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_SERIAL
id|usb_serial_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_CPIA
id|usb_cpia_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_HUB
id|usb_hub_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_SCSI
id|usb_scsi_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Clean up when unloading the module&n; */
DECL|function|cleanup_drivers
r_void
id|cleanup_drivers
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_USB_PROC
id|proc_usb_cleanup
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef MODULE
macro_line|#&t;ifdef CONFIG_USB_HUB
id|usb_hub_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#&t;ifdef CONFIG_USB_MOUSE
id|usb_mouse_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#&t;endif
macro_line|#       ifdef CONFIG_USB_HP_SCANNER
id|usb_hp_scanner_cleanup
c_func
(paren
)paren
suffix:semicolon
macro_line|#       endif
macro_line|#endif
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|usb_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|cleanup_drivers
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
