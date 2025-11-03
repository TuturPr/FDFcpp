# **************************************************************************** #
#                                                                              #
#                                                                              #
#    Makefile                                          *        *        *     #
#                                                      * *    *   *    * *     #
#    By: arthur <arthur@student.42.fr>                 *    *       *    *     #
#                                                      *                 *     #
#    Created: 2025/03/04 17:23:35 by arthur            *                 *     #
#    Updated: 2025/11/03 17:06:33 by arthur            *******************     #
#                                                                              #
# **************************************************************************** #

# Variables

NAME = fdf

INCLUDE = includes
MLX = libs/MLX42
LIBS = -Iinclude $(MLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I $(INCLUDE) -g

GREEN = \033[32m
RED = \033[31m
DEF_COLOR = \033[0m

# Sources

include Sources.mk

SRC_DIR = ./src

SRC = $(SRC_MAIN)

OBJS = $(SRC:.cpp=.o)

# Fonctions

all: libmlx $(NAME)
	@echo "$(GREEN)Compilation successful !$(DEF_COLOR)"

libmlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4 || \
		(echo "$(RED)Error in libmlx compilation!$(DEF_COLOR)" && exit 1)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(NAME) || \
		(echo "$(RED)Error during linking!$(DEF_COLOR)" && exit 1)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ || (echo "$(RED)Error compiling $<!$(DEF_COLOR)" && exit 1)

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Clean successful !$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX)/build
	@echo "$(GREEN)Full clean successful !$(DEF_COLOR)"

re: fclean all

norminette:
	@norminette $(SRC_DIR)| grep -Ev '^Notice|OK!$$'	\
	&& bash -c 'echo -e "\033[1;31mNorminette KO!"'						\
	|| bash -c 'echo -e "\033[1;32mNorminette OK!"'

.PHONY: all clean fclean re
