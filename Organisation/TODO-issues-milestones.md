# Issues and milestones

## Proposed sequence
. Simple tokenizing and parsing: no parameter expansion, no quotes `+ no pipes and redirections ?`
. Simple execution of commands: no variable assignment, no redirection, no quote removal
. Execution environment
. exit status and error handling => cmegret ?
. Filename expansion/Pathname resolution => cmegret ?
. Pipeline execution : subshell => cmegret ?
. parse command prefix and suffixes => fallan ?
. parse and execute redirections => fallan ?
. cd, pwd, and pathname resolution => cmegret ?
. signal handling => fallan ?
. quote interpretation => cmegret ?
. env => cmegret ?
. echo => cmegret ?
. exit => cmegret ?
. parameter expansion (`$`)=> fallan ?
. export and unset (variable assignment) => cmegret ?
. Here-docs ? => fallan ?

## To-do by topic
### Tokenizing and parsing
- implementing `=` in the parsing (requires: `export`; references: see Shell-functioning.md#Shell grammar#Assignment)
- keep track of quotes in parsing => see header: `struct token // bool	is_double_quoted;// bool is_single_quoted;` (to try)
- adapt BNF grammar from POSIX standard for Minishell project => almost done
- Check that if no token is found (input empty), struct token is NULL

### Builtins
#### Export
- Check if valid name (see [POSIX definition](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_235))

### History
- Add history : different with here doc

### Execution
- Pathname resolution

### Documentation
- Add parsing and tokenization summary to Shell-functioning.md