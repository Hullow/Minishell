# Shell functioning
How the shell works according to the [Shell Command Language definition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) and [Bash reference manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html), summarized, paraphrased and simplified for the Minishell project.

## 1. Reads input
### Input sources
(see Requirements.md -> to clarify)
- Shell reads lines
- From stdin
- From command line string (with `readline`)
- From a file

### Input characteristics
- length: unlimited

## 2. Tokenization
### 2.0 Tokenization summary
- Shell breaks input into tokens:
	- [**words**](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
	> A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.
	- [**operators**](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
    > A **control operator** or a **redirection operator**. Operators contain at least one unquoted metacharacter.
- Tokens are separated by [metacharacters](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions):
	> A character that, when unquoted, separates words:
	- space, tab, newline (whitespace)
	- `|` (pipe)
	- `<`, `>` (redirection)
	- (`&` , `;` , `(`, `)`. `=> don't implement`)
- Metacharacters and other special characters between quotes are not interpreted, except for `$` between double quotes
- Redirections operators:
	- `> < <> >& <& <<< << >> &>> &> >|`
### 2.1. [Quoting rules](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Quoting)
- Tokenization follows the quoting rules:
> Quoting is used to remove the special meaning of certain characters or words to the shell, including to prevent parameter expansion.
> Each of the shell metacharacters has special meaning to the shell and must be quoted if it is to represent itself.
- Quoting mechanisms:
	- Single quotes `'`:
		- Preserves the literal value of each character within the quotes
		- A single quote may not occur between single quotes
	- Double quotes `"`:
		- Preserves the literal value of all characters within the quotes, except `$`
		- A double quote may not occur between double quotes
		<br>(n.b.: because "A double quote may be quoted within double quotes by preceding it with a backslash." `=> don't implement backslash`
- Example:
```bash
bash-3.2$ VAR=2
bash-3.2$ echo VAR
VAR
bash-3.2$ echo $VAR
2
bash-3.2$ echo "$VAR"
2
bash-3.2$ echo '$VAR'
$VAR
bash-3.2$ echo "'$VAR'"
'2'
bash-3.2$ echo '"$VAR"'
"$VAR"
bash-3.2$ echo "'"$VAR"'"
'2'
bash-3.2$ echo ""'"$VAR"'""
"$VAR"
bash-3.2$ echo """'"$VAR"'"""
'2'
bash-3.2$ echo """"'"$VAR"'""""
"$VAR"
```

### 2.2. Token classification
#### 2.2.1. Here-documents processing
IF
- an **io_here** token has been recognized by the grammar

=> one or more of the subsequent lines immediately following the next NEWLINE token form the body of one of more here-documents<br>
=> the here-document(s) are parsed according to the [rules of Here-Document](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_07_04)
#### 2.2.2. [Ordinary token recognition](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03)
How to delimit tokens:<br>
- break input into tokens by applying the first applicable rule below to the next character in its input.
- the token shall be from the current position in the input until a token is delimited according to one of the rules below
- the characters forming the token are exactly those in the input, including any quoting characters.
- if is indicated that a token is delimited, and no characters have been included in a token, processing shall continue until an actual token is delimited. `=>?`

<br>**Rules**:
#### Tokenization functions requirements
Based on the rules below, here are some requirements for our tokenization functions:
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

=> return the end-of-input indicator as the token

##### 2.2.2.2. Continued operator token and current character usable
IF
- previous character used as part of an operator
- current character can be used with the current characters to form an operator
- current character not quoted

=> use character as part of that (operator) token

##### 2.2.2.3. Continued operator token and current character not usable
IF
- previous character used as part of an operator
- current character cannot be used with the current characters to form an operator

=> delimit the operator containing the previous character

##### 2.2.2.4. Quotes
IF
- the current character is single-quote `'` or double-quote `"`
- the current character is not quoted

=> affects quoting for subsequent characters up to the end of the quoted text (see [Quoting rules](#21-quoting-rules))<br>
=> During token recognition, no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, including any embedded or enclosing quotes or substitution operators, between the quotation mark and the end of the quoted text. `=> ?`<br>
=> The token shall not be delimited by the end of the quoted field.

##### 2.2.2.5. Parameter and arithmetic expansion, command substitution (`$` and '`')
IF
- the current character is an unquoted `$` or '`'

=> identify introductory sequence :
- `$` or `${` : [parameter expansion](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02) **=> implement partially**
- `$(` or '\`' : command substitution **=> don't implement**
- `$((` : arithmetic expansion **=> don't implement**<br>

=> read sufficient input to determine the end of the unit to be expanded (see [parameter expansion](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02))<br>
=> recursion (nested $) **=> don't implement**<br>
=> The token shall not be delimited by the end of the substitution.

See Requirements.md#Metacharacter_handling

###### Parsing of $/Parameter Expansion rules according to cmegret & fallan
=> See ft_check_export (nb fallan: should be ft_check_expansion)

- When `$`, start
- if digit
	=> expand with empty string `char *str; str[0] = '\0' and skip the 2 characters (`$` + `digits`)
- if `?`, expand => call ft_expansion avec parameter 1
- while lowercase letter, uppercase letter, `_`, digits 0-9
	=> continue
- else
	=> if possible to expand to the previous character, expand
	=> else: don't expand, return to `$`
- if ` ` or `EOF`

###### Parameter expansion
> If parameter is not in braces `{}`, and is a name, the expansion shall use the longest valid name (see XBD Name), whether or not the variable represented by that name exists. Otherwise, the parameter is a single-character symbol, and behavior is unspecified if that character is neither a digit nor one of the special parameters (see Special Parameters).

IF
- a parameter expansion occurs inside double-quotes

=> Pathname expansion shall not be performed on the results of the expansion. (e.g. `VAR="ls /etc/*.conf" && echo $VAR` will not expand the `*`)

=> Field splitting shall not be performed on the results of the expansion.

##### 2.2.2.6. New operator token
IF
- the current character is unquoted
- the current character can be used as the first character of a new operator

=> delimit the current token, if any<br>
=> use the current character as the beginning of the next (operator) token

#### 2.2.2.7. Blank character
N.b.: a "blank" is a space or tab character. (cf. [Bash reference manual - Definitions](https://www.gnu.org/software/bash/manual/bash.html#Definitions))

IF
- the current character is an unquoted \<blank\>

=> delimit any token containing the previous character<br>
=> discard the current character

#### 2.2.2.8. Previous character part of a word
IF
- the previous character was part of a word

=> append the current character to that word

#### 2.2.2.9. Comment (`#`) `=> don't implement`
IF
- the current character is a `#`

=> discard as a comment the current character and all subsequent characters up to but not including the next \<newline\>

#### 2.2.2.10 New word
=> use the current character as the start of a new word

After delimiting a token, the next step is to categorize it following the [Shell Grammar](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10)


## 3. Shell Grammar
Rules for determining what a token is

### 3.1 Initial classification
Apply the following rules in order (if, else if, else if, else)
### 3.1.1 Newline
IF
- a newline is found

=> return the newline as token identifier NEWLINE

### 3.1.2 Operator
ELSE IF
- the token is an operator (n.b.: in our case redirections `>`, `<`, `>>`, `<<`, or a pipe `|`)

=> return the token identifier for that operator `=> ???`
>("If the token is an operator, the token identifier for that operator shall result")
=> does this mean `|` 

### 3.1.2 Operator
IF
- the string consists solely of digits and the delimiter character is `<` or `>`

=> return the token identifier IO_NUMBER

ELSE
=> return the token identifier TOKEN

N.b.: further distinction on TOKEN is context-dependent. The same TOKEN can be considered a WORD, a NAME, an ASSIGNMENT_WORD, or a reserved below from the below list. Some of the productions in the grammar below are annotated with a rule number from the following list. When a TOKEN

### 3.2. Shell grammar rules
#### 3.2.3. Reserved word
#### 3.2.4. Redirection to or from filename
#### 3.2.5. Name
IF
- the token meets requirements for a name (see [definition](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap03.html#tag_03_230))

- the token identifier is NAME

ELSE
- the token identifier is WORD
#### 3.2.7 Assignment preceding command name
a. IF
- the first word does not contain the character `=`

=> apply rule 3.1.

ELSE
=> apply rule b.
b. IF
- the token contains the equal sign character:
	- if it begins with `=`
		=> the token identifier is WORD
	- if all characters preceding '=' form a valid name (see [definition](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/xbd_chap03.html#tag_03_230))
		=> the token identifier is ASSIGNMENT_WORD (quoted characters cannot participate in forming a valid name)
	- else
		=> the token identifier is either ASSIGNMENT_WORD or WORD (unspecified)

#### 3.2.9. Body of function
When the token is exact



## Definitions
### Operator

> In the shell command language, either a control operator or a redirection operator.

### Control Operator
> In the shell command language, a token that performs a control function. It is one of the following symbols:

&   &&   (   )   ;   ;;   newline   |   ||

>The end-of-input indicator used internally by the shell is also considered a control operator.

ref: [POSIX.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_260)

### Redirection

> In the shell command language, a method of associating files with the input or output of commands. 

### Redirection Operator

>In the shell command language, a token that performs a redirection function. It is one of the following symbols:

<     >     >|     <<     >>     <&     >&     <<-     <>

