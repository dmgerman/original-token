multiline_comment|/*&n; * mediabay.h: definitions for using the media bay&n; * on PowerBook 3400 and similar computers.&n; *&n; * Copyright (C) 1997 Paul Mackerras.&n; */
macro_line|#ifndef _PPC_MEDIABAY_H
DECL|macro|_PPC_MEDIABAY_H
mdefine_line|#define _PPC_MEDIABAY_H
DECL|macro|MB_FD
mdefine_line|#define MB_FD&t;0&t;&t;/* media bay contains floppy drive */
DECL|macro|MB_CD
mdefine_line|#define MB_CD&t;3&t;&t;/* media bay contains ATA drive such as CD */
DECL|macro|MB_NO
mdefine_line|#define MB_NO&t;7&t;&t;/* media bay contains nothing */
macro_line|#ifdef __KERNEL__
r_void
id|media_bay_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|check_media_bay
c_func
(paren
r_int
id|what
)paren
suffix:semicolon
r_int
id|media_bay_task
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|media_bay_present
suffix:semicolon
multiline_comment|/* 1 if this machine has a media bay */
multiline_comment|/*&n; * The following give information about the IDE interface&n; * of the media bay: the base virtual address and IRQ number,&n; * and the index that the IDE driver has assigned to it&n; * (or -1 if it is not currently registered with the driver).&n; */
r_extern
r_int
r_int
id|mb_cd_base
suffix:semicolon
r_extern
r_int
id|mb_cd_irq
suffix:semicolon
r_extern
r_int
id|mb_cd_index
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PPC_MEDIABAY_H */
eof
