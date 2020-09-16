# Builds the tiny shell
tsh: tsh.o
	clang tsh.o -o tsh

tsh.o:
	clang -c src/main.c -o tsh.o
