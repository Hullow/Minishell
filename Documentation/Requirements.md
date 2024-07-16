# List of requirements and dependencies for Minishell

## Environment
- Bash version on 42 Ubuntu iMacs : GNU bash, version 5.1.16(1)-release (x86_64-pc-linux-gnu)

## Functionalities
> Display a prompt when waiting for a new command
=> Use readline
> Have a working history.
=> Use add_history, rl_clear_history (or clear_history), and ... ?
=> Subshell history ?

### Metacharacter handling
#### `\`:
> Not interpret unclosed quotes or special characters which are not required by the
subject such as **\ (backslash)** or ; (semicolon).

#### `$`:
> - Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence **except for \$ (dollar sign)**.
> - Handle environment variables (**\$ followed by a sequence of characters**) which should expand to their values.
> - Handle **$?** which should expand to the exit status of the most recently executed foreground pipeline.
=> see Shell-functioning.md#Token recognition# 2.2.5. Parameter and arithmetic expansion, command substitution

**Summary:**
- `$?`
- `$ENVIRONMENTAL_VARIABLE`
- Expand between double quotes but not between single quotes

#### newline

#### pipe `|`

#### redirections

##### `>>`
> \>\> should redirect output in append mode.
- (maybe) use `access` to check existence and rights (if not readable, return error and print error message)
- use `open` with O_WRONLY | O_APPND | O_CREAT : `fd = open(tmpname, O_WRONLY | O_APPEND | O_CREAT, 0644);`

### Builtins
See [Builtins - Bash Reference Manual (v5.2)](https://www.gnu.org/software/bash/manual/bash.html#Shell-Builtin-Commands)
- Re-hardcoded

#### Export
- how to do it without setenv ?

### Keybindings
#### Signals
- ctrl + c


### Not required
#### Signals
- ctrl + k
- ctrl + a
- ctrl + \42

#### Input
- `-c`, `-i`, `-s`
- Command substitution: `$(command)` or \`command\`
- Arithmetic substitution: 

#### Control operators
- &   &&   (   )   ;   ;;    ||

#### Reserved words
- If    Then    Else    Elif    Fi    Do    Done
- Case    Esac    While    Until    For

#### Other
- in
- `!`

### To clarify
## Shell input
- from a file
- `#!` : "If the first line of a file of shell commands starts with the characters "#!", the results are unspecified." (SCL)
- `{}`

## Variables
- Variable creation ?
- Env variable creation

## Tokenization
- Parameter expansion for `$`: `${` also ?
- Command substitution: what to do instead ? E.g. `echo $(ls) >> file`