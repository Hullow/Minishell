# Shell functioning
This document describes how the minishell should work, based on the [Shell Command Language definition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) and the [Bash reference manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html), summarized, paraphrased and simplified to fit the Minishell project requirements (Ecole 42, common core).

## Sources
- The [Shell Command Language definition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) chapter of the [Shell and Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html) volume of POSIX.1-2017, which is simultaneously IEEE Std 1003.1™-2017 and The Open Group Technical Standard Base Specifications, Issue 7:
	> POSIX.1-2017 defines a standard operating system interface and environment, including a command interpreter (or “shell”), and common utility programs to support applications portability at the source code level. POSIX.1-2017 is intended to be used by both application developers and system implementors and comprises four major components (each in an associated volume):
	> - (...)
	> - Definitions for a standard source code-level interface to command interpretation services (a “shell”) and common utility programs for application programs are included in the Shell and Utilities volume.

	> POSIX.1-2017 describes the external characteristics and facilities that are of importance to application developers, rather than the internal construction techniques employed to achieve these capabilities.

- The [Bash reference manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html) is "a brief description of the features that are present in the Bash shell (version 5.2, 19 September 2022) (...) [and] is meant as a brief introduction to features found in Bash. The Bash manual page should be used as the definitive reference on shell behavior."

- Note: there is substantial overlap between the two documents, such that each helps to understand the other.

- Note 2: "(..)" means part of the original document is ignored.

## 1. Reads input
### Input sources
(see `Requirements.md` -> `To clarify`)
- Shell reads lines
- From stdin
- From command line string (with `readline`)
- From a file

### Input characteristics
- length: unlimited


## 2.-3. Tokenizing and interpreting the grammar
> Parts of an interpreter:<br>
> • In designing an interpreter, follow the decomposition into two tasks, and design it to have two parts:
> 1. A syntactic analysis engine, which takes as input a string, and outputs an appropriate tree structure
> 2. A semantic evaluation engine, which takes as input that tree, and does what the original input string said to do
[CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf)

## 2. Tokenization
### 2.0. Tokenization summary
- Shell breaks input into tokens:
	- [**words**](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
		> A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.
	- [**operators**](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
    	> Operators contain at least one unquoted metacharacter, and are classified into:
		- **control operators**:
			> A token that performs a control function:
			- newline
			- `|` ([pipeline](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Pipelines))
			- (`&`, `|&`, `(`, `)` `=> don't implement`)
		- **redirection operators**:
			- `<` ([redirect input](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Redirecting-Input))
			- `>` ([redirect output](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Redirecting-Output))
			- `>>` ([redirect output in append mode](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Appending-Redirected-Output))
			- `<<` ([Here Documents](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Here-Documents))
			<br>From subject:
				> should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
			- `>|` : `=> implement ?`
			- (`<> >& <& <<<  &>> &> ` `=> don't implement`)
- [Metacharacters](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
	> A character that, when unquoted, separates words:
	- space, tab, newline (whitespace)
	- `|` (pipe)
	- `<`, `>` (redirection)
	- (`&` , `;` , `(`, `)`. `=> don't implement`)
- Metacharacters and other special characters between quotes are not interpreted, except for `$` between double quotes

### 2.1. [Quoting rules](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Quoting)
- Tokenization follows the quoting rules:
	> Quoting is used to remove the special meaning of certain characters or words to the shell, including to prevent parameter expansion. Any shell metacharacter must be quoted if it is to represent itself.
- Quoting mechanisms:
	- Single quotes `'`:
		- Preserves the literal value of each character within the quotes
		- A single quote may not occur between single quotes
	- Double quotes `"`:
		- Preserves the literal value of all characters within the quotes, except `$`
		- A double quote may not occur between double quotes
		- Examples: see `Quoting.md`


### 2.2. Token classification
#### 2.2.1. Here-documents processing
IF
- an **io_here** token has been recognized by the grammar

=> one or more of the subsequent lines immediately following the next NEWLINE token form the body of one of more here-documents<br>
=> the here-document(s) are parsed according to the [rules of Here-Document](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07_04)
=> the here-document shall be treated as a single word that begins after the next \<newline\> and continues until there is a line containing only the delimiter and a \<newline\>, with no \<space\> or \<tab\> in between.
=> Then the next here-document starts, if there is one.
=> Format:

```bash
<<word
	here-document
delimiter
```
=> The here-document redirects t
=> No parameter expansion is performed on *word*

[Bash reference manual - Here documents](https://www.gnu.org/software/bash/manual/bash.html#Here-Documents):
> this type of redirection instructs the shell to read input from the current source until a line containing only *word* (with no trailing blanks) is seen. All of the lines read up to that point are then used as the standard input for a command.

#### 2.2.2. [Ordinary token recognition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03)
How to delimit tokens:<br>
- apply the first applicable rule below to the next character in the input
- the token shall be from the current position in the input until a token is delimited according to one of the rules below
- the characters forming the token are exactly those in the input, including any quoting characters.
- if is indicated that a token is delimited, and no characters have been included in a token, processing shall continue until an actual token is delimited.
<br>=> Copilot:
	> If a delimiter (like a space or newline) is encountered before any characters are read into a token, it's not considered a token. The shell continues reading until it forms a valid token with one or more characters.

<br>**Rules**:
#### Tokenization functions requirements
Based on the rules below, here are some proposed requirements for our tokenization functions:
- Token status: is there a current token ?
- Usage of the previous character : word or operator token ?
- Quoting status : is current character quoted or not ?
- Delimitation of token to previous character

##### 2.2.2.1. End of input
IF
- end of input is recognized

AND	EITHER:
- there is a current token

=> delimit the current token

OR:
- there is no current token

=> return the end-of-input indicator as the token `=> return {EOF} token ?`

##### 2.2.2.2. Continued operator token and current character usable
IF
- current character not quoted
- previous character used as part of an operator ==> 

<br> &emsp;=> only `>>` or `<<` in our case

=> use character as part of that (operator) token

##### 2.2.2.3. Continued operator token and current character not usable
IF
- previous character used as part of an operator
- current character cannot be used with the previous characters to form an operator
<br> &emsp;e.g. `>>` + `>` => no implementation of `>>>` in our case

=> delimit the operator containing the previous character

=> question: when do we mark tok->is_operator ?

##### 2.2.2.4. Quotes
IF
- current character is single-quote `'` or double-quote `"`
- current character is not quoted

=> affects quoting for subsequent characters up to the end of the quoted text (see [Quoting rules](#21-quoting-rules))<br>
=> During token recognition, no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining `=> ?`), unmodified, including any embedded or enclosing quotes or substitution operators, between the quotation mark and the end of the quoted text.
=> The token shall not be delimited by the end of the quoted field.

##### 2.2.2.5. Parameter expansion (`$`)
IF
- current character is an unquoted `$`

=> identify introductory sequence :
- `$` : see [parameter expansion (SCL)](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02) **=> implement partially**
- `$?`: "Expands to the decimal exit status of the most recently executed foreground pipeline." - [Bash reference manual - Special parameters](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Special-Parameters)

=> read sufficient input to determine the end of the unit to be expanded (see [parameter expansion](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02))<br>
=> recursion (nested $) **=> don't implement**<br>
=> The token shall not be delimited by the end of the substitution.

See `Requirements.md#Metacharacter_handling`

###### Parameter expansion (`$`)
=> rules to prepare parameter expansion, which is done after tokenization
IF
- parameter is not in braces `{}`
- parameter is a name

=> the expansion shall use the longest valid name (see XBD Name), whether or not the variable represented by that name exists
=> Otherwise, the parameter is a single-character symbol, and behavior is unspecified if that character is not `?`

IF
- a parameter expansion occurs inside double-quotes

=> Pathname expansion shall not be performed on the results of the expansion. (e.g. `VAR="ls /etc/*.conf" && echo $VAR` will not expand the `*`)

=> Field splitting shall not be performed on the results of the expansion.

General note on Word Splitting ([AOSA Book - Bash](https://aosabook.org/en/v1/bash.html)):
> 3.5.3. Word Splitting
The results of the word expansions are split using the characters in the value of the shell variable `IFS` as delimiters. This is how the shell transforms a single word into more than one. Each time one of the characters in `$IFS` appears in the result, bash splits the word into two. Single and double quotes both inhibit word splitting.

##### 2.2.2.6. New operator token
IF
- current character is unquoted
- current character can be used as the first character of a new operator

=> delimit the current token, if any<br>
=> use the current character as the beginning of the next (operator) token

#### 2.2.2.7. Space or tab
(N.b.: "A blank is a space or tab character" cf. [Bash reference manual - Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions))

IF
- current character is an unquoted \<space\> or \<tab\>

=> delimit any token containing previous character<br>
=> discard current character

#### 2.2.2.8. Previous character part of a word
IF
- previous character was part of a word

=> append current character to that word

N.b.: added => check if previous token delimited

<details>
####<summary><b>2.2.2.9. Comment (#) <i>=> don't implement</i></b></summary>
IF
- current character is a `#`

=> discard as a comment the current character and all subsequent characters up to but not including the next \<newline\>

n.b.: see how zsh does it (doesn't interpret them in interactive mode) ([Stackexchange](https://apple.stackexchange.com/a/405317))
</details>

#### 2.2.2.10 New word
=> use current character as the start of a new word


After delimiting a token, the next step is to categorize it following the Shell Grammar.


## 3. [Shell Grammar](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10)

### Preliminary note: Syntax rules and BNF
> The syntax rules for the language can be written down in Backus-Naur Form (BNF) or a similar notation
> - A BNF grammar is a list of syntax rules
> - Each rule defines one "nonterminal symbol", which appears at the left of a " := " sign in the rule
> - Alternative definitions of the nonterminal symbol appear to the right of the " := " sign, separated by " | " signs
> - Often the definition of a nonterminal in a BNF grammar is recursive: it defines the nonterminal in terms of itself

>- The nonterminal symbol defined in rule listed first in the grammar is called the "start" symbol of the grammar
>- A symbol not defined by a rule in the grammar is a "terminal symbol", and is usually taken literally
>- If a string satisfies the definition of the "start" symbol, it is in the language defined by the BNF grammar; otherwise not
>- The process of using the grammar to check to see if a string is in the language is called **parsing** the string

Source: [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf)


Note: (from [Introduction - Grammar Conventions - POSIX.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap01.html#tag_17_03))
> The following typographical conventions are used in the grammar; they have no significance except to aid in reading.

- identifiers for reserved words: leading capital letter (these are terminals in the grammar; for example, While, Case.)

- identifiers for terminals: named with uppercase letters and underscores; for example, NEWLINE, ASSIGN_OP, NAME.

- identifiers for non-terminals: all lowercase

### Parsing principles
- For each derivation from a grammar, there is a corresponding **parse tree**
- Each node in the **parse tree** corresponds to one symbol in the BNF grammar:
	- Leaves: terminal symbols
	- Internal nodes: nonterminal symbols
	- Root: start symbol
- The **children of an internal node in the parse tree** correspond to the symbols in a definition of the nonterminal symbol corresponding to their parent node
- Reading the leaves of the parse tree left to right gives you the string that has been parsed


### 3.0. Token identifiers
- Operator token identifier:
	- NEWLINE
	- PIPELINE `|`
	- INPUT_REDIRECT `<`
	- OUTPUT_REDIRECT  `>`
	- DGREAT `>>` (redirect output in append mode)
	- DLESS `<<` (Here Documents)
- IO_NUMBER
- WORD
- NAME
- ASSIGNMENT_WORD

Rules for determining what a token is:

### 3.1. Token classification
Apply the following rules in order:
#### 3.1.1 Operator
IF
- the token is an operator (n.b.: in our case \<newline\>, redirections, `>`, `<`, `>>`, `<<`, or a pipe `|`)

=> return the token identifier for that operator

#### 3.1.2. IO_number
ELSE IF
- the string consists solely of digits and the delimiter character is `<` or `>`

=> return the token identifier IO_NUMBER

#### 3.1.3. Unclassified token
ELSE<br>
=> return the token identifier TOKEN<br>
=> follow the rules below to categorize TOKEN as WORD, NAME, or ASSIGNMENT_WORD


### 3.2. Unclassified token
Tokens are classified in a context-dependent way, according to the following rules applied in order:
<details>
<summary><b><i>Grammar rules we don't need to implement</i></b></summary>
3.2.4. Reserved word 'esac' `=> don't implement`<br>
3.2.6. Third word of for and case `=> don't implement`<br>
3.2.8. NAME in function `=> don't implement`<br>
</details>

#### 3.2.1. Reserved word
N.b.: "Rule 1 is not directly referenced in the grammar, but is referred to by other rules, or applies globally."<br>
IF
- token is not exactly a reserved word

=> the token WORD shall be returned<br>
=> note: at this point quotes are retained in the token, so they must be included in the comparison with reserved words
#### 3.2.2. Redirection to or from filename
> the expansions specified in [Redirection](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10) shall occur. As specified there, exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.
#### 3.2.3. Redirection from here-document
IF
- any part of the delimiting word is quoted

=> remove quotes to determine the delimiter<br>
=> don't perform parameter expansion in the here-document

ELSE IF
- the delimiting word is unquoted

=> all lines of the here-document are subjected to parameter expansion
#### 3.2.7 Assignment preceding command name
a) IF
- the first word `=> of what ?` does not contain the character `=`

=> apply rule 3.2.1. (return token identifier WORD)

ELSE<br>
=> apply rule b:<br>
b) IF
- the token contains an unquoted `=` that is not part of an embedded parameter expansion construct (see [rule 5 in Token recognition](#2225-parameter-expansion)):
	- if it begins with `=`
		=> the token identifier is WORD
	- if all characters preceding `=` are underscores, digits, or alphabetics from the [portable character set](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap06.html#tag_06_01) (see [definition of a name](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap03.html#tag_03_230))
		=> the token identifier is ASSIGNMENT_WORD
	- else
		=> the token identifier is either ASSIGNMENT_WORD or WORD (unspecified)
c. ELSE
		=> the token identifier is WORD

> Assignment to the name within a returned ASSIGNMENT_WORD token shall occur as specified in [Simple Commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01).
<br>&emsp;`=> ?`

#### 3.2.9. Body of function
=> Word expansion and assignment don't occur
=> Each TOKEN is returned as a single WORD consisting of characters that are exactly the token described in Token Recognition

### 3.3 Parameter expansion


### 3.4 Redirections
#### 3.4.1. Types of redirection
#### 3.4.1.1. Input redirection
- IF
	- General format: `[n]<word`

	=> perform filename expansion of *word*<br>
	=> open the resulting file for reading:<br>
		&emsp;- IF<br>
				- n is specified<br>
					=> on file descriptor n<br>
		&emsp;- ELSE<br>
				- on stdin (file descriptor 0)<br>

#### 3.4.1.2. Output redirection
- IF
	- General format: `[n]>word`

	=> perform filename expansion of *word*:<br>

	&emsp; IF<br>
	&emsp;&emsp;- the file does not exist:<br>
	&emsp;&emsp;=> create the file<br>
	&emsp; ELSE<br>
	&emsp;&emsp;=> truncate the file to zero size<br>

	=> open the resulting file for writing:<br>

	&emsp; - IF<br>
				- n is specified<br>
					=> on file descriptor n<br>
	&emsp; - ELSE<br>
				- on stdout (file descriptor 1)<br>

#### 3.4.1.3. Append redirected output
- IF
	- General format: `[n]>>word`

	=> perform filename expansion of *word*:<br>

	&emsp; IF<br>
	&emsp;&emsp;- the file does not exist:<br>
	&emsp;&emsp;=> create the file<br>

	=> open the resulting file for appending:<br>

	&emsp; - IF<br>
				- n is specified<br>
					=> on file descriptor n<br>
	&emsp; - ELSE<br>
				- on stdout (file descriptor 1)<br>

#### 3.4.1.4. Here Documents
IF
	- General format:
	```bash
	[n]<<word
		here-document
	delimiter
	```

	=> do not perform any parameter expansion or filename expansion on *word*
	=> read input from the current source until a line containing only *word* (with no trailing tabs or spaces) is seen
	=> use all the lines read up to that point as the standard input (or file descriptor *n* if *n* is specified) for a command

- IF
	- any part of *word* is quoted

	=> the *delimiter* is the result of quote removal on *word*
	=> the lines in the here-document are not expanded

- ELSE
	=> the lines in the here-document are subject to parameter expansion
	=> ignore the character sequence `\newline`

#### 3.4.2. Expansions in redirections
- IF
	- a parameter or filename expansion can be performed on the word following the redirection operator 

	=> Perform the expansion

		- IF
			- the expansion produces more than one word
				=> report an error

#### 3.4.3. Failure to open or create a file
- IF
	- there is a failure to open or create a file for a redirection

	=> the redirection fails

#### 3.4.4. Special filenames in redirections
- IF
	- the operating system on which Bash is running provides these special files, 
	
	=> use them
	
ELSE

	=> emulate them internally with the behavior described below

```
/dev/fd/fd

    If fd is a valid integer, file descriptor fd is duplicated.
/dev/stdin

    File descriptor 0 is duplicated.
/dev/stdout

    File descriptor 1 is duplicated.
/dev/stderr

    File descriptor 2 is duplicated.
/dev/tcp/host/port

    If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding TCP socket.
/dev/udp/host/port

    If host is a valid hostname or Internet address, and port is an integer port number or service name, Bash attempts to open the corresponding UDP socket. 
```

#### 3.4.5. Lack of file descriptor number (Implicit redirections)
- IF
	- the file descriptor number is omitted, and
	- the first character of the redirection operator is ‘<’

=> the redirection refers to the standard input (file descriptor 0)

- IF
	- the file descriptor number is omitted, and
	- the first character of the redirection operator is ‘>’

=> the redirection refers to the standard output (file descriptor 1)


## 4. [Command execution](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09)
A **command** is either a **simple command** or a **pipeline**.
- Unless otherwise cited, the exit status of a command shall be that of the last simple command executed by the command.
- No limit on the size of a command except the system limits (memory constraints, {ARG_MAX}, etc.)

### 4.0. General execution considerations
### 4.0.1. Shell Execution environment
- See [Shell Execution Environment](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_12)

- A shell execution environment consists of the following:

	- Open files inherited upon invocation of the shell, plus open files controlled by exec
	- Working directory as set by `cd`
	- Shell parameters from the environment inherited by the shell when it begins (see the `export` built-in)

- Utilities other than the built-in
=> shall be invoked in a separate environment that consists of the following. The initial value of these objects shall be the same as that for the parent shell, except as noted below:

	- Files:
		- Open files inherited on invocation of the shell
		- open files controlled by the exec special built-in plus any modifications
		- additions specified by any redirections to the utility

    - Current working directory

    - Variables with the export attribute, along with those explicitly exported for the duration of the command, shall be passed to the utility environment variables

	- The environment of the shell process shall not be changed by the utility unless explicitly specified by the utility description (for example, `cd`)

	- A subshell environment shall be created as a duplicate of the shell environment

	- Changes made to the subshell environment shall not affect the shell environment. 

	- each command of a multi-command pipeline is in a subshell environment. All other commands shall be executed in the current shell environment.

#### 4.0.2. Environment
- The environment for any simple command or function may be augmented temporarily by prefixing it with parameter assignments, as described in Shell Parameters. These assignment statements affect only the environment seen by that command.

=> `export VAR=2 | echo $VAR` => ""
=> `export` or `unset` in a subshell have not effect outside the subshell

#### 4.0.3. Exit status
- The exit status of an executed command is the value returned by the `waitpid` system call or equivalent function.
- Exit statuses fall between 0 and 255, although the shell may use values above 125 specially (see explanations below). Exit statuses from shell builtins are also limited to this range. Under certain circumstances, the shell will use special values to indicate specific failure modes.

#### 4.0.3.1. Success and failure:
	- IF
		- a command succeeds
		
		=> exit status zero

	- ELSE

		=> non-zero exit status (indicates failure)

#### 4.0.3.2. Types of failure
- IF
	- a command terminates on a fatal signal
	- the fatal signal number is N, Bash uses the value 
	
	=> the exit status is 128+N

- IF
	- a command is not found
	
	=> the child process created to execute it returns a status of 127

- IF
	- a command is found
	- the command is not executable
	
	=> the child process created to execute it returns a status of 126

- IF

	- an error during parameter expansion or redirection causes a command to fail
	
	=> the exit status is greater than zero (POSIX: between 1 and 125 inclusive)


#### 4.0.3.2. Exit status of builtins
- All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure

- IF
	- the builtin is used incorrectly
	OR
	- there are generally invalid options
	OR
	- there are missing arguments
	
	=> exit status is 2

#### 4.0.3.2. Exit status of last command
- Store the exit status of the last command (== "the most recently executed foreground pipeline") in the special parameter `$?`

#### 4.0.4. Signals
See [Bash reference manual - Signals](https://gnu.org/software/bash/manual/bash.html#Signals)

### 4.1. Command types
#### 4.1.1. [Simple commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01)
[Bash](https://www.gnu.org/software/bash/manual/bash.html#Simple-Commands):<br>
> a sequence of words separated by blanks, terminated by one of the shell’s control operators (only `|` in our case)<br>
> The first word generally specifies a command to be executed, with the rest of the words being that command’s arguments.<br>
> The return status (see Exit Status) of a simple command is its exit status as provided by the POSIX 1003.1 `waitpid` function, or 128+n if the command was terminated by signal n.

POSIX:<br>
A sequence of optional variable assignments and redirections, in any sequence, optionally followed by words and redirections, terminated by a control operator (\<newline\>, `|`, "the end-of-input indicator used internally by the shell").

Command execution sequence:
1. variable assignments and redirection recognition:<br>
IF
	- some words recognized as variable assignments or redirections according to the [Shell Grammar](#3-shell-grammar)

	=> save these words for processing in steps 3. and 4.

2. expansion of the other words:<br>
IF 
	- some words are not variable assignments or redirections

	=> expand those words:<br>
	&emsp;	- parameter expansion<br>
	&emsp;	- [filename expansion](https://www.gnu.org/software/bash/manual/bash.html#Filename-Expansion)/ Pathname-resolution.md<br>
	&emsp;	- IF<br>
	- expansion performed<br>
	-  any fields (\<space\> or \<tab\>) remain following the expansion of the words

	&emsp;&emsp;		=> perform [word splitting](https://www.gnu.org/software/bash/manual/bash.html#Word-Splitting)

3. redirections<br>
IF
	- there are any redirections

=> perform the redirections (see [Redirection](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07))

4. variable assignment expansion<br>
IF
	- there are any variable assignments
	- the variable assignments have possible expansions (parameter expansion or quote removal)

=> perform the expansions before assigning the value:<br>
	- parameter expansion
	- quote removal

Other rules for variable assignments and redirections:<br>

1. Command name results ?<br>
IF
	- no command name results

=> variable assignments affect the current execution environment
=> assignment statements are performed before redirections
=> redirections are performed, but do not affect the current shell environment
=> A redirection error causes the command to exit with a non-zero status

ELSE<br>
- the variables are added to the environment of the executed command and do not affect the current shell environment
	(..)

2. Command name left after expansion ?<br>
IF
	- there is a command name left after expansion

=> execution proceeds as described below

ELSE

=> the command exits


#### 4.1.2. Pipelines
- Pipeline: a sequence of one or more commands separated by the control operator `'|'`
- For each command, except the last, the shell shall:
	- connect the standard output of the command to the standard input of the next command
	- as if by creating a pipe, and passing the *write end of the pipe* as **the standard output of the command** and the *read end of the pipe* as the **standard input of the next command**

- Format for a pipeline: `command1 [ | command2 ...]`

- The standard output of command1 shall be connected to the standard input of command2.

- Redirections: 
	IF
	- a command has redirections specified by redirection operators

	=> the standard input, standard output, or both of a command shall be considered to be assigned by the pipeline before any redirections

- The shell shall wait for the last command specified in the pipeline to complete, and may also wait for all commands to complete

- Execution environment:
	- A subshell environment shall be created as a duplicate of the shell environment, except that signal traps that are not being ignored shall be set to the default action.
	- Each command of a multi-command pipeline is in a subshell environment; as an extension, however, any or all commands in a pipeline may be executed in the current environment.
	- All other commands shall be executed in the current shell environment.

- Exit Status: the exit status of the last command specified in the pipeline

### 4.2. [Command Search and Execution](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01_01)
IF<br>
	- a simple command results in a command name and an optional list of arguments, the following actions shall be performed:

#### 4.2.1. No slash  `/`  characters in the command<br>
IF<br>
	- the command name does not contain any slash `/` characters

=> the first successful step in the following sequence shall occur:

##### 4.2.1.a. built-in match
	IF
	- the command name matches the name of a built-in utility
		=> invoke that built-in utility

##### 4.2.1.b. PATH search
	ELSE
	=> search for the command using the PATH environment variable as described in XBD Environment Variables :
		(...)
##### 4.2.1.b.1. successful PATH search
IF<br>
	- search is successful

	IF
	- the utility is a built-in
		=> invoke the built-in

	ELSE
		=> execute the utility in a separate ?utility? environment (see Shell Execution Environment) with actions equivalent to calling the execl() function with arguments:

		- path:
		set to the pathname resulting from the search

		- arg0:
		set to the command name

		- remaining execl() arguments:
		set to the command arguments (if any) and the null terminator
			
		IF
		- execl() fails due to an error equivalent to the [ENOEXEC] error defined in (POSIX.1-2017 - System Interfaces)
		=> execute a command equivalent to having a shell invoke with arguments:
		- first operand: the pathname resulting from the search
		- any remaining arguments passed to the shell

			IF
			- the executable file is not a text file
			=> the shell may bypass this command execution, and:
			=> return an exit status of 126
			=> write an error message

##### 4.2.1.b.2. unsuccessful PATH search
ELSE<br>
	- search is unsuccessful<br>

=> command fails with exit status 127<br>
=> shell writes an error message

### 4.2.2. Slash `/` characters in the command<br>
IF<br>
	- the command name contains at least one slash `/` character
	<br>(..)

=> execute the utility in a separate utility environment with actions equivalent to calling the execl() function with arguments:
- path:
set to the command name
- arg0:
set to the command name
- remaining execl() arguments:
		set to the command arguments (if any) and the null terminator

	IF<br>
		- execl() fails due to an error equivalent to the [ENOEXEC] error defined in (POSIX.1-2017 - System Interfaces)

	=> execute a command equivalent to having a shell invoked with:
	- the command name as its first operand
	- any remaining arguments passed to the shell<br><br>
		IF
		- the executable file is not a text file:<br>

		=> the shell may bypass this command execution, and:<br>
		=> return an exit status of 126<br>
		=> write an error message

#### [Quote removal](https://www.gnu.org/software/bash/manual/bash.html#Quote-Removal)
> After the preceding expansions, all unquoted occurrences of the characters ‘\’, ‘'’, and ‘"’ that did not result from one of the above expansions are removed.

## Built-ins
Built-ins implement functionality impossible or inconvenient to obtain via separate utilities. For example, `cd`, `break`, `continue`, and `exec` cannot be implemented outside of the shell because they directly manipulate the shell itself. The `history`, `pwd`, `kill`, or `getopts` builtins, among others, could be implemented in separate utilities, but they are more convenient to use as builtin commands.

## Definitions
See: [POSIX.1-2017 - Definitions](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html)

### [Name](https://www.gnu.org/software/bash/manual/bash.html#index-name)
> A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore. Names are used as shell variable and function names. Also referred to as an identifier.

#### Operator
> In the shell command language, either a control operator or a redirection operator.

### [Control Operator](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_113)
> In the shell command language, a token that performs a control function. It is one of the following symbols:

&   &&   (   )   ;   ;;   newline   |   ||

>The end-of-input indicator used internally by the shell is also considered a control operator.

### [Reserved word](https://www.gnu.org/software/bash/manual/bash.html#index-reserved-word)
> A word that has a special meaning to the shell. Most reserved words introduce shell flow control constructs, such as for and while.

### Redirection
> In the shell command language, a method of associating files with the input or output of commands. 

### Redirection Operator
>In the shell command language, a token that performs a redirection function. It is one of the following symbols:

<     >     >|     <<     >>     <&     >&     <<-     <>

### [Word](https://www.gnu.org/software/bash/manual/bash.html#index-word)
Bash reference manual:
> A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

POSIX definition:
> In the shell command language, a token other than an operator. In some cases a word is also a portion of a word token: in the various forms of parameter expansion, such as `${name-word}`, and variable assignment, such as `name=word`, the word is the portion of the token depicted by `word`. The concept of a word is no longer applicable following word expansions—only fields remain.

Note:
    For further information, see [XCU 2.6.2 Parameter Expansion](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06_02) and [2.6 Word Expansions](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_06) . 