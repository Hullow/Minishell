#!/bin/bash

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Définir le chemin absolu vers le répertoire contenant le Makefile
MAKEFILE_DIR="/Users/corentin/Documents/Minishell/Code"  # Chemin du Makefile
MINISHELL_EXEC="minishell"
export MINISHELL_PATH="$MAKEFILE_DIR/$MINISHELL_EXEC"

# Fonction pour afficher l'en-tête
function display_header {
    echo -e "${YELLOW}╔══════════════════════════════════════════════════════════════════════════════╗${NC}"
    echo -e "${YELLOW}║                Welcome to Minishell Tester Framework!                       ║${NC}"
    echo -e "${YELLOW}╚══════════════════════════════════════════════════════════════════════════════╝${NC}"
    echo
}

# Affichage de l'aide
function display_help {
    echo -e "${YELLOW}Usage: ./run_all_tests.sh [OPTIONS]${NC}"
    echo -e "Options:"
    echo -e "  -h       Affiche cette aide et quitte."
    echo -e "  -all     Exécute tous les tests sans demande de confirmation."
    echo -e "  -XX      Exécute uniquement le fichier de test avec le numéro XX (par ex., -07 pour test_07_echo_command.sh)."
    echo
    exit 0
}

# Vérifie si l'exécutable minishell existe et le compile si nécessaire
function check_and_build_minishell {
    echo -e "${YELLOW}✔ Checking for Minishell...${NC}"
    if [ ! -f "$MINISHELL_PATH" ]; then
        echo -e "${RED}❌ Minishell executable not found. Compiling...${NC}"
        if [ -d "$MAKEFILE_DIR" ]; then
            (cd "$MAKEFILE_DIR" && make)
            if [ ! -f "$MINISHELL_PATH" ]; then
                echo -e "${RED}❌ Compilation failed. Exiting.${NC}"
                exit 1
            fi
        else
            echo -e "${RED}❌ Directory $MAKEFILE_DIR does not exist. Exiting.${NC}"
            exit 1
        fi
    else
        echo -e "${GREEN}✔ Minishell found at $MINISHELL_PATH${NC}"
    fi
    clear
}

# Vérification des flags
run_all=false
specific_test=""
while [[ "$1" != "" ]]; do
    case $1 in
        -h ) display_help ;;
        -all ) run_all=true ;;
        -[0-9][0-9] )
            specific_test=$(ls tests/test_"${1:1}"_*.sh 2>/dev/null)
            ;;
        * ) echo -e "${RED}Option invalide : $1${NC}"; display_help ;;
    esac
    shift
done

# Fonction pour exécuter un script de test
function run_test_script {
    local script_name="$1"
    echo -e "${YELLOW}Running tests in $script_name...${NC}"
    bash "$script_name"
}

# Vérification et compilation de Minishell
check_and_build_minishell

# Affichage de l'en-tête
display_header

# Si un test spécifique est demandé
if [[ -n "$specific_test" ]]; then
    if ls $specific_test 1> /dev/null 2>&1; then
        run_test_script "$specific_test"
    else
        echo -e "${RED}❌ Test file matching $specific_test not found.${NC}"
        exit 1
    fi
    exit 0
fi

# Lancer chaque script de test
is_first_command=true
skip_remaining_tests=false

for script in tests/test_*.sh; do
    if [ "$is_first_command" = true ]; then
        is_first_command=false
        run_test_script "$script"
        continue
    fi

    if [ "$skip_remaining_tests" = true ]; then
        echo -e "${RED}Tests dans ${script} ignorés.${NC}"
        continue
    fi

    if [[ "$run_all" == true ]]; then
        run_test_script "$script"
    else
        # Demande confirmation pour exécuter le test
        echo -e "${YELLOW}Voulez-vous exécuter les tests dans ${script}? (Y/n/q pour quitter)${NC}"
        read -r answer
        if [[ -z "$answer" || "$answer" == "y" || "$answer" == "Y" ]]; then
            run_test_script "$script"
        elif [[ "$answer" == "q" || "$answer" == "Q" ]]; then
            echo -e "${RED}Arrêt des tests.${NC}"
            skip_remaining_tests=true
        else
            echo -e "${RED}Tests dans ${script} ignorés.${NC}"
        fi
    fi
    echo # Ajoute une ligne vide pour la lisibilité
done