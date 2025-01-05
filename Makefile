##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for my_printf project
##

SRC = $(shell find . -type f -name "*.c")
INCLUDE_H := $(shell find include -type d)
INCLUDE = $(INCLUDE_H:%=-I%)
OBJ = 	$(SRC:%.c=build/%.o)
OBJ_DEBUG = $(SRC:%.c=build-debug/%.o)
OBJ_OPTIMIZATION = $(SRC:%.c=build-optimization/%.o)
CFLAGS += 	-lcsfml-audio -lcsfml-graphics -lcsfml-window \
			-lcsfml-network -lcsfml-system -Wextra -Wall -lm $(INCLUDE)
DEBUG_FLAGS = 	-fsanitize=address -g3 -lcsfml-audio -lcsfml-graphics \
				-lcsfml-window -lcsfml-network -lcsfml-system \
				-Wextra -Wall -lm $(INCLUDE)
OPTIMIZATION_FLAGS = 	-fsanitize=address -g -pg -lcsfml-audio \
						-lcsfml-graphics -lcsfml-window -lcsfml-network \
						-lcsfml-system -Wextra -Wall -lm $(INCLUDE)

NAME = my_radar
DEBUG_NAME = debug
OPTIMIZATION_NAME = optimization

all: $(NAME)

build/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $< -o $@

build-debug/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(DEBUG_FLAGS) -c $< -o $@

build-optimization/%.o: %.c
	mkdir -p $(dir $@)
	gcc $(OPTIMIZATION_FLAGS) -c $< -o $@

$(NAME): $(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

$(DEBUG_NAME): $(OBJ_DEBUG)
	gcc -o $(DEBUG_NAME) $(OBJ_DEBUG) $(DEBUG_FLAGS)

$(OPTIMIZATION_NAME): $(OBJ_OPTIMIZATION)
	gcc -o $(OPTIMIZATION_NAME) $(OBJ_OPTIMIZATION) $(OPTIMIZATION_FLAGS)

clean:
	$(shell find . -type f -name "*.o" -delete)

fclean:
	rm -f $(NAME)
	rm -f $(DEBUG_NAME)
	rm -f $(OPTIMIZATION_NAME)
	rm -rf build-optimization
	rm -rf build-debug
	rm -rf build

re: fclean all
