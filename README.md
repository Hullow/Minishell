# Minishell
Minishell project at Ecole 42 Lausanne (2024)

Authors: cmegret (@C0X23), fallan (@Hullow)

A simple shell in C emulating the behavior of bash, featuring:
- pipelines
- redirections (input, output, append)
- here-documents
- environmental variables
- some builtins (echo, cd, pwd, export, unset, env, exit)
- exit status of commands
- signal handling (SIGINT, SIGQUIT)
- history

The shell interprets single and double quotes, but not parentheses, wildcards, semicolons and backslashes.

The prompt is managed by the Readline library.