// This is the shell grammar, processed to eliminate left recursion
// rules (from [Wikipedia - Left recursion](https://en.wikipedia.org/wiki/Left_recursion#Removing_direct_left_recursion))
// for a left-recursive non terminal A:
// A -> A alpha_1 | ... | A alpha_n | Beta_1 | ... | Beta_m
//
// Where each *alpha* is a nonempty sequence of nonterminals and terminals, and
// each *Beta* is a sequence of nonterminals and terminals that does not start with A
//
// Replace these with two sets of production, one set for A:
// 		A -> Beta_1 A' | ... | Beta_m A'
//
// and another set for the fresh nonterminal A' (often called the "tail" or the "rest"):
// 		A' -> alpha_1 A' | ... | alpha_n A' | epsilon (empty)
//
// repeat this process until no direct left recursion remains
MINISHELL GRAMMAR WITH DIRECT LEFT RECURSION
<br>(BEFORE preprocessing)
--------------------------------------------------------------------
													|	Form:
--------------------------------------------------------------------
// direct left recursion, adapt
program		 	 : command							|	Beta_1
                 | program '|' command				|	A alpha_1
                 ;

=> no direct left recursion, leave intact
command   		 : cmd_prefix cmd_word cmd_suffix	|	
                 | cmd_prefix cmd_word				|
                 | cmd_prefix						|
                 | cmd_name cmd_suffix				|
                 | cmd_name							|
                 ;

=> no direct left recursion, leave intact
cmd_name         : WORD                   /* Apply rule 7a (see Shell-functioning.md): */
                 ;

=> no direct left recursion, leave intact
cmd_word         : WORD                   `=` : Apply rule 7b (see Shell-functioning.md): 
				 ;							": if the token contains an unquoted `=` that is not part of 
											an embedded parameter expansion construct, then ..."

// direct left recursion, adapt
cmd_prefix       :            io_redirect			|	Beta_1
                 | cmd_prefix io_redirect			|	A alpha_1 
                 |            ASSIGNMENT_WORD		|	Beta_2
                 | cmd_prefix ASSIGNMENT_WORD		|	A alpha_2
                 ;

// direct left recursion, adapt
cmd_suffix       :            io_redirect			|	Beta_1
                 | cmd_suffix io_redirect			|	A alpha_1
                 |            WORD					|	Beta_2
                 | cmd_suffix WORD					|	A alpha_2
                 ;

=> no direct left recursion, leave intact
io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           here_doc
                 | IO_NUMBER here_doc
                 ;

=> no direct left recursion, leave intact
/* io_file – Apply rule 2: redirection to or from filename (see Shell-functioning.md)*/
io_file          : '<'			filename(->WORD)
                 | '>'			filename(->WORD)
                 | REDIR_APPEND	filename(->WORD)
                 ;

=> no direct left recursion, leave intact
/* Apply rule 3: redirection from here-document (see Shell-functioning.md)*/
here_doc          : REDIR_HEREDOC     here_end(->WORD)
                 ;


MINISHELL GRAMMAR WITHOUT DIRECT LEFT-RECURSION<br>
(AFTER preprocessing)
---------------------------------------------------------------------
rule			 : (...)							| 	Form:
---------------------------------------------------------------------
// adapted
program			 : command program_prime			|	Beta_1 A'

program_prime	 : '|' command program_prime		|	alpha_1 A'
				 | (empty)							|	epsilon (empty)
				 ;

command   		 : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD                   /* rule 7a (see Shell-functioning.md): 
												if no `=`, then WORD */
                 ;

cmd_word         : WORD                   `=` /* rule 7b (see Shell-functioning.md): 
				 ;							if unquoted "=", then either ASSIGNMENT_WORD or WORD ..."

// adapted
cmd_prefix		 : io_redirect		cmd_prefix_prime		|	Beta_1 A_prime
				 | ASSIGNMENT_WORD	cmd_prefix_prime		|	Beta_2 A_prime

// adapted
cmd_prefix_prime : io_redirect		cmd_prefix_prime		|	alpha_1 A_prime
				 | ASSIGNMENT_WORD	cmd_prefix_prime		|	alpha_2 A_prime
				 | (empty)									|	epsilon (empty)

// adapted
cmd_suffix		 : io_redirect	cmd_suffix_prime			|	Beta_1 A_prime
				 : WORD			cmd_suffix_prime			|	Beta_2 A_prime
				 ;

// adapted
cmd_suffix_prime : io_redirect	cmd_suffix_prime			|	alpha_1 A_prime
				 | WORD			cmd_suffix_prime			|	alpha_2 A_prime
				 | (empty)									|	epsilon (empty)	 
				 ;

io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here_doc
                 | IO_NUMBER io_here_doc
                 ;

/* io_file – Apply rule 2: redirection to or from filename (see Shell-functioning.md) */
io_file          : REDIR_INPUT  ('<')	filename(->WORD)
                 | REDIR_OUTPUT ('>')	filename(->WORD)
                 | REDIR_APPEND ('>>')  filename(->WORD)
                 ;

/* Apply rule 3: redirection from here-document (see Shell-functioning.md) */
io_here_doc      : REDIR_HEREDOC ('<<') here_end(->WORD)
                 ;


MINISHELL GRAMMAR WITHOUT DIRECT LEFT-RECURSION<br>
(without notes)
---------------------------------------------------------------------
program			 : command program_prime

program_prime	 : '|' command program_prime		
				 | (empty)							
				 ;

command   		 : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;

/* rule 7a (see Shell-functioning.md): if no `=`, then WORD */
cmd_name         : WORD                   
                 ;

`=` /* rule 7b (see Shell-functioning.md): if unquoted "=",
then either ASSIGNMENT_WORD or WORD ..." */
cmd_word         : WORD

cmd_prefix		 : io_redirect		cmd_prefix_prime		
				 | ASSIGNMENT_WORD	cmd_prefix_prime		

cmd_prefix_prime : io_redirect		cmd_prefix_prime
				 | ASSIGNMENT_WORD	cmd_prefix_prime
				 | (empty)									


cmd_suffix		 : io_redirect	cmd_suffix_prime			
				 : WORD			cmd_suffix_prime			
				 ;

cmd_suffix_prime : io_redirect	cmd_suffix_prime			
				 | WORD			cmd_suffix_prime			
				 | (empty)									
				 ;

io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here_doc
                 | IO_NUMBER io_here_doc
                 ;

/* io_file – Apply rule 2: redirection to or from filename (see Shell-functioning.md) */
io_file          : REDIR_INPUT  ('<')	filename(->WORD)
                 | REDIR_OUTPUT ('>')	filename(->WORD)
                 | REDIR_APPEND ('>>')  filename(->WORD)
                 ;

/* Apply rule 3: redirection from here-document (see Shell-functioning.md) */
io_here_doc      : REDIR_HEREDOC ('<<') here_end(->WORD)
                 ;