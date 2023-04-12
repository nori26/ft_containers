ALL_FILES=$(shell find tests srcs -type f -name '*.cpp' -o -name '*.hpp')

.PHONY:all
all:

test      : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

ft      : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

stl       : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

asan : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

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