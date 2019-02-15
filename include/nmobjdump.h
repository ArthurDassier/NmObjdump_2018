/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** mes_prototypes
*/

#ifndef NMOBJDUMP_H_
    #define NMOBJDUMP_H_

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

typedef struct chainlist chainlist;

struct chainlist
{
    int adress;
    char type;
    char *name;
    chainlist *next;
};

int open_files(char *, char *);

char found_type_six(Elf64_Sym, Elf64_Shdr *);
char found_type_three(Elf32_Sym, Elf32_Shdr *);

int get_section_three(void *, Elf32_Shdr *, Elf32_Shdr *, Elf32_Sym *);
int check_elf(Elf64_Ehdr *, void *);

chainlist *init(int, char, char *);
void insert_end(chainlist **, int, char, char *);
void insert_end(chainlist **, int, char, char *);

int my_strcmp(char const *, char const *, int, int);

int is_sup(chainlist *);
void pb(chainlist **, chainlist **);

void sa(chainlist **);
void ra(chainlist **);
void pa(chainlist **, chainlist **);
int recup(chainlist *);

void print_me_that(chainlist *);
void sort_and_print(chainlist *);

char *getter(char *, int);

#endif
