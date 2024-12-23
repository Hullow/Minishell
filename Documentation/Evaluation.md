# Minishell Evaluation - preparation

## TO DO
- Errors: Write to stderr (2)

## Bugs dans notre shell:
## Other bugs to check (ahanzi)
espace expansion code erreur				?
warning msg on ctrlD						?
ctrl\ print quit							?
ft_strcmp - Len								?

## Exit
n.b.: `exit text` 2 sur Linux, 255 OS X

exit -12345678945134678945615				✅
exit 256									✅
echo $?+$?									✅

exit ""										❌
- Bash: exit: : numeric argument required, exit code 255
- Minishell: nothing, exit code 0

exit -0										❌
- bash: (nothing), exit status 0
- Minishell: exit: -0: numeric argument required, exit status 255

exit -1										❌
- bash: (nothing), exit status 255
- Minishell: exit: -1: numeric argument required, exit status 255

exit 777777777777777777777777				❌
- bash: exit: 777777777777777777777777: numeric argument required, exit code 255
- Minishell: nothing, exit code 113
exit: 78948561245367867897922				❌

- bash: exit: 78948561245367867897922: numeric argument required, exit code 255
- Minishell: nothing, exit code 188

code exit ctrl-d 							❌
=> prompt> nonexistentcommand
=> ctrl+D
- bash: exit status 127
- Minishell: exit status 0

### Signals
ctrlD heredoc								✅

### Syntax
ls "" commande vide							✅
echo "" -n 									✅
"" >out | <out cat -e 						✅

minishell > ""								~(not OK)
- bash: : No such file or directory
- minishell: syntax error near unexpected token `newline'

cmd | | cmd 								~(not OK)
- bash: syntax error near unexpected token `|'
- Minishell: "" (newline)

### Redirections
- echo > $VAR 								❌
=> minishell: syntax error near unexpected token `newline'
=> bash: $VAR: ambiguous redirect

### Expansions
$ "vide":
- `echo $"USER"`
- `echo $"$USER"`
- `echo $'USER'`
- `echo echo "$USER"`
(autrement, `echo echo '$PATH'`, `"ls"` marchent)

### Export/env
- `export 6go=bl` 							✅
- `export koko` && `env | grep koko` 		✅
- export zw: ne fait rien 					✅
- export zw= : cree							✅
- export zw=abc: assigne					✅
- export zw: ne fait rien 					✅
- export zw= : vide 						✅
- export zw="" : vide 						✅
- export zww > doesnt update var			✅
- envv										✅


### Pipes
- cat -e | cat -e | cat -e 					✅

- `echo hello > test.txt`
+											✅
`< test.txt cat -e | cat -e` 				

- `ls | lsss`								✅
=> Segmentation fault: 11
=> fixed on its own

- ls | ls | lsss > ec 127					✅

- `lsss <in | caast | ls -la`				❌	
- `ls | caast | ls -la <in`					❌
=> manque "caast: command not found" dans les deux cas
=> manque aussi "**Minishell**: caast: commant not found"

- Gestion des pipes ouvertes:				❌
par ex. `cat |` puis \<enter\>
(autre exemple: `echo $ |`, suivi de `cat`)


### Heredocs
expansion on delimiter						✅


### Expansions
- `$a`										❌
-> Minishell: permission denied
-> bash: (nothing)

- `$'a'`									~OK
=> "$a: command not found"
=> "bash: a: command not found"

- `echo $`									✅
=> réglé (if `prompt[i + 1]`)
- `echo $o_`								✅
 segfault => réglé
 (ft_free_token_list fixed)
- `c$a`										✅
- `echo $_`									✅

### Free
```Bash 									✅
Minishell : lsls
lsls: command not found
Minishell : expr $? + $?
254
minishell(40802,0x1f610cc00) malloc: Double free of object 0x134605e90
minishell(40802,0x1f610cc00) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
```
=> fixed on its own

```bash										✅
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


## Notes d'eval - Eval de SBaumann et fsan-vic
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

## Mes remarques
- POSIX: version de bash
=> oui, mais techniquement c'est surtout un standard pour les Shell (sh, bash, ksh)
- git **/*.o

Questions:
- UNEXPECTED EOF define => ?
- nosleep.c : `int main(){ while(1){} }`
- qu'est-ce qui l'a fait crasher ? => pas de réponse


Savoir expliquer les signaux!			