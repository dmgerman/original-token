multiline_comment|/*&n;&n;This file contains just a stub version of the Sound Driver.&n;&n;The real version is available at tsx-11.mit.edu&n;(pub/linux/ALPHA/sound/snd-driv-0.x.tar.Z)&n;&n;Hannu Savolainen&n;hsavolai@cs.helsinki.fi&n;*/
DECL|function|soundcard_init
r_int
id|soundcard_init
c_func
(paren
r_int
id|mem_start
)paren
(brace
r_return
id|mem_start
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SOUND
macro_line|#error The Sound Driver not installed.
macro_line|#endif
eof
