# Issues and milestones

## Proposed sequence
1. Simple tokenizing: no parameter expansion, no quotes `+ no pipes and redirections ?`
2. Simple execution of commands: no variable assignment, no redirection, no quote removal
=> with echo only ?
3. exit and error handling
4. signal handling
4. env
5. cd, pwd, and pathname resolution
6. subshell ?
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

### History
- Add history : different with here doc

### Execution
- Pathname resolution