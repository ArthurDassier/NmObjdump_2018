/*
** EPITECH PROJECT, 2019
** objdump.h
** File description:
** dump
*/

#ifndef OBJDUMP_H_
	#define OBJDUMP_H_

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
#include <ctype.h>

void print_bytes(Elf64_Ehdr *, Elf64_Shdr *);
int format(char *, char *, Elf64_Ehdr *);

void print_bytes_three(Elf32_Ehdr *, Elf32_Shdr *);
int get_section_three(void *, char *, char *);

#endif /* !OBJDUMP_H_ */
