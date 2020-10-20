THIS_FILE := $(lastword $(MAKEFILE_LIST))

# Use vendored readline
readline := lib/readline/libreadline.a
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

# Targets an x86 web demo machine
web_demo: $(core_bin)
	cc $(libreadline) -m32 -Isrc $(source_files) src/main.c -o tsh

src/%:

# Builds readline
lib/readline/libreadline.a: .gitmodules
	stat lib/readline/libreadline.a || (cd lib/readline && ./configure && make)

# Clones submodules
.PHONY: .gitmodules
.gitmodules:
	(stat .gitmodules || git submodule init) && git submodule update

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
	clang-format -i $(shell find tests src -name "*.c" -or -name "*.h") -style=file

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm -f $(example_binaries) *.o tsh debug
	rm -rf *.dSYM

.PHONY: all
all: format tsh test
