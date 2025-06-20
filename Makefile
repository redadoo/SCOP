# **************************************************************************** #
# Makefile for SCOP Project                                                    #
# **************************************************************************** #

# Project
NAME        := SCOP

# Compiler & Flags
CXX         := g++
CXXFLAGS    := -std=c++17
LDFLAGS     := -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Directories
SRCDIR      := src
OBJDIR      := .obj
INCDIRS     := src src/utility src/Engine src/Data

# Shader files
SHADERDIR   := shaders
SHADERSRC   := $(wildcard $(SHADERDIR)/*.vert $(SHADERDIR)/*.frag)

# Source files
SRCFILES    := main Engine/Engine utility/utility
SRC         := $(addprefix $(SRCDIR)/, $(SRCFILES:=.cpp))
OBJ         := $(addprefix $(OBJDIR)/, $(SRCFILES:=.o))
DEPS        := $(OBJ:.o=.d)

# Include flags
INCFLAGS    := $(addprefix -I, $(INCDIRS))

# Colors
GREEN       := \033[32m
GRAY        := \033[2;37m
YELLOW      := \033[1;33m
RESET       := \033[0m

.PHONY: all clean fclean re run leaks shaders

all: shaders $(NAME)

$(NAME): $(OBJ)
	@echo "$(GRAY)[Linking] $(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)✓ Build successful$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[Compiling] $<$(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCFLAGS) -MMD -MP -c $< -o $@

run: re
	./$(NAME) 2>error

leaks: re
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

shaders:
	@echo "$(YELLOW)[Compiling shader] $< -> $@$(RESET)"
	@bash $(SHADERDIR)/compile.sh

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GRAY)✗ Object files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME) leaks.txt error $(SHADERDIR)/*.spv
	@echo "$(GRAY)✗ Binary, shaders and extra files cleaned$(RESET)"

re: fclean all

-include $(DEPS)
