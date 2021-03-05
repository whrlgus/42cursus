#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

va_list	ap;
int dot,width,precision;
char type;

// MARK:- stdout
int ft_putc(char c){
	write(1,&c,1);
	return 1;
}

int ft_putcn(char c, int n){
	if(n<=0)return 0;
	
	int tmp=n;
	while(tmp--)ft_putc(c);
	return n;
}

int ft_puts(char *s, int n){
	int	i=0;
	while (s[i] && i < n)ft_putc(s[i++]);
	return i;
}

void ft_putn(long long num, int base){
	char *hex = "0123456789abcdef";
	if (num < 0)num = -num;
	
	if (num >= base){
		ft_putn(num / base, base);
		ft_putn(num % base, base);
	}else ft_putc(hex[num]);
}

// MARK:- length
int	ft_strlen(char *s){
	int	i=-1;
	while(s[++i]);
	return i;
}

int	ft_dlen(int num){
	int	i=1;
	while (num/=10)i++;
	return i;
}

int ft_hlen(unsigned int num){
	int	i=1;
	while (num/=16)i++;
	return i;
}


// MARK:- print sdx
int print_s(void){
	char *str=va_arg(ap, char *);
	if(!str)str="(null)";

	int len=ft_strlen(str);
	if(!dot||precision>len)precision=len;

	return ft_putcn(' ',width-precision)+ft_puts(str, precision);
}

int print_d(void){
	int num=va_arg(ap,int),neg=num<0,len=ft_dlen(num);

	if(dot&&num==0&&precision==0)return ft_putcn(' ',width);
	
	if(!dot||precision<len)precision=len;
	
	int ret=ft_putcn(' ',width-precision-neg);
	if(neg)ret+=ft_putc('-');
	ret+=ft_putcn('0',precision-len);
	ft_putn(num, 10);
	
	return ret+len;
}

int print_x(void){
	unsigned int num=va_arg(ap,unsigned int);
	int len=ft_hlen(num);

	if(dot&&num==0&&precision==0)return ft_putcn(' ',width);
	
	if(!dot||precision<len)precision=len;
	
	int ret=ft_putcn(' ',width-precision);
	ret+=ft_putcn('0',precision-len);
	ft_putn(num, 16);
	
	return ret+len;
}

int ft_isdigit(char c){
	return '0'<=c&&c<='9';
}

int setParam(char *s){
	width=0;
	dot=0;
	precision=0;
	int i=0;
	while(s[i]){
		char c=s[i];
		if(ft_isdigit(c)){
			int tmp=c-'0';
			if(!dot)width=(width*10)+tmp;
			else precision=(precision*10)+tmp;
		}else if(c=='.')dot=1;
		else break;
			
		++i;
	}
	type=s[i++];
	return i;
}

int	parse(char *s)
{
	int	i=0,ret=0;

	while(s[i]){
		if(s[i]!='%')ret+=ft_putc(s[i]);
		else{
			i+=setParam(s+i+1);
			if (type == 's')ret+=print_s();
			else if(type=='d')ret+=print_d();
			else ret+=print_x();
		}
		++i;
	}
	return (ret);
}


int	ft_printf(const char *s, ...)
{
	va_start(ap, s);
	int ret = parse((char *)s);
	va_end(ap);
	return (ret);
}

