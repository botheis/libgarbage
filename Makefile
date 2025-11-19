PREFIX ?= /usr/local
VERSION = 1.0.0

CC = gcc
CFLAGS = -Wall -Wextra -O3 -fPIC
INCLUDE = -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

LIB_NAME = garbage
STATIC = lib$(LIB_NAME).a
SHARED = lib$(LIB_NAME).so

EXAMPLES_OPTS = -Wall -g -O3 -o
EXAMPLES_CFLAGS= -I/usr/local/include
EXAMPLES_LIBS= -L/usr/local/lib -lgarbage

all: $(STATIC) $(SHARED)

$(STATIC): $(OBJ)
	ar rcs $@ $^

$(SHARED): $(OBJ)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	# install libs
	install -d $(PREFIX)/lib
	install -m 755 $(STATIC) $(SHARED) $(PREFIX)/lib

	# install headers
	install -d $(PREFIX)/include
	if [ ! -d $(PREFIX)/include/garbage ]; then mkdir $(PREFIX)/include/garbage; fi
	install -m 644 include/garbage/*.h $(PREFIX)/include/garbage

	# install pkg-config file
	install -d $(PREFIX)/lib/pkgconfig
	sed \
		-e "s|@PREFIX@|$(PREFIX)|" \
		-e "s|@VERSION@|$(VERSION)|" \
		pkgconfig/$(LIB_NAME).pc.in \
		> $(PREFIX)/lib/pkgconfig/$(LIB_NAME).pc


examples:all
	$(CC) $(EXAMPLES_OPTS) examples/init.exe examples/init.c $(EXAMPLES_CFLAGS) $(EXAMPLES_LIBS)
	$(CC) $(EXAMPLES_OPTS) examples/push.exe examples/init.c $(EXAMPLES_CFLAGS) $(EXAMPLES_LIBS)


clean:
	rm -f src/*.o $(STATIC) $(SHARED)
	rm -rf examples/*.exe

.PHONY: all clean install