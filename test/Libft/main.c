#include "main.h"

const size_t size = 20;
void *arr, *ft_arr;
size_t n = size;
char *file = "/Users/gihyun/tmp/txtfile";

int main(int argc, const char * argv[]) {
	init();
//	t_memset(n);
//	t_bzero(n-1);
//	t_memcpy(n);
//	t_memccpy();
//	t_memmove();
//	t_memchr();
//	t_memcmp();
//	t_strlen();
//	t_strlcat();
//	t_strchr();
//	t_strncmp();
//	t_strrchr();
//	t_strnstr();
//	t_isalpha();
//	t_isascii();
//	t_toupper();
//	t_calloc();
//	t_strdup();
//	t_strlcpy();
//	t_substr();
	t_strjoin();
//	t_strtrim();
//	t_split();
//	t_itoa();
//	t_strmapi();
//	t_putchar_fd();
//	t_putstr_fd();
//	t_putendl_fd();
//	t_putnbr_fd();
	
//	t_bonus();
	return 0;
}

void print_list(t_list *lst){
	while(lst){
		printf("%d ",*(int*)lst->content);
		lst=lst->next;
	}
	printf("\n");
}

void del(void *data){
	
}

void f(void *data){
	printf("%d ",*(int*)data);
}
void *f1(void *data){
	*(int*)data += 1;
	return data;
}

void t_bonus(){
	t_list *head=0;
	int data[]={9,1,2,3,4,5};
//	for(int i=0;i<6;++i)
//		ft_lstadd_front(&head,ft_lstnew(&data[i]));
//	print_list(ft_lstlast(head));
//	print_list(head);
	print_list(head);
//	ft_lstdelone(head, del);
	head = ft_lstmap(head, f1, del);
//	ft_lstclear(&head,del);
	ft_lstiter(head, f);
	
	printf("lst size : %d\n", ft_lstsize(head));
}

void t_putnbr_fd(){
	int fd = open(file, O_WRONLY|O_CREAT|O_EXCL,0644);
	if(fd==-1){
		fd = open(file, O_WRONLY);
		if(fd==-1)return;
	}
	ft_putnbr_fd(0, fd);
	close(fd);
}

void t_putendl_fd(){
	int fd = open(file, O_WRONLY|O_CREAT|O_EXCL,0644);
	if(fd==-1){
		fd = open(file, O_WRONLY);
		if(fd==-1)return;
	}
	char *s ="Hello World!";
	ft_putendl_fd(s, fd);
	close(fd);
}

void t_putstr_fd(){
	int fd = open(file, O_WRONLY|O_CREAT|O_EXCL,0644);
	if(fd==-1){
		fd = open(file, O_WRONLY);
		if(fd==-1)return;
	}
	char *s ="Hello World!";
	ft_putstr_fd(s, fd);
	close(fd);
}


void t_strlcpy(){
	char dst[5],ft_dst[5];
	printf("%d %d\n",ft_strlcpy(dst, "asdfasd", 0),ft_strlcpy(ft_dst, "asdfasd", 0));
	printf("%s %s\n",dst,ft_dst);
}

void t_putchar_fd(){
	int fd = open(file, O_WRONLY|O_CREAT|O_EXCL,0644);
	if(fd==-1){
		fd = open(file, O_WRONLY);
		if(fd==-1)return;
	}
	ft_putchar_fd('a', fd);
	close(fd);
}

char foo(unsigned int i, char c){
	return c+i;
}

void t_strmapi(){
	printf("%s\n",ft_strmapi("1234", foo));
}

void t_itoa(){
	printf("%s\n",ft_itoa(0));
}

void t_split(){
	char **ret = ft_split("hello world! ", ' ');
	while (*ret)printf("%s\n",*ret++);
}

void t_strtrim(){
	char *s1 = "123a123";
	char *set = "";
	printf("%s\n",ft_strtrim(s1, set));
}

void t_strjoin(){
	char *s1 = "12";
	char *s2 = "23";
	printf("%s\n",ft_strjoin(s1, s2));
}

void t_substr(){
//	char *s = "123456";
//	printf("%s\n",ft_substr(s, 2, 3));
	char    str[] = "lorem ipsum dolor sit amet";
	printf("%s\n",ft_substr(str, 7, 10));
}

void t_strdup(){
	char *s1="123123";
	printf("%s %s\n",strdup(s1),ft_strdup(s1));
}

void t_calloc(){
	int * pData = (int*) ft_calloc (10,sizeof(int));
	for(int j=0;j<10;++j)printf("%d ",pData[j]);
}

void t_toupper(){
	int c='A';
	printf("%d %d",tolower(c),ft_tolower(c));
}

void t_isascii(){
	int c = 128;
	printf("%d %d\n",isascii(c),ft_isascii(c));
}

void t_isalpha(){
	int c = 'a';
	printf("%d %d\n",isalpha(c),ft_isalpha(c));
}

void t_strnstr(){
	char *src="asdfqwer123qwer";
	char *to_find="12";
	char *ret=strnstr(src,to_find,0);
	char *ft_ret=ft_strnstr(src,to_find,0);
	printf("%s %s\n",ret,ft_ret);
}

void t_strrchr(){
	char *s="142341";
	char *ret=strrchr(s,'4');
	char *ft_ret=ft_strrchr(s,'4');
	printf("%s %s\n",ret,ft_ret);
	printf("%c %c\n",*ret,*ft_ret);
}

void t_strchr(){
	char *s="1234";
	char *ret=strchr(s,0);
	char *ft_ret=ft_strchr(s,0);
	//	printf("%s %s\n",ret,ft_ret);
	printf("%c %c\n",*ret,*ft_ret);
}

void t_strlcat(){
	char dst[5]="11111",ft_dst[5]="11111",*src="asdf";
	printf("%d %d\n",strlcat(dst,src,5),ft_strlcat(ft_dst,src,5));
	printf("%s %s\n",dst,ft_dst);
	
}

void t_strlen(){
	char *arr=0;
	printf("%d\n",strlen(arr));
	printf("%d\n",ft_strlen(arr));
}

void t_memcmp(){
	for(int i=0;i<10;++i){
		memset(arr+i, i, 1);
		memset(ft_arr+i, i, 1);
	}
	*(char*)(ft_arr+5)=0xff;
	display(10);
	
	printf("%d %d\n",memcmp(arr, ft_arr, 5),ft_memcmp(arr, ft_arr, 5));
}
void t_strncmp(){
	char *s1="1233";
	char *s2="123";
	size_t n=5;
	printf("%d %d\n",strncmp(s1, s2, n),ft_strncmp(s1, s2, n));
}

void t_memchr(){
	for(int i=0;i<10;++i){
		memset(arr+i, i, 1);
		memset(ft_arr+i, i, 1);
	}
	void *ret=memchr(arr, 5, 4);
	void *ft_ret=ft_memchr(ft_arr, 5, 4);
	
	if(ret)printf("%d ",*(char*)ret);
	else printf("null ");
	if(ft_ret)printf("%d\n",*(char*)ft_ret);
	else printf("null\n");
}

void t_memmove(){
	for(int i=0;i<10;++i){
		memset(arr+i, i, 1);
		memset(ft_arr+i, i, 1);
	}
	arr = memmove(arr-2,arr,8);
	ft_arr = ft_memmove(ft_arr-2,ft_arr,8);
	display(10);
}

void t_memccpy(){
	char src[5] = "12345";
	t_memset(5);
	void *ret = memccpy(arr, src, 1, 5);
	void *ft_ret = ft_memccpy(ft_arr, src, 1, 5);
	
	if(ret)printf("%d ",*(char*)ret);
	else printf("null ");
	if(ft_ret)printf("%d\n",*(char*)ft_ret);
	else printf("null\n");
	
	display(size);
}

void t_memcpy(size_t n){
	char src[10]="1234567890";
	memset(arr,1,10);
	ft_memset(ft_arr,1,10);
	memcpy(arr,src,10);
	ft_memcpy(ft_arr,src,10);
	display(20);
}

void t_bzero(size_t n){
	bzero(arr, n);
	ft_bzero(ft_arr, n);
	display(size);
}

void t_memset(size_t n){
	int c = 2;
	void *ret = memset(arr, c, n);
	void *ft_ret = ft_memset(ft_arr, c, n);
	
	printf("%d %d\n", *(char*)ret, *(char*)ft_ret);
	display(size);
}



void init(){
	arr = (char*)malloc(size);
	ft_arr = (char*)malloc(size);
}

void display(int size){
	print(arr,size);
	print(ft_arr,size);
}

void print(char *arr,int size){
	for(int i=0;i<size;++i)printf("%d ", (unsigned char)arr[i]);
	printf("\n");
}

