# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 14:10:52 by rihoy             #+#    #+#              #
#    Updated: 2024/04/17 09:39:13 by rihoy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#   NAME
NAME = lib.a

#--------------------------------------#
#		Commande
#-----------------------#
RM = rm -fr
CC = cc
FLAGS = -Wall -Werror -Wextra -g3

#--------------------------------------#
#       directory
#-----------------------#
OBJS = objs_lib

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
FILE_C =	get_next_line.c \
			lib_char.c \
			lib_check.c \
			lib_cmp.c \
			lib_free.c \
			lib_is.c \
			lib_join.c \
			lib_len.c \
			lib_sent.c \
			lib_split.c \
			lib_srch.c \
			lib_strdup.c \
			lib_write.c \
			lib_set.c \
			printf_error.c \
			nbr_base.c

FILE_O =	$(FILE_C:%.c=$(OBJS)/%.o)

#--------------------------------------#
#		Rules
#-----------------------#
all : $(NAME)
	@echo "$(C_G)Compilation lib STATUS [OK]$(RESET)"

$(NAME) : $(FILE_O)
	@ar rc $(NAME) $(FILE_O)

$(OBJS)/%.o : %.c
	@mkdir -p $(OBJS)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(C_B)loading : $(C_W)$< $(C_G)[OK]$(RESET)"

clean :
	@$(RM) $(OBJS)
	@echo "$(C_W)FILE '*.o' in $(C_R)LIB deleted$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(C_W)Extension $(C_R)$(NAME) deleted$(RESET)"

re : fclean all
