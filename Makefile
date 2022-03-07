# Name of the final executable
NAME = minishell

# Project's directories
SOURCEDIR := ./src
HEADERSDIR := ./inc
OBJECTSDIR := ./objects
MINISHELL_FOLDER = minishell
PARSE_FOLDER = parse
SIGNAL_FOLDER = signal
BUILT_FOLDER = builtins
EXEC_FOLDER = execution
LIBFT_HEADER = $(SOURCEDIR)/libft/libft.h
LIBFT_FOLDER = $(SOURCEDIR)/libft

# Name of variables
LIBFT_LIB = libft.a
LIBS = -lncurses
FLAGS = -Wall -Wextra -Werror -g
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

# BUILTINS files variable

BUILT_FILES = cd.c \
			  echo.c \
			  env.c \
			  chained_list.c \
			  chained_list_2.c \
			  chained_list_3.c \
			  exit.c \
			  export.c \
			  export_utils.c \
			  pwd.c \
			  swap_nodes.c \
			  unset.c

# MINISHELL file variable

MINISHELL_FILES = minishell.c \
				  prompt_msg.c \
				  working_history.c

# Parse files variable

PARSE_FILES =	parsing.c \
				error_parse.c \
				parse_tools.c \
				parse_tools_2.c \
				parse_tools_3.c \
				sep_n_space.c \
				pimp_my_string.c \
				pimp_my_string_2.c \
				replace_dollars.c \
				replace_dollars_ext.c \
				alloc_childs.c \
				dollar_out_quote.c \
				arg_redir_nodes.c \
				quote_treatment.c \
				list_parsing.c

# SIGNAL files variable

SIGNAL_FILES = signal.c

# Exec files variable

EXEC_FILES = execution.c \
			 pipe.c \
			 exec_tools.c \
			 redirection.c \
			 file_func.c

# Main file variable

MAIN_FILE = main.c

# Define objects for all sources

OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
OBJ_BUILT = $(addprefix $(OBJECTSDIR)/$(BUILT_FOLDER)/, $(BUILT_FILES:.c=.o))
OBJ_MINISHELL = $(addprefix $(OBJECTSDIR)/$(MINISHELL_FOLDER)/, $(MINISHELL_FILES:.c=.o))
OBJ_PARSE= $(addprefix $(OBJECTSDIR)/$(PARSE_FOLDER)/, $(PARSE_FILES:.c=.o))
OBJ_SIGNAL = $(addprefix $(OBJECTSDIR)/$(SIGNAL_FOLDER)/, $(SIGNAL_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))

OBJS := $(OBJ_MINISHELL) $(OBJ_SIGNAL) $(OBJ_MAIN) \
		$(OBJ_PARSE) $(OBJ_BUILT) $(OBJ_EXEC)

LIBFT_FILE := $(LIBFT_FOLDER)/$(LIBFT_LIB)

# Name the compiler
CC = gcc

# OS specific part
RM = rm -rf
RMDIR = rm -rf
MKDIR = mkdir -p
MAKE = make -C
ECHO = /bin/echo
ERRIGNORE = 2>/dev/null

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),T)
    HIDE =
else
    HIDE = @
endif


.PHONY: all fclean

all: credit $(NAME)

libft:
	@echo "$(BLUE)█████████████████████████ Making LIBFT █████████████████████████$(RESET)"
	@$(MAKE) $(LIBFT_FOLDER)
	@echo "$(BLUE)███████████████████████ Making minishell ███████████████████████$(RESET)"

$(NAME): libft $(OBJS)
	@$(CC) -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@ -lreadline -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib
	@echo "$(BLUE)███████████████████████ Compiling is DONE ██████████████████████$(RESET)"

$(OBJECTSDIR)/%.o : $(SOURCEDIR)/%.c $(HEADERSDIR)/*.h
	@$(MKDIR) $(dir $@)
	@echo "$(BLUE)█ $(YELLOW)Compiling$(RESET) $<:\r\t\t\t\t\t\t\t$(GREEN){DONE}$(BLUE) █$(RESET)"
	@$(CC) $(FLAGS) -I $(HEADERSDIR) -I $(LIBFT_HEADER) -o $@ -c $<

# Remove all objects, dependencies and executable files generated during the build

clean:
	@echo "$(RED)deleting$(RESET): " $(OBJECTSDIR)
	@$(RMDIR) $(OBJECTSDIR) $(ERRIGNORE)
	@echo "$(RED)deleting$(RESET): " "libft objects"
	@$(MAKE) $(LIBFT_FOLDER) clean

fclean: clean
	@echo "$(RED)deleting$(RESET): " $(LIBFT_FOLDER)/$(LIBFT_LIB)
	@$(RM) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(ERRIGNORE)
	@echo "$(RED)deleting$(RESET): " $(NAME)
	@$(RM) $(NAME) $(ERRIGNORE)

re: fclean $(NAME)

credit:
	@echo "																				"
	@echo "██████╗     ██████╗ ███████╗    ███████╗██████╗ ███████╗███████╗ ██╗██████╗  "
	@echo "╚════██╗    ██╔══██╗██╔════╝    ██╔════╝██╔══██╗██╔════╝██╔════╝ ╚═╝██╔══██╗ "
	@echo " █████╔╝    ██████╔╝█████╗      █████╗  ██████╔╝█████╗  █████╗      ██║  ██║ "
	@echo "██╔═══╝     ██╔══██╗██╔══╝      ██╔══╝  ██╔══██╗██╔══╝  ██╔══╝      ██║  ██║ "
	@echo "███████╗    ██████╔╝███████╗    ██║     ██║  ██║███████╗███████╗    ██████╔╝ "
	@echo "╚══════╝    ╚═════╝ ╚══════╝    ╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝    ╚═════╝  "
	@echo "																				"
