# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 13:19:55 by mmardi            #+#    #+#              #
#    Updated: 2022/06/28 15:28:33 by mmardi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

FILES = commands.c get_next_line.c utils4.c unset.c cd.c\
		minishell.c mysplit.c utils.c utils2.c utils3.c\
		executable.c ft_split.c cmd.c  ft_putstr_fd.c\
		redirections.c redirections_2.c get_globals.c   ft_strjoin.c\
		export.c exp_utl.c parsing.c ft_exit.c ft_env.c\
		exp_utl2.c exp_utl3.c ft_env_utils.c handle_dollar.c\

HEADER = minishell.h

LFLAGS	=	-I /Users/$(USER)/.brew/opt/readline/include

OBJ = $(FILES:.c=.o)

all: $(NAME)
$(NAME): $(HEADER) $(OBJ)
	$(CC) $(CFLAGS) $(FILES)  $(LFLAGS) -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME) -lreadline
	
%.o : %.c
	@$(CC) $(LFLAGS)  -o $@  -c $^
clean:
	@rm -rf $(OBJ)
	
fclean: clean
	@rm -rf $(NAME)

re: fclean all