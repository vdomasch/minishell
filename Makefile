NAME				=	minishell

SRCS_DIR			=	sources

OBJS_DIR			=	.objs

HEADER_DIR			=	includes

FILES				=	test.c				\
					

OBJS				=	$(FILES:%.c=$(OBJS_DIR)/%.o)

HEADERS				=	$(HEADER_DIR)/$(NAME).h

CC					=	cc -lreadline

FLAGS				=	-Wall -Werror -Wextra

RL_FLAGS			=	-lreadline

all:				$(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HEADERS)
						$(CC) $(FLAGS) -c $< -o $@

$(NAME):			$(OBJS_DIR) $(OBJS) $(HEADERS)
						$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(RL_FLAGS)

$(OBJS_DIR):
						mkdir -p $(OBJS_DIR)

clean:
						rm -rf $(OBJS_DIR)

fclean:
						$(MAKE) clean
						rm -rf $(NAME)

re:
						$(MAKE) fclean all

.PHONY: all clean fclean re
