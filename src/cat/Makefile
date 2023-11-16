CC = gcc
CFLAGS = -Wall -Werror -Wextra

SOURCES = s21_cat.c parser.c print_file.c
HEADERS = s21_cat.h parser.h print_file.h flags_struct.h
OBJECTS = $(SOURCES:.c=.o)

TARGET = s21_cat

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean