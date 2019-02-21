/*
** EPITECH PROJECT, 2019
** print_three
** File description:
** print_three
*/

#include "objdump.h"

static void print_begin_three(Elf32_Addr var, Elf32_Shdr *shdr,
unsigned char *byte)
{
    printf(" %04x ", var);
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

static void print_during_three(Elf32_Shdr *shdr,
unsigned char *byte, size_t i)
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

void print_bytes_three(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    Elf32_Addr var = shdr->sh_addr;
    unsigned char *byte = (unsigned char *)((char *)elf + shdr->sh_offset);

    print_begin_three(var, shdr, byte);
    for (size_t i = 0; i < shdr->sh_size; ++i) {
        if (isprint(byte[i]))
            printf("%c", byte[i]);
        else
            printf(".");
        if ((i + 1) % 16 == 0 && (i + 1) < shdr->sh_size) {
            printf("\n");
            var += 16;
            printf(" %04x ", var);
            print_during_three(shdr, byte, i);
        }
    }
    printf("\n");
}