#!/bin/bash
source ./test_structure.sh

# Tests
run_test ":\nexit\n" "" 0 "Single colon"
run_test " \nexit\n" "" 0 "Single space"
run_test "         \nexit\n" "" 0 "Multiple spaces"
run_test "      \nexit\n" "" 0 "Multiple spaces with newline"
run_test "#\nexit\n" "" 0 "Single hashtag"
run_test "!\nexit\n" "" 1 "Single exclamation mark"