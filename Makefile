NAME      := ft_bin
NAME_STL  := stl_bin

CXX      := c++
CXXFALGS := -Werror -Wall -Wextra -std=c++98 -pedantic -MP -MMD

SRCS     := main.cpp
OBJDIR   := ./obj
FT_DIR   := $(OBJDIR)/ft
STL_DIR  := $(OBJDIR)/stl

FT_OBJS  := $(SRCS:%.cpp=$(FT_DIR)/%.o)
STL_OBJS := $(SRCS:%.cpp=$(STL_DIR)/%.o)

FT_D  := $(SRCS:%.cpp=$(FT_DIR)/%.d)
STL_D := $(SRCS:%.cpp=$(STL_DIR)/%.d)

ALL_FILES=$(shell find tests srcs -type f -name '*.cpp' -o -name '*.hpp')

.PHONY:all
all: $(NAME) $(NAME_STL)

-include $(FT_D) $(STL_D)

$(NAME)	: $(FT_OBJS)
	$(CXX) $(CXXFALGS) $< -o $@

$(NAME_STL)	: $(STL_OBJS)
	$(CXX) $(CXXFALGS) $< -o $@

$(FT_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFALGS) -D FT_CONTAINERS $< -c -o $@

$(STL_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFALGS) $< -c -o $@

test      : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

ft      : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

stl       : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

asan : FORCE
	$(MAKE) $(MAKECMDGOALS) -C tests

clean: FORCE
	rm -rf $(OBJDIR)
	$(MAKE) clean -C tests

fclean: clean
	rm -f $(NAME) $(NAME_STL)
	$(MAKE) fclean -C tests

.PHONY:re
re: fclean all

fmt: FORCE
	clang-format -i --verbose $(ALL_FILES)

%:;@:

.PHONY: FORCE