# 20/6/24
- Preparing call with Corentin
- Call with Corentin

# 25/6/24
- Watched 42sh video, took notes
- Read about Test-driven development, types of tests

# 26/6/24
- 2h call with cmegret

# 27/6/24
- Watching "A shell in 10min" and rewriting the code to understand it (-> 10minshell.c)
- Also tested some functions (fork, execv, wait)

# 28/6/24
- Setting own computer to bash (from zsh)
- Housekeeping (folders)

# 4/7/24
- Call cmegret

# 5/7/24
- Work with cmegret
- Admin, merges

- question to cmegret: why does `echo "hello" > hello1.txt && cat hello1.txt | echo > hello2.txt` not put anything into hello2, while `echo > hello2.txt hello` does ?

# 9/7/24
- Corrected dcortes and bwach's minishell, took some notes of things to test
- Reading through SCL and taking notes in Shell-functioning.md, as well as Requirements.md
	- Going through token recognition (parsing), not finished


# 15/7/24
- Read about field splitting in the SCL and the IFS ([Input Field Separators](https://en.wikipedia.org/wiki/Input_Field_Separators)) => likely not needed because no expansion except enviromental variable expansion and exit status expansion, where there are no whitespaces
- Read the Bash reference manual, especially the [Shell operation section](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Operation).
- Note: parameter expansion happens after the parsing of tokens into simple and compound commands

- History expansion with `!`: `!-25` to display to the command 25 lines back. `!!` to refer to the previous command. `!string` to refer to the most recent command preceding the current position in the history list starting with *string*.

- Look at how quoting is implemented in other shells, in particular nested quoting.