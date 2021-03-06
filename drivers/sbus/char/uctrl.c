multiline_comment|/* $Id: uctrl.c,v 1.9 2000/11/08 05:04:06 davem Exp $&n; * uctrl.c: TS102 Microcontroller interface on Tadpole Sparcbook 3&n; *&n; * Copyright 1999 Derrick J Brashear (shadow@dementia.org)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
DECL|macro|UCTRL_MINOR
mdefine_line|#define UCTRL_MINOR&t;174
DECL|macro|DEBUG
mdefine_line|#define DEBUG 1
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(x) printk x
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x)
macro_line|#endif
DECL|struct|uctrl_regs
r_struct
id|uctrl_regs
(brace
DECL|member|uctrl_intr
r_volatile
id|u32
id|uctrl_intr
suffix:semicolon
DECL|member|uctrl_data
r_volatile
id|u32
id|uctrl_data
suffix:semicolon
DECL|member|uctrl_stat
r_volatile
id|u32
id|uctrl_stat
suffix:semicolon
DECL|member|uctrl_xxx
r_volatile
id|u32
id|uctrl_xxx
(braket
l_int|5
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ts102_regs
r_struct
id|ts102_regs
(brace
DECL|member|card_a_intr
r_volatile
id|u32
id|card_a_intr
suffix:semicolon
DECL|member|card_a_stat
r_volatile
id|u32
id|card_a_stat
suffix:semicolon
DECL|member|card_a_ctrl
r_volatile
id|u32
id|card_a_ctrl
suffix:semicolon
DECL|member|card_a_xxx
r_volatile
id|u32
id|card_a_xxx
suffix:semicolon
DECL|member|card_b_intr
r_volatile
id|u32
id|card_b_intr
suffix:semicolon
DECL|member|card_b_stat
r_volatile
id|u32
id|card_b_stat
suffix:semicolon
DECL|member|card_b_ctrl
r_volatile
id|u32
id|card_b_ctrl
suffix:semicolon
DECL|member|card_b_xxx
r_volatile
id|u32
id|card_b_xxx
suffix:semicolon
DECL|member|uctrl_intr
r_volatile
id|u32
id|uctrl_intr
suffix:semicolon
DECL|member|uctrl_data
r_volatile
id|u32
id|uctrl_data
suffix:semicolon
DECL|member|uctrl_stat
r_volatile
id|u32
id|uctrl_stat
suffix:semicolon
DECL|member|uctrl_xxx
r_volatile
id|u32
id|uctrl_xxx
suffix:semicolon
DECL|member|ts102_xxx
r_volatile
id|u32
id|ts102_xxx
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits for uctrl_intr register */
DECL|macro|UCTRL_INTR_TXE_REQ
mdefine_line|#define UCTRL_INTR_TXE_REQ         0x01    /* transmit FIFO empty int req */
DECL|macro|UCTRL_INTR_TXNF_REQ
mdefine_line|#define UCTRL_INTR_TXNF_REQ        0x02    /* transmit FIFO not full int req */
DECL|macro|UCTRL_INTR_RXNE_REQ
mdefine_line|#define UCTRL_INTR_RXNE_REQ        0x04    /* receive FIFO not empty int req */
DECL|macro|UCTRL_INTR_RXO_REQ
mdefine_line|#define UCTRL_INTR_RXO_REQ         0x08    /* receive FIFO overflow int req */
DECL|macro|UCTRL_INTR_TXE_MSK
mdefine_line|#define UCTRL_INTR_TXE_MSK         0x10    /* transmit FIFO empty mask */
DECL|macro|UCTRL_INTR_TXNF_MSK
mdefine_line|#define UCTRL_INTR_TXNF_MSK        0x20    /* transmit FIFO not full mask */
DECL|macro|UCTRL_INTR_RXNE_MSK
mdefine_line|#define UCTRL_INTR_RXNE_MSK        0x40    /* receive FIFO not empty mask */
DECL|macro|UCTRL_INTR_RXO_MSK
mdefine_line|#define UCTRL_INTR_RXO_MSK         0x80    /* receive FIFO overflow mask */
multiline_comment|/* Bits for uctrl_stat register */
DECL|macro|UCTRL_STAT_TXE_STA
mdefine_line|#define UCTRL_STAT_TXE_STA         0x01    /* transmit FIFO empty status */
DECL|macro|UCTRL_STAT_TXNF_STA
mdefine_line|#define UCTRL_STAT_TXNF_STA        0x02    /* transmit FIFO not full status */
DECL|macro|UCTRL_STAT_RXNE_STA
mdefine_line|#define UCTRL_STAT_RXNE_STA        0x04    /* receive FIFO not empty status */
DECL|macro|UCTRL_STAT_RXO_STA
mdefine_line|#define UCTRL_STAT_RXO_STA         0x08    /* receive FIFO overflow status */
DECL|variable|uctrl_extstatus
r_static
r_const
r_char
op_star
id|uctrl_extstatus
(braket
l_int|16
)braket
op_assign
(brace
l_string|&quot;main power available&quot;
comma
l_string|&quot;internal battery attached&quot;
comma
l_string|&quot;external battery attached&quot;
comma
l_string|&quot;external VGA attached&quot;
comma
l_string|&quot;external keyboard attached&quot;
comma
l_string|&quot;external mouse attached&quot;
comma
l_string|&quot;lid down&quot;
comma
l_string|&quot;internal battery currently charging&quot;
comma
l_string|&quot;external battery currently charging&quot;
comma
l_string|&quot;internal battery currently discharging&quot;
comma
l_string|&quot;external battery currently discharging&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Everything required for one transaction with the uctrl */
DECL|struct|uctrl_txn
r_struct
id|uctrl_txn
(brace
DECL|member|opcode
id|u8
id|opcode
suffix:semicolon
DECL|member|inbits
id|u8
id|inbits
suffix:semicolon
DECL|member|outbits
id|u8
id|outbits
suffix:semicolon
DECL|member|inbuf
id|u8
op_star
id|inbuf
suffix:semicolon
DECL|member|outbuf
id|u8
op_star
id|outbuf
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uctrl_status
r_struct
id|uctrl_status
(brace
DECL|member|current_temp
id|u8
id|current_temp
suffix:semicolon
multiline_comment|/* 0x07 */
DECL|member|reset_status
id|u8
id|reset_status
suffix:semicolon
multiline_comment|/* 0x0b */
DECL|member|event_status
id|u16
id|event_status
suffix:semicolon
multiline_comment|/* 0x0c */
DECL|member|error_status
id|u16
id|error_status
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|external_status
id|u16
id|external_status
suffix:semicolon
multiline_comment|/* 0x11, 0x1b */
DECL|member|internal_charge
id|u8
id|internal_charge
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|external_charge
id|u8
id|external_charge
suffix:semicolon
multiline_comment|/* 0x19 */
DECL|member|control_lcd
id|u16
id|control_lcd
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|control_bitport
id|u8
id|control_bitport
suffix:semicolon
multiline_comment|/* 0x21 */
DECL|member|speaker_volume
id|u8
id|speaker_volume
suffix:semicolon
multiline_comment|/* 0x23 */
DECL|member|control_tft_brightness
id|u8
id|control_tft_brightness
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|control_kbd_repeat_delay
id|u8
id|control_kbd_repeat_delay
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|control_kbd_repeat_rate
id|u8
id|control_kbd_repeat_rate
suffix:semicolon
multiline_comment|/* 0x29 */
DECL|member|control_screen_contrast
id|u8
id|control_screen_contrast
suffix:semicolon
multiline_comment|/* 0x2F */
)brace
suffix:semicolon
DECL|enum|uctrl_opcode
r_enum
id|uctrl_opcode
(brace
DECL|enumerator|READ_SERIAL_NUMBER
id|READ_SERIAL_NUMBER
op_assign
l_int|0x1
comma
DECL|enumerator|READ_ETHERNET_ADDRESS
id|READ_ETHERNET_ADDRESS
op_assign
l_int|0x2
comma
DECL|enumerator|READ_HARDWARE_VERSION
id|READ_HARDWARE_VERSION
op_assign
l_int|0x3
comma
DECL|enumerator|READ_MICROCONTROLLER_VERSION
id|READ_MICROCONTROLLER_VERSION
op_assign
l_int|0x4
comma
DECL|enumerator|READ_MAX_TEMPERATURE
id|READ_MAX_TEMPERATURE
op_assign
l_int|0x5
comma
DECL|enumerator|READ_MIN_TEMPERATURE
id|READ_MIN_TEMPERATURE
op_assign
l_int|0x6
comma
DECL|enumerator|READ_CURRENT_TEMPERATURE
id|READ_CURRENT_TEMPERATURE
op_assign
l_int|0x7
comma
DECL|enumerator|READ_SYSTEM_VARIANT
id|READ_SYSTEM_VARIANT
op_assign
l_int|0x8
comma
DECL|enumerator|READ_POWERON_CYCLES
id|READ_POWERON_CYCLES
op_assign
l_int|0x9
comma
DECL|enumerator|READ_POWERON_SECONDS
id|READ_POWERON_SECONDS
op_assign
l_int|0xA
comma
DECL|enumerator|READ_RESET_STATUS
id|READ_RESET_STATUS
op_assign
l_int|0xB
comma
DECL|enumerator|READ_EVENT_STATUS
id|READ_EVENT_STATUS
op_assign
l_int|0xC
comma
DECL|enumerator|READ_REAL_TIME_CLOCK
id|READ_REAL_TIME_CLOCK
op_assign
l_int|0xD
comma
DECL|enumerator|READ_EXTERNAL_VGA_PORT
id|READ_EXTERNAL_VGA_PORT
op_assign
l_int|0xE
comma
DECL|enumerator|READ_MICROCONTROLLER_ROM_CHECKSUM
id|READ_MICROCONTROLLER_ROM_CHECKSUM
op_assign
l_int|0xF
comma
DECL|enumerator|READ_ERROR_STATUS
id|READ_ERROR_STATUS
op_assign
l_int|0x10
comma
DECL|enumerator|READ_EXTERNAL_STATUS
id|READ_EXTERNAL_STATUS
op_assign
l_int|0x11
comma
DECL|enumerator|READ_USER_CONFIGURATION_AREA
id|READ_USER_CONFIGURATION_AREA
op_assign
l_int|0x12
comma
DECL|enumerator|READ_MICROCONTROLLER_VOLTAGE
id|READ_MICROCONTROLLER_VOLTAGE
op_assign
l_int|0x13
comma
DECL|enumerator|READ_INTERNAL_BATTERY_VOLTAGE
id|READ_INTERNAL_BATTERY_VOLTAGE
op_assign
l_int|0x14
comma
DECL|enumerator|READ_DCIN_VOLTAGE
id|READ_DCIN_VOLTAGE
op_assign
l_int|0x15
comma
DECL|enumerator|READ_HORIZONTAL_POINTER_VOLTAGE
id|READ_HORIZONTAL_POINTER_VOLTAGE
op_assign
l_int|0x16
comma
DECL|enumerator|READ_VERTICAL_POINTER_VOLTAGE
id|READ_VERTICAL_POINTER_VOLTAGE
op_assign
l_int|0x17
comma
DECL|enumerator|READ_INTERNAL_BATTERY_CHARGE_LEVEL
id|READ_INTERNAL_BATTERY_CHARGE_LEVEL
op_assign
l_int|0x18
comma
DECL|enumerator|READ_EXTERNAL_BATTERY_CHARGE_LEVEL
id|READ_EXTERNAL_BATTERY_CHARGE_LEVEL
op_assign
l_int|0x19
comma
DECL|enumerator|READ_REAL_TIME_CLOCK_ALARM
id|READ_REAL_TIME_CLOCK_ALARM
op_assign
l_int|0x1A
comma
DECL|enumerator|READ_EVENT_STATUS_NO_RESET
id|READ_EVENT_STATUS_NO_RESET
op_assign
l_int|0x1B
comma
DECL|enumerator|READ_INTERNAL_KEYBOARD_LAYOUT
id|READ_INTERNAL_KEYBOARD_LAYOUT
op_assign
l_int|0x1C
comma
DECL|enumerator|READ_EXTERNAL_KEYBOARD_LAYOUT
id|READ_EXTERNAL_KEYBOARD_LAYOUT
op_assign
l_int|0x1D
comma
DECL|enumerator|READ_EEPROM_STATUS
id|READ_EEPROM_STATUS
op_assign
l_int|0x1E
comma
DECL|enumerator|CONTROL_LCD
id|CONTROL_LCD
op_assign
l_int|0x20
comma
DECL|enumerator|CONTROL_BITPORT
id|CONTROL_BITPORT
op_assign
l_int|0x21
comma
DECL|enumerator|SPEAKER_VOLUME
id|SPEAKER_VOLUME
op_assign
l_int|0x23
comma
DECL|enumerator|CONTROL_TFT_BRIGHTNESS
id|CONTROL_TFT_BRIGHTNESS
op_assign
l_int|0x24
comma
DECL|enumerator|CONTROL_WATCHDOG
id|CONTROL_WATCHDOG
op_assign
l_int|0x25
comma
DECL|enumerator|CONTROL_FACTORY_EEPROM_AREA
id|CONTROL_FACTORY_EEPROM_AREA
op_assign
l_int|0x26
comma
DECL|enumerator|CONTROL_KBD_TIME_UNTIL_REPEAT
id|CONTROL_KBD_TIME_UNTIL_REPEAT
op_assign
l_int|0x28
comma
DECL|enumerator|CONTROL_KBD_TIME_BETWEEN_REPEATS
id|CONTROL_KBD_TIME_BETWEEN_REPEATS
op_assign
l_int|0x29
comma
DECL|enumerator|CONTROL_TIMEZONE
id|CONTROL_TIMEZONE
op_assign
l_int|0x2A
comma
DECL|enumerator|CONTROL_MARK_SPACE_RATIO
id|CONTROL_MARK_SPACE_RATIO
op_assign
l_int|0x2B
comma
DECL|enumerator|CONTROL_DIAGNOSTIC_MODE
id|CONTROL_DIAGNOSTIC_MODE
op_assign
l_int|0x2E
comma
DECL|enumerator|CONTROL_SCREEN_CONTRAST
id|CONTROL_SCREEN_CONTRAST
op_assign
l_int|0x2F
comma
DECL|enumerator|RING_BELL
id|RING_BELL
op_assign
l_int|0x30
comma
DECL|enumerator|SET_DIAGNOSTIC_STATUS
id|SET_DIAGNOSTIC_STATUS
op_assign
l_int|0x32
comma
DECL|enumerator|CLEAR_KEY_COMBINATION_TABLE
id|CLEAR_KEY_COMBINATION_TABLE
op_assign
l_int|0x33
comma
DECL|enumerator|PERFORM_SOFTWARE_RESET
id|PERFORM_SOFTWARE_RESET
op_assign
l_int|0x34
comma
DECL|enumerator|SET_REAL_TIME_CLOCK
id|SET_REAL_TIME_CLOCK
op_assign
l_int|0x35
comma
DECL|enumerator|RECALIBRATE_POINTING_STICK
id|RECALIBRATE_POINTING_STICK
op_assign
l_int|0x36
comma
DECL|enumerator|SET_BELL_FREQUENCY
id|SET_BELL_FREQUENCY
op_assign
l_int|0x37
comma
DECL|enumerator|SET_INTERNAL_BATTERY_CHARGE_RATE
id|SET_INTERNAL_BATTERY_CHARGE_RATE
op_assign
l_int|0x39
comma
DECL|enumerator|SET_EXTERNAL_BATTERY_CHARGE_RATE
id|SET_EXTERNAL_BATTERY_CHARGE_RATE
op_assign
l_int|0x3A
comma
DECL|enumerator|SET_REAL_TIME_CLOCK_ALARM
id|SET_REAL_TIME_CLOCK_ALARM
op_assign
l_int|0x3B
comma
DECL|enumerator|READ_EEPROM
id|READ_EEPROM
op_assign
l_int|0x40
comma
DECL|enumerator|WRITE_EEPROM
id|WRITE_EEPROM
op_assign
l_int|0x41
comma
DECL|enumerator|WRITE_TO_STATUS_DISPLAY
id|WRITE_TO_STATUS_DISPLAY
op_assign
l_int|0x42
comma
DECL|enumerator|DEFINE_SPECIAL_CHARACTER
id|DEFINE_SPECIAL_CHARACTER
op_assign
l_int|0x43
comma
DECL|enumerator|DEFINE_KEY_COMBINATION_ENTRY
id|DEFINE_KEY_COMBINATION_ENTRY
op_assign
l_int|0x50
comma
DECL|enumerator|DEFINE_STRING_TABLE_ENTRY
id|DEFINE_STRING_TABLE_ENTRY
op_assign
l_int|0x51
comma
DECL|enumerator|DEFINE_STATUS_SCREEN_DISPLAY
id|DEFINE_STATUS_SCREEN_DISPLAY
op_assign
l_int|0x52
comma
DECL|enumerator|PERFORM_EMU_COMMANDS
id|PERFORM_EMU_COMMANDS
op_assign
l_int|0x64
comma
DECL|enumerator|READ_EMU_REGISTER
id|READ_EMU_REGISTER
op_assign
l_int|0x65
comma
DECL|enumerator|WRITE_EMU_REGISTER
id|WRITE_EMU_REGISTER
op_assign
l_int|0x66
comma
DECL|enumerator|READ_EMU_RAM
id|READ_EMU_RAM
op_assign
l_int|0x67
comma
DECL|enumerator|WRITE_EMU_RAM
id|WRITE_EMU_RAM
op_assign
l_int|0x68
comma
DECL|enumerator|READ_BQ_REGISTER
id|READ_BQ_REGISTER
op_assign
l_int|0x69
comma
DECL|enumerator|WRITE_BQ_REGISTER
id|WRITE_BQ_REGISTER
op_assign
l_int|0x6A
comma
DECL|enumerator|SET_USER_PASSWORD
id|SET_USER_PASSWORD
op_assign
l_int|0x70
comma
DECL|enumerator|VERIFY_USER_PASSWORD
id|VERIFY_USER_PASSWORD
op_assign
l_int|0x71
comma
DECL|enumerator|GET_SYSTEM_PASSWORD_KEY
id|GET_SYSTEM_PASSWORD_KEY
op_assign
l_int|0x72
comma
DECL|enumerator|VERIFY_SYSTEM_PASSWORD
id|VERIFY_SYSTEM_PASSWORD
op_assign
l_int|0x73
comma
DECL|enumerator|POWER_OFF
id|POWER_OFF
op_assign
l_int|0x82
comma
DECL|enumerator|POWER_RESTART
id|POWER_RESTART
op_assign
l_int|0x83
comma
)brace
suffix:semicolon
DECL|struct|uctrl_driver
r_struct
id|uctrl_driver
(brace
DECL|member|regs
r_struct
id|uctrl_regs
op_star
id|regs
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|pending
r_int
id|pending
suffix:semicolon
DECL|member|status
r_struct
id|uctrl_status
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|drv
r_static
r_struct
id|uctrl_driver
id|drv
suffix:semicolon
r_void
id|uctrl_get_event_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|uctrl_get_external_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|loff_t
DECL|function|uctrl_llseek
id|uctrl_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|type
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
r_static
r_int
DECL|function|uctrl_ioctl
id|uctrl_ioctl
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
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|uctrl_open
id|uctrl_open
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
)paren
(brace
id|uctrl_get_event_status
c_func
(paren
)paren
suffix:semicolon
id|uctrl_get_external_status
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uctrl_interrupt
r_void
id|uctrl_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
(paren
r_struct
id|uctrl_driver
op_star
)paren
id|dev_id
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;in uctrl_interrupt&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|uctrl_fops
r_static
r_struct
id|file_operations
id|uctrl_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|uctrl_llseek
comma
id|ioctl
suffix:colon
id|uctrl_ioctl
comma
id|open
suffix:colon
id|uctrl_open
comma
)brace
suffix:semicolon
DECL|variable|uctrl_dev
r_static
r_struct
id|miscdevice
id|uctrl_dev
op_assign
(brace
id|UCTRL_MINOR
comma
l_string|&quot;uctrl&quot;
comma
op_amp
id|uctrl_fops
)brace
suffix:semicolon
multiline_comment|/* Wait for space to write, then write to it */
DECL|macro|WRITEUCTLDATA
mdefine_line|#define WRITEUCTLDATA(value) &bslash;&n;{ &bslash;&n;  unsigned int i; &bslash;&n;  for (i = 0; i &lt; 10000; i++) { &bslash;&n;    if (UCTRL_STAT_TXNF_STA &amp; driver-&gt;regs-&gt;uctrl_stat) &bslash;&n;      break; &bslash;&n;  } &bslash;&n;  dprintk((&quot;write data 0x%02x&bslash;n&quot;, value)); &bslash;&n;  driver-&gt;regs-&gt;uctrl_data = value; &bslash;&n;}
multiline_comment|/* Wait for something to read, read it, then clear the bit */
DECL|macro|READUCTLDATA
mdefine_line|#define READUCTLDATA(value) &bslash;&n;{ &bslash;&n;  unsigned int i; &bslash;&n;  value = 0; &bslash;&n;  for (i = 0; i &lt; 10000; i++) { &bslash;&n;    if ((UCTRL_STAT_RXNE_STA &amp; driver-&gt;regs-&gt;uctrl_stat) == 0) &bslash;&n;      break; &bslash;&n;    udelay(1); &bslash;&n;  } &bslash;&n;  value = driver-&gt;regs-&gt;uctrl_data; &bslash;&n;  dprintk((&quot;read data 0x%02x&bslash;n&quot;, value)); &bslash;&n;  driver-&gt;regs-&gt;uctrl_stat = UCTRL_STAT_RXNE_STA; &bslash;&n;}
DECL|function|uctrl_set_video
r_void
id|uctrl_set_video
c_func
(paren
r_int
id|status
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
)brace
DECL|function|uctrl_do_txn
r_static
r_void
id|uctrl_do_txn
c_func
(paren
r_struct
id|uctrl_txn
op_star
id|txn
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
r_int
id|stat
comma
id|incnt
comma
id|outcnt
comma
id|bytecnt
comma
id|intr
suffix:semicolon
id|u32
id|byte
suffix:semicolon
id|stat
op_assign
id|driver-&gt;regs-&gt;uctrl_stat
suffix:semicolon
id|intr
op_assign
id|driver-&gt;regs-&gt;uctrl_intr
suffix:semicolon
id|driver-&gt;regs-&gt;uctrl_stat
op_assign
id|stat
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;interrupt stat 0x%x int 0x%x&bslash;n&quot;
comma
id|stat
comma
id|intr
)paren
)paren
suffix:semicolon
id|incnt
op_assign
id|txn-&gt;inbits
suffix:semicolon
id|outcnt
op_assign
id|txn-&gt;outbits
suffix:semicolon
id|byte
op_assign
(paren
id|txn-&gt;opcode
op_lshift
l_int|8
)paren
suffix:semicolon
id|WRITEUCTLDATA
c_func
(paren
id|byte
)paren
suffix:semicolon
id|bytecnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|incnt
OG
l_int|0
)paren
(brace
id|byte
op_assign
(paren
id|txn-&gt;inbuf
(braket
id|bytecnt
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|WRITEUCTLDATA
c_func
(paren
id|byte
)paren
suffix:semicolon
id|incnt
op_decrement
suffix:semicolon
id|bytecnt
op_increment
suffix:semicolon
)brace
multiline_comment|/* Get the ack */
id|READUCTLDATA
c_func
(paren
id|byte
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;ack was %x&bslash;n&quot;
comma
(paren
id|byte
op_rshift
l_int|8
)paren
)paren
)paren
suffix:semicolon
id|bytecnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|outcnt
OG
l_int|0
)paren
(brace
id|READUCTLDATA
c_func
(paren
id|byte
)paren
suffix:semicolon
id|txn-&gt;outbuf
(braket
id|bytecnt
)braket
op_assign
(paren
id|byte
op_rshift
l_int|8
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;set byte to %02x&bslash;n&quot;
comma
id|byte
)paren
)paren
suffix:semicolon
id|outcnt
op_decrement
suffix:semicolon
id|bytecnt
op_increment
suffix:semicolon
)brace
)brace
DECL|function|uctrl_get_event_status
r_void
id|uctrl_get_event_status
c_func
(paren
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
r_struct
id|uctrl_txn
id|txn
suffix:semicolon
id|u8
id|outbits
(braket
l_int|2
)braket
suffix:semicolon
id|txn.opcode
op_assign
id|READ_EVENT_STATUS
suffix:semicolon
id|txn.inbits
op_assign
l_int|0
suffix:semicolon
id|txn.outbits
op_assign
l_int|2
suffix:semicolon
id|txn.inbuf
op_assign
l_int|0
suffix:semicolon
id|txn.outbuf
op_assign
id|outbits
suffix:semicolon
id|uctrl_do_txn
c_func
(paren
op_amp
id|txn
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;bytes %x %x&bslash;n&quot;
comma
(paren
id|outbits
(braket
l_int|0
)braket
op_amp
l_int|0xff
)paren
comma
(paren
id|outbits
(braket
l_int|1
)braket
op_amp
l_int|0xff
)paren
)paren
)paren
suffix:semicolon
id|driver-&gt;status.event_status
op_assign
(paren
(paren
id|outbits
(braket
l_int|0
)braket
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|outbits
(braket
l_int|1
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;ev is %x&bslash;n&quot;
comma
id|driver-&gt;status.event_status
)paren
)paren
suffix:semicolon
)brace
DECL|function|uctrl_get_external_status
r_void
id|uctrl_get_external_status
c_func
(paren
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
r_struct
id|uctrl_txn
id|txn
suffix:semicolon
id|u8
id|outbits
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|v
suffix:semicolon
id|txn.opcode
op_assign
id|READ_EXTERNAL_STATUS
suffix:semicolon
id|txn.inbits
op_assign
l_int|0
suffix:semicolon
id|txn.outbits
op_assign
l_int|2
suffix:semicolon
id|txn.inbuf
op_assign
l_int|0
suffix:semicolon
id|txn.outbuf
op_assign
id|outbits
suffix:semicolon
id|uctrl_do_txn
c_func
(paren
op_amp
id|txn
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;bytes %x %x&bslash;n&quot;
comma
(paren
id|outbits
(braket
l_int|0
)braket
op_amp
l_int|0xff
)paren
comma
(paren
id|outbits
(braket
l_int|1
)braket
op_amp
l_int|0xff
)paren
)paren
)paren
suffix:semicolon
id|driver-&gt;status.external_status
op_assign
(paren
(paren
id|outbits
(braket
l_int|0
)braket
op_star
l_int|256
)paren
op_plus
(paren
id|outbits
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;ex is %x&bslash;n&quot;
comma
id|driver-&gt;status.external_status
)paren
)paren
suffix:semicolon
id|v
op_assign
id|driver-&gt;status.external_status
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|v
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
comma
id|v
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|v
op_amp
l_int|1
)paren
(brace
id|dprintk
c_func
(paren
(paren
l_string|&quot;%s%s&quot;
comma
l_string|&quot; &quot;
comma
id|uctrl_extstatus
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
)brace
id|dprintk
c_func
(paren
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
DECL|function|ts102_uctrl_init
r_static
r_int
id|__init
id|ts102_uctrl_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
r_struct
id|linux_prom_irqs
id|tmp_irq
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|vaddr
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|tmpnode
comma
id|uctrlnode
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|tmpnode
op_assign
id|prom_searchsiblings
c_func
(paren
id|uctrlnode
comma
l_string|&quot;obio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmpnode
)paren
id|uctrlnode
op_assign
id|prom_getchild
c_func
(paren
id|tmpnode
)paren
suffix:semicolon
id|uctrlnode
op_assign
id|prom_searchsiblings
c_func
(paren
id|uctrlnode
comma
l_string|&quot;uctrl&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uctrlnode
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* the prom mapped it for us */
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|uctrlnode
comma
l_string|&quot;address&quot;
comma
(paren
r_void
op_star
)paren
id|vaddr
comma
r_sizeof
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|driver-&gt;regs
op_assign
(paren
r_struct
id|uctrl_regs
op_star
)paren
id|vaddr
(braket
l_int|0
)braket
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|uctrlnode
comma
l_string|&quot;intr&quot;
comma
(paren
r_char
op_star
)paren
id|tmp_irq
comma
r_sizeof
(paren
id|tmp_irq
)paren
)paren
suffix:semicolon
multiline_comment|/* Flush device */
id|READUCTLDATA
c_func
(paren
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver-&gt;irq
)paren
(brace
id|driver-&gt;irq
op_assign
id|tmp_irq
(braket
l_int|0
)braket
dot
id|pri
suffix:semicolon
)brace
id|request_irq
c_func
(paren
id|driver-&gt;irq
comma
id|uctrl_interrupt
comma
l_int|0
comma
l_string|&quot;uctrl&quot;
comma
id|driver
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|driver-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|uctrl_dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to get misc minor %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|uctrl_dev.minor
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|driver-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|driver-&gt;irq
comma
id|driver
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|driver-&gt;regs-&gt;uctrl_intr
op_assign
id|UCTRL_INTR_RXNE_REQ
op_or
id|UCTRL_INTR_RXNE_MSK
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;uctrl: 0x%x (irq %s)&bslash;n&quot;
comma
id|driver-&gt;regs
comma
id|__irq_itoa
c_func
(paren
id|driver-&gt;irq
)paren
)paren
suffix:semicolon
id|uctrl_get_event_status
c_func
(paren
)paren
suffix:semicolon
id|uctrl_get_external_status
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ts102_uctrl_cleanup
r_static
r_void
id|__exit
id|ts102_uctrl_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|uctrl_driver
op_star
id|driver
op_assign
op_amp
id|drv
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|uctrl_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driver-&gt;irq
)paren
(brace
id|disable_irq
c_func
(paren
id|driver-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|driver-&gt;irq
comma
id|driver
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|driver-&gt;regs
)paren
id|driver-&gt;regs
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|ts102_uctrl_init
id|module_init
c_func
(paren
id|ts102_uctrl_init
)paren
suffix:semicolon
DECL|variable|ts102_uctrl_cleanup
id|module_exit
c_func
(paren
id|ts102_uctrl_cleanup
)paren
suffix:semicolon
eof
