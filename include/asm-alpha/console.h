macro_line|#ifndef __AXP_CONSOLE_H
DECL|macro|__AXP_CONSOLE_H
mdefine_line|#define __AXP_CONSOLE_H
multiline_comment|/*&n; * Console callback routine numbers&n; */
DECL|macro|CCB_GETC
mdefine_line|#define CCB_GETC&t;&t;0x01
DECL|macro|CCB_PUTS
mdefine_line|#define CCB_PUTS&t;&t;0x02
DECL|macro|CCB_RESET_TERM
mdefine_line|#define CCB_RESET_TERM&t;&t;0x03
DECL|macro|CCB_SET_TERM_INT
mdefine_line|#define CCB_SET_TERM_INT&t;0x04
DECL|macro|CCB_SET_TERM_CTL
mdefine_line|#define CCB_SET_TERM_CTL&t;0x05
DECL|macro|CCB_PROCESS_KEYCODE
mdefine_line|#define CCB_PROCESS_KEYCODE&t;0x06
DECL|macro|CCB_OPEN
mdefine_line|#define CCB_OPEN&t;&t;0x10
DECL|macro|CCB_CLOSE
mdefine_line|#define CCB_CLOSE&t;&t;0x11
DECL|macro|CCB_IOCTL
mdefine_line|#define CCB_IOCTL&t;&t;0x12
DECL|macro|CCB_READ
mdefine_line|#define CCB_READ&t;&t;0x13
DECL|macro|CCB_WRITE
mdefine_line|#define CCB_WRITE&t;&t;0x14
DECL|macro|CCB_SET_ENV
mdefine_line|#define CCB_SET_ENV&t;&t;0x20
DECL|macro|CCB_RESET_ENV
mdefine_line|#define CCB_RESET_ENV&t;&t;0x21
DECL|macro|CCB_GET_ENV
mdefine_line|#define CCB_GET_ENV&t;&t;0x22
DECL|macro|CCB_SAVE_ENV
mdefine_line|#define CCB_SAVE_ENV&t;&t;0x23
multiline_comment|/*&n; * Environment variable numbers&n; */
DECL|macro|ENV_AUTO_ACTION
mdefine_line|#define ENV_AUTO_ACTION&t;&t;0x01
DECL|macro|ENV_BOOT_DEV
mdefine_line|#define ENV_BOOT_DEV&t;&t;0x02
DECL|macro|ENV_BOOTDEF_DEV
mdefine_line|#define ENV_BOOTDEF_DEV&t;&t;0x03
DECL|macro|ENV_BOOTED_DEV
mdefine_line|#define ENV_BOOTED_DEV&t;&t;0x04
DECL|macro|ENV_BOOT_FILE
mdefine_line|#define ENV_BOOT_FILE&t;&t;0x05
DECL|macro|ENV_BOOTED_FILE
mdefine_line|#define ENV_BOOTED_FILE&t;&t;0x06
DECL|macro|ENV_BOOT_OSFLAGS
mdefine_line|#define ENV_BOOT_OSFLAGS&t;0x07
DECL|macro|ENV_BOOTED_OSFLAGS
mdefine_line|#define ENV_BOOTED_OSFLAGS&t;0x08
DECL|macro|ENV_BOOT_RESET
mdefine_line|#define ENV_BOOT_RESET&t;&t;0x09
DECL|macro|ENV_DUMP_DEV
mdefine_line|#define ENV_DUMP_DEV&t;&t;0x0A
DECL|macro|ENV_ENABLE_AUDIT
mdefine_line|#define ENV_ENABLE_AUDIT&t;0x0B
DECL|macro|ENV_LICENCE
mdefine_line|#define ENV_LICENCE&t;&t;0x0C
DECL|macro|ENV_CHAR_SET
mdefine_line|#define ENV_CHAR_SET&t;&t;0x0D
DECL|macro|ENV_LANGUAGE
mdefine_line|#define ENV_LANGUAGE&t;&t;0x0E
DECL|macro|ENV_TTY_DEV
mdefine_line|#define ENV_TTY_DEV&t;&t;0x0F
r_extern
r_int
r_int
id|dispatch
c_func
(paren
r_int
r_int
id|code
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|puts
mdefine_line|#define puts(x,l) dispatch(CCB_PUTS,0,x,l)
macro_line|#endif
eof
