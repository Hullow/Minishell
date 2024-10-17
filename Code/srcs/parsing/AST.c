#include "../../Code/header/Minishell.h"
#include <stdbool.h>

/////////////////////////////////////
/// AST for arithmetic expression ///
/////////////////////////////////////
struct AST_for_numbers
{
	enum
	{
		AST_NUMBER,
		AST_ADD,
		AST_MUL,
	}	tag;
	union
	{
		struct AST_NUMBER
		{
			int	number;
		}	AST_NUMBER;
		struct AST_ADD
		{
			AST *left;
			AST *right;
		}	AST_ADD;
		struct AST_MUL
		{
			AST *left;
			AST *right;
		}	AST_MUL;
	}	data;
};

// creates a new AST node
AST *ast_new(AST ast)
{
  AST *ptr = malloc(sizeof(AST));
  if (ptr)
  	*ptr = ast;
  return ptr;
}



ast_new((AST) {		AST_NUMBER,
				{
					.AST_NUMBER=(struct AST_NUMBER){1} // union part
				}
}
// Now, we can represent an expression 5 + 1 using the following code:
AST *term_ = ast_new((AST){
	AST_ADD, // enum part
	{
		.AST_ADD =(struct AST_ADD) // union part (.AST_ADD is the **designated initializer** to say which element of the union we're initializing)
		{
			ast_new((AST)
			{
				AST_NUMBER, // enum part
				{
					.AST_NUMBER=(struct AST_NUMBER){5} // union part
				}
			}),
			ast_new((AST)
			{
				AST_NUMBER,  // enum part
				{
					.AST_NUMBER=(struct AST_NUMBER){1} // union part
				}
			}),
		}
	}
});

// define to make the creation of new nodes lighter in code
#define AST_NEW(tag, ...) \
  ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})

// example initialization of an AST for the expression: 4 + 2 * 10 + 3 * (5 + 1)
AST *term = 
AST_NEW(AST_ADD,
	AST_NEW(AST_NUMBER, 4),
	AST_NEW(AST_ADD,
	AST_NEW(AST_MUL, 
		AST_NEW(AST_NUMBER, 2), 
		AST_NEW(AST_NUMBER, 10),
	),
	AST_NEW(AST_MUL,
		AST_NEW(AST_NUMBER, 3),
		AST_NEW(AST_ADD,
		AST_NEW(AST_NUMBER, 5),
		AST_NEW(AST_NUMBER, 1),
		),
	),
	),
);

// prints an AST element
void	ast_print(AST *ptr)
{
	AST ast = *ptr;
	if (ast.tag == AST_NUMBER)
	{
		struct AST_NUMBER data = ast.data.AST_NUMBER;
		printf("%d", data.number);
		return;
	}
	else if (ast.tag == AST_ADD)
	{
		struct AST_ADD data = ast.data.AST_ADD;
		printf("(");
		ast_print(data.left);
		printf(" + ");
		ast_print(data.right);
		printf(")");
		return;
	}
	else if (ast.tag == AST_MUL)
	{
		struct AST_ADD data = ast.data.AST_MUL;
		printf("(");
		ast_print(data.left);
		printf(" * ");
		ast_print(data.right);
		printf(")");
		return;
	}
}


///////////////////////////////////
////////   Minishell AST   ////////
///////////////////////////////////
typedef enum {
// Non-terminal symbols
	AST_PROGRAM,
	AST_PROGRAM_PRIME,
	AST_COMMAND,
	AST_CMD_NAME,
	AST_CMD_WORD,
	AST_CMD_PREFIX,
	AST_CMD_PREFIX_PRIME,
	AST_CMD_SUFFIX,
	AST_CMD_SUFFIX_PRIME,
	AST_IO_REDIRECT,
	AST_IO_FILE,
	AST_IO_HERE_DOC,
// Terminal symbols
	AST_WORD,
	AST_ASSIGNMENT_WORD,
	AST_IO_NUMBER,
	AST_PIPE,
	AST_REDIR_INPUT; // '<' symbol
	AST_REDIR_OUTPUT; // '>' symbol
	AST_REDIR_APPEND; // '>>' symbol
	AST_REDIR_HERE_DOC; // <<' symbol
}	AST_Node_Type;

// pre-declared typedef to enable recursive declaration 
typedef struct AST AST;

// Define structures for AST nodes
typedef struct AST {
    AST_Node_Type	type;
	struct AST		*children[3]; // up to three possible children
    union
	{
		// terminal nodes
        typedef struct AST_WORD {
            char *string;
        } AST_WORD;
        typedef struct AST_ASSIGNMENT_WORD {
            char *string;
        } AST_ASSIGNMENT_WORD;
        typedef struct AST_IO_NUMBER {
            int io_number;
        } AST_IO_NUMBER;
        typedef struct AST_PIPE {
		} AST_PIPE;
		typedef struct AST_REDIR_INPUT {
		} AST_REDIR_INPUT;
		typedef struct AST_REDIR_OUTPUT {
		} AST_REDIR_OUTPUT;
		typedef struct AST_REDIR_APPEND {
		} AST_REDIR_APPEND;
		typedef struct AST_REDIR_HEREDOC {
		} AST_REDIR_HEREDOC;
		// non-terminal nodes
		typedef struct AST_IO_HEREDOC {
			AST_REDIR_HEREDOC; // the '<<' redirection heredoc symbol
            AST_WORD *here_end;
        } AST_IO_HEREDOC;
		typedef struct AST_IO_FILE {
			union {
			AST_REDIR_INPUT redir_input;
			AST_REDIR_OUTPUT redir_output;
			AST_REDIR_APPEND redir_append;
			}
			AST_WORD *filename;
        } AST_IO_FILE;
		typedef struct AST_IO_REDIRECT {
				AST_IO_NUMBER *io_number;
				union {
					AST_IO_FILE *io_file;
					AST_IO_HEREDOC *here_document;
				};
			} AST_IO_REDIRECT;
		typedef struct AST_CMD_SUFFIX_PRIME {
			AST_IO_REDIRECT *io_redirect;
			AST_CMD_SUFFIX_PRIME *cmd_suffix_prime;
			AST_WORD *word;
			bool empty; // 0 if empty => need to initialize at 0!
		} AST_CMD_SUFFIX;
		typedef struct AST_CMD_SUFFIX {
			union {
				AST_IO_REDIRECT *io_redirect;
				AST_WORD *word;
			}
			AST_CMD_SUFFIX_PRIME *cmd_suffix_prime;
		} AST_CMD_SUFFIX;
		typedef struct AST_CMD_PREFIX_PRIME {
			union {
				AST_IO_REDIRECT *io_redirect;
				AST_ASSIGNMENT_WORD *assignment_word;
			}
			AST_CMD_PREFIX_PRIME *cmd_prefix_prime;
			bool empty; // 0 if empty => need to initialize at 0!
		} AST_CMD_PREFIX_PRIME;
		typedef struct AST_CMD_PREFIX {
			union {
				AST_IO_REDIRECT *io_redirect;
				AST_ASSIGNMENT_WORD *assignment_word;
			}
			AST_CMD_PREFIX_PRIME *cmd_prefix_prime;
		} AST_CMD_PREFIX;
        typedef struct AST_CMD_WORD {
            AST_WORD *word;
            AST_ASSIGNMENT_WORD *assignment_word;
        } AST_CMD_WORD;
        typedef struct AST_CMD_NAME {
            AST_WORD *word;
        } AST_CMD_NAME;
        typedef struct AST_COMMAND {
            AST_CMD_PREFIX;
			AST_CMD_WORD;
            AST_CMD_SUFFIX;
			AST_CMD_NAME;
        } AST_COMMAND;
        typedef struct AST_PROGRAM_PRIME {
            AST_PIPE *pipe;
			AST_COMMAND *command;
			AST_PROGRAM_PRIME *program_prime;
			bool empty; // 0 if empty => need to initialize at 0!
        } AST_PROGRAM_PRIME;
        typedef struct AST_PROGRAM {
			AST_COMMAND *command;
			AST_PROGRAM_PRIME *program_prime;
		} AST_PROGRAM;
    } data;
} AST;

/// data structures
	typedef struct AST_WORD {
		char *string;
	} AST_WORD;
	typedef struct AST_REDIR_HEREDOC {
	} AST_REDIR_HEREDOC;
	// non-terminal nodes
	typedef struct AST_IO_HEREDOC {
		AST_REDIR_HEREDOC; // the '<<' redirection heredoc symbol
		AST_WORD *here_end;
	} AST_IO_HEREDOC;

// initializes an AST node using ast_new and a compound literal
// returns a here_end AST node (which is of type AST_WORD)
s_AST *ft_parse_here_end(struct s_token *token)
{
	if (!token || !token->str)
		return (NULL);
	s_AST *here_end = NULL;
	here_end = ast_new ((AST) { 	// malloc fail check ?
		AST_WORD,
		{ .AST_WORD = (struct AST_WORD) {token->str} }
	});
	return (here_end);
}

// initializes an AST node using ast_new and a compound literal
// returns a redir_heredoc AST node
// no data, only a node type (AST_REDIR_HEREDOC)
s_AST *ft_parse_redir_heredoc(struct s_token *token)
{
	if (!token || !token->str)
		return (NULL);
	if (token->type != REDIR_HEREDOC)
		return (NULL);
	s_AST *redir_heredoc = ast_new ((AST) {
		AST_REDIR_HEREDOC });
	return (redir_heredoc);
}

struct s_AST	*ft_parse_io_here_doc(struct s_token *token)
{
	if (!token || !token->str)
		return (NULL);
	s_AST *io_here_doc = NULL;
	s_AST *redir_heredoc = NULL;
	s_AST *here_end = NULL;
	if (token->type == REDIR_HEREDOC && token->next)
	{
		redir_heredoc = ft_parse_redir_heredoc(token); // parse redirection symbol, return a REDIR_HEREDOC AST node
		here_end = ft_parse_here_end(token->next); // parse here-document word, return a here_end (WORD) AST node
		if (redir_heredoc && here_end) // if both AST nodes initialized, we initialize a new AST node with the right components
		{
			io_here_doc = ast_new((AST) {
				AST_IO_HEREDOC,
				{
					.AST_IO_HEREDOC = (struct AST_IO_HEREDOC) {
							.AST_REDIR_HEREDOC = redir_heredoc,
							.here_end = here_end
						}
				},
				{

				}
			});
		}
	}
	return (io_here_doc);
}


struct s_AST	*ft_parse_io_file(struct s_token *token)
{
	if (!token || !token->str)
		return (NULL);
	if (token->type == REDIR_OUTPUT && token->next)
	filename = ft_parse_filename(token->next);
	if (filename)
	{
		// make a new io_file node, 
		// with the result of '> filename' as its child
		// and return it
	}
}

/////////////////////////
// Copilot suggestions //
/////////////////////////
// Function to create a new AST node
AST *ast_new(AST ast) {
    AST *ptr = malloc(sizeof(AST));
    if (ptr)
        *ptr = ast;
    return ptr;
}

// Function to parse a filename
AST *ft_parse_filename(char *token) {
    if (!token)
        return NULL;
    return ast_new((AST){
        AST_FILENAME,
        {.filename = {.name = strdup(token)}}
    });
}

// Function to parse io_file
AST *ft_parse_io_file(char *token) {
    if (!token)
        return NULL;

    AST *filename_node = NULL;
    if (strcmp(token, ">") == 0) {
        filename_node = ft_parse_filename(token + 1); // Assuming token + 1 points to the next token
        if (filename_node) {
            return ast_new((AST){
                AST_IO_FILE,
                {.io_file = {AST_FILENAME, 
				.filename = filename_node}}
            });
        }
    }
    // Add similar checks for '<' and 'REDIR_APPEND' if needed
    return NULL;
}

// Example usage
int main() {
    char *token = ">";
    AST *ast = ft_parse_io_file(token);
    if (ast) {
        // Process the AST
    }
    return 0;
}
```

### Remarks

1. **Token Handling**: Ensure that [`token + 1`](command:_github.copilot.openSymbolFromReferences?%5B%22token%20%2B%201%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22path%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A110%2C%22character%22%3A17%7D%7D%5D%5D "Go to definition") correctly points to the next token. In a real parser, you would typically have a more sophisticated way of handling tokens, such as a tokenizer or lexer.
2. **Memory Management**: Remember to free the allocated memory for AST nodes and strings when they are no longer needed to avoid memory leaks.
3. **Error Handling**: Add appropriate error handling to manage invalid tokens or parsing failures.

This implementation provides a basic structure for parsing [`io_file`](command:_github.copilot.openSymbolFromReferences?%5B%22io_file%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22path%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A115%2C%22character%22%3A13%7D%7D%5D%5D "Go to definition") and [`filename`](command:_github.copilot.openSymbolFromReferences?%5B%22filename%22%2C%5B%7B%22uri%22%3A%7B%22%24mid%22%3A1%2C%22fsPath%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22external%22%3A%22file%3A%2F%2F%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22path%22%3A%22%2Fhome%2Ffallan%2FMinishell%2FDocumentation%2FExample-code%2FAST.c%22%2C%22scheme%22%3A%22file%22%7D%2C%22pos%22%3A%7B%22line%22%3A115%2C%22character%22%3A49%7D%7D%5D%5D "Go to definition") nonterminals and generating the corresponding AST nodes. You can extend it to handle other parts of your grammar as needed.