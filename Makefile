CC = gcc
DEBUG = 
CFLAGS = -Wall
LDFLAGS = 
EXEC = 
SRCDIR = ./src
OBJDIR = ./obj
VPATH = $(SRCDIR)
OBJ_NAMES = 
OBJS = $(addprefix $(OBJDIR)/, $(OBJ_NAMES))

ifeq ($(DEBUG), 1)
CFLAGS += -g -DDEBUG
endif

all: huffman codlineal injectError

huffman: huffman.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
codlineal: codlineal.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
injectError: injectError.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean cleanest init

clean:
	rm -f huffman codlineal injectError
	
cleanest: clean
	rm -f $(OBJDIR)/*.o
	
init:
	mkdir -p $(OBJDIR) $(SRCDIR)
	
