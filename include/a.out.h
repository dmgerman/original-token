macro_line|#ifndef _A_OUT_H
DECL|macro|_A_OUT_H
mdefine_line|#define _A_OUT_H
DECL|macro|__GNU_EXEC_MACROS__
mdefine_line|#define __GNU_EXEC_MACROS__
DECL|struct|exec
r_struct
id|exec
(brace
DECL|member|a_magic
r_int
r_int
id|a_magic
suffix:semicolon
multiline_comment|/* Use macros N_MAGIC, etc for access */
DECL|member|a_text
r_int
id|a_text
suffix:semicolon
multiline_comment|/* length of text, in bytes */
DECL|member|a_data
r_int
id|a_data
suffix:semicolon
multiline_comment|/* length of data, in bytes */
DECL|member|a_bss
r_int
id|a_bss
suffix:semicolon
multiline_comment|/* length of uninitialized data area for file, in bytes */
DECL|member|a_syms
r_int
id|a_syms
suffix:semicolon
multiline_comment|/* length of symbol table data in file, in bytes */
DECL|member|a_entry
r_int
id|a_entry
suffix:semicolon
multiline_comment|/* start address */
DECL|member|a_trsize
r_int
id|a_trsize
suffix:semicolon
multiline_comment|/* length of relocation info for text, in bytes */
DECL|member|a_drsize
r_int
id|a_drsize
suffix:semicolon
multiline_comment|/* length of relocation info for data, in bytes */
)brace
suffix:semicolon
macro_line|#ifndef N_MAGIC
DECL|macro|N_MAGIC
mdefine_line|#define N_MAGIC(exec) ((exec).a_magic)
macro_line|#endif
macro_line|#ifndef OMAGIC
multiline_comment|/* Code indicating object file or impure executable.  */
DECL|macro|OMAGIC
mdefine_line|#define OMAGIC 0407
multiline_comment|/* Code indicating pure executable.  */
DECL|macro|NMAGIC
mdefine_line|#define NMAGIC 0410
multiline_comment|/* Code indicating demand-paged executable.  */
DECL|macro|ZMAGIC
mdefine_line|#define ZMAGIC 0413
macro_line|#endif /* not OMAGIC */
macro_line|#ifndef N_BADMAG
DECL|macro|N_BADMAG
mdefine_line|#define N_BADMAG(x)&t;&t;&t;&t;&t;&bslash;&n; (N_MAGIC(x) != OMAGIC &amp;&amp; N_MAGIC(x) != NMAGIC&t;&t;&bslash;&n;  &amp;&amp; N_MAGIC(x) != ZMAGIC)
macro_line|#endif
DECL|macro|_N_BADMAG
mdefine_line|#define _N_BADMAG(x)&t;&t;&t;&t;&t;&bslash;&n; (N_MAGIC(x) != OMAGIC &amp;&amp; N_MAGIC(x) != NMAGIC&t;&t;&bslash;&n;  &amp;&amp; N_MAGIC(x) != ZMAGIC)
DECL|macro|_N_HDROFF
mdefine_line|#define _N_HDROFF(x) (SEGMENT_SIZE - sizeof (struct exec))
macro_line|#ifndef N_TXTOFF
DECL|macro|N_TXTOFF
mdefine_line|#define N_TXTOFF(x) &bslash;&n; (N_MAGIC(x) == ZMAGIC ? _N_HDROFF((x)) + sizeof (struct exec) : sizeof (struct exec))
macro_line|#endif
macro_line|#ifndef N_DATOFF
DECL|macro|N_DATOFF
mdefine_line|#define N_DATOFF(x) (N_TXTOFF(x) + (x).a_text)
macro_line|#endif
macro_line|#ifndef N_TRELOFF
DECL|macro|N_TRELOFF
mdefine_line|#define N_TRELOFF(x) (N_DATOFF(x) + (x).a_data)
macro_line|#endif
macro_line|#ifndef N_DRELOFF
DECL|macro|N_DRELOFF
mdefine_line|#define N_DRELOFF(x) (N_TRELOFF(x) + (x).a_trsize)
macro_line|#endif
macro_line|#ifndef N_SYMOFF
DECL|macro|N_SYMOFF
mdefine_line|#define N_SYMOFF(x) (N_DRELOFF(x) + (x).a_drsize)
macro_line|#endif
macro_line|#ifndef N_STROFF
DECL|macro|N_STROFF
mdefine_line|#define N_STROFF(x) (N_SYMOFF(x) + (x).a_syms)
macro_line|#endif
multiline_comment|/* Address of text segment in memory after it is loaded.  */
macro_line|#ifndef N_TXTADDR
DECL|macro|N_TXTADDR
mdefine_line|#define N_TXTADDR(x) 0
macro_line|#endif
multiline_comment|/* Address of data segment in memory after it is loaded.&n;   Note that it is up to you to define SEGMENT_SIZE&n;   on machines not listed here.  */
macro_line|#if defined(vax) || defined(hp300) || defined(pyr)
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE PAGE_SIZE
macro_line|#endif
macro_line|#ifdef&t;hp300
DECL|macro|PAGE_SIZE
mdefine_line|#define&t;PAGE_SIZE&t;4096
macro_line|#endif
macro_line|#ifdef&t;sony
DECL|macro|SEGMENT_SIZE
mdefine_line|#define&t;SEGMENT_SIZE&t;0x2000
macro_line|#endif&t;/* Sony.  */
macro_line|#ifdef is68k
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE 0x20000
macro_line|#endif
macro_line|#if defined(m68k) &amp;&amp; defined(PORTAR)
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE 0x400
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE PAGE_SIZE
macro_line|#endif
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE 4096
DECL|macro|SEGMENT_SIZE
mdefine_line|#define SEGMENT_SIZE 1024
DECL|macro|_N_SEGMENT_ROUND
mdefine_line|#define _N_SEGMENT_ROUND(x) (((x) + SEGMENT_SIZE - 1) &amp; ~(SEGMENT_SIZE - 1))
DECL|macro|_N_TXTENDADDR
mdefine_line|#define _N_TXTENDADDR(x) (N_TXTADDR(x)+(x).a_text)
macro_line|#ifndef N_DATADDR
DECL|macro|N_DATADDR
mdefine_line|#define N_DATADDR(x) &bslash;&n;    (N_MAGIC(x)==OMAGIC? (_N_TXTENDADDR(x)) &bslash;&n;     : (_N_SEGMENT_ROUND (_N_TXTENDADDR(x))))
macro_line|#endif
multiline_comment|/* Address of bss segment in memory after it is loaded.  */
macro_line|#ifndef N_BSSADDR
DECL|macro|N_BSSADDR
mdefine_line|#define N_BSSADDR(x) (N_DATADDR(x) + (x).a_data)
macro_line|#endif
macro_line|#ifndef N_NLIST_DECLARED
DECL|struct|nlist
r_struct
id|nlist
(brace
r_union
(brace
DECL|member|n_name
r_char
op_star
id|n_name
suffix:semicolon
DECL|member|n_next
r_struct
id|nlist
op_star
id|n_next
suffix:semicolon
DECL|member|n_strx
r_int
id|n_strx
suffix:semicolon
DECL|member|n_un
)brace
id|n_un
suffix:semicolon
DECL|member|n_type
r_int
r_char
id|n_type
suffix:semicolon
DECL|member|n_other
r_char
id|n_other
suffix:semicolon
DECL|member|n_desc
r_int
id|n_desc
suffix:semicolon
DECL|member|n_value
r_int
r_int
id|n_value
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifndef N_UNDF
DECL|macro|N_UNDF
mdefine_line|#define N_UNDF 0
macro_line|#endif
macro_line|#ifndef N_ABS
DECL|macro|N_ABS
mdefine_line|#define N_ABS 2
macro_line|#endif
macro_line|#ifndef N_TEXT
DECL|macro|N_TEXT
mdefine_line|#define N_TEXT 4
macro_line|#endif
macro_line|#ifndef N_DATA
DECL|macro|N_DATA
mdefine_line|#define N_DATA 6
macro_line|#endif
macro_line|#ifndef N_BSS
DECL|macro|N_BSS
mdefine_line|#define N_BSS 8
macro_line|#endif
macro_line|#ifndef N_COMM
DECL|macro|N_COMM
mdefine_line|#define N_COMM 18
macro_line|#endif
macro_line|#ifndef N_FN
DECL|macro|N_FN
mdefine_line|#define N_FN 15
macro_line|#endif
macro_line|#ifndef N_EXT
DECL|macro|N_EXT
mdefine_line|#define N_EXT 1
macro_line|#endif
macro_line|#ifndef N_TYPE
DECL|macro|N_TYPE
mdefine_line|#define N_TYPE 036
macro_line|#endif
macro_line|#ifndef N_STAB
DECL|macro|N_STAB
mdefine_line|#define N_STAB 0340
macro_line|#endif
multiline_comment|/* The following type indicates the definition of a symbol as being&n;   an indirect reference to another symbol.  The other symbol&n;   appears as an undefined reference, immediately following this symbol.&n;&n;   Indirection is asymmetrical.  The other symbol&squot;s value will be used&n;   to satisfy requests for the indirect symbol, but not vice versa.&n;   If the other symbol does not have a definition, libraries will&n;   be searched to find a definition.  */
DECL|macro|N_INDR
mdefine_line|#define N_INDR 0xa
multiline_comment|/* The following symbols refer to set elements.&n;   All the N_SET[ATDB] symbols with the same name form one set.&n;   Space is allocated for the set in the text section, and each set&n;   element&squot;s value is stored into one word of the space.&n;   The first word of the space is the length of the set (number of elements).&n;&n;   The address of the set is made into an N_SETV symbol&n;   whose name is the same as the name of the set.&n;   This symbol acts like a N_DATA global symbol&n;   in that it can satisfy undefined external references.  */
multiline_comment|/* These appear as input to LD, in a .o file.  */
DECL|macro|N_SETA
mdefine_line|#define&t;N_SETA&t;0x14&t;&t;/* Absolute set element symbol */
DECL|macro|N_SETT
mdefine_line|#define&t;N_SETT&t;0x16&t;&t;/* Text set element symbol */
DECL|macro|N_SETD
mdefine_line|#define&t;N_SETD&t;0x18&t;&t;/* Data set element symbol */
DECL|macro|N_SETB
mdefine_line|#define&t;N_SETB&t;0x1A&t;&t;/* Bss set element symbol */
multiline_comment|/* This is output from LD.  */
DECL|macro|N_SETV
mdefine_line|#define N_SETV&t;0x1C&t;&t;/* Pointer to set vector in data area.  */
macro_line|#ifndef N_RELOCATION_INFO_DECLARED
multiline_comment|/* This structure describes a single relocation to be performed.&n;   The text-relocation section of the file is a vector of these structures,&n;   all of which apply to the text section.&n;   Likewise, the data-relocation section applies to the data section.  */
DECL|struct|relocation_info
r_struct
id|relocation_info
(brace
multiline_comment|/* Address (within segment) to be relocated.  */
DECL|member|r_address
r_int
id|r_address
suffix:semicolon
multiline_comment|/* The meaning of r_symbolnum depends on r_extern.  */
DECL|member|r_symbolnum
r_int
r_int
id|r_symbolnum
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Nonzero means value is a pc-relative offset&n;     and it should be relocated for changes in its own address&n;     as well as for changes in the symbol or section specified.  */
DECL|member|r_pcrel
r_int
r_int
id|r_pcrel
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Length (as exponent of 2) of the field to be relocated.&n;     Thus, a value of 2 indicates 1&lt;&lt;2 bytes.  */
DECL|member|r_length
r_int
r_int
id|r_length
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 1 =&gt; relocate with value of symbol.&n;          r_symbolnum is the index of the symbol&n;&t;  in file&squot;s the symbol table.&n;     0 =&gt; relocate with the address of a segment.&n;          r_symbolnum is N_TEXT, N_DATA, N_BSS or N_ABS&n;&t;  (the N_EXT bit may be set also, but signifies nothing).  */
DECL|member|r_extern
r_int
r_int
id|r_extern
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Four bits that aren&squot;t used, but when writing an object file&n;     it is desirable to clear them.  */
DECL|member|r_pad
r_int
r_int
id|r_pad
suffix:colon
l_int|4
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* no N_RELOCATION_INFO_DECLARED.  */
macro_line|#endif /* __A_OUT_GNU_H__ */
eof
