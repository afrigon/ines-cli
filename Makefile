CC	= gcc
INCLDIR	= include/
BINDIR	= bin/
OBJDIR	= obj/
SRCDIR	= src/

NAME = ines
BIN	= $(addprefix $(BINDIR), $(NAME))

SRC	= $(wildcard src/*.c)
_OBJS	= $(patsubst src/%.c, %.o, $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

CFLAGS = -Wall -std=c99 -pedantic -g -I$(INCLDIR)

.PHONY: all, clean
all: $(BIN)

clean:
	rm -rf $(BINDIR) $(OBJDIR)

$(BIN): $(BINDIR) $(OBJS)
	$(CC) $(OFLAGS) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJS): $(OBJDIR) $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

