NAME = libft.a

FLAGS =  -c -Wall -Wextra -Werror

SRCS = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	   ft_isprint.c ft_calloc.c ft_memcpy.c ft_memcmp.c ft_memchr.c \
	   ft_memmove.c ft_memset.c ft_atoi.c ft_strdup.c ft_strchr.c \
	   ft_strrchr.c ft_strlcat.c ft_strncmp.c ft_strnstr.c ft_strlcpy.c \
	   ft_strlen.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   get_next_line_yann.c ft_printf.c ft_printf_utils.c \
	   ft_strcmp.c

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   		 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	   		 ft_lstmap.c 

ALL_SRCS = $(SRCS)
OBJ = $(ALL_SRCS:.c=.o)
DIR_OBJ = objs_libft
OBJS = $(addprefix objs_libft/, $(OBJ))

ALL_SRCS_BONUS = $(SRCS) $(SRCS_BONUS)
OBJ_BONUS = $(ALL_SRCS_BONUS:.c=.o)
OBJS_BONUS = $(addprefix objs/, $(OBJ_BONUS))

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "                 compilation de libft.a OK"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: %.c
	@cc $(FLAGS) -o $@ -c $<

so:
	@cc -fPIC $(FLAGS) $(SRCS)
	@gcc -shared -o libft.so $(OBJ)

bonus: $(DIR_OBJ) $(OBJS_BONUS)
	@ar rc $(NAME) $(OBJS_BONUS)
	@ranlib $(NAME)
	@echo "                 compilation de libft.a (avec bonus) OK"

norme:
	@echo "\n<------------------Norminette------------------>\n"
	@norminette $(SRCS)
	@norminette -R CheckDefine $(INC)
	@echo "\n               NORMINETTE OK"

clean:
	@rm -rf $(DIR_OBJ)
	@echo "\n<------------------Folder Clean------------------>\n"
	@echo "                 Fichiers objets SUPPRIME"

fclean: clean
	@rm -f $(NAME)
	@echo "                 $(NAME) SUPPRIME"

re: fclean all

.PHONY: clean fclean re all bonus norme
