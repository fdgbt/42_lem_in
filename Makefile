# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 17:34:44 by fdagbert          #+#    #+#              #
#    Updated: 2019/07/04 14:22:15 by fdagbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = object
INC_PATH = include

LIB_NAME = libftprintf.a
LIBFT_NAME = libft.a

DOT = lem.dot
SVG_NEATO = lem_neato.svg
SVG_SFDP = lem_sfdp.svg

CHROME = /Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome
CHROMIUM = /usr/bin/chromium-browser

LIBFT_PATH = $(LIB_PATH)/libft
FTPRINTF_PATH = $(LIB_PATH)/ft_printf

SRC_LEM_PATH = $(SRC_PATH)/$(NAME)
LEM_FCT = ft_check_file.c			\
		  ft_check_comments.c		\
		  ft_check_rooms.c			\
		  ft_check_links.c			\
		  ft_pathfinder.c			\
		  ft_pathfinder_sp.c		\
		  ft_add_set.c				\
		  ft_add_path.c				\
		  ft_bfs.c					\
		  ft_bfs_sp.c				\
		  ft_bfs_reset.c			\
		  ft_end.c					\
		  ft_print_graph.c			\
		  ft_clean.c				\
		  ft_print_paths.c			\
		  ft_print_laps.c			\
		  ft_best_laps.c			\
		  main.c
LEM_SRC = $(addprefix $(SRC_LEM_PATH)/,$(LEM_FCT))

OBJ_LEM_PATH = $(OBJ_PATH)/$(NAME)
OBJ_LEM = $(LEM_FCT:.c=.o)
	OBJ_LEM_SRC = $(addprefix $(OBJ_LEM_PATH)/,$(OBJ_LEM))

OBJECTS = $(OBJ_LEM_SRC)

HEAD_SRC = $(LIBFT_PATH)/$(INC_PATH)/libft.h				\
		   $(LIBFT_PATH)/$(INC_PATH)/ft_get_next_line.h		\
		   $(FTPRINTF_PATH)/$(INC_PATH)/ft_printf.h			\
		   $(INC_PATH)/lem_in.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L$(LIB_PATH)/ft_printf
LDLIBS = -lftprintf

INCLUDES = $(LIBFT_PATH)/$(INC_PATH) $(FTPRINTF_PATH)/$(INC_PATH) $(INC_PATH)
INC_CC = $(foreach DIR,$(INCLUDES),-I$(DIR))

.PHONY: all, clean, fclean, re, lib

all:
	@$(MAKE) $(NAME)

$(NAME): $(LIBFT_PATH)/$(LIBFT_NAME) $(FTPRINTF_PATH)/$(LIB_NAME) $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(INC_CC) $(LDFLAGS) $(LDLIBS)

$(OBJ_LEM_PATH)/%.o: $(SRC_LEM_PATH)/%.c $(HEAD_SRC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_LEM_PATH) 2> /dev/null || true
	$(CC) -g $(CFLAGS) $(INC_CC) -o $@ -c $<

$(LIBFT_PATH)/$(LIBFT_NAME): lib

lib:
	@$(MAKE) -C $(LIBFT_PATH)
	@$(MAKE) -C $(FTPRINTF_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(FTPRINTF_PATH) clean
	@rm -fv $(OBJECTS)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@rm -fv $(DOT) 2> /dev/null || true

fclean: clean
	@rm -fv $(LIBFT_PATH)/$(LIBFT_NAME)
	@rm -fv $(FTPRINTF_PATH)/$(LIB_NAME)
	@rm -fv $(NAME)
	@rm -fv $(SVG_NEATO) 2> /dev/null || true
	@rm -fv $(SVG_SFDP) 2> /dev/null || true

re: fclean all

neato:
	neato -n -Tsvg $(DOT) > $(SVG_NEATO)
	@if [ -d "/Applications" ];		\
		then						\
		$(CHROME) $(SVG_NEATO);		\
		else						\
		$(CHROMIUM) $(SVG_NEATO);	\
		fi

sfdp:
	sfdp -x -Tsvg $(DOT) > $(SVG_SFDP)
	@if [ -d "/Applications" ];		\
		then						\
		$(CHROME) $(SVG_SFDP);		\
		else						\
		$(CHROMIUM) $(SVG_SFDP);	\
		fi
