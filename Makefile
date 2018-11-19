#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 15:33:35 by nkolosov          #+#    #+#              #
#    Updated: 2017/11/16 15:33:35 by nkolosov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FOLD = .
NAME = gnl

# GNL FILES

GNLC = $(FOLD)/get_next_line.c
GNLH = $(FOLD)/get_next_line.h
GNLO = $(FOLD)/get_next_line.o

LIBDIR = $(FOLD)/libft
LIBFT = $(LIBDIR)/libft.a

# MAIN FILES

MAIN1 = main

# COLORS

RED = '\033[0;31m'
GREEN = '\033[0;32m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

# BUILD COMMANDS

all:
	@make $(NAME)

libre:
	@mkdir $(LOGDIR) || true
	make -C $(LIBDIR)/ fclean > $(LOGDIR)/lib_fclean
	make -C $(LIBDIR)/ > $(LOGDIR)/lib_make

$(NAME): $(GNLO) $(MAIN1).o $(GNLH) $(LIBFT)
	clang -o $(NAME) $(MAIN1).o $(GNLO) -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft

$(GNLO): $(GNLC) $(GNLH) $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(GNLO) -c $(GNLC)

$(MAIN1).o: $(MAIN1).c $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(MAIN1).o -c $(MAIN1).c

$(LIBFT):
	@make -C $(LIBDIR)/

clean:
	@find . -name "*.o" -delete

fclean: clean
	@rm $(NAME) || true

re: fclean all

norm:
	@clear
	@norminette $(GNLC) $(GNLH)
	@norminette $(LIBDIR)/ || true

tar:
	@make evalclean
	tar -cf check.tar resources/ Makefile
