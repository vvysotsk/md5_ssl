#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 17:07:41 by vvysotsk          #+#    #+#              #
#    Updated: 2018/10/02 17:07:42 by vvysotsk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY : all clean fclean clean re

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror -I ../inc/

FILES =	printf/ft_printf.c printf/bonus.c printf/form_out.c \
		printf/handler.c printf/help_handler.c printf/num.c \
		printf/num_help.c printf/parser.c printf/str.c printf/uni.c \
		printf/wstr.c printf/identify.c printf/simple_func.c \

LIBFILES =	ft_atoi.c ft_bzero.c ft_count_char.c  ft_count_str.c ft_find_char.c \
		ft_find_nword.c ft_imaxtoa.c ft_int_len.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_itoa_base.c \
		ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
		ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
		ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_realloc.c ft_recalloc.c \
		ft_save_str.c ft_save_to_str.c ft_strcat.c ft_strchr.c ft_strclr.c \
		ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c \
		ft_striter.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
		ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strndup.c \
		ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
		ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
		ft_uimaxtoa_base.c get_next_line.c my_pad.c my_write.c stnchr.c \

OBJ = $(FILES:.c=.o)
LIBOBJ = $(LIBFILES:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(LIBOBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): $(LIBOBJ) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBOBJ)
	@echo "\033[32mlibftprintf.a created\033[0m"

clean:
	@rm -rf $(OBJ) $(LIBOBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
