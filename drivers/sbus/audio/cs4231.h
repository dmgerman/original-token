multiline_comment|/*&n; * drivers/sbus/audio/cs4231.h&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; * Copyright (C) 1997 Derrick J. Brashear (shadow@dementia.org)&n; */
macro_line|#ifndef _CS4231_H_
DECL|macro|_CS4231_H_
mdefine_line|#define _CS4231_H_
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|cs4231_regs
r_struct
id|cs4231_regs
(brace
DECL|member|iar
id|u_char
id|iar
suffix:semicolon
multiline_comment|/* Index Address Register */
DECL|member|pad0
id|u_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr
id|u_char
id|idr
suffix:semicolon
multiline_comment|/* Indexed Data Register */
DECL|member|pad1
id|u_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|statr
id|u_char
id|statr
suffix:semicolon
multiline_comment|/* Status Register */
DECL|member|pad2
id|u_char
id|pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|piodr
id|u_char
id|piodr
suffix:semicolon
multiline_comment|/* PIO Data Register I/O */
DECL|member|pad3
id|u_char
id|pad3
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cs4231_dma
r_struct
id|cs4231_dma
(brace
DECL|member|dmacsr
id|u_long
id|dmacsr
suffix:semicolon
multiline_comment|/* APC CSR */
DECL|member|dmapad
id|u_long
id|dmapad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dmacva
id|u_long
id|dmacva
suffix:semicolon
multiline_comment|/* Capture Virtual Address */
DECL|member|dmacc
id|u_long
id|dmacc
suffix:semicolon
multiline_comment|/* Capture Count */
DECL|member|dmacnva
id|u_long
id|dmacnva
suffix:semicolon
multiline_comment|/* Capture Next Virtual Address */
DECL|member|dmacnc
id|u_long
id|dmacnc
suffix:semicolon
multiline_comment|/* Capture Next Count */
DECL|member|dmapva
id|u_long
id|dmapva
suffix:semicolon
multiline_comment|/* Playback Virtual Address */
DECL|member|dmapc
id|u_long
id|dmapc
suffix:semicolon
multiline_comment|/* Playback Count */
DECL|member|dmapnva
id|u_long
id|dmapnva
suffix:semicolon
multiline_comment|/* Playback Next Virtual Address */
DECL|member|dmapnc
id|u_long
id|dmapnc
suffix:semicolon
multiline_comment|/* Playback Next Count */
)brace
suffix:semicolon
DECL|struct|cs4231_chip
r_struct
id|cs4231_chip
(brace
DECL|member|pioregs
r_struct
id|cs4231_regs
op_star
id|pioregs
suffix:semicolon
DECL|member|dmaregs
r_struct
id|cs4231_dma
id|dmaregs
suffix:semicolon
DECL|member|perchip_info
r_struct
id|audio_info
id|perchip_info
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|regs_size
r_int
r_int
id|regs_size
suffix:semicolon
multiline_comment|/* Keep track of various info */
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|dma2
r_int
id|dma2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Status bits */
DECL|macro|CS_STATUS_NEED_INIT
mdefine_line|#define CS_STATUS_NEED_INIT 0x01
DECL|macro|CS_STATUS_INIT_ON_CLOSE
mdefine_line|#define CS_STATUS_INIT_ON_CLOSE 0x02
DECL|macro|CS_STATUS_REV_A
mdefine_line|#define CS_STATUS_REV_A 0x04
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT      9000000
DECL|macro|GAIN_SET
mdefine_line|#define GAIN_SET(var, gain)     ((var &amp; ~(0x3f)) | gain)
DECL|macro|RECGAIN_SET
mdefine_line|#define RECGAIN_SET(var, gain)  ((var &amp; ~(0x1f)) | gain)
DECL|macro|IAR_AUTOCAL_BEGIN
mdefine_line|#define IAR_AUTOCAL_BEGIN       0x40 /* IAR_MCE */
DECL|macro|IAR_AUTOCAL_END
mdefine_line|#define IAR_AUTOCAL_END         ~(0x40) /* IAR_MCD */
DECL|macro|IAR_NOT_READY
mdefine_line|#define IAR_NOT_READY            0x80    /* 80h not ready CODEC state */
multiline_comment|/* Each register assumed mode 1 and 2 unless noted */
multiline_comment|/* 0 - Left Input Control */
multiline_comment|/* 1 - Right Input Control */
DECL|macro|MIC_ENABLE
mdefine_line|#define MIC_ENABLE(var)         ((var &amp; 0x2f) | 0x80)
DECL|macro|LINE_ENABLE
mdefine_line|#define LINE_ENABLE(var)        (var &amp; 0x2f)
DECL|macro|CDROM_ENABLE
mdefine_line|#define CDROM_ENABLE(var)       ((var &amp; 0x2f) | 0x40)
DECL|macro|INPUTCR_AUX1
mdefine_line|#define INPUTCR_AUX1            0x40
multiline_comment|/* 2 - Left Aux 1 Input Control */
multiline_comment|/* 3 - Right Aux 1 Input Control */
multiline_comment|/* 4 - Left Aux 2 Input Control */
multiline_comment|/* 5 - Right Aux 2 Input Control */
multiline_comment|/* 6 - Left Output Control */
multiline_comment|/* 7 - Right Output Control */
DECL|macro|OUTCR_MUTE
mdefine_line|#define OUTCR_MUTE              0x80
DECL|macro|OUTCR_UNMUTE
mdefine_line|#define OUTCR_UNMUTE            ~0x80
multiline_comment|/* 8 - Playback Data Format (Mode 2) */
DECL|macro|CHANGE_DFR
mdefine_line|#define CHANGE_DFR(var, val)            ((var &amp; ~(0xF)) | val)
DECL|macro|CHANGE_ENCODING
mdefine_line|#define CHANGE_ENCODING(var, val)       ((var &amp; ~(0xe0)) | val)
DECL|macro|DEFAULT_DATA_FMAT
mdefine_line|#define DEFAULT_DATA_FMAT               CS4231_DFR_ULAW
DECL|macro|CS4231_DFR_8000
mdefine_line|#define CS4231_DFR_8000                 0x00
DECL|macro|CS4231_DFR_9600
mdefine_line|#define CS4231_DFR_9600                 0x0e
DECL|macro|CS4231_DFR_11025
mdefine_line|#define CS4231_DFR_11025                0x03
DECL|macro|CS4231_DFR_16000
mdefine_line|#define CS4231_DFR_16000                0x02
DECL|macro|CS4231_DFR_18900
mdefine_line|#define CS4231_DFR_18900                0x05
DECL|macro|CS4231_DFR_22050
mdefine_line|#define CS4231_DFR_22050                0x07
DECL|macro|CS4231_DFR_32000
mdefine_line|#define CS4231_DFR_32000                0x06
DECL|macro|CS4231_DFR_37800
mdefine_line|#define CS4231_DFR_37800                0x09
DECL|macro|CS4231_DFR_44100
mdefine_line|#define CS4231_DFR_44100                0x0b
DECL|macro|CS4231_DFR_48000
mdefine_line|#define CS4231_DFR_48000                0x0c
DECL|macro|CS4231_DFR_LINEAR8
mdefine_line|#define CS4231_DFR_LINEAR8              0x00
DECL|macro|CS4231_DFR_ULAW
mdefine_line|#define CS4231_DFR_ULAW                 0x20
DECL|macro|CS4231_DFR_ALAW
mdefine_line|#define CS4231_DFR_ALAW                 0x60
DECL|macro|CS4231_DFR_ADPCM
mdefine_line|#define CS4231_DFR_ADPCM                0xa0
DECL|macro|CS4231_DFR_LINEARBE
mdefine_line|#define CS4231_DFR_LINEARBE             0xc0
DECL|macro|CS4231_STEREO_ON
mdefine_line|#define CS4231_STEREO_ON(val)           (val | 0x10)
DECL|macro|CS4231_MONO_ON
mdefine_line|#define CS4231_MONO_ON(val)             (val &amp; ~0x10)
multiline_comment|/* 9 - Interface Config. Register */
DECL|macro|CHIP_INACTIVE
mdefine_line|#define CHIP_INACTIVE           0x08
DECL|macro|PEN_ENABLE
mdefine_line|#define PEN_ENABLE              (0x01)
DECL|macro|PEN_DISABLE
mdefine_line|#define PEN_DISABLE             (~0x01)
DECL|macro|CEN_ENABLE
mdefine_line|#define CEN_ENABLE              (0x02)
DECL|macro|CEN_DISABLE
mdefine_line|#define CEN_DISABLE             (~0x02)
DECL|macro|ACAL_DISABLE
mdefine_line|#define ACAL_DISABLE            (~0x08)
DECL|macro|ICR_AUTOCAL_INIT
mdefine_line|#define ICR_AUTOCAL_INIT        0x01
multiline_comment|/* 10 - Pin Control Register */
DECL|macro|INTR_ON
mdefine_line|#define INTR_ON                 0x82
DECL|macro|INTR_OFF
mdefine_line|#define INTR_OFF                0x80
DECL|macro|PINCR_LINE_MUTE
mdefine_line|#define PINCR_LINE_MUTE         0x40
DECL|macro|PINCR_HDPH_MUTE
mdefine_line|#define PINCR_HDPH_MUTE         0x80
multiline_comment|/* 11 - Test/Initialization */
DECL|macro|DRQ_STAT
mdefine_line|#define DRQ_STAT                0x10
DECL|macro|AUTOCAL_IN_PROGRESS
mdefine_line|#define AUTOCAL_IN_PROGRESS      0x20
multiline_comment|/* 12 - Misc Information */
DECL|macro|MISC_IR_MODE2
mdefine_line|#define MISC_IR_MODE2           0x40
multiline_comment|/* 13 - Loopback Control */
DECL|macro|LOOPB_ON
mdefine_line|#define LOOPB_ON                0x01
DECL|macro|LOOPB_OFF
mdefine_line|#define LOOPB_OFF               0x00
multiline_comment|/* 14 - Unused (mode 1) */
multiline_comment|/* 15 - Unused (mode 1) */
multiline_comment|/* 14 - Playback Upper (mode 2) */
multiline_comment|/* 15 - Playback Lower (mode 2) */
multiline_comment|/* The rest are mode 2 only */
multiline_comment|/* 16 - Alternate Feature 1 Enable */
DECL|macro|OLB_ENABLE
mdefine_line|#define OLB_ENABLE              0x80
multiline_comment|/* 17 - Alternate Feature 2 Enable */
DECL|macro|HPF_ON
mdefine_line|#define HPF_ON                  0x01
DECL|macro|XTALE_ON
mdefine_line|#define XTALE_ON                0x20
multiline_comment|/* 18 - Left Line Input Gain */
multiline_comment|/* 19 - Right Line Input Gain */
multiline_comment|/* 20 - Timer High */
multiline_comment|/* 21 - Timer Low */
multiline_comment|/* 22 - unused */
multiline_comment|/* 23 - unused */
multiline_comment|/* 24 - Alternate Feature Status */
DECL|macro|CS_PU
mdefine_line|#define CS_PU                   0x01 /* Underrun */
DECL|macro|CS_PO
mdefine_line|#define CS_PO                   0x20 /* Overrun */
multiline_comment|/* 25 - Version */
DECL|macro|CS4231A
mdefine_line|#define CS4231A         0x20
DECL|macro|CS4231CDE
mdefine_line|#define CS4231CDE       0x80
multiline_comment|/* 26 - Mono I/O Control */
DECL|macro|CHANGE_MONO_GAIN
mdefine_line|#define CHANGE_MONO_GAIN(val)   ((val &amp; ~(0xFF)) | val)
DECL|macro|MONO_IOCR_MUTE
mdefine_line|#define MONO_IOCR_MUTE       0x40
multiline_comment|/* 27 - Unused */
multiline_comment|/* 28 - Capture Data Format */
multiline_comment|/* see register 8 */
multiline_comment|/* 29 - Unused */
multiline_comment|/* 30 - Capture Upper */
multiline_comment|/* 31 - Capture Lower */
multiline_comment|/* Following are CSR register definitions for the Sparc */
multiline_comment|/* Also list &quot;Solaris&quot; equivs for now, not really useful tho */
DECL|macro|CS_INT_PENDING
mdefine_line|#define CS_INT_PENDING 0x800000 /* APC_IP */ /* Interrupt Pending */
DECL|macro|CS_PLAY_INT
mdefine_line|#define CS_PLAY_INT    0x400000 /* APC_PI */ /* Playback interrupt */
DECL|macro|CS_CAPT_INT
mdefine_line|#define CS_CAPT_INT    0x200000 /* APC_CI */ /* Capture interrupt */
DECL|macro|CS_GENL_INT
mdefine_line|#define CS_GENL_INT    0x100000 /* APC_EI */ /* General interrupt */
DECL|macro|CS_XINT_ENA
mdefine_line|#define CS_XINT_ENA    0x80000  /* APC_IE */ /* General ext int. enable */
DECL|macro|CS_XINT_PLAY
mdefine_line|#define CS_XINT_PLAY   0x40000  /* APC_PIE */ /* Playback ext intr */
DECL|macro|CS_XINT_CAPT
mdefine_line|#define CS_XINT_CAPT   0x20000  /* APC_CIE */ /* Capture ext intr */
DECL|macro|CS_XINT_GENL
mdefine_line|#define CS_XINT_GENL   0x10000  /* APC_EIE */ /* Error ext intr */
DECL|macro|CS_XINT_EMPT
mdefine_line|#define CS_XINT_EMPT   0x8000   /* APC_PMI */ /* Pipe empty interrupt */
DECL|macro|CS_XINT_PEMP
mdefine_line|#define CS_XINT_PEMP   0x4000   /* APC_PM */ /* Play pipe empty */
DECL|macro|CS_XINT_PNVA
mdefine_line|#define CS_XINT_PNVA   0x2000   /* APC_PD */ /* Playback NVA dirty */
DECL|macro|CS_XINT_PENA
mdefine_line|#define CS_XINT_PENA   0x1000   /* APC_PMIE */ /* play pipe empty Int enable */
DECL|macro|CS_XINT_COVF
mdefine_line|#define CS_XINT_COVF   0x800    /* APC_CM */ /* Cap data dropped on floor */
DECL|macro|CS_XINT_CNVA
mdefine_line|#define CS_XINT_CNVA   0x400    /* APC_CD */ /* Capture NVA dirty */
DECL|macro|CS_XINT_CEMP
mdefine_line|#define CS_XINT_CEMP   0x200    /* APC_CMI */ /* Capture pipe empty interrupt */
DECL|macro|CS_XINT_CENA
mdefine_line|#define CS_XINT_CENA   0x100    /* APC_CMIE */ /* Cap. pipe empty int enable */
DECL|macro|CS_PPAUSE
mdefine_line|#define CS_PPAUSE      0x80     /* APC_PPAUSE */ /* Pause the play DMA */
DECL|macro|CS_CPAUSE
mdefine_line|#define CS_CPAUSE      0x40     /* APC_CPAUSE */ /* Pause the capture DMA */
DECL|macro|CS_CDC_RESET
mdefine_line|#define CS_CDC_RESET   0x20     /* APC_CODEC_PDN */ /* CODEC RESET */
DECL|macro|PDMA_READY
mdefine_line|#define PDMA_READY     0x08     /* PDMA_GO */
DECL|macro|CDMA_READY
mdefine_line|#define CDMA_READY     0x04     /* CDMA_GO */
DECL|macro|CS_CHIP_RESET
mdefine_line|#define CS_CHIP_RESET  0x01     /* APC_RESET */       /* Reset the chip */
DECL|macro|CS_INIT_SETUP
mdefine_line|#define CS_INIT_SETUP  (CDMA_READY | PDMA_READY | CS_XINT_ENA | CS_XINT_PLAY | CS_XINT_GENL | CS_INT_PENDING | CS_PLAY_INT | CS_CAPT_INT | CS_GENL_INT) 
DECL|macro|CS_PLAY_SETUP
mdefine_line|#define CS_PLAY_SETUP  (CS_GENL_INT | CS_PLAY_INT | CS_XINT_ENA | CS_XINT_PLAY | CS_XINT_EMPT | CS_XINT_GENL | CS_XINT_PENA | PDMA_READY)
DECL|macro|CS_CAPT_SETUP
mdefine_line|#define CS_CAPT_SETUP  (CS_GENL_INT | CS_CAPT_INT | CS_XINT_ENA | CS_XINT_CAPT | CS_XINT_CEMP | CS_XINT_GENL | CDMA_READY)
DECL|macro|CS4231_MIN_ATEN
mdefine_line|#define CS4231_MIN_ATEN     (0)
DECL|macro|CS4231_MAX_ATEN
mdefine_line|#define CS4231_MAX_ATEN     (31)
DECL|macro|CS4231_MAX_DEV_ATEN
mdefine_line|#define CS4231_MAX_DEV_ATEN (63)
DECL|macro|CS4231_MON_MIN_ATEN
mdefine_line|#define CS4231_MON_MIN_ATEN         (0)
DECL|macro|CS4231_MON_MAX_ATEN
mdefine_line|#define CS4231_MON_MAX_ATEN         (63)
DECL|macro|CS4231_DEFAULT_PLAYGAIN
mdefine_line|#define CS4231_DEFAULT_PLAYGAIN     (132)
DECL|macro|CS4231_DEFAULT_RECGAIN
mdefine_line|#define CS4231_DEFAULT_RECGAIN      (126)
DECL|macro|CS4231_MIN_GAIN
mdefine_line|#define CS4231_MIN_GAIN     (0)
DECL|macro|CS4231_MAX_GAIN
mdefine_line|#define CS4231_MAX_GAIN     (15)
DECL|macro|CS4231_PRECISION
mdefine_line|#define CS4231_PRECISION    (8)             /* # of bits/sample */
DECL|macro|CS4231_CHANNELS
mdefine_line|#define CS4231_CHANNELS     (1)             /* channels/sample */
DECL|macro|CS4231_RATE
mdefine_line|#define CS4231_RATE   (8000)                /* default sample rate */
multiline_comment|/* Other rates supported are:&n; * 9600, 11025, 16000, 18900, 22050, 32000, 37800, 44100, 48000 &n; */
macro_line|#endif
eof
