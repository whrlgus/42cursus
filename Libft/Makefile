CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

TARGET = libft.a
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
$(TARGET): $(OBJECTS)
	ar cr $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
