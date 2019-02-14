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

static char found_type_part_three(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if (compare(sym, shdr, getter(NULL, 42), ".debug") && c == 0)
        c = 'N';
    else if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE && c == 0)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
    && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT && c == 0) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    } else if (sym.st_shndx == SHN_ABS && c == 0)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON && c == 0)
        c = 'C';
    if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 0)
        c = 'B';
    else if (c == 0)
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return (c);
}

static char found_type_part_two(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if ((compare(sym, shdr, getter(NULL, 42), ".fini_array")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == SHF_ALLOC && c == 0)
        c = 'R';
    else if ((compare(sym, shdr, getter(NULL, 42), ".eh_frame_hdr")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC) && c == 0)
        c = 'R';
    else if ((ELF64_ST_TYPE(sym.st_info) == STT_OBJECT
    || ELF64_ST_TYPE(sym.st_info) == STT_NOTYPE
    || compare(sym, shdr, getter(NULL, 42), ".data")
    || compare(sym, shdr, getter(NULL, 42), ".data1")) && c == 0)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC && c == 0)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) && c == 0)
        c = 'D';
    else if (compare(sym, shdr, getter(NULL, 42), ".rodata") && c == 0)
        c = 'R';
    return (found_type_part_three(sym, shdr, c));
}

char found_type64(Elf64_Sym sym, Elf64_Shdr *shdr)
{
    char c = 0;

    if (compare(sym, shdr, getter(NULL, 42), ".bss"))
        c = 'B';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        c = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'w';
    } else if (sym.st_shndx == SHN_UNDEF)
        c = 'U';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        c = 'T';
    else if (compare(sym, shdr, getter(NULL, 42), ".text")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC)
        c = 'T';
    else if (compare(sym, shdr, getter(NULL, 42), ".init_array")
    || ELF64_ST_TYPE(sym.st_info) == STT_FUNC)
        c = 'T';
    return (found_type_part_two(sym, shdr, c));
}