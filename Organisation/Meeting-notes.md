# 20/6/24 (call)
## Items to discuss
# Discussed
### Organisational
- Scheduling meetings (2, 3 times a week ?)
- Task system on github
- English language ?

### Technical
- Environment: Linux ? (see subject: zsh ? bash ?)
- Testing system for each "module"

### Misc
- Pipex: cmegret l'as fait, fallan fait minitalk
- Documentation: on se repartit la lecture ?

## Other things discussed
- Github issues: when making a commit, use "#2" to refer to issue #2 automatically
- Branching: make branches as often as possible and as many as necessary
	=> easier to cut things up, helps to isolate code

# 21/6/24 (call)
21/6/24 – 11am (Discord)
## Items to discuss
- Documentation, research

# 26/6/24 (call)
## To do list (from last meeting)
- Watch videos
- Re-read subject
- Start making visual schemas of project

## Notes
- Cmegret: thinks the execution block will not change much

- To do:
	- Iterate on:
		- Re-read subject and make list of tasks + requirements, dependencies on Github	
			=> make individual lists (on own Github branch) and then discuss over call, confront them => synthesize
		- Code examples of each function
		- Start making visual schemas of project

	- Make project (P.S.: on Github)

- To do after:
	- Make a very basic shell that executes basic commands

# 4/7/24 (Call)
## UML Diagram
- We chose **activity diagram** ("An activity diagram serves as an analytical tool to help developers, business analysts, and even project managers map out a process flow and understand what activities happen over time. Similar to flowcharts, activity diagrams are especially useful for depicting a complex process.") instead of **sequence diagram** ("Understand the order in which the events within a sequence interact with each other.")
- Tool: [Visual-paradigm](https://online.visual-paradigm.com/share.jsp?id=323336313339372d3131#diagram:workspace=mxsxpzyl&proj=0&id=11) (Miro UML diagrams needs payed upgrade)
	- End of flow => end of command (command finished or interrupted)
	- End of activity => end of minishell
- cmegret made a [basic flow diagram](https://online.visual-paradigm.com/share.jsp?id=323336313339372d3131#diagram:workspace=mxsxpzyl&proj=0&id=11) 

## Playing with commands
> Nb: put them in a Tested-commands.txt
- trying echo, with flags, and with redirections (se):
	- `echo -n hello` => no need to differentiate between flags and other types of arguments
	- `echo hello -n` => no need to differentiate between flags and other types of arguments
- redirections:
	- `echo "hello world" > test.txt`
	- `echo "hello world" >a test.txt` => puts all the line into "a"

- `existing_command; non_existing_command; existing_command` vs `existing_command && non_existing_command && existing_command`

- redirection: `<non_executable_file> > <non_existent_file.txt>` => "command not found" AND creates a file with name `non_existent_file.txt`
	> Redirection is used to open and close files for the current shell execution environment (see Shell Execution Environment) or for any command. ([SCL](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07))

# 5/7/24 (42)
- Re-reading subject, topics and questions:
	- Readline/history:
		- should we implement indexing of history to navigate history with up/down arrows, or is it implemented by one of the authorized functions ?
		- Readline commands: ctrl + k, ctrl + a
		- clear history: rl_clear_history => not found on OS X/Macbook M1 => clang recommends clear_history from readline.h => which one to use ?
	- Execution:
		- how to call echo with -n ? Something special to do ?
		- pberset: to code builtins, use functions tsetaddr, etc.


# 16/8/24
- Two sources of documentation: Shell-functioning.md, Topics/*.md (Builtins, Quoting, ...). Follow them !

# 5/9/24
- fallan back from break
- 2hour call, discussed execution, errors and exit, builtins, makefile, parsing, next steps
- To do next: 
	- cmegret => refactoring execution, builtins
	- fallan => read more about parsing methods, refactor tokenization/parsing a bit