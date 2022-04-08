#
# MAIN VARIABLES
#
PROGRAMS	= vector stack map
DEPS		= $(shell find . -type f -name "*.hpp")
DEPS_DIR	= iterators .
TESTS_DIR	= tests
TEST_EXE	= ./tests/run_tests.sh
$(foreach prog, $(PROGRAMS), $(eval $(prog)_OBJ = $(TESTS_DIR)/$(prog)/main.o))
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 $(addprefix -I, $(DEPS_DIR))
SHELL		= /bin/bash

#
# TEXT HIGHLIGHTING VARIABLES
#
RED		= "\033[0;31m"
GREEN	= "\033[0;32m"
YELLOW	= "\033[1;33m"
L_GRAY	= "\033[0;37m"
D_GRAY	= "\033[1;30m"
WHITE	= "\033[1;37m"

#
# TEXT VARIABLES
#
OK		= echo -e $(GREEN)[OK]$(L_GRAY)
FAIL	= echo -e $(RED)[FAIL]$(L_GRAY)
BUILD	= echo -ne $(L_GRAY)"=> Building $(1)... "
LINK	= echo -ne $(L_GRAY)"Linking $(1)... "
TEST	= echo -ne $(L_GRAY)"Testing... "

#
# TEMPLATES
#
define TRY =
$(1) && $(call OK) || ($(call FAIL) && exit 1);
endef

define PROGRAM_template =
$(1): $$($(1)_OBJ)
	@$(call LINK,$(1)) ; \
	$(call TRY,$(CC) $(CFLAGS) $$($(1)_OBJ) -o $(1))
ALL_OBJS += $$($(1)_OBJ)
endef


#
# RECIPES
#

all: $(PROGRAMS)

$(foreach prog, $(PROGRAMS), $(eval $(call PROGRAM_template,$(prog))))

%.o: %.cpp
	@$(call BUILD,$<); \
	$(call TRY,$(CC) $(CFLAGS) -c $< -o $@)

test: re
	@$(call TEST); \
	$(call TRY, $(TEST_EXE))

clean:
	@echo -ne $(YELLOW)
	rm -f $(ALL_OBJS)
	@echo -ne $(L_GRAY)

fclean: clean
	@echo -ne $(YELLOW)
	rm -rf $(PROGRAMS)
	@echo -ne $(L_GRAY)

re: fclean all

.PHONY: all clean fclean re
