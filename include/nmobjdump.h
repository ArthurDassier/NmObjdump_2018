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

char print_type(Elf64_Sym, Elf64_Shdr *);

#endif
