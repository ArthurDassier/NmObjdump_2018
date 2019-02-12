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

static char found_type_part_two(Elf64_Sym sym, Elf64_Shdr *shdr, char c)
{
    if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        c = 'R';
    else if (c == 0)
        c = '?';
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
        c += 32;
    return (c);
}

char found_type64(Elf64_Sym sym, Elf64_Shdr *shdr, char *str)
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
    else if (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT
    || ELF64_ST_TYPE(sym.st_info) == STT_NOTYPE
    || compare(sym, shdr, getter(NULL, 42), ".data")
    || compare(sym, shdr, getter(NULL, 42), ".data1"))
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        c = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
    && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        c = 'D';
    else if (compare(sym, shdr, getter(NULL, 42), ".rodata"))
        c = 'R';
    else if (compare(sym, shdr, getter(NULL, 42), ".debug"))
        c = 'N';
    else if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        c = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
    && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        c = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            c = 'v';
    } else if (sym.st_shndx == SHN_ABS)
        c = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        c = 'C';
    return (found_type_part_two(sym, shdr, c));
}