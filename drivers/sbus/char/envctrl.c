multiline_comment|/* $Id: envctrl.c,v 1.3 1998/04/10 08:42:24 jj Exp $&n; * envctrl.c: Temperature and Fan monitoring on Machines providing it.&n; *&n; * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
DECL|macro|PCF8584_ADDRESS
mdefine_line|#define PCF8584_ADDRESS&t;0x55
DECL|macro|CONTROL_PIN
mdefine_line|#define CONTROL_PIN&t;0x80
DECL|macro|CONTROL_ES0
mdefine_line|#define CONTROL_ES0&t;0x40
DECL|macro|CONTROL_ES1
mdefine_line|#define CONTROL_ES1&t;0x20
DECL|macro|CONTROL_ES2
mdefine_line|#define CONTROL_ES2&t;0x10
DECL|macro|CONTROL_ENI
mdefine_line|#define CONTROL_ENI&t;0x08
DECL|macro|CONTROL_STA
mdefine_line|#define CONTROL_STA&t;0x04
DECL|macro|CONTROL_STO
mdefine_line|#define CONTROL_STO&t;0x02
DECL|macro|CONTROL_ACK
mdefine_line|#define CONTROL_ACK&t;0x01
DECL|macro|STATUS_PIN
mdefine_line|#define STATUS_PIN&t;0x80
DECL|macro|STATUS_STS
mdefine_line|#define STATUS_STS&t;0x20
DECL|macro|STATUS_BER
mdefine_line|#define STATUS_BER&t;0x10
DECL|macro|STATUS_LRB
mdefine_line|#define STATUS_LRB&t;0x08
DECL|macro|STATUS_AD0
mdefine_line|#define STATUS_AD0&t;0x08
DECL|macro|STATUS_AAB
mdefine_line|#define STATUS_AAB&t;0x04
DECL|macro|STATUS_LAB
mdefine_line|#define STATUS_LAB&t;0x02
DECL|macro|STATUS_BB
mdefine_line|#define STATUS_BB&t;0x01
multiline_comment|/*&n; * CLK Mode Register.&n; */
DECL|macro|BUS_CLK_90
mdefine_line|#define BUS_CLK_90&t;0x00
DECL|macro|BUS_CLK_45
mdefine_line|#define BUS_CLK_45&t;0x01
DECL|macro|BUS_CLK_11
mdefine_line|#define BUS_CLK_11&t;0x02
DECL|macro|BUS_CLK_1_5
mdefine_line|#define BUS_CLK_1_5&t;0x03
DECL|macro|CLK_3
mdefine_line|#define CLK_3&t;&t;0x00
DECL|macro|CLK_4_43
mdefine_line|#define CLK_4_43&t;0x10
DECL|macro|CLK_6
mdefine_line|#define CLK_6&t;&t;0x14
DECL|macro|CLK_8
mdefine_line|#define CLK_8&t;&t;0x18
DECL|macro|CLK_12
mdefine_line|#define CLK_12&t;&t;0x1c
DECL|macro|I2C_WRITE
mdefine_line|#define I2C_WRITE&t;0x00
DECL|macro|I2C_READ
mdefine_line|#define I2C_READ&t;0x01
DECL|struct|pcf8584_reg
r_struct
id|pcf8584_reg
(brace
DECL|member|data
id|__volatile__
r_int
r_char
id|data
suffix:semicolon
DECL|member|csr
id|__volatile__
r_int
r_char
id|csr
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|i2c
r_static
r_struct
id|pcf8584_reg
op_star
id|i2c
suffix:semicolon
DECL|struct|i2c_addr_map
r_struct
id|i2c_addr_map
(brace
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
DECL|member|mask
r_int
r_char
id|mask
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|devmap
r_static
r_struct
id|i2c_addr_map
id|devmap
(braket
)braket
op_assign
(brace
(brace
l_int|0x38
comma
l_int|0x78
comma
l_string|&quot;PCF8574A&quot;
)brace
comma
(brace
l_int|0x20
comma
l_int|0x78
comma
l_string|&quot;TDA8444&quot;
)brace
comma
(brace
l_int|0x48
comma
l_int|0x78
comma
l_string|&quot;PCF8591&quot;
)brace
comma
)brace
suffix:semicolon
DECL|macro|NR_DEVMAP
mdefine_line|#define NR_DEVMAP (sizeof(devmap) / sizeof(devmap[0]))
r_static
r_int
DECL|function|envctrl_read
id|envctrl_read
c_func
(paren
r_int
r_char
id|dev
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|dummy
suffix:semicolon
r_int
r_char
id|stat
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
id|count
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|i2c-&gt;data
op_assign
(paren
id|dev
op_lshift
l_int|1
)paren
op_or
id|I2C_READ
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|i2c-&gt;csr
op_amp
id|STATUS_BB
)paren
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES0
op_or
id|CONTROL_STA
op_or
id|CONTROL_ACK
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|stat
op_assign
id|i2c-&gt;csr
)paren
op_amp
id|STATUS_PIN
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|STATUS_LRB
)paren
r_goto
id|stop
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
(paren
id|len
op_minus
l_int|2
)paren
)paren
r_goto
id|final
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OG
l_int|0
)paren
op_star
id|buffer
op_increment
op_assign
id|i2c-&gt;data
suffix:semicolon
r_else
id|dummy
op_assign
id|i2c-&gt;data
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|final
suffix:colon
id|i2c-&gt;csr
op_assign
id|CONTROL_ES0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OG
l_int|0
)paren
op_star
id|buffer
op_increment
op_assign
id|i2c-&gt;data
suffix:semicolon
r_else
id|dummy
op_assign
id|i2c-&gt;data
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|stat
op_assign
id|i2c-&gt;csr
)paren
op_amp
id|STATUS_PIN
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|stop
suffix:colon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES0
op_or
id|CONTROL_STO
op_or
id|CONTROL_ACK
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OG
l_int|0
)paren
op_star
id|buffer
op_increment
op_assign
id|i2c-&gt;data
suffix:semicolon
r_else
id|dummy
op_assign
id|i2c-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|envctrl_write
id|envctrl_write
c_func
(paren
r_int
r_char
id|dev
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
(brace
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|i2c-&gt;csr
op_amp
id|STATUS_BB
)paren
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c-&gt;data
op_assign
(paren
id|dev
op_lshift
l_int|1
)paren
op_or
id|I2C_WRITE
suffix:semicolon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES0
op_or
id|CONTROL_STA
op_or
id|CONTROL_ACK
suffix:semicolon
r_do
(brace
r_int
r_char
id|stat
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|stat
op_assign
id|i2c-&gt;csr
)paren
op_amp
id|STATUS_PIN
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|STATUS_LRB
)paren
r_goto
id|stop
suffix:semicolon
id|error
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
id|len
)paren
r_goto
id|stop
suffix:semicolon
id|i2c-&gt;data
op_assign
op_star
id|buffer
op_increment
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|stop
suffix:colon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES0
op_or
id|CONTROL_STO
op_or
id|CONTROL_ACK
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_int
id|scan_bus
c_func
(paren
r_void
)paren
)paren
(brace
r_int
r_char
id|dev
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* scan */
r_for
c_loop
(paren
id|dev
op_assign
l_int|1
suffix:semicolon
id|dev
OL
l_int|128
suffix:semicolon
id|dev
op_increment
)paren
r_if
c_cond
(paren
id|envctrl_write
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_DEVMAP
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|dev
op_amp
id|devmap
(braket
id|i
)braket
dot
id|mask
)paren
op_eq
id|devmap
(braket
id|i
)braket
dot
id|addr
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;envctrl: i2c device at %02x: %s&bslash;n&quot;
comma
id|dev
comma
id|i
OL
id|NR_DEVMAP
ques
c_cond
id|devmap
(braket
id|i
)braket
dot
id|name
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
(brace
r_int
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|envctrl_read
c_func
(paren
id|dev
comma
id|buf
comma
l_int|4
)paren
op_eq
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;envctrl: read %02x %02x %02x %02x&bslash;n&quot;
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
id|count
op_increment
suffix:semicolon
)brace
r_return
id|count
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_int
id|envctrl_init
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
macro_line|#ifdef CONFIG_PCI
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
suffix:semicolon
id|for_all_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;SUNW,envctrl&quot;
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|edev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|edev-&gt;base_address
(braket
l_int|0
)braket
comma
r_sizeof
(paren
op_star
id|i2c
)paren
)paren
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;%s: Can&squot;t get region %lx, %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|edev-&gt;base_address
(braket
l_int|0
)braket
comma
r_sizeof
(paren
op_star
id|i2c
)paren
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|edev-&gt;base_address
(braket
l_int|0
)braket
comma
r_sizeof
(paren
op_star
id|i2c
)paren
comma
l_string|&quot;i2c&quot;
)paren
suffix:semicolon
id|i2c
op_assign
(paren
r_struct
id|pcf8584_reg
op_star
)paren
id|edev-&gt;base_address
(braket
l_int|0
)braket
suffix:semicolon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
suffix:semicolon
id|i2c-&gt;data
op_assign
id|PCF8584_ADDRESS
suffix:semicolon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES1
suffix:semicolon
id|i2c-&gt;data
op_assign
id|CLK_4_43
op_or
id|BUS_CLK_90
suffix:semicolon
id|i2c-&gt;csr
op_assign
id|CONTROL_PIN
op_or
id|CONTROL_ES0
op_or
id|CONTROL_ACK
suffix:semicolon
id|udelay
c_func
(paren
l_int|10000
)paren
suffix:semicolon
r_return
id|scan_bus
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
eof
