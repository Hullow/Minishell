/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:52:54 by fallan            #+#    #+#             */
/*   Updated: 2024/10/03 16:48:26 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct AST AST;

struct AST
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
		struct AST_ADD;
		{
			AST *left;
			AST *right;
		}	AST_ADD;
		struct AST_MUL;
		{
			AST *left;
			AST *right;
		}	AST_MUL;
	}	data;
};

AST	*ast_new(AST ast)
{
	AST *ptr = malloc(sizeof(AST));
	if (ptr)
		*ptr = ast;
	return ptr;
}

AST *term_ = ast_new((AST){
	AST_ADD, // enum part
	{
		.AST_ADD =(struct AST_ADD) // union part (.AST_ADD is the **designated initializer** to say which element of the union we're initializing)
		{
			ast_new((AST)
			{
				AST_NUMBER, // enum part
				{
					.AST_NUMBER=(struct AST_NUMBER){5}
				}
			}),
			ast_new((AST)
			{
				AST_NUMBER,
				{
					.AST_NUMBER=(struct AST_NUMBER){1}
				}
			}),
		}
	}
});

#define AST_NEW(tag, ...) \
	ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})


// example of use of this define with 4 + 2 * 10 + 3 * (5 + 1)
AST *term =
	AST_NEW(AST_ADD,
		AST_NEW(AST_NUMBER, 4),
		AST_NEW(AST_ADD,
			AST_NEW(AST)
		))