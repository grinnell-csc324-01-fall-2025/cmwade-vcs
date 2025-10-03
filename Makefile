CC := clang
CFLAGS := -c -Iinclude
AR := ar
AFLAGS := rcs

CFILES := $(wildcard src/VCS*.c)
HFILES := $(wildcard include/VCS*.h)
COBJECTS := $(patsubst src/%.c,bin/%.o,$(CFILES))

LIBNAME := libvcs_sdl.a
INSTALL := /usr/lib/
INCLUDE := /usr/local/include/VCS/

$(LIBNAME): $(COBJECTS)
	$(AR) $(AFLAGS) $@ $^

$(COBJECTS): bin/%.o: src/%.c
	$(CC) $< $(CFLAGS) -o $@

install:
	cp $(LIBNAME) $(INSTALL)
	mkdir -p $(INCLUDE)
	cp $(HFILES) $(INCLUDE)

uninstall:
	rm $(INSTALL)$(LIBNAME)
	rm -r $(INCLUDE)

clean:
	rm $(COBJECTS) $(LIBNAME)
