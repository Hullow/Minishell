#!/bin/bash
source ./test_structure.sh

run_test "&&\nexit\n" "syntax error near unexpected token '&&'" 2 "Double ampersand"
run_test "&&&&\nexit\n" "syntax error near unexpected token '&&'" 2 "Multiple double ampersands"
run_test "&&&&&&&&&&&&&&\nexit\n" "syntax error near unexpected token '&&'" 2 "Long sequence of ampersands"
run_test ";;\nexit\n" "syntax error near unexpected token ';;'" 2 "Double semicolon"
run_test ";;;;\nexit\n" "syntax error near unexpected token ';;'" 2 "Multiple semicolons"
run_test ";;;;;;;;;;;;;;\nexit\n" "syntax error near unexpected token ';;'" 2 "Long sequence of semicolons"
run_test "()\nexit\n" "syntax error near unexpected token ')'" 2 "Empty parentheses"
run_test "(())\nexit\n" "syntax error near unexpected token ')'" 2 "Nested parentheses"
run_test "(((())))\nexit\n" "syntax error near unexpected token ')'" 2 "Deeply nested parentheses"