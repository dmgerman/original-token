DECL|struct|hw_pci
r_struct
id|hw_pci
(brace
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|io_start
r_int
r_int
id|io_start
suffix:semicolon
DECL|member|mem_start
r_int
r_int
id|mem_start
suffix:semicolon
DECL|member|swizzle
id|u8
(paren
op_star
id|swizzle
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
suffix:semicolon
DECL|member|map_irq
r_int
(paren
op_star
id|map_irq
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
id|dc21285_init
c_func
(paren
r_void
)paren
suffix:semicolon
eof
