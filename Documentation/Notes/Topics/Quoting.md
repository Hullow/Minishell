# Quoting

## Requirements
> • Not interpret unclosed quotes or special characters which are not required by the
subject such as `\` (backslash) or `;` (semicolon).<br>
> • Handle `’` (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.<br>
> • Handle `"` (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for `$` (dollar sign).

## 0. Summary
> 1. Reads its input from the user’s terminal.
> 2. Breaks the input into words and operators, obeying the quoting rules. These tokens are separated by metacharacters.

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
		- Examples: see "Tests" below

[POSIX-2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_02):
- The application shall quote the following characters if they are to represent themselves:
> |  &  ;  <  >  (  )  $  `  \  "  '  <space>  <tab>  <newline>

and the following might need to be quoted under certain circumstances. That is, these characters are sometimes special depending on conditions described elsewhere in this volume of POSIX.1-2024:

> *  ?  [  ]  ^  -  !  #  ~  =  %  {  ,  }

	
### [Word](https://www.gnu.org/software/bash/manual/bash.html#index-word)
Bash reference manual:
> A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

<br>**Rules**:
#### Tokenization functions requirements
Based on the rules below, here are some proposed requirements for our tokenization functions:
- Token status: is there a current token ?
- Usage of the previous character : word or operator token ?
- Quoting status : is current character quoted or not ?
- Delimitation of token to previous character

##### 2.2.2.2. Continued operator token and current character usable
IF
- current character not quoted
- previous character used as part of an operator ==> 

<br> &emsp;=> only `>>` or `<<` in our case

=> use character as part of that (operator) token

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

#### 3.2.3. Redirection from here-document
(Rule 3)
IF
- any part of the delimiting word is quoted

=> remove quotes to determine the delimiter<br>
=> don't perform parameter expansion in the here-document

ELSE IF
- the delimiting word is unquoted

=> all lines of the here-document are subjected to parameter expansion


## (rule 7b)
(..)<br>
b) IF
- the token contains an unquoted `=` that is not part of an embedded parameter expansion construct (see [rule 5 in Token recognition](#2225-parameter-expansion)):

(..)

#### 3.4.1.4. Here Documents
IF
	- General format:
	```bash
	<<word
		here-document
	delimiter
	```

	=> do not perform any parameter expansion or filename expansion on *word*
	=> read input from the current source until a line containing only *word* (with no trailing tabs or spaces) is seen
	=> use all the lines read up to that point as the standard input for a command

- IF
	- any part of *word* is quoted

	=> the *delimiter* is the result of quote removal on *word*
	=> the lines in the here-document are not expanded

- ELSE
	=> the lines in the here-document are subject to parameter expansion
	=> ignore the character sequence `\newline`


#### 4.1.1. Simple commands
(..)
4. variable assignment expansion<br>
IF
	- there are any variable assignments
	- the variable assignments have possible expansions (parameter expansion or quote removal)

=> perform the expansions before assigning the value:<br>
	- parameter expansion
	- quote removal

#### [Quote removal](https://www.gnu.org/software/bash/manual/bash.html#Quote-Removal)
> After the preceding expansions, all unquoted occurrences of the characters ‘\’, ‘'’, and ‘"’ that did not result from one of the above expansions are removed.

## Method
- how to verify if current character is unquoted: have a "quote" struct that counts how many quotes we are in ?

## Examples
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
bash-3.2$ echo '"""'"$VAR"'"""'
"""2"""
bash-3.2$ echo '""''"$VAR'""'"'
"""$VAR"
bash-3.2$ echo '"'"'"'"$VAR'""'"'"'"
"'"$VAR"'
```

- Manual decomposition:
```bash
bash-3.2$ echo "'$VAR'"
'2'
```
=> Between double quotes, so parameter expanded

```bash
bash-3.2$ echo '"$VAR"'
"$VAR"
```
=> Between double quotes, so should be expanded, but all this is between single quotes, thus literal value of each character, including the double quotes

```bash
bash-3.2$ echo "'"$VAR"'"
'2'
```
=> From left to right:
1. `"'"` => `'`
2. `$VAR` => `2`
3. `"'"` => `'`

```bash
bash-3.2$ echo ""'"$VAR"'""
"$VAR"
```
=> From left to right:
1. `""` => {}
2. `'"$VAR"'` => `"$VAR"`
3. `""` => {}

```bash
bash-3.2$ echo '"'"'"'"$VAR'""'"'"'"
"'"$VAR"'
```
=> From left to right:
1. `'"'` => `"`
2. `"'"` => `'`
3. `'"$VAR'` => `"$VAR`
4. `""` => {}
5. `'"'` => `"`
6. `"'"` => `'`