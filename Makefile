# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 16:32:28 by toteixei          #+#    #+#              #
#    Updated: 2023/11/16 17:14:47 by tomteixeira      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= 	minishell
SRCS 		=	main.c sources/lexer/lexer.c sources/lexer/len_fonctions.c \
				sources/lexer/token.c sources/parser/parser.c sources/parser/node.c \
				sources/parser/redirection.c sources/lexer/check_parsing.c \
				sources/handling_error/ft_free.c \
				sources/lexer/check_parsing_utils.c \
				sources/execution/execution_main.c \
				sources/execution/execution_builtins.c \
				sources/execution/execution_assignment.c \
				sources/execution/execution_assignment_utils.c \
				sources/execution/execution_error.c \
				sources/execution/execution_exec.c \
				sources/execution/execution_redirection.c \
				sources/execution/execution_heredoc.c \
				sources/execution/execution_path.c \
				sources/execution/execution_fork.c \
				sources/execution/execution_signal.c \
				sources/execution/execution_utils.c \
				sources/execution/execution_utils_2.c \
				sources/execution/execution_utils_3.c \
				sources/execution/execution_expansion.c \
				sources/execution/execution_expansion_bis.c \
				sources/execution/execution_expansion_ter.c \
				sources/builtins/cd.c \
				sources/builtins/pwd.c \
				sources/builtins/echo.c \
				sources/builtins/export.c \
				sources/builtins/unset.c \
				sources/builtins/env.c \
				sources/builtins/exit.c \
				sources/signal.c \
				sources/prompt.c

OBJ 		= 	$(SRCS:.c=.o)

CC			= 	cc
LIBFT 		= 	libft
RM			=	rm -f
LIB 		= 	libft.a
INCLUDES	=	-I libft -I /opt/homebrew/opt/readline/include
RLLIBS		=	-L /opt/homebrew/opt/readline/lib -lreadline

CFLAGS 		= 	-Wall -Wextra -Werror

all : libs $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -o $(NAME) $(RLLIBS) $(INCLUDES)

%.o : %.c minishell.h Makefile
		$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@


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
