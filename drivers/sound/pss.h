multiline_comment|/******************************************************************************&n;&n;&t;def.h&n;&n;&t;Version 1.3&t;11/2/93&n;&n;&t;Copyright (c) 1993 Analog Devices Inc. All rights reserved&n;&n;******************************************************************************/
multiline_comment|/* Port offsets from base port for Sound Blaster DSP */
DECL|macro|DSP_PORT_CMSD0
mdefine_line|#define DSP_PORT_CMSD0      0x00  /* C/MS music voice 1-6 data port, write only */
DECL|macro|DSP_PORT_CMSR0
mdefine_line|#define DSP_PORT_CMSR0      0x01  /* C/MS music voice 1-6 register port, write only */
DECL|macro|DSP_PORT_CMSD1
mdefine_line|#define DSP_PORT_CMSD1      0x02  /* C/MS music voice 7-12 data port, write only */
DECL|macro|DSP_PORT_CMSR1
mdefine_line|#define DSP_PORT_CMSR1      0x03  /* C/MS music voice 7-12 register port, write only */
DECL|macro|DSP_PORT_STATUS
mdefine_line|#define DSP_PORT_STATUS     0x04  /* DSP Status bits, read only */
DECL|macro|DSP_PORT_CONTROL
mdefine_line|#define DSP_PORT_CONTROL    0x04  /* DSP Control bits, write only */
DECL|macro|DSP_PORT_DATA_LSB
mdefine_line|#define DSP_PORT_DATA_LSB   0x05  /* Read or write LSB of 16 bit data */
DECL|macro|DSP_PORT_RESET
mdefine_line|#define DSP_PORT_RESET      0x06  /* DSP Reset, write only */
DECL|macro|DSP_PORT_07h
mdefine_line|#define DSP_PORT_07h        0x07  /* reserved port */
DECL|macro|DSP_PORT_FMD0
mdefine_line|#define DSP_PORT_FMD0       0x08  /* FM music data/status port, read/write  */
DECL|macro|DSP_PORT_FMR0
mdefine_line|#define DSP_PORT_FMR0       0x09  /* FM music data/status port, write only */
DECL|macro|DSP_PORT_RDDATA
mdefine_line|#define DSP_PORT_RDDATA     0x0A  /* DSP Read data, read only reading signals DSP */
DECL|macro|DSP_PORT_0Bh
mdefine_line|#define DSP_PORT_0Bh        0x0B  /* reserved port */
DECL|macro|DSP_PORT_WRDATA
mdefine_line|#define DSP_PORT_WRDATA     0x0C  /* DSP Write data or command, write */
DECL|macro|DSP_PORT_WRBUSY
mdefine_line|#define DSP_PORT_WRBUSY     0x0C  /* DSP Write buffer status (bit 7), read */
DECL|macro|DSP_PORT_0Dh
mdefine_line|#define DSP_PORT_0Dh        0x0D  /* reserved port */
DECL|macro|DSP_PORT_DATAAVAIL
mdefine_line|#define DSP_PORT_DATAAVAIL  0x0E  /* DSP Data available status (bit 7), read only */
DECL|macro|DSP_PORT_INTERFACE
mdefine_line|#define DSP_PORT_INTERFACE  0x0E  /* Sets DMA Channel and Interrupt, write only */
DECL|macro|DSP_PORT_0Fh
mdefine_line|#define DSP_PORT_0Fh        0x0F  /* reserved port (used on Pro cards) */
DECL|macro|ADDR_MASK
mdefine_line|#define ADDR_MASK   0x003f
DECL|macro|INT_MASK
mdefine_line|#define INT_MASK    0xffc7
DECL|macro|INT_3_BITS
mdefine_line|#define INT_3_BITS  0x0008
DECL|macro|INT_5_BITS
mdefine_line|#define INT_5_BITS  0x0010
DECL|macro|INT_7_BITS
mdefine_line|#define INT_7_BITS  0x0018
DECL|macro|INT_9_BITS
mdefine_line|#define INT_9_BITS  0x0020
DECL|macro|INT_10_BITS
mdefine_line|#define INT_10_BITS 0x0028
DECL|macro|INT_11_BITS
mdefine_line|#define INT_11_BITS 0x0030
DECL|macro|INT_12_BITS
mdefine_line|#define INT_12_BITS 0x0038
DECL|macro|GAME_BIT
mdefine_line|#define GAME_BIT      0x0400
DECL|macro|GAME_BIT_MASK
mdefine_line|#define GAME_BIT_MASK 0xfbff
DECL|macro|INT_TEST_BIT
mdefine_line|#define INT_TEST_BIT 0x0200
DECL|macro|INT_TEST_PASS
mdefine_line|#define INT_TEST_PASS 0x0100
DECL|macro|INT_TEST_BIT_MASK
mdefine_line|#define INT_TEST_BIT_MASK 0xFDFF
DECL|macro|DMA_MASK
mdefine_line|#define DMA_MASK    0xfff8
DECL|macro|DMA_0_BITS
mdefine_line|#define DMA_0_BITS  0x0001
DECL|macro|DMA_1_BITS
mdefine_line|#define DMA_1_BITS  0x0002
DECL|macro|DMA_3_BITS
mdefine_line|#define DMA_3_BITS  0x0003
DECL|macro|DMA_5_BITS
mdefine_line|#define DMA_5_BITS  0x0004
DECL|macro|DMA_6_BITS
mdefine_line|#define DMA_6_BITS  0x0005
DECL|macro|DMA_7_BITS
mdefine_line|#define DMA_7_BITS  0x0006
DECL|macro|DMA_TEST_BIT
mdefine_line|#define DMA_TEST_BIT  0x0080
DECL|macro|DMA_TEST_PASS
mdefine_line|#define DMA_TEST_PASS 0x0040
DECL|macro|DMA_TEST_BIT_MASK
mdefine_line|#define DMA_TEST_BIT_MASK 0xFF7F
multiline_comment|/* Echo DSP Flags */
DECL|macro|DSP_FLAG3
mdefine_line|#define DSP_FLAG3     0x10
DECL|macro|DSP_FLAG2
mdefine_line|#define DSP_FLAG2     0x08
DECL|macro|DSP_FLAG1
mdefine_line|#define DSP_FLAG1     0x80
DECL|macro|DSP_FLAG0
mdefine_line|#define DSP_FLAG0     0x40
DECL|macro|PSS_CONFIG
mdefine_line|#define PSS_CONFIG    0x10
DECL|macro|PSS_WSS_CONFIG
mdefine_line|#define PSS_WSS_CONFIG    0x12
DECL|macro|SB_CONFIG
mdefine_line|#define SB_CONFIG     0x14
DECL|macro|MIDI_CONFIG
mdefine_line|#define MIDI_CONFIG   0x18
DECL|macro|CD_CONFIG
mdefine_line|#define CD_CONFIG     0x16
DECL|macro|UART_CONFIG
mdefine_line|#define UART_CONFIG   0x1a
DECL|macro|PSS_DATA
mdefine_line|#define PSS_DATA      0x00
DECL|macro|PSS_STATUS
mdefine_line|#define PSS_STATUS    0x02
DECL|macro|PSS_CONTROL
mdefine_line|#define PSS_CONTROL   0x02
DECL|macro|PSS_ID_VERS
mdefine_line|#define PSS_ID_VERS   0x04
DECL|macro|PSS_FLAG3
mdefine_line|#define PSS_FLAG3     0x0800
DECL|macro|PSS_FLAG2
mdefine_line|#define PSS_FLAG2     0x0400
DECL|macro|PSS_FLAG1
mdefine_line|#define PSS_FLAG1     0x1000
DECL|macro|PSS_FLAG0
mdefine_line|#define PSS_FLAG0     0x0800
multiline_comment|/*_____ WSS defines */
DECL|macro|WSS_BASE_ADDRESS
mdefine_line|#define WSS_BASE_ADDRESS 0x530
DECL|macro|WSS_CONFIG
mdefine_line|#define WSS_CONFIG       0x0
DECL|macro|WSS_VERSION
mdefine_line|#define WSS_VERSION      0x03
DECL|macro|WSS_SP0
mdefine_line|#define WSS_SP0          0x04
DECL|macro|WSS_SP1
mdefine_line|#define WSS_SP1          0x05
DECL|macro|WSS_SP2
mdefine_line|#define WSS_SP2          0x06
DECL|macro|WSS_SP3
mdefine_line|#define WSS_SP3          0x07
multiline_comment|/*_____ SoundPort register addresses */
DECL|macro|SP_LIN_SOURCE_CTRL
mdefine_line|#define SP_LIN_SOURCE_CTRL   0x00
DECL|macro|SP_RIN_SOURCE_CTRL
mdefine_line|#define SP_RIN_SOURCE_CTRL   0x01
DECL|macro|SP_LIN_GAIN_CTRL
mdefine_line|#define SP_LIN_GAIN_CTRL   0x10
DECL|macro|SP_RIN_GAIN_CTRL
mdefine_line|#define SP_RIN_GAIN_CTRL   0x11
DECL|macro|SP_LAUX1_CTRL
mdefine_line|#define SP_LAUX1_CTRL      0x02
DECL|macro|SP_RAUX1_CTRL
mdefine_line|#define SP_RAUX1_CTRL      0x03
DECL|macro|SP_LAUX2_CTRL
mdefine_line|#define SP_LAUX2_CTRL      0x04
DECL|macro|SP_RAUX2_CTRL
mdefine_line|#define SP_RAUX2_CTRL      0x05
DECL|macro|SP_LOUT_CTRL
mdefine_line|#define SP_LOUT_CTRL       0x06
DECL|macro|SP_ROUT_CTRL
mdefine_line|#define SP_ROUT_CTRL       0x07
DECL|macro|SP_CLK_FORMAT
mdefine_line|#define SP_CLK_FORMAT      0x48
DECL|macro|SP_INT_CONF
mdefine_line|#define SP_INT_CONF        0x09
DECL|macro|SP_INT_CONF_MCE
mdefine_line|#define SP_INT_CONF_MCE    0x49
DECL|macro|SP_PIN_CTRL
mdefine_line|#define SP_PIN_CTRL        0x0a
DECL|macro|SP_TEST_INIT
mdefine_line|#define SP_TEST_INIT       0x0b
DECL|macro|SP_MISC_CTRL
mdefine_line|#define SP_MISC_CTRL       0x0c
DECL|macro|SP_MIX_CTRL
mdefine_line|#define SP_MIX_CTRL        0x0d
DECL|macro|SP_DMA_UCNT
mdefine_line|#define SP_DMA_UCNT        0x0e
DECL|macro|SP_DMA_LCNT
mdefine_line|#define SP_DMA_LCNT        0x0f
multiline_comment|/*_____ Gain constants  */
DECL|macro|GAIN_0
mdefine_line|#define GAIN_0      0x00
DECL|macro|GAIN_1_5
mdefine_line|#define GAIN_1_5    0x01
DECL|macro|GAIN_3
mdefine_line|#define GAIN_3      0x02
DECL|macro|GAIN_4_5
mdefine_line|#define GAIN_4_5    0x03
DECL|macro|GAIN_6
mdefine_line|#define GAIN_6      0x04
DECL|macro|GAIN_7_5
mdefine_line|#define GAIN_7_5    0x05
DECL|macro|GAIN_9
mdefine_line|#define GAIN_9      0x06
DECL|macro|GAIN_10_5
mdefine_line|#define GAIN_10_5   0x07
DECL|macro|GAIN_12
mdefine_line|#define GAIN_12     0x08
DECL|macro|GAIN_13_5
mdefine_line|#define GAIN_13_5   0x09
DECL|macro|GAIN_15
mdefine_line|#define GAIN_15     0x0a
DECL|macro|GAIN_16_5
mdefine_line|#define GAIN_16_5   0x0b
DECL|macro|GAIN_18
mdefine_line|#define GAIN_18     0x0c
DECL|macro|GAIN_19_5
mdefine_line|#define GAIN_19_5   0x0d
DECL|macro|GAIN_21
mdefine_line|#define GAIN_21     0x0e
DECL|macro|GAIN_22_5
mdefine_line|#define GAIN_22_5   0x0f
DECL|macro|MUTE
mdefine_line|#define MUTE       0XFFFF
multiline_comment|/*_____ Attenuation constants  */
DECL|macro|ATTEN_0
mdefine_line|#define ATTEN_0      0x00
DECL|macro|ATTEN_1_5
mdefine_line|#define ATTEN_1_5    0x01
DECL|macro|ATTEN_3
mdefine_line|#define ATTEN_3      0x02
DECL|macro|ATTEN_4_5
mdefine_line|#define ATTEN_4_5    0x03
DECL|macro|ATTEN_6
mdefine_line|#define ATTEN_6      0x04
DECL|macro|ATTEN_7_5
mdefine_line|#define ATTEN_7_5    0x05
DECL|macro|ATTEN_9
mdefine_line|#define ATTEN_9      0x06
DECL|macro|ATTEN_10_5
mdefine_line|#define ATTEN_10_5   0x07
DECL|macro|ATTEN_12
mdefine_line|#define ATTEN_12     0x08
DECL|macro|ATTEN_13_5
mdefine_line|#define ATTEN_13_5   0x09
DECL|macro|ATTEN_15
mdefine_line|#define ATTEN_15     0x0a
DECL|macro|ATTEN_16_5
mdefine_line|#define ATTEN_16_5   0x0b
DECL|macro|ATTEN_18
mdefine_line|#define ATTEN_18     0x0c
DECL|macro|ATTEN_19_5
mdefine_line|#define ATTEN_19_5   0x0d
DECL|macro|ATTEN_21
mdefine_line|#define ATTEN_21     0x0e
DECL|macro|ATTEN_22_5
mdefine_line|#define ATTEN_22_5   0x0f
DECL|macro|PSS_WRITE_EMPTY
mdefine_line|#define PSS_WRITE_EMPTY 0x8000
DECL|macro|CD_POL_MASK
mdefine_line|#define CD_POL_MASK 0xFFBF
DECL|macro|CD_POL_BIT
mdefine_line|#define CD_POL_BIT  0x0040
multiline_comment|/******************************************************************************&n;&n;&t;host.h&n;&n;&t;Version 1.2&t;9/27/93&n;&n;&t;Copyright (c) 1993 Analog Devices Inc. All rights reserved&n;&n;******************************************************************************/
DECL|macro|SB_WRITE_FULL
mdefine_line|#define SB_WRITE_FULL    0x80
DECL|macro|SB_READ_FULL
mdefine_line|#define SB_READ_FULL     0x80
DECL|macro|SB_WRITE_STATUS
mdefine_line|#define SB_WRITE_STATUS  0x0C
DECL|macro|SB_READ_STATUS
mdefine_line|#define SB_READ_STATUS   0x0E
DECL|macro|SB_READ_DATA
mdefine_line|#define SB_READ_DATA     0x0A
DECL|macro|SB_WRITE_DATA
mdefine_line|#define SB_WRITE_DATA    0x0C
DECL|macro|PSS_DATA_REG
mdefine_line|#define PSS_DATA_REG     0x00
DECL|macro|PSS_STATUS_REG
mdefine_line|#define PSS_STATUS_REG   0x02
DECL|macro|PSS_WRITE_EMPTY
mdefine_line|#define PSS_WRITE_EMPTY  0x8000
DECL|macro|PSS_READ_FULL
mdefine_line|#define PSS_READ_FULL    0x4000
multiline_comment|/*_____ 1848 Sound Port bit defines */
DECL|macro|SP_IN_INIT
mdefine_line|#define SP_IN_INIT            0x80
DECL|macro|MODE_CHANGE_ENABLE
mdefine_line|#define MODE_CHANGE_ENABLE    0x40
DECL|macro|MODE_CHANGE_MASK
mdefine_line|#define MODE_CHANGE_MASK      0xbf
DECL|macro|TRANSFER_DISABLE
mdefine_line|#define TRANSFER_DISABLE      0x20
DECL|macro|TRANSFER_DISABLE_MASK
mdefine_line|#define TRANSFER_DISABLE_MASK 0xdf
DECL|macro|ADDRESS_MASK
mdefine_line|#define ADDRESS_MASK          0xf0
multiline_comment|/*_____ Status bits */
DECL|macro|INTERRUPT_STATUS
mdefine_line|#define INTERRUPT_STATUS      0x01
DECL|macro|PLAYBACK_READY
mdefine_line|#define PLAYBACK_READY        0x02
DECL|macro|PLAYBACK_LEFT
mdefine_line|#define PLAYBACK_LEFT         0x04
multiline_comment|/*_____ pbright is not left */
DECL|macro|PLAYBACK_UPPER
mdefine_line|#define PLAYBACK_UPPER        0x08
multiline_comment|/*_____ bplower is not upper */
DECL|macro|SAMPLE_OVERRUN
mdefine_line|#define SAMPLE_OVERRUN        0x10
DECL|macro|SAMPLE_UNDERRUN
mdefine_line|#define SAMPLE_UNDERRUN       0x10
DECL|macro|CAPTURE_READY
mdefine_line|#define CAPTURE_READY         0x20
DECL|macro|CAPTURE_LEFT
mdefine_line|#define CAPTURE_LEFT          0x40
multiline_comment|/*_____ cpright is not left */
DECL|macro|CAPTURE_UPPER
mdefine_line|#define CAPTURE_UPPER         0x08
multiline_comment|/*_____ cplower is not upper */
multiline_comment|/*_____ Input &amp; Output regs bits */
DECL|macro|LINE_INPUT
mdefine_line|#define LINE_INPUT            0x80
DECL|macro|AUX_INPUT
mdefine_line|#define AUX_INPUT             0x40
DECL|macro|MIC_INPUT
mdefine_line|#define MIC_INPUT             0x80
DECL|macro|MIXED_DAC_INPUT
mdefine_line|#define MIXED_DAC_INPUT       0xC0
DECL|macro|INPUT_GAIN_MASK
mdefine_line|#define INPUT_GAIN_MASK       0xf0
DECL|macro|INPUT_MIC_GAIN_ENABLE
mdefine_line|#define INPUT_MIC_GAIN_ENABLE 0x20
DECL|macro|INPUT_MIC_GAIN_MASK
mdefine_line|#define INPUT_MIC_GAIN_MASK   0xdf
DECL|macro|INPUT_SOURCE_MASK
mdefine_line|#define INPUT_SOURCE_MASK     0x3f
DECL|macro|AUX_INPUT_ATTEN_MASK
mdefine_line|#define AUX_INPUT_ATTEN_MASK  0xf0
DECL|macro|AUX_INPUT_MUTE
mdefine_line|#define AUX_INPUT_MUTE        0x80
DECL|macro|AUX_INPUT_MUTE_MASK
mdefine_line|#define AUX_INPUT_MUTE_MASK   0x7f
DECL|macro|OUTPUT_MUTE
mdefine_line|#define OUTPUT_MUTE           0x80
DECL|macro|OUTPUT_MUTE_MASK
mdefine_line|#define OUTPUT_MUTE_MASK      0x7f
DECL|macro|OUTPUT_ATTEN_MASK
mdefine_line|#define OUTPUT_ATTEN_MASK     0xc0
multiline_comment|/*_____ Clock and Data format reg bits */
DECL|macro|CLOCK_SELECT_MASK
mdefine_line|#define CLOCK_SELECT_MASK     0xfe
DECL|macro|CLOCK_XTAL2
mdefine_line|#define CLOCK_XTAL2           0x01
DECL|macro|CLOCK_XTAL1
mdefine_line|#define CLOCK_XTAL1           0x00
DECL|macro|CLOCK_FREQ_MASK
mdefine_line|#define CLOCK_FREQ_MASK       0xf1
DECL|macro|STEREO_MONO_MASK
mdefine_line|#define STEREO_MONO_MASK      0xef
DECL|macro|STEREO
mdefine_line|#define STEREO                0x10
DECL|macro|AUDIO_MONO
mdefine_line|#define AUDIO_MONO            0x00
DECL|macro|LINEAR_COMP_MASK
mdefine_line|#define LINEAR_COMP_MASK      0xdf
DECL|macro|LINEAR
mdefine_line|#define LINEAR                0x00
DECL|macro|COMPANDED
mdefine_line|#define COMPANDED             0x20
DECL|macro|FORMAT_MASK
mdefine_line|#define FORMAT_MASK           0xbf
DECL|macro|PCM
mdefine_line|#define PCM                   0x00
DECL|macro|ULAW
mdefine_line|#define ULAW                  0x00
DECL|macro|TWOS_COMP
mdefine_line|#define TWOS_COMP             0x40
DECL|macro|ALAW
mdefine_line|#define ALAW                  0x40
multiline_comment|/*_____ Interface Configuration reg bits */
DECL|macro|PLAYBACK_ENABLE
mdefine_line|#define PLAYBACK_ENABLE       0x01
DECL|macro|PLAYBACK_ENABLE_MASK
mdefine_line|#define PLAYBACK_ENABLE_MASK  0xfe
DECL|macro|CAPTURE_ENABLE
mdefine_line|#define CAPTURE_ENABLE        0x02
DECL|macro|CAPTURE_ENABLE_MASK
mdefine_line|#define CAPTURE_ENABLE_MASK   0xfd
DECL|macro|SINGLE_DMA
mdefine_line|#define SINGLE_DMA            0x04
DECL|macro|SINGLE_DMA_MASK
mdefine_line|#define SINGLE_DMA_MASK       0xfb
DECL|macro|DUAL_DMA
mdefine_line|#define DUAL_DMA              0x00
DECL|macro|AUTO_CAL_ENABLE
mdefine_line|#define AUTO_CAL_ENABLE       0x08
DECL|macro|AUTO_CAL_DISABLE_MASK
mdefine_line|#define AUTO_CAL_DISABLE_MASK 0xf7
DECL|macro|PLAYBACK_PIO_ENABLE
mdefine_line|#define PLAYBACK_PIO_ENABLE   0x40
DECL|macro|PLAYBACK_DMA_MASK
mdefine_line|#define PLAYBACK_DMA_MASK     0xbf
DECL|macro|CAPTURE_PIO_ENABLE
mdefine_line|#define CAPTURE_PIO_ENABLE    0x80
DECL|macro|CAPTURE_DMA_MASK
mdefine_line|#define CAPTURE_DMA_MASK      0x7f
multiline_comment|/*_____ Pin control bits */
DECL|macro|INTERRUPT_ENABLE
mdefine_line|#define INTERRUPT_ENABLE      0x02
DECL|macro|INTERRUPT_MASK
mdefine_line|#define INTERRUPT_MASK        0xfd
multiline_comment|/*_____ Test and init reg bits */
DECL|macro|OVERRANGE_LEFT_MASK
mdefine_line|#define OVERRANGE_LEFT_MASK   0xfc
DECL|macro|OVERRANGE_RIGHT_MASK
mdefine_line|#define OVERRANGE_RIGHT_MASK  0xf3
DECL|macro|DATA_REQUEST_STATUS
mdefine_line|#define DATA_REQUEST_STATUS   0x10
DECL|macro|AUTO_CAL_IN_PROG
mdefine_line|#define AUTO_CAL_IN_PROG      0x20
DECL|macro|PLAYBACK_UNDERRUN
mdefine_line|#define PLAYBACK_UNDERRUN     0x40
DECL|macro|CAPTURE_UNDERRUN
mdefine_line|#define CAPTURE_UNDERRUN      0x80
multiline_comment|/*_____ Miscellaneous Control reg bits */
DECL|macro|ID_MASK
mdefine_line|#define ID_MASK               0xf0
multiline_comment|/*_____ Digital Mix Control reg bits */
DECL|macro|DIGITAL_MIX1_MUTE_MASK
mdefine_line|#define DIGITAL_MIX1_MUTE_MASK 0xfe
DECL|macro|MIX_ATTEN_MASK
mdefine_line|#define MIX_ATTEN_MASK         0x03
multiline_comment|/*_____ 1848 Sound Port reg defines */
DECL|macro|SP_LEFT_INPUT_CONTROL
mdefine_line|#define SP_LEFT_INPUT_CONTROL    0x0
DECL|macro|SP_RIGHT_INPUT_CONTROL
mdefine_line|#define SP_RIGHT_INPUT_CONTROL   0x1
DECL|macro|SP_LEFT_AUX1_CONTROL
mdefine_line|#define SP_LEFT_AUX1_CONTROL     0x2
DECL|macro|SP_RIGHT_AUX1_CONTROL
mdefine_line|#define SP_RIGHT_AUX1_CONTROL    0x3
DECL|macro|SP_LEFT_AUX2_CONTROL
mdefine_line|#define SP_LEFT_AUX2_CONTROL     0x4
DECL|macro|SP_RIGHT_AUX2_CONTROL
mdefine_line|#define SP_RIGHT_AUX2_CONTROL    0x5
DECL|macro|SP_LEFT_OUTPUT_CONTROL
mdefine_line|#define SP_LEFT_OUTPUT_CONTROL   0x6
DECL|macro|SP_RIGHT_OUTPUT_CONTROL
mdefine_line|#define SP_RIGHT_OUTPUT_CONTROL  0x7
DECL|macro|SP_CLOCK_DATA_FORMAT
mdefine_line|#define SP_CLOCK_DATA_FORMAT     0x8
DECL|macro|SP_INTERFACE_CONFIG
mdefine_line|#define SP_INTERFACE_CONFIG      0x9
DECL|macro|SP_PIN_CONTROL
mdefine_line|#define SP_PIN_CONTROL           0xA
DECL|macro|SP_TEST_AND_INIT
mdefine_line|#define SP_TEST_AND_INIT         0xB
DECL|macro|SP_MISC_INFO
mdefine_line|#define SP_MISC_INFO             0xC
DECL|macro|SP_DIGITAL_MIX
mdefine_line|#define SP_DIGITAL_MIX           0xD
DECL|macro|SP_UPPER_BASE_COUNT
mdefine_line|#define SP_UPPER_BASE_COUNT      0xE
DECL|macro|SP_LOWER_BASE_COUNT
mdefine_line|#define SP_LOWER_BASE_COUNT      0xF
DECL|macro|HOST_SP_ADDR
mdefine_line|#define HOST_SP_ADDR (0x534)
DECL|macro|HOST_SP_DATA
mdefine_line|#define HOST_SP_DATA (0x535)
multiline_comment|/******************************************************************************&n;&n;&t;phillips.h&n;&n;&t;Version 1.2&t;9/27/93&n;&n;&t;Copyright (c) 1993 Analog Devices Inc. All rights reserved&n;&n;******************************************************************************/
multiline_comment|/*_____ Phillips control SW defines */
multiline_comment|/*_____ Settings and ranges */
DECL|macro|VOLUME_MAX
mdefine_line|#define VOLUME_MAX   6
DECL|macro|VOLUME_MIN
mdefine_line|#define VOLUME_MIN (-64)
DECL|macro|VOLUME_RANGE
mdefine_line|#define VOLUME_RANGE 70
DECL|macro|VOLUME_STEP
mdefine_line|#define VOLUME_STEP  2
DECL|macro|BASS_MAX
mdefine_line|#define BASS_MAX    15
DECL|macro|BASS_MIN
mdefine_line|#define BASS_MIN   (-12)
DECL|macro|BASS_STEP
mdefine_line|#define BASS_STEP    2
DECL|macro|BASS_RANGE
mdefine_line|#define BASS_RANGE 27
DECL|macro|TREBLE_MAX
mdefine_line|#define TREBLE_MAX  12
DECL|macro|TREBLE_MIN
mdefine_line|#define TREBLE_MIN (-12)
DECL|macro|TREBLE_STEP
mdefine_line|#define TREBLE_STEP  2
DECL|macro|TREBLE_RANGE
mdefine_line|#define TREBLE_RANGE 24
DECL|macro|VOLUME_CONSTANT
mdefine_line|#define VOLUME_CONSTANT 252
DECL|macro|BASS_CONSTANT
mdefine_line|#define BASS_CONSTANT   246
DECL|macro|TREBLE_CONSTANT
mdefine_line|#define TREBLE_CONSTANT 246
multiline_comment|/*_____ Software commands */
DECL|macro|SET_MASTER_COMMAND
mdefine_line|#define SET_MASTER_COMMAND  0x0010
DECL|macro|MASTER_VOLUME_LEFT
mdefine_line|#define MASTER_VOLUME_LEFT  0x0000
DECL|macro|MASTER_VOLUME_RIGHT
mdefine_line|#define MASTER_VOLUME_RIGHT 0x0100
DECL|macro|MASTER_BASS
mdefine_line|#define MASTER_BASS         0x0200
DECL|macro|MASTER_TREBLE
mdefine_line|#define MASTER_TREBLE       0x0300
DECL|macro|MASTER_SWITCH
mdefine_line|#define MASTER_SWITCH       0x0800
DECL|macro|STEREO_MODE
mdefine_line|#define STEREO_MODE  0x00ce
DECL|macro|PSEUDO_MODE
mdefine_line|#define PSEUDO_MODE  0x00d6
DECL|macro|SPATIAL_MODE
mdefine_line|#define SPATIAL_MODE 0x00de
DECL|macro|MONO_MODE
mdefine_line|#define MONO_MODE    0x00c6
DECL|macro|PSS_STEREO
mdefine_line|#define PSS_STEREO           0x00ce
DECL|macro|PSS_PSEUDO
mdefine_line|#define PSS_PSEUDO           0x00d6
DECL|macro|PSS_SPATIAL
mdefine_line|#define PSS_SPATIAL          0x00de
DECL|macro|PSS_MONO
mdefine_line|#define PSS_MONO             0x00c6
DECL|macro|PHILLIPS_VOL_MIN
mdefine_line|#define PHILLIPS_VOL_MIN          -64
DECL|macro|PHILLIPS_VOL_MAX
mdefine_line|#define PHILLIPS_VOL_MAX            6
DECL|macro|PHILLIPS_VOL_DELTA
mdefine_line|#define PHILLIPS_VOL_DELTA         70
DECL|macro|PHILLIPS_VOL_INITIAL
mdefine_line|#define PHILLIPS_VOL_INITIAL      -20
DECL|macro|PHILLIPS_VOL_CONSTANT
mdefine_line|#define PHILLIPS_VOL_CONSTANT     252
DECL|macro|PHILLIPS_VOL_STEP
mdefine_line|#define PHILLIPS_VOL_STEP           2
DECL|macro|PHILLIPS_BASS_MIN
mdefine_line|#define PHILLIPS_BASS_MIN         -12
DECL|macro|PHILLIPS_BASS_MAX
mdefine_line|#define PHILLIPS_BASS_MAX          15
DECL|macro|PHILLIPS_BASS_DELTA
mdefine_line|#define PHILLIPS_BASS_DELTA        27
DECL|macro|PHILLIPS_BASS_INITIAL
mdefine_line|#define PHILLIPS_BASS_INITIAL       0
DECL|macro|PHILLIPS_BASS_CONSTANT
mdefine_line|#define PHILLIPS_BASS_CONSTANT    246
DECL|macro|PHILLIPS_BASS_STEP
mdefine_line|#define PHILLIPS_BASS_STEP          2
DECL|macro|PHILLIPS_TREBLE_MIN
mdefine_line|#define PHILLIPS_TREBLE_MIN       -12
DECL|macro|PHILLIPS_TREBLE_MAX
mdefine_line|#define PHILLIPS_TREBLE_MAX        12
DECL|macro|PHILLIPS_TREBLE_DELTA
mdefine_line|#define PHILLIPS_TREBLE_DELTA      24
DECL|macro|PHILLIPS_TREBLE_INITIAL
mdefine_line|#define PHILLIPS_TREBLE_INITIAL     0
DECL|macro|PHILLIPS_TREBLE_CONSTANT
mdefine_line|#define PHILLIPS_TREBLE_CONSTANT  246
DECL|macro|PHILLIPS_TREBLE_STEP
mdefine_line|#define PHILLIPS_TREBLE_STEP        2
eof
