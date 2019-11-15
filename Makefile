# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 00:16:40 by rpapagna          #+#    #+#              #
#    Updated: 2019/11/15 15:26:06 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= wolf3d

#COLORS
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
NC		= \033[0m

SRC		= main.c \
		game.c \
		render.c \
		inputs.c
UTIL	= init.c \
		del.c \
		parse.c
OUT		= out_console.c

FLAGS	= -Wall -Wextra -Werror
INC		= includes/wolf3d.h
RU_DEB	=_DEBUG_RULE_
INPUT = $(shell bash -c 'read -p "confirm (y/n) " pwd; echo $$pwd')

#MLX COMPILE ORDER
MLX_LNK	= -L libs/minilibx_macos -l mlx_macos -framework AppKit -framework OpenGL
#LIB COMPILE ORDER
FT_LNK	= -L libs/libft -l ft

OBJ_PATH= obj
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(OUT:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(UTIL:.c=.o))

.PHONY:	all clean fclean re debug

all:	$(NAME)

clean:
		@printf "[$(RED)clean   obj$(NC)]\t[:#         :]\r"
		@make -C libs/libft clean
		@printf "[$(RED)clean   obj$(NC)]\t[:#######   :]\r"
		@rm -f $(OBJ)
		@printf "[$(RED)clean   obj$(NC)]\t[:##########:]\n"

fclean: clean
		@make -C libs/libft fclean
		@rm -rf $(OBJ_PATH)
		@make -C libs/minilibx clean
		@printf "[$(RED)full  clean$(NC)]\t[:#######   :]\r"
		@make -C libs/minilibx_macos clean
		@printf "[$(RED)full  clean$(NC)]\t[:########  :]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)full  clean$(NC)]\t[:######### :]\r"
		@rm -rf $(NAME)
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\n"

re: fclean all

$(NAME): $(ARCHIVE) $(OBJ)
		@make -C libs/minilibx_macos
		@printf "[$(GREEN)$(NAME)$(NC) ]\t[:##        :]\r"
		@gcc $(FLAGS) $(OBJ_PATH)/*.o $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC) ]\t[:##########:]\n"
		@printf "usage: ./wolf3d [ file.map ]\n"

debug:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -D$(RU_DEB) $(FLAGS) -g $(addprefix src/,$(SRC)) $(addprefix src/output/,$(OUT)) $(addprefix src/utils/,$(UTIL)) $(MLX_LNK) $(FT_LNK) -I ./$(INC) -o $(NAME)
		@printf "[$(YELLOW)debug$(NC)]\t\t[:##########:]\n"

santitize:
#ifeq ($(INPUT),y)
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):#         :$(NC)]\r"
		@rm -rf $(NAME)
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##        :$(NC)]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):###       :$(NC)]\r"
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(addprefix src/output/,$(OUT)) $(addprefix src/utils/,$(UTIL)) $(MLX_LNK) $(FT_LNK) -I ./$(INC) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##########:$(NC)]\n"
#else
#		@printf "$(RED)Exit$(NC)\n"
#endif

q:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -Wall -Wextra -g $(addprefix src/,$(SRC)) $(addprefix src/output/,$(OUT)) $(addprefix src/utils/,$(UTIL)) $(MLX_LNK) $(FT_LNK) -I ./$(INC) -o $(NAME)

$(OBJ_PATH):
		@mkdir -p $@

$(OBJ_PATH)/%.o: src/output/%.c $(INC) | $(OBJ_PATH)
		@gcc $(FLAGS) -I ./$(INC) -o $@ -c $<
$(OBJ_PATH)/%.o: src/utils/%.c $(INC) | $(OBJ_PATH)
		@gcc $(FLAGS) -I ./$(INC) -o $@ -c $<
$(OBJ_PATH)/%.o: src/%.c $(INC) | $(OBJ_PATH)
		@gcc $(FLAGS) -I ./$(INC) -o $@ -c $<
$(ARCHIVE):
		@make -C libs/libft