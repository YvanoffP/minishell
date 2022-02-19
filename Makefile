# Name of the final executable
NAME = minishell

# Project's directories
SOURCEDIR := ./src
HEADERSDIR := ./inc
OBJECTSDIR := ./objects
CD_FOLDER = cd
ECHO_FOLDER = echo
ENV_FOLDER = env
EXIT_FOLDER = exit
# EXEC_FOLDER = execution
EXPORT_FOLDER = export
MINISHELL_FOLDER = minishell
PARSE_FOLDER = parse
PWD_FOLDER = pwd
SIGNAL_FOLDER = signal
UNSET_FOLDER = unset
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

# CD files variable

CD_FILES =	cd.c

# ECHO files variable

ECHO_FILES = echo.c

# ENV files variable

ENV_FILES = env.c \
			chained_list.c

# EXIT files variable

EXIT_FILES = exit.c

# EXECUTION files

# EXEC_FILES	= execution.c

# EXPORT files variable

EXPORT_FILES = export.c

# MINISHELL file variable

MINISHELL_FILES = minishell.c \
				  prompt_msg.c \
				  working_history.c

# Parse files variable

PARSE_FILES =	parsing.c \
				array_zone.c \
				error_parse.c \
				parse_tools.c \
				sep_n_space.c \
				parse_tools_2.c \
				pimp_my_string.c \
				quote_treatment.c \
				replace_dollars.c \
				list_parsing.c

# PWD files variable

PWD_FILES = pwd.c

# SIGNAL files variable

SIGNAL_FILES = signal.c

# UNSET files variable

UNSET_FILES = unset.c

# Main file variable

MAIN_FILE = main.c

# Define objects for all sources
# OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))
OBJ_CD = $(addprefix $(OBJECTSDIR)/$(CD_FOLDER)/, $(CD_FILES:.c=.o))
OBJ_ECHO = $(addprefix $(OBJECTSDIR)/$(ECHO_FOLDER)/, $(ECHO_FILES:.c=.o))
OBJ_ENV = $(addprefix $(OBJECTSDIR)/$(ENV_FOLDER)/, $(ENV_FILES:.c=.o))
OBJ_EXIT = $(addprefix $(OBJECTSDIR)/$(EXIT_FOLDER)/, $(EXIT_FILES:.c=.o))

# OBJ_EXEC = $(addprefix $(OBJECTSDIR)/$(EXEC_FOLDER)/, $(EXEC_FILES:.c=.o))

OBJ_EXPORT = $(addprefix $(OBJECTSDIR)/$(EXPORT_FOLDER)/, $(EXPORT_FILES:.c=.o))
OBJ_MINISHELL = $(addprefix $(OBJECTSDIR)/$(MINISHELL_FOLDER)/, $(MINISHELL_FILES:.c=.o))
OBJ_PARSE= $(addprefix $(OBJECTSDIR)/$(PARSE_FOLDER)/, $(PARSE_FILES:.c=.o))
OBJ_PWD= $(addprefix $(OBJECTSDIR)/$(PWD_FOLDER)/, $(PWD_FILES:.c=.o))
OBJ_SIGNAL = $(addprefix $(OBJECTSDIR)/$(SIGNAL_FOLDER)/, $(SIGNAL_FILES:.c=.o))
OBJ_UNSET = $(addprefix $(OBJECTSDIR)/$(UNSET_FOLDER)/, $(UNSET_FILES:.c=.o))
OBJ_MAIN = $(addprefix $(OBJECTSDIR)/, $(MAIN_FILE:.c=.o))
OBJS := $(OBJ_CD) $(OBJ_ECHO) $(OBJ_ENV) $(OBJ_EXPORT) $(OBJ_EXIT) \
		$(OBJ_MINISHELL) $(OBJ_PWD) $(OBJ_SIGNAL) $(OBJ_UNSET) $(OBJ_MAIN) \
		$(OBJ_PARSE) # $(OBJ_EXEC)
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
	@$(CC) -lreadline -I $(HEADERSDIR) -I $(LIBFT_FOLDER) $(OBJS) $(LIBFT_FOLDER)/$(LIBFT_LIB) $(LIBS) -o $@
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
