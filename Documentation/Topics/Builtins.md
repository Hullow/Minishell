# Shell builtins
- pberset: to code builtins, use functions tsetaddr, etc.

`man builtin`:
> Shell builtin commands are commands that can be executed within the running shell's process.
> If a command specified to the shell contains a slash ‘/’, the shell will not execute a builtin command, even if the last component of the specified command matches the name of a builtin command.  Thus, while specifying “echo” causes a builtin command to be executed under shells that support the echo builtin command, specifying “/bin/echo” or “./echo” does not.
> Consult a shell's manual page for details on the operation of its builtin commands.

=> `man bash` > search "SHELL BUILTIN COMMANDS"



## Execution and environment
- @erabbath: builtins in pipe do not change global environment, but otherwise they do

## Description of builtins
## [Special builtins](https://www.gnu.org/software/bash/manual/bash.html#Special-Builtins)
> When Bash is not executing in POSIX mode, these builtins (including `exit`, `export`, `unset`) behave no differently than the rest of the Bash builtin commands.

### cd
See [Open Group Specification - POSIX.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html)

### Exit
`exit` - cause the shell to exit([Shell Command Language - Special builtins](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#exit)):<br>
>SYNOPSIS<br>
>`exit [n]`<br><br>
>DESCRIPTION<br>
>The exit utility shall cause the shell to exit from its current execution environment with the exit status specified by the unsigned decimal integer n. If the current execution environment is a subshell environment, the shell shall exit from the subshell environment with the specified exit status and continue in the environment from which that subshell environment was invoked; otherwise, the shell utility shall terminate with the specified exit status. If n is specified, but its value is not between 0 and 255 inclusively, the exit status is undefined.<br><br>
A trap on EXIT shall be executed before the shell terminates, except when the exit utility is invoked in that trap itself, in which case the shell shall exit immediately.<br><br>
>OPTIONS<br>
>None.<br><br>
>OPERANDS<br>
>See the DESCRIPTION.<br><br>
>STDIN<br>
>Not used.<br><br>
>INPUT FILES<br>
>None.<br><br>
>ENVIRONMENT VARIABLES<br>
>None.<br><br>
>ASYNCHRONOUS EVENTS<br>
>Default.<br><br>
>STDOUT<br>
>Not used.<br><br>
>STDERR<br>
>The standard error shall be used only for diagnostic messages.<br><br>
>OUTPUT FILES<br>
>None.<br><br>
>EXTENDED DESCRIPTION<br>
>None.<br><br>
>EXIT STATUS<br>
> The exit status shall be n, if specified, except that the behavior is unspecified if n is not an unsigned decimal integer or is greater than 255. Otherwise, the value shall be the exit value of the last command executed, or zero if no command was executed. When exit is executed in a trap action, the last command is considered to be the command that executed immediately preceding the trap action.<br><br>
>CONSEQUENCES OF ERRORS<br>
>Default.

### Export
[General note on variable assignment](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap04.html#tag_foot_1):
> When a variable assignment is done, the variable shall be created if it did not already exist. If value is not specified, the variable shall be given a null value.

Note on valid names [POSIX](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_235:~:text=unlocks%20the%20mutex.-,3.235,-Name):
> In the shell command language, a word consisting solely of underscores, digits, and alphabetics from the portable character set. The first character of a name is not a digit.
> Note: The Portable Character Set is defined in detail in Portable Character Set.

=> in bash, `export VAR-OH_VAR=22` => error: `bash: export: VAR-OH_VAR=22: not a valid identifier`
But `export VAR_OH_VAR=22` works

#### `man bash`
> `export` [`-fn`] [name[=word]] ...<br>
> `export -p` <br>
	The supplied names are marked for automatic export to the environment of subsequently exe-
	cuted commands. If the -f option is given, the names refer to functions. If no names are
	given, or if the -p option is supplied, a list of all names that are exported in this shell
	is printed. The -n option causes the export property to be removed from each name. If a
	variable name is followed by =word, the value of the variable is set to word. export
	returns an exit status of 0 unless an invalid option is encountered, one of the names is
	not a valid shell variable name, or -f is supplied with a name that is not a function.

#### [Export - Bash Reference Manual (v5.2)](https://www.gnu.org/software/bash/manual/bash.html#index-export)
`export [-fn] [-p] [name[=value]]`

> Mark each name to be passed to child processes in the environment. If the -f option is supplied, the names refer to shell functions; otherwise the names refer to shell variables. The -n option means to no longer mark each name for export. If no names are supplied, or if the -p option is given, a list of names of all exported variables is displayed. The -p option displays output in a form that may be reused as input. If a variable name is followed by =value, the value of the variable is set to value.

> The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a shell function.

`export` - set the export attribute for variables ([Shell Command Language - Special builtins](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#export)):<br>
>SYNOPSIS<br>
>`export name[=word]...`<br>
>`export -p`<br><br>
>DESCRIPTION<br>
>The shell shall give the export attribute to the variables corresponding to the specified names, which shall cause them to be in the environment of subsequently executed commands. If the name of a variable is followed by = word, then the value of that variable shall be set to word.<br><br>
>The export special built-in shall support XBD Utility Syntax Guidelines.<br><br>
>When -p is specified, export shall write to the standard output the names and values of all exported variables, in the following format:<br><br>
>"`export %s=%s\n`", <name>, <value><br>
>if name is set, and:<br>
>"`export %s\n`", <name><br>
>if name is unset.<br><br>
>The shell shall format the output, including the proper use of quoting, so that it is suitable for reinput to the shell as commands that achieve the same exporting results, except:<br><br>
>Read-only variables with values cannot be reset.<br><br>
>Variables that were unset at the time they were output need not be reset to the unset state if a value is assigned to the variable between the time the state was saved and the time at which the saved output is reinput to the shell.<br><br>
>When no arguments are given, the results are unspecified.<br><br>
>OPTIONS<br>
>See the DESCRIPTION.<br><br>
>OPERANDS<br>
>See the DESCRIPTION.<br><br>
>STDIN<br>
>Not used.<br><br>
>INPUT FILES<br>
>None.<br><br>
>ENVIRONMENT VARIABLES<br>
>None.<br><br>
>ASYNCHRONOUS EVENTS<br>
>Default.<br><br>
>STDOUT<br>
>See the DESCRIPTION.<br><br>
>STDERR<br>
>The standard error shall be used only for diagnostic messages.<br><br>
>OUTPUT FILES<br>
>None.<br><br>
>EXTENDED DESCRIPTION<br>
>None.<br><br>
>EXIT STATUS<br>
>0 All name operands were successfully exported.<br>
>\>0 At least one name could not be exported, or the -p option was specified and an error occurred.<br>
>CONSEQUENCES OF ERRORS<br>
>Default.

#### [ksh code (var.c)](https://github.com/openbsd/src/blob/7520e8fab0993b4a897a2774a7038459b8b069e4/bin/ksh/var.c#L576) :

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

### Unset
#### [Shell Command Language manual - Parameter expansion]( https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02)
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

`unset` - unset values and attributes of variables and functions ([Shell Command Language - Special builtins](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#unset)):<br>
>SYNOPSIS<br>
>`unset [-fv] name...`<br><br>
>DESCRIPTION<br>
>Each variable or function specified by name shall be unset.<br><br>
If -v is specified, name refers to a variable name and the shell shall unset it and remove it from the environment. Read-only variables cannot be unset.<br><br>
If -f is specified, name refers to a function and the shell shall unset the function definition.<br><br>
If neither -f nor -v is specified, name refers to a variable; if a variable by that name does not exist, it is unspecified whether a function by that name, if any, shall be unset.<br><br>
Unsetting a variable or function that was not previously set shall not be considered an error and does not cause the shell to abort.<br><br>
The unset special built-in shall support XBD [Utility Syntax Guidelines](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html#tag_12_02).<br><br>
Note that:<br>
`VARIABLE=`<br>
is not equivalent to an unset of VARIABLE; in the example, VARIABLE is set to "". Also, the variables that can be unset should not be misinterpreted to include the special parameters (see [Special Parameters](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_05_02)).<br><br>
>OPTIONS<br>
>See the DESCRIPTION.<br><br>
>OPERANDS<br>
>See the DESCRIPTION.<br><br>
>STDIN<br>
>Not used.<br><br>
>INPUT FILES<br>
>None.<br><br>
>ENVIRONMENT VARIABLES<br>
>None.<br><br>
>ASYNCHRONOUS EVENTS<br>
>Default.<br><br>
>STDOUT<br>
>Not used.<br><br>
>STDERR<br>
>The standard error shall be used only for diagnostic messages.<br><br>
>OUTPUT FILES<br>
>None.<br><br>
>EXTENDED DESCRIPTION<br>
>None.<br><br>
>EXIT STATUS<br>
> `0` : All name operands were successfully unset.<br>
> `>0` : At least one name could not be unset.<br><br>
>CONSEQUENCES OF ERRORS<br>
>Default.

### pwd
See [Open Group Specification - POSIX.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/)