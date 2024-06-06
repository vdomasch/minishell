NAME				=	minishell

SRCS_DIR			=	sources

OBJS_DIR			=	.objs

HEADER_DIR			=	includes

DLIB				=	libft

FILES				=	main.c										\
						read_command_line.c							\
						minishell_utils.c							\
						signals.c									\
						process_message.c							\
							environment/env_list.c					\
							environment/env_array.c					\
							environment/process_env.c				\
							execution/exec.c						\
							execution/exec_child.c					\
							execution/exec_redirections.c			\
							execution/exec_redirections_utils.c		\
							execution/in_out_redirection.c			\
							execution/heredoc_redirection.c			\
							execution/pipes.c						\
							execution/builtins/ft_pwd.c				\
							execution/builtins/ft_echo.c			\
							execution/builtins/ft_env.c				\
							execution/builtins/ft_exit.c			\
							execution/builtins/ft_export.c			\
							execution/builtins/ft_export_child.c	\
							execution/builtins/ft_cd.c				\
							execution/builtins/ft_unset.c			\
							parsing/dollars.c						\
							parsing/dollars_size.c					\
							parsing/redirections.c					\
							parsing/redirections_checks.c			\
							parsing/quotes_utils.c					\
							parsing/pipes_checks.c					\
							parsing/command_utils.c					\
							parsing/split_arguments.c				\
							parsing/split_arguments_utils.c

OBJS				=	$(FILES:%.c=$(OBJS_DIR)/%.o)

HEADERS				=	$(HEADER_DIR)/$(NAME).h						\
						$(HEADER_DIR)/error_messages.h

CC					=	cc

FLAGS				=	-Wall -Werror -Wextra

DFLAGS				=	-fsanitize=address -g3

RL_FLAGS			=	-lreadline

ifeq ($(DEBUG),true)
	FLAGS = -Wall -Werror -Wextra $(DFLAGS)
endif

all:				libft $(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HEADERS)
						$(CC) $(FLAGS) -c $< -o $@

$(NAME):			$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a Makefile
						$(CC) $(FLAGS) $(OBJS) $(DLIB)/libft.a -o $(NAME) $(RL_FLAGS)

$(OBJS_DIR):
						mkdir -p $(OBJS_DIR)
						mkdir -p $(OBJS_DIR)/environment
						mkdir -p $(OBJS_DIR)/execution
						mkdir -p $(OBJS_DIR)/execution/builtins
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

debug				:
							@$(MAKE) fclean all DEBUG=true

.PHONY: all clean fclean re libft debug
