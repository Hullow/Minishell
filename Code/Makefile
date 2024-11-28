# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francis <francis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 14:53:36 by cmegret           #+#    #+#              #
#    Updated: 2024/11/28 17:03:52 by francis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER1 =                                                                    
HEADER2 =                                                                    
HEADER3 = "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
HEADER4 = "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
HEADER5 = "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
HEADER6 = "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
HEADER7 = "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
HEADER8 = "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
HEADER9 =                                                                    
HEADER10 =

# Délai d'affichage du logo
DELAY = 0.1

# Redirection des erreurs
REDIRECT = > /dev/null 2>&1

# Codes de couleur
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# Nom de l'exécutable
NAME = minishell

# Bibliothèques
LIBFT = ./lib/libft.a
FT_PRINTF = ./lib/libftprintf.a

# Compilateur
CC = gcc

# -g3 -fsanitize=address
# Flags de compilation
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LIBFLAGS = -L./lib -lft -lftprintf -L/opt/homebrew/opt/readline/lib -lreadline

# Fichiers sources et objets
SRCS = main/main.c \
      main/main_utils.c \
	  main/main_initialize.c \
      token/token_main.c \
      token/token_checks.c \
      token/token_utils.c \
      token/token_creation.c \
      token/token_operator.c \
	  parsing/parse_main.c \
	  parsing/expend_exit_status.c \
	  execution/execution_main.c \
	  execution/execution_env_path.c \
	  execution/execute_builtin.c \
	  builtin/cd.c \
	  builtin/cd_utils.c \
      builtin/env.c \
      builtin/export.c \
      builtin/export_utils.c \
      builtin/unset.c \
      builtin/pwd.c \
      builtin/echo.c \
      builtin/exit.c \
      signal/signal.c \

# Add path prefix to SRCS files
SRC = $(addprefix srcs/, $(SRCS))

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle pour tout compiler
all: start norm $(NAME)

# Règle pour afficher le logo au démarrage
start:
	clear
	@echo $(HEADER1)
	@sleep $(DELAY)
	@echo $(HEADER2)
	@sleep $(DELAY)
	@echo $(HEADER3)
	@sleep $(DELAY)
	@echo $(HEADER4)
	@sleep $(DELAY)
	@echo $(HEADER5)
	@sleep $(DELAY)
	@echo $(HEADER6)
	@sleep $(DELAY)
	@echo $(HEADER7)
	@sleep $(DELAY)
	@echo $(HEADER8)
	@sleep $(DELAY)
	@echo $(HEADER9)
	@sleep $(DELAY)
	@echo $(HEADER10)
	@sleep $(DELAY)

# Règle pour l'exécutable final
$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJ)
	@echo "$(BLUE)Linking: $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFLAGS)
	@echo "$(GREEN)\nCompilation successful!\n$(RESET)"

# Règle pour les fichiers objets
%.o: %.c
	@echo "$(BLUE)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF): $(LIBFT)
	@echo "$(BLUE)Compiling: lib/ft_printf$(RESET)"
	@$(MAKE) -C ./lib/ft_printf -f Makefile $(REDIRECT)

$(LIBFT):
	@echo "$(BLUE)Compiling: lib/libft$(RESET)"
	@$(MAKE) -C ./lib/libft -f Makefile $(REDIRECT)

# Règle pour la norminette
norm:
	@echo "$(YELLOW)Exécution de norminette sur les fichiers spécifiés dans SRC...$(RESET)"
	@norminette $(SRC) > norminette_output.txt || (echo "")
	@error=0; \
	while IFS= read -r line; do \
		if ! echo "$$line" | grep -q 'OK!$$'; then \
			echo "$(RED)Erreur dans le fichier : $$line$(RESET)"; \
			error=1; \
		fi; \
	done < norminette_output.txt || (echo "$(MAGENTA)Erreur lors de la vérification du résultat de norminette$(RESET)"); \
	if [ $$error -eq 0 ]; then \
		echo "$(GREEN)Tous les fichiers spécifiés dans SRC sont conformes à la norme.$(RESET)"; \
	fi
	@rm norminette_output.txt
	@echo " "

sanitize: CFLAGS += -fsanitize=address
sanitize: re

debug: CFLAGS += -g
debug: re

clean_libs:
	@$(MAKE) -C lib/libft/ clean $(REDIRECT)
	@$(MAKE) -C lib/ft_printf/ clean $(REDIRECT)

fclean_libs:
	@$(MAKE) -C lib/libft/ fclean $(REDIRECT)
	@$(MAKE) -C lib/ft_printf/ fclean $(REDIRECT)

# Règle pour nettoyer les fichiers objets
clean: clean_libs
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)

# Règle pour nettoyer tout
fclean: fclean_libs clean
	@echo "$(RED)Cleaning executable(s)...$(RESET)"
	@rm -f $(NAME)
	@sleep 1
	clear

# Règle pour refaire tout
re: fclean all

# Règle pour rendre le makefile "phony"
.PHONY: all clean fclean re norm start sanitize debug clean_libs fclean_libs