macro_line|#ifndef _LINUX_JOYSTICK_H
DECL|macro|_LINUX_JOYSTICK_H
mdefine_line|#define _LINUX_JOYSTICK_H
multiline_comment|/*&n; *  $Id: joystick.h,v 1.3 1998/03/30 11:10:40 mj Exp $&n; *&n; *  Copyright (C) 1997, 1998 Vojtech Pavlik&n; */
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/*&n; * Version&n; */
DECL|macro|JS_VERSION
mdefine_line|#define JS_VERSION&t;&t;0x00010007L&t;&t;/* 1.0.7 BCD */
multiline_comment|/*&n; * IOCTL commands for joystick driver&n; */
DECL|macro|JSIOCGVERSION
mdefine_line|#define JSIOCGVERSION&t;&t;_IOR(&squot;j&squot;, 0x01, __u32)&t;&t;&t;&t;/* get driver version */
DECL|macro|JSIOCGAXES
mdefine_line|#define JSIOCGAXES&t;&t;_IOR(&squot;j&squot;, 0x11, __u8)&t;&t;&t;&t;/* get number of axes */
DECL|macro|JSIOCGBUTTONS
mdefine_line|#define JSIOCGBUTTONS&t;&t;_IOR(&squot;j&squot;, 0x12, __u8)&t;&t;&t;&t;/* get number of buttons */
DECL|macro|JSIOCSCORR
mdefine_line|#define JSIOCSCORR&t;&t;_IOW(&squot;j&squot;, 0x21, struct js_corr[4])&t;&t;/* set correction values */
DECL|macro|JSIOCGCORR
mdefine_line|#define JSIOCGCORR&t;&t;_IOR(&squot;j&squot;, 0x22, struct js_corr[4])&t;&t;/* get correction values */
multiline_comment|/*&n; * Types and constants for get/set correction&n; */
DECL|macro|JS_CORR_NONE
mdefine_line|#define JS_CORR_NONE&t;&t;0x00&t;&t;/* returns raw values */
DECL|macro|JS_CORR_BROKEN
mdefine_line|#define JS_CORR_BROKEN&t;&t;0x01&t;&t;/* broken line */
DECL|struct|js_corr
r_struct
id|js_corr
(brace
DECL|member|coef
id|__s32
id|coef
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|prec
id|__u16
id|prec
suffix:semicolon
DECL|member|type
id|__u16
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Types and constants for reading from /dev/js&n; */
DECL|macro|JS_EVENT_BUTTON
mdefine_line|#define JS_EVENT_BUTTON&t;&t;0x01&t;/* button pressed/released */
DECL|macro|JS_EVENT_AXIS
mdefine_line|#define JS_EVENT_AXIS&t;&t;0x02&t;/* joystick moved */
DECL|macro|JS_EVENT_INIT
mdefine_line|#define JS_EVENT_INIT&t;&t;0x80&t;/* initial state of device */
DECL|struct|js_event
r_struct
id|js_event
(brace
DECL|member|time
id|__u32
id|time
suffix:semicolon
multiline_comment|/* time when event happened in miliseconds since open */
DECL|member|value
id|__u16
id|value
suffix:semicolon
multiline_comment|/* new value */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* type of event, see above */
DECL|member|number
id|__u8
id|number
suffix:semicolon
multiline_comment|/* axis/button number */
)brace
suffix:semicolon
multiline_comment|/*&n; * Backward (version 0.x) compatibility definitions&n; */
DECL|macro|JS_RETURN
mdefine_line|#define JS_RETURN &t;sizeof(struct JS_DATA_TYPE)
DECL|macro|JS_TRUE
mdefine_line|#define JS_TRUE &t;1
DECL|macro|JS_FALSE
mdefine_line|#define JS_FALSE &t;0
DECL|macro|JS_X_0
mdefine_line|#define JS_X_0&t;&t;0x01&t;&t;/* bit mask for x-axis js0 */
DECL|macro|JS_Y_0
mdefine_line|#define JS_Y_0&t;&t;0x02&t;&t;/* bit mask for y-axis js0 */
DECL|macro|JS_X_1
mdefine_line|#define JS_X_1&t;&t;0x04&t;&t;/* bit mask for x-axis js1 */
DECL|macro|JS_Y_1
mdefine_line|#define JS_Y_1&t;&t;0x08&t;&t;/* bit mask for y-axis js1 */
DECL|macro|JS_MAX
mdefine_line|#define JS_MAX &t;&t;2&t;&t;/* max number of joysticks */
DECL|struct|JS_DATA_TYPE
r_struct
id|JS_DATA_TYPE
(brace
DECL|member|buttons
r_int
id|buttons
suffix:semicolon
multiline_comment|/* immediate button state */
DECL|member|x
r_int
id|x
suffix:semicolon
multiline_comment|/* immediate x axis value */
DECL|member|y
r_int
id|y
suffix:semicolon
multiline_comment|/* immediate y axis value */
)brace
suffix:semicolon
r_extern
r_int
id|js_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_JOYSTICK_H */
eof
