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

int main(int ac, char **av)
{
    int         fd;
    int         counter;
    int         filesize;
    void        *data;
    char        *strtab;
    Elf64_Ehdr  *elf;
    Elf64_Shdr  *shdr;

    counter = 0;
    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("open : ");
        return (EXIT_FAILURE);
    }
    filesize = lseek(fd, 0, SEEK_END);
    data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if (data != NULL) {
        elf = (Elf64_Ehdr *)(data);
        shdr = (Elf64_Shdr *)(data + elf->e_shoff);
        strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
        while(counter < elf->e_shnum) {
            printf("%s\n", &strtab[shdr[counter].sh_name]);
            ++counter;
        }
        return (EXIT_SUCCESS);
    }
    perror("mmap :");
    return (EXIT_FAILURE);
}