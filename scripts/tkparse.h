DECL|enum|token
r_enum
id|token
(brace
DECL|enumerator|tok_menuname
id|tok_menuname
comma
DECL|enumerator|tok_menuoption
id|tok_menuoption
comma
DECL|enumerator|tok_comment
id|tok_comment
comma
DECL|enumerator|tok_bool
id|tok_bool
comma
DECL|enumerator|tok_tristate
id|tok_tristate
comma
DECL|enumerator|tok_dep_tristate
id|tok_dep_tristate
comma
DECL|enumerator|tok_nop
id|tok_nop
comma
DECL|enumerator|tok_if
id|tok_if
comma
DECL|enumerator|tok_else
id|tok_else
comma
DECL|enumerator|tok_fi
id|tok_fi
comma
DECL|enumerator|tok_int
id|tok_int
comma
DECL|enumerator|tok_sound
id|tok_sound
comma
DECL|enumerator|tok_define
id|tok_define
comma
DECL|enumerator|tok_choose
id|tok_choose
comma
DECL|enumerator|tok_choice
id|tok_choice
comma
DECL|enumerator|tok_unknown
id|tok_unknown
)brace
suffix:semicolon
DECL|enum|operator
r_enum
r_operator
(brace
DECL|enumerator|op_eq
id|op_eq
comma
DECL|enumerator|op_neq
id|op_neq
comma
DECL|enumerator|op_and
id|op_and
comma
DECL|enumerator|op_and1
id|op_and1
comma
DECL|enumerator|op_or
id|op_or
comma
DECL|enumerator|op_bang
id|op_bang
comma
DECL|enumerator|op_lparen
id|op_lparen
comma
DECL|enumerator|op_rparen
id|op_rparen
comma
DECL|enumerator|op_variable
id|op_variable
comma
DECL|enumerator|op_kvariable
id|op_kvariable
comma
DECL|enumerator|op_shellcmd
id|op_shellcmd
comma
DECL|enumerator|op_constant
id|op_constant
comma
DECL|enumerator|op_nuked
id|op_nuked
)brace
suffix:semicolon
DECL|union|var
r_union
id|var
(brace
DECL|member|str
r_char
op_star
id|str
suffix:semicolon
DECL|member|cfg
r_struct
id|kconfig
op_star
id|cfg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|condition
r_struct
id|condition
(brace
DECL|member|next
r_struct
id|condition
op_star
id|next
suffix:semicolon
DECL|member|op
r_enum
r_operator
id|op
suffix:semicolon
DECL|member|variable
r_union
id|var
id|variable
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GLOBAL_WRITTEN
mdefine_line|#define GLOBAL_WRITTEN  1
DECL|macro|CFG_DUP
mdefine_line|#define CFG_DUP &t;2
DECL|macro|UNSAFE
mdefine_line|#define UNSAFE&t;&t;4
DECL|struct|kconfig
r_struct
id|kconfig
(brace
DECL|member|next
r_struct
id|kconfig
op_star
id|next
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|tok
r_enum
id|token
id|tok
suffix:semicolon
DECL|member|menu_number
r_char
id|menu_number
suffix:semicolon
DECL|member|menu_line
r_char
id|menu_line
suffix:semicolon
DECL|member|submenu_start
r_char
id|submenu_start
suffix:semicolon
DECL|member|submenu_end
r_char
id|submenu_end
suffix:semicolon
DECL|member|optionname
r_char
op_star
id|optionname
suffix:semicolon
DECL|member|label
r_char
op_star
id|label
suffix:semicolon
DECL|member|value
r_char
op_star
id|value
suffix:semicolon
DECL|member|choice_value
r_int
id|choice_value
suffix:semicolon
DECL|member|choice_label
r_struct
id|kconfig
op_star
id|choice_label
suffix:semicolon
DECL|member|depend
r_union
id|var
id|depend
suffix:semicolon
DECL|member|cond
r_struct
id|condition
op_star
id|cond
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|kconfig
op_star
id|config
suffix:semicolon
r_extern
r_struct
id|kconfig
op_star
id|clast
suffix:semicolon
r_extern
r_struct
id|kconfig
op_star
id|koption
suffix:semicolon
eof