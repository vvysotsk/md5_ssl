#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/24 16:32:43 by vvysotsk          #+#    #+#              #
#    Updated: 2018/10/24 16:32:44 by vvysotsk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY : all clean fclean re

NAME = ft_ssl2

CFLAGS = -Wall -Werror -Wextra -I inc/

FILES =	src/main.c src/md5_helper.c src/md5_ssl.c src/md5_ssl_start.c src/md5_stack.c \
		src/parser.c src/sha_224.c src/sha_256.c src/sha_256_helper.c src/sha_384.c \
		src/sha_512.c src/sha_512_helper.c src/simpl_func.c\

OBJ = $(subst .c,.o, $(FILES))

LIBFT_FLAGS = -L ./libftprintf -l ftprintf

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ)
	@make -C ./libftprintf
	@gcc -I inc/ $(LIBFT_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32mft_ssl Created\033[0m"

clean: 
	@/bin/rm -rf $(OBJ)
	@make clean -C ./libftprintf/
	@echo "\033[32mObject Files Removed\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@make fclean -C ./libftprintf/
	@echo "\033[32mft_ssl Removed\033[0m"

re: fclean all
