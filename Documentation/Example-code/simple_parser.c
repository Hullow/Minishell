/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallan <fallan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:11:48 by fallan            #+#    #+#             */
/*   Updated: 2024/09/18 15:30:04 by fallan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	main(int argc, char **argv)
{
	if (argc > 1)
		ft_parse(argv[1]);
	else
		printf("string to parse ?\n");
}

Struct: remainder of string to parse, token linked list

struct s_parsed_string
{
	char			*remainder;
	
	int				type;
	bool			is_delimited;
	bool			is_quoted;
	// bool			is_double_quoted;
	// bool			is_single_quoted;
	bool			is_operator;
	struct s_token	*next;
};

// either returns NULL or a token type
// the function must take the sentence, e.g. 
ft_parse_ident()
{

}

void	ft_parse(char *string)
{
	
}


/*
Simple grammar: (derived from [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf))
```
<A> := <A> + <M> | <M>

<M> := <ident> | <const>

<ident> := w | x | y | z

<const> := 0 | 1 | 2 | 3 | 4
```

To parse: `2 + w`
Parsing:
A => A + M => M + M => const + M => 2 + M 
=> 2 + ident => 2 + w

*/


/*
Source: [CSE12 UCSD - Abstract Syntax Trees](https://cseweb.ucsd.edu/~kube/cls/12.s13/Lectures/lec16/lec16.pdf)
### Example parsing
#### Example grammar
```
<A> := <B> | <C>

<B> := <ident> = <A>

<C> := <C> + <D> | <C> - <D> | <D>

<D> := <D> * <M> | <D> / <M> | <M>

<M> := <ident> | <const> | (<A>)

<ident> := w | x | y | z

<const> := 0 | 1 | 2 | 3 | 4
```

#### Strings to parse
##### `2 + w + 3`
*/