macro_line|#ifndef MSP3400_H
DECL|macro|MSP3400_H
mdefine_line|#define MSP3400_H
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|macro|MSP_SET_TVNORM
mdefine_line|#define MSP_SET_TVNORM     _IOW(&squot;m&squot;,1,int)  /* TV mode + PAL/SECAM/NTSC  */
DECL|macro|MSP_SET_RADIO
mdefine_line|#define MSP_SET_RADIO      _IO(&squot;m&squot;,2)       /* Radio mode                */
DECL|macro|MSP_NEWCHANNEL
mdefine_line|#define MSP_NEWCHANNEL     _IO(&squot;m&squot;,3)       /* indicate new channel      */
DECL|macro|MSP_GET_VOLUME
mdefine_line|#define MSP_GET_VOLUME     _IOR(&squot;m&squot;,4,int)
DECL|macro|MSP_SET_VOLUME
mdefine_line|#define MSP_SET_VOLUME     _IOW(&squot;m&squot;,5,int)
DECL|macro|MSP_GET_STEREO
mdefine_line|#define MSP_GET_STEREO     _IOR(&squot;m&squot;,6,int)
DECL|macro|MSP_SET_STEREO
mdefine_line|#define MSP_SET_STEREO     _IOW(&squot;m&squot;,7,int)
DECL|macro|MSP_GET_DC
mdefine_line|#define MSP_GET_DC         _IOW(&squot;m&squot;,8,int)
DECL|macro|MSP_GET_BASS
mdefine_line|#define MSP_GET_BASS       _IOR(&squot;m&squot;, 9,int)
DECL|macro|MSP_SET_BASS
mdefine_line|#define MSP_SET_BASS       _IOW(&squot;m&squot;,10,int)
DECL|macro|MSP_GET_TREBLE
mdefine_line|#define MSP_GET_TREBLE     _IOR(&squot;m&squot;,11,int)
DECL|macro|MSP_SET_TREBLE
mdefine_line|#define MSP_SET_TREBLE     _IOW(&squot;m&squot;,12,int)
macro_line|#endif /* MSP3400_H */
eof
