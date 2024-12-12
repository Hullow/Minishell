# `<<` ([Here Documents](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Here-Documents))
## Minishell requirement
<br>From subject:
	> should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!

##

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

#### 3.2.3. Redirection from here-document
(Rule 3)
IF
- any part of the delimiting word is quoted

=> remove quotes to determine the delimiter<br>
=> don't perform parameter expansion in the here-document

ELSE IF
- the delimiting word is unquoted

=> all lines of the here-document are subjected to parameter expansion

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

## Commentaire de @tfrily à 42
Expansion is different in Here-docs: 
```bash
<< 'EOF' cat
<< 'EOF' cat
<< "'EOF'" cat
```
etc.

## Tests
sort << EOF
> 2 
> 3
> 1
> 0
> -2
> EOF

echo "hello" > testfile
echo "world" >> testfile
echo "!" >> testfile
cat << EOF
> 
> testfile 
> 
> EOF

rm testfile
<< EOF
> echo "hello" > testfile
> echo "world" >> testfile
> EOF


ls << EOF | grep m
> EOF

cat << EOF
> $VAR1
> $VAR2
> EOF

cat << EOF | grep h
> $VAR1
> $VAR2

cat << EOF | grep h
> "$VAR1"
> "$VAR2"
> EOF

cat << EOF > file.txt
> hello 
> world
> EOF

cat << EOF
> file.txt 
> EOF

cat < file.txt 
hello 
world

cat << EOF < file.txt
> blabla
> EOF

cat << EOF < file.txt
> EOF

cat << EOF >> file.txt
> thank you
> very much
> EOF