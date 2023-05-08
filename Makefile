# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 17:07:45 by tmarts            #+#    #+#              #
#    Updated: 2023/04/29 14:36:20 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
NAME_BONUS = pipex
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g3
LDFLAGS = -lm
# LDFLAGS += -fsanitize=address -g3
LIBFT	= ./libft
HEADERS = -I $(LIBFT)
LIBS	= $(LIBFT)/libft.a
SRC_DIR	= ./src/
SRCS	= $(addprefix $(SRC_DIR)/, \
main.c \
pipex_utils.c \
pipex_utils2.c \
parser.c \
errors.c \
pipex_initiate.c \
pipex_free.c \
pipex.c)

SRC_DIR_BONUS	= ./bonus/
SRCS_BONUS	= $(addprefix $(SRC_DIR_BONUS)/, \
main_bonus.c \
pipex_utils_bonus.c \
pipex_utils2_bonus.c \
parser_bonus.c \
errors_bonus.c \
pipex_initiate_bonus.c \
pipex_free_bonus.c \
here_doc_bonus.c \
pipex_bonus.c)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)


%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) ${LDFLAGS}

bonus: libft $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS) ${LDFLAGS}
	
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(OBJS_BONUS)
	
fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	
re: fclean all

.PHONY: all, clean, fclean, re, libft
