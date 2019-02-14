/*
** EPITECH PROJECT, 2019
** print_type.c
** File description:
** print_type
*/

#include "nmobjdump.h"

int compare(Elf64_Sym sym, Elf64_Shdr *shdr, char *str, char *s)
{
    if (strcmp(&str[shdr[sym.st_shndx].sh_name], s) == 0)
        return (1);
    return (0);
}

static char found_type_part_four(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if (sym.st_shndx == SHN_ABS && c == 0)
        c = 'A';
    if (sym.st_shndx == SHN_COMMON && c == 0)
        c = 'C';
    if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 0)
        c = 'B';
    if (c == 0)
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return (c);
}

static char found_type_part_three(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 0)
        c = 'D';
    if (compare(sym, shdr, getter(NULL, 42), ".rodata") && c == 0)
        c = 'R';
    if (compare(sym, shdr, getter(NULL, 42), ".debug") && c == 0)
        c = 'N';
    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE && c == 0)
        c = 'u';
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
    && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT && c == 0) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    }
    return (found_type_part_four(sym, shdr, c));
}

static char found_type_part_two(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if ((compare(sym, shdr, getter(NULL, 42), ".fini_array")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'T';
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == SHF_ALLOC && c == 0)
        c = 'R';
    if ((compare(sym, shdr, getter(NULL, 42), ".eh_frame_hdr")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'R';
    if ((ELF64_ST_TYPE(sym.st_info) == STT_OBJECT
    || ELF64_ST_TYPE(sym.st_info) == STT_NOTYPE
    || compare(sym, shdr, getter(NULL, 42), ".data")
    || compare(sym, shdr, getter(NULL, 42), ".data1")) && c == 0)
        c = 'D';
    if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC && c == 0)
        c = 'D';
    return (found_type_part_three(sym, shdr, c));
}

char found_type_six(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char c = 0;

    if (compare(sym, shdr, getter(NULL, 42), ".bss"))
        c = 'B';
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && c == 0) {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    }
    if (sym.st_shndx == SHN_UNDEF && c == 0)
        c = 'U';
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS && c == 0
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    if ((compare(sym, shdr, getter(NULL, 42), ".text")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'T';
    if ((compare(sym, shdr, getter(NULL, 42), ".init_array")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'T';
    return (found_type_part_two(sym, shdr, c));
}