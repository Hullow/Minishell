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

=> predecessor of the first filename in the pathname is the root directory of the process

### Relative pathnames
#### Slashes (`/`)
IF<br>
- the pathname does not begin with a `/`

=> the predecessor of the first filename in the pathname shall be taken to be either:
- the current working directory of the process
or
- for certain interfaces, the directory identified by a file descriptor passed to the interface

IF<br>
- The pathname consisting of a single <slash>

=> the pathname shall resolve to the root directory of the process. 

IF<br>
- A pathname is null

=> it shall not be successfully resolved

#### Dots (`.`, `..`)
- The special filename dot `.` refers to the directory specified by its predecessor.
- The special filename dot-dot `..` refers to the parent directory of its predecessor directory. 
- In the root directory, dot-dot `..` may refer to the root directory itself.

## File name restrictions
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

## Functions for filename/pathname handling
### GETCWD function ([POSIX definition](https://pubs.opengroup.org/onlinepubs/009695299/functions/getcwd.html))
NAME

    getcwd - get the pathname of the current working directory

SYNOPSIS

    #include <unistd.h>

    char *getcwd(char *buf, size_t size);

DESCRIPTION

    The getcwd() function shall place an absolute pathname of the current working directory in the array pointed to by buf, and return buf. The pathname copied to the array shall contain no components that are symbolic links. The size argument is the size in bytes of the character array pointed to by the buf argument. If buf is a null pointer, the behavior of getcwd() is unspecified.

RETURN VALUE

    Upon successful completion, getcwd() shall return the buf argument. Otherwise, getcwd() shall return a null pointer and set errno to indicate the error. The contents of the array pointed to by buf are then undefined.

ERRORS

    The getcwd() function shall fail if:

    [EINVAL]
        The size argument is 0.
    [ERANGE]
        The size argument is greater than 0, but is smaller than the length of the pathname +1.

    The getcwd() function may fail if:

    [EACCES]
        Read or search permission was denied for a component of the pathname.
    [ENOMEM]
        Insufficient storage space is available.

The following sections are informative.
EXAMPLES

    Determining the Absolute Pathname of the Current Working Directory

    The following example returns a pointer to an array that holds the absolute pathname of the current working directory. The pointer is returned in the ptr variable, which points to the buf array where the pathname is stored.

    #include <stdlib.h>
    #include <unistd.h>
    ...
    long size;
    char *buf;
    char *ptr;


    size = pathconf(".", _PC_PATH_MAX);


    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);
    ...

APPLICATION USAGE

    None.

RATIONALE

    Since the maximum pathname length is arbitrary unless {PATH_MAX} is defined, an application generally cannot supply a buf with size {{PATH_MAX}+1}.

    Having getcwd() take no arguments and instead use the malloc() function to produce space for the returned argument was considered. The advantage is that getcwd() knows how big the working directory pathname is and can allocate an appropriate amount of space. But the programmer would have to use the free() function to free the resulting object, or each use of getcwd() would further reduce the available memory. Also, malloc() and free() are used nowhere else in this volume of IEEE Std 1003.1-2001. Finally, getcwd() is taken from the SVID where it has the two arguments used in this volume of IEEE Std 1003.1-2001.

    The older function getwd() was rejected for use in this context because it had only a buffer argument and no size argument, and thus had no way to prevent overwriting the buffer, except to depend on the programmer to provide a large enough buffer.

    On some implementations, if buf is a null pointer, getcwd() may obtain size bytes of memory using malloc(). In this case, the pointer returned by getcwd() may be used as the argument in a subsequent call to free(). Invoking getcwd() with buf as a null pointer is not recommended in conforming applications.

    If a program is operating in a directory where some (grand)parent directory does not permit reading, getcwd() may fail, as in most implementations it must read the directory to determine the name of the file. This can occur if search, but not read, permission is granted in an intermediate directory, or if the program is placed in that directory by some more privileged process (for example, login). Including the [EACCES] error condition makes the reporting of the error consistent and warns the application writer that getcwd() can fail for reasons beyond the control of the application writer or user. Some implementations can avoid this occurrence (for example, by implementing getcwd() using pwd, where pwd is a set-user-root process), thus the error was made optional. Since this volume of IEEE Std 1003.1-2001 permits the addition of other errors, this would be a common addition and yet one that applications could not be expected to deal with without this addition.

FUTURE DIRECTIONS

    None.

SEE ALSO

    malloc(), the Base Definitions volume of IEEE Std 1003.1-2001, <unistd.h>

CHANGE HISTORY

    First released in Issue 1. Derived from Issue 1 of the SVID.

Issue 6

    The following new requirements on POSIX implementations derive from alignment with the Single UNIX Specification:

        The [ENOMEM] optional error condition is added.

End of informative text.



### CHDIR function ([POSIX definition](https://pubs.opengroup.org/onlinepubs/009695299/functions/chdir.html))
NAME

    chdir - change working directory

SYNOPSIS

    #include <unistd.h>

    int chdir(const char *path);

DESCRIPTION

    The chdir() function shall cause the directory named by the pathname pointed to by the path argument to become the current working directory; that is, the starting point for path searches for pathnames not beginning with '/'.

RETURN VALUE

    Upon successful completion, 0 shall be returned. Otherwise, -1 shall be returned, the current working directory shall remain unchanged, and errno shall be set to indicate the error.

ERRORS

    The chdir() function shall fail if:

    [EACCES]
        Search permission is denied for any component of the pathname.
    [ELOOP]
        A loop exists in symbolic links encountered during resolution of the path argument.
    [ENAMETOOLONG]
        The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}.
    [ENOENT]
        A component of path does not name an existing directory or path is an empty string.
    [ENOTDIR]
        A component of the pathname is not a directory.

    The chdir() function may fail if:

    [ELOOP]
        More than {SYMLOOP_MAX} symbolic links were encountered during resolution of the path argument.
    [ENAMETOOLONG]
        As a result of encountering a symbolic link in resolution of the path argument, the length of the substituted pathname string exceeded {PATH_MAX}.

The following sections are informative.
EXAMPLES

    Changing the Current Working Directory

    The following example makes the value pointed to by directory, /tmp, the current working directory.

    #include <unistd.h>
    ...
    char *directory = "/tmp";
    int ret;


    ret = chdir (directory);

APPLICATION USAGE

    None.

RATIONALE

    The chdir() function only affects the working directory of the current process.

FUTURE DIRECTIONS

    None.

SEE ALSO

    getcwd(), the Base Definitions volume of IEEE Std 1003.1-2001, <unistd.h>

CHANGE HISTORY

    First released in Issue 1. Derived from Issue 1 of the SVID.

Issue 6

    The APPLICATION USAGE section is added.

    The following new requirements on POSIX implementations derive from alignment with the Single UNIX Specification:

        The [ELOOP] mandatory error condition is added.

        A second [ENAMETOOLONG] is added as an optional error condition.

    The following changes were made to align with the IEEE P1003.1a draft standard:

        The [ELOOP] optional error condition is added.

End of informative text.