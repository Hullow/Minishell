# Header ASCII
HEADER1 =                                                                          
HEADER2 =                                                                          
HEADER3 = ░█████╗░  ███╗░░░███╗  ███████╗  ░██████╗░  ██████╗░  ███████╗  ████████╗
HEADER4 = ██╔══██╗  ████╗░████║  ██╔════╝  ██╔════╝░  ██╔══██╗  ██╔════╝  ╚══██╔══╝
HEADER5 = ██║░░╚═╝  ██╔████╔██║  █████╗░░  ██║░░██╗░  ██████╔╝  █████╗░░  ░░░██║░░░
HEADER6 = ██║░░██╗  ██║╚██╔╝██║  ██╔══╝░░  ██║░░╚██╗  ██╔══██╗  ██╔══╝░░  ░░░██║░░░
HEADER7 = ╚█████╔╝  ██║░╚═╝░██║  ███████╗  ╚██████╔╝  ██║░░██║  ███████╗  ░░░██║░░░
HEADER8 = ░╚════╝░  ╚═╝░░░░░╚═╝  ╚══════╝  ░╚═════╝░  ╚═╝░░╚═╝  ╚══════╝  ░░░╚═╝░░░
HEADER9 =                                                                          
HEADER10 =                                                                          

# Délai d'affichage du logo
DELAY = 0.1

# Codes de couleur
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

# Nom de l'exécutable
NAME = pipex

# Compilateur
CC = gcc

# -g3 -fsanitize=address
# Flags de compilation
CFLAGS = -g -Wall -Wextra -Werror

# Dossiers
INCDIR = includes/

# Fichiers sources et objets
SRC = srcs/main.c \
	  srcs/command.c \
	  srcs/fork_process.c \
	  utils/ft_split.c \
	  utils/ft_strchr.c \
	  utils/ft_strjoin.c \
	  utils/ft_strlcpy.c \
	  utils/ft_strlen.c \
	  utils/ft_strncmp.c \
	  utils/ft_strtrim.c \

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

# Règle pour l'exécutable push_swap
$(NAME): $(OBJ)
	@echo "\n$(GREEN)Linking: $@$(RESET)\n"
	@$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^


# Règle pour les fichiers objets
%.o: %.c
	@echo "$(BLUE)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

# Règle pour la norminette
norm:
	@echo "$(YELLOW)Exécution de norminette...$(RESET)"
	@norminette > norminette_output.txt || (echo "")
	@error=0; \
	while IFS= read -r line; do \
		if ! echo "$$line" | grep -q 'OK!$$'; then \
			echo "$(RED)Erreur dans le fichier : $$line$(RESET)"; \
			error=1; \
		fi; \
	done < norminette_output.txt || (echo "$(MAGENTA)Erreur lors de la vérification du résultat de norminette$(RESET)"); \
	if [ $$error -eq 0 ]; then \
		echo "$(GREEN)Tous les fichiers sont conformes à la norme.$(RESET)"; \
	fi
	@rm norminette_output.txt
	@echo " "

# Règle pour nettoyer les fichiers objets
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)

# Règle pour nettoyer tout
fclean: clean
	@echo "$(RED)Cleaning executable(s)...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@sleep 1
	clear

# Règle pour refaire tout
re: fclean all

# Règle pour rendre le makefile "phony"
.PHONY: all clean fclean re norm start