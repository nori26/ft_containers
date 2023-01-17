ALL_FILES=$(shell find . -path './gtest' -prune -o -name '*.cpp' -o -name '*.hpp')

.PHONY:all
all:

test      : FORCE
	$(MAKE) test -C tests

asan : FORCE
	$(MAKE) asan -C tests

clean: FORCE
	$(MAKE) clean -C tests

fclean: clean
	$(MAKE) fclean -C tests

.PHONY:re
re: fclean all

fmt: FORCE
	clang-format -i --verbose $(ALL_FILES)

.PHONY: FORCE