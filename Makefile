# Builds the tiny shell
tsh: tsh.o
	cc tsh.o -o tsh

tsh.o:
	cc -c src/main.c -o tsh.o

debug:
	cc -g -Isrc $(shell find src -name *.c) $(f) -o debug && lldb debug && rm debug

# Builds and runs individual test files
tests/%:
	@echo "RUNNING TEST " $@
	cc -Isrc $(shell find src -name *.c) $@.c -o $@ && $@ && rm $@
	@echo "DONE"; echo ""

# Runs all unit tests
.PHONY: test
test: $(subst .c, , $(wildcard tests/*))

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm *.o tsh debug

.PHONY: all
all: tsh test
