DECL|struct|unicode_value
r_struct
id|unicode_value
(brace
DECL|member|uni1
r_int
r_char
id|uni1
suffix:semicolon
DECL|member|uni2
r_int
r_char
id|uni2
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
r_char
id|fat_a2alias
(braket
)braket
suffix:semicolon
multiline_comment|/* Ascii to alias name conversion table */
r_extern
r_struct
id|unicode_value
id|fat_a2uni
(braket
)braket
suffix:semicolon
multiline_comment|/* Ascii to Unicode conversion table */
r_extern
r_int
r_char
op_star
id|fat_uni2asc_pg
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Since Linux can&squot;t deal with Unicode in filenames, these provide&n; * a method to encode the Unicode names in a manner that the vfat&n; * filesystem can them decode back to Unicode.  This conversion&n; * only occurs when the filesystem was mounted with the &squot;uni_xlate&squot; mount&n; * option.&n; */
r_extern
r_int
r_char
id|fat_uni2code
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|fat_code2uni
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
