NAME        		= 	SCOP

CXX        			= 	g++
CXXFLAGS   			= 	-std=c++17 -O2 #-ftime-report
LDFLAGS    			= 	-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
RM          		= 	rm -rf

OBJDIR      		= 	.objFiles

# Paths for source and header files
SRCDIR      		= 	src

# Specify source files
FILES       		= 	main Engine utility

SRC         		= 	$(addprefix $(SRCDIR)/, $(FILES:=.cpp))
OBJ         		= 	$(addprefix $(OBJDIR)/, $(FILES:=.o))

#include the lib/ directory for header files
INC         		= -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
NONE        		= "\033[0m"
GREEN       		= "\033[32m"
GRAY        		= "\033[2;37m"
CURSIVE     		= "\033[3m"
YELLOW      		= "\033[1;33m"

.PHONY: all clean fclean re leaks

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@echo $(CURSIVE) $(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: re
	./$(NAME) 2>error

leaks: re
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

clean:
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) leaks.txt

re: fclean all