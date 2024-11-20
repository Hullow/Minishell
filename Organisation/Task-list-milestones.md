# Issues and milestones

## Proposed sequence
. Simple tokenizing and parsing: no parameter expansion, no quotes `+ no pipes and redirections ?`
. Simple execution of commands: no variable assignment, no redirection, no quote removal
. Execution environment: 
- check that is correct (except cd?)

. exit status and error handling => cmegret ?

. exit => cmegret ?
Requires: exit status

. Pipeline (parse and execute): subshell => cmegret ?


. Signals handling => fallan ?
. parse command prefixes and suffixes => fallan ?

. Redirections (parse and execute) => fallan ?
Parse and execute redirections:
- parse IO_NUMBER (*`2`* `>`)

- execute various redirections:
	- manage file retrieval, creation, appending
	- implement the various redirections:
		- redirect output (`>`)
		- redirect input (`<`)
		- append output (`>>`)

- manage redirection errors

Requires:
- Parse command prefixes and suffixes
- filename expansion/pathname resolution

. Filename expansion/Pathname resolution => cmegret ?
. cd, pwd, and pathname resolution => cmegret ?
Requires: filename expansion/pathname resolution

. quote interpretation => cmegret + fallan (subdivide)
. echo => cmegret ?
. parameter expansion (`$`) => fallan ?
. env, export and unset (environmental variable management) => cmegret ?
. `=` parsing (for export) => fallan ?
. Here-docs ? => fallan + cmegret ? (subdivide)


## To-do by topic
### Tokenizing and parsing
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