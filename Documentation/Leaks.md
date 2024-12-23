 <<eof
> 
> 
> 
> eof


==586180== Use --track-origins=yes to see where uninitialised values come from
==586180== For lists of detected and suppressed errors, rerun with: -s
==586180== ERROR SUMMARY: 2 errors from 1 contexts (suppressed: 0 from 0)
==585961== Invalid write of size 8
==585961==    at 0x1097DB: ft_free_redir_list (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10960D: ft_free_cmd_list (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x109C2E: ft_free_all (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10959E: main (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==  Address 0x4b67860 is 0 bytes inside a block of size 16 free'd
==585961==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==585961==    by 0x1097D6: ft_free_redir_list (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10960D: ft_free_cmd_list (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x109C2E: ft_free_all (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10959E: main (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==  Block was alloc'd at
==585961==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==585961==    by 0x10BBA1: ft_init_heredoc (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10BBE5: initialize_heredoc (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10B8CD: ft_handle_heredoc_input (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x10B9AB: ft_open_heredocs (in /goinfre/ahanzi/Minishell/Code/minishell)
==585961==    by 0x109561: main (in /goinfre/ahanzi/Minishell/Code/minishell)





==605101== Memcheck, a memory error detector
==605101== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==605101== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==605101== Command: ./minishell
==605101== 
Minishell : 
`Minishell : ,,,,`
,,,,: command not found
==605108== 
==605108== FILE DESCRIPTORS: 5 open (3 std) at exit.
==605108== Open file descriptor 4: /dev/pts/0
==605108==    at 0x49DAFEB: dup (syscall-template.S:120)
==605108==    by 0x10D7DC: configure_redirections (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C7D4: execute_child (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CDD2: execute_pipeline (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C8D2: execute_cmd (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x109587: main (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108== 
==605108== Open file descriptor 3: /dev/pts/0
==605108==    at 0x49DAFEB: dup (syscall-template.S:120)
==605108==    by 0x10D7CB: configure_redirections (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C7D4: execute_child (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CDD2: execute_pipeline (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C8D2: execute_cmd (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x109587: main (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108== 
==605108== 
==605108== HEAP SUMMARY:
==605108==     in use at exit: 212,714 bytes in 313 blocks
==605108==   total heap usage: 682 allocs, 369 frees, 235,786 bytes allocated
==605108== 
==605108== 10 bytes in 1 blocks are definitely lost in loss record 8 of 79
==605108==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==605108==    by 0x10F8DB: ft_substr (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F32A: ft_add_splitted (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F3F9: ft_apply_split (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F475: ft_split (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CEAF: get_env_paths (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CF26: get_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D484: resolve_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D4F3: handle_child_process (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C767: run_command (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C816: execute_child (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CDD2: execute_pipeline (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108== 
==605108== 106 bytes in 9 blocks are definitely lost in loss record 32 of 79
==605108==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==605108==    by 0x10F8DB: ft_substr (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F32A: ft_add_splitted (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F3AA: ft_apply_split (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10F475: ft_split (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CEAF: get_env_paths (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CF26: get_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D484: resolve_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D4F3: handle_child_process (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C767: run_command (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C816: execute_child (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CDD2: execute_pipeline (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108== 
==605108== 126 bytes in 10 blocks are definitely lost in loss record 33 of 79
==605108==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==605108==    by 0x10F12B: ft_strjoin (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CF7A: get_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D484: resolve_cmd_path (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10D4F3: handle_child_process (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C767: run_command (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C816: execute_child (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10CDD2: execute_pipeline (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x10C8D2: execute_cmd (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108==    by 0x109587: main (in /goinfre/ahanzi/Minishell-fallan-cmegret/Code/minishell)
==605108== 
==605108== LEAK SUMMARY:
==605108==    definitely lost: 242 bytes in 20 blocks
==605108==    indirectly lost: 0 bytes in 0 blocks
==605108==      possibly lost: 0 bytes in 0 blocks
==605108==    still reachable: 212,472 bytes in 293 blocks
==605108==         suppressed: 0 bytes in 0 blocks
==605108== Reachable blocks (those to which a pointer was found) are not shown.
==605108== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==605108== 
==605108== For lists of detected and suppressed errors, rerun with: -s
==605108== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
