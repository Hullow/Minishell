# Notes from consulting the documentation
(see References.md for all references)
## 42sh - Architecture d'un shell (Epitech 2019) - [YouTube](https://www.youtube.com/watch?v=oIFRiwFRSRY&t=745s)
- What matters is to be able to execute a command => if's, etc. come after
- Read [Shell Command Language manual](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
 	=> remark by Cmegret: we probably won't read too much in detail in the beginning
- Toujours avoir quelque chose de fonctionnel à montrer (vs "dans 2 semaines on aura qqch")
- Ne pas faire en bloc: parsing, ensuite expanding, ensuite execution; plutôt faire parsing basique de commandes, puis rajouter de la complexité. Par exemple, être capable de parser et exécuter une seule commande, puis rajouter des if, etc.
- Syntax abstraite vs concrète, arbre de parsing:
pas faire un arbre de parsing complet avant de coder => plutôt, partir du truc "inratable" => parser des commandes simples et faire `fork exec`
- Tester les choses séparément, au fur et à mesure
- Subshell: attention à l'historique
- Ce qui est compliqué c'est pas d'exécuter une commande, mais les variables et les substitutions
### Posix
(57:00): "un shell POSIX ça n'existe pas; ce qui existe c'est un script Shell qui se sert que du sous-ensemble Posix des features du shell". Il y a quelques comportements que Bash ne respecte pas concernant Posix, notamment ordre des pipes et valeurs retour en cas d'un fail. => quelle valeur retour quand j'ai plusieurs commandes dans mon pipe ? `bash --posix` change le comportement du pipe et tous les comportements qui changent par rapport à POSIX, mais ne désactive pas toutes les extensions du bash, e.g. `if [[ ]]`
- Cas d'erreur: le shell est un langage de m..... des comportements sont indéfinis ou mal définis dans la spec (SCL)
=> ne pas se casser la tête et suivre le comportement de Bash; le but est de faire un shell qui marche, pas suivre Bash dans les comportements les plus stupides
- Allez lire des bouts de shell, ça vaut le coup; pas Bash, plutôt des choses comme [ksh](https://github.com/openbsd/src/tree/master/bin/ksh) => "au fait, toi tu fais comment ?" e.g. quels sont les appels systèmes quand je fais tel ou tel truc (avec `strace`). Attention aussi aux optimisations qui sont faites pour éviter de fork trop de fois (il y a des commandes implémentées en builtin, etc.)
- **Faire des tests dès le début : créer des scripts shells, lancer avec un shell quelconque, vérifier si ça marche pareil
=> à chaque fois, quand on rajoute une feature, faire un test qui va avec; ça doit devenir un réflexe: "je veux que tel script marche, j'écris mon script, j'écris le shell" Permet de voir en continu si on a cassé quelque chose. Si on a le moindre bug, mettre le script dans les tests avant de faire quoi que ce soit**
=> faire du [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development) => tests écrits avant le code, code écrit pour satisfaire les tests

## EnthusiastiCon - Stefanie Schirmer “OMG building a shell in 10 minutes” [YouTube](https://www.youtube.com/watch?v=k6TTj4C0LF0)
- Privileged space to interact with the kernel
- Very simplified shell:
	- Prompt to input things
	- Parse user input
	- Run builtin commands for job control
	- Run other system commands and show their output
- Execvp replaces the current process with a new process image

## Environment
### POSIX
see above: [42sh - architecture d'un shell#POSIX](#posix)

### Linux
#### Compiling
- flag: `gcc history.c -lreadline` to compile (OS X/clang: `gcc -lreadline history.c`)

## Concepts
### Notions to explore
From [42sh - architecture d'un shell](#42sh---architecture-dun-shell-epitech-2019---youtube)
- Abstract Syntax tree
- Here-docs
- [Process image](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_process_image.htm)
- Job control ?

### Redirections
#### File name restrictions
(Copilot)
> Yes, in Unix and Unix-like systems, there are characters that are not supported or are problematic when used in file names:
- Slash (/): Used as the directory separator and cannot be used in file names.
- Null character (\0): Indicates the end of a string in C and many other programming languages, so it cannot be part of a file name.
>Additionally, while not strictly unsupported, the following should be used with caution as they can be problematic:
- Dot (.) at the start of a file name: Files beginning with a dot are hidden by default in Unix-like systems.
- Spaces ( ): Can be used but often need to be escaped or quoted, which can complicate command line operations.
- Special characters such as *, ?, ", ', :, |, &, <, >, (, ), ;, !, ^, {, }, [, ], $, #, ~, and backtick (`): These have special meanings in the shell and may require escaping or quoting.
- Control characters (ASCII 0-31 and 127): Can be problematic in shell and other utilities.
>It's generally recommended to stick to alphanumeric characters, dashes (-), and underscores (_) for maximum compatibility and ease of use in file names on Unix systems.

### Shell builtins
- pberset: to code builtins, use functions tsetaddr, etc.

`man builtin`:
> Shell builtin commands are commands that can be executed within the running shell's process.
> If a command specified to the shell contains a slash ‘/’, the shell will not execute a builtin command, even if the last component of the specified command matches the name of a builtin command.  Thus, while specifying “echo” causes a builtin command to be executed under shells that support the echo builtin command, specifying “/bin/echo” or “./echo” does not.
> Consult a shell's manual page for details on the operation of its builtin commands.

=> `man bash` > search "SHELL BUILTIN COMMANDS"
<br>=> Note: not clear what to do with builtins; copy the code from bash ? or re-code them ourselves ?


#### Export
[Export - Bash Reference Manual (v5.2)](https://www.gnu.org/software/bash/manual/bash.html#index-export)
`export [-fn] [-p] [name[=value]]`

> Mark each name to be passed to child processes in the environment. If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. The -n option means to no longer mark each name for export. If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed. The -p option displays output in a form that may be reused as input. If a variable name is followed by =value, the value of the variable is set to value.

> The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.

- [ksh code (var.c)](https://github.com/openbsd/src/blob/7520e8fab0993b4a897a2774a7038459b8b069e4/bin/ksh/var.c#L576) :

```c
/*
 * make vp->val.s be "name=value" for quick exporting.
 */
static void
export(struct tbl *vp, const char *val)
{
	char *xp;
	char *op = (vp->flag&ALLOC) ? vp->val.s : NULL;
	int namelen = strlen(vp->name);
	int vallen = strlen(val) + 1;

	vp->flag |= ALLOC;
	xp = alloc(namelen + 1 + vallen, vp->areap);
	memcpy(vp->val.s = xp, vp->name, namelen);
	xp += namelen;
	*xp++ = '=';
	vp->type = xp - vp->val.s; /* offset to value */
	memcpy(xp, val, vallen);
	afree(op, vp->areap);
}
```

### Signals
- Doable in the beginning
- [Bash manual](https://www.gnu.org/software/bash/manual/html_node/Signals.html):
> When job control is not enabled, and Bash is waiting for a foreground command to complete, the shell receives keyboard-generated signals such as SIGINT (usually generated by ‘^C’) that users commonly intend to send to that command. This happens because the shell and the command are in the same process group as the terminal, and ‘^C’ sends SIGINT to all processes in that process group. See Job Control, for a more in-depth discussion of process groups.

## Useful commands
- Show current shell in use: `ps -p $$`
- View Git commands executed by VSCode: View > Output, select Log (Git)
