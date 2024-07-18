# Shell functioning
How the shell works according to the [Shell Command Language definition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) and [Bash reference manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html), summarized, paraphrased and simplified for the Minishell project.

## 1. Reads input
### Input sources
(see `Requirements.md` -> `To clarify`)
- Shell reads lines
- From stdin
- From command line string (with `readline`)
- From a file

### Input characteristics
- length: unlimited

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
- previous character used as part of an operator
- current character can be used with the previous characterS to form an operator
- current character not quoted

=> use character as part of that (operator) token
<br>e.g.: previous character is `>`, current character is `>` => add it to `>>`

##### 2.2.2.3. Continued operator token and current character not usable
IF
- previous character used as part of an operator
- current character cannot be used with the current characters to form an operator

=> delimit the operator containing the previous character

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
### 3.0. Token identifiers:
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
#### 3.2.5. Name in `for` `=> implement or not ?`
IF
- the token consists solely of underscores, digits, and alphabetics from the [portable character set](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap06.html#tag_06_01) (see [definition of a name](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap03.html#tag_03_230))

=> the token identifier is NAME

ELSE<br>
=> the token identifier is WORD

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


## 4. [Shell Commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09)
A **command** is either a **simple command** or a **pipeline**.
- Unless otherwise cited, the exit status of a command shall be that of the last simple command executed by the command.
- No limit on the size of a command except the system limits (memory constraints, {ARG_MAX}, etc.)

### 4.1. Command types
### 4.1.1. [Simple commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01)
A sequence of optional variable assignments and redirections, in any sequence, optionally followed by words and redirections, terminated by a control operator (\<newline\>, `|`, "the end-of-input indicator used internally by the shell").

Command execution sequence:
1. variable assignments and redirection recognition:<br>
IF
- some words recognized as variable assignments or redirections according to the [Shell Grammar](#3-shell-grammar)

	=> save these words for processing in steps 3. and 4.

2. expansion of the other words:<br>
IF
- some words are not variable assignments or redirections

	=> expand those words `=> parameter expansion` ; `=> pathname expansion ?`<br>
=> IF<br>
&emsp;-  any fields (if there are \<space\> or \<tab\>) remain following the expansion of the words

3. redirections<br>
IF
- there are any redirections

=> perform the redirections (see [Redirection](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07))

4. variable assignment expansion<br>
IF
- there are any variable assignments
- the variable assignments have possible expansions (parameter expansion or quote removal)

=> perform the expansions before assigning the value

> Variable assignments shall be performed as follows:
>
> If no command name results, variable assignments shall affect the current execution environment.

(..)

### 4.1.2. Pipelines

### 4.2. [Command Search and Execution](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01_01)
IF<br>
- a simple command results in a command name and an optional list of arguments, the following actions shall be performed:

### 4.2.1. No slash  `/`  characters in the command<br>
IF<br>
- the command name does not contain any <slash> characters

=> the first successful step in the following sequence shall occur:

	a. special built-in utility
	IF
	- the command name matches the name of a special built-in utility

		=> invoke that special built-in utility

	(..)

	d. Match
	IF
	- the command name matches the name of a utility listed in the following table:
		- `cd`
		- `pwd`
		- (`bg alias command false fc fg getopts hash jobs kill newgrp read true umask type ulimit`)

		=> invoke that utility

	e. search command in PATH
	OTHERWISE

	=> search for the command using the PATH environment variable as described in XBD Environment Variables :

		(...)

### 4.2.2. Slash `/` characters in the command<br>
IF<br>
	- the command name contains at least one slash `/` character
	<br>(..)

#### [Quote removal](https://www.gnu.org/software/bash/manual/bash.html#Quote-Removal)
> After the preceding expansions, all unquoted occurrences of the characters ‘\’, ‘'’, and ‘"’ that did not result from one of the above expansions are removed.

## Definitions
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
> A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.