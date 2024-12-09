// VAR1="bonjour merci"
// VAR2="super de rien"
// INPUT: echo hello world $VAR1 aurevoir $VAR2 


char **ft_expand_and_allocate_all_args(char **args)
{
char	***all_args;

char	**VAR1 = {"bonjour", "merci"};
char	**VAR2 = {"super", "de rien"};


// INPUT : cmd_list->args: ["echo"] ["hello"] ["world"] [$VAR1] ["aurevoir"] [$VAR2]
all_args = malloc(#tokens * sizeof(char **)); // here: 6 tokens

while (args)
{

	all_args[i] = expand(args[i]);

char **expand(char *arg)
{
	char **expanded_arg;
	if (!(check_expand(arg))) // e.g. if arg = "echo"
	{
		expanded_arg = malloc(2 * sizeof(char *));
		expanded_arg = {arg, NULL}; {"echo", NULL}
	}
	else // if arg = $VAR1
	{
		// expansion
	}
	return (expanded_arg);
}
// RESULT:
	// all_args[0] = {"echo", NULL}; // all_args[0][0] == "echo"; all_args[0][1] == NULL;
	// all_args[1] = {"hello", NULL}; // all_args[1][0] == "hello"; all_args[1][1] == NULL;
	// all_args[2] = {"world", NULL}; // all_args[2][0] == "world"; all_args[2][1] == NULL;
	// all_args[3] = VAR1; // all_args[3][0] == "bonjour"; all_args[3][1] == "merci"; all_args[3][2] == NULL;
	// all_args[4] = {"aurevoir", NULL}; // all_args[4][0] == "aurevoir"; all_args[4][1] == NULL;
	// all_args[5] = VAR2; // all_args[5][0] == "super"; all_args[5][1] == "de rien"; all_args[5][2] == NULL;
}

	int size = ft_size_all_args(all_args);
	char **args = malloc(size); // output de la fonction
	k = 0;
	while (k < size)
	{
		while (all_args[i][j])
		{
			args[k] = 

		}

		i++;
	}
}



Tab1 : [echo, hello, world, $VAR1, aurevoir, $VAR2]
Tab1 : [echo, hello, world, Tab2, aurevoir, tab3]
Tab2 : [TEST]
tab3 : [TEST2]