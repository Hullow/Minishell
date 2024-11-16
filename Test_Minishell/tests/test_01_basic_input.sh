#!/bin/bash

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Initialisation des compteurs globaux
total_tests=0
successful_tests=0

if [ -z "$MINISHELL_PATH" ]; then
    echo -e "${RED}Error: MINISHELL_PATH is not set. Exiting.${NC}"
    exit 1
fi

# Fonction pour exécuter un test
function run_test {
    local commands="$1"
    local expected_output="$2"
    local expected_exit="$3"

    # Crée un FIFO
    local fifo_name=$(mktemp -u)
    mkfifo "$fifo_name"

    # Lancer Minishell en arrière-plan
    "$MINISHELL_PATH" < "$fifo_name" > output.log 2>&1 &
    minishell_pid=$!

    # Injecter les commandes dans le FIFO
    echo -e "$commands" > "$fifo_name"

    # Attendre que Minishell termine
    wait $minishell_pid
    actual_exit=$?

    # Lire la sortie de Minishell
    actual_output=$(cat output.log)

    # Supprimer les lignes de prompt liées à la commande `exit`
    actual_output=$(echo "$actual_output" | grep -v "exit")

    # Nettoyer
    rm -f "$fifo_name" output.log

    # Vérifier la sortie et le code de retour
    echo -e "${BLUE}--- Running Command: ${commands} ---${NC}"
	((total_tests++))
    if [[ "$actual_output" == *"$expected_output"* ]] && [ "$actual_exit" -eq "$expected_exit" ]; then
        echo -e "${GREEN}✔ Command '${commands%%\\n*}' : SUCCESS${NC}"
        echo -e "${BLUE}Expected Output: ${NC}$expected_output"
        echo -e "${BLUE}Actual Output:   ${NC}$actual_output"
        echo -e "${BLUE}Expected Exit:   ${NC}$expected_exit"
        echo -e "${BLUE}Actual Exit:     ${NC}$actual_exit"
        echo
		((successful_tests++))
        return 0
    else
        echo -e "${RED}✗ Command '${commands%%\\n*}' : FAIL${NC}"
        echo -e "${RED}Expected Output: ${NC}$expected_output"
        echo -e "${RED}Actual Output:   ${NC}$actual_output"
        echo -e "${RED}Expected Exit:   ${NC}$expected_exit"
        echo -e "${RED}Actual Exit:     ${NC}$actual_exit"
        echo
        return 1
    fi
}

# Tests
run_test "echo Hello\nexit\n" "Hello" 0
run_test "invalid_command\nexit\n" "command not found" 127
run_test "    \nexit\n" "" 0
run_test ": \nexit\n" "" 0

# Fonction pour afficher les résultats
function display_results {
    echo "====================="
    echo -e "${YELLOW}Résultats des Tests :${NC}"
    echo -e "Tests réussis : ${GREEN}${successful_tests}${NC} / ${total_tests}"
    echo -e "Tests échoués : ${RED}$((total_tests - successful_tests))${NC}"
    echo "====================="
}

# Appeler le résumé des résultats une seule fois
display_results

# Code de sortie global
if [ $successful_tests -eq $total_tests ]; then
    exit 0
else
    exit 1
fi