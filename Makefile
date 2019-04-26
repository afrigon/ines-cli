CC	= gcc
INCLDIR	= include/
BINDIR	= bin/
OBJDIR	= obj/
SRCDIR	= src/

TARGET = ines
BIN	= $(addprefix $(BINDIR), $(TARGET))

SRC	= $(wildcard src/*.c)
_OBJS	= $(patsubst src/%.c, %.o, $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

CFLAGS = -Wall -pedantic -I$(INCLDIR)

.PHONY: all, clean
all: $(BINDIR) $(OBJDIR) $(BIN)

$(BIN): $(BINDIR) $(OBJS)
	$(CC) $(OBJS) -o $(BIN)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(BIN) $(OBJS)
