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

#### Minishell grammar

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

pipe_sequence    : command
                 | pipe_sequence '|' command
                 ;

command   		 : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD                   /* Apply rule 7a */
                 ;

cmd_word         : WORD                   /* Apply rule 7b */
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

filename         : WORD                      /* Apply rule 2 */
                 ;

io_here          : REDIR_HEREDOC     here_end
                 ;

here_end         : WORD                      /* Apply rule 3 */
                 ;

```


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


export VAR = 14

echo "VAR=14"


echo "hello, world" > file1
ls > ls.txt | grep file1


find . -name "file*" 2>error.txt
find . -name "file*" 1>find.txt | 









##### Parsing examples
`echo hello > 2 > 4` :

program -> pipe_sequence -> command -> cmd_name + cmd_suffix -> WORD ('echo') + cmd_suffix -> WORD ('echo') + cmd_suffix + io_redirect -> WORD ('echo') + cmd_suffix + io_redirect + io_redirect -> WORD ('echo') + WORD ('hello') + io_redirect + io_redirect -> WORD ('echo') + WORD ('hello') + io_file + io_redirect -> WORD ('echo') + WORD ('hello') + '>' filename + io_redirect -> WORD ('echo') + WORD ('hello') + '>'	WORD ('2') + io_redirect -> WORD ('echo') + WORD ('hello') + '>' WORD ('2') + '>' filename -> WORD ('echo') + WORD ('hello') + '>' WORD ('2') + '>' WORD ('4')


