# Checklist Minishell
- Open quotes: show message ? (ft_check_open_quote)
- Malloc checks: also look for ft_strdup
- Heredocs delimiter exit bug:
```sh
Minishell : << EOF << EOF2
>EOF2
>EOF
>EOF
Minishell :
```
- Exit status: do tests
- Signals: do tests

# If time
- Reintroduce colored prompt and check leaks/crashes
- ft_tokenize_end_of_input: is it ever called ?