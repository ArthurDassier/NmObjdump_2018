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

void print_begin(Elf64_Addr, Elf64_Shdr *, unsigned char *);
void print_during(Elf64_Shdr *, unsigned char *, size_t);
void print_bytes(Elf64_Ehdr *, Elf64_Shdr *);

#endif /* !OBJDUMP_H_ */
