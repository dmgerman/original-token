multiline_comment|/* Flags for bug emulation. These occupy the top three bytes. */
DECL|macro|STICKY_TIMEOUTS
mdefine_line|#define STICKY_TIMEOUTS&t;&t;0x8000000
DECL|macro|WHOLE_SECONDS
mdefine_line|#define WHOLE_SECONDS&t;&t;0x4000000
multiline_comment|/* Personality types. These go in the low byte. */
DECL|macro|PER_MASK
mdefine_line|#define PER_MASK&t;&t;(0x00ff)
DECL|macro|PER_LINUX
mdefine_line|#define PER_LINUX&t;&t;(0x0000)
DECL|macro|PER_SVR4
mdefine_line|#define PER_SVR4&t;&t;(0x0001 | STICKY_TIMEOUTS)
DECL|macro|PER_SVR3
mdefine_line|#define PER_SVR3&t;&t;(0x0002 | STICKY_TIMEOUTS)
DECL|macro|PER_SCOSVR3
mdefine_line|#define PER_SCOSVR3&t;&t;(0x0003 | STICKY_TIMEOUTS | WHOLE_SECONDS)
DECL|macro|PER_WYSEV386
mdefine_line|#define PER_WYSEV386&t;&t;(0x0004 | STICKY_TIMEOUTS)
DECL|macro|PER_ISCR4
mdefine_line|#define PER_ISCR4&t;&t;(0x0005 | STICKY_TIMEOUTS)
eof
