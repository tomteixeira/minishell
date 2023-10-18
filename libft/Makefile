# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 16:50:01 by toteixei          #+#    #+#              #
#    Updated: 2023/10/18 00:57:24 by hebernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
	ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c ft_strcmp.c ft_strlcpy.c \
	ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memcpy.c \
	ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
	ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
	ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
	ft_printf.c ft_treat_char.c ft_treat_string.c ft_treat_ptr.c \
	ft_treat_hexa.c ft_treat_uint.c ft_treat_int.c ft_lstnew.c \
	ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c get_next_line.c free.c ft_iswhitespace.c

INCLUDES	= libft.h

NAME    = libft.a

OBJ     = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	@echo "\n\n\033[0;32mCompiling libft..."
	ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[1A\033[K"

.c.o:
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	gcc -Wall -Wextra -Werror -g3 -c $< -I includes -o $@
	@printf "\033[1A\033[K"

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re
