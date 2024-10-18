# Parsing
## General approach
- Go through linked list, and follow rules:

### Redirections
- if we find redirection token, check next token, then put both in a struct
=> linked list of redirections ? => yes, because e.g. `echo hello >2 > 3 > 4` creates 2, 3 and 4 but only stores "hello" in 4

in struct s_command:
```c
	s_redir				*redirections; // linked list of all redirections
	int					input;
	int					output;
```

