#
# MAIN VARIABLES
#
DEPS		= $(shell find . -type f -name "*.hpp")
DEPS_DIR	= $(shell find . -type d)
#FILES		= $(shell find . -type f -name "*.cpp")
#OBJ		= $(FILES:%.cpp=%.o)
VECTOR_FILE	= tests/vector/main.cpp
STACK_FILE	= tests/stack/main.cpp
MAP_FILE	= tests/map/main.cpp
VECTOR_OBJ	= $(VECTOR_FILE:%.cpp=%.o)
STACK_OBJ	= $(STACK_FILE:%.cpp=%.o)
MAP_OBJ		= $(MAP_FILE:%.cpp=%.o)
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
# RECIPES
#

all: vector stack map

vector: $(DEPS) $(VECTOR_OBJ)
	@echo -e $(L_GRAY)Building $@...; \
	$(CC) $(CFLAGS) $(VECTOR_OBJ) -o $@ && \
	echo -e $(GREEN)[OK]$(L_GRAY) || \
	(echo -e $(RED)[FAIL]$(L_GRAY) && exit 1);

stack: $(DEPS) $(STACK_OBJ)
	@echo -e $(L_GRAY)Building $@...; \
	$(CC) $(CFLAGS) $(STACK_OBJ) -o $@ && \
	echo -e $(GREEN)[OK]$(L_GRAY) || \
	(echo -e $(RED)[FAIL]$(L_GRAY) && exit 1);

map: $(DEPS) $(MAP_OBJ)
	@echo -e $(L_GRAY)Building $@...; \
	$(CC) $(CFLAGS) $(MAP_OBJ) -o $@ && \
	echo -e $(GREEN)[OK]$(L_GRAY) || \
	(echo -e $(RED)[FAIL]$(L_GRAY) && exit 1);

%.o: %.cpp
	@echo -e $(L_GRAY)Building $<...; \
	$(CC) $(CFLAGS) -c $< -o $@ && \
	echo -e $(GREEN)[OK]$(L_GRAY) || \
	(echo -e $(RED)[FAIL]$(L_GRAY) && exit 1);

clean:
	@echo -ne $(YELLOW)
	rm -f $(shell find . -type f -name "*.o")
	@echo -ne $(L_GRAY)

fclean: clean
	@echo -ne $(YELLOW)
	rm -f vector stack map
	@echo -ne $(L_GRAY)

re: fclean all

.PHONY: all clean fclean re
