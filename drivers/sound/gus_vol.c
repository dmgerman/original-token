multiline_comment|/*&n; * gus_vol.c - Compute volume for GUS.&n; *&n; * Greg Lee 1993.&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#ifndef EXCLUDE_GUS
macro_line|#include &quot;gus_linearvol.h&quot;
DECL|macro|GUS_VOLUME
mdefine_line|#define GUS_VOLUME&t;gus_wave_volume
r_extern
r_int
id|gus_wave_volume
suffix:semicolon
multiline_comment|/*&n; * Calculate gus volume from note velocity, main volume, expression, and&n; * intrinsic patch volume given in patch library.  Expression is multiplied&n; * in, so it emphasizes differences in note velocity, while main volume is&n; * added in -- I don&squot;t know whether this is right, but it seems reasonable to&n; * me.  (In the previous stage, main volume controller messages were changed&n; * to expression controller messages, if they were found to be used for&n; * dynamic volume adjustments, so here, main volume can be assumed to be&n; * constant throughout a song.)&n; *&n; * Intrinsic patch volume is added in, but if over 64 is also multiplied in, so&n; * we can give a big boost to very weak voices like nylon guitar and the&n; * basses.  The normal value is 64.  Strings are assigned lower values.&n; */
r_int
r_int
DECL|function|gus_adagio_vol
id|gus_adagio_vol
(paren
r_int
id|vel
comma
r_int
id|mainv
comma
r_int
id|xpn
comma
r_int
id|voicev
)paren
(brace
r_int
id|i
comma
id|m
comma
id|n
comma
id|x
suffix:semicolon
multiline_comment|/*&n;   * A voice volume of 64 is considered neutral, so adjust the main volume if&n;   * something other than this neutral value was assigned in the patch&n;   * library.&n;   */
id|x
op_assign
l_int|256
op_plus
l_int|6
op_star
(paren
id|voicev
op_minus
l_int|64
)paren
suffix:semicolon
multiline_comment|/*&n;   * Boost expression by voice volume above neutral.&n;   */
r_if
c_cond
(paren
id|voicev
OG
l_int|65
)paren
id|xpn
op_add_assign
id|voicev
op_minus
l_int|64
suffix:semicolon
id|xpn
op_add_assign
(paren
id|voicev
op_minus
l_int|64
)paren
op_div
l_int|2
suffix:semicolon
multiline_comment|/*&n;   * Combine multiplicative and level components.&n;   */
id|x
op_assign
id|vel
op_star
id|xpn
op_star
l_int|6
op_plus
(paren
id|voicev
op_div
l_int|4
)paren
op_star
id|x
suffix:semicolon
macro_line|#ifdef GUS_VOLUME
multiline_comment|/*&n;   * Further adjustment by installation-specific master volume control&n;   * (default 60).&n;   */
id|x
op_assign
(paren
id|x
op_star
id|GUS_VOLUME
op_star
id|GUS_VOLUME
)paren
op_div
l_int|10000
suffix:semicolon
macro_line|#endif
macro_line|#ifdef GUS_USE_CHN_MAIN_VOLUME
multiline_comment|/*&n;   * Experimental support for the channel main volume&n;   */
id|mainv
op_assign
(paren
id|mainv
op_div
l_int|2
)paren
op_plus
l_int|64
suffix:semicolon
multiline_comment|/* Scale to 64 to 127 */
id|x
op_assign
(paren
id|x
op_star
id|mainv
op_star
id|mainv
)paren
op_div
l_int|16384
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|x
OL
l_int|2
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|x
op_ge
l_int|65535
)paren
r_return
(paren
(paren
l_int|15
op_lshift
l_int|8
)paren
op_or
l_int|255
)paren
suffix:semicolon
multiline_comment|/*&n;   * Convert to gus&squot;s logarithmic form with 4 bit exponent i and 8 bit&n;   * mantissa m.&n;   */
id|n
op_assign
id|x
suffix:semicolon
id|i
op_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|128
)paren
(brace
r_while
c_loop
(paren
id|i
OG
l_int|0
op_logical_and
id|n
OL
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|i
op_decrement
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|n
OG
l_int|255
)paren
(brace
id|n
op_rshift_assign
l_int|1
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;   * Mantissa is part of linear volume not expressed in exponent.  (This is&n;   * not quite like real logs -- I wonder if it&squot;s right.)&n;   */
id|m
op_assign
id|x
op_minus
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;   * Adjust mantissa to 8 bits.&n;   */
r_if
c_cond
(paren
id|m
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i
OG
l_int|8
)paren
id|m
op_rshift_assign
id|i
op_minus
l_int|8
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
l_int|8
)paren
id|m
op_lshift_assign
l_int|8
op_minus
id|i
suffix:semicolon
)brace
r_return
(paren
(paren
id|i
op_lshift
l_int|8
)paren
op_plus
id|m
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Volume-values are interpreted as linear values. Volume is based on the&n; * value supplied with SEQ_START_NOTE(), channel main volume (if compiled in)&n; * and the volume set by the mixer-device (default 60%).&n; */
r_int
r_int
DECL|function|gus_linear_vol
id|gus_linear_vol
(paren
r_int
id|vol
comma
r_int
id|mainvol
)paren
(brace
r_int
id|mixer_mainvol
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_le
l_int|0
)paren
id|vol
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vol
op_ge
l_int|127
)paren
id|vol
op_assign
l_int|127
suffix:semicolon
macro_line|#ifdef GUS_VOLUME
id|mixer_mainvol
op_assign
id|GUS_VOLUME
suffix:semicolon
macro_line|#else
id|mixer_mainvol
op_assign
l_int|100
suffix:semicolon
macro_line|#endif
macro_line|#ifdef GUS_USE_CHN_MAIN_VOLUME
r_if
c_cond
(paren
id|mainvol
op_le
l_int|0
)paren
id|mainvol
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mainvol
op_ge
l_int|127
)paren
id|mainvol
op_assign
l_int|127
suffix:semicolon
macro_line|#else
id|mainvol
op_assign
l_int|128
suffix:semicolon
macro_line|#endif
r_return
id|gus_linearvol
(braket
(paren
(paren
(paren
id|vol
op_star
id|mainvol
)paren
op_div
l_int|128
)paren
op_star
id|mixer_mainvol
)paren
op_div
l_int|100
)braket
suffix:semicolon
)brace
macro_line|#endif
eof
