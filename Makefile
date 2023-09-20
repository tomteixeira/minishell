# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 16:32:28 by toteixei          #+#    #+#              #
#    Updated: 2023/09/20 15:26:20 by toteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= 	minishell
SRCS 		=	main.c sources/lexer/lexer.c sources/lexer/len_fonctions.c \
				sources/lexer/token.c sources/parser/parser.c sources/parser/node.c \
				sources/parser/redirection.c
				
OBJ 		= 	$(SRCS:.c=.o)

CC			= 	cc
LIBFT 		= 	libft
RM			=	rm -f
LIB 		= 	libft.a
INCLUDES	=	-I libft

CFLAGS 		= 	-Wall -Wextra -Werror -g3

all : libs $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -o $(NAME)

%.o : %.c minishell.h Makefile
		$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@


libs:
		@$(MAKE) -C $(LIBFT)

clean:
		@$(RM) $(OBJ)
		@$(MAKE) clean -C $(LIBFT)

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) fclean -C $(LIBFT)

re:		fclean all

.PHONY: all libs clean fclean re