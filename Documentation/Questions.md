# Questions on Minishell
All questions we need answers to

## Input and parsing
- Here-docs: can be implemented after regular parsing ?
- Readline/history: should we implement indexing of history to navigate history with up/down arrows, or is it implemented by one of the authorized functions ?
- Readline commands/signals: ctrl + k, ctrl + a
	- clear history: rl_clear_history => not found on OS X/Macbook M1 => clang recommends clear_history from readline.h => which one to use ?

- Restrictions on file names (asked Copilot already)

- Variable management:
	- variable creation ? `VAR=blabla` => no (Thenguye)
	- env variable creation => yes, with export

- How to treat unclosed quotes ?

- multi-character operator tokens: what to do with e.g. `>|` tokenize `>` separately from `|` and then try to execute it, or parse them together like bash and then return an error message ?

- unexpected characters like `$$` => what to do ?

## Redirections
- implement `>|` ?

## Execution:
- how to call echo with -n ? Something special to do ?