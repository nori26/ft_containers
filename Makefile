ALL_FILES=$(shell find tests srcs -type f -name '*.cpp' -o -name '*.hpp')

.PHONY:all
all:

test      : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests
	$(error ft done)

stl       : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

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

%:;@:

.PHONY: FORCE