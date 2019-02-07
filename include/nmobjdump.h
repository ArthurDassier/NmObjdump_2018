/*
** EPITECH PROJECT, 2018
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

char found_type(Elf64_Sym, Elf64_Shdr *);
chainlist *init(int, char, char *);
void insert_end(chainlist **, int, char, char *);
void insert_end(chainlist **, int, char, char *);

int my_strcmp(char const *, char const *);

int is_sup(chainlist *);
void pb(chainlist **, chainlist **);

void sa(chainlist **);
void ra(chainlist **);
void pa(chainlist **, chainlist **);
int recup(chainlist *);

chainlist *brain(chainlist *);

#endif
