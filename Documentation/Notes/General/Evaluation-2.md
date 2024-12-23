# Minishell Eval
Eval de SBaumann et fsan-vic: 

## TO DO
- Preparing expansions in heredocs
- Errors: Write to stderr (2)
- Makefile: objects folder
- Rl_clear_history: au bon endroit ?
- Python tester (+ Valgrind ?)

## Bugs dans notre shell:
### Bugs restants
- expansions: redirections strings (more cmegret): export VAR=2800 puis echo > $VAR

### Heredocs
```bash
sh << out
> ls
(ctrl+c/SIGINT)
```
=> this executes ls; it should not!

### Bugs réglés en principe
### Exit
exit 777777777777777777777777			OK
exit -12345678945134678945615			OK
exit: 78948561245367867897922			OK
exit -0									OK
exit -1									OK
exit 256								OK
=> modulo 255 if scope LONG_INT_MIN/MAX

exit text: 2 sur Linux, 255 OS X

### Expansions
$ "vide":
- `echo $"USER"`
- `echo $"$USER"`
- `echo $'USER'`
- `echo echo "$USER"`
(autrement, `echo echo '$PATH'`, `"ls"` marchent)

#### Export/env
- `export 6go=bl` ✅
- `export koko` && `env | grep koko` ✅

- export zz: cree
- export zz=abc: assigne
- export zz: rien
- export zz= : vide
- export zz="" : vide


- export zzz > doesnt update var			OK

### Pipes
- Gestion des pipes ouvertes différente de bash, par `cat |` puis \<enter\> (autre exemple: `echo $ |`, suivi de `cat`)
- 
 lsss <in | caast | ls -la
 ls | caast | ls -la <in
=> manque "caast: command not found" dans les deux cas

## Autres bugs
- `$a` => permission denied (nothing in bash)
- `$'a'` => $a: command not found (bash: a: command not found)

## Bugs réglés
### Pipes
- `ls | lsss` => Segmentation fault: 11 => fixed on its own

### Expansions
- `echo $` => réglé (if `prompt[i + 1]`)
- `echo $o_` : segfault => réglé (ft_free_token_list fixed)
- `c$a`
- `echo $_`

### Free
```bash
Minishell : lsls
lsls: command not found
Minishell : expr $? + $?
254
minishell(40802,0x1f610cc00) malloc: Double free of object 0x134605e90
minishell(40802,0x1f610cc00) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
```
=> fixed on its own

```bash
Minishell : ./minishell
Minishell : slsls
slsls: command not found
Minishell : echo $?
127
Minishell : exit
exit
Minishell : echo $?
0
minishell(12605,0x1f610cc00) malloc: Double free of object 0x136607c90
minishell(12605,0x1f610cc00) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
```
=> fixed on its own


## Notes d'eval
- SBaumann: "Faire l'eval sur Mac plutôt que Linux parce que ... (signaux ?)"
- Dans la fiche d'eval il est dit: "Verifiez la variable globale: ne peut contenir aucune information autre que la valeur du signal reçu"
- Object files: les mettre dans un dossier objet pour rendre ça plus lisible (Sforster)
- Si expansion de variables marche bien, ça rajoute un point de bonus (?!)
- Ont mis prompt en vert pour aide visuelle
- Ont mis des define pour les messages d'erreur, genre 
`# define WRITE_ERR write("write failed\n")`
- SBaumann: "leaks ont été galère", prêt à donner un coup de main
- Tests divers à faire :
	- `gcc nosleep.c` puis `./a.out | cat test.txt` et aussi `./a.out | cat test.txt | echo hey`
	- `echo cat lol.c | cat > lol.c`

## Mes remarques sur l'eval
- POSIX: version de bash
=> oui, mais techniquement c'est surtout un standard pour les Shell (sh, bash, ksh)
- git **/*.o

Questions:
- UNEXPECTED EOF define => ?
- nosleep.c : `int main(){ while(1){} }`
- qu'est-ce qui l'a fait crasher ? => pas de réponse



## Other errors to check (ahanzi)
# Minishell
A 42 project about creating a simple shell.  
[Subject requirements](https://github.com/angelahanzi/minishell/blob/main/en.subject.pdf) 

First evaluation bugs:
mettre bash par défaut

Empty command:
minishell > ""							OK
echo "" -n 								OK

< test.txt cat -e | cat -e 				OK

exit 777777777777777777777777			OK
exit -12345678945134678945615			OK
exit: 78948561245367867897922			OK
exit -0									OK
exit -1									OK
exit 256								OK

echo $?+$?								OK
espace expansion code erreur

cat -e | cat -e | cat -e 				OK
\n en trop apres signal

code exit ctrl-d 						OK

ls "" commande vide						OK

ctrlD heredoc							OK
warning msg on ctrlD					OK
expansion on delimiter					OK

ctrl\ print quit						OK

ft_strcmp - Len							OK
envv									OK

"" >out | <out cat -e 					OK
exit ""									OK
export zzz > doesnt update var			OK
cmd | | cmd 							OK

Outputs order (error msg and cmd)		OK
>> errors on STDERR when encountered
+ stdout and stderr are different streams

ls | ls | lsss > ec 141 (sigpipe)		

Savoir expliquer les signaux!			

### Remarques sur notre shell



#### Bash exit status "bug"
`/bin/ls/filethatdoesntexist` ; `echo $?`
/bin/ls/filethatdoesntexist ; echo $?
=> bash, sh: 126
=> zsh, our Minishell: 127

POSIX:
- 126 is for command found but not executable
- 127 for command not found

=> Bash is wrong !


### Fonctions utilisées
Readline functions

Variable: int rl_done
Setting this to a non-zero value causes Readline to return the current line immediately. Readline will set this variable when it has read a key sequence bound to accept-line and is about to return the line to the caller.

Function: void rl_redisplay (void)
Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

Variable: rl_hook_func_t * rl_event_hook
If non-zero, this is the address of a function to call periodically when Readline is waiting for terminal input. By default, this will be called at most ten times a second if there is no keyboard input.

Function: int rl_on_new_line (void)
Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

Function: void rl_replace_line (const char *text, int clear_undo)
Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.