multiline_comment|/*&n; * linux/drivers/i2c/pcf8583.c&n; *&n; * Copyright (C) 2000 Russell King&n; *&n; * Driver for PCF8583 RTC &amp; RAM chip&n; */
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pcf8583.h&quot;
DECL|variable|pcf8583_driver
r_static
r_struct
id|i2c_driver
id|pcf8583_driver
suffix:semicolon
DECL|variable|ignore
r_static
r_int
r_int
id|ignore
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_addr
r_static
r_int
r_int
id|normal_addr
(braket
)braket
op_assign
(brace
l_int|0x50
comma
l_int|0x51
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_client_address_data
id|addr_data
op_assign
(brace
id|force
suffix:colon
id|ignore
comma
id|ignore
suffix:colon
id|ignore
comma
id|ignore_range
suffix:colon
id|ignore
comma
id|normal_i2c
suffix:colon
id|ignore
comma
id|normal_i2c_range
suffix:colon
id|normal_addr
comma
id|probe
suffix:colon
id|ignore
comma
id|probe_range
suffix:colon
id|ignore
)brace
suffix:semicolon
DECL|macro|DAT
mdefine_line|#define DAT(x) ((unsigned int)(x-&gt;data))
r_static
r_int
DECL|function|pcf8583_attach
id|pcf8583_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|addr
comma
r_int
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
r_struct
id|i2c_client
op_star
id|c
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|1
)braket
comma
id|ad
(braket
l_int|1
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|addr
comma
l_int|0
comma
l_int|1
comma
id|ad
)brace
comma
(brace
id|addr
comma
id|I2C_M_RD
comma
l_int|1
comma
id|buf
)brace
)brace
suffix:semicolon
id|c
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|c
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|strcpy
c_func
(paren
id|c-&gt;name
comma
l_string|&quot;PCF8583&quot;
)paren
suffix:semicolon
id|c-&gt;id
op_assign
id|pcf8583_driver.id
suffix:semicolon
id|c-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|c-&gt;addr
op_assign
id|addr
suffix:semicolon
id|c-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|c-&gt;driver
op_assign
op_amp
id|pcf8583_driver
suffix:semicolon
id|c-&gt;data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_eq
l_int|2
)paren
id|DAT
c_func
(paren
id|c
)paren
op_assign
id|buf
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|i2c_attach_client
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_probe
id|pcf8583_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|pcf8583_attach
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_detach
id|pcf8583_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_get_datetime
id|pcf8583_get_datetime
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|rtc_tm
op_star
id|dt
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|8
)braket
comma
id|addr
(braket
l_int|1
)braket
op_assign
(brace
l_int|1
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|client-&gt;addr
comma
l_int|0
comma
l_int|1
comma
id|addr
)brace
comma
(brace
id|client-&gt;addr
comma
id|I2C_M_RD
comma
l_int|6
comma
id|buf
)brace
)brace
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
c_func
(paren
id|client-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_eq
l_int|2
)paren
(brace
id|dt-&gt;year_off
op_assign
id|buf
(braket
l_int|4
)braket
op_rshift
l_int|6
suffix:semicolon
id|dt-&gt;wday
op_assign
id|buf
(braket
l_int|5
)braket
op_rshift
l_int|5
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_and_assign
l_int|0x3f
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_and_assign
l_int|0x1f
suffix:semicolon
id|dt-&gt;cs
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|dt-&gt;secs
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|dt-&gt;mins
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|dt-&gt;hours
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|dt-&gt;mday
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|dt-&gt;mon
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buf
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_set_datetime
id|pcf8583_set_datetime
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|rtc_tm
op_star
id|dt
comma
r_int
id|datetoo
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|ret
comma
id|len
op_assign
l_int|6
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|DAT
c_func
(paren
id|client
)paren
op_or
l_int|0x80
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;cs
)paren
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;secs
)paren
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;mins
)paren
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;hours
)paren
suffix:semicolon
r_if
c_cond
(paren
id|datetoo
)paren
(brace
id|len
op_assign
l_int|8
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;mday
)paren
op_or
(paren
id|dt-&gt;year_off
op_lshift
l_int|6
)paren
suffix:semicolon
id|buf
(braket
l_int|7
)braket
op_assign
id|BIN_TO_BCD
c_func
(paren
id|dt-&gt;mon
)paren
op_or
(paren
id|dt-&gt;wday
op_lshift
l_int|5
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|i2c_master_send
c_func
(paren
id|client
comma
(paren
r_char
op_star
)paren
id|buf
comma
id|len
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|DAT
c_func
(paren
id|client
)paren
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
(paren
r_char
op_star
)paren
id|buf
comma
l_int|2
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_get_ctrl
id|pcf8583_get_ctrl
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_char
op_star
id|ctrl
)paren
(brace
op_star
id|ctrl
op_assign
id|DAT
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_set_ctrl
id|pcf8583_set_ctrl
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_char
op_star
id|ctrl
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
op_star
id|ctrl
suffix:semicolon
id|DAT
c_func
(paren
id|client
)paren
op_assign
op_star
id|ctrl
suffix:semicolon
r_return
id|i2c_master_send
c_func
(paren
id|client
comma
(paren
r_char
op_star
)paren
id|buf
comma
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_read_mem
id|pcf8583_read_mem
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|mem
op_star
id|mem
)paren
(brace
r_int
r_char
id|addr
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|client-&gt;addr
comma
l_int|0
comma
l_int|1
comma
id|addr
)brace
comma
(brace
id|client-&gt;addr
comma
id|I2C_M_RD
comma
l_int|0
comma
id|mem-&gt;data
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;loc
OL
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr
(braket
l_int|0
)braket
op_assign
id|mem-&gt;loc
suffix:semicolon
id|msgs
(braket
l_int|1
)braket
dot
id|len
op_assign
id|mem-&gt;nr
suffix:semicolon
r_return
id|i2c_transfer
c_func
(paren
id|client-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_eq
l_int|2
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_write_mem
id|pcf8583_write_mem
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|mem
op_star
id|mem
)paren
(brace
r_int
r_char
id|addr
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|client-&gt;addr
comma
l_int|0
comma
l_int|1
comma
id|addr
)brace
comma
(brace
id|client-&gt;addr
comma
l_int|0
comma
l_int|0
comma
id|mem-&gt;data
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;loc
OL
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|addr
(braket
l_int|0
)braket
op_assign
id|mem-&gt;loc
suffix:semicolon
id|msgs
(braket
l_int|1
)braket
dot
id|len
op_assign
id|mem-&gt;nr
suffix:semicolon
r_return
id|i2c_transfer
c_func
(paren
id|client-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_eq
l_int|2
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_int
DECL|function|pcf8583_command
id|pcf8583_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_GETDATETIME
suffix:colon
r_return
id|pcf8583_get_datetime
c_func
(paren
id|client
comma
id|arg
)paren
suffix:semicolon
r_case
id|RTC_SETTIME
suffix:colon
r_return
id|pcf8583_set_datetime
c_func
(paren
id|client
comma
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_case
id|RTC_SETDATETIME
suffix:colon
r_return
id|pcf8583_set_datetime
c_func
(paren
id|client
comma
id|arg
comma
l_int|1
)paren
suffix:semicolon
r_case
id|RTC_GETCTRL
suffix:colon
r_return
id|pcf8583_get_ctrl
c_func
(paren
id|client
comma
id|arg
)paren
suffix:semicolon
r_case
id|RTC_SETCTRL
suffix:colon
r_return
id|pcf8583_set_ctrl
c_func
(paren
id|client
comma
id|arg
)paren
suffix:semicolon
r_case
id|MEM_READ
suffix:colon
r_return
id|pcf8583_read_mem
c_func
(paren
id|client
comma
id|arg
)paren
suffix:semicolon
r_case
id|MEM_WRITE
suffix:colon
r_return
id|pcf8583_write_mem
c_func
(paren
id|client
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|variable|pcf8583_driver
r_static
r_struct
id|i2c_driver
id|pcf8583_driver
op_assign
(brace
l_string|&quot;PCF8583&quot;
comma
id|I2C_DRIVERID_PCF8583
comma
id|I2C_DF_NOTIFY
comma
id|pcf8583_probe
comma
id|pcf8583_detach
comma
id|pcf8583_command
)brace
suffix:semicolon
DECL|function|pcf8583_init
r_static
id|__init
r_int
id|pcf8583_init
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|pcf8583_driver
)paren
suffix:semicolon
)brace
DECL|variable|pcf8583_init
id|__initcall
c_func
(paren
id|pcf8583_init
)paren
suffix:semicolon
eof
