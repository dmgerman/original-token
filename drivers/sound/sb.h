DECL|macro|DSP_RESET
mdefine_line|#define DSP_RESET&t;(sbc_base + 0x6)
DECL|macro|DSP_READ
mdefine_line|#define DSP_READ&t;(sbc_base + 0xA)
DECL|macro|DSP_WRITE
mdefine_line|#define DSP_WRITE&t;(sbc_base + 0xC)
DECL|macro|DSP_COMMAND
mdefine_line|#define DSP_COMMAND&t;(sbc_base + 0xC)
DECL|macro|DSP_STATUS
mdefine_line|#define DSP_STATUS&t;(sbc_base + 0xC)
DECL|macro|DSP_DATA_AVAIL
mdefine_line|#define DSP_DATA_AVAIL&t;(sbc_base + 0xE)
DECL|macro|DSP_DATA_AVL16
mdefine_line|#define DSP_DATA_AVL16&t;(sbc_base + 0xF)
DECL|macro|MIXER_ADDR
mdefine_line|#define MIXER_ADDR&t;(sbc_base + 0x4)
DECL|macro|MIXER_DATA
mdefine_line|#define MIXER_DATA&t;(sbc_base + 0x5)
DECL|macro|OPL3_LEFT
mdefine_line|#define OPL3_LEFT&t;(sbc_base + 0x0)
DECL|macro|OPL3_RIGHT
mdefine_line|#define OPL3_RIGHT&t;(sbc_base + 0x2)
DECL|macro|OPL3_BOTH
mdefine_line|#define OPL3_BOTH&t;(sbc_base + 0x8)
multiline_comment|/* DSP Commands */
DECL|macro|DSP_CMD_SPKON
mdefine_line|#define DSP_CMD_SPKON&t;&t;0xD1
DECL|macro|DSP_CMD_SPKOFF
mdefine_line|#define DSP_CMD_SPKOFF&t;&t;0xD3
DECL|macro|DSP_CMD_DMAON
mdefine_line|#define DSP_CMD_DMAON&t;&t;0xD0
DECL|macro|DSP_CMD_DMAOFF
mdefine_line|#define DSP_CMD_DMAOFF&t;&t;0xD4
DECL|macro|IMODE_NONE
mdefine_line|#define IMODE_NONE&t;&t;0
DECL|macro|IMODE_OUTPUT
mdefine_line|#define IMODE_OUTPUT&t;&t;1
DECL|macro|IMODE_INPUT
mdefine_line|#define IMODE_INPUT&t;&t;2
DECL|macro|IMODE_INIT
mdefine_line|#define IMODE_INIT&t;&t;3
DECL|macro|IMODE_MIDI
mdefine_line|#define IMODE_MIDI&t;&t;4
DECL|macro|NORMAL_MIDI
mdefine_line|#define NORMAL_MIDI&t;0
DECL|macro|UART_MIDI
mdefine_line|#define UART_MIDI&t;1
eof
