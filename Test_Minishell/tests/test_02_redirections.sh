#!/bin/bash
source ./test_structure.sh

# Tests
run_test ">\nexit\n" "syntax error near unexpected token 'newline'" 2 "Single greater than"
run_test "<\nexit\n" "syntax error near unexpected token 'newline'" 2 "Single less than"
run_test ">>\nexit\n" "syntax error near unexpected token 'newline'" 2 "Double greater than"
run_test "<<\nexit\n" "syntax error near unexpected token 'newline'" 2 "Double less than"
run_test "<>\nexit\n" "syntax error near unexpected token 'newline'" 2 "Less than greater than"
run_test ">>>>>\nexit\n" "syntax error near unexpected token '>>'" 2 "Multiple greater thans"
run_test ">>>>>>>>>>>>>>>\nexit\n" "syntax error near unexpected token '>>'" 2 "Many greater thans"
run_test "<<<<<\nexit\n" "syntax error near unexpected token '<<'" 2 "Multiple less thans"
run_test "<<<<<<<<<<<<<<<<\nexit\n" "syntax error near unexpected token '<<'" 2 "Many less thans"
run_test "> > > >\nexit\n" "syntax error near unexpected token '>'" 2 "Multiple greater thans with spaces"
run_test ">> >> >> >>\nexit\n" "syntax error near unexpected token '>>'" 2 "Multiple double greater thans with spaces"
run_test ">>>> >> >> >>\nexit\n" "syntax error near unexpected token '>>'" 2 "Mixed multiple greater thans with spaces"