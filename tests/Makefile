##############
# Test rules #
##############

CXX              := c++

BUILDDIR		 := ./build
FTDIR            := $(BUILDDIR)/ft
ASANDIR          := $(BUILDDIR)/asan
STLDIR           := $(BUILDDIR)/stl
DEFAULTDIR       := $(FTDIR)
OBJDIR           := $(DEFAULTDIR)/obj
DEPSDIR          := $(DEFAULTDIR)/depends
INCLUDES         := -I ../includes/ -I utils/

VALGRIND         := $(shell type valgrind > /dev/null && echo valgrind)

FT_TEST          := ft_test
STL_TEST         := stl_test
ASAN_TEST        := asan_test
TESTER			 := $(FT_TEST)

TESTDIR          := ../gtest
GTESTDIR		 := $(TESTDIR)/googletest
GTESTLIB		 := $(GTESTDIR)/gtest.a
GTEST_INCLUDES	 := -I$(GTESTDIR)/gtest
GTEST_FLAGS		 := -Werror -Wall -Wextra -std=c++98
GTEST_LIBS		 := -lpthread

PP_FLAGS         := -D FT_TEST

CASE_DIR	     := system_tests
CASE_SRCS	      = $(shell find $(CASE_DIR) -name '*.cpp')
CASE_OBJS	      = $(CASE_SRCS:%.cpp=$(OBJDIR)/%.o)
CASE_DEPS	      = $(CASE_SRCS:%.cpp=$(DEPSDIR)/%.d)

UTIL_DIR          := utils
UTIL_SRCS	      = $(shell find $(UTIL_DIR) -name '*.cpp')
UTIL_OBJS	      = $(UTIL_SRCS:%.cpp=$(OBJDIR)/%.o)
UTIL_DEPS	      = $(UTIL_SRCS:%.cpp=$(DEPSDIR)/%.d)

GTEST_OPT	:= $(subst $() ,*:*,$(filter-out test asan clean fclean stl ft,$(MAKECMDGOALS)))

test		: $(TESTER) FORCE
	$(VALGRIND) ./$< --gtest_filter='*$(GTEST_OPT)*'

ft   : FORCE
	$(MAKE) test $(GTEST_OPT) 'DEFAULTDIR=$(FTDIR)' 'TESTER=$(FT_TEST)' 'PP_FLAGS= -D FT_TEST'

asan   : FORCE
	$(MAKE) test $(GTEST_OPT) 'GTEST_FLAGS=$(GTEST_FLAGS) -fsanitize=address -g3' 'DEFAULTDIR=$(ASANDIR)' 'TESTER=asan' 'VALGRIND='

stl   : FORCE
	$(MAKE) test $(GTEST_OPT) 'DEFAULTDIR=$(STLDIR)' 'TESTER=$(STL_TEST)' 'PP_FLAGS= -D STL_TEST'

$(TESTER)	: $(GTESTLIB) $(CASE_OBJS) $(UTIL_OBJS)
	c++ $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) $(GTESTLIB) $(CASE_OBJS) $(UTIL_OBJS) $(GTEST_LIBS) -o $@

$(GTESTLIB)	:
	$(MAKE) -C $(TESTDIR)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)/$(*D)
	@mkdir -p $(DEPSDIR)/$(*D)
	$(CXX) $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) -MMD -MP -MF $(DEPSDIR)/$*.d -c $< -o $@

clean: FORCE
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(FT_TEST) $(STL_TEST) $(ASAN_TEST)

.PHONY: re
re: fclean test

%:;@:

.PHONY: $(CASE_DEPS) $(UTIL_DEPS)
-include $(CASE_DEPS) $(UTIL_DEPS)
