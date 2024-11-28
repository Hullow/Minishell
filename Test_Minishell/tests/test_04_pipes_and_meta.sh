#!/bin/bash
source ./test_structure.sh

run_test "-\nexit\n" "-: command not found" 127 "-"
run_test "|\nexit\n" "syntax error near unexpected token '|'" 2 "Single pipe"
run_test "| hola\nexit\n" "syntax error near unexpected token '|'" 2 "Pipe with command"
run_test "||\nexit\n" "syntax error near unexpected token '||'" 2 "Double pipe"
run_test "|||\nexit\n" "syntax error near unexpected token '|'" 2 "Triple pipe"
run_test "||||||||||\nexit\n" "syntax error near unexpected token '|'" 2 "Multiple pipes"
run_test ">>|<<\nexit\n" "syntax error near unexpected token '|'" 2 "Mixed redirection and pipe"