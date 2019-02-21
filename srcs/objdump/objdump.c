/*
** EPITECH PROJECT, 2019
** objdump.c
** File description:
** objdump
*/

#include "objdump.h"

int get_section(char *filename, char *binary_name, void *data, Elf64_Ehdr *elf)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *)(data + elf->e_shoff);
    char *tab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
    int code = format(filename, binary_name, elf);

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
            print_bytes(elf, &shdr[counter]);
        }
    }
    return (0);
}

static int open_files_part_two(char *filename, char *binary_name,
void *data)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)(data);

    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
        binary_name, filename);
        return (1);
    }
    if (elf->e_ident[4] == 2)
        return (get_section(filename, binary_name, data, elf));
    else
        return (get_section_three(data, binary_name, filename));
}

int open_files(char *filename, char *binary_name, void *data, int fd)
{
    int code = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: '%s': No such file\n", binary_name, filename);
        return (1);
    }
    data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    if (data == NULL)
        return (84);
    if (data == (void *) -1) {
        fprintf(stderr, "%s: Warning: '%s' is a directory\n",
        binary_name, filename);
        close(fd);
        return (1);
    }
    code = open_files_part_two(filename, binary_name, data);
    close(fd);
    return (code);
}

int main(int ac , char **av)
{
    int code = 0;

    if (ac == 1)
        return (open_files("a.out", av[0], NULL, 0));
    for (int i = 1; i < ac; ++i)
        code = open_files(av[i], av[0], NULL, 0);
    return (code);
}