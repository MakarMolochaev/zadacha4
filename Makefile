CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c func.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=program

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@