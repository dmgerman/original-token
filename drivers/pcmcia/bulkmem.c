multiline_comment|/*======================================================================&n;&n;    PCMCIA Bulk Memory Services&n;&n;    bulkmem.c 1.38 2000/09/25 19:29:51&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
DECL|macro|IN_CARD_SERVICES
mdefine_line|#define IN_CARD_SERVICES
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/ss.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/bulkmem.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &quot;cs_internal.h&quot;
multiline_comment|/*======================================================================&n;&n;    This function handles submitting an MTD request, and retrying&n;    requests when an MTD is busy.&n;&n;    An MTD request should never block.&n;    &n;======================================================================*/
DECL|function|do_mtd_request
r_static
r_int
id|do_mtd_request
c_func
(paren
id|memory_handle_t
id|handle
comma
id|mtd_request_t
op_star
id|req
comma
id|caddr_t
id|buf
)paren
(brace
r_int
id|ret
comma
id|tries
suffix:semicolon
id|client_t
op_star
id|mtd
suffix:semicolon
id|socket_info_t
op_star
id|s
suffix:semicolon
id|mtd
op_assign
id|handle-&gt;mtd
suffix:semicolon
r_if
c_cond
(paren
id|mtd
op_eq
l_int|NULL
)paren
r_return
id|CS_GENERAL_FAILURE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|mtd
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ret
op_assign
id|tries
op_assign
l_int|0
suffix:semicolon
id|tries
OL
l_int|100
suffix:semicolon
id|tries
op_increment
)paren
(brace
id|mtd-&gt;event_callback_args.mtdrequest
op_assign
id|req
suffix:semicolon
id|mtd-&gt;event_callback_args.buffer
op_assign
id|buf
suffix:semicolon
id|ret
op_assign
id|EVENT
c_func
(paren
id|mtd
comma
id|CS_EVENT_MTD_REQUEST
comma
id|CS_EVENT_PRI_LOW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_BUSY
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|req-&gt;Status
)paren
(brace
r_case
id|MTD_WAITREQ
suffix:colon
multiline_comment|/* Not that we should ever need this... */
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|mtd-&gt;mtd_req
comma
id|HZ
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTD_WAITTIMER
suffix:colon
r_case
id|MTD_WAITRDY
suffix:colon
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|mtd-&gt;mtd_req
comma
id|req-&gt;Timeout
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
id|req-&gt;Function
op_or_assign
id|MTD_REQ_TIMEOUT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTD_WAITPOWER
suffix:colon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|mtd-&gt;mtd_req
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;cs: do_mtd_request interrupted!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tries
op_eq
l_int|20
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;cs: MTD request timed out!&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|CS_GENERAL_FAILURE
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|mtd-&gt;mtd_req
)paren
suffix:semicolon
id|retry_erase_list
c_func
(paren
op_amp
id|mtd-&gt;erase_busy
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* do_mtd_request */
multiline_comment|/*======================================================================&n;&n;    This stuff is all for handling asynchronous erase requests.  It&n;    is complicated because all the retry stuff has to be dealt with&n;    in timer interrupts or in the card status event handler.&n;&n;======================================================================*/
DECL|function|insert_queue
r_static
r_void
id|insert_queue
c_func
(paren
id|erase_busy_t
op_star
id|head
comma
id|erase_busy_t
op_star
id|entry
)paren
(brace
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;cs: adding 0x%p to queue 0x%p&bslash;n&quot;
comma
id|entry
comma
id|head
)paren
suffix:semicolon
id|entry-&gt;next
op_assign
id|head
suffix:semicolon
id|entry-&gt;prev
op_assign
id|head-&gt;prev
suffix:semicolon
id|head-&gt;prev-&gt;next
op_assign
id|entry
suffix:semicolon
id|head-&gt;prev
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|remove_queue
r_static
r_void
id|remove_queue
c_func
(paren
id|erase_busy_t
op_star
id|entry
)paren
(brace
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;cs: unqueueing 0x%p&bslash;n&quot;
comma
id|entry
)paren
suffix:semicolon
id|entry-&gt;next-&gt;prev
op_assign
id|entry-&gt;prev
suffix:semicolon
id|entry-&gt;prev-&gt;next
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
DECL|function|retry_erase
r_static
r_void
id|retry_erase
c_func
(paren
id|erase_busy_t
op_star
id|busy
comma
id|u_int
id|cause
)paren
(brace
id|eraseq_entry_t
op_star
id|erase
op_assign
id|busy-&gt;erase
suffix:semicolon
id|mtd_request_t
id|req
suffix:semicolon
id|client_t
op_star
id|mtd
suffix:semicolon
id|socket_info_t
op_star
id|s
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;cs: trying erase request 0x%p...&bslash;n&quot;
comma
id|busy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy-&gt;next
)paren
id|remove_queue
c_func
(paren
id|busy
)paren
suffix:semicolon
id|req.Function
op_assign
id|MTD_REQ_ERASE
op_or
id|cause
suffix:semicolon
id|req.TransferLength
op_assign
id|erase-&gt;Size
suffix:semicolon
id|req.DestCardOffset
op_assign
id|erase-&gt;Offset
op_plus
id|erase-&gt;Handle-&gt;info.CardOffset
suffix:semicolon
id|req.MediaID
op_assign
id|erase-&gt;Handle-&gt;MediaID
suffix:semicolon
id|mtd
op_assign
id|erase-&gt;Handle-&gt;mtd
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|mtd
)paren
suffix:semicolon
id|mtd-&gt;event_callback_args.mtdrequest
op_assign
op_amp
id|req
suffix:semicolon
id|ret
op_assign
id|EVENT
c_func
(paren
id|mtd
comma
id|CS_EVENT_MTD_REQUEST
comma
id|CS_EVENT_PRI_LOW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|CS_BUSY
)paren
(brace
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;  Status = %d, requeueing.&bslash;n&quot;
comma
id|req.Status
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|req.Status
)paren
(brace
r_case
id|MTD_WAITREQ
suffix:colon
r_case
id|MTD_WAITPOWER
suffix:colon
id|insert_queue
c_func
(paren
op_amp
id|mtd-&gt;erase_busy
comma
id|busy
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTD_WAITTIMER
suffix:colon
r_case
id|MTD_WAITRDY
suffix:colon
r_if
c_cond
(paren
id|req.Status
op_eq
id|MTD_WAITRDY
)paren
id|insert_queue
c_func
(paren
op_amp
id|s-&gt;erase_busy
comma
id|busy
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|busy-&gt;timeout
comma
id|jiffies
op_plus
id|req.Timeout
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* update erase queue status */
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;  Ret = %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
r_case
id|CS_SUCCESS
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_PASSED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_WRITE_PROTECTED
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_MEDIA_WRPROT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_BAD_OFFSET
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_BAD_OFFSET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_BAD_SIZE
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_BAD_SIZE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_NO_CARD
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_BAD_SOCKET
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|erase-&gt;State
op_assign
id|ERASE_FAILED
suffix:semicolon
r_break
suffix:semicolon
)brace
id|busy-&gt;client-&gt;event_callback_args.info
op_assign
id|erase
suffix:semicolon
id|EVENT
c_func
(paren
id|busy-&gt;client
comma
id|CS_EVENT_ERASE_COMPLETE
comma
id|CS_EVENT_PRI_LOW
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|busy
)paren
suffix:semicolon
multiline_comment|/* Resubmit anything waiting for a request to finish */
id|wake_up_interruptible
c_func
(paren
op_amp
id|mtd-&gt;mtd_req
)paren
suffix:semicolon
id|retry_erase_list
c_func
(paren
op_amp
id|mtd-&gt;erase_busy
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* retry_erase */
DECL|function|retry_erase_list
r_void
id|retry_erase_list
c_func
(paren
id|erase_busy_t
op_star
id|list
comma
id|u_int
id|cause
)paren
(brace
id|erase_busy_t
id|tmp
op_assign
op_star
id|list
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;cs: rescanning erase queue list 0x%p&bslash;n&quot;
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;next
op_eq
id|list
)paren
r_return
suffix:semicolon
multiline_comment|/* First, truncate the original list */
id|list-&gt;prev-&gt;next
op_assign
op_amp
id|tmp
suffix:semicolon
id|list-&gt;next-&gt;prev
op_assign
op_amp
id|tmp
suffix:semicolon
id|list-&gt;prev
op_assign
id|list-&gt;next
op_assign
id|list
suffix:semicolon
id|tmp.prev-&gt;next
op_assign
op_amp
id|tmp
suffix:semicolon
id|tmp.next-&gt;prev
op_assign
op_amp
id|tmp
suffix:semicolon
multiline_comment|/* Now, retry each request, in order. */
r_while
c_loop
(paren
id|tmp.next
op_ne
op_amp
id|tmp
)paren
id|retry_erase
c_func
(paren
id|tmp.next
comma
id|cause
)paren
suffix:semicolon
)brace
multiline_comment|/* retry_erase_list */
DECL|function|handle_erase_timeout
r_static
r_void
id|handle_erase_timeout
c_func
(paren
id|u_long
id|arg
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cs: erase timeout for entry 0x%lx&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
id|retry_erase
c_func
(paren
(paren
id|erase_busy_t
op_star
)paren
id|arg
comma
id|MTD_REQ_TIMEOUT
)paren
suffix:semicolon
)brace
DECL|function|setup_erase_request
r_static
r_void
id|setup_erase_request
c_func
(paren
id|client_handle_t
id|handle
comma
id|eraseq_entry_t
op_star
id|erase
)paren
(brace
id|erase_busy_t
op_star
id|busy
suffix:semicolon
id|region_info_t
op_star
id|info
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_REGION
c_func
(paren
id|erase-&gt;Handle
)paren
)paren
id|erase-&gt;State
op_assign
id|ERASE_BAD_SOCKET
suffix:semicolon
r_else
(brace
id|info
op_assign
op_amp
id|erase-&gt;Handle-&gt;info
suffix:semicolon
r_if
c_cond
(paren
(paren
id|erase-&gt;Offset
op_ge
id|info-&gt;RegionSize
)paren
op_logical_or
(paren
id|erase-&gt;Offset
op_amp
(paren
id|info-&gt;BlockSize
op_minus
l_int|1
)paren
)paren
)paren
id|erase-&gt;State
op_assign
id|ERASE_BAD_OFFSET
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|erase-&gt;Offset
op_plus
id|erase-&gt;Size
OG
id|info-&gt;RegionSize
)paren
op_logical_or
(paren
id|erase-&gt;Size
op_amp
(paren
id|info-&gt;BlockSize
op_minus
l_int|1
)paren
)paren
)paren
id|erase-&gt;State
op_assign
id|ERASE_BAD_SIZE
suffix:semicolon
r_else
(brace
id|erase-&gt;State
op_assign
l_int|1
suffix:semicolon
id|busy
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|erase_busy_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|busy-&gt;erase
op_assign
id|erase
suffix:semicolon
id|busy-&gt;client
op_assign
id|handle
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|busy-&gt;timeout
)paren
suffix:semicolon
id|busy-&gt;timeout.data
op_assign
(paren
id|u_long
)paren
id|busy
suffix:semicolon
id|busy-&gt;timeout.function
op_assign
op_amp
id|handle_erase_timeout
suffix:semicolon
id|busy-&gt;prev
op_assign
id|busy-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|retry_erase
c_func
(paren
id|busy
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* setup_erase_request */
multiline_comment|/*======================================================================&n;&n;    MTD helper functions&n;&n;======================================================================*/
DECL|function|mtd_modify_window
r_static
r_int
id|mtd_modify_window
c_func
(paren
id|window_handle_t
id|win
comma
id|mtd_mod_win_t
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
(paren
id|win
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|win-&gt;magic
op_ne
id|WINDOW_MAGIC
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|win-&gt;ctl.flags
op_assign
id|MAP_16BIT
op_or
id|MAP_ACTIVE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Attributes
op_amp
id|WIN_USE_WAIT
)paren
id|win-&gt;ctl.flags
op_or_assign
id|MAP_USE_WAIT
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Attributes
op_amp
id|WIN_MEMORY_TYPE
)paren
id|win-&gt;ctl.flags
op_or_assign
id|MAP_ATTRIB
suffix:semicolon
id|win-&gt;ctl.speed
op_assign
id|req-&gt;AccessSpeed
suffix:semicolon
id|win-&gt;ctl.card_start
op_assign
id|req-&gt;CardOffset
suffix:semicolon
id|win-&gt;sock-&gt;ss_entry
op_member_access_from_pointer
id|set_mem_map
c_func
(paren
id|win-&gt;sock-&gt;sock
comma
op_amp
id|win-&gt;ctl
)paren
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
DECL|function|mtd_set_vpp
r_static
r_int
id|mtd_set_vpp
c_func
(paren
id|client_handle_t
id|handle
comma
id|mtd_vpp_req_t
op_star
id|req
)paren
(brace
id|socket_info_t
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Vpp1
op_ne
id|req-&gt;Vpp2
)paren
r_return
id|CS_BAD_VPP
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
id|s-&gt;socket.Vpp
op_assign
id|req-&gt;Vpp1
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;ss_entry
op_member_access_from_pointer
id|set_socket
c_func
(paren
id|s-&gt;sock
comma
op_amp
id|s-&gt;socket
)paren
)paren
r_return
id|CS_BAD_VPP
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
DECL|function|mtd_rdy_mask
r_static
r_int
id|mtd_rdy_mask
c_func
(paren
id|client_handle_t
id|handle
comma
id|mtd_rdy_req_t
op_star
id|req
)paren
(brace
id|socket_info_t
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Mask
op_amp
id|CS_EVENT_READY_CHANGE
)paren
id|s-&gt;socket.csc_mask
op_or_assign
id|SS_READY
suffix:semicolon
r_else
id|s-&gt;socket.csc_mask
op_and_assign
op_complement
id|SS_READY
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;ss_entry
op_member_access_from_pointer
id|set_socket
c_func
(paren
id|s-&gt;sock
comma
op_amp
id|s-&gt;socket
)paren
)paren
r_return
id|CS_GENERAL_FAILURE
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
DECL|function|MTDHelperEntry
r_int
id|MTDHelperEntry
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|a1
comma
r_void
op_star
id|a2
)paren
(brace
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
id|MTDRequestWindow
suffix:colon
(brace
id|window_handle_t
id|w
suffix:semicolon
r_int
id|ret
op_assign
id|pcmcia_request_window
c_func
(paren
id|a1
comma
id|a2
comma
op_amp
id|w
)paren
suffix:semicolon
(paren
id|window_handle_t
op_star
)paren
id|a1
op_assign
id|w
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MTDReleaseWindow
suffix:colon
r_return
id|pcmcia_release_window
c_func
(paren
id|a1
)paren
suffix:semicolon
r_case
id|MTDModifyWindow
suffix:colon
r_return
id|mtd_modify_window
c_func
(paren
id|a1
comma
id|a2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTDSetVpp
suffix:colon
r_return
id|mtd_set_vpp
c_func
(paren
id|a1
comma
id|a2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MTDRDYMask
suffix:colon
r_return
id|mtd_rdy_mask
c_func
(paren
id|a1
comma
id|a2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|CS_UNSUPPORTED_FUNCTION
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* MTDHelperEntry */
multiline_comment|/*======================================================================&n;&n;    This stuff is used by Card Services to initialize the table of&n;    region info used for subsequent calls to GetFirstRegion and&n;    GetNextRegion.&n;    &n;======================================================================*/
DECL|function|setup_regions
r_static
r_void
id|setup_regions
c_func
(paren
id|client_handle_t
id|handle
comma
r_int
id|attr
comma
id|memory_handle_t
op_star
id|list
)paren
(brace
r_int
id|i
comma
id|code
comma
id|has_jedec
comma
id|has_geo
suffix:semicolon
id|u_int
id|offset
suffix:semicolon
id|cistpl_device_t
id|device
suffix:semicolon
id|cistpl_jedec_t
id|jedec
suffix:semicolon
id|cistpl_device_geo_t
id|geo
suffix:semicolon
id|memory_handle_t
id|r
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;cs: setup_regions(0x%p, %d, 0x%p)&bslash;n&quot;
comma
id|handle
comma
id|attr
comma
id|list
)paren
suffix:semicolon
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_DEVICE_A
suffix:colon
id|CISTPL_DEVICE
suffix:semicolon
r_if
c_cond
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|device
)paren
op_ne
id|CS_SUCCESS
)paren
r_return
suffix:semicolon
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_JEDEC_A
suffix:colon
id|CISTPL_JEDEC_C
suffix:semicolon
id|has_jedec
op_assign
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|jedec
)paren
op_eq
id|CS_SUCCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_jedec
op_logical_and
(paren
id|device.ndev
op_ne
id|jedec.nid
)paren
)paren
(brace
macro_line|#ifdef PCMCIA_DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cs: Device info does not match JEDEC info.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|has_jedec
op_assign
l_int|0
suffix:semicolon
)brace
id|code
op_assign
(paren
id|attr
)paren
ques
c_cond
id|CISTPL_DEVICE_GEO_A
suffix:colon
id|CISTPL_DEVICE_GEO
suffix:semicolon
id|has_geo
op_assign
(paren
id|read_tuple
c_func
(paren
id|handle
comma
id|code
comma
op_amp
id|geo
)paren
op_eq
id|CS_SUCCESS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|has_geo
op_logical_and
(paren
id|device.ndev
op_ne
id|geo.ngeo
)paren
)paren
(brace
macro_line|#ifdef PCMCIA_DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cs: Device info does not match geometry tuple.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|has_geo
op_assign
l_int|0
suffix:semicolon
)brace
id|offset
op_assign
l_int|0
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
id|device.ndev
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|device.dev
(braket
id|i
)braket
dot
id|type
op_ne
id|CISTPL_DTYPE_NULL
)paren
op_logical_and
(paren
id|device.dev
(braket
id|i
)braket
dot
id|size
op_ne
l_int|0
)paren
)paren
(brace
id|r
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|r
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|r-&gt;region_magic
op_assign
id|REGION_MAGIC
suffix:semicolon
id|r-&gt;state
op_assign
l_int|0
suffix:semicolon
id|r-&gt;dev_info
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|r-&gt;mtd
op_assign
l_int|NULL
suffix:semicolon
id|r-&gt;info.Attributes
op_assign
(paren
id|attr
)paren
ques
c_cond
id|REGION_TYPE_AM
suffix:colon
l_int|0
suffix:semicolon
id|r-&gt;info.CardOffset
op_assign
id|offset
suffix:semicolon
id|r-&gt;info.RegionSize
op_assign
id|device.dev
(braket
id|i
)braket
dot
id|size
suffix:semicolon
id|r-&gt;info.AccessSpeed
op_assign
id|device.dev
(braket
id|i
)braket
dot
id|speed
suffix:semicolon
r_if
c_cond
(paren
id|has_jedec
)paren
(brace
id|r-&gt;info.JedecMfr
op_assign
id|jedec.id
(braket
id|i
)braket
dot
id|mfr
suffix:semicolon
id|r-&gt;info.JedecInfo
op_assign
id|jedec.id
(braket
id|i
)braket
dot
id|info
suffix:semicolon
)brace
r_else
id|r-&gt;info.JedecMfr
op_assign
id|r-&gt;info.JedecInfo
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|has_geo
)paren
(brace
id|r-&gt;info.BlockSize
op_assign
id|geo.geo
(braket
id|i
)braket
dot
id|buswidth
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|erase_block
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|interleave
suffix:semicolon
id|r-&gt;info.PartMultiple
op_assign
id|r-&gt;info.BlockSize
op_star
id|geo.geo
(braket
id|i
)braket
dot
id|partition
suffix:semicolon
)brace
r_else
id|r-&gt;info.BlockSize
op_assign
id|r-&gt;info.PartMultiple
op_assign
l_int|1
suffix:semicolon
id|r-&gt;info.next
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
id|r
suffix:semicolon
)brace
id|offset
op_add_assign
id|device.dev
(braket
id|i
)braket
dot
id|size
suffix:semicolon
)brace
)brace
multiline_comment|/* setup_regions */
multiline_comment|/*======================================================================&n;&n;    This is tricky.  When get_first_region() is called by Driver&n;    Services, we initialize the region info table in the socket&n;    structure.  When it is called by an MTD, we can just scan the&n;    table for matching entries.&n;    &n;======================================================================*/
DECL|function|match_region
r_static
r_int
id|match_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|memory_handle_t
id|list
comma
id|region_info_t
op_star
id|match
)paren
(brace
r_while
c_loop
(paren
id|list
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|handle-&gt;Attributes
op_amp
id|INFO_MTD_CLIENT
)paren
op_logical_or
(paren
id|strcmp
c_func
(paren
id|handle-&gt;dev_info
comma
id|list-&gt;dev_info
)paren
op_eq
l_int|0
)paren
)paren
(brace
op_star
id|match
op_assign
id|list-&gt;info
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
id|list
op_assign
id|list-&gt;info.next
suffix:semicolon
)brace
r_return
id|CS_NO_MORE_ITEMS
suffix:semicolon
)brace
multiline_comment|/* match_region */
DECL|function|pcmcia_get_first_region
r_int
id|pcmcia_get_first_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
(brace
id|socket_info_t
op_star
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|handle-&gt;Attributes
op_amp
id|INFO_MASTER_CLIENT
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|s-&gt;state
op_amp
id|SOCKET_REGION_INFO
)paren
)paren
)paren
(brace
id|setup_regions
c_func
(paren
id|handle
comma
l_int|0
comma
op_amp
id|s-&gt;c_region
)paren
suffix:semicolon
id|setup_regions
c_func
(paren
id|handle
comma
l_int|1
comma
op_amp
id|s-&gt;a_region
)paren
suffix:semicolon
id|s-&gt;state
op_or_assign
id|SOCKET_REGION_INFO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rgn-&gt;Attributes
op_amp
id|REGION_TYPE_AM
)paren
r_return
id|match_region
c_func
(paren
id|handle
comma
id|s-&gt;a_region
comma
id|rgn
)paren
suffix:semicolon
r_else
r_return
id|match_region
c_func
(paren
id|handle
comma
id|s-&gt;c_region
comma
id|rgn
)paren
suffix:semicolon
)brace
multiline_comment|/* get_first_region */
DECL|function|pcmcia_get_next_region
r_int
id|pcmcia_get_next_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
(brace
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|match_region
c_func
(paren
id|handle
comma
id|rgn-&gt;next
comma
id|rgn
)paren
suffix:semicolon
)brace
multiline_comment|/* get_next_region */
multiline_comment|/*======================================================================&n;&n;    Connect an MTD with a memory region.&n;    &n;======================================================================*/
DECL|function|pcmcia_register_mtd
r_int
id|pcmcia_register_mtd
c_func
(paren
id|client_handle_t
id|handle
comma
id|mtd_reg_t
op_star
id|reg
)paren
(brace
id|memory_handle_t
id|list
suffix:semicolon
id|socket_info_t
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_HANDLE
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;Attributes
op_amp
id|REGION_TYPE_AM
)paren
id|list
op_assign
id|s-&gt;a_region
suffix:semicolon
r_else
id|list
op_assign
id|s-&gt;c_region
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;cs: register_mtd(0x%p, &squot;%s&squot;, 0x%x)&bslash;n&quot;
comma
id|handle
comma
id|handle-&gt;dev_info
comma
id|reg-&gt;Offset
)paren
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;info.CardOffset
op_eq
id|reg-&gt;Offset
)paren
r_break
suffix:semicolon
id|list
op_assign
id|list-&gt;info.next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list
op_logical_and
(paren
id|list-&gt;mtd
op_eq
l_int|NULL
)paren
op_logical_and
(paren
id|strcmp
c_func
(paren
id|handle-&gt;dev_info
comma
id|list-&gt;dev_info
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|list-&gt;info.Attributes
op_assign
id|reg-&gt;Attributes
suffix:semicolon
id|list-&gt;MediaID
op_assign
id|reg-&gt;MediaID
suffix:semicolon
id|list-&gt;mtd
op_assign
id|handle
suffix:semicolon
id|handle-&gt;mtd_count
op_increment
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
r_else
r_return
id|CS_BAD_OFFSET
suffix:semicolon
)brace
multiline_comment|/* register_mtd */
multiline_comment|/*======================================================================&n;&n;    Erase queue management functions&n;    &n;======================================================================*/
DECL|function|pcmcia_register_erase_queue
r_int
id|pcmcia_register_erase_queue
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|eraseq_hdr_t
op_star
id|header
comma
id|eraseq_handle_t
op_star
id|e
)paren
(brace
id|eraseq_t
op_star
id|queue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|handle
op_eq
l_int|NULL
)paren
op_logical_or
id|CHECK_HANDLE
c_func
(paren
op_star
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|queue
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|queue
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|queue
)paren
r_return
id|CS_OUT_OF_RESOURCE
suffix:semicolon
id|queue-&gt;eraseq_magic
op_assign
id|ERASEQ_MAGIC
suffix:semicolon
id|queue-&gt;handle
op_assign
op_star
id|handle
suffix:semicolon
id|queue-&gt;count
op_assign
id|header-&gt;QueueEntryCnt
suffix:semicolon
id|queue-&gt;entry
op_assign
id|header-&gt;QueueEntryArray
suffix:semicolon
op_star
id|e
op_assign
id|queue
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* register_erase_queue */
DECL|function|pcmcia_deregister_erase_queue
r_int
id|pcmcia_deregister_erase_queue
c_func
(paren
id|eraseq_handle_t
id|eraseq
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_ERASEQ
c_func
(paren
id|eraseq
)paren
)paren
r_return
id|CS_BAD_HANDLE
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
id|eraseq-&gt;count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ERASE_IN_PROGRESS
c_func
(paren
id|eraseq-&gt;entry
(braket
id|i
)braket
dot
id|State
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|eraseq-&gt;count
)paren
r_return
id|CS_BUSY
suffix:semicolon
id|eraseq-&gt;eraseq_magic
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|eraseq
)paren
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* deregister_erase_queue */
DECL|function|pcmcia_check_erase_queue
r_int
id|pcmcia_check_erase_queue
c_func
(paren
id|eraseq_handle_t
id|eraseq
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_ERASEQ
c_func
(paren
id|eraseq
)paren
)paren
r_return
id|CS_BAD_HANDLE
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
id|eraseq-&gt;count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|eraseq-&gt;entry
(braket
id|i
)braket
dot
id|State
op_eq
id|ERASE_QUEUED
)paren
id|setup_erase_request
c_func
(paren
id|eraseq-&gt;handle
comma
op_amp
id|eraseq-&gt;entry
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* check_erase_queue */
multiline_comment|/*======================================================================&n;&n;    Look up the memory region matching the request, and return a&n;    memory handle.&n;    &n;======================================================================*/
DECL|function|pcmcia_open_memory
r_int
id|pcmcia_open_memory
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|open_mem_t
op_star
id|open
comma
id|memory_handle_t
op_star
id|mh
)paren
(brace
id|socket_info_t
op_star
id|s
suffix:semicolon
id|memory_handle_t
id|region
suffix:semicolon
r_if
c_cond
(paren
(paren
id|handle
op_eq
l_int|NULL
)paren
op_logical_or
id|CHECK_HANDLE
c_func
(paren
op_star
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
id|s
op_assign
id|SOCKET
c_func
(paren
op_star
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|open-&gt;Attributes
op_amp
id|MEMORY_TYPE_AM
)paren
id|region
op_assign
id|s-&gt;a_region
suffix:semicolon
r_else
id|region
op_assign
id|s-&gt;c_region
suffix:semicolon
r_while
c_loop
(paren
id|region
)paren
(brace
r_if
c_cond
(paren
id|region-&gt;info.CardOffset
op_eq
id|open-&gt;Offset
)paren
r_break
suffix:semicolon
id|region
op_assign
id|region-&gt;info.next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|region
op_logical_and
id|region-&gt;mtd
)paren
(brace
op_star
id|mh
op_assign
id|region
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;cs: open_memory(0x%p, 0x%x) = 0x%p&bslash;n&quot;
comma
id|handle
comma
id|open-&gt;Offset
comma
id|region
)paren
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
r_else
r_return
id|CS_BAD_OFFSET
suffix:semicolon
)brace
multiline_comment|/* open_memory */
multiline_comment|/*======================================================================&n;&n;    Close a memory handle from an earlier call to OpenMemory.&n;    &n;    For the moment, I don&squot;t think this needs to do anything.&n;    &n;======================================================================*/
DECL|function|pcmcia_close_memory
r_int
id|pcmcia_close_memory
c_func
(paren
id|memory_handle_t
id|handle
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;cs: close_memory(0x%p)&bslash;n&quot;
comma
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_REGION
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|CS_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* close_memory */
multiline_comment|/*======================================================================&n;&n;    Read from a memory device, using a handle previously returned&n;    by a call to OpenMemory.&n;    &n;======================================================================*/
DECL|function|pcmcia_read_memory
r_int
id|pcmcia_read_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|mem_op_t
op_star
id|req
comma
id|caddr_t
id|buf
)paren
(brace
id|mtd_request_t
id|mtd
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_REGION
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Offset
op_ge
id|handle-&gt;info.RegionSize
)paren
r_return
id|CS_BAD_OFFSET
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Offset
op_plus
id|req-&gt;Count
OG
id|handle-&gt;info.RegionSize
)paren
r_return
id|CS_BAD_SIZE
suffix:semicolon
id|mtd.SrcCardOffset
op_assign
id|req-&gt;Offset
op_plus
id|handle-&gt;info.CardOffset
suffix:semicolon
id|mtd.TransferLength
op_assign
id|req-&gt;Count
suffix:semicolon
id|mtd.MediaID
op_assign
id|handle-&gt;MediaID
suffix:semicolon
id|mtd.Function
op_assign
id|MTD_REQ_READ
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Attributes
op_amp
id|MEM_OP_BUFFER_KERNEL
)paren
id|mtd.Function
op_or_assign
id|MTD_REQ_KERNEL
suffix:semicolon
r_return
id|do_mtd_request
c_func
(paren
id|handle
comma
op_amp
id|mtd
comma
id|buf
)paren
suffix:semicolon
)brace
multiline_comment|/* read_memory */
multiline_comment|/*======================================================================&n;&n;    Write to a memory device, using a handle previously returned by&n;    a call to OpenMemory.&n;    &n;======================================================================*/
DECL|function|pcmcia_write_memory
r_int
id|pcmcia_write_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|mem_op_t
op_star
id|req
comma
id|caddr_t
id|buf
)paren
(brace
id|mtd_request_t
id|mtd
suffix:semicolon
r_if
c_cond
(paren
id|CHECK_REGION
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Offset
op_ge
id|handle-&gt;info.RegionSize
)paren
r_return
id|CS_BAD_OFFSET
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Offset
op_plus
id|req-&gt;Count
OG
id|handle-&gt;info.RegionSize
)paren
r_return
id|CS_BAD_SIZE
suffix:semicolon
id|mtd.DestCardOffset
op_assign
id|req-&gt;Offset
op_plus
id|handle-&gt;info.CardOffset
suffix:semicolon
id|mtd.TransferLength
op_assign
id|req-&gt;Count
suffix:semicolon
id|mtd.MediaID
op_assign
id|handle-&gt;MediaID
suffix:semicolon
id|mtd.Function
op_assign
id|MTD_REQ_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;Attributes
op_amp
id|MEM_OP_BUFFER_KERNEL
)paren
id|mtd.Function
op_or_assign
id|MTD_REQ_KERNEL
suffix:semicolon
r_return
id|do_mtd_request
c_func
(paren
id|handle
comma
op_amp
id|mtd
comma
id|buf
)paren
suffix:semicolon
)brace
multiline_comment|/* write_memory */
multiline_comment|/*======================================================================&n;&n;    This isn&squot;t needed for anything I could think of.&n;    &n;======================================================================*/
DECL|function|pcmcia_copy_memory
r_int
id|pcmcia_copy_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|copy_op_t
op_star
id|req
)paren
(brace
r_if
c_cond
(paren
id|CHECK_REGION
c_func
(paren
id|handle
)paren
)paren
r_return
id|CS_BAD_HANDLE
suffix:semicolon
r_return
id|CS_UNSUPPORTED_FUNCTION
suffix:semicolon
)brace
eof
