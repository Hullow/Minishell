#!/bin/bash

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Initialisation des compteurs
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
    local test_name="$4"

    local cleaned_command=$(echo "$commands" | sed -E 's/exit.*//; s/\\n/ /g; s/\\s+$//')
    local fifo_name=$(mktemp -u)
    mkfifo "$fifo_name"

    "$MINISHELL_PATH" < "$fifo_name" > output.log 2>&1 &
    minishell_pid=$!
    echo -e "$commands" | sed 's/\\\\/\\\\\\\\/g' > "$fifo_name"
    wait $minishell_pid
    actual_exit=$?

    python3 clean_output.py output.log cleaned_output.log
    actual_output=$(cat cleaned_output.log)

    rm -f "$fifo_name" output.log cleaned_output.log

    echo -e "${YELLOW}--- Running Test: ${test_name} ---${NC}"
    ((total_tests++))
	expected_output=$(echo -n "$expected_output" | sed 's/\\\\/\\/g')
	actual_output=$(echo -n "$actual_output" | sed 's/\\\\/\\/g')
	if diff <(echo -n "$actual_output") <(echo -n "$expected_output") &>/dev/null && [ "$actual_exit" -eq "$expected_exit" ]; then
        echo -e "${GREEN}✔ Test '${test_name}' : SUCCESS${NC}"
        echo -e "${BLUE}Expected Output: ${NC}$expected_output"
        echo -e "${BLUE}Actual Output:   ${NC}$actual_output"
        echo -e "${BLUE}Expected Exit:   ${NC}$expected_exit"
        echo -e "${BLUE}Actual Exit:     ${NC}$actual_exit"
        echo
        ((successful_tests++))
    else
        echo -e "${RED}✗ Test '${test_name}' : FAIL${NC}"
        echo -e "${BLUE}Expected Output: ${NC}$expected_output"
        echo -e "${BLUE}Actual Output:   ${NC}$actual_output"
        echo -e "${BLUE}Expected Exit:   ${NC}$expected_exit"
        echo -e "${BLUE}Actual Exit:     ${NC}$actual_exit"
        echo
    fi
}

run_test "/\nexit\n" "/: Is a directory" 126 "Root directory access"
run_test "//\nexit\n" "//: Is a directory" 126 "Double root directory access"
run_test "/.\nexit\n" "/.: Is a directory" 126 "Single dot directory"
run_test "/./././././.\nexit\n" "/./././././.: Is a directory" 126 "Multiple dots directory"
run_test "///////\nexit\n" "///////: Is a directory" 126 "Many slashes directory"
run_test "\\\nexit\n" "\\: command not found" 127 "Single backslash command"
run_test "\\\\\nexit\n" "\\\\: command not found" 127 "Double backslash command"
run_test "\\\\\\\\\\\\\nexit\n" "\\\\\\\\\\\\: command not found" 127 "Multiple backslashes command"

function display_results {
    echo "====================="
    echo -e "${YELLOW}Résultats des Tests :${NC}"
    echo -e "Tests réussis : ${GREEN}${successful_tests}${NC} / ${total_tests}"
    echo -e "Tests échoués : ${RED}$((total_tests - successful_tests))${NC}"
    echo "====================="
}

display_results

if [ $successful_tests -eq $total_tests ]; then
    exit 0
else
    exit 1
fi