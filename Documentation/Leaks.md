valgrind --track-fds=yes --leak-check=full ./minishell


`Minishell : ,,,,`
,,,,: command not found
==615202== 
==615202== HEAP SUMMARY:
==615202==     in use at exit: 212,598 bytes in 303 blocks
==615202==   total heap usage: 552 allocs, 249 frees, 233,514 bytes allocated
==615202== 
==615202== 126 bytes in 10 blocks are definitely lost in loss record 31 of 77
==615202==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==615202==    by 0x10F106: ft_strjoin (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==615202==    by 0x10CF0A: get_cmd_path (execution_env_path.c:79)
==615202==    by 0x10D45F: resolve_cmd_path (execution_external.c:65)
==615202==    by 0x10D4CE: handle_child_process (execution_external.c:89)
==615202==    by 0x10C6F7: run_command (execution_main.c:85)
==615202==    by 0x10C7A6: execute_child (execution_main.c:117)
==615202==    by 0x10CD62: execute_pipeline (execution_pipeline.c:75)
==615202==    by 0x10C862: execute_cmd (execution_main.c:148)
==615202==    by 0x109587: main (main.c:32)
==615202== 
==615202== LEAK SUMMARY:
==615202==    definitely lost: 126 bytes in 10 blocks
==615202==    indirectly lost: 0 bytes in 0 blocks
==615202==      possibly lost: 0 bytes in 0 blocks
==615202==    still reachable: 212,472 bytes in 293 blocks
==615202==         suppressed: 0 bytes in 0 blocks
==615202== Reachable blocks (those to which a pointer was found) are not shown.
==615202== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==615202== 
==615202== For lists of detected and suppressed errors, rerun with: -s
