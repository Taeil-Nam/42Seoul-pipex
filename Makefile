# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnam <tnam@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 16:17:47 by tnam              #+#    #+#              #
#    Updated: 2023/02/04 20:23:06 by tnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 수정 필요 (2023/02/04)
# - 꼭 오브젝트 파일로 만들어서 링크 시켜줘야 하는지?

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

SRCS_B_DIR		=	./sources_m/
SRCS_B			=	pipex.c			\
					pipex_child.c	\
					pipex_parent.c	\
					pipex_utils.c

LIBFT_DIR		=	./libft/
LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_COMPILE	=	-L $(LIBFT_DIR) -l$(LIBFT)

BONUS_MODE = $(findstring $(MAKECMDGOALS),bonus)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(SRCS_M_DIR)$(SRCS_M) $(LIBFT) $(if $(BONUS_MODE),$(SRCS_M_DIR)$(SRCS_B))
	$(CC) $(CFLAG) $(SRCS_M_DIR)$(SRCS_M) $(LIBFT_COMPILE) -o $(NAME)

clean :
	$(RM) $(OBJS_M) $(OBJS_B)

fclean : clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY : all clean fclean re bonus