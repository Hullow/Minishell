# Minishell
cmegret, fallan's Minishell project @Ecole 42 Lausanne (2024)

A simple shell in C emulating the behavior of bash, with pipelines, redirections (input, output, append), here-documents,environmental variables, some builtins (echo, cd, pwd, export, unset, env, exit), exit status, signal handling (SIGINT, SIGQUIT), and a history. The shell interprets single and double quotes, but not parentheses, wildcards, semicolons and backslashes. The prompt is managed by the Readline library.