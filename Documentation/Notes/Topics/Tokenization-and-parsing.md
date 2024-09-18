# Tokenization and parsing

## Tokenization

- Doubly linked list ?
	=> no use, we never have to check the previous token

## Problems

## Parsing
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

```
<A> => <C> => <C> + <D> => <C> + <M> => <C> + <const> => <C> + <D> + <const> => <C> + <M> + <const> => <C> + <ident> + <const> => <D> + <ident> + <const> => <M> + <ident> + <const> => <const> + <ident> + <const>
```

Solution:
```
<A> => <C> => <C> + <D> => <C> + <M> =>
<C> + <const> => <C> + 3 =>
<C> + <D> + 3 => <D> + <D> + 3 =>
<M> + <D> + 3 => <M> + <M> + 3 =>
<const> + <M> + 3 => <const> + <ident> + 3 =>
2 + <ident> + 3 => 2 + w + 3 
```

##### `2 + w * 3`
```
<A> => <C> => <C> + <D> => <M> + <D> => <const> + <D> => 2 + <D> => 2 + <D> * <M> => 2 + <M> * <M>
=> 2 + <ident> * <M> => 2 + w * <M> => 2 + w * <const> => 2 + w * 3
```

##### `(2 + w) * 3`
```
<A> => <C> => <D> => <D> * <M> => <M> * <M> => (<A>) * <M> 
=> (<C>) * <M> => (<C> + <D>) * <M> => (<D> + <D>) * <M>
=> (<M> + <D>) * <M> => (<const> + <D>) * <M> => (2 + <D>) * <M>
=> (2 + <M>) * <M> => (2 + <ident>) * <M> => (2 + w) * <M>
=> (2 + w) * <const> => => (2 + w) * 3
```

### Parse trees
#### Structure
- Every derivation has a corresponding **parse tree**:
	- each node corresponds to one symbol in the BNF grammar:
		- root: "start" symbol
		- leaves: terminal symbols
		- internal nodes: nonterminal symbols
	- The children of an internal node in the parse tree correspond to the symbols in a definition of the nonterminal symbol corresponding to their parent node
	- reading the leaves of the parse tree left to right gives you the string that has been parsed

#### Building a parse tree

### Abstract syntax tree (AST)
- A parse tree includes *all* the information in a derivation of a string from a start symbol
- This may be more information than is required for some applications of the tree
- A parse tree with nonessential nodes left out is called an **Abstract Syntax Tree** (AST)

- Syntactic analysis == building an AST : <br>
> The input to the syntactic analysis phase of an interpreter is a string; the output is an AST
- Two main issues:
	- AST data structure design: what type of objects to use for the nodes, etc.
	- algorithm used to build the AST

#### AST data structure design
- nodes can have more than 2 children
- nodes are of somewhat different types (?)
- nodes are also of similar type: all correspond to part of an input string at some level of analysis

##### Object-oriented approach
- Define separate class for each different nonterminal symbol in the grammar. Nodes will be instances of these classes. This allows different types of nodes to have different possible numbers of children, and different behavior (different methods)
- Make all these classes derived from one base class, or make them all implement one interface. This permits polymorphism
- Method: follow the BNF grammar definitions:
	- each class in the OO design has a method that "knows how" to parse a string according to the definition of the nonterminal symbol corresponding to that class
	- "knowing how" to parse a string will rely on parse methods in other classes, that know how to parse strings according to the definitions of their corresponding symbols!
	- **if the method successfully parse the string, it should return a pointer to an AST node of the appropriate subtype, with its children initialized in the appropriate way**
	- **if the method cannot successfully parse the string it should return a null pointer to indicate that fact**

###### Example implementation
- Non-terminal symbol `<A>` defined as `<A> := <B> | <C>`:
```code
public static A parse (String s)
{
	if (B.parse(s) != null)
	{
		// the string satisfies definition of <B>; so,
		// make a new A node, with the result of B.parse(s)
		// as its child, and return it
	}
	else if (C.parse(s) != null)
	{
		// the string satisfies definition of <C>; so,
		// make a new A node, with the result of C.parse(s)
		// as its child, and return it
	}
	else // the string does not satisfy definition of <A>
		return null;
}
```

#### Semantic rules
- An interpreter does:
	1. **syntactic analysis**, constructing an AST
	2. **semantic evaluation**, according to the semantic rules for the language
- To implement semantic evaluation correctly, clearly stated and followed semantic rules are necessary
- Unfortunately, there is no universally accepted notation for specifying semantic rules that is as standard as BNF notation is for specifying syntax rules
- Usually, semantic rules are stated as English or pseudocode, attached to each BNF rule, or equivalently, to each type of node in the AST

##### Examples of semantic rules
- `<A> := <B> | <C>` : the value of `<A>` is the value of `<B>` or `<C>`, as appropriate
- `<B> := <ident> = <A>` : the value of `<B>` is the value of `<A>` on the right hand side of the `=`. In addition, evaluating a `<B>` has the side effect of assigning the value of `<A>` to the variable named by the `<ident>`
- `<C> := <C> + <D>` : the value of `<C>` is the value of the `<C>` plus the value of `<D>`
- `<ident> := w | x | y | z` : the value of `<ident>` is the value of the variable named by the identifier. If the variable has not been assigned a value, it is a runtime error
- `<const> := 0 | 1 | 2 | 3 | 4` : the value of `<const>` is the value of the matching literal constant

### Concepts in parsing
#### [Backtracking](https://en.wikipedia.org/wiki/Backtracking)
> a class of algorithms for finding solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons a candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

#### [Leftmost vs rightmost derivation](https://cs.stackexchange.com/questions/54814/different-between-left-most-and-right-most-derivation)
> Given a derivation tree for a word, you can "implement" it as a sequence of productions in many different ways. The leftmost derivation is the one in which you always expand the leftmost non-terminal. The rightmost derivation is the one in which you always expand the rightmost non-terminal.

Example:
- Grammar: `A : A - A | A + A | a`

- Rightmost derivation:
`A => A - A => A - a => A + A - a => A + a - a => a + a - a`

- Leftmost derivation:
`A => A - A => A + A - A => a + A - A => a + a - A => a + a - a`

(Note: the grammar is [ambiguous](#ambiguity))

#### Ambiguity
More than one way (more than one [parse tree](#parse-trees)) to produce the sentence from a grammar => semantic issues

##### Essential and spurious ambiguity
A sentence from a grammar can easily have more than one production tree, i.e., there can easily be more than one way to produce the sentence. From a formal point of view this is a non-issue (a set does not count how many times it contains an element), but as soon as we are interested in the semantics, the difference becomes significant. Not surprisingly, a sentence with more than one production tree is called ambiguous, but we must immediately distinguish between **essential ambiguity** and **spurious ambiguity**. <br>

The difference comes from the fact that we are not interested in the production trees per se, but rather in the semantics they describe. An ambiguous sentence is **spuriously ambiguous if all its production trees describe the same semantics**; **if some of them differ in their semantics, the ambiguity is essential**. <br>

The notion of “ambiguity” can also be defined for grammars: a grammar is essentially ambiguous if it can produce an essentially ambiguous sentence, spuriously ambiguous if it can produce a spuriously ambiguous sentence (but not an essentially ambiguous one) and unambiguous if it cannot do either.<br>
 <br> From: *Parsing Techniques – Grune & Jacobs (2008)*

##### Evaluating ambiguity
> **It is often important to be sure that a grammar is not ambiguous, but unfortunately that property is undecidable**: it can be proved that there cannot be an algorithm that can, for every CF grammar, decide whether it is ambiguous or unambiguous.<br>(..)<br>
> **The most effective ambiguity test for a CF grammar we have at present is the construction of the corresponding LR(k) automaton, but it is not a perfect test**: if the construction succeeds, the grammar is guaranteed to be unambiguous; if it fails, in principle nothing is known. In practice, however, the reported conflicts will often point to genuine ambiguities. The construction of an LR-regular parser (Section 9.13.2) is an even stronger, but more complicated test<br>
From *Parsing Techniques – Grune & Jacobs (2008)*

#### Minishell grammar
Adapted from [Shell Grammar - Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10_02) for the Minishell Subject.

```BNF
/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */
%token  WORD
%token  ASSIGNMENT_WORD
%token  NAME
%token  IO_NUMBER

/* The following are the operators (either a control operator or redirection operator) containing more than one character. */

%token  REDIR_HEREDOC  REDIR_APPEND
/*     		 '<<'   	   '>>'   */

/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */
%start program
%%
program          : pipe_sequence
                 ;

pipe_sequence	 : command
                 | pipe_sequence '|' command
                 ;

command   		 : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD                   /* Apply rule 7a (see Shell-functioning.md)*/
                 ;

cmd_word         : WORD                   /* Apply rule 7b (see Shell-functioning.md)*/
                 ;

cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;

cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;

redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;

io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here
                 ;

io_file          : '<'			filename
                 | '>'			filename
                 | REDIR_APPEND	filename
                 ;

filename         : WORD                      /* Apply rule 2 (see Shell-functioning.md)*/
                 ;

io_here          : REDIR_HEREDOC     here_end
                 ;

here_end         : WORD                      /* Apply rule 3 (see Shell-functioning.md)*/
                 ;

```

##### Notes on the grammar
- It is [left-recursive](https://en.wikipedia.org/wiki/Left_recursion), for instance with `pipe_sequence : pipe_sequence '|' command`


#### Illustrations
if (ft_parse_pipe)
{
	if (ft_find_pipe_in_list)
		ft_pipe_

}
else if (ft_parse_command)


cmd1

cmd1 | cmd2 | cmd3

=> cmd1 | cmd2 | cmd3 => command


Example prompts to parse:
export VAR = 14

echo "VAR=14"

echo "hello, world" > file1
ls > ls.txt | grep file1

find . -name "file*" 2>error.txt
find . -name "file*" 1>find.txt | 

##### Parsing examples
`echo hello > 2 > 4` :

program -> pipe_sequence -> command -> cmd_name + cmd_suffix -> WORD ('echo') + cmd_suffix -> WORD ('echo') + cmd_suffix + io_redirect -> WORD ('echo') + cmd_suffix + io_redirect + io_redirect -> WORD ('echo') + WORD ('hello') + io_redirect + io_redirect -> WORD ('echo') + WORD ('hello') + io_file + io_redirect -> WORD ('echo') + WORD ('hello') + '>' filename + io_redirect -> WORD ('echo') + WORD ('hello') + '>'	WORD ('2') + io_redirect -> WORD ('echo') + WORD ('hello') + '>' WORD ('2') + '>' filename -> WORD ('echo') + WORD ('hello') + '>' WORD ('2') + '>' WORD ('4')

## Parsing techniques
> The basic connection between a sentence and the grammar it derives from is the parse tree, which describes how the grammar was used to produce the sentence. For the reconstruction of this connection we need a parsing technique. When we consult the extensive literature on parsing techniques, we seem to find dozens of them, yet **there are only two techniques to do parsing**; all the rest is technical detail and embellishment.<br>
> The first method tries to imitate the original production process by rederiving the sentence from the start symbol. This method is called *top-down*, because the parse tree is reconstructed from the top downwards.<br>
> The second method tries to roll back the production process and to reduce the sentence back to the start symbol. Quite naturally this technique is called *bottom-up*.<br>
From *Parsing Techniques – Grune & Jacobs (2008)*

## Attempt implementation
///// Recursive Decent Parsing
///// ATTEMPT TO IMPLEMENT 
/////
// typedef enum {command, cmd_name, cmd_word, cmd_prefix, cmd_suffix} Symbol;
// To parse our string using the grammar (see Tokenization-and-parsing####Minishell_grammar)
// if we are attempting to match e.g. a "command" symbol (left-hand side),
// e.g. for the string: grep hello
// => tokenization: 'grep', 'hello' 
// for *cmd_prefix cmd_word cmd_suffix*:
	// what do we check for "cmd_prefix" ? "grep" or "grep hello"
	// it's minimum 3 tokens, so it cannot be can only be a subset by definition, so we remove two

	// e.g. for the string: find . -name "hello"
	// cmd_prefix => find .
/* struct token	*ft_parse_using_grammar(struct token *head)
{

	// Example:
	// 
	ft_parse_pipe_sequence
	{
		if (ft_parse_command != NULL)
		{
			// To implement later:
				// string satisfies definition of "cmd_prefix cmd_word cmd_suffix"
				// string satisfies definition of "cmd_prefix cmd_word"
				// string satisfies definition of "cmd_prefix"

			// string satisfies definition of "cmd_name cmd_suffix"
			if (ft_parse_command_name != NULL)
			// string satisfies definition of "cmd_name"
			else if (ft_parse_command_name != NULL)

			else
				return NULL;
		}
		// else if (ft_parse_pipe_sequence != NULL)
		// {

		// }
		else
			return NULL;
	}
} */

/* ft_parse_command_suffix(struct token *tok)
{
// io_redirect
// 		=> TO IMPLEMENT

// | cmd_suffix io_redirect
// 		=> TO IMPLEMENT

// |            WORD
	if (tok)
		tok->type = WORD;
	
// | cmd_suffix WORD
// 		=> TO IMPLEMENT
}

ft_parse_command_name(struct token *tok)
{
	if (ft_strchr(tok->str, '=') == NULL)
		tok->type = WORD;
	else	
		return (NULL); // should be 7b : ft_parse_command_word(tok);
	return (tok);
} */
