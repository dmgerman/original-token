multiline_comment|/*&n; * ac97.h &n; * &n; * definitions for the AC97, Intel&squot;s Audio Codec 97 Spec&n; */
macro_line|#ifndef _AC97_H_
DECL|macro|_AC97_H_
mdefine_line|#define _AC97_H_
singleline_comment|// conections on concert 97 */
DECL|macro|AC97_RESET
mdefine_line|#define  AC97_RESET              0x0000      
singleline_comment|//  */
DECL|macro|AC97_MASTER_VOL_STEREO
mdefine_line|#define  AC97_MASTER_VOL_STEREO  0x0002      
singleline_comment|// Line Out
DECL|macro|AC97_HEADPHONE_VOL
mdefine_line|#define  AC97_HEADPHONE_VOL      0x0004      
singleline_comment|// 
DECL|macro|AC97_MASTER_VOL_MONO
mdefine_line|#define  AC97_MASTER_VOL_MONO    0x0006      
singleline_comment|// TAD Output
DECL|macro|AC97_MASTER_TONE
mdefine_line|#define  AC97_MASTER_TONE        0x0008      
singleline_comment|//
DECL|macro|AC97_PCBEEP_VOL
mdefine_line|#define  AC97_PCBEEP_VOL         0x000a      
singleline_comment|// none
DECL|macro|AC97_PHONE_VOL
mdefine_line|#define  AC97_PHONE_VOL          0x000c      
singleline_comment|// TAD Input (mono)
DECL|macro|AC97_MIC_VOL
mdefine_line|#define  AC97_MIC_VOL            0x000e      
singleline_comment|// MIC Input (mono)
DECL|macro|AC97_LINEIN_VOL
mdefine_line|#define  AC97_LINEIN_VOL         0x0010      
singleline_comment|// Line Input (stereo)
DECL|macro|AC97_CD_VOL
mdefine_line|#define  AC97_CD_VOL             0x0012      
singleline_comment|// CD Input (stereo)
DECL|macro|AC97_VIDEO_VOL
mdefine_line|#define  AC97_VIDEO_VOL          0x0014      
singleline_comment|// none
DECL|macro|AC97_AUX_VOL
mdefine_line|#define  AC97_AUX_VOL            0x0016      
singleline_comment|// Aux Input (stereo)
DECL|macro|AC97_PCMOUT_VOL
mdefine_line|#define  AC97_PCMOUT_VOL         0x0018      
singleline_comment|// Wave Output (stereo)
DECL|macro|AC97_RECORD_SELECT
mdefine_line|#define  AC97_RECORD_SELECT      0x001a      
singleline_comment|//
DECL|macro|AC97_RECORD_GAIN
mdefine_line|#define  AC97_RECORD_GAIN        0x001c
DECL|macro|AC97_RECORD_GAIN_MIC
mdefine_line|#define  AC97_RECORD_GAIN_MIC    0x001e
DECL|macro|AC97_GENERAL_PURPOSE
mdefine_line|#define  AC97_GENERAL_PURPOSE    0x0020
DECL|macro|AC97_3D_CONTROL
mdefine_line|#define  AC97_3D_CONTROL         0x0022
DECL|macro|AC97_MODEM_RATE
mdefine_line|#define  AC97_MODEM_RATE         0x0024
DECL|macro|AC97_POWER_CONTROL
mdefine_line|#define  AC97_POWER_CONTROL      0x0026
multiline_comment|/* registers 0x0028 - 0x0058 are reserved */
multiline_comment|/* registers 0x005a - 0x007a are vendor reserved */
DECL|macro|AC97_VENDOR_ID1
mdefine_line|#define  AC97_VENDOR_ID1         0x007c
DECL|macro|AC97_VENDOR_ID2
mdefine_line|#define  AC97_VENDOR_ID2         0x007e
multiline_comment|/* volume control bit defines */
DECL|macro|AC97_MUTE
mdefine_line|#define AC97_MUTE                0x8000
DECL|macro|AC97_MICBOOST
mdefine_line|#define AC97_MICBOOST            0x0040
DECL|macro|AC97_LEFTVOL
mdefine_line|#define AC97_LEFTVOL             0x3f00
DECL|macro|AC97_RIGHTVOL
mdefine_line|#define AC97_RIGHTVOL            0x003f
multiline_comment|/* record mux defines */
DECL|macro|AC97_RECMUX_MIC
mdefine_line|#define AC97_RECMUX_MIC          0x0000
DECL|macro|AC97_RECMUX_CD
mdefine_line|#define AC97_RECMUX_CD           0x0101
DECL|macro|AC97_RECMUX_VIDEO
mdefine_line|#define AC97_RECMUX_VIDEO        0x0202      /* not used */
DECL|macro|AC97_RECMUX_AUX
mdefine_line|#define AC97_RECMUX_AUX          0x0303      
DECL|macro|AC97_RECMUX_LINE
mdefine_line|#define AC97_RECMUX_LINE         0x0404      
DECL|macro|AC97_RECMUX_STEREO_MIX
mdefine_line|#define AC97_RECMUX_STEREO_MIX   0x0505
DECL|macro|AC97_RECMUX_MONO_MIX
mdefine_line|#define AC97_RECMUX_MONO_MIX     0x0606
DECL|macro|AC97_RECMUX_PHONE
mdefine_line|#define AC97_RECMUX_PHONE        0x0707
multiline_comment|/* general purpose register bit defines */
DECL|macro|AC97_GP_LPBK
mdefine_line|#define AC97_GP_LPBK             0x0080      /* Loopback mode */
DECL|macro|AC97_GP_MS
mdefine_line|#define AC97_GP_MS               0x0100      /* Mic Select 0=Mic1, 1=Mic2 */
DECL|macro|AC97_GP_MIX
mdefine_line|#define AC97_GP_MIX              0x0200      /* Mono output select 0=Mix, 1=Mic */
DECL|macro|AC97_GP_RLBK
mdefine_line|#define AC97_GP_RLBK             0x0400      /* Remote Loopback - Modem line codec */
DECL|macro|AC97_GP_LLBK
mdefine_line|#define AC97_GP_LLBK             0x0800      /* Local Loopback - Modem Line codec */
DECL|macro|AC97_GP_LD
mdefine_line|#define AC97_GP_LD               0x1000      /* Loudness 1=on */
DECL|macro|AC97_GP_3D
mdefine_line|#define AC97_GP_3D               0x2000      /* 3D Enhancement 1=on */
DECL|macro|AC97_GP_ST
mdefine_line|#define AC97_GP_ST               0x4000      /* Stereo Enhancement 1=on */
DECL|macro|AC97_GP_POP
mdefine_line|#define AC97_GP_POP              0x8000      /* Pcm Out Path, 0=pre 3D, 1=post 3D */
multiline_comment|/* powerdown control and status bit defines */
multiline_comment|/* status */
DECL|macro|AC97_PWR_MDM
mdefine_line|#define AC97_PWR_MDM             0x0010      /* Modem section ready */
DECL|macro|AC97_PWR_REF
mdefine_line|#define AC97_PWR_REF             0x0008      /* Vref nominal */
DECL|macro|AC97_PWR_ANL
mdefine_line|#define AC97_PWR_ANL             0x0004      /* Analog section ready */
DECL|macro|AC97_PWR_DAC
mdefine_line|#define AC97_PWR_DAC             0x0002      /* DAC section ready */
DECL|macro|AC97_PWR_ADC
mdefine_line|#define AC97_PWR_ADC             0x0001      /* ADC section ready */
multiline_comment|/* control */
DECL|macro|AC97_PWR_PR0
mdefine_line|#define AC97_PWR_PR0             0x0100      /* ADC and Mux powerdown */
DECL|macro|AC97_PWR_PR1
mdefine_line|#define AC97_PWR_PR1             0x0200      /* DAC powerdown */
DECL|macro|AC97_PWR_PR2
mdefine_line|#define AC97_PWR_PR2             0x0400      /* Output mixer powerdown (Vref on) */
DECL|macro|AC97_PWR_PR3
mdefine_line|#define AC97_PWR_PR3             0x0800      /* Output mixer powerdown (Vref off) */
DECL|macro|AC97_PWR_PR4
mdefine_line|#define AC97_PWR_PR4             0x1000      /* AC-link powerdown */
DECL|macro|AC97_PWR_PR5
mdefine_line|#define AC97_PWR_PR5             0x2000      /* Internal Clk disable */
DECL|macro|AC97_PWR_PR6
mdefine_line|#define AC97_PWR_PR6             0x4000      /* HP amp powerdown */
DECL|macro|AC97_PWR_PR7
mdefine_line|#define AC97_PWR_PR7             0x8000      /* Modem off - if supported */
multiline_comment|/* useful power states */
DECL|macro|AC97_PWR_D0
mdefine_line|#define AC97_PWR_D0              0x0000      /* everything on */
DECL|macro|AC97_PWR_D1
mdefine_line|#define AC97_PWR_D1              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR4
DECL|macro|AC97_PWR_D2
mdefine_line|#define AC97_PWR_D2              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR2|AC97_PWR_PR3|AC97_PWR_PR4
DECL|macro|AC97_PWR_D3
mdefine_line|#define AC97_PWR_D3              AC97_PWR_PR0|AC97_PWR_PR1|AC97_PWR_PR2|AC97_PWR_PR3|AC97_PWR_PR4
DECL|macro|AC97_PWR_ANLOFF
mdefine_line|#define AC97_PWR_ANLOFF          AC97_PWR_PR2|AC97_PWR_PR3  /* analog section off */
macro_line|#endif /* _AC97_H_ */
eof
