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

Learning:
- History expansion with `!`: `!-25` to display to the command 25 lines back. `!!` to refer to the previous command. `!string` to refer to the most recent command preceding the current position in the history list starting with *string*.

- Look at how quoting is implemented in other shells, in particular nested quoting.

# 16/7/24
- Examined some quoting examples
- Reading the bash manual and SCL. Things make more and more sense, for instance Shell Grammar in SCL.
- Re-reading and rewriting Shell-functioning.md for more detail and clarity. Added examples of quoting sequences and expected output
- Reorganized documentation files 

Learning:
- Tab in Markdown: `&emsp;`
- `<command>&` :
	> If a command is terminated by the control operator ‘&’, the shell executes the command asynchronously in a subshell. This is known as executing the command in the background, and these are referred to as asynchronous commands. The shell does not wait for the command to finish, and the return status is 0 (true). When job control is not active (see Job Control), the standard input for asynchronous commands, in the absence of any explicit redirections, is redirected from /dev/null.
	<br>([Bash reference manual - Lists of commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Lists))

# 17/7/24
- Re-reading and re-writing Shell-functioning.md
- Wrote a proposal for milestone organization
- Learning:
>Create a collapsible section in Markdown
>You can create collapsible sections in Markdown using HTML \<details\> and \<summary\> tags. Let's break down the example below:

>\<details\>
>\<summary\>Click to expand\</summary\>

>This is the content of the collapsible section. You can include any Markdown-formatted text, lists, or code here.

>\</details\>

Thinking about Copilot prompting, maybe we could make some prompt tool like Fabric to answer questions about whether something is required to be done in Minishell. A mini-web app where you deposit your pdf, then it extracts the relevant information, demands you check it, then produces system prompts and indications to answer questions about what is required by the subject, but also how POSIX.1-2017 and the Bash reference manual do it, how Bash code is, etc.
=> make a GPT ? any way to augment Copilot ? Claude plugin/agent ?

# 18/7/24
- Re-writing Shell-functioning.md