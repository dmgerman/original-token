multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Port addresses and bit fields for the Media Vision Pro AudioSpectrum second generation sound cards.&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* &t;Feel free to use this header file in any application you create that has support for the Media Vision&t;&t;&t;*/
multiline_comment|/*&t;Pro AudioSpectrum second generation sound cards. Other uses prohibited without prior permission.&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;- cmetz@thor.tjhsst.edu&t;&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Notes:&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;*&t;All of these ports go into the MVD101 multimedia controller chip, which&t;then signals the other chips to do&t;*/
multiline_comment|/* &t;&t;the actual work. Many ports like the FM ones functionally attach directly to the destination chip though &t;*/
multiline_comment|/* &t;&t;they don&squot;t actually have a direct connection.&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* &t;*&t;The PAS2 series cards have an MVD101 multimedia controller chip, the original PAS cards don&squot;t. The original&t;*/
multiline_comment|/* &t;&t;PAS cards are pretty defunct now, so no attempt is made here to support them. &t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;*&t;The PAS2 series cards are all really different at the hardware level, though the MVD101 hides some of the &t;*/
multiline_comment|/*&t;&t;incompatibilities, there still are differences that need to be accounted for.&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;Card&t;&t;CD-ROM interface&t;PCM chip&t;&t;Mixer chip&t;&t;FM chip&t;&t;&t;*/
multiline_comment|/* &t;&t;PAS Plus&t;Sony proprietary&t;(Crystal?) 8-bit DAC&t;National &t;&t;OPL3&t;&t;&t;*/
multiline_comment|/* &t;&t;PAS 16&t;&t;Zilog SCSI&t;&t;MVA416 16-bit Codec&t;MVA508 &t;&t;&t;OPL3&t;&t;&t;*/
multiline_comment|/* &t;&t;CDPC&t;&t;Sony proprietary&t;Sony 16-bit Codec&t;National&t;&t;OPL3&t;&t;&t;*/
multiline_comment|/*&t;&t;Fusion CD 16&t;Sony proprietary&t;MVA416 16-bit Codec&t;MVA508&t;&t;&t;OPL3&t;&t;&t;*/
multiline_comment|/*&t;&t;Fusion CD&t;Sony proprietary&t;(Crystal?) 8-bit DAC&t;National&t;&t;OPL3&t;&t;&t;*/
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|PAS_DEFAULT_BASE
mdefine_line|#define PAS_DEFAULT_BASE&t;&t;0x388
multiline_comment|/*      Symbolic Name&t;&t;&t;Value &t;&t;   R W  Subsystem&t;Description&t;&t;&t;&t;&t;*/
DECL|macro|SPEAKER_CONTROL
mdefine_line|#define SPEAKER_CONTROL&t;&t;&t;0x61&t;&t;/*   W&t;PC speaker &t;Control register &t;&t;&t;&t;*/
DECL|macro|SPEAKER_CONTROL_GHOST
mdefine_line|#define SPEAKER_CONTROL_GHOST&t;&t;0x738B&t;&t;/* R W&t;PC speaker &t;Control ghost register&t;&t;&t;&t;*/
DECL|macro|SPEAKER_TIMER_CONTROL
mdefine_line|#define SPEAKER_TIMER_CONTROL&t;&t;0x43&t;&t;/*   W  PC speaker &t;Timer control register&t;&t;&t;&t;*/
DECL|macro|SPEAKER_TIMER_CONTROL_GHOST
mdefine_line|#define SPEAKER_TIMER_CONTROL_GHOST&t;0x778B&t;&t;/* R W  PC speaker &t;Timer control register ghost&t;&t;&t;*/
DECL|macro|SPEAKER_TIMER_DATA
mdefine_line|#define SPEAKER_TIMER_DATA&t;&t;0x42&t;&t;/*   W  PC speaker &t;Timer data register&t;&t;&t;&t;*/
DECL|macro|SPEAKER_TIMER_DATA_GHOST
mdefine_line|#define SPEAKER_TIMER_DATA_GHOST&t;0x138A&t;&t;/* R W  PC speaker&t;Timer data register ghost&t;&t;&t;*/
DECL|macro|WARM_BOOT
mdefine_line|#define WARM_BOOT&t;&t;&t;0x41&t;&t;/*   W  Control&t;&t;Used to detect system warm boot&t;  &t;&t;*/
DECL|macro|WARM_BOOT_GHOST
mdefine_line|#define WARM_BOOT_GHOST&t;&t;&t;0x7789&t;&t;/* ? W  Control&t;&t;Use to get the card to fake warm boot&t;&t;*/
DECL|macro|MASTER_DECODE
mdefine_line|#define MASTER_DECODE&t;&t;&t;0x9A01&t;&t;/*   W  Control&t;&t;Address &gt;&gt; 2 of card base address&t;&t;*/
DECL|macro|PRESCALE_DIVIDER
mdefine_line|#define PRESCALE_DIVIDER&t;&t;0xBF8A&t;&t;/* R W&t;PCM&t;&t;Ration between Codec clock and master clock&t;*/
DECL|macro|WAIT_STATE
mdefine_line|#define WAIT_STATE&t;&t;&t;0xBF88&t;&t;/* R W&t;Control&t;&t;Four-bit bus wait-state count (~140ns ea.)&t;*/
DECL|macro|BOARD_REV_ID
mdefine_line|#define BOARD_REV_ID&t;&t;&t;0x2789&t;&t;/* R&t;Control&t;&t;Extended Board Revision ID&t;&t;&t;*/
DECL|macro|SYSTEM_CONFIGURATION_1
mdefine_line|#define SYSTEM_CONFIGURATION_1&t;&t;0x8388&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|S_C_1_PCS_ENABLE
mdefine_line|#define S_C_1_PCS_ENABLE&t;0x01&t;&t;/* R W  PC speaker&t;1=enable, 0=disable PC speaker emulation&t;*/
DECL|macro|S_C_1_PCM_CLOCK_SELECT
mdefine_line|#define S_C_1_PCM_CLOCK_SELECT&t;0x02&t;&t;/* R W  PCM&t;&t;1=14.31818Mhz/12, 0=28.224Mhz master clock&t;*/ 
DECL|macro|S_C_1_FM_EMULATE_CLOCK
mdefine_line|#define S_C_1_FM_EMULATE_CLOCK&t;0x04&t;&t;/* R W  FM&t;&t;1=use 28.224Mhz/2, 0=use 14.31818Mhz clock&t;*/
DECL|macro|S_C_1_PCS_STEREO
mdefine_line|#define S_C_1_PCS_STEREO&t;0x10 &t;&t;/* R W  PC speaker&t;1=enable PC speaker stereo effect, 0=disable&t;*/
DECL|macro|S_C_1_PCS_REALSOUND
mdefine_line|#define S_C_1_PCS_REALSOUND&t;0x20&t;&t;/* R W  PC speaker&t;1=enable RealSound enhancement, 0=disable&t;*/
DECL|macro|S_C_1_FORCE_EXT_RESET
mdefine_line|#define S_C_1_FORCE_EXT_RESET&t;0x40&t;&t;/* R W  Control&t;&t;Force external reset&t;&t;&t;&t;*/
DECL|macro|S_C_1_FORCE_INT_RESET
mdefine_line|#define S_C_1_FORCE_INT_RESET&t;0x80&t;&t;/* R W  Control&t;&t;Force internal reset&t;&t;&t;&t;*/
DECL|macro|SYSTEM_CONFIGURATION_2
mdefine_line|#define SYSTEM_CONFIGURATION_2&t;&t;0x8389&t;&t;/* R W  Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|S_C_2_PCM_OVERSAMPLING
mdefine_line|#define S_C_2_PCM_OVERSAMPLING&t;0x03&t;&t;/* R W  PCM&t;&t;00=0x, 01=2x, 10=4x, 11=reserved&t;&t;*/
DECL|macro|S_C_2_PCM_16_BIT
mdefine_line|#define S_C_2_PCM_16_BIT&t;0x04&t;&t;/* R W&t;PCM&t;&t;1=16-bit, 0=8-bit samples&t;&t;&t;*/
DECL|macro|SYSTEM_CONFIGURATION_3
mdefine_line|#define SYSTEM_CONFIGURATION_3&t;&t;0x838A&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|S_C_3_PCM_CLOCK_SELECT
mdefine_line|#define S_C_3_PCM_CLOCK_SELECT&t;0x02&t;&t;/* R W&t;PCM&t;&t;1=use 1.008Mhz clock for PCM, 0=don&squot;t&t;&t;*/
DECL|macro|SYSTEM_CONFIGURATION_4
mdefine_line|#define SYSTEM_CONFIGURATION_4&t;&t;0x838B&t;&t;/* R W  Control&t;&t;CD-ROM interface controls&t;&t;&t;*/
DECL|macro|IO_CONFIGURATION_1
mdefine_line|#define IO_CONFIGURATION_1&t;&t;0xF388&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|I_C_1_BOOT_RESET_ENABLE
mdefine_line|#define I_C_1_BOOT_RESET_ENABLE&t;0x80&t;&t;/* R W  Control&t;&t;1=reset board on warm boot, 0=don&squot;t&t;&t;*/
DECL|macro|IO_CONFIGURATION_2
mdefine_line|#define IO_CONFIGURATION_2&t;&t;0xF389&t;&t;/* R W  Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|I_C_2_PCM_DMA_DISABLED
mdefine_line|#define&t;I_C_2_PCM_DMA_DISABLED&t;0x00&t;&t;/* R W  PCM&t;&t;PCM DMA disabled&t;&t;&t;&t;*/
DECL|macro|IO_CONFIGURATION_3
mdefine_line|#define IO_CONFIGURATION_3&t;&t;0xF38A&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|I_C_3_PCM_IRQ_DISABLED
mdefine_line|#define I_C_3_PCM_IRQ_DISABLED&t;0x00&t;&t;/* R W  PCM&t;&t;PCM IRQ disabled&t;&t;&t;&t;*/
DECL|macro|COMPATIBILITY_ENABLE
mdefine_line|#define COMPATIBILITY_ENABLE&t;&t;0xF788&t;&t;/* R W  Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|C_E_MPU401_ENABLE
mdefine_line|#define C_E_MPU401_ENABLE&t;0x01&t;&t;/* R W&t;MIDI&t;&t;1=enable, 0=disable MPU401 MIDI emulation&t;*/
DECL|macro|C_E_SB_ENABLE
mdefine_line|#define C_E_SB_ENABLE&t;&t;0x02&t;&t;/* R W  PCM&t;&t;1=enable, 0=disable Sound Blaster emulation&t;*/
DECL|macro|C_E_SB_ACTIVE
mdefine_line|#define C_E_SB_ACTIVE&t;&t;0x04&t;&t;/* R    PCM&t;&t;&quot;Sound Blaster Interrupt active&quot;&t;&t;*/
DECL|macro|C_E_MPU401_ACTIVE
mdefine_line|#define C_E_MPU401_ACTIVE&t;0x08&t;&t;/* R&t;MIDI&t;&t;&quot;MPU UART mode active&quot;&t;&t;&t;&t;*/
DECL|macro|C_E_PCM_COMPRESSION
mdefine_line|#define C_E_PCM_COMPRESSION&t;0x10&t;&t;/* R W  PCM&t;&t;1=enable, 0=disabled compression&t;&t;*/
DECL|macro|EMULATION_ADDRESS
mdefine_line|#define EMULATION_ADDRESS&t;&t;0xF789&t;&t;/* R W  Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|E_A_SB_BASE
mdefine_line|#define E_A_SB_BASE&t;&t;0x0f&t;&t;/* R W  PCM&t;&t;bits A4-A7 for SB base port&t;&t;&t;*/
DECL|macro|E_A_MPU401_BASE
mdefine_line|#define E_A_MPU401_BASE&t;&t;0xf0&t;&t;/* R W&t;MIDI&t;&t;bits A4-A7 for MPU401 base port &t;&t;*/
DECL|macro|EMULATION_CONFIGURATION
mdefine_line|#define EMULATION_CONFIGURATION&t;&t;0xFB8A&t;&t;/* R W&t;&t;&t;***** Only valid on newer PAS2 cards (?) *****&t;*/
DECL|macro|E_C_MPU401_IRQ
mdefine_line|#define E_C_MPU401_IRQ&t;&t;0x07&t;&t;/* R W&t;MIDI&t;&t;MPU401 emulation IRQ&t;&t;&t;&t;*/
DECL|macro|E_C_SB_IRQ
mdefine_line|#define E_C_SB_IRQ&t;&t;0x38&t;&t;/* R W  PCM&t;&t;SB emulation IRQ&t;&t;&t;&t;*/
DECL|macro|E_C_SB_DMA
mdefine_line|#define E_C_SB_DMA&t;&t;0xC0&t;&t;/* R W&t;PCM&t;&t;SB emulation DMA&t;&t;&t;&t;*/
DECL|macro|OPERATION_MODE_1
mdefine_line|#define OPERATION_MODE_1&t;&t;0xEF8B&t;&t;/* R&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|O_M_1_CDROM_TYPE
mdefine_line|#define&t;O_M_1_CDROM_TYPE&t;0x03&t;&t;/* R&t;CD-ROM&t;&t;3=SCSI, 2=Sony, 0=no CD-ROM interface&t;&t;*/
DECL|macro|O_M_1_FM_TYPE
mdefine_line|#define O_M_1_FM_TYPE&t;&t;0x04&t;&t;/* R&t;FM&t;&t;1=stereo, 0=mono FM chip&t;&t;&t;*/
DECL|macro|O_M_1_PCM_TYPE
mdefine_line|#define O_M_1_PCM_TYPE &t;&t;0x08&t;&t;/* R&t;PCM&t;&t;1=16-bit Codec, 0=8-bit DAC&t;&t;&t;*/
DECL|macro|OPERATION_MODE_2
mdefine_line|#define OPERATION_MODE_2&t;&t;0xFF8B&t;&t;/* R&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|O_M_2_PCS_ENABLED
mdefine_line|#define O_M_2_PCS_ENABLED&t;0x02&t;&t;/* R&t;PC speaker&t;PC speaker emulation 1=enabled, 0=disabled&t;*/
DECL|macro|O_M_2_BUS_TIMING
mdefine_line|#define O_M_2_BUS_TIMING&t;0x10&t;&t;/* R&t;Control&t;&t;1=AT bus timing, 0=XT bus timing&t;&t;*/
DECL|macro|O_M_2_BOARD_REVISION
mdefine_line|#define O_M_2_BOARD_REVISION&t;0xe0&t;&t;/* R&t;Control&t;&t;Board revision&t;&t;&t;&t;&t;*/
DECL|macro|INTERRUPT_MASK
mdefine_line|#define INTERRUPT_MASK&t;&t;&t;0x0B8B&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|I_M_FM_LEFT_IRQ_ENABLE
mdefine_line|#define I_M_FM_LEFT_IRQ_ENABLE&t;0x01&t;&t;/* R W&t;FM&t;&t;Enable FM left interrupt&t;&t;&t;*/
DECL|macro|I_M_FM_RIGHT_IRQ_ENABLE
mdefine_line|#define I_M_FM_RIGHT_IRQ_ENABLE&t;0x02&t;&t;/* R W&t;FM&t;&t;Enable FM right interrupt&t;&t;&t;*/
DECL|macro|I_M_PCM_RATE_IRQ_ENABLE
mdefine_line|#define I_M_PCM_RATE_IRQ_ENABLE&t;0x04&t;&t;/* R W&t;PCM&t;&t;Enable Sample Rate interrupt&t;&t;&t;*/
DECL|macro|I_M_PCM_BUFFER_IRQ_ENABLE
mdefine_line|#define I_M_PCM_BUFFER_IRQ_ENABLE 0x08&t;&t;/* R W&t;PCM&t;&t;Enable Sample Buffer interrupt&t;&t;&t;*/
DECL|macro|I_M_MIDI_IRQ_ENABLE
mdefine_line|#define I_M_MIDI_IRQ_ENABLE&t;0x10&t;&t;/* R W&t;MIDI&t;&t;Enable MIDI interrupt&t;&t;&t;&t;*/
DECL|macro|I_M_BOARD_REV
mdefine_line|#define I_M_BOARD_REV&t;&t;0xE0&t;&t;/* R&t;Control&t;&t;Board revision&t;&t;&t;&t;&t;*/
DECL|macro|INTERRUPT_STATUS
mdefine_line|#define INTERRUPT_STATUS&t;&t;0x0B89&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|I_S_FM_LEFT_IRQ
mdefine_line|#define I_S_FM_LEFT_IRQ&t;&t;0x01&t;&t;/* R W&t;FM&t;&t;Left FM Interrupt Pending&t;&t;&t;*/
DECL|macro|I_S_FM_RIGHT_IRQ
mdefine_line|#define I_S_FM_RIGHT_IRQ&t;0x02&t;&t;/* R W&t;FM&t;&t;Right FM Interrupt Pending&t;&t;&t;*/
DECL|macro|I_S_PCM_SAMPLE_RATE_IRQ
mdefine_line|#define I_S_PCM_SAMPLE_RATE_IRQ&t;0x04&t;&t;/* R W&t;PCM&t;&t;Sample Rate Interrupt Pending&t;&t;&t;*/
DECL|macro|I_S_PCM_SAMPLE_BUFFER_IRQ
mdefine_line|#define I_S_PCM_SAMPLE_BUFFER_IRQ 0x08&t;&t;/* R W&t;PCM&t;&t;Sample Buffer Interrupt Pending&t;&t;&t;*/
DECL|macro|I_S_MIDI_IRQ
mdefine_line|#define I_S_MIDI_IRQ&t;&t;0x10&t;&t;/* R W&t;MIDI&t;&t;MIDI Interrupt Pending&t;&t;&t;&t;*/
DECL|macro|I_S_PCM_CHANNEL
mdefine_line|#define I_S_PCM_CHANNEL&t;&t;0x20&t;&t;/* R W&t;PCM&t;&t;1=right, 0=left&t;&t;&t;&t;&t;*/
DECL|macro|I_S_RESET_ACTIVE
mdefine_line|#define I_S_RESET_ACTIVE&t;0x40&t;&t;/* R W&t;Control&t;&t;Reset is active (Timed pulse not finished)&t;*/
DECL|macro|I_S_PCM_CLIPPING
mdefine_line|#define I_S_PCM_CLIPPING&t;0x80&t;&t;/* R W&t;PCM&t;&t;Clipping has occurred&t;&t;&t;&t;*/
DECL|macro|FILTER_FREQUENCY
mdefine_line|#define FILTER_FREQUENCY&t;&t;0x0B8A&t;&t;/* R W&t;Control&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|F_F_FILTER_DISABLED
mdefine_line|#define F_F_FILTER_DISABLED&t;0x00&t;&t;/* R W &t;Mixer&t;&t;No filter&t;&t;&t;&t;&t;*/
macro_line|#if 0
r_struct
(brace
multiline_comment|/* R W&t;Mixer&t;&t;Filter translation&t;&t;&t;&t;*/
r_int
r_int
id|freq
suffix:colon
l_int|24
suffix:semicolon
r_int
r_int
id|value
suffix:colon
l_int|8
suffix:semicolon
)brace
id|F_F_FILTER_translate
(braket
)braket
op_assign
(brace
(brace
l_int|73500
comma
l_int|0x01
)brace
comma
multiline_comment|/* 73500Hz - divide by  16 */
(brace
l_int|65333
comma
l_int|0x02
)brace
comma
multiline_comment|/* 65333Hz - divide by  18 */
(brace
l_int|49000
comma
l_int|0x09
)brace
comma
multiline_comment|/* 49000Hz - divide by  24 */
(brace
l_int|36750
comma
l_int|0x11
)brace
comma
multiline_comment|/* 36750Hz - divide by  32 */
(brace
l_int|24500
comma
l_int|0x19
)brace
comma
multiline_comment|/* 24500Hz - divide by  48 */
(brace
l_int|18375
comma
l_int|0x07
)brace
comma
multiline_comment|/* 18375Hz - divide by  64 */
(brace
l_int|12783
comma
l_int|0x0f
)brace
comma
multiline_comment|/* 12783Hz - divide by  92 */
(brace
l_int|12250
comma
l_int|0x04
)brace
comma
multiline_comment|/* 12250Hz - divide by  96 */
(brace
l_int|9188
comma
l_int|0x17
)brace
comma
multiline_comment|/*  9188Hz - divide by 128 */
(brace
l_int|6125
comma
l_int|0x1f
)brace
comma
multiline_comment|/*  6125Hz - divide by 192 */
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|F_F_MIXER_UNMUTE
mdefine_line|#define F_F_MIXER_UNMUTE&t;0x20&t;&t;/* R W&t;Mixer&t;&t;1=disable, 0=enable board mute&t;&t;&t;*/
DECL|macro|F_F_PCM_RATE_COUNTER
mdefine_line|#define F_F_PCM_RATE_COUNTER&t;0x40&t;&t;/* R W&t;PCM&t;&t;1=enable, 0=disable sample rate counter&t;&t;*/
DECL|macro|F_F_PCM_BUFFER_COUNTER
mdefine_line|#define F_F_PCM_BUFFER_COUNTER&t;0x80&t;&t;/* R W &t;PCM&t;&t;1=enable, 0=disable sample buffer counter&t;*/
DECL|macro|PAS_NONE
mdefine_line|#define PAS_NONE&t;0
DECL|macro|PAS_PLUS
mdefine_line|#define PAS_PLUS&t;1
DECL|macro|PAS_CDPC
mdefine_line|#define PAS_CDPC&t;2
DECL|macro|PAS_16
mdefine_line|#define PAS_16&t;&t;3
DECL|macro|PAS_16D
mdefine_line|#define PAS_16D&t;&t;4
macro_line|#ifdef DEFINE_TRANSLATIONS
DECL|variable|I_C_2_PCM_DMA_translate
r_int
r_char
id|I_C_2_PCM_DMA_translate
(braket
)braket
op_assign
multiline_comment|/* R W  PCM&t;&t;PCM DMA channel value translations&t;&t;*/
(brace
l_int|4
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|0
comma
l_int|5
comma
l_int|6
comma
l_int|7
)brace
suffix:semicolon
DECL|variable|I_C_3_PCM_IRQ_translate
r_int
r_char
id|I_C_3_PCM_IRQ_translate
(braket
)braket
op_assign
multiline_comment|/* R W&t;PCM&t;&t;PCM IRQ level value translation&t;&t;&t;*/
(brace
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|0
comma
l_int|10
comma
l_int|11
)brace
suffix:semicolon
DECL|variable|E_C_MPU401_IRQ_translate
r_int
r_char
id|E_C_MPU401_IRQ_translate
(braket
)braket
op_assign
multiline_comment|/* R W&t;MIDI&t;&t;MPU401 emulation IRQ value translation&t;&t;*/
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x01
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
)brace
suffix:semicolon
DECL|variable|E_C_SB_IRQ_translate
r_int
r_char
id|E_C_SB_IRQ_translate
(braket
)braket
op_assign
multiline_comment|/* R W&t;PCM&t;&t;SB emulation IRQ translate&t;&t;&t;*/
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0x10
comma
l_int|0x00
comma
l_int|0x18
comma
l_int|0x00
comma
l_int|0x20
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0x28
comma
l_int|0x30
comma
l_int|0x38
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|E_C_SB_DMA_translate
r_int
r_char
id|E_C_SB_DMA_translate
(braket
)braket
op_assign
multiline_comment|/* R W&t;PCM&t;&t;SB emulation DMA translate&t;&t;&t;*/
(brace
l_int|0x00
comma
l_int|0x40
comma
l_int|0x80
comma
l_int|0xC0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|O_M_1_to_card
r_int
r_char
id|O_M_1_to_card
(braket
)braket
op_assign
multiline_comment|/* R W&t;Control&t;&t;Translate (OM1 &amp; 0x0f) to card type&t;&t;*/
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|2
comma
l_int|3
)brace
suffix:semicolon
macro_line|#else
r_extern
r_int
r_char
id|I_C_2_PCM_DMA_translate
(braket
)braket
suffix:semicolon
multiline_comment|/* R W  PCM&t;&t;PCM DMA channel value translations&t;&t;*/
r_extern
r_int
r_char
id|I_C_3_PCM_IRQ_translate
(braket
)braket
suffix:semicolon
multiline_comment|/* R W&t;PCM&t;&t;PCM IRQ level value translation&t;&t;&t;*/
r_extern
r_int
r_char
id|E_C_MPU401_IRQ_translate
(braket
)braket
suffix:semicolon
multiline_comment|/* R W&t;MIDI&t;&t;MPU401 emulation IRQ value translation&t;&t;*/
r_extern
r_int
r_char
id|E_C_SB_IRQ_translate
(braket
)braket
suffix:semicolon
multiline_comment|/* R W&t;PCM&t;&t;SB emulation IRQ translate&t;&t;&t;*/
r_extern
r_int
r_char
id|E_C_SB_DMA_translate
(braket
)braket
suffix:semicolon
multiline_comment|/* R W&t;PCM&t;&t;SB emulation DMA translate&t;&t;&t;*/
r_extern
r_int
r_char
id|O_M_1_to_card
(braket
)braket
suffix:semicolon
multiline_comment|/* R W&t;Control&t;&t;Translate (OM1 &amp; 0x0f) to card type&t;&t;*/
macro_line|#endif
DECL|macro|PARALLEL_MIXER
mdefine_line|#define PARALLEL_MIXER&t;&t;&t;0x078B&t;&t;/*   W&t;Mixer&t;&t;Documented for MVD101 as FM Mono Right decode?? */
DECL|macro|P_M_MV508_ADDRESS
mdefine_line|#define P_M_MV508_ADDRESS&t;0x80&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Address/mixer select&t;&t;&t;*/
DECL|macro|P_M_MV508_DATA
mdefine_line|#define P_M_MV508_DATA&t;&t;0x00
DECL|macro|P_M_MV508_LEFT
mdefine_line|#define P_M_MV508_LEFT&t;&t;0x20&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Left channel select&t;&t;&t;*/
DECL|macro|P_M_MV508_RIGHT
mdefine_line|#define P_M_MV508_RIGHT&t;&t;0x40&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Right channel select&t;&t;&t;*/
DECL|macro|P_M_MV508_BOTH
mdefine_line|#define P_M_MV508_BOTH&t;&t;0x00&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Both channel select&t;&t;&t;*/
DECL|macro|P_M_MV508_MIXER
mdefine_line|#define P_M_MV508_MIXER&t;&t;0x10&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Select a mixer (rather than a volume) &t;*/
DECL|macro|P_M_MV508_VOLUME
mdefine_line|#define P_M_MV508_VOLUME&t;0x00
DECL|macro|P_M_MV508_INPUTMIX
mdefine_line|#define P_M_MV508_INPUTMIX&t;0x20&t;&t;/*   W  Mixer&t;&t;MVD508&t;Select mixer A&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_OUTPUTMIX
mdefine_line|#define P_M_MV508_OUTPUTMIX&t;0x00&t;&t;/*   W  Mixer&t;&t;MVD508&t;Select mixer B&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_MASTER_A
mdefine_line|#define P_M_MV508_MASTER_A&t;0x01&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Master volume control A (output)&t;*/
DECL|macro|P_M_MV508_MASTER_B
mdefine_line|#define P_M_MV508_MASTER_B&t;0x02&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Master volume control B (DSP input)&t;*/
DECL|macro|P_M_MV508_BASS
mdefine_line|#define P_M_MV508_BASS&t;&t;0x03&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Bass control&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_TREBLE
mdefine_line|#define P_M_MV508_TREBLE&t;0x04&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Treble control&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_MODE
mdefine_line|#define P_M_MV508_MODE&t;&t;0x05&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Master mode control&t;&t;&t;*/
DECL|macro|P_M_MV508_LOUDNESS
mdefine_line|#define P_M_MV508_LOUDNESS&t;0x04&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Mode control - Loudness filter &t;&t;*/
DECL|macro|P_M_MV508_ENHANCE_BITS
mdefine_line|#define P_M_MV508_ENHANCE_BITS&t;0x03
DECL|macro|P_M_MV508_ENHANCE_NONE
mdefine_line|#define P_M_MV508_ENHANCE_NONE&t;0x00&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Mode control - No stereo enhancement&t;*/
DECL|macro|P_M_MV508_ENHANCE_40
mdefine_line|#define P_M_MV508_ENHANCE_40&t;0x01&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Mode control - 40% stereo enhancement&t;*/
DECL|macro|P_M_MV508_ENHANCE_60
mdefine_line|#define P_M_MV508_ENHANCE_60&t;0x02&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Mode control - 60% stereo enhancement&t;*/
DECL|macro|P_M_MV508_ENHANCE_80
mdefine_line|#define P_M_MV508_ENHANCE_80&t;0x03&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Mode control - 80% stereo enhancement&t;*/
DECL|macro|P_M_MV508_FM
mdefine_line|#define P_M_MV508_FM&t;&t;0x00&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 0 - FM&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_IMIXER
mdefine_line|#define P_M_MV508_IMIXER&t;0x01&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 1 - Input mixer (rec monitor)&t;*/
DECL|macro|P_M_MV508_LINE
mdefine_line|#define P_M_MV508_LINE&t;&t;0x02&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 2 - Line in&t;&t;&t;*/
DECL|macro|P_M_MV508_CDROM
mdefine_line|#define P_M_MV508_CDROM&t;&t;0x03&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 3 - CD-ROM&t;&t;&t;*/
DECL|macro|P_M_MV508_MIC
mdefine_line|#define P_M_MV508_MIC&t;&t;0x04&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 4 - Microphone&t;&t;&t;*/
DECL|macro|P_M_MV508_PCM
mdefine_line|#define P_M_MV508_PCM&t;&t;0x05&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 5 - PCM&t;&t;&t;&t;*/
DECL|macro|P_M_MV508_SPEAKER
mdefine_line|#define P_M_MV508_SPEAKER&t;0x06&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 6 - PC Speaker&t;&t;&t;*/
DECL|macro|P_M_MV508_SB
mdefine_line|#define P_M_MV508_SB&t;&t;0x07&t;&t;/*   W&t;Mixer&t;&t;MVD508&t;Channel 7 - SB DSP&t;&t;&t;*/
DECL|macro|SERIAL_MIXER
mdefine_line|#define SERIAL_MIXER&t;&t;&t;0xB88&t;&t;/* R W&t;Control&t;&t;Serial mixer control (used other ways)&t;&t;*/
DECL|macro|S_M_PCM_RESET
mdefine_line|#define S_M_PCM_RESET&t;&t;0x01&t;&t;/* R W&t;PCM&t;&t;Codec/DSP reset&t;&t;&t;&t;&t;*/
DECL|macro|S_M_FM_RESET
mdefine_line|#define S_M_FM_RESET&t;&t;0x02&t;&t;/* R W&t;FM&t;&t;FM chip reset&t;&t;&t;&t;&t;*/
DECL|macro|S_M_SB_RESET
mdefine_line|#define S_M_SB_RESET&t;&t;0x04&t;&t;/* R W&t;PCM&t;&t;SB emulation chip reset&t;&t;&t;&t;*/
DECL|macro|S_M_MIXER_RESET
mdefine_line|#define S_M_MIXER_RESET&t;&t;0x10&t;&t;/* R W&t;Mixer&t;&t;Mixer chip reset&t;&t;&t;&t;*/
DECL|macro|S_M_INTEGRATOR_ENABLE
mdefine_line|#define S_M_INTEGRATOR_ENABLE&t;0x40&t;&t;/* R W&t;Speaker&t;&t;Enable PC speaker integrator (FORCE RealSound)&t;*/
DECL|macro|S_M_OPL3_DUAL_MONO
mdefine_line|#define S_M_OPL3_DUAL_MONO&t;0x80&t;&t;/* R W  FM&t;&t;Set the OPL-3 to dual mono mode&t;&t;&t;*/
DECL|macro|PCM_CONTROL
mdefine_line|#define PCM_CONTROL&t;&t;&t;0xF8A&t;&t;/* R W&t;PCM&t;&t;PCM Control Register&t;&t;&t;&t;*/
DECL|macro|P_C_MIXER_CROSS_FIELD
mdefine_line|#define P_C_MIXER_CROSS_FIELD&t;0x0f
DECL|macro|P_C_MIXER_CROSS_R_TO_R
mdefine_line|#define P_C_MIXER_CROSS_R_TO_R&t;0x01&t;&t;/* R W&t;Mixer&t;&t;Connect Right to Right&t;&t;&t;&t;*/
DECL|macro|P_C_MIXER_CROSS_L_TO_R
mdefine_line|#define P_C_MIXER_CROSS_L_TO_R&t;0x02&t;&t;/* R W&t;Mixer&t;&t;Connect Left  to Right&t;&t;&t;&t;*/
DECL|macro|P_C_MIXER_CROSS_R_TO_L
mdefine_line|#define P_C_MIXER_CROSS_R_TO_L&t;0x04&t;&t;/* R W&t;Mixer&t;&t;Connect Right to Left&t;&t;&t;&t;*/
DECL|macro|P_C_MIXER_CROSS_L_TO_L
mdefine_line|#define P_C_MIXER_CROSS_L_TO_L&t;0x08&t;&t;/* R W&t;Mixer&t;&t;Connect Left  to Left&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_DAC_MODE
mdefine_line|#define P_C_PCM_DAC_MODE&t;0x10&t;&t;/* R W&t;PCM&t;&t;Playback (DAC) mode&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_ADC_MODE
mdefine_line|#define P_C_PCM_ADC_MODE&t;0x00&t;&t;/* R W&t;PCM&t;&t;Record (ADC) mode&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_MONO
mdefine_line|#define P_C_PCM_MONO&t;&t;0x20&t;&t;/* R W&t;PCM&t;&t;Mono mode&t;&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_STEREO
mdefine_line|#define P_C_PCM_STEREO&t;&t;0x00&t;&t;/* R W&t;PCM&t;&t;Stereo mode&t;&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_ENABLE
mdefine_line|#define P_C_PCM_ENABLE&t;&t;0x40&t;&t;/* R W&t;PCM&t;&t;Enable PCM engine&t;&t;&t;&t;*/
DECL|macro|P_C_PCM_DMA_ENABLE
mdefine_line|#define P_C_PCM_DMA_ENABLE&t;0x80&t;&t;/* R W&t;PCM&t;&t;Enable DRQ&t;&t;&t;&t;&t;*/
DECL|macro|SAMPLE_COUNTER_CONTROL
mdefine_line|#define SAMPLE_COUNTER_CONTROL&t;&t;0x138B&t;&t;/* R W&t;PCM&t;&t;Sample counter control register&t;&t;&t;*/
DECL|macro|S_C_C_SQUARE_WAVE
mdefine_line|#define S_C_C_SQUARE_WAVE&t;0x04&t;&t;/* R W&t;PCM&t;&t;Square wave generator (use for sample rate)&t;*/
DECL|macro|S_C_C_RATE
mdefine_line|#define S_C_C_RATE&t;&t;0x06&t;&t;/* R W&t;PCM&t;&t;Rate generator (use for sample buffer count)&t;*/
DECL|macro|S_C_C_LSB_THEN_MSB
mdefine_line|#define S_C_C_LSB_THEN_MSB&t;0x30&t;&t;/* R W&t;PCM&t;&t;Change all 16 bits, LSB first, then MSB&t;&t;*/
multiline_comment|/* MVD101 and SDK documentations have S_C_C_SAMPLE_RATE and S_C_C_SAMPLE_BUFFER transposed. Only one works :-) */
DECL|macro|S_C_C_SAMPLE_RATE
mdefine_line|#define S_C_C_SAMPLE_RATE&t;0x00&t;&t;/* R W&t;PCM&t;&t;Select sample rate timer&t;&t;&t;*/
DECL|macro|S_C_C_SAMPLE_BUFFER
mdefine_line|#define S_C_C_SAMPLE_BUFFER&t;0x40&t;&t;/* R W&t;PCM&t;&t;Select sample buffer counter&t;&t;&t;*/
DECL|macro|S_C_C_PC_SPEAKER
mdefine_line|#define S_C_C_PC_SPEAKER&t;0x80&t;&t;/* R W&t;PCM&t;&t;Select PC speaker counter&t;&t;&t;*/
DECL|macro|SAMPLE_RATE_TIMER
mdefine_line|#define SAMPLE_RATE_TIMER&t;&t;0x1388&t;&t;/*   W&t;PCM&t;&t;Sample rate timer register (PCM wait interval)&t;*/
DECL|macro|SAMPLE_BUFFER_COUNTER
mdefine_line|#define SAMPLE_BUFFER_COUNTER&t;&t;0x1389&t;&t;/* R W&t;PCM&t;&t;Sample buffer counter (DMA buffer size)&t;&t;*/
DECL|macro|MIDI_CONTROL
mdefine_line|#define MIDI_CONTROL&t;&t;&t;0x178b&t;&t;/* R W  MIDI&t;&t;Midi control register&t;&t;&t;&t;*/
DECL|macro|M_C_ENA_TSTAMP_IRQ
mdefine_line|#define M_C_ENA_TSTAMP_IRQ&t;0x01&t;&t;/* R W&t;MIDI&t;&t;Enable Time Stamp Interrupts&t;&t;&t;*/
DECL|macro|M_C_ENA_TME_COMP_IRQ
mdefine_line|#define M_C_ENA_TME_COMP_IRQ&t;0x02&t;&t;/* R W  MIDI&t;&t;Enable time compare interrupts&t;&t;&t;*/
DECL|macro|M_C_ENA_INPUT_IRQ
mdefine_line|#define M_C_ENA_INPUT_IRQ&t;0x04&t;&t;/* R W  MIDI&t;&t;Enable input FIFO interrupts&t;&t;&t;*/
DECL|macro|M_C_ENA_OUTPUT_IRQ
mdefine_line|#define M_C_ENA_OUTPUT_IRQ&t;0x08&t;&t;/* R W  MIDI&t;&t;Enable output FIFO interrupts&t;&t;&t;*/
DECL|macro|M_C_ENA_OUTPUT_HALF_IRQ
mdefine_line|#define M_C_ENA_OUTPUT_HALF_IRQ&t;0x10&t;&t;/* R W  MIDI&t;&t;Enable output FIFO half full interrupts&t;&t;*/
DECL|macro|M_C_RESET_INPUT_FIFO
mdefine_line|#define M_C_RESET_INPUT_FIFO&t;0x20&t;&t;/* R W  MIDI&t;&t;Reset input FIFO pointer&t;&t;&t;*/
DECL|macro|M_C_RESET_OUTPUT_FIFO
mdefine_line|#define M_C_RESET_OUTPUT_FIFO&t;0x40&t;&t;/* R W  MIDI&t;&t;Reset output FIFO pointer&t;&t;&t;*/
DECL|macro|M_C_ENA_THRU_MODE
mdefine_line|#define M_C_ENA_THRU_MODE&t;0x80&t;&t;/* R W  MIDI&t;&t;Echo input to output (THRU)&t;&t;&t;*/
DECL|macro|MIDI_STATUS
mdefine_line|#define MIDI_STATUS&t;&t;&t;0x1B88&t;&t;/* R W  MIDI&t;&t;Midi (interrupt) status register&t;&t;*/
DECL|macro|M_S_TIMESTAMP
mdefine_line|#define M_S_TIMESTAMP&t;&t;0x01&t;&t;/* R W  MIDI&t;&t;Midi time stamp interrupt occurred&t;&t;*/
DECL|macro|M_S_COMPARE
mdefine_line|#define M_S_COMPARE&t;&t;0x02&t;&t;/* R W  MIDI&t;&t;Midi compare time interrupt occurred&t;&t;*/
DECL|macro|M_S_INPUT_AVAIL
mdefine_line|#define M_S_INPUT_AVAIL&t;&t;0x04&t;&t;/* R W  MIDI&t;&t;Midi input data available interrupt occurred&t;*/
DECL|macro|M_S_OUTPUT_EMPTY
mdefine_line|#define M_S_OUTPUT_EMPTY&t;0x08&t;&t;/* R W  MIDI&t;&t;Midi output FIFO empty interrupt occurred&t;*/
DECL|macro|M_S_OUTPUT_HALF_EMPTY
mdefine_line|#define M_S_OUTPUT_HALF_EMPTY&t;0x10&t;&t;/* R W  MIDI&t;&t;Midi output FIFO half empty interrupt occurred&t;*/
DECL|macro|M_S_INPUT_OVERRUN
mdefine_line|#define M_S_INPUT_OVERRUN&t;0x20&t;&t;/* R W  MIDI&t;&t;Midi input overrun error occurred&t;&t;*/
DECL|macro|M_S_OUTPUT_OVERRUN
mdefine_line|#define M_S_OUTPUT_OVERRUN&t;0x40&t;&t;/* R W  MIDI &t;&t;Midi output overrun error occurred&t;&t;*/
DECL|macro|M_S_FRAMING_ERROR
mdefine_line|#define M_S_FRAMING_ERROR&t;0x80&t;&t;/* R W  MIDI&t;&t;Midi input framing error occurred&t;&t;*/
DECL|macro|MIDI_FIFO_STATUS
mdefine_line|#define MIDI_FIFO_STATUS&t;&t;0x1B89&t;&t;/* R W  MIDI&t;&t;Midi fifo status&t;&t;&t;&t;*/
DECL|macro|MIDI_DATA
mdefine_line|#define MIDI_DATA&t;&t;&t;0x178A&t;&t;/* R W  MIDI&t;&t;Midi data register&t;&t;&t;&t;*/
DECL|macro|MIDI_INPUT_AVAILABLE
mdefine_line|#define MIDI_INPUT_AVAILABLE&t;&t;0x0f&t;&t;/* RW   MIDI */ 
eof
