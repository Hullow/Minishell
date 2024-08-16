# Issues and milestones

## Proposed sequence
1. Simple tokenizing: no parameter expansion, no quotes `+ no pipes and redirections ?`
2. Simple execution of commands: no variable assignment, no redirection, no quote removal
3. Filename expansion/Pathname resolution
4. Execution environment
5. exit status handling
6. Pipeline execution : subshell => cmegret ?
7. cd, pwd, and pathname resolution => cmegret ?
8. echo
9. exit
8. signal handling
9. parameter expansion + $?
9. export and unset (variable assignment)
10. quote interpretation
11. Redirections
12. Here-docs ?

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