multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *      hfmodem.h  --  Linux soundcard HF FSK driver.&n; *&n; *      Copyright (C) 1997  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *        Swiss Federal Institute of Technology (ETH), Electronics Lab&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; *  This is the Linux realtime sound output driver&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _HFMODEM_H
DECL|macro|_HFMODEM_H
mdefine_line|#define _HFMODEM_H
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20100
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|HFMODEM_MINOR
mdefine_line|#define HFMODEM_MINOR         145
DECL|macro|HFMODEM_SRATE
mdefine_line|#define HFMODEM_SRATE        8000
DECL|macro|HFMODEM_MAXBITS
mdefine_line|#define HFMODEM_MAXBITS      4800   /* required for GTOR 300 baud mode */
DECL|macro|HFMODEM_MINBAUD
mdefine_line|#define HFMODEM_MINBAUD        40
DECL|macro|HFMODEM_MAXBAUD
mdefine_line|#define HFMODEM_MAXBAUD       400
DECL|macro|HFMODEM_MAXCORRLEN
mdefine_line|#define HFMODEM_MAXCORRLEN   ((HFMODEM_SRATE+HFMODEM_MINBAUD-1)/HFMODEM_MINBAUD)
multiline_comment|/* --------------------------------------------------------------------- */
DECL|typedef|hfmodem_time_t
r_typedef
r_int
r_int
id|hfmodem_time_t
suffix:semicolon
DECL|typedef|hfmodem_soft_t
r_typedef
r_int
id|hfmodem_soft_t
suffix:semicolon
DECL|typedef|hfmodem_id_t
r_typedef
r_int
r_int
id|hfmodem_id_t
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|hfmodem_ioctl_fsk_tx_request
r_struct
id|hfmodem_ioctl_fsk_tx_request
(brace
DECL|member|tstart
id|hfmodem_time_t
id|tstart
suffix:semicolon
DECL|member|tinc
id|hfmodem_time_t
id|tinc
suffix:semicolon
DECL|member|inv
r_int
id|inv
suffix:semicolon
DECL|member|id
id|hfmodem_id_t
id|id
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|freq
r_int
r_int
id|freq
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfmodem_ioctl_fsk_rx_request
r_struct
id|hfmodem_ioctl_fsk_rx_request
(brace
DECL|member|tstart
id|hfmodem_time_t
id|tstart
suffix:semicolon
DECL|member|tinc
id|hfmodem_time_t
id|tinc
suffix:semicolon
DECL|member|baud
r_int
r_int
id|baud
suffix:semicolon
DECL|member|id
id|hfmodem_id_t
id|id
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:semicolon
DECL|member|data
id|hfmodem_soft_t
op_star
id|data
suffix:semicolon
DECL|member|freq
r_int
r_int
id|freq
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfmodem_ioctl_mixer_params
r_struct
id|hfmodem_ioctl_mixer_params
(brace
DECL|member|src
r_int
id|src
suffix:semicolon
DECL|member|igain
r_int
id|igain
suffix:semicolon
DECL|member|ogain
r_int
id|ogain
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfmodem_ioctl_sample_params
r_struct
id|hfmodem_ioctl_sample_params
(brace
DECL|member|data
id|__s16
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HFMODEM_IOCTL_FSKTXREQUEST
mdefine_line|#define HFMODEM_IOCTL_FSKTXREQUEST    _IOW(&squot;H&squot;, 0, struct hfmodem_ioctl_fsk_tx_request)
DECL|macro|HFMODEM_IOCTL_FSKRXREQUEST
mdefine_line|#define HFMODEM_IOCTL_FSKRXREQUEST    _IOW(&squot;H&squot;, 1, struct hfmodem_ioctl_fsk_rx_request)
DECL|macro|HFMODEM_IOCTL_CLEARRQ
mdefine_line|#define HFMODEM_IOCTL_CLEARRQ         _IO(&squot;H&squot;,  3)
DECL|macro|HFMODEM_IOCTL_GETCURTIME
mdefine_line|#define HFMODEM_IOCTL_GETCURTIME      _IOR(&squot;H&squot;, 4, hfmodem_time_t)
DECL|macro|HFMODEM_IOCTL_WAITRQ
mdefine_line|#define HFMODEM_IOCTL_WAITRQ          _IOR(&squot;H&squot;, 5, hfmodem_id_t)
DECL|macro|HFMODEM_IOCTL_MIXERPARAMS
mdefine_line|#define HFMODEM_IOCTL_MIXERPARAMS     _IOW(&squot;H&squot;, 6, struct hfmodem_ioctl_mixer_params)
DECL|macro|HFMODEM_IOCTL_SAMPLESTART
mdefine_line|#define HFMODEM_IOCTL_SAMPLESTART     _IOW(&squot;H&squot;, 7, struct hfmodem_ioctl_sample_params)
DECL|macro|HFMODEM_IOCTL_SAMPLEFINISHED
mdefine_line|#define HFMODEM_IOCTL_SAMPLEFINISHED  _IO(&squot;H&squot;,  8)
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifdef __KERNEL__
DECL|macro|DMA_MODE_AUTOINIT
mdefine_line|#define DMA_MODE_AUTOINIT      0x10
DECL|macro|NR_DEVICE
mdefine_line|#define NR_DEVICE 1
DECL|macro|HFMODEM_FRAGSAMPLES
mdefine_line|#define HFMODEM_FRAGSAMPLES (HFMODEM_SRATE/100)
DECL|macro|HFMODEM_FRAGSIZE
mdefine_line|#define HFMODEM_FRAGSIZE    (HFMODEM_FRAGSAMPLES*2)
DECL|macro|HFMODEM_NUMFRAGS
mdefine_line|#define HFMODEM_NUMFRAGS    8
DECL|macro|HFMODEM_EXCESSFRAGS
mdefine_line|#define HFMODEM_EXCESSFRAGS 3
DECL|macro|HFMODEM_NUMRXSLOTS
mdefine_line|#define HFMODEM_NUMRXSLOTS 20
DECL|macro|HFMODEM_NUMTXSLOTS
mdefine_line|#define HFMODEM_NUMTXSLOTS 4
DECL|macro|HFMODEM_CORRELATOR_CACHE
mdefine_line|#define HFMODEM_CORRELATOR_CACHE 8
DECL|enum|slot_st
DECL|enumerator|ss_unused
DECL|enumerator|ss_ready
DECL|enumerator|ss_oper
DECL|enumerator|ss_retired
r_enum
id|slot_st
(brace
id|ss_unused
op_assign
l_int|0
comma
id|ss_ready
comma
id|ss_oper
comma
id|ss_retired
)brace
suffix:semicolon
DECL|typedef|hfmodem_conv_t
r_typedef
r_int
id|hfmodem_conv_t
suffix:semicolon
DECL|struct|hfmodem_state
r_struct
id|hfmodem_state
(brace
DECL|member|scops
r_const
r_struct
id|hfmodem_scops
op_star
id|scops
suffix:semicolon
multiline_comment|/* io params */
r_struct
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|dma
r_int
r_int
id|dma
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|io
)brace
id|io
suffix:semicolon
r_struct
(brace
DECL|member|seriobase
r_int
r_int
id|seriobase
suffix:semicolon
DECL|member|pariobase
r_int
r_int
id|pariobase
suffix:semicolon
DECL|member|midiiobase
r_int
r_int
id|midiiobase
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ptt_out
)brace
id|ptt_out
suffix:semicolon
r_struct
(brace
DECL|member|buf
id|__s16
op_star
id|buf
suffix:semicolon
DECL|member|lastfrag
r_int
r_int
id|lastfrag
suffix:semicolon
DECL|member|fragptr
r_int
r_int
id|fragptr
suffix:semicolon
DECL|member|last_dmaptr
r_int
r_int
id|last_dmaptr
suffix:semicolon
DECL|member|ptt_frames
r_int
id|ptt_frames
suffix:semicolon
DECL|member|dma
)brace
id|dma
suffix:semicolon
r_struct
(brace
DECL|member|last_tvusec
r_int
r_int
id|last_tvusec
suffix:semicolon
DECL|member|time_cnt
r_int
r_int
r_int
id|time_cnt
suffix:semicolon
DECL|member|lasttime
id|hfmodem_time_t
id|lasttime
suffix:semicolon
macro_line|#ifdef __i386__
DECL|member|starttime_lo
DECL|member|starttime_hi
r_int
r_int
id|starttime_lo
comma
id|starttime_hi
suffix:semicolon
macro_line|#endif /* __i386__ */
DECL|member|clk
)brace
id|clk
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
r_struct
(brace
DECL|member|kbuf
id|__s16
op_star
id|kbuf
suffix:semicolon
DECL|member|ubuf
id|__s16
op_star
id|ubuf
suffix:semicolon
DECL|member|kptr
id|__s16
op_star
id|kptr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|rem
r_int
id|rem
suffix:semicolon
DECL|member|sbuf
)brace
id|sbuf
suffix:semicolon
r_struct
(brace
DECL|member|last_time
id|hfmodem_time_t
id|last_time
suffix:semicolon
DECL|member|tx_phase
r_int
r_int
id|tx_phase
suffix:semicolon
DECL|struct|hfmodem_l1_rxslot
r_struct
id|hfmodem_l1_rxslot
(brace
DECL|member|state
r_enum
id|slot_st
id|state
suffix:semicolon
DECL|member|tstart
DECL|member|tinc
id|hfmodem_time_t
id|tstart
comma
id|tinc
suffix:semicolon
DECL|member|data
id|hfmodem_soft_t
op_star
id|data
suffix:semicolon
DECL|member|userdata
id|hfmodem_soft_t
op_star
id|userdata
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:semicolon
DECL|member|cntbits
r_int
r_int
id|cntbits
suffix:semicolon
DECL|member|id
id|hfmodem_id_t
id|id
suffix:semicolon
DECL|member|corrlen
r_int
r_int
id|corrlen
suffix:semicolon
DECL|member|scale
id|hfmodem_conv_t
id|scale
suffix:semicolon
DECL|member|corr_cache
r_int
r_int
id|corr_cache
suffix:semicolon
DECL|member|rxslots
)brace
id|rxslots
(braket
id|HFMODEM_NUMRXSLOTS
)braket
suffix:semicolon
DECL|struct|hfmodem_l1_txslot
r_struct
id|hfmodem_l1_txslot
(brace
DECL|member|state
r_enum
id|slot_st
id|state
suffix:semicolon
DECL|member|tstart
DECL|member|tinc
id|hfmodem_time_t
id|tstart
comma
id|tinc
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:semicolon
DECL|member|cntbits
r_int
r_int
id|cntbits
suffix:semicolon
DECL|member|id
id|hfmodem_id_t
id|id
suffix:semicolon
DECL|member|inv
r_int
r_char
id|inv
suffix:semicolon
DECL|member|phinc
r_int
r_int
id|phinc
suffix:semicolon
DECL|member|phase_incs
r_int
r_int
id|phase_incs
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|txslots
)brace
id|txslots
(braket
id|HFMODEM_NUMTXSLOTS
)braket
suffix:semicolon
DECL|member|l1
)brace
id|l1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfmodem_correlator_cache
r_struct
id|hfmodem_correlator_cache
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
DECL|member|lru
r_int
id|lru
suffix:semicolon
DECL|member|phase_incs
r_int
r_int
id|phase_incs
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|correlator
id|hfmodem_conv_t
id|correlator
(braket
l_int|2
)braket
(braket
l_int|2
)braket
(braket
id|HFMODEM_MAXCORRLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hfmodem_scops
r_struct
id|hfmodem_scops
(brace
DECL|member|extent
r_int
r_int
id|extent
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|prepare_input
r_void
(paren
op_star
id|prepare_input
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|trigger_input
r_void
(paren
op_star
id|trigger_input
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|prepare_output
r_void
(paren
op_star
id|prepare_output
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|trigger_output
r_void
(paren
op_star
id|trigger_output
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|intack
r_int
r_int
(paren
op_star
id|intack
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
DECL|member|mixer
r_void
(paren
op_star
id|mixer
)paren
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
r_int
id|src
comma
r_int
id|igain
comma
r_int
id|ogain
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
r_extern
r_int
id|hfmodem_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20100
r_extern
r_int
r_int
id|hfmodem_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
id|hfmodem_select
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|hfmodem_clear_rq
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_input_samples
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
id|hfmodem_time_t
id|tstart
comma
id|hfmodem_time_t
id|tinc
comma
id|__s16
op_star
id|samples
)paren
suffix:semicolon
r_extern
r_int
id|hfmodem_output_samples
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
id|hfmodem_time_t
id|tstart
comma
id|hfmodem_time_t
id|tinc
comma
id|__s16
op_star
id|samples
)paren
suffix:semicolon
r_extern
r_int
id|hfmodem_next_tx_event
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
id|hfmodem_time_t
id|curr
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_finish_pending_rx_requests
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_wakeup
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hfmodem_sbcprobe
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|hfmodem_wssprobe
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_refclock_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_refclock_init
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|hfmodem_time_t
id|hfmodem_refclock_current
c_func
(paren
r_struct
id|hfmodem_state
op_star
id|dev
comma
id|hfmodem_time_t
id|expected
comma
r_int
id|exp_valid
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
r_extern
r_const
r_char
id|hfmodem_drvname
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|hfmodem_drvinfo
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|hfmodem_state
id|hfmodem_state
(braket
id|NR_DEVICE
)braket
suffix:semicolon
r_extern
r_struct
id|hfmodem_correlator_cache
id|hfmodem_correlator_cache
(braket
id|HFMODEM_CORRELATOR_CACHE
)braket
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* _HFMODEM_H */
eof