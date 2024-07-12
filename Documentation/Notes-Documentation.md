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
- [Process image](https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_process_image.htm)
- Job control ?

### Quoting
- Unclosed quotes: don't manage with a `>` prompt, just return an error message ("\double/single quote not closed")
- @tfrily: start a counter when a quote is opened
- External quotes are determining, e.g. for expansion "'$USER'"

### Heredocuments
- expansion is different (cf. @tfrily): 
```bash
<< 'EOF' cat
<< 'EOF' cat
<< "'EOF'" cat
```
etc.

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

### Environmental variables
#### [Open group specification - 8. Environment Variables](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html)
> See the ENVIRONMENT VARIABLES section of the utility descriptions in the Shell and Utilities volume of POSIX.1-2017 for information on environment variable usage.

>The value of an environment variable is a string of characters. For a C-language program, an array of strings called the environment shall be made available when a process begins. The array is pointed to by the external variable environ, which is defined as:

`extern char **environ;`

>These strings have the form name=value; names shall not contain the character '='. For values to be portable across systems conforming to POSIX.1-2017, the value shall be composed of characters from the portable character set (except NUL and as indicated below). There is no meaning associated with the order of strings in the environment. If more than one string in an environment of a process has the same name, the consequences are undefined.

>Environment variable names used by the utilities in the Shell and Utilities volume of POSIX.1-2017 consist solely of uppercase letters, digits, and the <underscore> ( '_' ) from the characters defined in Portable Character Set and do not begin with a digit. Other characters may be permitted by an implementation; applications shall tolerate the presence of such names. Uppercase and lowercase letters shall retain their unique identities and shall not be folded together. The name space of environment variable names containing lowercase letters is reserved for applications. Applications can define any environment variables with names from this name space without modifying the behavior of the standard utilities.

>Note:
>    Other applications may have difficulty dealing with environment variable names that start with a digit. For this reason, use of such names is not recommended anywhere.

>The values that the environment variables may be assigned are not restricted except that they are considered to end with a null byte and the total space used to store the environment and the arguments to the process is limited to {ARG_MAX} bytes.
=> to get ARG_MAX: `echo $(getconf ARG_MAX)` => 1048576 on Macbook M1

>Other name= value pairs may be placed in the environment by, for example, calling any of the setenv(), unsetenv(), [XSI] [Option Start]  or putenv() [Option End] functions, assigning a new value to the environ variable, or by using envp arguments when creating a process; see exec in the System Interfaces volume of POSIX.1-2017.

>If the application modifies the pointers to which environ points, the behavior of all interfaces described in the System Interfaces volume of POSIX.1-2017 is undefined.

#### Conseils @tfrily
=> get environmental variables from `char **envp` (in main), then store them, in linked list (easier to modify) or array of strings. `Execve()` takes an array of strings for env parameters.

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

#### Unset
From [Shell Command Language manual - Parameter expansion]( https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02)
> ${parameter-word}
>    This example demonstrates the difference between unset and set to the empty string, as well as the rules for finding the delimiting close brace.
```bash
        foo=asdf
        echo ${foo-bar}xyz}
        asdfxyz}foo=
        echo ${foo-bar}xyz}
        xyz}unset foo
        echo ${foo-bar}xyz}
        barxyz}
```

### Signals
- Doable in the beginning
- [Bash manual](https://www.gnu.org/software/bash/manual/html_node/Signals.html):
> When job control is not enabled, and Bash is waiting for a foreground command to complete, the shell receives keyboard-generated signals such as SIGINT (usually generated by ‘^C’) that users commonly intend to send to that command. This happens because the shell and the command are in the same process group as the terminal, and ‘^C’ sends SIGINT to all processes in that process group. See Job Control, for a more in-depth discussion of process groups.

#### Ctrl + D
`C-D` in [Bash manual](https://www.gnu.org/software/bash/manual/html_node/Signals.html)

8.2.1 Readline Bare Essentials
C-d

    Delete the character underneath the cursor. 

Arguments ?
>8.2.4 Readline Arguments

>You can pass numeric arguments to Readline commands. Sometimes the argument acts as a repeat count, other times it is the sign of the argument that is significant. If you pass a negative argument to a command which normally acts in a forward direction, that command will act in a backward direction. For example, to kill text back to the start of the line, you might type ‘M-- C-k’.

>The general way to pass numeric arguments to a command is to type meta digits before the command. If the first ‘digit’ typed is a minus sign (‘-’), then the sign of the argument will be negative. Once you have typed one meta digit to get the argument started, you can type the remainder of the digits, and then the command. **For example, to give the C-d command an argument of 10, you could type ‘M-1 0 C-d’, which will delete the next ten characters on the input line**.

>8.4.3 Commands For Changing Text

end-of-file (usually C-d)

    The character indicating end-of-file as set, for example, by stty. If this character is read when there are no characters on the line, and point is at the beginning of the line, Readline interprets it as the end of input and returns EOF.
delete-char (C-d)

    Delete the character at point. If this function is bound to the same character as the tty EOF character, as C-d commonly is, see above for the effects.


#### Ctrl + \
Probably SIGQUIT



## Useful commands
- Show current shell in use: `ps -p $$`
- View Git commands executed by VSCode: View > Output, select Log (Git)
