multiline_comment|/*&n; * console_struct.h&n; *&n; * Data structure and defines shared between console.c, vga.c and tga.c&n; */
DECL|macro|NPAR
mdefine_line|#define NPAR 16
DECL|struct|vc_data
r_struct
id|vc_data
(brace
DECL|member|vc_screenbuf_size
r_int
r_int
id|vc_screenbuf_size
suffix:semicolon
DECL|member|vc_video_erase_char
r_int
r_int
id|vc_video_erase_char
suffix:semicolon
multiline_comment|/* Background erase character */
DECL|member|vc_attr
r_int
r_char
id|vc_attr
suffix:semicolon
multiline_comment|/* Current attributes */
DECL|member|vc_def_color
r_int
r_char
id|vc_def_color
suffix:semicolon
multiline_comment|/* Default colors */
DECL|member|vc_color
r_int
r_char
id|vc_color
suffix:semicolon
multiline_comment|/* Foreground &amp; background */
DECL|member|vc_s_color
r_int
r_char
id|vc_s_color
suffix:semicolon
multiline_comment|/* Saved foreground &amp; background */
DECL|member|vc_ulcolor
r_int
r_char
id|vc_ulcolor
suffix:semicolon
multiline_comment|/* Colour for underline mode */
DECL|member|vc_halfcolor
r_int
r_char
id|vc_halfcolor
suffix:semicolon
multiline_comment|/* Colour for half intensity mode */
DECL|member|vc_origin
r_int
r_int
id|vc_origin
suffix:semicolon
multiline_comment|/* Used for EGA/VGA fast scroll&t;*/
DECL|member|vc_scr_end
r_int
r_int
id|vc_scr_end
suffix:semicolon
multiline_comment|/* Used for EGA/VGA fast scroll&t;*/
DECL|member|vc_pos
r_int
r_int
id|vc_pos
suffix:semicolon
DECL|member|vc_x
DECL|member|vc_y
r_int
r_int
id|vc_x
comma
id|vc_y
suffix:semicolon
DECL|member|vc_top
DECL|member|vc_bottom
r_int
r_int
id|vc_top
comma
id|vc_bottom
suffix:semicolon
DECL|member|vc_state
r_int
r_int
id|vc_state
suffix:semicolon
DECL|member|vc_npar
DECL|member|vc_par
r_int
r_int
id|vc_npar
comma
id|vc_par
(braket
id|NPAR
)braket
suffix:semicolon
DECL|member|vc_video_mem_start
r_int
r_int
id|vc_video_mem_start
suffix:semicolon
multiline_comment|/* Start of video RAM&t;&t;*/
DECL|member|vc_video_mem_end
r_int
r_int
id|vc_video_mem_end
suffix:semicolon
multiline_comment|/* End of video RAM (sort of)&t;*/
DECL|member|vc_saved_x
r_int
r_int
id|vc_saved_x
suffix:semicolon
DECL|member|vc_saved_y
r_int
r_int
id|vc_saved_y
suffix:semicolon
multiline_comment|/* mode flags */
DECL|member|vc_charset
r_int
r_int
id|vc_charset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Character set G0 / G1 */
DECL|member|vc_s_charset
r_int
r_int
id|vc_s_charset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Saved character set */
DECL|member|vc_disp_ctrl
r_int
r_int
id|vc_disp_ctrl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Display chars &lt; 32? */
DECL|member|vc_toggle_meta
r_int
r_int
id|vc_toggle_meta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Toggle high bit? */
DECL|member|vc_decscnm
r_int
r_int
id|vc_decscnm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Screen Mode */
DECL|member|vc_decom
r_int
r_int
id|vc_decom
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Origin Mode */
DECL|member|vc_decawm
r_int
r_int
id|vc_decawm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Autowrap Mode */
DECL|member|vc_deccm
r_int
r_int
id|vc_deccm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cursor Visible */
DECL|member|vc_decim
r_int
r_int
id|vc_decim
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Insert Mode */
DECL|member|vc_deccolm
r_int
r_int
id|vc_deccolm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 80/132 Column Mode */
multiline_comment|/* attribute flags */
DECL|member|vc_intensity
r_int
r_int
id|vc_intensity
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 0=half-bright, 1=normal, 2=bold */
DECL|member|vc_underline
r_int
r_int
id|vc_underline
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_blink
r_int
r_int
id|vc_blink
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_reverse
r_int
r_int
id|vc_reverse
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_intensity
r_int
r_int
id|vc_s_intensity
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* saved rendition */
DECL|member|vc_s_underline
r_int
r_int
id|vc_s_underline
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_blink
r_int
r_int
id|vc_s_blink
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_s_reverse
r_int
r_int
id|vc_s_reverse
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* misc */
DECL|member|vc_ques
r_int
r_int
id|vc_ques
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_need_wrap
r_int
r_int
id|vc_need_wrap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vc_has_scrolled
r_int
r_int
id|vc_has_scrolled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Info for unblank_screen */
DECL|member|vc_kmalloced
r_int
r_int
id|vc_kmalloced
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* kfree_s() needed */
DECL|member|vc_report_mouse
r_int
r_int
id|vc_report_mouse
suffix:colon
l_int|2
suffix:semicolon
DECL|member|vc_utf
r_int
r_char
id|vc_utf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unicode UTF-8 encoding */
DECL|member|vc_utf_count
r_int
r_char
id|vc_utf_count
suffix:semicolon
DECL|member|vc_utf_char
r_int
id|vc_utf_char
suffix:semicolon
DECL|member|vc_tab_stop
r_int
r_int
id|vc_tab_stop
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Tab stops. 160 columns. */
DECL|member|vc_palette
r_int
r_char
id|vc_palette
(braket
l_int|16
op_star
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Colour palette for VGA+ */
DECL|member|vc_translate
r_int
r_int
op_star
id|vc_translate
suffix:semicolon
DECL|member|vc_G0_charset
r_int
r_char
id|vc_G0_charset
suffix:semicolon
DECL|member|vc_G1_charset
r_int
r_char
id|vc_G1_charset
suffix:semicolon
DECL|member|vc_saved_G0
r_int
r_char
id|vc_saved_G0
suffix:semicolon
DECL|member|vc_saved_G1
r_int
r_char
id|vc_saved_G1
suffix:semicolon
multiline_comment|/* additional information is in vt_kern.h */
)brace
suffix:semicolon
DECL|struct|vc
r_struct
id|vc
(brace
DECL|member|d
r_struct
id|vc_data
op_star
id|d
suffix:semicolon
multiline_comment|/* might add  scrmem, vt_struct, kbd  at some time,&n;&t;   to have everything in one place - the disadvantage&n;&t;   would be that vc_cons etc can no longer be static */
)brace
suffix:semicolon
r_extern
r_struct
id|vc
id|vc_cons
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
DECL|macro|screenbuf_size
mdefine_line|#define screenbuf_size&t;(vc_cons[currcons].d-&gt;vc_screenbuf_size)
DECL|macro|origin
mdefine_line|#define origin&t;&t;(vc_cons[currcons].d-&gt;vc_origin)
DECL|macro|scr_end
mdefine_line|#define scr_end&t;(vc_cons[currcons].d-&gt;vc_scr_end)
DECL|macro|pos
mdefine_line|#define pos&t;&t;(vc_cons[currcons].d-&gt;vc_pos)
DECL|macro|top
mdefine_line|#define top&t;&t;(vc_cons[currcons].d-&gt;vc_top)
DECL|macro|bottom
mdefine_line|#define bottom&t;&t;(vc_cons[currcons].d-&gt;vc_bottom)
DECL|macro|x
mdefine_line|#define x&t;&t;(vc_cons[currcons].d-&gt;vc_x)
DECL|macro|y
mdefine_line|#define y&t;&t;(vc_cons[currcons].d-&gt;vc_y)
DECL|macro|vc_state
mdefine_line|#define vc_state&t;(vc_cons[currcons].d-&gt;vc_state)
DECL|macro|npar
mdefine_line|#define npar&t;&t;(vc_cons[currcons].d-&gt;vc_npar)
DECL|macro|par
mdefine_line|#define par&t;&t;(vc_cons[currcons].d-&gt;vc_par)
DECL|macro|ques
mdefine_line|#define ques&t;&t;(vc_cons[currcons].d-&gt;vc_ques)
DECL|macro|attr
mdefine_line|#define attr&t;&t;(vc_cons[currcons].d-&gt;vc_attr)
DECL|macro|saved_x
mdefine_line|#define saved_x&t;(vc_cons[currcons].d-&gt;vc_saved_x)
DECL|macro|saved_y
mdefine_line|#define saved_y&t;(vc_cons[currcons].d-&gt;vc_saved_y)
DECL|macro|translate
mdefine_line|#define translate&t;(vc_cons[currcons].d-&gt;vc_translate)
DECL|macro|G0_charset
mdefine_line|#define G0_charset&t;(vc_cons[currcons].d-&gt;vc_G0_charset)
DECL|macro|G1_charset
mdefine_line|#define G1_charset&t;(vc_cons[currcons].d-&gt;vc_G1_charset)
DECL|macro|saved_G0
mdefine_line|#define saved_G0&t;(vc_cons[currcons].d-&gt;vc_saved_G0)
DECL|macro|saved_G1
mdefine_line|#define saved_G1&t;(vc_cons[currcons].d-&gt;vc_saved_G1)
DECL|macro|utf
mdefine_line|#define utf&t;&t;(vc_cons[currcons].d-&gt;vc_utf)
DECL|macro|utf_count
mdefine_line|#define utf_count&t;(vc_cons[currcons].d-&gt;vc_utf_count)
DECL|macro|utf_char
mdefine_line|#define utf_char&t;(vc_cons[currcons].d-&gt;vc_utf_char)
DECL|macro|video_mem_start
mdefine_line|#define video_mem_start (vc_cons[currcons].d-&gt;vc_video_mem_start)
DECL|macro|video_mem_end
mdefine_line|#define video_mem_end&t;(vc_cons[currcons].d-&gt;vc_video_mem_end)
DECL|macro|video_erase_char
mdefine_line|#define video_erase_char (vc_cons[currcons].d-&gt;vc_video_erase_char)
DECL|macro|disp_ctrl
mdefine_line|#define disp_ctrl&t;(vc_cons[currcons].d-&gt;vc_disp_ctrl)
DECL|macro|toggle_meta
mdefine_line|#define toggle_meta&t;(vc_cons[currcons].d-&gt;vc_toggle_meta)
DECL|macro|decscnm
mdefine_line|#define decscnm&t;(vc_cons[currcons].d-&gt;vc_decscnm)
DECL|macro|decom
mdefine_line|#define decom&t;&t;(vc_cons[currcons].d-&gt;vc_decom)
DECL|macro|decawm
mdefine_line|#define decawm&t;&t;(vc_cons[currcons].d-&gt;vc_decawm)
DECL|macro|deccm
mdefine_line|#define deccm&t;&t;(vc_cons[currcons].d-&gt;vc_deccm)
DECL|macro|decim
mdefine_line|#define decim&t;&t;(vc_cons[currcons].d-&gt;vc_decim)
DECL|macro|deccolm
mdefine_line|#define deccolm&t;(vc_cons[currcons].d-&gt;vc_deccolm)
DECL|macro|need_wrap
mdefine_line|#define need_wrap&t;(vc_cons[currcons].d-&gt;vc_need_wrap)
DECL|macro|has_scrolled
mdefine_line|#define has_scrolled&t;(vc_cons[currcons].d-&gt;vc_has_scrolled)
DECL|macro|kmalloced
mdefine_line|#define kmalloced&t;(vc_cons[currcons].d-&gt;vc_kmalloced)
DECL|macro|report_mouse
mdefine_line|#define report_mouse&t;(vc_cons[currcons].d-&gt;vc_report_mouse)
DECL|macro|color
mdefine_line|#define color&t;&t;(vc_cons[currcons].d-&gt;vc_color)
DECL|macro|s_color
mdefine_line|#define s_color&t;(vc_cons[currcons].d-&gt;vc_s_color)
DECL|macro|def_color
mdefine_line|#define def_color&t;(vc_cons[currcons].d-&gt;vc_def_color)
DECL|macro|foreground
mdefine_line|#define &t;foreground&t;(color &amp; 0x0f)
DECL|macro|background
mdefine_line|#define &t;background&t;(color &amp; 0xf0)
DECL|macro|charset
mdefine_line|#define charset&t;(vc_cons[currcons].d-&gt;vc_charset)
DECL|macro|s_charset
mdefine_line|#define s_charset&t;(vc_cons[currcons].d-&gt;vc_s_charset)
DECL|macro|intensity
mdefine_line|#define&t;intensity&t;(vc_cons[currcons].d-&gt;vc_intensity)
DECL|macro|underline
mdefine_line|#define&t;underline&t;(vc_cons[currcons].d-&gt;vc_underline)
DECL|macro|blink
mdefine_line|#define&t;blink&t;&t;(vc_cons[currcons].d-&gt;vc_blink)
DECL|macro|reverse
mdefine_line|#define&t;reverse&t;&t;(vc_cons[currcons].d-&gt;vc_reverse)
DECL|macro|s_intensity
mdefine_line|#define&t;s_intensity&t;(vc_cons[currcons].d-&gt;vc_s_intensity)
DECL|macro|s_underline
mdefine_line|#define&t;s_underline&t;(vc_cons[currcons].d-&gt;vc_s_underline)
DECL|macro|s_blink
mdefine_line|#define&t;s_blink&t;&t;(vc_cons[currcons].d-&gt;vc_s_blink)
DECL|macro|s_reverse
mdefine_line|#define&t;s_reverse&t;(vc_cons[currcons].d-&gt;vc_s_reverse)
DECL|macro|ulcolor
mdefine_line|#define&t;ulcolor&t;&t;(vc_cons[currcons].d-&gt;vc_ulcolor)
DECL|macro|halfcolor
mdefine_line|#define&t;halfcolor&t;(vc_cons[currcons].d-&gt;vc_halfcolor)
DECL|macro|tab_stop
mdefine_line|#define tab_stop&t;(vc_cons[currcons].d-&gt;vc_tab_stop)
DECL|macro|palette
mdefine_line|#define palette&t;&t;(vc_cons[currcons].d-&gt;vc_palette)
DECL|macro|vcmode
mdefine_line|#define vcmode&t;&t;(vt_cons[currcons]-&gt;vc_mode)
DECL|macro|structsize
mdefine_line|#define structsize&t;(sizeof(struct vc_data) + sizeof(struct vt_struct))
eof
