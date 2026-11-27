# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: endyildi <endyildi@mulhouse42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/26 22:03:17 by endyildi          #+#    #+#              #
#    Updated: 2026/11/27 01:05:14 by endyildi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= get_next_line.a

CC			= cc
CFLAGS		+= $(if $(BUFFER_SIZE),-D BUFFER_SIZE=$(BUFFER_SIZE))
AR			= ar rcs
RM			= rm -f
HEADER		= get_next_line.h

SRCS		= get_next_line.c \
			  get_next_line_utils.c 
	
OBJ_DIR		= obj
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: %.c $(HEADER) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) -I. main.c $(NAME) -o gnl_test
.PHONY: all clean fclean re