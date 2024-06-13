# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:09:45 by vdomasch          #+#    #+#              #
#    Updated: 2024/02/22 16:21:25 by vdomasch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################

SRCS		:=	ft_atoi.c								\
				ft_bzero.c								\
				ft_calloc.c								\
				ft_isalnum.c							\
				ft_isalpha.c							\
				ft_isascii.c							\
				ft_isdigit.c							\
				ft_isprint.c							\
				ft_isspace.c							\
				ft_itoa.c								\
				ft_memchr.c								\
				ft_memcmp.c								\
				ft_memcpy.c								\
				ft_memmove.c							\
				ft_memset.c								\
				ft_putchar_fd.c							\
				ft_putendl_fd.c							\
				ft_putnbr_fd.c							\
				ft_putstr_fd.c							\
				ft_split.c								\
				split.c									\
				ft_strchr.c								\
				ft_strdup.c								\
				ft_striteri.c							\
				ft_strjoin.c							\
				ft_strlcat.c							\
				ft_strlcpy.c							\
				ft_strlen.c								\
				ft_strmapi.c							\
				ft_strncmp.c							\
				ft_strnstr.c							\
				ft_strrchr.c							\
				ft_strtrim.c							\
				ft_substr.c								\
				ft_tolower.c							\
				ft_toupper.c							\
				get_next_line.c							\
				get_next_line_utils.c

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	libft.h

#HEAD_D		:=	

CFLAGS		:=	-Wall -Wextra -Werror

NAME		:=	libft.a

########################################################################################################################
#                                                         LIB                                                          #
########################################################################################################################

#LIB		:=	

#LIB_D		:=	

#LIB_I		:=	$(LIB_D)

#LIB_H		:=	$(LIB_I)libft.h

#LIB_A		:=	$(addprefix $(LIB_D), $(LIB))

########################################################################################################################
#                                                        RULES                                                         #
########################################################################################################################

all			:	$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(HEAD) Makefile
				ar rcs $(NAME) $(OBJS)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

########################################################################################################################
#                                                        COMMANDS                                                      #
########################################################################################################################

clean		:
				rm -rf $(OBJS) $(OBJS_D)

fclean		:	clean
				rm -rf $(NAME)
				$(MAKE) clean

re			:	fclean all

.PHONY: all clean fclean re lib
