#!/bin/bash
source ./test_structure.sh

run_test "/\nexit\n" "/: Is a directory" 126 "Root directory access"
run_test "//\nexit\n" "//: Is a directory" 126 "Double root directory access"
run_test "/.\nexit\n" "/.: Is a directory" 126 "Single dot directory"
run_test "/./././././.\nexit\n" "/./././././.: Is a directory" 126 "Multiple dots directory"
run_test "///////\nexit\n" "///////: Is a directory" 126 "Many slashes directory"