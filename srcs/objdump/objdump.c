/*
** EPITECH PROJECT, 2019
** objdump.c
** File description:
** objdump
*/

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

char *add_flags(Elf64_Ehdr *elf)
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

void get_section(void *data, char *filename)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    char *strtab;
    int counter = 0;

    elf = (Elf64_Ehdr *)(data);
    shdr = (Elf64_Shdr *)(data + elf->e_shoff);
    strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
    if (elf->e_ident[0] != ELFMAG0 || elf->e_ident[1] != ELFMAG1
    || elf->e_ident[2] != ELFMAG2 || elf->e_ident[3] != ELFMAG3)
        exit(84);
    if (elf->e_ident[4] == 2)
        printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", elf->e_flags);
    printf("%s\n", add_flags(elf));
    printf("start address 0x%016x\n\n", (unsigned int)elf->e_entry);
    // while(counter < elf->e_shnum) {
    //     if (strcmp(&strtab[shdr[counter].sh_name], ".bss")
    //     && strcmp(&strtab[shdr[counter].sh_name], ".symtab")
    //     && strcmp(&strtab[shdr[counter].sh_name], ".strtab")
    //     && strcmp(&strtab[shdr[counter].sh_name], ".shstrtab")
    //     && strcmp(&strtab[shdr[counter].sh_name], "\0"))
    //         printf("%s\n", &strtab[shdr[counter].sh_name]);
    //     ++counter;
    // }
}

int open_files(char *filename)
{
    void *data = NULL;
    int fd = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (84);
    data = mmap(NULL, lseek(fd, 0, SEEK_END), PROT_READ, MAP_SHARED, fd, 0);
    if (data == NULL) {
        close(fd);
        return (84);
    }
    get_section(data, filename);
    close(fd);
    return (0);
}

int main(int ac , char **av)
{
    if (ac == 1)
        return (open_files("a.out"));
    for (int i = 1; i < ac; ++i) {
        if (open_files(av[i]) == 84)
            return (84);
    }
    return (0);
}