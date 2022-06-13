# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ejang <ejang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 20:10:08 by jeyoon            #+#    #+#              #
#    Updated: 2022/06/13 16:10:41 by ejang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = test_parse
CFLAGS	=	-Wall -Wextra -Werror -lreadline -fsanitize=address

LIBFT_DIR = ./libft/
PARSE_DIR = ./parse/
BUILTIN_DIR = ./built_in/
UTIL_DIR = ./util/

LIBFT_SRCS = ft_memset.c ft_substr.c ft_strdup.c ft_strlcpy.c ft_strlen.c ft_isalnum.c ft_isalpha.c ft_split.c ft_strncmp.c ft_isdigit.c ft_strjoin.c
PARSE_SRCS = main.c parse_main.c parse_token.c parse_cmd.c parse_cmd_utils.c parse_cmd_type.c
BUILTIN_SRCS = func_pwd.c exe_cmd.c func_env.c func_echo.c func_export.c func_unset.c func_cd.c func_cd_util.c
UTIL_SRCS = ft_strcmp.c copy_env.c

SRCS = $(addprefix $(LIBFT_DIR), $(LIBFT_SRCS)) $(addprefix $(PARSE_DIR), $(PARSE_SRCS)) $(addprefix $(BUILTIN_DIR), $(BUILTIN_SRCS)) $(addprefix $(UTIL_DIR), $(UTIL_SRCS))
OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o	:	%.c
		$(CC) $(CFLAG) -c $< -o $@

clean	:
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re	:	fclean all

.PHONY	:	all, clean, fclean, re
