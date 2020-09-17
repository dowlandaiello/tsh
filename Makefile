test_binaries = $(subst .c, , $(wildcard tests/*))
example_binaries = $(subst .c, , $(wildcard examples/*.c))

# Builds the tiny shell
tsh: tsh.o
	cc tsh.o -o tsh

tsh.o:
	cc -c src/main.c -o tsh.o

# Builds and runs individual test files
tests/%:
	@echo "RUNNING TEST " $@; echo ""
	cc -Isrc $(shell find src -name *.c) $@.c -o $@ && $@ && rm $@
	@echo ""; echo "DONE"; echo ""

# Builds an individual example file
examples/%:
	cc $@.c -o $@

# Build all the example programs
.PHONY: examples
examples: $(example_binaries)

# Debugs the specified file
.PHONY: debug
debug: examples
	cc -g -Isrc $(shell find src -name *.c) $(f) -o debug && lldb debug && rm debug

# Runs all unit tests
.PHONY: test
test: examples $(test_binaries)

.PHONY: format
format:
	clang-format -i tests/**.c src/**.c src/**.h -style=file

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm -f $(example_binaries) *.o tsh debug

.PHONY: all
all: format tsh test
