#   NAME
NAME = minishell

#--------------------------------------#
#		Commande
#-----------------------#
RM = rm -fr
CC = cc
FLAGS = -Wall -Werror -Wextra -g
FLAG_READLINE = -lreadline

#--------------------------------------#
#       directory
#-----------------------#
SRCS = srcs
OBJS = objs_minishell
PARS = parsing

BUT = builtins
TOOLS = tools
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
PARS_C =	condition_launch.c \
				get_path.c \
				error_exit.c \
				get_process.c \
				check_str.c \
				free_lst.c \
				free_shell.c \
				infopars.c \
				lst_cmd.c \
				split_minishell.c

BUT_C = 		cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c

TOOLS_C = 		lst_utils.c \
				test_execution.c \
				utils2_minishell.c \
				utils_minishell.c
#				# $(SRCS)/$(TOOLS)/
#				# $(SRCS)/$(TOOLS)/
#				# $(SRCS)/$(TOOLS)/
#				# $(SRCS)/
#				# $(SRCS)/


# FILE_MAIN_C = main.c

SRC =		$(addprefix $(SRCS)/$(PARS)/, $(PARS_C)) \
			$(addprefix $(SRCS)/$(BUT)/, $(BUT_C)) \
			$(addprefix $(SRCS)/$(TOOLS)/, $(TOOLS_C))

OBJ = $(patsubst %.c,%.o,$(SRC))

# **************************** #
#     LIB                      #
# **************************** #
UTILS = utils
LIB = $(UTILS)/lib.a
EXTENSION = $(UTILS)/lib.a

DIR_YANN = libft
LIB_YANN = $(DIR_YANN)/libft.a
SEC_EXT = $(DIR_YANN)/libft.a

#--------------------------------------#
#		Rules
#-----------------------#
all : $(NAME)
	@echo "$(C_G)Compilation Minishell STATUS [OK]$(RESET)"

$(NAME) : $(LIB) $(LIB_YANN) $(OBJ)
	@$(CC) $(FLAGS) $(FLAG_READLINE) -o $(NAME) main.c -I $(INCLUDES) -I $(UTILS) $(EXTENSION) -I $(DIR_YANN) $(SEC_EXT) $(OBJ)

$(LIB_YANN) :
	@make -C $(DIR_YANN) --silent

$(LIB) :
	@make -C $(UTILS) --silent

$(OBJS)/%.o : $(SRCS)/%.c
	@mkdir -p $(OBJS)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES) -I $(UTILS) -I $(DIR_YANN)
	@echo "$(C_B)loading : $(RESET)$< $(C_G)[OK]$(RESET)"

clean :
	@$(RM) $(OBJS)
	@make clean -C $(DIR_YANN) --silent
	@make clean -C $(UTILS) --silent
	@echo "$(C_R)FILE '*.o' for $(NAME) deleted$(RESET)"

fclean :
	@$(RM) $(NAME)
	@$(RM) $(OBJS)
	@make fclean -C $(UTILS) --silent
	@make fclean -C $(DIR_YANN) --silent
	@echo "$(C_W)FILE '*.o' for $(C_R)$(NAME) deleted$(RESET)"
	@echo "Projet $(C_R)$(NAME) deleted$(RESET)"

re : fclean all

.PHONY : re clean fclean all
