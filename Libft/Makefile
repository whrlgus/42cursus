TARGET = libft.a
CFLAGS = -Wall -Wextra -Werror

BSRCS = $(wildcard *_p.c)
BOBJS = $(BSRCS:.c=.o)
SRCS = $(filter-out $(BSRCS),$(wildcard *.c))
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar cr $@ $^

bonus: $(OBJS) $(BOBJS)
	ar cr $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
