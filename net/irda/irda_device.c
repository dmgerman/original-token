multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda_device.c&n; * Version:       0.9&n; * Description:   Utility functions used by the device drivers&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Oct  9 09:22:27 1999&n; * Modified at:   Sun Jan 23 17:41:24 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/wrapper.h&gt;
r_extern
r_int
id|irtty_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nsc_ircc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ircc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|toshoboe_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|litelink_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|w83977af_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|esi_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tekram_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|actisys_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|girbil_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__irda_task_delete
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|variable|dongles
r_static
id|hashbin_t
op_star
id|dongles
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|tasks
r_static
id|hashbin_t
op_star
id|tasks
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|infrared_mode
r_const
r_char
op_star
id|infrared_mode
(braket
)braket
op_assign
(brace
l_string|&quot;IRDA_IRLAP&quot;
comma
l_string|&quot;IRDA_RAW&quot;
comma
l_string|&quot;SHARP_ASK&quot;
comma
l_string|&quot;TV_REMOTE&quot;
comma
)brace
suffix:semicolon
DECL|variable|task_state
r_static
r_const
r_char
op_star
id|task_state
(braket
)braket
op_assign
(brace
l_string|&quot;IRDA_TASK_INIT&quot;
comma
l_string|&quot;IRDA_TASK_DONE&quot;
comma
l_string|&quot;IRDA_TASK_WAIT&quot;
comma
l_string|&quot;IRDA_TASK_WAIT1&quot;
comma
l_string|&quot;IRDA_TASK_WAIT2&quot;
comma
l_string|&quot;IRDA_TASK_WAIT3&quot;
comma
l_string|&quot;IRDA_TASK_CHILD_INIT&quot;
comma
l_string|&quot;IRDA_TASK_CHILD_WAIT&quot;
comma
l_string|&quot;IRDA_TASK_CHILD_DONE&quot;
comma
)brace
suffix:semicolon
r_static
r_void
id|irda_task_timer_expired
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_int
id|irda_device_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
id|unused
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
DECL|function|irda_device_init
r_int
id|__init
id|irda_device_init
c_func
(paren
r_void
)paren
(brace
id|dongles
op_assign
id|hashbin_new
c_func
(paren
id|HB_GLOBAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dongles
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IrDA: Can&squot;t allocate dongles hashbin!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|tasks
op_assign
id|hashbin_new
c_func
(paren
id|HB_GLOBAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tasks
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;IrDA: Can&squot;t allocate tasks hashbin!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Call the init function of the device drivers that has not been&n;&t; * compiled as a module &n;&t; */
macro_line|#ifdef CONFIG_IRTTY_SIR
id|irtty_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_WINBOND_FIR
id|w83977af_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NSC_FIR
id|nsc_ircc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TOSHIBA_FIR
id|toshoboe_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMC_IRCC_FIR
id|ircc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ESI_DONGLE
id|esi_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TEKRAM_DONGLE
id|tekram_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACTISYS_DONGLE
id|actisys_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GIRBIL_DONGLE
id|girbil_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_LITELINK_DONGLE
id|litelink_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_OLD_BELKIN
id|old_belkin_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irda_device_cleanup
r_void
id|irda_device_cleanup
c_func
(paren
r_void
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|hashbin_delete
c_func
(paren
id|tasks
comma
(paren
id|FREE_FUNC
)paren
id|__irda_task_delete
)paren
suffix:semicolon
id|hashbin_delete
c_func
(paren
id|dongles
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_set_media_busy (self, status)&n; *&n; *    Called when we have detected that another station is transmiting&n; *    in contention mode.&n; */
DECL|function|irda_device_set_media_busy
r_void
id|irda_device_set_media_busy
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|status
)paren
(brace
r_struct
id|irlap_cb
op_star
id|self
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(%s)&bslash;n&quot;
comma
id|status
ques
c_cond
l_string|&quot;TRUE&quot;
suffix:colon
l_string|&quot;FALSE&quot;
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irlap_cb
op_star
)paren
id|dev-&gt;atalk_ptr
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
id|self-&gt;media_busy
op_assign
id|TRUE
suffix:semicolon
id|irlap_start_mbusy_timer
c_func
(paren
id|self
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|4
comma
l_string|&quot;Media busy!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|self-&gt;media_busy
op_assign
id|FALSE
suffix:semicolon
id|irlap_stop_mbusy_timer
c_func
(paren
id|self
)paren
suffix:semicolon
)brace
)brace
DECL|function|irda_device_set_dtr_rts
r_int
id|irda_device_set_dtr_rts
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|dtr
comma
r_int
id|rts
)paren
(brace
r_struct
id|if_irda_req
id|req
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;do_ioctl
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), do_ioctl not impl. by &quot;
l_string|&quot;device driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|req.ifr_dtr
op_assign
id|dtr
suffix:semicolon
id|req.ifr_rts
op_assign
id|rts
suffix:semicolon
id|ret
op_assign
id|dev
op_member_access_from_pointer
id|do_ioctl
c_func
(paren
id|dev
comma
(paren
r_struct
id|ifreq
op_star
)paren
op_amp
id|req
comma
id|SIOCSDTRRTS
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|irda_device_change_speed
r_int
id|irda_device_change_speed
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|__u32
id|speed
)paren
(brace
r_struct
id|if_irda_req
id|req
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;do_ioctl
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), do_ioctl not impl. by &quot;
l_string|&quot;device driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|req.ifr_baudrate
op_assign
id|speed
suffix:semicolon
id|ret
op_assign
id|dev
op_member_access_from_pointer
id|do_ioctl
c_func
(paren
id|dev
comma
(paren
r_struct
id|ifreq
op_star
)paren
op_amp
id|req
comma
id|SIOCSBANDWIDTH
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_is_receiving (dev)&n; *&n; *    Check if the device driver is currently receiving data&n; *&n; */
DECL|function|irda_device_is_receiving
r_int
id|irda_device_is_receiving
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|if_irda_req
id|req
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;do_ioctl
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), do_ioctl not impl. by &quot;
l_string|&quot;device driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|dev
op_member_access_from_pointer
id|do_ioctl
c_func
(paren
id|dev
comma
(paren
r_struct
id|ifreq
op_star
)paren
op_amp
id|req
comma
id|SIOCGRECEIVING
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
id|req.ifr_receiving
suffix:semicolon
)brace
DECL|function|irda_task_next_state
r_void
id|irda_task_next_state
c_func
(paren
r_struct
id|irda_task
op_star
id|task
comma
id|IRDA_TASK_STATE
id|state
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), state = %s&bslash;n&quot;
comma
id|task_state
(braket
id|state
)braket
)paren
suffix:semicolon
id|task-&gt;state
op_assign
id|state
suffix:semicolon
)brace
DECL|function|__irda_task_delete
r_static
r_void
id|__irda_task_delete
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|task-&gt;timer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
DECL|function|irda_task_delete
r_void
id|irda_task_delete
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
multiline_comment|/* Unregister task */
id|hashbin_remove
c_func
(paren
id|tasks
comma
(paren
r_int
)paren
id|task
comma
l_int|NULL
)paren
suffix:semicolon
id|__irda_task_delete
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_task_kick (task)&n; *&n; *    Tries to execute a task possible multiple times until the task is either&n; *    finished, or askes for a timeout. When a task is finished, we do post&n; *    processing, and notify the parent task, that is waiting for this task&n; *    to complete.&n; */
DECL|function|irda_task_kick
r_int
id|irda_task_kick
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
(brace
r_int
id|finished
op_assign
id|TRUE
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|task
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|task-&gt;magic
op_eq
id|IRDA_TASK_MAGIC
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Execute task until it&squot;s finished, or askes for a timeout */
r_do
(brace
id|timeout
op_assign
id|task
op_member_access_from_pointer
id|function
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_increment
OG
l_int|100
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), error in task handler!&bslash;n&quot;
)paren
suffix:semicolon
id|irda_task_delete
c_func
(paren
id|task
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|timeout
op_eq
l_int|0
)paren
op_logical_and
(paren
id|task-&gt;state
op_ne
id|IRDA_TASK_DONE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), Error executing task!&bslash;n&quot;
)paren
suffix:semicolon
id|irda_task_delete
c_func
(paren
id|task
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/* Check if we are finished */
r_if
c_cond
(paren
id|task-&gt;state
op_eq
id|IRDA_TASK_DONE
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|task-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Do post processing */
r_if
c_cond
(paren
id|task-&gt;finished
)paren
id|task
op_member_access_from_pointer
id|finished
c_func
(paren
id|task
)paren
suffix:semicolon
multiline_comment|/* Notify parent */
r_if
c_cond
(paren
id|task-&gt;parent
)paren
(brace
multiline_comment|/* Check if parent is waiting for us to complete */
r_if
c_cond
(paren
id|task-&gt;parent-&gt;state
op_eq
id|IRDA_TASK_CHILD_WAIT
)paren
(brace
id|task-&gt;parent-&gt;state
op_assign
id|IRDA_TASK_CHILD_DONE
suffix:semicolon
multiline_comment|/* Stop timer now that we are here */
id|del_timer
c_func
(paren
op_amp
id|task-&gt;parent-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Kick parent task */
id|irda_task_kick
c_func
(paren
id|task-&gt;parent
)paren
suffix:semicolon
)brace
)brace
id|irda_task_delete
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|timeout
OG
l_int|0
)paren
(brace
id|irda_start_timer
c_func
(paren
op_amp
id|task-&gt;timer
comma
id|timeout
comma
(paren
r_void
op_star
)paren
id|task
comma
id|irda_task_timer_expired
)paren
suffix:semicolon
id|finished
op_assign
id|FALSE
suffix:semicolon
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), not finished, and no timeout!&bslash;n&quot;
)paren
suffix:semicolon
id|finished
op_assign
id|FALSE
suffix:semicolon
)brace
r_return
id|finished
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_task_execute (instance, function, finished)&n; *&n; *    This function registers and tries to execute tasks that may take some&n; *    time to complete. We do it this hairy way since we may have been&n; *    called from interrupt context, so it&squot;s not possible to use&n; *    schedule_timeout() &n; */
DECL|function|irda_task_execute
r_struct
id|irda_task
op_star
id|irda_task_execute
c_func
(paren
r_void
op_star
id|instance
comma
id|IRDA_TASK_CALLBACK
id|function
comma
id|IRDA_TASK_CALLBACK
id|finished
comma
r_struct
id|irda_task
op_star
id|parent
comma
r_void
op_star
id|param
)paren
(brace
r_struct
id|irda_task
op_star
id|task
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|task
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irda_task
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|task
)paren
r_return
l_int|NULL
suffix:semicolon
id|task-&gt;state
op_assign
id|IRDA_TASK_INIT
suffix:semicolon
id|task-&gt;instance
op_assign
id|instance
suffix:semicolon
id|task-&gt;function
op_assign
id|function
suffix:semicolon
id|task-&gt;finished
op_assign
id|finished
suffix:semicolon
id|task-&gt;parent
op_assign
id|parent
suffix:semicolon
id|task-&gt;param
op_assign
id|param
suffix:semicolon
id|task-&gt;magic
op_assign
id|IRDA_TASK_MAGIC
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|task-&gt;timer
)paren
suffix:semicolon
multiline_comment|/* Register task */
id|hashbin_insert
c_func
(paren
id|tasks
comma
(paren
id|irda_queue_t
op_star
)paren
id|task
comma
(paren
r_int
)paren
id|task
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* No time to waste, so lets get going! */
id|ret
op_assign
id|irda_task_kick
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
r_return
id|task
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_task_timer_expired (data)&n; *&n; *    Task time has expired. We now try to execute task (again), and restart&n; *    the timer if the task has not finished yet&n; */
DECL|function|irda_task_timer_expired
r_static
r_void
id|irda_task_timer_expired
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|irda_task
op_star
id|task
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|task
op_assign
(paren
r_struct
id|irda_task
op_star
)paren
id|data
suffix:semicolon
id|irda_task_kick
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_setup (dev)&n; *&n; *    This function should be used by low level device drivers in a similar way&n; *    as ether_setup() is used by normal network device drivers&n; */
DECL|function|irda_device_setup
r_int
id|irda_device_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ASSERT
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|dev-&gt;hard_header_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;addr_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;features
op_or_assign
id|NETIF_F_DYNALLOC
suffix:semicolon
multiline_comment|/* dev-&gt;destructor      = irda_device_destructor; */
id|dev-&gt;type
op_assign
id|ARPHRD_IRDA
suffix:semicolon
id|dev-&gt;tx_queue_len
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Window size + 1 s-frame */
id|memset
c_func
(paren
id|dev-&gt;broadcast
comma
l_int|0xff
comma
l_int|4
)paren
suffix:semicolon
id|dev-&gt;mtu
op_assign
l_int|2048
suffix:semicolon
id|dev_init_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_NOARP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_txqueue_empty (dev)&n; *&n; *    Check if there is still some frames in the transmit queue for this&n; *    device. Maybe we should use: q-&gt;q.qlen == 0.&n; *&n; */
DECL|function|irda_device_txqueue_empty
r_int
id|irda_device_txqueue_empty
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|dev-&gt;qdisc-&gt;q
)paren
)paren
r_return
id|FALSE
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_init_dongle (self, type, qos)&n; *&n; *    Initialize attached dongle.&n; */
DECL|function|irda_device_dongle_init
id|dongle_t
op_star
id|irda_device_dongle_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|type
)paren
(brace
r_struct
id|dongle_reg
op_star
id|reg
suffix:semicolon
r_char
id|modname
(braket
l_int|32
)braket
suffix:semicolon
id|dongle_t
op_star
id|dongle
suffix:semicolon
id|ASSERT
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
multiline_comment|/* Try to load the module needed */
id|sprintf
c_func
(paren
id|modname
comma
l_string|&quot;irda-dongle-%d&quot;
comma
id|type
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_KMOD */
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_assign
id|hashbin_find
c_func
(paren
id|dongles
comma
id|type
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;IrDA: Unable to find requested dongle&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Allocate dongle info for this instance */
id|dongle
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|dongle_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dongle
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|dongle
comma
l_int|0
comma
r_sizeof
(paren
id|dongle_t
)paren
)paren
suffix:semicolon
multiline_comment|/* Bind the registration info to this particular instance */
id|dongle-&gt;issue
op_assign
id|reg
suffix:semicolon
id|dongle-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
id|dongle
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_dongle_cleanup (dongle)&n; *&n; *    &n; *&n; */
DECL|function|irda_device_dongle_cleanup
r_int
id|irda_device_dongle_cleanup
c_func
(paren
id|dongle_t
op_star
id|dongle
)paren
(brace
id|ASSERT
c_func
(paren
id|dongle
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|dongle-&gt;issue
op_member_access_from_pointer
id|close
c_func
(paren
id|dongle
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dongle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_register_dongle (dongle)&n; *&n; *    &n; *&n; */
DECL|function|irda_device_register_dongle
r_int
id|irda_device_register_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
r_new
)paren
(brace
multiline_comment|/* Check if this dongle has been registred before */
r_if
c_cond
(paren
id|hashbin_find
c_func
(paren
id|dongles
comma
r_new
op_member_access_from_pointer
id|type
comma
l_int|NULL
)paren
)paren
(brace
id|MESSAGE
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), Dongle already registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Insert IrDA dongle into hashbin */
id|hashbin_insert
c_func
(paren
id|dongles
comma
(paren
id|irda_queue_t
op_star
)paren
r_new
comma
r_new
op_member_access_from_pointer
id|type
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_device_unregister_dongle (dongle)&n; *&n; *    Unregister dongle, and remove dongle from list of registred dongles&n; *&n; */
DECL|function|irda_device_unregister_dongle
r_void
id|irda_device_unregister_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
id|dongle
)paren
(brace
r_struct
id|dongle
op_star
id|node
suffix:semicolon
id|node
op_assign
id|hashbin_remove
c_func
(paren
id|dongles
comma
id|dongle-&gt;type
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), dongle not found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function irda_device_set_mode (self, mode)&n; *&n; *    Set the Infrared device driver into mode where it sends and receives&n; *    data without using IrLAP framing. Check out the particular device&n; *    driver to find out which modes it support.&n; */
DECL|function|irda_device_set_mode
r_int
id|irda_device_set_mode
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mode
)paren
(brace
r_struct
id|if_irda_req
id|req
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;do_ioctl
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), set_raw_mode not impl. by &quot;
l_string|&quot;device driver&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|req.ifr_mode
op_assign
id|mode
suffix:semicolon
id|ret
op_assign
id|dev
op_member_access_from_pointer
id|do_ioctl
c_func
(paren
id|dev
comma
(paren
r_struct
id|ifreq
op_star
)paren
op_amp
id|req
comma
id|SIOCSMODE
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function setup_dma (idev, buffer, count, mode)&n; *&n; *    Setup the DMA channel. Commonly used by ISA FIR drivers&n; *&n; */
DECL|function|setup_dma
r_void
id|setup_dma
c_func
(paren
r_int
id|channel
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|claim_dma_lock
c_func
(paren
)paren
suffix:semicolon
id|disable_dma
c_func
(paren
id|channel
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|channel
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|channel
comma
id|mode
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|channel
comma
id|virt_to_bus
c_func
(paren
id|buffer
)paren
)paren
suffix:semicolon
id|set_dma_count
c_func
(paren
id|channel
comma
id|count
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|channel
)paren
suffix:semicolon
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
