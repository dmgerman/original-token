multiline_comment|/*&n; * Definitions for talking to the CUDA.  The CUDA is a microcontroller&n; * which controls the ADB, system power, RTC, and various other things.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
multiline_comment|/* First byte sent to or received from CUDA */
DECL|macro|ADB_PACKET
mdefine_line|#define ADB_PACKET&t;0
DECL|macro|CUDA_PACKET
mdefine_line|#define CUDA_PACKET&t;1
DECL|macro|ERROR_PACKET
mdefine_line|#define ERROR_PACKET&t;2
DECL|macro|TIMER_PACKET
mdefine_line|#define TIMER_PACKET&t;3
DECL|macro|POWER_PACKET
mdefine_line|#define POWER_PACKET&t;4
DECL|macro|MACIIC_PACKET
mdefine_line|#define MACIIC_PACKET&t;5
DECL|macro|PMU_PACKET
mdefine_line|#define PMU_PACKET&t;6
multiline_comment|/* CUDA commands (2nd byte) */
DECL|macro|CUDA_WARM_START
mdefine_line|#define CUDA_WARM_START&t;&t;0
DECL|macro|CUDA_AUTOPOLL
mdefine_line|#define CUDA_AUTOPOLL&t;&t;1
DECL|macro|CUDA_GET_6805_ADDR
mdefine_line|#define CUDA_GET_6805_ADDR&t;2
DECL|macro|CUDA_GET_TIME
mdefine_line|#define CUDA_GET_TIME&t;&t;3
DECL|macro|CUDA_GET_PRAM
mdefine_line|#define CUDA_GET_PRAM&t;&t;7
DECL|macro|CUDA_SET_6805_ADDR
mdefine_line|#define CUDA_SET_6805_ADDR&t;8
DECL|macro|CUDA_SET_TIME
mdefine_line|#define CUDA_SET_TIME&t;&t;9
DECL|macro|CUDA_POWERDOWN
mdefine_line|#define CUDA_POWERDOWN&t;&t;0xa
DECL|macro|CUDA_POWERUP_TIME
mdefine_line|#define CUDA_POWERUP_TIME&t;0xb
DECL|macro|CUDA_SET_PRAM
mdefine_line|#define CUDA_SET_PRAM&t;&t;0xc
DECL|macro|CUDA_MS_RESET
mdefine_line|#define CUDA_MS_RESET&t;&t;0xd
DECL|macro|CUDA_SEND_DFAC
mdefine_line|#define CUDA_SEND_DFAC&t;&t;0xe
DECL|macro|CUDA_RESET_SYSTEM
mdefine_line|#define CUDA_RESET_SYSTEM&t;0x11
DECL|macro|CUDA_SET_IPL
mdefine_line|#define CUDA_SET_IPL&t;&t;0x12
DECL|macro|CUDA_SET_AUTO_RATE
mdefine_line|#define CUDA_SET_AUTO_RATE&t;0x14
DECL|macro|CUDA_GET_AUTO_RATE
mdefine_line|#define CUDA_GET_AUTO_RATE&t;0x16
DECL|macro|CUDA_SET_DEVICE_LIST
mdefine_line|#define CUDA_SET_DEVICE_LIST&t;0x19
DECL|macro|CUDA_GET_DEVICE_LIST
mdefine_line|#define CUDA_GET_DEVICE_LIST&t;0x1a
DECL|macro|CUDA_GET_SET_IIC
mdefine_line|#define CUDA_GET_SET_IIC&t;0x22
macro_line|#ifdef __KERNEL__
r_void
id|via_cuda_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|cuda_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|adb_request
op_star
)paren
comma
r_int
id|nbytes
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|cuda_send_request
c_func
(paren
r_struct
id|adb_request
op_star
id|req
)paren
suffix:semicolon
r_void
id|cuda_poll
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL */
eof
