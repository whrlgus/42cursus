#ifndef main_h
#define main_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# include <fcntl.h>

#include "/Users/gihyun/github/42cursus/Libft/libft.h"
void t_memset(size_t n);
void t_bzero(size_t n);
void t_memcpy(size_t n);
void t_memccpy(void);
void t_memmove(void);
void t_memchr(void);
void t_memcmp(void);
void t_strlen(void);
void t_strlcpy(void);
void t_strlcat(void);
void t_strchr(void);
void t_strrchr(void);
void t_strnstr(void);
void t_strncmp(void);
void t_atoi(void);
void t_isalpha(void);
void t_isdigit(void);
void t_isalnum(void);
void t_isascii(void);
void t_isprint(void);
void t_toupper(void);
void t_tolower(void);
void t_calloc(void);
void t_strdup(void);

void t_substr(void);
void t_strjoin(void);
void t_strtrim(void);
void t_split(void);
void t_itoa(void);
void t_strmapi(void);
void t_putchar_fd(void);
void t_putstr_fd(void);
void t_putendl_fd(void);
void t_putnbr_fd(void);

void t_bonus(void);

void init(void);
void print(char *arr,int size);
void display(int size);
#endif 

