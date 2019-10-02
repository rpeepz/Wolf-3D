# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 00:16:40 by rpapagna          #+#    #+#              #
#    Updated: 2019/10/01 05:40:13 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= wolf3d

#COLORS
GREEN	= \033[0;32m
RED	= \033[0;31m
YELLOW	= \033[0;33m
NC	= \033[0m

SRC		= main.c \
		init.c \
		render.c \
		inputs.c

OUT		= help_text.c

FLAGS	= -Wall -Wextra -Werror
INC		= -I ./includes/
#MLX COMPILE ORDER
MLX_LNK	= -L ./minilibx_macos -l mlx_macos -framework AppKit -framework OpenGL
#LIB COMPILE ORDER
FT_LNK	= -L ./libft -l ft

#extra paths
OUT_PATH= output
OBJ_PATH= obj
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(OUT:.c=.o))

.PHONY:	all clean fclean re debug

all:	$(NAME)

clean:
		@make -C libft clean
		@printf "[$(RED)clean   mlx$(NC)]\t[:######    :]\r"
		@rm -f $(OBJ)
		@printf "[$(RED)clean   mlx$(NC)]\t[:##########:]\n"

fclean: clean
		@make -C libft fclean
		@rm -rf $(OBJ_PATH)
		@make -C minilibx clean
		@printf "[$(RED)full  clean$(NC)]\t[:#######   :]\r"
		@make -C minilibx_macos clean
		@printf "[$(RED)full  clean$(NC)]\t[:########  :]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)full  clean$(NC)]\t[:######### :]\r"
		@rm -rf $(NAME)
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\n"

re: fclean all

$(NAME):$(OBJ)
		@make -C libft
		@make -C minilibx_macos
		@printf "[$(GREEN)$(NAME)$(NC) ]\t[:##        :]\r"
		@gcc $(FLAGS) $(OBJ_PATH)/*.o $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC) ]\t[:##########:]\n"
		@printf "usage: ./wolf3d [ ]\n"

debug:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(addprefix src/output/,$(OUT)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME)
		@printf "[$(YELLOW)debug   $(NC)]\t[:##########:]\n"

sanitize:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(addprefix src/output/,$(OUT)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##########:$(NC)]\n"

q:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -Wall -Wextra -g $(addprefix src/,$(SRC)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME)

$(OBJ_PATH):
		@mkdir -p $@

$(OBJ_PATH)/%.o: src/%.c | $(OBJ_PATH)
		@gcc $(FLAGS) $(INC) -o $@ -c $<
$(OBJ_PATH)/%.o: src/output/%.c | $(OBJ_PATH)
		@gcc $(FLAGS) $(INC) -o $@ -c $<
