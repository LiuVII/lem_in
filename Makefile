# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/22 09:34:02 by mfilipch          #+#    #+#              #
#    Updated: 2016/10/09 23:56:07 by mfilipch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem_in

FUNC0		=	main.c

FUNCS		+=	solve.c\
				print.c\
				read.c\
				servfunc.c\
				checks.c

LIBFT		=	./libft/libft.a
LIBINC		=	-I./libft
LIBLINK		=	-L./libft -lft

PRINTF		=	./ft_printf/libftprintf.a
PRINTFINC	=	-I./ft_printf/includes
PRINTFLINK	=	-L./ft_printf -lft

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror #-fsanitize=address
OBJ0		=	$(addprefix $(OBJS_DIR), $(FUNC0:.c=.o))
OBJS		=	$(addprefix $(OBJS_DIR), $(FUNCS:.c=.o))

INC_DIR		=	./includes/
OBJS_DIR	=	./build/

ifdef ALLOCWRAP
	LDFLAGS += ./alloc_wrap.c -ldl
endif 

.PHONY: all clean fclean re

all: $(NAME)

build:
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c | build
	@$(CC) $(CFLAGS) $(LIBINC) $(PRINTFINC) -I $(INC_DIR) -c $(FUNC0) -o $(OBJ0)
	@$(CC) $(CFLAGS) $(LIBINC) $(PRINTFINC) -I $(INC_DIR) -c $< -o $@

$(LIBFT):
	@make -C ./libft

$(PRINTF):
	@make -C ./ft_printf

$(NAME): $(LIBFT) $(PRINTF) $(OBJS) $(OBJ0) $(OBJ1)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ0) $(OBJS) $(LIBLINK) $(PRINTF)

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@make -C ./libft clean
	@make -C ./ft_printf clean
	@/bin/rm -f *.out
	@/bin/rm -f ._*
	@/bin/rm -f .DS*

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean
	@make -C ./ft_printf fclean

re: fclean all
