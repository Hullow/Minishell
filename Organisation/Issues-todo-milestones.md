# Issues and milestones

## Proposed sequence
1. Simple tokenizing: no parameter expansion, no quotes `+ no pipes and redirections ?`
2. Simple execution of commands: no variable assignment, no redirection, no quote removal
=> with echo only ?
3. env
4. exit status handling
6. Pipeline execution : subshell
5. signal handling
6. cd, pwd, and pathname resolution
7. parameter expansion + $?
8. export and unset (variable assignment)
9. quote interpretation
10. Redirections
11. Pipes ?
12. Here-docs ?

## To-do by topic
### Tokenizing and parsing
- implementing `=` in the parsing (requires: `export`; references: see Shell-functioning.md#Shell grammar#Assignment)
- keep track of quotes in parsing
- adapt BNF grammar from POSIX standard for Minishell project

### Builtins
#### Export
- Check if valid name (see [POSIX definition](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_235))

### History
- Add history : different with here doc

### Execution
- Pathname resolution

### Documentation
- Add parsing and tokenization summary to Shell-functioning.md