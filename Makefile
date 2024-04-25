NAME				=	minishell

SRCS_DIR			=	sources

OBJS_DIR			=	.objs

HEADER_DIR			=	includes

DLIB				=	libft

FILES				=	main.c							\
						read_command_line.c				\
						minishell_utils.c				\
						signals.c						\
						env_list.c						\
						exec.c							\
						pipes.c							\
						process_env.c					\
							parsing/process_message.c	\
							parsing/dollars.c			\
							parsing/redirections.c		\
							parsing/quotes_utils.c		\
							parsing/pipes_checks.c		\
							parsing/command_utils.c		\
							parsing/split_arguments.c

OBJS				=	$(FILES:%.c=$(OBJS_DIR)/%.o)

HEADERS				=	$(HEADER_DIR)/$(NAME).h

CC					=	cc

FLAGS				=	-Wall -Werror -Wextra

RL_FLAGS			=	-lreadline

all:				libft $(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HEADERS)
						$(CC) $(FLAGS) -c $< -o $@

$(NAME):			$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a
						$(CC) $(FLAGS) $(OBJS) $(DLIB)/libft.a -o $(NAME) $(RL_FLAGS)

$(OBJS_DIR):
						mkdir -p $(OBJS_DIR)
						mkdir -p $(OBJS_DIR)/parsing

libft:
						$(MAKE) -C $(DLIB)

clean:
						rm -rf $(OBJS_DIR)
						$(MAKE) clean -C $(DLIB)

fclean:
						$(MAKE) clean
						rm -rf $(NAME)
						$(MAKE) fclean -C $(DLIB)

re:
						$(MAKE) fclean all

.PHONY: all clean fclean re libft
