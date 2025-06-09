# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edoardo <you@example.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/09 by edoardo                 #+#    #+#              #
#    Updated: 2025/06/09 by edoardo                 ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        		= 	SCOP

CC          		= 	g++ -std=c++17
RM          		= 	rm -rf

OBJDIR      		= 	.objFiles

# Paths
SRCDIR      		= 	src
INCDIR      		= 	src
LIBENGINE   		= 	src/Engine
LIBUTILITY  		= 	src/utility
LIBDATA    		    = 	src/Data

# Source files (relative to SRCDIR)
FILES       		= 	main Engine/Engine utility/utility

SRC         		= 	$(addprefix $(SRCDIR)/, $(FILES:=.cpp))
OBJ         		= 	$(addprefix $(OBJDIR)/, $(FILES:=.o))

# Headers (used for dependency tracking)
HEADER      		= 	$(LIBENGINE)/Engine.hpp $(LIBUTILITY)/utility.hpp $(LIBDATA)/Data.hpp

# Include flags
INC         		= 	-I$(INCDIR) -I$(LIBUTILITY) -I$(LIBENGINE) -I$(LIBDATA)
# Libraries
LDFLAGS     		= 	-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Colors
NONE        		= "\033[0m"
GREEN       		= "\033[32m"
GRAY        		= "\033[2;37m"
CURSIVE     		= "\033[3m"
YELLOW      		= "\033[1;33m"

.PHONY: all clean fclean re run leaks

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(INC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

run: re
	./$(NAME) 2>error

leaks: re
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) leaks.txt
	@$(RM) error

re: fclean all
