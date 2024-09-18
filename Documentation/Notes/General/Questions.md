# Questions on Minishell
All questions we need answers to

## Authorized functions
- `rl_clear_history`: function not found, gcc on Mac ARM suggests `clear_history()` instead

## Input and parsing
- Newline tokens: don't implement right ?
- Here-docs: can be implemented after regular parsing ?
- Readline/history: should we implement indexing of history to navigate history with up/down arrows, or is it implemented by one of the authorized functions ?
- Readline commands/signals: ctrl + k, ctrl + a
	- clear history: rl_clear_history => not found on OS X/Macbook M1 => clang recommends clear_history from readline.h => which one to use ?

- Restrictions on file names (asked Copilot already)

- Variable management:
	- variable creation ? `VAR=blabla` => no (@Thenguye)
	- env variable creation => yes, with export

- How to treat unclosed quotes ?

- multi-character operator tokens: what to do with e.g. `>|` tokenize `>` separately from `|` and then try to execute it, or parse them together like bash and then return an error message ?

- unexpected characters like `$$` => what to do ?

- "the end-of-input indicator used internally by the shell is also considered a control operator." (see [control operator](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_113))
=> what is the end-of-input indicator used internally ?

## Redirections
- implement `>|` ?

## Quoting
- What to do with unclosed quotes : Error or `>` ?

## Execution:
- how to call echo with -n ? Something special to do ?
