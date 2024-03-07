# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 15:04:08 by rihoy             #+#    #+#              #
#    Updated: 2024/03/07 13:49:52 by rihoy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#   NAME
NAME = minishell

#--------------------------------------#
#		Commande
#-----------------------#
RM = rm -fr
CC = cc
FLAGS = -Wall -Werror -Wextra -g

#--------------------------------------#
#       directory
#-----------------------#
SRCS = srcs
OBJS = objs_minishell
PARS = parsing
#---------------#
#	includes
#---------------#
INCLUDES =	includes 

#--------------------------------------#
#       Colors
#-----------------------#
C_B = \033[0;30m
C_R = \033[1;31m
C_G = \033[1;32m
C_Y = \033[0;33m
C_BU = \033[0;34m
C_M = \033[0;35m
C_C = \033[0;36m
C_W = \033[0;37m
RESET = \033[0m

#--------------------------------------#
#		File
#-----------------------#
FILE_PARS_C =	$(SRCS)/$(PARS)/condition_launch.c \
				$(SRCS)/$(PARS)/get_path.c \
				$(SRCS)/$(PARS)/error_exit.c \
				$(SRCS)/$(PARS)/get_process.c \
				$(SRCS)/$(PARS)/check_str.c \
				$(SRCS)/$(PARS)/free_lst.c \
				$(SRCS)/$(PARS)/free_shell.c \
				$(SRCS)/$(PARS)/infopars.c \
				$(SRCS)/$(PARS)/lst_cmd.c

# FILE_MAIN_C = main.c

FILE_O =	$(FILE_PARS_C:$(SRCS)/$(PARS)/%.c=$(OBJS)/%.o)


# **************************** #
#     LIB                      #
# **************************** #
UTILS = utils
LIB = $(UTILS)/lib.a
EXTENSION = $(UTILS)/lib.a

#--------------------------------------#
#		Rules
#-----------------------#
all : $(NAME)
	@echo "$(C_G)Compilation Minishell STATUS [OK]$(RESET)"

$(NAME) : $(LIB) $(FILE_O)
	@$(CC) $(FLAGS) $(FILE_O) -o $(NAME) main.c -I $(INCLUDES) -I $(UTILS) $(EXTENSION)

$(LIB) :
	@make -C $(UTILS) --silent

$(OBJS)/%.o : $(SRCS)/$(PARS)/%.c
	@mkdir -p $(OBJS)
	@$(CC) $(FLAGS) -I $(INCLUDES) -I $(UTILS) -c $< -o $@
	@echo "$(C_B)loading : $(RESET)$< $(C_G)[OK]$(RESET)"

clean :
	@$(RM) $(OBJS)
	@make clean -C $(UTILS) --silent
	@echo "$(C_R)FILE '*.o' for $(NAME) deleted$(RESET)"

fclean :
	@$(RM) $(NAME)
	@$(RM) $(OBJS)
	@make fclean -C $(UTILS) --silent
	@echo "$(C_W)FILE '*.o' for $(C_R)$(NAME) deleted$(RESET)"
	@echo "Projet $(C_R)$(NAME) deleted$(RESET)"

re : fclean all

.PHONY : re clean