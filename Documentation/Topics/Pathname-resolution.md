# Pathname resolution
Reference:
- [Open Group POSIX.1 - 2017 specification](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap04.html#tag_04_13)

## [Filename expansion](https://www.gnu.org/software/bash/manual/bash.html#Filename-Expansion)
> When a pattern is used for filename expansion, the character ‘.’ at the start of a filename or immediately following a slash must be matched explicitly.
> When not matching filenames, the ‘.’ character is not treated specially.

## Pathname rules
### Absolute pathnames
IF<br>
- the pathname begins with a `/`

=> the predecessor of the first filename in the pathname shall be taken to be the root directory of the process

### Relative pathnames
IF<br>
- the pathname begins with a `/`

=> the predecessor of the first filename in the pathname shall be taken to be:
- the current working directory of the process
- for certain interfaces, the directory identifed by a file descriptor passed to the interface `=> ?`

Limits:
> The interpretation of a pathname component is dependent on the value of {NAME_MAX} and _POSIX_NO_TRUNC associated with the path prefix of that component. If any pathname component is longer than {NAME_MAX}, the implementation shall consider this an error.

IF<br>
- A pathname contains:
	- at least one non- `/` character
	<br>&emsp;AND
	- ends with one or more trailing `/` characters

=> that pathname shall not be resolved successfully<br>
=> unless the last pathname component before the trailing `/` characters:
- names an existing directory
<br>&emsp;OR
- a directory entry that is to be created for a directory immediately after the pathname is resolved

`=> ?`