CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

TARGET = ContactBook

SOURCES = main.c menu.c

OBJECTS = $(SOURCES:.c=.o)

LIB = libcontact.a

LIB_SRC = contact_manager.c

LIB_OBJ = $(LIB_SRC:.c=.o)

HEADERS = menu.h contact_manager.h

all: $(TARGET)

$(TARGET): $(OBJECTS) $(LIB)
	$(CC) $(OBJECTS) -L. -lcontact -o $(TARGET)

$(LIB): $(LIB_OBJ)
	ar rcs $(LIB) $(LIB_OBJ)

$(LIB_OBJ): $(LIB_SRC) contact_manager.h 
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

menu.o: menu.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(OBJECTS) $(LIB_OBJ) $(LIB) $(TARGET)

.PHONY: all run clean