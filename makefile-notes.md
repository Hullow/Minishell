NAME = 		minishell
CC = 		cc
CCFLAGS = 	-Wall -Werror -Wextra
ARFLAGS = 	-rcs

LIBFT = 	libft.a
DIRLIBFT = 	libft/

SRCDIR = 	src
OBJDIR =	obj

SRC = 		src/main.c \
			src/signals.c \
			src/token/partition.c \
			src/token/token.c \
			src/token/token_handle.c \
			src/token/token_utils.c \
			src/token/token_check.c\
			src/substitution/substitution.c \
			src/substitution/substitution_tilde.c \
			src/substitution/substitution_expand.c \
			src/parser/parser.c \
			src/parser/parser_node_handle.c \
			src/parser/parser_utils.c \
			src/redirections/redir_setup.c \
			src/redirections/redir_heredoc.c \
			src/redirections/redir_utils.c \
			src/execution/execution.c \
			src/execution/exec_setup.c \
			src/execution/exec_builtin.c \
			src/execution/exec_child.c \
			src/builtin/echo_builtin.c \
			src/builtin/pwd_builtin.c \
			src/builtin/env_builtin.c \
			src/builtin/exit_builtin.c \
			src/builtin/cd_builtin.c \
			src/builtin/unset_builtin.c \
			src/builtin/export_builtin.c \
			src/builtin/export_builtin_print.c \
			src/error/common_errors.c \
			src/error/custom_errors.c \
			src/utils/utils_string.c \
			src/utils/utils_env.c \
			src/utils/utils_free.c \
			src/utils/utils_check.c \
			src/utils/utils_signals.c

SRCDIR = 	src
OBJDIR =	obj

OBJ = 		$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -sC $(DIRLIBFT)
	@$(CC) $(CCFLAGS) $(OBJ) $(DIRLIBFT)$(LIBFT) -lreadline -o $(NAME)
	@echo "\033[33mLinking complete!\033[0m"

# $< first prerequisite
# $@ target of the rule
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c $< -lreadline -o $@
	@echo "\033[32mCompiled "$<" successfully!\033[0m"

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[33mCleanup complete!\033[0m"
	@make clean -sC $(DIRLIBFT)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33mExecutable removed!\033[0m"
	@make fclean -sC $(DIRLIBFT)

re: fclean all

.PHONY: all clean fclean re
