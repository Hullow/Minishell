/*
Simplified grammar to implement:
command   		 : cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD

cmd_suffix       : 			  WORD
                 | cmd_suffix WORD
*/

Parsing `ls -la`:
start: command => cmd_name cmd_suffix => WORD cmd_suffix => WORD WORD


Parsing `cp -r directory`:

start:
- command

=>(more than one token, therefore:)
- cmd_name
- cmd_suffix

=>(leftmost parsing)
- WORD (token `cp`) 
- cmd_suffix (non-empty node in token list: token list starting with `-r`, followed by token `directory`)

=>(cmd_suffix has more than one token, therefore:)
- WORD (token `cp`)
- cmd_suffix (non-empty node in token list starting with `-r`) 
- WORD (token `directory`) => go to last token ?

Parsing `find . -name "notes.txt"`:

start:
- command

=> (more than one token, therefore:)
- cmd_name (token `find`)
- cmd_suffix (token list starting with `.`)

=>(leftmost parsing, therefore:)
- WORD (token `find`)
- cmd_suffix (token list starting with `.`)

=> (token followed by non-empty token node in list therefore:)
- WORD (token `find`)
- cmd_suffix ()
- WORD (token `"notes.txt"`, because last token in list).

-> procedure: copy start node (where cmd_suffix starts), go to last token in list and assign it the type WORD
-> come back to start node
	-> if only one node after it, i.e. if next.next == NULL, then assign type WORD
	-> else, continue until list entirely assigned types ? or until NULL is returned to the top ?

`cp file1.txt file2.txt file3.txt /destination/directory/`

command
- cmd_name (`cp`) cmd_suffix (`file1.txt file2.txt file3.txt /destination/directory/`)
cmd_suffix: tokens to evaluate to the right: 4 counted (to the end)

- WORD (`cp`) cmd_suffix (`file1.txt file2.txt file3.txt /destination/directory/`)

cmd_suffix: tokens to evaluate to the right: 4
- WORD (`cp`) cmd_suffix (`file1.txt file2.txt file3.txt`) WORD (`/destination/directory/`)

cmd_suffix: tokens to evaluate to the right: 4-- => 3 
- WORD (`cp`) cmd_suffix (`file1.txt file2.txt`) WORD (`file3.txt`) WORD (`/destination/directory/`)

- WORD (`cp`) cmd_suffix (`file1.txt`) WORD (`file3.txt`) WORD (`/destination/directory/`)

=>(because no last token)
- WORD (`cp`) WORD (`file1.txt`) WORD (`file3.txt`) WORD (`/destination/directory/`)

tokens to evaluate to the right:  