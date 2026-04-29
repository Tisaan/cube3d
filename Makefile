# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tseche <tseche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 23:39:11 by tseche            #+#    #+#              #
#    Updated: 2026/04/29 11:53:15 by pcaplat          ###   ########.fr        #
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

OBJ_DIR = ./obj

INC_DIR = ./includes

SRC_DIR = ./srcs/
SUB_DIR = parsing graphic

VPATH = $(SRC_DIR) \
	$(addprefix $(SRC_DIR)/, $(SUB_DIR))

SRC_PARSING = utils.c
SRC_GRAPHIC = 

SRCS = main.c $(SRC_PARSING) $(SRC_GRAPHIC)

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
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJS) $(MLX) -L$(LIBDIR) -l:$(LIBNAME) -L$(GNLDIR) -l:$(GNLNAME) -lSDL2 -o $(NAME)
	@printf "$(GREEN)✅ Created $@$(NC)\n"
	
$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean: libclean
	@printf "$(RED)🧹 Cleaning...$(NC)\n"
	@rm -rf $(OBJS)

libclean:
	@printf "$(RED)🧹 Cleaning... lib-ft$(NC)\n"
	@make -C $(LIBDIR) fclean --no-print-directory
	@printf "$(RED)🧹 Cleaning... GNL$(NC)\n"
	@make -C $(GNLDIR) fclean --no-print-directory

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
	

.PHONY: all libs clean libclean fclean re help
