multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * Exported symbols for module usage.&n; *&n; * Copyright (C) 1999 Andreas E. Bombe&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;ieee1394_transactions.h&quot;
multiline_comment|/* #include &quot;events.h&quot; */
macro_line|#include &quot;highlevel.h&quot;
DECL|variable|hpsb_register_lowlevel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_register_lowlevel
)paren
suffix:semicolon
DECL|variable|hpsb_unregister_lowlevel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_unregister_lowlevel
)paren
suffix:semicolon
DECL|variable|hpsb_get_host
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_get_host
)paren
suffix:semicolon
DECL|variable|hpsb_get_host_list
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_get_host_list
)paren
suffix:semicolon
DECL|variable|hpsb_inc_host_usage
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_inc_host_usage
)paren
suffix:semicolon
DECL|variable|hpsb_dec_host_usage
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_dec_host_usage
)paren
suffix:semicolon
DECL|variable|alloc_hpsb_packet
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_hpsb_packet
)paren
suffix:semicolon
DECL|variable|free_hpsb_packet
id|EXPORT_SYMBOL
c_func
(paren
id|free_hpsb_packet
)paren
suffix:semicolon
DECL|variable|hpsb_send_packet
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_send_packet
)paren
suffix:semicolon
DECL|variable|hpsb_bus_reset
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_bus_reset
)paren
suffix:semicolon
DECL|variable|hpsb_selfid_received
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_selfid_received
)paren
suffix:semicolon
DECL|variable|hpsb_selfid_complete
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_selfid_complete
)paren
suffix:semicolon
DECL|variable|hpsb_packet_sent
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_packet_sent
)paren
suffix:semicolon
DECL|variable|hpsb_packet_received
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_packet_received
)paren
suffix:semicolon
DECL|variable|hpsb_generation
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_generation
)paren
suffix:semicolon
DECL|variable|get_tlabel
id|EXPORT_SYMBOL
c_func
(paren
id|get_tlabel
)paren
suffix:semicolon
DECL|variable|free_tlabel
id|EXPORT_SYMBOL
c_func
(paren
id|free_tlabel
)paren
suffix:semicolon
DECL|variable|hpsb_make_readqpacket
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_make_readqpacket
)paren
suffix:semicolon
DECL|variable|hpsb_make_readbpacket
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_make_readbpacket
)paren
suffix:semicolon
DECL|variable|hpsb_make_writeqpacket
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_make_writeqpacket
)paren
suffix:semicolon
DECL|variable|hpsb_make_writebpacket
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_make_writebpacket
)paren
suffix:semicolon
DECL|variable|hpsb_make_lockpacket
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_make_lockpacket
)paren
suffix:semicolon
DECL|variable|hpsb_read
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_read
)paren
suffix:semicolon
DECL|variable|hpsb_write
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_write
)paren
suffix:semicolon
DECL|variable|hpsb_lock
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_lock
)paren
suffix:semicolon
DECL|variable|hpsb_register_highlevel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_register_highlevel
)paren
suffix:semicolon
DECL|variable|hpsb_unregister_highlevel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_unregister_highlevel
)paren
suffix:semicolon
DECL|variable|hpsb_register_addrspace
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_register_addrspace
)paren
suffix:semicolon
DECL|variable|hpsb_listen_channel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_listen_channel
)paren
suffix:semicolon
DECL|variable|hpsb_unlisten_channel
id|EXPORT_SYMBOL
c_func
(paren
id|hpsb_unlisten_channel
)paren
suffix:semicolon
DECL|variable|highlevel_read
id|EXPORT_SYMBOL
c_func
(paren
id|highlevel_read
)paren
suffix:semicolon
DECL|variable|highlevel_write
id|EXPORT_SYMBOL
c_func
(paren
id|highlevel_write
)paren
suffix:semicolon
DECL|variable|highlevel_lock
id|EXPORT_SYMBOL
c_func
(paren
id|highlevel_lock
)paren
suffix:semicolon
DECL|variable|highlevel_lock64
id|EXPORT_SYMBOL
c_func
(paren
id|highlevel_lock64
)paren
suffix:semicolon
multiline_comment|/*&n;EXPORT_SYMBOL(hpsb_dispatch_event);&n;EXPORT_SYMBOL(hpsb_reg_event_handler);&n;*/
eof
