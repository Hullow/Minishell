# Redirections
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

## Heredocuments
- expansion is different (cf. @tfrily): 
```bash
<< 'EOF' cat
<< 'EOF' cat
<< "'EOF'" cat
```
etc.
