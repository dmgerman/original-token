multiline_comment|/*&n; *&t;DMA buffer calls&n; */
r_int
id|DMAbuf_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
suffix:semicolon
r_int
id|DMAbuf_release
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
suffix:semicolon
r_int
id|DMAbuf_read
(paren
r_int
id|dev
comma
id|snd_rw_buf
op_star
id|user_buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|DMAbuf_getwrbuffer
c_func
(paren
r_int
id|dev
comma
r_char
op_star
op_star
id|buf
comma
r_int
op_star
id|size
)paren
suffix:semicolon
r_int
id|DMAbuf_getrdbuffer
c_func
(paren
r_int
id|dev
comma
r_char
op_star
op_star
id|buf
comma
r_int
op_star
id|len
)paren
suffix:semicolon
r_int
id|DMAbuf_rmchars
c_func
(paren
r_int
id|dev
comma
r_int
id|buff_no
comma
r_int
id|c
)paren
suffix:semicolon
r_int
id|DMAbuf_start_output
c_func
(paren
r_int
id|dev
comma
r_int
id|buff_no
comma
r_int
id|l
)paren
suffix:semicolon
r_int
id|DMAbuf_ioctl
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
id|local
)paren
suffix:semicolon
r_int
id|DMAbuf_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_int
id|DMAbuf_start_dma
(paren
r_int
id|dev
comma
r_int
r_int
id|physaddr
comma
r_int
id|count
comma
r_int
id|dma_mode
)paren
suffix:semicolon
r_int
id|DMAbuf_open_dma
(paren
r_int
id|chan
)paren
suffix:semicolon
r_void
id|DMAbuf_close_dma
(paren
r_int
id|chan
)paren
suffix:semicolon
r_void
id|DMAbuf_reset_dma
(paren
r_int
id|chan
)paren
suffix:semicolon
r_void
id|DMAbuf_inputintr
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_void
id|DMAbuf_outputintr
c_func
(paren
r_int
id|dev
comma
r_int
id|underflow_flag
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;System calls for /dev/dsp and /dev/audio&n; */
r_int
id|audio_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|audio_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|audio_open
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_void
id|audio_release
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_int
id|audio_ioctl
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
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
suffix:semicolon
r_int
id|audio_lseek
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|off_t
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
r_int
id|audio_init
(paren
r_int
id|mem_start
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;System calls for the /dev/sequencer&n; */
r_int
id|sequencer_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|sequencer_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|sequencer_open
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_void
id|sequencer_release
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_int
id|sequencer_ioctl
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
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
suffix:semicolon
r_int
id|sequencer_lseek
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|off_t
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
r_int
id|sequencer_init
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_void
id|sequencer_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|note_to_freq
c_func
(paren
r_int
id|note_num
)paren
suffix:semicolon
r_int
r_int
id|compute_finetune
c_func
(paren
r_int
r_int
id|base_freq
comma
r_int
id|bend
comma
r_int
id|range
)paren
suffix:semicolon
macro_line|#ifdef ALLOW_SELECT
r_int
id|sequencer_select
c_func
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_int
id|sel_type
comma
id|select_table
op_star
id|wait
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;System calls for the /dev/midi&n; */
r_int
id|MIDIbuf_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|MIDIbuf_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|MIDIbuf_open
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_void
id|MIDIbuf_release
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_int
id|MIDIbuf_ioctl
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
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
suffix:semicolon
r_int
id|MIDIbuf_lseek
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|off_t
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
r_void
id|MIDIbuf_bytes_received
c_func
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|MIDIbuf_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;System calls for the generic midi interface.&n; *&n; */
r_int
id|CMIDI_init
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_int
id|CMIDI_open
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
r_int
id|CMIDI_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|CMIDI_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|CMIDI_close
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
suffix:semicolon
multiline_comment|/*&n; *&n; *&t;Misc calls from various sources&n; */
multiline_comment|/* &t;From pro_midi.c &t;*/
r_int
id|pro_midi_attach
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_int
id|pro_midi_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
suffix:semicolon
r_void
id|pro_midi_close
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_int
id|pro_midi_write
c_func
(paren
r_int
id|dev
comma
id|snd_rw_buf
op_star
id|uio
)paren
suffix:semicolon
r_int
id|pro_midi_read
c_func
(paren
r_int
id|dev
comma
id|snd_rw_buf
op_star
id|uio
)paren
suffix:semicolon
multiline_comment|/*&t;From soundcard.c&t;*/
r_int
id|soundcard_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_void
id|tenmicrosec
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|request_sound_timer
(paren
r_int
id|count
)paren
suffix:semicolon
r_void
id|sound_stop_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_ioctl_return
c_func
(paren
r_int
op_star
id|addr
comma
r_int
id|value
)paren
suffix:semicolon
r_int
id|snd_set_irq_handler
(paren
r_int
id|interrupt_level
comma
r_void
(paren
op_star
id|hndlr
)paren
(paren
r_int
)paren
)paren
suffix:semicolon
r_void
id|snd_release_irq
c_func
(paren
r_int
id|vect
)paren
suffix:semicolon
multiline_comment|/*&t;From sb_dsp.c&t;*/
r_int
id|sb_dsp_detect
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|sb_dsp_init
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_void
id|sb_dsp_disable_midi
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|sb_get_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sb_free_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|sb_dsp_command
(paren
r_int
r_char
id|val
)paren
suffix:semicolon
r_int
id|sb_reset_dsp
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&t;From sb16_dsp.c&t;*/
r_void
id|sb16_dsp_interrupt
(paren
r_int
id|unused
)paren
suffix:semicolon
r_int
id|sb16_dsp_init
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|sb16_dsp_detect
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
multiline_comment|/*&t;From sb_midi.c&t;*/
r_void
id|sb_midi_init
c_func
(paren
r_int
id|model
)paren
suffix:semicolon
multiline_comment|/*&t;From sb_mixer.c&t;*/
r_void
id|sb_setmixer
(paren
r_int
r_char
id|port
comma
r_int
r_char
id|value
)paren
suffix:semicolon
r_int
id|sb_getmixer
(paren
r_int
r_char
id|port
)paren
suffix:semicolon
r_void
id|sb_mixer_set_stereo
c_func
(paren
r_int
id|mode
)paren
suffix:semicolon
r_void
id|sb_mixer_init
c_func
(paren
r_int
id|major_model
)paren
suffix:semicolon
multiline_comment|/*&t;From opl3.c&t;*/
r_int
id|opl3_detect
(paren
r_int
id|ioaddr
)paren
suffix:semicolon
r_int
id|opl3_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
multiline_comment|/*&t;From sb_card.c&t;*/
r_int
id|attach_sb_card
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|probe_sb
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
multiline_comment|/*&t;From adlib_card.c&t;*/
r_int
id|attach_adlib_card
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|probe_adlib
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
multiline_comment|/*&t;From pas_card.c&t;*/
r_int
id|attach_pas_card
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|probe_pas
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|pas_set_intr
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
r_int
id|pas_remove_intr
c_func
(paren
r_int
id|mask
)paren
suffix:semicolon
r_int
r_char
id|pas_read
c_func
(paren
r_int
id|ioaddr
)paren
suffix:semicolon
r_void
id|pas_write
c_func
(paren
r_int
r_char
id|data
comma
r_int
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/*&t;From pas_audio.c */
r_void
id|pas_pcm_interrupt
c_func
(paren
r_int
r_char
id|status
comma
r_int
id|cause
)paren
suffix:semicolon
r_int
id|pas_pcm_init
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
multiline_comment|/*&t;From pas_mixer.c */
r_int
id|pas_init_mixer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&t;From pas_midi.c */
r_int
id|pas_midi_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_void
id|pas_midi_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&t;From gus_card.c */
r_int
id|attach_gus_card
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|probe_gus
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|gus_set_midi_irq
c_func
(paren
r_int
id|num
)paren
suffix:semicolon
r_void
id|gusintr
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&t;From gus_wave.c */
r_int
id|gus_wave_detect
c_func
(paren
r_int
id|baseaddr
)paren
suffix:semicolon
r_int
id|gus_wave_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|irq
comma
r_int
id|dma
)paren
suffix:semicolon
r_void
id|gus_voice_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_char
id|gus_read8
(paren
r_int
id|reg
)paren
suffix:semicolon
r_void
id|gus_write8
c_func
(paren
r_int
id|reg
comma
r_int
r_char
id|data
)paren
suffix:semicolon
r_void
id|guswave_dma_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|gus_delay
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&t;From gus_midi.c */
r_int
id|gus_midi_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
r_void
id|gus_midi_interrupt
c_func
(paren
r_int
id|dummy
)paren
suffix:semicolon
multiline_comment|/*&t;From mpu401.c */
r_int
id|attach_mpu401
c_func
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
r_int
id|probe_mpu401
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
suffix:semicolon
multiline_comment|/*&t;From opl3.c */
r_void
id|enable_opl3_mode
c_func
(paren
r_int
id|left
comma
r_int
id|right
comma
r_int
id|both
)paren
suffix:semicolon
multiline_comment|/*&t;From patmgr.c */
r_int
id|pmgr_open
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_void
id|pmgr_release
c_func
(paren
r_int
id|dev
)paren
suffix:semicolon
r_int
id|pmgr_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|pmgr_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|pmgr_access
c_func
(paren
r_int
id|dev
comma
r_struct
id|patmgr_info
op_star
id|rec
)paren
suffix:semicolon
r_int
id|pmgr_inform
c_func
(paren
r_int
id|dev
comma
r_int
id|event
comma
r_int
r_int
id|parm1
comma
r_int
r_int
id|parm2
comma
r_int
r_int
id|parm3
comma
r_int
r_int
id|parm4
)paren
suffix:semicolon
eof