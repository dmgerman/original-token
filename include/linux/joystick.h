macro_line|#ifndef _LINUX_JOYSTICK_H
DECL|macro|_LINUX_JOYSTICK_H
mdefine_line|#define _LINUX_JOYSTICK_H
DECL|macro|JS_RETURN
mdefine_line|#define JS_RETURN sizeof(struct js_status)&t;/*number of bytes returned by js_read*/
DECL|macro|JS_TRUE
mdefine_line|#define JS_TRUE 1
DECL|macro|JS_FALSE
mdefine_line|#define JS_FALSE 0
DECL|macro|JS_PORT
mdefine_line|#define JS_PORT 0x201&t;&t;/*io port for joystick operations*/
DECL|macro|JS_DEF_TIMEOUT
mdefine_line|#define JS_DEF_TIMEOUT 0x1300&t;/*default timeout value for js_read()*/
DECL|macro|JS_DEF_CORR
mdefine_line|#define JS_DEF_CORR&t;0&t;/*default correction factor*/
DECL|macro|JS_DEF_TIMELIMIT
mdefine_line|#define JS_DEF_TIMELIMIT 10L&t;/*default data valid time =10 jiffies == 100ms*/
DECL|macro|JS_X_0
mdefine_line|#define JS_X_0&t;0x01&t;&t;/*bit mask for x-axis js0*/
DECL|macro|JS_Y_0
mdefine_line|#define JS_Y_0&t;0x02&t;&t;/*bit mask for y-axis js0*/
DECL|macro|JS_X_1
mdefine_line|#define JS_X_1&t;0x04&t;&t;/*bit mask for x-axis js1*/
DECL|macro|JS_Y_1
mdefine_line|#define JS_Y_1&t;0x08&t;&t;/*bit mask for y-axis js1*/
DECL|macro|JS_MAX
mdefine_line|#define JS_MAX 2&t;&t;/*Max number of joysticks*/
DECL|macro|PIT_MODE
mdefine_line|#define PIT_MODE 0x43&t;&t;/*io port for timer 0*/
DECL|macro|PIT_COUNTER_0
mdefine_line|#define PIT_COUNTER_0 0x40&t;/*io port for timer 0*/
DECL|macro|JSIOCSCAL
mdefine_line|#define JSIOCSCAL 0x01&t;&t;/*ioctl cmd to set joystick correction factor*/
DECL|macro|JSIOCGCAL
mdefine_line|#define JSIOCGCAL 0x02&t;&t;/*ioctl cmd to get joystick correction factor*/
DECL|macro|JSIOCSTIMEOUT
mdefine_line|#define JSIOCSTIMEOUT 0x03&t;/*ioctl cmd to set maximum number of iterations&n;&t;&t;&t;&t;  to wait for a timeout*/
DECL|macro|JSIOCGTIMEOUT
mdefine_line|#define JSIOCGTIMEOUT&t;&t;0x04&t;/*as above, to get*/
DECL|macro|JSIOCSTIMELIMIT
mdefine_line|#define JSIOCSTIMELIMIT&t;0x05&t;/*set data retention time*/
DECL|macro|JSIOCGTIMELIMIT
mdefine_line|#define JSIOCGTIMELIMIT&t;0x06&t;/*get data retention time*/
DECL|macro|JSIOCGCONFIG
mdefine_line|#define JSIOCGCONFIG&t;&t;0x07&t;/*get the whole js_data[minor] struct*/
DECL|macro|JSIOCSCONFIG
mdefine_line|#define JSIOCSCONFIG&t;&t;0x08&t;/*set the whole js_data[minor] struct&n;&t;&t;&t;&t;&t;&t;  except js_busy!*/
multiline_comment|/*&n; *&t;This union is used for the ioctl to set the scaling factor and to &n; *&t;return the current values for a joystick. &squot;buttons&squot; is ignored on&n; *&t;the ioctl call&n; */
DECL|struct|js_status
r_struct
id|js_status
(brace
DECL|member|buttons
r_int
id|buttons
suffix:semicolon
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;This struct is used for misc data about the joystick&n; */
DECL|struct|js_config
r_struct
id|js_config
(brace
DECL|member|js_timeout
r_int
id|js_timeout
suffix:semicolon
multiline_comment|/*timeout*/
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/*joystick is in use*/
DECL|member|js_expiretime
r_int
id|js_expiretime
suffix:semicolon
multiline_comment|/*Time when stick after which stick must be re-read*/
DECL|member|js_timelimit
r_int
id|js_timelimit
suffix:semicolon
multiline_comment|/*Max time before data is invalid*/
DECL|member|js_save
r_struct
id|js_status
id|js_save
suffix:semicolon
multiline_comment|/*last read data*/
DECL|member|js_corr
r_struct
id|js_status
id|js_corr
suffix:semicolon
multiline_comment|/*correction factor*/
)brace
suffix:semicolon
DECL|macro|LATCH
mdefine_line|#define LATCH (1193180L/HZ)&t;/*initial timer 0 value*/
DECL|macro|DELTA_TIME
mdefine_line|#define DELTA_TIME(X,Y) ((X)-(Y)+(((X)&gt;=(Y))?0:LATCH))
r_extern
r_int
id|joystick_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_JOYSTICK_H */
eof
