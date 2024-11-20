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

### Subshells
- Maybe check [POSIX.1-2017 - 11. General Terminal Interface](https://pubs.opengroup.org/onlinepubs/9699919799/)

## Useful commands
- Show current shell in use: `ps -p $$`
- View Git commands executed by VSCode: View > Output, select Log (Git)
- Clone the bash git repo : `git clone https://git.savannah.gnu.org/git/bash.git`