NAME	:= gtest.a
AR		:= ar
ARFLAGS	:= scr
DIR		:= googletest
SRCS	= $(LIBDIR)/googletest/src/gtest_main.cc $(SRCDIR)/gtest-all.cc
OBJS	= $(notdir $(SRCS:.cc=.o))
SRCDIR	:= $(DIR)/gtest
LIBDIR	:= $(DIR)/googletest-release-1.8.1

.PHONY: all
all		: $(NAME)

$(NAME)	: $(OBJS)
	$(AR) $(ARFLAGS) $(DIR)/$(NAME) $^

$(LIBDIR):
	mkdir -p $(DIR)
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.8.1.tar.gz
	tar -xvzf release-1.8.1.tar.gz -C $(DIR)
	rm  release-1.8.1.tar.gz

.PHONY: clean
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

$(SRCDIR): $(LIBDIR)
	python3 $(LIBDIR)/googletest/scripts/fuse_gtest_files.py $(DIR)

$(OBJS)	: $(SRCDIR)
	c++ -c -std=c++98 -Wall -Wextra -Werror $(LIBDIR)/googletest/src/gtest_main.cc $(SRCDIR)/gtest-all.cc -I$(DIR)
