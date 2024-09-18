# Personal journal - Minishell project - fallan
## 20/6/24
- Preparing call with Corentin
- Call with Corentin

## 25/6/24
- Watched 42sh video, took notes
- Read about Test-driven development, types of tests

## 26/6/24
- 2h call with cmegret

## 27/6/24
- Watching "A shell in 10min" and rewriting the code to understand it (-> 10minshell.c)
- Also tested some functions (fork, execv, wait)

## 28/6/24
- Setting own computer to bash (from zsh)
- Housekeeping (folders)

## 4/7/24
- Call cmegret

## 5/7/24
- Work with cmegret
- Admin, merges

- question to cmegret: why does `echo "hello" > hello1.txt && cat hello1.txt | echo > hello2.txt` not put anything into hello2, while `echo > hello2.txt hello` does ?

## 9/7/24
- Corrected dcortes and bwach's minishell, took some notes of things to test
- Reading through SCL and taking notes in Shell-functioning.md, as well as Requirements.md
	- Going through token recognition (parsing), not finished


## 15/7/24
- Read about field splitting in the SCL and the IFS ([Input Field Separators](https://en.wikipedia.org/wiki/Input_Field_Separators)) => likely not needed because no expansion except enviromental variable expansion and exit status expansion, where there are no whitespaces
- Read the Bash reference manual, especially the [Shell operation section](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Shell-Operation).
- Note: parameter expansion happens after the parsing of tokens into simple and compound commands

Learning:
- History expansion with `!`: `!-25` to display to the command 25 lines back. `!!` to refer to the previous command. `!string` to refer to the most recent command preceding the current position in the history list starting with *string*.

- Look at how quoting is implemented in other shells, in particular nested quoting.

## 16/7/24
- Examined some quoting examples
- Reading the bash manual and SCL. Things make more and more sense, for instance Shell Grammar in SCL.
- Re-reading and rewriting Shell-functioning.md for more detail and clarity. Added examples of quoting sequences and expected output
- Reorganized documentation files 

Learning:
- Tab in Markdown: `&emsp;`
- `<command>&` :
	> If a command is terminated by the control operator ‘&’, the shell executes the command asynchronously in a subshell. This is known as executing the command in the background, and these are referred to as asynchronous commands. The shell does not wait for the command to finish, and the return status is 0 (true). When job control is not active (see Job Control), the standard input for asynchronous commands, in the absence of any explicit redirections, is redirected from /dev/null.
	<br>([Bash reference manual - Lists of commands](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Lists))

## 17/7/24
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

## 18/7/24
- Re-writing Shell-functioning.md

- Learning:
POSIX.1-2017's special grammar notation is based on the syntax used by the `yacc` ([yet-another-compiler-compiler](https://en.wikipedia.org/wiki/Yacc)) utility. It is used to portray the complex syntax of certain program input.
([Grammar Conventions](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap01.html#tag_17_03))

## 19/7/24
- Workday with cmegret
- Started coding the tokenization

## 22/7/24
- Tokenization: separating code into functions

## 23/7/24
- Tokenization:
	- fixed issue with first character not printed out
	- linked list,
	- refactoring,
	- continued operator token
	- issue with some sequences like `Hello >>    ???     kk` => "Hello", ">>", "k" tokens only (see Tokenization.md)
		=> to fix<br>
		- `Hello ??? >>>` :<br>
			- token: Hello???
			- token: >>
			- token: >
		- `Hello ??? >>> ??? kkk` :<br>
			- token: Hello???
			- token: >>
			- token: >
			- token: k
			
			=> issue fixed: needed to pass **tok (by reference) rather than as a parameter in all functions that create or edit a token.
- Simple tokenizer done. To do:
	- Check if behavior is correct !!!
	- test it with various sequences, check if behavior is adequate
	- test for leaks
	- refactor for clarity of code (and to prevent issues)
- New commit: removed printf statements, refactored a tiny bit (put conditions in functions)
- New commit: more refactoring and cleaning up. Couldn't make ft_tokenize work with a call to ft_create_token at the beginning, need to initialize tok separately which takes up space. => maybe do this soon
- Norminette: not done

## 25/7/24
- Read about Abstract Syntax Trees, Backus-Naur Form grammars, parsing

## 26/7/24
- More research into parsing and grammars, starting to make sense (asked Claude via Double in VSCode, continued reading the slides at [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf))

## 30/7/24
- More research into parsing and grammars, starting to make sense (asked Claude via Double in VSCode, continued reading the slides at [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf))
- 

## 1/8/24
?

## 5/8/24
- Reading more about parsing, abstract syntax trees and semantic rules from [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf)
- made a parse tree with UML diagram tool: https://online.visual-paradigm.com/w/emnfyqki/diagrams/#diagram:proj=0&type=ClassDiagram&width=11&height=8.5&unit=inch
- Saw an outline of how to code an AST

## 6/8/24
- Simplified the POSIX Shell Grammar to fit the Minishell project requirements (without bonuses)
- Looking at data structures to store the parsed strings: Map ADT, hashtables, binary search trees, ...

## 8/8/24
- Reading about parsing, thinking about parsing output for execution
- wrote some code to parse operators

# ?/8/24
- 

# 12-14/8/24
- See git logs Hullow branch

# 15/8/24
- Work with cmegret @42 on parsing + executing basic commands (ls with and without arguments)

# 16/8/24
- Work (distance) with cmegret

# 4/9/24
- Back to work after 2-week break
- Read about parsing principles and methods

# 5/9/24
- Read about parsing principles and methods
- Call with cmegret, discussed exeuction

# 6/9/24
- Reading about grammars (for choice of parsing methods): Chomsky hierarchy, ambiguity, types of parsing techniques
- Attempt to implement a Recursive Decent Parsing algorithm (top-down). No test yet, still writing code/pseudocode
- Need to add references

# 12/9/24
- Reading cmegret's code
- Git merges and some order

# 13/9/24
- Reading cmegret's code, refactoring
- Fixed pipe tokenization issue (when '|' at the end of prompt)
- Git learning (learngitbranching.org), git merging, and some file reordering

# 18/9/24
- Reading more about parsing concepts (leftmost/rightmost derivation, and approaches (types of parsing: top-down, bottom-up, LL, Recursive descent, LR, ...))
- Implementing a parser for a very simple grammar => doesn't seem to relevant to our parser; too different, but helps make issues concrete. Will try directly a recursive descent parser with our data structures and grammar instead.
- Trying to implement Recursive descent parsing with an iterative component to avoid infinite loop (see parse_main.c). New branch created that corresponds to the task: `parse_cmd_prefixes_suffixes`