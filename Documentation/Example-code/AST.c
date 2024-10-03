
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
