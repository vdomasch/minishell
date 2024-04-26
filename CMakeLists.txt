cmake_minimum_required(VERSION 3.27)
project(minishell C)

set(CMAKE_C_STANDARD 90)

add_executable(minishell
        libft/srcs/ft_atoi.c
        libft/srcs/ft_bzero.c
        libft/srcs/ft_calloc.c
        libft/srcs/ft_isalnum.c
        libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c
        libft/srcs/ft_isdigit.c
        libft/srcs/ft_isprint.c
        libft/srcs/ft_isspace.c
        libft/srcs/ft_itoa.c
        libft/srcs/ft_lstadd_back_bonus.c
        libft/srcs/ft_lstadd_front_bonus.c
        libft/srcs/ft_lstclear_bonus.c
        libft/srcs/ft_lstdelone_bonus.c
        libft/srcs/ft_lstiter_bonus.c
        libft/srcs/ft_lstlast_bonus.c
        libft/srcs/ft_lstmap_bonus.c
        libft/srcs/ft_lstnew_bonus.c
        libft/srcs/ft_lstsize_bonus.c
        libft/srcs/ft_memchr.c
        libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c
        libft/srcs/ft_memmove.c
        libft/srcs/ft_memset.c
        libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr_fd.c
        libft/srcs/ft_putstr_fd.c
        libft/srcs/ft_split.c
        libft/srcs/split.c
        libft/srcs/ft_strchr.c
        libft/srcs/ft_strdup.c
        libft/srcs/ft_striteri.c
        libft/srcs/ft_strjoin.c
        libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlcpy.c
        libft/srcs/ft_strlen.c
        libft/srcs/ft_strmapi.c
        libft/srcs/ft_strncmp.c
        libft/srcs/ft_strnstr.c
        libft/srcs/ft_strrchr.c
        libft/srcs/ft_strtrim.c
        libft/srcs/ft_substr.c
        libft/srcs/ft_tolower.c
        libft/srcs/ft_toupper.c
        libft/srcs/get_next_line.c
        libft/srcs/get_next_line_utils.c

        includes/minishell.h
        sources/main.c
        sources/minishell_utils.c
        sources/read_command_line.c
        sources/signals.c
        sources/parsing/command_utils.c
        sources/parsing/dollars.c
        sources/parsing/pipes_checks.c
        sources/parsing/process_message.c
        sources/parsing/quotes_utils.c
        sources/parsing/redirections.c
        sources/parsing/split_arguments.c
        sources/environment/env_list.c
        sources/environment/process_env.c
        sources/execution/exec.c
        sources/execution/pipes.c)

target_link_libraries(minishell readline)