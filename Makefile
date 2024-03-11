# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 09:09:09 by yrio              #+#    #+#              #
#    Updated: 2024/02/19 11:57:43 by yrio             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g3
FLAG_READLINE = -lreadline
ARCHIVE = libft/libft.a
BUILTINS = cd.c env.c unset.c export.c pwd.c echo.c exit.c
MAIN = main.c
TOOLS = utils_minishell.c lst_utils.c utils2_minishell.c
SRC = $(addprefix srcs/builtins/, $(BUILTINS)) \
		$(addprefix srcs/main/, $(MAIN)) \
		$(addprefix srcs/tools/, $(TOOLS))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAG_READLINE) $(FLAGS) -o $(NAME) $(OBJ) $(ARCHIVE) -lm	

%.o: %.c
	make bonus -C libft
	cc $(FLAGS) -g -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus