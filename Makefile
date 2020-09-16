ROOT_DIR := $(shell pwd)

test: $(wildcard $(ROOT_DIR)/tests/**/*)
	@echo "RUNNING TESTS: " $^; echo ""

	for f in "$^"; do \
		echo "RUNNING TEST: '" $$f "'" && echo "" && \
		clang $$f -I $(ROOT_DIR)/src -o test && \
		./test && \
		rm test && \
		echo "" && echo "DONE"; \
	done

	@echo ""; echo "DONE WITH ALL"
