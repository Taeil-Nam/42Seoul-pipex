# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 16:17:47 by tnam              #+#    #+#              #
#    Updated: 2023/02/03 17:44:12 by tnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 수정 필요 (2023/02/03)
NAME			=	pipex

CC				=	cc
CFLAG			=	-Wall -Wextra -Werror

RM				=	rm -f

HEADERS_DIR		=	./includes/
HEADERS			=	$(HEADERS_DIR)pipex.h

SRCS_M_DIR		=	./sources_m/
SRCS_M			=	pipex.c			\
					pipex_child.c	\
					pipex_parent.c	\
					pipex_utils.c

LIBFT_DIR		=	./libft/
LIBFT_HEADERS	=	$(LIBFT_DIR)libft.h
LIBFT			=	$(LIBFT_DIR)libft.a

BONUS_MODE = $(findstring $(MAKECMDGOALS),bonus)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(SRCS_M_DIR)$(SRCS_M) $(LIBFT) $(if $(BONUS_MODE),$(SRCS_B))
	$(AR) $(ARFLAG) $@ $^

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	$(RM) $(OBJS_M) $(OBJS_B)

fclean : clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re bonus