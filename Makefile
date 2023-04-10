# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 17:07:45 by tmarts            #+#    #+#              #
#    Updated: 2023/04/10 19:12:49 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LIBFT	= ./libft
HEADERS = -I $(LIBFT)
LIBS	= $(LIBFT)/libft.a
SRC_DIR	= ./src/
SRCS	= $(addprefix $(SRC_DIR)/, \
main.c \
path.c \
pipex_utils.c \
pipex.c)

OBJS	= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) fclean

fclean:	clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all, clean, fclean, re, libft
