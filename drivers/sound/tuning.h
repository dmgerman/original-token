macro_line|#ifdef SEQUENCER_C
DECL|variable|semitone_tuning
r_int
r_int
id|semitone_tuning
(braket
l_int|24
)braket
op_assign
(brace
multiline_comment|/*   0 */
l_int|10000
comma
l_int|10595
comma
l_int|11225
comma
l_int|11892
comma
l_int|12599
comma
l_int|13348
comma
l_int|14142
comma
l_int|14983
comma
multiline_comment|/*   8 */
l_int|15874
comma
l_int|16818
comma
l_int|17818
comma
l_int|18877
comma
l_int|20000
comma
l_int|21189
comma
l_int|22449
comma
l_int|23784
comma
multiline_comment|/*  16 */
l_int|25198
comma
l_int|26697
comma
l_int|28284
comma
l_int|29966
comma
l_int|31748
comma
l_int|33636
comma
l_int|35636
comma
l_int|37755
)brace
suffix:semicolon
DECL|variable|cent_tuning
r_int
r_int
id|cent_tuning
(braket
l_int|100
)braket
op_assign
(brace
multiline_comment|/*   0 */
l_int|10000
comma
l_int|10006
comma
l_int|10012
comma
l_int|10017
comma
l_int|10023
comma
l_int|10029
comma
l_int|10035
comma
l_int|10041
comma
multiline_comment|/*   8 */
l_int|10046
comma
l_int|10052
comma
l_int|10058
comma
l_int|10064
comma
l_int|10070
comma
l_int|10075
comma
l_int|10081
comma
l_int|10087
comma
multiline_comment|/*  16 */
l_int|10093
comma
l_int|10099
comma
l_int|10105
comma
l_int|10110
comma
l_int|10116
comma
l_int|10122
comma
l_int|10128
comma
l_int|10134
comma
multiline_comment|/*  24 */
l_int|10140
comma
l_int|10145
comma
l_int|10151
comma
l_int|10157
comma
l_int|10163
comma
l_int|10169
comma
l_int|10175
comma
l_int|10181
comma
multiline_comment|/*  32 */
l_int|10187
comma
l_int|10192
comma
l_int|10198
comma
l_int|10204
comma
l_int|10210
comma
l_int|10216
comma
l_int|10222
comma
l_int|10228
comma
multiline_comment|/*  40 */
l_int|10234
comma
l_int|10240
comma
l_int|10246
comma
l_int|10251
comma
l_int|10257
comma
l_int|10263
comma
l_int|10269
comma
l_int|10275
comma
multiline_comment|/*  48 */
l_int|10281
comma
l_int|10287
comma
l_int|10293
comma
l_int|10299
comma
l_int|10305
comma
l_int|10311
comma
l_int|10317
comma
l_int|10323
comma
multiline_comment|/*  56 */
l_int|10329
comma
l_int|10335
comma
l_int|10341
comma
l_int|10347
comma
l_int|10353
comma
l_int|10359
comma
l_int|10365
comma
l_int|10371
comma
multiline_comment|/*  64 */
l_int|10377
comma
l_int|10383
comma
l_int|10389
comma
l_int|10395
comma
l_int|10401
comma
l_int|10407
comma
l_int|10413
comma
l_int|10419
comma
multiline_comment|/*  72 */
l_int|10425
comma
l_int|10431
comma
l_int|10437
comma
l_int|10443
comma
l_int|10449
comma
l_int|10455
comma
l_int|10461
comma
l_int|10467
comma
multiline_comment|/*  80 */
l_int|10473
comma
l_int|10479
comma
l_int|10485
comma
l_int|10491
comma
l_int|10497
comma
l_int|10503
comma
l_int|10509
comma
l_int|10515
comma
multiline_comment|/*  88 */
l_int|10521
comma
l_int|10528
comma
l_int|10534
comma
l_int|10540
comma
l_int|10546
comma
l_int|10552
comma
l_int|10558
comma
l_int|10564
comma
multiline_comment|/*  96 */
l_int|10570
comma
l_int|10576
comma
l_int|10582
comma
l_int|10589
)brace
suffix:semicolon
macro_line|#else
r_extern
r_int
r_int
id|semitone_tuning
(braket
l_int|24
)braket
suffix:semicolon
r_extern
r_int
r_int
id|cent_tuning
(braket
l_int|100
)braket
suffix:semicolon
macro_line|#endif
eof