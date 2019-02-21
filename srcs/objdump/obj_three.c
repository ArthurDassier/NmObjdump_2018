/*
** EPITECH PROJECT, 2019
** obj_three
** File description:
** obj_three
*/

#include "objdump.h"

static char *add_flags(Elf32_Ehdr *elf)
{
    char *str = calloc(10, 100);

    if (elf->e_type == ET_EXEC)
        str = strcat(str, "EXEC_P, D_PAGED");
    if (elf->e_type == ET_DYN)
        str = strcat(str, "DYNAMIC, D_PAGED");
    if (elf->e_type == ET_REL)
        str = strcat(str, ", HAS_RELOC");
    return (str);
}

static int format_three(char *filename, char *binary_name, Elf32_Ehdr *elf)
{
    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
        binary_name, filename);
        return (1);
    }
    printf("\n%s:     file format elf32-i386\n", filename);
    printf("architecture: i386:x86-32, flags 0x%08x:\n", elf->e_flags);
    printf("%s\n", add_flags(elf));
    printf("start address 0x%016x\n\n", (unsigned int)elf->e_entry);
    return (0);
}

int get_section_three(void *data, char *binary_name, char *filename)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)(data);
    Elf32_Shdr *shdr = (Elf32_Shdr *)(data + elf->e_shoff);
    char *tab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
    int code = format_three(filename, binary_name, elf);

    if (code != 0)
        return (code);
    for (int counter = 0; counter < elf->e_shnum; ++counter) {
        if (shdr[counter].sh_size
        && strcmp(&tab[shdr[counter].sh_name], ".bss")
        && strcmp(&tab[shdr[counter].sh_name], ".symtab")
        && strcmp(&tab[shdr[counter].sh_name], ".strtab")
        && strcmp(&tab[shdr[counter].sh_name], ".shstrtab")
        && strcmp(&tab[shdr[counter].sh_name], "\0")) {
            printf("Contents of section %s:\n", &tab[shdr[counter].sh_name]);
            print_bytes_three(elf, &shdr[counter]);
        }
    }
    return (0);
}