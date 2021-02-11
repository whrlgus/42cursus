#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libasm.h"

void strcmp_check(const char *a, const char *b) {
	printf("%d %d\n",ft_strcmp(a,b), strcmp(a,b));
	printf("%s %s\n",a, b);
}

void strcpy_check(char *c) {
	int len = strlen(c) + 1;
	char *a = (char*)malloc(len);
	char *b = (char*)malloc(len);

	printf("%s %s\n",ft_strcpy(a, c), strcpy(b, c));
	printf("%s %s\n",a, b);
}

void strdup_check(char *c) {
	char *a = ft_strdup(c);
	char *b = strdup(c);
	printf("%s %s\n", a, b);
}

int main() {
	// ft_write(1, "gicho", 6);
	// printf("%d",ft_strlen("hello world"));
	// printf("%s", ft_strcpy("hello", "world"));


	// strcmp_check("aaa","aa");
	// strcmp_check("aa","aa");
	// strcmp_check("aba","aa");
	// strcmp_check("aaa","aab");

	// strcpy_check("hello");
	// strcpy_check("world");

	// strdup_check("hello");
	// strdup_check("world");


	char *buf = (char*)malloc(10);
	// ft_read(0,buf,10 );
	// printf("%s",buf);

	int res = ft_read(10,buf,10);
	printf("%d %s",res, buf);
	return 0;
}

