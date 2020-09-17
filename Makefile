THIS_FILE := $(lastword $(MAKEFILE_LIST))

test_binaries = $(subst .c, , $(wildcard tests/*))
example_binaries = $(subst .c, , $(wildcard examples/*.c))
source_files = $(shell find src -name *.c ! -path 'src/main.c')

# Builds the tiny shell
tsh: $(source_files) src/main.c
	cc -Isrc $(source_files) src/main.c -o tsh

src/%:

# Builds and runs individual test files
tests/%:
	@echo "RUNNING TEST " $@; echo ""
	cc -Isrc $(shell find src -name *.c ! -path 'src/main.c') $@.c -o $@ && $@ && rm $@
	@echo ""; echo "DONE"; echo ""

# Builds an individual example file
examples/%:
	cc $@.c -o $@

# Install to path
.PHONY: install
install: tsh
	cp tsh /usr/bin

# Build all the example programs
.PHONY: examples
examples: $(example_binaries)

.PHONY: clean_examples
clean_examples:
	rm -f $(example_binaries)

# Debugs the specified file
.PHONY: debug
debug: examples
	cc -g -Isrc $(shell find src -name *.c) $(f) -o debug && lldb debug && rm debug
	@$(MAKE) -f $(THIS_FILE) clean_examples

# Runs all unit tests
.PHONY: test
test: examples $(test_binaries) clean_examples

.PHONY: format
format:
	clang-format -i tests/**.c src/**.c src/**.h -style=file

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm -f $(example_binaries) *.o tsh debug
	rm -rf *.dSYM

.PHONY: all
all: format tsh test
