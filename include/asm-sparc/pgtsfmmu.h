multiline_comment|/* pgtsfmmu.h:  Spitfire V9 MMU support goes here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PGTSFMMU_H
DECL|macro|_SPARC_PGTSFMMU_H
mdefine_line|#define _SPARC_PGTSFMMU_H
multiline_comment|/* Spitfire is four-level.... I think... It also has a seperate TLB for&n; * data and instruction mappings.&n; */
DECL|macro|SFMMU_PMD_SHIFT
mdefine_line|#define SFMMU_PMD_SHIFT       16
DECL|macro|SFMMU_PMD_SIZE
mdefine_line|#define SFMMU_PMD_SIZE        (1UL &lt;&lt; SFMMU_PMD_SHIFT)
DECL|macro|SFMMU_PMD_MASK
mdefine_line|#define SFMMU_PMD_MASK        (~(SFMMU_PMD_SIZE-1))
DECL|macro|SFMMU_PMD_ALIGN
mdefine_line|#define SFMMU_PMD_ALIGN(addr) (((addr)+SFMMU_PMD_SIZE-1)&amp;SFMMU_PMD_MASK)
DECL|macro|SFMMU_PGDIR_SHIFT
mdefine_line|#define SFMMU_PGDIR_SHIFT     19
DECL|macro|SFMMU_PGDIR_SIZE
mdefine_line|#define SFMMU_PGDIR_SIZE        (1UL &lt;&lt; SFMMU_PGDIR_SHIFT)
DECL|macro|SFMMU_PGDIR_MASK
mdefine_line|#define SFMMU_PGDIR_MASK        (~(SFMMU_PGDIR_SIZE-1))
DECL|macro|SFMMU_PGDIR_ALIGN
mdefine_line|#define SFMMU_PGDIR_ALIGN(addr) (((addr)+SFMMU_PGDIR_SIZE-1)&amp;SFMMU_PGDIR_MASK)
DECL|macro|SFMMU_PGMAP_SHIFT
mdefine_line|#define SFMMU_PGMAP_SHIFT     22
DECL|macro|SFMMU_PGDIR_SIZE
mdefine_line|#define SFMMU_PGDIR_SIZE        (1UL &lt;&lt; SFMMU_PGDIR_SHIFT)
DECL|macro|SFMMU_PGDIR_MASK
mdefine_line|#define SFMMU_PGDIR_MASK        (~(SFMMU_PGDIR_SIZE-1))
DECL|macro|SFMMU_PGDIR_ALIGN
mdefine_line|#define SFMMU_PGDIR_ALIGN(addr) (((addr)+SFMMU_PGDIR_SIZE-1)&amp;SFMMU_PGDIR_MASK)
macro_line|#endif /* !(_SPARC_PGTSFMMU_H) */
eof
