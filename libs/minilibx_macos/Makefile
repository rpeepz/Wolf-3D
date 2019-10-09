#
#
RED		= \033[0;31m
CYN		= \033[0;36m
NC		= \033[0m
NAME	= libmlx_macos.a
OBJ_PATH= obj

SRC		= mlx_shaders.c \
		mlx_xpm.c \
		mlx_int_str_to_wordtab.c

SRM		= mlx_new_window.m \
		mlx_init_loop.m \
		mlx_new_image.m

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))
OBJ += $(addprefix $(OBJ_PATH)/,$(SRM:.m=.o))
CFLAGS+=-O2

all: $(NAME)

$(NAME):$(OBJ)
	@printf "[make    mlx]\t[:########  :]\r"
	@ar -rcs $(NAME) $(OBJ)
	@printf "[$(CYN)make    mlx$(NC)]\t[:##########:]\n"

$(OBJ_PATH):
	@printf "[$(CYN)make    mlx$(NC)]\t[:#         :]\r"
	@mkdir -p $@

$(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	@printf "[make    mlx]\t[:###       :]\r"
	@cc -w $(CFLAGS) -o $@ -c $<
$(OBJ_PATH)/%.o: %.m | $(OBJ_PATH)
	@printf "[make    mlx]\t[:######    :]\r"
	@cc -w $(CFLAGS) -o $@ -c $<


clean:
	@printf "[rm      obj]\t[:####      :]\r"
	@rm -f $(NAME) $(OBJ) *~
	@rm -rf $(OBJ_PATH)
	@rm -f mlx_app
	@printf "[$(RED)clean   mlx$(NC)]\t[:##########:]\n"

re: clean all
