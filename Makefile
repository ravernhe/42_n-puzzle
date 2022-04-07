# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ravernhe <ravernhe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 17:25:22 by ravernhe          #+#    #+#              #
#    Updated: 2020/03/09 12:14:20 by ravernhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = npuzzle

CC = g++
CFLAG = -g #-Wall -Wextra -Werror

SRC_PATH	= ./srcs/
INC_PATH	= ./includes/
OBJ_PATH	= ./obj/

OBJ_FILE = $(SRC_FILE:.cpp=.o)

SRC_FILE = 	main.cpp\
			Parser_class.cpp\
			Solver_class_v2.cpp\

OBJ      = $(addprefix $(OBJ_PATH),$(OBJ_FILE))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAG) -o $@ $^
		$(info Compilation done.)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp Makefile includes/npuzzle.hpp includes/Parser_class.hpp includes/Solver_class.hpp
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(CFLAG) -I $(INC_PATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	$(info Object file delete.)

fclean: clean
	@rm -rf $(NAME)
	$(info Executable delete.)

re: fclean all
