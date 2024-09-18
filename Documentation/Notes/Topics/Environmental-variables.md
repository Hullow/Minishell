# Environmental variables
## [Open group specification - 8. Environment Variables](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html)
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

> [Shell Command Language - Shell Variables](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_05_03)

> Variables shall be initialized from the environment (as defined by XBD Environment Variables and the exec function in the System Interfaces volume of POSIX.1-2017) and can be given new values with variable assignment commands. If a variable is initialized from the environment, it shall be marked for export immediately; see the export special built-in. New variables can be defined and initialized with variable assignments, with the read or getopts utilities, with the name parameter in a for loop, with the ${ name= word} expansion, or with other mechanisms provided as implementation extensions.

The following variables shall affect the execution of the shell:

## `ENV`
- [Shell Command Language - Shell Variables](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_05_03):
>The processing of the ENV shell variable shall be supported if the system supports the User Portability Utilities option.<br><br>
>This variable, when and only when an interactive shell is invoked, shall be subjected to parameter expansion (see Parameter Expansion) by the shell and the resulting value shall be used as a pathname of a file containing shell commands to execute in the current environment. The file need not be executable. If the expanded value of ENV is not an absolute pathname, the results are unspecified. ENV shall be ignored if the user's real and effective user IDs or real and effective group IDs are different.

## `PATH`
- [Shell Command Language - Shell Variables](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_05_03):
> A string formatted as described in XBD Environment Variables, used to effect command interpretation; see [Command Search and Execution](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_09_01_01).

## `PWD`
- [Summary](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html):
> This variable shall represent an absolute pathname of the current working directory. It shall not contain any components that are dot or dot-dot. The value is set by the cd utility, and by the sh utility during initialization.
- [Shell Command Language - Shell Variables](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_05_03):
> Set by the shell and by the cd utility. In the shell the value shall be initialized from the environment as follows. If a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory that is no longer than {PATH_MAX} bytes including the terminating null byte, and the value does not contain any components that are dot or dot-dot, then the shell shall set PWD to the value from the environment. Otherwise, if a value for PWD is passed to the shell in the environment when it is executed, the value is an absolute pathname of the current working directory, and the value does not contain any components that are dot or dot-dot, then it is unspecified whether the shell sets PWD to the value from the environment or sets PWD to the pathname that would be output by pwd -P. Otherwise, the sh utility sets PWD to the pathname that would be output by pwd -P. In cases where PWD is set to the value from the environment, the value can contain components that refer to files of type symbolic link. In cases where PWD is set to the pathname that would be output by pwd -P, if there is insufficient permission on the current working directory, or on any parent of that directory, to determine what that pathname would be, the value of PWD is unspecified. Assignments to this variable may be ignored. If an application sets or unsets the value of PWD, the behaviors of the cd and pwd utilities are unspecified.

## Conseils @tfrily
=> get environmental variables from `char **envp` (in main), then store them, in linked list (easier to modify) or array of strings. `Execve()` takes an array of strings for env parameters.
