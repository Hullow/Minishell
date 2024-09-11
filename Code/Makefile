# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmegret <cmegret@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 14:53:36 by cmegret           #+#    #+#              #
#    Updated: 2024/09/11 15:38:16 by cmegret          ###   ########.fr        #
# **************************************************************************** #

# Header ASCII
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
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./lib -lft -lftprintf -lreadline

# Fichiers sources et objets
SRCS = srcs/main/main.c \
      srcs/main/main_utils.c \
      srcs/token/token_main.c \
      srcs/token/token_utils.c \
      srcs/token/token_creation.c \
      srcs/token/token_operator.c \
	  srcs/parsing/parse_main.c \
	  srcs/parsing/parse_utils.c \
	  srcs/execution/execution_main.c \
	  srcs/execution/execution_env_path.c \
	  srcs/builtin/cd/main_cd.c \
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
	@echo "$(GREEN)Compilation successful!$(RESET)"

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