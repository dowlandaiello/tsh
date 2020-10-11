THIS_FILE := $(lastword $(MAKEFILE_LIST))

# Use vendored readline
readline := ./lib/readline/libreadline.a ./lib/readline/libhistory.a
libreadline := -I ./lib/readline -lreadline

test_binaries := $(subst .c, , $(wildcard tests/*))
example_binaries := $(subst .c, , $(wildcard examples/*.c))
source_files := $(shell find src -name *.c ! -path 'src/main.c')
core_bin := $(readline) $(source_files) src/main.c

# Builds the tiny shell
tsh: $(core_bin)
	cc $(libreadline) -Isrc $(source_files) src/main.c -o tsh

tsh_debug: $(core_bin)
	cc $(libreadline) -Isrc $(source_files) src/main.c -g -o debug

# Targets a riscv64 web demo machine
web_demo: ./lib/readline/risc/libreadline.a $(source_files) src/main.c
	riscv64-linux-gnu-gcc $(subst /readline/, /readline/risc, $(libreadline)) -Isrc $(source_files) src/main.c -o tsh

src/%:

# Builds readline
lib/readline/libreadline.a:
	cd lib/readline && ./configure && make

lib/readline/risc/libreadline.a: lib/ncurses/risc/lib/libncurses.a
	mkdir -p lib/readline/risc && cd lib/readline/risc && CC=riscv64-linux-gnu-gcc ../configure --build=x86_64 --host=riscv64-linux-gnu && make

# Builds ncurses for risc
lib/ncurses/risc/lib/ncurses.a: lib/ncurses/risc/README
	cd lib/ncurses/risc && make && mkdir -p /usr/riscv64-linux-gnu/bin && sudo ln -s /usr/bin/tic /usr/riscv64-linux-gnu/bin/tic && sudo make DESTDIR=/usr/riscv64-linux-gnu/lib install

# Downloads ncurses
lib/ncurses/risc/README:
	mkdir -p lib/ncurses/risc && cd lib/ncurses/risc && curl https://invisible-island.net/datafiles/release/ncurses.tar.gz -o ncurses.tar.gz && \
	tar -xvf ncurses.tar.gz && rm ncurses.tar.gz && mv ncurses-*/* ./ && rm -rf ncurses-* && ./configure --build=x86_64 --host=riscv64-linux-gnu --without-ada

# Builds and runs individual test files
tests/%:
	@echo "RUNNING TEST " $@; echo ""
	cc $(libreadline) -Isrc $(source_files) $@.c -o $@ && $@ && rm $@
	@echo ""; echo "DONE"; echo ""

# Builds an individual example file
examples/%:
	cc $(libreadline) $@.c -o $@

# Install to path
.PHONY: install
install: tsh
	sudo cp tsh /usr/local/bin

# Build all the example programs
.PHONY: examples
examples: $(example_binaries)

.PHONY: clean_examples
clean_examples:
	rm -f $(example_binaries)

# Debugs the specified file
.PHONY: debug
debug: examples
	cc $(libreadline) -g -Isrc $(shell find src -name *.c) $(f) -o debug && lldb debug && rm debug
	@$(MAKE) -f $(THIS_FILE) clean_examples

# Runs all unit tests
.PHONY: test
test: examples $(test_binaries) clean_examples

.PHONY: format
format:
	clang-format -i $(shell find . -name *.c -or -name *.h) -style=file

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm -f $(example_binaries) *.o tsh debug
	rm -rf *.dSYM

.PHONY: all
all: format tsh test
