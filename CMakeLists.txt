cmake_minimum_required(VERSION 3.27)
project(minishell C)

set(CMAKE_C_STANDARD 90)

add_executable(minishell sources/main.c
        includes/minishell.h
        sources/prompt.c
        sources/libft.c)

target_link_libraries(minishell readline)