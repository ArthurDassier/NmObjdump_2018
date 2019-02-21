/*
** EPITECH PROJECT, 2019
** dump_six.c
** File description:
** six
*/

#include "objdump.h"

void print_begin(Elf64_Addr var, Elf64_Shdr *shdr, unsigned char *byte)
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

void print_during(Elf64_Shdr *shdr, unsigned char *byte, size_t i)
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