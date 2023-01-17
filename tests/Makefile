##############
# Test rules #
##############

BUILDDIR		 := ./build
OBJDIR           := $(BUILDDIR)/obj
ASANDIR          := $(BUILDDIR)/obj-asan
STLDIR           := $(BUILDDIR)/obj-stl
DEPSDIR          := $(BUILDDIR)/depends
INCLUDES         := -I ../srcs/

FT_TEST          := ft
STL_TEST         := stl
TESTER			 := $(FT_TEST)
GTESTDIR		 := ../gtest/googletest
GTESTLIB		 := $(GTESTDIR)/gtest.a
GTEST_INCLUDES	 := -I$(GTESTDIR)/gtest
GTEST_FLAGS		 := -Werror -Wall -Wextra -std=c++98
GTEST_LIBS		 := -lpthread

PP_FLAGS         := -D FT_TEST

CASE_DIR	     := unit-tests
CASE_SRCS	      = $(shell find $(CASE_DIR) -name '*test.cpp')
CASE_OBJS	      = $(CASE_SRCS:%.cpp=$(OBJDIR)/%.o)
CASE_DEPS	      = $(CASE_SRCS:%.cpp=$(DEPSDIR)/%.d)

GTEST_OPT	:= $(subst $() ,*:*,$(filter-out test asan clean fclean stl,$(MAKECMDGOALS)))

test		: $(TESTER) FORCE
	./$< --gtest_filter='*$(GTEST_OPT)*' || ($(MAKE) check; ! :)
	@$(MAKE) check

asan   : FORCE
	$(MAKE) 'GTEST_FLAGS=$(GTEST_FLAGS) -fsanitize=address' 'OBJDIR=$(ASANDIR)'

stl   : FORCE
	$(MAKE) 'GTEST_FLAGS=$(GTEST_FLAGS)' 'OBJDIR=$(STLDIR)' 'TESTER=$(STL_TEST)' 'PP_FLAGS= -D STL_TEST'

$(TESTER)	: $(GTESTLIB) $(CASE_OBJS)
	c++ $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) $(GTESTLIB) $(CASE_OBJS) $(TEST_TARGET) $(GTEST_LIBS) -o $@

$(GTESTLIB)	:
	$(MAKE) -C $(TESTDIR)

$(OBJDIR)/$(CASE_DIR)/%.o: $(CASE_DIR)/%.cpp
	@mkdir -p $(OBJDIR)/$(CASE_DIR)/$(*D)
	@mkdir -p $(DEPSDIR)/$(CASE_DIR)/$(*D)
	$(CXX) $(GTEST_FLAGS) $(PP_FLAGS) $(GTEST_INCLUDES) $(INCLUDES) -MMD -MP -MF $(DEPSDIR)/$(CASE_DIR)/$*.d -c $< -o $@

check:
	@printf "$(RED)$(BOLD)\n"
	@WARN_FILE=$$(find $(CASE_DIR) -type f | grep -v '_test\.cpp') \
		&& printf "Some files are not included.\n$(END)$(RED)%s\n" $$WARN_FILE \
		||:
	@printf "$(END)"

clean: FORCE
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(FT_TEST) $(STL_TEST)

.PHONY: re
re: fclean test

%:;@:

.PHONY: $(CASE_DEPS)
-include $(CASE_DEPS)
