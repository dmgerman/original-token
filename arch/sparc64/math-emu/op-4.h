multiline_comment|/*&n; * Basic four-word fraction declaration and manipulation.&n; */
DECL|macro|_FP_FRAC_DECL_4
mdefine_line|#define _FP_FRAC_DECL_4(X)&t;_FP_W_TYPE X##_f[4]
DECL|macro|_FP_FRAC_COPY_4
mdefine_line|#define _FP_FRAC_COPY_4(D,S)&t;&t;&t;&bslash;&n;  (D##_f[0] = S##_f[0], D##_f[1] = S##_f[1],&t;&bslash;&n;   D##_f[2] = S##_f[2], D##_f[3] = S##_f[3])
DECL|macro|_FP_FRAC_SET_4
mdefine_line|#define _FP_FRAC_SET_4(X,I)&t;__FP_FRAC_SET_4(X, I)
DECL|macro|_FP_FRAC_HIGH_4
mdefine_line|#define _FP_FRAC_HIGH_4(X)&t;(X##_f[3])
DECL|macro|_FP_FRAC_LOW_4
mdefine_line|#define _FP_FRAC_LOW_4(X)&t;(X##_f[0])
DECL|macro|_FP_FRAC_WORD_4
mdefine_line|#define _FP_FRAC_WORD_4(X,w)&t;(X##_f[w])
DECL|macro|_FP_FRAC_SLL_4
mdefine_line|#define _FP_FRAC_SLL_4(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = _FP_W_TYPE_SIZE - _up;&t;&t;&t;&t;&t;&bslash;&n;    for (_i = 3; _i &gt; _skip; --_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i-_skip] &lt;&lt; _up | X##_f[_i-_skip-1] &gt;&gt; _down;&t;&bslash;&n;    X##_f[_i] &lt;&lt;= _up;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    for (--_i; _i &gt;= 0; --_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_SRL_4
mdefine_line|#define _FP_FRAC_SRL_4(X,N)&t;&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = _FP_W_TYPE_SIZE - _down;&t;&t;&t;&t;&t;&bslash;&n;    for (_i = 0; _i &lt; 4-_skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i+_skip] &gt;&gt; _down | X##_f[_i+_skip+1] &lt;&lt; _up;&t;&bslash;&n;    X##_f[_i] &gt;&gt;= _down;&t;&t;&t;&t;&t;&t;&bslash;&n;    for (++_i; _i &lt; 4; ++_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
multiline_comment|/* Right shift with sticky-lsb.  */
DECL|macro|_FP_FRAC_SRS_4
mdefine_line|#define _FP_FRAC_SRS_4(X,N,size)&t;&t;&t;&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _FP_I_TYPE _up, _down, _skip, _i;&t;&t;&t;&t;&t;&bslash;&n;    _FP_W_TYPE _s;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _skip = (N) / _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _down = (N) % _FP_W_TYPE_SIZE;&t;&t;&t;&t;&t;&bslash;&n;    _up = _FP_W_TYPE_SIZE - _down;&t;&t;&t;&t;&t;&bslash;&n;    for (_s = _i = 0; _i &lt; _skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      _s |= X##_f[_i];&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    _s = X##_f[_i] &lt;&lt; _up;&t;&t;&t;&t;&t;&t;&bslash;&n;    X##_f[0] = X##_f[_skip] &gt;&gt; _down | X##_f[_skip+1] &lt;&lt; _up | (_s != 0); &bslash;&n;    for (_i = 1; _i &lt; 4-_skip; ++_i)&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = X##_f[_i+_skip] &gt;&gt; _down | X##_f[_i+_skip+1] &lt;&lt; _up;&t;&bslash;&n;    X##_f[_i] &gt;&gt;= _down;&t;&t;&t;&t;&t;&t;&bslash;&n;    for (++_i; _i &lt; 4; ++_i)&t;&t;&t;&t;&t;&t;&bslash;&n;      X##_f[_i] = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  } while (0)
DECL|macro|_FP_FRAC_ADD_4
mdefine_line|#define _FP_FRAC_ADD_4(R,X,Y)&t;&t;&t;&t;&t;&t;&bslash;&n;  __FP_FRAC_ADD_4(R##_f[3], R##_f[2], R##_f[1], R##_f[0],&t;&t;&bslash;&n;&t;&t;  X##_f[3], X##_f[2], X##_f[1], X##_f[0],&t;&t;&bslash;&n;&t;&t;  Y##_f[3], Y##_f[2], Y##_f[1], Y##_f[0])
multiline_comment|/*&n; * Internals &n; */
DECL|macro|__FP_FRAC_SET_4
mdefine_line|#define __FP_FRAC_SET_4(X,I3,I2,I1,I0)&t;&t;&t;&t;&t;&bslash;&n;  (X##_f[3] = I3, X##_f[2] = I2, X##_f[1] = I1, X##_f[0] = I0)
macro_line|#ifndef __FP_FRAC_ADD_4
DECL|macro|__FP_FRAC_ADD_4
mdefine_line|#define __FP_FRAC_ADD_4(r3,r2,r1,r0,x3,x2,x1,x0,y3,y2,y1,y0)&t;&t;&bslash;&n;  (r0 = x0 + y0,&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   r1 = x1 + y1 + (r0 &lt; x0),&t;&t;&t;&t;&t;&t;&bslash;&n;   r2 = x2 + y2 + (r1 &lt; x1),&t;&t;&t;&t;&t;&t;&bslash;&n;   r3 = x3 + y3 + (r2 &lt; x2))
macro_line|#endif
eof
