CC = gcc
DEBUG = 
CFLAGS = -Wall
LDFLAGS = 
EXEC = 
SRCDIR = ./src
OBJDIR = ./obj
VPATH = $(SRCDIR)
OBJ_NAMES = huffman.o codlineal.o
OBJS = $(addprefix $(OBJDIR)/, $(OBJ_NAMES))

ifeq ($(DEBUG), 1)
CFLAGS += -g -DDEBUG
endif

all: huffman codlineal

huffman: huffman.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
codlineal: codlineal.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $^

.PHONY: clean cleanest init

clean:
	rm -f huffman codlineal
	
cleanest: clean
	rm -f $(OBJDIR)/*.o
	
init:
	mkdir -p $(OBJDIR) $(SRCDIR)
	
