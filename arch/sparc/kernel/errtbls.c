multiline_comment|/* $Id: errtbls.c,v 1.2 1995/11/25 00:57:55 davem Exp $&n; * errtbls.c: Error number conversion tables between various syscall&n; *            OS semantics.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Based upon preliminary work which is:&n; *&n; * Copyright (C) 1995 Adrian M. Rodriguez (adrian@remus.rutgers.edu)&n; */
macro_line|#include &lt;asm/bsderrno.h&gt;        /* NetBSD (bsd4.4) errnos */
macro_line|#include &lt;asm/solerrno.h&gt;        /* Solaris errnos */
multiline_comment|/* Here are tables which convert between Linux/SunOS error number&n; * values to the equivalent in other OSs.  Note that since the Linux&n; * ones have been set up to match exactly those of SunOS, no&n; * translation table is needed for that OS.&n; */
DECL|variable|solaris_errno
r_int
id|solaris_errno
(braket
)braket
op_assign
(brace
l_int|0
comma
id|SOL_EPERM
comma
id|SOL_ENOENT
comma
id|SOL_ESRCH
comma
id|SOL_EINTR
comma
id|SOL_EIO
comma
id|SOL_ENXIO
comma
id|SOL_E2BIG
comma
id|SOL_ENOEXEC
comma
id|SOL_EBADF
comma
id|SOL_ECHILD
comma
id|SOL_EAGAIN
comma
id|SOL_ENOMEM
comma
id|SOL_EACCES
comma
id|SOL_EFAULT
comma
id|SOL_NOTBLK
comma
id|SOL_EBUSY
comma
id|SOL_EEXIST
comma
id|SOL_EXDEV
comma
id|SOL_ENODEV
comma
id|SOL_ENOTDIR
comma
id|SOL_EISDIR
comma
id|SOL_EINVAL
comma
id|SOL_ENFILE
comma
id|SOL_EMFILE
comma
id|SOL_ENOTTY
comma
id|SOL_ETXTBSY
comma
id|SOL_EFBIG
comma
id|SOL_ENOSPC
comma
id|SOL_ESPIPE
comma
id|SOL_EROFS
comma
id|SOL_EMLINK
comma
id|SOL_EPIPE
comma
id|SOL_EDOM
comma
id|SOL_ERANGE
comma
id|SOL_EWOULDBLOCK
comma
id|SOL_EINPROGRESS
comma
id|SOL_EALREADY
comma
id|SOL_ENOTSOCK
comma
id|SOL_EDESTADDRREQ
comma
id|SOL_EMSGSIZE
comma
id|SOL_EPROTOTYPE
comma
id|SOL_ENOPROTOOPT
comma
id|SOL_EPROTONOSUPPORT
comma
id|SOL_ESOCKTNOSUPPORT
comma
id|SOL_EOPNOTSUPP
comma
id|SOL_EPFNOSUPPORT
comma
id|SOL_EAFNOSUPPORT
comma
id|SOL_EADDRINUSE
comma
id|SOL_EADDRNOTAVAIL
comma
id|SOL_ENETDOWN
comma
id|SOL_ENETUNREACH
comma
id|SOL_ENETRESET
comma
id|SOL_ECONNABORTED
comma
id|SOL_ECONNRESET
comma
id|SOL_ENOBUFS
comma
id|SOL_EISCONN
comma
id|SOL_ENOTONN
comma
id|SOL_ESHUTDOWN
comma
id|SOL_ETOOMANYREFS
comma
id|SOL_ETIMEDOUT
comma
id|SOL_ECONNREFUSED
comma
id|SOL_ELOOP
comma
id|SOL_ENAMETOOLONG
comma
id|SOL_EHOSTDOWN
comma
id|SOL_EHOSTUNREACH
comma
id|SOL_ENOTEMPTY
comma
id|SOL_EPROCLIM
comma
id|SOL_EUSERS
comma
id|SOL_EDQUOT
comma
id|SOL_ESTALE
comma
id|SOL_EREMOTE
comma
id|SOL_ENOSTR
comma
id|SOL_ETIME
comma
id|SOL_ENOSR
comma
id|SOL_ENOMSG
comma
id|SOL_EBADMSG
comma
id|SOL_IDRM
comma
id|SOL_EDEADLK
comma
id|SOL_ENOLCK
comma
id|SOL_ENONET
comma
id|SOL_ERREMOTE
comma
id|SOL_ENOLINK
comma
id|SOL_EADV
comma
id|SOL_ESRMNT
comma
id|SOL_ECOMM
comma
id|SOL_EPROTO
comma
id|SOL_EMULTIHOP
comma
id|SOL_EINVAL
comma
multiline_comment|/* EDOTDOT XXX??? */
id|SOL_REMCHG
comma
id|SOL_NOSYS
comma
id|SOL_STRPIPE
comma
id|SOL_EOVERFLOW
comma
id|SOL_EBADFD
comma
id|SOL_ECHRNG
comma
id|SOL_EL2NSYNC
comma
id|SOL_EL3HLT
comma
id|SOL_EL3RST
comma
id|SOL_NRNG
comma
id|SOL_EUNATCH
comma
id|SOL_ENOCSI
comma
id|SOL_EL2HLT
comma
id|SOL_EBADE
comma
id|SOL_EBADR
comma
id|SOL_EXFULL
comma
id|SOL_ENOANO
comma
id|SOL_EBADRQC
comma
id|SOL_EBADSLT
comma
id|SOL_EDEADLOCK
comma
id|SOL_EBFONT
comma
id|SOL_ELIBEXEC
comma
id|SOL_ENODATA
comma
id|SOL_ELIBBAD
comma
id|SOL_ENOPKG
comma
id|SOL_ELIBACC
comma
id|SOL_ENOTUNIQ
comma
id|SOL_ERESTART
comma
id|SOL_EUCLEAN
comma
id|SOL_ENOTNAM
comma
id|SOL_ENAVAIL
comma
id|SOL_EISNAM
comma
id|SOL_EREMOTEIO
comma
id|SOL_EILSEQ
comma
id|SOL_ELIBMAX
comma
id|SOL_ELIBSCN
comma
)brace
suffix:semicolon
DECL|variable|netbsd_errno
r_int
id|netbsd_errno
(braket
)braket
op_assign
(brace
l_int|0
comma
id|BSD_EPERM
comma
id|BSD_ENOENT
comma
id|BSD_ESRCH
comma
id|BSD_EINTR
comma
id|BSD_EIO
comma
id|BSD_ENXIO
comma
id|BSD_E2BIG
comma
id|BSD_ENOEXEC
comma
id|BSD_EBADF
comma
id|BSD_ECHILD
comma
id|BSD_EAGAIN
comma
id|BSD_ENOMEM
comma
id|BSD_EACCES
comma
id|BSD_EFAULT
comma
id|BSD_NOTBLK
comma
id|BSD_EBUSY
comma
id|BSD_EEXIST
comma
id|BSD_EXDEV
comma
id|BSD_ENODEV
comma
id|BSD_ENOTDIR
comma
id|BSD_EISDIR
comma
id|BSD_EINVAL
comma
id|BSD_ENFILE
comma
id|BSD_EMFILE
comma
id|BSD_ENOTTY
comma
id|BSD_ETXTBSY
comma
id|BSD_EFBIG
comma
id|BSD_ENOSPC
comma
id|BSD_ESPIPE
comma
id|BSD_EROFS
comma
id|BSD_EMLINK
comma
id|BSD_EPIPE
comma
id|BSD_EDOM
comma
id|BSD_ERANGE
comma
id|BSD_EWOULDBLOCK
comma
id|BSD_EINPROGRESS
comma
id|BSD_EALREADY
comma
id|BSD_ENOTSOCK
comma
id|BSD_EDESTADDRREQ
comma
id|BSD_EMSGSIZE
comma
id|BSD_EPROTOTYPE
comma
id|BSD_ENOPROTOOPT
comma
id|BSD_EPROTONOSUPPORT
comma
id|BSD_ESOCKTNOSUPPORT
comma
id|BSD_EOPNOTSUPP
comma
id|BSD_EPFNOSUPPORT
comma
id|BSD_EAFNOSUPPORT
comma
id|BSD_EADDRINUSE
comma
id|BSD_EADDRNOTAVAIL
comma
id|BSD_ENETDOWN
comma
id|BSD_ENETUNREACH
comma
id|BSD_ENETRESET
comma
id|BSD_ECONNABORTED
comma
id|BSD_ECONNRESET
comma
id|BSD_ENOBUFS
comma
id|BSD_EISCONN
comma
id|BSD_ENOTONN
comma
id|BSD_ESHUTDOWN
comma
id|BSD_ETOOMANYREFS
comma
id|BSD_ETIMEDOUT
comma
id|BSD_ECONNREFUSED
comma
id|BSD_ELOOP
comma
id|BSD_ENAMETOOLONG
comma
id|BSD_EHOSTDOWN
comma
id|BSD_EHOSTUNREACH
comma
id|BSD_ENOTEMPTY
comma
id|BSD_EPROCLIM
comma
id|BSD_EUSERS
comma
id|BSD_EDQUOT
comma
id|BSD_ESTALE
comma
id|BSD_EREMOTE
comma
id|BSD_ENOSTR
comma
id|BSD_ETIME
comma
id|BSD_ENOSR
comma
id|BSD_ENOMSG
comma
id|BSD_EBADMSG
comma
id|BSD_IDRM
comma
id|BSD_EDEADLK
comma
id|BSD_ENOLCK
comma
id|BSD_ENONET
comma
id|BSD_ERREMOTE
comma
id|BSD_ENOLINK
comma
id|BSD_EADV
comma
id|BSD_ESRMNT
comma
id|BSD_ECOMM
comma
id|BSD_EPROTO
comma
id|BSD_EMULTIHOP
comma
id|BSD_EINVAL
comma
multiline_comment|/* EDOTDOT XXX??? */
id|BSD_REMCHG
comma
id|BSD_NOSYS
comma
id|BSD_STRPIPE
comma
id|BSD_EOVERFLOW
comma
id|BSD_EBADFD
comma
id|BSD_ECHRNG
comma
id|BSD_EL2NSYNC
comma
id|BSD_EL3HLT
comma
id|BSD_EL3RST
comma
id|BSD_NRNG
comma
id|BSD_EUNATCH
comma
id|BSD_ENOCSI
comma
id|BSD_EL2HLT
comma
id|BSD_EBADE
comma
id|BSD_EBADR
comma
id|BSD_EXFULL
comma
id|BSD_ENOANO
comma
id|BSD_EBADRQC
comma
id|BSD_EBADSLT
comma
id|BSD_EDEADLOCK
comma
id|BSD_EBFONT
comma
id|BSD_ELIBEXEC
comma
id|BSD_ENODATA
comma
id|BSD_ELIBBAD
comma
id|BSD_ENOPKG
comma
id|BSD_ELIBACC
comma
id|BSD_ENOTUNIQ
comma
id|BSD_ERESTART
comma
id|BSD_EUCLEAN
comma
id|BSD_ENOTNAM
comma
id|BSD_ENAVAIL
comma
id|BSD_EISNAM
comma
id|BSD_EREMOTEIO
comma
id|BSD_EILSEQ
comma
id|BSD_ELIBMAX
comma
id|BSD_ELIBSCN
comma
)brace
suffix:semicolon
eof
