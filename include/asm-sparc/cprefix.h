multiline_comment|/* cprefix.h:  This file is included by assembly source which needs&n; *             to know what the c-label prefixes are. The newer versions&n; *&t;       of cpp that come with gcc predefine such things to help&n; *&t;       us out. The reason this stuff is needed is to make&n; *&t;       solaris compiles of the kernel work.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __svr4__
DECL|macro|C_LABEL_PREFIX
mdefine_line|#define C_LABEL_PREFIX _
macro_line|#else
DECL|macro|C_LABEL_PREFIX
mdefine_line|#define C_LABEL_PREFIX
macro_line|#endif
DECL|macro|CONCAT1
mdefine_line|#define CONCAT1(a, b) CONCAT2(a, b)
DECL|macro|CONCAT2
mdefine_line|#define CONCAT2(a, b) a##b
DECL|macro|C_LABEL
mdefine_line|#define C_LABEL(name) CONCAT1(C_LABEL_PREFIX, name)
eof
