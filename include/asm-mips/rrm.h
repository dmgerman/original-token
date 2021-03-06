multiline_comment|/*&n; * SGI Rendering Resource Manager API (?).&n; *&n; * written by Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *&n; * Ok, even if SGI choosed to do mmap trough ioctls, their&n; * kernel support for virtualizing the graphics card is nice.&n; *&n; * We should be able to make graphic applications on Linux&n; * fly.&n; *&n; * This header file should be included from GNU libc as well.&n; */
multiline_comment|/* Why like this you say?  Well, gdb can print enums */
DECL|macro|RRM_BASE
mdefine_line|#define RRM_BASE 1000
DECL|macro|RRM_CMD_LIMIT
mdefine_line|#define RRM_CMD_LIMIT (RRM_BASE + 100)
r_enum
(brace
DECL|enumerator|RRM_OPENRN
id|RRM_OPENRN
op_assign
id|RRM_BASE
comma
multiline_comment|/* open rendering node */
DECL|enumerator|RRM_CLOSERN
id|RRM_CLOSERN
comma
DECL|enumerator|RRM_BINDPROCTORN
id|RRM_BINDPROCTORN
comma
multiline_comment|/* set current rendering region for node */
DECL|enumerator|RRM_BINDRNTOCLIP
id|RRM_BINDRNTOCLIP
comma
DECL|enumerator|RRM_UNBINDRNFROMCLIP
id|RRM_UNBINDRNFROMCLIP
comma
DECL|enumerator|RRM_SWAPBUF
id|RRM_SWAPBUF
comma
DECL|enumerator|RRM_SETSWAPINTERVAL
id|RRM_SETSWAPINTERVAL
comma
DECL|enumerator|RRM_WAITFORRETRACE
id|RRM_WAITFORRETRACE
comma
DECL|enumerator|RRM_SETDISPLAYMODE
id|RRM_SETDISPLAYMODE
comma
DECL|enumerator|RRM_MESSAGE
id|RRM_MESSAGE
comma
DECL|enumerator|RRM_INVALIDATERN
id|RRM_INVALIDATERN
comma
DECL|enumerator|RRM_VALIDATECLIP
id|RRM_VALIDATECLIP
comma
DECL|enumerator|RRM_VALIDATESWAPBUF
id|RRM_VALIDATESWAPBUF
comma
DECL|enumerator|RRM_SWAPGROUP
id|RRM_SWAPGROUP
comma
DECL|enumerator|RRM_SWAPUNGROUP
id|RRM_SWAPUNGROUP
comma
DECL|enumerator|RRM_VALIDATEMESSAGE
id|RRM_VALIDATEMESSAGE
comma
DECL|enumerator|RRM_GETDISPLAYMODES
id|RRM_GETDISPLAYMODES
comma
DECL|enumerator|RRM_LOADDISPLAYMODE
id|RRM_LOADDISPLAYMODE
comma
DECL|enumerator|RRM_CUSHIONBUFFER
id|RRM_CUSHIONBUFFER
comma
DECL|enumerator|RRM_SWAPREADY
id|RRM_SWAPREADY
comma
DECL|enumerator|RRM_MGR_SWAPBUF
id|RRM_MGR_SWAPBUF
comma
DECL|enumerator|RRM_SETVSYNC
id|RRM_SETVSYNC
comma
DECL|enumerator|RRM_GETVSYNC
id|RRM_GETVSYNC
comma
DECL|enumerator|RRM_WAITVSYNC
id|RRM_WAITVSYNC
comma
DECL|enumerator|RRM_BINDRNTOREADANDCLIP
id|RRM_BINDRNTOREADANDCLIP
comma
DECL|enumerator|RRM_MAPCLIPTOSWPBUFID
id|RRM_MAPCLIPTOSWPBUFID
)brace
suffix:semicolon
multiline_comment|/* Parameters for the above ioctls&n; *&n; * All of the ioctls take as their first argument the rendering node id.&n; *&n; */
multiline_comment|/*&n; * RRM_OPENRN:&n; *&n; * This is called by the IRIX X server with:&n; * rnid = 0xffffffff rmask = 0&n; *&n; * Returns a number like this: 0x10001.&n; * If you run the X server over and over, you get a value&n; * that is of the form (n * 0x10000) + 1.&n; *&n; * The return value seems to be the RNID.&n; */
DECL|struct|RRM_OpenRN
r_struct
id|RRM_OpenRN
(brace
DECL|member|rnid
r_int
id|rnid
suffix:semicolon
DECL|member|rmask
r_int
r_int
id|rmask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RRM_CloseRN
r_struct
id|RRM_CloseRN
(brace
DECL|member|rnid
r_int
id|rnid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * RRM_BINDPROCTORN:&n; *&n; * Return value when the X server calls it: 0&n; */
DECL|struct|RRM_BindProcToRN
r_struct
id|RRM_BindProcToRN
(brace
DECL|member|rnid
r_int
id|rnid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_int
id|rrm_command
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|rrm_close
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
macro_line|#endif
eof
