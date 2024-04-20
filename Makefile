#   NAME
NAME = minishell

#---------------#
#	includes
#---------------#
UTILS =		utils
INCLUDES =	includes
DIR_YANN = 	libft

#--------------------------------------#
#		Commande
#-----------------------#
RM = rm -fr
CC = cc
FLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES) -I $(UTILS) -I $(DIR_YANN)
FLAG_READLINE = -lreadline

#--------------------------------------#
#       directory
#-----------------------#
SRCS = srcs
OBJS = objs_minishell
PARS = parsing

BUT = builtins
TOOLS = tools

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
			error_exit.c \
			free_shell.c \
			get_path.c \
			get_process.c \
			split_minishell.c \
			skip_part.c \
			insert_env.c \
			second_insert_env.c \
			utils_lst_split.c \
			utils_box.c \
			utils_box2.c \
			lst_split.c \
			utils_check_list.c \
			check_lst_split.c \
			utils_check_list_split.c \
			utils_parenthese.c \
			utils_parenthese2.c \
			check_redirection.c \
			creat_cmd.c \
			create_lstcmd.c \
			build_branch.c \
			new_tree.c \
			gestion_quote.c \
			free_essential.c \
			openning_file.c \
			redirection.c \
			closing_all.c \
			insert_env_here.c

SRC_PARS = $(addprefix $(SRCS)/$(PARS)/, $(PARS_C))
OBJ_PARS = $(patsubst %.c, $(OBJS)/%.o, $(PARS_C))

BUT_C =		cd.c \
			echo.c \
			env.c \
			exit.c \
			export.c \
			pwd.c \
			unset.c

SRC_BUT = $(addprefix $(SRCS)/$(BUT)/, $(BUT_C))
OBJ_BUT = $(patsubst %.c, $(OBJS)/%.o, $(BUT_C))

TOOL_C =	lst_utils.c \
			utils_minishell.c \
			utils2_minishell.c \
			utils_builtins.c \
			utils_exec.c \
			utils_signal.c \
			utils2_exec.c \
			signal_heredoc.c

SRC_TOOL = $(addprefix $(SRCS)/$(TOOLS)/, $(TOOL_C))
OBJ_TOOL = $(patsubst %.c, $(OBJS)/%.o, $(TOOL_C))

# **************************** #
#     LIB                      #
# **************************** #
LIB = $(UTILS)/lib.a
EXTENSION = $(UTILS)/lib.a

LIB_YANN = $(DIR_YANN)/libft.a
SEC_EXT = $(DIR_YANN)/libft.a

#--------------------------------------#
#		Rules
#-----------------------#
all : $(NAME)
	@echo "$(C_G)Compilation Minishell STATUS [OK]$(RESET)"

$(NAME) : $(LIB) $(LIB_YANN) $(OBJ_PARS) $(OBJ_BUT) $(OBJ_TOOL)
	@$(CC) $(FLAGS) -o $(NAME) main.c $(OBJ_PARS) $(OBJ_TOOL) $(OBJ_BUT) $(EXTENSION) $(SEC_EXT) $(FLAG_READLINE)

$(LIB_YANN) :
	@make -C $(DIR_YANN) --silent

$(LIB) :
	@make -C $(UTILS) --silent

$(OBJS)/%.o : $(SRCS)/$(PARS)/%.c
	@mkdir -p $(OBJS)
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(C_B)loading : $(RESET)$< $(C_G)[OK]$(RESET)"

$(OBJS)/%.o : $(SRCS)/$(BUT)/%.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(C_B)loading : $(RESET)$< $(C_G)[OK]$(RESET)"

$(OBJS)/%.o : $(SRCS)/$(TOOLS)/%.c
	@$(CC) $(FLAGS) -c $< -o $@
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
