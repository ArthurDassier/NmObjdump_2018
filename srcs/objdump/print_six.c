/*
** EPITECH PROJECT, 2019
** dump_six.c
** File description:
** six
*/

#include "objdump.h"

static char *add_flags(Elf64_Ehdr *elf)
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

int format(char *filename, char *binary_name, Elf64_Ehdr *elf)
{
    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
        binary_name, filename);
        return (1);
    }
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", elf->e_flags);
    printf("%s\n", add_flags(elf));
    printf("start address 0x%016x\n\n", (unsigned int)elf->e_entry);
    return (0);
}

static void print_begin(Elf64_Addr var, Elf64_Shdr *shdr, unsigned char *byte)
{
    printf(" %04lx ", var);
    for (size_t i = 0; i < 16; ++i) {
        if (i < shdr->sh_size)
            printf("%02x", byte[i]);
        else
            printf("%2s", "");
        if ((i + 1) % 4 == 0)
            printf (" ");
    }
    printf (" ");
}

static void print_during(Elf64_Shdr *shdr, unsigned char *byte, size_t i)
{
    for (size_t j = (i + 1); j < (i + 17); ++j) {
        if (j < shdr->sh_size)
            printf("%02x", byte[j]);
        else
            printf("%2s", "");
        if ((j + 1) % 4 == 0)
            printf (" ");
    }
    printf (" ");
}

void print_bytes(Elf64_Ehdr *elf, Elf64_Shdr *shdr)
{
    Elf64_Addr var = shdr->sh_addr;
    unsigned char *byte = (unsigned char *)((char *)elf + shdr->sh_offset);

    print_begin(var, shdr, byte);
    for (size_t i = 0; i < shdr->sh_size; ++i) {
        if (isprint(byte[i]))
            printf("%c", byte[i]);
        else
            printf(".");
        if ((i + 1) % 16 == 0 && (i + 1) < shdr->sh_size) {
            printf("\n");
            var += 16;
            printf(" %04lx ", var);
            print_during(shdr, byte, i);
        }
    }
    printf("\n");
}