#include "../../Code/header/Minishell.h"


typedef enum {
	AST_COMMAND
}

typedef struct AST AST;

struct AST
{
	enum
	{
		AST_NUMBER,
		AST_ADD,
		AST_MUL,
	}	tag;
	union AST
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

AST *ast_new(AST ast)
{
  AST *ptr = malloc(sizeof(AST));
  if (ptr)
  	*ptr = ast;
  return ptr;
}

// Now, we can represent an expression 5 + 1 using the following code:
AST *term_ = ast_new((AST){
AST_ADD, 
{
	.AST_ADD=(struct AST_ADD){
	ast_new((AST){
		AST_NUMBER, 
		{.AST_NUMBER=(struct AST_NUMBER){5}}
	}),
	ast_new((AST){
		AST_NUMBER, 
		{.AST_NUMBER=(struct AST_NUMBER){1}}}
	),
	}
}
});

#define AST_NEW(tag, ...) \
  ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})


// example: 4 + 2 * 10 + 3 * (5 + 1)
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

struct s_AST	*ft_parse_io_file(struct *s_token token)
{
	if (!token || !token->str)
		return (NULL);
	if (token->type == REDIR_OUTPUT && \
	ft_parse_filename(token->next))
	{
		// make a new io_file node, 
		// with the result of '> filename' as its child
		// and return it
	}

}

ft_parse_filename(token)
{
	if (!token)
		return (NULL);
	ast_new((AST) {WORD,  = (struct tag) )

}


```c
#include <stdlib.h>
#include <string.h>

// Define AST node types
typedef enum {
    AST_IO_FILE,
    AST_FILENAME,
    AST_WORD
} ASTType;

// Define structures for AST nodes
typedef struct AST {
    ASTType type;
    union {
        struct {
            struct AST *filename;
        } io_file;
        struct {
            char *name;
        } filename;
    } data;
} AST;

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
                {.io_file = {.filename = filename_node}}
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