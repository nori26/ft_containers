##############
# Test rules #
##############

BUILDDIR		 := ./build
FTDIR            := $(BUILDDIR)/ft
ASANDIR          := $(BUILDDIR)/asan
STLDIR           := $(BUILDDIR)/stl
DEFAULTDIR       := $(FTDIR)
OBJDIR           := $(DEFAULTDIR)/obj
DEPSDIR          := $(DEFAULTDIR)/depends
INCLUDES         := -I ../srcs/ -I utils/

VALGRIND         := $(shell type valgrind > /dev/null && echo valgrind)

FT_TEST          := ft
STL_TEST         := stl
TESTER			 := $(FT_TEST)

TESTDIR          := ../gtest
GTESTDIR		 := $(TESTDIR)/googletest
GTESTLIB		 := $(GTESTDIR)/gtest.a
GTEST_INCLUDES	 := -I$(GTESTDIR)/gtest
GTEST_FLAGS		 := -Werror -Wall -Wextra -std=c++98
GTEST_LIBS		 := -lpthread

PP_FLAGS         := -D FT_TEST

CASE_DIR	     := unit-tests
CASE_SRCS	      = $(shell find $(CASE_DIR) -name '*.cpp')
CASE_OBJS	      = $(CASE_SRCS:%.cpp=$(OBJDIR)/%.o)
CASE_DEPS	      = $(CASE_SRCS:%.cpp=$(DEPSDIR)/%.d)

UTIL_DIR          := utils
UTIL_SRCS	      = $(shell find $(UTIL_DIR) -name '*.cpp')
UTIL_OBJS	      = $(UTIL_SRCS:%.cpp=$(OBJDIR)/%.o)
UTIL_DEPS	      = $(UTIL_SRCS:%.cpp=$(DEPSDIR)/%.d)

GTEST_OPT	:= $(subst $() ,*:*,$(filter-out test asan clean fclean stl,$(MAKECMDGOALS)))

test		: $(TESTER) FORCE
	$(VALGRIND) ./$< --gtest_filter='*$(GTEST_OPT)*' || ($(MAKE) check; ! :)

asan   : FORCE
	$(MAKE) test $(GTEST_OPT) 'GTEST_FLAGS=$(GTEST_FLAGS) -fsanitize=address -g3' 'DEFAULTDIR=$(ASANDIR)' 'TESTER=asan' 'VALGRIND='

stl   : FORCE
	$(MAKE) test $(GTEST_OPT) 'DEFAULTDIR=$(STLDIR)' 'TESTER=$(STL_TEST)' 'PP_FLAGS= -D STL_TEST'

$(TESTER)	: $(GTESTLIB) $(CASE_OBJS) $(UTIL_OBJS)
	c++ $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) $(GTESTLIB) $(CASE_OBJS) $(UTIL_OBJS) $(GTEST_LIBS) -o $@

$(GTESTLIB)	:
	$(MAKE) -C $(TESTDIR)

$(OBJDIR)/$(CASE_DIR)/%.o: $(CASE_DIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(CASE_DIR)/$(*D)
	@mkdir -p $(DEPSDIR)/$(CASE_DIR)/$(*D)
	$(CXX) $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) -MMD -MP -MF $(DEPSDIR)/$(CASE_DIR)/$*.d -c $< -o $@

$(OBJDIR)/$(UTIL_DIR)/%.o: $(UTIL_DIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(UTIL_DIR)/$(*D)
	@mkdir -p $(DEPSDIR)/$(UTIL_DIR)/$(*D)
	$(CXX) $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) -MMD -MP -MF $(DEPSDIR)/$(UTIL_DIR)/$*.d -c $< -o $@

clean: FORCE
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(FT_TEST) $(STL_TEST)

.PHONY: re
re: fclean test

%:;@:

.PHONY: $(CASE_DEPS) $(UTIL_DEPS)
-include $(CASE_DEPS) $(UTIL_DEPS)
