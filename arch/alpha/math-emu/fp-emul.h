multiline_comment|/*&n; * These defines correspond to the dynamic rounding mode bits in the&n; * Floating Point Control Register.  They also happen to correspond to&n; * the instruction encodings except that 0x03 signifies dynamic&n; * rounding mode in that case.&n; */
DECL|macro|ROUND_CHOP
mdefine_line|#define ROUND_CHOP&t;0x00&t;/* chopped (aka round towards zero) */
DECL|macro|ROUND_NINF
mdefine_line|#define ROUND_NINF&t;0x01&t;/* round towards negative infinity */
DECL|macro|ROUND_NEAR
mdefine_line|#define ROUND_NEAR&t;0x02&t;/* round towards nearest number */
DECL|macro|ROUND_PINF
mdefine_line|#define ROUND_PINF&t;0x03&t;/* round towards positive infinity */
eof
