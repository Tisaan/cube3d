# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tseche <tseche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 23:39:11 by tseche            #+#    #+#              #
#    Updated: 2026/01/16 16:07:29 by tseche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = gnl.a
CFLAGS = -Wall -Werror -Wextra -g
CC	= cc
SRCS = ./get_next_line.c \
		./get_next_line_utils.c \

BONUS = get_next_line.c \
		get_next_line_utils.c \

OBJS = $(SRCS:%.c=%.o)
OBJSB = $(BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(OBJS) $(OBJSB)
	@ar rcs $(NAME) $(OBJS) $(OBJSB)
	
clean:
	@rm -rf $(OBJS) $(OBJSB)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re