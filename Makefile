ROOT_DIR := $(shell pwd)

test: $(ROOT_DIR)/tests/*/*
	@echo "RUNNING TEST: " $^; echo ""

	clang $^ -I $(ROOT_DIR)/src -o test
	./test
	rm test

	@echo ""; echo "DONE"
