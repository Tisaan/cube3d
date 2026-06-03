# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tseche <tseche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 23:39:11 by tseche            #+#    #+#              #
#    Updated: 2026/06/03 18:21:38 by tseche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors ---
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
PURPLE := \033[0;35m
CYAN   := \033[0;36m
NC     := \033[0m # No Color

# --- Compilation ---
NAME = cub3D
CFLAGS = -Wall -Werror -Wextra -g -I mlx/includes
CC	= cc

# --- Directory ---

INC_DIR = ./includes

SRC_DIR = srcs
BONUS_DIR = bonus_

DIR = $(SRC_DIR)
ifeq ($(MAKECMDGOALS), bonus)
	DIR = $(BONUS_DIR)
endif

OBJ_DIR = ./obj/$(DIR)

ifeq ($(MAKECMDGOALS), bonus)
SRC_PARSING = 	path.c \
				parser.c \
				map.c \
				error.c \
				map_data.c \
				parser_utils.c \
				init.c \
				map_utils.c \
				map_utils2.c

SRC_UTILS =		free.c \
				debug.c \
				vectors.c \
				utils2.c \
				utils.c

SRC_RAYCAST =	player.c \
				render.c \
				ray.c \
				ray_utils.c \
				dda.c \
				objs.c

SRC_HOOKS = hooks.c

SRC_PLAYER = move.c \
			 rotate.c

SRC_GEN =   door_bonus.c \
			free_bonus.c \
			gen_seed_bonus.c \
			method_bonus.c \
			spawn_bonus.c \
			utils_bonus.c \
			utils2_bonus.c \
			utils3_bonus.c \
			utils4_bonus.c \
			wall_bonus.c

SUB_DIR = parsing utils hooks raycast player generation

else

SRC_PARSING = 	error.c \
				init.c \
				map_data.c \
				map_utils.c \
				map_utils2.c \
				map.c \
				parser_utils.c \
				parser.c \
				path.c \

SRC_UTILS =		free.c \
				debug.c \
				vectors.c \
				utils.c

SRC_RAYCAST =	player.c \
				render.c \
				ray.c \
				ray_utils.c \
				dda.c \
				objs.c

SRC_HOOKS = hooks.c

SRC_PLAYER = move.c \
			 rotate.c

SUB_DIR = parsing utils hooks raycast player

endif


VPATH := $(DIR) \
	$(addprefix $(DIR)/, $(SUB_DIR))


ifeq ($(MAKECMDGOALS), bonus)
	SRCS = main.c main_proc.c $(SRC_UTILS) $(SRC_PARSING) $(SRC_HOOKS) $(SRC_RAYCAST) $(SRC_PLAYER) $(SRC_GEN)
else
	SRCS = main.c $(SRC_PARSING) $(SRC_UTILS) $(SRC_HOOKS) $(SRC_RAYCAST) $(SRC_PLAYER)
endif

# --- MLX ---

#gere si MLX est pas present
MLXNAME = libmlx.so
MLXDIR = mlx
MLX = $(MLXDIR)/$(MLXNAME)

# --- LIBFT --- 

LIBNAME = libft.a
LIBDIR = libft
LIB = $(LIBDIR)/$(LIBNAME)
LIBMAKE =  $(MAKE) --no-print-directory -C $(LIBDIR) -j

# --- GNL ---

GNLNAME = gnl.a
GNLDIR = gnl
GNL = $(GNLDIR)/$(GNLNAME)
GNLMAKE = $(MAKE) --no-print-directory -C $(GNLDIR) -j


# --- LOGIC ---

OBJS = ${SRCS:%.c=$(OBJ_DIR)/%.o}

all:  libs $(NAME)

bonus: libs $(NAME)

libs:
	@printf "$(BLUE)📦 Building library in $(LIBDIR)...$(NC)\n"
	@$(LIBMAKE)
	@printf "$(BLUE)📦 Lib_ft created $(NC)\n"

	@printf "$(BLUE)📦 Building library in $(GNLDIR)...$(NC)\n"
	@$(GNLMAKE)
	@printf "$(BLUE)📦 GNL created $(NC)\n"
	
	@test -d "$(MLXDIR)" || git clone https://github.com/seekrs/MacroLibX.git mlx
	@printf "$(BLUE)📦 Building library in $(MLXDIR)...$(NC)\n"
	@make -s -C $(MLXDIR) -j
	@printf "$(BLUE)📦MLX created $(NC)\n"
	

$(NAME): $(OBJS)
	@printf "$(BLUE)🔗 Creating Executable $@...$(NC)\n"
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) $(MLX) -L$(LIBDIR) -l:$(LIBNAME) -L$(GNLDIR) -l:$(GNLNAME) -lm -lSDL2 -o $(NAME)
	@printf "$(GREEN)✅ Created $@$(NC)\n"
	
$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"
	
clean: libclean
	@printf "$(RED)🧹 Cleaning...$(NC)\n"
	@rm -rf ./obj/

libclean:
	@printf "$(RED)🧹 Cleaning... lib-ft$(NC)\n"
	@make -C $(LIBDIR) fclean --no-print-directory
	@printf "$(RED)🧹 Cleaning... GNL$(NC)\n"
	@make -C $(GNLDIR) fclean --no-print-directory
	@printf "$(RED)🧹 Cleaning... GNL$(NC)\n"
	@make -C $(MLXDIR) fclean --no-print-directory

fclean: clean libclean
	@printf "$(RED)🗑️ Removing Executable $(NAME)...$(NC)\n"
	@rm -rf $(NAME)

re: fclean all

help:
	@printf "$(PURPLE)=== Makefile Help ===$(NC)\n"
	@printf "$(PURPLE)all:$(NC) Build the library\n"
	@printf "$(PURPLE)clean:$(NC) Remove object files\n"
	@printf "$(PURPLE)fclean:$(NC) Remove object files and library\n"
	@printf "$(PURPLE)re:$(NC) Rebuild the library from scratch\n"
	@printf "$(PURPLE)help:$(NC) Show this help message\n"
	@printf "$(PURPLE)credit:$(NC) Show the people who help with this project\n"
	

.PHONY: all libs clean bonus libclean fclean re help
