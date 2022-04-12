#
# MAIN VARIABLES
#
PROGRAMS	= stl ft
DEPS_DIR	= iterators containers
TESTS_DIR	= tests
TEST_EXE	= ./tests/run_tests.sh > /dev/null 2>&1
stl_OBJ		= tests/stl.o
ft_OBJ		= tests/my_stl.o
OBJECTS		=  $(stl_OBJ) $(ft_OBJ)
MAIN		= tests/main.cpp
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
define TRY
$(1) && $(call OK) || ($(call FAIL) && exit 1);
endef

define PROGRAM_template
$(1): $$($(1)_OBJ)
	@$(call LINK,$(1)) ; \
	$(call TRY,$(CC) $(CFLAGS) $$($(1)_OBJ) -o $(1))
ALL_OBJS += $$($(1)_OBJ)
endef

define OBJ_template
$(1): $(2)
	@$(call BUILD,$(1)) ; \
	$(call TRY,$(CC) $(CFLAGS) -D $(shell echo $(1) | cut -d '.' -f1 | cut -d '/' -f2)=1 -c $(2) -o $(1))
endef

#
# RECIPES
#

all: $(PROGRAMS)

$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

# This is used to build two objects from the same cpp file
$(foreach obj,$(OBJECTS),$(eval $(call OBJ_template,$(obj),$(MAIN))))

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
