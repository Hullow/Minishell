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

# Fonction générique pour exécuter un test
function run_test {
    local commands="$1"
    local expected_output="$2"
    local expected_exit="$3"

    local cleaned_command=$(echo "$commands" | sed -E 's/exit.*//; s/\\n/ /g; s/\\s+$//')
    local fifo_name=$(mktemp -u)
    mkfifo "$fifo_name"

    "$MINISHELL_PATH" < "$fifo_name" > output.log 2>&1 &
    minishell_pid=$!
    echo -e "$commands" > "$fifo_name"
    wait $minishell_pid
    actual_exit=$?

    python3 clean_output.py output.log cleaned_output.log
    actual_output=$(cat cleaned_output.log)

    rm -f "$fifo_name" output.log cleaned_output.log

    echo -e "${YELLOW}--- Running Command: ${cleaned_command} ---${NC}"
    ((total_tests++))
    if [[ "$actual_output" == "$expected_output" ]] && [ "$actual_exit" -eq "$expected_exit" ]; then
        echo -e "${GREEN}✔ Command '${cleaned_command}' : SUCCESS${NC}"
        echo -e "${BLUE}Expected Output: ${NC}$expected_output"
        echo -e "${BLUE}Actual Output:   ${NC}$actual_output"
        echo -e "${BLUE}Expected Exit:   ${NC}$expected_exit"
        echo -e "${BLUE}Actual Exit:     ${NC}$actual_exit"
        echo
        ((successful_tests++))
    else
        echo -e "${RED}✗ Command '${cleaned_command}' : FAIL${NC}"
        echo -e "${RED}Expected Output: ${NC}$expected_output"
        echo -e "${RED}Actual Output:   ${NC}$actual_output"
        echo -e "${RED}Expected Exit:   ${NC}$expected_exit"
        echo -e "${RED}Actual Exit:     ${NC}$actual_exit"
        echo
    fi
}

# Fonction pour afficher les résultats globaux
function display_results {
    echo "====================="
    echo -e "${YELLOW}Résultats des Tests :${NC}"
    echo -e "Tests réussis : ${GREEN}${successful_tests}${NC} / ${total_tests}"
    echo -e "Tests échoués : ${RED}$((total_tests - successful_tests))${NC}"
    echo "====================="
}