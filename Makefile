# The names of all test files
tests = $(wildcard tests/**/*)

# Builds the tiny shell
tsh: tsh.o
	cc tsh.o -o tsh

tsh.o:
	cc -c src/main.c -o tsh.o

test: $(tests)

tests/%.c:
	cc $@ -o tests/$@ && tests/$@ && rm tests/$@

# Removes all object files, and deletes the built shell
.PHONY: clean
clean:
	rm *.o tsh
