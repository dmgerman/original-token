multiline_comment|/* paride.h&t;(c) 1997  Grant R. Guenther &lt;grant@torque.net&gt;&n;   &t;&t;          Under the terms of the GPL.&n;&n;   This file defines the interface between the high-level parallel&n;   IDE device drivers (pd, pf, pcd, pt) and the adapter chips.&n;&n;*/
DECL|macro|PARIDE_H_VERSION
mdefine_line|#define PARIDE_H_VERSION &t;&quot;1.0&quot;
multiline_comment|/* Some adapters need to know what kind of device they are in&n;&n;   Values for devtype:&n;*/
DECL|macro|PI_PD
mdefine_line|#define&t;PI_PD&t;0&t;/* IDE disk */
DECL|macro|PI_PCD
mdefine_line|#define PI_PCD&t;1&t;/* ATAPI CDrom */
DECL|macro|PI_PF
mdefine_line|#define PI_PF   2&t;/* ATAPI disk */
DECL|macro|PI_PT
mdefine_line|#define PI_PT&t;3&t;/* ATAPI tape */
multiline_comment|/* The paride module contains no state, instead the drivers allocate&n;   a pi_adapter data structure and pass it to paride in every operation.&n;&n;*/
DECL|struct|pi_adapter
r_struct
id|pi_adapter
(brace
DECL|member|proto
r_struct
id|pi_protocol
op_star
id|proto
suffix:semicolon
multiline_comment|/* adapter protocol */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* base address of parallel port */
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* transfer mode in use */
DECL|member|delay
r_int
id|delay
suffix:semicolon
multiline_comment|/* adapter delay setting */
DECL|member|devtype
r_int
id|devtype
suffix:semicolon
multiline_comment|/* device type: PI_PD etc. */
DECL|member|device
r_char
op_star
id|device
suffix:semicolon
multiline_comment|/* name of driver */
DECL|member|unit
r_int
id|unit
suffix:semicolon
multiline_comment|/* unit number for chained adapters */
DECL|member|saved_r0
r_int
id|saved_r0
suffix:semicolon
multiline_comment|/* saved port state */
DECL|member|saved_r2
r_int
id|saved_r2
suffix:semicolon
multiline_comment|/* saved port state */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* number of ports reserved */
DECL|member|private
r_int
r_private
suffix:semicolon
multiline_comment|/* for protocol module */
DECL|member|parq
r_struct
id|wait_queue
op_star
id|parq
suffix:semicolon
multiline_comment|/* semaphore for parport sharing */
DECL|member|pardev
r_void
op_star
id|pardev
suffix:semicolon
multiline_comment|/* pointer to pardevice */
DECL|member|parname
r_char
op_star
id|parname
suffix:semicolon
multiline_comment|/* parport name */
DECL|member|claimed
r_int
id|claimed
suffix:semicolon
multiline_comment|/* parport has already been claimed */
DECL|member|claim_cont
r_void
(paren
op_star
id|claim_cont
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* continuation for parport wait */
)brace
suffix:semicolon
DECL|typedef|PIA
r_typedef
r_struct
id|pi_adapter
id|PIA
suffix:semicolon
multiline_comment|/* functions exported by paride to the high level drivers */
r_extern
r_int
id|pi_init
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|autoprobe
comma
multiline_comment|/* 1 to autoprobe */
r_int
id|port
comma
multiline_comment|/* base port address */
r_int
id|mode
comma
multiline_comment|/* -1 for autoprobe */
r_int
id|unit
comma
multiline_comment|/* unit number, if supported */
r_int
id|protocol
comma
multiline_comment|/* protocol to use */
r_int
id|delay
comma
multiline_comment|/* -1 to use adapter specific default */
r_char
op_star
id|scratch
comma
multiline_comment|/* address of 512 byte buffer */
r_int
id|devtype
comma
multiline_comment|/* device type: PI_PD, PI_PCD, etc ... */
r_int
id|verbose
comma
multiline_comment|/* log verbose data while probing */
r_char
op_star
id|device
multiline_comment|/* name of the driver */
)paren
suffix:semicolon
multiline_comment|/* returns 0 on failure, 1 on success */
r_extern
r_void
id|pi_release
c_func
(paren
id|PIA
op_star
id|pi
)paren
suffix:semicolon
multiline_comment|/* registers are addressed as (cont,regr)&n;&n;       &t;cont: 0 for command register file, 1 for control register(s)&n;&t;regr: 0-7 for register number.&n;&n;*/
r_extern
r_void
id|pi_write_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
comma
r_int
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pi_read_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
)paren
suffix:semicolon
r_extern
r_void
id|pi_write_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|pi_read_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|pi_connect
c_func
(paren
id|PIA
op_star
id|pi
)paren
suffix:semicolon
r_extern
r_void
id|pi_disconnect
c_func
(paren
id|PIA
op_star
id|pi
)paren
suffix:semicolon
r_extern
r_void
id|pi_do_claimed
c_func
(paren
id|PIA
op_star
id|pi
comma
r_void
(paren
op_star
id|cont
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
multiline_comment|/* macros and functions exported to the protocol modules */
DECL|macro|delay_p
mdefine_line|#define delay_p&t;&t;&t;(pi-&gt;delay?udelay(pi-&gt;delay):0)
DECL|macro|out_p
mdefine_line|#define out_p(offs,byte)&t;outb(byte,pi-&gt;port+offs); delay_p;
DECL|macro|in_p
mdefine_line|#define in_p(offs)&t;&t;(delay_p,inb(pi-&gt;port+offs))
DECL|macro|w0
mdefine_line|#define w0(byte)                {out_p(0,byte);}
DECL|macro|r0
mdefine_line|#define r0()                    (in_p(0) &amp; 0xff)
DECL|macro|w1
mdefine_line|#define w1(byte)                {out_p(1,byte);}
DECL|macro|r1
mdefine_line|#define r1()                    (in_p(1) &amp; 0xff)
DECL|macro|w2
mdefine_line|#define w2(byte)                {out_p(2,byte);}
DECL|macro|r2
mdefine_line|#define r2()                    (in_p(2) &amp; 0xff)
DECL|macro|w3
mdefine_line|#define w3(byte)                {out_p(3,byte);}
DECL|macro|w4
mdefine_line|#define w4(byte)                {out_p(4,byte);}
DECL|macro|r4
mdefine_line|#define r4()                    (in_p(4) &amp; 0xff)
DECL|macro|w4w
mdefine_line|#define w4w(data)     &t;&t;{outw(data,pi-&gt;port+4); delay_p;}
DECL|macro|w4l
mdefine_line|#define w4l(data)     &t;&t;{outl(data,pi-&gt;port+4); delay_p;}
DECL|macro|r4w
mdefine_line|#define r4w()         &t;&t;(delay_p,inw(pi-&gt;port+4)&amp;0xffff)
DECL|macro|r4l
mdefine_line|#define r4l()         &t;&t;(delay_p,inl(pi-&gt;port+4)&amp;0xffffffff)
DECL|function|pi_swab16
r_static
r_inline
id|u16
id|pi_swab16
c_func
(paren
r_char
op_star
id|b
comma
r_int
id|k
)paren
(brace
r_union
(brace
id|u16
id|u
suffix:semicolon
r_char
id|t
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|r
suffix:semicolon
id|r.t
(braket
l_int|0
)braket
op_assign
id|b
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
suffix:semicolon
id|r.t
(braket
l_int|1
)braket
op_assign
id|b
(braket
l_int|2
op_star
id|k
)braket
suffix:semicolon
r_return
id|r.u
suffix:semicolon
)brace
DECL|function|pi_swab32
r_static
r_inline
id|u32
id|pi_swab32
c_func
(paren
r_char
op_star
id|b
comma
r_int
id|k
)paren
(brace
r_union
(brace
id|u32
id|u
suffix:semicolon
r_char
id|f
(braket
l_int|4
)braket
suffix:semicolon
)brace
id|r
suffix:semicolon
id|r.f
(braket
l_int|0
)braket
op_assign
id|b
(braket
l_int|4
op_star
id|k
op_plus
l_int|1
)braket
suffix:semicolon
id|r.f
(braket
l_int|1
)braket
op_assign
id|b
(braket
l_int|4
op_star
id|k
)braket
suffix:semicolon
id|r.f
(braket
l_int|2
)braket
op_assign
id|b
(braket
l_int|4
op_star
id|k
op_plus
l_int|3
)braket
suffix:semicolon
id|r.f
(braket
l_int|3
)braket
op_assign
id|b
(braket
l_int|4
op_star
id|k
op_plus
l_int|2
)braket
suffix:semicolon
r_return
id|r.u
suffix:semicolon
)brace
DECL|struct|pi_protocol
r_struct
id|pi_protocol
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* name for this protocol */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* index into protocol table */
DECL|member|max_mode
r_int
id|max_mode
suffix:semicolon
multiline_comment|/* max mode number */
DECL|member|epp_first
r_int
id|epp_first
suffix:semicolon
multiline_comment|/* modes &gt;= this use 8 ports */
DECL|member|default_delay
r_int
id|default_delay
suffix:semicolon
multiline_comment|/* delay parameter if not specified */
DECL|member|max_units
r_int
id|max_units
suffix:semicolon
multiline_comment|/* max chained units probed for */
DECL|member|write_regr
r_void
(paren
op_star
id|write_regr
)paren
(paren
id|PIA
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|read_regr
r_int
(paren
op_star
id|read_regr
)paren
(paren
id|PIA
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|write_block
r_void
(paren
op_star
id|write_block
)paren
(paren
id|PIA
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|read_block
r_void
(paren
op_star
id|read_block
)paren
(paren
id|PIA
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|connect
r_void
(paren
op_star
id|connect
)paren
(paren
id|PIA
op_star
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
id|PIA
op_star
)paren
suffix:semicolon
DECL|member|test_port
r_int
(paren
op_star
id|test_port
)paren
(paren
id|PIA
op_star
)paren
suffix:semicolon
DECL|member|probe_unit
r_int
(paren
op_star
id|probe_unit
)paren
(paren
id|PIA
op_star
)paren
suffix:semicolon
DECL|member|test_proto
r_int
(paren
op_star
id|test_proto
)paren
(paren
id|PIA
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|log_adapter
r_void
(paren
op_star
id|log_adapter
)paren
(paren
id|PIA
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|inc_use
r_void
(paren
op_star
id|inc_use
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|dec_use
r_void
(paren
op_star
id|dec_use
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|PIP
r_typedef
r_struct
id|pi_protocol
id|PIP
suffix:semicolon
r_extern
r_int
id|pi_register
c_func
(paren
id|PIP
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pi_unregister
(paren
id|PIP
op_star
)paren
suffix:semicolon
multiline_comment|/* end of paride.h */
eof