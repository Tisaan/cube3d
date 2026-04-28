# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tseche <tseche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 23:39:11 by tseche            #+#    #+#              #
#    Updated: 2026/04/28 19:38:02 by tseche           ###   ########.fr        #
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
CFLAGS = -Wall -Werror -Wextra -g 
CC	= cc

# --- Directory ---

SRC_DIR = ./srcs/
SUB_DIR = parsing graphic

VPATH = $(SRC_DIR) \
	$(addprefix $(SRC_DIR)/, $(SUB_DIR))

SRC_PARSING = utils.c
SRC_GRAPHIC = 

SRCS = main.c $(SRC_PARSING) $(SRC_GRAPHIC)

# --- MLX ---

#gere si MLX est pas present
MLXNAME = libmlx.a
MLXDIR = ./mlx_linux
MLX = $(MLXDIR)/$(MLXNAME)
MLXMAKE = $(MAKE) --no-print-directory -C $(MLXDIR) -j

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

OBJS = $(SRCS:%.c=%.o)

all:  libs $(NAME)

libs:
	@echo "$(BLUE)📦 Building library in $(LIBDIR)...$(NC)"
	@$(LIBMAKE)
	@echo "$(BLUE)📦 Lib_ft created $(NC)"
	@echo "$(BLUE)📦 Building library in $(GNLDIR)...$(NC)"
	@$(GNLMAKE)
	@echo "$(BLUE)📦 GNL created $(NC)"
	@test -d "$(MLXDIR)" || git clone https://github.com/42paris/minilibx-linux.git mlx_linux --depth=1
	@echo "$(BLUE)📦 Building library in $(MLXDIR)...$(NC)"
	@$(MLXMAKE)
	@echo "$(BLUE)📦MLX created $(NC)"
	

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Creating Executable $@...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLXDIR) -l:$(MLXNAME) -lX11 -lm -lXext -L$(LIBDIR) -l:$(LIBNAME) -L$(GNLDIR) -l:$(GNLNAME) -o $(NAME)
	@echo "$(GREEN)✅ Created $@$(NC)"
	
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean: libclean
	@echo "$(RED)🧹 Cleaning...$(NC)"
	@rm -rf $(OBJS)

libclean:
	@echo "$(RED)🧹 Cleaning... lib-ft$(NC)"
	@make -C $(LIBDIR) fclean --no-print-directory
	@echo "$(RED)🧹 Cleaning... GNL$(NC)"
	@make -C $(GNLDIR) fclean --no-print-directory

fclean: clean libclean
	@echo "$(RED)🗑️ Removing Executable $(NAME)...$(NC)"
	@rm -rf $(NAME)

re: fclean all

help:
	@echo "$(PURPLE)=== Makefile Help ===$(NC)"
	@echo "$(PURPLE)all:$(NC) Build the library"
	@echo "$(PURPLE)clean:$(NC) Remove object files"
	@echo "$(PURPLE)fclean:$(NC) Remove object files and library"
	@echo "$(PURPLE)re:$(NC) Rebuild the library from scratch"
	@echo "$(PURPLE)help:$(NC) Show this help message"
	@echo "$(PURPLE)credit:$(NC) Show the people who help with this project"
	

.PHONY: all libs clean libclean fclean re help