# List of requirements and dependencies for Minishell

## Environment
- Bash version on 42 Ubuntu iMacs : GNU bash, version 5.1.16(1)-release (x86_64-pc-linux-gnu)

## Functionalities
> Display a prompt when waiting for a new command
=> Use readline
> Have a working history.
=> Use add_history, rl_clear_history (or clear_history), and ... ?
=> Subshell history ?

### Character handling
- `$`:
> - Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence **except for \$ (dollar sign)**.
> - Handle environment variables (**\$ followed by a sequence of characters**) which
should expand to their values.
> - Handle **$?** which should expand to the exit status of the most recently executed
foreground pipeline.
Normal shells: see Shell-functioning.md#Token recognition# 2.2.5. Parameter and arithmetic expansion, command substitution

### Builtins
- Re-hardcoded

### Keybindings
#### Signals
- ctrl + c


### Not required
- ctrl + k
- ctrl + a
- ctrl + \42
- Command substitution: `$(command)` or \`command\`


### To clarify
## Shell input
- from a file
- `-c`
- `#!` : "If the first line of a file of shell commands starts with the characters "#!", the results are unspecified." (SCL)

## Tokenization
- Parameter expansion
- Command substitution: what to do instead ? E.g. `echo $(ls) >> file`