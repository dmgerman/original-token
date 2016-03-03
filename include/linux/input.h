macro_line|#ifndef _INPUT_H
DECL|macro|_INPUT_H
mdefine_line|#define _INPUT_H
multiline_comment|/*&n; * $Id: input.h,v 1.18 2000/07/25 21:36:56 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/time.h&gt;
macro_line|#else
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#endif
multiline_comment|/*&n; * The event structure itself&n; */
DECL|struct|input_event
r_struct
id|input_event
(brace
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Protocol version.&n; */
DECL|macro|EV_VERSION
mdefine_line|#define EV_VERSION&t;&t;0x010000
multiline_comment|/*&n; * IOCTLs (0x00 - 0x7f)&n; */
DECL|macro|EVIOCGVERSION
mdefine_line|#define EVIOCGVERSION&t;&t;_IOR(&squot;E&squot;, 0x01, int)                    /* get driver version */
DECL|macro|EVIOCGID
mdefine_line|#define EVIOCGID&t;&t;_IOR(&squot;E&squot;, 0x02, short[4])&t;&t;/* get device ID */
DECL|macro|EVIOCGREP
mdefine_line|#define EVIOCGREP&t;&t;_IOR(&squot;E&squot;, 0x03, int[2])&t;&t;&t;/* get repeat settings */
DECL|macro|EVIOCSREP
mdefine_line|#define EVIOCSREP&t;&t;_IOW(&squot;E&squot;, 0x03, int[2])&t;&t;&t;/* get repeat settings */
DECL|macro|EVIOCGKEYCODE
mdefine_line|#define EVIOCGKEYCODE&t;&t;_IOR(&squot;E&squot;, 0x04, int[2])&t;&t;&t;/* get keycode */
DECL|macro|EVIOCSKEYCODE
mdefine_line|#define EVIOCSKEYCODE&t;&t;_IOW(&squot;E&squot;, 0x04, int[2])&t;&t;&t;/* set keycode */
DECL|macro|EVIOCGKEY
mdefine_line|#define EVIOCGKEY&t;&t;_IOR(&squot;E&squot;, 0x05, int[2])&t;&t;&t;/* get key value */
DECL|macro|EVIOCGNAME
mdefine_line|#define EVIOCGNAME(len)&t;&t;_IOC(_IOC_READ, &squot;E&squot;, 0x06, len)&t;&t;/* get device name */
DECL|macro|EVIOCGBIT
mdefine_line|#define EVIOCGBIT(ev,len)&t;_IOC(_IOC_READ, &squot;E&squot;, 0x20 + ev, len)&t;/* get event bits */
DECL|macro|EVIOCGABS
mdefine_line|#define EVIOCGABS(abs)&t;&t;_IOR(&squot;E&squot;, 0x40 + abs, int[5])&t;&t;/* get abs value/limits */ 
multiline_comment|/*&n; * Event types&n; */
DECL|macro|EV_RST
mdefine_line|#define EV_RST&t;&t;&t;0x00
DECL|macro|EV_KEY
mdefine_line|#define EV_KEY&t;&t;&t;0x01
DECL|macro|EV_REL
mdefine_line|#define EV_REL&t;&t;&t;0x02
DECL|macro|EV_ABS
mdefine_line|#define EV_ABS&t;&t;&t;0x03
DECL|macro|EV_LED
mdefine_line|#define EV_LED&t;&t;&t;0x11
DECL|macro|EV_SND
mdefine_line|#define EV_SND&t;&t;&t;0x12
DECL|macro|EV_REP
mdefine_line|#define EV_REP&t;&t;&t;0x14
DECL|macro|EV_MAX
mdefine_line|#define EV_MAX&t;&t;&t;0x1f
multiline_comment|/*&n; * Keys and buttons&n; */
DECL|macro|KEY_RESERVED
mdefine_line|#define KEY_RESERVED&t;&t;0&t;&t;
DECL|macro|KEY_ESC
mdefine_line|#define KEY_ESC&t;&t;&t;1&t;&t;
DECL|macro|KEY_1
mdefine_line|#define KEY_1&t;&t;&t;2&t;&t;
DECL|macro|KEY_2
mdefine_line|#define KEY_2&t;&t;&t;3&t;&t;
DECL|macro|KEY_3
mdefine_line|#define KEY_3&t;&t;&t;4&t;&t;
DECL|macro|KEY_4
mdefine_line|#define KEY_4&t;&t;&t;5&t;&t;
DECL|macro|KEY_5
mdefine_line|#define KEY_5&t;&t;&t;6&t;&t;
DECL|macro|KEY_6
mdefine_line|#define KEY_6&t;&t;&t;7&t;&t;
DECL|macro|KEY_7
mdefine_line|#define KEY_7&t;&t;&t;8&t;&t;
DECL|macro|KEY_8
mdefine_line|#define KEY_8&t;&t;&t;9&t;&t;
DECL|macro|KEY_9
mdefine_line|#define KEY_9&t;&t;&t;10&t;&t;
DECL|macro|KEY_0
mdefine_line|#define KEY_0&t;&t;&t;11&t;&t;
DECL|macro|KEY_MINUS
mdefine_line|#define KEY_MINUS&t;&t;12&t;&t;
DECL|macro|KEY_EQUAL
mdefine_line|#define KEY_EQUAL&t;&t;13&t;&t;
DECL|macro|KEY_BACKSPACE
mdefine_line|#define KEY_BACKSPACE&t;&t;14&t;&t;
DECL|macro|KEY_TAB
mdefine_line|#define KEY_TAB&t;&t;&t;15&t;&t;
DECL|macro|KEY_Q
mdefine_line|#define KEY_Q&t;&t;&t;16&t;&t;
DECL|macro|KEY_W
mdefine_line|#define KEY_W&t;&t;&t;17&t;&t;
DECL|macro|KEY_E
mdefine_line|#define KEY_E&t;&t;&t;18&t;&t;
DECL|macro|KEY_R
mdefine_line|#define KEY_R&t;&t;&t;19&t;&t;
DECL|macro|KEY_T
mdefine_line|#define KEY_T&t;&t;&t;20&t;&t;
DECL|macro|KEY_Y
mdefine_line|#define KEY_Y&t;&t;&t;21&t;&t;
DECL|macro|KEY_U
mdefine_line|#define KEY_U&t;&t;&t;22&t;&t;
DECL|macro|KEY_I
mdefine_line|#define KEY_I&t;&t;&t;23&t;&t;
DECL|macro|KEY_O
mdefine_line|#define KEY_O&t;&t;&t;24&t;&t;
DECL|macro|KEY_P
mdefine_line|#define KEY_P&t;&t;&t;25&t;&t;
DECL|macro|KEY_LEFTBRACE
mdefine_line|#define KEY_LEFTBRACE&t;&t;26&t;&t;
DECL|macro|KEY_RIGHTBRACE
mdefine_line|#define KEY_RIGHTBRACE&t;&t;27&t;&t;
DECL|macro|KEY_ENTER
mdefine_line|#define KEY_ENTER&t;&t;28&t;&t;
DECL|macro|KEY_LEFTCTRL
mdefine_line|#define KEY_LEFTCTRL&t;&t;29&t;&t;
DECL|macro|KEY_A
mdefine_line|#define KEY_A&t;&t;&t;30&t;&t;
DECL|macro|KEY_S
mdefine_line|#define KEY_S&t;&t;&t;31&t;&t;
DECL|macro|KEY_D
mdefine_line|#define KEY_D&t;&t;&t;32&t;&t;
DECL|macro|KEY_F
mdefine_line|#define KEY_F&t;&t;&t;33&t;&t;
DECL|macro|KEY_G
mdefine_line|#define KEY_G&t;&t;&t;34&t;&t;
DECL|macro|KEY_H
mdefine_line|#define KEY_H&t;&t;&t;35&t;&t;
DECL|macro|KEY_J
mdefine_line|#define KEY_J&t;&t;&t;36&t;&t;
DECL|macro|KEY_K
mdefine_line|#define KEY_K&t;&t;&t;37&t;&t;
DECL|macro|KEY_L
mdefine_line|#define KEY_L&t;&t;&t;38&t;&t;
DECL|macro|KEY_SEMICOLON
mdefine_line|#define KEY_SEMICOLON&t;&t;39&t;&t;
DECL|macro|KEY_APOSTROPHE
mdefine_line|#define KEY_APOSTROPHE&t;&t;40&t;&t;
DECL|macro|KEY_GRAVE
mdefine_line|#define KEY_GRAVE&t;&t;41&t;&t;
DECL|macro|KEY_LEFTSHIFT
mdefine_line|#define KEY_LEFTSHIFT&t;&t;42&t;&t;
DECL|macro|KEY_BACKSLASH
mdefine_line|#define KEY_BACKSLASH&t;&t;43&t;&t;
DECL|macro|KEY_Z
mdefine_line|#define KEY_Z&t;&t;&t;44&t;&t;
DECL|macro|KEY_X
mdefine_line|#define KEY_X&t;&t;&t;45&t;&t;
DECL|macro|KEY_C
mdefine_line|#define KEY_C&t;&t;&t;46&t;&t;
DECL|macro|KEY_V
mdefine_line|#define KEY_V&t;&t;&t;47&t;&t;
DECL|macro|KEY_B
mdefine_line|#define KEY_B&t;&t;&t;48&t;&t;
DECL|macro|KEY_N
mdefine_line|#define KEY_N&t;&t;&t;49&t;&t;
DECL|macro|KEY_M
mdefine_line|#define KEY_M&t;&t;&t;50&t;&t;
DECL|macro|KEY_COMMA
mdefine_line|#define KEY_COMMA&t;&t;51&t;&t;
DECL|macro|KEY_DOT
mdefine_line|#define KEY_DOT&t;&t;&t;52&t;&t;
DECL|macro|KEY_SLASH
mdefine_line|#define KEY_SLASH&t;&t;53&t;&t;
DECL|macro|KEY_RIGHTSHIFT
mdefine_line|#define KEY_RIGHTSHIFT&t;&t;54&t;&t;
DECL|macro|KEY_KPASTERISK
mdefine_line|#define KEY_KPASTERISK&t;&t;55&t;&t;
DECL|macro|KEY_LEFTALT
mdefine_line|#define KEY_LEFTALT&t;&t;56&t;&t;
DECL|macro|KEY_SPACE
mdefine_line|#define KEY_SPACE&t;&t;57&t;&t;
DECL|macro|KEY_CAPSLOCK
mdefine_line|#define KEY_CAPSLOCK&t;&t;58&t;&t;
DECL|macro|KEY_F1
mdefine_line|#define KEY_F1&t;&t;&t;59&t;&t;
DECL|macro|KEY_F2
mdefine_line|#define KEY_F2&t;&t;&t;60&t;&t;
DECL|macro|KEY_F3
mdefine_line|#define KEY_F3&t;&t;&t;61&t;&t;
DECL|macro|KEY_F4
mdefine_line|#define KEY_F4&t;&t;&t;62&t;&t;
DECL|macro|KEY_F5
mdefine_line|#define KEY_F5&t;&t;&t;63&t;&t;
DECL|macro|KEY_F6
mdefine_line|#define KEY_F6&t;&t;&t;64&t;&t;
DECL|macro|KEY_F7
mdefine_line|#define KEY_F7&t;&t;&t;65&t;&t;
DECL|macro|KEY_F8
mdefine_line|#define KEY_F8&t;&t;&t;66&t;&t;
DECL|macro|KEY_F9
mdefine_line|#define KEY_F9&t;&t;&t;67&t;&t;
DECL|macro|KEY_F10
mdefine_line|#define KEY_F10&t;&t;&t;68&t;&t;
DECL|macro|KEY_NUMLOCK
mdefine_line|#define KEY_NUMLOCK&t;&t;69&t;&t;
DECL|macro|KEY_SCROLLLOCK
mdefine_line|#define KEY_SCROLLLOCK&t;&t;70&t;&t;
DECL|macro|KEY_KP7
mdefine_line|#define KEY_KP7&t;&t;&t;71&t;&t;
DECL|macro|KEY_KP8
mdefine_line|#define KEY_KP8&t;&t;&t;72&t;&t;
DECL|macro|KEY_KP9
mdefine_line|#define KEY_KP9&t;&t;&t;73&t;&t;
DECL|macro|KEY_KPMINUS
mdefine_line|#define KEY_KPMINUS&t;&t;74&t;&t;
DECL|macro|KEY_KP4
mdefine_line|#define KEY_KP4&t;&t;&t;75&t;&t;
DECL|macro|KEY_KP5
mdefine_line|#define KEY_KP5&t;&t;&t;76&t;&t;
DECL|macro|KEY_KP6
mdefine_line|#define KEY_KP6&t;&t;&t;77&t;&t;
DECL|macro|KEY_KPPLUS
mdefine_line|#define KEY_KPPLUS&t;&t;78&t;&t;
DECL|macro|KEY_KP1
mdefine_line|#define KEY_KP1&t;&t;&t;79&t;&t;
DECL|macro|KEY_KP2
mdefine_line|#define KEY_KP2&t;&t;&t;80&t;&t;
DECL|macro|KEY_KP3
mdefine_line|#define KEY_KP3&t;&t;&t;81&t;&t;
DECL|macro|KEY_KP0
mdefine_line|#define KEY_KP0&t;&t;&t;82&t;&t;
DECL|macro|KEY_KPDOT
mdefine_line|#define KEY_KPDOT&t;&t;83&t;&t;
DECL|macro|KEY_103RD
mdefine_line|#define KEY_103RD&t;&t;84
DECL|macro|KEY_F13
mdefine_line|#define KEY_F13&t;&t;&t;85&t;&t;
DECL|macro|KEY_102ND
mdefine_line|#define KEY_102ND&t;&t;86&t;&t;
DECL|macro|KEY_F11
mdefine_line|#define KEY_F11&t;&t;&t;87&t;&t;
DECL|macro|KEY_F12
mdefine_line|#define KEY_F12&t;&t;&t;88&t;&t;
DECL|macro|KEY_F14
mdefine_line|#define KEY_F14&t;&t;&t;89&t;&t;
DECL|macro|KEY_F15
mdefine_line|#define KEY_F15&t;&t;&t;90&t;&t;
DECL|macro|KEY_F16
mdefine_line|#define KEY_F16&t;&t;&t;91&t;&t;
DECL|macro|KEY_F17
mdefine_line|#define KEY_F17&t;&t;&t;92&t;&t;
DECL|macro|KEY_F18
mdefine_line|#define KEY_F18&t;&t;&t;93&t;&t;
DECL|macro|KEY_F19
mdefine_line|#define KEY_F19&t;&t;&t;94&t;&t;
DECL|macro|KEY_F20
mdefine_line|#define KEY_F20&t;&t;&t;95&t;&t;
DECL|macro|KEY_KPENTER
mdefine_line|#define KEY_KPENTER&t;&t;96&t;&t;
DECL|macro|KEY_RIGHTCTRL
mdefine_line|#define KEY_RIGHTCTRL&t;&t;97&t;&t;
DECL|macro|KEY_KPSLASH
mdefine_line|#define KEY_KPSLASH&t;&t;98&t;&t;
DECL|macro|KEY_SYSRQ
mdefine_line|#define KEY_SYSRQ&t;&t;99&t;&t;
DECL|macro|KEY_RIGHTALT
mdefine_line|#define KEY_RIGHTALT&t;&t;100&t;&t;
DECL|macro|KEY_LINEFEED
mdefine_line|#define KEY_LINEFEED&t;&t;101&t;&t;
DECL|macro|KEY_HOME
mdefine_line|#define KEY_HOME&t;&t;102&t;&t;
DECL|macro|KEY_UP
mdefine_line|#define KEY_UP&t;&t;&t;103&t;&t;
DECL|macro|KEY_PAGEUP
mdefine_line|#define KEY_PAGEUP&t;&t;104&t;&t;
DECL|macro|KEY_LEFT
mdefine_line|#define KEY_LEFT&t;&t;105&t;&t;
DECL|macro|KEY_RIGHT
mdefine_line|#define KEY_RIGHT&t;&t;106&t;&t;
DECL|macro|KEY_END
mdefine_line|#define KEY_END&t;&t;&t;107&t;&t;
DECL|macro|KEY_DOWN
mdefine_line|#define KEY_DOWN&t;&t;108&t;&t;
DECL|macro|KEY_PAGEDOWN
mdefine_line|#define KEY_PAGEDOWN&t;&t;109&t;&t;
DECL|macro|KEY_INSERT
mdefine_line|#define KEY_INSERT&t;&t;110&t;&t;
DECL|macro|KEY_DELETE
mdefine_line|#define KEY_DELETE&t;&t;111&t;&t;
DECL|macro|KEY_MACRO
mdefine_line|#define KEY_MACRO&t;&t;112&t;&t;
DECL|macro|KEY_MUTE
mdefine_line|#define KEY_MUTE&t;&t;113&t;&t;
DECL|macro|KEY_VOLUMEDOWN
mdefine_line|#define KEY_VOLUMEDOWN&t;&t;114&t;&t;
DECL|macro|KEY_VOLUMEUP
mdefine_line|#define KEY_VOLUMEUP&t;&t;115&t;&t;
DECL|macro|KEY_POWER
mdefine_line|#define KEY_POWER&t;&t;116&t;&t;
DECL|macro|KEY_KPEQUAL
mdefine_line|#define KEY_KPEQUAL&t;&t;117&t;&t;
DECL|macro|KEY_KPPLUSMINUS
mdefine_line|#define KEY_KPPLUSMINUS&t;&t;118&t;&t;
DECL|macro|KEY_PAUSE
mdefine_line|#define KEY_PAUSE&t;&t;119&t;&t;
DECL|macro|KEY_F21
mdefine_line|#define KEY_F21&t;&t;&t;120&t;&t;
DECL|macro|KEY_F22
mdefine_line|#define KEY_F22&t;&t;&t;121&t;&t;
DECL|macro|KEY_F23
mdefine_line|#define KEY_F23&t;&t;&t;122&t;&t;
DECL|macro|KEY_F24
mdefine_line|#define KEY_F24&t;&t;&t;123&t;&t;
DECL|macro|KEY_KPCOMMA
mdefine_line|#define KEY_KPCOMMA&t;&t;124
DECL|macro|KEY_LEFTMETA
mdefine_line|#define KEY_LEFTMETA&t;&t;125&t;&t;
DECL|macro|KEY_RIGHTMETA
mdefine_line|#define KEY_RIGHTMETA&t;&t;126&t;&t;
DECL|macro|KEY_COMPOSE
mdefine_line|#define KEY_COMPOSE&t;&t;127&t;&t;
DECL|macro|KEY_STOP
mdefine_line|#define KEY_STOP&t;&t;128&t;&t;
DECL|macro|KEY_AGAIN
mdefine_line|#define KEY_AGAIN&t;&t;129&t;&t;
DECL|macro|KEY_PROPS
mdefine_line|#define KEY_PROPS&t;&t;130&t;&t;
DECL|macro|KEY_UNDO
mdefine_line|#define KEY_UNDO&t;&t;131&t;&t;
DECL|macro|KEY_FRONT
mdefine_line|#define KEY_FRONT&t;&t;132&t;&t;
DECL|macro|KEY_COPY
mdefine_line|#define KEY_COPY&t;&t;133&t;&t;
DECL|macro|KEY_OPEN
mdefine_line|#define KEY_OPEN&t;&t;134&t;&t;
DECL|macro|KEY_PASTE
mdefine_line|#define KEY_PASTE&t;&t;135&t;&t;
DECL|macro|KEY_FIND
mdefine_line|#define KEY_FIND&t;&t;136&t;&t;
DECL|macro|KEY_CUT
mdefine_line|#define KEY_CUT&t;&t;&t;137&t;&t;
DECL|macro|KEY_HELP
mdefine_line|#define KEY_HELP&t;&t;138&t;&t;
DECL|macro|KEY_MENU
mdefine_line|#define KEY_MENU&t;&t;139&t;&t;
DECL|macro|KEY_CALC
mdefine_line|#define KEY_CALC&t;&t;140&t;&t;
DECL|macro|KEY_SETUP
mdefine_line|#define KEY_SETUP&t;&t;141&t;&t;
DECL|macro|KEY_SLEEP
mdefine_line|#define KEY_SLEEP&t;&t;142&t;&t;
DECL|macro|KEY_WAKEUP
mdefine_line|#define KEY_WAKEUP&t;&t;143&t;&t;
DECL|macro|KEY_FILE
mdefine_line|#define KEY_FILE&t;&t;144&t;&t;
DECL|macro|KEY_SENDFILE
mdefine_line|#define KEY_SENDFILE&t;&t;145&t;&t;
DECL|macro|KEY_DELETEFILE
mdefine_line|#define KEY_DELETEFILE&t;&t;146&t;&t;
DECL|macro|KEY_XFER
mdefine_line|#define KEY_XFER&t;&t;147&t;&t;
DECL|macro|KEY_PROG1
mdefine_line|#define KEY_PROG1&t;&t;148&t;&t;
DECL|macro|KEY_PROG2
mdefine_line|#define KEY_PROG2&t;&t;149&t;&t;
DECL|macro|KEY_WWW
mdefine_line|#define KEY_WWW&t;&t;&t;150&t;&t;
DECL|macro|KEY_MSDOS
mdefine_line|#define KEY_MSDOS&t;&t;151&t;&t;
DECL|macro|KEY_COFFEE
mdefine_line|#define KEY_COFFEE&t;&t;152&t;&t;
DECL|macro|KEY_DIRECTION
mdefine_line|#define KEY_DIRECTION&t;&t;153&t;&t;
DECL|macro|KEY_CYCLEWINDOWS
mdefine_line|#define KEY_CYCLEWINDOWS&t;154&t;&t;
DECL|macro|KEY_MAIL
mdefine_line|#define KEY_MAIL&t;&t;155
DECL|macro|KEY_BOOKMARKS
mdefine_line|#define KEY_BOOKMARKS&t;&t;156
DECL|macro|KEY_COMPUTER
mdefine_line|#define KEY_COMPUTER&t;&t;157
DECL|macro|KEY_BACK
mdefine_line|#define KEY_BACK&t;&t;158
DECL|macro|KEY_FORWARD
mdefine_line|#define KEY_FORWARD&t;&t;159
DECL|macro|KEY_CLOSECD
mdefine_line|#define KEY_CLOSECD&t;&t;160&t;&t;
DECL|macro|KEY_EJECTCD
mdefine_line|#define KEY_EJECTCD&t;&t;161&t;&t;
DECL|macro|KEY_EJECTCLOSECD
mdefine_line|#define KEY_EJECTCLOSECD&t;162&t;&t;
DECL|macro|KEY_NEXTSONG
mdefine_line|#define KEY_NEXTSONG&t;&t;163&t;&t;
DECL|macro|KEY_PLAYPAUSE
mdefine_line|#define KEY_PLAYPAUSE&t;&t;164&t;&t;
DECL|macro|KEY_PREVIOUSSONG
mdefine_line|#define KEY_PREVIOUSSONG&t;165&t;&t;
DECL|macro|KEY_STOPCD
mdefine_line|#define KEY_STOPCD&t;&t;166&t;&t;
DECL|macro|KEY_RECORD
mdefine_line|#define KEY_RECORD&t;&t;167&t;&t;
DECL|macro|KEY_REWIND
mdefine_line|#define KEY_REWIND&t;&t;168&t;&t;
DECL|macro|KEY_PHONE
mdefine_line|#define KEY_PHONE&t;&t;169
DECL|macro|KEY_CONFIG
mdefine_line|#define KEY_CONFIG&t;&t;171
DECL|macro|KEY_HOMEPAGE
mdefine_line|#define KEY_HOMEPAGE&t;&t;172
DECL|macro|KEY_REFRESH
mdefine_line|#define KEY_REFRESH&t;&t;173
DECL|macro|KEY_EXIT
mdefine_line|#define KEY_EXIT&t;&t;174
DECL|macro|KEY_MOVE
mdefine_line|#define KEY_MOVE&t;&t;175
DECL|macro|KEY_EDIT
mdefine_line|#define KEY_EDIT&t;&t;176
DECL|macro|KEY_SCROLLUP
mdefine_line|#define KEY_SCROLLUP&t;&t;177
DECL|macro|KEY_SCROLLDOWN
mdefine_line|#define KEY_SCROLLDOWN&t;&t;178
DECL|macro|KEY_KPLEFTPAREN
mdefine_line|#define KEY_KPLEFTPAREN&t;&t;179
DECL|macro|KEY_KPRIGHTPAREN
mdefine_line|#define KEY_KPRIGHTPAREN&t;180
DECL|macro|KEY_INTL1
mdefine_line|#define KEY_INTL1&t;&t;181
DECL|macro|KEY_INTL2
mdefine_line|#define KEY_INTL2&t;&t;182
DECL|macro|KEY_INTL3
mdefine_line|#define KEY_INTL3&t;&t;183
DECL|macro|KEY_INTL4
mdefine_line|#define KEY_INTL4&t;&t;184
DECL|macro|KEY_INTL5
mdefine_line|#define KEY_INTL5&t;&t;185
DECL|macro|KEY_INTL6
mdefine_line|#define KEY_INTL6&t;&t;186
DECL|macro|KEY_INTL7
mdefine_line|#define KEY_INTL7&t;&t;187
DECL|macro|KEY_INTL8
mdefine_line|#define KEY_INTL8&t;&t;188
DECL|macro|KEY_INTL9
mdefine_line|#define KEY_INTL9&t;&t;189
DECL|macro|KEY_LANG1
mdefine_line|#define KEY_LANG1&t;&t;190
DECL|macro|KEY_LANG2
mdefine_line|#define KEY_LANG2&t;&t;191
DECL|macro|KEY_LANG3
mdefine_line|#define KEY_LANG3&t;&t;192
DECL|macro|KEY_LANG4
mdefine_line|#define KEY_LANG4&t;&t;193
DECL|macro|KEY_LANG5
mdefine_line|#define KEY_LANG5&t;&t;194
DECL|macro|KEY_LANG6
mdefine_line|#define KEY_LANG6&t;&t;195
DECL|macro|KEY_LANG7
mdefine_line|#define KEY_LANG7&t;&t;196
DECL|macro|KEY_LANG8
mdefine_line|#define KEY_LANG8&t;&t;197
DECL|macro|KEY_LANG9
mdefine_line|#define KEY_LANG9&t;&t;198
DECL|macro|KEY_UNKNOWN
mdefine_line|#define KEY_UNKNOWN&t;&t;200
DECL|macro|BTN_MISC
mdefine_line|#define BTN_MISC&t;&t;0x100
DECL|macro|BTN_0
mdefine_line|#define BTN_0&t;&t;&t;0x100
DECL|macro|BTN_1
mdefine_line|#define BTN_1&t;&t;&t;0x101
DECL|macro|BTN_2
mdefine_line|#define BTN_2&t;&t;&t;0x102
DECL|macro|BTN_3
mdefine_line|#define BTN_3&t;&t;&t;0x103
DECL|macro|BTN_4
mdefine_line|#define BTN_4&t;&t;&t;0x104
DECL|macro|BTN_5
mdefine_line|#define BTN_5&t;&t;&t;0x105
DECL|macro|BTN_6
mdefine_line|#define BTN_6&t;&t;&t;0x106
DECL|macro|BTN_7
mdefine_line|#define BTN_7&t;&t;&t;0x107
DECL|macro|BTN_8
mdefine_line|#define BTN_8&t;&t;&t;0x108
DECL|macro|BTN_9
mdefine_line|#define BTN_9&t;&t;&t;0x109
DECL|macro|BTN_MOUSE
mdefine_line|#define BTN_MOUSE&t;&t;0x110
DECL|macro|BTN_LEFT
mdefine_line|#define BTN_LEFT&t;&t;0x110
DECL|macro|BTN_RIGHT
mdefine_line|#define BTN_RIGHT&t;&t;0x111
DECL|macro|BTN_MIDDLE
mdefine_line|#define BTN_MIDDLE&t;&t;0x112
DECL|macro|BTN_SIDE
mdefine_line|#define BTN_SIDE&t;&t;0x113
DECL|macro|BTN_EXTRA
mdefine_line|#define BTN_EXTRA&t;&t;0x114
DECL|macro|BTN_FORWARD
mdefine_line|#define BTN_FORWARD&t;&t;0x115
DECL|macro|BTN_BACK
mdefine_line|#define BTN_BACK&t;&t;0x116
DECL|macro|BTN_JOYSTICK
mdefine_line|#define BTN_JOYSTICK&t;&t;0x120
DECL|macro|BTN_TRIGGER
mdefine_line|#define BTN_TRIGGER&t;&t;0x120
DECL|macro|BTN_THUMB
mdefine_line|#define BTN_THUMB&t;&t;0x121
DECL|macro|BTN_THUMB2
mdefine_line|#define BTN_THUMB2&t;&t;0x122
DECL|macro|BTN_TOP
mdefine_line|#define BTN_TOP&t;&t;&t;0x123
DECL|macro|BTN_TOP2
mdefine_line|#define BTN_TOP2&t;&t;0x124
DECL|macro|BTN_PINKIE
mdefine_line|#define BTN_PINKIE&t;&t;0x125
DECL|macro|BTN_BASE
mdefine_line|#define BTN_BASE&t;&t;0x126
DECL|macro|BTN_BASE2
mdefine_line|#define BTN_BASE2&t;&t;0x127
DECL|macro|BTN_BASE3
mdefine_line|#define BTN_BASE3&t;&t;0x128
DECL|macro|BTN_BASE4
mdefine_line|#define BTN_BASE4&t;&t;0x129
DECL|macro|BTN_BASE5
mdefine_line|#define BTN_BASE5&t;&t;0x12a
DECL|macro|BTN_BASE6
mdefine_line|#define BTN_BASE6&t;&t;0x12b
DECL|macro|BTN_GAMEPAD
mdefine_line|#define BTN_GAMEPAD&t;&t;0x130
DECL|macro|BTN_A
mdefine_line|#define BTN_A&t;&t;&t;0x130
DECL|macro|BTN_B
mdefine_line|#define BTN_B&t;&t;&t;0x131
DECL|macro|BTN_C
mdefine_line|#define BTN_C&t;&t;&t;0x132
DECL|macro|BTN_X
mdefine_line|#define BTN_X&t;&t;&t;0x133
DECL|macro|BTN_Y
mdefine_line|#define BTN_Y&t;&t;&t;0x134
DECL|macro|BTN_Z
mdefine_line|#define BTN_Z&t;&t;&t;0x135
DECL|macro|BTN_TL
mdefine_line|#define BTN_TL&t;&t;&t;0x136
DECL|macro|BTN_TR
mdefine_line|#define BTN_TR&t;&t;&t;0x137
DECL|macro|BTN_TL2
mdefine_line|#define BTN_TL2&t;&t;&t;0x138
DECL|macro|BTN_TR2
mdefine_line|#define BTN_TR2&t;&t;&t;0x139
DECL|macro|BTN_SELECT
mdefine_line|#define BTN_SELECT&t;&t;0x13a
DECL|macro|BTN_START
mdefine_line|#define BTN_START&t;&t;0x13b
DECL|macro|BTN_MODE
mdefine_line|#define BTN_MODE&t;&t;0x13c
DECL|macro|BTN_DIGI
mdefine_line|#define BTN_DIGI&t;&t;0x140
DECL|macro|BTN_TOOL_PEN
mdefine_line|#define BTN_TOOL_PEN&t;&t;0x140
DECL|macro|BTN_TOOL_RUBBER
mdefine_line|#define BTN_TOOL_RUBBER&t;&t;0x141
DECL|macro|BTN_TOOL_BRUSH
mdefine_line|#define BTN_TOOL_BRUSH&t;&t;0x142
DECL|macro|BTN_TOOL_PENCIL
mdefine_line|#define BTN_TOOL_PENCIL&t;&t;0x143
DECL|macro|BTN_TOOL_AIRBRUSH
mdefine_line|#define BTN_TOOL_AIRBRUSH&t;0x144
DECL|macro|BTN_TOOL_FINGER
mdefine_line|#define BTN_TOOL_FINGER&t;&t;0x145
DECL|macro|BTN_TOOL_MOUSE
mdefine_line|#define BTN_TOOL_MOUSE&t;&t;0x146
DECL|macro|BTN_TOOL_LENS
mdefine_line|#define BTN_TOOL_LENS&t;&t;0x147
DECL|macro|BTN_TOUCH
mdefine_line|#define BTN_TOUCH&t;&t;0x14a
DECL|macro|BTN_STYLUS
mdefine_line|#define BTN_STYLUS&t;&t;0x14b
DECL|macro|BTN_STYLUS2
mdefine_line|#define BTN_STYLUS2&t;&t;0x14c
DECL|macro|KEY_MAX
mdefine_line|#define KEY_MAX&t;&t;&t;0x1ff
multiline_comment|/*&n; * Relative axes&n; */
DECL|macro|REL_X
mdefine_line|#define REL_X&t;&t;&t;0x00
DECL|macro|REL_Y
mdefine_line|#define REL_Y&t;&t;&t;0x01
DECL|macro|REL_Z
mdefine_line|#define REL_Z&t;&t;&t;0x02
DECL|macro|REL_HWHEEL
mdefine_line|#define REL_HWHEEL&t;&t;0x06
DECL|macro|REL_DIAL
mdefine_line|#define REL_DIAL&t;&t;0x07
DECL|macro|REL_WHEEL
mdefine_line|#define REL_WHEEL&t;&t;0x08
DECL|macro|REL_MISC
mdefine_line|#define REL_MISC&t;&t;0x09
DECL|macro|REL_MAX
mdefine_line|#define REL_MAX&t;&t;&t;0x0f
multiline_comment|/*&n; * Absolute axes&n; */
DECL|macro|ABS_X
mdefine_line|#define ABS_X&t;&t;&t;0x00
DECL|macro|ABS_Y
mdefine_line|#define ABS_Y&t;&t;&t;0x01
DECL|macro|ABS_Z
mdefine_line|#define ABS_Z&t;&t;&t;0x02
DECL|macro|ABS_RX
mdefine_line|#define ABS_RX&t;&t;&t;0x03
DECL|macro|ABS_RY
mdefine_line|#define ABS_RY&t;&t;&t;0x04
DECL|macro|ABS_RZ
mdefine_line|#define ABS_RZ&t;&t;&t;0x05
DECL|macro|ABS_THROTTLE
mdefine_line|#define ABS_THROTTLE&t;&t;0x06
DECL|macro|ABS_RUDDER
mdefine_line|#define ABS_RUDDER&t;&t;0x07
DECL|macro|ABS_WHEEL
mdefine_line|#define ABS_WHEEL&t;&t;0x08
DECL|macro|ABS_GAS
mdefine_line|#define ABS_GAS&t;&t;&t;0x09
DECL|macro|ABS_BRAKE
mdefine_line|#define ABS_BRAKE&t;&t;0x0a
DECL|macro|ABS_HAT0X
mdefine_line|#define ABS_HAT0X&t;&t;0x10
DECL|macro|ABS_HAT0Y
mdefine_line|#define ABS_HAT0Y&t;&t;0x11
DECL|macro|ABS_HAT1X
mdefine_line|#define ABS_HAT1X&t;&t;0x12
DECL|macro|ABS_HAT1Y
mdefine_line|#define ABS_HAT1Y&t;&t;0x13
DECL|macro|ABS_HAT2X
mdefine_line|#define ABS_HAT2X&t;&t;0x14
DECL|macro|ABS_HAT2Y
mdefine_line|#define ABS_HAT2Y&t;&t;0x15
DECL|macro|ABS_HAT3X
mdefine_line|#define ABS_HAT3X&t;&t;0x16
DECL|macro|ABS_HAT3Y
mdefine_line|#define ABS_HAT3Y&t;&t;0x17
DECL|macro|ABS_PRESSURE
mdefine_line|#define ABS_PRESSURE&t;&t;0x18
DECL|macro|ABS_DISTANCE
mdefine_line|#define ABS_DISTANCE&t;&t;0x19
DECL|macro|ABS_TILT_X
mdefine_line|#define ABS_TILT_X&t;&t;0x1a
DECL|macro|ABS_TILT_Y
mdefine_line|#define ABS_TILT_Y&t;&t;0x1b
DECL|macro|ABS_MISC
mdefine_line|#define ABS_MISC&t;&t;0x1c
DECL|macro|ABS_MAX
mdefine_line|#define ABS_MAX&t;&t;&t;0x1f
multiline_comment|/*&n; * LEDs&n; */
DECL|macro|LED_NUML
mdefine_line|#define LED_NUML&t;&t;0x00
DECL|macro|LED_CAPSL
mdefine_line|#define LED_CAPSL&t;&t;0x01
DECL|macro|LED_SCROLLL
mdefine_line|#define LED_SCROLLL&t;&t;0x02
DECL|macro|LED_COMPOSE
mdefine_line|#define LED_COMPOSE&t;&t;0x03
DECL|macro|LED_KANA
mdefine_line|#define LED_KANA&t;&t;0x04
DECL|macro|LED_MAX
mdefine_line|#define LED_MAX&t;&t;&t;0x0f
multiline_comment|/*&n; * Autorepeat values&n; */
DECL|macro|REP_DELAY
mdefine_line|#define REP_DELAY&t;&t;0x00
DECL|macro|REP_PERIOD
mdefine_line|#define REP_PERIOD&t;&t;0x01
DECL|macro|REP_MAX
mdefine_line|#define REP_MAX&t;&t;&t;0x01
multiline_comment|/*&n; * Sounds&n; */
DECL|macro|SND_CLICK
mdefine_line|#define SND_CLICK&t;&t;0x00
DECL|macro|SND_BELL
mdefine_line|#define SND_BELL&t;&t;0x01
DECL|macro|SND_MAX
mdefine_line|#define SND_MAX&t;&t;&t;0x07
multiline_comment|/*&n; * IDs.&n; */
DECL|macro|ID_BUS
mdefine_line|#define ID_BUS&t;&t;&t;0
DECL|macro|ID_VENDOR
mdefine_line|#define ID_VENDOR&t;&t;1
DECL|macro|ID_PRODUCT
mdefine_line|#define ID_PRODUCT&t;&t;2
DECL|macro|ID_VERSION
mdefine_line|#define ID_VERSION&t;&t;3
DECL|macro|BUS_PCI
mdefine_line|#define BUS_PCI&t;&t;&t;0x01
DECL|macro|BUS_ISAPNP
mdefine_line|#define BUS_ISAPNP&t;&t;0x02
DECL|macro|BUS_USB
mdefine_line|#define BUS_USB&t;&t;&t;0x03
DECL|macro|BUS_ISA
mdefine_line|#define BUS_ISA&t;&t;&t;0x10
DECL|macro|BUS_I8042
mdefine_line|#define BUS_I8042&t;&t;0x11
DECL|macro|BUS_XTKBD
mdefine_line|#define BUS_XTKBD&t;&t;0x12
DECL|macro|BUS_RS232
mdefine_line|#define BUS_RS232&t;&t;0x13
DECL|macro|BUS_GAMEPORT
mdefine_line|#define BUS_GAMEPORT&t;&t;0x14
DECL|macro|BUS_PARPORT
mdefine_line|#define BUS_PARPORT&t;&t;0x15
DECL|macro|BUS_AMIGA
mdefine_line|#define BUS_AMIGA&t;&t;0x16
DECL|macro|BUS_ADB
mdefine_line|#define BUS_ADB&t;&t;&t;0x17
DECL|macro|BUS_I2C
mdefine_line|#define BUS_I2C&t;&t;&t;0x18
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * In-kernel definitions.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|NBITS
mdefine_line|#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;(1UL&lt;&lt;((x)%BITS_PER_LONG))
DECL|macro|LONG
mdefine_line|#define LONG(x) ((x)/BITS_PER_LONG)
DECL|struct|input_dev
r_struct
id|input_dev
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|idbus
r_int
r_int
id|idbus
suffix:semicolon
DECL|member|idvendor
r_int
r_int
id|idvendor
suffix:semicolon
DECL|member|idproduct
r_int
r_int
id|idproduct
suffix:semicolon
DECL|member|idversion
r_int
r_int
id|idversion
suffix:semicolon
DECL|member|evbit
r_int
r_int
id|evbit
(braket
id|NBITS
c_func
(paren
id|EV_MAX
)paren
)braket
suffix:semicolon
DECL|member|keybit
r_int
r_int
id|keybit
(braket
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
)braket
suffix:semicolon
DECL|member|relbit
r_int
r_int
id|relbit
(braket
id|NBITS
c_func
(paren
id|REL_MAX
)paren
)braket
suffix:semicolon
DECL|member|absbit
r_int
r_int
id|absbit
(braket
id|NBITS
c_func
(paren
id|ABS_MAX
)paren
)braket
suffix:semicolon
DECL|member|ledbit
r_int
r_int
id|ledbit
(braket
id|NBITS
c_func
(paren
id|LED_MAX
)paren
)braket
suffix:semicolon
DECL|member|sndbit
r_int
r_int
id|sndbit
(braket
id|NBITS
c_func
(paren
id|SND_MAX
)paren
)braket
suffix:semicolon
DECL|member|keycodemax
r_int
r_int
id|keycodemax
suffix:semicolon
DECL|member|keycodesize
r_int
r_int
id|keycodesize
suffix:semicolon
DECL|member|keycode
r_void
op_star
id|keycode
suffix:semicolon
DECL|member|repeat_key
r_int
r_int
id|repeat_key
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|abs
r_int
id|abs
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|rep
r_int
id|rep
(braket
id|REP_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|key
r_int
r_int
id|key
(braket
id|NBITS
c_func
(paren
id|KEY_MAX
)paren
)braket
suffix:semicolon
DECL|member|led
r_int
r_int
id|led
(braket
id|NBITS
c_func
(paren
id|LED_MAX
)paren
)braket
suffix:semicolon
DECL|member|snd
r_int
r_int
id|snd
(braket
id|NBITS
c_func
(paren
id|SND_MAX
)paren
)braket
suffix:semicolon
DECL|member|absmax
r_int
id|absmax
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absmin
r_int
id|absmin
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absfuzz
r_int
id|absfuzz
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|absflat
r_int
id|absflat
(braket
id|ABS_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|event
r_int
(paren
op_star
id|event
)paren
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
DECL|member|next
r_struct
id|input_dev
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|input_handler
r_struct
id|input_handler
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|event
r_void
(paren
op_star
id|event
)paren
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|member|connect
r_struct
id|input_handle
op_star
(paren
op_star
id|connect
)paren
(paren
r_struct
id|input_handler
op_star
id|handler
comma
r_struct
id|input_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|member|disconnect
r_void
(paren
op_star
id|disconnect
)paren
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
op_star
id|handle
suffix:semicolon
DECL|member|next
r_struct
id|input_handler
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|input_handle
r_struct
id|input_handle
(brace
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
DECL|member|handler
r_struct
id|input_handler
op_star
id|handler
suffix:semicolon
DECL|member|dnext
r_struct
id|input_handle
op_star
id|dnext
suffix:semicolon
DECL|member|hnext
r_struct
id|input_handle
op_star
id|hnext
suffix:semicolon
)brace
suffix:semicolon
r_void
id|input_register_device
c_func
(paren
r_struct
id|input_dev
op_star
)paren
suffix:semicolon
r_void
id|input_unregister_device
c_func
(paren
r_struct
id|input_dev
op_star
)paren
suffix:semicolon
r_void
id|input_register_handler
c_func
(paren
r_struct
id|input_handler
op_star
)paren
suffix:semicolon
r_void
id|input_unregister_handler
c_func
(paren
r_struct
id|input_handler
op_star
)paren
suffix:semicolon
r_int
id|input_open_device
c_func
(paren
r_struct
id|input_handle
op_star
)paren
suffix:semicolon
r_void
id|input_close_device
c_func
(paren
r_struct
id|input_handle
op_star
)paren
suffix:semicolon
id|devfs_handle_t
id|input_register_minor
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|minor
comma
r_int
id|minor_base
)paren
suffix:semicolon
r_void
id|input_unregister_minor
c_func
(paren
id|devfs_handle_t
id|handle
)paren
suffix:semicolon
r_void
id|input_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
suffix:semicolon
DECL|macro|input_report_key
mdefine_line|#define input_report_key(a,b,c) input_event(a, EV_KEY, b, !!(c))
DECL|macro|input_report_rel
mdefine_line|#define input_report_rel(a,b,c) input_event(a, EV_REL, b, c)
DECL|macro|input_report_abs
mdefine_line|#define input_report_abs(a,b,c) input_event(a, EV_ABS, b, c)
macro_line|#endif
macro_line|#endif
eof
