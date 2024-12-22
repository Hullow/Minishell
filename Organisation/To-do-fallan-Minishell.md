# To do list - fallan
## Features
- expansions: $" (empty $)
- expansions: redirections strings (more cmegret)
- expansions preparations: in heredocs too
- Signals : sigint

## Bugs
- Signals: ctrl+c + exit bug

## Testing
- Find way to test pipes in Linux
- Make Python tester


## Mostly done (to check if time)
### Research
- Simple tokenizer:
	- Check if behavior is correct !!!
	- test it with various sequences, check if behavior is adequate
	- test for leaks
	- refactor for clarity of code (and to prevent issues)
		- Claude3.5 (in Double/VSCode):
		> Error Handling: The code could benefit from more robust error handling, especially for memory allocation failures.
		> Consider using more consistent naming conventions (some functions use snake_case, others use camelCase).
- Finish shell-functioning.md
- learn about abstract/concrete syntax trees and their implementation
- Go through token recognition process manually with a few examples
- Quick read of allowed functions to understand their purpose
- Readings:
	- man execve
	- man fork
- Re-read cmegret's pipex

### Other
- Environment set up: bash5.1.16 via macports/brew, UTM, ..

### Organisation
- Github: learngitbranching + Github projects