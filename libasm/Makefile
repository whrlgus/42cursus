NAME = libasm.a

GCC = gcc -Wall -Wextra -Werror

NASM = nasm -fmacho64

AR = ar rc
RM = rm -f


SRCS = $(wildcard *.s)
OBJS = $(SRCS:.s=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.s
	$(NASM) $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
