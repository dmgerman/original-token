multiline_comment|/* $Id: hysdn_sched.c,v 1.5 2000/11/22 17:13:13 kai Exp $&n;&n; * Linux driver for HYSDN cards, scheduler routines for handling exchange card &lt;-&gt; pc.&n; *&n; * written by Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; *&n; * Copyright 1999  by Werner Cornelius (werner@titro.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;hysdn_defs.h&quot;
multiline_comment|/*****************************************************************************/
multiline_comment|/* hysdn_sched_rx is called from the cards handler to announce new data is   */
multiline_comment|/* available from the card. The routine has to handle the data and return    */
multiline_comment|/* with a nonzero code if the data could be worked (or even thrown away), if */
multiline_comment|/* no room to buffer the data is available a zero return tells the card      */
multiline_comment|/* to keep the data until later.                                             */
multiline_comment|/*****************************************************************************/
r_int
DECL|function|hysdn_sched_rx
id|hysdn_sched_rx
c_func
(paren
id|hysdn_card
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
id|word
id|len
comma
id|word
id|chan
)paren
(brace
r_switch
c_cond
(paren
id|chan
)paren
(brace
r_case
id|CHAN_NDIS_DATA
suffix:colon
id|hysdn_rx_netpkt
c_func
(paren
id|card
comma
id|buf
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* give packet to network handler */
r_break
suffix:semicolon
r_case
id|CHAN_ERRLOG
suffix:colon
id|hysdn_card_errlog
c_func
(paren
id|card
comma
(paren
id|tErrLogEntry
op_star
)paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;err_log_state
op_eq
id|ERRLOG_STATE_ON
)paren
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_START
suffix:semicolon
multiline_comment|/* start new fetch */
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_HYSDN_CAPI
r_case
id|CHAN_CAPI
suffix:colon
multiline_comment|/* give packet to CAPI handler */
id|hycapi_rx_capipkt
c_func
(paren
id|card
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_HYSDN_CAPI */
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq message channel %d len %d unhandled &bslash;n&quot;
comma
id|chan
comma
id|len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch rx channel */
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* always handled */
)brace
multiline_comment|/* hysdn_sched_rx */
multiline_comment|/*****************************************************************************/
multiline_comment|/* hysdn_sched_tx is called from the cards handler to announce that there is */
multiline_comment|/* room in the tx-buffer to the card and data may be sent if needed.         */
multiline_comment|/* If the routine wants to send data it must fill buf, len and chan with the */
multiline_comment|/* appropriate data and return a nonzero value. With a zero return no new    */
multiline_comment|/* data to send is assumed. maxlen specifies the buffer size available for   */
multiline_comment|/* sending.                                                                  */
multiline_comment|/*****************************************************************************/
r_int
DECL|function|hysdn_sched_tx
id|hysdn_sched_tx
c_func
(paren
id|hysdn_card
op_star
id|card
comma
id|uchar
op_star
id|buf
comma
id|word
r_volatile
op_star
id|len
comma
id|word
r_volatile
op_star
id|chan
comma
id|word
id|maxlen
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;net_tx_busy
)paren
(brace
id|card-&gt;net_tx_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reset flag */
id|hysdn_tx_netack
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* acknowledge packet send */
)brace
multiline_comment|/* a network packet has completely been transferred */
multiline_comment|/* first of all async requests are handled */
r_if
c_cond
(paren
id|card-&gt;async_busy
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;async_len
op_le
id|maxlen
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|card-&gt;async_data
comma
id|card-&gt;async_len
)paren
suffix:semicolon
op_star
id|len
op_assign
id|card-&gt;async_len
suffix:semicolon
op_star
id|chan
op_assign
id|card-&gt;async_channel
suffix:semicolon
id|card-&gt;async_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reset request */
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|card-&gt;async_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* in case of length error */
)brace
multiline_comment|/* async request */
r_if
c_cond
(paren
(paren
id|card-&gt;err_log_state
op_eq
id|ERRLOG_STATE_START
)paren
op_logical_and
(paren
id|maxlen
op_ge
id|ERRLOG_CMD_REQ_SIZE
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
id|ERRLOG_CMD_REQ
)paren
suffix:semicolon
multiline_comment|/* copy the command */
op_star
id|len
op_assign
id|ERRLOG_CMD_REQ_SIZE
suffix:semicolon
multiline_comment|/* buffer length */
op_star
id|chan
op_assign
id|CHAN_ERRLOG
suffix:semicolon
multiline_comment|/* and channel */
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_ON
suffix:semicolon
multiline_comment|/* new state is on */
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* tell that data should be send */
)brace
multiline_comment|/* error log start and able to send */
r_if
c_cond
(paren
(paren
id|card-&gt;err_log_state
op_eq
id|ERRLOG_STATE_STOP
)paren
op_logical_and
(paren
id|maxlen
op_ge
id|ERRLOG_CMD_STOP_SIZE
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
id|ERRLOG_CMD_STOP
)paren
suffix:semicolon
multiline_comment|/* copy the command */
op_star
id|len
op_assign
id|ERRLOG_CMD_STOP_SIZE
suffix:semicolon
multiline_comment|/* buffer length */
op_star
id|chan
op_assign
id|CHAN_ERRLOG
suffix:semicolon
multiline_comment|/* and channel */
id|card-&gt;err_log_state
op_assign
id|ERRLOG_STATE_OFF
suffix:semicolon
multiline_comment|/* new state is off */
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* tell that data should be send */
)brace
multiline_comment|/* error log start and able to send */
multiline_comment|/* now handle network interface packets */
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|hysdn_tx_netget
c_func
(paren
id|card
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
op_le
id|maxlen
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* copy the packet to the buffer */
op_star
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
op_star
id|chan
op_assign
id|CHAN_NDIS_DATA
suffix:semicolon
id|card-&gt;net_tx_busy
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we are busy sending network data */
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* go and send the data */
)brace
r_else
id|hysdn_tx_netack
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* aknowledge packet -&gt; throw away */
)brace
multiline_comment|/* send a network packet if available */
macro_line|#ifdef CONFIG_HYSDN_CAPI
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|hycapi_tx_capiget
c_func
(paren
id|card
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|skb-&gt;len
op_le
id|maxlen
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
op_star
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
op_star
id|chan
op_assign
id|CHAN_CAPI
suffix:semicolon
id|hycapi_tx_capiack
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* go and send the data */
)brace
)brace
macro_line|#endif /* CONFIG_HYSDN_CAPI */
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* nothing to send */
)brace
multiline_comment|/* hysdn_sched_tx */
multiline_comment|/*****************************************************************************/
multiline_comment|/* send one config line to the card and return 0 if successfull, otherwise a */
multiline_comment|/* negative error code.                                                      */
multiline_comment|/* The function works with timeouts perhaps not giving the greatest speed    */
multiline_comment|/* sending the line, but this should be meaningless beacuse only some lines  */
multiline_comment|/* are to be sent and this happens very seldom.                              */
multiline_comment|/*****************************************************************************/
r_int
DECL|function|hysdn_tx_cfgline
id|hysdn_tx_cfgline
c_func
(paren
id|hysdn_card
op_star
id|card
comma
id|uchar
op_star
id|line
comma
id|word
id|chan
)paren
(brace
r_int
id|cnt
op_assign
l_int|50
suffix:semicolon
multiline_comment|/* timeout intervalls */
id|ulong
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_SCHED_ASYN
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;async tx-cfg chan=%d len=%d&quot;
comma
id|chan
comma
id|strlen
c_func
(paren
id|line
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|card-&gt;async_busy
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_SCHED_ASYN
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;async tx-cfg delayed&quot;
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|20
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 20ms */
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|cnt
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_ASYNC_TIME
)paren
suffix:semicolon
multiline_comment|/* timed out */
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* wait for buffer to become free */
id|strcpy
c_func
(paren
id|card-&gt;async_data
comma
id|line
)paren
suffix:semicolon
id|card-&gt;async_len
op_assign
id|strlen
c_func
(paren
id|line
)paren
op_plus
l_int|1
suffix:semicolon
id|card-&gt;async_channel
op_assign
id|chan
suffix:semicolon
id|card-&gt;async_busy
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* request transfer */
multiline_comment|/* now queue the task */
id|queue_task
c_func
(paren
op_amp
id|card-&gt;irq_queue
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_SCHED_ASYN
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;async tx-cfg data queued&quot;
)paren
suffix:semicolon
id|cnt
op_increment
suffix:semicolon
multiline_comment|/* short delay */
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|card-&gt;async_busy
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_SCHED_ASYN
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;async tx-cfg waiting for tx-ready&quot;
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|20
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 20ms */
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|cnt
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_ASYNC_TIME
)paren
suffix:semicolon
multiline_comment|/* timed out */
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* wait for buffer to become free again */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
id|LOG_SCHED_ASYN
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;async tx-cfg data send&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* line send correctly */
)brace
multiline_comment|/* hysdn_tx_cfgline */
eof
