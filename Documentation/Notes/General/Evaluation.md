# Minishell Eval
Eval de SBaumann et fsan-vic: 

## TO DO
- REMETTRE RL_CLEAR_HISTORY

## Bugs dans notre shell:
### Expansions
- `echo $"PATH"`
- `echo $'PATH'`
- `echo echo "$PATH"`
(autrement, `echo echo '$PATH'`, `"ls"` marchent)

### Export/env
- `export 6go=bl`
- `export koko` && `env | grep koko`

### Pipes
- Gestion des pipes ouvertes différente de bash, par `cat |` puis \<enter\>
- `ls | lsss` => Segmentation fault: 11

### Exit
```bash
Minishell : lsls
lsls: command not found
Minishell : expr $? + $?
254
minishell(40802,0x1f610cc00) malloc: Double free of object 0x134605e90
minishell(40802,0x1f610cc00) malloc: *** set a breakpoint in malloc_error_break to debug
Abort trap: 6
```

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

## Mes remarques
- POSIX: version de bash
=> oui, mais techniquement c'est surtout un standard pour les Shell (sh, bash, ksh)
- git **/*.o

Questions:
- UNEXPECTED EOF define => ?
- nosleep.c : `int main(){ while(1){} }`
- qu'est-ce qui l'a fait crasher ? => pas de réponse