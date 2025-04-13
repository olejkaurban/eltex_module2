CC = gcc

CFLAGS = -Wall -Werror -Wextra -g 

TARGET = ContactBook

SOURCES = main.c menu.c contact_manager.c

HEADERS = menu.h contact_manager.h

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

menu.o: menu.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

contact_manager.o: contact_manager.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all run clean